#include "global.h"
#include "battle_main.h"
#include "data.h"
#include "event_data.h"
#include "move.h"
#include "pokemon.h"
#include "trainer_moves.h"
#include "test/test.h"

#include "constants/battle.h"
#include "constants/difficulty.h"

static bool32 IsLevelUpMoveAvailable(u16 species, u8 level, enum Move move)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
    u32 i;

    for (i = 0; i < MAX_LEVEL_UP_MOVES && learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].level > level)
            break;
        if (learnset[i].level != 0 && learnset[i].move == move)
            return TRUE;
    }
    return FALSE;
}

static bool32 IsTeachableMoveAvailable(u16 species, enum Move move)
{
    const u16 *learnset = GetSpeciesTeachableLearnset(species);
    u32 i;

    for (i = 0; learnset[i] != MOVE_UNAVAILABLE; i++)
    {
        if (learnset[i] == move)
            return TRUE;
    }
    return FALSE;
}

static bool32 MoveSetContains(const enum Move moves[MAX_MON_MOVES], enum Move move)
{
    u32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] == move)
            return TRUE;
    }
    return FALSE;
}

TEST("Hard trainer move scoring recognizes unlocked Like a Dragon STAB")
{
    u8 unlockLevel = GetInnateUnlockLevel(3);

    ASSUME(GetMoveType(MOVE_DRAGON_PULSE) == TYPE_DRAGON);
    ASSUME(!IsSpeciesOfType(SPECIES_SERPERIOR, TYPE_DRAGON));
    ASSUME(SpeciesHasInnate(SPECIES_SERPERIOR, ABILITY_LIKE_A_DRAGON) != 0);
    EXPECT(!IsTrainerMoveStab(MOVE_DRAGON_PULSE, SPECIES_SERPERIOR, unlockLevel - 1));
    EXPECT(IsTrainerMoveStab(MOVE_DRAGON_PULSE, SPECIES_SERPERIOR, unlockLevel));
}

TEST("Trainer default moveset preserves a trainerproc-authored all-None set")
{
    const struct TrainerMon *partyEntry = GetTrainerStructFromId(15)->party;
    enum Move moves[MAX_MON_MOVES];
    u32 i;

    EXPECT(TrainerMonHasExplicitMoves(partyEntry));
    BuildTrainerMonMoves(moves, partyEntry, SPECIES_MAGIKARP, 10,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

    for (i = 0; i < MAX_MON_MOVES; i++)
        EXPECT_EQ(moves[i], MOVE_NONE);
}

TEST("Trainer default moveset preserves a partially authored set exactly")
{
    static const struct TrainerMon partyEntry =
    {
        .species = SPECIES_AUDINO,
        .moves = { MOVE_HELPING_HAND, MOVE_NONE, MOVE_TACKLE, MOVE_NONE },
    };
    enum Move normalMoves[MAX_MON_MOVES];
    enum Move hardMoves[MAX_MON_MOVES];
    u32 i;

    EXPECT(TrainerMonHasExplicitMoves(&partyEntry));
    BuildTrainerMonMoves(normalMoves, &partyEntry, SPECIES_AUDINO, 48,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_NORMAL);
    BuildTrainerMonMoves(hardMoves, &partyEntry, SPECIES_AUDINO, 48,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        EXPECT_EQ(normalMoves[i], partyEntry.moves[i]);
        EXPECT_EQ(hardMoves[i], partyEntry.moves[i]);
    }
}

TEST("Trainer default moveset initializes authored PP and clears PP bonuses")
{
    static const struct TrainerMon partyEntry =
    {
        .species = SPECIES_AUDINO,
        .moves = { MOVE_HELPING_HAND, MOVE_NONE, MOVE_TACKLE, MOVE_NONE },
    };
    struct Pokemon mon;
    u32 ppBonuses = 0xFF;

    CreateMon(&mon, SPECIES_AUDINO, 48, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_PP_BONUSES, &ppBonuses);
    AssignTrainerMonMoves(&mon, &partyEntry, TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_PP_BONUSES), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), MOVE_HELPING_HAND);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE2), MOVE_NONE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE3), MOVE_TACKLE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE4), MOVE_NONE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PP1), GetMovePP(MOVE_HELPING_HAND));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PP2), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PP3), GetMovePP(MOVE_TACKLE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PP4), 0);
}

