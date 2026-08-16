"""Parse reachable scripted Pokemon sources for species location documentation."""

from __future__ import annotations

import json
import re
from collections import defaultdict
from typing import Mapping

from ..c_parser import parse_define_aliases, read, strip_c_comments
from ..map_names import is_docs_excluded_map, map_display_name
from ..models import SpeciesLocation, SpeciesRow
from ..paths import GACHA_C, MAP_GROUPS_JSON, ODD_EGG_C, REPO_ROOT, SPECIES_H


SCRIPT_LABEL_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)(?:::|:)\s*$", re.MULTILINE)
GIFT_COMMAND_RE = re.compile(
    r"\b(givemon|giveegg)\s+(SPECIES_[A-Z0-9_]+)(?:\s*,\s*(\d+))?",
    re.IGNORECASE,
)
LEGENDARY_ENCOUNTER_RE = re.compile(
    r"\b(?:bosslegendaryencounterwithmoves|bosslegendaryencounter|legendaryencounter)"
    r"\s+(SPECIES_[A-Z0-9_]+)\s*,\s*(\d+)\b",
    re.IGNORECASE,
)
MASTER_GACHA_ARRAY_RE = re.compile(
    r"static\s+const\s+u16\s+sGachaMasterSpecies(?:Common|Uncommon|Rare|UltraRare)\[\]\s*=\s*\{(.*?)\};",
    re.DOTALL,
)
ODD_EGG_ARRAY_RE = re.compile(
    r"static\s+const\s+u16\s+sOddEggSpecies(?:\[[^\]]*\])?\s*=\s*\{(.*?)\};",
    re.DOTALL,
)
GIFT_LOCATION_NAME_OVERRIDES = {
    ("SPECIES_BELDUM", "MAP_KITAKAMI_HOUSES"): "Gift from Steven in Kitakami",
    ("SPECIES_GRENINJA_BOND", "MAP_ROUTE40_HOUSE4"): "Route 40 Achievement reward (30 trophies)",
    ("SPECIES_POIPOLE", "MAP_ROUTE40_HOUSE4"): "Route 40 Achievement reward (45 trophies)",
    ("SPECIES_FLOETTE_ETERNAL", "MAP_ROUTE40_HOUSE4"): "Route 40 Achievement reward (60 trophies)",
    ("SPECIES_ZARUDE", "MAP_ROUTE40_HOUSE4"): "Route 40 Achievement reward (75 trophies)",
    ("SPECIES_MAGEARNA_ORIGINAL", "MAP_ROUTE40_HOUSE4"): "Route 40 Achievement reward (100 trophies)",
}
LEGENDARY_LOCATION_NAME_OVERRIDES = {
    "MAP_CERULEAN_CAVE_B2F": "Nameless Cave",
}
FOSSIL_REVIVAL_ITEMS = {
    "SPECIES_LILEEP": "ITEM_ROOT_FOSSIL",
    "SPECIES_ANORITH": "ITEM_CLAW_FOSSIL",
    "SPECIES_OMANYTE": "ITEM_HELIX_FOSSIL",
    "SPECIES_KABUTO": "ITEM_DOME_FOSSIL",
    "SPECIES_AERODACTYL": "ITEM_OLD_AMBER",
    "SPECIES_ARCHEN": "ITEM_PLUME_FOSSIL",
    "SPECIES_TYRUNT": "ITEM_JAW_FOSSIL",
    "SPECIES_AMAURA": "ITEM_SAIL_FOSSIL",
}
FOSSIL_REVIVAL_LEVELS = {
    "SPECIES_KABUTO": ((5, "before 4th badge"), (20, "after 4th badge")),
}
FOSSIL_LAB_MAP = "MAP_RUINS_OF_ALPH_LAB"


def species_aliases() -> dict[str, str]:
    return parse_define_aliases(SPECIES_H, "SPECIES_")


def script_blocks(text: str) -> dict[str, str]:
    text = strip_c_comments(text)
    matches = list(SCRIPT_LABEL_RE.finditer(text))
    return {
        match.group(1): text[match.end():matches[index + 1].start() if index + 1 < len(matches) else len(text)]
        for index, match in enumerate(matches)
    }


