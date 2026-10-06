#include "global.h"
#include "bug_contest.h"
#include "level_scaling.h"
#include "pokemon.h"
#include "data.h"
#include "caps.h"
#include "random.h"
#include "pokemon_storage_system.h"
#include "constants/trainers.h"
#include "constants/pokemon.h"

#if B_LEVEL_SCALING_ENABLED

#include "data/level_scaling_rules.h"
#include "data/level_scaling_evolution_overrides.h"

// Party level cache for performance
static struct {
    u8 partyAverage;
    u8 partyHighest;
    u8 partyLowest;
    bool8 cached;
} sPartyLevelCache = {0};

static struct LevelScalingConfig sTrainerOptionConfig;
static struct LevelScalingConfig sWildOptionConfig;

// ============================================================================
// Internal Helper Functions - Party Level Calculation
// ============================================================================

static u8 GetPlayerPartyAverageLevel(bool8 excludeFainted)
{
    u32 totalLevel = 0;
    u32 count = 0;
    u32 i;
    u8 highestLevel = 1;

    // Establish the top of the active party first. Pokémon seven or more
    // levels below it are omitted from the average so a deliberately weak
    // passenger cannot drag trainer levels down.
    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u8 level;

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            break;
        if (excludeFainted && GetMonData(mon, MON_DATA_HP) == 0)
            continue;

        level = GetMonData(mon, MON_DATA_LEVEL);
        if (level > highestLevel)
            highestLevel = level;
    }

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u8 level;

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            break;

        if (excludeFainted && GetMonData(mon, MON_DATA_HP) == 0)
            continue;

        level = GetMonData(mon, MON_DATA_LEVEL);
        if (highestLevel - level >= 7)
            continue;

        totalLevel += level;
        count++;
    }

    if (count == 0)
        return 1; // Fallback if no valid mons

    return totalLevel / count;
}

static u8 GetPlayerPartyHighestLevel(bool8 excludeFainted)
{
    u8 highest = 1;
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            break;

        if (excludeFainted && GetMonData(mon, MON_DATA_HP) == 0)
            continue;

        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        if (level > highest)
            highest = level;
    }

    return highest;
}

static u8 GetPlayerPartyLowestLevel(bool8 excludeFainted)
{
    u8 lowest = MAX_LEVEL;
    u32 i;
    bool8 foundMon = FALSE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            break;

        if (excludeFainted && GetMonData(mon, MON_DATA_HP) == 0)
            continue;

        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        if (level < lowest)
        {
            lowest = level;
            foundMon = TRUE;
        }
    }

    return foundMon ? lowest : 1;
}


// ============================================================================
// Internal Helper Functions - Level Manipulation
// ============================================================================

static u8 ApplyLevelVariation(u8 baseLevel, u8 variation)
{
    if (variation == 0)
        return baseLevel;

    // Randomly reduce level by 0 to variation
    u8 reduction = Random() % (variation + 1);
    if (baseLevel > reduction)
        return baseLevel - reduction;

    return 1; // Never go below 1
}

static u8 GetDeterministicTrainerVariation(u16 trainerId, u8 variation)
{
    u32 seed;

    if (variation == 0)
        return 0;

    seed = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    seed ^= trainerId * 1103515245;
    seed ^= seed >> 16;
    seed *= 2246822519U;
    seed ^= seed >> 13;

    return seed % (variation + 1);
}

static u8 ApplyLevelVariationAmount(u8 baseLevel, u8 reduction)
{
    if (baseLevel > reduction)
        return baseLevel - reduction;

    return 1;
}

static u8 ClampLevel(u8 level, u8 minLevel, u8 maxLevel)
{
    // Apply minimum
    if (minLevel > 0 && level < minLevel)
        level = minLevel;

    // Apply maximum
    if (maxLevel > 0 && level > maxLevel)
        level = maxLevel;

    // Ensure level is always valid
    if (level < 1)
        level = 1;
    if (level > MAX_LEVEL)
        level = MAX_LEVEL;

    return level;
}

// ============================================================================
// Internal Helper Functions - Evolution Management
// ============================================================================

