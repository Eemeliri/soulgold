
BattleCafe_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleCafe_OnTransition
	.byte 0

BattleCafe_OnTransition::
	setflag FLAG_HIDE_BATTLE_CAFE_OPPONENT
	setflag FLAG_VISITED_ROUTE50
	end


BattleCafe_Owner::
	lock
	faceplayer
	goto_if_unset FLAG_BATTLE_CAFE_DIANCIE_RECEIVED, BattleCafe_Owner_4
BattleCafe_Owner_1:
	goto BattleCafe_OwnerMenu
	return

BattleCafe_Owner_2:
	goto BattleCafe_GiveDiancie
	goto BattleCafe_Owner_1

BattleCafe_Owner_3:
	checktrainerflag TRAINER_CAFE_DOVES
	goto_if 1, BattleCafe_Owner_8
	goto BattleCafe_Owner_1

BattleCafe_Owner_4:
	checktrainerflag TRAINER_CAFE_ATHENA
	goto_if 1, BattleCafe_Owner_3
	goto BattleCafe_Owner_1

BattleCafe_Owner_7:
	checktrainerflag TRAINER_CAFE_NEM
	goto_if 1, BattleCafe_Owner_12
	goto BattleCafe_Owner_1

BattleCafe_Owner_8:
	checktrainerflag TRAINER_CAFE_ELTON
	goto_if 1, BattleCafe_Owner_7
	goto BattleCafe_Owner_1

BattleCafe_Owner_11:
	checktrainerflag TRAINER_CAFE_DRAC
	goto_if 1, BattleCafe_Owner_16
	goto BattleCafe_Owner_1

BattleCafe_Owner_12:
	checktrainerflag TRAINER_CAFE_BAI
	goto_if 1, BattleCafe_Owner_11
	goto BattleCafe_Owner_1

BattleCafe_Owner_15:
	checktrainerflag TRAINER_CAFE_TYLARIE
	goto_if 1, BattleCafe_Owner_2
	goto BattleCafe_Owner_1

BattleCafe_Owner_16:
	checktrainerflag TRAINER_CAFE_JUNA
	goto_if 1, BattleCafe_Owner_15
	goto BattleCafe_Owner_1


BattleCafe_GiveDiancie::
	goto_if_unset FLAG_BATTLE_CAFE_DIANCIE_READY, BattleCafe_GiveDiancie_2
	msgbox BattleCafe_GiveDiancie_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_GiveDiancie_5
BattleCafe_GiveDiancie_4:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DIANCIE
	bufferspeciesname STR_VAR_1, SPECIES_DIANCIE
	givemon SPECIES_DIANCIE, 70
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq BattleCafe_GiveDiancie_8
BattleCafe_GiveDiancie_7:
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	clearflag FLAG_BATTLE_CAFE_DIANCIE_READY
	setflag FLAG_BATTLE_CAFE_DIANCIE_RECEIVED
	msgbox BattleCafe_GiveDiancie_Text_4
	goto BattleCafe_OwnerMenu
	return

BattleCafe_GiveDiancie_2:
	msgbox BattleCafe_GiveDiancie_Text_0
	msgbox BattleCafe_GiveDiancie_Text_1
	setflag FLAG_BATTLE_CAFE_DIANCIE_READY
	release
	end

BattleCafe_GiveDiancie_5:
	msgbox BattleCafe_GiveDiancie_Text_3
	goto BattleCafe_OwnerMenu
	goto BattleCafe_GiveDiancie_4

BattleCafe_GiveDiancie_8:
	goto Common_EventScript_NoMoreRoomForPokemon
	goto BattleCafe_GiveDiancie_7


BattleCafe_OwnerMenu::
	goto_if_unset FLAG_CAFE_INTRO_DONE, BattleCafe_OwnerMenu_2
BattleCafe_OwnerMenu_1:
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_OwnerMenu_6
BattleCafe_OwnerMenu_4:
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_OwnerMenu_11
BattleCafe_OwnerMenu_9:
	msgbox BattleCafe_OwnerMenu_Text_3
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_OwnerMenu_15
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_OwnerMenu_15
BattleCafe_OwnerMenu_14:
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_OwnerMenu_Text_4, BattleCafe_OwnerMenu_Text_5, BattleCafe_OwnerMenu_Text_6, BattleCafe_OwnerMenu_Text_7, BattleCafe_OwnerMenu_Text_9, BattleCafe_OwnerMenu_Text_10, BattleCafe_OwnerMenu_Text_11
	switch VAR_RESULT
	case 0, BattleCafe_OwnerMenu_20
	case 1, BattleCafe_OwnerMenu_21
	case 2, BattleCafe_OwnerMenu_22
	case 3, BattleCafe_OwnerMenu_23
	case 4, BattleCafe_OwnerMenu_24
	case 5, BattleCafe_OwnerMenu_25
	goto BattleCafe_Goodbye
	return

BattleCafe_OwnerMenu_2:
	msgbox BattleCafe_OwnerMenu_Text_0
	setflag FLAG_CAFE_INTRO_DONE
	goto BattleCafe_OwnerMenu_1

BattleCafe_OwnerMenu_5:
	msgbox BattleCafe_OwnerMenu_Text_1
	setflag FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED
	goto BattleCafe_OwnerMenu_4

BattleCafe_OwnerMenu_6:
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_CHALLENGE_WON, BattleCafe_OwnerMenu_5
	goto BattleCafe_OwnerMenu_4

BattleCafe_OwnerMenu_10:
	msgbox BattleCafe_OwnerMenu_Text_2
	setflag FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED
	goto BattleCafe_OwnerMenu_9

BattleCafe_OwnerMenu_11:
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_RUSH_WON, BattleCafe_OwnerMenu_10
	goto BattleCafe_OwnerMenu_9

BattleCafe_OwnerMenu_15:
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_OwnerMenu_Text_4, BattleCafe_OwnerMenu_Text_5, BattleCafe_OwnerMenu_Text_6, BattleCafe_OwnerMenu_Text_7, BattleCafe_OwnerMenu_Text_8, BattleCafe_OwnerMenu_Text_9, BattleCafe_OwnerMenu_Text_10, BattleCafe_OwnerMenu_Text_11
	switch VAR_RESULT
	case 0, BattleCafe_OwnerMenu_28
	case 1, BattleCafe_OwnerMenu_29
	case 2, BattleCafe_OwnerMenu_30
	case 3, BattleCafe_OwnerMenu_31
	case 4, BattleCafe_OwnerMenu_32
	case 5, BattleCafe_OwnerMenu_33
	case 6, BattleCafe_OwnerMenu_34
	goto BattleCafe_Goodbye
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_20:
	goto BattleCafe_AskDailyChallenge
	return

BattleCafe_OwnerMenu_21:
	goto BattleCafe_AskRushMode
	return

BattleCafe_OwnerMenu_22:
	goto BattleCafe_AskSuperChallenge
	return

BattleCafe_OwnerMenu_23:
	goto BattleCafe_AskSuperRush
	return

BattleCafe_OwnerMenu_24:
	goto BattleCafe_RewardMenu
	return

BattleCafe_OwnerMenu_25:
	goto BattleCafe_OptionsMenu
	return

BattleCafe_OwnerMenu_28:
	goto BattleCafe_AskDailyChallenge
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_29:
	goto BattleCafe_AskRushMode
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_30:
	goto BattleCafe_AskSuperChallenge
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_31:
	goto BattleCafe_AskSuperRush
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_32:
	goto BattleCafe_EndlessMenu
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_33:
	goto BattleCafe_RewardMenu
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_34:
	goto BattleCafe_OptionsMenu
	goto BattleCafe_OwnerMenu_14


BattleCafe_OptionsMenu::
	msgbox BattleCafe_OptionsMenu_Text_0
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_OptionsMenu_Text_1, BattleCafe_OptionsMenu_Text_2, BattleCafe_OptionsMenu_Text_3, BattleCafe_OptionsMenu_Text_4, BattleCafe_OptionsMenu_Text_5
	switch VAR_RESULT
	case 0, BattleCafe_OptionsMenu_2
	case 1, BattleCafe_OptionsMenu_3
	case 2, BattleCafe_OptionsMenu_4
	case 3, BattleCafe_OptionsMenu_5
	goto BattleCafe_OwnerMenu
	return

BattleCafe_OptionsMenu_2:
	goto BattleCafe_ChooseBattleBgm
	return

BattleCafe_OptionsMenu_3:
	goto BattleCafe_ViewHighScores
	return

BattleCafe_OptionsMenu_4:
	goto BattleCafe_ChooseInnates
	return

BattleCafe_OptionsMenu_5:
	goto BattleCafe_ExplainRules
	return


BattleCafe_ChooseBattleBgm::
	call BattleFrontier_EventScript_ChooseBattleBgm
	goto BattleCafe_OwnerMenu
	return


BattleCafe_ViewHighScores::
	closemessage
	special BattleCafe_ShowRecordsWindow
	waitbuttonpress
	special RemoveRecordsWindow
	goto BattleCafe_OwnerMenu
	return


BattleCafe_ChooseInnates::
	call BattleFrontier_EventScript_ChooseInnates
	goto BattleCafe_OptionsMenu
	return


BattleCafe_ExplainRules::
	msgbox BattleCafe_ExplainRules_Text_0
	msgbox BattleCafe_ExplainRules_Text_1
	msgbox BattleCafe_ExplainRules_Text_2
	msgbox BattleCafe_ExplainRules_Text_3
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_ExplainRules_2
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_ExplainRules_2
BattleCafe_ExplainRules_1:
	goto BattleCafe_OwnerMenu
	return