def reachable_script_labels(map_data: Mapping[str, object], blocks: dict[str, str]) -> set[str]:
    roots = {
        str(event.get("script"))
        for event_key in ("object_events", "coord_events", "bg_events")
        for event in map_data.get(event_key) or []
        if event.get("script")
    }
    roots.update(label for label in blocks if label.endswith("_MapScripts"))

    reachable: set[str] = set()
    pending = [label for label in roots if label in blocks]
    known_labels = set(blocks)
    while pending:
        label = pending.pop()
        if label in reachable:
            continue
        reachable.add(label)
        references = set(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", blocks[label]))
        pending.extend(references & known_labels - reachable)
    return reachable


def ruins_of_alph_rock_smash_fossils() -> set[str]:
    """Return the fossils currently available from the Ruins of Alph rocks."""
    try:
        text = strip_c_comments(read(REPO_ROOT / "src/wild_encounter.c"))
    except FileNotFoundError:
        return set()
    match = re.search(
        r"sRockSmashItems_RuinsOfAlph\[\]\s*=\s*\{(.*?)\n\};",
        text,
        re.DOTALL,
    )
    return set(re.findall(r"\bITEM_(?:[A-Z0-9_]*FOSSIL|OLD_AMBER)\b", match.group(1))) if match else set()


def add_fossil_revival_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    """Document fossil revivals separately from ordinary scripted gifts."""
    rock_smash_fossils = ruins_of_alph_rock_smash_fossils()
    for species, fossil in FOSSIL_REVIVAL_ITEMS.items():
        if species not in by_species:
            continue
        fossil_name = fossil.removeprefix("ITEM_").replace("_", " ").title()
        for level, condition in FOSSIL_REVIVAL_LEVELS.get(species, ((20, ""),)):
            method = f"Revived from {fossil_name}"
            if condition:
                method += f" ({condition})"
            if fossil in rock_smash_fossils:
                method += "; fossil found via Rock Smash in Ruins of Alph"
            location: SpeciesLocation = {
                "map": FOSSIL_LAB_MAP,
                "name": "Ruins of Alph Lab",
                "time": "",
                "method": method,
                "minLevel": level,
                "maxLevel": level,
                "rate": None,
            }
            locations.setdefault(species, [])
            if location not in locations[species]:
                locations[species].append(location)


def add_gift_species_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    try:
        map_groups = json.loads(read(MAP_GROUPS_JSON))
    except (FileNotFoundError, json.JSONDecodeError):
        return

    aliases = species_aliases()
    gifts: dict[str, list[SpeciesLocation]] = defaultdict(list)
    for group_name in map_groups.get("group_order") or []:
        for map_name in map_groups.get(group_name) or []:
            if is_docs_excluded_map(map_name, group_name):
                continue
            map_dir = REPO_ROOT / "data" / "maps" / map_name
            script = map_dir / "scripts.inc"
            try:
                map_data = json.loads(read(map_dir / "map.json"))
                blocks = script_blocks(read(script))
            except (FileNotFoundError, json.JSONDecodeError):
                continue

            map_constant = str(map_data.get("id") or "")
            display_name = map_display_name(map_data, map_name)
            for label in reachable_script_labels(map_data, blocks):
                for command in GIFT_COMMAND_RE.finditer(blocks[label]):
                    method, raw_species, raw_level = command.groups()
                    species = aliases.get(raw_species, raw_species)
                    if species not in by_species:
                        continue
                    if map_constant == FOSSIL_LAB_MAP and species in FOSSIL_REVIVAL_ITEMS:
                        continue
                    level = int(raw_level) if raw_level is not None else None
                    location_name = GIFT_LOCATION_NAME_OVERRIDES.get(
                        (species, map_constant),
                        display_name,
                    )
                    location: SpeciesLocation = {
                        "map": map_constant,
                        "name": location_name,
                        "time": "",
                        "method": "Gift Egg" if method.lower() == "giveegg" else "Gift",
                        "minLevel": level,
                        "maxLevel": level,
                        "rate": None,
                    }
                    if location not in gifts[species]:
                        gifts[species].append(location)

    add_fossil_revival_locations(gifts, by_species)

    for species, gift_locations in gifts.items():
        locations.setdefault(species, [])
        for location in gift_locations:
            if location not in locations[species]:
                locations[species].append(location)


def add_scripted_legendary_species_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    """Add reachable encounters created by the supported legendary script macros."""
    try:
        map_groups = json.loads(read(MAP_GROUPS_JSON))
    except (FileNotFoundError, json.JSONDecodeError):
        return

    aliases = species_aliases()
    legendary_locations: dict[str, list[SpeciesLocation]] = defaultdict(list)
    for group_name in map_groups.get("group_order") or []:
        for map_name in map_groups.get(group_name) or []:
            if is_docs_excluded_map(map_name, group_name):
                continue
            map_dir = REPO_ROOT / "data" / "maps" / map_name
            try:
                map_data = json.loads(read(map_dir / "map.json"))
                blocks = script_blocks(read(map_dir / "scripts.inc"))
            except (FileNotFoundError, json.JSONDecodeError):
                continue

            map_constant = str(map_data.get("id") or "")
            display_name = LEGENDARY_LOCATION_NAME_OVERRIDES.get(
                map_constant,
                map_display_name(map_data, map_name),
            )
            for label in reachable_script_labels(map_data, blocks):
                for command in LEGENDARY_ENCOUNTER_RE.finditer(blocks[label]):
                    raw_species, raw_level = command.groups()
                    species = aliases.get(raw_species, raw_species)
                    if species not in by_species:
                        continue
                    level = int(raw_level)
                    location: SpeciesLocation = {
                        "map": map_constant,
                        "name": display_name,
                        "time": "",
                        "method": "Legendary encounter",
                        "minLevel": level,
                        "maxLevel": level,
                        "rate": None,
                    }
                    if location not in legendary_locations[species]:
                        legendary_locations[species].append(location)

    for species, scripted_locations in legendary_locations.items():
        locations.setdefault(species, [])
        for location in scripted_locations:
            if location not in locations[species]:
                locations[species].append(location)


def add_master_gachapon_species_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    try:
        text = strip_c_comments(read(GACHA_C))
    except FileNotFoundError:
        return

    aliases = species_aliases()
    for pool in MASTER_GACHA_ARRAY_RE.findall(text):
        for raw_species in re.findall(r"\bSPECIES_[A-Z0-9_]+\b", pool):
            species = aliases.get(raw_species, raw_species)
            if species not in by_species:
                continue
            location: SpeciesLocation = {
                "map": "MAP_MAUVILLE_CITY_GAME_CORNER",
                "name": "Goldenrod Gachapon",
                "time": "",
                "method": "Gachapon",
                "minLevel": None,
                "maxLevel": None,
                "rate": None,
            }
            locations.setdefault(species, [])
            if location not in locations[species]:
                locations[species].append(location)


def add_odd_egg_species_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    """Add the uniformly random, one-time Route 34 Odd Egg pool."""
    try:
        text = strip_c_comments(read(ODD_EGG_C))
    except FileNotFoundError:
        return

    match = ODD_EGG_ARRAY_RE.search(text)
    if not match:
        return

    aliases = species_aliases()
    pool = []
    for raw_species in re.findall(r"\bSPECIES_[A-Z0-9_]+\b", match.group(1)):
        species = aliases.get(raw_species, raw_species)
        if species != "SPECIES_NONE" and species in by_species and species not in pool:
            pool.append(species)
    if not pool:
        return

    method = f"One-time Odd Egg (1/{len(pool)} chance)"
    for species in pool:
        location: SpeciesLocation = {
            "map": "MAP_ROUTE34",
            "name": "Route 34",
            "time": "",
            "method": method,
            "minLevel": 1,
            "maxLevel": 1,
            "rate": None,
        }
        locations.setdefault(species, [])
        if location not in locations[species]:
            locations[species].append(location)
