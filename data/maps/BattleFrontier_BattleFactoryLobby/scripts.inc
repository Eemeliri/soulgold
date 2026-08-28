# 1 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 2 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_MapScripts::
# 3 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame
# 4 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp
# 5 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.byte 0
# 6 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 7 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_OnWarp:
# 8 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth
# 9 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte 0
# 10 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 11 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth::
# 12 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_1, 1
# 13 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	turnobject LOCALID_PLAYER, DIR_NORTH
# 14 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 15 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 16 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_OnFrame:
# 17 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus
# 18 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving
# 19 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge
# 20 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge
# 21 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge
# 22 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte 0
# 23 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 24 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus::
# 25 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_getstatus
# 26 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 27 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 28 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving::
# 29 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lockall
# 30 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
# 31 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	closemessage
# 32 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_setswapped
# 33 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
# 34 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_set FACTORY_DATA_WIN_STREAK, 0
# 35 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
# 36 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 37 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 38 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	releaseall
# 39 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 40 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 41 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge::
# 42 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lockall
# 43 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_isbrain
# 44 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead
# 45 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins, MSGBOX_DEFAULT
# 46 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 47 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints
# 48 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 49 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead::
# 50 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead, MSGBOX_DEFAULT
# 51 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 52 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints::
# 53 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints, MSGBOX_DEFAULT
# 54 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_givepoints
# 55 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
# 56 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave
# 57 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 58 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_checkairshow
# 59 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	special LoadPlayerParty
# 60 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 61 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_save 0
# 62 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	playse SE_SAVE
# 63 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitse
# 64 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
# 65 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	closemessage
# 66 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 67 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	releaseall
# 68 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 69 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 70 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge::
# 71 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lockall
# 72 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults
# 73 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 74 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_checkairshow
# 75 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	special LoadPlayerParty
# 76 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 77 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
# 78 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_save 0
# 79 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	playse SE_SAVE
# 80 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitse
# 81 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 82 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle::
# 83 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call BattleFrontier_EventScript_GetCantRecordBattle
# 84 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
# 85 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch
# 86 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 87 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
# 88 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	switch VAR_RESULT
# 89 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
# 90 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle
# 91 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
# 92 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 93 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle::
# 94 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call BattleFrontier_EventScript_SaveBattle
# 95 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle::
# 96 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
# 97 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	closemessage
# 98 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 99 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	releaseall
# 100 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 101 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 102 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge::
# 103 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lockall
# 104 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume
# 105 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 106 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_save CHALLENGE_STATUS_SAVING
# 107 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	playse SE_SAVE
# 108 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitse
# 109 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 110 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 111 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_0x8006, 2
# 112 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge
# 113 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 114 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant::
# 115 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lock
# 116 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	faceplayer
# 117 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
# 118 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
# 119 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
# 120 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 121 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 122 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant::
# 123 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
# 124 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
# 125 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
# 126 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 127 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 128 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_Attendant::
# 129 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	special SavePlayerParty
# 130 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle
# 131 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle
# 132 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge::
# 133 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge
# 134 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge
# 135 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 136 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 137 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	switch VAR_RESULT
# 138 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
# 139 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge
# 140 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
# 141 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
# 142 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 143 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge::
# 144 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode
# 145 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 146 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	multichoice 17, 2, MULTI_LEVEL_MODE, FALSE
# 147 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	switch VAR_RESULT
# 148 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleFrontier_BattleFactoryLobby_EventScript_Innates
# 149 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattleFactoryLobby_EventScript_LevelInfo
# 150 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattleFactoryLobby_EventScript_Bgm
# 151 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
# 152 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 153 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
# 154 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	switch VAR_RESULT
# 155 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
# 156 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge
# 157 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
# 158 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 159 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_LevelInfo::
# 160 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 161 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
# 162 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 163 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_Innates::
# 164 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 165 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
# 166 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 167 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_Bgm::
# 168 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 169 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
# 170 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 171 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge::
# 172 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 173 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_init
# 174 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
# 175 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
# 176 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 177 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	closemessage
# 178 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	delay 2
# 179 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 180 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 181 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed
# 182 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_0x8006, 0
# 183 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge::
# 184 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	special SavePlayerParty
# 185 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay, MSGBOX_DEFAULT
# 186 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	closemessage
# 187 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant
# 188 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant
# 189 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor
# 190 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor
# 191 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmovement 0
# 192 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM, 8, 13
# 193 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 194 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitstate
# 195 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 196 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 197 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant::
# 198 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_SINGLES
# 199 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 200 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 201 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant::
# 202 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_DOUBLES
# 203 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 204 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 205 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge::
# 206 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge
# 207 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge
# 208 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge
# 209 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 210 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed::
# 211 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 212 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
# 213 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 214 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge::
# 215 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	special LoadPlayerParty
# 216 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 217 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge::
# 218 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
# 219 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	release
# 220 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 221 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 222 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor:
# 223 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	walk_up
# 224 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	walk_up
# 225 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	walk_up
# 226 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	set_invisible
# 227 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	step_end
# 228 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 229 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor:
# 230 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	walk_up
# 231 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	walk_up
# 232 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	walk_up
# 233 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	walk_up
# 234 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	step_end
# 235 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 236 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle::
# 237 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
# 238 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 239 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 240 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle::
# 241 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
# 242 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 243 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 244 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge::
# 245 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge
# 246 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 247 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 248 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge::
# 249 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge
# 250 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 251 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 252 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge::
# 253 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
# 254 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 255 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 256 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge::
# 257 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
# 258 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	return
# 259 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 260 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults::
# 261 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lockall
# 262 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_SINGLES
# 263 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitbuttonpress
# 264 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	special RemoveRecordsWindow
# 265 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	releaseall
# 266 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 267 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 268 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults::
# 269 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lockall
# 270 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_DOUBLES
# 271 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitbuttonpress
# 272 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	special RemoveRecordsWindow
# 273 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	releaseall
# 274 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 275 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 276 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_Woman::
# 277 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves, MSGBOX_NPC
# 278 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 279 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 280 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_Camper::
# 281 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon, MSGBOX_NPC
# 282 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 283 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 284 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_Picnicker::
# 285 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lock
# 286 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons, MSGBOX_DEFAULT
# 287 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	release
# 288 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 289 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 290 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_FatMan::
# 291 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints, MSGBOX_NPC
# 292 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 293 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 294 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard::
# 295 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lockall
# 296 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed, MSGBOX_DEFAULT
# 297 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
# 298 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 299 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 300 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard::
# 301 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
# 302 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	waitmessage
# 303 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, FALSE
# 304 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	switch VAR_RESULT
# 305 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics
# 306 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner
# 307 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber
# 308 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes
# 309 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv
# 310 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
# 311 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
# 312 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 313 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 314 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics::
# 315 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
# 316 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
# 317 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 318 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 319 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner::
# 320 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
# 321 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
# 322 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 323 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 324 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber::
# 325 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
# 326 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
# 327 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 328 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 329 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes::
# 330 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules, MSGBOX_DEFAULT
# 331 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
# 332 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 333 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 334 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv::
# 335 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules, MSGBOX_DEFAULT
# 336 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
# 337 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 338 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 339 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_EventScript_ExitRules::
# 340 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	releaseall
# 341 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	end
# 342 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 343 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle:
# 344 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Where the intelligence of Trainers\n"
# 345 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "is put to the test!\p"
# 346 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Welcome to the Battle Factory!\p"
# 347 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I am your guide to the Battle Swap\n"
# 348 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Single Tournament.$"
# 349 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 350 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge:
# 351 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Would you like to take the Battle\n"
# 352 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Swap Single challenge?$"
# 353 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 354 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge:
# 355 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "The Battle Swap Single Tournament\n"
# 356 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "is a Single Battle competition using\l"
# 357 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "only rental Pokémon.\p"
# 358 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "First, you will be loaned three\n"
# 359 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Pokémon specifically for this event.\p"
# 360 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Using the supplied rental Pokémon,\n"
# 361 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "you must conduct a Single Battle.\p"
# 362 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "If you win, you are permitted to trade\n"
# 363 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "one of your rental Pokémon.\p"
# 364 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Repeat this cycle of battling and\n"
# 365 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "trading--if you win seven times in\l"
# 366 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "a row, you will earn Battle Points.\p"
# 367 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 368 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "challenge, please save the game.\p"
# 369 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "If you don't save, you will be\n"
# 370 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "disqualified from your challenge.$"
# 371 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 372 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit:
# 373 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "We look forward to your next visit.$"
# 374 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 375 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode:
# 376 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Which level do you wish to challenge?\n"
# 377 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Classic or Chaos?$"
# 378 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 379 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge:
# 380 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Before you begin your challenge,\n"
# 381 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I need to save the game. Is that okay?$"
# 382 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 383 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
@ Unused
# 384 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping:
# 385 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Okay, I will hold your Pokémon for\n"
# 386 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "safekeeping while you compete.$"
# 387 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 388 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_StepThisWay:
# 389 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Please step this way.$"
# 390 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 391 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults:
# 392 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Thank you for participating!\p"
# 393 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I will return your Pokémon in exchange\n"
# 394 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "for our rental Pokémon.\p"
# 395 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I must also save the event results.\n"
# 396 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Please wait.$"
# 397 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 398 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
@ Unused
# 399 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ReturnMons:
# 400 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I will return your Pokémon in exchange\n"
# 401 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "for our rental Pokémon.$"
# 402 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 403 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins:
# 404 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Congratulations! You've won seven\n"
# 405 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "straight Battle Swap matches!$"
# 406 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 407 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
@ Unused
# 408 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_AwardBattlePointsForStreak:
# 409 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "In recognition of your 7-win streak,\n"
# 410 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "we award you these Battle Point(s).$"
# 411 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 412 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
@ Unused
# 413 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints:
# 414 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Oh, oh, oh!\p"
# 415 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Your Battle Points are maxed.\p"
# 416 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Please come back after using\n"
# 417 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "some Battle Points.$"
# 418 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 419 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume:
# 420 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "We've been waiting for you!\p"
# 421 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Before we resume your challenge,\n"
# 422 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I must save the game.$"
# 423 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 424 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting:
# 425 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I'm sorry to say this, but you didn't\n"
# 426 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "save before you quit playing last time.\p"
# 427 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "As a result, you have been disqualified\n"
# 428 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "from your challenge.$"
# 429 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 430 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
@ Unused
# 431 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_WellReturnMons:
# 432 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "We'll return your personal Pokémon.$"
# 433 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 434 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
@ Unused
# 435 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem:
# 436 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "{PLAYER} received the prize\n"
# 437 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "{STR_VAR_1}.$"
# 438 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 439 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle:
# 440 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Where the intelligence of Trainers\n"
# 441 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "is put to the test!\p"
# 442 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Welcome to the Battle Factory!\p"
# 443 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I am your guide to the Battle Swap\n"
# 444 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Double Tournament.$"
# 445 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 446 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge:
# 447 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Would you like to take the Battle\n"
# 448 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Swap Double challenge?$"
# 449 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 450 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge:
# 451 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "The Battle Swap Double Tournament\n"
# 452 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "is a Double Battle competition using\l"
# 453 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "only rental Pokémon.\p"
# 454 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "First, you will be loaned three\n"
# 455 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Pokémon specifically for this event.\p"
# 456 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Using the supplied rental Pokémon,\n"
# 457 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "you must conduct a Double Battle.\p"
# 458 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "If you win, you are permitted to trade\n"
# 459 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "one of your rental Pokémon.\p"
# 460 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Repeat this cycle of battling and\n"
# 461 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "trading--if you win seven times in\l"
# 462 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "a row, you will earn Battle Points.\p"
# 463 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 464 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "challenge, please save the game.\p"
# 465 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "If you don't save before interrupting,\n"
# 466 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "you will be disqualified.$"
# 467 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 468 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead:
# 469 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Congratulations for defeating\n"
# 470 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "the Factory Head and winning\l"
# 471 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "seven matches in a row!$"
# 472 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 473 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints:
# 474 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "In recognition of your wealth of\n"
# 475 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "knowledge and keen intelligence,\l"
# 476 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "we award you these Battle Point(s).$"
# 477 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 478 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave:
# 479 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Let me exchange your Pokémon\n"
# 480 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "for our rental Pokémon.\p"
# 481 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I need to save the battle data,\n"
# 482 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "so please wait.$"
# 483 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 484 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch:
# 485 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Would you like to record your last\n"
# 486 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Battle Factory match on your\l"
# 487 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Frontier Pass?$"
# 488 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 489 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves:
# 490 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Hi!\n"
# 491 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "You, there!\p"
# 492 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Are you thinking that the events here\n"
# 493 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "are easy since you don't need to have\l"
# 494 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "a raised team of Pokémon?\p"
# 495 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I wouldn't be too sure about winning\n"
# 496 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "that easily.\p"
# 497 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "If you don't have thorough knowledge\n"
# 498 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "about Pokémon and their moves,\l"
# 499 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "it will be tough to keep winning.$"
# 500 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 501 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon:
# 502 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I swapped for a weak Pokémon…\n"
# 503 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "I thought it was a good kind to have…\p"
# 504 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "They wiped the floor with us…$"
# 505 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 506 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons:
# 507 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Things haven't been going my way\n"
# 508 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "at all.\p"
# 509 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "You need to check your opponent's\n"
# 510 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Pokémon during battle to see if\l"
# 511 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "they're any good.$"
# 512 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 513 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints:
# 514 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "You know how the staff here give you\n"
# 515 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "a few hints about your next opponent?\p"
# 516 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Well, I'm a full-grown man, but I have\n"
# 517 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "trouble figuring out their hints.$"
# 518 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 519 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
@ Unused
# 520 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried:
# 521 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Like, I'm really tough, but I get bored\n"
# 522 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "really easily, so I just kept swapping\l"
# 523 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "and battling over and over.\p"
# 524 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "So anyway, when I kept entering\n"
# 525 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Battle Swap events, I noticed they\l"
# 526 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "varied the rental Pokémon.$"
# 527 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 528 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_RulesAreListed:
# 529 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "The Battle Swap rules are listed.$"
# 530 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 531 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading:
# 532 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Which heading do you want to read?$"
# 533 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 534 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules:
# 535 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "In a Battle Swap event, you may use\n"
# 536 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "only three Pokémon.\p"
# 537 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Whether you are renting or swapping,\n"
# 538 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "your team may not have two or more\l"
# 539 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "of the same Pokémon.$"
# 540 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 541 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules:
# 542 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "You may swap Pokémon only with\n"
# 543 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "the Trainer you have just defeated.\p"
# 544 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "You may swap for only those Pokémon\n"
# 545 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "used by the beaten Trainer.$"
# 546 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 547 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules:
# 548 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "After every battle you win, you may\n"
# 549 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "swap for one of your defeated\l"
# 550 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "opponent's Pokémon.\p"
# 551 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "You will not be able to swap Pokémon\n"
# 552 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "with the seventh Trainer in the event.$"
# 553 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 554 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules:
# 555 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "There are two key points to be aware\n"
# 556 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "of when swapping Pokémon.\p"
# 557 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "First, when swapping, you can't check\n"
# 558 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "the stats of the Pokémon you are\l"
# 559 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "about to receive.\p"
# 560 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Second, the Pokémon on your team\n"
# 561 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "are lined up in sequence, depending on\l"
# 562 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "the order in which you rented them.\p"
# 563 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "This sequence remains unchanged\n"
# 564 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "even when swaps are made.$"
# 565 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"

