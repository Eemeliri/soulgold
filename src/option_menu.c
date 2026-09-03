#include "global.h"
#include "option_menu.h"
#include "bg.h"
#include "difficulty.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "level_scaling.h"
#include "list_menu.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "replay_options.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "gba/m4a_internal.h"
#include "constants/party_menu.h"
#include "constants/rgb.h"
#include "constants/vars.h"
#include "event_data.h"

#define tMenuSelection data[0]
#define tTextSpeed data[1]
#define tBattleSceneOff data[2]
#define tBattleStyle data[3]
#define tSound data[4]
#define tButtonMode data[5]
#define tWindowFrameType data[6]
#define tLevelCaps data[7]

#define tFollowers data[8]
#define tAutorun data[9]
#define tTrainerLevelScaling data[10]
#define tWildLevelScaling data[11]
#define tDifficulty data[12]
#define tOverworldSpeedup data[13]
#define tBattleSpeed data[14]
#define tFastIntroNoSlide data[15]

#define TEXT_SPEED_STYLES_COUNT (OPTIONS_TEXT_SPEED_FASTER + 1)

enum
{
    MENUITEM_TEXTSPEED,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_LEVELCAPS,
    MENUITEM_COUNT,
};

// Menu items Pg2
enum
{
    MENUITEM_FOLLOWERS,
    MENUITEM_AUTORUN,
    MENUITEM_OVERWORLD_SPEEDUP,
    MENUITEM_BATTLE_SPEED,
    MENUITEM_TRAINER_LEVEL_SCALING,
    MENUITEM_WILD_LEVEL_SCALING,
    MENUITEM_DIFFICULTY,
    MENUITEM_COUNT_PG2,
};

// Menu items Pg3
enum
{
    MENUITEM_INTRO_SLIDE,
    MENUITEM_UI_ANIMATIONS,
    MENUITEM_DARK_BATTLE_UI,
    MENUITEM_FAST_MEGAS,
    MENUITEM_FAST_WEATHER,
    MENUITEM_SURF_MUSIC,
    MENUITEM_PARTY_MENU,
    MENUITEM_BATTLE_FORMAT,
    MENUITEM_COUNT_PG3,
};

#define OPTION_MENU_PG1_OPTIONS MENUITEM_COUNT
#define OPTION_MENU_PG2_START   OPTION_MENU_PG1_OPTIONS
#define OPTION_MENU_PG3_START   (OPTION_MENU_PG2_START + MENUITEM_COUNT_PG2)
#define OPTION_MENU_CLOSE       (OPTION_MENU_PG3_START + MENUITEM_COUNT_PG3)
#define OPTION_MENU_ITEM_COUNT  (OPTION_MENU_CLOSE + 1)
#define OPTION_MENU_VISIBLE_ROWS 7
#define OPTION_MENU_MAX_SCROLL  (OPTION_MENU_ITEM_COUNT - OPTION_MENU_VISIBLE_ROWS)
#define TAG_OPTION_MENU_SCROLL_ARROW 2100

enum
{
    WIN_HEADER,
    WIN_OPTIONS
};

#define YPOS_TEXTSPEED             sOptionDrawY
#define YPOS_BATTLESCENE           sOptionDrawY
#define YPOS_BATTLESTYLE           sOptionDrawY
#define YPOS_SOUND                 sOptionDrawY
#define YPOS_BUTTONMODE            sOptionDrawY
#define YPOS_FRAMETYPE             sOptionDrawY
#define YPOS_LEVELCAPS             sOptionDrawY
#define YPOS_FOLLOWERS             sOptionDrawY
#define YPOS_AUTORUN               sOptionDrawY
#define YPOS_OVERWORLD_SPEEDUP     sOptionDrawY
#define YPOS_BATTLE_SPEED          sOptionDrawY
#define YPOS_TRAINER_LEVEL_SCALING sOptionDrawY
#define YPOS_WILD_LEVEL_SCALING    sOptionDrawY
#define YPOS_DIFFICULTY            sOptionDrawY
#define YPOS_INTRO_SLIDE           sOptionDrawY
#define YPOS_UI_ANIMATIONS         sOptionDrawY
#define YPOS_DARK_BATTLE_UI        sOptionDrawY
#define YPOS_FAST_MEGAS            sOptionDrawY
#define YPOS_FAST_WEATHER          sOptionDrawY
#define YPOS_SURF_MUSIC            sOptionDrawY
#define YPOS_PARTY_MENU            sOptionDrawY
#define YPOS_BATTLE_FORMAT         sOptionDrawY

static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuProcessHelpInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void SaveCurrentSettings(u8 taskId);
static void ShowOptionMenuHelp(u8 taskId);
static void RedrawCurrentOptions(u8 taskId);
static void HighlightOptionMenuItem(u8 selection);
static void DrawVisibleOptions(u8 taskId);
static void DrawOptionChoices(u8 taskId, u8 option);
static void ProcessOptionInput(u8 taskId);
static const u8 *GetOptionName(u8 option);
static const u8 *GetOptionHelpText(u8 option);
static void AddOptionMenuScrollArrows(void);
static void RemoveOptionMenuScrollArrows(void);
static u8 TextSpeed_ProcessInput(u8 selection);
static void TextSpeed_DrawChoices(u8 selection);
static u8 TextSpeed_NormalizeSelection(u8 selection);
static u8 TextSpeed_GetNextSelection(u8 selection);
static u8 TextSpeed_GetPreviousSelection(u8 selection);
static u8 BattleScene_ProcessInput(u8 selection);
static void BattleScene_DrawChoices(u8 selection);
static u8 BattleStyle_ProcessInput(u8 selection);
static void BattleStyle_DrawChoices(u8 selection);
static u8 Sound_ProcessInput(u8 selection);
static void Sound_DrawChoices(u8 selection);
static u8 FrameType_ProcessInput(u8 selection);
static void FrameType_DrawChoices(u8 selection);
static u8 ButtonMode_ProcessInput(u8 selection);
static void ButtonMode_DrawChoices(u8 selection);

static u8 Followers_ProcessInput(u8 selection);
static void Followers_DrawChoices(u8 selection);
static u8 LevelCaps_ProcessInput(u8 selection);
static void LevelCaps_DrawChoices(u8 selection);
static u8 LevelScaling_ProcessInput(u8 selection);
static void TrainerLevelScaling_DrawChoices(u8 selection);
static void WildLevelScaling_DrawChoices(u8 selection);
static u8 Difficulty_ProcessInput(u8 selection);
static void Difficulty_DrawChoices(u8 selection);
static u8   Autorun_ProcessInput(u8 selection);
static void Autorun_DrawChoices(u8 selection);
static u8 OverworldSpeedup_ProcessInput(u8 selection);
static void OverworldSpeedup_DrawChoices(u8 selection);
static u8 BattleSpeed_ProcessInput(u8 selection);
static void BattleSpeed_DrawChoices(u8 selection);
static u8 IntroSlide_ProcessInput(u8 selection);
static void IntroSlide_DrawChoices(u8 selection);
static u8 UiAnimations_ProcessInput(u8 selection);
static void UiAnimations_DrawChoices(u8 selection);
static u8 DarkBattleUi_ProcessInput(u8 selection);
static void DarkBattleUi_DrawChoices(u8 selection);
static u8 FastMegas_ProcessInput(u8 selection);
static void FastMegas_DrawChoices(u8 selection);
static u8 FastWeather_ProcessInput(u8 selection);
static void FastWeather_DrawChoices(u8 selection);
static u8 SurfMusic_ProcessInput(u8 selection);
static void SurfMusic_DrawChoices(u8 selection);
static u8 PartyMenuStyle_ProcessInput(u8 selection);
static void PartyMenuStyle_DrawChoices(u8 selection);
static u8 GetSavedPartyMenuStyle(void);
static void SetSavedPartyMenuStyle(u8 selection);
static u8 BattleFormat_ProcessInput(u8 selection);
static void BattleFormat_DrawChoices(u8 selection);

static void DrawHeaderText(void);
static void DrawBgWindowFrames(void);

