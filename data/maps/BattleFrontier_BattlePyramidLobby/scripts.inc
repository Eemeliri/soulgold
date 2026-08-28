# 1 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 2 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_MapScripts::
# 3 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame
# 4 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
# 5 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.byte 0
# 6 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 7 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical
# 8 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_OnWarp:
# 9 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth
# 10 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte 0
# 11 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 12 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth:
# 13 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_TEMP_1, 1
# 14 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	turnobject LOCALID_PLAYER, DIR_NORTH
# 15 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 16 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 17 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_OnFrame:
# 18 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus
# 19 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving
# 20 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge
# 21 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge
# 22 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge
# 23 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte 0
# 24 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 25 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus::
# 26 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_getstatus
# 27 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 28 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 29 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving::
# 30 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lockall
# 31 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag
# 32 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 33 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	playse SE_EXP_MAX
# 34 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitse
# 35 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	closemessage
# 36 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_set PYRAMID_DATA_WIN_STREAK, 0
# 37 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
# 38 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 39 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 40 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	releaseall
# 41 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 42 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 43 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge::
# 44 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lockall
# 45 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_isbrain
# 46 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing
# 47 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid, MSGBOX_DEFAULT
# 48 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints
# 49 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 50 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing::
# 51 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing, MSGBOX_DEFAULT
# 52 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints::
# 53 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special DoBattlePyramidMonsHaveHeldItem
# 54 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag
# 55 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
# 56 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_checkairshow
# 57 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special LoadPlayerParty
# 58 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_clearhelditems
# 59 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special HealPlayerParty
# 60 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 61 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept
# 62 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 63 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	playse SE_EXP_MAX
# 64 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitse
# 65 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints, MSGBOX_DEFAULT
# 66 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_givepoints
# 67 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
# 68 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
# 69 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 70 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_setprize
# 71 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_save 0
# 72 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	playse SE_SAVE
# 73 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitse
# 74 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
# 75 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	closemessage
# 76 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 77 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	releaseall
# 78 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 79 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 80 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge::
# 81 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_checkairshow
# 82 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special LoadPlayerParty
# 83 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_clearhelditems
# 84 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special HealPlayerParty
# 85 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 86 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lockall
# 87 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag
# 88 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 89 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	playse SE_EXP_MAX
# 90 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitse
# 91 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
# 92 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 93 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
# 94 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_save 0
# 95 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	playse SE_SAVE
# 96 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitse
# 97 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
# 98 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	closemessage
# 99 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 100 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	releaseall
# 101 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 102 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 103 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge::
# 104 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge
# 105 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 106 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_Attendant::
# 107 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lock
# 108 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	faceplayer
# 109 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
# 110 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
# 111 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special SavePlayerParty
# 112 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid, MSGBOX_DEFAULT
# 113 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge::
# 114 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge
# 115 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 116 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
# 117 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 118 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
# 119 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge
# 120 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
# 121 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
# 122 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 123 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge::
# 124 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode
# 125 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 126 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	multichoice 17, 2, MULTI_LEVEL_MODE, FALSE
# 127 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 128 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleFrontier_BattlePyramidLobby_EventScript_Innates
# 129 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleFrontier_BattlePyramidLobby_EventScript_LevelInfo
# 130 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleFrontier_BattlePyramidLobby_EventScript_Bgm
# 131 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
# 132 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_checkineligible
# 133 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons
# 134 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 135 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
# 136 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	fadescreen FADE_TO_BLACK
# 137 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	callnative RemoveFollowingPokemon
# 138 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 139 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 140 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
# 141 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special ChoosePartyForBattleFrontier
# 142 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitstate
# 143 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
# 144 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
# 145 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 146 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
# 147 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge
# 148 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
# 149 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 150 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_LevelInfo::
# 151 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 152 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
# 153 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 154 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_Innates::
# 155 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 156 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
# 157 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 158 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_Bgm::
# 159 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 160 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
# 161 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 162 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge::
# 163 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 164 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 165 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_init
# 166 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, TRUE
# 167 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
# 168 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 169 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_seedfloor
# 170 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_settrainers
# 171 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special LoadPlayerParty
# 172 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	closemessage
# 173 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	delay 2
# 174 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call Common_EventScript_SaveGame
# 175 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 176 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed
# 177 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge::
# 178 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special SavePlayerParty
# 179 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_setpartyorder FRONTIER_PARTY_SIZE
# 180 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid, MSGBOX_DEFAULT
# 181 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	closemessage
# 182 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag
# 183 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 184 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_RESULT, 0
# 185 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special HealPlayerParty
# 186 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
# 187 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 188 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitstate
# 189 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 190 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 191 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge::
# 192 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid, MSGBOX_DEFAULT
# 193 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge
# 194 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 195 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons::
# 196 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 197 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50
# 198 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen
# 199 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 200 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50::
# 201 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
# 202 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 203 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 204 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge
# 205 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 206 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen::
# 207 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
# 208 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_ShowCaughtBannedSpecies
# 209 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
# 210 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge
# 211 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 212 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed::
# 213 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 214 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
# 215 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 216 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge::
# 217 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special LoadPlayerParty
# 218 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	callnative UpdateFollowingPokemon
# 219 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge::
# 220 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge, MSGBOX_DEFAULT
# 221 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge::
# 222 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	release
# 223 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 224 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 225 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintGiver::
# 226 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lockall
# 227 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	applymovement LOCALID_PYRAMID_LOBBY_HINT_GIVER, Common_Movement_FacePlayer
# 228 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmovement 0
# 229 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait, MSGBOX_DEFAULT
# 230 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint
# 231 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot, MSGBOX_DEFAULT
# 232 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	releaseall
# 233 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 234 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 235 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_GiveHint::
# 236 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	multichoice 32, 10, MULTI_LEVEL_MODE_WITH_EXIT, FALSE
# 237 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 238 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50
# 239 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen
# 240 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
# 241 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
# 242 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 243 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 244 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ Shouldn't occur
# 245 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_NoHint::
# 246 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 247 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 248 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50::
# 249 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
# 250 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
# 251 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak
# 252 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_RESULT, 0
# 253 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
# 254 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 255 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 256 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak::
# 257 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
# 258 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
# 259 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 260 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 261 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen::
# 262 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
# 263 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
# 264 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak
# 265 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setvar VAR_RESULT, 0
# 266 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
# 267 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 268 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 269 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak::
# 270 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
# 271 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
# 272 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 273 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 274 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment::
# 275 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 276 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special GetBattlePyramidHint
# 277 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 278 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis
# 279 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison
# 280 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn
# 281 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste
# 282 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate
# 283 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility
# 284 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce
# 285 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion
# 286 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic
# 287 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock
# 288 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting
# 289 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather
# 290 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug
# 291 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark
# 292 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater
# 293 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost
# 294 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel
# 295 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon
# 296 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve
# 297 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal
# 298 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 299 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 300 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis::
# 301 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis, MSGBOX_DEFAULT
# 302 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 303 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 304 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintPoison::
# 305 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison, MSGBOX_DEFAULT
# 306 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 307 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 308 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintBurn::
# 309 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn, MSGBOX_DEFAULT
# 310 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 311 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 312 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste::
# 313 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste, MSGBOX_DEFAULT
# 314 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 315 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 316 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate::
# 317 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate, MSGBOX_DEFAULT
# 318 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 319 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 320 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility::
# 321 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility, MSGBOX_DEFAULT
# 322 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 323 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 324 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintIce::
# 325 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce, MSGBOX_DEFAULT
# 326 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 327 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 328 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion::
# 329 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion, MSGBOX_DEFAULT
# 330 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 331 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 332 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic::
# 333 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic, MSGBOX_DEFAULT
# 334 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 335 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 336 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintRock::
# 337 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock, MSGBOX_DEFAULT
# 338 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 339 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 340 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintFighting::
# 341 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting, MSGBOX_DEFAULT
# 342 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 343 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 344 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintWeather::
# 345 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather, MSGBOX_DEFAULT
# 346 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 347 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 348 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintBug::
# 349 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug, MSGBOX_DEFAULT
# 350 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 351 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 352 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintDark::
# 353 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark, MSGBOX_DEFAULT
# 354 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 355 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 356 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintWater::
# 357 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater, MSGBOX_DEFAULT
# 358 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 359 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 360 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintGhost::
# 361 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost, MSGBOX_DEFAULT
# 362 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 363 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 364 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintSteel::
# 365 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel, MSGBOX_DEFAULT
# 366 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 367 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 368 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon::
# 369 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon, MSGBOX_DEFAULT
# 370 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 371 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 372 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve::
# 373 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve, MSGBOX_DEFAULT
# 374 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 375 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 376 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HintNormal::
# 377 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal, MSGBOX_DEFAULT
# 378 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 379 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 380 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ShowResults::
# 381 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lockall
# 382 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	frontier_results FRONTIER_FACILITY_PYRAMID
# 383 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitbuttonpress
# 384 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special RemoveRecordsWindow
# 385 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	releaseall
# 386 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 387 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 388 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag::
# 389 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
# 390 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
# 391 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmovement 0
# 392 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping, MSGBOX_DEFAULT
# 393 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	pyramid_get PYRAMID_DATA_WIN_STREAK
# 394 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag
# 395 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag, MSGBOX_DEFAULT
# 396 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag
# 397 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 398 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag::
# 399 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag, MSGBOX_DEFAULT
# 400 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag::
# 401 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag
# 402 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 403 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	playse SE_EXP_MAX
# 404 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitse
# 405 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel, MSGBOX_DEFAULT
# 406 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	closemessage
# 407 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
# 408 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmovement 0
# 409 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
# 410 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmovement 0
# 411 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 412 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 413 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel:
# 414 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 415 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 416 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 417 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 418 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 419 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 420 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 421 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	face_down
# 422 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	step_end
# 423 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 424 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel:
# 425 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 426 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 427 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 428 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 429 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 430 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 431 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 432 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	step_end
# 433 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 434 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside:
# 435 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_right
# 436 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	face_left
# 437 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	step_end
# 438 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 439 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel:
# 440 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 441 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	walk_up
# 442 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	step_end
# 443 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 444 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag::
# 445 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake, MSGBOX_DEFAULT
# 446 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
# 447 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special TryStoreHeldItemsInPyramidBag
# 448 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag
# 449 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep
# 450 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 451 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
# 452 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 453 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 454 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag::
# 455 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag, MSGBOX_DEFAULT
# 456 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 457 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 458 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag
# 459 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep::
# 460 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, FALSE
# 461 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 462 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag
# 463 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty
# 464 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
# 465 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
# 466 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 467 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 468 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag::
# 469 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special ChooseItemsToTossFromPyramidBag
# 470 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitstate
# 471 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
# 472 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 473 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
# 474 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 475 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 476 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty::
# 477 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special BattlePyramidChooseMonHeldItems
# 478 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitstate
# 479 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
# 480 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 481 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
# 482 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 483 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 484 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems::
# 485 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	special DoBattlePyramidMonsHaveHeldItem
# 486 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems
# 487 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	return
# 488 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 489 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems::
# 490 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem, MSGBOX_DEFAULT
# 491 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
# 492 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 493 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
# 494 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 495 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 496 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_Woman::
# 497 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning, MSGBOX_NPC
# 498 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 499 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 500 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_FatMan::
# 501 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems, MSGBOX_NPC
# 502 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 503 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 504 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard::
# 505 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lockall
# 506 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed, MSGBOX_DEFAULT
# 507 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
# 508 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 509 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 510 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard::
# 511 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading
# 512 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	waitmessage
# 513 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, FALSE
# 514 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	switch VAR_RESULT
# 515 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon
# 516 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers
# 517 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze
# 518 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag
# 519 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
# 520 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
# 521 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 522 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 523 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon::
# 524 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
# 525 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
# 526 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 527 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 528 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers::
# 529 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules, MSGBOX_DEFAULT
# 530 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
# 531 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 532 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 533 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze::
# 534 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules, MSGBOX_DEFAULT
# 535 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
# 536 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 537 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 538 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_RulesBag::
# 539 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules, MSGBOX_DEFAULT
# 540 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
# 541 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 542 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 543 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_EventScript_ExitRules::
# 544 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	releaseall
# 545 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	end
# 546 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 547 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid:
# 548 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Where the courage of Trainers\n"
# 549 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "is put to the test!\p"
# 550 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Welcome to the Battle Pyramid!\p"
# 551 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I am your guide to\n"
# 552 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Battle Quest.$"
# 553 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 554 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge:
# 555 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Have you the courage to embark on\n"
# 556 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Battle Quest challenge?$"
# 557 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 558 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge:
# 559 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "We await your challenge in the future!$"
# 560 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 561 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid:
# 562 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The Battle Quest is a battling\n"
# 563 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "event in which you must explore\l"
# 564 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Pyramid and try to reach the top.\p"
# 565 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "In the Pyramid are seven floors of\n"
# 566 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "mazes, all of them filled with not only\l"
# 567 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "skilled Trainers but also wild Pokémon.\p"
# 568 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You must enter with three Pokémon,\n"
# 569 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "none of them holding an item.\p"
# 570 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "On your ascent, you will be provided\n"
# 571 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "with a Battle Bag for items.\p"
# 572 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "If you fail in your challenge, any item\n"
# 573 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "placed in the Battle Bag disappears.\p"
# 574 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "If you want to interrupt your\n"
# 575 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "challenge, you must select “Rest”\l"
# 576 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "and save the game.\p"
# 577 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "If you don't save before interrupting,\n"
# 578 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "you will be disqualified.$"
# 579 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 580 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode:
# 581 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The Pyramid offers two courses,\n"
# 582 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Classic and Chaos.\l"
# 583 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Which will you enter?$"
# 584 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 585 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons:
# 586 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Very good. Now, please select the three\n"
# 587 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Pokémon you wish to accompany you.$"
# 588 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 589 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen:
# 590 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "A slight problem, adventurer!\p"
# 591 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You seem to not have the three\n"
# 592 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Pokémon qualified for the challenge.\p"
# 593 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Please also remember to take all\n"
# 594 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "items from your Pokémon.\p"
# 595 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 596 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 597 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50:
# 598 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "A slight problem, adventurer!\p"
# 599 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You seem to not have the three\n"
# 600 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Pokémon qualified for the challenge.\p"
# 601 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The three Pokémon must be different\n"
# 602 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "and each eligible to enter.\p"
# 603 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Please also remember to take all\n"
# 604 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "items from your Pokémon.\p"
# 605 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Eggs{STR_VAR_1}.$"
# 606 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 607 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd:
# 608 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "When you are ready, please have\n"
# 609 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "a word with me.$"
# 610 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 611 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge:
# 612 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Before you enter the Battle Pyramid,\n"
# 613 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the game must be saved. Is that okay?$"
# 614 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 615 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid:
# 616 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Very good. I will now show you into\n"
# 617 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Battle Pyramid.$"
# 618 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 619 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping:
# 620 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "We will hold your Bag for safekeeping,\n"
# 621 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{PLAYER}, while you are exploring.$"
# 622 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 623 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag:
# 624 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "In exchange, please take this Battle\n"
# 625 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Bag, the one you used previously.$"
# 626 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 627 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag:
# 628 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "In exchange, please take this\n"
# 629 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Battle Bag.$"
# 630 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 631 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag:
# 632 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{PLAYER} exchanged the Bag for\n"
# 633 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Battle Bag.$"
# 634 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 635 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel:
# 636 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "When you step on this floor panel,\n"
# 637 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "you will be transported to a higher\l"
# 638 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "floor in the Pyramid.\p"
# 639 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I hope for your sake that your\n"
# 640 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "quest goes safely!$"
# 641 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 642 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag:
# 643 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "A major problem, explorer!\p"
# 644 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You did not save before ending\n"
# 645 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "your challenge the last time.\p"
# 646 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Consequently, your challenge has\n"
# 647 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "been disqualified, I'm sorry to say.\p"
# 648 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Here is the Bag we've been holding\n"
# 649 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "for you.\p"
# 650 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{PLAYER} got the Bag back.$"
# 651 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 652 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid:
# 653 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Excellent to see you back!\p"
# 654 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You've conquered the Pyramid!\n"
# 655 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "How splendid!$"
# 656 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 657 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake:
# 658 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Ah, a slight problem.\p"
# 659 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "At least one Pokémon is holding\n"
# 660 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "an item.\p"
# 661 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I'm sorry to say, items obtained in\n"
# 662 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Pyramid cannot be taken away.$"
# 663 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 664 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag:
# 665 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "All items held by your Pokémon will be\n"
# 666 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "moved to your Battle Bag, {PLAYER}.$"
# 667 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 668 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep:
# 669 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The Battle Bag cannot hold all your\n"
# 670 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "items, I'm sorry to say.\p"
# 671 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Please pick the items you'll keep in the\n"
# 672 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Battle Bag, and with your Pokémon.$"
# 673 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 674 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem:
# 675 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "At least one Pokémon is still\n"
# 676 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "holding an item.$"
# 677 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 678 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep:
# 679 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Please pick the items you'll keep in the\n"
# 680 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Battle Bag, and with your Pokémon.$"
# 681 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 682 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ Unused
# 683 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld:
# 684 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{PLAYER} returned everything that\n"
# 685 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Pokémon held.$"
# 686 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 687 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept:
# 688 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The Battle Bag you used will be kept\n"
# 689 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "in readiness for your next challenge.\p"
# 690 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{PLAYER} turned the Battle Bag over\n"
# 691 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "for the Bag's return.$"
# 692 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 693 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait:
# 694 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I must record your results.\n"
# 695 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Please wait.$"
# 696 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 697 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ Unused
# 698 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis:
# 699 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "As a memento for conquering\n"
# 700 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Battle Pyramid, please take this.$"
# 701 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 702 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ Unused
# 703 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem:
# 704 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{PLAYER} received the prize\n"
# 705 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{STR_VAR_1}.$"
# 706 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 707 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ Unused
# 708 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_BagIsFull:
# 709 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…Ah…\n"
# 710 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Your Bag appears to be filled.\p"
# 711 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Please return after you've organized\n"
# 712 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "your Bag's contents.$"
# 713 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 714 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag:
# 715 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "How disappointing for you…\p"
# 716 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Here is the Bag we've been holding\n"
# 717 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "for you.\p"
# 718 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "{PLAYER} got the Bag back.$"
# 719 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 720 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge:
# 721 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "We look forward to your\n"
# 722 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "next challenge!$"
# 723 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 724 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
@ Unused
# 725 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize:
# 726 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "We have been looking forward to\n"
# 727 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "your arrival!\p"
# 728 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Here is your prize for conquering\n"
# 729 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the Pyramid.$"
# 730 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 731 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait:
# 732 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Welcome…\p"
# 733 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I shall be pleased to tell you what\n"
# 734 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "misfortunes await in the Pyramid…$"
# 735 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 736 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_Aah:
# 737 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "… … … … … …\n"
# 738 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "… … … … … …\p"
# 739 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "… … … … … …\n"
# 740 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Aah!$"
# 741 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 742 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintParalysis:
# 743 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see a shower of sparks…\p"
# 744 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And in it, I see your Pokémon\n"
# 745 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "struggling with paralysis…$"
# 746 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 747 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintPoison:
# 748 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see poison…\p"
# 749 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 750 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from the effects of poison…$"
# 751 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 752 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintBurn:
# 753 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see bright red flames…\p"
# 754 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 755 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from burns…$"
# 756 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 757 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintPPWaste:
# 758 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I sense the tremendous pressure of\n"
# 759 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "unrequited anger…\p"
# 760 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "It is a curse…\p"
# 761 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon drained of\n"
# 762 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Power Points and having no recourse\l"
# 763 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "but to use Struggle…$"
# 764 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 765 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintLevitate:
# 766 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Pokémon loftily airborne…\p"
# 767 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon frustrated\n"
# 768 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "by powerless Ground-type moves…$"
# 769 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 770 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility:
# 771 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I sense terrific energy rising from\n"
# 772 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the ground below…\p"
# 773 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon unable to\n"
# 774 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "escape the power's clutches…$"
# 775 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 776 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintIce:
# 777 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Ice-type Pokémon…\p"
# 778 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon fighting\n"
# 779 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the freezing effects of ice…$"
# 780 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 781 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintExplosion:
# 782 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see a flurry of moves that imperil\n"
# 783 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the user…\p"
# 784 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon falling\n"
# 785 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "to them…$"
# 786 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 787 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintPsychic:
# 788 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Psychic-type Pokémon…\p"
# 789 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon in torment\n"
# 790 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from Psychic moves…$"
# 791 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 792 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintRock:
# 793 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Rock-type Pokémon…\p"
# 794 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 795 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from Rock moves…$"
# 796 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 797 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintFighting:
# 798 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Fighting-type Pokémon…\p"
# 799 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon pummeled\n"
# 800 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "by Fighting moves…$"
# 801 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 802 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintWeather:
# 803 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Rain Dance… Sunny Day…\n"
# 804 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Sandstorm… Hail…\p"
# 805 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Pokémon that become stronger\n"
# 806 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "with the weather…\p"
# 807 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon confounded\n"
# 808 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "by different types of moves…$"
# 809 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 810 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintBug:
# 811 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Bug-type Pokémon…\p"
# 812 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 813 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from different kinds of attacks…$"
# 814 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 815 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintDark:
# 816 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Dark-type Pokémon…\p"
# 817 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 818 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from Dark-type moves…$"
# 819 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 820 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintWater:
# 821 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Water-type Pokémon…\p"
# 822 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 823 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from Water-type moves…$"
# 824 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 825 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintGhost:
# 826 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Ghost-type Pokémon…\p"
# 827 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 828 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from Ghost-type moves…$"
# 829 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 830 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintSteel:
# 831 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Steel-type Pokémon…\p"
# 832 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 833 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from enormously powerful moves…$"
# 834 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 835 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon:
# 836 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see flying Pokémon…\p"
# 837 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 838 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from enormously powerful moves…$"
# 839 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 840 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve:
# 841 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see those that have evolved from\n"
# 842 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the power of stones…\p"
# 843 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I also sense fire, water,\n"
# 844 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "and electricity…\p"
# 845 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 846 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from those three powers…$"
# 847 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 848 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_HintNormal:
# 849 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I see Normal-type Pokémon…\p"
# 850 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "…And, I see your Pokémon suffering\n"
# 851 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "from enormously powerful moves…$"
# 852 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 853 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot:
# 854 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Whether you believe my fortunes\n"
# 855 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "or not, the choice is yours…\p"
# 856 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The future can be changed anytime…\n"
# 857 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I wish you safe passage…$"
# 858 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 859 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning:
# 860 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Did you know?\p"
# 861 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "If you run fast, Trainers may notice\n"
# 862 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "and come after you for a battle.\p"
# 863 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "So, if you want to avoid Trainers,\n"
# 864 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "don't catch their eyes, but sneak\l"
# 865 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "cautiously and quietly past them.$"
# 866 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 867 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems:
# 868 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Awaaaaaaarrrrgh!\p"
# 869 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "I had a whole lot of items, but I lost\n"
# 870 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "them all when I lost!\p"
# 871 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Awaaaaaaarrrrgh!$"
# 872 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 873 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing:
# 874 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Welcome back!\n"
# 875 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You've done the unthinkable!\p"
# 876 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You've defeated the Pyramid King\n"
# 877 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "and conquered the Battle Pyramid!$"
# 878 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 879 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints:
# 880 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Young explorer!\n"
# 881 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "In commendation of your courage,\l"
# 882 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "we give you these Battle Point(s)!$"
# 883 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 884 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_RulesAreListed:
# 885 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The Battle Quest rules are listed.$"
# 886 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 887 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading:
# 888 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Which heading do you want to read?$"
# 889 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 890 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules:
# 891 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "When the Pyramid is conquered,\n"
# 892 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "the wild Pokémon that appear in it\l"
# 893 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "are replaced by different kinds.\p"
# 894 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Explore, observe, and learn what kinds\n"
# 895 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "of wild Pokémon you may encounter.$"
# 896 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 897 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules:
# 898 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Trainers are lying in wait for you\n"
# 899 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "inside the Pyramid.\p"
# 900 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "On each floor, there are up to\n"
# 901 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "eight Trainers.\p"
# 902 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "When you defeat a Trainer, you will\n"
# 903 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "get a helpful hint for your adventure.$"
# 904 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 905 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules:
# 906 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The mazes in the Pyramid rearrange\n"
# 907 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "themselves every time you enter it.\p"
# 908 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The mazes are poorly lit.\n"
# 909 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "You must advance with caution.\p"
# 910 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The light grows brighter whenever you\n"
# 911 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "defeat a wild Pokémon or a Trainer.$"
# 912 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"

