#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "test/test.h"
#include "tv.h"
#include "vs_seeker.h"
#include "constants/battle_setup.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_types.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/script_commands.h"
#include "constants/species.h"
#include "constants/trainer_types.h"
#include "constants/tv.h"

#define TRAINER_SCRIPT(name, mode, trainerId) \
    static const u8 name[] = \
    { \
        SCR_OP_TRAINERBATTLE, \
        (mode) << 4, \
        0, \
        (trainerId) & 0xFF, \
        (trainerId) >> 8, \
    }

TRAINER_SCRIPT(sWadeScript, TRAINER_BATTLE_SINGLE, TRAINER_WADE);
TRAINER_SCRIPT(sJoeyScript, TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JOEY);
TRAINER_SCRIPT(sMikeyScript, TRAINER_BATTLE_DOUBLE, TRAINER_MIKEY);
TRAINER_SCRIPT(sDonScript, TRAINER_BATTLE_SINGLE, TRAINER_DON);
TRAINER_SCRIPT(sShelbyScript, TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_SHELBY_1);
TRAINER_SCRIPT(sExpertScript, TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT, TRAINER_ROUTE_31_EXPERT);
TRAINER_SCRIPT(sTabithaScript, TRAINER_BATTLE_SINGLE, TRAINER_TABITHA_MT_CHIMNEY);
TRAINER_SCRIPT(sNoTrainerIdScript, TRAINER_BATTLE_SINGLE, TRAINER_NONE);

static const u8 sTrainerBattleAfterAnotherCommand[] =
{
    SCR_OP_LOCK,
    SCR_OP_TRAINERBATTLE,
    TRAINER_BATTLE_SINGLE << 4,
    0,
    TRAINER_DON & 0xFF,
    TRAINER_DON >> 8,
};

static const u16 sRoute31Prerequisites[] =
{
    TRAINER_WADE,
    TRAINER_JOEY,
    TRAINER_MIKEY,
    TRAINER_DON,
};

static const u16 sGoldenrodShorePrerequisites[] =
{
    TRAINER_SAMUEL,
    TRAINER_BRANDON,
    TRAINER_TODD,
    TRAINER_IAN,
    TRAINER_GINA,
    TRAINER_KIM,
    TRAINER_ELLIOT,
    TRAINER_BROOKE,
    TRAINER_IVAN,
    TRAINER_IRWIN,
    TRAINER_WALT,
    TRAINER_ARNIE,
    TRAINER_BRYAN,
    TRAINER_MARK,
    TRAINER_ALAN,
};

static const u16 sRoute43Prerequisites[] =
{
    TRAINER_BRENT,
    TRAINER_RON,
    TRAINER_MARVIN,
    TRAINER_SPENCER,
    TRAINER_TIFFANY,
    TRAINER_ANDRE,
    TRAINER_RAYMOND,
    TRAINER_AARON,
    TRAINER_LOIS,
};

static const u16 sRoute47Prerequisites[] =
{
    TRAINER_DEVIN,
    TRAINER_GRANT,
    TRAINER_THOM_AND_KAE,
    TRAINER_DUFF_AND_EDA,
};

static const u16 sRoute27Prerequisites[] =
{
    TRAINER_BLAKE,
    TRAINER_BRIAN,
    TRAINER_REENA,
    TRAINER_MEGAN,
    TRAINER_GILBERT,
    TRAINER_JOSE,
    TRAINER_SCOTT,
    TRAINER_JAKE,
    TRAINER_GAVEN,
    TRAINER_JOYCE,
    TRAINER_BETH,
    TRAINER_RICHARD,
};

struct ExpertTestData
{
    u16 qualificationFlag;
    u16 expertDefeatedFlag;
    const u16 *prerequisites;
    u32 prerequisiteCount;
};

static const struct ExpertTestData sExpertTestData[] =
{
    { FLAG_ROUTE31_EXPERT_QUALIFIED, FLAG_ROUTE31_EXPERT, sRoute31Prerequisites, ARRAY_COUNT(sRoute31Prerequisites) },
    { FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED, FLAG_GOLDENRODSHORE_EXPERT, sGoldenrodShorePrerequisites, ARRAY_COUNT(sGoldenrodShorePrerequisites) },
    { FLAG_ROUTE43_EXPERT_QUALIFIED, FLAG_ROUTE43_EXPERT, sRoute43Prerequisites, ARRAY_COUNT(sRoute43Prerequisites) },
    { FLAG_ROUTE47_EXPERT_QUALIFIED, FLAG_ROUTE47_EXPERT, sRoute47Prerequisites, ARRAY_COUNT(sRoute47Prerequisites) },
    { FLAG_ROUTE27_EXPERT_QUALIFIED, FLAG_ROUTE27_EXPERT, sRoute27Prerequisites, ARRAY_COUNT(sRoute27Prerequisites) },
};

