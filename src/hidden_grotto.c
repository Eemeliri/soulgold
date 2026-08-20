#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "hidden_grotto.h"
#include "overworld.h"
#include "pokemon.h"
#include "random.h"
#include "script_pokemon_util.h"
#include "constants/event_objects.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/species.h"

#define ITEM_FROM_GROTTO_DATA 0xFFFF

enum HiddenGrottoId
{
    //Johto Grottos
    HIDDEN_GROTTO_ROUTE32,
    HIDDEN_GROTTO_GOLDENROD_SHORE,
    HIDDEN_GROTTO_ROUTE35,
    HIDDEN_GROTTO_ILEX,
    HIDDEN_GROTTO_ROUTE33,
    HIDDEN_GROTTO_ROUTE38,
    HIDDEN_GROTTO_ROUTE44,
    HIDDEN_GROTTO_LAKEOFRAGE,
    HIDDEN_GROTTO_ROUTE47,
    HIDDEN_GROTTO_VAJRA_DESERT_WEST,
    HIDDEN_GROTTO_JOHTO_UNUSED2,
    
    // Kanto Grottos
    HIDDEN_GROTTO_KANTO_UNUSED1,
    HIDDEN_GROTTO_KANTO_UNUSED2,
    HIDDEN_GROTTO_KANTO_UNUSED3,
    HIDDEN_GROTTO_KANTO_UNUSED4,
    HIDDEN_GROTTO_KANTO_UNUSED5,
    HIDDEN_GROTTO_KANTO_UNUSED6,
    HIDDEN_GROTTO_KANTO_UNUSED7,
    HIDDEN_GROTTO_KANTO_UNUSED8,
    HIDDEN_GROTTO_KANTO_UNUSED9,
    HIDDEN_GROTTO_COUNT,
};

STATIC_ASSERT(HIDDEN_GROTTO_COUNT == NUM_HIDDEN_GROTTOES, HiddenGrottoCountDoesNotMatchSaveData);

enum
{
    HIDDEN_GROTTO_OBJ_ITEM = 1,
    HIDDEN_GROTTO_OBJ_MON = 2,
};

struct HiddenGrottoWeightedEntry
{
    u8 weight;
    u16 value;
};

struct HiddenGrottoMonEntry
{
    u16 species;
    u8 form;
};

struct HiddenGrottoData
{
    u8 mapGroup;
    u8 mapNum;
    u8 monLevel;
    u8 monObjectLocalId;
    u16 rareItem;
    struct HiddenGrottoMonEntry mons[4];
};

static u16 GetCurrentHiddenGrottoId(void);
static struct HiddenGrottoContent *GetCurrentHiddenGrottoContent(void);
static const struct HiddenGrottoData *GetCurrentHiddenGrottoData(void);
static u8 GetHiddenGrottoMonLevel(const struct HiddenGrottoData *grotto);
static bool32 IsHiddenGrottoContentValid(const struct HiddenGrottoContent *content);
static void PopulateCurrentHiddenGrotto(void);
static u16 GetWeightedTableEntry(const struct HiddenGrottoWeightedEntry *table, u8 count, enum RandomTag tag);
static u16 GetHiddenGrottoSpecies(const struct HiddenGrottoMonEntry *entry);
static u16 GetRandomHiddenGrottoSpecies(const struct HiddenGrottoData *grotto);
static void GiveHiddenGrottoMonPerfectIvs(struct Pokemon *mon);
static void UpdateCurrentHiddenGrottoMonGraphics(u16 species);

