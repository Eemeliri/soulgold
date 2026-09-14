#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"
#include "battle_util.h"

SINGLE_BATTLE_TEST("Chimecho's Mind Float benefits from its Psychic Surge", s16 damage)
{
    u32 species;
    bool32 terrain;

    PARAMETRIZE { species = SPECIES_CHIMECHO; terrain = FALSE; }
    PARAMETRIZE { species = SPECIES_CHIMECHO; terrain = TRUE; }
    PARAMETRIZE { species = SPECIES_CHIMECHO_MEGA; terrain = FALSE; }
    PARAMETRIZE { species = SPECIES_CHIMECHO_MEGA; terrain = TRUE; }
    GIVEN {
        PLAYER(species) { Level(100); USE_DEFAULT_INNATES; }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
        TURN { MOVE(opponent, terrain ? MOVE_CELEBRATE : MOVE_ICE_SPINNER); }
        TURN { MOVE(player, MOVE_CONFUSION); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_PSYCHIC_SURGE);
        ABILITY_POPUP(player, ABILITY_MIND_FLOAT);
        MESSAGE("It doesn't affect Chimecho…");
        MESSAGE("Chimecho used Confusion!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        for (u32 j = 0; j < 4; j += 2)
            EXPECT_MUL_EQ(results[j].damage, Q_4_12(B_TERRAIN_TYPE_BOOST >= GEN_8 ? 1.3 : 1.5), results[j + 1].damage);
    }
}

SINGLE_BATTLE_TEST("Mind Float receives Psychic Terrain's priority protection")
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_LEVITATE; }
    PARAMETRIZE { ability = ABILITY_MIND_FLOAT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Innates(ABILITY_PSYCHIC_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_QUICK_ATTACK); }
    } SCENE {
        if (ability == ABILITY_MIND_FLOAT)
        {
            MESSAGE("Wobbuffet is protected by the Psychic Terrain!");
            NOT HP_BAR(player);
        }
        else
        {
            HP_BAR(player);
        }
    }
}

DOUBLE_BATTLE_TEST("Mind Float enables Expanding Force's terrain power and spread", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_LEVITATE; }
    PARAMETRIZE { ability = ABILITY_MIND_FLOAT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Innates(ABILITY_PSYCHIC_SURGE); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_EXPANDING_FORCE, target: opponentLeft); }
    } SCENE {
        HP_BAR(opponentLeft, captureDamage: &results[i].damage);
        if (ability == ABILITY_MIND_FLOAT)
        {
            HP_BAR(opponentRight);
            NOT HP_BAR(playerRight);
        }
        else
        {
            NONE_OF {
                HP_BAR(opponentRight);
                HP_BAR(playerRight);
            }
        }
    } FINALLY {
        // 1.5x move bonus, terrain bonus, and the 0.75x spread modifier.
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5 * (B_TERRAIN_TYPE_BOOST >= GEN_8 ? 1.3 : 1.5) * 0.75), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mind Float does not receive Electric Terrain's sleep protection")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MIND_FLOAT); Innates(ABILITY_ELECTRIC_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SPORE); }
    } SCENE {
        STATUS_ICON(player, sleep: TRUE);
    }
}

SINGLE_BATTLE_TEST("AI accounts for Mind Float's Ground immunity and Psychic Terrain damage")
{
    s16 damage;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MIND_FLOAT); Innates(ABILITY_PSYCHIC_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EXPANDING_FORCE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &damage);
    } THEN {
        enum BattlerId battler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum BattlerId target = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        uq4_12_t effectiveness;
        gAiLogicData->abilities[battler] = ABILITY_MIND_FLOAT;
        struct SimulatedDamage psychic = AI_CalcDamageSaveBattlers(
            MOVE_EXPANDING_FORCE, battler, target, &effectiveness, NO_GIMMICK, NO_GIMMICK);
        EXPECT_EQ(psychic.maximum, damage);
        struct SimulatedDamage ground = AI_CalcDamageSaveBattlers(
            MOVE_EARTHQUAKE, target, battler, &effectiveness, NO_GIMMICK, NO_GIMMICK);
        EXPECT_EQ(ground.maximum, 0);
        EXPECT_EQ(effectiveness, UQ_4_12(0.0));
    }
}

SINGLE_BATTLE_TEST("Mind Float grants Ground immunity like Levitate")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MIND_FLOAT); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MIND_FLOAT);
        MESSAGE("It doesn't affect Wobbuffet…");
    }
}

AI_SINGLE_BATTLE_TEST("Switch AI recognizes Mind Float and Mold Breaker")
{
    enum Ability ability;
    enum Item item;

    PARAMETRIZE { ability = ABILITY_OWN_TEMPO; item = ITEM_NONE; }
    PARAMETRIZE { ability = ABILITY_MOLD_BREAKER; item = ITEM_NONE; }
    PARAMETRIZE { ability = ABILITY_MOLD_BREAKER; item = ITEM_ABILITY_SHIELD; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_TINKATON) { Ability(ability); Speed(3); }
        OPPONENT(SPECIES_PONYTA) { Level(1); Item(ITEM_EJECT_PACK); Moves(MOVE_OVERHEAT); Speed(4); }
        OPPONENT(SPECIES_VIKAVOLT) { HP(1); Speed(1); Ability(ABILITY_MIND_FLOAT); Moves(MOVE_FLAMETHROWER); Item(item); }
        OPPONENT(SPECIES_HYPNO) { Speed(1); Moves(MOVE_IRON_HEAD); }
    } WHEN {
        if (ability == ABILITY_MOLD_BREAKER && item != ITEM_ABILITY_SHIELD)
            TURN { MOVE(player, MOVE_MUD_SLAP); EXPECT_SEND_OUT(opponent, 2); }
        else
            TURN { MOVE(player, MOVE_MUD_SLAP); EXPECT_SEND_OUT(opponent, 1); }
    }
}

SINGLE_BATTLE_TEST("Mind Float allows Psychic Terrain to boost Psychic moves", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_LEVITATE; }
    PARAMETRIZE { ability = ABILITY_MIND_FLOAT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Innates(ABILITY_PSYCHIC_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CONFUSION); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        if (B_TERRAIN_TYPE_BOOST >= GEN_8)
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), results[1].damage);
        else
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Gravity suppresses Mind Float's Ground immunity")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_GRAVITY) == EFFECT_GRAVITY);
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MIND_FLOAT); }
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
            ABILITY_POPUP(player, ABILITY_MIND_FLOAT);
            MESSAGE("It doesn't affect Wobbuffet…");
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker bypasses Mind Float's Ground immunity")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MIND_FLOAT); }
        OPPONENT(SPECIES_TINKATON) { Ability(ABILITY_MOLD_BREAKER); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MUD_SLAP, opponent);
        HP_BAR(player);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_MIND_FLOAT);
            MESSAGE("It doesn't affect Wobbuffet…");
        }
    }
}

SINGLE_BATTLE_TEST("Mind Float allows Psychic Seed to activate on Psychic Terrain")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_PSYCHIC_SEED].holdEffect == HOLD_EFFECT_TERRAIN_SEED);
        ASSUME(gItemsInfo[ITEM_PSYCHIC_SEED].holdEffectParam == HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MIND_FLOAT); Innates(ABILITY_PSYCHIC_SURGE); Item(ITEM_PSYCHIC_SEED); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_PSYCHIC_SURGE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Using Psychic Seed, the Sp. Def of Wobbuffet rose!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->item, ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Mind Float avoids all grounded entry hazards")
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
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MIND_FLOAT); }
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