static void ResetExpertTestFlags(void)
{
    u32 i;
    u32 j;

    for (i = 0; i < ARRAY_COUNT(sExpertTestData); i++)
    {
        FlagClear(sExpertTestData[i].qualificationFlag);
        FlagClear(sExpertTestData[i].expertDefeatedFlag);
        for (j = 0; j < sExpertTestData[i].prerequisiteCount; j++)
            ClearTrainerFlag(sExpertTestData[i].prerequisites[j]);
    }
}

static void SetPrerequisiteFlags(const struct ExpertTestData *expert, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++)
        SetTrainerFlag(expert->prerequisites[i]);
}

TEST("Vs Seeker old save state migrates to a full charge")
{
    memset(&gSaveBlock1Ptr->vsSeekerSaveMagic, 0, sizeof(gSaveBlock1Ptr->vsSeekerSaveMagic));
    gSaveBlock1Ptr->vsSeekerChargeSteps = 0;
    gSaveBlock1Ptr->vsSeekerSaveMagicInv = 0;

    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);
    EXPECT_EQ(gSaveBlock1Ptr->vsSeekerSaveMagic, VSSEEKER_SAVE_MAGIC);
    EXPECT_EQ(gSaveBlock1Ptr->vsSeekerSaveMagicInv, (u8)~VSSEEKER_SAVE_MAGIC);

    gSaveBlock1Ptr->vsSeekerSaveMagic = 0x31;
    gSaveBlock1Ptr->vsSeekerChargeSteps = 47;
    gSaveBlock1Ptr->vsSeekerSaveMagicInv = 0xE4;
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);
}

TEST("Vs Seeker rejects an out of range charge with valid magic")
{
    gSaveBlock1Ptr->vsSeekerSaveMagic = VSSEEKER_SAVE_MAGIC;
    gSaveBlock1Ptr->vsSeekerChargeSteps = VSSEEKER_RECHARGE_STEPS + 1;
    gSaveBlock1Ptr->vsSeekerSaveMagicInv = (u8)~VSSEEKER_SAVE_MAGIC;

    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);
}

TEST("Vs Seeker valid full and empty charges persist")
{
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);

    SetVsSeekerChargeSteps(0);
    EXPECT_EQ(GetVsSeekerChargeSteps(), 0);
    EXPECT_EQ(gSaveBlock1Ptr->vsSeekerSaveMagic, VSSEEKER_SAVE_MAGIC);
    EXPECT_EQ(gSaveBlock1Ptr->vsSeekerSaveMagicInv, (u8)~VSSEEKER_SAVE_MAGIC);
}

TEST("Vs Seeker charging requires the item and caps with one transition")
{
    u32 i;

    ClearBag();
    SetVsSeekerChargeSteps(0);
    EXPECT(!UpdateVsSeekerStepCounter());
    EXPECT_EQ(GetVsSeekerChargeSteps(), 0);

    EXPECT(AddBagItem(ITEM_VS_SEEKER, 1));
    for (i = 0; i < VSSEEKER_RECHARGE_STEPS - 1; i++)
        EXPECT(!UpdateVsSeekerStepCounter());
    EXPECT_EQ(GetVsSeekerRemainingSteps(), 1);

    EXPECT(UpdateVsSeekerStepCounter());
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);
    EXPECT_EQ(GetVsSeekerRemainingSteps(), 0);
    EXPECT(!UpdateVsSeekerStepCounter());
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);
}

