"""Wild encounter parsing and species-location aggregation."""

from __future__ import annotations

import json
import re
from collections import defaultdict

from ..constants import (
    BATTLE_PYRAMID_WILD_LABEL,
    DOCS_HIDDEN_WILD_ENCOUNTER_MAPS,
    ENCOUNTER_SLOT_RATES,
    JOHTO_ROUTE_PROGRESS,
    TIME_NIGHT_SUFFIX,
    UNKNOWN_MAP,
)
from ..c_parser import clean_constant_name, parse_define_aliases, read
from ..map_names import is_docs_excluded_map, map_constant_display_name, map_data_by_constant
from ..models import EncounterMon, RawEncounterRow, SpeciesLocation, SpeciesRow, WildEncounterRow
from ..paths import MAP_GROUPS_JSON, SPECIES_H, WILD_ENCOUNTERS_JSON
from .hidden_grottos import HiddenGrottoRow


def combine_duplicate_species_slots(mons: list[EncounterMon]) -> list[EncounterMon]:
    """Combine repeated species slots while retaining their full level range."""
    combined: dict[str, EncounterMon] = {}
    for mon in mons:
        species = mon["species"]
        if species not in combined:
            combined[species] = mon.copy()
            continue

        current = combined[species]
        min_levels = [
            level
            for level in (current.get("minLevel"), mon.get("minLevel"))
            if level is not None
        ]
        max_levels = [
            level
            for level in (current.get("maxLevel"), mon.get("maxLevel"))
            if level is not None
        ]
        rates = [
            rate
            for rate in (current.get("rate"), mon.get("rate"))
            if rate is not None
        ]
        current["minLevel"] = min(min_levels) if min_levels else None
        current["maxLevel"] = max(max_levels) if max_levels else None
        current["rate"] = sum(rates) if rates else None
    return list(combined.values())


def parse_wild_encounters(by_species: dict[str, SpeciesRow]) -> list[WildEncounterRow]:
    data = json.loads(read(WILD_ENCOUNTERS_JSON))
    try:
        map_groups_data = json.loads(read(MAP_GROUPS_JSON))
    except (FileNotFoundError, json.JSONDecodeError):
        map_groups_data = {}
    map_groups = {
        map_name: group_name
        for group_name in map_groups_data.get("group_order") or []
        for map_name in map_groups_data.get(group_name) or []
    }
    aliases = parse_define_aliases(SPECIES_H, "SPECIES_")
    rows = []
    original_index = 0
    for group in data.get("wild_encounter_groups", []):
        if group.get("label") == BATTLE_PYRAMID_WILD_LABEL:
            continue
        for encounter in group.get("encounters", []):
            map_const = encounter.get("map", UNKNOWN_MAP)
            if map_const == UNKNOWN_MAP or map_const in DOCS_HIDDEN_WILD_ENCOUNTER_MAPS:
                continue
            map_data = map_data_by_constant().get(map_const, {})
            map_name = str(map_data.get("name") or "")
            if is_docs_excluded_map(map_name, map_groups.get(map_name, "")):
                continue
            label = map_constant_display_name(map_const)
            base_label = encounter.get("base_label", "")
            time_label = "Night" if base_label.endswith(TIME_NIGHT_SUFFIX) else "Day"
            methods = []
            for method, payload in encounter.items():
                if not isinstance(payload, dict) or "mons" not in payload:
                    continue
                mons = []
                slot_rates = ENCOUNTER_SLOT_RATES.get(method, [])
                for slot, mon in enumerate(payload.get("mons", [])):
                    raw_species_const = mon.get("species", "SPECIES_NONE")
                    species_const = aliases.get(raw_species_const, raw_species_const)
                    species = by_species.get(species_const)
                    mons.append({
                        "species": species_const,
                        "hasSpecies": species is not None,
                        "name": species.name if species else clean_constant_name(species_const, "SPECIES_"),
                        "sprite": species.sprite if species else None,
                        "minLevel": mon.get("min_level"),
                        "maxLevel": mon.get("max_level"),
                        "rate": slot_rates[slot] if slot < len(slot_rates) else mon.get("encounter_rate"),
                    })
                # Fishing odds are scoped to separate rod groups that the UI
                # derives from slot positions, so those slots must stay intact.
                if method != "fishing_mons":
                    mons = combine_duplicate_species_slots(mons)
                methods.append({"key": method, "method": method.replace("_", " ").title(), "mons": mons})
            if methods:
                rows.append({
                    "map": map_const,
                    "name": label,
                    "baseLabel": base_label,
                    "time": time_label,
                    "methods": methods,
                    "_order": original_index,
                })
                original_index += 1
    rows = merge_time_variant_encounters(rows)
    rows.sort(key=wild_encounter_sort_key)
    for row in rows:
        row.pop("_order", None)
    return rows

