#include "global.h"
#include "battle_tower.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "pokemon.h"
#include "replay_options.h"
#include "constants/flags.h"

static bool32 ToggleFlag(u16 flag)
{
    FlagToggle(flag);
    return FlagGet(flag);
}

static bool32 ToggleNoInnatesFlag(void)
{
    FlagToggle(FLAG_REPLAY_NO_INNATES);
    if (FlagGet(FLAG_REPLAY_NO_INNATES))
        FlagClear(FLAG_ALL_INNATES_UNLOCKED);
    return FlagGet(FLAG_REPLAY_NO_INNATES);
}

bool32 ToggleReplayOption(enum ReplayOption option)
{
    switch (option)
    {
    case REPLAY_OPTION_TRAINER_PERFECT_IVS:
        return ToggleFlag(FLAG_REPLAY_TRAINER_PERFECT_IVS);
    case REPLAY_OPTION_TRAINER_MAX_EVS:
        return ToggleFlag(FLAG_REPLAY_TRAINER_MAX_EVS);
    case REPLAY_OPTION_EASY_IVS:
        return ToggleFlag(FLAG_REPLAY_EASY_IVS);
    case REPLAY_OPTION_NO_INNATES:
        return ToggleNoInnatesFlag();
    default:
        return FALSE;
    }
}

bool32 ToggleReplayAllInnatesUnlocked(void)
{
    FlagToggle(FLAG_ALL_INNATES_UNLOCKED);
    if (FlagGet(FLAG_ALL_INNATES_UNLOCKED))
        FlagClear(FLAG_REPLAY_NO_INNATES);
    return FlagGet(FLAG_ALL_INNATES_UNLOCKED);
}

bool32 ToggleReplayTrainerFullStats(void)
{
    if (FlagGet(FLAG_REPLAY_TRAINER_PERFECT_IVS) && FlagGet(FLAG_REPLAY_TRAINER_MAX_EVS))
    {
        FlagClear(FLAG_REPLAY_TRAINER_PERFECT_IVS);
        FlagClear(FLAG_REPLAY_TRAINER_MAX_EVS);
        return FALSE;
    }

    FlagSet(FLAG_REPLAY_TRAINER_PERFECT_IVS);
    FlagSet(FLAG_REPLAY_TRAINER_MAX_EVS);
    return TRUE;
}

bool32 ToggleMaxPainReplayOptions(void)
{
    if (FlagGet(FLAG_REPLAY_TRAINER_PERFECT_IVS)
     && FlagGet(FLAG_REPLAY_TRAINER_MAX_EVS)
     && FlagGet(FLAG_ALL_INNATES_UNLOCKED)
     && !FlagGet(FLAG_REPLAY_NO_INNATES))
    {
        FlagClear(FLAG_REPLAY_TRAINER_PERFECT_IVS);
        FlagClear(FLAG_REPLAY_TRAINER_MAX_EVS);
        FlagClear(FLAG_ALL_INNATES_UNLOCKED);
        return FALSE;
    }

    FlagSet(FLAG_REPLAY_TRAINER_PERFECT_IVS);
    FlagSet(FLAG_REPLAY_TRAINER_MAX_EVS);
    FlagSet(FLAG_ALL_INNATES_UNLOCKED);
    FlagClear(FLAG_REPLAY_NO_INNATES);
    return TRUE;
}

enum ReplayBattleFormat GetReplayBattleFormat(void)
{
    if (FlagGet(FLAG_REPLAY_BATTLE_FORMAT_DOUBLES))
        return REPLAY_BATTLE_FORMAT_DOUBLES;
    if (FlagGet(FLAG_REPLAY_BATTLE_FORMAT_SINGLES))
        return REPLAY_BATTLE_FORMAT_SINGLES;
    return REPLAY_BATTLE_FORMAT_DESIGNED;
}

void SetReplayBattleFormat(enum ReplayBattleFormat format)
{
    FlagClear(FLAG_REPLAY_BATTLE_FORMAT_DOUBLES);
    FlagClear(FLAG_REPLAY_BATTLE_FORMAT_SINGLES);

    if (format == REPLAY_BATTLE_FORMAT_DOUBLES)
        FlagSet(FLAG_REPLAY_BATTLE_FORMAT_DOUBLES);
    else if (format == REPLAY_BATTLE_FORMAT_SINGLES)
        FlagSet(FLAG_REPLAY_BATTLE_FORMAT_SINGLES);
}

bool32 AreReplayTrainerPerfectIVsForced(void)
{
    return FlagGet(FLAG_REPLAY_TRAINER_PERFECT_IVS);
}

bool32 AreReplayTrainerMaxEVsForced(void)
{
    return FlagGet(FLAG_REPLAY_TRAINER_MAX_EVS);
}

bool32 AreReplayEasyIVsEnabled(void)
{
    return FlagGet(FLAG_REPLAY_EASY_IVS);
}

bool32 AreReplayInnatesDisabled(void)
{
    return FlagGet(FLAG_REPLAY_NO_INNATES) || AreBattleFacilityInnatesDisabled();
}

void ApplyReplayEasyIVs(struct Pokemon *mon)
{
    if (AreReplayEasyIVsEnabled())
    {
        u32 ivs = TRAINER_PARTY_IVS(MAX_PER_STAT_IVS, MAX_PER_STAT_IVS, MAX_PER_STAT_IVS, MAX_PER_STAT_IVS, MAX_PER_STAT_IVS, MAX_PER_STAT_IVS);

        SetMonData(mon, MON_DATA_IVS, &ivs);
        CalculateMonStats(mon);
    }
}
