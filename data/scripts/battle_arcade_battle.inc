BattleArcade_Challenge_EventScript_BeginChallenge::
	setvar VAR_TEMP_0, 2
	call BattleArcade_BattleRoom_EventScript_MCFaceCrowd
	msgbox BattleArcade_Challenge_EventScript_BeginChallenge_Text_0, MSGBOX_DEFAULT
	msgbox BattleArcade_Challenge_EventScript_BeginChallenge_Text_1, MSGBOX_DEFAULT
	arcade_takeplayerhelditems
	goto BattleArcade_Challenge_EventScript_BattleOpponent
	return


BattleArcade_Challenge_EventScript_BattleOpponent::
	tower_setopponent
	goto BattleArcade_Challenge_EventScript_SpawnOpponentStartGameBoard
	return


BattleArcade_Challenge_EventScript_SpawnOpponentStartGameBoard::
	call BattleArcade_Challenge_EventScript_AnnounceGameNumber
	call BattleArcade_BattleRoom_EventScript_SpawnOpponentEntrance
	call BattleArcade_Challenge_EventScript_BrainIntro
	call BattleArcade_Challenge_EventScript_StartGameBoard
	call BattleArcade_BattleRoom_EventScript_OpponentBattleMovement
	call BattleArcade_Challenge_EventScript_LoadOpponentText
	call BattleArcade_Challenge_EventScript_StartBattle
	goto BattleArcade_Challenge_EventScript_HandleBattleResult
	return


BattleArcade_Challenge_EventScript_AnnounceGameNumber::
	call BattleArcade_Challenge_EventScript_BufferNextBattleNumber
	msgbox BattleArcade_Challenge_EventScript_AnnounceGameNumber_Text_0, MSGBOX_DEFAULT
	closemessage
	return


BattleArcade_Challenge_EventScript_BufferNextBattleNumber::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	buffernumberstring STR_VAR_1, VAR_RESULT
	return


BattleArcade_Challenge_EventScript_StartGameBoard::
	call BattleArcade_BattleRoom_EventScript_MCMoveIntoPosition
	call BattleArcade_Challenge_EventScript_PlayGameBoard
	call BattleArcade_Challenge_EventScript_HandleGameResults
	return


BattleArcade_Challenge_EventScript_PlayGameBoard::
	msgbox BattleArcade_Challenge_EventScript_PlayGameBoard_Text_0, MSGBOX_DEFAULT
	closemessage
	arcade_generateopponentparty
	arcade_takeenemyhelditems
	arcade_playgameboard
	return


BattleArcade_Challenge_EventScript_HandleGameResults::
	msgbox BattleArcade_Challenge_EventScript_HandleGameResults_Text_0, MSGBOX_DEFAULT
	call BattleArcade_BattleRoom_EventScript_ApplyOverworldImpact
	call BattleArcade_Challenge_AnnounceImpactGiveItem
	call BattleArcade_BattleRoom_EventScript_MoveMCBack
	call BattleArcade_Challenge_SkipBattle_Script
	msgbox BattleArcade_Challenge_EventScript_HandleGameResults_Text_1, MSGBOX_DEFAULT
	closemessage
	return


BattleArcade_Challenge_AnnounceImpactGiveItem::
	compare VAR_0x8009, 0
	goto_if_ne BattleArcade_Challenge_AnnounceImpactGiveItem_2
	call BattleArcade_Challenge_AnnounceImpactGiveItem_Failure
BattleArcade_Challenge_AnnounceImpactGiveItem_1:
	closemessage
	call BattleArcade_Challenge_GiveItem_Script
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_2:
	call BattleArcade_Challenge_AnnounceImpactGiveItem_Success
	goto BattleArcade_Challenge_AnnounceImpactGiveItem_1


