#include "global.h"
#include "event_data.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Magnify Field extends finite weather but not infinite weather", u8 duration)
{
    bool32 finiteWeather;

    PARAMETRIZE { finiteWeather = FALSE; }
    PARAMETRIZE { finiteWeather = TRUE; }
    GIVEN {
        if (finiteWeather)
            STARTING_WEATHER_WITH_DURATION(B_WEATHER_RAIN_NORMAL, 5);
        else
            STARTING_WEATHER(B_WEATHER_RAIN_NORMAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGNIFY_FIELD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {}
    } THEN {
        results[i].duration = gBattleStruct->weatherDuration;
    } FINALLY {
        EXPECT_EQ(results[0].duration, 0);
        EXPECT_EQ(results[1].duration, 6);
    }
}

SINGLE_BATTLE_TEST("Magnify Field extends standard temporary terrain by two turns")
{
    SetStartingStatus(STARTING_STATUS_ELECTRIC_TERRAIN_TEMPORARY);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGNIFY_FIELD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {}
    } THEN {
        EXPECT_EQ(gFieldTimers.terrainTimer, 6);
        ResetStartingStatuses();
    }
}

SINGLE_BATTLE_TEST("Time Spiral inverts move priority", u16 hp)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_BIG_PECKS; }
    PARAMETRIZE { ability = ABILITY_TIME_SPIRAL; }
    GIVEN {
        ASSUME(GetMovePriority(MOVE_QUICK_ATTACK) > GetMovePriority(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); HP(1); MaxHP(1); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(1); Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_QUICK_ATTACK); }
    } THEN {
        results[i].hp = player->hp;
    } FINALLY {
        EXPECT_EQ(results[0].hp, 0);
        EXPECT_EQ(results[1].hp, 1);
    }
}

SINGLE_BATTLE_TEST("Time Spiral does not invert Dragon Tail's forced-switch priority")
{
    GIVEN {
        ASSUME(GetMovePriority(MOVE_DRAGON_TAIL) < GetMovePriority(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TIME_SPIRAL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_TAIL, hit: TRUE); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_TAIL, player);
    }
}

SINGLE_BATTLE_TEST("Time Spiral accelerates finite weather timers once per turn", u8 duration)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_BIG_PECKS; }
    PARAMETRIZE { ability = ABILITY_TIME_SPIRAL; }
    GIVEN {
        STARTING_WEATHER_WITH_DURATION(B_WEATHER_RAIN_NORMAL, 5);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        results[i].duration = gBattleStruct->weatherDuration;
    } FINALLY {
        EXPECT_EQ(results[0].duration, 4);
        EXPECT_EQ(results[1].duration, 3);
    }
}

SINGLE_BATTLE_TEST("Rock and Stone sets Stealth Rock after knocking out a foe")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ROCK_AND_STONE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } THEN {
        EXPECT(IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_STEALTH_ROCK));
    }
}

SINGLE_BATTLE_TEST("Rock and Stone does not set Stealth Rock without a KO")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ROCK_AND_STONE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); MaxHP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } THEN {
        EXPECT(!IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_STEALTH_ROCK));
    }
}

SINGLE_BATTLE_TEST("Shockwiring charges on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SHOCKWIRING); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } THEN {
        EXPECT(player->volatiles.chargeTimer > 0);
    }
}

SINGLE_BATTLE_TEST("Heatstorm sets Scorched Field on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_HEATSTORM); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        EXPECT(gFieldStatuses & STATUS_FIELD_SCORCHED_FIELD);
    }
}

SINGLE_BATTLE_TEST("Lava Surfer doubles Speed during Scorched Field")
{
    SetStartingStatus(STARTING_STATUS_SCORCHED_FIELD);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_LAVA_SURFER); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(3); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    }
}

