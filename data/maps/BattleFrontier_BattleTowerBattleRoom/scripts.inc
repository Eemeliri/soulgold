# 1 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 2 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_MapScripts::
# 3 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerBattleRoom_OnFrame
# 4 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerBattleRoom_OnWarp
# 5 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.byte 0
# 6 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 7 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_OnWarp:
# 8 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerBattleRoom_EventScript_SetUpObjects
# 9 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.2byte 0
# 10 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 11 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_SetUpObjects::
# 12 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_TEMP_1, 1
# 13 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SetInvisible
# 14 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	end
# 15 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 16 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_OnFrame:
# 17 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleTowerBattleRoom_EventScript_EnterRoom
# 18 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.2byte 0
# 19 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 20 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_EnterRoom::
# 21 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_TEMP_0, 1
# 22 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerEnter
# 23 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 24 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_get FRONTIER_DATA_BATTLE_NUM
# 25 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerBattleRoom_EventScript_OpponentEnter
# 26 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantApproachPlayer
# 27 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 28 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceAttendant
# 29 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 30 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_TEMP_2, 1
# 31 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
# 32 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 33 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 34 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_OpponentEnter::
# 35 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_setopponent
# 36 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	addobject LOCALID_TOWER_BATTLE_OPPONENT
# 37 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_OPPONENT, BattleFrontier_BattleTowerBattleRoom_Movement_OpponentEnter
# 38 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 39 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_getopponentintro 0
# 40 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 41 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 42 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle
# 43 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 44 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case B_OUTCOME_WON, BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedOpponent
# 45 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTower_EventScript_WarpToLobbyLost::
# 46 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
# 47 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_set TOWER_DATA_LVL_MODE
# 48 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_0x8004, FANCOUNTER_USED_BATTLE_TOWER
# 49 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	special Script_TryGainNewFanFromCounter
# 50 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobby
# 51 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 52 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedOpponent::
# 53 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_EventScript_IncrementWinStreak
# 54 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_setbattlewon
# 55 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	@ switch VAR_RESULT
# 56 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	@ case 7, BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
# 57 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_OPPONENT, BattleFrontier_BattleTowerBattleRoom_Movement_OpponentExit
# 58 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 59 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	removeobject LOCALID_TOWER_BATTLE_OPPONENT
# 60 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_getbrainstatus
# 61 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call_if_ne VAR_RESULT, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattleTowerBattleRoom_EventScript_SecondAttendantEnter
# 62 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantApproachPlayer
# 63 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 64 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceAttendant
# 65 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 66 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_RestoreMonsToFullHealth, MSGBOX_DEFAULT
# 67 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	playfanfare MUS_HEAL
# 68 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitfanfare
# 69 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	special HealPlayerParty
# 70 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
    tower_givepoints
# 71 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
    msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS 
