#include "global.h"
#include "new_game.h"
#include "derby.h"
#include "random.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "level_scaling.h"
#include "play_time.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "clock.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "constants/flags.h"
#include "money.h"
#include "trainer_hill.h"
#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
#include "apprentice.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "replay_options.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
#include "candy_jar.h"
#include "mystery_gift.h"
#include "union_room_chat.h"
#include "constants/map_groups.h"
#include "constants/items.h"
#include "constants/party_menu.h"
#include "difficulty.h"
#include "follower_npc.h"
#include "config/battle.h"
#include "constants/heal_locations.h"
#include "main_menu.h"
#include "constants/flags.h"

extern const u8 EventScript_ResetAllMapFlags[];

static void ClearFrontierRecord(void);
static void WarpToTruck(void);
static void ResetMiniGamesRecords(void);
static void ResetItemFlags(void);
static void ResetDexNav(void);
static void SetDefaultPartyMenuStyle(void);
static u8 GetCurrentPartyMenuStyle(void);
static void TryInitializeClockFromRtc(void);

struct NewGameOptions
{
    enum DifficultyLevel difficulty;
    u16 overworldSpeed;
    u8 battleSpeed;
    u8 partyMenuStyle;
    enum ReplayBattleFormat battleFormat;
};

EWRAM_DATA bool8 gDifferentSaveFile = FALSE;
EWRAM_DATA bool8 gEnableContestDebugging = FALSE;

static const struct ContestWinner sContestWinnerPicDummy =
{
    .monName = _(""),
    .trainerName = _("")
};

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

u32 GetTrainerId(u8 *trainerId)
{
    return (trainerId[3] << 24) | (trainerId[2] << 16) | (trainerId[1] << 8) | (trainerId[0]);
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 16) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

// L=A isnt set here for some reason.
static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_STEREO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SET;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_NORMAL;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsUiAnimationsOff = FALSE;
    gSaveBlock2Ptr->optionsFollowers = TRUE;
    gSaveBlock2Ptr->optionsAutorun = TRUE;
    gSaveBlock2Ptr->optionsFont = 0;
    gSaveBlock2Ptr->optionsLevelCaps = B_EXP_CAP_TYPE;
    gSaveBlock2Ptr->optionsTrainerLevelScaling = LEVEL_SCALING_OPTION_OFF;
    gSaveBlock2Ptr->optionsWildLevelScaling = LEVEL_SCALING_OPTION_OFF;
    gSaveBlock2Ptr->optionsFastIntroNoSlide = TRUE;
    gSaveBlock2Ptr->optionsFastMegas = B_FAST_MEGAS;
    gSaveBlock2Ptr->optionsFastWeather = B_FAST_WEATHER;
    gSaveBlock2Ptr->optionsSurfMusic = OW_SURF_MUSIC;
    gSaveBlock2Ptr->optionsBattleSpeed = OPTIONS_BATTLE_SCENE_2X;
    VarSet(VAR_BATTLE_SPEED, OPTIONS_BATTLE_SCENE_2X);
    SetDefaultPartyMenuStyle();
               
}

static void SetDefaultPartyMenuStyle(void)
{
    gSaveBlock1Ptr->optionsPartyMenuStyle = PARTY_MENU_DEFAULT_OPTION;
    gSaveBlock1Ptr->optionsPartyMenuStyleMagic = PARTY_MENU_OPTION_SAVE_MAGIC;
}

static u8 GetCurrentPartyMenuStyle(void)
{
    if (gSaveBlock1Ptr->optionsPartyMenuStyleMagic == PARTY_MENU_OPTION_SAVE_MAGIC
     && gSaveBlock1Ptr->optionsPartyMenuStyle < PARTY_MENU_OPTION_COUNT)
        return gSaveBlock1Ptr->optionsPartyMenuStyle;

    if (gSaveBlock2Ptr->unused1)
        return PARTY_MENU_OPTION_BW;

    return PARTY_MENU_DEFAULT_OPTION;
}

static void ClearPokedexFlags(void)
{
    gUnusedPokedexU8 = 0;
    memset(&gSaveBlock1Ptr->dexCaught, 0, sizeof(gSaveBlock1Ptr->dexCaught));
    memset(&gSaveBlock1Ptr->dexSeen, 0, sizeof(gSaveBlock1Ptr->dexSeen));
}

void ClearAllContestWinnerPics(void)
{
    s32 i;

    ClearContestWinnerPicsInContestHall();

    // Clear Museum paintings
    for (i = MUSEUM_CONTEST_WINNERS_START; i < NUM_CONTEST_WINNERS; i++)
        gSaveBlock1Ptr->contestWinners[i] = sContestWinnerPicDummy;
}

