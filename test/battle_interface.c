#include "global.h"
#include "battle.h"
#include "battle_interface.h"
#include "battle_util.h"
#include "sprite.h"
#include "constants/items.h"
#include "constants/abilities.h"
#include "task.h"
#include "test/test.h"

#define SWAP_TASK_TARGET_BALL 3

TEST("A malformed zero-EXP bar state still completes")
{
    EXPECT(BattleInterface_TestMalformedExpBarCompletes());
}

TEST("Last-used ball swaps coalesce rapid input to the latest ball")
{
    gBallToDisplay = ITEM_POKE_BALL;
    SwapBallToDisplay(FALSE);

    EXPECT_EQ(GetTaskCount(), 1);
    EXPECT_EQ(gTasks[0].data[SWAP_TASK_TARGET_BALL], ITEM_POKE_BALL);

    gBallToDisplay = ITEM_GREAT_BALL;
    SwapBallToDisplay(FALSE);
    gBallToDisplay = ITEM_ULTRA_BALL;
    SwapBallToDisplay(FALSE);

    EXPECT_EQ(GetTaskCount(), 1);
    EXPECT_EQ(gTasks[0].data[SWAP_TASK_TARGET_BALL], ITEM_ULTRA_BALL);

    DestroyTask(0);
}

static void SetUpAbilityPopUpFailureTest(struct BattleStruct *battleStruct)
{
    memset(battleStruct, 0, sizeof(*battleStruct));
    gBattleStruct = battleStruct;
    gBattlersCount = 2;
    gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetTasks();
}

TEST("Ability pop-up fails cleanly when no task slot is available")
{
    struct BattleStruct battleStruct;
    struct BattleStruct *savedBattleStruct = gBattleStruct;
    u8 savedBattlersCount = gBattlersCount;
    u8 savedBattlerPosition = gBattlerPositions[0];

    SetUpAbilityPopUpFailureTest(&battleStruct);
    for (u32 i = 0; i < NUM_TASKS; i++)
        EXPECT_NE(TryCreateTask(TaskDummy, i), TASK_NONE);

    EXPECT(!BattleInterface_TestCreateAbilityPopUp(0, ABILITY_DRIZZLE, FALSE));
    EXPECT(!battleStruct.battlerState[0].activeAbilityPopUps);
    EXPECT_EQ(GetTaskCount(), NUM_TASKS);

    ResetTasks();
    gBattleStruct = savedBattleStruct;
    gBattlersCount = savedBattlersCount;
    gBattlerPositions[0] = savedBattlerPosition;
}

TEST("Ability pop-up update is ignored after creation fails")
{
    struct BattleStruct battleStruct;
    struct BattleStruct *savedBattleStruct = gBattleStruct;
    u8 savedBattlersCount = gBattlersCount;
    u8 savedBattlerPosition = gBattlerPositions[0];
    enum Ability savedAbility = gBattleMons[0].ability;

    SetUpAbilityPopUpFailureTest(&battleStruct);
    gBattleMons[0].ability = ABILITY_DRIZZLE;
    for (u32 i = 0; i < NUM_TASKS; i++)
        EXPECT_NE(TryCreateTask(TaskDummy, i), TASK_NONE);

    EXPECT(!BattleInterface_TestCreateAbilityPopUp(0, ABILITY_DRIZZLE, FALSE));
    PushTraitStack(0, ABILITY_DRIZZLE);
    EXPECT(!BattleInterface_TestUpdateAbilityPopUp(0));
    EXPECT_EQ(PullTraitStackAbility(), ABILITY_NONE);
    EXPECT(!battleStruct.battlerState[0].activeAbilityPopUps);

    ResetTasks();
    gBattleMons[0].ability = savedAbility;
    gBattleStruct = savedBattleStruct;
    gBattlersCount = savedBattlersCount;
    gBattlerPositions[0] = savedBattlerPosition;
}

TEST("Ability pop-up fails cleanly when no OBJ palette is available")
{
    struct BattleStruct battleStruct;
    struct BattleStruct *savedBattleStruct = gBattleStruct;
    u8 savedBattlersCount = gBattlersCount;
    u8 savedBattlerPosition = gBattlerPositions[0];

    SetUpAbilityPopUpFailureTest(&battleStruct);
    for (u32 i = 0; i < 16; i++)
        EXPECT_NE(AllocSpritePalette(i + 1), 0xFF);

    EXPECT(!BattleInterface_TestCreateAbilityPopUp(0, ABILITY_DRIZZLE, FALSE));
    EXPECT(!battleStruct.battlerState[0].activeAbilityPopUps);
    EXPECT_EQ(GetTaskCount(), 0);

    FreeAllSpritePalettes();
    gBattleStruct = savedBattleStruct;
    gBattlersCount = savedBattlersCount;
    gBattlerPositions[0] = savedBattlerPosition;
}

TEST("Ability pop-up fails cleanly and releases its palette when OBJ tiles are full")
{
    struct BattleStruct battleStruct;
    struct BattleStruct *savedBattleStruct = gBattleStruct;
    u8 savedBattlersCount = gBattlersCount;
    u8 savedBattlerPosition = gBattlerPositions[0];

    SetUpAbilityPopUpFailureTest(&battleStruct);
    while (AllocSpriteTiles(16) >= 0)
        ;

    EXPECT(!BattleInterface_TestCreateAbilityPopUp(0, ABILITY_DRIZZLE, FALSE));
    EXPECT(!battleStruct.battlerState[0].activeAbilityPopUps);
    EXPECT_EQ(GetTaskCount(), 0);
    for (u32 i = 0; i < 16; i++)
        EXPECT_NE(AllocSpritePalette(i + 1), 0xFF);

    ResetSpriteData();
    FreeAllSpritePalettes();
    gBattleStruct = savedBattleStruct;
    gBattlersCount = savedBattlersCount;
    gBattlerPositions[0] = savedBattlerPosition;
}

TEST("Ability pop-up fails cleanly when fewer than two sprite slots are available")
{
    struct BattleStruct battleStruct;
    struct BattleStruct *savedBattleStruct = gBattleStruct;
    u8 savedBattlersCount = gBattlersCount;
    u8 savedBattlerPosition = gBattlerPositions[0];

    SetUpAbilityPopUpFailureTest(&battleStruct);
    for (u32 i = 0; i < MAX_SPRITES - 1; i++)
        EXPECT_LT(CreateSprite(&gDummySpriteTemplate, 0, 0, 0), MAX_SPRITES);

    EXPECT(!BattleInterface_TestCreateAbilityPopUp(0, ABILITY_DRIZZLE, FALSE));
    EXPECT(!battleStruct.battlerState[0].activeAbilityPopUps);
    EXPECT_EQ(GetTaskCount(), 0);

    ResetSpriteData();
    FreeAllSpritePalettes();
    gBattleStruct = savedBattleStruct;
    gBattlersCount = savedBattlersCount;
    gBattlerPositions[0] = savedBattlerPosition;
}

#undef SWAP_TASK_TARGET_BALL
