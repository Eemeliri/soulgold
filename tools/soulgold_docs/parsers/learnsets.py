"""Learnset parsing for level-up, TM/HM, tutor, and egg moves."""

from __future__ import annotations

import json
import re

from ..c_parser import parse_enum_constants, read
from ..models import LevelUpMove, Teachables, TMHMRow
from ..paths import MOVES_H, REPO_ROOT, SPECIAL_MOVESETS_JSON

_move_ids, _ = parse_enum_constants(MOVES_H, "")

_canonical_move_by_id: dict[int, str] = {}

for constant, move_id in _move_ids.items():
    if constant.startswith("MOVE_"):
        _canonical_move_by_id.setdefault(move_id, constant)


def canonical_move(move: str) -> str:
    move_id = _move_ids.get(move)
    if move_id is None:
        return move

    return _canonical_move_by_id.get(move_id, move)


def parse_level_up_learnsets() -> dict[str, list[LevelUpMove]]:
    learnsets: dict[str, list[LevelUpMove]] = {}
    learnset_dir = REPO_ROOT / "src/data/pokemon/level_up_learnsets"
    paths = sorted(learnset_dir.glob("gen_*.h"))
    legacy_config = read(REPO_ROOT / "include/config/pokemon.h")
    legacy_enabled = re.search(
        r"^#define\s+P_LEGACY_LVL_UP_LEARNSETS\s+(?:TRUE|1)\b",
        legacy_config,
        re.MULTILINE,
    )
    latest_level_ups = re.search(
        r"^#define\s+P_LVL_UP_LEARNSETS\s+(?:GEN_LATEST|GEN_9)\b",
        legacy_config,
        re.MULTILINE,
    )
    generated_legacy = learnset_dir / "generated_legacy_level_up_learnsets.h"
    if legacy_enabled and latest_level_ups and generated_legacy.exists():
        paths.append(generated_legacy)

    text = "\n".join(read(path) for path in paths)
    pattern = re.compile(r"static\s+const\s+struct\s+LevelUpMove\s+(s[A-Za-z0-9_]+LevelUpLearnset)\[\]\s*=\s*\{(.*?)\};", re.DOTALL)
    for symbol, body in pattern.findall(text):
        moves = []
        for level, move in re.findall(r"LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*(MOVE_[A-Z0-9_]+)\s*\)", body):
            moves.append({
                "level": int(level),
                "move": canonical_move(move),
            })
        learnsets[symbol] = moves
    return learnsets

def parse_teachable_learnsets(tmhm_moves: set[str]) -> dict[str, Teachables]:
    text = read(REPO_ROOT / "src/data/pokemon/teachable_learnsets.h")
    learnsets: dict[str, Teachables] = {}
    pattern = re.compile(r"static\s+const\s+u16\s+(s[A-Za-z0-9_]+TeachableLearnset)\[\]\s*=\s*\{(.*?)\};", re.DOTALL)
    for symbol, body in pattern.findall(text):
        moves = [
                    canonical_move(move)
                    for move in re.findall(r"\bMOVE_[A-Z0-9_]+\b", body)
                    if move != "MOVE_UNAVAILABLE"
                ]
        learnsets[symbol] = {
            "tmhm": [move for move in moves if move in tmhm_moves],
            "tutors": [move for move in moves if move not in tmhm_moves],
        }
    return learnsets


def parse_dedicated_tutors() -> dict[str, str]:
    data = json.loads(read(SPECIAL_MOVESETS_JSON))
    return {
        canonical_move(move): note
        for move, note in data.get("dedicatedTutors", {}).items()
    }


def parse_egg_move_learnsets() -> dict[str, list[str]]:
    text = read(REPO_ROOT / "src/data/pokemon/egg_moves.h")
    learnsets: dict[str, list[str]] = {}
    pattern = re.compile(r"static\s+const\s+u16\s+(s[A-Za-z0-9_]+EggMoveLearnset)\[\]\s*=\s*\{(.*?)\};", re.DOTALL)
    for symbol, body in pattern.findall(text):
        moves = [
                    canonical_move(move)
                    for move in re.findall(r"\bMOVE_[A-Z0-9_]+\b", body)
                    if move != "MOVE_UNAVAILABLE"
                ]
        learnsets[symbol] = moves
    return learnsets


def tmhm_move_constants(tmhm_rows: list[TMHMRow]) -> set[str]:
    return {row["move"] for row in tmhm_rows}
