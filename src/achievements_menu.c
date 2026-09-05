#include "global.h"
#include "achievements.h"
#include "bg.h"
#include "comfy_anim.h"
#include "decompress.h"
#include "graphics.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "list_menu.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define ACHIEVEMENTS_VISIBLE_ROWS 6
#define ACHIEVEMENTS_MENU_ICON_TAG_BASE 0xAC00
#define ACHIEVEMENTS_SCROLL_ARROW_TAG 0xAC80
#define ACHIEVEMENTS_BLANK_TILE 0
#define ACHIEVEMENTS_MENU_PAL_SLOT 1
#define ACHIEVEMENTS_MENU_MAP_BASE 29
#define ACHIEVEMENTS_STATUS_LEFT 192
#define ACHIEVEMENTS_STATUS_WIDTH 48
#define ACHIEVEMENTS_ROW_HEIGHT 15
#define ACHIEVEMENTS_TEXT_Y(row) (4 + (row) * ACHIEVEMENTS_ROW_HEIGHT)
#define ACHIEVEMENTS_CURSOR_X 14
#define ACHIEVEMENTS_CURSOR_CLEAR_X 0
#define ACHIEVEMENTS_CURSOR_CLEAR_WIDTH 48
#define ACHIEVEMENTS_CURSOR_CLEAR_HEIGHT 96
#define ACHIEVEMENTS_CURSOR_ANIM_DURATION 8
#define ACHIEVEMENTS_BACKGROUND_SCROLL_SPEED 128
#define ACHIEVEMENTS_NAME_X 54
#define ACHIEVEMENTS_ICON_X 35
#define ACHIEVEMENTS_ICON_Y(row) (27 + (row) * ACHIEVEMENTS_ROW_HEIGHT)
#define ACHIEVEMENTS_FOOTER_TEXT_X 8
#define ACHIEVEMENTS_FOOTER_TEXT_Y 26
#define ACHIEVEMENTS_SCROLL_ARROW_X 170
#define ACHIEVEMENTS_SCROLL_ARROW_TOP_Y 18
#define ACHIEVEMENTS_SCROLL_ARROW_BOTTOM_Y 118
#define ACHIEVEMENTS_BALL_ICON_SIZE (4 * TILE_SIZE_4BPP)

enum
{
    BG_DETAIL,
    BG_TEXT,
    BG_MENU,
    BG_BACKGROUND,
};

enum
{
    WIN_HEADER,
    WIN_LIST,
    WIN_FOOTER,
};

static void CB2_AchievementsMenu(void);
static void VBlankCB_AchievementsMenu(void);
static void Task_AchievementsMenu(u8 taskId);
static void DrawAchievementsMenu(void);
static void DrawHeader(void);
static void DrawList(void);
static void DrawAchievementFooter(void);
static void LoadMenuTilemap(void);
static void PrintListStatusText(const u8 *text, u8 y, const u8 *color);
static const u8 *GetAchievementDescription(const struct Achievement *achievement);
static void DrawListCursor(u8 row);
static void DrawListCursorAtY(s16 y);
static void UpdateListCursor(u16 oldCursor);
static void UpdateListCursorAnimation(void);
static void ResetListCursorAnimation(void);
static void CreateListBallIcon(u8 row, const struct Achievement *achievement);
static void TintBallIconIfLocked(u8 spriteId, const struct Achievement *achievement);
static void DestroyListBallIcons(void);
static void AddScrollArrows(void);
static void RemoveScrollArrows(void);
static void ExitAchievementsMenu(u8 taskId);
static void AnimateAchievementsBackground(void);

EWRAM_DATA static u16 sAchievementCursor = 0;
EWRAM_DATA static u16 sAchievementTop = 0;
EWRAM_DATA static u8 sListBallIconSpriteIds[ACHIEVEMENTS_VISIBLE_ROWS] = {};
EWRAM_DATA static struct SpriteTemplate sListBallIconTemplates[ACHIEVEMENTS_VISIBLE_ROWS] = {};
EWRAM_DATA static u8 sListCursorAnimId = 0;
EWRAM_DATA static s16 sListCursorY = 0;
EWRAM_DATA static u8 sScrollIndicatorArrowPairId = 0;
EWRAM_DATA static u16 sDetailTilemapBuffer[BG_SCREEN_SIZE / 2] = {};
EWRAM_DATA static u16 sTextTilemapBuffer[BG_SCREEN_SIZE / 2] = {};
EWRAM_DATA static u16 sMenuTilemapBuffer[BG_SCREEN_SIZE / 2] = {};
EWRAM_DATA static MainCallback sExitCallback = NULL;

