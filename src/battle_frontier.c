#include "global.h"
#include "main.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_frontier.h"
#include "battle_setup.h"
#include "battle_dome.h"
#include "battle_factory.h"
#include "battle_partner.h"
#include "battle_tower.h"
#include "battle_transition.h"
#include "event_data.h"
#include "frontier_util.h"
#include "item.h"
#include "overworld.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "constants/abilities.h"
#include "constants/battle_frontier.h"
#include "constants/battle_frontier_mons.h"
#include "constants/moves.h"

static void FillTrainerParty(u16 trainerId, u16 firstMonId, u16 monCount);
static u32 GetFacilityMonPersonality(const struct TrainerMon *fmon);

enum FacilityMonRequiredRole
{
    FACILITY_ROLE_ANY,
    FACILITY_ROLE_SETTER,
    FACILITY_ROLE_ABUSER,
};

#define FACILITY_RANDOM_CANDIDATE_ATTEMPTS 64

static bool32 TryBuildFacilityTrainerMonSelection(const u16 *monSet, const struct TrainerMon *facilityMons,
                                                  u16 facilityMonsCount, u8 monCount, bool32 doubles,
                                                  enum FacilityTeamArchetype archetype, bool32 fullArchetype,
                                                  u16 maxMonId,
                                                  const struct Pokemon *existingParty, u8 existingCount,
                                                  u16 *chosenMonIds);

// EWRAM vars.
EWRAM_DATA const struct BattleFrontierTrainer *gFacilityTrainers = NULL;
EWRAM_DATA const struct TrainerMon *gFacilityTrainerMons = NULL;

// IWRAM common
COMMON_DATA u16 gFrontierTempParty[MAX_FRONTIER_PARTY_SIZE] = {0};

STATIC_ASSERT(sizeof(enum FrontierMon) == sizeof(u16), FrontierMonSize_MustBeTwoBytes);

static const u16 sRejectedFrontierSpecies[] =
{
    SPECIES_KELDEO_ORDINARY,
    SPECIES_KELDEO_RESOLUTE,
    SPECIES_ETERNATUS,
    SPECIES_ETERNATUS_ETERNAMAX,
    SPECIES_RESHIRAM,
    SPECIES_ZEKROM,
    SPECIES_KYUREM,
    SPECIES_KYUREM_WHITE,
    SPECIES_KYUREM_BLACK,
    SPECIES_GENESECT_DOUSE,
    SPECIES_GENESECT_SHOCK,
    SPECIES_GENESECT_BURN,
    SPECIES_GENESECT_CHILL,
    SPECIES_ZYGARDE_50,
    SPECIES_ZYGARDE_10_AURA_BREAK,
    SPECIES_ZYGARDE_10_POWER_CONSTRUCT,
    SPECIES_ZYGARDE_50_POWER_CONSTRUCT,
    SPECIES_ZYGARDE_COMPLETE,
    SPECIES_ZYGARDE_MEGA,
    SPECIES_DEOXYS_NORMAL,
    SPECIES_DEOXYS_ATTACK,
    SPECIES_DEOXYS_DEFENSE,
    SPECIES_DEOXYS_SPEED,
    SPECIES_XERNEAS_NEUTRAL,
    SPECIES_XERNEAS_ACTIVE,
    SPECIES_YVELTAL,
    SPECIES_VOLCANION,
    SPECIES_COSMOG,
    SPECIES_COSMOEM,
    SPECIES_SOLGALEO,
    SPECIES_LUNALA,
    SPECIES_NECROZMA,
    SPECIES_NECROZMA_DUSK_MANE,
    SPECIES_NECROZMA_DAWN_WINGS,
    SPECIES_NECROZMA_ULTRA,
    SPECIES_ZACIAN_HERO,
    SPECIES_ZACIAN_CROWNED,
    SPECIES_ZAMAZENTA_HERO,
    SPECIES_ZAMAZENTA_CROWNED,
    SPECIES_REGIELEKI,
    SPECIES_REGIDRAGO,
    SPECIES_GLASTRIER,
    SPECIES_SPECTRIER,
    SPECIES_CALYREX,
    SPECIES_CALYREX_ICE,
    SPECIES_CALYREX_SHADOW,
    SPECIES_PECHARUNT,
    SPECIES_TERAPAGOS_NORMAL,
    SPECIES_TERAPAGOS_TERASTAL,
    SPECIES_TERAPAGOS_STELLAR,
};

