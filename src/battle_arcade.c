#include "global.h"
#include "achievements.h"
#include "battle.h"
#include "battle_arcade.h"
#include "battle_dome.h"
#include "battle_main.h"
#include "battle_partner.h"
#include "battle_records.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "battle_transition.h"
#include "battle_util.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_poison.h"
#include "field_weather.h"
#include "frontier_util.h"
#include "gba/defines.h"
#include "gba/macro.h"
#include "gba/types.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "gym_leader_rematch.h"
#include "international_string_util.h"
#include "item.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "money.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon_icon.h"
#include "random.h"
#include "scanline_effect.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "tv.h"
#include "window.h"
#include "constants/battle_arcade.h"
#include "constants/battle_frontier.h"
#include "constants/field_specials.h"
#include "constants/frontier_util.h"
#include "constants/hold_effects.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/party_menu.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/weather.h"

struct GameBoardState
{
    MainCallback savedCallback;
    u8 loadState;
    u8 gameMode;
    u8 monIconSpriteId[2][MAX_FRONTIER_PARTY_SIZE];
    u16 timer;
    u8 cursorPosition;
    u8 eventIconSpriteId[ARCADE_GAME_BOARD_SPACES];
    u8 countdownPanelSpriteId[ARCADE_GAME_BOARD_SPACES];
    u8 cursorPaletteNum[2];
};

// Arcade Challenge Functions
void CallBattleArcadeFunc(void);
static void InitArcadeChallenge(void);
static void ResetCursorPositionOnSaveblock(void);
static void SetCursorPosition(u32);
static void SaveCursorPositionToSaveblock(void);
static u32 GetCursorPosition(void);
static void ResetCursorSpeed(void);
static void ClearCursorRandomMode(void);
static void TakePlayerHeldItems(void);
static void GenerateItemsToBeGiven(void);
static u32 GenerateItemOrBerry(u32);
static u32 GetCategorySize(u32);
static u32 GetGroupIdFromStreak(void);
static const u32 (*GetCategoryGroups(u32))[ARCADE_BERRY_GROUP_SIZE];
static void GetArcadeData(void);
static u16 GetCurrentStreak(void);
static void SetArcadeData(void);
static void SetArcadeBattleWon(void);
static void IncrementCurrentStreak(void);
static void SaveCurrentStreak(void);
static void SaveArcadeChallenge(void);
static void BufferRocketArcadePrize(void);
static void AwardRocketArcadePrize(void);
static void DoubleDownRocketArcadePrize(void);
static void ClearRocketArcadePrize(void);
static void CheckRocketArcadeDoubleDown(void);
static u32 GetRocketArcadePrize(void);
static u32 GetRocketArcadePayoutIndex(void);
static bool32 IsArcadeBrainBattle(void);
static void BufferEarnedArcadePrint(void);
static u32 GetEarnedArcadePrint(void);
static bool32 ShouldGetGoldPrint(u32);
static bool32 ShouldGetSilverPrint(u32);
static bool32 ShouldGetPrint(u32, u32, u32);
static void TakeEnemyHeldItems(void);
static void GetArcadeBrainStatus(void);
static void ArcadeBattleCleanup(void);
static void ResetWeatherPostBattle(void);
static void ReturnPartyToOwner(void);
static bool32 HaveMonsBeenSwapped(void);
static void ResetLevelsToOriginal(void);
static void ResetSketchedMoves(void);
static void StartArcadeGameBoardFromOverworld(void);
static void GenerateArcadeOpponent(void);
u32 GetArcadePrintCount(void);
static void SetArcadeBrainObjectEvent(void);
static void BufferPrintFromCurrentStreak(void);
static u32 GetPendingArcadePrint(void);
void ShowArcadeRecordsFromOverworld(void);
void DoArcadeTrainerBattle(void);
static void SetArcadeBattleFlags(void);
static u32 GetPerformancePoints(void);
void CalculateAndSetPerformancePoints(void);
void ResetPerformancePoints(void);
void SetPerformancePoints(u32);
static u32 CalculatePerformancePoints(void);
static void HandleArcadeTrainerBattleEnd(void);
static void Task_StartArcadeBattleAfterTransition(u8);

// Arcade Game Board Front End
static void Task_OpenGameBoard(u8);
static void GameBoard_Init(MainCallback);
static void GameBoard_SetupCB(void);
static bool8 GameBoard_InitBgs(void);
static bool32 BattleArcade_AllocTilemapBuffers(void);
static void GameBoard_HandleAndShowBgs(void);
static void SetScheduleShowBgs(u32);
static void GameBoard_FadeAndBail(void);
static void Task_GameBoardWaitFadeAndBail(u8);
static bool8 GameBoard_LoadGraphics(void);
static void GameBoard_InitWindows(void);
static void LoadEventPalettes(void);
static void GenerateGameBoard(void);
static void PrintEnemyParty(void);
static void PrintPlayerParty(void);
static void PrintPartyIcons(u32);
static u32 GetHorizontalPositionFromSide(u32);
static struct Pokemon* LoadSideParty(u32);
static void PrintHelpBar(void);
static const u8* GetHelpBarText(void);
static u32 GetGameBoardMode(void);
static void Task_GameBoardWaitFadeIn(u8);
static void Task_GameBoardMainInput(u8);
static void VBlankCB(void);
static void MainCB(void);
static void StartCountdown(void);
static void SetTimerForCountdown(void);
static void SetTimer(u32);
static void PopulateCountdownSprites(void);
static void CalculatePanelPosition(u32, u32*, u32*);
static u32 CreateCountdownPanel(u32, u32);
static void Task_GameBoard_Countdown(u8);
static void PopulateEventSprites(void);
static void LoadTileSpriteSheets(void);
static const u32* GetEventGfx(u32);
static u8 CreateEventSprite(u32, u32, u32);
static const u16 GetTileTag(u32);
static void StartGame(void);
static void SetTimerForGame(void);
static void InitCursorPositionFromSaveblock(void);
static void CreateGameBoardCursor(void);
static void SpriteCB_Cursor(struct Sprite*);
static void ChangeCursorColor(struct Sprite*);
static u32 ReturnNextCursorPalette(u32);
static void ChangeCursorSpritePosition(struct Sprite*);
static void DestroyCountdownPanels(void);
static void Task_GameBoard_Game(u8);
static u32 GetGameBoardTimer(void);
static void IncrementGameBoardMode(void);
static bool32 ShouldCursorMove(u32);
static u32 ReturnCursorWait(u32);
static void ChangeCursorPosition(void);
static bool32 IsCursorInRandomMode(void);
static bool32 IsGameBoardTimerEmpty(void);
static void DecrementGameBoardTimer(void);
static void HandleFinishMode(void);
static void SetTimerForFinish(void);
static void SelectGameBoardSpace(u32*, u32*);
static void HandleGameBoardResult(u32, u32);
static void BufferImpactedName(u8*, u32);
static u32 GetImpactedTrainerId(u32);
static void SetGameBoardToChosenEvent(u32, u32);
static void StoreEventToVar(u32);
static void StoreImpactedSideToVar(u32);
static void DestroyEventSprites(void);
static void Task_GameBoard_CleanUp(u8);
static void Task_GameBoardWaitFadeAndExitGracefully(u8);
static void GameBoard_FreeResources(void);

// Arcade Game Board Back End Init
static u32 GenerateImpact(void);
static u32 ConvertPerformanceToImpactBracket(void);
static u32 GenerateEvent(u32);
static u32 GenerateRandomBetweenBounds(u32);
static s32 GetPanelUpperBound(u32);
static s32 GetPanelLowerBound(u32);
static bool32 IsEventValidDuringBattleOrStreak(u32, u32);
static bool32 IsEventBanned(u32);
static bool32 IsEventValidDuringCurrentBattle(u32);
static bool32 IsEventValidDuringCurrentStreak(u32);
static u32 GetChallengeNumIndex(void);
static u32 GetChallengeNum(void);

// Arcade Game Board Back End Resolve
static bool32 DoGameBoardResult(u32, u32);
static bool32 BattleArcade_DoLowerHP(u32);
static bool32 BattleArcade_DoPoison(u32);
static bool32 BattleArcade_DoParalyze(u32);
static bool32 BattleArcade_DoBurn(u32);
static bool32 BattleArcade_DoSleep(u32);
static bool32 BattleArcade_DoFreeze(u32);
bool8 DoesTypePreventStatus(u16 species, u32 status);
bool8 DoesAbilityPreventStatus(struct Pokemon *mon, u32 status);
static bool32 BattleArcade_DoStatusAilment(u32, u32);
static void InitalizePartyIndex(u32*);
static bool32 IsStatusSleepOrFreeze(u32);
static void ShufflePartyIndex(u32*);
static bool32 BattleArcade_DoGiveBerry(u32);
static bool32 BattleArcade_DoGiveItem(u32);
static bool32 BattleArcade_DoGive(u32, u32);
static void BufferGiveString(u32);
static bool32 BattleArcade_DoLevelUp(u32);
static u32 CalculateAndSaveNewLevel(u32);
static bool32 BattleArcade_DoSun(void);
static bool32 BattleArcade_DoRain(void);
static bool32 BattleArcade_DoSand(void);
static bool32 BattleArcade_DoHail(void);
static bool32 BattleArcade_DoFog(void);
static bool32 BattleArcade_DoWeather(u32);
static bool32 BattleArcade_DoTrickRoom(void);
static bool32 BattleArcade_DoSwap(void);
static bool32 BattleArcade_DoSpeedUp(void);
static bool32 BattleArcade_DoSpeedDown(void);
static bool32 BattleArcade_ChangeSpeed(u32);
static u32 GetCursorSpeed(void);
static void SetCursorSpeed(u32);
static bool32 BattleArcade_DoRandom(void);
static void SetCursorRandomMode(void);
static bool32 BattleArcade_DoGiveBPSmall(void);
static bool32 BattleArcade_DoGiveBPBig(void);
static bool32 BattleArcade_DoNoBattle(void);
static bool32 BattleArcade_DoNoEvent(void);

// Arcade Records Window
static void Task_OpenArcadeRecord(u8);
static void ArcadeRecords_Init(MainCallback);
static void ArcadeRecords_SetupCB(void);
static bool8 ArcadeRecords_InitBgs(void);
static bool32 ArcadeRecords_AllocTilemapBuffers(void);
static void ArcadeRecord_HandleAndShowBgs(void);
static void ArcadeRecord_SetScheduleShowBgs(u32);
static void ArcadeRecord_FadeAndBail(void);
static void Task_ArcadeRecordWaitFadeAndBail(u8);
static bool8 ArcadeRecord_LoadGraphics(void);
static void ArcadeRecord_InitWindows(void);
static void DisplayRecordsText(void);
static void GenerateRecordText(void);
static void HandleHeader(u32, u32, u32, u32, u8*, u32, u32);
static const u8 *BattleArcade_GenerateRecordName(void);
static const u8 *BattleArcade_GetRecordName(void);
static void HandleRecord(u32, u32, u32, u32, u8*, u32, u32);
static void PrintRecordHeaderLevelRecord(u32, u32, u32, u32, u8*, u32, u32, u32, u32);
static u32 CalculateRecordRowYPosition(u32);
static void PrintRecordHeader(u32, u32, u32, u32, u8*, u32, u32, u32, u32);
static const u8 *BattleArcade_GetRecordHeaderName(u32, u32);
static void PrintRecordLevelMode(u32, u32, u32, u32, u8*, u32, u32, u32, u32);
static const u8 *BattleArcade_GetLevelText(u32);
static void PrintRecord(u32, u32, u32, u32, u8*, u32, u32, u32, u32);
static u32 GetRecordValue(u32, u32);
static void Task_ArcadeRecordWaitFadeIn(u8);
static void Task_RecordsWaitForKeyPress(u8);
static void Task_ArcadeRecord_CleanUp(u8);
static void Task_ArcadeRecordWaitFadeAndExitGracefully(u8);
static void ArcadeRecord_FreeResources(void);

static EWRAM_DATA struct GameBoardState *sGameBoardState = NULL;
static EWRAM_DATA u8 *sBgTilemapBuffer[BG_BOARD_COUNT] = {NULL, NULL, NULL, NULL};