BattleArcade_Challenge_AnnounceImpactGiveItem_Success::
	switch VAR_0x8007
	case ARCADE_EVENT_LOWER_HP, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_2
	case ARCADE_EVENT_POISON, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_3
	case ARCADE_EVENT_PARALYZE, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_4
	case ARCADE_EVENT_BURN, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_5
	case ARCADE_EVENT_SLEEP, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_6
	case ARCADE_EVENT_FREEZE, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_7
	case ARCADE_EVENT_GIVE_BERRY, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_8
	case ARCADE_EVENT_GIVE_ITEM, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_8
	case ARCADE_EVENT_LEVEL_UP, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_9
	case ARCADE_EVENT_SUN, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_10
	case ARCADE_EVENT_RAIN, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_11
	case ARCADE_EVENT_SAND, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_12
	case ARCADE_EVENT_HAIL, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_13
	case ARCADE_EVENT_FOG, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_14
	case ARCADE_EVENT_TRICK_ROOM, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_15
	case ARCADE_EVENT_SWAP, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_16
	case ARCADE_EVENT_SPEED_UP, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_17
	case ARCADE_EVENT_SPEED_DOWN, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_18
	case ARCADE_EVENT_RANDOM, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_19
	case ARCADE_EVENT_GIVE_BP_SMALL, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_20
	case ARCADE_EVENT_GIVE_BP_BIG, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_20
	case ARCADE_EVENT_NO_BATTLE, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_21
	case ARCADE_EVENT_NO_EVENT, BattleArcade_Challenge_AnnounceImpactGiveItem_Success_22
BattleArcade_Challenge_AnnounceImpactGiveItem_Success_22:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_20, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_2:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_0, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_3:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_1, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_4:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_2, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_5:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_3, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_6:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_4, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_7:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_5, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_8:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_6, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_9:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_7, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_10:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_8, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_11:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_9, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_12:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_10, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_13:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_11, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_14:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_12, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_15:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_13, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_16:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_14, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_17:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_15, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_18:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_16, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_19:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_17, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_20:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_18, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_21:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_19, MSGBOX_DEFAULT
	return


BattleArcade_Challenge_AnnounceImpactGiveItem_Failure::
	switch VAR_0x8007
	case ARCADE_EVENT_POISON, BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_2
	case ARCADE_EVENT_PARALYZE, BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_3
	case ARCADE_EVENT_BURN, BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_4
	case ARCADE_EVENT_SLEEP, BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_5
	case ARCADE_EVENT_FREEZE, BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_6
BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_6:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_4, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_2:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_0, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_3:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_1, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_4:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_2, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_5:
	msgbox BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_3, MSGBOX_DEFAULT
	return


BattleArcade_Challenge_GiveItem_Script::
	compare VAR_0x8007, ARCADE_EVENT_GIVE_BERRY
	goto_if_ne BattleArcade_Challenge_GiveItem_Script_3
BattleArcade_Challenge_GiveItem_Script_1:
	call BattleArcade_BattleRoom_EventScript_MoveMCToTrainer
	msgbox BattleArcade_Challenge_GiveItem_Script_Text_0
	closemessage
	call BattleArcade_BattleRoom_EventScript_MoveMCFromTrainer
	return

BattleArcade_Challenge_GiveItem_Script_2:
	return

BattleArcade_Challenge_GiveItem_Script_3:
	compare VAR_0x8007, ARCADE_EVENT_GIVE_ITEM
	goto_if_ne BattleArcade_Challenge_GiveItem_Script_2
	goto BattleArcade_Challenge_GiveItem_Script_1


BattleArcade_Challenge_SkipBattle_Script::
	compare VAR_0x8007, ARCADE_EVENT_NO_BATTLE
	goto_if_ne BattleArcade_Challenge_SkipBattle_Script_2
	call BattleArcade_BattleRoom_EventScript_MoveBattlersIntoPosition
	goto BattleArcade_Challenge_EventScript_DefeatedOpponent
	return

BattleArcade_Challenge_SkipBattle_Script_2:
	return


BattleArcade_Challenge_EventScript_BattleBrain::
	arcade_setbrainobj
	goto BattleArcade_Challenge_EventScript_SpawnOpponentStartGameBoard
	return


BattleArcade_Challenge_EventScript_LoadOpponentText::
	frontier_isbrain
	compare VAR_RESULT, TRUE
	goto_if_eq BattleArcade_Challenge_EventScript_LoadOpponentText_2
	tower_getopponentintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
BattleArcade_Challenge_EventScript_LoadOpponentText_1:
	waitmessage
	closemessage
	return

BattleArcade_Challenge_EventScript_LoadOpponentText_2:
	call BattleArcade_Challenge_EventScript_BufferBrainPreBattleText
	msgbox gStringVar3, MSGBOX_DEFAULT
	goto BattleArcade_Challenge_EventScript_LoadOpponentText_1


