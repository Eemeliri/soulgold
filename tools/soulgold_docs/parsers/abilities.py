from __future__ import annotations

import re
from collections import defaultdict

from ..c_parser import clean_constant_name, collect_strings, extract_field, extract_number, parse_shared_strings, preprocess, read, split_designated_entries
from ..models import AbilityUsage, NamedRecord, SpeciesRow
from ..paths import REPO_ROOT


def parse_abilities() -> dict[str, NamedRecord]:
    include_path = "data/abilities.h"
    key_prefix = "ABILITY_"
    name_prefix = "ABILITY_"
    text = preprocess(include_path)
    source_path = REPO_ROOT / include_path
    if not source_path.exists():
        source_path = REPO_ROOT / "src" / include_path
    source_text = read(source_path)
    shared_strings = parse_shared_strings(source_text)
    entries = split_designated_entries(text)
    rows: dict[str, NamedRecord] = {}

    for key, entry in entries.items():
        if not key.startswith(key_prefix):
            continue
        name_expr = extract_field(entry, "name") or ""
        desc_expr = extract_field(entry, "longDescription") or ""
        name = collect_strings(name_expr) or clean_constant_name(key, name_prefix)
        description = collect_strings(desc_expr)
        if not description and desc_expr in shared_strings:
            description = shared_strings[desc_expr]
        rows[key] = {"constant": key, "name": name, "description": description}
        for field_name in ("power", "accuracy", "pp", "priority"):
            rows[key][field_name] = extract_number(entry, field_name)
        for field_name in ("type", "category"):
            expr = extract_field(entry, field_name) or ""
            const = re.search(r"\b[A-Z][A-Z0-9_]+\b", expr)
            rows[key][field_name] = const.group(0) if const else ""
    return rows


def build_ability_usage(visible_species: list[SpeciesRow]) -> AbilityUsage:
    ability_usage: AbilityUsage = defaultdict(lambda: {"base": [], "innate": []})
    for row in visible_species:
        mini = {"species": row.constant, "name": row.name, "dex": row.display_dex, "sprite": row.sprite}
        for ability in dict.fromkeys(row.abilities):
            ability_usage[ability]["base"].append(mini)
        for ability in dict.fromkeys(row.innates):
            ability_usage[ability]["innate"].append(mini)
    return ability_usage