EWRAM_DATA static bool8 sArrowPressed = FALSE;
EWRAM_DATA static bool8 sUiAnimationsOff = FALSE;
EWRAM_DATA static bool8 sDarkBattleUi = FALSE;
EWRAM_DATA static bool8 sFastMegas = FALSE;
EWRAM_DATA static bool8 sFastWeather = FALSE;
EWRAM_DATA static bool8 sSurfMusic = FALSE;
EWRAM_DATA static u8 sPartyMenuStyle = PARTY_MENU_DEFAULT_OPTION;
EWRAM_DATA static u8 sBattleFormat = REPLAY_BATTLE_FORMAT_DESIGNED;
EWRAM_DATA static u16 sOptionScrollOffset = 0;
EWRAM_DATA static u8 sOptionScrollArrowTaskId = 0;
EWRAM_DATA static u8 sOptionDrawY = 0;

static const u8 gText_Option[]             = _("Options");
static const u8 gText_TextSpeedFast[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Normal");
static const u8 gText_TextSpeedFaster[]    = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Fast");
static const u8 gText_TextSpeedInstant[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Inst");
static const u8 gText_BattleSceneOn[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}On");
static const u8 gText_BattleSceneOff[]     = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");
static const u8 gText_BattleStyleShift[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Shift");
static const u8 gText_BattleStyleSet[]     = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Set");
static const u8 gText_SoundMono[]          = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Mono");
static const u8 gText_SoundStereo[]        = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Stereo");
static const u8 gText_FrameType[]          = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Type");
static const u8 gText_FrameTypeNumber[]    = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}");
static const u8 gText_ButtonTypeNormal[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Normal");
static const u8 gText_ButtonTypeLR[]       = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}LR");
static const u8 gText_ButtonTypeLEqualsA[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}L=A");
static const u8 gText_AutorunOn[]            = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}On");
static const u8 gText_AutorunOff[]          = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");

static const u8 gText_NoCaps[]             = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}None");
static const u8 gText_SoftCaps[]             = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Soft");
static const u8 gText_HardCaps[]             = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Hard");
static const u8 gText_ScalingOff[]         = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");
static const u8 gText_ScalingOn[]          = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}On");
static const u8 gText_DifficultyNormal[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Normal");
static const u8 gText_DifficultyHard[]     = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Hard");
static const u8 gText_OverworldSpeed1x[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}1x");
static const u8 gText_OverworldSpeed2x[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}2x");
static const u8 gText_OverworldSpeed3x[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}3x");
static const u8 gText_OverworldSpeed4x[]   = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}4x");
static const u8 gText_BattleSpeed1x[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}1x");
static const u8 gText_BattleSpeed2x[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}2x");
static const u8 gText_BattleSpeed3x[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}3x");
static const u8 gText_IntroSlideOn[]       = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}On");
static const u8 gText_IntroSlideOff[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");
static const u8 gText_BattleUiLight[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Light");
static const u8 gText_BattleUiDark[]       = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Dark");
static const u8 gText_FastMegasOn[]        = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}On");
static const u8 gText_FastMegasOff[]       = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");
static const u8 gText_FastWeatherOn[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}On");
static const u8 gText_FastWeatherOff[]     = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");
static const u8 gText_SurfMusicOn[]        = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}On");
static const u8 gText_SurfMusicOff[]       = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");
static const u8 gText_PartyMenuCustom[]    = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Custom");
static const u8 gText_PartyMenuHGSS[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}HGSS");
static const u8 gText_PartyMenuBW[]        = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}BW");
static const u8 gText_BattleFormatDefault[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Default");
static const u8 gText_BattleFormatSingles[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Singles");
static const u8 gText_BattleFormatDoubles[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Doubles");
static const u8 sText_OptionHelp[]           = _("Options guide");
static const u8 sText_CloseHelp[]            = _("{SELECT_BUTTON} Close");
static const u8 sText_OpenHelp[]             = _("{SELECT_BUTTON} Help");
static const u8 sText_Close[]                = _("Close");
static const u8 sText_CloseDescription[]     = _(
    "Saves the current settings and\n"
    "returns to the previous screen.");

static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text.gbapal");
#define OPTION_GUIDE_TEXT_COLOR_DARK_GRAY  8
#define OPTION_GUIDE_TEXT_COLOR_LIGHT_GRAY 9
static const u16 sOptionGuideText_Pal[] =
{
    RGB(6, 6, 6),
    RGB(18, 18, 18),
};
static const u8 sOptionGuideTextColors[] =
{
    TEXT_COLOR_WHITE,
    OPTION_GUIDE_TEXT_COLOR_DARK_GRAY,
    OPTION_GUIDE_TEXT_COLOR_LIGHT_GRAY,
};
// note: this is only used in the Japanese release
static const u8 sEqualSignGfx[] = INCBIN_U8("graphics/interface/option_menu_equals_sign.4bpp");

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = COMPOUND_STRING("Text speed"),
    [MENUITEM_BATTLESCENE] = COMPOUND_STRING("Battle scene"),
    [MENUITEM_BATTLESTYLE] = COMPOUND_STRING("Battle style"),
    [MENUITEM_SOUND]       = COMPOUND_STRING("Sound"),
    [MENUITEM_BUTTONMODE]  = COMPOUND_STRING("Button mode"),
    [MENUITEM_FRAMETYPE]   = COMPOUND_STRING("Frame"),
    [MENUITEM_LEVELCAPS]   = COMPOUND_STRING("Level caps"),
};

static const u8 *const sOptionMenuItemsNames_Pg2[MENUITEM_COUNT_PG2] =
{
    [MENUITEM_FOLLOWERS]        = gText_Followers,
    [MENUITEM_AUTORUN]         = COMPOUND_STRING("Autorun"),
    [MENUITEM_OVERWORLD_SPEEDUP] = COMPOUND_STRING("OW speed"),
    [MENUITEM_BATTLE_SPEED] = COMPOUND_STRING("Battle speed"),
    [MENUITEM_TRAINER_LEVEL_SCALING] = COMPOUND_STRING("Trainer scaling"),
    [MENUITEM_WILD_LEVEL_SCALING] = COMPOUND_STRING("Wild scaling"),
    [MENUITEM_DIFFICULTY] = COMPOUND_STRING("Difficulty"),
};

static const u8 *const sOptionMenuItemsNames_Pg3[MENUITEM_COUNT_PG3] =
{
    [MENUITEM_INTRO_SLIDE] = COMPOUND_STRING("Battle intro"),
    [MENUITEM_UI_ANIMATIONS] = COMPOUND_STRING("UI animations"),
    [MENUITEM_DARK_BATTLE_UI] = COMPOUND_STRING("Battle/Bag UI"),
    [MENUITEM_FAST_MEGAS] = COMPOUND_STRING("Fast megas"),
    [MENUITEM_FAST_WEATHER] = COMPOUND_STRING("Fast weather"),
    [MENUITEM_SURF_MUSIC] = COMPOUND_STRING("Surf music"),
    [MENUITEM_PARTY_MENU] = COMPOUND_STRING("Party menu"),
    [MENUITEM_BATTLE_FORMAT] = COMPOUND_STRING("Trainer format"),
};

static const u8 *const sOptionMenuHelpTexts[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED] = COMPOUND_STRING(
        "Controls how quickly dialogue\n"
        "appears. Normal uses standard\n"
        "speed, Fast is quicker, and Inst\n"
        "shows text immediately."),
    [MENUITEM_BATTLESCENE] = COMPOUND_STRING(
        "Controls move animations in\n"
        "battle. On plays them normally.\n"
        "Off skips most move animations."),
    [MENUITEM_BATTLESTYLE] = COMPOUND_STRING(
        "Shift offers a free switch when\n"
        "an opposing Pokémon faints. Set\n"
        "sends the next foe in without a\n"
        "free switch."),
    [MENUITEM_SOUND] = COMPOUND_STRING(
        "Mono mixes audio for one speaker.\n"
        "Stereo separates some sounds\n"
        "between the left and right\n"
        "speakers."),
    [MENUITEM_BUTTONMODE] = COMPOUND_STRING(
        "Normal uses standard controls.\n"
        "LR makes L/R act as left/right\n"
        "in some menus. L=A also lets L\n"
        "confirm like the A Button."),
    [MENUITEM_FRAMETYPE] = COMPOUND_STRING(
        "Changes dialogue and text-window\n"
        "borders. This is purely visual\n"
        "and does not affect gameplay."),
    [MENUITEM_LEVELCAPS] = COMPOUND_STRING(
        "None gives full EXP at all\n"
        "levels. Soft sharply reduces EXP\n"
        "at the story cap. Hard gives no\n"
        "EXP at the cap."),
};

static const u8 *const sOptionMenuHelpTexts_Pg2[MENUITEM_COUNT_PG2] =
{
    [MENUITEM_FOLLOWERS] = COMPOUND_STRING(
        "Shows your first usable Pokémon\n"
        "behind you in the overworld.\n"
        "Some maps and scenes may hide it."),
    [MENUITEM_AUTORUN] = COMPOUND_STRING(
        "On runs automatically once\n"
        "running is unlocked. Hold B to\n"
        "walk while On, or run while Off."),
    [MENUITEM_OVERWORLD_SPEEDUP] = COMPOUND_STRING(
        "Sets overworld movement and\n"
        "animation speed. Hold R for 1x.\n"
        "If R starts DexNav, use Select\n"
        "there to unbind the target."),
    [MENUITEM_BATTLE_SPEED] = COMPOUND_STRING(
        "Sets battle animation and delay\n"
        "speed. Move selection remains at\n"
        "normal speed. Hold L for 1x."),
    [MENUITEM_TRAINER_LEVEL_SCALING] = COMPOUND_STRING(
        "On scales trainer levels to trail\n"
        "your party's average level.\n"
        "Off uses each trainer's default\n"
        "levels."),
    [MENUITEM_WILD_LEVEL_SCALING] = COMPOUND_STRING(
        "On scales wild Pokémon levels to\n"
        "trail 8-10 levels behind your party.\n"
        "Never scales below the nonscaled\n"
        "wild encounter levels."),
    [MENUITEM_DIFFICULTY] = COMPOUND_STRING(
        "Normal uses standard trainer teams.\n"
        "Hard uses tougher teams for Gym\n"
        "battles, the Elite Four and\n"
        "makes them Doubles.\n"),
};

static const u8 *const sOptionMenuHelpTexts_Pg3[MENUITEM_COUNT_PG3] =
{
    [MENUITEM_INTRO_SLIDE] = COMPOUND_STRING(
        "On plays the sliding entrance.\n"
        "Off skips it to begin battles\n"
        "more quickly."),
    [MENUITEM_UI_ANIMATIONS] = COMPOUND_STRING(
        "On animates dialogue boxes and\n"
        "the pause menu. Off makes these\n"
        "interfaces appear immediately."),
    [MENUITEM_DARK_BATTLE_UI] = COMPOUND_STRING(
        "Light uses the standard UI. Dark\n"
        "uses dark healthboxes and\n"
        "and Bag screen with lighter text.\n"
        "Shiny healthboxes are unchanged."),
    [MENUITEM_FAST_MEGAS] = COMPOUND_STRING(
        "On uses a near-instant Mega\n"
        "Evolution animation. Off plays\n"
        "the complete sequence."),
    [MENUITEM_FAST_WEATHER] = COMPOUND_STRING(
        "On skips repeated weather text\n"
        "and animations after it begins.\n"
        "Off shows them each turn."),
    [MENUITEM_SURF_MUSIC] = COMPOUND_STRING(
        "On plays the Surf theme while\n"
        "surfing. Off keeps the map music."),
    [MENUITEM_PARTY_MENU] = COMPOUND_STRING(
        "Custom uses the redesigned screen.\n"
        "HGSS and BW use their respective\n"
        "DS-style layouts. This applies\n"
        "wherever the party menu is opened."),
    [MENUITEM_BATTLE_FORMAT] = COMPOUND_STRING(
        "Default uses intended formats.\n"
        "Singles/Doubles override eligible\n"
        "trainers; Doubles needs 2 Pokémon.\n"
        "Wild/facility/partner/multi\n"
        "battles keep their own format."),
};

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 14,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    }
};

