// bug_contest.c
#include "global.h"
#include "achievements.h"
#include "script.h"
#include "event_data.h"
#include "fieldmap.h"
#include "overworld.h"
#include "bug_contest.h"
#include "constants/flags.h"
#include "constants/maps.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "script.h"
#include "pokemon.h"
#include "constants/species.h"
#include "item.h"
#include "battle.h"
#include "field_screen_effect.h"
#include "pokemon.h"
#include "string_util.h"
#include "constants/map_event_ids.h"
#include "constants/party_menu.h"
#include "load_save.h"
extern const struct SpeciesInfo gSpeciesInfo[];
static bool32 IsPlayerDefeated(u32 battleOutcome);
static u32 sBugContestStartTime;
static bool8 sBugContestTimerActive;
static u32 sBugContestLeadPersonality;
static u32 sBugContestLeadOtId;


bool32 GetBugContestFlag(void)
{
    return FlagGet(FLAG_SYS_BUG_CONTEST_MODE);
}


void BugContestRetirePrompt(void)
{
    ScriptContext_SetupScript(BugContest_EventScript_TimesUp);
}

void EnterBugContestMode(void)
{
    FlagSet(FLAG_SYS_BUG_CONTEST_MODE);
    sBugContestStartTime = gMain.vblankCounter1;
    sBugContestTimerActive = TRUE;
    sBugContestLeadPersonality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
    sBugContestLeadOtId = GetMonData(&gPlayerParty[0], MON_DATA_OT_ID);
}

void ExitBugContestMode(void)
{
    struct Pokemon *savedLead = GetSavedPlayerPartyMon(0);

    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];

        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE
            && GetMonData(mon, MON_DATA_PERSONALITY) == sBugContestLeadPersonality
            && GetMonData(mon, MON_DATA_OT_ID) == sBugContestLeadOtId)
        {
            for (u32 slot = 0; slot < MAX_MON_ITEMS; slot++)
            {
                u16 item = GetMonData(mon, MON_DATA_HELD_ITEM + slot);
                SetMonData(savedLead, MON_DATA_HELD_ITEM + slot, &item);
            }

            u8 mail = GetMonData(mon, MON_DATA_MAIL);
            SetMonData(savedLead, MON_DATA_MAIL, &mail);
            break;
        }
    }

    LoadPlayerParty();
    FlagClear(FLAG_SYS_BUG_CONTEST_MODE);
    sBugContestTimerActive = FALSE;
    sBugContestLeadPersonality = 0;
    sBugContestLeadOtId = 0;
}

bool8 BugContestCheckTimeLimit(void)
{
    if (!FlagGet(FLAG_SYS_BUG_CONTEST_MODE) || !sBugContestTimerActive)
        return FALSE;

    u32 elapsed = gMain.vblankCounter1 - sBugContestStartTime;
    if (elapsed >= BUG_CONTEST_TIME_LIMIT_FRAMES) // 5 minutes by default
    {
        sBugContestTimerActive = FALSE;
        ScriptContext_SetupScript(BugContest_EventScript_TimesUp);
        return TRUE;
    }

    return FALSE;
}



bool8 TransferBugContestMon(void)
{
    u8 monIndex = VarGet(VAR_0x8004);
    struct Pokemon *mon = &gPlayerParty[monIndex];
    struct BoxPokemon *boxMon = &mon->box;
    u8 boxId, boxPos;

    if (StorePokemonInBox(boxMon, &boxId, &boxPos) != -1)
    {
        ZeroMonData(mon);  // Remove mon from party after storing
        CompactPartySlots();
        gSpecialVar_Result = MON_GIVEN_TO_PC;
    }
    else
    {
        gSpecialVar_Result = MON_CANT_GIVE;
    }

    return FALSE;
}



bool8 JudgeBugContestMon(void)
{
    //Scyther max hp: 53
        //low 48
    //Pinsir max hp: 51
        //low 46
    //Butterfree min hp:45
    //Beedrill min hp:44
    //Venonat min hp:40
    //metapod min hp:49
    //paras min hp:33

    u16 monIndex = VarGet(VAR_0x8004);
    u16 UNUSED species = GetMonData(&gPlayerParty[monIndex], MON_DATA_SPECIES);
    u8 maxHP = GetMonData(&gPlayerParty[monIndex], MON_DATA_MAX_HP); //change to MON_DATA_HP for a more authentic johto experience
    u16 rand = Random() % 100;
    u16 placement;
    bool8 isShiny;
    isShiny = GetMonData(&gPlayerParty[monIndex], MON_DATA_IS_SHINY);
    
    if (isShiny) // Shiny is unconditional first place
    {
        gSpecialVar_Result = 1;
        placement = gSpecialVar_Result;
    }
    else if (maxHP < 41)
    {
        gSpecialVar_Result = 3;
        placement = gSpecialVar_Result;
    }
    else if (maxHP <= 46)
    {
        gSpecialVar_Result = (rand < 50) ? 2 : 3;
        placement = gSpecialVar_Result;
    }
    else if (maxHP <= 47)
    {
        gSpecialVar_Result = (rand < 75) ? 1 : 2;
        placement = gSpecialVar_Result;
    }
    else // baseHP >= 48
    {
        gSpecialVar_Result = 1;
        placement = gSpecialVar_Result;
    }

    static const u16 sThirdPlaceRewards[]  = {
        ITEM_ORAN_BERRY, ITEM_CHERI_BERRY, ITEM_PERSIM_BERRY, ITEM_SITRUS_BERRY,
        ITEM_PECHA_BERRY, ITEM_RAWST_BERRY, ITEM_ASPEAR_BERRY, ITEM_CHESTO_BERRY
    };

    switch (placement)
    {
    case 1:
        Achievement_Unlock(ACH_BUG_CATCHER);
        VarSet(VAR_0x8005, ITEM_NONE);
        break;
    case 2:
        VarSet(VAR_0x8005, ITEM_NONE);
        break;
    case 3:
        VarSet(VAR_0x8005, sThirdPlaceRewards[Random() % ARRAY_COUNT(sThirdPlaceRewards)]);
        break;
    default:
        VarSet(VAR_0x8005, ITEM_NONE);
        break;
    }

    return FALSE;
}