BattleArcade_Challenge_EventScript_StartBattle::
	call BattleArcade_BattleRoom_EventScript_MoveBattlersIntoPosition
	call BattleArcade_Challenge_EventScript_DoArcadeBattle
	return


BattleArcade_Challenge_EventScript_DoArcadeBattle::
	closemessage
	setvar VAR_TEMP_2, FALSE
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	setvar VAR_0x8005, 0
	special DoArcadeTrainerBattle
	waitstate
	arcade_eventcleanup
	copyvar VAR_0x8004, VAR_FRONTIER_BATTLE_MODE
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	return


BattleArcade_Challenge_EventScript_HandleBattleResult::
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq BattleArcade_Challenge_EventScript_HandleBattleResult_2
BattleArcade_Challenge_EventScript_HandleBattleResult_1:
	arcade_checkdoubledown
	compare VAR_RESULT, TRUE
	goto_if_eq BattleArcade_Challenge_EventScript_HandleBattleResult_5
BattleArcade_Challenge_EventScript_HandleBattleResult_4:
	setvar VAR_RESULT, B_OUTCOME_LOST
	goto BattleArcade_Challenge_EventScript_SaveWarpToLobby
	return

BattleArcade_Challenge_EventScript_HandleBattleResult_2:
	goto BattleArcade_Challenge_EventScript_DefeatedOpponent
	goto BattleArcade_Challenge_EventScript_HandleBattleResult_1

BattleArcade_Challenge_EventScript_HandleBattleResult_5:
	msgbox BattleArcade_Challenge_EventScript_HandleBattleResult_Text_0, MSGBOX_DEFAULT
	arcade_clearprize
	goto BattleArcade_Challenge_EventScript_HandleBattleResult_4


BattleArcade_Challenge_EventScript_Save::
	message gText_SavingDontTurnOffPower
	waitmessage
	special LoadPlayerParty
	call BattleArcade_Challenge_EventScript_SetChallengeStatus
	playse SE_SAVE
	waitse
	closemessage
	return


BattleArcade_Challenge_EventScript_SetChallengeStatus::
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq BattleArcade_Challenge_EventScript_SetChallengeStatus_1
	tower_save CHALLENGE_STATUS_LOST
	return

BattleArcade_Challenge_EventScript_SetChallengeStatus_1:
	tower_save CHALLENGE_STATUS_WON
	return


BattleArcade_Challenge_EventScript_SaveWarpToLobby::
	call BattleArcade_Challenge_EventScript_Save
	copyvar VAR_RESULT, VAR_FRONTIER_BATTLE_MODE
	compare VAR_RESULT, FRONTIER_MODE_MULTIS
	goto_if_eq BattleArcade_Challenge_EventScript_SaveWarpToLobby_2
	warpsilent MAP_GOLDENROD_BATTLE_ARACDE_LOBBY, 7, 6
BattleArcade_Challenge_EventScript_SaveWarpToLobby_1:
	waitstate
	end

BattleArcade_Challenge_EventScript_SaveWarpToLobby_2:
	warpsilent MAP_GOLDENROD_BATTLE_ARACDE_LOBBY, 8, 6
	goto BattleArcade_Challenge_EventScript_SaveWarpToLobby_1


BattleArcade_Challenge_EventScript_DefeatedOpponent::
	frontier_isbrain
	compare VAR_RESULT, 0
	goto_if_ne BattleArcade_Challenge_EventScript_DefeatedOpponent_2
BattleArcade_Challenge_EventScript_DefeatedOpponent_1:
	arcade_setbattlewon
	call BattleArcade_BattleRoom_EventScript_MoveBattlersBack
	compare VAR_RESULT, FRONTIER_STAGES_PER_CHALLENGE
	goto_if_ge BattleArcade_Challenge_EventScript_DefeatedOpponent_5
BattleArcade_Challenge_EventScript_DefeatedOpponent_4:
	call BattleArcade_Challenge_EventScript_CashOutOrDoubleDown
	call BattleArcade_BattleRoom_EventScript_HandleHealAttendantMovement
	goto BattleArcade_Challenge_EventScript_HealPlayer
	return

