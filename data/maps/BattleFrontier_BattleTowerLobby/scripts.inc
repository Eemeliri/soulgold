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
	multichoice 17, 4, MULTI_LEVEL_MODE, FALSE
# 192 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 193 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_SinglesLevelInfo
# 194 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_SinglesBgm
# 195 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 196 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 197 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 198 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 199 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
# 200 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 201 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 202 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 203 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 204 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
# 205 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 206 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 207 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 208 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 209 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 210 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 211 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeSinglesChallenge
# 212 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 213 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 214 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SinglesLevelInfo::
# 215 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 216 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge
# 217 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 218 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SinglesBgm::
# 219 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 220 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge
# 221 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 222 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeSinglesChallenge::
# 223 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 224 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 225 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 226 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 227 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 228 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 229 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 230 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 231 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 232 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 233 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 234 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 235 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, TRUE
# 236 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 237 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 238 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 239 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainSinglesChallenge::
# 240 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
# 241 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterSinglesChallenge
# 242 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 243 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 244 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DoublesAttendant::
# 245 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 246 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 247 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
# 248 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 249 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeDoubleBattle, MSGBOX_DEFAULT
# 250 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskEnterDoublesChallenge::
# 251 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_TakeDoublesChallenge
# 252 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 253 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 254 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 255 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
# 256 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainDoublesChallenge
# 257 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 258 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 259 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 260 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge::
# 261 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
# 262 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
# 263 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 264 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 4, MULTI_LEVEL_MODE, FALSE
# 265 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 266 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_DoublesLevelInfo
# 267 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_DoublesBgm
# 268 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 269 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 270 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 271 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 272 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectFourMons, MSGBOX_DEFAULT
# 273 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 274 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 275 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 276 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 277 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_DOUBLES_PARTY_SIZE
# 278 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 279 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 280 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 281 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 282 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 283 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 284 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeDoublesChallenge
# 285 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 286 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 287 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DoublesLevelInfo::
# 288 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 289 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
# 290 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 291 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_DoublesBgm::
# 292 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 293 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
# 294 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 295 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeDoublesChallenge::
# 296 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 297 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 298 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 299 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 300 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 301 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 302 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 303 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 304 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 305 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 306 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 307 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 308 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 309 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 310 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 311 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 312 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainDoublesChallenge::
# 313 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
# 314 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterDoublesChallenge
# 315 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 316 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 317 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_MultisAttendant::
# 318 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 319 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 320 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
# 321 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	clearflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
# 322 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 323 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeMultiBattle, MSGBOX_DEFAULT
# 324 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskEnterMultisChallenge::
# 325 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_TakeMultisChallenge
# 326 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 327 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 328 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 329 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
# 330 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainMultisChallenge
# 331 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 332 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 333 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 334 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge::
# 335 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS
# 336 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
# 337 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 338 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 4, MULTI_LEVEL_MODE, FALSE
# 339 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 340 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_MultisLevelInfo
# 341 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_MultisBgm
# 342 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 343 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 344 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 345 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 346 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons, MSGBOX_DEFAULT
# 347 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 348 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 349 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 350 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 351 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 352 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 353 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 354 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 355 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 356 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 357 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 358 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeMultisChallenge
# 359 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 360 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 361 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_MultisLevelInfo::
# 362 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 363 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
# 364 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 365 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_MultisBgm::
# 366 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 367 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
# 368 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 369 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeMultisChallenge::
# 370 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 371 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 372 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 373 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 374 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 375 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 376 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 377 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 378 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 379 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 380 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 381 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 382 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 383 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 384 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 385 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 386 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainMultisChallenge::
# 387 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMultisChallenge, MSGBOX_DEFAULT
# 388 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterMultisChallenge
# 389 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 390 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 391 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkMultisAttendant::
# 392 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 393 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 394 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
# 395 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 396 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeLinkMultiBattle, MSGBOX_DEFAULT
# 397 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AskEnterLinkMultisChallenge::
# 398 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_TakeLinkMultisChallenge
# 399 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 400 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 401 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 402 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
# 403 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainLinkMultisChallenge
# 404 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 405 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 406 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 407 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge::
# 408 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
# 409 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
# 410 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 411 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 4, MULTI_LEVEL_MODE, FALSE
# 412 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 413 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleTowerLobby_EventScript_LinkMultisLevelInfo
# 414 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleTowerLobby_EventScript_LinkMultisBgm
# 415 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 416 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_checkineligible
# 417 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
# 418 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 419 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons2, MSGBOX_DEFAULT
# 420 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 421 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 422 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 423 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 424 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 425 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 426 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 427 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 428 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
# 429 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 430 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 431 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeLinkMultisChallenge
# 432 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
# 433 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 434 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkMultisLevelInfo::
# 435 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 436 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
# 437 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 438 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LinkMultisBgm::
# 439 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 440 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
# 441 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 442 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeLinkMultisChallenge::
# 443 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 444 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 445 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_init
# 446 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
# 447 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 448 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 449 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 450 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 2
# 451 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ The command tower_save ultimately calls TrySavingData(SAVE_LINK), which writes data in SaveBlock1 and SaveBlock2
# 452 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ to the flash, but not data in PokemonStorage. The SaveGame script that follows asks the player to do a full save,
# 453 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ which they can opt out of. As a result the player can save their party and quit without having saved the PC.
# 454 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ This allows players to clone pokemon and their held items by withdrawing them (or erase them by despositing).
# 455 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#ifndef BUGFIX
# 456 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save 0
# 457 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#endif
# 458 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 459 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 460 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
# 461 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ GAME_STAT_ENTERED_BATTLE_TOWER should not be incremented here, for two reasons:
# 462 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ 1. It is incremented again in BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful or BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
# 463 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ 2. If the player tries to connect, but fails, the counter will still be incremented even if the player never enters the tower.
# 464 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#ifndef BUGFIX
# 465 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 466 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
#endif
# 467 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	specialvar VAR_RESULT, IsWirelessAdapterConnected
# 468 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink
# 469 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryCableLink
# 470 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 471 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 472 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsMan::
# 473 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 474 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 475 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_DescribeFeelingsAboutBattleTower
# 476 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 477 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 16, 4, MULTI_BATTLE_TOWER_FEELINGS, FALSE
# 478 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 479 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_FeelingsBattleNow
# 480 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_FeelingsIWon
# 481 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_FeelingsILost
# 482 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 3, BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell
# 483 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell
# 484 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 485 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 486 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 487 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsBattleNow::
# 488 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouBegin, MSGBOX_DEFAULT
# 489 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_START
# 490 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_ShowEasyChatScreen
# 491 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 492 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 493 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
# 494 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 495 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 496 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsIWon::
# 497 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveWon, MSGBOX_DEFAULT
# 498 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_WON
# 499 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_ShowEasyChatScreen
# 500 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 501 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 502 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
# 503 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 504 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 505 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsILost::
# 506 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveLost, MSGBOX_DEFAULT
# 507 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_LOST
# 508 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call Common_ShowEasyChatScreen
# 509 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 510 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 511 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
# 512 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 513 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 514 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell::
# 515 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_DontThinkMuchAboutIt, MSGBOX_DEFAULT
# 516 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 517 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 518 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 519 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings::
# 520 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CanceledEasyChat
# 521 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattleTowerLobby_EventScript_SubmittedFeelings
# 522 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 523 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 524 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CanceledEasyChat::
# 525 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ChangedYourMind, MSGBOX_DEFAULT
# 526 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 527 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 528 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 529 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SubmittedFeelings::
# 530 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ThatsHowYouFeel, MSGBOX_DEFAULT
# 531 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 532 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 533 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 534 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_Woman::
# 535 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_WinsInRowRecorded, MSGBOX_NPC
# 536 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 537 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 538 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_Boy::
# 539 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_CanLeaveUntilLossOrSevenWins, MSGBOX_NPC
# 540 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 541 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 542 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowSinglesResults::
# 543 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 544 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_SINGLES
# 545 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 546 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 547 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 548 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 549 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 550 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowDoublesResults::
# 551 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 552 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_DOUBLES
# 553 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 554 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 555 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 556 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 557 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 558 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowMultisResults::
# 559 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 560 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_MULTIS
# 561 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 562 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 563 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 564 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 565 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 566 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowLinkMultisResults::
# 567 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 568 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_LINK_MULTIS
# 569 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitbuttonpress
# 570 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special RemoveRecordsWindow
# 571 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 572 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 573 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 574 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons::
# 575 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 576 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LVL_50, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50
# 577 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpen
# 578 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 579 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50::
# 580 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_FRONTIER_BATTLE_MODE
# 581 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Singles
# 582 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Doubles
# 583 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Multis, MSGBOX_DEFAULT
# 584 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 585 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 586 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 587 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 588 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 589 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Singles::
# 590 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Singles, MSGBOX_DEFAULT
# 591 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 592 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 593 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 594 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 595 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 596 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Doubles::
# 597 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Doubles, MSGBOX_DEFAULT
# 598 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 599 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 600 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 601 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 602 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 603 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpen::
# 604 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_FRONTIER_BATTLE_MODE
# 605 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenSingles
# 606 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenDoubles
# 607 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenMultis, MSGBOX_DEFAULT
# 608 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 609 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 610 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 611 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 612 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 613 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenSingles::
# 614 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenSingles, MSGBOX_DEFAULT
# 615 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 616 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 617 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 618 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 619 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 620 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenDoubles::
# 621 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenDoubles, MSGBOX_DEFAULT
# 622 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 623 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 624 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
# 625 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 626 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 627 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed::
# 628 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS  @ No status provided, so it relies on VAR_0x8006 being 0 already
# 629 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 630 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 631 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 632 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge::
# 633 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special LoadPlayerParty
# 634 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 635 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge::
# 636 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 637 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge, MSGBOX_DEFAULT
# 638 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge::
# 639 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 640 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 641 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 642 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_EnterElevator::
# 643 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SavePlayerParty
# 644 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, FRONTIER_UTIL_FUNC_SET_PARTY_ORDER
# 645 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_GetPartySize
# 646 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CallFrontierUtilFunc
# 647 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_RESULT, 0
# 648 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_WaitForLinkOpponentLoad::
# 649 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_loadlinkopponents
# 650 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 1
# 651 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_ne VAR_RESULT, 6, BattleFrontier_BattleTowerLobby_EventScript_WaitForLinkOpponentLoad
# 652 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_ShowYouToBattleRoom
# 653 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	clearflag FLAG_CANCEL_BATTLE_ROOM_CHALLENGE
# 654 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
# 655 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 656 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 657 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 658 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 659 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowYouToBattleRoom::
# 660 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_BufferModeText
# 661 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_ShowYouToLinkMultiBattleRoom
# 662 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom, MSGBOX_DEFAULT
# 663 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_WalkToElevator
# 664 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 665 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ShowYouToLinkMultiBattleRoom::
# 666 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	messageautoscroll BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom
# 667 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 668 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	delay 48
# 669 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_WalkToElevator::
# 670 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closemessage
# 671 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_SetAttendantTalkedTo
# 672 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoord
# 673 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerLobby_Movement_WalkToElevator
# 674 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerLobby_Movement_WalkToElevator
# 675 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmovement 0
# 676 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	opendoor VAR_0x8004, 1
# 677 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitdooranim
# 678 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerLobby_Movement_AttendantEnterElevator
# 679 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerLobby_Movement_PlayerEnterElevator
# 680 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmovement 0
# 681 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	closedoor VAR_0x8004, 1
# 682 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitdooranim
# 683 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 684 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 685 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_WalkToElevator:
# 686 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 687 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 688 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 689 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 690 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 691 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_AttendantEnterElevator:
# 692 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 693 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	set_invisible
# 694 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 695 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 696 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_PlayerEnterElevator:
# 697 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 698 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_up
# 699 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	set_invisible
# 700 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 701 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 702 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 703 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Movement_UnusedEnterElevator:
# 704 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 705 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 706 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 707 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 708 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	walk_fast_up
# 709 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	set_invisible
# 710 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	step_end
# 711 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 712 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferModeText::
# 713 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_BufferTextSingle
# 714 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_BufferTextDouble
# 715 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_BufferTextMulti
# 716 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_BufferTextLinkMulti
# 717 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 718 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 719 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextSingle::
# 720 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
# 721 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 722 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 723 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextDouble::
# 724 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
# 725 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 726 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 727 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextMulti::
# 728 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
# 729 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 730 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 731 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_BufferTextLinkMulti::
# 732 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
# 733 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 734 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 735 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_SetAttendantTalkedTo::
# 736 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_TalkedToSinglesAttendant
# 737 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_TalkedToDoublesAttendant
# 738 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_TalkedToMultisAttendant
# 739 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_TalkedToLinkMultisAttendant
# 740 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 741 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 742 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToSinglesAttendant::
# 743 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_SINGLES
# 744 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 745 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 746 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToDoublesAttendant::
# 747 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_DOUBLES
# 748 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 749 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 750 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToMultisAttendant::
# 751 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_MULTIS
# 752 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 753 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 754 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TalkedToLinkMultisAttendant::
# 755 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_TOWER_ATTENDANT_LINK_MULTIS
# 756 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 757 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 758 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoord::
# 759 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordSingles
# 760 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordDoubles
# 761 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordMultis
# 762 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordLinkMultis
# 763 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 764 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 765 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordSingles::
# 766 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 6
# 767 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 768 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 769 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordDoubles::
# 770 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 10
# 771 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 772 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 773 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordMultis::
# 774 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 14
# 775 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 776 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 777 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordLinkMultis::
# 778 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, 18
# 779 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 780 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 781 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetPartySize::
# 782 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_GetSinglesPartySize
# 783 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoublesPartySize
# 784 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetMultisPartySize
# 785 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetLinkMultisPartySize
# 786 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 787 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 788 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetSinglesPartySize::
# 789 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
# 790 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 791 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 792 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetDoublesPartySize::
# 793 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_DOUBLES_PARTY_SIZE
# 794 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 795 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 796 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetMultisPartySize::
# 797 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 798 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 799 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 800 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_GetLinkMultisPartySize::
# 801 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
# 802 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 803 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 804 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_EventScript_GetLvlMode::
# 805 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	frontier_get FRONTIER_DATA_LVL_MODE
# 806 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 807 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 808 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryCableLink::
# 809 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, USING_BATTLE_TOWER
# 810 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message gText_PleaseWaitForLink
# 811 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 812 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8005, 0
# 813 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special TryBattleLinkup
# 814 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 815 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful
# 816 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, CableClub_EventScript_AbortLinkSomeoneNotReady
# 817 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, BattleFrontier_BattleTowerLobby_EventScript_AbortLinkDifferentSelections
# 818 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, BattleFrontier_BattleTowerLobby_EventScript_AbortLinkIncorrectNumberOfPlayers
# 819 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 820 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, CableClub_EventScript_AbortLinkConnectionError
# 821 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
# 822 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 823 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 824 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AbortLinkDifferentSelections::
# 825 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 826 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_0x8005, 3, BattleFrontier_BattleTowerLobby_EventScript_FriendDifferentSelection
# 827 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox Text_PlayersMadeDifferentSelections, MSGBOX_DEFAULT
# 828 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 829 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 830 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 831 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendDifferentSelection::
# 832 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode, MSGBOX_DEFAULT
# 833 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode, MSGBOX_DEFAULT
# 834 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 835 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 836 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 837 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AbortLinkIncorrectNumberOfPlayers::
# 838 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_LinkMultiOnlyForTwoPlayers, MSGBOX_DEFAULT
# 839 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 840 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox CableClub_Text_IncorrectNumberOfParticipants, MSGBOX_DEFAULT
# 841 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 842 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 843 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 844 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_AbortLink::
# 845 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special CloseLink
# 846 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_0x8005, 0, BattleFrontier_BattleTowerLobby_EventScript_FriendChoseDifferentLvlMode
# 847 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_0x8005, 1, BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMon
# 848 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call_if_eq VAR_0x8005, 2, BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMons
# 849 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode, MSGBOX_DEFAULT
# 850 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 851 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 852 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 853 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendChoseDifferentLvlMode::
# 854 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode, MSGBOX_DEFAULT
# 855 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 856 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 857 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMon::
# 858 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMon, MSGBOX_DEFAULT
# 859 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 860 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 861 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMons::
# 862 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMons, MSGBOX_DEFAULT
# 863 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 864 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 865 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful::
# 866 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 867 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 868 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn
# 869 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 870 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save CHALLENGE_STATUS_SAVING
# 871 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SaveForBattleTowerLink
# 872 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 873 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playse SE_SAVE
# 874 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitse
# 875 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special TrySetBattleTowerLinkType
# 876 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 877 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 878 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 879 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExplainLinkMultisChallenge::
# 880 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainLinkMultisChallenge, MSGBOX_DEFAULT
# 881 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterLinkMultisChallenge
# 882 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 883 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 884 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink::
# 885 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_0x8004, LINK_GROUP_BATTLE_TOWER
# 886 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
# 887 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 888 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 889 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader::
# 890 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message CableClub_Text_ChooseGroupLeaderOfTwo
# 891 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 892 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 16, 6, MULTI_LINK_LEADER, FALSE
# 893 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 894 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup
# 895 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader
# 896 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 897 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
# 898 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 899 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 900 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader::
# 901 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call CableClub_EventScript_TryBecomeLinkLeader
# 902 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
# 903 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
# 904 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader
# 905 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
# 906 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 907 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 908 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 909 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup::
# 910 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	call CableClub_EventScript_TryJoinLinkGroup
# 911 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
# 912 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
# 913 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup
# 914 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
# 915 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
# 916 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	return
# 917 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 918 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful::
# 919 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
# 920 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
# 921 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn
# 922 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 923 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	tower_save CHALLENGE_STATUS_SAVING
# 924 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	special SaveForBattleTowerLink
# 925 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitstate
# 926 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	playse SE_SAVE
# 927 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitse
# 928 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
# 929 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 930 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 931 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesBoard::
# 932 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lockall
# 933 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_RulesAreListed, MSGBOX_DEFAULT
# 934 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 935 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 936 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 937 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard::
# 938 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	message BattleFrontier_BattleTowerLobby_Text_ReadWhichHeading
# 939 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	waitmessage
# 940 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	multichoice 17, 2, MULTI_BATTLE_TOWER_RULES, FALSE
# 941 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	switch VAR_RESULT
# 942 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 0, BattleFrontier_BattleTowerLobby_EventScript_RulesTower
# 943 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 1, BattleFrontier_BattleTowerLobby_EventScript_RulesMons
# 944 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 2, BattleFrontier_BattleTowerLobby_EventScript_RulesSalon
# 945 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 3, BattleFrontier_BattleTowerLobby_EventScript_RulesMultiLink
# 946 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case 4, BattleFrontier_BattleTowerLobby_EventScript_ExitRules
# 947 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_ExitRules
# 948 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 949 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 950 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesTower::
# 951 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainTowerRules, MSGBOX_DEFAULT
# 952 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 953 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 954 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 955 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesMons::
# 956 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
# 957 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 958 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 959 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 960 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesSalon::
# 961 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainSalonRules, MSGBOX_DEFAULT
# 962 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 963 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 964 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 965 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_RulesMultiLink::
# 966 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMultiLinkRules, MSGBOX_DEFAULT
# 967 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
# 968 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 969 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 970 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_EventScript_ExitRules::
# 971 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	releaseall
# 972 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	end
# 973 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 974 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 975 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DirectYouToBattleRoom:
# 976 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I'll direct you to your Battle Room now.$"
# 977 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 978 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DidntSaveBeforeQuitting:
# 979 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 980 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You didn't save before you quit your\n"
# 981 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "challenge last time.\p"
# 982 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Because of that, your challenge so far\n"
# 983 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "has been disqualified. Sorry!$"
# 984 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 985 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_CongratsBeatenSeven:
# 986 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Congratulations!\n"
# 987 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You've beaten all seven Trainers!\p"
# 988 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 989 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 990 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 991 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_EarnedFabulousPrize:
# 992 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "For beating seven Trainers in a row,\n"
# 993 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you have earned this fabulous prize!\p"
# 994 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 995 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 996 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ReceivedPrize:
# 997 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} received the prize\n"
# 998 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{STR_VAR_1}.$"
# 999 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1000 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1001 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_BagFullMakeRoom:
# 1002 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Oh, your Bag appears to be full.\p"
# 1003 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please make room in your Bag, then come\n"
# 1004 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "see me.$"
# 1005 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1006 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ThankYouForPlaying:
# 1007 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Thank you for playing!\p"
# 1008 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 1009 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1010 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_RecordWillBeSaved:
# 1011 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your record will be saved.\n"
# 1012 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please wait.$"
# 1013 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1014 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WeveBeenWaitingForYou:
# 1015 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "We've been waiting for you!\p"
# 1016 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "$"
# 1017 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1018 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ProgressWillBeSaved:
# 1019 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Before entering a Battle Room, your\n"
# 1020 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "progress will be saved. Please wait.$"
# 1021 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1022 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_AboutToFace50thTrainer:
# 1023 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You're finally about to face the\n"
# 1024 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "50th Trainer.\p"
# 1025 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "From here on, every time you beat seven\n"
# 1026 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Trainers in a row, your Pokémon will\l"
# 1027 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "receive a commemorative Ribbon.\p"
# 1028 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Good luck!$"
# 1029 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1030 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_HereAreSomeRibbons:
# 1031 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Here are some Ribbons for beating\n"
# 1032 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "seven tough Trainers in a row.\p"
# 1033 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} received some Ribbons!$"
# 1034 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1035 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PutRibbonOnMons:
# 1036 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} put the Ribbons on\n"
# 1037 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the challenger Pokémon.$"
# 1038 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1039 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DescribeFeelingsAboutBattleTower:
# 1040 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me, do you have a moment?\p"
# 1041 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Can you describe your feelings when\n"
# 1042 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you're about to begin a Battle Tower\l"
# 1043 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "match, or when you've either won or\l"
# 1044 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "lost a match?$"
# 1045 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1046 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouBegin:
# 1047 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Okay, what are your feelings when\n"
# 1048 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you're about to begin a match?$"
# 1049 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1050 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveWon:
# 1051 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "What do you feel when you've won\n"
# 1052 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "a match?$"
# 1053 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1054 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveLost:
# 1055 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Can I hear about your feelings when\n"
# 1056 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you have lost a match?$"
# 1057 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1058 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DontThinkMuchAboutIt:
# 1059 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Oh, so you don't think much about it?\n"
# 1060 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You're one cool customer.$"
# 1061 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1062 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ChangedYourMind:
# 1063 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Hunh? You changed your mind?\n"
# 1064 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I guess you're fickle.$"
# 1065 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1066 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ThatsHowYouFeel:
# 1067 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Okay, so that's how you feel?\n"
# 1068 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "That's quite original.\p"
# 1069 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Thanks!$"
# 1070 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1071 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WinsInRowRecorded:
# 1072 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The number of matches you win in a row\n"
# 1073 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is recorded.\p"
# 1074 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I'd better not get beaten in\n"
# 1075 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "an embarrassing way!$"
# 1076 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1077 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_CanLeaveUntilLossOrSevenWins:
# 1078 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Once you've entered the Battle Tower,\n"
# 1079 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you can't leave until you either lose\l"
# 1080 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "or you beat seven Trainers in a row.\p"
# 1081 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You'd best be certain that you're up\n"
# 1082 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to the challenge.$"
# 1083 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1084 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1085 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_DoubleBattleRoomConstruction:
# 1086 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower\n"
# 1087 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Double Battle Corner!\p"
# 1088 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Unfortunately, the Battle Rooms\n"
# 1089 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are still under construction.\p"
# 1090 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please come back when the work\n"
# 1091 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is completed.$"
# 1092 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1093 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1094 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_MultiBattleRoomConstruction:
# 1095 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower\n"
# 1096 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battle Corner!\p"
# 1097 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Unfortunately, the Battle Rooms\n"
# 1098 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are still under construction.\p"
# 1099 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please come back when the work\n"
# 1100 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is completed.$"
# 1101 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1102 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge:
# 1103 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "We look forward to seeing you on\n"
# 1104 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "another challenge!$"
# 1105 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1106 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WhichLevelMode:
# 1107 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Room offers two levels\n"
# 1108 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "of challenge, Classic and Chaos.\l"
# 1109 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Which is your choice?$"
# 1110 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1111 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1112 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PleaseSelectMons:
# 1113 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please select the Pokémon you wish\n"
# 1114 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.$"
# 1115 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1116 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering:
# 1117 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Before entering a Battle Room, your\n"
# 1118 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "progress must be saved. Is that okay?$"
# 1119 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1120 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom:
# 1121 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I will now show you to the\n"
# 1122 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{STR_VAR_1} Battle Room.$"
# 1123 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1124 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_RecordLastMatch:
# 1125 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Shall I record your last Battle Tower\n"
# 1126 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "match on your Frontier Pass?$"
# 1127 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1128 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1129 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50:
# 1130 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1131 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have {STR_VAR_2} eligible Pokémon.\p"
# 1132 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have {STR_VAR_2} different Pokémon\n"
# 1133 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1134 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1135 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1136 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1137 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1138 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsEnd:
# 1139 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please come see me when you are ready.$"
# 1140 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1141 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1142 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpen:
# 1143 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1144 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have {STR_VAR_2} eligible Pokémon.\p"
# 1145 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have {STR_VAR_2} different Pokémon\n"
# 1146 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1147 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1148 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1149 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1150 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1151 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Singles:
# 1152 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1153 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have three eligible Pokémon.\p"
# 1154 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have three different Pokémon\n"
# 1155 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1156 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1157 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1158 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1159 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1160 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenSingles:
# 1161 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1162 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have three eligible Pokémon.\p"
# 1163 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have three different Pokémon\n"
# 1164 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1165 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1166 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1167 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1168 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1169 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Doubles:
# 1170 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1171 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have four eligible Pokémon.\p"
# 1172 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have four different Pokémon\n"
# 1173 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1174 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1175 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1176 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1177 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1178 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenDoubles:
# 1179 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1180 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have four eligible Pokémon.\p"
# 1181 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have four different Pokémon\n"
# 1182 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1183 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1184 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1185 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1186 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1187 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Multis:
# 1188 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1189 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have two eligible Pokémon.\p"
# 1190 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have two different Pokémon\n"
# 1191 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1192 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1193 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1194 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1195 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1196 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenMultis:
# 1197 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Excuse me!\p"
# 1198 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You don't have two eligible Pokémon.\p"
# 1199 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must have two different Pokémon\n"
# 1200 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to enter.\p"
# 1201 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "They also must be holding different\n"
# 1202 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "kinds of items.\p"
# 1203 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 1204 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1205 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomSingleBattle:
# 1206 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1207 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1208 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1209 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Single\n"
# 1210 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1211 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1212 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeSinglesChallenge:
# 1213 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Single\n"
# 1214 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1215 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1216 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainSinglesChallenge:
# 1217 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Single Battle\n"
# 1218 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1219 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Single Battles with three Pokémon.\p"
# 1220 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There are many Single Battle Rooms\n"
# 1221 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the Battle Tower for team battles.\p"
# 1222 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In each of the Single Battle Rooms,\n"
# 1223 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "seven Trainers await your challenge.\p"
# 1224 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you manage to defeat all seven,\n"
# 1225 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will earn Battle Points.\p"
# 1226 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 1227 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "challenge, please save the game.\p"
# 1228 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you don't save before interrupting,\n"
# 1229 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will be disqualified.$"
# 1230 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1231 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_SelectThreeMons:
# 1232 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the three Pokémon\n"
# 1233 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1234 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1235 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomeDoubleBattle:
# 1236 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1237 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1238 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1239 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Double\n"
# 1240 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1241 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1242 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeDoublesChallenge:
# 1243 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Double\n"
# 1244 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1245 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1246 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainDoublesChallenge:
# 1247 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Double Battle\n"
# 1248 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1249 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Double Battles with four Pokémon.\p"
# 1250 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There are many Double Battle Rooms\n"
# 1251 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the Battle Tower for team battles.\p"
# 1252 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In each of the Double Battle Rooms,\n"
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
BattleFrontier_BattleTowerLobby_Text_PleaseSelectFourMons:
# 1262 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the four Pokémon\n"
# 1263 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1264 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1265 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomeMultiBattle:
# 1266 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1267 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1268 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1269 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Multi\n"
# 1270 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1271 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1272 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeMultisChallenge:
# 1273 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Multi\n"
# 1274 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1275 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1276 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainMultisChallenge:
# 1277 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Multi Battle\n"
# 1278 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1279 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battles.\p"
# 1280 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "For Multi Battles, you must partner\n"
# 1281 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "with a Trainer in the Tower and enter\l"
# 1282 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "with two Pokémon each.\p"
# 1283 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Inside the Tower is a room named\n"
# 1284 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Battle Salon where you may meet\l"
# 1285 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "other Trainers.\p"
# 1286 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There, you must find a Trainer to act\n"
# 1287 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "as your partner in Multi Battles.\p"
# 1288 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Once you have partnered up, you will\n"
# 1289 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "be shown to a Multi Battle Room.\p"
# 1290 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In the Multi Battle Room, seven\n"
# 1291 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "tag teams await your challenge.\p"
# 1292 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you manage to defeat all seven\n"
# 1293 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "teams, you will earn Battle Points.\p"
# 1294 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 1295 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "challenge, please save the game.\p"
# 1296 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you don't save before interrupting,\n"
# 1297 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you will be disqualified.$"
# 1298 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1299 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons:
# 1300 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the two Pokémon\n"
# 1301 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1302 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1303 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_WelcomeLinkMultiBattle:
# 1304 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Where the talents of Trainers\n"
# 1305 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "are put to the test!\p"
# 1306 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome to the Battle Tower!\p"
# 1307 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I am your guide to the Link Multi\n"
# 1308 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Rooms.$"
# 1309 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1310 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_TakeLinkMultisChallenge:
# 1311 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Would you like to take the Link Multi\n"
# 1312 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle Room challenge?$"
# 1313 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1314 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainLinkMultisChallenge:
# 1315 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower's Multi Battle\n"
# 1316 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Rooms are facilities for conducting\l"
# 1317 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battles with a friend.\p"
# 1318 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must link with your friend using\n"
# 1319 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Wireless Adapters or a Game Boy\l"
# 1320 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Advance Game Link cable.\p"
# 1321 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must partner with your friend and\n"
# 1322 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "enter two different kinds of Pokémon.\p"
# 1323 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There are many Multi Battle Rooms\n"
# 1324 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the Battle Tower for team battles.\p"
# 1325 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In a Multi Battle Room, seven\n"
# 1326 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "tag teams await you and your friend\l"
# 1327 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "to make a tag-team challenge.\p"
# 1328 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "If you manage to defeat all seven\n"
# 1329 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "teams, you will earn Battle Points.\p"
# 1330 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please beware that unlike other Rooms,\n"
# 1331 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you may not interrupt your challenge.\p"
# 1332 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Once you start, you must battle seven\n"
# 1333 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Multi Battles in a row nonstop.$"
# 1334 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1335 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons2:
# 1336 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Now please select the two Pokémon\n"
# 1337 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "that are to be entered.$"
# 1338 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1339 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1340 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ChoseSameMonAsFriend:
# 1341 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You have chosen the same kind of\n"
# 1342 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon as your friend.\p"
# 1343 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please choose two Pokémon different\n"
# 1344 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "from your friend's, match the level\l"
# 1345 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you wish to enter, and register again.$"
# 1346 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1347 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_LinkMultiOnlyForTwoPlayers:
# 1348 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Link Multi Battle Room challenge\n"
# 1349 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "is only for two linked players.$"
# 1350 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1351 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMon:
# 1352 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected\n"
# 1353 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Pokémon {STR_VAR_1}.$"
# 1354 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1355 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMons:
# 1356 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected the\n"
# 1357 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon {STR_VAR_1} and {STR_VAR_2}.$"
# 1358 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1359 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode:
# 1360 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has chosen a different\n"
# 1361 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "battle level.$"
# 1362 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1363 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1364 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlModeSameMon:
# 1365 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has chosen a different\n"
# 1366 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "battle level.\p"
# 1367 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected\n"
# 1368 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Pokémon {STR_VAR_1}.$"
# 1369 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1370 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
@ Unused
# 1371 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlModeSameMons:
# 1372 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has chosen a different\n"
# 1373 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "battle level.\p"
# 1374 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Your friend has also selected the\n"
# 1375 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon {STR_VAR_1} and {STR_VAR_2}.$"
# 1376 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1377 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode:
# 1378 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please choose two Pokémon different\n"
# 1379 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "from your friend's, match the level\l"
# 1380 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "you wish to enter, and register again.$"
# 1381 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1382 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn:
# 1383 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "I will save the game before\n"
# 1384 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "showing you in. Please wait.$"
# 1385 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1386 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_CongratsDefeatedMaiden:
# 1387 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Congratulations!\n"
# 1388 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You defeated the Salon Maiden as\l"
# 1389 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "your 21st consecutive victory!$"
# 1390 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1391 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_AwardYouTheseBattlePoints:
# 1392 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "In recognition of your infinite talent,\n"
# 1393 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "we award you these Battle Point(s).$"
# 1394 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1395 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_Text_ObtainedXBattlePoints:
# 1396 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "{PLAYER} obtained {STR_VAR_1} Battle Point(s).$"
# 1397 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1398 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_RulesAreListed:
# 1399 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower rules are listed.$"
# 1400 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1401 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ReadWhichHeading:
# 1402 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Which heading do you want to read?$"
# 1403 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1404 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainTowerRules:
# 1405 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Tower is a facility where\n"
# 1406 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "four types of battles are waged--\l"
# 1407 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Single Battle, Double Battle, Multi\l"
# 1408 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Battle, and Link Multi Battle.\p"
# 1409 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "For each of these types, there are\n"
# 1410 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "separate Battle Rooms.\p"
# 1411 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Please speak with a guide offering\n"
# 1412 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the type of battle you wish to enter.$"
# 1413 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1414 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainMonRules:
# 1415 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Depending on the Battle Room you are\n"
# 1416 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "entering, you will be required to take\l"
# 1417 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "a certain number of Pokémon.\p"
# 1418 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Single Battle mode requires\n"
# 1419 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "three Pokémon.\p"
# 1420 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Double Battle mode requires four,\n"
# 1421 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "and the Multi modes both require two.$"
# 1422 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1423 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainSalonRules:
# 1424 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Battle Salon is where you must\n"
# 1425 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "find a partner to form a tag team for\l"
# 1426 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the Multi Battle Room challenge.\p"
# 1427 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Choose the best partner for you by\n"
# 1428 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "examining other Trainers'\l"
# 1429 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Pokémon and their moves.\p"
# 1430 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You may choose a new tag partner\n"
# 1431 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "after winning seven straight matches.$"
# 1432 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"

