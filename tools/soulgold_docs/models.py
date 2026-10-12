from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path
from typing import TypedDict


class HeldItemRow(TypedDict, total=False):
    constant: str
    rarity: str
    name: str


class LevelUpMove(TypedDict):
    level: int
    move: str


class Teachables(TypedDict):
    tmhm: list[str]
    tutors: list[str]


class EvolutionRow(TypedDict):
    method: str
    param: str
    target: str
    conditions: list[str]
    label: str
    itemName: str


class MegaEvolutionRow(TypedDict):
    source: str
    target: str
    item: str
    itemName: str
    label: str


class ItemLocation(TypedDict):
    map: str
    source: str


class SpeciesLocation(TypedDict):
    map: str
    name: str
    time: str
    method: str
    minLevel: int | None
    maxLevel: int | None
    rate: int | None


class AcquisitionStep(TypedDict):
    kind: str
    source: str
    target: str
    requirement: str
    evolution: EvolutionRow | None


class AcquisitionPath(TypedDict):
    source: str
    locations: list[SpeciesLocation]
    steps: list[AcquisitionStep]


class MoveAbilityBoost(TypedDict):
    ability: str
    percent: int


class NamedRecord(TypedDict, total=False):
    id: int
    constant: str
    name: str
    description: str
    power: int
    accuracy: int
    pp: int
    priority: int
    type: str
    category: str
    abilityBoosts: list[MoveAbilityBoost]
    usage: "AbilityUsageEntry"


class GuideRow(TypedDict):
    slug: str
    title: str
    summary: str
    category: str
    order: int
    source: str
    content: str


class AbilityUsageMini(TypedDict):
    species: str
    name: str
    dex: int
    sprite: str | None


class AbilityUsageEntry(TypedDict):
    base: list[AbilityUsageMini]
    innate: list[AbilityUsageMini]


AbilityUsage = dict[str, AbilityUsageEntry]


class ItemRecord(TypedDict):
    id: int
    constant: str
    name: str
    description: str
    pocket: str
    sortType: str
    iconName: str


class ItemIconRow(TypedDict):
    name: str
    src: str


class ImportantItemRow(TypedDict):
    id: int
    constant: str
    name: str
    description: str
    pocket: str
    sortType: str
    itemIcon: str | None
    itemIcons: list[ItemIconRow]
    locations: list[ItemLocation]
    location: str


class TMHMRow(TypedDict):
    kind: str
    number: int
    item: str
    move: str
    label: str


class TMRow(TypedDict, total=False):
    kind: str
    number: int
    item: str
    move: str
    label: str
    name: str
    description: str
    moveName: str
    type: str
    category: str
    power: int
    accuracy: int
    pp: int
    locations: list[ItemLocation]
    location: str
    moveSlug: str


class EncounterMon(TypedDict):
    species: str
    hasSpecies: bool
    name: str
    sprite: str | None
    minLevel: int | None
    maxLevel: int | None
    rate: int | None


class EncounterMethod(TypedDict):
    key: str
    method: str
    mons: list[EncounterMon]


class EncounterVariant(TypedDict):
    time: str
    baseLabel: str
    methods: list[EncounterMethod]
    showTime: bool


class RawEncounterVariant(TypedDict, total=False):
    time: str
    baseLabel: str
    methods: list[EncounterMethod]
    showTime: bool
    _order: int


class WildEncounterRow(TypedDict):
    map: str
    name: str
    baseLabel: str
    variants: list[EncounterVariant]
    hasTimeVariants: bool


class RawEncounterRow(TypedDict, total=False):
    map: str
    name: str
    baseLabel: str
    time: str
    methods: list[EncounterMethod]
    variants: list[RawEncounterVariant]
    hasTimeVariants: bool
    _order: int


class ShowdownMon(TypedDict, total=False):
    name: str
    item: str
    level: int
    ability: str
    nature: str
    evs: dict[str, int]
    ivs: dict[str, int]
    moves: list[str]


class TrainerMon(ShowdownMon, total=False):
    constant: str
    displayName: str
    innates: list[str]
    itemConstant: str
    itemName: str
    itemDescription: str
    itemIcon: str | None
    sprite: str | None


class TrainerRow(TypedDict):
    constant: str
    name: str
    displayName: str
    difficulty: str
    averageLevel: float
    pic: str
    sprite: str | None
    locations: list[str]
    party: list[TrainerMon]


class SpeciesPayloadOptionalFields(TypedDict, total=False):
    formLabel: str


class SpeciesPayloadRow(SpeciesPayloadOptionalFields):
    id: int
    constant: str
    dex: int
    name: str
    types: list[str]
    stats: dict[str, int]
    evYield: dict[str, int]
    eggGroups: list[str]
    categories: list[str]
    bst: int
    abilities: list[str]
    regularAbilities: list[str]
    hiddenAbilities: list[str]
    innates: list[str]
    sprite: str | None
    shinySprite: str | None
    levelUp: list[LevelUpMove]
    tmhm: list[str]
    tutors: list[str]
    eggMoves: list[str]
    evolutions: list[EvolutionRow]
    locations: list[SpeciesLocation]
    acquisitionPaths: list[AcquisitionPath]
    heldItems: list[HeldItemRow]
    slug: str


@dataclass
class SpeciesRow:
    id: int
    constant: str
    name: str
    nat_dex: int
    display_dex: int
    dex_visible: bool
    types: list[str]
    stats: dict[str, int]
    ev_yield: dict[str, int]
    egg_groups: list[str]
    categories: list[str]
    abilities: list[str]
    regular_abilities: list[str]
    hidden_abilities: list[str]
    innates: list[str]
    level_up_symbol: str | None
    teachable_symbol: str | None
    egg_move_symbol: str | None
    front_pic_symbol: str | None
    shiny_palette_symbol: str | None
    sprite: str | None = None
    shiny_sprite: str | None = None
    level_up: list[LevelUpMove] = field(default_factory=list)
    tmhm: list[str] = field(default_factory=list)
    tutors: list[str] = field(default_factory=list)
    egg_moves: list[str] = field(default_factory=list)
    evolutions: list[EvolutionRow] = field(default_factory=list)
    locations: list[SpeciesLocation] = field(default_factory=list)
    acquisition_paths: list[AcquisitionPath] = field(default_factory=list)
    held_items: list[HeldItemRow] = field(default_factory=list)


@dataclass
class SpeciesParseResult:
    rows: list[SpeciesRow]
    by_constant: dict[str, SpeciesRow]


@dataclass(frozen=True)
class OutputPaths:
    sprite_dir: Path
    trainer_sprite_dir: Path
    item_icon_dir: Path


class DocsPayload(TypedDict):
    meta: dict[str, str]
    species: list[SpeciesPayloadRow]
    dedicatedTutors: dict[str, str]
    moves: dict[str, NamedRecord]
    abilities: dict[str, NamedRecord]
    tms: list[TMRow]
    items: list[ImportantItemRow]
    encounters: list[WildEncounterRow]
    trainers: list[TrainerRow]
    typeIcons: dict[str, str]
    categoryIcons: dict[str, str]
    uiIcons: dict[str, str]
    megaEvolutions: list[MegaEvolutionRow]
    guides: list[GuideRow]
