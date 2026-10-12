from __future__ import annotations

import json
from functools import cache
from typing import Mapping

from .constants import EXCLUDED_TRAINER_MAP_GROUPS, EXCLUDED_TRAINER_MAP_NAMES, EXCLUDED_TRAINER_MAP_PREFIXES
from .c_parser import format_identifier_name, normalize_token, read
from .paths import REGION_MAP_SECTIONS_JSON, REPO_ROOT


@cache
def region_map_section_names() -> dict[str, str]:
    try:
        data = json.loads(read(REGION_MAP_SECTIONS_JSON))
    except (FileNotFoundError, json.JSONDecodeError):
        return {}
    return {
        section["id"]: section["name"]
        for section in data.get("map_sections", [])
        if section.get("id") and section.get("name")
    }


@cache
def map_data_by_constant() -> dict[str, Mapping[str, object]]:
    maps: dict[str, Mapping[str, object]] = {}
    for map_json in sorted((REPO_ROOT / "data/maps").glob("*/map.json")):
        try:
            data = json.loads(read(map_json))
        except (FileNotFoundError, json.JSONDecodeError):
            continue
        if map_constant := data.get("id"):
            maps[str(map_constant)] = data
    return maps


def _renamed_region_map_name(map_data: Mapping[str, object], fallback: str) -> str:
    map_constant = str(map_data.get("id") or "")
    section_constant = str(map_data.get("region_map_section") or "")
    section_name = region_map_section_names().get(section_constant)
    if not map_constant or not section_name:
        return fallback

    map_key = map_constant.removeprefix("MAP_")
    section_key = section_constant.removeprefix("MAPSEC_")
    if normalize_token(map_key) == normalize_token(section_key):
        return section_name
    if map_key.startswith(f"{section_key}_"):
        suffix = format_identifier_name(map_key.removeprefix(f"{section_key}_"))
        return f"{section_name} {suffix}"
    if map_key.startswith(section_key):
        suffix_key = map_key.removeprefix(section_key).lstrip("_")
        if not suffix_key or suffix_key.isdigit():
            return section_name
        return f"{section_name} {format_identifier_name(suffix_key)}"
    if map_data.get("show_map_name"):
        return section_name
    return fallback


def _docs_map_name_override(map_data: Mapping[str, object]) -> str | None:
    map_constant = str(map_data.get("id") or "")
    if map_constant == "MAP_FOGGY_SHORE":
        return "Route 34"
    if map_constant == "MAP_ROUTE33SOUTH_UNDERWATER":
        return "South Johto Sea Underwater"
    if map_constant == "MAP_SOUTH_PASSAGE_SIDE":
        return "Southern Sidepath"
    if map_constant == "MAP_SOUTH_PASSAGE_END":
        return "Abandoned Lab"
    if map_constant == "MAP_METEOR_CAVE2":
        return "Meteor Island"
    victory_road_prefix = "MAP_VICTORY_ROAD_KANTO"
    if map_constant == victory_road_prefix:
        return "Victory Road"
    if map_constant.startswith(f"{victory_road_prefix}_"):
        floor = format_identifier_name(map_constant.removeprefix(f"{victory_road_prefix}_"))
        return f"Victory Road {floor}"
    return None


def map_display_name(map_data: Mapping[str, object], fallback_name: str) -> str:
    fallback = format_identifier_name(str(map_data.get("name") or fallback_name))
    if override := _docs_map_name_override(map_data):
        return override
    return _renamed_region_map_name(map_data, fallback)


def map_constant_display_name(map_constant: str) -> str:
    map_data = map_data_by_constant().get(map_constant, {})
    return map_display_name(map_data, format_identifier_name(map_constant))


def is_docs_excluded_map(map_name: str, group_name: str) -> bool:
    if group_name in EXCLUDED_TRAINER_MAP_GROUPS:
        return True
    if map_name in EXCLUDED_TRAINER_MAP_NAMES:
        return True
    return map_name.endswith("_Frlg") or map_name.startswith(EXCLUDED_TRAINER_MAP_PREFIXES)
