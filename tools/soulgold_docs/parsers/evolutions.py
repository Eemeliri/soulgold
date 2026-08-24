"""Evolution and form-change parsing for the SoulGold docs generator."""

from __future__ import annotations

import re
from collections import defaultdict
from typing import Mapping

from ..c_parser import clean_constant_name, collect_strings, eval_int_expr, extract_balanced_call, extract_field, format_identifier_name, parse_define_constants, preprocess_source, read, split_designated_entries, split_top_level_braces, split_top_level_commas, strip_c_comments
from ..models import EvolutionRow, ItemRecord, MegaEvolutionRow
from ..paths import FORM_CHANGE_TABLES_H, REPO_ROOT, SPECIES_H
from .items import item_display_name
from .species import is_totem_species


def format_time_condition(value: str, inverted: bool = False) -> str:
    time_name = clean_constant_name(value, "TIME_")
    if not inverted:
        return time_name
    if value == "TIME_NIGHT":
        return "Day"
    return f"Not {time_name}"

def format_random_percent(condition: str, arg: str, modulo: int) -> str:
    value = eval_int_expr(arg)
    if value is None:
        return "Random Chance"
    if condition.endswith("_GT"):
        percent = max(0, modulo - 1 - value)
    elif condition.endswith("_EQ"):
        percent = 1
    else:
        percent = max(0, value)
    return f"Random {percent}%"

def format_evolution_condition(parts: list[str], item_names: Mapping[str, ItemRecord]) -> str:
    if not parts:
        return ""
    condition = parts[0]
    args = parts[1:]
    arg1 = args[0] if args else ""
    arg2 = args[1] if len(args) > 1 else ""
    arg3 = args[2] if len(args) > 2 else ""

    if condition == "IF_GENDER":
        return {"MON_MALE": "Male", "MON_FEMALE": "Female"}.get(arg1, clean_constant_name(arg1, "MON_"))
    if condition == "IF_TIME":
        return format_time_condition(arg1)
    if condition == "IF_NOT_TIME":
        return format_time_condition(arg1, inverted=True)
    if condition == "IF_MIN_FRIENDSHIP":
        return "High Friendship"
    if condition == "IF_ATK_GT_DEF":
        return "Atk > Def"
    if condition == "IF_ATK_EQ_DEF":
        return "Atk = Def"
    if condition == "IF_ATK_LT_DEF":
        return "Atk < Def"
    if condition == "IF_HOLD_ITEM":
        return f"Holding {item_display_name(arg1, item_names)}"
    if condition in {"IF_PID_UPPER_MODULO_10_GT", "IF_PID_UPPER_MODULO_10_EQ", "IF_PID_UPPER_MODULO_10_LT"}:
        return format_random_percent(condition, arg1, 10)
    if condition in {"IF_MIN_BEAUTY", "IF_MIN_COOLNESS", "IF_MIN_SMARTNESS", "IF_MIN_TOUGHNESS", "IF_MIN_CUTENESS"}:
        stat = clean_constant_name(condition, "IF_MIN_")
        return f"{stat} >= {arg1}" if arg1 else stat
    if condition == "IF_SPECIES_IN_PARTY":
        return f"{clean_constant_name(arg1, 'SPECIES_')} in Party"
    if condition == "IF_IN_MAP":
        return f"In {format_identifier_name(arg1)}"
    if condition == "IF_IN_MAPSEC":
        return f"In {format_identifier_name(arg1.removeprefix('MAPSEC_'))}"
    if condition == "IF_KNOWS_MOVE":
        return f"Knows {clean_constant_name(arg1, 'MOVE_')}"
    if condition == "IF_TRADE_PARTNER_SPECIES":
        return f"Traded for {clean_constant_name(arg1, 'SPECIES_')}"
    if condition == "IF_TYPE_IN_PARTY":
        return f"{clean_constant_name(arg1, 'TYPE_')}-type in Party"
    if condition == "IF_WEATHER":
        return clean_constant_name(arg1, "WEATHER_")
    if condition == "IF_KNOWS_MOVE_TYPE":
        return f"Knows {clean_constant_name(arg1, 'TYPE_')}-type Move"
    if condition == "IF_REGION":
        return f"In {clean_constant_name(arg1, 'REGION_')}"
    if condition == "IF_NOT_REGION":
        return f"Outside {clean_constant_name(arg1, 'REGION_')}"
    if condition == "IF_NATURE":
        return f"{clean_constant_name(arg1, 'NATURE_')} Nature"
    if condition == "IF_AMPED_NATURE":
        return "Amped Nature"
    if condition == "IF_LOW_KEY_NATURE":
        return "Low Key Nature"
    if condition == "IF_RECOIL_DAMAGE_GE":
        return f"{arg1} Recoil Damage"
    if condition == "IF_CURRENT_DAMAGE_GE":
        return f"{arg1} Current Damage"
    if condition == "IF_CRITICAL_HITS_GE":
        return f"{arg1} Critical Hits"
    if condition == "IF_USED_MOVE_X_TIMES":
        return f"Use {clean_constant_name(arg1, 'MOVE_')} {arg2} Times"
    if condition == "IF_DEFEAT_X_WITH_ITEMS":
        return f"Defeat {arg3} {clean_constant_name(arg1, 'SPECIES_')} holding {item_display_name(arg2, item_names)}"
    if condition in {"IF_PID_MODULO_100_GT", "IF_PID_MODULO_100_EQ", "IF_PID_MODULO_100_LT"}:
        return format_random_percent(condition, arg1, 100)
    if condition == "IF_MIN_OVERWORLD_STEPS":
        return f"{arg1} Steps"
    if condition == "IF_BAG_ITEM_COUNT":
        return f"{arg2} {item_display_name(arg1, item_names)} in Bag"
    return clean_constant_name(condition, "IF_")

