# 1 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 2 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_MapScripts::
# 3 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerLobby_OnResume
# 4 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerLobby_OnTransition
# 5 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerLobby_OnFrame
# 6 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerLobby_OnWarp
# 7 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.byte 0
# 8 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 9 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_OnResume:
# 10 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special TryHideBattleTowerReporter
# 11 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 12 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 13 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_OnTransition:
# 14 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_ShowOrHideReporter
# 15 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	apprentice_shouldcheckgone
# 16 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, FALSE, BattleFrontier_BattleTowerLobby_EventScript_ShowApprentice  @ VAR_0x8004 always TRUE here
# 17 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_set FLAG_DAILY_APPRENTICE_LEAVES, BattleFrontier_BattleTowerLobby_EventScript_HideApprentice
# 18 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowApprentice::
# 19 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	clearflag FLAG_HIDE_APPRENTICE
# 20 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	apprentice_setgfx
# 21 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_EndShowOrHideApprentice::
# 22 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 23 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 24 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_HideApprentice::
# 25 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setflag FLAG_HIDE_APPRENTICE
# 26 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndShowOrHideApprentice
# 27 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 28 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_OnWarp:
# 29 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerLobby_EventScript_PlayerFaceNorth
# 30 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte 0
# 31 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 32 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_PlayerFaceNorth::
# 33 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_1, 1
# 34 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	turnobject LOCALID_PLAYER, DIR_NORTH
# 35 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 36 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 37 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_OnFrame:
# 38 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleTowerLobby_EventScript_GetChallengeStatus
# 39 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleTowerLobby_EventScript_QuitWithoutSaving
# 40 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleTowerLobby_EventScript_ResumeChallenge
# 41 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleTowerLobby_EventScript_WonChallenge
# 42 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleTowerLobby_EventScript_LostChallenge
# 43 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte 0
# 44 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 45 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetChallengeStatus::
# 46 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_getstatus
# 47 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 48 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 49 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_QuitWithoutSaving::
# 50 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 51 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 52 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
# 53 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 54 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK, 0
# 55 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, FALSE
# 56 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 57 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 58 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 59 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 60 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 61 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_WonChallenge::
# 62 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 63 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 64 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_isbrain
# 65 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerLobby_EventScript_DefeatedMaiden
# 66 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_CongratsBeatenSeven
# 67 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 68 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_GiveRibbons
# 69 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 70 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DefeatedMaiden::
# 71 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_CongratsDefeatedMaiden, MSGBOX_DEFAULT
# 72 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GiveRibbons::
# 73 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_giveribbons
# 74 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleTowerLobby_EventScript_GiveBattlePoints
# 75 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_HereAreSomeRibbons
# 76 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 77 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 78 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitfanfare
# 79 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PutRibbonOnMons, MSGBOX_DEFAULT
# 80 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GiveBattlePoints::
# 81 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_AwardYouTheseBattlePoints, MSGBOX_DEFAULT
# 82 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_givepoints
# 83 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
# 84 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_AskSaveBattle
# 85 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_get TOWER_DATA_WIN_STREAK
# 86 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_ne VAR_RESULT, 49, BattleFrontier_BattleTowerLobby_EventScript_LookForwardToChallenge
# 87 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_AboutToFace50thTrainer, MSGBOX_DEFAULT
# 88 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LookForwardToChallenge::
# 89 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge, MSGBOX_DEFAULT
# 90 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 91 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 92 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 93 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 94 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 95 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 96 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LostChallenge::
# 97 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_ne VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_CancelWinStreak
# 98 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerLobby_EventScript_CancelWinStreak
# 99 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_get TOWER_DATA_WIN_STREAK
# 100 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_ne VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LostThanksForPlaying
# 101 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CancelWinStreak::
# 102 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, FALSE
# 103 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BATTLE_TOWER_STREAK, 0
# 104 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LostThanksForPlaying::
# 105 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 106 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 107 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_ThankYouForPlaying
# 108 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 109 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_AskSaveBattle
# 110 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge, MSGBOX_DEFAULT
# 111 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 112 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 113 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 114 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 115 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 116 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 117 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskSaveBattle::
# 118 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_RecordWillBeSaved
# 119 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 120 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkairshow
# 121 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 122 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special HealPlayerParty
# 123 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save 0
# 124 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playse SE_SAVE
# 125 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitse
# 126 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetCantRecordBattle
# 127 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle
# 128 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_RecordLastMatch
# 129 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 130 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
# 131 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 132 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle
# 133 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_EventScript_SaveBattle
# 134 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle
# 135 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 136 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_EventScript_SaveBattle::
# 137 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_savebattle
# 138 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_EventScript_BattleSaveFailed
# 139 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playse SE_SAVE
# 140 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_BattleRecordedOnPass, MSGBOX_DEFAULT
# 141 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle
# 142 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 143 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_EventScript_BattleSaveFailed::
# 144 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_RecordCouldntBeSaved, MSGBOX_DEFAULT
# 145 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle::
# 146 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 147 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 148 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_EventScript_GetCantRecordBattle::
# 149 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_get FRONTIER_DATA_RECORD_DISABLED
# 150 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 151 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 152 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ResumeChallenge::
# 153 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 154 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 155 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_SetBravoTrainerOn
# 156 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WeveBeenWaitingForYou
# 157 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 158 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_ProgressWillBeSaved
# 159 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 160 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save CHALLENGE_STATUS_SAVING
# 161 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playse SE_SAVE
# 162 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitse
# 163 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 164 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 165 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 166 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 167 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SetBravoTrainerOn::
# 168 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, TRUE
# 169 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 170 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 171 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SinglesAttendant::
# 172 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 173 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 174 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
# 175 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 176 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomSingleBattle, MSGBOX_DEFAULT
# 177 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskEnterSinglesChallenge::
# 178 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_TakeSinglesChallenge
# 179 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 180 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 181 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 182 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge
# 183 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainSinglesChallenge
# 184 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 185 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 186 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 187 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge::
# 188 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
# 189 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
# 190 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 191 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 2, MULTI_LEVEL_MODE, FALSE
# 192 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 193 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleFrontier_BattleTowerLobby_EventScript_SinglesInnates
# 194 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_SinglesLevelInfo
# 195 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_SinglesBgm
# 196 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 197 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 198 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 199 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 200 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
# 201 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 202 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 203 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 204 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 205 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
# 206 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 207 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 208 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 209 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 210 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 211 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 212 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeSinglesChallenge
# 213 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 214 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 215 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SinglesLevelInfo::
# 216 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 217 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge
# 218 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 219 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SinglesInnates::
# 220 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 221 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge
# 222 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 223 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SinglesBgm::
# 224 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 225 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge
# 226 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 227 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeSinglesChallenge::
# 228 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 229 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 230 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 231 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 232 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 233 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 234 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 235 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 236 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 237 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 238 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 239 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 240 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, TRUE
# 241 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 242 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 243 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 244 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainSinglesChallenge::
# 245 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
# 246 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterSinglesChallenge
# 247 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 248 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 249 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DoublesAttendant::
# 250 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 251 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 252 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
# 253 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 254 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeDoubleBattle, MSGBOX_DEFAULT
# 255 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskEnterDoublesChallenge::
# 256 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_TakeDoublesChallenge
# 257 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 258 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 259 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 260 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
# 261 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainDoublesChallenge
# 262 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 263 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 264 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 265 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge::
# 266 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
# 267 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
# 268 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 269 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 2, MULTI_LEVEL_MODE, FALSE
# 270 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 271 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleFrontier_BattleTowerLobby_EventScript_DoublesInnates
# 272 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_DoublesLevelInfo
# 273 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_DoublesBgm
# 274 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 275 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 276 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 277 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 278 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectFourMons, MSGBOX_DEFAULT
# 279 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 280 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 281 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 282 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 283 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_DOUBLES_PARTY_SIZE
# 284 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 285 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 286 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 287 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 288 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 289 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 290 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeDoublesChallenge
# 291 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 292 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 293 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DoublesLevelInfo::
# 294 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 295 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
# 296 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 297 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DoublesInnates::
# 298 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 299 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
# 300 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 301 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DoublesBgm::
# 302 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 303 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
# 304 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 305 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeDoublesChallenge::
# 306 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 307 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 308 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 309 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 310 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 311 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 312 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 313 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 314 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 315 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 316 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 317 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 318 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 319 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 320 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 321 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 322 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainDoublesChallenge::
# 323 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
# 324 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterDoublesChallenge
# 325 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 326 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 327 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_MultisAttendant::
# 328 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 329 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 330 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
# 331 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	clearflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
# 332 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 333 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeMultiBattle, MSGBOX_DEFAULT
# 334 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskEnterMultisChallenge::
# 335 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_TakeMultisChallenge
# 336 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 337 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 338 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 339 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
# 340 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainMultisChallenge
# 341 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 342 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 343 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 344 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge::
# 345 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS
# 346 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
# 347 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 348 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 2, MULTI_LEVEL_MODE, FALSE
# 349 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 350 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleFrontier_BattleTowerLobby_EventScript_MultisInnates
# 351 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_MultisLevelInfo
# 352 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_MultisBgm
# 353 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 354 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 355 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 356 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 357 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons, MSGBOX_DEFAULT
# 358 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 359 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 360 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 361 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 362 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 363 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 364 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 365 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 366 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 367 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 368 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 369 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeMultisChallenge
# 370 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 371 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 372 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_MultisLevelInfo::
# 373 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 374 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
# 375 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 376 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_MultisInnates::
# 377 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 378 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
# 379 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 380 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_MultisBgm::
# 381 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 382 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
# 383 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 384 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeMultisChallenge::
# 385 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 386 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 387 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 388 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 389 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 390 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 391 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 392 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 393 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 394 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 395 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 396 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 397 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 398 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 399 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 400 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 401 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainMultisChallenge::
# 402 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMultisChallenge, MSGBOX_DEFAULT
# 403 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterMultisChallenge
# 404 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 405 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 406 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkMultisAttendant::
# 407 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 408 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 409 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
# 410 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 411 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeLinkMultiBattle, MSGBOX_DEFAULT
# 412 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskEnterLinkMultisChallenge::
# 413 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_TakeLinkMultisChallenge
# 414 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 415 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 416 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 417 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
# 418 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainLinkMultisChallenge
# 419 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 420 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 421 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 422 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge::
# 423 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
# 424 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
# 425 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 426 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 2, MULTI_LEVEL_MODE, FALSE
# 427 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 428 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleFrontier_BattleTowerLobby_EventScript_LinkMultisInnates
# 429 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_LinkMultisLevelInfo
# 430 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_LinkMultisBgm
# 431 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 432 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 433 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 434 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 435 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons2, MSGBOX_DEFAULT
# 436 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 437 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 438 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 439 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 440 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 441 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 442 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 443 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 444 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 445 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 446 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 447 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeLinkMultisChallenge
# 448 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 449 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 450 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkMultisLevelInfo::
# 451 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 452 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
# 453 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 454 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkMultisInnates::
# 455 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 456 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
# 457 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 458 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkMultisBgm::
# 459 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 460 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
# 461 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 462 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeLinkMultisChallenge::
# 463 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 464 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 465 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 466 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 467 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 468 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 469 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 470 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 471 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ The command tower_save ultimately calls TrySavingData(SAVE_LINK), which writes data in SaveBlock1 and SaveBlock2
# 472 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ to the flash, but not data in PokemonStorage. The SaveGame script that follows asks the player to do a full save,
# 473 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ which they can opt out of. As a result the player can save their party and quit without having saved the PC.
# 474 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ This allows players to clone pokemon and their held items by withdrawing them (or erase them by despositing).
# 475 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#ifndef BUGFIX
# 476 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save 0
# 477 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#endif
# 478 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 479 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 480 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 481 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ GAME_STAT_ENTERED_BATTLE_TOWER should not be incremented here, for two reasons:
# 482 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ 1. It is incremented again in BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful or BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
# 483 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ 2. If the player tries to connect, but fails, the counter will still be incremented even if the player never enters the tower.
# 484 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#ifndef BUGFIX
# 485 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 486 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#endif
# 487 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	specialvar VAR_RESULT, IsWirelessAdapterConnected
# 488 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink
# 489 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryCableLink
# 490 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 491 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 492 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsMan::
# 493 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 494 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 495 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_DescribeFeelingsAboutBattleTower
# 496 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 497 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 16, 4, MULTI_BATTLE_TOWER_FEELINGS, FALSE
# 498 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 499 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_FeelingsBattleNow
# 500 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_FeelingsIWon
# 501 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_FeelingsILost
# 502 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 3, BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell
# 503 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell
# 504 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 505 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 506 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 507 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsBattleNow::
# 508 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouBegin, MSGBOX_DEFAULT
# 509 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_START
# 510 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_ShowEasyChatScreen
# 511 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 512 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 513 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
# 514 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 515 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 516 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsIWon::
# 517 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveWon, MSGBOX_DEFAULT
# 518 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_WON
# 519 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_ShowEasyChatScreen
# 520 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 521 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 522 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
# 523 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 524 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 525 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsILost::
# 526 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveLost, MSGBOX_DEFAULT
# 527 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_LOST
# 528 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_ShowEasyChatScreen
# 529 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 530 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 531 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
# 532 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 533 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 534 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell::
# 535 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_DontThinkMuchAboutIt, MSGBOX_DEFAULT
# 536 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 537 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 538 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 539 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings::
# 540 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CanceledEasyChat
# 541 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattleTowerLobby_EventScript_SubmittedFeelings
# 542 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 543 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 544 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CanceledEasyChat::
# 545 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ChangedYourMind, MSGBOX_DEFAULT
# 546 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 547 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 548 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 549 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SubmittedFeelings::
# 550 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ThatsHowYouFeel, MSGBOX_DEFAULT
# 551 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 552 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 553 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 554 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_Woman::
# 555 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WinsInRowRecorded, MSGBOX_NPC
# 556 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 557 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 558 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_Boy::
# 559 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_CanLeaveUntilLossOrSevenWins, MSGBOX_NPC
# 560 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 561 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 562 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowSinglesResults::
# 563 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 564 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_SINGLES
# 565 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 566 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 567 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 568 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 569 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 570 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowDoublesResults::
# 571 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 572 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_DOUBLES
# 573 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 574 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 575 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 576 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 577 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 578 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowMultisResults::
# 579 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 580 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_MULTIS
# 581 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 582 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 583 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 584 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 585 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 586 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowLinkMultisResults::
# 587 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 588 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_LINK_MULTIS
# 589 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 590 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 591 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 592 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 593 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 594 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons::
# 595 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 596 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LVL_50, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50
# 597 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpen
# 598 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 599 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50::
# 600 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_FRONTIER_BATTLE_MODE
# 601 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Singles
# 602 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Doubles
# 603 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Multis, MSGBOX_DEFAULT
# 604 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 605 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 606 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 607 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 608 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 609 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Singles::
# 610 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Singles, MSGBOX_DEFAULT
# 611 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 612 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 613 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 614 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 615 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 616 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Doubles::
# 617 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Doubles, MSGBOX_DEFAULT
# 618 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 619 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 620 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 621 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 622 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 623 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpen::
# 624 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_FRONTIER_BATTLE_MODE
# 625 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenSingles
# 626 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenDoubles
# 627 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenMultis, MSGBOX_DEFAULT
# 628 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 629 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 630 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 631 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 632 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 633 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenSingles::
# 634 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenSingles, MSGBOX_DEFAULT
# 635 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 636 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 637 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 638 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 639 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 640 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenDoubles::
# 641 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenDoubles, MSGBOX_DEFAULT
# 642 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 643 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 644 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 645 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 646 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 647 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed::
# 648 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS  @ No status provided, so it relies on VAR_0x8006 being 0 already
# 649 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 650 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 651 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 652 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge::
# 653 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 654 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 655 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge::
# 656 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 657 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge, MSGBOX_DEFAULT
# 658 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge::
# 659 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 660 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 661 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 662 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_EnterElevator::
# 663 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 664 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, FRONTIER_UTIL_FUNC_SET_PARTY_ORDER
# 665 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_GetPartySize
# 666 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CallFrontierUtilFunc
# 667 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_RESULT, 0
# 668 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_WaitForLinkOpponentLoad::
# 669 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_loadlinkopponents
# 670 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 1
# 671 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_ne VAR_RESULT, 6, BattleFrontier_BattleTowerLobby_EventScript_WaitForLinkOpponentLoad
# 672 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_ShowYouToBattleRoom
# 673 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	clearflag FLAG_CANCEL_BATTLE_ROOM_CHALLENGE
# 674 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
# 675 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 676 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 677 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 678 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 679 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowYouToBattleRoom::
# 680 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_BufferModeText
# 681 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_ShowYouToLinkMultiBattleRoom
# 682 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom, MSGBOX_DEFAULT
# 683 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_WalkToElevator
# 684 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 685 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowYouToLinkMultiBattleRoom::
# 686 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	messageautoscroll BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom
# 687 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 688 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 48
# 689 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_WalkToElevator::
# 690 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 691 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_SetAttendantTalkedTo
# 692 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoord
# 693 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerLobby_Movement_WalkToElevator
# 694 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerLobby_Movement_WalkToElevator
# 695 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmovement 0
# 696 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	opendoor VAR_0x8004, 1
# 697 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitdooranim
# 698 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerLobby_Movement_AttendantEnterElevator
# 699 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerLobby_Movement_PlayerEnterElevator
# 700 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmovement 0
# 701 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closedoor VAR_0x8004, 1
# 702 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitdooranim
# 703 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 704 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 705 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_WalkToElevator:
# 706 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 707 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 708 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 709 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 710 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 711 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_AttendantEnterElevator:
# 712 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 713 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	set_invisible
# 714 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 715 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 716 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_PlayerEnterElevator:
# 717 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 718 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 719 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	set_invisible
# 720 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 721 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 722 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 723 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_UnusedEnterElevator:
# 724 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 725 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 726 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 727 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 728 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 729 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	set_invisible
# 730 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 731 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 732 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferModeText::
# 733 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_BufferTextSingle
# 734 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_BufferTextDouble
# 735 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_BufferTextMulti
# 736 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_BufferTextLinkMulti
# 737 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 738 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 739 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextSingle::
# 740 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
# 741 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 742 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 743 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextDouble::
# 744 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
# 745 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 746 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 747 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextMulti::
# 748 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
# 749 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 750 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 751 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextLinkMulti::
# 752 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
# 753 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 754 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 755 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SetAttendantTalkedTo::
# 756 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_TalkedToSinglesAttendant
# 757 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_TalkedToDoublesAttendant
# 758 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_TalkedToMultisAttendant
# 759 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_TalkedToLinkMultisAttendant
# 760 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 761 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 762 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToSinglesAttendant::
# 763 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_SINGLES
# 764 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 765 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 766 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToDoublesAttendant::
# 767 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_DOUBLES
# 768 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 769 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 770 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToMultisAttendant::
# 771 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_MULTIS
# 772 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 773 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 774 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToLinkMultisAttendant::
# 775 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_LINK_MULTIS
# 776 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 777 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 778 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoord::
# 779 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordSingles
# 780 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordDoubles
# 781 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordMultis
# 782 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordLinkMultis
# 783 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 784 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 785 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordSingles::
# 786 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 6
# 787 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 788 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 789 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordDoubles::
# 790 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 10
# 791 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 792 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 793 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordMultis::
# 794 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 14
# 795 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 796 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 797 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordLinkMultis::
# 798 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 18
# 799 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 800 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 801 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetPartySize::
# 802 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_GetSinglesPartySize
# 803 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoublesPartySize
# 804 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetMultisPartySize
# 805 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetLinkMultisPartySize
# 806 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 807 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 808 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetSinglesPartySize::
# 809 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
# 810 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 811 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 812 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoublesPartySize::
# 813 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_DOUBLES_PARTY_SIZE
# 814 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 815 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 816 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetMultisPartySize::
# 817 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 818 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 819 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 820 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetLinkMultisPartySize::
# 821 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 822 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 823 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 824 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_EventScript_GetLvlMode::
# 825 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_get FRONTIER_DATA_LVL_MODE
# 826 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 827 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 828 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryCableLink::
# 829 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, USING_BATTLE_TOWER
# 830 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message gText_PleaseWaitForLink
# 831 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 832 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, 0
# 833 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special TryBattleLinkup
# 834 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 835 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful
# 836 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, CableClub_EventScript_AbortLinkSomeoneNotReady
# 837 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, BattleFrontier_BattleTowerLobby_EventScript_AbortLinkDifferentSelections
# 838 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, BattleFrontier_BattleTowerLobby_EventScript_AbortLinkIncorrectNumberOfPlayers
# 839 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 840 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, CableClub_EventScript_AbortLinkConnectionError
# 841 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
# 842 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 843 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 844 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AbortLinkDifferentSelections::
# 845 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 846 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8005, 3, BattleFrontier_BattleTowerLobby_EventScript_FriendDifferentSelection
# 847 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox Text_PlayersMadeDifferentSelections, MSGBOX_DEFAULT
# 848 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 849 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 850 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 851 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendDifferentSelection::
# 852 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode, MSGBOX_DEFAULT
# 853 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode, MSGBOX_DEFAULT
# 854 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 855 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 856 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 857 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AbortLinkIncorrectNumberOfPlayers::
# 858 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_LinkMultiOnlyForTwoPlayers, MSGBOX_DEFAULT
# 859 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 860 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox CableClub_Text_IncorrectNumberOfParticipants, MSGBOX_DEFAULT
# 861 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 862 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 863 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 864 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AbortLink::
# 865 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 866 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_0x8005, 0, BattleFrontier_BattleTowerLobby_EventScript_FriendChoseDifferentLvlMode
# 867 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_0x8005, 1, BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMon
# 868 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_0x8005, 2, BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMons
# 869 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode, MSGBOX_DEFAULT
# 870 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 871 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 872 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 873 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendChoseDifferentLvlMode::
# 874 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode, MSGBOX_DEFAULT
# 875 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 876 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 877 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMon::
# 878 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMon, MSGBOX_DEFAULT
# 879 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 880 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 881 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMons::
# 882 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMons, MSGBOX_DEFAULT
# 883 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 884 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 885 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful::
# 886 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 887 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 888 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn
# 889 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 890 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save CHALLENGE_STATUS_SAVING
# 891 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SaveForBattleTowerLink
# 892 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 893 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleTowerLobby_EventScript_LinkFullSaveFailed
# 894 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playse SE_SAVE
# 895 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitse
# 896 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special TrySetBattleTowerLinkType
# 897 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 898 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 899 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 900 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainLinkMultisChallenge::
# 901 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainLinkMultisChallenge, MSGBOX_DEFAULT
# 902 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterLinkMultisChallenge
# 903 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 904 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 905 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink::
# 906 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, LINK_GROUP_BATTLE_TOWER
# 907 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
# 908 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 909 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 910 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader::
# 911 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message CableClub_Text_ChooseGroupLeaderOfTwo
# 912 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 913 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 16, 6, MULTI_LINK_LEADER, FALSE
# 914 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 915 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup
# 916 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader
# 917 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 918 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 919 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 920 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 921 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader::
# 922 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call CableClub_EventScript_TryBecomeLinkLeader
# 923 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
# 924 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
# 925 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader
# 926 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
# 927 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 928 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 929 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 930 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup::
# 931 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call CableClub_EventScript_TryJoinLinkGroup
# 932 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
# 933 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
# 934 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup
# 935 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
# 936 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 937 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 938 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 939 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful::
# 940 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 941 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 942 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn
# 943 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 944 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save CHALLENGE_STATUS_SAVING
# 945 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SaveForBattleTowerLink
# 946 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 947 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleTowerLobby_EventScript_LinkFullSaveFailed
# 948 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playse SE_SAVE
# 949 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitse
# 950 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 951 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 952 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 953 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkFullSaveFailed::
# 954 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8006, 0
# 955 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS
# 956 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 957 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_RecordCouldntBeSaved, MSGBOX_DEFAULT
# 958 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 959 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 960 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 961 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesBoard::
# 962 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 963 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_RulesAreListed, MSGBOX_DEFAULT
# 964 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 965 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 966 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 967 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard::
# 968 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_ReadWhichHeading
# 969 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 970 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 2, MULTI_BATTLE_TOWER_RULES, FALSE
# 971 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 972 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_RulesTower
# 973 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_RulesMons
# 974 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_RulesSalon
# 975 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 3, BattleFrontier_BattleTowerLobby_EventScript_RulesMultiLink
# 976 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 4, BattleFrontier_BattleTowerLobby_EventScript_ExitRules
# 977 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_ExitRules
# 978 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 979 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 980 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesTower::
# 981 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainTowerRules, MSGBOX_DEFAULT
# 982 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 983 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 984 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 985 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesMons::
# 986 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
# 987 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 988 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 989 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 990 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesSalon::
# 991 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainSalonRules, MSGBOX_DEFAULT
# 992 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 993 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 994 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 995 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesMultiLink::
# 996 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMultiLinkRules, MSGBOX_DEFAULT
# 997 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 998 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 999 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1000 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExitRules::
# 1001 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 1002 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 1003 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1004 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1005 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DirectYouToBattleRoom:
# 1006 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I'll direct you to your Battle Room now.$"
# 1007 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1008 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DidntSaveBeforeQuitting:
# 1009 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1010 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You didn't save before you quit your\n"
# 1011 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "challenge last time.\p"
# 1012 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Because of that, your challenge so far\n"
# 1013 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "has been disqualified. Sorry!$"
# 1014 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1015 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_CongratsBeatenSeven:
# 1016 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Congratulations!\n"
# 1017 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You've beaten all seven Trainers!\p"
# 1018 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 1019 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1020 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1021 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_EarnedFabulousPrize:
# 1022 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "For beating seven Trainers in a row,\n"
# 1023 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you have earned this fabulous prize!\p"
# 1024 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 1025 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1026 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ReceivedPrize:
# 1027 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} received the prize\n"
# 1028 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{STR_VAR_1}.$"
# 1029 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1030 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1031 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_BagFullMakeRoom:
# 1032 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Oh, your Bag appears to be full.\p"
# 1033 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please make room in your Bag, then come\n"
# 1034 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "see me.$"
# 1035 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1036 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ThankYouForPlaying:
# 1037 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Thank you for playing!\p"
# 1038 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 1039 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1040 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_RecordWillBeSaved:
# 1041 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your record will be saved.\n"
# 1042 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please wait.$"
# 1043 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1044 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WeveBeenWaitingForYou:
# 1045 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "We've been waiting for you!\p"
# 1046 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 1047 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1048 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ProgressWillBeSaved:
# 1049 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Before entering a Battle Room, your\n"
# 1050 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "progress will be saved. Please wait.$"
# 1051 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1052 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_AboutToFace50thTrainer:
# 1053 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You're finally about to face the\n"
# 1054 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "50th Trainer.\p"
# 1055 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "From here on, every time you beat seven\n"
# 1056 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Trainers in a row, your Pokémon will\l"
# 1057 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "receive a commemorative Ribbon.\p"
# 1058 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Good luck!$"
# 1059 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1060 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_HereAreSomeRibbons:
# 1061 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Here are some Ribbons for beating\n"
# 1062 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "seven tough Trainers in a row.\p"
# 1063 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} received some Ribbons!$"
# 1064 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1065 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PutRibbonOnMons:
# 1066 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} put the Ribbons on\n"
# 1067 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the challenger Pokémon.$"
# 1068 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1069 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DescribeFeelingsAboutBattleTower:
# 1070 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me, do you have a moment?\p"
# 1071 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Can you describe your feelings when\n"
# 1072 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you're about to begin a Battle Tower\l"
# 1073 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "match, or when you've either won or\l"
# 1074 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "lost a match?$"
# 1075 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1076 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouBegin:
# 1077 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Okay, what are your feelings when\n"
# 1078 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you're about to begin a match?$"
# 1079 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1080 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveWon:
# 1081 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "What do you feel when you've won\n"
# 1082 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "a match?$"
# 1083 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1084 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveLost:
# 1085 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Can I hear about your feelings when\n"
# 1086 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you have lost a match?$"
# 1087 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1088 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DontThinkMuchAboutIt:
# 1089 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Oh, so you don't think much about it?\n"
# 1090 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You're one cool customer.$"
# 1091 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1092 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ChangedYourMind:
# 1093 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Hunh? You changed your mind?\n"
# 1094 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I guess you're fickle.$"
# 1095 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1096 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ThatsHowYouFeel:
# 1097 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Okay, so that's how you feel?\n"
# 1098 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "That's quite original.\p"
# 1099 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Thanks!$"
# 1100 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1101 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WinsInRowRecorded:
# 1102 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The number of matches you win in a row\n"
# 1103 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is recorded.\p"
# 1104 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I'd better not get beaten in\n"
# 1105 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "an embarrassing way!$"
# 1106 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1107 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_CanLeaveUntilLossOrSevenWins:
# 1108 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Once you've entered the Battle Tower,\n"
# 1109 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you can't leave until you either lose\l"
# 1110 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "or you beat seven Trainers in a row.\p"
# 1111 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You'd best be certain that you're up\n"
# 1112 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to the challenge.$"
# 1113 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1114 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1115 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DoubleBattleRoomConstruction:
# 1116 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower\n"
# 1117 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Double Battle Corner!\p"
# 1118 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Unfortunately, the Battle Rooms\n"
# 1119 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are still under construction.\p"
# 1120 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please come back when the work\n"
# 1121 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is completed.$"
# 1122 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1123 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1124 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_MultiBattleRoomConstruction:
# 1125 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower\n"
# 1126 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battle Corner!\p"
# 1127 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Unfortunately, the Battle Rooms\n"
# 1128 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are still under construction.\p"
# 1129 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please come back when the work\n"
# 1130 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is completed.$"
# 1131 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1132 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge:
# 1133 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "We look forward to seeing you on\n"
# 1134 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "another challenge!$"
# 1135 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1136 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WhichLevelMode:
# 1137 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Room offers two levels\n"
# 1138 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "of challenge, Classic and Chaos.\l"
# 1139 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Which is your choice?$"
# 1140 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1141 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1142 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PleaseSelectMons:
# 1143 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please select the Pokémon you wish\n"
# 1144 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.$"
# 1145 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1146 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering:
# 1147 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Before entering a Battle Room, your\n"
# 1148 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "progress must be saved. Is that okay?$"
# 1149 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1150 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom:
# 1151 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I will now show you to the\n"
# 1152 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{STR_VAR_1} Battle Room.$"
# 1153 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1154 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_RecordLastMatch:
# 1155 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Shall I record your last Battle Tower\n"
# 1156 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "match on your Frontier Pass?$"
# 1157 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1158 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1159 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50:
# 1160 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1161 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have {STR_VAR_2} eligible Pokémon.\p"
# 1162 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have {STR_VAR_2} different Pokémon\n"
# 1163 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1164 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1165 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1166 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1167 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1168 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd:
# 1169 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please come see me when you are ready.$"
# 1170 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1171 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1172 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpen:
# 1173 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1174 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have {STR_VAR_2} eligible Pokémon.\p"
# 1175 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have {STR_VAR_2} different Pokémon\n"
# 1176 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1177 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1178 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1179 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1180 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1181 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Singles:
# 1182 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1183 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have three eligible Pokémon.\p"
# 1184 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have three different Pokémon\n"
# 1185 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1186 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1187 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1188 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1189 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1190 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenSingles:
# 1191 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1192 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have three eligible Pokémon.\p"
# 1193 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have three different Pokémon\n"
# 1194 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1195 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1196 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1197 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1198 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1199 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Doubles:
# 1200 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1201 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have four eligible Pokémon.\p"
# 1202 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have four different Pokémon\n"
# 1203 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1204 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1205 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1206 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1207 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1208 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenDoubles:
# 1209 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1210 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have four eligible Pokémon.\p"
# 1211 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have four different Pokémon\n"
# 1212 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1213 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1214 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1215 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1216 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1217 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Multis:
# 1218 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1219 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have two eligible Pokémon.\p"
# 1220 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have two different Pokémon\n"
# 1221 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1222 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1223 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1224 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1225 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1226 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenMultis:
# 1227 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1228 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have two eligible Pokémon.\p"
# 1229 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have two different Pokémon\n"
# 1230 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1231 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1232 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1233 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1234 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1235 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomSingleBattle:
# 1236 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1237 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1238 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1239 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Single\n"
# 1240 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1241 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1242 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeSinglesChallenge:
# 1243 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Single\n"
# 1244 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1245 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1246 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainSinglesChallenge:
# 1247 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Single Battle\n"
# 1248 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1249 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Single Battles with three Pokémon.\p"
# 1250 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There are many Single Battle Rooms\n"
# 1251 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the Battle Tower for team battles.\p"
# 1252 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In each of the Single Battle Rooms,\n"
# 1253 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "seven Trainers await your challenge.\p"
# 1254 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you manage to defeat all seven,\n"
# 1255 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will earn Battle Points.\p"
# 1256 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 1257 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "challenge, please save the game.\p"
# 1258 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you don't save before interrupting,\n"
# 1259 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will be disqualified.$"
# 1260 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1261 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_SelectThreeMons:
# 1262 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the three Pokémon\n"
# 1263 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1264 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1265 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomeDoubleBattle:
# 1266 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1267 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1268 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1269 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Double\n"
# 1270 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1271 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1272 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeDoublesChallenge:
# 1273 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Double\n"
# 1274 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1275 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1276 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainDoublesChallenge:
# 1277 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Double Battle\n"
# 1278 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1279 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Double Battles with four Pokémon.\p"
# 1280 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There are many Double Battle Rooms\n"
# 1281 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the Battle Tower for team battles.\p"
# 1282 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In each of the Double Battle Rooms,\n"
# 1283 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "seven Trainers await your challenge.\p"
# 1284 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you manage to defeat all seven,\n"
# 1285 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will earn Battle Points.\p"
# 1286 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 1287 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "challenge, please save the game.\p"
# 1288 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you don't save before interrupting,\n"
# 1289 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will be disqualified.$"
# 1290 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1291 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PleaseSelectFourMons:
# 1292 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the four Pokémon\n"
# 1293 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1294 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1295 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomeMultiBattle:
# 1296 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1297 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1298 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1299 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Multi\n"
# 1300 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1301 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1302 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeMultisChallenge:
# 1303 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Multi\n"
# 1304 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1305 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1306 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainMultisChallenge:
# 1307 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Multi Battle\n"
# 1308 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1309 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battles.\p"
# 1310 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "For Multi Battles, you must partner\n"
# 1311 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "with a Trainer in the Tower and enter\l"
# 1312 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "with two Pokémon each.\p"
# 1313 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Inside the Tower is a room named\n"
# 1314 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Battle Salon where you may meet\l"
# 1315 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "other Trainers.\p"
# 1316 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There, you must find a Trainer to act\n"
# 1317 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "as your partner in Multi Battles.\p"
# 1318 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Once you have partnered up, you will\n"
# 1319 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "be shown to a Multi Battle Room.\p"
# 1320 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In the Multi Battle Room, seven\n"
# 1321 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "tag teams await your challenge.\p"
# 1322 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you manage to defeat all seven\n"
# 1323 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "teams, you will earn Battle Points.\p"
# 1324 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 1325 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "challenge, please save the game.\p"
# 1326 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you don't save before interrupting,\n"
# 1327 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will be disqualified.$"
# 1328 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1329 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons:
# 1330 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the two Pokémon\n"
# 1331 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1332 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1333 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomeLinkMultiBattle:
# 1334 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1335 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1336 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1337 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Link Multi\n"
# 1338 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1339 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1340 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeLinkMultisChallenge:
# 1341 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Link Multi\n"
# 1342 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1343 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1344 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainLinkMultisChallenge:
# 1345 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Multi Battle\n"
# 1346 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1347 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battles with a friend.\p"
# 1348 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must link with your friend using\n"
# 1349 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Wireless Adapters or a Game Boy\l"
# 1350 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Advance Game Link cable.\p"
# 1351 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must partner with your friend and\n"
# 1352 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "enter two different kinds of Pokémon.\p"
# 1353 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There are many Multi Battle Rooms\n"
# 1354 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the Battle Tower for team battles.\p"
# 1355 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In a Multi Battle Room, seven\n"
# 1356 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "tag teams await you and your friend\l"
# 1357 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to make a tag-team challenge.\p"
# 1358 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you manage to defeat all seven\n"
# 1359 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "teams, you will earn Battle Points.\p"
# 1360 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please beware that unlike other Rooms,\n"
# 1361 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you may not interrupt your challenge.\p"
# 1362 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Once you start, you must battle seven\n"
# 1363 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battles in a row nonstop.$"
# 1364 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1365 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons2:
# 1366 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the two Pokémon\n"
# 1367 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1368 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1369 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1370 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ChoseSameMonAsFriend:
# 1371 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You have chosen the same kind of\n"
# 1372 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon as your friend.\p"
# 1373 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please choose two Pokémon different\n"
# 1374 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "from your friend's, match the level\l"
# 1375 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you wish to enter, and register again.$"
# 1376 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1377 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_LinkMultiOnlyForTwoPlayers:
# 1378 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Link Multi Battle Room challenge\n"
# 1379 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is only for two linked players.$"
# 1380 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1381 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMon:
# 1382 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected\n"
# 1383 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Pokémon {STR_VAR_1}.$"
# 1384 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1385 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMons:
# 1386 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected the\n"
# 1387 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon {STR_VAR_1} and {STR_VAR_2}.$"
# 1388 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1389 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode:
# 1390 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has chosen a different\n"
# 1391 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "battle level.$"
# 1392 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1393 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1394 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlModeSameMon:
# 1395 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has chosen a different\n"
# 1396 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "battle level.\p"
# 1397 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected\n"
# 1398 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Pokémon {STR_VAR_1}.$"
# 1399 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1400 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1401 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlModeSameMons:
# 1402 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has chosen a different\n"
# 1403 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "battle level.\p"
# 1404 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected the\n"
# 1405 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon {STR_VAR_1} and {STR_VAR_2}.$"
# 1406 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1407 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode:
# 1408 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please choose two Pokémon different\n"
# 1409 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "from your friend's, match the level\l"
# 1410 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you wish to enter, and register again.$"
# 1411 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1412 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn:
# 1413 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I will save the game before\n"
# 1414 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "showing you in. Please wait.$"
# 1415 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1416 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_CongratsDefeatedMaiden:
# 1417 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Congratulations!\n"
# 1418 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You defeated the Salon Maiden as\l"
# 1419 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "your 21st consecutive victory!$"
# 1420 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1421 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_AwardYouTheseBattlePoints:
# 1422 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In recognition of your infinite talent,\n"
# 1423 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "we award you these Battle Point(s).$"
# 1424 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1425 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_Text_ObtainedXBattlePoints:
# 1426 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} obtained {STR_VAR_1} Battle Point(s).$"
# 1427 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1428 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_RulesAreListed:
# 1429 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower rules are listed.$"
# 1430 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1431 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ReadWhichHeading:
# 1432 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Which heading do you want to read?$"
# 1433 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1434 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainTowerRules:
# 1435 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower is a facility where\n"
# 1436 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "four types of battles are waged--\l"
# 1437 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Single Battle, Double Battle, Multi\l"
# 1438 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle, and Link Multi Battle.\p"
# 1439 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "For each of these types, there are\n"
# 1440 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "separate Battle Rooms.\p"
# 1441 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please speak with a guide offering\n"
# 1442 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the type of battle you wish to enter.$"
# 1443 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1444 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainMonRules:
# 1445 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Depending on the Battle Room you are\n"
# 1446 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "entering, you will be required to take\l"
# 1447 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "a certain number of Pokémon.\p"
# 1448 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Single Battle mode requires\n"
# 1449 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "three Pokémon.\p"
# 1450 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Double Battle mode requires four,\n"
# 1451 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "and the Multi modes both require two.$"
# 1452 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1453 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainSalonRules:
# 1454 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Salon is where you must\n"
# 1455 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "find a partner to form a tag team for\l"
# 1456 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Multi Battle Room challenge.\p"
# 1457 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Choose the best partner for you by\n"
# 1458 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "examining other Trainers'\l"
# 1459 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon and their moves.\p"
# 1460 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You may choose a new tag partner\n"
# 1461 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "after winning seven straight matches.$"
# 1462 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1463 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainMultiLinkRules:
# 1464 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Link Multi Battle Mode is for two\n"
# 1465 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "friends to mount a challenge together.\p"
# 1466 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You and your friend must be linked with\n"
# 1467 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Wireless Adapters or a Gba Game Link\l"
# 1468 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "cable.\p"
# 1469 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must choose two Pokémon at\n"
# 1470 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the registration counter.\p"
# 1471 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "These Pokémon must be different\n"
# 1472 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "from those of your friend.\p"
# 1473 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You may not interrupt this challenge\n"
# 1474 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the middle, unlike other modes.$"