BattleCafe_ExplainRules_2:
	msgbox BattleCafe_ExplainRules_Text_4
	msgbox BattleCafe_ExplainRules_Text_5
	goto BattleCafe_ExplainRules_1


BattleCafe_AskDailyChallenge::
	goto_if_set FLAG_DAILY_BATTLE_CAFE_CHALLENGE_WON, BattleCafe_AskDailyChallenge_2
BattleCafe_AskDailyChallenge_1:
	msgbox BattleCafe_AskDailyChallenge_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskDailyChallenge_5
BattleCafe_AskDailyChallenge_4:
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskDailyChallenge_2:
	msgbox BattleCafe_AskDailyChallenge_Text_0
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskDailyChallenge_1

BattleCafe_AskDailyChallenge_5:
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskDailyChallenge_4


BattleCafe_AskRushMode::
	goto_if_set FLAG_DAILY_BATTLE_CAFE_RUSH_WON, BattleCafe_AskRushMode_2
BattleCafe_AskRushMode_1:
	msgbox BattleCafe_AskRushMode_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskRushMode_5
BattleCafe_AskRushMode_4:
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_RUSH
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskRushMode_2:
	msgbox BattleCafe_AskRushMode_Text_0
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskRushMode_1

BattleCafe_AskRushMode_5:
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskRushMode_4


BattleCafe_AskSuperChallenge::
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_CHALLENGE_WON, BattleCafe_AskSuperChallenge_2
BattleCafe_AskSuperChallenge_1:
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskSuperChallenge_5
BattleCafe_AskSuperChallenge_4:
	msgbox BattleCafe_AskSuperChallenge_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskSuperChallenge_8
BattleCafe_AskSuperChallenge_7:
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_CHALLENGE
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskSuperChallenge_2:
	msgbox BattleCafe_AskSuperChallenge_Text_0
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperChallenge_1

BattleCafe_AskSuperChallenge_5:
	msgbox BattleCafe_AskSuperChallenge_Text_1
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperChallenge_4

BattleCafe_AskSuperChallenge_8:
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperChallenge_7


BattleCafe_AskSuperRush::
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_RUSH_WON, BattleCafe_AskSuperRush_2
BattleCafe_AskSuperRush_1:
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskSuperRush_5
BattleCafe_AskSuperRush_4:
	msgbox BattleCafe_AskSuperRush_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskSuperRush_8
BattleCafe_AskSuperRush_7:
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_RUSH
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskSuperRush_2:
	msgbox BattleCafe_AskSuperRush_Text_0
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperRush_1

BattleCafe_AskSuperRush_5:
	msgbox BattleCafe_AskSuperRush_Text_1
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperRush_4

BattleCafe_AskSuperRush_8:
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperRush_7


BattleCafe_EndlessMenu::
	msgbox BattleCafe_EndlessMenu_Text_0
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_EndlessMenu_Text_1, BattleCafe_EndlessMenu_Text_2, BattleCafe_EndlessMenu_Text_3, BattleCafe_OptionsMenu_Text_5
	switch VAR_RESULT
	case 0, BattleCafe_EndlessMenu_2
	case 1, BattleCafe_EndlessMenu_3
	case 2, BattleCafe_EndlessMenu_4
	goto BattleCafe_OwnerMenu
	return

BattleCafe_EndlessMenu_2:
	goto BattleCafe_AskEndlessChallenge
	return

BattleCafe_EndlessMenu_3:
	goto BattleCafe_AskEndlessRush
	return

BattleCafe_EndlessMenu_4:
	goto BattleCafe_ExplainEndlessRules
	return


BattleCafe_ExplainEndlessRules::
	msgbox BattleCafe_ExplainEndlessRules_Text_0
	msgbox BattleCafe_ExplainEndlessRules_Text_1
	msgbox BattleCafe_ExplainEndlessRules_Text_2
	goto BattleCafe_EndlessMenu
	return


BattleCafe_AskEndlessChallenge::
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_AskEndlessChallenge_2
BattleCafe_AskEndlessChallenge_1:
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskEndlessChallenge_5
BattleCafe_AskEndlessChallenge_4:
	msgbox BattleCafe_AskEndlessChallenge_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskEndlessChallenge_8
BattleCafe_AskEndlessChallenge_7:
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskEndlessChallenge_2:
	msgbox BattleCafe_AskEndlessChallenge_Text_0
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessChallenge_1

BattleCafe_AskEndlessChallenge_5:
	msgbox BattleCafe_AskEndlessChallenge_Text_1
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessChallenge_4

BattleCafe_AskEndlessChallenge_8:
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessChallenge_7


BattleCafe_AskEndlessRush::
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_AskEndlessRush_2
BattleCafe_AskEndlessRush_1:
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskEndlessRush_5
BattleCafe_AskEndlessRush_4:
	msgbox BattleCafe_AskEndlessRush_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskEndlessRush_8
BattleCafe_AskEndlessRush_7:
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskEndlessRush_2:
	msgbox BattleCafe_AskEndlessRush_Text_0
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessRush_1

BattleCafe_AskEndlessRush_5:
	msgbox BattleCafe_AskEndlessChallenge_Text_1
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessRush_4

BattleCafe_AskEndlessRush_8:
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessRush_7


BattleCafe_BeginChallenge::
	closemessage
	hidefollower
	special HealPlayerParty
	special BattleCafe_InitChallenge
	moveobjecttocoords LOCALID_PLAYER, 6, 13, DIR_EAST
	waitmovement 0
	setvar VAR_TEMP_9, 0
	setvar VAR_TEMP_C, 0
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
	goto_if_eq BattleCafe_BeginChallenge_2
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
	goto_if_eq BattleCafe_BeginChallenge_2
	msgbox BattleCafe_BeginChallenge_Text_1
BattleCafe_BeginChallenge_1:
	closemessage
	goto BattleCafe_ChallengeNextRound
	return

BattleCafe_BeginChallenge_2:
	msgbox BattleCafe_BeginChallenge_Text_0
	goto BattleCafe_BeginChallenge_1


BattleCafe_ChallengeNextRound::
	call BattleCafe_RunRound
	compare VAR_RESULT, TRUE
	goto_if_ne BattleCafe_ChallengeNextRound_2
BattleCafe_ChallengeNextRound_1:
	special BattleCafe_AdvanceWinCount
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
	goto_if_eq BattleCafe_ChallengeNextRound_5
BattleCafe_ChallengeNextRound_4:
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
	goto_if_eq BattleCafe_ChallengeNextRound_8
BattleCafe_ChallengeNextRound_7:
	compare VAR_TEMP_9, 3
	goto_if_ge BattleCafe_ChallengeNextRound_14
BattleCafe_ChallengeNextRound_13:
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY
	goto_if_eq BattleCafe_ChallengeNextRound_21
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_CHALLENGE
	goto_if_eq BattleCafe_ChallengeNextRound_27
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_RUSH
	goto_if_eq BattleCafe_ChallengeNextRound_30
	msgbox BattleCafe_ChallengeNextRound_Text_6
BattleCafe_ChallengeNextRound_20:
	closemessage
	goto BattleCafe_ChallengeNextRound
	return

BattleCafe_ChallengeNextRound_2:
	goto BattleCafe_ChallengeLost
	goto BattleCafe_ChallengeNextRound_1

BattleCafe_ChallengeNextRound_5:
	setvar VAR_0x8004, 1
	special BattleCafe_AwardPoints
	copyvar VAR_TEMP_B, VAR_RESULT
	special HealPlayerParty
	playse SE_SHOP
	waitse
	buffernumberstring STR_VAR_1, VAR_TEMP_9
	buffernumberstring STR_VAR_2, VAR_TEMP_B
	msgbox BattleCafe_ChallengeNextRound_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChallengeNextRound_11
BattleCafe_ChallengeNextRound_10:
	closemessage
	goto BattleCafe_ChallengeNextRound
	goto BattleCafe_ChallengeNextRound_4

BattleCafe_ChallengeNextRound_8:
	setvar VAR_0x8004, 2
	special BattleCafe_AwardPoints
	copyvar VAR_TEMP_B, VAR_RESULT
	addvar VAR_TEMP_C, 1
	playse SE_SHOP
	waitse
	buffernumberstring STR_VAR_1, VAR_TEMP_9
	buffernumberstring STR_VAR_2, VAR_TEMP_B
	compare VAR_TEMP_C, 3
	goto_if_ge BattleCafe_ChallengeNextRound_17
	msgbox BattleCafe_ChallengeNextRound_Text_2, MSGBOX_YESNO
BattleCafe_ChallengeNextRound_16:
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChallengeNextRound_25
BattleCafe_ChallengeNextRound_24:
	closemessage
	goto BattleCafe_ChallengeNextRound
	goto BattleCafe_ChallengeNextRound_7

BattleCafe_ChallengeNextRound_11:
	goto BattleCafe_EndlessRetired
	goto BattleCafe_ChallengeNextRound_10

BattleCafe_ChallengeNextRound_14:
	goto BattleCafe_ChallengeWon
	goto BattleCafe_ChallengeNextRound_13

BattleCafe_ChallengeNextRound_17:
	setvar VAR_TEMP_C, 0
	special HealPlayerParty
	playse SE_USE_ITEM
	msgbox BattleCafe_ChallengeNextRound_Text_1, MSGBOX_YESNO
	goto BattleCafe_ChallengeNextRound_16

BattleCafe_ChallengeNextRound_21:
	special HealPlayerParty
	playse SE_USE_ITEM
	msgbox BattleCafe_ChallengeNextRound_Text_3
	goto BattleCafe_ChallengeNextRound_20

BattleCafe_ChallengeNextRound_25:
	goto BattleCafe_EndlessRetired
	goto BattleCafe_ChallengeNextRound_24