static void (* const sBattleArcadeFuncs[])(void) =
    {
        [ARCADE_FUNC_INIT]                   = InitArcadeChallenge,
        [ARCADE_FUNC_GET_DATA]               = GetArcadeData,
        [ARCADE_FUNC_SET_DATA]               = SetArcadeData,
        [ARCADE_FUNC_SAVE]                   = SaveArcadeChallenge,
        [ARCADE_FUNC_GENERATE_OPPONENT]      = GenerateArcadeOpponent,
        [ARCADE_FUNC_TAKE_ENEMY_ITEMS]       = TakeEnemyHeldItems,
        [ARCADE_FUNC_PLAY_GAME_BOARD]        = StartArcadeGameBoardFromOverworld,
        [ARCADE_FUNC_BATTLE_CLEAN_UP]        = ArcadeBattleCleanup,
        [ARCADE_FUNC_SET_BATTLE_WON]         = SetArcadeBattleWon,
        [ARCADE_FUNC_GIVE_BATTLE_POINTS]     = AwardRocketArcadePrize,
        [ARCADE_FUNC_CHECK_SYMBOL]           = BufferEarnedArcadePrint,
        [ARCADE_FUNC_GET_PRINT_FROM_STREAK]  = BufferPrintFromCurrentStreak,
        [ARCADE_FUNC_CHECK_BRAIN_STATUS]     = GetArcadeBrainStatus,
        [ARCADE_FUNC_SET_BRAIN_OBJECT]       = SetArcadeBrainObjectEvent,
        [ARCADE_FUNC_RECORDS]                = ShowArcadeRecordsFromOverworld,
        [ARCADE_FUNC_TAKE_PLAYER_HELD_ITEM]  = TakePlayerHeldItems,
        [ARCADE_FUNC_BUFFER_PRIZE]           = BufferRocketArcadePrize,
        [ARCADE_FUNC_AWARD_PRIZE]            = AwardRocketArcadePrize,
        [ARCADE_FUNC_DOUBLE_DOWN]            = DoubleDownRocketArcadePrize,
        [ARCADE_FUNC_CLEAR_PRIZE]            = ClearRocketArcadePrize,
        [ARCADE_FUNC_CHECK_DOUBLE_DOWN]      = CheckRocketArcadeDoubleDown,
    };

static const u32 sStreakFlags[FRONTIER_MODE_COUNT][FRONTIER_LVL_MODE_COUNT] =
    {
        [FRONTIER_MODE_SINGLES]     = {STREAK_ARCADE_SINGLES_50,      STREAK_ARCADE_SINGLES_OPEN},
        [FRONTIER_MODE_DOUBLES]     = {STREAK_ARCADE_DOUBLES_50,      STREAK_ARCADE_DOUBLES_OPEN},
        [FRONTIER_MODE_LINK_MULTIS] = {STREAK_ARCADE_LINK_MULTIS_50,  STREAK_ARCADE_LINK_MULTIS_OPEN},
    };

static const u32 sStreakMasks[FRONTIER_MODE_COUNT][FRONTIER_LVL_MODE_COUNT] =
    {
        [FRONTIER_MODE_SINGLES]     = {~STREAK_ARCADE_SINGLES_50,      ~STREAK_ARCADE_SINGLES_OPEN},
        [FRONTIER_MODE_DOUBLES]     = {~STREAK_ARCADE_DOUBLES_50,      ~STREAK_ARCADE_DOUBLES_OPEN},
        [FRONTIER_MODE_LINK_MULTIS] = {~STREAK_ARCADE_LINK_MULTIS_50,  ~STREAK_ARCADE_LINK_MULTIS_OPEN},
    };

static const u32 sArcadePerformanceTable[IMPACT_PERFORMANCE_TABLE_SIZE][3] =
    {
        [0] = { 8, 6 },
        [1] = { 6, 4 },
        [2] = { 4, 2 },
        [3] = { 0, 0 },
        [4] = { 0, 0 },
    };

static const u8 sArcadeTurnPointTable[IMPACT_PERFORMANCE_TABLE_SIZE][2] =
    {
        { 3, 10 },
        { 5,  6 },
        { 7,  4 },
        { 9,  2 },
        { 10, 0 },
    };

static const u32 sRocketArcadePayouts[] =
{
    4000,
    8000,
    12000,
    24000,
    48000,
    96000,
    384000
};

void CallBattleArcadeFunc(void)
{
    sBattleArcadeFuncs[gSpecialVar_0x8004]();
}

static void InitArcadeChallenge(void)
{
    u32 lvlMode = FRONTIER_SAVEDATA.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    FRONTIER_SAVEDATA.challengeStatus = CHALLENGE_STATUS_SAVING;
    FRONTIER_SAVEDATA.curChallengeBattleNum = 0;
    FRONTIER_SAVEDATA.challengePaused = FALSE;
    FRONTIER_SAVEDATA.disableRecordBattle = FALSE;

    ResetPerformancePoints();
    ResetCursorPositionOnSaveblock();
    ResetCursorSpeed();
    ResetFrontierTrainerIds();
    GenerateItemsToBeGiven();
    ClearRocketArcadePrize();
    FlagSet(FLAG_HIDE_BATTLE_TOWER_OPPONENT);

    if (!(FRONTIER_SAVEDATA.winStreakActiveFlags & sStreakFlags[battleMode][lvlMode]))
        ARCADE_SAVEDATA_CURRENT_STREAK[battleMode][lvlMode] = 0;

    SetDynamicWarp(0, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, WARP_ID_NONE);
    TRAINER_BATTLE_PARAM.opponentA = 0;
}

static void TakePlayerHeldItems(void)
{
    BattleArcade_DoGive(ARCADE_IMPACT_PLAYER, ITEM_NONE);
}

static void ResetCursorPositionOnSaveblock(void)
{
    SetCursorPosition(0);
    SaveCursorPositionToSaveblock();
}

static void SetCursorPosition(u32 value)
{
    sGameBoardState->cursorPosition = value;
}

static void SaveCursorPositionToSaveblock(void)
{
    ARCADE_SAVEDATA_CURSOR.position = GetCursorPosition();
}

static u32 GetCursorPosition(void)
{
    return sGameBoardState->cursorPosition;
}

static void ResetCursorSpeed(void)
{
    ARCADE_SAVEDATA_CURSOR.speed = ARCADE_SPEED_DEFAULT;
}

static void ClearCursorRandomMode(void)
{
    ARCADE_SAVEDATA_CURSOR.isRandom = FALSE;
}

static void GenerateItemsToBeGiven(void)
{
    VarSet(VAR_ARCADE_BERRY,GenerateItemOrBerry(ARCADE_EVENT_GIVE_BERRY));
    VarSet(VAR_ARCADE_ITEM,GenerateItemOrBerry(ARCADE_EVENT_GIVE_ITEM));
}

static u32 GenerateItemOrBerry(u32 type)
{
    u32 heldItem = ITEM_NONE;
    u32 maxGroupSize = GetCategorySize(type);
    u32 groupId = GetGroupIdFromStreak();
    const u32 (*itemGroups)[ARCADE_BERRY_GROUP_SIZE] = GetCategoryGroups(type);

    do
    {
        heldItem = itemGroups[groupId][Random() % maxGroupSize];
    } while (heldItem == ITEM_NONE);

    return heldItem;
}

static u32 GetCategorySize(u32 type)
{
    if (type == ARCADE_EVENT_GIVE_ITEM)
        return ARCADE_ITEM_GROUP_SIZE;
    else
        return ARCADE_BERRY_GROUP_SIZE;
}

static u32 GetGroupIdFromStreak(void)
{
    u32 challengeNum = GetChallengeNum();

    return challengeNum <= 2 ? ARCADE_BERRY_GROUP_1:
    challengeNum <= 6 ? ARCADE_BERRY_GROUP_2:
    ARCADE_BERRY_GROUP_3;
}

static const u32 (*GetCategoryGroups(u32 type))[ARCADE_BERRY_GROUP_SIZE]
{
    static const u32 gameBerries[ARCADE_BERRY_GROUP_COUNT][ARCADE_BERRY_GROUP_SIZE] =
        {
            [ARCADE_BERRY_GROUP_1] =
            {
                ITEM_CHERI_BERRY,
                ITEM_CHESTO_BERRY,
                ITEM_PECHA_BERRY,
                ITEM_RAWST_BERRY,
                ITEM_ASPEAR_BERRY,
                ITEM_PERSIM_BERRY,
                ITEM_SITRUS_BERRY,
                ITEM_LUM_BERRY,
            },
            [ARCADE_BERRY_GROUP_2] =
            {
                ITEM_PERSIM_BERRY,
                ITEM_SITRUS_BERRY,
                ITEM_LUM_BERRY,
            },
            [ARCADE_BERRY_GROUP_3] =
            {
                ITEM_PERSIM_BERRY,
                ITEM_SITRUS_BERRY,
                ITEM_LUM_BERRY,
                ITEM_LIECHI_BERRY,
                ITEM_GANLON_BERRY,
                ITEM_SALAC_BERRY,
                ITEM_PETAYA_BERRY,
                ITEM_APICOT_BERRY,
                ITEM_LANSAT_BERRY,
                ITEM_STARF_BERRY,
            },
        };

    static const u32 gameItems[ARCADE_ITEM_GROUP_COUNT][ARCADE_ITEM_GROUP_SIZE] =
        {
            [ARCADE_ITEM_GROUP_1] =
            {
                ITEM_KINGS_ROCK,
                ITEM_QUICK_CLAW,
                ITEM_BRIGHT_POWDER,
                ITEM_FOCUS_BAND,
                ITEM_LEFTOVERS,
            },
            [ARCADE_ITEM_GROUP_2] =
            {
                ITEM_WHITE_HERB,
                ITEM_SHELL_BELL,
                ITEM_SCOPE_LENS,
            },
            [ARCADE_ITEM_GROUP_3] =
            {
                ITEM_FOCUS_BAND,
                ITEM_LEFTOVERS,
                ITEM_SCOPE_LENS,
                ITEM_CHOICE_BAND
            },
        };

    return (type == ARCADE_EVENT_GIVE_ITEM) ? gameItems : gameBerries;
}

static void GetArcadeData(void)
{
    u32 lvlMode = FRONTIER_SAVEDATA.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
        case 0:
            break;
        case ARCADE_DATA_WIN_STREAK:
            gSpecialVar_Result = GetCurrentStreak();
            break;
        case ARCADE_DATA_WIN_STREAK_ACTIVE:
            gSpecialVar_Result = (!(FRONTIER_SAVEDATA.winStreakActiveFlags & sStreakFlags[battleMode][lvlMode]));
            break;
    }
}

static bool32 IsMonFainted(struct Pokemon *mon)
{
    if (GetMonData(mon,MON_DATA_HP) > 0)
        return FALSE;

    return TRUE;
}

static bool32 DoesMonHaveStatus(struct Pokemon *mon)
{
    u32 ailment = GetAilmentFromStatus(GetMonData(mon, MON_DATA_STATUS));

    if (ailment == AILMENT_NONE)
        return FALSE;

    return TRUE;
}

u32 GetPerformancePoints(void)
{
    return VarGet(VAR_ARCADE_PERFORMANCE_POINTS);
}

void SetPerformancePoints(u32 points)
{
    VarSet(VAR_ARCADE_PERFORMANCE_POINTS,points);
}

void ResetPerformancePoints(void)
{
    SetPerformancePoints(0);
}

void CalculateAndSetPerformancePoints(void)
{
    SetPerformancePoints(CalculatePerformancePoints());
}

static u32 CalculatePerformancePoints(void)
{
    u32 faintedCount = 0;
    u32 statusCount = 0;
    u32 points = 0;
    u32 turn = gBattleResults.battleTurnCounter;
    u32 partyIndex, tableIndex;
    struct Pokemon *playerMon;

    for (partyIndex = 0; partyIndex < MAX_FRONTIER_PARTY_SIZE; partyIndex++)
    {
        playerMon = &gPlayerParty[partyIndex];

        if (!IsMonValidSpecies(playerMon))
            break;

        if (IsMonFainted(playerMon))
            faintedCount++;

        if (DoesMonHaveStatus(playerMon))
            statusCount++;
    }
    // TODO Add function to check the partner's party for Multi Battles

    points += sArcadePerformanceTable[statusCount][0];
    points += sArcadePerformanceTable[faintedCount][1];

    for (tableIndex = 0; tableIndex < IMPACT_PERFORMANCE_TABLE_SIZE; tableIndex++)
    {
        if (turn < sArcadeTurnPointTable[tableIndex][0])
        {
            points += sArcadeTurnPointTable[tableIndex][1];
            break;
        }
    }
    return points;
}

