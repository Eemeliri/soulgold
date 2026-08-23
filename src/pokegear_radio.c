#include "global.h"
#include "bg.h"
#include "buenas_password.h"
#include "decompress.h"
#include "event_data.h"
#include "fieldmap.h"
#include "gpu_regs.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "pokegear_radio.h"
#include "random.h"
#include "rtc.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/characters.h"
#include "constants/flags.h"
#include "constants/region_map_sections.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/vars.h"

#define TAG_RADIO_DIAL 0x6790
#define PAL_TAG_RADIO_DIAL 0x6790

#define RADIO_TUNING_MIN 0
#define RADIO_TUNING_MAX 63
#define RADIO_DEFAULT_TUNING_POS 13
#define RADIO_DIAL_BASE_X 144
#define RADIO_DIAL_Y 28
#define RADIO_TUNE_DELAY 3
#define RADIO_LINE_HEIGHT 16
#define RADIO_SCROLL_DELAY 90
#define RADIO_MAX_LINES 12
#define RADIO_LINE_BUFFER_SIZE 40

#define RADIO_FRAME_BASE_TILE 150
#define RADIO_FRAME_PALETTE 4
#define RADIO_TEXT_PALETTE 5

enum RadioStation
{
    RADIO_STATION_NONE,
    RADIO_STATION_POKEMON_TALK,
    RADIO_STATION_POKEMON_MUSIC,
    RADIO_STATION_BUENAS_PASSWORD,
    RADIO_STATION_UNOWN,
    RADIO_STATION_ROCKET,
};

struct RadioChannel
{
    u8 tuningPos;
    u8 station;
    const u8 *name;
};

struct PokegearRadioResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 tuningPos;
    u8 tuneDelay;
    u8 currentStation;
    u8 dialSpriteId;
    u8 stationNameWindowId;
    u8 radioTextWindowId;
    u8 currentLine;
    u8 numLines;
    bool8 needsScroll;
    u16 scrollTimer;
    u16 currentMusic;
    const u8 *lines[RADIO_MAX_LINES];
    u8 lineBuffer[RADIO_LINE_BUFFER_SIZE];
    u8 topicLineBuffers[RADIO_MAX_LINES][RADIO_LINE_BUFFER_SIZE];
    u16 bg1TilemapBuffer[BG_SCREEN_SIZE / 2];
    u16 bg2TilemapBuffer[BG_SCREEN_SIZE / 2];
};

static EWRAM_DATA struct PokegearRadioResources *sRadio = NULL;
static EWRAM_DATA u8 sLastTuningPos = 0;
static EWRAM_DATA bool8 sHasLastTuningPos = FALSE;

static void CB2_PokegearRadioSetup(void);
static bool8 PokegearRadioDoGfxSetup(void);
static void CB2_PokegearRadioMain(void);
static void VBlankCB_PokegearRadio(void);
static void Task_PokegearRadioInput(u8 taskId);
static void Task_ExitPokegearRadio(u8 taskId);
static void FreePokegearRadioResources(void);
static u8 FindStation(u8 tuningPos);
static void UpdateTuning(void);
static void GenerateStationContent(u8 station);
static void AddRadioTopic(const u8 *text);
static void PrintStationName(u8 station);
static void PrintFirstRadioLine(void);
static void ScrollRadioText(void);

static const u16 sRadioUIPal[] = INCBIN_U16("graphics/pokegear/radio/ui.gbapal");
static const u32 sRadioUIGfx[] = INCBIN_U32("graphics/pokegear/radio/ui_tiles.4bpp.smol");
static const u32 sRadioUITilemap[] = INCBIN_U32("graphics/pokegear/radio/ui_map.bin.smolTM");
static const u32 sRadioDialGfx[] = INCBIN_U32("graphics/pokegear/radio/dial.4bpp.smol");

static const u8 sText_NoStation[] = _("- - - -");
static const u8 sText_OaksPokemonTalk[] = _("Oak's Pokémon Talk");
static const u8 sText_PokemonMusic[] = _("Pokémon Music");
static const u8 sText_BuenasPassword[] = _("Buena's Password");
static const u8 sText_UnownStation[] = _("?????");
static const u8 sText_TeamRocket[] = _("Team Rocket");

