#include "global.h"
#include "battle_z_move.h"
#include "malloc.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_field_statuses.h"
#include "battle_ai_util.h"
#include "battle_ai_main.h"
#include "battle_factory.h"
#include "battle_setup.h"
#include "event_data.h"
#include "data.h"
#include "item.h"
#include "move.h"
#include "pokemon.h"
#include "random.h"
#include "recorded_battle.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_move_effects.h"
#include "constants/moves.h"
#include "constants/items.h"

static bool32 DoesBattlerBenefitFromWeather(u32 battler, u32 weather);
static bool32 DoesBattlerBenefitFromFieldStatus(u32 battler, u32 fieldStatus);
// A move is light sensitive if it is boosted by Sunny Day and weakened by low light weathers.
static bool32 IsLightSensitiveMove(enum Move move);
static bool32 HasLightSensitiveMove(enum BattlerId battler);
// The following functions all feed into WeatherChecker, which is then called by ShouldSetWeather and ShouldClearWeather.
// BenefitsFrom functions all return FIELD_EFFECT_POSITIVE if the weather or field effect is good to have in place from the perspective of the battler, FIELD_EFFECT_NEUTRAL if it is neither good nor bad, and FIELD_EFFECT_NEGATIVE if it is bad.
// The purpose of WeatherChecker and FieldStatusChecker is to cleanly homogenize the logic that's the same with all of them, and to more easily apply single battle logic to double battles.
// ShouldSetWeather and ShouldClearWeather are looking for a positive or negative result respectively, and check the entire side.
// If one pokemon has a positive result and the other has a negative result, it defaults to the opinion of the battler that may change the weather or field status.
static enum FieldEffectOutcome BenefitsFromSun(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromSandstorm(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromHailOrSnow(enum BattlerId battler, u32 weather);
static enum FieldEffectOutcome BenefitsFromRain(enum BattlerId battler);
// The following functions all feed into FieldStatusChecker, which is then called by ShouldSetFieldStatus and ShouldClearFieldStatus.
// They work approximately the same as the weather functions.
static enum FieldEffectOutcome BenefitsFromElectricTerrain(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromGrassyTerrain(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromMistyTerrain(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromPsychicTerrain(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromScorchedField(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromGravity(enum BattlerId battler);
static enum FieldEffectOutcome BenefitsFromTrickRoom(enum BattlerId battler);

static bool32 HasBattlerTerrainBoostMove(enum BattlerId battler, u32 terrain)
{
    if (!IsBattlerAlive(battler))
        return FALSE;

    enum Move *moves = GetMovesArray(battler);
    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        enum Move move = moves[moveIndex];
        if (GetMoveEffect(move) == EFFECT_TERRAIN_BOOST
         && GetMoveTerrainBoost_Terrain(move) == terrain)
            return TRUE;
    }

    return FALSE;
}

bool32 WeatherChecker(enum BattlerId battler, u32 weather, enum FieldEffectOutcome desiredResult)
{
    if (IsWeatherActive(B_WEATHER_PRIMAL_ANY) != WEATHER_INACTIVE)
        return (FIELD_EFFECT_BLOCKED == desiredResult);

    enum FieldEffectOutcome result = FIELD_EFFECT_NEUTRAL;
    enum FieldEffectOutcome firstResult = FIELD_EFFECT_NEUTRAL;

    u32 battlersOnSide = 1;

    if (HasPartner(battler))
        battlersOnSide = 2;

    for (u32 battlerIndex = 0; battlerIndex < battlersOnSide; battlerIndex++)
    {
        if (weather & B_WEATHER_RAIN)
            result = BenefitsFromRain(battler);
        else if (weather & B_WEATHER_SUN)
            result = BenefitsFromSun(battler);
        else if (weather & B_WEATHER_SANDSTORM)
            result = BenefitsFromSandstorm(battler);
        else if (weather & B_WEATHER_ICY_ANY)
            result = BenefitsFromHailOrSnow(battler, weather);

        battler = BATTLE_PARTNER(battler);

        if (result != FIELD_EFFECT_NEUTRAL)
        {
            if (weather & B_WEATHER_DAMAGING_ANY && battlerIndex == 0 && battlersOnSide == 2)
                firstResult = result;
        }
    }
    if (firstResult != FIELD_EFFECT_NEUTRAL)
        return (firstResult == result) && (result == desiredResult);
    return (result == desiredResult);
}

bool32 FieldStatusChecker(enum BattlerId battler, u32 fieldStatus, enum FieldEffectOutcome desiredResult)
{
    enum FieldEffectOutcome result = FIELD_EFFECT_NEUTRAL;
    enum FieldEffectOutcome firstResult = FIELD_EFFECT_NEUTRAL;

    u32 battlersOnSide = 1;

    if (HasPartner(battler))
        battlersOnSide = 2;

    for (u32 battlerIndex = 0; battlerIndex < battlersOnSide; battlerIndex++)
    {
        // terrains
        if (fieldStatus & STATUS_FIELD_ELECTRIC_TERRAIN)
            result = BenefitsFromElectricTerrain(battler);
        if (fieldStatus & STATUS_FIELD_GRASSY_TERRAIN)
            result = BenefitsFromGrassyTerrain(battler);
        if (fieldStatus & STATUS_FIELD_MISTY_TERRAIN)
            result = BenefitsFromMistyTerrain(battler);
        if (fieldStatus & STATUS_FIELD_PSYCHIC_TERRAIN)
            result = BenefitsFromPsychicTerrain(battler);
        if (fieldStatus & STATUS_FIELD_SCORCHED_FIELD)
            result = BenefitsFromScorchedField(battler);

        // other field statuses
        if (fieldStatus & STATUS_FIELD_GRAVITY)
            result = BenefitsFromGravity(battler);
        if (fieldStatus & STATUS_FIELD_TRICK_ROOM)
            result = BenefitsFromTrickRoom(battler);

        battler = BATTLE_PARTNER(battler);

        if (result != FIELD_EFFECT_NEUTRAL)
        {
            // Trick room wants both pokemon to agree, not just one
            if (fieldStatus & STATUS_FIELD_TRICK_ROOM && battlerIndex == 0 && battlersOnSide == 2)
                firstResult = result;
        }
    }
    if (firstResult != FIELD_EFFECT_NEUTRAL)
        return (firstResult == result) && (result == desiredResult);
    return (result == desiredResult);
}

static bool32 DoesBattlerBenefitFromWeather(u32 battler, u32 weather)
{
    enum Ability AIBattlerTraits[MAX_MON_TRAITS];
    AI_STORE_BATTLER_TRAITS(battler);

    if (SearchTraits(AIBattlerTraits, ABILITY_FORECAST))
        return (weather & (B_WEATHER_RAIN | B_WEATHER_SUN | B_WEATHER_ICY_ANY));
    if (SearchTraits(AIBattlerTraits, ABILITY_MAGIC_GUARD)
     || SearchTraits(AIBattlerTraits, ABILITY_OVERCOAT))
        return (weather & B_WEATHER_DAMAGING_ANY);
    if (SearchTraits(AIBattlerTraits, ABILITY_SAND_FORCE)
     || SearchTraits(AIBattlerTraits, ABILITY_SAND_RUSH)
     || SearchTraits(AIBattlerTraits, ABILITY_SAND_VEIL))
        return (weather & B_WEATHER_SANDSTORM);
    if (SearchTraits(AIBattlerTraits, ABILITY_ICE_BODY)
     || SearchTraits(AIBattlerTraits, ABILITY_ICE_FACE)
     || SearchTraits(AIBattlerTraits, ABILITY_SNOW_CLOAK))
        return (weather & B_WEATHER_ICY_ANY);
    if (SearchTraits(AIBattlerTraits, ABILITY_SLUSH_RUSH))
        return (weather & B_WEATHER_SNOW);
    if (SearchTraits(AIBattlerTraits, ABILITY_DRY_SKIN)
     || SearchTraits(AIBattlerTraits, ABILITY_HYDRATION)
     || SearchTraits(AIBattlerTraits, ABILITY_RAIN_DISH)
     || SearchTraits(AIBattlerTraits, ABILITY_SWIFT_SWIM))
        return (weather & B_WEATHER_RAIN);
    if (SearchTraits(AIBattlerTraits, ABILITY_CHLOROPHYLL)
     || SearchTraits(AIBattlerTraits, ABILITY_FLOWER_GIFT)
     || SearchTraits(AIBattlerTraits, ABILITY_HARVEST)
     || SearchTraits(AIBattlerTraits, ABILITY_LEAF_GUARD)
     || SearchTraits(AIBattlerTraits, ABILITY_ORICHALCUM_PULSE)
     || SearchTraits(AIBattlerTraits, ABILITY_PROTOSYNTHESIS)
     || SearchTraits(AIBattlerTraits, ABILITY_SOLAR_POWER))
        return (weather & B_WEATHER_SUN);

    return FALSE;
}

static bool32 DoesBattlerBenefitFromFieldStatus(u32 battler, u32 fieldStatus)
{
    enum Ability AIBattlerTraits[MAX_MON_TRAITS];
    AI_STORE_BATTLER_TRAITS(battler);

    if (SearchTraits(AIBattlerTraits, ABILITY_MIMICRY))
        return (fieldStatus & STATUS_FIELD_TERRAIN_ANY);
    if (SearchTraits(AIBattlerTraits, ABILITY_HADRON_ENGINE)
     || SearchTraits(AIBattlerTraits, ABILITY_QUARK_DRIVE)
     || SearchTraits(AIBattlerTraits, ABILITY_SURGE_SURFER))
        return (fieldStatus & STATUS_FIELD_ELECTRIC_TERRAIN);
    if (SearchTraits(AIBattlerTraits, ABILITY_GRASS_PELT))
        return (fieldStatus & STATUS_FIELD_GRASSY_TERRAIN);
    if (SearchTraits(AIBattlerTraits, ABILITY_ALLSEEING_IDOL))
        return (fieldStatus & STATUS_FIELD_GRAVITY);
    if (SearchTraits(AIBattlerTraits, ABILITY_ASH_ASSETS)
     || SearchTraits(AIBattlerTraits, ABILITY_LAVA_SURFER)
     || SearchTraits(AIBattlerTraits, ABILITY_COALWALKER))
        return (fieldStatus & STATUS_FIELD_SCORCHED_FIELD);
    // no abilities inherently benefit from Misty or Psychic Terrains
    // return (fieldStatus & STATUS_FIELD_MISTY_TERRAIN);
    // return (fieldStatus & STATUS_FIELD_PSYCHIC_TERRAIN);

    return FALSE;
}

static bool32 IsLightSensitiveMove(enum Move move)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_SOLAR_BEAM:
    case EFFECT_MORNING_SUN:
    case EFFECT_SYNTHESIS:
    case EFFECT_MOONLIGHT:
    case EFFECT_GROWTH:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 HasLightSensitiveMove(enum BattlerId battler)
{
    enum Move *moves = GetMovesArray(battler);

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE && IsLightSensitiveMove(moves[moveIndex]))
            return TRUE;
    }

    return FALSE;
}

// Sun
// Utility Umbrella does NOT block Ancient Pokemon from their stat boosts.
static enum FieldEffectOutcome BenefitsFromSun(enum BattlerId battler)
{
    enum Ability AIBattlerTraits[MAX_MON_TRAITS];
    AI_STORE_BATTLER_TRAITS(battler);

    if (Ai_BattlerHasHoldEffect(battler, HOLD_EFFECT_UTILITY_UMBRELLA, gAiLogicData))
    {
        if (SearchTraits(AIBattlerTraits, ABILITY_ORICHALCUM_PULSE) || SearchTraits(AIBattlerTraits, ABILITY_PROTOSYNTHESIS))
            return FIELD_EFFECT_POSITIVE;
        else
            return FIELD_EFFECT_NEUTRAL;
    }

    if (DoesBattlerBenefitFromWeather(battler, B_WEATHER_SUN)
    || HasLightSensitiveMove(battler)
    || HasDamagingMoveOfType(battler, TYPE_FIRE)
    || HasMoveWithEffect(battler, EFFECT_WEATHER_BALL)
    || HasMoveWithEffect(battler, EFFECT_HYDRO_STEAM))
        return FIELD_EFFECT_POSITIVE;

    if (HasMoveWithFlag(battler, MoveHas50AccuracyInSun) || HasDamagingMoveOfType(battler, TYPE_WATER) || SearchTraits(AIBattlerTraits, ABILITY_DRY_SKIN))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

// Sandstorm
static enum FieldEffectOutcome BenefitsFromSandstorm(enum BattlerId battler)
{
    if (DoesBattlerBenefitFromWeather(battler, B_WEATHER_SANDSTORM)
     || IS_BATTLER_OF_TYPE(battler, TYPE_ROCK)
     || HasMoveWithEffect(battler, EFFECT_WEATHER_BALL))
        return FIELD_EFFECT_POSITIVE;

    if (Ai_BattlerHasHoldEffect(battler, HOLD_EFFECT_SAFETY_GOGGLES, gAiLogicData) || IS_BATTLER_ANY_TYPE(battler, TYPE_ROCK, TYPE_GROUND, TYPE_STEEL))
    {
        if (!(IS_BATTLER_ANY_TYPE(LEFT_FOE(battler), TYPE_ROCK, TYPE_GROUND, TYPE_STEEL))
         || Ai_BattlerHasHoldEffect(LEFT_FOE(battler), HOLD_EFFECT_SAFETY_GOGGLES, gAiLogicData)
         || DoesBattlerBenefitFromWeather(LEFT_FOE(battler), B_WEATHER_SANDSTORM))
            return FIELD_EFFECT_POSITIVE;
        else
            return FIELD_EFFECT_NEUTRAL;
    }

    return FIELD_EFFECT_NEGATIVE;
}

// Hail or Snow
static enum FieldEffectOutcome BenefitsFromHailOrSnow(enum BattlerId battler, u32 weather)
{
    if (DoesBattlerBenefitFromWeather(battler, weather)
     || IS_BATTLER_OF_TYPE(battler, TYPE_ICE)
     || HasMoveWithEffect(battler, EFFECT_WEATHER_BALL)
     || HasMoveWithFlag(battler, MoveAlwaysHitsInHailSnow)
     || HasBattlerSideMoveWithEffect(battler, EFFECT_AURORA_VEIL))
        return FIELD_EFFECT_POSITIVE;

    if ((weather & B_WEATHER_DAMAGING_ANY) && !Ai_BattlerHasHoldEffect(battler, HOLD_EFFECT_SAFETY_GOGGLES, gAiLogicData))
        return FIELD_EFFECT_NEGATIVE;

    if (HasLightSensitiveMove(battler))
        return FIELD_EFFECT_NEGATIVE;

    if (HasMoveWithFlag(LEFT_FOE(battler), MoveAlwaysHitsInHailSnow))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

// Rain
static enum FieldEffectOutcome BenefitsFromRain(enum BattlerId battler)
{
    if (Ai_BattlerHasHoldEffect(battler, HOLD_EFFECT_UTILITY_UMBRELLA, gAiLogicData))
        return FIELD_EFFECT_NEUTRAL;

    if (DoesBattlerBenefitFromWeather(battler, B_WEATHER_RAIN)
      || HasMoveWithFlag(battler, MoveAlwaysHitsInRain)
      || HasDamagingMoveOfType(battler, TYPE_WATER)
      || HasMoveWithEffect(battler, EFFECT_WEATHER_BALL)
      || HasMove(battler, MOVE_ELECTRO_SHOT))
        return FIELD_EFFECT_POSITIVE;

    if (HasLightSensitiveMove(battler) || HasDamagingMoveOfType(battler, TYPE_FIRE))
        return FIELD_EFFECT_NEGATIVE;

    if (HasMoveWithFlag(LEFT_FOE(battler), MoveAlwaysHitsInRain))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

//TODO: when is electric terrain bad?
static enum FieldEffectOutcome BenefitsFromElectricTerrain(enum BattlerId battler)
{
    if (DoesBattlerBenefitFromFieldStatus(battler, STATUS_FIELD_ELECTRIC_TERRAIN))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerTerrainBoostMove(battler, STATUS_FIELD_ELECTRIC_TERRAIN))
        return FIELD_EFFECT_POSITIVE;

    if ((HasMoveWithEffect(LEFT_FOE(battler), EFFECT_REST) && AI_IsBattlerGrounded(LEFT_FOE(battler)))
     || (HasMoveWithEffect(RIGHT_FOE(battler), EFFECT_REST) && AI_IsBattlerGrounded(RIGHT_FOE(battler))))
        return FIELD_EFFECT_POSITIVE;

    bool32 grounded = AI_IsBattlerGrounded(battler);
    if (grounded && HasBattlerSideMoveWithAdditionalEffect(LEFT_FOE(battler), MOVE_EFFECT_SLEEP))
        return FIELD_EFFECT_POSITIVE;

    if (grounded && ((gBattleMons[battler].status1 & STATUS1_SLEEP)
    || gBattleMons[battler].volatiles.yawn
    || HasDamagingMoveOfType(battler, TYPE_ELECTRIC)))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerTerrainBoostMove(LEFT_FOE(battler), STATUS_FIELD_ELECTRIC_TERRAIN)
     || HasBattlerTerrainBoostMove(RIGHT_FOE(battler), STATUS_FIELD_ELECTRIC_TERRAIN))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

//TODO: when is grassy terrain bad?
static enum FieldEffectOutcome BenefitsFromGrassyTerrain(enum BattlerId battler)
{
    if (DoesBattlerBenefitFromFieldStatus(battler, STATUS_FIELD_GRASSY_TERRAIN))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerSideMoveWithEffect(battler, EFFECT_GRASSY_GLIDE))
        return FIELD_EFFECT_POSITIVE;
    if (HasMoveWithAdditionalEffect(battler, MOVE_EFFECT_FLORAL_HEALING))
        return FIELD_EFFECT_POSITIVE;

    bool32 grounded = AI_IsBattlerGrounded(battler);

    // Weaken spamming Earthquake, Magnitude, and Bulldoze.
    if (grounded && (HasBattlerSideMoveWithEffect(LEFT_FOE(battler), EFFECT_EARTHQUAKE)
    || HasBattlerSideMoveWithEffect(LEFT_FOE(battler), EFFECT_MAGNITUDE)))
        return FIELD_EFFECT_POSITIVE;

    if (grounded && HasDamagingMoveOfType(battler, TYPE_GRASS))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerSideMoveWithEffect(LEFT_FOE(battler), EFFECT_GRASSY_GLIDE))
        return FIELD_EFFECT_NEGATIVE;


    return FIELD_EFFECT_NEUTRAL;
}

//TODO: when is misty terrain bad?
static enum FieldEffectOutcome BenefitsFromMistyTerrain(enum BattlerId battler)
{
    if (DoesBattlerBenefitFromFieldStatus(battler, STATUS_FIELD_MISTY_TERRAIN))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerTerrainBoostMove(battler, STATUS_FIELD_MISTY_TERRAIN)
     || HasBattlerTerrainBoostMove(BATTLE_PARTNER(battler), STATUS_FIELD_MISTY_TERRAIN))
        return FIELD_EFFECT_POSITIVE;

    bool32 grounded = AI_IsBattlerGrounded(battler);
    bool32 allyGrounded = FALSE;
    if (HasPartner(battler))
        allyGrounded = AI_IsBattlerGrounded(BATTLE_PARTNER(battler));

    if ((HasMoveWithEffect(LEFT_FOE(battler), EFFECT_REST) && AI_IsBattlerGrounded(LEFT_FOE(battler)))
     || (HasMoveWithEffect(RIGHT_FOE(battler), EFFECT_REST) && AI_IsBattlerGrounded(RIGHT_FOE(battler))))
        return FIELD_EFFECT_POSITIVE;

    // harass dragons
    if ((grounded || allyGrounded)
     && (HasDamagingMoveOfType(LEFT_FOE(battler), TYPE_DRAGON) || HasDamagingMoveOfType(RIGHT_FOE(battler), TYPE_DRAGON)))
        return FIELD_EFFECT_POSITIVE;

    if ((grounded || allyGrounded)
     && (HasNonVolatileMoveEffect(LEFT_FOE(battler), MOVE_EFFECT_SLEEP) || HasNonVolatileMoveEffect(RIGHT_FOE(battler), MOVE_EFFECT_SLEEP)))
        return FIELD_EFFECT_POSITIVE;

    if (grounded && (gBattleMons[battler].status1 & STATUS1_SLEEP || gBattleMons[battler].volatiles.yawn))
        return FIELD_EFFECT_POSITIVE;

    return FIELD_EFFECT_NEUTRAL;
}

//TODO: when is Psychic Terrain negative?
static enum FieldEffectOutcome BenefitsFromPsychicTerrain(enum BattlerId battler)
{
    if (DoesBattlerBenefitFromFieldStatus(battler, STATUS_FIELD_PSYCHIC_TERRAIN))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerTerrainBoostMove(battler, STATUS_FIELD_PSYCHIC_TERRAIN)
     || HasBattlerTerrainBoostMove(BATTLE_PARTNER(battler), STATUS_FIELD_PSYCHIC_TERRAIN))
        return FIELD_EFFECT_POSITIVE;

    bool32 grounded = AI_IsBattlerGrounded(battler);
    bool32 allyGrounded = FALSE;
    if (HasPartner(battler))
        allyGrounded = AI_IsBattlerGrounded(BATTLE_PARTNER(battler));

    // don't bother if we're not grounded
    if (grounded || allyGrounded)
    {
        // harass priority
        if (AI_IsAbilityOnSide(LEFT_FOE(battler), ABILITY_GALE_WINGS)
         || AI_IsAbilityOnSide(LEFT_FOE(battler), ABILITY_TRIAGE)
         || AI_IsAbilityOnSide(LEFT_FOE(battler), ABILITY_PRANKSTER))
            return FIELD_EFFECT_POSITIVE;
    }

    if (grounded && HasDamagingMoveOfType(battler, TYPE_PSYCHIC))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerTerrainBoostMove(LEFT_FOE(battler), STATUS_FIELD_PSYCHIC_TERRAIN)
     || HasBattlerTerrainBoostMove(RIGHT_FOE(battler), STATUS_FIELD_PSYCHIC_TERRAIN))
        return FIELD_EFFECT_NEGATIVE;

    if (AI_IsAbilityOnSide(battler, ABILITY_GALE_WINGS)
     || AI_IsAbilityOnSide(battler, ABILITY_TRIAGE)
     || AI_IsAbilityOnSide(battler, ABILITY_PRANKSTER))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}
static enum FieldEffectOutcome BenefitsFromScorchedField(enum BattlerId battler)
{
    if (DoesBattlerBenefitFromFieldStatus(battler, STATUS_FIELD_SCORCHED_FIELD))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerTerrainBoostMove(battler, STATUS_FIELD_SCORCHED_FIELD)
     || HasBattlerTerrainBoostMove(BATTLE_PARTNER(battler), STATUS_FIELD_SCORCHED_FIELD))
        return FIELD_EFFECT_POSITIVE;

    bool32 grounded = AI_IsBattlerGrounded(battler);
    bool32 allyGrounded = FALSE;
    if (HasPartner(battler))
        allyGrounded = AI_IsBattlerGrounded(BATTLE_PARTNER(battler));

    // don't bother if we're not grounded
    if (grounded || allyGrounded)
    {
        // harass priority
        if (AI_IsAbilityOnSide(LEFT_FOE(battler), ABILITY_GALE_WINGS)
         || AI_IsAbilityOnSide(LEFT_FOE(battler), ABILITY_TRIAGE)
         || AI_IsAbilityOnSide(LEFT_FOE(battler), ABILITY_PRANKSTER))
            return FIELD_EFFECT_POSITIVE;
    }

    if (grounded && HasDamagingMoveOfType(battler, TYPE_FIRE))
        return FIELD_EFFECT_POSITIVE;

    if (HasBattlerTerrainBoostMove(LEFT_FOE(battler), STATUS_FIELD_PSYCHIC_TERRAIN)
     || HasBattlerTerrainBoostMove(RIGHT_FOE(battler), STATUS_FIELD_PSYCHIC_TERRAIN))
        return FIELD_EFFECT_NEGATIVE;

    if (AI_IsAbilityOnSide(battler, ABILITY_GALE_WINGS)
     || AI_IsAbilityOnSide(battler, ABILITY_TRIAGE)
     || AI_IsAbilityOnSide(battler, ABILITY_PRANKSTER))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

static enum FieldEffectOutcome BenefitsFromGravity(enum BattlerId battler)
{
    if (AI_BATTLER_HAS_TRAIT(battler, ABILITY_ALLSEEING_IDOL))
        return FIELD_EFFECT_POSITIVE;

    if (!AI_IsBattlerGrounded(battler))
        return FIELD_EFFECT_NEGATIVE;

    if (AI_IsAbilityOnSide(battler, ABILITY_HUSTLE))
        return FIELD_EFFECT_POSITIVE;

    if (HasMoveWithFlag(battler, IsMoveGravityBanned))
        return FIELD_EFFECT_NEGATIVE;

    if (IsBattlerAlive(LEFT_FOE(battler)))
    {
        if (HasMoveWithLowAccuracy(battler, LEFT_FOE(battler), LOW_ACCURACY_THRESHOLD, FALSE)
         || (!AI_IsBattlerGrounded(LEFT_FOE(battler)) && HasDamagingMoveOfType(battler, TYPE_GROUND)))
            return FIELD_EFFECT_POSITIVE;
    }

    if (IsBattlerAlive(RIGHT_FOE(battler)))
    {
        if (HasMoveWithLowAccuracy(battler, RIGHT_FOE(battler), LOW_ACCURACY_THRESHOLD, FALSE)
         || (!AI_IsBattlerGrounded(RIGHT_FOE(battler)) && HasDamagingMoveOfType(battler, TYPE_GROUND)))
            return FIELD_EFFECT_POSITIVE;
    }

    return FIELD_EFFECT_NEUTRAL;
}

static enum FieldEffectOutcome BenefitsFromTrickRoom(enum BattlerId battler)
{
    // If we're in singles, we literally only care about speed.
    if (IsBattle1v1())
    {
        if (gAiLogicData->speedStats[battler] < gAiLogicData->speedStats[LEFT_FOE(battler)])
            return FIELD_EFFECT_POSITIVE;
        // If we tie, we shouldn't change trick room state.
        else if (gAiLogicData->speedStats[battler] == gAiLogicData->speedStats[LEFT_FOE(battler)])
            return FIELD_EFFECT_NEUTRAL;
        else
            return FIELD_EFFECT_NEGATIVE;
    }

    // First checking if we have enough priority for one pokemon to disregard Trick Room entirely.
    if (!(gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN))
    {
        enum Move *aiMoves = GetMovesArray(battler);
        for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            enum Move move = aiMoves[moveIndex];
            if (GetBattleMovePriority(battler, move) > 0 && !(GetMovePriority(move) > 0 && IsBattleMoveStatus(move)))
            {
                return FIELD_EFFECT_POSITIVE;
            }
        }
    }

    // If we are faster or tie, we don't want trick room.
    if ((gAiLogicData->speedStats[battler] >= gAiLogicData->speedStats[LEFT_FOE(battler)]) || (gAiLogicData->speedStats[battler] >= gAiLogicData->speedStats[RIGHT_FOE(battler)]))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_POSITIVE;
}

