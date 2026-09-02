#include "global.h"
#include "difficulty.h"
#include "event_data.h"
#include "new_game.h"
#include "overworld.h"
#include "pokemon.h"
#include "replay_options.h"
#include "test/test.h"
#include "constants/flags.h"
#include "constants/game_stat.h"
#include "constants/party_menu.h"
#include "constants/pokemon.h"
#include "constants/vars.h"

TEST("A fresh new game defaults to 2x battle speed")
{
    Sav2_ClearSetDefault();

    NewGameInitData();

    EXPECT_EQ(VarGet(VAR_BATTLE_SPEED), OPTIONS_BATTLE_SCENE_2X);
    EXPECT_EQ((u8)gSaveBlock2Ptr->optionsBattleSpeed, OPTIONS_BATTLE_SCENE_2X);
    EXPECT(FlagGet(FLAG_PYRAMID_ACHIEVEMENT_MIGRATION_COMPLETE));
    EXPECT_EQ(GetGameStat(GAME_STAT_BATTLE_PYRAMID_FLOORS), 0);
}

TEST("Starting a new game preserves settings selected from the main menu")
{
    SetCurrentDifficultyLevel(DIFFICULTY_HARD);
    VarSet(VAR_OVERWORLD_SPEEDUP, OPTIONS_OVERWORLD_SPEED_4X);
    VarSet(VAR_BATTLE_SPEED, OPTIONS_BATTLE_SCENE_3X);
    gSaveBlock2Ptr->optionsBattleSpeed = OPTIONS_BATTLE_SCENE_3X;
    gSaveBlock1Ptr->optionsPartyMenuStyle = PARTY_MENU_OPTION_HGSS;
    gSaveBlock1Ptr->optionsPartyMenuStyleMagic = PARTY_MENU_OPTION_SAVE_MAGIC;
    SetReplayBattleFormat(REPLAY_BATTLE_FORMAT_DOUBLES);

    NewGameInitData();

    EXPECT_EQ(GetCurrentDifficultyLevel(), DIFFICULTY_HARD);
    EXPECT_EQ(VarGet(VAR_OVERWORLD_SPEEDUP), OPTIONS_OVERWORLD_SPEED_4X);
    EXPECT_EQ(VarGet(VAR_BATTLE_SPEED), OPTIONS_BATTLE_SCENE_3X);
    EXPECT_EQ((u8)gSaveBlock2Ptr->optionsBattleSpeed, OPTIONS_BATTLE_SCENE_3X);
    EXPECT_EQ(gSaveBlock1Ptr->optionsPartyMenuStyle, PARTY_MENU_OPTION_HGSS);
    EXPECT_EQ(gSaveBlock1Ptr->optionsPartyMenuStyleMagic, PARTY_MENU_OPTION_SAVE_MAGIC);
    EXPECT_EQ(GetReplayBattleFormat(), REPLAY_BATTLE_FORMAT_DOUBLES);
}

TEST("Shiny RNG audit: a fresh new game sets exactly 1-in-256 base odds")
{
    NewGameInitData();

    EXPECT(FlagGet(FLAG_RELEASE_SHINY_ODDS));
    EXPECT_EQ(GetCurrentShinyOdds(), RELEASE_SHINY_ODDS);
    EXPECT_EQ(GetCurrentShinyOdds() * 256, MAX_u16 + 1);
}

TEST("Shiny RNG audit: the release predicate accepts exactly 1 in 256 values")
{
    const u32 trainerId = 0x12345678;
    const u32 personalityLo = 0x9ABC;
    u32 personalityHi;
    u32 shinyCount = 0;

    // XOR with personalityHi is a bijection over all 65,536 shiny values.
    // Exhausting that half therefore proves the count for every possible
    // OT ID and low personality half.
    for (personalityHi = 0; personalityHi <= MAX_u16; personalityHi++)
    {
        u32 personality = (personalityHi << 16) | personalityLo;

        if (GET_SHINY_VALUE(trainerId, personality) < RELEASE_SHINY_ODDS)
            shinyCount++;
    }

    EXPECT_EQ(shinyCount, RELEASE_SHINY_ODDS);
    EXPECT_EQ(shinyCount * 256, MAX_u16 + 1);
}
