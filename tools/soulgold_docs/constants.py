"""Configuration constants for the SoulGold docs generator."""

from __future__ import annotations

import re

STAT_FIELDS = {
    "baseHP": "hp",
    "baseAttack": "atk",
    "baseDefense": "def",
    "baseSpAttack": "spa",
    "baseSpDefense": "spd",
    "baseSpeed": "spe",
}

EV_YIELD_FIELDS = {
    "evYield_HP": "hp",
    "evYield_Attack": "atk",
    "evYield_Defense": "def",
    "evYield_SpAttack": "spa",
    "evYield_SpDefense": "spd",
    "evYield_Speed": "spe",
}

ENCOUNTER_SLOT_RATES = {
    "land_mons": [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1],
    "water_mons": [60, 30, 5, 4, 1],
    "rock_smash_mons": [60, 30, 5, 4, 1],
    "fishing_mons": [70, 30, 60, 20, 20, 40, 40, 15, 4, 1],
}

JOHTO_ROUTE_PROGRESS = {
    route: index
    for index, route in enumerate([29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48])
}

TYPE_ICON_FILES = {
    "TYPE_NONE": "none.png",
    "TYPE_NORMAL": "normal.png",
    "TYPE_FIGHTING": "fight.png",
    "TYPE_FLYING": "flying.png",
    "TYPE_POISON": "poison.png",
    "TYPE_GROUND": "ground.png",
    "TYPE_ROCK": "rock.png",
    "TYPE_BUG": "bug.png",
    "TYPE_GHOST": "ghost.png",
    "TYPE_STEEL": "steel.png",
    "TYPE_MYSTERY": "mystery.png",
    "TYPE_FIRE": "fire.png",
    "TYPE_WATER": "water.png",
    "TYPE_GRASS": "grass.png",
    "TYPE_ELECTRIC": "electric.png",
    "TYPE_PSYCHIC": "psychic.png",
    "TYPE_ICE": "ice.png",
    "TYPE_DRAGON": "dragon.png",
    "TYPE_DARK": "dark.png",
    "TYPE_FAIRY": "fairy.png",
    "TYPE_STELLAR": "stellar.png",
}

MOVE_CATEGORY_ICON_FILES = {
    "DAMAGE_CATEGORY_PHYSICAL": "physical.png",
    "DAMAGE_CATEGORY_SPECIAL": "special.png",
    "DAMAGE_CATEGORY_STATUS": "status.png",
}

SHINY_TOGGLE_ICON_FILE = "shiny.png"

COMPOUND_STRING_MACRO = "COMPOUND_STRING"
SPRITE_FRAME_SIZE = 64
SHINY_TOGGLE_ICON_SIZE = (24, 24)
GBA_COLOR_CHANNEL_MAX = 31
RGB_CHANNEL_MAX = 255
PIL_PALETTE_SIZE = 768
UNKNOWN_MAP = "UNKNOWN_MAP"
BATTLE_PYRAMID_WILD_LABEL = "gBattlePyramidWildMonHeaders"
TIME_NIGHT_SUFFIX = "_Night"
DOCS_HIDDEN_WILD_ENCOUNTER_MAPS = {
    "MAP_BATTLE_CAFE",
}

GMAX_DMAX_FORM_RE = re.compile(r"_(?:GMAX|DMAX)(?:_|$)")

FOSSIL_POKEMON_SPECIES = {
    "SPECIES_OMANYTE",
    "SPECIES_OMASTAR",
    "SPECIES_KABUTO",
    "SPECIES_KABUTOPS",
    "SPECIES_AERODACTYL",
    "SPECIES_LILEEP",
    "SPECIES_CRADILY",
    "SPECIES_ANORITH",
    "SPECIES_ARMALDO",
    "SPECIES_CRANIDOS",
    "SPECIES_RAMPARDOS",
    "SPECIES_SHIELDON",
    "SPECIES_BASTIODON",
    "SPECIES_TIRTOUGA",
    "SPECIES_CARRACOSTA",
    "SPECIES_ARCHEN",
    "SPECIES_ARCHEOPS",
    "SPECIES_TYRUNT",
    "SPECIES_TYRANTRUM",
    "SPECIES_AMAURA",
    "SPECIES_AURORUS",
    "SPECIES_DRACOZOLT",
    "SPECIES_ARCTOZOLT",
    "SPECIES_DRACOVISH",
    "SPECIES_ARCTOVISH",
}