BattleCafe_ChallengeNextRound_27:
	special HealPlayerParty
	playse SE_USE_ITEM
	msgbox BattleCafe_ChallengeNextRound_Text_4
	goto BattleCafe_ChallengeNextRound_20

BattleCafe_ChallengeNextRound_30:
	msgbox BattleCafe_ChallengeNextRound_Text_5
	goto BattleCafe_ChallengeNextRound_20


BattleCafe_EndlessRetired::
	closemessage
	special BattleCafe_EndChallenge
	special HealPlayerParty
	moveobjecttocoords LOCALID_PLAYER, 6, 24, DIR_NORTH
	waitmovement 0
	turnobject LOCALID_CAFE_OWNER, DIR_SOUTH
	buffernumberstring STR_VAR_1, VAR_TEMP_9
	msgbox BattleCafe_EndlessRetired_Text_0
	goto BattleCafe_OwnerMenu
	return


BattleCafe_RunRound::
	copyvar VAR_0x8004, VAR_TEMP_9
	special BattleCafe_SelectOpponent
	setobjectxy LOCALID_BATTLE_CAFE_OPPONENT, 14, 17
	addobject LOCALID_BATTLE_CAFE_OPPONENT
	moveobjecttocoords LOCALID_BATTLE_CAFE_OPPONENT, 10, 13, DIR_WEST
	waitmovement 0
	tower_getopponentintro FRONTIER_BEFORE_TEXT
	msgbox gStringVar4
	closemessage
	dofacilitytrainerbattle FACILITY_BATTLE_CAFE
	waitstate
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	copyvar VAR_TEMP_A, VAR_RESULT
	moveobjecttocoords LOCALID_BATTLE_CAFE_OPPONENT, 14, 17, DIR_EAST
	waitmovement 0
	removeobject LOCALID_BATTLE_CAFE_OPPONENT
	compare VAR_TEMP_A, B_OUTCOME_WON
	goto_if_eq BattleCafe_RunRound_2
	setvar VAR_RESULT, FALSE
BattleCafe_RunRound_1:
	return

BattleCafe_RunRound_2:
	setvar VAR_RESULT, TRUE
	goto BattleCafe_RunRound_1


BattleCafe_ChallengeLost::
	special BattleCafe_EndChallenge
	special HealPlayerParty
	moveobjecttocoords LOCALID_PLAYER, 6, 24, DIR_NORTH
	waitmovement 0
	turnobject LOCALID_CAFE_OWNER, DIR_SOUTH
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
	goto_if_eq BattleCafe_ChallengeLost_2
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
	goto_if_eq BattleCafe_ChallengeLost_2
	msgbox BattleCafe_ChallengeLost_Text_1
BattleCafe_ChallengeLost_1:
	goto BattleCafe_OwnerMenu
	return

BattleCafe_ChallengeLost_2:
	buffernumberstring STR_VAR_1, VAR_TEMP_9
	msgbox BattleCafe_ChallengeLost_Text_0
	goto BattleCafe_ChallengeLost_1


BattleCafe_ChallengeWon::
	special BattleCafe_EndChallenge
	special HealPlayerParty
	moveobjecttocoords LOCALID_PLAYER, 6, 24, DIR_NORTH
	waitmovement 0
	turnobject LOCALID_CAFE_OWNER, DIR_SOUTH
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY
	goto_if_eq BattleCafe_ChallengeWon_2
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_RUSH
	goto_if_eq BattleCafe_ChallengeWon_5
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_CHALLENGE
	goto_if_eq BattleCafe_ChallengeWon_8
	setflag FLAG_DAILY_BATTLE_CAFE_SUPER_RUSH_WON
	setvar VAR_0x8004, 10
	special BattleCafe_AwardPoints
	copyvar VAR_TEMP_B, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_TEMP_B
	msgbox BattleCafe_ChallengeWon_Text_3
BattleCafe_ChallengeWon_1:
	special BattleCafe_UnlockClearAchievement
	playse SE_SHOP
	waitse
	goto BattleCafe_OwnerMenu
	return

BattleCafe_ChallengeWon_2:
	setflag FLAG_DAILY_BATTLE_CAFE_CHALLENGE_WON
	setvar VAR_0x8004, 3
	special BattleCafe_AwardPoints
	copyvar VAR_TEMP_B, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_TEMP_B
	msgbox BattleCafe_ChallengeWon_Text_0
	goto BattleCafe_ChallengeWon_1

BattleCafe_ChallengeWon_5:
	setflag FLAG_DAILY_BATTLE_CAFE_RUSH_WON
	setvar VAR_0x8004, 5
	special BattleCafe_AwardPoints
	copyvar VAR_TEMP_B, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_TEMP_B
	msgbox BattleCafe_ChallengeWon_Text_1
	goto BattleCafe_ChallengeWon_1

BattleCafe_ChallengeWon_8:
	setflag FLAG_DAILY_BATTLE_CAFE_SUPER_CHALLENGE_WON
	setvar VAR_0x8004, 5
	special BattleCafe_AwardPoints
	copyvar VAR_TEMP_B, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_TEMP_B
	msgbox BattleCafe_ChallengeWon_Text_2
	goto BattleCafe_ChallengeWon_1


BattleCafe_RewardMenu::
	buffernumberstring STR_VAR_1, VAR_BATTLE_CAFE_POINTS
	msgbox BattleCafe_RewardMenu_Text_0
	special BattleCafe_GetParadoxRewardEligibility
	copyvar VAR_TEMP_C, VAR_RESULT
	dynmultipush BattleCafe_RewardMenu_Text_1, 10
	dynmultipush BattleCafe_RewardMenu_Text_2, 11
	dynmultipush BattleCafe_RewardMenu_Text_3, 12
	dynmultipush BattleCafe_RewardMenu_Text_4, 7
	dynmultipush BattleCafe_RewardMenu_Text_5, 8
	dynmultipush BattleCafe_RewardMenu_Text_6, 9
	dynmultipush BattleCafe_RewardMenu_Text_7, 0
	dynmultipush BattleCafe_RewardMenu_Text_8, 1
	dynmultipush BattleCafe_RewardMenu_Text_9, 2
	dynmultipush BattleCafe_RewardMenu_Text_10, 3
	dynmultipush BattleCafe_RewardMenu_Text_11, 4
	dynmultipush BattleCafe_RewardMenu_Text_12, 5
	dynmultipush BattleCafe_RewardMenu_Text_13, 6
	dynmultipush BattleCafe_RewardMenu_Text_14, 16
	dynmultipush BattleCafe_RewardMenu_Text_15, 17
	dynmultipush BattleCafe_RewardMenu_Text_16, 18
	dynmultipush BattleCafe_RewardMenu_Text_17, 19
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_MIRAIDON
	goto_if_eq BattleCafe_RewardMenu_2
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_MIRAIDON + BATTLE_CAFE_PARADOX_REWARD_KORAIDON
	goto_if_eq BattleCafe_RewardMenu_2
BattleCafe_RewardMenu_1:
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_KORAIDON
	goto_if_eq BattleCafe_RewardMenu_7
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_MIRAIDON + BATTLE_CAFE_PARADOX_REWARD_KORAIDON
	goto_if_eq BattleCafe_RewardMenu_7
BattleCafe_RewardMenu_6:
	dynmultipush BattleCafe_OptionsMenu_Text_5, 15
	dynmultistack 0, 0, FALSE, 6, FALSE, 10, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, BattleCafe_RewardMenu_12
	case 1, BattleCafe_RewardMenu_13
	case 2, BattleCafe_RewardMenu_14
	case 3, BattleCafe_RewardMenu_15
	case 4, BattleCafe_RewardMenu_16
	case 5, BattleCafe_RewardMenu_17
	case 6, BattleCafe_RewardMenu_18
	case 7, BattleCafe_RewardMenu_19
	case 8, BattleCafe_RewardMenu_20
	case 9, BattleCafe_RewardMenu_21
	case 10, BattleCafe_RewardMenu_22
	case 11, BattleCafe_RewardMenu_23
	case 12, BattleCafe_RewardMenu_24
	case 13, BattleCafe_RewardMenu_25
	case 14, BattleCafe_RewardMenu_26
	case 16, BattleCafe_RewardMenu_27
	case 17, BattleCafe_RewardMenu_28
	case 18, BattleCafe_RewardMenu_29
	case 19, BattleCafe_RewardMenu_30
	goto BattleCafe_OwnerMenu
	return

BattleCafe_RewardMenu_2:
	dynmultipush BattleCafe_RewardMenu_Text_18, 13
	goto BattleCafe_RewardMenu_1

BattleCafe_RewardMenu_7:
	dynmultipush BattleCafe_RewardMenu_Text_19, 14
	goto BattleCafe_RewardMenu_6

BattleCafe_RewardMenu_12:
	goto BattleCafe_ChooseArticuno
	return

BattleCafe_RewardMenu_13:
	goto BattleCafe_ChooseZapdos
	return

BattleCafe_RewardMenu_14:
	goto BattleCafe_ChooseMoltres
	return

BattleCafe_RewardMenu_15:
	goto BattleCafe_ChooseTornadus
	return

BattleCafe_RewardMenu_16:
	goto BattleCafe_ChooseThundurus
	return

BattleCafe_RewardMenu_17:
	goto BattleCafe_ChooseLandorus
	return

BattleCafe_RewardMenu_18:
	goto BattleCafe_ChooseEnamorus
	return

BattleCafe_RewardMenu_19:
	goto BattleCafe_ChooseShinyGenome
	return

BattleCafe_RewardMenu_20:
	goto BattleCafe_ChooseGoldBottleCaps
	return

BattleCafe_RewardMenu_21:
	goto BattleCafe_ChooseMoney
	return

