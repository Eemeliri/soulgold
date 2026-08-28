#include "global.h"
#include "battle_pyramid.h"
#include "event_data.h"
#include "item.h"
#include "pokedex.h"

#define SPECIAL_FLAGS_SIZE  (NUM_SPECIAL_FLAGS / 8)  // 8 flags per byte
#define TEMP_FLAGS_SIZE     (NUM_TEMP_FLAGS / 8)
#define DAILY_FLAGS_SIZE    (NUM_DAILY_FLAGS / 8)
#define TEMP_VARS_SIZE      (NUM_TEMP_VARS * 2)      // 1/2 var per byte

EWRAM_DATA u16 gSpecialVar_0x8000 = 0;
EWRAM_DATA u16 gSpecialVar_0x8001 = 0;
EWRAM_DATA u16 gSpecialVar_0x8002 = 0;
EWRAM_DATA u16 gSpecialVar_0x8003 = 0;
EWRAM_DATA u16 gSpecialVar_0x8004 = 0;
EWRAM_DATA u16 gSpecialVar_0x8005 = 0;
EWRAM_DATA u16 gSpecialVar_0x8006 = 0;
EWRAM_DATA u16 gSpecialVar_0x8007 = 0;
EWRAM_DATA u16 gSpecialVar_0x8008 = 0;
EWRAM_DATA u16 gSpecialVar_0x8009 = 0;
EWRAM_DATA u16 gSpecialVar_0x800A = 0;
EWRAM_DATA u16 gSpecialVar_0x800B = 0;
EWRAM_DATA u16 gSpecialVar_Result = 0;
EWRAM_DATA u16 gSpecialVar_LastTalked = 0;
EWRAM_DATA u16 gSpecialVar_Facing = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxId = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxPos = 0;
EWRAM_DATA u16 gSpecialVar_Unused_0x8014 = 0;
EWRAM_DATA static u8 sSpecialFlags[SPECIAL_FLAGS_SIZE] = {0};

#if TESTING
#define TEST_FLAGS_SIZE     1
#define TEST_VARS_SIZE      8
EWRAM_DATA static u8 sTestFlags[TEST_FLAGS_SIZE] = {0};
EWRAM_DATA static u16 sTestVars[TEST_VARS_SIZE] = {0};
#endif // TESTING

extern u16 *const gSpecialVars[];

const u16 gBadgeFlags[NUM_BADGES] =
{
    FLAG_BADGE01_GET,
    FLAG_BADGE02_GET,
    FLAG_BADGE03_GET,
    FLAG_BADGE04_GET,
    FLAG_BADGE05_GET,
    FLAG_BADGE06_GET,
    FLAG_BADGE07_GET,
    FLAG_BADGE08_GET,
};

void InitEventData(void)
{
    memset(gSaveBlock1Ptr->flags, 0, sizeof(gSaveBlock1Ptr->flags));
    memset(gSaveBlock1Ptr->vars, 0, sizeof(gSaveBlock1Ptr->vars));
    memset(sSpecialFlags, 0, sizeof(sSpecialFlags));
}

void ClearTempFieldEventData(void)
{
    memset(&gSaveBlock1Ptr->flags[TEMP_FLAGS_START / 8], 0, TEMP_FLAGS_SIZE);
    memset(&gSaveBlock1Ptr->vars[TEMP_VARS_START - VARS_START], 0, TEMP_VARS_SIZE);
    FlagClear(FLAG_SYS_ENC_UP_ITEM);
    FlagClear(FLAG_SYS_ENC_DOWN_ITEM);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_CTRL_OBJ_DELETE);
    FlagClear(FLAG_NURSE_UNION_ROOM_REMINDER);
}

void ClearDailyFlags(void)
{
    memset(&gSaveBlock1Ptr->flags[DAILY_FLAGS_START / 8], 0, DAILY_FLAGS_SIZE);
}

void DisableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0;
    *nationalDexVar = 0;
    FlagClear(FLAG_SYS_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.mode = DEX_MODE_HOENN;
    gSaveBlock2Ptr->pokedex.order = 0;
    ResetPokedexScrollPositions();
}

void EnableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0xDA;
    *nationalDexVar = 0x302;
    FlagSet(FLAG_SYS_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.mode = DEX_MODE_NATIONAL;
    gSaveBlock2Ptr->pokedex.order = 0;
    ResetPokedexScrollPositions();
}

