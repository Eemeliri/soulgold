#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Allseeing Idol grants Ground immunity with or without Gravity")
{
    bool32 gravity;

    PARAMETRIZE { gravity = FALSE; }
    PARAMETRIZE { gravity = TRUE; }

    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ALLSEEING_IDOL); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_GRAVITY, MOVE_MUD_SLAP); }
    } WHEN {
        if (gravity)
            TURN { MOVE(opponent, MOVE_GRAVITY); }
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        if (gravity) {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_GRAVITY, opponent);
            MESSAGE("Gravity intensified!");
        }
        ABILITY_POPUP(player, ABILITY_ALLSEEING_IDOL);
        MESSAGE("It doesn't affect Wobbuffet…");
    }
}

SINGLE_BATTLE_TEST("Allseeing Idol is bypassed by Mold Breaker during Gravity")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ALLSEEING_IDOL); }
        OPPONENT(SPECIES_TINKATON) { Ability(ABILITY_MOLD_BREAKER); Moves(MOVE_GRAVITY, MOVE_MUD_SLAP); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_GRAVITY); }
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GRAVITY, opponent);
        MESSAGE("Gravity intensified!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MUD_SLAP, opponent);
        HP_BAR(player);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_ALLSEEING_IDOL);
            MESSAGE("It doesn't affect Wobbuffet…");
        }
    }
}

SINGLE_BATTLE_TEST("Allseeing Idol avoids grounded hazards with or without Gravity")
{
    bool32 gravity;

    PARAMETRIZE { gravity = FALSE; }
    PARAMETRIZE { gravity = TRUE; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(gravity ? ABILITY_GRAVITY_WELL : ABILITY_SHADOW_TAG); }
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ALLSEEING_IDOL); HP(160); MaxHP(160); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_TOXIC_SPIKES, MOVE_STEALTH_ROCK, MOVE_STICKY_WEB, MOVE_SPIKES); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TOXIC_SPIKES); }
        TURN { MOVE(opponent, MOVE_STEALTH_ROCK); }
        TURN { MOVE(opponent, MOVE_STICKY_WEB); }
        TURN { MOVE(opponent, MOVE_SPIKES); }
        TURN { SWITCH(player, 1); MOVE(opponent, MOVE_SPIKES); }
    } SCENE {
        if (gravity) {
            ABILITY_POPUP(player, ABILITY_GRAVITY_WELL);
            MESSAGE("Gravity intensified!");
        }
        MESSAGE("Pointed stones dug into Wobbuffet!");
        NONE_OF {
            MESSAGE("Wobbuffet was poisoned!");
            MESSAGE("Wobbuffet was badly poisoned!");
            MESSAGE("Wobbuffet was caught in a sticky web!");
            MESSAGE("Wobbuffet was hurt by the spikes!");
        }
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
        EXPECT_LT(player->hp, player->maxHP); // Allseeing Idol does not avoid Stealth Rock.
    }
}

SINGLE_BATTLE_TEST("Allseeing Idol boosts Defense by 30 percent only during Gravity", s16 damage)
{
    enum Ability ability;
    enum Move move;
    bool32 gravity;

    PARAMETRIZE { ability = ABILITY_LIGHT_METAL;    move = MOVE_SCRATCH; gravity = FALSE; }
    PARAMETRIZE { ability = ABILITY_ALLSEEING_IDOL; move = MOVE_SCRATCH; gravity = FALSE; }
    PARAMETRIZE { ability = ABILITY_LIGHT_METAL;    move = MOVE_SCRATCH; gravity = TRUE;  }
    PARAMETRIZE { ability = ABILITY_ALLSEEING_IDOL; move = MOVE_SCRATCH; gravity = TRUE;  }
    PARAMETRIZE { ability = ABILITY_LIGHT_METAL;    move = MOVE_PSYCHIC; gravity = TRUE;  }
    PARAMETRIZE { ability = ABILITY_ALLSEEING_IDOL; move = MOVE_PSYCHIC; gravity = TRUE;  }

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(GetMoveCategory(MOVE_PSYCHIC) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Defense(200); SpDefense(200); }
        OPPONENT(SPECIES_WOBBUFFET) { Attack(200); SpAttack(200); Moves(MOVE_CELEBRATE, MOVE_GRAVITY, MOVE_SCRATCH, MOVE_PSYCHIC); }
    } WHEN {
        if (gravity)
            TURN { MOVE(opponent, MOVE_GRAVITY); }
        else
            TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, move); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_EQ(results[0].damage, results[2].damage);
        EXPECT_MUL_EQ(results[3].damage, UQ_4_12(1.3), results[2].damage);
        EXPECT_EQ(results[4].damage, results[5].damage);
    }
}

SINGLE_BATTLE_TEST("Allseeing Idol loses its Defense boost when Gravity ends")
{
    s16 gravityDamage;
    s16 normalDamage;

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ALLSEEING_IDOL); HP(1000); MaxHP(1000); Defense(200); }
        OPPONENT(SPECIES_WOBBUFFET) { Attack(200); Moves(MOVE_GRAVITY, MOVE_SCRATCH, MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_GRAVITY); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GRAVITY, opponent);
        MESSAGE("Gravity intensified!");
        HP_BAR(player, captureDamage: &gravityDamage);
        MESSAGE("Gravity returned to normal!");
        HP_BAR(player, captureDamage: &normalDamage);
    } THEN {
        EXPECT_MUL_EQ(gravityDamage, UQ_4_12(1.3), normalDamage);
    }
}

SINGLE_BATTLE_TEST("Allseeing Idol replaces Claydol's Levitate and works with Gravity Well")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_CLAYDOL) { Innates(ABILITY_GRAVITY_WELL); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_MUD_SLAP); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_GRAVITY_WELL);
        MESSAGE("Gravity intensified!");
        ABILITY_POPUP(player, ABILITY_ALLSEEING_IDOL);
        MESSAGE("It doesn't affect Claydol…");
    } THEN {
        EXPECT_EQ(player->ability, ABILITY_ALLSEEING_IDOL);
    }
}

AI_SINGLE_BATTLE_TEST("Allseeing Idol's Ground immunity is recognized by the AI during Gravity")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_TINKATON) { Ability(ABILITY_OWN_TEMPO); Innates(ABILITY_GRAVITY_WELL); Moves(MOVE_MUD_SLAP); Speed(3); }
        OPPONENT(SPECIES_PONYTA) { Level(1); Item(ITEM_EJECT_PACK); Moves(MOVE_OVERHEAT); Speed(4); }
        OPPONENT(SPECIES_VIKAVOLT) { HP(1); Ability(ABILITY_ALLSEEING_IDOL); Moves(MOVE_FLAMETHROWER); Speed(1); }
        OPPONENT(SPECIES_HYPNO) { Moves(MOVE_IRON_HEAD); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_MUD_SLAP); EXPECT_SEND_OUT(opponent, 1); }
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Allseeing Idol works as an innate trait during Gravity")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_LIGHT_METAL); Innates(ABILITY_ALLSEEING_IDOL); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_GRAVITY, MOVE_MUD_SLAP); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_GRAVITY); }
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GRAVITY, opponent);
        MESSAGE("Gravity intensified!");
        ABILITY_POPUP(player, ABILITY_ALLSEEING_IDOL);
        MESSAGE("It doesn't affect Wobbuffet…");
    }
}
#endif