TEST("Trainer default moveset Normal doubles matches GiveMonInitialMoveset")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_PYUKUMUKU };
    struct Pokemon expected;
    struct Pokemon actual;
    u32 i;

    CreateMon(&expected, SPECIES_PYUKUMUKU, 100, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&actual, SPECIES_PYUKUMUKU, 100, 0, OTID_STRUCT_PLAYER_ID);
    GiveMonInitialMoveset(&expected);
    AssignTrainerMonMoves(&actual, &partyEntry,
                          TRAINER_BATTLE_TYPE_DOUBLES, DIFFICULTY_NORMAL);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        EXPECT_EQ(GetMonData(&actual, MON_DATA_MOVE1 + i),
                  GetMonData(&expected, MON_DATA_MOVE1 + i));
        EXPECT_EQ(GetMonData(&actual, MON_DATA_PP1 + i),
                  GetMonData(&expected, MON_DATA_PP1 + i));
    }
}

TEST("Trainer default moveset Normal singles filters and backfills ally moves")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_AUDINO };
    static const enum Move expectedSingles[MAX_MON_MOVES] =
    {
        MOVE_TAKE_DOWN,
        MOVE_SIMPLE_BEAM,
        MOVE_HYPER_VOICE,
        MOVE_DOUBLE_EDGE,
    };
    static const enum Move expectedDoubles[MAX_MON_MOVES] =
    {
        MOVE_SIMPLE_BEAM,
        MOVE_HYPER_VOICE,
        MOVE_HEAL_PULSE,
        MOVE_DOUBLE_EDGE,
    };
    enum Move singlesMoves[MAX_MON_MOVES];
    enum Move doublesMoves[MAX_MON_MOVES];
    u32 i;

    EXPECT(!TrainerMonHasExplicitMoves(&partyEntry));
    BuildTrainerMonMoves(singlesMoves, &partyEntry, SPECIES_AUDINO, 48,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_NORMAL);
    BuildTrainerMonMoves(doublesMoves, &partyEntry, SPECIES_AUDINO, 48,
                         TRAINER_BATTLE_TYPE_DOUBLES, DIFFICULTY_NORMAL);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        EXPECT_EQ(singlesMoves[i], expectedSingles[i]);
        EXPECT_EQ(doublesMoves[i], expectedDoubles[i]);
    }
}

TEST("Trainer default moveset AI-vs-AI player party uses opponent doubles format")
{
    static const enum Move expected[MAX_MON_MOVES] =
    {
        MOVE_SIMPLE_BEAM,
        MOVE_HYPER_VOICE,
        MOVE_HEAL_PULSE,
        MOVE_DOUBLE_EDGE,
    };
    u32 i;

    gSpecialVar_0x8004 = 16;
    gSpecialVar_0x8005 = 17;
    CreateTrainerPartyForPlayer();

    for (i = 0; i < MAX_MON_MOVES; i++)
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1 + i), expected[i]);
}

TEST("Trainer default moveset Normal uses moves learned at the exact current level")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_CHARIZARD };
    static const enum Move expected[MAX_MON_MOVES] =
    {
        MOVE_DRAGON_RAGE,
        MOVE_FIRE_FANG,
        MOVE_SLASH,
        MOVE_FLAMETHROWER
    };
    enum Move moves[MAX_MON_MOVES];
    u32 i;

    BuildTrainerMonMoves(moves, &partyEntry, SPECIES_CHARIZARD, 30,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_NORMAL);
    for (i = 0; i < MAX_MON_MOVES; i++)
        EXPECT_EQ(moves[i], expected[i]);
}

