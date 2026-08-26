"""Species parsing and enrichment for the SoulGold docs generator."""

from __future__ import annotations

import re
from pathlib import Path

from ..constants import DEX_HIDDEN_COLOR_FORMS, DEX_HIDDEN_PREFIXES, DEX_HIDDEN_SPECIES, EV_YIELD_FIELDS, FOSSIL_POKEMON_SPECIES, GMAX_DMAX_FORM_RE, SPECIES_NAME_OVERRIDES, STAT_FIELDS
from ..c_parser import clean_constant_name, collect_strings, extract_braced_constants, extract_constant, extract_field, extract_number, normalize_token, parse_define_aliases, parse_define_constants, parse_enum_constants, preprocess, preprocess_source, read, split_designated_entries
from ..image_utils import process_sprite, shiny_palette_symbol
from ..models import EvolutionRow, ItemRecord, LevelUpMove, MegaEvolutionRow, SpeciesLocation, SpeciesParseResult, SpeciesRow, Teachables
from ..paths import OUT_DIR, POKEDEX_H, SPECIES_H, TYPES_H
from .items import item_display_name


def is_dex_visible_species(constant: str) -> bool:
    if "_TOTEM" in constant:
        return False
    if constant in DEX_HIDDEN_SPECIES or constant in DEX_HIDDEN_COLOR_FORMS:
        return False
    if any(constant.startswith(prefix) for prefix in DEX_HIDDEN_PREFIXES):
        return constant == "SPECIES_ARCEUS_NORMAL"
    return True

def is_totem_species(constant: str) -> bool:
    return "_TOTEM" in constant

def is_gmax_dmax_form(constant: str) -> bool:
    return bool(GMAX_DMAX_FORM_RE.search(constant))

def johto_dex_species_order() -> list[str]:
    text = preprocess_source(
        '#include "global.h"\n'
        '#define JOHTO_DEX(name) DOCS_JOHTO_DEX_##name\n'
        '#include "constants/johto_dex_order.h"\n'
    )
    return [
        f"SPECIES_{name}"
        for name in re.findall(r"\bDOCS_JOHTO_DEX_([A-Z0-9_]+)\b", text)
    ]

def refresh_display_dex(rows: list[SpeciesRow]) -> None:
    aliases = parse_define_aliases(SPECIES_H, "SPECIES_")
    by_constant = {row.constant: row for row in rows}
    display_by_nat_dex: dict[int, int] = {}
    for display_dex, ordered_constant in enumerate(johto_dex_species_order(), start=1):
        constant = aliases.get(ordered_constant, ordered_constant)
        ordered_row = by_constant.get(constant)
        if ordered_row and ordered_row.nat_dex:
            display_by_nat_dex.setdefault(ordered_row.nat_dex, display_dex)
    for row in rows:
        row.display_dex = display_by_nat_dex.get(row.nat_dex, 0)

def apply_dex_form_visibility(rows: list[SpeciesRow], mega_evolutions: list[MegaEvolutionRow]) -> list[SpeciesRow]:
    mega_targets = {evolution["target"] for evolution in mega_evolutions}
    for row in rows:
        if is_gmax_dmax_form(row.constant) and row.constant not in mega_targets:
            row.dex_visible = False
    refresh_display_dex(rows)
    return rows