static const struct HiddenGrottoData sHiddenGrottoData[NUM_HIDDEN_GROTTOES] =
{
    [HIDDEN_GROTTO_ROUTE32] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_ROUTE32),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_ROUTE32),
        .monLevel = 10,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_EVERSTONE,
        .mons =
        {
            { SPECIES_APPLIN, 0 },
            { SPECIES_WOOPER_PALDEA, 0 },
            { SPECIES_MAREEP, 0 },
            { SPECIES_MISDREAVUS, 0 },
        },
    },
    [HIDDEN_GROTTO_GOLDENROD_SHORE] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_GOLDENROD_SHORE),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_GOLDENROD_SHORE),
        .monLevel = 20,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_LIGHT_CLAY,
        .mons =
        {
            { SPECIES_MINCCINO, 0 },
            { SPECIES_SHROOMISH, 0 },
            { SPECIES_ROCKRUFF_OWN_TEMPO, 0 },
            { SPECIES_HERACROSS, 0 },
        },
    },
    [HIDDEN_GROTTO_ROUTE35] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_ROUTE35),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_ROUTE35),
        .monLevel = 18,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_UNREMARKABLE_TEACUP,
        .mons =
        {
            { SPECIES_ROOKIDEE, 0 },
            { SPECIES_PIKACHU, 0 },
            { SPECIES_POLTCHAGEIST, 0 },
            { SPECIES_EEVEE, 0 },
        },
    },
    [HIDDEN_GROTTO_ILEX] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_ILEX),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_ILEX),
        .monLevel = 15,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_LEAF_STONE,
        .mons =
        {
            { SPECIES_ODDISH, 0 },
            { SPECIES_FERROSEED, 0 },
            { SPECIES_ROSELIA, 0 },
            { SPECIES_EXEGGCUTE, 0 },
        },
    },
    [HIDDEN_GROTTO_ROUTE33] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_ROUTE33),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_ROUTE33),
        .monLevel = 14,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_SUN_STONE,
        .mons =
        {
            { SPECIES_PACHIRISU, 0 },
            { SPECIES_MIENFOO, 0 },
            { SPECIES_DARUMAKA, 0 },
            { SPECIES_COTTONEE, 0 },
        },
    },
    [HIDDEN_GROTTO_ROUTE38] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_ROUTE38),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_ROUTE38),
        .monLevel = 30,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_STARDUST,
        .mons =
        {
            { SPECIES_MUNCHLAX, 0 },
            { SPECIES_MEOWSTIC_M, 0 },
            { SPECIES_MEOWSTIC_F, 0 },
            { SPECIES_ESPATHRA, 0 },
        },
    },
    [HIDDEN_GROTTO_ROUTE44] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_ROUTE44),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_ROUTE44),
        .monLevel = 40,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_ICE_STONE,
        .mons =
        {
            { SPECIES_ARCTIBAX, 0 },
            { SPECIES_BERGMITE, 0 },
            { SPECIES_LOPUNNY, 0 },
            { SPECIES_ZORUA_HISUI, 0 },
        },
    },
    [HIDDEN_GROTTO_LAKEOFRAGE] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_LAKEOFRAGE),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_LAKEOFRAGE),
        .monLevel = 35,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_EVIOLITE,
        .mons =
        {
            { SPECIES_CYCLIZAR, 0 },
            { SPECIES_ORICORIO_SENSU, 0 },
            { SPECIES_FALINKS, 0 },
            { SPECIES_DRAMPA, 0 },
        },
    },
    [HIDDEN_GROTTO_ROUTE47] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_ROUTE47),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_ROUTE47),
        .monLevel = 40,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_LUCKY_EGG,
        .mons =
        {
            { SPECIES_CHANSEY, 0 },
            { SPECIES_LARVESTA, 0 },
            { SPECIES_DITTO, 0 },
            { SPECIES_ZORUA, 0 },
        },
    },
    [HIDDEN_GROTTO_VAJRA_DESERT_WEST] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 30,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_SMOOTH_ROCK,
        .mons =
        {
            { SPECIES_BALTOY, 0 },
            { SPECIES_VULLABY, 0 },
            { SPECIES_LARVITAR, 0 },
            { SPECIES_GIBLE, 0 },
        },
    },

    [HIDDEN_GROTTO_JOHTO_UNUSED2] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CYNDAQUIL, 0 },
            { SPECIES_TOTODILE, 0 },
            { SPECIES_CHIKORITA, 0 },
            { SPECIES_CELEBI, 0 },
        },
    },

    // KANTO

    [HIDDEN_GROTTO_KANTO_UNUSED1] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED2] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED3] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED4] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED5] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED6] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED7] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED8] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },
    [HIDDEN_GROTTO_KANTO_UNUSED9] =
    {
        .mapGroup = MAP_GROUP(MAP_HIDDEN_GROTTO_UNUSED),
        .mapNum = MAP_NUM(MAP_HIDDEN_GROTTO_UNUSED),
        .monLevel = 100,
        .monObjectLocalId = HIDDEN_GROTTO_OBJ_MON,
        .rareItem = ITEM_MOON_STONE,
        .mons =
        {
            { SPECIES_CHARMANDER, 0 },
            { SPECIES_SQUIRTLE, 0 },
            { SPECIES_BULBASAUR, 0 },
            { SPECIES_PIKACHU, 0 },
        },
    },

};

