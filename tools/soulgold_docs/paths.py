from __future__ import annotations

from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]
SRC_DIR = REPO_ROOT / "docs" / "src"
OUT_DIR = REPO_ROOT / "docs"
TYPE_GRAPHICS_DIR = REPO_ROOT / "graphics/types"
VERSION_H = REPO_ROOT / "include/config/version.h"

SPECIES_H = REPO_ROOT / "include/constants/species.h"
POKEDEX_H = REPO_ROOT / "include/constants/pokedex.h"
MOVES_H = REPO_ROOT / "include/constants/moves.h"
ABILITIES_H = REPO_ROOT / "include/constants/abilities.h"
TYPES_H = REPO_ROOT / "include/constants/pokemon.h"
TMS_HMS_H = REPO_ROOT / "include/constants/tms_hms.h"
ITEMS_H = REPO_ROOT / "include/constants/items.h"
TRAINERS_H = REPO_ROOT / "src/data/trainers.party"
GRAPHICS_POKEMON_H = REPO_ROOT / "src/data/graphics/pokemon.h"
TRAINER_FRONT_PIC_DIR = REPO_ROOT / "graphics/trainers/front_pics"
WILD_ENCOUNTERS_JSON = REPO_ROOT / "src/data/wild_encounters.json"
HIDDEN_GROTTO_C = REPO_ROOT / "src/hidden_grotto.c"
GACHA_C = REPO_ROOT / "src/game_corner_gacha.c"
ODD_EGG_C = REPO_ROOT / "src/scrcmd.c"
TRADE_DATA_H = REPO_ROOT / "src/data/trade.h"
MAP_GROUPS_JSON = REPO_ROOT / "data/maps/map_groups.json"
REGION_MAP_SECTIONS_JSON = REPO_ROOT / "src/data/region_map/region_map_sections.json"
FORM_CHANGE_TABLES_H = REPO_ROOT / "src/data/pokemon/form_change_tables.h"
SPECIAL_MOVESETS_JSON = REPO_ROOT / "src/data/pokemon/special_movesets.json"
GUIDES_DIR = SRC_DIR / "guides"
