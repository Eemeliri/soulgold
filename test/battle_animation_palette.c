#include "global.h"
#include "battle_anim.h"
#include "palette.h"
#include "sprite.h"
#include "task.h"
#include "test/test.h"
#include "constants/battle_anim.h"
#include "constants/rgb.h"

void AnimTask_CycleMagicalLeafPal(u8 taskId);
void AnimTask_BlendNightSlash(u8 taskId);
void AnimTask_RotateAuroraRingColors(u8 taskId);

static const u16 sTestPalette[16] = {RGB_WHITE};

static u32 LoadTestPalette(u16 tag)
{
    const struct SpritePalette palette =
    {
        .data = sTestPalette,
        .tag = tag,
    };

    return LoadSpritePalette(&palette);
}

static void ExpectMissingPaletteTaskToStop(TaskFunc taskFunc)
{
    u8 taskId;

    ResetTasks();
    FreeAllSpritePalettes();
    gAnimVisualTaskCount = 1;
    gBattleAnimArgs[7] = 0;

    taskId = CreateTask(taskFunc, 0);
    taskFunc(taskId);

    EXPECT(!gTasks[taskId].isActive);
    EXPECT_EQ(gAnimVisualTaskCount, 0);

    ResetTasks();
    gAnimVisualTaskCount = 0;
}

TEST("Battle animation palette tasks stop when their palette is unavailable")
{
    ExpectMissingPaletteTaskToStop(AnimTask_CycleMagicalLeafPal);
    ExpectMissingPaletteTaskToStop(AnimTask_RotateAuroraRingColors);
    ExpectMissingPaletteTaskToStop(AnimTask_BlendNightSlash);
}

TEST("Battle animation palette tasks still run when their palettes are loaded")
{
    u8 taskId;

    ResetTasks();
    FreeAllSpritePalettes();
    EXPECT_EQ(LoadTestPalette(ANIM_TAG_LEAF), 0);
    EXPECT_EQ(LoadTestPalette(ANIM_TAG_RAZOR_LEAF), 1);
    gAnimVisualTaskCount = 1;
    gBattleAnimArgs[7] = 0;
    taskId = CreateTask(AnimTask_CycleMagicalLeafPal, 0);
    AnimTask_CycleMagicalLeafPal(taskId);
    EXPECT(gTasks[taskId].isActive);
    EXPECT_EQ(gTasks[taskId].data[8], OBJ_PLTT_ID(0));
    EXPECT_EQ(gTasks[taskId].data[12], OBJ_PLTT_ID(1));
    DestroyAnimVisualTask(taskId);

    ResetTasks();
    FreeAllSpritePalettes();
    EXPECT_EQ(LoadTestPalette(ANIM_TAG_RAINBOW_RINGS), 0);
    gAnimVisualTaskCount = 1;
    gBattleAnimArgs[0] = 10;
    taskId = CreateTask(AnimTask_RotateAuroraRingColors, 0);
    AnimTask_RotateAuroraRingColors(taskId);
    EXPECT(gTasks[taskId].isActive);
    EXPECT_EQ(gTasks[taskId].data[2], OBJ_PLTT_ID(0));
    DestroyAnimVisualTask(taskId);

    ResetTasks();
    FreeAllSpritePalettes();
    EXPECT_EQ(LoadTestPalette(ANIM_TAG_SLASH), 0);
    gAnimVisualTaskCount = 1;
    taskId = CreateTask(AnimTask_BlendNightSlash, 0);
    AnimTask_BlendNightSlash(taskId);
    EXPECT(!gTasks[taskId].isActive);
    EXPECT_NE(gPlttBufferFaded[OBJ_PLTT_ID(0)], 0);
    EXPECT_EQ(gAnimVisualTaskCount, 0);

    ResetTasks();
    FreeAllSpritePalettes();
    gAnimVisualTaskCount = 0;
}
