#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

if __package__ in {None, ""}:
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from tools.soulgold_docs.image_utils import (
    copy_move_category_icons,
    copy_shiny_toggle_icon,
    copy_type_icons,
    parse_front_pic_sources,
    parse_shiny_palette_sources,
    parse_trainer_front_pic_sources,
)
from tools.soulgold_docs.parsers.abilities import build_ability_usage, parse_abilities
from tools.soulgold_docs.parsers.acquisition import attach_acquisition_paths
from tools.soulgold_docs.parsers.encounters import add_hidden_grotto_species_locations, build_species_locations, parse_wild_encounters
from tools.soulgold_docs.parsers.forms import add_rotom_form_change_locations
from tools.soulgold_docs.parsers.gifts import (
    add_gift_species_locations,
    add_master_gachapon_species_locations,
    add_odd_egg_species_locations,
    add_scripted_encounter_species_locations,
)
from tools.soulgold_docs.parsers.hidden_grottos import parse_hidden_grottos
from tools.soulgold_docs.parsers.trades import add_johto_trade_species_locations
from tools.soulgold_docs.parsers.evolutions import parse_evolutions, parse_mega_evolutions
from tools.soulgold_docs.parsers.items import (
    build_important_items,
    build_tms,
    parse_item_records,
    parse_tmhm_list,
    parse_tmhm_locations,
)
from tools.soulgold_docs.parsers.guides import parse_guides
from tools.soulgold_docs.parsers.learnsets import (
    parse_dedicated_tutors,
    parse_egg_move_learnsets,
    parse_level_up_learnsets,
    parse_teachable_learnsets,
    tmhm_move_constants,
)
from tools.soulgold_docs.parsers.moves import parse_moves
from tools.soulgold_docs.parsers.species import (
    apply_dex_form_visibility,
    attach_species_locations,
    build_species_lookup,
    enrich_species_rows,
    parse_species,
    visible_species_rows,
)
from tools.soulgold_docs.parsers.trainers import (
    parse_trainers,
    trainer_constants_for_docs_maps,
    trainer_locations_for_docs_maps,
)
from tools.soulgold_docs.site import build_docs_payload, prepare_output_tree, refresh_static_site, write_docs_payload


def build() -> None:
    moves = parse_moves()
    abilities = parse_abilities()
    species_data = parse_species()
    tmhm_rows = parse_tmhm_list()
    tmhm_moves = tmhm_move_constants(tmhm_rows)
    item_records = parse_item_records()
    tmhm_locations = parse_tmhm_locations()
    evolution_map = parse_evolutions(item_records)
    mega_evolutions = parse_mega_evolutions(item_records)
    species = apply_dex_form_visibility(species_data.rows, mega_evolutions)
    level_up = parse_level_up_learnsets()
    teachables = parse_teachable_learnsets(tmhm_moves)
    dedicated_tutors = parse_dedicated_tutors()
    egg_moves = parse_egg_move_learnsets()
    front_sources = parse_front_pic_sources()
    shiny_palette_sources = parse_shiny_palette_sources()
    trainer_front_sources = parse_trainer_front_pic_sources()
    output_paths = prepare_output_tree()
    type_icons = copy_type_icons()
    category_icons = copy_move_category_icons()
    shiny_toggle_icon = copy_shiny_toggle_icon()
    enriched_species = enrich_species_rows(
        species,
        level_up,
        teachables,
        egg_moves,
        evolution_map,
        front_sources,
        shiny_palette_sources,
        output_paths.sprite_dir,
        item_records,
    )
    encounters = parse_wild_encounters(species_data.by_constant)
    hidden_grottos = parse_hidden_grottos()
    species_locations = build_species_locations(encounters)
    add_hidden_grotto_species_locations(species_locations, hidden_grottos)
    add_gift_species_locations(species_locations, species_data.by_constant)
    add_scripted_encounter_species_locations(species_locations, species_data.by_constant)
    add_master_gachapon_species_locations(species_locations, species_data.by_constant)
    add_odd_egg_species_locations(species_locations, species_data.by_constant)
    add_johto_trade_species_locations(species_locations, species_data.by_constant)
    add_rotom_form_change_locations(species_locations, species_data.by_constant)
    located_species = attach_species_locations(enriched_species, species_locations)
    attach_acquisition_paths(located_species, item_records)
    visible_species = visible_species_rows(located_species)
    species_lookup = build_species_lookup(located_species)
    trainer_locations = trainer_locations_for_docs_maps()
    allowed_trainer_constants = trainer_constants_for_docs_maps(trainer_locations)
    trainers = parse_trainers(
        species_lookup,
        front_sources,
        trainer_front_sources,
        output_paths.sprite_dir,
        output_paths.trainer_sprite_dir,
        item_records,
        output_paths.item_icon_dir,
        allowed_trainer_constants,
        trainer_locations,
    )
    ability_usage = build_ability_usage(visible_species)
    tms = build_tms(tmhm_rows, moves, item_records, tmhm_locations)
    important_items = build_important_items(item_records, located_species, output_paths.item_icon_dir, hidden_grottos)
    guides = parse_guides()
    payload = build_docs_payload(
        visible_species,
        dedicated_tutors,
        moves,
        abilities,
        ability_usage,
        tms,
        important_items,
        encounters,
        trainers,
        type_icons,
        category_icons,
        shiny_toggle_icon,
        mega_evolutions,
        guides,
    )
    write_docs_payload(payload)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--static-only", action="store_true", help="Refresh website UI and existing routes without rebuilding game data")
    args = parser.parse_args()
    if args.static_only:
        refresh_static_site()
    else:
        build()
