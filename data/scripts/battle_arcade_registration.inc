BattleArcade_Registration_EventScript_SinglesAttendant::
# 9 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_2, FRONTIER_MODE_SINGLES
# 10 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_Attendant
	return


BattleArcade_Registration_EventScript_MultisAttendant::
# 15 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_2, FRONTIER_MODE_MULTIS
# 16 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_Attendant
	return


BattleArcade_Registration_EventScript_Attendant::
# 22 "data/scripts/battle_arcade_registration.pory"
	lock
# 23 "data/scripts/battle_arcade_registration.pory"
	faceplayer
# 24 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARCADE
# 26 "data/scripts/battle_arcade_registration.pory"
	special SavePlayerParty
# 27 "data/scripts/battle_arcade_registration.pory"
	compare VAR_TEMP_2, FRONTIER_MODE_SINGLES
	goto_if_eq BattleArcade_Registration_EventScript_Attendant_1
# 34 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_Attendant_Text_1, MSGBOX_DEFAULT
# 35 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_AskEnterMultiChallenge
	return

BattleArcade_Registration_EventScript_Attendant_1:
# 29 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_Attendant_Text_0
# 30 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_AskEnterChallenge
	return


BattleArcade_Registration_EventScript_AskEnterChallenge::
# 41 "data/scripts/battle_arcade_registration.pory"
	message BattleArcade_Registration_EventScript_AskEnterChallenge_Text_0
# 42 "data/scripts/battle_arcade_registration.pory"
	waitmessage
# 43 "data/scripts/battle_arcade_registration.pory"
	multichoice 17, 4, MULTI_CHALLENGE_TYPES_INFO, FALSE
# 44 "data/scripts/battle_arcade_registration.pory"
	switch VAR_RESULT
# 46 "data/scripts/battle_arcade_registration.pory"
	case 0, BattleArcade_Registration_EventScript_AskEnterChallenge_2
# 47 "data/scripts/battle_arcade_registration.pory"
	case 1, BattleArcade_Registration_EventScript_AskEnterChallenge_2
# 50 "data/scripts/battle_arcade_registration.pory"
	case 2, BattleArcade_Registration_EventScript_AskEnterChallenge_3
# 52 "data/scripts/battle_arcade_registration.pory"
	case 3, BattleArcade_Registration_EventScript_AskEnterChallenge_4
# 53 "data/scripts/battle_arcade_registration.pory"
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_AskEnterChallenge_4
	return

BattleArcade_Registration_EventScript_AskEnterChallenge_2:
# 48 "data/scripts/battle_arcade_registration.pory"
	copyvar VAR_FRONTIER_BATTLE_MODE, VAR_RESULT
# 49 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	return

BattleArcade_Registration_EventScript_AskEnterChallenge_3:
# 51 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_ExplainChallenge
	return

BattleArcade_Registration_EventScript_AskEnterChallenge_4:
# 54 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_AskEnterMultiChallenge::
# 60 "data/scripts/battle_arcade_registration.pory"
	message BattleArcade_Registration_EventScript_AskEnterMultiChallenge_Text_0
# 61 "data/scripts/battle_arcade_registration.pory"
	waitmessage
# 62 "data/scripts/battle_arcade_registration.pory"
	multichoice 17, 5, MULTI_CHALLENGEINFO, FALSE
# 63 "data/scripts/battle_arcade_registration.pory"
	switch VAR_RESULT
# 65 "data/scripts/battle_arcade_registration.pory"
	case 0, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_2
# 68 "data/scripts/battle_arcade_registration.pory"
	case 1, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_3
# 70 "data/scripts/battle_arcade_registration.pory"
	case 2, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_4
# 71 "data/scripts/battle_arcade_registration.pory"
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_4
	return

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_2:
# 66 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
# 67 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	return

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_3:
# 69 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_ExplainChallenge
	return

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_4:
# 72 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_ExplainChallenge::
# 78 "data/scripts/battle_arcade_registration.pory"
	compare VAR_TEMP_2, FRONTIER_MODE_SINGLES
	goto_if_eq BattleArcade_Registration_EventScript_ExplainChallenge_1
# 85 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_ExplainChallenge_Text_1, MSGBOX_DEFAULT
# 86 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_AskEnterMultiChallenge
	return