TEST("Vs Seeker resets all and only defeated eligible Trainers on a route")
{
    const struct ObjectEventTemplate objects[] =
    {
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sWadeScript },
        { .trainerType = TRAINER_TYPE_BURIED, .script = sJoeyScript },
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sMikeyScript },
    };

    SetTrainerFlag(TRAINER_WADE);
    SetTrainerFlag(TRAINER_JOEY);
    ClearTrainerFlag(TRAINER_MIKEY);
    SetTrainerFlag(TRAINER_DON);
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);

    EXPECT_EQ(VsSeekerCountDefeatedTrainers(objects, ARRAY_COUNT(objects), MAP_TYPE_ROUTE), 2);
    EXPECT_EQ(VsSeekerTryActivate(objects, ARRAY_COUNT(objects), MAP_TYPE_ROUTE), 2);
    EXPECT(!HasTrainerBeenFought(TRAINER_WADE));
    EXPECT(!HasTrainerBeenFought(TRAINER_JOEY));
    EXPECT(!HasTrainerBeenFought(TRAINER_MIKEY));
    EXPECT(HasTrainerBeenFought(TRAINER_DON));
    EXPECT_EQ(GetVsSeekerChargeSteps(), 0);
}

TEST("Vs Seeker failed uses preserve charge and Trainer flags")
{
    const struct ObjectEventTemplate object =
    {
        .trainerType = TRAINER_TYPE_NORMAL,
        .script = sWadeScript,
    };

    SetTrainerFlag(TRAINER_WADE);
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);
    EXPECT_EQ(VsSeekerTryActivate(&object, 1, MAP_TYPE_CITY), 0);
    EXPECT(HasTrainerBeenFought(TRAINER_WADE));
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);

    ClearTrainerFlag(TRAINER_WADE);
    EXPECT_EQ(VsSeekerTryActivate(&object, 1, MAP_TYPE_ROUTE), 0);
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);

    SetTrainerFlag(TRAINER_WADE);
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS - 1);
    EXPECT_EQ(VsSeekerTryActivate(&object, 1, MAP_TYPE_ROUTE), 0);
    EXPECT(HasTrainerBeenFought(TRAINER_WADE));
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS - 1);
}

TEST("Vs Seeker eligibility excludes special and unsafe script shapes")
{
    const struct ObjectEventTemplate objects[] =
    {
        { .trainerType = TRAINER_TYPE_NONE, .script = sWadeScript },
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sNoTrainerIdScript },
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sExpertScript },
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sTabithaScript },
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sTrainerBattleAfterAnotherCommand },
    };

    SetTrainerFlag(TRAINER_WADE);
    SetTrainerFlag(TRAINER_ROUTE_31_EXPERT);
    SetTrainerFlag(TRAINER_TABITHA_MT_CHIMNEY);
    SetTrainerFlag(TRAINER_DON);
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);

    EXPECT_EQ(VsSeekerTryActivate(objects, ARRAY_COUNT(objects), MAP_TYPE_ROUTE), 0);
    EXPECT(HasTrainerBeenFought(TRAINER_WADE));
    EXPECT(HasTrainerBeenFought(TRAINER_ROUTE_31_EXPERT));
    EXPECT(HasTrainerBeenFought(TRAINER_TABITHA_MT_CHIMNEY));
    EXPECT(HasTrainerBeenFought(TRAINER_DON));
    EXPECT_EQ(GetVsSeekerChargeSteps(), VSSEEKER_RECHARGE_STEPS);
}

TEST("Vs Seeker deduplicates shared double Trainer IDs")
{
    const struct ObjectEventTemplate objects[] =
    {
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sMikeyScript },
        { .trainerType = TRAINER_TYPE_NORMAL, .script = sMikeyScript },
    };

    SetTrainerFlag(TRAINER_MIKEY);
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);

    EXPECT_EQ(VsSeekerCountDefeatedTrainers(objects, ARRAY_COUNT(objects), MAP_TYPE_ROUTE), 1);
    EXPECT_EQ(VsSeekerTryActivate(objects, ARRAY_COUNT(objects), MAP_TYPE_ROUTE), 1);
    EXPECT(!HasTrainerBeenFought(TRAINER_MIKEY));
}

TEST("Vs Seeker clears only the original Trainer ID")
{
    const struct ObjectEventTemplate object =
    {
        .trainerType = TRAINER_TYPE_NORMAL,
        .script = sShelbyScript,
    };

    SetTrainerFlag(TRAINER_SHELBY_1);
    SetTrainerFlag(TRAINER_SHELBY_2);
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);

    EXPECT_EQ(VsSeekerTryActivate(&object, 1, MAP_TYPE_ROUTE), 1);
    EXPECT(!HasTrainerBeenFought(TRAINER_SHELBY_1));
    EXPECT(HasTrainerBeenFought(TRAINER_SHELBY_2));
}