BattleCafe_RewardMenu_22:
	goto BattleCafe_ChooseVitaminSetAtk
	return

BattleCafe_RewardMenu_23:
	goto BattleCafe_ChooseVitaminSetDef
	return

BattleCafe_RewardMenu_24:
	goto BattleCafe_ChooseVitaminSetSpe
	return

BattleCafe_RewardMenu_25:
	goto BattleCafe_ChooseMiraidon
	return

BattleCafe_RewardMenu_26:
	goto BattleCafe_ChooseKoraidon
	return

BattleCafe_RewardMenu_27:
	goto BattleCafe_ChooseTapuKoko
	return

BattleCafe_RewardMenu_28:
	goto BattleCafe_ChooseTapuLele
	return

BattleCafe_RewardMenu_29:
	goto BattleCafe_ChooseTapuBulu
	return

BattleCafe_RewardMenu_30:
	goto BattleCafe_ChooseTapuFini
	return


BattleCafe_ChooseArticuno::
	goto_if_set FLAG_BATTLE_CAFE_ARTICUNO_RECEIVED, BattleCafe_ChooseArticuno_2
BattleCafe_ChooseArticuno_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ARTICUNO_GALAR
	setvar VAR_TEMP_B, 0
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseArticuno_2:
	msgbox BattleCafe_ChooseArticuno_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseArticuno_1


BattleCafe_ChooseZapdos::
	goto_if_set FLAG_BATTLE_CAFE_ZAPDOS_RECEIVED, BattleCafe_ChooseZapdos_2
BattleCafe_ChooseZapdos_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZAPDOS_GALAR
	setvar VAR_TEMP_B, 1
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseZapdos_2:
	msgbox BattleCafe_ChooseZapdos_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseZapdos_1


BattleCafe_ChooseMoltres::
	goto_if_set FLAG_BATTLE_CAFE_MOLTRES_RECEIVED, BattleCafe_ChooseMoltres_2
BattleCafe_ChooseMoltres_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MOLTRES_GALAR
	setvar VAR_TEMP_B, 2
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseMoltres_2:
	msgbox BattleCafe_ChooseMoltres_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseMoltres_1


BattleCafe_ChooseTornadus::
	goto_if_set FLAG_BATTLE_CAFE_TORNADUS_RECEIVED, BattleCafe_ChooseTornadus_2
BattleCafe_ChooseTornadus_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TORNADUS
	setvar VAR_TEMP_B, 3
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTornadus_2:
	msgbox BattleCafe_ChooseTornadus_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTornadus_1


BattleCafe_ChooseThundurus::
	goto_if_set FLAG_BATTLE_CAFE_THUNDURUS_RECEIVED, BattleCafe_ChooseThundurus_2
BattleCafe_ChooseThundurus_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_THUNDURUS
	setvar VAR_TEMP_B, 4
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseThundurus_2:
	msgbox BattleCafe_ChooseThundurus_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseThundurus_1


BattleCafe_ChooseLandorus::
	goto_if_set FLAG_BATTLE_CAFE_LANDORUS_RECEIVED, BattleCafe_ChooseLandorus_2
BattleCafe_ChooseLandorus_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LANDORUS
	setvar VAR_TEMP_B, 5
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseLandorus_2:
	msgbox BattleCafe_ChooseLandorus_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseLandorus_1


BattleCafe_ChooseEnamorus::
	goto_if_set FLAG_BATTLE_CAFE_ENAMORUS_RECEIVED, BattleCafe_ChooseEnamorus_2
BattleCafe_ChooseEnamorus_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ENAMORUS
	setvar VAR_TEMP_B, 6
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseEnamorus_2:
	msgbox BattleCafe_ChooseEnamorus_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseEnamorus_1


BattleCafe_ChooseTapuKoko::
	goto_if_set FLAG_BATTLE_CAFE_TAPU_KOKO_RECEIVED, BattleCafe_ChooseTapuKoko_2
BattleCafe_ChooseTapuKoko_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_KOKO
	setvar VAR_TEMP_B, 7
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuKoko_2:
	msgbox BattleCafe_ChooseTapuKoko_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuKoko_1


BattleCafe_ChooseTapuLele::
	goto_if_set FLAG_BATTLE_CAFE_TAPU_LELE_RECEIVED, BattleCafe_ChooseTapuLele_2
BattleCafe_ChooseTapuLele_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_LELE
	setvar VAR_TEMP_B, 8
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuLele_2:
	msgbox BattleCafe_ChooseTapuLele_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuLele_1


BattleCafe_ChooseTapuBulu::
	goto_if_set FLAG_BATTLE_CAFE_TAPU_BULU_RECEIVED, BattleCafe_ChooseTapuBulu_2
BattleCafe_ChooseTapuBulu_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_BULU
	setvar VAR_TEMP_B, 9
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuBulu_2:
	msgbox BattleCafe_ChooseTapuBulu_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuBulu_1


BattleCafe_ChooseTapuFini::
	goto_if_set FLAG_BATTLE_CAFE_TAPU_FINI_RECEIVED, BattleCafe_ChooseTapuFini_2
BattleCafe_ChooseTapuFini_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_FINI
	setvar VAR_TEMP_B, 10
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuFini_2:
	msgbox BattleCafe_ChooseTapuFini_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuFini_1


BattleCafe_ConfirmRewardMon::
	compare VAR_BATTLE_CAFE_POINTS, 5
	goto_if_lt BattleCafe_ConfirmRewardMon_2
BattleCafe_ConfirmRewardMon_1:
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
	msgbox BattleCafe_ConfirmRewardMon_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ConfirmRewardMon_5
BattleCafe_ConfirmRewardMon_4:
	compare VAR_TEMP_B, 3
	goto_if_ge BattleCafe_ConfirmRewardMon_10
BattleCafe_ConfirmRewardMon_7:
	givemon VAR_TEMP_TRANSFERRED_SPECIES, 70
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq BattleCafe_ConfirmRewardMon_15
BattleCafe_ConfirmRewardMon_14:
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	subvar VAR_BATTLE_CAFE_POINTS, 5
	switch VAR_TEMP_B
	case 0, BattleCafe_ConfirmRewardMon_21
	case 1, BattleCafe_ConfirmRewardMon_22
	case 2, BattleCafe_ConfirmRewardMon_23
	case 3, BattleCafe_ConfirmRewardMon_24
	case 4, BattleCafe_ConfirmRewardMon_25
	case 5, BattleCafe_ConfirmRewardMon_26
	case 6, BattleCafe_ConfirmRewardMon_27
	case 7, BattleCafe_ConfirmRewardMon_28
	case 8, BattleCafe_ConfirmRewardMon_29
	case 9, BattleCafe_ConfirmRewardMon_30
	case 10, BattleCafe_ConfirmRewardMon_31
BattleCafe_ConfirmRewardMon_19:
	special Achievement_CheckAll
	compare VAR_TEMP_B, 3
	goto_if_ge BattleCafe_ConfirmRewardMon_34
BattleCafe_ConfirmRewardMon_32:
	msgbox BattleCafe_ConfirmRewardMon_Text_2
	goto BattleCafe_RewardMenu
	return

BattleCafe_ConfirmRewardMon_2:
	goto BattleCafe_NotEnoughPoints
	goto BattleCafe_ConfirmRewardMon_1

BattleCafe_ConfirmRewardMon_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ConfirmRewardMon_4

BattleCafe_ConfirmRewardMon_8:
	checkitemspace ITEM_REVEAL_GLASS, 1
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ConfirmRewardMon_17
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_9:
	checkitem ITEM_REVEAL_GLASS
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ConfirmRewardMon_8
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_10:
	compare VAR_TEMP_B, 6
	goto_if_le BattleCafe_ConfirmRewardMon_9
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_15:
	goto Common_EventScript_NoMoreRoomForPokemon
	goto BattleCafe_ConfirmRewardMon_14

BattleCafe_ConfirmRewardMon_17:
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_21:
	setflag FLAG_BATTLE_CAFE_ARTICUNO_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_22:
	setflag FLAG_BATTLE_CAFE_ZAPDOS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_23:
	setflag FLAG_BATTLE_CAFE_MOLTRES_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_24:
	setflag FLAG_BATTLE_CAFE_TORNADUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_25:
	setflag FLAG_BATTLE_CAFE_THUNDURUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_26:
	setflag FLAG_BATTLE_CAFE_LANDORUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_27:
	setflag FLAG_BATTLE_CAFE_ENAMORUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_28:
	setflag FLAG_BATTLE_CAFE_TAPU_KOKO_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_29:
	setflag FLAG_BATTLE_CAFE_TAPU_LELE_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_30:
	setflag FLAG_BATTLE_CAFE_TAPU_BULU_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_31:
	setflag FLAG_BATTLE_CAFE_TAPU_FINI_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_33:
	checkitem ITEM_REVEAL_GLASS
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ConfirmRewardMon_37
	goto BattleCafe_ConfirmRewardMon_32

BattleCafe_ConfirmRewardMon_34:
	compare VAR_TEMP_B, 6
	goto_if_le BattleCafe_ConfirmRewardMon_33
	goto BattleCafe_ConfirmRewardMon_32

BattleCafe_ConfirmRewardMon_37:
	msgbox BattleCafe_ConfirmRewardMon_Text_1
	giveitem ITEM_REVEAL_GLASS
	goto BattleCafe_ConfirmRewardMon_32


BattleCafe_ChooseMiraidon::
	goto_if_set FLAG_BATTLE_CAFE_MIRAIDON_RECEIVED, BattleCafe_ChooseMiraidon_2
BattleCafe_ChooseMiraidon_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MIRAIDON
	setvar VAR_TEMP_B, 0
	goto BattleCafe_ConfirmParadoxLegend
	return

