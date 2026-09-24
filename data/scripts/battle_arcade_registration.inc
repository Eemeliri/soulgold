BattleArcade_Registration_EventScript_SinglesAttendant::
	setvar VAR_TEMP_2, FRONTIER_MODE_SINGLES
	goto BattleArcade_Registration_EventScript_Attendant
	return


BattleArcade_Registration_EventScript_MultisAttendant::
	setvar VAR_TEMP_2, FRONTIER_MODE_MULTIS
	goto BattleArcade_Registration_EventScript_Attendant
	return


BattleArcade_Registration_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARCADE
	special SavePlayerParty
	compare VAR_TEMP_2, FRONTIER_MODE_SINGLES
	goto_if_eq BattleArcade_Registration_EventScript_Attendant_1
	msgbox BattleArcade_Registration_EventScript_Attendant_Text_1, MSGBOX_DEFAULT
	goto BattleArcade_Registration_EventScript_AskEnterMultiChallenge
	return

BattleArcade_Registration_EventScript_Attendant_1:
	msgbox BattleArcade_Registration_EventScript_Attendant_Text_0
	goto BattleArcade_Registration_EventScript_AskEnterChallenge
	return


BattleArcade_Registration_EventScript_AskEnterChallenge::
	message BattleArcade_Registration_EventScript_AskEnterChallenge_Text_0
	waitmessage
	multichoice 17, 4, MULTI_CHALLENGE_TYPES_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleArcade_Registration_EventScript_AskEnterChallenge_2
	case 1, BattleArcade_Registration_EventScript_AskEnterChallenge_2
	case 2, BattleArcade_Registration_EventScript_AskEnterChallenge_3
	case 3, BattleArcade_Registration_EventScript_AskEnterChallenge_4
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_AskEnterChallenge_4
	return

BattleArcade_Registration_EventScript_AskEnterChallenge_2:
	copyvar VAR_FRONTIER_BATTLE_MODE, VAR_RESULT
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	return

BattleArcade_Registration_EventScript_AskEnterChallenge_3:
	goto BattleArcade_Registration_EventScript_ExplainChallenge
	return

BattleArcade_Registration_EventScript_AskEnterChallenge_4:
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_AskEnterMultiChallenge::
	message BattleArcade_Registration_EventScript_AskEnterMultiChallenge_Text_0
	waitmessage
	multichoice 17, 5, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_2
	case 1, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_3
	case 2, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_4
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_AskEnterMultiChallenge_4
	return

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_2:
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	return

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_3:
	goto BattleArcade_Registration_EventScript_ExplainChallenge
	return

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_4:
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_ExplainChallenge::
	compare VAR_TEMP_2, FRONTIER_MODE_SINGLES
	goto_if_eq BattleArcade_Registration_EventScript_ExplainChallenge_1
	msgbox BattleArcade_Registration_EventScript_ExplainChallenge_Text_1, MSGBOX_DEFAULT
	goto BattleArcade_Registration_EventScript_AskEnterMultiChallenge
	return

BattleArcade_Registration_EventScript_ExplainChallenge_1:
	msgbox BattleArcade_Registration_EventScript_ExplainChallenge_Text_0, MSGBOX_DEFAULT
	goto BattleArcade_Registration_EventScript_AskEnterChallenge
	return


BattleArcade_Registration_EventScript_TryEnterChallenge::
	message BattleArcade_Registration_EventScript_TryEnterChallenge_Text_0
	waitmessage
	multichoice 17, 2, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LEVEL_CHOICE_INNATES, BattleArcade_Registration_EventScript_TryEnterChallenge_3
	case FRONTIER_LEVEL_CHOICE_INFO, BattleArcade_Registration_EventScript_TryEnterChallenge_4
	case FRONTIER_LEVEL_CHOICE_BGM, BattleArcade_Registration_EventScript_TryEnterChallenge_5
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_TryEnterChallenge_6
BattleArcade_Registration_EventScript_TryEnterChallenge_1:
	frontier_checkineligible
	compare VAR_0x8004, 0
	goto_if_ne BattleArcade_Registration_EventScript_TryEnterChallenge_8
