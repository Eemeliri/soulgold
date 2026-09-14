#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"
#include "battle_util.h"

SINGLE_BATTLE_TEST("Controlled Burn boosts Fire recoil attacks and halves their recoil or HP costs", s16 recoil; s16 damage)
{
    enum Ability ability;
    enum Move move;
    PARAMETRIZE { move = MOVE_FLARE_BLITZ; ability = ABILITY_NONE; }
    PARAMETRIZE { move = MOVE_FLARE_BLITZ; ability = ABILITY_CONTROLLED_BURN; }
    PARAMETRIZE { move = MOVE_MIND_BLOWN; ability = ABILITY_NONE; }
    PARAMETRIZE { move = MOVE_MIND_BLOWN; ability = ABILITY_CONTROLLED_BURN; }
    PARAMETRIZE { move = MOVE_DOUBLE_EDGE; ability = ABILITY_NONE; }
    PARAMETRIZE { move = MOVE_DOUBLE_EDGE; ability = ABILITY_CONTROLLED_BURN; }
    PARAMETRIZE { move = MOVE_STEEL_BEAM; ability = ABILITY_NONE; }
    PARAMETRIZE { move = MOVE_STEEL_BEAM; ability = ABILITY_CONTROLLED_BURN; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NONE); Innates(ability); HP(501); MaxHP(501); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
        HP_BAR(player, captureDamage: &results[i].recoil);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.2), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.2), results[3].damage);
        // Flare Blitz recoil uses the boosted damage, before Controlled Burn halves it.
        EXPECT_EQ(results[1].recoil, max(1, (results[1].damage * GetMoveRecoil(MOVE_FLARE_BLITZ) / 100 + 1) / 2));
        EXPECT_EQ(results[3].recoil, (results[2].recoil + 1) / 2);
        EXPECT_EQ(results[4].damage, results[5].damage);
        EXPECT_EQ(results[6].damage, results[7].damage);
        EXPECT_EQ(results[4].recoil, results[5].recoil);
        EXPECT_EQ(results[6].recoil, results[7].recoil);
    }
}

SINGLE_BATTLE_TEST("Controlled Burn does not boost Fire attacks without recoil", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_CONTROLLED_BURN; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FLAMETHROWER); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Controlled Burn preserves Life Orb damage")
{
    s16 recoil;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CONTROLLED_BURN); Item(ITEM_LIFE_ORB); HP(500); MaxHP(500); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        HP_BAR(player, captureDamage: &recoil);
    } THEN {
        EXPECT_EQ(recoil, 50);
    }
}

DOUBLE_BATTLE_TEST("Controlled Burn charges Mind Blown once for a spread attack")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CONTROLLED_BURN); HP(500); MaxHP(500); }
        PLAYER(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_MIND_BLOWN); }
    } THEN {
        EXPECT_EQ(playerLeft->hp, 375);
    }
}

SINGLE_BATTLE_TEST("Crossfire rewards changing attack types, preserves history through status and resets on switching")
{
    s16 initial, changed, repeated, afterStatus, switched;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NONE); Innates(ABILITY_CROSSFIRE); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_WATER_VEIL); HP(2000); MaxHP(2000); }
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_EMBER); }
        TURN { SWITCH(player, 1); }
        TURN { SWITCH(player, 0); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &initial);
        HP_BAR(opponent, captureDamage: &changed);
        HP_BAR(opponent, captureDamage: &repeated);
        HP_BAR(opponent, captureDamage: &afterStatus);
        HP_BAR(opponent, captureDamage: &switched);
    } THEN {
        EXPECT_EQ(initial, repeated);
        EXPECT_EQ(initial, switched);
        EXPECT_MUL_EQ(initial, Q_4_12(1.25), changed);
        EXPECT_EQ(changed, afterStatus);
    }
}

DOUBLE_BATTLE_TEST("Crossfire applies to every target of a spread attack", s16 leftDamage; s16 rightDamage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_CROSSFIRE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_WATER_GUN, target: opponentLeft); }
        TURN { MOVE(playerLeft, MOVE_HEAT_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAT_WAVE, playerLeft);
        HP_BAR(opponentLeft, captureDamage: &results[i].leftDamage);
        HP_BAR(opponentRight, captureDamage: &results[i].rightDamage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].leftDamage, Q_4_12(1.25), results[1].leftDamage);
        EXPECT_MUL_EQ(results[0].rightDamage, Q_4_12(1.25), results[1].rightDamage);
    }
}