BattleArcade_Challenge_EventScript_DefeatedOpponent_2:
	call BattleArcade_Challenge_EventScript_BrainCongratsText
	goto BattleArcade_Challenge_EventScript_DefeatedOpponent_1

BattleArcade_Challenge_EventScript_DefeatedOpponent_5:
	goto BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge
	goto BattleArcade_Challenge_EventScript_DefeatedOpponent_4


BattleArcade_Challenge_EventScript_CashOutOrDoubleDown::
	arcade_bufferprize
	message BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_Text_0
	waitmessage
	multichoice 20, 8, MULTI_ROCKET_ARCADE_CASH_OUT, TRUE
	switch VAR_RESULT
	case 0, BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_2
	case 1, BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_3
	case MULTI_B_PRESSED, BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_4
	return

BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_2:
	goto BattleArcade_Challenge_EventScript_DoubleDown
	return

BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_3:
	goto BattleArcade_Challenge_EventScript_CashOut
	return

BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_4:
	goto BattleArcade_Challenge_EventScript_CashOutOrDoubleDown
	return


BattleArcade_Challenge_EventScript_CashOut::
	showmoneybox 0, 0
	delay 30
	arcade_awardprize
	updatemoneybox 0
	playse SE_SHOP
	waitse
	msgbox BattleArcade_Challenge_EventScript_CashOut_Text_0, MSGBOX_DEFAULT
	hidemoneybox
	setvar VAR_RESULT, B_OUTCOME_WON
	goto BattleArcade_Challenge_EventScript_SaveWarpToLobby
	return


BattleArcade_Challenge_EventScript_DoubleDown::
	arcade_doubledown
	msgbox BattleArcade_Challenge_EventScript_DoubleDown_Text_0, MSGBOX_DEFAULT
	return


BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge::
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, FALSE
	goto_if_eq BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge_2
BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge_1:
	call BattleArcade_Challenge_EventScript_GivePrize
	msgbox BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge_Text_0
	goto BattleArcade_Challenge_EventScript_SaveWarpToLobby
	return

BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge_2:
	call BattleArcade_Challenge_EventScript_AskRecordBattle
	goto BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge_1


BattleArcade_Challenge_EventScript_GivePrize::
	showmoneybox 0, 0
	delay 30
	arcade_awardprize
	updatemoneybox 0
	playse SE_SHOP
	waitse
	msgbox BattleArcade_Challenge_EventScript_GivePrize_Text_0, MSGBOX_DEFAULT
	hidemoneybox
	return


BattleArcade_Challenge_EventScript_HealPlayer::
	msgbox BattleArcade_Challenge_EventScript_HealPlayer_Text_0
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	closemessage
	call BattleArcade_BattleRoom_EventScript_AttendantLeave
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent
	return


BattleArcade_Challenge_EventScript_AskReadyForOpponent::
	arcade_getbrainstatus
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleArcade_Challenge_EventScript_AskReadyForOpponent_2
BattleArcade_Challenge_EventScript_AskReadyForOpponent_1:
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call BattleArcade_Challenge_EventScript_ReadyForOpponent
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleArcade_Challenge_EventScript_AskReadyForOpponent_5
BattleArcade_Challenge_EventScript_AskReadyForOpponent_4:
	goto BattleArcade_Challenge_EventScript_ReadyMenu
	return

BattleArcade_Challenge_EventScript_AskReadyForOpponent_2:
	goto BattleArcade_Challenge_EventScript_BrainUpNext
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent_1

BattleArcade_Challenge_EventScript_AskReadyForOpponent_5:
	goto BattleArcade_Challenge_EventScript_ReadyMenuNoRecord
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent_4


BattleArcade_Challenge_EventScript_ReadyForOpponent::
	call BattleArcade_Challenge_EventScript_BufferNextBattleNumber
	message BattleArcade_Challenge_EventScript_ReadyForOpponent_Text_0
	waitmessage
	return


BattleArcade_Challenge_EventScript_ReadyMenu::
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, BattleArcade_Challenge_EventScript_ReadyMenu_2
	case 1, BattleArcade_Challenge_EventScript_ReadyMenu_3
	case 2, BattleArcade_Challenge_EventScript_ReadyMenu_4
	case 3, BattleArcade_Challenge_EventScript_ReadyMenu_5
	case MULTI_B_PRESSED, BattleArcade_Challenge_EventScript_ReadyMenu_6
	return