static void HandleFacilityTrainerBattleEnd(void)
{
    u8 facility = gBattleScripting.specialTrainerBattleType;

    if (facility == FACILITY_BATTLE_CAFE)
        BattleCafe_RestoreHeldItems();

    switch (facility) 
    {
    case FACILITY_BATTLE_TOWER:
    case FACILITY_BATTLE_DOME:
    case FACILITY_BATTLE_PALACE:
    case FACILITY_BATTLE_ARENA:
    case FACILITY_BATTLE_FACTORY:
    case FACILITY_BATTLE_PIKE_SINGLE:
    case FACILITY_BATTLE_PIKE_DOUBLE:
    case FACILITY_BATTLE_PYRAMID:
    case FACILITY_BATTLE_ARCADE:
    case FACILITY_BATTLE_CAFE:
        if (gSaveBlock2Ptr->frontier.battlesCount < 0xFFFFFF)
        {
            gSaveBlock2Ptr->frontier.battlesCount++;
            if (gSaveBlock2Ptr->frontier.battlesCount % 20 == 0)
                UpdateGymLeaderRematch();
        }
        else
        {
            gSaveBlock2Ptr->frontier.battlesCount = 0xFFFFFF;
        }
        break;
    case FACILITY_BATTLE_TRAINER_HILL:
    default:
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void Task_StartBattleAfterTransition(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = HandleFacilityTrainerBattleEnd;
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}

static void DoFacilityTrainerBattleInternal(u8 facility)
{
    gBattleScripting.specialTrainerBattleType = facility;
    
    switch (facility)
    {
    case FACILITY_BATTLE_TOWER:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
        switch (VarGet(VAR_FRONTIER_BATTLE_MODE))
        {
        case FRONTIER_MODE_SINGLES:
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
            break;
        case FRONTIER_MODE_DOUBLES:
            FillFrontierTrainerParty(FRONTIER_DOUBLES_PARTY_SIZE);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
            break;
        case FRONTIER_MODE_MULTIS:
            FillFrontierTrainersParties(FRONTIER_MULTI_PARTY_SIZE);
            gPartnerTrainerId = gSaveBlock2Ptr->frontier.trainerIds[17];
            FillPartnerParty(gPartnerTrainerId);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_MULTI | BATTLE_TYPE_TWO_OPPONENTS;
            break;
        case FRONTIER_MODE_LINK_MULTIS:
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_LINK | BATTLE_TYPE_MULTI | BATTLE_TYPE_TOWER_LINK_MULTI;
            FillFrontierTrainersParties(FRONTIER_MULTI_PARTY_SIZE);
            break;
        }
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_TOWER));
        break;
    case FACILITY_BATTLE_CAFE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
        if (BattleCafe_ShouldUseDoubles())
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (BattleCafe_GetChallengeMode() == BATTLE_CAFE_MODE_SUPER_CHALLENGE
         || BattleCafe_GetChallengeMode() == BATTLE_CAFE_MODE_SUPER_RUSH
         || BattleCafe_GetChallengeMode() == BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
         || BattleCafe_GetChallengeMode() == BATTLE_CAFE_MODE_ENDLESS_RUSH)
            FillFrontierTrainerParty(PARTY_SIZE);
        else
            FillFrontierTrainerParty(FRONTIER_DOUBLES_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_TOWER));
        break;
    case FACILITY_BATTLE_DOME:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOME;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
        gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_FRONTIER_BRAIN)
        FillFrontierTrainerParty(DOME_BATTLE_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        CreateTask_PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_DOME));
        break;
    case FACILITY_BATTLE_PALACE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PALACE;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
        gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        else
        FillTentTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PALACE));
        break;
    case FACILITY_BATTLE_ARENA:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_ARENA;
        if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        else
        FillTentTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_ARENA));
        break;
    case FACILITY_BATTLE_FACTORY:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_FACTORY;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
        gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        FillFactoryTrainerParty();
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_FACTORY));
        break;
    case FACILITY_BATTLE_PIKE_SINGLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PIKE));
        break;
    case FACILITY_BATTLE_PIKE_DOUBLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS;
        FillFrontierTrainersParties(1);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PIKE));
        break;
    case FACILITY_BATTLE_PYRAMID:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PYRAMID;
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PYRAMID));
        break;
    case FACILITY_BATTLE_TRAINER_HILL:
    default:
        break;
    }
}

void DoFacilityTrainerBattle(struct ScriptContext *ctx)
{
    u8 facility = ScriptReadByte(ctx);

    DoFacilityTrainerBattleInternal(facility);
}

void FacilityTrainerBattle(struct ScriptContext *ctx)
{
    InitTrainerBattleParameter();

    u8 facility = ScriptReadByte(ctx);
    ctx->scriptPtr = BattleSetup_ConfigureFacilityTrainerBattle(facility, ctx->scriptPtr);
}

void FillFrontierTrainerParty(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(TRAINER_BATTLE_PARAM.opponentA, 0, monsCount);
}

void FillFrontierTrainersParties(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(TRAINER_BATTLE_PARAM.opponentA, 0, monsCount);
    FillTrainerParty(TRAINER_BATTLE_PARAM.opponentB, 3, monsCount);
}

