#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Alolan Raichu's Electrolevitate preserves its Electric Surge boost", s16 damage)
{
    bool32 terrain;

    PARAMETRIZE { terrain = FALSE; }
    PARAMETRIZE { terrain = TRUE; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        ASSUME(GetMoveType(MOVE_THUNDER_SHOCK) == TYPE_ELECTRIC);
        ASSUME(GetMoveEffect(MOVE_ICE_SPINNER) == EFFECT_ICE_SPINNER);
        PLAYER(SPECIES_RAICHU_ALOLA) { Level(100); USE_DEFAULT_INNATES; }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
        TURN { MOVE(opponent, terrain ? MOVE_CELEBRATE : MOVE_ICE_SPINNER); }
        TURN { MOVE(player, MOVE_THUNDER_SHOCK); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ELECTRIC_SURGE);
        ABILITY_POPUP(player, ABILITY_ELECTROLEVITATE);
        MESSAGE("It doesn't affect Raichu…");
        MESSAGE("Raichu used Thunder Shock!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT(SpeciesHasInnate(SPECIES_RAICHU_ALOLA, ABILITY_ELECTROLEVITATE));
        EXPECT(SpeciesHasInnate(SPECIES_RAICHU_ALOLA, ABILITY_ELECTRIC_SURGE));
        EXPECT(!SpeciesHasInnate(SPECIES_RAICHU_ALOLA, ABILITY_LEVITATE));
    } FINALLY {
        if (B_TERRAIN_TYPE_BOOST >= GEN_8)
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), results[1].damage);
        else
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Electrolevitate grants Ground immunity like Levitate")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ELECTROLEVITATE); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ELECTROLEVITATE);
        MESSAGE("It doesn't affect Wobbuffet…");
    }
}

SINGLE_BATTLE_TEST("Electrolevitate allows Electric Terrain to boost Electric moves", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_LEVITATE; }
    PARAMETRIZE { ability = ABILITY_ELECTROLEVITATE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Innates(ABILITY_ELECTRIC_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_THUNDER_SHOCK); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        if (B_TERRAIN_TYPE_BOOST >= GEN_8)
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), results[1].damage);
        else
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Gravity suppresses Electrolevitate's Ground immunity")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_GRAVITY) == EFFECT_GRAVITY);
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ELECTROLEVITATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_GRAVITY); }
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GRAVITY, opponent);
        MESSAGE("Gravity intensified!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MUD_SLAP, opponent);
        HP_BAR(player);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_ELECTROLEVITATE);
            MESSAGE("It doesn't affect Wobbuffet…");
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker bypasses Electrolevitate's Ground immunity")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ELECTROLEVITATE); }
        OPPONENT(SPECIES_TINKATON) { Ability(ABILITY_MOLD_BREAKER); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MUD_SLAP, opponent);
        HP_BAR(player);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_ELECTROLEVITATE);
            MESSAGE("It doesn't affect Wobbuffet…");
        }
    }
}

SINGLE_BATTLE_TEST("Electrolevitate allows Electric Terrain to prevent sleep")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ELECTROLEVITATE); Innates(ABILITY_ELECTRIC_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SPORE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ELECTRIC_SURGE);
        MESSAGE("The opposing Wobbuffet used Spore!");
        MESSAGE("Wobbuffet surrounds itself with electrified terrain!");
        NOT STATUS_ICON(player, sleep: TRUE);
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Electrolevitate allows Electric Seed to activate on Electric Terrain")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_ELECTRIC_SEED].holdEffect == HOLD_EFFECT_TERRAIN_SEED);
        ASSUME(gItemsInfo[ITEM_ELECTRIC_SEED].holdEffectParam == HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ELECTROLEVITATE); Innates(ABILITY_ELECTRIC_SURGE); Item(ITEM_ELECTRIC_SEED); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ELECTRIC_SURGE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Using Electric Seed, the Defense of Wobbuffet rose!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->item, ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Electrolevitate avoids all grounded entry hazards")
{
    enum Move hazard;

    PARAMETRIZE { hazard = MOVE_SPIKES; }
    PARAMETRIZE { hazard = MOVE_TOXIC_SPIKES; }
    PARAMETRIZE { hazard = MOVE_STICKY_WEB; }
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_SPIKES) == EFFECT_SPIKES);
        ASSUME(GetMoveEffect(MOVE_TOXIC_SPIKES) == EFFECT_TOXIC_SPIKES);
        ASSUME(GetMoveEffect(MOVE_STICKY_WEB) == EFFECT_STICKY_WEB);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_ELECTROLEVITATE); }
    } WHEN {
        TURN { MOVE(player, hazard); }
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("2 sent out Wobbuffet!");
        NONE_OF {
            MESSAGE("The opposing Wobbuffet was hurt by the spikes!");
            MESSAGE("The opposing Wobbuffet was poisoned!");
            MESSAGE("The opposing Wobbuffet was caught in a sticky web!");
        }
    } THEN {
        EXPECT_EQ(opponent->hp, opponent->maxHP);
        EXPECT_EQ(opponent->status1, STATUS1_NONE);
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
    }
}