TEST("Vs Seeker establishes all five expert qualifications")
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sExpertTestData); i++)
    {
        ResetExpertTestFlags();
        SetPrerequisiteFlags(&sExpertTestData[i], sExpertTestData[i].prerequisiteCount);
        VsSeekerUpdateExpertQualifications();
        EXPECT(FlagGet(sExpertTestData[i].qualificationFlag));
    }
}

TEST("Vs Seeker does not qualify a partial expert requirement")
{
    ResetExpertTestFlags();
    SetPrerequisiteFlags(&sExpertTestData[0], sExpertTestData[0].prerequisiteCount - 1);

    VsSeekerUpdateExpertQualifications();
    EXPECT(!FlagGet(FLAG_ROUTE31_EXPERT_QUALIFIED));
}

TEST("Vs Seeker migrates completed experts and never revokes qualification")
{
    u32 i;

    ResetExpertTestFlags();
    FlagSet(FLAG_ROUTE43_EXPERT);
    VsSeekerUpdateExpertQualifications();
    EXPECT(FlagGet(FLAG_ROUTE43_EXPERT_QUALIFIED));

    ResetExpertTestFlags();
    SetPrerequisiteFlags(&sExpertTestData[0], sExpertTestData[0].prerequisiteCount);
    VsSeekerUpdateExpertQualifications();
    for (i = 0; i < sExpertTestData[0].prerequisiteCount; i++)
        ClearTrainerFlag(sExpertTestData[0].prerequisites[i]);
    VsSeekerUpdateExpertQualifications();
    EXPECT(FlagGet(FLAG_ROUTE31_EXPERT_QUALIFIED));
}

TEST("Vs Seeker captures expert qualification before resetting Trainers")
{
    const struct ObjectEventTemplate object =
    {
        .trainerType = TRAINER_TYPE_NORMAL,
        .script = sWadeScript,
    };

    ResetExpertTestFlags();
    SetPrerequisiteFlags(&sExpertTestData[0], sExpertTestData[0].prerequisiteCount);
    SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);

    EXPECT_EQ(VsSeekerTryActivate(&object, 1, MAP_TYPE_ROUTE), 1);
    EXPECT(FlagGet(FLAG_ROUTE31_EXPERT_QUALIFIED));
    EXPECT(!HasTrainerBeenFought(TRAINER_WADE));
}

TEST("Mass outbreak start and end preserve Vs Seeker state")
{
    TVShow *show = &gSaveBlock1Ptr->tvShows[0];

    memset(show, 0, sizeof(*show));
    show->massOutbreak.species = SPECIES_ZIGZAGOON;
    show->massOutbreak.locationMapNum = 7;
    show->massOutbreak.locationMapGroup = 2;
    show->massOutbreak.level = 14;
    show->massOutbreak.moves[0] = MOVE_TACKLE;
    show->massOutbreak.moves[1] = MOVE_GROWL;
    show->massOutbreak.probability = 50;
    gSpecialVar_0x8004 = 0;
    SetVsSeekerChargeSteps(37);

    StartMassOutbreak();
    EXPECT_EQ(GetVsSeekerChargeSteps(), 37);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonSpecies, SPECIES_ZIGZAGOON);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakLocationMapNum, 7);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakLocationMapGroup, 2);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonLevel, 14);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonMoves[0], MOVE_TACKLE);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonMoves[1], MOVE_GROWL);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonProbability, 50);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakDaysLeft, 2);

    EndMassOutbreak();
    EXPECT_EQ(GetVsSeekerChargeSteps(), 37);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonSpecies, SPECIES_NONE);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonMoves[0], MOVE_NONE);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonProbability, 0);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakDaysLeft, 0);
}

TEST("Daily outbreak expiration preserves Vs Seeker state")
{
    SetVsSeekerChargeSteps(12);
    gSaveBlock1Ptr->outbreakPokemonSpecies = SPECIES_ZIGZAGOON;
    gSaveBlock1Ptr->outbreakDaysLeft = 1;

    UpdateTVShowsPerDay(1);
    EXPECT_EQ(GetVsSeekerChargeSteps(), 12);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonSpecies, SPECIES_NONE);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakDaysLeft, 0);
}

#undef TRAINER_SCRIPT