BattleArcade_Registration_EventScript_ExplainChallenge_1:
# 80 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_ExplainChallenge_Text_0, MSGBOX_DEFAULT
# 81 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_AskEnterChallenge
	return


BattleArcade_Registration_EventScript_TryEnterChallenge::
# 92 "data/scripts/battle_arcade_registration.pory"
	message BattleArcade_Registration_EventScript_TryEnterChallenge_Text_0
# 93 "data/scripts/battle_arcade_registration.pory"
	waitmessage
# 94 "data/scripts/battle_arcade_registration.pory"
	multichoice 17, 4, MULTI_LEVEL_MODE, FALSE
# 95 "data/scripts/battle_arcade_registration.pory"
	switch VAR_RESULT
# 97 "data/scripts/battle_arcade_registration.pory"
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleArcade_Registration_EventScript_TryEnterChallenge_3
# 100 "data/scripts/battle_arcade_registration.pory"
	case FRONTIER_LEVEL_CHOICE_INFO, BattleArcade_Registration_EventScript_TryEnterChallenge_4
# 103 "data/scripts/battle_arcade_registration.pory"
	case FRONTIER_LEVEL_CHOICE_BGM, BattleArcade_Registration_EventScript_TryEnterChallenge_5
# 106 "data/scripts/battle_arcade_registration.pory"
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_TryEnterChallenge_6
BattleArcade_Registration_EventScript_TryEnterChallenge_1:
# 108 "data/scripts/battle_arcade_registration.pory"
	frontier_checkineligible
# 109 "data/scripts/battle_arcade_registration.pory"
	compare VAR_0x8004, 0
	goto_if_ne BattleArcade_Registration_EventScript_TryEnterChallenge_8
BattleArcade_Registration_EventScript_TryEnterChallenge_7:
# 114 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
# 115 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectMons, MSGBOX_DEFAULT
# 117 "data/scripts/battle_arcade_registration.pory"
	fadescreen FADE_TO_BLACK
# 118 "data/scripts/battle_arcade_registration.pory"
	frontier_get FRONTIER_DATA_LVL_MODE
# 119 "data/scripts/battle_arcade_registration.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 120 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_GetPartySize
# 122 "data/scripts/battle_arcade_registration.pory"
	special ChoosePartyForBattleFrontier
# 123 "data/scripts/battle_arcade_registration.pory"
	waitstate
# 124 "data/scripts/battle_arcade_registration.pory"
	compare VAR_RESULT, 0
	goto_if_eq BattleArcade_Registration_EventScript_TryEnterChallenge_11
BattleArcade_Registration_EventScript_TryEnterChallenge_10:
# 128 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_SaveBeforeChallenge
	return

BattleArcade_Registration_EventScript_TryEnterChallenge_3:
# 98 "data/scripts/battle_arcade_registration.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 99 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_4:
# 101 "data/scripts/battle_arcade_registration.pory"
	call BattleFrontier_EventScript_ShowLevelModeInfo
# 102 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_5:
# 104 "data/scripts/battle_arcade_registration.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 105 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_6:
# 106 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_8:
# 111 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_GetPartySize
# 112 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_NotEnoughValidMons
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_7

BattleArcade_Registration_EventScript_TryEnterChallenge_11:
# 126 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_LoadPartyCancelChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_10


BattleArcade_Registration_EventScript_GetPartySize::
# 133 "data/scripts/battle_arcade_registration.pory"
	switch VAR_FRONTIER_BATTLE_MODE
# 135 "data/scripts/battle_arcade_registration.pory"
	case FRONTIER_MODE_SINGLES, BattleArcade_Registration_EventScript_GetPartySize_3
# 136 "data/scripts/battle_arcade_registration.pory"
	case FRONTIER_MODE_DOUBLES, BattleArcade_Registration_EventScript_GetPartySize_4
# 137 "data/scripts/battle_arcade_registration.pory"
	case FRONTIER_MODE_LINK_MULTIS, BattleArcade_Registration_EventScript_GetPartySize_5
BattleArcade_Registration_EventScript_GetPartySize_1:
	return

BattleArcade_Registration_EventScript_GetPartySize_3:
# 135 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	goto BattleArcade_Registration_EventScript_GetPartySize_1