bool32 IsNationalPokedexEnabled(void)
{
    if (gSaveBlock2Ptr->pokedex.nationalMagic == 0xDA && VarGet(VAR_NATIONAL_DEX) == 0x302 && FlagGet(FLAG_SYS_NATIONAL_DEX))
        return TRUE;
    else
        return FALSE;
}

void MigrateNationalPokedex(void)
{
    if (!FlagGet(FLAG_NATIONAL_DEX_MIGRATION_COMPLETE) || IsNationalPokedexEnabled())
    {
        if (VarGet(VAR_NEWBARKTOWN_LABSTATE) <= 1 && CalculatePlayerPartyCount() == 0)
            FlagClear(FLAG_SYS_POKEMON_GET);

        DisableNationalPokedex();
        FlagSet(FLAG_NATIONAL_DEX_MIGRATION_COMPLETE);
    }
}

struct InfiniteHeldItemMigration
{
    enum Item item;
    u16 obtainedFlag;
};

static const struct InfiniteHeldItemMigration sInfiniteHeldItemMigrations[] =
{
    { ITEM_NORMALITE, FLAG_ITEM_TOHJOFALLS_HEART_SCALE },
    { ITEM_FIRETITE,  FLAG_MTMORTAR_DEPTHS_FIRETITE },
    { ITEM_WATERTITE, FLAG_ITEM_WHIRL_ISLANDS_B2F_CALCIUM },
    { ITEM_ELECTRITE, FLAG_RAILWAY_ELECTRITE },
    { ITEM_GRASSTITE, FLAG_HIDE_GRASSTITE },
    { ITEM_ICETITE,   FLAG_ICEPATH_DEPTHS_FROSLASSITE },
    { ITEM_FIGHTITE,  FLAG_ITEM_DARKCAVE2_BLACK_FLUTE },
    { ITEM_POISONTITE, FLAG_HIDE_POISOTITE },
    { ITEM_GROUNDITE, FLAG_ITEM_UNION_CAVE_ETHER },
    { ITEM_FLYINGITE, FLAG_CIANWOOD_FLYINGITE },
    { ITEM_PSYCHITE,  FLAG_ROUTE42_PSYCHITE },
    { ITEM_BUGTITE,   FLAG_ITEM_NATIONAL_PARK_HERACRONITE },
    { ITEM_ROCKTITE,  FLAG_ITEM_ROUTE46_REVIVE },
    { ITEM_GHOSTITE,  FLAG_HIDE_GHOSTITE },
    { ITEM_DRAGOTITE, FLAG_ITEM_DRAGONSDEN2_PP_MAX },
    { ITEM_DARKTITE,  FLAG_HIDE_DARKTITE },
    { ITEM_STEELTITE, FLAG_ITEM_VICTORYROAD2_MAX_REVIVE },
};

static bool32 TryRestoreInfiniteHeldItem(enum Item item)
{
    if (CheckBagHasItem(item, 1))
        return TRUE;

    return AddHeldItemToBag(item);
}

void MigrateInfiniteHeldItems(void)
{
    u32 i;
    bool32 migrationComplete = TRUE;

    if (FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE))
        return;

    // AddBagItem targets the Pyramid bag during a challenge, so retry later instead.
    if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE
     || FlagGet(FLAG_STORING_ITEMS_IN_PYRAMID_BAG))
        return;

    for (i = 0; i < ARRAY_COUNT(sInfiniteHeldItemMigrations); i++)
    {
        const struct InfiniteHeldItemMigration *migration = &sInfiniteHeldItemMigrations[i];

        if (FlagGet(migration->obtainedFlag) && !TryRestoreInfiniteHeldItem(migration->item))
            migrationComplete = FALSE;
    }

    if (FlagGet(FLAG_HIDE_LAKE_OF_RAGE_GYARADOS)
     && !CheckBagHasItem(ITEM_RED_SCALE, 1)
     && !TryRestoreInfiniteHeldItem(ITEM_FAIRYTITE))
        migrationComplete = FALSE;

    if (VarGet(VAR_NEWBARKTOWN_LABSTATE) >= 8
     && !TryRestoreInfiniteHeldItem(ITEM_BONDSTONE))
        migrationComplete = FALSE;

    if (migrationComplete)
        FlagSet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
}

