#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(MoveMakesContact(MOVE_SCRATCH));
    ASSUME(MoveMakesContact(MOVE_DRAINING_KISS));
    ASSUME(IsBattleMoveSpecial(MOVE_DRAINING_KISS));
    ASSUME(MoveMakesContact(MOVE_FIRE_PUNCH));
    ASSUME(GetMoveType(MOVE_FIRE_PUNCH) == TYPE_FIRE);
    ASSUME(!MoveMakesContact(MOVE_ROCK_SLIDE));
    ASSUME(IsBattleMovePhysical(MOVE_ROCK_SLIDE));
    ASSUME(MoveMakesContact(MOVE_THUNDER_PUNCH));
    ASSUME(IsPunchingMove(MOVE_THUNDER_PUNCH));
}

SINGLE_BATTLE_TEST("Aura Guard halves damage taken from contact moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Guard halves damage taken from special contact moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAINING_KISS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAINING_KISS, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Guard halves damage taken from Fire-type contact moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_FIRE_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FIRE_PUNCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Guard does not reduce damage from physical non-contact moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_ROCK_SLIDE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_SLIDE, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Guard still reduces contact damage through Protective Pads", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_PROTECTIVE_PADS); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Guard does not reduce damage when Punching Glove prevents contact", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_PUNCHING_GLOVE); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_THUNDER_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDER_PUNCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Guard does not reduce damage when Long Reach prevents contact", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_ROWLET) { Ability(ABILITY_LONG_REACH); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker bypasses Aura Guard", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_MOLD_BREAKER; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_AURA_GUARD); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, UQ_4_12(0.5), results[0].damage);
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Aura Guard halves contact damage when it is an innate trait", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); Innates(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.5), results[1].damage);
    }
}
#endif
