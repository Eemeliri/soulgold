#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "item.h"
#include "item_menu.h"
#include "item_use.h"
#include "script.h"
#include "script_movement.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "vs_seeker.h"
#include "constants/battle_setup.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/opponents.h"
#include "constants/script_commands.h"
#include "constants/songs.h"
#include "constants/trainer_types.h"

// Documentation for the Vs. Seeker can be found in docs/tutorials/vs_seeker.md.

enum VsSeekerUseResult
{
    VSSEEKER_NOT_CHARGED,
    VSSEEKER_NO_DEFEATED_TRAINERS,
    VSSEEKER_CAN_USE,
};

struct VsSeekerExpertQualification
{
    u16 qualificationFlag;
    u16 expertDefeatedFlag;
    const u16 *prerequisiteTrainerIds;
    u8 prerequisiteCount;
};

static const u16 sRoute31ExpertPrerequisites[] =
{
    TRAINER_WADE,
    TRAINER_JOEY,
    TRAINER_MIKEY,
    TRAINER_DON,
};

static const u16 sGoldenrodShoreExpertPrerequisites[] =
{
    TRAINER_SAMUEL,
    TRAINER_BRANDON,
    TRAINER_TODD,
    TRAINER_IAN,
    TRAINER_GINA,
    TRAINER_KIM,
    TRAINER_ELLIOT,
    TRAINER_BROOKE,
    TRAINER_IVAN,
    TRAINER_IRWIN,
    TRAINER_WALT,
    TRAINER_ARNIE,
    TRAINER_BRYAN,
    TRAINER_MARK,
    TRAINER_ALAN,
};

static const u16 sRoute43ExpertPrerequisites[] =
{
    TRAINER_BRENT,
    TRAINER_RON,
    TRAINER_MARVIN,
    TRAINER_SPENCER,
    TRAINER_TIFFANY,
    TRAINER_ANDRE,
    TRAINER_RAYMOND,
    TRAINER_AARON,
    TRAINER_LOIS,
};

static const u16 sRoute47ExpertPrerequisites[] =
{
    TRAINER_DEVIN,
    TRAINER_GRANT,
    TRAINER_THOM_AND_KAE,
    TRAINER_DUFF_AND_EDA,
};

static const u16 sRoute27ExpertPrerequisites[] =
{
    TRAINER_BLAKE,
    TRAINER_BRIAN,
    TRAINER_REENA,
    TRAINER_MEGAN,
    TRAINER_GILBERT,
    TRAINER_JOSE,
    TRAINER_SCOTT,
    TRAINER_JAKE,
    TRAINER_GAVEN,
    TRAINER_JOYCE,
    TRAINER_BETH,
    TRAINER_RICHARD,
};

static const struct VsSeekerExpertQualification sExpertQualifications[] =
{
    {
        .qualificationFlag = FLAG_ROUTE31_EXPERT_QUALIFIED,
        .expertDefeatedFlag = FLAG_ROUTE31_EXPERT,
        .prerequisiteTrainerIds = sRoute31ExpertPrerequisites,
        .prerequisiteCount = ARRAY_COUNT(sRoute31ExpertPrerequisites),
    },
    {
        .qualificationFlag = FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED,
        .expertDefeatedFlag = FLAG_GOLDENRODSHORE_EXPERT,
        .prerequisiteTrainerIds = sGoldenrodShoreExpertPrerequisites,
        .prerequisiteCount = ARRAY_COUNT(sGoldenrodShoreExpertPrerequisites),
    },
    {
        .qualificationFlag = FLAG_ROUTE43_EXPERT_QUALIFIED,
        .expertDefeatedFlag = FLAG_ROUTE43_EXPERT,
        .prerequisiteTrainerIds = sRoute43ExpertPrerequisites,
        .prerequisiteCount = ARRAY_COUNT(sRoute43ExpertPrerequisites),
    },
    {
        .qualificationFlag = FLAG_ROUTE47_EXPERT_QUALIFIED,
        .expertDefeatedFlag = FLAG_ROUTE47_EXPERT,
        .prerequisiteTrainerIds = sRoute47ExpertPrerequisites,
        .prerequisiteCount = ARRAY_COUNT(sRoute47ExpertPrerequisites),
    },
    {
        .qualificationFlag = FLAG_ROUTE27_EXPERT_QUALIFIED,
        .expertDefeatedFlag = FLAG_ROUTE27_EXPERT,
        .prerequisiteTrainerIds = sRoute27ExpertPrerequisites,
        .prerequisiteCount = ARRAY_COUNT(sRoute27ExpertPrerequisites),
    },
};