void MigrateInfestationSludgeWaveFlags(void)
{
    bool32 hasInfestation;
    bool32 hasSludgeWave;

    if (FlagGet(FLAG_TM_PICKUP_MIGRATION_COMPLETE))
        return;

    if (FlagGet(FLAG_ITEM_OLIVINE_TM_SHOCKWAVE))
    {
        hasInfestation = CheckBagHasItem(ITEM_TM_INFESTATION, 1);
        hasSludgeWave = CheckBagHasItem(ITEM_TM_SLUDGE_WAVE, 1);

        if (hasInfestation)
            FlagSet(FLAG_TM_INFESTATION);

        if (!hasSludgeWave)
            FlagClear(FLAG_ITEM_OLIVINE_TM_SHOCKWAVE);
    }

    FlagSet(FLAG_TM_PICKUP_MIGRATION_COMPLETE);
}

void DisableMysteryEvent(void)
{
    FlagClear(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

void EnableMysteryEvent(void)
{
    FlagSet(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

bool32 IsMysteryEventEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

void DisableMysteryGift(void)
{
    FlagClear(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

void EnableMysteryGift(void)
{
    FlagSet(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

bool32 IsMysteryGiftEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

void ClearMysteryGiftFlags(void)
{
    FlagClear(FLAG_MYSTERY_GIFT_DONE);
    FlagClear(FLAG_MYSTERY_GIFT_1);
    FlagClear(FLAG_MYSTERY_GIFT_2);
    FlagClear(FLAG_MYSTERY_GIFT_3);
    FlagClear(FLAG_MYSTERY_GIFT_4);
    FlagClear(FLAG_MYSTERY_GIFT_5);
    FlagClear(FLAG_MYSTERY_GIFT_6);
    FlagClear(FLAG_MYSTERY_GIFT_7);
    FlagClear(FLAG_MYSTERY_GIFT_8);
    FlagClear(FLAG_MYSTERY_GIFT_9);
    FlagClear(FLAG_MYSTERY_GIFT_10);
    FlagClear(FLAG_MYSTERY_GIFT_11);
    FlagClear(FLAG_MYSTERY_GIFT_12);
    FlagClear(FLAG_MYSTERY_GIFT_13);
    FlagClear(FLAG_MYSTERY_GIFT_14);
    FlagClear(FLAG_MYSTERY_GIFT_15);
}

void ClearMysteryGiftVars(void)
{
    VarSet(VAR_GIFT_PICHU_SLOT, 0);
}

void DisableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0);
    FlagClear(FLAG_SYS_RESET_RTC_ENABLE);
}

void EnableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0x920);
    FlagSet(FLAG_SYS_RESET_RTC_ENABLE);
}

bool32 CanResetRTC(void)
{
    if (FlagGet(FLAG_SYS_RESET_RTC_ENABLE) && VarGet(VAR_RESET_RTC_ENABLE) == 0x920)
        return TRUE;
    else
        return FALSE;
}

u16 *GetVarPointer(u16 id)
{
    if (id < VARS_START)
        return NULL;
    else if (id < SPECIAL_VARS_START)
        return &gSaveBlock1Ptr->vars[id - VARS_START];
#if TESTING
    else if (id >= TESTING_VARS_START)
        return &sTestVars[id - TESTING_VARS_START];
#endif // TESTING
    else
        return gSpecialVars[id - SPECIAL_VARS_START];
}

u16 VarGet(u16 id)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return id;
    return *ptr;
}

u16 VarGetIfExist(u16 id)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return 65535;
    return *ptr;
}

bool8 VarSet(u16 id, u16 value)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return FALSE;
    *ptr = value;
    return TRUE;
}

u16 VarGetObjectEventGraphicsId(u8 id)
{
    return VarGet(VAR_OBJ_GFX_ID_0 + id);
}

u8 *GetFlagPointer(u16 id)
{
    if (id == 0)
        return NULL;
    else if (id < SPECIAL_FLAGS_START)
        return &gSaveBlock1Ptr->flags[id / 8];
#if TESTING
    else if (id >= TESTING_FLAGS_START)
        return &sTestFlags[(id - TESTING_FLAGS_START) / 8];
#endif // TESTING
    else
        return &sSpecialFlags[(id - SPECIAL_FLAGS_START) / 8];
}

u8 FlagSet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u8 FlagToggle(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr ^= 1 << (id & 7);
    return 0;
}

u8 FlagClear(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 FlagGet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);

    if (!ptr)
        return FALSE;

    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    return TRUE;
}
