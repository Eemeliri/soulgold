#!/usr/bin/env python3

"""Generate or preview latest-generation level-up learnsets with legacy moves.

The current learnset is authoritative. A legacy move is added only when its
canonical move ID is completely absent from the current learnset. Current
levels are never changed. Legacy evolution/level-1 rows are preserved, while
later legacy rows can be automatically spread between current level anchors.

The JSON configuration supports global and per-species exclusions, explicit
level overrides, and automatic spacing controls. Explicit overrides are
applied after automatic spacing.

Examples:
    python3 tools/learnset_helpers/preview_legacy_levelups.py Blaziken Snorlax
    python3 tools/learnset_helpers/preview_legacy_levelups.py --top 10
    python3 tools/learnset_helpers/preview_legacy_levelups.py --merged Magearna
    python3 tools/learnset_helpers/preview_legacy_levelups.py --output output.h
"""

from __future__ import annotations

import argparse
import difflib
import json
import re
from dataclasses import dataclass, replace
from pathlib import Path
from typing import Any


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_CURRENT = REPO_ROOT / "src/data/pokemon/level_up_learnsets/gen_9.h"
DEFAULT_LEGACY = REPO_ROOT / "src/data/pokemon/level_up_learnsets/gen_7.h"
DEFAULT_CONFIG = REPO_ROOT / "src/data/pokemon/legacy_level_up_config.json"
MOVES_HEADER = REPO_ROOT / "include/constants/moves.h"
POKEMON_CONSTANTS = REPO_ROOT / "include/constants/pokemon.h"
DEFAULT_SPECIES = ("Blaziken", "Snorlax", "MrMime", "Sceptile", "Magearna")

LEARNSET_PATTERN = re.compile(
    r"static\s+const\s+struct\s+LevelUpMove\s+"
    r"(?P<symbol>s[A-Za-z0-9_]+LevelUpLearnset)\[\]\s*=\s*\{"
    r"(?P<body>.*?)"
    r"\n\};",
    re.DOTALL,
)
MOVE_PATTERN = re.compile(
    r"LEVEL_UP_MOVE\(\s*(?P<level>\d+)\s*,\s*(?P<move>MOVE_[A-Z0-9_]+)\s*\)"
)
MOVE_ALIAS_PATTERN = re.compile(
    r"^\s*(?P<alias>MOVE_[A-Z0-9_]+)\s*=\s*(?P<target>MOVE_[A-Z0-9_]+)\s*,",
    re.MULTILINE,
)
MAX_LEVEL_UP_MOVES_PATTERN = re.compile(r"^#define\s+MAX_LEVEL_UP_MOVES\s+(\d+)", re.MULTILINE)


@dataclass(frozen=True)
class LevelUpMove:
    level: int
    move: str
    order: int
    source: str
    original_level: int


@dataclass(frozen=True)
class MergeConfig:
    minimum_spacing_level: int
    minimum_spacing: int
    globally_excluded_moves: frozenset[str]
    species: dict[str, dict[str, Any]]


def parse_learnsets(path: Path, source: str) -> dict[str, list[LevelUpMove]]:
    text = path.read_text(encoding="utf-8")
    learnsets: dict[str, list[LevelUpMove]] = {}

    for match in LEARNSET_PATTERN.finditer(text):
        rows = [
            LevelUpMove(
                level=int(move.group("level")),
                move=move.group("move"),
                order=order,
                source=source,
                original_level=int(move.group("level")),
            )
            for order, move in enumerate(MOVE_PATTERN.finditer(match.group("body")))
        ]
        learnsets[match.group("symbol")] = rows

    if not learnsets:
        raise ValueError(f"No level-up learnsets found in {path}")

    return learnsets


def parse_move_aliases(path: Path) -> dict[str, str]:
    return {
        match.group("alias"): match.group("target")
        for match in MOVE_ALIAS_PATTERN.finditer(path.read_text(encoding="utf-8"))
    }


def canonical_move(move: str, aliases: dict[str, str]) -> str:
    seen: set[str] = set()
    while move in aliases and move not in seen:
        seen.add(move)
        move = aliases[move]
    return move


