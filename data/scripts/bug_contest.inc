BugContest_EventScript_Start::
	end

BugContest_EventScript_WhiteOut::
	lockall
	delay 200
	msgbox BugContest_Text_WhiteOut, MSGBOX_DEFAULT
	closemessage
	goto BugContest_EventScript_End
	end

BugContest_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	msgbox BugContest_Text_TimesUp, MSGBOX_DEFAULT
	closemessage
	waitse
	getpartysize
	goto_if_eq VAR_RESULT, 1, BugContest_EventScript_Didntcatch
	fadescreen FADE_TO_BLACK
	setvar VAR_BUG_CONTEST_STATE, 3
	
	msgbox BugContest_Text_Judging0, MSGBOX_DEFAULT
	closemessage
	BugContest_EventScript_TimesUp2::
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BugContest_EventScript_WrongChoiceMon
	special ValidateBugContestSelectedMon
	goto_if_eq VAR_RESULT, FALSE, BugContest_EventScript_WrongChoiceMon
	fadescreen FADE_TO_BLACK
	warp MAP_NATIONAL_PARK_BUG_CONTEST, 5
	delay 90
	end

BugContest_EventScript_WrongChoiceMon::
	msgbox BugContest_Text_WrongChoiceMon, MSGBOX_DEFAULT
	goto BugContest_EventScript_TimesUp2
	end

BugContestEventScript_Judging::
	msgbox BugContest_Text_Judging1, MSGBOX_DEFAULT
	closemessage
	special JudgeBugContestMon
	call_if_eq VAR_RESULT, 1, BugContest_EventScript_First
	call_if_eq VAR_RESULT, 2, BugContest_EventScript_Second
	call_if_eq VAR_RESULT, 3, BugContest_EventScript_Third

BugContestEventScript_JudgingFinish::
	special TransferBugContestMon
	delay 20
	giveitem VAR_0x8005
	msgbox BugContest_Text_TransferAndReturn, MSGBOX_DEFAULT
	playse SE_SUCCESS
	waitse
	msgbox BugContest_Text_TakePartInFuture, MSGBOX_DEFAULT
	closemessage
	goto BugContest_EventScript_End
	end

BugContest_EventScript_Didntcatch::
	msgbox BugContest_Text_DidntCatch, MSGBOX_DEFAULT
	playse SE_SUCCESS
	closemessage
	fadescreen FADE_TO_BLACK
	goto BugContest_EventScript_End
	end

BugContest_EventScript_First::
	msgbox BugContest_Text_First1, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_First2, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_First3, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	call BugContest_EventScript_ChooseFirstPlaceReward
	closemessage
	goto BugContestEventScript_JudgingFinish

BugContest_EventScript_Second::
	msgbox BugContest_Text_Second1, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Second2, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Second3, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	call BugContest_EventScript_ChooseSecondPlaceReward
	closemessage
	goto BugContestEventScript_JudgingFinish

BugContest_EventScript_Third::
	msgbox BugContest_Text_Third1, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Third2, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Third3, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	closemessage
	goto BugContestEventScript_JudgingFinish

BugContest_EventScript_ChooseFirstPlaceReward::
	msgbox BugContest_Text_FirstPlaceRewardPrompt, MSGBOX_DEFAULT
	call BugContest_EventScript_ChooseFirstPlaceRewardLoop
	return

BugContest_EventScript_ChooseFirstPlaceRewardLoop::
	dynmultichoice 0, 0, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, BugContest_Text_FirstRewardMoonStone, BugContest_Text_FirstRewardSunStone, BugContest_Text_FirstRewardLeafStone, BugContest_Text_FirstRewardDawnStone, BugContest_Text_FirstRewardShinyStone, BugContest_Text_FirstRewardDuskStone, BugContest_Text_FirstRewardIceStone
	switch VAR_RESULT
	case 0, BugContest_EventScript_SetFirstPlaceMoonStone
	case 1, BugContest_EventScript_SetFirstPlaceSunStone
	case 2, BugContest_EventScript_SetFirstPlaceLeafStone
	case 3, BugContest_EventScript_SetFirstPlaceDawnStone
	case 4, BugContest_EventScript_SetFirstPlaceShinyStone
	case 5, BugContest_EventScript_SetFirstPlaceDuskStone
	case 6, BugContest_EventScript_SetFirstPlaceIceStone
	return

BugContest_EventScript_SetFirstPlaceMoonStone::
	setvar VAR_0x8005, ITEM_MOON_STONE
	return

BugContest_EventScript_SetFirstPlaceSunStone::
	setvar VAR_0x8005, ITEM_SUN_STONE
	return

BugContest_EventScript_SetFirstPlaceLeafStone::
	setvar VAR_0x8005, ITEM_LEAF_STONE
	return

BugContest_EventScript_SetFirstPlaceDawnStone::
	setvar VAR_0x8005, ITEM_DAWN_STONE
	return

BugContest_EventScript_SetFirstPlaceShinyStone::
	setvar VAR_0x8005, ITEM_SHINY_STONE
	return

BugContest_EventScript_SetFirstPlaceDuskStone::
	setvar VAR_0x8005, ITEM_DUSK_STONE
	return

BugContest_EventScript_SetFirstPlaceIceStone::
	setvar VAR_0x8005, ITEM_ICE_STONE
	return

BugContest_EventScript_ChooseSecondPlaceReward::
	msgbox BugContest_Text_SecondPlaceRewardPrompt, MSGBOX_DEFAULT
	call BugContest_EventScript_ChooseSecondPlaceRewardLoop
	return

