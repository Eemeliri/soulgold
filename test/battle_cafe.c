#include "global.h"
#include "achievements.h"
#include "battle.h"
#include "battle_tower.h"
#include "event_data.h"
#include "item.h"
#include "pokedex.h"
#include "pokemon.h"
#include "replay_options.h"
#include "test/test.h"
#include "constants/battle_frontier.h"
#include "constants/battle.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/pokedex.h"
#include "constants/vars.h"

static const u16 sTestBattleCafePastParadoxDexNums[] =
{
    NATIONAL_DEX_GREAT_TUSK,
    NATIONAL_DEX_SCREAM_TAIL,
    NATIONAL_DEX_BRUTE_BONNET,
    NATIONAL_DEX_FLUTTER_MANE,
    NATIONAL_DEX_SLITHER_WING,
    NATIONAL_DEX_SANDY_SHOCKS,
    NATIONAL_DEX_ROARING_MOON,
    NATIONAL_DEX_WALKING_WAKE,
    NATIONAL_DEX_GOUGING_FIRE,
    NATIONAL_DEX_RAGING_BOLT,
};

static const u16 sTestBattleCafeFutureParadoxDexNums[] =
{
    NATIONAL_DEX_IRON_TREADS,
    NATIONAL_DEX_IRON_BUNDLE,
    NATIONAL_DEX_IRON_HANDS,
    NATIONAL_DEX_IRON_JUGULIS,
    NATIONAL_DEX_IRON_MOTH,
    NATIONAL_DEX_IRON_THORNS,
    NATIONAL_DEX_IRON_VALIANT,
    NATIONAL_DEX_IRON_LEAVES,
    NATIONAL_DEX_IRON_BOULDER,
    NATIONAL_DEX_IRON_CROWN,
};

static void CatchBattleCafeTestSpecies(const u16 *dexNums, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++)
        GetSetPokedexFlag(dexNums[i], FLAG_SET_CAUGHT);
}

TEST("Battle Cafe Endless Challenge records its own streak")
{
    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE);
    VarSet(VAR_TEMP_9, 7);
    VarSet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD, 6);
    VarSet(VAR_BATTLE_CAFE_ENDLESS_RUSH_RECORD, 12);

    BattleCafe_AdvanceWinCount();

    EXPECT_EQ(VarGet(VAR_TEMP_9), 8);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD), 8);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_ENDLESS_RUSH_RECORD), 12);
}

TEST("Battle Cafe Endless Rush records its own streak")
{
    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH);
    VarSet(VAR_TEMP_9, 14);
    VarSet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD, 20);
    VarSet(VAR_BATTLE_CAFE_ENDLESS_RUSH_RECORD, 9);

    BattleCafe_AdvanceWinCount();

    EXPECT_EQ(VarGet(VAR_TEMP_9), 15);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD), 20);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_ENDLESS_RUSH_RECORD), 15);
}

TEST("Battle Cafe Endless Challenge unlocks Endless Master at 15 wins")
{
    const struct Achievement *achievement = Achievement_GetById(ACH_BATTLE_CAFE_ENDLESS_MASTER);

    EXPECT(achievement != NULL);
    EXPECT_EQ(achievement->tier, ACH_TIER_PLATINUM);
    EXPECT_EQ(Achievement_GetTierBallItem(achievement->tier), ITEM_MASTER_BALL);

    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE);
    VarSet(VAR_TEMP_9, BATTLE_CAFE_ENDLESS_MASTER_STREAK - 2);

    BattleCafe_AdvanceWinCount();
    EXPECT_EQ(VarGet(VAR_TEMP_9), BATTLE_CAFE_ENDLESS_MASTER_STREAK - 1);
    EXPECT(!Achievement_IsUnlocked(ACH_BATTLE_CAFE_ENDLESS_MASTER));

    BattleCafe_AdvanceWinCount();
    EXPECT_EQ(VarGet(VAR_TEMP_9), BATTLE_CAFE_ENDLESS_MASTER_STREAK);
    EXPECT(Achievement_IsUnlocked(ACH_BATTLE_CAFE_ENDLESS_MASTER));
}

TEST("Battle Cafe Endless Rush does not unlock Endless Master")
{
    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH);
    VarSet(VAR_TEMP_9, BATTLE_CAFE_ENDLESS_MASTER_STREAK - 1);

    BattleCafe_AdvanceWinCount();

    EXPECT_EQ(VarGet(VAR_TEMP_9), BATTLE_CAFE_ENDLESS_MASTER_STREAK);
    EXPECT(!Achievement_IsUnlocked(ACH_BATTLE_CAFE_ENDLESS_MASTER));
}

TEST("Battle Cafe fixed challenges do not change Endless records")
{
    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY);
    VarSet(VAR_TEMP_9, 1);
    VarSet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD, 4);
    VarSet(VAR_BATTLE_CAFE_ENDLESS_RUSH_RECORD, 5);

    BattleCafe_AdvanceWinCount();

    EXPECT_EQ(VarGet(VAR_TEMP_9), 2);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD), 4);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_ENDLESS_RUSH_RECORD), 5);
}