BattleArcade_Registration_EventScript_TryEnterChallenge_7:
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	frontier_get FRONTIER_DATA_LVL_MODE
	copyvar VAR_0x8004, VAR_RESULT
	call BattleArcade_Registration_EventScript_GetPartySize
	special ChoosePartyForBattleFrontier
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq BattleArcade_Registration_EventScript_TryEnterChallenge_11
BattleArcade_Registration_EventScript_TryEnterChallenge_10:
	goto BattleArcade_Registration_EventScript_SaveBeforeChallenge
	return

BattleArcade_Registration_EventScript_TryEnterChallenge_3:
	call BattleFrontier_EventScript_ChooseInnates
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_4:
	call BattleFrontier_EventScript_ShowLevelModeInfo
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_5:
	call BattleFrontier_EventScript_ChooseBattleBgm
	goto BattleArcade_Registration_EventScript_TryEnterChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_6:
	goto BattleArcade_Registration_EventScript_CancelChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_1

BattleArcade_Registration_EventScript_TryEnterChallenge_8:
	call BattleArcade_Registration_EventScript_GetPartySize
	goto BattleArcade_Registration_EventScript_NotEnoughValidMons
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_7

BattleArcade_Registration_EventScript_TryEnterChallenge_11:
	goto BattleArcade_Registration_EventScript_LoadPartyCancelChallenge
	goto BattleArcade_Registration_EventScript_TryEnterChallenge_10


BattleArcade_Registration_EventScript_GetPartySize::
	switch VAR_FRONTIER_BATTLE_MODE
	case FRONTIER_MODE_SINGLES, BattleArcade_Registration_EventScript_GetPartySize_3
	case FRONTIER_MODE_DOUBLES, BattleArcade_Registration_EventScript_GetPartySize_4
	case FRONTIER_MODE_LINK_MULTIS, BattleArcade_Registration_EventScript_GetPartySize_5
BattleArcade_Registration_EventScript_GetPartySize_1:
	return

BattleArcade_Registration_EventScript_GetPartySize_3:
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	goto BattleArcade_Registration_EventScript_GetPartySize_1

BattleArcade_Registration_EventScript_GetPartySize_4:
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	goto BattleArcade_Registration_EventScript_GetPartySize_1

BattleArcade_Registration_EventScript_GetPartySize_5:
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
	goto BattleArcade_Registration_EventScript_GetPartySize_1


BattleArcade_Registration_EventScript_NotEnoughValidMons::
	buffernumberstring STR_VAR_2, VAR_0x8005
	msgbox BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_0, MSGBOX_DEFAULT
	call BattleFrontier_EventScript_GetLvlMode
	compare VAR_RESULT, FRONTIER_LVL_50
	goto_if_eq BattleArcade_Registration_EventScript_NotEnoughValidMons_2
BattleArcade_Registration_EventScript_NotEnoughValidMons_1:
	msgbox BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_2, MSGBOX_DEFAULT
	closemessage
	end

BattleArcade_Registration_EventScript_NotEnoughValidMons_2:
	msgbox BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_1, MSGBOX_DEFAULT
	goto BattleArcade_Registration_EventScript_NotEnoughValidMons_1


BattleArcade_Registration_EventScript_LoadPartyCancelChallenge::
	special LoadPlayerParty
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_CancelChallenge::
	msgbox gText_WeHopeToSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	release
	end


BattleArcade_Registration_EventScript_SaveBeforeChallenge::
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	arcade_init
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
	goto_if_eq BattleArcade_Registration_EventScript_SaveBeforeChallenge_2