BattleArcade_Registration_EventScript_GetPartySize_4:
# 136 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	goto BattleArcade_Registration_EventScript_GetPartySize_1

BattleArcade_Registration_EventScript_GetPartySize_5:
# 137 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
	goto BattleArcade_Registration_EventScript_GetPartySize_1


BattleArcade_Registration_EventScript_NotEnoughValidMons::
# 144 "data/scripts/battle_arcade_registration.pory"
	buffernumberstring STR_VAR_2, VAR_0x8005
# 145 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_0, MSGBOX_DEFAULT
# 147 "data/scripts/battle_arcade_registration.pory"
	call BattleFrontier_EventScript_GetLvlMode
# 148 "data/scripts/battle_arcade_registration.pory"
	compare VAR_RESULT, FRONTIER_LVL_50
	goto_if_eq BattleArcade_Registration_EventScript_NotEnoughValidMons_2
BattleArcade_Registration_EventScript_NotEnoughValidMons_1:
# 152 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_2, MSGBOX_DEFAULT
# 153 "data/scripts/battle_arcade_registration.pory"
	closemessage
	end

BattleArcade_Registration_EventScript_NotEnoughValidMons_2:
# 150 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_1, MSGBOX_DEFAULT
	goto BattleArcade_Registration_EventScript_NotEnoughValidMons_1


BattleArcade_Registration_EventScript_LoadPartyCancelChallenge::
# 159 "data/scripts/battle_arcade_registration.pory"
	special LoadPlayerParty
# 160 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_CancelChallenge::
# 165 "data/scripts/battle_arcade_registration.pory"
	msgbox gText_WeHopeToSeeYouAgain, MSGBOX_DEFAULT
# 166 "data/scripts/battle_arcade_registration.pory"
	closemessage
# 167 "data/scripts/battle_arcade_registration.pory"
	release
	end


BattleArcade_Registration_EventScript_SaveBeforeChallenge::
# 173 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
# 174 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 175 "data/scripts/battle_arcade_registration.pory"
	arcade_init
# 176 "data/scripts/battle_arcade_registration.pory"
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, TRUE
# 177 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 178 "data/scripts/battle_arcade_registration.pory"
	special LoadPlayerParty
# 179 "data/scripts/battle_arcade_registration.pory"
	closemessage
# 180 "data/scripts/battle_arcade_registration.pory"
	delay 2
# 182 "data/scripts/battle_arcade_registration.pory"
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
	goto_if_eq BattleArcade_Registration_EventScript_SaveBeforeChallenge_2
BattleArcade_Registration_EventScript_SaveBeforeChallenge_1:
# 188 "data/scripts/battle_arcade_registration.pory"
	call Common_EventScript_SaveGame
# 189 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 191 "data/scripts/battle_arcade_registration.pory"
	compare VAR_RESULT, 0
	goto_if_eq BattleArcade_Registration_EventScript_SaveBeforeChallenge_5
BattleArcade_Registration_EventScript_SaveBeforeChallenge_4:
# 197 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_HandleMultiplayer
# 198 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_EnterElevator
	return

BattleArcade_Registration_EventScript_SaveBeforeChallenge_2:
# 184 "data/scripts/battle_arcade_registration.pory"
	arcade_save 0
# 185 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Entrance_LinkMulti_EventScript_Cancel
	goto BattleArcade_Registration_EventScript_SaveBeforeChallenge_1

BattleArcade_Registration_EventScript_SaveBeforeChallenge_5:
# 193 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS
# 194 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	goto BattleArcade_Registration_EventScript_SaveBeforeChallenge_4


BattleArcade_Registration_EventScript_HandleMultiplayer::
# 203 "data/scripts/battle_arcade_registration.pory"
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
	goto_if_ne BattleArcade_Registration_EventScript_HandleMultiplayer_2
# 208 "data/scripts/battle_arcade_registration.pory"
	specialvar VAR_RESULT, IsWirelessAdapterConnected
# 209 "data/scripts/battle_arcade_registration.pory"
	compare VAR_RESULT, 0
	goto_if_ne BattleArcade_Registration_EventScript_HandleMultiplayer_5
