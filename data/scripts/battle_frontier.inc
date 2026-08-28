BattleFrontier_ShowCaughtBannedSpecies::
	goto_if_eq VAR_0x8005, 0, BattleFrontier_ShowCaughtBannedSpeciesEnd
	msgbox BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ShowCaughtBannedSpeciesEnd
	callnative ShowBattleFrontierCaughtBannedSpecies
	waitstate
BattleFrontier_ShowCaughtBannedSpeciesEnd:
	return


BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies:
	.string "Do you want to see the list of\n"
	.string "Pokémon species you can't bring?$"

BattleFrontier_EventScript_ShowLevelModeInfo::
	msgbox BattleFrontier_Text_LevelModeInfo, MSGBOX_DEFAULT
	return

BattleFrontier_EventScript_ChooseInnates::
	goto_if_set FLAG_BATTLE_FACILITY_NO_INNATES, BattleFrontier_EventScript_EnableInnates
	msgbox BattleFrontier_Text_DisableInnates, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, BattleFrontier_EventScript_ChooseInnatesEnd
	setflag FLAG_BATTLE_FACILITY_NO_INNATES
	playse SE_SWITCH
	waitse
	msgbox BattleFrontier_Text_InnatesDisabled, MSGBOX_DEFAULT
	return

BattleFrontier_EventScript_EnableInnates:
	msgbox BattleFrontier_Text_EnableInnates, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, BattleFrontier_EventScript_ChooseInnatesEnd
	clearflag FLAG_BATTLE_FACILITY_NO_INNATES
	playse SE_SWITCH
	waitse
	msgbox BattleFrontier_Text_InnatesEnabled, MSGBOX_DEFAULT
BattleFrontier_EventScript_ChooseInnatesEnd:
	return

BattleFrontier_EventScript_ChooseBattleBgm::
	message BattleFrontier_Text_ChooseBattleBgm
	waitmessage
	special BuildBattleFacilityBgmMenu
	dynmultistack 0, 0, FALSE, 6, FALSE, VAR_BATTLE_FACILITY_BGM, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_EventScript_ChooseBattleBgmEnd
	copyvar VAR_BATTLE_FACILITY_BGM, VAR_RESULT
	msgbox BattleFrontier_Text_BattleBgmUpdated, MSGBOX_DEFAULT
BattleFrontier_EventScript_ChooseBattleBgmEnd:
	return

BattleFrontier_Text_LevelModeInfo:
	.string "In Classic, your party is scaled to\n"
	.string "Lv. 50, and restricted legends are\l"
	.string "excluded from facility battles.\p"
	.string "In Chaos, your party is scaled to\n"
	.string "Lv. 100, and anything goes.\p"
	.string "Innates can be enabled or disabled\n"
	.string "separately.$"

BattleFrontier_Text_DisableInnates:
	.string "Innates are currently enabled.\n"
	.string "Disable them?$"

BattleFrontier_Text_EnableInnates:
	.string "Innates are currently disabled.\n"
	.string "Enable them?$"

BattleFrontier_Text_InnatesDisabled:
	.string "Innates are now disabled in all\n"
	.string "facilities.$"

BattleFrontier_Text_InnatesEnabled:
	.string "Innates are now enabled in all\n"
	.string "facilities.$"

BattleFrontier_Text_ChooseBattleBgm:
	.string "Choose the music for facility battles.$"

BattleFrontier_Text_BattleBgmUpdated:
	.string "The facility battle BGM was updated.$"
