#ifndef GUARD_PARTY_MENU_H
#define GUARD_PARTY_MENU_H

#include "main.h"
#include "task.h"

// seems like the last two fields may have been left as all-purpose vars
// and the second of the two just happens to only be used in one case
struct PartyMenu
{
    MainCallback exitCallback;
    TaskFunc task;
    u8 menuType:4;
    u8 layout:2;
    s8 slotId;
    s8 slotId2;
    u8 action;
    u16 bagItem;
    s16 data1;           // used variously as a move, counter, moveSlotId, cursorPos, or indicator that the menu is opened from the field
    s16 learnMoveState;  // data2, used only as a learn move state
};

#define DATA1_PARTY_MENU_FROM_FIELD -1

extern struct PartyMenu gPartyMenu;
extern bool8 gPartyMenuUseExitCallback;
extern u8 gSelectedMonPartyId;
extern MainCallback gPostMenuFieldCallback;
extern u8 gSelectedOrderFromParty[MAX_FRONTIER_PARTY_SIZE];
extern u8 gBattlePartyCurrentOrder[PARTY_SIZE / 2];

extern const struct SpriteSheet gSpriteSheet_HeldItem;
extern const u16 gHeldItemPalette[];

extern void (*gItemUseCB)(u8, TaskFunc);
extern const struct SpriteTemplate gSpriteTemplate_StatusIcons;

/*
**DS PARTY SCREEN**
Below features are configs for the DS party screen.
I did not create the DS party screen, the base comes from TheXaman: https://github.com/TheXaman/pokeemerald/tree/tx_ui_party_screen_ds_style_2
While graphics + other touch ups come from the original FRLG/Em patch here: https://www.pokecommunity.com/threads/fr-em-pok%C3%A9mon-party-screen-modifications-base-hgss-and-bw-styles.414022/
Huge credits to everyone involved!
*/

#define PARTY_MENU_STYLE_DEFAULT    0
#define PARTY_MENU_STYLE_HGSS       1
#define PARTY_MENU_STYLE_BW         2

#ifndef PARTY_MENU_STYLE
#define PARTY_MENU_STYLE                   PARTY_MENU_STYLE_BW
#endif
#define PARTY_MENU_ALPHA                   (PARTY_MENU_STYLE == PARTY_MENU_STYLE_BW) // If TRUE, the columns have a transparent BG. 
                                                                                     // Only designed for the BW style, so looks ugly on other styles.
#define PARTY_MENU_HIGHLIGHT_ACTIVE_SINGLE FALSE // If TRUE, in single battles, changes the colour of the first party slot. Easier to see who is on the field, in my opinion.
#define PARTY_MENU_HIGHLIGHT_ACTIVE_DOUBLE FALSE // If TRUE, in double battles, changes the colour of the first two party slots. Easier to see who is on the field, in my opinion.
                                                 // This is not active in multi-battles, as it uses the colour that is usually used to represent our partner's pokemon.