static const u8 sMovementScript_Wait48[] =
{
    MOVEMENT_ACTION_DELAY_16,
    MOVEMENT_ACTION_DELAY_16,
    MOVEMENT_ACTION_DELAY_16,
    MOVEMENT_ACTION_STEP_END,
};

static void ValidateVsSeekerChargeState(void);
static bool32 AreExpertPrerequisitesComplete(const struct VsSeekerExpertQualification *qualification);
static bool32 IsAllowedFirstBattleMode(u8 mode);
static bool32 IsExplicitlyExcludedTrainer(u16 trainerId);
static u32 CollectDefeatedTrainerIds(const struct ObjectEventTemplate *objects, u32 objectCount, enum MapType mapType, u16 *trainerIds);
static u32 TryActivateVsSeekerOnCurrentMap(void);
static enum VsSeekerUseResult CanUseVsSeeker(void);
static void Task_VsSeekerFrameCountdown(u8 taskId);
static void Task_VsSeeker_PlaySoundAndResetTrainers(u8 taskId);
static void Task_VsSeeker_ShowResponseToPlayer(u8 taskId);

static void ValidateVsSeekerChargeState(void)
{
    if (gSaveBlock1Ptr->vsSeekerSaveMagic != VSSEEKER_SAVE_MAGIC
     || gSaveBlock1Ptr->vsSeekerSaveMagicInv != (u8)~VSSEEKER_SAVE_MAGIC
     || gSaveBlock1Ptr->vsSeekerChargeSteps > VSSEEKER_RECHARGE_STEPS)
        SetVsSeekerChargeSteps(VSSEEKER_RECHARGE_STEPS);
}

u16 GetVsSeekerChargeSteps(void)
{
    ValidateVsSeekerChargeState();
    return gSaveBlock1Ptr->vsSeekerChargeSteps;
}

u16 GetVsSeekerRemainingSteps(void)
{
    return VSSEEKER_RECHARGE_STEPS - GetVsSeekerChargeSteps();
}

void SetVsSeekerChargeSteps(u16 steps)
{
    if (steps > VSSEEKER_RECHARGE_STEPS)
        steps = VSSEEKER_RECHARGE_STEPS;

    gSaveBlock1Ptr->vsSeekerChargeSteps = steps;
    gSaveBlock1Ptr->vsSeekerSaveMagicInv = (u8)~VSSEEKER_SAVE_MAGIC;
    gSaveBlock1Ptr->vsSeekerSaveMagic = VSSEEKER_SAVE_MAGIC;
}

bool8 UpdateVsSeekerStepCounter(void)
{
    u16 chargeSteps;

    if (!I_VS_SEEKER_ENABLED)
        return FALSE;

    chargeSteps = GetVsSeekerChargeSteps();
    if (!CheckBagHasItem(ITEM_VS_SEEKER, 1) || chargeSteps == VSSEEKER_RECHARGE_STEPS)
        return FALSE;

    SetVsSeekerChargeSteps(chargeSteps + 1);
    return chargeSteps + 1 == VSSEEKER_RECHARGE_STEPS;
}

bool32 IsVsSeekerEnabled(void)
{
    return I_VS_SEEKER_ENABLED && CheckBagHasItem(ITEM_VS_SEEKER, 1);
}

bool32 IsVsSeekerMapTypeValid(enum MapType mapType)
{
    return mapType == MAP_TYPE_ROUTE;
}

