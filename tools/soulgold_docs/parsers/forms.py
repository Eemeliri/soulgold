from __future__ import annotations

import json
import re

from ..c_parser import read, strip_c_comments
from ..models import SpeciesLocation, SpeciesRow
from ..paths import FORM_CHANGE_TABLES_H, REPO_ROOT
from .gifts import reachable_script_labels, script_blocks


ROTOM_FORM_TABLE_RE = re.compile(
    r"sRotomFormChangeTable\[\]\s*=\s*\{(.*?)\};",
    re.DOTALL,
)
ROTOM_FORM_RE = re.compile(
    r"\{\s*FORM_CHANGE_MOVE\s*,\s*(SPECIES_ROTOM_[A-Z0-9_]+)\s*,",
)
ROTOM_APARTMENT_MAP = "GoldenrodApartmentBasement"


def _rotom_forms() -> list[str]:
    try:
        text = strip_c_comments(read(FORM_CHANGE_TABLES_H))
    except FileNotFoundError:
        return []
    table = ROTOM_FORM_TABLE_RE.search(text)
    return ROTOM_FORM_RE.findall(table.group(1)) if table else []


def add_rotom_form_change_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    map_dir = REPO_ROOT / "data" / "maps" / ROTOM_APARTMENT_MAP
    try:
        map_data = json.loads(read(map_dir / "map.json"))
        blocks = script_blocks(read(map_dir / "scripts.inc"))
    except (FileNotFoundError, json.JSONDecodeError):
        return

    reachable = reachable_script_labels(map_data, blocks)
    if not any("ChangeRotomForm" in blocks[label] for label in reachable):
        return

    for species in _rotom_forms():
        if species not in by_species:
            continue
        location: SpeciesLocation = {
            "map": str(map_data.get("id") or ""),
            "name": "Goldenrod Apartment Basement",
            "time": "",
            "method": "Bring Rotom here to change form",
            "minLevel": None,
            "maxLevel": None,
            "rate": None,
        }
        locations.setdefault(species, [])
        if location not in locations[species]:
            locations[species].append(location)