static const u8 sText_Music1[] = _("Ben: Pokémon Music Channel!");
static const u8 sText_Music2[] = _("It's me, DJ Ben!");
static const u8 sText_Music3March[] = _("Today's tune is Pokémon March!");
static const u8 sText_Music3Lullaby[] = _("Today's tune is Pokémon Lullaby!");

static const u8 sText_Buena1[] = _("Buena: Buena here!");
static const u8 sText_Buena2[] = _("Time for today's password!");
static const u8 sText_Buena3[] = _("Today's password is…");
static const u8 sText_BuenaPassword[] = _("{STR_VAR_1}!");
static const u8 sText_Buena4[] = _("Don't forget it! I'm in");
static const u8 sText_Buena5[] = _("Goldenrod's Radio Tower!");
static const u8 sText_BuenaOffAir1[] = _("Buena's Password is off air.");
static const u8 sText_BuenaOffAir2[] = _("Tune in from 6 PM to midnight!");

static const u8 sText_Unown1[] = _("????????????????????????????");
static const u8 sText_Unown2[] = _("????????????????????????????");

static const u8 sText_Rocket1[] = _("… …Ahem, we are");
static const u8 sText_Rocket2[] = _("Team Rocket!");
static const u8 sText_Rocket3[] = _("After three years of preparation,");
static const u8 sText_Rocket4[] = _("we have risen from the ashes!");
static const u8 sText_Rocket5[] = _("Giovanni! Can you hear us?");

static const u8 *const sOakTalkTopics[] =
{
    gText_OakTalk_Lapras,
    gText_OakTalk_Ampharos,
    gText_OakTalk_Sudowoodo,
    gText_OakTalk_RedGyarados,
    gText_OakTalk_Unown,
    gText_OakTalk_Slowpoke,
    gText_OakTalk_LavenderTower,
    gText_OakTalk_TentacruelWhirl,
};

// Crystal frequencies (0-80) scaled to the 64 positions used by this dial.
static const struct RadioChannel sRadioChannels[] =
{
    { 13, RADIO_STATION_POKEMON_TALK,    sText_OaksPokemonTalk },
    { 22, RADIO_STATION_POKEMON_MUSIC,   sText_PokemonMusic },
    { 32, RADIO_STATION_BUENAS_PASSWORD, sText_BuenasPassword },
    { 41, RADIO_STATION_UNOWN,           sText_UnownStation },
};

static const struct BgTemplate sRadioBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sRadioWindowTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 6,
        .tilemapTop = 8,
        .width = 19,
        .height = 4,
        .paletteNum = 2,
        .baseBlock = 200,
    },
    {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 13,
        .width = 28,
        .height = 4,
        .paletteNum = RADIO_TEXT_PALETTE,
        .baseBlock = 1,
    },
    DUMMY_WIN_TEMPLATE,
};

static const u8 sStationNameTextColors[] = {TEXT_COLOR_TRANSPARENT, 7, 5};
static const u8 sRadioTextColors[] = {TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};

static const struct CompressedSpriteSheet sRadioDialSpriteSheet =
{
    .data = sRadioDialGfx,
    .size = 16 * 16 / 2,
    .tag = TAG_RADIO_DIAL,
};

static const struct SpritePalette sRadioDialSpritePalette =
{
    .data = sRadioUIPal,
    .tag = PAL_TAG_RADIO_DIAL,
};

static const struct OamData sRadioDialOam =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1,
};

