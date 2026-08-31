#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "move.h"
#include "pokemon.h"
#include "trainer_moves.h"

#include "constants/battle_move_effects.h"
#include "constants/difficulty.h"

#define TRAINER_MOVE_SCORE_REJECT (-10000)
#define TRAINER_MOVE_SEEN_BYTES DIV_ROUND_UP(MOVES_COUNT, 8)
#define HARD_TRAINER_BASIC_TEACHABLE_LEVEL 33
#define HARD_TRAINER_ADVANCED_TEACHABLE_LEVEL 43
#define HARD_TRAINER_FULL_TEACHABLE_LEVEL 50
#define HARD_TRAINER_BASIC_TEACHABLE_MAX_POWER 80
#define HARD_TRAINER_HIGH_POWER_TEACHABLE_MIN_POWER 100

enum TrainerMoveSource
{
    TRAINER_MOVE_SOURCE_LEVEL_UP,
    TRAINER_MOVE_SOURCE_TEACHABLE,
};

enum TrainerMoveRole
{
    TRAINER_MOVE_ROLE_NONE,
    TRAINER_MOVE_ROLE_RECOVERY,
    TRAINER_MOVE_ROLE_PHYSICAL_SETUP,
    TRAINER_MOVE_ROLE_SPECIAL_SETUP,
    TRAINER_MOVE_ROLE_MIXED_SETUP,
    TRAINER_MOVE_ROLE_SPEED_SETUP,
    TRAINER_MOVE_ROLE_STATUS,
    TRAINER_MOVE_ROLE_ALLY_SUPPORT,
    TRAINER_MOVE_ROLE_SCREEN,
    TRAINER_MOVE_ROLE_HAZARD,
    TRAINER_MOVE_ROLE_SPEED_CONTROL,
    TRAINER_MOVE_ROLE_PROTECT,
    TRAINER_MOVE_ROLE_DISRUPTION,
    TRAINER_MOVE_ROLE_PARTY_SUPPORT,
    TRAINER_MOVE_ROLE_WEATHER_TERRAIN,
    TRAINER_MOVE_ROLE_SACRIFICE,
    TRAINER_MOVE_ROLE_OTHER,
    TRAINER_MOVE_ROLE_NO_OP,
};

struct TrainerMoveCandidate
{
    enum Move move;
    enum TrainerMoveSource source;
    u16 order;
};

struct TrainerMoveContext
{
    const struct TrainerMon *partyEntry;
    u16 species;
    u8 level;
    enum TrainerBattleType battleType;
};

struct TrainerMoveSelection
{
    enum Move moves[MAX_MON_MOVES];
    u8 count;
};

static s32 ClampTrainerMoveScore(s32 value, s32 minValue, s32 maxValue)
{
    if (value < minValue)
        return minValue;
    if (value > maxValue)
        return maxValue;
    return value;
}

static bool32 IsValidAutomaticTrainerMove(enum Move move)
{
    return move > MOVE_NONE
        && move < MOVES_COUNT
        && GetMoveEffect(move) != EFFECT_PLACEHOLDER;
}

static enum Move SanitizeTrainerMove(enum Move move)
{
    assertf(move < MOVES_COUNT, "invalid trainer move: %d", move)
    {
        return MOVE_NONE;
    }
    return move;
}

bool32 TrainerMonHasExplicitMoves(const struct TrainerMon *partyEntry)
{
    u32 i;

    if (partyEntry->hasExplicitMoves)
        return TRUE;

    // Preserve compatibility with TrainerMon data authored directly in C.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (partyEntry->moves[i] != MOVE_NONE)
            return TRUE;
    }
    return FALSE;
}

bool32 IsAutomaticTrainerMoveSuitableForSingles(enum Move move)
{
    enum BattleMoveEffects effect;

    if (!IsValidAutomaticTrainerMove(move))
        return FALSE;
    if (GetMoveTarget(move) == TARGET_ALLY)
        return FALSE;
    if (GetMoveEffect(move) == EFFECT_PROTECT
     && GetMoveProtectMethod(move) == PROTECT_WIDE_GUARD)
        return FALSE;

    effect = GetMoveEffect(move);
    switch (effect)
    {
    case EFFECT_HELPING_HAND:
    case EFFECT_FOLLOW_ME:
    case EFFECT_ALLY_SWITCH:
    case EFFECT_HEAL_PULSE:
    case EFFECT_AFTER_YOU:
    case EFFECT_QUASH:
    case EFFECT_INSTRUCT:
    case EFFECT_AROMATIC_MIST:
    case EFFECT_COACHING:
    case EFFECT_DECORATE:
    case EFFECT_HOLD_HANDS:
        return FALSE;
    default:
        return TRUE;
    }
}