TEST("Trainer default moveset singles classifier follows the documented policy")
{
    static const enum Move rejectedMoves[] =
    {
        MOVE_HELPING_HAND,
        MOVE_FOLLOW_ME,
        MOVE_RAGE_POWDER,
        MOVE_SPOTLIGHT,
        MOVE_ALLY_SWITCH,
        MOVE_HEAL_PULSE,
        MOVE_AFTER_YOU,
        MOVE_QUASH,
        MOVE_INSTRUCT,
        MOVE_AROMATIC_MIST,
        MOVE_COACHING,
        MOVE_DECORATE,
        MOVE_HOLD_HANDS,
        MOVE_WIDE_GUARD,
    };
    static const enum Move retainedMoves[] =
    {
        MOVE_SURF,
        MOVE_EARTHQUAKE,
        MOVE_ACUPRESSURE,
        MOVE_LIFE_DEW,
        MOVE_QUICK_GUARD,
        MOVE_CRAFTY_SHIELD,
        MOVE_RAIN_DANCE,
        MOVE_LIGHT_SCREEN,
        MOVE_RECOVER,
        MOVE_POLLEN_PUFF,
        MOVE_REVIVAL_BLESSING,
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(rejectedMoves); i++)
        EXPECT(!IsAutomaticTrainerMoveSuitableForSingles(rejectedMoves[i]));
    for (i = 0; i < ARRAY_COUNT(retainedMoves); i++)
        EXPECT(IsAutomaticTrainerMoveSuitableForSingles(retainedMoves[i]));
}

TEST("Trainer default moveset rejects every ally-targeting move in singles")
{
    enum Move move;

    for (move = MOVE_NONE + 1; move < MOVES_COUNT; move++)
    {
        if (GetMoveTarget(move) == TARGET_ALLY)
            EXPECT(!IsAutomaticTrainerMoveSuitableForSingles(move));
    }
}

TEST("Trainer default moveset Hard generation is deterministic unique and legal")
{
    static const struct TrainerMon partyEntry =
    {
        .species = SPECIES_CHARIZARD,
        .friendship = MAX_FRIENDSHIP,
    };
    enum Move firstMoves[MAX_MON_MOVES];
    enum Move secondMoves[MAX_MON_MOVES];
    bool32 hasDamagingMove = FALSE;
    bool32 hasTeachableOnlyMove = FALSE;
    u32 i, j;

    BuildTrainerMonMoves(firstMoves, &partyEntry, SPECIES_CHARIZARD, 50,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);
    BuildTrainerMonMoves(secondMoves, &partyEntry, SPECIES_CHARIZARD, 50,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        enum Move move = firstMoves[i];

        EXPECT_EQ(move, secondMoves[i]);
        EXPECT_NE(move, MOVE_NONE);
        EXPECT(move < MOVES_COUNT);
        EXPECT(IsAutomaticTrainerMoveSuitableForSingles(move));
        EXPECT(IsLevelUpMoveAvailable(SPECIES_CHARIZARD, 50, move)
            || IsTeachableMoveAvailable(SPECIES_CHARIZARD, move));
        if (GetMoveCategory(move) != DAMAGE_CATEGORY_STATUS)
            hasDamagingMove = TRUE;
        if (!IsLevelUpMoveAvailable(SPECIES_CHARIZARD, 50, move)
         && IsTeachableMoveAvailable(SPECIES_CHARIZARD, move))
            hasTeachableOnlyMove = TRUE;
        for (j = i + 1; j < MAX_MON_MOVES; j++)
            EXPECT_NE(move, firstMoves[j]);
    }
    EXPECT(hasDamagingMove);
    EXPECT(hasTeachableOnlyMove);
}

TEST("Trainer default moveset Hard levels below 33 use only level-up moves")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_BUTTERFREE };
    enum Move moves[MAX_MON_MOVES];
    u32 i;

    BuildTrainerMonMoves(moves, &partyEntry, SPECIES_BUTTERFREE, 32,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        EXPECT_NE(moves[i], MOVE_NONE);
        EXPECT(IsLevelUpMoveAvailable(SPECIES_BUTTERFREE, 32, moves[i]));
    }
    EXPECT(!MoveSetContains(moves, MOVE_HYPER_BEAM));
    EXPECT(!MoveSetContains(moves, MOVE_SOLAR_BEAM));
}