static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void ReadAllCurrentSettings(u8 taskId)
{
        gTasks[taskId].tMenuSelection = 0;
        gTasks[taskId].tTextSpeed = gSaveBlock2Ptr->optionsTextSpeed;
        gTasks[taskId].tBattleSceneOff = gSaveBlock2Ptr->optionsBattleSceneOff;
        gTasks[taskId].tBattleStyle = gSaveBlock2Ptr->optionsBattleStyle;
        gTasks[taskId].tSound = gSaveBlock2Ptr->optionsSound;
        gTasks[taskId].tButtonMode = gSaveBlock2Ptr->optionsButtonMode;
        gTasks[taskId].tWindowFrameType = gSaveBlock2Ptr->optionsWindowFrameType;
        gTasks[taskId].tFollowers = gSaveBlock2Ptr->optionsFollowers;
        gTasks[taskId].tLevelCaps = gSaveBlock2Ptr->optionsLevelCaps;
        gTasks[taskId].tAutorun = gSaveBlock2Ptr->optionsAutorun;
        gTasks[taskId].tTrainerLevelScaling = gSaveBlock2Ptr->optionsTrainerLevelScaling;
        gTasks[taskId].tWildLevelScaling = gSaveBlock2Ptr->optionsWildLevelScaling;
        gTasks[taskId].tDifficulty = GetCurrentDifficultyLevel() == DIFFICULTY_HARD;
        gTasks[taskId].tOverworldSpeedup = VarGet(VAR_OVERWORLD_SPEEDUP);
        if (gTasks[taskId].tOverworldSpeedup > OPTIONS_OVERWORLD_SPEED_4X)
            gTasks[taskId].tOverworldSpeedup = OPTIONS_OVERWORLD_SPEED_1X;
        gTasks[taskId].tBattleSpeed = VarGet(VAR_BATTLE_SPEED);
        if (gTasks[taskId].tBattleSpeed > OPTIONS_BATTLE_SCENE_3X)
            gTasks[taskId].tBattleSpeed = OPTIONS_BATTLE_SCENE_1X;
        gTasks[taskId].tFastIntroNoSlide = gSaveBlock2Ptr->optionsFastIntroNoSlide;
        sUiAnimationsOff = gSaveBlock2Ptr->optionsUiAnimationsOff;
        sDarkBattleUi = gSaveBlock2Ptr->optionsDarkBattleUi;
        sFastMegas = gSaveBlock2Ptr->optionsFastMegas;
        sFastWeather = gSaveBlock2Ptr->optionsFastWeather;
        sSurfMusic = gSaveBlock2Ptr->optionsSurfMusic;
        sPartyMenuStyle = GetSavedPartyMenuStyle();
        sBattleFormat = GetReplayBattleFormat();
}

void CB2_InitOptionMenu(void)
{
    u8 taskId;
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        ChangeBgX(2, 0, BG_COORD_SET);
        ChangeBgY(2, 0, BG_COORD_SET);
        ChangeBgX(3, 0, BG_COORD_SET);
        ChangeBgY(3, 0, BG_COORD_SET);
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, BG_PLTT_ID(0), sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, BG_PLTT_ID(1), sizeof(sOptionMenuText_Pal));
        LoadPalette(sOptionGuideText_Pal, BG_PLTT_ID(1) + OPTION_GUIDE_TEXT_COLOR_DARK_GRAY, sizeof(sOptionGuideText_Pal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(WIN_HEADER);
        DrawHeaderText();
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_OPTIONS);
        FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
    case 9:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 10:
        taskId = CreateTask(Task_OptionMenuFadeIn, 0);
        ReadAllCurrentSettings(taskId);
        sOptionScrollOffset = 0;
        sOptionScrollArrowTaskId = TASK_NONE;
        DrawVisibleOptions(taskId);
        gMain.state++;
        break;
    case 11:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0 | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        AddOptionMenuScrollArrows();
        gTasks[taskId].func = Task_OptionMenuProcessInput;
    }
}

static const u8 *GetOptionName(u8 option)
{
    if (option < OPTION_MENU_PG2_START)
        return sOptionMenuItemsNames[option];
    if (option < OPTION_MENU_PG3_START)
        return sOptionMenuItemsNames_Pg2[option - OPTION_MENU_PG2_START];
    if (option < OPTION_MENU_CLOSE)
        return sOptionMenuItemsNames_Pg3[option - OPTION_MENU_PG3_START];
    return sText_Close;
}