bool32 IsFrontierSpeciesAllowed(u16 species)
{
    u32 i;

    if (!IsSpeciesEnabled(species))
        return FALSE;

    for (i = 0; i < ARRAY_COUNT(sRejectedFrontierSpecies); i++)
    {
        if (species == sRejectedFrontierSpecies[i])
            return FALSE;
    }

    return TRUE;
}

bool32 IsFrontierMonEnabled(enum FrontierMon monId)
{
    return monId < NUM_FRONTIER_MONS
        && IsFrontierSpeciesAllowed(gBattleFrontierMons[monId].species);
}

static bool32 FacilityMonHasMove(const struct TrainerMon *mon, enum Move move)
{
    u32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (mon->moves[i] == move)
            return TRUE;
    }
    return FALSE;
}

static bool32 FacilityMonHasTrait(const struct TrainerMon *mon, enum Ability ability)
{
    return mon->ability == ability || SpeciesHasInnate(mon->species, ability);
}

static bool32 IsClearlyDoublesOnlyFacilityMon(const struct TrainerMon *mon)
{
    static const enum Move sDoublesOnlyMoves[] =
    {
        MOVE_FOLLOW_ME,
        MOVE_RAGE_POWDER,
        MOVE_HELPING_HAND,
        MOVE_ALLY_SWITCH,
        MOVE_INSTRUCT,
        MOVE_DECORATE,
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sDoublesOnlyMoves); i++)
    {
        if (FacilityMonHasMove(mon, sDoublesOnlyMoves[i]))
            return TRUE;
    }
    return FALSE;
}

static bool32 IsFacilityArchetypeSetter(const struct TrainerMon *mon, enum FacilityTeamArchetype archetype)
{
    switch (archetype)
    {
    case FACILITY_TEAM_RAIN:
        return FacilityMonHasTrait(mon, ABILITY_DRIZZLE) || FacilityMonHasMove(mon, MOVE_RAIN_DANCE);
    case FACILITY_TEAM_SUN:
        return FacilityMonHasTrait(mon, ABILITY_DROUGHT) || FacilityMonHasMove(mon, MOVE_SUNNY_DAY);
    case FACILITY_TEAM_SAND:
        return FacilityMonHasTrait(mon, ABILITY_SAND_STREAM) || FacilityMonHasMove(mon, MOVE_SANDSTORM);
    case FACILITY_TEAM_SNOW:
        return FacilityMonHasTrait(mon, ABILITY_SNOW_WARNING)
            || FacilityMonHasMove(mon, MOVE_HAIL)
            || FacilityMonHasMove(mon, MOVE_SNOWSCAPE);
    case FACILITY_TEAM_TRICK_ROOM:
        return FacilityMonHasTrait(mon, ABILITY_SHOWTIME) || FacilityMonHasMove(mon, MOVE_TRICK_ROOM);
    case FACILITY_TEAM_TAILWIND:
        return FacilityMonHasTrait(mon, ABILITY_WINDBURST) || FacilityMonHasMove(mon, MOVE_TAILWIND);
    case FACILITY_TEAM_BALANCED:
    case FACILITY_TEAM_ARCHETYPE_COUNT:
    case FACILITY_TEAM_AUTO:
        return FALSE;
    }
    return FALSE;
}

static bool32 IsFacilityArchetypeAbuser(const struct TrainerMon *mon, enum FacilityTeamArchetype archetype)
{
    switch (archetype)
    {
    case FACILITY_TEAM_RAIN:
        return mon->ability == ABILITY_SWIFT_SWIM
            || mon->ability == ABILITY_RAIN_DISH
            || mon->ability == ABILITY_HYDRATION
            || mon->ability == ABILITY_DRY_SKIN
            || FacilityMonHasMove(mon, MOVE_THUNDER)
            || FacilityMonHasMove(mon, MOVE_HURRICANE);
    case FACILITY_TEAM_SUN:
        return mon->ability == ABILITY_CHLOROPHYLL
            || mon->ability == ABILITY_SOLAR_POWER
            || mon->ability == ABILITY_LEAF_GUARD
            || mon->ability == ABILITY_FLOWER_GIFT
            || mon->ability == ABILITY_PROTOSYNTHESIS
            || FacilityMonHasMove(mon, MOVE_SOLAR_BEAM)
            || FacilityMonHasMove(mon, MOVE_SOLAR_BLADE);
    case FACILITY_TEAM_SAND:
        return mon->ability == ABILITY_SAND_RUSH
            || mon->ability == ABILITY_SAND_FORCE
            || mon->ability == ABILITY_SAND_VEIL;
    case FACILITY_TEAM_SNOW:
        return mon->ability == ABILITY_SLUSH_RUSH
            || mon->ability == ABILITY_ICE_BODY
            || mon->ability == ABILITY_SNOW_CLOAK
            || FacilityMonHasMove(mon, MOVE_AURORA_VEIL)
            || FacilityMonHasMove(mon, MOVE_BLIZZARD);
    case FACILITY_TEAM_TRICK_ROOM:
        return gSpeciesInfo[mon->species].baseSpeed <= 70
            && (mon->ev == NULL || mon->ev[5] <= 64);
    case FACILITY_TEAM_TAILWIND:
        return gSpeciesInfo[mon->species].baseSpeed >= 80;
    case FACILITY_TEAM_BALANCED:
    case FACILITY_TEAM_ARCHETYPE_COUNT:
    case FACILITY_TEAM_AUTO:
        return FALSE;
    }
    return FALSE;
}

