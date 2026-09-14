#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Corviknight's Iron Barbs punishes contact without blocking Mirror Armor")
{
    GIVEN {
        PLAYER(SPECIES_CORVIKNIGHT) { Level(100); Ability(ABILITY_MIRROR_ARMOR); USE_DEFAULT_INNATES; }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCREECH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_IRON_BARBS);
        HP_BAR(opponent);
        MESSAGE("The opposing Wobbuffet used Screech!");
        ABILITY_POPUP(player, ABILITY_MIRROR_ARMOR);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 2);
    }
}
