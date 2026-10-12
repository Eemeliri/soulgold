from __future__ import annotations

import re

from ..c_parser import clean_constant_name, collect_strings, extract_field, extract_number, parse_enum_constants, parse_shared_strings, preprocess, read, split_designated_entries
from ..models import NamedRecord
from ..paths import MOVES_H, REPO_ROOT


MOVE_ABILITY_BOOSTS = (
    ("punchingMove", "ABILITY_IRON_FIST", 20, False),
    ("kickingMove", "ABILITY_STEEL_FEET", 20, False),
    ("bitingMove", "ABILITY_STRONG_JAW", 50, False),
    ("pulseMove", "ABILITY_MEGA_LAUNCHER", 50, False),
    ("soundMove", "ABILITY_PUNK_ROCK", 30, True),
    ("slicingMove", "ABILITY_SHARPNESS", 50, False),
)


def parse_moves() -> dict[str, NamedRecord]:
    include_path = "data/moves_info.h"
    key_prefix = "MOVE_"
    name_prefix = "MOVE_"
    text = preprocess(include_path)
    source_path = REPO_ROOT / include_path
    if not source_path.exists():
        source_path = REPO_ROOT / "src" / include_path
    source_text = read(source_path)
    shared_strings = parse_shared_strings(source_text)
    entries = split_designated_entries(text)
    move_ids, _ = parse_enum_constants(MOVES_H, "")
    hidden_ranges = (
        (move_ids.get("FIRST_Z_MOVE"), move_ids.get("LAST_Z_MOVE")),
        (move_ids.get("FIRST_MAX_MOVE"), move_ids.get("LAST_MAX_MOVE")),
    )
    rows: dict[str, NamedRecord] = {}

    for key, entry in entries.items():
        if not key.startswith(key_prefix):
            continue
        move_id = move_ids.get(key, len(rows))
        if any(
            first is not None and last is not None and first <= move_id <= last
            for first, last in hidden_ranges
        ):
            continue
        name_expr = extract_field(entry, "name") or ""
        desc_expr = extract_field(entry, "description") or ""
        name = collect_strings(name_expr) or clean_constant_name(key, name_prefix)
        description = collect_strings(desc_expr)
        if not description and desc_expr in shared_strings:
            description = shared_strings[desc_expr]
        rows[key] = {
            "id": move_id,
            "constant": key,
            "name": name,
            "description": description,
        }
        for field_name in ("power", "accuracy", "pp", "priority"):
            rows[key][field_name] = extract_number(entry, field_name)
        for field_name in ("type", "category"):
            expr = extract_field(entry, field_name) or ""
            const = re.search(r"\b[A-Z][A-Z0-9_]+\b", expr)
            rows[key][field_name] = const.group(0) if const else ""
        is_damaging = (
            rows[key].get("category") != "DAMAGE_CATEGORY_STATUS"
            and int(rows[key].get("power", 0)) > 0
        )
        rows[key]["abilityBoosts"] = [
            {"ability": ability, "percent": percent}
            for field_name, ability, percent, damaging_only in MOVE_ABILITY_BOOSTS
            if extract_number(entry, field_name) and (is_damaging or not damaging_only)
        ]
    return rows