static const struct SpriteTemplate sRadioDialSpriteTemplate =
{
    .tileTag = TAG_RADIO_DIAL,
    .paletteTag = PAL_TAG_RADIO_DIAL,
    .oam = &sRadioDialOam,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

void OpenPokegearRadio(MainCallback callback)
{
    if (callback == NULL)
        callback = CB2_ReturnToField;

    sRadio = AllocZeroed(sizeof(*sRadio));
    if (sRadio == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sRadio->savedCallback = callback;
    if (!sHasLastTuningPos)
    {
        sLastTuningPos = RADIO_DEFAULT_TUNING_POS;
        sHasLastTuningPos = TRUE;
    }
    sRadio->tuningPos = sLastTuningPos;
    sRadio->dialSpriteId = MAX_SPRITES;
    sRadio->currentMusic = GetCurrentMapMusic();
    gMain.state = 0;
    SetMainCallback2(CB2_PokegearRadioSetup);
}

static void CB2_PokegearRadioSetup(void)
{
    while (TRUE)
    {
        if (PokegearRadioDoGfxSetup())
            break;
    }
}

static bool8 PokegearRadioDoGfxSetup(void)
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
        ResetAllBgsCoordinates();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sRadioBgTemplates, ARRAY_COUNT(sRadioBgTemplates));
        SetBgTilemapBuffer(1, sRadio->bg1TilemapBuffer);
        SetBgTilemapBuffer(2, sRadio->bg2TilemapBuffer);
        FillBgTilemapBufferRect(1, 0, 0, 0, 32, 32, 0);
        ChangeBgX(2, 0x800, BG_COORD_SET);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        gMain.state++;
        break;
    case 3:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sRadioUIGfx, 0, 0, 0);
        CopyToBgTilemapBuffer(2, sRadioUITilemap, 0, 0);
        LoadPalette(sRadioUIPal, BG_PLTT_ID(2), sizeof(sRadioUIPal));
        gMain.state++;
        break;
    case 4:
        if (FreeTempTileDataBuffersIfPossible())
            break;
        LoadCompressedSpriteSheet(&sRadioDialSpriteSheet);
        LoadSpritePalette(&sRadioDialSpritePalette);
        InitWindows(sRadioWindowTemplates);
        DeactivateAllTextPrinters();
        sRadio->stationNameWindowId = 0;
        sRadio->radioTextWindowId = 1;
        LoadPalette(gStandardMenuPalette, BG_PLTT_ID(RADIO_TEXT_PALETTE), PLTT_SIZE_4BPP);
        LoadUserWindowBorderGfx(sRadio->radioTextWindowId, RADIO_FRAME_BASE_TILE, BG_PLTT_ID(RADIO_FRAME_PALETTE));
        DrawStdFrameWithCustomTileAndPalette(sRadio->radioTextWindowId, FALSE, RADIO_FRAME_BASE_TILE, RADIO_FRAME_PALETTE);
        PutWindowTilemap(sRadio->stationNameWindowId);
        PutWindowTilemap(sRadio->radioTextWindowId);
        sRadio->dialSpriteId = CreateSprite(&sRadioDialSpriteTemplate,
                                             RADIO_DIAL_BASE_X + sRadio->tuningPos,
                                             RADIO_DIAL_Y,
                                             1);
        UpdateTuning();
        ScheduleBgCopyTilemapToVram(1);
        ScheduleBgCopyTilemapToVram(2);
        ShowBg(1);
        ShowBg(2);
        CreateTask(Task_PokegearRadioInput, 0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_PokegearRadio);
        SetMainCallback2(CB2_PokegearRadioMain);
        return TRUE;
    }

    return FALSE;
}

static void CB2_PokegearRadioMain(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_PokegearRadio(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 IsRocketTakeoverActive(void)
{
    u16 state = VarGet(VAR_GOLDENROD_CITY_STATE);

    return state >= 6 && state < 10;
}

static u8 FindStation(u8 tuningPos)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sRadioChannels); i++)
    {
        u8 station;

        if (sRadioChannels[i].tuningPos != tuningPos)
            continue;

        station = sRadioChannels[i].station;
        if (station == RADIO_STATION_UNOWN)
        {
            if (gMapHeader.regionMapSectionId != MAPSEC_RUINS_OF_ALPH)
                return RADIO_STATION_NONE;
            return station;
        }

        if (IsRocketTakeoverActive())
            return RADIO_STATION_ROCKET;
        return station;
    }

    return RADIO_STATION_NONE;
}

static const u8 *GetStationName(u8 station)
{
    u32 i;

    if (station == RADIO_STATION_NONE)
        return sText_NoStation;
    if (station == RADIO_STATION_ROCKET)
        return sText_TeamRocket;

    for (i = 0; i < ARRAY_COUNT(sRadioChannels); i++)
    {
        if (sRadioChannels[i].station == station)
            return sRadioChannels[i].name;
    }

    return sText_NoStation;
}