SINGLE_BATTLE_TEST("Crossfire and Bull Rush preserve their bonuses during a charging turn", s16 damage)
{
    enum Ability ability;
    enum Move previous;
    PARAMETRIZE { ability = ABILITY_NONE; previous = MOVE_WATER_GUN; }
    PARAMETRIZE { ability = ABILITY_CROSSFIRE; previous = MOVE_WATER_GUN; }
    PARAMETRIZE { ability = ABILITY_NONE; previous = MOVE_CELEBRATE; }
    PARAMETRIZE { ability = ABILITY_BULL_RUSH; previous = MOVE_CELEBRATE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, previous); }
        TURN { MOVE(player, MOVE_SOLAR_BEAM); }
        TURN { SKIP_TURN(player); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SOLAR_BEAM, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.25), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.2), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("Crossfire compares the effective type of Weather Ball", s16 same; s16 changed)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_CROSSFIRE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_DROUGHT); Innates(ABILITY_WATER_VEIL); HP(2000); MaxHP(2000); }
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
        TURN { MOVE(player, MOVE_WEATHER_BALL); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
        TURN { MOVE(player, MOVE_WEATHER_BALL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WEATHER_BALL, player);
        HP_BAR(opponent, captureDamage: &results[i].same);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WEATHER_BALL, player);
        HP_BAR(opponent, captureDamage: &results[i].changed);
    } FINALLY {
        EXPECT_EQ(results[0].same, results[1].same);
        EXPECT_MUL_EQ(results[0].changed, Q_4_12(1.25), results[1].changed);
    }
}

SINGLE_BATTLE_TEST("Bull Rush boosts one attack per entry and is not consumed by status moves")
{
    s16 first, second, reentry;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NONE); Innates(ABILITY_BULL_RUSH); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { SWITCH(player, 1); }
        TURN { SWITCH(player, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &first);
        HP_BAR(opponent, captureDamage: &second);
        HP_BAR(opponent, captureDamage: &reentry);
    } THEN {
        EXPECT_MUL_EQ(second, Q_4_12(1.2), first);
        EXPECT_EQ(first, reentry);
    }
}

SINGLE_BATTLE_TEST("Bull Rush is consumed by a protected attack", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_BULL_RUSH; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_PROTECT); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Bull Rush boosts all hits of the first multihit attack", s16 first; s16 second)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_BULL_RUSH; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DOUBLE_KICK); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].first);
        HP_BAR(opponent, captureDamage: &results[i].second);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].first, Q_4_12(1.2), results[1].first);
        EXPECT_MUL_EQ(results[0].second, Q_4_12(1.2), results[1].second);
    }
}

SINGLE_BATTLE_TEST("Hot Tag shields the replacement for one hit after a pivot", s16 first; s16 second)
{
    enum Ability ability;
    enum Move move;
    PARAMETRIZE { ability = ABILITY_NONE; move = MOVE_U_TURN; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; move = MOVE_U_TURN; }
    PARAMETRIZE { ability = ABILITY_NONE; move = MOVE_PARTING_SHOT; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; move = MOVE_PARTING_SHOT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NONE); Innates(ability); Speed(100); }
        PLAYER(SPECIES_WYNAUT) { HP(500); MaxHP(500); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, move); SEND_OUT(player, 1); MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].first);
        HP_BAR(player, captureDamage: &results[i].second);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].first, Q_4_12(0.6), results[1].first);
        EXPECT_EQ(results[0].second, results[1].second);
        EXPECT_MUL_EQ(results[2].first, Q_4_12(0.6), results[3].first);
        EXPECT_EQ(results[2].second, results[3].second);
    }
}

SINGLE_BATTLE_TEST("Hot Tag does not activate on a manual switch", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { SWITCH(player, 1); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_HOT_TAG);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Hot Tag persists through Protect and does not survive the recipient switching out", s16 shielded; s16 reentry)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        PLAYER(SPECIES_WYNAUT) { HP(1000); MaxHP(1000); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_U_TURN); SEND_OUT(player, 1); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_PROTECT); MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { SWITCH(player, 0); }
        TURN { MOVE(player, MOVE_U_TURN); SEND_OUT(player, 1); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { SWITCH(player, 0); }
        TURN { SWITCH(player, 1); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].shielded);
        HP_BAR(player, captureDamage: &results[i].reentry);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].shielded, Q_4_12(0.6), results[1].shielded);
        EXPECT_EQ(results[0].reentry, results[1].reentry);
    }
}