def format_evolution_conditions(conditions_expr: str, item_names: Mapping[str, ItemRecord]) -> list[str]:
    if not conditions_expr.startswith("CONDITIONS"):
        return []
    body = extract_balanced_call(conditions_expr, 0)
    if body is None:
        return []
    labels = []
    for chunk in split_top_level_braces(body):
        label = format_evolution_condition(split_top_level_commas(chunk), item_names)
        if label:
            labels.append(label)
    return labels

def format_evolution_method(method: str, param: str, item_names: Mapping[str, ItemRecord], conditions: list[str] | None = None) -> str:
    conditions = conditions or []
    if method in {"EVO_LEVEL", "EVO_LEVEL_BATTLE_ONLY"}:
        label = f"Level {param}" if param and param != "0" else "Level Up"
        if method == "EVO_LEVEL_BATTLE_ONLY":
            conditions = ["Battle Only", *conditions]
    elif method == "EVO_ITEM":
        label = f"By Using Specific Item ({item_display_name(param, item_names)})"
    elif method == "EVO_TRADE":
        label = "Trade"
    elif method == "EVO_FRIENDSHIP":
        label = "Friendship"
    elif method == "EVO_MOVE":
        label = f"Knowing {clean_constant_name(param, 'MOVE_')}"
    elif method == "EVO_NONE":
        label = "Special"
    else:
        label = clean_constant_name(method, "EVO_")
    if conditions:
        label = f"{label} ({', '.join(conditions)})"
    return label

def preprocess_evolution_entries() -> dict[str, str]:
    """Expand active species macros while retaining symbolic evolution arguments."""
    species_info_path = REPO_ROOT / "src/data/pokemon/species_info.h"
    source = read(species_info_path)
    source, replacement_count = re.subn(
        r"^#define EVOLUTION\(\.\.\.\).*$",
        r"#define EVOLUTION(...) DOC_EVOLUTION(#__VA_ARGS__)",
        source,
        count=1,
        flags=re.MULTILINE,
    )
    if replacement_count != 1:
        raise RuntimeError(f"could not instrument EVOLUTION macro in {species_info_path}")
    text = preprocess_source(
        f'#include "global.h"\n{source}',
        "src/data/pokemon",
    )
    return split_designated_entries(text)