BattleCafe_ChooseMiraidon_2:
	msgbox BattleCafe_ChooseMiraidon_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseMiraidon_1


BattleCafe_ChooseKoraidon::
	goto_if_set FLAG_BATTLE_CAFE_KORAIDON_RECEIVED, BattleCafe_ChooseKoraidon_2
BattleCafe_ChooseKoraidon_1:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KORAIDON
	setvar VAR_TEMP_B, 1
	goto BattleCafe_ConfirmParadoxLegend
	return

BattleCafe_ChooseKoraidon_2:
	msgbox BattleCafe_ChooseKoraidon_Text_0
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseKoraidon_1


BattleCafe_ConfirmParadoxLegend::
	compare VAR_BATTLE_CAFE_POINTS, 25
	goto_if_lt BattleCafe_ConfirmParadoxLegend_2
BattleCafe_ConfirmParadoxLegend_1:
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
	msgbox BattleCafe_ConfirmParadoxLegend_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ConfirmParadoxLegend_5
BattleCafe_ConfirmParadoxLegend_4:
	givemon VAR_TEMP_TRANSFERRED_SPECIES, 70
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq BattleCafe_ConfirmParadoxLegend_8
BattleCafe_ConfirmParadoxLegend_7:
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	subvar VAR_BATTLE_CAFE_POINTS, 25
	switch VAR_TEMP_B
	case 0, BattleCafe_ConfirmParadoxLegend_12
	case 1, BattleCafe_ConfirmParadoxLegend_13
BattleCafe_ConfirmParadoxLegend_10:
	special Achievement_CheckAll
	msgbox BattleCafe_ConfirmParadoxLegend_Text_1
	goto BattleCafe_RewardMenu
	return

BattleCafe_ConfirmParadoxLegend_2:
	goto BattleCafe_NotEnoughLegendPoints
	goto BattleCafe_ConfirmParadoxLegend_1

BattleCafe_ConfirmParadoxLegend_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ConfirmParadoxLegend_4

BattleCafe_ConfirmParadoxLegend_8:
	goto Common_EventScript_NoMoreRoomForPokemon
	goto BattleCafe_ConfirmParadoxLegend_7

BattleCafe_ConfirmParadoxLegend_12:
	setflag FLAG_BATTLE_CAFE_MIRAIDON_RECEIVED
	goto BattleCafe_ConfirmParadoxLegend_10

BattleCafe_ConfirmParadoxLegend_13:
	setflag FLAG_BATTLE_CAFE_KORAIDON_RECEIVED
	goto BattleCafe_ConfirmParadoxLegend_10


BattleCafe_ChooseShinyGenome::
	compare VAR_BATTLE_CAFE_POINTS, 4
	goto_if_lt BattleCafe_ChooseShinyGenome_2
BattleCafe_ChooseShinyGenome_1:
	msgbox BattleCafe_ChooseShinyGenome_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseShinyGenome_5
BattleCafe_ChooseShinyGenome_4:
	checkitemspace ITEM_SHIN_GENOME, 1
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ChooseShinyGenome_8
BattleCafe_ChooseShinyGenome_7:
	giveitem ITEM_SHIN_GENOME
	compare VAR_RESULT, TRUE
	goto_if_ne BattleCafe_ChooseShinyGenome_11
BattleCafe_ChooseShinyGenome_10:
	subvar VAR_BATTLE_CAFE_POINTS, 4
	msgbox BattleCafe_ChooseShinyGenome_Text_1
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseShinyGenome_2:
	goto BattleCafe_NotEnoughFourPoints
	goto BattleCafe_ChooseShinyGenome_1

BattleCafe_ChooseShinyGenome_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseShinyGenome_4

BattleCafe_ChooseShinyGenome_8:
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseShinyGenome_7

BattleCafe_ChooseShinyGenome_11:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseShinyGenome_10


BattleCafe_ChooseGoldBottleCaps::
	compare VAR_BATTLE_CAFE_POINTS, 5
	goto_if_lt BattleCafe_ChooseGoldBottleCaps_2
BattleCafe_ChooseGoldBottleCaps_1:
	msgbox BattleCafe_ChooseGoldBottleCaps_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseGoldBottleCaps_5
BattleCafe_ChooseGoldBottleCaps_4:
	checkitemspace ITEM_GOLD_BOTTLE_CAP, 2
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ChooseGoldBottleCaps_8
BattleCafe_ChooseGoldBottleCaps_7:
	giveitem ITEM_GOLD_BOTTLE_CAP, 2
	compare VAR_RESULT, TRUE
	goto_if_ne BattleCafe_ChooseGoldBottleCaps_11
BattleCafe_ChooseGoldBottleCaps_10:
	subvar VAR_BATTLE_CAFE_POINTS, 5
	msgbox BattleCafe_ChooseGoldBottleCaps_Text_1
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseGoldBottleCaps_2:
	goto BattleCafe_NotEnoughPoints
	goto BattleCafe_ChooseGoldBottleCaps_1

BattleCafe_ChooseGoldBottleCaps_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseGoldBottleCaps_4

BattleCafe_ChooseGoldBottleCaps_8:
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseGoldBottleCaps_7

BattleCafe_ChooseGoldBottleCaps_11:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseGoldBottleCaps_10


BattleCafe_ChooseMoney::
	compare VAR_BATTLE_CAFE_POINTS, 5
	goto_if_lt BattleCafe_ChooseMoney_2
BattleCafe_ChooseMoney_1:
	msgbox BattleCafe_ChooseMoney_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseMoney_5
BattleCafe_ChooseMoney_4:
	subvar VAR_BATTLE_CAFE_POINTS, 5
	showmoneybox 0, 0
	addmoney 250000
	updatemoneybox 0
	playse SE_SHOP
	waitse
	hidemoneybox
	msgbox BattleCafe_ChooseMoney_Text_1
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseMoney_2:
	goto BattleCafe_NotEnoughPoints
	goto BattleCafe_ChooseMoney_1

BattleCafe_ChooseMoney_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseMoney_4


BattleCafe_ChooseVitaminSetAtk::
	compare VAR_BATTLE_CAFE_POINTS, 4
	goto_if_lt BattleCafe_ChooseVitaminSetAtk_2
BattleCafe_ChooseVitaminSetAtk_1:
	msgbox BattleCafe_ChooseVitaminSetAtk_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseVitaminSetAtk_5
BattleCafe_ChooseVitaminSetAtk_4:
	setvar VAR_0x8004, BATTLE_CAFE_VITAMIN_SET_ATK
	special BattleCafe_TryPurchaseVitaminSet
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_NOT_ENOUGH_POINTS
	goto_if_eq BattleCafe_ChooseVitaminSetAtk_8
BattleCafe_ChooseVitaminSetAtk_7:
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS
	goto_if_ne BattleCafe_ChooseVitaminSetAtk_11
BattleCafe_ChooseVitaminSetAtk_10:
	playse SE_SHOP
	waitse
	msgbox BattleCafe_ChooseVitaminSetAtk_Text_1
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseVitaminSetAtk_2:
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetAtk_1

BattleCafe_ChooseVitaminSetAtk_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseVitaminSetAtk_4

BattleCafe_ChooseVitaminSetAtk_8:
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetAtk_7

BattleCafe_ChooseVitaminSetAtk_11:
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseVitaminSetAtk_10


BattleCafe_ChooseVitaminSetDef::
	compare VAR_BATTLE_CAFE_POINTS, 4
	goto_if_lt BattleCafe_ChooseVitaminSetDef_2
BattleCafe_ChooseVitaminSetDef_1:
	msgbox BattleCafe_ChooseVitaminSetDef_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseVitaminSetDef_5
BattleCafe_ChooseVitaminSetDef_4:
	setvar VAR_0x8004, BATTLE_CAFE_VITAMIN_SET_DEF
	special BattleCafe_TryPurchaseVitaminSet
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_NOT_ENOUGH_POINTS
	goto_if_eq BattleCafe_ChooseVitaminSetDef_8
BattleCafe_ChooseVitaminSetDef_7:
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS
	goto_if_ne BattleCafe_ChooseVitaminSetDef_11
BattleCafe_ChooseVitaminSetDef_10:
	playse SE_SHOP
	waitse
	msgbox BattleCafe_ChooseVitaminSetDef_Text_1
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseVitaminSetDef_2:
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetDef_1

BattleCafe_ChooseVitaminSetDef_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseVitaminSetDef_4

BattleCafe_ChooseVitaminSetDef_8:
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetDef_7

BattleCafe_ChooseVitaminSetDef_11:
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseVitaminSetDef_10


BattleCafe_ChooseVitaminSetSpe::
	compare VAR_BATTLE_CAFE_POINTS, 2
	goto_if_lt BattleCafe_ChooseVitaminSetSpe_2
BattleCafe_ChooseVitaminSetSpe_1:
	msgbox BattleCafe_ChooseVitaminSetSpe_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseVitaminSetSpe_5
BattleCafe_ChooseVitaminSetSpe_4:
	setvar VAR_0x8004, BATTLE_CAFE_VITAMIN_SET_SPE
	special BattleCafe_TryPurchaseVitaminSet
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_NOT_ENOUGH_POINTS
	goto_if_eq BattleCafe_ChooseVitaminSetSpe_8
BattleCafe_ChooseVitaminSetSpe_7:
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS
	goto_if_ne BattleCafe_ChooseVitaminSetSpe_11
BattleCafe_ChooseVitaminSetSpe_10:
	playse SE_SHOP
	waitse
	msgbox BattleCafe_ChooseVitaminSetSpe_Text_1
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseVitaminSetSpe_2:
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetSpe_1