BattleArcade_Challenge_EventScript_ReadyMenu_2:
	goto BattleArcade_Challenge_EventScript_ContinueChallenge
	return

BattleArcade_Challenge_EventScript_ReadyMenu_3:
	goto BattleArcade_Challenge_EventScript_AskRecordBattleNextBattle
	return

BattleArcade_Challenge_EventScript_ReadyMenu_4:
	goto BattleArcade_Challenge_EventScript_AskPauseChallenge
	return

BattleArcade_Challenge_EventScript_ReadyMenu_5:
	goto BattleArcade_Challenge_EventScript_AskRetireChallenge
	return

BattleArcade_Challenge_EventScript_ReadyMenu_6:
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent
	return


BattleArcade_Challenge_EventScript_ReadyMenuNoRecord::
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_2
	case 1, BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_3
	case 2, BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_4
	case MULTI_B_PRESSED, BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_5
	return

BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_2:
	goto BattleArcade_Challenge_EventScript_ContinueChallenge
	return

BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_3:
	goto BattleArcade_Challenge_EventScript_AskPauseChallenge
	return

BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_4:
	goto BattleArcade_Challenge_EventScript_AskRetireChallenge
	return

BattleArcade_Challenge_EventScript_ReadyMenuNoRecord_5:
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent
	return


BattleArcade_Challenge_EventScript_AskRecordBattleNextBattle::
	call BattleArcade_Challenge_EventScript_AskRecordBattle
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent
	return


BattleArcade_Challenge_EventScript_AskRecordBattle::
	message BattleFrontier_BattleTowerBattleRoom_Text_RecordYourBattle
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	compare VAR_RESULT, 0
	goto_if_eq BattleArcade_Challenge_EventScript_AskRecordBattle_1
	return

BattleArcade_Challenge_EventScript_AskRecordBattle_1:
	call BattleFrontier_EventScript_SaveBattle
	return


BattleArcade_Challenge_EventScript_AskPauseChallenge::
	msgbox BattleArcade_Challenge_EventScript_AskPauseChallenge_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BattleArcade_Challenge_EventScript_AskPauseChallenge_2
BattleArcade_Challenge_EventScript_AskPauseChallenge_1:
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent
	return

BattleArcade_Challenge_EventScript_AskPauseChallenge_2:
	goto BattleArcade_Challenge_EventScript_PauseChallenge
	goto BattleArcade_Challenge_EventScript_AskPauseChallenge_1


BattleArcade_Challenge_EventScript_PauseChallenge::
	message gText_SavingDontTurnOffPower
	waitmessage
	arcade_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end


BattleArcade_Challenge_EventScript_AskRetireChallenge::
	message BattleArcade_Challenge_EventScript_AskRetireChallenge_Text_0
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	compare VAR_RESULT, 0
	goto_if_eq BattleArcade_Challenge_EventScript_AskRetireChallenge_2
BattleArcade_Challenge_EventScript_AskRetireChallenge_1:
	goto BattleArcade_Challenge_EventScript_AskReadyForOpponent
	return

BattleArcade_Challenge_EventScript_AskRetireChallenge_2:
	goto BattleArcade_Challenge_EventScript_RetireChallenge
	goto BattleArcade_Challenge_EventScript_AskRetireChallenge_1


BattleArcade_Challenge_EventScript_RetireChallenge::
	setvar VAR_RESULT, B_OUTCOME_LOST
	goto BattleArcade_Challenge_EventScript_SaveWarpToLobby
	return


BattleArcade_Challenge_EventScript_ContinueChallenge::
	closemessage
	goto BattleArcade_Challenge_EventScript_BattleOpponent
	return


BattleArcade_Challenge_EventScript_BrainUpNext::
	compare VAR_TEMP_2, TRUE
	goto_if_eq BattleArcade_Challenge_EventScript_BrainUpNext_2
BattleArcade_Challenge_EventScript_BrainUpNext_1:
	msgbox BattleArcade_Challenge_EventScript_BrainUpNext_Text_0, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, TRUE
	goto BattleArcade_Challenge_EventScript_AskReadyForBrain
	return