static void ClearFrontierRecord(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->frontier, sizeof(gSaveBlock2Ptr->frontier));

    gSaveBlock2Ptr->frontier.opponentNames[0][0] = EOS;
    gSaveBlock2Ptr->frontier.opponentNames[1][0] = EOS;
}

static void WarpToTruck(void)
{
    SetWarpDestination(MAP_GROUP(MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F), WARP_ID_NONE, 1, 6);
    WarpIntoMap();
}


void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetPokeblockScrollPositions();
}

void NewGameInitData(void)
{
    struct NewGameOptions options =
    {
        .difficulty = GetCurrentDifficultyLevel(),
        .overworldSpeed = VarGet(VAR_OVERWORLD_SPEEDUP),
        .battleSpeed = VarGet(VAR_BATTLE_SPEED),
        .partyMenuStyle = GetCurrentPartyMenuStyle(),
        .battleFormat = GetReplayBattleFormat(),
    };

    if (options.overworldSpeed > OPTIONS_OVERWORLD_SPEED_4X)
        options.overworldSpeed = OPTIONS_OVERWORLD_SPEED_1X;
    if (options.battleSpeed > OPTIONS_BATTLE_SCENE_3X)
        options.battleSpeed = OPTIONS_BATTLE_SCENE_1X;

    if ((gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
     && RtcGetErrorStatus() != 0)
        RtcReset();

    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    SetDefaultPartyMenuStyle();
    ClearSav3();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    FlagSet(FLAG_NATIONAL_DEX_MIGRATION_COMPLETE);
    FlagSet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
    FlagSet(FLAG_TM_PICKUP_MIGRATION_COMPLETE);
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    SetCoins(0);
    GetNewDerby();
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    DeactivateAllRoamers();
    gSaveBlock1Ptr->registeredItemCompat = ITEM_NONE;
    memset(gSaveBlock1Ptr->registeredItems, 0, sizeof(gSaveBlock1Ptr->registeredItems));
    memset(gSaveBlock1Ptr->registeredShortcutTypes, REGISTERED_SHORTCUT_ITEM, sizeof(gSaveBlock1Ptr->registeredShortcutTypes));
    memset(gSaveBlock1Ptr->registeredPokegearApps, 0, sizeof(gSaveBlock1Ptr->registeredPokegearApps));
    gSaveBlock1Ptr->registeredShortcutsMagic = REGISTERED_SHORTCUTS_SAVE_MAGIC;
    gSaveBlock1Ptr->registeredShortcutsMagicInv = REGISTERED_SHORTCUTS_SAVE_MAGIC_INV;
    ClearBag();
    NewGameInitPCItems();
    ClearPokeblocks();
    ClearDecorationInventories();
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    WarpToTruck();
    RunScriptImmediately(EventScript_ResetAllMapFlags);
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetContestLinkResults();
    SetCurrentDifficultyLevel(options.difficulty);
    VarSet(VAR_OVERWORLD_SPEEDUP, options.overworldSpeed);
    gSaveBlock2Ptr->optionsBattleSpeed = options.battleSpeed;
    VarSet(VAR_BATTLE_SPEED, options.battleSpeed);
    gSaveBlock1Ptr->optionsPartyMenuStyle = options.partyMenuStyle;
    gSaveBlock1Ptr->optionsPartyMenuStyleMagic = PARTY_MENU_OPTION_SAVE_MAGIC;
    SetReplayBattleFormat(options.battleFormat);
    VarSet(VAR_BATTLE_FACILITY_BGM, 0);
    ResetItemFlags();
    ResetDexNav();
    ClearFollowerNPCData();
    SetLastHealLocationWarp(HEAL_LOCATION_NEW_BARK_TOWN_PLAYERS_HOUSE_2F);
    TryInitializeClockFromRtc();
}

static void TryInitializeClockFromRtc(void)
{
    if (!RtcInitLocalTimeFromRtc())
        return;

    InitTimeBasedEvents();
    FlagSet(FLAG_SET_WALL_CLOCK);
    VarSet(VAR_NEWBARK_TOWN_STATE, 1);
}

static void ResetMiniGamesRecords(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    SetCandyJarExp(&gSaveBlock3Ptr->candyJarExp, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}

static void ResetItemFlags(void)
{
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
    memset(&gSaveBlock3Ptr->itemFlags, 0, sizeof(gSaveBlock3Ptr->itemFlags));
#endif
}

static void ResetDexNav(void)
{
#if USE_DEXNAV_SEARCH_LEVELS == DEXNAV_SEARCH_LEVELS_PER_SPECIES
    memset(gSaveBlock3Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock3Ptr->dexNavSearchLevels));
#elif USE_DEXNAV_SEARCH_LEVELS == DEXNAV_SEARCH_LEVELS_REGISTERED_SPECIES
    VarSet(DN_VAR_SEARCH_LEVEL, 0);
#endif
    gSaveBlock3Ptr->dexNavChain = 0;
}