BattleCafe_ChooseVitaminSetSpe_5:
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseVitaminSetSpe_4

BattleCafe_ChooseVitaminSetSpe_8:
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetSpe_7

BattleCafe_ChooseVitaminSetSpe_11:
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseVitaminSetSpe_10


BattleCafe_NotEnoughPoints::
	msgbox BattleCafe_NotEnoughPoints_Text_0
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughLegendPoints::
	msgbox BattleCafe_NotEnoughLegendPoints_Text_0
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughFourPoints::
	msgbox BattleCafe_NotEnoughFourPoints_Text_0
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughVitaminSetPoints::
	msgbox BattleCafe_NotEnoughVitaminSetPoints_Text_0
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughBagSpace::
	msgbox BattleCafe_NotEnoughBagSpace_Text_0
	goto BattleCafe_RewardMenu
	return


BattleCafe_Goodbye::
	msgbox BattleCafe_Goodbye_Text_0
	release
	end


BattleCafe_GiveDailyCandyReward::
	random 3
	addvar VAR_RESULT, 1
	giveitem ITEM_EXP_CANDY_XL, VAR_RESULT
	return


BattleCafe_TrainerAthena::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_ATHENA, BattleCafe_TrainerAthena_2
	msgbox BattleCafe_TrainerAthena_Text_1
	trainerbattle_no_intro TRAINER_CAFE_ATHENA, BattleCafe_TrainerAthena_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_ATHENA
	msgbox BattleCafe_TrainerAthena_Text_3
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerAthena_2:
	msgbox BattleCafe_TrainerAthena_Text_0
	release
	end


BattleCafe_TrainerDoves::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_DOVES, BattleCafe_TrainerDoves_2
	msgbox BattleCafe_TrainerDoves_Text_1
	trainerbattle_no_intro TRAINER_CAFE_DOVES, BattleCafe_TrainerDoves_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_DOVES
	msgbox BattleCafe_TrainerDoves_Text_3
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerDoves_2:
	msgbox BattleCafe_TrainerDoves_Text_0
	release
	end


BattleCafe_TrainerElton::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_ELTON, BattleCafe_TrainerElton_2
	msgbox BattleCafe_TrainerElton_Text_1
	trainerbattle_no_intro TRAINER_CAFE_ELTON, BattleCafe_TrainerElton_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_ELTON
	msgbox BattleCafe_TrainerElton_Text_3
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerElton_2:
	msgbox BattleCafe_TrainerElton_Text_0
	release
	end


BattleCafe_TrainerNem::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_NEM, BattleCafe_TrainerNem_2
	msgbox BattleCafe_TrainerNem_Text_1
	trainerbattle_no_intro TRAINER_CAFE_NEM, BattleCafe_TrainerNem_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_NEM
	msgbox BattleCafe_TrainerNem_Text_3
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerNem_2:
	msgbox BattleCafe_TrainerNem_Text_0
	release
	end


BattleCafe_TrainerBai::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_BAI, BattleCafe_TrainerBai_2
	msgbox BattleCafe_TrainerBai_Text_1
	trainerbattle_no_intro TRAINER_CAFE_BAI, BattleCafe_TrainerBai_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_BAI
	msgbox BattleCafe_TrainerBai_Text_3
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerBai_2:
	msgbox BattleCafe_TrainerBai_Text_0
	release
	end


BattleCafe_TrainerDrac::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_DRAC, BattleCafe_TrainerDrac_2
	msgbox BattleCafe_TrainerDrac_Text_1
	trainerbattle_no_intro TRAINER_CAFE_DRAC, BattleCafe_TrainerDrac_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_DRAC
	msgbox BattleCafe_TrainerDrac_Text_0
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerDrac_2:
	msgbox BattleCafe_TrainerDrac_Text_0
	release
	end


BattleCafe_TrainerSimpli::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SIMPLI, BattleCafe_TrainerSimpli_2
	msgbox BattleCafe_TrainerSimpli_Text_1
	trainerbattle_no_intro TRAINER_CAFE_JUNA, BattleCafe_TrainerSimpli_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_SIMPLI
	msgbox BattleCafe_TrainerSimpli_Text_3
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerSimpli_2:
	msgbox BattleCafe_TrainerSimpli_Text_0
	release
	end


BattleCafe_TrainerTylarie::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_BATTLE_CAFE_TYLARIE, BattleCafe_TrainerTylarie_2
	msgbox BattleCafe_TrainerTylarie_Text_1
	trainerbattle_no_intro TRAINER_CAFE_TYLARIE, BattleCafe_TrainerTylarie_Text_2
	setflag FLAG_DAILY_BATTLE_CAFE_TYLARIE
	msgbox BattleCafe_TrainerTylarie_Text_3
	call BattleCafe_GiveDailyCandyReward
	release
	end

BattleCafe_TrainerTylarie_2:
	msgbox BattleCafe_TrainerTylarie_Text_0
	release
	end


BattleCafe_FreshWaterFountain::
	goto_if_set FLAG_GOT_FRESH_WATER, BattleCafe_FreshWaterFountain_1
	lock
	msgbox BattleCafe_FreshWaterFountain_Text_1
	finditem ITEM_FRESH_WATER
	setflag FLAG_GOT_FRESH_WATER
	msgbox BattleCafe_FreshWaterFountain_Text_2
	release
	end

BattleCafe_FreshWaterFountain_1:
	msgbox BattleCafe_FreshWaterFountain_Text_0, MSGBOX_SIGN
	return


BattleCafe_GiveDiancie_Text_0:
	.string "Well, look at that. You've beaten\n"
	.string "every one of my regulars at least\l"
	.string "once.\p"
	.string "Seems only right you leave with a\n"
	.string "rare dining companion, Diancie!$"

BattleCafe_GiveDiancie_Text_1:
	.string "It'll be waiting right here. Make\n"
	.string "whatever preparations you need, then\l"
	.string "come talk to me when you're ready to\l"
	.string "welcome it aboard.$"

BattleCafe_GiveDiancie_Text_2:
	.string "Diancie is waiting for you.\p"
	.string "Are you ready to receive it?$"

BattleCafe_GiveDiancie_Text_3:
	.string "No rush. Diancie will be right\n"
	.string "here whenever you're ready.$"

BattleCafe_GiveDiancie_Text_4:
	.string "Diancie's a fine addition to the menu.\n"
	.string "Take good care of it!$"

BattleCafe_OwnerMenu_Text_0:
	.string "Welcome to my Battle Café!\p"
	.string "I picked up my recipes and my battling\n"
	.string "chops back home in Galar.\p"
	.string "These days I bring Trainers together\n"
	.string "for good food and good battles, right\l"
	.string "here in Johto.\p"
	.string "There's even a special prize if you\n"
	.string "manage to beat all the regulars here.\p"
	.string "However I must warn you that all the\n"
	.string "regulars here are really tough!\p"
	.string "Anyway, enough about me...$"

BattleCafe_OwnerMenu_Text_1:
	.string "After seeing you clear Super Challenge,\n"
	.string "I can offer you a new format:\p"
	.string "Endless Challenge!$"

BattleCafe_OwnerMenu_Text_2:
	.string "After seeing you conquer Super Rush,\n"
	.string "I can offer you one final format:\p"
	.string "Endless Rush!$"

BattleCafe_OwnerMenu_Text_3:
	.string "Welcome! What'll it be today?$"

BattleCafe_OwnerMenu_Text_4:
	.string "Daily Challenge$"

BattleCafe_OwnerMenu_Text_5:
	.string "Rush Mode$"

BattleCafe_OwnerMenu_Text_6:
	.string "Super Challenge$"

BattleCafe_OwnerMenu_Text_7:
	.string "Super Rush$"

BattleCafe_OwnerMenu_Text_8:
	.string "Endless Modes$"

BattleCafe_OwnerMenu_Text_9:
	.string "Exchange Points$"

BattleCafe_OwnerMenu_Text_10:
	.string "Café Options$"

BattleCafe_OwnerMenu_Text_11:
	.string "Leave$"

BattleCafe_OptionsMenu_Text_0:
	.string "What would you like to check?$"

BattleCafe_OptionsMenu_Text_1:
	.string "Battle BGM$"

BattleCafe_OptionsMenu_Text_2:
	.string "High Scores$"

BattleCafe_OptionsMenu_Text_3:
	.string "Innates$"

BattleCafe_OptionsMenu_Text_4:
	.string "Café Rules$"

BattleCafe_OptionsMenu_Text_5:
	.string "Back$"

BattleCafe_ExplainRules_Text_0:
	.string "Three Café visitors will answer each\n"
	.string "challenge, one after another.\p"
	.string "In the Daily Challenge, they bring\n"
	.string "dependable teams of four.\p"
	.string "I'll tend to your Pokémon after each\n"
	.string "battle.\p"
	.string "Win all three for 3 Café Points.$"

BattleCafe_ExplainRules_Text_1:
	.string "Rush Mode draws seasoned battlers with\n"
	.string "teams of four.\p"
	.string "Anything goes, and I can't heal\n"
	.string "your Pokémon between the matches.\p"
	.string "Win all three for 5 points.$"

BattleCafe_ExplainRules_Text_2:
	.string "Super Challenge and Super Rush pit\n"
	.string "you against full teams of six Pokémon.\p"
	.string "Anyone might show up so prepare to\n"
	.string "face literally anything.\p"
	.string "Same rules apply here for healing\n"
	.string "between the rounds.$"

BattleCafe_ExplainRules_Text_3:
	.string "There are no breaks once service\n"
	.string "begins.\p"
	.string "A loss ends the run, though\n"
	.string "you may retry until you win.\p"
	.string "Each challenge can be won once per day.$"