// Get the level required to evolve INTO this species (from its pre-evolution)
static u8 GetEvolutionLevelForSpecies(u16 species)
{
    u32 i, j;

    // Find what evolves into this species
    for (i = 1; i < NUM_SPECIES; i++)
    {
        if (!IsSpeciesEnabled(i))
            continue;

        const struct Evolution *evolutions = GetSpeciesEvolutions(i);
        if (evolutions == NULL)
            continue;

        for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
        {
            if (evolutions[j].targetSpecies == species)
            {
                // Check if this is a level-based evolution
                if (evolutions[j].method == EVO_LEVEL || evolutions[j].method == EVO_LEVEL_BATTLE_ONLY)
                {
                    return evolutions[j].param;
                }
            }
        }
    }

    return 0; // No level-based evolution found
}

static bool8 IsSpeciesLegalAtLevel(u16 species, u8 level)
{
    u8 requiredLevel;
    #if B_SCALING_USE_OVERRIDES
    const struct EvolutionOverride *override;

    // Check evolution overrides first
    override = GetEvolutionOverride(species);
    if (override != NULL)
    {
        return level >= override->minimumLevel;
    }
    #endif

    // Check if this species is an evolved form
    u16 preEvo = GetSpeciesPreEvolution(species);
    if (preEvo == SPECIES_NONE)
    {
        // This is a base form, always legal
        return TRUE;
    }

    // This is an evolved form - check the level required to evolve into it
    requiredLevel = GetEvolutionLevelForSpecies(species);
    if (requiredLevel > 0 && level < requiredLevel)
    {
        // Level is too low for this evolution
        return FALSE;
    }

    // Recursively check if the pre-evolution is legal at this level
    // (handles multi-stage evolutions like Fuecoco -> Crocalor -> Skeledirge)
    return IsSpeciesLegalAtLevel(preEvo, level);
}

// ============================================================================
// Public API Functions
// ============================================================================

const struct EvolutionOverride *GetEvolutionOverride(u16 species)
{
    u32 i;

    for (i = 0; gEvolutionOverrides[i].species != SPECIES_NONE; i++)
    {
        if (gEvolutionOverrides[i].species == species)
            return &gEvolutionOverrides[i];
    }

    return NULL;
}

u8 GetCurrentTrainerLevelScalingMode(void)
{
    if (gSaveBlock2Ptr->optionsTrainerLevelScaling == LEVEL_SCALING_OPTION_OFF)
        return LEVEL_SCALING_NONE;

    return B_TRAINER_SCALING_DEFAULT_MODE;
}

u8 GetCurrentWildLevelScalingMode(void)
{
    if (GetBugContestFlag())
        return LEVEL_SCALING_NONE;

    if (gSaveBlock2Ptr->optionsWildLevelScaling == LEVEL_SCALING_OPTION_OFF)
        return LEVEL_SCALING_NONE;

    return B_WILD_SCALING_DEFAULT_MODE;
}

u16 ValidateSpeciesForLevel(u16 species, u8 targetLevel, bool8 manageEvolutions)
{
    if (!manageEvolutions)
        return species;

    // Check if current species is legal at this level
    if (IsSpeciesLegalAtLevel(species, targetLevel))
        return species;

    // Need to devolve - find pre-evolution
    u16 currentSpecies = species;
    u16 preEvo;
    u32 maxIterations = 10; // Prevent infinite loops

    while (maxIterations-- > 0)
    {
        preEvo = GetSpeciesPreEvolution(currentSpecies);

        if (preEvo == SPECIES_NONE)
        {
            // No pre-evolution found, use current species
            break;
        }

        currentSpecies = preEvo;

        // Check if this pre-evolution is legal
        if (IsSpeciesLegalAtLevel(currentSpecies, targetLevel))
            return currentSpecies;
    }

    // If we couldn't find a legal evolution, return the furthest devolved form
    return currentSpecies;
}

u16 EvolveSpeciesForLevel(u16 species, u8 targetLevel)
{
    u32 maxIterations = 10;

    while (maxIterations-- > 0)
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(species);
        u16 targetSpecies = SPECIES_NONE;
        u32 i;

        if (evolutions == NULL)
            break;

        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            // Only choose plain level evolutions. Conditional and branching
            // evolutions need authored trainer data or a future explicit
            // override so scaling never selects an arbitrary form.
            if ((evolutions[i].method != EVO_LEVEL
              && evolutions[i].method != EVO_LEVEL_BATTLE_ONLY)
             || evolutions[i].param == 0
             || evolutions[i].params != NULL
             || targetLevel < evolutions[i].param
             || !IsSpeciesEnabled(evolutions[i].targetSpecies))
                continue;

            if (targetSpecies != SPECIES_NONE
             && targetSpecies != evolutions[i].targetSpecies)
                return species;

            targetSpecies = evolutions[i].targetSpecies;
        }

        if (targetSpecies == SPECIES_NONE)
            break;

        species = targetSpecies;
    }

    return species;
}

