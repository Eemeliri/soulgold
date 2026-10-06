#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Simple doubles stat increases and decreases")
{
    bool32 innate;
    PARAMETRIZE { innate = FALSE; }
#if MAX_MON_TRAITS > 1
    PARAMETRIZE { innate = TRUE; }
#endif
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_SWORDS_DANCE) == EFFECT_ATTACK_UP_2);
        ASSUME(GetMoveEffect(MOVE_SCREECH) == EFFECT_DEFENSE_DOWN_2);
        PLAYER(SPECIES_WOBBUFFET) {
            Ability(innate ? ABILITY_LIGHT_METAL : ABILITY_SIMPLE);
            Innates(innate ? ABILITY_SIMPLE : ABILITY_NONE);
        }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SWORDS_DANCE); MOVE(opponent, MOVE_SCREECH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 4);
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 4);
    }
}