BattleCafe_ExplainRules_Text_4:
	.string "Both Endless formats use full teams\n"
	.string "of six and continue until you lose\l"
	.string "or choose to retire.\p"
	.string "Endless Challenge heals your party\n"
	.string "after every win and awards 1 point.$"

BattleCafe_ExplainRules_Text_5:
	.string "Endless Rush restores your party\n"
	.string "after every third victory and awards\l"
	.string "2 points per win.\p"
	.string "Your best streak in each format is\n"
	.string "saved under High Scores.$"

BattleCafe_AskDailyChallenge_Text_0:
	.string "You've already cleared today's\n"
	.string "Daily Challenge.\p"
	.string "Come back tomorrow,\n"
	.string "or try another challenge!$"

BattleCafe_AskDailyChallenge_Text_1:
	.string "Three Café visitors are ready with\n"
	.string "teams of four.\p"
	.string "I'll tend to your party\n"
	.string "after rounds one and two.\p"
	.string "Begin today's challenge?$"

BattleCafe_AskRushMode_Text_0:
	.string "You've already conquered Rush Mode\n"
	.string "today.\p"
	.string "Come back tomorrow, or take\n"
	.string "another challenge!$"

BattleCafe_AskRushMode_Text_1:
	.string "Three seasoned visitors are waiting\n"
	.string "with teams of four.\p"
	.string "I can't tend to your party between \n"
	.string "these battles.\p"
	.string "Begin today's rush?$"

BattleCafe_AskSuperChallenge_Text_0:
	.string "You've already cleared today's\n"
	.string "Super Challenge.\p"
	.string "Come back tomorrow,\n"
	.string "or attempt another challenge!$"

BattleCafe_AskSuperChallenge_Text_1:
	.string "Every Pokémon gets a seat in Super\n"
	.string "Challenge. Bring a full party of six\l"
	.string "before entering.$"

BattleCafe_AskSuperChallenge_Text_2:
	.string "Three visitors will each meet your full\n"
	.string "party with six Pokémon of their own.\p"
	.string "I'll tend to your team between battles.\p"
	.string "Begin the Super Challenge?$"

BattleCafe_AskSuperRush_Text_0:
	.string "You've already conquered Super Rush\n"
	.string "today.\p"
	.string "Come back tomorrow for\n"
	.string "another full-team trial!$"

BattleCafe_AskSuperRush_Text_1:
	.string "Every Pokémon gets a seat in Super\n"
	.string "Rush.\p"
	.string "Bring a full party of six\n"
	.string "before entering.$"

BattleCafe_AskSuperRush_Text_2:
	.string "Three visitors will each bring a full\n"
	.string "team of six.\p"
	.string "Once the rush begins, I can't heal\n"
	.string "your Pokémon between the battles.\p"
	.string "Begin the Super Rush?$"

BattleCafe_EndlessMenu_Text_0:
	.string "Which Endless format will you try?$"

BattleCafe_EndlessMenu_Text_1:
	.string "Endless Challenge$"

BattleCafe_EndlessMenu_Text_2:
	.string "Endless Rush$"

BattleCafe_EndlessMenu_Text_3:
	.string "Endless Rules$"

BattleCafe_ExplainEndlessRules_Text_0:
	.string "Endless Challenge restores your party\n"
	.string "after every victory. \p"
	.string "Each win immediately awards 1 \n"
	.string "Café Point.\p"
	.string "Clear Super Challenge to unlock it.$"

BattleCafe_ExplainEndlessRules_Text_1:
	.string "Endless Rush restores your party after\n"
	.string "every third victory. \p"
	.string "Each win immediately awards 2 \n"
	.string "Café Points.\p"
	.string "Clear Super Rush to unlock it.$"

BattleCafe_ExplainEndlessRules_Text_2:
	.string "Both formats use full 6-vs-6 battles.\n"
	.string "You may retire after any victory,\l"
	.string "and your best streak is saved.$"

BattleCafe_AskEndlessChallenge_Text_0:
	.string "Clear Super Challenge to unlock\n"
	.string "Endless Challenge.$"

BattleCafe_AskEndlessChallenge_Text_1:
	.string "Every Endless opponent brings\n"
	.string "six Pokémon.\p"
	.string "Bring a full party of six before\n"
	.string "taking your seat.$"

BattleCafe_AskEndlessChallenge_Text_2:
	.string "Full teams of six will keep coming\n"
	.string "until you lose or retire.\p"
	.string "I'll restore your party after every win,\n"
	.string "and each victory earns 1 Café Point.\p"
	.string "Begin Endless Challenge?$"

BattleCafe_AskEndlessRush_Text_0:
	.string "Clear Super Rush to unlock\n"
	.string "Endless Rush.$"

BattleCafe_AskEndlessRush_Text_1:
	.string "Full teams of six will keep coming\n"
	.string "until you lose or retire.\p"
	.string "I'll restore your party after every third\n"
	.string "victory. Each win earns 2 Café Points.\p"
	.string "Begin Endless Rush?$"

BattleCafe_BeginChallenge_Text_0:
	.string "No final course. No final opponent.\n"
	.string "Endless service begins now!$"

BattleCafe_BeginChallenge_Text_1:
	.string "Three courses. Three opponents.\n"
	.string "Service begins now!$"

BattleCafe_ChallengeNextRound_Text_0:
	.string "Victory! Streak: {STR_VAR_1}.\n"
	.string "You received {STR_VAR_2} Café Points,\l"
	.string "and your party was restored.\p"
	.string "Continue the run?$"

BattleCafe_ChallengeNextRound_Text_1:
	.string "Victory! Streak: {STR_VAR_1}.\n"
	.string "You received {STR_VAR_2} Café Points.\p"
	.string "Three battles cleared! Your party\n"
	.string "was restored. Continue the run?$"

BattleCafe_ChallengeNextRound_Text_2:
	.string "Victory! Streak: {STR_VAR_1}.\n"
	.string "You received {STR_VAR_2} Café Points.\p"
	.string "Your party has not been restored.\n"
	.string "Continue the run?$"

BattleCafe_ChallengeNextRound_Text_3:
	.string "Your party was restored.\n"
	.string "The next challenger is arriving!$"

BattleCafe_ChallengeNextRound_Text_4:
	.string "Your party was restored.\n"
	.string "The next full team is arriving!$"

BattleCafe_ChallengeNextRound_Text_5:
	.string "No healing in Super Rush!\n"
	.string "The next full team is arriving!$"

BattleCafe_ChallengeNextRound_Text_6:
	.string "No healing in Rush Mode!\n"
	.string "The next challenger is arriving!$"

BattleCafe_EndlessRetired_Text_0:
	.string "Run retired at {STR_VAR_1} wins.\p"
	.string "Your party is fully restored, your record\n"
	.string "is safe, and every point is yours to keep.$"

BattleCafe_ChallengeLost_Text_0:
	.string "Your Endless run ends at {STR_VAR_1}\n"
	.string "wins. I've fully\l"
	.string "restored your party.\p"
	.string "Every Café Point you earned is yours\n"
	.string "to keep. Try to push even farther\l"
	.string "next time!$"

BattleCafe_ChallengeLost_Text_1:
	.string "Tough course, huh? I've fully restored\n"
	.string "your party.\p"
	.string "Catch your breath, rework\n"
	.string "your strategy, and come at it again\l"
	.string "whenever you like!$"

BattleCafe_ChallengeWon_Text_0:
	.string "Daily Challenge complete!\p"
	.string "That's {STR_VAR_1} Café Points for you.$"

BattleCafe_ChallengeWon_Text_1:
	.string "Rush Mode complete! That took\n"
	.string "some real grit.\p"
	.string "Here's {STR_VAR_1} Café Points.$"

BattleCafe_ChallengeWon_Text_2:
	.string "Super Challenge complete!\n"
	.string "Full team, full effort!\p"
	.string "That's {STR_VAR_1} Café Points.$"

BattleCafe_ChallengeWon_Text_3:
	.string "Incredible! You have beaten\n"
	.string "the Super Rush mode!\p"
	.string "I can hardly believe it!\p"
	.string "Here's your reward of\n"
	.string "{STR_VAR_1} Café Points.$"

BattleCafe_RewardMenu_Text_0:
	.string "You have {STR_VAR_1} Café Points.\n"
	.string "Anything you want to exchange for?$"

BattleCafe_RewardMenu_Text_1:
	.string "Vitamin Set Atk - 4$"

BattleCafe_RewardMenu_Text_2:
	.string "Vitamin Set Def - 4$"

BattleCafe_RewardMenu_Text_3:
	.string "Vitamin Set Spe - 2$"

BattleCafe_RewardMenu_Text_4:
	.string "Shiny Genome - 4$"

BattleCafe_RewardMenu_Text_5:
	.string "2 Gold Caps - 5$"

BattleCafe_RewardMenu_Text_6:
	.string "¥250,000 - 5$"

BattleCafe_RewardMenu_Text_7:
	.string "G. Articuno - 5$"

BattleCafe_RewardMenu_Text_8:
	.string "G. Zapdos - 5$"

BattleCafe_RewardMenu_Text_9:
	.string "G. Moltres - 5$"

BattleCafe_RewardMenu_Text_10:
	.string "Tornadus - 5$"

BattleCafe_RewardMenu_Text_11:
	.string "Thundurus - 5$"

BattleCafe_RewardMenu_Text_12:
	.string "Landorus - 5$"

BattleCafe_RewardMenu_Text_13:
	.string "Enamorus - 5$"

BattleCafe_RewardMenu_Text_14:
	.string "Tapu Koko - 5$"

BattleCafe_RewardMenu_Text_15:
	.string "Tapu Lele - 5$"