static bool32 IsHardTrainerMoveUnsupported(enum Move move)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_DREAM_EATER:
    case EFFECT_SNORE:
    case EFFECT_SLEEP_TALK:
    case EFFECT_ASSIST:
    case EFFECT_SPIT_UP:
    case EFFECT_SWALLOW:
    case EFFECT_FLING:
    case EFFECT_NATURAL_GIFT:
    case EFFECT_LAST_RESORT:
    case EFFECT_BELCH:
    case EFFECT_STEEL_ROLLER:
    case EFFECT_DO_NOTHING:
    case EFFECT_CELEBRATE:
    case EFFECT_HAPPY_HOUR:
    case EFFECT_HOLD_HANDS:
        return TRUE;
    default:
        return FALSE;
    }
}

static void BuildLatestLevelUpTrainerMoves(enum Move outMoves[MAX_MON_MOVES],
                                           u16 species,
                                           u8 level,
                                           bool32 filterSingles)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
    u32 i;
    u8 addedMoves = 0;

    for (i = 0; i < MAX_MON_MOVES; i++)
        outMoves[i] = MOVE_NONE;

    for (i = 0; i < MAX_LEVEL_UP_MOVES && learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        enum Move move = learnset[i].move;
        bool32 alreadyKnown = FALSE;
        u32 j;

        if (learnset[i].level > level)
            break;
        if (learnset[i].level == 0 || !IsValidAutomaticTrainerMove(move))
            continue;
        if (filterSingles && !IsAutomaticTrainerMoveSuitableForSingles(move))
            continue;

        // Deliberately match GiveBoxMonInitialMoveset: duplicates are checked
        // only against the four moves still retained in the sliding window.
        for (j = 0; j < addedMoves; j++)
        {
            if (outMoves[j] == move)
            {
                alreadyKnown = TRUE;
                break;
            }
        }

        if (!alreadyKnown)
        {
            if (addedMoves < MAX_MON_MOVES)
            {
                outMoves[addedMoves++] = move;
            }
            else
            {
                for (j = 0; j < MAX_MON_MOVES - 1; j++)
                    outMoves[j] = outMoves[j + 1];
                outMoves[MAX_MON_MOVES - 1] = move;
            }
        }
    }
}

static bool32 IsMoveSeen(const u8 seen[TRAINER_MOVE_SEEN_BYTES], enum Move move)
{
    return seen[move / 8] & (1u << (move % 8));
}

static void SetMoveSeen(u8 seen[TRAINER_MOVE_SEEN_BYTES], enum Move move)
{
    seen[move / 8] |= 1u << (move % 8);
}

static bool32 SelectionHasMove(const struct TrainerMoveSelection *selection, enum Move move)
{
    u32 i;

    for (i = 0; i < selection->count; i++)
    {
        if (selection->moves[i] == move)
            return TRUE;
    }
    return FALSE;
}

static bool32 IsDamagingTrainerMove(enum Move move)
{
    return GetMoveCategory(move) != DAMAGE_CATEGORY_STATUS;
}

static enum Type GetAutomaticTrainerMoveType(enum Move move, u16 species)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_HIDDEN_POWER:
        // Its actual type depends on IVs, which are outside this first-pass
        // scorer. Do not incorrectly count the metadata's Normal type as STAB.
        return TYPE_NONE;
    case EFFECT_REVELATION_DANCE:
        return GetSpeciesType(species, 0);
    default:
        return GetMoveType(move);
    }
}

bool32 IsTrainerMoveStab(enum Move move, u16 species, u8 level)
{
    enum Type type = GetAutomaticTrainerMoveType(move, species);

    return type != TYPE_NONE
        && (type == GetSpeciesType(species, 0)
         || type == GetSpeciesType(species, 1)
         || (type == TYPE_DRAGON && SpeciesHasInnateAtLevel(species, ABILITY_LIKE_A_DRAGON, level)));
}

