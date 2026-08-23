#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Fairy Lock's animation does not crash in Double Battles")
{
    FORCE_MOVE_ANIM(TRUE);
    GIVEN {
        PLAYER(SPECIES_KLEFKI);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_FAIRY_LOCK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FAIRY_LOCK, playerLeft);
    } THEN {
        FORCE_MOVE_ANIM(FALSE);
    }
}

TO_DO_BATTLE_TEST("Fairy Lock prevents all Pokémon from switching out on their next turn")
TO_DO_BATTLE_TEST("Fairy Lock does not prevent switch out via Dragon Tail")
TO_DO_BATTLE_TEST("Fairy Lock does not prevent switch out via Whirlwind")
TO_DO_BATTLE_TEST("Fairy Lock does not prevent switch out via Eject Button")
TO_DO_BATTLE_TEST("Fairy Lock does not prevent switch out via Red Card")
TO_DO_BATTLE_TEST("Fairy Lock prevents a Pokémon from switching out on the following turn after replacing a fainted mon")