BattleArcade_Registration_EventScript_SaveBeforeChallenge_1:
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	compare VAR_RESULT, 0
	goto_if_eq BattleArcade_Registration_EventScript_SaveBeforeChallenge_5
BattleArcade_Registration_EventScript_SaveBeforeChallenge_4:
	call BattleArcade_Registration_EventScript_HandleMultiplayer
	goto BattleArcade_Registration_EventScript_EnterElevator
	return

BattleArcade_Registration_EventScript_SaveBeforeChallenge_2:
	arcade_save 0
	goto BattleArcade_Entrance_LinkMulti_EventScript_Cancel
	goto BattleArcade_Registration_EventScript_SaveBeforeChallenge_1

BattleArcade_Registration_EventScript_SaveBeforeChallenge_5:
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS
	goto BattleArcade_Registration_EventScript_CancelChallenge
	goto BattleArcade_Registration_EventScript_SaveBeforeChallenge_4


BattleArcade_Registration_EventScript_HandleMultiplayer::
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
	goto_if_ne BattleArcade_Registration_EventScript_HandleMultiplayer_2
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	compare VAR_RESULT, 0
	goto_if_ne BattleArcade_Registration_EventScript_HandleMultiplayer_5
BattleArcade_Registration_EventScript_HandleMultiplayer_4:
	goto BattleFrontier_BattleTowerLobby_EventScript_TryCableLink
	return

BattleArcade_Registration_EventScript_HandleMultiplayer_2:
	return

BattleArcade_Registration_EventScript_HandleMultiplayer_5:
	goto BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink
	goto BattleArcade_Registration_EventScript_HandleMultiplayer_4


BattleArcade_Registration_EventScript_EnterElevator::
	special SavePlayerParty
	setvar VAR_0x8004, FRONTIER_UTIL_FUNC_SET_PARTY_ORDER
	call BattleArcade_Registration_EventScript_GetPartySize
	special CallFrontierUtilFunc
	setvar VAR_RESULT, 0
	goto BattleArcade_Registration_EventScript_GoToHallway
	return


BattleArcade_Registration_EventScript_GoToHallway::
	call BattleArcade_Registration_EventScript_ShowYouToBattleRoom
	special HealPlayerParty
	call BattleArcade_Lobby_EventScript_WarpToHallway
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end


BattleArcade_Registration_EventScript_ShowYouToBattleRoom::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	call BattleArcade_Lobby_EventScript_WalkToElevator
	return


BattleArcade_Registration_EventScript_GetChallengeStatus::
	frontier_getstatus
	end


BattleArcade_Registration_EventScript_ResetChallengeStatus::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	return


BattleArcade_Registration_EventScript_WonChallenge::
	lock
	faceplayer
	frontier_isbrain
	compare VAR_RESULT, 0
	goto_if_ne BattleArcade_Registration_EventScript_WonChallenge_2
BattleArcade_Registration_EventScript_WonChallenge_1:
	call BattleArcade_Registration_EventScript_ResetChallengeStatus
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return

BattleArcade_Registration_EventScript_WonChallenge_2:
	call BattleArcade_Registration_EventScript_CheckStreakAndSymbols
	goto BattleArcade_Registration_EventScript_WonChallenge_1


BattleArcade_Registration_EventScript_CheckStreakAndSymbols::
	arcade_checksymbol
	switch VAR_RESULT
	case ARCADE_SYMBOL_SILVER, BattleArcade_Registration_EventScript_CheckStreakAndSymbols_2
	case ARCADE_SYMBOL_GOLD, BattleArcade_Registration_EventScript_CheckStreakAndSymbols_3
	case ARCADE_SYMBOL_NONE, BattleArcade_Registration_EventScript_CheckStreakAndSymbols_4
BattleArcade_Registration_EventScript_CheckStreakAndSymbols_4:
	return

BattleArcade_Registration_EventScript_CheckStreakAndSymbols_2:
	setflag FLAG_ARCADE_SILVER_PRINT
	return