static u32 GetTrainerMoveNominalPower(const struct TrainerMoveContext *ctx, enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    u32 power = GetMovePower(move);

    switch (effect)
    {
    case EFFECT_RETURN:
        return 10 * ctx->partyEntry->friendship / 25;
    case EFFECT_FRUSTRATION:
        return 10 * (MAX_FRIENDSHIP - ctx->partyEntry->friendship) / 25;
    case EFFECT_HIDDEN_POWER:
        return power <= 1 ? 60 : power;
    case EFFECT_FIXED_HP_DAMAGE:
        return min(100, GetMoveFixedHPDamage(move) * 2);
    case EFFECT_LEVEL_DAMAGE:
        return min(100, ctx->level * 2);
    case EFFECT_FIXED_PERCENT_DAMAGE:
        return 70;
    case EFFECT_REFLECT_DAMAGE:
        return 75;
    case EFFECT_OHKO:
        return 100;
    case EFFECT_PSYWAVE:
        return 60;
    case EFFECT_PRESENT:
        return 50;
    case EFFECT_MAGNITUDE:
        return 71;
    case EFFECT_FLAIL:
    case EFFECT_POWER_BASED_ON_USER_HP:
    case EFFECT_POWER_BASED_ON_TARGET_HP:
    case EFFECT_LOW_KICK:
    case EFFECT_HEAT_CRASH:
    case EFFECT_ELECTRO_BALL:
    case EFFECT_GYRO_BALL:
    case EFFECT_PUNISHMENT:
    case EFFECT_STORED_POWER:
    case EFFECT_TRUMP_CARD:
        return 65;
    case EFFECT_ENDEAVOR:
    case EFFECT_FINAL_GAMBIT:
        return 70;
    case EFFECT_BEAT_UP:
        return 60;
    case EFFECT_LAST_RESPECTS:
    case EFFECT_RAGE_FIST:
        return 75;
    case EFFECT_SPECIES_POWER_OVERRIDE:
        return GetMoveSpeciesPowerOverride_Power(move);
    default:
        // A power of 1 is used by many effect-driven attacks in this fork.
        // Keep unknown future cases viable without letting them dominate.
        return power <= 1 ? 50 : power;
    }
}

static s32 GetTrainerMoveOffenseAdjustment(const struct TrainerMoveContext *ctx, enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    u32 attack = GetSpeciesBaseAttack(ctx->species);
    u32 specialAttack = GetSpeciesBaseSpAttack(ctx->species);
    s32 relevant;
    s32 other;

    if (effect == EFFECT_FOUL_PLAY)
        return 0;
    if (effect == EFFECT_BODY_PRESS)
    {
        relevant = GetSpeciesBaseDefense(ctx->species);
        other = max(attack, specialAttack);
    }
    else if (effect == EFFECT_PHOTON_GEYSER || effect == EFFECT_SHELL_SIDE_ARM)
    {
        relevant = max(attack, specialAttack);
        other = min(attack, specialAttack);
    }
    else if (GetMoveCategory(move) == DAMAGE_CATEGORY_PHYSICAL)
    {
        relevant = attack;
        other = specialAttack;
    }
    else
    {
        relevant = specialAttack;
        other = attack;
    }

    return ClampTrainerMoveScore((relevant - other) / 5, -12, 12);
}