static const u8 *GetOptionHelpText(u8 option)
{
    if (option < OPTION_MENU_PG2_START)
        return sOptionMenuHelpTexts[option];
    if (option < OPTION_MENU_PG3_START)
        return sOptionMenuHelpTexts_Pg2[option - OPTION_MENU_PG2_START];
    if (option < OPTION_MENU_CLOSE)
        return sOptionMenuHelpTexts_Pg3[option - OPTION_MENU_PG3_START];
    return sText_CloseDescription;
}

static void DrawOptionChoices(u8 taskId, u8 option)
{
    switch (option)
    {
    case MENUITEM_TEXTSPEED:
        TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
        break;
    case MENUITEM_BATTLESCENE:
        BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
        break;
    case MENUITEM_BATTLESTYLE:
        BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
        break;
    case MENUITEM_SOUND:
        Sound_DrawChoices(gTasks[taskId].tSound);
        break;
    case MENUITEM_BUTTONMODE:
        ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
        break;
    case MENUITEM_FRAMETYPE:
        FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
        break;
    case MENUITEM_LEVELCAPS:
        LevelCaps_DrawChoices(gTasks[taskId].tLevelCaps);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_FOLLOWERS:
        Followers_DrawChoices(gTasks[taskId].tFollowers);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_AUTORUN:
        Autorun_DrawChoices(gTasks[taskId].tAutorun);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_OVERWORLD_SPEEDUP:
        OverworldSpeedup_DrawChoices(gTasks[taskId].tOverworldSpeedup);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_BATTLE_SPEED:
        BattleSpeed_DrawChoices(gTasks[taskId].tBattleSpeed);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_TRAINER_LEVEL_SCALING:
        TrainerLevelScaling_DrawChoices(gTasks[taskId].tTrainerLevelScaling);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_WILD_LEVEL_SCALING:
        WildLevelScaling_DrawChoices(gTasks[taskId].tWildLevelScaling);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_DIFFICULTY:
        Difficulty_DrawChoices(gTasks[taskId].tDifficulty);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_INTRO_SLIDE:
        IntroSlide_DrawChoices(gTasks[taskId].tFastIntroNoSlide);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_UI_ANIMATIONS:
        UiAnimations_DrawChoices(sUiAnimationsOff);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_DARK_BATTLE_UI:
        DarkBattleUi_DrawChoices(sDarkBattleUi);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_FAST_MEGAS:
        FastMegas_DrawChoices(sFastMegas);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_FAST_WEATHER:
        FastWeather_DrawChoices(sFastWeather);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_SURF_MUSIC:
        SurfMusic_DrawChoices(sSurfMusic);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_PARTY_MENU:
        PartyMenuStyle_DrawChoices(sPartyMenuStyle);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_BATTLE_FORMAT:
        BattleFormat_DrawChoices(sBattleFormat);
        break;
    }
}

static void ProcessOptionInput(u8 taskId)
{
    u8 option = gTasks[taskId].tMenuSelection;
    u8 previousOption;

    sOptionDrawY = (option - sOptionScrollOffset) * 16;
    switch (option)
    {
    case MENUITEM_TEXTSPEED:
        previousOption = gTasks[taskId].tTextSpeed;
        gTasks[taskId].tTextSpeed = TextSpeed_ProcessInput(gTasks[taskId].tTextSpeed);
        if (previousOption != gTasks[taskId].tTextSpeed)
            TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
        break;
    case MENUITEM_BATTLESCENE:
        previousOption = gTasks[taskId].tBattleSceneOff;
        gTasks[taskId].tBattleSceneOff = BattleScene_ProcessInput(gTasks[taskId].tBattleSceneOff);
        if (previousOption != gTasks[taskId].tBattleSceneOff)
            BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
        break;
    case MENUITEM_BATTLESTYLE:
        previousOption = gTasks[taskId].tBattleStyle;
        gTasks[taskId].tBattleStyle = BattleStyle_ProcessInput(gTasks[taskId].tBattleStyle);
        if (previousOption != gTasks[taskId].tBattleStyle)
            BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
        break;
    case MENUITEM_SOUND:
        previousOption = gTasks[taskId].tSound;
        gTasks[taskId].tSound = Sound_ProcessInput(gTasks[taskId].tSound);
        if (previousOption != gTasks[taskId].tSound)
            Sound_DrawChoices(gTasks[taskId].tSound);
        break;
    case MENUITEM_BUTTONMODE:
        previousOption = gTasks[taskId].tButtonMode;
        gTasks[taskId].tButtonMode = ButtonMode_ProcessInput(gTasks[taskId].tButtonMode);
        if (previousOption != gTasks[taskId].tButtonMode)
            ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
        break;
    case MENUITEM_FRAMETYPE:
        previousOption = gTasks[taskId].tWindowFrameType;
        gTasks[taskId].tWindowFrameType = FrameType_ProcessInput(gTasks[taskId].tWindowFrameType);
        if (previousOption != gTasks[taskId].tWindowFrameType)
            FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
        break;
    case MENUITEM_LEVELCAPS:
        previousOption = gTasks[taskId].tLevelCaps;
        gTasks[taskId].tLevelCaps = LevelCaps_ProcessInput(gTasks[taskId].tLevelCaps);
        if (previousOption != gTasks[taskId].tLevelCaps)
            LevelCaps_DrawChoices(gTasks[taskId].tLevelCaps);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_FOLLOWERS:
        previousOption = gTasks[taskId].tFollowers;
        gTasks[taskId].tFollowers = Followers_ProcessInput(gTasks[taskId].tFollowers);
        if (previousOption != gTasks[taskId].tFollowers)
            Followers_DrawChoices(gTasks[taskId].tFollowers);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_AUTORUN:
        previousOption = gTasks[taskId].tAutorun;
        gTasks[taskId].tAutorun = Autorun_ProcessInput(gTasks[taskId].tAutorun);
        if (previousOption != gTasks[taskId].tAutorun)
            Autorun_DrawChoices(gTasks[taskId].tAutorun);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_OVERWORLD_SPEEDUP:
        previousOption = gTasks[taskId].tOverworldSpeedup;
        gTasks[taskId].tOverworldSpeedup = OverworldSpeedup_ProcessInput(gTasks[taskId].tOverworldSpeedup);
        if (previousOption != gTasks[taskId].tOverworldSpeedup)
            OverworldSpeedup_DrawChoices(gTasks[taskId].tOverworldSpeedup);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_BATTLE_SPEED:
        previousOption = gTasks[taskId].tBattleSpeed;
        gTasks[taskId].tBattleSpeed = BattleSpeed_ProcessInput(gTasks[taskId].tBattleSpeed);
        if (previousOption != gTasks[taskId].tBattleSpeed)
            BattleSpeed_DrawChoices(gTasks[taskId].tBattleSpeed);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_TRAINER_LEVEL_SCALING:
        previousOption = gTasks[taskId].tTrainerLevelScaling;
        gTasks[taskId].tTrainerLevelScaling = LevelScaling_ProcessInput(gTasks[taskId].tTrainerLevelScaling);
        if (previousOption != gTasks[taskId].tTrainerLevelScaling)
            TrainerLevelScaling_DrawChoices(gTasks[taskId].tTrainerLevelScaling);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_WILD_LEVEL_SCALING:
        previousOption = gTasks[taskId].tWildLevelScaling;
        gTasks[taskId].tWildLevelScaling = LevelScaling_ProcessInput(gTasks[taskId].tWildLevelScaling);
        if (previousOption != gTasks[taskId].tWildLevelScaling)
            WildLevelScaling_DrawChoices(gTasks[taskId].tWildLevelScaling);
        break;
    case OPTION_MENU_PG2_START + MENUITEM_DIFFICULTY:
        previousOption = gTasks[taskId].tDifficulty;
        gTasks[taskId].tDifficulty = Difficulty_ProcessInput(gTasks[taskId].tDifficulty);
        if (previousOption != gTasks[taskId].tDifficulty)
            Difficulty_DrawChoices(gTasks[taskId].tDifficulty);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_INTRO_SLIDE:
        previousOption = gTasks[taskId].tFastIntroNoSlide;
        gTasks[taskId].tFastIntroNoSlide = IntroSlide_ProcessInput(gTasks[taskId].tFastIntroNoSlide);
        if (previousOption != gTasks[taskId].tFastIntroNoSlide)
            IntroSlide_DrawChoices(gTasks[taskId].tFastIntroNoSlide);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_UI_ANIMATIONS:
        previousOption = sUiAnimationsOff;
        sUiAnimationsOff = UiAnimations_ProcessInput(sUiAnimationsOff);
        if (previousOption != sUiAnimationsOff)
            UiAnimations_DrawChoices(sUiAnimationsOff);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_DARK_BATTLE_UI:
        previousOption = sDarkBattleUi;
        sDarkBattleUi = DarkBattleUi_ProcessInput(sDarkBattleUi);
        if (previousOption != sDarkBattleUi)
            DarkBattleUi_DrawChoices(sDarkBattleUi);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_FAST_MEGAS:
        previousOption = sFastMegas;
        sFastMegas = FastMegas_ProcessInput(sFastMegas);
        if (previousOption != sFastMegas)
            FastMegas_DrawChoices(sFastMegas);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_FAST_WEATHER:
        previousOption = sFastWeather;
        sFastWeather = FastWeather_ProcessInput(sFastWeather);
        if (previousOption != sFastWeather)
            FastWeather_DrawChoices(sFastWeather);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_SURF_MUSIC:
        previousOption = sSurfMusic;
        sSurfMusic = SurfMusic_ProcessInput(sSurfMusic);
        if (previousOption != sSurfMusic)
            SurfMusic_DrawChoices(sSurfMusic);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_PARTY_MENU:
        previousOption = sPartyMenuStyle;
        sPartyMenuStyle = PartyMenuStyle_ProcessInput(sPartyMenuStyle);
        if (previousOption != sPartyMenuStyle)
            PartyMenuStyle_DrawChoices(sPartyMenuStyle);
        break;
    case OPTION_MENU_PG3_START + MENUITEM_BATTLE_FORMAT:
        previousOption = sBattleFormat;
        sBattleFormat = BattleFormat_ProcessInput(sBattleFormat);
        if (previousOption != sBattleFormat)
            BattleFormat_DrawChoices(sBattleFormat);
        break;
    }

    if (sArrowPressed)
    {
        sArrowPressed = FALSE;
        CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
    }
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    if (JOY_NEW(SELECT_BUTTON))
    {
        ShowOptionMenuHelp(taskId);
    }
    else if (JOY_REPEAT(L_BUTTON | R_BUTTON))
    {
        if (JOY_REPEAT(L_BUTTON))
        {
            if (gTasks[taskId].tMenuSelection > OPTION_MENU_VISIBLE_ROWS)
                gTasks[taskId].tMenuSelection -= OPTION_MENU_VISIBLE_ROWS;
            else
                gTasks[taskId].tMenuSelection = 0;

            if (sOptionScrollOffset > OPTION_MENU_VISIBLE_ROWS)
                sOptionScrollOffset -= OPTION_MENU_VISIBLE_ROWS;
            else
                sOptionScrollOffset = 0;
        }
        else
        {
            if (gTasks[taskId].tMenuSelection + OPTION_MENU_VISIBLE_ROWS < OPTION_MENU_ITEM_COUNT)
                gTasks[taskId].tMenuSelection += OPTION_MENU_VISIBLE_ROWS;
            else
                gTasks[taskId].tMenuSelection = OPTION_MENU_ITEM_COUNT - 1;

            if (sOptionScrollOffset + OPTION_MENU_VISIBLE_ROWS <= OPTION_MENU_MAX_SCROLL)
                sOptionScrollOffset += OPTION_MENU_VISIBLE_ROWS;
            else
                sOptionScrollOffset = OPTION_MENU_MAX_SCROLL;
        }

        DrawVisibleOptions(taskId);
    }
    else if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(DPAD_UP | DPAD_DOWN))
    {
        if (JOY_NEW(DPAD_UP))
        {
            if (gTasks[taskId].tMenuSelection == 0)
                gTasks[taskId].tMenuSelection = OPTION_MENU_ITEM_COUNT - 1;
            else
                gTasks[taskId].tMenuSelection--;
        }
        else
        {
            if (gTasks[taskId].tMenuSelection == OPTION_MENU_ITEM_COUNT - 1)
                gTasks[taskId].tMenuSelection = 0;
            else
                gTasks[taskId].tMenuSelection++;
        }

        if (gTasks[taskId].tMenuSelection < sOptionScrollOffset)
            sOptionScrollOffset = gTasks[taskId].tMenuSelection;
        else if (gTasks[taskId].tMenuSelection >= sOptionScrollOffset + OPTION_MENU_VISIBLE_ROWS)
            sOptionScrollOffset = gTasks[taskId].tMenuSelection - OPTION_MENU_VISIBLE_ROWS + 1;
        DrawVisibleOptions(taskId);
    }
    else
    {
        ProcessOptionInput(taskId);
    }
}


