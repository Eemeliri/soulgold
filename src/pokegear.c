#include "global.h"
#include "achievements.h"
#include "bg.h"
#include "decompress.h"
#include "dexnav.h"
#include "event_data.h"
#include "fieldmap.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "item_menu.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "pokegear.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/flags.h"
#include "constants/rgb.h"
#include "constants/songs.h"

enum
{
    WIN_POKEGEAR_MAIN,
    WIN_POKEGEAR_HEADER,
};

enum
{
    POKEGEAR_MODE_MAIN,
    POKEGEAR_MODE_JUKEBOX,
    POKEGEAR_MODE_REGISTER,
};

struct PokegearResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 cursorPos;
    u8 mode;
    u8 jukeboxCursor;
    u8 iconSpriteIds[POKEGEAR_APP_COUNT];
    bool8 openedFromShortcut;
};

struct PokegearTrack
{
    const u8 *name;
    u16 songId;
};

#define TAG_POKEGEAR_ICON_MAP    0x6780
#define TAG_POKEGEAR_ICON_DEXNAV 0x6781
#define TAG_POKEGEAR_ICON_TROPHY 0x6782
#define TAG_POKEGEAR_ICON_JUKEBOX 0x6783


#define POKEGEAR_BG_WIDTH 30
#define POKEGEAR_BG_HEIGHT 20
#define POKEGEAR_BUTTON_X 6
#define POKEGEAR_BUTTON_W 18
#define POKEGEAR_BUTTON_H 4
#define POKEGEAR_BUTTON_SRC_H 8
#define POKEGEAR_BUTTON_FIRST_Y 2
#define POKEGEAR_BUTTON_Y_SPACING 4

static EWRAM_DATA struct PokegearResources *sPokegear = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;
static EWRAM_DATA u8 sPokegearLastCursor = POKEGEAR_APP_MAP;

static void Pokegear_Init(MainCallback callback, bool8 openJukeboxShortcut);
static void PokegearRunSetup(void);
static bool8 PokegearDoGfxSetup(void);
static bool8 Pokegear_InitBgs(void);
static bool8 PokegearLoadGraphics(void);
static void Pokegear_InitWindows(void);
static void PokegearMainCB(void);
static void PokegearVBlankCB(void);
static void PokegearFreeResources(void);
static void PokegearFadeAndBail(void);
static bool8 IsDexNavAppUnlocked(void);
static u8 GetButtonY(u8 app);
static u8 GetNextSelectableApp(u8 app);
static u8 GetPreviousSelectableApp(u8 app);
static void EnsureCursorSelectable(void);
static void DrawMainScreen(void);
static void DrawMainButtons(bool8 fullRedraw);
static void DrawMainText(void);
static void DrawHeaderText(void);
static void DrawJukeboxScreen(void);
static void CreateMainIcons(void);
static void SetMainIconsVisible(bool8 visible);
static void Task_PokegearWaitFadeIn(u8 taskId);
static void Task_PokegearMain(u8 taskId);
static void Task_PokegearWaitFadeAndBail(u8 taskId);
static void Task_PokegearTurnOff(u8 taskId);
static void Task_PokegearOpenMap(u8 taskId);
static void Task_PokegearOpenDexNav(u8 taskId);
static void Task_PokegearOpenTrophies(u8 taskId);
static void Task_PokegearRegisterApp(u8 taskId);

static const u32 sPokegearBgTiles[] = INCBIN_U32("graphics/pokegear/tiles.4bpp.smol");
static const u16 sPokegearBgTilemap[] = INCBIN_U16("graphics/pokegear/tiles.bin");
static const u16 sPokegearBgPal[] = INCBIN_U16("graphics/pokegear/tiles.gbapal");
static const u32 sPokegearBgFemaleTiles[] = INCBIN_U32("graphics/pokegear/tiles_f.4bpp.smol");
static const u16 sPokegearBgFemaleTilemap[] = INCBIN_U16("graphics/pokegear/tiles_f.bin");
static const u16 sPokegearBgFemalePal[] = INCBIN_U16("graphics/pokegear/tiles_f.gbapal");
static const u32 sPokegearButtonTiles[] = INCBIN_U32("graphics/pokegear/tiles_button.4bpp.smol");
static const u16 sPokegearButtonTilemap[] = INCBIN_U16("graphics/pokegear/tiles_button.bin");
static const u16 sPokegearButtonPal[] = INCBIN_U16("graphics/pokegear/tiles_button.gbapal");
static const u16 sPokegearButtonPalF[] = INCBIN_U16("graphics/pokegear/tiles_button_f.gbapal");
static const u32 sPokegearIconsGfx[] = INCBIN_U32("graphics/pokegear/icons.4bpp.smol");
static const u16 sPokegearIconsPal[] = INCBIN_U16("graphics/pokegear/icons.gbapal");