# 72 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent::
# 73 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_getbrainstatus
# 74 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	copyvar VAR_BATTLE_TOWER_STREAK, VAR_RESULT
# 75 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_ne VAR_RESULT, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattleTowerBattleRoom_EventScript_MaidenUpNext
# 76 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_get FRONTIER_DATA_BATTLE_NUM
# 77 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyForOpponent
# 78 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_EventScript_GetCantRecordBattle
# 79 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponentNoRecord
# 80 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, TRUE
# 81 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 82 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_ContinueChallenge
# 83 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRecordBattle
# 84 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
# 85 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 3, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
# 86 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 87 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 88 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponentNoRecord::
# 89 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
# 90 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 91 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_ContinueChallenge
# 92 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
# 93 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
# 94 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 95 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 96 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AskRecordBattle::
# 97 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_RecordYourBattle
# 98 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 99 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
# 100 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 101 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 102 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_RecordBattle
# 103 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 104 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 105 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_RecordBattle::
# 106 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_EventScript_SaveBattle
# 107 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 108 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 109 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge::
# 110 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
# 111 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 112 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case NO, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 113 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case YES, BattleFrontier_BattleTowerBattleRoom_EventScript_PauseChallenge
# 114 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 115 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 116 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge::
# 117 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_CancelYourChallenge
# 118 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 119 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
# 120 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 121 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 122 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_RetireChallenge
# 123 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
# 124 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 125 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_ContinueChallenge::
# 126 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	closemessage
# 127 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceBattle
# 128 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 129 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantReturnToPos
# 130 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 131 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_OpponentEnter
# 132 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 133 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon::
# 134 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
# 135 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_set TOWER_DATA_LVL_MODE
# 136 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_0x8004, FANCOUNTER_USED_BATTLE_TOWER
# 137 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	special Script_TryGainNewFanFromCounter
# 138 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobby
# 139 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 140 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_PauseChallenge::
# 141 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_SavingPleaseWait
# 142 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 143 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_save CHALLENGE_STATUS_PAUSED
# 144 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	playse SE_SAVE
# 145 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitse
# 146 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	fadescreen FADE_TO_BLACK
# 147 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_reset
# 148 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	end
# 149 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 150 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor2ndOpponent::
# 151 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent
# 152 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 153 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 154 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 155 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor3rdOpponent::
# 156 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor3rdOpponent
# 157 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 158 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 159 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 160 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor4thOpponent::
# 161 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor4thOpponent
# 162 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 163 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 164 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 165 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor5thOpponent::
# 166 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor5thOpponent
# 167 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 168 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 169 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 170 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor6thOpponent::
# 171 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor6thOpponent
# 172 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 173 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 174 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 175 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor7thOpponent::
# 176 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor7thOpponent
# 177 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 178 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 179 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 180 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_EventScript_IncrementWinStreak::
# 181 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_incrementstreak
# 182 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 183 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 184 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_SecondAttendantEnter::
# 185 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantEnter
# 186 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 187 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_2, Common_Movement_WalkInPlaceLeft
# 188 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 189 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	playse SE_PIN
# 190 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_1, Common_Movement_ExclamationMark
# 191 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 192 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_1, Common_Movement_Delay48
# 193 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 194 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantDelay
# 195 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantFaceSecondAttendant
# 196 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 197 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantExit
# 198 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 199 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 200 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 201 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_MaidenUpNext::
# 202 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_TEMP_2, 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden
# 203 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_SalonMaidenOnHerWay, MSGBOX_DEFAULT
# 204 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_TEMP_2, 1
# 205 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden::
# 206 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyForSalonMaiden
# 207 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 208 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_EventScript_GetCantRecordBattle
# 209 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaidenNoRecord
# 210 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, TRUE
# 211 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 212 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabel
# 213 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRecordBattle
# 214 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
# 215 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 3, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
# 216 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden
# 217 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 218 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaidenNoRecord::
# 219 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
# 220 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_RESULT
# 221 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabel
# 222 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
# 223 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
# 224 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden
# 225 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 226 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabel::
# 227 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_EventScript_SetBrainObjectGfx
# 228 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	closemessage
# 229 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceBattle
# 230 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 231 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantReturnToPos
# 232 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 233 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	addobject LOCALID_TOWER_BATTLE_OPPONENT
# 234 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	applymovement LOCALID_TOWER_BATTLE_OPPONENT, BattleFrontier_BattleTowerBattleRoom_Movement_AnabelEnter
# 235 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmovement 0
# 236 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	switch VAR_TEMP_F
# 237 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleTowerBattleRoom_EventScript_AnabelGoldIntro
# 238 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelSilver
# 239 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelGold
# 240 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
# 241 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelSilver
# 242 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_GreetingsImAnabel, MSGBOX_DEFAULT
# 243 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
# 244 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelSilver::
# 245 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_LetMeSeeYourTalent, MSGBOX_DEFAULT
# 246 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle
# 247 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelSilver
# 248 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
# 249 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 250 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelSilver::
# 251 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_EventScript_IncrementWinStreak
# 252 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_getsymbols
# 253 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_ne VAR_RESULT, 0, BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
# 254 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelTalentShallBeRecognized, MSGBOX_DEFAULT
# 255 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	playfanfare MUS_OBTAIN_SYMBOL
# 256 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_ReceivedAbilitySymbol
# 257 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 258 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitfanfare
# 259 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_givesymbol
# 260 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_UntilNextTime, MSGBOX_DEFAULT
# 261 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
# 262 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 263 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_AnabelGoldIntro::
# 264 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
# 265 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelGold
# 266 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelYouCameBack, MSGBOX_DEFAULT
# 267 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
# 268 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelGold::
# 269 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_LetsBeginShallWe, MSGBOX_DEFAULT
# 270 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle
# 271 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelGold
# 272 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
# 273 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 274 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelGold::
# 275 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	call BattleFrontier_EventScript_IncrementWinStreak
# 276 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_getsymbols
# 277 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, 2, BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
# 278 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelCongratsYourPassPlease, MSGBOX_DEFAULT
# 279 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	playfanfare MUS_OBTAIN_SYMBOL
# 280 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	message BattleFrontier_BattleTowerBattleRoom_Text_AbilitySymbolTookGoldenShine
# 281 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitmessage
# 282 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitfanfare
# 283 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_givesymbol
# 284 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_WishICouldBattleYouAgain, MSGBOX_DEFAULT
# 285 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
# 286 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 287 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle::
# 288 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	closemessage
# 289 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_TEMP_2, 0
# 290 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
# 291 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	special HealPlayerParty
# 292 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_0x8004, SPECIAL_BATTLE_TOWER
# 293 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setvar VAR_0x8005, 0
# 294 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	special DoSpecialTrainerBattle
# 295 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitstate
# 296 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	copyvar VAR_0x8004, VAR_FRONTIER_BATTLE_MODE
# 297 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_0x8004, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerBattleRoom_EventScript_EndTowerBattle
# 298 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_restorehelditems
# 299 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	special HealPlayerParty
# 300 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_resetsketch
# 301 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_EndTowerBattle::
# 302 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_setinterviewdata
# 303 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
# 304 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 305 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 306 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_EventScript_SetBrainObjectGfx::
# 307 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	frontier_setbrainobj
# 308 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	return
# 309 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 310 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_PlayerEnter:
# 311 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 312 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 313 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 314 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	face_right
# 315 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 316 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 317 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceAttendant:
# 318 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	face_down
# 319 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 320 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 321 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceBattle:
# 322 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	face_right
# 323 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 324 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 325 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_OpponentEnter:
# 326 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_down
# 327 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_down
# 328 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_down
# 329 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_down
# 330 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	face_left
# 331 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 332 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 333 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_OpponentExit:
# 334 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 335 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 336 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 337 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 338 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 339 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 340 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_AttendantApproachPlayer:
# 341 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_right
# 342 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_right
# 343 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_right
# 344 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 345 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 346 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 347 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_AttendantReturnToPos:
# 348 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_down
# 349 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_left
# 350 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_left
# 351 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_left
# 352 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	face_right
# 353 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 354 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 355 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_SetInvisible:
# 356 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	set_invisible
# 357 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 358 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 359 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantEnter:
# 360 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	set_visible
# 361 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 362 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_up
# 363 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_left
# 364 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_left
# 365 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_8
# 366 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 367 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 368 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantExit:
# 369 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_right
# 370 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_right
# 371 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_down
# 372 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	set_invisible
# 373 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 374 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 375 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantDelay:
# 376 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 377 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 378 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 379 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 380 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 381 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 382 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_AttendantFaceSecondAttendant:
# 383 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	face_right
# 384 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 385 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 386 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 387 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	delay_16
# 388 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_in_place_right
# 389 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 390 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 391 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Movement_AnabelEnter:
# 392 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_slow_down
# 393 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_slow_down
# 394 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_slow_down
# 395 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	walk_slow_down
# 396 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	face_left
# 397 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	step_end
# 398 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 399 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobby::
# 400 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	copyvar VAR_RESULT, VAR_FRONTIER_BATTLE_MODE
# 401 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyDoubles
# 402 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyMultis
# 403 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto_if_eq VAR_RESULT, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyLinkMultis
# 404 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 6, 6
# 405 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitstate
# 406 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	end
# 407 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 408 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyDoubles::
# 409 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 10, 6
# 410 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitstate
# 411 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	end
# 412 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 413 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyMultis::
# 414 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 14, 6
# 415 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitstate
# 416 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	end
# 417 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 418 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyLinkMultis::
# 419 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	tower_closelink
# 420 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 18, 6
# 421 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	waitstate
# 422 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	end
# 423 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 424 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_EventScript_RetireChallenge::
# 425 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	setflag FLAG_CANCEL_BATTLE_ROOM_CHALLENGE
# 426 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
# 427 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	end
# 428 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 429 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_RestoreMonsToFullHealth:
# 430 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "We will restore your POKéMON to\n"
# 431 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "full health.$"
# 432 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 433 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
@ Unused
# 434 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyForOpponent:
# 435 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent no. {STR_VAR_1}.\n"
# 436 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you ready?$"
# 437 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 438 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent:
# 439 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent no. 2.\n"
# 440 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you ready?$"
# 441 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 442 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor3rdOpponent:
# 443 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent no. 3.\n"
# 444 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you ready?$"
# 445 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 446 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor4thOpponent:
# 447 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent no. 4.\n"
# 448 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you ready?$"
# 449 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 450 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor5thOpponent:
# 451 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent no. 5.\n"
# 452 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you ready?$"
# 453 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 454 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor6thOpponent:
# 455 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent no. 6.\n"
# 456 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you ready?$"
# 457 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 458 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor7thOpponent:
# 459 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent no. 7.\n"
# 460 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you ready?$"
# 461 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 462 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_RecordYourBattle:
# 463 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Record your battle on your\n"
# 464 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "FRONTIER PASS?$"
# 465 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 466 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_BattleRecordedOnPass:
# 467 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "{PLAYER}'s battle was recorded\n"
# 468 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "on the FRONTIER PASS.$"
# 469 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 470 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_SaveAndQuitGame:
# 471 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Would you like to save and\n"
# 472 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "quit the game?$"
# 473 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 474 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_SavingPleaseWait:
# 475 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Saving your battle data.\n"
# 476 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Please wait.$"
# 477 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 478 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_CancelYourChallenge:
# 479 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Would you like to cancel your BATTLE\n"
# 480 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "ROOM challenge?$"
# 481 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 482 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_RecordCouldntBeSaved::
# 483 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "There was an error of some sort.\n"
# 484 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Your record could not be saved.$"
# 485 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 486 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_SalonMaidenOnHerWay:
# 487 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Excuse me, but…\p"
# 488 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Our leader, the SALON MAIDEN, is on\n"
# 489 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "her way here in hopes of battling you.\p"
# 490 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "She should be arriving very shortly.$"
# 491 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 492 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReadyForSalonMaiden:
# 493 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing the SALON MAIDEN.\n"
# 494 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Are you prepared?$"
# 495 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 496 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_GreetingsImAnabel:
# 497 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Greetings…\n"
# 498 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "My name is ANABEL.\p"
# 499 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "I am the SALON MAIDEN, and I am in\n"
# 500 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "charge of running the BATTLE TOWER…\p"
# 501 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "I have heard several rumors\n"
# 502 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "about you…\p"
# 503 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "In all honesty, what I have heard does\n"
# 504 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "not seem attractive in any way…\p"
# 505 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "The reason I've come to see you…\n"
# 506 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Well, there is but one reason…$"
# 507 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 508 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_LetMeSeeYourTalent:
# 509 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Let me see your talent in\n"
# 510 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "its entirety…$"
# 511 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 512 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_AnabelTalentShallBeRecognized:
# 513 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "ANABEL: Fufufu, nicely done…\p"
# 514 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Your FRONTIER PASS, please…\n"
# 515 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Your talent shall be recognized.$"
# 516 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 517 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_ReceivedAbilitySymbol:
# 518 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "The Ability Symbol was embossed on\n"
# 519 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "the FRONTIER PASS!$"
# 520 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 521 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_UntilNextTime:
# 522 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "… … … … … …\p"
# 523 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You have confidence in your POKéMON\n"
# 524 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "battling talent, don't you?\p"
# 525 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "I urge you to keep battling and\n"
# 526 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "keep on winning.\p"
# 527 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "I will be waiting for you.\n"
# 528 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Until the next time we meet…$"
# 529 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 530 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_AnabelYouCameBack:
# 531 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "ANABEL: You really did come back to\n"
# 532 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "see me…\p"
# 533 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "… … … … … …\p"
# 534 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You've won straight matches to see me…\n"
# 535 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "I won't have to hold back against you…\p"
# 536 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "It's been too long now…\p"
# 537 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Too long since I've been able to battle\n"
# 538 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "without thinking about anything…$"
# 539 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 540 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_LetsBeginShallWe:
# 541 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Let's begin, shall we?$"
# 542 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 543 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_AnabelCongratsYourPassPlease:
# 544 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "ANABEL: Fufu, congratulations…\n"
# 545 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "Your FRONTIER PASS, please…$"
# 546 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 547 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_AbilitySymbolTookGoldenShine:
# 548 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "The Ability Symbol took on\n"
# 549 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "a golden shine!$"
# 550 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"

# 551 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
BattleFrontier_BattleTowerBattleRoom_Text_WishICouldBattleYouAgain:
# 552 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "That was fun…\p"
# 553 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "I have never had a POKéMON battle\n"
# 554 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "so enjoyable before…\p"
# 555 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "I wish I could battle with you again…$"

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyForOpponent::
# 560 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	copyvar VAR_BATTLE_TOWER_STREAK, VAR_RESULT
# 561 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_RESULT
# 562 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyForOpponent_Text_0
	return


BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyForOpponent_Text_0:
# 562 "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory"
	.string "You will be facing opponent\nno. {STR_VAR_1}. Are you ready?$"