static const struct HiddenGrottoWeightedEntry sHiddenGrottoPokemonIndexes[] =
{
    { 10, 0 },
    { 10, 1 },
    { 10, 2 },
    { 10, 3 },
};

static const struct HiddenGrottoWeightedEntry sHiddenGrottoItems[] =
{
    { 20, ITEM_HEALTH_WING },
    {  8, ITEM_GENIUS_FEATHER },
    { 10, ITEM_MUSCLE_FEATHER },
    {  4, ITEM_RESIST_FEATHER },
    { 10, ITEM_CLEVER_FEATHER },
    {  4, ITEM_SWIFT_FEATHER },
    { 44, ITEM_FROM_GROTTO_DATA },
};

static const struct HiddenGrottoWeightedEntry sHiddenGrottoHiddenItems[] =
{
    { 30, ITEM_GROWTH_MULCH },
    { 20, ITEM_TINYMUSHROOM },
    { 12, ITEM_BIG_MUSHROOM },
    {  4, ITEM_BALMMUSHROOM },
    { 10, ITEM_HEART_SCALE },
    { 10, ITEM_PEARL },
    {  5, ITEM_RARE_CANDY },
    {  5, ITEM_PP_UP },
    {  4, ITEM_PP_MAX },
};

void DailyResetHiddenGrottoes(void)
{
    memset(gSaveBlock3Ptr->hiddenGrottoContents, 0, sizeof(gSaveBlock3Ptr->hiddenGrottoContents));
}

void HiddenGrotto_InitializeCurrent(void)
{
    struct HiddenGrottoContent *content = GetCurrentHiddenGrottoContent();

    gSpecialVar_0x8004 = ITEM_NONE;
    gSpecialVar_0x8005 = 0;

    if (content == NULL)
    {
        gSpecialVar_Result = HIDDEN_GROTTO_EMPTY;
        return;
    }

    if (!IsHiddenGrottoContentValid(content))
    {
        content->type = HIDDEN_GROTTO_UNSET;
        content->id = ITEM_NONE;
    }

    PopulateCurrentHiddenGrotto();

    gSpecialVar_Result = content->type;
    gSpecialVar_0x8004 = content->id;

    if (content->type == HIDDEN_GROTTO_POKEMON)
        UpdateCurrentHiddenGrottoMonGraphics(content->id);
}

void HiddenGrotto_EmptyCurrent(void)
{
    struct HiddenGrottoContent *content = GetCurrentHiddenGrottoContent();

    if (content != NULL)
    {
        content->type = HIDDEN_GROTTO_EMPTY;
        content->id = ITEM_NONE;
    }
}

void HiddenGrotto_GetCurrentContentType(void)
{
    struct HiddenGrottoContent *content = GetCurrentHiddenGrottoContent();

    gSpecialVar_Result = (content != NULL) ? content->type : HIDDEN_GROTTO_EMPTY;
}

void HiddenGrotto_GetCurrentContentId(void)
{
    struct HiddenGrottoContent *content = GetCurrentHiddenGrottoContent();

    gSpecialVar_Result = (content != NULL) ? content->id : ITEM_NONE;
}

void HiddenGrotto_CreateCurrentMon(void)
{
    const struct HiddenGrottoData *grotto = GetCurrentHiddenGrottoData();
    struct HiddenGrottoContent *content = GetCurrentHiddenGrottoContent();
    u8 hiddenAbilityNum = NUM_NORMAL_ABILITY_SLOTS;

    gSpecialVar_Result = FALSE;

    if (grotto == NULL
     || content == NULL
     || content->type != HIDDEN_GROTTO_POKEMON
     || content->id == SPECIES_NONE
     || content->id >= NUM_SPECIES)
        return;

    CreateScriptedWildMon(content->id, GetHiddenGrottoMonLevel(grotto), ITEM_NONE, ITEM_NONE);
    GiveHiddenGrottoMonPerfectIvs(&gEnemyParty[0]);
    if (GetSpeciesAbility(content->id, hiddenAbilityNum) != ABILITY_NONE)
        SetMonData(&gEnemyParty[0], MON_DATA_ABILITY_NUM, &hiddenAbilityNum);
    CalculateMonStats(&gEnemyParty[0]);
    gSpecialVar_Result = TRUE;
}