BattleArcade_Challenge_EventScript_BrainUpNext_2:
	goto BattleArcade_Challenge_EventScript_AskReadyForBrain
	goto BattleArcade_Challenge_EventScript_BrainUpNext_1


BattleArcade_Challenge_EventScript_AskReadyForBrain::
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleArcade_Challenge_EventScript_AskReadyForBrain_1
	goto BattleArcade_Challenge_EventScript_BrainReadyMenu
	return

BattleArcade_Challenge_EventScript_AskReadyForBrain_1:
	goto BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord
	return


BattleArcade_Challenge_EventScript_BrainReadyMenu::
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, BattleArcade_Challenge_EventScript_BrainReadyMenu_2
	case 1, BattleArcade_Challenge_EventScript_BrainReadyMenu_3
	case 2, BattleArcade_Challenge_EventScript_BrainReadyMenu_4
	case 3, BattleArcade_Challenge_EventScript_BrainReadyMenu_5
	case MULTI_B_PRESSED, BattleArcade_Challenge_EventScript_BrainReadyMenu_6
	return

BattleArcade_Challenge_EventScript_BrainReadyMenu_2:
	goto BattleArcade_Challenge_EventScript_BattleBrain
	return

BattleArcade_Challenge_EventScript_BrainReadyMenu_3:
	goto BattleArcade_Challenge_EventScript_AskRecordBattleNextBattle
	return

BattleArcade_Challenge_EventScript_BrainReadyMenu_4:
	goto BattleArcade_Challenge_EventScript_AskPauseChallenge
	return

BattleArcade_Challenge_EventScript_BrainReadyMenu_5:
	goto BattleArcade_Challenge_EventScript_AskRetireChallenge
	return

BattleArcade_Challenge_EventScript_BrainReadyMenu_6:
	goto BattleArcade_Challenge_EventScript_AskReadyForBrain
	return


BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord::
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_2
	case 1, BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_3
	case 2, BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_4
	case MULTI_B_PRESSED, BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_5
	return

BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_2:
	goto BattleArcade_Challenge_EventScript_BattleBrain
	return

BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_3:
	goto BattleArcade_Challenge_EventScript_AskPauseChallenge
	return

BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_4:
	goto BattleArcade_Challenge_EventScript_AskRetireChallenge
	return

BattleArcade_Challenge_EventScript_BrainReadyMenuNoRecord_5:
	goto BattleArcade_Challenge_EventScript_AskReadyForBrain
	return


BattleArcade_Challenge_EventScript_BrainIntro::
	frontier_isbrain
	compare VAR_RESULT, FALSE
	goto_if_eq BattleArcade_Challenge_EventScript_BrainIntro_2
	msgbox BattleArcade_Challenge_EventScript_BrainIntro_Text_0, MSGBOX_DEFAULT
	arcade_getprintfromstreak
	compare VAR_RESULT, ARCADE_SYMBOL_SILVER
	goto_if_eq BattleArcade_Challenge_EventScript_BrainIntro_4
	msgbox BattleArcade_Challenge_EventScript_BrainIntro_Text_2, MSGBOX_DEFAULT
	return

BattleArcade_Challenge_EventScript_BrainIntro_2:
	return

BattleArcade_Challenge_EventScript_BrainIntro_4:
	msgbox BattleArcade_Challenge_EventScript_BrainIntro_Text_1, MSGBOX_DEFAULT
	return


BattleArcade_Challenge_EventScript_BufferBrainPreBattleText::
	arcade_getprintfromstreak
	compare VAR_RESULT, ARCADE_SYMBOL_SILVER
	goto_if_eq BattleArcade_Challenge_EventScript_BufferBrainPreBattleText_1
	bufferstring STR_VAR_3, BattleArcade_Challenge_EventScript_BufferBrainPreBattleText_Text_1
	return

BattleArcade_Challenge_EventScript_BufferBrainPreBattleText_1:
	bufferstring STR_VAR_3, BattleArcade_Challenge_EventScript_BufferBrainPreBattleText_Text_0
	return


