#include "global.h"
#include "achievements.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_arena.h"
#include "battle_environment.h"
#include "battle_pyramid.h"
#include "battle_util.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_setup.h"
#include "battle_z_move.h"
#include "battle_gimmick.h"
#include "battle_hold_effects.h"
#include "generational_changes.h"
#include "party_menu.h"
#include "pokemon.h"
#include "international_string_util.h"
#include "item.h"
#include "util.h"
#include "battle_scripts.h"
#include "random.h"
#include "text.h"
#include "safari_zone.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "test_runner.h"
#include "trig.h"
#include "trainer_slide.h"
#include "window.h"
#include "battle_message.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "event_data.h"
#include "link.h"
#include "malloc.h"
#include "berry.h"
#include "pokedex.h"
#include "mail.h"
#include "field_weather.h"
#include "constants/abilities.h"
#include "constants/battle_anim.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_string_ids.h"
#include "constants/items.h"
#include "constants/item_effects.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/weather.h"
#include "constants/pokemon.h"

static bool32 TryRemoveScreens(enum BattlerId battler);
static bool32 IsUnnerveAbilityOnOpposingSide(enum BattlerId battler);
static u32 GetFlingPowerFromItemId(enum Item itemId);
static bool32 IsNonVolatileStatusBlocked(enum BattlerId battlerDef, enum Ability abilityDef, bool32 abilityAffected, const u8 *battleScript, enum ResultOption option);
static bool32 CanSleepDueToSleepClause(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum ResultOption option);
static bool32 IsOpposingSideEmpty(enum BattlerId battler);
static enum BattlerId GetOppositeSideShiftTarget(enum BattlerId battler);
static void ResetParadoxWeatherStat(enum BattlerId battler);
static void ResetParadoxTerrainStat(enum BattlerId battler);
static bool32 CanBattlerFormChange(enum BattlerId battler, enum FormChanges method);
static bool32 IsPowderMoveBlocked(struct BattleContext *ctx);
const u8 *AbsorbedByDrainHpAbility(enum BattlerId battlerDef);
const u8 *AbsorbedByStatIncreaseAbility(enum BattlerId battlerDef, enum Stat statId, u32 statAmount);
const u8 *AbsorbedByFlashFire(enum BattlerId battlerDef);

ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12(u32 percent);
ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12_Floored(u32 percent);

extern const u8 *const gBattlescriptsForRunningByItem[];
extern const u8 *const gBattlescriptsForUsingItem[];
extern const u8 *const gBattlescriptsForSafariActions[];

enum Type GetAteAbilityType(enum Ability ability)
{
    switch (ability)
    {
    case ABILITY_FIGHTING_ATE:
        return TYPE_FIGHTING;
    case ABILITY_AERILATE:
        return TYPE_FLYING;
    case ABILITY_POISON_ATE:
        return TYPE_POISON;
    case ABILITY_GROUND_ATE:
        return TYPE_GROUND;
    case ABILITY_ROCK_ATE:
        return TYPE_ROCK;
    case ABILITY_BUG_ATE:
        return TYPE_BUG;
    case ABILITY_GHOST_ATE:
        return TYPE_GHOST;
    case ABILITY_STEEL_ATE:
        return TYPE_STEEL;
    case ABILITY_FIRE_ATE:
        return TYPE_FIRE;
    case ABILITY_WATER_ATE:
        return TYPE_WATER;
    case ABILITY_GRASS_ATE:
        return TYPE_GRASS;
    case ABILITY_GALVANIZE:
        return TYPE_ELECTRIC;
    case ABILITY_PSYCHIC_ATE:
        return TYPE_PSYCHIC;
    case ABILITY_REFRIGERATE:
        return TYPE_ICE;
    case ABILITY_DRAGON_ATE:
        return TYPE_DRAGON;
    case ABILITY_DRAGONIZE:
        return TYPE_DRAGON;
    case ABILITY_DARK_ATE:
        return TYPE_DARK;
    case ABILITY_PIXILATE:
        return TYPE_FAIRY;
    default:
        return TYPE_NONE;
    }
}

bool32 IsCustomAbilityDirectDamagingMove(enum Move move)
{
    return move != MOVE_NONE && !IsBattleMoveStatus(move);
}

bool32 BattlerHasEffectiveMajorStatus(enum BattlerId battler)
{
    if (gBattleMons[battler].status1 & STATUS1_ANY)
        return TRUE;

    return BattlerHasTrait(battler, ABILITY_HAUNTED);
}

enum Stat GetBattlerHighestNonHpStat(enum BattlerId battler)
{
    enum Stat bestStat = STAT_ATK;
    u16 bestValue = gBattleMons[battler].attack;

    if (gBattleMons[battler].defense > bestValue)
    {
        bestStat = STAT_DEF;
        bestValue = gBattleMons[battler].defense;
    }
    if (gBattleMons[battler].spAttack > bestValue)
    {
        bestStat = STAT_SPATK;
        bestValue = gBattleMons[battler].spAttack;
    }
    if (gBattleMons[battler].spDefense > bestValue)
    {
        bestStat = STAT_SPDEF;
        bestValue = gBattleMons[battler].spDefense;
    }
    if (gBattleMons[battler].speed > bestValue)
        bestStat = STAT_SPEED;

    return bestStat;
}

bool32 IsFiniteWeatherActive(void)
{
    return gBattleWeather != B_WEATHER_NONE && HasWeatherEffect() && gBattleStruct->weatherDuration > 0;
}

bool32 IsFiniteTerrainActive(void)
{
    return (gFieldStatuses & STATUS_FIELD_TERRAIN_ANY) && gFieldTimers.terrainTimer > 0;
}

bool32 IsTimeSpiralActiveOnField(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (IsBattlerAlive(battler) && BattlerHasTrait(battler, ABILITY_TIME_SPIRAL))
            return TRUE;
    }

    return FALSE;
}

static bool32 IsDialgaSpecies(u16 species)
{
    return species == SPECIES_DIALGA
        || species == SPECIES_DIALGA_ORIGIN
        || species == SPECIES_DIALGA_PRIMAL;
}

static bool32 IsPalkiaSpecies(u16 species)
{
    return species == SPECIES_PALKIA || species == SPECIES_PALKIA_ORIGIN;
}

bool32 SameSidePalkiaDialgaRiftActive(enum BattlerId battler)
{
    bool32 hasDialga = FALSE;
    bool32 hasPalkia = FALSE;
    bool32 hasRift = FALSE;

    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (!IsBattlerAlive(i) || !IsBattlerAlly(i, battler))
            continue;

        if (IsDialgaSpecies(gBattleMons[i].species))
            hasDialga = TRUE;
        if (IsPalkiaSpecies(gBattleMons[i].species))
            hasPalkia = TRUE;
        if (BattlerHasTrait(i, ABILITY_SPACETIME_RIFT))
            hasRift = TRUE;
    }

    return hasDialga && hasPalkia && hasRift;
}

static enum BattlerId GetSameSidePalkiaDialgaRiftOwner(enum BattlerId battler)
{
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerAlive(i) && IsBattlerAlly(i, battler) && BattlerHasTrait(i, ABILITY_SPACETIME_RIFT))
            return i;
    }

    return MAX_BATTLERS_COUNT;
}

static const u8 sPkblToEscapeFactor[][3] = {
    {
        [B_MSG_MON_CURIOUS]    = 0,
        [B_MSG_MON_ENTHRALLED] = 0,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 3,
        [B_MSG_MON_ENTHRALLED] = 5,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 2,
        [B_MSG_MON_ENTHRALLED] = 3,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 1,
        [B_MSG_MON_ENTHRALLED] = 2,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 1,
        [B_MSG_MON_ENTHRALLED] = 1,
        [B_MSG_MON_IGNORED]    = 0
    }
};
static const u8 sGoNearCounterToCatchFactor[] = {4, 3, 2, 1};
static const u8 sGoNearCounterToEscapeFactor[] = {4, 4, 4, 4};

struct BattleWeatherInfo
{
    u16 flag;
    u8 rock;
    u8 abilityStartMessage;
    u8 moveStartMessage;
    u8 endMessage;
    u8 continuesMessage;
    u8 animation;
};

static const struct BattleWeatherInfo sBattleWeatherInfo[BATTLE_WEATHER_COUNT] = {
    [BATTLE_WEATHER_RAIN] =
    {
        .flag = B_WEATHER_RAIN_NORMAL,
        .rock = HOLD_EFFECT_DAMP_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DRIZZLE,
        .moveStartMessage = B_MSG_STARTED_RAIN,
        .endMessage = B_MSG_WEATHER_END_RAIN,
        .continuesMessage = B_MSG_WEATHER_TURN_RAIN,
        .animation = B_ANIM_RAIN_CONTINUES,
    },

    [BATTLE_WEATHER_RAIN_PRIMAL] =
    {
        .flag = B_WEATHER_RAIN_PRIMAL,
        .rock = HOLD_EFFECT_DAMP_ROCK,
        .abilityStartMessage = B_MSG_STARTED_PRIMORDIAL_SEA,
        .moveStartMessage = B_MSG_STARTED_RAIN, // Placeholder
        .endMessage = B_MSG_WEATHER_END_RAIN,
        .continuesMessage = B_MSG_WEATHER_TURN_RAIN,
        .animation = B_ANIM_RAIN_CONTINUES,
    },

    [BATTLE_WEATHER_RAIN_DOWNPOUR] =
    {
        .flag = B_WEATHER_RAIN_NORMAL,
        .rock = HOLD_EFFECT_DAMP_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DRIZZLE,
        .moveStartMessage = B_MSG_STARTED_RAIN,
        .endMessage = B_MSG_WEATHER_END_RAIN,
        .continuesMessage = B_MSG_WEATHER_TURN_DOWNPOUR,
        .animation = B_ANIM_RAIN_CONTINUES,
    },

    [BATTLE_WEATHER_SUN] =
    {
        .flag = B_WEATHER_SUN_NORMAL,
        .rock = HOLD_EFFECT_HEAT_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DROUGHT,
        .moveStartMessage = B_MSG_STARTED_SUNLIGHT,
        .endMessage = B_MSG_WEATHER_END_SUN,
        .continuesMessage = B_MSG_WEATHER_TURN_SUN,
        .animation = B_ANIM_SUN_CONTINUES,
    },

    [BATTLE_WEATHER_SUN_PRIMAL] =
    {
        .flag = B_WEATHER_SUN_PRIMAL,
        .rock = HOLD_EFFECT_HEAT_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DESOLATE_LAND,
        .moveStartMessage = B_MSG_STARTED_SUNLIGHT, // Placeholder
        .endMessage = B_MSG_WEATHER_END_SUN,
        .continuesMessage = B_MSG_WEATHER_TURN_SUN,
        .animation = B_ANIM_SUN_CONTINUES,
    },

    [BATTLE_WEATHER_SANDSTORM] =
    {
        .flag = B_WEATHER_SANDSTORM,
        .rock = HOLD_EFFECT_SMOOTH_ROCK,
        .abilityStartMessage = B_MSG_STARTED_SAND_STREAM,
        .moveStartMessage = B_MSG_STARTED_SANDSTORM,
        .endMessage = B_MSG_WEATHER_END_SANDSTORM,
        .continuesMessage = B_MSG_WEATHER_TURN_SANDSTORM,
        .animation = B_ANIM_SANDSTORM_CONTINUES,
    },

    [BATTLE_WEATHER_HAIL] =
    {
        .flag = B_WEATHER_HAIL,
        .rock = HOLD_EFFECT_ICY_ROCK,
        .abilityStartMessage = B_MSG_STARTED_HAIL_WARNING,
        .moveStartMessage = B_MSG_STARTED_HAIL,
        .endMessage = B_MSG_WEATHER_END_HAIL,
        .continuesMessage = B_MSG_WEATHER_TURN_HAIL,
        .animation = B_ANIM_HAIL_CONTINUES,
    },

    [BATTLE_WEATHER_SNOW] =
    {
        .flag = B_WEATHER_SNOW,
        .rock = HOLD_EFFECT_ICY_ROCK,
        .abilityStartMessage = B_MSG_STARTED_SNOW_WARNING,
        .moveStartMessage = B_MSG_STARTED_SNOW,
        .endMessage = B_MSG_WEATHER_END_SNOW,
        .continuesMessage = B_MSG_WEATHER_TURN_SNOW,
        .animation = B_ANIM_SNOW_CONTINUES,
    },

    [BATTLE_WEATHER_FOG] =
    {
        .flag = B_WEATHER_FOG,
        .rock = HOLD_EFFECT_NONE,
        .abilityStartMessage = B_MSG_STARTED_DRIZZLE, // Placeholder
        .moveStartMessage = B_MSG_STARTED_RAIN, // Placeholder
        .endMessage = B_MSG_WEATHER_END_FOG,
        .continuesMessage = B_MSG_WEATHER_TURN_FOG,
        .animation = B_ANIM_FOG_CONTINUES,
    },

    [BATTLE_WEATHER_STRONG_WINDS] =
    {
        .flag = B_WEATHER_STRONG_WINDS,
        .rock = HOLD_EFFECT_NONE,
        .abilityStartMessage = B_MSG_STARTED_STRONG_WINDS,
        .moveStartMessage = B_MSG_STARTED_RAIN, // Placeholder
        .endMessage = B_MSG_WEATHER_END_STRONG_WINDS,
        .continuesMessage = B_MSG_WEATHER_TURN_STRONG_WINDS,
        .animation = B_ANIM_STRONG_WINDS,
    },

    [BATTLE_WEATHER_TWILIGHT] =
    {
        .flag = B_WEATHER_TWILIGHT,
        .rock = HOLD_EFFECT_NONE,
        .abilityStartMessage = B_MSG_STARTED_TWILIGHT,
        .moveStartMessage = B_MSG_STARTED_TWILIGHT,
        .endMessage = B_MSG_WEATHER_END_TWILIGHT,
        .continuesMessage = B_MSG_WEATHER_TURN_TWILIGHT,
        .animation = B_ANIM_FOG_CONTINUES,
    },
};

u32 GetCurrentBattleWeather(void)
{
    u32 currBattleWeather = 0xFF;

    for (u32 weather = 0; weather < ARRAY_COUNT(sBattleWeatherInfo); weather++)
    {
        if (gBattleWeather & sBattleWeatherInfo[weather].flag)
        {
            currBattleWeather = weather;
            break;
        }
    }

    return currBattleWeather;
}

bool32 EndOrContinueWeather(void)
{
    u32 currBattleWeather = GetCurrentBattleWeather();

    if (currBattleWeather == 0xFF)
        return FALSE;

    bool32 finiteWeather = gBattleStruct->weatherDuration > 0;

    if (finiteWeather)
    {
        gBattleStruct->weatherDuration--;
        if (gBattleStruct->weatherDuration > 0 && IsTimeSpiralActiveOnField())
            gBattleStruct->weatherDuration--;
    }

    if (finiteWeather && gBattleStruct->weatherDuration == 0)
    {
        gBattleWeather = B_WEATHER_NONE;
        for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
        {
            gBattleMons[battler].volatiles.weatherAbilityDone = FALSE;
            gBattleMons[battler].volatiles.transformWeatherAbilityDone = FALSE;
            ResetParadoxWeatherStat(battler);
        }
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[currBattleWeather].endMessage;
        BattleScriptExecute(BattleScript_WeatherFaded);
        return TRUE;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[currBattleWeather].continuesMessage;
        gBattleScripting.animArg1 = sBattleWeatherInfo[currBattleWeather].animation;
        BattleScriptExecute(gSaveBlock2Ptr->optionsFastWeather ? BattleScript_FastWeatherContinues : BattleScript_WeatherContinues);
        return TRUE;
    }

    return FALSE;
}

static inline u32 CommonSwitchInAbilities(u32 battler, u16 trait, u8 traitDone, const u8 *BS_ptr)
{
    gSpecialStatuses[battler].switchInTraitDone[traitDone - 1] = TRUE;
    PushTraitStack(battler, trait);
    BattleScriptCall(BS_ptr);
    return 1; // simulate effect ++
}

static u32 TrySwitchInStatRaiseAbility(enum BattlerId battler, enum Ability *battlerTraits, enum Ability ability, enum Stat statId, bool32 shouldAbilityTrigger)
{
    u32 traitCheck = SearchTraits(battlerTraits, ability);

    if (traitCheck
     && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
     && shouldAbilityTrigger
     && CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
    {
        SET_STATCHANGER(statId, 1, FALSE);
        return CommonSwitchInAbilities(battler, ability, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInGeneric);
    }

    return 0;
}

// Gen5+
static u32 CalcBeatUpPower(void)
{
    u32 species = gBattleStruct->beatUpSpecies[gBattleStruct->beatUpSlot++];
    // FIXME: Why call CalcBeatUpPower when 'beatUpSlot' is OOB?
    if (species == 0xFFFF)
        return 0;
    return (GetSpeciesBaseAttack(species) / 10) + 5;
}

// Gen 3/4
static s32 CalcBeatUpDamage(struct BattleContext *ctx)
{
    u32 partyIndex = gBattleStruct->beatUpSpecies[gBattleStruct->beatUpSlot++];
    struct Pokemon *party = GetBattlerParty(ctx->battlerAtk);
    u32 species = GetMonData(&party[partyIndex], MON_DATA_SPECIES);
    u32 levelFactor = GetMonData(&party[partyIndex], MON_DATA_LEVEL) * 2 / 5 + 2;
    s32 dmg = GetSpeciesBaseAttack(species);

    dmg *= GetMovePower(ctx->move);
    dmg *= levelFactor;
    dmg /= GetSpeciesBaseDefense(gBattleMons[ctx->battlerDef].species);
    dmg = (dmg / 50) + 2;

    if (gProtectStructs[ctx->battlerAtk].helpingHand)
        dmg = dmg * 15 / 10;
    if (ctx->isCrit)
        dmg *= 2;

    return dmg;
}

enum DamageCategory GetReflectDamageMoveDamageCategory(enum BattlerId battler, enum Move move)
{
    u32 damageCategories = GetMoveReflectDamage_DamageCategories(move);

    if (damageCategories == 1u << DAMAGE_CATEGORY_PHYSICAL) // Counter
        return DAMAGE_CATEGORY_PHYSICAL;
    if (damageCategories == 1u << DAMAGE_CATEGORY_SPECIAL) // Mirror Coat
        return DAMAGE_CATEGORY_SPECIAL;

    // Metal Burst / Comeuppance
    if (gProtectStructs[battler].lastHitBySpecialMove)
        return DAMAGE_CATEGORY_SPECIAL;
    else
        return DAMAGE_CATEGORY_PHYSICAL;
}

static bool32 ShouldTeraShellDistortTypeMatchups(enum Move move, enum BattlerId battlerDef)
{
    if (!gSpecialStatuses[battlerDef].distortedTypeMatchups
     && gBattleMons[battlerDef].species == SPECIES_TERAPAGOS_TERASTAL
     && gBattleMons[battlerDef].hp == gBattleMons[battlerDef].maxHP
     && !IsBattleMoveStatus(move)
     && BattlerHasTrait(battlerDef, ABILITY_TERA_SHELL))
        return TRUE;

    return FALSE;
}

bool32 IsUnnerveBlocked(enum BattlerId battler, enum Item itemId)
{
    if (GetItemPocket(itemId) != POCKET_BERRIES)
        return FALSE;

    if (gBattleScripting.overrideBerryRequirements > 0) // Berries that aren't eaten naturally ignore unnerve
        return FALSE;

    if (IsUnnerveAbilityOnOpposingSide(battler))
        return TRUE;

    return FALSE;
}

static bool32 IsUnnerveAbilityOnOpposingSide(enum BattlerId battler)
{
    for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
    {
        if (battler == battlerDef || IsBattlerAlly(battler, battlerDef))
            continue;

        if (!IsBattlerAlive(battlerDef))
            continue;

        if (BattlerHasTrait(battlerDef, ABILITY_UNNERVE)
         || BattlerHasTrait(battlerDef, ABILITY_AS_ONE_ICE_RIDER)
         || BattlerHasTrait(battlerDef, ABILITY_AS_ONE_SHADOW_RIDER))
            return TRUE;
    }

    return FALSE;
}

// Functions
void HandleAction_UseMove(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (gAbsentBattlerFlags & 1u << gBattlerAttacker
     || gBattleStruct->battlerState[gBattlerAttacker].commandingDondozo
     || !IsBattlerAlive(gBattlerAttacker))
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }

    gCurrMovePos = gChosenMovePos = gBattleStruct->chosenMovePositions[gBattlerAttacker];

    // choose move
    if (gProtectStructs[gBattlerAttacker].noValidMoves)
    {
        gProtectStructs[gBattlerAttacker].noValidMoves = FALSE;
        gCurrentMove = gChosenMove = MOVE_STRUGGLE;
        gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(MOVE_STRUGGLE, TARGET_NONE);
    }
    else if (gBattleMons[gBattlerAttacker].volatiles.multipleTurns || gBattleMons[gBattlerAttacker].volatiles.rechargeTimer > 0)
    {
        gCurrentMove = gChosenMove = gLockedMoves[gBattlerAttacker];
    }
    // encore forces you to use the same move
    else if (GetActiveGimmick(gBattlerAttacker) != GIMMICK_Z_MOVE && gBattleMons[gBattlerAttacker].volatiles.encoredMove != MOVE_NONE
             && gBattleMons[gBattlerAttacker].volatiles.encoredMove == gBattleMons[gBattlerAttacker].moves[gBattleMons[gBattlerAttacker].volatiles.encoredMovePos])
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].volatiles.encoredMove;
        gCurrMovePos = gChosenMovePos = gBattleMons[gBattlerAttacker].volatiles.encoredMovePos;
        if (GetConfig(B_ENCORE_TARGET) < GEN_5)
            gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(gCurrentMove, TARGET_NONE);
    }
    // check if the encored move wasn't overwritten
    else if (GetActiveGimmick(gBattlerAttacker) != GIMMICK_Z_MOVE && gBattleMons[gBattlerAttacker].volatiles.encoredMove != MOVE_NONE
          && gBattleMons[gBattlerAttacker].volatiles.encoredMove != gBattleMons[gBattlerAttacker].moves[gBattleMons[gBattlerAttacker].volatiles.encoredMovePos])
    {
        gCurrMovePos = gChosenMovePos = gBattleMons[gBattlerAttacker].volatiles.encoredMovePos;
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        gBattleMons[gBattlerAttacker].volatiles.encoredMove = MOVE_NONE;
        gBattleMons[gBattlerAttacker].volatiles.encoredMovePos = 0;
        gBattleMons[gBattlerAttacker].volatiles.encoreTimer = 0;
        gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(gCurrentMove, TARGET_NONE);
    }
    else if (gBattleMons[gBattlerAttacker].moves[gCurrMovePos] != gChosenMoveByBattler[gBattlerAttacker])
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(gCurrentMove, TARGET_NONE);
    }
    else
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
    }

    if (IsBattlerAlive(gBattlerAttacker))
    {
        if (IsOnPlayerSide(gBattlerAttacker))
            gBattleResults.lastUsedMovePlayer = gCurrentMove;
        else
            gBattleResults.lastUsedMoveOpponent = gCurrentMove;
    }

    // Set dynamic move type.
    SetTypeBeforeUsingMove(gChosenMove, gBattlerAttacker);

    // check Z-Move used
    if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_Z_MOVE && !IsBattleMoveStatus(gCurrentMove) && !IsZMove(gCurrentMove))
    {
        gBattleStruct->categoryOverride = GetMoveCategory(gCurrentMove);
        gCurrentMove = gChosenMove = GetUsableZMove(gBattlerAttacker, gCurrentMove);
    }
    // check Max Move used
    else if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_DYNAMAX)
    {
        gBattleStruct->categoryOverride = GetMoveCategory(gCurrentMove);
        gCurrentMove = gChosenMove = GetMaxMove(gBattlerAttacker, gCurrentMove);
    }

    gBattleStruct->eventState.atkCanceler = 0;
    ClearDamageCalcResults();
    gMultiHitCounter = 0;
    gBattleCommunication[MISS_TYPE] = 0;
    gBattlerTarget = gBattleStruct->moveTarget[gBattlerAttacker];

    if (gBattleTypeFlags & BATTLE_TYPE_PALACE && gProtectStructs[gBattlerAttacker].palaceUnableToUseMove)
    {
        // Battle Palace, select battle script for failure to use move
        if (!IsBattlerAlive(gBattlerAttacker))
        {
            gCurrentActionFuncId = B_ACTION_FINISHED;
            return;
        }
        else if (gPalaceSelectionBattleScripts[gBattlerAttacker] != NULL)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_INCAPABLE_OF_POWER;
            gBattlescriptCurrInstr = gPalaceSelectionBattleScripts[gBattlerAttacker];
            gPalaceSelectionBattleScripts[gBattlerAttacker] = NULL;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_INCAPABLE_OF_POWER;
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
        }
    }
    else
    {
        gBattlescriptCurrInstr = GetMoveBattleScript(gCurrentMove);
    }

    if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
        BattleArena_AddMindPoints(gBattlerAttacker);

    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        gBattleStruct->battlerState[battler].wasAboveHalfHp = gBattleMons[battler].hp > gBattleMons[battler].maxHP / 2;
        gBattleMons[battler].volatiles.activateDancer = FALSE;
    }

    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_Switch(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];

    // if switching to a mon that is already on field, cancel switch
    if (!(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(gBattlerAttacker)))
     && IsBattlerAlive(BATTLE_PARTNER(gBattlerAttacker))
     && gBattlerPartyIndexes[BATTLE_PARTNER(gBattlerAttacker)] == gBattleStruct->monToSwitchIntoId[gBattlerAttacker])
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gActionSelectionCursor[gBattlerAttacker] = 0;
    gMoveSelectionCursor[gBattlerAttacker] = 0;

    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattleStruct->battlerPartyIndexes[gBattlerAttacker]);

    gBattleScripting.battler = gBattlerAttacker;
    gBattlescriptCurrInstr = BattleScript_ActionSwitch;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;

    if (gBattleResults.playerSwitchesCounter < 255)
        gBattleResults.playerSwitchesCounter++;

    TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_SWITCH_OUT);
}

void HandleAction_UseItem(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    ClearVariousBattlerFlags(gBattlerAttacker);

    gLastUsedItem = gBattleResources->bufferB[gBattlerAttacker][1] | (gBattleResources->bufferB[gBattlerAttacker][2] << 8);
    if (X_ITEM_FRIENDSHIP_INCREASE > 0
        && GetItemEffectType(gLastUsedItem) == ITEM_EFFECT_X_ITEM
        && !ShouldSkipFriendshipChange())
        UpdateFriendshipFromXItem(gBattlerAttacker);

    gBattlescriptCurrInstr = gBattlescriptsForUsingItem[GetItemBattleUsage(gLastUsedItem) - 1];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

bool32 TryRunFromBattle(enum BattlerId battler)
{
    bool32 effect = FALSE;
    u8 pyramidMultiplier;
    u8 speedVar;

    // If this flag is set, running will never be successful under any other circumstances.
    if (!(gBattleTypeFlags & BATTLE_TYPE_BOSS) && FlagGet(B_FLAG_NO_RUNNING))
        return effect;

    gPotentialItemEffectBattler = battler;

    // Boss battles use Run as an explicit forfeit. Once confirmed, it must not
    // be affected by held items, types, abilities, speed, or trapping effects.
    if (gBattleTypeFlags & BATTLE_TYPE_BOSS)
        effect++;
    else if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_CAN_ALWAYS_RUN, TRUE))
    {
        gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_CAN_ALWAYS_RUN, TRUE);
        gProtectStructs[battler].fleeType = FLEE_ITEM;
        effect++;
    }
    else if (GetConfig(B_GHOSTS_ESCAPE) >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
    {
        effect++;
    }
    else if (BattlerHasTrait(battler, ABILITY_RUN_AWAY))
    {
        if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        {
            gBattleStruct->runTries++;
            pyramidMultiplier = GetPyramidRunMultiplier();
            speedVar = (gBattleMons[battler].speed * pyramidMultiplier) / (gBattleMons[BATTLE_OPPOSITE(battler)].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
            {
                gLastUsedAbility = gDisplayAbility = ABILITY_RUN_AWAY;
                PushTraitStack(battler, ABILITY_RUN_AWAY);
                gProtectStructs[battler].fleeType = FLEE_ABILITY;
                effect++;
            }
        }
        else
        {
            gLastUsedAbility = gDisplayAbility = ABILITY_RUN_AWAY;
            PushTraitStack(battler, ABILITY_RUN_AWAY);
            gProtectStructs[battler].fleeType = FLEE_ABILITY;
            effect++;
        }
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_TRAINER_HILL) && gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        effect++;
    }
    else if (CanPlayerForfeitNormalTrainerBattle())
    {
        effect++;
    }
    else
    {
        enum BattlerId runningFromBattler = BATTLE_OPPOSITE(battler);
        if (!IsBattlerAlive(runningFromBattler))
            runningFromBattler |= BIT_FLANK;

        if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        {
            pyramidMultiplier = GetPyramidRunMultiplier();
            speedVar = (gBattleMons[battler].speed * pyramidMultiplier) / (gBattleMons[runningFromBattler].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
                effect++;
        }
        else if (gBattleMons[battler].speed < gBattleMons[runningFromBattler].speed)
        {
            speedVar = (gBattleMons[battler].speed * 128) / (gBattleMons[runningFromBattler].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
                effect++;
        }
        else // same speed or faster
        {
            effect++;
        }

        gBattleStruct->runTries++;
    }

    if (effect != 0)
    {
        gCurrentTurnActionNumber = gBattlersCount;
        gBattleOutcome = B_OUTCOME_RAN;
    }

    return effect;
}

void HandleAction_Run(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
    {
        gCurrentTurnActionNumber = gBattlersCount;

        for (enum BattlerId i = 0; i < gBattlersCount; i++)
        {
            if (IsOnPlayerSide(i))
            {
                if (gChosenActionByBattler[i] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_LOST;
            }
            else
            {
                if (gChosenActionByBattler[i] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_WON;
            }
        }

        gBattleOutcome |= B_OUTCOME_LINK_BATTLE_RAN;
        gSaveBlock2Ptr->frontier.disableRecordBattle = TRUE;
    }
    else
    {
        if (IsOnPlayerSide(gBattlerAttacker))
        {
            if (!TryRunFromBattle(gBattlerAttacker)) // failed to run away
            {
                ClearVariousBattlerFlags(gBattlerAttacker);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CANT_ESCAPE_2;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
        }
        else
        {
            if (!BattlerHasHeldItemEffect(gBattlerAttacker, HOLD_EFFECT_CAN_ALWAYS_RUN, TRUE)
             && !BattlerHasTrait(gBattlerAttacker, ABILITY_RUN_AWAY)
             && !CanBattlerEscape(gBattlerAttacker))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_ATTACKER_CANT_ESCAPE;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
            else
            {
                gCurrentTurnActionNumber = gBattlersCount;
                gBattleOutcome = B_OUTCOME_MON_FLED;
            }
        }
    }
}

#define safariBaitThrowCounter safariPkblThrowCounter
#define safariRockThrowCounter safariGoNearCounter

void HandleAction_WatchesCarefully(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[0];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_SafariZoneBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gNumSafariBalls--;
    gLastUsedItem = ITEM_SAFARI_BALL;
    gBattlescriptCurrInstr = BattleScript_SafariBallThrow;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_ThrowBall(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gLastUsedItem = gBallToDisplay;
    if (!GetItemImportance(gLastUsedItem))
        RemoveBagItem(gLastUsedItem, 1);
    gBattlescriptCurrInstr = BattleScript_BallThrow;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_ThrowPokeblock(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
        // throw pokeblock
        gBattleCommunication[MULTISTRING_CHOOSER] = gBattleResources->bufferB[gBattlerAttacker][1] - 1;
        gLastUsedItem = gBattleResources->bufferB[gBattlerAttacker][2];

        if (gBattleResults.pokeblockThrows < 255)
            gBattleResults.pokeblockThrows++;
        if (gBattleStruct->safariPkblThrowCounter < 3)
            gBattleStruct->safariPkblThrowCounter++;
        if (gBattleStruct->safariEscapeFactor > 1)
        {
            // BUG: safariEscapeFactor can become 0 below. This causes the pokeblock throw glitch.
            #ifdef BUGFIX
            if (gBattleStruct->safariEscapeFactor <= sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]])
            #else
            if (gBattleStruct->safariEscapeFactor < sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]])
            #endif
                gBattleStruct->safariEscapeFactor = 1;
            else
                gBattleStruct->safariEscapeFactor -= sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]];
        }

        gBattlescriptCurrInstr = gBattlescriptsForSafariActions[2];
    

    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_GoNear(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
        // go near
        gBattleStruct->safariCatchFactor += sGoNearCounterToCatchFactor[gBattleStruct->safariGoNearCounter];
        if (gBattleStruct->safariCatchFactor > 20)
            gBattleStruct->safariCatchFactor = 20;

        gBattleStruct->safariEscapeFactor += sGoNearCounterToEscapeFactor[gBattleStruct->safariGoNearCounter];
        if (gBattleStruct->safariEscapeFactor > 20)
            gBattleStruct->safariEscapeFactor = 20;

        if (gBattleStruct->safariGoNearCounter < 3)
        {
            gBattleStruct->safariGoNearCounter++;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CREPT_CLOSER;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CANT_GET_CLOSER;
        }
        gBattlescriptCurrInstr = gBattlescriptsForSafariActions[1];

    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

#undef safariBaitThrowCounter
#undef safariRockThrowCounter

void HandleAction_SafariZoneRun(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    PlaySE(SE_FLEE);
    gCurrentTurnActionNumber = gBattlersCount;
    gBattleOutcome = B_OUTCOME_RAN;
}

void HandleAction_WallyBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;

    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])

    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[3];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
    gActionsByTurnOrder[1] = B_ACTION_FINISHED;
}

void HandleAction_TryFinish(void)
{
    if (!HandleFaintedMonActions())
    {
        gBattleStruct->eventState.faintedAction = 0;
        gCurrentActionFuncId = B_ACTION_FINISHED;
    }
}

void HandleAction_NothingIsFainted(void)
{
    gCurrentTurnActionNumber++;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;
}

void HandleAction_ActionFinished(void)
{
    u32 i, j;
    bool32 afterYouActive = gSpecialStatuses[gBattlerByTurnOrder[gCurrentTurnActionNumber + 1]].afterYou;
    gBattleStruct->monToSwitchIntoId[gBattlerByTurnOrder[gCurrentTurnActionNumber]] = gSelectedMonPartyId = PARTY_SIZE;
    gCurrentTurnActionNumber++;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    memset(&gSpecialStatuses, 0, sizeof(gSpecialStatuses));

    gCurrentMove = MOVE_NONE;
    ClearDamageCalcResults(); // Relies on gCurrentMove
    gBattleScripting.animTurn = 0;
    gBattleScripting.animTargetsHit = 0;
    gBattleStruct->dynamicMoveType = 0;
    gBattleStruct->bouncedMoveIsUsed = FALSE;
    gBattleStruct->snatchedMoveIsUsed = FALSE;
    gBattleScripting.moveendState = 0;
    gBattleCommunication[3] = 0;
    gBattleCommunication[4] = 0;
    gBattleResources->battleScriptsStack->size = 0;
    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;

    if (GetConfig(B_RECALC_TURN_AFTER_ACTIONS) >= GEN_8 && !afterYouActive && !gBattleStruct->pledgeMove && !IsPursuitTargetSet())
    {
        // i starts at `gCurrentTurnActionNumber` because we don't want to recalculate turn order for mon that have already
        // taken action. It's been previously increased, which we want in order to not recalculate the turn of the mon that just finished its action

        struct BattleCalcValues calcValues = {0};

        for (i = gCurrentTurnActionNumber; i < gBattlersCount - 1; i++)
        {
            for (j = i + 1; j < gBattlersCount; j++)
            {
                calcValues.battlerAtk = gBattlerByTurnOrder[i];
                calcValues.battlerDef = gBattlerByTurnOrder[j];

                if (gProtectStructs[calcValues.battlerAtk].quash || gProtectStructs[calcValues.battlerDef].quash
                    || gProtectStructs[calcValues.battlerAtk].shellTrap || gProtectStructs[calcValues.battlerDef].shellTrap)
                    continue;

                // We recalculate order only for action of the same priority. If any action other than switch/move has been taken, they should
                // have been executed before. The only recalculation needed is for moves/switch. Mega evolution is handled in src/battle_main.c/TryChangeOrder
                if ((gActionsByTurnOrder[i] == B_ACTION_USE_MOVE && gActionsByTurnOrder[j] == B_ACTION_USE_MOVE))
                {
                    if (GetWhichBattlerFaster(&calcValues, FALSE) == -1)
                        SwapTurnOrder(i, j);
                }
                else if ((gActionsByTurnOrder[i] == B_ACTION_SWITCH && gActionsByTurnOrder[j] == B_ACTION_SWITCH))
                {
                    if (GetWhichBattlerFaster(&calcValues, TRUE) == -1) // If the actions chosen are switching, we recalc order but ignoring the moves
                        SwapTurnOrder(i, j);
                }
            }
        }
    }
}

// code

ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12(u32 percent)
{
    return (4096 * percent + 50) / 100;
}

ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12_Floored(u32 percent)
{
    return (4096 * percent) / 100;
}

static inline uq4_12_t PercentToUQ4_12AddOne(u32 percent)
{
    return uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(percent));
}

enum BattlerId GetBattlerForBattleScript(u8 caseId)
{
    enum BattlerId ret = 0;
    switch (caseId)
    {
    case BS_TARGET:
        ret = gBattlerTarget;
        break;
    case BS_ATTACKER:
        ret = gBattlerAttacker;
        break;
    case BS_ATTACKER_PARTNER:
        ret = BATTLE_PARTNER(gBattlerAttacker);
        break;
    case BS_EFFECT_BATTLER:
        ret = gEffectBattler;
        break;
    case BS_BATTLER_0:
        ret = 0;
        break;
    case BS_SCRIPTING:
        ret = gBattleScripting.battler;
        break;
    case BS_FAINTED:
        ret = gBattlerFainted;
        break;
    case BS_FAINTED_MULTIPLE_1:
        ret = gBattlerFainted;
        break;
    case BS_FAINTED_MULTIPLE_2:
        ret = BATTLE_PARTNER(gBattlerFainted);
        break;
    case BS_ATTACKER_WITH_PARTNER:
    case BS_ATTACKER_SIDE:
    case BS_TARGET_SIDE:
    case BS_PLAYER1:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        break;
    case BS_OPPONENT1:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        break;
    case BS_PLAYER2:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        break;
    case BS_OPPONENT2:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        break;
    case BS_ABILITY_BATTLER:
        ret = gBattlerAbility;
        break;
    case BS_SCRIPTING_PARTNER:
        ret = BATTLE_PARTNER(gBattleScripting.battler);
        break;
    }
    return ret;
}

static void UNUSED MarkAllBattlersForControllerExec(void)
{
    enum BattlerId i;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        for (i = 0; i < gBattlersCount; i++)
            MarkBattleControllerMessageOutboundOverLink(i);
    }
    else
    {
        for (i = 0; i < gBattlersCount; i++)
            MarkBattleControllerActiveOnLocal(i);
    }
}

bool32 IsBattlerMarkedForControllerExec(enum BattlerId battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        return IsBattleControllerMessageSynchronizedOverLink(battler);
    else
        return IsBattleControllerActiveOnLocal(battler);
}

bool32 CanRunBattleScriptCommands(void)
{
    enum BattlerId battler;

    if (gBattleControllerExecFlags == 0)
        return TRUE;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        return FALSE;

    for (battler = 0; battler < gBattlersCount; battler++)
    {
        if (!IsBattlerMarkedForControllerExec(battler))
            continue;

        if (gBattleResources->bufferA[battler][0] != CONTROLLER_BATTLEANIMATION
         || gBattleResources->bufferA[battler][1] != B_ANIM_STATS_CHANGE)
            return FALSE;
    }

    return TRUE;
}

void MarkBattlerForControllerExec(enum BattlerId battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        MarkBattleControllerMessageOutboundOverLink(battler);
    else
        MarkBattleControllerActiveOnLocal(battler);
}

void MarkBattlerReceivedLinkData(enum BattlerId battler)
{
    s32 i;

    for (i = 0; i < GetLinkPlayerCount(); i++)
        MarkBattleControllerActiveForPlayer(battler, i);

    MarkBattleControllerMessageSynchronizedOverLink(battler);
}

const u8 *CheckSkyDropState(enum BattlerId battler, enum SkyDropState skyDropState)
{
    const u8 *result = NULL;

    u8 otherSkyDropper = gBattleStruct->skyDropTargets[battler];
    gBattleMons[battler].volatiles.semiInvulnerable = STATE_NONE;

    // Makes both attacker and target's sprites visible
    gSprites[gBattlerSpriteIds[battler]].invisible = FALSE;
    gSprites[gBattlerSpriteIds[otherSkyDropper]].invisible = FALSE;

    // If target was sky dropped in the middle of Outrage/Thrash/Petal Dance,
    // confuse them upon release and display "confused by fatigue" message & animation.
    // Don't do this if this CancelMultiTurnMoves is caused by falling asleep via Yawn.
    if (gBattleMons[otherSkyDropper].volatiles.rampageTurns && skyDropState != SKY_DROP_STATUS_YAWN)
    {
        gBattleMons[otherSkyDropper].volatiles.rampageTurns = 0;

        // If the target can be confused, confuse them.
        // Don't use CanBeConfused, can cause issues in edge cases.
        if (!(gBattleMons[otherSkyDropper].volatiles.confusionTurns > 0
            || IsAbilityAndRecord(otherSkyDropper, ABILITY_OWN_TEMPO)
            || BattlerHasTrait(otherSkyDropper, ABILITY_UNSTOPPABLE)
            || IsMistyTerrainAffected(otherSkyDropper, gFieldStatuses)))
        {
            gBattleMons[otherSkyDropper].volatiles.confusionTurns = RandomUniform(RNG_CONFUSION_TURNS, 2, B_CONFUSION_TURNS); // 2-5 turns
            if (skyDropState == SKY_DROP_ATTACKCANCELER_CHECK)
            {
                gBattleStruct->skyDropTargets[battler] = SKY_DROP_RELEASED_TARGET;
            }
            else if (skyDropState == SKY_DROP_GRAVITY_ON_AIRBORNE)
            {
                // Reapplying STATE_SKY_DROPPED allows for avoiding unecessary messages when Gravity is applied to the target.
                gBattleStruct->skyDropTargets[battler] = SKY_DROP_RELEASED_TARGET;
                gBattleMons[otherSkyDropper].volatiles.semiInvulnerable = STATE_SKY_DROP;
            }
            else if (skyDropState == SKY_DROP_CANCEL_MULTI_TURN_MOVES)
            {
                gBattlerAttacker = otherSkyDropper;
                result = BattleScript_ThrashConfuses;
            }
            else if (skyDropState == SKY_DROP_STATUS_FREEZE_SLEEP)
            {
                gBattlerAttacker = otherSkyDropper;
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                result = BattleScript_ThrashConfuses;
            }
        }
    }

    // Clear skyDropTargets data, unless this CancelMultiTurnMoves is caused by Yawn, attackcanceler, or VARIOUS_GRAVITY_ON_AIRBORNE_MONS
    if (!(gBattleMons[otherSkyDropper].volatiles.rampageTurns) && gBattleStruct->skyDropTargets[battler] < 4)
    {
        gBattleStruct->skyDropTargets[battler] = SKY_DROP_NO_TARGET;
        gBattleStruct->skyDropTargets[otherSkyDropper] = SKY_DROP_NO_TARGET;
    }

    return result;
}

const u8 *CancelMultiTurnMoves(enum BattlerId battler, enum SkyDropState skyDropState)
{
    const u8 *result = NULL;
    gBattleMons[battler].volatiles.uproarTurns = 0;
    gBattleMons[battler].volatiles.bideTurns = 0;

    if (B_RAMPAGE_CANCELLING < GEN_5)
    {
        gBattleMons[battler].volatiles.multipleTurns = 0;
        gBattleMons[battler].volatiles.rampageTurns = 0;
    }
    else if (!gBattleMons[battler].volatiles.rampageTurns
     || gBattleMons[battler].volatiles.rampageTurns > 1)
    {
        gBattleMons[battler].volatiles.multipleTurns = 0;
    }

    // Clear battler's semi-invulnerable bits if they are not held by Sky Drop.
    if (gBattleMons[battler].volatiles.semiInvulnerable != STATE_SKY_DROP)
        gBattleMons[battler].volatiles.semiInvulnerable = STATE_NONE;

    if (gBattleStruct->skyDropTargets[battler] != SKY_DROP_NO_TARGET && gBattleMons[battler].volatiles.semiInvulnerable != STATE_SKY_DROP)
        result = CheckSkyDropState(battler, skyDropState);

    gBattleMons[battler].volatiles.rolloutTimer = 0;
    gBattleMons[battler].volatiles.furyCutterCounter = 0;

    return result;
}


// Returns TRUE if no other battler after this one in turn order will use a move
bool32 IsLastMonToMove(enum BattlerId battler)
{
    u32 i;
    u32 battlerTurnOrderNum = GetBattlerTurnOrderNum(battler);

    if (battlerTurnOrderNum >= gBattlersCount - 1)
        return TRUE;

    for (i = battlerTurnOrderNum + 1; i < gBattlersCount; i++)
    {
        enum BattlerId otherBattler = gBattlerByTurnOrder[i];
        if (!IsBattlerAlive(otherBattler))
            continue;
        if (gActionsByTurnOrder[i] == B_ACTION_USE_MOVE)
            return FALSE;
    }
    return TRUE;
}

bool32 ShouldDefiantCompetitiveActivate(enum BattlerId battler)
{
    enum BattleSide side = GetBattlerSide(battler);
    if (!BattlerHasTrait(battler, ABILITY_DEFIANT) && !BattlerHasTrait(battler, ABILITY_COMPETITIVE))
        return FALSE;
    // if an ally dropped the stats (except for Sticky Web), don't activate
    if (IsBattlerAlly(gSpecialStatuses[battler].changedStatsBattlerId, battler) && !gBattleScripting.stickyWebStatDrop)
        return FALSE;

    if (GetConfig(B_DEFIANT_STICKY_WEB) >= GEN_9 || !gBattleScripting.stickyWebStatDrop)
        return TRUE;
    // only activate Defiant/Competitive if Web was setup by foe
    return gSideTimers[side].stickyWebBattlerSide != side;
}

void PrepareStringBattle(enum StringID stringId, enum BattlerId battler)
{
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(gBattlerTarget);
    bool32 hasContrary = (BattlerHasTrait(gBattlerTarget, ABILITY_CONTRARY));

    // Support for Contrary ability.
    // If a move attempted to raise stat - print "won't increase".
    // If a move attempted to lower stat - print "won't decrease".
    switch (stringId)
    {
    case STRINGID_ATTACKERSSTATROSE:
    case STRINGID_DEFENDERSSTATROSE:
    case STRINGID_STATSWONTINCREASE:
    case STRINGID_USINGITEMSTATOFPKMNROSE:
        if (gBattleScripting.statChanger & STAT_BUFF_NEGATIVE)
            stringId = gStatDownStringIds[gBattleCommunication[MULTISTRING_CHOOSER]];
        break;
    case STRINGID_ATTACKERSSTATFELL:
    case STRINGID_DEFENDERSSTATFELL:
    case STRINGID_STATSWONTDECREASE:
    case STRINGID_USINGITEMSTATOFPKMNFELL:
        if (!(gBattleScripting.statChanger & STAT_BUFF_NEGATIVE))
            stringId = gStatUpStringIds[gBattleCommunication[MULTISTRING_CHOOSER]];
        break;
    case STRINGID_STATSWONTINCREASE2:
        if (hasContrary)
            stringId = STRINGID_STATSWONTDECREASE2;
        break;
    case STRINGID_STATSWONTDECREASE2:
        if (hasContrary)
            stringId = STRINGID_STATSWONTINCREASE2;
        break;
    case STRINGID_STATSWONTINCREASECONTRARY2:
        if (hasContrary)
            stringId = STRINGID_STATSWONTDECREASECONTRARY2;
        break;
    case STRINGID_STATSWONTDECREASECONTRARY2:
        if (hasContrary)
            stringId = STRINGID_STATSWONTINCREASECONTRARY2;
        break;
    case STRINGID_PKMNCUTSATTACKWITH:
        if (GetConfig(B_UPDATED_INTIMIDATE) >= GEN_8
         && SearchTraits(battlerTraits, ABILITY_RATTLED)
         && CompareStat(gBattlerTarget, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gBattlerAbility = gBattlerTarget;
            PushTraitStack(gBattlerTarget, ABILITY_RATTLED);
            BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
            SET_STATCHANGER(STAT_SPEED, 1, FALSE);
        }
        break;
    case STRINGID_PKMNINTIMIDATECONTRARYRATTLED: // Special string for Intimidate + Contrary + Rattled.  Rattled should activate even if Attack is raised.
        stringId = STRINGID_DEFENDERSSTATROSE;
        if (GetConfig(B_UPDATED_INTIMIDATE) >= GEN_8
         && SearchTraits(battlerTraits, ABILITY_RATTLED)
         && CompareStat(gBattlerTarget, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gBattlerAbility = gBattlerTarget;
            BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
            PushTraitStack(gBattlerTarget, ABILITY_RATTLED);
            SET_STATCHANGER(STAT_SPEED, 1, FALSE);
        }
        break;
    case STRINGID_ITDOESNTAFFECT:
    case STRINGID_PKMNUNAFFECTED:
        TryInitializeTrainerSlideEnemyMonUnaffected(gBattlerTarget);
        break;
    default:
        break;
    }

    if (!hasContrary
     && (stringId == STRINGID_PKMNCUTSATTACKWITH || stringId == STRINGID_DEFENDERSSTATFELL)
     && ShouldDefiantCompetitiveActivate(gBattlerTarget))
    {
        gBattlerAbility = gBattlerTarget;
        BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
        if (SearchTraits(battlerTraits, ABILITY_DEFIANT))
        {
            PushTraitStack(gBattlerTarget, ABILITY_DEFIANT);
            SET_STATCHANGER(STAT_ATK, 2, FALSE);
        }
        if (SearchTraits(battlerTraits, ABILITY_COMPETITIVE))
        {
            PushTraitStack(gBattlerTarget, ABILITY_COMPETITIVE);
            SET_STATCHANGER(STAT_SPATK, 2, FALSE);
        }
    }
    // Check Defiant and Competitive when Contrary is present
    else if (stringId == STRINGID_DEFENDERSSTATFELL
              && hasContrary
              && gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != BATTLE_PARTNER(gBattlerTarget) 
              && gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != gBattlerTarget) // Defiant/Competitive should not trigger on self afflicted changes
    {
        // First case: Competitive on its own
        // Second case: Defiant on its own will work normally, ignoring the second call for Competitive.
        // Third case: Defiant triggers but NOT Competitive, Defiant then triggers Comptitive resulting in only one activation each.
        // Fourth case: ATK is maxed out, Defiant can't trigger but an exclusion is included to manually trigger Competitive.

        // Competitive on its own
        if (SearchTraits(battlerTraits, ABILITY_COMPETITIVE)
         && !SearchTraits(battlerTraits, ABILITY_DEFIANT)
         && gProtectStructs[gBattlerTarget].contraryCompetitive == FALSE)
        {
            if (CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gProtectStructs[gBattlerTarget].contraryCompetitive = TRUE;
                gBattlerAbility = gBattlerTarget;
                BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
                PushTraitStack(gBattlerTarget, ABILITY_COMPETITIVE);
                SET_STATCHANGER(STAT_SPATK, 2, FALSE);
            }
            else
            {
                gProtectStructs[gBattlerTarget].contraryCompetitive = TRUE;
                stringId = STRINGID_STATSWONTDECREASE;
            }
        }
        // Defiant either on its own or paired with Competitive
        else if (SearchTraits(battlerTraits, ABILITY_DEFIANT)
         && gProtectStructs[gBattlerTarget].contraryDefiant == FALSE)
        {
            if (CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gProtectStructs[gBattlerTarget].contraryDefiant = TRUE;
                gBattlerAbility = gBattlerTarget;
                BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
                PushTraitStack(gBattlerTarget, ABILITY_DEFIANT);
                SET_STATCHANGER(STAT_ATK, 2, FALSE);
            }
            else //If Defiant triggered but ATK is maxed, display Won't Increase message and manually trigger Competitive
            {
                gProtectStructs[gBattlerTarget].contraryDefiant = TRUE;
                stringId = STRINGID_STATSWONTDECREASE;
                BtlController_EmitPrintString(battler, B_COMM_TO_CONTROLLER, stringId);

                if (SearchTraits(battlerTraits, ABILITY_COMPETITIVE)
                && gProtectStructs[gBattlerTarget].contraryCompetitive == FALSE)
                {
                    if (CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                    {
                        gProtectStructs[gBattlerTarget].contraryCompetitive = TRUE;
                        gBattlerAbility = gBattlerTarget;
                        BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
                        PushTraitStack(gBattlerTarget, ABILITY_COMPETITIVE);
                        SET_STATCHANGER(STAT_SPATK, 2, FALSE);
                    }
                    else
                    {
                        gProtectStructs[gBattlerTarget].contraryCompetitive = TRUE;
                        stringId = STRINGID_STATSWONTDECREASE;
                    }
                }
            }
        } // else if used because Contrary Defiant will already retrigger the loop, so this enforces only Defiant triggers and then only Competitive
        else if (SearchTraits(battlerTraits, ABILITY_COMPETITIVE)
         && gProtectStructs[gBattlerTarget].contraryCompetitive == FALSE)
        {
            if (CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gProtectStructs[gBattlerTarget].contraryCompetitive = TRUE;
                gBattlerAbility = gBattlerTarget;
                BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
                PushTraitStack(gBattlerTarget, ABILITY_COMPETITIVE);
                SET_STATCHANGER(STAT_SPATK, 2, FALSE);
            }
            else
            {
                gProtectStructs[gBattlerTarget].contraryCompetitive = TRUE;
                stringId = STRINGID_STATSWONTDECREASE;
            }
        }
    }

    // Generate ability popup for Contrary, only when a status change happens outside of Defiant/Competitive wich have their own popup calls
    // Contrary does not have popup in vanilla
    // if (hasContrary
    //     && ((stringId == STRINGID_DEFENDERSSTATFELL || stringId == STRINGID_STATSWONTINCREASE || stringId == STRINGID_STATSWONTDECREASE || stringId == STRINGID_STATSWONTINCREASE2 || stringId == STRINGID_STATSWONTDECREASE2
    //     stringId == STRINGID_STATSWONTINCREASECONTRARY2 || stringId == STRINGID_STATSWONTDECREASECONTRARY2)
    //     || (stringId == STRINGID_DEFENDERSSTATROSE && !((gProtectStructs[gBattlerTarget].contraryCompetitive || gProtectStructs[gBattlerTarget].contraryDefiant))
    //     && (gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != BATTLE_PARTNER(gBattlerTarget) || gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != gBattlerTarget))))
    // {
    //     PushTraitStack(gBattlerTarget, ABILITY_CONTRARY);
    //     BattleScriptCall(BattleScript_GenerateAbilityPopUp);
    // }

    BtlController_EmitPrintString(battler, B_COMM_TO_CONTROLLER, stringId);
    MarkBattlerForControllerExec(battler);
}

void ResetSentPokesToOpponentValue(void)
{
    s32 i;
    u32 bits = 0;

    gSentPokesToOpponent[0] = 0;
    gSentPokesToOpponent[1] = 0;

    for (i = 0; i < gBattlersCount; i += 2)
        bits |= 1u << gBattlerPartyIndexes[i];

    for (i = 1; i < gBattlersCount; i += 2)
        gSentPokesToOpponent[(i & BIT_FLANK) >> 1] = bits;
}

void OpponentSwitchInResetSentPokesToOpponentValue(enum BattlerId battler)
{
    s32 i = 0;
    u32 bits = 0;

    if (!IsOnPlayerSide(battler))
    {
        u8 flank = ((battler & BIT_FLANK) >> 1);
        gSentPokesToOpponent[flank] = 0;

        for (i = 0; i < gBattlersCount; i += 2)
        {
            if (!(gAbsentBattlerFlags & (1u << i)))
                bits |= 1u << gBattlerPartyIndexes[i];
        }
        gSentPokesToOpponent[flank] = bits;
    }
}

void UpdateSentPokesToOpponentValue(enum BattlerId battler)
{
    if (!IsOnPlayerSide(battler))
    {
        OpponentSwitchInResetSentPokesToOpponentValue(battler);
    }
    else
    {
        s32 i;
        for (i = 1; i < gBattlersCount; i++)
            gSentPokesToOpponent[(i & BIT_FLANK) >> 1] |= 1u << gBattlerPartyIndexes[battler];
    }
}

void BattleScriptPush(const u8 *bsPtr)
{
    assertf(gBattleResources->battleScriptsStack->size < UINT8_MAX, "attempted to push a battle script, but battleScriptsStack is full!");
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = bsPtr;
}

void BattleScriptPushCursor(void)
{
    assertf(gBattleResources->battleScriptsStack->size < UINT8_MAX, "attempted to push cursor, but battleScriptsStack is full!");
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = gBattlescriptCurrInstr;
}

void BattleScriptCall(const u8 *bsPtr)
{
    BattleScriptPushCursor();
    gBattlescriptCurrInstr = bsPtr;
}

void BattleScriptPop(void)
{
    if (gBattleResources->battleScriptsStack->size != 0)
        gBattlescriptCurrInstr = gBattleResources->battleScriptsStack->ptr[--gBattleResources->battleScriptsStack->size];
}

void BattleScriptExecute(const u8 *BS_ptr)
{
    gBattlescriptCurrInstr = BS_ptr;
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands_PopCallbacksStack;
    gCurrentActionFuncId = 0;
}

void BattleScriptPushCursorAndCallback(const u8 *BS_ptr)
{
    BattleScriptCall(BS_ptr);
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands;
}

bool32 IsGravityPreventingMove(enum Move move)
{
    if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
        return FALSE;

    return IsMoveGravityBanned(move);
}

bool32 IsHealBlockPreventingMove(enum BattlerId battler, enum Move move)
{
    if (!gBattleMons[battler].volatiles.healBlock)
        return FALSE;

    return IsHealingMove(move);
}

bool32 IsBelchPreventingMove(enum BattlerId battler, enum Move move)
{
    if (GetMoveEffect(move) != EFFECT_BELCH)
        return FALSE;

    return !GetBattlerPartyState(battler)->ateBerry;
}

// Dynamax bypasses all selection prevention except Taunt and Assault Vest.
#define DYNAMAX_BYPASS_CHECK    (!IsGimmickSelected(battler, GIMMICK_DYNAMAX) && GetActiveGimmick(battler) != GIMMICK_DYNAMAX)

u32 TrySetCantSelectMoveBattleScript(enum BattlerId battler)
{
    u32 limitations = 0;
    u8 moveId = gBattleResources->bufferB[battler][2] & ~RET_GIMMICK;
    enum Move move = gBattleMons[battler].moves[moveId];
    u16 *choicedMove = &gBattleStruct->choicedMove[battler];
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);

    if (GetConfig(B_ENCORE_TARGET) >= GEN_5
     && DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && gBattleMons[battler].volatiles.encoredMove != move && gBattleMons[battler].volatiles.encoredMove != MOVE_NONE)
    {
        gBattleScripting.battler = battler;
        gCurrentMove = gBattleMons[battler].volatiles.encoredMove;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_EncoredMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_EncoredMove;
            limitations++;
        }
        return limitations;
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && gBattleMons[battler].volatiles.disabledMove == move && move != MOVE_NONE)
    {
        gBattleScripting.battler = battler;
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingDisabledMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingDisabledMove;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && move == gLastMoves[battler] && move != MOVE_STRUGGLE && (gBattleMons[battler].volatiles.torment == TRUE))
    {
        CancelMultiTurnMoves(battler, SKY_DROP_IGNORE);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingTormentedMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingTormentedMove;
            limitations++;
        }
    }

    if (GetActiveGimmick(battler) != GIMMICK_Z_MOVE
     && gBattleMons[battler].volatiles.tauntTimer != 0
     && IsBattleMoveStatus(move)
     && (GetConfig(B_TAUNT_ME_FIRST) < GEN_5 || moveEffect != EFFECT_ME_FIRST))
    {
        if ((GetActiveGimmick(battler) == GIMMICK_DYNAMAX))
            gCurrentMove = MOVE_MAX_GUARD;
        else
            gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveTauntInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveTaunt;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && gBattleMons[battler].volatiles.throatChopTimer > 0 && IsSoundMove(move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveThroatChopInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveThroatChop;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && GetImprisonedMovesCount(battler, move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingImprisonedMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingImprisonedMove;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && IsGravityPreventingMove(move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGravityInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGravity;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && IsHealBlockPreventingMove(battler, move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveHealBlockInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveHealBlock;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && IsBelchPreventingMove(battler, move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedBelchInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedBelch;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && moveEffect == EFFECT_STUFF_CHEEKS && !BattlerHasBerry(battler))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedStuffCheeksInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedStuffCheeks;
            limitations++;
        }
    }

    if (MoveCantBeUsedTwice(move) && move == gLastResultingMoves[battler])
    {
        gCurrentMove = move;
        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gCurrentMove);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMove;
            limitations++;
        }
    }

    gPotentialItemEffectBattler = battler;
    if (DYNAMAX_BYPASS_CHECK && BattlerHasHoldEffectChoice(battler) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        //Check for the choice item
        gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_CHOICE_BAND, TRUE);
        if(gLastUsedItem == ITEM_NONE)
            gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_CHOICE_SCARF, TRUE);
        if(gLastUsedItem == ITEM_NONE)
            gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_CHOICE_SPECS, TRUE);
        
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveChoiceItemInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveChoiceItem;
            limitations++;
        }
    }
    else if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_ASSAULT_VEST, TRUE) && IsBattleMoveStatus(move) && moveEffect != EFFECT_ME_FIRST)
    {
        if ((GetActiveGimmick(battler) == GIMMICK_DYNAMAX))
            gCurrentMove = MOVE_MAX_GUARD;
        else
            gCurrentMove = move;
        gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_ASSAULT_VEST, TRUE);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveAssaultVestInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveAssaultVest;
            limitations++;
        }
    }
    if (DYNAMAX_BYPASS_CHECK && (BattlerHasTrait(battler, ABILITY_GORILLA_TACTICS)) && *choicedMove != MOVE_NONE
              && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_ASSAULT_VEST, TRUE);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGorillaTacticsInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGorillaTactics;
            limitations++;
        }
    }

    if (gBattleMons[battler].pp[moveId] == 0)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingMoveWithNoPP;
            limitations++;
        }
    }

    if (moveEffect == EFFECT_PLACEHOLDER)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedPlaceholderInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedPlaceholder;
            limitations++;
        }
    }

    return limitations;
}

u32 CheckMoveLimitations(enum BattlerId battler, u8 unusableMoves, u16 check)
{
    enum Move move;
    enum BattleMoveEffects moveEffect;
    u16 *choicedMove = &gBattleStruct->choicedMove[battler];
    s32 i;

    gPotentialItemEffectBattler = battler;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = gBattleMons[battler].moves[i];
        moveEffect = GetMoveEffect(move);
        // No move
        if (check & MOVE_LIMITATION_ZEROMOVE && move == MOVE_NONE)
            unusableMoves |= 1u << i;
        // No PP
        else if (check & MOVE_LIMITATION_PP && gBattleMons[battler].pp[i] == 0)
            unusableMoves |= 1u << i;
        // Placeholder
        else if (check & MOVE_LIMITATION_PLACEHOLDER && moveEffect == EFFECT_PLACEHOLDER)
            unusableMoves |= 1u << i;
        // Disable
        else if (check & MOVE_LIMITATION_DISABLED && move == gBattleMons[battler].volatiles.disabledMove)
            unusableMoves |= 1u << i;
        // Torment
        else if (check & MOVE_LIMITATION_TORMENTED && move == gLastMoves[battler] && gBattleMons[battler].volatiles.torment == TRUE)
            unusableMoves |= 1u << i;
        // Taunt
        else if (check & MOVE_LIMITATION_TAUNT
              && gBattleMons[battler].volatiles.tauntTimer
              && IsBattleMoveStatus(move)
              && (GetConfig(B_TAUNT_ME_FIRST) < GEN_5 || moveEffect != EFFECT_ME_FIRST))
            unusableMoves |= 1u << i;
        // Imprison
        else if (check & MOVE_LIMITATION_IMPRISON && GetImprisonedMovesCount(battler, move))
            unusableMoves |= 1u << i;
        // Encore
        else if (check & MOVE_LIMITATION_ENCORE && gBattleMons[battler].volatiles.encoreTimer && gBattleMons[battler].volatiles.encoredMove != move)
            unusableMoves |= 1u << i;
        // Choice Items
        else if (check & MOVE_LIMITATION_CHOICE_ITEM && BattlerHasHoldEffectChoice(battler) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
            unusableMoves |= 1u << i;
        // Assault Vest
        else if (check & MOVE_LIMITATION_ASSAULT_VEST && BattlerHasHeldItemEffect(battler, HOLD_EFFECT_ASSAULT_VEST, TRUE) && IsBattleMoveStatus(move) && moveEffect != EFFECT_ME_FIRST)
            unusableMoves |= 1u << i;
        // Gravity
        else if (check & MOVE_LIMITATION_GRAVITY && IsGravityPreventingMove(move))
            unusableMoves |= 1u << i;
        // Heal Block
        else if (check & MOVE_LIMITATION_HEAL_BLOCK && IsHealBlockPreventingMove(battler, move))
            unusableMoves |= 1u << i;
        // Belch
        else if (check & MOVE_LIMITATION_BELCH && IsBelchPreventingMove(battler, move))
            unusableMoves |= 1u << i;
        // Throat Chop
        else if (check & MOVE_LIMITATION_THROAT_CHOP && gBattleMons[battler].volatiles.throatChopTimer > 0 && IsSoundMove(move))
            unusableMoves |= 1u << i;
        // Stuff Cheeks
        else if (check & MOVE_LIMITATION_STUFF_CHEEKS && moveEffect == EFFECT_STUFF_CHEEKS && !BattlerHasBerry(battler))
            unusableMoves |= 1u << i;
        // Gorilla Tactics
        else if (check & MOVE_LIMITATION_CHOICE_ITEM && BattlerHasTrait(battler, ABILITY_GORILLA_TACTICS) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
            unusableMoves |= 1u << i;
        // Can't Use Twice flag
        else if (check & MOVE_LIMITATION_CANT_USE_TWICE && MoveCantBeUsedTwice(move) && move == gLastResultingMoves[battler])
            unusableMoves |= 1u << i;
    }
    return unusableMoves;
}

#define ALL_MOVES_MASK ((1 << MAX_MON_MOVES) - 1)
bool32 AreAllMovesUnusable(enum BattlerId battler)
{
    u32 unusable = CheckMoveLimitations(battler, 0, MOVE_LIMITATIONS_ALL);

    if (unusable == ALL_MOVES_MASK) // All moves are unusable.
    {
        gProtectStructs[battler].noValidMoves = TRUE;
        gSelectionBattleScripts[battler] = BattleScript_NoMovesLeft;
    }
    else
    {
        gProtectStructs[battler].noValidMoves = FALSE;
    }

    return (unusable == ALL_MOVES_MASK);
}

u8 GetImprisonedMovesCount(enum BattlerId battler, enum Move move)
{
    s32 i;
    u8 imprisonedMoves = 0;
    u32 battlerSide = GetBattlerSide(battler);

    for (i = 0; i < gBattlersCount; i++)
    {
        if (battlerSide != GetBattlerSide(i) && gBattleMons[i].volatiles.imprison)
        {
            s32 j;
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (move == gBattleMons[i].moves[j])
                    break;
            }
            if (j < MAX_MON_MOVES)
                imprisonedMoves++;
        }
    }

    return imprisonedMoves;
}

u32 GetBattlerAffectionHearts(enum BattlerId battler)
{
    struct Pokemon *mon = GetBattlerMon(battler);
    u16 species = GetMonData(mon, MON_DATA_SPECIES);

    if (!IsOnPlayerSide(battler))
        return AFFECTION_NO_HEARTS;
    else if (gSpeciesInfo[species].isMegaEvolution
          || (gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
                                | BATTLE_TYPE_FRONTIER
                                | BATTLE_TYPE_LINK
                                | BATTLE_TYPE_RECORDED_LINK
                                | BATTLE_TYPE_SECRET_BASE)))
        return AFFECTION_NO_HEARTS;

    return GetMonAffectionHearts(mon);
}

// gBattlerAttacker is the battler that's trying to raise their stats and due to limitations of RandomUniformExcept, cannot be an argument
bool32 MoodyCantRaiseStat(u32 stat)
{
    return CompareStat(gBattlerAttacker, stat, MAX_STAT_STAGE, CMP_EQUAL);
}

// gBattlerAttacker is the battler that's trying to lower their stats and due to limitations of RandomUniformExcept, cannot be an argument
bool32 MoodyCantLowerStat(u32 stat)
{
    return stat == GET_STAT_BUFF_ID(gBattleScripting.statChanger) || CompareStat(gBattlerAttacker, stat, MIN_STAT_STAGE, CMP_EQUAL);
}

void TryToRevertMimicryAndFlags(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        gBattleMons[battler].volatiles.terrainAbilityDone = FALSE;
        ResetParadoxTerrainStat(battler);
        if (IsAbilityAndRecord(battler, ABILITY_MIMICRY))
            RESTORE_BATTLER_TYPE(battler);
    }
}

bool32 BattleArenaTurnEnd(void)
{
    if ((gBattleTypeFlags & BATTLE_TYPE_ARENA)
     && gBattleStruct->eventState.arenaTurn == 2
     && IsBattlerAlive(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)) && IsBattlerAlive(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)))
    {
        for (enum BattlerId battler = 0; battler < 2; battler++)
            CancelMultiTurnMoves(battler, SKY_DROP_IGNORE);

        gBattlescriptCurrInstr = BattleScript_ArenaDoJudgment;
        BattleScriptExecute(BattleScript_ArenaDoJudgment);
        return TRUE;
    }
    return FALSE;
}

// Ingrain, Leech Seed, Strength Sap and Aqua Ring
s32 GetDrainedBigRootHp(enum BattlerId battler, s32 hp)
{
    if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_BIG_ROOT, TRUE))
        hp = (hp * 1300) / 1000;
    if (hp == 0)
        hp = 1;

    return hp;
}

// Should always be the last check. Otherwise the ability might be wrongly recorded.
bool32 IsAbilityAndRecord(enum BattlerId battler, enum Ability abilityToCheck)
{
    if (!BattlerHasTrait(battler, abilityToCheck))
        return FALSE;

    RecordAbilityBattle(battler, abilityToCheck);
    return TRUE;
}

bool32 HandleFaintedMonActions(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return FALSE;

    do
    {
        switch (gBattleStruct->eventState.faintedAction)
        {
        case FAINTED_ACTIONS_NO_MONS_TO_SWITCH:
            gBattleStruct->eventState.faintedActionBattler = 0;
            gBattleStruct->eventState.faintedAction++;
            for (enum BattlerId i = 0; i < gBattlersCount; i++)
            {
                if (gAbsentBattlerFlags & (1u << i) && !HasNoMonsToSwitch(i, PARTY_SIZE, PARTY_SIZE))
                    gAbsentBattlerFlags &= ~(1u << i);
            }
            // fall through
        case FAINTED_ACTIONS_GIVE_EXP:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->eventState.faintedActionBattler;
                if (gBattleMons[gBattleStruct->eventState.faintedActionBattler].hp == 0
                 && !(gBattleStruct->givenExpMons & (1u << gBattlerPartyIndexes[gBattleStruct->eventState.faintedActionBattler]))
                 && !(gAbsentBattlerFlags & (1u << gBattleStruct->eventState.faintedActionBattler)))
                {
                    BattleScriptExecute(BattleScript_GiveExp);
                    gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_SET_ABSENT_FLAGS;
                    return TRUE;
                }
            } while (++gBattleStruct->eventState.faintedActionBattler != gBattlersCount);
            gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_WAIT_STATE;
            break;
        case FAINTED_ACTIONS_SET_ABSENT_FLAGS:
            OpponentSwitchInResetSentPokesToOpponentValue(gBattlerFainted);
            if (++gBattleStruct->eventState.faintedActionBattler == gBattlersCount)
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_WAIT_STATE;
            else
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_GIVE_EXP;
            // Don't switch mons until all pokemon performed their actions or the battle's over.
            if (B_FAINT_SWITCH_IN >= GEN_4
                && gBattleOutcome == 0
                && !NoAliveMonsForEitherParty()
                && gCurrentTurnActionNumber != gBattlersCount)
            {
                gAbsentBattlerFlags |= 1u << gBattlerFainted;
                if (gBattleStruct->eventState.faintedAction != FAINTED_ACTIONS_GIVE_EXP)
                    return FALSE;
            }
            break;
        case FAINTED_ACTIONS_WAIT_STATE:
            // Don't switch mons until all pokemon performed their actions or the battle's over.
            if (B_FAINT_SWITCH_IN >= GEN_4
                && gBattleOutcome == 0
                && !NoAliveMonsForEitherParty()
                && gCurrentTurnActionNumber != gBattlersCount)
            {
                return FALSE;
            }
            gBattleStruct->eventState.faintedActionBattler = 0;
            gBattleStruct->eventState.faintedAction++;
            // fall through
        case FAINTED_ACTIONS_HANDLE_FAINTED_MON:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->eventState.faintedActionBattler;
                if (gBattleMons[gBattleStruct->eventState.faintedActionBattler].hp == 0
                 && !(gAbsentBattlerFlags & (1u << gBattleStruct->eventState.faintedActionBattler)))
                {
                    BattleScriptExecute(BattleScript_HandleFaintedMon);
                    gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_HANDLE_NEXT_BATTLER;
                    return TRUE;
                }
            } while (++gBattleStruct->eventState.faintedActionBattler != gBattlersCount);
            gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_MAX_CASE;
            break;
        case FAINTED_ACTIONS_HANDLE_NEXT_BATTLER:
            if (++gBattleStruct->eventState.faintedActionBattler == gBattlersCount)
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_MAX_CASE;
            else
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_HANDLE_FAINTED_MON;
            break;
        case FAINTED_ACTIONS_MAX_CASE:
            break;
        }
    } while (gBattleStruct->eventState.faintedAction != FAINTED_ACTIONS_MAX_CASE);
    return FALSE;
}

void TryClearRageAndFuryCutter(void)
{
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (!MoveHasAdditionalEffect(gChosenMoveByBattler[i], MOVE_EFFECT_RAGE))
            gBattleMons[i].volatiles.rage = FALSE;
    }
}

bool32 HasNoMonsToSwitch(enum BattlerId battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2)
{
    u32 i, playerId, flankId;
    struct Pokemon *party;

    if (!IsDoubleBattle())
        return FALSE;

    bool32 isPlayerside = IsOnPlayerSide(battler);

    if (BATTLE_TWO_VS_ONE_OPPONENT && !isPlayerside)
    {
        flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        party = gEnemyParty;

        // Edge case: If both opposing Pokemon were knocked out on the same turn,
        // make sure opponent only sends out the final Pokemon once.
        if (battler == playerId
         && (gHitMarker & HITMARKER_FAINTED(flankId))
         && (gHitMarker & HITMARKER_FAINTED(playerId)))
        {
            u8 count = 0;
            for (i = 0; i < PARTY_SIZE; i++)
                if (IsValidForBattle(&party[i]))
                    count++;

            if (count < 2)
                return TRUE;
        }

        if (partyIdBattlerOn1 == PARTY_SIZE)
            partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
        if (partyIdBattlerOn2 == PARTY_SIZE)
            partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i])
             && i != partyIdBattlerOn1 && i != partyIdBattlerOn2
             && i != gBattleStruct->monToSwitchIntoId[flankId] && i != playerId[gBattleStruct->monToSwitchIntoId])
                break;
        }
        return (i == PARTY_SIZE);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        party = GetBattlerParty(battler);
        if (!isPlayerside && WILD_DOUBLE_BATTLE)
        {
            flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);

            if (partyIdBattlerOn1 == PARTY_SIZE)
                partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
            if (partyIdBattlerOn2 == PARTY_SIZE)
                partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

            for (i = 0; i < PARTY_SIZE; i++)
            {
                if (IsValidForBattle(&party[i])
                 && i != partyIdBattlerOn1 && i != partyIdBattlerOn2
                 && i != gBattleStruct->monToSwitchIntoId[flankId] && i != playerId[gBattleStruct->monToSwitchIntoId])
                    break;
            }
            return (i == PARTY_SIZE);
        }
        else
        {
            playerId = ((battler & BIT_FLANK) / 2);
            for (i = playerId * MULTI_PARTY_SIZE; i < playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE; i++)
            {
                if (IsValidForBattle(&party[i]))
                    break;
            }
            return (i == playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE);
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
        {
            if (isPlayerside)
            {
                party = gPlayerParty;
                flankId = GetBattlerMultiplayerId(battler);
                playerId = GetLinkTrainerFlankId(flankId);
            }
            else
            {
                party = gEnemyParty;
                if (battler == 1)
                    playerId = 0;
                else
                    playerId = 1;
            }
        }
        else
        {
            flankId = GetBattlerMultiplayerId(battler);
            party = GetBattlerParty(battler);
            playerId = GetLinkTrainerFlankId(flankId);
        }

        for (i = playerId * MULTI_PARTY_SIZE; i < playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]))
                break;
        }
        return (i == playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE);
    }
    else if ((gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) && !isPlayerside)
    {
        party = gEnemyParty;

        if (battler == 1)
            playerId = 0;
        else
            playerId = MULTI_PARTY_SIZE;

        for (i = playerId; i < playerId + MULTI_PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]))
                break;
        }
        return (i == playerId + 3);
    }
    else
    {
        if (!isPlayerside)
        {
            flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
            party = gEnemyParty;
        }
        else
        {
            flankId = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
            party = gPlayerParty;
        }

        if (partyIdBattlerOn1 == PARTY_SIZE)
            partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
        if (partyIdBattlerOn2 == PARTY_SIZE)
            partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i])
             && i != partyIdBattlerOn1 && i != partyIdBattlerOn2
             && i != gBattleStruct->monToSwitchIntoId[flankId] && i != playerId[gBattleStruct->monToSwitchIntoId])
                break;
        }
        return (i == PARTY_SIZE);
    }
}

bool32 TryChangeBattleWeather(enum BattlerId battler, u32 battleWeatherId, bool32 viaAbility)
{
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battler);

    if (gBattleWeather & sBattleWeatherInfo[battleWeatherId].flag)
        return FALSE;

    else if (gBattleWeather & B_WEATHER_PRIMAL_ANY
        && !SearchTraits(battlerTraits, ABILITY_DESOLATE_LAND)
        && !SearchTraits(battlerTraits, ABILITY_PRIMORDIAL_SEA)
        && !SearchTraits(battlerTraits, ABILITY_DELTA_STREAM))
    {
        return FALSE;
    }

    if (GetConfig(B_ABILITY_WEATHER) < GEN_6 && viaAbility)
    {
        gBattleWeather = sBattleWeatherInfo[battleWeatherId].flag;
    }
    else
    {
        u32 rock = sBattleWeatherInfo[battleWeatherId].rock;
        gBattleWeather = sBattleWeatherInfo[battleWeatherId].flag;

        if (gBattleWeather & B_WEATHER_PRIMAL_ANY)
            gBattleStruct->weatherDuration = 0;
        else if (rock != 0 && BattlerHasHeldItemEffect(battler, rock, TRUE))
            gBattleStruct->weatherDuration = 8;
        else
            gBattleStruct->weatherDuration = 5;
    }

    if (viaAbility) // Weather started by Ability
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[battleWeatherId].abilityStartMessage;
        gBattleScripting.animArg1 = sBattleWeatherInfo[battleWeatherId].animation;
    }
    else // Weather started by Move
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[battleWeatherId].moveStartMessage;
    }

    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        gBattleMons[i].volatiles.weatherAbilityDone = FALSE;
        gBattleMons[i].volatiles.transformWeatherAbilityDone = FALSE;
        ResetParadoxWeatherStat(i);
    }

    return TRUE;
}

bool32 TryChangeBattleTerrain(enum BattlerId battler, u32 statusFlag)
{
    if (gBattleStruct->isSkyBattle)
        return FALSE;

    if (!(gFieldStatuses & statusFlag))
    {
        gFieldStatuses &= ~STATUS_FIELD_TERRAIN_ANY;
        gFieldStatuses |= statusFlag;
        for (enum BattlerId i = 0; i < gBattlersCount; i++)
        {
            gBattleMons[i].volatiles.terrainAbilityDone = FALSE;
            ResetParadoxTerrainStat(i);
        }
        if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_TERRAIN_EXTENDER, TRUE))
            gFieldTimers.terrainTimer = 8;
        else
            gFieldTimers.terrainTimer = 5;
        gBattleScripting.battler = battler;
        return TRUE;
    }

    return FALSE;
}

static void ForewarnChooseMove(enum BattlerId battler)
{
    struct Forewarn {
        enum BattlerId battler;
        u8 power;
        u16 moveId;
    };
    u32 i, j, bestId, count;
    struct Forewarn *data = Alloc(sizeof(struct Forewarn) * MAX_BATTLERS_COUNT * MAX_MON_MOVES);

    // Put all moves
    for (count = 0, i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (IsBattlerAlive(i) && !IsBattlerAlly(i, battler))
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMons[i].moves[j] == MOVE_NONE)
                    continue;
                data[count].moveId = gBattleMons[i].moves[j];
                data[count].battler = i;
                switch (GetMoveEffect(data[count].moveId))
                {
                case EFFECT_OHKO:
                    data[count].power = 150;
                    break;
                case EFFECT_REFLECT_DAMAGE:
                    data[count].power = 120;
                    break;
                default:
                {
                    u32 movePower = GetMovePower(data[count].moveId);
                    if (movePower == 1)
                        data[count].power = 80;
                    else
                        data[count].power = movePower;
                    break;
                }
                }
                count++;
            }
        }
    }

    if (count == 0)
    {
        Free(data);
        return;
    }

    u32 tieCount = 1;
    u8 bestPower = data[0].power;

    bestId = 0;
    for (i = 1; i < count; i++)
    {
        if (data[i].power > bestPower)
        {
            bestPower = data[i].power;
            bestId = i;
            tieCount = 1;
        }
        else if (data[i].power == bestPower)
        {
            tieCount++;
        }
    }

    if (tieCount > 1)
    {
        u32 tieIndex = RandomUniform(RNG_FOREWARN, 0, tieCount - 1);
        for (i = 0, bestId = 0; i < count; i++)
        {
            if (data[i].power != bestPower)
                continue;
            if (tieIndex-- == 0)
            {
                bestId = i;
                break;
            }
        }
    }

    gEffectBattler = data[bestId].battler;
    PREPARE_MOVE_BUFFER(gBattleTextBuff1, data[bestId].moveId)
    RecordKnownMove(data[bestId].battler, data[bestId].moveId);

    Free(data);
}

bool32 ChangeTypeBasedOnTerrain(enum BattlerId battler)
{
    enum Type battlerType;

    if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
        battlerType = TYPE_ELECTRIC;
    else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
        battlerType = TYPE_GRASS;
    else if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
        battlerType = TYPE_FAIRY;
    else if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
        battlerType = TYPE_PSYCHIC;
    else if (gFieldStatuses & STATUS_FIELD_SCORCHED_FIELD)
        battlerType = TYPE_FIRE;
    else // failsafe
        return FALSE;

    SET_BATTLER_TYPE(battler, battlerType);
    PREPARE_TYPE_BUFFER(gBattleTextBuff1, battlerType);
    return TRUE;
}

static inline u8 GetSideFaintCounter(enum BattleSide side)
{
    return (side == B_SIDE_PLAYER) ? gBattleResults.playerFaintCounter : gBattleResults.opponentFaintCounter;
}

static inline u8 GetBattlerSideFaintCounter(enum BattlerId battler)
{
    return GetSideFaintCounter(GetBattlerSide(battler));
}

// Supreme Overlord adds a x0.1 damage boost for each fainted ally.
static inline uq4_12_t GetSupremeOverlordModifier(enum BattlerId battler)
{
    return UQ_4_12(1.0) + (PercentToUQ4_12(gBattleStruct->supremeOverlordCounter[battler] * 10));
}

static inline u32 GetPackLeaderAllyCount(enum BattlerId battler)
{
    u32 count = 0;
    struct Pokemon *party = GetBattlerParty(battler);

    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (i == gBattlerPartyIndexes[battler])
            continue;
        if (GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
         || GetMonData(&party[i], MON_DATA_IS_EGG)
         || GetMonData(&party[i], MON_DATA_HP) == 0)
            continue;
        count++;
    }

    return min(5, count);
}

static inline uq4_12_t GetPackLeaderModifier(enum BattlerId battler)
{
    return UQ_4_12(1.0) + PercentToUQ4_12(GetPackLeaderAllyCount(battler) * 5);
}

static bool32 IsHorseCouncilSpecies(u16 species)
{
    switch (species)
    {
    case SPECIES_PONYTA:
    case SPECIES_RAPIDASH:
    case SPECIES_PONYTA_GALAR:
    case SPECIES_RAPIDASH_GALAR:
    case SPECIES_PALKIA_ORIGIN:
    case SPECIES_DIALGA:
    case SPECIES_DIALGA_ORIGIN:
    case SPECIES_DIALGA_PRIMAL:
    case SPECIES_KELDEO_ORDINARY:
    case SPECIES_KELDEO_RESOLUTE:
    case SPECIES_GLASTRIER:
    case SPECIES_SPECTRIER:
    case SPECIES_PHANPY:
    case SPECIES_DONPHAN:
    case SPECIES_GIRAFARIG:
    case SPECIES_FARIGIRAF:
    case SPECIES_DEERLING_SPRING:
    case SPECIES_DEERLING_SUMMER:
    case SPECIES_DEERLING_AUTUMN:
    case SPECIES_DEERLING_WINTER:
    case SPECIES_SAWSBUCK_SPRING:
    case SPECIES_SAWSBUCK_SUMMER:
    case SPECIES_SAWSBUCK_AUTUMN:
    case SPECIES_SAWSBUCK_WINTER:
    case SPECIES_NUMEL:
    case SPECIES_CAMERUPT:
    case SPECIES_TAUROS:
    case SPECIES_TAUROS_PALDEA_COMBAT:
    case SPECIES_TAUROS_PALDEA_BLAZE:
    case SPECIES_TAUROS_PALDEA_AQUA:
    case SPECIES_ARCEUS_NORMAL:
    case SPECIES_ARCEUS_FIGHTING:
    case SPECIES_ARCEUS_FLYING:
    case SPECIES_ARCEUS_POISON:
    case SPECIES_ARCEUS_GROUND:
    case SPECIES_ARCEUS_ROCK:
    case SPECIES_ARCEUS_BUG:
    case SPECIES_ARCEUS_GHOST:
    case SPECIES_ARCEUS_STEEL:
    case SPECIES_ARCEUS_FIRE:
    case SPECIES_ARCEUS_WATER:
    case SPECIES_ARCEUS_GRASS:
    case SPECIES_ARCEUS_ELECTRIC:
    case SPECIES_ARCEUS_PSYCHIC:
    case SPECIES_ARCEUS_ICE:
    case SPECIES_ARCEUS_DRAGON:
    case SPECIES_ARCEUS_DARK:
    case SPECIES_ARCEUS_FAIRY:
        return TRUE;
    default:
        return FALSE;
    }
}

static inline u32 GetHorseCouncilAllyCount(enum BattlerId battler)
{
    u32 count = 0;
    struct Pokemon *party = GetBattlerParty(battler);

    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        u16 species;

        if (i == gBattlerPartyIndexes[battler])
            continue;
        if (GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
         || GetMonData(&party[i], MON_DATA_IS_EGG)
         || GetMonData(&party[i], MON_DATA_HP) == 0)
            continue;

        species = GetMonData(&party[i], MON_DATA_SPECIES);
        if (IsHorseCouncilSpecies(species))
            count++;
    }

    return min(5, count);
}

static inline uq4_12_t GetHorseCouncilModifier(enum BattlerId battler)
{
    return UQ_4_12(1.0) + PercentToUQ4_12(GetHorseCouncilAllyCount(battler) * 10);
}

static enum Type GetTypeBoostAbilityType(enum Ability ability)
{
    switch (ability)
    {
    case ABILITY_TRUE_GRIT:
        return TYPE_NORMAL;
    case ABILITY_WARRIOR_SPIRIT:
        return TYPE_FIGHTING;
    case ABILITY_WIND_FORCE:
        return TYPE_FLYING;
    case ABILITY_TOXIC_CORE:
        return TYPE_POISON;
    case ABILITY_EARTHBOUND:
        return TYPE_GROUND;
    case ABILITY_HIVE_FORCE:
        return TYPE_BUG;
    case ABILITY_SPECTRAL_FORCE:
        return TYPE_GHOST;
    case ABILITY_FIERY_HEART:
        return TYPE_FIRE;
    case ABILITY_SEABOUND:
        return TYPE_WATER;
    case ABILITY_VERDANT_SOUL:
        return TYPE_GRASS;
    case ABILITY_MIND_FORCE:
        return TYPE_PSYCHIC;
    case ABILITY_FROST_FORCE:
        return TYPE_ICE;
    case ABILITY_NIGHTFALL:
        return TYPE_DARK;
    case ABILITY_FAE_HEART:
        return TYPE_FAIRY;
    default:
        return TYPE_NONE;
    }
}

static enum Type GetAdditionalTypeAbilityType(enum Ability ability)
{
    switch (ability)
    {
    case ABILITY_PLAIN_SOUL:
        return TYPE_NORMAL;
    case ABILITY_FIGHTER_SOUL:
        return TYPE_FIGHTING;
    case ABILITY_WIND_SOUL:
        return TYPE_FLYING;
    case ABILITY_VENOM_SOUL:
        return TYPE_POISON;
    case ABILITY_EARTH_SOUL:
        return TYPE_GROUND;
    case ABILITY_STONE_SOUL:
        return TYPE_ROCK;
    case ABILITY_HIVE_SOUL:
        return TYPE_BUG;
    case ABILITY_PHANTOM_SOUL:
        return TYPE_GHOST;
    case ABILITY_STEEL_SOUL:
        return TYPE_STEEL;
    case ABILITY_FLAME_SOUL:
        return TYPE_FIRE;
    case ABILITY_SEA_SOUL:
        return TYPE_WATER;
    case ABILITY_VERDANT_SOUL_TYPE:
        return TYPE_GRASS;
    case ABILITY_THUNDER_SOUL:
        return TYPE_ELECTRIC;
    case ABILITY_MIND_SOUL:
        return TYPE_PSYCHIC;
    case ABILITY_FROST_SOUL:
        return TYPE_ICE;
    case ABILITY_DRAGON_SOUL:
        return TYPE_DRAGON;
    case ABILITY_NIGHT_SOUL:
        return TYPE_DARK;
    case ABILITY_FAE_SOUL:
        return TYPE_FAIRY;
    default:
        return TYPE_MYSTERY;
    }
}

bool32 HadMoreThanHalfHpNowDoesnt(enum BattlerId battler)
{
    // Had more than half of hp before, now has less
    return gBattleStruct->battlerState[battler].wasAboveHalfHp
        && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2;
}

u32 NumFaintedBattlersByAttacker(enum BattlerId battlerAtk)
{
    u32 numMonsFainted = 0;

    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (battler == battlerAtk)
            continue;

        if (IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES) && !IsBattlerAlive(battler))
            numMonsFainted++;
    }

    return numMonsFainted;
}

static u32 NumFaintedFoesByAttacker(enum BattlerId battlerAtk)
{
    u32 numMonsFainted = 0;

    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (battler == battlerAtk || IsBattlerAlly(battlerAtk, battler))
            continue;

        if (IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES) && !IsBattlerAlive(battler))
            numMonsFainted++;
    }

    return numMonsFainted;
}

u32 GetStatChangeAnimationId(enum Stat statId, bool32 sharply, bool32 goesDown)
{
    if (goesDown)
        return statId + (sharply ? STAT_ANIM_MINUS2 : STAT_ANIM_MINUS1);

    return statId + (sharply ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
}

void ChooseStatBoostAnimation(enum BattlerId battler)
{
    u32 i;
    enum Stat firstStat = STAT_HP;
    bool32 statBuffMoreThan1 = FALSE;
    static const enum Stat sQueuedStatBoostAnimOrder[] =
    {
        STAT_ATK, STAT_DEF, STAT_SPATK, STAT_SPDEF, STAT_SPEED, STAT_ACC, STAT_EVASION,
    };

    gBattleScripting.animArg1 = 0;

    for (i = 0; i < ARRAY_COUNT(sQueuedStatBoostAnimOrder); i++)
    {
        enum Stat statId = sQueuedStatBoostAnimOrder[i];
        s8 statChange = gQueuedStatBoosts[battler].statChanges[statId - 1];

        if ((gQueuedStatBoosts[battler].stats & (1 << (statId - 1))) == 0)
            continue;

        if (firstStat == STAT_HP)
            firstStat = statId;

        if (statChange > 1 || statChange < -1)
            statBuffMoreThan1 = TRUE;
    }

    if (firstStat != STAT_HP)
        gBattleScripting.animArg1 = GetStatChangeAnimationId(firstStat, statBuffMoreThan1, FALSE);
}

bool32 CanMoveBeBlockedByTarget(struct BattleContext *ctx, s32 movePriority)
{
    return CanPsychicTerrainProtectTarget(ctx, movePriority)
        || CanTargetBlockPranksterMove(ctx, movePriority)
        || IsPowderMoveBlocked(ctx)
        || CanAbilityAbsorbMove(ctx);
}

bool32 CanPsychicTerrainProtectTarget(struct BattleContext *ctx, s32 movePriority)
{
    if (movePriority <= 0
     || !IsPsychicTerrainAffected(ctx->battlerDef, gFieldStatuses)
     || IsBattlerAlly(ctx->battlerAtk, ctx->battlerDef)
     || GetMoveTarget(ctx->move) == TARGET_ALL_BATTLERS
     || GetMoveTarget(ctx->move) == TARGET_OPPONENTS_FIELD)
        return FALSE;

    if (ctx->runScript)
        BattleScriptCall(BattleScript_MoveUsedPsychicTerrainPrevents);

    return TRUE;
}

bool32 CanTargetBlockPranksterMove(struct BattleContext *ctx, s32 movePriority)
{
    if (movePriority <= 0
     || !IsBattleMoveStatus(ctx->move)
     || !BlocksPrankster(ctx->move, ctx->battlerAtk, ctx->battlerDef, TRUE)
     || (IsBattleMoveStatus(ctx->move) && (BattlerHasTrait(ctx->battlerDef, ABILITY_MAGIC_BOUNCE) || gProtectStructs[ctx->battlerDef].bounceMove)))
        return FALSE;

    if (ctx->runScript)
        BattleScriptCall(BattleScript_DoesntAffectScripting);

    return TRUE;
}

static bool32 IsPowderMoveBlocked(struct BattleContext *ctx)
{
    if (!IsPowderMove(ctx->move)
     || ctx->battlerAtk == ctx->battlerDef
     || IsAffectedByPowderMove(ctx->battlerDef))
        return FALSE;

    if (ctx->runScript)
    {
        gBattlerAbility = ctx->battlerDef;
        if (!(GetConfig(B_POWDER_GRASS) >= GEN_6 && IS_BATTLER_OF_TYPE(ctx->battlerDef, TYPE_GRASS))
         && BattlerHasTrait(ctx->battlerDef, ABILITY_OVERCOAT))
        {
            PushTraitStack(ctx->battlerDef, ABILITY_OVERCOAT);
        }
        BattleScriptCall(BattleScript_PowderMoveNoEffect);
    }

    return TRUE;
}

bool32 CanAbilityAbsorbMove(struct BattleContext *ctx)
{
    enum Ability abilityDef = ABILITY_NONE;
    enum Ability battlerTraits[MAX_MON_TRAITS];
    enum Ability AIBattlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(ctx->battlerDef);
    AI_STORE_BATTLER_TRAITS(ctx->battlerDef); //includes AI ambiguity over opponent abilities, innates are always fixed and known

    const u8 *battleScript = NULL;

    if (!IsBattleMoveStatus(ctx->move)
     && GetMovePower(ctx->move) != 0
     && (BattlerHasTrait(ctx->battlerAtk, ABILITY_OMEGA) || BattlerHasTrait(ctx->battlerDef, ABILITY_OMEGA)))
        return FALSE;

    if (BattlerHasTrait(ctx->battlerAtk, ABILITY_MONSOON)
     && ctx->moveType == TYPE_WATER
     && IsBattlerWeatherAffected(ctx->battlerAtk, B_WEATHER_RAIN))
        return FALSE;

    // Uses an extra check for the received ability in case the AI is trying to give a status to itself and thus should know the ability already
    if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_VOLT_ABSORB) : SearchTraits(battlerTraits, ABILITY_VOLT_ABSORB))
     && ctx->moveType == TYPE_ELECTRIC)
    {
        abilityDef = ABILITY_VOLT_ABSORB;
        battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_MUDSLIDE) : SearchTraits(battlerTraits, ABILITY_MUDSLIDE))
     && ctx->moveType == TYPE_WATER
     && IsBattlerWeatherAffected(ctx->battlerDef, B_WEATHER_SANDSTORM))
    {
        abilityDef = ABILITY_MUDSLIDE;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_DEF, 2);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_WATER_ABSORB) : SearchTraits(battlerTraits, ABILITY_WATER_ABSORB))
     && ctx->moveType == TYPE_WATER)
    {
        abilityDef = ABILITY_WATER_ABSORB;
        battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_DRY_SKIN) : SearchTraits(battlerTraits, ABILITY_DRY_SKIN))
     && ctx->moveType == TYPE_WATER)
    {
        abilityDef = ABILITY_DRY_SKIN;
        battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_SMOULDERING) : SearchTraits(battlerTraits, ABILITY_SMOULDERING))
     && ctx->moveType == TYPE_WATER)
    {
        abilityDef = ABILITY_SMOULDERING;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_SPDEF, 1);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_EARTH_EATER) : SearchTraits(battlerTraits, ABILITY_EARTH_EATER))
     && ctx->moveType == TYPE_GROUND)
    {
        abilityDef = ABILITY_EARTH_EATER;
        battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_MOTOR_DRIVE) : SearchTraits(battlerTraits, ABILITY_MOTOR_DRIVE))
     && ctx->moveType == TYPE_ELECTRIC)
    {
        abilityDef = ABILITY_MOTOR_DRIVE;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_SPEED, 1);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_LIGHTNING_ROD) : SearchTraits(battlerTraits, ABILITY_LIGHTNING_ROD))
     && GetConfig(B_REDIRECT_ABILITY_IMMUNITY) >= GEN_5 && ctx->moveType == TYPE_ELECTRIC)
    {
        abilityDef = ABILITY_LIGHTNING_ROD;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_SPATK, 1);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_STORM_DRAIN) : SearchTraits(battlerTraits, ABILITY_STORM_DRAIN))
     && GetConfig(B_REDIRECT_ABILITY_IMMUNITY) >= GEN_5 && ctx->moveType == TYPE_WATER)
    {
        abilityDef = ABILITY_STORM_DRAIN;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_SPATK, 1);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_SAP_SIPPER) : SearchTraits(battlerTraits, ABILITY_SAP_SIPPER))
     && ctx->moveType == TYPE_GRASS)
    {
        abilityDef = ABILITY_SAP_SIPPER;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_ATK, 1);
    }
    else if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_BRIMSTONE)
     && (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_WELL_BAKED_BODY) : SearchTraits(battlerTraits, ABILITY_WELL_BAKED_BODY))
     && ctx->moveType == TYPE_FIRE)
    {
        abilityDef = ABILITY_WELL_BAKED_BODY;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_DEF, 2);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_WIND_RIDER) : SearchTraits(battlerTraits, ABILITY_WIND_RIDER))
     && IsWindMove(ctx->move))
    {
        abilityDef = ABILITY_WIND_RIDER;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_ATK, 1);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_WIND_CHIME) : SearchTraits(battlerTraits, ABILITY_WIND_CHIME))
     && IsWindMove(ctx->move))
    {
        abilityDef = ABILITY_WIND_CHIME;
        battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, STAT_SPATK, 1);
    }
    else if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_BRIMSTONE)
     && (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_FLASH_FIRE) : SearchTraits(battlerTraits, ABILITY_FLASH_FIRE))
     && ctx->moveType == TYPE_FIRE && (B_FLASH_FIRE_FROZEN >= GEN_5 || !(gBattleMons[ctx->battlerDef].status1 & STATUS1_FREEZE)))
    {
        abilityDef = ABILITY_FLASH_FIRE;
        battleScript = AbsorbedByFlashFire(ctx->battlerDef);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_RITUAL) : SearchTraits(battlerTraits, ABILITY_RITUAL))
     && ctx->moveType == TYPE_GHOST)
    {
        abilityDef = ABILITY_RITUAL;
        battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_SOUNDPROOF) : SearchTraits(battlerTraits, ABILITY_SOUNDPROOF))
     && IsSoundMove(ctx->move))
    {
        abilityDef = ABILITY_SOUNDPROOF;
        PushTraitStack(ctx->battlerDef, ABILITY_SOUNDPROOF);
        battleScript = BattleScript_SoundproofProtected;
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_BULLETPROOF) : SearchTraits(battlerTraits, ABILITY_BULLETPROOF))
     && IsBallisticMove(ctx->move))
    {
        abilityDef = ABILITY_BULLETPROOF;
        PushTraitStack(ctx->battlerDef, ABILITY_BULLETPROOF);
        battleScript = BattleScript_SoundproofProtected;
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_GOOD_AS_GOLD) : SearchTraits(battlerTraits, ABILITY_GOOD_AS_GOLD))
     && IsBattleMoveStatus(ctx->move))
    {
        enum MoveTarget target = GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move);
        if (target != TARGET_OPPONENTS_FIELD && target != TARGET_ALL_BATTLERS)
        {
            abilityDef = ABILITY_GOOD_AS_GOLD;
            PushTraitStack(ctx->battlerDef, ABILITY_GOOD_AS_GOLD);
            battleScript = BattleScript_GoodAsGoldActivates;
        }
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_SOLAR_ARMOR) : SearchTraits(battlerTraits, ABILITY_SOLAR_ARMOR))
     && IsBattleMoveStatus(ctx->move))
    {
        enum MoveTarget target = GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move);
        if (target != TARGET_OPPONENTS_FIELD && target != TARGET_ALL_BATTLERS)
        {
            abilityDef = ABILITY_SOLAR_ARMOR;
            PushTraitStack(ctx->battlerDef, ABILITY_SOLAR_ARMOR);
            battleScript = BattleScript_GoodAsGoldActivates;
        }
    }
    else if ((gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_ABYSSAL_VEIL) : SearchTraits(battlerTraits, ABILITY_ABYSSAL_VEIL))
     && IsBattleMoveStatus(ctx->move)
     && gBattleMons[ctx->battlerDef].hp > (gBattleMons[ctx->battlerDef].maxHP * 3) / 4)
    {
        enum MoveTarget target = GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move);
        if (target != TARGET_OPPONENTS_FIELD && target != TARGET_ALL_BATTLERS)
        {
            abilityDef = ABILITY_ABYSSAL_VEIL;
            PushTraitStack(ctx->battlerDef, ABILITY_ABYSSAL_VEIL);
            battleScript = BattleScript_GoodAsGoldActivates;
        }
    }

    if (battleScript == NULL)
        return FALSE;

    if (ctx->runScript)
    {
        gLastUsedAbility = abilityDef;
        PushTraitStack(ctx->battlerDef, abilityDef);
        gBattleScripting.battler = gBattlerAbility = ctx->battlerDef;
        BattleScriptCall(battleScript);
    }

    return TRUE;
}

const u8 *AbsorbedByDrainHpAbility(enum BattlerId battlerDef)
{
    if (IsBattlerAtMaxHp(battlerDef) || (B_HEAL_BLOCKING >= GEN_5 && gBattleMons[battlerDef].volatiles.healBlock))
    {
        return BattleScript_MonMadeMoveUseless;
    }
    else
    {
        SetHealAmount(battlerDef, GetNonDynamaxMaxHP(battlerDef) / 4);
        return BattleScript_MoveHPDrain;
    }
}

const u8 *AbsorbedByStatIncreaseAbility(enum BattlerId battlerDef, enum Stat statId, u32 statAmount)
{
    if (!CompareStat(battlerDef, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
    {
        return BattleScript_MonMadeMoveUseless;
    }
    else
    {
        SET_STATCHANGER(statId, statAmount, FALSE);
        return BattleScript_MoveStatDrain;
    }
}

const u8 *AbsorbedByFlashFire(enum BattlerId battlerDef)
{
    if (!gBattleMons[battlerDef].volatiles.flashFireBoosted)
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FLASH_FIRE_BOOST;
        gBattleMons[battlerDef].volatiles.flashFireBoosted = TRUE;
        return BattleScript_FlashFireBoost;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FLASH_FIRE_NO_BOOST;
        return BattleScript_FlashFireBoost;
    }
}

static u32 GetFirstBattlerOnSide(enum BattleSide side)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (GetBattlerSide(battler) == side && !IsBattlerAlive(battler))
            return battler;
    }

    return GetBattlerAtPosition(side == B_SIDE_PLAYER ? B_POSITION_PLAYER_LEFT : B_POSITION_OPPONENT_LEFT);
}

static inline bool32 SetStartingFieldStatus(u32 flag, u32 message, u32 anim, u16 *timer, u16 time)
{
    if (!(gFieldStatuses & flag))
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = message;
        if (STATUS_FIELD_TERRAIN_ANY & flag)
            gFieldStatuses &= ~STATUS_FIELD_TERRAIN_ANY;
        gFieldStatuses |= flag;
        gBattleScripting.animArg1 = anim;
        *timer = time;

        return TRUE;
    }

    return FALSE;
}

static inline bool32 SetStartingSideStatus(u32 flag, enum BattleSide side, u32 message, u32 anim, u16 *timer, u16 time)
{
    if (!(gSideStatuses[side] & flag))
    {
        gBattlerAttacker = gBattlerTarget = (enum BattlerId)side;
        gBattleCommunication[MULTISTRING_CHOOSER] = message;
        gSideStatuses[side] |= flag;
        gBattleScripting.animArg1 = anim;
        *timer = time;

        return TRUE;
    }

    return FALSE;
}

static bool32 SetStartingHazardStatus(enum Hazards hazard, u32 targetSide, u8 layers, enum StartingStatusStringID messageId)
{
    bool32 effect = FALSE;
    u32 setterSide = (targetSide == B_SIDE_PLAYER) ? B_SIDE_OPPONENT : B_SIDE_PLAYER;

    switch (hazard)
    {
    case HAZARDS_SPIKES:
        if (layers != 0)
        {
            if (!IsHazardOnSide(targetSide, HAZARDS_SPIKES))
                PushHazardTypeToQueue(targetSide, HAZARDS_SPIKES);
            gSideTimers[targetSide].spikesAmount = layers;
            effect = TRUE;
        }
        break;
    case HAZARDS_TOXIC_SPIKES:
        if (layers != 0)
        {
            if (!IsHazardOnSide(targetSide, HAZARDS_TOXIC_SPIKES))
                PushHazardTypeToQueue(targetSide, HAZARDS_TOXIC_SPIKES);
            gSideTimers[targetSide].toxicSpikesAmount = layers;
            effect = TRUE;
        }
        break;
    case HAZARDS_STICKY_WEB:
        if (!IsHazardOnSide(targetSide, HAZARDS_STICKY_WEB))
        {
            PushHazardTypeToQueue(targetSide, HAZARDS_STICKY_WEB);
            gSideTimers[targetSide].stickyWebBattlerId = 0xFF;
            gSideTimers[targetSide].stickyWebBattlerSide = setterSide;
            effect = TRUE;
        }
        break;
    case HAZARDS_STEALTH_ROCK:
        if (!IsHazardOnSide(targetSide, HAZARDS_STEALTH_ROCK))
        {
            PushHazardTypeToQueue(targetSide, HAZARDS_STEALTH_ROCK);
            effect = TRUE;
        }
        break;
    case HAZARDS_STEELSURGE:
        if (!IsHazardOnSide(targetSide, HAZARDS_STEELSURGE))
        {
            PushHazardTypeToQueue(targetSide, HAZARDS_STEELSURGE);
            effect = TRUE;
        }
        break;
    case HAZARDS_NONE:
    case HAZARDS_MAX_COUNT:
        break;
    }

    if (effect)
    {
        gBattlerAttacker = GetFirstBattlerOnSide(setterSide);
        gBattleScripting.battler = gBattlerAttacker;
        gBattlerTarget = GetFirstBattlerOnSide(targetSide);
        gBattleCommunication[MULTISTRING_CHOOSER] = messageId;
        BattleScriptPushCursorAndCallback(BattleScript_OverworldHazard);
    }

    return effect;
}

bool32 TryFieldEffects(enum FieldEffectCases caseId)
{
    bool32 effect = FALSE;
    bool32 isTerrain = FALSE;

    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return FALSE;

    switch (caseId)
    {
    case FIELD_EFFECT_TRAINER_STATUSES:  // starting field/side/etc statuses with a variable
        if (gStartingStatuses.electricTerrain || gStartingStatuses.electricTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_ELECTRIC_TERRAIN,
                        B_MSG_TERRAIN_SET_ELECTRIC,
                        0,
                        &gFieldTimers.terrainTimer, gStartingStatuses.electricTerrain ? 0 : 5);
            gStartingStatuses.electricTerrainTemporary = gStartingStatuses.electricTerrain = FALSE;
            isTerrain = TRUE;
            if (effect)
            {
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                return TRUE;
            }
        }
        else if (gStartingStatuses.mistyTerrain || gStartingStatuses.mistyTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_MISTY_TERRAIN,
                        B_MSG_TERRAIN_SET_MISTY,
                        0,
                        &gFieldTimers.terrainTimer, gStartingStatuses.mistyTerrain ? 0 : 5);
            gStartingStatuses.mistyTerrainTemporary = gStartingStatuses.mistyTerrain = FALSE;
            isTerrain = TRUE;
            if (effect)
            {
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                return TRUE;
            }
        }
        else if (gStartingStatuses.grassyTerrain || gStartingStatuses.grassyTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_GRASSY_TERRAIN,
                        B_MSG_TERRAIN_SET_GRASSY,
                        0,
                        &gFieldTimers.terrainTimer, gStartingStatuses.grassyTerrain ? 0 : 5);
            gStartingStatuses.grassyTerrainTemporary = gStartingStatuses.grassyTerrain = FALSE;
            isTerrain = TRUE;
            if (effect)
            {
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                return TRUE;
            }
        }
        else if (gStartingStatuses.psychicTerrain || gStartingStatuses.psychicTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_PSYCHIC_TERRAIN,
                        B_MSG_TERRAIN_SET_PSYCHIC,
                        0,
                        &gFieldTimers.terrainTimer, gStartingStatuses.psychicTerrain ? 0 : 5);
            gStartingStatuses.psychicTerrainTemporary = gStartingStatuses.psychicTerrain = FALSE;
            isTerrain = TRUE;
        }
        else if (gStartingStatuses.scorchedField || gStartingStatuses.scorchedFieldTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_SCORCHED_FIELD,
                        B_MSG_TERRAIN_SET_SCORCHED,
                        0,
                        &gFieldTimers.terrainTimer, gStartingStatuses.scorchedField ? 0 : 5);
            gStartingStatuses.scorchedFieldTemporary = gStartingStatuses.scorchedField = FALSE;
            isTerrain = TRUE;
        }
        else if (gStartingStatuses.trickRoom || gStartingStatuses.trickRoomTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_TRICK_ROOM,
                        B_MSG_SET_TRICK_ROOM,
                        B_ANIM_TRICK_ROOM,
                        &gFieldTimers.trickRoomTimer, gStartingStatuses.trickRoom ? 0 : 5);
            gStartingStatuses.trickRoomTemporary = gStartingStatuses.trickRoom = FALSE;
        }
        else if (gStartingStatuses.magicRoom || gStartingStatuses.magicRoomTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_MAGIC_ROOM,
                        B_MSG_SET_MAGIC_ROOM,
                        B_ANIM_MAGIC_ROOM,
                        &gFieldTimers.magicRoomTimer, gStartingStatuses.magicRoom ? 0 : 5);
            gStartingStatuses.magicRoomTemporary = gStartingStatuses.magicRoom = FALSE;
        }
        else if (gStartingStatuses.wonderRoom || gStartingStatuses.wonderRoomTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_WONDER_ROOM,
                        B_MSG_SET_WONDER_ROOM,
                        B_ANIM_WONDER_ROOM,
                        &gFieldTimers.wonderRoomTimer,  gStartingStatuses.wonderRoom ? 0 : 5);
            gStartingStatuses.wonderRoomTemporary = gStartingStatuses.wonderRoom = FALSE;
        }
        else if (gStartingStatuses.tailwindPlayer || gStartingStatuses.tailwindPlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_TAILWIND,
                        B_SIDE_PLAYER,
                        B_MSG_SET_TAILWIND,
                        B_ANIM_TAILWIND,
                        &gSideTimers[B_SIDE_PLAYER].tailwindTimer, gStartingStatuses.tailwindPlayer ? 0 : (B_TAILWIND_TURNS >= GEN_5 ? 4 : 3));
            gStartingStatuses.tailwindPlayerTemporary = gStartingStatuses.tailwindPlayer = FALSE;
        }
        else if (gStartingStatuses.tailwindOpponent || gStartingStatuses.tailwindOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_TAILWIND,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_TAILWIND,
                        B_ANIM_TAILWIND,
                        &gSideTimers[B_SIDE_OPPONENT].tailwindTimer, gStartingStatuses.tailwindOpponent ? 0 : (B_TAILWIND_TURNS >= GEN_5 ? 4 : 3));
            gStartingStatuses.tailwindOpponentTemporary = gStartingStatuses.tailwindOpponent = FALSE;
        }
        else if (gStartingStatuses.rainbowPlayer || gStartingStatuses.rainbowPlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_RAINBOW,
                        B_SIDE_PLAYER,
                        B_MSG_SET_RAINBOW,
                        B_ANIM_RAINBOW,
                        &gSideTimers[B_SIDE_PLAYER].rainbowTimer, gStartingStatuses.rainbowPlayer ? 0 : 4);
            gStartingStatuses.rainbowPlayerTemporary = gStartingStatuses.rainbowPlayer = FALSE;
        }
        else if (gStartingStatuses.rainbowOpponent || gStartingStatuses.rainbowOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_RAINBOW,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_RAINBOW,
                        B_ANIM_RAINBOW,
                        &gSideTimers[B_SIDE_OPPONENT].rainbowTimer, gStartingStatuses.rainbowOpponent ? 0 : 4);
            gStartingStatuses.rainbowOpponentTemporary = gStartingStatuses.rainbowOpponent = FALSE;
        }
        else if (gStartingStatuses.seaOfFirePlayer || gStartingStatuses.seaOfFirePlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SEA_OF_FIRE,
                        B_SIDE_PLAYER,
                        B_MSG_SET_SEA_OF_FIRE,
                        B_ANIM_SEA_OF_FIRE,
                        &gSideTimers[B_SIDE_PLAYER].seaOfFireTimer, gStartingStatuses.seaOfFirePlayer ? 0 : 4);
            gStartingStatuses.seaOfFirePlayerTemporary = gStartingStatuses.seaOfFirePlayer = FALSE;
        }
        else if (gStartingStatuses.seaOfFireOpponent || gStartingStatuses.seaOfFireOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SEA_OF_FIRE,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_SEA_OF_FIRE,
                        B_ANIM_SEA_OF_FIRE,
                        &gSideTimers[B_SIDE_OPPONENT].seaOfFireTimer, gStartingStatuses.seaOfFireOpponent ? 0 : 4);
            gStartingStatuses.seaOfFireOpponentTemporary = gStartingStatuses.seaOfFireOpponent = FALSE;
        }
        else if (gStartingStatuses.swampPlayer || gStartingStatuses.swampPlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SWAMP,
                        B_SIDE_PLAYER,
                        B_MSG_SET_SWAMP,
                        B_ANIM_SWAMP,
                        &gSideTimers[B_SIDE_PLAYER].swampTimer, gStartingStatuses.swampPlayer ? 0 : 4);
            gStartingStatuses.swampPlayerTemporary = gStartingStatuses.swampPlayer = FALSE;
        }
        else if (gStartingStatuses.swampOpponent || gStartingStatuses.swampOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SWAMP,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_SWAMP,
                        B_ANIM_SWAMP,
                        &gSideTimers[B_SIDE_OPPONENT].swampTimer, gStartingStatuses.swampOpponent ? 0 : 4);
            gStartingStatuses.swampOpponentTemporary = gStartingStatuses.swampOpponent = FALSE;
        }
        // Hazards - Spikes
        else if (gStartingStatuses.spikesPlayerL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_PLAYER, 1, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesPlayerL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesPlayerL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_PLAYER, 2, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesPlayerL2 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesPlayerL3)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_PLAYER, 3, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesPlayerL3 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesOpponentL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_OPPONENT, 1, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesOpponentL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesOpponentL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_OPPONENT, 2, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesOpponentL2 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesOpponentL3)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_OPPONENT, 3, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesOpponentL3 = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Toxic Spikes
        else if (gStartingStatuses.toxicSpikesPlayerL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_PLAYER, 1, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesPlayerL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.toxicSpikesPlayerL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_PLAYER, 2, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesPlayerL2 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.toxicSpikesOpponentL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_OPPONENT, 1, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesOpponentL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.toxicSpikesOpponentL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_OPPONENT, 2, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesOpponentL2 = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Sticky Web
        else if (gStartingStatuses.stickyWebPlayer)
        {
            effect = SetStartingHazardStatus(HAZARDS_STICKY_WEB, B_SIDE_PLAYER, 1, B_MSG_SET_STICKY_WEB);
            gStartingStatuses.stickyWebPlayer = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.stickyWebOpponent)
        {
            effect = SetStartingHazardStatus(HAZARDS_STICKY_WEB, B_SIDE_OPPONENT, 1, B_MSG_SET_STICKY_WEB);
            gStartingStatuses.stickyWebOpponent = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Stealth Rock
        else if (gStartingStatuses.stealthRockPlayer)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEALTH_ROCK, B_SIDE_PLAYER, 1, B_MSG_SET_STEALTH_ROCK);
            gStartingStatuses.stealthRockPlayer = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.stealthRockOpponent)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEALTH_ROCK, B_SIDE_OPPONENT, 1, B_MSG_SET_STEALTH_ROCK);
            gStartingStatuses.stealthRockOpponent = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Steelsurge
        else if (gStartingStatuses.sharpSteelPlayer)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEELSURGE, B_SIDE_PLAYER, 1, B_MSG_SET_SHARP_STEEL);
            gStartingStatuses.sharpSteelPlayer = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.sharpSteelOpponent)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEELSURGE, B_SIDE_OPPONENT, 1, B_MSG_SET_SHARP_STEEL);
            gStartingStatuses.sharpSteelOpponent = FALSE;
            if (effect)
                return TRUE;
        }
        if (effect)
        {
            if (isTerrain)
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            else
                BattleScriptPushCursorAndCallback(BattleScript_OverworldStatusStarts);
        }

        break;
    case FIELD_EFFECT_OVERWORLD_TERRAIN:   // terrain starting from overworld weather
        if (B_THUNDERSTORM_TERRAIN == TRUE
         && !(gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
         && GetCurrentWeather() == WEATHER_RAIN_THUNDERSTORM)
        {
            // overworld weather started rain, so just do electric terrain anim
            gFieldStatuses = STATUS_FIELD_ELECTRIC_TERRAIN;
            gFieldTimers.terrainTimer = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_TERRAIN_SET_ELECTRIC;
            BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            effect = TRUE;
        }
        else if (B_OVERWORLD_FOG >= GEN_8
              && (GetCurrentWeather() == WEATHER_FOG_HORIZONTAL || GetCurrentWeather() == WEATHER_FOG_DIAGONAL)
              && !(gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN))
        {
            gFieldStatuses = STATUS_FIELD_MISTY_TERRAIN;
            gFieldTimers.terrainTimer = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_TERRAIN_SET_MISTY;
            BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            effect = TRUE;
        }
        break;
    case FIELD_EFFECT_OVERWORLD_WEATHER:
        if (!(gBattleTypeFlags & BATTLE_TYPE_RECORDED))
        {
            switch (GetCurrentWeather())
            {
            case WEATHER_RAIN:
            case WEATHER_RAIN_THUNDERSTORM:
            case WEATHER_DOWNPOUR:
                if (!(gBattleWeather & B_WEATHER_RAIN))
                {
                    gBattleWeather = B_WEATHER_RAIN_NORMAL;
                    gBattleScripting.animArg1 = B_ANIM_RAIN_CONTINUES;
                    effect = TRUE;
                }
                break;
            case WEATHER_SANDSTORM:
                if (!(gBattleWeather & B_WEATHER_SANDSTORM))
                {
                    gBattleWeather = B_WEATHER_SANDSTORM;
                    gBattleScripting.animArg1 = B_ANIM_SANDSTORM_CONTINUES;
                    effect = TRUE;
                }
                break;
            case WEATHER_DROUGHT:
                if (!(gBattleWeather & B_WEATHER_SUN))
                {
                    gBattleWeather = B_WEATHER_SUN_NORMAL;
                    gBattleScripting.animArg1 = B_ANIM_SUN_CONTINUES;
                    effect = TRUE;
                }
                break;
            case WEATHER_SNOW:
                if (!(gBattleWeather & B_WEATHER_ICY_ANY))
                {
                    if (B_OVERWORLD_SNOW >= GEN_9)
                    {
                        gBattleWeather = B_WEATHER_SNOW;
                        gBattleScripting.animArg1 = B_ANIM_SNOW_CONTINUES;
                    }
                    else
                    {
                        gBattleWeather = B_WEATHER_HAIL;
                        gBattleScripting.animArg1 = B_ANIM_HAIL_CONTINUES;
                    }
                    effect = TRUE;
                }
                break;
            case WEATHER_FOG_DIAGONAL:
            case WEATHER_FOG_HORIZONTAL:
                if (B_OVERWORLD_FOG == GEN_4 && !(gBattleWeather & B_WEATHER_FOG))
                {
                    gBattleWeather = B_WEATHER_FOG;
                    gBattleScripting.animArg1 = B_ANIM_FOG_CONTINUES;
                    effect = TRUE;
                }
                break;
            }
        }
        if (effect)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = GetCurrentWeather();
            BattleScriptPushCursorAndCallback(BattleScript_OverworldWeatherStarts);
        }
        break;
    }

    return effect;
}

static bool32 IsRestrictedAbility(enum BattlerId battler, enum Ability ability)
{
    return GetSpeciesAbility(gBattleMons[battler].species, 0) == ability
        || GetSpeciesAbility(gBattleMons[battler].species, 1) == ability
        || GetSpeciesAbility(gBattleMons[battler].species, 2) == ability;
}

u32 AbilityBattleEffects(enum AbilityEffect caseID, enum BattlerId battler, enum Move move, bool32 shouldAbilityTrigger)
{
    u32 effect = 0;
    enum Type moveType = 0;
    u32 side = 0;
    u32 i = 0, j = 0;
    u32 partner = BATTLE_PARTNER(battler);
    enum Ability ability = ABILITY_NONE;

    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battler);
    u8 slot;
    u32 speciesForm = SPECIES_NONE;

    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return 0;

    if (gBattlerAttacker >= gBattlersCount)
        gBattlerAttacker = battler;

    //Default as a redundancy (Multi)
    gLastUsedAbility = GetBattlerAbility(battler);

    if (move == MOVE_NONE)
        move = gCurrentMove;

    moveType = GetBattleMoveType(move);

    switch (caseID)
    {
    case ABILITYEFFECT_ON_SWITCHIN:
        gBattleScripting.battler = battler;
        u8 traitCheck = ABILITY_NONE;

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TRACE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] )
        {
            if (traitCheck > 1)
            {
                // Trace replaces your main Ability, so it generally should not be an Innate.
                DebugPrintf("Trace not set as main Ability");
            }
            else
            {
                enum BattlerId chosenTarget;
                enum BattlerId target1;
                enum BattlerId target2;

                if (BattlerHasHeldItemEffectIgnoreAbility(battler, HOLD_EFFECT_ABILITY_SHIELD, TRUE))
                    break;

                side = (BATTLE_OPPOSITE(GetBattlerPosition(battler))) & BIT_SIDE;
                target1 = GetBattlerAtPosition(side);
                target2 = GetBattlerAtPosition(side + BIT_FLANK);
                if (IsDoubleBattle())
                {
                    if (!gAbilitiesInfo[gBattleMons[target1].ability].cantBeTraced && gBattleMons[target1].hp != 0
                    && !gAbilitiesInfo[gBattleMons[target2].ability].cantBeTraced && gBattleMons[target2].hp != 0)
                        chosenTarget = GetBattlerAtPosition((RandomPercentage(RNG_TRACE, 50) * 2) | side), effect++;
                    else if (!gAbilitiesInfo[gBattleMons[target1].ability].cantBeTraced && gBattleMons[target1].hp != 0)
                        chosenTarget = target1, effect++;
                    else if (!gAbilitiesInfo[gBattleMons[target2].ability].cantBeTraced && gBattleMons[target2].hp != 0)
                        chosenTarget = target2, effect++;
                }
                else
                {
                    if (!gAbilitiesInfo[gBattleMons[target1].ability].cantBeTraced && gBattleMons[target1].hp != 0)
                        chosenTarget = target1, effect++;
                }
                if (effect != 0)
                {
                    //SwitchinTraitDone not set to True so that Traced switchin abilities like Intimidate can still activate
                    PushTraitStack(battler, ABILITY_TRACE);
                    BattleScriptCall(BattleScript_TraceActivates);
                    gBattleStruct->tracedAbility[battler] = gLastUsedAbility = gBattleMons[chosenTarget].ability;
                    RecordAbilityBattle(chosenTarget, gLastUsedAbility); // Record the opposing battler has this ability
                    PREPARE_MON_NICK_WITH_PREFIX_LOWER_BUFFER(gBattleTextBuff1, chosenTarget, gBattlerPartyIndexes[chosenTarget])
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff2, gLastUsedAbility)
                }
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_IMPOSTER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1])
            if (gBattleStruct->battlerState[battler].switchIn)
        {
            enum BattlerId diagonalBattler = BATTLE_OPPOSITE(battler);
            if (IsDoubleBattle())
                diagonalBattler = BATTLE_PARTNER(diagonalBattler);

            // Imposter only activates when the battler first switches in
            if(!gBattleMons[battler].volatiles.overwrittenAbility
             && IsBattlerAlive(diagonalBattler)
             && !gBattleMons[diagonalBattler].volatiles.substitute
             && !gBattleMons[diagonalBattler].volatiles.transformed
             && !gBattleMons[battler].volatiles.transformed
             && gBattleStruct->illusion[diagonalBattler].state != ILLUSION_ON
             && !IsSemiInvulnerable(diagonalBattler, EXCLUDE_COMMANDER))
            {
                SaveBattlerAttacker(gBattlerAttacker);
                SaveBattlerTarget(gBattlerTarget);
                gBattlerAttacker = battler;
                gBattlerTarget = diagonalBattler;
                effect += CommonSwitchInAbilities(battler, ABILITY_IMPOSTER, traitCheck, BattleScript_ImposterActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_INTIMIDATE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = battler;
            effect += CommonSwitchInAbilities(battler, ABILITY_INTIMIDATE, traitCheck, BattleScript_IntimidateActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_INFERNAL)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = battler;
            effect += CommonSwitchInAbilities(battler, ABILITY_INFERNAL, traitCheck, BattleScript_InfernalActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_POLARITY_SHIFT)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            enum BattlerId target = GetOppositeSideShiftTarget(battler);

            if (target < gBattlersCount)
            {
                u32 temp;

                SWAP(gBattleMons[battler].speed, gBattleMons[target].speed, temp);
                SaveBattlerAttacker(gBattlerAttacker);
                SaveBattlerTarget(gBattlerTarget);
                gBattlerAttacker = battler;
                gBattlerTarget = target;
                effect += CommonSwitchInAbilities(battler, ABILITY_POLARITY_SHIFT, traitCheck, BattleScript_PolarityShiftActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_POWER_SHIFT)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            enum BattlerId target = GetOppositeSideShiftTarget(battler);

            if (target < gBattlersCount)
            {
                u32 temp;

                SWAP(gBattleMons[battler].attack, gBattleMons[target].attack, temp);
                SWAP(gBattleMons[battler].spAttack, gBattleMons[target].spAttack, temp);
                SaveBattlerAttacker(gBattlerAttacker);
                SaveBattlerTarget(gBattlerTarget);
                gBattlerAttacker = battler;
                gBattlerTarget = target;
                effect += CommonSwitchInAbilities(battler, ABILITY_POWER_SHIFT, traitCheck, BattleScript_PowerShiftActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_WISHMAKER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && gBattleStruct->wish[battler].counter == 0)
        {
            gBattleStruct->wish[battler].counter = 2;
            gBattleStruct->wish[battler].partyId = gBattlerPartyIndexes[battler];
            SaveBattlerAttacker(gBattlerAttacker);
            SaveBattlerTarget(gBattlerTarget);
            gBattlerAttacker = battler;
            gBattlerTarget = battler;
            effect += CommonSwitchInAbilities(battler, ABILITY_WISHMAKER, traitCheck, BattleScript_WishmakerActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_UNCANNY)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            PushTraitStack(battler, ABILITY_UNCANNY);
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = battler;
            effect += CommonSwitchInAbilities(battler, ABILITY_UNCANNY, traitCheck, BattleScript_UncannyActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_BREAKING_PRESENCE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = battler;
            effect += CommonSwitchInAbilities(battler, ABILITY_BREAKING_PRESENCE, traitCheck, BattleScript_BreakingPresenceActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_DISQUIET)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = battler;
            effect += CommonSwitchInAbilities(battler, ABILITY_DISQUIET, traitCheck, BattleScript_DisquietActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_HOBBLE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !IsOpposingSideEmpty(battler))
        {
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = battler;
            effect += CommonSwitchInAbilities(battler, ABILITY_HOBBLE, traitCheck, BattleScript_HobbleActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SUPERSWEET_SYRUP)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !GetBattlerPartyState(battler)->supersweetSyrup
         && !IsOpposingSideEmpty(battler))
        {
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = battler;
            GetBattlerPartyState(battler)->supersweetSyrup = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_SUPERSWEET_SYRUP, traitCheck, BattleScript_SupersweetSyrupActivates);
        }
        // Only one Mold Breaker type move needs to activate
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TERAVOLT)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_TERAVOLT, traitCheck, BattleScript_TeravoltActivates);
        else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TURBOBLAZE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_TURBOBLAZE, traitCheck, BattleScript_TurboblazeActivates);
        else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_MOLD_BREAKER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_MOLD_BREAKER, traitCheck, BattleScript_MoldBreakerActivates);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SLOW_START)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gBattleMons[battler].volatiles.slowStartTimer = B_SLOW_START_TIMER;
            effect += CommonSwitchInAbilities(battler, ABILITY_SLOW_START, traitCheck, BattleScript_SlowStartActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_CURIOUS_MEDICINE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && IsDoubleBattle() 
         && IsBattlerAlive(BATTLE_PARTNER(battler))
         && TryResetBattlerStatChanges(BATTLE_PARTNER(battler)))
        {
            gEffectBattler = BATTLE_PARTNER(battler);
            effect += CommonSwitchInAbilities(battler, ABILITY_CURIOUS_MEDICINE, traitCheck, BattleScript_CuriousMedicineActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_PASTEL_VEIL)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            SaveBattlerTarget(gBattlerTarget);
            gBattlerTarget = battler;
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON)
             || gBattleMons[partner].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON)) // Only adds to the popup stack if there is poison to cure.
                PushTraitStack(battler, ABILITY_PASTEL_VEIL);
            BattleScriptCall(BattleScript_PastelVeilActivates);
            effect++;
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_ANTICIPATION)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            bool32 anticipationCheck = FALSE;
            struct BattleContext ctx = {0};
            uq4_12_t modifier = UQ_4_12(1.0);
            for (i = 0; i < MAX_BATTLERS_COUNT; i++)
            {
                if (IsBattlerAlive(i) && !IsBattlerAlly(i, battler))
                {
                    for (j = 0; j < MAX_MON_MOVES; j++)
                    {
                        move = gBattleMons[i].moves[j];
                        enum BattleMoveEffects moveEffect = GetMoveEffect(move);
                        moveType = GetBattleMoveType(move);

                            ctx.battlerAtk = i;
                            ctx.battlerDef = battler;
                            ctx.move = ctx.chosenMove = move;
                            ctx.moveType = moveType;
                            ctx.isAnticipation = TRUE;
                            modifier = CalcTypeEffectivenessMultiplier(&ctx);

                            if (modifier >= UQ_4_12(2.0) || moveEffect == EFFECT_OHKO)
                        {
                            anticipationCheck = TRUE;
                            effect++;
                            break;
                        }
                    }
                }
            }

            if (anticipationCheck)
                CommonSwitchInAbilities(battler, ABILITY_ANTICIPATION, traitCheck, BattleScript_AnticipationActivates); // effect++ already called, so it is not incremented again here
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_FRISK)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            effect += CommonSwitchInAbilities(battler, ABILITY_FRISK, traitCheck, BattleScript_FriskActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_FOREWARN)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && !IsOpposingSideEmpty(battler))
        {
            ForewarnChooseMove(battler);
            effect += CommonSwitchInAbilities(battler, ABILITY_FOREWARN, traitCheck, BattleScript_ForewarnActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_DOWNLOAD)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            enum Stat statId;
            enum BattlerId opposingBattler;
            u32 opposingDef = 0, opposingSpDef = 0;

            opposingBattler = BATTLE_OPPOSITE(battler);
            for (i = 0; i < 2; opposingBattler ^= BIT_FLANK, i++)
            {
                if (IsBattlerAlive(opposingBattler))
                {
                    opposingDef += gBattleMons[opposingBattler].defense
                                * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][0]
                                / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][1];
                    opposingSpDef += gBattleMons[opposingBattler].spDefense
                                  * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][0]
                                  / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][1];
                }
            }

            if (opposingDef < opposingSpDef)
                statId = STAT_ATK;
            else
                statId = STAT_SPATK;

            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                SET_STATCHANGER(statId, 1, FALSE);
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
                PushTraitStack(battler, ABILITY_DOWNLOAD);
                BattleScriptCall(BattleScript_AttackerDownloadStatRaise);
                effect++;
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_PRESSURE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_PRESSURE, traitCheck, BattleScript_PressureActivates);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_DARK_AURA)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_DARK_AURA, traitCheck, BattleScript_DarkAuraActivates);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_FAIRY_AURA)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_FAIRY_AURA, traitCheck, BattleScript_FairyAuraActivates);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_AURA_BREAK)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_AURA_BREAK, traitCheck, BattleScript_AuraBreakActivates);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_COMATOSE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_COMATOSE, traitCheck, BattleScript_ComatoseActivates);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SCREEN_CLEANER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && TryRemoveScreens(battler))
            effect += CommonSwitchInAbilities(battler, ABILITY_SCREEN_CLEANER, traitCheck, BattleScript_ScreenCleanerActivates);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_DRIZZLE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_RAIN, TRUE))
                effect += CommonSwitchInAbilities(battler, ABILITY_DRIZZLE, traitCheck, BattleScript_DrizzleActivates);
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && HasWeatherEffect())
                effect += CommonSwitchInAbilities(battler, ABILITY_DRIZZLE, traitCheck, BattleScript_BlockedByPrimalWeather);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SAND_STREAM)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SANDSTORM, TRUE))
                effect += CommonSwitchInAbilities(battler, ABILITY_SAND_STREAM, traitCheck, BattleScript_SandstreamActivates);
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && HasWeatherEffect())
                effect += CommonSwitchInAbilities(battler, ABILITY_SAND_STREAM, traitCheck, BattleScript_BlockedByPrimalWeather);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_DROUGHT)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SUN, TRUE))
                effect += CommonSwitchInAbilities(battler, ABILITY_DROUGHT, traitCheck, BattleScript_DroughtActivates);
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && HasWeatherEffect())
                effect += CommonSwitchInAbilities(battler, ABILITY_DROUGHT, traitCheck, BattleScript_BlockedByPrimalWeather);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_HEATSTORM)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_SCORCHED_FIELD))
                effect += CommonSwitchInAbilities(battler, ABILITY_HEATSTORM, traitCheck, BattleScript_HeatstormActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_ORICHALCUM_PULSE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SUN, TRUE))
                effect += CommonSwitchInAbilities(battler, ABILITY_ORICHALCUM_PULSE, traitCheck, BattleScript_DroughtActivates);
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && HasWeatherEffect() && !gSpecialStatuses[battler].switchInAbilityDone) 
                effect += CommonSwitchInAbilities(battler, ABILITY_ORICHALCUM_PULSE, traitCheck, BattleScript_BlockedByPrimalWeather);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SNOW_WARNING)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            if (GetConfig(B_SNOW_WARNING) >= GEN_9 && TryChangeBattleWeather(battler, BATTLE_WEATHER_SNOW, TRUE))
                effect += CommonSwitchInAbilities(battler, ABILITY_SNOW_WARNING, traitCheck, BattleScript_SnowWarningActivatesSnow);
            else if (GetConfig(B_SNOW_WARNING) < GEN_9 && TryChangeBattleWeather(battler, BATTLE_WEATHER_HAIL, TRUE))
                effect += CommonSwitchInAbilities(battler, ABILITY_SNOW_WARNING, traitCheck, BattleScript_SnowWarningActivatesHail);
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && HasWeatherEffect())
                effect += CommonSwitchInAbilities(battler, ABILITY_SNOW_WARNING, traitCheck, BattleScript_BlockedByPrimalWeather);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_ELECTRIC_SURGE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if(TryChangeBattleTerrain(battler, STATUS_FIELD_ELECTRIC_TERRAIN))
                effect += CommonSwitchInAbilities(battler, ABILITY_ELECTRIC_SURGE, traitCheck, BattleScript_ElectricSurgeActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_HADRON_ENGINE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if(TryChangeBattleTerrain(battler, STATUS_FIELD_ELECTRIC_TERRAIN))
                effect += CommonSwitchInAbilities(battler, ABILITY_HADRON_ENGINE, traitCheck, BattleScript_ElectricSurgeActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_GRASSY_SURGE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if(TryChangeBattleTerrain(battler, STATUS_FIELD_GRASSY_TERRAIN))
                effect += CommonSwitchInAbilities(battler, ABILITY_GRASSY_SURGE, traitCheck, BattleScript_GrassySurgeActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_MISTY_SURGE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE; 
            if(TryChangeBattleTerrain(battler, STATUS_FIELD_MISTY_TERRAIN))
                effect += CommonSwitchInAbilities(battler, ABILITY_MISTY_SURGE, traitCheck, BattleScript_MistySurgeActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_PSYCHIC_SURGE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE; 
            if(TryChangeBattleTerrain(battler, STATUS_FIELD_PSYCHIC_TERRAIN))
                effect += CommonSwitchInAbilities(battler, ABILITY_PSYCHIC_SURGE, traitCheck, BattleScript_PsychicSurgeActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SHOWTIME)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (!(gFieldStatuses & STATUS_FIELD_TRICK_ROOM))
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gFieldStatuses |= STATUS_FIELD_TRICK_ROOM;
                gFieldTimers.trickRoomTimer = 5;
                effect += CommonSwitchInAbilities(battler, ABILITY_SHOWTIME, traitCheck, BattleScript_ShowtimeActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_GRAVITY_WELL)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gFieldStatuses |= STATUS_FIELD_GRAVITY;
                gFieldTimers.gravityTimer = 5;
                effect += CommonSwitchInAbilities(battler, ABILITY_GRAVITY_WELL, traitCheck, BattleScript_GravityWellActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_WINDBURST)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (!(gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gSideStatuses[GetBattlerSide(battler)] |= SIDE_STATUS_TAILWIND;
                gSideTimers[GetBattlerSide(battler)].tailwindTimer = (GetConfig(B_TAILWIND_TURNS) >= GEN_5 ? 4 : 3);
                effect += CommonSwitchInAbilities(battler, ABILITY_WINDBURST, traitCheck, BattleScript_WindburstActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_ROOTED)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (!gBattleMons[battler].volatiles.root)
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gBattleMons[battler].volatiles.root = TRUE;
                effect += CommonSwitchInAbilities(battler, ABILITY_ROOTED, traitCheck, BattleScript_RootedActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_RESTORING)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            if (!gBattleMons[battler].volatiles.aquaRing)
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gBattleMons[battler].volatiles.aquaRing = TRUE;
                effect += CommonSwitchInAbilities(battler, ABILITY_RESTORING, traitCheck, BattleScript_RestoringActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_CLOUD_NINE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_CLOUD_NINE, traitCheck, BattleScript_AnnounceAirLockCloudNine);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_AIR_LOCK)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
            effect += CommonSwitchInAbilities(battler, ABILITY_AIR_LOCK, traitCheck, BattleScript_AnnounceAirLockCloudNine);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TERAFORM_ZERO)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && gBattleMons[battler].species == SPECIES_TERAPAGOS_STELLAR)
            effect += CommonSwitchInAbilities(battler, ABILITY_TERAFORM_ZERO, traitCheck, BattleScript_ActivateTeraformZero);

        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_INTREPID_SWORD)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && !GetBattlerPartyState(battler)->intrepidSwordBoost)
        {
            if (GetConfig(B_INTREPID_SWORD) == GEN_9)
                GetBattlerPartyState(battler)->intrepidSwordBoost = TRUE;

            if (CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                effect += CommonSwitchInAbilities(battler, ABILITY_INTREPID_SWORD, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInIntrepid);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_DAUNTLESS_SHIELD)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && !GetBattlerPartyState(battler)->dauntlessShieldBoost)
        {
            if (GetConfig(B_DAUNTLESS_SHIELD) == GEN_9)
                GetBattlerPartyState(battler)->dauntlessShieldBoost = TRUE;

            if (CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
                effect += CommonSwitchInAbilities(battler, ABILITY_DAUNTLESS_SHIELD, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInDauntless);
        }
        effect += TrySwitchInStatRaiseAbility(battler, battlerTraits, ABILITY_BATTLE_FERVOR, STAT_ATK, shouldAbilityTrigger);
        effect += TrySwitchInStatRaiseAbility(battler, battlerTraits, ABILITY_GUARD_STANCE, STAT_DEF, shouldAbilityTrigger);
        effect += TrySwitchInStatRaiseAbility(battler, battlerTraits, ABILITY_MENTAL_SURGE, STAT_SPATK, shouldAbilityTrigger);
        effect += TrySwitchInStatRaiseAbility(battler, battlerTraits, ABILITY_RESOLUTE_GUARD, STAT_SPDEF, shouldAbilityTrigger);
        effect += TrySwitchInStatRaiseAbility(battler, battlerTraits, ABILITY_SKIP_STEP, STAT_SPEED, shouldAbilityTrigger);
        effect += TrySwitchInStatRaiseAbility(battler, battlerTraits, ABILITY_GLACIAL, STAT_SPDEF, shouldAbilityTrigger);
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SHOCKWIRING)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gBattleMons[battler].volatiles.chargeTimer = 2;
            effect += CommonSwitchInAbilities(battler, ABILITY_SHOCKWIRING, traitCheck, BattleScript_ShockwiringActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_WIND_RIDER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN)
         && gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND)
        {
            effect += CommonSwitchInAbilities(battler, ABILITY_WIND_RIDER, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInWindRider);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_WIND_CHIME)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN)
         && gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND)
        {
            effect += CommonSwitchInAbilities(battler, ABILITY_WIND_CHIME, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInWindChime);
        }
        if (SearchTraits(battlerTraits, ABILITY_DESOLATE_LAND)
         && shouldAbilityTrigger
         && TryChangeBattleWeather(battler, BATTLE_WEATHER_SUN_PRIMAL, TRUE))
        {
            PushTraitStack(battler, ABILITY_DESOLATE_LAND);
            BattleScriptCall(BattleScript_DesolateLandActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_PRIMORDIAL_SEA)
         && shouldAbilityTrigger
         && TryChangeBattleWeather(battler, BATTLE_WEATHER_RAIN_PRIMAL, TRUE))
        {
            PushTraitStack(battler, ABILITY_PRIMORDIAL_SEA);
            BattleScriptCall(BattleScript_PrimordialSeaActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_DELTA_STREAM)
         && shouldAbilityTrigger
         && TryChangeBattleWeather(battler, BATTLE_WEATHER_STRONG_WINDS, TRUE))
        {
            PushTraitStack(battler, ABILITY_DELTA_STREAM);
            BattleScriptCall(BattleScript_DeltaStreamActivates);
            effect++;
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_VESSEL_OF_RUIN)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gBattleMons[battler].volatiles.vesselOfRuin = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_VESSEL_OF_RUIN, traitCheck, BattleScript_RuinAbilityActivatesVessel);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SWORD_OF_RUIN)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gBattleMons[battler].volatiles.swordOfRuin = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_SWORD_OF_RUIN, traitCheck, BattleScript_RuinAbilityActivatesSword);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TABLETS_OF_RUIN)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gBattleMons[battler].volatiles.tabletsOfRuin = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_TABLETS_OF_RUIN, traitCheck, BattleScript_RuinAbilityActivatesTablets);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_BEADS_OF_RUIN)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gBattleMons[battler].volatiles.beadsOfRuin = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_BEADS_OF_RUIN, traitCheck, BattleScript_RuinAbilityActivatesBeads);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SUPREME_OVERLORD)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            gBattleStruct->supremeOverlordCounter[battler] = min(5, GetBattlerSideFaintCounter(battler));
            if (gBattleStruct->supremeOverlordCounter[battler] > 0)
                effect += CommonSwitchInAbilities(battler, ABILITY_SUPREME_OVERLORD, traitCheck, BattleScript_SupremeOverlordActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_ZERO_TO_HERO) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1])
         && GetMonData(GetBattlerMon(battler), MON_DATA_SPECIES) == SPECIES_PALAFIN_HERO
         && !GetBattlerPartyState(battler)->transformZeroToHero)
        {
            if(!gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
             && GetMonData(GetBattlerMon(battler), MON_DATA_SPECIES) == SPECIES_PALAFIN_HERO
             && !GetBattlerPartyState(battler)->transformZeroToHero)
            {
                GetBattlerPartyState(battler)->transformZeroToHero = TRUE;
                effect += CommonSwitchInAbilities(battler, ABILITY_ZERO_TO_HERO, traitCheck, BattleScript_ZeroToHeroActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_EMBODY_ASPECT_TEAL_MASK)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_EQUAL))
        {
            effect += CommonSwitchInAbilities(battler, ABILITY_EMBODY_ASPECT_TEAL_MASK, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInEmbodyAspectTeal);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_EQUAL))
        {
            effect += CommonSwitchInAbilities(battler, ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInEmbodyAspectHearthFlame);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_EMBODY_ASPECT_WELLSPRING_MASK)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !CompareStat(battler, STAT_SPDEF, MAX_STAT_STAGE, CMP_EQUAL))
        {
            effect += CommonSwitchInAbilities(battler, ABILITY_EMBODY_ASPECT_WELLSPRING_MASK, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInEmbodyAspectWellSpring);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && !CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_EQUAL))
        {
            effect += CommonSwitchInAbilities(battler, ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK, traitCheck, BattleScript_BattlerAbilityStatRaiseOnSwitchInEmbodyAspectCornerStone);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_GLASS_CANNON)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            enum Stat offense = (gBattleMons[battler].spAttack > gBattleMons[battler].attack) ? STAT_SPATK : STAT_ATK;
            SET_STATCHANGER(offense, 2, FALSE);
            effect += CommonSwitchInAbilities(battler, ABILITY_GLASS_CANNON, traitCheck, BattleScript_GlassCannonActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_MAGNIFY_FIELD)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger)
        {
            bool32 extended = FALSE;

            if (IsFiniteWeatherActive())
            {
                gBattleStruct->weatherDuration = min(gBattleStruct->weatherDuration + 2, MAX_u8);
                extended = TRUE;
            }
            if (IsFiniteTerrainActive())
            {
                gFieldTimers.terrainTimer = min(gFieldTimers.terrainTimer + 2, MAX_u8);
                extended = TRUE;
            }
            if (extended)
                effect += CommonSwitchInAbilities(battler, ABILITY_MAGNIFY_FIELD, traitCheck, BattleScript_MagnifyFieldActivates);
            else
                gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_RALLY)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && IsDoubleBattle()
         && IsBattlerAlive(partner))
        {
            SET_STATCHANGER(GetBattlerHighestNonHpStat(partner), 1, FALSE);
            SaveBattlerTarget(gBattlerTarget);
            gBattlerTarget = partner;
            gBattleScripting.battler = battler;
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            PushTraitStack(battler, ABILITY_RALLY);
            BattleScriptCall(BattleScript_RallyActivates);
            effect++;
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TWIN_STARS)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && IsDoubleBattle()
         && IsBattlerAlive(partner)
         && BattlerHasTrait(partner, ABILITY_TWIN_STARS)
        && !GetBattlerPartyState(battler)->twinStarsBoosted
         && !GetBattlerPartyState(partner)->twinStarsBoosted)
        {
            GetBattlerPartyState(battler)->twinStarsBoosted = TRUE;
            GetBattlerPartyState(partner)->twinStarsBoosted = TRUE;
            SaveBattlerTarget(gBattlerTarget);
            gBattlerTarget = partner;
            gBattleScripting.battler = battler;
            gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1] = TRUE;
            PushTraitStack(battler, ABILITY_TWIN_STARS);
            BattleScriptCall(BattleScript_TwinStarsActivates);
            effect++;
        }
        break;
    case ABILITYEFFECT_SWITCH_IN_FORM_CHANGE:
    ability = ABILITY_NONE;

        if (BattlerHasTrait(battler, ABILITY_SCHOOLING))
            ability = ABILITY_SCHOOLING;
        else if (BattlerHasTrait(battler, ABILITY_SHIELDS_DOWN))
            ability = ABILITY_SHIELDS_DOWN;

        if (shouldAbilityTrigger && TryBattleFormChange(battler, FORM_CHANGE_BATTLE_HP_PERCENT_SEND_OUT))
        {
            gBattleScripting.battler = battler;
            // To prevent the new form's ability from pop up
            gBattleScripting.abilityPopupOverwrite = ability;
            PushTraitStack(battler, ability);
            BattleScriptCall(BattleScript_BattlerFormChange);
            effect++;
        }
        break;
    case ABILITYEFFECT_ENDTURN:
        if (IsBattlerAlive(battler))
        {
            u8 itemTraitType = 0;
            u8 itemTraitSlot = MAX_MON_ITEMS;
            gBattlerAttacker = battler;

            // Item abilities have additional conitions which might conflict with following Else statements
            // Harvest, Pickup, and Ball Fetch do their item availability checks first independantly
            // then just their activations are included in the If Else statements of the rest of the abilities.
            // If affecting the same slot at the same time, priority is Harvest, Pickup, Ball Fetch (Ball Fetch is last because it seeks an empty slot)

            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_HARVEST)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && itemTraitType == 0)
            {
                for (i = 0; i < MAX_MON_ITEMS; i++)
                {
                    if ((IsBattlerWeatherAffected(battler, B_WEATHER_SUN) || RandomPercentage(RNG_HARVEST, 50))
                     && gBattleMons[battler].items[i] == ITEM_NONE
                     && GetItemPocket(GetBattlerPartyState(battler)->usedHeldItems[i]) == POCKET_BERRIES)
                    {
                        itemTraitType = TRIGGER_HARVEST;
                        itemTraitSlot = i;
                        break;
                    }
                }
            }   
            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_PICKUP)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && itemTraitType == 0)
            {
                for (i = 0; i < MAX_MON_ITEMS; i++)
                {
                    if (gBattleMons[battler].items[i] == ITEM_NONE
                     && PickupHasValidTarget(battler))
                    {
                        itemTraitType = TRIGGER_PICKUP;
                        itemTraitSlot = i;
                        break;
                    }
                }
            }
            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_BALL_FETCH)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && itemTraitType == 0)
            {
                slot = MAX_MON_ITEMS;

                if (!(gBattleTypeFlags & BATTLE_TYPE_RAID))
                    slot = GetBattlerNextEmptySlot(battler, gLastUsedBall);
                
                if (gBattleResults.catchAttempts[ItemIdToBallId(gLastUsedBall)] >= 1
                 && !gHasFetchedBall
                 && slot != MAX_MON_ITEMS)
                {
                    itemTraitType = TRIGGER_BALL_FETCH;
                    itemTraitSlot = slot;
                }
            }
            
            if (itemTraitType != 0)
            {
                if (itemTraitType == TRIGGER_HARVEST)
                {
                    gLastUsedItem = GetBattlerPartyState(battler)->usedHeldItems[itemTraitSlot];
                    PushTraitStack(battler, ABILITY_HARVEST);
                    BattleScriptExecute(BattleScript_HarvestActivates);
                    effect++;
                    break;
                }
                else if (itemTraitType == TRIGGER_PICKUP)
                {
                    gSpecialStatuses[battler].endTurnTraitDone[SearchTraits(battlerTraits, ABILITY_PICKUP) - 1] = TRUE;
                    gBattlerTarget = RandomUniformExcept(RNG_PICKUP, 0, gBattlersCount - 1, CantPickupItem);
                    gLastUsedItem = GetBattlerPartyState(gBattlerTarget)->usedHeldItems[itemTraitSlot];
                    PushTraitStack(battler, ABILITY_PICKUP);
                    BattleScriptExecute(BattleScript_PickupActivates);
                    effect++;
                    break;
                }
                else if (itemTraitType == TRIGGER_BALL_FETCH)
                {
                    gSpecialStatuses[battler].endTurnTraitDone[SearchTraits(battlerTraits, ABILITY_BALL_FETCH) - 1] = TRUE;
                    gLastUsedItem = gLastUsedBall;
                    gBattleScripting.battler = battler;
                    gBattleMons[battler].items[itemTraitSlot] = gLastUsedItem;
                    BtlController_EmitSetMonData(battler, B_COMM_TO_CONTROLLER, REQUEST_HELDITEM_BATTLE + itemTraitSlot, 0, 2, &gLastUsedItem);
                    MarkBattlerForControllerExec(battler);
                    gHasFetchedBall = TRUE;
                    PushTraitStack(battler, ABILITY_BALL_FETCH);
                    BattleScriptExecute(BattleScript_BallFetch);
                    effect++;
                    break;
                }
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_ICE_BODY)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
            && IsBattlerWeatherAffected(battler, B_WEATHER_ICY_ANY)
            && !IsBattlerAtMaxHp(battler)
            && gBattleMons[battler].volatiles.semiInvulnerable != STATE_UNDERGROUND
            && gBattleMons[battler].volatiles.semiInvulnerable != STATE_UNDERWATER
            && !gBattleMons[battler].volatiles.healBlock)
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_ICE_BODY);
                BattleScriptExecute(BattleScript_IceBodyHeal);
                SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / 16);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_GLACIAL)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
            && IsBattlerWeatherAffected(battler, B_WEATHER_ICY_ANY)
            && !IsBattlerAtMaxHp(battler)
            && gBattleMons[battler].volatiles.semiInvulnerable != STATE_UNDERGROUND
            && gBattleMons[battler].volatiles.semiInvulnerable != STATE_UNDERWATER
            && !gBattleMons[battler].volatiles.healBlock)
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_GLACIAL);
                BattleScriptExecute(BattleScript_IceBodyHeal);
                SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / 8);
                effect++;
                break;
            }
            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_RAIN_DISH)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && IsBattlerWeatherAffected(battler, B_WEATHER_RAIN)
             && !IsBattlerAtMaxHp(battler)
             && !gBattleMons[battler].volatiles.healBlock)
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_RAIN_DISH);
                if (!SearchTraits(battlerTraits, ABILITY_DRY_SKIN))
                    SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / 16);
                else
                {
                    SetHealAmount(battler, GetNonDynamaxMaxHP(battler) * (0.187)); // Rain Dish + Dry Skin
                    gSpecialStatuses[battler].endTurnTraitDone[SearchTraits(battlerTraits, ABILITY_DRY_SKIN) - 1] = TRUE;
                }
                BattleScriptExecute(BattleScript_RainDishActivates);
                effect++;
                break;
            }
             else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SOLAR_POWER)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && IsBattlerWeatherAffected(battler, B_WEATHER_SUN))
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_SOLAR_POWER);
                if (!SearchTraits(battlerTraits, ABILITY_DRY_SKIN))
                    SetPassiveDamageAmount(battler, GetNonDynamaxMaxHP(battler) / 8);
                else
                {
                    SetPassiveDamageAmount(battler, GetNonDynamaxMaxHP(battler) / 4); // Solar Power + Dry Skin
                    gSpecialStatuses[battler].endTurnTraitDone[SearchTraits(battlerTraits, ABILITY_DRY_SKIN) - 1] = TRUE;
                }
                BattleScriptExecute(BattleScript_SolarPowerActivates);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_DRY_SKIN)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1])
            {
                if (IsBattlerWeatherAffected(battler, B_WEATHER_SUN) && !SearchTraits(battlerTraits, ABILITY_SOLAR_POWER)) // Damage stacking handled in Solar Power
                {
                    gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                    PushTraitStack(battler, ABILITY_DRY_SKIN);
                    SetPassiveDamageAmount(battler, GetNonDynamaxMaxHP(battler) / 8);
                    BattleScriptExecute(BattleScript_SolarPowerActivates);
                    effect++;
                    break;
                }
                else if (IsBattlerWeatherAffected(battler, B_WEATHER_RAIN) && !SearchTraits(battlerTraits, ABILITY_RAIN_DISH)) // Healing stacking handled in Rain Dish
                {
                    gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                    PushTraitStack(battler, ABILITY_DRY_SKIN);
                    SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / 8);
                    BattleScriptExecute(BattleScript_RainDishActivates);
                    effect++;
                    break;
                }
            }
            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_MENDING)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && RandomPercentage(RNG_MENDING, 30))
            {
                bool32 cured = (gBattleMons[battler].status1 & STATUS1_ANY) != 0;
                bool32 healed = !IsBattlerAtMaxHp(battler) && !gBattleMons[battler].volatiles.healBlock;

                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                if (cured || healed)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = (cured ? 1 : 0) | (healed ? 2 : 0);
                    if (healed)
                        SetHealAmount(battler, max(1, GetNonDynamaxMaxHP(battler) / 8));
                    PushTraitStack(battler, ABILITY_MENDING);
                    BattleScriptExecute(BattleScript_MendingActivates);
                    effect++;
                    break;
                }
            }
            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_CHANNEL_EARTH)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && (gFieldStatuses & STATUS_FIELD_TERRAIN_ANY))
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                if (!IsBattlerAtMaxHp(battler) && !gBattleMons[battler].volatiles.healBlock)
                {
                    SetHealAmount(battler, max(1, GetNonDynamaxMaxHP(battler) / 16));
                    PushTraitStack(battler, ABILITY_CHANNEL_EARTH);
                    BattleScriptExecute(BattleScript_RainDishActivates);
                    effect++;
                    break;
                }
            }
            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SPLINTER)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1])
            {
                enum BattlerId foe;

                for (foe = 0; foe < gBattlersCount; foe++)
                {
                    if (IsBattlerAlly(battler, foe)
                     || !(gProtectStructs[foe].revengeDoubled & (1u << battler)))
                        continue;

                    // One target is processed per pass so HP/controller updates and
                    // fainting finish before the next target is considered.
                    gProtectStructs[foe].revengeDoubled &= ~(1u << battler);
                    if (!IsBattlerAlive(foe) || IsAbilityAndRecord(foe, ABILITY_MAGIC_GUARD))
                        continue;

                    gBattlerAttacker = foe;
                    gBattlerTarget = battler;
                    gBattleScripting.battler = battler;
                    SetPassiveDamageAmount(foe, max(1, GetNonDynamaxMaxHP(foe) / 16));
                    PushTraitStack(battler, ABILITY_SPLINTER);
                    BattleScriptExecute(BattleScript_SplinterActivates);
                    effect++;
                    break;
                }

                if (effect)
                    break;
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
            }
            if ((traitCheck = SearchTraits(battlerTraits, ABILITY_HYDRATION)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && IsBattlerWeatherAffected(battler, B_WEATHER_RAIN)
             && gBattleMons[battler].status1 & STATUS1_ANY)
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_HYDRATION);
                goto ABILITY_HEAL_MON_STATUS;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SHED_SKIN)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && gBattleMons[battler].status1 & STATUS1_ANY
             && (GetConfig(B_ABILITY_TRIGGER_CHANCE) == GEN_4 ? RandomPercentage(RNG_SHED_SKIN, 30) : RandomChance(RNG_SHED_SKIN, 1, 3)))
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_SHED_SKIN);
                ABILITY_HEAL_MON_STATUS:
                    if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON))
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                    if (gBattleMons[battler].status1 & STATUS1_SLEEP)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                        TryDeactivateSleepClause(GetBattlerSide(battler), gBattlerPartyIndexes[battler]);
                    }

                    if (gBattleMons[battler].status1 & STATUS1_PARALYSIS)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                    if (gBattleMons[battler].status1 & STATUS1_BURN)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                    if (gBattleMons[battler].status1 & STATUS1_ICY_ANY)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);

                    gBattleMons[battler].status1 = 0;
                    gBattleMons[battler].volatiles.nightmare = FALSE;
                    gBattleScripting.battler = battler;
                    BattleScriptExecute(BattleScript_ShedSkinActivates);
                    BtlController_EmitSetMonData(battler, B_COMM_TO_CONTROLLER, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                    effect++;
                    break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_JADE_BLOOM)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && !(gBattleMons[battler].status1 & STATUS1_ANY))
            {
                bool32 canHeal = !IsBattlerAtMaxHp(battler) && !gBattleMons[battler].volatiles.healBlock;
                bool32 canRaiseSpAtk = CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN);
                bool32 canRaiseSpDef = CompareStat(battler, STAT_SPDEF, MAX_STAT_STAGE, CMP_LESS_THAN);

                if (canHeal || canRaiseSpAtk || canRaiseSpDef)
                {
                    enum Stat stat = STAT_SPATK;

                    gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                    SaveBattlerAttacker(gBattlerAttacker);
                    gBattleScripting.battler = gBattlerAbility = gBattlerAttacker = battler;
                    if (canRaiseSpAtk && canRaiseSpDef)
                        stat = RandomChance(RNG_JADE_BLOOM, 1, 2) ? STAT_SPATK : STAT_SPDEF;
                    else if (canRaiseSpDef)
                        stat = STAT_SPDEF;
                    SET_STATCHANGER(stat, 1, FALSE);
                    PushTraitStack(battler, ABILITY_JADE_BLOOM);
                    if (canHeal && (canRaiseSpAtk || canRaiseSpDef))
                    {
                        SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / 16);
                        BattleScriptExecute(BattleScript_JadeBloomActivates);
                    }
                    else if (canHeal)
                    {
                        SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / 16);
                        BattleScriptExecute(BattleScript_IceBodyHeal);
                    }
                    else
                    {
                        BattleScriptExecute(BattleScript_AttackerAbilityStatRaiseEnd2);
                    }
                    effect++;
                    break;
                }
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SPEED_BOOST)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN) && gBattleStruct->battlerState[battler].isFirstTurn != 2)
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                SaveBattlerAttacker(gBattlerAttacker);
                SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                PushTraitStack(battler, ABILITY_SPEED_BOOST);
                BattleScriptExecute(BattleScript_AttackerAbilityStatRaiseEnd2);
                gBattleScripting.battler = battler;
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_REJUVENATION)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && IsBattlerAlive(battler)
             && !gProtectStructs[battler].assuranceDoubled
             && !IsBattlerAtMaxHp(battler)
             && !gBattleMons[battler].volatiles.healBlock)
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_REJUVENATION);
                SetHealAmount(battler, max(1, GetNonDynamaxMaxHP(battler) / 10));
                BattleScriptExecute(BattleScript_IceBodyHeal);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_STORMRIDER)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && !NoAliveMonsForEitherParty())
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gBattlerTarget = BATTLE_OPPOSITE(battler);
                SET_STATCHANGER(STAT_SPDEF, 1, TRUE);
                PushTraitStack(battler, ABILITY_STORMRIDER);
                BattleScriptExecute(BattleScript_EndTurnAbilityLowerStatFoe);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_VOLCANO_HOWL)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && !NoAliveMonsForEitherParty())
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gBattlerTarget = BATTLE_OPPOSITE(battler);
                SET_STATCHANGER(STAT_DEF, 1, TRUE);
                PushTraitStack(battler, ABILITY_VOLCANO_HOWL);
                BattleScriptExecute(BattleScript_EndTurnAbilityLowerStatFoe);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_ARCTIC_AURA)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && !NoAliveMonsForEitherParty())
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                gBattlerTarget = BATTLE_OPPOSITE(battler);
                SET_STATCHANGER(STAT_ATK, 1, TRUE);
                PushTraitStack(battler, ABILITY_ARCTIC_AURA);
                BattleScriptExecute(BattleScript_EndTurnAbilityLowerStatFoe);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_MOODY)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
             && gBattleStruct->battlerState[battler].isFirstTurn != 2)
            {
                u32 validToRaise = 0, validToLower = 0;
                u32 statsNum = GetConfig(B_MOODY_ACC_EVASION) >= GEN_8 ? NUM_STATS : NUM_BATTLE_STATS;

                for (i = STAT_ATK; i < statsNum; i++)
                {
                    if (CompareStat(battler, i, MIN_STAT_STAGE, CMP_GREATER_THAN))
                        validToLower |= 1u << i;
                    if (CompareStat(battler, i, MAX_STAT_STAGE, CMP_LESS_THAN))
                        validToRaise |= 1u << i;
                }

                gBattleScripting.statChanger = gBattleScripting.savedStatChanger = 0; // for raising and lowering stat respectively
                if (validToRaise) // Find stat to raise
                {
                    i = RandomUniformExcept(RNG_MOODY_INCREASE, STAT_ATK, statsNum - 1, MoodyCantRaiseStat);
                    SET_STATCHANGER(i, 2, FALSE);
                    validToLower &= ~(1u << i); // Can't lower the same stat as raising.
                }
                if (validToLower) // Find stat to lower
                {
                    // MoodyCantLowerStat already checks that both stats are different
                    i = RandomUniformExcept(RNG_MOODY_DECREASE, STAT_ATK, statsNum - 1, MoodyCantLowerStat);
                    SET_STATCHANGER2(gBattleScripting.savedStatChanger, i, 1, TRUE);
                }
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_MOODY);
                BattleScriptExecute(BattleScript_MoodyActivates);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TRUANT)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1])
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                gBattleMons[battler].volatiles.truantCounter ^= 1;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_SLOW_START)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1]
                && gBattleMons[battler].volatiles.slowStartTimer > 0 && --gBattleMons[battler].volatiles.slowStartTimer == 0)
            {
                    gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                    PushTraitStack(battler, ABILITY_SLOW_START);
                    BattleScriptExecute(BattleScript_SlowStartEnds);
                    effect++;
                    break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_BAD_DREAMS)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1])
            {
                gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                PushTraitStack(battler, ABILITY_BAD_DREAMS);
                BattleScriptExecute(BattleScript_BadDreamsActivates);
                effect++;
                break;
            }
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_HEALER)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1])
            {
                gBattleScripting.battler = partner;
                if (IsBattlerAlive(gBattleScripting.battler)
                 && gBattleMons[gBattleScripting.battler].status1 & STATUS1_ANY
                 && RandomPercentage(RNG_HEALER, 30))
                {
                    gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                    PushTraitStack(battler, ABILITY_HEALER);
                    BattleScriptExecute(BattleScript_HealerActivates);
                    effect++;
                    break;
                }
            }
            // Cud Chew moved to the bottom because it has additional IF conditions so it could block the Else on abilities coming after (Multi)
            else if ((traitCheck = SearchTraits(battlerTraits, ABILITY_CUD_CHEW)) && !gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1])
			{
                for (i = 0; i < MAX_MON_ITEMS; i++)
                {
                    if (gBattleMons[battler].volatiles.cudChew && GetItemPocket(GetBattlerPartyState(battler)->usedHeldItems[i]) == POCKET_BERRIES)
                    {
                        gSpecialStatuses[battler].endTurnTraitDone[traitCheck - 1] = TRUE;
                        gBattleScripting.battler = battler;
                        gBattleMons[battler].volatiles.cudChew = FALSE;
                        gLastUsedItem = GetBattlerPartyState(battler)->usedHeldItems[i];
                        GetBattlerPartyState(battler)->usedHeldItems[i] = ITEM_NONE;
                        PushTraitStack(battler, ABILITY_CUD_CHEW);
                        BattleScriptExecute(BattleScript_CudChewActivates);
                        effect++;
                        break;
                    }
                    else if (!gBattleMons[battler].volatiles.cudChew && GetItemPocket(GetBattlerPartyState(battler)->usedHeldItems[i]) == POCKET_BERRIES)
                    {
                        gBattleMons[battler].volatiles.cudChew = TRUE;
                        break;
                    }
                }
            }
        }
        break;
    case ABILITYEFFECT_COLOR_CHANGE:
        if (SearchTraits(battlerTraits, ABILITY_BERSERK)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && HadMoreThanHalfHpNowDoesnt(battler)
         && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gEffectBattler = battler;
            PushTraitStack(battler, ABILITY_BERSERK);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetBerserk);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_ANGER_SHELL)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && HadMoreThanHalfHpNowDoesnt(battler))
        {
            PushTraitStack(gBattlerTarget, ABILITY_ANGER_SHELL);
            BattleScriptCall(BattleScript_AngerShellActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_COLOR_CHANGE) // Last so the other abilities don't overwrite the gBattleTextBuff1
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && !IS_BATTLER_OF_TYPE(battler, moveType)
         && move != MOVE_STRUGGLE
         && moveType != TYPE_STELLAR
         && moveType != TYPE_MYSTERY)
        {
            gEffectBattler = gBattlerAbility = battler;
            SET_BATTLER_TYPE(battler, moveType);
            PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
            PushTraitStack(battler, ABILITY_COLOR_CHANGE);
            BattleScriptCall(BattleScript_ColorChangeActivates);
            effect++;
        }
        break;
    case ABILITYEFFECT_MOVE_END: // Think contact abilities.
        if (SearchTraits(battlerTraits, ABILITY_JUSTIFIED)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && moveType == TYPE_DARK
         && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gEffectBattler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_JUSTIFIED);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetJustified);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_RATTLED)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && (moveType == TYPE_DARK || moveType == TYPE_BUG || moveType == TYPE_GHOST)
         && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gEffectBattler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_RATTLED);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetRattled);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_WATER_COMPACTION)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && moveType == TYPE_WATER
         && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gEffectBattler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_WATER_COMPACTION);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetWaterCompaction);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_STAMINA)
         && gBattlerAttacker != gBattlerTarget
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gEffectBattler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_STAMINA);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetStamina);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_WEAK_ARMOR)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && IsBattleMovePhysical(gCurrentMove)
         && (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN) // Don't activate if both Speed and Defense cannot be raised.
         || CompareStat(battler, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN)))
        {
            if (GetMoveEffect(gCurrentMove) == EFFECT_HIT_ESCAPE && CanBattlerSwitch(gBattlerAttacker))
                gProtectStructs[battler].disableEjectPack = TRUE;  // Set flag for target
            PushTraitStack(battler, ABILITY_WEAK_ARMOR);
            BattleScriptCall(BattleScript_WeakArmorActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_CURSED_BODY)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && gBattleMons[gBattlerAttacker].volatiles.disabledMove == MOVE_NONE
         && IsBattlerAlive(gBattlerAttacker)
         && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL)
         && gChosenMove != MOVE_STRUGGLE
         && RandomPercentage(RNG_CURSED_BODY, 30))
        {
            gBattleMons[gBattlerAttacker].volatiles.disabledMove = gChosenMove;
            gBattleMons[gBattlerAttacker].volatiles.disableTimer = B_DISABLE_TIMER;
            PREPARE_MOVE_BUFFER(gBattleTextBuff3, gChosenMove);
            PushTraitStack(battler, ABILITY_CURSED_BODY);
            BattleScriptCall(BattleScript_CursedBodyActivates);
            effect++;
        }
        // Mummy and Lingering Aroma use the same battlescript since they can't both activate at the same time (Trait)
        if (SearchTraits(battlerTraits, ABILITY_MUMMY)
         && IsBattlerAlive(gBattlerAttacker)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)
         && gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility != GetBattlerAbility(gBattlerTarget)
         && !BattlerHasTrait(gBattlerAttacker, ABILITY_MUMMY)
         && !BattlerHasTrait(gBattlerAttacker, ABILITY_LINGERING_AROMA)
         && !gAbilitiesInfo[gBattleMons[gBattlerAttacker].ability].cantBeSuppressed)
        {
            if (BattlerHasHeldItemEffectIgnoreAbility(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD, FALSE))
            {
                RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
            }
            else
            {
                RemoveAbilityFlags(gBattlerAttacker);
                gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
                gBattleMons[gBattlerAttacker].ability = gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility = ABILITY_MUMMY;
                PushTraitStack(gBattlerAttacker, gLastUsedAbility);
                PushTraitStack(battler, ABILITY_MUMMY);
                BattleScriptCall(BattleScript_MummyActivates);
                effect++;
            }
        }
        else if (SearchTraits(battlerTraits, ABILITY_LINGERING_AROMA)
         && IsBattlerAlive(gBattlerAttacker)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)
         && gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility != GetBattlerAbility(gBattlerTarget)
         && !BattlerHasTrait(gBattlerAttacker, ABILITY_MUMMY)
         && !BattlerHasTrait(gBattlerAttacker, ABILITY_LINGERING_AROMA)
         && !gAbilitiesInfo[gBattleMons[gBattlerAttacker].ability].cantBeSuppressed)
        {
            if (BattlerHasHeldItemEffectIgnoreAbility(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD, TRUE))
            {
                RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
                break;
            }
            RemoveAbilityFlags(gBattlerAttacker);
            gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
            gBattleMons[gBattlerAttacker].ability = gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility = ABILITY_LINGERING_AROMA;
            PushTraitStack(gBattlerAttacker, gLastUsedAbility);
            PushTraitStack(battler, ABILITY_LINGERING_AROMA);
            BattleScriptCall(BattleScript_MummyActivates);
            effect++;
            break;
        }
        if (SearchTraits(battlerTraits, ABILITY_WANDERING_SPIRIT)
         && IsBattlerAlive(gBattlerAttacker)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)
         && !(GetActiveGimmick(gBattlerTarget) == GIMMICK_DYNAMAX)
         && !gAbilitiesInfo[gBattleMons[gBattlerAttacker].ability].cantBeSwapped)
        {
            if (SearchTraits(battlerTraits, ABILITY_WANDERING_SPIRIT) > 1)
            {
                // Wandering Spirit replaces your main Ability, so it generally should not be an Innate.
                DebugPrintf("Wandering Spirit not set as main Ability");
            }
            if (BattlerHasHeldItemEffectIgnoreAbility(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD, FALSE))
            {
                RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
            }
            if (BattlerHasHeldItemEffectIgnoreAbility(gBattlerTarget, HOLD_EFFECT_ABILITY_SHIELD, TRUE))
            {
                RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_ABILITY_SHIELD);
            }

            RemoveAbilityFlags(gBattlerAttacker);
            gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
            gBattleMons[gBattlerAttacker].ability = gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility = gBattleMons[gBattlerTarget].ability;
            gBattleMons[gBattlerTarget].ability = gBattleMons[gBattlerTarget].volatiles.overwrittenAbility = gLastUsedAbility;
            BattleScriptCall(BattleScript_WanderingSpiritActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_ANGER_POINT)
         && gSpecialStatuses[battler].criticalHit
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            SET_STATCHANGER(STAT_ATK, MAX_STAT_STAGE - gBattleMons[battler].statStages[STAT_ATK], FALSE);
            PushTraitStack(battler, ABILITY_ANGER_POINT);
            BattleScriptCall(BattleScript_TargetsStatWasMaxedOut);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_DESPERADO)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && (gBattleStruct->moveResultFlags[battler] & MOVE_RESULT_SUPER_EFFECTIVE))
        {
            gEffectBattler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_DESPERADO);
            BattleScriptCall(BattleScript_DesperadoActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_PARRYING)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && (gProtectStructs[battler].chargingTurn
          || (gBattleStruct->battlerState[battler].focusPunchBattlers
           && GetMoveEffect(gChosenMoveByBattler[battler]) == EFFECT_FOCUS_PUNCH)))
        {
            gEffectBattler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_PARRYING);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetStamina);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_SHARDPLATE)
         && IsCustomAbilityDirectDamagingMove(move)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES))
        {
            struct PartyState *partyState = GetBattlerPartyState(battler);
            if (partyState->shardplateHits < 5)
            {
                partyState->shardplateHits++;
                RecordAbilityBattle(battler, ABILITY_SHARDPLATE);
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_FAINTRATTLE)
         && !IsBattlerAlive(battler)
         && IsBattlerAlive(gBattlerAttacker)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, battler, move)
         && CanSetNonVolatileStatus(battler, gBattlerAttacker, MOVE_EFFECT_TOXIC, CHECK_TRIGGER))
        {
            gEffectBattler = gBattlerAttacker;
            gBattleScripting.battler = battler;
            gBattleScripting.moveEffect = MOVE_EFFECT_TOXIC;
            gLastUsedAbility = ABILITY_FAINTRATTLE;
            PushTraitStack(battler, ABILITY_FAINTRATTLE);
            BattleScriptCall(BattleScript_AbilityStatusEffectDef);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_FLAMEBURST)
         && !IsBattlerAlive(battler)
         && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES)
         && !IsOpposingSideEmpty(battler)
         && !IsBattlerAlly(battler, gBattlerAttacker))
        {
            bool32 canBurn = FALSE;

            for (enum BattlerId foe = 0; foe < gBattlersCount; foe++)
            {
                if (IsBattlerAlive(foe) && !IsBattlerAlly(battler, foe) && CanBeBurned(battler, foe))
                    canBurn = TRUE;
            }

            if (canBurn)
            {
                SaveBattlerAttacker(gBattlerAttacker);
                SaveBattlerTarget(gBattlerTarget);
                gBattlerAttacker = battler;
                gBattlerTarget = BATTLE_OPPOSITE(battler);
                gBattleScripting.battler = battler;
                gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
                gLastUsedAbility = ABILITY_FLAMEBURST;
                PushTraitStack(battler, ABILITY_FLAMEBURST);
                BattleScriptCall(BattleScript_FlameburstActivates);
                effect++;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_GOOEY)
         && IsBattlerAlive(gBattlerAttacker)
         && (CompareStat(gBattlerAttacker, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN) || BattlerHasTrait(gBattlerAttacker, ABILITY_MIRROR_ARMOR))
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
         {
            gLastUsedAbility = ABILITY_GOOEY;
            SET_STATCHANGER(STAT_SPEED, 1, TRUE);
            PushTraitStack(battler, ABILITY_GOOEY);
            BattleScriptCall(BattleScript_GooeyActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_TANGLING_HAIR)
         && IsBattlerAlive(gBattlerAttacker)
         && (CompareStat(gBattlerAttacker, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN) || BattlerHasTrait(gBattlerAttacker, ABILITY_MIRROR_ARMOR))
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            gLastUsedAbility = ABILITY_TANGLING_HAIR;
            SET_STATCHANGER(STAT_SPEED, 1, TRUE);
            PushTraitStack(battler, ABILITY_TANGLING_HAIR);
            BattleScriptCall(BattleScript_TanglingHairActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_INKY)
         && IsBattlerAlive(gBattlerAttacker)
         && (CompareStat(gBattlerAttacker, STAT_ACC, MIN_STAT_STAGE, CMP_GREATER_THAN) || BattlerHasTrait(gBattlerAttacker, ABILITY_MIRROR_ARMOR))
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES))
        {
            gLastUsedAbility = ABILITY_INKY;
            SET_STATCHANGER(STAT_ACC, 1, TRUE);
            PushTraitStack(battler, ABILITY_INKY);
            BattleScriptCall(BattleScript_InkyActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_REEF_WARDEN)
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            if (!gBattleMons[gBattlerAttacker].volatiles.healBlock)
            {
                gBattleMons[gBattlerAttacker].volatiles.healBlock = TRUE;
                gBattleMons[gBattlerAttacker].volatiles.healBlockTimer = 2;
                PushTraitStack(battler, ABILITY_REEF_WARDEN);
                BattleScriptCall(BattleScript_ReefWardenActivates);
                effect++;
            }
            else if (gBattleMons[gBattlerAttacker].volatiles.healBlockTimer < 2)
            {
                gBattleMons[gBattlerAttacker].volatiles.healBlockTimer = 2;
            }
        }

        s32 returnDamage = 0;
        if (SearchTraits(battlerTraits, ABILITY_INNARDS_OUT)
         && !IsBattlerUnaffectedByMove(gBattlerTarget)
         && !IsBattlerAlive(gBattlerTarget)
         && IsBattlerAlive(gBattlerAttacker))
         {
            // Prevent Innards Out effect if Future Sight user is currently not on field
            if (!IsFutureSightAttackerInParty(gBattlerAttacker, gBattlerTarget, gCurrentMove))
            {
                returnDamage += (gBattleStruct->moveDamage[gBattlerTarget]);
                PushTraitStack(battler, ABILITY_INNARDS_OUT);
                BattleScriptCall(BattleScript_InnardsOutDmg);
                effect++;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_AFTERMATH)
         && !IsBattlerUnaffectedByMove(gBattlerTarget)
         && !IsBattlerAlive(gBattlerTarget)
         && IsBattlerAlive(gBattlerAttacker)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            enum BattlerId dampBattler;
            if ((dampBattler = IsAbilityOnField(ABILITY_DAMP)))
            {
                gBattleScripting.battler = dampBattler = dampBattler - 1;
                PushTraitStack(dampBattler, ABILITY_DAMP);
                PushTraitStack(battler, ABILITY_AFTERMATH);
                BattleScriptCall(BattleScript_DampPreventsAftermath);
            }
            else
            {
                returnDamage += (GetNonDynamaxMaxHP(gBattlerAttacker) / 4);
                PushTraitStack(battler, ABILITY_AFTERMATH);
                BattleScriptCall(BattleScript_AftermathDmg);
            }
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_IRON_BARBS)
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            if (!IsAbilityAndRecord(gBattlerAttacker, ABILITY_MAGIC_GUARD))
            {
                returnDamage += (GetNonDynamaxMaxHP(gBattlerAttacker) / (B_ROUGH_SKIN_DMG >= GEN_4 ? 8 : 16));
                gLastUsedAbility = ABILITY_IRON_BARBS;
                PushTraitStack(battler, ABILITY_IRON_BARBS);
                BattleScriptCall(BattleScript_IronBarbsActivates);
            }
            else
            {
                PushTraitStack(battler, ABILITY_IRON_BARBS);
                BattleScriptCall(BattleScript_AbilityPopUp);
            }
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_ROUGH_SKIN)
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            if (!IsAbilityAndRecord(gBattlerAttacker, ABILITY_MAGIC_GUARD))
            {
                returnDamage += (GetNonDynamaxMaxHP(gBattlerAttacker) / (B_ROUGH_SKIN_DMG >= GEN_4 ? 8 : 16));
                gLastUsedAbility = ABILITY_ROUGH_SKIN;
                PushTraitStack(battler, ABILITY_ROUGH_SKIN);
                BattleScriptCall(BattleScript_RoughSkinActivates);
            }
            else
            {
                PushTraitStack(battler, ABILITY_ROUGH_SKIN);
                BattleScriptCall(BattleScript_AbilityPopUp);
            }
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_FORCE_RETURN)
         && IsBattlerAlive(gBattlerAttacker)
         && gBattlerAttacker != gBattlerTarget
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES))
        {
            if (!IsAbilityAndRecord(gBattlerAttacker, ABILITY_MAGIC_GUARD))
            {
                s32 forceReturnDamage = (gBattleStruct->moveDamage[gBattlerTarget] * 30) / 100;

                if (forceReturnDamage == 0)
                    forceReturnDamage = 1;
                returnDamage += forceReturnDamage;
                gBattlerAbility = gBattlerTarget;
                PushTraitStack(battler, ABILITY_FORCE_RETURN);
                BattleScriptCall(BattleScript_RoughSkinActivates);
            }
            else
            {
                PushTraitStack(battler, ABILITY_FORCE_RETURN);
                BattleScriptCall(BattleScript_AbilityPopUp);
            }
            effect++;
        }
        if (returnDamage > 0)
        {
            SetPassiveDamageAmount(gBattlerAttacker, returnDamage); // Set combined passive damage of damage returning abilities
        }

        // Only one non-volitile ailment can trigger at a time,
        // so each ability is checked for viability then one ailment is activated from tht list.
        // Ailment priority is: Sleep > Paralysis > Burn > Poison
        bool32 trySleep = FALSE;
        bool32 tryParalysis = FALSE;
        bool32 tryBurn = FALSE;
        bool32 tryPoison = FALSE;
        enum Ability sleepAbility = ABILITY_NONE;
        enum Ability paralysisAbility = ABILITY_NONE;
        enum Ability burnAbility = ABILITY_NONE;
        enum Ability poisonAbility = ABILITY_NONE;

        if (SearchTraits(battlerTraits, ABILITY_EFFECT_SPORE))
        {
            if (IsBattlerAlive(gBattlerAttacker)
             && !gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)
             && IsAffectedByPowderMove(gBattlerAttacker))
            {
                u32 poison, paralysis, sleep;

                if (GetConfig(B_ABILITY_TRIGGER_CHANCE) >= GEN_5)
                {
                    poison = 9;
                    paralysis = 19;
                }
                else
                {
                    poison = 10;
                    paralysis = 20;
                }
                sleep = 30;

                gLastUsedAbility= ABILITY_EFFECT_SPORE;

                i = RandomUniform(RNG_EFFECT_SPORE, 0, GetConfig(B_ABILITY_TRIGGER_CHANCE) >= GEN_4 ? 99 : 299);
                if (i < poison)
                {
                    poisonAbility = ABILITY_EFFECT_SPORE;
                    tryPoison = TRUE;
                }
                else if (i < paralysis)
                {
                    paralysisAbility = ABILITY_EFFECT_SPORE;
                    tryParalysis = TRUE;
                }
                else if (i < sleep)
                {
                    sleepAbility = ABILITY_EFFECT_SPORE;
                    trySleep = TRUE;
                }
            }
        }

        if (SearchTraits(battlerTraits, ABILITY_STATIC)
        && (GetConfig(B_ABILITY_TRIGGER_CHANCE) >= GEN_4 ? RandomPercentage(RNG_STATIC, 30) : RandomChance(RNG_STATIC, 1, 3)))
        {
            paralysisAbility = ABILITY_STATIC;
            tryParalysis = TRUE;
        }
        if (SearchTraits(battlerTraits, ABILITY_FLAME_BODY)
        && (GetConfig(B_ABILITY_TRIGGER_CHANCE) >= GEN_4 ? RandomPercentage(RNG_FLAME_BODY, 30) : RandomChance(RNG_FLAME_BODY, 1, 3)))
        {
            burnAbility = ABILITY_FLAME_BODY;
            tryBurn = TRUE;
        }
        if (SearchTraits(battlerTraits, ABILITY_SPICY_SPRAY)
         && !gBattleStruct->unableToUseMove
         && IsCustomAbilityDirectDamagingMove(move)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES))
        {
            burnAbility = ABILITY_SPICY_SPRAY;
            tryBurn = TRUE;
        }
        if (SearchTraits(battlerTraits, ABILITY_POISON_POINT)
        && (GetConfig(B_ABILITY_TRIGGER_CHANCE) >= GEN_4 ? RandomPercentage(RNG_POISON_POINT, 30) : RandomChance(RNG_POISON_POINT, 1, 3)))
        {
            poisonAbility = ABILITY_POISON_POINT;
            tryPoison = TRUE;
        }

        // Ailment priority is: Sleep > Paralysis > Burn > Poison
        if (trySleep
            && IsBattlerAlive(gBattlerAttacker)
            && !gBattleStruct->unableToUseMove
            && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
            && CanBeSlept(gBattlerTarget, gBattlerAttacker, NOT_BLOCKED_BY_SLEEP_CLAUSE)
            && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            if (IsSleepClauseEnabled())
                gBattleStruct->battlerState[gBattlerAttacker].sleepClauseEffectExempt = TRUE;
            gEffectBattler = gBattlerAttacker;
            gBattleScripting.battler = gBattlerTarget;
            gBattleScripting.moveEffect = MOVE_EFFECT_SLEEP;
            gLastUsedAbility = sleepAbility;
            PushTraitStack(battler, gLastUsedAbility);
            BattleScriptCall(BattleScript_AbilityStatusEffectDef);
            effect++;
        }
        else if (tryParalysis
        && IsBattlerAlive(gBattlerAttacker)
        && !gBattleStruct->unableToUseMove
        && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
        && CanBeParalyzed(gBattlerTarget, gBattlerAttacker)
        && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            gEffectBattler = gBattlerAttacker;
            gBattleScripting.battler = gBattlerTarget;
            gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
            gLastUsedAbility = paralysisAbility;
            PushTraitStack(battler, gLastUsedAbility);
            BattleScriptCall(BattleScript_AbilityStatusEffectDef);
            effect++;
        }
        else if (tryBurn
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && CanBeBurned(gBattlerTarget, gBattlerAttacker)
         && (burnAbility == ABILITY_SPICY_SPRAY || !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)))
        {
            gEffectBattler = gBattlerAttacker;
            gBattleScripting.battler = gBattlerTarget;
            gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
            gLastUsedAbility = burnAbility;
            PushTraitStack(battler, gLastUsedAbility);
            BattleScriptCall(BattleScript_AbilityStatusEffectDef);
            effect++;
        }
        else if (tryPoison
            && IsBattlerAlive(gBattlerAttacker)
            && !gBattleStruct->unableToUseMove
            && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
            && CanBePoisoned(gBattlerTarget, gBattlerAttacker)
            && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move))
        {
            gEffectBattler = gBattlerAttacker;
            gBattleScripting.battler = gBattlerTarget;
            gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
            gLastUsedAbility = poisonAbility;
            PushTraitStack(battler, gLastUsedAbility);
            BattleScriptCall(BattleScript_AbilityStatusEffectDef);
            effect++;
        }
        
        if (SearchTraits(battlerTraits, ABILITY_CUTE_CHARM)
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(gBattlerTarget)
         && (GetConfig(B_ABILITY_TRIGGER_CHANCE) >= GEN_4 ? RandomPercentage(RNG_CUTE_CHARM, 30) : RandomChance(RNG_CUTE_CHARM, 1, 3))
         && !(gBattleMons[gBattlerAttacker].volatiles.infatuation)
         && AreBattlersOfOppositeGender(gBattlerAttacker, gBattlerTarget)
         && !IsAbilityAndRecord(gBattlerAttacker, ABILITY_OBLIVIOUS)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)
         && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL))
        {
            gBattleMons[gBattlerAttacker].volatiles.infatuation = INFATUATED_WITH(gBattlerTarget);
            PushTraitStack(battler, ABILITY_CUTE_CHARM);
            BattleScriptCall(BattleScript_CuteCharmActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_BRAND_OF_TORMENT)
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)
         && !gBattleMons[gBattlerAttacker].volatiles.torment
         && GetActiveGimmick(gBattlerAttacker) != GIMMICK_DYNAMAX
         && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL)
         && RandomPercentage(RNG_BRAND_OF_TORMENT, 30))
        {
            gBattleMons[gBattlerAttacker].volatiles.torment = TRUE;
            gBattleMons[gBattlerAttacker].volatiles.tormentTimer = B_TORMENT_TIMER;
            SaveBattlerTarget(gBattlerTarget);
            gBattlerTarget = gBattlerAttacker;
            gLastUsedAbility = ABILITY_BRAND_OF_TORMENT;
            PushTraitStack(battler, ABILITY_BRAND_OF_TORMENT);
            BattleScriptCall(BattleScript_BrandOfTormentActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_ILLUSION)
         && gBattleStruct->illusion[gBattlerTarget].state == ILLUSION_ON && IsBattlerTurnDamaged(battler, EXCLUDING_SUBSTITUTES))
        {
            gBattleScripting.battler = gBattlerTarget;
            BattleScriptCall(BattleScript_IllusionOff);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_COTTON_DOWN)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES))
        {
            gEffectBattler = gBattlerTarget;
            // Will ability popup activate if there is only one target?
            PushTraitStack(battler, ABILITY_COTTON_DOWN);
            BattleScriptCall(BattleScript_CottonDownActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_STEAM_ENGINE)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN)
         && (moveType == TYPE_FIRE || moveType == TYPE_WATER))
        {
            gEffectBattler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_STEAM_ENGINE);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetSteam);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_SAND_SPIT)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !(gBattleWeather & B_WEATHER_SANDSTORM && HasWeatherEffect()))
        {
            if (gBattleWeather & B_WEATHER_PRIMAL_ANY && HasWeatherEffect())
            {
                PushTraitStack(battler, ABILITY_SAND_SPIT);
                BattleScriptCall(BattleScript_BlockedByPrimalWeather);
                effect++;
            }
            else if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SANDSTORM, TRUE))
            {
                PushTraitStack(battler, ABILITY_SAND_SPIT);
                gBattleScripting.battler = battler;
                BattleScriptCall(BattleScript_SandSpitActivates);
                effect++;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_TIDAL_DEITY)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(gBattlerTarget)
         && !IsBattlerAtMaxHp(gBattlerTarget)
         && gBattleMons[gBattlerTarget].hp + gBattleStruct->moveDamage[gBattlerTarget] >= gBattleMons[gBattlerTarget].maxHP
         && !(gBattleWeather & B_WEATHER_RAIN && HasWeatherEffect()))
        {
            if (gBattleWeather & B_WEATHER_PRIMAL_ANY && HasWeatherEffect())
            {
                PushTraitStack(battler, ABILITY_TIDAL_DEITY);
                BattleScriptCall(BattleScript_BlockedByPrimalWeather);
                effect++;
            }
            else if (TryChangeBattleWeather(battler, BATTLE_WEATHER_RAIN, TRUE))
            {
                PushTraitStack(battler, ABILITY_TIDAL_DEITY);
                gBattleScripting.battler = battler;
                BattleScriptCall(BattleScript_DrizzleActivates);
                effect++;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_PERISH_BODY)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(battler)
         && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, move)
         && !gBattleMons[gBattlerAttacker].volatiles.perishSong)
        {
            if (!gBattleMons[battler].volatiles.perishSong)
            {
                gBattleMons[battler].volatiles.perishSong = TRUE;
                gBattleMons[battler].volatiles.perishSongTimer = 3;
            }
            gBattleMons[gBattlerAttacker].volatiles.perishSong = TRUE;
            gBattleMons[gBattlerAttacker].volatiles.perishSongTimer = 3;
            PushTraitStack(battler, ABILITY_PERISH_BODY);
            BattleScriptCall(BattleScript_PerishBodyActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_SEED_SOWER)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && TryChangeBattleTerrain(gBattlerTarget, STATUS_FIELD_GRASSY_TERRAIN))
        {
            PushTraitStack(gBattlerTarget, ABILITY_SEED_SOWER);
            BattleScriptCall(BattleScript_SeedSowerActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_THERMAL_EXCHANGE)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(gBattlerTarget)
         && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN)
         && moveType == TYPE_FIRE)
        {
            gEffectBattler = gBattlerAbility = gBattlerTarget;
            PushTraitStack(gBattlerTarget, ABILITY_THERMAL_EXCHANGE);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetThermal);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_SOLIDIFY)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(gBattlerTarget)
         && CompareStat(gBattlerTarget, STAT_SPDEF, MAX_STAT_STAGE, CMP_LESS_THAN)
         && IsBattleMoveSpecial(gCurrentMove))
        {
            gEffectBattler = gBattlerAbility = gBattlerTarget;
            PushTraitStack(gBattlerTarget, ABILITY_SOLIDIFY);
            BattleScriptCall(BattleScript_TargetAbilityStatRaiseRetSolidify);
            effect++;
        }
        // Only one of Wind Power or Electromorphosis can activate at a time
        if (SearchTraits(battlerTraits, ABILITY_WIND_POWER)
         && IsWindMove(gCurrentMove)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES))
        {
            PushTraitStack(battler, ABILITY_WIND_POWER);
            BattleScriptCall(BattleScript_WindPowerActivates);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_ELECTROMORPHOSIS)
         && !gBattleStruct->unableToUseMove
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES))
        {
            PushTraitStack(battler, ABILITY_ELECTROMORPHOSIS);
            BattleScriptCall(BattleScript_ElectromorphosisActivates);
            effect++;
        }

        if (SearchTraits(battlerTraits, ABILITY_TOXIC_DEBRIS)
         && !gBattleStruct->isSkyBattle
         && !gBattleStruct->unableToUseMove
         && IsBattleMovePhysical(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && (gSideTimers[GetBattlerSide(gBattlerAttacker)].toxicSpikesAmount != 2))
        {
            SaveBattlerTarget(gBattlerTarget);
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = gBattlerTarget;
            gBattlerTarget = BATTLE_OPPOSITE(gBattlerAttacker);
            PushTraitStack(battler, ABILITY_TOXIC_DEBRIS);
            BattleScriptCall(BattleScript_ToxicDebrisActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_FROST_NOVA)
         && gBattleMons[gBattlerTarget].hp == 0
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && CanSetNonVolatileStatus(gBattlerTarget, gBattlerAttacker, MOVE_EFFECT_FREEZE, CHECK_TRIGGER))
        {
            gBattleMons[gBattlerAttacker].volatiles.frostNovaTimer = 2;
            gEffectBattler = gBattlerAttacker;
            gBattleScripting.battler = gBattlerTarget;
            gBattleScripting.moveEffect = MOVE_EFFECT_FREEZE;
            gLastUsedAbility = ABILITY_FROST_NOVA;
            PushTraitStack(gBattlerTarget, ABILITY_FROST_NOVA);
            BattleScriptCall(BattleScript_AbilityStatusEffectDef);
            effect++;
        }
    break;
    case ABILITYEFFECT_MOVE_END_ATTACKER: // Same as above, but for attacker
        STORE_BATTLER_TRAITS(gBattlerAttacker);

        if (gBattleMons[gBattlerAttacker].volatiles.overlock
         && moveType == TYPE_STEEL
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES))
            gBattleMons[gBattlerAttacker].volatiles.overlock = FALSE;

        if (SearchTraits(battlerTraits, ABILITY_POISON_PUPPETEER)
         && IsRestrictedAbility(gBattlerAttacker, ABILITY_POISON_PUPPETEER)
         && gBattleStruct->poisonPuppeteerConfusion == TRUE
         && CanBeConfused(gBattlerTarget))
        {
            gBattleStruct->poisonPuppeteerConfusion = FALSE;
            gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
            gLastUsedAbility = ABILITY_POISON_PUPPETEER;
            PushTraitStack(gBattlerAttacker, ABILITY_POISON_PUPPETEER);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_TOXIC_CHAIN)
         && gBattleStruct->toxicChainPriority)
        {
            gBattleStruct->toxicChainPriority = FALSE;
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_TOXIC;
            gLastUsedAbility = ABILITY_TOXIC_CHAIN;
            PushTraitStack(gBattlerAttacker, ABILITY_TOXIC_CHAIN);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_POISON_TOUCH)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && CanBePoisoned(gBattlerAttacker, gBattlerTarget)
         && IsMoveMakingContact(gBattlerAttacker, gBattlerTarget, move)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES) // Need to actually hit the target
         && RandomPercentage(RNG_POISON_TOUCH, 30))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
            gLastUsedAbility = ABILITY_POISON_TOUCH;
            PushTraitStack(gBattlerAttacker, ABILITY_POISON_TOUCH);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_STENCH)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && RandomChance(RNG_STENCH, 1, 10)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_FLINCH))
        {
            SetMoveEffect(gBattlerAttacker, gBattlerTarget, MOVE_EFFECT_FLINCH, gBattlescriptCurrInstr, NO_FLAGS);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_HAUNTING)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && RandomPercentage(RNG_HAUNTING, 20)
         && moveType == TYPE_GHOST
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_FLINCH))
        {
            SetMoveEffect(gBattlerAttacker, gBattlerTarget, MOVE_EFFECT_FLINCH, gBattlescriptCurrInstr, NO_FLAGS);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_SEER)
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && moveType == TYPE_PSYCHIC
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && CompareStat(gBattlerAttacker, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
            SET_STATCHANGER(STAT_SPEED, 1, FALSE);
            PushTraitStack(gBattlerAttacker, ABILITY_SEER);
            BattleScriptCall(BattleScript_AttackerAbilityStatRaise);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_LUNAR_CYCLE)
         && IsBattlerAlive(gBattlerAttacker)
         && !gBattleStruct->unableToUseMove
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && CompareStat(gBattlerAttacker, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
            SET_STATCHANGER(STAT_SPEED, 1, FALSE);
            PushTraitStack(gBattlerAttacker, ABILITY_LUNAR_CYCLE);
            BattleScriptCall(BattleScript_AttackerAbilityStatRaise);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_PERMAFROST)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && RandomPercentage(RNG_PERMAFROST, 20)
         && CanSetNonVolatileStatus(gBattlerAttacker, gBattlerTarget, MOVE_EFFECT_FREEZE_OR_FROSTBITE, CHECK_TRIGGER))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE;
            gLastUsedAbility = ABILITY_PERMAFROST;
            PushTraitStack(gBattlerAttacker, ABILITY_PERMAFROST);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_BLAZING_SUN)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && moveType == TYPE_FIRE
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && CanBeBurned(gBattlerAttacker, gBattlerTarget))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
            gLastUsedAbility = ABILITY_BLAZING_SUN;
            PushTraitStack(gBattlerAttacker, ABILITY_BLAZING_SUN);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_PLASMA_SURGE)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && CanBeParalyzed(gBattlerAttacker, gBattlerTarget))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
            gLastUsedAbility = ABILITY_PLASMA_SURGE;
            PushTraitStack(gBattlerAttacker, ABILITY_PLASMA_SURGE);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_DUST_DEVIL)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && !IsBattleMoveStatus(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && RandomPercentage(RNG_DUST_DEVIL, 15)
         && CanBeConfused(gBattlerTarget))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
            gLastUsedAbility = ABILITY_DUST_DEVIL;
            PushTraitStack(gBattlerAttacker, ABILITY_DUST_DEVIL);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_HUNTER)
         && gCurrentMove == MOVE_GLARE
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && CanBeConfused(gBattlerTarget))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
            gLastUsedAbility = ABILITY_HUNTER;
            PushTraitStack(gBattlerAttacker, ABILITY_HUNTER);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_PLANTATION)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && RandomPercentage(RNG_PLANTATION, 30)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GRASS)
         && !gBattleMons[gBattlerTarget].volatiles.leechSeed)
        {
            PushTraitStack(gBattlerAttacker, ABILITY_PLANTATION);
            BattleScriptCall(BattleScript_PlantationActivates);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_ECHOING)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && RandomPercentage(RNG_ECHOING, 30)
         && IsSoundMove(gCurrentMove)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && !MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_FLINCH))
        {
            SetMoveEffect(gBattlerAttacker, gBattlerTarget, MOVE_EFFECT_FLINCH, gBattlescriptCurrInstr, NO_FLAGS);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_SOOTHING)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && RandomPercentage(RNG_SOOTHING, 10)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && CanBeSlept(gBattlerAttacker, gBattlerTarget, BLOCKED_BY_SLEEP_CLAUSE)
         && !MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_SLEEP))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_SLEEP;
            gLastUsedAbility = ABILITY_SOOTHING;
            PushTraitStack(gBattlerAttacker, ABILITY_SOOTHING);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        else if (SearchTraits(battlerTraits, ABILITY_OVERLOCK)
         && gCurrentMove == MOVE_SHIFT_GEAR
         && !gBattleStruct->unableToUseMove)
        {
            gBattleMons[gBattlerAttacker].volatiles.overlock = TRUE;
            PushTraitStack(gBattlerAttacker, ABILITY_OVERLOCK);
            BattleScriptCall(BattleScript_OverlockActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_BLOODLUST)
         && gSpecialStatuses[gBattlerTarget].criticalHit
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(gBattlerAttacker))
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
            PushTraitStack(gBattlerAttacker, ABILITY_BLOODLUST);
            BattleScriptCall(BattleScript_BloodlustActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_MOMENTUM)
         && !gBattleStruct->unableToUseMove
         && GetChosenMovePriority(gBattlerAttacker) > 0
         && IsBattlerAlive(gBattlerAttacker))
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
            SET_STATCHANGER(STAT_SPEED, 1, FALSE);
            PushTraitStack(gBattlerAttacker, ABILITY_MOMENTUM);
            BattleScriptCall(BattleScript_AttackerAbilityStatRaise);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_MAIM_AND_MEND)
         && gSpecialStatuses[gBattlerTarget].criticalHit
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && IsBattlerAlive(gBattlerAttacker))
        {
            if (!IsBattlerAtMaxHp(gBattlerAttacker) && !gBattleMons[gBattlerAttacker].volatiles.healBlock)
            {
                SetHealAmount(gBattlerAttacker, max(1, gBattleStruct->moveDamage[gBattlerTarget] / 4));
                PushTraitStack(gBattlerAttacker, ABILITY_MAIM_AND_MEND);
                BattleScriptCall(BattleScript_LifestealActivates);
                effect++;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_PLAGUETOUCH)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && IsMoveMakingContact(gBattlerAttacker, gBattlerTarget, move)
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && RandomPercentage(RNG_PLAGUETOUCH, 20))
        {
            enum MoveEffect status = MOVE_EFFECT_POISON;
            bool32 canApply = FALSE;

            switch (RandomUniform(RNG_PLAGUETOUCH, 0, 4))
            {
            case 0:
                status = MOVE_EFFECT_BURN;
                canApply = CanBeBurned(gBattlerAttacker, gBattlerTarget);
                break;
            case 1:
                status = MOVE_EFFECT_PARALYSIS;
                canApply = CanBeParalyzed(gBattlerAttacker, gBattlerTarget);
                break;
            case 2:
                status = MOVE_EFFECT_POISON;
                canApply = CanBePoisoned(gBattlerAttacker, gBattlerTarget);
                break;
            case 3:
                status = MOVE_EFFECT_SLEEP;
                canApply = CanBeSlept(gBattlerAttacker, gBattlerTarget, BLOCKED_BY_SLEEP_CLAUSE);
                break;
            case 4:
                status = MOVE_EFFECT_FREEZE_OR_FROSTBITE;
                canApply = CanSetNonVolatileStatus(gBattlerAttacker, gBattlerTarget, status, CHECK_TRIGGER);
                break;
            }

            if (canApply)
            {
                gEffectBattler = gBattlerTarget;
                gBattleScripting.battler = gBattlerAttacker;
                gBattleScripting.moveEffect = status;
                gLastUsedAbility = ABILITY_PLAGUETOUCH;
                PushTraitStack(gBattlerAttacker, ABILITY_PLAGUETOUCH);
                BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
                effect++;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_MIRAGE)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && IsCustomAbilityDirectDamagingMove(gCurrentMove)
         && !(gBattleStruct->moveResultFlags[gBattlerTarget] & (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_FAILED))
         && IsBattlerWeatherAffected(gBattlerAttacker, B_WEATHER_SUN)
         && RandomPercentage(RNG_MIRAGE, 25)
         && CanBeConfused(gBattlerTarget))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
            gLastUsedAbility = ABILITY_MIRAGE;
            PushTraitStack(gBattlerAttacker, ABILITY_MIRAGE);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_BLIZZARD_HEART)
         && IsBattlerAlive(gBattlerTarget)
         && !gBattleStruct->unableToUseMove
         && IsBattlerWeatherAffected(gBattlerAttacker, B_WEATHER_ICY_ANY)
         && moveType == TYPE_ICE
         && IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         && RandomPercentage(RNG_BLIZZARD_HEART, 20)
         && CanSetNonVolatileStatus(gBattlerAttacker, gBattlerTarget, MOVE_EFFECT_FREEZE_OR_FROSTBITE, CHECK_TRIGGER))
        {
            gEffectBattler = gBattlerTarget;
            gBattleScripting.battler = gBattlerAttacker;
            gBattleScripting.moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE;
            gLastUsedAbility = ABILITY_BLIZZARD_HEART;
            PushTraitStack(gBattlerAttacker, ABILITY_BLIZZARD_HEART);
            BattleScriptCall(BattleScript_AbilityStatusEffectAtk);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_PENDULUM)
         && !gBattleStruct->unableToUseMove)
        {
            if (gBattleStruct->pendulumLastMove[gBattlerAttacker] == gCurrentMove)
                gBattleStruct->pendulumStreak[gBattlerAttacker] = min(gBattleStruct->pendulumStreak[gBattlerAttacker] + 1, 3);
            else
            {
                gBattleStruct->pendulumLastMove[gBattlerAttacker] = gCurrentMove;
                gBattleStruct->pendulumStreak[gBattlerAttacker] = 1;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_BLITZ)
         && !gBattleStruct->unableToUseMove)
        {
            if (gCurrentMove == MOVE_PROTECT && gProtectStructs[gBattlerAttacker].protected != PROTECT_NONE)
                gBattleStruct->blitzReady[gBattlerAttacker] = TRUE;
            else if (IsCustomAbilityDirectDamagingMove(gCurrentMove))
                gBattleStruct->blitzReady[gBattlerAttacker] = FALSE;
        }
        break;
    case ABILITYEFFECT_FORM_CHANGE_ON_HIT:
        speciesForm = gBattleMons[gBattlerTarget].species;
        ability = ABILITY_NONE;

        if (BattlerHasTrait(battler, ABILITY_AURA_SHIELD) && gBattleMons[battler].volatiles.auraShieldState == 1)
        {
            gBattleMons[battler].volatiles.auraShieldState = 2;
            gBattleScripting.battler = gBattlerAbility = battler;
            PushTraitStack(battler, ABILITY_AURA_SHIELD);
            BattleScriptCall(BattleScript_AuraShieldBlocks);
            effect++;
            break;
        }

        if (BattlerHasTrait(battler, ABILITY_DISGUISE))
            ability = ABILITY_DISGUISE;
        else if (BattlerHasTrait(battler, ABILITY_GULP_MISSILE))
            ability = ABILITY_GULP_MISSILE;
        else if (BattlerHasTrait(battler, ABILITY_ICE_FACE))
            ability = ABILITY_ICE_FACE;

        if (gBattleStruct->unableToUseMove
         || !IsBattlerTurnDamaged(gBattlerTarget, EXCLUDING_SUBSTITUTES)
         || !TryBattleFormChange(gBattlerTarget, FORM_CHANGE_BATTLE_HIT_BY_MOVE_CATEGORY))
            break;

        gBattleScripting.abilityPopupOverwrite = ability;
        gBattleScripting.battler = gBattlerAbility = battler;
        effect++;

        PushTraitStack(gBattlerTarget, ability);

        switch (ability)
        {
        case ABILITY_GULP_MISSILE:
            if (!IsBattlerAlive(gBattlerAttacker))
                break;

            if (!IsAbilityAndRecord(gBattlerAttacker, ABILITY_MAGIC_GUARD))
                SetPassiveDamageAmount(gBattlerAttacker, GetNonDynamaxMaxHP(gBattlerAttacker) / 4);

            switch (speciesForm)
            {
            case SPECIES_CRAMORANT_GORGING:
                BattleScriptCall(BattleScript_GulpMissileGorging);
                break;
            case SPECIES_CRAMORANT_GULPING:
                BattleScriptCall(BattleScript_GulpMissileGulping);
                break;
            default:
                BattleScriptCall(BattleScript_BattlerFormChange); // Fallback
                break;
            }
            break;
        case ABILITY_DISGUISE:
            if (GetConfig(B_DISGUISE_HP_LOSS))
                SetPassiveDamageAmount(gBattlerTarget, GetNonDynamaxMaxHP(gBattlerTarget) / 8);
            BattleScriptCall(BattleScript_BattlerFormChangeDisguise);
            break;
        case ABILITY_ICE_FACE:
            BattleScriptCall(BattleScript_IceFaceNullsDamage);
            break;
        default:
            BattleScriptCall(BattleScript_BattlerFormChange);
            break;
        }
        break;
    case ABILITYEFFECT_MOVE_END_OTHER: // Abilities that activate on *another* battler's moveend: Dancer, Soul-Heart, Receiver, Symbiosis
        if (IsBattlerAlive(battler) //Dancer SearchTraits handled elsewhere as Dancer may activate before Neutralization enters and should still go off
         && IsDanceMove(move)
         && !gSpecialStatuses[battler].dancerUsedMove
         && gBattlerAttacker != battler)
        {
            // Set bit and save Dancer mon's original target
            gSpecialStatuses[battler].dancerUsedMove = TRUE;
            gSpecialStatuses[battler].dancerOriginalTarget = gBattleStruct->moveTarget[battler] | 0x4;
            gBattleMons[battler].volatiles.activateDancer = FALSE;
            gBattlerAttacker = gBattlerAbility = battler;
            gCalledMove = move;

                // Set the target to the original target of the mon that first used a Dance move
                gBattlerTarget = gBattleStruct->dancerSavedTarget;

            // Make sure that the target isn't an ally - if it is, target the original user
            if (IsBattlerAlly(gBattlerTarget, gBattlerAttacker))
                gBattlerTarget = gBattleStruct->dancerSavedAttacker;
            PushTraitStack(battler, ABILITY_DANCER);
            BattleScriptExecute(BattleScript_DancerActivates);
            effect++;
        }
        break;
    case ABILITYEFFECT_MOVE_END_FOES_FAINTED:
        enum Stat stat = STAT_ATK;
        u32 numMonsFainted = 0;
        STORE_BATTLER_TRAITS(battler);

        if (SearchTraits(battlerTraits, ABILITY_MAGICIAN))
        {
            u32 slot, j, targetableSlots[MAX_MON_ITEMS];
            u32 index = 0;

            if (GetMoveEffect(move) != EFFECT_FLING
             && GetMoveEffect(move) != EFFECT_NATURAL_GIFT
             && IsBattlerAlive(battler)
             && !gSpecialStatuses[battler].gemBoost) // In base game, gems are consumed after magician would activate.
            {
                u32 numFoeMagicianTargets = 0;
                u32 numAllyMagicianTargets = 0;
                u32 foeMagicianTargets = 0;
                u32 allyMagicianTargets = 0;

                for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
                {
                    if (battlerDef != battler
                     && !BattlerHasHeldItem(battlerDef, ITEM_NONE, FALSE) // Skip battler early if no items to check (Multi)
                     && IsBattlerTurnDamaged(battlerDef, EXCLUDING_SUBSTITUTES)
                     && !GetBattlerPartyState(battlerDef)->isKnockedOff
                     && !DoesSubstituteBlockMove(battler, battlerDef, move))
                    {
                        if (IsBattlerAlly(battler, battlerDef))
                        {
                            allyMagicianTargets |= 1u << battlerDef;
                            numAllyMagicianTargets++;
                        }
                        else
                        {
                            foeMagicianTargets |= 1u << battlerDef;
                            numFoeMagicianTargets++;
                        }
                    }
                }

                if (numFoeMagicianTargets == 0 && numAllyMagicianTargets == 0)
                {
                    effect = FALSE;
                    break;
                }

                u32 magicianTargets = (numFoeMagicianTargets != 0) ? foeMagicianTargets : allyMagicianTargets;
                u32 numMagicianTargets = (numFoeMagicianTargets != 0) ? numFoeMagicianTargets : numAllyMagicianTargets;
                enum BattlerId battlers[MAX_BATTLERS_COUNT] = {0, 1, 2, 3};

                if (numMagicianTargets > 1)
                    SortBattlersBySpeed(battlers, (gFieldStatuses & STATUS_FIELD_TRICK_ROOM) != 0);

                for (u32 i = 0; i < gBattlersCount; i++)
                {
                    enum BattlerId targetBattler = battlers[i];
                    if (!(magicianTargets & 1u << targetBattler))
                        continue;

                    if (BattlerHasTrait(targetBattler, ABILITY_STICKY_HOLD) && IsBattlerAlive(targetBattler))
                    {
                        effect = FALSE;
                        break;
                    }

                    index = 0;
                    for (j = 0; j < MAX_MON_ITEMS; j++)
                        targetableSlots[j] = MAX_MON_ITEMS; //clear targetableSlots for each battler

                    for (j = 0; j < MAX_MON_ITEMS; j++) //Gather all stealable item slots
                    {
                        if (CanStealItem(battler, targetBattler, gBattleMons[targetBattler].items[j])
                            && gBattleMons[battler].items[j] == ITEM_NONE
                            && gBattleMons[targetBattler].items[j] != ITEM_NONE)
                        {
                            if (targetableSlots[0] != MAX_MON_ITEMS)
                                index++;
                            targetableSlots[index] = j;
                        }
                    }

                    if (targetableSlots[0] != MAX_MON_ITEMS)
                    {
                        slot = gLastItemSlot = GetSlot(targetableSlots, index);
                        StealTargetItem(battler, targetBattler, slot);
                        gBattlerAbility = battler;
                        gEffectBattler = targetBattler;
                        PushTraitStack(battler, ABILITY_MAGICIAN);
                        BattleScriptCall(BattleScript_MagicianActivates);
                        effect = TRUE;
                        break;
                    }
                }
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_MOXIE))
        {
            if (IsBattlerAlive(battler) && !NoAliveMonsForEitherParty())
            {
                stat = STAT_ATK;
                numMonsFainted = NumFaintedBattlersByAttacker(battler);

                if (numMonsFainted && CompareStat(battler, stat, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gLastUsedAbility = ABILITY_MOXIE;
                    SET_STATCHANGER(stat, numMonsFainted, FALSE);
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, stat);
                    gBattleScripting.animArg1 = GET_STAT_BUFF_ID(stat) + (numMonsFainted > 1 ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
                    PushTraitStack(battler, ABILITY_MOXIE);
                    BattleScriptCall(BattleScript_RaiseStatOnFaintingTargetMoxie);
                    effect = TRUE;
                }
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_ROCK_AND_STONE)
         && IsBattlerAlive(battler)
         && NumFaintedFoesByAttacker(battler))
        {
            enum BattleSide targetSide = BATTLE_OPPOSITE(GetBattlerSide(battler));

            if (!IsHazardOnSide(targetSide, HAZARDS_STEALTH_ROCK))
            {
                PushHazardTypeToQueue(targetSide, HAZARDS_STEALTH_ROCK);
                RecordAbilityBattle(battler, ABILITY_ROCK_AND_STONE);
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_CONSUME))
        {
            if (IsBattlerAlive(battler)
             && !NoAliveMonsForEitherParty()
             && !IsBattlerAtMaxHp(battler)
             && !(B_HEAL_BLOCKING >= GEN_5 && gBattleMons[battler].volatiles.healBlock))
            {
                numMonsFainted = NumFaintedFoesByAttacker(battler);

                if (numMonsFainted)
                {
                    s32 healAmount = (GetNonDynamaxMaxHP(battler) / 2) * numMonsFainted;

                    if (healAmount == 0)
                        healAmount = 1;
                    SetHealAmount(battler, healAmount);
                    PushTraitStack(battler, ABILITY_CONSUME);
                    BattleScriptCall(BattleScript_ConsumeActivates);
                    effect = TRUE;
                }
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_FILL_VOID))
        {
            if (IsBattlerAlive(battler)
             && !NoAliveMonsForEitherParty()
             && NumFaintedFoesByAttacker(battler)
            && (CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN)
             || CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN)))
            {
                gBattlerAttacker = gBattlerAbility = battler;
                PushTraitStack(battler, ABILITY_FILL_VOID);
                BattleScriptCall(BattleScript_FillVoidActivates);
                effect = TRUE;
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_ASH_ASSETS))
        {
            if (IsBattlerAlive(battler)
             && !NoAliveMonsForEitherParty()
             && NumFaintedFoesByAttacker(battler)
             && !(gFieldStatuses & STATUS_FIELD_SCORCHED_FIELD))
            {
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_SCORCHED_FIELD))
                {
                    gBattleScripting.battler = gBattlerAbility = battler;
                    PushTraitStack(battler, ABILITY_ASH_ASSETS);
                    BattleScriptCall(BattleScript_HeatstormActivates);
                    effect = TRUE;
                }
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_CHILLING_NEIGH)
        || SearchTraits(battlerTraits, ABILITY_AS_ONE_ICE_RIDER))
        {
            if (IsBattlerAlive(battler) && !NoAliveMonsForEitherParty())
            {
                stat = STAT_ATK;
                numMonsFainted = NumFaintedBattlersByAttacker(battler);

                if (numMonsFainted && CompareStat(battler, stat, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gLastUsedAbility = ABILITY_CHILLING_NEIGH;
                    if (SearchTraits(battlerTraits, ABILITY_AS_ONE_ICE_RIDER))
                        gBattleScripting.abilityPopupOverwrite = ABILITY_CHILLING_NEIGH;

                    SET_STATCHANGER(stat, numMonsFainted, FALSE);
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, stat);
                    gBattleScripting.animArg1 = GET_STAT_BUFF_ID(stat) + (numMonsFainted > 1 ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
                    PushTraitStack(battler, ABILITY_CHILLING_NEIGH);
                    BattleScriptCall(BattleScript_RaiseStatOnFaintingTargetChilling);
                    effect = TRUE;
                }
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_GRIM_NEIGH)
        || SearchTraits(battlerTraits, ABILITY_AS_ONE_SHADOW_RIDER))
        {
            if (IsBattlerAlive(battler) && !NoAliveMonsForEitherParty())
            {
                stat = STAT_SPATK;
                numMonsFainted = NumFaintedBattlersByAttacker(battler);

                if (numMonsFainted && CompareStat(battler, stat, MAX_STAT_STAGE, CMP_LESS_THAN))
                {

                    gLastUsedAbility = ABILITY_GRIM_NEIGH;
                    if (SearchTraits(battlerTraits, ABILITY_AS_ONE_SHADOW_RIDER))
                        gBattleScripting.abilityPopupOverwrite = ABILITY_GRIM_NEIGH;

                    SET_STATCHANGER(stat, numMonsFainted, FALSE);
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, stat);
                    gBattleScripting.animArg1 = GET_STAT_BUFF_ID(stat) + (numMonsFainted > 1 ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
                    PushTraitStack(battler, ABILITY_GRIM_NEIGH);
                    BattleScriptCall(BattleScript_RaiseStatOnFaintingTargetGrim);
                    effect = TRUE;
                }
            }
        }
        ability = ABILITY_NONE;
        if (SearchTraits(battlerTraits, ABILITY_EELEVATE))
            ability = ABILITY_EELEVATE;
        else if (SearchTraits(battlerTraits, ABILITY_BEAST_BOOST))
            ability = ABILITY_BEAST_BOOST;

        if (ability != ABILITY_NONE)
        {
            if (IsBattlerAlive(battler) && !NoAliveMonsForEitherParty())
            {
                stat = GetHighestStatId(battler);
                if (ability == ABILITY_EELEVATE)
                    numMonsFainted = NumFaintedFoesByAttacker(battler);
                else
                    numMonsFainted = NumFaintedBattlersByAttacker(battler);

                if (numMonsFainted && CompareStat(battler, stat, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gLastUsedAbility = ability;
                    SET_STATCHANGER(stat, numMonsFainted, FALSE);
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, stat);
                    gBattleScripting.animArg1 = GET_STAT_BUFF_ID(stat) + (numMonsFainted > 1 ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
                    PushTraitStack(battler, ability);
                    BattleScriptCall(BattleScript_RaiseStatOnFaintingTargetBeastBoost);
                    effect = TRUE;
                }
            }
        }
        if (SearchTraits(battlerTraits, ABILITY_BATTLE_BOND))
        {
            if (IsBattlerAlive(battler)
             && !NoAliveMonsForEitherParty()
             && !NumFaintedBattlersByAttacker(battler) == 0)
            {

                if (!GetBattlerPartyState(battler)->battleBondBoost)
                {
                    if (GetConfig(B_BATTLE_BOND) < GEN_9 && gBattleMons[battler].species == SPECIES_GRENINJA_BATTLE_BOND)
                    {
                        gLastUsedAbility = ABILITY_BATTLE_BOND;
                        GetBattlerPartyState(battler)->battleBondBoost = TRUE;
                        PREPARE_SPECIES_BUFFER(gBattleTextBuff1, gBattleMons[battler].species);
                        TryBattleFormChange(battler, FORM_CHANGE_BATTLE_BOND);
                        PushTraitStack(battler, ABILITY_BATTLE_BOND);
                        BattleScriptCall(BattleScript_BattleBondActivatesOnMoveEndAttacker);
                        effect = TRUE;
                    }
                    else
                    {
                        u32 numStatBuffs = 0;
                        enum Stat firstStat = STAT_HP;

                        if (CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                        {
                            firstStat = STAT_ATK;
                            numStatBuffs++;
                        }
                        if (CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                        {
                            if (firstStat == STAT_HP)
                                firstStat = STAT_SPATK;
                            numStatBuffs++;
                        }
                        if (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
                        {
                            if (firstStat == STAT_HP)
                                firstStat = STAT_SPEED;
                            numStatBuffs++;
                        }

                        if (numStatBuffs > 0)
                        {
                            gBattleScripting.animArg1 = GetStatChangeAnimationId(firstStat, FALSE, FALSE);
                            gLastUsedAbility = ABILITY_BATTLE_BOND;
                            gBattlerAbility = battler;
                            PushTraitStack(battler, ABILITY_BATTLE_BOND);
                            GetBattlerPartyState(battler)->battleBondBoost = TRUE;
                            BattleScriptCall(BattleScript_EffectBattleBondStatIncrease);
                            effect = TRUE;
                        }
                    }
                }
            }
        }
        break;
    case ABILITYEFFECT_OPPORTUNIST:
        if ((BattlerHasTrait(battler, ABILITY_OPPORTUNIST) || BattlerHasTrait(battler, ABILITY_TETHER))
             && gProtectStructs[battler].activateOpportunist == 2)
            {
                gBattleScripting.battler = battler;
                gProtectStructs[battler].activateOpportunist--;
                ChooseStatBoostAnimation(battler);
                PushTraitStack(battler, BattlerHasTrait(battler, ABILITY_TETHER) ? ABILITY_TETHER : ABILITY_OPPORTUNIST);
                BattleScriptCall(BattleScript_OpportunistCopyStatChange);
                effect = 1;
            }
        break;
    case ABILITYEFFECT_IMMUNITY:
        effect = TryImmunityAbilityHealStatus(battler);
        if (effect)
                return effect;
        break;
    case ABILITYEFFECT_SYNCHRONIZE:
        if (SearchTraits(battlerTraits, ABILITY_SYNCHRONIZE) && gBattleStruct->synchronizeMoveEffect != MOVE_EFFECT_NONE)
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerTarget;
            RecordAbilityBattle(gBattlerTarget, ABILITY_SYNCHRONIZE);

            if (GetConfig(B_SYNCHRONIZE_TOXIC) < GEN_5 && gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

            if (CanSetNonVolatileStatus(
                    gBattlerTarget,
                    gBattlerAttacker,

                    gBattleStruct->synchronizeMoveEffect,
                    CHECK_TRIGGER))
            {
                gEffectBattler = gBattlerAttacker;
                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, ABILITY_SYNCHRONIZE);
                PushTraitStack(battler, ABILITY_SYNCHRONIZE);
                BattleScriptCall(BattleScript_SynchronizeActivates);
                effect++;
            }
            else // Synchronize ability pop up still shows up even if status fails
            {
                PushTraitStack(battler, ABILITY_SYNCHRONIZE);
                BattleScriptCall(BattleScript_AbilityPopUp);
            }
            gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;
        }
        break;
    case ABILITYEFFECT_ATK_SYNCHRONIZE:
        if (SearchTraits(battlerTraits, ABILITY_SYNCHRONIZE) && gBattleStruct->synchronizeMoveEffect != MOVE_EFFECT_NONE)
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
            RecordAbilityBattle(gBattlerAttacker, ABILITY_SYNCHRONIZE);

            if (GetConfig(B_SYNCHRONIZE_TOXIC) < GEN_5 && gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

            if (CanSetNonVolatileStatus(
                    gBattlerAttacker,
                    gBattlerTarget,
                    gBattleStruct->synchronizeMoveEffect,
                    CHECK_TRIGGER))
            {
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

                gEffectBattler = gBattlerTarget;
                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, ABILITY_SYNCHRONIZE);
                PushTraitStack(battler, ABILITY_SYNCHRONIZE);
                BattleScriptCall(BattleScript_SynchronizeActivates);
                effect++;
            }
            else // Synchronize ability pop up still shows up even if status fails
            {
                PushTraitStack(battler, ABILITY_SYNCHRONIZE);
                BattleScriptCall(BattleScript_AbilityPopUp);
            }
            gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;
        }
        break;
    case ABILITYEFFECT_TERA_SHIFT:
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_TERA_SHIFT)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && TryBattleFormChange(battler, FORM_CHANGE_BATTLE_SWITCH_IN))
        {
            gBattleScripting.battler = battler;
            gBattleScripting.abilityPopupOverwrite = gLastUsedAbility = ABILITY_TERA_SHIFT;
            effect += CommonSwitchInAbilities(battler, ABILITY_TERA_SHIFT, traitCheck, BattleScript_BattlerFormChangeWithString);
        }
        break;
    case ABILITYEFFECT_NEUTRALIZINGGAS:
        // Prints message only. separate from ABILITYEFFECT_ON_SWITCHIN bc activates before entry hazards
        if (SearchTraits(battlerTraits, ABILITY_NEUTRALIZING_GAS) && !gBattleMons[battler].volatiles.neutralizingGas)
        {
            if (SearchTraits(battlerTraits, ABILITY_NEUTRALIZING_GAS) > 1)
            {
                // Neutralizing Gas negates all Main Abilities and should not be an Innate.
                DebugPrintf("Neutralizing Gas not set as main Ability");
            }
            else
            {
                gBattleMons[battler].volatiles.neutralizingGas = TRUE;
                gBattlerAbility = battler;
                PushTraitStack(battler, ABILITY_NEUTRALIZING_GAS);
                BattleScriptCall(BattleScript_NeutralizingGasActivates);
                effect++;
            }
        }
        break;
    case ABILITYEFFECT_UNNERVE:
    {
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_UNNERVE)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && !gBattleMons[battler].volatiles.unnerveActivated)
        {
            gBattleScripting.battler = battler;
            gEffectBattler2 = GetOppositeBattler(battler);
            gBattleMons[battler].volatiles.unnerveActivated = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_UNNERVE, traitCheck, BattleScript_UnnerveActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_AS_ONE_ICE_RIDER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && !gBattleMons[battler].volatiles.unnerveActivated)
        {
            gBattleScripting.battler = battler;
            gEffectBattler2 = GetOppositeBattler(battler);
            gBattleMons[battler].volatiles.unnerveActivated = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_AS_ONE_ICE_RIDER, traitCheck, BattleScript_ActivateAsOne);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_AS_ONE_SHADOW_RIDER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger && !gBattleMons[battler].volatiles.unnerveActivated)
        {
            gBattleScripting.battler = battler;
            gEffectBattler2 = GetOppositeBattler(battler);
            gBattleMons[battler].volatiles.unnerveActivated = TRUE;
            effect += CommonSwitchInAbilities(battler, ABILITY_AS_ONE_SHADOW_RIDER, traitCheck, BattleScript_ActivateAsOne);
        }
    }
    break;
    case ABILITYEFFECT_COMMANDER:
        gBattleScripting.battler = battler;
        partner = BATTLE_PARTNER(battler);
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_COMMANDER)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && IsBattlerAlive(partner)
         && IsBattlerAlive(battler)
         && gBattleStruct->battlerState[partner].commanderSpecies == SPECIES_NONE
         && gBattleMons[partner].species == SPECIES_DONDOZO
         && (gChosenActionByBattler[partner] != B_ACTION_SWITCH || HasBattlerActedThisTurn(partner))
         && GET_BASE_SPECIES_ID(GetMonData(GetBattlerMon(battler), MON_DATA_SPECIES)) == SPECIES_TATSUGIRI)
        {
            SaveBattlerAttacker(gBattlerAttacker);
            gBattlerAttacker = partner;
            gBattleStruct->battlerState[battler].commandingDondozo = TRUE;
            gBattleStruct->battlerState[partner].commanderSpecies = gBattleMons[battler].species;
            gBattleMons[battler].volatiles.semiInvulnerable = STATE_COMMANDER;
            if (gBattleMons[battler].volatiles.confusionTurns > 0 && !gBattleMons[battler].volatiles.infiniteConfusion)
                gBattleMons[battler].volatiles.confusionTurns--;
            BtlController_EmitSpriteInvisibility(battler, B_COMM_TO_CONTROLLER, TRUE);
            MarkBattlerForControllerExec(battler);
            effect += CommonSwitchInAbilities(battler, ABILITY_COMMANDER, traitCheck, BattleScript_CommanderActivates);
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_HOSPITALITY))
         && shouldAbilityTrigger)
        {
            if (!gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
             && IsDoubleBattle()
             && !gBattleMons[partner].volatiles.healBlock
             && gBattleMons[partner].hp < gBattleMons[partner].maxHP
             && IsBattlerAlive(partner))
            {
                gEffectBattler = partner;
                SetHealAmount(partner, GetNonDynamaxMaxHP(partner) / 4);
                effect += CommonSwitchInAbilities(battler, ABILITY_HOSPITALITY, traitCheck, BattleScript_HospitalityActivates);
            }
        }
        if ((traitCheck = SearchTraits(battlerTraits, ABILITY_COSTAR)) && !gSpecialStatuses[battler].switchInTraitDone[traitCheck - 1]
         && shouldAbilityTrigger
         && IsDoubleBattle()
         && IsBattlerAlive(partner)
         && BattlerHasCopyableChanges(partner)
         && !SearchTraits(battlerTraits, ABILITY_CURIOUS_MEDICINE)) // Curious Medicine would negate Costar so it's one or the other
        {
            for (i = 0; i < NUM_BATTLE_STATS; i++)
                gBattleMons[battler].statStages[i] = gBattleMons[partner].statStages[i];
            // Copy crit boosts (Focus Energy, Dragon Cheer, G-Max Chi Strike)
            gBattleMons[battler].volatiles.focusEnergy = gBattleMons[partner].volatiles.focusEnergy;
            gBattleMons[battler].volatiles.dragonCheer = gBattleMons[partner].volatiles.dragonCheer;
            gBattleMons[battler].volatiles.bonusCritStages = gBattleMons[partner].volatiles.bonusCritStages;
            gEffectBattler = partner;
            effect += CommonSwitchInAbilities(battler, ABILITY_COSTAR, traitCheck, BattleScript_CostarActivates);
        }
        break;
    case ABILITYEFFECT_ON_WEATHER: // For ability effects that activate when the battle weather changes.
        if (!IsBattlerAlive(battler))
            return effect;

        ability = ABILITY_NONE;
        if (SearchTraits(battlerTraits, ABILITY_FORECAST))
            ability = ABILITY_FORECAST;
        else if (SearchTraits(battlerTraits, ABILITY_FLOWER_GIFT))
            ability = ABILITY_FLOWER_GIFT;
        else if (SearchTraits(battlerTraits, ABILITY_ICE_FACE))
            ability = ABILITY_ICE_FACE;

        if (ability != ABILITY_NONE)
        {
            bool32 battlerWeatherAffected = IsBattlerWeatherAffected(battler, gBattleWeather);
            if (battlerWeatherAffected && !CanBattlerFormChange(battler, FORM_CHANGE_BATTLE_WEATHER))
            {
                // If Hail/Snow activates when in Eiscue is in base, prevent reversion when Eiscue Noice gets broken
                gBattleMons[battler].volatiles.weatherAbilityDone = TRUE;
            }

            if (((!gBattleMons[battler].volatiles.weatherAbilityDone && battlerWeatherAffected)
             || gBattleWeather == B_WEATHER_NONE
             || !HasWeatherEffect()) // Air Lock active
             && TryBattleFormChange(battler, FORM_CHANGE_BATTLE_WEATHER))
            {
                gLastUsedAbility = ability;
                gBattleScripting.battler = battler;
                gBattleMons[battler].volatiles.transformWeatherAbilityDone = TRUE;
                PushTraitStack(battler, ability);
                BattleScriptCall(BattleScript_BattlerFormChangeWithString);
                effect++;
            }
        }

       if (SearchTraits(battlerTraits, ABILITY_PROTOSYNTHESIS)
         && !gBattleMons[battler].volatiles.weatherAbilityDone
         && (gBattleWeather & B_WEATHER_SUN) && HasWeatherEffect()
         && !gBattleMons[battler].volatiles.transformed
         && !gBattleMons[battler].volatiles.boosterEnergyActivated)
       {
            gLastUsedAbility = ABILITY_PROTOSYNTHESIS;
            gBattleMons[battler].volatiles.weatherAbilityDone = TRUE;
            gBattleMons[battler].volatiles.paradoxBoostedStat = GetParadoxHighestStatId(battler);
            PREPARE_STAT_BUFFER(gBattleTextBuff1, gBattleMons[battler].volatiles.paradoxBoostedStat);
            gBattleScripting.battler = battler;
            PushTraitStack(battler, ABILITY_PROTOSYNTHESIS);
            BattleScriptCall(BattleScript_ProtosynthesisActivates);
            effect++;
       }
       break;
    case ABILITYEFFECT_ON_TERRAIN:  // For ability effects that activate when the field terrain changes.
        if (!IsBattlerAlive(battler))
            return effect;

        if (SearchTraits(battlerTraits, ABILITY_MIMICRY)
         && !gBattleMons[battler].volatiles.terrainAbilityDone && ChangeTypeBasedOnTerrain(battler))
        {
            gLastUsedAbility = ABILITY_MIMICRY;
            gBattleMons[battler].volatiles.terrainAbilityDone = TRUE;
            ChangeTypeBasedOnTerrain(battler);
            gBattlerAbility = gBattleScripting.battler = battler;
            PushTraitStack(battler, ABILITY_MIMICRY);
            BattleScriptCall(BattleScript_MimicryActivates);
            effect++;
        }
        if (SearchTraits(battlerTraits, ABILITY_QUARK_DRIVE)
         && !gBattleMons[battler].volatiles.terrainAbilityDone
         && gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN
         && !gBattleMons[battler].volatiles.transformed
         && !gBattleMons[battler].volatiles.boosterEnergyActivated)
        {
            gLastUsedAbility = ABILITY_QUARK_DRIVE;
            gBattleMons[battler].volatiles.terrainAbilityDone = TRUE;
            gBattleMons[battler].volatiles.paradoxBoostedStat = GetParadoxHighestStatId(battler);
            PREPARE_STAT_BUFFER(gBattleTextBuff1, gBattleMons[battler].volatiles.paradoxBoostedStat);
            gBattlerAbility = gBattleScripting.battler = battler;
            PushTraitStack(battler, ABILITY_QUARK_DRIVE);
            BattleScriptCall(BattleScript_QuarkDriveActivates);
            effect++;
        }
        break;
    }

    if (effect)
    {
        RecordAbilityBattle(battler, gLastUsedAbility);
        gBattlerAbility = battler;
    }
    return effect;
}

bool32 TryPrimalReversion(enum BattlerId battler)
{
    if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_PRIMAL_REVERSION))
    {
        gBattleScripting.battler = battler;
        BattleScriptCall(BattleScript_PrimalReversion);
        return TRUE;
    }
    return FALSE;
}

bool32 IsNeutralizingGasOnField(void)
{
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (gBattleMons[i].volatiles.neutralizingGas && !gBattleMons[i].volatiles.gastroAcid)
            return TRUE;
    }

    return FALSE;
}

bool32 HasMoldBreakerTypeAbility(enum BattlerId battler)
{
    enum Ability foundAbility = ABILITY_NONE;
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battler);

    if (gAiLogicData->aiCalcInProgress)
        battlerTraits[0] = gAiLogicData->abilities[battler];

    if (gBattleMons[battler].volatiles.gastroAcid)
        return FALSE;

    if (SearchTraits(battlerTraits, ABILITY_TERAVOLT))
        foundAbility = ABILITY_TERAVOLT;
    else if (SearchTraits(battlerTraits, ABILITY_TURBOBLAZE))
        foundAbility = ABILITY_TURBOBLAZE;
    else if (SearchTraits(battlerTraits, ABILITY_MOLD_BREAKER))
        foundAbility = ABILITY_MOLD_BREAKER;
    else if ((SearchTraits(battlerTraits, ABILITY_MYCELIUM_MIGHT)) && IsBattleMoveStatus(gCurrentMove))
        foundAbility = ABILITY_MYCELIUM_MIGHT;
    
    if (foundAbility != ABILITY_NONE)
    {
        RecordAbilityBattle(battler, foundAbility);
        return TRUE;
    }

    return FALSE;
}

static inline bool32 CanBreakThroughAbility(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability ability, bool32 hasAbilityShield, bool32 ignoreMoldBreaker)
{
    if (ability == ABILITY_NONE)
        ability = gBattleMons[battlerDef].ability;

    if (hasAbilityShield || ignoreMoldBreaker || battlerDef == battlerAtk)
        return FALSE;

    return gBattleStruct->moldBreakerActive && gAbilitiesInfo[ability].breakable;
}

enum Ability GetBattlerAbilityNoAbilityShield(enum BattlerId battler)
{
    return GetBattlerAbilityInternal(battler, FALSE, TRUE);
}

enum Ability GetBattlerAbilityIgnoreMoldBreaker(enum BattlerId battler)
{
    return GetBattlerAbilityInternal(battler, TRUE, FALSE);
}

enum Ability GetBattlerAbility(enum BattlerId battler)
{
    return GetBattlerAbilityInternal(battler, FALSE, FALSE);
}

enum Ability GetBattlerAbilityInternal(enum BattlerId battler, bool32 ignoreMoldBreaker, bool32 noAbilityShield)
{
    bool32 hasAbilityShield = !noAbilityShield && BattlerHasHeldItemEffectIgnoreAbility(battler, HOLD_EFFECT_ABILITY_SHIELD, TRUE);
    bool32 abilityCantBeSuppressed = gAbilitiesInfo[gBattleMons[battler].ability].cantBeSuppressed;

    if (abilityCantBeSuppressed)
    {
        // Edge case: pokemon under the effect of gastro acid transforms into a pokemon with Comatose (Todo: verify how other unsuppressable abilities behave)
        if (gBattleMons[battler].volatiles.transformed
         && gBattleMons[battler].volatiles.gastroAcid
         && gBattleMons[battler].ability == ABILITY_COMATOSE)
            return ABILITY_NONE;

        if (CanBreakThroughAbility(gBattlerAttacker, battler, ABILITY_NONE, hasAbilityShield, ignoreMoldBreaker))
            return ABILITY_NONE;

        return gBattleMons[battler].ability;
    }

    if (gBattleMons[battler].volatiles.gastroAcid)
        return ABILITY_NONE;

    if (!hasAbilityShield
     && IsNeutralizingGasOnField()
     && (gBattleMons[battler].ability != ABILITY_NEUTRALIZING_GAS || gBattleMons[battler].volatiles.gastroAcid)) // Neutralizing Gas should be a Main Ability
        return ABILITY_NONE;

    if (CanBreakThroughAbility(gBattlerAttacker, battler, ABILITY_NONE, hasAbilityShield, ignoreMoldBreaker))
        return ABILITY_NONE;

    return gBattleMons[battler].ability;
}

// Used for Held Item Checks to avoid infinite loops
u32 BattlerHasKlutz(u32 battler)
{
    if (gBattleMons[battler].volatiles.gastroAcid)
        return FALSE;

    if (IsNeutralizingGasOnField()
     && gBattleMons[battler].ability != ABILITY_NEUTRALIZING_GAS)
        return FALSE;

    return BattlerHasTrait(battler, ABILITY_KLUTZ) || BattlerHasTrait(battler, ABILITY_UNLEASHED);
}

u32 IsAbilityOnSide(enum BattlerId battler, enum Ability ability)
{
    if (IsBattlerAlive(battler) && BattlerHasTrait(battler, ability))
        return battler + 1;
    else if (IsBattlerAlive(BATTLE_PARTNER(battler)) && BattlerHasTrait(BATTLE_PARTNER(battler), ability))
        return BATTLE_PARTNER(battler) + 1;
    else
        return 0;
}

u32 IsAbilityOnOpposingSide(enum BattlerId battler, enum Ability ability)
{
    return IsAbilityOnSide(BATTLE_OPPOSITE(battler), ability);
}

u32 IsAbilityOnField(enum Ability ability)
{
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerAlive(i) && BattlerHasTrait(i, ability))
            return i + 1;
    }

    return 0;
}

u32 IsAbilityOnFieldExcept(enum BattlerId battler, enum Ability ability)
{
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (i != battler && IsBattlerAlive(i) && BattlerHasTrait(i, ability))
            return i + 1;
    }

    return 0;
}

u32 IsAbilityPreventingEscape(enum BattlerId battler)
{
    if (GetConfig(B_GHOSTS_ESCAPE) >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return 0;

    bool32 isBattlerGrounded = IsBattlerGrounded(battler);
    for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
    {
        if (battler == battlerDef || IsBattlerAlly(battler, battlerDef))
            continue;

        if (BattlerHasTrait(battlerDef, ABILITY_SHADOW_TAG) && (B_SHADOW_TAG_ESCAPE <= GEN_3 || !BattlerHasTrait(battler, ABILITY_SHADOW_TAG)))
        {
            gDisplayAbility = ABILITY_SHADOW_TAG;
                return battlerDef + 1;

        }
        if (BattlerHasTrait(battlerDef, ABILITY_ARENA_TRAP) && isBattlerGrounded)
        {
            gDisplayAbility = ABILITY_ARENA_TRAP;
            return battlerDef + 1;

        }
        if (BattlerHasTrait(battlerDef, ABILITY_MAGNET_PULL) && IS_BATTLER_OF_TYPE(battler, TYPE_STEEL))
        {
            gDisplayAbility = ABILITY_MAGNET_PULL;
            return battlerDef + 1;
        }
    }

    return 0;
}

bool32 CanBattlerEscape(enum BattlerId battler) // no ability check
{
    if (gBattleStruct->battlerState[battler].commanderSpecies != SPECIES_NONE)
        return FALSE;
    else if (GetConfig(B_GHOSTS_ESCAPE) >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return TRUE;
    else if (gBattleMons[battler].volatiles.escapePrevention)
        return FALSE;
    else if (gBattleMons[battler].volatiles.wrapped)
        return FALSE;
    else if (gBattleMons[battler].volatiles.root)
        return FALSE;
    else if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)
        return FALSE;
    else if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_SKY_DROP)
        return FALSE;
    else
        return TRUE;
}

bool32 IsPsychicTerrainAffected(enum BattlerId battler, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler,fieldStatuses, STATUS_FIELD_PSYCHIC_TERRAIN);
}

bool32 IsMistyTerrainAffected(enum BattlerId battler, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, fieldStatuses, STATUS_FIELD_MISTY_TERRAIN);
}

bool32 IsGrassyTerrainAffected(enum BattlerId battler, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, fieldStatuses, STATUS_FIELD_GRASSY_TERRAIN);
}

bool32 IsElectricTerrainAffected(enum BattlerId battler, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, fieldStatuses, STATUS_FIELD_ELECTRIC_TERRAIN);
}

bool32 IsAnyTerrainAffected(enum BattlerId battler, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, fieldStatuses, STATUS_FIELD_TERRAIN_ANY);
}

bool32 IsBattlerTerrainAffected(enum BattlerId battler, u32 fieldStatus, u32 terrainFlag)
{
    if (!(fieldStatus & terrainFlag))
        return FALSE;
    if (IsSemiInvulnerable(battler, CHECK_ALL))
        return FALSE;

    return IsBattlerGrounded(battler);
}

enum Stat GetHighestStatId(enum BattlerId battler)
{
    enum Stat highestId = STAT_ATK;
    bool32 wonderRoom = (gFieldStatuses & STATUS_FIELD_WONDER_ROOM) != 0;
    u32 highestStat = gBattleMons[battler].attack;

    for (u32 stat = STAT_DEF; stat < NUM_STATS; stat++)
    {
        if (stat == STAT_SPEED)
            continue;

        u32 statVal;
        switch (stat)
        {
        case STAT_ATK:
            statVal = gBattleMons[battler].attack;
            break;
        case STAT_DEF:
            statVal = wonderRoom ? gBattleMons[battler].spDefense : gBattleMons[battler].defense;
            break;
        case STAT_SPATK:
            statVal = gBattleMons[battler].spAttack;
            break;
        case STAT_SPDEF:
            statVal = wonderRoom ? gBattleMons[battler].defense : gBattleMons[battler].spDefense;
            break;
        default:
            continue;
        }

        if (statVal > highestStat)
        {
            highestStat = statVal;
            highestId = stat;
        }
    }

    if (gBattleMons[battler].speed > highestStat)
        highestId = STAT_SPEED;

    return highestId;
}

static u32 GetStatValueWithStages(enum BattlerId battler, enum Stat stat)
{
    u32 statValue;

    switch (stat)
    {
    case STAT_ATK:
        statValue = gBattleMons[battler].attack;
        break;
    case STAT_DEF:
        statValue = gBattleMons[battler].defense;
        break;
    case STAT_SPATK:
        statValue = gBattleMons[battler].spAttack;
        break;
    case STAT_SPDEF:
        statValue = gBattleMons[battler].spDefense;
        break;
    case STAT_SPEED:
        statValue = gBattleMons[battler].speed;
        break;
    default:
        return 0;
    }

    statValue *= gStatStageRatios[gBattleMons[battler].statStages[stat]][0];
    statValue /= gStatStageRatios[gBattleMons[battler].statStages[stat]][1];

    return statValue;
}

enum Stat GetParadoxHighestStatId(enum BattlerId battler)
{
    enum Stat highestId = STAT_ATK;
    bool32 wonderRoom = gFieldStatuses & STATUS_FIELD_WONDER_ROOM;
    u32 highestStat = GetStatValueWithStages(battler, STAT_ATK);

    for (u32 stat = STAT_DEF; stat < NUM_STATS; stat++)
    {
        if (stat == STAT_SPEED)
            continue;

        u32 statValue;
        switch (stat)
        {
        case STAT_DEF:
            statValue = wonderRoom ? gBattleMons[battler].spDefense : gBattleMons[battler].defense;
            statValue *= gStatStageRatios[gBattleMons[battler].statStages[STAT_DEF]][0];
            statValue /= gStatStageRatios[gBattleMons[battler].statStages[STAT_DEF]][1];
            break;
        case STAT_SPDEF:
            statValue = wonderRoom ? gBattleMons[battler].defense : gBattleMons[battler].spDefense;
            statValue *= gStatStageRatios[gBattleMons[battler].statStages[STAT_SPDEF]][0];
            statValue /= gStatStageRatios[gBattleMons[battler].statStages[STAT_SPDEF]][1];
            break;
        default:
            statValue = GetStatValueWithStages(battler, stat);
            break;
        }
        if (statValue > highestStat)
        {
            highestStat = statValue;
            highestId = stat;
        }
    }

    u32 speed = GetStatValueWithStages(battler, STAT_SPEED);
    if (speed > highestStat)
        highestId = STAT_SPEED;

    return highestId;
}

static void ResetParadoxWeatherStat(enum BattlerId battler)
{
    if (BattlerHasTrait(battler, ABILITY_PROTOSYNTHESIS)
     && !gBattleMons[battler].volatiles.boosterEnergyActivated)
        gBattleMons[battler].volatiles.paradoxBoostedStat = 0;
}

static void ResetParadoxTerrainStat(enum BattlerId battler)
{
    if (BattlerHasTrait(battler, ABILITY_QUARK_DRIVE)
     && !gBattleMons[battler].volatiles.boosterEnergyActivated)
        gBattleMons[battler].volatiles.paradoxBoostedStat = 0;
}

enum Stat GetParadoxBoostedStatId(enum BattlerId battler)
{
    if (gBattleMons[battler].volatiles.paradoxBoostedStat == 0)
        gBattleMons[battler].volatiles.paradoxBoostedStat = GetParadoxHighestStatId(battler);

    return gBattleMons[battler].volatiles.paradoxBoostedStat;
}

bool32 CanBeSlept(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum SleepClauseBlock isBlockedBySleepClause)
{
    if (IsSleepClauseActiveForSide(GetBattlerSide(battlerDef)) && isBlockedBySleepClause != NOT_BLOCKED_BY_SLEEP_CLAUSE)
        return FALSE;

    if (isBlockedBySleepClause == NOT_BLOCKED_BY_SLEEP_CLAUSE)
        gBattleStruct->sleepClauseNotBlocked = TRUE;

    bool32 effect = FALSE;
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            MOVE_EFFECT_SLEEP, // also covers yawn
            CHECK_TRIGGER))
        effect = TRUE;

    gBattleStruct->sleepClauseNotBlocked = FALSE;
    return effect;
}

bool32 CanBePoisoned(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            MOVE_EFFECT_TOXIC, // also covers poison
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

// TODO: check order of battlerAtk and battlerDef
bool32 CanBeBurned(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            MOVE_EFFECT_BURN,
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

bool32 CanBeParalyzed(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            MOVE_EFFECT_PARALYSIS,
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

bool32 CanBeFrozen(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            MOVE_EFFECT_FREEZE,
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}
// Unused, technically also redundant because it is just a copy of CanBeFrozen
bool32 CanGetFrostbite(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            MOVE_EFFECT_FREEZE_OR_FROSTBITE, // also covers frostbite
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

bool32 IsSafeguardProtected(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (!(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_SAFEGUARD))
        return FALSE;
    if (IsBattlerAlly(battlerAtk, battlerDef))
        return TRUE;
    if (BattlerHasTrait(battlerAtk, ABILITY_INFILTRATOR) || BattlerHasTrait(battlerAtk, ABILITY_VOIDTOUCH))
        return FALSE;
    return TRUE;
}

bool32 CanSetNonVolatileStatus(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum MoveEffect effect, enum ResultOption option)
{
    const u8 *battleScript = NULL;
    u32 sideBattler = 0;
    bool32 abilityAffected = FALSE;
    enum Ability abilityDef = ABILITY_NONE;
    enum Ability battlerTraits[MAX_MON_TRAITS];
    enum Ability AIBattlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battlerDef);
    AI_STORE_BATTLER_TRAITS(battlerDef);

    // Move specific checks
    switch (effect)
    {
    case MOVE_EFFECT_POISON:
    case MOVE_EFFECT_TOXIC:

        if (gBattleMons[battlerDef].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON))
        {
            battleScript = BattleScript_AlreadyPoisoned;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_IMMUNITY) : SearchTraits(battlerTraits, ABILITY_IMMUNITY))
        {
            gLastUsedAbility = abilityDef = ABILITY_IMMUNITY;
            PushTraitStack(battlerDef, ABILITY_IMMUNITY);
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        else if ((sideBattler = IsAbilityOnSide(battlerDef, ABILITY_PASTEL_VEIL)))
        {
            gLastUsedAbility = abilityDef = ABILITY_PASTEL_VEIL;
            abilityAffected = TRUE;
            battlerDef = sideBattler - 1;
            PushTraitStack(battlerDef, ABILITY_PASTEL_VEIL);
            battleScript = BattleScript_ImmunityProtected;
        }
        else if (!BattlerHasTrait(battlerAtk, ABILITY_CORROSION)
              && (IS_BATTLER_ANY_TYPE(battlerDef, TYPE_POISON, TYPE_STEEL)
               || (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_VALKYRIE) : SearchTraits(battlerTraits, ABILITY_VALKYRIE))))
        {
            battleScript = BattleScript_NotAffected;
        }
        break;
    case MOVE_EFFECT_PARALYSIS:
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS)
        {
            battleScript = BattleScript_AlreadyParalyzed;
        }
        else if (GetConfig(B_PARALYZE_ELECTRIC) >= GEN_6 && IS_BATTLER_OF_TYPE(battlerDef, TYPE_ELECTRIC))
        {
            battleScript = BattleScript_NotAffected;
        }
        else if (option == RUN_SCRIPT && IsBattlerUnaffectedByMove(battlerDef))
        {
            battleScript = BattleScript_ButItFailed;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_LIMBER) : SearchTraits(battlerTraits, ABILITY_LIMBER))
        {
            gLastUsedAbility = abilityDef = ABILITY_LIMBER;
            PushTraitStack(battlerDef, ABILITY_LIMBER);
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        break;
    case MOVE_EFFECT_BURN:
        if (gBattleMons[battlerDef].status1 & STATUS1_BURN)
        {
            battleScript = BattleScript_AlreadyBurned;
        }
        else if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_FIRE))
        {
            battleScript = BattleScript_NotAffected;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_WATER_VEIL) : SearchTraits(battlerTraits, ABILITY_WATER_VEIL))
        {
            gLastUsedAbility = abilityDef = ABILITY_WATER_VEIL;
            PushTraitStack(battlerDef, ABILITY_WATER_VEIL);
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_WATER_BUBBLE) : SearchTraits(battlerTraits, ABILITY_WATER_BUBBLE))
        {
            gLastUsedAbility = abilityDef = ABILITY_WATER_BUBBLE;
            PushTraitStack(battlerDef, ABILITY_WATER_BUBBLE);
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_THERMAL_EXCHANGE) : SearchTraits(battlerTraits, ABILITY_THERMAL_EXCHANGE))
        {
            gLastUsedAbility = abilityDef = ABILITY_THERMAL_EXCHANGE;
            PushTraitStack(battlerDef, ABILITY_THERMAL_EXCHANGE);
            abilityAffected = TRUE;
            battleScript = BattleScript_AbilityProtectsDoesntAffect;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_PERMAFROST) : SearchTraits(battlerTraits, ABILITY_PERMAFROST))
        {
            gLastUsedAbility = abilityDef = ABILITY_PERMAFROST;
            PushTraitStack(battlerDef, ABILITY_PERMAFROST);
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        break;
    case MOVE_EFFECT_SLEEP:
        if (gBattleMons[battlerDef].status1 & STATUS1_SLEEP)
        {
            battleScript = BattleScript_AlreadyAsleep;
        }
        else if (UproarWakeUpCheck(battlerDef))
        {
            battleScript = BattleScript_CantMakeAsleep;
        }
        else if (!gBattleStruct->sleepClauseNotBlocked && CanSleepDueToSleepClause(battlerAtk, battlerDef, option))
        {
            battleScript = BattleScript_SleepClauseBlocked;
        }
        else if (IsElectricTerrainAffected(battlerDef, gFieldStatuses))
        {
            battleScript = BattleScript_ElectricTerrainPrevents;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_INSOMNIA) : SearchTraits(battlerTraits, ABILITY_INSOMNIA))
        {
            gLastUsedAbility = abilityDef = ABILITY_INSOMNIA;
            PushTraitStack(battlerDef, ABILITY_INSOMNIA);
            abilityAffected = TRUE;
            battleScript = BattleScript_PrintAbilityMadeIneffective;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_VITAL_SPIRIT) : SearchTraits(battlerTraits, ABILITY_VITAL_SPIRIT))
        {
            gLastUsedAbility = abilityDef = ABILITY_VITAL_SPIRIT;
            PushTraitStack(battlerDef, ABILITY_VITAL_SPIRIT);
            abilityAffected = TRUE;
            battleScript = BattleScript_PrintAbilityMadeIneffective;
        }
        else if ((sideBattler = IsAbilityOnSide(battlerDef, ABILITY_SWEET_VEIL)))
        {   
            gLastUsedAbility = abilityDef = ABILITY_SWEET_VEIL;
            abilityAffected = TRUE;
            battlerDef = sideBattler - 1;
            PushTraitStack(battlerDef, ABILITY_SWEET_VEIL);
            battleScript = BattleScript_ImmunityProtected;
        }
        break;
    case MOVE_EFFECT_FREEZE:
    case MOVE_EFFECT_FROSTBITE:
        if (gBattleMons[battlerDef].status1 & STATUS1_ICY_ANY)
        {
            battleScript = BattleScript_AlreadyBurned;
        }
        else if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_ICE) || IsBattlerWeatherAffected(battlerDef, B_WEATHER_SUN))
        {
            battleScript = BattleScript_NotAffected;
        }
        else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_MAGMA_ARMOR) : SearchTraits(battlerTraits, ABILITY_MAGMA_ARMOR))
        {
            gLastUsedAbility = abilityDef = ABILITY_MAGMA_ARMOR;
            PushTraitStack(battlerDef, ABILITY_MAGMA_ARMOR);
            abilityAffected = TRUE;
            battleScript = BattleScript_NotAffected;
        }
        break;
    default:
        break;
    }

    if (IsNonVolatileStatusBlocked(battlerDef, abilityDef, abilityAffected, battleScript, option))
        return FALSE;

    // Checks that apply to all non volatile statuses
    if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_HAUNTED) : SearchTraits(battlerTraits, ABILITY_HAUNTED))
    {
        gLastUsedAbility = abilityDef = ABILITY_HAUNTED;
        PushTraitStack(battlerDef, ABILITY_HAUNTED);
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_COMATOSE) : SearchTraits(battlerTraits, ABILITY_COMATOSE))
    {
        gLastUsedAbility = abilityDef = ABILITY_COMATOSE;
        PushTraitStack(battlerDef, ABILITY_COMATOSE);
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if (gAiLogicData->aiCalcInProgress ? SearchTraits(AIBattlerTraits, ABILITY_PURIFYING_SALT) : SearchTraits(battlerTraits, ABILITY_PURIFYING_SALT))
    {
        gLastUsedAbility = abilityDef = ABILITY_PURIFYING_SALT;
        PushTraitStack(battlerDef, ABILITY_PURIFYING_SALT);
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if (IsMistyTerrainAffected(battlerDef, gFieldStatuses))
    {
        battleScript = BattleScript_MistyTerrainPrevents;
    }
    else if (IsLeafGuardProtected(battlerDef))
    {
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if (IsShieldsDownProtected(battlerDef))
    {
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if ((sideBattler = IsFlowerVeilProtected(battlerDef)))
    {
        abilityAffected = TRUE;
        battlerDef = sideBattler - 1;
        abilityDef = ABILITY_FLOWER_VEIL;
        battleScript = BattleScript_FlowerVeilProtects;
    }
    else if (IsSafeguardProtected(battlerAtk, battlerDef))
    {
        battleScript = BattleScript_SafeguardProtected;
    }
    else if (gBattleMons[battlerDef].status1 & STATUS1_ANY)
    {
        battleScript = BattleScript_ButItFailed;
    }

    if (IsNonVolatileStatusBlocked(battlerDef, abilityDef, abilityAffected, battleScript, option))
        return FALSE;

    return TRUE;
}

static bool32 IsNonVolatileStatusBlocked(enum BattlerId battlerDef, enum Ability abilityDef, bool32 abilityAffected, const u8 *battleScript, enum ResultOption option)
{
    if (battleScript != NULL)
    {
        if (option == RUN_SCRIPT)
        {
            if (battleScript != BattleScript_NotAffected)
                gBattleStruct->moveResultFlags[battlerDef] |= MOVE_RESULT_FAILED;

            if (abilityAffected)
            {
                gLastUsedAbility = abilityDef;
                gBattleScripting.battler = gBattlerAbility = battlerDef;
                RecordAbilityBattle(battlerDef, abilityDef);
            }

            gBattlescriptCurrInstr = battleScript;
        }

        return TRUE;
    }

    return FALSE;
}

static bool32 CanSleepDueToSleepClause(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum ResultOption option)
{
    // Can freely sleep own partner
    if (IsDoubleBattle() && IsSleepClauseEnabled() && IsBattlerAlly(battlerAtk, battlerDef))
    {
        if (option == RUN_SCRIPT)
            gBattleStruct->battlerState[battlerDef].sleepClauseEffectExempt = TRUE;
        return FALSE;
    }

    if (option == RUN_SCRIPT)
        gBattleStruct->battlerState[battlerDef].sleepClauseEffectExempt = FALSE;
    // Can't sleep if clause is active otherwise
    if (IsSleepClauseActiveForSide(GetBattlerSide(battlerDef)))
        return TRUE;

    return FALSE;
}

bool32 CanBeConfused(enum BattlerId battler)
{
    // Uses an extra check for the received ability in case the AI is trying to give a status to itself and thus should know the ability already
    if (gBattleMons[battler].volatiles.confusionTurns > 0
     || IsMistyTerrainAffected(battler, gFieldStatuses)
     || (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battler, ABILITY_OWN_TEMPO) : IsAbilityAndRecord(battler, ABILITY_OWN_TEMPO)))
        return FALSE;
    return TRUE;
}

// second argument is 1/X of current hp compared to max hp
bool32 HasEnoughHpToEatBerry(enum BattlerId battler, u32 hpFraction, enum Item itemId)
{
    if (!IsBattlerAlive(battler))
        return FALSE;
    if (gBattleScripting.overrideBerryRequirements)
        return TRUE;
    if (gBattleMons[battler].hp <= gBattleMons[battler].maxHP / hpFraction)
        return TRUE;

    if (hpFraction <= 4 && BattlerHasBerry(battler)
         && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2
         && IsAbilityAndRecord(battler, ABILITY_GLUTTONY))
    {
        return TRUE;
    }

    return FALSE;
}

void ClearVariousBattlerFlags(enum BattlerId battler)
{
    gBattleMons[battler].volatiles.furyCutterCounter = 0;
    gBattleMons[battler].volatiles.destinyBond = 0;
    gBattleMons[battler].volatiles.glaiveRush = FALSE;
    gBattleMons[battler].volatiles.grudge = FALSE;
}

void HandleAction_RunBattleScript(void) // identical to RunBattleScriptCommands
{
    if (CanRunBattleScriptCommands())
        gBattleScriptingCommandsTable[*gBattlescriptCurrInstr]();
}

u32 SetRandomTarget(enum BattlerId battlerAtk)
{
    enum BattlerId target;
    static const u8 targets[NUM_BATTLE_SIDES][MAX_BATTLERS_COUNT / 2] =
    {
        [B_SIDE_PLAYER] = {B_POSITION_OPPONENT_LEFT, B_POSITION_OPPONENT_RIGHT},
        [B_SIDE_OPPONENT] = {B_POSITION_PLAYER_LEFT, B_POSITION_PLAYER_RIGHT},
    };

    if (IsDoubleBattle())
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battlerAtk)][RandomUniform(RNG_RANDOM_TARGET, 0, 1)]);
        if (!IsBattlerAlive(target))
            target ^= BIT_FLANK;
    }
    else
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battlerAtk)][0]);
    }

    return target;
}

u32 GetBattleMoveTarget(enum Move move, enum MoveTarget moveTarget)
{
    u32 targetBattler = 0;
    enum BattleSide side;

    if (moveTarget == TARGET_NONE)
        moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, move);

    switch (moveTarget)
    {
    case TARGET_SELECTED:
    case TARGET_SMART:
    case TARGET_OPPONENT:
    case TARGET_RANDOM:
        side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
        if (IsAffectedByFollowMe(gBattlerAttacker, side, move))
            targetBattler = gSideTimers[side].followmeTarget;
        else
            targetBattler = SetRandomTarget(gBattlerAttacker);
        break;
    case TARGET_DEPENDS:
    case TARGET_BOTH:
    case TARGET_FOES_AND_ALLY:
        targetBattler = GetOpposingSideBattler(gBattlerAttacker);
        if (IsDoubleBattle() && !IsBattlerAlive(targetBattler))
            targetBattler ^= BIT_FLANK;
        break;
    case TARGET_OPPONENTS_FIELD:
        targetBattler = GetOpposingSideBattler(gBattlerAttacker);
        break;
    case TARGET_USER:
    default:
        targetBattler = gBattlerAttacker;
        break;
    case TARGET_ALLY:
        if (IsBattlerAlive(BATTLE_PARTNER(gBattlerAttacker)))
            targetBattler = BATTLE_PARTNER(gBattlerAttacker);
        else
            targetBattler = gBattlerAttacker;
        break;
    }

    gBattleStruct->moveTarget[gBattlerAttacker] = targetBattler;

    return targetBattler;
}

enum Obedience GetAttackerObedienceForAction(void)
{
    s32 rnd;
    s32 calc;
    u8 obedienceLevel = 0;
    u8 levelReferenced;

    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
        return OBEYS;
    if (BattlerHasAi(gBattlerAttacker))
        return OBEYS;

    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && GetBattlerPosition(gBattlerAttacker) == B_POSITION_PLAYER_RIGHT)
        return OBEYS;
    if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
        return OBEYS;
    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        return OBEYS;
    if (B_OBEDIENCE_MECHANICS < GEN_8 && !IsOtherTrainer(gBattleMons[gBattlerAttacker].otId, gBattleMons[gBattlerAttacker].otName))
        return OBEYS;
    if (FlagGet(FLAG_BADGE08_GET)) // Rain Badge, ignore obedience altogether
        return OBEYS;

    obedienceLevel = 100;

    if (B_OBEDIENCE_MECHANICS >= GEN_8
     && !IsOtherTrainer(gBattleMons[gBattlerAttacker].otId, gBattleMons[gBattlerAttacker].otName))
        levelReferenced = gBattleMons[gBattlerAttacker].metLevel;
    else
        levelReferenced = gBattleMons[gBattlerAttacker].level;

    if (levelReferenced <= obedienceLevel)
        return OBEYS;

    rnd = Random();
    calc = (levelReferenced + obedienceLevel) * (rnd & 255) >> 8;
    if (calc < obedienceLevel)
        return OBEYS;

    //  Clear the Z-Move flags if the battler is disobedient as to not waste the Z-Move
    if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_Z_MOVE)
    {
        gBattleStruct->gimmick.activated[gBattlerAttacker][GIMMICK_Z_MOVE] = FALSE;
        gBattleStruct->gimmick.activeGimmick[GetBattlerSide(gBattlerAttacker)][gBattlerPartyIndexes[gBattlerAttacker]] = GIMMICK_NONE;
    }

    // is not obedient
    enum BattleMoveEffects moveEffect = GetMoveEffect(gCurrentMove);
    if (MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_RAGE))
        gBattleMons[gBattlerAttacker].volatiles.rage = FALSE;
    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP && IsUsableWhileAsleepEffect(moveEffect))
        return DISOBEYS_WHILE_ASLEEP;

    calc = (levelReferenced + obedienceLevel) * ((rnd >> 8) & 255) >> 8;
    if (calc < obedienceLevel)
    {
        calc = CheckMoveLimitations(gBattlerAttacker, 1u << gCurrMovePos, MOVE_LIMITATIONS_ALL);
        if (calc == ALL_MOVES_MASK) // all moves cannot be used
            return DISOBEYS_LOAFS;
        else // use a random move
            do
                gCurrMovePos = gChosenMovePos = MOD(Random(), MAX_MON_MOVES);
            while ((1u << gCurrMovePos) & calc);
        return DISOBEYS_RANDOM_MOVE;
    }
    else
    {
        obedienceLevel = levelReferenced - obedienceLevel;

        calc = ((rnd >> 16) & 255);
        if (calc < obedienceLevel && CanBeSlept(gBattlerAttacker, gBattlerAttacker, NOT_BLOCKED_BY_SLEEP_CLAUSE))
        {
            // try putting asleep
            enum BattlerId i;
            for (i = 0; i < gBattlersCount; i++)
                if (gBattleMons[i].volatiles.uproarTurns)
                    break;
            if (i == gBattlersCount)
                return DISOBEYS_FALL_ASLEEP;
        }
        calc -= obedienceLevel;
        if (calc < obedienceLevel)
            return DISOBEYS_HITS_SELF;
        else
            return DISOBEYS_LOAFS;
    }
}

enum HoldEffect GetBattlerItemHoldEffect(enum BattlerId battler, enum Item item)
{
    if (item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffectParam;
    else if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
    {
        for (u32 i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (gAiLogicData->items[battler][i] == item)
                return gAiLogicData->holdEffects[battler][i];
        }
    }
    else
        return GetItemHoldEffect(item);

    return GetItemHoldEffect(item);
}

u32 GetBattlerItemHoldEffectParam(enum BattlerId battler, enum Item item)
{
    if (item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffectParam;
    else if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
    {
        for (u32 i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (gAiLogicData->items[battler][i] == item)
                return gAiLogicData->holdEffectParams[battler][i];
        }
    }
    else
        return GetItemHoldEffectParam(item);

    return GetItemHoldEffectParam(item);
}

bool32 BattlerHasBerry(enum BattlerId battler)
{
    for(u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (GetItemPocket(gBattleMons[battler].items[i]) == POCKET_BERRIES)
            return TRUE;
    }
    return FALSE;
}

bool32 GetBattlerBerrySlot(enum BattlerId battler)
{
    u32 i;
    u32 targetableSlots[MAX_MON_ITEMS];
    u32 index = 0;
    targetableSlots[0] = MAX_MON_ITEMS; // Invalid value for first slot if no valid slots found

    for (i = 0; i < MAX_MON_ITEMS; i++) //Gather all berry item slots
    {
        if (GetItemPocket(gBattleMons[battler].items[i]) == POCKET_BERRIES)
        {
            if (targetableSlots[0] != MAX_MON_ITEMS)
                index++;
            targetableSlots[index] = i;
        }
    }

    gLastItemSlot = GetSlot(targetableSlots, index);

    return gLastItemSlot;
}

bool32 CanBattlerAvoidContactEffects(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    if (BattlerHasHeldItemEffect(gBattlerAttacker, HOLD_EFFECT_PROTECTIVE_PADS, TRUE))
    {
        RecordItemEffectBattle(battlerAtk, HOLD_EFFECT_PROTECTIVE_PADS);
        return TRUE;
    }

    return !IsMoveMakingContact(battlerAtk, battlerDef, move);
}

bool32 IsMoveMakingContact(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    if (!(MoveMakesContact(move) || (GetMoveEffect(move) == EFFECT_SHELL_SIDE_ARM
                                  && gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] == DAMAGE_CATEGORY_PHYSICAL)))
    {
        return FALSE;
    }
    else if ((BattlerHasHeldItemEffect(battlerAtk, HOLD_EFFECT_PUNCHING_GLOVE, TRUE) && IsPunchingMove(move)))
    {
        RecordItemEffectBattle(battlerAtk, HOLD_EFFECT_PUNCHING_GLOVE);
        return FALSE;
    }
    else if (BattlerHasTrait(battlerAtk, ABILITY_LONG_REACH))
    {
        RecordAbilityBattle(battlerAtk, ABILITY_LONG_REACH);
        return FALSE;
    }
        return TRUE;
}

static inline bool32 IsSideProtected(enum BattlerId battler, enum ProtectMethod method)
{
    return gProtectStructs[battler].protected == method
        || gProtectStructs[BATTLE_PARTNER(battler)].protected == method;
}

static bool32 IsCraftyShieldProtected(u32 battlerAtk, u32 battlerDef, u32 move)
{
    if (!IsBattleMoveStatus(move))
        return FALSE;

    if (!IsSideProtected(battlerDef, PROTECT_CRAFTY_SHIELD))
        return FALSE;

    if (GetMoveEffect(move) == EFFECT_HOLD_HANDS)
        return TRUE;

    u32 moveTarget = GetBattlerMoveTargetType(battlerAtk, move);
    if (!IsBattlerAlly(battlerAtk, battlerDef)
     && moveTarget != TARGET_OPPONENTS_FIELD
     && moveTarget != TARGET_ALL_BATTLERS)
        return TRUE;

    return FALSE;
}

bool32 IsBattlerProtected(struct BattleContext *ctx)
{
    if (gProtectStructs[ctx->battlerDef].protected == PROTECT_NONE
     && gProtectStructs[BATTLE_PARTNER(ctx->battlerDef)].protected == PROTECT_NONE)
        return FALSE;

    if (GetMoveEffect(ctx->move) == EFFECT_CURSE && !IS_BATTLER_OF_TYPE(ctx->battlerAtk, TYPE_GHOST))
        return FALSE;

    if (gProtectStructs[ctx->battlerDef].protected != PROTECT_MAX_GUARD && !MoveIgnoresProtect(ctx->move))
    {
        if (IsZMove(ctx->move) || IsMaxMove(ctx->move))
            return FALSE; // Z-Moves and Max Moves bypass protection (except Max Guard).
        if (BattlerHasTrait(ctx->battlerAtk, ABILITY_TIDAL_DEITY) && IsBattlerAtMaxHp(ctx->battlerAtk))
            return FALSE;
        if (BattlerHasTrait(ctx->battlerAtk, ABILITY_UNSEEN_FIST)
         && IsMoveMakingContact(ctx->battlerAtk, ctx->battlerDef, ctx->move))
            return FALSE;
    }

    if (GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move) == TARGET_ALL_BATTLERS)
        return FALSE;

    bool32 isProtected = FALSE;

    if (IsCraftyShieldProtected(ctx->battlerAtk, ctx->battlerDef, ctx->move))
        isProtected = TRUE;
    else if (MoveIgnoresProtect(ctx->move))
        isProtected = FALSE;
    else if (IsSideProtected(ctx->battlerDef, PROTECT_WIDE_GUARD) && IsSpreadMove(GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move)))
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_NORMAL)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_SPIKY_SHIELD)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_MAX_GUARD)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_BANEFUL_BUNKER)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_BURNING_BULWARK)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_OBSTRUCT && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_SILK_TRAP && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_KINGS_SHIELD && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else if (IsSideProtected(ctx->battlerDef, PROTECT_QUICK_GUARD) && GetChosenMovePriority(ctx->battlerAtk) > 0)
        isProtected = TRUE;
    else if (IsSideProtected(ctx->battlerDef, PROTECT_MAT_BLOCK) && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else
        isProtected = FALSE;

    if (isProtected
     && gProtectStructs[ctx->battlerDef].protected != PROTECT_MAX_GUARD
     && BattlerHasTrait(ctx->battlerAtk, ABILITY_NULL_SPACE)
     && IsCustomAbilityDirectDamagingMove(ctx->move))
    {
        RecordAbilityBattle(ctx->battlerAtk, ABILITY_NULL_SPACE);
        gBattleStruct->nullSpaceProtectedHit[ctx->battlerDef] = TRUE;
        return FALSE;
    }

    return isProtected;
}

enum ProtectType GetProtectType(enum ProtectMethod method)
{
    switch (method)
    {
    case PROTECT_NONE:
        return PROTECT_TYPE_NONE;
    case PROTECT_NORMAL:
    case PROTECT_SPIKY_SHIELD:
    case PROTECT_KINGS_SHIELD:
    case PROTECT_BANEFUL_BUNKER:
    case PROTECT_BURNING_BULWARK:
    case PROTECT_OBSTRUCT:
    case PROTECT_SILK_TRAP:
    case PROTECT_MAX_GUARD:
        return PROTECT_TYPE_SINGLE;
    case PROTECT_WIDE_GUARD:
    case PROTECT_QUICK_GUARD:
    case PROTECT_CRAFTY_SHIELD:
    case PROTECT_MAT_BLOCK:
        return PROTECT_TYPE_SIDE;
    }

    return FALSE;
}

enum InverseBattleCheck
{
    INVERSE_BATTLE,
    NOT_INVERSE_BATTLE
};

enum IronBallCheck
{
    CHECK_IRON_BALL,
    IGNORE_IRON_BALL
};

static bool32 IsBattlerGroundedInverseCheck(enum BattlerId battler, enum InverseBattleCheck checkInverse, bool32 isAnticipation, bool32 hasLevitate, bool32 ignoresGravity, bool32 skipIronBall)
{
    if (skipIronBall == FALSE && BattlerHasHeldItemEffect(battler, HOLD_EFFECT_IRON_BALL, TRUE))
        return TRUE;
    if (gFieldStatuses & STATUS_FIELD_GRAVITY && isAnticipation == FALSE && !ignoresGravity)
        return TRUE;
    if (B_ROOTED_GROUNDING >= GEN_4 && gBattleMons[battler].volatiles.root)
        return TRUE;
    if (gBattleMons[battler].volatiles.smackDown)
        return TRUE;
    if (gBattleMons[battler].volatiles.telekinesis)
        return FALSE;
    if (gBattleMons[battler].volatiles.magnetRise)
        return FALSE;
    if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_AIR_BALLOON, TRUE))
        return FALSE;
    if (hasLevitate)
        return FALSE;
    if (IS_BATTLER_OF_TYPE(battler, TYPE_FLYING) && (checkInverse != INVERSE_BATTLE || !FlagGet(B_FLAG_INVERSE_BATTLE)))
        return FALSE;
    return TRUE;
}

bool32 IsBattlerGrounded(enum BattlerId battler)
{
    bool32 hasLevitate;
    bool32 ignoresGravity;

    // Regular ability check split out here as the AI switching logic uses battle context to figure out the Ability instead. (Multi)
    hasLevitate = gAiLogicData->aiCalcInProgress
                ? (AI_BATTLER_HAS_TRAIT(battler, ABILITY_LEVITATE) || AI_BATTLER_HAS_TRAIT(battler, ABILITY_EELEVATE) || AI_BATTLER_HAS_TRAIT(battler, ABILITY_ALLSEEING_IDOL))
                : (BattlerHasTrait(battler, ABILITY_LEVITATE) || BattlerHasTrait(battler, ABILITY_EELEVATE) || BattlerHasTrait(battler, ABILITY_ALLSEEING_IDOL));
    ignoresGravity = gAiLogicData->aiCalcInProgress
                   ? AI_BATTLER_HAS_TRAIT(battler, ABILITY_ALLSEEING_IDOL)
                   : BattlerHasTrait(battler, ABILITY_ALLSEEING_IDOL);

    return IsBattlerGroundedInverseCheck(battler, NOT_INVERSE_BATTLE, FALSE, hasLevitate, ignoresGravity, FALSE);
}

u32 GetMoveSlot(u16 *moves, enum Move move)
{
    u32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] == move)
            break;
    }
    return i;
}

u32 GetBattlerWeight(enum BattlerId battler)
{
    u32 i;
    u32 weight = GetSpeciesWeight(gBattleMons[battler].species);

    if (BattlerHasTrait(battler, ABILITY_HEAVY_METAL))
        weight *= 2;
    if (BattlerHasTrait(battler, ABILITY_LIGHT_METAL))
        weight /= 2;

    if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_FLOAT_STONE, TRUE))
        weight /= 2;

    for (i = 0; i < gBattleMons[battler].volatiles.autotomizeCount; i++)
    {
        if (weight > 1000)
        {
            weight -= 1000;
        }
        else if (weight <= 1000)
        {
            weight = 1;
            break;
        }
    }

    if (weight == 0)
        weight = 1;

    return weight;
}

u32 CountBattlerStatIncreases(enum BattlerId battler, bool32 countEvasionAcc)
{
    enum Stat i;
    u32 count = 0;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if ((i == STAT_ACC || i == STAT_EVASION) && !countEvasionAcc)
            continue;
        if (gBattleMons[battler].statStages[i] > DEFAULT_STAT_STAGE) // Stat is increased.
            count += gBattleMons[battler].statStages[i] - DEFAULT_STAT_STAGE;
    }

    return count;
}

bool32 BattlerHasCopyableChanges(enum BattlerId battler)
{
    u32 i;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battler].statStages[i] != DEFAULT_STAT_STAGE)
            return TRUE;
    }

    if (gBattleMons[battler].volatiles.focusEnergy
     || gBattleMons[battler].volatiles.dragonCheer
     || gBattleMons[battler].volatiles.bonusCritStages != 0)
        return TRUE;

    return FALSE;
}

u32 GetMoveTargetCount(struct BattleContext *ctx)
{
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;

    switch (GetBattlerMoveTargetType(battlerAtk, move))
    {
    case TARGET_BOTH:
        return !(gAbsentBattlerFlags & (1u << battlerDef))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerDef)));
    case TARGET_FOES_AND_ALLY:
        return !(gAbsentBattlerFlags & (1u << battlerDef))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerDef)))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerAtk)));
    case TARGET_OPPONENTS_FIELD:
        return 1;
    case TARGET_DEPENDS:
    case TARGET_SELECTED:
    case TARGET_RANDOM:
    case TARGET_OPPONENT:
        return IsBattlerAlive(battlerDef);
    case TARGET_USER:
        return IsBattlerAlive(battlerAtk);
    default:
        return 0;
    }
}

static const u8 sFlailHpScaleToPowerTable[] =
{
    1, 200,
    4, 150,
    9, 100,
    16, 80,
    32, 40,
    48, 20
};

// format: min. weight (hectograms), base power
static const u16 sWeightToDamageTable[] =
{
    100, 20,
    250, 40,
    500, 60,
    1000, 80,
    2000, 100,
    0xFFFF, 0xFFFF
};

static const u8 sSpeedDiffPowerTable[] = {40, 60, 80, 120, 150};
static const u8 sHeatCrashPowerTable[] = {40, 40, 60, 80, 100, 120};
static const u8 sTrumpCardPowerTable[] = {200, 80, 60, 50, 40};

const struct TypePower gNaturalGiftTable[] =
{
    [ITEM_TO_BERRY(ITEM_CHERI_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_CHESTO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_PECHA_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RAWST_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_ASPEAR_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_LEPPA_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_ORAN_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_PERSIM_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_LUM_BERRY)] = {TYPE_FLYING, 80},
    [ITEM_TO_BERRY(ITEM_SITRUS_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_FIGY_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_WIKI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_MAGO_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_AGUAV_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_IAPAPA_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_RAZZ_BERRY)] = {TYPE_STEEL, 80},
    [ITEM_TO_BERRY(ITEM_OCCA_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_PASSHO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_WACAN_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RINDO_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_YACHE_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_CHOPLE_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_KEBIA_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_SHUCA_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_COBA_BERRY)] = {TYPE_FLYING, 80},
    [ITEM_TO_BERRY(ITEM_PAYAPA_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_TANGA_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_CHARTI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_KASIB_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_HABAN_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_COLBUR_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_BABIRI_BERRY)] = {TYPE_STEEL, 80},
    [ITEM_TO_BERRY(ITEM_CHILAN_BERRY)] = {TYPE_NORMAL, 80},
    [ITEM_TO_BERRY(ITEM_ROSELI_BERRY)] = {TYPE_FAIRY, 80},
    [ITEM_TO_BERRY(ITEM_BLUK_BERRY)] = {TYPE_FIRE, 90},
    [ITEM_TO_BERRY(ITEM_NANAB_BERRY)] = {TYPE_WATER, 90},
    [ITEM_TO_BERRY(ITEM_WEPEAR_BERRY)] = {TYPE_ELECTRIC, 90},
    [ITEM_TO_BERRY(ITEM_PINAP_BERRY)] = {TYPE_GRASS, 90},
    [ITEM_TO_BERRY(ITEM_POMEG_BERRY)] = {TYPE_ICE, 90},
    [ITEM_TO_BERRY(ITEM_KELPSY_BERRY)] = {TYPE_FIGHTING, 90},
    [ITEM_TO_BERRY(ITEM_QUALOT_BERRY)] = {TYPE_POISON, 90},
    [ITEM_TO_BERRY(ITEM_HONDEW_BERRY)] = {TYPE_GROUND, 90},
    [ITEM_TO_BERRY(ITEM_GREPA_BERRY)] = {TYPE_FLYING, 90},
    [ITEM_TO_BERRY(ITEM_TAMATO_BERRY)] = {TYPE_PSYCHIC, 90},
    [ITEM_TO_BERRY(ITEM_CORNN_BERRY)] = {TYPE_BUG, 90},
    [ITEM_TO_BERRY(ITEM_MAGOST_BERRY)] = {TYPE_ROCK, 90},
    [ITEM_TO_BERRY(ITEM_RABUTA_BERRY)] = {TYPE_GHOST, 90},
    [ITEM_TO_BERRY(ITEM_NOMEL_BERRY)] = {TYPE_DRAGON, 90},
    [ITEM_TO_BERRY(ITEM_SPELON_BERRY)] = {TYPE_DARK, 90},
    [ITEM_TO_BERRY(ITEM_PAMTRE_BERRY)] = {TYPE_STEEL, 90},
    [ITEM_TO_BERRY(ITEM_WATMEL_BERRY)] = {TYPE_FIRE, 100},
    [ITEM_TO_BERRY(ITEM_DURIN_BERRY)] = {TYPE_WATER, 100},
    [ITEM_TO_BERRY(ITEM_BELUE_BERRY)] = {TYPE_ELECTRIC, 100},
    [ITEM_TO_BERRY(ITEM_LIECHI_BERRY)] = {TYPE_GRASS, 100},
    [ITEM_TO_BERRY(ITEM_GANLON_BERRY)] = {TYPE_ICE, 100},
    [ITEM_TO_BERRY(ITEM_SALAC_BERRY)] = {TYPE_FIGHTING, 100},
    [ITEM_TO_BERRY(ITEM_PETAYA_BERRY)] = {TYPE_POISON, 100},
    [ITEM_TO_BERRY(ITEM_APICOT_BERRY)] = {TYPE_GROUND, 100},
    [ITEM_TO_BERRY(ITEM_LANSAT_BERRY)] = {TYPE_FLYING, 100},
    [ITEM_TO_BERRY(ITEM_STARF_BERRY)] = {TYPE_PSYCHIC, 100},
    [ITEM_TO_BERRY(ITEM_ENIGMA_BERRY)] = {TYPE_BUG, 100},
    [ITEM_TO_BERRY(ITEM_MICLE_BERRY)] = {TYPE_ROCK, 100},
    [ITEM_TO_BERRY(ITEM_CUSTAP_BERRY)] = {TYPE_GHOST, 100},
    [ITEM_TO_BERRY(ITEM_JABOCA_BERRY)] = {TYPE_DRAGON, 100},
    [ITEM_TO_BERRY(ITEM_ROWAP_BERRY)] = {TYPE_DARK, 100},
    [ITEM_TO_BERRY(ITEM_KEE_BERRY)] = {TYPE_FAIRY, 100},
    [ITEM_TO_BERRY(ITEM_MARANGA_BERRY)] = {TYPE_DARK, 100},
};

static inline u32 CalcRolloutBasePower(enum BattlerId battlerAtk, u32 basePower)
{
    u32 i;
    for (i = 0; i < gBattleMons[battlerAtk].volatiles.rolloutTimer; i++)
        basePower *= 2;
    if (gBattleMons[battlerAtk].volatiles.defenseCurl)
        basePower *= 2;
    return basePower;
}

static inline u32 CalcFuryCutterBasePower(enum BattlerId battlerAtk, u32 basePower)
{
    for (u32 i = 0; i < gBattleMons[battlerAtk].volatiles.furyCutterCounter; i++)
        basePower *= 2;
    return min(basePower, 160); // The duration to reach 160 depends on a gen
}

static inline u32 CalcTerrainBoostedPower(struct BattleContext *ctx, u32 basePower)
{
    bool32 isTerrainAffected = FALSE;

    if (GetMoveTerrainBoost_GroundCheck(ctx->move) == GROUND_CHECK_USER)
        isTerrainAffected = IsBattlerTerrainAffected(ctx->battlerAtk, ctx->fieldStatuses, GetMoveTerrainBoost_Terrain(ctx->move));
    else if (GetMoveTerrainBoost_GroundCheck(ctx->move) == GROUND_CHECK_TARGET)
        isTerrainAffected = IsBattlerTerrainAffected(ctx->battlerDef, ctx->fieldStatuses, GetMoveTerrainBoost_Terrain(ctx->move));
    else if (ctx->fieldStatuses & GetMoveTerrainBoost_Terrain(ctx->move)) // no ground check (Psyblade)
        isTerrainAffected = TRUE;

    if (isTerrainAffected)
        basePower = uq4_12_multiply(basePower, PercentToUQ4_12AddOne(GetMoveTerrainBoost_Percent(ctx->move)));

    return basePower;
}

static inline u32 IsFieldMudSportAffected(enum Type moveType)
{
    if (moveType != TYPE_ELECTRIC)
        return FALSE;

    if (gFieldStatuses & STATUS_FIELD_MUDSPORT)
        return TRUE;

    if (B_SPORT_TURNS < GEN_6)
    {
        for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
        {
            if (gBattleMons[battler].volatiles.mudSport)
                return TRUE;
        }
    }

    return FALSE;
}

static inline u32 IsFieldWaterSportAffected(enum Type moveType)
{
    if (moveType != TYPE_FIRE)
        return FALSE;

    if (gFieldStatuses & STATUS_FIELD_WATERSPORT)
        return TRUE;

    if (B_SPORT_TURNS < GEN_6)
    {
        for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
        {
            if (gBattleMons[battler].volatiles.waterSport)
                return TRUE;
        }
    }

    return FALSE;
}

static inline u32 CalcMoveBasePower(struct BattleContext *ctx)
{
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;

    u32 i;
    u32 basePower = GetMovePower(move);
    u32 moveEffect = GetMoveEffect(move);
    u32 weight, hpFraction, speed;

    if (GetActiveGimmick(battlerAtk) == GIMMICK_Z_MOVE)
        return GetZMovePower(gCurrentMove);

    if (GetActiveGimmick(battlerAtk) == GIMMICK_DYNAMAX)
        return GetMaxMovePower(move);

    switch (moveEffect)
    {
    case EFFECT_PLEDGE:
        if (gBattleStruct->pledgeMove)
            basePower = 150;
        break;
    case EFFECT_FLING:
            basePower = GetFlingPowerFromItemId(gLastUsedItem);
        break;
    case EFFECT_POWER_BASED_ON_USER_HP:
        basePower = gBattleMons[battlerAtk].hp * basePower / gBattleMons[battlerAtk].maxHP;
        break;
    case EFFECT_FLAIL:
        hpFraction = GetScaledHPFraction(gBattleMons[battlerAtk].hp, gBattleMons[battlerAtk].maxHP, 48);
        for (i = 0; i < sizeof(sFlailHpScaleToPowerTable); i += 2)
        {
            if (hpFraction <= sFlailHpScaleToPowerTable[i])
                break;
        }
        basePower = sFlailHpScaleToPowerTable[i + 1];
        break;
    case EFFECT_RETURN:
        basePower = 10 * (gBattleMons[battlerAtk].friendship) / 25;
        break;
    case EFFECT_FRUSTRATION:
        basePower = 10 * (MAX_FRIENDSHIP - gBattleMons[battlerAtk].friendship) / 25;
        break;
    case EFFECT_FURY_CUTTER:
        basePower = CalcFuryCutterBasePower(battlerAtk, basePower);
        break;
    case EFFECT_ROLLOUT:
        basePower = CalcRolloutBasePower(battlerAtk, basePower);
        break;
    case EFFECT_MAGNITUDE:
        basePower = gBattleStruct->magnitudeBasePower;
        break;
    case EFFECT_PRESENT:
        basePower = gBattleStruct->presentBasePower;
        break;
    case EFFECT_TRIPLE_KICK:
        basePower *= 1 + GetMoveStrikeCount(move) - gMultiHitCounter;
        break;
    case EFFECT_SPIT_UP:
        basePower = 100 * gBattleMons[battlerAtk].volatiles.stockpileCounter;
        break;
    case EFFECT_REVENGE:
        if (gProtectStructs[battlerAtk].revengeDoubled & 1u << battlerDef)
            basePower *= 2;
        break;
    case EFFECT_WEATHER_BALL:
        if (GetBattlerWeather(battlerAtk, ctx->weather) & B_WEATHER_ANY)
            basePower *= 2;
        break;
    case EFFECT_PURSUIT:
        if (gBattleStruct->battlerState[battlerDef].pursuitTarget)
            basePower *= 2;
        break;
    case EFFECT_NATURAL_GIFT:
        for (i = 0; i < MAX_MON_ITEMS; i++) //Uses the first berry found for dependability
        {   
            if (GetItemPocket(gBattleMons[battlerAtk].items[i]) == POCKET_BERRIES)
            {
                basePower = gNaturalGiftTable[ITEM_TO_BERRY(gBattleMons[battlerAtk].items[i])].power;
                break;
            }
        } 
        break;
    case EFFECT_DOUBLE_POWER_ON_ARG_STATUS:
        if (move == MOVE_HEX && BattlerHasTrait(battlerAtk, ABILITY_RITUAL))
            basePower = 75;
        // Comatose targets treated as if asleep
        if (((gBattleMons[battlerDef].status1 | (STATUS1_SLEEP * (BattlerHasTrait(battlerDef, ABILITY_COMATOSE)))) & GetMoveEffectArg_Status(move)
          || BattlerHasTrait(battlerDef, ABILITY_HAUNTED))
         && !((GetMoveAdditionalEffectById(move, 0)->moveEffect == MOVE_EFFECT_REMOVE_STATUS) && DoesSubstituteBlockMove(battlerAtk, battlerDef, move)))
            basePower *= 2;
        break;
    case EFFECT_POWER_BASED_ON_TARGET_HP:
        basePower = gBattleMons[battlerDef].hp * basePower / gBattleMons[battlerDef].maxHP;
        break;
    case EFFECT_ASSURANCE:
        if (gProtectStructs[battlerDef].assuranceDoubled)
            basePower *= 2;
        break;
    case EFFECT_TRUMP_CARD:
        i = GetMoveSlot(gBattleMons[battlerAtk].moves, ctx->chosenMove);
        if (i != MAX_MON_MOVES)
        {
            if (gBattleMons[battlerAtk].pp[i] >= ARRAY_COUNT(sTrumpCardPowerTable))
                basePower = sTrumpCardPowerTable[ARRAY_COUNT(sTrumpCardPowerTable) - 1];
            else
                basePower = sTrumpCardPowerTable[gBattleMons[battlerAtk].pp[i]];
        }
        break;
    case EFFECT_ACROBATICS:
        // For Multi Items, increase power in stages based on number of held items
        u8 occupiedSlots = MAX_MON_ITEMS;

        for (i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (gBattleMons[battlerAtk].items[i] == ITEM_NONE
            // Edge case, because removal of items happens after damage calculation.
            || (gSpecialStatuses[battlerAtk].gemBoost && gItemsInfo[GetSlotHeldItem(battlerAtk, i, FALSE)].holdEffect == HOLD_EFFECT_GEMS))
                occupiedSlots--;
        }

        if (occupiedSlots == 0)
            basePower *= 2; // Normal boosted damage with no items at all
        else if (occupiedSlots == 1 && MAX_MON_ITEMS > 1) // Only apply additional math if there are more than one item slot
           basePower = uq4_12_multiply(basePower, UQ_4_12(1.33)); // If pokemon has 1 item, damage boost reduced to 33% since there's a major jump between having no items and having even 1
        else if (MAX_MON_ITEMS > 1) // Further items then evenly reduce the remaining boost down to 1x effectiveness at full load
           basePower = uq4_12_multiply(basePower, uq4_12_subtract(UQ_4_12(1.33),uq4_12_multiply(uq4_12_divide(UQ_4_12(0.33), UQ_4_12(MAX_MON_ITEMS - 1)), UQ_4_12(occupiedSlots - 1)))); 
        break;
    case EFFECT_LOW_KICK:
        weight = GetBattlerWeight(battlerDef);
        for (i = 0; sWeightToDamageTable[i] != 0xFFFF; i += 2)
        {
            if (sWeightToDamageTable[i] > weight)
                break;
        }
        if (sWeightToDamageTable[i] != 0xFFFF)
            basePower = sWeightToDamageTable[i + 1];
        else
            basePower = 120;
        break;
    case EFFECT_HEAT_CRASH:
        weight = GetBattlerWeight(battlerAtk) / GetBattlerWeight(battlerDef);
        if (weight >= ARRAY_COUNT(sHeatCrashPowerTable))
            basePower = sHeatCrashPowerTable[ARRAY_COUNT(sHeatCrashPowerTable) - 1];
        else
            basePower = sHeatCrashPowerTable[weight];
        break;
    case EFFECT_PUNISHMENT:
        basePower = 60 + (CountBattlerStatIncreases(battlerDef, FALSE) * 20);
        if (basePower > 200)
            basePower = 200;
        break;
    case EFFECT_STORED_POWER:
        basePower += (CountBattlerStatIncreases(battlerAtk, TRUE) * 20);
        break;
    case EFFECT_ELECTRO_BALL:
        speed = GetBattlerTotalSpeedStat(battlerAtk) / GetBattlerTotalSpeedStat(battlerDef);
        if (speed >= ARRAY_COUNT(sSpeedDiffPowerTable))
            speed = ARRAY_COUNT(sSpeedDiffPowerTable) - 1;
        basePower = sSpeedDiffPowerTable[speed];
        break;
    case EFFECT_GYRO_BALL:
        {
            u32 attackerSpeed = GetBattlerTotalSpeedStat(battlerAtk);
            if (attackerSpeed == 0)
            {
                basePower = 1;
            }
            else
            {
                basePower = ((25 * GetBattlerTotalSpeedStat(battlerDef)) / attackerSpeed) + 1;
                if (basePower > 150)
                    basePower = 150;
            }
            break;
        }
    case EFFECT_ECHOED_VOICE:
        // gBattleStruct->echoedVoiceCounter incremented in EndTurnVarious called by DoEndTurnEffects
        if (gBattleStruct->echoedVoiceCounter != 0)
        {
            basePower += (basePower * gBattleStruct->echoedVoiceCounter);
            if (basePower > 200)
                basePower = 200;
        }
        break;
    case EFFECT_PAYBACK:
        if (HasBattlerActedThisTurn(battlerDef)
            && (B_PAYBACK_SWITCH_BOOST < GEN_5 || gBattleStruct->battlerState[battlerDef].isFirstTurn != 2))
            basePower *= 2;
        break;
    case EFFECT_BOLT_BEAK:
        if (!HasBattlerActedThisTurn(battlerDef)
            || gBattleStruct->battlerState[battlerDef].isFirstTurn == 2)
            basePower *= 2;
        break;
    case EFFECT_FUSION_COMBO:
        if (move == gLastUsedMove)
            break;
        // fallthrough
    case EFFECT_ROUND:
        // don't double power due to previous turn's Round/Fusion move
        if (gCurrentTurnActionNumber != 0
         && gActionsByTurnOrder[gCurrentTurnActionNumber - 1] == B_ACTION_USE_MOVE
         && GetMoveEffect(gLastUsedMove) == moveEffect)
            basePower *= 2;
        break;
    case EFFECT_LASH_OUT:
        if (gProtectStructs[battlerAtk].lashOutAffected)
            basePower *= 2;
        break;
    case EFFECT_TERRAIN_BOOST:
        basePower = CalcTerrainBoostedPower(ctx, basePower);
        break;
    case EFFECT_DYNAMAX_DOUBLE_DMG:
        if (GetActiveGimmick(battlerDef) == GIMMICK_DYNAMAX)
            basePower *= 2;
        break;
    case EFFECT_HIDDEN_POWER:
    {
        if (B_HIDDEN_POWER_DMG < GEN_6)
        {
            u8 powerBits = ((gBattleMons[battlerAtk].hpIV & 2) >> 1)
                         | ((gBattleMons[battlerAtk].attackIV & 2) << 0)
                         | ((gBattleMons[battlerAtk].defenseIV & 2) << 1)
                         | ((gBattleMons[battlerAtk].speedIV & 2) << 2)
                         | ((gBattleMons[battlerAtk].spAttackIV & 2) << 3)
                         | ((gBattleMons[battlerAtk].spDefenseIV & 2) << 4);

            basePower = (40 * powerBits) / 63 + 30;
        }
        break;
    }
    case EFFECT_GRAV_APPLE:
        if (ctx->fieldStatuses & STATUS_FIELD_GRAVITY)
            basePower = uq4_12_multiply(basePower, UQ_4_12(1.5));
        break;
    case EFFECT_TERRAIN_PULSE:
        if (IsAnyTerrainAffected(battlerAtk, ctx->fieldStatuses))
            basePower *= 2;
        break;
    case EFFECT_BEAT_UP:
        if (GetConfig(B_BEAT_UP) >= GEN_5)
            basePower = CalcBeatUpPower();
        break;
    case EFFECT_MAX_MOVE:
        basePower = GetMaxMovePower(GetBattlerChosenMove(battlerAtk));
        break;
    case EFFECT_RAGE_FIST:
        basePower += 50 * GetBattlerPartyState(battlerAtk)->timesGotHit;
        basePower = (basePower > 350) ? 350 : basePower;
        break;
    case EFFECT_FICKLE_BEAM:
        if (gBattleStruct->fickleBeamBoosted)
            basePower *= 2;
        break;
    case EFFECT_TERA_BLAST:
        if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA && GetBattlerTeraType(battlerAtk) == TYPE_STELLAR)
            basePower = 100;
        break;
    case EFFECT_LAST_RESPECTS:
        basePower += (basePower * min(100, GetBattlerSideFaintCounter(battlerAtk)));
        break;
    case EFFECT_SPECIES_POWER_OVERRIDE:
        if (gBattleMons[battlerAtk].species == GetMoveSpeciesPowerOverride_Species(ctx->move))
            basePower = GetMoveSpeciesPowerOverride_Power(ctx->move);
    default:
        break;
    }

    if (basePower == 0)
        basePower = 1;
    return basePower;
}

static bool32 IsEnigmaPowerMove(enum Move move)
{
    switch (move)
    {
    case MOVE_HIDDEN_POWER:
    case MOVE_ANCIENT_POWER:
    case MOVE_NATURE_POWER:
    case MOVE_SUPERPOWER:
    case MOVE_SECRET_POWER:
    case MOVE_POWER_GEM:
    case MOVE_EARTH_POWER:
    case MOVE_POWER_WHIP:
    case MOVE_STORED_POWER:
    case MOVE_POWER_UP_PUNCH:
    case MOVE_HIGH_HORSEPOWER:
    case MOVE_POWER_TRIP:
    case MOVE_MYSTICAL_POWER:
        return TRUE;
    default:
        return FALSE;
    }
}

static u32 GetSpeciesBaseStatTotal(u16 species)
{
    return GetSpeciesBaseStat(species, STAT_HP)
         + GetSpeciesBaseStat(species, STAT_ATK)
         + GetSpeciesBaseStat(species, STAT_DEF)
         + GetSpeciesBaseStat(species, STAT_SPATK)
         + GetSpeciesBaseStat(species, STAT_SPDEF)
         + GetSpeciesBaseStat(species, STAT_SPEED);
}

static inline u32 CalcMoveBasePowerAfterModifiers(struct BattleContext *ctx, u32 *unmodifiedBasePower)
{
    u32 holdEffectParamAtk;
    u32 basePower = CalcMoveBasePower(ctx);
    *unmodifiedBasePower = basePower;
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum Type moveType = ctx->moveType;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);
    enum Ability battlerTraits[MAX_MON_TRAITS];

    uq4_12_t holdEffectModifier;
    uq4_12_t modifier = UQ_4_12(1.0);
    u32 atkSide = GetBattlerSide(battlerAtk);

    // move effect
    switch (moveEffect)
    {
    case EFFECT_FACADE:
        if (gBattleMons[battlerAtk].status1 & (STATUS1_BURN | STATUS1_PSN_ANY | STATUS1_PARALYSIS | STATUS1_FROSTBITE)
         || BattlerHasTrait(battlerAtk, ABILITY_HAUNTED))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_BRINE:
        if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP / 2))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_RETALIATE:
    {
        u32 retaliateTimer = gSideTimers[atkSide].retaliateTimer;
        if (retaliateTimer  == 1 || (gAiLogicData->switchInCalc && retaliateTimer == 2))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    }
    case EFFECT_SOLAR_BEAM:
    {
        u32 weather = GetBattlerWeather(battlerAtk, ctx->weather);
        if ((GetConfig(B_SANDSTORM_SOLAR_BEAM) >= GEN_3 && weather & B_WEATHER_LOW_LIGHT)
            || weather & (B_WEATHER_RAIN | B_WEATHER_ICY_ANY | B_WEATHER_FOG)) // Excludes Sandstorm
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        break;
    }
    case EFFECT_STOMPING_TANTRUM:
        if (gBattleStruct->battlerState[battlerAtk].stompingTantrumTimer == 1)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_MAGNITUDE:
    case EFFECT_EARTHQUAKE:
        if (ctx->fieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && !IsSemiInvulnerable(battlerDef, CHECK_ALL))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        break;
    case EFFECT_KNOCK_OFF:
        if (B_KNOCK_OFF_DMG >= GEN_6)
        {
            bool32 canKnockOff = FALSE;
            for (u32 i = 0; i < MAX_MON_ITEMS; i++)
            {
                if (gBattleMons[battlerDef].items[i] != ITEM_NONE
                 && CanBattlerGetOrLoseItem(battlerDef, battlerAtk, gBattleMons[battlerDef].items[i]))
                 {
                    canKnockOff = TRUE;
                    break;
                 }
            }
        if (canKnockOff)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        }
        break;
    default:
        break;
    }

    // various effects
    for (u32 i = 0; i < gProtectStructs[battlerAtk].helpingHand; i++)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));

    if (gSpecialStatuses[battlerAtk].gemBoost)
        modifier = uq4_12_multiply(modifier, PercentToUQ4_12AddOne(gSpecialStatuses[battlerAtk].gemParam));
    if (moveType == TYPE_ELECTRIC && gBattleMons[battlerAtk].volatiles.chargeTimer > 0)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
    if (moveType == TYPE_STEEL && gBattleMons[battlerAtk].volatiles.overlock)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
    if (GetMoveEffect(ctx->chosenMove) == EFFECT_ME_FIRST)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (IsGrassyTerrainAffected(battlerAtk, ctx->fieldStatuses) && moveType == TYPE_GRASS)
        modifier = uq4_12_multiply(modifier, (B_TERRAIN_TYPE_BOOST >= GEN_8 ? UQ_4_12(1.3) : UQ_4_12(1.5)));
    if (IsMistyTerrainAffected(battlerDef, ctx->fieldStatuses) && moveType == TYPE_DRAGON)
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    if (IsElectricTerrainAffected(battlerAtk, ctx->fieldStatuses) && moveType == TYPE_ELECTRIC)
        modifier = uq4_12_multiply(modifier, (B_TERRAIN_TYPE_BOOST >= GEN_8 ? UQ_4_12(1.3) : UQ_4_12(1.5)));
    if (IsPsychicTerrainAffected(battlerAtk, ctx->fieldStatuses) && moveType == TYPE_PSYCHIC)
        modifier = uq4_12_multiply(modifier, (B_TERRAIN_TYPE_BOOST >= GEN_8 ? UQ_4_12(1.3) : UQ_4_12(1.5)));
    if (IsFieldMudSportAffected(ctx->moveType))
        modifier = uq4_12_multiply(modifier, UQ_4_12(GetConfig(B_SPORT_DMG_REDUCTION) >= GEN_5 ? 0.33 : 0.5));
    if (IsFieldWaterSportAffected(ctx->moveType))
        modifier = uq4_12_multiply(modifier, UQ_4_12(GetConfig(B_SPORT_DMG_REDUCTION) >= GEN_5 ? 0.33 : 0.5));
    if (ctx->weather & B_WEATHER_TWILIGHT && HasWeatherEffect())
    {
        if (moveType == TYPE_DARK || moveType == TYPE_GHOST)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        else if (moveType == TYPE_FIGHTING || moveType == TYPE_FAIRY)
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.8));
    }

    // attacker's abilities
    STORE_BATTLER_TRAITS(battlerAtk);

    if (SearchTraits(battlerTraits, ABILITY_TECHNICIAN) && basePower <= 60)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_FLARE_BOOST) && gBattleMons[battlerAtk].status1 & STATUS1_BURN && IsBattleMoveSpecial(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_TOXIC_BOOST) && gBattleMons[battlerAtk].status1 & STATUS1_PSN_ANY && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_RECKLESS) && (moveEffect == EFFECT_RECOIL || moveEffect == EFFECT_RECOIL_IF_MISS))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
    if (SearchTraits(battlerTraits, ABILITY_IRON_FIST) && IsPunchingMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
    if (SearchTraits(battlerTraits, ABILITY_STEEL_FEET) && IsKickingMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
    if (SearchTraits(battlerTraits, ABILITY_SHEER_FORCE) && MoveIsAffectedBySheerForce(move))
        {modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));}
    if (SearchTraits(battlerTraits, ABILITY_SAND_FORCE) && (moveType == TYPE_STEEL || moveType == TYPE_ROCK || moveType == TYPE_GROUND)
        && ctx->weather & B_WEATHER_SANDSTORM)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    if (SearchTraits(battlerTraits, ABILITY_RIVALRY))
    {
        if (AreBattlersOfSameGender(battlerAtk, battlerDef))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
        else if (AreBattlersOfOppositeGender(battlerAtk, battlerDef))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
    }
    if (SearchTraits(battlerTraits, ABILITY_ANALYTIC)
     && IsLastMonToMove(battlerAtk) && moveEffect != EFFECT_FUTURE_SIGHT)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    if (SearchTraits(battlerTraits, ABILITY_TOUGH_CLAWS) && IsMoveMakingContact(battlerAtk, battlerDef, ctx->move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    if (SearchTraits(battlerTraits, ABILITY_STRONG_JAW) && IsBitingMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_MEGA_LAUNCHER) && IsPulseMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_WATER_BUBBLE) && moveType == TYPE_WATER)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
    if (SearchTraits(battlerTraits, ABILITY_STEELWORKER) && moveType == TYPE_STEEL)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_WINDCALLER) && moveType == TYPE_FLYING)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    if (SearchTraits(battlerTraits, ABILITY_ASH_ASSETS)
     && (ctx->fieldStatuses & STATUS_FIELD_SCORCHED_FIELD))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.15));
    if (SearchTraits(battlerTraits, ABILITY_ENIGMA) && IsEnigmaPowerMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
    if (SearchTraits(battlerTraits, ABILITY_BURROWER) && move == MOVE_DIG)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_DIVER) && move == MOVE_DIVE)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_FLIER) && move == MOVE_FLY)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_LAST_STAND))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    if (SearchTraits(battlerTraits, ABILITY_GANG_UP)
     && gProtectStructs[battlerDef].assuranceDoubled
     && IsCustomAbilityDirectDamagingMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
    if (SearchTraits(battlerTraits, ABILITY_PENDULUM)
     && gBattleStruct->pendulumLastMove[battlerAtk] == move
     && gBattleStruct->pendulumStreak[battlerAtk] > 0
     && IsCustomAbilityDirectDamagingMove(move))
        modifier = uq4_12_multiply(modifier, PercentToUQ4_12AddOne(min(gBattleStruct->pendulumStreak[battlerAtk], 3) * 20));
    if (SearchTraits(battlerTraits, ABILITY_BLITZ)
     && gBattleStruct->blitzReady[battlerAtk]
     && IsCustomAbilityDirectDamagingMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
    if (SearchTraits(battlerTraits, ABILITY_FLARE)
     && moveType == TYPE_FIRE
     && gBattleMons[battlerDef].status1 & STATUS1_BURN)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_UNDERDOG)
     && IsCustomAbilityDirectDamagingMove(move)
     && GetSpeciesBaseStatTotal(gBattleMons[battlerDef].species) > GetSpeciesBaseStatTotal(gBattleMons[battlerAtk].species))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    for (u32 i = 0; i < MAX_MON_TRAITS; i++)
    {
        if (GetAteAbilityType(battlerTraits[i]) == moveType && gBattleStruct->battlerState[battlerAtk].ateBoost)
        {
            modifier = uq4_12_multiply(modifier, UQ_4_12(GetConfig(B_ATE_MULTIPLIER) >= GEN_7 ? 1.2 : 1.3));
            break;
        }
    }
    if (SearchTraits(battlerTraits, ABILITY_NORMALIZE) && moveType == TYPE_NORMAL && gBattleStruct->battlerState[battlerAtk].ateBoost && GetConfig(B_ATE_MULTIPLIER) >= GEN_7)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
    if (SearchTraits(battlerTraits, ABILITY_PUNK_ROCK) && IsSoundMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    if (SearchTraits(battlerTraits, ABILITY_STEELY_SPIRIT) && moveType == TYPE_STEEL)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_SHARPNESS) && IsSlicingMove(move))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_SUPREME_OVERLORD))
        modifier = uq4_12_multiply(modifier, GetSupremeOverlordModifier(battlerAtk));
    if (SearchTraits(battlerTraits, ABILITY_PACK_LEADER))
        modifier = uq4_12_multiply(modifier, GetPackLeaderModifier(battlerAtk));
    if (SearchTraits(battlerTraits, ABILITY_HORSE_COUNCIL))
        modifier = uq4_12_multiply(modifier, GetHorseCouncilModifier(battlerAtk));

    // field abilities
    if ((IsAbilityOnField(ABILITY_DARK_AURA) && moveType == TYPE_DARK)
     || (IsAbilityOnField(ABILITY_FAIRY_AURA) && moveType == TYPE_FAIRY))
    {
        if (IsAbilityOnField(ABILITY_AURA_BREAK))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
        else
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.33));
    }

    // attacker partner's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
    {
        STORE_BATTLER_TRAITS(BATTLE_PARTNER(battlerAtk));

        if (SearchTraits(battlerTraits, ABILITY_BATTERY)
         && IsBattleMoveSpecial(move))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        
        if (SearchTraits(battlerTraits, ABILITY_POWER_SPOT))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));

        if (SearchTraits(battlerTraits, ABILITY_STEELY_SPIRIT)
         && moveType == TYPE_STEEL)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    }

    // target's abilities
    STORE_BATTLER_TRAITS(ctx->battlerDef);

    if(SearchTraits(battlerTraits, ABILITY_HEATPROOF)
     && moveType == TYPE_FIRE)
    {
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_HEATPROOF);
    }
    if(SearchTraits(battlerTraits, ABILITY_WATER_BUBBLE)
     && moveType == TYPE_FIRE)
    {
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_WATER_BUBBLE);
    }
    if(SearchTraits(battlerTraits, ABILITY_DRY_SKIN)
     && moveType == TYPE_FIRE)
    {
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
    }
    
    u16 battlerItems[MAX_MON_ITEMS];
    STORE_BATTLER_ITEMS(battlerAtk);

    #define ITEM_EFFECT_PARAM_ATK(item) holdEffectParamAtk = GetBattlerItemHoldEffectParam(battlerAtk, item); \
        if (holdEffectParamAtk > 100) holdEffectParamAtk = 100; \
        holdEffectModifier = uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(holdEffectParamAtk));

    #define HOLD_EFFECT_PARAM_ATK(holdEffect) holdEffectParamAtk = GetBattlerItemHoldEffectParam(battlerAtk, GetBattlerHeldItemWithEffect(battlerAtk, holdEffect, TRUE)); \
        if (holdEffectParamAtk > 100) holdEffectParamAtk = 100; \
        holdEffectModifier = uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(holdEffectParamAtk));
    

    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (battlerItems[i] != ITEM_NONE)
        {
            // attacker's hold effect
            if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_MUSCLE_BAND
             && IsBattleMovePhysical(move))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12_Floored(holdEffectParamAtk)));
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_WISE_GLASSES
             && IsBattleMoveSpecial(move))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12_Floored(holdEffectParamAtk)));
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_LUSTROUS_ORB
             && GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_PALKIA && (moveType == TYPE_WATER || moveType == TYPE_DRAGON))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, holdEffectModifier);
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_ADAMANT_ORB
             && GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_DIALGA && (moveType == TYPE_STEEL || moveType == TYPE_DRAGON))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, holdEffectModifier);
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_GRISEOUS_ORB
             && GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_GIRATINA && (moveType == TYPE_GHOST || moveType == TYPE_DRAGON))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, holdEffectModifier);
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_SOUL_DEW
             && (gBattleMons[battlerAtk].species == SPECIES_LATIAS || gBattleMons[battlerAtk].species == SPECIES_LATIOS)
             && ((B_SOUL_DEW_BOOST >= GEN_7 && (moveType == TYPE_PSYCHIC || moveType == TYPE_DRAGON))
             || (B_SOUL_DEW_BOOST < GEN_7 && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER) && IsBattleMoveSpecial(move))))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, holdEffectModifier);
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_TYPE_POWER
             && moveType == GetItemSecondaryId(battlerItems[i]))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, holdEffectModifier);
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_PLATE
             && moveType == GetItemSecondaryId(battlerItems[i]))
            {
                ITEM_EFFECT_PARAM_ATK(battlerItems[i]);
                modifier = uq4_12_multiply(modifier, holdEffectModifier);
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_PUNCHING_GLOVE
             && IsPunchingMove(move))
            {
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.1));
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
            else if (GetBattlerItemHoldEffect(battlerAtk, battlerItems[i]) == HOLD_EFFECT_OGERPON_MASK
             && GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_OGERPON)
            {
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
                if (!GetConfig(B_ALLOW_HELD_DUPES))
                    i = MAX_MON_ITEMS;
            }
        }
    }

    // Terastallization boosts weak, non-priority, non-multi hit moves after modifiers to 60 BP.
    if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA
        && (moveType == GetBattlerTeraType(battlerAtk)
        || (GetBattlerTeraType(battlerAtk) == TYPE_STELLAR && IsTypeStellarBoosted(battlerAtk, moveType)))
        && uq4_12_multiply_by_int_half_down(modifier, basePower) < 60
        && GetMovePower(move) > 1
        && GetMoveStrikeCount(move) < 2
        && !IsMultiHitMove(move)
        && moveEffect != EFFECT_POWER_BASED_ON_USER_HP
        && moveEffect != EFFECT_POWER_BASED_ON_TARGET_HP
        && GetMovePriority(move) == 0)
    {
        return 60;
    }

    return uq4_12_multiply_by_int_half_down(modifier, basePower);
}

static bool32 IsRuinStatusActive(u32 fieldEffect)
{
    bool32 isNeutralizingGasOnField = IsNeutralizingGasOnField();
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        // Mold Breaker doesn't ignore Ruin field status but Gastro Acid and Neutralizing Gas do
        if (gBattleMons[battler].volatiles.gastroAcid)
            continue;
        if (!BattlerHasHeldItemEffectIgnoreAbility(battler, HOLD_EFFECT_ABILITY_SHIELD, TRUE)
         && isNeutralizingGasOnField
         && gBattleMons[battler].ability != ABILITY_NEUTRALIZING_GAS)
            continue;

        if (GetBattlerVolatile(battler, fieldEffect))
            return TRUE;
    }

    return FALSE;
}

static inline uq4_12_t ApplyOffensiveBadgeBoost(uq4_12_t modifier, enum BattlerId battler, enum Move move)
{
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_ATTACK, battler) && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_SPATK, battler) && IsBattleMoveSpecial(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    return modifier;
}

static inline uq4_12_t ApplyDefensiveBadgeBoost(uq4_12_t modifier, enum BattlerId battler, enum Move move)
{
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_DEFENSE, battler) && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_SPDEF, battler) && IsBattleMoveSpecial(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    return modifier;
}

static inline bool32 ShouldUseSpAtkForPhysicalMove(enum Move move, enum Ability *battlerTraits)
{
    return IsBattleMovePhysical(move)
        && (SearchTraits(battlerTraits, ABILITY_ELEMENTALIST)
         || (SearchTraits(battlerTraits, ABILITY_ELEMENTAL_FIST) && IsPunchingMove(move)));
}

static inline u32 CalcAttackStat(struct BattleContext *ctx)
{
    u8 atkStage;
    u32 atkStat;
    uq4_12_t modifier;
    u16 atkBaseSpeciesId;
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum Type moveType = ctx->moveType;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battlerAtk);

    atkBaseSpeciesId = GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species);

    if (moveEffect == EFFECT_FOUL_PLAY)
    {
        if (IsBattleMovePhysical(move))
        {
            atkStat = gBattleMons[battlerDef].attack;
            atkStage = gBattleMons[battlerDef].statStages[STAT_ATK];
        }
        else
        {
            atkStat = gBattleMons[battlerDef].spAttack;
            atkStage = gBattleMons[battlerDef].statStages[STAT_SPATK];
        }
    }
    else if (moveEffect == EFFECT_BODY_PRESS)
    {
        if (IsBattleMovePhysical(move))
        {
            atkStat = gBattleMons[battlerAtk].defense;
            // Edge case: Body Press used during Wonder Room. For some reason, it still uses Defense over Sp.Def, but uses Sp.Def stat changes
            if (ctx->fieldStatuses & STATUS_FIELD_WONDER_ROOM)
                atkStage = gBattleMons[battlerAtk].statStages[STAT_SPDEF];
            else
                atkStage = gBattleMons[battlerAtk].statStages[STAT_DEF];
        }
        else
        {
            atkStat = gBattleMons[battlerAtk].spDefense;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_SPDEF];
        }
    }
    else
    {
        if (SearchTraits(battlerTraits, ABILITY_SIEGEBREAKER))
        {
            atkStat = gBattleMons[battlerAtk].defense * 2 / 3;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_DEF];
        }
        else if (ShouldUseSpAtkForPhysicalMove(move, battlerTraits))
        {
            atkStat = gBattleMons[battlerAtk].spAttack;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_SPATK];
        }
        else if (IsBattleMovePhysical(move))
        {
            atkStat = gBattleMons[battlerAtk].attack;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_ATK];
        }
        else
        {
            atkStat = gBattleMons[battlerAtk].spAttack;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_SPATK];
        }
    }

    // critical hits ignore attack stat's stage drops
    if (ctx->isCrit && atkStage < DEFAULT_STAT_STAGE)
        atkStage = DEFAULT_STAT_STAGE;
    // pokemon with unaware ignore attack stat changes while taking damage
    if (BattlerHasTrait(battlerDef, ABILITY_UNAWARE))
        atkStage = DEFAULT_STAT_STAGE;

    atkStat *= gStatStageRatios[atkStage][0];
    atkStat /= gStatStageRatios[atkStage][1];

    // apply attack stat modifiers
    modifier = UQ_4_12(1.0);

    if (ctx->isSelfInflicted)
        return uq4_12_multiply_by_int_half_down(ApplyOffensiveBadgeBoost(modifier, battlerAtk, move), atkStat);

    // attacker's abilities
    if (SearchTraits(battlerTraits, ABILITY_HUGE_POWER)
     && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    if (SearchTraits(battlerTraits, ABILITY_PURE_POWER)
     && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    if (SearchTraits(battlerTraits, ABILITY_SLOW_START)
     && gBattleMons[battlerAtk].volatiles.slowStartTimer > 0
     && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
    if (SearchTraits(battlerTraits, ABILITY_SOLAR_POWER)
     && IsBattleMoveSpecial(move) && IsBattlerWeatherAffected(battlerAtk, B_WEATHER_SUN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_DEFEATIST)
     && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 2))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
    if (SearchTraits(battlerTraits, ABILITY_FLASH_FIRE)
     && moveType == TYPE_FIRE && gBattleMons[battlerAtk].volatiles.flashFireBoosted)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_SWARM)
     && moveType == TYPE_BUG && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_TORRENT)
     && moveType == TYPE_WATER && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_BLAZE)
     && moveType == TYPE_FIRE && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_OVERGROW)
     && moveType == TYPE_GRASS && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_PLUS)
     && IsBattleMoveSpecial(move) && IsBattlerAlive(BATTLE_PARTNER(battlerAtk))
     && (BattlerHasTrait(BATTLE_PARTNER(battlerAtk), ABILITY_MINUS)
     || (B_PLUS_MINUS_INTERACTION >= GEN_5 && BattlerHasTrait(BATTLE_PARTNER(battlerAtk), ABILITY_PLUS))))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_MINUS)
     && IsBattleMoveSpecial(move) && IsBattlerAlive(BATTLE_PARTNER(battlerAtk))
     && (BattlerHasTrait(BATTLE_PARTNER(battlerAtk), ABILITY_PLUS)
     || (B_PLUS_MINUS_INTERACTION >= GEN_5 && BattlerHasTrait(BATTLE_PARTNER(battlerAtk), ABILITY_MINUS))))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_FLOWER_GIFT)
     && gBattleMons[battlerAtk].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(battlerAtk, B_WEATHER_SUN) && IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_HUSTLE)
     && IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_STAKEOUT)
     && gBattleStruct->battlerState[battlerDef].isFirstTurn == 2) // just switched in
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    if (SearchTraits(battlerTraits, ABILITY_GUTS)
     && BattlerHasEffectiveMajorStatus(battlerAtk) && IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_HUNTER) && IsBattleMovePhysical(move))
    {
        for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
        {
            if (!IsBattlerAlly(battlerAtk, battler)
             && IsBattlerAlive(battler)
             && gBattleMons[battler].status1 & STATUS1_PARALYSIS)
            {
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
                break;
            }
        }
    }
    if (SearchTraits(battlerTraits, ABILITY_TRANSISTOR)
     && moveType == TYPE_ELECTRIC)
        {
            if (GetConfig(B_TRANSISTOR_BOOST) >= GEN_9)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            else
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        }
    if (SearchTraits(battlerTraits, ABILITY_DRAGONS_MAW)
     && moveType == TYPE_DRAGON)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_GORILLA_TACTICS)
     && IsBattleMovePhysical(move)
     && !IsGimmickSelected(battlerAtk, GIMMICK_DYNAMAX)
     && GetActiveGimmick(battlerAtk) != GIMMICK_DYNAMAX)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_ROCKY_PAYLOAD)
     && moveType == TYPE_ROCK)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (SearchTraits(battlerTraits, ABILITY_GENERALIST)
     && move != MOVE_STRUGGLE
     && move != MOVE_NONE
     && moveType != TYPE_MYSTERY
     && !IS_BATTLER_OF_TYPE(battlerAtk, moveType))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
    for (u32 i = 0; i < MAX_MON_TRAITS; i++)
    {
        if (GetTypeBoostAbilityType(battlerTraits[i]) == moveType)
        {
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
            break;
        }
    }
    if (SearchTraits(battlerTraits, ABILITY_PROTOSYNTHESIS)
     && !(gBattleMons[battlerAtk].volatiles.transformed))
    {
        enum Stat atkHighestStat = GetParadoxBoostedStatId(battlerAtk);
        if (ctx->weather & B_WEATHER_SUN || gBattleMons[battlerAtk].volatiles.boosterEnergyActivated)
        {
            if ((IsBattleMovePhysical(move) && atkHighestStat == STAT_ATK) || (IsBattleMoveSpecial(move) && atkHighestStat == STAT_SPATK))
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        }
    }
    if (SearchTraits(battlerTraits, ABILITY_QUARK_DRIVE)
     && !(gBattleMons[battlerAtk].volatiles.transformed))
        {
            enum Stat atkHighestStat = GetParadoxBoostedStatId(battlerAtk);
            if (ctx->fieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN || gBattleMons[battlerAtk].volatiles.boosterEnergyActivated)
            {
                if ((IsBattleMovePhysical(move) && atkHighestStat == STAT_ATK) || (IsBattleMoveSpecial(move) && atkHighestStat == STAT_SPATK))
                    modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            }
        }
    if (SearchTraits(battlerTraits, ABILITY_ORICHALCUM_PULSE)
     && (ctx->weather & B_WEATHER_SUN) && HasWeatherEffect() && IsBattleMovePhysical(move)
     && !BattlerHasHeldItemEffect(battlerAtk, HOLD_EFFECT_UTILITY_UMBRELLA, TRUE))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3333));
    if (SearchTraits(battlerTraits, ABILITY_HADRON_ENGINE)
     && (ctx->fieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN && IsBattleMoveSpecial(move)))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3333));

    // target's abilities
    if (BattlerHasTrait(battlerDef, ABILITY_THICK_FAT)
     && (moveType == TYPE_FIRE || moveType == TYPE_ICE))
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_THICK_FAT);
    }
    if (BattlerHasTrait(battlerDef, ABILITY_PURIFYING_SALT)
     && moveType == TYPE_GHOST)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_PURIFYING_SALT);
    }
    if (BattlerHasTrait(battlerDef, ABILITY_PHALANX)
     && IsBattleMovePhysical(move))
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_PHALANX);
    }
    if (BattlerHasTrait(battlerDef, ABILITY_SPECTRAL)
     && IsBattleMoveSpecial(move))
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_SPECTRAL);
    }

    // ally's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
    {
        if (BattlerHasTrait(BATTLE_PARTNER(battlerAtk), ABILITY_FLOWER_GIFT)
         && gBattleMons[BATTLE_PARTNER(battlerAtk)].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(BATTLE_PARTNER(battlerAtk), B_WEATHER_SUN) && IsBattleMovePhysical(move))
        {
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        }
    }

    // Ruin field effects
    if (IsBattleMoveSpecial(move) && !gBattleMons[ctx->battlerAtk].volatiles.vesselOfRuin && IsRuinStatusActive(VOLATILE_VESSEL_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    if (IsBattleMovePhysical(move) && !gBattleMons[ctx->battlerAtk].volatiles.tabletsOfRuin && IsRuinStatusActive(VOLATILE_TABLETS_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    u16 battlerItems[MAX_MON_ITEMS];
    STORE_BATTLER_ITEMS(battlerAtk);

    // attacker's hold effect
    if (SearchItemSlots(battlerItems, HOLD_EFFECT_THICK_CLUB)){
        if ((atkBaseSpeciesId == SPECIES_CUBONE || atkBaseSpeciesId == SPECIES_MAROWAK) && IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    }
    if (SearchItemSlots(battlerItems, HOLD_EFFECT_DEEP_SEA_TOOTH)){
        if (gBattleMons[battlerAtk].species == SPECIES_CLAMPERL && IsBattleMoveSpecial(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    }

    if (SearchItemSlots(battlerItems, HOLD_EFFECT_LIGHT_BALL)){
        if (atkBaseSpeciesId == SPECIES_PIKACHU && (GetConfig(B_LIGHT_BALL_ATTACK_BOOST) >= GEN_4 || IsBattleMoveSpecial(move)))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    }

    if (SearchItemSlots(battlerItems, HOLD_EFFECT_CHOICE_BAND)){
        if (IsBattleMovePhysical(move) && GetActiveGimmick(battlerAtk) != GIMMICK_DYNAMAX)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    }

    if (SearchItemSlots(battlerItems, HOLD_EFFECT_CHOICE_SPECS)){
        if (IsBattleMoveSpecial(move) && GetActiveGimmick(battlerAtk) != GIMMICK_DYNAMAX)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    }

    modifier = ApplyOffensiveBadgeBoost(modifier, battlerAtk, move);

    return uq4_12_multiply_by_int_half_down(modifier, atkStat);
}

static bool32 CanEvolve(u32 species)
{
    u32 i;
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    if (evolutions != NULL)
    {
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            if (evolutions[i].method
             && SanitizeSpeciesId(evolutions[i].targetSpecies) != SPECIES_NONE)
                return TRUE;
        }
    }
    return FALSE;
}

static inline u32 CalcDefenseStat(struct BattleContext *ctx)
{
    bool32 usesDefStat;
    u8 defStage;
    u32 defStat, def, spDef;
    uq4_12_t modifier;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);
    enum Ability battlerTraits[MAX_MON_TRAITS];

    def = gBattleMons[battlerDef].defense;
    spDef = gBattleMons[battlerDef].spDefense;

    if (moveEffect == EFFECT_PSYSHOCK || IsBattleMovePhysical(move)) // uses defense stat instead of sp.def
    {
        if (ctx->fieldStatuses & STATUS_FIELD_WONDER_ROOM) // the defense stats are swapped
        {
            defStat = spDef;
            usesDefStat = FALSE;
        }
        else
        {
            defStat = def;
            usesDefStat = TRUE;
        }
        defStage = gBattleMons[battlerDef].statStages[STAT_DEF];
    }
    else // is special
    {
        if (ctx->fieldStatuses & STATUS_FIELD_WONDER_ROOM) // the defense stats are swapped
        {
            defStat = def;
            usesDefStat = TRUE;
        }
        else
        {
            defStat = spDef;
            usesDefStat = FALSE;
        }
        defStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
    }

    // Self-destruct / Explosion cut defense in half
    if (GetConfig(B_EXPLOSION_DEFENSE) < GEN_5 && IsExplosionMove(ctx->move))
        defStat /= 2;

    // critical hits ignore positive stat changes
    if (ctx->isCrit && defStage > DEFAULT_STAT_STAGE)
        defStage = DEFAULT_STAT_STAGE;
    // pokemon with unaware ignore defense stat changes while dealing damage
    if (BattlerHasTrait(ctx->battlerAtk, ABILITY_UNAWARE))
        defStage = DEFAULT_STAT_STAGE;
    // certain moves also ignore stat changes
    if (MoveIgnoresDefenseEvasionStages(move))
        defStage = DEFAULT_STAT_STAGE;

    defStat *= gStatStageRatios[defStage][0];
    defStat /= gStatStageRatios[defStage][1];

    // apply defense stat modifiers
    modifier = UQ_4_12(1.0);

    if (ctx->isSelfInflicted)
        return uq4_12_multiply_by_int_half_down(ApplyDefensiveBadgeBoost(modifier, battlerDef, move), defStat);

    // target's abilities
    STORE_BATTLER_TRAITS(battlerDef);

    if (SearchTraits(battlerTraits, ABILITY_MARVEL_SCALE)
     && BattlerHasEffectiveMajorStatus(battlerDef) && usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_MARVEL_SCALE);
    }
    if (SearchTraits(battlerTraits, ABILITY_FUR_COAT)
     && usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_FUR_COAT);
    }
    if (SearchTraits(battlerTraits, ABILITY_SANDSHIELD)
     && IsBattlerWeatherAffected(battlerDef, B_WEATHER_SANDSTORM) && usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_SANDSHIELD);
    }
    if (SearchTraits(battlerTraits, ABILITY_COALWALKER)
     && (ctx->fieldStatuses & STATUS_FIELD_SCORCHED_FIELD) && usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_COALWALKER);
    }
    if (SearchTraits(battlerTraits, ABILITY_SUNHARDENED)
     && IsBattlerWeatherAffected(battlerDef, B_WEATHER_SUN) && !usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_SUNHARDENED);
    }
    if (SearchTraits(battlerTraits, ABILITY_GRASS_PELT)
     && ctx->fieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_GRASS_PELT);
    }
    if (SearchTraits(battlerTraits, ABILITY_ALLSEEING_IDOL)
     && ctx->fieldStatuses & STATUS_FIELD_GRAVITY && usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.3));
        if (ctx->updateFlags)
            RecordAbilityBattle(battlerDef, ABILITY_ALLSEEING_IDOL);
    }
    if (SearchTraits(battlerTraits, ABILITY_FLOWER_GIFT)
     && gBattleMons[battlerDef].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(battlerDef, B_WEATHER_SUN) && !usesDefStat)
    {
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    }
    if(SearchTraits(battlerTraits, ABILITY_PROTOSYNTHESIS))
    {
        enum Stat defHighestStat = GetParadoxBoostedStatId(battlerDef);
        if (((ctx->weather & B_WEATHER_SUN && HasWeatherEffect()) || gBattleMons[battlerDef].volatiles.boosterEnergyActivated)
         && ((IsBattleMovePhysical(move) && defHighestStat == STAT_DEF) || (IsBattleMoveSpecial(move) && defHighestStat == STAT_SPDEF))
         && !(gBattleMons[battlerDef].volatiles.transformed))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    }
     if(SearchTraits(battlerTraits, ABILITY_QUARK_DRIVE))
    {
        u32 defHighestStat = GetParadoxBoostedStatId(battlerDef);
        if ((gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN || gBattleMons[battlerDef].volatiles.boosterEnergyActivated)
         && ((IsBattleMovePhysical(move) && defHighestStat == STAT_DEF) || (IsBattleMoveSpecial(move) && defHighestStat == STAT_SPDEF))
         && !(gBattleMons[battlerDef].volatiles.transformed))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    }

    // ally's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerDef))
     && BattlerHasTrait(BATTLE_PARTNER(battlerDef), ABILITY_FLOWER_GIFT))
    {
        if (gBattleMons[BATTLE_PARTNER(battlerDef)].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(BATTLE_PARTNER(battlerDef), B_WEATHER_SUN) && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    }

    // Ruin field effects
    if (usesDefStat && !gBattleMons[ctx->battlerDef].volatiles.swordOfRuin && IsRuinStatusActive(VOLATILE_SWORD_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    if (!usesDefStat && !gBattleMons[ctx->battlerDef].volatiles.beadsOfRuin && IsRuinStatusActive(VOLATILE_BEADS_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    u16 battlerItems[MAX_MON_ITEMS];
    STORE_BATTLER_ITEMS(battlerDef);

    // target's hold effects
    if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD) && SearchItemSlots(battlerItems, HOLD_EFFECT_DEEP_SEA_SCALE))
    {
        if (gBattleMons[battlerDef].species == SPECIES_CLAMPERL && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    }
    if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD) && SearchItemSlots(battlerItems, HOLD_EFFECT_METAL_POWDER))
    {
        if (gBattleMons[battlerDef].species == SPECIES_DITTO && usesDefStat && !(gBattleMons[battlerDef].volatiles.transformed))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
    }
    if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD) && SearchItemSlots(battlerItems, HOLD_EFFECT_EVIOLITE))
    {
        {
            u16 species = gBattleMons[battlerDef].species;
            if (gBattleMons[battlerDef].volatiles.transformed && gBattleMons[battlerDef].volatiles.transformedMonSpecies != SPECIES_NONE)
                species = gBattleMons[battlerDef].volatiles.transformedMonSpecies;
            if (CanEvolve(species))
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        }
    }
    if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD) && SearchItemSlots(battlerItems, HOLD_EFFECT_ASSAULT_VEST))
    {
        if (!usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    }
    if (SearchItemSlots(battlerItems, HOLD_EFFECT_SOUL_DEW))
    {
        if (B_SOUL_DEW_BOOST < GEN_7
         && (gBattleMons[battlerDef].species == SPECIES_LATIAS || gBattleMons[battlerDef].species == SPECIES_LATIOS)
         && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
         && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    }

    // sandstorm sp.def boost for rock types
    if (GetConfig(B_SANDSTORM_SPDEF_BOOST) >= GEN_4 && IS_BATTLER_OF_TYPE(battlerDef, TYPE_ROCK) && IsBattlerWeatherAffected(battlerDef, B_WEATHER_SANDSTORM) && !usesDefStat)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    // snow def boost for ice types
    if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_ICE) && IsBattlerWeatherAffected(battlerDef, B_WEATHER_SNOW) && usesDefStat)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));

    modifier = ApplyDefensiveBadgeBoost(modifier, battlerDef, move);

    return uq4_12_multiply_by_int_half_down(modifier, defStat);
}

// base damage formula before adding any modifiers
static inline s32 CalculateBaseDamage(u32 power, u32 userFinalAttack, u32 level, u32 targetFinalDefense)
{
    return power * userFinalAttack * (2 * level / 5 + 2) / targetFinalDefense / 50 + 2;
}

static inline uq4_12_t GetTargetDamageModifier(struct BattleContext *ctx)
{
    if (IsDoubleBattle())
    {
        if (GetMoveTargetCount(ctx) == 2)
            return B_MULTIPLE_TARGETS_DMG >= GEN_4 ? UQ_4_12(0.75) : UQ_4_12(0.5);
        else if (GetMoveTargetCount(ctx) >= 3)
            return B_MULTIPLE_TARGETS_DMG >= GEN_4 ? UQ_4_12(0.75) : UQ_4_12(1.0);
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetParentalBondModifier(enum BattlerId battlerAtk)
{
    if (gSpecialStatuses[battlerAtk].parentalBondState != PARENTAL_BOND_2ND_HIT)
        return UQ_4_12(1.0);
    if (BattlerHasTrait(battlerAtk, ABILITY_ECHO_CHAMBER) && IsSoundMove(gCurrentMove))
        return UQ_4_12(0.5);
    return B_PARENTAL_BOND_DMG >= GEN_7 ? UQ_4_12(0.25) : UQ_4_12(0.5);
}

static inline uq4_12_t GetSameTypeAttackBonusModifier(struct BattleContext *ctx)
{
    if (ctx->moveType == TYPE_MYSTERY)
        return UQ_4_12(1.0);
    else if (gBattleStruct->pledgeMove && IS_BATTLER_OF_TYPE(BATTLE_PARTNER(ctx->battlerAtk), ctx->moveType))
        return (BattlerHasTrait(ctx->battlerAtk, ABILITY_ADAPTABILITY)) ? UQ_4_12(2.0) : UQ_4_12(1.5);
    else if (!IS_BATTLER_OF_TYPE(ctx->battlerAtk, ctx->moveType) || ctx->move == MOVE_STRUGGLE || ctx->move == MOVE_NONE)
        return UQ_4_12(1.0);
    return (BattlerHasTrait(ctx->battlerAtk, ABILITY_ADAPTABILITY)) ? UQ_4_12(2.0) : UQ_4_12(1.5);
}

// Utility Umbrella holders take normal damage from what would be rain- and sun-weakened attacks.
static uq4_12_t GetWeatherDamageModifier(struct BattleContext *ctx)
{
    bool32 aiCalcInProgress = (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress);
    bool32 attackerHasMegaSol = aiCalcInProgress
                              ? AI_BATTLER_HAS_TRAIT(ctx->battlerAtk, ABILITY_MEGA_SOL)
                              : BattlerHasTrait(ctx->battlerAtk, ABILITY_MEGA_SOL);
    u32 attackerWeather = attackerHasMegaSol ? B_WEATHER_SUN_NORMAL : ctx->weather;

    if ((attackerWeather | ctx->weather) == B_WEATHER_NONE)
        return UQ_4_12(1.0);
    if (GetMoveEffect(ctx->move) == EFFECT_HYDRO_STEAM
     && (attackerWeather & B_WEATHER_SUN)
     && (attackerHasMegaSol || !BattlerHasHeldItemEffect(ctx->battlerAtk, HOLD_EFFECT_UTILITY_UMBRELLA, TRUE)))
        return UQ_4_12(1.5);
    if (BattlerHasHeldItemEffect(ctx->battlerDef, HOLD_EFFECT_UTILITY_UMBRELLA, TRUE))
        return UQ_4_12(1.0);

    if (attackerWeather & B_WEATHER_SUN)
    {
        if (ctx->moveType != TYPE_FIRE && ctx->moveType != TYPE_WATER)
            return UQ_4_12(1.0);
        return (ctx->moveType == TYPE_WATER) ? UQ_4_12(0.5) : UQ_4_12(1.5);
    }
    if (attackerWeather & B_WEATHER_RAIN)
    {
        if (ctx->moveType != TYPE_FIRE && ctx->moveType != TYPE_WATER)
            return UQ_4_12(1.0);
        return (ctx->moveType == TYPE_FIRE) ? UQ_4_12(0.5) : UQ_4_12(1.5);
    }
    return UQ_4_12(1.0);
}

static uq4_12_t GetFieldDamageModifier(struct BattleContext *ctx)
{
    enum Type moveType;

    if (!(ctx->fieldStatuses & STATUS_FIELD_SCORCHED_FIELD))
        return UQ_4_12(1.0);

    if (ctx->move == MOVE_SCALD)
        return UQ_4_12(1.2);

    moveType = ctx->moveType;
    if (moveType == TYPE_FIRE || GetMoveType(ctx->move) == TYPE_FIRE)
        return UQ_4_12(1.1);
    if (moveType == TYPE_WATER || GetMoveType(ctx->move) == TYPE_WATER
     || moveType == TYPE_ICE || GetMoveType(ctx->move) == TYPE_ICE)
        return UQ_4_12(0.9);

    return UQ_4_12(1.0);
}

static inline uq4_12_t GetBurnOrFrostBiteModifier(struct BattleContext *ctx)
{
    enum BattleMoveEffects moveEffect = GetMoveEffect(ctx->move);

    if (gBattleMons[ctx->battlerAtk].status1 & STATUS1_BURN
        && IsBattleMovePhysical(ctx->move)
        && (GetConfig(B_BURN_FACADE_DMG) < GEN_6 || moveEffect != EFFECT_FACADE)
        && !BattlerHasTrait(ctx->battlerAtk, ABILITY_GUTS))
        return UQ_4_12(0.5);
    if (gBattleMons[ctx->battlerAtk].status1 & STATUS1_FROSTBITE
        && IsBattleMoveSpecial(ctx->move)
        && (GetConfig(B_BURN_FACADE_DMG) < GEN_6 || moveEffect != EFFECT_FACADE))
        return UQ_4_12(0.5);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetCriticalModifier(bool32 isCrit)
{
    if (isCrit)
        return GetConfig(B_CRIT_MULTIPLIER) >= GEN_6 ? UQ_4_12(1.5) : UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetGlaiveRushModifier(enum BattlerId battlerDef)
{
    if (gBattleMons[battlerDef].volatiles.glaiveRush)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetZMaxMoveAgainstProtectionModifier(struct BattleContext *ctx)
{
    if (!IsZMove(ctx->move) && !IsMaxMove(ctx->move))
        return UQ_4_12(1.0);

    u32 protected = gProtectStructs[ctx->battlerDef].protected;
    if (GetProtectType(protected) == PROTECT_TYPE_SINGLE && protected != PROTECT_MAX_GUARD)
        return UQ_4_12(0.25);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetMinimizeModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveIncreasesPowerToMinimizedTargets(move) && gBattleMons[battlerDef].volatiles.minimize)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetUndergroundModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveDamagesUnderground(move) && gBattleMons[battlerDef].volatiles.semiInvulnerable == STATE_UNDERGROUND)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDiveModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveDamagesUnderWater(move) && gBattleMons[battlerDef].volatiles.semiInvulnerable == STATE_UNDERWATER)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAirborneModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveDamagesAirborneDoubleDamage(move) && gBattleMons[battlerDef].volatiles.semiInvulnerable == STATE_ON_AIR)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetScreensModifier(struct BattleContext *ctx)
{
    u32 sideStatus = gSideStatuses[GetBattlerSide(ctx->battlerDef)];
    bool32 lightScreen = (sideStatus & SIDE_STATUS_LIGHTSCREEN) && IsBattleMoveSpecial(ctx->move);
    bool32 reflect = (sideStatus & SIDE_STATUS_REFLECT) && IsBattleMovePhysical(ctx->move);
    bool32 auroraVeil = sideStatus & SIDE_STATUS_AURORA_VEIL;

    if (ctx->isCrit || ctx->isSelfInflicted)
    {
        return UQ_4_12(1.0);
    }
    if ((BattlerHasTrait(ctx->battlerAtk, ABILITY_INFILTRATOR)
      || BattlerHasTrait(ctx->battlerAtk, ABILITY_VOIDTOUCH)
      || (BattlerHasTrait(ctx->battlerAtk, ABILITY_TIDAL_DEITY) && IsBattlerAtMaxHp(ctx->battlerAtk)))
     && !IsBattlerAlly(ctx->battlerAtk, ctx->battlerDef))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerAtk, BattlerHasTrait(ctx->battlerAtk, ABILITY_TIDAL_DEITY) ? ABILITY_TIDAL_DEITY : (BattlerHasTrait(ctx->battlerAtk, ABILITY_VOIDTOUCH) ? ABILITY_VOIDTOUCH : ABILITY_INFILTRATOR));
        return UQ_4_12(1.0);
    }
    if (reflect || lightScreen || auroraVeil)
    {
        return (IsDoubleBattle()) ? UQ_4_12(0.667) : UQ_4_12(0.5);
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetCollisionCourseElectroDriftModifier(enum Move move, uq4_12_t typeEffectivenessModifier)
{
    if (GetMoveEffect(move) == EFFECT_COLLISION_COURSE && typeEffectivenessModifier >= UQ_4_12(2.0))
        return UQ_4_12(1.3333);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAttackerAbilitiesModifier(enum BattlerId battlerAtk, uq4_12_t typeEffectivenessModifier, bool32 isCrit)
{
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battlerAtk);

    if (SearchTraits(battlerTraits, ABILITY_NEUROFORCE)
     && typeEffectivenessModifier >= UQ_4_12(2.0))
        return UQ_4_12(1.25);

    if (SearchTraits(battlerTraits, ABILITY_SNIPER)
     && isCrit)
        return UQ_4_12(1.5);

    if (SearchTraits(battlerTraits, ABILITY_TINTED_LENS)
     && typeEffectivenessModifier <= UQ_4_12(0.5))
        return UQ_4_12(2.0);

    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDefenderAbilitiesModifier(struct BattleContext *ctx)
{
    uq4_12_t modifier = UQ_4_12(1.0);
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(ctx->battlerDef);

    if (SearchTraits(battlerTraits, ABILITY_MULTISCALE) && IsBattlerAtMaxHp(ctx->battlerDef))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_MULTISCALE);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    }
    if (SearchTraits(battlerTraits, ABILITY_SHADOW_SHIELD) && IsBattlerAtMaxHp(ctx->battlerDef))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_SHADOW_SHIELD);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    }
    if (SearchTraits(battlerTraits, ABILITY_FILTER) && ctx->typeEffectivenessModifier >= UQ_4_12(2.0))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_FILTER);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
    }
    if (SearchTraits(battlerTraits, ABILITY_SOLID_ROCK) && ctx->typeEffectivenessModifier >= UQ_4_12(2.0))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_SOLID_ROCK);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
    }
    if (SearchTraits(battlerTraits, ABILITY_PRISM_ARMOR) && ctx->typeEffectivenessModifier >= UQ_4_12(2.0))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_PRISM_ARMOR);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
    }
    if (SearchTraits(battlerTraits, ABILITY_FLUFFY))
    {
        if (ctx->moveType == TYPE_FIRE && !IsMoveMakingContact(ctx->battlerAtk, ctx->battlerDef, ctx->move))
        {
            if (ctx->updateFlags)
                RecordAbilityBattle(ctx->battlerDef, ABILITY_FLUFFY);
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        }
        if (ctx->moveType != TYPE_FIRE && IsMoveMakingContact(ctx->battlerAtk, ctx->battlerDef, ctx->move))
        {
            if (ctx->updateFlags)
                RecordAbilityBattle(ctx->battlerDef, ABILITY_FLUFFY);
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));  
        }
    }
    if (SearchTraits(battlerTraits, ABILITY_PUNK_ROCK) 
     && IsSoundMove(ctx->move))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_PUNK_ROCK);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    }

    if (SearchTraits(battlerTraits, ABILITY_ICE_SCALES) 
     && IsBattleMoveSpecial(ctx->move))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_ICE_SCALES);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    }
    if (SearchTraits(battlerTraits, ABILITY_SHARDPLATE)
     && IsCustomAbilityDirectDamagingMove(ctx->move)
     && gBattleStruct->partyState[GetBattlerSide(ctx->battlerDef)][gBattlerPartyIndexes[ctx->battlerDef]].shardplateHits < 5)
    {
        u32 reductionPercent = 50 + (10 * gBattleStruct->partyState[GetBattlerSide(ctx->battlerDef)][gBattlerPartyIndexes[ctx->battlerDef]].shardplateHits);
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_SHARDPLATE);
        modifier = uq4_12_multiply(modifier, PercentToUQ4_12(reductionPercent));
    }
    if (SearchTraits(battlerTraits, ABILITY_GUARDIAN)
     && IsCustomAbilityDirectDamagingMove(ctx->move))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_GUARDIAN);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.85));
    }
    if (SearchTraits(battlerTraits, ABILITY_COSMIC_FORM)
     && ctx->typeEffectivenessModifier >= UQ_4_12(2.0))
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_COSMIC_FORM);
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.7));
    }

    return modifier;
}

static inline uq4_12_t GetDefenderPartnerAbilitiesModifier(enum BattlerId battlerPartnerDef)
{
    if (!IsBattlerAlive(battlerPartnerDef))
        return UQ_4_12(1.0);

    if (BattlerHasTrait(battlerPartnerDef, ABILITY_FRIEND_GUARD))
        return UQ_4_12(0.75);

    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAttackerItemsModifier(enum BattlerId battlerAtk, uq4_12_t typeEffectivenessModifier)
{
    u32 i, item;
    uq4_12_t percentBoost = UQ_4_12(1.0);
    u32 metronomeTurns;
    bool32 firstMetronome = TRUE, firstBelt = TRUE, firstOrb = TRUE;
    uq4_12_t metronomeBoostBase;

    // Metronome separated out to accomodate addition logic below which needs to happen first regardless of item order
    for (i = 0; i < MAX_MON_ITEMS; i++)
    {
        item = GetSlotHeldItem(battlerAtk, i, TRUE);

        if (GetItemHoldEffect(item) == HOLD_EFFECT_METRONOME && (firstMetronome || GetConfig(B_ALLOW_HELD_DUPES)))
        {
            firstMetronome = FALSE;
            metronomeBoostBase = PercentToUQ4_12(GetBattlerItemHoldEffectParam(battlerAtk, item));
            metronomeTurns = min(gBattleMons[battlerAtk].volatiles.metronomeItemCounter, 5);
            // according to bulbapedia this is the "correct" way to calculate the metronome boost
            // due to the limited domain of damage numbers it will never really matter whether this is off by one
            percentBoost = uq4_12_add(percentBoost, metronomeBoostBase * metronomeTurns);
        }
    }

    for (i = 0; i < MAX_MON_ITEMS; i++)
    {
        item = GetSlotHeldItem(battlerAtk, i, TRUE);

        if (GetItemHoldEffect(item) == HOLD_EFFECT_EXPERT_BELT && (firstBelt || GetConfig(B_ALLOW_HELD_DUPES))
         && typeEffectivenessModifier >= UQ_4_12(2.0))
        {
            firstBelt = FALSE;
            percentBoost = uq4_12_multiply_half_down(percentBoost, UQ_4_12(1.2));
        }

        if (GetItemHoldEffect(item) == HOLD_EFFECT_LIFE_ORB && (firstOrb || GetConfig(B_ALLOW_HELD_DUPES)))
        {
            firstOrb = FALSE;
            percentBoost = uq4_12_multiply_half_down(percentBoost, UQ_4_12(1.3));
        }
    }

    return percentBoost;
}

static inline uq4_12_t GetDefenderItemsModifier(struct BattleContext *ctx)
{
    u32 itemDef = ITEM_NONE;

    if (BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD))
        return UQ_4_12(1.0);

    for (int i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (GetItemHoldEffect(gBattleMons[ctx->battlerDef].items[i]) == HOLD_EFFECT_RESIST_BERRY)
        {
            //If B_FLYING_PRESS_RESIST is TRUE, included the second type of dual type moves like Flying Press in the check.
            if ((GetBattlerItemHoldEffectParam(ctx->battlerDef, gBattleMons[ctx->battlerDef].items[i]) == ctx->moveType
             || (B_FLYING_PRESS_RESIST == (GetMoveEffect(ctx->move) == EFFECT_TWO_TYPED_MOVE) //Logic for dual type moves
             && GetBattlerItemHoldEffectParam(ctx->battlerDef, gBattleMons[ctx->battlerDef].items[i]) == ctx->moveType)))
            {
                itemDef = GetSlotHeldItem(ctx->battlerDef, i, TRUE);
                break;
            }
        }
    }
    if(itemDef != ITEM_NONE)
    {
        if (IsUnnerveBlocked(ctx->battlerDef, itemDef))
            return UQ_4_12(1.0);
        if (ctx->moveType == TYPE_NORMAL || ctx->typeEffectivenessModifier >= UQ_4_12(2.0))
        {
            if (ctx->updateFlags)
            {
                gSpecialStatuses[ctx->battlerDef].berryReduced = TRUE;
                gSpecialStatuses[ctx->battlerDef].berryReducedType = GetBattlerItemHoldEffectParam(ctx->battlerDef, itemDef); //prevents multiple reduction berry activations and transfers hiddenpower type to eating function
            }
            if (ctx->aiCalc && AI_DAMAGES_THROUGH_BERRIES)
                ctx->aiCheckBerryModifier = TRUE;
            return (BattlerHasTrait(ctx->battlerDef, ABILITY_RIPEN)) ? UQ_4_12(0.25) : UQ_4_12(0.5);
        }
    }
    return UQ_4_12(1.0);
}

#define DAMAGE_MULTIPLY_MODIFIER(modifier) do {                     \
    finalModifier = uq4_12_multiply_half_down(modifier, finalModifier); \
} while (0)

// Calculates the "other" modifier which accounts for held items, abilities,
// or very specific interactions of moves that are not handled in the basic
// damage calculation. It is implemented as described by bulbapedia:
// https://bulbapedia.bulbagarden.net/wiki/Damage#Generation_V_onward
// Please Note: Fixed Point Multiplication is not associative.
// The order of operations is relevant.
static inline uq4_12_t GetOtherModifiers(struct BattleContext *ctx)
{
    uq4_12_t finalModifier = UQ_4_12(1.0);
    enum BattlerId battlerDefPartner = BATTLE_PARTNER(ctx->battlerDef);
    u32 unmodifiedAttackerSpeed = gBattleMons[ctx->battlerAtk].speed;
    u32 unmodifiedDefenderSpeed = gBattleMons[ctx->battlerDef].speed;

    //TODO: Behemoth Blade, Behemoth Bash, Dynamax Cannon (Dynamax)
    DAMAGE_MULTIPLY_MODIFIER(GetMinimizeModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetUndergroundModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetDiveModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetAirborneModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetScreensModifier(ctx));
    DAMAGE_MULTIPLY_MODIFIER(GetCollisionCourseElectroDriftModifier(ctx->move, ctx->typeEffectivenessModifier));
    if (gBattleStruct->nullSpaceProtectedHit[ctx->battlerDef])
        DAMAGE_MULTIPLY_MODIFIER(UQ_4_12(0.5));

    if (unmodifiedAttackerSpeed >= unmodifiedDefenderSpeed)
    {
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerAbilitiesModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier, ctx->isCrit));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderAbilitiesModifier(ctx));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerAbilitiesModifier(battlerDefPartner));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerItemsModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderItemsModifier(ctx));
    }
    else
    {
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderAbilitiesModifier(ctx));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerAbilitiesModifier(battlerDefPartner));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerAbilitiesModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier, ctx->isCrit));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderItemsModifier(ctx));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerItemsModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier));
    }
    return finalModifier;
}

#undef DAMAGE_ACCUMULATE_MULTIPLIER

#define DAMAGE_APPLY_MODIFIER(modifier) do {               \
    dmg = uq4_12_multiply_by_int_half_down(modifier, dmg); \
} while (0)

static inline s32 DoMoveDamageCalcVars(struct BattleContext *ctx)
{
    s32 dmg;
    u32 unmodifiedBasePower;
    u32 userFinalAttack;
    u32 targetFinalDefense;

    if (ctx->fixedBasePower)
    {
        gBattleMovePower = ctx->fixedBasePower;
        unmodifiedBasePower = ctx->fixedBasePower;
    }
    else
        gBattleMovePower = CalcMoveBasePowerAfterModifiers(ctx, &unmodifiedBasePower);

    if (BattlerHasTrait(ctx->battlerDef, ABILITY_COLOSSAL)
     && IsCustomAbilityDirectDamagingMove(ctx->move)
     && unmodifiedBasePower <= 44)
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ABILITY_COLOSSAL);
        gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        return 0;
    }

    userFinalAttack = CalcAttackStat(ctx);
    targetFinalDefense = CalcDefenseStat(ctx);

    dmg = CalculateBaseDamage(gBattleMovePower, userFinalAttack, gBattleMons[ctx->battlerAtk].level, targetFinalDefense);
    DAMAGE_APPLY_MODIFIER(GetTargetDamageModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetParentalBondModifier(ctx->battlerAtk));
    DAMAGE_APPLY_MODIFIER(GetWeatherDamageModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetFieldDamageModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetCriticalModifier(ctx->isCrit));
    DAMAGE_APPLY_MODIFIER(GetGlaiveRushModifier(ctx->battlerDef));

    if (ctx->randomFactor)
    {
        dmg *= DMG_ROLL_PERCENT_HI - RandomUniform(RNG_DAMAGE_MODIFIER, 0, DMG_ROLL_PERCENT_HI - DMG_ROLL_PERCENT_LO);
        dmg /= 100;
    }
    else // Apply rest of modifiers in the ai function
    {
        if (dmg == 0)
            dmg = 1;
        return dmg;
    }

    dmg = ApplyModifiersAfterDmgRoll(ctx, dmg);

    if (dmg == 0)
        dmg = 1;

    return dmg;
}

s32 ApplyModifiersAfterDmgRoll(struct BattleContext *ctx, s32 dmg)
{
    if (GetActiveGimmick(ctx->battlerAtk) == GIMMICK_TERA)
        DAMAGE_APPLY_MODIFIER(GetTeraMultiplier(ctx));
    else
        DAMAGE_APPLY_MODIFIER(GetSameTypeAttackBonusModifier(ctx));
    DAMAGE_APPLY_MODIFIER(ctx->typeEffectivenessModifier);
    DAMAGE_APPLY_MODIFIER(GetBurnOrFrostBiteModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetZMaxMoveAgainstProtectionModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetOtherModifiers(ctx));

    return dmg;
}

s32 DoFixedDamageMoveCalc(struct BattleContext *ctx)
{
    s32 dmg = INT32_MAX;
    s32 randDamage;

    switch (GetMoveEffect(ctx->move))
    {
    case EFFECT_LEVEL_DAMAGE:
        dmg = gBattleMons[ctx->battlerAtk].level;
        if (ctx->move == MOVE_NIGHT_SHADE && (ctx->weather & B_WEATHER_TWILIGHT) && HasWeatherEffect())
            dmg *= 2;
        break;
    case EFFECT_PSYWAVE:
        if (B_PSYWAVE_DMG >= GEN_5)
        {
            randDamage = Random() % 101;
            dmg = gBattleMons[ctx->battlerAtk].level * (randDamage + 50) / 100;
        }
        else if (B_PSYWAVE_DMG >= GEN_3)
        {
            randDamage = Random() % 11;
            dmg = gBattleMons[ctx->battlerAtk].level * ((randDamage * 10) + 50) / 100;
        }
        else
        {
            dmg = Random() % ((gBattleMons[ctx->battlerAtk].level + (gBattleMons[ctx->battlerAtk].level / 2)) + 1);
        }
        break;
    case EFFECT_FIXED_HP_DAMAGE:
        dmg = GetMoveFixedHPDamage(ctx->move);
        break;
    case EFFECT_FIXED_PERCENT_DAMAGE:
        dmg = GetNonDynamaxHP(ctx->battlerDef) * GetMoveDamagePercentage(ctx->move) / 100;
        break;
    case EFFECT_FINAL_GAMBIT:
        dmg = GetNonDynamaxHP(ctx->battlerAtk);
        break;
    case EFFECT_BEAT_UP:
        if (GetConfig(B_BEAT_UP) < GEN_5)
            dmg = CalcBeatUpDamage(ctx);
        break;
    case EFFECT_REFLECT_DAMAGE:
        if (!ctx->aiCalc)
        {
            u32 percentMultiplier = GetMoveReflectDamage_DamagePercent(ctx->move);
            enum DamageCategory reflectCategory = GetReflectDamageMoveDamageCategory(ctx->battlerAtk, ctx->move);
            s32 baseDamage;

            if (reflectCategory == DAMAGE_CATEGORY_PHYSICAL)
                baseDamage = gProtectStructs[ctx->battlerAtk].physicalDmg;
            else
                baseDamage = gProtectStructs[ctx->battlerAtk].specialDmg;

            dmg = (baseDamage - 1) * percentMultiplier / 100;
        }
        break;
    case EFFECT_ENDEAVOR:
        if (GetNonDynamaxHP(ctx->battlerDef) <= gBattleMons[ctx->battlerAtk].hp)
        {
            dmg = 0;
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        }
        else
        {
            dmg = GetNonDynamaxHP(ctx->battlerDef) - gBattleMons[ctx->battlerAtk].hp;
        }
        break;
    case EFFECT_OHKO:
        dmg = gBattleMons[ctx->battlerDef].hp;
        break;
    default:
        break;
    }

    if (dmg == INT32_MAX)
        return dmg;

    gBattleStruct->moveResultFlags[ctx->battlerDef] &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE);
    gSpecialStatuses[ctx->battlerDef].criticalHit = FALSE;

    if (dmg == 0)
        dmg = 1;

    return dmg;
}

static inline s32 DoMoveDamageCalc(struct BattleContext *ctx)
{
    if (ctx->typeEffectivenessModifier == UQ_4_12(0.0))
        return 0;

    s32 dmg = DoFixedDamageMoveCalc(ctx);
    if (dmg != INT32_MAX)
        return dmg;

    return DoMoveDamageCalcVars(ctx);
}

static inline s32 DoFutureSightAttackDamageCalcVars(struct BattleContext *ctx)
{
    s32 dmg;
    u32 userFinalAttack;
    u32 targetFinalDefense;
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum Type moveType = ctx->moveType;

    struct Pokemon *party = GetBattlerParty(battlerAtk);
    struct Pokemon *partyMon = &party[gBattleStruct->futureSight[battlerDef].partyIndex];
    u32 partyMonLevel = GetMonData(partyMon, MON_DATA_LEVEL);
    u32 partyMonSpecies = GetMonData(partyMon, MON_DATA_SPECIES);
    gBattleMovePower = GetMovePower(move);

    if (IsBattleMovePhysical(move))
        userFinalAttack = GetMonData(partyMon, MON_DATA_ATK);
    else
        userFinalAttack = GetMonData(partyMon, MON_DATA_SPATK);

    targetFinalDefense = CalcDefenseStat(ctx);
    dmg = CalculateBaseDamage(gBattleMovePower, userFinalAttack, partyMonLevel, targetFinalDefense);

    DAMAGE_APPLY_MODIFIER(GetCriticalModifier(ctx->isCrit));

    if (ctx->randomFactor)
    {
        dmg *= DMG_ROLL_PERCENT_HI - RandomUniform(RNG_DAMAGE_MODIFIER, 0, DMG_ROLL_PERCENT_HI - DMG_ROLL_PERCENT_LO);
        dmg /= 100;
    }

    // Same type attack bonus
    if (GetSpeciesType(partyMonSpecies, 0) == moveType || GetSpeciesType(partyMonSpecies, 1) == moveType)
        DAMAGE_APPLY_MODIFIER(UQ_4_12(1.5));
    else
        DAMAGE_APPLY_MODIFIER(UQ_4_12(1.0));
    DAMAGE_APPLY_MODIFIER(ctx->typeEffectivenessModifier);

    if (dmg == 0)
        dmg = 1;

    return dmg;
}

static inline s32 DoFutureSightAttackDamageCalc(struct BattleContext *ctx)
{
    if (ctx->typeEffectivenessModifier == UQ_4_12(0.0))
        return 0;

    return DoFutureSightAttackDamageCalcVars(ctx);
}

bool32 IsFutureSightAttackerInParty(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    if (GetMoveEffect(move) != EFFECT_FUTURE_SIGHT)
        return FALSE;

    struct Pokemon *party = GetBattlerParty(battlerAtk);
    if (IsDoubleBattle())
    {
        return &party[gBattleStruct->futureSight[battlerDef].partyIndex] != &party[gBattlerPartyIndexes[battlerAtk]]
            && &party[gBattleStruct->futureSight[battlerDef].partyIndex] != &party[gBattlerPartyIndexes[BATTLE_PARTNER(battlerAtk)]];
    }

    return &party[gBattleStruct->futureSight[battlerDef].partyIndex] != &party[gBattlerPartyIndexes[battlerAtk]];
}

#undef DAMAGE_APPLY_MODIFIER

// The chance is 1/N for each stage.
static const u32 sGen7CriticalHitOdds[] = {24,  8,  2,  1,   1}; // 1/X
static const u32 sGen6CriticalHitOdds[] = {16,  8,  2,  1,   1}; // 1/X
static const u32 sCriticalHitOdds[]     = {16,  8,  4,  3,   2}; // 1/X, Gens 3,4,5
static const u32 sGen2CriticalHitOdds[] = {17, 32, 64, 85, 128}; // X/256

static inline u32 GetCriticalHitOdds(u32 critChance)
{
    if (GetConfig(B_CRIT_CHANCE) >= GEN_7)
        return sGen7CriticalHitOdds[critChance];
    if (GetConfig(B_CRIT_CHANCE) == GEN_6)
        return sGen6CriticalHitOdds[critChance];
    if (GetConfig(B_CRIT_CHANCE) == GEN_2)
        return sGen2CriticalHitOdds[critChance];

    return sCriticalHitOdds[critChance];
}

static inline u32 IsBattlerLeekAffected(enum BattlerId battler, enum Item item)
{
    if (GetBattlerItemHoldEffect(battler, item) == HOLD_EFFECT_LEEK)
    {
        return GET_BASE_SPECIES_ID(gBattleMons[battler].species) == SPECIES_FARFETCHD
            || gBattleMons[battler].species == SPECIES_SIRFETCHD;
    }
    return FALSE;
}

static inline u32 GetHoldEffectCritChanceIncrease(enum BattlerId battler)
{
    u32 critStageIncrease = 0;
    u32 i, item;
    bool32 firstScope = TRUE, firstPunch = TRUE, firstLeek = TRUE;
    
    for (i = 0; i < MAX_MON_ITEMS; i++)
    {
        item = GetSlotHeldItem(battler, i, TRUE);
        
        if (GetBattlerItemHoldEffect(battler, item) == HOLD_EFFECT_SCOPE_LENS && (firstScope || GetConfig(B_ALLOW_HELD_DUPES)))
        {
            firstScope = FALSE;
            critStageIncrease += 1;
        }
        if (GetBattlerItemHoldEffect(battler, item) == HOLD_EFFECT_LUCKY_PUNCH && (firstPunch || GetConfig(B_ALLOW_HELD_DUPES))
            && gBattleMons[battler].species == SPECIES_CHANSEY)
        {
            firstPunch = FALSE;
            critStageIncrease += 2;
        }
        if (IsBattlerLeekAffected(battler, item) && (firstLeek || GetConfig(B_ALLOW_HELD_DUPES)))
        {
            firstLeek = FALSE;
            critStageIncrease += 2;
        }
    }

    return critStageIncrease;
}

s32 CalcCritChanceStage(struct BattleContext *ctx)
{
    s32 critChance = 0;
    enum Ability abilityDef = ABILITY_NONE;

    if (gSideStatuses[GetBattlerSide(ctx->battlerDef)] & SIDE_STATUS_LUCKY_CHANT)
    {
        critChance = CRITICAL_HIT_BLOCKED;
    }
    else if (gBattleMons[ctx->battlerAtk].volatiles.laserFocus
          || MoveAlwaysCrits(ctx->move)
          || ((gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(ctx->battlerAtk, ABILITY_MERCILESS) : BattlerHasTrait(ctx->battlerAtk, ABILITY_MERCILESS))
          && gBattleMons[ctx->battlerDef].status1 & STATUS1_PSN_ANY))
    {
        critChance = CRITICAL_HIT_ALWAYS;
    }
    else
    {
        critChance  = (gBattleMons[ctx->battlerAtk].volatiles.focusEnergy != 0 ? 2 : 0)
                    + (gBattleMons[ctx->battlerAtk].volatiles.dragonCheer != 0 ? 1 : 0)
                    + GetMoveCriticalHitStage(ctx->move)
                    + GetHoldEffectCritChanceIncrease(ctx->battlerAtk)
                    + ((B_AFFECTION_MECHANICS == TRUE && GetBattlerAffectionHearts(ctx->battlerAtk) == AFFECTION_FIVE_HEARTS) ? 2 : 0)
                    + ((gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(ctx->battlerAtk, ABILITY_SUPER_LUCK) : BattlerHasTrait(ctx->battlerAtk, ABILITY_SUPER_LUCK)) ? 1 : 0)
                    + gBattleMons[ctx->battlerAtk].volatiles.bonusCritStages;
        if (critChance >= ARRAY_COUNT(sCriticalHitOdds))
            critChance = ARRAY_COUNT(sCriticalHitOdds) - 1;
    }

    if (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(ctx->battlerDef, ABILITY_BATTLE_ARMOR) : BattlerHasTrait(ctx->battlerDef, ABILITY_BATTLE_ARMOR))
        abilityDef = ABILITY_BATTLE_ARMOR;
    else if (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(ctx->battlerDef, ABILITY_SHELL_ARMOR) : BattlerHasTrait(ctx->battlerDef, ABILITY_SHELL_ARMOR))
        abilityDef = ABILITY_SHELL_ARMOR;

    if (critChance != CRITICAL_HIT_BLOCKED && abilityDef)
    {
        // Record ability only if move had 100% chance to get a crit
        if (ctx->updateFlags)
        {
            if (critChance == CRITICAL_HIT_ALWAYS)
                RecordAbilityBattle(ctx->battlerDef, abilityDef);
            else if (GetCriticalHitOdds(critChance) == 1)
                RecordAbilityBattle(ctx->battlerDef, abilityDef);
        }
        critChance = CRITICAL_HIT_BLOCKED;
    }

    return critChance;
}

// Bulbapedia: https://bulbapedia.bulbagarden.net/wiki/Critical_hit#Generation_I
// Crit chance = Threshold / 256, Threshold maximum of 255
// Threshold = Base Speed / 2
// High crit move = 8 * (Base Speed / 2)
// Focus Energy = 4 * (Base Speed / 2)
s32 CalcCritChanceStageGen1(struct BattleContext *ctx)
{
    s32 critChance = 0;
    enum Ability abilityDef = ABILITY_NONE;
    s32 moveCritStage = GetMoveCriticalHitStage(ctx->move);
    s32 bonusCritStage = gBattleMons[ctx->battlerAtk].volatiles.bonusCritStages; // G-Max Chi Strike
    u32 holdEffectCritStage = GetHoldEffectCritChanceIncrease(ctx->battlerAtk);
    u16 baseSpeed = GetSpeciesBaseSpeed(gBattleMons[ctx->battlerAtk].species);

    critChance = baseSpeed / 2;

    // Crit scaling
    if (moveCritStage > 0)
        critChance *= 8 * moveCritStage;

    if (bonusCritStage > 0)
        critChance *= bonusCritStage;

    if (gBattleMons[ctx->battlerAtk].volatiles.focusEnergy)
        critChance *= 4;
    else if (gBattleMons[ctx->battlerAtk].volatiles.dragonCheer)
        critChance *= 2;

    if (holdEffectCritStage > 0)
        critChance *= 4 * holdEffectCritStage;

    if (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(ctx->battlerAtk, ABILITY_SUPER_LUCK) : BattlerHasTrait(ctx->battlerAtk, ABILITY_SUPER_LUCK))
        critChance *= 4;

    if (critChance > 255)
        critChance = 255;

    if (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(ctx->battlerDef, ABILITY_BATTLE_ARMOR) : BattlerHasTrait(ctx->battlerDef, ABILITY_BATTLE_ARMOR))
        abilityDef = ABILITY_BATTLE_ARMOR;
    else if (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(ctx->battlerDef, ABILITY_SHELL_ARMOR) : BattlerHasTrait(ctx->battlerDef, ABILITY_SHELL_ARMOR))
        abilityDef = ABILITY_SHELL_ARMOR;

    if (abilityDef)
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, abilityDef);
        critChance = CRITICAL_HIT_BLOCKED;
    }
    else if (gBattleMons[ctx->battlerAtk].volatiles.laserFocus
          || MoveAlwaysCrits(ctx->move)
          || (BattlerHasTrait(ctx->battlerAtk, ABILITY_MERCILESS) && gBattleMons[ctx->battlerDef].status1 & STATUS1_PSN_ANY))
    {
        critChance = CRITICAL_HIT_ALWAYS;
    }

    return critChance;
}

static bool32 IsCriticalHit(struct BattleContext *ctx)
{

    if (gBattleTypeFlags & (BATTLE_TYPE_WALLY_TUTORIAL | BATTLE_TYPE_FIRST_BATTLE))
        return FALSE;
    if (ctx->isSelfInflicted)
        return FALSE;
    if (gSideStatuses[GetBattlerSide(ctx->battlerDef)] & SIDE_STATUS_LUCKY_CHANT)
        return FALSE;

    bool32 isCrit = FALSE;
    s32 critChance = 0;

    if (GetConfig(B_CRIT_CHANCE) == GEN_1)
        critChance = CalcCritChanceStageGen1(ctx);
    else
        critChance = CalcCritChanceStage(ctx);

    if (critChance == CRITICAL_HIT_BLOCKED)
        isCrit = FALSE;
    else if (critChance == CRITICAL_HIT_ALWAYS)
        isCrit = TRUE;
    else if (GetConfig(B_CRIT_CHANCE) == GEN_1)
        isCrit = RandomChance(RNG_CRITICAL_HIT, critChance, 256);
    else if (GetConfig(B_CRIT_CHANCE) == GEN_2)
        isCrit = RandomChance(RNG_CRITICAL_HIT, GetCriticalHitOdds(critChance), 256);
    else
        isCrit = RandomChance(RNG_CRITICAL_HIT, 1, GetCriticalHitOdds(critChance));

    // Counter for IF_CRITICAL_HITS_GE evolution condition.
    if (ctx->updateFlags
     && isCrit
     && IsOnPlayerSide(ctx->battlerAtk)
     && !(gBattleTypeFlags & BATTLE_TYPE_MULTI && GetBattlerPosition(ctx->battlerAtk) == B_POSITION_PLAYER_LEFT))
    {
        gPartyCriticalHits[gBattlerPartyIndexes[ctx->battlerAtk]]++;
        Achievement_IncrementCounter(ACH_COUNTER_CRITICAL_HITS, 1);
    }

    if (ctx->updateFlags)
        gSpecialStatuses[ctx->battlerDef].criticalHit = isCrit;
    return isCrit;
}

s32 GetAdjustedDamage(struct BattleContext *ctx, s32 damage)
{
    if (DoesSubstituteBlockMove(ctx->battlerAtk, ctx->battlerDef, ctx->move)
     || DoesDisguiseBlockMove(ctx->battlerDef, ctx->move)
     || DoesIceFaceBlockMove(ctx->battlerDef, ctx->move)
     || (BattlerHasTrait(ctx->battlerDef, ABILITY_AURA_SHIELD)
      && gBattleMons[ctx->battlerDef].volatiles.auraShieldState <= 1
      && !gBattleMons[ctx->battlerDef].volatiles.transformed
      && !IsBattleMoveStatus(ctx->move)))
        return damage; // No damage will be dealt

    if (BattlerHasTrait(ctx->battlerDef, ABILITY_AEGIS)
     && !gBattleStruct->aegisUsed[ctx->battlerDef]
     && IsCustomAbilityDirectDamagingMove(ctx->move)
     && damage > max(1, gBattleMons[ctx->battlerDef].maxHP / 4))
    {
        if (ctx->updateFlags)
        {
            RecordAbilityBattle(ctx->battlerDef, ABILITY_AEGIS);
            gBattleStruct->aegisUsed[ctx->battlerDef] = TRUE;
        }
        damage = max(1, gBattleMons[ctx->battlerDef].maxHP / 4);
    }

    if (gBattleMons[ctx->battlerDef].hp > damage)
        return damage;

    bool32 enduredHit = FALSE;
    u32 rand = Random() % 100;
    u32 affectionScore = GetBattlerAffectionHearts(ctx->battlerDef);
    u32 bandParam = 0;
    enum Item battlerItems[MAX_MON_ITEMS], item = ITEM_NONE;
    enum Ability enduredAbility = ABILITY_NONE;

    if (gBattleMons[ctx->battlerDef].volatiles.endured)
    {
        enduredHit = TRUE;
        if (ctx->updateFlags)
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_FOE_ENDURED;
    }

    if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD))
    {
        for (u32 i = 0; i < MAX_MON_ITEMS; i++)
        {
            item = GetSlotHeldItem(ctx->battlerDef, i, TRUE);

            if (GetBattlerItemHoldEffect(ctx->battlerDef, item) == HOLD_EFFECT_FOCUS_BAND && (bandParam == 0 || GetConfig(B_ALLOW_HELD_DUPES)))
                bandParam += (100 - bandParam) * GetItemHoldEffectParam(item) / 100;
        }
    }

    STORE_BATTLER_ITEMS(ctx->battlerDef);

    if (!enduredHit && rand < bandParam)
    {
        enduredHit = TRUE;
        if (ctx->updateFlags)
        {
            RecordItemEffectBattle(ctx->battlerDef, HOLD_EFFECT_FOCUS_BAND);
            gLastUsedItem = GetBattlerHeldItemWithEffect(ctx->battlerDef, HOLD_EFFECT_FOCUS_BAND, TRUE);
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_FOE_HUNG_ON;
        }
    }
    else if (!enduredHit
          && BattlerHasTrait(ctx->battlerDef, ABILITY_REBORN)
          && !(gBattleStruct->rebornUsed[GetBattlerSide(ctx->battlerDef)] & (1u << gBattlerPartyIndexes[ctx->battlerDef])))
    {
        enduredHit = TRUE;
        if (ctx->updateFlags)
        {
            gBattleStruct->rebornUsed[GetBattlerSide(ctx->battlerDef)] |= (1u << gBattlerPartyIndexes[ctx->battlerDef]);
            gLastUsedAbility = ABILITY_REBORN;
            PushTraitStack(ctx->battlerDef, gLastUsedAbility);
            RecordAbilityBattle(ctx->battlerDef, gLastUsedAbility);
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_STURDIED;
            gBattleMons[ctx->battlerDef].hp = GetNonDynamaxMaxHP(ctx->battlerDef);
        }
        return 0;
    }
    else if (!enduredHit
          && GetConfig(B_STURDY) >= GEN_5 && (BattlerHasTrait(ctx->battlerDef, ABILITY_STURDY) || BattlerHasTrait(ctx->battlerDef, ABILITY_STONE_FACE) || BattlerHasTrait(ctx->battlerDef, ABILITY_NINE_LIVES)) && IsBattlerAtMaxHp(ctx->battlerDef))
    {
        enduredHit = TRUE;
        if (BattlerHasTrait(ctx->battlerDef, ABILITY_STONE_FACE))
            enduredAbility = ABILITY_STONE_FACE;
        else if (BattlerHasTrait(ctx->battlerDef, ABILITY_NINE_LIVES))
            enduredAbility = ABILITY_NINE_LIVES;
        else
            enduredAbility = ABILITY_STURDY;
        if (ctx->updateFlags)
        {
            gLastUsedAbility = enduredAbility;
            PushTraitStack(ctx->battlerDef, enduredAbility);
            RecordAbilityBattle(ctx->battlerDef, enduredAbility);
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_STURDIED;
        }
    }
    else if (!enduredHit
          && !BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD) && SearchItemSlots(battlerItems, HOLD_EFFECT_FOCUS_SASH) && IsBattlerAtMaxHp(ctx->battlerDef))
    {
        enduredHit = TRUE;
        if (ctx->updateFlags)
        {
            RecordItemEffectBattle(ctx->battlerDef, HOLD_EFFECT_FOCUS_SASH);
            gLastUsedItem = GetBattlerHeldItemWithEffect(ctx->battlerDef, HOLD_EFFECT_FOCUS_SASH, TRUE);
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_FOE_HUNG_ON;
        }
    }
    else if (!enduredHit
          && B_AFFECTION_MECHANICS == TRUE && IsOnPlayerSide(ctx->battlerDef) && affectionScore >= AFFECTION_THREE_HEARTS)
    {
        if ((affectionScore == AFFECTION_FIVE_HEARTS && rand < 20)
            || (affectionScore == AFFECTION_FOUR_HEARTS && rand < 15)
            || (affectionScore == AFFECTION_THREE_HEARTS && rand < 10))
        {
            enduredHit = TRUE;
            if (ctx->updateFlags)
                gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_FOE_ENDURED_AFFECTION;
        }
    }

    if (enduredHit)
    {
        damage = gBattleMons[ctx->battlerDef].hp - 1; // Reduce damage to 1 hp.
        if (enduredAbility == ABILITY_STONE_FACE)
            damage = gBattleMons[ctx->battlerDef].hp - max(1, GetNonDynamaxMaxHP(ctx->battlerDef) / 4);
        if (ctx->updateFlags)
            gProtectStructs[ctx->battlerDef].assuranceDoubled = TRUE;
    }
    else if (GetMoveEffect(ctx->move) == EFFECT_FALSE_SWIPE)
    {
        damage = gBattleMons[ctx->battlerDef].hp - 1;
    }

    return damage;
}

s32 CalculateMoveDamage(struct BattleContext *ctx)
{
    s32 damage = 0;

    ctx->typeEffectivenessModifier = CalcTypeEffectivenessMultiplier(ctx);
    ctx->isCrit = IsCriticalHit(ctx);

    if (IsFutureSightAttackerInParty(ctx->battlerAtk, ctx->battlerDef, ctx->move))
        damage = DoFutureSightAttackDamageCalc(ctx);
    else
        damage = DoMoveDamageCalc(ctx);

    return GetAdjustedDamage(ctx, damage);
}

// for AI so that typeEffectivenessModifier, weather, abilities and holdEffects are calculated only once
s32 CalculateMoveDamageVars(struct BattleContext *ctx)
{
    return DoMoveDamageCalcVars(ctx);
}

static uq4_12_t GetValkyrieTypeModifier(enum Type moveType)
{
    switch (moveType)
    {
    case TYPE_NORMAL:
    case TYPE_FLYING:
    case TYPE_ROCK:
    case TYPE_BUG:
    case TYPE_STEEL:
    case TYPE_GRASS:
    case TYPE_PSYCHIC:
    case TYPE_ICE:
    case TYPE_DRAGON:
    case TYPE_FAIRY:
        return UQ_4_12(0.5);
    case TYPE_POISON:
        return UQ_4_12(0.0);
    default:
        return UQ_4_12(1.0);
    }
}

static uq4_12_t GetRawTypeModifierAgainstBattler(enum Type moveType, enum BattlerId battlerDef)
{
    uq4_12_t modifier = UQ_4_12(1.0);
    enum Type types[3];

    GetBattlerTypes(battlerDef, FALSE, types);
    modifier = uq4_12_multiply(modifier, GetTypeModifier(moveType, types[0]));
    if (types[1] != types[0])
        modifier = uq4_12_multiply(modifier, GetTypeModifier(moveType, types[1]));
    if (types[2] != TYPE_MYSTERY && types[2] != types[1] && types[2] != types[0])
        modifier = uq4_12_multiply(modifier, GetTypeModifier(moveType, types[2]));
    if (BattlerHasTrait(battlerDef, ABILITY_VALKYRIE))
        modifier = uq4_12_multiply(modifier, GetValkyrieTypeModifier(moveType));

    return modifier;
}

static void TryTransmuteMoveType(struct BattleContext *ctx)
{
    enum Type candidates[NUMBER_OF_MON_TYPES];
    u32 candidateCount = 0;

    if (!ctx->randomFactor
     || ctx->isAnticipation
     || gAiLogicData->aiCalcInProgress
     || GetBattlerPartyState(ctx->battlerDef)->transmuteUsed
     || !BattlerHasTrait(ctx->battlerDef, ABILITY_TRANSMUTE)
     || !IsCustomAbilityDirectDamagingMove(ctx->move)
     || ctx->move == MOVE_STRUGGLE)
        return;

    GetBattlerPartyState(ctx->battlerDef)->transmuteUsed = TRUE;
    for (enum Type type = TYPE_NORMAL; type < NUMBER_OF_MON_TYPES; type++)
    {
        if (type == TYPE_MYSTERY || type == TYPE_STELLAR)
            continue;
        if (GetRawTypeModifierAgainstBattler(type, ctx->battlerDef) <= UQ_4_12(0.5))
            candidates[candidateCount++] = type;
    }

    if (candidateCount == 0)
        return;

    ctx->moveType = candidates[RandomUniform(RNG_TRANSMUTE, 0, candidateCount - 1)];
    RecordAbilityBattle(ctx->battlerDef, ABILITY_TRANSMUTE);
}

static inline void MulByTypeEffectiveness(struct BattleContext *ctx, uq4_12_t *modifier, enum Type defType)
{
    uq4_12_t mod = GetTypeModifier(ctx->moveType, defType);
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(ctx->battlerAtk);

    if (mod == UQ_4_12(0.0) && BattlerHasHeldItemEffect(ctx->battlerDef, HOLD_EFFECT_RING_TARGET, TRUE))
    {
        mod = UQ_4_12(1.0);
        if (ctx->updateFlags)
            RecordItemEffectBattle(ctx->battlerDef, HOLD_EFFECT_RING_TARGET);
    }
    else if ((ctx->moveType == TYPE_FIGHTING || ctx->moveType == TYPE_NORMAL) && defType == TYPE_GHOST && gBattleMons[ctx->battlerDef].volatiles.foresight && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
    }
    else if ((ctx->moveType == TYPE_FIGHTING || ctx->moveType == TYPE_NORMAL) && defType == TYPE_GHOST
        && (SearchTraits(battlerTraits, ABILITY_SCRAPPY) || SearchTraits(battlerTraits, ABILITY_MINDS_EYE))
        && mod == UQ_4_12(0.0) && !ctx->isAnticipation) // Anticipation ignores Scrappy and Minds Eye
    {
        mod = UQ_4_12(1.0);
        if (SearchTraits(battlerTraits, ABILITY_SCRAPPY))
            RecordAbilityBattle(ctx->battlerAtk, ABILITY_SCRAPPY);
        else if (SearchTraits(battlerTraits, ABILITY_MINDS_EYE))
            RecordAbilityBattle(ctx->battlerAtk, ABILITY_MINDS_EYE);
    }

    if (ctx->moveType == TYPE_PSYCHIC && defType == TYPE_DARK && gBattleMons[ctx->battlerDef].volatiles.miracleEye && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);
    if (GetMoveEffect(ctx->move) == EFFECT_SUPER_EFFECTIVE_ON_ARG && defType == GetMoveArgType(ctx->move) && !ctx->isAnticipation)
        mod = UQ_4_12(2.0);
    if (ctx->weather & B_WEATHER_TWILIGHT && ctx->moveType == TYPE_DARK && defType == TYPE_FAIRY && !ctx->isAnticipation)
        mod = UQ_4_12(2.0);
    if (ctx->moveType == TYPE_GROUND && defType == TYPE_FLYING && IsBattlerGrounded(ctx->battlerDef) && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);
    if (ctx->moveType == TYPE_STELLAR && GetActiveGimmick(ctx->battlerDef) == GIMMICK_TERA)
        mod = UQ_4_12(2.0);

    // B_WEATHER_STRONG_WINDS weakens Super Effective moves against Flying-type Pokémon
    if (ctx->weather & B_WEATHER_STRONG_WINDS && !ctx->isAnticipation)
    {
        if (defType == TYPE_FLYING && mod >= UQ_4_12(2.0))
            mod = UQ_4_12(1.0);
    }

    if (ctx->invertDefenderTypeMatchups)
    {
        switch (mod)
        {
        case UQ_4_12(0.5):
            mod = UQ_4_12(2.0);
            if (ctx->updateFlags)
                RecordAbilityBattle(ctx->battlerDef, ABILITY_INVERSION);
            break;
        case UQ_4_12(2.0):
            mod = UQ_4_12(0.5);
            if (ctx->updateFlags)
                RecordAbilityBattle(ctx->battlerDef, ABILITY_INVERSION);
            break;
        }
    }

    if (gSpecialStatuses[ctx->battlerDef].distortedTypeMatchups || (mod > UQ_4_12(0.0) && ShouldTeraShellDistortTypeMatchups(ctx->move, ctx->battlerDef)))
    {
        PushTraitStack(gBattlerTarget, ABILITY_TERA_SHELL);
        mod = UQ_4_12(0.5);
        if (ctx->updateFlags)
        {
            RecordAbilityBattle(ctx->battlerDef, ABILITY_TERA_SHELL);
            gSpecialStatuses[ctx->battlerDef].distortedTypeMatchups = TRUE;
            gSpecialStatuses[ctx->battlerDef].teraShellAbilityDone = TRUE;
        }
    }

    if (mod == UQ_4_12(0.0)
     && SearchTraits(battlerTraits, ABILITY_COSMIC_FORM)
     && IsCustomAbilityDirectDamagingMove(ctx->move)
     && !ctx->isAnticipation)
    {
        mod = UQ_4_12(1.0);
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerAtk, ABILITY_COSMIC_FORM);
    }

    *modifier = uq4_12_multiply(*modifier, mod);
}

static inline void TryNoticeIllusionInTypeEffectiveness(enum Move move, enum Type moveType, enum BattlerId battlerAtk, enum BattlerId battlerDef, uq4_12_t resultingModifier, u32 illusionSpecies)
{
    // Check if the type effectiveness would've been different if the pokemon really had the types as the disguise.
    uq4_12_t presumedModifier = UQ_4_12(1.0);

    struct BattleContext ctx = {0};
    ctx.battlerAtk = battlerAtk;
    ctx.battlerDef = battlerDef;
    ctx.move = ctx.chosenMove = move;
    ctx.moveType = moveType;
    ctx.updateFlags = FALSE;

    MulByTypeEffectiveness(&ctx, &presumedModifier, GetSpeciesType(illusionSpecies, 0));
    if (GetSpeciesType(illusionSpecies, 1) != GetSpeciesType(illusionSpecies, 0))
        MulByTypeEffectiveness(&ctx, &presumedModifier, GetSpeciesType(illusionSpecies, 1));

    if (presumedModifier != resultingModifier)
        RecordAbilityBattle(ctx.battlerDef, ABILITY_ILLUSION);
}

void UpdateMoveResultFlags(uq4_12_t modifier, u16 *resultFlags)
{
    if (modifier == UQ_4_12(0.0))
    {
        *resultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        *resultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE);
        gBattleStruct->blunderPolicy = FALSE; // Don't activate if missed
    }
    else if (modifier == UQ_4_12(1.0))
    {
        *resultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else if (modifier > UQ_4_12(1.0))
    {
        *resultFlags |= MOVE_RESULT_SUPER_EFFECTIVE;
        *resultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else //if (modifier < UQ_4_12(1.0))
    {
        *resultFlags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
        *resultFlags &= ~(MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
}

static inline uq4_12_t CalcTypeEffectivenessMultiplierInternal(struct BattleContext *ctx, uq4_12_t modifier)
{
    u32 illusionSpecies;
    enum Type types[3];
    GetBattlerTypes(ctx->battlerDef, FALSE, types);
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(ctx->battlerDef);
    enum Ability levitatingAbility = ABILITY_NONE;

    if (SearchTraits(battlerTraits, ABILITY_LEVITATE))
        levitatingAbility = ABILITY_LEVITATE;
    else if (SearchTraits(battlerTraits, ABILITY_EELEVATE))
        levitatingAbility = ABILITY_EELEVATE;
    else if (SearchTraits(battlerTraits, ABILITY_ALLSEEING_IDOL))
        levitatingAbility = ABILITY_ALLSEEING_IDOL;

    ctx->invertDefenderTypeMatchups = SearchTraits(battlerTraits, ABILITY_INVERSION) && !ctx->isAnticipation;

    MulByTypeEffectiveness(ctx, &modifier, types[0]);
    if (types[1] != types[0])
        MulByTypeEffectiveness(ctx, &modifier, types[1]);
    if (types[2] != TYPE_MYSTERY && types[2] != types[1] && types[2] != types[0])
        MulByTypeEffectiveness(ctx, &modifier, types[2]);
    if (SearchTraits(battlerTraits, ABILITY_VALKYRIE)
     && IsCustomAbilityDirectDamagingMove(ctx->move)
     && !ctx->isAnticipation)
    {
        uq4_12_t valkyrieModifier = GetValkyrieTypeModifier(ctx->moveType);
        if (valkyrieModifier == UQ_4_12(0.0) && BattlerHasTrait(ctx->battlerAtk, ABILITY_COSMIC_FORM))
        {
            valkyrieModifier = UQ_4_12(1.0);
            if (ctx->updateFlags)
                RecordAbilityBattle(ctx->battlerAtk, ABILITY_COSMIC_FORM);
        }
        else if (ctx->updateFlags)
        {
            RecordAbilityBattle(ctx->battlerDef, ABILITY_VALKYRIE);
        }
        modifier = uq4_12_multiply(modifier, valkyrieModifier);
    }
    if (ctx->moveType == TYPE_FIRE && gBattleMons[ctx->battlerDef].volatiles.tarShot)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));

    if (ctx->updateFlags && (illusionSpecies = GetIllusionMonSpecies(ctx->battlerDef)))
        TryNoticeIllusionInTypeEffectiveness(ctx->move, ctx->moveType, ctx->battlerAtk, ctx->battlerDef, modifier, illusionSpecies);

    bool32 isPresentHealing = GetMoveEffect(ctx->move) == EFFECT_PRESENT && gBattleStruct->presentBasePower == 0;
    bool32 ignoreTypeCalc = isPresentHealing || GetMoveCategory(ctx->move) == DAMAGE_CATEGORY_STATUS;
    if (ignoreTypeCalc && ctx->move != MOVE_THUNDER_WAVE)
    {
        modifier = UQ_4_12(1.0);
        if (B_GLARE_GHOST < GEN_4 && ctx->move == MOVE_GLARE && IS_BATTLER_OF_TYPE(ctx->battlerDef, TYPE_GHOST))
            modifier = UQ_4_12(0.0);
    }
    else if (ctx->moveType == TYPE_GROUND && !IsBattlerGroundedInverseCheck(ctx->battlerDef, INVERSE_BATTLE, ctx->isAnticipation, levitatingAbility != ABILITY_NONE, SearchTraits(battlerTraits, ABILITY_ALLSEEING_IDOL), FALSE)
     && !MoveIgnoresTypeIfFlyingAndUngrounded(ctx->move)
     && !BattlerHasHeldItemEffect(ctx->battlerDef, HOLD_EFFECT_RING_TARGET, TRUE)
     && !MoveIgnoresTargetAbility(ctx->move) && (BattlerHasHeldItemEffect(ctx->battlerDef, HOLD_EFFECT_ABILITY_SHIELD, TRUE) || !HasMoldBreakerTypeAbility(ctx->battlerAtk)))
    {
        if (BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD) && BattlerHasHeldItemEffect(ctx->battlerDef, HOLD_EFFECT_AIR_BALLOON, TRUE))
            return modifier;
        modifier = UQ_4_12(0.0);
        if (ctx->updateFlags && levitatingAbility != ABILITY_NONE)
        {
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastUsedAbility = levitatingAbility;
            ctx->abilityBlocked = TRUE;
            PushTraitStack(ctx->battlerDef, levitatingAbility);
            RecordAbilityBattle(ctx->battlerDef, levitatingAbility);
        }
        else if (!BattlerHasTrait(ctx->battlerAtk, ABILITY_OVERLOAD) && BattlerHasHeldItemEffect(ctx->battlerDef, HOLD_EFFECT_AIR_BALLOON, TRUE))
        {
            ctx->airBalloonBlocked = TRUE;
        }
    }
    else if (MoveHasNoEffectOnSameType(ctx->move) && IS_BATTLER_OF_TYPE(ctx->battlerDef, GetMoveType(ctx->move)))
    {
        modifier = UQ_4_12(0.0);
    }

    enum BattlerId spacetimeRiftOwner = GetSameSidePalkiaDialgaRiftOwner(ctx->battlerDef);

    if (spacetimeRiftOwner < gBattlersCount
     && SameSidePalkiaDialgaRiftActive(ctx->battlerDef)
     && (IsDialgaSpecies(gBattleMons[ctx->battlerDef].species) || IsPalkiaSpecies(gBattleMons[ctx->battlerDef].species))
     && IsSpreadMove(GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move))
     && IsCustomAbilityDirectDamagingMove(ctx->move)
     && !ctx->isAnticipation)
    {
        modifier = UQ_4_12(0.0);
        if (ctx->updateFlags)
            RecordAbilityBattle(spacetimeRiftOwner, ABILITY_SPACETIME_RIFT);
    }

    // Thousand Arrows ignores type modifiers for flying mons
    if (MoveIgnoresTypeIfFlyingAndUngrounded(ctx->move)
     && !IsBattlerGrounded(ctx->battlerDef)
     && IS_BATTLER_OF_TYPE(ctx->battlerDef, TYPE_FLYING))
    {
        modifier = UQ_4_12(1.0);
    }

    // Iron Ball ignores type modifiers for flying-type mons if it is the only source of grounding
    if (GetConfig(B_IRON_BALL) >= GEN_5
        && ctx->moveType == TYPE_GROUND
        && BattlerHasHeldItemEffect(ctx->battlerDef, HOLD_EFFECT_IRON_BALL, TRUE)
        && IS_BATTLER_OF_TYPE(ctx->battlerDef, TYPE_FLYING)
        && !IsBattlerGroundedInverseCheck(ctx->battlerDef, NOT_INVERSE_BATTLE, FALSE, BattlerHasTrait(ctx->battlerDef, ABILITY_LEVITATE) || BattlerHasTrait(ctx->battlerDef, ABILITY_EELEVATE) || BattlerHasTrait(ctx->battlerDef, ABILITY_ALLSEEING_IDOL), BattlerHasTrait(ctx->battlerDef, ABILITY_ALLSEEING_IDOL), TRUE) // We want to ignore Iron Ball so skip item check // We want to ignore Iron Ball so skip item check
        && !FlagGet(B_FLAG_INVERSE_BATTLE))
    {
        modifier = UQ_4_12(1.0);
    }

    if (((SearchTraits(battlerTraits, ABILITY_WONDER_GUARD) && modifier <= UQ_4_12(1.0) && !isPresentHealing)
        || (SearchTraits(battlerTraits, ABILITY_TELEPATHY) && ctx->battlerDef == BATTLE_PARTNER(ctx->battlerAtk)))
        && GetMovePower(ctx->move) != 0)
    {
        modifier = UQ_4_12(0.0);
        ctx->abilityBlocked = TRUE;
        if (ctx->updateFlags)
        {
            if(SearchTraits(battlerTraits, ABILITY_WONDER_GUARD))
                gLastUsedAbility = ABILITY_WONDER_GUARD;
            else if(SearchTraits(battlerTraits, ABILITY_TELEPATHY))
                gLastUsedAbility = ABILITY_TELEPATHY;
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_MISSED;
            PushTraitStack(ctx->battlerDef, gLastUsedAbility);
            RecordAbilityBattle(ctx->battlerDef, gLastUsedAbility);
        }
    }

    if (ctx->updateFlags)
        TryInitializeFirstSTABMoveTrainerSlide(ctx->battlerDef, ctx->battlerAtk, ctx->moveType);

    return modifier;
}

uq4_12_t CalcTypeEffectivenessMultiplier(struct BattleContext *ctx)
{
    uq4_12_t modifier = UQ_4_12(1.0);

    TryTransmuteMoveType(ctx);

    if (ctx->move != MOVE_STRUGGLE && ctx->moveType != TYPE_MYSTERY)
    {
        modifier = CalcTypeEffectivenessMultiplierInternal(ctx, modifier);
        if (GetMoveEffect(ctx->move) == EFFECT_TWO_TYPED_MOVE && !ctx->isAnticipation)
        {
            ctx->moveType = GetMoveArgType(ctx->move);
            modifier = CalcTypeEffectivenessMultiplierInternal(ctx, modifier);
        }
    }

    if (ctx->move != MOVE_STRUGGLE
     && ctx->moveType != TYPE_MYSTERY
     && !IsBattleMoveStatus(ctx->move)
     && GetMovePower(ctx->move) != 0)
    {
        if (BattlerHasTrait(ctx->battlerAtk, ABILITY_OMEGA))
        {
            modifier = UQ_4_12(2.0);
            if (ctx->updateFlags)
            {
                gBattleStruct->moveResultFlags[ctx->battlerDef] &= ~(MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
                RecordAbilityBattle(ctx->battlerAtk, ABILITY_OMEGA);
            }
        }
        else if (BattlerHasTrait(ctx->battlerDef, ABILITY_OMEGA))
        {
            modifier = UQ_4_12(0.5);
            if (ctx->updateFlags)
            {
                gBattleStruct->moveResultFlags[ctx->battlerDef] &= ~(MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
                RecordAbilityBattle(ctx->battlerDef, ABILITY_OMEGA);
            }
        }
    }

    if (ctx->updateFlags)
        UpdateMoveResultFlags(modifier, &gBattleStruct->moveResultFlags[ctx->battlerDef]);
    return modifier;
}

uq4_12_t CalcVisualTypeEffectivenessMultiplier(struct BattleContext *ctx)
{
    u32 illusionSpecies = GetIllusionMonSpecies(ctx->battlerDef);
    u32 actualSpecies = gBattleMons[ctx->battlerDef].species;
    enum Type actualTypes[3];
    uq4_12_t modifier;

    // Public type changes (such as Soak, Roost, or Terastallization) take
    // precedence over the disguise. Otherwise, calculate against the species
    // the player can actually see so the move-selection UI does not identify
    // Illusion before a move is used.
    if (illusionSpecies == SPECIES_NONE
     || GetActiveGimmick(ctx->battlerDef) == GIMMICK_TERA
     || gBattleMons[ctx->battlerDef].types[0] != GetSpeciesType(actualSpecies, 0)
     || gBattleMons[ctx->battlerDef].types[1] != GetSpeciesType(actualSpecies, 1)
     || gBattleMons[ctx->battlerDef].types[2] != TYPE_MYSTERY
     || gBattleMons[ctx->battlerDef].volatiles.roostActive)
        return CalcTypeEffectivenessMultiplier(ctx);

    // Reuse the normal calculation so special moves and public field effects
    // retain their usual UI behavior, but substitute the visible types for the
    // duration of the calculation.
    memcpy(actualTypes, gBattleMons[ctx->battlerDef].types, sizeof(actualTypes));
    gBattleMons[ctx->battlerDef].types[0] = GetSpeciesType(illusionSpecies, 0);
    gBattleMons[ctx->battlerDef].types[1] = GetSpeciesType(illusionSpecies, 1);
    gBattleMons[ctx->battlerDef].types[2] = TYPE_MYSTERY;
    modifier = CalcTypeEffectivenessMultiplier(ctx);
    memcpy(gBattleMons[ctx->battlerDef].types, actualTypes, sizeof(actualTypes));

    return modifier;
}

uq4_12_t CalcPartyMonTypeEffectivenessMultiplier(enum Move move, u16 speciesDef, struct Pokemon *mon)
{
    uq4_12_t modifier = UQ_4_12(1.0);
    enum Type moveType = GetBattleMoveType(move);

    if (move != MOVE_STRUGGLE && moveType != TYPE_MYSTERY)
    {
        struct BattleContext ctx = {0};
        ctx.move = ctx.chosenMove = move;
        ctx.moveType = moveType;
        ctx.updateFlags = FALSE;

        MulByTypeEffectiveness(&ctx, &modifier, GetSpeciesType(speciesDef, 0));
        if (GetSpeciesType(speciesDef, 1) != GetSpeciesType(speciesDef, 0))
            MulByTypeEffectiveness(&ctx, &modifier, GetSpeciesType(speciesDef, 1));

        if (mon == 0) //catch for non Pokemon struct entries, only checks Ability
        {
            if (ctx.moveType == TYPE_GROUND
             && (MonHasTrait(mon, ABILITY_LEVITATE) || MonHasTrait(mon, ABILITY_EELEVATE) || MonHasTrait(mon, ABILITY_ALLSEEING_IDOL))
             && (!(gFieldStatuses & STATUS_FIELD_GRAVITY) || MonHasTrait(mon, ABILITY_ALLSEEING_IDOL)))
                modifier = UQ_4_12(0.0);
            if (MonHasTrait(mon, ABILITY_WONDER_GUARD) && modifier <= UQ_4_12(1.0) && GetMovePower(move) != 0)
                modifier = UQ_4_12(0.0);
        }
        else
        {
            if (ctx.moveType == TYPE_GROUND
             && (MonHasTrait(mon, ABILITY_LEVITATE) || MonHasTrait(mon, ABILITY_EELEVATE) || MonHasTrait(mon, ABILITY_ALLSEEING_IDOL))
             && (!(gFieldStatuses & STATUS_FIELD_GRAVITY) || MonHasTrait(mon, ABILITY_ALLSEEING_IDOL)))
                modifier = UQ_4_12(0.0);
            if (MonHasTrait(mon, ABILITY_WONDER_GUARD) && modifier <= UQ_4_12(1.0) && GetMovePower(move) != 0)
                modifier = UQ_4_12(0.0);
        }
    }

    return modifier;
}

static uq4_12_t GetInverseTypeMultiplier(uq4_12_t multiplier)
{
    switch (multiplier)
    {
    case UQ_4_12(0.0):
    case UQ_4_12(0.5):
        return UQ_4_12(2.0);
    case UQ_4_12(2.0):
        return UQ_4_12(0.5);
    case UQ_4_12(1.0):
    default:
        return UQ_4_12(1.0);
    }
}

uq4_12_t GetOverworldTypeEffectiveness(struct Pokemon *mon, enum Type moveType)
{
    uq4_12_t modifier = UQ_4_12(1.0);

    if (moveType == TYPE_MYSTERY)
        return modifier;


    struct BattleContext ctx = {0};
    ctx.move = ctx.chosenMove = MOVE_POUND;
    ctx.moveType = moveType;
    ctx.updateFlags = FALSE;

    u32 speciesDef = GetMonData(mon, MON_DATA_SPECIES);
    enum Type type1 = GetSpeciesType(speciesDef, 0);
    enum Type type2 = GetSpeciesType(speciesDef, 1);

    MulByTypeEffectiveness(&ctx, &modifier, type1);
    if (type2 != type1)
        MulByTypeEffectiveness(&ctx, &modifier, type2);

    if ((modifier <= UQ_4_12(1.0) && MonHasTrait(mon, ABILITY_WONDER_GUARD))
     || CanAbilityAbsorbMove(&ctx))
        modifier = UQ_4_12(0.0);

    return modifier;
}

uq4_12_t GetTypeModifier(enum Type atkType, enum Type defType)
{
    if (B_FLAG_INVERSE_BATTLE != 0 && FlagGet(B_FLAG_INVERSE_BATTLE))
        return GetInverseTypeMultiplier(gTypeEffectivenessTable[atkType][defType]);
    return gTypeEffectivenessTable[atkType][defType];
}

s32 GetStealthHazardDamageByTypesAndHP(enum TypeSideHazard hazardType, enum Type type1, enum Type type2, u32 maxHp)
{
    s32 dmg = 0;
    uq4_12_t modifier = UQ_4_12(1.0);

    modifier = uq4_12_multiply(modifier, GetTypeModifier((u8)hazardType, type1));
    if (type2 != type1)
        modifier = uq4_12_multiply(modifier, GetTypeModifier((u8)hazardType, type2));

    switch (modifier)
    {
    case UQ_4_12(0.0):
        dmg = 0;
        break;
    case UQ_4_12(0.25):
        dmg = maxHp / 32;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(0.5):
        dmg = maxHp / 16;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(1.0):
        dmg = maxHp / 8;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(2.0):
        dmg = maxHp / 4;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(4.0):
        dmg = maxHp / 2;
        if (dmg == 0)
            dmg = 1;
        break;
    }

    return dmg;
}

s32 GetStealthHazardDamage(enum TypeSideHazard hazardType, enum BattlerId battler)
{
    enum Type types[3];
    GetBattlerTypes(battler, FALSE, types);
    u32 maxHp = gBattleMons[battler].maxHP;

    return GetStealthHazardDamageByTypesAndHP(hazardType, types[0], types[1], maxHp);
}

bool32 IsPartnerMonFromSameTrainer(enum BattlerId battler)
{
    if (!IsOnPlayerSide(battler))
        return !(gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS);
    else
        return !(gBattleTypeFlags & BATTLE_TYPE_MULTI);
}

bool32 DoesSpeciesUseHoldItemToChangeForm(u16 species, u16 heldItemId)
{
    u32 i;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    if (heldItemId == ITEM_NONE)
        return FALSE;

    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        enum FormChanges method = formChanges[i].method;
        switch (method)
        {
        case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM:
        case FORM_CHANGE_BATTLE_PRIMAL_REVERSION:
        case FORM_CHANGE_BATTLE_ULTRA_BURST:
        case FORM_CHANGE_ITEM_HOLD:
        case FORM_CHANGE_BEGIN_BATTLE:
            if (formChanges[i].param1 == heldItemId)
                return TRUE;
            break;
        default:
            break;
        }
    }
    return FALSE;
}

bool32 CanMegaEvolve(enum BattlerId battler)
{
    enum BattlerPosition position = GetBattlerPosition(battler);

    // Check if Player has a Mega Ring.
    if (!TESTING
        && (position == B_POSITION_PLAYER_LEFT || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && position == B_POSITION_PLAYER_RIGHT))
        && !(gBattleTypeFlags & BATTLE_TYPE_FACTORY)
        && !CheckBagHasItem(ITEM_MEGA_RING, 1))
        return FALSE;

    // Check if Trainer has already Mega Evolved.
    if (HasTrainerUsedGimmick(battler, GIMMICK_MEGA))
        return FALSE;

    // Check if battler has another gimmick active.
    if (GetActiveGimmick(battler) != GIMMICK_NONE)
        return FALSE;

    // Check if battler is currently held by Sky Drop.
    if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_SKY_DROP)
        return FALSE;

    // Check if battler is holding a Z-Crystal.
    if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_Z_CRYSTAL, FALSE))
        return FALSE;

    // Check if there is an entry in the form change table for regular Mega Evolution and battler is holding Mega Stone.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM) != gBattleMons[battler].species)
        return TRUE;

    // Check if there is an entry in the form change table for Wish Mega Evolution.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE) != gBattleMons[battler].species)
        return TRUE;

    // No checks passed, the mon CAN'T mega evolve.
    return FALSE;
}

bool32 CanUltraBurst(enum BattlerId battler)
{
    enum BattlerPosition position = GetBattlerPosition(battler);

    // Check if Player has a Z-Ring
    if (!TESTING && (position == B_POSITION_PLAYER_LEFT
        || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && position == B_POSITION_PLAYER_RIGHT))
        && !CheckBagHasItem(ITEM_Z_POWER_RING, 1))
        return FALSE;

    // Check if Trainer has already Ultra Bursted.
    if (HasTrainerUsedGimmick(battler, GIMMICK_ULTRA_BURST))
        return FALSE;

    // Check if battler has another gimmick active.
    if (GetActiveGimmick(battler) != GIMMICK_NONE)
        return FALSE;

    // Check if mon is currently held by Sky Drop
    if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_SKY_DROP)
        return FALSE;

    // Check if there is an entry in the form change table for Ultra Burst and battler is holding a Z-Crystal.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_ULTRA_BURST) != gBattleMons[battler].species && GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_Z_CRYSTAL, FALSE))
        return TRUE;

    // No checks passed, the mon CAN'T ultra burst.
    return FALSE;
}

void ActivateMegaEvolution(enum BattlerId battler)
{
    gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_MEGA_STONE, FALSE);
    if (gLastUsedItem == ITEM_NONE && GET_BASE_SPECIES_ID(gBattleMons[battler].species) == SPECIES_OGERPON)
        gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_OGERPON_MASK, FALSE);

    SetActiveGimmick(battler, GIMMICK_MEGA);
    SetGimmickAsActivated(battler, GIMMICK_MEGA);

    if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE))
    {
        BattleScriptPushCursorAndCallback(BattleScript_WishMegaEvolution);
    }
    else
    {
        TryBattleFormChange(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM);
        BattleScriptPushCursorAndCallback(BattleScript_MegaEvolution);
    }
}

void ActivateUltraBurst(enum BattlerId battler)
{
    gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_Z_CRYSTAL, FALSE);
    SetActiveGimmick(battler, GIMMICK_ULTRA_BURST);
    SetGimmickAsActivated(battler, GIMMICK_ULTRA_BURST);
    TryBattleFormChange(battler, FORM_CHANGE_BATTLE_ULTRA_BURST);
    BattleScriptPushCursorAndCallback(BattleScript_UltraBurst);
}

bool32 IsBattlerMegaEvolved(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Mega Evolution.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isMegaEvolution);
}

bool32 IsBattlerPrimalReverted(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Primal Revesion.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isPrimalReversion);
}

bool32 IsBattlerUltraBursted(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Ultra Burst.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isUltraBurst);
}

bool32 IsBattlerInTeraForm(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as a true Tera Form.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isTeraForm);
}

u32 GetBattleFormChangeTargetSpecies(enum BattlerId battler, enum FormChanges method)
{
    u32 i;
    u32 species = gBattleMons[battler].species;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battler);

    if (formChanges == NULL)
        return species;

    struct FormChangeContext ctx =
    {
        .method = method,
        .currentSpecies = gBattleMons[battler].species,
        .status = gBattleMons[battler].status1,
        .gmaxFactor = GetMonData(GetBattlerMon(battler), MON_DATA_GIGANTAMAX_FACTOR),
        .hp = gBattleMons[battler].hp,
        .maxHP = gBattleMons[battler].maxHP,
        .teraType = GetBattlerTeraType(battler),
        .level = gBattleMons[battler].level,
    };

    for (i = 0; i < MAX_MON_MOVES; i++)
        ctx.moves[i] = gBattleMons[battler].moves[i];
    for (i = 0; i < MAX_MON_ITEMS; i++)
        ctx.heldItems[i] = gBattleMons[battler].items[i];
    for (i = 0; i < MAX_MON_TRAITS; i++)
        ctx.traits[i] = battlerTraits[i];

    return GetFormChangeTargetSpecies_Internal(ctx);
}

static bool32 CanBattlerFormChange(enum BattlerId battler, enum FormChanges method)
{
    // Can't change form if transformed.
    if (gBattleMons[battler].volatiles.transformed
        && GetConfig(B_TRANSFORM_FORM_CHANGES) >= GEN_5)
        return FALSE;

    switch (method)
    {
    case FORM_CHANGE_END_BATTLE:
        if (IsBattlerPrimalReverted(battler))
            return TRUE;
        // Fallthrough
    case FORM_CHANGE_FAINT:
        if (IsBattlerMegaEvolved(battler) || IsBattlerUltraBursted(battler) || IsBattlerInTeraForm(battler) || IsGigantamaxed(battler))
            return TRUE;
        break;
    case FORM_CHANGE_BATTLE_SWITCH_OUT:
        if (IsGigantamaxed(battler))
            return TRUE;
        else if (GetActiveGimmick(battler) == GIMMICK_TERA && DoesSpeciesHaveFormChangeMethod(gBattleMons[battler].species, FORM_CHANGE_BATTLE_TURN_END))
            return FALSE;
        break;
    case FORM_CHANGE_BATTLE_TURN_END:
        if (GetActiveGimmick(battler) == GIMMICK_TERA)
            return FALSE;
        break;
    default:
        break;
    }
    return DoesSpeciesHaveFormChangeMethod(gBattleMons[battler].species, method);
}

bool32 TryRevertPartyMonFormChange(u32 partyIndex)
{
     bool32 changedForm = FALSE;

    // Appeared in battle and didn't faint
    if (gBattleStruct->partyState[B_SIDE_PLAYER][partyIndex].sentOut && GetMonData(&gPlayerParty[partyIndex], MON_DATA_HP) != 0)
        changedForm = TryFormChange(&gPlayerParty[partyIndex], FORM_CHANGE_END_BATTLE_ENVIRONMENT);

    if (!changedForm)
        changedForm = TryFormChange(&gPlayerParty[partyIndex], FORM_CHANGE_END_BATTLE);

    // Clear original species field
    gBattleStruct->partyState[B_SIDE_PLAYER][partyIndex].changedSpecies = SPECIES_NONE;

    return changedForm;
}

bool32 TryBattleFormChange(enum BattlerId battler, enum FormChanges method)
{
    struct Pokemon *mon = GetBattlerMon(battler);

    if (!CanBattlerFormChange(battler, method))
        return FALSE;

    if(BattlerHasTrait(battler, ABILITY_STANCE_CHANGE))
        PushTraitStack(battler, ABILITY_STANCE_CHANGE);

    u32 currentSpecies = GetMonData(mon, MON_DATA_SPECIES);
    u32 targetSpecies = GetBattleFormChangeTargetSpecies(battler, method);

    struct PartyState *battlePartyState = GetBattlerPartyState(battler);
    // If the battle ends, and there's not a specified species to change back to,
    // use the species at the start of the battle.
    if (targetSpecies == SPECIES_NONE
        && battlePartyState != NULL && battlePartyState->changedSpecies != SPECIES_NONE
        // This is added to prevent FORM_CHANGE_END_BATTLE_ENVIRONMENT from omitting move changes
        // at the end of the battle, as it was being counting as a successful form change.
        && (method == FORM_CHANGE_END_BATTLE || method == FORM_CHANGE_FAINT))
    {
        targetSpecies = battlePartyState->changedSpecies;
    }

    assertf(targetSpecies != SPECIES_NONE, "form change target returned NONE. cur:%d, method:%d", currentSpecies, method)
    {
        return FALSE;
    }

    if (targetSpecies != currentSpecies)
    {
        // Saves the original species on the first form change.
        if (GetBattlerPartyState(battler)->changedSpecies == SPECIES_NONE)
            GetBattlerPartyState(battler)->changedSpecies = gBattleMons[battler].species;

        TryToSetBattleFormChangeMoves(mon, method, targetSpecies);
        SetMonData(mon, MON_DATA_SPECIES, &targetSpecies);
        gBattleMons[battler].species = targetSpecies;
        RecalcBattlerStats(battler, mon, method == FORM_CHANGE_BATTLE_GIGANTAMAX);
        return TRUE;
    }

    return FALSE;
}

bool32 DoBattlersShareType(enum BattlerId battler1, enum BattlerId battler2)
{
    s32 i;
    s32 j;
    enum Type types1[3], types2[3];
    GetBattlerTypes(battler1, FALSE, types1);
    GetBattlerTypes(battler2, FALSE, types2);

    for (i = 0; i < 3; i++)
    {
        if (types1[i] == TYPE_MYSTERY)
            continue;

        for (j = 0; j < 3; j++)
        {
            if (types2[j] == TYPE_MYSTERY)
                continue;
            if (types1[i] == types2[j])
                return TRUE;
        }
    }

    return FALSE;
}

bool32 CanBattlerGetOrLoseItem(enum BattlerId fromBattler, enum BattlerId battler, enum Item itemId)
{
    u32 fromSpecies = gBattleMons[fromBattler].species;
    u32 otherSpecies = gBattleMons[battler].species;

    enum HoldEffect holdEffect = GetItemHoldEffect(itemId); // Raw hold effect

    if (ItemIsMail(itemId))
        return FALSE;
    else if (itemId == ITEM_ENIGMA_BERRY_E_READER)
        return FALSE;
    else if (itemId != ITEM_NONE
          && GET_BASE_SPECIES_ID(fromSpecies) == SPECIES_ARCEUS
          && BattlerHasTrait(fromBattler, ABILITY_MULTITYPE)
          && BattlerHasHeldItem(fromBattler, itemId, FALSE))
        return FALSE;
    else if (DoesSpeciesUseHoldItemToChangeForm(fromSpecies, itemId))
        return FALSE;
    else if (holdEffect == HOLD_EFFECT_Z_CRYSTAL)
        return FALSE;
    else if (holdEffect == HOLD_EFFECT_BOOSTER_ENERGY
         && (gSpeciesInfo[fromSpecies].isParadox || gSpeciesInfo[otherSpecies].isParadox))
        return FALSE;
    else if (holdEffect == HOLD_EFFECT_OGERPON_MASK && GET_BASE_SPECIES_ID(fromSpecies) == SPECIES_OGERPON)
        return FALSE;
    else
        return TRUE;
}

u32 GetBattlerVisualSpecies(enum BattlerId battler)
{
    u32 illusionSpecies = GetIllusionMonSpecies(battler);
    if (illusionSpecies != SPECIES_NONE)
        return illusionSpecies;
    return gBattleMons[battler].species;
}

bool32 TryClearIllusion(enum BattlerId battler)
{
    if (gBattleStruct->illusion[battler].state != ILLUSION_ON)
        return FALSE;
    if (BattlerHasTrait(battler, ABILITY_ILLUSION) && IsBattlerAlive(battler))
        return FALSE;

    gBattleScripting.battler = battler;
    BattleScriptCall(BattleScript_IllusionOff);
    return TRUE;
}

struct Pokemon *GetIllusionMonPtr(enum BattlerId battler)
{
    if (gBattleStruct->illusion[battler].state == ILLUSION_NOT_SET)
        SetIllusionMon(GetBattlerMon(battler), battler);
    if (gBattleStruct->illusion[battler].state != ILLUSION_ON)
        return NULL;

    return gBattleStruct->illusion[battler].mon;
}

void ClearIllusionMon(enum BattlerId battler)
{
    memset(&gBattleStruct->illusion[battler], 0, sizeof(gBattleStruct->illusion[battler]));
}

u32 GetIllusionMonSpecies(enum BattlerId battler)
{
    struct Pokemon *illusionMon = GetIllusionMonPtr(battler);
    if (illusionMon != NULL)
        return GetMonData(illusionMon, MON_DATA_SPECIES);
    return SPECIES_NONE;
}

u32 GetIllusionMonPartyId(struct Pokemon *party, struct Pokemon *mon, struct Pokemon *partnerMon, enum BattlerId battler)
{
    s32 partyEnd=6;
    s32 partyStart=0;

    // Adjust party search range for Multibattles and Player vs two-trainers
    if ((GetBattlerSide(battler) == B_SIDE_PLAYER && (gBattleTypeFlags & BATTLE_TYPE_MULTI))
        || (GetBattlerSide(battler) == B_SIDE_OPPONENT && (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)))
        {
            if ((GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT) || (GetBattlerPosition(battler) == B_POSITION_OPPONENT_LEFT))
            {
                partyEnd = 3;
                partyStart = 0;
            }
            else
            {
                partyEnd = 6;
                partyStart = 3;
            }
        }

    // Find last alive non-egg pokemon.
    for (s32 id = partyEnd - 1; id >= partyStart; id--)
    {
        if (GetMonData(&party[id], MON_DATA_SANITY_HAS_SPECIES)
            && GetMonData(&party[id], MON_DATA_HP)
            && !GetMonData(&party[id], MON_DATA_IS_EGG))
        {
            u32 species = GetMonData(&party[id], MON_DATA_SPECIES);
            if (species == SPECIES_TERAPAGOS_STELLAR || (species >= SPECIES_OGERPON_TEAL_TERA && species <= SPECIES_OGERPON_CORNERSTONE_TERA))
                continue;
            if (&party[id] != mon && &party[id] != partnerMon)
                return id;
            else // If this pokemon or its partner is last in the party, ignore Illusion.
                return PARTY_SIZE;
        }
    }
    return PARTY_SIZE;
}

void SetIllusionMon(struct Pokemon *mon, enum BattlerId battler)
{
    struct Pokemon *party, *partnerMon;
    u32 id;

    gBattleStruct->illusion[battler].state = ILLUSION_OFF;
    if (!MonHasTrait(mon, ABILITY_ILLUSION))
        return;

    party = GetBattlerParty(battler);

    if (IsBattlerAlive(BATTLE_PARTNER(battler)))
        partnerMon = &party[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]];
    else
        partnerMon = mon;

    id = GetIllusionMonPartyId(party, mon, partnerMon, battler);
    if (id != PARTY_SIZE)
    {
        gBattleStruct->illusion[battler].state = ILLUSION_ON;
        gBattleStruct->illusion[battler].mon = &party[id];
    }
}

enum ImmunityHealStatusOutcome TryImmunityAbilityHealStatus(enum BattlerId battler)
{
    enum ImmunityHealStatusOutcome outcome = IMMUNITY_NO_EFFECT;
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS_IGNORE_MOLDBREAKER(battler);

    // Cures non-volatile status conditions before volitile and can only cure one at a time
    if (SearchTraits(battlerTraits, ABILITY_IMMUNITY)
     && gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON | STATUS1_TOXIC_COUNTER))
    {
        PushTraitStack(battler, ABILITY_IMMUNITY);
        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_PASTEL_VEIL)
     && gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON | STATUS1_TOXIC_COUNTER))
    {
        PushTraitStack(battler, ABILITY_PASTEL_VEIL);
        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_OWN_TEMPO)
     && gBattleMons[battler].volatiles.confusionTurns > 0)
    {
        PushTraitStack(battler, ABILITY_OWN_TEMPO);
        StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);
        outcome = IMMUNITY_CONFUSION_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_LIMBER)
     && gBattleMons[battler].status1 & STATUS1_PARALYSIS)
    {
        PushTraitStack(battler, ABILITY_LIMBER);
        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_INSOMNIA)
     && gBattleMons[battler].status1 & STATUS1_SLEEP)
    {
        TryDeactivateSleepClause(GetBattlerSide(battler), gBattlerPartyIndexes[battler]);
        gBattleMons[battler].volatiles.nightmare = FALSE;
        PushTraitStack(battler, ABILITY_INSOMNIA);
        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_VITAL_SPIRIT)
     && gBattleMons[battler].status1 & STATUS1_SLEEP)
    {
        TryDeactivateSleepClause(GetBattlerSide(battler), gBattlerPartyIndexes[battler]);
        gBattleMons[battler].volatiles.nightmare = FALSE;
        PushTraitStack(battler, ABILITY_VITAL_SPIRIT);
        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_WATER_VEIL)
     && gBattleMons[battler].status1 & STATUS1_BURN)
    {
        PushTraitStack(battler, ABILITY_WATER_VEIL);
        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_WATER_BUBBLE)
     && gBattleMons[battler].status1 & STATUS1_BURN)
    {
        PushTraitStack(battler, ABILITY_WATER_BUBBLE);
        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_THERMAL_EXCHANGE)
     && gBattleMons[battler].status1 & STATUS1_BURN)
    {
        PushTraitStack(battler, ABILITY_THERMAL_EXCHANGE);
        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_MAGMA_ARMOR)
     && gBattleMons[battler].status1 & STATUS1_ICY_ANY)
    {
        PushTraitStack(battler, ABILITY_MAGMA_ARMOR);
        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
        outcome = IMMUNITY_STATUS_CLEARED;
    }
    else if (SearchTraits(battlerTraits, ABILITY_OBLIVIOUS)
     && gBattleMons[battler].status1 & (STATUS1_FREEZE | STATUS1_FROSTBITE))
    {
        PushTraitStack(battler, ABILITY_OBLIVIOUS);
        if (gBattleMons[battler].volatiles.infatuation)
            outcome = IMMUNITY_INFATUATION_CLEARED;
        else if (GetConfig(B_OBLIVIOUS_TAUNT) >= GEN_6 && gBattleMons[battler].volatiles.tauntTimer != 0)
            outcome = IMMUNITY_TAUNT_CLEARED;
    }

    switch (outcome)
    {
    case IMMUNITY_STATUS_CLEARED:
        gBattleMons[battler].status1 = 0;
        BattleScriptCall(BattleScript_AbilityCuredStatus);
        break;
    case IMMUNITY_CONFUSION_CLEARED:
        RemoveConfusionStatus(battler);
        BattleScriptCall(BattleScript_AbilityCuredStatus);
        break;
    case IMMUNITY_INFATUATION_CLEARED:
        gBattleMons[battler].volatiles.infatuation = 0;
        BattleScriptCall(BattleScript_AbilityCuredStatus);
        break;
    case IMMUNITY_TAUNT_CLEARED:
        gBattleMons[battler].volatiles.tauntTimer = 0;
        BattleScriptCall(BattleScript_AbilityCuredStatus);
        break;
    case IMMUNITY_NO_EFFECT:
        return IMMUNITY_NO_EFFECT;
    }

    gBattleScripting.battler = gBattlerAbility = battler;
    if (outcome == IMMUNITY_STATUS_CLEARED)
    {
        BtlController_EmitSetMonData(battler, B_COMM_TO_CONTROLLER, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
        MarkBattlerForControllerExec(battler);
    }
    return outcome;
}

uq4_12_t GetBadgeBoostModifier(void)
{
    if (GetConfig(B_BADGE_BOOST) < GEN_3)
        return UQ_4_12(1.125);
    else
        return UQ_4_12(1.1);
}

bool32 ShouldGetStatBadgeBoost(u16 badgeFlag, enum BattlerId battler)
{
    if (GetConfig(B_BADGE_BOOST) <= GEN_3 && badgeFlag != 0)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_FRONTIER))
            return FALSE;
        else if (!IsOnPlayerSide(battler))
            return FALSE;
        else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && TRAINER_BATTLE_PARAM.opponentA == TRAINER_SECRET_BASE)
            return FALSE;
        else if (FlagGet(badgeFlag))
            return TRUE;
    }
    return FALSE;
}

static enum DamageCategory SwapMoveDamageCategory(enum Move move)
{
    if (GetMoveCategory(move) == DAMAGE_CATEGORY_PHYSICAL)
        return DAMAGE_CATEGORY_SPECIAL;
    return DAMAGE_CATEGORY_PHYSICAL;
}

/*
    The Global States gBattleStruct->categoryOverride and gBattleStruct->swapDamageCategory
    can be removed but a lot of function arguments (battlerAtk and battlerDef) have to be added for this, about 50+.
    This is potentially a good change because it is less likely to cause bugs in the future.
*/
enum DamageCategory GetBattleMoveCategory(enum Move move)
{
    if (gBattleStruct != NULL)
    {
        if (gBattleStruct->swapDamageCategory) // Photon Geyser, Shell Side Arm, Light That Burns the Sky, Tera Blast
            return SwapMoveDamageCategory(move);
        if (IsZMove(move) || IsMaxMove(move)) // TODO: Might be buggy depending on when this is called.
            return gBattleStruct->categoryOverride;
        if (IsBattleMoveStatus(move))
            return DAMAGE_CATEGORY_STATUS;
    }

    if (B_PHYSICAL_SPECIAL_SPLIT < GEN_4)
        return gTypesInfo[GetBattleMoveType(move)].damageCategory;

    return GetMoveCategory(move);
}

void SetDynamicMoveCategory(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_PHOTON_GEYSER:
        gBattleStruct->swapDamageCategory = (GetCategoryBasedOnStats(battlerAtk) == DAMAGE_CATEGORY_PHYSICAL);
        break;
    case EFFECT_SHELL_SIDE_ARM:
        if (gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] == DAMAGE_CATEGORY_PHYSICAL)
            gBattleStruct->swapDamageCategory = TRUE;
        break;
    case EFFECT_TERA_BLAST:
        if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA)
            gBattleStruct->swapDamageCategory = GetCategoryBasedOnStats(battlerAtk) == DAMAGE_CATEGORY_PHYSICAL;
        break;
    case EFFECT_TERA_STARSTORM:
        if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA && GET_BASE_SPECIES_ID(GetMonData(GetBattlerMon(battlerAtk), MON_DATA_SPECIES)) == SPECIES_TERAPAGOS)
            gBattleStruct->swapDamageCategory = GetCategoryBasedOnStats(battlerAtk) == DAMAGE_CATEGORY_PHYSICAL;
        break;
    default:
        gBattleStruct->swapDamageCategory = FALSE;
        break;
    }
}

static bool32 TryRemoveScreens(enum BattlerId battler)
{
    bool32 removed = FALSE;
    u32 battlerSide = GetBattlerSide(battler);
    u8 enemySide = GetBattlerSide(BATTLE_OPPOSITE(battler));

    // try to remove from battler's side
    if (gSideStatuses[battlerSide] & SIDE_STATUS_SCREEN_ANY)
    {
        gSideStatuses[battlerSide] &= ~SIDE_STATUS_SCREEN_ANY;
        removed = TRUE;
    }

    // try to remove from battler opponent's side
    if (gSideStatuses[enemySide] & SIDE_STATUS_SCREEN_ANY)
    {
        gSideStatuses[enemySide] &= ~SIDE_STATUS_SCREEN_ANY;
        removed = TRUE;
    }

    return removed;
}

// Photon Geyser, Light That Burns the Sky, Tera Blast
enum DamageCategory GetCategoryBasedOnStats(enum BattlerId battler)
{
    u32 attack = gBattleMons[battler].attack;
    u32 spAttack = gBattleMons[battler].spAttack;

    attack = attack * gStatStageRatios[gBattleMons[battler].statStages[STAT_ATK]][0];
    attack = attack / gStatStageRatios[gBattleMons[battler].statStages[STAT_ATK]][1];

    spAttack = spAttack * gStatStageRatios[gBattleMons[battler].statStages[STAT_SPATK]][0];
    spAttack = spAttack / gStatStageRatios[gBattleMons[battler].statStages[STAT_SPATK]][1];

    if (spAttack >= attack)
        return DAMAGE_CATEGORY_SPECIAL;
    else
        return DAMAGE_CATEGORY_PHYSICAL;
}

static u32 GetFlingPowerFromItemId(enum Item itemId)
{
    if (gItemsInfo[itemId].pocket == POCKET_TM_HM)
    {
        u32 power = GetMovePower(ItemIdToBattleMoveId(itemId));
        if (power > 1)
            return power;
        return 10; // Status moves and moves with variable power always return 10 power.
    }
    else
        return GetItemFlingPower(itemId);
}

bool32 CanFling(enum BattlerId battlerAtk)
{
    enum Item item = ITEM_NONE;

    for (int i = 0; i < MAX_MON_ITEMS; i++)
    {
        item = gBattleMons[battlerAtk].items[i];

        if (item != ITEM_NONE
        && !(GetConfig(B_KLUTZ_FLING_INTERACTION) >= GEN_5 && BattlerHasTrait(battlerAtk, ABILITY_KLUTZ))
        && !(gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
        && !(gBattleMons[battlerAtk].volatiles.embargo)
        && !(GetItemTMHMIndex(item) != 0 && GetItemImportance(item) == 1) // don't fling reusable TMs
        && !(GetFlingPowerFromItemId(item) == 0)
        && CanBattlerGetOrLoseItem(battlerAtk, battlerAtk, item)) // defender being a paradox mon doesn't matter
        {
            if (!gAiLogicData->aiCalcInProgress)
                gBattleStruct->flingItem = gLastUsedItem = item;
            return TRUE;
        }
    }

    return FALSE;
}

// Sort an array of battlers by speed
// Useful for effects like pickpocket, eject button, red card, dancer
void SortBattlersBySpeed(enum BattlerId *battlers, bool32 slowToFast)
{
    int i, j, currSpeed;
    enum BattlerId currBattler;
    u16 speeds[MAX_BATTLERS_COUNT] = {0};

    for (i = 0; i < gBattlersCount; i++)
    {
        enum BattlerId battler = battlers[i];
        speeds[i] = GetBattlerTotalSpeedStat(battler);
    }

    for (i = 1; i < gBattlersCount; i++)
    {
        currBattler = battlers[i];
        currSpeed = speeds[i];
        j = i - 1;

        if (slowToFast)
        {
            while (j >= 0 && speeds[j] > currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && speeds[j] < currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }

        battlers[j + 1] = currBattler;
        speeds[j + 1] = currSpeed;
    }
}

void TryRestoreHeldItemsForPartySlot(u32 partySlot)
{
    u32 j;
    u16 lostItem;
    bool32 restoreHeldBattleItems = GetConfig(B_RESTORE_HELD_BATTLE_ITEMS) >= GEN_9;
    bool32 returnNPCItems = GetConfig(B_RETURN_STOLEN_NPC_ITEMS) >= GEN_5 && gBattleTypeFlags & BATTLE_TYPE_TRAINER;

    // Check if held items should be restored after battle based on generation
    if (restoreHeldBattleItems || returnNPCItems)
    {
        for (j = 0; j < MAX_MON_ITEMS; j++)
        {
            if (restoreHeldBattleItems)
            {
                u16 consumedItem = gBattleStruct->partyState[B_SIDE_PLAYER][partySlot].consumedHeldItems[j];
                u16 originalItem = gBattleStruct->itemLost[B_SIDE_PLAYER][partySlot][j].originalItem;

                if (consumedItem != ITEM_NONE
                 && consumedItem == originalItem
                 && GetItemPocket(consumedItem) != POCKET_BERRIES)
                    SetMonData(&gPlayerParty[partySlot], MON_DATA_HELD_ITEM + j, &originalItem);
            }

            if (gBattleStruct->itemLost[B_SIDE_PLAYER][partySlot][j].stolen)
            {
                lostItem = gBattleStruct->itemLost[B_SIDE_PLAYER][partySlot][j].originalItem;

                // Check if the lost item is a berry and the mon is not holding it
                if (GetItemPocket(lostItem) == POCKET_BERRIES && GetMonData(&gPlayerParty[partySlot], MON_DATA_HELD_ITEM + j) != lostItem)
                    lostItem = ITEM_NONE;

                // Check if the lost item should be restored
                if ((lostItem != ITEM_NONE || returnNPCItems) && GetItemPocket(lostItem) != POCKET_BERRIES)
                    SetMonData(&gPlayerParty[partySlot], MON_DATA_HELD_ITEM + j, &lostItem);
            }
        }
    }
}

void TryRestoreHeldItems(void)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
        TryRestoreHeldItemsForPartySlot(i);
}

bool32 CanStealItem(enum BattlerId battlerStealing, enum BattlerId battlerItem, enum Item item)
{
    enum BattleSide stealerSide = GetBattlerSide(battlerStealing);

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
        return FALSE;

    // Check if the battler trying to steal should be able to
    if (stealerSide == B_SIDE_OPPONENT
        && !(gBattleTypeFlags &
             (BATTLE_TYPE_EREADER_TRAINER
              | BATTLE_TYPE_FRONTIER
              | BATTLE_TYPE_LINK
              | BATTLE_TYPE_RECORDED_LINK
              | BATTLE_TYPE_SECRET_BASE
              | (B_TRAINERS_KNOCK_OFF_ITEMS == TRUE ? BATTLE_TYPE_TRAINER : 0)
              )))
    {
        return FALSE;
    }
    else if (!(gBattleTypeFlags &
          (BATTLE_TYPE_EREADER_TRAINER
           | BATTLE_TYPE_FRONTIER
           | BATTLE_TYPE_LINK
           | BATTLE_TYPE_RECORDED_LINK
           | BATTLE_TYPE_SECRET_BASE))
        && GetBattlerPartyState(battlerStealing)->isKnockedOff)
    {
        return FALSE;
    }

    // It's supposed to pop before trying to steal but this also works
    // Now that the order is correct this is redundant. The question is whether Trick can steal it.
    if (GetItemHoldEffect(item) == HOLD_EFFECT_AIR_BALLOON)
        return FALSE;

    if (!CanBattlerGetOrLoseItem(battlerItem, battlerStealing, item)  // Battler with item cannot have it stolen
     || !CanBattlerGetOrLoseItem(battlerStealing, battlerItem, item)) // Stealer cannot take the item
        return FALSE;

    return TRUE;
}

void TrySaveExchangedItem(enum BattlerId battler, enum Item stolenItem, u8 slot)
{
    // Because BtlController_EmitSetMonData does SetMonData, we need to save the stolen item only if it matches the battler's original
    // So, if the player steals an item during battle and has it stolen from it, it will not end the battle with it (naturally)
    if (B_TRAINERS_KNOCK_OFF_ITEMS == FALSE)
        return;
    // If regular trainer battle and mon's original item matches what is being stolen, save it to be restored at end of battle
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER
      && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
      && IsOnPlayerSide(battler)
      && stolenItem == gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]][slot].originalItem)
        gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]][slot].stolen = TRUE;
}

bool32 IsBattlerAffectedByHazards(enum BattlerId battler, bool32 toxicSpikes)
{
    bool32 ret = TRUE;
    if (!IsBattlerAlive(battler))
    {
        ret = FALSE;
    }
    else if (toxicSpikes && BattlerHasHeldItemEffect(battler, HOLD_EFFECT_HEAVY_DUTY_BOOTS, TRUE) && !IS_BATTLER_OF_TYPE(battler, TYPE_POISON))
    {
        ret = FALSE;
        RecordItemEffectBattle(battler, HOLD_EFFECT_HEAVY_DUTY_BOOTS);
    }
    else if (BattlerHasHeldItemEffect(battler, HOLD_EFFECT_HEAVY_DUTY_BOOTS, TRUE))
    {
        ret = FALSE;
        RecordItemEffectBattle(battler, HOLD_EFFECT_HEAVY_DUTY_BOOTS);
    }
    return ret;
}

bool32 IsSheerForceAffected(enum Move move, u32 battler)
{
    return (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battler, ABILITY_SHEER_FORCE) : BattlerHasTrait(battler, ABILITY_SHEER_FORCE)) && MoveIsAffectedBySheerForce(move);
}

// This function is the body of "jumpifstat", but can be used dynamically in a function
bool32 CompareStat(enum BattlerId battler, enum Stat statId, u32 cmpTo, u32 cmpKind)
{
    bool32 ret = FALSE;
    u32 statValue = gBattleMons[battler].statStages[statId];

    // Because this command is used as a way of checking if a stat can be lowered/raised,
    // we need to do some modification at run-time.
    if (BattlerHasTrait(battler, ABILITY_CONTRARY))
    {
        if (cmpKind == CMP_GREATER_THAN)
            cmpKind = CMP_LESS_THAN;
        else if (cmpKind == CMP_LESS_THAN)
            cmpKind = CMP_GREATER_THAN;

        if (cmpTo == MIN_STAT_STAGE)
            cmpTo = MAX_STAT_STAGE;
        else if (cmpTo == MAX_STAT_STAGE)
            cmpTo = MIN_STAT_STAGE;
    }

    switch (cmpKind)
    {
    case CMP_EQUAL:
        if (statValue == cmpTo)
            ret = TRUE;
        break;
    case CMP_NOT_EQUAL:
        if (statValue != cmpTo)
            ret = TRUE;
        break;
    case CMP_GREATER_THAN:
        if (statValue > cmpTo)
            ret = TRUE;
        break;
    case CMP_LESS_THAN:
        if (statValue < cmpTo)
            ret = TRUE;
        break;
    case CMP_COMMON_BITS:
        if (statValue & cmpTo)
            ret = TRUE;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(statValue & cmpTo))
            ret = TRUE;
        break;
    }

    return ret;
}

bool32 CompareStatIgnoreContrary(enum BattlerId battler, enum Stat statId, u32 cmpTo, u32 cmpKind)
{
    bool32 ret = FALSE;
    u32 statValue = gBattleMons[battler].statStages[statId];

    // Because this command is used as a way of checking if a stat can be lowered/raised,
    // we need to do some modification at run-time.

    switch (cmpKind)
    {
    case CMP_EQUAL:
        if (statValue == cmpTo)
            ret = TRUE;
        break;
    case CMP_NOT_EQUAL:
        if (statValue != cmpTo)
            ret = TRUE;
        break;
    case CMP_GREATER_THAN:
        if (statValue > cmpTo)
            ret = TRUE;
        break;
    case CMP_LESS_THAN:
        if (statValue < cmpTo)
            ret = TRUE;
        break;
    case CMP_COMMON_BITS:
        if (statValue & cmpTo)
            ret = TRUE;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(statValue & cmpTo))
            ret = TRUE;
        break;
    }

    return ret;
}

bool32 BlocksPrankster(enum Move move, enum BattlerId battlerPrankster, enum BattlerId battlerDef, bool32 checkTarget)
{
    if (GetConfig(B_PRANKSTER_DARK_TYPES) < GEN_7)
        return FALSE;
    if (!gProtectStructs[battlerPrankster].pranksterElevated)
        return FALSE;
    if (IsBattlerAlly(battlerPrankster, battlerDef))
        return FALSE;
    if (checkTarget && GetBattlerMoveTargetType(battlerPrankster, move) == TARGET_DEPENDS)
        return FALSE;
    if (checkTarget && GetBattlerMoveTargetType(battlerPrankster, move) == TARGET_OPPONENTS_FIELD)
        return FALSE;
    if (!IS_BATTLER_OF_TYPE(battlerDef, TYPE_DARK))
        return FALSE;
    if (IsSemiInvulnerable(battlerDef, CHECK_ALL))
        return FALSE;

    return TRUE;
}

// Not enum BattlerId to allow using it with RandomUniformExcept
bool32 CantPickupItem(u32 _battler)
{
    enum BattlerId battler = _battler;
    bool8 hasUsedHeldItem = FALSE;
    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (GetBattlerPartyState(battler)->usedHeldItems[i]);
        {
            hasUsedHeldItem = TRUE;
            break;
        }
    }

    // Used by RandomUniformExcept() for RNG_PICKUP
    if (battler == gBattlerAttacker && (GetConfig(B_PICKUP_WILD) < GEN_9 || gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_LINK)))
        return TRUE;
    return !(IsBattlerAlive(battler) && hasUsedHeldItem && gBattleStruct->battlerState[battler].canPickupItem);
}

bool32 PickupHasValidTarget(enum BattlerId battler)
{
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (!CantPickupItem(i))
            return TRUE;
    }
    return FALSE;
}

u32 GetBattlerWeather(enum BattlerId battler, u32 weather)
{
    bool32 aiCalcInProgress = (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress);

    if (aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battler, ABILITY_MEGA_SOL) : BattlerHasTrait(battler, ABILITY_MEGA_SOL))
        return B_WEATHER_SUN_NORMAL;

    if (weather == B_WEATHER_NONE || !HasWeatherEffect())
        return B_WEATHER_NONE;

    if (weather & (B_WEATHER_SUN | B_WEATHER_RAIN))
    {
        bool32 utilityUmbrellaAffected = aiCalcInProgress
                                       ? Ai_BattlerHasHoldEffect(battler, HOLD_EFFECT_UTILITY_UMBRELLA, gAiLogicData)
                                       : BattlerHasHeldItemEffect(battler, HOLD_EFFECT_UTILITY_UMBRELLA, TRUE);

        if (utilityUmbrellaAffected)
            weather &= ~(B_WEATHER_SUN | B_WEATHER_RAIN);
    }

    return weather;
}

bool32 IsBattlerWeatherAffected(enum BattlerId battler, u32 weatherFlags)
{
    return (GetBattlerWeather(battler, gBattleWeather) & weatherFlags) != 0;
}

static u32 CanBattlerHitBothFoesInTerrain(enum BattlerId battler, enum Move move, enum BattleMoveEffects effect)
{
    return effect == EFFECT_TERRAIN_BOOST
        && GetMoveTerrainBoost_HitsBothFoes(move)
        && IsBattlerTerrainAffected(battler, gFieldStatuses, GetMoveTerrainBoost_Terrain(move));
}

enum MoveTarget GetBattlerMoveTargetType(enum BattlerId battler, enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    if (effect == EFFECT_CURSE && !IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return TARGET_USER;
    if (CanBattlerHitBothFoesInTerrain(battler, move, effect))
        return TARGET_BOTH;
    if (effect == EFFECT_TERA_STARSTORM && gBattleMons[battler].species == SPECIES_TERAPAGOS_STELLAR)
        return TARGET_BOTH;

    return GetMoveTarget(move);
}

bool32 CanTargetBattler(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    if (GetMoveEffect(move) == EFFECT_HIT_ENEMY_HEAL_ALLY
    &&  IsBattlerAlly(battlerAtk, battlerDef)
    &&  gBattleMons[battlerAtk].volatiles.healBlock)
        return FALSE;   // Pokémon affected by Heal Block cannot target allies with Pollen Puff
    if (IsBattlerAlly(battlerAtk, battlerDef) && (GetActiveGimmick(battlerAtk) == GIMMICK_DYNAMAX
                                               || IsGimmickSelected(battlerAtk, GIMMICK_DYNAMAX)))
        return FALSE;

    return TRUE;
}

u32 GetNextTarget(u32 moveTarget, bool32 excludeCurrent)
{
    enum BattlerId battler;
    for (battler = 0; battler < MAX_BATTLERS_COUNT; battler++)
    {
        if (battler == gBattlerAttacker || !IsBattlerAlive(battler))
            continue;

        if (!(excludeCurrent && battler == gBattlerTarget)
         && !gBattleStruct->battlerState[gBattlerAttacker].targetsDone[battler]
         && (!IsBattlerAlly(battler, gBattlerAttacker) || moveTarget == TARGET_FOES_AND_ALLY))
            break;
    }
    return battler;
}

void CopyMonLevelAndBaseStatsToBattleMon(enum BattlerId battler, struct Pokemon *mon)
{
    gBattleMons[battler].level = GetMonData(mon, MON_DATA_LEVEL);
    gBattleMons[battler].hp = GetMonData(mon, MON_DATA_HP);
    gBattleMons[battler].maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    gBattleMons[battler].attack = GetMonData(mon, MON_DATA_ATK);
    gBattleMons[battler].defense = GetMonData(mon, MON_DATA_DEF);
    gBattleMons[battler].speed = GetMonData(mon, MON_DATA_SPEED);
    gBattleMons[battler].spAttack = GetMonData(mon, MON_DATA_SPATK);
    gBattleMons[battler].spDefense = GetMonData(mon, MON_DATA_SPDEF);
}

void CopyMonAbilityAndTypesToBattleMon(enum BattlerId battler, struct Pokemon *mon)
{
    gBattleMons[battler].ability = GetMonAbility(mon);
    #if TESTING
    if (gTestRunnerEnabled)
    {
        u32 array = (!IsPartnerMonFromSameTrainer(battler)) ? battler : GetBattlerSide(battler);
        u32 partyIndex = gBattlerPartyIndexes[battler];
        if (TestRunner_Battle_GetForcedAbility(array, partyIndex))
            gBattleMons[battler].ability = TestRunner_Battle_GetForcedAbility(array, partyIndex);
    }
    #endif
    gBattleMons[battler].types[0] = GetSpeciesType(gBattleMons[battler].species, 0);
    gBattleMons[battler].types[1] = GetSpeciesType(gBattleMons[battler].species, 1);
    gBattleMons[battler].types[2] = TYPE_MYSTERY;
}

void RecalcBattlerStats(enum BattlerId battler, struct Pokemon *mon, bool32 isDynamaxing)
{
    u32 hp = GetMonData(mon, MON_DATA_HP);
    u32 oldMaxHp = GetMonData(mon, MON_DATA_MAX_HP);
    CalculateMonStats(mon);
    if (GetActiveGimmick(battler) == GIMMICK_DYNAMAX && gChosenActionByBattler[battler] != B_ACTION_SWITCH)
    {
        ApplyDynamaxHPMultiplier(mon);
        u32 newMaxHp = GetMonData(mon, MON_DATA_MAX_HP);
        if (!isDynamaxing)
        {
            if (newMaxHp > oldMaxHp) // restore hp gained from changing form, without this, dynamaxed form changes are calculated incorrectly
            {
                hp += (newMaxHp - oldMaxHp);
                SetMonData(mon, MON_DATA_HP, &hp);
            }
            else
            {
                SetMonData(mon, MON_DATA_HP, &hp);
            }
        }
    }
    CopyMonLevelAndBaseStatsToBattleMon(battler, mon);
    CopyMonAbilityAndTypesToBattleMon(battler, mon);
    ApplyBossStatMultiplierAfterRecalculation(battler);
}

void RemoveConfusionStatus(enum BattlerId battler)
{
    gBattleMons[battler].volatiles.confusionTurns = 0;
    gBattleMons[battler].volatiles.infiniteConfusion = FALSE;
}

u32 GetBattlerGender(enum BattlerId battler)
{
    return GetGenderFromSpeciesAndPersonality(gBattleMons[battler].species,
                                              gBattleMons[battler].personality);
}

bool32 AreBattlersOfOppositeGender(enum BattlerId battler1, enum BattlerId battler2)
{
    u32 gender1 = GetBattlerGender(battler1);
    u32 gender2 = GetBattlerGender(battler2);

    return (gender1 != MON_GENDERLESS && gender2 != MON_GENDERLESS && gender1 != gender2);
}

bool32 AreBattlersOfSameGender(enum BattlerId battler1, enum BattlerId battler2)
{
    u32 gender1 = GetBattlerGender(battler1);
    u32 gender2 = GetBattlerGender(battler2);

    return (gender1 != MON_GENDERLESS && gender2 != MON_GENDERLESS && gender1 == gender2);
}

u32 CalcSecondaryEffectChance(enum BattlerId battler, const struct AdditionalEffect *additionalEffect)
{
    bool8 hasSereneGrace = (BattlerHasTrait(battler, ABILITY_SERENE_GRACE));
    bool8 hasRainbow = (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_RAINBOW) != 0;
    u16 secondaryEffectChance = additionalEffect->chance;

    if (hasRainbow && hasSereneGrace && additionalEffect->moveEffect == MOVE_EFFECT_FLINCH)
        return secondaryEffectChance * 2;

    if (hasSereneGrace)
        secondaryEffectChance *= 2;
    if (hasRainbow && additionalEffect->moveEffect != MOVE_EFFECT_SECRET_POWER)
        secondaryEffectChance *= 2;

    return secondaryEffectChance;
}

bool32 MoveEffectIsGuaranteed(enum BattlerId battler, const struct AdditionalEffect *additionalEffect)
{
    return additionalEffect->chance == 0 || CalcSecondaryEffectChance(battler, additionalEffect) >= 100;
}

bool32 IsGen6ExpShareEnabled(void)
{
    if (I_EXP_SHARE_FLAG <= TEMP_FLAGS_END)
        return FALSE;

    return FlagGet(I_EXP_SHARE_FLAG);
}


bool32 MoveHasAdditionalEffect(enum Move move, enum MoveEffect moveEffect)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if (additionalEffect->moveEffect == moveEffect && additionalEffect->self == FALSE)
            return TRUE;
    }
    return FALSE;
}

bool32 MoveHasAdditionalEffectWithChance(enum Move move, enum MoveEffect moveEffect, u32 chance)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if (additionalEffect->moveEffect == moveEffect && additionalEffect->chance == chance)
            return TRUE;
    }
    return FALSE;
}

bool32 MoveHasAdditionalEffectSelf(enum Move move, enum MoveEffect moveEffect)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if (additionalEffect->moveEffect == moveEffect && additionalEffect->self == TRUE)
            return TRUE;
    }
    return FALSE;
}

bool32 IsMoveEffectRemoveSpeciesType(enum Move move, enum MoveEffect moveEffect, u32 argument)
{
    return (MoveHasAdditionalEffectSelf(move, moveEffect) && GetMoveArgType(move) == argument);
}

bool32 MoveHasChargeTurnAdditionalEffect(enum Move move)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        if (GetMoveAdditionalEffectById(move, i)->onChargeTurnOnly)
            return TRUE;
    }
    return FALSE;
}

bool32 MoveIsAffectedBySheerForce(enum Move move)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if ((additionalEffect->chance > 0) != additionalEffect->sheerForceOverride)
            return TRUE;
    }
    return FALSE;
}

bool32 CanMonParticipateInSkyBattle(struct Pokemon *mon)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES);

    bool32 hasLevitateAbility = (MonHasTrait(mon, ABILITY_LEVITATE) || MonHasTrait(mon, ABILITY_EELEVATE) || MonHasTrait(mon, ABILITY_ALLSEEING_IDOL));
    bool32 isFlyingType = GetSpeciesType(species, 0) == TYPE_FLYING || GetSpeciesType(species, 1) == TYPE_FLYING;
    bool32 monIsValidAndNotEgg = GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES) && !GetMonData(mon, MON_DATA_IS_EGG);

    if (monIsValidAndNotEgg)
    {
        if ((hasLevitateAbility || isFlyingType) && !gSpeciesInfo[species].isSkyBattleBanned)
            return TRUE;
    }
    return FALSE;
}

void GetBattlerTypes(enum BattlerId battler, bool32 ignoreTera, enum Type types[static 3])
{
    // Terastallization.
    bool32 isTera = GetActiveGimmick(battler) == GIMMICK_TERA;
    if (!ignoreTera && isTera)
    {
        enum Type teraType = GetBattlerTeraType(battler);
        if (teraType != TYPE_STELLAR)
        {
            types[0] = types[1] = types[2] = teraType;
            return;
        }
    }

    types[0] = gBattleMons[battler].types[0];
    types[1] = gBattleMons[battler].types[1];
    types[2] = gBattleMons[battler].types[2];

    // Roost.
    if (!isTera && gBattleMons[battler].volatiles.roostActive)
    {
        if (types[0] == TYPE_FLYING && types[1] == TYPE_FLYING)
            types[0] = types[1] = B_ROOST_PURE_FLYING >= GEN_5 ? TYPE_NORMAL : TYPE_MYSTERY;
        else if (types[0] == TYPE_FLYING)
            types[0] = TYPE_MYSTERY;
        else if (types[1] == TYPE_FLYING)
            types[1] = TYPE_MYSTERY;
    }

    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battler);
    for (u32 i = 0; i < MAX_MON_TRAITS; i++)
    {
        enum Type addedType = GetAdditionalTypeAbilityType(battlerTraits[i]);
        if (addedType == TYPE_MYSTERY || types[0] == addedType || types[1] == addedType || types[2] == addedType)
            continue;
        types[2] = addedType;
        break;
    }
}

enum Type GetBattlerType(enum BattlerId battler, u32 typeIndex, bool32 ignoreTera)
{
    enum Type types[3];
    GetBattlerTypes(battler, ignoreTera, types);
    return types[typeIndex];
}

void RemoveBattlerType(enum BattlerId battler, enum Type type)
{
    u32 i;
    if (GetActiveGimmick(battler) == GIMMICK_TERA) // don't remove type if Terastallized
        return;
    for (i = 0; i < 3; i++)
    {
        if (*(u8 *)(&gBattleMons[battler].types[0] + i) == type)
            *(u8 *)(&gBattleMons[battler].types[0] + i) = TYPE_MYSTERY;
    }
}

void SetShellSideArmCategory(void)
{
    enum BattlerId battlerAtk, battlerDef;
    u32 attackerAtkStat;
    u32 targetDefStat;
    u32 attackerSpAtkStat;
    u32 targetSpDefStat;
    u8 statStage;
    u32 physical;
    u32 special;
    u32 power = GetMovePower(MOVE_SHELL_SIDE_ARM);

    // Don't run this check for Safari Battles. Because player's stats are zeroed out, this performs division by zero which previously would crash on certain emulators in Safari Zone.
    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return;

    for (battlerAtk = 0; battlerAtk < gBattlersCount; battlerAtk++)
    {
        attackerAtkStat = gBattleMons[battlerAtk].attack;
        statStage = gBattleMons[battlerAtk].statStages[STAT_ATK];
        attackerAtkStat *= gStatStageRatios[statStage][0];
        attackerAtkStat /= gStatStageRatios[statStage][1];

        attackerSpAtkStat = gBattleMons[battlerAtk].spAttack;
        statStage = gBattleMons[battlerAtk].statStages[STAT_SPATK];
        attackerSpAtkStat *= gStatStageRatios[statStage][0];
        attackerSpAtkStat /= gStatStageRatios[statStage][1];

        for (battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
        {
            if (battlerAtk == battlerDef)
                continue;

            targetDefStat = gBattleMons[battlerDef].defense;
            statStage = gBattleMons[battlerDef].statStages[STAT_DEF];
            targetDefStat *= gStatStageRatios[statStage][0];
            targetDefStat /= gStatStageRatios[statStage][1];
            if (targetDefStat == 0)
                targetDefStat = 1;

            physical = ((((2 * gBattleMons[battlerAtk].level / 5 + 2) * power * attackerAtkStat) / targetDefStat) / 50);

            targetSpDefStat = gBattleMons[battlerDef].spDefense;
            statStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
            targetSpDefStat *= gStatStageRatios[statStage][0];
            targetSpDefStat /= gStatStageRatios[statStage][1];
            if (targetSpDefStat == 0)
                targetSpDefStat = 1;

            special = ((((2 * gBattleMons[battlerAtk].level / 5 + 2) * power * attackerSpAtkStat) / targetSpDefStat) / 50);

            if ((physical > special) || (physical == special && RandomPercentage(RNG_SHELL_SIDE_ARM, 50)))
                gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] = DAMAGE_CATEGORY_PHYSICAL;
            else
                gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] = DAMAGE_CATEGORY_SPECIAL;
        }
    }
}

bool32 CanTargetPartner(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    return (IsDoubleBattle()
         && IsBattlerAlive(BATTLE_PARTNER(battlerDef))
         && battlerDef != BATTLE_PARTNER(battlerAtk));
}

bool32 IsBattlerUnaffectedByMove(enum BattlerId battler)
{
    return gBattleStruct->moveResultFlags[battler] & MOVE_RESULT_NO_EFFECT;
}

enum Type GetBattleMoveType(enum Move move)
{
    if (gMain.inBattle)
    {
        if (gBattleStruct->dynamicMoveType)
            return gBattleStruct->dynamicMoveType & DYNAMIC_TYPE_MASK;

        enum BattleMoveEffects effect = GetMoveEffect(move);
        if (B_UPDATED_MOVE_TYPES < GEN_5
         && (effect == EFFECT_BEAT_UP || effect == EFFECT_FUTURE_SIGHT))
          return TYPE_MYSTERY;
    }
    return GetMoveType(move);
}

void TryActivateSleepClause(enum BattlerId battler, u32 indexInParty)
{
    if (gBattleStruct->battlerState[battler].sleepClauseEffectExempt)
    {
        gBattleStruct->battlerState[battler].sleepClauseEffectExempt = FALSE;
        return;
    }

    if (IsSleepClauseEnabled())
        gBattleStruct->monCausingSleepClause[GetBattlerSide(battler)] = indexInParty;
}

void TryDeactivateSleepClause(enum BattleSide battlerSide, u32 indexInParty)
{
    // If the pokemon on the given side at the given index in the party is the one causing Sleep Clause to be active,
    // set monCausingSleepClause[battlerSide] = PARTY_SIZE, which means Sleep Clause is not active for the given side
    if (IsSleepClauseEnabled() && gBattleStruct->monCausingSleepClause[battlerSide] == indexInParty)
        gBattleStruct->monCausingSleepClause[battlerSide] = PARTY_SIZE;
}

bool32 IsSleepClauseActiveForSide(enum BattleSide battlerSide)
{
    // If monCausingSleepClause[battlerSide] == PARTY_SIZE, Sleep Clause is not active for the given side.
    // If monCausingSleepClause[battlerSide] < PARTY_SIZE, it means it is storing the index of the mon that is causing Sleep Clause to be active,
    // from which it follows that Sleep Clause is active.
    return (IsSleepClauseEnabled() && (gBattleStruct->monCausingSleepClause[battlerSide] < PARTY_SIZE));
}

bool32 IsSleepClauseEnabled(void)
{
    if (B_SLEEP_CLAUSE)
        return TRUE;
    if (FlagGet(B_FLAG_SLEEP_CLAUSE))
        return TRUE;
    return FALSE;
}

void ClearDamageCalcResults(void)
{
    for (enum BattlerId battler = 0; battler < MAX_BATTLERS_COUNT; battler++)
    {
        gBattleStruct->moveDamage[battler] = 0;
        gBattleStruct->moveResultFlags[battler] = 0;
        gBattleStruct->passiveHpUpdate[battler] = 0;
        gSpecialStatuses[battler].criticalHit = FALSE;
        gSpecialStatuses[battler].damagedByAttack = FALSE;
    }

    gBattleStruct->doneDoublesSpreadHit = FALSE;
    gBattleStruct->calculatedDamageDone = FALSE;
    gBattleStruct->calculatedSpreadMoveAccuracy = FALSE;
    gBattleStruct->printedStrongWindsWeakenedAttack = FALSE;
    gBattleStruct->numSpreadTargets = 0;
    gBattleStruct->unableToUseMove = FALSE;
    gBattleStruct->attackAnimPlayed = FALSE;
    gBattleStruct->preAttackEffectHappened = FALSE;
    gBattleScripting.savedDmg = 0;
    if (gCurrentMove != MOVE_NONE)
        gBattleStruct->moldBreakerActive = HasMoldBreakerTypeAbility(gBattlerAttacker) || MoveIgnoresTargetAbility(gCurrentMove);
    else
        gBattleStruct->moldBreakerActive = FALSE;
}

bool32 DoesDestinyBondFail(enum BattlerId battler)
{
    return GetConfig(B_DESTINY_BOND_FAIL) >= GEN_7 && gBattleMons[battler].volatiles.destinyBond;
}

// This check has always to be the last in a condtion statement because of the recording of AI data.
bool32 IsMoveEffectBlockedByTarget(void)
{
    if (BattlerHasTrait(gBattlerTarget, ABILITY_SHIELD_DUST))
    {
        RecordAbilityBattle(gBattlerTarget, ABILITY_SHIELD_DUST);
        return TRUE;
    }
    else if (BattlerHasHeldItemEffect(gBattlerTarget, HOLD_EFFECT_COVERT_CLOAK, TRUE))
    {
        RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_COVERT_CLOAK);
        return TRUE;
    }

    return FALSE;
}

bool32 SetTargetToNextPursuiter(enum BattlerId battlerDef)
{
    u32 i;
    for (i = gCurrentTurnActionNumber + 1; i < gBattlersCount; i++)
    {
        enum BattlerId battler = gBattlerByTurnOrder[i];
        if (gChosenActionByBattler[battler] == B_ACTION_USE_MOVE
        && GetMoveEffect(gChosenMoveByBattler[battler]) == EFFECT_PURSUIT
        && IsBattlerAlive(battlerDef)
        && IsBattlerAlive(battler)
        && !IsBattlerAlly(battler, battlerDef)
        && (B_PURSUIT_TARGET >= GEN_4 || gBattleStruct->moveTarget[battler] == battlerDef)
        && !IsGimmickSelected(battler, GIMMICK_Z_MOVE)
        && !IsGimmickSelected(battler, GIMMICK_DYNAMAX)
        && GetActiveGimmick(battler) != GIMMICK_DYNAMAX)
        {
            gBattlerTarget = battler;
            return TRUE;
        }
    }
    return FALSE;
}

bool32 IsPursuitTargetSet(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (gBattleStruct->battlerState[battler].pursuitTarget)
            return TRUE;
    }
    return FALSE;
}

void ClearPursuitValues(void)
{
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
        gBattleStruct->battlerState[i].pursuitTarget = FALSE;
    gBattleStruct->pursuitStoredSwitch = PARTY_SIZE;
}

void ClearPursuitValuesIfSet(enum BattlerId battler)
{
    if (gBattleStruct->battlerState[battler].pursuitTarget)
        ClearPursuitValues();
}

bool32 HasWeatherEffect(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (!IsBattlerAlive(battler))
            continue;

        if (BattlerHasTrait(battler, ABILITY_CLOUD_NINE)
         || BattlerHasTrait(battler, ABILITY_AIR_LOCK))
            return FALSE;
    }

    return TRUE;
}

void UpdateStallMons(void)
{
    if (IsBattlerTurnDamaged(gBattlerTarget, INCLUDING_SUBSTITUTES) || GetMoveCategory(gCurrentMove) == DAMAGE_CATEGORY_STATUS)
        return;

    struct BattleContext ctx = {0};
    ctx.battlerAtk = gBattlerAttacker;
    ctx.battlerDef = gBattlerTarget;
    ctx.move = ctx.chosenMove = gCurrentMove;
    ctx.moveType = GetBattleMoveType(gCurrentMove); //  Probably doesn't handle dynamic move types right now

    if (IsBattlerProtected(&ctx))
        return;

    enum MoveTarget target = GetBattlerMoveTargetType(ctx.battlerAtk, ctx.move);
    if (!IsDoubleBattle()
     || target == TARGET_SELECTED
     || target == TARGET_SMART)
    {
        if (CanMoveBeBlockedByTarget(&ctx, GetChosenMovePriority(ctx.battlerAtk)))
        {
            gAiBattleData->playerStallMons[gBattlerPartyIndexes[gBattlerTarget]]++;
        }
        else if (CalcTypeEffectivenessMultiplier(&ctx) == UQ_4_12(0.0))
        {
            gAiBattleData->playerStallMons[gBattlerPartyIndexes[gBattlerTarget]]++;
        }
    }
    //  Handling for moves that target multiple opponents in doubles not handled currently
}

bool32 TrySwitchInEjectPack(enum EjectPackTiming timing)
{
    // Because sorting the battlers by speed takes lots of cycles, it's better to just check if any of the battlers has the Eject items.
    u32 ejectPackBattlers = 0;
    u32 numEjectPackBattlers = 0;

    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (gBattleMons[i].volatiles.tryEjectPack
         && BattlerHasHeldItemEffect(i, HOLD_EFFECT_EJECT_PACK, TRUE)
         && IsBattlerAlive(i)
         && CanBattlerSwitch(i))
        {
            ejectPackBattlers |= 1u << i;
            numEjectPackBattlers++;
        }
    }

    if (numEjectPackBattlers == 0)
        return FALSE;

    enum BattlerId battlers[MAX_BATTLERS_COUNT] = {0, 1, 2, 3};
    if (numEjectPackBattlers > 1)
        SortBattlersBySpeed(battlers, FALSE);

    for (enum BattlerId i = 0; i < gBattlersCount; i++)
        gBattleMons[i].volatiles.tryEjectPack = FALSE;

    for (u32 i = 0; i < gBattlersCount; i++)
    {
        enum BattlerId battler = battlers[i];

        if (!(ejectPackBattlers & 1u << battler))
            continue;

        gBattleScripting.battler = battler;
        gLastUsedItem = GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_EJECT_PACK, TRUE);
        if (timing == END_TURN)
            BattleScriptExecute(BattleScript_EjectPackActivate_End2);
        else
            BattleScriptCall(BattleScript_EjectPackActivate_Ret);
        gAiLogicData->ejectPackSwitch = TRUE;
        return TRUE;
    }

    return FALSE;
}

bool32 EmergencyExitCanBeTriggered(enum BattlerId battler)
{
    enum Ability ability = ABILITY_NONE;

    if (BattlerHasTrait(battler, ABILITY_EMERGENCY_EXIT))
        ability = ABILITY_EMERGENCY_EXIT;
    else if (BattlerHasTrait(battler, ABILITY_WIMP_OUT))
        ability = ABILITY_WIMP_OUT;

    if (ability == ABILITY_NONE)
        return FALSE;

    if (IsBattlerAlive(battler)
     && HadMoreThanHalfHpNowDoesnt(battler)
     && (CanBattlerSwitch(battler) || !(gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_BOSS)))
     && !(gBattleTypeFlags & BATTLE_TYPE_ARENA)
     && gBattleMons[battler].volatiles.semiInvulnerable != STATE_SKY_DROP)
     {
        gLastUsedAbility = ability;
        PushTraitStack(battler, ability);
        return TRUE;
     }
        
    return FALSE;
}

bool32 TryTriggerSymbiosis(enum BattlerId battler, u32 ally)
{
    return BattlerHasTrait(ally, ABILITY_SYMBIOSIS)
        && IsBattlerAlive(battler)
        && IsBattlerAlive(ally);
}

// Called by Cmd_removeitem. itemId represents the item that was removed, not being given.
bool32 TrySymbiosis(enum BattlerId battler, bool32 moveEnd)
{
    if (!GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_EJECT_BUTTON, TRUE)
        && !GetBattlerHeldItemWithEffect(battler, HOLD_EFFECT_EJECT_PACK, TRUE)
        && (GetConfig(B_SYMBIOSIS_GEMS) < GEN_7 || !(gSpecialStatuses[battler].gemBoost))
        && GetMoveEffect(gCurrentMove) != EFFECT_FLING //Fling and damage-reducing berries are handled separately.
        && !gSpecialStatuses[battler].berryReduced
        && TryTriggerSymbiosis(battler, BATTLE_PARTNER(battler)))
    {
        u32 slot, i, targetableSlots[MAX_MON_ITEMS];
        u32 index = 0;
        targetableSlots[0] = MAX_MON_ITEMS; // Invalid value for first slot if no valid slots found

        for (i = 0; i < MAX_MON_ITEMS; i++)
        {
            if(!gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]][i].stolen
            && gBattleMons[battler].items[i] == ITEM_NONE
            && gBattleMons[BATTLE_PARTNER(battler)].items[i] != ITEM_NONE
            && CanBattlerGetOrLoseItem(battler, BATTLE_PARTNER(battler), gBattleMons[BATTLE_PARTNER(battler)].items[i])
            && CanBattlerGetOrLoseItem(BATTLE_PARTNER(battler), battler, gBattleMons[BATTLE_PARTNER(battler)].items[i]))
            {
                if (targetableSlots[0] != MAX_MON_ITEMS)
                    index++;
                targetableSlots[index] = i;
            }
        }
        
        if (targetableSlots[0] != MAX_MON_ITEMS)
        {
            slot = gLastItemSlot = GetSlot(targetableSlots, index);
            BestowItem(BATTLE_PARTNER(battler), battler, slot);
            gLastUsedAbility = ABILITY_SYMBIOSIS;
            PushTraitStack(BATTLE_PARTNER(battler), ABILITY_SYMBIOSIS);
            gEffectBattler = battler;
            gBattleScripting.battler = gBattlerAbility = BATTLE_PARTNER(battler);
            if (moveEnd)
                BattleScriptPushCursor();
            else
                BattleScriptPush(gBattlescriptCurrInstr + 2);
            gBattlescriptCurrInstr = BattleScript_SymbiosisActivates;
            return TRUE;
        }
    }
    return FALSE;
}

// Used by Bestow and Symbiosis to take an item from one battler and give to another.
void BestowItem(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 slot)
{
    gLastUsedItem = gBattleMons[battlerAtk].items[slot];

    gBattleMons[battlerAtk].items[slot] = ITEM_NONE;
    BtlController_EmitSetMonData(battlerAtk, B_COMM_TO_CONTROLLER, REQUEST_HELDITEM_BATTLE + slot, 0, sizeof(gBattleMons[battlerAtk].items[slot]), &gBattleMons[battlerAtk].items[slot]);
    MarkBattlerForControllerExec(battlerAtk);
    CheckSetUnburden(battlerAtk);

    gBattleMons[battlerDef].items[slot] = gLastUsedItem;
    BtlController_EmitSetMonData(battlerDef, B_COMM_TO_CONTROLLER, REQUEST_HELDITEM_BATTLE + slot, 0, sizeof(gBattleMons[battlerDef].items[slot]), &gBattleMons[battlerDef].items[slot]);
    MarkBattlerForControllerExec(battlerDef);
    gBattleMons[battlerDef].volatiles.unburdenActive = FALSE;
}

#define UNPACK_VOLATILE_GETTERS(_enum, _fieldName, _typeMaxValue, ...) case _enum: return gBattleMons[battler].volatiles._fieldName;

// Gets the value of a volatile status flag for a certain battler
// Primarily used for the debug menu and scripts. Outside of it explicit references are preferred
// Uses Arm because there is a compiler bug when it tries to compile in thumb
ARM_FUNC u32 GetBattlerVolatile(enum BattlerId battler, enum Volatile _volatile)
{
    switch (_volatile)
    {
    VOLATILE_DEFINITIONS(UNPACK_VOLATILE_GETTERS)
    /* Expands to:
    case VOLATILE_CONFUSION:
        return gBattleMons[battler].volatiles.confusionTurns;
    */
    default: // Invalid volatile status
        return 0;
    }
}

#define UNPACK_VOLATILE_SETTERS(_enum, _fieldName, _typeMaxValue, ...) case _enum: gBattleMons[battler].volatiles._fieldName = min(GET_VOLATILE_MAXIMUM(_typeMaxValue), newValue); break;

// Sets the value of a volatile status flag for a certain battler
// Primarily used for the debug menu and scripts. Outside of it explicit references are preferred
void SetMonVolatile(enum BattlerId battler, enum Volatile _volatile, u32 newValue)
{
    switch (_volatile)
    {
        VOLATILE_DEFINITIONS(UNPACK_VOLATILE_SETTERS)
        /* Expands to:
    case VOLATILE_CONFUSION:
            gBattleMons[battler].volatiles.confusionTurns = min(MAX_BITS(3), newValue);
            break;
        */
    default: // Invalid volatile status
            return;
    }
}

bool32 ItemHealMonVolatile(enum BattlerId battler, enum Item itemId)
{
    bool32 statusChanged = FALSE;
    const u8 *effect = GetItemEffect(itemId);
    if (effect[3] & ITEM3_STATUS_ALL)
    {
        statusChanged = (gBattleMons[battler].volatiles.infatuation || gBattleMons[battler].volatiles.confusionTurns > 0 || gBattleMons[battler].volatiles.infiniteConfusion);
        gBattleMons[battler].volatiles.infatuation = 0;
        gBattleMons[battler].volatiles.confusionTurns = 0;
        gBattleMons[battler].volatiles.infiniteConfusion = FALSE;
    }
    else if (effect[0] & ITEM0_INFATUATION)
    {
        statusChanged = !!gBattleMons[battler].volatiles.infatuation;
        gBattleMons[battler].volatiles.infatuation = 0;
    }
    else if (effect[3] & ITEM3_CONFUSION)
    {
        statusChanged = (gBattleMons[battler].volatiles.confusionTurns > 0 || gBattleMons[battler].volatiles.infiniteConfusion);
        gBattleMons[battler].volatiles.confusionTurns = 0;
        gBattleMons[battler].volatiles.infiniteConfusion = FALSE;
    }

    return statusChanged;
}

// Hazards are added to a queue and applied based in order (FIFO)
void PushHazardTypeToQueue(enum BattleSide side, enum Hazards hazardType)
{
    if (!IsHazardOnSide(side, hazardType)) // Failsafe
        gBattleStruct->hazardsQueue[side][gBattleStruct->numHazards[side]++] = hazardType;
}

bool32 IsHazardOnSide(enum BattleSide side, enum Hazards hazardType)
{
    for (u32 i = 0; i < HAZARDS_MAX_COUNT; i++)
    {
        if (gBattleStruct->hazardsQueue[side][i] == hazardType)
            return TRUE;
    }
    return FALSE;
}

bool32 AreAnyHazardsOnSide(enum BattleSide side)
{
    return gBattleStruct->numHazards[side] > 0;
}

bool32 IsHazardOnSideAndClear(enum BattleSide side, enum Hazards hazardType)
{
    for (u32 i = 0; i < HAZARDS_MAX_COUNT; i++)
    {
        if (gBattleStruct->hazardsQueue[side][i] == hazardType)
        {
            gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
            if (hazardType == HAZARDS_SPIKES)
                gSideTimers[side].spikesAmount = 0;
            else if (hazardType == HAZARDS_TOXIC_SPIKES)
                gSideTimers[side].toxicSpikesAmount = 0;
            return TRUE;
        }
    }
    return FALSE;
}

void RemoveAllHazardsFromField(enum BattleSide side)
{
    gSideTimers[side].spikesAmount = 0;
    gSideTimers[side].toxicSpikesAmount = 0;
    gBattleStruct->numHazards[side] = 0;
    for (u32 i = 0; i < HAZARDS_MAX_COUNT; i++)
        gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
}

void RemoveHazardFromField(enum BattleSide side, enum Hazards hazardType)
{
    u32 i;
    for (i = 0; i < HAZARDS_MAX_COUNT; i++)
    {
        if (gBattleStruct->hazardsQueue[side][i] == hazardType)
        {
            gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
            gBattleStruct->numHazards[side]--;
            if (hazardType == HAZARDS_SPIKES)
                gSideTimers[side].spikesAmount = 0;
            else if (hazardType == HAZARDS_TOXIC_SPIKES)
                gSideTimers[side].toxicSpikesAmount = 0;
            break;
        }
    }
    while (i < HAZARDS_MAX_COUNT)
    {
        if (i+1 == HAZARDS_MAX_COUNT)
        {
            gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
            break;
        }
        gBattleStruct->hazardsQueue[side][i] = gBattleStruct->hazardsQueue[side][i+1];
        i++;
    }
}

static bool32 CanMoveSkipAccuracyCheck(enum BattlerId battlerAtk, u32 move)
{
    return MoveAlwaysHitsOnSameType(move) && IS_BATTLER_OF_TYPE(battlerAtk, GetMoveType(move));
}

bool32 CanMoveSkipAccuracyCalc(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, enum ResultOption option)
{
    bool32 effect = FALSE;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);

    if (gBattleMons[battlerAtk].volatiles.battlerWithSureHit == battlerDef + 1
     || CanMoveSkipAccuracyCheck(battlerAtk, move)
     || gBattleMons[battlerDef].volatiles.glaiveRush)
    {
        effect = TRUE;
    }
    // If the attacker has the ability No Guard and they aren't targeting a Pokemon involved in a Sky Drop with the move Sky Drop, move hits.
    else if (BattlerHasTrait(battlerAtk, ABILITY_NO_GUARD)
          && gBattleMons[battlerDef].volatiles.semiInvulnerable != STATE_COMMANDER
          && (moveEffect != EFFECT_SKY_DROP || gBattleStruct->skyDropTargets[battlerDef] == SKY_DROP_NO_TARGET))
    {
        effect = TRUE;
    }
    // If the target has the ability No Guard and they aren't involved in a Sky Drop or the current move isn't Sky Drop, move hits.
    else if (BattlerHasTrait(battlerDef, ABILITY_NO_GUARD)
          && (moveEffect != EFFECT_SKY_DROP || gBattleStruct->skyDropTargets[battlerDef] == SKY_DROP_NO_TARGET))
    {
        effect = TRUE;
    }
    // If the target is under the effects of Telekinesis, and the move isn't a OH-KO move, move hits.
    else if (gBattleMons[battlerDef].volatiles.telekinesis
          && !IsSemiInvulnerable(battlerDef, CHECK_ALL)
          && moveEffect != EFFECT_OHKO)
    {
        effect = TRUE;
    }
    else if (gBattleStruct->battlerState[battlerDef].pursuitTarget)
    {
        effect = TRUE;
    }
    else if (GetActiveGimmick(battlerAtk) == GIMMICK_Z_MOVE && !IsSemiInvulnerable(battlerDef, CHECK_ALL))
    {
        effect = TRUE;
    }
    else if (B_MINIMIZE_DMG_ACC >= GEN_6
     && gBattleMons[battlerDef].volatiles.minimize
     && MoveIncreasesPowerToMinimizedTargets(move))
    {
        effect = TRUE;
    }
    else if (GetMoveAccuracy(move) == 0)
    {
        effect = TRUE;
    }

    if (!effect && HasWeatherEffect())
    {
        if (MoveAlwaysHitsInRain(move) && IsBattlerWeatherAffected(battlerDef, B_WEATHER_RAIN))
            effect = TRUE;
        else if ((gBattleWeather & B_WEATHER_ICY_ANY) && MoveAlwaysHitsInHailSnow(move))
            effect = TRUE;
        else if (BattlerHasTrait(battlerAtk, ABILITY_SOLAR_PANEL)
              && GetBattleMoveType(move) == TYPE_ELECTRIC
              && IsBattlerWeatherAffected(battlerAtk, B_WEATHER_SUN))
            effect = TRUE;
        else if (BattlerHasTrait(battlerAtk, ABILITY_ROCKSTORM)
              && GetBattleMoveType(move) == TYPE_ROCK
              && IsBattlerWeatherAffected(battlerAtk, B_WEATHER_SANDSTORM))
            effect = TRUE;
        else if (BattlerHasTrait(battlerAtk, ABILITY_MONSOON)
              && GetBattleMoveType(move) == TYPE_WATER
              && IsBattlerWeatherAffected(battlerAtk, B_WEATHER_RAIN))
            effect = TRUE;

        if (effect)
            return effect;
    }

    if (BattlerHasTrait(battlerAtk, ABILITY_NO_GUARD) && option == RUN_SCRIPT)
        RecordAbilityBattle(battlerAtk, ABILITY_NO_GUARD);

    return effect;
}

u32 GetTotalAccuracy(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    u32 calc, moveAcc;
    s8 buff, accStage, evasionStage;
    enum Ability battlerTraits[MAX_MON_TRAITS];
    STORE_BATTLER_TRAITS(battlerAtk);
    bool32 attackerHasMegaSol = SearchTraits(battlerTraits, ABILITY_MEGA_SOL);

    // Use AI Ability knowledge if this is an AI check
    if(gAiLogicData->aiCalcInProgress)
    {
        battlerTraits[0] = gAiLogicData->abilities[battlerAtk];
        attackerHasMegaSol = SearchTraits(battlerTraits, ABILITY_MEGA_SOL);
    }

    gPotentialItemEffectBattler = battlerDef;
    accStage = gBattleMons[battlerAtk].statStages[STAT_ACC];
    evasionStage = gBattleMons[battlerDef].statStages[STAT_EVASION];
    if (SearchTraits(battlerTraits, ABILITY_UNAWARE) || SearchTraits(battlerTraits, ABILITY_KEEN_EYE) || SearchTraits(battlerTraits, ABILITY_MINDS_EYE)
     || (GetConfig(B_ILLUMINATE_EFFECT) >= GEN_9 && SearchTraits(battlerTraits, ABILITY_ILLUMINATE)))
        evasionStage = DEFAULT_STAT_STAGE;
    if (MoveIgnoresDefenseEvasionStages(move))
        evasionStage = DEFAULT_STAT_STAGE;
    if (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battlerDef, ABILITY_UNAWARE) : BattlerHasTrait(battlerDef, ABILITY_UNAWARE))
        accStage = DEFAULT_STAT_STAGE;

    if (gBattleMons[battlerDef].volatiles.foresight || gBattleMons[battlerDef].volatiles.miracleEye)
        buff = accStage;
    else
        buff = accStage + DEFAULT_STAT_STAGE - evasionStage;

    if (buff < MIN_STAT_STAGE)
        buff = MIN_STAT_STAGE;
    if (buff > MAX_STAT_STAGE)
        buff = MAX_STAT_STAGE;

    moveAcc = GetMoveAccuracy(move);
    // Check Thunder and Hurricane on sunny weather.
    if (((attackerHasMegaSol && (GetBattlerWeather(battlerAtk, gBattleWeather) & B_WEATHER_SUN))
      || (!attackerHasMegaSol && IsBattlerWeatherAffected(battlerDef, B_WEATHER_SUN)))
     && MoveHas50AccuracyInSun(move))
        moveAcc = 50;
    // Check Wonder Skin.
    if ((gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battlerDef, ABILITY_WONDER_SKIN) : BattlerHasTrait(battlerDef, ABILITY_WONDER_SKIN)) && IsBattleMoveStatus(move) && moveAcc > 50)
        moveAcc = 50;
    if ((gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battlerDef, ABILITY_INDOMITABLE) : BattlerHasTrait(battlerDef, ABILITY_INDOMITABLE)) && IsBattleMoveStatus(move))
        moveAcc /= 2;

    calc = gAccuracyStageRatios[buff].dividend * moveAcc;
    calc /= gAccuracyStageRatios[buff].divisor;

    // Attacker's ability
    if (SearchTraits(battlerTraits, ABILITY_COMPOUND_EYES))
        calc = (calc * 130) / 100; // 1.3 compound eyes boost
    if (SearchTraits(battlerTraits, ABILITY_KEEN_EYE) && accStage >= DEFAULT_STAT_STAGE)
        calc = (calc * 130) / 100; // 1.3 keen eye boost
    if (SearchTraits(battlerTraits, ABILITY_VICTORY_STAR))
        calc = (calc * 110) / 100; // 1.1 victory star boost
    if (SearchTraits(battlerTraits, ABILITY_HUSTLE))
        if (IsBattleMovePhysical(move))
            calc = (calc * 80) / 100; // 1.2 hustle loss

    // Target's ability
    STORE_BATTLER_TRAITS(battlerDef);

    if (SearchTraits(battlerTraits, ABILITY_SAND_VEIL))
        if (gBattleWeather & B_WEATHER_SANDSTORM && HasWeatherEffect())
            calc = (calc * 80) / 100; // 1.2 sand veil loss
    if (SearchTraits(battlerTraits, ABILITY_SNOW_CLOAK))
        if ((gBattleWeather & B_WEATHER_ICY_ANY) && HasWeatherEffect())
            calc = (calc * 80) / 100; // 1.2 snow cloak loss
    if (SearchTraits(battlerTraits, ABILITY_TANGLED_FEET))
        if (gBattleMons[battlerDef].volatiles.confusionTurns)
            calc = (calc * 50) / 100; // 1.5 tangled feet loss

    // Attacker's ally's ability
    enum BattlerId atkAlly = BATTLE_PARTNER(battlerAtk);
    if (BattlerHasTrait(atkAlly, ABILITY_VICTORY_STAR))
        if (IsBattlerAlive(atkAlly))
            calc = (calc * 110) / 100; // 1.1 ally's victory star boost

    if (MoveHasIncreasedAccByTenOnSameType(move) && !IS_BATTLER_OF_TYPE(battlerAtk, GetMoveType(move)))
        calc = (calc * 110) / 100;

    // Attacker's hold effect
    if (BattlerHasHeldItemEffect(battlerAtk, HOLD_EFFECT_WIDE_LENS, TRUE))
        calc = (calc * (100 + GetBattlerItemHoldEffectParam(battlerAtk, GetBattlerHeldItemWithEffect(battlerAtk, HOLD_EFFECT_WIDE_LENS, TRUE)))) / 100;

    if (BattlerHasHeldItemEffect(battlerAtk, HOLD_EFFECT_ZOOM_LENS, TRUE)
     && gChosenActionByBattler[battlerDef] == B_ACTION_USE_MOVE
     && HasBattlerActedThisTurn(battlerDef))
        calc = (calc * (100 + GetBattlerItemHoldEffectParam(battlerAtk, GetBattlerHeldItemWithEffect(battlerAtk, HOLD_EFFECT_ZOOM_LENS, TRUE)))) / 100;

    // Target's hold effect
    if (!BattlerHasTrait(battlerAtk, ABILITY_OVERLOAD) && BattlerHasHeldItemEffect(battlerDef, HOLD_EFFECT_EVASION_UP, TRUE))
        calc = (calc * (100 - GetBattlerItemHoldEffectParam(battlerDef, GetBattlerHeldItemWithEffect(battlerDef, HOLD_EFFECT_EVASION_UP, TRUE)))) / 100;


    if (gBattleStruct->battlerState[battlerAtk].usedMicleBerry)
    {
        // TODO: Is this true?
        if ((gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battlerAtk, ABILITY_RIPEN) : BattlerHasTrait(battlerAtk, ABILITY_RIPEN)))
            calc = (calc * 140) / 100;  // ripen gives 40% acc boost
        else
            calc = (calc * 120) / 100;  // 20% acc boost
    }

    if (gFieldStatuses & STATUS_FIELD_GRAVITY)
        calc = (calc * 5) / 3; // 1.66 Gravity acc boost

    if (B_AFFECTION_MECHANICS == TRUE && GetBattlerAffectionHearts(battlerDef) == AFFECTION_FIVE_HEARTS)
        calc = (calc * 90) / 100;

    if (HasWeatherEffect() && gBattleWeather & B_WEATHER_FOG)
        calc = (calc * 60) / 100; // modified by 3/5

    return calc;
}

bool32 DoesOHKOMoveMissTarget(struct BattleCalcValues *cv)
{
    enum OHKOResult {
        NO_HIT,
        CALC_ACC,
        SURE_HIT,
    };

    // Dynamaxed Pokemon cannot be hit by OHKO moves.
    if (GetActiveGimmick(cv->battlerDef) == GIMMICK_DYNAMAX)
    {
        gBattleStruct->moveResultFlags[cv->battlerDef] |= MOVE_RESULT_ONE_HIT_KO_NO_AFFECT;
        return TRUE;
    }

    if (gBattleMons[cv->battlerDef].level > gBattleMons[cv->battlerAtk].level)
        return TRUE;

    if (BattlerHasTrait(cv->battlerDef, ABILITY_STURDY))
    {
        PushTraitStack(cv->battlerDef, ABILITY_STURDY);
        gBattleStruct->moveResultFlags[cv->battlerDef] |= MOVE_RESULT_ONE_HIT_KO_STURDY;
        return TRUE;
    }

    enum OHKOResult lands = NO_HIT;

    if (gBattleMons[cv->battlerAtk].volatiles.battlerWithSureHit == cv->battlerDef + 1
          || IsAbilityAndRecord(cv->battlerAtk, ABILITY_NO_GUARD)
          || IsAbilityAndRecord(cv->battlerDef, ABILITY_NO_GUARD))
    {
        lands = SURE_HIT;
    }
    else
    {
        lands = CALC_ACC;
    }

    if (lands == CALC_ACC)
    {
        u32 odds = GetMoveAccuracy(cv->move) + (gBattleMons[cv->battlerAtk].level - gBattleMons[cv->battlerDef].level);
        if (MoveHasIncreasedAccByTenOnSameType(cv->move) && !IS_BATTLER_OF_TYPE(cv->battlerAtk, GetMoveType(cv->move)))
            odds -= 10;
        if (RandomPercentage(RNG_ACCURACY, odds) && gBattleMons[cv->battlerAtk].level >= gBattleMons[cv->battlerDef].level)
            lands = SURE_HIT;
    }

    if (lands == SURE_HIT)
    {
        gBattleStruct->moveResultFlags[cv->battlerDef] |= MOVE_RESULT_ONE_HIT_KO_NO_AFFECT;
        return FALSE;
    }

    return TRUE;
}

bool32 DoesMoveMissTarget(struct BattleCalcValues *cv)
{
    if (GetMoveEffect(cv->move) == EFFECT_OHKO)
        return DoesOHKOMoveMissTarget(cv);

    if (CanMoveSkipAccuracyCalc(cv->battlerAtk, cv->battlerDef, cv->move, RUN_SCRIPT))
        return FALSE;

    u32 accuracy = GetTotalAccuracy(
                        cv->battlerAtk,
                        cv->battlerDef,
                        cv->move
                    );
    return !RandomPercentage(RNG_ACCURACY, accuracy);
}

bool32 IsSemiInvulnerable(enum BattlerId battler, enum SemiInvulnerableExclusion excludeCommander)
{
    if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_COMMANDER)
        return excludeCommander != EXCLUDE_COMMANDER;
    return gBattleMons[battler].volatiles.semiInvulnerable != STATE_NONE;
}

bool32 BreaksThroughSemiInvulnerablity(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    enum SemiInvulnerableState state = gBattleMons[battlerDef].volatiles.semiInvulnerable;

    if (state != STATE_COMMANDER)
    {
        if (CanMoveSkipAccuracyCheck(battlerAtk, move))
            return TRUE;
        if ((gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battlerAtk, ABILITY_NO_GUARD) : BattlerHasTrait(battlerAtk, ABILITY_NO_GUARD))
         || (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battlerDef, ABILITY_NO_GUARD) : BattlerHasTrait(battlerDef, ABILITY_NO_GUARD)))
            return TRUE;
        if (gBattleMons[battlerAtk].volatiles.battlerWithSureHit == battlerDef + 1)
            return TRUE;
    }

    switch (state)
    {
    case STATE_UNDERGROUND:
        return MoveDamagesUnderground(move);
    case STATE_UNDERWATER:
        return MoveDamagesUnderWater(move);
    case STATE_ON_AIR:
    case STATE_SKY_DROP:
        return MoveDamagesAirborne(move) || MoveDamagesAirborneDoubleDamage(move);
    case STATE_PHANTOM_FORCE:
        return FALSE;
    case STATE_COMMANDER:
        return GetMoveEffect(move) == EFFECT_TRANSFORM;
    case STATE_NONE:
    case SEMI_INVULNERABLE_COUNT:
        return TRUE;
    }

    return FALSE;
}

bool32 HasPartnerTrainer(enum BattlerId battler)
{
    if ((GetBattlerSide(battler) == B_SIDE_PLAYER && gBattleTypeFlags & BATTLE_TYPE_PLAYER_HAS_PARTNER)
     || (GetBattlerSide(battler) == B_SIDE_OPPONENT && gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS))
        return TRUE;
    else
        return FALSE;
}

static bool32 IsOpposingSideEmpty(enum BattlerId battler)
{
    enum BattlerId oppositeBattler = BATTLE_OPPOSITE(battler);

    if (IsBattlerAlive(oppositeBattler))
        return FALSE;

    if (!IsDoubleBattle())
        return TRUE;

    if (IsBattlerAlive(BATTLE_PARTNER(oppositeBattler)))
        return FALSE;
    return TRUE;
}

static enum BattlerId GetOppositeSideShiftTarget(enum BattlerId battler)
{
    enum BattlerId oppositeBattler = BATTLE_OPPOSITE(battler);

    if (IsBattlerAlive(oppositeBattler))
        return oppositeBattler;

    if (IsDoubleBattle() && IsBattlerAlive(BATTLE_PARTNER(oppositeBattler)))
        return BATTLE_PARTNER(oppositeBattler);

    return MAX_BATTLERS_COUNT;
}

bool32 IsAffectedByPowderMove(enum BattlerId battler)
{
    bool32 hasGoggles = (gAiLogicData->aiCalcInProgress ? Ai_BattlerHasHoldEffect (battler, HOLD_EFFECT_SAFETY_GOGGLES, gAiLogicData) : BattlerHasHeldItemEffect(battler, HOLD_EFFECT_SAFETY_GOGGLES, TRUE));
    bool32 hasCoat = (gAiLogicData->aiCalcInProgress ? AI_BATTLER_HAS_TRAIT(battler, ABILITY_OVERCOAT) : BattlerHasTrait(battler, ABILITY_OVERCOAT));

    if (GetConfig(B_POWDER_OVERCOAT) >= GEN_6 && hasCoat)
        return FALSE;
    if (GetConfig(B_POWDER_GRASS) >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GRASS))
        return FALSE;
    if (hasGoggles)
        return FALSE;
    return TRUE;
}

void RemoveAbilityFlags(enum BattlerId battler)
{
    gBattleMons[battler].volatiles.unburdenActive = FALSE;

    switch (GetBattlerAbility(battler))
    {
    case ABILITY_FLASH_FIRE:
        gBattleMons[battler].volatiles.flashFireBoosted = FALSE;
        break;
    case ABILITY_VESSEL_OF_RUIN:
        gBattleMons[battler].volatiles.vesselOfRuin = FALSE;
        break;
    case ABILITY_TABLETS_OF_RUIN:
        gBattleMons[battler].volatiles.tabletsOfRuin = FALSE;
        break;
    case ABILITY_SWORD_OF_RUIN:
        gBattleMons[battler].volatiles.swordOfRuin = FALSE;
        break;
    case ABILITY_BEADS_OF_RUIN:
        gBattleMons[battler].volatiles.beadsOfRuin = FALSE;
        break;
    default:
       break;
    }
}

void CheckSetUnburden(enum BattlerId battler)
{
    if (IsAbilityAndRecord(battler, ABILITY_UNBURDEN))
        gBattleMons[battler].volatiles.unburdenActive = TRUE;
}

bool32 IsAnyTargetTurnDamaged(enum BattlerId battlerAtk)
{
    for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
    {
        if (battlerDef == battlerAtk)
            continue;
        if (IsBattlerTurnDamaged(battlerDef, INCLUDING_SUBSTITUTES))
            return TRUE;
    }
    return FALSE;
}

bool32 IsAnyTargetAffected(void)
{
    bool32 isSpreadMove = IsSpreadMove(GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove));
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (isSpreadMove)
        {
            if (battler == gBattlerAttacker)
                continue;
        }
        else
        {
            if (battler != gBattlerTarget)
                continue;
        }

        if (!IsBattlerUnaffectedByMove(battler))
            return TRUE;
    }
    return FALSE;
}

bool32 IsDoubleSpreadMove(void)
{
    return gBattleStruct->numSpreadTargets > 1
        && !gBattleStruct->unableToUseMove
        && IsSpreadMove(GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove));
}

bool32 IsBattlerInvalidForSpreadMove(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    return battlerDef == battlerAtk
        || !IsBattlerAlive(battlerDef)
        || IsBattlerUnaffectedByMove(battlerDef);
}

bool32 IsAllowedToUseBag(void)
{
    switch (VarGet(B_VAR_NO_BAG_USE))
    {
    case NO_BAG_RESTRICTION:
        return TRUE;
    case NO_BAG_AGAINST_TRAINER: //True in wild battle; False in trainer battle
        return (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER));
    case NO_BAG_IN_BATTLE:
        return FALSE;
    default:
        return TRUE; // Undefined Behavior
    }
}

bool32 IsMimikyuDisguised(enum BattlerId battler)
{
    return gBattleMons[battler].species == SPECIES_MIMIKYU_DISGUISED
        || gBattleMons[battler].species == SPECIES_MIMIKYU_TOTEM_DISGUISED;
}

#define UNPACK_STARTING_STATUS_TO_EWRAM(_enum, _fieldName, ...) case _enum: gStartingStatuses._fieldName = TRUE; break;

void SetStartingStatus(enum StartingStatus status)
{
    switch (status)
    {
    STARTING_STATUS_DEFINITIONS(UNPACK_STARTING_STATUS_TO_EWRAM);
    }
}

#define UNPACK_STARTING_STATUS_RESET(_enum, _fieldName, ...) gStartingStatuses._fieldName = FALSE;

void ResetStartingStatuses(void)
{
    STARTING_STATUS_DEFINITIONS(UNPACK_STARTING_STATUS_RESET);
}

bool32 IsUsableWhileAsleepEffect(enum BattleMoveEffects effect)
{
    // All moves usable while asleep like Snore, Sleep Talk, etc.
    switch (effect)
    {
    case EFFECT_SNORE:
    case EFFECT_SLEEP_TALK:
        return TRUE;
    default:
        return FALSE;
    }
}

void SetWrapTurns(enum BattlerId battler)
{
    u32 normalWrapTurns = B_WRAP_TURNS - 2; // 5 turns

    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (GetSlotHeldItemEffect(gBattlerAttacker, i, TRUE) == HOLD_EFFECT_GRIP_CLAW)
        {
            if (gBattleMons[battler].volatiles.wrapTurns == 0)
                gBattleMons[battler].volatiles.wrapTurns = GetConfig(B_BINDING_TURNS) >= GEN_5 ? B_WRAP_TURNS : normalWrapTurns;
            else if (GetConfig(B_ALLOW_HELD_DUPES))
                gBattleMons[battler].volatiles.wrapTurns += 2;
        }
    }
    if (gBattleMons[battler].volatiles.wrapTurns == 0)
        gBattleMons[battler].volatiles.wrapTurns = GetConfig(B_BINDING_TURNS) >= GEN_5 ? RandomUniform(RNG_WRAP, 4, normalWrapTurns) : RandomUniform(RNG_WRAP, 2, normalWrapTurns);   
}

// Return True if the order was changed, and false if the order was not changed(for example because the target would move after the attacker anyway).
bool32 ChangeOrderTargetAfterAttacker(void)
{
    u32 i;
    u8 data[MAX_BATTLERS_COUNT];
    u8 actionsData[MAX_BATTLERS_COUNT];
    u32 attackerTurnOrderNum = GetBattlerTurnOrderNum(gBattlerAttacker);
    u32 targetTurnOrderNum = GetBattlerTurnOrderNum(gBattlerTarget);

    if (attackerTurnOrderNum > targetTurnOrderNum)
        return FALSE;
    if (attackerTurnOrderNum + 1 == targetTurnOrderNum)
        return GetConfig(B_AFTER_YOU_TURN_ORDER) >= GEN_8;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        data[i] = gBattlerByTurnOrder[i];
        actionsData[i] = gActionsByTurnOrder[i];
    }
    if (attackerTurnOrderNum == 0 && targetTurnOrderNum == 2)
    {
        gBattlerByTurnOrder[1] = gBattlerTarget;
        gActionsByTurnOrder[1] = actionsData[2];
        gBattlerByTurnOrder[2] = data[1];
        gActionsByTurnOrder[2] = actionsData[1];
    }
    else if (attackerTurnOrderNum == 0 && targetTurnOrderNum == 3)
    {
        gBattlerByTurnOrder[1] = gBattlerTarget;
        gActionsByTurnOrder[1] = actionsData[3];
        gBattlerByTurnOrder[2] = data[1];
        gActionsByTurnOrder[2] = actionsData[1];
        gBattlerByTurnOrder[3] = data[2];
        gActionsByTurnOrder[3] = actionsData[2];
    }
    else // attackerTurnOrderNum == 1, targetTurnOrderNum == 3
    {
        gBattlerByTurnOrder[2] = gBattlerTarget;
        gActionsByTurnOrder[2] = actionsData[3];
        gBattlerByTurnOrder[3] = data[2];
        gActionsByTurnOrder[3] = actionsData[2];
    }
    return TRUE;
}

void TryUpdateEvolutionTracker(enum EvolutionConditions evolutionCondition, u32 upAmount, enum Move usedMove)
{
    u32 i, j;

    if (IsOnPlayerSide(gBattlerAttacker)
     && ((TESTING && IsDoubleBattle()) // To be removed when Wild Double Battles are added to tests
     || !(gBattleTypeFlags & (BATTLE_TYPE_LINK
                             | BATTLE_TYPE_EREADER_TRAINER
                             | BATTLE_TYPE_RECORDED_LINK
                             | BATTLE_TYPE_TRAINER_HILL
                             | BATTLE_TYPE_FRONTIER))))
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(gBattleMons[gBattlerAttacker].species);
        if (evolutions == NULL)
            return;

        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
                continue;
            if (evolutions[i].params == NULL)
                continue;

            for (j = 0; evolutions[i].params[j].condition != CONDITIONS_END; j++)
            {
                if (evolutions[i].params[j].condition != evolutionCondition)
                    continue;

                struct Pokemon *monAtk = GetBattlerMon(gBattlerAttacker);
                struct Pokemon *monDef = GetBattlerMon(gBattlerTarget);
                // We only have 10 bits to use
                u16 val = min(1023, GetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER) + upAmount);
                // Reset progress if you faint for the recoil method.
                switch (evolutionCondition)
                {
                case IF_USED_MOVE_X_TIMES:
                    if (evolutions[i].params[j].arg1 == usedMove)
                        SetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER, &val);
                    break;
                case IF_RECOIL_DAMAGE_GE:
                    if (gBattleMons[gBattlerAttacker].hp == 0)
                        val = 0;
                    SetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER, &val);
                    break;
                case IF_DEFEAT_X_WITH_ITEMS:
                    for (u32 k = 0; k < MAX_MON_ITEMS; k++)
                    {
                        if (GetMonData(monDef, MON_DATA_SPECIES) == evolutions[i].params[j].arg1
                        && GetMonData(monDef, MON_DATA_HELD_ITEM + k) == evolutions[i].params[j].arg2)
                            SetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER, &val);
                    }
                    break;
                default:
                    assertf(FALSE, "evolution condition %d is not handled within TryUpdateEvolutionTracker", evolutionCondition) {}
                    break;
                }
                return;
            }
        }
    }
}

static const u16 sProtectSuccessRates[] =
{
    USHRT_MAX,
    USHRT_MAX / 2,
    USHRT_MAX / 4,
    USHRT_MAX / 8
};

static const u16 sGen5ProtectSuccessRates[] =
{
    USHRT_MAX,
    USHRT_MAX / 3,
    USHRT_MAX / 9,
    USHRT_MAX / 27
};

bool32 CanUseMoveConsecutively(enum BattlerId battler)
{
    u32 moveUses = gBattleMons[battler].volatiles.consecutiveMoveUses;
    if (moveUses >= ARRAY_COUNT(sProtectSuccessRates))
        moveUses = ARRAY_COUNT(sProtectSuccessRates) - 1;

    u32 successRate = sGen5ProtectSuccessRates[moveUses];
    if (B_PROTECT_FAILURE_RATE < GEN_5)
        successRate = sProtectSuccessRates[moveUses];

    return successRate >= RandomUniform(RNG_PROTECT_FAIL, 0, USHRT_MAX);
}

// Used for Protect, Endure and Ally switch
void TryResetConsecutiveUseCounter(enum BattlerId battler)
{
    u32 lastMove = gLastResultingMoves[battler];
    if (lastMove == MOVE_UNAVAILABLE)
    {
        gBattleMons[battler].volatiles.consecutiveMoveUses = 0;
        return;
    }

    enum BattleMoveEffects lastEffect = GetMoveEffect(lastMove);
    if (!gBattleMoveEffects[lastEffect].usesProtectCounter)
    {
        if (GetConfig(B_ALLY_SWITCH_FAIL_CHANCE) < GEN_9 || lastEffect != EFFECT_ALLY_SWITCH)
            gBattleMons[battler].volatiles.consecutiveMoveUses = 0;
    }
}

void SetOrClearRageVolatile(void)
{
    if (GetConfig(B_RAGE_BUILDS) <= GEN_3 && MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_RAGE))
        gBattleMons[gBattlerAttacker].volatiles.rage = TRUE;
    else
        gBattleMons[gBattlerAttacker].volatiles.rage = FALSE;
}

enum BattlerId GetTargetBySlot(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    switch (battlerDef)
    {
    case B_BATTLER_0:
        return battlerAtk;
    case B_BATTLER_1:
        return BATTLE_PARTNER(battlerAtk);
    case B_BATTLER_2:
        return LEFT_FOE(battlerAtk);
    case B_BATTLER_3:
        return RIGHT_FOE(battlerAtk);
    default:
        errorf("Illegal battler");
        return B_BATTLER_0;
    }
}

//Returns the Ability or Innate of the battler at the given trait number, used to build out trait arrays
enum Ability GetBattlerTrait(enum BattlerId battlerId, u32 traitNum, bool32 ignoreMoldBreaker)
{
    bool32 hasAbilityShield = BattlerHasHeldItemEffectIgnoreAbility(battlerId, HOLD_EFFECT_ABILITY_SHIELD, TRUE);

    enum Ability ability = ABILITIES_COUNT;
    bool32 forcedTestInnate = FALSE;

    #if TESTING
    if (gTestRunnerEnabled)
    {
        u32 array = (!IsPartnerMonFromSameTrainer(battlerId)) ? battlerId : GetBattlerSide(battlerId);
        u32 partyIndex = gBattlerPartyIndexes[battlerId];
 
        if (T_SHOULD_TEST_DEFAULT_INNATES) // If TRUE, tests will use a pokemon's default Innates whenever one is not specified in the test.
        {
            if (traitNum > 0 && TestRunner_Battle_GetForcedInnates(array, partyIndex, traitNum - 1) != ABILITY_NONE)
            {
                ability = TestRunner_Battle_GetForcedInnates(array, partyIndex, traitNum - 1);
                forcedTestInnate = TRUE;
            }
        }
        else if (traitNum > 0)
        {
            ability = TestRunner_Battle_GetForcedInnates(array, partyIndex, traitNum - 1);
            forcedTestInnate = ability != ABILITY_NONE;
        }
    }
    #endif
        
    if (traitNum == 0){
        {
            //DebugPrintf("ABILITY: %S", gAbilitiesInfo[GetBattlerAbility(battlerId)].name);
            if (!ignoreMoldBreaker)
                return GetBattlerAbility(battlerId);
            else
                return GetBattlerAbilityIgnoreMoldBreaker(battlerId);
        }
    }
    else
    {
        // Load natural Innate if not a Test
        if (ability == ABILITIES_COUNT)
            ability = GetSpeciesInnate(gBattleMons[battlerId].species, traitNum);

        if (!forcedTestInnate && !IsInnateUnlockedByLevel(traitNum, gBattleMons[battlerId].level))
            return ABILITY_NONE;
        
        //DebugPrintf("Trait %d: %S", traitNum, gAbilitiesInfo[ability].name);
        
        // Check if ability is nullified
         if (battlerId != gBattlerAttacker
          && !ignoreMoldBreaker
          && CanBreakThroughAbility(gBattlerAttacker, battlerId, ability, hasAbilityShield, FALSE))
                return ABILITY_NONE;
        
        return ability;
    }
}

//Returns the slot the Innate is found in accouting for randomization and ability disabling. Assumes the Ability is already slot 1.  Returns 0 if not found.
u32 BattlerHasInnate(enum BattlerId battlerId, enum Ability ability)
{
    /*if (BattlerIgnoresAbility(gBattlerAttacker, battlerId, ability) && B_MOLD_BREAKER_WORKS_ON_INNATES == TRUE)
        return 0;
    else if (BattlerAbilityWasRemoved(battlerId, ability) && B_NEUTRALIZING_GAS_WORKS_ON_INNATES == TRUE)
        return 0;
    else*/

    //Check for Mold Breaker type negation
    if (battlerId != gBattlerAttacker
     && CanBreakThroughAbility(gBattlerAttacker, battlerId, ability, FALSE, FALSE))
        return 0;

#if TESTING
    if (gTestRunnerEnabled)
    {
        u32 array = (!IsPartnerMonFromSameTrainer(battlerId)) ? battlerId : GetBattlerSide(battlerId);
        u32 partyIndex = gBattlerPartyIndexes[battlerId];

        for (u32 i = 0; i < MAX_MON_INNATES; i++)
        {
            if (TestRunner_Battle_GetForcedInnates(array, partyIndex, i) == ability)
                return i + 2;
        }
    }
#endif

    for (u32 i = 0; i < MAX_MON_INNATES; i++)
    {
        if (gBattleMons[battlerId].innates[i] == ability
         && IsInnateUnlockedByLevel(i + 1, gBattleMons[battlerId].level))
            return i + 2;
    }

#if TESTING
    if (gTestRunnerEnabled && !T_SHOULD_TEST_DEFAULT_INNATES)
        return 0;
#endif

    return SpeciesHasInnateAtLevel(gBattleMons[battlerId].species, ability, gBattleMons[battlerId].level); 
}

static inline bool32 AiBattlerHasCachedHoldEffect(enum BattlerId battlerId, enum HoldEffect holdEffect)
{
    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (gAiLogicData->holdEffects[battlerId][i] == holdEffect)
            return TRUE;
    }

    return FALSE;
}

static inline u32 AiCachedBattlerTraitSlot(enum BattlerId battlerId, enum Ability ability)
{
    bool32 hasAbilityShield = AiBattlerHasCachedHoldEffect(battlerId, HOLD_EFFECT_ABILITY_SHIELD);

    if (gAiLogicData->abilities[battlerId] == ability)
    {
        if (CanBreakThroughAbility(gBattlerAttacker, battlerId, ability, hasAbilityShield, FALSE))
            return 0;
        return 1;
    }

    for (u32 i = 0; i < gAiLogicData->activeInnateCount[battlerId]; i++)
    {
        if (gAiLogicData->innates[battlerId][i] == ability)
        {
            if (CanBreakThroughAbility(gBattlerAttacker, battlerId, ability, hasAbilityShield, FALSE))
                return 0;
            return i + 2;
        }
    }

    return 0;
}

//Returns the trait slot number of the given ability. Starts at 1 for the primary Ability and returns 0 if the ability is not found. Use for individual checks.
u32 BattlerHasTrait(enum BattlerId battlerId, enum Ability ability) 
{
    u32 traitNum = 0;

    if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        return AiCachedBattlerTraitSlot(battlerId, ability);

    if (GetBattlerAbility(battlerId) == ability)
        traitNum = 1;
    else 
        traitNum = BattlerHasInnate(battlerId, ability);

    return traitNum;
}

//Used to search abilities for functions already under GetBattlerAbility to avoid infinite loops.
u32 BattlerHasTraitPlain(enum BattlerId battlerId, enum Ability ability)
{
    if (gBattleMons[battlerId].ability == ability)
        return 1;
    else 
        return BattlerHasInnate(battlerId, ability);
}

void PushTraitStack(enum BattlerId battlerId, enum Ability ability)
{
    if (battlerId >= MAX_BATTLERS_COUNT || ability <= ABILITY_NONE || ability >= ABILITIES_COUNT)
        return;

    for (u32 i = 0; i < ARRAY_COUNT(gTraitStack); i++)
    {
        if (gTraitStack[i][1] == ABILITY_NONE)
        {
            gTraitStack[i][0] = (enum Ability)battlerId;
            gTraitStack[i][1] = ability;
            //DebugPrintf("TRAIT STACK: Stack Slot: %d, Battler: %d, Ability: %S", i, gTraitStack[i][0], gAbilitiesInfo[gTraitStack[i][1]].name);
            return;
        }
    }

    DebugPrintf("Trait stack full");
}

u32 PullTraitStackBattler(void)
{
    for (s32 i = ARRAY_COUNT(gTraitStack) - 1; i >= 0; i--)
        if (gTraitStack[i][1] != ABILITY_NONE)
            return gTraitStack[i][0];

    return MAX_BATTLERS_COUNT;
}

enum Ability PullTraitStackAbility(void)
{
    for (s32 i = ARRAY_COUNT(gTraitStack) - 1; i >= 0; i--)
        if (gTraitStack[i][1] != ABILITY_NONE)
            return gTraitStack[i][1];

    return ABILITY_NONE;
}

void PopTraitStack(void)
{
    for (s32 i = ARRAY_COUNT(gTraitStack) - 1; i >= 0; i--)
    {
        if (gTraitStack[i][1] != ABILITY_NONE)
        {
            gTraitStack[i][0] = 0;
            gTraitStack[i][1] = ABILITY_NONE;
            return;
        }
    }
}

//Multiple Hold Items

bool32 BattlerHasHeldItemEffect(enum BattlerId battler, enum HoldEffect holdEffect, bool32 checkNegating)
{
    return BattlerHasHeldItemEffectInternal(battler, holdEffect, checkNegating, TRUE);
}

bool32 BattlerHasHeldItemEffectIgnoreAbility(enum BattlerId battler, enum HoldEffect holdEffect, bool32 checkNegating)
{
    return BattlerHasHeldItemEffectInternal(battler, holdEffect, checkNegating, FALSE);
}

//Check if the battler has an item with the given hold effect
bool32 BattlerHasHeldItemEffectInternal(enum BattlerId battler, enum HoldEffect holdEffect, bool32 checkNegating, bool32 checkAbility)
{
    if(battler >= MAX_BATTLERS_COUNT)
    {
        DebugPrintf("Invalid Battler: %d", battler);
        return FALSE;
    }

    if (holdEffect == HOLD_EFFECT_NONE)
        return FALSE;

    if (checkNegating)
    {
        if (gBattleMons[battler].volatiles.embargo)
            return FALSE;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return FALSE;
        if (checkAbility && BattlerHasTrait(battler, ABILITY_KLUTZ) && !gBattleMons[battler].volatiles.gastroAcid)
            return FALSE;
    }
    
    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        {
            if (gAiLogicData->holdEffects[battler][i] == holdEffect)
                return TRUE;
        }
        else if((GetItemHoldEffect(gBattleMons[battler].items[i]) == holdEffect))
            return TRUE;
    }
       return FALSE;
}

//Check if the battler has a given item
bool32 BattlerHasHeldItem(enum BattlerId battler, enum Item item, bool32 checkNegating)
{
    if(battler >= MAX_BATTLERS_COUNT)
    {
        DebugPrintf("Invalid Battler: %d", battler);
        return FALSE;
    }

    // Using ITEM_NONE returns TRUE if the battler has no items at all
    if (item == ITEM_NONE)
    {
        for (u32 i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
            {
                if (gAiLogicData->items[battler][i] != ITEM_NONE)
                    return FALSE;
            }
            else if((gBattleMons[battler].items[i] != ITEM_NONE))
                return FALSE;
        }
        return TRUE;
    }

    if (checkNegating)
    {
        if (gBattleMons[battler].volatiles.embargo)
            return FALSE;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return FALSE;
        if (BattlerHasKlutz(battler))
            return FALSE;
    }
    
    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        {
            if (gAiLogicData->items[battler][i] == item)
                return TRUE;
        }
        else if((gBattleMons[battler].items[i] == item))
            return TRUE;
    }
       return FALSE;
}

//Returns item with the given hold effect if present
u32 GetBattlerHeldItemWithEffect(enum BattlerId battler, enum HoldEffect holdEffect, bool32 checkNegating)
{
    enum Item item = ITEM_NONE;

    if(battler >= MAX_BATTLERS_COUNT)
    {
        DebugPrintf("Invalid Battler: %d", battler);
        return item;
    }

    if (checkNegating)
    {
        if (gBattleMons[battler].volatiles.embargo)
            return item;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return item;
        if (BattlerHasKlutz(battler))
            return item;
    }

    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        {
            if (gAiLogicData->holdEffects[battler][i] == holdEffect)
                return gAiLogicData->items[battler][i];
        }
        else
        {
            item = gBattleMons[battler].items[i];

            if(GetItemHoldEffect(item) == holdEffect)
                return item;
        }
    }
    return ITEM_NONE;
}

//Returns slot of the item with the given hold effect if present
u32 GetBattlerHeldItemSlotWithEffect(enum BattlerId battler, enum HoldEffect holdEffect, bool32 checkNegating)
{
    u32 slot = MAX_MON_ITEMS;

    if(battler >= MAX_BATTLERS_COUNT)
    {
        DebugPrintf("Invalid Battler: %d", battler);
        return slot;
    }

    if (checkNegating)
    {
        if (gBattleMons[battler].volatiles.embargo)
            return slot;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return slot;
        if (BattlerHasKlutz(battler))
            return slot;
    }

    if(battler >= MAX_BATTLERS_COUNT)
    {
        DebugPrintf("Invalid Battler: %d", battler);
        return slot;
    }

    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        {
            if (gAiLogicData->holdEffects[battler][i] == holdEffect)
                slot = i;
        }
        else if(GetItemHoldEffect(gBattleMons[battler].items[i]) == holdEffect)
            slot = i;
    }
    return slot;
}

//Returns item in the given slot
u32 GetSlotHeldItem(enum BattlerId battler, u32 slot, bool32 checkNegating)
{
    if (checkNegating)
    {
        if (gBattleMons[battler].volatiles.embargo)
            return ITEM_NONE;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return ITEM_NONE;
        if (BattlerHasKlutz(battler))
            return ITEM_NONE;
    }

    if(battler >= MAX_BATTLERS_COUNT)
    {
        DebugPrintf("Invalid Battler: %d", battler);
        return ITEM_NONE;
    }

    if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        return gAiLogicData->items[battler][slot];

    return gBattleMons[battler].items[slot];
}

//Returns item effect in the given slot
u32 GetSlotHeldItemEffect(enum BattlerId battler, u32 slot, bool32 checkNegating)
{
    if (checkNegating)
    {
        if (gBattleMons[battler].volatiles.embargo)
            return ITEM_NONE;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return ITEM_NONE;
        if (BattlerHasKlutz(battler))
            return ITEM_NONE;
    }

    if(battler >= MAX_BATTLERS_COUNT)
    {
        DebugPrintf("Invalid Battler: %d", battler);
        return ITEM_NONE;
    }

    if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        return gAiLogicData->holdEffects[battler][slot];

    return GetItemHoldEffect(gBattleMons[battler].items[slot]);
}

//Returns slot of the given item
u32 GetHeldItemSlot(enum BattlerId battler, enum Item itemId, bool32 checkNegating)
{
    u32 slot = MAX_MON_ITEMS;

    if (itemId == ITEM_NONE)
        return slot;

    if (checkNegating)
    {
        if (gBattleMons[battler].volatiles.embargo)
            return slot;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return slot;
        if (BattlerHasKlutz(battler))
            return slot;
    }

    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (gAiLogicData != NULL && gAiLogicData->aiCalcInProgress)
        {
            if (gAiLogicData->items[battler][i] == itemId)
                slot = i;
        }
        else if(gBattleMons[battler].items[i] == itemId)
            slot = i;
    }
    return slot;
}

//Gets next valid slot to add an item to based categorization flag and item's heldSlot value
u32 GetMonNextEmptySlot(struct Pokemon *mon, enum Item item)
{
    u32 i, slot = MAX_MON_ITEMS;

    //If categorization flag is enabled, items can only be sent to their assigned slots based on their heldSlot value.
    //Otherwise, items are first sent to empty available slots and if none are found, target the first item slot
    if (B_HELD_ITEM_CATEGORIZATION)
    {
        i = gItemsInfo[item].heldSlot;
        if (GetMonData(mon, MON_DATA_HELD_ITEM + i) == ITEM_NONE)
            slot = i;
    }
    else
    {
        for (i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (GetMonData(mon, MON_DATA_HELD_ITEM + i) == ITEM_NONE)
            {
                slot = i;
                break;
            }
        }
    }

    //Example Block for hybrid categorization where first two slots are free but third slot (2) only takes items marked
    // else
    // {
    //     if (gItemsInfo[item].heldSlot == 2)
    //     {
    //         slot = gItemsInfo[item].heldSlot;
    //     }
    //     else
    //     {
    //         for (int i = 0; i < MAX_MON_ITEMS; i++)
    //         {
    //             if (i != gItemsInfo[item].heldSlot && GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM + i) == ITEM_NONE)
    //             {
    //                 slot = i;
    //                 break;
    //             }
    //         }
    //     }
    // }

    return slot;
}

u32 GetBattlerNextEmptySlot(enum BattlerId battler, enum Item item)
{
    u32 i, slot = MAX_MON_ITEMS;

    //If categorization flag is enabled, items can only be sent to their assigned slots based on their heldSlot value.
    //Otherwise, items are first sent to empty available slots and if none are found, target the first item slot
    if (B_HELD_ITEM_CATEGORIZATION)
    {
        i = gItemsInfo[item].heldSlot;
        if (gBattleMons[battler].items[i] == ITEM_NONE)
            slot = i;
    }
    else
    {
        for (i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (gBattleMons[battler].items[i] == ITEM_NONE)
            {
                slot = i;
                break;
            }
        }
    }

    return slot;
}

//Takes a list of valid item slots for an effect and returns a targeted slot based on preferences
u32 GetSlot(u32 *availableSlots, u32 size)
{
    if (availableSlots[0] == MAX_MON_ITEMS) //MAX_MON_ITEMS is an invalid slot
    return MAX_MON_ITEMS;
    
    #if TESTING //Testing defaults to Proper Item Order 0
    for (u32 i = size; i >= 0; i--)
        {
                return availableSlots[i];
        } 
    #endif // TESTING
    
    // Returns slot of first found item based on B_MULTI_ITEM_ORDER
    //0 = latest to earliest, 1 = earliest to latest, 2 = random
    if(B_MULTI_ITEM_ORDER == 0)
        return gLastItemSlot = availableSlots[size];
    else if(B_MULTI_ITEM_ORDER == 1) 
        return gLastItemSlot = availableSlots[0];
    else if(B_MULTI_ITEM_ORDER == 2)
        return gLastItemSlot = availableSlots[Random() % size];
}

bool32 IsVictoryCatch(void)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_RAID | BATTLE_TYPE_BOSS))
        return TRUE;
    if (gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE))
        return FALSE;

    return (B_FLAG_VICTORY_CATCH_RANDOM != 0 && FlagGet(B_FLAG_VICTORY_CATCH_RANDOM))
        || (B_FLAG_VICTORY_CATCH_GUARANTEED != 0 && FlagGet(B_FLAG_VICTORY_CATCH_GUARANTEED));
}

bool32 IsVictoryCatchGuaranteed(void)
{
    return (gBattleTypeFlags & (BATTLE_TYPE_RAID | BATTLE_TYPE_BOSS))
        || (IsVictoryCatch()
         && B_FLAG_VICTORY_CATCH_GUARANTEED != 0
         && FlagGet(B_FLAG_VICTORY_CATCH_GUARANTEED));
}