def parse_species() -> SpeciesParseResult:
    species_to_id, id_to_species = parse_define_constants(SPECIES_H, "SPECIES_")
    nat_to_id, _ = parse_enum_constants(POKEDEX_H, "NATIONAL_DEX_")
    text = preprocess("data/pokemon/species_info.h")
    entries = split_designated_entries(text)
    _, egg_group_by_id = parse_define_constants(TYPES_H, "EGG_GROUP_")
    rows: list[SpeciesRow] = []
    by_constant: dict[str, SpeciesRow] = {}

    for key, entry in entries.items():
        if not key.isdigit():
            continue
        species_id = int(key)
        constant = id_to_species.get(species_id)
        if not constant or constant in {"SPECIES_NONE", "SPECIES_EGG"}:
            continue
        name = SPECIES_NAME_OVERRIDES.get(
            constant,
            collect_strings(extract_field(entry, "speciesName") or "") or clean_constant_name(constant, "SPECIES_"),
        )
        nat_expr = extract_field(entry, "natDexNum") or "NATIONAL_DEX_NONE"
        nat_const = re.search(r"\bNATIONAL_DEX_[A-Z0-9_]+\b", nat_expr)
        species_nat_const = ""
        if nat_const:
            species_nat_const = nat_const.group(0).replace("NATIONAL_DEX_", "SPECIES_")
            nat_dex = species_to_id.get(species_nat_const, nat_to_id.get(nat_const.group(0), 0))
        else:
            nat_dex = extract_number(entry, "natDexNum")
        stats = {short: extract_number(entry, field_name) for field_name, short in STAT_FIELDS.items()}
        ev_yield = {
            short: value
            for field_name, short in EV_YIELD_FIELDS.items()
            if (value := extract_number(entry, field_name))
        }
        egg_groups = []
        egg_group_expr = extract_field(entry, "eggGroups") or ""
        for raw_group in re.findall(r"\b\d+\b", egg_group_expr):
            egg_group = egg_group_by_id.get(int(raw_group))
            if egg_group and egg_group != "EGG_GROUP_NONE" and egg_group not in egg_groups:
                egg_groups.append(egg_group)
        categories = []
        if extract_number(entry, "isRestrictedLegendary") or extract_number(entry, "isSubLegendary"):
            categories.append("legendary")
        if any(
            extract_number(entry, field)
            for field in ("isAlolanForm", "isGalarianForm", "isHisuianForm", "isPaldeanForm")
        ):
            categories.append("regional")
        if extract_number(entry, "isParadox"):
            categories.append("paradox")
        if extract_number(entry, "isMythical"):
            categories.append("mythical")
        if extract_number(entry, "isMegaEvolution"):
            categories.append("mega")
        if species_nat_const in FOSSIL_POKEMON_SPECIES:
            categories.append("fossil")
        types = extract_braced_constants(entry, "types", "TYPE_") or ["TYPE_NORMAL"]
        if len(types) == 1:
            types.append(types[0])
        ability_slots = extract_braced_constants(entry, "abilities", "ABILITY_")
        regular_abilities = [a for a in ability_slots[:2] if a != "ABILITY_NONE"]
        hidden_abilities = [a for a in ability_slots[2:3] if a != "ABILITY_NONE"]
        abilities = [a for a in ability_slots if a != "ABILITY_NONE"]
        innates = [a for a in extract_braced_constants(entry, "innates", "ABILITY_") if a != "ABILITY_NONE"]
        level_expr = extract_field(entry, "levelUpLearnset") or ""
        teach_expr = extract_field(entry, "teachableLearnset") or ""
        egg_expr = extract_field(entry, "eggMoveLearnset") or ""
        front_expr = extract_field(entry, "frontPic") or ""
        shiny_palette_expr = extract_field(entry, "shinyPalette") or ""
        level_symbol = re.search(r"\bs[A-Za-z0-9_]+LevelUpLearnset\b", level_expr)
        teach_symbol = re.search(r"\bs[A-Za-z0-9_]+TeachableLearnset\b", teach_expr)
        egg_symbol = re.search(r"\bs[A-Za-z0-9_]+EggMoveLearnset\b", egg_expr)
        front_symbol = re.search(r"\bgMonFrontPic_[A-Za-z0-9_]+\b", front_expr)
        shiny_palette = re.search(r"\bgMonShinyPalette_[A-Za-z0-9_]+\b", shiny_palette_expr)
        held_items = []
        seen_held_items = set()
        for field_name, rarity in (("itemCommon", "common"), ("itemRare", "rare")):
            item = extract_constant(entry, field_name, "ITEM_")
            if item and item != "ITEM_NONE" and item not in seen_held_items:
                held_items.append({"constant": item, "rarity": rarity})
                seen_held_items.add(item)
        row = SpeciesRow(
            id=species_id,
            constant=constant,
            name=name,
            nat_dex=nat_dex,
            display_dex=0,
            dex_visible=is_dex_visible_species(constant),
            types=types[:2],
            stats=stats,
            ev_yield=ev_yield,
            egg_groups=egg_groups,
            categories=categories,
            abilities=abilities,
            regular_abilities=regular_abilities,
            hidden_abilities=hidden_abilities,
            innates=innates,
            level_up_symbol=level_symbol.group(0) if level_symbol else None,
            teachable_symbol=teach_symbol.group(0) if teach_symbol else None,
            egg_move_symbol=egg_symbol.group(0) if egg_symbol else None,
            front_pic_symbol=front_symbol.group(0) if front_symbol else None,
            shiny_palette_symbol=shiny_palette.group(0) if shiny_palette else None,
            held_items=held_items,
        )
        rows.append(row)
        by_constant[constant] = row

    rows.sort(key=lambda row: (row.nat_dex if row.nat_dex else 99999, row.id))
    refresh_display_dex(rows)
    return SpeciesParseResult(rows, by_constant)