void HiddenGrotto_TestCurrentMonBounds(void)
{
    const struct HiddenGrottoData *grotto = GetCurrentHiddenGrottoData();
    u16 invalidCount = 0;
    u16 minSpecies = NUM_SPECIES;
    u16 maxSpecies = SPECIES_NONE;
    u16 lastSpecies = SPECIES_NONE;
    u16 i;

    gSpecialVar_Result = 0xFFFF;
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = SPECIES_NONE;
    gSpecialVar_0x8006 = SPECIES_NONE;
    gSpecialVar_0x8007 = SPECIES_NONE;

    if (grotto == NULL)
        return;

    for (i = 0; i < 1000; i++)
    {
        u16 species = GetRandomHiddenGrottoSpecies(grotto);

        if (species == SPECIES_NONE || species >= NUM_SPECIES)
        {
            invalidCount++;
            lastSpecies = species;
            continue;
        }

        if (species < minSpecies)
            minSpecies = species;
        if (species > maxSpecies)
            maxSpecies = species;
    }

    if (minSpecies == NUM_SPECIES)
        minSpecies = SPECIES_NONE;

    gSpecialVar_Result = invalidCount;
    gSpecialVar_0x8004 = 1000;
    gSpecialVar_0x8005 = minSpecies;
    gSpecialVar_0x8006 = maxSpecies;
    gSpecialVar_0x8007 = lastSpecies;

    DebugPrintf("HiddenGrottoTest samples=%d invalid=%d min=%d max=%d lastInvalid=%d",
                gSpecialVar_0x8004, gSpecialVar_Result, gSpecialVar_0x8005, gSpecialVar_0x8006, gSpecialVar_0x8007);
}

static u16 GetCurrentHiddenGrottoId(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sHiddenGrottoData); i++)
    {
        if (sHiddenGrottoData[i].mapGroup == gSaveBlock1Ptr->location.mapGroup
         && sHiddenGrottoData[i].mapNum == gSaveBlock1Ptr->location.mapNum)
            return i;
    }

    return NUM_HIDDEN_GROTTOES;
}

static struct HiddenGrottoContent *GetCurrentHiddenGrottoContent(void)
{
    u16 grottoId = GetCurrentHiddenGrottoId();

    if (grottoId >= NUM_HIDDEN_GROTTOES)
        return NULL;

    return &gSaveBlock3Ptr->hiddenGrottoContents[grottoId];
}

static const struct HiddenGrottoData *GetCurrentHiddenGrottoData(void)
{
    u16 grottoId = GetCurrentHiddenGrottoId();

    if (grottoId >= NUM_HIDDEN_GROTTOES)
        return NULL;

    return &sHiddenGrottoData[grottoId];
}

bool8 IsCurrentMapHiddenGrotto(void)
{
    return GetCurrentHiddenGrottoId() < NUM_HIDDEN_GROTTOES;
}

static u8 GetHiddenGrottoMonLevel(const struct HiddenGrottoData *grotto)
{
    return grotto->monLevel;
}

static bool32 IsHiddenGrottoContentValid(const struct HiddenGrottoContent *content)
{
    switch (content->type)
    {
    case HIDDEN_GROTTO_UNSET:
    case HIDDEN_GROTTO_EMPTY:
        return content->id == ITEM_NONE;
    case HIDDEN_GROTTO_POKEMON:
        return content->id != SPECIES_NONE && content->id < NUM_SPECIES;
    case HIDDEN_GROTTO_ITEM:
    case HIDDEN_GROTTO_HIDDEN_ITEM:
        return content->id != ITEM_NONE && content->id < ITEMS_COUNT;
    default:
        return FALSE;
    }
}

