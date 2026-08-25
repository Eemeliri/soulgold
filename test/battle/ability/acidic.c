#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveType(MOVE_SLUDGE_BOMB) == TYPE_POISON);
    ASSUME(GetMovePower(MOVE_SLUDGE_BOMB) > 0);
    ASSUME(GetSpeciesType(SPECIES_BELDUM, 0) == TYPE_STEEL || GetSpeciesType(SPECIES_BELDUM, 1) == TYPE_STEEL);
}

SINGLE_BATTLE_TEST("Acidic makes Poison-type attacks super effective against Steel-type Pokemon")
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_OBLIVIOUS; }
    PARAMETRIZE { ability = ABILITY_ACIDIC; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_BELDUM);
    } WHEN {
        TURN { MOVE(player, MOVE_SLUDGE_BOMB); }
    } SCENE {
        if (ability == ABILITY_ACIDIC)
        {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SLUDGE_BOMB, player);
            HP_BAR(opponent);
            MESSAGE("It's super effective!");
        }
        else
        {
            NONE_OF {
                ANIMATION(ANIM_TYPE_MOVE, MOVE_SLUDGE_BOMB, player);
                HP_BAR(opponent);
            }
            MESSAGE("It doesn't affect the opposing Beldum…");
        }
    }
}

SINGLE_BATTLE_TEST("Acidic changes Steel's Poison matchup to exactly 2x damage", s16 damage)
{
    u32 species;

    PARAMETRIZE { species = SPECIES_WOBBUFFET; }
    PARAMETRIZE { species = SPECIES_BELDUM; }
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_WOBBUFFET, 0) == TYPE_PSYCHIC);
        ASSUME(GetSpeciesType(SPECIES_WOBBUFFET, 1) == TYPE_PSYCHIC);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ACIDIC); Level(50); SpAttack(100); }
        OPPONENT(species) { Ability(ABILITY_CLEAR_BODY); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SLUDGE_BOMB, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Acidic composes with a Steel-type Pokemon's other type")
{
    u32 species;
    uq4_12_t expectedMultiplier;

    PARAMETRIZE { species = SPECIES_BELDUM;     expectedMultiplier = UQ_4_12(2.0); }
    PARAMETRIZE { species = SPECIES_TINKATON;   expectedMultiplier = UQ_4_12(4.0); }
    PARAMETRIZE { species = SPECIES_REVAVROOM;  expectedMultiplier = UQ_4_12(1.0); }
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_TINKATON, 0) == TYPE_FAIRY || GetSpeciesType(SPECIES_TINKATON, 1) == TYPE_FAIRY);
        ASSUME(GetSpeciesType(SPECIES_TINKATON, 0) == TYPE_STEEL || GetSpeciesType(SPECIES_TINKATON, 1) == TYPE_STEEL);
        ASSUME(GetSpeciesType(SPECIES_REVAVROOM, 0) == TYPE_POISON || GetSpeciesType(SPECIES_REVAVROOM, 1) == TYPE_POISON);
        ASSUME(GetSpeciesType(SPECIES_REVAVROOM, 0) == TYPE_STEEL || GetSpeciesType(SPECIES_REVAVROOM, 1) == TYPE_STEEL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ACIDIC); }
        OPPONENT(species) { Ability(ABILITY_CLEAR_BODY); }
    } WHEN {
        TURN { }
    } THEN {
        enum BattlerId battlerAtk = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum BattlerId battlerDef = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        struct BattleContext ctx = {
            .battlerAtk = battlerAtk,
            .battlerDef = battlerDef,
            .move = MOVE_SLUDGE_BOMB,
            .chosenMove = MOVE_SLUDGE_BOMB,
            .moveType = TYPE_POISON,
        };

        EXPECT_EQ(CalcTypeEffectivenessMultiplier(&ctx), expectedMultiplier);
    }
}

SINGLE_BATTLE_TEST("Acidic does not change non-Poison attacks against Steel-type Pokemon")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_SCRATCH) == TYPE_NORMAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ACIDIC); }
        OPPONENT(SPECIES_BELDUM);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        MESSAGE("It's not very effective…");
        NONE_OF { MESSAGE("It's super effective!"); }
    }
}

SINGLE_BATTLE_TEST("Gastro Acid suppresses Acidic")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_GASTRO_ACID) == EFFECT_GASTRO_ACID);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ACIDIC); Speed(1); }
        OPPONENT(SPECIES_BELDUM) { Speed(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_GASTRO_ACID); MOVE(player, MOVE_SLUDGE_BOMB); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GASTRO_ACID, opponent);
        NONE_OF {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SLUDGE_BOMB, player);
            HP_BAR(opponent);
        }
        MESSAGE("It doesn't affect the opposing Beldum…");
    }
}

SINGLE_BATTLE_TEST("Anticipation does not account for Acidic")
{
    GIVEN {
        PLAYER(SPECIES_BELDUM) { Ability(ABILITY_ANTICIPATION); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_ACIDIC); Moves(MOVE_SLUDGE_BOMB, MOVE_CELEBRATE); }
    } WHEN {
        TURN { }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_ANTICIPATION);
    }
}

SINGLE_BATTLE_TEST("Context-free type calculations do not inherit Acidic from battler 0")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ACIDIC); }
        OPPONENT(SPECIES_BELDUM) { Ability(ABILITY_CLEAR_BODY); }
    } WHEN {
        TURN { }
    } THEN {
        enum BattlerId battlerAtk = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum BattlerId battlerDef = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        struct Pokemon *mon = GetBattlerMon(battlerDef);

        EXPECT_EQ(CalcPartyMonTypeEffectivenessMultiplier(MOVE_SLUDGE_BOMB, SPECIES_BELDUM, mon, MAX_BATTLERS_COUNT), UQ_4_12(0.0));
        EXPECT_EQ(GetOverworldTypeEffectiveness(mon, TYPE_POISON), UQ_4_12(0.0));
        EXPECT_EQ(CalcPartyMonTypeEffectivenessMultiplier(MOVE_SLUDGE_BOMB, SPECIES_BELDUM, mon, battlerAtk), UQ_4_12(2.0));
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Acidic affects moves converted to Poison by Poison-ate")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_SCRATCH) == TYPE_NORMAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ACIDIC); Innates(ABILITY_POISON_ATE); }
        OPPONENT(SPECIES_BELDUM);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Acidic makes Poison-type attacks super effective against Steel-type Pokemon (Traits)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_OBLIVIOUS); Innates(ABILITY_ACIDIC); }
        OPPONENT(SPECIES_BELDUM);
    } WHEN {
        TURN { MOVE(player, MOVE_SLUDGE_BOMB); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SLUDGE_BOMB, player);
        HP_BAR(opponent);
        MESSAGE("It's super effective!");
    }
}
#endif
