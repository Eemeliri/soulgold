#include "global.h"
#include "bg.h"
#include "config/version.h"
#include "docs_menu.h"
#include "gpu_regs.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "random.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#include "data/docs_qr.h"

enum
{
    COLOR_BACKGROUND = 1,
    COLOR_WHITE,
    COLOR_BLACK,
    COLOR_MUTED,
    COLOR_ACCENT,
};

#define QR_SCALE 3
#define QR_QUIET_ZONE 4
#define QR_PIXELS ((DOCS_QR_SIZE + QR_QUIET_ZONE * 2) * QR_SCALE)
#define QR_LEFT 6
#define QR_TOP 28
#define TEXT_LEFT 138

STATIC_ASSERT(QR_LEFT + QR_PIXELS < TEXT_LEFT, DocsQrFitsBesideText);
STATIC_ASSERT(QR_TOP + QR_PIXELS <= DISPLAY_HEIGHT, DocsQrFitsScreen);
STATIC_ASSERT(ARRAY_COUNT(sDocsQrModules) == 2, DocsQrHasTwoPages);
STATIC_ASSERT(ARRAY_COUNT(sDocsQrChecksums) == ARRAY_COUNT(sDocsQrModules), DocsQrChecksumsMatchPages);

static const struct BgTemplate sBgTemplate =
{
    .bg = 0,
    .charBaseIndex = 0,
    .mapBaseIndex = 31,
    .screenSize = 0,
    .paletteMode = 0,
    .priority = 0,
    .baseTile = 0,
};

static const struct WindowTemplate sWindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = DISPLAY_TILE_WIDTH,
        .height = DISPLAY_TILE_HEIGHT,
        .paletteNum = 0,
        .baseBlock = 1,
    },
    DUMMY_WIN_TEMPLATE
};

static const u16 sPalette[] =
{
    [0] = RGB(4, 7, 12),
    [COLOR_BACKGROUND] = RGB(4, 7, 12),
    [COLOR_WHITE] = RGB_WHITE,
    [COLOR_BLACK] = RGB_BLACK,
    [COLOR_MUTED] = RGB(22, 24, 27),
    [COLOR_ACCENT] = RGB(31, 25, 9),
};

static const u8 sTextColors[] = {COLOR_BACKGROUND, COLOR_WHITE, COLOR_BACKGROUND};
static const u8 sMutedColors[] = {COLOR_BACKGROUND, COLOR_MUTED, COLOR_BACKGROUND};
static const u8 sAccentColors[] = {COLOR_BACKGROUND, COLOR_ACCENT, COLOR_BACKGROUND};
static const u8 sText_Docs[] = _("Documentation");
static const u8 sText_Guides[] = _("Guides");
static const u8 sText_Version[] = _(DISPLAY_VERSION);
static const u8 sText_Scan[] = _("Scan with your phone");
static const u8 sText_OpenManually[] = _("Open the website\nmanually");
static const u8 sText_QrBlocked[] = _("QR code blocked.\nUse the address\non the right.");
static const u8 sText_DocsDescription[] = _("Pokédex, items\nand locations");
static const u8 sText_GuidesDescription[] = _("Guides, tips and\nFAQ");
static const u8 sText_Website[] = _("eemeliri.github.io\n/soulgold/");
static const u8 sText_SwitchToGuides[] = _("A: Guides");
static const u8 sText_SwitchToDocs[] = _("A: Docs");
static const u8 sText_Back[] = _("B: Back");

static bool8 ReadDocsQr(u8 page, u8 *modules)
{
    const volatile u8 *source;
    u32 i;

    if (page >= ARRAY_COUNT(sDocsQrModules))
        return FALSE;

    // Force actual ROM reads even with LTO. Draw this same checked copy, so
    // replacing the matrix cannot evade a check folded away by the compiler.
    source = (const volatile u8 *)sDocsQrModules[page];
    for (i = 0; i < sizeof(sDocsQrModules[0]); i++)
        modules[i] = source[i];

    return Crc32B(modules, sizeof(sDocsQrModules[0])) == sDocsQrChecksums[page];
}

