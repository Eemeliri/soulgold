#include "global.h"
#include "battle_frontier.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "event_data.h"
#include "frontier_util.h"
#include "item.h"
#include "string_util.h"
#include "test/test.h"
#include "constants/abilities.h"
#include "constants/battle_frontier_mons.h"
#include "constants/battle_frontier_trainers.h"
#include "constants/easy_chat.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"

TEST("This test checks for rain team creation")
{
    static const struct TrainerMon sMons[] =
    {
        {
            .species = SPECIES_PELIPPER,
            .moves = { MOVE_HURRICANE, MOVE_RAIN_DANCE },
            .heldItem = { ITEM_LEFTOVERS },
            .ability = ABILITY_DRIZZLE,
        },
        {
            .species = SPECIES_FLOATZEL,
            .moves = { MOVE_WATERFALL },
            .heldItem = { ITEM_LIFE_ORB },
            .ability = ABILITY_SWIFT_SWIM,
        },
        {
            .species = SPECIES_KINGDRA,
            .moves = { MOVE_HYDRO_PUMP },
            .heldItem = { ITEM_MYSTIC_WATER },
            .ability = ABILITY_SWIFT_SWIM,
        },
        {
            .species = SPECIES_TORKOAL,
            .moves = { MOVE_SOLAR_BEAM },
            .heldItem = { ITEM_CHARCOAL },
            .ability = ABILITY_DROUGHT,
        },
        {
            .species = SPECIES_GYARADOS,
            .moves = { MOVE_WATERFALL },
            .heldItem = { ITEM_GYARADOSITE },
        },
        {
            .species = SPECIES_SWAMPERT,
            .moves = { MOVE_WATERFALL },
            .heldItem = { ITEM_SWAMPERTITE },
        },
        {
            .species = SPECIES_WOBBUFFET,
            .moves = { MOVE_COUNTER },
            .heldItem = { ITEM_LUM_BERRY },
        },
        {
            .species = SPECIES_CLEFAIRY,
            .moves = { MOVE_FOLLOW_ME },
            .heldItem = { ITEM_EVIOLITE },
        },
        {
            .species = SPECIES_LUDICOLO,
            .moves = { MOVE_SURF },
            .heldItem = { ITEM_DAMP_ROCK },
            .ability = ABILITY_RAIN_DISH,
        },
    };
    static const u16 sMonSet[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, FRONTIER_MON_END };
    static const u16 sPartialMonSet[] = { 0, 1, 6, FRONTIER_MON_END };
    static const u16 sSinglesMonSet[] = { 6, 7, FRONTIER_MON_END };
    u16 chosen[4];
    u16 actualFacilityTeam[FRONTIER_DOUBLES_PARTY_SIZE];
    u16 singlesChoice;
    const struct BattleFrontierTrainer *savedFacilityTrainers;
    u32 i;
    u32 megaStoneCount = 0;
    u8 fallbackText[100];
    static const struct BattleFrontierTrainer sFallbackTrainer[] =
    {
        {
            .facilityClass = FACILITY_CLASS_AQUA_LEADER_ARCHIE,
            .speechBefore = {EC_WORD_I_AM, EC_WORD_READY, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        },
    };

    EXPECT(BuildFacilityTrainerMonSelection(sMonSet, sMons, ARRAY_COUNT(sMons), ARRAY_COUNT(chosen),
                                            TRUE, FACILITY_TEAM_RAIN, TRUE,
                                            ARRAY_COUNT(sMons) - 1, chosen));

    // The setter leads, a rain beneficiary follows, and an opposing weather setter is excluded.
    EXPECT_EQ(chosen[0], 0);
    EXPECT(chosen[1] == 1 || chosen[1] == 2 || chosen[1] == 8);
    for (i = 0; i < ARRAY_COUNT(chosen); i++)
    {
        EXPECT_NE(chosen[i], 3);
        if (gItemsInfo[sMons[chosen[i]].heldItem[0]].sortType == ITEM_TYPE_MEGA_STONE)
            megaStoneCount++;
    }
    for (i = 1; i < ARRAY_COUNT(chosen); i++)
        EXPECT(chosen[i] == 1 || chosen[i] == 2 || chosen[i] == 8);
    EXPECT_LE(megaStoneCount, 1);

    // Before 21 wins, only the setter and first beneficiary are required to
    // match. At 21 wins this same undersized core is rejected as incomplete.
    EXPECT(BuildFacilityTrainerMonSelection(sPartialMonSet, sMons, ARRAY_COUNT(sMons), 3,
                                            FALSE, FACILITY_TEAM_RAIN, FALSE,
                                            ARRAY_COUNT(sMons) - 1, chosen));
    EXPECT_EQ(chosen[2], 6);
    EXPECT(!BuildFacilityTrainerMonSelection(sPartialMonSet, sMons, ARRAY_COUNT(sMons), 3,
                                             FALSE, FACILITY_TEAM_RAIN, TRUE,
                                             ARRAY_COUNT(sMons) - 1, chosen));

    // The authored early-streak pool also contains enough compatible spreads to
    // construct a complete rain team under the real facility restrictions.
    EXPECT(BuildFacilityTrainerMonSelection(gBattleFrontierTrainers[0].monSet, gBattleFrontierMons,
                                            NUM_FRONTIER_MONS, ARRAY_COUNT(actualFacilityTeam), TRUE,
                                            FACILITY_TEAM_RAIN, TRUE, FRONTIER_MONS_HIGH_TIER,
                                            actualFacilityTeam));

    // Follow Me is inferred as doubles-only even without an explicit format tag.
    EXPECT(BuildFacilityTrainerMonSelection(sSinglesMonSet, sMons, ARRAY_COUNT(sMons), 1,
                                            FALSE, FACILITY_TEAM_BALANCED,
                                            FALSE,
                                            ARRAY_COUNT(sMons) - 1, &singlesChoice));
    EXPECT_EQ(singlesChoice, 6);

    // Facility dialogue uses a stable class voice across every battle phase.
    savedFacilityTrainers = gFacilityTrainers;
    gFacilityTrainers = gBattleFrontierTrainers;
    CopyFrontierTrainerText(FRONTIER_BEFORE_TEXT, FRONTIER_TRAINER_BRADY);
    EXPECT_EQ(StringCompare(gStringVar4, COMPOUND_STRING("Ma! Pa! Watch me!\nI'll do my best!")), 0);
    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, FRONTIER_TRAINER_BRADY);
    EXPECT_EQ(StringCompare(gStringVar4, COMPOUND_STRING("Ma! Pa! Were you watching?\nI was so strong!")), 0);
    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, FRONTIER_TRAINER_BRADY);
    EXPECT_EQ(StringCompare(gStringVar4, COMPOUND_STRING("Ma, Pa... I lost...\nGet revenge for me...")), 0);

    // Normal and Super Maison quotes share one class pool regardless of IV tier.
    CopyFrontierTrainerText(FRONTIER_BEFORE_TEXT, FRONTIER_TRAINER_LEON);
    EXPECT_EQ(StringCompare(gStringVar4, COMPOUND_STRING("Let me stop your\nwinning streak here.")), 0);

    // An unmapped class retains its authored Easy Chat line.
    gFacilityTrainers = sFallbackTrainer;
    FrontierSpeechToString(sFallbackTrainer[0].speechBefore);
    StringCopy(fallbackText, gStringVar4);
    CopyFrontierTrainerText(FRONTIER_BEFORE_TEXT, 0);
    EXPECT_EQ(StringCompare(gStringVar4, fallbackText), 0);
    gFacilityTrainers = savedFacilityTrainers;
}