BattleArcade_Challenge_EventScript_BrainCongratsText::
	arcade_getprintfromstreak
	compare VAR_RESULT, ARCADE_SYMBOL_SILVER
	goto_if_eq BattleArcade_Challenge_EventScript_BrainCongratsText_2
	msgbox BattleArcade_Challenge_EventScript_BrainCongratsText_Text_1, MSGBOX_DEFAULT
BattleArcade_Challenge_EventScript_BrainCongratsText_1:
	closemessage
	return

BattleArcade_Challenge_EventScript_BrainCongratsText_2:
	msgbox BattleArcade_Challenge_EventScript_BrainCongratsText_Text_0, MSGBOX_DEFAULT
	goto BattleArcade_Challenge_EventScript_BrainCongratsText_1


BattleArcade_Challenge_EventScript_BeginChallenge_Text_0:
	.string "Welcome to the Rocket Arcade!$"

BattleArcade_Challenge_EventScript_BeginChallenge_Text_1:
	.string "First, I’ll need to hold on to any items\n"
	.string "held by your Pokémon.$"

BattleArcade_Challenge_EventScript_AnnounceGameNumber_Text_0:
	.string "Game no. {STR_VAR_1}! Come on!$"

BattleArcade_Challenge_EventScript_PlayGameBoard_Text_0:
	.string "Without further ado... Let’s activate\n"
	.string "the game board!$"

BattleArcade_Challenge_EventScript_HandleGameResults_Text_0:
	.string "This is our current event!$"

BattleArcade_Challenge_EventScript_HandleGameResults_Text_1:
	.string "OK! Let the battle commence!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_0:
	.string "The match will commence with\n"
	.string "{STR_VAR_1}’s Pokémon without full\l"
	.string "HP!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_1:
	.string "The match will commence with\n"
	.string "{STR_VAR_1}’s Pokémon poisoned!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_2:
	.string "The match will commence with\n"
	.string "{STR_VAR_1}’s Pokémon paralyzed!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_3:
	.string "The match will commence with\n"
	.string "{STR_VAR_1}’s Pokémon burned!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_4:
	.string "The match will commence with\n"
	.string "{STR_VAR_1}’s Pokémon asleep!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_5:
	.string "The match will commence with\n"
	.string "{STR_VAR_1}’s Pokémon frozen!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_6:
	.string "{STR_VAR_1}’s Pokémon will be loaned\n"
	.string "the {STR_VAR_3}.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_7:
	.string "The match will commence with\n"
	.string "{STR_VAR_1}’s Pokémon leveled up!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_8:
	.string "This match will be conducted under\n"
	.string "harsh sunlight.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_9:
	.string "This match will be conducted under a\n"
	.string "steady rainfall.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_10:
	.string "This match will be conducted under a\n"
	.string "raging sandstorm.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_11:
	.string "This match will be conducted under\n"
	.string "pelting hail.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_12:
	.string "This match will be conducted in a dense\n"
	.string "fog.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_13:
	.string "This match will be conducted on a floor\n"
	.string "where time and space are distorted.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_14:
	.string "Your Pokémon will be switched with the\n"
	.string "other Trainer’s for this match.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_15:
	.string "From the next game on, the game board’s\n"
	.string "speed will be increased.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_16:
	.string "From the next game on, the game board’s\n"
	.string "speed will be decreased.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_17:
	.string "For the next game, the game board’s\n"
	.string "motion will become random.$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_18:
	.string "The prize panel flashes, but the Rocket\n"
	.string "Arcade only pays out after a win!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_19:
	.string "Oh! Lucky! You can skip the battle!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Success_Text_20:
	.string "Too bad! There is no event this time!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_0:
	.string "{STR_VAR_1}’s Pokémon will enter the\n"
	.string "match poisoned... Oh! A lucky break!\l"
	.string "{STR_VAR_1} has no Pokémon that\l"
	.string "can be poisoned!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_1:
	.string "{STR_VAR_1}’s Pokémon will enter the\n"
	.string "match paralyzed... Oh! A lucky break!\l"
	.string "{STR_VAR_1} has no Pokémon that\l"
	.string "can be paralyzed!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_2:
	.string "{STR_VAR_1}’s Pokémon will enter the\n"
	.string "match burned... Oh! A lucky break!\l"
	.string "{STR_VAR_1} has no Pokémon that\l"
	.string "can be burned!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_3:
	.string "{STR_VAR_1}’s Pokémon will enter the\n"
	.string "match asleep... Oh! A lucky break!\l"
	.string "{STR_VAR_1} has no Pokémon that\l"
	.string "can be made to sleep!$"

