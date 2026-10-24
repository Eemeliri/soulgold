"""Frontier sets helper"""

from __future__ import annotations

import re
import subprocess
from pathlib import Path

from ..c_parser import asset_stem, clean_constant_name, extract_braced_constants, extract_constant, split_designated_entries, strip_c_comments
from ..image_utils import copy_item_icon, parse_front_pic_sources, process_sprite
from ..paths import OUT_DIR, REPO_ROOT
from .trainers import front_pic_symbol_for_name

FRONTIER_FILES = (
    "src/data/battle_frontier/battle_frontier_mons.h",
    "src/data/battle_frontier/battle_frontier_mons_expansion.h",
)
MACRO_STATS = ("hp", "atk", "def", "spe", "spa", "spd")
DISPLAY_STATS = ("hp", "atk", "def", "spa", "spd", "spe")
SPEED_HOLD_EFFECTS = {
    "HOLD_EFFECT_CHOICE_SCARF": 1.5,
    "HOLD_EFFECT_IRON_BALL": 0.5,
    "HOLD_EFFECT_MACHO_BRACE": 0.5,
    "HOLD_EFFECT_POWER_ITEM": 0.5,
}


def resolve_alias(constant: str, aliases: dict[str, str]) -> str:
    seen = set()
    while constant in aliases:
        if constant in seen:
            raise ValueError(f"Cyclic Frontier constant alias: {constant}")
        seen.add(constant)
        constant = aliases[constant]
    return constant


def parse_spread(entry: str, field: str, macro: str) -> list[int]:
    match = re.search(rf"\.{field}\s*=\s*{macro}\(([^)]+)\)", entry)
    if not match:
        raise ValueError(f"Missing or unsupported {macro} spread")
    values = [int(value.strip()) for value in match.group(1).split(",")]
    if len(values) != 6:
        raise ValueError(f"Expected six values in {macro}")
    maximum = 31 if field == "iv" else 255
    if any(value < 0 or value > maximum for value in values):
        raise ValueError(f"Out-of-range {macro} spread")
    spread = dict(zip(MACRO_STATS, values))
    return [spread[stat] for stat in DISPLAY_STATS]


def parse_frontier_entries(sources: list[str]) -> list[dict]:
    sets = []
    seen = set()
    for source in sources:
        source = strip_c_comments(source)
        if re.search(r"^\s*#\s*(?:if|ifdef|ifndef)\b", source, re.MULTILINE):
            raise ValueError("Frontier table now needs preprocessing")
        entries = split_designated_entries(source)
        declared = re.findall(r"\[\s*(FRONTIER_MON_\w+)\s*\]\s*=", source)
        if len(declared) != len(entries):
            raise ValueError("Duplicate or unparsed Frontier set entries")
        for set_id, entry in entries.items():
            if set_id in seen:
                raise ValueError(f"Duplicate Frontier set: {set_id}")
            seen.add(set_id)
            species = extract_constant(entry, "species", "SPECIES_")
            moves = extract_braced_constants(entry, "moves", "MOVE_")
            items = extract_braced_constants(entry, "heldItem", "ITEM_")
            ability = extract_constant(entry, "ability", "ABILITY_")
            nature = extract_constant(entry, "nature", "NATURE_")
            if nature is None and re.search(r"\.nature\s*=\s*0\s*[,}]", entry):
                nature = "NATURE_HARDY"
            if not species or not moves or len(items) != 1 or not ability or not nature:
                raise ValueError(f"Incomplete or unsupported Frontier set: {set_id}")
            suffix = set_id.rsplit("_", 1)[1]
            sets.append({
                "setId": set_id,
                "setNumber": int(suffix) if suffix.isdigit() else None,
                "constant": species,
                "moves": [move for move in moves if move != "MOVE_NONE"],
                "itemConstant": items[0],
                "ability": ability,
                "nature": clean_constant_name(nature, "NATURE_"),
                "evs": parse_spread(entry, "ev", "TRAINER_PARTY_EVS"),
                "ivs": parse_spread(entry, "iv", "TRAINER_PARTY_IVS"),
            })
    if not sets:
        raise ValueError("Frontier set pool is empty")
    return sets