BattleTowerBPVendor1::
# 1478 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 1479 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 1480 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_0
# 1481 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bpmart BattleTowerBpMart1
# 1482 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_1
# 1483 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
	end


BattleTowerBPVendor2::
# 1488 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 1489 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 1490 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_0
# 1491 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bpmart BattleTowerBpMart2
# 1492 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_1
# 1493 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
	end


	.align 2
# 1497 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleTowerBpMart1:
# 1498 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_BOTTLE_CAP
# 1499 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_GOLD_BOTTLE_CAP
# 1500 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_EXP_CANDY_XL
# 1501 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CHOICE_BAND
# 1502 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CHOICE_SPECS
# 1503 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CHOICE_SCARF
# 1504 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_HP_UP_EX
# 1505 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_PROTEIN_EX
# 1506 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_IRON_EX
# 1507 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CARBOS_EX
# 1508 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ZINC_EX
# 1509 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CALCIUM_EX
# 1510 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_PP_MAX
	.2byte ITEM_NONE

	.align 2
# 1513 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleTowerBpMart2:
# 1514 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_DAMP_ROCK
# 1515 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_HEAT_ROCK
# 1516 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ICY_ROCK
# 1517 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_SMOOTH_ROCK
# 1518 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ELECTRIC_SEED
# 1519 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_PSYCHIC_SEED
# 1520 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_MISTY_SEED
# 1521 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_GRASSY_SEED
# 1522 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_LUCKY_EGG
# 1523 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ROOM_SERVICE
# 1524 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_BLUNDER_POLICY
# 1525 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_WEAKNESS_POLICY
# 1526 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_HEAVY_DUTY_BOOTS
	.2byte ITEM_NONE

TowerLobbyDude::
# 1530 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ZERAORA, TowerLobbyDude_2
TowerLobbyDude_1:
# 1541 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox TowerLobbyDude_Text_1, MSGBOX_NPC
	return

TowerLobbyDude_2:
# 1531 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	specialvar VAR_RESULT, HasBattleTowerStreakForZeraora
# 1532 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TowerLobbyDude_4
	goto TowerLobbyDude_1

TowerLobbyDude_4:
# 1533 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox TowerLobbyDude_Text_0, MSGBOX_NPC
	end


BattleTowerBPVendor1_Text_0:
# 1480 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome!$"

BattleTowerBPVendor1_Text_1:
# 1482 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Thanks!$"

TowerLobbyDude_Text_0:
# 1533 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There's been talk of a strange Pokémon\n"
	.string "lurking just outside the Tower.\p"
	.string "It seemed to be watching your\n"
	.string "impressive battles!$"

TowerLobbyDude_Text_1:
# 1541 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The battles seem to get tougher\n"
	.string "over time. They even allow\l"
	.string "legendaries in the Chaos mode.$"