# 913 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules:
# 914 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The Battle Bag serves as your Bag\n"
# 915 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "while in the Pyramid.\p"
# 916 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "There are two separate Battle Bags--\n"
# 917 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "one each for the Classic and\l"
# 918 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Chaos adventures.\p"
# 919 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "They each can hold up to 99 pieces\n"
# 920 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "of ten kinds of items.\p"
# 921 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "The contents of the Battle Bag are\n"
# 922 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "lost if you fail in your quest.$"

PyramidLobbyBPVendor::
# 926 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	lock
# 927 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	faceplayer
# 928 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox PyramidLobbyBPVendor_Text_0
# 929 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	bpmart PyramidBPVendor
# 930 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	msgbox PyramidLobbyBPVendor_Text_1
# 931 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	release
	end


	.align 2
# 935 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
PyramidBPVendor:
# 936 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_FLAME_ORB
# 937 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_TOXIC_ORB
# 938 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_LIFE_ORB
# 939 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_FOCUS_SASH
# 940 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_POWER_HERB
# 941 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_WHITE_HERB
# 942 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_BLACK_SLUDGE
# 943 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.2byte ITEM_ASSAULT_VEST
	.2byte ITEM_NONE

PyramidLobbyBPVendor_Text_0:
# 928 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Welcome!$"

PyramidLobbyBPVendor_Text_1:
# 930 "data/maps/BattleFrontier_BattlePyramidLobby/scripts.pory"
	.string "Thanks!$"