static void DrawVisibleOptions(u8 taskId)
{
    u8 row;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (row = 0; row < OPTION_MENU_VISIBLE_ROWS; row++)
    {
        u8 option = sOptionScrollOffset + row;

        if (option >= OPTION_MENU_ITEM_COUNT)
            break;
        sOptionDrawY = row * 16;
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, GetOptionName(option), 8, sOptionDrawY + 1, TEXT_SKIP_DRAW, NULL);
        DrawOptionChoices(taskId, option);
    }

    HighlightOptionMenuItem(gTasks[taskId].tMenuSelection - sOptionScrollOffset);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void AddOptionMenuScrollArrows(void)
{
    if (sOptionScrollArrowTaskId == TASK_NONE)
    {
        sOptionScrollArrowTaskId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP, 224, 48, 144, OPTION_MENU_MAX_SCROLL,
            TAG_OPTION_MENU_SCROLL_ARROW, TAG_OPTION_MENU_SCROLL_ARROW, &sOptionScrollOffset);
    }
}

static void RemoveOptionMenuScrollArrows(void)
{
    if (sOptionScrollArrowTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sOptionScrollArrowTaskId);
        sOptionScrollArrowTaskId = TASK_NONE;
    }
}

static void SaveCurrentSettings(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed = TextSpeed_NormalizeSelection(gTasks[taskId].tTextSpeed);
    gSaveBlock2Ptr->optionsBattleSceneOff = gTasks[taskId].tBattleSceneOff;
    gSaveBlock2Ptr->optionsBattleStyle = gTasks[taskId].tBattleStyle;
    gSaveBlock2Ptr->optionsSound = gTasks[taskId].tSound;
    gSaveBlock2Ptr->optionsButtonMode = gTasks[taskId].tButtonMode;
    gSaveBlock2Ptr->optionsWindowFrameType = gTasks[taskId].tWindowFrameType;
    gSaveBlock2Ptr->optionsFollowers = gTasks[taskId].tFollowers;
    gSaveBlock2Ptr->optionsLevelCaps = gTasks[taskId].tLevelCaps;
    gSaveBlock2Ptr->optionsAutorun = gTasks[taskId].tAutorun;
    gSaveBlock2Ptr->optionsTrainerLevelScaling = gTasks[taskId].tTrainerLevelScaling;
    gSaveBlock2Ptr->optionsWildLevelScaling = gTasks[taskId].tWildLevelScaling;
    SetCurrentDifficultyLevel(gTasks[taskId].tDifficulty ? DIFFICULTY_HARD : DIFFICULTY_NORMAL);
    VarSet(VAR_OVERWORLD_SPEEDUP, gTasks[taskId].tOverworldSpeedup);
    gSaveBlock2Ptr->optionsBattleSpeed = gTasks[taskId].tBattleSpeed;
    VarSet(VAR_BATTLE_SPEED, gTasks[taskId].tBattleSpeed);
    gSaveBlock2Ptr->optionsFastIntroNoSlide = gTasks[taskId].tFastIntroNoSlide;
    gSaveBlock2Ptr->optionsUiAnimationsOff = sUiAnimationsOff;
    gSaveBlock2Ptr->optionsDarkBattleUi = sDarkBattleUi;
    gSaveBlock2Ptr->optionsFastMegas = sFastMegas;
    gSaveBlock2Ptr->optionsFastWeather = sFastWeather;
    gSaveBlock2Ptr->optionsSurfMusic = sSurfMusic;
    SetSavedPartyMenuStyle(sPartyMenuStyle);
    SetReplayBattleFormat(sBattleFormat);
}

