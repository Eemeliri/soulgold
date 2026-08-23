#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Particle-heavy move animations complete in Double Battles")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_AIR_CUTTER; }
    PARAMETRIZE { move = MOVE_BARRAGE; }
    PARAMETRIZE { move = MOVE_DARK_VOID; }
    PARAMETRIZE { move = MOVE_ERUPTION; }
    PARAMETRIZE { move = MOVE_FACADE; }
    PARAMETRIZE { move = MOVE_GLARE; }
    PARAMETRIZE { move = MOVE_GRUDGE; }
    PARAMETRIZE { move = MOVE_HAIL; }
    PARAMETRIZE { move = MOVE_HEART_SWAP; }
    PARAMETRIZE { move = MOVE_IMPRISON; }
    PARAMETRIZE { move = MOVE_ION_DELUGE; }
    PARAMETRIZE { move = MOVE_LEAF_BLADE; }
    PARAMETRIZE { move = MOVE_METEOR_MASH; }
    PARAMETRIZE { move = MOVE_PARABOLIC_CHARGE; }
    PARAMETRIZE { move = MOVE_RAIN_DANCE; }
    PARAMETRIZE { move = MOVE_ROLLOUT; }
    PARAMETRIZE { move = MOVE_SHOCK_WAVE; }
    PARAMETRIZE { move = MOVE_SKILL_SWAP; }
    PARAMETRIZE { move = MOVE_SMOKESCREEN; }
    PARAMETRIZE { move = MOVE_SNOWSCAPE; }
    PARAMETRIZE { move = MOVE_TORMENT; }
    PARAMETRIZE { move = MOVE_WATER_PULSE; }
    PARAMETRIZE { move = MOVE_WATER_SPOUT; }

    FORCE_MOVE_ANIM(TRUE);
    GIVEN {
        PLAYER(SPECIES_DARKRAI) { HP(9999); MaxHP(9999); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(9999); MaxHP(9999); Defense(9999); SpDefense(9999); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(9999); MaxHP(9999); Defense(9999); SpDefense(9999); }
    } WHEN {
        TURN { MOVE(playerLeft, move, target: opponentLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, playerLeft);
    } THEN {
        FORCE_MOVE_ANIM(FALSE);
    }
}