s32 CalcWeatherScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, struct AiLogicData *aiData)
{
    s32 score = 0;

    switch (GetMoveWeatherType(move))
    {
    case BATTLE_WEATHER_RAIN:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_RAIN))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
            if (Ai_BattlerHasHoldEffect(battlerAtk, HOLD_EFFECT_DAMP_ROCK, aiData))
                score += WEAK_EFFECT;
            if (HasBattlerSideMoveWithEffect(battlerDef, EFFECT_MORNING_SUN)
             || HasBattlerSideMoveWithEffect(battlerDef, EFFECT_SYNTHESIS)
             || HasBattlerSideMoveWithEffect(battlerDef, EFFECT_SOLAR_BEAM)
             || HasBattlerSideMoveWithEffect(battlerDef, EFFECT_MOONLIGHT))
                score += WEAK_EFFECT;
            if (HasDamagingMoveOfType(battlerDef, TYPE_FIRE) || HasDamagingMoveOfType(BATTLE_PARTNER(battlerDef), TYPE_FIRE))
                score += WEAK_EFFECT;
        }
        break;
    case BATTLE_WEATHER_SUN:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_SUN))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
            if (Ai_BattlerHasHoldEffect(battlerAtk, HOLD_EFFECT_HEAT_ROCK, aiData))
                score += WEAK_EFFECT;
            if (HasDamagingMoveOfType(battlerDef, TYPE_WATER) || HasDamagingMoveOfType(BATTLE_PARTNER(battlerDef), TYPE_WATER))
                score += WEAK_EFFECT;
            if (HasMoveWithFlag(battlerDef, MoveHas50AccuracyInSun) || HasMoveWithFlag(BATTLE_PARTNER(battlerDef), MoveHas50AccuracyInSun))
                score += WEAK_EFFECT;
        }
        break;
    case BATTLE_WEATHER_SANDSTORM:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_SANDSTORM))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
            if (Ai_BattlerHasHoldEffect(battlerAtk, HOLD_EFFECT_SMOOTH_ROCK, aiData))
                score += WEAK_EFFECT;
            if (HasMoveWithEffect(battlerDef, EFFECT_MORNING_SUN)
             || HasMoveWithEffect(battlerDef, EFFECT_SYNTHESIS)
             || HasMoveWithEffect(battlerDef, EFFECT_MOONLIGHT))
                score += WEAK_EFFECT;
        }
        break;
    case BATTLE_WEATHER_HAIL:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_HAIL))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_AURORA_VEIL) && ShouldSetScreen(battlerAtk, battlerDef, EFFECT_AURORA_VEIL))
                score += GOOD_EFFECT;
            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
            if (Ai_BattlerHasHoldEffect(battlerAtk, HOLD_EFFECT_ICY_ROCK, aiData))
                score += WEAK_EFFECT;
            if (HasMoveWithEffect(battlerDef, EFFECT_MORNING_SUN)
             || HasMoveWithEffect(battlerDef, EFFECT_SYNTHESIS)
             || HasMoveWithEffect(battlerDef, EFFECT_MOONLIGHT))
                score += WEAK_EFFECT;
        }
        break;
    case BATTLE_WEATHER_SNOW:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_SNOW))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_AURORA_VEIL) && ShouldSetScreen(battlerAtk, battlerDef, EFFECT_AURORA_VEIL))
                score += GOOD_EFFECT;
            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
            if (Ai_BattlerHasHoldEffect(battlerAtk, HOLD_EFFECT_ICY_ROCK, aiData))
                score += WEAK_EFFECT;
            if (HasMoveWithEffect(battlerDef, EFFECT_MORNING_SUN)
             || HasMoveWithEffect(battlerDef, EFFECT_SYNTHESIS)
             || HasMoveWithEffect(battlerDef, EFFECT_MOONLIGHT))
                score += WEAK_EFFECT;
        }
        break;
    }

    return score;
}