DEX_HIDDEN_SPECIES = {
    "SPECIES_MIMIKYU_BUSTED",
    "SPECIES_MIMIKYU_BUSTED_TOTEM",
    "SPECIES_MIMIKYU_TOTEM_DISGUISED",
    "SPECIES_MIMIKYU_TOTEM_BUSTED",
    "SPECIES_ZARUDE_DADA",
}

DEX_HIDDEN_PREFIXES = (
    "SPECIES_ARCEUS_",
    "SPECIES_UNOWN_",
)

DEX_HIDDEN_COLOR_FORMS = {
    "SPECIES_FLABEBE_YELLOW",
    "SPECIES_FLABEBE_ORANGE",
    "SPECIES_FLABEBE_BLUE",
    "SPECIES_FLABEBE_WHITE",
    "SPECIES_FLOETTE_YELLOW",
    "SPECIES_FLOETTE_ORANGE",
    "SPECIES_FLOETTE_BLUE",
    "SPECIES_FLOETTE_WHITE",
    "SPECIES_FLORGES_YELLOW",
    "SPECIES_FLORGES_ORANGE",
    "SPECIES_FLORGES_BLUE",
    "SPECIES_FLORGES_WHITE",
}

SPECIES_NAME_OVERRIDES = {
    "SPECIES_FLOETTE_ETERNAL": "Floette Eternal",
}

ITEMS_HIDDEN_SORT_TYPES = {
    "ITEM_TYPE_GEM",
    "ITEM_TYPE_MEMORY",
    "ITEM_TYPE_PLATE",
    "ITEM_TYPE_Z_CRYSTAL",
}

ITEMS_HIDDEN_CONSTANTS = {
    "ITEM_ARMORITE_ORE",
    "ITEM_BLUE_ORB",
    "ITEM_BURN_DRIVE",
    "ITEM_CHILL_DRIVE",
    "ITEM_DOUSE_DRIVE",
    "ITEM_DYNITE_ORE",
    "ITEM_GALARICA_TWIG",
    "ITEM_GIMMIGHOUL_COIN",
    "ITEM_MACHO_BRACE",
    "ITEM_MASTERPIECE_TEACUP",
    "ITEM_RED_ORB",
    "ITEM_SACHET",
    "ITEM_SHOCK_DRIVE",
    "ITEM_WHIPPED_DREAM",
}

ITEMS_HIDDEN_SUFFIXES = (
    "_SWEET",
)

IMPORTANT_ITEM_SORT_TYPES = {
    "ITEM_TYPE_EVOLUTION_ITEM",
    "ITEM_TYPE_EVOLUTION_STONE",
}

SPRITE_CACHE_VERSION = "alpha2"

GENERIC_MEGA_STONE_ITEMS = {
    "ITEM_NORMALITE",
    "ITEM_FIRETITE",
    "ITEM_WATERTITE",
    "ITEM_ELECTRITE",
    "ITEM_GRASSTITE",
    "ITEM_ICETITE",
    "ITEM_FIGHTITE",
    "ITEM_POISONTITE",
    "ITEM_GROUNDITE",
    "ITEM_FLYINGITE",
    "ITEM_PSYCHITE",
    "ITEM_BUGTITE",
    "ITEM_ROCKTITE",
    "ITEM_GHOSTITE",
    "ITEM_DRAGOTITE",
    "ITEM_DARKTITE",
    "ITEM_STEELTITE",
    "ITEM_FAIRYTITE",
    "ITEM_BONDSTONE",
}

IMPORTANT_ITEM_POCKETS = {
    "POCKET_BATTLE_ITEMS",
}

