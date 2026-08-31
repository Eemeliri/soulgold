#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveType(MOVE_EMBER) == TYPE_FIRE);
    ASSUME(GetMoveType(MOVE_WATER_GUN) == TYPE_WATER);
    ASSUME(GetMoveType(MOVE_ENERGY_BALL) == TYPE_GRASS);
    ASSUME(GetMoveType(MOVE_THUNDER_SHOCK) == TYPE_ELECTRIC);
    ASSUME(GetMoveType(MOVE_ICE_BEAM) == TYPE_ICE);
    ASSUME(GetMoveType(MOVE_DRAGON_PULSE) == TYPE_DRAGON);
    ASSUME(GetMoveType(MOVE_MOONBLAST) == TYPE_FAIRY);
    ASSUME(GetMoveType(MOVE_G_MAX_FIREBALL) == TYPE_FIRE);
    ASSUME(MoveIgnoresTargetAbility(MOVE_G_MAX_FIREBALL));
    ASSUME(!IsSpeciesOfType(SPECIES_WOBBUFFET, TYPE_DRAGON));
    ASSUME(IsSpeciesOfType(SPECIES_SERPERIOR, TYPE_GRASS));
    ASSUME(!IsSpeciesOfType(SPECIES_SERPERIOR, TYPE_DRAGON));
}

SINGLE_BATTLE_TEST("Like a Dragon grants Dragon-type STAB", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Level(50); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_PULSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon grants all Dragon-type resistances", s16 damage)
{
    enum Ability ability;
    enum Move move;

    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_EMBER; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_EMBER; }
    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_WATER_GUN; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_WATER_GUN; }
    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_ENERGY_BALL; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_ENERGY_BALL; }
    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_THUNDER_SHOCK; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_THUNDER_SHOCK; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, move, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.5), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(0.5), results[3].damage);
        EXPECT_MUL_EQ(results[4].damage, Q_4_12(0.5), results[5].damage);
        EXPECT_MUL_EQ(results[6].damage, Q_4_12(0.5), results[7].damage);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon does not grant Dragon-type weaknesses", s16 damage)
{
    enum Ability ability;
    enum Move move;

    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_ICE_BEAM; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_ICE_BEAM; }
    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_DRAGON_PULSE; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_DRAGON_PULSE; }
    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_MOONBLAST; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_MOONBLAST; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, move, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_EQ(results[2].damage, results[3].damage);
        EXPECT_EQ(results[4].damage, results[5].damage);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon does not add Dragon to the user's actual types")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_LIKE_A_DRAGON); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } THEN {
        enum Type types[3];
        enum BattlerId battler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);

        GetBattlerTypes(battler, FALSE, types);
        EXPECT_NE(types[0], TYPE_DRAGON);
        EXPECT_NE(types[1], TYPE_DRAGON);
        EXPECT_NE(types[2], TYPE_DRAGON);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon's resistances combine with the user's actual type", s16 damage)
{
    enum Ability ability;
    enum Move move;

    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_EMBER; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_EMBER; }
    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_WATER_GUN; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_WATER_GUN; }
    PARAMETRIZE { ability = ABILITY_KLUTZ;         move = MOVE_ICE_BEAM; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; move = MOVE_ICE_BEAM; }
    GIVEN {
        PLAYER(SPECIES_SERPERIOR) { Ability(ABILITY_OVERGROW); Innates(ability); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, move, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.5), results[1].damage); // Fire: 2x becomes 1x.
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(0.5), results[3].damage); // Water: 0.5x becomes 0.25x.
        EXPECT_EQ(results[4].damage, results[5].damage);                 // Ice remains 2x, not 4x.
    }
}