static void ShowOptionMenuHelp(u8 taskId)
{
    u8 selection = gTasks[taskId].tMenuSelection;

    RemoveOptionMenuScrollArrows();

    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);

    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, sText_OptionHelp, 8, 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, sText_CloseHelp, GetStringRightAlignXOffset(FONT_NORMAL, sText_CloseHelp, 198), 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    AddTextPrinterParameterized3(WIN_OPTIONS, FONT_NORMAL, 8, 1, sOptionGuideTextColors, TEXT_SKIP_DRAW, GetOptionName(selection));
    AddTextPrinterParameterized3(WIN_OPTIONS, FONT_NORMAL, 8, 21, sOptionGuideTextColors, TEXT_SKIP_DRAW, GetOptionHelpText(selection));
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);

    gTasks[taskId].func = Task_OptionMenuProcessHelpInput;
}

static void RedrawCurrentOptions(u8 taskId)
{
    DrawHeaderText();
    DrawVisibleOptions(taskId);
    AddOptionMenuScrollArrows();
    gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void Task_OptionMenuProcessHelpInput(u8 taskId)
{
    if (JOY_NEW(SELECT_BUTTON | A_BUTTON | B_BUTTON))
        RedrawCurrentOptions(taskId);
}

static void Task_OptionMenuSave(u8 taskId)
{
    SaveCurrentSettings(taskId);
    RemoveOptionMenuScrollArrows();
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void HighlightOptionMenuItem(u8 index)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(16, DISPLAY_WIDTH - 16));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(index * 16 + 40, index * 16 + 56));
}

static void DrawOptionMenuChoiceWithFont(const u8 *text, u8 x, u8 y, u8 style, u8 fontId)
{
    u8 dst[16];
    u16 i;

    for (i = 0; *text != EOS && i < ARRAY_COUNT(dst) - 1; i++)
        dst[i] = *(text++);

    if (style != 0)
    {
        dst[2] = TEXT_COLOR_RED;
        dst[5] = TEXT_COLOR_LIGHT_RED;
    }

    dst[i] = EOS;
    AddTextPrinterParameterized(WIN_OPTIONS, fontId, dst, x, y + 1, TEXT_SKIP_DRAW, NULL);
}

static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style)
{
    DrawOptionMenuChoiceWithFont(text, x, y, style, FONT_NORMAL);
}

static u8 TextSpeed_ProcessInput(u8 selection)
{
    selection = TextSpeed_NormalizeSelection(selection);

    if (JOY_NEW(DPAD_RIGHT))
    {
        selection = TextSpeed_GetNextSelection(selection);
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        selection = TextSpeed_GetPreviousSelection(selection);
        sArrowPressed = TRUE;
    }
    return selection;
}

static u8 TextSpeed_NormalizeSelection(u8 selection)
{
    if (selection != OPTIONS_TEXT_SPEED_FAST
     && selection != OPTIONS_TEXT_SPEED_FASTER
     && selection != OPTIONS_TEXT_SPEED_INSTANT)
        return OPTIONS_TEXT_SPEED_FAST;

    return selection;
}

static u8 TextSpeed_GetNextSelection(u8 selection)
{
    switch (TextSpeed_NormalizeSelection(selection))
    {
    case OPTIONS_TEXT_SPEED_FAST:
        return OPTIONS_TEXT_SPEED_FASTER;
    case OPTIONS_TEXT_SPEED_FASTER:
        return OPTIONS_TEXT_SPEED_INSTANT;
    default:
        return OPTIONS_TEXT_SPEED_FAST;
    }
}

static u8 TextSpeed_GetPreviousSelection(u8 selection)
{
    switch (TextSpeed_NormalizeSelection(selection))
    {
    case OPTIONS_TEXT_SPEED_FAST:
        return OPTIONS_TEXT_SPEED_INSTANT;
    case OPTIONS_TEXT_SPEED_FASTER:
        return OPTIONS_TEXT_SPEED_FAST;
    default:
        return OPTIONS_TEXT_SPEED_FASTER;
    }
}

static void TextSpeed_DrawChoices(u8 selection)
{
    u8 styles[TEXT_SPEED_STYLES_COUNT];
    s32 widthFast, widthFaster, widthInstant, xMid;

    selection = TextSpeed_NormalizeSelection(selection);

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[3] = 0;
    styles[4] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_TextSpeedFast, 104, YPOS_TEXTSPEED, styles[OPTIONS_TEXT_SPEED_FAST]);

    widthFast = GetStringWidth(FONT_NORMAL, gText_TextSpeedFast, 0);
    widthFaster = GetStringWidth(FONT_NORMAL, gText_TextSpeedFaster, 0);
    widthInstant = GetStringWidth(FONT_NORMAL, gText_TextSpeedInstant, 0);

    widthFaster -= 94;
    xMid = (widthFast - widthFaster - widthInstant) / 2 + 104;
    DrawOptionMenuChoice(gText_TextSpeedFaster, xMid, YPOS_TEXTSPEED, styles[OPTIONS_TEXT_SPEED_FASTER]);

    DrawOptionMenuChoice(gText_TextSpeedInstant, GetStringRightAlignXOffset(FONT_NORMAL, gText_TextSpeedInstant, 198), YPOS_TEXTSPEED, styles[OPTIONS_TEXT_SPEED_INSTANT]);
}

static u8 BattleScene_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleScene_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, YPOS_BATTLESCENE, styles[0]);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOff, 198), YPOS_BATTLESCENE, styles[1]);
}

static u8 BattleStyle_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleStyle_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleStyleShift, 104, YPOS_BATTLESTYLE, styles[0]);
    DrawOptionMenuChoice(gText_BattleStyleSet, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleStyleSet, 198), YPOS_BATTLESTYLE, styles[1]);
}

static u8 Sound_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        SetPokemonCryStereo(selection);
        sArrowPressed = TRUE;
    }

    return selection;
}

static void Sound_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_SoundMono, 104, YPOS_SOUND, styles[0]);
    DrawOptionMenuChoice(gText_SoundStereo, GetStringRightAlignXOffset(FONT_NORMAL, gText_SoundStereo, 198), YPOS_SOUND, styles[1]);
}

static u8 FrameType_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        sArrowPressed = TRUE;
    }
    return selection;
}

static void FrameType_DrawChoices(u8 selection)
{
    u8 text[16] = {EOS};
    u8 n = selection + 1;
    u16 i;

    for (i = 0; gText_FrameTypeNumber[i] != EOS && i <= 5; i++)
        text[i] = gText_FrameTypeNumber[i];

    // Convert a number to decimal string
    if (n / 10 != 0)
    {
        text[i] = n / 10 + CHAR_0;
        i++;
        text[i] = n % 10 + CHAR_0;
        i++;
    }
    else
    {
        text[i] = n % 10 + CHAR_0;
        i++;
        text[i] = CHAR_SPACER;
        i++;
    }

    text[i] = EOS;

    DrawOptionMenuChoice(gText_FrameType, 104, YPOS_FRAMETYPE, 0);
    DrawOptionMenuChoice(text, 128, YPOS_FRAMETYPE, 1);
}

static u8 ButtonMode_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void ButtonMode_DrawChoices(u8 selection)
{
    s32 widthNormal, widthLR, widthLA, xLR;
    u8 styles[3];

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_ButtonTypeNormal, 104, YPOS_BUTTONMODE, styles[0]);

    widthNormal = GetStringWidth(FONT_NORMAL, gText_ButtonTypeNormal, 0);
    widthLR = GetStringWidth(FONT_NORMAL, gText_ButtonTypeLR, 0);
    widthLA = GetStringWidth(FONT_NORMAL, gText_ButtonTypeLEqualsA, 0);

    widthLR -= 94;
    xLR = (widthNormal - widthLR - widthLA) / 2 + 104;
    DrawOptionMenuChoice(gText_ButtonTypeLR, xLR, YPOS_BUTTONMODE, styles[1]);

    DrawOptionMenuChoice(gText_ButtonTypeLEqualsA, GetStringRightAlignXOffset(FONT_NORMAL, gText_ButtonTypeLEqualsA, 198), YPOS_BUTTONMODE, styles[2]);
}


static u8 Followers_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}