static const u32 sPokegearIconMapGfx[]    = INCBIN_U32("graphics/pokegear/icon_map.4bpp.smol");
static const u32 sPokegearIconDexNavGfx[] = INCBIN_U32("graphics/pokegear/icon_phone.4bpp.smol");
static const u32 sPokegearIconTrophyGfx[] = INCBIN_U32("graphics/pokegear/icon_trophy.4bpp.smol");
static const u32 sPokegearIconJukeboxGfx[] = INCBIN_U32("graphics/pokegear/icon_jukebox.4bpp.smol");


static const u8 sText_Map[] = _("Map");
static const u8 sText_DexNav[] = _("DexNav");
static const u8 sText_Trophies[] = _("Trophies");
static const u8 sText_Jukebox[] = _("Jukebox");
static const u8 sText_Back[] = _("{B_BUTTON} Back");
static const u8 sText_MainHelp[] = _("{SELECT_BUTTON}Reg. {B_BUTTON}Back");
static const u8 sText_RegisterHelp[] = _("{DPAD_NONE}Slot {B_BUTTON}Back");
static const u8 sText_JukeboxTitle[] = _("Jukebox");
static const u8 sText_PlayMarker[] = _("{RIGHT_ARROW}");
static const u8 sText_PokemonMarch[] = _("Pokemon March");
static const u8 sText_PokemonLullaby[] = _("Pokemon Lullaby");
static const u8 sText_HoennSound[] = _("Hoenn Sound");
static const u8 sText_PokeFlute[] = _("Poke Flute");
static const u8 sText_OaksTalk[] = _("Oak's Talk");
static const u8 sText_DpadUp[] = _(" {DPAD_UP}");
static const u8 sText_DpadRight[] = _(" {DPAD_RIGHT}");
static const u8 sText_DpadDown[] = _(" {DPAD_DOWN}");
static const u8 sText_DpadLeft[] = _(" {DPAD_LEFT}");

static const u8 *const sMainLabels[POKEGEAR_APP_COUNT] =
{
    [POKEGEAR_APP_MAP] = sText_Map,
    [POKEGEAR_APP_DEXNAV] = sText_DexNav,
    [POKEGEAR_APP_TROPHIES] = sText_Trophies,
    [POKEGEAR_APP_JUKEBOX] = sText_Jukebox,
};

static const u8 *const sRegisteredDirectionLabels[MAX_REGISTERED_ITEMS] =
{
    sText_DpadUp,
    sText_DpadRight,
    sText_DpadDown,
    sText_DpadLeft,
};

static const struct PokegearTrack sJukeboxTracks[] =
{
    {sText_PokemonMarch, MUS_HG_RADIO_MARCH},
    {sText_PokemonLullaby, MUS_HG_RADIO_LULLABY},
    {sText_PokeFlute, MUS_HG_RADIO_POKE_FLUTE},
    {sText_OaksTalk, MUS_HG_RADIO_OAK},
    {sText_HoennSound, MUS_HG_RADIO_ROUTE101},
};

static const u8 sTextColor_White[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};

static const struct BgTemplate sPokegearBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
};