static bool32 IsPlayerDefeated(u32 battleOutcome)
{
    switch (battleOutcome)
    {
    case B_OUTCOME_LOST:
    case B_OUTCOME_DREW:
        return TRUE;
    case B_OUTCOME_WON:
    case B_OUTCOME_RAN:
    case B_OUTCOME_PLAYER_TELEPORTED:
    case B_OUTCOME_MON_FLED:
    case B_OUTCOME_CAUGHT:
        return FALSE;
    default:
        return FALSE;
    }
}

void CB2_EndBugContestBattle(void)
{
    CpuFill16(0, (void *)(BG_PLTT), BG_PLTT_SIZE);
    ResetOamRange(0, 128);
    u8 partyCount = 0;
    for (u8 i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE)
            partyCount++;
    }

    if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        SetMainCallback2(CB2_BugContestWhiteOut);
    }
    else if (gBattleOutcome == B_OUTCOME_CAUGHT)
    {

        if (partyCount == PARTY_SIZE)
        {
            ScriptContext_SetupScript(BugContest_EventScript_TimesUp); //change
        }
        SetMainCallback2(CB2_ReturnToField);
        gFieldCallback = FieldCB_ReturnToFieldNoScriptCheckMusic;
    }
    else
    {
        SetMainCallback2(CB2_ReturnToField);
        gFieldCallback = FieldCB_ReturnToFieldNoScriptCheckMusic;
    }
}

bool8 RemoveSafariBalls(void)
{
    u16 count = CountTotalItemQuantityInBag(ITEM_SAFARI_BALL);

    if (count > 0)
        RemoveBagItem(ITEM_SAFARI_BALL, count);

    return FALSE;
}

bool8 ValidateBugContestSelectedMon(void)
{
    u16 monIndex = VarGet(VAR_0x8004);
    u32 personality;
    u32 otId;

    if (monIndex == PARTY_NOTHING_CHOSEN || monIndex >= PARTY_SIZE)
    {
        gSpecialVar_Result = FALSE;
        return FALSE;
    }

    personality = GetMonData(&gPlayerParty[monIndex], MON_DATA_PERSONALITY);
    otId = GetMonData(&gPlayerParty[monIndex], MON_DATA_OT_ID);

    gSpecialVar_Result = !(personality == sBugContestLeadPersonality && otId == sBugContestLeadOtId);
    return FALSE;
}

bool8 ShowBugContestChosenMon(void)
{
    u16 monIndex = VarGet(VAR_0x8004);
    u16 species = GetMonData(&gPlayerParty[monIndex], MON_DATA_SPECIES);

    StringCopy(gStringVar1, GetSpeciesName(species));

    switch (species)
    {
    case SPECIES_CATERPIE:
        gSpecialVar_Result = LOCALID_BUGCONTEST_CATERPIE;
        break;
    case SPECIES_WEEDLE:
        gSpecialVar_Result = LOCALID_BUGCONTEST_WEEDLE;
        break;
    case SPECIES_METAPOD:
        gSpecialVar_Result = LOCALID_BUGCONTEST_METAPOD;
        break;
    case SPECIES_KAKUNA:
        gSpecialVar_Result = LOCALID_BUGCONTEST_KAKUNA;
        break;
    case SPECIES_SEWADDLE:
        gSpecialVar_Result = LOCALID_BUGCONTEST_SEWADDLE;
        break;
    case SPECIES_VENIPEDE:
        gSpecialVar_Result = LOCALID_BUGCONTEST_VENIPEDE;
        break;
    case SPECIES_BUTTERFREE:
        gSpecialVar_Result = LOCALID_BUGCONTEST_BUTTERFREE;
        break;
    case SPECIES_BEEDRILL:
        gSpecialVar_Result = LOCALID_BUGCONTEST_BEEDRILL;
        break;
    case SPECIES_SCYTHER:
        gSpecialVar_Result = LOCALID_BUGCONTEST_SCYTHER;
        break;
    case SPECIES_PINSIR:
        gSpecialVar_Result = LOCALID_BUGCONTEST_PINSIR;
        break;
    default:
        gSpecialVar_Result = LOCALID_BUGCONTEST_CATERPIE;
        break;
    }

    return FALSE;
}