void AnimatePartySlot(u8 slot, u8 animNum);
bool8 IsMultiBattle(void);
u8 GetCursorSelectionMonId(void);
u8 GetPartyMenuType(void);
void Task_HandleChooseMonInput(u8 taskId);
u8 *GetMonNickname(struct Pokemon *mon, u8 *dest);
u8 DisplayPartyMenuMessage(const u8 *str, bool8 keepOpen);
bool8 IsPartyMenuTextPrinterActive(void);
void PartyMenuModifyHP(u8 taskId, u8 slot, s8 hpIncrement, s16 hpDifference, TaskFunc task);
u8 GetAilmentFromStatus(u32 status);
u8 GetMonAilment(struct Pokemon *mon);
void DisplayPartyMenuStdMessage(u32 stringId);
bool8 FieldCallback_PrepareFadeInFromMenu(void);
bool8 FieldCallback_PrepareFadeInForTeleport(void);
void CB2_ReturnToPartyMenuFromFlyMap(void);
void LoadHeldItemIcons(void);
void DrawHeldItemIconsForTrade(u8 *partyCounts, u8 *partySpriteIds, u8 whichParty);
void LoadPartyMenuAilmentGfx(void);
void CB2_ShowPartyMenuForItemUse(void);
void ItemUseCB_BattleScript(u8 taskId, TaskFunc task);
void ItemUseCB_BattleChooseMove(u8 taskId, TaskFunc task);
void ItemUseCB_Medicine(u8 taskId, TaskFunc task);
void ItemUseCB_ChangePokeball(u8 taskId, TaskFunc task);
void ItemUseCB_AbilityCapsule(u8 taskId, TaskFunc task);
void ItemUseCB_AbilityPatch(u8 taskId, TaskFunc task);
void ItemUseCB_ShinGenome(u8 taskId, TaskFunc task);
void ItemUseCB_Mint(u8 taskId, TaskFunc task);
void ItemUseCB_ResetEVs(u8 taskId, TaskFunc task);
void ItemUseCB_ReduceEV(u8 taskId, TaskFunc task);
void ItemUseCB_PPRecovery(u8 taskId, TaskFunc task);
void ItemUseCB_PPUp(u8 taskId, TaskFunc task);
enum Move ItemIdToBattleMoveId(enum Item item);
bool8 MonKnowsMove(struct Pokemon *mon, enum Move move);
bool8 BoxMonKnowsMove(struct BoxPokemon *boxMon, enum Move move);
bool8 PlayerHasMove(enum Move move);
void ItemUseCB_TMHM(u8 taskId, TaskFunc task);
void ItemUseCB_RareCandy(u8 taskId, TaskFunc task);
void ItemUseCB_DynamaxCandy(u8 taskId, TaskFunc task);
void ItemUseCB_SacredAsh(u8 taskId, TaskFunc task);
void ItemUseCB_EvolutionStone(u8 taskId, TaskFunc task);
void ItemUseCB_FormChange(u8 taskId, TaskFunc task);
void ItemUseCB_FormChange_ConsumedOnUse(u8 taskId, TaskFunc task);
void ItemUseCB_RotomCatalog(u8 taskId, TaskFunc task);
void ItemUseCB_ZygardeCube(u8 taskId, TaskFunc task);
void ItemUseCB_Fusion(u8 taskId, TaskFunc task);
enum ItemEffectType GetItemEffectType(enum Item item);
void CB2_PartyMenuFromStartMenu(void);
void CB2_ChooseMonToGiveItem(void);
void ChooseMonToGiveMailFromMailbox(void);
void InitChooseHalfPartyForBattle(u8 unused);
void ClearSelectedPartyOrder(void);
void ChooseMonForTradingBoard(u8 menuType, MainCallback callback);
void ChooseMonForMoveTutor(void);
void ChooseMonForWirelessMinigame(void);
void OpenPartyMenuInBattle(u8 partyAction);
void ChooseMonForInBattleItem(void);
void BufferBattlePartyCurrentOrder(void);
void BufferBattlePartyCurrentOrderBySide(enum BattlerId battler, u8 flankId);
void SwitchPartyOrderLinkMulti(enum BattlerId battler, u8 slot, u8 slot2);
void SwitchPartyMonSlots(u8 slot, u8 slot2);
u8 GetPartyIdFromBattlePartyId(u8 battlePartyId);
void ShowPartyMenuToShowcaseMultiBattleParty(void);
void ChooseMonForDaycare(void);
bool8 CB2_FadeFromPartyMenu(void);
void CB2_ReturnToPartyMenuFromSummaryScreen(void);
void ChooseContestMon(void);
void ChoosePartyMon(void);
void ChooseMonForMoveRelearner(void);
void BattlePyramidChooseMonHeldItems(void);
void DoBattlePyramidMonsHaveHeldItem(void);
void IsSelectedMonEgg(void);
void IsLastMonThatKnowsSurf(void);
void MoveDeleterForgetMove(void);
void BufferMoveDeleterNicknameAndMove(void);
void GetNumMovesSelectedMonHas(void);
void MoveDeleterChooseMoveToForget(void);

bool32 SetUpFieldMove_Surf(void);
bool32 SetUpFieldMove_Fly(void);
bool32 SetUpFieldMove_Waterfall(void);
bool32 SetUpFieldMove_Dive(void);
bool32 SetUpFieldMove_RockClimb(void);
bool32 SetUpFieldMove_Whirlpool(void);

#if TESTING
bool32 SwShPartyMenu_TestGiveHeldItemToMon(u8 partyId, enum Item item);
bool32 SwShPartyMenu_TestCancelHeldItemSwitch(enum Item item);
bool32 SwShPartyMenu_TestTossHeldItem(u8 partyId);
bool32 SwShPartyMenu_TestMissingSlotSpritesAreIgnored(void);
bool32 SwShPartyMenu_TestEmptyHeldItemSlotIsIgnored(bool8 inItemMode);
#endif

#endif // GUARD_PARTY_MENU_H
