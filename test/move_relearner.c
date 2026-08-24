#include "global.h"
#include "event_data.h"
#include "move_relearner.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/flags.h"
#include "constants/moves.h"

static u32 CountMove(const u16 *moves, u32 numMoves, u16 move)
{
    u32 count = 0;

    for (u32 i = 0; i < numMoves; i++)
    {
        if (moves[i] == move)
            count++;
    }

    return count;
}

TEST("Azumarill egg move relearner combines Marill and Azurill egg moves")
{
    struct Pokemon mon;
    u16 moves[MAX_RELEARNER_MOVES];
    u32 numMoves;

    FlagSet(FLAG_EGG_MOVES_UNLOCKED);
    CreateMon(&mon, SPECIES_AZUMARILL, 50, 0, OTID_STRUCT_PLAYER_ID);

    EXPECT(CanBoxMonRelearnMoves(&mon.box, MOVE_RELEARNER_EGG_MOVES));
    numMoves = GetBoxMonRelearnableEggMoves(&mon.box, moves);
    EXPECT_EQ(CountMove(moves, numMoves, MOVE_AQUA_JET), 1);
    EXPECT_EQ(CountMove(moves, numMoves, MOVE_BELLY_DRUM), 1);
    EXPECT_EQ(CountMove(moves, numMoves, MOVE_ENCORE), 1);
    EXPECT_EQ(CountMove(moves, numMoves, MOVE_REFRESH), 1);

    FlagClear(FLAG_EGG_MOVES_UNLOCKED);
}
