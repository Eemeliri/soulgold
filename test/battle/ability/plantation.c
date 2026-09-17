#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Plantation does not seed targets hit by False Swipe or Hold Back")
{
    u32 move = MOVE_FALSE_SWIPE;
    u32 hp = 1;
    u32 initialHp;
    bool32 innate = FALSE;
    s16 damage;

    for (initialHp = 1; initialHp <= 100; initialHp *= 10)
    {
        PARAMETRIZE { move = MOVE_FALSE_SWIPE; innate = FALSE; hp = initialHp; }
        PARAMETRIZE { move = MOVE_HOLD_BACK; innate = FALSE; hp = initialHp; }
    #if MAX_MON_TRAITS > 1
        PARAMETRIZE { move = MOVE_FALSE_SWIPE; innate = TRUE; hp = initialHp; }
        PARAMETRIZE { move = MOVE_HOLD_BACK; innate = TRUE; hp = initialHp; }
    #endif
    }

    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_FALSE_SWIPE);
        PLAYER(SPECIES_BRELOOM) {
            Ability(innate ? ABILITY_TECHNICIAN : ABILITY_PLANTATION);
            Innates(innate ? ABILITY_PLANTATION : ABILITY_NONE);
            Attack(100);
        }
        OPPONENT(SPECIES_WOBBUFFET) { HP(hp); MaxHP(100); Defense(100); }
    } WHEN {
        TURN { MOVE(player, move, WITH_RNG(RNG_PLANTATION, TRUE)); }
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &damage);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_PLANTATION);
            MESSAGE("The opposing Wobbuffet was seeded!");
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_LEECH_SEED_DRAIN, opponent);
            HP_BAR(opponent);
        }
    } THEN {
        EXPECT_EQ(opponent->hp, hp - damage);
        EXPECT_GT(opponent->hp, 0);
        if (hp <= 10)
            EXPECT_EQ(opponent->hp, 1);
        else
            EXPECT_GT(opponent->hp, 1);
    }
}

SINGLE_BATTLE_TEST("Plantation's False Swipe exception does not prevent existing Leech Seed damage")
{
    u32 move;

    PARAMETRIZE { move = MOVE_FALSE_SWIPE; }
    PARAMETRIZE { move = MOVE_HOLD_BACK; }

    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_FALSE_SWIPE);
        ASSUME(GetMoveEffect(MOVE_LEECH_SEED) == EFFECT_LEECH_SEED);
        PLAYER(SPECIES_BRELOOM) { Ability(ABILITY_PLANTATION); Attack(500); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); MaxHP(100); Defense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_LEECH_SEED); }
        TURN { MOVE(player, move, WITH_RNG(RNG_PLANTATION, TRUE)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LEECH_SEED, player);
        MESSAGE("The opposing Wobbuffet was seeded!");
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, hp: 1);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_LEECH_SEED_DRAIN, opponent);
        HP_BAR(opponent, hp: 0);
        MESSAGE("The opposing Wobbuffet fainted!");
    }
}

SINGLE_BATTLE_TEST("Plantation has a 30% chance to seed damaged targets")
{
    PASSES_RANDOMLY(3, 10, RNG_PLANTATION);
    GIVEN {
        ASSUME(GetMovePower(MOVE_SCRATCH) > 0);
        PLAYER(SPECIES_BULBASAUR) { Ability(ABILITY_PLANTATION); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ABILITY_POPUP(player, ABILITY_PLANTATION);
        MESSAGE("The opposing Wobbuffet was seeded!");
    }
}

SINGLE_BATTLE_TEST("Plantation does not seed Grass-type targets")
{
    GIVEN {
        ASSUME(GetMovePower(MOVE_SCRATCH) > 0);
        ASSUME(IsSpeciesOfType(SPECIES_BULBASAUR, TYPE_GRASS));
        PLAYER(SPECIES_BULBASAUR) { Ability(ABILITY_PLANTATION); }
        OPPONENT(SPECIES_BULBASAUR);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_PLANTATION, TRUE)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_PLANTATION);
            MESSAGE("The opposing Bulbasaur was seeded!");
        }
    }
}

SINGLE_BATTLE_TEST("Plantation only seeds if the target takes damage")
{
    GIVEN {
        ASSUME(GetMovePower(MOVE_SCRATCH) > 0);
        PLAYER(SPECIES_BULBASAUR) { Ability(ABILITY_PLANTATION); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_PROTECT); MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_PLANTATION, TRUE)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PROTECT, opponent);
        NONE_OF {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            ABILITY_POPUP(player, ABILITY_PLANTATION);
            MESSAGE("The opposing Wobbuffet was seeded!");
        }
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Plantation has a 30% chance to seed damaged targets (Traits)")
{
    PASSES_RANDOMLY(3, 10, RNG_PLANTATION);
    GIVEN {
        ASSUME(GetMovePower(MOVE_SCRATCH) > 0);
        PLAYER(SPECIES_BULBASAUR) { Ability(ABILITY_OVERGROW); Innates(ABILITY_PLANTATION); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ABILITY_POPUP(player, ABILITY_PLANTATION);
        MESSAGE("The opposing Wobbuffet was seeded!");
    }
}
#endif