SINGLE_BATTLE_TEST("Hot Tag survives Disguise and reduces the first actual hit", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; }
    GIVEN {
        WITH_CONFIG(B_DISGUISE_HP_LOSS, GEN_7);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Speed(100); }
        PLAYER(SPECIES_MIMIKYU_DISGUISED) { Ability(ABILITY_DISGUISE); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_U_TURN); SEND_OUT(player, 1); MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_DISGUISE);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.6), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Hot Tag reduces only the first hit of a multihit move and also works on fixed damage", s16 first; s16 second)
{
    enum Move move;
    PARAMETRIZE { move = MOVE_DOUBLE_KICK; }
    PARAMETRIZE { move = MOVE_SEISMIC_TOSS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_HOT_TAG); Speed(100); }
        PLAYER(SPECIES_WYNAUT) { HP(1000); MaxHP(1000); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_U_TURN); SEND_OUT(player, 1); MOVE(opponent, move); }
        if (move == MOVE_SEISMIC_TOSS)
            TURN { MOVE(opponent, move); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].first);
        HP_BAR(player, captureDamage: &results[i].second);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].second, Q_4_12(0.6), results[0].first);
        EXPECT_MUL_EQ(results[1].second, Q_4_12(0.6), results[1].first);
    }
}

SINGLE_BATTLE_TEST("Incineroar combines Hot Tag with Backdraft on Parting Shot")
{
    GIVEN {
        PLAYER(SPECIES_INCINEROAR) { Level(100); Ability(ABILITY_INTIMIDATE); USE_DEFAULT_INNATES; }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PARTING_SHOT); SEND_OUT(player, 1); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_HOT_TAG);
        ABILITY_POPUP(player, ABILITY_BACKDRAFT);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE - 2);
        EXPECT(gBattleStruct->hotTagActive[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)]);
    }
}

SINGLE_BATTLE_TEST("Hot Tag AI reduces only the first strike, including fixed damage")
{
    enum Move move;
    enum Ability ability;
    u32 roll;
    s16 firstHit;

    for (u32 j = 0; j < 3; j++)
    {
        PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_NONE; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_DOUBLE_KICK; ability = ABILITY_NONE; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_TRIPLE_KICK; ability = ABILITY_NONE; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_BEAT_UP; ability = ABILITY_NONE; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_BULLET_SEED; ability = ABILITY_SKILL_LINK; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_PARENTAL_BOND; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_DUAL_STRIKE; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_HYPER_VOICE; ability = ABILITY_ECHO_CHAMBER; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_SEISMIC_TOSS; ability = ABILITY_NONE; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
        PARAMETRIZE { move = MOVE_NIGHT_SHADE; ability = ABILITY_NONE; roll = j == 0 ? 0 : j == 1 ? 7 : 15; }
    }
    GIVEN {
        WITH_CONFIG(B_BEAT_UP, GEN_5);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NONE); HP(10000); MaxHP(10000); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_MACHAMP);
        OPPONENT(SPECIES_MAGIKARP);
    } WHEN {
        TURN { MOVE(opponent, move, hit: TRUE, WITH_RNG(RNG_DAMAGE_MODIFIER, roll)); }
    } SCENE {
        HP_BAR(player, captureDamage: &firstHit);
    } THEN {
        enum BattlerId battlerDef = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum BattlerId battlerAtk = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        uq4_12_t effectiveness;
        gAiLogicData->abilities[battlerAtk] = ability;
        struct SimulatedDamage normal = AI_CalcDamageSaveBattlers(
            move, battlerAtk, battlerDef, &effectiveness, NO_GIMMICK, NO_GIMMICK);
        gBattleStruct->hotTagActive[battlerDef] = TRUE;
        struct SimulatedDamage shielded = AI_CalcDamageSaveBattlers(
            move, battlerAtk, battlerDef, &effectiveness, NO_GIMMICK, NO_GIMMICK);
        // Use the observed first strike, including its roll and rounding, as the oracle.
        u32 reduction = firstHit - max(1, uq4_12_multiply_by_int_half_down(UQ_4_12(0.6), firstHit));
        if (roll == 0)
            EXPECT_EQ(shielded.maximum, normal.maximum - reduction);
        else if (roll == 7)
            EXPECT_EQ(shielded.median, normal.median - reduction);
        else
            EXPECT_EQ(shielded.minimum, normal.minimum - reduction);
        EXPECT(gBattleStruct->hotTagActive[battlerDef]);
    }
}