BattleArcade_Registration_EventScript_CheckStreakAndSymbols_3:
	setflag FLAG_ARCADE_GOLD_PRINT
	return


BattleArcade_Registration_EventScript_GiveGoldPrint::
	msgbox BattleArcade_Entrance_Text_CongratulationsInHonorOf, MSGBOX_DEFAULT
	msgbox BattleArcade_Registration_EventScript_GiveGoldPrint_Text_0, MSGBOX_DEFAULT
	call BattleArcade_Registration_EventScript_GivePrint
	return


BattleArcade_Registration_EventScript_GiveSilverPrint::
	msgbox BattleArcade_Entrance_Text_CongratulationsInHonorOf, MSGBOX_DEFAULT
	msgbox BattleArcade_Registration_EventScript_GiveSilverPrint_Text_0, MSGBOX_DEFAULT
	call BattleArcade_Registration_EventScript_GivePrint
	return


BattleArcade_Registration_EventScript_QuitWithoutSaving::
	lock
	faceplayer
	msgbox BattleArcade_Registration_EventScript_QuitWithoutSaving_Text_0, MSGBOX_DEFAULT
	closemessage
	arcade_set ARCADE_DATA_WIN_STREAK, 0
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	release
	end


BattleArcade_Registration_EventScript_GivePrint::
	call BattleArcade_Registration_EventScript_CheckandGivePrint
	call BattleArcade_Registration_EventScript_PlayFanfareMessage
	return


BattleArcade_Registration_EventScript_CheckandGivePrint::
	goto_if_set FLAG_ARCADE_SILVER_PRINT, BattleArcade_Registration_EventScript_CheckandGivePrint_1
	setflag FLAG_ARCADE_SILVER_PRINT
	return

BattleArcade_Registration_EventScript_CheckandGivePrint_1:
	setflag FLAG_ARCADE_GOLD_PRINT
	return


BattleArcade_Registration_EventScript_PlayFanfareMessage::
	playfanfare MUS_OBTAIN_SYMBOL
	waitmessage
	waitfanfare
	return


BattleArcade_Registration_EventScript_LostChallenge::
	arcade_get ARCADE_DATA_WIN_STREAK
	compare VAR_RESULT, 0
	goto_if_ne BattleArcade_Registration_EventScript_LostChallenge_2
BattleArcade_Registration_EventScript_LostChallenge_1:
	call BattleArcade_Registration_EventScript_ResetChallengeStatus
	goto BattleArcade_Registration_EventScript_LostThanksForPlaying
	return

BattleArcade_Registration_EventScript_LostChallenge_2:
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, FALSE
	goto BattleArcade_Registration_EventScript_LostChallenge_1


BattleArcade_Registration_EventScript_LostThanksForPlaying::
	lock
	faceplayer
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_ResumeChallenge::
	lock
	faceplayer
	message BattleArcade_Registration_EventScript_ResumeChallenge_Text_0
	waitmessage
	arcade_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	goto BattleArcade_Registration_EventScript_EnterElevator
	end


BattleArcade_Entrance_LinkMulti_EventScript_Cancel::
	msgbox BattleArcade_Entrance_LinkMulti_EventScript_Cancel_Text_0
	closemessage
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS
	goto BattleArcade_Registration_EventScript_CancelChallenge
	return


BattleArcade_Registration_EventScript_AskModeResultsBoard::
	lockall
	message BattleArcade_Registration_EventScript_AskModeResultsBoard_Text_0
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARCADE_RECORDS, FALSE
	switch VAR_RESULT
	case 2, BattleArcade_Registration_EventScript_AskModeResultsBoard_2
	case MULTI_B_PRESSED, BattleArcade_Registration_EventScript_AskModeResultsBoard_2
	goto BattleArcade_Registration_EventScript_ShowResults
	return

BattleArcade_Registration_EventScript_AskModeResultsBoard_2:
	closemessage
	releaseall
	end


