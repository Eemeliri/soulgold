from __future__ import annotations

import json
import re
from collections import defaultdict
from typing import TypedDict

from ..c_parser import read, strip_c_comments
from ..map_names import map_display_name
from ..paths import HIDDEN_GROTTO_C, REPO_ROOT, SPECIES_H


class HiddenGrottoRow(TypedDict):
    map: str
    name: str
    level: int
    species: list[str]
    rareItem: str


def _species_aliases() -> dict[str, str]:
    aliases = dict(re.findall(
        r"^#define\s+(SPECIES_[A-Z0-9_]+)\s+(SPECIES_[A-Z0-9_]+)\s*$",
        read(SPECIES_H),
        re.MULTILINE,
    ))
    for alias in aliases:
        target = aliases[alias]
        seen = {alias}
        while target in aliases and target not in seen:
            seen.add(target)
            target = aliases[target]
        aliases[alias] = target
    return aliases


def _grotto_sources() -> dict[str, list[tuple[str, str]]]:
    sources: dict[str, list[tuple[str, str]]] = defaultdict(list)
    warp_re = re.compile(r"\bwarp\s+(MAP_HIDDEN_GROTTO_[A-Z0-9_]+)\b")
    for script in sorted((REPO_ROOT / "data/maps").glob("*/scripts.inc")):
        matches = set(warp_re.findall(strip_c_comments(read(script))))
        if not matches:
            continue
        try:
            map_data = json.loads(read(script.parent / "map.json"))
        except (FileNotFoundError, json.JSONDecodeError):
            map_data = {}
        map_constant = str(map_data.get("id") or "")
        name = map_display_name(map_data, script.parent.name)
        for grotto_map in matches:
            source = (map_constant, name)
            if source not in sources[grotto_map]:
                sources[grotto_map].append(source)
    return dict(sources)


def parse_hidden_grottos() -> list[HiddenGrottoRow]:
    text = strip_c_comments(read(HIDDEN_GROTTO_C))
    table_match = re.search(
        r"sHiddenGrottoData\s*\[[^]]+\]\s*=\s*\{(.*?)\n\};\s*\n\s*static const struct HiddenGrottoWeightedEntry sHiddenGrottoPokemonIndexes",
        text,
        re.DOTALL,
    )
    if not table_match:
        return []

    table = table_match.group(1)
    entry_re = re.compile(r"\[(HIDDEN_GROTTO_[A-Z0-9_]+)\]\s*=")
    matches = list(entry_re.finditer(table))
    sources = _grotto_sources()
    species_aliases = _species_aliases()
    seen_grotto_maps: set[str] = set()
    rows: list[HiddenGrottoRow] = []

    for index, match in enumerate(matches):
        end = matches[index + 1].start() if index + 1 < len(matches) else len(table)
        body = table[match.end():end]
        map_match = re.search(r"\.mapGroup\s*=\s*MAP_GROUP\((MAP_HIDDEN_GROTTO_[A-Z0-9_]+)\)", body)
        level_match = re.search(r"\.monLevel\s*=\s*(\d+)", body)
        item_match = re.search(r"\.rareItem\s*=\s*(ITEM_[A-Z0-9_]+)", body)
        if not map_match or not level_match or not item_match:
            continue

        grotto_map = map_match.group(1)
        if grotto_map in seen_grotto_maps:
            continue
        seen_grotto_maps.add(grotto_map)
        source_maps = sources.get(grotto_map, [])
        if not source_maps:
            continue

        species = [
            species_aliases.get(species, species)
            for species in re.findall(r"\{\s*(SPECIES_[A-Z0-9_]+)\s*,", body)
        ]
        for map_constant, name in source_maps:
            rows.append({
                "map": map_constant,
                "name": name,
                "level": int(level_match.group(1)),
                "species": species,
                "rareItem": item_match.group(1),
            })
    return rows