static enum TrainerMoveRole GetTrainerMoveRole(enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);

    switch (effect)
    {
    case EFFECT_RESTORE_HP:
    case EFFECT_REST:
    case EFFECT_MORNING_SUN:
    case EFFECT_SYNTHESIS:
    case EFFECT_MOONLIGHT:
    case EFFECT_SOFTBOILED:
    case EFFECT_WISH:
    case EFFECT_INGRAIN:
    case EFFECT_AQUA_RING:
    case EFFECT_ROOST:
    case EFFECT_STRENGTH_SAP:
    case EFFECT_SHORE_UP:
        return TRAINER_MOVE_ROLE_RECOVERY;

    case EFFECT_ATTACK_UP:
    case EFFECT_ATTACK_UP_2:
    case EFFECT_ATTACK_ACCURACY_UP:
    case EFFECT_BELLY_DRUM:
    case EFFECT_BULK_UP:
    case EFFECT_DRAGON_DANCE:
    case EFFECT_COIL:
    case EFFECT_SHIFT_GEAR:
    case EFFECT_VICTORY_DANCE:
    case EFFECT_TIDY_UP:
        return TRAINER_MOVE_ROLE_PHYSICAL_SETUP;

    case EFFECT_SPECIAL_ATTACK_UP:
    case EFFECT_SPECIAL_ATTACK_UP_2:
    case EFFECT_SPECIAL_ATTACK_UP_3:
    case EFFECT_CALM_MIND:
    case EFFECT_QUIVER_DANCE:
    case EFFECT_GEOMANCY:
    case EFFECT_TAKE_HEART:
        return TRAINER_MOVE_ROLE_SPECIAL_SETUP;

    case EFFECT_ATTACK_SPATK_UP:
    case EFFECT_GROWTH:
    case EFFECT_SHELL_SMASH:
    case EFFECT_NO_RETREAT:
    case EFFECT_CLANGOROUS_SOUL:
    case EFFECT_EXTREME_EVOBOOST:
    case EFFECT_FILLET_AWAY:
        return TRAINER_MOVE_ROLE_MIXED_SETUP;

    case EFFECT_SPEED_UP:
    case EFFECT_SPEED_UP_2:
    case EFFECT_AUTOTOMIZE:
        return TRAINER_MOVE_ROLE_SPEED_SETUP;

    case EFFECT_NON_VOLATILE_STATUS:
    case EFFECT_YAWN:
    case EFFECT_DARK_VOID:
        return TRAINER_MOVE_ROLE_STATUS;

    case EFFECT_HELPING_HAND:
    case EFFECT_FOLLOW_ME:
    case EFFECT_ALLY_SWITCH:
    case EFFECT_HEAL_PULSE:
    case EFFECT_AFTER_YOU:
    case EFFECT_QUASH:
    case EFFECT_INSTRUCT:
    case EFFECT_AROMATIC_MIST:
    case EFFECT_COACHING:
    case EFFECT_DECORATE:
        return TRAINER_MOVE_ROLE_ALLY_SUPPORT;

    case EFFECT_LIGHT_SCREEN:
    case EFFECT_REFLECT:
    case EFFECT_AURORA_VEIL:
    case EFFECT_SAFEGUARD:
        return TRAINER_MOVE_ROLE_SCREEN;

    case EFFECT_SPIKES:
    case EFFECT_TOXIC_SPIKES:
    case EFFECT_STEALTH_ROCK:
    case EFFECT_STICKY_WEB:
        return TRAINER_MOVE_ROLE_HAZARD;

    case EFFECT_TAILWIND:
    case EFFECT_TRICK_ROOM:
    case EFFECT_SPEED_DOWN:
    case EFFECT_SPEED_DOWN_2:
        return TRAINER_MOVE_ROLE_SPEED_CONTROL;

    case EFFECT_PROTECT:
    case EFFECT_ENDURE:
    case EFFECT_MAT_BLOCK:
        return TRAINER_MOVE_ROLE_PROTECT;

    case EFFECT_DISABLE:
    case EFFECT_HAZE:
    case EFFECT_ROAR:
    case EFFECT_CONFUSE:
    case EFFECT_LEECH_SEED:
    case EFFECT_ENCORE:
    case EFFECT_MEAN_LOOK:
    case EFFECT_PERISH_SONG:
    case EFFECT_ATTRACT:
    case EFFECT_TORMENT:
    case EFFECT_TAUNT:
    case EFFECT_IMPRISON:
    case EFFECT_GRAVITY:
    case EFFECT_EMBARGO:
    case EFFECT_MAGIC_ROOM:
    case EFFECT_WONDER_ROOM:
    case EFFECT_GASTRO_ACID:
    case EFFECT_TOPSY_TURVY:
    case EFFECT_FAIRY_LOCK:
    case EFFECT_OCTOLOCK:
        return TRAINER_MOVE_ROLE_DISRUPTION;

    case EFFECT_HEAL_BELL:
    case EFFECT_REFRESH:
    case EFFECT_LIFE_DEW:
    case EFFECT_JUNGLE_HEALING:
    case EFFECT_REVIVAL_BLESSING:
        return TRAINER_MOVE_ROLE_PARTY_SUPPORT;

    case EFFECT_WEATHER:
    case EFFECT_WEATHER_AND_SWITCH:
    case EFFECT_MISTY_TERRAIN:
    case EFFECT_GRASSY_TERRAIN:
    case EFFECT_ELECTRIC_TERRAIN:
    case EFFECT_PSYCHIC_TERRAIN:
        return TRAINER_MOVE_ROLE_WEATHER_TERRAIN;

    case EFFECT_HEALING_WISH:
    case EFFECT_LUNAR_DANCE:
    case EFFECT_MEMENTO:
    case EFFECT_SHED_TAIL:
        return TRAINER_MOVE_ROLE_SACRIFICE;

    case EFFECT_DO_NOTHING:
    case EFFECT_HOLD_HANDS:
    case EFFECT_CELEBRATE:
    case EFFECT_HAPPY_HOUR:
        return TRAINER_MOVE_ROLE_NO_OP;
    default:
        return TRAINER_MOVE_ROLE_OTHER;
    }
}