BugContest_EventScript_ChooseSecondPlaceRewardLoop::
	dynmultichoice 0, 0, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, BugContest_Text_SecondRewardFireStone, BugContest_Text_SecondRewardThunderStone, BugContest_Text_SecondRewardWaterStone
	switch VAR_RESULT
	case 0, BugContest_EventScript_SetSecondPlaceFireStone
	case 1, BugContest_EventScript_SetSecondPlaceThunderStone
	case 2, BugContest_EventScript_SetSecondPlaceWaterStone
	return

BugContest_EventScript_SetSecondPlaceFireStone::
	setvar VAR_0x8005, ITEM_FIRE_STONE
	return

BugContest_EventScript_SetSecondPlaceThunderStone::
	setvar VAR_0x8005, ITEM_THUNDER_STONE
	return

BugContest_EventScript_SetSecondPlaceWaterStone::
	setvar VAR_0x8005, ITEM_WATER_STONE
	return

BugContest_EventScript_End::
	special HealPlayerParty
	special ExitBugContestMode
	setvar VAR_BUG_CONTEST_STATE, 0
	special RemoveSafariBalls
	setflag FLAG_DAILY_BUG_DONE
	goto_if_eq VAR_TEMP_1, 1, BugContest_EventScript_SideEnd
	warp MAP_GATE_NATIONAL_PARK, 18, 2
	waitstate
	releaseall
	end

BugContest_EventScript_SideEnd::
	warp MAP_GATE_NATIONAL_PARK, 35, 7
	releaseall
	end

BugContest_Text_Judging0::
	.string "The contest has now concluded.\n"
	.string "Please pick the Pokémon you would\l"
	.string "like to keep and have judged.$"

BugContest_Text_Judging1::
	.string "We will now judge the Pokémon\n"
	.string "you've caught.\p"
	.string "...................\n"
	.string "...................\p"
	.string "We have chosen the winners! Are\n"
	.string "ready for this?$"

BugContest_Text_WrongChoiceMon:
	.string "Please pick the Pokémon you would\n"
	.string "like to keep and have judged.$"

BugContest_Text_DidntCatch:
	.string "Oh no! You didn't catch a Pokémon.\n"
	.string "You've forfeited the competition.\p"
	.string "Your party will now be returned.$"

BugContest_Text_TimesUp:
	.string "Ding-dong! Time's up!$"

BugContest_Text_WhiteOut:
	.string "{PLAYER} is out of useable Pokémon.\n"
	.string "{PLAYER} forfeited the contest.$"

BugContest_Text_First1:
	.string "Placing third is the Cooltrainer\n"
	.string "Belinda, who caught a wriggling\l"
	.string "Butterfree!$"
BugContest_Text_First2:
	.string "Placing second is the Bugcatcher\n"
	.string "Shaun, who caught a writhing\l"
	.string "Pinsir!$"
BugContest_Text_First3:
	.string "This Bug-Catching Contest Winner\n"
	.string "is...\p"
	.string "{PLAYER}, who caught a whopping\n"
	.string "{STR_VAR_1}!$"

BugContest_Text_Second1:
	.string "Placing second is the Cooltrainer\n"
	.string "Belinda, who caught a wriggling\l"
	.string "Butterfree!$"
BugContest_Text_Second2:
	.string "Placing second is {PLAYER}, who\n"
	.string "caught a writhing {STR_VAR_1}!$"
BugContest_Text_Second3:
	.string "This Bug-Catching Contest Winner\n"
	.string "is...\p"
	.string "Bugcatcher Shaun, who caught a\n"
	.string "whopping Pinsir!$"


BugContest_Text_Third1:
	.string "Placing third is {PLAYER}, who\n"
	.string "caught a wriggling {STR_VAR_1}!$"
BugContest_Text_Third2:
	.string "Placing second is the Cooltrainer\n"
	.string "Belinda, who caught a writhing\l"
	.string "Butterfree!$"
BugContest_Text_Third3:
	.string "This Bug-Catching Contest Winner\n"
	.string "is...\p"
	.string "Bugcatcher Shaun, who caught a\n"
	.string "whopping Pinsir!$"

BugContest_Text_TakePartInFuture:
	.string "Thank you for participating!\n"
	.string "We hope you'll take part in the\l"
	.string "future.$"

BugContest_Text_TransferAndReturn:
	.string "Your chosen Bug Pokémon will now\n"
	.string "be sent to the PC and your party\l"
	.string "will be returned to you.$"

BugContest_Text_FirstPlaceRewardPrompt:
	.string "As the winner, you may choose one\n"
	.string "special prize.$"

BugContest_Text_SecondPlaceRewardPrompt:
	.string "For second place, please choose\n"
	.string "one of these stones.$"

BugContest_Text_FirstRewardMoonStone:
	.string "Moon Stone$"

BugContest_Text_FirstRewardSunStone:
	.string "Sun Stone$"

BugContest_Text_FirstRewardLeafStone:
	.string "Leaf Stone$"

BugContest_Text_FirstRewardDawnStone:
	.string "Dawn Stone$"

BugContest_Text_FirstRewardShinyStone:
	.string "Shiny Stone$"

BugContest_Text_FirstRewardIceStone:
	.string "Ice Stone$"

BugContest_Text_FirstRewardDuskStone:
	.string "Dusk Stone$"

BugContest_Text_SecondRewardFireStone:
	.string "Fire Stone$"

BugContest_Text_SecondRewardThunderStone:
	.string "Thunder Stone$"

BugContest_Text_SecondRewardWaterStone:
	.string "Water Stone$"