def load_config(path: Path, aliases: dict[str, str]) -> MergeConfig:
    data = json.loads(path.read_text(encoding="utf-8"))
    spacing = data.get("automaticSpacing", {})
    minimum_level = spacing.get("minimumLevel", 40)
    minimum_spacing = spacing.get("minimumSpacing", 3)

    if not isinstance(minimum_level, int) or not 0 <= minimum_level <= 100:
        raise ValueError("automaticSpacing.minimumLevel must be an integer from 0 to 100")
    if not isinstance(minimum_spacing, int) or minimum_spacing < 0:
        raise ValueError("automaticSpacing.minimumSpacing must be a non-negative integer")

    global_exclusions = data.get("excludedMoves", [])
    if not isinstance(global_exclusions, list) or not all(
        isinstance(move, str) for move in global_exclusions
    ):
        raise ValueError("excludedMoves must be a list of MOVE_* strings")

    species = data.get("species", {})
    if not isinstance(species, dict):
        raise ValueError("species must be an object")

    normalized_species: dict[str, dict[str, Any]] = {}
    for name, settings in species.items():
        if not isinstance(settings, dict):
            raise ValueError(f"species.{name} must be an object")
        unknown_settings = set(settings) - {"excludedMoves", "levelOverrides"}
        if unknown_settings:
            raise ValueError(
                f"Unknown settings for species.{name}: {', '.join(sorted(unknown_settings))}"
            )
        exclusions = settings.get("excludedMoves", [])
        if not isinstance(exclusions, list) or not all(
            isinstance(move, str) for move in exclusions
        ):
            raise ValueError(f"species.{name}.excludedMoves must be a list of MOVE_* strings")
        overrides = settings.get("levelOverrides", {})
        if not isinstance(overrides, dict):
            raise ValueError(f"species.{name}.levelOverrides must be an object")
        normalized_species[normalized(name)] = settings

    return MergeConfig(
        minimum_spacing_level=minimum_level,
        minimum_spacing=minimum_spacing,
        globally_excluded_moves=frozenset(
            canonical_move(move, aliases) for move in global_exclusions
        ),
        species=normalized_species,
    )


def short_name(symbol: str) -> str:
    return symbol.removeprefix("s").removesuffix("LevelUpLearnset")


def normalized(value: str) -> str:
    return re.sub(r"[^a-z0-9]", "", value.lower())


def species_aliases(symbols: set[str]) -> dict[str, str]:
    aliases: dict[str, str] = {}
    for symbol in symbols:
        name = short_name(symbol)
        aliases[normalized(symbol)] = symbol
        aliases[normalized(name)] = symbol
        aliases[normalized(f"SPECIES_{name}")] = symbol
    return aliases


def resolve_species(selector: str, aliases: dict[str, str]) -> str:
    key = normalized(selector)
    if key in aliases:
        return aliases[key]

    suggestions = difflib.get_close_matches(key, aliases, n=3, cutoff=0.55)
    message = f"Unknown species/learnset {selector!r}"
    if suggestions:
        names = ", ".join(short_name(aliases[item]) for item in suggestions)
        message += f". Did you mean: {names}?"
    raise ValueError(message)


def species_settings(symbol: str, config: MergeConfig) -> dict[str, Any]:
    return config.species.get(normalized(short_name(symbol)), {})


def legacy_additions(
    symbol: str,
    current: list[LevelUpMove],
    legacy: list[LevelUpMove],
    config: MergeConfig,
    aliases: dict[str, str],
) -> list[LevelUpMove]:
    current_moves = {canonical_move(row.move, aliases) for row in current}
    settings = species_settings(symbol, config)
    excluded = set(config.globally_excluded_moves)
    excluded.update(
        canonical_move(move, aliases) for move in settings.get("excludedMoves", [])
    )

    return [
        row
        for row in legacy
        if canonical_move(row.move, aliases) not in current_moves
        and canonical_move(row.move, aliases) not in excluded
    ]