# Useful training consumables and player-facing key items live outside the
# pockets and sort types used by the evolution-item index, so opt them into the
# Items page explicitly.
ADDITIONAL_IMPORTANT_ITEMS = {
    "ITEM_ABILITY_CAPSULE",
    "ITEM_ABILITY_PATCH",
    "ITEM_BOTTLE_CAP",
    "ITEM_GOLD_BOTTLE_CAP",
    "ITEM_HP_UP",
    "ITEM_PROTEIN",
    "ITEM_IRON",
    "ITEM_CALCIUM",
    "ITEM_ZINC",
    "ITEM_CARBOS",
    "ITEM_HP_UP_EX",
    "ITEM_PROTEIN_EX",
    "ITEM_IRON_EX",
    "ITEM_CALCIUM_EX",
    "ITEM_ZINC_EX",
    "ITEM_CARBOS_EX",
    "ITEM_WITHERED_HERB",
    "ITEM_GRIMY_HERB",
    "ITEM_BRITTLE_HERB",
    "ITEM_GOOPY_HERB",
    "ITEM_DULL_HERB",
    "ITEM_SOGGY_HERB",
    "ITEM_OLD_ROD",
    "ITEM_GOOD_ROD",
    "ITEM_SUPER_ROD",
    "ITEM_DOWSING_MACHINE",
    "ITEM_VS_SEEKER",
    "ITEM_COIN_CASE",
    "ITEM_GRACIDEA",
}

EXCLUDED_TRAINER_MAP_GROUPS = {
    "gMapGroup_IndoorPallet",
    "gMapGroup_IndoorViridian",
    "gMapGroup_IndoorPewter",
    "gMapGroup_IndoorCerulean",
    "gMapGroup_IndoorVermilion",
    "gMapGroup_IndoorLavender",
    "gMapGroup_IndoorCeladon",
    "gMapGroup_IndoorSaffron",
    "gMapGroup_IndoorFuchsia",
    "gMapGroup_IndoorCinnabar",
    "gMapGroup_IndoorIndigo",
    "gMapGroup_IndoorKantoRoutes",
    "gMapGroup_Emerald1",
    "gMapGroup_Emerald2",
    "gMapGroup_Emerald3",
    "gMapGroup_Emerald4",
    "gMapGroup_Emerald5",
}

EXCLUDED_TRAINER_MAP_NAMES = {
    "PalletTown",
    "ViridianCity",
    "PewterCity",
    "CeruleanCity",
    "VermilionCity",
    "LavenderTown",
    "CeladonCity",
    "SaffronCity",
    "FuchsiaCity",
    "CinnabarIsland",
    "IndigoPlateau",
    "Route1",
    "Route2",
    "Route3",
    "Route4",
    "Route5",
    "Route6",
    "Route7",
    "Route8",
    "Route9",
    "Route10",
    "Route11",
    "Route12",
    "Route13",
    "Route14",
    "Route15",
    "Route16",
    "Route17",
    "Route18",
    "Route19",
    "Route20",
    "Route21",
    "Route22",
    "Route23",
    "Route24",
    "Route25",
    "Route28",
    "OneIsland",
    "OneIsland_KindleRoad_Frlg",
    "OneIsland_TreasureBeach_Frlg",
    "OneIsland_KindleRoad_EmberSpa_Frlg",
    "Saffron_Temp",
}

EXCLUDED_TRAINER_MAP_PREFIXES = (
    "DiglettsCave",
    "MtEmber",
    "MtMoon",
    "PewterCity",
    "RockTunnel",
    "Route19_Cave",
    "SeafoamIslands",
    "ViridianForest",
)

ALWAYS_INCLUDED_TRAINER_CONSTANTS = {
    "TRAINER_WILL_1",
    "TRAINER_WILL_2",
    "TRAINER_KOGA_1",
    "TRAINER_KOGA_2",
    "TRAINER_BRUNO_1",
    "TRAINER_BRUNO_2",
    "TRAINER_KAREN_1",
    "TRAINER_KAREN_2",
    "TRAINER_LANCE_1",
    "TRAINER_LANCE_2",
}