static const u32 sBlankBgTile[8] = {};
static const u32 sAchievementsBgTiles[] = INCBIN_U32("graphics/pokegear/tiles.4bpp");
static const u16 sAchievementsBgTilemap[] = INCBIN_U16("graphics/pokegear/tiles.bin");
static const u16 sAchievementsBgPal[] = INCBIN_U16("graphics/pokegear/tiles.gbapal");
static const u32 sAchievementsMenuTiles[] = INCBIN_U32("graphics/achievements/menu.4bpp");
static const u16 sAchievementsMenuTilemap[] = INCBIN_U16("graphics/achievements/menu.bin");
static const u16 sAchievementsMenuPal[] = INCBIN_U16("graphics/achievements/menu.gbapal");

STATIC_ASSERT(ARRAY_COUNT(sAchievementsBgTilemap) == DISPLAY_TILE_WIDTH * DISPLAY_TILE_HEIGHT, AchievementsBgTilemapSize);

static const u8 sColor_DarkGray[3] = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY };
static const u8 sColor_Blue[3] = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_BLUE, TEXT_COLOR_LIGHT_BLUE };
static const u8 sColor_Green[3] = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_GREEN, TEXT_COLOR_LIGHT_GREEN };
static const u8 sColor_White[3] = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY };

struct AchievementBallIconGfx
{
    const u32 *tiles;
    const u16 *palette;
};

static const struct AchievementBallIconGfx sBallIconGfxByTier[] =
{
    [ACH_TIER_BRONZE] =
    {
        .tiles = gBallGfx_Poke,
        .palette = gBallPal_Poke,
    },
    [ACH_TIER_SILVER] =
    {
        .tiles = gBallGfx_Great,
        .palette = gBallPal_Great,
    },
    [ACH_TIER_GOLD] =
    {
        .tiles = gBallGfx_Ultra,
        .palette = gBallPal_Ultra,
    },
    [ACH_TIER_PLATINUM] =
    {
        .tiles = gBallGfx_Master,
        .palette = gBallPal_Master,
    },
};

static const struct OamData sOamData_BallIcon =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sAnim_BallIcon[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnims_BallIcon[] =
{
    sAnim_BallIcon,
};

static const struct SpriteTemplate sSpriteTemplate_BallIcon =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &sOamData_BallIcon,
    .anims = sAnims_BallIcon,
    .callback = SpriteCallbackDummy,
};