TEST("Balanced Frontier teams does not take conflicting speed setters")
{
    static const struct TrainerMon sMons[] =
    {
        {
            .species = SPECIES_PIDGEOT,
            .moves = { MOVE_HURRICANE },
            .heldItem = { ITEM_FLYINGITE },
            .ability = ABILITY_KEEN_EYE,
        },
        {
            .species = SPECIES_REUNICLUS,
            .moves = { MOVE_PSYCHIC },
            .heldItem = { ITEM_LIFE_ORB },
            .ability = ABILITY_MAGIC_GUARD,
        },
    };
    static const u16 sMonSet[] = { 0, 1, FRONTIER_MON_END };
    u16 chosen[2];
    EXPECT(!BuildFacilityTrainerMonSelection(sMonSet, sMons, ARRAY_COUNT(sMons), ARRAY_COUNT(chosen),
                                             FALSE, FACILITY_TEAM_BALANCED, FALSE,
                                             ARRAY_COUNT(sMons) - 1, chosen));
}

TEST("Every Frontier trainer supports a genuine six-Pokemon singles team")
{
    u16 chosen[PARTY_SIZE];
    u16 trainerId;
    u32 i;

    for (trainerId = FRONTIER_TRAINER_BRADY; trainerId <= FRONTIER_TRAINER_GRETEL; trainerId++)
    {
        EXPECT(BuildFacilityTrainerMonSelection(gBattleFrontierTrainers[trainerId].monSet,
                                                gBattleFrontierMons, NUM_FRONTIER_MONS,
                                                ARRAY_COUNT(chosen), FALSE,
                                                FACILITY_TEAM_BALANCED, FALSE,
                                                NUM_FRONTIER_MONS - 1, chosen));

        for (i = 0; i < ARRAY_COUNT(chosen); i++)
        {
            EXPECT_LT(chosen[i], NUM_FRONTIER_MONS);
            EXPECT(IsFrontierMonEnabled(chosen[i]));
        }
    }
}

TEST("Unavailable legendaries are banned from Frontier parties")
{
    EXPECT(!IsFrontierSpeciesAllowed(SPECIES_CALYREX_SHADOW));
    EXPECT(!IsFrontierMonEnabled(FRONTIER_MON_CALYREX_SHADOW_1));
}