static void DrawDocsPage(u8 page)
{
    u8 modules[DOCS_QR_SIZE][(DOCS_QR_SIZE + 7) / 8];
    bool8 qrValid = ReadDocsQr(page, &modules[0][0]);
    u32 x, y;
    u32 versionX = DISPLAY_WIDTH - 8 - GetStringWidth(FONT_SMALL, sText_Version, 0);

    FillWindowPixelBuffer(0, PIXEL_FILL(COLOR_BACKGROUND));
    AddTextPrinterParameterized3(0, FONT_NORMAL, 8, 3, sTextColors, TEXT_SKIP_DRAW,
                                 page == 0 ? sText_Docs : sText_Guides);
    AddTextPrinterParameterized3(0, FONT_SMALL, versionX, 5, sAccentColors, TEXT_SKIP_DRAW, sText_Version);

    if (qrValid)
    {
        // Leave four whole white modules around the code. Never smooth or stretch it.
        FillWindowPixelRect(0, PIXEL_FILL(COLOR_WHITE), QR_LEFT, QR_TOP, QR_PIXELS, QR_PIXELS);
        for (y = 0; y < DOCS_QR_SIZE; y++)
        {
            for (x = 0; x < DOCS_QR_SIZE; x++)
            {
                if (modules[y][x / 8] & (0x80 >> (x % 8)))
                    FillWindowPixelRect(0, PIXEL_FILL(COLOR_BLACK),
                                        QR_LEFT + (x + QR_QUIET_ZONE) * QR_SCALE,
                                        QR_TOP + (y + QR_QUIET_ZONE) * QR_SCALE, QR_SCALE, QR_SCALE);
            }
        }
    }
    else
    {
        AddTextPrinterParameterized3(0, FONT_SMALL, QR_LEFT + 8, QR_TOP + 29,
                                     sMutedColors, TEXT_SKIP_DRAW, sText_QrBlocked);
    }

    AddTextPrinterParameterized3(0, FONT_SMALL, TEXT_LEFT, 30, sTextColors, TEXT_SKIP_DRAW,
                                 qrValid ? sText_Scan : sText_OpenManually);
    AddTextPrinterParameterized3(0, FONT_SMALL, TEXT_LEFT, 62, sMutedColors, TEXT_SKIP_DRAW,
                                 page == 0 ? sText_DocsDescription : sText_GuidesDescription);
    AddTextPrinterParameterized3(0, FONT_SMALL, TEXT_LEFT, 91, sMutedColors, TEXT_SKIP_DRAW, sText_Website);
    AddTextPrinterParameterized3(0, FONT_SMALL, TEXT_LEFT, 121, sAccentColors, TEXT_SKIP_DRAW,
                                 page == 0 ? sText_SwitchToGuides : sText_SwitchToDocs);
    AddTextPrinterParameterized3(0, FONT_SMALL, TEXT_LEFT, 137, sTextColors, TEXT_SKIP_DRAW, sText_Back);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void Task_DocsReturnToField(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetVBlankCallback(NULL);
        FreeAllWindowBuffers();
        DestroyTask(taskId);
        SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    }
}

static void Task_DocsInput(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_DocsReturnToField;
    }
    else if (JOY_NEW(A_BUTTON | DPAD_LEFT | DPAD_RIGHT))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].data[0] ^= 1;
        DrawDocsPage(gTasks[taskId].data[0]);
    }
}

static void CB2_DocsMenu(void)
{
    RunTasks();
    UpdatePaletteFade();
}

static void VBlankCB_DocsMenu(void)
{
    TransferPlttBuffer();
}

void CB2_InitDocsMenu(void)
{
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
    DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
    ResetPaletteFade();
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, &sBgTemplate, 1);
    ChangeBgX(0, 0, BG_COORD_SET);
    ChangeBgY(0, 0, BG_COORD_SET);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    LoadPalette(sPalette, BG_PLTT_ID(0), sizeof(sPalette));
    DrawDocsPage(0);
    ShowBg(0);
    CreateTask(Task_DocsInput, 0);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetVBlankCallback(VBlankCB_DocsMenu);
    SetMainCallback2(CB2_DocsMenu);
}