static const struct BgTemplate sBgTemplates[] =
{
    // Higher-priority BGs are listed first; text and popup layers stay separate.
    {
        .bg = BG_DETAIL,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = BG_TEXT,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = BG_MENU,
        .charBaseIndex = 0,
        .mapBaseIndex = ACHIEVEMENTS_MENU_MAP_BASE,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
    {
        .bg = BG_BACKGROUND,
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sWindowTemplates[] =
{
    // These base blocks share charbase 1, so keep them disjoint.
    [WIN_HEADER] =
    {
        .bg = BG_TEXT,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x024,
    },
    [WIN_LIST] =
    {
        .bg = BG_TEXT,
        .tilemapLeft = 0,
        .tilemapTop = 2,
        .width = 30,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 0x078,
    },
    [WIN_FOOTER] =
    {
        .bg = BG_DETAIL,
        .tilemapLeft = 0,
        .tilemapTop = 13,
        .width = 30,
        .height = 7,
        .paletteNum = 15,
        .baseBlock = 0x240,
    },
    DUMMY_WIN_TEMPLATE,
};

void CB2_InitAchievementsMenu(void)
{
    CB2_InitAchievementsMenuWithCallback(CB2_ReturnToFieldWithOpenMenu);
}

void CB2_InitAchievementsMenuWithCallback(MainCallback callback)
{
    u8 i;

    if (callback == NULL)
        callback = CB2_ReturnToFieldWithOpenMenu;
    sExitCallback = callback;
    SetVBlankHBlankCallbacksToNull();
    ClearScheduledBgCopiesToVram();
    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    CpuFill16(0, sDetailTilemapBuffer, sizeof(sDetailTilemapBuffer));
    CpuFill16(0, sTextTilemapBuffer, sizeof(sTextTilemapBuffer));
    CpuFill16(0, sMenuTilemapBuffer, sizeof(sMenuTilemapBuffer));
    SetBgTilemapBuffer(BG_DETAIL, sDetailTilemapBuffer);
    SetBgTilemapBuffer(BG_TEXT, sTextTilemapBuffer);
    SetBgTilemapBuffer(BG_MENU, sMenuTilemapBuffer);
    ResetAllBgsCoordinates();
    ResetPaletteFade();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    LoadMessageBoxAndBorderGfx();
    Menu_LoadStdPalAt(BG_PLTT_ID(15));
    DmaClear16(3, BG_SCREEN_ADDR(31), BG_SCREEN_SIZE);
    DmaClear16(3, BG_SCREEN_ADDR(30), BG_SCREEN_SIZE);
    DmaClear16(3, BG_SCREEN_ADDR(29), BG_SCREEN_SIZE);
    DmaClear16(3, BG_SCREEN_ADDR(28), BG_SCREEN_SIZE);
    LoadBgTiles(BG_DETAIL, sBlankBgTile, sizeof(sBlankBgTile), ACHIEVEMENTS_BLANK_TILE);
    LoadBgTiles(BG_MENU, sAchievementsMenuTiles, sizeof(sAchievementsMenuTiles), 0);
    LoadBgTiles(BG_BACKGROUND, sAchievementsBgTiles, sizeof(sAchievementsBgTiles), 0);
    LoadPalette(sAchievementsBgPal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
    LoadPalette(sAchievementsMenuPal, BG_PLTT_ID(ACHIEVEMENTS_MENU_PAL_SLOT), PLTT_SIZE_4BPP);
    FillBgTilemapBufferRect_Palette0(BG_DETAIL, ACHIEVEMENTS_BLANK_TILE, 0, 0, DISPLAY_TILE_WIDTH, DISPLAY_TILE_HEIGHT);
    FillBgTilemapBufferRect_Palette0(BG_TEXT, ACHIEVEMENTS_BLANK_TILE, 0, 0, DISPLAY_TILE_WIDTH, DISPLAY_TILE_HEIGHT);
    LoadMenuTilemap();
    for (i = 0; i < DISPLAY_TILE_HEIGHT; i++)
    {
        LoadBgTilemap(BG_BACKGROUND,
                      &sAchievementsBgTilemap[i * DISPLAY_TILE_WIDTH],
                      DISPLAY_TILE_WIDTH * sizeof(sAchievementsBgTilemap[0]),
                      i * 32);
    }
    CopyBgTilemapBufferToVram(BG_DETAIL);
    CopyBgTilemapBufferToVram(BG_TEXT);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_BG3_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    ShowBg(BG_DETAIL);
    ShowBg(BG_TEXT);
    ShowBg(BG_MENU);
    ShowBg(BG_BACKGROUND);

    sAchievementCursor = 0;
    sAchievementTop = 0;
    sListCursorAnimId = INVALID_COMFY_ANIM;
    sListCursorY = ACHIEVEMENTS_TEXT_Y(0);
    sScrollIndicatorArrowPairId = TASK_NONE;
    for (i = 0; i < ACHIEVEMENTS_VISIBLE_ROWS; i++)
        sListBallIconSpriteIds[i] = MAX_SPRITES;
    DrawAchievementsMenu();
    AddScrollArrows();
    CreateTask(Task_AchievementsMenu, 0);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    gPaletteFade.bufferTransferDisabled = FALSE;
    SetVBlankCallback(VBlankCB_AchievementsMenu);
    SetMainCallback2(CB2_AchievementsMenu);
}

static void VBlankCB_AchievementsMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_AchievementsMenu(void)
{
    RunTasks();
    //AnimateAchievementsBackground();
    UpdateListCursorAnimation();
    AnimateSprites();
    BuildOamBuffer();
    RunTextPrinters();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void DrawHeader(void)
{
    PutWindowTilemap(WIN_HEADER);
    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(0));
    AddTextPrinterParameterized3(WIN_HEADER, FONT_SMALL, 10, 2, sColor_DarkGray, TEXT_SKIP_DRAW, COMPOUND_STRING("Trophies"));

    ConvertIntToDecimalStringN(gStringVar1, Achievement_CountUnlocked(), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, Achievement_GetCount(), STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("{STR_VAR_1}/{STR_VAR_2}"));
    AddTextPrinterParameterized3(WIN_HEADER, FONT_SMALL, 203, 2, sColor_DarkGray, TEXT_SKIP_DRAW, gStringVar4);
        
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}

static void LoadMenuTilemap(void)
{
    u16 i;

    for (i = 0; i < BG_SCREEN_SIZE / 2; i++)
        sMenuTilemapBuffer[i] = (sAchievementsMenuTilemap[i] & 0x0FFF) | (ACHIEVEMENTS_MENU_PAL_SLOT << 12);
    CopyBgTilemapBufferToVram(BG_MENU);
}

static void PrintListStatusText(const u8 *text, u8 y, const u8 *color)
{
    u8 x = ACHIEVEMENTS_STATUS_LEFT + GetStringCenterAlignXOffset(FONT_SMALL, text, ACHIEVEMENTS_STATUS_WIDTH);

    AddTextPrinterParameterized3(WIN_LIST, FONT_SMALL, x, y, color, TEXT_SKIP_DRAW, text);
}

static void PrintAchievementProgress(const struct Achievement *achievement, u8 y)
{
    u32 progress = Achievement_GetProgress(achievement);
    u32 target = Achievement_GetTarget(achievement);

    if (Achievement_IsUnlocked(achievement->id))
    {
        PrintListStatusText(COMPOUND_STRING("Done"), y, sColor_Green);
    }
    else if (achievement->id == ACH_MILLIONAIRE || achievement->id == ACH_SPENDTHRIFT)
    {
        PrintListStatusText(COMPOUND_STRING("Locked"), y, sColor_DarkGray);
    }
    else if (target > 1)
    {
        if (progress > target)
            progress = target;
        ConvertIntToDecimalStringN(gStringVar1, progress, STR_CONV_MODE_LEFT_ALIGN, 4);
        ConvertIntToDecimalStringN(gStringVar2, target, STR_CONV_MODE_LEFT_ALIGN, 4);
        StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("{STR_VAR_1}/{STR_VAR_2}"));
        PrintListStatusText(gStringVar4, y, sColor_Blue);
    }
    else
    {
        PrintListStatusText(COMPOUND_STRING("Locked"), y, sColor_DarkGray);
    }
}

static const u8 *GetAchievementDescription(const struct Achievement *achievement)
{
    if (achievement->id == ACH_MILLIONAIRE || achievement->id == ACH_SPENDTHRIFT)
    {
        ConvertIntToDecimalStringN(
            gStringVar1,
            Achievement_GetProgress(achievement),
            STR_CONV_MODE_LEFT_ALIGN,
            10);
        if (achievement->id == ACH_MILLIONAIRE)
        {
            StringExpandPlaceholders(
                gStringVar4,
                COMPOUND_STRING("Earn ¥1,000,000 in total.\n(¥{STR_VAR_1} / ¥1,000,000)"));
        }
        else
        {
            StringExpandPlaceholders(
                gStringVar4,
                COMPOUND_STRING("Spend ¥1,000,000 in total.\n(¥{STR_VAR_1} / ¥1,000,000)"));
        }
        return gStringVar4;
    }

    return achievement->description;
}

static void TintBallIconIfLocked(u8 spriteId, const struct Achievement *achievement)
{
    u8 i;
    u8 paletteNum;
    u16 palette[16];

    if (Achievement_IsUnlocked(achievement->id))
        return;

    paletteNum = gSprites[spriteId].oam.paletteNum;
    CpuCopy16(&gPlttBufferUnfaded[OBJ_PLTT_ID(paletteNum)], palette, sizeof(palette));
    for (i = 1; i < ARRAY_COUNT(palette); i++)
    {
        u16 color = palette[i];
        u8 gray = (GET_R(color) + GET_G(color) + GET_B(color)) / 3;

        palette[i] = RGB(gray, gray, gray);
    }
    LoadPalette(palette, OBJ_PLTT_ID(paletteNum), sizeof(palette));
}

static void DestroyListBallIcons(void)
{
    u8 i;

    for (i = 0; i < ACHIEVEMENTS_VISIBLE_ROWS; i++)
    {
        if (sListBallIconSpriteIds[i] != MAX_SPRITES)
        {
            u16 tag = ACHIEVEMENTS_MENU_ICON_TAG_BASE + i;

            FreeSpriteTilesByTag(tag);
            FreeSpritePaletteByTag(tag);
            FreeSpriteOamMatrix(&gSprites[sListBallIconSpriteIds[i]]);
            DestroySprite(&gSprites[sListBallIconSpriteIds[i]]);
            sListBallIconSpriteIds[i] = MAX_SPRITES;
        }
    }
}

static void CreateListBallIcon(u8 row, const struct Achievement *achievement)
{
    u16 tag = ACHIEVEMENTS_MENU_ICON_TAG_BASE + row;
    enum AchievementTier tier = achievement->tier;
    struct CompressedSpriteSheet spriteSheet;
    struct SpritePalette spritePalette;
    struct SpriteTemplate *spriteTemplate = &sListBallIconTemplates[row];
    u8 spriteId;

    if (tier >= ARRAY_COUNT(sBallIconGfxByTier))
        tier = ACH_TIER_BRONZE;

    spriteSheet.data = sBallIconGfxByTier[tier].tiles;
    spriteSheet.size = ACHIEVEMENTS_BALL_ICON_SIZE;
    spriteSheet.tag = tag;
    LoadCompressedSpriteSheet(&spriteSheet);

    spritePalette.data = sBallIconGfxByTier[tier].palette;
    spritePalette.tag = tag;
    LoadSpritePalette(&spritePalette);

    CpuCopy16(&sSpriteTemplate_BallIcon, spriteTemplate, sizeof(*spriteTemplate));
    spriteTemplate->tileTag = tag;
    spriteTemplate->paletteTag = tag;
    spriteId = CreateSprite(spriteTemplate, 0, 0, 0);

    if (spriteId == MAX_SPRITES)
    {
        FreeSpriteTilesByTag(tag);
        FreeSpritePaletteByTag(tag);
        return;
    }
    sListBallIconSpriteIds[row] = spriteId;
    gSprites[spriteId].x = ACHIEVEMENTS_ICON_X;
    gSprites[spriteId].y = ACHIEVEMENTS_ICON_Y(row);
    gSprites[spriteId].oam.priority = 0;
    TintBallIconIfLocked(spriteId, achievement);
}

static void DrawListCursor(u8 row)
{
    sListCursorY = ACHIEVEMENTS_TEXT_Y(row);
    DrawListCursorAtY(sListCursorY);
}

static void DrawListCursorAtY(s16 y)
{
    AddTextPrinterParameterized3(WIN_LIST, FONT_SMALL, ACHIEVEMENTS_CURSOR_X, y, sColor_DarkGray, TEXT_SKIP_DRAW, gText_SelectorArrow2);
}

static void CopyListCursorColumnToVram(void)
{
    CopyWindowRectToVram(
        WIN_LIST,
        COPYWIN_GFX,
        ACHIEVEMENTS_CURSOR_CLEAR_X / 8,
        0,
        (ACHIEVEMENTS_CURSOR_CLEAR_WIDTH + 7) / 8,
        (ACHIEVEMENTS_CURSOR_CLEAR_HEIGHT + 7) / 8);
}

static void ClearListCursorColumn(void)
{
    FillWindowPixelRect(
        WIN_LIST,
        PIXEL_FILL(0),
        ACHIEVEMENTS_CURSOR_CLEAR_X,
        0,
        ACHIEVEMENTS_CURSOR_CLEAR_WIDTH,
        ACHIEVEMENTS_CURSOR_CLEAR_HEIGHT);
}

static void DrawAndCopyListCursorAtY(s16 y)
{
    sListCursorY = y;
    ClearListCursorColumn();
    DrawListCursorAtY(y);
    CopyListCursorColumnToVram();
}

static void ResetListCursorAnimation(void)
{
    if (sListCursorAnimId != INVALID_COMFY_ANIM)
    {
        ReleaseComfyAnim(sListCursorAnimId);
        sListCursorAnimId = INVALID_COMFY_ANIM;
    }
}

static void StartListCursorAnimation(s16 fromY, s16 toY)
{
    struct ComfyAnimEasingConfig config;

    ResetListCursorAnimation();
    if (fromY == toY)
    {
        DrawAndCopyListCursorAtY(toY);
        return;
    }

    InitComfyAnimConfig_Easing(&config);
    config.durationFrames = ACHIEVEMENTS_CURSOR_ANIM_DURATION;
    config.easingFunc = ComfyAnimEasing_EaseOutCubic;
    config.from = Q_24_8(fromY);
    config.to = Q_24_8(toY);
    sListCursorAnimId = CreateComfyAnim_Easing(&config);
    if (sListCursorAnimId == INVALID_COMFY_ANIM)
        DrawAndCopyListCursorAtY(toY);
    else
        DrawAndCopyListCursorAtY(fromY);
}

static void UpdateListCursorAnimation(void)
{
    struct ComfyAnim *anim;

    if (sListCursorAnimId == INVALID_COMFY_ANIM)
        return;

    anim = &gComfyAnims[sListCursorAnimId];
    if (!anim->inUse)
    {
        sListCursorAnimId = INVALID_COMFY_ANIM;
        return;
    }

    TryAdvanceComfyAnim(anim);
    DrawAndCopyListCursorAtY(ReadComfyAnimValueSmooth(anim));
    if (anim->completed)
    {
        ReleaseComfyAnim(sListCursorAnimId);
        sListCursorAnimId = INVALID_COMFY_ANIM;
    }
}

static void UpdateListCursor(u16 oldCursor)
{
    u8 oldRow = oldCursor - sAchievementTop;
    u8 newRow = sAchievementCursor - sAchievementTop;
    s16 fromY;

    if (oldCursor == sAchievementCursor)
        return;

    fromY = sListCursorAnimId == INVALID_COMFY_ANIM ? ACHIEVEMENTS_TEXT_Y(oldRow) : sListCursorY;
    StartListCursorAnimation(fromY, ACHIEVEMENTS_TEXT_Y(newRow));
}

static void DrawList(void)
{
    u8 i;
    u16 count = Achievement_GetCount();

    ResetListCursorAnimation();
    DestroyListBallIcons();
    PutWindowTilemap(WIN_LIST);
    FillWindowPixelBuffer(WIN_LIST, PIXEL_FILL(0));
    for (i = 0; i < ACHIEVEMENTS_VISIBLE_ROWS && sAchievementTop + i < count; i++)
    {
        const struct Achievement *achievement = Achievement_GetByIndex(sAchievementTop + i);
        u8 textY = ACHIEVEMENTS_TEXT_Y(i);

        if (sAchievementCursor == sAchievementTop + i)
            DrawListCursor(i);
        CreateListBallIcon(i, achievement);
        AddTextPrinterParameterized3(WIN_LIST, FONT_SMALL, ACHIEVEMENTS_NAME_X, textY, sColor_DarkGray, TEXT_SKIP_DRAW, achievement->name);
        PrintAchievementProgress(achievement, textY);
    }
    CopyWindowToVram(WIN_LIST, COPYWIN_FULL);
}

static void DrawAchievementFooter(void)
{
    const struct Achievement *achievement;

    PutWindowTilemap(WIN_FOOTER);
    FillWindowPixelBuffer(WIN_FOOTER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    if (Achievement_GetCount() != 0)
    {
        achievement = Achievement_GetByIndex(sAchievementCursor);
        AddTextPrinterParameterized3(
            WIN_FOOTER,
            FONT_SMALL,
            ACHIEVEMENTS_FOOTER_TEXT_X,
            ACHIEVEMENTS_FOOTER_TEXT_Y,
            sColor_White,
            TEXT_SKIP_DRAW,
            GetAchievementDescription(achievement));
    }
    CopyWindowToVram(WIN_FOOTER, COPYWIN_FULL);
}

static void DrawAchievementsMenu(void)
{
    DrawHeader();
    DrawList();
    DrawAchievementFooter();
}

static void AddScrollArrows(void)
{
    u16 count = Achievement_GetCount();

    if (sScrollIndicatorArrowPairId == TASK_NONE && count > ACHIEVEMENTS_VISIBLE_ROWS)
    {
        sScrollIndicatorArrowPairId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            ACHIEVEMENTS_SCROLL_ARROW_X,
            ACHIEVEMENTS_SCROLL_ARROW_TOP_Y,
            ACHIEVEMENTS_SCROLL_ARROW_BOTTOM_Y,
            count - ACHIEVEMENTS_VISIBLE_ROWS,
            ACHIEVEMENTS_SCROLL_ARROW_TAG,
            ACHIEVEMENTS_SCROLL_ARROW_TAG,
            &sAchievementTop);
    }
}

static void RemoveScrollArrows(void)
{
    if (sScrollIndicatorArrowPairId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sScrollIndicatorArrowPairId);
        sScrollIndicatorArrowPairId = TASK_NONE;
    }
}

static void UNUSED AnimateAchievementsBackground(void)
{
    ChangeBgY(BG_BACKGROUND, ACHIEVEMENTS_BACKGROUND_SCROLL_SPEED, BG_COORD_ADD);
}

static void MoveCursor(s16 delta)
{
    u16 oldTop = sAchievementTop;
    u16 oldCursor = sAchievementCursor;
    u8 oldRow = sAchievementCursor - sAchievementTop;
    u16 count = Achievement_GetCount();
    s32 newCursor;
    bool8 isPageJump = delta <= -ACHIEVEMENTS_VISIBLE_ROWS || delta >= ACHIEVEMENTS_VISIBLE_ROWS;

    if (count == 0)
        return;

    newCursor = sAchievementCursor + delta;
    if (newCursor < 0)
        newCursor = 0;
    else if (newCursor >= count)
        newCursor = count - 1;
    sAchievementCursor = newCursor;

    if (count <= ACHIEVEMENTS_VISIBLE_ROWS)
    {
        sAchievementTop = 0;
    }
    else if (isPageJump)
    {
        if (sAchievementCursor >= oldRow)
            sAchievementTop = sAchievementCursor - oldRow;
        else
            sAchievementTop = 0;

        if (sAchievementTop + ACHIEVEMENTS_VISIBLE_ROWS > count)
            sAchievementTop = count - ACHIEVEMENTS_VISIBLE_ROWS;
    }
    else
    {
        if (sAchievementCursor < sAchievementTop)
            sAchievementTop = sAchievementCursor;
        else if (sAchievementCursor >= sAchievementTop + ACHIEVEMENTS_VISIBLE_ROWS)
            sAchievementTop = sAchievementCursor - ACHIEVEMENTS_VISIBLE_ROWS + 1;
    }

    if (sAchievementCursor == oldCursor && sAchievementTop == oldTop)
        return;

    PlaySE(SE_SELECT);
    if (sAchievementTop != oldTop)
        DrawList();
    else
        UpdateListCursor(oldCursor);
    DrawAchievementFooter();
}

static void Task_AchievementsMenu(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    if (JOY_REPEAT(DPAD_UP))
        MoveCursor(-1);
    else if (JOY_REPEAT(DPAD_DOWN))
        MoveCursor(1);
    else if (JOY_REPEAT(DPAD_LEFT))
        MoveCursor(-ACHIEVEMENTS_VISIBLE_ROWS);
    else if (JOY_REPEAT(DPAD_RIGHT))
        MoveCursor(ACHIEVEMENTS_VISIBLE_ROWS);
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = ExitAchievementsMenu;
    }
}

static void ExitAchievementsMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        RemoveScrollArrows();
        ResetListCursorAnimation();
        DestroyListBallIcons();
        FreeAllWindowBuffers();
        SetMainCallback2(sExitCallback);
    }
}