u16 GetCurrentStreak(void)
{
    u8 lvlMode = FRONTIER_SAVEDATA.lvlMode;
    u32 battleMode = (VarGet(VAR_FRONTIER_BATTLE_MODE));
    u32 streak = ARCADE_SAVEDATA_CURRENT_STREAK[battleMode][lvlMode];

    if (streak > MAX_STREAK)
        return MAX_STREAK;
    else
        return streak;
}

static void SetArcadeData(void)
{
    u32 lvlMode = FRONTIER_SAVEDATA.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
        case 0:
            break;
        case ARCADE_DATA_WIN_STREAK:
            FRONTIER_SAVEDATA.curChallengeBattleNum = gSpecialVar_0x8006;
            break;
        case ARCADE_DATA_WIN_STREAK_ACTIVE:
            if (gSpecialVar_0x8006)
                FRONTIER_SAVEDATA.winStreakActiveFlags |= sStreakFlags[battleMode][lvlMode];
            else
                FRONTIER_SAVEDATA.winStreakActiveFlags &= sStreakMasks[battleMode][lvlMode];
            break;
    }
}

static void SetArcadeBattleWon(void)
{
    IncrementCurrentStreak();
    SaveCurrentStreak();
    if (FRONTIER_SAVEDATA.arcadeTotalWins < 0xFFFF)
        FRONTIER_SAVEDATA.arcadeTotalWins++;
    Achievement_CheckAll();
    gSpecialVar_Result = ++FRONTIER_SAVEDATA.curChallengeBattleNum;
}

static void IncrementCurrentStreak(void)
{
    u8 lvlMode = FRONTIER_SAVEDATA.lvlMode;
    u32 battleMode = (VarGet(VAR_FRONTIER_BATTLE_MODE));
    u32 currentStreak = ARCADE_SAVEDATA_CURRENT_STREAK[battleMode][lvlMode];

    if (currentStreak < MAX_STREAK)
        ARCADE_SAVEDATA_CURRENT_STREAK[battleMode][lvlMode]++;
}

static void SaveCurrentStreak(void)
{
    u8 lvlMode = FRONTIER_SAVEDATA.lvlMode;
    u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u32 oldStreak = ARCADE_SAVEDATA_RECORD_STREAK[battleMode][lvlMode];
    u32 currentStreak = GetCurrentStreak();

    if (oldStreak >= currentStreak)
        return;

    ARCADE_SAVEDATA_RECORD_STREAK[battleMode][lvlMode] = currentStreak;
    Achievement_CheckAll();
}

static void SaveArcadeChallenge(void)
{
    FRONTIER_SAVEDATA.challengeStatus = gSpecialVar_0x8005;
    VarSet(VAR_TEMP_CHALLENGE_STATUS, 0);
    FRONTIER_SAVEDATA.challengePaused = TRUE;
    SaveGameFrontier();
}

static void BufferRocketArcadePrize(void)
{
    u32 prize = GetRocketArcadePrize();

    ConvertIntToDecimalStringN(gStringVar1, prize, STR_CONV_MODE_LEFT_ALIGN, CountDigits(prize));
}

static void AwardRocketArcadePrize(void)
{
    u32 prize = GetRocketArcadePrize();

    ConvertIntToDecimalStringN(gStringVar2, prize, STR_CONV_MODE_LEFT_ALIGN, CountDigits(prize));
    AddMoney(&gSaveBlock1Ptr->money, prize);
    FRONTIER_SAVEDATA.rocketArcadePendingPrize = 0;
    FlagClear(FLAG_ROCKET_ARCADE_DOUBLED_DOWN);
}

static void DoubleDownRocketArcadePrize(void)
{
    FlagSet(FLAG_ROCKET_ARCADE_DOUBLED_DOWN);
    BufferRocketArcadePrize();
}

static void ClearRocketArcadePrize(void)
{
    FRONTIER_SAVEDATA.rocketArcadePendingPrize = 0;
    FlagClear(FLAG_ROCKET_ARCADE_DOUBLED_DOWN);
}

static void CheckRocketArcadeDoubleDown(void)
{
    gSpecialVar_Result = FlagGet(FLAG_ROCKET_ARCADE_DOUBLED_DOWN);
}

static u32 GetRocketArcadePrize(void)
{
    u32 prize = sRocketArcadePayouts[GetRocketArcadePayoutIndex()];

    if (IsArcadeBrainBattle())
        prize *= 2;

    return prize;
}

static u32 GetRocketArcadePayoutIndex(void)
{
    u32 winStreak = FRONTIER_SAVEDATA.curChallengeBattleNum;

    if (winStreak == 0)
        return 0;

    if (winStreak > ARRAY_COUNT(sRocketArcadePayouts))
        winStreak = ARRAY_COUNT(sRocketArcadePayouts);

    return winStreak - 1;
}

static bool32 IsArcadeBrainBattle(void)
{
    return TRAINER_BATTLE_PARAM.opponentA == TRAINER_FRONTIER_BRAIN;
}

static void BufferEarnedArcadePrint(void)
{
    gSpecialVar_Result = GetEarnedArcadePrint();
}

static u32 GetEarnedArcadePrint(void)
{
    u32 numWins = (GetCurrentStreak());

    if (ShouldGetGoldPrint(numWins))
        return ARCADE_SYMBOL_GOLD;
    else if (ShouldGetSilverPrint(numWins))
        return ARCADE_SYMBOL_SILVER;
    else
        return ARCADE_SYMBOL_NONE;
}
static bool32 ShouldGetGoldPrint(u32 numWins)
{
    return ShouldGetPrint(FLAG_ARCADE_GOLD_PRINT,numWins,ARCADE_GOLD_BATTLE_NUMBER);
}

static bool32 ShouldGetSilverPrint(u32 numWins)
{
    return ShouldGetPrint(FLAG_ARCADE_SILVER_PRINT,numWins,ARCADE_SILVER_BATTLE_NUMBER);
}

static bool32 ShouldGetPrint(u32 print, u32 numWins, u32 battleNum)
{
    if (FlagGet(print))
        return FALSE;

    if (numWins < battleNum)
        return FALSE;

    return TRUE;
}

static void TakeEnemyHeldItems(void)
{
    BattleArcade_DoGive(ARCADE_IMPACT_OPPONENT, ITEM_NONE);
}

static void GetArcadeBrainStatus(void)
{
    if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_LINK_MULTIS
     || FRONTIER_SAVEDATA.curChallengeBattleNum != FRONTIER_STAGES_PER_CHALLENGE - 1)
    {
        gSpecialVar_Result = FRONTIER_BRAIN_NOT_READY;
        return;
    }

    BufferPrintFromCurrentStreak();
}

void ArcadeBattleCleanup(void)
{
    ResetWeatherPostBattle();
    ReturnPartyToOwner();
    ResetLevelsToOriginal();
    ResetSketchedMoves();
    CalculateAndSetPerformancePoints();
    HealPlayerParty();
}

static void ResetWeatherPostBattle(void)
{
    SetSavedWeather(gMapHeader.weather);
    SetCurrentAndNextWeatherNoDelay(GetSavedWeather());
}

static void ReturnPartyToOwner(void)
{
    if (!HaveMonsBeenSwapped())
        return;

    BattleArcade_DoSwap();
}

static void ResetLevelsToOriginal(void)
{
    struct Pokemon *playerMon;
    u32 i, monId;

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        monId = gSaveBlock2Ptr->frontier.selectedPartyMons[i] - 1;

        if (monId >= PARTY_SIZE)
            continue;

        playerMon = &gPlayerParty[i];
        RestoreFrontierPlayerPartyMonLevel(i, monId);
        ScaleFrontierMonToCurrentLevelMode(playerMon);
    }
}

static void ResetSketchedMoves(void)
{
    u8 i, j;
    struct Pokemon *frontierMon;
    struct Pokemon *playerMon;

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        u32 monId = gSaveBlock2Ptr->frontier.selectedPartyMons[i] - 1;

        if (monId >= PARTY_SIZE)
            continue;

        frontierMon = &gSaveBlock1Ptr->playerParty[monId];
        playerMon = &gPlayerParty[i];

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            if (MonKnowsMove(frontierMon, GetMonData(playerMon, MON_DATA_MOVE1+j, NULL)))
                continue;

            SetMonMoveSlot(playerMon, MOVE_SKETCH, j);
            break;
        }
    }
}

static void StartArcadeGameBoardFromOverworld(void)
{
    CreateTask(Task_OpenGameBoard, 0);
}

static void GenerateArcadeOpponent(void)
{
    gBattleScripting.specialTrainerBattleType = FACILITY_BATTLE_ARCADE;
    SetArcadeBattleFlags();

    switch (VarGet(VAR_FRONTIER_BATTLE_MODE))
    {
        case FRONTIER_MODE_SINGLES:
        case FRONTIER_MODE_DOUBLES:
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
            break;
        case FRONTIER_MODE_LINK_MULTIS:
            FillFrontierTrainersParties(FRONTIER_MULTI_PARTY_SIZE);
            gPartnerTrainerId = gSaveBlock2Ptr->frontier.trainerIds[17];
            FillPartnerParty(gPartnerTrainerId);
            break;
    }
}

u32 GetArcadePrintCount(void)
{
    return GetPendingArcadePrint() == ARCADE_SYMBOL_GOLD;
}

static void SetArcadeBrainObjectEvent(void)
{
    SetFrontierBrainObjEventGfx(FRONTIER_FACILITY_ARCADE);
}

static void BufferPrintFromCurrentStreak(void)
{
    gSpecialVar_Result = GetPendingArcadePrint();
}

static u32 GetPendingArcadePrint(void)
{
    u32 currentStreak = GetCurrentStreak();

    if (!FlagGet(FLAG_ARCADE_SILVER_PRINT) && currentStreak >= ARCADE_SILVER_BATTLE_NUMBER - 1)
        return ARCADE_SYMBOL_SILVER;
    if (!FlagGet(FLAG_ARCADE_GOLD_PRINT) && currentStreak >= ARCADE_GOLD_BATTLE_NUMBER - 1)
        return ARCADE_SYMBOL_GOLD;

    return ARCADE_SYMBOL_NONE;
}

void ShowArcadeRecordsFromOverworld(void)
{
    CreateTask(Task_OpenArcadeRecord,0);
}

void DoArcadeTrainerBattle(void)
{
    gBattleScripting.specialTrainerBattleType = FACILITY_BATTLE_ARCADE;
    SetArcadeBattleFlags();
    CreateTask(Task_StartArcadeBattleAfterTransition, 1);
    PlayMapChosenOrBattleBGM(0);
    BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_TOWER));
}