static bool32 IsAllowedFirstBattleMode(u8 mode)
{
    switch (mode)
    {
    case TRAINER_BATTLE_SINGLE:
    case TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC:
    case TRAINER_BATTLE_CONTINUE_SCRIPT:
    case TRAINER_BATTLE_DOUBLE:
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE:
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 IsExplicitlyExcludedTrainer(u16 trainerId)
{
    // This story battle is the sole audited route object that otherwise has
    // the exact object type and leading script shape of a regular Trainer.
    return trainerId == TRAINER_TABITHA_MT_CHIMNEY;
}

bool32 VsSeekerGetEligibleTrainerId(const struct ObjectEventTemplate *object, u16 *trainerId)
{
    u16 id;
    u8 battleFlags;

    if (object == NULL || object->script == NULL)
        return FALSE;
    if (object->trainerType != TRAINER_TYPE_NORMAL && object->trainerType != TRAINER_TYPE_BURIED)
        return FALSE;
    if (object->script[0] != SCR_OP_TRAINERBATTLE)
        return FALSE;

    battleFlags = object->script[1];
    if ((battleFlags & (1 << 1)) || !IsAllowedFirstBattleMode(battleFlags >> 4))
        return FALSE;

    id = T1_READ_16(object->script + 3);
    if (id == TRAINER_NONE || id >= MAX_TRAINERS_COUNT || IsExplicitlyExcludedTrainer(id))
        return FALSE;

    if (trainerId != NULL)
        *trainerId = id;
    return TRUE;
}

static u32 CollectDefeatedTrainerIds(const struct ObjectEventTemplate *objects, u32 objectCount, enum MapType mapType, u16 *trainerIds)
{
    u32 i;
    u32 j;
    u32 trainerCount = 0;

    if (!IsVsSeekerMapTypeValid(mapType) || objects == NULL)
        return 0;
    if (objectCount > OBJECT_EVENT_TEMPLATES_COUNT)
        objectCount = OBJECT_EVENT_TEMPLATES_COUNT;

    for (i = 0; i < objectCount; i++)
    {
        u16 trainerId;

        if (!VsSeekerGetEligibleTrainerId(&objects[i], &trainerId) || !HasTrainerBeenFought(trainerId))
            continue;

        for (j = 0; j < trainerCount; j++)
        {
            if (trainerIds[j] == trainerId)
                break;
        }
        if (j == trainerCount)
            trainerIds[trainerCount++] = trainerId;
    }

    return trainerCount;
}

u32 VsSeekerCountDefeatedTrainers(const struct ObjectEventTemplate *objects, u32 objectCount, enum MapType mapType)
{
    u16 trainerIds[OBJECT_EVENT_TEMPLATES_COUNT];

    return CollectDefeatedTrainerIds(objects, objectCount, mapType, trainerIds);
}

static bool32 AreExpertPrerequisitesComplete(const struct VsSeekerExpertQualification *qualification)
{
    u32 i;

    for (i = 0; i < qualification->prerequisiteCount; i++)
    {
        if (!HasTrainerBeenFought(qualification->prerequisiteTrainerIds[i]))
            return FALSE;
    }
    return TRUE;
}

void VsSeekerUpdateExpertQualifications(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sExpertQualifications); i++)
    {
        const struct VsSeekerExpertQualification *qualification = &sExpertQualifications[i];

        if (FlagGet(qualification->qualificationFlag))
            continue;
        if (FlagGet(qualification->expertDefeatedFlag) || AreExpertPrerequisitesComplete(qualification))
            FlagSet(qualification->qualificationFlag);
    }
}

u32 VsSeekerTryActivate(const struct ObjectEventTemplate *objects, u32 objectCount, enum MapType mapType)
{
    u16 trainerIds[OBJECT_EVENT_TEMPLATES_COUNT];
    u32 i;
    u32 trainerCount;

    if (!I_VS_SEEKER_ENABLED || GetVsSeekerChargeSteps() != VSSEEKER_RECHARGE_STEPS)
        return 0;

    trainerCount = CollectDefeatedTrainerIds(objects, objectCount, mapType, trainerIds);
    if (trainerCount == 0)
        return 0;

    // Preserve every newly completed route-expert requirement before any of
    // its ordinary Trainer flags can be cleared.
    VsSeekerUpdateExpertQualifications();
    for (i = 0; i < trainerCount; i++)
        ClearTrainerFlag(trainerIds[i]);

    SetVsSeekerChargeSteps(0);
    return trainerCount;
}

static u32 TryActivateVsSeekerOnCurrentMap(void)
{
    if (gMapHeader.events == NULL)
        return 0;

    return VsSeekerTryActivate(gSaveBlock1Ptr->objectEventTemplates,
                               gMapHeader.events->objectEventCount,
                               gMapHeader.mapType);
}