void InvalidatePartyLevelCache(void)
{
    sPartyLevelCache.cached = FALSE;
}

u8 CalculatePlayerPartyBaseLevel(u8 mode, bool8 excludeFainted)
{
    u8 baseLevel = 1;

    // Use cache if available
    if (sPartyLevelCache.cached)
    {
        switch (mode)
        {
            case LEVEL_SCALING_PARTY_AVG:
                return sPartyLevelCache.partyAverage;
            case LEVEL_SCALING_PARTY_HIGHEST:
                return sPartyLevelCache.partyHighest;
            case LEVEL_SCALING_PARTY_LOWEST:
                return sPartyLevelCache.partyLowest;
        }
    }

    // Calculate based on mode
    switch (mode)
    {
        case LEVEL_SCALING_NONE:
            return 0; // Signal to use original level

        case LEVEL_SCALING_TO_LEVEL_CAP:
            baseLevel = GetCurrentLevelCap();
            break;

        case LEVEL_SCALING_PARTY_AVG:
            baseLevel = GetPlayerPartyAverageLevel(excludeFainted);
            sPartyLevelCache.partyAverage = baseLevel;
            break;

        case LEVEL_SCALING_PARTY_HIGHEST:
            baseLevel = GetPlayerPartyHighestLevel(excludeFainted);
            sPartyLevelCache.partyHighest = baseLevel;
            break;

        case LEVEL_SCALING_PARTY_LOWEST:
            baseLevel = GetPlayerPartyLowestLevel(excludeFainted);
            sPartyLevelCache.partyLowest = baseLevel;
            break;

        default:
            baseLevel = 1;
            break;
    }

    // Mark cache as valid after first calculation
    sPartyLevelCache.cached = TRUE;

    return baseLevel;
}

static bool8 IsOptionalScalingTrainer(u16 trainerId)
{
    u32 i;

    for (i = 0; sOptionalScalingTrainerIds[i] != TRAINERS_COUNT; i++)
    {
        if (sOptionalScalingTrainerIds[i] == trainerId)
            return TRUE;
    }

    return FALSE;
}

const struct LevelScalingConfig *GetTrainerLevelScalingConfig(u16 trainerId, u8 intendedAverageLevel)
{
    bool8 isOptionalTrainer = IsOptionalScalingTrainer(trainerId);
    bool8 forceScaling = FALSE;

    if (isOptionalTrainer
     && CalculatePlayerPartyBaseLevel(LEVEL_SCALING_PARTY_AVG, FALSE)
          > intendedAverageLevel + B_OPTIONAL_TRAINER_SCALING_THRESHOLD)
        forceScaling = TRUE;

    if (forceScaling)
        sTrainerOptionConfig.mode = LEVEL_SCALING_PARTY_AVG;
    else
        sTrainerOptionConfig.mode = GetCurrentTrainerLevelScalingMode();
    sTrainerOptionConfig.levelAugmentAdd = B_TRAINER_SCALING_LEVEL_AUGMENT;
    sTrainerOptionConfig.levelVariation = B_TRAINER_SCALING_LEVEL_VARIATION;
    sTrainerOptionConfig.minLevel = B_TRAINER_SCALING_MIN_LEVEL;
    sTrainerOptionConfig.maxLevel = B_TRAINER_SCALING_MAX_LEVEL;
    sTrainerOptionConfig.manageEvolutions = forceScaling
                                          ? TRUE
                                          : B_TRAINER_SCALING_MANAGE_EVOLUTIONS;
    sTrainerOptionConfig.excludeFainted = B_TRAINER_SCALING_EXCLUDE_FAINTED;
    sTrainerOptionConfig.useAuthoredLevelFloor = isOptionalTrainer;
    sTrainerOptionConfig.evolveAboveLevel = forceScaling;

    // There's a chance that the random variance from trainer scaling applies +1 level to these trainers, which can feel unfair.
    switch (trainerId)
    {
        case TRAINER_RIVAL_TOTODILE_1:
        case TRAINER_RIVAL_CHIKORITA_1:
        case TRAINER_RIVAL_CYNDAQUIL_1:
        case TRAINER_RIVALCRYSTAL1:
        case TRAINER_RIVALGOLD1:
            sTrainerOptionConfig.levelAugmentAdd = 0;
            sTrainerOptionConfig.levelVariation = 0;
            break;
    }

    return &sTrainerOptionConfig;
}