static enum FacilityTeamArchetype GetFacilityWeatherSetterArchetype(const struct TrainerMon *mon)
{
    enum FacilityTeamArchetype archetype;

    for (archetype = FACILITY_TEAM_RAIN; archetype <= FACILITY_TEAM_SNOW; archetype++)
    {
        if (IsFacilityArchetypeSetter(mon, archetype))
            return archetype;
    }
    return FACILITY_TEAM_BALANCED;
}

static bool32 FacilitySelectionHasWeatherSetter(const struct TrainerMon *facilityMons,
                                                const u16 *chosenMonIds, u8 chosenCount)
{
    u32 i;

    for (i = 0; i < chosenCount; i++)
    {
        if (GetFacilityWeatherSetterArchetype(&facilityMons[chosenMonIds[i]]) != FACILITY_TEAM_BALANCED)
            return TRUE;
    }
    return FALSE;
}

static bool32 FacilitySelectionHasArchetypeSetter(const struct TrainerMon *facilityMons,
                                                  const u16 *chosenMonIds, u8 chosenCount,
                                                  enum FacilityTeamArchetype archetype)
{
    u32 i;

    for (i = 0; i < chosenCount; i++)
    {
        if (IsFacilityArchetypeSetter(&facilityMons[chosenMonIds[i]], archetype))
            return TRUE;
    }
    return FALSE;
}

static bool32 FacilitySelectionHasSpecies(const struct TrainerMon *facilityMons, const u16 *chosenMonIds,
                                          u8 chosenCount, const struct Pokemon *existingParty,
                                          u8 existingCount, u16 species)
{
    u32 i;
    enum NationalDexOrder natDex = gSpeciesInfo[species].natDexNum;

    for (i = 0; i < chosenCount; i++)
    {
        if (gSpeciesInfo[facilityMons[chosenMonIds[i]].species].natDexNum == natDex)
            return TRUE;
    }
    for (i = 0; i < existingCount; i++)
    {
        u16 existingSpecies = GetMonData((struct Pokemon *)&existingParty[i], MON_DATA_SPECIES);

        if (existingSpecies != SPECIES_NONE && gSpeciesInfo[existingSpecies].natDexNum == natDex)
            return TRUE;
    }
    return FALSE;
}