SINGLE_BATTLE_TEST("Ash Assets boosts damage during Scorched Field", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_ASH_ASSETS; }
    SetStartingStatus(STARTING_STATUS_SCORCHED_FIELD);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.15), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Ash Assets works while its holder is airborne", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_ASH_ASSETS; }
    SetStartingStatus(STARTING_STATUS_SCORCHED_FIELD);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Item(ITEM_AIR_BALLOON); Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.15), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Ash Assets starts Scorched Field after a KO")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ASH_ASSETS); Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
    } THEN {
        EXPECT(gFieldStatuses & STATUS_FIELD_SCORCHED_FIELD);
    }
}

SINGLE_BATTLE_TEST("Ash Assets does not restart Scorched Field after a KO if it is already active")
{
    SetStartingStatus(STARTING_STATUS_SCORCHED_FIELD);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ASH_ASSETS); Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
    } SCENE {
        NONE_OF { ABILITY_POPUP(player, ABILITY_ASH_ASSETS); }
    } THEN {
        EXPECT(gFieldStatuses & STATUS_FIELD_SCORCHED_FIELD);
    }
}

SINGLE_BATTLE_TEST("Tidal Deity bypasses Protect at full HP and summons rain after being damaged")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TIDAL_DEITY); Attack(200); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_PROTECT); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        EXPECT_LT(opponent->hp, opponent->maxHP);
        EXPECT(gBattleWeather & B_WEATHER_RAIN);
    }
}

SINGLE_BATTLE_TEST("Tidal Deity does not summon rain from a hit taken below full HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TIDAL_DEITY); HP(80); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        EXPECT(!(gBattleWeather & B_WEATHER_RAIN));
    }
}

SINGLE_BATTLE_TEST("Windburst sets Tailwind on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); Ability(ABILITY_WINDBURST); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(15); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_WINDBURST);
        MESSAGE("The Tailwind blew from behind your team!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    }
}

SINGLE_BATTLE_TEST("Generic switch-in boost abilities raise their matching stat")
{
    enum Ability ability;
    enum Stat statId;

    PARAMETRIZE { ability = ABILITY_BATTLE_FERVOR; statId = STAT_ATK; }
    PARAMETRIZE { ability = ABILITY_GUARD_STANCE; statId = STAT_DEF; }
    PARAMETRIZE { ability = ABILITY_MENTAL_SURGE; statId = STAT_SPATK; }
    PARAMETRIZE { ability = ABILITY_RESOLUTE_GUARD; statId = STAT_SPDEF; }
    PARAMETRIZE { ability = ABILITY_SKIP_STEP; statId = STAT_SPEED; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ability);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
    } THEN {
        EXPECT_EQ(player->statStages[statId], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Generic switch-in drop abilities lower their matching opposing stat")
{
    enum Ability ability;
    enum Stat statId;

    PARAMETRIZE { ability = ABILITY_BREAKING_PRESENCE; statId = STAT_DEF; }
    PARAMETRIZE { ability = ABILITY_DISQUIET; statId = STAT_SPDEF; }
    PARAMETRIZE { ability = ABILITY_HOBBLE; statId = STAT_SPEED; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(opponent, ability);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
    } THEN {
        EXPECT_EQ(player->statStages[statId], DEFAULT_STAT_STAGE - 1);
    }
}

#if MAX_MON_TRAITS > 1

SINGLE_BATTLE_TEST("New switch-in abilities work as innates")
{
    enum Ability innate;
    enum Stat statId;
    bool32 targetsUser;

    PARAMETRIZE { innate = ABILITY_SKIP_STEP; statId = STAT_SPEED; targetsUser = TRUE; }
    PARAMETRIZE { innate = ABILITY_HOBBLE; statId = STAT_SPEED; targetsUser = FALSE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHED_SKIN); Innates(innate); }
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(opponent, innate);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, targetsUser ? opponent : player);
    } THEN {
        if (targetsUser)
            EXPECT_EQ(opponent->statStages[statId], DEFAULT_STAT_STAGE + 1);
        else
            EXPECT_EQ(player->statStages[statId], DEFAULT_STAT_STAGE - 1);
    }
}
#endif
