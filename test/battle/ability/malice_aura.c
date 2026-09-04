#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Malice Aura boosts Ghost moves used by either side")
{
    s16 damage[4];

    GIVEN {
        ASSUME(GetMoveType(MOVE_SHADOW_BALL) == TYPE_GHOST);
        PLAYER(SPECIES_WOBBUFFET) { Speed(2); }
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MALICE_AURA); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_SHADOW_BALL, secondaryEffect: FALSE);
            MOVE(opponent, MOVE_SHADOW_BALL, secondaryEffect: FALSE);
        }
        TURN { SWITCH(player, 1); }
        TURN {
            MOVE(player, MOVE_SHADOW_BALL, secondaryEffect: FALSE);
            MOVE(opponent, MOVE_SHADOW_BALL, secondaryEffect: FALSE);
        }
    } SCENE {
        HP_BAR(opponent, captureDamage: &damage[0]);
        HP_BAR(player, captureDamage: &damage[1]);

        ABILITY_POPUP(player, ABILITY_MALICE_AURA);
        MESSAGE("Wobbuffet is radiating a malicious aura!");

        HP_BAR(opponent, captureDamage: &damage[2]);
        HP_BAR(player, captureDamage: &damage[3]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], UQ_4_12(1.33), damage[2]);
        EXPECT_MUL_EQ(damage[1], UQ_4_12(1.33), damage[3]);
    }
}

DOUBLE_BATTLE_TEST("Aura Break inverts Malice Aura's effect")
{
    s16 damage[3];

    GIVEN {
        ASSUME(GetMoveType(MOVE_SHADOW_BALL) == TYPE_GHOST);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_GIRATINA) { Ability(ABILITY_MALICE_AURA); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ZYGARDE_50) { Ability(ABILITY_AURA_BREAK); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SHADOW_BALL, target: opponentLeft, secondaryEffect: FALSE); }
        TURN { MOVE(playerLeft, MOVE_SHADOW_BALL, target: opponentLeft, secondaryEffect: FALSE); SWITCH(playerRight, 2); }
        TURN { MOVE(playerLeft, MOVE_SHADOW_BALL, target: opponentLeft, secondaryEffect: FALSE); SWITCH(opponentRight, 2); }
    } SCENE {
        HP_BAR(opponentLeft, captureDamage: &damage[0]);

        ABILITY_POPUP(playerRight, ABILITY_MALICE_AURA);
        HP_BAR(opponentLeft, captureDamage: &damage[1]);

        ABILITY_POPUP(opponentRight, ABILITY_AURA_BREAK);
        HP_BAR(opponentLeft, captureDamage: &damage[2]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], UQ_4_12(1.33), damage[1]);
        EXPECT_MUL_EQ(damage[0], UQ_4_12(0.75), damage[2]);
    }
}