static bool32 FacilitySelectionHasItem(const struct TrainerMon *facilityMons, const u16 *chosenMonIds,
                                       u8 chosenCount, const struct Pokemon *existingParty,
                                       u8 existingCount, enum Item item)
{
    u32 i;

    if (item == ITEM_NONE)
        return FALSE;
    for (i = 0; i < chosenCount; i++)
    {
        if (facilityMons[chosenMonIds[i]].heldItem[0] == item)
            return TRUE;
    }
    for (i = 0; i < existingCount; i++)
    {
        if (GetMonData((struct Pokemon *)&existingParty[i], MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    return FALSE;
}

static bool32 FacilitySelectionHasItemType(const struct TrainerMon *facilityMons, const u16 *chosenMonIds,
                                           u8 chosenCount, const struct Pokemon *existingParty,
                                           u8 existingCount, enum ItemSortType sortType)
{
    u32 i;

    for (i = 0; i < chosenCount; i++)
    {
        if (gItemsInfo[facilityMons[chosenMonIds[i]].heldItem[0]].sortType == sortType)
            return TRUE;
    }
    for (i = 0; i < existingCount; i++)
    {
        enum Item item = GetMonData((struct Pokemon *)&existingParty[i], MON_DATA_HELD_ITEM);

        if (gItemsInfo[item].sortType == sortType)
            return TRUE;
    }
    return FALSE;
}

static bool32 IsFacilityMonSelectionCandidate(const struct TrainerMon *facilityMons, u16 facilityMonsCount,
                                              u16 monId, u16 maxMonId, bool32 doubles,
                                              enum FacilityTeamArchetype archetype,
                                              enum FacilityMonRequiredRole requiredRole,
                                              const struct Pokemon *existingParty, u8 existingCount,
                                              const u16 *chosenMonIds, u8 chosenCount)
{
    const struct TrainerMon *mon;
    enum Item item;
    enum ItemSortType itemType;
    enum FacilityTeamArchetype setterArchetype;

    if (monId >= facilityMonsCount || monId > maxMonId)
        return FALSE;
    mon = &facilityMons[monId];
    if (!IsFrontierSpeciesAllowed(mon->species))
        return FALSE;
    if ((doubles && (mon->tags & FACILITY_MON_TAG_SINGLES_ONLY))
     || (!doubles && ((mon->tags & FACILITY_MON_TAG_DOUBLES_ONLY) || IsClearlyDoublesOnlyFacilityMon(mon))))
        return FALSE;
    if (requiredRole == FACILITY_ROLE_SETTER && !IsFacilityArchetypeSetter(mon, archetype))
        return FALSE;
    if (requiredRole == FACILITY_ROLE_ABUSER
     && (!IsFacilityArchetypeAbuser(mon, archetype) || IsFacilityArchetypeSetter(mon, archetype)))
        return FALSE;

    setterArchetype = GetFacilityWeatherSetterArchetype(mon);
    if (archetype >= FACILITY_TEAM_RAIN && archetype <= FACILITY_TEAM_SNOW
     && setterArchetype != FACILITY_TEAM_BALANCED && setterArchetype != archetype)
        return FALSE;
    if (archetype == FACILITY_TEAM_TRICK_ROOM
     && IsFacilityArchetypeSetter(mon, FACILITY_TEAM_TAILWIND))
        return FALSE;
    if (archetype == FACILITY_TEAM_TAILWIND
     && IsFacilityArchetypeSetter(mon, FACILITY_TEAM_TRICK_ROOM))
        return FALSE;
    if (setterArchetype != FACILITY_TEAM_BALANCED
     && FacilitySelectionHasWeatherSetter(facilityMons, chosenMonIds, chosenCount))
        return FALSE;
    if ((IsFacilityArchetypeSetter(mon, FACILITY_TEAM_TRICK_ROOM)
      && FacilitySelectionHasArchetypeSetter(facilityMons, chosenMonIds, chosenCount,
                                             FACILITY_TEAM_TAILWIND))
     || (IsFacilityArchetypeSetter(mon, FACILITY_TEAM_TAILWIND)
      && FacilitySelectionHasArchetypeSetter(facilityMons, chosenMonIds, chosenCount,
                                             FACILITY_TEAM_TRICK_ROOM)))
        return FALSE;

    if (FacilitySelectionHasSpecies(facilityMons, chosenMonIds, chosenCount,
                                    existingParty, existingCount, mon->species))
        return FALSE;
    item = mon->heldItem[0];
    if (FacilitySelectionHasItem(facilityMons, chosenMonIds, chosenCount,
                                 existingParty, existingCount, item))
        return FALSE;
    itemType = gItemsInfo[item].sortType;
    if ((itemType == ITEM_TYPE_MEGA_STONE || itemType == ITEM_TYPE_Z_CRYSTAL)
     && FacilitySelectionHasItemType(facilityMons, chosenMonIds, chosenCount,
                                     existingParty, existingCount, itemType))
        return FALSE;
    return TRUE;
}

static u16 CountFacilityMonSet(const u16 *monSet)
{
    u16 count;

    for (count = 0; monSet[count] != FRONTIER_MON_END; count++)
        ;
    return count;
}

static bool32 TrySelectFacilityMonExhaustive(const u16 *monSet, u16 monSetCount,
                                             const struct TrainerMon *facilityMons,
                                             u16 facilityMonsCount, u16 maxMonId,
                                             bool32 doubles, enum FacilityTeamArchetype archetype,
                                             enum FacilityMonRequiredRole requiredRole,
                                             const struct Pokemon *existingParty, u8 existingCount,
                                             const u16 *chosenMonIds, u8 chosenCount,
                                             u16 *selectedMonId)
{
    u16 validCount = 0;
    u16 target;
    u32 i;

    for (i = 0; i < monSetCount; i++)
    {
        if (IsFacilityMonSelectionCandidate(facilityMons, facilityMonsCount, monSet[i], maxMonId,
                                            doubles, archetype, requiredRole, existingParty,
                                            existingCount, chosenMonIds, chosenCount))
            validCount++;
    }
    if (validCount == 0)
        return FALSE;

    target = Random() % validCount;
    for (i = 0; i < monSetCount; i++)
    {
        if (IsFacilityMonSelectionCandidate(facilityMons, facilityMonsCount, monSet[i], maxMonId,
                                            doubles, archetype, requiredRole, existingParty,
                                            existingCount, chosenMonIds, chosenCount))
        {
            if (target == 0)
            {
                *selectedMonId = monSet[i];
                return TRUE;
            }
            target--;
        }
    }

    return FALSE;
}

static bool32 TryBuildFacilityTrainerMonSelection(const u16 *monSet, const struct TrainerMon *facilityMons,
                                                  u16 facilityMonsCount, u8 monCount, bool32 doubles,
                                                  enum FacilityTeamArchetype archetype, bool32 fullArchetype,
                                                  u16 maxMonId,
                                                  const struct Pokemon *existingParty, u8 existingCount,
                                                  u16 *chosenMonIds)
{
    u16 monSetCount = CountFacilityMonSet(monSet);
    u32 slot;

    if (monSetCount == 0)
        return FALSE;

    for (slot = 0; slot < monCount; slot++)
    {
        enum FacilityMonRequiredRole requiredRole = FACILITY_ROLE_ANY;
        u32 attempt;

        if (archetype != FACILITY_TEAM_BALANCED)
        {
            if (slot == 0)
                requiredRole = FACILITY_ROLE_SETTER;
            else if (slot == 1 || fullArchetype)
                requiredRole = FACILITY_ROLE_ABUSER;
        }

        // Most pools have a high proportion of valid candidates. Sample those
        // directly so the common case does not scan the entire set twice.
        for (attempt = 0; attempt < FACILITY_RANDOM_CANDIDATE_ATTEMPTS; attempt++)
        {
            u16 monId = monSet[Random() % monSetCount];

            if (IsFacilityMonSelectionCandidate(facilityMons, facilityMonsCount, monId, maxMonId,
                                                doubles, archetype, requiredRole, existingParty,
                                                existingCount, chosenMonIds, slot))
            {
                chosenMonIds[slot] = monId;
                break;
            }
        }

        // Sparse and impossible role pools are uncommon, but the exhaustive
        // path preserves guaranteed completion/failure after bounded retries.
        if (attempt == FACILITY_RANDOM_CANDIDATE_ATTEMPTS
         && !TrySelectFacilityMonExhaustive(monSet, monSetCount, facilityMons, facilityMonsCount,
                                            maxMonId, doubles, archetype, requiredRole, existingParty,
                                            existingCount, chosenMonIds, slot, &chosenMonIds[slot]))
            return FALSE;
    }
    return TRUE;
}

static u8 GetFacilityMonLeadPriority(const struct TrainerMon *mon, bool32 doubles)
{
    if (mon->tags & FACILITY_MON_TAG_LEAD)
        return 100;
    if (doubles && (FacilityMonHasMove(mon, MOVE_FOLLOW_ME)
                 || FacilityMonHasMove(mon, MOVE_RAGE_POWDER)))
        return 90;
    if (FacilityMonHasMove(mon, MOVE_STEALTH_ROCK)
     || FacilityMonHasMove(mon, MOVE_SPIKES)
     || FacilityMonHasMove(mon, MOVE_TOXIC_SPIKES)
     || FacilityMonHasMove(mon, MOVE_STICKY_WEB))
        return 60;
    if (FacilityMonHasMove(mon, MOVE_REFLECT)
     || FacilityMonHasMove(mon, MOVE_LIGHT_SCREEN)
     || FacilityMonHasMove(mon, MOVE_AURORA_VEIL))
        return 50;
    return 0;
}

static void OrderBalancedFacilityTeam(const struct TrainerMon *facilityMons, u16 *chosenMonIds,
                                      u8 monCount, bool32 doubles)
{
    u32 leadSlot;
    u32 leadCount = doubles ? min(2, monCount) : 1;

    for (leadSlot = 0; leadSlot < leadCount; leadSlot++)
    {
        u32 i;
        u8 bestPriority = GetFacilityMonLeadPriority(&facilityMons[chosenMonIds[leadSlot]], doubles);
        u8 bestIndex = leadSlot;

        for (i = leadSlot + 1; i < monCount; i++)
        {
            u8 priority = GetFacilityMonLeadPriority(&facilityMons[chosenMonIds[i]], doubles);

            if (priority > bestPriority)
            {
                bestPriority = priority;
                bestIndex = i;
            }
        }
        if (bestIndex != leadSlot)
        {
            u16 temp = chosenMonIds[leadSlot];

            chosenMonIds[leadSlot] = chosenMonIds[bestIndex];
            chosenMonIds[bestIndex] = temp;
        }
    }
}

static bool32 BuildFacilityTrainerMonSelectionWithExistingParty(const u16 *monSet,
                                                                const struct TrainerMon *facilityMons,
                                                                u16 facilityMonsCount, u8 monCount,
                                                                bool32 doubles,
                                                                enum FacilityTeamArchetype archetype,
                                                                bool32 fullArchetype,
                                                                u16 maxMonId,
                                                                const struct Pokemon *existingParty,
                                                                u8 existingCount, u16 *chosenMonIds)
{
    enum FacilityTeamArchetype selectedArchetype = archetype;

    if (monCount == 0 || monCount > PARTY_SIZE)
        return FALSE;

    if (archetype == FACILITY_TEAM_AUTO)
    {
        // Setup teams should be distinctive rather than the default texture of the
        // facility. Try one about a third of the time, then use balanced selection.
        if (Random() % 3 == 0)
        {
            enum FacilityTeamArchetype start = FACILITY_TEAM_RAIN + Random() % (FACILITY_TEAM_ARCHETYPE_COUNT - 1);
            u32 i;

            for (i = 0; i < FACILITY_TEAM_ARCHETYPE_COUNT - 1; i++)
            {
                selectedArchetype = FACILITY_TEAM_RAIN
                    + (start - FACILITY_TEAM_RAIN + i) % (FACILITY_TEAM_ARCHETYPE_COUNT - 1);
                if (TryBuildFacilityTrainerMonSelection(monSet, facilityMons, facilityMonsCount, monCount,
                                                        doubles, selectedArchetype, fullArchetype, maxMonId,
                                                        existingParty, existingCount, chosenMonIds))
                    break;
            }
            if (i == FACILITY_TEAM_ARCHETYPE_COUNT - 1)
                selectedArchetype = FACILITY_TEAM_AUTO;
        }

        if (selectedArchetype == FACILITY_TEAM_AUTO)
        {
            selectedArchetype = FACILITY_TEAM_BALANCED;
            if (!TryBuildFacilityTrainerMonSelection(monSet, facilityMons, facilityMonsCount, monCount,
                                                     doubles, selectedArchetype, FALSE, maxMonId,
                                                     existingParty, existingCount, chosenMonIds))
                return FALSE;
        }
    }
    else if (!TryBuildFacilityTrainerMonSelection(monSet, facilityMons, facilityMonsCount, monCount,
                                                  doubles, archetype, fullArchetype, maxMonId, existingParty,
                                                  existingCount, chosenMonIds))
    {
        return FALSE;
    }

    if (selectedArchetype == FACILITY_TEAM_BALANCED)
        OrderBalancedFacilityTeam(facilityMons, chosenMonIds, monCount, doubles);
    return TRUE;
}

bool32 BuildFacilityTrainerMonSelection(const u16 *monSet, const struct TrainerMon *facilityMons,
                                        u16 facilityMonsCount, u8 monCount, bool32 doubles,
                                        enum FacilityTeamArchetype archetype, bool32 fullArchetype,
                                        u16 maxMonId,
                                        u16 *chosenMonIds)
{
    return BuildFacilityTrainerMonSelectionWithExistingParty(monSet, facilityMons, facilityMonsCount,
                                                             monCount, doubles, archetype, fullArchetype, maxMonId,
                                                             NULL, 0, chosenMonIds);
}

static void FillTrainerParty(u16 trainerId, u16 firstMonId, u16 monCount)
{
    s32 i, j;
    u16 chosenMonIndices[PARTY_SIZE];
    u8 level = SetFacilityPtrsGetLevel();
    u8 fixedIV = 0;
    const u16 *monSet = NULL;
    u32 otID = 0;

    if (gBattleScripting.specialTrainerBattleType == FACILITY_BATTLE_CAFE)
        level = max(GetHighestLevelInPlayerParty(), FRONTIER_MIN_LEVEL_OPEN);

    if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        // Normal battle frontier trainer.
        fixedIV = GetFrontierTrainerFixedIvs(trainerId);
        monSet = gFacilityTrainers[trainerId].monSet;
    }
    else if (trainerId == TRAINER_EREADER)
    {
    #if FREE_BATTLE_TOWER_E_READER == FALSE
        for (i = firstMonId; i < firstMonId + FRONTIER_PARTY_SIZE; i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.ereaderTrainer.party[i - firstMonId]);
    #endif //FREE_BATTLE_TOWER_E_READER
        return;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CreateFrontierBrainPokemon();
        return;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        // Record mixed player.
        for (j = 0, i = firstMonId; i < firstMonId + monCount; j++, i++)
        {
            if (gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j].species != SPECIES_NONE
                && gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j].level <= level)
            {
                CreateBattleTowerMon_HandleLevel(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j], FALSE);
            }
        }
        return;
    }
    else
    {
        // Apprentice.
        for (i = firstMonId; i < firstMonId + FRONTIER_PARTY_SIZE; i++)
            CreateApprenticeMon(&gEnemyParty[i], &gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE], i - firstMonId);
        return;
    }

    // Regular battle frontier trainer. Build the full selection before creating any
    // Pokémon so format, archetype, and team-wide clauses can be considered together.
    {
        bool32 doubles = (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            || (gBattleScripting.specialTrainerBattleType == FACILITY_BATTLE_TOWER
             && VarGet(VAR_FRONTIER_BATTLE_MODE) != FRONTIER_MODE_SINGLES);
        bool32 isCafe = gBattleScripting.specialTrainerBattleType == FACILITY_BATTLE_CAFE;
        bool32 isDailyCafe = isCafe && BattleCafe_GetChallengeMode() == BATTLE_CAFE_MODE_DAILY;
        bool32 fullArchetype = isCafe ? !isDailyCafe : GetCurrentFacilityWinStreak() >= 21;
        u16 maxMonId = NUM_FRONTIER_MONS - 1;

        if (isDailyCafe
         || (!isCafe
          && (level == FRONTIER_MAX_LEVEL_50
           || level == 20
           || GetCurrentFacilityWinStreak() < 21)))
            maxMonId = FRONTIER_MONS_HIGH_TIER;

        if (!BuildFacilityTrainerMonSelectionWithExistingParty(monSet, gFacilityTrainerMons,
                                                               NUM_FRONTIER_MONS, monCount, doubles,
                                                               FACILITY_TEAM_AUTO,
                                                               fullArchetype,
                                                               maxMonId,
                                                               gEnemyParty, firstMonId,
                                                               chosenMonIndices))
            return;
    }

    otID = Random32();
    for (i = 0; i < monCount; i++)
    {
        enum FrontierMon monId = chosenMonIndices[i];

        // Place the chosen Pokémon into the trainer's party.
        CreateFacilityMon(&gFacilityTrainerMons[monId], level, fixedIV, otID, 0, &gEnemyParty[i + firstMonId]);
    }
}