BattleArcade_Registration_EventScript_HandleMultiplayer_4:
# 213 "data/scripts/battle_arcade_registration.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryCableLink
	return

BattleArcade_Registration_EventScript_HandleMultiplayer_2:
	return

BattleArcade_Registration_EventScript_HandleMultiplayer_5:
# 211 "data/scripts/battle_arcade_registration.pory"
	goto BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink
	goto BattleArcade_Registration_EventScript_HandleMultiplayer_4


BattleArcade_Registration_EventScript_EnterElevator::
# 218 "data/scripts/battle_arcade_registration.pory"
	special SavePlayerParty
# 219 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_0x8004, FRONTIER_UTIL_FUNC_SET_PARTY_ORDER
# 220 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_GetPartySize
# 221 "data/scripts/battle_arcade_registration.pory"
	special CallFrontierUtilFunc
# 222 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_RESULT, 0
# 223 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_GoToHallway
	return


BattleArcade_Registration_EventScript_GoToHallway::
# 228 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_ShowYouToBattleRoom
# 229 "data/scripts/battle_arcade_registration.pory"
	special HealPlayerParty
# 230 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Lobby_EventScript_WarpToHallway
# 231 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
# 232 "data/scripts/battle_arcade_registration.pory"
	waitstate
	end


BattleArcade_Registration_EventScript_ShowYouToBattleRoom::
# 238 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
# 239 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Lobby_EventScript_WalkToElevator
	return


BattleArcade_Registration_EventScript_GetChallengeStatus::
# 245 "data/scripts/battle_arcade_registration.pory"
	frontier_getstatus
	end


BattleArcade_Registration_EventScript_ResetChallengeStatus::
# 251 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 252 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	return


BattleArcade_Registration_EventScript_WonChallenge::
# 258 "data/scripts/battle_arcade_registration.pory"
	lock
# 259 "data/scripts/battle_arcade_registration.pory"
	faceplayer
# 261 "data/scripts/battle_arcade_registration.pory"
	frontier_isbrain
# 262 "data/scripts/battle_arcade_registration.pory"
	compare VAR_RESULT, 0
	goto_if_ne BattleArcade_Registration_EventScript_WonChallenge_2
BattleArcade_Registration_EventScript_WonChallenge_1:
# 266 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_ResetChallengeStatus
# 267 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return

BattleArcade_Registration_EventScript_WonChallenge_2:
# 264 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_CheckStreakAndSymbols
	goto BattleArcade_Registration_EventScript_WonChallenge_1


BattleArcade_Registration_EventScript_CheckStreakAndSymbols::
# 272 "data/scripts/battle_arcade_registration.pory"
	arcade_checksymbol
# 273 "data/scripts/battle_arcade_registration.pory"
	switch VAR_RESULT
# 275 "data/scripts/battle_arcade_registration.pory"
	case ARCADE_SYMBOL_SILVER, BattleArcade_Registration_EventScript_CheckStreakAndSymbols_2
# 277 "data/scripts/battle_arcade_registration.pory"
	case ARCADE_SYMBOL_GOLD, BattleArcade_Registration_EventScript_CheckStreakAndSymbols_3
# 279 "data/scripts/battle_arcade_registration.pory"
	case ARCADE_SYMBOL_NONE, BattleArcade_Registration_EventScript_CheckStreakAndSymbols_4
BattleArcade_Registration_EventScript_CheckStreakAndSymbols_4:
	return

BattleArcade_Registration_EventScript_CheckStreakAndSymbols_2:
# 276 "data/scripts/battle_arcade_registration.pory"
	setflag FLAG_ARCADE_SILVER_PRINT
	return

BattleArcade_Registration_EventScript_CheckStreakAndSymbols_3:
# 278 "data/scripts/battle_arcade_registration.pory"
	setflag FLAG_ARCADE_GOLD_PRINT
	return


BattleArcade_Registration_EventScript_GiveGoldPrint::
# 287 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Entrance_Text_CongratulationsInHonorOf, MSGBOX_DEFAULT
# 288 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_GiveGoldPrint_Text_0, MSGBOX_DEFAULT
# 289 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_GivePrint
	return