# 1433 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleFrontier_BattleTowerLobby_Text_ExplainMultiLinkRules:
# 1434 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The Link Multi Battle Mode is for two\n"
# 1435 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "friends to mount a challenge together.\p"
# 1436 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You and your friend must be linked with\n"
# 1437 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Wireless Adapters or a Gba Game Link\l"
# 1438 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "cable.\p"
# 1439 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You must choose two Pokémon at\n"
# 1440 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "the registration counter.\p"
# 1441 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "These Pokémon must be different\n"
# 1442 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "from those of your friend.\p"
# 1443 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "You may not interrupt this challenge\n"
# 1444 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "in the middle, unlike other modes.$"

BattleTowerBPVendor1::
# 1448 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 1449 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 1450 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_0
# 1451 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bpmart BattleTowerBpMart1
# 1452 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_1
# 1453 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
	end


BattleTowerBPVendor2::
# 1458 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	lock
# 1459 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	faceplayer
# 1460 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_0
# 1461 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	bpmart BattleTowerBpMart2
# 1462 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox BattleTowerBPVendor1_Text_1
# 1463 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	release
	end


	.align 2
# 1467 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleTowerBpMart1:
# 1468 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_BOTTLE_CAP
# 1469 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_GOLD_BOTTLE_CAP
# 1470 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_EXP_CANDY_XL
# 1471 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CHOICE_BAND
# 1472 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CHOICE_SPECS
# 1473 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CHOICE_SCARF
# 1474 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_HP_UP_EX
# 1475 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_PROTEIN_EX
# 1476 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_IRON_EX
# 1477 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CARBOS_EX
# 1478 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ZINC_EX
# 1479 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_CALCIUM_EX
# 1480 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_PP_MAX
	.2byte ITEM_NONE

	.align 2