BattleArcade_Registration_EventScript_ShowResults::
	closemessage
	copyvar VAR_0x8006, VAR_RESULT
	fadescreen FADE_TO_BLACK
	arcade_results VAR_0x8006
	waitstate
	goto BattleArcade_Registration_EventScript_AskModeResultsBoard
	return


BattleArcade_Registration_EventScript_Attendant_Text_0:
	.string "Welcome to the Rocket Arcade! I am your\n"
	.string "guide to the Single and Double Battle\l"
	.string "challenges. Please be aware that these\l"
	.string "challenges are designed for a single\l"
	.string "Trainer.$"

BattleArcade_Registration_EventScript_Attendant_Text_1:
	.string "Welcome to the Rocket Arcade! I am your\n"
	.string "guide to the Multi Battle challenge.\l"
	.string "Please be aware that this challenge\l"
	.string "requires two Trainers.$"

BattleArcade_Registration_EventScript_AskEnterChallenge_Text_0:
	.string "Which challenge would you like to take?$"

BattleArcade_Registration_EventScript_AskEnterMultiChallenge_Text_0:
	.string "Would you like to take the Rocket\n"
	.string "Arcade Multi Battle challenge?$"

BattleArcade_Registration_EventScript_ExplainChallenge_Text_0:
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
	.string "The Rocket Arcade offers two levels of\n"
	.string "challenge, Classic and Chaos. Which is\l"
	.string "your choice?$"

BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_0:
	.string "Excuse me! You don't have\n"
	.string "{STR_VAR_2} eligible Pokémon. You\l"
	.string "must have {STR_VAR_2} different\l"
	.string "Pokémon to enter.$"

BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_1:
	.string "The {STR_VAR_2} different Pokémon\n"
	.string "must all be eligible.$"

BattleArcade_Registration_EventScript_NotEnoughValidMons_Text_2:
	.string "Eggs{STR_VAR_1} are not allowed to\n"
	.string "enter.$"

BattleArcade_Registration_EventScript_GiveGoldPrint_Text_0:
	.string "The Gold Print was added to\n"
	.string "{PLAYER}'s Vs. Recorder!$"

BattleArcade_Registration_EventScript_GiveSilverPrint_Text_0:
	.string "The Silver Print was added to\n"
	.string "{PLAYER}'s Vs. Recorder!$"

BattleArcade_Registration_EventScript_QuitWithoutSaving_Text_0:
	.string "Excuse me! You didn't save before you\n"
	.string "quit your challenge last time. Because\l"
	.string "of that, you have been disqualified\l"
	.string "from your challenge!$"

BattleArcade_Registration_EventScript_ResumeChallenge_Text_0:
	.string "We've missed you! You must save the\n"
	.string "game before you resume your challenge.\l"
	.string "Please wait.$"

BattleArcade_Entrance_LinkMulti_EventScript_Cancel_Text_0:
	.string "I'm sorry! Link Multi Battles have not\n"
	.string "been implemented at this time. Please\l"
	.string "come back later.$"

BattleArcade_Registration_EventScript_AskModeResultsBoard_Text_0:
	.string "Which record would you like to see?$"

BattleArcade_Entrance_Text_CongratulationsInHonorOf::
	.string "Congratulations! In honor of your\n"
	.string "victory, we present you with this\l"
	.string "commemorative print!$"

BattleArcade_Entrance_Text_OneTrainerShouldSelectBecome::
	.string "One Trainer should select “Become\n"
	.string "Leader.” The other Trainer must select\l"
	.string "“Join Group.”$"

BattleArcade_Entrance_Text_WeNeedToLaunchDs::
	.string "We need to launch DS Wireless\n"
	.string "Communications.$"

BattleArcade_Entrance_Text_YouMustSaveTheGame::
	.string "You must save the game before I show\n"
	.string "you in. Please wait.$"