u8 CalculateScaledLevel(const struct LevelScalingConfig *config, u8 originalLevel)
{
    u8 baseLevel;
    s16 adjustedLevel;

    // Get base level from scaling mode
    baseLevel = CalculatePlayerPartyBaseLevel(config->mode, config->excludeFainted);

    // If mode is NONE, return original
    if (baseLevel == 0)
        return originalLevel;

    // Apply augmentation (can be positive or negative)
    adjustedLevel = (s16)baseLevel + (s16)config->levelAugmentAdd;

    // Ensure we don't go negative
    if (adjustedLevel < 1)
        adjustedLevel = 1;

    // Apply random variation
    adjustedLevel = ApplyLevelVariation((u8)adjustedLevel, config->levelVariation);

    // Clamp to configured min/max
    adjustedLevel = ClampLevel((u8)adjustedLevel, config->minLevel, config->maxLevel);

    if (B_SCALING_DEBUG_PRINT)
    {
        // Debug output would go here
    }

    return (u8)adjustedLevel;
}

u8 CalculateTrainerScaledLevel(const struct LevelScalingConfig *config, u8 originalLevel, u16 trainerId)
{
    u8 baseLevel;
    s16 adjustedLevel;
    u8 reduction;

    // Get base level from scaling mode
    baseLevel = CalculatePlayerPartyBaseLevel(config->mode, config->excludeFainted);

    // If mode is NONE, return original
    if (baseLevel == 0)
        return originalLevel;

    // Apply augmentation (can be positive or negative)
    adjustedLevel = (s16)baseLevel + (s16)config->levelAugmentAdd;

    // Ensure we don't go negative
    if (adjustedLevel < 1)
        adjustedLevel = 1;

    // Apply deterministic per-save, per-trainer variation
    reduction = GetDeterministicTrainerVariation(trainerId, config->levelVariation);
    adjustedLevel = ApplyLevelVariationAmount((u8)adjustedLevel, reduction);

    // Clamp to configured min/max
    adjustedLevel = ClampLevel((u8)adjustedLevel, config->minLevel, config->maxLevel);

    return (u8)adjustedLevel;
}

u8 CalculateWildScaledLevel(u16 species, u8 originalLevel, u8 minimumLevel)
{
    sWildOptionConfig.mode = GetCurrentWildLevelScalingMode();
    sWildOptionConfig.levelAugmentAdd = B_WILD_SCALING_LEVEL_AUGMENT;
    sWildOptionConfig.levelVariation = B_WILD_SCALING_LEVEL_VARIATION;
    sWildOptionConfig.minLevel = max(B_WILD_SCALING_MIN_LEVEL, minimumLevel);
    sWildOptionConfig.maxLevel = B_WILD_SCALING_MAX_LEVEL;
    sWildOptionConfig.manageEvolutions = B_WILD_SCALING_MANAGE_EVOLUTIONS;
    sWildOptionConfig.excludeFainted = B_WILD_SCALING_EXCLUDE_FAINTED;

    u8 newLevel = CalculateScaledLevel(&sWildOptionConfig, originalLevel);

    // Note: Species validation should happen in wild encounter code
    // as we can't modify the species from this function

    return newLevel;
}

// Calculate scaled species for wild encounters (called from wild_encounter.c)
u16 CalculateWildScaledSpecies(u16 species, u8 scaledLevel)
{
    #if B_WILD_SCALING_MANAGE_EVOLUTIONS
    if (GetCurrentWildLevelScalingMode() == LEVEL_SCALING_NONE)
        return species;

    return ValidateSpeciesForLevel(species, scaledLevel, TRUE);
    #else
    return species;
    #endif
}

#endif // B_LEVEL_SCALING_ENABLED