TEST("Trainer default moveset Hard falls back when policy rejects every move")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_MAGIKARP };
    enum Move moves[MAX_MON_MOVES];

    BuildTrainerMonMoves(moves, &partyEntry, SPECIES_MAGIKARP, 10,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

    EXPECT_EQ(moves[0], MOVE_SPLASH);
    EXPECT_EQ(moves[1], MOVE_NONE);
    EXPECT_EQ(moves[2], MOVE_NONE);
    EXPECT_EQ(moves[3], MOVE_NONE);
}

TEST("Trainer default moveset Hard levels 33 through 42 use only basic teachables")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_BUTTERFREE };
    static const u8 levels[] = {33, 42};
    u32 levelIndex;

    for (levelIndex = 0; levelIndex < ARRAY_COUNT(levels); levelIndex++)
    {
        enum Move moves[MAX_MON_MOVES];
        bool32 hasTeachableOnlyMove = FALSE;
        u32 i;

        BuildTrainerMonMoves(moves, &partyEntry, SPECIES_BUTTERFREE, levels[levelIndex],
                             TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            enum Move move = moves[i];

            EXPECT_NE(move, MOVE_NONE);
            EXPECT(IsLevelUpMoveAvailable(SPECIES_BUTTERFREE, levels[levelIndex], move)
                || IsTeachableMoveAvailable(SPECIES_BUTTERFREE, move));
            if (!IsLevelUpMoveAvailable(SPECIES_BUTTERFREE, levels[levelIndex], move))
            {
                hasTeachableOnlyMove = TRUE;
                if (GetMoveCategory(move) != DAMAGE_CATEGORY_STATUS)
                    EXPECT_LE(GetMovePower(move), 80);
            }
        }
        EXPECT(hasTeachableOnlyMove);
        EXPECT(!MoveSetContains(moves, MOVE_ROOST));
        EXPECT(!MoveSetContains(moves, MOVE_HYPER_BEAM));
        EXPECT(!MoveSetContains(moves, MOVE_SOLAR_BEAM));
    }
}

TEST("Trainer default moveset Hard levels 43 through 49 lock high-power teachables")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_BUTTERFREE };
    static const u8 levels[] = {43, 49};
    u32 levelIndex;

    for (levelIndex = 0; levelIndex < ARRAY_COUNT(levels); levelIndex++)
    {
        enum Move moves[MAX_MON_MOVES];
        u32 i;

        BuildTrainerMonMoves(moves, &partyEntry, SPECIES_BUTTERFREE, levels[levelIndex],
                             TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            enum Move move = moves[i];

            if (!IsLevelUpMoveAvailable(SPECIES_BUTTERFREE, levels[levelIndex], move)
             && IsTeachableMoveAvailable(SPECIES_BUTTERFREE, move)
             && GetMoveCategory(move) != DAMAGE_CATEGORY_STATUS)
            {
                EXPECT_LT(GetMovePower(move), 100);
            }
        }
        EXPECT(!MoveSetContains(moves, MOVE_HYPER_BEAM));
        EXPECT(!MoveSetContains(moves, MOVE_SOLAR_BEAM));
    }
}

TEST("Trainer default moveset Hard level 50 unlocks high-power teachables")
{
    static const struct TrainerMon partyEntry = { .species = SPECIES_BUTTERFREE };
    enum Move moves[MAX_MON_MOVES];
    bool32 hasHighPowerTeachableMove = FALSE;
    u32 i;

    BuildTrainerMonMoves(moves, &partyEntry, SPECIES_BUTTERFREE, 50,
                         TRAINER_BATTLE_TYPE_SINGLES, DIFFICULTY_HARD);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        enum Move move = moves[i];

        if (!IsLevelUpMoveAvailable(SPECIES_BUTTERFREE, 50, move)
         && IsTeachableMoveAvailable(SPECIES_BUTTERFREE, move)
         && GetMoveCategory(move) != DAMAGE_CATEGORY_STATUS
         && GetMovePower(move) >= 100)
            hasHighPowerTeachableMove = TRUE;
    }
    EXPECT(hasHighPowerTeachableMove);
}
