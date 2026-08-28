#ifndef GUARD_BATTLE_FRONTIER_H
#define GUARD_BATTLE_FRONTIER_H

#include "data.h"
#include "script.h"
#include "constants/battle_frontier_mons.h"

struct BattleFrontierTrainer
{
    u8 facilityClass;
    u8 filler1[3];
    u8 trainerName[PLAYER_NAME_LENGTH + 1];
    u16 speechBefore[EASY_CHAT_BATTLE_WORDS_COUNT];
    u16 speechWin[EASY_CHAT_BATTLE_WORDS_COUNT];
    u16 speechLose[EASY_CHAT_BATTLE_WORDS_COUNT];
    const u16 *monSet;
};

// Facility-specific TrainerMon tags start after the generic trainer-pool tags.
// They are optional overrides; common roles are also inferred from moves and abilities.
#define FACILITY_MON_TAG_SINGLES_ONLY (1u << 8)
#define FACILITY_MON_TAG_DOUBLES_ONLY (1u << 9)
#define FACILITY_MON_TAG_LEAD         (1u << 10)

enum FacilityTeamArchetype
{
    FACILITY_TEAM_BALANCED,
    FACILITY_TEAM_RAIN,
    FACILITY_TEAM_SUN,
    FACILITY_TEAM_SAND,
    FACILITY_TEAM_SNOW,
    FACILITY_TEAM_TRICK_ROOM,
    FACILITY_TEAM_TAILWIND,
    FACILITY_TEAM_ARCHETYPE_COUNT,
    FACILITY_TEAM_AUTO = 0xFF,
};

// Temporary storage for monIds of the opponent team
// during team generation in battle factory and similar facilities.
extern u16 gFrontierTempParty[MAX_FRONTIER_PARTY_SIZE];

extern const struct BattleFrontierTrainer *gFacilityTrainers;
extern const struct TrainerMon *gFacilityTrainerMons;
extern const struct BattleFrontierTrainer gBattleFrontierTrainers[];
extern const struct TrainerMon gBattleFrontierMons[NUM_FRONTIER_MONS];

void DoFacilityTrainerBattle(struct ScriptContext *ctx);
void FillFrontierTrainerParty(u8 monsCount);
void FillFrontierTrainersParties(u8 monsCount);
bool32 IsFrontierSpeciesAllowed(u16 species);
bool32 IsFrontierMonEnabled(enum FrontierMon monId);
bool32 BuildFacilityTrainerMonSelection(const u16 *monSet, const struct TrainerMon *facilityMons,
                                        u16 facilityMonsCount, u8 monCount, bool32 doubles,
                                        enum FacilityTeamArchetype archetype, bool32 fullArchetype,
                                        u16 maxMonId,
                                        u16 *chosenMonIds);
void CreateFacilityMon(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, struct Pokemon *dst);
void CreateFacilityMonWithPersonality(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, u32 personality, struct Pokemon *dst);

#endif // GUARD_BATTLE_FRONTIER_H