def canonical_encounter_label(base_label: str) -> str:
    return re.sub(r"_Night$", "", base_label or "")

def merge_time_variant_encounters(rows: list[RawEncounterRow]) -> list[RawEncounterRow]:
    merged: dict[tuple[str, str], RawEncounterRow] = {}
    for row in rows:
        key = (row["map"], canonical_encounter_label(row["baseLabel"]))
        if key not in merged:
            merged[key] = {
                "map": row["map"],
                "name": row["name"],
                "baseLabel": canonical_encounter_label(row["baseLabel"]) or row["baseLabel"],
                "variants": [],
                "_order": row["_order"],
            }
        target = merged[key]
        target["_order"] = min(target["_order"], row["_order"])
        target["variants"].append({
            "time": row["time"],
            "baseLabel": row["baseLabel"],
            "methods": row["methods"],
            "_order": row["_order"],
        })

    for row in merged.values():
        row["variants"].sort(key=lambda variant: (variant["time"] == "Night", variant["_order"]))
        has_night_variant = any(variant["time"] == "Night" for variant in row["variants"])
        row["hasTimeVariants"] = has_night_variant
        for variant in row["variants"]:
            variant["showTime"] = has_night_variant
            variant.pop("_order", None)
    return list(merged.values())

def wild_encounter_sort_key(encounter: RawEncounterRow) -> tuple[int, int, int]:
    haystack = f"{encounter.get('map', '')} {encounter.get('baseLabel', '')} {encounter.get('name', '')}"
    match = re.search(r"\b(?:MAP_)?ROUTE_?(\d+)\b|\bRoute\s*(\d+)\b|\bgRoute(\d+)\b", haystack, re.IGNORECASE)
    route = int(next(group for group in match.groups() if group)) if match else None
    if route in JOHTO_ROUTE_PROGRESS:
        return (0, JOHTO_ROUTE_PROGRESS[route], encounter["_order"])
    return (1, encounter["_order"], 0)

def build_species_locations(encounters: list[WildEncounterRow]) -> dict[str, list[SpeciesLocation]]:
    locations: dict[str, list[SpeciesLocation]] = defaultdict(list)
    seen: dict[str, set[tuple[object, ...]]] = defaultdict(set)
    for encounter in encounters:
        for variant in encounter.get("variants", [{"time": "", "methods": encounter.get("methods", [])}]):
            time = variant.get("time", "") if variant.get("showTime") else ""
            for method in variant["methods"]:
                for mon in method["mons"]:
                    key = (
                        encounter["map"],
                        time,
                        method["method"],
                        mon.get("minLevel"),
                        mon.get("maxLevel"),
                        mon.get("rate"),
                    )
                    if key in seen[mon["species"]]:
                        continue
                    seen[mon["species"]].add(key)
                    locations[mon["species"]].append({
                        "map": encounter["map"],
                        "name": encounter["name"],
                        "time": time,
                        "method": method["method"],
                        "minLevel": mon.get("minLevel"),
                        "maxLevel": mon.get("maxLevel"),
                        "rate": mon.get("rate"),
                    })
    return dict(locations)


def add_hidden_grotto_species_locations(
    locations: dict[str, list[SpeciesLocation]],
    grottos: list[HiddenGrottoRow],
) -> None:
    for grotto in grottos:
        for species in grotto["species"]:
            location: SpeciesLocation = {
                "map": grotto["map"],
                "name": grotto["name"],
                "time": "",
                "method": "Hidden Grotto",
                "minLevel": grotto["level"],
                "maxLevel": grotto["level"],
                "rate": 25,
            }
            locations.setdefault(species, [])
            if location not in locations[species]:
                locations[species].append(location)
