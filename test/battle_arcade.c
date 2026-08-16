#include "global.h"
#include "battle_arcade.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "event_data.h"
#include "money.h"
#include "pokemon.h"
#include "string_util.h"
#include "strings.h"
#include "test/battle.h"
#include "test/test.h"
#include "constants/battle_arcade.h"
#include "constants/battle.h"
#include "constants/battle_frontier.h"
#include "constants/battle_tower.h"
#include "constants/frontier_util.h"
#include "constants/opponents.h"

TEST("Rocket Arcade exposes seven payouts ending at 384000")
{
    static const u32 expectedPayouts[] =
    {
        4000,
        8000,
        12000,
        24000,
        48000,
        96000,
        384000,
    };

    TRAINER_BATTLE_PARAM.opponentA = TRAINER_NONE;
    for (u32 win = 1; win <= ARRAY_COUNT(expectedPayouts); win++)
    {
        SetMoney(&gSaveBlock1Ptr->money, 0);
        FRONTIER_SAVEDATA.curChallengeBattleNum = win;
        gSpecialVar_0x8004 = ARCADE_FUNC_AWARD_PRIZE;
        CallBattleArcadeFunc();
        EXPECT_EQ(gSaveBlock1Ptr->money, expectedPayouts[win - 1]);
    }
}

TEST("Rocket Arcade clamps prize money to the seventh round payout")
{
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_NONE;
    SetMoney(&gSaveBlock1Ptr->money, 0);
    FRONTIER_SAVEDATA.curChallengeBattleNum = FRONTIER_STAGES_PER_CHALLENGE + 1;

    gSpecialVar_0x8004 = ARCADE_FUNC_AWARD_PRIZE;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSaveBlock1Ptr->money, 384000);
    EXPECT_EQ(StringCompare(gStringVar2, COMPOUND_STRING("384000")), 0);
}

TEST("Rocket Arcade doubles the final payout for defeating its Brain")
{
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_FRONTIER_BRAIN;
    FRONTIER_SAVEDATA.curChallengeBattleNum = FRONTIER_STAGES_PER_CHALLENGE;
    SetMoney(&gSaveBlock1Ptr->money, 0);

    gSpecialVar_0x8004 = ARCADE_FUNC_AWARD_PRIZE;
    CallBattleArcadeFunc();
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 768000);
    EXPECT_EQ(StringCompare(gStringVar2, COMPOUND_STRING("768000")), 0);

    SetMoney(&gSaveBlock1Ptr->money, MAX_MONEY - 1000);
    CallBattleArcadeFunc();
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), MAX_MONEY);
}

TEST("Rocket Arcade double down follows the fixed round payouts")
{
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_NONE;
    SetMoney(&gSaveBlock1Ptr->money, 0);
    FRONTIER_SAVEDATA.curChallengeBattleNum = 1;
    FRONTIER_SAVEDATA.rocketArcadePendingPrize = 0;
    FlagClear(FLAG_ROCKET_ARCADE_DOUBLED_DOWN);

    gSpecialVar_0x8004 = ARCADE_FUNC_DOUBLE_DOWN;
    CallBattleArcadeFunc();
    EXPECT(FlagGet(FLAG_ROCKET_ARCADE_DOUBLED_DOWN));

    FRONTIER_SAVEDATA.curChallengeBattleNum = 2;
    gSpecialVar_0x8004 = ARCADE_FUNC_DOUBLE_DOWN;
    CallBattleArcadeFunc();

    FRONTIER_SAVEDATA.curChallengeBattleNum = 3;
    gSpecialVar_0x8004 = ARCADE_FUNC_BUFFER_PRIZE;
    CallBattleArcadeFunc();
    EXPECT_EQ(StringCompare(gStringVar1, COMPOUND_STRING("12000")), 0);

    gSpecialVar_0x8004 = ARCADE_FUNC_AWARD_PRIZE;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSaveBlock1Ptr->money, 12000);
    EXPECT_EQ(StringCompare(gStringVar2, COMPOUND_STRING("12000")), 0);
    EXPECT(!FlagGet(FLAG_ROCKET_ARCADE_DOUBLED_DOWN));
}

TEST("Rocket Arcade initializes its first battle as round one")
{
    VarSet(VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES);
    FRONTIER_SAVEDATA.lvlMode = FRONTIER_LVL_50;
    FRONTIER_SAVEDATA.curChallengeBattleNum = 1;

    gSpecialVar_0x8004 = ARCADE_FUNC_INIT;
    CallBattleArcadeFunc();
    EXPECT_EQ(FRONTIER_SAVEDATA.curChallengeBattleNum, 0);

    gSpecialVar_0x8004 = ARCADE_FUNC_SET_BATTLE_WON;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSpecialVar_Result, 1);
}