BattleArcade_Challenge_AnnounceImpactGiveItem_Failure_Text_4:
	.string "{STR_VAR_1}’s Pokémon will enter the\n"
	.string "match frozen... Oh! A lucky break!\l"
	.string "{STR_VAR_1} has no Pokémon that\l"
	.string "can be frozen!$"

BattleArcade_Challenge_GiveItem_Script_Text_0:
	.string "Here you go!$"

BattleArcade_Challenge_EventScript_HandleBattleResult_Text_0:
	.string "You lost it all! Better luck next time.$"

BattleArcade_Challenge_EventScript_CashOutOrDoubleDown_Text_0:
	.string "You won ¥{STR_VAR_1}!\n"
	.string "Cash out or risk it all?$"

BattleArcade_Challenge_EventScript_CashOut_Text_0:
	.string "You cashed out ¥{STR_VAR_2}!$"

BattleArcade_Challenge_EventScript_DoubleDown_Text_0:
	.string "Double down accepted! The next round\n"
	.string "puts it all on the line.$"

BattleArcade_RoulettRoom_EventScript_ResolveEndChallenge_Text_0:
	.string "We will return any items we were holding\n"
	.string "for you.$"

BattleArcade_Challenge_EventScript_GivePrize_Text_0:
	.string "Congratulations! You earned\n"
	.string "¥{STR_VAR_2} as your prize!$"

BattleArcade_Challenge_EventScript_HealPlayer_Text_0:
	.string "Good going! We’ll heal your Pokémon now.$"

BattleArcade_Challenge_EventScript_ReadyForOpponent_Text_0:
	.string "Next up, game no. {STR_VAR_1}! Are\n"
	.string "you ready?$"

BattleArcade_Challenge_EventScript_AskPauseChallenge_Text_0:
	.string "Would you like to save and take a break\n"
	.string "from playing?$"

BattleArcade_Challenge_EventScript_AskRetireChallenge_Text_0:
	.string "Would you like to retire from this\n"
	.string "challenge?$"

BattleArcade_Challenge_EventScript_BrainUpNext_Text_0:
	.string "Congratulations, Trainer! In\n"
	.string "recognition of your outstanding nerve,\l"
	.string "our Frontier Brain is demanding a match\l"
	.string "with you. So, your next match is against\l"
	.string "Archer, the Rocket Arcade Boss; no ifs\l"
	.string "or buts! Are you ready?$"

BattleArcade_Challenge_EventScript_BrainIntro_Text_0:
	.string "Archer: The Rocket Arcade rewards\n"
	.string "skill, not luck.\p"
	.string "You have pressed your advantage well\n"
	.string "enough to stand before me once more.\l"
	.string "But this time I will show you the true\l"
	.string "might of Team Rocket.$"

BattleArcade_Challenge_EventScript_BrainIntro_Text_1:
	.string "Show me whether your skill is true, or\n"
	.string "mere luck.$"

BattleArcade_Challenge_EventScript_BrainIntro_Text_2:
	.string "You have returned with the same\n"
	.string "arrogance as before. I will correct\l"
	.string "that.$"

BattleArcade_Challenge_EventScript_BufferBrainPreBattleText_Text_0:
	.string "Archer: A proper Rocket Operative\n"
	.string "never leaves victory to chance. Let us\l"
	.string "see if you can stand against it.$"

BattleArcade_Challenge_EventScript_BufferBrainPreBattleText_Text_1:
	.string "Archer: You have pushed deeper into my\n"
	.string "house than most. Now pay attention to\l"
	.string "how a Rocket closes a game.$"

BattleArcade_Challenge_EventScript_BrainCongratsText_Text_0:
	.string "Archer: Hmph. You read the table\n"
	.string "correctly and struck when it mattered.\l"
	.string "Take your winnings.$"

BattleArcade_Challenge_EventScript_BrainCongratsText_Text_1:
	.string "Archer: You have taken even the\n"
	.string "house's best hand. Remember this\l"
	.string "feeling. It is expensive to chase.$"