# 1483 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
BattleTowerBpMart2:
# 1484 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_DAMP_ROCK
# 1485 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_HEAT_ROCK
# 1486 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ICY_ROCK
# 1487 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_SMOOTH_ROCK
# 1488 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ELECTRIC_SEED
# 1489 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_PSYCHIC_SEED
# 1490 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_MISTY_SEED
# 1491 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_GRASSY_SEED
# 1492 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_LUCKY_EGG
# 1493 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_ROOM_SERVICE
# 1494 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_BLUNDER_POLICY
# 1495 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_WEAKNESS_POLICY
# 1496 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.2byte ITEM_HEAVY_DUTY_BOOTS
	.2byte ITEM_NONE

TowerLobbyDude::
# 1500 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ZERAORA, TowerLobbyDude_2
TowerLobbyDude_1:
# 1511 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox TowerLobbyDude_Text_1, MSGBOX_NPC
	return

TowerLobbyDude_2:
# 1501 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	specialvar VAR_RESULT, HasBattleTowerStreakForZeraora
# 1502 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TowerLobbyDude_4
	goto TowerLobbyDude_1

TowerLobbyDude_4:
# 1503 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	msgbox TowerLobbyDude_Text_0, MSGBOX_NPC
	end


BattleTowerBPVendor1_Text_0:
# 1450 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Welcome!$"

BattleTowerBPVendor1_Text_1:
# 1452 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "Thanks!$"

TowerLobbyDude_Text_0:
# 1503 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "There's been talk of a strange Pokémon\n"
	.string "lurking just outside the Tower.\p"
	.string "It seemed to be watching your\n"
	.string "impressive battles!$"

TowerLobbyDude_Text_1:
# 1511 "data/maps/BattleFrontier_BattleTowerLobby/scripts.pory"
	.string "The battles seem to get tougher\n"
	.string "over time. They even allow\l"
	.string "legendaries in the Chaos mode.$"