TEST("Rocket Arcade opponent setup preserves the local round after an early cash out")
{
    VarSet(VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARCADE);
    VarSet(VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES);
    FRONTIER_SAVEDATA.lvlMode = FRONTIER_LVL_50;
    ARCADE_SAVEDATA_CURRENT_STREAK[FRONTIER_MODE_SINGLES][FRONTIER_LVL_50] = 1;
    FRONTIER_SAVEDATA.winStreakActiveFlags = STREAK_ARCADE_SINGLES_50;

    gSpecialVar_0x8004 = ARCADE_FUNC_INIT;
    CallBattleArcadeFunc();
    EXPECT_EQ(FRONTIER_SAVEDATA.curChallengeBattleNum, 0);

    gSpecialVar_0x8004 = BATTLE_TOWER_FUNC_SET_OPPONENT;
    CallBattleTowerFunc();
    EXPECT_EQ(FRONTIER_SAVEDATA.curChallengeBattleNum, 0);

    gSpecialVar_0x8004 = ARCADE_FUNC_SET_BATTLE_WON;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSpecialVar_Result, 1);

    gSpecialVar_0x8004 = BATTLE_TOWER_FUNC_SET_OPPONENT;
    CallBattleTowerFunc();
    EXPECT_EQ(FRONTIER_SAVEDATA.curChallengeBattleNum, 1);
}

TEST("Rocket Arcade Classic opponent generation ignores stale Battle Cafe state")
{
    VarSet(VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARCADE);
    VarSet(VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES);
    FRONTIER_SAVEDATA.lvlMode = FRONTIER_LVL_50;
    TRAINER_BATTLE_PARAM.opponentA = FRONTIER_TRAINER_BRADY;
    CreateMon(&gPlayerParty[0], SPECIES_BULBASAUR, FRONTIER_MAX_LEVEL_50, 0, OTID_STRUCT_PLAYER_ID);

    gBattleScripting.specialTrainerBattleType = FACILITY_BATTLE_CAFE;
    gSpecialVar_0x8004 = ARCADE_FUNC_GENERATE_OPPONENT;
    CallBattleArcadeFunc();

    for (u32 i = 0; i < FRONTIER_PARTY_SIZE; i++)
        EXPECT_EQ(GetMonData(&gEnemyParty[i], MON_DATA_LEVEL), FRONTIER_MAX_LEVEL_50);
}

TEST("Rocket Arcade schedules the Brain for the final battle of a set")
{
    VarSet(VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES);
    FRONTIER_SAVEDATA.lvlMode = FRONTIER_LVL_50;
    FlagClear(FLAG_ARCADE_SILVER_PRINT);
    FlagClear(FLAG_ARCADE_GOLD_PRINT);
    FRONTIER_SAVEDATA.curChallengeBattleNum = FRONTIER_STAGES_PER_CHALLENGE - 2;
    ARCADE_SAVEDATA_CURRENT_STREAK[FRONTIER_MODE_SINGLES][FRONTIER_LVL_50] = ARCADE_SILVER_BATTLE_NUMBER + 1;

    gSpecialVar_0x8004 = ARCADE_FUNC_CHECK_BRAIN_STATUS;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSpecialVar_Result, FRONTIER_BRAIN_NOT_READY);

    FRONTIER_SAVEDATA.curChallengeBattleNum = FRONTIER_STAGES_PER_CHALLENGE - 1;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSpecialVar_Result, ARCADE_SYMBOL_SILVER);

    FlagSet(FLAG_ARCADE_SILVER_PRINT);
    ARCADE_SAVEDATA_CURRENT_STREAK[FRONTIER_MODE_SINGLES][FRONTIER_LVL_50] = ARCADE_GOLD_BATTLE_NUMBER + 1;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSpecialVar_Result, ARCADE_SYMBOL_GOLD);
}

TEST("Rocket Arcade awards prints when a Brain milestone was delayed until the final battle")
{
    VarSet(VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES);
    FRONTIER_SAVEDATA.lvlMode = FRONTIER_LVL_50;
    FlagClear(FLAG_ARCADE_SILVER_PRINT);
    FlagClear(FLAG_ARCADE_GOLD_PRINT);
    ARCADE_SAVEDATA_CURRENT_STREAK[FRONTIER_MODE_SINGLES][FRONTIER_LVL_50] = ARCADE_SILVER_BATTLE_NUMBER + 2;

    gSpecialVar_0x8004 = ARCADE_FUNC_CHECK_SYMBOL;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSpecialVar_Result, ARCADE_SYMBOL_SILVER);

    FlagSet(FLAG_ARCADE_SILVER_PRINT);
    ARCADE_SAVEDATA_CURRENT_STREAK[FRONTIER_MODE_SINGLES][FRONTIER_LVL_50] = ARCADE_GOLD_BATTLE_NUMBER + 2;
    CallBattleArcadeFunc();
    EXPECT_EQ(gSpecialVar_Result, ARCADE_SYMBOL_GOLD);
}

SINGLE_BATTLE_TEST("Pika Papow uses the player's friendship in Rocket Arcade battles", s16 damage)
{
    u32 friendship;

    PARAMETRIZE { friendship = 0; }
    PARAMETRIZE { friendship = 200; }
    GIVEN {
        gBattleTestRunnerState->data.recordedBattle.battleFlags |= BATTLE_TYPE_BATTLE_TOWER;
        PLAYER(SPECIES_PIKACHU) {
            Friendship(friendship);
            Speed(2);
            Moves(MOVE_PIKA_PAPOW);
        }
        OPPONENT(SPECIES_WOBBUFFET) {
            Speed(1);
            Moves(MOVE_SPLASH);
        }
    } WHEN {
        TURN { MOVE(player, MOVE_PIKA_PAPOW); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PIKA_PAPOW, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_EQ(player->friendship, friendship);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_FRIENDSHIP), friendship);
        if (i > 0)
            EXPECT_GT(results[i].damage, results[i - 1].damage);
    }
}