BattleCafe_RewardMenu_Text_16:
	.string "Tapu Bulu - 5$"

BattleCafe_RewardMenu_Text_17:
	.string "Tapu Fini - 5$"

BattleCafe_RewardMenu_Text_18:
	.string "Miraidon - 25$"

BattleCafe_RewardMenu_Text_19:
	.string "Koraidon - 25$"

BattleCafe_ChooseArticuno_Text_0:
	.string "I've already entrusted Galarian\n"
	.string "Articuno to you.$"

BattleCafe_ChooseZapdos_Text_0:
	.string "I've already entrusted Galarian\n"
	.string "Zapdos to you.$"

BattleCafe_ChooseMoltres_Text_0:
	.string "I've already entrusted Galarian\n"
	.string "Moltres to you.$"

BattleCafe_ChooseTornadus_Text_0:
	.string "I've already entrusted Tornadus\n"
	.string "to you.$"

BattleCafe_ChooseThundurus_Text_0:
	.string "I've already entrusted Thundurus\n"
	.string "to you.$"

BattleCafe_ChooseLandorus_Text_0:
	.string "I've already entrusted Landorus\n"
	.string "to you.$"

BattleCafe_ChooseEnamorus_Text_0:
	.string "I've already entrusted Enamorus\n"
	.string "to you.$"

BattleCafe_ChooseTapuKoko_Text_0:
	.string "I've already entrusted Tapu Koko\n"
	.string "to you.$"

BattleCafe_ChooseTapuLele_Text_0:
	.string "I've already entrusted Tapu Lele\n"
	.string "to you.$"

BattleCafe_ChooseTapuBulu_Text_0:
	.string "I've already entrusted Tapu Bulu\n"
	.string "to you.$"

BattleCafe_ChooseTapuFini_Text_0:
	.string "I've already entrusted Tapu Fini\n"
	.string "to you.$"

BattleCafe_ConfirmRewardMon_Text_0:
	.string "Exchange 5 Café Points for\n"
	.string "{STR_VAR_1}?$"

BattleCafe_ConfirmRewardMon_Text_1:
	.string "You might find this useful.$"

BattleCafe_ConfirmRewardMon_Text_2:
	.string "A fair trade. I'm sure it'll fit right\n"
	.string "into your team.$"

BattleCafe_ChooseMiraidon_Text_0:
	.string "I've already entrusted Miraidon\n"
	.string "to you.$"

BattleCafe_ChooseKoraidon_Text_0:
	.string "I've already entrusted Koraidon\n"
	.string "to you.$"

BattleCafe_ConfirmParadoxLegend_Text_0:
	.string "Exchange 25 Café Points for\n"
	.string "{STR_VAR_1}?$"

BattleCafe_ConfirmParadoxLegend_Text_1:
	.string "A rare specimen from Paldea. Take good\n"
	.string "care of it!$"

BattleCafe_ChooseShinyGenome_Text_0:
	.string "Exchange 4 Café Points for a\n"
	.string "Shiny Genome?$"

BattleCafe_ChooseShinyGenome_Text_1:
	.string "A rare find. Use it on whichever\n"
	.string "Pokémon you want to bring out the\l"
	.string "shine.$"

BattleCafe_ChooseGoldBottleCaps_Text_0:
	.string "Exchange 5 Café Points for two\n"
	.string "Gold Bottle Caps?$"

BattleCafe_ChooseGoldBottleCaps_Text_1:
	.string "Two Gold Bottle Caps, polished up and\n"
	.string "ready. Here you go!$"

BattleCafe_ChooseMoney_Text_0:
	.string "Exchange 5 Café Points for\n"
	.string "¥250,000?$"

BattleCafe_ChooseMoney_Text_1:
	.string "Use it well, and perhaps spend a little\n"
	.string "on dessert!$"

BattleCafe_ChooseVitaminSetAtk_Text_0:
	.string "Exchange 4 Café Points for two each of\n"
	.string "Protein EX and Calcium EX?$"

BattleCafe_ChooseVitaminSetAtk_Text_1:
	.string "Two Protein EX and two Calcium EX,\n"
	.string "power and wisdom!$"

BattleCafe_ChooseVitaminSetDef_Text_0:
	.string "Exchange 4 Café Points for two each of\n"
	.string "Iron EX and Zinc EX?$"

BattleCafe_ChooseVitaminSetDef_Text_1:
	.string "Two Iron EX and two Zinc EX,\n"
	.string "time to bulk up!$"

BattleCafe_ChooseVitaminSetSpe_Text_0:
	.string "Exchange 2 Café Points for\n"
	.string "two Carbos EX?$"

BattleCafe_ChooseVitaminSetSpe_Text_1:
	.string "Two Carbos EX, ready to speed up!$"

BattleCafe_NotEnoughPoints_Text_0:
	.string "That prize costs 5 Café Points.\n"
	.string "Complete one of my challenges and try\l"
	.string "again!$"

BattleCafe_NotEnoughLegendPoints_Text_0:
	.string "That prize costs 25 Café Points.\n"
	.string "Complete more of my challenges and\l"
	.string "try again!$"

BattleCafe_NotEnoughFourPoints_Text_0:
	.string "The Shiny Genome costs 4 Café Points.\n"
	.string "Complete one of my challenges and try\l"
	.string "again!$"

BattleCafe_NotEnoughVitaminSetPoints_Text_0:
	.string "You don't have enough Café Points for\n"
	.string "that vitamin set. \p"
	.string "Complete one of my\n"
	.string "challenges and try again!$"

BattleCafe_NotEnoughBagSpace_Text_0:
	.string "Your Bag is too full for that prize.\n"
	.string "Make some room and come back whenever\l"
	.string "you're ready!$"

BattleCafe_Goodbye_Text_0:
	.string "Come back hungry for another battle!$"

BattleCafe_TrainerAthena_Text_0:
	.string "Did you have fun? Let's try this\n"
	.string "again tomorrow!$"

BattleCafe_TrainerAthena_Text_1:
	.string "Let's see if you can survive this\n"
	.string "stall!$"

BattleCafe_TrainerAthena_Text_2:
	.string "Huh?$"

BattleCafe_TrainerAthena_Text_3:
	.string "Did you have fun?$"

BattleCafe_TrainerDoves_Text_0:
	.string "Doves: Let's fight again tomorrow when \n"
	.string "my Genesect is allowed on the \l"
	.string "battlefield.$"

BattleCafe_TrainerDoves_Text_1:
	.string "Doves: Let me show you the power of \n"
	.string "Genesect!$"

BattleCafe_TrainerDoves_Text_2:
	.string "Banned again from Overused...$"

BattleCafe_TrainerDoves_Text_3:
	.string "Doves: Let's fight again tomorrow when\n"
	.string "my Genesect is allowed on the \l"
	.string "battlefield.$"

BattleCafe_TrainerElton_Text_0:
	.string "Elton: Rematch tomorrow! Be there!$"

BattleCafe_TrainerElton_Text_1:
	.string "Elton: Let's have a battle with our\n"
	.string "favourite Pokémon!$"

BattleCafe_TrainerElton_Text_2:
	.string "You handled every trick I had!$"

BattleCafe_TrainerElton_Text_3:
	.string "Elton: Even Gengar's impressed, and it\n"
	.string "rarely takes a loss seriously.$"

BattleCafe_TrainerNem_Text_0:
	.string "Nem: Come back tomorrow.$"

BattleCafe_TrainerNem_Text_1:
	.string "Nem: Think fast!$"

BattleCafe_TrainerNem_Text_2:
	.string "I'll be watching.$"

BattleCafe_TrainerNem_Text_3:
	.string "Nem: We can fight again tomorrow.$"

BattleCafe_TrainerBai_Text_0:
	.string "Bai: That was a good match!\n"
	.string "Let's fight again tomorrow!$"

BattleCafe_TrainerBai_Text_1:
	.string "Bai: Let's see what you bring to \n"
	.string "the table!$"

BattleCafe_TrainerBai_Text_2:
	.string "Guess I'm cooked this time...$"

BattleCafe_TrainerBai_Text_3:
	.string "Bai: Good match! Let's try this again \n"
	.string "tomorrow!$"

BattleCafe_TrainerDrac_Text_0:
	.string "Drac: You're really tough! Let's fight\n"
	.string "again tomorrow!$"

BattleCafe_TrainerDrac_Text_1:
	.string "Drac: Care for a double battle?$"

BattleCafe_TrainerDrac_Text_2:
	.string "Soothed.$"

BattleCafe_TrainerSimpli_Text_0:
	.string "Tomorrow will surely be better.$"

BattleCafe_TrainerSimpli_Text_1:
	.string "Gamble with the rain!$"

BattleCafe_TrainerSimpli_Text_2:
	.string "Weathered...$"

BattleCafe_TrainerSimpli_Text_3:
	.string "Maybe tomorrow will go better.$"

BattleCafe_TrainerTylarie_Text_0:
	.string "Steelix has settled down for\n"
	.string "lunch. We'll be ready tomorrow!$"

BattleCafe_TrainerTylarie_Text_1:
	.string "Tylarie: Let me show you how sturdy my\n"
	.string "team is!$"

BattleCafe_TrainerTylarie_Text_2:
	.string "Ouch.$"

BattleCafe_TrainerTylarie_Text_3:
	.string "Tylarie: Not bad. We can go at it again\n"
	.string "another day.$"

BattleCafe_FreshWaterFountain_Text_0:
	.string "It's a small fountain of water.$"

BattleCafe_FreshWaterFountain_Text_1:
	.string "You decide to grab some fresh water\n"
	.string "from the fountain.$"

BattleCafe_FreshWaterFountain_Text_2:
	.string "Stay hydrated.$"