static void Followers_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;
    
    DrawOptionMenuChoice(gText_BattleSceneOn, 104, YPOS_FOLLOWERS, styles[0]);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOff, 198), YPOS_FOLLOWERS, styles[1]);
}

static u8 Autorun_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void Autorun_DrawChoices(u8 selection)
{
    u8 styles[2];
    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;
    DrawOptionMenuChoice(gText_AutorunOn, 104, YPOS_AUTORUN, styles[0]);
    DrawOptionMenuChoice(gText_AutorunOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_AutorunOff, 198), YPOS_AUTORUN, styles[1]);
}

static u8 OverworldSpeedup_ProcessInput(u8 selection)
{
    if (selection > OPTIONS_OVERWORLD_SPEED_4X)
        selection = OPTIONS_OVERWORLD_SPEED_1X;

    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < OPTIONS_OVERWORLD_SPEED_4X)
            selection++;
        else
            selection = OPTIONS_OVERWORLD_SPEED_1X;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection > OPTIONS_OVERWORLD_SPEED_1X)
            selection--;
        else
            selection = OPTIONS_OVERWORLD_SPEED_4X;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void OverworldSpeedup_DrawChoices(u8 selection)
{
    u8 styles[4];

    if (selection > OPTIONS_OVERWORLD_SPEED_4X)
        selection = OPTIONS_OVERWORLD_SPEED_1X;

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[3] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_OverworldSpeed1x, 88, YPOS_OVERWORLD_SPEEDUP, styles[OPTIONS_OVERWORLD_SPEED_1X]);
    DrawOptionMenuChoice(gText_OverworldSpeed2x, 122, YPOS_OVERWORLD_SPEEDUP, styles[OPTIONS_OVERWORLD_SPEED_2X]);
    DrawOptionMenuChoice(gText_OverworldSpeed3x, 156, YPOS_OVERWORLD_SPEEDUP, styles[OPTIONS_OVERWORLD_SPEED_3X]);
    DrawOptionMenuChoice(gText_OverworldSpeed4x, GetStringRightAlignXOffset(FONT_NORMAL, gText_OverworldSpeed4x, 198), YPOS_OVERWORLD_SPEEDUP, styles[OPTIONS_OVERWORLD_SPEED_4X]);
}

static u8 BattleSpeed_ProcessInput(u8 selection)
{
    if (selection > OPTIONS_BATTLE_SCENE_3X)
        selection = OPTIONS_BATTLE_SCENE_1X;

    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < OPTIONS_BATTLE_SCENE_3X)
            selection++;
        else
            selection = OPTIONS_BATTLE_SCENE_1X;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection > OPTIONS_BATTLE_SCENE_1X)
            selection--;
        else
            selection = OPTIONS_BATTLE_SCENE_3X;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void BattleSpeed_DrawChoices(u8 selection)
{
    s32 width1x, width2x, width3x, x2x;
    u8 styles[3];

    if (selection > OPTIONS_BATTLE_SCENE_3X)
        selection = OPTIONS_BATTLE_SCENE_1X;

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSpeed1x, 104, YPOS_BATTLE_SPEED, styles[OPTIONS_BATTLE_SCENE_1X]);

    width1x = GetStringWidth(FONT_NORMAL, gText_BattleSpeed1x, 0);
    width2x = GetStringWidth(FONT_NORMAL, gText_BattleSpeed2x, 0);
    width3x = GetStringWidth(FONT_NORMAL, gText_BattleSpeed3x, 0);

    width2x -= 94;
    x2x = (width1x - width2x - width3x) / 2 + 104;
    DrawOptionMenuChoice(gText_BattleSpeed2x, x2x, YPOS_BATTLE_SPEED, styles[OPTIONS_BATTLE_SCENE_2X]);

    DrawOptionMenuChoice(gText_BattleSpeed3x, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSpeed3x, 198), YPOS_BATTLE_SPEED, styles[OPTIONS_BATTLE_SCENE_3X]);
}

static u8 IntroSlide_ProcessInput(u8 selection)
{
    if (selection > TRUE)
        selection = FALSE;

    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void IntroSlide_DrawChoices(u8 selection)
{
    u8 styles[2];

    if (selection > TRUE)
        selection = FALSE;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_IntroSlideOn, 104, YPOS_INTRO_SLIDE, styles[FALSE]);
    DrawOptionMenuChoice(gText_IntroSlideOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_IntroSlideOff, 198), YPOS_INTRO_SLIDE, styles[TRUE]);
}

static u8 UiAnimations_ProcessInput(u8 selection)
{
    if (selection > TRUE)
        selection = FALSE;

    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void UiAnimations_DrawChoices(u8 selection)
{
    u8 styles[2];

    if (selection > TRUE)
        selection = FALSE;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_IntroSlideOn, 104, YPOS_UI_ANIMATIONS, styles[FALSE]);
    DrawOptionMenuChoice(gText_IntroSlideOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_IntroSlideOff, 198), YPOS_UI_ANIMATIONS, styles[TRUE]);
}

static u8 DarkBattleUi_ProcessInput(u8 selection)
{
    if (selection > TRUE)
        selection = FALSE;

    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void DarkBattleUi_DrawChoices(u8 selection)
{
    u8 styles[2];

    if (selection > TRUE)
        selection = FALSE;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleUiLight, 104, YPOS_DARK_BATTLE_UI, styles[FALSE]);
    DrawOptionMenuChoice(gText_BattleUiDark, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleUiDark, 198), YPOS_DARK_BATTLE_UI, styles[TRUE]);
}

static u8 FastMegas_ProcessInput(u8 selection)
{
    if (selection > TRUE)
        selection = FALSE;

    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void FastMegas_DrawChoices(u8 selection)
{
    u8 styles[2];

    if (selection > TRUE)
        selection = FALSE;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_FastMegasOn, 104, YPOS_FAST_MEGAS, styles[TRUE]);
    DrawOptionMenuChoice(gText_FastMegasOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_FastMegasOff, 198), YPOS_FAST_MEGAS, styles[FALSE]);
}

static u8 FastWeather_ProcessInput(u8 selection)
{
    if (selection > TRUE)
        selection = FALSE;

    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void FastWeather_DrawChoices(u8 selection)
{
    u8 styles[2];

    if (selection > TRUE)
        selection = FALSE;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_FastWeatherOn, 104, YPOS_FAST_WEATHER, styles[TRUE]);
    DrawOptionMenuChoice(gText_FastWeatherOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_FastWeatherOff, 198), YPOS_FAST_WEATHER, styles[FALSE]);
}

static u8 SurfMusic_ProcessInput(u8 selection)
{
    if (selection > TRUE)
        selection = FALSE;

    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void SurfMusic_DrawChoices(u8 selection)
{
    u8 styles[2];

    if (selection > TRUE)
        selection = FALSE;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_SurfMusicOn, 104, YPOS_SURF_MUSIC, styles[TRUE]);
    DrawOptionMenuChoice(gText_SurfMusicOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_SurfMusicOff, 198), YPOS_SURF_MUSIC, styles[FALSE]);
}

static u8 PartyMenuStyle_ProcessInput(u8 selection)
{
    if (selection >= PARTY_MENU_OPTION_COUNT)
        selection = PARTY_MENU_DEFAULT_OPTION;

    if (JOY_NEW(DPAD_RIGHT))
    {
        switch (selection)
        {
        case PARTY_MENU_OPTION_CUSTOM:
            selection = PARTY_MENU_OPTION_HGSS;
            break;
        case PARTY_MENU_OPTION_HGSS:
            selection = PARTY_MENU_OPTION_BW;
            break;
        default:
            selection = PARTY_MENU_OPTION_CUSTOM;
            break;
        }
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        switch (selection)
        {
        case PARTY_MENU_OPTION_CUSTOM:
            selection = PARTY_MENU_OPTION_BW;
            break;
        case PARTY_MENU_OPTION_BW:
            selection = PARTY_MENU_OPTION_HGSS;
            break;
        default:
            selection = PARTY_MENU_OPTION_CUSTOM;
            break;
        }
        sArrowPressed = TRUE;
    }

    return selection;
}