TEST("Battle Cafe streaks saturate without wrapping")
{
    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE);
    VarSet(VAR_TEMP_9, BATTLE_CAFE_MAX_STREAK);
    VarSet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD, BATTLE_CAFE_MAX_STREAK - 1);

    BattleCafe_AdvanceWinCount();

    EXPECT_EQ(VarGet(VAR_TEMP_9), BATTLE_CAFE_MAX_STREAK);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_ENDLESS_CHALLENGE_RECORD), BATTLE_CAFE_MAX_STREAK);
}

TEST("Battle Cafe point awards saturate and report the amount received")
{
    VarSet(VAR_BATTLE_CAFE_POINTS, BATTLE_CAFE_MAX_POINTS - 1);
    gSpecialVar_0x8004 = 5;

    BattleCafe_AwardPoints();

    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_POINTS), BATTLE_CAFE_MAX_POINTS);
    EXPECT_EQ(gSpecialVar_Result, 1);

    gSpecialVar_0x8004 = 2;
    BattleCafe_AwardPoints();

    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_POINTS), BATTLE_CAFE_MAX_POINTS);
    EXPECT_EQ(gSpecialVar_Result, 0);
}

TEST("Battle Cafe point awards repair an out-of-range saved total")
{
    VarSet(VAR_BATTLE_CAFE_POINTS, MAX_u16);
    gSpecialVar_0x8004 = 1;

    BattleCafe_AwardPoints();

    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_POINTS), BATTLE_CAFE_MAX_POINTS);
    EXPECT_EQ(gSpecialVar_Result, 0);
}

TEST("Battle Cafe Miraidon reward requires every future Paradox Pokemon")
{
    CatchBattleCafeTestSpecies(sTestBattleCafeFutureParadoxDexNums, ARRAY_COUNT(sTestBattleCafeFutureParadoxDexNums) - 1);

    BattleCafe_GetParadoxRewardEligibility();
    EXPECT_EQ(gSpecialVar_Result & BATTLE_CAFE_PARADOX_REWARD_MIRAIDON, 0);

    GetSetPokedexFlag(NATIONAL_DEX_IRON_CROWN, FLAG_SET_CAUGHT);
    BattleCafe_GetParadoxRewardEligibility();
    EXPECT_EQ(gSpecialVar_Result, BATTLE_CAFE_PARADOX_REWARD_MIRAIDON);
}

TEST("Battle Cafe Koraidon reward requires every past Paradox Pokemon")
{
    CatchBattleCafeTestSpecies(sTestBattleCafePastParadoxDexNums, ARRAY_COUNT(sTestBattleCafePastParadoxDexNums) - 1);

    BattleCafe_GetParadoxRewardEligibility();
    EXPECT_EQ(gSpecialVar_Result & BATTLE_CAFE_PARADOX_REWARD_KORAIDON, 0);

    GetSetPokedexFlag(NATIONAL_DEX_RAGING_BOLT, FLAG_SET_CAUGHT);
    BattleCafe_GetParadoxRewardEligibility();
    EXPECT_EQ(gSpecialVar_Result, BATTLE_CAFE_PARADOX_REWARD_KORAIDON);
}

TEST("Battle Cafe can unlock both Paradox legendary rewards")
{
    CatchBattleCafeTestSpecies(sTestBattleCafeFutureParadoxDexNums, ARRAY_COUNT(sTestBattleCafeFutureParadoxDexNums));
    CatchBattleCafeTestSpecies(sTestBattleCafePastParadoxDexNums, ARRAY_COUNT(sTestBattleCafePastParadoxDexNums));

    BattleCafe_GetParadoxRewardEligibility();
    EXPECT_EQ(gSpecialVar_Result,
              BATTLE_CAFE_PARADOX_REWARD_MIRAIDON | BATTLE_CAFE_PARADOX_REWARD_KORAIDON);
}

TEST("Battle Cafe Attack vitamin set gives two Protein EX and Calcium EX for four points")
{
    ClearBag();
    VarSet(VAR_BATTLE_CAFE_POINTS, 4);
    gSpecialVar_0x8004 = BATTLE_CAFE_VITAMIN_SET_ATK;

    BattleCafe_TryPurchaseVitaminSet();

    EXPECT_EQ(gSpecialVar_Result, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_POINTS), 0);
    EXPECT(CheckBagHasItem(ITEM_PROTEIN_EX, 2));
    EXPECT(CheckBagHasItem(ITEM_CALCIUM_EX, 2));
}