BattleArcade_Registration_EventScript_GiveSilverPrint::
# 294 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Entrance_Text_CongratulationsInHonorOf, MSGBOX_DEFAULT
# 295 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_GiveSilverPrint_Text_0, MSGBOX_DEFAULT
# 296 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_GivePrint
	return


BattleArcade_Registration_EventScript_QuitWithoutSaving::
# 301 "data/scripts/battle_arcade_registration.pory"
	lock
# 302 "data/scripts/battle_arcade_registration.pory"
	faceplayer
# 303 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Registration_EventScript_QuitWithoutSaving_Text_0, MSGBOX_DEFAULT
# 304 "data/scripts/battle_arcade_registration.pory"
	closemessage
# 305 "data/scripts/battle_arcade_registration.pory"
	arcade_set ARCADE_DATA_WIN_STREAK, 0
# 306 "data/scripts/battle_arcade_registration.pory"
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, FALSE
# 307 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
# 308 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 309 "data/scripts/battle_arcade_registration.pory"
	release
	end


BattleArcade_Registration_EventScript_GivePrint::
# 315 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_CheckandGivePrint
# 316 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_PlayFanfareMessage
	return


BattleArcade_Registration_EventScript_CheckandGivePrint::
# 322 "data/scripts/battle_arcade_registration.pory"
	goto_if_set FLAG_ARCADE_SILVER_PRINT, BattleArcade_Registration_EventScript_CheckandGivePrint_1
# 328 "data/scripts/battle_arcade_registration.pory"
	setflag FLAG_ARCADE_SILVER_PRINT
	return

BattleArcade_Registration_EventScript_CheckandGivePrint_1:
# 324 "data/scripts/battle_arcade_registration.pory"
	setflag FLAG_ARCADE_GOLD_PRINT
	return


BattleArcade_Registration_EventScript_PlayFanfareMessage::
# 334 "data/scripts/battle_arcade_registration.pory"
	playfanfare MUS_OBTAIN_SYMBOL
# 335 "data/scripts/battle_arcade_registration.pory"
	waitmessage
# 336 "data/scripts/battle_arcade_registration.pory"
	waitfanfare
	return


BattleArcade_Registration_EventScript_LostChallenge::
# 341 "data/scripts/battle_arcade_registration.pory"
	arcade_get ARCADE_DATA_WIN_STREAK
# 342 "data/scripts/battle_arcade_registration.pory"
	compare VAR_RESULT, 0
	goto_if_ne BattleArcade_Registration_EventScript_LostChallenge_2
BattleArcade_Registration_EventScript_LostChallenge_1:
# 346 "data/scripts/battle_arcade_registration.pory"
	call BattleArcade_Registration_EventScript_ResetChallengeStatus
# 347 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_LostThanksForPlaying
	return

BattleArcade_Registration_EventScript_LostChallenge_2:
# 344 "data/scripts/battle_arcade_registration.pory"
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, FALSE
	goto BattleArcade_Registration_EventScript_LostChallenge_1


BattleArcade_Registration_EventScript_LostThanksForPlaying::
# 352 "data/scripts/battle_arcade_registration.pory"
	lock
# 353 "data/scripts/battle_arcade_registration.pory"
	faceplayer
# 354 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
# 355 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_ResumeChallenge::
# 360 "data/scripts/battle_arcade_registration.pory"
	lock
# 361 "data/scripts/battle_arcade_registration.pory"
	faceplayer
# 363 "data/scripts/battle_arcade_registration.pory"
	message BattleArcade_Registration_EventScript_ResumeChallenge_Text_0
# 364 "data/scripts/battle_arcade_registration.pory"
	waitmessage
# 366 "data/scripts/battle_arcade_registration.pory"
	arcade_save CHALLENGE_STATUS_SAVING
# 367 "data/scripts/battle_arcade_registration.pory"
	playse SE_SAVE
# 368 "data/scripts/battle_arcade_registration.pory"
	waitse
# 369 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_PAUSED, FALSE
# 371 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_EnterElevator
	end


BattleArcade_Entrance_LinkMulti_EventScript_Cancel::
# 377 "data/scripts/battle_arcade_registration.pory"
	msgbox BattleArcade_Entrance_LinkMulti_EventScript_Cancel_Text_0
# 378 "data/scripts/battle_arcade_registration.pory"
	closemessage
