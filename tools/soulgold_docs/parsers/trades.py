from __future__ import annotations

import json
import re

from ..c_parser import read, split_designated_entries, strip_c_comments
from ..models import SpeciesLocation, SpeciesRow
from ..paths import REPO_ROOT, TRADE_DATA_H
from .gifts import reachable_script_labels, script_blocks, species_aliases


IN_GAME_TRADE_COMMAND_RE = re.compile(
    r"\bingame_trade\s+(INGAME_TRADE_[A-Z0-9_]+)\b",
    re.IGNORECASE,
)

JOHTO_TRADE_SOURCES = (
    (
        "VioletCity_House1",
        "VioletCity_House1",
        "INGAME_TRADE_PAWMI",
        "Violet City",
    ),
    (
        "AzaleaTown_House2",
        "AzaleaTown_House2",
        "INGAME_TRADE_SLOWPOKE",
        "Azalea Town",
    ),
    (
        "GoldenrodCity_DepartmentStore_5F",
        "GoldenrodCity_DepartmentStore_6F",
        "INGAME_TRADE_HONEDGE",
        "Goldenrod Dept Store",
    ),
    (
        "OlivineCity_House1",
        "OlivineCity_House1",
        "INGAME_TRADE_VOLTORB",
        "Olivine City",
    ),
    (
        "RintoHouse3",
        "RintoHouse3",
        "INGAME_TRADE_MELTAN",
        "Rinto Village",
    ),
    (
        "BlackthornCity_House2",
        "BlackthornCity_House2",
        "INGAME_TRADE_GABITE",
        "Blackthorn City",
    ),
    (
        "Gate_Route39North",
        "Gate_Route39North",
        "INGAME_TRADE_ROTOM",
        "Route 39-Route 49 Gatehouse",
    ),
)


def _trade_species() -> dict[str, tuple[str, str]]:
    try:
        entries = split_designated_entries(strip_c_comments(read(TRADE_DATA_H)))
    except FileNotFoundError:
        return {}

    aliases = species_aliases()
    trades: dict[str, tuple[str, str]] = {}
    for trade_id, entry in entries.items():
        received_match = re.search(r"\.species\s*=\s*(SPECIES_[A-Z0-9_]+)\b", entry)
        requested_match = re.search(
            r"\.requestedSpecies\s*=\s*(SPECIES_[A-Z0-9_]+)\b",
            entry,
        )
        if not received_match or not requested_match:
            continue
        received = received_match.group(1)
        requested = requested_match.group(1)
        trades[trade_id] = (
            aliases.get(received, received),
            aliases.get(requested, requested),
        )
    return trades


def add_johto_trade_species_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    trades = _trade_species()
    for map_name, script_map_name, trade_id, display_name in JOHTO_TRADE_SOURCES:
        map_dir = REPO_ROOT / "data" / "maps" / map_name
        script_map_dir = REPO_ROOT / "data" / "maps" / script_map_name
        try:
            map_data = json.loads(read(map_dir / "map.json"))
            blocks = script_blocks(read(script_map_dir / "scripts.inc"))
        except (FileNotFoundError, json.JSONDecodeError):
            continue

        reachable_trades = {
            command.group(1).upper()
            for label in reachable_script_labels(map_data, blocks)
            for command in IN_GAME_TRADE_COMMAND_RE.finditer(blocks[label])
        }
        if trade_id not in reachable_trades or trade_id not in trades:
            continue

        received, requested = trades[trade_id]
        if received not in by_species or requested not in by_species:
            continue
        location: SpeciesLocation = {
            "map": str(map_data.get("id") or ""),
            "name": display_name,
            "time": "",
            "method": f"In-game trade (requires {by_species[requested].name})",
            "minLevel": None,
            "maxLevel": None,
            "rate": None,
        }
        locations.setdefault(received, [])
        if location not in locations[received]:
            locations[received].append(location)