def automatically_space_legacy_rows(
    current: list[LevelUpMove],
    additions: list[LevelUpMove],
    minimum_level: int,
    minimum_spacing: int,
) -> list[LevelUpMove]:
    """Evenly spread crowded legacy rows between two fixed current anchors.

    Only a fully bounded interval is adjusted, and only when it has enough room
    to keep every distinct legacy level at least ``minimum_spacing`` levels
    away from the current endpoints and its neighboring legacy level. Rows at
    the same original level remain together.
    """

    if minimum_spacing == 0:
        return additions

    current_levels = sorted({row.level for row in current if row.level > 1})
    groups: dict[tuple[int, int], list[tuple[int, LevelUpMove]]] = {}

    for index, row in enumerate(additions):
        if row.level < minimum_level:
            continue

        lower = max((level for level in current_levels if level <= row.level), default=None)
        upper = min((level for level in current_levels if level > row.level), default=None)
        if lower is None or upper is None:
            continue
        groups.setdefault((lower, upper), []).append((index, row))

    adjusted = list(additions)
    for (lower, upper), indexed_rows in groups.items():
        clusters: list[tuple[int, list[tuple[int, LevelUpMove]]]] = []
        for index, row in sorted(indexed_rows, key=lambda item: (item[1].level, item[0])):
            if not clusters or clusters[-1][0] != row.level:
                clusters.append((row.level, [(index, row)]))
            else:
                clusters[-1][1].append((index, row))

        interval = upper - lower
        required_interval = minimum_spacing * (len(clusters) + 1)
        crowded = any(
            min(level - lower, upper - level) < minimum_spacing for level, _ in clusters
        )
        if not crowded or interval < required_interval:
            continue

        denominator = len(clusters) + 1
        for cluster_index, (_, rows) in enumerate(clusters, start=1):
            # Integer half-up rounding keeps results deterministic (unlike round()).
            numerator = interval * cluster_index
            new_level = lower + (numerator + denominator // 2) // denominator
            for index, row in rows:
                adjusted[index] = replace(row, level=new_level)

    return adjusted


def apply_level_overrides(
    symbol: str,
    additions: list[LevelUpMove],
    config: MergeConfig,
    aliases: dict[str, str],
) -> list[LevelUpMove]:
    overrides = species_settings(symbol, config).get("levelOverrides", {})
    if not isinstance(overrides, dict):
        raise ValueError(f"species.{short_name(symbol)}.levelOverrides must be an object")

    canonical_overrides = {
        canonical_move(move, aliases): levels for move, levels in overrides.items()
    }
    occurrences: dict[str, int] = {}
    result: list[LevelUpMove] = []

    for row in additions:
        move = canonical_move(row.move, aliases)
        if move not in canonical_overrides:
            result.append(row)
            continue

        value = canonical_overrides[move]
        occurrence = occurrences.get(move, 0)
        occurrences[move] = occurrence + 1
        if isinstance(value, int):
            new_level = value
        elif isinstance(value, list) and all(isinstance(level, int) for level in value):
            if occurrence >= len(value):
                raise ValueError(
                    f"Not enough level overrides for {short_name(symbol)} {row.move}"
                )
            new_level = value[occurrence]
        else:
            raise ValueError(
                f"Level override for {short_name(symbol)} {row.move} must be an integer "
                "or a list of integers"
            )

        if not 0 <= new_level <= 100:
            raise ValueError(
                f"Level override for {short_name(symbol)} {row.move} must be from 0 to 100"
            )
        result.append(replace(row, level=new_level))

    return result


def prepare_additions(
    symbol: str,
    current: list[LevelUpMove],
    legacy: list[LevelUpMove],
    config: MergeConfig,
    aliases: dict[str, str],
) -> list[LevelUpMove]:
    additions = legacy_additions(symbol, current, legacy, config, aliases)
    additions = automatically_space_legacy_rows(
        current,
        additions,
        config.minimum_spacing_level,
        config.minimum_spacing,
    )
    return apply_level_overrides(symbol, additions, config, aliases)


def merged_learnset(
    current: list[LevelUpMove], additions: list[LevelUpMove]
) -> list[LevelUpMove]:
    # Current rows win ties so their established ordering remains primary.
    return sorted(
        current + additions,
        key=lambda row: (row.level, row.source != "current", row.order),
    )


def max_level_up_moves() -> int:
    match = MAX_LEVEL_UP_MOVES_PATTERN.search(POKEMON_CONSTANTS.read_text(encoding="utf-8"))
    if match is None:
        raise ValueError(f"Could not find MAX_LEVEL_UP_MOVES in {POKEMON_CONSTANTS}")
    return int(match.group(1))


def validate_merged_learnsets(
    current: dict[str, list[LevelUpMove]],
    merged: dict[str, list[LevelUpMove]],
    aliases: dict[str, str],
) -> None:
    row_limit = max_level_up_moves()
    for symbol, rows in merged.items():
        if len(rows) >= row_limit:
            raise ValueError(
                f"{symbol} has {len(rows)} rows; MAX_LEVEL_UP_MOVES requires fewer than "
                f"{row_limit}"
            )
        if rows != sorted(rows, key=lambda row: (row.level, row.source != "current", row.order)):
            raise ValueError(f"{symbol} is not sorted by level")

        merged_moves = {canonical_move(row.move, aliases) for row in rows}
        missing_current = [
            row.move
            for row in current[symbol]
            if canonical_move(row.move, aliases) not in merged_moves
        ]
        if missing_current:
            raise ValueError(f"{symbol} lost current moves: {', '.join(missing_current)}")


def format_generated_row(row: LevelUpMove) -> str:
    line = f"    LEVEL_UP_MOVE({row.level:>2}, {row.move}),"
    if row.source == "legacy":
        line += " // Legacy Gen 7"
        if row.level != row.original_level:
            line += f"; originally Lv. {row.original_level}"
    return line


def generate_header(
    current_path: Path,
    legacy_path: Path,
    config_path: Path,
    current: dict[str, list[LevelUpMove]],
    merged: dict[str, list[LevelUpMove]],
) -> str:
    current_text = current_path.read_text(encoding="utf-8")

    def replace_learnset(match: re.Match[str]) -> str:
        symbol = match.group("symbol")
        if symbol not in merged:
            return match.group(0)
        rows = "\n".join(format_generated_row(row) for row in merged[symbol])
        return (
            f"static const struct LevelUpMove {symbol}[] = {{\n"
            f"{rows}\n"
            "    LEVEL_UP_END\n"
            "};"
        )

    generated = LEARNSET_PATTERN.sub(replace_learnset, current_text)
    if len(LEARNSET_PATTERN.findall(generated)) != len(current):
        raise ValueError("Generated header does not contain every current learnset")

    def display_path(path: Path) -> Path:
        try:
            return path.resolve().relative_to(REPO_ROOT)
        except ValueError:
            return path

    relative_current = display_path(current_path)
    relative_legacy = display_path(legacy_path)
    relative_config = display_path(config_path)
    banner = (
        "//\n"
        "// DO NOT MODIFY THIS FILE! It is auto-generated by "
        "tools/learnset_helpers/preview_legacy_levelups.py.\n"
        f"// Current source: {relative_current}\n"
        f"// Legacy source:  {relative_legacy}\n"
        f"// Adjustments:    {relative_config}\n"
        "//\n\n"
    )
    return banner + generated


def level_label(level: int) -> str:
    return "Evo" if level == 0 else f"L{level:>2}"


def print_rows(rows: list[LevelUpMove], show_source: bool = False) -> None:
    if not rows:
        print("    (none)")
        return

    for row in rows:
        suffix = ""
        if show_source:
            suffix = f"  [{row.source}]"
        if row.source == "legacy" and row.level != row.original_level:
            suffix += f"  [USUM {level_label(row.original_level)}]"
        print(f"    {level_label(row.level):>3}  {row.move}{suffix}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "species",
        nargs="*",
        help="Species or learnset names to preview (for example, MrMime or Snorlax)",
    )
    parser.add_argument(
        "--current",
        type=Path,
        default=DEFAULT_CURRENT,
        help="Authoritative current learnset header (default: gen_9.h)",
    )
    parser.add_argument(
        "--legacy",
        type=Path,
        default=DEFAULT_LEGACY,
        help="Fallback learnset header (default: gen_7.h)",
    )
    parser.add_argument(
        "--config",
        type=Path,
        default=DEFAULT_CONFIG,
        help="Legacy merge configuration JSON",
    )
    parser.add_argument(
        "--output",
        type=Path,
        help="Write a complete generated C header instead of a preview",
    )
    parser.add_argument(
        "--merged",
        action="store_true",
        help="Also print the complete merged learnset for each species",
    )
    parser.add_argument(
        "--top",
        type=int,
        metavar="N",
        help="Preview the N learnsets receiving the most legacy rows",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    if args.top is not None and args.top < 1:
        raise SystemExit("--top must be at least 1")
    if args.top is not None and args.species:
        raise SystemExit("Pass either species names or --top, not both")
    if args.output is not None and (args.species or args.top is not None or args.merged):
        raise SystemExit("--output cannot be combined with preview options")

    move_aliases = parse_move_aliases(MOVES_HEADER)
    try:
        config = load_config(args.config, move_aliases)
        current = parse_learnsets(args.current, "current")
        legacy = parse_learnsets(args.legacy, "legacy")
    except (OSError, ValueError, json.JSONDecodeError) as error:
        raise SystemExit(str(error)) from error

    common_symbols = set(current) & set(legacy)
    aliases = species_aliases(common_symbols)
    known_species = {normalized(short_name(symbol)) for symbol in common_symbols}
    unknown_species = set(config.species) - known_species
    if unknown_species:
        raise SystemExit(
            "Unknown species in legacy level-up config: "
            + ", ".join(sorted(unknown_species))
        )
    additions_by_symbol = {
        symbol: prepare_additions(
            symbol,
            current[symbol],
            legacy[symbol],
            config,
            move_aliases,
        )
        for symbol in common_symbols
    }
    merged = {
        symbol: merged_learnset(rows, additions_by_symbol.get(symbol, []))
        for symbol, rows in current.items()
    }

    try:
        validate_merged_learnsets(current, merged, move_aliases)
    except ValueError as error:
        raise SystemExit(str(error)) from error

    if args.output is not None:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(
            generate_header(args.current, args.legacy, args.config, current, merged),
            encoding="utf-8",
        )
        print(f"Generated {args.output}")
        return

    if args.top is not None:
        symbols = sorted(
            common_symbols,
            key=lambda symbol: (-len(additions_by_symbol[symbol]), short_name(symbol)),
        )[: args.top]
    else:
        selectors = args.species or DEFAULT_SPECIES
        try:
            symbols = [resolve_species(selector, aliases) for selector in selectors]
        except ValueError as error:
            raise SystemExit(str(error)) from error

    affected = sum(bool(rows) for rows in additions_by_symbol.values())
    total_rows = sum(len(rows) for rows in additions_by_symbol.values())
    total_moves = sum(
        len({canonical_move(row.move, move_aliases) for row in rows})
        for rows in additions_by_symbol.values()
    )
    adjusted_rows = sum(
        row.level != row.original_level
        for rows in additions_by_symbol.values()
        for row in rows
    )
    largest_symbol = max(merged, key=lambda symbol: len(merged[symbol]))

    print(f"Current: {args.current}")
    print(f"Legacy:  {args.legacy}")
    print(f"Config:  {args.config}")
    print("Rule: keep current levels; add a legacy move only when absent from current")
    print(
        f"Overall: {total_moves} missing moves ({total_rows} source rows) "
        f"across {affected} learnsets; {adjusted_rows} rows automatically/explicitly re-leveled"
    )
    print(f"Largest result: {short_name(largest_symbol)} with {len(merged[largest_symbol])} rows")

    for symbol in symbols:
        additions = additions_by_symbol[symbol]
        print()
        print(
            f"{short_name(symbol)}: {len(current[symbol])} current rows + "
            f"{len(additions)} legacy rows = {len(merged[symbol])} merged"
        )
        print("  Would add:")
        print_rows(additions)

        if args.merged:
            print("  Complete merged learnset:")
            print_rows(merged[symbol], show_source=True)


if __name__ == "__main__":
    main()