def build_frontier_payload(ref: str, species: list[dict], items: dict, item_icon_dir: Path) -> dict:
    def git(*args: str) -> str:
        result = subprocess.run(["git", *args], cwd=REPO_ROOT, text=True, capture_output=True)
        if result.returncode:
            raise ValueError(f"Cannot read Frontier source {ref!r}: {result.stderr.strip()}")
        return result.stdout

    commit = git("rev-parse", "--verify", "--end-of-options", f"{ref}^{{commit}}").strip()
    sets = parse_frontier_entries([git("show", f"{commit}:{path}") for path in FRONTIER_FILES])
    aliases = dict(re.findall(
        r"^\s*#define\s+(SPECIES_\w+)\s+(SPECIES_\w+)\s*$",
        strip_c_comments(git("show", f"{commit}:include/constants/species.h")), re.MULTILINE,
    ))
    move_aliases = dict(re.findall(
        r"\b(MOVE_\w+)\s*=\s*(MOVE_\w+)\s*,",
        strip_c_comments(git("show", f"{commit}:include/constants/moves.h")),
    ))
    species_by_constant = {mon["constant"]: mon for mon in species}
    front_sources = None
    species_table = {}
    item_table = {}
    for entry in sets:
        entry["moves"] = [resolve_alias(move, move_aliases) for move in entry["moves"]]
        constant = entry["constant"]
        if constant not in species_table:
            canonical = resolve_alias(constant, aliases)
            mon = species_by_constant.get(canonical)
            if mon:
                species_table[constant] = {
                    "name": mon.get("formLabel", mon["name"]),
                    "sprite": mon.get("sprite"),
                    "link": canonical,
                    "baseSpeed": mon["stats"]["spe"],
                }
            else:
                if front_sources is None:
                    front_sources = parse_front_pic_sources()
                symbol = front_pic_symbol_for_name(canonical, front_sources) or front_pic_symbol_for_name(constant, front_sources)
                # Silvally's memory forms share the same front sprite.
                if symbol is None and canonical.startswith("SPECIES_SILVALLY_"):
                    symbol = "gMonFrontPic_Silvally"
                source = front_sources.get(symbol)
                target = OUT_DIR / "sprites/pokemon" / f"{canonical.removeprefix('SPECIES_').lower()}.png"
                if source and not target.exists():
                    process_sprite(source, target)
                species_table[constant] = {
                    "name": clean_constant_name(constant, "SPECIES_"),
                    "sprite": str(target.relative_to(OUT_DIR)) if target.exists() else None,
                }
        item_constant = entry["itemConstant"]
        if item_constant == "ITEM_NONE":
            item_table[item_constant] = {"name": "No held item"}
        elif item_constant not in item_table:
            item = items.get(item_constant)
            if not item:
                raise ValueError(f"Unknown Frontier item: {item_constant}")
            existing = next((item_icon_dir / f"{stem}.png" for stem in (
                item_constant.removeprefix("ITEM_").lower(), asset_stem(item.get("iconName", "")),
            ) if stem and (item_icon_dir / f"{stem}.png").exists()), None)
            item_table[item_constant] = {
                "name": item["name"],
                "description": item.get("description", ""),
                "icon": str(existing.relative_to(OUT_DIR)) if existing else copy_item_icon(item, item_icon_dir),
            }
            if item["holdEffect"] in SPEED_HOLD_EFFECTS:
                item_table[item_constant]["speedModifier"] = SPEED_HOLD_EFFECTS[item["holdEffect"]]
    sets.sort(key=lambda entry: (species_table[entry["constant"]]["name"].casefold(), entry["constant"], entry["setNumber"] or 0))
    return {
        "source": {"ref": ref, "commit": commit, "files": list(FRONTIER_FILES)},
        "species": species_table,
        "items": item_table,
        "sets": [[
            entry["setId"], entry["constant"], entry["itemConstant"], entry["ability"],
            entry["nature"], entry["moves"], entry["evs"], entry["ivs"],
        ] for entry in sets],
    }