# 566 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules:
# 567 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "In Chaos, the rental Pokémon\n"
# 568 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "and the opposing Trainers' Pokémon\l"
# 569 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "are all Level 100.$"

FactoryBpLady::
# 573 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	lock
# 574 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	faceplayer
# 575 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox FactoryBpLady_Text_0
# 576 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	goto_if_set FLAG_BADGE08_GET, FactoryBpLady_2
# 579 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	bpmart FactoryBpMart
FactoryBpLady_1:
# 581 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	msgbox FactoryBpLady_Text_1
# 582 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	release
	end

FactoryBpLady_2:
# 577 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	bpmart FactoryBpMart8Badges
	goto FactoryBpLady_1


	.align 2
# 586 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
FactoryBpMart:
# 587 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_HEALTH_FEATHER
# 588 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_MUSCLE_FEATHER
# 589 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_RESIST_FEATHER
# 590 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_GENIUS_FEATHER
# 591 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_CLEVER_FEATHER
# 592 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_SWIFT_FEATHER
# 593 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_ABILITY_CAPSULE
# 594 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_ABILITY_PATCH
# 595 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_BECKONING_BELL
	.2byte ITEM_NONE

	.align 2
# 598 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
FactoryBpMart8Badges:
# 599 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_NUGGET
# 600 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_BIG_NUGGET
# 601 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_HEALTH_FEATHER
# 602 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_MUSCLE_FEATHER
# 603 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_RESIST_FEATHER
# 604 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_GENIUS_FEATHER
# 605 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_CLEVER_FEATHER
# 606 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_SWIFT_FEATHER
# 607 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_ABILITY_CAPSULE
# 608 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_ABILITY_PATCH
# 609 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.2byte ITEM_BECKONING_BELL
	.2byte ITEM_NONE

FactoryBpLady_Text_0:
# 575 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Welcome!$"

FactoryBpLady_Text_1:
# 581 "data/maps/BattleFrontier_BattleFactoryLobby/scripts.pory"
	.string "Thanks!$"