static u32 GetFacilityMonPersonality(const struct TrainerMon *fmon)
{
    u32 personality = Random32();

    if (fmon->gender == TRAINER_MON_MALE)
        personality = (personality & 0xFFFFFF00) | GeneratePersonalityForGender(MON_MALE, fmon->species);
    else if (fmon->gender == TRAINER_MON_FEMALE)
        personality = (personality & 0xFFFFFF00) | GeneratePersonalityForGender(MON_FEMALE, fmon->species);

    ModifyPersonalityForNature(&personality, fmon->nature);
    return personality;
}

void CreateFacilityMon(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, struct Pokemon *dst)
{
    CreateFacilityMonWithPersonality(fmon, level, fixedIV, otID, flags, GetFacilityMonPersonality(fmon), dst);
}

void CreateFacilityMonWithPersonality(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, u32 personality, struct Pokemon *dst)
{
    u8 ball = (fmon->ball == 0xFF) ? Random() % POKEBALL_COUNT : fmon->ball;
    enum Move move;
    u32 ability, friendship, j;

    CreateMonWithIVs(dst, fmon->species, level, personality, OTID_STRUCT_PRESET(otID), fixedIV);

    friendship = MAX_FRIENDSHIP;
    // Give the chosen Pokémon its specified moves.
    for (j = 0; j < MAX_MON_MOVES; j++)
    {
        move = fmon->moves[j];
        if (flags & FLAG_FRONTIER_MON_FACTORY && move == MOVE_RETURN)
            move = MOVE_FRUSTRATION;

        SetMonMoveSlot(dst, move, j);
        if (GetMoveEffect(move) == EFFECT_FRUSTRATION)
            friendship = 0;  // Frustration is more powerful the lower the pokemon's friendship is.
    }

    SetMonData(dst, MON_DATA_FRIENDSHIP, &friendship);
    SetMonData(dst, MON_DATA_HELD_ITEM, &fmon->heldItem);

    // try to set ability. Otherwise, random of non-hidden as per vanilla
    if (fmon->ability != ABILITY_NONE)
    {
        const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[fmon->species];
        u32 maxAbilities = ARRAY_COUNT(speciesInfo->abilities);
        for (ability = 0; ability < maxAbilities; ++ability)
        {
            if (speciesInfo->abilities[ability] == fmon->ability)
                break;
        }
        if (ability >= maxAbilities)
            ability = 0;
        SetMonData(dst, MON_DATA_ABILITY_NUM, &ability);
    }

    if (fmon->ev != NULL)
    {
        SetMonData(dst, MON_DATA_HP_EV, &(fmon->ev[0]));
        SetMonData(dst, MON_DATA_ATK_EV, &(fmon->ev[1]));
        SetMonData(dst, MON_DATA_DEF_EV, &(fmon->ev[2]));
        SetMonData(dst, MON_DATA_SPATK_EV, &(fmon->ev[3]));
        SetMonData(dst, MON_DATA_SPDEF_EV, &(fmon->ev[4]));
        SetMonData(dst, MON_DATA_SPEED_EV, &(fmon->ev[5]));
    }

    if (fmon->iv)
        SetMonData(dst, MON_DATA_IVS, &(fmon->iv));

    if (fmon->isShiny)
    {
        u32 data = TRUE;
        SetMonData(dst, MON_DATA_IS_SHINY, &data);
    }
    if (fmon->dynamaxLevel > 0)
    {
        u32 data = fmon->dynamaxLevel;
        SetMonData(dst, MON_DATA_DYNAMAX_LEVEL, &data);
    }
    if (fmon->gigantamaxFactor)
    {
        u32 data = fmon->gigantamaxFactor;
        SetMonData(dst, MON_DATA_GIGANTAMAX_FACTOR, &data);
    }
    if (fmon->teraType)
    {
        u32 data = fmon->teraType;
        SetMonData(dst, MON_DATA_TERA_TYPE, &data);
    }


    SetMonData(dst, MON_DATA_POKEBALL, &ball);
    CalculateMonStats(dst);
}