static void PopulateCurrentHiddenGrotto(void)
{
    const struct HiddenGrottoData *grotto = GetCurrentHiddenGrottoData();
    struct HiddenGrottoContent *content = GetCurrentHiddenGrottoContent();
    u16 value;

    if (grotto == NULL || content == NULL || content->type != HIDDEN_GROTTO_UNSET)
        return;

    if (!FlagGet(FLAG_SYS_HIDDEN_GROTTO_FIRST_VISIT))
    {
        FlagSet(FLAG_SYS_HIDDEN_GROTTO_FIRST_VISIT);
        content->type = HIDDEN_GROTTO_POKEMON;
        content->id = GetRandomHiddenGrottoSpecies(grotto);
        return;
    }

    switch (RandomWeighted(RNG_HIDDEN_GROTTO_CONTENT, 6, 2, 2))
    {
    case 0:
        content->type = HIDDEN_GROTTO_POKEMON;
        content->id = GetRandomHiddenGrottoSpecies(grotto);
        break;
    case 1:
        value = GetWeightedTableEntry(sHiddenGrottoItems, ARRAY_COUNT(sHiddenGrottoItems), RNG_HIDDEN_GROTTO_ITEM);
        if (value == ITEM_FROM_GROTTO_DATA)
            value = grotto->rareItem;
        content->type = HIDDEN_GROTTO_ITEM;
        content->id = value;
        break;
    case 2:
    default:
        value = GetWeightedTableEntry(sHiddenGrottoHiddenItems, ARRAY_COUNT(sHiddenGrottoHiddenItems), RNG_HIDDEN_GROTTO_HIDDEN_ITEM);
        content->type = HIDDEN_GROTTO_HIDDEN_ITEM;
        content->id = value;
        break;
    }
}

static u16 GetWeightedTableEntry(const struct HiddenGrottoWeightedEntry *table, u8 count, enum RandomTag tag)
{
    u32 totalWeight = 0;
    u16 roll;
    u32 i;

    for (i = 0; i < count; i++)
        totalWeight += table[i].weight;

    assertf(count > 0 && totalWeight > 0 && totalWeight <= MAX_u16);
    roll = RandomUniform(tag, 0, totalWeight - 1);

    for (i = 0; i < count; i++)
    {
        if (roll < table[i].weight)
            return table[i].value;
        roll -= table[i].weight;
    }

    return table[count - 1].value;
}

static u16 GetHiddenGrottoSpecies(const struct HiddenGrottoMonEntry *entry)
{
    if (entry->form == 0)
        return entry->species;

    return GetFormSpeciesId(entry->species, entry->form);
}

static u16 GetRandomHiddenGrottoSpecies(const struct HiddenGrottoData *grotto)
{
    u16 monIndex = GetWeightedTableEntry(sHiddenGrottoPokemonIndexes, ARRAY_COUNT(sHiddenGrottoPokemonIndexes), RNG_HIDDEN_GROTTO_POKEMON);

    return GetHiddenGrottoSpecies(&grotto->mons[monIndex]);
}

static void GiveHiddenGrottoMonPerfectIvs(struct Pokemon *mon)
{
    u8 perfectIv = MAX_PER_STAT_IVS;
    u8 statPair = RandomUniform(RNG_HIDDEN_GROTTO_IVS, 0, NUM_STATS * (NUM_STATS - 1) - 1);
    u8 firstStat = statPair / (NUM_STATS - 1);
    u8 secondStat = statPair % (NUM_STATS - 1);

    if (secondStat >= firstStat)
        secondStat++;

    SetMonData(mon, MON_DATA_HP_IV + firstStat, &perfectIv);
    SetMonData(mon, MON_DATA_HP_IV + secondStat, &perfectIv);
}

static void UpdateCurrentHiddenGrottoMonGraphics(u16 species)
{
    u8 objectEventId;
    const struct HiddenGrottoData *grotto = GetCurrentHiddenGrottoData();
    u16 graphicsId;

    if (grotto == NULL || species == SPECIES_NONE || species >= NUM_SPECIES)
        return;

    graphicsId = species + OBJ_EVENT_MON;
    VarSet(VAR_OBJ_GFX_ID_0, graphicsId);

    if (TryGetObjectEventIdByLocalIdAndMap(grotto->monObjectLocalId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &objectEventId))
        return;

    ObjectEventSetGraphicsId(&gObjectEvents[objectEventId], graphicsId);
}