SINGLE_BATTLE_TEST("Hot Tag preserves its shield through passed Substitutes and their breaking hit", u16 subDamage; s16 protectedHit; s16 nextHit)
{
    enum Ability ability;
    enum Move pivot;
    PARAMETRIZE { ability = ABILITY_NONE; pivot = MOVE_BATON_PASS; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; pivot = MOVE_BATON_PASS; }
    PARAMETRIZE { ability = ABILITY_NONE; pivot = MOVE_SHED_TAIL; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; pivot = MOVE_SHED_TAIL; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); HP(800); MaxHP(800); Speed(100); }
        PLAYER(SPECIES_WYNAUT) { HP(1000); MaxHP(1000); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(100); Speed(1); }
    } WHEN {
        if (pivot == MOVE_BATON_PASS)
            TURN { MOVE(player, MOVE_SUBSTITUTE); }
        TURN { MOVE(player, pivot); SEND_OUT(player, 1); MOVE(opponent, MOVE_SEISMIC_TOSS); }
        TURN { MOVE(opponent, MOVE_SEISMIC_TOSS); }
        TURN { MOVE(opponent, MOVE_SEISMIC_TOSS); }
        TURN { MOVE(opponent, MOVE_SEISMIC_TOSS); }
    } SCENE {
        HP_BAR(player); // Substitute or Shed Tail's HP cost.
        SUB_HIT(player, captureDamage: &results[i].subDamage);
        SUB_HIT(player);
        MESSAGE("Wynaut's substitute faded!");
        HP_BAR(player, captureDamage: &results[i].protectedHit);
        HP_BAR(player, captureDamage: &results[i].nextHit);
    } FINALLY {
        for (u32 j = 0; j < 4; j += 2)
        {
            EXPECT_EQ(results[j].subDamage, 100);
            EXPECT_EQ(results[j + 1].subDamage, 100);
            EXPECT_EQ(results[j].protectedHit, 100);
            EXPECT_EQ(results[j + 1].protectedHit, 60);
            EXPECT_EQ(results[j].nextHit, 100);
            EXPECT_EQ(results[j + 1].nextHit, 100);
        }
    }
}

SINGLE_BATTLE_TEST("Hot Tag protects the next strike after a multihit attack breaks Substitute", s16 first; s16 next)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_HOT_TAG; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); HP(4); MaxHP(4); Speed(100); }
        PLAYER(SPECIES_WYNAUT) { HP(1000); MaxHP(1000); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SHED_TAIL); SEND_OUT(player, 1); MOVE(opponent, MOVE_DOUBLE_KICK); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(player);
        SUB_HIT(player, subBreak: TRUE);
        HP_BAR(player, captureDamage: &results[i].first);
        HP_BAR(player, captureDamage: &results[i].next);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].first, Q_4_12(0.6), results[1].first);
        EXPECT_EQ(results[0].next, results[1].next);
    }
}

SINGLE_BATTLE_TEST("Hot Tag applies and is spent when a move bypasses Substitute", s16 first; s16 next)
{
    enum Move move;
    enum Ability ability;
    PARAMETRIZE { move = MOVE_ROUND; ability = ABILITY_NONE; }
    PARAMETRIZE { move = MOVE_SEISMIC_TOSS; ability = ABILITY_INFILTRATOR; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_HOT_TAG); HP(800); MaxHP(800); Speed(100); }
        PLAYER(SPECIES_WYNAUT) { HP(1000); MaxHP(1000); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SHED_TAIL); SEND_OUT(player, 1); MOVE(opponent, move); }
        TURN { MOVE(opponent, move); }
    } SCENE {
        HP_BAR(player);
        HP_BAR(player, captureDamage: &results[i].first);
        HP_BAR(player, captureDamage: &results[i].next);
    } THEN {
        EXPECT(player->volatiles.substitute);
        EXPECT(!gBattleStruct->hotTagActive[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)]);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].next, Q_4_12(0.6), results[0].first);
        EXPECT_MUL_EQ(results[1].next, Q_4_12(0.6), results[1].first);
    }
}