static u16 GetStationMusic(u8 station)
{
    switch (station)
    {
    case RADIO_STATION_POKEMON_TALK:
        return MUS_HG_RADIO_OAK;
    case RADIO_STATION_POKEMON_MUSIC:
        return GetDayOfWeek() % 2 == 0 ? MUS_HG_RADIO_MARCH : MUS_HG_RADIO_LULLABY;
    case RADIO_STATION_BUENAS_PASSWORD:
        return BuenasPassword_IsBroadcastTime() ? MUS_HG_RADIO_BUENA : 0;
    case RADIO_STATION_UNOWN:
        return MUS_HG_RADIO_UNOWN;
    case RADIO_STATION_ROCKET:
        return MUS_HG_RADIO_ROCKET;
    default:
        return 0;
    }
}

static void PrintStationName(u8 station)
{
    const u8 *name = GetStationName(station);
    u32 width = GetStringWidth(FONT_NORMAL, name, -1);
    u32 windowWidth = 19 * 8;

    FillWindowPixelBuffer(sRadio->stationNameWindowId, PIXEL_FILL(0));
    AddTextPrinterParameterized3(sRadio->stationNameWindowId,
                                 FONT_NORMAL,
                                 (windowWidth - width) / 2,
                                 1,
                                 sStationNameTextColors,
                                 TEXT_SKIP_DRAW,
                                 name);
    CopyWindowToVram(sRadio->stationNameWindowId, COPYWIN_FULL);
}

static void AddRadioLine(const u8 *text)
{
    if (sRadio->numLines < RADIO_MAX_LINES)
        sRadio->lines[sRadio->numLines++] = text;
}

static void AddRadioTopic(const u8 *text)
{
    while (*text != EOS && sRadio->numLines < RADIO_MAX_LINES)
    {
        u32 length = 0;
        u8 *line = sRadio->topicLineBuffers[sRadio->numLines];

        while (*text != EOS
            && *text != CHAR_NEWLINE
            && *text != CHAR_PROMPT_SCROLL
            && *text != CHAR_PROMPT_CLEAR
            && *text != EXT_CTRL_CODE_BEGIN)
        {
            if (length < RADIO_LINE_BUFFER_SIZE - 1)
                line[length++] = *text;
            text++;
        }

        line[length] = EOS;
        if (length != 0)
            AddRadioLine(line);

        if (*text == CHAR_NEWLINE || *text == CHAR_PROMPT_SCROLL || *text == CHAR_PROMPT_CLEAR)
            text++;
        else if (*text == EXT_CTRL_CODE_BEGIN)
            break;
    }
}

static void GenerateStationContent(u8 station)
{
    sRadio->numLines = 0;

    switch (station)
    {
    case RADIO_STATION_POKEMON_TALK:
        AddRadioTopic(sOakTalkTopics[Random() % ARRAY_COUNT(sOakTalkTopics)]);
        break;
    case RADIO_STATION_POKEMON_MUSIC:
        AddRadioLine(sText_Music1);
        AddRadioLine(sText_Music2);
        AddRadioLine(GetDayOfWeek() % 2 == 0 ? sText_Music3March : sText_Music3Lullaby);
        break;
    case RADIO_STATION_BUENAS_PASSWORD:
        if (BuenasPassword_IsBroadcastTime())
        {
            BuenasPassword_BufferCurrentPassword();
            StringExpandPlaceholders(sRadio->lineBuffer, sText_BuenaPassword);
            AddRadioLine(sText_Buena1);
            AddRadioLine(sText_Buena2);
            AddRadioLine(sText_Buena3);
            AddRadioLine(sRadio->lineBuffer);
            AddRadioLine(sText_Buena4);
            AddRadioLine(sText_Buena5);
        }
        else
        {
            AddRadioLine(sText_BuenaOffAir1);
            AddRadioLine(sText_BuenaOffAir2);
        }
        break;
    case RADIO_STATION_UNOWN:
        AddRadioLine(sText_Unown1);
        AddRadioLine(sText_Unown2);
        break;
    case RADIO_STATION_ROCKET:
        AddRadioLine(sText_Rocket1);
        AddRadioLine(sText_Rocket2);
        AddRadioLine(sText_Rocket3);
        AddRadioLine(sText_Rocket4);
        AddRadioLine(sText_Rocket5);
        break;
    }

    sRadio->currentLine = 0;
    sRadio->scrollTimer = RADIO_SCROLL_DELAY;
    sRadio->needsScroll = FALSE;
}