TEST("Battle Cafe Defense vitamin set gives two Iron EX and Zinc EX for four points")
{
    ClearBag();
    VarSet(VAR_BATTLE_CAFE_POINTS, 4);
    gSpecialVar_0x8004 = BATTLE_CAFE_VITAMIN_SET_DEF;

    BattleCafe_TryPurchaseVitaminSet();

    EXPECT_EQ(gSpecialVar_Result, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_POINTS), 0);
    EXPECT(CheckBagHasItem(ITEM_IRON_EX, 2));
    EXPECT(CheckBagHasItem(ITEM_ZINC_EX, 2));
}

TEST("Battle Cafe Speed vitamin set gives two Carbos EX for two points")
{
    ClearBag();
    VarSet(VAR_BATTLE_CAFE_POINTS, 2);
    gSpecialVar_0x8004 = BATTLE_CAFE_VITAMIN_SET_SPE;

    BattleCafe_TryPurchaseVitaminSet();

    EXPECT_EQ(gSpecialVar_Result, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_POINTS), 0);
    EXPECT(CheckBagHasItem(ITEM_CARBOS_EX, 2));
}

TEST("Battle Cafe vitamin sets do not charge or give items without enough points")
{
    ClearBag();
    VarSet(VAR_BATTLE_CAFE_POINTS, 3);
    gSpecialVar_0x8004 = BATTLE_CAFE_VITAMIN_SET_ATK;

    BattleCafe_TryPurchaseVitaminSet();

    EXPECT_EQ(gSpecialVar_Result, BATTLE_CAFE_VITAMIN_PURCHASE_NOT_ENOUGH_POINTS);
    EXPECT_EQ(VarGet(VAR_BATTLE_CAFE_POINTS), 3);
    EXPECT(!CheckBagHasItem(ITEM_PROTEIN_EX, 1));
    EXPECT(!CheckBagHasItem(ITEM_CALCIUM_EX, 1));
}

TEST("Battle Cafe no-innates preference applies only while a challenge is active")
{
    FlagClear(FLAG_REPLAY_NO_INNATES);
    FlagSet(FLAG_BATTLE_FACILITY_NO_INNATES);

    EXPECT(!AreReplayInnatesDisabled());

    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY);
    BattleCafe_InitChallenge();
    EXPECT(AreReplayInnatesDisabled());
    EXPECT(!IsInnateUnlockedByLevel(1, 100));

    BattleCafe_EndChallenge();
    EXPECT(!AreReplayInnatesDisabled());
}

TEST("Battle Cafe challenges keep innates when the preference is enabled")
{
    FlagClear(FLAG_REPLAY_NO_INNATES);
    FlagClear(FLAG_BATTLE_FACILITY_NO_INNATES);

    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE);
    BattleCafe_InitChallenge();
    EXPECT(!AreReplayInnatesDisabled());
    EXPECT(IsInnateUnlockedByLevel(1, 50));

    BattleCafe_EndChallenge();
}

TEST("Battle Facility innates preference is independent of Classic and Chaos levels")
{
    u32 savedBattleTypeFlags = gBattleTypeFlags;
    enum FrontierLevelMode savedLevelMode = gSaveBlock2Ptr->frontier.lvlMode;

    FlagClear(FLAG_REPLAY_NO_INNATES);
    FlagClear(FLAG_ALL_INNATES_UNLOCKED);
    gSaveBlock2Ptr->frontier.lvlMode = FRONTIER_LVL_50;
    gBattleTypeFlags = BATTLE_TYPE_BATTLE_TOWER;

    FlagClear(FLAG_BATTLE_FACILITY_NO_INNATES);
    EXPECT(IsInnateUnlockedByLevel(1, FRONTIER_MAX_LEVEL_50));

    FlagSet(FLAG_BATTLE_FACILITY_NO_INNATES);
    EXPECT(!IsInnateUnlockedByLevel(1, FRONTIER_MAX_LEVEL_OPEN));

    gSaveBlock2Ptr->frontier.lvlMode = FRONTIER_LVL_TENT;
    FlagClear(FLAG_BATTLE_FACILITY_NO_INNATES);
    EXPECT(!IsInnateUnlockedByLevel(1, FRONTIER_MAX_LEVEL_50));

    gBattleTypeFlags = savedBattleTypeFlags;
    gSaveBlock2Ptr->frontier.lvlMode = savedLevelMode;
}

TEST("Battle Cafe restores held items changed by battle effects after every round")
{
    enum Item item;

    CreateMon(&gPlayerParty[0], SPECIES_UMBREON, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_KROOKODILE, 50, 0, OTID_STRUCT_PLAYER_ID);
    item = ITEM_LEFTOVERS;
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &item);

    VarSet(VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_RUSH);
    BattleCafe_InitChallenge();

    // Simulate Trick replacing Umbreon's item and giving Krookodile an item.
    item = ITEM_FLAME_ORB;
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &item);
    item = ITEM_CHOICE_SCARF;
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &item);

    BattleCafe_RestoreHeldItems();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_NONE);

    BattleCafe_EndChallenge();
}