static void HandleArcadeTrainerBattleEnd(void)
{
    if (gSaveBlock2Ptr->frontier.battlesCount < 0xFFFFFF)
    {
        gSaveBlock2Ptr->frontier.battlesCount++;
        if (gSaveBlock2Ptr->frontier.battlesCount % 20 == 0)
            UpdateGymLeaderRematch();
    }
    else
    {
        gSaveBlock2Ptr->frontier.battlesCount = 0xFFFFFF;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void Task_StartArcadeBattleAfterTransition(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = HandleArcadeTrainerBattleEnd;
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}

void SetArcadeBattleFlags(void)
{
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
    switch (VarGet(VAR_FRONTIER_BATTLE_MODE))
    {
        case FRONTIER_MODE_SINGLES:
            break;
        case FRONTIER_MODE_DOUBLES:
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
            break;
        case FRONTIER_MODE_MULTIS:
        case FRONTIER_MODE_LINK_MULTIS:
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_MULTI | BATTLE_TYPE_TWO_OPPONENTS;
            break;
    }
}

// Arcade Game Board Front End

static const struct BgTemplate sGameBoardBgTemplates[] =
    {
        {
            .bg = BG_BOARD_HELP_BAR,
            .charBaseIndex = 0,
            .mapBaseIndex = 31,
            .priority = 1
        },
        {
            .bg = BG_BOARD_EVENTS,
            .charBaseIndex = 3,
            .mapBaseIndex = 30,
            .priority = 2
        },
        {
            .bg = BG_BOARD_BACKGROUND,
            .charBaseIndex = 2,
            .mapBaseIndex = 29,
            .priority = 0
        },
        {
            .bg = BG_BOARD_BACKBOARD,
            .charBaseIndex = 1,
            .mapBaseIndex = 28,
            .priority = 3
        },
    };

static const struct WindowTemplate sGameBoardWinTemplates[] =
    {
        [WIN_BOARD_HELP_BAR] =
        {
            .bg = 0,
            .tilemapLeft = 0,
            .tilemapTop = 18,
            .width = 30,
            .height = 2,
            .paletteNum = 15,
            .baseBlock = 1,
        },
        DUMMY_WIN_TEMPLATE
    };

static EWRAM_DATA struct GameResult sGameBoard[ARCADE_GAME_BOARD_SPACES] = {{0}};

static const u8 sGameBoardWindowFontColors[][3] =
    {
        [TEXT_COLOR_WHITE]  =
        {
            TEXT_COLOR_TRANSPARENT,
            TEXT_COLOR_WHITE,
            TEXT_COLOR_DARK_GRAY
        },
    };

static const u32 sBackgroundTilemap[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/backgrounds/background.bin.smolTM");
static const u32 sBackgroundTiles[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/backgrounds/background.4bpp.smol");

static const u32 sLogobackgroundTilemap[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/backgrounds/logobackground.bin.smolTM");
static const u32 sLogobackgroundTiles[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/backgrounds/logobackground.4bpp.smol");

static const u32 sCountdownTile1[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/countdown/1.4bpp");
static const u32 sCountdownTile2[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/countdown/2.4bpp");
static const u32 sCountdownTile3[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/countdown/3.4bpp");

static const u32 sEventBurn[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/burn.4bpp.smol");
static const u32 sEventFog[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/fog.4bpp.smol");
static const u32 sEventFreeze[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/freeze.4bpp.smol");
static const u32 sEventGiveBerry[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/give_berry.4bpp.smol");
static const u32 sEventGiveBpBig[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/give_bp_big.4bpp.smol");
static const u32 sEventGiveBpSmall[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/give_bp_small.4bpp.smol");
static const u32 sEventGiveItem[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/give_item.4bpp.smol");
static const u32 sEventHail[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/hail.4bpp.smol");
static const u32 sEventLevelUp[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/level_up.4bpp.smol");
static const u32 sEventLowerHp[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/lower_hp.4bpp.smol");
static const u32 sEventNoBattle[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/no_battle.4bpp.smol");
static const u32 sEventParalyze[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/paralyze.4bpp.smol");
static const u32 sEventPoison[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/poison.4bpp.smol");
static const u32 sEventRain[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/rain.4bpp.smol");
static const u32 sEventRandom[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/random.4bpp.smol");
static const u32 sEventSand[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/sand.4bpp.smol");
static const u32 sEventSleep[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/sleep.4bpp.smol");
static const u32 sEventSpeedDown[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/speed_down.4bpp.smol");
static const u32 sEventSpeedUp[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/speed_up.4bpp.smol");
static const u32 sEventSun[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/sun.4bpp.smol");
static const u32 sEventSwap[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/swap.4bpp.smol");
static const u32 sEventTrickRoom[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/trick_room.4bpp.smol");
static const u32 sEventNoEvent[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/panels/event/no_event.4bpp.smol");

static const u32 sGameCursor[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/game/cursor.4bpp.smol");

const u16 sArcadeEventPlayer_Pal[] = INCBIN_U16("graphics/battle_frontier/battle_arcade/game/palettes/event_player.gbapal");
const u16 sArcadeEventOpponent_Pal[] = INCBIN_U16("graphics/battle_frontier/battle_arcade/game/palettes/event_opponent.gbapal");
const u16 sGameBoardPalette_Pal[] = INCBIN_U16("graphics/battle_frontier/battle_arcade/game/palettes/background.gbapal");

static const struct SpritePalette sArcadePalettes[] =
    {
        {sArcadeEventOpponent_Pal, ARCADE_PALTAG_OPPONENT},
        {sArcadeEventPlayer_Pal,   ARCADE_PALTAG_PLAYER},
    };

static const union AnimCmd sCountdownPanelAnim[] =
    {
        ANIMCMD_FRAME(0, ARCADE_BOARD_COUNTDOWN_TIMER / 3),
        ANIMCMD_FRAME(1, ARCADE_BOARD_COUNTDOWN_TIMER / 3),
        ANIMCMD_FRAME(2, ARCADE_BOARD_COUNTDOWN_TIMER / 3),
        ANIMCMD_FRAME(2, 10),
        ANIMCMD_END
    };

static const union AnimCmd *const sCountdownAnims[] =
    {
        [ARCADE_COUNTDOWN_ANIM] = sCountdownPanelAnim
    };

static const struct SpriteFrameImage sCountdownPanelPicTable[] =
    {
        obj_frame_tiles(sCountdownTile3),
        obj_frame_tiles(sCountdownTile2),
        obj_frame_tiles(sCountdownTile1),
    };

static const struct OamData CountdownPanelOam =
    {
        .y = 0,
        .affineMode = ST_OAM_AFFINE_OFF,
        .objMode = ST_OAM_OBJ_NORMAL,
        .mosaic = FALSE,
        .bpp = ST_OAM_4BPP,
        .shape = SPRITE_SHAPE(32x32),
        .x = 0,
        .matrixNum = 0,
        .size = SPRITE_SIZE(32x32),
        .tileNum = 0,
        .priority = 1,
        .paletteNum = 0,
        .affineParam = 0,
    };

static const struct SpriteTemplate sCountdownPanelSpriteTemplate =
    {
        .tileTag = TAG_NONE,
        .paletteTag = ARCADE_PALTAG_OPPONENT,
        .oam = &CountdownPanelOam,
        .anims = sCountdownAnims,
        .images = sCountdownPanelPicTable,
        .callback = SpriteCallbackDummy,
    };

void Task_OpenGameBoard(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    CleanupOverworldWindowsAndTilemaps();
    GameBoard_Init(CB2_ReturnToFieldContinueScript);
    DestroyTask(taskId);
}

void GameBoard_Init(MainCallback callback)
{
    sGameBoardState = AllocZeroed(sizeof(struct GameBoardState));

    if (sGameBoardState == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sGameBoardState->loadState = 0;
    sGameBoardState->savedCallback = callback;

    SetMainCallback2(GameBoard_SetupCB);
}

static void GameBoard_SetupCB(void)
{
    switch (gMain.state)
    {
        case 0:
            DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
            SetVBlankHBlankCallbacksToNull();
            ClearScheduledBgCopiesToVram();
            gMain.state++;
            break;
        case 1:
            ScanlineEffect_Stop();
            FreeAllSpritePalettes();
            ResetPaletteFade();
            ResetSpriteData();
            ResetTasks();
            gMain.state++;
            break;
        case 2:
            if (GameBoard_InitBgs())
            {
                sGameBoardState->loadState = 0;
                gMain.state++;
            }
            else
        {
                GameBoard_FadeAndBail();
                return;
            }
            break;
        case 3:
            if (GameBoard_LoadGraphics() == TRUE)
                gMain.state++;
            break;
        case 4:
            GameBoard_InitWindows();
            gMain.state++;
            break;
        case 5:
            FreeMonIconPalettes();
            LoadMonIconPalettes();
            GenerateGameBoard();
            PrintEnemyParty();
            PrintPlayerParty();
            PrintHelpBar();
            CreateTask(Task_GameBoardWaitFadeIn, 0);
            gMain.state++;
            break;
        case 6:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            gMain.state++;
            break;
        case 7:
            SetVBlankCallback(VBlankCB);
            SetMainCallback2(MainCB);
            break;
    }
}

static bool8 GameBoard_InitBgs(void)
{
    ResetAllBgsCoordinates();

    if (!BattleArcade_AllocTilemapBuffers())
        return FALSE;
    GameBoard_HandleAndShowBgs();

    return TRUE;
}

static bool32 BattleArcade_AllocTilemapBuffers(void)
{
    u32 backgroundId;

    for (backgroundId = 0; backgroundId < BG_BOARD_COUNT; backgroundId++)
    {
        sBgTilemapBuffer[backgroundId] = AllocZeroed(ARCADE_TILEMAP_BUFFER_SIZE);

        if (sBgTilemapBuffer[backgroundId] == NULL)
            return FALSE;
    }
    return TRUE;
}

static void GameBoard_HandleAndShowBgs(void)
{
    u32 backgroundId;

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sGameBoardBgTemplates, NELEMS(sGameBoardBgTemplates));

    for (backgroundId = 0; backgroundId < BG_BOARD_COUNT; backgroundId++)
        SetScheduleShowBgs(backgroundId);
}

static void SetScheduleShowBgs(u32 backgroundId)
{
    SetBgTilemapBuffer(backgroundId, sBgTilemapBuffer[backgroundId]);
    ScheduleBgCopyTilemapToVram(backgroundId);
    ShowBg(backgroundId);
}

static void GameBoard_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_GameBoardWaitFadeAndBail, 0);

    SetVBlankCallback(VBlankCB);
    SetMainCallback2(MainCB);
}

static void Task_GameBoardWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sGameBoardState->savedCallback);
        GameBoard_FreeResources();
        DestroyTask(taskId);
    }
}

static bool8 GameBoard_LoadGraphics(void)
{
    switch (sGameBoardState->loadState)
    {
        case 0:
            ResetTempTileDataBuffers();

            DecompressAndCopyTileDataToVram(BG_BOARD_BACKBOARD, sBackgroundTiles, 0, 0, 0);
            DecompressAndCopyTileDataToVram(BG_BOARD_BACKGROUND, sLogobackgroundTiles, 0, 0, 0);
            sGameBoardState->loadState++;
            break;
        case 1:
            if (FreeTempTileDataBuffersIfPossible() != TRUE)
            {
                DecompressDataWithHeaderWram(sBackgroundTilemap, sBgTilemapBuffer[BG_BOARD_BACKBOARD]);
                DecompressDataWithHeaderWram(sLogobackgroundTilemap, sBgTilemapBuffer[BG_BOARD_BACKGROUND]);
                sGameBoardState->loadState++;
            }
            break;
        case 2:
            LoadPalette(sGameBoardPalette_Pal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
            sGameBoardState->loadState++;
        default:
            sGameBoardState->loadState = 0;
            return TRUE;
    }
    return FALSE;
}

static void GameBoard_InitWindows(void)
{
    u32 windowId;
    InitWindows(sGameBoardWinTemplates);

    DeactivateAllTextPrinters();

    ScheduleBgCopyTilemapToVram(0);

    for (windowId = 0; windowId < WIN_BOARD_COUNT; windowId++)
    {
        FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

static void LoadEventPalettes(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sArcadePalettes); i++)
        sGameBoardState->cursorPaletteNum[i] = LoadSpritePalette(&sArcadePalettes[i]);
}

static void GenerateGameBoard(void)
{
    u32 space;

    for (space = 0; space < ARCADE_GAME_BOARD_SPACES; space++)
    {
        sGameBoard[space].impact = GenerateImpact();
        sGameBoard[space].event = GenerateEvent(sGameBoard[space].impact);

    }
}

static void PrintEnemyParty(void)
{
    PrintPartyIcons(ARCADE_IMPACT_OPPONENT);
}

static void PrintPlayerParty(void)
{
    PrintPartyIcons(ARCADE_IMPACT_PLAYER);
}

static void PrintPartyIcons(u32 side)
{
    u32 x = GetHorizontalPositionFromSide(side);
    u32 y = 33;
    u32 i;
    struct Pokemon *party = LoadSideParty(side);

    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        if (!GetMonData(&party[i], MON_DATA_SANITY_HAS_SPECIES))
            break;

        sGameBoardState->monIconSpriteId[side][i] = CreateMonIcon(GetMonData(&party[i], MON_DATA_SPECIES), SpriteCallbackDummy, x, y, 4, GetMonData(&party[i], MON_DATA_PERSONALITY));
        gSprites[sGameBoardState->monIconSpriteId[side][i]].oam.priority = 0;
        y += 30;
    }
}

static u32 GetHorizontalPositionFromSide(u32 side)
{
    return (side == ARCADE_IMPACT_OPPONENT) ? 215 : 22;
}

static struct Pokemon *LoadSideParty(u32 impact)
{
    if (impact == ARCADE_IMPACT_PLAYER)
        return gPlayerParty;
    else
        return gEnemyParty;
}

static void PrintHelpBar(void)
{
    u32 windowId = WIN_BOARD_HELP_BAR;
    u32 fontId = FONT_NARROW;

    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(windowId, fontId, 4, 1, GetFontAttribute(fontId, FONTATTR_LETTER_SPACING), GetFontAttribute(fontId, FONTATTR_LINE_SPACING), sGameBoardWindowFontColors[TEXT_COLOR_WHITE], TEXT_SKIP_DRAW, GetHelpBarText());

    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static const u8 *GetHelpBarText(void)
{
    static const u8 sText_HelpBarStart[] =_("{A_BUTTON} Start Game");
    static const u8 sText_HelpBarFinish[] =_("{A_BUTTON} Select Event");

    switch (GetGameBoardMode())
    {
        case ARCADE_BOARD_MODE_WAIT:
            return sText_HelpBarStart;
        case ARCADE_BOARD_MODE_GAME_START:
            return sText_HelpBarFinish;
        default:
            return gText_Blank;
    }
}

static u32 GetGameBoardMode(void)
{
    return sGameBoardState->gameMode;
}

static void Task_GameBoardWaitFadeIn(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    gTasks[taskId].func = Task_GameBoardMainInput;
}

static void Task_GameBoardMainInput(u8 taskId)
{
    if (!JOY_NEW(A_BUTTON))
        return;

    PlaySE(SE_SELECT);
    switch (GetGameBoardMode())
    {
        case ARCADE_BOARD_MODE_WAIT:
            StartCountdown();
            break;
        case ARCADE_BOARD_MODE_GAME_START:
            HandleFinishMode();
            break;
        default:
            return;
    }
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void StartCountdown(void)
{
    HideBg(BG_BOARD_BACKGROUND);
    IncrementGameBoardMode();
    SetTimerForCountdown();
    PopulateCountdownSprites();
    PrintHelpBar();
    CreateTask(Task_GameBoard_Countdown, 0);
}

static void SetTimerForCountdown(void)
{
    SetTimer(ARCADE_BOARD_COUNTDOWN_TIMER);
}

static void SetTimer(u32 value)
{
    sGameBoardState->timer = value;
}

static void PopulateCountdownSprites(void)
{
    u32 space, x, y;

    LoadEventPalettes();
    for (space = 0; space < (ARCADE_GAME_BOARD_ROWS * ARCADE_GAME_BOARD_COLUMNS); space++)
    {
        CalculatePanelPosition(space,&x,&y);
        sGameBoardState->countdownPanelSpriteId[space] = CreateCountdownPanel(x+12,y+12);
    }
}

static void CalculatePanelPosition(u32 space, u32* x, u32* y)
{
    u32 rowIndex = space / ARCADE_GAME_BOARD_COLUMNS;
    u32 columnIndex = space % ARCADE_GAME_BOARD_COLUMNS;
    *x = 65 + columnIndex * 32;
    *y = 17 + rowIndex * 32;
}

static u32 CreateCountdownPanel(u32 x, u32 y)
{
    return CreateSprite(&sCountdownPanelSpriteTemplate, x, y, 0);
}

static void Task_GameBoard_Countdown(u8 taskId)
{
    DecrementGameBoardTimer();

    switch(GetGameBoardTimer())
    {
        case ARCADE_COUNTDOWN_SHOW_FRAMES_2:
        case ARCADE_COUNTDOWN_SHOW_FRAMES_1:
            IncrementGameBoardMode();
            break;
        case 0:
            IncrementGameBoardMode();
            PopulateEventSprites();
            PrintHelpBar();
            StartGame();
            DestroyTask(taskId);
            break;
        default:
            break;
    }
}

static void PopulateEventSprites(void)
{
    u32 space, x, y;

    LoadTileSpriteSheets();
    LoadEventPalettes();

    for (space = 0; space < (ARCADE_GAME_BOARD_ROWS * ARCADE_GAME_BOARD_COLUMNS); space++)
    {
        CalculatePanelPosition(space,&x,&y);
        sGameBoardState->eventIconSpriteId[space] = CreateEventSprite(x, y, space);
    }
}

static void LoadTileSpriteSheets(void)
{
    u32 i;
    for (i = 0; i < ARCADE_GAME_BOARD_SPACES; i++)
    {
        u16 TileTag = GetTileTag(i);
        const u32 *gfx = GetEventGfx(sGameBoard[i].event);
        struct CompressedSpriteSheet sSpriteSheet_EventSpace = {gfx, 0x0200, TileTag};
        LoadCompressedSpriteSheet(&sSpriteSheet_EventSpace);
    }
}

static const u32* GetEventGfx(u32 event)
{
    switch (event)
    {
        case ARCADE_EVENT_LOWER_HP: return sEventLowerHp;
        case ARCADE_EVENT_POISON: return sEventPoison;
        case ARCADE_EVENT_PARALYZE: return sEventParalyze;
        case ARCADE_EVENT_BURN: return sEventBurn;
        case ARCADE_EVENT_SLEEP: return sEventSleep;
        case ARCADE_EVENT_FREEZE: return sEventFreeze;
        case ARCADE_EVENT_GIVE_BERRY: return sEventGiveBerry;
        case ARCADE_EVENT_GIVE_ITEM: return sEventGiveItem;
        case ARCADE_EVENT_LEVEL_UP: return sEventLevelUp;
        case ARCADE_EVENT_SUN: return sEventSun;
        case ARCADE_EVENT_RAIN: return sEventRain;
        case ARCADE_EVENT_SAND: return sEventSand;
        case ARCADE_EVENT_HAIL: return sEventHail;
        case ARCADE_EVENT_FOG: return sEventFog;
        case ARCADE_EVENT_TRICK_ROOM: return sEventTrickRoom;
        case ARCADE_EVENT_SWAP: return sEventSwap;
        case ARCADE_EVENT_SPEED_UP: return sEventSpeedUp;
        case ARCADE_EVENT_SPEED_DOWN: return sEventSpeedDown;
        case ARCADE_EVENT_RANDOM: return sEventRandom;
        case ARCADE_EVENT_GIVE_BP_SMALL: return sEventGiveBpSmall;
        case ARCADE_EVENT_NO_BATTLE: return sEventNoBattle;
        case ARCADE_EVENT_GIVE_BP_BIG: return sEventGiveBpBig;
        default:
        case ARCADE_EVENT_NO_EVENT: return sEventNoEvent;
    }
}

static u8 CreateEventSprite(u32 x, u32 y, u32 space)
{
    u32 spriteId;
    u16 TileTag = GetTileTag(space);
    u32 impact = (sGameBoard[space].impact == ARCADE_IMPACT_PLAYER) ? ARCADE_IMPACT_PLAYER : ARCADE_IMPACT_OPPONENT;

    struct SpriteTemplate TempSpriteTemplate = gDummySpriteTemplate;
    TempSpriteTemplate.tileTag = TileTag;
    TempSpriteTemplate.paletteTag = ARCADE_PALTAG_EVENT + impact;
    TempSpriteTemplate.callback = SpriteCallbackDummy;

    spriteId = CreateSprite(&TempSpriteTemplate,x,y, 0);

    gSprites[spriteId].oam.shape = SPRITE_SHAPE(32x32);
    gSprites[spriteId].oam.size = SPRITE_SIZE(32x32);
    gSprites[spriteId].oam.priority = 0;

    return spriteId;
}

static const u16 GetTileTag(u32 space)
{
    return (sGameBoard[space].event) + ARCADE_GFXTAG_EVENT;
}

static void StartGame(void)
{
    SetTimerForGame();
    InitCursorPositionFromSaveblock();
    CreateGameBoardCursor();
    DestroyCountdownPanels();
    CreateTask(Task_GameBoard_Game, 0);
}

static void SetTimerForGame(void)
{
    SetTimer(ARCADE_BOARD_GAME_TIMER);
}

static void InitCursorPositionFromSaveblock(void)
{
    sGameBoardState->cursorPosition = ARCADE_SAVEDATA_CURSOR.position;
}

static void CreateGameBoardCursor(void)
{
    u16 TileTag = ARCADE_GFXTAG_CURSOR;
    u32 spriteId;

    struct CompressedSpriteSheet sSpriteSheet_Cursor = {sGameCursor, 0x0200, TileTag};
    struct SpriteTemplate TempSpriteTemplate = gDummySpriteTemplate;

    LoadCompressedSpriteSheet(&sSpriteSheet_Cursor);

    TempSpriteTemplate.tileTag = TileTag;
    TempSpriteTemplate.paletteTag = ARCADE_PALTAG_CURSOR;
    TempSpriteTemplate.callback = SpriteCB_Cursor;

    spriteId = CreateSprite(&TempSpriteTemplate,45,7, 0);

    gSprites[spriteId].oam.shape = SPRITE_SHAPE(32x32);
    gSprites[spriteId].oam.size = SPRITE_SIZE(32x32);
    gSprites[spriteId].oam.priority = 1;
}

static void SpriteCB_Cursor(struct Sprite *sprite)
{
    ChangeCursorColor(sprite);
    ChangeCursorSpritePosition(sprite);
}

static void ChangeCursorColor(struct Sprite *sprite)
{
    if (GetGameBoardTimer() % ARCADE_CURSOR_COLOR_CHANGE_FRAMES != 0)
        return;

    sprite->oam.paletteNum = ReturnNextCursorPalette(sprite->oam.paletteNum);
}

static u32 ReturnNextCursorPalette(u32 paletteNum)
{
    if (paletteNum == sGameBoardState->cursorPaletteNum[1])
        return sGameBoardState->cursorPaletteNum[0];
    else
        return sGameBoardState->cursorPaletteNum[1];
}

static void ChangeCursorSpritePosition(struct Sprite *sprite)
{
    u32 x, y;
    CalculatePanelPosition(GetCursorPosition(),&x,&y);
    sprite->x2 = x - 50;
    sprite->y2 = y - 10;
}

static void DestroyCountdownPanels(void)
{
    u32 space;

    for (space = 0; space < ARCADE_GAME_BOARD_SPACES; space++)
    {
        DestroySpriteAndFreeResources(&gSprites[sGameBoardState->countdownPanelSpriteId[space]]);
        sGameBoardState->countdownPanelSpriteId[space] = 0;
    }
}

static void Task_GameBoard_Game(u8 taskId)
{
    u32 timer = GetGameBoardTimer();

    if (GetGameBoardMode() > ARCADE_BOARD_MODE_GAME_START)
        HandleFinishMode();
    else if (IsGameBoardTimerEmpty())
        IncrementGameBoardMode();
    else if (ShouldCursorMove(timer))
        ChangeCursorPosition();

    DecrementGameBoardTimer();
}

static u32 GetGameBoardTimer(void)
{
    return sGameBoardState->timer;
}

static void IncrementGameBoardMode(void)
{
    sGameBoardState->gameMode++;
}

static bool32 ShouldCursorMove(u32 timer)
{
    u32 cursorWaitValue = ReturnCursorWait(GetCursorSpeed());

    if (cursorWaitValue == 0)
        return TRUE;

    return (timer % cursorWaitValue == 0);
}

u32 ReturnCursorWait(u32 speed)
{
    static const u32 cursorWaitTable[ARCADE_SPEED_COUNT] =
        {
            [ARCADE_SPEED_LEVEL_0] = ARCADE_CURSOR_WAIT_LEVEL_0,
            [ARCADE_SPEED_LEVEL_1] = ARCADE_CURSOR_WAIT_LEVEL_1,
            [ARCADE_SPEED_LEVEL_2] = ARCADE_CURSOR_WAIT_LEVEL_2,
            [ARCADE_SPEED_LEVEL_3] = ARCADE_CURSOR_WAIT_LEVEL_3,
            [ARCADE_SPEED_DEFAULT] = ARCADE_CURSOR_WAIT_LEVEL_4,
            [ARCADE_SPEED_LEVEL_5] = ARCADE_CURSOR_WAIT_LEVEL_5,
            [ARCADE_SPEED_LEVEL_6] = ARCADE_CURSOR_WAIT_LEVEL_6,
            [ARCADE_SPEED_LEVEL_7] = ARCADE_CURSOR_WAIT_LEVEL_7,
        };

    return cursorWaitTable[speed];
}

static void ChangeCursorPosition(void)
{
    u32 newPosition = GetCursorPosition() + 1;

    if (IsCursorInRandomMode())
        SetCursorPosition(Random() % ARCADE_GAME_BOARD_SPACES);
    else
    {
        if (newPosition >= ARCADE_GAME_BOARD_SPACES)
            SetCursorPosition(0);
        else
            SetCursorPosition(newPosition);
    }

}

static bool32 IsCursorInRandomMode(void)
{
    return (ARCADE_SAVEDATA_CURSOR.isRandom == TRUE);
}

static bool32 IsGameBoardTimerEmpty(void)
{
    return (GetGameBoardTimer() == 0);
}

static void DecrementGameBoardTimer(void)
{
    sGameBoardState->timer--;
}

static void HandleFinishMode()
{
    u32 impact = 0, event = 0;

    IncrementGameBoardMode();
    DestroyTask(FindTaskIdByFunc(Task_GameBoard_Game));
    PrintHelpBar();
    SelectGameBoardSpace(&impact,&event);
    ClearCursorRandomMode();
    HandleGameBoardResult(impact,event);
    SaveCursorPositionToSaveblock();
    DestroyEventSprites();
    PopulateEventSprites();
    SetTimerForFinish();
    CreateTask(Task_GameBoard_CleanUp,0);
}

static void SetTimerForFinish(void)
{
    SetTimer(ARCADE_BOARD_FINISH_TIMER);
}

static void SelectGameBoardSpace(u32 *impact, u32 *event)
{
    u32 space = GetCursorPosition();

    *impact = sGameBoard[space].impact;
    *event = sGameBoard[space].event;
}

static void HandleGameBoardResult(u32 impact, u32 event)
{
    LOCAL_VAR_GAME_BOARD_SUCCESS = DoGameBoardResult(event, impact);
    BufferImpactedName(gStringVar1,impact);

    SetGameBoardToChosenEvent(impact,event);
    StoreEventToVar(event);
    StoreImpactedSideToVar(impact);
}

static void BufferImpactedName(u8 *dest, u32 impact)
{
    if (impact == ARCADE_IMPACT_PLAYER)
        StringCopy_PlayerName(dest, gSaveBlock2Ptr->playerName);
    else
        GetFrontierTrainerName(dest, GetImpactedTrainerId(impact));
}

static u32 GetImpactedTrainerId(u32 impact)
{
    return (impact == ARCADE_IMPACT_PLAYER) ? TRAINER_PLAYER : TRAINER_BATTLE_PARAM.opponentA;
}

static void SetGameBoardToChosenEvent(u32 impact, u32 event)
{
    u32 i;
    for (i = 0; i < ARCADE_GAME_BOARD_SPACES; i++)
    {
        sGameBoard[i].impact = impact;
        sGameBoard[i].event = event;
    }
}

static void StoreEventToVar(u32 event)
{
    LOCAL_VAR_GAME_BOARD_EVENT = event;
}

static void StoreImpactedSideToVar(u32 impact)
{
    LOCAL_VAR_GAME_BOARD_IMPACT = impact;
}

static void DestroyEventSprites(void)
{
    u32 space;

    for (space = 0; space < ARCADE_GAME_BOARD_SPACES; space++)
    {
        DestroySpriteAndFreeResources(&gSprites[sGameBoardState->eventIconSpriteId[space]]);
        sGameBoardState->eventIconSpriteId[space] = 0;
    }
}

static void Task_GameBoard_CleanUp(u8 taskId)
{
    DecrementGameBoardTimer();

    if (!IsGameBoardTimerEmpty())
        return;

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);

    gTasks[taskId].func = Task_GameBoardWaitFadeAndExitGracefully;
}

static void Task_GameBoardWaitFadeAndExitGracefully(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sGameBoardState->savedCallback);
        GameBoard_FreeResources();
        DestroyTask(taskId);
    }
}

static void GameBoard_FreeResources(void)
{
    u32 backgroundId;

    if (sGameBoardState != NULL)
    {
        Free(sGameBoardState);
    }

    for (backgroundId = 0; backgroundId < BG_BOARD_COUNT; backgroundId++)
    {
        if (sBgTilemapBuffer[backgroundId] != NULL)
            Free(sBgTilemapBuffer[backgroundId]);
    }

    FreeAllWindowBuffers();
    ResetSpriteData();
}

static u32 GenerateImpact(void)
{
    static const u32 ImpactTable[][ARCADE_IMPACT_COUNT] =
        {
            //Opponent, Player, All, Special
            [ARCADE_PERFORMANCE_BRACKET_0_4]     = {10, 75, 10, 5},
            [ARCADE_PERFORMANCE_BRACKET_5_10]    = {25, 40, 30, 5},
            [ARCADE_PERFORMANCE_BRACKET_11_15]   = {30, 30, 35, 5},
            [ARCADE_PERFORMANCE_BRACKET_16_20]   = {35, 20, 30, 15},
            [ARCADE_PERFORMANCE_BRACKET_21_PLUS] = {15, 15, 40, 30},
        };

    u32 impactThreshold = 0, impactIndex = 0;
    u32 randImpact = Random() % 100;
    u32 impactBracket = ConvertPerformanceToImpactBracket();

    for (impactIndex = 0; impactIndex < ARCADE_IMPACT_COUNT; impactIndex++)
    {
        impactThreshold += ImpactTable[impactBracket][impactIndex];
        if (randImpact < impactThreshold)
            return impactIndex;
    }
    return ARCADE_IMPACT_PLAYER;
}

static u32 ConvertPerformanceToImpactBracket(void)
{
    u32 performancePoints = GetPerformancePoints();

    return performancePoints <= 4 ? ARCADE_PERFORMANCE_BRACKET_0_4 :
    performancePoints <= 10 ? ARCADE_PERFORMANCE_BRACKET_5_10 :
    performancePoints <= 15 ? ARCADE_PERFORMANCE_BRACKET_11_15 :
    performancePoints <= 20 ? ARCADE_PERFORMANCE_BRACKET_16_20 :
    ARCADE_PERFORMANCE_BRACKET_21_PLUS;
}

static u32 GenerateEvent(u32 impact)
{
    u32 event = GenerateRandomBetweenBounds(impact);

    do
    {
        event = GenerateRandomBetweenBounds(impact);
    } while (!IsEventValidDuringBattleOrStreak(event,impact));

    return event;
}

static u32 GenerateRandomBetweenBounds(u32 impact)
{
    u32 upper = GetPanelUpperBound(impact);
    u32 lower = GetPanelLowerBound(impact);

    return (lower + Random() % (upper - lower + 1));
}

static s32 GetPanelUpperBound(u32 impact)
{
    //Not Inclusive
    switch (impact)
    {
        case ARCADE_IMPACT_PLAYER:
        case ARCADE_IMPACT_OPPONENT:
            return ARCADE_EVENT_WEATHER_START;
        case ARCADE_IMPACT_ALL:
            return ARCADE_EVENT_SPECIAL_START;
        default:
        case ARCADE_IMPACT_SPECIAL:
            return ARCADE_EVENT_COUNT;
    }
}

static s32 GetPanelLowerBound(u32 impact)
{
    //Inclusive
    switch (impact)
    {
        case ARCADE_IMPACT_PLAYER:
        case ARCADE_IMPACT_OPPONENT:
            return ARCADE_EVENT_INDIVIDUAL_START;
        case ARCADE_IMPACT_ALL:
            return ARCADE_EVENT_WEATHER_START;
        default:
        case ARCADE_IMPACT_SPECIAL:
            return ARCADE_EVENT_SPECIAL_START;
    }
}

static bool32 IsEventValidDuringBattleOrStreak(u32 event, u32 impact)
{
    if (IsEventBanned(event))
        return FALSE;
    if (!IsEventValidDuringCurrentStreak(event))
        return FALSE;
    if (!IsEventValidDuringCurrentBattle(event))
        return FALSE;

    return TRUE;
}

static bool32 IsEventBanned(u32 event)
{
    if (event == ARCADE_EVENT_FOG)
        return TRUE;
    return FALSE;
}

static bool32 IsEventValidDuringCurrentBattle(u32 event)
{
    u32 battleNum = FRONTIER_SAVEDATA.curChallengeBattleNum;
    static const u32 SpecialPanelTable[][FRONTIER_STAGES_PER_CHALLENGE] =
        {
            //Battle 1  2  3  4  5  6  7
            [ARCADE_EVENT_SWAP]          = {1, 1, 1, 1, 1, 1, 0},
            [ARCADE_EVENT_SPEED_UP]      = {1, 1, 1, 1, 1, 1, 0},
            [ARCADE_EVENT_SPEED_DOWN]    = {1, 1, 1, 1, 1, 1, 0},
            [ARCADE_EVENT_RANDOM]        = {1, 1, 1, 1, 1, 1, 0},
            [ARCADE_EVENT_GIVE_BP_SMALL] = {0, 0, 0, 0, 0, 0, 0},
            [ARCADE_EVENT_NO_BATTLE]     = {0, 1, 0, 1, 0, 1, 0},
            [ARCADE_EVENT_GIVE_BP_BIG]   = {0, 0, 0, 0, 0, 0, 0},
            [ARCADE_EVENT_NO_EVENT]      = {1, 1, 1, 1, 1, 1, 1},
        };

    if (event < ARCADE_EVENT_SPECIAL_START)
        return TRUE;

    if (battleNum >= FRONTIER_STAGES_PER_CHALLENGE)
        battleNum = FRONTIER_STAGES_PER_CHALLENGE - 1;

    if (!SpecialPanelTable[event][battleNum])
        return FALSE;

    return TRUE;
}

static bool32 IsEventValidDuringCurrentStreak(u32 event)
{
    static const u32 PanelStreakTable[][ARCADE_STREAK_NUM_COUNT] =
        {                          //Streak 1  2  3  4  5  6  7
            [ARCADE_EVENT_LOWER_HP]      = {0, 1, 1, 1, 1, 1, 1},
            [ARCADE_EVENT_POISON]        = {1, 0, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_PARALYZE]      = {1, 0, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_BURN]          = {1, 0, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_SLEEP]         = {0, 0, 0, 0, 1, 1, 1},
            [ARCADE_EVENT_FREEZE]        = {0, 0, 0, 0, 1, 1, 1},
            [ARCADE_EVENT_GIVE_BERRY]    = {1, 1, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_GIVE_ITEM]     = {0, 0, 0, 1, 1, 1, 1},
            [ARCADE_EVENT_LEVEL_UP]      = {0, 1, 1, 1, 1, 1, 1},
            [ARCADE_EVENT_SUN]           = {0, 1, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_RAIN]          = {0, 1, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_SAND]          = {0, 1, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_HAIL]          = {0, 1, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_FOG]           = {0, 0, 0, 1, 0, 1, 1},
            [ARCADE_EVENT_TRICK_ROOM]    = {0, 0, 0, 1, 0, 1, 1},
            [ARCADE_EVENT_SWAP]          = {1, 1, 1, 1, 1, 1, 1},
            [ARCADE_EVENT_SPEED_UP]      = {1, 1, 1, 0, 0, 0, 1},
            [ARCADE_EVENT_SPEED_DOWN]    = {1, 1, 1, 1, 1, 1, 1},
            [ARCADE_EVENT_RANDOM]        = {0, 0, 0, 0, 1, 1, 1},
            [ARCADE_EVENT_GIVE_BP_SMALL] = {0, 0, 0, 0, 0, 0, 0},
            [ARCADE_EVENT_NO_BATTLE]     = {0, 0, 0, 0, 1, 1, 1},
            [ARCADE_EVENT_GIVE_BP_BIG]   = {0, 0, 0, 0, 0, 0, 0},
            [ARCADE_EVENT_NO_EVENT]      = {1, 1, 1, 1, 1, 1, 1},
        };

    if (event < ARCADE_EVENT_SPECIAL_START)
        return TRUE;

    if (!PanelStreakTable[event][GetChallengeNumIndex()])
        return FALSE;

    return TRUE;
}

static u32 GetChallengeNumIndex(void)
{
    u32 challengeNum = GetChallengeNum();

    if (challengeNum > ARCADE_STREAK_NUM_MAX)
        return ARCADE_STREAK_NUM_MAX;
    else
        return challengeNum;
}

static u32 GetChallengeNum(void)
{
    return (GetCurrentStreak() / FRONTIER_STAGES_PER_CHALLENGE);
}

// Arcade Game Board Back End Resolution
static bool32 DoGameBoardResult(u32 event, u32 impact)
{
    switch (event)
    {
        case ARCADE_EVENT_LOWER_HP: return BattleArcade_DoLowerHP(impact);
        case ARCADE_EVENT_POISON: return BattleArcade_DoPoison(impact);
        case ARCADE_EVENT_PARALYZE: return BattleArcade_DoParalyze(impact);
        case ARCADE_EVENT_BURN: return BattleArcade_DoBurn(impact);
        case ARCADE_EVENT_SLEEP: return BattleArcade_DoSleep(impact);
        case ARCADE_EVENT_FREEZE: return BattleArcade_DoFreeze(impact);
        case ARCADE_EVENT_GIVE_BERRY: return BattleArcade_DoGiveBerry(impact);
        case ARCADE_EVENT_GIVE_ITEM: return BattleArcade_DoGiveItem(impact);
        case ARCADE_EVENT_LEVEL_UP: return BattleArcade_DoLevelUp(impact);
        case ARCADE_EVENT_SUN: return BattleArcade_DoSun();
        case ARCADE_EVENT_RAIN: return BattleArcade_DoRain();
        case ARCADE_EVENT_SAND: return BattleArcade_DoSand();
        case ARCADE_EVENT_HAIL: return BattleArcade_DoHail();
        case ARCADE_EVENT_FOG: return BattleArcade_DoFog();
        case ARCADE_EVENT_TRICK_ROOM: return BattleArcade_DoTrickRoom();
        case ARCADE_EVENT_SWAP: return BattleArcade_DoSwap();
        case ARCADE_EVENT_SPEED_UP: return BattleArcade_DoSpeedUp();
        case ARCADE_EVENT_SPEED_DOWN: return BattleArcade_DoSpeedDown();
        case ARCADE_EVENT_RANDOM: return BattleArcade_DoRandom();
        case ARCADE_EVENT_GIVE_BP_SMALL: return BattleArcade_DoGiveBPSmall();
        case ARCADE_EVENT_GIVE_BP_BIG: return BattleArcade_DoGiveBPBig();
        case ARCADE_EVENT_NO_BATTLE: return BattleArcade_DoNoBattle();
        default:
        case ARCADE_EVENT_NO_EVENT: return BattleArcade_DoNoEvent();
    }
    return TRUE;
}

static bool32 BattleArcade_DoLowerHP(u32 impact)
{
    u32 i, maxHP, reducedHP;
    struct Pokemon *party = LoadSideParty(impact);

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        if (!GetMonData(&party[i], MON_DATA_SANITY_HAS_SPECIES))
            break;

        maxHP = GetMonData(&party[i], MON_DATA_MAX_HP);
        reducedHP = maxHP - (maxHP * 200 / 1000);
        SetMonData(&party[i], MON_DATA_HP, &reducedHP);
    }
    return TRUE;
}

static bool32 BattleArcade_DoPoison(u32 impact)
{
    return BattleArcade_DoStatusAilment(impact, STATUS1_TOXIC_POISON);
}
static bool32 BattleArcade_DoParalyze(u32 impact)
{
    return BattleArcade_DoStatusAilment(impact, STATUS1_PARALYSIS);
}
static bool32 BattleArcade_DoBurn(u32 impact)
{
    return BattleArcade_DoStatusAilment(impact, STATUS1_BURN);
}
static bool32 BattleArcade_DoSleep(u32 impact)
{
    return BattleArcade_DoStatusAilment(impact, STATUS1_SLEEP);
}
static bool32 BattleArcade_DoFreeze(u32 impact)
{
    return BattleArcade_DoStatusAilment(impact, STATUS1_FROSTBITE);
}

static bool32 BattleArcade_DoStatusAilment(u32 impact, u32 status)
{
    struct Pokemon *party = LoadSideParty(impact);
    struct Pokemon *mon;
    u32 i, impactedCount = 0;
    u32 newIndex[MAX_FRONTIER_PARTY_SIZE];

    InitalizePartyIndex(newIndex);

    if (IsStatusSleepOrFreeze(status))
        ShufflePartyIndex(newIndex);

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        mon = &party[newIndex[i]];

        if (!GetMonData(mon,MON_DATA_SANITY_HAS_SPECIES))
            continue;

        if (DoesAbilityPreventStatus(mon, status))
            continue;

        if (DoesTypePreventStatus(GetMonData(mon,MON_DATA_SPECIES), status))
            continue;

        SetMonData(mon, MON_DATA_STATUS, &status);
        impactedCount++;

        if (!IsStatusSleepOrFreeze(status))
            continue;

        return TRUE;
    }
    return (impactedCount > 0);
}

static void InitalizePartyIndex(u32 *newIndex)
{
    u32 i;
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        newIndex[i] = i;
}

static bool32 IsStatusSleepOrFreeze(u32 status)
{
    return ((status == STATUS1_FROSTBITE) || (status == STATUS1_SLEEP));
}

static void ShufflePartyIndex(u32 *newIndex)
{
    u32 i, temp;
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        SWAP(newIndex[i], newIndex[Random() % (i +1)], temp);
}

static bool32 BattleArcade_DoGiveBerry(u32 impact)
{
    u32 item = VarGet(VAR_ARCADE_BERRY);
    return BattleArcade_DoGive(impact, item);
}

static bool32 BattleArcade_DoGiveItem(u32 impact)
{
    u32 item = VarGet(VAR_ARCADE_ITEM);
    return BattleArcade_DoGive(impact, item);
}

static bool32 BattleArcade_DoGive(u32 impact, u32 item)
{
    u32 i;
    struct Pokemon *party = LoadSideParty(impact);

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            break;

        SetMonData(&party[i], MON_DATA_HELD_ITEM, &item);
    }

    BufferGiveString(item);
    return TRUE;
}

static void BufferGiveString(u32 item)
{
    CopyItemName(item,gStringVar3);
}

static bool32 BattleArcade_DoLevelUp(u32 impact)
{
    u32 i, newLevel;
    struct Pokemon *party = LoadSideParty(impact);

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        if (!GetMonData(&party[i], MON_DATA_SANITY_HAS_SPECIES))
            break;

        newLevel = CalculateAndSaveNewLevel(GetMonData(&party[i], MON_DATA_LEVEL));
        SetMonData(&party[i], MON_DATA_LEVEL, &newLevel);
    }
    return TRUE;
}

static u32 CalculateAndSaveNewLevel(u32 origLevel)
{
    u32 newLevel = (origLevel + ARCADE_EVENT_LEVEL_INCREASE);
    return (newLevel >= MAX_LEVEL) ? MAX_LEVEL : newLevel;
}

static bool32 HaveMonsBeenSwapped(void)
{
    struct Pokemon *frontierMon;
    struct Pokemon *playerMon;
    u32 playerMonPersonality, frontierMonPersonality, i, monId;

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        monId = gSaveBlock2Ptr->frontier.selectedPartyMons[i] - 1;
        if (monId >= PARTY_SIZE)
            continue;

        frontierMon = &gSaveBlock1Ptr->playerParty[monId];
        playerMon = &gPlayerParty[i];

        playerMonPersonality = GetMonData(playerMon, MON_DATA_PERSONALITY,NULL);
        frontierMonPersonality = GetMonData(frontierMon, MON_DATA_PERSONALITY,NULL);

        if (playerMonPersonality == frontierMonPersonality)
            continue;

        return TRUE;
    }
    return FALSE;
}

static bool32 BattleArcade_DoSun(void)
{
    return BattleArcade_DoWeather(WEATHER_DROUGHT);
}
static bool32 BattleArcade_DoRain(void)
{
    return BattleArcade_DoWeather(WEATHER_DOWNPOUR);
}
static bool32 BattleArcade_DoSand(void)
{
    return BattleArcade_DoWeather(WEATHER_SANDSTORM);
}
static bool32 BattleArcade_DoHail(void)
{
    return BattleArcade_DoWeather(WEATHER_SNOW);
}
static bool32 BattleArcade_DoFog(void)
{
    return BattleArcade_DoWeather(WEATHER_FOG_HORIZONTAL);
}

static bool32 BattleArcade_DoWeather(u32 weather)
{
    SetSavedWeather(weather);
    DoCurrentWeather();
    return TRUE;
}

static bool32 BattleArcade_DoTrickRoom(void)
{
  SetStartingStatus(STARTING_STATUS_TRICK_ROOM);
    return TRUE;
}

static bool32 BattleArcade_DoSwap(void)
{
    u32 i;
    struct Pokemon tempParty[MAX_FRONTIER_PARTY_SIZE];

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            break;

        CopyMon(&tempParty[i],&gPlayerParty[i],sizeof(gPlayerParty[i]));
        CopyMon(&gPlayerParty[i],&gEnemyParty[i],sizeof(gEnemyParty[i]));
        CopyMon(&gEnemyParty[i],&tempParty[i],sizeof(tempParty[i]));
    }
    return TRUE;
}

static bool32 BattleArcade_DoSpeedUp(void)
{
    BattleArcade_ChangeSpeed(ARCADE_EVENT_SPEED_UP);
    return TRUE;
}

static bool32 BattleArcade_DoSpeedDown(void)
{
    BattleArcade_ChangeSpeed(ARCADE_EVENT_SPEED_DOWN);
    return TRUE;
}

static bool32 BattleArcade_ChangeSpeed(u32 mode)
{
    u32 currentSpeed = GetCursorSpeed();
    u32 boundarySpeed = (mode == ARCADE_EVENT_SPEED_UP) ? ARCADE_SPEED_LEVEL_MAX : ARCADE_SPEED_LEVEL_MIN;

    if (currentSpeed == boundarySpeed)
    {
        currentSpeed = boundarySpeed;
    }
    else if (mode == ARCADE_EVENT_SPEED_UP)
    {
        currentSpeed++;
        if (currentSpeed > ARCADE_SPEED_LEVEL_MAX)
            currentSpeed = ARCADE_SPEED_LEVEL_MAX;
    }
    else
{
        currentSpeed--;

        if (currentSpeed < ARCADE_SPEED_LEVEL_MIN)
            currentSpeed = ARCADE_SPEED_LEVEL_MIN;
    }

    SetCursorSpeed(currentSpeed);
    return TRUE;
}

static u32 GetCursorSpeed(void)
{
    return ARCADE_SAVEDATA_CURSOR.speed;
}

static void SetCursorSpeed(u32 speed)
{
    ARCADE_SAVEDATA_CURSOR.speed = speed;
}

static bool32 BattleArcade_DoRandom(void)
{
    SetCursorRandomMode();
    return TRUE;
}

static void SetCursorRandomMode(void)
{
    ARCADE_SAVEDATA_CURSOR.isRandom = TRUE;
}

static bool32 BattleArcade_DoGiveBPSmall(void)
{
    return TRUE;
}

static bool32 BattleArcade_DoGiveBPBig(void)
{
    return TRUE;
}

static bool32 BattleArcade_DoNoBattle(void)
{
    return TRUE;
}

static bool32 BattleArcade_DoNoEvent(void)
{
    return TRUE;
}

static const struct BgTemplate sArcadeRecordBgTemplates[BG_RECORD_COUNT] =
    {
        {
            .bg = BG_RECORD_TEXT,
            .charBaseIndex = 1,
            .mapBaseIndex = 31,
            .screenSize = 0,
            .paletteMode = 0,
            .priority = 0,
            .baseTile = 0,
        },
        {
            .bg = BG_RECORD_BACKGROUND,
            .charBaseIndex = 0,
            .mapBaseIndex = 6,
            .screenSize = 0,
            .paletteMode = 0,
            .priority = 1,
            .baseTile = 0,
        },
    };

static const struct WindowTemplate sArcadeRecordWinTemplates[WIN_RECORD_COUNT] =
    {
        [WIN_RECORD_TEXT] =
        {
            .bg = BG_RECORD_TEXT,
            .tilemapLeft = 3,
            .tilemapTop = 1,
            .width = 26,
            .height = 16,
            .paletteNum = 15,
            .baseBlock = 1,
        },
        DUMMY_WIN_TEMPLATE,
    };

static const u32 sRecordsTilemap[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/records/backgrounds/background.bin.smolTM");
static const u32 sRecordsTiles[] = INCBIN_U32("graphics/battle_frontier/battle_arcade/records/backgrounds/background.4bpp.smol");
static const u16 sRecordsPalettes[] = INCBIN_U16("graphics/battle_frontier/battle_arcade/records/palettes/background.gbapal");

static void Task_OpenArcadeRecord(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    CleanupOverworldWindowsAndTilemaps();
    ArcadeRecords_Init(CB2_ReturnToFieldFadeFromBlack);
    DestroyTask(taskId);
}

static void ArcadeRecords_Init(MainCallback callback)
{
    SetMainCallback2(ArcadeRecords_SetupCB);
}

static void ArcadeRecords_SetupCB(void)
{
    switch (gMain.state)
    {
        case 0:
            DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
            SetVBlankHBlankCallbacksToNull();
            ClearScheduledBgCopiesToVram();
            gMain.state++;
            break;
        case 1:
            ScanlineEffect_Stop();
            FreeAllSpritePalettes();
            ResetPaletteFade();
            ResetSpriteData();
            ResetTasks();
            gMain.state++;
            break;
        case 2:
            if (ArcadeRecords_InitBgs())
                gMain.state++;
            else
            {
                ArcadeRecord_FadeAndBail();
                return;
            }
            break;
        case 3:
            if (ArcadeRecord_LoadGraphics() == TRUE)
                gMain.state++;
            break;
        case 4:
            ArcadeRecord_InitWindows();
            gMain.state++;
            break;
        case 5:
            DisplayRecordsText();
            CreateTask(Task_ArcadeRecordWaitFadeIn, 0);
            gMain.state++;
            break;
        case 6:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            gMain.state++;
            break;
        case 7:
            SetVBlankCallback(VBlankCB);
            SetMainCallback2(MainCB);
            break;
    }
}

static EWRAM_DATA u8 arcadeRecordLoadState = 0;

static bool8 ArcadeRecords_InitBgs(void)
{
    ResetAllBgsCoordinates();

    if (!ArcadeRecords_AllocTilemapBuffers())
        return FALSE;
    ArcadeRecord_HandleAndShowBgs();

    return TRUE;
}

static bool32 ArcadeRecords_AllocTilemapBuffers(void)
{
    u32 backgroundId;

    for (backgroundId = 0; backgroundId < BG_RECORD_COUNT; backgroundId++)
    {
        sBgTilemapBuffer[backgroundId] = AllocZeroed(ARCADE_TILEMAP_BUFFER_SIZE);

        if (sBgTilemapBuffer[backgroundId] == NULL)
            return FALSE;
    }
    return TRUE;
}

static void ArcadeRecord_HandleAndShowBgs(void)
{
    u32 backgroundId;

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sArcadeRecordBgTemplates, NELEMS(sArcadeRecordBgTemplates));

    for (backgroundId = 0; backgroundId < BG_RECORD_COUNT; backgroundId++)
        ArcadeRecord_SetScheduleShowBgs(backgroundId);
}

static void ArcadeRecord_SetScheduleShowBgs(u32 backgroundId)
{
    SetBgTilemapBuffer(backgroundId, sBgTilemapBuffer[backgroundId]);
    ScheduleBgCopyTilemapToVram(backgroundId);
    ShowBg(backgroundId);
}

static void ArcadeRecord_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_ArcadeRecordWaitFadeAndBail, 0);

    SetVBlankCallback(VBlankCB);
    SetMainCallback2(MainCB);
}

static void Task_ArcadeRecordWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(CB2_ReturnToFieldFadeFromBlack);
        ArcadeRecord_FreeResources();
        DestroyTask(taskId);
    }
}

static bool8 ArcadeRecord_LoadGraphics(void)
{
    switch (arcadeRecordLoadState)
    {
        case 0:
            ResetTempTileDataBuffers();

            DecompressAndCopyTileDataToVram(BG_RECORD_BACKGROUND, sRecordsTiles, 0, 0, 0);
            arcadeRecordLoadState++;
            break;
        case 1:
            if (FreeTempTileDataBuffersIfPossible() != TRUE)
            {
                DecompressDataWithHeaderWram(sRecordsTilemap, sBgTilemapBuffer[BG_RECORD_BACKGROUND]);
                arcadeRecordLoadState++;
            }
            break;
        case 2:
            LoadPalette(sRecordsPalettes, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
            arcadeRecordLoadState++;
        default:
            arcadeRecordLoadState = 0;
            return TRUE;
    }
    return FALSE;
}

static void ArcadeRecord_InitWindows(void)
{
    u32 windowId;
    InitWindows(sArcadeRecordWinTemplates);

    DeactivateAllTextPrinters();

    ScheduleBgCopyTilemapToVram(0);

    for (windowId = 0; windowId < WIN_RECORD_COUNT; windowId++)
    {
        FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

static void Task_ArcadeRecordWaitFadeIn(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    gTasks[taskId].func = Task_RecordsWaitForKeyPress;
}


static void Task_RecordsWaitForKeyPress(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_ArcadeRecord_CleanUp;
    }
}

static void Task_ArcadeRecord_CleanUp(u8 taskId)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_ArcadeRecordWaitFadeAndExitGracefully;
}

static void Task_ArcadeRecordWaitFadeAndExitGracefully(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(CB2_ReturnToFieldFadeFromBlack);
        ArcadeRecord_FreeResources();
        DestroyTask(taskId);
    }
}

static void ArcadeRecord_FreeResources(void)
{
    u32 backgroundId;

    for (backgroundId = 0; backgroundId < BG_RECORD_COUNT; backgroundId++)
    {
        if (sBgTilemapBuffer[backgroundId] != NULL)
            Free(sBgTilemapBuffer[backgroundId]);
    }

    FreeAllWindowBuffers();
    ResetSpriteData();
}

static const u8 *BattleArcade_GetRecordName(void)
{
    switch(gSpecialVar_0x8006)
    {
        case FRONTIER_MODE_SINGLES:
            return gText_Single2;
        case FRONTIER_MODE_DOUBLES:
            return gText_Double;
        default:
        case FRONTIER_MODE_LINK_MULTIS:
            return gText_Multi;
    }
}

static const u8 *BattleArcade_GenerateRecordName(void)
{
    StringCopy(gStringVar3,BattleArcade_GetRecordName());
    StringAppend(gStringVar3,gText_Space);
    StringAppend(gStringVar3,gText_Record);
    return gStringVar3;
}

static void HandleHeader(u32 windowId, u32 fontID, u32 letterSpacing, u32 lineSpacing, u8 *color, u32 speed, u32 lvlMode)
{
    static const u8 sText_BattleArcade[] = _("Rocket Arcade");

    AddTextPrinterParameterized4(windowId, fontID, 0,ARCADE_RECORD_HEADER_Y_POSITION, letterSpacing, lineSpacing, color, speed, sText_BattleArcade);
    AddTextPrinterParameterized4(windowId, fontID, 122, ARCADE_RECORD_HEADER_Y_POSITION, letterSpacing, lineSpacing, color, speed, BattleArcade_GenerateRecordName());
}

static void HandleRecord(u32 windowId, u32 fontID, u32 letterSpacing, u32 lineSpacing, u8 *color, u32 speed, u32 mode)
{
    u32 lvlMode, streakIndex;
    u32 loopIterations = 0;

    for (lvlMode = 0; lvlMode < FRONTIER_LVL_MODE_COUNT ; lvlMode++)
        for (streakIndex = 0; streakIndex < ARCADE_RECORD_STREAK_INDEX_COUNT; streakIndex++)
            PrintRecordHeaderLevelRecord(windowId, fontID, letterSpacing, lineSpacing, color, speed, streakIndex, lvlMode, loopIterations++);
}

static u32 CalculateRecordRowYPosition(u32 loopIterations)
{
    return (50 +
    (loopIterations * 20));
}

static void PrintRecordHeaderLevelRecord(u32 windowId, u32 fontID, u32 letterSpacing, u32 lineSpacing, u8 *color, u32 speed, u32 streakIndex, u32 lvlMode, u32 loopIterations)
{
    u32 y = CalculateRecordRowYPosition(loopIterations);

    PrintRecordHeader(windowId, fontID, letterSpacing, lineSpacing, color, speed,streakIndex,lvlMode,y);
    PrintRecordLevelMode(windowId, fontID, letterSpacing, lineSpacing, color, speed,streakIndex,lvlMode,y);
    PrintRecord(windowId, fontID, letterSpacing, lineSpacing, color, speed,streakIndex,lvlMode,y);
}

static const u8 *BattleArcade_GetRecordHeaderName(u32 level, u32 streakIndex)
{
    bool32 isStreakActive = ((FRONTIER_SAVEDATA.winStreakActiveFlags & sStreakFlags[gSpecialVar_0x8006][level]));

    if (streakIndex == 0 && isStreakActive)
        return gText_Current;
    else if (streakIndex == 0)
        return gText_Prev;
    else
        return gText_Record;
}

static void PrintRecordHeader(u32 windowId, u32 fontID, u32 letterSpacing, u32 lineSpacing, u8 *color, u32 speed, u32 streakIndex, u32 level, u32 y)
{
    AddTextPrinterParameterized4(windowId, fontID, 0,y, letterSpacing, lineSpacing, color, speed, BattleArcade_GetRecordHeaderName(level, streakIndex));
}

static const u8 *BattleArcade_GetLevelText(u32 level)
{
    if (level == FRONTIER_LVL_50)
        return gText_Lv502;
    else
        return gText_OpenLv;
}

static void PrintRecordLevelMode(u32 windowId, u32 fontID, u32 letterSpacing, u32 lineSpacing, u8 *color, u32 speed, u32 streakStatus, u32 level, u32 y)
{
    AddTextPrinterParameterized4(windowId, fontID, 45,y, letterSpacing, lineSpacing, color, speed, BattleArcade_GetLevelText(level));
}

static u32 GetRecordValue(u32 level, u32 streakIndex)
{
    u32 mode = gSpecialVar_0x8006;

    if (streakIndex == 0)
        return ARCADE_SAVEDATA_CURRENT_STREAK[mode][level];
    else
        return ARCADE_SAVEDATA_RECORD_STREAK[mode][level];
}

static void PrintRecord(u32 windowId, u32 fontID, u32 letterSpacing, u32 lineSpacing, u8 *color, u32 speed, u32 streakIndex, u32 level, u32 y)
{
    u32 record = GetRecordValue(level, streakIndex);
    static const u8 sText_GamesStreak[] = _("Games cleared: {STR_VAR_1}");

    ConvertIntToDecimalStringN(gStringVar1,record,STR_CONV_MODE_LEFT_ALIGN,CountDigits(record));
    StringExpandPlaceholders(gStringVar4,sText_GamesStreak);
    AddTextPrinterParameterized4(windowId, fontID, 95,y, letterSpacing, lineSpacing, color, speed, gStringVar4);
}

static void GenerateRecordText(void)
{
    u32 windowId = 0;
    u32 fontID = FONT_NORMAL;
    u32 letterSpacing = GetFontAttribute(fontID,FONTATTR_LETTER_SPACING);
    u32 lineSpacing = GetFontAttribute(fontID,FONTATTR_LINE_SPACING);
    u8 color[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};
    u32 speed = TEXT_SKIP_DRAW;

    HandleHeader(windowId, fontID, letterSpacing, lineSpacing, color, speed,FRONTIER_LVL_OPEN);
    HandleRecord(windowId, fontID, letterSpacing, lineSpacing, color, speed,FRONTIER_LVL_50);
}

static void DisplayRecordsText(void)
{
    GenerateRecordText();
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);
}