static void PrintFirstRadioLine(void)
{
    FillWindowPixelBuffer(sRadio->radioTextWindowId, PIXEL_FILL(1));
    if (sRadio->numLines != 0)
    {
        AddTextPrinterParameterized3(sRadio->radioTextWindowId,
                                     FONT_NORMAL,
                                     2,
                                     RADIO_LINE_HEIGHT + 1,
                                     sRadioTextColors,
                                     TEXT_SKIP_DRAW,
                                     sRadio->lines[0]);
        sRadio->needsScroll = TRUE;
    }
    CopyWindowToVram(sRadio->radioTextWindowId, COPYWIN_GFX);
}

static void ScrollRadioText(void)
{
    if (sRadio->numLines == 0)
        return;

    if (sRadio->needsScroll)
        ScrollWindow(sRadio->radioTextWindowId, 0, RADIO_LINE_HEIGHT, PIXEL_FILL(1));
    else
        FillWindowPixelBuffer(sRadio->radioTextWindowId, PIXEL_FILL(1));

    AddTextPrinterParameterized3(sRadio->radioTextWindowId,
                                 FONT_NORMAL,
                                 2,
                                 RADIO_LINE_HEIGHT + 1,
                                 sRadioTextColors,
                                 TEXT_SKIP_DRAW,
                                 sRadio->lines[sRadio->currentLine]);
    CopyWindowToVram(sRadio->radioTextWindowId, COPYWIN_GFX);
    sRadio->needsScroll = TRUE;
}

static void UpdateTuning(void)
{
    u16 music;

    if (sRadio->dialSpriteId != MAX_SPRITES)
        gSprites[sRadio->dialSpriteId].x = RADIO_DIAL_BASE_X + sRadio->tuningPos;

    sRadio->currentStation = FindStation(sRadio->tuningPos);
    PrintStationName(sRadio->currentStation);
    GenerateStationContent(sRadio->currentStation);
    PrintFirstRadioLine();

    music = GetStationMusic(sRadio->currentStation);
    if (music == sRadio->currentMusic)
        return;

    if (music == 0)
        StopMapMusic();
    else
        PlayNewMapMusic(music);
    sRadio->currentMusic = music;
}

static void Task_PokegearRadioInput(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        sLastTuningPos = sRadio->tuningPos;
        if (sRadio->currentMusic == 0)
            PlayNewMapMusic(GetCurrLocationDefaultMusic());
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_ExitPokegearRadio;
        return;
    }

    if (JOY_HELD(DPAD_LEFT) || JOY_HELD(DPAD_RIGHT))
    {
        if (++sRadio->tuneDelay >= RADIO_TUNE_DELAY)
        {
            sRadio->tuneDelay = 0;
            if (JOY_HELD(DPAD_LEFT) && sRadio->tuningPos > RADIO_TUNING_MIN)
            {
                sRadio->tuningPos--;
                UpdateTuning();
                return;
            }
            if (JOY_HELD(DPAD_RIGHT) && sRadio->tuningPos < RADIO_TUNING_MAX)
            {
                sRadio->tuningPos++;
                UpdateTuning();
                return;
            }
        }
    }
    else
    {
        sRadio->tuneDelay = RADIO_TUNE_DELAY - 1;
    }

    if (sRadio->numLines > 1)
    {
        if (sRadio->scrollTimer != 0)
            sRadio->scrollTimer--;
        else
        {
            sRadio->scrollTimer = RADIO_SCROLL_DELAY;
            sRadio->currentLine = (sRadio->currentLine + 1) % sRadio->numLines;
            ScrollRadioText();
        }
    }
}

static void Task_ExitPokegearRadio(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        MainCallback callback = sRadio->savedCallback;

        FreePokegearRadioResources();
        DestroyTask(taskId);
        SetMainCallback2(callback);
    }
}

static void FreePokegearRadioResources(void)
{
    if (sRadio == NULL)
        return;

    if (sRadio->dialSpriteId != MAX_SPRITES)
        DestroySprite(&gSprites[sRadio->dialSpriteId]);
    FreeSpriteTilesByTag(TAG_RADIO_DIAL);
    FreeSpritePaletteByTag(PAL_TAG_RADIO_DIAL);
    FreeAllWindowBuffers();
    TRY_FREE_AND_SET_NULL(sRadio);
}