#undef ACHIEVEMENTS_VISIBLE_ROWS
#undef ACHIEVEMENTS_MENU_ICON_TAG_BASE
#undef ACHIEVEMENTS_SCROLL_ARROW_TAG
#undef ACHIEVEMENTS_BLANK_TILE
#undef ACHIEVEMENTS_MENU_PAL_SLOT
#undef ACHIEVEMENTS_MENU_MAP_BASE
#undef ACHIEVEMENTS_STATUS_RIGHT
#undef ACHIEVEMENTS_ROW_HEIGHT
#undef ACHIEVEMENTS_TEXT_Y
#undef ACHIEVEMENTS_CURSOR_X
#undef ACHIEVEMENTS_CURSOR_CLEAR_X
#undef ACHIEVEMENTS_CURSOR_CLEAR_WIDTH
#undef ACHIEVEMENTS_CURSOR_CLEAR_HEIGHT
#undef ACHIEVEMENTS_CURSOR_ANIM_DURATION
#undef ACHIEVEMENTS_BACKGROUND_SCROLL_SPEED
#undef ACHIEVEMENTS_NAME_X
#undef ACHIEVEMENTS_ICON_X
#undef ACHIEVEMENTS_ICON_Y
#undef ACHIEVEMENTS_FOOTER_TEXT_X
#undef ACHIEVEMENTS_FOOTER_TEXT_Y
#undef ACHIEVEMENTS_SCROLL_ARROW_X
#undef ACHIEVEMENTS_SCROLL_ARROW_TOP_Y
#undef ACHIEVEMENTS_SCROLL_ARROW_BOTTOM_Y
#undef ACHIEVEMENTS_BALL_ICON_SIZE