# 379 "data/scripts/battle_arcade_registration.pory"
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS
# 380 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_AskModeResultsBoard::
# 385 "data/scripts/battle_arcade_registration.pory"
	lockall
# 386 "data/scripts/battle_arcade_registration.pory"
	message BattleArcade_Registration_EventScript_AskModeResultsBoard_Text_0
# 387 "data/scripts/battle_arcade_registration.pory"
	waitmessage
# 388 "data/scripts/battle_arcade_registration.pory"
	multichoice 17, 2, MULTI_BATTLE_ARCADE_RECORDS, FALSE
# 389 "data/scripts/battle_arcade_registration.pory"
	switch VAR_RESULT
# 391 "data/scripts/battle_arcade_registration.pory"
	case 2, BattleArcade_Registration_EventScript_AskModeResultsBoard_2
# 394 "data/scripts/battle_arcade_registration.pory"
	case 3, BattleArcade_Registration_EventScript_AskModeResultsBoard_3
# 395 "data/scripts/battle_arcade_registration.pory"
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_AskModeResultsBoard_3
# 400 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_ShowResults
	return

BattleArcade_Registration_EventScript_AskModeResultsBoard_2:
# 392 "data/scripts/battle_arcade_registration.pory"
	setvar VAR_RESULT, FRONTIER_MODE_LINK_MULTIS
# 393 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_ShowResults
	return

BattleArcade_Registration_EventScript_AskModeResultsBoard_3:
# 396 "data/scripts/battle_arcade_registration.pory"
	closemessage
# 397 "data/scripts/battle_arcade_registration.pory"
	releaseall
	end


BattleArcade_Registration_EventScript_ShowResults::
# 406 "data/scripts/battle_arcade_registration.pory"
	closemessage
# 407 "data/scripts/battle_arcade_registration.pory"
	copyvar VAR_0x8006, VAR_RESULT
# 408 "data/scripts/battle_arcade_registration.pory"
	fadescreen FADE_TO_BLACK
# 409 "data/scripts/battle_arcade_registration.pory"
	arcade_results VAR_0x8006
# 410 "data/scripts/battle_arcade_registration.pory"
	goto BattleArcade_Registration_EventScript_AskModeResultsBoard
	return


BattleArcade_Registration_EventScript_Attendant_Text_0:
# 29 "data/scripts/battle_arcade_registration.pory"
	.string "Welcome to the Rocket Arcade! I am your\n"
	.string "guide to the Single and Double Battle\l"
	.string "challenges. Please be aware that these\l"
	.string "challenges are designed for a single\l"
	.string "Trainer.$"

BattleArcade_Registration_EventScript_Attendant_Text_1:
# 34 "data/scripts/battle_arcade_registration.pory"
	.string "Welcome to the Rocket Arcade! I am your\n"
	.string "guide to the Multi Battle challenge.\l"
	.string "Please be aware that this challenge\l"
	.string "requires two Trainers.$"

BattleArcade_Registration_EventScript_AskEnterChallenge_Text_0:
# 41 "data/scripts/battle_arcade_registration.pory"
	.string "Which challenge would you like to take?$"

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_Text_0:
# 60 "data/scripts/battle_arcade_registration.pory"
	.string "Would you like to take the Rocket\n"
	.string "Arcade Multi Battle challenge?$"

BattleArcade_Registration_EventScript_ExplainChallenge_Text_0:
# 80 "data/scripts/battle_arcade_registration.pory"
	.string "At the Rocket Arcade, you may take a\n"
	.string "Single or Double Battle challenge. Each\l"
	.string "challenge lasts seven games, with the\l"
	.string "game board activated before every\l"
	.string "match. Depending on what comes up on\l"
	.string "the game board, an event takes place.\l"
	.string "Some events will be good for the\l"
	.string "challenger, while others won't be. After\l"
	.string "each of the first six wins, you may cash\l"
	.string "out your prize money or risk it all on\l"
	.string "the next round. Win game seven to\l"
	.string "receive the top prize automatically. If\l"
	.string "you want to interrupt your challenge,\l"
	.string "please save the game. If you don't save,\l"
	.string "you will be disqualified from your\l"
	.string "challenge. Please be aware of that!$"