static s32 GetTrainerStatusMoveScore(const struct TrainerMoveContext *ctx, enum Move move)
{
    enum TrainerMoveRole role = GetTrainerMoveRole(move);
    s32 attack = GetSpeciesBaseAttack(ctx->species);
    s32 specialAttack = GetSpeciesBaseSpAttack(ctx->species);

    switch (role)
    {
    case TRAINER_MOVE_ROLE_RECOVERY:
        return 72;
    case TRAINER_MOVE_ROLE_MIXED_SETUP:
        return 64;
    case TRAINER_MOVE_ROLE_PHYSICAL_SETUP:
        return 58 + ClampTrainerMoveScore((attack - specialAttack) / 4, -20, 20);
    case TRAINER_MOVE_ROLE_SPECIAL_SETUP:
        return 58 + ClampTrainerMoveScore((specialAttack - attack) / 4, -20, 20);
    case TRAINER_MOVE_ROLE_SPEED_SETUP:
        return 55;
    case TRAINER_MOVE_ROLE_STATUS:
        return 54;
    case TRAINER_MOVE_ROLE_ALLY_SUPPORT:
        return ctx->battleType == TRAINER_BATTLE_TYPE_DOUBLES ? 52 : TRAINER_MOVE_SCORE_REJECT;
    case TRAINER_MOVE_ROLE_SCREEN:
    case TRAINER_MOVE_ROLE_HAZARD:
        return 48;
    case TRAINER_MOVE_ROLE_SPEED_CONTROL:
        return 46;
    case TRAINER_MOVE_ROLE_PROTECT:
        return 44;
    case TRAINER_MOVE_ROLE_DISRUPTION:
        return 40;
    case TRAINER_MOVE_ROLE_PARTY_SUPPORT:
        return 38;
    case TRAINER_MOVE_ROLE_WEATHER_TERRAIN:
        return 36;
    case TRAINER_MOVE_ROLE_SACRIFICE:
        return 24;
    case TRAINER_MOVE_ROLE_NO_OP:
        return 0;
    default:
        return 16;
    }
}

static bool32 IsBasicHardTrainerTeachableMove(const struct TrainerMoveContext *ctx,
                                              enum Move move)
{
    if (IsDamagingTrainerMove(move))
        return GetTrainerMoveNominalPower(ctx, move) <= HARD_TRAINER_BASIC_TEACHABLE_MAX_POWER;

