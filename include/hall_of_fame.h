#ifndef GUARD_HALL_OF_FAME_H
#define GUARD_HALL_OF_FAME_H

struct HallofFameMon
{
    u32 tid;
    u32 personality;
    u16 isShiny:1;
    u16 species:15;
    u8 lvl;
    u8 nickname[POKEMON_NAME_LENGTH];
};

struct HallofFameTeam
{
    struct HallofFameMon mon[PARTY_SIZE];
};

#define HALL_OF_FAME_LEGACY_MAX_TEAMS 30
#define HALL_OF_FAME_RETAINED_TEAMS   11

struct HallOfFameArchive
{
    u8 count;
    u8 reserved[3];
    struct HallofFameTeam teams[HALL_OF_FAME_RETAINED_TEAMS];
};

STATIC_ASSERT(sizeof(struct HallofFameTeam) == 144, HallOfFameTeamSize);
STATIC_ASSERT(sizeof(struct HallOfFameArchive) == 1588, HallOfFameArchiveSize);

extern struct HallofFameTeam *gHoFSaveBuffer;

void ResetHallOfFameArchive(void);
u16 CountRetainedHallOfFameTeams(const struct HallofFameTeam *);
void AppendRetainedHallOfFameTeam(struct HallofFameTeam *, const struct HallofFameTeam *);
u16 GetRetainedHallOfFameTeamNumber(u16, u16);

void CB2_DoHallOfFameScreen(void);
void CB2_DoHallOfFameScreenDontSaveData(void);
void CB2_DoHallOfFamePC(void);

#if TESTING
void HallOfFame_TestCleanupAfterSaveFailure(void);
#endif

// hof_pc.c
void ReturnFromHallOfFamePC(void);

#endif // GUARD_HALL_OF_FAME_H