BattleArcade_Registration_EventScript_ExplainChallenge_Text_1:
# 85 "data/scripts/battle_arcade_registration.pory"
	.string "You may team up with a friend for a\n"
	.string "Multi Battle challenge. Here, a game\l"
	.string "board is activated before every match.\l"
	.string "Depending on what comes up on the game\l"
	.string "board, an event takes place. The events\l"
	.string "may have great impact on the match's\l"
	.string "outcome, good or bad. The objective is\l"
	.string "to keep a winning streak alive as long\l"
	.string "as possible. During your challenge, any\l"
	.string "items held by your Pokémon will be kept\l"
	.string "in storage. Please note: a Rocket\l"
	.string "Arcade Multi Battle challenge can't be\l"
	.string "interrupted.$"

BattleArcade_Registration_EventScript_TryEnterChallenge_Text_0:
# 92 "data/scripts/battle_arcade_registration.pory"
	.string "The Rocket Arcade offers two levels of\n"
	.string "challenge, Classic and Chaos. Which is\l"
	.string "your choice?$"

BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_0:
# 145 "data/scripts/battle_arcade_registration.pory"
	.string "Excuse me! You don't have\n"
	.string "{STR_VAR_2} eligible Pokémon. You\l"
	.string "must have {STR_VAR_2} different\l"
	.string "Pokémon to enter.$"

BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_1:
# 150 "data/scripts/battle_arcade_registration.pory"
	.string "The {STR_VAR_2} different Pokémon\n"
	.string "must all be eligible.$"

BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_2:
# 152 "data/scripts/battle_arcade_registration.pory"
	.string "Eggs{STR_VAR_1} are not allowed to\n"
	.string "enter.$"

BattleArcade_Registration_EventScript_GiveGoldPrint_Text_0:
# 288 "data/scripts/battle_arcade_registration.pory"
	.string "The Gold Print was added to\n"
	.string "{PLAYER}'s Vs. Recorder!$"

BattleArcade_Registration_EventScript_GiveSilverPrint_Text_0:
# 295 "data/scripts/battle_arcade_registration.pory"
	.string "The Silver Print was added to\n"
	.string "{PLAYER}'s Vs. Recorder!$"

BattleArcade_Registration_EventScript_QuitWithoutSaving_Text_0:
# 303 "data/scripts/battle_arcade_registration.pory"
	.string "Excuse me! You didn't save before you\n"
	.string "quit your challenge last time. Because\l"
	.string "of that, you have been disqualified\l"
	.string "from your challenge!$"

BattleArcade_Registration_EventScript_ResumeChallenge_Text_0:
# 363 "data/scripts/battle_arcade_registration.pory"
	.string "We've missed you! You must save the\n"
	.string "game before you resume your challenge.\l"
	.string "Please wait.$"

BattleArcade_Entrance_LinkMulti_EventScript_Cancel_Text_0:
# 377 "data/scripts/battle_arcade_registration.pory"
	.string "I'm sorry! Link Multi Battles have not\n"
	.string "been implemented at this time. Please\l"
	.string "come back later.$"

BattleArcade_Registration_EventScript_AskModeResultsBoard_Text_0:
# 386 "data/scripts/battle_arcade_registration.pory"
	.string "Which record would you like to see?$"

BattleArcade_Entrance_Text_CongratulationsInHonorOf::
# 413 "data/scripts/battle_arcade_registration.pory"
	.string "Congratulations! In honor of your\n"
	.string "victory, we present you with this\l"
	.string "commemorative print!$"

BattleArcade_Entrance_Text_OneTrainerShouldSelectBecome::
# 420 "data/scripts/battle_arcade_registration.pory"
	.string "One Trainer should select “Become\n"
	.string "Leader.” The other Trainer must select\l"
	.string "“Join Group.”$"

BattleArcade_Entrance_Text_WeNeedToLaunchDs::
# 424 "data/scripts/battle_arcade_registration.pory"
	.string "We need to launch DS Wireless\n"
	.string "Communications.$"

BattleArcade_Entrance_Text_YouMustSaveTheGame::
# 428 "data/scripts/battle_arcade_registration.pory"
	.string "You must save the game before I show\n"
	.string "you in. Please wait.$"