    switch (GetTrainerMoveRole(move))
    {
    case TRAINER_MOVE_ROLE_STATUS:
    case TRAINER_MOVE_ROLE_ALLY_SUPPORT:
    case TRAINER_MOVE_ROLE_SCREEN:
    case TRAINER_MOVE_ROLE_HAZARD:
    case TRAINER_MOVE_ROLE_SPEED_CONTROL:
    case TRAINER_MOVE_ROLE_PROTECT:
    case TRAINER_MOVE_ROLE_DISRUPTION:
    case TRAINER_MOVE_ROLE_PARTY_SUPPORT:
    case TRAINER_MOVE_ROLE_WEATHER_TERRAIN:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 IsHardTrainerTeachableMoveAvailable(const struct TrainerMoveContext *ctx,
                                                  enum Move move)
{
    if (ctx->level < HARD_TRAINER_BASIC_TEACHABLE_LEVEL)
        return FALSE;
    if (ctx->level >= HARD_TRAINER_FULL_TEACHABLE_LEVEL)
        return TRUE;
    if (ctx->level < HARD_TRAINER_ADVANCED_TEACHABLE_LEVEL)
        return IsBasicHardTrainerTeachableMove(ctx, move);
    if (IsDamagingTrainerMove(move)
     && GetTrainerMoveNominalPower(ctx, move) >= HARD_TRAINER_HIGH_POWER_TEACHABLE_MIN_POWER)
        return FALSE;
    return TRUE;
}

static s32 GetTrainerDamagingMoveScore(const struct TrainerMoveContext *ctx, enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    u32 accuracy = GetMoveAccuracy(move);
    u32 power = GetTrainerMoveNominalPower(ctx, move);
    s32 score;

    if (accuracy == 0)
        accuracy = 100;
    score = power * accuracy / 100;
    if (IsTrainerMoveStab(move, ctx->species, ctx->level))
        score += 20;
    score += GetTrainerMoveOffenseAdjustment(ctx, move);
    if (GetMovePriority(move) > 0)
        score += min(9, GetMovePriority(move) * 3);

    if (MoveHasAdditionalEffectSelf(move, MOVE_EFFECT_RECHARGE))
        score -= 25;
    if (IsExplosionMove(move))
        score -= 35;
    if (effect == EFFECT_RECOIL)
        score -= GetMoveRecoil(move) > 25 ? 18 : 10;
    if (effect == EFFECT_MAX_HP_50_RECOIL || effect == EFFECT_CHLOROBLAST)
        score -= 30;
    if (effect == EFFECT_TWO_TURNS_ATTACK
     || effect == EFFECT_SOLAR_BEAM
     || effect == EFFECT_SEMI_INVULNERABLE
     || effect == EFFECT_SKY_DROP)
        score -= 15;
    if (effect == EFFECT_FOCUS_PUNCH)
        score -= 20;
    if (effect == EFFECT_FIRST_TURN_ONLY)
        score -= 5;
    if (effect == EFFECT_FINAL_GAMBIT)
        score -= 35;

    return score;
}

static bool32 SelectionHasDamagingMove(const struct TrainerMoveSelection *selection)
{
    u32 i;

    for (i = 0; i < selection->count; i++)
    {
        if (IsDamagingTrainerMove(selection->moves[i]))
            return TRUE;
    }
    return FALSE;
}

static s32 ApplyTrainerMoveComposition(const struct TrainerMoveContext *ctx,
                                       const struct TrainerMoveSelection *selection,
                                       enum Move move,
                                       s32 score)
{
    enum TrainerMoveRole role = GetTrainerMoveRole(move);
    enum Type type = GetAutomaticTrainerMoveType(move, ctx->species);
    bool32 hasDamagingMove = SelectionHasDamagingMove(selection);
    bool32 typeSeen = FALSE;
    bool32 hasStab = FALSE;
    u32 i;

    for (i = 0; i < selection->count; i++)
    {
        enum Move selectedMove = selection->moves[i];
        enum TrainerMoveRole selectedRole = GetTrainerMoveRole(selectedMove);

        if (IsDamagingTrainerMove(move) && IsDamagingTrainerMove(selectedMove))
        {
            enum Type selectedType = GetAutomaticTrainerMoveType(selectedMove, ctx->species);

            if (selectedType == type && type != TYPE_NONE)
            {
                typeSeen = TRUE;
                if (GetMoveCategory(selectedMove) == GetMoveCategory(move))
                    score -= 8;
            }
            if (IsTrainerMoveStab(selectedMove, ctx->species, ctx->level))
                hasStab = TRUE;
        }

        if (role == TRAINER_MOVE_ROLE_RECOVERY && selectedRole == role)
            return TRAINER_MOVE_SCORE_REJECT;
        if (role == TRAINER_MOVE_ROLE_PROTECT && selectedRole == role)
            score -= 30;
        if ((role == TRAINER_MOVE_ROLE_PHYSICAL_SETUP
          || role == TRAINER_MOVE_ROLE_SPECIAL_SETUP
          || role == TRAINER_MOVE_ROLE_MIXED_SETUP
          || role == TRAINER_MOVE_ROLE_SPEED_SETUP)
         && selectedRole == role)
            score -= 35;
        if (role == TRAINER_MOVE_ROLE_HAZARD && selectedRole == role)
            score -= 30;
        if (role == TRAINER_MOVE_ROLE_SCREEN && selectedRole == role)
            score -= 10;
        if (role == TRAINER_MOVE_ROLE_STATUS
         && selectedRole == role
         && GetMoveNonVolatileStatus(selectedMove) == GetMoveNonVolatileStatus(move))
            score -= 35;
        if (GetMoveEffect(selectedMove) == GetMoveEffect(move))
            score -= 20;
    }

    if (IsDamagingTrainerMove(move) && hasDamagingMove && type != TYPE_NONE)
        score += typeSeen ? -12 : 10;
    if (IsDamagingTrainerMove(move) && !hasStab && IsTrainerMoveStab(move, ctx->species, ctx->level))
        score += 8;

    return score;
}

static s32 ScoreTrainerMoveCandidate(const struct TrainerMoveContext *ctx,
                                     const struct TrainerMoveSelection *selection,
                                     const struct TrainerMoveCandidate *candidate)
{
    s32 score;

    if (IsDamagingTrainerMove(candidate->move))
        score = GetTrainerDamagingMoveScore(ctx, candidate->move);
    else
        score = GetTrainerStatusMoveScore(ctx, candidate->move);
    if (candidate->source == TRAINER_MOVE_SOURCE_LEVEL_UP)
        score += 8;

    return ApplyTrainerMoveComposition(ctx, selection, candidate->move, score);
}

static bool32 IsBetterTrainerMoveCandidate(const struct TrainerMoveCandidate *candidate,
                                           s32 score,
                                           const struct TrainerMoveCandidate *best,
                                           s32 bestScore,
                                           bool32 hasBest)
{
    if (!hasBest || score > bestScore)
        return TRUE;
    if (score < bestScore)
        return FALSE;
    if (candidate->source != best->source)
        return candidate->source == TRAINER_MOVE_SOURCE_LEVEL_UP;
    if (candidate->source == TRAINER_MOVE_SOURCE_LEVEL_UP && candidate->order != best->order)
        return candidate->order > best->order;
    if (candidate->source == TRAINER_MOVE_SOURCE_TEACHABLE && candidate->order != best->order)
        return candidate->order < best->order;
    return candidate->move < best->move;
}

static void ConsiderTrainerMoveCandidate(const struct TrainerMoveContext *ctx,
                                         const struct TrainerMoveSelection *selection,
                                         const struct TrainerMoveCandidate *candidate,
                                         bool32 damagingOnly,
                                         struct TrainerMoveCandidate *best,
                                         s32 *bestScore,
                                         bool32 *hasBest)
{
    s32 score;

    if (SelectionHasMove(selection, candidate->move))
        return;
    if (damagingOnly && !IsDamagingTrainerMove(candidate->move))
        return;

    score = ScoreTrainerMoveCandidate(ctx, selection, candidate);
    if (score <= TRAINER_MOVE_SCORE_REJECT)
        return;
    if (IsBetterTrainerMoveCandidate(candidate, score, best, *bestScore, *hasBest))
    {
        *best = *candidate;
        *bestScore = score;
        *hasBest = TRUE;
    }
}

static bool32 FindBestHardTrainerMove(const struct TrainerMoveContext *ctx,
                                      const struct TrainerMoveSelection *selection,
                                      bool32 damagingOnly,
                                      enum Move *bestMove)
{
    const struct LevelUpMove *levelUpLearnset = GetSpeciesLevelUpLearnset(ctx->species);
    const u16 *teachableLearnset = GetSpeciesTeachableLearnset(ctx->species);
    struct TrainerMoveCandidate best = {0};
    s32 bestScore = TRAINER_MOVE_SCORE_REJECT;
    bool32 hasBest = FALSE;
    u8 seen[TRAINER_MOVE_SEEN_BYTES] = {0};
    u32 i;

    for (i = 0; i < MAX_LEVEL_UP_MOVES && levelUpLearnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        struct TrainerMoveCandidate candidate;
        enum Move move = levelUpLearnset[i].move;

        if (levelUpLearnset[i].level > ctx->level)
            break;
        if (levelUpLearnset[i].level == 0 || !IsValidAutomaticTrainerMove(move))
            continue;
        if (IsMoveSeen(seen, move))
            continue;
        SetMoveSeen(seen, move);
        if (ctx->battleType == TRAINER_BATTLE_TYPE_SINGLES
         && !IsAutomaticTrainerMoveSuitableForSingles(move))
            continue;
        if (IsHardTrainerMoveUnsupported(move))
            continue;

        candidate.move = move;
        candidate.source = TRAINER_MOVE_SOURCE_LEVEL_UP;
        candidate.order = i;
        ConsiderTrainerMoveCandidate(ctx, selection, &candidate, damagingOnly,
                                     &best, &bestScore, &hasBest);
    }

    for (i = 0; teachableLearnset[i] != MOVE_UNAVAILABLE; i++)
    {
        struct TrainerMoveCandidate candidate;
        enum Move move = teachableLearnset[i];

        if (!IsValidAutomaticTrainerMove(move) || IsMoveSeen(seen, move))
            continue;
        if (!IsHardTrainerTeachableMoveAvailable(ctx, move))
            continue;
        SetMoveSeen(seen, move);
        if (ctx->battleType == TRAINER_BATTLE_TYPE_SINGLES
         && !IsAutomaticTrainerMoveSuitableForSingles(move))
            continue;
        if (IsHardTrainerMoveUnsupported(move))
            continue;

        candidate.move = move;
        candidate.source = TRAINER_MOVE_SOURCE_TEACHABLE;
        candidate.order = i;
        ConsiderTrainerMoveCandidate(ctx, selection, &candidate, damagingOnly,
                                     &best, &bestScore, &hasBest);
    }

    if (hasBest)
        *bestMove = best.move;
    return hasBest;
}

static void BuildHardTrainerMoves(enum Move outMoves[MAX_MON_MOVES],
                                  const struct TrainerMoveContext *ctx)
{
    struct TrainerMoveSelection selection = {0};
    enum Move move;
    u32 i;

    // Guarantee one damaging move whenever the legal pool contains one.
    if (FindBestHardTrainerMove(ctx, &selection, TRUE, &move))
        selection.moves[selection.count++] = move;

    while (selection.count < MAX_MON_MOVES
        && FindBestHardTrainerMove(ctx, &selection, FALSE, &move))
        selection.moves[selection.count++] = move;

    // Hard-mode policy filters should never leave a mon with no usable data.
    // If every candidate was rejected, preserve the latest legal level-up set,
    // including harmless moves such as Splash that Hard scoring normally omits.
    if (selection.count == 0)
    {
        BuildLatestLevelUpTrainerMoves(outMoves, ctx->species, ctx->level,
                                       ctx->battleType == TRAINER_BATTLE_TYPE_SINGLES);
        return;
    }

    for (i = 0; i < MAX_MON_MOVES; i++)
        outMoves[i] = i < selection.count ? selection.moves[i] : MOVE_NONE;
}

void BuildTrainerMonMoves(enum Move outMoves[MAX_MON_MOVES],
                          const struct TrainerMon *partyEntry,
                          u16 actualSpecies,
                          u8 actualLevel,
                          enum TrainerBattleType battleType,
                          enum DifficultyLevel activeDifficulty)
{
    struct TrainerMoveContext ctx;
    u32 i;

    if (TrainerMonHasExplicitMoves(partyEntry))
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
            outMoves[i] = SanitizeTrainerMove(partyEntry->moves[i]);
        return;
    }

    if (activeDifficulty != DIFFICULTY_HARD)
    {
        BuildLatestLevelUpTrainerMoves(outMoves, actualSpecies, actualLevel,
                                       battleType == TRAINER_BATTLE_TYPE_SINGLES);
        return;
    }

    ctx.partyEntry = partyEntry;
    ctx.species = actualSpecies;
    ctx.level = actualLevel;
    ctx.battleType = battleType;
    BuildHardTrainerMoves(outMoves, &ctx);
}

void AssignTrainerMonMoves(struct Pokemon *mon,
                           const struct TrainerMon *partyEntry,
                           enum TrainerBattleType battleType,
                           enum DifficultyLevel activeDifficulty)
{
    enum Move moves[MAX_MON_MOVES];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u8 level = GetMonData(mon, MON_DATA_LEVEL);
    u32 ppBonuses = 0;
    u32 i;

    SetMonData(mon, MON_DATA_PP_BONUSES, &ppBonuses);

    if (!TrainerMonHasExplicitMoves(partyEntry)
     && activeDifficulty != DIFFICULTY_HARD
     && battleType == TRAINER_BATTLE_TYPE_DOUBLES)
    {
        GiveMonInitialMoveset(mon);
        return;
    }

    BuildTrainerMonMoves(moves, partyEntry, species, level, battleType, activeDifficulty);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, moves[i], i);
}