static void PartyMenuStyle_DrawChoices(u8 selection)
{
    s32 widthCustom, widthHGSS, widthBW, xHGSS;
    u8 styles[PARTY_MENU_OPTION_COUNT] = {0};

    if (selection >= PARTY_MENU_OPTION_COUNT)
        selection = PARTY_MENU_DEFAULT_OPTION;

    styles[selection] = 1;

    widthCustom = GetStringWidth(FONT_NORMAL, gText_PartyMenuCustom, 0);
    widthHGSS = GetStringWidth(FONT_NORMAL, gText_PartyMenuHGSS, 0);
    widthBW = GetStringWidth(FONT_NORMAL, gText_PartyMenuBW, 0);
    xHGSS = 92 + widthCustom + (106 - widthCustom - widthHGSS - widthBW) / 2;

    DrawOptionMenuChoice(gText_PartyMenuCustom, 92, YPOS_PARTY_MENU, styles[PARTY_MENU_OPTION_CUSTOM]);
    DrawOptionMenuChoice(gText_PartyMenuHGSS, xHGSS, YPOS_PARTY_MENU, styles[PARTY_MENU_OPTION_HGSS]);
    DrawOptionMenuChoice(gText_PartyMenuBW, GetStringRightAlignXOffset(FONT_NORMAL, gText_PartyMenuBW, 198), YPOS_PARTY_MENU, styles[PARTY_MENU_OPTION_BW]);
}

static u8 GetSavedPartyMenuStyle(void)
{
    u8 selection;

    if (gSaveBlock1Ptr != NULL && gSaveBlock1Ptr->optionsPartyMenuStyleMagic == PARTY_MENU_OPTION_SAVE_MAGIC)
    {
        selection = gSaveBlock1Ptr->optionsPartyMenuStyle;
        if (selection < PARTY_MENU_OPTION_COUNT)
            return selection;
        return PARTY_MENU_DEFAULT_OPTION;
    }

    if (gSaveBlock2Ptr != NULL && gSaveBlock2Ptr->unused1)
        return PARTY_MENU_OPTION_BW;

    return PARTY_MENU_DEFAULT_OPTION;
}

static void SetSavedPartyMenuStyle(u8 selection)
{
    if (gSaveBlock1Ptr == NULL)
        return;

    if (selection >= PARTY_MENU_OPTION_COUNT)
        selection = PARTY_MENU_DEFAULT_OPTION;

    gSaveBlock1Ptr->optionsPartyMenuStyle = selection;
    gSaveBlock1Ptr->optionsPartyMenuStyleMagic = PARTY_MENU_OPTION_SAVE_MAGIC;
}

static u8 BattleFormat_ProcessInput(u8 selection)
{
    if (selection != REPLAY_BATTLE_FORMAT_DESIGNED
     && selection != REPLAY_BATTLE_FORMAT_SINGLES
     && selection != REPLAY_BATTLE_FORMAT_DOUBLES)
        selection = REPLAY_BATTLE_FORMAT_DESIGNED;

    if (JOY_NEW(DPAD_RIGHT))
    {
        switch (selection)
        {
        case REPLAY_BATTLE_FORMAT_DESIGNED:
            selection = REPLAY_BATTLE_FORMAT_SINGLES;
            break;
        case REPLAY_BATTLE_FORMAT_SINGLES:
            selection = REPLAY_BATTLE_FORMAT_DOUBLES;
            break;
        default:
            selection = REPLAY_BATTLE_FORMAT_DESIGNED;
            break;
        }
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        switch (selection)
        {
        case REPLAY_BATTLE_FORMAT_DESIGNED:
            selection = REPLAY_BATTLE_FORMAT_DOUBLES;
            break;
        case REPLAY_BATTLE_FORMAT_DOUBLES:
            selection = REPLAY_BATTLE_FORMAT_SINGLES;
            break;
        default:
            selection = REPLAY_BATTLE_FORMAT_DESIGNED;
            break;
        }
        sArrowPressed = TRUE;
    }
    return selection;
}

static void BattleFormat_DrawChoices(u8 selection)
{
    s32 widthDefault, widthSingles, widthDoubles, xSingles;
    u8 styles[3] = {0};

    if (selection != REPLAY_BATTLE_FORMAT_DESIGNED
     && selection != REPLAY_BATTLE_FORMAT_SINGLES
     && selection != REPLAY_BATTLE_FORMAT_DOUBLES)
        selection = REPLAY_BATTLE_FORMAT_DESIGNED;

    styles[selection] = 1;

    widthDefault = GetStringWidth(FONT_NARROWER, gText_BattleFormatDefault, 0);
    widthSingles = GetStringWidth(FONT_NARROWER, gText_BattleFormatSingles, 0);
    widthDoubles = GetStringWidth(FONT_NARROWER, gText_BattleFormatDoubles, 0);
    xSingles = 104 + widthDefault + (94 - widthDefault - widthSingles - widthDoubles) / 2;

    DrawOptionMenuChoiceWithFont(gText_BattleFormatDefault, 104, YPOS_BATTLE_FORMAT, styles[REPLAY_BATTLE_FORMAT_DESIGNED], FONT_NARROWER);
    DrawOptionMenuChoiceWithFont(gText_BattleFormatSingles, xSingles, YPOS_BATTLE_FORMAT, styles[REPLAY_BATTLE_FORMAT_SINGLES], FONT_NARROWER);
    DrawOptionMenuChoiceWithFont(gText_BattleFormatDoubles, GetStringRightAlignXOffset(FONT_NARROWER, gText_BattleFormatDoubles, 198), YPOS_BATTLE_FORMAT, styles[REPLAY_BATTLE_FORMAT_DOUBLES], FONT_NARROWER);
}

static u8 LevelCaps_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void LevelCaps_DrawChoices(u8 selection)
{
    s32 widthNoCaps, widthSoftCaps, widthHardCaps, xHardCaps;
    u8 styles[3];

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_NoCaps, 92, YPOS_LEVELCAPS, styles[0]);

    widthNoCaps = GetStringWidth(FONT_NORMAL, gText_NoCaps, 0);
    widthSoftCaps = GetStringWidth(FONT_NORMAL, gText_SoftCaps, 0);
    widthHardCaps = GetStringWidth(FONT_NORMAL, gText_HardCaps, 0);

    widthHardCaps -= 94;
    xHardCaps = (widthNoCaps - widthHardCaps - widthSoftCaps) / 2 + 100;
    DrawOptionMenuChoice(gText_SoftCaps, xHardCaps, YPOS_LEVELCAPS, styles[1]);

    DrawOptionMenuChoice(gText_HardCaps, GetStringRightAlignXOffset(FONT_NORMAL, gText_HardCaps, 198), YPOS_LEVELCAPS, styles[2]);
}

static u8 LevelScaling_ProcessInput(u8 selection)
{
    if (selection > LEVEL_SCALING_OPTION_ON)
        selection = LEVEL_SCALING_OPTION_OFF;

    if (JOY_NEW(DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }
    return selection;
}

static void LevelScaling_DrawChoices(u8 selection, u8 y)
{
    u8 styles[2];

    if (selection > LEVEL_SCALING_OPTION_ON)
        selection = LEVEL_SCALING_OPTION_OFF;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_ScalingOn, 104, y, styles[LEVEL_SCALING_OPTION_ON]);
    DrawOptionMenuChoice(gText_ScalingOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_ScalingOff, 198), y, styles[LEVEL_SCALING_OPTION_OFF]);
}

static void TrainerLevelScaling_DrawChoices(u8 selection)
{
    LevelScaling_DrawChoices(selection, YPOS_TRAINER_LEVEL_SCALING);
}

static void WildLevelScaling_DrawChoices(u8 selection)
{
    LevelScaling_DrawChoices(selection, YPOS_WILD_LEVEL_SCALING);
}

static u8 Difficulty_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void Difficulty_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_DifficultyNormal, 104, YPOS_DIFFICULTY, styles[0]);
    DrawOptionMenuChoice(gText_DifficultyHard, GetStringRightAlignXOffset(FONT_NORMAL, gText_DifficultyHard, 198), YPOS_DIFFICULTY, styles[1]);
}

static void DrawHeaderText(void)
{
    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, gText_Option, 8, 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, sText_OpenHelp, GetStringRightAlignXOffset(FONT_NORMAL, sText_OpenHelp, 198), 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}
#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Draw title window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  0, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1,  3,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2,  3, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28,  3,  1,  1,  7);

    // Draw options list window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  4, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}
