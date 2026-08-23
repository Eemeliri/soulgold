#ifndef GUARD_VS_SEEKER_H
#define GUARD_VS_SEEKER_H

#include "global.h"
#include "constants/map_types.h"

struct ScriptContext;

void Task_InitVsSeekerAndCheckForTrainersOnScreen(u8 taskId);
bool8 UpdateVsSeekerStepCounter(void);
bool32 IsVsSeekerEnabled(void);
void NativeVsSeekerRematchId(struct ScriptContext *ctx);
u16 GetVsSeekerChargeSteps(void);
u16 GetVsSeekerRemainingSteps(void);
void SetVsSeekerChargeSteps(u16 steps);
bool32 IsVsSeekerMapTypeValid(enum MapType mapType);
bool32 VsSeekerGetEligibleTrainerId(const struct ObjectEventTemplate *object, u16 *trainerId);
u32 VsSeekerCountDefeatedTrainers(const struct ObjectEventTemplate *objects, u32 objectCount, enum MapType mapType);
u32 VsSeekerTryActivate(const struct ObjectEventTemplate *objects, u32 objectCount, enum MapType mapType);
void VsSeekerUpdateExpertQualifications(void);

#define VSSEEKER_RECHARGE_STEPS 200
#define VSSEEKER_SAVE_MAGIC 0xA7

#endif //GUARD_VS_SEEKER_H