SINGLE_BATTLE_TEST("Like a Dragon resistances invert in inverse battles", s16 damage)
{
    bool32 inverseBattle;

    PARAMETRIZE { inverseBattle = FALSE; }
    PARAMETRIZE { inverseBattle = TRUE; }
    GIVEN {
        if (inverseBattle)
            FLAG_SET(TESTING_FLAG_INVERSE_BATTLE);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_LIKE_A_DRAGON); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_GUN, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(4.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Off-field effectiveness includes Like a Dragon resistances")
{
    GIVEN {
        PLAYER(SPECIES_SERPERIOR) { Ability(ABILITY_OVERGROW); Level(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } THEN {
        enum BattlerId battler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        struct Pokemon *mon = GetBattlerMon(battler);

        EXPECT_EQ(CalcPartyMonTypeEffectivenessMultiplier(MOVE_EMBER, SPECIES_SERPERIOR, mon, MAX_BATTLERS_COUNT), UQ_4_12(1.0));
        EXPECT_EQ(CalcPartyMonTypeEffectivenessMultiplier(MOVE_EMBER, SPECIES_SERPERIOR, NULL, MAX_BATTLERS_COUNT), UQ_4_12(1.0));
        EXPECT_EQ(GetOverworldTypeEffectiveness(mon, TYPE_FIRE), UQ_4_12(1.0));
    }
}

SINGLE_BATTLE_TEST("Off-field Like a Dragon respects ability bypass and Ability Shield")
{
    enum Move move;
    enum Ability ability;
    enum Item item;
    uq4_12_t expectedModifier;

    PARAMETRIZE { move = MOVE_EMBER; ability = ABILITY_KLUTZ; item = ITEM_NONE; expectedModifier = UQ_4_12(1.0); }
    PARAMETRIZE { move = MOVE_EMBER; ability = ABILITY_MOLD_BREAKER; item = ITEM_NONE; expectedModifier = UQ_4_12(2.0); }
    PARAMETRIZE { move = MOVE_EMBER; ability = ABILITY_MOLD_BREAKER; item = ITEM_ABILITY_SHIELD; expectedModifier = UQ_4_12(1.0); }
    PARAMETRIZE { move = MOVE_G_MAX_FIREBALL; ability = ABILITY_KLUTZ; item = ITEM_NONE; expectedModifier = UQ_4_12(2.0); }
    PARAMETRIZE { move = MOVE_G_MAX_FIREBALL; ability = ABILITY_KLUTZ; item = ITEM_ABILITY_SHIELD; expectedModifier = UQ_4_12(1.0); }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_ABILITY_SHIELD].holdEffect == HOLD_EFFECT_ABILITY_SHIELD);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_SERPERIOR) { Ability(ABILITY_OVERGROW); Level(100); Item(item); }
    } WHEN {
        TURN { }
    } THEN {
        enum BattlerId battlerAtk = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum BattlerId battlerDef = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        struct Pokemon *mon = GetBattlerMon(battlerDef);

        EXPECT_EQ(CalcPartyMonTypeEffectivenessMultiplier(move, SPECIES_SERPERIOR, mon, battlerAtk), expectedModifier);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon off-field Ability Shield is disabled by Magic Room")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_MAGIC_ROOM) == EFFECT_MAGIC_ROOM);
        ASSUME(gItemsInfo[ITEM_ABILITY_SHIELD].holdEffect == HOLD_EFFECT_ABILITY_SHIELD);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MOLD_BREAKER); }
        OPPONENT(SPECIES_SERPERIOR) { Ability(ABILITY_OVERGROW); Level(100); Item(ITEM_ABILITY_SHIELD); }
    } WHEN {
        TURN { MOVE(player, MOVE_MAGIC_ROOM); }
    } THEN {
        enum BattlerId battlerAtk = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum BattlerId battlerDef = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        struct Pokemon *mon = GetBattlerMon(battlerDef);

        EXPECT_EQ(CalcPartyMonTypeEffectivenessMultiplier(MOVE_EMBER, SPECIES_SERPERIOR, mon, battlerAtk), UQ_4_12(2.0));
    }
}

SINGLE_BATTLE_TEST("Like a Dragon's resistances are bypassed by Mold Breaker", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_MOLD_BREAKER; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_LIKE_A_DRAGON); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); Level(50); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_GUN, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon's benefits are suppressed by Gastro Acid", s16 damageDealt, s16 damageTaken)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Level(50); HP(1000); MaxHP(1000); SpAttack(100); SpDefense(100); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); HP(1000); MaxHP(1000); SpAttack(100); SpDefense(100); Speed(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_GASTRO_ACID); MOVE(player, MOVE_DRAGON_PULSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
        TURN { MOVE(opponent, MOVE_WATER_GUN, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damageDealt);
        HP_BAR(player, captureDamage: &results[i].damageTaken);
    } FINALLY {
        EXPECT_EQ(results[0].damageDealt, results[1].damageDealt);
        EXPECT_EQ(results[0].damageTaken, results[1].damageTaken);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon preserves Dragon STAB after Terastallizing into another type", s16 damage)
{
    bool32 tera;

    PARAMETRIZE { tera = GIMMICK_NONE; }
    PARAMETRIZE { tera = GIMMICK_TERA; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_LIKE_A_DRAGON); TeraType(TYPE_NORMAL); Level(50); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_PULSE, gimmick: tera, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon stacks its Dragon STAB with Dragon Terastallization", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_LIKE_A_DRAGON; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); TeraType(TYPE_DRAGON); Level(50); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_PULSE, gimmick: GIMMICK_TERA, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.33), results[1].damage);
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Like a Dragon resistances respect Inversion", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_INVERSION; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Innates(ABILITY_LIKE_A_DRAGON); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_GUN, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(4.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon grants Dragon-type STAB as an innate", s16 damage)
{
    enum Ability innate;

    PARAMETRIZE { innate = ABILITY_KLUTZ; }
    PARAMETRIZE { innate = ABILITY_LIKE_A_DRAGON; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_OBLIVIOUS); Innates(innate); Level(50); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_PULSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Like a Dragon grants Dragon-type resistances as an innate", s16 damage)
{
    enum Ability innate;

    PARAMETRIZE { innate = ABILITY_KLUTZ; }
    PARAMETRIZE { innate = ABILITY_LIKE_A_DRAGON; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_OBLIVIOUS); Innates(innate); Level(50); HP(1000); MaxHP(1000); SpDefense(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_GUN, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.5), results[1].damage);
    }
}
#endif
