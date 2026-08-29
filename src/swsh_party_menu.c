#include "global.h"
#include "constants/party_menu.h"
#if PARTY_MENU_STYLE_OPTION
#define PARTY_MENU_VARIANT_SWSH
#include "party_menu_variant.h"
#endif

#include "malloc.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_gfx_sfx_util.h"
#include "battle_interface.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "item_icon.h"
#include "bg.h"
#include "contest.h"
#include "data.h"
#include "decompress.h"
#include "easy_chat.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "evolution_scene.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_move.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_specials.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "follower_npc.h"
#include "frontier_util.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "item_menu.h"
#include "item_use.h"
#include "pokemon_storage_system.h"
#include "caps.h"
#include "link.h"
#include "link_rfu.h"
#include "mail.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "menu_specialized.h"
#include "metatile_behavior.h"
#include "move_relearner.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "comfy_anim.h"
#include "player_pc.h"
#include "pokemon.h"
#include "pokerus.h"
#include "pokemon_icon.h"
#include "pokemon_jump.h"
#include "pokemon_storage_system.h"
#include "pokemon_summary_screen.h"
#include "pokedex.h"
#include "pokedex_plus_hgss.h"
#include "region_map.h"
#include "pokeball.h"
#include "reshow_battle_screen.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "start_menu.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "surfable.h"
#include "trade.h"
#include "union_room.h"
#include "window.h"
#include "constants/battle.h"
#include "constants/battle_frontier.h"
#include "constants/field_effects.h"
#include "constants/field_move.h"
#include "constants/form_change_types.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "constants/pokemon_icon.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#if SWSH_PARTY_MENU || PARTY_MENU_STYLE_OPTION

enum {
    MENU_SUMMARY,
    MENU_SWITCH,
    MENU_CANCEL1,
    MENU_ITEM,
    MENU_POKEDEX,
    MENU_GIVE,
    MENU_TAKE_ITEM,
    MENU_MOVE_ITEM,
    MENU_MAIL,
    MENU_TAKE_MAIL,
    MENU_READ,
    MENU_CANCEL2,
    MENU_SHIFT,
    MENU_SEND_OUT,
    MENU_ENTER,
    MENU_NO_ENTRY,
    MENU_STORE,
    MENU_REGISTER,
    MENU_TRADE1,
    MENU_TRADE2,
    MENU_LEVEL_UP_MOVES,
    MENU_EGG_MOVES,
    MENU_TM_MOVES,
    MENU_TUTOR_MOVES,
    MENU_SUB_MOVES,
    MENU_TOSS,
    MENU_CATALOG_BULB,
    MENU_CATALOG_OVEN,
    MENU_CATALOG_WASHING,
    MENU_CATALOG_FRIDGE,
    MENU_CATALOG_FAN,
    MENU_CATALOG_MOWER,
    MENU_CHANGE_FORM,
    MENU_CHANGE_ABILITY,
    MENU_FIELD_MOVES
};

// IDs for the action lists that appear when a party mon is selected
enum {
    ACTIONS_NONE,
    ACTIONS_SWITCH,
    ACTIONS_SHIFT,
    ACTIONS_SEND_OUT,
    ACTIONS_ENTER,
    ACTIONS_NO_ENTRY,
    ACTIONS_STORE,
    ACTIONS_SUMMARY_ONLY,
    ACTIONS_ITEM,
    ACTIONS_MAIL,
    ACTIONS_REGISTER,
    ACTIONS_TRADE,
    ACTIONS_SPIN_TRADE,
    ACTIONS_MOVES_SUB,
    ACTIONS_TAKEITEM_TOSS,
    ACTIONS_ROTOM_CATALOG,
    ACTIONS_ZYGARDE_CUBE,
};

enum {
    PARTY_BOX_LEFT_COLUMN,
    PARTY_BOX_RIGHT_COLUMN,
    PARTY_BOX_SWSH_COLUMN,
};

enum {
    TAG_POKEBALL = 1200,
    TAG_POKEBALL_SMALL,
    TAG_STATUS_ICONS,
};

#define TAG_HELD_ITEM               55120
#define TAG_HOVER_CURSOR            55121
#define TAG_HOVER_ITEM              55122
#define TAG_HELD_ITEM_ICON_BASE     55123
#define TAG_SELECT_FRAME            55130
#define TAG_MON_SHADOW              55140
#define TAG_SWITCH_ITEM_1           55141
#define TAG_SWITCH_ITEM_2           55142
#define TAG_MESSAGE_WINDOW          55150
#define TAG_MULTIUSE_WINDOW         55151
#define TAG_MOVE_TYPES              55160
#define TAG_SELECTED_MON_ITEM_ICON  55170

#define PARTY_PAL_SELECTED     (1 << 0)
#define PARTY_PAL_FAINTED      (1 << 1)
#define PARTY_PAL_TO_SWITCH    (1 << 2)
#define PARTY_PAL_MULTI_ALT    (1 << 3)
#define PARTY_PAL_TO_SOFTBOIL  (1 << 5)
#define PARTY_PAL_NO_MON       (1 << 6)
#define PARTY_PAL_UNUSED       (1 << 7)

#define MENU_DIR_DOWN     1
#define MENU_DIR_UP      -1
#define MENU_DIR_RIGHT    2
#define MENU_DIR_LEFT    -2

enum {
    // Window ids 0-5 are implicitly assigned to each party Pokémon in InitPartyMenuBoxes
    WIN_MSG = PARTY_SIZE,
};

struct PartyMenuBoxInfoRects
{
    void (*blitFunc)(u8, u8, u8, u8, u8, bool8);
    u8 dimensions[24];
    u8 descTextLeft;
    u8 descTextTop;
    u8 descTextWidth;
    u8 descTextHeight;
};

struct PartyMenuMoveBoxInfoRects
{
    void (*blitFunc)(u8, u8, u8, u8, u8, bool8);
    u8 dimensions[8];
};

struct PartyMenuInternal
{
    TaskFunc task;
    MainCallback exitCallback;
    u32 chooseHalf:1;
    u32 lastSelectedSlot:3;  // Used to return to same slot when going left/right bewtween columns
    u32 spriteIdConfirmPokeball:7;
    u32 spriteIdCancelPokeball:7;
    u32 messageId:14;
    // Cursor movement state
    u8 comfyAnimX;
    u8 comfyAnimY;
    // Each party slot keeps its own animation so quickly scrolling through the
    // list leaves the previous slots smoothly returning to their resting place.
    struct ComfyAnim slotAnims[PARTY_SIZE];
    s16 slotSpriteOffsets[PARTY_SIZE];
    u8 offsetCursorSpriteId;
    s16 cursorSpriteOffset;

    // Item mode (activated by selecting Item in mon menu)
    bool8 inItemMode;

    u8 windowId[3];
    u8 promptWindowId;
    u8 actions[12];
    u8 numActions;
    // In vanilla Emerald, only the first 0xB0 hwords (0x160 bytes) are actually used.
    // However, a full 0x100 hwords (0x200 bytes) are allocated.
    // It is likely that the 0x160 value used below is a constant defined by
    // bin2c, the utility used to encode the compressed palette data.
    u16 palBuffer[BG_PLTT_SIZE / sizeof(u16)];
    s16 switchCounter;
    s16 data[16];
};

struct PartyMenuBox
{
    const struct PartyMenuBoxInfoRects *infoRects;
    const u8 *spriteCoords;
    u8 windowId;
    u8 monSpriteId;
    u8 itemSpriteId;
    u8 pokeballSpriteId;
    u8 statusSpriteId;
};

enum {
    BUTTON_PROMPT_NONE,
    BUTTON_PROMPT_CONFIRM,
    BUTTON_PROMPT_SWITCH,
    BUTTON_PROMPT_BOXES,
};

// EWRAM vars
static EWRAM_DATA struct PartyMenuInternal *sPartyMenuInternal = NULL;
#if !PARTY_MENU_STYLE_OPTION
EWRAM_DATA struct PartyMenu gPartyMenu = {0};
#endif
static EWRAM_DATA struct PartyMenuBox *sPartyMenuBoxes = NULL;
static EWRAM_DATA u8 *sPartyBgGfxTilemap = NULL;
static EWRAM_DATA u8 *sPartyBgTilemapBuffer = NULL;
static EWRAM_DATA u8 *sPartyBg3TilemapBuffer = NULL;
#if !PARTY_MENU_STYLE_OPTION
EWRAM_DATA bool8 gPartyMenuUseExitCallback = 0;
EWRAM_DATA u8 gSelectedMonPartyId = 0;
EWRAM_DATA MainCallback gPostMenuFieldCallback = NULL;
#endif
static EWRAM_DATA u16 *sSlot1TilemapBuffer = 0; // for switching party slots
static EWRAM_DATA u16 *sSlot2TilemapBuffer = 0; //
#if !PARTY_MENU_STYLE_OPTION
EWRAM_DATA u8 gSelectedOrderFromParty[MAX_FRONTIER_PARTY_SIZE] = {0};
#endif
static EWRAM_DATA u16 sPartyMenuItemId = 0;
#if !PARTY_MENU_STYLE_OPTION
EWRAM_DATA u8 gBattlePartyCurrentOrder[PARTY_SIZE / 2] = {0}; // bits 0-3 are the current pos of Slot 1, 4-7 are Slot 2, and so on
#endif
#if TESTING
static EWRAM_DATA bool8 sSkipGiveHeldItemVisualsForTest = FALSE;
static EWRAM_DATA bool8 sSkipTossHeldItemVisualsForTest = FALSE;
static EWRAM_DATA bool8 sInvalidHeldItemSpriteAccessForTest = FALSE;
#endif
static EWRAM_DATA u8 sFusionFirstMonSlot = 0; // Fusion item: selected first mon slot
static EWRAM_DATA u16 sFusionFirstMonSpecies = 0; // Fusion item: selected first mon species
static EWRAM_DATA u8 sInitialLevel = 0;
static EWRAM_DATA u8 sFinalLevel = 0;
static EWRAM_DATA u8 sHoverCursorSpriteId = 0;
static EWRAM_DATA u8 sItemIconSpriteId = 0;
static EWRAM_DATA u8 sSelectFrameSpriteIds[7] = {0}; // Left + 5 middle + Right
static EWRAM_DATA u8 sMessageWindowSpriteIds[16] = {0}; // 8 across * 2 rows
static EWRAM_DATA u8 sMultiuseWindowSpriteIds[6] = {0}; // 3 across * 2 rows
static EWRAM_DATA u8 sMonSpriteId = 0;
static EWRAM_DATA u8 sMoveWindowIds[MAX_MON_MOVES];
static EWRAM_DATA u8 sAbilityWindowId;
static EWRAM_DATA u8 sMonShadowSpriteId = 0;
static EWRAM_DATA u8 sSelectedMonItemSpriteId = 0;
static EWRAM_DATA u8 sPartyTitleWindowId = 0;
static EWRAM_DATA u8 sSelectedMonHeldItemInfoWindowId = 0;
static EWRAM_DATA u16 sMonAnimTimer = 0;
static EWRAM_DATA u8 sMoveTypeSpriteIds[MAX_MON_MOVES];
// Saved party menu state for reopening after opening the PC Move Pokémon UI
static EWRAM_DATA u8 sSavedPartyMenuType = 0;
static EWRAM_DATA u8 sSavedPartyLayout = 0;
static EWRAM_DATA u8 sSavedPartyAction = 0;
static EWRAM_DATA u8 sSavedPartyMessageId = 0;
static EWRAM_DATA TaskFunc sSavedPartyTask = NULL;
static EWRAM_DATA MainCallback sSavedPartyExitCallback = NULL;
static EWRAM_DATA u8 sSavedPartySlotId = 0;


// IWRAM common
#if !PARTY_MENU_STYLE_OPTION
COMMON_DATA void (*gItemUseCB)(u8, TaskFunc) = NULL;
#endif

static void ResetPartyMenu(void);
static void CB2_InitPartyMenu(void);
static void CB2_ReloadPartyMenu(void);
static bool8 ShowPartyMenu(void);
static bool8 ReloadPartyMenu(void);
static void SetPartyMonsAllowedInMinigame(void);
static void ExitPartyMenu(void);
static bool8 AllocPartyMenuBg(void);
static bool8 DecompressGraphics(void);
static void InitPartyMenuWindows(u8);
static void LoadPartyMenuWindows(void);
static void ShowSelectedMonInfo(void);
static void InitPartyMenuBoxes(u8);
static void LoadPartyMenuBoxes(u8);
static bool8 CreatePartyMonSpritesLoop(void);
static bool8 RenderPartyMenuBoxes(void);
static void Task_ExitPartyMenu(u8);
static void FreePartyPointers(void);
static u8 LoadMonGfxAndSprite(struct Pokemon *, s16 *, bool32);
static u8 CreateMonSprite(struct Pokemon *, bool32);
static void DestroyMonSprite(void);
static void UpdateSelectedMonItemSprite(void);
static void DestroySelectedMonItemSprite(void);
static void UpdatePartyMonSprite(u8);
static void SpriteCB_PartyMonPokemon(struct Sprite *);
static void RunMonAnimTimer(void);
static void PartyPaletteBufferCopy(u8);
static void ApplyFaintedPartyBoxFrameColors(void);
static void DisplayPartyPokemonDataForMultiBattle(u8);
static void LoadPartyBoxPalette(struct PartyMenuBox *, u8);
static void DrawEmptySlot(u8 windowId);
static void DisplayPartyPokemonDataForRelearner(u8);
static void DisplayPartyPokemonDataForContest(u8);
static void DisplayPartyPokemonDataForChooseHalf(u8);
static void DisplayPartyPokemonDataForFusion(u8);
static void DisplayPartyPokemonDataForFormChange(u8);
static void DisplayPartyPokemonDataForWirelessMinigame(u8);
static void DisplayPartyPokemonDataForBattlePyramidHeldItem(u8);
static bool8 DisplayPartyPokemonDataForItemOrTutor(u8);
static void DisplayPartyPokemonData(u8);
static void DisplayPartyPokemonNickname(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonLevelCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonGenderNidoranCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonHPCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonMaxHPCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonHPBarCheck(struct Pokemon *, struct PartyMenuBox *);
static void DisplayPartyPokemonDescriptionText(u8, struct PartyMenuBox *, u8);
static bool8 IsMonAllowedInMinigame(u8);
static void DisplayPartyPokemonDataToTeachMove(u8, enum Move);
static enum CanMoveBeLearned CanTeachMove(struct Pokemon *, enum Move);
static void DisplayPartyPokemonBarDetail(u8, const u8 *, u8, const u8 *);
static void DisplayPartyPokemonBarDetailToFit(u8 windowId, const u8 *str, u8 color, const u8 *align, u32 width);
static void DisplayPartyPokemonLevel(u8, struct PartyMenuBox *);
static void DisplayPartyPokemonGender(u8, u16, u8 *, struct PartyMenuBox *);
static void DisplayPartyPokemonHP(u16 hp, u16 maxHp, struct PartyMenuBox *menuBox);
static void DisplayPartyPokemonMaxHP(u16, struct PartyMenuBox *);
static void DisplayPartyPokemonHPBar(u16, u16, struct PartyMenuBox *);
static void CreatePartyMonIconSpriteParameterized(u16 species, u32 pid, bool32 isShiny, bool32 isEgg, struct PartyMenuBox *menuBox, u8 priority);
static void CreatePartyMonHeldItemSpriteParameterized(u16, enum Item, struct PartyMenuBox *);
static void CreatePartyMonStatusSpriteParameterized(u16, u8, struct PartyMenuBox *);
// These next 4 functions are essentially redundant with the above 4
// The only difference is that rather than receive the data directly they retrieve it from the mon struct
static void CreatePartyMonHeldItemSprite(struct Pokemon *, struct PartyMenuBox *);
static void CreatePartyMonIconSprite(struct Pokemon *, struct PartyMenuBox *, u32);
static void CreatePartyMonStatusSprite(struct Pokemon *, struct PartyMenuBox *);
static void CreateHoverSprite(struct PartyMenuBox *, u8);
static void CreateMessageWindowSprite(void);
static void DestroyMessageWindowSprite(void);
static void CreateMultiuseWindowSprite(void);
static void DestroyMultiuseWindowSprite(void);
static void DestroyHoverSprite(void);
static void CreateItemIconSprite(struct PartyMenuBox *, u8, enum Item);
static void CreateItemMoveSprite(u8, u8, enum Item);
static void DestroyItemIconSprite(void);
static void CreateSelectFrame(struct PartyMenuBox *, u8);
static void DestroySelectFrame(void);
static void AnimateSelectedPartyIcon(u8, u8);
static void PartyMenuStartSpriteAnim(u8, u8);
static u8 GetPartyBoxPaletteFlags(u8, u8);
static bool8 PartyBoxPal_ParnterOrDisqualifiedInArena(u8);
static u8 GetPartyIdFromBattleSlot(u8);
static void BlitBitmapToPartyMoveWindow_SwSh(u8, u8, u8, u8, u8, bool8);
static void UpdatePartyMoveWindows(u8);
static void DestroyMoveTypeSprites(void);
static void DisplayPartyPokemonMoves(u8, struct Pokemon *, int);
static void DisplayPartyPokemonAbility(u8, u8);
static bool8 ShouldShowBattleDetails(void);
static u8 *GetPartyMenuBgTile(u16);
static void Task_ClosePartyMenuAndSetCB2(u8);
static void UpdatePartyToFieldOrder(void);
static void HandleChooseMonCancel(u8, s8 *);
static void HandleChooseMonSelection(u8, s8 *);
static u16 PartyMenuButtonHandler(s8 *);
static s8 *GetCurrentPartySlotPtr(void);
static bool8 IsSelectedMonNotEgg(u8 *);
static bool8 DoesSelectedMonKnowHM(u8 *);
static void PartyMenuRemoveWindow(u8 *);
static void CB2_SetUpExitToBattleScreen(void);
static void Task_ClosePartyMenuAfterText(u8);
static void TryTutorSelectedMon(u8);
static void TryGiveMailToSelectedMon(u8);
static void TryGiveItemOrMailToSelectedMon(u8);
static void SwitchSelectedMons(u8);
static void TryEnterMonForMinigame(u8, u8);
static void Task_TryCreateSelectionWindow(u8);
static bool8 IsBattleEntrySelectionComplete(void);
static inline u8 GetButtonPromptType(void);
static void ShowButtonPrompt(u8 type);
static void RefreshSelectedMonInfoAndPrompt(void);
static void PrintButtonIcon(u8 windowId, u8 buttonType, u32 x, u32 y);
static void PrintTextOnWindowWithFont(u8 windowId, const u8 *string, u8 x, u8 y, u8 lineSpacing, u8 colorId, u32 fontId);
static void PrintTextOnWindowToFit(u8 windowId, const u8 *string, u8 x, u8 y, u32 width, u8 colorId, u32 fontId);
static void FinishTwoMonAction(u8);
static void CancelParticipationPrompt(u8);
static bool8 DisplayCancelChooseMonYesNo(u8);
static const u8 *GetFacilityCancelString(void);
static void Task_CancelChooseMonYesNo(u8);
static void PartyMenuDisplayYesNoMenu(void);
static void Task_HandleCancelChooseMonYesNoInput(u8);
static void Task_ReturnToChooseMonAfterText(u8);
static void UpdateCurrentPartySelection(s8 *, s8);
static void InitPartySlotAnimations(void);
static void InitPartySlotScanlineEffect(void);
static void UpdatePartySlotAnimations(void);
static void ApplyPartySlotOffsetToSprite(struct PartyMenuBox *, u8);
static void UpdatePartySelectionSingleLayout(s8 *, s8);
static void UpdatePartySelectionDoubleLayout(s8 *, s8);
static s8 GetNewSlotDoubleLayout(s8, s8);
static void PrintMessage(const u8 *);
static void Task_PrintAndWaitForText(u8);
static bool16 IsMonAllowedInPokemonJump(struct Pokemon *);
static bool16 IsMonAllowedInDodrioBerryPicking(struct Pokemon *);
static void Task_CancelParticipationYesNo(u8);
static void Task_HandleCancelParticipationYesNoInput(u8);
static bool8 ShouldUseChooseMonText(void);
static void SetPartyMonFieldSelectionActions(struct Pokemon *, u8);
static void SetPartyMonLearnMoveSelectionActions(struct Pokemon*, u8);
static u8 GetPartyMenuActionsTypeInBattle(struct Pokemon *);
static u8 GetPartyMenuActionsType(struct Pokemon *mon);
static u8 GetPartySlotEntryStatus(s8);
static void Task_UpdateHeldItemSprite(u8);
static void Task_HandleSelectionMenuInput(u8);
static void CB2_ShowPokemonSummaryScreen(void);
static void UpdatePartyToBattleOrder(void);
static void SlidePartyMenuBoxOneStep(u8);
static void Task_SlideSelectedSlotsOffscreen(u8);
static void SwitchPartyMon(void);
static void Task_SlideSelectedSlotsOnscreen(u8);
static void CB2_SelectBagItemToGive(void);
static void CB2_GiveHoldItem(void);
static void CB2_WriteMailToGiveMon(void);
static void Task_SwitchHoldItemsPrompt(u8);
static void Task_GiveHoldItem(u8);
static void Task_SwitchItemsYesNo(u8);
static void Task_HandleSwitchItemsYesNoInput(u8);
static void Task_WriteMailToGiveMonAfterText(u8);
static void CB2_ReturnToPartyMenuFromWritingMail(void);
static void Task_DisplayGaveMailFromPartyMessage(u8);
static void UpdatePartyMonHeldItemSprite(struct Pokemon *, struct PartyMenuBox *);
static void Task_TossHeldItemYesNo(u8 taskId);
static void Task_HandleTossHeldItemYesNoInput(u8);
static void Task_TossHeldItem(u8);
static void CB2_ReadHeldMail(void);
static void CB2_ReturnToPartyMenuFromReadingMail(void);
static void Task_SendMailToPCYesNo(u8);
static void Task_HandleSendMailToPCYesNoInput(u8);
static void Task_LoseMailMessageYesNo(u8);
static void Task_HandleLoseMailMessageYesNoInput(u8);
static bool8 TrySwitchInPokemon(void);
static void Task_SpinTradeYesNo(u8);
static void Task_HandleSpinTradeYesNoInput(u8);
static void Task_CancelAfterAorBPress(u8);
static void DisplayFieldMoveExitAreaMessage(u8);
static void DisplayCantUseFlashMessage(void);
static void DisplayCantUseSurfMessage(void);
static void Task_FieldMoveExitAreaYesNo(u8);
static void Task_HandleFieldMoveExitAreaYesNoInput(u8);
static void Task_FieldMoveWaitForFade(u8);
static u16 GetFieldMoveMonSpecies(void);
static void UpdatePartyMonHPBar(u8, struct Pokemon *);
static void SpriteCB_UpdatePartyMonIcon(struct Sprite *);
static void SpriteCB_BouncePartyMonIcon(struct Sprite *);
static void ShowOrHideHeldItemSprite(enum Item, struct PartyMenuBox *);
static void CreateHeldItemSpriteForTrade(u8, bool8);
static void SpriteCB_HeldItem(struct Sprite *);
static void SetPartyMonAilmentGfx(struct Pokemon *, struct PartyMenuBox *);
static void UpdatePartyMonAilmentGfx(u8, struct PartyMenuBox *);
static u8 GetPartyLayoutFromBattleType(void);
static void Task_SetSacredAshCB(u8);
static void CB2_ReturnToBagMenu(void);
static void Task_DisplayHPRestoredMessage(u8);
static u16 ItemEffectToMonEv(struct Pokemon *, u8);
static u16 ItemEffectToMonIV(struct Pokemon *, u8);
static void ItemEffectToStatString(u8, u8 *);
static void ReturnToUseOnWhichMon(u8);
static void SetSelectedMoveForItem(u8);
static void TryUseItemOnMove(u8);
static void Task_LearnedMove(u8);
static void Task_ReplaceMoveYesNo(u8);
static void Task_DoLearnedMoveFanfareAfterText(u8);
static void Task_LearnNextMoveOrClosePartyMenu(u8);
static void Task_TryLearningNextMove(u8);
static void Task_HandleReplaceMoveYesNoInput(u8);
static void Task_ShowSummaryScreenToForgetMove(u8);
static void StopLearningMovePrompt(u8);
static void CB2_ShowSummaryScreenToForgetMove(void);
static void CB2_ReturnToPartyMenuWhileLearningMove(void);
static void Task_ReturnToPartyMenuWhileLearningMove(u8);
static void DisplayPartyMenuForgotMoveMessage(u8);
static void Task_PartyMenuReplaceMove(u8);
static void Task_HandleStopLearningMove(u8 taskId);
static void Task_StopLearningMoveYesNo(u8);
static void Task_HandleStopLearningMoveYesNoInput(u8);
static void Task_TryLearningNextMoveAfterText(u8);
static void BufferMonStatsToTaskData(struct Pokemon *, s16 *);
static void ItemUseCB_ReverseCandy(u8, TaskFunc);
static void UpdateMonDisplayInfoAfterRareCandy(u8, struct Pokemon *);
static void Task_DisplayLevelUpStatsPg1(u8);
static void DisplayLevelUpStatsPg1(u8);
static void Task_DisplayLevelUpStatsPg2(u8);
static void DisplayLevelUpStatsPg2(u8);
static void Task_TryLearnNewMoves(u8);
static void PartyMenuTryEvolution(u8);
static void DisplayMonNeedsToReplaceMove(u8);
static void DisplayMonLearnedMove(u8, u16);
static void UseSacredAsh(u8);
static void Task_SacredAshLoop(u8);
static void Task_SacredAshDisplayHPRestored(u8);
static void GiveItemOrMailToSelectedMon(u8);
static void DisplayItemMustBeRemovedFirstMessage(u8);
static void Task_SwitchItemsFromBagYesNo(u8);
static void CB2_WriteMailToGiveMonFromBag(void);
static void GiveItemToSelectedMon(u8);
static void Task_UpdateHeldItemSpriteAndClosePartyMenu(u8);
static void CB2_ReturnToPartyOrBagMenuFromWritingMail(void);
static bool8 ReturnGiveItemToBagOrPC(enum Item);
static void Task_DisplayGaveMailFromBagMessage(u8);
static void Task_HandleSwitchItemsFromBagYesNoInput(u8);
static void Task_ValidateChosenHalfParty(u8);
static void Task_ShowChosenHalfPartyYesNo(u8);
static void Task_HandleChosenHalfPartyYesNoInput(u8);
static void UnselectLastBattleEntry(void);
static bool8 GetBattleEntryEligibility(struct Pokemon *);
static bool8 IsFrontierSpeciesBanEnforcedForBattleEntry(void);
static bool8 HasPartySlotAlreadyBeenSelected(u8);
static u8 GetBattleEntryLevelCap(void);
static u8 GetMaxBattleEntries(void);
static u8 GetMinBattleEntries(void);
static void Task_ContinueChoosingHalfParty(u8);
static void BufferBattlePartyOrder(u8 *, bool8);
static void BufferBattlePartyOrderBySide(u8 *, u8, enum BattlerId);
static void Task_InitMultiPartnerPartySlideIn(u8);
static void Task_MultiPartnerPartySlideIn(u8);
static void SlideMultiPartyMenuBoxSpritesOneStep(u8);
static void Task_WaitAfterMultiPartnerPartySlideIn(u8);
static void BufferMonSelection(void);
static void Task_PartyMenuWaitForFade(u8 taskId);
static void Task_ChooseContestMon(u8 taskId);
static void CB2_ChooseContestMon(void);
static void Task_ChoosePartyMon(u8 taskId);
static void Task_ChooseMonForMoveRelearner(u8);
static void CB2_ChooseMonForMoveRelearner(void);
static void Task_BattlePyramidChooseMonHeldItems(u8);
static void ShiftMoveSlot(struct BoxPokemon *, u8, u8);
static void BlitBitmapToPartyWindow(u8, const u8 *, u8, u8, u8, u8, u8);
static void BlitBitmapToPartyWindow_SwSh(u8, u8, u8, u8, u8, bool8);
static void CursorCb_Summary(u8);
static void CursorCb_Switch(u8);
static void CursorCb_Cancel1(u8);
static void CursorCb_Item(u8);
static void CursorCb_Pokedex(u8);
static void CB2_OpenPartyPokedex(void);
static void CB2_ReturnToPartyMenuFromPokedex(void);
static void CursorCb_Give(u8);
static void CursorCb_TakeItem(u8);
static void CursorCb_MoveItem(u8);
static void CursorCb_Mail(u8);
static void CursorCb_Read(u8);
static void CursorCb_TakeMail(u8);
static void CursorCb_Cancel2(u8);
static void CursorCb_SendMon(u8);
static void CursorCb_Enter(u8);
static void CursorCb_NoEntry(u8);
static void CursorCb_Store(u8);
static void CursorCb_Register(u8);
static void CursorCb_Trade1(u8);
static void CursorCb_Trade2(u8);
static void CursorCb_Toss(u8);
static void CursorCb_FieldMove(u8);
static void CursorCb_ChangeLevelUpMoves(u8);
static void CursorCb_ChangeEggMoves(u8);
static void CursorCb_ChangeTMMoves(u8);
static void CursorCb_ChangeTutorMoves(u8);
static void CursorCb_LearnMovesSubMenu(u8);
static void CursorCb_CatalogBulb(u8);
static void CursorCb_CatalogOven(u8);
static void CursorCb_CatalogWashing(u8);
static void CursorCb_CatalogFridge(u8);
static void CursorCb_CatalogFan(u8);
static void CursorCb_CatalogMower(u8);
static void CursorCb_ChangeForm(u8);
static void CursorCb_ChangeAbility(u8);
void TryItemHoldFormChange(struct Pokemon *mon, s8 slotId);
static void ShowMoveSelectWindow(u8 slot);
static void Task_HandleWhichMoveInput(u8 taskId);
static u8 IsFusionMon(u16 species);
static void Task_HideFollowerNPCForTeleport(u8);
static void FieldCallback_RockClimb(void);
static void SavePartyMenuStateForPC(void);
static void CB2_ReopenPartyMenuFromPC(void);
// Multiuse item code from Kasen
static void DisplayGiveHowManyMessage(void);
static bool8 DoesItemIncreaseEV(u8 itemType);
static bool8 DoesItemReduceIV(u8 itemType);
static bool8 ShouldLevelUpItemUseLevelCap(void);
static u16 GetMaxLevelUpItemQuantity(struct Pokemon *mon, u8 holdEffectParam, u16 quantityInBag);
static void ClearHowManyItemsWindow(u8 taskId);
static void PrintHowManyItemsWindow(u8 taskId);
static void Task_GiveHowManyItems(u8 taskId);
static void Task_GiveHowManyItemsHandleInput(u8 taskId);
static void Task_ReturnToUseOnWhichMonAfterText(u8 taskId);
static void ItemUse_ApplyEvReduceBerry(u8 taskId);
static void ItemUse_ApplyEvIncreaseItem(u8 taskId);
static void ItemUse_ApplyIVReduceHerb(u8 taskId);
static void ItemUse_ApplyExpCandy(u8 taskId);
static void ItemUse_ApplyReverseCandy(u8 taskId);

static void Task_FirstBattleEnterParty_DarkenScreen(u8 taskId);
static void Task_FirstBattleEnterParty_WaitDarken(u8 taskId);
static void Task_FirstBattleEnterParty_CreatePrinter(u8 taskId);
static void Task_FirstBattleEnterParty_RunPrinterMsg1(u8 taskId);
static void Task_FirstBattleEnterParty_LightenFirstMonIcon(u8 taskId);
static void Task_FirstBattleEnterParty_WaitLightenFirstMonIcon(u8 taskId);
static void Task_FirstBattleEnterParty_StartPrintMsg2(u8 taskId);
static void Task_FirstBattleEnterParty_RunPrinterMsg2(u8 taskId);
static void Task_FirstBattleEnterParty_FadeNormal(u8 taskId);
static void Task_FirstBattleEnterParty_WaitFadeNormal(u8 taskId);

static const u8 sText_askText[] = _("Would you like to change {STR_VAR_1}'s\nability to {STR_VAR_2}?");
static const u8 sText_doneText[] = _("{STR_VAR_1}'s ability became\n{STR_VAR_2}!{PAUSE_UNTIL_PRESS}");
static const u8 sText_ChangePokeballAsk[] = _("Use the {STR_VAR_2} to change\n{STR_VAR_1}'s Ball?");
static const u8 sText_ChangePokeballDone[] = _("{STR_VAR_1}'s Ball was changed\nto the {STR_VAR_2}.{PAUSE_UNTIL_PRESS}");
static const u8 sText_PokeballAlreadyMatches[] = _("That Pokémon is already in\nthat kind of Ball.{PAUSE_UNTIL_PRESS}");
static const u8 sText_askShinyText[] = _("Would you like to turn {STR_VAR_1}\nshiny?");
static const u8 sText_doneShinyText[] = _("{STR_VAR_1} became shiny!{PAUSE_UNTIL_PRESS}");
static const u8 sText_BasePointsResetToZero[] = _("{STR_VAR_1}'s base points\nwere all reset to zero!{PAUSE_UNTIL_PRESS}");
static const u8 sText_CannotSendMonToBoxHM[] = _("Cannot send that mon to the box,\nbecause it knows a HM move.{PAUSE_UNTIL_PRESS}");
static const u8 sText_CannotSendMonToBoxPartner[] = _("Cannot send a mon that doesn't\nbelong to you to the box.{PAUSE_UNTIL_PRESS}");
static const u8 sText_GoWithThisTeam[] = _("Go with this team?");

#define tItemCount          data[5]
#define tMaxItemQuantity    data[6]
#define tQuantityInBag      data[7]
#define tWindowId           data[8]
#define tItemEffect         data[9]
#define tHoldEffectParam    data[10]

// static const data
#include "data/swsh_party_menu.h"

// code
static void InitPartyMenu(u8 menuType, u8 layout, u8 partyAction, bool8 keepCursorPos, u8 messageId, TaskFunc task, MainCallback callback)
{
    u16 i;

    ResetPartyMenu();
    sPartyMenuInternal = Alloc(sizeof(struct PartyMenuInternal));
    if (sPartyMenuInternal == NULL)
    {
        SetMainCallback2(callback);
    }
    else
    {
        gPartyMenu.menuType = menuType;
        gPartyMenu.exitCallback = callback;
        gPartyMenu.action = partyAction;
        sPartyMenuInternal->messageId = messageId;
        sPartyMenuInternal->task = task;
        sPartyMenuInternal->exitCallback = NULL;
        sPartyMenuInternal->lastSelectedSlot = 0;
        sPartyMenuInternal->spriteIdConfirmPokeball = 0x7F;
        sPartyMenuInternal->spriteIdCancelPokeball = 0x7F;

        if (menuType == PARTY_MENU_TYPE_CHOOSE_HALF)
            sPartyMenuInternal->chooseHalf = TRUE;
        else
            sPartyMenuInternal->chooseHalf = FALSE;

        if (layout != KEEP_PARTY_LAYOUT)
            gPartyMenu.layout = layout;

        for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->data); i++)
            sPartyMenuInternal->data[i] = 0;
        for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->windowId); i++)
            sPartyMenuInternal->windowId[i] = WINDOW_NONE;
        for (i = 0; i < PARTY_SIZE; i++)
            sPartyMenuInternal->slotSpriteOffsets[i] = 0;

        sPartyMenuInternal->inItemMode = FALSE;
        sPartyMenuInternal->comfyAnimX = INVALID_COMFY_ANIM;
        sPartyMenuInternal->comfyAnimY = INVALID_COMFY_ANIM;
        sPartyMenuInternal->offsetCursorSpriteId = MAX_SPRITES;
        if (!keepCursorPos)
            gPartyMenu.slotId = 0;

        else if (gPartyMenu.slotId > PARTY_SIZE - 1 || GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES) == SPECIES_NONE)
            gPartyMenu.slotId = 0;

        if (gPlayerPartyCount == 0)
            gPartyMenu.slotId = PARTY_SIZE + 1; // Cancel

        gTextFlags.autoScroll = 0;
        CalculatePlayerPartyCount();
        SetMainCallback2(CB2_InitPartyMenu);
    }
}

static void RefreshPartyMenu(void) //Refreshes the party menu without restarting tasks
{
    u16 i;
    for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->data); i++)
        sPartyMenuInternal->data[i] = 0;
    for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->windowId); i++)
        sPartyMenuInternal->windowId[i] = WINDOW_NONE;
    gTextFlags.autoScroll = 0;
    CalculatePlayerPartyCount();
    SetMainCallback2(CB2_ReloadPartyMenu);
}

static void CB2_UpdatePartyMenu(void)
{
    RunTasks();
    u8 cursorSpriteId = MAX_SPRITES;
    if (sHoverCursorSpriteId != MAX_SPRITES)
        cursorSpriteId = sHoverCursorSpriteId;
    else if (sItemIconSpriteId != MAX_SPRITES)
        cursorSpriteId = sItemIconSpriteId;

    if (cursorSpriteId != MAX_SPRITES)
    {
        AdvanceComfyAnimations();

        if (sPartyMenuInternal->comfyAnimX != INVALID_COMFY_ANIM)
        {
            struct ComfyAnim *anim = &gComfyAnims[sPartyMenuInternal->comfyAnimX];
            if (anim->inUse)
            {
                gSprites[cursorSpriteId].x = ReadComfyAnimValueSmooth(anim);
                if (anim->completed)
                {
                    ReleaseComfyAnim(sPartyMenuInternal->comfyAnimX);
                    sPartyMenuInternal->comfyAnimX = INVALID_COMFY_ANIM;
                }
            }
            else
            {
                sPartyMenuInternal->comfyAnimX = INVALID_COMFY_ANIM;
            }
        }

        if (sPartyMenuInternal->comfyAnimY != INVALID_COMFY_ANIM)
        {
            struct ComfyAnim *anim = &gComfyAnims[sPartyMenuInternal->comfyAnimY];
            if (anim->inUse)
            {
                gSprites[cursorSpriteId].y = ReadComfyAnimValueSmooth(anim);
                if (anim->completed)
                {
                    ReleaseComfyAnim(sPartyMenuInternal->comfyAnimY);
                    sPartyMenuInternal->comfyAnimY = INVALID_COMFY_ANIM;
                }
            }
            else
            {
                sPartyMenuInternal->comfyAnimY = INVALID_COMFY_ANIM;
            }
        }
    }
    UpdatePartySlotAnimations();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_PartyMenu(void)
{
    ScanlineEffect_InitHBlankDmaTransfer();
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ChangeBgX(3, 64, BG_COORD_ADD);
    ChangeBgY(3, 64, BG_COORD_ADD);
    if (SWSH_PARTY_MON_IDLE_ANIMS && sMonSpriteId != 0 && sMonSpriteId != MAX_SPRITES)
    {
        RunMonAnimTimer();
    }
}

static void CB2_InitPartyMenu(void)
{
    while (TRUE)
    {
        if (MenuHelpers_ShouldWaitForLinkRecv() == TRUE || ShowPartyMenu() == TRUE || MenuHelpers_IsLinkActive() == TRUE)
            break;
    }
}

static void CB2_ReloadPartyMenu(void)
{
    while (TRUE)
    {
        if (MenuHelpers_ShouldWaitForLinkRecv() == TRUE || ReloadPartyMenu() == TRUE || MenuHelpers_IsLinkActive() == TRUE)
            break;
    }
}

static bool8 ShowPartyMenu(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ResetVramOamAndBgCntRegs();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        gPaletteFade.bufferTransferDisabled = TRUE;
        gMain.state++;
        break;
    case 3:
        ResetSpriteData();
        gMain.state++;
        break;
    case 4:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 5:
        if (!MenuHelpers_IsLinkActive())
            ResetTasks();
        gMain.state++;
        break;
    case 6:
        SetPartyMonsAllowedInMinigame();
        gMain.state++;
        break;
    case 7:
        if (!AllocPartyMenuBg())
        {
            ExitPartyMenu();
            return TRUE;
        }
        else
        {
            sPartyMenuInternal->switchCounter = 0;
            gMain.state++;
        }
        break;
    case 8:
        if (DecompressGraphics())
            gMain.state++;
        break;
    case 9:
        InitPartyMenuWindows(gPartyMenu.layout);
        gMain.state++;
        break;
    case 10:
        InitPartyMenuBoxes(gPartyMenu.layout);
        sPartyMenuInternal->switchCounter = 0;
        gMain.state++;
        break;
    case 11:
        if (gMonSpritesGfxPtr == NULL)
            CreateMonSpritesGfxManager(MON_SPR_GFX_MANAGER_A, MON_SPR_GFX_MODE_NORMAL);
        gMain.state++;
        break;
    case 12:
        if (CreatePartyMonSpritesLoop())
        {
            sPartyMenuInternal->switchCounter = 0;
            gMain.state++;
        }
        break;
    case 13:
        if (RenderPartyMenuBoxes())
        {
            sPartyMenuInternal->switchCounter = 0;
            gMain.state++;
        }
        break;
    case 14:
        {
            u8 promptType = GetButtonPromptType();
            if (promptType != BUTTON_PROMPT_NONE
                && sPartyMenuInternal != NULL
                && sPartyMenuInternal->promptWindowId != WINDOW_NONE)
            {
                ShowButtonPrompt(promptType);
                PutWindowTilemap(sPartyMenuInternal->promptWindowId);
                ScheduleBgCopyTilemapToVram(0);
            }
        }
        gMain.state++;
        break;
    case 15:
        AnimatePartySlot(gPartyMenu.slotId, 1);
        CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);
        InitPartySlotAnimations();
        InitPartySlotScanlineEffect();
        gMain.state++;
        break;
    case 16:
        sPartyMenuInternal->switchCounter = 0;
        gMain.state++;
        break;
    case 17:
        if (!ShouldShowBattleDetails()
            && gPartyMenu.menuType != PARTY_MENU_TYPE_MULTI_SHOWCASE
            && gPartyMenu.slotId < gPlayerPartyCount
            && GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES) != SPECIES_NONE)
        {
            sMonSpriteId = LoadMonGfxAndSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuInternal->switchCounter, FALSE);
            if (sMonSpriteId != 0xFF)
                gMain.state++;
        }
        else
            gMain.state++;
        break;
    case 18:
        sPartyMenuInternal->switchCounter = 0;
        gMain.state++;
        break;
    case 19:
        if (!ShouldShowBattleDetails()
            && gPartyMenu.menuType != PARTY_MENU_TYPE_MULTI_SHOWCASE
            && gPartyMenu.slotId < gPlayerPartyCount
            && GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES) != SPECIES_NONE)
        {
            sMonShadowSpriteId = LoadMonGfxAndSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuInternal->switchCounter, TRUE);
            if (sMonShadowSpriteId != 0xFF)
                gMain.state++;
        }
        else
            gMain.state++;
        break;
    case 20:
        UpdateSelectedMonItemSprite();
        CreateTask(sPartyMenuInternal->task, 0);
        gMain.state++;
        break;
    case 21:
        BlendPalettes(PALETTES_ALL, 16, 0);
        gPaletteFade.bufferTransferDisabled = FALSE;
        gMain.state++;
        break;
    case 22:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_PartyMenu);
        SetMainCallback2(CB2_UpdatePartyMenu);
        return TRUE;
    }
    return FALSE;
}

static bool8 ReloadPartyMenu(void)
{
    u8 i;
    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        for (i = 0; i < MAX_MON_MOVES; i++)
            sMoveTypeSpriteIds[i] = MAX_SPRITES;
        gMain.state++;
        break;
    case 2:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 3:
        ResetPaletteFade();
        gPaletteFade.bufferTransferDisabled = TRUE;
        gMain.state++;
        break;
    case 4:
        ResetSpriteData();
        gMain.state++;
        break;
    case 5:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 6:
        SetPartyMonsAllowedInMinigame();
        sPartyMenuInternal->switchCounter = 0;
        gMain.state++;
        break;
    case 7:
        if (DecompressGraphics())
            gMain.state++;
        break;
    case 8:
        LoadPartyMenuWindows();
        gMain.state++;
        break;
    case 9:
        LoadPartyMenuBoxes(gPartyMenu.layout);
        sPartyMenuInternal->switchCounter = 0;
        gMain.state++;
        break;
    case 10:
        if (CreatePartyMonSpritesLoop())
        {
            sPartyMenuInternal->switchCounter = 0;
            gMain.state++;
        }
        break;
    case 11:
        if (RenderPartyMenuBoxes())
        {
            sPartyMenuInternal->switchCounter = 0;
            gMain.state++;
        }
        break;
    case 12:
        {
            u8 promptType = GetButtonPromptType();
            if (promptType != BUTTON_PROMPT_NONE
                && sPartyMenuInternal != NULL
                && sPartyMenuInternal->promptWindowId != WINDOW_NONE)
            {
                ShowButtonPrompt(promptType);
                PutWindowTilemap(sPartyMenuInternal->promptWindowId);
                ScheduleBgCopyTilemapToVram(0);
            }
        }
        gMain.state++;
        break;
    case 13:
        sPartyMenuInternal->switchCounter = 0;
        gMain.state++;
        break;
    case 14:
        if (!ShouldShowBattleDetails()
            && gPartyMenu.menuType != PARTY_MENU_TYPE_MULTI_SHOWCASE
            && gPartyMenu.slotId < gPlayerPartyCount
            && GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES) != SPECIES_NONE)
        {
            sMonSpriteId = LoadMonGfxAndSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuInternal->switchCounter, FALSE);
            if (sMonSpriteId != 0xFF)
                gMain.state++;
        }
        else
            gMain.state++;
        break;
    case 15:
        sPartyMenuInternal->switchCounter = 0;
        gMain.state++;
        break;
    case 16:
        if (!ShouldShowBattleDetails()
            && gPartyMenu.menuType != PARTY_MENU_TYPE_MULTI_SHOWCASE
            && gPartyMenu.slotId < gPlayerPartyCount
            && GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES) != SPECIES_NONE)
        {
            sMonShadowSpriteId = LoadMonGfxAndSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuInternal->switchCounter, TRUE);
            if (sMonShadowSpriteId != 0xFF)
                gMain.state++;
        }
        else
            gMain.state++;
        break;
    case 17:
        UpdateSelectedMonItemSprite();
        InitPartySlotAnimations();
        InitPartySlotScanlineEffect();
        BlendPalettes(PALETTES_ALL, 16, RGB_WHITEALPHA);
        gPaletteFade.bufferTransferDisabled = FALSE;
        gMain.state++;
        break;
    case 18:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_WHITEALPHA);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_PartyMenu);
        SetMainCallback2(CB2_UpdatePartyMenu);
        return TRUE;
    }
    return FALSE;
}

static void ExitPartyMenu(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_ExitPartyMenu, 0);
    SetVBlankCallback(VBlankCB_PartyMenu);
    SetMainCallback2(CB2_UpdatePartyMenu);
}

static void Task_ExitPartyMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(gPartyMenu.exitCallback);
        FreePartyPointers();
        DestroyTask(taskId);
    }
}

static void ResetPartyMenu(void)
{
    u8 i;
    sPartyMenuInternal = NULL;
    sPartyBgTilemapBuffer = NULL;
    sPartyBg3TilemapBuffer = NULL;
    sPartyMenuBoxes = NULL;
    sPartyBgGfxTilemap = NULL;
    sHoverCursorSpriteId = MAX_SPRITES;
    sItemIconSpriteId = MAX_SPRITES;
    sMonSpriteId = MAX_SPRITES;
    sMonShadowSpriteId = MAX_SPRITES;
    sSelectedMonItemSpriteId = MAX_SPRITES;
    sPartyTitleWindowId = WINDOW_NONE;
    sSelectedMonHeldItemInfoWindowId = WINDOW_NONE;
    sMonAnimTimer = 0;
    for (i = 0; i < ARRAY_COUNT(sSelectFrameSpriteIds); i++)
        sSelectFrameSpriteIds[i] = MAX_SPRITES;
    for (i = 0; i < ARRAY_COUNT(sMessageWindowSpriteIds); i++)
        sMessageWindowSpriteIds[i] = MAX_SPRITES;
    for (i = 0; i < ARRAY_COUNT(sMultiuseWindowSpriteIds); i++)
        sMultiuseWindowSpriteIds[i] = MAX_SPRITES;
    for (i = 0; i < MAX_MON_MOVES; ++i)
    {
        sMoveWindowIds[i] = WINDOW_NONE;
        sMoveTypeSpriteIds[i] = MAX_SPRITES;
    }
    sAbilityWindowId = WINDOW_NONE;
}

static bool8 ShouldShowBattleDetails(void)
{
    return SWSH_PARTY_BATTLE_DETAILS
        && gPartyMenu.menuType == PARTY_MENU_TYPE_IN_BATTLE;
}

static bool8 AllocPartyMenuBg(void)
{
    sPartyBgTilemapBuffer = Alloc(0x800);
    if (sPartyBgTilemapBuffer == NULL)
        return FALSE;

    sPartyBg3TilemapBuffer = Alloc(0x800);
    if (sPartyBg3TilemapBuffer == NULL)
        return FALSE;

    memset(sPartyBgTilemapBuffer, 0, 0x800);
    memset(sPartyBg3TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sPartyMenuBgTemplates, ARRAY_COUNT(sPartyMenuBgTemplates));
    SetBgTilemapBuffer(1, sPartyBgTilemapBuffer);
    SetBgTilemapBuffer(3, sPartyBg3TilemapBuffer);
    ResetAllBgsCoordinates();
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(3);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_BG3 | BLDCNT_TGT2_BG2 | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(14, 6));

    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
    return TRUE;
}

static bool8 DecompressGraphics(void)
{
    u32 sizeout;

    switch (sPartyMenuInternal->switchCounter)
    {
    case 0:
        if (sPartyBgGfxTilemap == NULL)
            sPartyBgGfxTilemap = malloc_and_decompress(sPartyMenuBg_Gfx_SwSh, &sizeout);
        else
            sizeout = GetDecompressedDataSize(sPartyMenuBg_Gfx_SwSh);
        LoadBgTiles(1, sPartyBgGfxTilemap, sizeout, 0);
        sPartyMenuInternal->switchCounter++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            DecompressDataWithHeaderWram(sPartyMenuBg_Main_Tilemap_SwSh, sPartyBgTilemapBuffer);
            sPartyMenuInternal->switchCounter++;
        }
        break;
    case 2:
        DecompressDataWithHeaderWram(sPartyMenuBg_Scroll_Tilemap_SwSh, sPartyBg3TilemapBuffer);
        ScheduleBgCopyTilemapToVram(3);
        sPartyMenuInternal->switchCounter++;
        break;
    case 3:
        LoadPalette(sPartyMenuBg_Pal_SwSh, BG_PLTT_ID(0), 11 * PLTT_SIZE_4BPP);
        CpuCopy16(gPlttBufferUnfaded, sPartyMenuInternal->palBuffer, 11 * PLTT_SIZE_4BPP);
        ApplyFaintedPartyBoxFrameColors();
        sPartyMenuInternal->switchCounter++;
        break;
    case 4:
        PartyPaletteBufferCopy(4);
        sPartyMenuInternal->switchCounter++;
        break;
    case 5:
        PartyPaletteBufferCopy(5);
        sPartyMenuInternal->switchCounter++;
        break;
    case 6:
        PartyPaletteBufferCopy(6);
        sPartyMenuInternal->switchCounter++;
        break;
    case 7:
        PartyPaletteBufferCopy(7);
        sPartyMenuInternal->switchCounter++;
        break;
    case 8:
        PartyPaletteBufferCopy(8);
        sPartyMenuInternal->switchCounter++;
        break;
    case 9:
        LoadSpriteSheet(&gSpriteSheet_HeldItem);
        sPartyMenuInternal->switchCounter++;
        break;
    case 10:
        LoadSpritePalette(&sSpritePalette_HeldItem);
        sPartyMenuInternal->switchCounter++;
        break;
    case 11:
        LoadCompressedSpriteSheet(&sSpriteSheet_SelectFrame);
        sPartyMenuInternal->switchCounter++;
        break;
    case 12:
        LoadSpritePalette(&sSpritePal_SelectFrame);
        sPartyMenuInternal->switchCounter++;
        break;
    case 13:
        LoadCompressedSpriteSheet(&sSpriteSheet_HoverCursor);
        sPartyMenuInternal->switchCounter++;
        break;
    case 14:
        LoadCompressedSpriteSheet(&sSpriteSheet_StatusIcons);
        sPartyMenuInternal->switchCounter++;
        break;
    case 15:
        LoadSpritePalette(&sSpritePalette_StatusIcons);
        sPartyMenuInternal->switchCounter++;
        break;
    case 16:
        LoadMonIconPalettes();
        sPartyMenuInternal->switchCounter++;
        break;
    case 17:
        LoadCompressedSpriteSheet(&sSpriteSheet_MessageWindow);
        sPartyMenuInternal->switchCounter++;
        break;
    case 18:
        LoadSpritePalette(&sSpritePal_MessageWindow);
        sPartyMenuInternal->switchCounter++;
        break;
    case 19:
        LoadCompressedSpriteSheet(&sSpriteSheet_MultiuseWindow);
        sPartyMenuInternal->switchCounter++;
        break;
    case 20:
        LoadSpritePalette(&sSpritePal_MultiuseWindow);
        sPartyMenuInternal->switchCounter++;
        break;
    case 21:
        if (ShouldShowBattleDetails())
            LoadCompressedSpriteSheet(&sSpriteSheet_MoveTypes);
        sPartyMenuInternal->switchCounter = 0;
        return TRUE;
    }
    return FALSE;
}

static void PartyPaletteBufferCopy(u8 palNum)
{
    u8 offset = PLTT_ID(palNum);
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(3)], &gPlttBufferUnfaded[offset], PLTT_SIZE_4BPP);
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(3)], &gPlttBufferFaded[offset], PLTT_SIZE_4BPP);
}

static void ApplyFaintedPartyBoxFrameColors(void)
{
    // The source palette leaves the visible slot fill unchanged and uses orange
    // accents. Replace the fill and accents while keeping text and HP bars intact.
    sPartyMenuInternal->palBuffer[sPartyBoxFaintedPalIds1[1]] = RGB(31, 8, 8);
    sPartyMenuInternal->palBuffer[sPartyBoxFaintedPalIds1[2]] = RGB(22, 3, 3);
    sPartyMenuInternal->palBuffer[sPartyBoxFaintedPalIds2[0]] = RGB(15, 4, 4);
    sPartyMenuInternal->palBuffer[sPartyBoxFaintedPalIds2[1]] = RGB(27, 5, 5);
    sPartyMenuInternal->palBuffer[sPartyBoxFaintedPalIds2[2]] = RGB(22, 3, 3);
    sPartyMenuInternal->palBuffer[sPartyBoxCurrSelectionFaintedPalIds[1]] = RGB(31, 14, 14);
    sPartyMenuInternal->palBuffer[sPartyBoxCurrSelectionFaintedPalIds[2]] = RGB(26, 6, 6);
    sPartyMenuInternal->palBuffer[sPartyBoxCurrSelectionFaintedPalIds2[0]] = RGB(31, 18, 18);
    sPartyMenuInternal->palBuffer[sPartyBoxCurrSelectionFaintedPalIds2[1]] = RGB(31, 12, 12);
    sPartyMenuInternal->palBuffer[sPartyBoxCurrSelectionFaintedPalIds2[2]] = RGB(26, 6, 6);
}

static void FreePartyPointers(void)
{
    ScanlineEffect_Stop();
    DestroyMonSprite();
    DestroyMonSpritesGfxManager(MON_SPR_GFX_MANAGER_A);
    DestroyMoveTypeSprites();
    // Clear alpha blending from party mon shadows
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);

    if (sPartyMenuInternal)
    {
        if (sPartyMenuInternal->comfyAnimX != INVALID_COMFY_ANIM)
            ReleaseComfyAnim(sPartyMenuInternal->comfyAnimX);
        if (sPartyMenuInternal->comfyAnimY != INVALID_COMFY_ANIM)
            ReleaseComfyAnim(sPartyMenuInternal->comfyAnimY);
        Free(sPartyMenuInternal);
        sPartyMenuInternal = NULL;
    }
    if (sPartyBgTilemapBuffer)
    {
        Free(sPartyBgTilemapBuffer);
        sPartyBgTilemapBuffer = NULL;
    }
    if (sPartyBg3TilemapBuffer)
    {
        Free(sPartyBg3TilemapBuffer);
        sPartyBg3TilemapBuffer = NULL;
    }
    if (sPartyBgGfxTilemap)
    {
        Free(sPartyBgGfxTilemap);
        sPartyBgGfxTilemap = NULL;
    }
    if (sPartyMenuBoxes)
    {
        Free(sPartyMenuBoxes);
        sPartyMenuBoxes = NULL;
    }
    FreeAllWindowBuffers();
}

static void InitPartyMenuBoxes(u8 layout)
{
    sPartyMenuBoxes = Alloc(sizeof(struct PartyMenuBox[PARTY_SIZE]));
    LoadPartyMenuBoxes(layout);
}

static void LoadPartyMenuBoxes(u8 layout)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        sPartyMenuInternal->slotSpriteOffsets[i] = 0;
        sPartyMenuBoxes[i].infoRects = &sPartyBoxInfoRects[PARTY_BOX_SWSH_COLUMN];
        sPartyMenuBoxes[i].spriteCoords = sPartyMenuSpriteCoords[layout][i];
        sPartyMenuBoxes[i].windowId = i;
        sPartyMenuBoxes[i].monSpriteId = SPRITE_NONE;
        sPartyMenuBoxes[i].itemSpriteId = SPRITE_NONE;
        sPartyMenuBoxes[i].pokeballSpriteId = SPRITE_NONE;
        sPartyMenuBoxes[i].statusSpriteId = SPRITE_NONE;
    }
}

static void RenderPartyMenuBox(u8 slot)
{
    if (gPartyMenu.menuType == PARTY_MENU_TYPE_MULTI_SHOWCASE && slot >= MULTI_PARTY_SIZE)
    {
        DisplayPartyPokemonDataForMultiBattle(slot);
        if (gMultiPartnerParty[slot - MULTI_PARTY_SIZE].species == SPECIES_NONE)
            LoadPartyBoxPalette(&sPartyMenuBoxes[slot], PARTY_PAL_NO_MON);
        else
            LoadPartyBoxPalette(&sPartyMenuBoxes[slot], PARTY_PAL_MULTI_ALT);
        CopyWindowToVram(sPartyMenuBoxes[slot].windowId, COPYWIN_GFX);
        PutWindowTilemap(sPartyMenuBoxes[slot].windowId);
        ScheduleBgCopyTilemapToVram(2);
    }
    else if (gPlayerPartyCount != 0)
    {
        if (GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES) == SPECIES_NONE)
        {
            DrawEmptySlot(sPartyMenuBoxes[slot].windowId);
            LoadPartyBoxPalette(&sPartyMenuBoxes[slot], PARTY_PAL_NO_MON);
            CopyWindowToVram(sPartyMenuBoxes[slot].windowId, COPYWIN_GFX);
        }
        else
        {
            if (gPartyMenu.menuType == PARTY_MENU_TYPE_MOVE_RELEARNER)
                DisplayPartyPokemonDataForRelearner(slot);
            else if (gPartyMenu.menuType == PARTY_MENU_TYPE_CONTEST)
                DisplayPartyPokemonDataForContest(slot);
            else if (gPartyMenu.menuType == PARTY_MENU_TYPE_CHOOSE_HALF)
                DisplayPartyPokemonDataForChooseHalf(slot);
            else if (gPartyMenu.menuType == PARTY_MENU_TYPE_MINIGAME)
                DisplayPartyPokemonDataForWirelessMinigame(slot);
            else if (gPartyMenu.menuType == PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS)
                DisplayPartyPokemonDataForBattlePyramidHeldItem(slot);
            else if (!DisplayPartyPokemonDataForItemOrTutor(slot))
                DisplayPartyPokemonData(slot);

            if (gPartyMenu.menuType == PARTY_MENU_TYPE_MULTI_SHOWCASE)
                AnimatePartySlot(slot, 0);
            else if (gPartyMenu.slotId == slot)
                AnimatePartySlot(slot, 1);
            else
                AnimatePartySlot(slot, 0);
        }
        PutWindowTilemap(sPartyMenuBoxes[slot].windowId);
        if (ShouldShowBattleDetails() && gPartyMenu.slotId == slot)
        {
            UpdatePartyMoveWindows(slot);
        }
        ScheduleBgCopyTilemapToVram(0);
    }
}

static void DisplayPartyPokemonData(u8 slot)
{
    if (GetMonData(&gPlayerParty[slot], MON_DATA_IS_EGG))
    {
        sPartyMenuBoxes[slot].infoRects->blitFunc(sPartyMenuBoxes[slot].windowId, 0, 0, 0, 0, TRUE);
        DisplayPartyPokemonNickname(&gPlayerParty[slot], &sPartyMenuBoxes[slot], 0);
    }
    else
    {
        sPartyMenuBoxes[slot].infoRects->blitFunc(sPartyMenuBoxes[slot].windowId, 0, 0, 0, 0, FALSE);
        DisplayPartyPokemonNickname(&gPlayerParty[slot], &sPartyMenuBoxes[slot], 0);
        DisplayPartyPokemonLevelCheck(&gPlayerParty[slot], &sPartyMenuBoxes[slot], 0);
        DisplayPartyPokemonGenderNidoranCheck(&gPlayerParty[slot], &sPartyMenuBoxes[slot], 0);
        DisplayPartyPokemonHPCheck(&gPlayerParty[slot], &sPartyMenuBoxes[slot], 0);
        DisplayPartyPokemonMaxHPCheck(&gPlayerParty[slot], &sPartyMenuBoxes[slot], 0);
        DisplayPartyPokemonHPBarCheck(&gPlayerParty[slot], &sPartyMenuBoxes[slot]);
    }
}

static void DisplayPartyPokemonDescriptionData(u8 slot, u8 stringID)
{
    struct Pokemon *mon = &gPlayerParty[slot];

    sPartyMenuBoxes[slot].infoRects->blitFunc(sPartyMenuBoxes[slot].windowId, 0, 0, 0, 0, TRUE);
    DisplayPartyPokemonNickname(mon, &sPartyMenuBoxes[slot], 0);
    if (!GetMonData(mon, MON_DATA_IS_EGG))
    {
        DisplayPartyPokemonLevelCheck(mon, &sPartyMenuBoxes[slot], 0);
        DisplayPartyPokemonGenderNidoranCheck(mon, &sPartyMenuBoxes[slot], 0);
    }
    DisplayPartyPokemonDescriptionText(stringID, &sPartyMenuBoxes[slot], 0);
}


static void UpdatePartyMoveWindows(u8 slot)
{
    int m;
    const u8 *tm;

    if (!ShouldShowBattleDetails())
        return;

    DestroyMoveTypeSprites();
    for (m = 0; m < MAX_MON_MOVES; ++m)
    {
        if (sMoveWindowIds[m] == WINDOW_NONE)
            continue;

        FillWindowPixelBuffer(sMoveWindowIds[m], PIXEL_FILL(0));
        tm = (GetMonData(&gPlayerParty[slot], MON_DATA_MOVE1 + m) != MOVE_NONE) ? sMoveTilemap_Main_SwSh : sMoveTilemap_Empty_SwSh;
        BlitBitmapToPartyWindow(sMoveWindowIds[m], tm, 14, 0, 0, 14, 2);
        {
            struct Pokemon *mon = &gPlayerParty[slot];
            enum Move move = GetMonData(mon, MON_DATA_MOVE1 + m);
            if (move != MOVE_NONE)
            {
                DisplayPartyPokemonMoves(sMoveWindowIds[m], mon, m);
            }
        }
        CopyWindowToVram(sMoveWindowIds[m], COPYWIN_GFX);
    }
    if (sAbilityWindowId != WINDOW_NONE)
        DisplayPartyPokemonAbility(sAbilityWindowId, slot);
}

static void DisplayPartyPokemonAbility(u8 windowId, u8 slot)
{
    if (windowId == WINDOW_NONE)
        return;

    u8 abilityNum;
    u16 species;
    enum Ability ability;
    const u8 *name;
    int x;
    int y = 16;

    FillWindowPixelBuffer(windowId, PIXEL_FILL(0));
    BlitBitmapToPartyWindow(windowId, sAbilityTilemap_SwSh, 13, 0, 0, 13, 4);

    {
        struct Pokemon *mon = &gPlayerParty[slot];
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE && !GetMonData(mon, MON_DATA_IS_EGG))
        {
            abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM);
            species = GetMonData(mon, MON_DATA_SPECIES);
            ability = GetAbilityBySpecies(species, abilityNum);
            name = gAbilitiesInfo[ability].name;
            x = GetStringCenterAlignXOffset(FONT_SMALL, name, 104);
            AddTextPrinterParameterized3(windowId, FONT_SMALL, x, y, sFontColorTable[9], 0, name);
        }
    }
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static void DisplayPartyPokemonDataForChooseHalf(u8 slot)
{
    u8 i;
    struct Pokemon *mon = &gPlayerParty[slot];
    u8 *order = gSelectedOrderFromParty;

    if (!GetBattleEntryEligibility(mon))
    {
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_NOT_ABLE);
        return;
    }
    else
    {
        for (i = 0; i < GetMaxBattleEntries(); i++)
        {
            if (order[i] != 0 && (order[i] - 1) == slot)
            {
                DisplayPartyPokemonDescriptionData(slot, i + PARTYBOX_DESC_FIRST);
                return;
            }
        }
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_ABLE_3);
    }
}

static void DisplayPartyPokemonDataForContest(u8 slot)
{
    switch (GetContestEntryEligibility(&gPlayerParty[slot]))
    {
    case CANT_ENTER_CONTEST:
    case CANT_ENTER_CONTEST_EGG:
    case CANT_ENTER_CONTEST_FAINTED:
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_NOT_ABLE);
        break;
    case CAN_ENTER_CONTEST_EQUAL_RANK:
    case CAN_ENTER_CONTEST_HIGH_RANK:
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_ABLE);
        break;
    }
}

static void DisplayPartyPokemonDataForRelearner(u8 slot)
{
    bool32 hasMoves = CanBoxMonRelearnMoves(&gPlayerParty[slot].box, gMoveRelearnerState);
    u32 desc = (hasMoves ? PARTYBOX_DESC_ABLE_2 : PARTYBOX_DESC_NOT_ABLE_2);
    DisplayPartyPokemonDescriptionData(slot, desc);
}

static void DisplayPartyPokemonDataForWirelessMinigame(u8 slot)
{
    if (IsMonAllowedInMinigame(slot) == TRUE)
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_ABLE);
    else
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_NOT_ABLE);
}

static void DisplayPartyPokemonDataForBattlePyramidHeldItem(u8 slot)
{
    if (GetMonData(&gPlayerParty[slot], MON_DATA_HELD_ITEM))
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_HAVE);
    else
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_DONT_HAVE);
}

enum ItemUseType
{
    ITEM_USE_NONE,
    ITEM_USE_TM_HM,
    ITEM_USE_EVOLUTION_STONE,
    ITEM_USE_FORM_CHANGE,
    ITEM_USE_FUSION,
};

static bool8 IsFusionItem(enum Item item)
{
    return GetItemFieldFunc(item) == ItemUseOutOfBattle_Fusion;
}

static bool8 IsFormChangeItem(enum Item item)
{
    ItemUseFunc fieldFunc = GetItemFieldFunc(item);
    return fieldFunc == ItemUseOutOfBattle_FormChange
        || fieldFunc == ItemUseOutOfBattle_FormChange_ConsumedOnUse;
}

static u8 CheckItemUseType(enum Item item)
{
    u8 tmhmOrStone = CheckIfItemIsTMHMOrEvolutionStone(item);

    if (tmhmOrStone != 0)
        return tmhmOrStone;

    if (IsFormChangeItem(item))
        return ITEM_USE_FORM_CHANGE;

    if (IsFusionItem(item))
        return ITEM_USE_FUSION;

    return ITEM_USE_NONE;
}

// static bool8 DisplayPartyPokemonDataForMoveTutorOrEvolutionItem(u8 slot) -- vanilla reference
static bool8 DisplayPartyPokemonDataForItemOrTutor(u8 slot)
{
    struct Pokemon *currentPokemon = &gPlayerParty[slot];
    enum Item item = gSpecialVar_ItemId;

    if (gPartyMenu.action == PARTY_ACTION_MOVE_TUTOR)
    {
        gSpecialVar_Result = FALSE;
        DisplayPartyPokemonDataToTeachMove(slot, gSpecialVar_0x8005);
    }
    else
    {
        if (gPartyMenu.action != PARTY_ACTION_USE_ITEM)
            return FALSE;

        switch (CheckItemUseType(item))
        {
        default:
        case ITEM_USE_NONE:
            return FALSE;
        case ITEM_USE_TM_HM:
            DisplayPartyPokemonDataToTeachMove(slot, ItemIdToBattleMoveId(item));
            break;
        case ITEM_USE_EVOLUTION_STONE:
            if (!GetMonData(currentPokemon, MON_DATA_IS_EGG) && GetEvolutionTargetSpecies(currentPokemon, EVO_MODE_ITEM_CHECK, item, NULL, NULL, CHECK_EVO) != SPECIES_NONE)
                return FALSE;
            DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_NO_USE);
            break;
        case ITEM_USE_FORM_CHANGE:
            DisplayPartyPokemonDataForFormChange(slot);
            break;
        case ITEM_USE_FUSION:
            if (sFusionFirstMonSlot < PARTY_SIZE)
            {
                sFusionFirstMonSlot = PARTY_SIZE;
                sFusionFirstMonSpecies = 0;
            }
            DisplayPartyPokemonDataForFusion(slot);
            break;
        }
    }
    return TRUE;
}

static void DisplayPartyPokemonDataToTeachMove(u8 slot, enum Move move)
{
    switch (CanTeachMove(&gPlayerParty[slot], move))
    {
    case CANNOT_LEARN_MOVE:
    case CANNOT_LEARN_MOVE_IS_EGG:
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_NOT_ABLE_2);
        break;
    case ALREADY_KNOWS_MOVE:
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_LEARNED);
        break;
    default:
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_ABLE_2);
        break;
    }
}

static void DisplayPartyPokemonDataForMultiBattle(u8 slot)
{
    struct PartyMenuBox *menuBox = &sPartyMenuBoxes[slot];
    u8 actualSlot = slot - MULTI_PARTY_SIZE;

    if (gMultiPartnerParty[actualSlot].species == SPECIES_NONE)
    {
        DrawEmptySlot(menuBox->windowId);
    }
    else
    {
        menuBox->infoRects->blitFunc(menuBox->windowId, 0, 0, 0, 0, FALSE);
        StringCopy(gStringVar1, gMultiPartnerParty[actualSlot].nickname);
        StringGet_Nickname(gStringVar1);
        ConvertInternationalPlayerName(gStringVar1);
        DisplayPartyPokemonBarDetailToFit(menuBox->windowId, gStringVar1, 0, menuBox->infoRects->dimensions, 50);
        DisplayPartyPokemonLevel(gMultiPartnerParty[actualSlot].level, menuBox);
        DisplayPartyPokemonGender(gMultiPartnerParty[actualSlot].gender, gMultiPartnerParty[actualSlot].species, gMultiPartnerParty[actualSlot].nickname, menuBox);
        DisplayPartyPokemonHP(gMultiPartnerParty[actualSlot].hp, gMultiPartnerParty[actualSlot].maxhp, menuBox);
        DisplayPartyPokemonMaxHP(gMultiPartnerParty[actualSlot].maxhp, menuBox);
        DisplayPartyPokemonHPBar(gMultiPartnerParty[actualSlot].hp, gMultiPartnerParty[actualSlot].maxhp, menuBox);
    }
}

static bool8 RenderPartyMenuBoxes(void)
{
    RenderPartyMenuBox(sPartyMenuInternal->switchCounter);
    if (++sPartyMenuInternal->switchCounter == PARTY_SIZE)
        return TRUE;
    else
        return FALSE;
}

static u8 *GetPartyMenuBgTile(u16 tileId)
{
    return &sPartyBgGfxTilemap[tileId << 5];
}

static void CreatePartyMonSprites(u8 slot)
{
    u8 actualSlot;

    if (gPartyMenu.menuType == PARTY_MENU_TYPE_MULTI_SHOWCASE && slot >= MULTI_PARTY_SIZE)
    {
        u32 multi;
        actualSlot = slot - MULTI_PARTY_SIZE;

        if (gMultiPartnerParty[actualSlot].species != SPECIES_NONE)
        {
            CreatePartyMonIconSpriteParameterized(gMultiPartnerParty[actualSlot].species, gMultiPartnerParty[actualSlot].personality, FALSE, FALSE, &sPartyMenuBoxes[slot], 0);
            CreatePartyMonHeldItemSpriteParameterized(gMultiPartnerParty[actualSlot].species, gMultiPartnerParty[actualSlot].heldItem, &sPartyMenuBoxes[slot]);
            if (gMultiPartnerParty[actualSlot].hp == 0)
                multi = AILMENT_FNT;
            else
                multi = GetAilmentFromStatus(gMultiPartnerParty[actualSlot].status);
            CreatePartyMonStatusSpriteParameterized(gMultiPartnerParty[actualSlot].species, multi, &sPartyMenuBoxes[slot]);
        }
    }
    else if (GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES) != SPECIES_NONE)
    {
        CreatePartyMonIconSprite(&gPlayerParty[slot], &sPartyMenuBoxes[slot], slot);
        CreatePartyMonHeldItemSprite(&gPlayerParty[slot], &sPartyMenuBoxes[slot]);
        CreatePartyMonStatusSprite(&gPlayerParty[slot], &sPartyMenuBoxes[slot]);
    }
}

static bool8 CreatePartyMonSpritesLoop(void)
{
    CreatePartyMonSprites(sPartyMenuInternal->switchCounter);
    if (++sPartyMenuInternal->switchCounter == PARTY_SIZE)
        return TRUE;
    else
        return FALSE;
}

void AnimatePartySlot(u8 slot, u8 animNum)
{
    u8 spriteId;

    switch (slot)
    {
    default:
        if (GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES) != SPECIES_NONE)
        {
            LoadPartyBoxPalette(&sPartyMenuBoxes[slot], GetPartyBoxPaletteFlags(slot, animNum));
            AnimateSelectedPartyIcon(sPartyMenuBoxes[slot].monSpriteId, animNum);
            ApplyPartySlotOffsetToSprite(&sPartyMenuBoxes[slot], sPartyMenuBoxes[slot].monSpriteId);
            PartyMenuStartSpriteAnim(sPartyMenuBoxes[slot].pokeballSpriteId, animNum);
        }
        return;
    case PARTY_SIZE: // Confirm
        if (animNum == 0)
        {
            // Disabled: SetBgTilemapPalette(1, 23, 16, 7, 2, 1);
        }
        else
        {
            // Disabled: SetBgTilemapPalette(1, 23, 16, 7, 2, 2);
        }
        spriteId = sPartyMenuInternal->spriteIdConfirmPokeball;
        break;
    case PARTY_SIZE + 1: // Cancel
        // The position of the Cancel button changes if Confirm is present
        if (!sPartyMenuInternal->chooseHalf)
        {
            if (animNum == 0)
            {
                // Disabled: SetBgTilemapPalette(1, 23, 17, 7, 2, 1);
            }
            else
            {
                // Disabled: SetBgTilemapPalette(1, 23, 17, 7, 2, 2);
            }
        }
        else if (animNum == 0)
        {
            // Disabled: SetBgTilemapPalette(1, 23, 18, 7, 2, 1);
        }
        else
        {
            // Disabled: SetBgTilemapPalette(1, 23, 18, 7, 2, 2);
        }
        spriteId = sPartyMenuInternal->spriteIdCancelPokeball;
        break;
    }
    PartyMenuStartSpriteAnim(spriteId, animNum);
    // Disabled: ScheduleBgCopyTilemapToVram(1);
}

static u8 GetPartyBoxPaletteFlags(u8 slot, u8 animNum)
{
    u8 palFlags = 0;

    if (animNum == 1)
        palFlags |= PARTY_PAL_SELECTED;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_HP) == 0)
        palFlags |= PARTY_PAL_FAINTED;
    if (PartyBoxPal_ParnterOrDisqualifiedInArena(slot) == TRUE)
        palFlags |= PARTY_PAL_MULTI_ALT;
    if ((gPartyMenu.action == PARTY_ACTION_SWITCH
         || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM)
        && slot == gPartyMenu.slotId)
        palFlags |= PARTY_PAL_SELECTED;
    if (gPartyMenu.action == PARTY_ACTION_FUSION)
    {
        if (slot == gPartyMenu.slotId)
            palFlags |= PARTY_PAL_TO_SWITCH;
    }
    if (gPartyMenu.action == PARTY_ACTION_SOFTBOILED && slot == gPartyMenu.slotId )
        palFlags |= PARTY_PAL_TO_SOFTBOIL;

    return palFlags;
}

static bool8 PartyBoxPal_ParnterOrDisqualifiedInArena(u8 slot)
{
    if (gPartyMenu.layout == PARTY_LAYOUT_MULTI && (slot == 1 || slot == 4 || slot == 5))
        return TRUE;

    if (slot < MULTI_PARTY_SIZE && (gBattleTypeFlags & BATTLE_TYPE_ARENA) && gMain.inBattle && (gBattleStruct->arenaLostPlayerMons >> GetPartyIdFromBattleSlot(slot) & 1))
        return TRUE;

    return FALSE;
}

bool8 IsMultiBattle(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_MULTI && IsDoubleBattle() && gMain.inBattle)
        return TRUE;
    else
        return FALSE;
}

static void SwapPartyPokemon(struct Pokemon *mon1, struct Pokemon *mon2)
{
    struct Pokemon *temp = Alloc(sizeof(struct Pokemon));

    *temp = *mon1;
    *mon1 = *mon2;
    *mon2 = *temp;

    Free(temp);
}

static void Task_ClosePartyMenu(u8 taskId)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_ClosePartyMenuAndSetCB2;
}

static void Task_ClosePartyMenuAndSetCB2(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (gPartyMenu.menuType == PARTY_MENU_TYPE_IN_BATTLE)
            UpdatePartyToFieldOrder();

        if (sPartyMenuInternal->exitCallback != NULL)
            SetMainCallback2(sPartyMenuInternal->exitCallback);
        else
            SetMainCallback2(gPartyMenu.exitCallback);

        ResetSpriteData();
        FreePartyPointers();
        DestroyTask(taskId);
    }
}

// Save states to recreate the party menu when exiting PC storage
static void SavePartyMenuStateForPC(void)
{
    sSavedPartyMenuType = gPartyMenu.menuType;
    sSavedPartyLayout = gPartyMenu.layout;
    sSavedPartyAction = gPartyMenu.action;
    sSavedPartySlotId = 0;
    sSavedPartyMessageId = PARTY_MSG_NONE;
    sSavedPartyTask = Task_HandleChooseMonInput;
    sSavedPartyExitCallback = gPartyMenu.exitCallback;
}

static void CB2_ReopenPartyMenuFromPC(void)
{
    if (sSavedPartyTask == NULL)
        sSavedPartyTask = Task_HandleChooseMonInput;
    if (sSavedPartyExitCallback == NULL)
        sSavedPartyExitCallback = CB2_ReturnToField;
    if (sSavedPartySlotId > PARTY_SIZE)
        sSavedPartySlotId = 0;
    gPartyMenu.slotId = sSavedPartySlotId;

    InitPartyMenu(sSavedPartyMenuType, sSavedPartyLayout, sSavedPartyAction, TRUE, sSavedPartyMessageId, sSavedPartyTask, sSavedPartyExitCallback);
}

u8 GetCursorSelectionMonId(void)
{
    return gPartyMenu.slotId;
}

u8 GetPartyMenuType(void)
{
    return gPartyMenu.menuType;
}

void Task_HandleChooseMonInput(u8 taskId)
{
    if (!gPaletteFade.active && MenuHelpers_ShouldWaitForLinkRecv() != TRUE)
    {
        s8 *slotPtr = GetCurrentPartySlotPtr();

        switch (PartyMenuButtonHandler(slotPtr))
        {
        case A_BUTTON: // Selected mon
            HandleChooseMonSelection(taskId, slotPtr);
            break;
        case B_BUTTON: // Selected Cancel / pressed B
            HandleChooseMonCancel(taskId, slotPtr);
            break;
        case START_BUTTON:
            if (sPartyMenuInternal->chooseHalf && IsBattleEntrySelectionComplete())
            {
                PlaySE(SE_SELECT);
                gPartyMenu.task(taskId);
            }
            break;
        case L_BUTTON: // Switch mon
        {
            struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
            u8 actionsType = GetPartyMenuActionsType(mon);

            if (gPartyMenu.action == PARTY_ACTION_SWITCH)
            {
                HandleChooseMonSelection(taskId, slotPtr);
                break;
            }
            if (actionsType == ACTIONS_SWITCH
                || (actionsType == ACTIONS_NONE
                    && !InBattlePike()
                    && GetMonData(&gPlayerParty[1], MON_DATA_SPECIES) != SPECIES_NONE))
            {
                CursorCb_Switch(taskId);
            }
            break;
        }
        case R_BUTTON:
            if (SWSH_PARTY_MENU_PC_ACCESS
                && gPartyMenu.action == PARTY_ACTION_CHOOSE_MON
                && gPartyMenu.layout == PARTY_LAYOUT_SINGLE
                && (gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD
                    || gPartyMenu.menuType == PARTY_MENU_TYPE_DAYCARE))
            {
                PlaySE(SE_SELECT);
                SavePartyMenuStateForPC();
                PokemonPC_SetReturnToPartyCallback(CB2_ReopenPartyMenuFromPC);
                sPartyMenuInternal->exitCallback = CB2_ShowPokemonPCFromParty;
                PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
                Task_ClosePartyMenu(taskId);
            }
            break;
        }
    }
}

static s8 *GetCurrentPartySlotPtr(void)
{
    if (gPartyMenu.action == PARTY_ACTION_SWITCH
        || gPartyMenu.action == PARTY_ACTION_SOFTBOILED
        || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM
        || gPartyMenu.action == PARTY_ACTION_FUSION)
        return &gPartyMenu.slotId2;
    else
        return &gPartyMenu.slotId;
}

static void Task_HandleSendMonToBoxYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        PlaySE(SE_SELECT);
        gSelectedMonPartyId = GetPartyIdFromBattleSlot(gPartyMenu.slotId);
        Task_ClosePartyMenu(taskId);
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
    case 1:
        Task_ReturnToChooseMonAfterText(taskId);
        break;
    }
}

static void Task_SendMonToBoxYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleSendMonToBoxYesNoInput;
    }
}

static void HandleChooseMonSelection(u8 taskId, s8 *slotPtr)
{
    if (*slotPtr == PARTY_SIZE)
    {
        gPartyMenu.task(taskId);
    }
    else
    {
        switch (gPartyMenu.action)
        {
        case PARTY_ACTION_SOFTBOILED:
            if (IsSelectedMonNotEgg((u8 *)slotPtr))
            {
                PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
                CreateSelectFrame(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId); // TODO: review why this doesn't work
                Task_TryUseSoftboiledOnPartyMon(taskId);
            }
            break;
        case PARTY_ACTION_USE_ITEM:
        case PARTY_ACTION_FUSION:
            if (IsSelectedMonNotEgg((u8 *)slotPtr))
            {
                if (gPartyMenu.menuType == PARTY_MENU_TYPE_IN_BATTLE)
                    sPartyMenuInternal->exitCallback = CB2_SetUpExitToBattleScreen;

                PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
                gItemUseCB(taskId, Task_ClosePartyMenuAfterText);
            }
            break;
        case PARTY_ACTION_MOVE_TUTOR:
            if (IsSelectedMonNotEgg((u8 *)slotPtr))
            {
                PlaySE(SE_SELECT);
                PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
                TryTutorSelectedMon(taskId);
            }
            break;
        case PARTY_ACTION_GIVE_MAILBOX_MAIL:
            if (IsSelectedMonNotEgg((u8 *)slotPtr))
            {
                PlaySE(SE_SELECT);
                PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
                TryGiveMailToSelectedMon(taskId);
            }
            break;
        case PARTY_ACTION_GIVE_ITEM:
        case PARTY_ACTION_GIVE_PC_ITEM:
            if (IsSelectedMonNotEgg((u8 *)slotPtr))
            {
                PlaySE(SE_SELECT);
                PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
                TryGiveItemOrMailToSelectedMon(taskId);
            }
            break;
        case PARTY_ACTION_SWITCH:
            PlaySE(SE_SELECT);
            SwitchSelectedMons(taskId);
            break;
        case PARTY_ACTION_CHOOSE_AND_CLOSE:
            PlaySE(SE_SELECT);
            Task_ClosePartyMenu(taskId);
            break;
        case PARTY_ACTION_MINIGAME:
            if (IsSelectedMonNotEgg((u8 *)slotPtr))
            {
                TryEnterMonForMinigame(taskId, (u8)*slotPtr);
            }
            break;
        case PARTY_ACTION_CHOOSE_FAINTED_MON:
        {
            u8 partyId = GetPartyIdFromBattleSlot((u8)*slotPtr);
            if (GetMonData(&gPlayerParty[*slotPtr], MON_DATA_HP) > 0
                || GetMonData(&gPlayerParty[*slotPtr], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG
                || ((gBattleTypeFlags & BATTLE_TYPE_MULTI) && partyId >= (PARTY_SIZE / 2)))
            {
                // Can't select if egg, alive, or doesn't belong to you
                PlaySE(SE_FAILURE);
            }
            else
            {
                PlaySE(SE_SELECT);
                gSelectedMonPartyId = partyId;
                Task_ClosePartyMenu(taskId);
            }
            break;
        }
        case PARTY_ACTION_SEND_MON_TO_BOX:
        {
            u8 partyId = (u8)*slotPtr;
            if ((gBattleTypeFlags & BATTLE_TYPE_MULTI) && partyId >= (PARTY_SIZE / 2))
            {
                // Can't select if mon doesn't belong to you
                PlaySE(SE_FAILURE);
                DisplayPartyMenuMessage(sText_CannotSendMonToBoxPartner, FALSE);
                ScheduleBgCopyTilemapToVram(2);
                gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
            }
            /*else if (DoesSelectedMonKnowHM((u8 *)slotPtr))
            {
                PlaySE(SE_FAILURE);
                DisplayPartyMenuMessage(sText_CannotSendMonToBoxHM, FALSE);
                ScheduleBgCopyTilemapToVram(2);
                gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
            }*/
            else
            {
                PlaySE(SE_SELECT);
                GetMonNickname(&gPlayerParty[partyId], gStringVar1);
                StringExpandPlaceholders(gStringVar4, sText_SendThisMonToPC);
                DisplayPartyMenuMessage(gStringVar4, TRUE);
                ScheduleBgCopyTilemapToVram(2);
                gTasks[taskId].func = Task_SendMonToBoxYesNo;
            }
            break;
        }
        default:
        case PARTY_ACTION_ABILITY_PREVENTS:
        case PARTY_ACTION_SWITCHING:
            PlaySE(SE_SELECT);
            Task_TryCreateSelectionWindow(taskId);
            break;
        }
    }
}

static bool8 IsSelectedMonNotEgg(u8 *slotPtr)
{
    if (GetMonData(&gPlayerParty[*slotPtr], MON_DATA_IS_EGG) == TRUE)
    {
        PlaySE(SE_FAILURE);
        return FALSE;
    }
    return TRUE;
}

static bool8 UNUSED DoesSelectedMonKnowHM(u8 *slotPtr)
{
    if (B_CATCH_SWAP_CHECK_HMS == FALSE)
        return FALSE;

    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        if (IsMoveHM(GetMonData(&gPlayerParty[*slotPtr], MON_DATA_MOVE1 + i)))
            return TRUE;
    }
    return FALSE;
}

static void HandleChooseMonCancel(u8 taskId, s8 *slotPtr)
{
    switch (gPartyMenu.action)
    {
    case PARTY_ACTION_SEND_OUT:
    case PARTY_ACTION_CHOOSE_FAINTED_MON:
        PlaySE(SE_FAILURE);
        break;
    case PARTY_ACTION_SWITCH:
    case PARTY_ACTION_SOFTBOILED:
    case PARTY_ACTION_MOVE_ITEM:
    case PARTY_ACTION_FUSION:
        PlaySE(SE_SELECT);
        DestroySelectFrame();
        FinishTwoMonAction(taskId);
        break;
    case PARTY_ACTION_MINIGAME:
        PlaySE(SE_SELECT);
        CancelParticipationPrompt(taskId);
        break;
    case PARTY_ACTION_SEND_MON_TO_BOX:
        PlaySE(SE_SELECT);
        gSelectedMonPartyId = PARTY_SIZE + 1;
        Task_ClosePartyMenu(taskId);
        break;
    default:
        PlaySE(SE_SELECT);
        if (DisplayCancelChooseMonYesNo(taskId) != TRUE)
        {
            if (!MenuHelpers_IsLinkActive())
                gSpecialVar_0x8004 = PARTY_SIZE + 1;
            gPartyMenuUseExitCallback = FALSE;
            *slotPtr = PARTY_SIZE + 1;
            Task_ClosePartyMenu(taskId);
        }
        break;
    }
}

static bool8 DisplayCancelChooseMonYesNo(u8 taskId)
{
    const u8 *stringPtr = NULL;

    if (gPartyMenu.menuType == PARTY_MENU_TYPE_CONTEST)
        stringPtr = gText_CancelParticipation;
    else if (gPartyMenu.menuType == PARTY_MENU_TYPE_CHOOSE_HALF)
        stringPtr = GetFacilityCancelString();

    if (stringPtr == NULL)
        return FALSE;

    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    StringExpandPlaceholders(gStringVar4, stringPtr);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_CancelChooseMonYesNo;
    return TRUE;
}

static void Task_CancelChooseMonYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleCancelChooseMonYesNoInput;
    }
}

static void Task_HandleCancelChooseMonYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        gPartyMenuUseExitCallback = FALSE;
        gPartyMenu.slotId = PARTY_SIZE + 1;
        ClearSelectedPartyOrder();
        Task_ClosePartyMenu(taskId);
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        Task_ReturnToChooseMonAfterText(taskId);
        break;
    }
}

static u16 PartyMenuButtonHandler(s8 *slotPtr)
{
    s8 movementDir;

    switch (gMain.newAndRepeatedKeys)
    {
    case DPAD_UP:
        movementDir = MENU_DIR_UP;
        break;
    case DPAD_DOWN:
        movementDir = MENU_DIR_DOWN;
        break;
    case DPAD_LEFT:
        movementDir = MENU_DIR_LEFT;
        break;
    case DPAD_RIGHT:
        movementDir = MENU_DIR_RIGHT;
        break;
    default:
        movementDir = 0;
        break;
    }
    if (gSaveBlock2Ptr->optionsButtonMode != OPTIONS_BUTTON_MODE_L_EQUALS_A && JOY_NEW(L_BUTTON))
        return L_BUTTON;

    if (JOY_NEW(R_BUTTON))
        return R_BUTTON;

    if (JOY_NEW(START_BUTTON))
        return START_BUTTON;

    if (JOY_NEW(SELECT_BUTTON))
        return SELECT_BUTTON;

    if (movementDir && gPlayerPartyCount != 0)
    {
        UpdateCurrentPartySelection(slotPtr, movementDir);
        return 0;
    }

    // Pressed Cancel
    // if (JOY_NEW(A_BUTTON) && *slotPtr == PARTY_SIZE + 1)
    //     return B_BUTTON;

    return JOY_NEW(A_BUTTON | B_BUTTON);
}


static void UpdatePartyMonSprite(u8 slotId)
{
    s16 state;
    u8 spriteId;

    if (!ShouldShowBattleDetails()
        && gPartyMenu.menuType != PARTY_MENU_TYPE_MULTI_SHOWCASE
        && slotId < gPlayerPartyCount
        && GetMonData(&gPlayerParty[slotId], MON_DATA_SPECIES) != SPECIES_NONE)
    {
        DestroyMonSprite();
        state = 0;
        do
        {
            spriteId = LoadMonGfxAndSprite(&gPlayerParty[slotId], &state, TRUE);
        } while (spriteId == 0xFF);
        sMonShadowSpriteId = spriteId;

        state = 0;
        do
        {
            spriteId = LoadMonGfxAndSprite(&gPlayerParty[slotId], &state, FALSE);
        } while (spriteId == 0xFF);
        sMonSpriteId = spriteId;
        UpdateSelectedMonItemSprite();
    }
    else
    {
        DestroyMonSprite();
    }
}

static void UpdateCurrentPartySelection(s8 *slotPtr, s8 movementDir)
{
    s8 newSlotId = *slotPtr;
    u8 layout = gPartyMenu.layout;

    if (layout == PARTY_LAYOUT_SINGLE)
        UpdatePartySelectionSingleLayout(slotPtr, movementDir);
    else
        UpdatePartySelectionDoubleLayout(slotPtr, movementDir);

    if (*slotPtr != newSlotId)
    {
        PlaySE(SE_SELECT);
        AnimatePartySlot(newSlotId, 0);
        AnimatePartySlot(*slotPtr, 1);
        CreateHoverSprite(&sPartyMenuBoxes[*slotPtr], *slotPtr);
        if (ShouldShowBattleDetails())
            UpdatePartyMoveWindows(*slotPtr);

        UpdatePartyMonSprite(*slotPtr);
    }
}

static bool8 ShouldOffsetPartySlot(u8 slot)
{
    return !ShouldShowBattleDetails()
        && gPartyMenu.menuType != PARTY_MENU_TYPE_MULTI_SHOWCASE
        && gPartyMenu.slotId == slot
        && slot < gPlayerPartyCount
        && GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES) != SPECIES_NONE;
}

static void StartPartySlotAnimation(struct ComfyAnim *anim, s32 from, s32 to)
{
    struct ComfyAnimEasingConfig config;

    InitComfyAnimConfig_Easing(&config);
    config.durationFrames = SWSH_PARTY_SLOT_ANIM_DURATION_FRAMES;
    config.from = from;
    config.to = to;
    config.easingFunc = ComfyAnimEasing_EaseOutCubic;
    InitComfyAnim_Easing(&config, anim);
}

static void InitPartySlotAnimations(void)
{
    u8 slot;

    for (slot = 0; slot < PARTY_SIZE; slot++)
    {
        s32 target = ShouldOffsetPartySlot(slot) ? -Q_24_8(SWSH_PARTY_SELECTED_SLOT_X_OFFSET) : 0;

        sPartyMenuInternal->slotSpriteOffsets[slot] = 0;
        StartPartySlotAnimation(&sPartyMenuInternal->slotAnims[slot], 0, target);
    }

    sPartyMenuInternal->offsetCursorSpriteId = MAX_SPRITES;
    sPartyMenuInternal->cursorSpriteOffset = 0;
}

static void InitPartySlotScanlineEffect(void)
{
    struct ScanlineEffectParams params;

    ScanlineEffect_Clear();
    params.dmaDest = &REG_BG0HOFS;
    params.dmaControl = SCANLINE_EFFECT_DMACNT_16BIT;
    params.initState = 1;
    params.unused9 = 0;
    ScanlineEffect_SetParams(params);
}

static void OffsetSpriteX(u8 spriteId, s16 offset)
{
    if (spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
        gSprites[spriteId].x2 += offset;
}

static void OffsetPartyMenuBoxSprites(struct PartyMenuBox *menuBox, s16 offset)
{
    OffsetSpriteX(menuBox->pokeballSpriteId, offset);
    OffsetSpriteX(menuBox->itemSpriteId, offset);
    OffsetSpriteX(menuBox->monSpriteId, offset);
    OffsetSpriteX(menuBox->statusSpriteId, offset);
}

static void ApplyPartySlotOffsetToSprite(struct PartyMenuBox *menuBox, u8 spriteId)
{
    u8 slot;

    if (sPartyMenuInternal == NULL || sPartyMenuBoxes == NULL)
        return;

    slot = menuBox - sPartyMenuBoxes;
    if (slot < PARTY_SIZE)
        OffsetSpriteX(spriteId, sPartyMenuInternal->slotSpriteOffsets[slot]);
}

static void UpdatePartySlotAnimations(void)
{
    u8 slot;
    u8 cursorSpriteId = MAX_SPRITES;
    u16 *scanlineBuffer;

    if (sPartyMenuInternal == NULL || sPartyMenuBoxes == NULL)
        return;

    scanlineBuffer = gScanlineEffectRegBuffers[gScanlineEffect.srcBuffer];

    CpuFill16(0, scanlineBuffer, DISPLAY_HEIGHT * sizeof(*scanlineBuffer));

    for (slot = 0; slot < PARTY_SIZE; slot++)
    {
        s16 xOffset;
        s16 spriteDelta;
        s32 target = ShouldOffsetPartySlot(slot) ? -Q_24_8(SWSH_PARTY_SELECTED_SLOT_X_OFFSET) : 0;
        struct ComfyAnim *anim = &sPartyMenuInternal->slotAnims[slot];

        if (anim->config.type != COMFY_ANIM_TYPE_EASING || anim->config.data.easing.to != target)
            StartPartySlotAnimation(anim, anim->position, target);

        TryAdvanceComfyAnim(anim);
        xOffset = ReadComfyAnimValueSmooth(anim);
        spriteDelta = xOffset - sPartyMenuInternal->slotSpriteOffsets[slot];
        if (spriteDelta != 0)
            OffsetPartyMenuBoxSprites(&sPartyMenuBoxes[slot], spriteDelta);
        sPartyMenuInternal->slotSpriteOffsets[slot] = xOffset;

        if (GetWindowAttribute(sPartyMenuBoxes[slot].windowId, WINDOW_BG) == 0)
        {
            u8 y;
            u8 top = GetWindowAttribute(sPartyMenuBoxes[slot].windowId, WINDOW_TILEMAP_TOP) * TILE_WIDTH;
            u8 bottom = min(top + GetWindowAttribute(sPartyMenuBoxes[slot].windowId, WINDOW_HEIGHT) * TILE_HEIGHT, DISPLAY_HEIGHT);

            for (y = top; y < bottom; y++)
                scanlineBuffer[y] = -xOffset;
        }
    }

    if (sHoverCursorSpriteId < MAX_SPRITES && gSprites[sHoverCursorSpriteId].inUse)
        cursorSpriteId = sHoverCursorSpriteId;
    else if (sItemIconSpriteId < MAX_SPRITES && gSprites[sItemIconSpriteId].inUse)
        cursorSpriteId = sItemIconSpriteId;

    if (cursorSpriteId != MAX_SPRITES)
    {
        s16 target = (gPartyMenu.slotId < PARTY_SIZE) ? -SWSH_PARTY_SELECTED_SLOT_X_OFFSET : 0;

        if (sPartyMenuInternal->offsetCursorSpriteId != cursorSpriteId)
        {
            sPartyMenuInternal->offsetCursorSpriteId = cursorSpriteId;
            sPartyMenuInternal->cursorSpriteOffset = 0;
        }
        OffsetSpriteX(cursorSpriteId, target - sPartyMenuInternal->cursorSpriteOffset);
        sPartyMenuInternal->cursorSpriteOffset = target;
    }
    else
    {
        sPartyMenuInternal->offsetCursorSpriteId = MAX_SPRITES;
        sPartyMenuInternal->cursorSpriteOffset = 0;
    }
}

static void UpdatePartySelectionSingleLayout(s8 *slotPtr, s8 movementDir)
{
    // PARTY_SIZE + 1 is Cancel, PARTY_SIZE is Confirm
    switch (movementDir)
    {
    case MENU_DIR_UP:
        if (*slotPtr == 0)
        {
            // *slotPtr = PARTY_SIZE + 1;
            *slotPtr = gPlayerPartyCount - 1; // Disable cursor going to Cancel
        }
        else if (*slotPtr == PARTY_SIZE)
        {
            *slotPtr = gPlayerPartyCount - 1;
        }
        else if (*slotPtr == PARTY_SIZE + 1)
        {
            // // Disable cursor going to Cancel
            //  if (sPartyMenuInternal->chooseHalf)
            //     *slotPtr = PARTY_SIZE;
            // else
            *slotPtr = gPlayerPartyCount - 1;
        }
        else
        {
            (*slotPtr)--;
        }
        break;
    case MENU_DIR_DOWN:
        if (*slotPtr == PARTY_SIZE + 1)
        {
            *slotPtr = 0;
        }
        else
        {
            if (*slotPtr == gPlayerPartyCount - 1)
            {
                *slotPtr = 0;
            }
            else
            {
                (*slotPtr)++;
            }
        }
        break;
    }
}

static void UpdatePartySelectionDoubleLayout(s8 *slotPtr, s8 movementDir)
{
    // PARTY_SIZE + 1 is Cancel, PARTY_SIZE is Confirm
    // newSlot is used temporarily as a movement direction during its later assignment
    s8 newSlot = movementDir;

    switch (movementDir)
    {
    case MENU_DIR_UP:
        if (*slotPtr == 0)
        {
            // *slotPtr = PARTY_SIZE + 1; // Disable cursor going to Cancel
            *slotPtr = gPlayerPartyCount - 1;
            break;
        }
        else if (*slotPtr == PARTY_SIZE)
        {
            *slotPtr = gPlayerPartyCount - 1;
            break;
        }
        else if (*slotPtr == PARTY_SIZE + 1)
        {
            // if (sPartyMenuInternal->chooseHalf) // Disable cursor going to Cancel
            // {
            //     *slotPtr = PARTY_SIZE;
            //     break;
            // }
            // (*slotPtr)--;
            *slotPtr = gPlayerPartyCount - 1;
            break;
        }
        newSlot = GetNewSlotDoubleLayout(*slotPtr, newSlot);
        if (newSlot != -1)
            *slotPtr = newSlot;
        break;
    case MENU_DIR_DOWN:
        if (*slotPtr == PARTY_SIZE)
        {
            // *slotPtr = PARTY_SIZE + 1; // Disable cursor going to Cancel
            *slotPtr = 0;
        }
        else if (*slotPtr == PARTY_SIZE + 1)
        {
            *slotPtr = 0;
        }
        else
        {
            newSlot = GetNewSlotDoubleLayout(*slotPtr, MENU_DIR_DOWN);
            if (newSlot == -1)
            {
                // if (sPartyMenuInternal->chooseHalf) // Disable cursor going to Cancel
                //     *slotPtr = PARTY_SIZE;
                // else
                //     *slotPtr = PARTY_SIZE + 1;
                *slotPtr = 0;
            }
            else
            {
                *slotPtr = newSlot;
            }
        }
        break;
    }
}

static s8 GetNewSlotDoubleLayout(s8 slotId, s8 movementDir)
{
    while (TRUE)
    {
        slotId += movementDir;
        if ((u8)slotId >= PARTY_SIZE)
            return -1;
        if (GetMonData(&gPlayerParty[slotId], MON_DATA_SPECIES) != SPECIES_NONE)
            return slotId;
    }
}

u8 *GetMonNickname(struct Pokemon *mon, u8 *dest)
{
    if (GetMonData(mon, MON_DATA_IS_EGG))
    {
        StringCopy(dest, sText_EggNickname);
        return dest;
    }
    else
    {
        GetMonData(mon, MON_DATA_NICKNAME, dest);
        return StringGet_Nickname(dest);
    }
}

#define tKeepOpen  data[0]

u8 DisplayPartyMenuMessage(const u8 *str, bool8 keepOpen)
{
    u8 taskId;

    PrintMessage(str);
    taskId = CreateTask(Task_PrintAndWaitForText, 1);
    gTasks[taskId].tKeepOpen = keepOpen;
    return taskId;
}

static void Task_PrintAndWaitForText(u8 taskId)
{
    if (RunTextPrintersRetIsActive(WIN_MSG) != TRUE)
    {
        if (gTasks[taskId].tKeepOpen == FALSE)
        {
            ClearStdWindowAndFrameToTransparent(WIN_MSG, FALSE);
            ClearWindowTilemap(WIN_MSG);
            DestroyMessageWindowSprite();
            ScheduleBgCopyTilemapToVram(2);
        }
        DestroyTask(taskId);
    }
}

#undef tKeepOpen

bool8 IsPartyMenuTextPrinterActive(void)
{
    return FuncIsActiveTask(Task_PrintAndWaitForText);
}

static void Task_WaitForLinkAndReturnToChooseMon(u8 taskId)
{
    if (MenuHelpers_ShouldWaitForLinkRecv() != TRUE)
    {
        gTasks[taskId].func = Task_HandleChooseMonInput;
    }
}

static void Task_ReturnToChooseMonAfterText(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        ClearStdWindowAndFrameToTransparent(WIN_MSG, FALSE);
        ClearWindowTilemap(WIN_MSG);
        DestroyMessageWindowSprite();
        ScheduleBgCopyTilemapToVram(2);
        {
            u8 promptType = GetButtonPromptType();
            if (promptType != BUTTON_PROMPT_NONE
                && sPartyMenuInternal != NULL
                && sPartyMenuInternal->promptWindowId != WINDOW_NONE)
            {
                ShowButtonPrompt(promptType);
                PutWindowTilemap(sPartyMenuInternal->promptWindowId);
                ScheduleBgCopyTilemapToVram(0);
            }
        }
        if (MenuHelpers_IsLinkActive() == TRUE)
        {
            gTasks[taskId].func = Task_WaitForLinkAndReturnToChooseMon;
        }
        else
        {
            gTasks[taskId].func = Task_HandleChooseMonInput;
        }
    }
}

static void DisplayGaveHeldItemMessage(struct Pokemon *mon, enum Item item, bool8 keepOpen, u8 unused)
{
    GetMonNickname(mon, gStringVar1);
    CopyItemName(item, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gText_PkmnWasGivenItem);
    DisplayPartyMenuMessage(gStringVar4, keepOpen);
    ScheduleBgCopyTilemapToVram(2);
}

static void DisplayTookHeldItemMessage(struct Pokemon *mon, enum Item item, bool8 keepOpen)
{
    GetMonNickname(mon, gStringVar1);
    CopyItemName(item, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gText_ReceivedItemFromPkmn);
    DisplayPartyMenuMessage(gStringVar4, keepOpen);
    ScheduleBgCopyTilemapToVram(2);
}

static void DisplayAlreadyHoldingItemSwitchMessage(struct Pokemon *mon, enum Item item, bool8 keepOpen)
{
    GetMonNickname(mon, gStringVar1);
    CopyItemName(item, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gText_PkmnAlreadyHoldingItemSwitch);
    DisplayPartyMenuMessage(gStringVar4, keepOpen);
    ScheduleBgCopyTilemapToVram(2);
}

static void DisplaySwitchedHeldItemMessage(enum Item item, enum Item item2, bool8 keepOpen)
{
    CopyItemName(item, gStringVar1);
    CopyItemName(item2, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gText_SwitchedPkmnItem);
    DisplayPartyMenuMessage(gStringVar4, keepOpen);
    ScheduleBgCopyTilemapToVram(2);
}

static void GiveItemToMon(struct Pokemon *mon, enum Item item)
{
    u8 itemBytes[2];

    if (ItemIsMail(item) == TRUE)
    {
        if (GiveMailToMonByItemId(mon, item) == MAIL_NONE)
            return;
    }
    itemBytes[0] = item;
    itemBytes[1] = item >> 8;
    SetMonData(mon, MON_DATA_HELD_ITEM, itemBytes);
    TryItemHoldFormChange(&gPlayerParty[gPartyMenu.slotId], gPartyMenu.slotId);
}

static u8 TryTakeMonItem(struct Pokemon *mon)
{
    enum Item item = GetMonData(mon, MON_DATA_HELD_ITEM);

    if (item == ITEM_NONE)
        return 0;
    if (AddHeldItemToBag(item) == FALSE)
        return 1;

    item = ITEM_NONE;
    SetMonData(mon, MON_DATA_HELD_ITEM, &item);
    TryItemHoldFormChange(&gPlayerParty[gPartyMenu.slotId], gPartyMenu.slotId);
    return 2;
}

static void BufferBagFullCantTakeItemMessage(u16 itemUnused)
{
    StringExpandPlaceholders(gStringVar4, gText_BagFullCouldNotRemoveItem);
}

#define tHP           data[0]
#define tMaxHP        data[1]
#define tHPIncrement  data[2]
#define tHPToAdd      data[3]
#define tPartyId      data[4]
#define tStartHP      data[5]

static void Task_PartyMenuModifyHP(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    tHP += tHPIncrement;
    tHPToAdd--;
    SetMonData(&gPlayerParty[tPartyId], MON_DATA_HP, &tHP);
    DisplayPartyPokemonHPCheck(&gPlayerParty[tPartyId], &sPartyMenuBoxes[tPartyId], 1);
    DisplayPartyPokemonHPBarCheck(&gPlayerParty[tPartyId], &sPartyMenuBoxes[tPartyId]);
    if (tHPToAdd == 0 || tHP == 0 || tHP == tMaxHP)
    {
        // If HP was recovered, buffer the amount recovered
        if (tHP > tStartHP)
            ConvertIntToDecimalStringN(gStringVar2, tHP - tStartHP, STR_CONV_MODE_LEFT_ALIGN, 3);

        SwitchTaskToFollowupFunc(taskId);

        // Handle destroying selection frame during Soft-boiled
        if (gPartyMenu.action == PARTY_ACTION_SOFTBOILED)
            DestroySelectFrame();
    }
}

void PartyMenuModifyHP(u8 taskId, u8 slot, s8 hpIncrement, s16 hpDifference, TaskFunc task)
{
    struct Pokemon *mon = &gPlayerParty[slot];
    s16 *data = gTasks[taskId].data;

    tHP = GetMonData(mon, MON_DATA_HP);
    tMaxHP = GetMonData(mon, MON_DATA_MAX_HP);
    tHPIncrement = hpIncrement;
    tHPToAdd = hpDifference;
    tPartyId = slot;
    tStartHP = tHP;
    SetTaskFuncWithFollowupFunc(taskId, Task_PartyMenuModifyHP, task);
}

// The usage of hp in this function is mostly nonsense
// Because caseId is always passed 0, none of the other cases ever occur
static void ResetHPTaskData(u8 taskId, u8 caseId, u32 hp)
{
    s16 *data = gTasks[taskId].data;

    switch (caseId) // always zero
    {
    case 0:
        tHP = hp;
        tStartHP = hp;
        break;
    case 1:
        tMaxHP = hp;
        break;
    case 2:
        tHPIncrement = hp;
        break;
    case 3:
        tHPToAdd = hp;
        break;
    case 4:
        tPartyId = hp;
        break;
    case 5:
        SetTaskFuncWithFollowupFunc(taskId, Task_PartyMenuModifyHP, (TaskFunc)hp); // >casting hp as a taskfunc
        break;
    }
}

#undef tHP
#undef tMaxHP
#undef tHPIncrement
#undef tHPToAdd
#undef tPartyId
#undef tStartHP

u8 GetAilmentFromStatus(u32 status)
{
    if (status & STATUS1_PSN_ANY)
        return AILMENT_PSN;
    if (status & STATUS1_PARALYSIS)
        return AILMENT_PRZ;
    if (status & STATUS1_SLEEP)
        return AILMENT_SLP;
    if (status & STATUS1_FREEZE)
        return AILMENT_FRZ;
    if (status & STATUS1_BURN)
        return AILMENT_BRN;
    if (status & STATUS1_FROSTBITE)
        return AILMENT_FRB;
    return AILMENT_NONE;
}

u8 GetMonAilment(struct Pokemon *mon)
{
    u8 ailment;

    if (GetMonData(mon, MON_DATA_HP) == 0)
        return AILMENT_FNT;
    ailment = GetAilmentFromStatus(GetMonData(mon, MON_DATA_STATUS));
    if (ailment != AILMENT_NONE)
        return ailment;
    if (ShouldPokemonShowActivePokerus(mon))
        return AILMENT_PKRS;
    return AILMENT_NONE;
}

static void SetPartyMonsAllowedInMinigame(void)
{
    s16 *ptr;

    if (gPartyMenu.menuType == PARTY_MENU_TYPE_MINIGAME)
    {
        u8 i;

        ptr = &gPartyMenu.data1;
        gPartyMenu.data1 = 0;
        if (gSpecialVar_0x8005 == 0)
        {
            for (i = 0; i < gPlayerPartyCount; i++)
                *ptr += IsMonAllowedInPokemonJump(&gPlayerParty[i]) << i;
        }
        else
        {
            for (i = 0; i < gPlayerPartyCount; i++)
                *ptr += IsMonAllowedInDodrioBerryPicking(&gPlayerParty[i]) << i;
        }
    }
}

static bool16 IsMonAllowedInPokemonJump(struct Pokemon *mon)
{
    if (GetMonData(mon, MON_DATA_IS_EGG) != TRUE && IsSpeciesAllowedInPokemonJump(GetMonData(mon, MON_DATA_SPECIES)))
        return TRUE;
    return FALSE;
}


static bool16 IsMonAllowedInDodrioBerryPicking(struct Pokemon *mon)
{
    if (GetMonData(mon, MON_DATA_IS_EGG) != TRUE && GetMonData(mon, MON_DATA_SPECIES) == SPECIES_DODRIO)
        return TRUE;
    return FALSE;
}

static bool8 IsMonAllowedInMinigame(u8 slot)
{
    if (!((gPartyMenu.data1 >> slot) & 1))
        return FALSE;
    return TRUE;
}

static void TryEnterMonForMinigame(u8 taskId, u8 slot)
{
    if (IsMonAllowedInMinigame(slot) == TRUE)
    {
        PlaySE(SE_SELECT);
        gSpecialVar_0x8004 = slot;
        Task_ClosePartyMenu(taskId);
    }
    else
    {
        PlaySE(SE_FAILURE);
        DisplayPartyMenuMessage(gText_PkmnCantParticipate, FALSE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    }
}

static void CancelParticipationPrompt(u8 taskId)
{
    DisplayPartyMenuMessage(gText_CancelParticipation, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_CancelParticipationYesNo;
}

static void Task_CancelParticipationYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleCancelParticipationYesNoInput;
    }
}

static void Task_HandleCancelParticipationYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        gSpecialVar_0x8004 = PARTY_SIZE + 1;
        Task_ClosePartyMenu(taskId);
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        break;
    }
}

static enum CanMoveBeLearned CanTeachMove(struct Pokemon *mon, enum Move move)
{
    if (GetMonData(mon, MON_DATA_IS_EGG))
        return CANNOT_LEARN_MOVE_IS_EGG;
    else if (!CanLearnTeachableMove(GetMonData(mon, MON_DATA_SPECIES_OR_EGG), move))
        return CANNOT_LEARN_MOVE;
    else if (MonKnowsMove(mon, move) == TRUE)
        return ALREADY_KNOWS_MOVE;
    else
        return CAN_LEARN_MOVE;
}

static void InitPartyMenuWindows(u8 layout)
{
    switch (layout)
    {
    case PARTY_LAYOUT_SINGLE:
        InitWindows(sSinglePartyMenuWindowTemplate_SwSh);
        break;
    case PARTY_LAYOUT_DOUBLE:
        InitWindows(sDoublePartyMenuWindowTemplate_SwSh);
        break;
    case PARTY_LAYOUT_MULTI:
        InitWindows(sMultiPartyMenuWindowTemplate_SwSh);
        break;
    default: // PARTY_LAYOUT_MULTI_SHOWCASE
        InitWindows(sShowcaseMultiPartyMenuWindowTemplate_SwSh);
        break;
    }
    LoadPartyMenuWindows();
}

static void LoadPartyMenuWindows(void)
{
    u32 i;
    DeactivateAllTextPrinters();
    for (i = 0; i < PARTY_SIZE; i++)
        FillWindowPixelBuffer(i, PIXEL_FILL(0));

    if (gPartyMenu.layout == PARTY_LAYOUT_SINGLE)
    {
        sPartyMenuInternal->promptWindowId = PARTY_LABEL_WINDOW_PROMPT;
        FillWindowPixelBuffer(PARTY_LABEL_WINDOW_PROMPT, PIXEL_FILL(0));
        CopyWindowToVram(PARTY_LABEL_WINDOW_PROMPT, COPYWIN_GFX);
    }
    else
    {
        sPartyMenuInternal->promptWindowId = WINDOW_NONE;
    }
    LoadUserWindowBorderGfx(0, 0x63, BG_PLTT_ID(13));
    LoadPalette(GetOverworldTextboxPalettePtr(), BG_PLTT_ID(14), PLTT_SIZE_4BPP);
    LoadPalette(gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
    ShowSelectedMonInfo();

    if (ShouldShowBattleDetails())
    {
        int i;
        for (i = 0; i < MAX_MON_MOVES; ++i)
        {
            sMoveWindowIds[i] = AddWindow(&sMoveInfoWindowTemplate_SwSh[i]);
            if (sMoveWindowIds[i] != WINDOW_NONE)
            {
                FillWindowPixelBuffer(sMoveWindowIds[i], PIXEL_FILL(0));
                PutWindowTilemap(sMoveWindowIds[i]);
                CopyWindowToVram(sMoveWindowIds[i], COPYWIN_GFX);
            }
        }
        sAbilityWindowId = AddWindow(&sAbilityInfoWindowTemplate);
        if (sAbilityWindowId != WINDOW_NONE)
        {
            PutWindowTilemap(sAbilityWindowId);
            DisplayPartyPokemonAbility(sAbilityWindowId, gPartyMenu.slotId);
        }
    }
}

static void PrintButtonIcon(u8 windowId, u8 buttonType, u32 x, u32 y)
{
    static const struct {
        u8 width;
        u8 height;
    } sButtonDimensions[] = {
        [BUTTON_START]  = {32, 8},
        [BUTTON_SELECT] = {16, 8},
        [BUTTON_L]      = {16, 8},
        [BUTTON_R]      = {16, 8},
    };

    const u8 *button = NULL;
    u8 width = 0;
    u8 height = 0;

    if (buttonType <= BUTTON_R)
    {
        button = sButtons_Gfx[buttonType];
        width = sButtonDimensions[buttonType].width;
        height = sButtonDimensions[buttonType].height;
    }

    if (button == NULL || width == 0 || height == 0)
        return;

    BlitBitmapToWindow(windowId, button, x, y, width, height);
}

static void PrintTextOnWindowWithFont(u8 windowId, const u8 *string, u8 x, u8 y, u8 lineSpacing, u8 colorId, u32 fontId)
{
    AddTextPrinterParameterized4(windowId, fontId, x, y, 0, lineSpacing, sFontColorTable[colorId], 0, string);
}

static void PrintTextOnWindowToFit(u8 windowId, const u8 *string, u8 x, u8 y, u32 width, u8 colorId, u32 fontId)
{
    AddTextPrinterParameterized4(windowId, GetFontIdToFit(string, fontId, 0, width), x, y, 0, 0, sFontColorTable[colorId], 0, string);
}

static bool8 IsBattleEntrySelectionComplete(void)
{
    u8 i;
    u8 maxBattlers;

    if (sPartyMenuInternal == NULL || !sPartyMenuInternal->chooseHalf)
        return FALSE;

    maxBattlers = GetMaxBattleEntries();
    if (maxBattlers == 0)
        return FALSE;

    for (i = 0; i < maxBattlers; i++)
    {
        if (gSelectedOrderFromParty[i] == 0)
            return FALSE;
    }

    return TRUE;
}

static void ShowSelectedMonInfo(void)
{
    bool8 hasMon = FALSE;
    u8 slotId = gPartyMenu.slotId;

    if (gPartyMenu.action == PARTY_ACTION_SWITCH
        || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM)
        slotId = gPartyMenu.slotId2;

    if (sPartyTitleWindowId == WINDOW_NONE)
        sPartyTitleWindowId = AddWindow(&sPartyTitleWindowTemplate_SwSh);
    if (sSelectedMonHeldItemInfoWindowId == WINDOW_NONE)
        sSelectedMonHeldItemInfoWindowId = AddWindow(&sSelectedHeldItemInfoWindowTemplate_SwSh);

    if (sPartyTitleWindowId == WINDOW_NONE || sSelectedMonHeldItemInfoWindowId == WINDOW_NONE)
        return;

    FillWindowPixelBuffer(sPartyTitleWindowId, PIXEL_FILL(0));
    FillWindowPixelBuffer(sSelectedMonHeldItemInfoWindowId, PIXEL_FILL(0));

    if (slotId < gPlayerPartyCount
        && GetMonData(&gPlayerParty[slotId], MON_DATA_SPECIES) != SPECIES_NONE)
    {
        struct Pokemon *mon = &gPlayerParty[slotId];
        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        enum Item item = GetMonData(mon, MON_DATA_HELD_ITEM);

        if (GetMonData(mon, MON_DATA_IS_EGG))
            StringCopy(gStringVar1, sText_EggNickname);
        else
            StringCopy(gStringVar1, GetSpeciesName(GetMonData(mon, MON_DATA_SPECIES)));
        StringCopy(gStringVar2, gText_LevelSymbol);
        ConvertIntToDecimalStringN(gStringVar3, level, STR_CONV_MODE_LEFT_ALIGN, 3);
        StringAppend(gStringVar2, gStringVar3);

        if (item != ITEM_NONE)
            CopyItemName(item, gStringVar3);
        else
            StringCopy(gStringVar3, gText_None);

        hasMon = TRUE;
    }

    if (hasMon)
    {
        PrintTextOnWindowWithFont(sPartyTitleWindowId, gStringVar1, SWSH_PARTY_SPECIES_TEXT_X, SWSH_PARTY_SPECIES_TEXT_Y, 0, SWSH_PARTY_FONT_COLOR_LIGHT, FONT_NORMAL);
        PrintTextOnWindowWithFont(sPartyTitleWindowId, gStringVar2, SWSH_PARTY_LEVEL_TEXT_X, SWSH_PARTY_LEVEL_TEXT_Y, 0, SWSH_PARTY_FONT_COLOR_BLACK, FONT_SMALL);
        PrintTextOnWindowWithFont(sSelectedMonHeldItemInfoWindowId, sText_HeldItem, SWSH_PARTY_HELD_ITEM_LABEL_TEXT_X, SWSH_PARTY_HELD_ITEM_LABEL_TEXT_Y, 0, SWSH_PARTY_FONT_COLOR_LIGHT, FONT_SMALL);
        PrintTextOnWindowToFit(sSelectedMonHeldItemInfoWindowId, gStringVar3, SWSH_PARTY_HELD_ITEM_NAME_TEXT_X, SWSH_PARTY_HELD_ITEM_NAME_TEXT_Y, SWSH_PARTY_HELD_ITEM_INFO_WIDTH, SWSH_PARTY_FONT_COLOR_BLACK, FONT_NORMAL);
    }

    PutWindowTilemap(sPartyTitleWindowId);
    PutWindowTilemap(sSelectedMonHeldItemInfoWindowId);
    CopyWindowToVram(sPartyTitleWindowId, COPYWIN_GFX);
    CopyWindowToVram(sSelectedMonHeldItemInfoWindowId, COPYWIN_GFX);
    ScheduleBgCopyTilemapToVram(2);
    ScheduleBgCopyTilemapToVram(0);
}

static inline u8 GetButtonPromptType(void)
{
    if (SWSH_PARTY_MENU_PC_ACCESS
        && gPartyMenu.action == PARTY_ACTION_CHOOSE_MON
        && gPartyMenu.layout == PARTY_LAYOUT_SINGLE
        && (gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD
            || gPartyMenu.menuType == PARTY_MENU_TYPE_DAYCARE))
        return BUTTON_PROMPT_BOXES;

    return BUTTON_PROMPT_NONE;
}

static const struct {
    u8 iconType;
    u8 iconOffset;
    const u8 *text;
    u8 totalWidth;
} sPromptButtonInfo[] = {
    [BUTTON_PROMPT_NONE]    = {BUTTON_NONE,    0,              NULL,  0},
    [BUTTON_PROMPT_CONFIRM] = {BUTTON_START,  25, sMenuText_Confirm, 60},
    [BUTTON_PROMPT_SWITCH]  = {BUTTON_L,      15,  sMenuText_Switch, 45},
    [BUTTON_PROMPT_BOXES]   = {BUTTON_R,      15,   sMenuText_Boxes, 41},
};

static void ShowButtonPrompt(u8 type)
{
    if (type == BUTTON_PROMPT_NONE
        || sPartyMenuInternal == NULL
        || sPartyMenuInternal->promptWindowId == WINDOW_NONE)
        return;
    u8 promptWindowId = sPartyMenuInternal->promptWindowId;

    // Determine availability of SWITCH and BOXES prompts
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    bool8 canShowSwitch = FALSE;
    bool8 canShowBoxes = FALSE;
    u8 actionsType = GetPartyMenuActionsType(mon);
    if (gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_L_EQUALS_A)
    {
        canShowSwitch = FALSE;
    }
    else if (actionsType == ACTIONS_SWITCH)
    {
        canShowSwitch = TRUE;
    }
    else if (actionsType == ACTIONS_NONE
             && !InBattlePike()
             && GetMonData(&gPlayerParty[1], MON_DATA_SPECIES) != SPECIES_NONE)
    {
        canShowSwitch = TRUE;
    };

    if (SWSH_PARTY_MENU_PC_ACCESS
        && gPartyMenu.action == PARTY_ACTION_CHOOSE_MON
        && gPartyMenu.layout == PARTY_LAYOUT_SINGLE
        && (gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD
            || gPartyMenu.menuType == PARTY_MENU_TYPE_DAYCARE))
    {
        canShowBoxes = TRUE;
    };

    // Build ordered draw list (Switch first when present)
    u8 drawList[2];
    u8 drawCount = 0;
    if (canShowSwitch)
        drawList[drawCount++] = BUTTON_PROMPT_SWITCH;
    if (canShowBoxes)
        drawList[drawCount++] = BUTTON_PROMPT_BOXES;

    if (drawCount > 0)
    {
        // Draw the prompts in order using totalWidth and a 4px gap
        int i;
        int gap = (drawCount > 1) ? 6 : 0;
        int combinedWidth = 0;
        for (i = 0; i < drawCount; ++i)
            combinedWidth += sPromptButtonInfo[drawList[i]].totalWidth;
        combinedWidth += gap * (drawCount - 1);

        int curLeft = 104 - combinedWidth;
        for (i = 0; i < drawCount; ++i)
        {
            u8 idx = drawList[i];
            const u8 *text = sPromptButtonInfo[idx].text;
            int stringXPos = GetStringRightAlignXOffset(FONT_SMALL, text, sPromptButtonInfo[idx].totalWidth) + curLeft;
            int iconXPos = stringXPos - sPromptButtonInfo[idx].iconOffset;
            if (iconXPos < 0)
                iconXPos = 0;
            PrintButtonIcon(promptWindowId, sPromptButtonInfo[idx].iconType, iconXPos, 4);
            PrintTextOnWindowWithFont(promptWindowId, text, stringXPos, 0, 0, SWSH_PARTY_FONT_COLOR_BLACK, FONT_SMALL);
            curLeft += sPromptButtonInfo[idx].totalWidth + gap;
        }
        CopyWindowToVram(promptWindowId, COPYWIN_GFX);
        return;
    }

    const u8 *text = sPromptButtonInfo[type].text;
    if (text == NULL)
        return;

    int stringXPos = GetStringRightAlignXOffset(FONT_SMALL, text, 104);
    const u8 iconType = sPromptButtonInfo[type].iconType;
    int iconXPos = stringXPos - sPromptButtonInfo[type].iconOffset;
    if (iconXPos < 0)
        iconXPos = 0;
    PrintButtonIcon(promptWindowId, iconType, iconXPos, 4);
    PrintTextOnWindowWithFont(promptWindowId, text, stringXPos, 0, 0, SWSH_PARTY_FONT_COLOR_BLACK, FONT_SMALL);
    CopyWindowToVram(promptWindowId, COPYWIN_GFX);
    ScheduleBgCopyTilemapToVram(GetWindowAttribute(promptWindowId, WINDOW_BG));
}

static void RefreshSelectedMonInfoAndPrompt(void)
{
    u8 promptType;
    u8 promptWindowId;

    if (sPartyMenuInternal == NULL || sPartyMenuInternal->promptWindowId == WINDOW_NONE)
    {
        ShowSelectedMonInfo();
        return;
    }

    promptWindowId = sPartyMenuInternal->promptWindowId;
    FillWindowPixelBuffer(promptWindowId, PIXEL_FILL(0));
    ClearWindowTilemap(promptWindowId);

    // The held-item and prompt windows overlap. Restore the held-item window
    // first, then place Confirm over its item-name row when selection is full.
    ShowSelectedMonInfo();
    promptType = GetButtonPromptType();
    if (promptType != BUTTON_PROMPT_NONE)
    {
        ShowButtonPrompt(promptType);
        PutWindowTilemap(promptWindowId);
    }
    else
    {
        CopyWindowToVram(promptWindowId, COPYWIN_GFX);
    }
    ScheduleBgCopyTilemapToVram(0);
}

static u16 *GetPartyMenuPalBufferPtr(u8 paletteId)
{
    return &sPartyMenuInternal->palBuffer[paletteId];
}

static u16 RemapPartyMenuTile_SwSh(u8 tileId)
{
    if (tileId == 0)
        return SWSH_PARTY_MENU_BLANK_TILE;
    if (tileId >= SWSH_PARTY_MENU_LEGACY_FRAME_TILE && tileId < SWSH_PARTY_MENU_LEGACY_FRAME_TILE + SWSH_PARTY_MENU_FRAME_TILE_COUNT)
        return SWSH_PARTY_MENU_FRAME_TILE + (tileId - SWSH_PARTY_MENU_LEGACY_FRAME_TILE);
    return tileId;
}

static void BlitBitmapToPartyWindow(u8 windowId, const u8 *b, u8 c, u8 x, u8 y, u8 width, u8 height)
{
    u8 *pixels = AllocZeroed(height * width * 32);
    u8 i, j;

    if (pixels != NULL)
    {
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                u16 tileId = RemapPartyMenuTile_SwSh(b[x + j + ((y + i) * c)]);

                CpuCopy16(GetPartyMenuBgTile(tileId), &pixels[(i * width + j) * 32], 32);
            }
        }
        BlitBitmapToWindow(windowId, pixels, x * 8, y * 8, width * 8, height * 8);
        Free(pixels);
    }
}

static void BlitBitmapToPartyWindow_SwSh(u8 windowId, u8 x, u8 y, u8 width, u8 height, bool8 hideHP)
{
    if (width == 0 && height == 0)
    {
        width = 14;
        height = 3;
    }
    BlitBitmapToPartyWindow(windowId, sSlotTilemap_Main_SwSh, 14, x, y, width, height);
}

static void BlitBitmapToPartyMoveWindow_SwSh(u8 windowId, u8 x, u8 y, u8 width, u8 height, bool8 isEmpty)
{
    if (width == 0 && height == 0)
    {
        width = 14;
        height = 2;
    }
    if (isEmpty)
        BlitBitmapToPartyWindow(windowId, sMoveTilemap_Empty_SwSh, 14, x, y, width, height);
    else
        BlitBitmapToPartyWindow(windowId, sMoveTilemap_Main_SwSh, 14, x, y, width, height);
}

static void DrawEmptySlot(u8 windowId)
{
    BlitBitmapToPartyWindow(windowId, sSlotTilemap_Empty_SwSh, 14, 0, 0, 14, 3);
}

#define LOAD_PARTY_BOX_PAL(paletteIds, paletteOffsets)                                                    \
{                                                                                                         \
    LoadPalette(GetPartyMenuPalBufferPtr(paletteIds[0]), paletteOffsets[0] + palOffset, PLTT_SIZEOF(1));  \
    LoadPalette(GetPartyMenuPalBufferPtr(paletteIds[1]), paletteOffsets[1] + palOffset, PLTT_SIZEOF(1));  \
    LoadPalette(GetPartyMenuPalBufferPtr(paletteIds[2]), paletteOffsets[2] + palOffset, PLTT_SIZEOF(1));  \
}

#define LOAD_PARTY_TEXT_PAL(paletteIds, paletteOffsets)                                                   \
{                                                                                                         \
    LoadPalette(GetPartyMenuPalBufferPtr(paletteIds[0]), paletteOffsets[0] + palOffset, PLTT_SIZEOF(1));  \
    LoadPalette(GetPartyMenuPalBufferPtr(paletteIds[1]), paletteOffsets[1] + palOffset, PLTT_SIZEOF(1));  \
}

static void LoadPartyBoxPalette(struct PartyMenuBox *menuBox, u8 palFlags)
{
    u8 palOffset = BG_PLTT_ID(GetWindowAttribute(menuBox->windowId, WINDOW_PALETTE_NUM));

    if (palFlags & PARTY_PAL_NO_MON)
    {
        LOAD_PARTY_BOX_PAL(sPartyBoxNoMonPalIds, sPartyBoxNoMonPalOffsets);
    }
    else if (palFlags & PARTY_PAL_TO_SOFTBOIL)
    {
        if (palFlags & PARTY_PAL_SELECTED)
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxSelectedForActionPalIds1, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxSelectedForActionPalIds3, sPartyBoxPalOffsets3);
        }
        else
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxSelectedForActionPalIds1, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxSelectedForActionPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxSelectedForActionPalIds3, sPartyBoxPalOffsets3);
        }
    }
    else if (palFlags & PARTY_PAL_TO_SWITCH)
    {
        if (palFlags & PARTY_PAL_SELECTED)
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxSelectedForActionPalIds1, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxSelectedForActionPalIds3, sPartyBoxPalOffsets3);
        }
        else
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxSelectedForActionPalIds1, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxSelectedForActionPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxSelectedForActionPalIds3, sPartyBoxPalOffsets3);
        }
    }
    else if (palFlags & PARTY_PAL_FAINTED)
    {
        if (palFlags & PARTY_PAL_SELECTED)
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionFaintedPalIds, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionFaintedPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxCurrSelectionFaintedPalIds3, sPartyBoxPalOffsets3);
        }
        else
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxFaintedPalIds1, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxFaintedPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxFaintedPalIds3, sPartyBoxPalOffsets3);
        }
    }
    else if (palFlags & PARTY_PAL_MULTI_ALT)
    {
        if (palFlags & PARTY_PAL_SELECTED)
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionMultiPalIds, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxCurrSelectionMultiPalIds3, sPartyBoxPalOffsets3);
        }
        else
        {
            LOAD_PARTY_BOX_PAL(sPartyBoxMultiPalIds1, sPartyBoxPalOffsets1);
            LOAD_PARTY_BOX_PAL(sPartyBoxMultiPalIds2, sPartyBoxPalOffsets2);
            LOAD_PARTY_TEXT_PAL(sPartyBoxMultiPalIds3, sPartyBoxPalOffsets3);
        }
    }
    else if (palFlags & PARTY_PAL_SELECTED)
    {
        LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionPalIds1, sPartyBoxPalOffsets1);
        LOAD_PARTY_BOX_PAL(sPartyBoxCurrSelectionPalIds2, sPartyBoxPalOffsets2);
        LOAD_PARTY_TEXT_PAL(sPartyBoxCurrSelectionPalIds3, sPartyBoxPalOffsets3);
    }
    else
    {
        LOAD_PARTY_BOX_PAL(sPartyBoxEmptySlotPalIds1, sPartyBoxPalOffsets1);
        LOAD_PARTY_BOX_PAL(sPartyBoxEmptySlotPalIds2, sPartyBoxPalOffsets2);
        LOAD_PARTY_TEXT_PAL(sPartyBoxEmptySlotPalIds3, sPartyBoxPalOffsets3);
    }
}

static void DisplayPartyPokemonBarDetail(u8 windowId, const u8 *str, u8 color, const u8 *align)
{
    AddTextPrinterParameterized3(windowId, FONT_SMALL, align[0], align[1], sFontColorTable[color], 0, str);
}

static void DisplayPartyPokemonBarDetailToFit(u8 windowId, const u8 *str, u8 color, const u8 *align, u32 width)
{
    AddTextPrinterParameterized3(windowId, GetFontIdToFit(str, FONT_SMALL, 0, width), align[0], align[1], sFontColorTable[color], 0, str);
}

static u8 GetPPFontColorIndexForMove(struct Pokemon *mon, enum Move move, int m)
{
    u8 currentPP = GetMonData(mon, MON_DATA_PP1 + m);
    u8 ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES);
    u8 maxPP = CalculatePPWithBonus(move, ppBonuses, m);
    u8 ppState = GetCurrentPpToMaxPpState(currentPP, maxPP);

    return 7 + ppState;
}

static void PrintMovePPToWindow(u8 windowId, u8 fontId, struct Pokemon *mon, int m, int xBase, int y, int areaWidth)
{
    enum Move move = GetMonData(mon, MON_DATA_MOVE1 + m);
    u8 bufDigits = 3;

    ConvertIntToDecimalStringN(gStringVar1, GetMonData(mon, MON_DATA_PP1 + m), STR_CONV_MODE_RIGHT_ALIGN, bufDigits);
    int ppX = xBase + GetStringRightAlignXOffset(fontId, gStringVar1, areaWidth);
    AddTextPrinterParameterized3(windowId, fontId, ppX, y, sFontColorTable[GetPPFontColorIndexForMove(mon, move, m)], 0, gStringVar1);
}

static void DisplayPartyPokemonMoves(u8 windowId, struct Pokemon *mon, int m)
{
    enum Move move = GetMonData(mon, MON_DATA_MOVE1 + m);
    const struct PartyMenuMoveBoxInfoRects *info = &sPartyMoveBoxInfoRects[0];

    if (move == MOVE_NONE)
        return;

    const u8 *name = GetMoveName(move);
    u8 type = gMovesInfo[move].type;
    struct SpriteTemplate template = sSpriteTemplate_MoveTypes;
    template.paletteTag = POKE_ICON_BASE_PAL_TAG + sMoveTypeToPalOffset[type];

    sMoveTypeSpriteIds[m] = CreateSprite(&template, 204, 24 + 16 * m, 1);
    if (sMoveTypeSpriteIds[m] != MAX_SPRITES)
    {
        StartSpriteAnim(&gSprites[sMoveTypeSpriteIds[m]], type);
    }
    AddTextPrinterParameterized3(windowId, GetFontIdToFit(name, FONT_SMALL, 0, info->dimensions[2]),
                                 info->dimensions[0], info->dimensions[1], sFontColorTable[0], 0, name);
    PrintMovePPToWindow(windowId, FONT_SMALL, mon, m, info->dimensions[4], info->dimensions[5], info->dimensions[6]);
}

static void DisplayPartyPokemonNickname(struct Pokemon *mon, struct PartyMenuBox *menuBox, u8 c)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];

    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
    {
        if (c == 1)
            menuBox->infoRects->blitFunc(menuBox->windowId, menuBox->infoRects->dimensions[0] >> 3, menuBox->infoRects->dimensions[1] >> 3, menuBox->infoRects->dimensions[2] >> 3, menuBox->infoRects->dimensions[3] >> 3, FALSE);
        GetMonNickname(mon, nickname);
        DisplayPartyPokemonBarDetailToFit(menuBox->windowId, nickname, 0, menuBox->infoRects->dimensions, 50);
    }
}

static void DisplayPartyPokemonLevelCheck(struct Pokemon *mon, struct PartyMenuBox *menuBox, u8 c)
{
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
    {
        u8 ailment = GetMonAilment(mon);
        if (ailment == AILMENT_NONE || ailment == AILMENT_PKRS)
        {
            if (c != 0)
                menuBox->infoRects->blitFunc(menuBox->windowId, menuBox->infoRects->dimensions[4] >> 3, (menuBox->infoRects->dimensions[5] >> 3) + 1, menuBox->infoRects->dimensions[6] >> 3, menuBox->infoRects->dimensions[7] >> 3, FALSE);
            if (c != 2)
                DisplayPartyPokemonLevel(GetMonData(mon, MON_DATA_LEVEL), menuBox);
        }
    }
}

static void DisplayPartyPokemonLevel(u8 level, struct PartyMenuBox *menuBox)
{
    ConvertIntToDecimalStringN(gStringVar2, level, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringCopy(gStringVar1, gText_LevelSymbol);
    StringAppend(gStringVar1, gStringVar2);
    DisplayPartyPokemonBarDetail(menuBox->windowId, gStringVar1, 0, &menuBox->infoRects->dimensions[4]);
}

static void DisplayPartyPokemonGenderNidoranCheck(struct Pokemon *mon, struct PartyMenuBox *menuBox, u8 c)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];

    if (c == 1)
        menuBox->infoRects->blitFunc(menuBox->windowId, menuBox->infoRects->dimensions[8] >> 3, (menuBox->infoRects->dimensions[9] >> 3) + 1, menuBox->infoRects->dimensions[10] >> 3, menuBox->infoRects->dimensions[11] >> 3, FALSE);
    GetMonNickname(mon, nickname);
    DisplayPartyPokemonGender(GetMonGender(mon), GetMonData(mon, MON_DATA_SPECIES), nickname, menuBox);
}

static void DisplayPartyPokemonGender(u8 gender, u16 species, u8 *nickname, struct PartyMenuBox *menuBox)
{
    u8 palOffset = BG_PLTT_ID(GetWindowAttribute(menuBox->windowId, WINDOW_PALETTE_NUM));

    if (species == SPECIES_NONE)
        return;
    if ((species == SPECIES_NIDORAN_M || species == SPECIES_NIDORAN_F) && StringCompare(nickname, GetSpeciesName(species)) == 0)
        return;
    switch (gender)
    {
    case MON_MALE:
        LoadPalette(GetPartyMenuPalBufferPtr(sGenderMalePalIds[0]), sGenderPalOffsets[0] + palOffset, PLTT_SIZEOF(1));
        LoadPalette(GetPartyMenuPalBufferPtr(sGenderMalePalIds[1]), sGenderPalOffsets[1] + palOffset, PLTT_SIZEOF(1));
        DisplayPartyPokemonBarDetail(menuBox->windowId, gText_MaleSymbol, 2, &menuBox->infoRects->dimensions[8]);
        break;
    case MON_FEMALE:
        LoadPalette(GetPartyMenuPalBufferPtr(sGenderFemalePalIds[0]), sGenderPalOffsets[0] + palOffset, PLTT_SIZEOF(1));
        LoadPalette(GetPartyMenuPalBufferPtr(sGenderFemalePalIds[1]), sGenderPalOffsets[1] + palOffset, PLTT_SIZEOF(1));
        DisplayPartyPokemonBarDetail(menuBox->windowId, gText_FemaleSymbol, 2, &menuBox->infoRects->dimensions[8]);
        break;
    }
}

// Mont note: because of how cramped together nickname, HP, and MaxHP are in the party menu boxes,
// we clear and redraw both HP and MaxHP areas together to avoid visual glitches
static void RedrawPartyMonInfo(struct Pokemon *mon, struct PartyMenuBox *menuBox, bool8 redrawHp, bool8 redrawMaxHP, bool8 redrawLevel, bool8 redrawGender)
{
    int left = menuBox->infoRects->dimensions[12];
    int top = menuBox->infoRects->dimensions[13];
    int right = left + menuBox->infoRects->dimensions[14] + 8;
    int bottom = top + menuBox->infoRects->dimensions[15];

    if (redrawMaxHP)
    {
        int l = menuBox->infoRects->dimensions[16];
        int t = menuBox->infoRects->dimensions[17];
        int r = l + menuBox->infoRects->dimensions[18];
        int b = t + menuBox->infoRects->dimensions[19];

        if (l < left) left = l;
        if (t < top) top = t;
        if (r > right) right = r;
        if (b > bottom) bottom = b;
    }

    if (redrawLevel)
    {
        int l = menuBox->infoRects->dimensions[4];
        int t = menuBox->infoRects->dimensions[5];
        int r = l + menuBox->infoRects->dimensions[6];
        int b = t + menuBox->infoRects->dimensions[7];

        if (l < left) left = l;
        if (t < top) top = t;
        if (r > right) right = r;
        if (b > bottom) bottom = b;
    }

    if (redrawGender)
    {
        int l = menuBox->infoRects->dimensions[8];
        int t = menuBox->infoRects->dimensions[9];
        int r = l + menuBox->infoRects->dimensions[10];
        int b = t + menuBox->infoRects->dimensions[11];

        if (l < left) left = l;
        if (t < top) top = t;
        if (r > right) right = r;
        if (b > bottom) bottom = b;
    }

    if (left < right && top < bottom)
       menuBox->infoRects->blitFunc(menuBox->windowId, left >> 3, top >> 3,
                                    ((right - 1) >> 3) - (left >> 3) + 1,
                                    ((bottom - 1) >> 3) - (top >> 3) + 1,
                                    FALSE);

    if (redrawMaxHP)
        DisplayPartyPokemonMaxHP(GetMonData(mon, MON_DATA_MAX_HP), menuBox);
    if (redrawHp)
        DisplayPartyPokemonHP(GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP), menuBox);
    if (redrawLevel)
        DisplayPartyPokemonLevelCheck(mon, menuBox, 0);
    if (redrawGender)
        DisplayPartyPokemonGenderNidoranCheck(mon, menuBox, 0);

    DisplayPartyPokemonNickname(mon, menuBox, 0);
}

static void DisplayPartyPokemonHPCheck(struct Pokemon *mon, struct PartyMenuBox *menuBox, u8 c)
{
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
    {
        if (c != 0)
            RedrawPartyMonInfo(mon, menuBox, FALSE, TRUE, FALSE, FALSE);
        if (c != 2)
            DisplayPartyPokemonHP(GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP), menuBox);
    }
}

static void DisplayParty4DigitsHP_ShiftRight(struct PartyMenuBox *menuBox, const u8 *str, const u8 *origAlings, u32 toAdd)
{
    u8 newAligns[4];

    memcpy(newAligns, origAlings, sizeof(newAligns));
    newAligns[0] += toAdd; // x, shift right for SwSh style
    DisplayPartyPokemonBarDetail(menuBox->windowId, str, 0, newAligns);
}

static void DisplayPartyPokemonHP(u16 hp, u16 maxhp, struct PartyMenuBox *menuBox)
{
    bool32 fourDigits = (maxhp >= 1000);
    u8 *strOut = ConvertIntToDecimalStringN(gStringVar1, hp, STR_CONV_MODE_RIGHT_ALIGN, fourDigits ? 4 : 3);

    strOut[0] = CHAR_SLASH;
    strOut[1] = EOS;

    DisplayPartyPokemonBarDetail(menuBox->windowId, gStringVar1, 0, &menuBox->infoRects->dimensions[12]);
}

static void DisplayPartyPokemonMaxHPCheck(struct Pokemon *mon, struct PartyMenuBox *menuBox, u8 c)
{
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
    {
        if (c != 0)
            RedrawPartyMonInfo(mon, menuBox, TRUE, TRUE, FALSE, FALSE);
        if (c != 2)
            DisplayPartyPokemonMaxHP(GetMonData(mon, MON_DATA_MAX_HP), menuBox);
    }
}

static void DisplayPartyPokemonMaxHP(u16 maxhp, struct PartyMenuBox *menuBox)
{
    bool32 fourDigits = (maxhp >= 1000);

    ConvertIntToDecimalStringN(gStringVar2, maxhp, STR_CONV_MODE_RIGHT_ALIGN, fourDigits ? 4 : 3);
    StringCopy(gStringVar1, gText_Slash);
    StringAppend(gStringVar1, gStringVar2);

    if (fourDigits)
        DisplayParty4DigitsHP_ShiftRight(menuBox, gStringVar1, &menuBox->infoRects->dimensions[16], 5);
    else
        DisplayPartyPokemonBarDetail(menuBox->windowId, gStringVar1, 0, &menuBox->infoRects->dimensions[16]);
}

static void DisplayPartyPokemonHPBarCheck(struct Pokemon *mon, struct PartyMenuBox *menuBox)
{
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
        DisplayPartyPokemonHPBar(GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP), menuBox);
}

static void DisplayPartyPokemonHPBar(u16 hp, u16 maxhp, struct PartyMenuBox *menuBox)
{
    u8 palOffset = BG_PLTT_ID(GetWindowAttribute(menuBox->windowId, WINDOW_PALETTE_NUM));
    u8 hpFraction;

    switch (GetHPBarLevel(hp, maxhp))
    {
    case HP_BAR_GREEN:
    case HP_BAR_FULL:
        LoadPalette(GetPartyMenuPalBufferPtr(sHPBarGreenPalIds[0]), sHPBarPalOffsets[0] + palOffset, PLTT_SIZEOF(1));
        LoadPalette(GetPartyMenuPalBufferPtr(sHPBarGreenPalIds[1]), sHPBarPalOffsets[1] + palOffset, PLTT_SIZEOF(1));
        break;
    case HP_BAR_YELLOW:
        LoadPalette(GetPartyMenuPalBufferPtr(sHPBarYellowPalIds[0]), sHPBarPalOffsets[0] + palOffset, PLTT_SIZEOF(1));
        LoadPalette(GetPartyMenuPalBufferPtr(sHPBarYellowPalIds[1]), sHPBarPalOffsets[1] + palOffset, PLTT_SIZEOF(1));
        break;
    default:
        LoadPalette(GetPartyMenuPalBufferPtr(sHPBarRedPalIds[0]), sHPBarPalOffsets[0] + palOffset, PLTT_SIZEOF(1));
        LoadPalette(GetPartyMenuPalBufferPtr(sHPBarRedPalIds[1]), sHPBarPalOffsets[1] + palOffset, PLTT_SIZEOF(1));
        break;
    }

    hpFraction = GetScaledHPFraction(hp, maxhp, menuBox->infoRects->dimensions[22]);
    FillWindowPixelRect(menuBox->windowId, sHPBarPalOffsets[1], menuBox->infoRects->dimensions[20], menuBox->infoRects->dimensions[21], hpFraction, menuBox->infoRects->dimensions[23]);
    if (hpFraction != menuBox->infoRects->dimensions[22])
    {
        // This appears to be an alternating fill
        FillWindowPixelRect(menuBox->windowId, 0x0D, menuBox->infoRects->dimensions[20] + hpFraction, menuBox->infoRects->dimensions[21], menuBox->infoRects->dimensions[22] - hpFraction, menuBox->infoRects->dimensions[23]);
    }
    CopyWindowToVram(menuBox->windowId, COPYWIN_GFX);
}

static void DisplayPartyPokemonDescriptionText(u8 stringID, struct PartyMenuBox *menuBox, u8 c)
{
    if (c)
    {
        int width = ((menuBox->infoRects->descTextLeft % 8) + menuBox->infoRects->descTextWidth + 7) / 8;
        int height = ((menuBox->infoRects->descTextTop % 8) + menuBox->infoRects->descTextHeight + 7) / 8;
        menuBox->infoRects->blitFunc(menuBox->windowId, menuBox->infoRects->descTextLeft >> 3, menuBox->infoRects->descTextTop >> 3, width, height, TRUE);

        // Redraw nickname, gender, and level after clearing area for description area (for SWSH layout where their windows overlap)
        u8 slot = menuBox->windowId;
        struct Pokemon *mon = &gPlayerParty[slot];
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
        {
            DisplayPartyPokemonNickname(mon, menuBox, 0);
            DisplayPartyPokemonGenderNidoranCheck(mon, menuBox, 0);
            DisplayPartyPokemonLevelCheck(mon, menuBox, 0);
        }
    }
    if (c != 2)
    {
        AddTextPrinterParameterized3(menuBox->windowId, FONT_SMALL, menuBox->infoRects->descTextLeft, menuBox->infoRects->descTextTop, sFontColorTable[0], 0, sDescriptionStringTable[stringID]);
    }
}

static void PartyMenuRemoveWindow(u8 *ptr)
{
    if (*ptr != WINDOW_NONE)
    {
        ClearStdWindowAndFrameToTransparent(*ptr, FALSE);
        RemoveWindow(*ptr);
        *ptr = WINDOW_NONE;
        ScheduleBgCopyTilemapToVram(2);
    }
}

void UNUSED DisplayPartyMenuStdMessage(u32 stringId)
{
    u8 *windowPtr = &sPartyMenuInternal->windowId[1];

    if (*windowPtr != WINDOW_NONE)
        PartyMenuRemoveWindow(windowPtr);

    // Suppress certain party menu prompts
    switch (stringId)
    {
    case PARTY_MSG_CHOOSE_MON:
    case PARTY_MSG_CHOOSE_MON_2:
    case PARTY_MSG_MOVE_TO_WHERE:
    case PARTY_MSG_TEACH_WHICH_MON:
    case PARTY_MSG_USE_ON_WHICH_MON:
    case PARTY_MSG_GIVE_TO_WHICH_MON:
    case PARTY_MSG_RESTORE_WHICH_MOVE:
    case PARTY_MSG_BOOST_PP_WHICH_MOVE:
    case PARTY_MSG_CHOOSE_MON_FOR_BOX:
        // Clear WIN_MSG for prompts that appear after item operations
        ClearStdWindowAndFrameToTransparent(WIN_MSG, FALSE);
        ClearWindowTilemap(WIN_MSG);
        DestroyMessageWindowSprite();
        ScheduleBgCopyTilemapToVram(2);
        return;

    case PARTY_MSG_DO_WHAT_WITH_MON:
    case PARTY_MSG_DO_WHAT_WITH_ITEM:
    case PARTY_MSG_DO_WHAT_WITH_MAIL:
    case PARTY_MSG_MOVE_ITEM_WHERE:
        // Suppress these prompts without clearing WIN_MSG
        return;
    }

    if (stringId != PARTY_MSG_NONE)
    {
        switch (stringId)
        {
        case PARTY_MSG_ALREADY_HOLDING_ONE:
            *windowPtr = AddWindow(&sAlreadyHoldingOneMsgWindowTemplate);
            break;
        case PARTY_MSG_WHICH_APPLIANCE:
            *windowPtr = AddWindow(&sOrderWhichApplianceMsgWindowTemplate);
            break;
        default:
            *windowPtr = AddWindow(&sDefaultPartyMsgWindowTemplate);
            break;
        }

        if (stringId == PARTY_MSG_CHOOSE_MON)
        {
            if (sPartyMenuInternal->chooseHalf)
                stringId = PARTY_MSG_CHOOSE_MON_AND_CONFIRM;
            else if (!ShouldUseChooseMonText())
                stringId = PARTY_MSG_CHOOSE_MON_OR_CANCEL;

            if (gPlayerPartyCount == 0)
                stringId = PARTY_MSG_NO_POKEMON;
        }
        DrawStdFrameWithCustomTileAndPalette(*windowPtr, FALSE, 0x63, 13);
        StringExpandPlaceholders(gStringVar4, sActionStringTable[stringId]);
        AddTextPrinterParameterized(*windowPtr, FONT_NORMAL, gStringVar4, 0, 1, 0, 0);
        ScheduleBgCopyTilemapToVram(2);
    }
}

static bool8 ShouldUseChooseMonText(void)
{
    struct Pokemon *party = gPlayerParty;
    u8 i;
    u8 numAliveMons = 0;

    if (gPartyMenu.action == PARTY_ACTION_SEND_OUT)
        return TRUE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE && (GetMonData(&party[i], MON_DATA_HP) != 0 || GetMonData(&party[i], MON_DATA_IS_EGG)))
            numAliveMons++;
        if (numAliveMons > 1)
            return TRUE;
    }
    return FALSE;
}

static u8 DisplaySelectionWindow(u8 windowType)
{
    struct WindowTemplate window;
    u8 cursorDimension;
    u8 letterSpacing;
    u8 i;

    switch (windowType)
    {
    case SELECTWINDOW_ACTIONS:
        SetWindowTemplateFields(&window, 2, 19, 19 - (sPartyMenuInternal->numActions * 2), 10, sPartyMenuInternal->numActions * 2, 14, 0x2E9);
        break;
    case SELECTWINDOW_ITEM:
        window = sItemGiveTakeWindowTemplate;
        break;
    case SELECTWINDOW_MAIL:
        window = sMailReadTakeWindowTemplate;
        break;
    case SELECTWINDOW_CATALOG:
        window = sCatalogSelectWindowTemplate;
        break;
    case SELECTWINDOW_ZYGARDECUBE:
        window = sZygardeCubeSelectWindowTemplate;
        break;
    default: // SELECTWINDOW_MOVES
        window = sMoveSelectWindowTemplate;
        break;
    }

    sPartyMenuInternal->windowId[0] = AddWindow(&window);
    DrawStdFrameWithCustomTileAndPalette(sPartyMenuInternal->windowId[0], FALSE, 0x63, 13);
    if (windowType == SELECTWINDOW_MOVES)
        return sPartyMenuInternal->windowId[0];
    cursorDimension = GetMenuCursorDimensionByFont(FONT_NORMAL, 0);
    letterSpacing = GetFontAttribute(FONT_NORMAL, FONTATTR_LETTER_SPACING);

    for (i = 0; i < sPartyMenuInternal->numActions; i++)
    {
        const u8 *text;
        u8 fontColorsId = 3;

        if (sPartyMenuInternal->actions[i] >= MENU_FIELD_MOVES)
            fontColorsId = 4;
        if (sPartyMenuInternal->actions[i] >= MENU_LEVEL_UP_MOVES && sPartyMenuInternal->actions[i] <= MENU_SUB_MOVES)
            fontColorsId = 6;

        if (sPartyMenuInternal->actions[i] >= MENU_FIELD_MOVES)
            text = GetMoveName(FieldMove_GetMoveId(sPartyMenuInternal->actions[i] - MENU_FIELD_MOVES));
        else
            text = sCursorOptions[sPartyMenuInternal->actions[i]].text;

        AddTextPrinterParameterized4(sPartyMenuInternal->windowId[0], FONT_NORMAL, cursorDimension, (i * 16) + 1, letterSpacing, 0, sFontColorTable[fontColorsId], 0, text);
    }

    InitMenuInUpperLeftCorner(sPartyMenuInternal->windowId[0], sPartyMenuInternal->numActions, 0, TRUE);
    ScheduleBgCopyTilemapToVram(2);

    return sPartyMenuInternal->windowId[0];
}

static void PrintMessage(const u8 *text)
{
    CreateMessageWindowSprite();
    FillBgTilemapBufferRect(2, SWSH_PARTY_MENU_BLANK_TILE, 1, 15, 28, 4, 14);
    PutWindowTilemap(WIN_MSG);
    FillWindowPixelBuffer(WIN_MSG, PIXEL_FILL(0));
    CopyWindowToVram(WIN_MSG, COPYWIN_GFX);
    ScheduleBgCopyTilemapToVram(2);
    gTextFlags.canABSpeedUpPrint = TRUE;
    AddTextPrinterParameterized2(WIN_MSG, FONT_NORMAL, text, GetPlayerTextSpeedDelay(), 0, TEXT_COLOR_WHITE, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY);
}

static void PartyMenuDisplayYesNoMenu(void)
{
    CreateYesNoMenu(&sPartyMenuYesNoWindowTemplate, 0x63, 13, 0);
}

static u8 CreateLevelUpStatsWindow(void)
{
    sPartyMenuInternal->windowId[0] = AddWindow(&sLevelUpStatsWindowTemplate);
    DrawStdFrameWithCustomTileAndPalette(sPartyMenuInternal->windowId[0], FALSE, 0x63, 13);
    return sPartyMenuInternal->windowId[0];
}

static void RemoveLevelUpStatsWindow(void)
{
    ClearWindowTilemap(sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
}

static void SetPartyMonSelectionActions(struct Pokemon *mons, u8 slotId, u8 action)
{
    u8 i;

    if (action == ACTIONS_NONE)
    {
        SetPartyMonFieldSelectionActions(mons, slotId);
    }
    else if (action == ACTIONS_MOVES_SUB && P_PARTY_MOVE_RELEARNER)
    {
        sPartyMenuInternal->numActions = 0;
        SetPartyMonLearnMoveSelectionActions(mons, slotId);
    }
    else
    {
        sPartyMenuInternal->numActions = sPartyMenuActionCounts[action];
        for (i = 0; i < sPartyMenuInternal->numActions; i++)
            sPartyMenuInternal->actions[i] = sPartyMenuActions[action][i];
    }
}

static void SetPartyMonFieldSelectionActions(struct Pokemon *mons, u8 slotId)
{
    u8 i, j;

    sPartyMenuInternal->numActions = 0;
    AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_SUMMARY);

    if (P_PARTY_MOVE_RELEARNER
        && GetMonData(&mons[slotId], MON_DATA_SPECIES)
        && CanBoxMonRelearnAnyMove(&mons[slotId].box))
    {
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_SUB_MOVES);
    }
    // Add field moves to action list
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        for (j = 0; j != FIELD_MOVES_COUNT; j++)
        {
            if (GetMonData(&mons[slotId], i + MON_DATA_MOVE1) == FieldMove_GetMoveId(j))
            {
                // If Mon already knows FLY and the HM is in the bag, prevent it from being added to action list
                if (FieldMove_GetMoveId(j) != MOVE_FLY || !CheckBagHasItem(ITEM_HM02, 1)){
                    // If Mon already knows FLASH and the HM is in the bag, prevent it from being added to action list
                    if (FieldMove_GetMoveId(j) != MOVE_FLASH || !CheckBagHasItem(ITEM_HM05, 1)){ 
                        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, j + MENU_FIELD_MOVES);
                    }
                }
                break;
            }
        }
    }

    // If Mon can learn HM02 and action list consists of < 4 moves, add FLY to action list
    if (sPartyMenuInternal->numActions < 5 && CanLearnTeachableMove(GetMonData(&mons[slotId], MON_DATA_SPECIES), ItemIdToBattleMoveId(ITEM_HM02)) && CheckBagHasItem(ITEM_HM02, 1)) 
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, 5 + MENU_FIELD_MOVES);
    // If Mon can learn HM05 and action list consists of < 4 moves, add FLASH to action list
    if (sPartyMenuInternal->numActions < 5 && CanLearnTeachableMove(GetMonData(&mons[slotId], MON_DATA_SPECIES), ItemIdToBattleMoveId(ITEM_HM05)) && CheckBagHasItem(ITEM_HM05, 1)) 
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, 1 + MENU_FIELD_MOVES);


    if (!InBattlePike())
    {
        if (GetMonData(&mons[1], MON_DATA_SPECIES) != SPECIES_NONE)
            AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_SWITCH);
        for (i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (!ItemIsMail(GetMonData(&mons[slotId], MON_DATA_HELD_ITEM + i)))
            {
                AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_ITEM);
                break;
            }
        }
        if (!GetMonData(&mons[slotId], MON_DATA_IS_EGG)
         && GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetMonData(&mons[slotId], MON_DATA_SPECIES)), FLAG_GET_SEEN))
            AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_POKEDEX);
        for (i = 0; i < MAX_MON_ITEMS; i++)
        {
            if (ItemIsMail(GetMonData(&mons[slotId], MON_DATA_HELD_ITEM + i)))
            {
                AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_MAIL);
                break;
            }
        }
    }
    AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_CANCEL1);
}

static void SetPartyMonLearnMoveSelectionActions(struct Pokemon *mons, u8 slotId)
{
    if (CanBoxMonRelearnMoves(&mons[slotId].box, MOVE_RELEARNER_LEVEL_UP_MOVES))
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_LEVEL_UP_MOVES);

    if (CanBoxMonRelearnMoves(&mons[slotId].box, MOVE_RELEARNER_TUTOR_MOVES))
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_TUTOR_MOVES);

    if (CanBoxMonRelearnMoves(&mons[slotId].box, MOVE_RELEARNER_EGG_MOVES))
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_EGG_MOVES);

    if (CanBoxMonRelearnMoves(&mons[slotId].box, MOVE_RELEARNER_TM_MOVES))
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_TM_MOVES);

    AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, MENU_CANCEL1);
}

static u8 GetPartyMenuActionsType(struct Pokemon *mon)
{
    // TODO: review all use cases to ensure feature parity with vanilla
    u32 actionType;

    switch (gPartyMenu.menuType)
    {
    case PARTY_MENU_TYPE_FIELD:
        if (InMultiPartnerRoom() == TRUE || GetMonData(mon, MON_DATA_IS_EGG))
            actionType = ACTIONS_SWITCH;
        else
            actionType = ACTIONS_NONE; // actions populated by SetPartyMonFieldSelectionActions
        break;
    case PARTY_MENU_TYPE_IN_BATTLE:
        actionType = GetPartyMenuActionsTypeInBattle(mon);
        break;
    case PARTY_MENU_TYPE_CHOOSE_HALF:
        switch (GetPartySlotEntryStatus(gPartyMenu.slotId))
        {
        default: // Not eligible
            actionType = ACTIONS_SUMMARY_ONLY;
            break;
        case 0: // Eligible
            actionType = ACTIONS_ENTER;
            break;
        case 1: // Already selected
            actionType = ACTIONS_NO_ENTRY;
            break;
        }
        break;
    case PARTY_MENU_TYPE_DAYCARE:
        actionType = (GetMonData(mon, MON_DATA_IS_EGG)) ? ACTIONS_SUMMARY_ONLY : ACTIONS_STORE;
        break;
    case PARTY_MENU_TYPE_UNION_ROOM_REGISTER:
        actionType = ACTIONS_REGISTER;
        break;
    case PARTY_MENU_TYPE_UNION_ROOM_TRADE:
        actionType = ACTIONS_TRADE;
        break;
    case PARTY_MENU_TYPE_SPIN_TRADE:
        actionType = ACTIONS_SPIN_TRADE;
        break;
    case PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS:
        actionType = ACTIONS_TAKEITEM_TOSS;
        break;
    // The following have no selection actions (i.e. they exit immediately upon selection)
    // PARTY_MENU_TYPE_CONTEST
    // PARTY_MENU_TYPE_CHOOSE_MON
    // PARTY_MENU_TYPE_MULTI_SHOWCASE
    // PARTY_MENU_TYPE_MOVE_RELEARNER
    // PARTY_MENU_TYPE_MINIGAME
    default:
        actionType = ACTIONS_NONE;
        break;
    }
    return actionType;
}

static bool8 CreateSelectionWindow(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item;

    GetMonNickname(mon, gStringVar1);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    if (gPartyMenu.menuType != PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS)
    {
        SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, GetPartyMenuActionsType(mon));
        DisplaySelectionWindow(SELECTWINDOW_ACTIONS);
    }
    else
    {
        item = GetMonData(mon, MON_DATA_HELD_ITEM);
        if (item != ITEM_NONE)
        {
            SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, GetPartyMenuActionsType(mon));
            DisplaySelectionWindow(SELECTWINDOW_ITEM);
            CopyItemName(item, gStringVar2);
        }
        else
        {
            StringExpandPlaceholders(gStringVar4, gText_PkmnNotHolding);
            DisplayPartyMenuMessage(gStringVar4, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_UpdateHeldItemSprite;
            return FALSE;
        }
    }
    return TRUE;
}

static void Task_TryCreateSelectionWindow(u8 taskId)
{
    if (CreateSelectionWindow(taskId))
    {
        gTasks[taskId].data[0] = 0xFF;
        gTasks[taskId].func = Task_HandleSelectionMenuInput;
    }
}

static void Task_HandleSelectionMenuInput(u8 taskId)
{
    if (!gPaletteFade.active && MenuHelpers_ShouldWaitForLinkRecv() != TRUE)
    {
        s8 input;
        s16 *data = gTasks[taskId].data;

        if (sPartyMenuInternal->numActions <= 3)
            input = Menu_ProcessInputNoWrapAround_other();
        else
            input = ProcessMenuInput_other();

        data[0] = Menu_GetCursorPos();
        switch (input)
        {
        case MENU_NOTHING_CHOSEN:
            break;
        case MENU_B_PRESSED:
            PlaySE(SE_SELECT);
            PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[2]);
            if (sPartyMenuInternal->actions[sPartyMenuInternal->numActions - 1] >= MENU_FIELD_MOVES)
                CursorCb_FieldMove(taskId);
            else
                sCursorOptions[sPartyMenuInternal->actions[sPartyMenuInternal->numActions - 1]].func(taskId);
            break;
        default:
            PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[2]);
            if (sPartyMenuInternal->actions[input] >= MENU_FIELD_MOVES)
                CursorCb_FieldMove(taskId);
            else
                sCursorOptions[sPartyMenuInternal->actions[input]].func(taskId);
            break;
        }
    }
}

static void CursorCb_Summary(u8 taskId)
{
    PlaySE(SE_SELECT);
    sPartyMenuInternal->exitCallback = CB2_ShowPokemonSummaryScreen;
    Task_ClosePartyMenu(taskId);
}

static void CB2_ShowPokemonSummaryScreen(void)
{
    if (gPartyMenu.menuType == PARTY_MENU_TYPE_IN_BATTLE)
    {
        UpdatePartyToBattleOrder();
        ShowPokemonSummaryScreen(SUMMARY_MODE_LOCK_MOVES, gPlayerParty, gPartyMenu.slotId, gPlayerPartyCount - 1, CB2_ReturnToPartyMenuFromSummaryScreen);
    }
    else if (gPartyMenu.menuType == PARTY_MENU_TYPE_CHOOSE_HALF)
    {
        ShowPokemonSummaryScreen(SUMMARY_MODE_LOCK_MOVES, gPlayerParty, gPartyMenu.slotId, gPlayerPartyCount - 1, CB2_ReturnToPartyMenuFromSummaryScreen);
    }
    else
    {
        ShowPokemonSummaryScreen(SUMMARY_MODE_NORMAL, gPlayerParty, gPartyMenu.slotId, gPlayerPartyCount - 1, CB2_ReturnToPartyMenuFromSummaryScreen);
    }
}

void CB2_ReturnToPartyMenuFromSummaryScreen(void)
{
    gPaletteFade.bufferTransferDisabled = TRUE;
    gPartyMenu.slotId = gLastViewedMonIndex;
    InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, gPartyMenu.action, TRUE, PARTY_MSG_DO_WHAT_WITH_MON, Task_TryCreateSelectionWindow, gPartyMenu.exitCallback);
}

static void CursorCb_Switch(u8 taskId)
{
    // Reset follower steps when the party leader is changed
    if (gPartyMenu.slotId == 0 || gPartyMenu.slotId2 == 0)
        gFollowerSteps = 0;
    PlaySE(SE_SELECT);
    gPartyMenu.action = PARTY_ACTION_SWITCH;
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    // Keep the switch origin visually selected, but leave its icon idle.
    AnimatePartySlot(gPartyMenu.slotId, 0);
    gPartyMenu.slotId2 = gPartyMenu.slotId;
    UpdateSelectedMonItemSprite();
    gTasks[taskId].func = Task_HandleChooseMonInput;
}

#define tSlot1Left     data[0]
#define tSlot1Top      data[1]
#define tSlot1Width    data[2]
#define tSlot1Height   data[3]
#define tSlot2Left     data[4]
#define tSlot2Top      data[5]
#define tSlot2Width    data[6]
#define tSlot2Height   data[7]
#define tSlot1Offset   data[8]
#define tSlot2Offset   data[9]
#define tSlot1SlideDir data[10]
#define tSlot2SlideDir data[11]

static void SwitchSelectedMons(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 windowIds[2];

    DestroySelectFrame();
    DestroyHoverSprite();
    DestroyMonSprite();

    if (gPartyMenu.slotId2 == gPartyMenu.slotId)
    {
        FinishTwoMonAction(taskId);
    }
    else
    {
        // Initialize switching party mons slide animation
        windowIds[0] = sPartyMenuBoxes[gPartyMenu.slotId].windowId;
        tSlot1Left = GetWindowAttribute(windowIds[0], WINDOW_TILEMAP_LEFT);
        tSlot1Top = GetWindowAttribute(windowIds[0], WINDOW_TILEMAP_TOP);
        tSlot1Width = GetWindowAttribute(windowIds[0], WINDOW_WIDTH);
        tSlot1Height = GetWindowAttribute(windowIds[0], WINDOW_HEIGHT);
        tSlot1Offset = 0;
        tSlot1SlideDir = -1;
        windowIds[1] = sPartyMenuBoxes[gPartyMenu.slotId2].windowId;
        tSlot2Left = GetWindowAttribute(windowIds[1], WINDOW_TILEMAP_LEFT);
        tSlot2Top = GetWindowAttribute(windowIds[1], WINDOW_TILEMAP_TOP);
        tSlot2Width = GetWindowAttribute(windowIds[1], WINDOW_WIDTH);
        tSlot2Height = GetWindowAttribute(windowIds[1], WINDOW_HEIGHT);
        tSlot2Offset = 0;
        tSlot2SlideDir = -1;
        sSlot1TilemapBuffer = Alloc(tSlot1Width * (tSlot1Height << 1));
        sSlot2TilemapBuffer = Alloc(tSlot2Width * (tSlot2Height << 1));
        CopyToBufferFromBgTilemap(0, sSlot1TilemapBuffer, tSlot1Left, tSlot1Top, tSlot1Width, tSlot1Height);
        CopyToBufferFromBgTilemap(0, sSlot2TilemapBuffer, tSlot2Left, tSlot2Top, tSlot2Width, tSlot2Height);
        ClearWindowTilemap(windowIds[0]);
        ClearWindowTilemap(windowIds[1]);
        gPartyMenu.action = PARTY_ACTION_SWITCHING;
        AnimatePartySlot(gPartyMenu.slotId, 1);
        AnimatePartySlot(gPartyMenu.slotId2, 1);
        SlidePartyMenuBoxOneStep(taskId);
        gTasks[taskId].func = Task_SlideSelectedSlotsOffscreen;
    }
}

// returns FALSE if the slot has slid fully offscreen / back onscreen
static bool8 TryMovePartySlot(s16 x, s16 width, u8 *leftMove, u8 *newX, u8 *newWidth)
{
    if (x + width < 0)
        return FALSE;
    if (x >= 32)
        return FALSE;

    if (x < 0)
    {
        *leftMove = x * -1;
        *newX = 0;
        *newWidth = width + x;
    }
    else
    {
        *leftMove = 0;
        *newX = x;
        if (x + width >= 32)
            *newWidth = 32 - x;
        else
            *newWidth = width;

    }
    return TRUE;
}

static void MoveAndBufferPartySlot(const void *rectSrc, s16 x, s16 y, s16 width, s16 height, s16 dir)
{
    u8 srcX, newX, newWidth;

    if (TryMovePartySlot(x, width, &srcX, &newX, &newWidth))
    {
        FillBgTilemapBufferRect_Palette0(0, SWSH_PARTY_MENU_BLANK_TILE, newX, y, newWidth, height);
        if (TryMovePartySlot(x + dir, width, &srcX, &newX, &newWidth))
            CopyRectToBgTilemapBufferRect(0, rectSrc, srcX, 0, width, height, newX, y, newWidth, height, 17, 0, 0);
    }
}

static void MovePartyMenuBoxSprites(struct PartyMenuBox *menuBox, s16 offset)
{
    OffsetPartyMenuBoxSprites(menuBox, offset * TILE_WIDTH);
}

static void SlidePartyMenuBoxSpritesOneStep(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tSlot1SlideDir != 0)
        MovePartyMenuBoxSprites(&sPartyMenuBoxes[gPartyMenu.slotId], tSlot1SlideDir);
    if (tSlot2SlideDir != 0)
        MovePartyMenuBoxSprites(&sPartyMenuBoxes[gPartyMenu.slotId2], tSlot2SlideDir);
}

static void SlidePartyMenuBoxOneStep(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tSlot1SlideDir != 0)
        MoveAndBufferPartySlot(sSlot1TilemapBuffer, tSlot1Left + tSlot1Offset, tSlot1Top, tSlot1Width, tSlot1Height, tSlot1SlideDir);
    if (tSlot2SlideDir != 0)
        MoveAndBufferPartySlot(sSlot2TilemapBuffer, tSlot2Left + tSlot2Offset, tSlot2Top, tSlot2Width, tSlot2Height, tSlot2SlideDir);
    ScheduleBgCopyTilemapToVram(0);
}

static void Task_SlideSelectedSlotsOffscreen(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    s16 slidingSlotPositions[2];

    SlidePartyMenuBoxOneStep(taskId);
    SlidePartyMenuBoxSpritesOneStep(taskId);
    tSlot1Offset += tSlot1SlideDir;
    tSlot2Offset += tSlot2SlideDir;
    slidingSlotPositions[0] = tSlot1Left + tSlot1Offset;
    slidingSlotPositions[1] = tSlot2Left + tSlot2Offset;

    // Both slots have slid offscreen
    if (slidingSlotPositions[0] + tSlot1Width < 0 && slidingSlotPositions[1] + tSlot2Width < 0)
    {
        tSlot1SlideDir *= -1;
        tSlot2SlideDir *= -1;
        SwitchPartyMon();
        DisplayPartyPokemonData(gPartyMenu.slotId);
        DisplayPartyPokemonData(gPartyMenu.slotId2);
        PutWindowTilemap(sPartyMenuBoxes[gPartyMenu.slotId].windowId);
        PutWindowTilemap(sPartyMenuBoxes[gPartyMenu.slotId2].windowId);
        CopyToBufferFromBgTilemap(0, sSlot1TilemapBuffer, tSlot1Left, tSlot1Top, tSlot1Width, tSlot1Height);
        CopyToBufferFromBgTilemap(0, sSlot2TilemapBuffer, tSlot2Left, tSlot2Top, tSlot2Width, tSlot2Height);
        ClearWindowTilemap(sPartyMenuBoxes[gPartyMenu.slotId].windowId);
        ClearWindowTilemap(sPartyMenuBoxes[gPartyMenu.slotId2].windowId);
        gTasks[taskId].func = Task_SlideSelectedSlotsOnscreen;
    }
}

static void Task_SlideSelectedSlotsOnscreen(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    SlidePartyMenuBoxOneStep(taskId);
    SlidePartyMenuBoxSpritesOneStep(taskId);

    // Both slots have slid back onscreen
    if (tSlot1SlideDir == 0 && tSlot2SlideDir == 0)
    {
        PutWindowTilemap(sPartyMenuBoxes[gPartyMenu.slotId].windowId);
        PutWindowTilemap(sPartyMenuBoxes[gPartyMenu.slotId2].windowId);
        ScheduleBgCopyTilemapToVram(0);
        Free(sSlot1TilemapBuffer);
        Free(sSlot2TilemapBuffer);
        FinishTwoMonAction(taskId);
    }
    // Continue sliding
    else
    {
        tSlot1Offset += tSlot1SlideDir;
        tSlot2Offset += tSlot2SlideDir;
        if (tSlot1Offset == 0)
            tSlot1SlideDir = 0;
        if (tSlot2Offset == 0)
            tSlot2SlideDir = 0;
    }
}

static void SwitchMenuBoxSprites(u8 *spriteIdPtr1, u8 *spriteIdPtr2)
{
    u8 spriteId1 = *spriteIdPtr1;
    u8 spriteId2 = *spriteIdPtr2;
    s16 xBuffer1, yBuffer1, xBuffer2, yBuffer2;

    *spriteIdPtr1 = spriteId2;
    *spriteIdPtr2 = spriteId1;

    // SwSh does not create the legacy Poké Ball slot sprites, so their IDs
    // remain SPRITE_NONE. Sprite allocation can also return MAX_SPRITES.
    if (spriteId1 >= MAX_SPRITES || spriteId2 >= MAX_SPRITES
        || !gSprites[spriteId1].inUse || !gSprites[spriteId2].inUse)
        return;

    xBuffer1 = gSprites[spriteId2].x;
    yBuffer1 = gSprites[spriteId2].y;
    xBuffer2 = gSprites[spriteId2].x2;
    yBuffer2 = gSprites[spriteId2].y2;
    gSprites[spriteId2].x = gSprites[spriteId1].x;
    gSprites[spriteId2].y = gSprites[spriteId1].y;
    gSprites[spriteId2].x2 = gSprites[spriteId1].x2;
    gSprites[spriteId2].y2 = gSprites[spriteId1].y2;
    gSprites[spriteId1].x = xBuffer1;
    gSprites[spriteId1].y = yBuffer1;
    gSprites[spriteId1].x2 = xBuffer2;
    gSprites[spriteId1].y2 = yBuffer2;
}

static void SwitchPartyMon(void)
{
    struct PartyMenuBox *menuBoxes[2];
    struct Pokemon *mon1, *mon2;
    struct Pokemon *monBuffer;

    menuBoxes[0] = &sPartyMenuBoxes[gPartyMenu.slotId];
    menuBoxes[1] = &sPartyMenuBoxes[gPartyMenu.slotId2];
    mon1 = &gPlayerParty[gPartyMenu.slotId];
    mon2 = &gPlayerParty[gPartyMenu.slotId2];
    monBuffer = Alloc(sizeof(struct Pokemon));
    *monBuffer = *mon1;
    *mon1 = *mon2;
    *mon2 = *monBuffer;
    Free(monBuffer);
    SwitchMenuBoxSprites(&menuBoxes[0]->pokeballSpriteId, &menuBoxes[1]->pokeballSpriteId);
    SwitchMenuBoxSprites(&menuBoxes[0]->itemSpriteId, &menuBoxes[1]->itemSpriteId);
    SwitchMenuBoxSprites(&menuBoxes[0]->monSpriteId, &menuBoxes[1]->monSpriteId);
    SwitchMenuBoxSprites(&menuBoxes[0]->statusSpriteId, &menuBoxes[1]->statusSpriteId);
}

// Finish switching mons or using Softboiled
static void FinishTwoMonAction(u8 taskId)
{
    u8 i;
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);

    if (gPartyMenu.action == PARTY_ACTION_FUSION)
    {
        sFusionFirstMonSlot = 0;
        sFusionFirstMonSpecies = 0;
    }

    gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;
    AnimatePartySlot(gPartyMenu.slotId, 0);
    gPartyMenu.slotId = gPartyMenu.slotId2;
    AnimatePartySlot(gPartyMenu.slotId2, 1);
    UpdatePartyMonSprite(gPartyMenu.slotId);
    CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);

    // Reset item icons to generic if we were in item mode
    if (sPartyMenuInternal->inItemMode)
    {
        sPartyMenuInternal->inItemMode = FALSE;
        for (i = 0; i < PARTY_SIZE; i++)
            UpdatePartyMonHeldItemSprite(&gPlayerParty[i], &sPartyMenuBoxes[i]);
    }
    else
    {
        // Make sure item sprites are visible again (e.g., after canceling MOVE_ITEM)
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (sPartyMenuBoxes[i].itemSpriteId != MAX_SPRITES)
            {
                enum Item item = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
                if (item != ITEM_NONE)
                    gSprites[sPartyMenuBoxes[i].itemSpriteId].invisible = FALSE;
            }
        }
    }

    UpdateSelectedMonItemSprite();

    gTasks[taskId].func = Task_HandleChooseMonInput;
}

#undef tSlot1Left
#undef tSlot1Top
#undef tSlot1Width
#undef tSlot1Height
#undef tSlot2Left
#undef tSlot2Top
#undef tSlot2Width
#undef tSlot2Height
#undef tSlot1Offset
#undef tSlot2Offset
#undef tSlot1SlideDir
#undef tSlot2SlideDir

static void CursorCb_Cancel1(u8 taskId)
{
    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    RefreshSelectedMonInfoAndPrompt();
    gTasks[taskId].func = Task_HandleChooseMonInput;
}

static void CursorCb_Item(u8 taskId)
{
    u8 i;
    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, ACTIONS_ITEM);
    DisplaySelectionWindow(SELECTWINDOW_ITEM);

    // Switch from generic held item icon to actual item icons
    sPartyMenuInternal->inItemMode = TRUE;
    for (i = 0; i < PARTY_SIZE; i++)
        UpdatePartyMonHeldItemSprite(&gPlayerParty[i], &sPartyMenuBoxes[i]);

    // The item selection window and the selected-mon info panels share BG2.
    // Refreshing the info here would redraw it over the selection window.
    DestroySelectedMonItemSprite();

    gTasks[taskId].data[0] = 0xFF;
    gTasks[taskId].func = Task_HandleSelectionMenuInput;
}

static void CursorCb_Pokedex(u8 taskId)
{
    PlaySE(SE_SELECT);
    sPartyMenuInternal->exitCallback = CB2_OpenPartyPokedex;
    Task_ClosePartyMenu(taskId);
}

static void CB2_OpenPartyPokedex(void)
{
    u16 species = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES);

    OpenPokedexPlusHGSSAtSpecies(species, CB2_ReturnToPartyMenuFromPokedex);
}

static void CB2_ReturnToPartyMenuFromPokedex(void)
{
    gPaletteFade.bufferTransferDisabled = TRUE;
    InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, gPartyMenu.action, TRUE, PARTY_MSG_DO_WHAT_WITH_MON, Task_TryCreateSelectionWindow, gPartyMenu.exitCallback);
}

static void CursorCb_Give(u8 taskId)
{
    PlaySE(SE_SELECT);
    sPartyMenuInternal->exitCallback = CB2_SelectBagItemToGive;
    Task_ClosePartyMenu(taskId);
}

static void CB2_SelectBagItemToGive(void)
{
    if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
        GoToBagMenu(ITEMMENULOCATION_PARTY, POCKETS_COUNT, CB2_GiveHoldItem);
    else
        GoToBattlePyramidBagMenu(PYRAMIDBAG_LOC_PARTY, CB2_GiveHoldItem);
}

static void CB2_GiveHoldItem(void)
{
    if (gSpecialVar_ItemId == ITEM_NONE)
    {
        InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, gPartyMenu.action, TRUE, PARTY_MSG_NONE, Task_TryCreateSelectionWindow, gPartyMenu.exitCallback);
    }
    else
    {
        sPartyMenuItemId = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM);

        // Already holding item
        if (sPartyMenuItemId != ITEM_NONE)
        {
            InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, PARTY_ACTION_GIVE_ITEM, TRUE, PARTY_MSG_NONE, Task_SwitchHoldItemsPrompt, gPartyMenu.exitCallback);
            gPartyMenu.bagItem = gSpecialVar_ItemId;
        }
        // Give mail
        else if (ItemIsMail(gSpecialVar_ItemId))
        {
            RemoveBagItem(gSpecialVar_ItemId, 1);
            GiveItemToMon(&gPlayerParty[gPartyMenu.slotId], gSpecialVar_ItemId);
            CB2_WriteMailToGiveMon();
        }
        // Give item
        else
        {
            InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, PARTY_ACTION_GIVE_ITEM, TRUE, PARTY_MSG_NONE, Task_GiveHoldItem, gPartyMenu.exitCallback);
            gPartyMenu.bagItem = gSpecialVar_ItemId;
        }
    }
}

static void Task_GiveHoldItem(u8 taskId)
{
    enum Item item;

    if (!gPaletteFade.active)
    {
        item = gSpecialVar_ItemId;
        GiveItemToMon(&gPlayerParty[gPartyMenu.slotId], item);
        RemoveHeldItemFromBag(item);

#if TESTING
        if (sSkipGiveHeldItemVisualsForTest)
            return;
#endif

        // Visually update cursor and held item sprites
        UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuBoxes[gPartyMenu.slotId]);
        gSpecialVar_ItemId = ITEM_NONE;
        DestroyHoverSprite();
        CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);

        DisplayGaveHeldItemMessage(&gPlayerParty[gPartyMenu.slotId], item, FALSE, 0);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
    }
}

#if TESTING
bool32 SwShPartyMenu_TestGiveHeldItemToMon(u8 partyId, enum Item item)
{
    bool8 paletteFadeActive = gPaletteFade.active;
    s8 previousSlot = gPartyMenu.slotId;
    u16 previousItem = gSpecialVar_ItemId;

    gPaletteFade.active = FALSE;
    gPartyMenu.slotId = partyId;
    gSpecialVar_ItemId = item;
    sSkipGiveHeldItemVisualsForTest = TRUE;
    Task_GiveHoldItem(0);
    sSkipGiveHeldItemVisualsForTest = FALSE;

    gPaletteFade.active = paletteFadeActive;
    gPartyMenu.slotId = previousSlot;
    gSpecialVar_ItemId = previousItem;

    return GetMonData(&gPlayerParty[partyId], MON_DATA_HELD_ITEM) == item;
}
#endif

static void Task_SwitchHoldItemsPrompt(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DisplayAlreadyHoldingItemSwitchMessage(&gPlayerParty[gPartyMenu.slotId], sPartyMenuItemId, TRUE);
        gTasks[taskId].func = Task_SwitchItemsYesNo;
    }
}

static void Task_SwitchItemsYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleSwitchItemsYesNoInput;
    }
}

static void CancelHeldItemSwitch(u8 taskId)
{
    gPartyMenu.action = PARTY_ACTION_GIVE_ITEM;
    gSpecialVar_ItemId = ITEM_NONE;
    gTasks[taskId].func = Task_UpdateHeldItemSprite;
}

#if TESTING
bool32 SwShPartyMenu_TestCancelHeldItemSwitch(enum Item item)
{
    u8 taskId;
    u8 previousAction = gPartyMenu.action;
    u16 previousItem = gSpecialVar_ItemId;
    bool32 canceled;

    taskId = CreateTask(TaskDummy, 0);
    if (taskId == TASK_NONE)
        return FALSE;

    gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;
    gSpecialVar_ItemId = item;
    CancelHeldItemSwitch(taskId);
    canceled = (gPartyMenu.action == PARTY_ACTION_GIVE_ITEM
             && gSpecialVar_ItemId == ITEM_NONE
             && gTasks[taskId].func == Task_UpdateHeldItemSprite);

    DestroyTask(taskId);
    gPartyMenu.action = previousAction;
    gSpecialVar_ItemId = previousItem;

    return canceled;
}
#endif

static void Task_HandleSwitchItemsYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // Yes, switch items
        RemoveHeldItemFromBag(gSpecialVar_ItemId);

        // No room to return held item to bag
        if (AddHeldItemToBag(sPartyMenuItemId) == FALSE)
        {
            AddHeldItemToBag(gSpecialVar_ItemId);
            BufferBagFullCantTakeItemMessage(sPartyMenuItemId);
            DisplayPartyMenuMessage(gStringVar4, FALSE);
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        }
        // Giving mail
        else if (ItemIsMail(gSpecialVar_ItemId))
        {
            GiveItemToMon(&gPlayerParty[gPartyMenu.slotId], gSpecialVar_ItemId);
            gTasks[taskId].func = Task_WriteMailToGiveMonAfterText;
        }
        // Giving item
        else
        {
            u16 newItem = gSpecialVar_ItemId;
            GiveItemToMon(&gPlayerParty[gPartyMenu.slotId], newItem);

            // Visually update cursor and held item sprites
            UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuBoxes[gPartyMenu.slotId]);
            gSpecialVar_ItemId = ITEM_NONE;
            DestroyHoverSprite();
            CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);

            DisplaySwitchedHeldItemMessage(newItem, sPartyMenuItemId, TRUE);
            gTasks[taskId].func = Task_UpdateHeldItemSprite;
        }
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1: // No
        CancelHeldItemSwitch(taskId);
        break;
    }
}

static void Task_WriteMailToGiveMonAfterText(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        sPartyMenuInternal->exitCallback = CB2_WriteMailToGiveMon;
        Task_ClosePartyMenu(taskId);
    }
}

static void CB2_WriteMailToGiveMon(void)
{
    u8 mail = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_MAIL);

    DoEasyChatScreen(
        EASY_CHAT_TYPE_MAIL,
        gSaveBlock1Ptr->mail[mail].words,
        CB2_ReturnToPartyMenuFromWritingMail,
        EASY_CHAT_PERSON_DISPLAY_NONE);
}

static void CB2_ReturnToPartyMenuFromWritingMail(void)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = GetMonData(mon, MON_DATA_HELD_ITEM);

    // Canceled writing mail
    if (gSpecialVar_Result == FALSE)
    {
        TakeMailFromMon(mon);
        SetMonData(mon, MON_DATA_HELD_ITEM, &sPartyMenuItemId);
        RemoveHeldItemFromBag(sPartyMenuItemId);
        AddBagItem(item, 1);
        InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, gPartyMenu.action, TRUE, PARTY_MSG_CHOOSE_MON, Task_TryCreateSelectionWindow, gPartyMenu.exitCallback);
    }
    // Wrote mail
    else
    {
        InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, gPartyMenu.action, TRUE, PARTY_MSG_NONE, Task_DisplayGaveMailFromPartyMessage, gPartyMenu.exitCallback);
    }
}

// Nearly redundant with Task_DisplayGaveMailFromBagMessgae
static void Task_DisplayGaveMailFromPartyMessage(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (sPartyMenuItemId == ITEM_NONE)
            DisplayGaveHeldItemMessage(&gPlayerParty[gPartyMenu.slotId], gSpecialVar_ItemId, FALSE, 0);
        else
            DisplaySwitchedHeldItemMessage(gSpecialVar_ItemId, sPartyMenuItemId, FALSE);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
    }
}

static void Task_UpdateHeldItemSprite(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        u8 i;
        bool8 wasGivingItem = (gPartyMenu.action == PARTY_ACTION_GIVE_ITEM);

        // Reset to generic icons after finishing item operations
        if (sPartyMenuInternal->inItemMode)
        {
            sPartyMenuInternal->inItemMode = FALSE;
            for (i = 0; i < PARTY_SIZE; i++)
                UpdatePartyMonHeldItemSprite(&gPlayerParty[i], &sPartyMenuBoxes[i]);
        }
        else
        {
            // Update the held item sprite for the selected mon
            UpdatePartyMonHeldItemSprite(mon, &sPartyMenuBoxes[gPartyMenu.slotId]);
        }

        if (gPartyMenu.menuType == PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS)
        {
            if (GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE)
                DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_HAVE, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
            else
                DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_DONT_HAVE, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
        }

        // After completing give item operation, reset cursor and icons
        if (wasGivingItem)
        {
            gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;
            gSpecialVar_ItemId = ITEM_NONE;

            sPartyMenuInternal->inItemMode = FALSE;
            for (i = 0; i < PARTY_SIZE; i++)
                UpdatePartyMonHeldItemSprite(&gPlayerParty[i], &sPartyMenuBoxes[i]);
            DestroyHoverSprite();
            CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);
        }

        // The held-item info window overlaps WIN_MSG on BG2. Clear the message
        // before restoring the info window so its text cannot bleed through.
        Task_ReturnToChooseMonAfterText(taskId);
        UpdateSelectedMonItemSprite();
    }
}

static void CursorCb_TakeItem(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = GetMonData(mon, MON_DATA_HELD_ITEM);

    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    switch (TryTakeMonItem(mon))
    {
    case 0: // Not holding item
        GetMonNickname(mon, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_PkmnNotHolding);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        break;
    case 1: // No room to take item
        BufferBagFullCantTakeItemMessage(item);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        break;
    default: // Took item
        DisplayTookHeldItemMessage(mon, item, TRUE);
        break;
    }
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_UpdateHeldItemSprite;
}

static void CursorCb_Toss(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = GetMonData(mon, MON_DATA_HELD_ITEM);

    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    if (item == ITEM_NONE)
    {
        GetMonNickname(mon, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_PkmnNotHolding);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
    }
    else if (!CanItemBeTossed(item))
    {
        DisplayPartyMenuMessage(gText_ItemCantBeTossed, TRUE);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
    }
    else
    {
        CopyItemName(item, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_ThrowAwayItem);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        gTasks[taskId].func = Task_TossHeldItemYesNo;
    }
}

static void Task_TossHeldItemYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleTossHeldItemYesNoInput;
    }
}

static void Task_HandleTossHeldItemYesNoInput(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        if (!CanItemBeTossed(GetMonData(mon, MON_DATA_HELD_ITEM)))
        {
            DisplayPartyMenuMessage(gText_ItemCantBeTossed, FALSE);
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
            break;
        }
        CopyItemName(GetMonData(mon, MON_DATA_HELD_ITEM), gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_ItemThrownAway);
        DisplayPartyMenuMessage(gStringVar4, FALSE);
        gTasks[taskId].func = Task_TossHeldItem;
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        break;
    }
}

static void Task_TossHeldItem(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    if (
#if TESTING
        sSkipTossHeldItemVisualsForTest ||
#endif
        IsPartyMenuTextPrinterActive() != TRUE)
    {
        enum Item heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
        enum Item item = ITEM_NONE;

        if (!CanItemBeTossed(heldItem))
        {
#if TESTING
            if (sSkipTossHeldItemVisualsForTest)
                return;
#endif
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
            return;
        }

        SetMonData(mon, MON_DATA_HELD_ITEM, &item);
#if TESTING
        if (sSkipTossHeldItemVisualsForTest)
            return;
#endif
        UpdatePartyMonHeldItemSprite(mon, &sPartyMenuBoxes[gPartyMenu.slotId]);
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_DONT_HAVE, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    }
}

#if TESTING
bool32 SwShPartyMenu_TestTossHeldItem(u8 partyId)
{
    s8 previousSlot = gPartyMenu.slotId;

    gPartyMenu.slotId = partyId;
    sSkipTossHeldItemVisualsForTest = TRUE;
    Task_TossHeldItem(0);
    sSkipTossHeldItemVisualsForTest = FALSE;
    gPartyMenu.slotId = previousSlot;

    return GetMonData(&gPlayerParty[partyId], MON_DATA_HELD_ITEM) == ITEM_NONE;
}
#endif

static void CursorCb_Mail(u8 taskId)
{
    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, ACTIONS_MAIL);
    DisplaySelectionWindow(SELECTWINDOW_MAIL);
    gTasks[taskId].data[0] = 0xFF;
    gTasks[taskId].func = Task_HandleSelectionMenuInput;
}

static void CursorCb_Read(u8 taskId)
{
    PlaySE(SE_SELECT);
    sPartyMenuInternal->exitCallback = CB2_ReadHeldMail;
    Task_ClosePartyMenu(taskId);
}

static void CB2_ReadHeldMail(void)
{
    ReadMail(&gSaveBlock1Ptr->mail[GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_MAIL)], CB2_ReturnToPartyMenuFromReadingMail, TRUE);
}

static void CB2_ReturnToPartyMenuFromReadingMail(void)
{
    gPaletteFade.bufferTransferDisabled = TRUE;
    InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, gPartyMenu.action, TRUE, PARTY_MSG_DO_WHAT_WITH_MON, Task_TryCreateSelectionWindow, gPartyMenu.exitCallback);
}

static void CursorCb_TakeMail(u8 taskId)
{
    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    DisplayPartyMenuMessage(gText_SendMailToPC, TRUE);
    gTasks[taskId].func = Task_SendMailToPCYesNo;
}

static void Task_SendMailToPCYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleSendMailToPCYesNoInput;
    }
}

static void Task_HandleSendMailToPCYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // Yes, send to PC
        if (TakeMailFromMonAndSave(&gPlayerParty[gPartyMenu.slotId]) != MAIL_NONE)
        {
            DisplayPartyMenuMessage(gText_MailSentToPC, FALSE);
            gTasks[taskId].func = Task_UpdateHeldItemSprite;
        }
        else
        {
            DisplayPartyMenuMessage(gText_PCMailboxFull, FALSE);
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        }
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        DisplayPartyMenuMessage(gText_MailMessageWillBeLost, TRUE);
        gTasks[taskId].func = Task_LoseMailMessageYesNo;
        break;
    }
}

static void Task_LoseMailMessageYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleLoseMailMessageYesNoInput;
    }
}

static void Task_HandleLoseMailMessageYesNoInput(u8 taskId)
{
    enum Item item;

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // Yes, lose mail message
        item = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM);
        if (AddBagItem(item, 1) == TRUE)
        {
            TakeMailFromMon(&gPlayerParty[gPartyMenu.slotId]);
            DisplayPartyMenuMessage(gText_MailTakenFromPkmn, FALSE);
            gTasks[taskId].func = Task_UpdateHeldItemSprite;
        }
        else
        {
            BufferBagFullCantTakeItemMessage(item);
            DisplayPartyMenuMessage(gStringVar4, FALSE);
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        }
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        break;
    }
}

static void CursorCb_Cancel2(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, GetPartyMenuActionsType(mon));

    // If canceling back to main action menu from Item mode, reset to generic held item icons
    if (sPartyMenuInternal->inItemMode)
    {
        u8 i;
        sPartyMenuInternal->inItemMode = FALSE;
        for (i = 0; i < PARTY_SIZE; i++)
            UpdatePartyMonHeldItemSprite(&gPlayerParty[i], &sPartyMenuBoxes[i]);
        UpdateSelectedMonItemSprite();
    }

    if (gPartyMenu.menuType != PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS)
    {
        DisplaySelectionWindow(SELECTWINDOW_ACTIONS);
    }
    else
    {
        DisplaySelectionWindow(SELECTWINDOW_ITEM);
        CopyItemName(GetMonData(mon, MON_DATA_HELD_ITEM), gStringVar2);
    }
    gTasks[taskId].data[0] = 0xFF;
    gTasks[taskId].func = Task_HandleSelectionMenuInput;
}

static void CursorCb_SendMon(u8 taskId)
{
    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    if (TrySwitchInPokemon() == TRUE)
    {
        Task_ClosePartyMenu(taskId);
    }
    else
    {
        // gStringVar4 below is the error message buffered by TrySwitchInPokemon
        PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    }
}

static void CursorCb_Enter(u8 taskId)
{
    u8 maxBattlers;
    u8 i;

    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    maxBattlers = GetMaxBattleEntries();
    for (i = 0; i < maxBattlers; i++)
    {
        if (gSelectedOrderFromParty[i] == 0)
        {
            PlaySE(SE_SELECT);
            gSelectedOrderFromParty[i] = gPartyMenu.slotId + 1;
            DisplayPartyPokemonDescriptionText(i + PARTYBOX_DESC_FIRST, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
            RefreshSelectedMonInfoAndPrompt();
            if (i == maxBattlers - 1)
                gPartyMenu.task(taskId);
            else
                gTasks[taskId].func = Task_HandleChooseMonInput;
            return;
        }
    }
    ConvertIntToDecimalStringN(gStringVar1, maxBattlers, STR_CONV_MODE_LEFT_ALIGN, 1);
    StringExpandPlaceholders(gStringVar4, gText_NoMoreThanVar1Pkmn);
    PlaySE(SE_FAILURE);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
}

static void CursorCb_NoEntry(u8 taskId)
{
    u8 maxBattlers;
    u8 i, j;

    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    maxBattlers = GetMaxBattleEntries();
    for (i = 0; i < maxBattlers; i++)
    {
        if (gSelectedOrderFromParty[i] == (gPartyMenu.slotId + 1))
        {
            for (j = i; j < (maxBattlers - 1); j++)
                gSelectedOrderFromParty[j] = gSelectedOrderFromParty[j + 1];
            gSelectedOrderFromParty[j] = 0;
            break;
        }
    }
    DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_ABLE_3, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
    for (i = 0; i < (maxBattlers - 1); i++)
    {
        if (gSelectedOrderFromParty[i] != 0)
            DisplayPartyPokemonDescriptionText(i + PARTYBOX_DESC_FIRST, &sPartyMenuBoxes[gSelectedOrderFromParty[i] - 1], 1);
    }
    RefreshSelectedMonInfoAndPrompt();
    gTasks[taskId].func = Task_HandleChooseMonInput;
}

static void CursorCb_Store(u8 taskId)
{
    PlaySE(SE_SELECT);
    Task_ClosePartyMenu(taskId);
}

// Register mon for the Trading Board in Union Room
static void CursorCb_Register(u8 taskId)
{
    u16 species2 = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES_OR_EGG);
    u16 species = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES);
    u8 isModernFatefulEncounter = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_MODERN_FATEFUL_ENCOUNTER);

    switch (CanRegisterMonForTradingBoard(*(struct RfuGameCompatibilityData *)GetHostRfuGameData(), species2, species, isModernFatefulEncounter))
    {
    case CANT_REGISTER_MON_NOW:
        StringExpandPlaceholders(gStringVar4, gText_PkmnCantBeTradedNow);
        break;
    case CANT_REGISTER_MON:
        StringExpandPlaceholders(gStringVar4, gText_PkmnCantBeTraded);
        break;
    case CANT_REGISTER_EGG:
        StringExpandPlaceholders(gStringVar4, gText_EggCantBeTradedNow);
        break;
    default:
        PlaySE(SE_SELECT);
        Task_ClosePartyMenu(taskId);
        return;
    }
    PlaySE(SE_FAILURE);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    StringAppend(gStringVar4, gText_PauseUntilPress);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
}

static void CursorCb_Trade1(u8 taskId)
{
    u16 species2 = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES_OR_EGG);
    u16 species = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES);
    u8 isModernFatefulEncounter = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_MODERN_FATEFUL_ENCOUNTER);
    u32 stringId = GetUnionRoomTradeMessageId(*(struct RfuGameCompatibilityData *)GetHostRfuGameData(), gRfuPartnerCompatibilityData, species2, gUnionRoomOfferedSpecies, gUnionRoomRequestedMonType, species, isModernFatefulEncounter);

    if (stringId != UR_TRADE_MSG_NONE)
    {
        StringExpandPlaceholders(gStringVar4, sUnionRoomTradeMessages[stringId - 1]);
        PlaySE(SE_FAILURE);
        PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
        PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
        StringAppend(gStringVar4, gText_PauseUntilPress);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    }
    else
    {
        PlaySE(SE_SELECT);
        Task_ClosePartyMenu(taskId);
    }
}

// Spin Trade (based on the translation of the Japanese trade prompt)
// Not fully implemented, and normally unreachable because PARTY_MENU_TYPE_SPIN_TRADE is never used
static void CursorCb_Trade2(u8 taskId)
{
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    switch (CanSpinTradeMon(gPlayerParty, gPartyMenu.slotId))
    {
    case CANT_TRADE_LAST_MON:
        StringExpandPlaceholders(gStringVar4, gText_OnlyPkmnForBattle);
        break;
    case CANT_TRADE_NATIONAL:
        StringExpandPlaceholders(gStringVar4, gText_PkmnCantBeTradedNow);
        break;
    case CANT_TRADE_EGG_YET:
        StringExpandPlaceholders(gStringVar4, gText_EggCantBeTradedNow);
        break;
    default: // CAN_TRADE_MON
        PlaySE(SE_SELECT);
        GetMonNickname(&gPlayerParty[gPartyMenu.slotId], gStringVar1);
        StringExpandPlaceholders(gStringVar4, gJPText_AreYouSureYouWantToSpinTradeMon);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        gTasks[taskId].func = Task_SpinTradeYesNo;
        return;
    }
    PlaySE(SE_FAILURE);
    StringAppend(gStringVar4, gText_PauseUntilPress);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
}

static void Task_SpinTradeYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleSpinTradeYesNoInput;
    }
}

// See comment on CursorCb_Trade2. Because no callback is set, selecting YES (0) to spin trade just closes the party menu
static void Task_HandleSpinTradeYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        Task_ClosePartyMenu(taskId);
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        Task_ReturnToChooseMonAfterText(taskId);
        break;
    }
}

static void CursorCb_FieldMove(u8 taskId)
{
    u8 fieldMove = sPartyMenuInternal->actions[Menu_GetCursorPos()] - MENU_FIELD_MOVES;
    const struct MapHeader *mapHeader;

    PlaySE(SE_SELECT);
    if (gFieldMoveInfo[fieldMove].fieldMoveFunc == NULL)
        return;

    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    if (MenuHelpers_IsLinkActive() == TRUE || InUnionRoom() == TRUE)
    {
        if (fieldMove == FIELD_MOVE_MILK_DRINK || fieldMove == FIELD_MOVE_SOFT_BOILED)
            DisplayPartyMenuMessage(gText_CantUseHere, TRUE);
        else
            StringExpandPlaceholders(gStringVar4, sActionStringTable[FieldMove_GetPartyMsgID(fieldMove)]);
            DisplayPartyMenuMessage(gStringVar4, TRUE);

        gTasks[taskId].func = Task_CancelAfterAorBPress;
    }
    else
    {
        // All field moves before WATERFALL are HMs.
        if (!IsFieldMoveUnlocked(fieldMove))
        {
            DisplayPartyMenuMessage(gText_CantUseUntilNewBadge, TRUE);
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        }
        else if (SetUpFieldMove(fieldMove) == TRUE)
        {
            switch (fieldMove)
            {
            case FIELD_MOVE_MILK_DRINK:
            case FIELD_MOVE_SOFT_BOILED:
                ChooseMonForSoftboiled(taskId);
                break;
            case FIELD_MOVE_TELEPORT:
                mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->lastHealLocation.mapGroup, gSaveBlock1Ptr->lastHealLocation.mapNum);
                GetMapNameGeneric(gStringVar1, mapHeader->regionMapSectionId);
                StringExpandPlaceholders(gStringVar4, gText_ReturnToHealingSpot);
                DisplayFieldMoveExitAreaMessage(taskId);
                sPartyMenuInternal->data[0] = fieldMove;
                break;
            case FIELD_MOVE_DIG:
                mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->escapeWarp.mapGroup, gSaveBlock1Ptr->escapeWarp.mapNum);
                GetMapNameGeneric(gStringVar1, mapHeader->regionMapSectionId);
                StringExpandPlaceholders(gStringVar4, gText_EscapeFromHere);
                DisplayFieldMoveExitAreaMessage(taskId);
                sPartyMenuInternal->data[0] = fieldMove;
                break;
            case FIELD_MOVE_FLY:
                gPartyMenu.exitCallback = CB2_OpenFlyMap;
                Task_ClosePartyMenu(taskId);
                break;
            default:
                gPartyMenu.exitCallback = CB2_ReturnToField;
                Task_ClosePartyMenu(taskId);
                break;
            }
        }
        // Cant use Field Move
        else
        {
            switch (fieldMove)
            {
            case FIELD_MOVE_SURF:
                DisplayCantUseSurfMessage();
                break;
            case FIELD_MOVE_FLASH:
                DisplayCantUseFlashMessage();
                break;
            default:
                StringExpandPlaceholders(gStringVar4, sActionStringTable[FieldMove_GetPartyMsgID(fieldMove)]);
                DisplayPartyMenuMessage(gStringVar4, TRUE);
                break;
            }
            gTasks[taskId].func = Task_CancelAfterAorBPress;
        }
    }
}

static void DisplayFieldMoveExitAreaMessage(u8 taskId)
{
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    gTasks[taskId].func = Task_FieldMoveExitAreaYesNo;
}

static void Task_FieldMoveExitAreaYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleFieldMoveExitAreaYesNoInput;
    }
}

static void Task_HandleFieldMoveExitAreaYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        gPartyMenu.exitCallback = CB2_ReturnToField;
        Task_ClosePartyMenu(taskId);
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        gFieldCallback2 = NULL;
        gPostMenuFieldCallback = NULL;
        Task_ReturnToChooseMonAfterText(taskId);
        break;
    }
}

bool8 FieldCallback_PrepareFadeInFromMenu(void)
{
    FadeInFromBlack();
    CreateTask(Task_FieldMoveWaitForFade, 8);
    if (PlayerHasFollowerNPC())
        CreateTask(Task_HideFollowerNPCForTeleport, 0);

    return TRUE;
}

// Same as above, but removes follower pokemon
bool8 FieldCallback_PrepareFadeInForTeleport(void)
{
    RemoveFollowingPokemon();
    return FieldCallback_PrepareFadeInFromMenu();
}

#define taskState       task->data[0]

enum
{
    FNPC_WALK_INTO_PLAYER,
    FNPC_WAIT_FOR_ANIM_FINISH
};

static void Task_HideFollowerNPCForTeleport(u8 taskId)
{
    struct ObjectEvent *follower = &gObjectEvents[GetFollowerNPCObjectId()];
    struct Task *task;
    task = &gTasks[taskId];
    if (taskState == FNPC_WALK_INTO_PLAYER)
    {
        if (!PlayerHasFollowerNPC())
        {
            DestroyTask(taskId);
        }
        else
        {
            FollowerNPCWalkIntoPlayerForLeaveMap();
            taskState = FNPC_WAIT_FOR_ANIM_FINISH;
        }
    }
    if (taskState == FNPC_WAIT_FOR_ANIM_FINISH)
    {
        if (ObjectEventClearHeldMovementIfFinished(follower))
        {
            FollowerNPCHideForLeaveMap(follower);
            DestroyTask(taskId);
        }
    }
}

#undef taskState

static void Task_FieldMoveWaitForFade(u8 taskId)
{
    if (IsWeatherNotFadingIn() == TRUE)
    {
        gFieldEffectArguments[0] = GetFieldMoveMonSpecies();
        gPostMenuFieldCallback();
        DestroyTask(taskId);
    }
}

static u16 GetFieldMoveMonSpecies(void)
{
    return GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES);
}

static void Task_CancelAfterAorBPress(u8 taskId)
{
    if ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON)))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    }
}

static void DisplayCantUseFlashMessage(void)
{
    if (FlagGet(FLAG_SYS_USE_FLASH) == TRUE)
    {
        DisplayPartyMenuMessage(gText_InUseAlready_PM, TRUE);
    }
    else
    {
        DisplayPartyMenuMessage(gText_CantUseHere, TRUE);
    }
}

static void FieldCallback_Surf(void)
{
    u8 surfMonPartySlot = GetSurfablePokemonPartySlot();

    gFieldEffectArguments[0] = (surfMonPartySlot == PARTY_SIZE) ? GetCursorSelectionMonId() : surfMonPartySlot;
    FieldEffectStart(FLDEFF_USE_SURF);
}

bool32 SetUpFieldMove_Surf(void)
{
    if (!CheckFollowerNPCFlag(FOLLOWER_NPC_FLAG_CAN_SURF))
        return FALSE;

    if (PartyHasMonWithSurf() == TRUE && IsPlayerFacingSurfableFishableWater() == TRUE)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Surf;
        return TRUE;
    }
    return FALSE;
}

static void DisplayCantUseSurfMessage(void)
{
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
    {
        DisplayPartyMenuMessage(gText_AlreadySurfing, TRUE);
    }
    else
    {
        DisplayPartyMenuMessage(gText_CantSurfHere, TRUE);
    }
}

bool32 SetUpFieldMove_Fly(void)
{
    if (!CheckFollowerNPCFlag(FOLLOWER_NPC_FLAG_CAN_LEAVE_ROUTE))
        return FALSE;

    if (Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE)
        return TRUE;
    else
        return FALSE;
}

void CB2_ReturnToPartyMenuFromFlyMap(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_FIELD, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, TRUE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ReturnToFieldWithOpenMenu);
}

static void FieldCallback_Waterfall(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    FieldEffectStart(FLDEFF_USE_WATERFALL);
}

bool32 SetUpFieldMove_Waterfall(void)
{
    s16 x, y;

    if (!CheckFollowerNPCFlag(FOLLOWER_NPC_FLAG_CAN_WATERFALL))
        return FALSE;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    if (MetatileBehavior_IsWaterfall(MapGridGetMetatileBehaviorAt(x, y)) == TRUE && IsPlayerSurfingNorth() == TRUE)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Waterfall;
        return TRUE;
    }
    return FALSE;
}

bool32 SetUpFieldMove_RockClimb(void)
{
    s16 x, y;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(x, y)))
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_RockClimb;
        return TRUE;
    }

    return FALSE;
}

bool32 SetUpFieldMove_Whirlpool(void)
{
    return FALSE;
}

static void FieldCallback_Dive(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    FieldEffectStart(FLDEFF_USE_DIVE);
}

bool32 SetUpFieldMove_Dive(void)
{
    if (!CheckFollowerNPCFlag(FOLLOWER_NPC_FLAG_CAN_DIVE))
        return FALSE;

    gFieldEffectArguments[1] = TrySetDiveWarp();
    if (gFieldEffectArguments[1] != 0)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Dive;
        return TRUE;
    }
    return FALSE;
}

static void CreatePartyMonIconSprite(struct Pokemon *mon, struct PartyMenuBox *menuBox, u32 slot)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    bool32 isEgg = GetMonData(mon, MON_DATA_IS_EGG);
    bool32 isShiny = GetMonData(mon, MON_DATA_IS_SHINY);
    CreatePartyMonIconSpriteParameterized(species, GetMonData(mon, MON_DATA_PERSONALITY), isShiny, isEgg, menuBox, 1);
    UpdatePartyMonHPBar(menuBox->monSpriteId, mon);
}

static void CreatePartyMonIconSpriteParameterized(u16 species, u32 pid, bool32 isShiny, bool32 isEgg, struct PartyMenuBox *menuBox, u8 priority)
{
    if (species != SPECIES_NONE)
    {
        //menuBox->monSpriteId = CreateMonIconIsEgg(species, SpriteCB_MonIcon, menuBox->spriteCoords[0], menuBox->spriteCoords[1], 4, pid, isEgg);
        menuBox->monSpriteId = CreateMonIcon2(species, SpriteCB_MonIcon, menuBox->spriteCoords[0], menuBox->spriteCoords[1], 4, isShiny, pid, isEgg);
        gSprites[menuBox->monSpriteId].oam.priority = priority;
        ApplyPartySlotOffsetToSprite(menuBox, menuBox->monSpriteId);
    }
}

static s16 GetPartyMenuHeldItemSpriteX(const struct PartyMenuBox *menuBox)
{
    return menuBox->spriteCoords[2] + SWSH_PARTY_HELD_ITEM_X_OFFSET;
}

static s16 GetPartyMenuHeldItemSpriteY(const struct PartyMenuBox *menuBox)
{
    return menuBox->spriteCoords[3] + SWSH_PARTY_HELD_ITEM_Y_OFFSET;
}

static void UpdateHPBar(u8 spriteId, u16 hp, u16 maxhp)
{
    switch (GetHPBarLevel(hp, maxhp))
    {
    case HP_BAR_FULL:
        SetPartyHPBarSprite(&gSprites[spriteId], 0);
        break;
    case HP_BAR_GREEN:
        SetPartyHPBarSprite(&gSprites[spriteId], 1);
        break;
    case HP_BAR_YELLOW:
        SetPartyHPBarSprite(&gSprites[spriteId], 2);
        break;
    case HP_BAR_RED:
        SetPartyHPBarSprite(&gSprites[spriteId], 3);
        break;
    default:
        SetPartyHPBarSprite(&gSprites[spriteId], 4);
        break;
    }
}

static void UpdatePartyMonHPBar(u8 spriteId, struct Pokemon *mon)
{
    UpdateHPBar(spriteId, GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP));
}

static void AnimateSelectedPartyIcon(u8 spriteId, u8 animNum)
{
    gSprites[spriteId].data[0] = 0;
    if (animNum == 0)
    {
        if (gSprites[spriteId].x == 16)
        {
            gSprites[spriteId].x2 = 0;
            gSprites[spriteId].y2 = -4;
        }
        else
        {
            gSprites[spriteId].x2 = -2;
            gSprites[spriteId].y2 = 0;
        }
        gSprites[spriteId].callback = SpriteCB_UpdatePartyMonIcon;
    }
    else
    {
        gSprites[spriteId].x2 = 0;
        gSprites[spriteId].y2 = 0;
        gSprites[spriteId].callback = SpriteCB_BouncePartyMonIcon;
    }
}

static void SpriteCB_BouncePartyMonIcon(struct Sprite *sprite)
{
    u8 animCmd = UpdateMonIconFrame(sprite);

    if (animCmd != 0)
    {
        if (animCmd & 1) // % 2 also matches
            sprite->y2 = -3;
        else
            sprite->y2 = 1;
    }
}

static void SpriteCB_UpdatePartyMonIcon(struct Sprite *sprite)
{
    UpdateMonIconFrame(sprite);
}

static const union AffineAnimCmd sAffineAnim_ItemIcon_Small[] =
{
    // scale to 75% of original item icon sprite
    AFFINEANIMCMD_FRAME(206, 206, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sAffineAnims_ItemIcon[] =
{
    sAffineAnim_ItemIcon_Small,
};

static bool8 ShouldShowSelectedMonItemSprite(void)
{
    if (sMonSpriteId == MAX_SPRITES || sMonSpriteId == SPRITE_NONE)
        return FALSE;
    if (ShouldShowBattleDetails()
        || gPartyMenu.menuType == PARTY_MENU_TYPE_MULTI_SHOWCASE)
        return FALSE;
    if (gPartyMenu.slotId >= gPlayerPartyCount)
        return FALSE;
    if (GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES) == SPECIES_NONE)
        return FALSE;
    if (gPartyMenu.action == PARTY_ACTION_SWITCH
        || gPartyMenu.action == PARTY_ACTION_SWITCHING)
        return FALSE;

    // Hide the selected mon item icon while item actions are already consuming
    // extra sprite slots for cursor, slot icons, or swap animations.
    if (sPartyMenuInternal != NULL
        && (sPartyMenuInternal->inItemMode
            || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM
            || gPartyMenu.action == PARTY_ACTION_GIVE_ITEM))
        return FALSE;

    return GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM) != ITEM_NONE;
}

static void DestroySelectedMonItemSprite(void)
{
    if (sSelectedMonItemSpriteId != MAX_SPRITES && sSelectedMonItemSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_SELECTED_MON_ITEM_ICON);
        FreeSpritePaletteByTag(TAG_SELECTED_MON_ITEM_ICON);
        FreeSpriteOamMatrix(&gSprites[sSelectedMonItemSpriteId]);
        DestroySprite(&gSprites[sSelectedMonItemSpriteId]);
        sSelectedMonItemSpriteId = MAX_SPRITES;
    }
}

static void UpdateSelectedMonItemSprite(void)
{
    enum Item item;

    RefreshSelectedMonInfoAndPrompt();

    if (!ShouldShowSelectedMonItemSprite())
    {
        DestroySelectedMonItemSprite();
        return;
    }

    item = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM);

    DestroySelectedMonItemSprite();
    sSelectedMonItemSpriteId = AddItemIconSprite(TAG_SELECTED_MON_ITEM_ICON, TAG_SELECTED_MON_ITEM_ICON, item);
    if (sSelectedMonItemSpriteId != MAX_SPRITES)
    {
        struct Sprite *sprite = &gSprites[sSelectedMonItemSpriteId];
        struct Sprite *monSprite = &gSprites[sMonSpriteId];

        sprite->x = monSprite->x + SWSH_PARTY_SELECTED_ITEM_X_OFFSET;
        sprite->y = monSprite->y + SWSH_PARTY_SELECTED_ITEM_Y_OFFSET;
        sprite->oam.priority = 1;
        sprite->subpriority = 5;
        sprite->oam.affineMode = ST_OAM_AFFINE_NORMAL;
        sprite->affineAnims = sAffineAnims_ItemIcon;
        InitSpriteAffineAnim(sprite);
        StartSpriteAffineAnim(sprite, 0);
    }
}

static void CreatePartyMonCustomItemIcon(struct PartyMenuBox *menuBox, enum Item item)
{
    u8 slot = menuBox - sPartyMenuBoxes;
    u16 tag = TAG_HELD_ITEM_ICON_BASE + slot;
    u8 spriteId = AddItemIconSprite(tag, tag, item);

    if (spriteId != MAX_SPRITES)
    {
        menuBox->itemSpriteId = spriteId;
        gSprites[spriteId].x = GetPartyMenuHeldItemSpriteX(menuBox);
        gSprites[spriteId].y = GetPartyMenuHeldItemSpriteY(menuBox);
        gSprites[spriteId].oam.priority = 1;
        gSprites[spriteId].subpriority = 2;

        gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_NORMAL;
        gSprites[spriteId].affineAnims = sAffineAnims_ItemIcon;
        InitSpriteAffineAnim(&gSprites[spriteId]);
        StartSpriteAffineAnim(&gSprites[spriteId], 0);
        ApplyPartySlotOffsetToSprite(menuBox, spriteId);
    }
}

static void CreatePartyMonHeldItemSprite(struct Pokemon *mon, struct PartyMenuBox *menuBox)
{
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
    {
        if (gPartyMenu.action == PARTY_ACTION_GIVE_ITEM || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM || sPartyMenuInternal->inItemMode)
        {
            menuBox->itemSpriteId = MAX_SPRITES;
            UpdatePartyMonHeldItemSprite(mon, menuBox);
        }
        else
        {
            menuBox->itemSpriteId = CreateSprite(&sSpriteTemplate_HeldItem, GetPartyMenuHeldItemSpriteX(menuBox), GetPartyMenuHeldItemSpriteY(menuBox), 1);
            if (menuBox->itemSpriteId != MAX_SPRITES)
            {
                gSprites[menuBox->itemSpriteId].subpriority = 2;
                ApplyPartySlotOffsetToSprite(menuBox, menuBox->itemSpriteId);
            }
            UpdatePartyMonHeldItemSprite(mon, menuBox);
        }
    }
}

static void CreatePartyMonHeldItemSpriteParameterized(u16 species, enum Item item, struct PartyMenuBox *menuBox)
{
    if (species != SPECIES_NONE)
    {
        if (gPartyMenu.action == PARTY_ACTION_GIVE_ITEM || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM || sPartyMenuInternal->inItemMode)
        {
            menuBox->itemSpriteId = MAX_SPRITES;
            if (item != ITEM_NONE)
                 CreatePartyMonCustomItemIcon(menuBox, item);
        }
        else
        {
            menuBox->itemSpriteId = CreateSprite(&sSpriteTemplate_HeldItem, GetPartyMenuHeldItemSpriteX(menuBox), GetPartyMenuHeldItemSpriteY(menuBox), 1);
            gSprites[menuBox->itemSpriteId].oam.priority = 1;
            gSprites[menuBox->itemSpriteId].subpriority = 2;
            ApplyPartySlotOffsetToSprite(menuBox, menuBox->itemSpriteId);
            ShowOrHideHeldItemSprite(item, menuBox);
        }
    }
}

static void DestroyPartyMonHeldItemSprite(struct PartyMenuBox *menuBox, u16 tag)
{
    if (menuBox->itemSpriteId >= MAX_SPRITES)
    {
#if TESTING
        sInvalidHeldItemSpriteAccessForTest = TRUE;
#endif
        return;
    }

    FreeSpriteOamMatrix(&gSprites[menuBox->itemSpriteId]);
    DestroySprite(&gSprites[menuBox->itemSpriteId]);
    FreeSpriteTilesByTag(tag);
    FreeSpritePaletteByTag(tag);
}

static bool8 PartyMonHeldItemSpriteUsesGenericIcon(struct PartyMenuBox *menuBox)
{
    if (menuBox->itemSpriteId >= MAX_SPRITES)
    {
#if TESTING
        sInvalidHeldItemSpriteAccessForTest = TRUE;
#endif
        return FALSE;
    }

    return gSprites[menuBox->itemSpriteId].template->tileTag == TAG_HELD_ITEM;
}

static void UpdatePartyMonHeldItemSprite(struct Pokemon *mon, struct PartyMenuBox *menuBox)
{
    u8 slot = menuBox - sPartyMenuBoxes;
    u16 tag = TAG_HELD_ITEM_ICON_BASE + slot;

    if (menuBox->itemSpriteId >= MAX_SPRITES)
        menuBox->itemSpriteId = MAX_SPRITES;

    if (gPartyMenu.action == PARTY_ACTION_GIVE_ITEM || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM || sPartyMenuInternal->inItemMode)
    {
        enum Item item = GetMonData(mon, MON_DATA_HELD_ITEM);

        if (menuBox->itemSpriteId < MAX_SPRITES)
            DestroyPartyMonHeldItemSprite(menuBox, tag);
        menuBox->itemSpriteId = MAX_SPRITES;

        if (item != ITEM_NONE)
        {
            CreatePartyMonCustomItemIcon(menuBox, item);
        }
    }
    else
    {
        if (menuBox->itemSpriteId < MAX_SPRITES)
        {
            if (!PartyMonHeldItemSpriteUsesGenericIcon(menuBox))
            {
                DestroyPartyMonHeldItemSprite(menuBox, tag);
                menuBox->itemSpriteId = MAX_SPRITES;
            }
        }

        if (menuBox->itemSpriteId == MAX_SPRITES && GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
        {
            menuBox->itemSpriteId = CreateSprite(&sSpriteTemplate_HeldItem, GetPartyMenuHeldItemSpriteX(menuBox), GetPartyMenuHeldItemSpriteY(menuBox), 1);
            if (menuBox->itemSpriteId < MAX_SPRITES)
            {
                gSprites[menuBox->itemSpriteId].subpriority = 2;
                ApplyPartySlotOffsetToSprite(menuBox, menuBox->itemSpriteId);
            }
        }

        if (menuBox->itemSpriteId < MAX_SPRITES)
            ShowOrHideHeldItemSprite(GetMonData(mon, MON_DATA_HELD_ITEM), menuBox);
    }
}

#if TESTING
bool32 SwShPartyMenu_TestEmptyHeldItemSlotIsIgnored(bool8 inItemMode)
{
    struct PartyMenuInternal *previousInternal = sPartyMenuInternal;
    struct PartyMenuBox *previousBoxes = sPartyMenuBoxes;
    struct PartyMenuInternal *internal = AllocZeroed(sizeof(*internal));
    struct PartyMenuBox menuBox = {.itemSpriteId = SPRITE_NONE};
    struct Pokemon mon = {0};
    u8 previousAction = gPartyMenu.action;
    bool8 previousInvalidAccess = sInvalidHeldItemSpriteAccessForTest;
    bool32 result;

    if (internal == NULL)
        return FALSE;

    internal->inItemMode = inItemMode;
    sPartyMenuInternal = internal;
    sPartyMenuBoxes = &menuBox;
    gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;
    sInvalidHeldItemSpriteAccessForTest = FALSE;

    UpdatePartyMonHeldItemSprite(&mon, &menuBox);
    result = !sInvalidHeldItemSpriteAccessForTest
          && menuBox.itemSpriteId == MAX_SPRITES;

    sPartyMenuInternal = previousInternal;
    sPartyMenuBoxes = previousBoxes;
    gPartyMenu.action = previousAction;
    sInvalidHeldItemSpriteAccessForTest = previousInvalidAccess;
    Free(internal);
    return result;
}
#endif

static void ShowOrHideHeldItemSprite(enum Item item, struct PartyMenuBox *menuBox)
{
    if (item == ITEM_NONE)
    {
        gSprites[menuBox->itemSpriteId].invisible = TRUE;
    }
    else
    {
        if (ItemIsMail(item))
            StartSpriteAnim(&gSprites[menuBox->itemSpriteId], 1);
        else
            StartSpriteAnim(&gSprites[menuBox->itemSpriteId], 0);
        gSprites[menuBox->itemSpriteId].invisible = FALSE;
    }
}

void LoadHeldItemIcons(void)
{
    LoadSpriteSheet(&gSpriteSheet_HeldItem);
    LoadSpritePalette(&sSpritePalette_HeldItem);
}

static void DestroyMoveTypeSprites(void)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (sMoveTypeSpriteIds[i] != MAX_SPRITES)
        {
            DestroySprite(&gSprites[sMoveTypeSpriteIds[i]]);
            sMoveTypeSpriteIds[i] = MAX_SPRITES;
        }
    }
}

static void DestroyHoverSprite(void)
{
    if (sHoverCursorSpriteId != MAX_SPRITES && sHoverCursorSpriteId != 0)
    {
        DestroySprite(&gSprites[sHoverCursorSpriteId]);
        sHoverCursorSpriteId = MAX_SPRITES;
        if (sPartyMenuInternal != NULL)
        {
            sPartyMenuInternal->offsetCursorSpriteId = MAX_SPRITES;
            sPartyMenuInternal->cursorSpriteOffset = 0;
        }
    }
}

static void InitPartyMenuCursorMove(u8 spriteId, s16 targetX, s16 targetY)
{
    struct ComfyAnimEasingConfig config;

    // Release old anims
    if (sPartyMenuInternal->comfyAnimX != INVALID_COMFY_ANIM)
        ReleaseComfyAnim(sPartyMenuInternal->comfyAnimX);
    if (sPartyMenuInternal->comfyAnimY != INVALID_COMFY_ANIM)
        ReleaseComfyAnim(sPartyMenuInternal->comfyAnimY);

    InitComfyAnimConfig_Easing(&config);
    config.durationFrames = 20;
    config.easingFunc = ComfyAnimEasing_EaseOutCubic;

    // X
    config.from = Q_24_8(gSprites[spriteId].x);
    config.to = Q_24_8(targetX);
    sPartyMenuInternal->comfyAnimX = CreateComfyAnim_Easing(&config);

    // Y
    config.from = Q_24_8(gSprites[spriteId].y);
    config.to = Q_24_8(targetY);
    sPartyMenuInternal->comfyAnimY = CreateComfyAnim_Easing(&config);
}

static void CreateItemIconSprite(struct PartyMenuBox *menuBox, u8 slot, enum Item item)
{
    u8 x = menuBox->spriteCoords[0] - 8;
    u8 y = menuBox->spriteCoords[1];

    if (sItemIconSpriteId != MAX_SPRITES && gSprites[sItemIconSpriteId].inUse)
    {
        InitPartyMenuCursorMove(sItemIconSpriteId, x, y);
    }
    else
    {
        DestroyItemIconSprite();

        sItemIconSpriteId = AddItemIconSprite(TAG_HOVER_ITEM, TAG_HOVER_ITEM, item);

        if (sItemIconSpriteId != MAX_SPRITES)
        {
            gSprites[sItemIconSpriteId].x = x;
            gSprites[sItemIconSpriteId].y = y;
            gSprites[sItemIconSpriteId].oam.priority = 1;
            gSprites[sItemIconSpriteId].subpriority = 2;
            if (sPartyMenuInternal->comfyAnimX != INVALID_COMFY_ANIM)
            {
                ReleaseComfyAnim(sPartyMenuInternal->comfyAnimX);
                sPartyMenuInternal->comfyAnimX = INVALID_COMFY_ANIM;
            }
            if (sPartyMenuInternal->comfyAnimY != INVALID_COMFY_ANIM)
            {
                ReleaseComfyAnim(sPartyMenuInternal->comfyAnimY);
                sPartyMenuInternal->comfyAnimY = INVALID_COMFY_ANIM;
            }
        }
    }
}

static void DestroyItemIconSprite(void)
{
    if (sItemIconSpriteId != MAX_SPRITES && sItemIconSpriteId != 0)
    {
        FreeSpriteTilesByTag(TAG_HOVER_ITEM);
        FreeSpritePaletteByTag(TAG_HOVER_ITEM);
        FreeSpriteOamMatrix(&gSprites[sItemIconSpriteId]);
        DestroySprite(&gSprites[sItemIconSpriteId]);
        sItemIconSpriteId = MAX_SPRITES;
        if (sPartyMenuInternal != NULL)
        {
            sPartyMenuInternal->offsetCursorSpriteId = MAX_SPRITES;
            sPartyMenuInternal->cursorSpriteOffset = 0;
        }
    }
}

static void CreateHoverSprite(struct PartyMenuBox *menuBox, u8 slot)
{
    // Do not show hover cursor in MULTI_SHOWCASE
    if (gPartyMenu.menuType == PARTY_MENU_TYPE_MULTI_SHOWCASE)
    {
        DestroyHoverSprite();
        DestroyItemIconSprite();
        return;
    }

    // When using or giving an item, show the item icon instead of the select cursor
    if (gSpecialVar_ItemId != ITEM_NONE
        && (gPartyMenu.action == PARTY_ACTION_USE_ITEM
            || gPartyMenu.action == PARTY_ACTION_GIVE_ITEM
            || gPartyMenu.action == PARTY_ACTION_MOVE_ITEM
            || gPartyMenu.action == PARTY_ACTION_FUSION)
        )
    {
        DestroyHoverSprite();
        CreateItemIconSprite(menuBox, slot, gSpecialVar_ItemId);
    }
    else
    {
        DestroyItemIconSprite();

        u8 x = menuBox->spriteCoords[0] - 18;
        u8 y = menuBox->spriteCoords[1] + 3;

        if (sHoverCursorSpriteId != MAX_SPRITES && gSprites[sHoverCursorSpriteId].inUse)
        {
            InitPartyMenuCursorMove(sHoverCursorSpriteId, x, y);
        }
        else
        {
            sHoverCursorSpriteId = CreateSprite(&sSpriteTemplate_HoverCursor, x, y, 1);

            if (sHoverCursorSpriteId != MAX_SPRITES)
            {
                gSprites[sHoverCursorSpriteId].oam.priority = 1;
                gSprites[sHoverCursorSpriteId].subpriority = 2;
                if (sPartyMenuInternal->comfyAnimX != INVALID_COMFY_ANIM)
                {
                    ReleaseComfyAnim(sPartyMenuInternal->comfyAnimX);
                    sPartyMenuInternal->comfyAnimX = INVALID_COMFY_ANIM;
                }
                if (sPartyMenuInternal->comfyAnimY != INVALID_COMFY_ANIM)
                {
                    ReleaseComfyAnim(sPartyMenuInternal->comfyAnimY);
                    sPartyMenuInternal->comfyAnimY = INVALID_COMFY_ANIM;
                }
            }
        }
    }
}

// Temp item sprite traveling from mon1 held-item position (fromSlot) to the mon2 (destSlot)
// mon2 held item sprite is updated when the moving sprite finishes animation
static void SpriteCB_ItemSwap(struct Sprite *sprite)
{
    if (++sprite->data[4] > sprite->data[5])
    {
        // Animation done
        u8 destSlot = sprite->data[0];

        FreeSpriteTilesByTag(sprite->data[6]);
        FreeSpritePaletteByTag(sprite->data[6]);
        DestroySprite(sprite);

        // Recreate the item icon at the destination.
        UpdatePartyMonHeldItemSprite(&gPlayerParty[destSlot], &sPartyMenuBoxes[destSlot]);
    }
    else
    {
        s32 currentFrame = sprite->data[4];
        s32 totalFrames = sprite->data[5];
        s32 startX = sprite->data[2];
        s32 startY = sprite->data[3];
        s32 endX = GetPartyMenuHeldItemSpriteX(&sPartyMenuBoxes[sprite->data[0]]);
        s32 endY = GetPartyMenuHeldItemSpriteY(&sPartyMenuBoxes[sprite->data[0]]);

        // Linear interpolation
        sprite->x = startX + (endX - startX) * currentFrame / totalFrames;
        sprite->y = startY + (endY - startY) * currentFrame / totalFrames;

        // Clockwise parabolic curve
        // Vector (dx, dy) = End - Start
        // Clockwise Perpendicular: (dy, -dx)
        {
            s32 dx = endX - startX;
            s32 dy = endY - startY;
            s32 perpX = dy;
            s32 perpY = -dx;

            // Factor t * (1-t) where t = current/total
            s32 term = currentFrame * (totalFrames - currentFrame);
            s32 denom = totalFrames * totalFrames;

            sprite->x += (perpX * term) / denom;
            sprite->y += (perpY * term) / denom;
        }
    }
}

static void InitItemSwapMotion(struct Sprite *sprite, u8 destSlot, u16 tag)
{
    int dx, dy;

    sprite->data[0] = destSlot;
    // data[1] unused
    sprite->data[2] = sprite->x;    // Start X
    sprite->data[3] = sprite->y;    // Start Y
    sprite->data[4] = 0;            // Current Frame
    sprite->data[6] = tag;          // Store tag for cleanup

    // Calc duration based on distance
    dx = GetPartyMenuHeldItemSpriteX(&sPartyMenuBoxes[destSlot]) - sprite->x;
    dy = GetPartyMenuHeldItemSpriteY(&sPartyMenuBoxes[destSlot]) - sprite->y;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    // Duration: 12 to 30 frames
    sprite->data[5] = (dx + dy) / 8 + 12;
    if (sprite->data[5] > 30) sprite->data[5] = 30;

    sprite->callback = SpriteCB_ItemSwap;
}

static void CreateItemMoveSprite(u8 fromSlot, u8 toSlot, enum Item item)
{
    // Animate tasks
    // item1: mon1 (fromSlot) -> mon2 (toSlot)
    // item2: mon2 (toSlot)   -> mon1 (fromSlot)

    // item2 is currently held by fromSlot (mon1) due to the previous data swap
    enum Item item2 = GetMonData(&gPlayerParty[fromSlot], MON_DATA_HELD_ITEM);
    enum Item item1 = item;

    // 1. Reset from item sprite to hover cursor
    DestroyItemIconSprite();
    sItemIconSpriteId = MAX_SPRITES;
    DestroySelectedMonItemSprite();

    DestroyHoverSprite();
    // Create stationary cursor at fromSlot
    sHoverCursorSpriteId = CreateSprite(&sSpriteTemplate_HoverCursor,
                                        sPartyMenuBoxes[fromSlot].spriteCoords[0] - 18,
                                        sPartyMenuBoxes[fromSlot].spriteCoords[1] + 3,
                                        1);
    if (sHoverCursorSpriteId != MAX_SPRITES)
    {
        gSprites[sHoverCursorSpriteId].oam.priority = 1;
        gSprites[sHoverCursorSpriteId].subpriority = 2;
        if (sPartyMenuInternal->comfyAnimX != INVALID_COMFY_ANIM)
        {
            ReleaseComfyAnim(sPartyMenuInternal->comfyAnimX);
            sPartyMenuInternal->comfyAnimX = INVALID_COMFY_ANIM;
        }
        if (sPartyMenuInternal->comfyAnimY != INVALID_COMFY_ANIM)
        {
            ReleaseComfyAnim(sPartyMenuInternal->comfyAnimY);
            sPartyMenuInternal->comfyAnimY = INVALID_COMFY_ANIM;
        }
    }

    // 2. Prep sprites
    // clear existing specific icons before creating animation sprites to make sure
    // UpdatePartyMonHeldItemSprite correctly loads NEW item graphics at anim end
    if (sPartyMenuBoxes[fromSlot].itemSpriteId != MAX_SPRITES)
    {
        u16 tag = TAG_HELD_ITEM_ICON_BASE + fromSlot;
        DestroySprite(&gSprites[sPartyMenuBoxes[fromSlot].itemSpriteId]);
        FreeSpriteTilesByTag(tag);
        FreeSpritePaletteByTag(tag);
        sPartyMenuBoxes[fromSlot].itemSpriteId = MAX_SPRITES;
    }
    if (sPartyMenuBoxes[toSlot].itemSpriteId != MAX_SPRITES)
    {
        u16 tag = TAG_HELD_ITEM_ICON_BASE + toSlot;
        DestroySprite(&gSprites[sPartyMenuBoxes[toSlot].itemSpriteId]);
        FreeSpriteTilesByTag(tag);
        FreeSpritePaletteByTag(tag);
        sPartyMenuBoxes[toSlot].itemSpriteId = MAX_SPRITES;
    }

    // 3. Create anim sprites
    // Sprite 1: item1 (mon1 -> mon2)
    if (item1 != ITEM_NONE)
    {
        u8 spriteId = AddItemIconSprite(TAG_SWITCH_ITEM_1, TAG_SWITCH_ITEM_1, item1);
        if (spriteId != MAX_SPRITES)
        {
            struct Sprite *sprite = &gSprites[spriteId];
            sprite->x = GetPartyMenuHeldItemSpriteX(&sPartyMenuBoxes[fromSlot]);
            sprite->y = GetPartyMenuHeldItemSpriteY(&sPartyMenuBoxes[fromSlot]);
            sprite->oam.priority = 1;
            sprite->subpriority = 1;
            InitItemSwapMotion(sprite, toSlot, TAG_HOVER_CURSOR + 20);
        }
    }

    // Sprite 2: item2 (mon2 -> mon1)
    if (item2 != ITEM_NONE)
    {
        u8 spriteId = AddItemIconSprite(TAG_SWITCH_ITEM_2, TAG_SWITCH_ITEM_2, item2);
        if (spriteId != MAX_SPRITES)
        {
            struct Sprite *sprite = &gSprites[spriteId];
            sprite->x = GetPartyMenuHeldItemSpriteX(&sPartyMenuBoxes[toSlot]);
            sprite->y = GetPartyMenuHeldItemSpriteY(&sPartyMenuBoxes[toSlot]);
            sprite->oam.priority = 1;
            sprite->subpriority = 1;
            InitItemSwapMotion(sprite, fromSlot, TAG_SWITCH_ITEM_2);
        }
    }
}

void DrawHeldItemIconsForTrade(u8 *partyCounts, u8 *partySpriteIds, u8 whichParty)
{
    u16 i;
    enum Item item;

    switch (whichParty)
    {
    case TRADE_PLAYER:
        for (i = 0; i < partyCounts[TRADE_PLAYER]; i++)
        {
            item = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
            if (item != ITEM_NONE)
                CreateHeldItemSpriteForTrade(partySpriteIds[i], ItemIsMail(item));
        }
        break;
    case TRADE_PARTNER:
        for (i = 0; i < partyCounts[TRADE_PARTNER]; i++)
        {
            item = GetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM);
            if (item != ITEM_NONE)
                CreateHeldItemSpriteForTrade(partySpriteIds[i + PARTY_SIZE], ItemIsMail(item));
        }
        break;
    }
}

static void CreateHeldItemSpriteForTrade(u8 spriteId, bool8 isMail)
{
    u8 newSpriteId = CreateSprite(&sSpriteTemplate_HeldItem, 250, 170, 4);

    gSprites[newSpriteId].x2 = 4;
    gSprites[newSpriteId].y2 = 10;
    gSprites[newSpriteId].callback = SpriteCB_HeldItem;
    gSprites[newSpriteId].data[7] = spriteId;
    StartSpriteAnim(&gSprites[newSpriteId], isMail);
    gSprites[newSpriteId].callback(&gSprites[newSpriteId]);
}

static void SpriteCB_HeldItem(struct Sprite *sprite)
{
    u8 otherSpriteId = sprite->data[7];

    if (gSprites[otherSpriteId].invisible)
    {
        sprite->invisible = TRUE;
    }
    else
    {
        sprite->invisible = FALSE;
        sprite->x = gSprites[otherSpriteId].x + gSprites[otherSpriteId].x2;
        sprite->y = gSprites[otherSpriteId].y + gSprites[otherSpriteId].y2;
    }
}

static void PartyMenuStartSpriteAnim(u8 spriteId, u8 animNum)
{
    if (spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
        StartSpriteAnim(&gSprites[spriteId], animNum);
}

#if TESTING
bool32 SwShPartyMenu_TestMissingSlotSpritesAreIgnored(void)
{
    struct Sprite dummySprite = gSprites[MAX_SPRITES];
    struct PartyMenuBox menuBox =
    {
        .monSpriteId = MAX_SPRITES,
        .itemSpriteId = MAX_SPRITES,
        .pokeballSpriteId = SPRITE_NONE,
        .statusSpriteId = MAX_SPRITES,
    };
    u8 spriteId1 = SPRITE_NONE;
    u8 spriteId2 = MAX_SPRITES;
    bool32 result;

    gSprites[MAX_SPRITES].x = 1234;
    gSprites[MAX_SPRITES].y = -1234;
    gSprites[MAX_SPRITES].x2 = 2345;
    gSprites[MAX_SPRITES].y2 = -2345;
    gSprites[MAX_SPRITES].animNum = 3;
    gSprites[MAX_SPRITES].inUse = FALSE;

    MovePartyMenuBoxSprites(&menuBox, 1);
    SwitchMenuBoxSprites(&spriteId1, &spriteId2);
    PartyMenuStartSpriteAnim(MAX_SPRITES, 1);
    PartyMenuStartSpriteAnim(SPRITE_NONE, 1);

    result = spriteId1 == MAX_SPRITES
        && spriteId2 == SPRITE_NONE
        && gSprites[MAX_SPRITES].x == 1234
        && gSprites[MAX_SPRITES].y == -1234
        && gSprites[MAX_SPRITES].x2 == 2345
        && gSprites[MAX_SPRITES].y2 == -2345
        && gSprites[MAX_SPRITES].animNum == 3;
    gSprites[MAX_SPRITES] = dummySprite;
    return result;
}
#endif

// Sprite bg for message window
static void CreateMessageWindowSprite(void)
{
    s16 x=16;
    s16 y=128;
    int i;
    u8 spriteId;

    if (sMessageWindowSpriteIds[0] != MAX_SPRITES)
        return;

    for (i = 0; i < ARRAY_COUNT(sMessageWindowSpriteIds); i++)
    {
        u8 row = i / 8;
        u8 col = i % 8;
        u8 animNum;
        s16 spriteX, spriteY;

        if (col <= 4)
            spriteX = x + (col * 32);
        else
            spriteX = x + (4 * 32) + 16 + ((col - 5) * 32);

        spriteY = y + (row * 16);

        if (col == 0) // Left edge
            animNum = (row == 0) ? 0 : 3;
        else if (col == 7) // Right edge
            animNum = (row == 0) ? 2 : 5;
        else // Middle body
            animNum = (row == 0) ? 1 : 4;

        spriteId = CreateSprite(&sSpriteTemplate_MessageWindow, spriteX, spriteY, 0);
        if (spriteId != MAX_SPRITES)
        {
            StartSpriteAnim(&gSprites[spriteId], animNum);
            gSprites[spriteId].oam.priority = 1;
            gSprites[spriteId].subpriority = 0;
            sMessageWindowSpriteIds[i] = spriteId;
        }
    }
}

static void DestroyMessageWindowSprite(void)
{
    int i;
    for (i = 0; i < ARRAY_COUNT(sMessageWindowSpriteIds); i++)
    {
        if (sMessageWindowSpriteIds[i] != MAX_SPRITES)
        {
            DestroySprite(&gSprites[sMessageWindowSpriteIds[i]]);
            sMessageWindowSpriteIds[i] = MAX_SPRITES;
        }
    }
}

static void CreateMultiuseWindowSprite(void)
{
    s16 x=160;
    s16 y=88;
    int i;
    u8 spriteId;

    if (sMultiuseWindowSpriteIds[0] != MAX_SPRITES)
        return;

    for (i = 0; i < ARRAY_COUNT(sMultiuseWindowSpriteIds); i++)
    {
        u8 animNum;
        s16 spriteX = x + ((i % 3) * 32);
        s16 spriteY = (i < 3) ? y : y + 16;

        if (i < 3) // Top row
            animNum = (i == 0) ? 0 : 1;
        else // Bottom row
            animNum = (i == 3) ? 2 : 3;

        spriteId = CreateSprite(&sSpriteTemplate_MultiuseWindow, spriteX, spriteY, 0);
        if (spriteId != MAX_SPRITES)
        {
            StartSpriteAnim(&gSprites[spriteId], animNum);
            gSprites[spriteId].oam.priority = 1;
            gSprites[spriteId].subpriority = 0;
            sMultiuseWindowSpriteIds[i] = spriteId;
        }
    }
}

static void DestroyMultiuseWindowSprite(void)
{
    int i;
    for (i = 0; i < ARRAY_COUNT(sMultiuseWindowSpriteIds); i++)
    {
        if (sMultiuseWindowSpriteIds[i] != MAX_SPRITES)
        {
            DestroySprite(&gSprites[sMultiuseWindowSpriteIds[i]]);
            sMultiuseWindowSpriteIds[i] = MAX_SPRITES;
        }
    }
}

static void DestroySelectFrame(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sSelectFrameSpriteIds); i++)
    {
        if (sSelectFrameSpriteIds[i] != MAX_SPRITES)
        {
            DestroySprite(&gSprites[sSelectFrameSpriteIds[i]]);
            sSelectFrameSpriteIds[i] = MAX_SPRITES;
        }
    }
}

static void CreateSelectFrame(struct PartyMenuBox *menuBox, u8 slot)
{
    u8 i;
    s16 x = menuBox->spriteCoords[0] - 10;
    s16 y = menuBox->spriteCoords[1] + 7;

    DestroySelectFrame();

    for (i = 0; i < ARRAY_COUNT(sSelectFrameSpriteIds); i++)
    {
        u8 animNum;
        s16 spriteX = x;

        if (i == 0) // Left end
            animNum = 0;
        else if (i == ARRAY_COUNT(sSelectFrameSpriteIds) - 1) // Right end
        {
            animNum = 1;
            spriteX = x + 16 + (5 * 16);
        }
        else // Middle
        {
            animNum = 2;
            spriteX = x + 16 + ((i - 1) * 16);
        }

        sSelectFrameSpriteIds[i] = CreateSprite(&sSpriteTemplate_SelectFrame, spriteX, y, 1);
        if (sSelectFrameSpriteIds[i] != MAX_SPRITES)
        {
            StartSpriteAnim(&gSprites[sSelectFrameSpriteIds[i]], animNum);
            gSprites[sSelectFrameSpriteIds[i]].oam.priority = 1;
            gSprites[sSelectFrameSpriteIds[i]].subpriority = 6;
        }
    }
}

static void CreatePartyMonStatusSprite(struct Pokemon *mon, struct PartyMenuBox *menuBox)
{
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE)
    {
        menuBox->statusSpriteId = CreateSprite(&gSpriteTemplate_StatusIcons, menuBox->spriteCoords[4], menuBox->spriteCoords[5], 1);
        if (menuBox->statusSpriteId != MAX_SPRITES)
        {
            gSprites[menuBox->statusSpriteId].oam.priority = 1;
            gSprites[menuBox->statusSpriteId].subpriority = 2;
            ApplyPartySlotOffsetToSprite(menuBox, menuBox->statusSpriteId);
        }
        SetPartyMonAilmentGfx(mon, menuBox);
    }
}

static void CreatePartyMonStatusSpriteParameterized(u16 species, u8 status, struct PartyMenuBox *menuBox)
{
    if (species != SPECIES_NONE)
    {
        menuBox->statusSpriteId = CreateSprite(&gSpriteTemplate_StatusIcons, menuBox->spriteCoords[4], menuBox->spriteCoords[5], 1);
        UpdatePartyMonAilmentGfx(status, menuBox);
        gSprites[menuBox->statusSpriteId].oam.priority = 1;
        gSprites[menuBox->statusSpriteId].subpriority = 3;
        ApplyPartySlotOffsetToSprite(menuBox, menuBox->statusSpriteId);
    }
}

static void SetPartyMonAilmentGfx(struct Pokemon *mon, struct PartyMenuBox *menuBox)
{
    UpdatePartyMonAilmentGfx(GetMonAilment(mon), menuBox);
}

static u8 LoadMonGfxAndSprite(struct Pokemon *mon, s16 *state, bool32 isShadow)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
    u32 pid = GetMonData(mon, MON_DATA_PERSONALITY);
    bool8 isShiny = GetMonData(mon, MON_DATA_IS_SHINY);

    switch (*state)
    {
    default:
        return CreateMonSprite(mon, isShadow);
    case 0:
        if (gMonSpritesGfxPtr != NULL)
        {
            HandleLoadSpecialPokePic(TRUE,
                                     gMonSpritesGfxPtr->spritesGfx[B_POSITION_OPPONENT_LEFT],
                                     species,
                                     pid);
        }
        else
        {
            HandleLoadSpecialPokePic(TRUE,
                                     MonSpritesGfxManager_GetSpritePtr(MON_SPR_GFX_MANAGER_A, B_POSITION_OPPONENT_LEFT),
                                     species,
                                     pid);
        }
        (*state)++;
        return 0xFF;
    case 1:
        LoadSpritePaletteWithTag(GetMonSpritePalFromSpeciesAndPersonality(species, isShiny, pid), species);
        SetMultiuseSpriteTemplateToPokemon(species, B_POSITION_OPPONENT_LEFT);
        (*state)++;
        return 0xFF;
    }
}

// Mon sprite data fields
#define sSpecies data[0]
#define sDontFlip data[1]
#define sDelayAnim data[2]
#define sIsShadow data[3]
#define sIsEgg data[4]      // for passing into onFrame in PokemonSummaryDoMonAnimation

static u8 CreateMonSprite(struct Pokemon *mon, bool32 isShadow)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
    u8 shadowPalette = 0;
    u8 spriteId = CreateSprite(&gMultiuseSpriteTemplate, SWSH_PARTY_FRONT_SPRITE_X, SWSH_PARTY_FRONT_SPRITE_Y, 5);

    if (spriteId != MAX_SPRITES)
    {
        FreeSpriteOamMatrix(&gSprites[spriteId]);
        gSprites[spriteId].sSpecies = species;
        gSprites[spriteId].sDelayAnim = 0;
        gSprites[spriteId].sIsShadow = isShadow;
        gSprites[spriteId].sIsEgg = GetMonData(mon, MON_DATA_IS_EGG);
        gSprites[spriteId].oam.priority = 1;
        if (isShadow)
        {
            gSprites[spriteId].subpriority = 7;
        }
        else
        {
            gSprites[spriteId].subpriority = 6;
        }
        gSprites[spriteId].callback = SpriteCB_PartyMonPokemon;
        if (isShadow)
        {
            FreeSpritePaletteByTag(TAG_MON_SHADOW);
            shadowPalette = LoadSpritePalette(&sSpritePal_PartyMonShadow);
            gSprites[spriteId].oam.paletteNum = shadowPalette;
            gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
            gSprites[spriteId].x += 5;
            gSprites[spriteId].y += 2;
        }
    }

    return spriteId;
}

static void DestroyMonSprite(void)
{
    DestroySelectedMonItemSprite();

    if (sMonSpriteId != 0 && sMonSpriteId != MAX_SPRITES)
    {
        StopPokemonAnimationDelayTask();
        DestroySpriteAndFreeResources(&gSprites[sMonSpriteId]);
        sMonSpriteId = MAX_SPRITES;
    }
    if (sMonShadowSpriteId != 0 && sMonShadowSpriteId != MAX_SPRITES)
    {
        StopPokemonAnimationDelayTask();
        DestroySpriteAndFreeResources(&gSprites[sMonShadowSpriteId]);
        sMonShadowSpriteId = MAX_SPRITES;
    }
}

static void SpriteCB_PartyMonPokemon(struct Sprite *sprite)
{
    if (!gPaletteFade.active && sprite->sDelayAnim != 1)
    {
        sprite->sDontFlip = TRUE;
        PokemonSummaryDoMonAnimation(sprite, sprite->sSpecies, sprite->sIsEgg);
        // PokemonSummaryDoMonAnimation(sprite, sprite->sSpecies, sprite->sIsEgg, sprite->sIsShadow); // use this if already using swsh_summary_screen branch
    }
}

static void RunMonAnimTimer(void)
{
    u32 i;

    if (sMonSpriteId != SPRITE_NONE && gSprites[sMonSpriteId].callback == SpriteCallbackDummy) // mon anim is finished
    {
        // Sanitize OAM bits to prevent the shared animation engine's flipping bug
        gSprites[sMonSpriteId].oam.matrixNum = (gSprites[sMonSpriteId].hFlip << 3) | (gSprites[sMonSpriteId].vFlip << 4);
        if (sMonShadowSpriteId != SPRITE_NONE)
            gSprites[sMonShadowSpriteId].oam.matrixNum = (gSprites[sMonShadowSpriteId].hFlip << 3) | (gSprites[sMonShadowSpriteId].vFlip << 4);

        sMonAnimTimer++;
    }

    if (sMonAnimTimer > SWSH_PARTY_MON_IDLE_ANIMS_FRAMES && sMonSpriteId != SPRITE_NONE) // time to re-run the anim
    {
        // Clear animation data for both sprites
        for (i = 1; i < 8; i++)
        {
            gSprites[sMonSpriteId].data[i] = 0;
            if (sMonShadowSpriteId != SPRITE_NONE)
                gSprites[sMonShadowSpriteId].data[i] = 0;
        }

        // Restore species and shadow flags for both sprites
        gSprites[sMonSpriteId].sSpecies = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES_OR_EGG);
        gSprites[sMonSpriteId].sIsShadow = FALSE;
        gSprites[sMonSpriteId].sIsEgg = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_IS_EGG);

        if (sMonShadowSpriteId != SPRITE_NONE)
        {
            gSprites[sMonShadowSpriteId].sSpecies = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES_OR_EGG);
            gSprites[sMonShadowSpriteId].sIsShadow = TRUE;
            gSprites[sMonShadowSpriteId].sIsEgg = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_IS_EGG);
        }

        // Restart animation for both sprites
        gSprites[sMonSpriteId].callback = SpriteCB_PartyMonPokemon;
        if (sMonShadowSpriteId != SPRITE_NONE)
            gSprites[sMonShadowSpriteId].callback = SpriteCB_PartyMonPokemon;

        sMonAnimTimer = 0;
    }
}

#undef sSpecies
#undef sDontFlip
#undef sDelayAnim
#undef sIsShadow
#undef sIsEgg

static void UpdatePartyMonAilmentGfx(u8 status, struct PartyMenuBox *menuBox)
{
    switch (status)
    {
    case AILMENT_NONE:
    case AILMENT_PKRS:
        gSprites[menuBox->statusSpriteId].invisible = TRUE;
        break;
    default:
        StartSpriteAnim(&gSprites[menuBox->statusSpriteId], status - 1);
        gSprites[menuBox->statusSpriteId].invisible = FALSE;
        break;
    }
}

void LoadPartyMenuAilmentGfx(void)
{
    LoadCompressedSpriteSheet(&sSpriteSheet_StatusIcons);
    LoadSpritePalette(&sSpritePalette_StatusIcons);
}

void CB2_ShowPartyMenuForItemUse(void)
{
    MainCallback callback = CB2_ReturnToBagMenu;
    u8 partyLayout;
    u8 menuType;
    u8 i;
    u8 msgId;
    TaskFunc task;

    if (gPartyMenu.data1 == DATA1_PARTY_MENU_FROM_FIELD)
    {
        callback = CB2_ReturnToField;
        gPartyMenu.data1 = 0;
    }

    if (gMain.inBattle)
    {
        menuType = PARTY_MENU_TYPE_IN_BATTLE;
        partyLayout = GetPartyLayoutFromBattleType();
    }
    else
    {
        menuType = PARTY_MENU_TYPE_FIELD;
        partyLayout = PARTY_LAYOUT_SINGLE;
    }

    if (GetItemEffectType(gSpecialVar_ItemId) == ITEM_EFFECT_SACRED_ASH)
    {
        gPartyMenu.slotId = 0;
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE && GetMonData(&gPlayerParty[i], MON_DATA_HP) == 0)
            {
                gPartyMenu.slotId = i;
                break;
            }
        }
        task = Task_SetSacredAshCB;
        msgId = PARTY_MSG_NONE;
    }
    else
    {
        if (GetItemPocket(gSpecialVar_ItemId) == POCKET_TM_HM)
            msgId = PARTY_MSG_TEACH_WHICH_MON;
        else
            msgId = PARTY_MSG_USE_ON_WHICH_MON;

        task = Task_HandleChooseMonInput;
    }

    InitPartyMenu(menuType, partyLayout, PARTY_ACTION_USE_ITEM, TRUE, msgId, task, callback);
}

static void CB2_ReturnToBagMenu(void)
{
    if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
        GoToBagMenu(ITEMMENULOCATION_LAST, POCKETS_COUNT, NULL);
    else
        GoToBattlePyramidBagMenu(PYRAMIDBAG_LOC_PREV, gPyramidBagMenuState.exitCallback);
}

static void Task_SetSacredAshCB(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (gPartyMenu.menuType == PARTY_MENU_TYPE_IN_BATTLE)
            sPartyMenuInternal->exitCallback = CB2_SetUpExitToBattleScreen;
        gItemUseCB(taskId, Task_ClosePartyMenuAfterText); // ItemUseCB_SacredAsh in this case
    }
}

static bool32 IsHPRecoveryItem(enum Item item)
{
    const u8 *effect = GetItemEffect(item);

    if (effect == NULL)
        return FALSE;

    if (effect[4] & ITEM4_HEAL_HP)
        return TRUE;
    else
        return FALSE;
}

static void GetMedicineItemEffectMessage(enum Item item, u32 statusCured)
{
    switch (GetItemEffectType(item))
    {
    case ITEM_EFFECT_CURE_POISON:
        StringExpandPlaceholders(gStringVar4, gText_PkmnCuredOfPoison);
        break;
    case ITEM_EFFECT_CURE_SLEEP:
        StringExpandPlaceholders(gStringVar4, gText_PkmnWokeUp2);
        break;
    case ITEM_EFFECT_CURE_BURN:
        StringExpandPlaceholders(gStringVar4, gText_PkmnBurnHealed);
        break;
    case ITEM_EFFECT_CURE_FREEZE_FROSTBITE:
        if (statusCured & STATUS1_FREEZE)
            StringExpandPlaceholders(gStringVar4, gText_PkmnThawedOut);
        if (statusCured & STATUS1_FROSTBITE)
            StringExpandPlaceholders(gStringVar4, gText_PkmnFrostbiteHealed);
        break;
    case ITEM_EFFECT_CURE_PARALYSIS:
        StringExpandPlaceholders(gStringVar4, gText_PkmnCuredOfParalysis);
        break;
    case ITEM_EFFECT_CURE_CONFUSION:
        StringExpandPlaceholders(gStringVar4, gText_PkmnSnappedOutOfConfusion);
        break;
    case ITEM_EFFECT_CURE_INFATUATION:
        StringExpandPlaceholders(gStringVar4, gText_PkmnGotOverInfatuation);
        break;
    case ITEM_EFFECT_CURE_ALL_STATUS:
        StringExpandPlaceholders(gStringVar4, gText_PkmnBecameHealthy);
        break;
    case ITEM_EFFECT_HP_EV:
        StringCopy(gStringVar2, gText_HP3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_ATK_EV:
        StringCopy(gStringVar2, gText_Attack3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_DEF_EV:
        StringCopy(gStringVar2, gText_Defense3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_SPEED_EV:
        StringCopy(gStringVar2, gText_Speed2);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_SPATK_EV:
        StringCopy(gStringVar2, gText_SpAtk3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_SPDEF_EV:
        StringCopy(gStringVar2, gText_SpDef3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_HP_IV:
        StringCopy(gStringVar2, gText_HP3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_ATK_IV:
        StringCopy(gStringVar2, gText_Attack3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_DEF_IV:
        StringCopy(gStringVar2, gText_Defense3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_SPEED_IV:
        StringCopy(gStringVar2, gText_Speed2);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_SPATK_IV:
        StringCopy(gStringVar2, gText_SpAtk3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_SPDEF_IV:
        StringCopy(gStringVar2, gText_SpDef3);
        StringExpandPlaceholders(gStringVar4, gText_PkmnBaseVar2StatIncreased);
        break;
    case ITEM_EFFECT_HP_IV_REDUCE:
    case ITEM_EFFECT_ATK_IV_REDUCE:
    case ITEM_EFFECT_DEF_IV_REDUCE:
    case ITEM_EFFECT_SPEED_IV_REDUCE:
    case ITEM_EFFECT_SPATK_IV_REDUCE:
    case ITEM_EFFECT_SPDEF_IV_REDUCE:
        ItemEffectToStatString(GetItemEffectType(item), gStringVar2);
        StringExpandPlaceholders(gStringVar4, gText_PkmnVar2IVWasLowered);
        break;
    case ITEM_EFFECT_PP_UP:
    case ITEM_EFFECT_PP_MAX:
        StringExpandPlaceholders(gStringVar4, gText_MovesPPIncreased);
        break;
    case ITEM_EFFECT_HEAL_PP:
        StringExpandPlaceholders(gStringVar4, gText_PPWasRestored);
        break;
    default:
        StringExpandPlaceholders(gStringVar4, gText_WontHaveEffect);
        break;
    }
}

static bool32 NotUsingHPEVItemOnShedinja(struct Pokemon *mon, enum Item item)
{
    if (GetItemEffectType(item) == ITEM_EFFECT_HP_EV && GetMonData(mon, MON_DATA_SPECIES) == SPECIES_SHEDINJA)
        return FALSE;
    return TRUE;
}

static bool32 IsItemFlute(enum Item item)
{
    if (item == ITEM_BLUE_FLUTE || item == ITEM_RED_FLUTE || item == ITEM_YELLOW_FLUTE)
        return TRUE;
    return FALSE;
}

// Battle scripts called in HandleAction_UseItem
void ItemUseCB_BattleScript(u8 taskId, TaskFunc task)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    if (CannotUseItemsInBattle(gSpecialVar_ItemId, mon))
    {
        gPartyMenuUseExitCallback = FALSE;
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = task;
    }
    else
    {
        gBattleStruct->itemPartyIndex[gBattlerInMenuId] = GetPartyIdFromBattleSlot(gPartyMenu.slotId);
        gPartyMenuUseExitCallback = TRUE;
        PlaySE(SE_SELECT);
        if (!IsItemFlute(gSpecialVar_ItemId))
            RemoveBagItem(gSpecialVar_ItemId, 1);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = task;
    }
}

void ItemUseCB_BattleChooseMove(u8 taskId, TaskFunc task)
{
    PlaySE(SE_SELECT);
    ShowMoveSelectWindow(gPartyMenu.slotId);
    gTasks[taskId].func = Task_HandleWhichMoveInput;
}

void ItemUseCB_Medicine(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    u16 hp = 0;
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = gSpecialVar_ItemId;
    bool8 canHeal = FALSE;
    bool8 cannotUse;
    u32 oldStatus = GetMonData(mon, MON_DATA_STATUS);
    tItemEffect = GetItemEffectType(item);
    u16 ev = ItemEffectToMonEv(mon, tItemEffect);
    tQuantityInBag = CountTotalItemQuantityInBag(gSpecialVar_ItemId);
    tItemCount = 1;

    if (NotUsingHPEVItemOnShedinja(mon, item) == FALSE)
    {
        cannotUse = TRUE;
    }
    else
    {
        canHeal = IsHPRecoveryItem(item);
        if (canHeal == TRUE)
        {
            hp = GetMonData(mon, MON_DATA_HP);
            if (hp == GetMonData(mon, MON_DATA_MAX_HP))
                canHeal = FALSE;
        }
        cannotUse = ExecuteTableBasedItemEffect(mon, item, gPartyMenu.slotId, 0, 0, 1);
    }

    if (cannotUse != FALSE)
    {
        gPartyMenuUseExitCallback = FALSE;
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        if (gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD)
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        else
            gTasks[taskId].func = task;
        return;
    }
    else
    {
        if (DoesItemReduceIV(tItemEffect))
        {
            tMaxItemQuantity = min(ItemEffectToMonIV(mon, tItemEffect), tQuantityInBag);
            if (tMaxItemQuantity > 1)
            {
                PlaySE(SE_SELECT);
                DisplayGiveHowManyMessage();
                gTasks[taskId].func = Task_GiveHowManyItems;
            }
            else
            {
                ItemUse_ApplyIVReduceHerb(taskId);
            }
            return;
        }

        if (DoesItemIncreaseEV(tItemEffect) && tQuantityInBag > 1 && GetItemEffect(item)[6] != ITEM6_MAX_EV)
        {
            PlaySE(SE_SELECT);
            DisplayGiveHowManyMessage();

            u32 evIncrease = GetItemEffect(item)[6];
            u32 evCount = GetMonEVCount(mon);
            u32 maxAllowedEVs = B_EV_ITEMS_CAP ? GetCurrentEVCap() : MAX_TOTAL_EVS;

            u32 remainingStatEVs  = MAX_PER_STAT_EVS - ev;
            u32 remainingTotalEVs = maxAllowedEVs - evCount;

            u32 maxQuantityByStat  = (remainingStatEVs  + evIncrease - 1) / evIncrease;
            u32 maxQuantityByTotal = (remainingTotalEVs + evIncrease - 1) / evIncrease;

            tMaxItemQuantity = min(maxQuantityByStat, min(maxQuantityByTotal, tQuantityInBag));

            gTasks[taskId].func = Task_GiveHowManyItems;
        }
        else
        {
            switch (tItemEffect)
            {
            case ITEM_EFFECT_HP_EV:
            case ITEM_EFFECT_ATK_EV:
            case ITEM_EFFECT_DEF_EV:
            case ITEM_EFFECT_SPEED_EV:
            case ITEM_EFFECT_SPATK_EV:
            case ITEM_EFFECT_SPDEF_EV:
            case ITEM_EFFECT_HP_IV:
            case ITEM_EFFECT_ATK_IV:
            case ITEM_EFFECT_DEF_IV:
            case ITEM_EFFECT_SPEED_IV:
            case ITEM_EFFECT_SPATK_IV:
            case ITEM_EFFECT_SPDEF_IV:
                ExecuteTableBasedItemEffect(mon, item, gPartyMenu.slotId, 0, 1, 1);
                break;
            default:
                break;
            }
            gPartyMenuUseExitCallback = TRUE;
            if (!IsItemFlute(item))
            {
                PlaySE(SE_USE_ITEM);
                RemoveBagItem(item, 1);
            }
            else
            {
                PlaySE(SE_GLASS_FLUTE);
            }
            switch (tItemEffect)
            {
            case ITEM_EFFECT_HP_EV:
            case ITEM_EFFECT_HP_IV:
                UpdateMonDisplayInfoAfterRareCandy(gPartyMenu.slotId, mon);
                break;
            case ITEM_EFFECT_ATK_EV:
            case ITEM_EFFECT_DEF_EV:
            case ITEM_EFFECT_SPEED_EV:
            case ITEM_EFFECT_SPATK_EV:
            case ITEM_EFFECT_SPDEF_EV:
            case ITEM_EFFECT_ATK_IV:
            case ITEM_EFFECT_DEF_IV:
            case ITEM_EFFECT_SPEED_IV:
            case ITEM_EFFECT_SPATK_IV:
            case ITEM_EFFECT_SPDEF_IV:
                break;
            default:
                SetPartyMonAilmentGfx(mon, &sPartyMenuBoxes[gPartyMenu.slotId]);
                if (gSprites[sPartyMenuBoxes[gPartyMenu.slotId].statusSpriteId].invisible)
                    DisplayPartyPokemonLevelCheck(mon, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
                break;
            }
            if (canHeal == TRUE)
            {
                if (hp == 0)
                    AnimatePartySlot(gPartyMenu.slotId, 1);
                PartyMenuModifyHP(taskId, gPartyMenu.slotId, 1, GetMonData(mon, MON_DATA_HP) - hp, Task_DisplayHPRestoredMessage);
                ResetHPTaskData(taskId, 0, hp);
                return;
            }
            else
            {
                GetMonNickname(mon, gStringVar1);
                GetMedicineItemEffectMessage(item, oldStatus);
                DisplayPartyMenuMessage(gStringVar4, TRUE);
                ScheduleBgCopyTilemapToVram(2);
                if (gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD && CheckBagHasItem(item, 1))
                    gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
                else
                    gTasks[taskId].func = task;
            }
        }
    }
}

#define tState      data[0]
#define tMonId      data[1]
#define tNextFunc   2

static void Task_ChangePokeball(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    struct Pokemon *mon = &gPlayerParty[tMonId];
    enum ChangeMonPokeballResult result;

    switch (tState)
    {
    case 0:
        result = CanChangeMonPokeball(mon, gSpecialVar_ItemId);
        if (result != CHANGE_MON_POKEBALL_SUCCESS)
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_FAILURE);
            if (result == CHANGE_MON_POKEBALL_SAME_BALL)
                StringExpandPlaceholders(gStringVar4, sText_PokeballAlreadyMatches);
            else
                StringExpandPlaceholders(gStringVar4, gText_WontHaveEffect);
            DisplayPartyMenuMessage(gStringVar4, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
            return;
        }

        gPartyMenuUseExitCallback = TRUE;
        GetMonNickname(mon, gStringVar1);
        CopyItemName(gSpecialVar_ItemId, gStringVar2);
        StringExpandPlaceholders(gStringVar4, sText_ChangePokeballAsk);
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 1:
        if (!IsPartyMenuTextPrinterActive())
        {
            PartyMenuDisplayYesNoMenu();
            tState++;
        }
        break;
    case 2:
        switch (Menu_ProcessInputNoWrapClearOnChoose())
        {
        case 0:
            result = TryChangeMonPokeball(mon, gSpecialVar_ItemId);
            if (result == CHANGE_MON_POKEBALL_SUCCESS)
            {
                PlaySE(SE_USE_ITEM);
                GetMonNickname(mon, gStringVar1);
                CopyItemName(gSpecialVar_ItemId, gStringVar2);
                StringExpandPlaceholders(gStringVar4, sText_ChangePokeballDone);
                gTasks[taskId].func = (void *)GetWordTaskArg(taskId, tNextFunc);
            }
            else
            {
                gPartyMenuUseExitCallback = FALSE;
                PlaySE(SE_FAILURE);
                if (result == CHANGE_MON_POKEBALL_SAME_BALL)
                    StringExpandPlaceholders(gStringVar4, sText_PokeballAlreadyMatches);
                else
                    StringExpandPlaceholders(gStringVar4, gText_WontHaveEffect);
                gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
            }
            DisplayPartyMenuMessage(gStringVar4, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            break;
        case 1:
        case MENU_B_PRESSED:
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            ScheduleBgCopyTilemapToVram(2);
            Task_ReturnToChooseMonAfterText(taskId);
            break;
        }
        break;
    }
}

void ItemUseCB_ChangePokeball(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    tState = 0;
    tMonId = gPartyMenu.slotId;
    SetWordTaskArg(taskId, tNextFunc, (uintptr_t)task);
    gTasks[taskId].func = Task_ChangePokeball;
}

#undef tState
#undef tMonId
#undef tNextFunc

#define tState      data[0]
#define tSpecies    data[1]
#define tAbilityNum data[2]
#define tMonId      data[3]
#define tOldFunc    4

void Task_AbilityCapsule(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        // Can't use.
        if (GetSpeciesAbility(tSpecies, 0) == GetSpeciesAbility(tSpecies, 1)
            || GetSpeciesAbility(tSpecies, 1) == 0
            || tAbilityNum > 1
            || !tSpecies)
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            DisplayPartyMenuMessage(gText_WontHaveEffect, 1);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            return;
        }
        gPartyMenuUseExitCallback = TRUE;
        GetMonNickname(&gPlayerParty[tMonId], gStringVar1);
        StringCopy(gStringVar2, gAbilitiesInfo[GetAbilityBySpecies(tSpecies, tAbilityNum)].name);
        StringExpandPlaceholders(gStringVar4, sText_askText);
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gStringVar4, 1);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 1:
        if (!IsPartyMenuTextPrinterActive())
        {
            PartyMenuDisplayYesNoMenu();
            tState++;
        }
        break;
    case 2:
        switch (Menu_ProcessInputNoWrapClearOnChoose())
        {
        case 0:
            tState++;
            break;
        case 1:
        case MENU_B_PRESSED:
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            ScheduleBgCopyTilemapToVram(2);
            // Don't exit party selections screen, return to choosing a mon.
            ClearStdWindowAndFrameToTransparent(6, 0);
            ClearWindowTilemap(6);
            DestroyMessageWindowSprite();
            gTasks[taskId].func = (void *)GetWordTaskArg(taskId, tOldFunc);
            return;
        }
        break;
    case 3:
        PlaySE(SE_USE_ITEM);
        StringExpandPlaceholders(gStringVar4, sText_doneText);
        DisplayPartyMenuMessage(gStringVar4, 1);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 4:
        if (!IsPartyMenuTextPrinterActive())
            tState++;
        break;
    case 5:
        SetMonData(&gPlayerParty[tMonId], MON_DATA_ABILITY_NUM, &tAbilityNum);
        RemoveBagItem(gSpecialVar_ItemId, 1);
        gTasks[taskId].func = Task_ClosePartyMenu;
        break;
    }
}

void ItemUseCB_AbilityCapsule(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    tState = 0;
    tMonId = gPartyMenu.slotId;
    tSpecies = GetMonData(&gPlayerParty[tMonId], MON_DATA_SPECIES);
    tAbilityNum = GetMonData(&gPlayerParty[tMonId], MON_DATA_ABILITY_NUM) ^ 1;
    SetWordTaskArg(taskId, tOldFunc, (uintptr_t)(gTasks[taskId].func));
    gTasks[taskId].func = Task_AbilityCapsule;
}

void Task_AbilityPatch(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        // Can't use.
        if (GetSpeciesAbility(tSpecies, tAbilityNum) == 0
            || !tSpecies
            )
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            DisplayPartyMenuMessage(gText_WontHaveEffect, 1);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            return;
        }
        gPartyMenuUseExitCallback = TRUE;
        GetMonNickname(&gPlayerParty[tMonId], gStringVar1);
        StringCopy(gStringVar2, gAbilitiesInfo[GetAbilityBySpecies(tSpecies, tAbilityNum)].name);
        StringExpandPlaceholders(gStringVar4, sText_askText);
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gStringVar4, 1);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 1:
        if (!IsPartyMenuTextPrinterActive())
        {
            PartyMenuDisplayYesNoMenu();
            tState++;
        }
        break;
    case 2:
        switch (Menu_ProcessInputNoWrapClearOnChoose())
        {
        case 0:
            tState++;
            break;
        case 1:
        case MENU_B_PRESSED:
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            ScheduleBgCopyTilemapToVram(2);
            // Don't exit party selections screen, return to choosing a mon.
            ClearStdWindowAndFrameToTransparent(6, 0);
            ClearWindowTilemap(6);
            DestroyMessageWindowSprite();
            gTasks[taskId].func = (void *)GetWordTaskArg(taskId, tOldFunc);
            return;
        }
        break;
    case 3:
        PlaySE(SE_USE_ITEM);
        StringExpandPlaceholders(gStringVar4, sText_doneText);
        DisplayPartyMenuMessage(gStringVar4, 1);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 4:
        if (!IsPartyMenuTextPrinterActive())
            tState++;
        break;
    case 5:
        SetMonData(&gPlayerParty[tMonId], MON_DATA_ABILITY_NUM, &tAbilityNum);
        RemoveBagItem(gSpecialVar_ItemId, 1);
        gTasks[taskId].func = Task_ClosePartyMenu;
        break;
    }
}

void ItemUseCB_AbilityPatch(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    tState = 0;
    tMonId = gPartyMenu.slotId;
    tSpecies = GetMonData(&gPlayerParty[tMonId], MON_DATA_SPECIES);
    if (GetMonData(&gPlayerParty[tMonId], MON_DATA_ABILITY_NUM) == 2)
        tAbilityNum = 0;
    else
        tAbilityNum = 2;
    SetWordTaskArg(taskId, tOldFunc, (uintptr_t)(gTasks[taskId].func));
    gTasks[taskId].func = Task_AbilityPatch;
}

#undef tState
#undef tSpecies
#undef tAbilityNum
#undef tMonId
#undef tOldFunc

#define tState        data[0]
#define tSpecies      data[1]
#define tMonId        data[2]
#define tMonShininess data[3]
#define tOldFunc      4

void Task_ShinGenome(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    bool8 makeShiny = TRUE;

    switch (tState)
    {
    case 0:
        if (GetMonData(&gPlayerParty[tMonId], MON_DATA_IS_SHINY) == TRUE)
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            return;
        }
        gPartyMenuUseExitCallback = TRUE;
        GetMonNickname(&gPlayerParty[tMonId], gStringVar1);
        StringExpandPlaceholders(gStringVar4, sText_askShinyText);
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 1:
        if (!IsPartyMenuTextPrinterActive())
        {
            PartyMenuDisplayYesNoMenu();
            tState++;
        }
        break;
    case 2:
        switch (Menu_ProcessInputNoWrapClearOnChoose())
        {
        case 0:
            tState++;
            break;
        case 1:
        case MENU_B_PRESSED:
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            ScheduleBgCopyTilemapToVram(2);
            ClearStdWindowAndFrameToTransparent(6, 0);
            ClearWindowTilemap(6);
            DestroyMessageWindowSprite();
            gTasks[taskId].func = (void *)GetWordTaskArg(taskId, tOldFunc);
            return;
        }
        break;
    case 3:
        PlaySE(SE_USE_ITEM);
        StringExpandPlaceholders(gStringVar4, sText_doneShinyText);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 4:
        if (!IsPartyMenuTextPrinterActive())
            tState++;
        break;
    case 5:
        SetMonData(&gPlayerParty[tMonId], MON_DATA_IS_SHINY, &makeShiny);
        RemoveBagItem(gSpecialVar_ItemId, 1);
        gTasks[taskId].func = Task_ClosePartyMenu;
        break;
    }
}

void ItemUseCB_ShinGenome(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    tState = 0;
    tMonId = gPartyMenu.slotId;
    tMonShininess = GetMonData(&gPlayerParty[tMonId], MON_DATA_IS_SHINY);
    tSpecies = GetMonData(&gPlayerParty[tMonId], MON_DATA_SPECIES);
    SetWordTaskArg(taskId, tOldFunc, (uintptr_t)(gTasks[taskId].func));
    gTasks[taskId].func = Task_ShinGenome;
}

#undef tState
#undef tSpecies
#undef tMonId
#undef tMonShininess
#undef tOldFunc

#define tState      data[0]
#define tMonId      data[1]
#define tOldNature  data[2]
#define tNewNature  data[3]
#define tOldFunc    4

void Task_Mint(u8 taskId)
{
    static const u8 sText_askText[] = _("It might affect {STR_VAR_1}'s stats.\nAre you sure you want to use it?");
    static const u8 sText_doneText[] = _("{STR_VAR_1}'s stats may have changed due\nto the effects of the {STR_VAR_2}!{PAUSE_UNTIL_PRESS}");
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        // Can't use.
        if (tOldNature == tNewNature)
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            DisplayPartyMenuMessage(gText_WontHaveEffect, 1);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            return;
        }
        gPartyMenuUseExitCallback = TRUE;
        GetMonNickname(&gPlayerParty[tMonId], gStringVar1);
        CopyItemName(gSpecialVar_ItemId, gStringVar2);
        StringExpandPlaceholders(gStringVar4, sText_askText);
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gStringVar4, 1);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 1:
        if (!IsPartyMenuTextPrinterActive())
        {
            PartyMenuDisplayYesNoMenu();
            tState++;
        }
        break;
    case 2:
        switch (Menu_ProcessInputNoWrapClearOnChoose())
        {
        case 0:
            tState++;
            break;
        case 1:
        case MENU_B_PRESSED:
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            ScheduleBgCopyTilemapToVram(2);
            // Don't exit party selections screen, return to choosing a mon.
            ClearStdWindowAndFrameToTransparent(6, 0);
            ClearWindowTilemap(6);
            DestroyMessageWindowSprite();
            gTasks[taskId].func = (void *)GetWordTaskArg(taskId, tOldFunc);
            return;
        }
        break;
    case 3:
        PlaySE(SE_USE_ITEM);
        StringExpandPlaceholders(gStringVar4, sText_doneText);
        DisplayPartyMenuMessage(gStringVar4, 1);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 4:
        if (!IsPartyMenuTextPrinterActive())
            tState++;
        break;
    case 5:
        SetMonData(&gPlayerParty[tMonId], MON_DATA_HIDDEN_NATURE, &tNewNature);
        CalculateMonStats(&gPlayerParty[tMonId]);
        RemoveBagItem(gSpecialVar_ItemId, 1);
        gTasks[taskId].func = Task_ClosePartyMenu;
        break;
    }
}

void ItemUseCB_Mint(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    tState = 0;
    tMonId = gPartyMenu.slotId;
    tOldNature = GetMonData(&gPlayerParty[tMonId], MON_DATA_HIDDEN_NATURE);
    tNewNature = GetItemSecondaryId(gSpecialVar_ItemId);
    SetWordTaskArg(taskId, tOldFunc, (uintptr_t)(gTasks[taskId].func));
    gTasks[taskId].func = Task_Mint;
}

#undef tState
#undef tMonId
#undef tOldNature
#undef tNewNature
#undef tOldFunc

static void Task_DisplayHPRestoredMessage(u8 taskId)
{
    GetMonNickname(&gPlayerParty[gPartyMenu.slotId], gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_PkmnHPRestoredByVar2);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    HandleBattleLowHpMusicChange();
    if (gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD && CheckBagHasItem(gSpecialVar_ItemId, 1))
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    else
        gTasks[taskId].func = Task_ClosePartyMenuAfterText;
}

static void Task_ClosePartyMenuAfterText(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        if (gPartyMenuUseExitCallback == FALSE)
            sPartyMenuInternal->exitCallback = NULL;
        Task_ClosePartyMenu(taskId);
    }
}

void ItemUseCB_ResetEVs(u8 taskId, TaskFunc task)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = gSpecialVar_ItemId;
    bool8 cannotUseEffect = ExecuteTableBasedItemEffect(mon, item, gPartyMenu.slotId, 0, 1, 1);

    if (cannotUseEffect)
    {
        gPartyMenuUseExitCallback = FALSE;
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = task;
    }
    else
    {
        gPartyMenuUseExitCallback = TRUE;
        PlaySE(SE_USE_ITEM);
        RemoveBagItem(item, 1);
        GetMonNickname(mon, gStringVar1);
        StringExpandPlaceholders(gStringVar4, sText_BasePointsResetToZero);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = task;
    }
}

void ItemUseCB_ReduceEV(u8 taskId, TaskFunc task)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    s16 *data = gTasks[taskId].data;
    u16 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP);
    tItemEffect = GetItemEffectType(gSpecialVar_ItemId);
    u16 ev = ItemEffectToMonEv(mon, tItemEffect);
    tQuantityInBag = CountTotalItemQuantityInBag(gSpecialVar_ItemId);
    tItemCount = 1;

    if (friendship == MAX_FRIENDSHIP && ev == 0)
    {
        gPartyMenuUseExitCallback = FALSE;
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = task;
    }
    else
    {
        if (tQuantityInBag > 1 && ev > 10)
        {
            PlaySE(SE_SELECT);
            DisplayGiveHowManyMessage();

            tMaxItemQuantity = (I_BERRY_EV_JUMP == GEN_4 && ev > 100) ? 11 : (ev + 9) / 10; // Currently hardcoded to assume that EV-reducing items always reduce EV by 10
            tMaxItemQuantity = min(tQuantityInBag, tMaxItemQuantity);

            gTasks[taskId].func = Task_GiveHowManyItems;
        }
        else
        {
            ItemUse_ApplyEvReduceBerry(taskId);
        }
    }
}

static u16 ItemEffectToMonEv(struct Pokemon *mon, u8 effectType)
{
    switch (effectType)
    {
    case ITEM_EFFECT_HP_EV:
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_SHEDINJA)
            return GetMonData(mon, MON_DATA_HP_EV);
        break;
    case ITEM_EFFECT_ATK_EV:
        return GetMonData(mon, MON_DATA_ATK_EV);
    case ITEM_EFFECT_DEF_EV:
        return GetMonData(mon, MON_DATA_DEF_EV);
    case ITEM_EFFECT_SPEED_EV:
        return GetMonData(mon, MON_DATA_SPEED_EV);
    case ITEM_EFFECT_SPATK_EV:
        return GetMonData(mon, MON_DATA_SPATK_EV);
    case ITEM_EFFECT_SPDEF_EV:
        return GetMonData(mon, MON_DATA_SPDEF_EV);
    }
    return 0;
}

static u16 ItemEffectToMonIV(struct Pokemon *mon, u8 effectType)
{
    enum Stat stat;

    switch (effectType)
    {
    case ITEM_EFFECT_HP_IV_REDUCE:
        stat = STAT_HP;
        break;
    case ITEM_EFFECT_ATK_IV_REDUCE:
        stat = STAT_ATK;
        break;
    case ITEM_EFFECT_DEF_IV_REDUCE:
        stat = STAT_DEF;
        break;
    case ITEM_EFFECT_SPEED_IV_REDUCE:
        stat = STAT_SPEED;
        break;
    case ITEM_EFFECT_SPATK_IV_REDUCE:
        stat = STAT_SPATK;
        break;
    case ITEM_EFFECT_SPDEF_IV_REDUCE:
        stat = STAT_SPDEF;
        break;
    default:
        return 0;
    }

    if (GetMonData(mon, MON_DATA_HYPER_TRAINED_HP + stat))
        return MAX_PER_STAT_IVS;
    return GetMonData(mon, MON_DATA_HP_IV + stat);
}

static void ItemEffectToStatString(u8 effectType, u8 *dest)
{
    switch (effectType)
    {
    case ITEM_EFFECT_HP_EV:
    case ITEM_EFFECT_HP_IV_REDUCE:
        StringCopy(dest, gText_HP3);
        break;
    case ITEM_EFFECT_ATK_EV:
    case ITEM_EFFECT_ATK_IV_REDUCE:
        StringCopy(dest, gText_Attack3);
        break;
    case ITEM_EFFECT_DEF_EV:
    case ITEM_EFFECT_DEF_IV_REDUCE:
        StringCopy(dest, gText_Defense3);
        break;
    case ITEM_EFFECT_SPEED_EV:
    case ITEM_EFFECT_SPEED_IV_REDUCE:
        StringCopy(dest, gText_Speed2);
        break;
    case ITEM_EFFECT_SPATK_EV:
    case ITEM_EFFECT_SPATK_IV_REDUCE:
        StringCopy(dest, gText_SpAtk3);
        break;
    case ITEM_EFFECT_SPDEF_EV:
    case ITEM_EFFECT_SPDEF_IV_REDUCE:
        StringCopy(dest, gText_SpDef3);
        break;
    }
}

static void ShowMoveSelectWindow(u8 slot)
{
    u8 i;
    u8 moveCount = 0;
    u8 windowId = DisplaySelectionWindow(SELECTWINDOW_MOVES);
    enum Move move;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = GetMonData(&gPlayerParty[slot], MON_DATA_MOVE1 + i);
        u8 fontId = GetFontIdToFit(GetMoveName(move), FONT_NORMAL, 0, 72);
        AddTextPrinterParameterized(windowId, fontId, GetMoveName(move), 8, (i * 16) + 1, TEXT_SKIP_DRAW, NULL);
        if (move != MOVE_NONE)
            moveCount++;
    }
    InitMenuInUpperLeftCornerNormal(windowId, moveCount, 0);
    ScheduleBgCopyTilemapToVram(2);
}

static void Task_HandleWhichMoveInput(u8 taskId)
{
    s8 input = Menu_ProcessInput();

    if (input != MENU_NOTHING_CHOSEN)
    {
        if (input == MENU_B_PRESSED)
        {
            PlaySE(SE_SELECT);
            ReturnToUseOnWhichMon(taskId);
        }
        else
        {
            PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
            SetSelectedMoveForItem(taskId);
        }
    }
}

void ItemUseCB_PPRecovery(u8 taskId, TaskFunc task)
{
    const u8 *effect = GetItemEffect(gSpecialVar_ItemId);

    if (effect == NULL || !(effect[4] & ITEM4_HEAL_PP_ONE))
    {
        gPartyMenu.data1 = 0;
        TryUseItemOnMove(taskId);
    }
    else
    {
        PlaySE(SE_SELECT);
        ShowMoveSelectWindow(gPartyMenu.slotId);
        gTasks[taskId].func = Task_HandleWhichMoveInput;
    }
}

static void SetSelectedMoveForItem(u8 taskId)
{
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    gPartyMenu.data1 = Menu_GetCursorPos();
    TryUseItemOnMove(taskId);
}

static void ReturnToUseOnWhichMon(u8 taskId)
{
    gTasks[taskId].func = Task_HandleChooseMonInput;
    sPartyMenuInternal->exitCallback = NULL;
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
}

static void TryUseItemOnMove(u8 taskId)
{
    struct PartyMenu *ptr = &gPartyMenu;
    struct Pokemon *mon = &gPlayerParty[ptr->slotId];
    // In battle, set appropriate variables to be used in battle script.
    if (gMain.inBattle)
    {
        if (CannotUseItemsInBattle(gSpecialVar_ItemId, mon))
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
        }
        else
        {
            gBattleStruct->itemPartyIndex[gBattlerInMenuId] = GetPartyIdFromBattleSlot(gPartyMenu.slotId);
            gBattleStruct->itemMoveIndex[gBattlerInMenuId] = ptr->data1;
            gPartyMenuUseExitCallback = TRUE;
            RemoveBagItem(gSpecialVar_ItemId, 1);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
        }
    }
    // Outside of battle, only PP items are used on moves.
    else
    {
        enum Move move = MOVE_NONE;
        s16 *moveSlot = &gPartyMenu.data1;
        enum Item item = gSpecialVar_ItemId;

        if (ExecuteTableBasedItemEffect(mon, item, ptr->slotId, *moveSlot, 1, 1))
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
        }
        else
        {
            gPartyMenuUseExitCallback = TRUE;
            PlaySE(SE_USE_ITEM);
            RemoveBagItem(item, 1);
            move = GetMonData(mon, MON_DATA_MOVE1 + *moveSlot);
            StringCopy(gStringVar1, GetMoveName(move));
            GetMedicineItemEffectMessage(item, 0);
            DisplayPartyMenuMessage(gStringVar4, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
        }
    }
}

void ItemUseCB_PPUp(u8 taskId, TaskFunc task)
{
    PlaySE(SE_SELECT);
    ShowMoveSelectWindow(gPartyMenu.slotId);
    gTasks[taskId].func = Task_HandleWhichMoveInput;
}

enum Move ItemIdToBattleMoveId(enum Item item)
{
    return (GetItemPocket(item) == POCKET_TM_HM) ? GetItemTMHMMoveId(item) : MOVE_NONE;
}

bool8 MonKnowsMove(struct Pokemon *mon, enum Move move)
{
    u8 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetMonData(mon, MON_DATA_MOVE1 + i) == move)
            return TRUE;
    }
    return FALSE;
}

bool8 BoxMonKnowsMove(struct BoxPokemon *boxMon, enum Move move)
{
    u8 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetBoxMonData(boxMon, MON_DATA_MOVE1 + i) == move)
            return TRUE;
    }
    return FALSE;
}

static void DisplayLearnMoveMessage(const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    ScheduleBgCopyTilemapToVram(2);
}

static void DisplayLearnMoveMessageAndClose(u8 taskId, const u8 *str)
{
    DisplayLearnMoveMessage(str);
    gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
}

// move[1] doesn't use constants cause I don't know if it's actually a move ID storage

void ItemUseCB_TMHM(u8 taskId, TaskFunc task)
{
    struct Pokemon *mon;
    enum Item item = gSpecialVar_ItemId;
    enum Move move = ItemIdToBattleMoveId(item);

    gPartyMenu.data1 = move;
    gPartyMenu.learnMoveState = 0;

    PlaySE(SE_SELECT);
    mon = &gPlayerParty[gPartyMenu.slotId];

    GetMonNickname(mon, gStringVar1);
    StringCopy(gStringVar2, GetMoveName(move));

    switch (CanTeachMove(mon, move))
    {
    case CANNOT_LEARN_MOVE:
        DisplayLearnMoveMessageAndClose(taskId, gText_PkmnCantLearnMove);
        return;
    case ALREADY_KNOWS_MOVE:
        DisplayLearnMoveMessageAndClose(taskId, gText_PkmnAlreadyKnows);
        return;
    default:
        break;
    }

    if (GiveMoveToMon(mon, move) != MON_HAS_MAX_MOVES)
    {
        gTasks[taskId].func = Task_LearnedMove;
    }
    else
    {
        DisplayLearnMoveMessage(gText_PkmnNeedsToReplaceMove);
        gTasks[taskId].func = Task_ReplaceMoveYesNo;
    }
}

static void Task_LearnedMove(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    s16 *move = &gPartyMenu.data1;
    enum Item item = gSpecialVar_ItemId;

    if (move[1] == 0)
    {
        AdjustFriendship(mon, FRIENDSHIP_EVENT_LEARN_TMHM);
        if (!GetItemImportance(item))
            RemoveBagItem(item, 1);
    }
    GetMonNickname(mon, gStringVar1);
    StringCopy(gStringVar2, GetMoveName(move[0]));
    StringExpandPlaceholders(gStringVar4, gText_PkmnLearnedMove3);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_DoLearnedMoveFanfareAfterText;
}

static void Task_DoLearnedMoveFanfareAfterText(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PlayFanfare(MUS_LEVEL_UP);
        gTasks[taskId].func = Task_LearnNextMoveOrClosePartyMenu;
    }
}

static void Task_LearnNextMoveOrClosePartyMenu(u8 taskId)
{
    if (IsFanfareTaskInactive() && ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON))))
    {
        if (gPartyMenu.learnMoveState == 1)
        {
            Task_TryLearningNextMove(taskId);
        }
        else
        {
            if (gPartyMenu.learnMoveState == 2) // never occurs
                gSpecialVar_Result = TRUE;
            Task_ClosePartyMenu(taskId);
        }
    }
}

static void Task_ReplaceMoveYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleReplaceMoveYesNoInput;
    }
}

static void Task_HandleReplaceMoveYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        DisplayPartyMenuMessage(gText_WhichMoveToForget, TRUE);
        gTasks[taskId].func = Task_ShowSummaryScreenToForgetMove;
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        StopLearningMovePrompt(taskId);
        break;
    }
}

static void Task_ShowSummaryScreenToForgetMove(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        sPartyMenuInternal->exitCallback = CB2_ShowSummaryScreenToForgetMove;
        Task_ClosePartyMenu(taskId);
    }
}

static void CB2_ShowSummaryScreenToForgetMove(void)
{
    ShowSelectMovePokemonSummaryScreen(gPlayerParty, gPartyMenu.slotId, CB2_ReturnToPartyMenuWhileLearningMove, gPartyMenu.data1);
}

static void CB2_ReturnToPartyMenuWhileLearningMove(void)
{
    if (sFinalLevel != 0)
        SetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_LEVEL, &sFinalLevel); // to avoid displaying incorrect level
    if (GetItemFieldFunc(gSpecialVar_ItemId) == ItemUseOutOfBattle_RareCandy && gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD && CheckBagHasItem(gSpecialVar_ItemId, 1))
        InitPartyMenu(PARTY_MENU_TYPE_FIELD, PARTY_LAYOUT_SINGLE, PARTY_ACTION_USE_ITEM, TRUE, PARTY_MSG_NONE, Task_ReturnToPartyMenuWhileLearningMove, gPartyMenu.exitCallback);
    else
        InitPartyMenu(PARTY_MENU_TYPE_FIELD, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, TRUE, PARTY_MSG_NONE, Task_ReturnToPartyMenuWhileLearningMove, gPartyMenu.exitCallback);
}

static void Task_ReturnToPartyMenuWhileLearningMove(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (GetMoveSlotToReplace() != MAX_MON_MOVES)
            DisplayPartyMenuForgotMoveMessage(taskId);
        else
            StopLearningMovePrompt(taskId);
    }
}

static void DisplayPartyMenuForgotMoveMessage(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Move move = GetMonData(mon, MON_DATA_MOVE1 + GetMoveSlotToReplace());

    GetMonNickname(mon, gStringVar1);
    StringCopy(gStringVar2, GetMoveName(move));
    DisplayLearnMoveMessage(gText_12PoofForgotMove);
    gTasks[taskId].func = Task_PartyMenuReplaceMove;
}

static void Task_PartyMenuReplaceMove(u8 taskId)
{
    struct Pokemon *mon;
    enum Move move;

    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        mon = &gPlayerParty[gPartyMenu.slotId];
        RemoveMonPPBonus(mon, GetMoveSlotToReplace());
        move = gPartyMenu.data1;
        SetMonMoveSlot(mon, move, GetMoveSlotToReplace());
        Task_LearnedMove(taskId);
    }
}

static void StopLearningMovePrompt(u8 taskId)
{
    if (P_ASK_MOVE_CONFIRMATION == FALSE)
    {
        struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
        GetMonNickname(mon, gStringVar1);
    }

    StringCopy(gStringVar2, GetMoveName(gPartyMenu.data1));
    StringExpandPlaceholders(gStringVar4, (P_ASK_MOVE_CONFIRMATION) ? gText_StopLearningMove2 : gText_MoveNotLearned);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = (P_ASK_MOVE_CONFIRMATION) ? Task_StopLearningMoveYesNo : Task_HandleStopLearningMove;
}

static void Task_HandleStopLearningMove(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        if (gPartyMenu.learnMoveState == 1)
            gTasks[taskId].func = Task_TryLearningNextMoveAfterText;
        else
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    }
}

static void Task_StopLearningMoveYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleStopLearningMoveYesNoInput;
    }
}

static void Task_HandleStopLearningMoveYesNoInput(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        GetMonNickname(mon, gStringVar1);
        StringCopy(gStringVar2, GetMoveName(gPartyMenu.data1));
        StringExpandPlaceholders(gStringVar4, gText_MoveNotLearned);
        DisplayPartyMenuMessage(gStringVar4, TRUE);
        if (gPartyMenu.learnMoveState == 1)
        {
            gTasks[taskId].func = Task_TryLearningNextMoveAfterText;
        }
        else
        {
            if (gPartyMenu.learnMoveState == 2) // never occurs
                gSpecialVar_Result = FALSE;
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        }
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        GetMonNickname(mon, gStringVar1);
        StringCopy(gStringVar2, GetMoveName(gPartyMenu.data1));
        DisplayLearnMoveMessage(gText_PkmnNeedsToReplaceMove);
        gTasks[taskId].func = Task_ReplaceMoveYesNo;
        break;
    }
}

static void Task_TryLearningNextMoveAfterText(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
        Task_TryLearningNextMove(taskId);
}

static void UNUSED DisplayExpPoints(u8 taskId, TaskFunc task, u8 holdEffectParam)
{
    PlaySE(SE_USE_ITEM);
    ConvertIntToDecimalStringN(gStringVar2, sExpCandyExperienceTable[holdEffectParam], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_PkmnGainedExp);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = task;
}

void ItemUseCB_RareCandy(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    bool8 cannotUseEffect;

    if (gSpecialVar_ItemId == ITEM_REVERSE_CANDY)
    {
        ItemUseCB_ReverseCandy(taskId, task);
        return;
    }

    tHoldEffectParam = GetItemHoldEffectParam(gSpecialVar_ItemId);
    sInitialLevel = GetMonData(mon, MON_DATA_LEVEL);
    tItemEffect = GetItemEffectType(gSpecialVar_ItemId);
    tQuantityInBag = CountTotalItemQuantityInBag(gSpecialVar_ItemId);
    tItemCount = 1;
    tMaxItemQuantity = GetMaxLevelUpItemQuantity(mon, tHoldEffectParam, tQuantityInBag);

    if (tMaxItemQuantity == 0)
        cannotUseEffect = TRUE;
    else
        cannotUseEffect = ExecuteTableBasedItemEffect(mon, gSpecialVar_ItemId, gPartyMenu.slotId, 0, 0, 1);

    PlaySE(SE_SELECT);
    if (cannotUseEffect)
    {
        u32 targetSpecies = SPECIES_NONE;
        bool32 canStopEvo = TRUE;

        // Resets values to 0 so other means of teaching moves doesn't overwrite levels
        sInitialLevel = 0;
        sFinalLevel = 0;

        if (tHoldEffectParam == 0) // Rare Candy
        {
            targetSpecies = GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStopEvo, CHECK_EVO);
        }

        if (targetSpecies != SPECIES_NONE)
        {
            GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStopEvo, DO_EVO);
            RemoveBagItem(gSpecialVar_ItemId, 1);
            FreePartyPointers();
            gCB2_AfterEvolution = gPartyMenu.exitCallback;
            BeginEvolutionScene(mon, targetSpecies, canStopEvo, gPartyMenu.slotId);
            DestroyTask(taskId);
        }
        else
        {
            gPartyMenuUseExitCallback = FALSE;
            DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = task;
        }
    }
    else
    {
        if (tQuantityInBag > 1)
        {
            DisplayGiveHowManyMessage();

            gTasks[taskId].func = Task_GiveHowManyItems;
        }
        else
        {
            ItemUse_ApplyExpCandy(taskId);
        }
    }
}

static void ItemUseCB_ReverseCandy(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    u16 level = GetMonData(mon, MON_DATA_LEVEL);

    tQuantityInBag = CountTotalItemQuantityInBag(gSpecialVar_ItemId);
    tItemCount = 1;
    if (GetMonData(mon, MON_DATA_IS_EGG) || level <= MIN_LEVEL)
        tMaxItemQuantity = 0;
    else
        tMaxItemQuantity = min(tQuantityInBag, level - MIN_LEVEL);

    PlaySE(SE_SELECT);
    if (tMaxItemQuantity == 0)
    {
        gPartyMenuUseExitCallback = FALSE;
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = task;
    }
    else if (tMaxItemQuantity > 1)
    {
        DisplayGiveHowManyMessage();
        gTasks[taskId].func = Task_GiveHowManyItems;
    }
    else
    {
        ItemUse_ApplyReverseCandy(taskId);
    }
}

static void UpdateMonDisplayInfoAfterRareCandy(u8 slot, struct Pokemon *mon)
{
    SetPartyMonAilmentGfx(mon, &sPartyMenuBoxes[slot]);
    RedrawPartyMonInfo(mon, &sPartyMenuBoxes[slot], TRUE, TRUE, TRUE, TRUE);
    DisplayPartyPokemonHPBarCheck(mon, &sPartyMenuBoxes[slot]);
    UpdatePartyMonHPBar(sPartyMenuBoxes[slot].monSpriteId, mon);
    AnimatePartySlot(slot, 1);
    ScheduleBgCopyTilemapToVram(0);
}

static void Task_DisplayLevelUpStatsPg1(u8 taskId)
{
    if (WaitFanfare(FALSE) && IsPartyMenuTextPrinterActive() != TRUE && ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON))))
    {
        PlaySE(SE_SELECT);
        DisplayLevelUpStatsPg1(taskId);
        gTasks[taskId].func = Task_DisplayLevelUpStatsPg2;
    }
}

static void Task_DisplayLevelUpStatsPg2(u8 taskId)
{
    if ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON)))
    {
        PlaySE(SE_SELECT);
        DisplayLevelUpStatsPg2(taskId);
        sInitialLevel += 1; // so the Pokemon doesn't learn a move meant for its previous level
        gTasks[taskId].func = Task_TryLearnNewMoves;
    }
}

static void DisplayLevelUpStatsPg1(u8 taskId)
{
    u16 *arrayPtr = (u16*) sPartyMenuInternal->data;

    arrayPtr[12] = CreateLevelUpStatsWindow();
    DrawLevelUpWindowPg1(arrayPtr[12], arrayPtr, &arrayPtr[6], TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY);
    CopyWindowToVram(arrayPtr[12], COPYWIN_GFX);
    ScheduleBgCopyTilemapToVram(2);
}

static void DisplayLevelUpStatsPg2(u8 taskId)
{
    u16 *arrayPtr = (u16*) sPartyMenuInternal->data;

    DrawLevelUpWindowPg2(arrayPtr[12], &arrayPtr[6], TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY);
    CopyWindowToVram(arrayPtr[12], COPYWIN_GFX);
    ScheduleBgCopyTilemapToVram(2);
}

static void Task_TryLearnNewMoves(u8 taskId)
{
    u16 learnMove;

    if (WaitFanfare(FALSE) && ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON))))
    {
        RemoveLevelUpStatsWindow();
        for (; sInitialLevel <= sFinalLevel; sInitialLevel++)
        {
            SetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_LEVEL, &sInitialLevel);
            learnMove = MonTryLearningNewMove(&gPlayerParty[gPartyMenu.slotId], TRUE);
            gPartyMenu.learnMoveState = 1;
            switch (learnMove)
            {
            case 0: // No moves to learn
                if (sInitialLevel >= sFinalLevel)
                    PartyMenuTryEvolution(taskId);
                break;
            case MON_HAS_MAX_MOVES:
                DisplayMonNeedsToReplaceMove(taskId);
                break;
            case MON_ALREADY_KNOWS_MOVE:
                gTasks[taskId].func = Task_TryLearningNextMove;
                break;
            default:
                DisplayMonLearnedMove(taskId, learnMove);
                break;
            }
            if (learnMove)
                break;
        }
    }
}

static void Task_TryLearningNextMove(u8 taskId)
{
    u16 result;
    for (; sInitialLevel <= sFinalLevel; sInitialLevel++)
    {
        SetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_LEVEL, &sInitialLevel);
        result = MonTryLearningNewMove(&gPlayerParty[gPartyMenu.slotId], FALSE);
        switch (result)
        {
        case 0: // No moves to learn
            if (sInitialLevel >= sFinalLevel)
                PartyMenuTryEvolution(taskId);
            break;
        case MON_HAS_MAX_MOVES:
            DisplayMonNeedsToReplaceMove(taskId);
            break;
        case MON_ALREADY_KNOWS_MOVE:
            gTasks[taskId].func = Task_TryLearningNextMove;
            return;
        default:
            DisplayMonLearnedMove(taskId, result);
            break;
        }
        if (result)
            break;
    }
}

static void CB2_ReturnToPartyMenuUsingRareCandy(void)
{
    gItemUseCB = ItemUseCB_RareCandy;
    SetMainCallback2(CB2_ShowPartyMenuForItemUse);
}

static void PartyMenuTryEvolution(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    u32 targetSpecies = SPECIES_NONE;
    bool32 canStopEvo = TRUE;

    // Resets values to 0 so other means of teaching moves doesn't overwrite levels
    sInitialLevel = 0;
    sFinalLevel = 0;

    targetSpecies = GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStopEvo, CHECK_EVO);

    if (targetSpecies != SPECIES_NONE)
    {
        GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStopEvo, DO_EVO);
        FreePartyPointers();
        if (GetItemFieldFunc(gSpecialVar_ItemId) == ItemUseOutOfBattle_RareCandy && gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD && CheckBagHasItem(gSpecialVar_ItemId, 1))
            gCB2_AfterEvolution = CB2_ReturnToPartyMenuUsingRareCandy;
        else
            gCB2_AfterEvolution = gPartyMenu.exitCallback;
        BeginEvolutionScene(mon, targetSpecies, canStopEvo, gPartyMenu.slotId);
        DestroyTask(taskId);
    }
    else
    {
        if (gPartyMenu.menuType == PARTY_MENU_TYPE_FIELD && CheckBagHasItem(gSpecialVar_ItemId, 1))
            gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        else
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
    }
}

static void DisplayMonNeedsToReplaceMove(u8 taskId)
{
    GetMonNickname(&gPlayerParty[gPartyMenu.slotId], gStringVar1);
    StringCopy(gStringVar2, GetMoveName(gMoveToLearn));
    StringExpandPlaceholders(gStringVar4, gText_PkmnNeedsToReplaceMove);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    gPartyMenu.data1 = gMoveToLearn;
    gTasks[taskId].func = Task_ReplaceMoveYesNo;
}

static void DisplayMonLearnedMove(u8 taskId, u16 move)
{
    GetMonNickname(&gPlayerParty[gPartyMenu.slotId], gStringVar1);
    StringCopy(gStringVar2, GetMoveName(move));
    StringExpandPlaceholders(gStringVar4, gText_PkmnLearnedMove3);
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    gPartyMenu.data1 = move;
    gTasks[taskId].func = Task_DoLearnedMoveFanfareAfterText;
}

static void BufferMonStatsToTaskData(struct Pokemon *mon, s16 *data)
{
    data[0] = GetMonData(mon, MON_DATA_MAX_HP);
    data[1] = GetMonData(mon, MON_DATA_ATK);
    data[2] = GetMonData(mon, MON_DATA_DEF);
    data[4] = GetMonData(mon, MON_DATA_SPATK);
    data[5] = GetMonData(mon, MON_DATA_SPDEF);
    data[3] = GetMonData(mon, MON_DATA_SPEED);
}

#define tState        data[0]
#define tMonId        data[1]
#define tDynamaxLevel data[2]
#define tOldFunc      4

void Task_DynamaxCandy(u8 taskId)
{
    static const u8 sText_doneText[] = _("{STR_VAR_1}'s Dynamax Level\nincreased by 1!{PAUSE_UNTIL_PRESS}");
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        // Can't use.
        if (tDynamaxLevel == MAX_DYNAMAX_LEVEL)
        {
            gPartyMenuUseExitCallback = FALSE;
            PlaySE(SE_SELECT);
            DisplayPartyMenuMessage(gText_WontHaveEffect, 1);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            return;
        }
        gPartyMenuUseExitCallback = TRUE;
        GetMonNickname(&gPlayerParty[tMonId], gStringVar1);
        CopyItemName(gSpecialVar_ItemId, gStringVar2);
        tState++;
        break;
    case 1:
        PlaySE(SE_USE_ITEM);
        StringExpandPlaceholders(gStringVar4, sText_doneText);
        DisplayPartyMenuMessage(gStringVar4, 1);
        ScheduleBgCopyTilemapToVram(2);
        tState++;
        break;
    case 2:
        if (!IsPartyMenuTextPrinterActive())
            tState++;
        break;
    case 3:
        tDynamaxLevel++;
        SetMonData(&gPlayerParty[tMonId], MON_DATA_DYNAMAX_LEVEL, &tDynamaxLevel);
        RemoveBagItem(gSpecialVar_ItemId, 1);
        gTasks[taskId].func = Task_ClosePartyMenu;
        break;
    }
}

void ItemUseCB_DynamaxCandy(u8 taskId, TaskFunc task)
{
    s16 *data = gTasks[taskId].data;

    tState = 0;
    tMonId = gPartyMenu.slotId;
    tDynamaxLevel = GetMonData(&gPlayerParty[tMonId], MON_DATA_DYNAMAX_LEVEL);
    SetWordTaskArg(taskId, tOldFunc, (uintptr_t)(gTasks[taskId].func));
    gTasks[taskId].func = Task_DynamaxCandy;
}

#undef tState
#undef tMonId
#undef tDynamaxLevel
#undef tOldFunc

#define tUsedOnSlot   data[0]
#define tHadEffect    data[1]
#define tLastSlotUsed data[2]

void ItemUseCB_SacredAsh(u8 taskId, TaskFunc task)
{
    sPartyMenuInternal->tUsedOnSlot = FALSE;
    sPartyMenuInternal->tHadEffect = FALSE;
    sPartyMenuInternal->tLastSlotUsed = gPartyMenu.slotId;
    UseSacredAsh(taskId);
}

static void UseSacredAsh(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    u16 hp;

    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
    {
        gTasks[taskId].func = Task_SacredAshLoop;
        return;
    }

    hp = GetMonData(mon, MON_DATA_HP);
    if (ExecuteTableBasedItemEffect(mon, gSpecialVar_ItemId, gPartyMenu.slotId, 0, 1, 1))
    {
        gTasks[taskId].func = Task_SacredAshLoop;
        return;
    }

    PlaySE(SE_USE_ITEM);
    SetPartyMonAilmentGfx(mon, &sPartyMenuBoxes[gPartyMenu.slotId]);
    if (gSprites[sPartyMenuBoxes[gPartyMenu.slotId].statusSpriteId].invisible)
        DisplayPartyPokemonLevelCheck(mon, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
    AnimatePartySlot(sPartyMenuInternal->tLastSlotUsed, 0);
    AnimatePartySlot(gPartyMenu.slotId, 1);
    PartyMenuModifyHP(taskId, gPartyMenu.slotId, 1, GetMonData(mon, MON_DATA_HP) - hp, Task_SacredAshDisplayHPRestored);
    ResetHPTaskData(taskId, 0, hp);
    sPartyMenuInternal->tUsedOnSlot = TRUE;
    sPartyMenuInternal->tHadEffect = TRUE;
}

static void Task_SacredAshLoop(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        if (sPartyMenuInternal->tUsedOnSlot == TRUE)
        {
            sPartyMenuInternal->tUsedOnSlot = FALSE;
            sPartyMenuInternal->tLastSlotUsed = gPartyMenu.slotId;
        }
        if (++(gPartyMenu.slotId) == PARTY_SIZE)
        {
            if (sPartyMenuInternal->tHadEffect == FALSE)
            {
                gPartyMenuUseExitCallback = FALSE;
                DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
                ScheduleBgCopyTilemapToVram(2);
            }
            else
            {
                gPartyMenuUseExitCallback = TRUE;
                RemoveBagItem(gSpecialVar_ItemId, 1);
            }
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            gPartyMenu.slotId = 0;
        }
        else
        {
            UseSacredAsh(taskId);
        }
    }
}

static void Task_SacredAshDisplayHPRestored(u8 taskId)
{
    GetMonNickname(&gPlayerParty[gPartyMenu.slotId], gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_PkmnHPRestoredByVar2);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_SacredAshLoop;
}

#undef tUsedOnSlot
#undef tHadEffect
#undef tLastSlotUsed

void ItemUseCB_EvolutionStone(u8 taskId, TaskFunc task)
{
    PlaySE(SE_SELECT);
    gCB2_AfterEvolution = gPartyMenu.exitCallback;
    if (ExecuteTableBasedItemEffect(&gPlayerParty[gPartyMenu.slotId], gSpecialVar_ItemId, gPartyMenu.slotId, 0, 1, 1))
    {
        gPartyMenuUseExitCallback = FALSE;
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
    }
    else
    {
        if (GetItemPocket(gSpecialVar_ItemId) != POCKET_KEY_ITEMS)
            RemoveBagItem(gSpecialVar_ItemId, 1);
        FreePartyPointers();
    }
}

#define tState          data[0]
#define tTargetSpecies  data[1]
#define tAnimWait       data[2]
#define tNextFunc       3

#define fusionType           data[6]
#define firstFusion          data[7]
#define firstFusionSlot      data[8]
#define fusionResult         data[9]
#define secondFusionSlot     data[10]
#define unfuseSecondMon      data[11]
#define moveToLearn          data[12]
#define tExtraMoveHandling   data[13]
#define forgetMove           data[14]
#define storageIndex         data[15]

#define MOSAIC_ANIM_DURATION 15

static void SpriteCB_MosaicAnim(struct Sprite *sprite)
{
    if (sprite->data[5] > 0)
        sprite->data[5]--;

    SetGpuReg(REG_OFFSET_MOSAIC, (sprite->data[5] << 12) | (sprite->data[5] << 8));

    if (sprite->data[5] == 0)
    {
        sprite->oam.mosaic = FALSE;
        if (sprite->data[6] == 1) // Restore MonIcon
            sprite->callback = SpriteCB_MonIcon;
        else // Restore PartyMon / Shadow
            sprite->callback = SpriteCB_PartyMonPokemon;
    }
}

static u8 LoadAndApplyMosaicToMonSprite(struct Pokemon *mon, bool32 isShadow)
{
    s16 state = 0;
    u8 spriteId;
    while ((spriteId = LoadMonGfxAndSprite(mon, &state, isShadow)) == 0xFF);

    if (spriteId != MAX_SPRITES)
    {
        gSprites[spriteId].oam.mosaic = TRUE;
        gSprites[spriteId].data[5] = MOSAIC_ANIM_DURATION;
        gSprites[spriteId].data[6] = 0; // Restore PartyMon
        gSprites[spriteId].callback = SpriteCB_MosaicAnim;
    }
    return spriteId;
}

#define FUSE_MON        1
#define UNFUSE_MON      2
#define SECOND_FUSE_MON 3

static bool8 CanUseFusionItem(const struct Fusion *itemFusion, enum Item itemId, bool8 checkUnfuse)
{
    u16 i;
    for (i = 0; itemFusion[i].fusionStorageIndex != FUSION_TERMINATOR; i++)
    {
        if (itemFusion[i].itemId != itemId)
            continue;

        if (!checkUnfuse)
            return TRUE;

        if (gPokemonStoragePtr->fusions[itemFusion[i].fusionStorageIndex].level != 0
            && GetMonData(&gPokemonStoragePtr->fusions[itemFusion[i].fusionStorageIndex], MON_DATA_SPECIES) == itemFusion[i].targetSpecies2)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static bool8 IsSecondFusionMon(const struct Fusion *itemFusion, enum Item itemId, u16 firstSpecies, u16 secondSpecies)
{
    u16 i;
    for (i = 0; itemFusion[i].fusionStorageIndex != FUSION_TERMINATOR; i++)
    {
        if (gPokemonStoragePtr->fusions[itemFusion[i].fusionStorageIndex].level != 0)
            continue;
        if (itemFusion[i].itemId == itemId
            && itemFusion[i].targetSpecies1 == firstSpecies
            && itemFusion[i].targetSpecies2 == secondSpecies)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static void DisplayPartyPokemonDataForFusion(u8 slot)
{
    struct Pokemon *mon = &gPlayerParty[slot];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    const struct Fusion *itemFusion = gFusionTablePointers[species];
    u8 fusionMonType = IsFusionMon(species);
    bool8 canUse;

    // No mon selected yet
    if (sFusionFirstMonSlot >= PARTY_SIZE)
    {
        switch (fusionMonType)
        {
        case UNFUSE_MON:
            canUse = CanUseFusionItem(itemFusion, gSpecialVar_ItemId, TRUE);
            break;
        case FUSE_MON:
            canUse = CanUseFusionItem(itemFusion, gSpecialVar_ItemId, FALSE);
            break;
        case SECOND_FUSE_MON:
        default: // Non-fusion mon
            canUse = FALSE;
            break;
        }
        DisplayPartyPokemonDescriptionData(slot, canUse ? PARTYBOX_DESC_ABLE : PARTYBOX_DESC_NOT_ABLE);
    }
    else
    {
        // First mon selected
        if (slot == sFusionFirstMonSlot)
        {
            DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_FIRST);
        }
        else if (fusionMonType == SECOND_FUSE_MON)
        {
            canUse = IsSecondFusionMon(itemFusion, gSpecialVar_ItemId, sFusionFirstMonSpecies, species);
            DisplayPartyPokemonDescriptionData(slot, canUse ? PARTYBOX_DESC_ABLE : PARTYBOX_DESC_NOT_ABLE);
        }
        else
        {
            DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_NOT_ABLE);
        }
    }
}

static void DisplayPartyPokemonDataForFormChange(u8 slot)
{
    struct Pokemon *mon = &gPlayerParty[slot];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u16 targetSpecies;
    bool8 canUse;

    targetSpecies = GetFormChangeTargetSpecies(mon, FORM_CHANGE_ITEM_USE);
    canUse = (targetSpecies != species);

    DisplayPartyPokemonDescriptionData(slot, canUse ? PARTYBOX_DESC_ABLE : PARTYBOX_DESC_NOT_ABLE);
}

static void Task_TryItemUseFusionChange(u8 taskId);
static void SpriteCB_FormChangeIconMosaic(struct Sprite *sprite);

static u8 IsFusionMon(u16 species)
{
    u16 i;
    const struct Fusion *itemFusion = gFusionTablePointers[species];
    if (itemFusion == NULL)
        return FALSE;
    for (i = 0; itemFusion[i].fusionStorageIndex != FUSION_TERMINATOR; i++)
    {
        if (itemFusion[i].fusingIntoMon == species)
            return UNFUSE_MON;
        else if (itemFusion[i].targetSpecies1 == species)
            return FUSE_MON;
        else if (itemFusion[i].targetSpecies2 == species)
            return SECOND_FUSE_MON;
    }
    return FALSE;
}

void FormChangeTeachMove(u8 taskId, enum Move move, u32 slot)
{
    struct Pokemon *mon;

    gPartyMenu.data1 = move;
    gPartyMenu.learnMoveState = 0;

    PlaySE(SE_SELECT);
    mon = &gPlayerParty[slot];
    GetMonNickname(mon, gStringVar1);
    StringCopy(gStringVar2, GetMoveName(move));

    if (GiveMoveToMon(mon, move) != MON_HAS_MAX_MOVES)
    {
        gTasks[taskId].func = Task_LearnedMove;
    }
    else
    {
        DisplayLearnMoveMessage(gText_PkmnNeedsToReplaceMove);
        gTasks[taskId].func = Task_ReplaceMoveYesNo;
    }
}

void DeleteMove(struct Pokemon *mon, enum Move move)
{
    struct BoxPokemon *boxMon = &mon->box;
    u32 i, j;

    if (move != MOVE_NONE)
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            u32 existingMove = GetBoxMonData(boxMon, MON_DATA_MOVE1 + i);
            if (existingMove == move)
            {
                SetMonMoveSlot(mon, MOVE_NONE, i);
                RemoveMonPPBonus(mon, i);
                for (j = i; j < MAX_MON_MOVES - 1; j++)
                    ShiftMoveSlot(&mon->box, j, j + 1);
                break;
            }
        }
    }
}

bool32 DoesMonHaveAnyMoves(struct Pokemon *mon)
{
    struct BoxPokemon *boxMon = &mon->box;
    u32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        enum Move existingMove = GetBoxMonData(boxMon, MON_DATA_MOVE1 + i);
        if (existingMove != MOVE_NONE)
            return TRUE;
    }
    return FALSE;
}

bool32 TryItemUseFusionChange(u8 taskId, TaskFunc task)
{
    u16 targetSpecies = gTasks[taskId].fusionResult;
    s8 *slotPtr = GetCurrentPartySlotPtr();
    *slotPtr = gTasks[taskId].firstFusionSlot;
    if (gTasks[taskId].fusionType == FUSE_MON)
        AnimatePartySlot(gTasks[taskId].secondFusionSlot, 0);
    AnimatePartySlot(*slotPtr, 1);

    if (targetSpecies != SPECIES_NONE)
    {
        gPartyMenuUseExitCallback = TRUE;
        SetWordTaskArg(taskId, tNextFunc, (u32)task);
        gTasks[taskId].func = Task_TryItemUseFusionChange;
        gTasks[taskId].tState = 0;
        gTasks[taskId].tTargetSpecies = targetSpecies;
        gTasks[taskId].tAnimWait = 0;
        return TRUE;
    }
    else
    {
        gPartyMenuUseExitCallback = FALSE;
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = task;
        return FALSE;
    }
}

static void RestoreFusionMon(struct Pokemon *mon)
{
    s32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) == SPECIES_NONE)
            break;
    }

    if (i >= PARTY_SIZE)
    {
        CopyMonToPC(mon);
    }
    else
    {
        CopyMon(&gPlayerParty[i], mon, sizeof(*mon));
        gPlayerPartyCount = i + 1;
    }
}

static void DeleteInvalidFusionMoves(struct Pokemon *mon, u32 species)
{
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        enum Move move = GetMonData(mon, MON_DATA_MOVE1 + i);
        bool32 toDelete = TRUE;
        const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
        for (u32 j = 0; learnset[j].move != LEVEL_UP_MOVE_END;j++)
        {
            if (learnset[j].move == move)
            {
                toDelete = FALSE;
                break;
            }
        }
        if (!toDelete)
            continue;
        const u16 *learnset2 = GetSpeciesTeachableLearnset(species);
        for (u32 j = 0; learnset2[j] != MOVE_UNAVAILABLE;j++)
        {
            if (learnset2[j] == move)
            {
                toDelete = FALSE;
                break;
            }
        }
        if (!toDelete)
            continue;
        const u16 *learnset3 = GetSpeciesEggMoves(species);
        for (u32 j = 0; learnset3[j] != MOVE_UNAVAILABLE;j++)
        {
            if (learnset3[j] == move)
            {
                toDelete = FALSE;
                break;
            }
        }
        if (toDelete)
            DeleteMove(mon, move);
    }
}

#if P_FUSION_FORMS
static void SwapFusionMonMoves(struct Pokemon *mon, const u16 moveTable[][2], u32 mode)
{
    u32 oldMoveIndex, newMoveIndex;
    if (mode == FUSE_MON)
    {
        oldMoveIndex = 0;
        newMoveIndex = 1;
    }
    else //mode == UNFUSE_MON
    {
        oldMoveIndex = 1;
        newMoveIndex = 0;
    }
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        enum Move move = GetMonData(mon, MON_DATA_MOVE1 + i);
        for (u32 j = 0; j < 2; j++)
        {
            if (move == moveTable[j][oldMoveIndex])
            {
                u32 pp = GetMovePP(moveTable[j][newMoveIndex]);
                SetMonData(mon, MON_DATA_MOVE1 + i, &moveTable[j][newMoveIndex]);
                SetMonData(mon, MON_DATA_PP1 + i, &pp);
            }
        }
    }

}
#endif //P_FUSION_FORMS

static void Task_TryItemUseFusionChange(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gTasks[taskId].firstFusionSlot];
    struct Sprite *icon = &gSprites[sPartyMenuBoxes[gTasks[taskId].firstFusionSlot].monSpriteId];
    struct Pokemon *mon2;
    struct Sprite *icon2 = &gSprites[sPartyMenuBoxes[gTasks[taskId].secondFusionSlot].monSpriteId];
    u16 targetSpecies;

    switch (gTasks[taskId].tState)
    {
    case 0:
        if (gTasks[taskId].fusionType == FUSE_MON)
        {
            mon2 = &gPlayerParty[gTasks[taskId].secondFusionSlot];
            CopyMon(&gPokemonStoragePtr->fusions[gTasks[taskId].storageIndex], mon2, sizeof(*mon2));
            ZeroMonData(&gPlayerParty[gTasks[taskId].secondFusionSlot]);
        }
        else
        {
            mon2 = &gPokemonStoragePtr->fusions[gTasks[taskId].storageIndex];
            RestoreFusionMon(mon2);
            ZeroMonData(&gPokemonStoragePtr->fusions[gTasks[taskId].storageIndex]);
        }
        targetSpecies = gTasks[taskId].tTargetSpecies;
        SetMonData(mon, MON_DATA_SPECIES, &targetSpecies);
        CalculateMonStats(mon);
        CompactPartySlots();
        CalculatePlayerPartyCount();
        gTasks[taskId].tState++;
        PlaySE(SE_M_TELEPORT);
        break;
    case 1:
        targetSpecies = gTasks[taskId].tTargetSpecies;
        if (gTasks[taskId].tAnimWait == 0)
        {
            icon->oam.mosaic = TRUE;
            icon->data[0] = MOSAIC_ANIM_DURATION;
            icon->data[1] = 1;
            icon->data[2] = taskId;
            icon->callback = SpriteCB_FormChangeIconMosaic;
            SetGpuReg(REG_OFFSET_MOSAIC, (icon->data[0] << 12) | (icon->data[1] << 8));
            if (gTasks[taskId].fusionType == FUSE_MON)
            {
                icon2->oam.mosaic = TRUE;
                icon2->data[0] = MOSAIC_ANIM_DURATION;
                icon2->data[1] = 1;
                icon2->data[2] = taskId;
                icon2->callback = SpriteCB_FormChangeIconMosaic;
                SetGpuReg(REG_OFFSET_MOSAIC, (icon2->data[0] << 12) | (icon2->data[1] << 8));
            }
            DestroyMonSprite();
            sMonSpriteId = LoadAndApplyMosaicToMonSprite(mon, FALSE);
            sMonShadowSpriteId = LoadAndApplyMosaicToMonSprite(mon, TRUE);
            UpdateSelectedMonItemSprite();
        }

        if (++gTasks[taskId].tAnimWait == 60)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
            gTasks[taskId].tState++;
        }
        break;
    case 2:
        if (gPaletteFade.active)
            break;
        if (gTasks[taskId].fusionType == FUSE_MON && gTasks[taskId].firstFusionSlot > gTasks[taskId].secondFusionSlot)
        {
            gTasks[taskId].firstFusionSlot--;
            gPartyMenu.slotId--;
        }
        RefreshPartyMenu();
        gTasks[taskId].tState++;
        break;
    case 3:
        BeginNormalPaletteFade(PALETTES_ALL, 16, 0, 0, RGB_WHITEALPHA);
        gTasks[taskId].tState++;
        break;
    case 4:
        targetSpecies = gTasks[taskId].tTargetSpecies;
        PlayCry_Normal(targetSpecies, 0);
        gTasks[taskId].tState++;
        break;
    case 5:
        if (IsCryFinished())
        {
            GetMonNickname(mon, gStringVar1);
            StringExpandPlaceholders(gStringVar4, gText_PkmnTransformed);
            DisplayPartyMenuMessage(gStringVar4, FALSE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].tState++;
        }
        break;
    case 6:
        if (!IsPartyMenuTextPrinterActive())
        {
            if (gTasks[taskId].fusionType == FUSE_MON)
            {
#if P_FUSION_FORMS
#if P_FAMILY_KYUREM
#if P_FAMILY_RESHIRAM
                if (gTasks[taskId].tExtraMoveHandling == SWAP_EXTRA_MOVES_KYUREM_WHITE)
                    SwapFusionMonMoves(mon, gKyuremWhiteSwapMoveTable, FUSE_MON);
#endif //P_FAMILY_RESHIRAM
#if P_FAMILY_ZEKROM
                if (gTasks[taskId].tExtraMoveHandling == SWAP_EXTRA_MOVES_KYUREM_BLACK)
                    SwapFusionMonMoves(mon, gKyuremBlackSwapMoveTable, FUSE_MON);
#endif //P_FAMILY_ZEKROM
#endif //P_FAMILY_KYUREM
#endif //P_FUSION_FORMS
                if (gTasks[taskId].moveToLearn != 0)
                    FormChangeTeachMove(taskId, gTasks[taskId].moveToLearn, gTasks[taskId].firstFusionSlot);
            }
            else //(gTasks[taskId].fusionType == UNFUSE_MON)
            {
#if P_FUSION_FORMS
#if P_FAMILY_KYUREM
#if P_FAMILY_RESHIRAM
                if (gTasks[taskId].tExtraMoveHandling == SWAP_EXTRA_MOVES_KYUREM_WHITE)
                    SwapFusionMonMoves(mon, gKyuremWhiteSwapMoveTable, UNFUSE_MON);
#endif //P_FAMILY_RESHIRAM
#if P_FAMILY_ZEKROM
                if (gTasks[taskId].tExtraMoveHandling == SWAP_EXTRA_MOVES_KYUREM_BLACK)
                    SwapFusionMonMoves(mon, gKyuremBlackSwapMoveTable, UNFUSE_MON);
#endif //P_FAMILY_ZEKROM
#endif //P_FAMILY_KYUREM
#endif //P_FUSION_FORMS
                if ( gTasks[taskId].tExtraMoveHandling == FORGET_EXTRA_MOVES)
                {
                    DeleteInvalidFusionMoves(mon, gTasks[taskId].fusionResult);
                    if (!DoesMonHaveAnyMoves(mon))
                        FormChangeTeachMove(taskId, MOVE_CONFUSION, gTasks[taskId].firstFusionSlot);
                }
            }
            gTasks[taskId].tState++;
        }
        break;
    case 7:
        gTasks[taskId].func = (void *)GetWordTaskArg(taskId, tNextFunc);
        break;
    }
}

void ItemUseCB_Fusion(u8 taskId, TaskFunc taskFunc)
{
    u16 i;
    struct Task *task = &gTasks[taskId];
    u8 slotId = gPartyMenu.slotId;

    if (gPartyMenu.action == PARTY_ACTION_FUSION)
        slotId = gPartyMenu.slotId2;

    u16 species = GetMonData(&gPlayerParty[slotId], MON_DATA_SPECIES);
    const struct Fusion *itemFusion = gFusionTablePointers[species];

    PlaySE(SE_SELECT);
    switch (IsFusionMon(species))
    {
    case FALSE: // Cancel if Not a Fuse Mon
        break;
    case UNFUSE_MON:
        if (task->fusionType == FUSE_MON) // Cancel if An already Fused Mon Is Chosen For The Second Fusion Mon
            break;
        if (gPlayerPartyCount == PARTY_SIZE)
        {
            gPartyMenuUseExitCallback = FALSE;
            DisplayPartyMenuMessage(gText_YourPartysFull, TRUE);
            ScheduleBgCopyTilemapToVram(2);
            task->func = Task_ReturnToChooseMonAfterText;
            return;
        }
        for (i = 0; itemFusion[i].fusionStorageIndex != FUSION_TERMINATOR; i++) // Loops through fusion table and checks if the mon can be unfused
        {
            if (gPokemonStoragePtr->fusions[itemFusion[i].fusionStorageIndex].level == 0)
                continue;
            if (itemFusion[i].itemId == gSpecialVar_ItemId && GetMonData(&gPokemonStoragePtr->fusions[itemFusion[i].fusionStorageIndex], MON_DATA_SPECIES) == itemFusion[i].targetSpecies2)
            {
                task->fusionType = UNFUSE_MON;
                task->firstFusion = species;
                task->firstFusionSlot = gPartyMenu.slotId;
                task->storageIndex = itemFusion[i].fusionStorageIndex;
                task->fusionResult = itemFusion[i].targetSpecies1;
                task->unfuseSecondMon = itemFusion[i].targetSpecies2;
                task->tExtraMoveHandling = itemFusion[i].extraMoveHandling;
                task->forgetMove = itemFusion[i].fusionMove;

                sFusionFirstMonSlot = 0;
                sFusionFirstMonSpecies = 0;
                TryItemUseFusionChange(taskId, taskFunc);
                return;
            }
        }
        break;
    case FUSE_MON:
        if (task->fusionType == FUSE_MON) // Cancel If Second Mon is Another First Fusion Mon
            break;
        for (i = 0; itemFusion[i].fusionStorageIndex != FUSION_TERMINATOR; i++) // Run through the Fusion table for each species and check if the item matches one of the entries
        {
            if (itemFusion[i].itemId == gSpecialVar_ItemId)
            {
                task->fusionType = FUSE_MON;
                task->firstFusion = species;
                task->firstFusionSlot = gPartyMenu.slotId;
                task->storageIndex = itemFusion[i].fusionStorageIndex;

                sFusionFirstMonSlot = gPartyMenu.slotId;
                sFusionFirstMonSpecies = species;
                DisplayPartyPokemonDataForFusion(gPartyMenu.slotId);
                CopyWindowToVram(sPartyMenuBoxes[gPartyMenu.slotId].windowId, COPYWIN_GFX);
                for (i = 0; i < PARTY_SIZE; i++)
                {
                    u16 slotSpecies;
                    u8 fusionType;

                    if (i == gPartyMenu.slotId)
                        continue;

                    slotSpecies = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
                    if (slotSpecies == SPECIES_NONE)
                        continue;

                    fusionType = IsFusionMon(slotSpecies);
                    if (fusionType != FALSE)
                    {
                        DisplayPartyPokemonDataForFusion(i);
                        CopyWindowToVram(sPartyMenuBoxes[i].windowId, COPYWIN_GFX);
                    }
                }
                ScheduleBgCopyTilemapToVram(2);
                task->func = Task_HandleChooseMonInput;
                gPartyMenuUseExitCallback = FALSE;
                sPartyMenuInternal->exitCallback = NULL;
                PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
                return;
            }
        }
        break;
    case SECOND_FUSE_MON:
        if (task->fusionType != FUSE_MON) // Cancel if Secondary Fusion Mon Chosen First
            break;
        for (i = 0; itemFusion[i].fusionStorageIndex != FUSION_TERMINATOR; i++) // run through fusion table and check if the fusion works
        {
            if (gPokemonStoragePtr->fusions[itemFusion[i].fusionStorageIndex].level != 0)
                continue;
            if (itemFusion[i].itemId == gSpecialVar_ItemId && itemFusion[i].targetSpecies1 == task->firstFusion && itemFusion[i].targetSpecies2 == species)
            {
                task->storageIndex = itemFusion[i].fusionStorageIndex;
                task->fusionResult = itemFusion[i].fusingIntoMon;
                task->secondFusionSlot = slotId;
                task->moveToLearn = itemFusion[i].fusionMove;
                task->tExtraMoveHandling = itemFusion[i].extraMoveHandling;

                sFusionFirstMonSlot = 0;
                sFusionFirstMonSpecies = 0;
                // Start Fusion
                TryItemUseFusionChange(taskId, taskFunc);
                return;
            }
        }
        break;
    }
    // No Effect - stay party menu
    gPartyMenuUseExitCallback = FALSE;
    DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    if (task->fusionType != FUSE_MON)
    {
        sFusionFirstMonSlot = 0;
        sFusionFirstMonSpecies = 0;
    }
    task->func = Task_ReturnToChooseMonAfterText;
    return;
}

#undef fusionType
#undef firstFusion
#undef firstFusionSlot
#undef fusionResult
#undef secondFusionSlot
#undef unfuseSecondMon
#undef moveToLearn
#undef forgetMove
#undef storageIndex

#undef FUSE_MON
#undef UNFUSE_MON
#undef SECOND_FUSE_MON

static void SpriteCB_FormChangeIconMosaic(struct Sprite *sprite)
{
    u8 taskId = sprite->data[2];

    sprite->data[0] -= sprite->data[1];

    if (sprite->data[0] <= 0)
    {
        if (gTasks[taskId].tAnimWait == 60)
            sprite->data[0] = 0;
        else
            sprite->data[0] = MOSAIC_ANIM_DURATION;
    }

    SetGpuReg(REG_OFFSET_MOSAIC, (sprite->data[0] << 12) | (sprite->data[1] << 8));

    if (sprite->data[0] == 0)
    {
        sprite->oam.mosaic = FALSE;
        sprite->callback = SpriteCallbackDummy;
    }
}

static void Task_TryItemUseFormChange(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    struct Sprite *icon = &gSprites[sPartyMenuBoxes[gPartyMenu.slotId].monSpriteId];

    switch (gTasks[taskId].tState)
    {
    case 0:
        PlaySE(SE_M_TELEPORT);
        gTasks[taskId].tState++;
        break;
    case 1:
        if (gTasks[taskId].tAnimWait == 0)
        {
            FreeAndDestroyMonIconSprite(icon);
            CreatePartyMonIconSpriteParameterized(gTasks[taskId].tTargetSpecies, GetMonData(mon, MON_DATA_PERSONALITY), GetMonData(mon, MON_DATA_IS_SHINY, NULL), FALSE, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
            icon->oam.mosaic = TRUE;
            icon->data[5] = MOSAIC_ANIM_DURATION;
            icon->data[6] = 1;
            icon->callback = SpriteCB_MosaicAnim;
            SetGpuReg(REG_OFFSET_MOSAIC, (icon->data[5] << 12) | (icon->data[5] << 8));

            DestroyMonSprite();
            sMonSpriteId = LoadAndApplyMosaicToMonSprite(mon, FALSE);
            sMonShadowSpriteId = LoadAndApplyMosaicToMonSprite(mon, TRUE);
            UpdateSelectedMonItemSprite();
        }
        if (++gTasks[taskId].tAnimWait == 60)
            gTasks[taskId].tState++;
        break;
    case 2:
        PlayCry_Normal(gTasks[taskId].tTargetSpecies, 0);
        gTasks[taskId].tState++;
        break;
    case 3:
        if (IsCryFinished())
        {
            GetMonNickname(mon, gStringVar1);
            StringExpandPlaceholders(gStringVar4, gText_PkmnTransformed);
            DisplayPartyMenuMessage(gStringVar4, FALSE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].tState++;
        }

        break;
    case 4:
        if (!IsPartyMenuTextPrinterActive())
        {
            if (gSpecialVar_ItemId == ITEM_ROTOM_CATALOG) //only for Rotom currently
            {
                u32 i;
                for (i = 0; i < ARRAY_COUNT(sRotomFormChangeMoves); i++)
                    DeleteMove(mon, sRotomFormChangeMoves[i]);

                if (I_ROTOM_CATALOG_THUNDER_SHOCK < GEN_9 && gSpecialVar_0x8000 == ROTOM_BASE_MOVE)
                {
                    if (!DoesMonHaveAnyMoves(mon))
                        FormChangeTeachMove(taskId, gSpecialVar_0x8000, gPartyMenu.slotId);
                }
                else
                    FormChangeTeachMove(taskId, gSpecialVar_0x8000, gPartyMenu.slotId);
            }

            gTasks[taskId].tState++;
        }
        break;
    case 5:
        gTasks[taskId].func = (void *)GetWordTaskArg(taskId, tNextFunc);
        break;
    }
}

bool32 TryItemUseFormChange(u8 taskId, TaskFunc task)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    if (TryFormChange(mon, FORM_CHANGE_ITEM_USE))
    {
        gPartyMenuUseExitCallback = TRUE;
        SetWordTaskArg(taskId, tNextFunc, (u32)task);
        gTasks[taskId].func = Task_TryItemUseFormChange;
        gTasks[taskId].tState = 0;
        gTasks[taskId].tTargetSpecies = GetMonData(mon, MON_DATA_SPECIES);
        gTasks[taskId].tAnimWait = 0;
        return TRUE;
    }
    else
    {
        gPartyMenuUseExitCallback = FALSE;
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_ReturnToChooseMonAfterText;
        return FALSE;
    }
}

void ItemUseCB_FormChange(u8 taskId, TaskFunc task)
{
    TryItemUseFormChange(taskId, task);
}

void ItemUseCB_FormChange_ConsumedOnUse(u8 taskId, TaskFunc task)
{
    if (TryItemUseFormChange(taskId, task))
        RemoveBagItem(gSpecialVar_ItemId, 1);
}

static bool32 IsRotomFormSpecies(u16 species)
{
    return GET_BASE_SPECIES_ID(species) == SPECIES_ROTOM;
}

static u16 GetRotomSpeciesForFormMove(enum Move move)
{
    switch (move)
    {
    case MOVE_THUNDER_SHOCK:
        return SPECIES_ROTOM;
    case MOVE_OVERHEAT:
        return SPECIES_ROTOM_HEAT;
    case MOVE_HYDRO_PUMP:
        return SPECIES_ROTOM_WASH;
    case MOVE_BLIZZARD:
        return SPECIES_ROTOM_FROST;
    case MOVE_AIR_SLASH:
        return SPECIES_ROTOM_FAN;
    case MOVE_LEAF_STORM:
        return SPECIES_ROTOM_MOW;
    default:
        return SPECIES_NONE;
    }
}

void ChangeRotomForm(void)
{
    struct Pokemon *mon;
    u32 i;
    u16 move = gSpecialVar_0x8000;
    u16 targetSpecies = GetRotomSpeciesForFormMove(move);
    u16 currentSpecies;

    gSpecialVar_Result = FALSE;
    if (gSpecialVar_0x8004 >= PARTY_SIZE || targetSpecies == SPECIES_NONE)
        return;

    mon = &gPlayerParty[gSpecialVar_0x8004];
    currentSpecies = GetMonData(mon, MON_DATA_SPECIES);
    if (!IsRotomFormSpecies(currentSpecies))
        return;

    if (currentSpecies == targetSpecies)
    {
        targetSpecies = SPECIES_ROTOM;
        move = MOVE_THUNDER_SHOCK;
    }

    for (i = 0; i < ARRAY_COUNT(sRotomFormChangeMoves); i++)
        DeleteMove(mon, sRotomFormChangeMoves[i]);

    if (move != MOVE_THUNDER_SHOCK || I_ROTOM_CATALOG_THUNDER_SHOCK >= GEN_9 || !DoesMonHaveAnyMoves(mon))
    {
        if (GiveMoveToMon(mon, move) == MON_HAS_MAX_MOVES)
            SetMonMoveSlot(mon, move, MAX_MON_MOVES - 1);
    }

    SetMonData(mon, MON_DATA_SPECIES, &targetSpecies);
    CalculateMonStats(mon);
    RefreshFollowingPokemon();
    gSpecialVar_Result = TRUE;
}

void ItemUseCB_RotomCatalog(u8 taskId, TaskFunc task)
{
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, ACTIONS_ROTOM_CATALOG);
    DisplaySelectionWindow(SELECTWINDOW_CATALOG);
    gTasks[taskId].data[0] = 0xFF;
    gTasks[taskId].func = Task_HandleSelectionMenuInput;
}

bool32 TryMultichoiceFormChange(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);

    if (TryFormChange(mon, FORM_CHANGE_ITEM_USE_MULTICHOICE))
    {
        gPartyMenuUseExitCallback = TRUE;
        SetWordTaskArg(taskId, tNextFunc, (u32)Task_ClosePartyMenuAfterText);
        gTasks[taskId].func = Task_TryItemUseFormChange;
        gTasks[taskId].tState = 0;
        gTasks[taskId].tTargetSpecies = GetMonData(mon, MON_DATA_SPECIES);
        gTasks[taskId].tAnimWait = 0;
        return TRUE;
    }
    else
    {
        gPartyMenuUseExitCallback = FALSE;
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(gText_WontHaveEffect, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_ClosePartyMenuAfterText;
        return FALSE;
    }
}

static void CursorCb_CatalogBulb(u8 taskId)
{
    gSpecialVar_Result = 0;
    gSpecialVar_0x8000 = ROTOM_BASE_MOVE;
    TryMultichoiceFormChange(taskId);
}

static void CursorCb_CatalogOven(u8 taskId)
{
    gSpecialVar_Result = 1;
    gSpecialVar_0x8000 = ROTOM_HEAT_MOVE;
    TryMultichoiceFormChange(taskId);
}

static void CursorCb_CatalogWashing(u8 taskId)
{
    gSpecialVar_Result = 2;
    gSpecialVar_0x8000 = ROTOM_WASH_MOVE;
    TryMultichoiceFormChange(taskId);
}

static void CursorCb_CatalogFridge(u8 taskId)
{
    gSpecialVar_Result = 3;
    gSpecialVar_0x8000 = ROTOM_FROST_MOVE;
    TryMultichoiceFormChange(taskId);
}

static void CursorCb_CatalogFan(u8 taskId)
{
    gSpecialVar_Result = 4;
    gSpecialVar_0x8000 = ROTOM_FAN_MOVE;
    TryMultichoiceFormChange(taskId);
}

static void CursorCb_CatalogMower(u8 taskId)
{
    gSpecialVar_Result = 5;
    gSpecialVar_0x8000 = ROTOM_MOW_MOVE;
    TryMultichoiceFormChange(taskId);
}

void ItemUseCB_ZygardeCube(u8 taskId, TaskFunc task)
{
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, ACTIONS_ZYGARDE_CUBE);
    DisplaySelectionWindow(SELECTWINDOW_ZYGARDECUBE);
    gTasks[taskId].data[0] = 0xFF;
    gTasks[taskId].func = Task_HandleSelectionMenuInput;
}

static void CursorCb_ChangeForm(u8 taskId)
{
    gSpecialVar_Result = 0;
    TryMultichoiceFormChange(taskId);
}

static void CursorCb_ChangeAbility(u8 taskId)
{
    gSpecialVar_Result = 1;
    TryMultichoiceFormChange(taskId);
}

void TryItemHoldFormChange(struct Pokemon *mon, s8 slotId)
{
    if (TryFormChange(mon, FORM_CHANGE_ITEM_HOLD))
    {
        u32 species = GetMonData(mon, MON_DATA_SPECIES);
        PlayCry_NormalNoDucking(species, 0, CRY_VOLUME_RS, CRY_VOLUME_RS);
        FreeAndDestroyMonIconSprite(&gSprites[sPartyMenuBoxes[slotId].monSpriteId]);
        //CreatePartyMonIconSpriteParameterized(species, GetMonData(mon, MON_DATA_PERSONALITY), FALSE, &sPartyMenuBoxes[slotId], 1);
        CreatePartyMonIconSpriteParameterized(species, GetMonData(mon, MON_DATA_PERSONALITY), GetMonData(mon, MON_DATA_IS_SHINY), FALSE, &sPartyMenuBoxes[slotId], 1);
        
        UpdatePartyMonHeldItemSprite(mon, &sPartyMenuBoxes[slotId]);

        // Mosaic anim for animated mon sprite
        if (slotId == gPartyMenu.slotId)
        {
            DestroyMonSprite();
            sMonSpriteId = LoadAndApplyMosaicToMonSprite(mon, FALSE);
            sMonShadowSpriteId = LoadAndApplyMosaicToMonSprite(mon, TRUE);
            UpdateSelectedMonItemSprite();
        }
    }
}

#undef tState
#undef tTargetSpecies
#undef tAnimWait
#undef tNextFunc

enum ItemEffectType GetItemEffectType(enum Item item)
{
    u32 statusCure;
    const u8 *itemEffect = GetItemEffect(item);

    if (itemEffect == NULL)
        return ITEM_EFFECT_NONE;

    if ((itemEffect[0] & ITEM0_DIRE_HIT) || itemEffect[1] || (itemEffect[3] & ITEM3_GUARD_SPEC))
        return ITEM_EFFECT_X_ITEM;
    else if (itemEffect[0] & ITEM0_SACRED_ASH)
        return ITEM_EFFECT_SACRED_ASH;
    else if (itemEffect[3] & ITEM3_LEVEL_UP)
        return ITEM_EFFECT_RAISE_LEVEL;

    statusCure = itemEffect[3] & ITEM3_STATUS_ALL;
    if (statusCure || (itemEffect[0] >> 7))
    {
        if (statusCure == ITEM3_SLEEP)
            return ITEM_EFFECT_CURE_SLEEP;
        else if (statusCure == ITEM3_POISON)
            return ITEM_EFFECT_CURE_POISON;
        else if (statusCure == ITEM3_BURN)
            return ITEM_EFFECT_CURE_BURN;
        else if (statusCure == ITEM3_FREEZE)
            return ITEM_EFFECT_CURE_FREEZE_FROSTBITE;
        else if (statusCure == ITEM3_PARALYSIS)
            return ITEM_EFFECT_CURE_PARALYSIS;
        else if (statusCure == ITEM3_CONFUSION)
            return ITEM_EFFECT_CURE_CONFUSION;
        else if (itemEffect[0] >> 7 && !statusCure)
            return ITEM_EFFECT_CURE_INFATUATION;
        else
            return ITEM_EFFECT_CURE_ALL_STATUS;
    }

    if (itemEffect[4] & (ITEM4_REVIVE | ITEM4_HEAL_HP))
        return ITEM_EFFECT_HEAL_HP;
    else if (itemEffect[4] & ITEM4_EV_ATK)
        return ITEM_EFFECT_ATK_EV;
    else if (itemEffect[4] & ITEM4_EV_HP)
        return ITEM_EFFECT_HP_EV;
    else if (itemEffect[5] & ITEM5_EV_SPATK)
        return ITEM_EFFECT_SPATK_EV;
    else if (itemEffect[5] & ITEM5_EV_SPDEF)
        return ITEM_EFFECT_SPDEF_EV;
    else if (itemEffect[5] & ITEM5_EV_SPEED)
        return ITEM_EFFECT_SPEED_EV;
    else if (itemEffect[5] & ITEM5_EV_DEF)
        return ITEM_EFFECT_DEF_EV;
    else if (itemEffect[10] & ITEM10_IV_HP)
        return ITEM_EFFECT_HP_IV;
    else if (itemEffect[10] & ITEM10_IV_ATK)
        return ITEM_EFFECT_ATK_IV;
    else if (itemEffect[10] & ITEM10_IV_DEF)
        return ITEM_EFFECT_DEF_IV;
    else if (itemEffect[10] & ITEM10_IV_SPEED)
        return ITEM_EFFECT_SPEED_IV;
    else if (itemEffect[10] & ITEM10_IV_SPATK)
        return ITEM_EFFECT_SPATK_IV;
    else if (itemEffect[10] & ITEM10_IV_SPDEF)
        return ITEM_EFFECT_SPDEF_IV;
    else if ((itemEffect[10] & ITEM10_REDUCE_IV) && itemEffect[9] == ITEM9_REDUCE_IV_HP)
        return ITEM_EFFECT_HP_IV_REDUCE;
    else if ((itemEffect[10] & ITEM10_REDUCE_IV) && itemEffect[9] == ITEM9_REDUCE_IV_ATK)
        return ITEM_EFFECT_ATK_IV_REDUCE;
    else if ((itemEffect[10] & ITEM10_REDUCE_IV) && itemEffect[9] == ITEM9_REDUCE_IV_DEF)
        return ITEM_EFFECT_DEF_IV_REDUCE;
    else if ((itemEffect[10] & ITEM10_REDUCE_IV) && itemEffect[9] == ITEM9_REDUCE_IV_SPEED)
        return ITEM_EFFECT_SPEED_IV_REDUCE;
    else if ((itemEffect[10] & ITEM10_REDUCE_IV) && itemEffect[9] == ITEM9_REDUCE_IV_SPATK)
        return ITEM_EFFECT_SPATK_IV_REDUCE;
    else if ((itemEffect[10] & ITEM10_REDUCE_IV) && itemEffect[9] == ITEM9_REDUCE_IV_SPDEF)
        return ITEM_EFFECT_SPDEF_IV_REDUCE;
    else if (itemEffect[4] & ITEM4_EVO_STONE)
        return ITEM_EFFECT_EVO_STONE;
    else if (itemEffect[4] & ITEM4_PP_UP)
        return ITEM_EFFECT_PP_UP;
    else if (itemEffect[5] & ITEM5_PP_MAX)
        return ITEM_EFFECT_PP_MAX;
    else if (itemEffect[4] & (ITEM4_HEAL_PP | ITEM4_HEAL_PP_ONE))
        return ITEM_EFFECT_HEAL_PP;
    else
        return ITEM_EFFECT_NONE;
}

static void TryTutorSelectedMon(u8 taskId)
{
    struct Pokemon *mon;
    s16 *move;

    if (!gPaletteFade.active)
    {
        mon = &gPlayerParty[gPartyMenu.slotId];
        move = &gPartyMenu.data1;
        GetMonNickname(mon, gStringVar1);
        gPartyMenu.data1 = gSpecialVar_0x8005;
        StringCopy(gStringVar2, GetMoveName(gPartyMenu.data1));
        move[1] = 2;
        switch (CanTeachMove(mon, gPartyMenu.data1))
        {
        case CANNOT_LEARN_MOVE:
            DisplayLearnMoveMessageAndClose(taskId, gText_PkmnCantLearnMove);
            return;
        case ALREADY_KNOWS_MOVE:
            DisplayLearnMoveMessageAndClose(taskId, gText_PkmnAlreadyKnows);
            return;
        default:
            if (GiveMoveToMon(mon, gPartyMenu.data1) != MON_HAS_MAX_MOVES)
            {
                Task_LearnedMove(taskId);
                return;
            }
            break;
        }
        DisplayLearnMoveMessage(gText_PkmnNeedsToReplaceMove);
        gTasks[taskId].func = Task_ReplaceMoveYesNo;
    }
}

void CB2_PartyMenuFromStartMenu(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_FIELD, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ReturnToFieldWithOpenMenu);
}

// Giving an item by selecting Give from the bag menu
// As opposted to by selecting Give in the party menu, which is handled by CursorCb_Give
void CB2_ChooseMonToGiveItem(void)
{
    MainCallback callback = (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE) ? CB2_ReturnToBagMenu : CB2_ReturnToPyramidBagMenu;
    InitPartyMenu(PARTY_MENU_TYPE_FIELD, PARTY_LAYOUT_SINGLE, PARTY_ACTION_GIVE_ITEM, FALSE, PARTY_MSG_GIVE_TO_WHICH_MON, Task_HandleChooseMonInput, callback);
    gPartyMenu.bagItem = gSpecialVar_ItemId;
}

static void TryGiveItemOrMailToSelectedMon(u8 taskId)
{
    sPartyMenuItemId = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM);
    if (sPartyMenuItemId == ITEM_NONE)
    {
        GiveItemOrMailToSelectedMon(taskId);
    }
    else if (ItemIsMail(sPartyMenuItemId))
    {
        DisplayItemMustBeRemovedFirstMessage(taskId);
    }
    else
    {
        DisplayAlreadyHoldingItemSwitchMessage(&gPlayerParty[gPartyMenu.slotId], sPartyMenuItemId, TRUE);
        gTasks[taskId].func = Task_SwitchItemsFromBagYesNo;
    }
}

static void GiveItemOrMailToSelectedMon(u8 taskId)
{
    if (ItemIsMail(gPartyMenu.bagItem))
    {
        RemoveBagItem(gPartyMenu.bagItem, 1);
        sPartyMenuInternal->exitCallback = CB2_WriteMailToGiveMonFromBag;
        Task_ClosePartyMenu(taskId);
    }
    else
    {
        GiveItemToSelectedMon(taskId);
    }
}

static void GiveItemToSelectedMon(u8 taskId)
{
    enum Item item;

    if (!gPaletteFade.active)
    {
        item = gPartyMenu.bagItem;
        GiveItemToMon(&gPlayerParty[gPartyMenu.slotId], item);
        RemoveHeldItemFromBag(item);

        // Visually update cursor and held item sprites
        UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuBoxes[gPartyMenu.slotId]);
        gSpecialVar_ItemId = ITEM_NONE;
        DestroyHoverSprite();
        CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);

        DisplayGaveHeldItemMessage(&gPlayerParty[gPartyMenu.slotId], item, FALSE, 1);
        gTasks[taskId].func = Task_UpdateHeldItemSpriteAndClosePartyMenu;
    }
}

static void Task_UpdateHeldItemSpriteAndClosePartyMenu(u8 taskId)
{
    s8 slot = gPartyMenu.slotId;

    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        UpdatePartyMonHeldItemSprite(&gPlayerParty[slot], &sPartyMenuBoxes[slot]);
        Task_ClosePartyMenu(taskId);
    }
}

static void CB2_WriteMailToGiveMonFromBag(void)
{
    u8 mail;

    GiveItemToMon(&gPlayerParty[gPartyMenu.slotId], gPartyMenu.bagItem);
    mail = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_MAIL);
    DoEasyChatScreen(
        EASY_CHAT_TYPE_MAIL,
        gSaveBlock1Ptr->mail[mail].words,
        CB2_ReturnToPartyOrBagMenuFromWritingMail,
        EASY_CHAT_PERSON_DISPLAY_NONE);
}

static void CB2_ReturnToPartyOrBagMenuFromWritingMail(void)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = GetMonData(mon, MON_DATA_HELD_ITEM);

    // Canceled writing mail
    if (gSpecialVar_Result == FALSE)
    {
        TakeMailFromMon(mon);
        SetMonData(mon, MON_DATA_HELD_ITEM, &sPartyMenuItemId);
        RemoveHeldItemFromBag(sPartyMenuItemId);
        ReturnGiveItemToBagOrPC(item);
        SetMainCallback2(gPartyMenu.exitCallback);
    }
    // Wrote mail
    else
    {
        InitPartyMenu(gPartyMenu.menuType, KEEP_PARTY_LAYOUT, gPartyMenu.action, TRUE, PARTY_MSG_NONE, Task_DisplayGaveMailFromBagMessage, gPartyMenu.exitCallback);
    }
}

static void Task_DisplayGaveMailFromBagMessage(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (sPartyMenuItemId != ITEM_NONE)
            DisplaySwitchedHeldItemMessage(gPartyMenu.bagItem, sPartyMenuItemId, FALSE);
        else
            DisplayGaveHeldItemMessage(&gPlayerParty[gPartyMenu.slotId], gPartyMenu.bagItem, FALSE, 1);
        gTasks[taskId].func = Task_UpdateHeldItemSpriteAndClosePartyMenu;
    }
}

static void Task_SwitchItemsFromBagYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleSwitchItemsFromBagYesNoInput;
    }
}

static void Task_HandleSwitchItemsFromBagYesNoInput(u8 taskId)
{
    enum Item item;

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // Yes, switch items
        item = gPartyMenu.bagItem;
        RemoveHeldItemFromBag(item);
        if (AddHeldItemToBag(sPartyMenuItemId) == FALSE)
        {
            ReturnGiveItemToBagOrPC(item);
            BufferBagFullCantTakeItemMessage(sPartyMenuItemId);
            DisplayPartyMenuMessage(gStringVar4, FALSE);
            gTasks[taskId].func = Task_UpdateHeldItemSpriteAndClosePartyMenu;
        }
        else if (ItemIsMail(item))
        {
            sPartyMenuInternal->exitCallback = CB2_WriteMailToGiveMonFromBag;
            Task_ClosePartyMenu(taskId);
        }
        else
        {
            GiveItemToMon(&gPlayerParty[gPartyMenu.slotId], item);

            // Visually update cursor and held item sprites
            UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuBoxes[gPartyMenu.slotId]);
            gSpecialVar_ItemId = ITEM_NONE;
            DestroyHoverSprite();
            CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);

            DisplaySwitchedHeldItemMessage(item, sPartyMenuItemId, TRUE);
            gTasks[taskId].func = Task_UpdateHeldItemSpriteAndClosePartyMenu;
        }
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1: // No, dont switch items
        gTasks[taskId].func = Task_UpdateHeldItemSpriteAndClosePartyMenu;
        break;
    }
}

static void DisplayItemMustBeRemovedFirstMessage(u8 taskId)
{
    DisplayPartyMenuMessage(gText_RemoveMailBeforeItem, TRUE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_UpdateHeldItemSpriteAndClosePartyMenu;
}

// Returns FALSE if there was no space to return the item
// but there always should be, and the return is ignored in all uses
static bool8 ReturnGiveItemToBagOrPC(enum Item item)
{
    if (IsItemInfiniteHold(item))
        return AddHeldItemToBag(item);

    if (gPartyMenu.action == PARTY_ACTION_GIVE_ITEM)
        return AddBagItem(item, 1);
    else
        return AddPCItem(item, 1);
}

void ChooseMonToGiveMailFromMailbox(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_FIELD, PARTY_LAYOUT_SINGLE, PARTY_ACTION_GIVE_MAILBOX_MAIL, FALSE, PARTY_MSG_GIVE_TO_WHICH_MON, Task_HandleChooseMonInput, Mailbox_ReturnToMailListAfterDeposit);
}

static void TryGiveMailToSelectedMon(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    struct Mail *mail;

    gPartyMenuUseExitCallback = FALSE;
    mail = &gSaveBlock1Ptr->mail[gPlayerPCItemPageInfo.itemsAbove + PARTY_SIZE + gPlayerPCItemPageInfo.cursorPos];
    if (GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE)
    {
        DisplayPartyMenuMessage(gText_PkmnHoldingItemCantHoldMail, TRUE);
    }
    else
    {
        GiveMailToMon(mon, mail);
        ClearMail(mail);
        DisplayPartyMenuMessage(gText_MailTransferredFromMailbox, TRUE);
    }
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_UpdateHeldItemSpriteAndClosePartyMenu;
}

void InitChooseHalfPartyForBattle(u8 unused)
{
    ClearSelectedPartyOrder();
    InitPartyMenu(PARTY_MENU_TYPE_CHOOSE_HALF, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, gMain.savedCallback);
    gPartyMenu.task = Task_ValidateChosenHalfParty;
}

void ClearSelectedPartyOrder(void)
{
    memset(gSelectedOrderFromParty, 0, sizeof(gSelectedOrderFromParty));
}

static u8 GetPartySlotEntryStatus(s8 slot)
{
    if (GetBattleEntryEligibility(&gPlayerParty[slot]) == FALSE)
        return 2;
    if (HasPartySlotAlreadyBeenSelected(slot + 1) == TRUE)
        return 1;
    return 0;
}

static bool8 GetBattleEntryEligibility(struct Pokemon *mon)
{
    u32 species;

    if (GetMonData(mon, MON_DATA_IS_EGG)
        || GetMonData(mon, MON_DATA_LEVEL) > GetBattleEntryLevelCap()
        || (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY)
            && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY)
            && GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE))
    {
        return FALSE;
    }

    switch (VarGet(VAR_FRONTIER_FACILITY))
    {
    case FACILITY_MULTI_OR_EREADER:
        if (GetMonData(mon, MON_DATA_HP) != 0)
            return TRUE;
        return FALSE;
    case FACILITY_UNION_ROOM:
        return TRUE;
    default: // Battle Frontier
        species = GetMonData(mon, MON_DATA_SPECIES);
        if (IsFrontierSpeciesBanEnforcedForBattleEntry() && gSpeciesInfo[GET_BASE_SPECIES_ID(species)].isFrontierBanned)
            return FALSE;
        return TRUE;
    }
}

static bool8 IsFrontierSpeciesBanEnforcedForBattleEntry(void)
{
    return gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_OPEN;
}

static const u8 *CheckBattleEntriesAndGetMessage(void)
{
    u8 maxBattlers;
    u8 i, j;
    u8 facility;
    struct Pokemon *party = gPlayerParty;
    u8 minBattlers = GetMinBattleEntries();
    u8 *order = gSelectedOrderFromParty;

    if (order[minBattlers - 1] == 0)
    {
        if (minBattlers == 1)
            return sActionStringTable[PARTY_MSG_NO_MON_FOR_BATTLE];
        ConvertIntToDecimalStringN(gStringVar1, minBattlers, STR_CONV_MODE_LEFT_ALIGN, 1);
        StringExpandPlaceholders(gStringVar4, sActionStringTable[PARTY_MSG_X_MONS_ARE_NEEDED]);
        return gStringVar4;
    }

    facility = VarGet(VAR_FRONTIER_FACILITY);
    if (facility == FACILITY_UNION_ROOM || facility == FACILITY_MULTI_OR_EREADER)
        return NULL;

    maxBattlers = GetMaxBattleEntries();
    for (i = 0; i < maxBattlers - 1; i++)
    {
        u16 species = GetMonData(&party[order[i] - 1], MON_DATA_SPECIES);
        enum Item item = GetMonData(&party[order[i] - 1], MON_DATA_HELD_ITEM);
        for (j = i + 1; j < maxBattlers; j++)
        {
            if (species == GetMonData(&party[order[j] - 1], MON_DATA_SPECIES))
                return sActionStringTable[PARTY_MSG_MONS_CANT_BE_SAME];
            if (item != ITEM_NONE && item == GetMonData(&party[order[j] - 1], MON_DATA_HELD_ITEM))
                return sActionStringTable[PARTY_MSG_NO_SAME_HOLD_ITEMS];
        }
    }

    return NULL;
}

static bool8 HasPartySlotAlreadyBeenSelected(u8 slot)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(gSelectedOrderFromParty); i++)
    {
        if (gSelectedOrderFromParty[i] == slot)
            return TRUE;
    }
    return FALSE;
}

static void Task_ValidateChosenHalfParty(u8 taskId)
{
    const u8 *msg = CheckBattleEntriesAndGetMessage();

    if (msg != NULL)
    {
        PlaySE(SE_FAILURE);
        DisplayPartyMenuMessage(msg, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_ContinueChoosingHalfParty;
    }
    else
    {
        PlaySE(SE_SELECT);
        DisplayPartyMenuMessage(sText_GoWithThisTeam, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_ShowChosenHalfPartyYesNo;
    }
}

static void Task_ShowChosenHalfPartyYesNo(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        PartyMenuDisplayYesNoMenu();
        gTasks[taskId].func = Task_HandleChosenHalfPartyYesNoInput;
    }
}

static void Task_HandleChosenHalfPartyYesNoInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        Task_ClosePartyMenu(taskId);
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        // fallthrough
    case 1:
        UnselectLastBattleEntry();
        Task_ReturnToChooseMonAfterText(taskId);
        break;
    }
}

static void UnselectLastBattleEntry(void)
{
    u8 i;
    u8 maxBattlers = GetMaxBattleEntries();
    u8 slot = gSelectedOrderFromParty[maxBattlers - 1] - 1;

    gSelectedOrderFromParty[maxBattlers - 1] = 0;
    DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_ABLE_3, &sPartyMenuBoxes[slot], 1);
    for (i = 0; i < maxBattlers - 1; i++)
    {
        if (gSelectedOrderFromParty[i] != 0)
            DisplayPartyPokemonDescriptionText(i + PARTYBOX_DESC_FIRST, &sPartyMenuBoxes[gSelectedOrderFromParty[i] - 1], 1);
    }
    RefreshSelectedMonInfoAndPrompt();
}

static void Task_ContinueChoosingHalfParty(u8 taskId)
{
    if ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON)))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_HandleChooseMonInput;
    }
}

static u8 GetMaxBattleEntries(void)
{
    switch (VarGet(VAR_FRONTIER_FACILITY))
    {
    case FACILITY_MULTI_OR_EREADER:
        return MULTI_PARTY_SIZE;
    case FACILITY_UNION_ROOM:
        return UNION_ROOM_PARTY_SIZE;
    default: // Battle Frontier
        return gSpecialVar_0x8005;
    }
}

static u8 GetMinBattleEntries(void)
{
    switch (VarGet(VAR_FRONTIER_FACILITY))
    {
    case FACILITY_MULTI_OR_EREADER:
        return 1;
    case FACILITY_UNION_ROOM:
        return UNION_ROOM_PARTY_SIZE;
    default: // Battle Frontier
        return gSpecialVar_0x8005;
    }
}

static u8 GetBattleEntryLevelCap(void)
{
    switch (VarGet(VAR_FRONTIER_FACILITY))
    {
    case FACILITY_MULTI_OR_EREADER:
        return MAX_LEVEL;
    case FACILITY_UNION_ROOM:
        return UNION_ROOM_MAX_LEVEL;
    default: // Battle Frontier
        return FRONTIER_MAX_LEVEL_OPEN;
    }
}

static const u8 *GetFacilityCancelString(void)
{
    u8 facilityNum = VarGet(VAR_FRONTIER_FACILITY);

    if (!(facilityNum != FACILITY_UNION_ROOM && facilityNum != FACILITY_MULTI_OR_EREADER))
        return gText_CancelBattle;
    else if (facilityNum == FRONTIER_FACILITY_DOME && gSpecialVar_0x8005 == 2)
        return gText_ReturnToWaitingRoom;
    else
        return gText_CancelChallenge;
}

void ChooseMonForTradingBoard(u8 menuType, MainCallback callback)
{
    InitPartyMenu(menuType, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, callback);
}

void ChooseMonForMoveTutor(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_FIELD, PARTY_LAYOUT_SINGLE, PARTY_ACTION_MOVE_TUTOR, FALSE, PARTY_MSG_TEACH_WHICH_MON, Task_HandleChooseMonInput, CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ChooseMonForWirelessMinigame(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_MINIGAME, PARTY_LAYOUT_SINGLE, PARTY_ACTION_MINIGAME, FALSE, PARTY_MSG_CHOOSE_MON_OR_CANCEL, Task_HandleChooseMonInput, CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static u8 GetPartyLayoutFromBattleType(void)
{
    if (IsMultiBattle() == TRUE)
        return PARTY_LAYOUT_MULTI;
    if (!IsDoubleBattle() || gPlayerPartyCount == 1) // Draw the single layout in a double battle where the player has only one pokemon.
        return PARTY_LAYOUT_SINGLE;
    return PARTY_LAYOUT_DOUBLE;
}

void OpenPartyMenuInBattle(u8 partyAction)
{
    if (partyAction == PARTY_ACTION_SEND_MON_TO_BOX)
            InitPartyMenu(PARTY_MENU_TYPE_IN_BATTLE, GetPartyLayoutFromBattleType(), partyAction, FALSE, PARTY_MSG_CHOOSE_MON_FOR_BOX, Task_HandleChooseMonInput, ReshowBlankBattleScreenAfterMenu);
        else
            InitPartyMenu(PARTY_MENU_TYPE_IN_BATTLE, GetPartyLayoutFromBattleType(), partyAction, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_SetUpReshowBattleScreenAfterMenu);
    ReshowBattleScreenDummy();
    UpdatePartyToBattleOrder();
}

void ChooseMonForInBattleItem(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_IN_BATTLE, GetPartyLayoutFromBattleType(), PARTY_ACTION_USE_ITEM, FALSE, PARTY_MSG_USE_ON_WHICH_MON, Task_HandleChooseMonInput, CB2_ReturnToBagMenu);
    ReshowBattleScreenDummy();
    UpdatePartyToBattleOrder();
}

static u8 GetPartyMenuActionsTypeInBattle(struct Pokemon *mon)
{
    if (GetMonData(&gPlayerParty[1], MON_DATA_SPECIES) != SPECIES_NONE && GetMonData(mon, MON_DATA_IS_EGG) == FALSE)
    {
        if (gPartyMenu.action == PARTY_ACTION_SEND_OUT)
            return ACTIONS_SEND_OUT;
        if (!(gBattleTypeFlags & BATTLE_TYPE_ARENA))
            return ACTIONS_SHIFT;
    }
    return ACTIONS_SUMMARY_ONLY;
}

static bool8 TrySwitchInPokemon(void)
{
    u8 slot = GetCursorSelectionMonId();
    u8 newSlot;

    // In a multi battle, slots 1, 4, and 5 are the partner's Pokémon
    if (IsMultiBattle() == TRUE && (slot == 1 || slot == 4 || slot == 5))
    {
        StringCopy(gStringVar1, GetTrainerPartnerName());
        StringExpandPlaceholders(gStringVar4, gText_CantSwitchWithAlly);
        return FALSE;
    }
    if (GetMonData(&gPlayerParty[slot], MON_DATA_HP) == 0)
    {
        GetMonNickname(&gPlayerParty[slot], gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_PkmnHasNoEnergy);
        return FALSE;
    }
    for (enum BattlerId i = 0; i < gBattlersCount; i++)
    {
        if (IsOnPlayerSide(i) && GetPartyIdFromBattleSlot(slot) == gBattlerPartyIndexes[i])
        {
            GetMonNickname(&gPlayerParty[slot], gStringVar1);
            StringExpandPlaceholders(gStringVar4, gText_PkmnAlreadyInBattle);
            return FALSE;
        }
    }
    if (GetMonData(&gPlayerParty[slot], MON_DATA_IS_EGG))
    {
        StringExpandPlaceholders(gStringVar4, gText_EggCantBattle);
        return FALSE;
    }
    if (GetPartyIdFromBattleSlot(slot) == gBattleStruct->prevSelectedPartySlot)
    {
        GetMonNickname(&gPlayerParty[slot], gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_PkmnAlreadySelected);
        return FALSE;
    }
    if (gPartyMenu.action == PARTY_ACTION_ABILITY_PREVENTS)
    {
        SetMonPreventsSwitchingString();
        return FALSE;
    }
    if (gPartyMenu.action == PARTY_ACTION_CANT_SWITCH)
    {
        u8 currBattler = gBattlerInMenuId;
        GetMonNickname(&gPlayerParty[GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[currBattler])], gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_PkmnCantSwitchOut);
        return FALSE;
    }
    gSelectedMonPartyId = GetPartyIdFromBattleSlot(slot);
    gPartyMenuUseExitCallback = TRUE;
    newSlot = GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[gBattlerInMenuId]);
    SwitchPartyMonSlots(newSlot, slot);
    SwapPartyPokemon(&gPlayerParty[newSlot], &gPlayerParty[slot]);
    return TRUE;
}

void BufferBattlePartyCurrentOrder(void)
{
    BufferBattlePartyOrder(gBattlePartyCurrentOrder, GetPlayerFlankId());
}

static void BufferBattlePartyOrder(u8 *partyBattleOrder, u8 flankId)
{
    u8 partyIds[PARTY_SIZE];
    int i, j;

    if (IsMultiBattle() == TRUE)
    {
        // Party ids are packed in 4 bits at a time
        // i.e. the party id order below would be 0, 3, 5, 4, 2, 1, and the two parties would be 0,5,4 and 3,2,1
        if (flankId != 0)
        {
            partyBattleOrder[0] = 0 | (3 << 4);
            partyBattleOrder[1] = 5 | (4 << 4);
            partyBattleOrder[2] = 2 | (1 << 4);
        }
        else
        {
            partyBattleOrder[0] = 3 | (0 << 4);
            partyBattleOrder[1] = 2 | (1 << 4);
            partyBattleOrder[2] = 5 | (4 << 4);
        }
        return;
    }
    else if (IsDoubleBattle() == FALSE)
    {
        j = 1;
        partyIds[0] = gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (i != partyIds[0])
            {
                partyIds[j] = i;
                j++;
            }
        }
    }
    else
    {
        j = 2;
        partyIds[0] = gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)];
        partyIds[1] = gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (i != partyIds[0] && i != partyIds[1])
            {
                partyIds[j] = i;
                j++;
            }
        }
    }
    for (i = 0; i < (int)ARRAY_COUNT(gBattlePartyCurrentOrder); i++)
        partyBattleOrder[i] = (partyIds[0 + (i * 2)] << 4) | partyIds[1 + (i * 2)];
}

void BufferBattlePartyCurrentOrderBySide(enum BattlerId battler, u8 flankId)
{
    BufferBattlePartyOrderBySide(gBattleStruct->battlerPartyOrders[battler], flankId, battler);
}

// when IsOnPlayerSide(battlerId), this function is identical the one above
static void BufferBattlePartyOrderBySide(u8 *partyBattleOrder, u8 flankId, enum BattlerId battler)
{
    u8 partyIndexes[PARTY_SIZE];
    int i, j;

    enum BattlerId leftBattler;
    if (IsOnPlayerSide(battler))
        leftBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    else
        leftBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);

    if (IsMultiBattle() == TRUE)
    {
        if (flankId != 0)
        {
            partyBattleOrder[0] = 0 | (3 << 4);
            partyBattleOrder[1] = 5 | (4 << 4);
            partyBattleOrder[2] = 2 | (1 << 4);
        }
        else
        {
            partyBattleOrder[0] = 3 | (0 << 4);
            partyBattleOrder[1] = 2 | (1 << 4);
            partyBattleOrder[2] = 5 | (4 << 4);
        }
        return;
    }
    else if (IsDoubleBattle() == FALSE)
    {
        j = 1;
        partyIndexes[0] = gBattlerPartyIndexes[leftBattler];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (i != partyIndexes[0])
            {
                partyIndexes[j] = i;
                j++;
            }
        }
    }
    else
    {
        enum BattlerId rightBattler;
        if (IsOnPlayerSide(battler))
            rightBattler = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        else
            rightBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);

        j = 2;
        partyIndexes[0] = gBattlerPartyIndexes[leftBattler];
        partyIndexes[1] = gBattlerPartyIndexes[rightBattler];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (i != partyIndexes[0] && i != partyIndexes[1])
            {
                partyIndexes[j] = i;
                j++;
            }
        }
    }

    for (i = 0; i < 3; i++)
        partyBattleOrder[i] = (partyIndexes[0 + (i * 2)] << 4) | partyIndexes[1 + (i * 2)];
}

void SwitchPartyOrderLinkMulti(enum BattlerId battler, u8 slot, u8 slot2)
{
    u8 partyIds[PARTY_SIZE];
    u8 tempSlot = 0;
    int i, j;
    u8 *partyBattleOrder;
    u8 partyIdBuffer;

    if (IsMultiBattle())
    {
        partyBattleOrder = gBattleStruct->battlerPartyOrders[battler];
        for (i = j = 0; i < PARTY_SIZE / 2; j++, i++)
        {
            partyIds[j] = partyBattleOrder[i] >> 4;
            j++;
            partyIds[j] = partyBattleOrder[i] & 0xF;
        }
        partyIdBuffer = partyIds[slot2];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (partyIds[i] == slot)
            {
                tempSlot = partyIds[i];
                partyIds[i] = partyIdBuffer;
                break;
            }
        }
        if (i != PARTY_SIZE)
        {
            partyIds[slot2] = tempSlot;
            partyBattleOrder[0] = (partyIds[0] << 4) | partyIds[1];
            partyBattleOrder[1] = (partyIds[2] << 4) | partyIds[3];
            partyBattleOrder[2] = (partyIds[4] << 4) | partyIds[5];
        }
    }
}

static u8 GetPartyIdFromBattleSlot(u8 slot)
{
    u8 modResult = slot & 1;
    u8 retVal;

    slot /= 2;
    if (modResult != 0)
        retVal = gBattlePartyCurrentOrder[slot] & 0xF;
    else
        retVal = gBattlePartyCurrentOrder[slot] >> 4;
    return retVal;
}

static void SetPartyIdAtBattleSlot(u8 slot, u8 setVal)
{
    bool32 modResult = slot & 1;

    slot /= 2;
    if (modResult != 0)
        gBattlePartyCurrentOrder[slot] = (gBattlePartyCurrentOrder[slot] & 0xF0) | setVal;
    else
        gBattlePartyCurrentOrder[slot] = (gBattlePartyCurrentOrder[slot] & 0xF) | (setVal << 4);
}

void SwitchPartyMonSlots(u8 slot, u8 slot2)
{
    u8 partyId = GetPartyIdFromBattleSlot(slot);
    SetPartyIdAtBattleSlot(slot, GetPartyIdFromBattleSlot(slot2));
    SetPartyIdAtBattleSlot(slot2, partyId);
}

u8 GetPartyIdFromBattlePartyId(u8 battlePartyId)
{
    u8 i, j;

    for (j = i = 0; i < (int)ARRAY_COUNT(gBattlePartyCurrentOrder); j++, i++)
    {
        if ((gBattlePartyCurrentOrder[i] >> 4) != battlePartyId)
        {
            j++;
            if ((gBattlePartyCurrentOrder[i] & 0xF) == battlePartyId)
                return j;
        }
        else
        {
            return j;
        }
    }
    return 0;
}

static void UpdatePartyToBattleOrder(void)
{
    struct Pokemon *partyBuffer = Alloc(sizeof(gPlayerParty));
    u8 i;

    memcpy(partyBuffer, gPlayerParty, sizeof(gPlayerParty));
    for (i = 0; i < PARTY_SIZE; i++)
        memcpy(&gPlayerParty[GetPartyIdFromBattlePartyId(i)], &partyBuffer[i], sizeof(struct Pokemon));
    Free(partyBuffer);
}

static void UpdatePartyToFieldOrder(void)
{
    struct Pokemon *partyBuffer = Alloc(sizeof(gPlayerParty));
    u8 i;

    memcpy(partyBuffer, gPlayerParty, sizeof(gPlayerParty));
    for (i = 0; i < PARTY_SIZE; i++)
        memcpy(&gPlayerParty[GetPartyIdFromBattleSlot(i)], &partyBuffer[i], sizeof(struct Pokemon));
    Free(partyBuffer);
}

static void UNUSED SwitchAliveMonIntoLeadSlot(void)
{
    u8 i;
    struct Pokemon *mon;
    u8 partyId;

    for (i = 1; i < PARTY_SIZE; i++)
    {
        mon = &gPlayerParty[GetPartyIdFromBattleSlot(i)];
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE && GetMonData(mon, MON_DATA_HP) != 0)
        {
            partyId = GetPartyIdFromBattleSlot(0);
            SwitchPartyMonSlots(0, i);
            SwapPartyPokemon(&gPlayerParty[partyId], mon);
            break;
        }
    }
}

static void CB2_SetUpExitToBattleScreen(void)
{
    SetMainCallback2(CB2_SetUpReshowBattleScreenAfterMenu);
}

void ShowPartyMenuToShowcaseMultiBattleParty(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_MULTI_SHOWCASE, PARTY_LAYOUT_MULTI_SHOWCASE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_NONE, Task_InitMultiPartnerPartySlideIn, gMain.savedCallback);
}

#define tXPos  data[0]

static void Task_InitMultiPartnerPartySlideIn(u8 taskId)
{
    // The first slide step also sets the sprites offscreen
    gTasks[taskId].tXPos = 256;
    SlideMultiPartyMenuBoxSpritesOneStep(taskId);
    ChangeBgX(2, 0x10000, BG_COORD_SET);
    gTasks[taskId].func = Task_MultiPartnerPartySlideIn;
}

static void Task_MultiPartnerPartySlideIn(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 i;

    if (!gPaletteFade.active)
    {
        tXPos -= 8;
        SlideMultiPartyMenuBoxSpritesOneStep(taskId);
        if (tXPos == 0)
        {
            for (i = MULTI_PARTY_SIZE; i < PARTY_SIZE; i++)
            {
                if (gMultiPartnerParty[i - MULTI_PARTY_SIZE].species != SPECIES_NONE)
                    AnimateSelectedPartyIcon(sPartyMenuBoxes[i].monSpriteId, 0);
            }
            PlaySE(SE_M_HARDEN); // The Harden SE plays once the partners party mons have slid on screen
            gTasks[taskId].func = Task_WaitAfterMultiPartnerPartySlideIn;
        }
    }
}

static void Task_WaitAfterMultiPartnerPartySlideIn(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    // data[0] used as a timer afterwards rather than the x pos
    if (FollowerNPCIsBattlePartner()) {
        if (++data[0] == 128)
            Task_ClosePartyMenu(taskId);
    }
    else if (++data[0] == 256)
        Task_ClosePartyMenu(taskId);
}

static void MoveMultiPartyMenuBoxSprite(u8 spriteId, s16 x)
{
    if (x >= 0)
        gSprites[spriteId].x2 = x;
}

static void SlideMultiPartyMenuBoxSpritesOneStep(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 i;

    for (i = MULTI_PARTY_SIZE; i < PARTY_SIZE; i++)
    {
        if (gMultiPartnerParty[i - MULTI_PARTY_SIZE].species != SPECIES_NONE)
        {
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].monSpriteId, tXPos - 8);
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].itemSpriteId, tXPos - 8);
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].pokeballSpriteId, tXPos - 8);
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].statusSpriteId, tXPos - 8);
        }
    }
    ChangeBgX(2, 0x800, BG_COORD_ADD);
}

#undef tXpos

void ChooseMonForDaycare(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_DAYCARE, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_CHOOSE_MON_2, Task_HandleChooseMonInput, BufferMonSelection);
}

static void UNUSED ChoosePartyMonByMenuType(u8 menuType)
{
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    InitPartyMenu(menuType, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ReturnToField);
}

static void BufferMonSelection(void)
{
    gSpecialVar_0x8004 = GetCursorSelectionMonId();
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
        gSpecialVar_0x8004 = PARTY_NOTHING_CHOSEN;
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    SetMainCallback2(CB2_ReturnToField);
}

bool8 CB2_FadeFromPartyMenu(void)
{
    FadeInFromBlack();
    CreateTask(Task_PartyMenuWaitForFade, 10);
    return TRUE;
}

static void Task_PartyMenuWaitForFade(u8 taskId)
{
    if (IsWeatherNotFadingIn())
    {
        DestroyTask(taskId);
        UnlockPlayerFieldControls();
        ScriptContext_Enable();
    }
}

void ChooseContestMon(void)
{
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_ChooseContestMon, 10);
}

static void Task_ChooseContestMon(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_CONTEST, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ChooseContestMon);
        DestroyTask(taskId);
    }
}

static void CB2_ChooseContestMon(void)
{
    gContestMonPartyIndex = GetCursorSelectionMonId();
    if (gContestMonPartyIndex >= PARTY_SIZE)
        gContestMonPartyIndex = PARTY_NOTHING_CHOSEN;
    gSpecialVar_0x8004 = gContestMonPartyIndex;
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    SetMainCallback2(CB2_ReturnToField);
}

// Used as a script special for showing a party mon to various npcs (e.g. in-game trades, move deleter)
void ChoosePartyMon(void)
{
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_ChoosePartyMon, 10);
}

static void Task_ChoosePartyMon(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_CHOOSE_MON, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, BufferMonSelection);
        DestroyTask(taskId);
    }
}

void ChooseMonForMoveRelearner(void)
{
    gRelearnMode = RELEARN_MODE_SCRIPT;
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_ChooseMonForMoveRelearner, 10);
}

static void Task_ChooseMonForMoveRelearner(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_MOVE_RELEARNER, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ChooseMonForMoveRelearner);
        DestroyTask(taskId);
    }
}

static void CB2_ChooseMonForMoveRelearner(void)
{
    gSpecialVar_0x8004 = GetCursorSelectionMonId();
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
    {
        gSpecialVar_0x8004 = PARTY_NOTHING_CHOSEN;
    }
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    SetMainCallback2(CB2_ReturnToField);
}

void DoBattlePyramidMonsHaveHeldItem(void)
{
    u8 i;

    gSpecialVar_Result = FALSE;
    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM) != ITEM_NONE)
        {
            gSpecialVar_Result = TRUE;
            break;
        }
    }
}

// Can be called if the Battle Pyramid Bag is full on exiting and at least one party mon still has held items
// The player can then select to toss items from the bag or take/toss held items from the party
void BattlePyramidChooseMonHeldItems(void)
{
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_BattlePyramidChooseMonHeldItems, 10);
}

static void Task_BattlePyramidChooseMonHeldItems(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, BufferMonSelection);
        DestroyTask(taskId);
    }
}

void MoveDeleterChooseMoveToForget(void)
{
    ShowPokemonSummaryScreen(SUMMARY_MODE_SELECT_MOVE, gPlayerParty, gSpecialVar_0x8004, gPlayerPartyCount - 1, CB2_ReturnToField);
    gFieldCallback = FieldCB_ContinueScriptHandleMusic;
}

void GetNumMovesSelectedMonHas(void)
{
    u32 i;
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();

    gSpecialVar_Result = 0;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetBoxMonData(boxmon , MON_DATA_MOVE1 + i) != MOVE_NONE)
            gSpecialVar_Result++;
    }
}

void BufferMoveDeleterNicknameAndMove(void)
{
    enum Move move = 0;
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();
    move = GetBoxMonData(boxmon, MON_DATA_MOVE1 + gSpecialVar_0x8005);
    GetBoxMonData(boxmon, MON_DATA_NICKNAME, gStringVar1);
    StringCopy(gStringVar2, GetMoveName(move));
}

void MoveDeleterForgetMove(void)
{
    enum Move move = MOVE_NONE;
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();
    SetBoxMonData(boxmon, MON_DATA_MOVE1 + gSpecialVar_0x8005, &move);
    SetBoxMonData(boxmon, MON_DATA_PP1 + gSpecialVar_0x8005, &gMovesInfo[MOVE_NONE].pp);
    u8 ppBonuses = GetBoxMonData(boxmon, MON_DATA_PP_BONUSES);
    ppBonuses &= gPPUpClearMask[gSpecialVar_0x8005];
    SetBoxMonData(boxmon, MON_DATA_PP_BONUSES, &ppBonuses);
    for (u32 i = gSpecialVar_0x8005; i < MAX_MON_MOVES - 1; i++)
        ShiftMoveSlot(boxmon, i, i + 1);
}

static void ShiftMoveSlot(struct BoxPokemon *mon, u8 slotTo, u8 slotFrom)
{
    enum Move move1 = GetBoxMonData(mon, MON_DATA_MOVE1 + slotTo);
    enum Move move0 = GetBoxMonData(mon, MON_DATA_MOVE1 + slotFrom);
    u8 pp1 = GetBoxMonData(mon, MON_DATA_PP1 + slotTo);
    u8 pp0 = GetBoxMonData(mon, MON_DATA_PP1 + slotFrom);
    u8 ppBonuses = GetBoxMonData(mon, MON_DATA_PP_BONUSES);
    u8 ppBonusMask1 = gPPUpGetMask[slotTo];
    u8 ppBonusMove1 = (ppBonuses & ppBonusMask1) >> (slotTo * 2);
    u8 ppBonusMask2 = gPPUpGetMask[slotFrom];
    u8 ppBonusMove2 = (ppBonuses & ppBonusMask2) >> (slotFrom * 2);
    ppBonuses &= ~ppBonusMask1;
    ppBonuses &= ~ppBonusMask2;
    ppBonuses |= (ppBonusMove1 << (slotFrom * 2)) + (ppBonusMove2 << (slotTo * 2));
    SetBoxMonData(mon, MON_DATA_MOVE1 + slotTo, &move0);
    SetBoxMonData(mon, MON_DATA_MOVE1 + slotFrom, &move1);
    SetBoxMonData(mon, MON_DATA_PP1 + slotTo, &pp0);
    SetBoxMonData(mon, MON_DATA_PP1 + slotFrom, &pp1);
    SetBoxMonData(mon, MON_DATA_PP_BONUSES, &ppBonuses);
}

void IsSelectedMonEgg(void)
{
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();
    if (GetBoxMonData(boxmon, MON_DATA_IS_EGG))
        gSpecialVar_Result = TRUE;
    else
        gSpecialVar_Result = FALSE;
}

void IsLastMonThatKnowsSurf(void)
{
    enum Move move;
    u32 i, j;

    gSpecialVar_Result = FALSE;
    if (gSpecialVar_0x8004 == PC_MON_CHOSEN)
        return;

    move = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_MOVE1 + gSpecialVar_0x8005);
    if (move == MOVE_SURF)
    {
        for (i = 0; i < CalculatePlayerPartyCount(); i++)
        {
            if (i != gSpecialVar_0x8004)
            {
                for (j = 0; j < MAX_MON_MOVES; j++)
                {
                    if (GetMonData(&gPlayerParty[i], MON_DATA_MOVE1 + j) == MOVE_SURF)
                        return;
                }
            }
        }
        if (AnyStorageMonWithMove(move) != TRUE)
            gSpecialVar_Result = !P_CAN_FORGET_HIDDEN_MOVE;
    }
}

static void CursorCb_ChangeLevelUpMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_LEVEL_UP_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_ChangeEggMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_EGG_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_ChangeTMMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_TM_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_ChangeTutorMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_TUTOR_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_LearnMovesSubMenu(u8 taskId)
{
    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, ACTIONS_MOVES_SUB);
    DisplaySelectionWindow(SELECTWINDOW_ACTIONS);
    gTasks[taskId].data[0] = 0xFF;
    gTasks[taskId].func = Task_HandleSelectionMenuInput;
}

void CursorCb_MoveItemCallback(u8 taskId)
{
    enum Item item1, item2;
    u8 buffer[100];

    if (gPaletteFade.active || MenuHelpers_ShouldWaitForLinkRecv())
        return;

    switch (PartyMenuButtonHandler(&gPartyMenu.slotId2))
    {
    case 2:     // User hit B or A while on Cancel
        HandleChooseMonCancel(taskId, &gPartyMenu.slotId2);
        break;
    case 1:     // User hit A on a Pokemon
        // Pokemon can't give away items to eggs
        if (GetMonData(&gPlayerParty[gPartyMenu.slotId2], MON_DATA_IS_EGG))
        {
            PlaySE(SE_FAILURE);
            return;
        }
        // If pressing A on the same Pokemon, cancel the move action
        if (gPartyMenu.slotId == gPartyMenu.slotId2)
        {
            HandleChooseMonCancel(taskId, &gPartyMenu.slotId2);
            return;
        }

        PlaySE(SE_SELECT);
        gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;

        // look up held items
        item1 = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM);
        item2 = GetMonData(&gPlayerParty[gPartyMenu.slotId2], MON_DATA_HELD_ITEM);

        // swap the held items
        SetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM, &item2);
        SetMonData(&gPlayerParty[gPartyMenu.slotId2], MON_DATA_HELD_ITEM, &item1);

        TryItemHoldFormChange(&gPlayerParty[gPartyMenu.slotId], gPartyMenu.slotId);
        TryItemHoldFormChange(&gPlayerParty[gPartyMenu.slotId2], gPartyMenu.slotId2);

        // Animate item swapping:
        // - Hide both party mon held-item sprites during animation
        // - Create moving sprite first, then update the destination's held item afterwards
        if (item2 != ITEM_NONE)
        {
            // Hide item sprites
            if (sPartyMenuBoxes[gPartyMenu.slotId].itemSpriteId != MAX_SPRITES)
                gSprites[sPartyMenuBoxes[gPartyMenu.slotId].itemSpriteId].invisible = TRUE;
            if (sPartyMenuBoxes[gPartyMenu.slotId2].itemSpriteId != MAX_SPRITES)
                gSprites[sPartyMenuBoxes[gPartyMenu.slotId2].itemSpriteId].invisible = TRUE;

            // Create moving sprite
            CreateItemMoveSprite(gPartyMenu.slotId2, gPartyMenu.slotId, item2);

            // Update destination slot to show its new item (item1)
            UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId2], &sPartyMenuBoxes[gPartyMenu.slotId2]);
            if (sPartyMenuBoxes[gPartyMenu.slotId2].itemSpriteId != MAX_SPRITES)
                gSprites[sPartyMenuBoxes[gPartyMenu.slotId2].itemSpriteId].invisible = TRUE;
        }
        else
        {
            UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId2], &sPartyMenuBoxes[gPartyMenu.slotId2]);
            UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuBoxes[gPartyMenu.slotId]);
        }

        // create the string describing the move
        if (item2 == ITEM_NONE)
        {
            GetMonNickname(&gPlayerParty[gPartyMenu.slotId2], gStringVar1);
            CopyItemName(item1, gStringVar2);
            StringExpandPlaceholders(gStringVar4, gText_PkmnWasGivenItem);
        }
        else
        {
            GetMonNickname(&gPlayerParty[gPartyMenu.slotId], gStringVar1);
            CopyItemName(item1, gStringVar2);
            StringExpandPlaceholders(buffer, gText_XsYAnd);

            StringAppend(buffer, gText_XsYWereSwapped);
            GetMonNickname(&gPlayerParty[gPartyMenu.slotId2], gStringVar1);
            CopyItemName(item2, gStringVar2);
            StringExpandPlaceholders(gStringVar4, buffer);
        }

        // WIN_MSG is one tile shorter than the overlapping held-item window.
        // Hide the full info window so its bottom text row cannot remain visible.
        if (sSelectedMonHeldItemInfoWindowId != WINDOW_NONE)
            ClearWindowTilemap(sSelectedMonHeldItemInfoWindowId);

        // display the string
        DisplayPartyMenuMessage(gStringVar4, TRUE);

        // update colors of selected boxes
        AnimatePartySlot(gPartyMenu.slotId, 0);
        gPartyMenu.slotId = gPartyMenu.slotId2;
        AnimatePartySlot(gPartyMenu.slotId, 1);

        // return to the main party menu
        DestroySelectFrame();
        ScheduleBgCopyTilemapToVram(2);
        CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
        break;
    }
}

void CursorCb_MoveItem(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    PlaySE(SE_SELECT);

    // delete old windows
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);

    if (GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE)
    {
        gSpecialVar_ItemId = GetMonData(mon, MON_DATA_HELD_ITEM);
        gPartyMenu.action = PARTY_ACTION_MOVE_ITEM;
        gPartyMenu.slotId2 = gPartyMenu.slotId;
        UpdateSelectedMonItemSprite();

        // Keep the move origin visually selected, but leave its icon idle.
        AnimatePartySlot(gPartyMenu.slotId, 0);

        // Hide the item sprite on the source Pokemon before showing it on cursor
        if (sPartyMenuBoxes[gPartyMenu.slotId].itemSpriteId != MAX_SPRITES)
            gSprites[sPartyMenuBoxes[gPartyMenu.slotId].itemSpriteId].invisible = TRUE;

        CreateHoverSprite(&sPartyMenuBoxes[gPartyMenu.slotId], gPartyMenu.slotId);

        // set up callback
        gTasks[taskId].func = CursorCb_MoveItemCallback;
    }
    else
    {
        // create and display string about lack of hold item
        GetMonNickname(mon, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_PkmnNotHolding);
        DisplayPartyMenuMessage(gStringVar4, TRUE);

        // return to the main party menu
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
    }
}

static void FieldCallback_RockClimb(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    FieldEffectStart(FLDEFF_USE_ROCK_CLIMB);
}

static void DisplayGiveHowManyMessage(void)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    CopyItemNameHandlePlural(gSpecialVar_ItemId, gStringVar1, 2);
    GetMonNickname(mon, gStringVar2);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Give how many {STR_VAR_1}\nto {STR_VAR_2}?"));
    DisplayPartyMenuMessage(gStringVar4, TRUE);
    ScheduleBgCopyTilemapToVram(2);
}

static bool8 DoesItemIncreaseEV(u8 itemType)
{
    switch (itemType)
    {
    case ITEM_EFFECT_ATK_EV:
    case ITEM_EFFECT_HP_EV:
    case ITEM_EFFECT_SPATK_EV:
    case ITEM_EFFECT_SPDEF_EV:
    case ITEM_EFFECT_SPEED_EV:
    case ITEM_EFFECT_DEF_EV:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool8 DoesItemReduceIV(u8 itemType)
{
    switch (itemType)
    {
    case ITEM_EFFECT_HP_IV_REDUCE:
    case ITEM_EFFECT_ATK_IV_REDUCE:
    case ITEM_EFFECT_DEF_IV_REDUCE:
    case ITEM_EFFECT_SPEED_IV_REDUCE:
    case ITEM_EFFECT_SPATK_IV_REDUCE:
    case ITEM_EFFECT_SPDEF_IV_REDUCE:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool8 ShouldLevelUpItemUseLevelCap(void)
{
    u32 expCapType = GetCurrentExpCapType();

    return B_RARE_CANDY_CAP && (expCapType == EXP_CAP_SOFT || expCapType == EXP_CAP_HARD);
}

static u16 GetMaxLevelUpItemQuantity(struct Pokemon *mon, u8 holdEffectParam, u16 quantityInBag)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 growthRate = gSpeciesInfo[species].growthRate;
    u32 level = GetMonData(mon, MON_DATA_LEVEL);
    u32 levelCap = GetCurrentLevelCap();
    u32 currentExp = GetMonData(mon, MON_DATA_EXP);
    u32 maxQuantity;

    if (quantityInBag == 0 || level >= MAX_LEVEL)
        return 0;

    if (ShouldLevelUpItemUseLevelCap())
    {
        levelCap = min(levelCap, MAX_LEVEL);
        if (level >= levelCap)
            return 0;
    }
    else
    {
        levelCap = MAX_LEVEL;
    }

    if (holdEffectParam == 0)
    {
        maxQuantity = levelCap - level;
    }
    else
    {
        u32 candyExp;
        u32 maxExp;
        u32 maxExpGain;

        if (holdEffectParam > EXP_30000)
            return 0;

        candyExp = sExpCandyExperienceTable[holdEffectParam - 1];
        if (candyExp == 0)
            return 0;

        maxExp = gExperienceTables[growthRate][levelCap];
        if (currentExp >= maxExp)
            return 0;

        maxExpGain = maxExp - currentExp;
        maxQuantity = (maxExpGain + candyExp - 1) / candyExp;
    }

    return min(quantityInBag, min(maxQuantity, MAX_BAG_ITEM_CAPACITY));
}

static void ClearHowManyItemsWindow(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    PlaySE(SE_SELECT);
    ClearStdWindowAndFrameToTransparent(tWindowId, FALSE);
    ClearStdWindowAndFrameToTransparent(WIN_MSG, FALSE);
    ClearWindowTilemap(tWindowId);
    ClearWindowTilemap(WIN_MSG);
    DestroyMessageWindowSprite();
    DestroyMultiuseWindowSprite();
    FillBgTilemapBufferRect(2, SWSH_PARTY_MENU_BLANK_TILE, 23, 10, 6, 4, 13);
    ScheduleBgCopyTilemapToVram(2);
}

static void PrintHowManyItemsWindow(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    CreateMultiuseWindowSprite();
    FillWindowPixelBuffer(tWindowId, PIXEL_FILL(0));
    ConvertIntToDecimalStringN(gStringVar1, tItemCount, STR_CONV_MODE_LEADING_ZEROS, MAX_ITEM_DIGITS);
    StringExpandPlaceholders(gStringVar3, gText_xVar1);
    AddTextPrinterParameterized4(tWindowId, FONT_NORMAL, 4, 0, 0, -2, sFontColorTable[11], TEXT_SPEED_INSTANT, gStringVar3);
}

static void Task_GiveHowManyItems(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        tWindowId = AddWindow(&sGiveHowManyItemsWindowTemplate);
        FillBgTilemapBufferRect(2, SWSH_PARTY_MENU_BLANK_TILE, 23, 10, 6, 4, 13);
        PutWindowTilemap(tWindowId);
        PrintHowManyItemsWindow(taskId);
        CopyWindowToVram(tWindowId, COPYWIN_GFX);
        ScheduleBgCopyTilemapToVram(2);

        gTasks[taskId].func = Task_GiveHowManyItemsHandleInput;
    }
}

static void Task_GiveHowManyItemsHandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tItemCount, tMaxItemQuantity) == TRUE)
    {
        PrintHowManyItemsWindow(taskId);
    }
    else
    {
        if (JOY_NEW(A_BUTTON))
        {
            ClearHowManyItemsWindow(taskId);

            if (gSpecialVar_ItemId == ITEM_REVERSE_CANDY)
            {
                ItemUse_ApplyReverseCandy(taskId);
            }
            else
            {
                switch (tItemEffect)
                {
                case ITEM_EFFECT_HP_EV:
                case ITEM_EFFECT_ATK_EV:
                case ITEM_EFFECT_DEF_EV:
                case ITEM_EFFECT_SPEED_EV:
                case ITEM_EFFECT_SPATK_EV:
                case ITEM_EFFECT_SPDEF_EV:
                    if ((s8)GetItemEffect(gSpecialVar_ItemId)[6] < 0)
                        ItemUse_ApplyEvReduceBerry(taskId);
                    else
                        ItemUse_ApplyEvIncreaseItem(taskId);
                    break;
                case ITEM_EFFECT_HP_IV_REDUCE:
                case ITEM_EFFECT_ATK_IV_REDUCE:
                case ITEM_EFFECT_DEF_IV_REDUCE:
                case ITEM_EFFECT_SPEED_IV_REDUCE:
                case ITEM_EFFECT_SPATK_IV_REDUCE:
                case ITEM_EFFECT_SPDEF_IV_REDUCE:
                    ItemUse_ApplyIVReduceHerb(taskId);
                    break;
                case ITEM_EFFECT_RAISE_LEVEL:
                    ItemUse_ApplyExpCandy(taskId);
                    break;
                default:
                    gTasks[taskId].func = Task_ClosePartyMenuAfterText;
                    break;
                }
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            ClearHowManyItemsWindow(taskId);
            ReturnToUseOnWhichMon(taskId);
        }
    }
}

static void Task_ReturnToUseOnWhichMonAfterText(u8 taskId)
{
    if (IsPartyMenuTextPrinterActive() != TRUE)
    {
        ReturnToUseOnWhichMon(taskId);
    }
}

static void ItemUse_ApplyEvReduceBerry(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = gSpecialVar_ItemId;
    u16 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP);
    u16 ev = ItemEffectToMonEv(mon, tItemEffect);

    ExecuteTableBasedItemEffect(mon, item, gPartyMenu.slotId, 0, 1, tItemCount);
    u16 newFriendship = GetMonData(mon, MON_DATA_FRIENDSHIP);
    u16 newEv = ItemEffectToMonEv(mon, tItemEffect);
    gPartyMenuUseExitCallback = TRUE;
    PlaySE(SE_USE_ITEM);
    if (tItemEffect == ITEM_EFFECT_HP_EV)
        UpdateMonDisplayInfoAfterRareCandy(gPartyMenu.slotId, mon);
    RemoveBagItem(item, tItemCount);
    GetMonNickname(mon, gStringVar1);
    ItemEffectToStatString(tItemEffect, gStringVar2);
    if (friendship != newFriendship)
    {
        if (ev != newEv)
            StringExpandPlaceholders(gStringVar4, gText_PkmnFriendlyBaseVar2Fell);
        else
            StringExpandPlaceholders(gStringVar4, gText_PkmnFriendlyBaseVar2CantFall);
    }
    else
    {
        StringExpandPlaceholders(gStringVar4, gText_PkmnAdoresBaseVar2Fell);
    }
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    if (CountTotalItemQuantityInBag(gSpecialVar_ItemId) == 0)
        gTasks[taskId].func = Task_ClosePartyMenuAfterText;
    else
        gTasks[taskId].func = Task_ReturnToUseOnWhichMonAfterText;
}

static void ItemUse_ApplyEvIncreaseItem(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = gSpecialVar_ItemId;

    ExecuteTableBasedItemEffect(mon, item, gPartyMenu.slotId, 0, 1, tItemCount);
    gPartyMenuUseExitCallback = TRUE;
    PlaySE(SE_USE_ITEM);
    if (tItemEffect == ITEM_EFFECT_HP_EV)
        UpdateMonDisplayInfoAfterRareCandy(gPartyMenu.slotId, mon);
    RemoveBagItem(item, tItemCount);
    GetMonNickname(mon, gStringVar1);
    GetMedicineItemEffectMessage(item, 0);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    if (CountTotalItemQuantityInBag(gSpecialVar_ItemId) == 0)
        gTasks[taskId].func = Task_ClosePartyMenuAfterText;
    else
        gTasks[taskId].func = Task_ReturnToUseOnWhichMonAfterText;
}

static void ItemUse_ApplyIVReduceHerb(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    enum Item item = gSpecialVar_ItemId;

    ExecuteTableBasedItemEffect(mon, item, gPartyMenu.slotId, 0, 1, tItemCount);
    gPartyMenuUseExitCallback = TRUE;
    PlaySE(SE_USE_ITEM);
    if (tItemEffect == ITEM_EFFECT_HP_IV_REDUCE)
        UpdateMonDisplayInfoAfterRareCandy(gPartyMenu.slotId, mon);
    RemoveBagItem(item, tItemCount);
    GetMonNickname(mon, gStringVar1);
    ItemEffectToStatString(tItemEffect, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gText_PkmnVar2IVWasLowered);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    if (CountTotalItemQuantityInBag(item) == 0)
        gTasks[taskId].func = Task_ClosePartyMenuAfterText;
    else
        gTasks[taskId].func = Task_ReturnToUseOnWhichMonAfterText;
}

static void ItemUse_ApplyExpCandy(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    struct PartyMenuInternal *ptr = sPartyMenuInternal;
    s16 *arrayPtr = ptr->data;

    BufferMonStatsToTaskData(mon, arrayPtr);
    ExecuteTableBasedItemEffect(mon, gSpecialVar_ItemId, gPartyMenu.slotId, 0, 1, tItemCount);
    BufferMonStatsToTaskData(mon, &ptr->data[NUM_STATS]);

    sFinalLevel = GetMonData(mon, MON_DATA_LEVEL, NULL);
    gPartyMenuUseExitCallback = TRUE;
    UpdateMonDisplayInfoAfterRareCandy(gPartyMenu.slotId, mon);
    RemoveBagItem(gSpecialVar_ItemId, tItemCount);
    GetMonNickname(mon, gStringVar1);
    if (sFinalLevel > sInitialLevel)
    {
        PlayFanfareByFanfareNum(FANFARE_LEVEL_UP);
        if (tHoldEffectParam == 0) // Rare Candy
        {
            ConvertIntToDecimalStringN(gStringVar2, sFinalLevel, STR_CONV_MODE_LEFT_ALIGN, 3);
            StringExpandPlaceholders(gStringVar4, gText_PkmnElevatedToLvVar2);
        }
        else // Exp Candies
        {
            ConvertIntToDecimalStringN(gStringVar2, sExpCandyExperienceTable[tHoldEffectParam - 1] * tItemCount, STR_CONV_MODE_LEFT_ALIGN, 7);
            ConvertIntToDecimalStringN(gStringVar3, sFinalLevel, STR_CONV_MODE_LEFT_ALIGN, 3);
            StringExpandPlaceholders(gStringVar4, gText_PkmnGainedExpAndElevatedToLvVar3);
        }

        DisplayPartyMenuMessage(gStringVar4, TRUE);
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_DisplayLevelUpStatsPg1;
    }
    else
    {
        PlaySE(SE_USE_ITEM);
        gPartyMenuUseExitCallback = FALSE;
        ConvertIntToDecimalStringN(gStringVar2, sExpCandyExperienceTable[tHoldEffectParam - 1] * tItemCount, STR_CONV_MODE_LEFT_ALIGN, 7);
        StringExpandPlaceholders(gStringVar4, gText_PkmnGainedExp);
        DisplayPartyMenuMessage(gStringVar4, FALSE);
        ScheduleBgCopyTilemapToVram(2);
        if (CountTotalItemQuantityInBag(gSpecialVar_ItemId) == 0)
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
        else
            gTasks[taskId].func = Task_ReturnToUseOnWhichMonAfterText;
    }
}

static void ItemUse_ApplyReverseCandy(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];
    u16 i;

    for (i = 0; i < tItemCount; i++)
        TryDecrementMonLevel(mon);

    gPartyMenuUseExitCallback = TRUE;
    PlaySE(SE_USE_ITEM);
    UpdateMonDisplayInfoAfterRareCandy(gPartyMenu.slotId, mon);
    RemoveBagItem(gSpecialVar_ItemId, tItemCount);
    GetMonNickname(mon, gStringVar1);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(mon, MON_DATA_LEVEL), STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_PkmnDroppedToLvVar2);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    if (CountTotalItemQuantityInBag(gSpecialVar_ItemId) == 0)
        gTasks[taskId].func = Task_ClosePartyMenuAfterText;
    else
        gTasks[taskId].func = Task_ReturnToUseOnWhichMonAfterText;
}

#undef tItemCount
#undef tMaxItemQuantity
#undef tQuantityInBag
#undef tWindowId
#undef tItemEffect
#undef tHoldEffectParam

static void PartyMenu_Oak_PrintText(u8 windowId, const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    gTextFlags.canABSpeedUpPrint = TRUE;
    AddTextPrinterParameterized2(windowId, FONT_NORMAL, gStringVar4, GetPlayerTextSpeedDelay(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
}

static bool8 FirstBattleEnterParty_CreateWindowAndMsg1Printer(void)
{
    u8 windowId = AddWindow(&sWindowTemplate_FirstBattleOakVoiceover);

    LoadMessageBoxGfx(windowId, 0x4F, BG_PLTT_ID(14));
    DrawDialogFrameWithCustomTileAndPalette(windowId, 1, 0x4F, 0xE);
    return windowId;
}

static void FirstBattleEnterParty_DestroyVoiceoverWindow(u8 windowId)
{
    ClearWindowTilemap(windowId);
    ClearDialogWindowAndFrameToTransparent(windowId, FALSE);
    RemoveWindow(windowId);
    ScheduleBgCopyTilemapToVram(2);
}

static void UNUSED Task_FirstBattleEnterParty_DarkenScreen(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFF1FFF, 4, 0, 6, RGB_BLACK);
    gTasks[taskId].func = Task_FirstBattleEnterParty_WaitDarken;
}

static void Task_FirstBattleEnterParty_WaitDarken(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_FirstBattleEnterParty_CreatePrinter;
}

static void Task_FirstBattleEnterParty_CreatePrinter(u8 taskId)
{
    gTasks[taskId].data[0] = FirstBattleEnterParty_CreateWindowAndMsg1Printer();
    gTasks[taskId].func = Task_FirstBattleEnterParty_RunPrinterMsg1;
}

static void Task_FirstBattleEnterParty_RunPrinterMsg1(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (RunTextPrintersRetIsActive((u8)data[0]) != TRUE)
        gTasks[taskId].func = Task_FirstBattleEnterParty_LightenFirstMonIcon;
}

static void Task_FirstBattleEnterParty_LightenFirstMonIcon(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFF0008, 4, 6, 0, RGB_BLACK);
    gTasks[taskId].func = Task_FirstBattleEnterParty_WaitLightenFirstMonIcon;
}

static void Task_FirstBattleEnterParty_WaitLightenFirstMonIcon(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_FirstBattleEnterParty_StartPrintMsg2;
}

static void Task_FirstBattleEnterParty_StartPrintMsg2(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    PartyMenu_Oak_PrintText(data[0], gText_Are);
    gTasks[taskId].func = Task_FirstBattleEnterParty_RunPrinterMsg2;
}

static void Task_FirstBattleEnterParty_RunPrinterMsg2(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (RunTextPrintersRetIsActive((u8)data[0]) != TRUE)
    {
        FirstBattleEnterParty_DestroyVoiceoverWindow((u8)data[0]);
        gTasks[taskId].func = Task_FirstBattleEnterParty_FadeNormal;
    }
}

static void Task_FirstBattleEnterParty_FadeNormal(u8 taskId)
{
    BeginNormalPaletteFade(0x0000FFF7, 4, 6, 0, RGB_BLACK);
    gTasks[taskId].func = Task_FirstBattleEnterParty_WaitFadeNormal;
}

static void Task_FirstBattleEnterParty_WaitFadeNormal(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        LoadUserWindowBorderGfx(0, 0x4F, BG_PLTT_ID(13));
        LoadUserWindowBorderGfx_(0, 0x58, BG_PLTT_ID(13));
        if (gPartyMenu.action == PARTY_ACTION_USE_ITEM)
            DisplayPartyMenuStdMessage(PARTY_MSG_USE_ON_WHICH_MON);
        else
            DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
        gTasks[taskId].func = Task_HandleChooseMonInput;
    }
}

bool8 PlayerHasMove(enum Move move)
{
    u16 item;
    switch (move)
    {
    case MOVE_CUT:
        item = ITEM_HM_CUT;
        break;
    case MOVE_FLY:
        item = ITEM_HM_FLY;
        break;
    case MOVE_SURF:
        item = ITEM_HM_SURF;
        break;
    case MOVE_STRENGTH:
        item = ITEM_HM_STRENGTH;
        break;
    case MOVE_FLASH:
        item = ITEM_HM_FLASH;
        break;
    case MOVE_ROCK_SMASH:
        item = ITEM_HM_ROCK_SMASH;
        break;
    case MOVE_WATERFALL:
        item = ITEM_HM_WATERFALL;
        break;
    case MOVE_DIVE:
        item = ITEM_HM_DIVE;
        break;
    case MOVE_ROCK_CLIMB:
        item = ITEM_HM_ROCK_CLIMB;
        break;
    case MOVE_WHIRLPOOL:
        item = ITEM_HM_WHIRLPOOL;
        break;
    default:
        return FALSE;
        break;
    }
    return CheckBagHasItem(item, 1);
}
#endif // SWSH_PARTY_MENU || PARTY_MENU_STYLE_OPTION