static const struct WindowTemplate sPokegearWindowTemplates[] =
{
    [WIN_POKEGEAR_MAIN] =
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 2,
        .width = 30,
        .height = 16,
        .paletteNum = 15,
        .baseBlock = 1,
    },
    [WIN_POKEGEAR_HEADER] =
    {
        .bg = 0,
        .tilemapLeft = 18,
        .tilemapTop = 0,
        .width = 12,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 481,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct OamData sOamData_PokegearIcon =
{
    .shape = SPRITE_SHAPE(64x32),
    .size  = SPRITE_SIZE(64x32),
    .priority = 0,
};

static const struct CompressedSpriteSheet sSpriteSheets_PokegearIcons[] =
{
    { sPokegearIconMapGfx,     (64 * 32) / 2, TAG_POKEGEAR_ICON_MAP    },
    { sPokegearIconDexNavGfx,  (64 * 32) / 2, TAG_POKEGEAR_ICON_DEXNAV },
    { sPokegearIconTrophyGfx,  (64 * 32) / 2, TAG_POKEGEAR_ICON_TROPHY },
    { sPokegearIconJukeboxGfx, (64 * 32) / 2, TAG_POKEGEAR_ICON_JUKEBOX},
};

static const struct SpritePalette sSpritePal_PokegearIcons =
{
    .data = sPokegearIconsPal,
    .tag  = TAG_POKEGEAR_ICON_MAP
};

static const union AnimCmd sSpriteAnim_Icon[] =
{
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sSpriteAnimTable_PokegearIcons[] =
{
    sSpriteAnim_Icon,
};

static const struct SpriteTemplate sSpriteTemplates_PokegearIcons[] =
{
    [POKEGEAR_APP_MAP] =
    {
        .tileTag    = TAG_POKEGEAR_ICON_MAP,
        .paletteTag = TAG_POKEGEAR_ICON_MAP,
        .oam        = &sOamData_PokegearIcon,
        .anims      = sSpriteAnimTable_PokegearIcons,
        .images     = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback   = SpriteCallbackDummy,
    },
    [POKEGEAR_APP_DEXNAV] =
    {
        .tileTag    = TAG_POKEGEAR_ICON_DEXNAV,
        .paletteTag = TAG_POKEGEAR_ICON_MAP,
        .oam        = &sOamData_PokegearIcon,
        .anims      = sSpriteAnimTable_PokegearIcons,
        .images     = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback   = SpriteCallbackDummy,
    },
    [POKEGEAR_APP_TROPHIES] =
    {
        .tileTag    = TAG_POKEGEAR_ICON_TROPHY,
        .paletteTag = TAG_POKEGEAR_ICON_MAP,
        .oam        = &sOamData_PokegearIcon,
        .anims      = sSpriteAnimTable_PokegearIcons,
        .images     = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback   = SpriteCallbackDummy,
    },
    [POKEGEAR_APP_JUKEBOX] =
    {
        .tileTag    = TAG_POKEGEAR_ICON_JUKEBOX,
        .paletteTag = TAG_POKEGEAR_ICON_MAP,
        .oam        = &sOamData_PokegearIcon,
        .anims      = sSpriteAnimTable_PokegearIcons,
        .images     = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback   = SpriteCallbackDummy,
    },
};

void CB2_InitPokegear(void)
{
    Pokegear_Init(CB2_ReturnToFieldWithOpenMenu, FALSE);
}

void CB2_ReturnToPokegear(void)
{
    Pokegear_Init(CB2_ReturnToFieldWithOpenMenu, FALSE);
}

void OpenPokegearApp(enum PokegearApp app, MainCallback callback)
{
    if (callback == NULL)
        callback = CB2_ReturnToField;

    if (!IsPokegearAppUnlocked(app))
    {
        SetMainCallback2(callback);
        return;
    }
    Menu_LoadStdPalAt(BG_PLTT_ID(15));

    switch (app)
    {
    case POKEGEAR_APP_MAP:
        FieldInitRegionMapWithOptions(callback, TRUE, TRUE);
        break;
    case POKEGEAR_APP_DEXNAV:
        DexNavGuiInit(callback);
        break;
    case POKEGEAR_APP_TROPHIES:
        CB2_InitAchievementsMenuWithCallback(callback);
        break;
    case POKEGEAR_APP_JUKEBOX:
        Pokegear_Init(callback, TRUE);
        break;
    default:
        SetMainCallback2(callback);
        break;
    }
}

static void Pokegear_Init(MainCallback callback, bool8 openJukeboxShortcut)
{
    u8 i;

    if ((sPokegear = AllocZeroed(sizeof(*sPokegear))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sPokegear->savedCallback = callback;
    sPokegear->cursorPos = sPokegearLastCursor;
    EnsureCursorSelectable();
    sPokegearLastCursor = sPokegear->cursorPos;
    sPokegear->mode = openJukeboxShortcut ? POKEGEAR_MODE_JUKEBOX : POKEGEAR_MODE_MAIN;
    sPokegear->jukeboxCursor = 0;
    sPokegear->openedFromShortcut = openJukeboxShortcut;
    sPokegear->gfxLoadState = 0;
    for (i = 0; i < POKEGEAR_APP_COUNT; i++)
        sPokegear->iconSpriteIds[i] = SPRITE_NONE;

    gMain.state = 0;
    SetMainCallback2(PokegearRunSetup);
}

static void PokegearRunSetup(void)
{
    while (1)
    {
        if (PokegearDoGfxSetup() == TRUE)
            break;
    }
}

static void PokegearMainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void PokegearVBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 PokegearDoGfxSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ResetVramOamAndBgCntRegs();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (Pokegear_InitBgs())
        {
            sPokegear->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            PokegearFadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (PokegearLoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        Pokegear_InitWindows();
        gMain.state++;
        break;
    case 5:
        CreateMainIcons();
        if (sPokegear->mode == POKEGEAR_MODE_JUKEBOX)
            DrawJukeboxScreen();
        else
            DrawMainScreen();
        CreateTask(Task_PokegearWaitFadeIn, 0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(PokegearVBlankCB);
        SetMainCallback2(PokegearMainCB);
        return TRUE;
    }

    return FALSE;
}

static bool8 Pokegear_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = AllocZeroed(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;

    sBg2TilemapBuffer = AllocZeroed(0x800);
    if (sBg2TilemapBuffer == NULL)
        return FALSE;

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sPokegearBgTemplates, ARRAY_COUNT(sPokegearBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    SetBgTilemapBuffer(2, sBg2TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(2);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    return TRUE;
}

static bool8 PokegearLoadGraphics(void)
{
    const u32 *bgTiles;
    const u16 *bgTilemap;
    const u16 *bgPal;
    const u16 *buttonPal;

    if (gSaveBlock2Ptr->playerGender == MALE)
    {
        bgTiles = sPokegearBgTiles;
        bgTilemap = sPokegearBgTilemap;
        bgPal = sPokegearBgPal;
        buttonPal = sPokegearButtonPal;
    }
    else
    {
        bgTiles = sPokegearBgFemaleTiles;
        bgTilemap = sPokegearBgFemaleTilemap;
        bgPal = sPokegearBgFemalePal;
        buttonPal = sPokegearButtonPalF;
    }

    switch (sPokegear->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, bgTiles, 0, 0, 0);
        DecompressAndCopyTileDataToVram(1, sPokegearButtonTiles, 0, 1, 0);
        sPokegear->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            CopyToBgTilemapBufferRect(2, bgTilemap, 0, 0, POKEGEAR_BG_WIDTH, POKEGEAR_BG_HEIGHT);
            FillBgTilemapBufferRect(1, 0, 0, 0, 32, 32, 0);
            sPokegear->gfxLoadState++;
        }
        break;
    case 2:
        LoadPalette(bgPal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        LoadPalette(buttonPal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        Menu_LoadStdPalAt(BG_PLTT_ID(15));
        LoadCompressedSpriteSheet(&sSpriteSheets_PokegearIcons[0]);
        LoadCompressedSpriteSheet(&sSpriteSheets_PokegearIcons[1]);
        LoadCompressedSpriteSheet(&sSpriteSheets_PokegearIcons[2]);
        LoadCompressedSpriteSheet(&sSpriteSheets_PokegearIcons[3]);
        LoadSpritePalette(&sSpritePal_PokegearIcons);
        sPokegear->gfxLoadState++;
        break;
    default:
        sPokegear->gfxLoadState = 0;
        return TRUE;
    }

    return FALSE;
}

static void Pokegear_InitWindows(void)
{
    InitWindows(sPokegearWindowTemplates);
    DeactivateAllTextPrinters();
    FillWindowPixelBuffer(WIN_POKEGEAR_MAIN, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WIN_POKEGEAR_HEADER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    PutWindowTilemap(WIN_POKEGEAR_MAIN);
    PutWindowTilemap(WIN_POKEGEAR_HEADER);
    CopyWindowToVram(WIN_POKEGEAR_MAIN, COPYWIN_FULL);
    CopyWindowToVram(WIN_POKEGEAR_HEADER, COPYWIN_FULL);
    ScheduleBgCopyTilemapToVram(0);
}

static void Task_PokegearWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        MainCallback callback = sPokegear->savedCallback;

        PokegearFreeResources();
        DestroyTask(taskId);
        SetMainCallback2(callback);
    }
}

static void PokegearFadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_PokegearWaitFadeAndBail, 0);
    SetVBlankCallback(PokegearVBlankCB);
    SetMainCallback2(PokegearMainCB);
}

static void DrawHeaderText(void)
{
    const u8 *text;
    u8 fontId;
    u8 x;

    if (sPokegear->mode == POKEGEAR_MODE_MAIN)
    {
        text = sText_MainHelp;
        fontId = FONT_SMALL;
        x = 0;
    }
    else if (sPokegear->mode == POKEGEAR_MODE_REGISTER)
    {
        text = sText_RegisterHelp;
        fontId = FONT_SMALL;
        x = 0;
    }
    else
    {
        text = sText_Back;
        fontId = FONT_NORMAL;
        x = 56;
    }

    FillWindowPixelBuffer(WIN_POKEGEAR_HEADER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(WIN_POKEGEAR_HEADER, fontId, x, 0, 0, 0, sTextColor_White, 0, text);
    PutWindowTilemap(WIN_POKEGEAR_HEADER);
    CopyWindowToVram(WIN_POKEGEAR_HEADER, COPYWIN_FULL);
}

static bool8 IsDexNavAppUnlocked(void)
{
    return FlagGet(FLAG_SYS_POKEDEX_GET) && FlagGet(FLAG_RECEIVED_FIRST_BALLS);
}

bool32 IsPokegearAppUnlocked(enum PokegearApp app)
{
    if (app >= POKEGEAR_APP_COUNT)
        return FALSE;
    if (app == POKEGEAR_APP_DEXNAV)
        return IsDexNavAppUnlocked();
    return TRUE;
}

static u8 GetButtonY(u8 app)
{
    u8 i;
    u8 row = 0;

    for (i = 0; i < app; i++)
    {
        if (IsPokegearAppUnlocked(i))
            row++;
    }
    return POKEGEAR_BUTTON_FIRST_Y + row * POKEGEAR_BUTTON_Y_SPACING;
}

static u8 GetNextSelectableApp(u8 app)
{
    do
    {
        app = (app + 1) % POKEGEAR_APP_COUNT;
    } while (!IsPokegearAppUnlocked(app));

    return app;
}

static u8 GetPreviousSelectableApp(u8 app)
{
    do
    {
        if (app == 0)
            app = POKEGEAR_APP_COUNT - 1;
        else
            app--;
    } while (!IsPokegearAppUnlocked(app));

    return app;
}

static void EnsureCursorSelectable(void)
{
    if (!IsPokegearAppUnlocked(sPokegear->cursorPos))
        sPokegear->cursorPos = GetNextSelectableApp(sPokegear->cursorPos);
}

static void DrawMainButtons(bool8 fullRedraw)
{
    u8 i;
    u8 prevPos = sPokegearLastCursor;
    u8 curPos  = sPokegear->cursorPos;

    if (fullRedraw)
        FillBgTilemapBufferRect(1, 0, 0, 0, 32, 32, 0);

    for (i = 0; i < POKEGEAR_APP_COUNT; i++)
    {
        u8 srcY;

        if (!IsPokegearAppUnlocked(i))
            continue;

        if (!fullRedraw && i != prevPos && i != curPos)
            continue;

        srcY = (i == curPos) ? POKEGEAR_BUTTON_H : 0;

        CopyRectToBgTilemapBufferRect(1,
                                      sPokegearButtonTilemap,
                                      0,
                                      srcY,
                                      POKEGEAR_BUTTON_W,
                                      POKEGEAR_BUTTON_H,
                                      POKEGEAR_BUTTON_X,
                                      GetButtonY(i),
                                      POKEGEAR_BUTTON_W,
                                      POKEGEAR_BUTTON_H,
                                      1, 1, 0);
    }
    ScheduleBgCopyTilemapToVram(1);
}

static void DrawMainText(void)
{
    u8 i;

    FillWindowPixelBuffer(WIN_POKEGEAR_MAIN, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    for (i = 0; i < POKEGEAR_APP_COUNT; i++)
    {
        s32 registeredSlot;
        u8 y;
        u8 x = 88 + GetStringCenterAlignXOffset(FONT_NORMAL, sMainLabels[i], 92);

        if (!IsPokegearAppUnlocked(i))
            continue;

        registeredSlot = RegisteredPokegearAppIndex(i);
        y = GetButtonY(i) * 8 - 7;
        AddTextPrinterParameterized4(WIN_POKEGEAR_MAIN, FONT_NORMAL, x, y, 0, 0, sTextColor_White, 0, sMainLabels[i]);
        if (registeredSlot >= 0)
            AddTextPrinterParameterized4(WIN_POKEGEAR_MAIN, FONT_NORMAL, 170, y, 0, 0, sTextColor_White, 0, sRegisteredDirectionLabels[registeredSlot]);
    }
    PutWindowTilemap(WIN_POKEGEAR_MAIN);
    CopyWindowToVram(WIN_POKEGEAR_MAIN, COPYWIN_FULL);
}

static void DrawMainScreen(void)
{
    sPokegear->mode = POKEGEAR_MODE_MAIN;
    DrawMainButtons(TRUE);
    DrawHeaderText();
    DrawMainText();
    SetMainIconsVisible(TRUE);
    ScheduleBgCopyTilemapToVram(0);
}

static void DrawJukeboxScreen(void)
{
    u8 i;

    sPokegear->mode = POKEGEAR_MODE_JUKEBOX;
    SetMainIconsVisible(FALSE);
    FillBgTilemapBufferRect(1, 0, 0, 0, 32, 32, 0);
    ScheduleBgCopyTilemapToVram(1);

    DrawHeaderText();
    FillWindowPixelBuffer(WIN_POKEGEAR_MAIN, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(WIN_POKEGEAR_MAIN,
                                 FONT_NORMAL,
                                 88 + GetStringCenterAlignXOffset(FONT_NORMAL, sText_JukeboxTitle, 72),
                                 4,
                                 0,
                                 0,
                                 sTextColor_White,
                                 0,
                                 sText_JukeboxTitle);

    for (i = 0; i < ARRAY_COUNT(sJukeboxTracks); i++)
    {
        u8 y = 26 + i * 16;

        if (i == sPokegear->jukeboxCursor)
            AddTextPrinterParameterized4(WIN_POKEGEAR_MAIN, FONT_NORMAL, 50, y, 0, 0, sTextColor_White, 0, sText_PlayMarker);
        AddTextPrinterParameterized4(WIN_POKEGEAR_MAIN, FONT_NORMAL, 68, y, 0, 0, sTextColor_White, 0, sJukeboxTracks[i].name);
    }

    PutWindowTilemap(WIN_POKEGEAR_MAIN);
    CopyWindowToVram(WIN_POKEGEAR_MAIN, COPYWIN_FULL);
    ScheduleBgCopyTilemapToVram(0);
}

static void CreateMainIcons(void)
{
    u8 i;
    for (i = 0; i < POKEGEAR_APP_COUNT; i++)
    {
        u8 spriteId;

        if (!IsPokegearAppUnlocked(i))
            continue;

        spriteId = CreateSprite(&sSpriteTemplates_PokegearIcons[i], 76, GetButtonY(i) * 8 + 16, 0);
        sPokegear->iconSpriteIds[i] = spriteId;
    }
}

static void PokegearFreeResources(void)
{
    u8 i;
    if (sPokegear != NULL)
    {
        for (i = 0; i < POKEGEAR_APP_COUNT; i++)
        {
            if (sPokegear->iconSpriteIds[i] != SPRITE_NONE)
            {
                DestroySprite(&gSprites[sPokegear->iconSpriteIds[i]]);
                sPokegear->iconSpriteIds[i] = SPRITE_NONE;
            }
        }
    }
    FreeSpriteTilesByTag(TAG_POKEGEAR_ICON_MAP);
    FreeSpriteTilesByTag(TAG_POKEGEAR_ICON_DEXNAV);
    FreeSpriteTilesByTag(TAG_POKEGEAR_ICON_TROPHY);
    FreeSpriteTilesByTag(TAG_POKEGEAR_ICON_JUKEBOX);
    FreeSpritePaletteByTag(TAG_POKEGEAR_ICON_MAP);
    FreeAllWindowBuffers();
    TRY_FREE_AND_SET_NULL(sPokegear);
    TRY_FREE_AND_SET_NULL(sBg1TilemapBuffer);
    TRY_FREE_AND_SET_NULL(sBg2TilemapBuffer);
}

static void SetMainIconsVisible(bool8 visible)
{
    u8 i;

    if (sPokegear == NULL)
        return;

    for (i = 0; i < POKEGEAR_APP_COUNT; i++)
    {
        if (sPokegear->iconSpriteIds[i] != SPRITE_NONE)
            gSprites[sPokegear->iconSpriteIds[i]].invisible = !visible || !IsPokegearAppUnlocked(i);
    }
}

static void Task_PokegearWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_PokegearMain;
}

static void Task_PokegearMainMenu(u8 taskId)
{
    if (JOY_NEW(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        sPokegear->cursorPos = GetPreviousSelectableApp(sPokegear->cursorPos);
        DrawMainButtons(FALSE);
        DrawMainText();
        sPokegearLastCursor = sPokegear->cursorPos;
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        sPokegear->cursorPos = GetNextSelectableApp(sPokegear->cursorPos);
        DrawMainButtons(FALSE);
        DrawMainText();
        sPokegearLastCursor = sPokegear->cursorPos;
    }
    else if (JOY_NEW(SELECT_BUTTON))
    {
        if (RegisteredPokegearAppIndex(sPokegear->cursorPos) >= 0)
        {
            PlaySE(SE_PC_OFF);
            UnregisterPokegearApp(sPokegear->cursorPos);
            DrawMainText();
        }
        else
        {
            PlaySE(SE_SELECT);
            sPokegear->mode = POKEGEAR_MODE_REGISTER;
            DrawHeaderText();
        }
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        sPokegearLastCursor = sPokegear->cursorPos;
        switch (sPokegear->cursorPos)
        {
        case POKEGEAR_APP_MAP:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_PokegearOpenMap;
            break;
        case POKEGEAR_APP_DEXNAV:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_PokegearOpenDexNav;
            break;
        case POKEGEAR_APP_TROPHIES:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_PokegearOpenTrophies;
            break;
        case POKEGEAR_APP_JUKEBOX:
            DrawJukeboxScreen();
            break;
        }
    }
    else if (JOY_NEW(B_BUTTON | START_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_PokegearTurnOff;
    }
}

static void Task_PokegearRegisterApp(u8 taskId)
{
    u8 slot;

    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        sPokegear->mode = POKEGEAR_MODE_MAIN;
        DrawHeaderText();
        return;
    }

    if (JOY_NEW(DPAD_UP))
        slot = 0;
    else if (JOY_NEW(DPAD_RIGHT))
        slot = 1;
    else if (JOY_NEW(DPAD_DOWN))
        slot = 2;
    else if (JOY_NEW(DPAD_LEFT))
        slot = 3;
    else
        return;

    PlaySE(SE_SELECT);
    RegisterPokegearApp(sPokegear->cursorPos, slot);
    sPokegear->mode = POKEGEAR_MODE_MAIN;
    DrawHeaderText();
    DrawMainText();
}

static void Task_PokegearJukebox(u8 taskId)
{
    if (JOY_NEW(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        if (sPokegear->jukeboxCursor == 0)
            sPokegear->jukeboxCursor = ARRAY_COUNT(sJukeboxTracks) - 1;
        else
            sPokegear->jukeboxCursor--;
        DrawJukeboxScreen();
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        sPokegear->jukeboxCursor = (sPokegear->jukeboxCursor + 1) % ARRAY_COUNT(sJukeboxTracks);
        DrawJukeboxScreen();
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        PlayBGM(sJukeboxTracks[sPokegear->jukeboxCursor].songId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sPokegear->openedFromShortcut)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_PokegearTurnOff;
        }
        else
        {
            DrawMainScreen();
        }
    }
}

static void Task_PokegearMain(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    if (sPokegear->mode == POKEGEAR_MODE_JUKEBOX)
        Task_PokegearJukebox(taskId);
    else if (sPokegear->mode == POKEGEAR_MODE_REGISTER)
        Task_PokegearRegisterApp(taskId);
    else
        Task_PokegearMainMenu(taskId);
}

static void Task_PokegearTurnOff(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        MainCallback callback = sPokegear->savedCallback;

        PokegearFreeResources();
        DestroyTask(taskId);
        SetMainCallback2(callback);
    }
}

static void Task_PokegearOpenMap(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        PokegearFreeResources();
        DestroyTask(taskId);
        OpenPokegearApp(POKEGEAR_APP_MAP, CB2_ReturnToPokegear);
    }
}

static void Task_PokegearOpenDexNav(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        PokegearFreeResources();
        DestroyTask(taskId);
        OpenPokegearApp(POKEGEAR_APP_DEXNAV, CB2_ReturnToPokegear);
    }
}

static void Task_PokegearOpenTrophies(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        PokegearFreeResources();
        DestroyTask(taskId);
        OpenPokegearApp(POKEGEAR_APP_TROPHIES, CB2_ReturnToPokegear);
    }
}
