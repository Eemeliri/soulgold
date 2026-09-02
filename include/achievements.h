#ifndef GUARD_ACHIEVEMENTS_H
#define GUARD_ACHIEVEMENTS_H

#include "main.h"
#include "constants/achievements.h"

struct Achievement
{
    enum AchievementId id;
    const u8 *name;
    const u8 *description;
    enum AchievementTier tier;
    enum AchievementCounter counter;
    u32 targetValue;
    u16 trainerId;
    bool32 (*predicate)(void);
};

bool32 Achievement_Unlock(enum AchievementId id);
void Achievement_IncrementCounter(enum AchievementCounter counter, u32 amount);
void Achievement_SetCounterMax(enum AchievementCounter counter, u32 value);
void Achievement_MigrateBattlePyramidFloorClears(void);
void Achievement_RecordBattlePyramidFloorClear(void);
void Achievement_AddBattlePointsEarned(u32 amount);
void Achievement_CheckAll(void);
void Achievement_CheckCounter(enum AchievementCounter counter);
void Achievement_UnlockHallOfFameDebut(void);
void Achievement_OnPokemonObtained(u16 species);
void Achievement_OnTrainerDefeated(u16 trainerId);
void Achievement_TryShowQueuedPopup(void);
void Achievement_HidePopup(void);
u16 Achievement_CountUnlocked(void);
void GetCompletedAchievementsCount(void);
bool32 Achievement_IsUnlocked(enum AchievementId id);
void Achievement_EnsureSaveInitialized(void);
u32 Achievement_GetCounter(enum AchievementCounter counter);
u32 Achievement_GetProgress(const struct Achievement *achievement);
u32 Achievement_GetTarget(const struct Achievement *achievement);
u16 Achievement_GetCount(void);
const struct Achievement *Achievement_GetByIndex(u16 index);
const struct Achievement *Achievement_GetById(enum AchievementId id);
const u8 *Achievement_GetTierLabel(enum AchievementTier tier);
u16 Achievement_GetTierBallItem(enum AchievementTier tier);
void CB2_InitAchievementsMenu(void);
void CB2_InitAchievementsMenuWithCallback(MainCallback callback);

#endif // GUARD_ACHIEVEMENTS_H
