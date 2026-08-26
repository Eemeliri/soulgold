#include "global.h"
#include "dexnav.h"
#include "test/test.h"
#include "constants/moves.h"

static u32 CountMove(const u16 *moves, u16 move)
{
    u32 count = 0;

    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] == move)
            count++;
    }

    return count;
}

TEST("DexNav special moves do not duplicate a move in the normal moveset")
{
    u16 moves[MAX_MON_MOVES] = {MOVE_ROLLOUT, MOVE_GLARE, MOVE_SCREECH, MOVE_ANCIENT_POWER};

    DexNav_TestSetSpecialMove(moves, MOVE_ANCIENT_POWER);

    EXPECT_EQ(moves[0], MOVE_ANCIENT_POWER);
    EXPECT_EQ(moves[1], MOVE_GLARE);
    EXPECT_EQ(moves[2], MOVE_SCREECH);
    EXPECT_EQ(moves[3], MOVE_ROLLOUT);
    EXPECT_EQ(CountMove(moves, MOVE_ANCIENT_POWER), 1);
}

TEST("DexNav special moves still replace the first move when newly learned")
{
    u16 moves[MAX_MON_MOVES] = {MOVE_ROLLOUT, MOVE_GLARE, MOVE_SCREECH, MOVE_ANCIENT_POWER};

    DexNav_TestSetSpecialMove(moves, MOVE_HEADBUTT);

    EXPECT_EQ(moves[0], MOVE_HEADBUTT);
    EXPECT_EQ(moves[1], MOVE_GLARE);
    EXPECT_EQ(moves[2], MOVE_SCREECH);
    EXPECT_EQ(moves[3], MOVE_ANCIENT_POWER);
    EXPECT_EQ(CountMove(moves, MOVE_HEADBUTT), 1);
}