def build_species_lookup(species: list[SpeciesRow]) -> dict[str, SpeciesRow]:
    lookup: dict[str, SpeciesRow] = {}
    for row in species:
        names = {
            row.name,
            clean_constant_name(row.constant, "SPECIES_"),
            row.constant.removeprefix("SPECIES_"),
        }
        for name in names:
            lookup.setdefault(normalize_token(name), row)
    return lookup

def species_for_trainer_mon(name: str, species_lookup: dict[str, SpeciesRow]) -> SpeciesRow | None:
    clean_name = re.sub(r"\s*\([^)]*\)\s*", " ", name)
    clean_name = clean_name.split("@", 1)[0].strip()
    return species_lookup.get(normalize_token(clean_name))


def egg_move_symbol_for_family(row: SpeciesRow, by_constant: dict[str, SpeciesRow], parent_map: dict[str, str]) -> str | None:
    lineage: list[SpeciesRow] = []
    current: SpeciesRow | None = row
    seen: set[str] = set()
    while current and current.constant not in seen:
        lineage.append(current)
        seen.add(current.constant)
        current = by_constant.get(parent_map.get(current.constant, ""))

    # Prefer the species' own learnset, then fall back to its nearest
    # pre-evolution. Baby Pokemon can have a different egg-move table from
    # the next stage in their family (for example, Azurill and Marill).
    for family_row in lineage:
        if family_row.egg_move_symbol:
            return family_row.egg_move_symbol
    return None


def enrich_species_rows(
    species: list[SpeciesRow],
    level_up: dict[str, list[LevelUpMove]],
    teachables: dict[str, Teachables],
    egg_moves: dict[str, list[str]],
    evolution_map: dict[str, list[EvolutionRow]],
    front_sources: dict[str, Path],
    shiny_palette_sources: dict[str, Path],
    sprite_dir: Path,
    item_records: dict[str, ItemRecord],
) -> list[SpeciesRow]:
    by_constant = {row.constant: row for row in species}
    parent_map = {
        evolution["target"]: source
        for source, evolutions in evolution_map.items()
        for evolution in evolutions
        if evolution["target"] in by_constant
    }

    for row in species:
        for held_item in row.held_items:
            held_item["name"] = item_display_name(held_item["constant"], item_records)
        if row.level_up_symbol:
            row.level_up = level_up.get(row.level_up_symbol, [])
        if row.teachable_symbol:
            row.tmhm = teachables.get(row.teachable_symbol, {}).get("tmhm", [])
            row.tutors = teachables.get(row.teachable_symbol, {}).get("tutors", [])
        family_egg_move_symbol = egg_move_symbol_for_family(row, by_constant, parent_map)
        if family_egg_move_symbol:
            row.egg_moves = egg_moves.get(family_egg_move_symbol, [])
        row.evolutions = evolution_map.get(row.constant, [])
        if row.front_pic_symbol and row.front_pic_symbol in front_sources:
            sprite_path = sprite_dir / f"{row.constant.removeprefix('SPECIES_').lower()}.png"
            process_sprite(front_sources[row.front_pic_symbol], sprite_path)
            row.sprite = str(sprite_path.relative_to(OUT_DIR))
            palette_source = shiny_palette_sources.get(
                row.shiny_palette_symbol or shiny_palette_symbol(row.front_pic_symbol)
            )
            if palette_source:
                shiny_sprite_path = sprite_dir / f"{row.constant.removeprefix('SPECIES_').lower()}_shiny.png"
                process_sprite(front_sources[row.front_pic_symbol], shiny_sprite_path, palette_source)
                row.shiny_sprite = str(shiny_sprite_path.relative_to(OUT_DIR))
    return species


def attach_species_locations(
    species: list[SpeciesRow],
    species_locations: dict[str, list[SpeciesLocation]],
) -> list[SpeciesRow]:
    for row in species:
        row.locations = species_locations.get(row.constant, [])
    return species


def visible_species_rows(species: list[SpeciesRow]) -> list[SpeciesRow]:
    return [row for row in species if row.dex_visible]