static enum VsSeekerUseResult CanUseVsSeeker(void)
{
    if (GetVsSeekerChargeSteps() != VSSEEKER_RECHARGE_STEPS)
    {
        ConvertIntToDecimalStringN(gStringVar1, GetVsSeekerRemainingSteps(), STR_CONV_MODE_LEFT_ALIGN, 3);
        return VSSEEKER_NOT_CHARGED;
    }

    if (gMapHeader.events == NULL
     || VsSeekerCountDefeatedTrainers(gSaveBlock1Ptr->objectEventTemplates,
                                      gMapHeader.events->objectEventCount,
                                      gMapHeader.mapType) == 0)
        return VSSEEKER_NO_DEFEATED_TRAINERS;

    return VSSEEKER_CAN_USE;
}

#define tCountdown    data[0]
#define tBeepDelay    data[1]
#define tNumBeeps     data[2]
#define tResetCount   data[3]

void Task_InitVsSeekerAndCheckForTrainersOnScreen(u8 taskId)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gTasks[taskId].data); i++)
        gTasks[taskId].data[i] = 0;

    if (!IsVsSeekerMapTypeValid(gMapHeader.mapType))
    {
        DisplayItemMessageOnField(taskId, VSSeeker_Text_OnlyWorksOnRoutes, Task_ItemUse_CloseMessageBoxAndReturnToField_VsSeeker);
        return;
    }

    switch (CanUseVsSeeker())
    {
    case VSSEEKER_NOT_CHARGED:
        DisplayItemMessageOnField(taskId, VSSeeker_Text_BatteryNotChargedNeedXSteps, Task_ItemUse_CloseMessageBoxAndReturnToField_VsSeeker);
        break;
    case VSSEEKER_NO_DEFEATED_TRAINERS:
        DisplayItemMessageOnField(taskId, VSSeeker_Text_NoTrainersWithinRange, Task_ItemUse_CloseMessageBoxAndReturnToField_VsSeeker);
        break;
    case VSSEEKER_CAN_USE:
        FieldEffectStart(FLDEFF_USE_VS_SEEKER);
        gTasks[taskId].func = Task_VsSeekerFrameCountdown;
        gTasks[taskId].tCountdown = 15;
        break;
    }
}

static void Task_VsSeekerFrameCountdown(u8 taskId)
{
    if (--gTasks[taskId].tCountdown == 0)
    {
        gTasks[taskId].func = Task_VsSeeker_PlaySoundAndResetTrainers;
        gTasks[taskId].tBeepDelay = 16;
    }
}

static void Task_VsSeeker_PlaySoundAndResetTrainers(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (task->tNumBeeps != 2 && --task->tBeepDelay == 0)
    {
        PlaySE(SE_CONTEST_MONS_TURN);
        task->tBeepDelay = 11;
        task->tNumBeeps++;
    }

    if (!FieldEffectActiveListContains(FLDEFF_USE_VS_SEEKER))
    {
        task->tResetCount = TryActivateVsSeekerOnCurrentMap();
        ScriptMovement_StartObjectMovementScript(LOCALID_PLAYER,
                                                  gSaveBlock1Ptr->location.mapNum,
                                                  gSaveBlock1Ptr->location.mapGroup,
                                                  sMovementScript_Wait48);
        task->func = Task_VsSeeker_ShowResponseToPlayer;
    }
}

static void Task_VsSeeker_ShowResponseToPlayer(u8 taskId)
{
    if (!ScriptMovement_IsObjectMovementFinished(LOCALID_PLAYER,
                                                 gSaveBlock1Ptr->location.mapNum,
                                                 gSaveBlock1Ptr->location.mapGroup))
        return;

    if (gTasks[taskId].tResetCount == 0)
    {
        DisplayItemMessageOnField(taskId, VSSeeker_Text_NoTrainersWithinRange, Task_ItemUse_CloseMessageBoxAndReturnToField_VsSeeker);
    }
    else
    {
        PlaySE(SE_PIN);
        DisplayItemMessageOnField(taskId, VSSeeker_Text_TrainersReset, Task_ItemUse_CloseMessageBoxAndReturnToField_VsSeeker);
    }
}

#undef tCountdown
#undef tBeepDelay
#undef tNumBeeps
#undef tResetCount

// Retained as a harmless parser marker for legacy scripts that still use the
// old vsseeker_rematchid macro. It is deliberately not an eligibility shape.
void NativeVsSeekerRematchId(struct ScriptContext *ctx)
{
    ScriptReadHalfword(ctx);
}
