#include "global.h"
#include "constants/party_menu.h"
#include "party_menu.h"
#include "pokemon.h"
#include "test/test.h"

TEST("A stale EXP Candy level is not restored after unrelated move learning")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_WOBBUFFET, 42, 0, OTID_STRUCT_PLAYER_ID);
#if PARTY_MENU_STYLE_OPTION
    EXPECT_EQ(BwPartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 33, FALSE), 42);

    CreateMon(&mon, SPECIES_WOBBUFFET, 42, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(HgssPartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 33, FALSE), 42);
#elif !SWSH_PARTY_MENU
    EXPECT_EQ(PartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 33, FALSE), 42);
#endif

#if SWSH_PARTY_MENU || PARTY_MENU_STYLE_OPTION
    CreateMon(&mon, SPECIES_WOBBUFFET, 42, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(SwShPartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 33, FALSE), 42);
#endif
}

TEST("An active EXP Candy level-up restores the final level after move learning")
{
    struct Pokemon mon;
    u8 temporaryLevel = 34;

    CreateMon(&mon, SPECIES_WOBBUFFET, 42, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_LEVEL, &temporaryLevel);
#if PARTY_MENU_STYLE_OPTION
    EXPECT_EQ(BwPartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 42, TRUE), 42);

    SetMonData(&mon, MON_DATA_LEVEL, &temporaryLevel);
    EXPECT_EQ(HgssPartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 42, TRUE), 42);
#elif !SWSH_PARTY_MENU
    EXPECT_EQ(PartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 42, TRUE), 42);
#endif

#if SWSH_PARTY_MENU || PARTY_MENU_STYLE_OPTION
    SetMonData(&mon, MON_DATA_LEVEL, &temporaryLevel);
    EXPECT_EQ(SwShPartyMenu_TestRestoreLevelAfterMoveSummary(&mon, 42, TRUE), 42);
#endif
}