def parse_evolutions(item_names: Mapping[str, ItemRecord]) -> dict[str, list[EvolutionRow]]:
    evolutions: dict[str, list[EvolutionRow]] = defaultdict(list)
    _, id_to_species = parse_define_constants(SPECIES_H, "SPECIES_")
    for key, entry in preprocess_evolution_entries().items():
        source = id_to_species.get(int(key)) if key.isdigit() else None
        evolution_expr = extract_field(entry, "evolutions")
        if source is None or evolution_expr is None:
            continue
        body = extract_balanced_call(evolution_expr, 0)
        if body is None:
            continue
        for chunk in split_top_level_braces(collect_strings(body)):
            parts = split_top_level_commas(chunk)
            if len(parts) < 3:
                continue
            method, param, target = parts[0], parts[1], parts[2]
            conditions = format_evolution_conditions(parts[3], item_names) if len(parts) > 3 else []
            if method == "EVOLUTIONS_END" or not target.startswith("SPECIES_"):
                continue
            if method == "EVO_TRADE":
                continue
            if is_totem_species(source) or is_totem_species(target):
                continue
            evolutions[source].append({
                "method": method,
                "param": param,
                "target": target,
                "conditions": conditions,
                "label": format_evolution_method(method, param, item_names, conditions),
                "itemName": item_display_name(param, item_names) if method == "EVO_ITEM" else "",
            })
    return dict(evolutions)

def parse_mega_evolutions(item_names: Mapping[str, ItemRecord]) -> list[MegaEvolutionRow]:
    text = strip_c_comments(read(FORM_CHANGE_TABLES_H))
    table_re = re.compile(
        r"static\s+const\s+struct\s+FormChange\s+s[A-Za-z0-9_]+FormChangeTable\[\]\s*=\s*\{(.*?)\};",
        re.DOTALL,
    )
    rows: list[MegaEvolutionRow] = []
    seen: set[tuple[str, str, str]] = set()
    for body in table_re.findall(text):
        source_match = re.search(r"\{\s*FORM_CHANGE_(?:FAINT|END_BATTLE)\s*,\s*(SPECIES_[A-Z0-9_]+)", body)
        if not source_match:
            continue
        source = source_match.group(1)
        for target, item in re.findall(
            r"\{\s*FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM\s*,\s*(SPECIES_[A-Z0-9_]+)\s*,\s*(ITEM_[A-Z0-9_]+)",
            body,
        ):
            key = (source, target, item)
            if key in seen:
                continue
            seen.add(key)
            item_name = item_names.get(item, {}).get("name") or clean_constant_name(item, "ITEM_")
            rows.append({
                "source": source,
                "target": target,
                "item": item,
                "itemName": item_name,
                "label": f"Mega Evolution ({item_name})",
            })
        for target, move in re.findall(
            r"\{\s*FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE\s*,\s*(SPECIES_[A-Z0-9_]+)\s*,\s*(MOVE_[A-Z0-9_]+)",
            body,
        ):
            key = (source, target, move)
            if key in seen:
                continue
            seen.add(key)
            rows.append({
                "source": source,
                "target": target,
                "item": "",
                "itemName": "",
                "label": f"Knows move {clean_constant_name(move, 'MOVE_')}",
            })
        for target, item in re.findall(
            r"\{\s*FORM_CHANGE_BEGIN_BATTLE\s*,\s*(SPECIES_[A-Z0-9_]+)\s*,\s*(ITEM_[A-Z0-9_]+)",
            body,
        ):
            key = (source, target, item)
            if key in seen:
                continue
            seen.add(key)
            item_name = item_names.get(item, {}).get("name") or clean_constant_name(item, "ITEM_")
            rows.append({
                "source": source,
                "target": target,
                "item": item,
                "itemName": item_name,
                "label": f"Holding {item_name} in Battle",
            })
    return rows
