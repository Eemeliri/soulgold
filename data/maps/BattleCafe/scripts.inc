# 1 "data/maps/BattleCafe/scripts.pory"

# 2 "data/maps/BattleCafe/scripts.pory"
BattleCafe_MapScripts::
# 3 "data/maps/BattleCafe/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, BattleCafe_OnTransition
# 4 "data/maps/BattleCafe/scripts.pory"
	.byte 0

BattleCafe_OnTransition::
# 8 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_HIDE_BATTLE_CAFE_OPPONENT
# 9 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_VISITED_ROUTE50
	end


BattleCafe_Owner::
# 14 "data/maps/BattleCafe/scripts.pory"
	lock
# 15 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 17 "data/maps/BattleCafe/scripts.pory"
	goto_if_unset FLAG_BATTLE_CAFE_DIANCIE_RECEIVED, BattleCafe_Owner_4
BattleCafe_Owner_1:
# 28 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_Owner_2:
# 26 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_GiveDiancie
	goto BattleCafe_Owner_1

BattleCafe_Owner_3:
# 19 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_DOVES
	goto_if 1, BattleCafe_Owner_8
	goto BattleCafe_Owner_1

BattleCafe_Owner_4:
# 18 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_ATHENA
	goto_if 1, BattleCafe_Owner_3
	goto BattleCafe_Owner_1

BattleCafe_Owner_7:
# 21 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_NEM
	goto_if 1, BattleCafe_Owner_12
	goto BattleCafe_Owner_1

BattleCafe_Owner_8:
# 20 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_ELTON
	goto_if 1, BattleCafe_Owner_7
	goto BattleCafe_Owner_1

BattleCafe_Owner_11:
# 23 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_DRAC
	goto_if 1, BattleCafe_Owner_16
	goto BattleCafe_Owner_1

BattleCafe_Owner_12:
# 22 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_BAI
	goto_if 1, BattleCafe_Owner_11
	goto BattleCafe_Owner_1

BattleCafe_Owner_15:
# 25 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_TYLARIE
	goto_if 1, BattleCafe_Owner_2
	goto BattleCafe_Owner_1

BattleCafe_Owner_16:
# 24 "data/maps/BattleCafe/scripts.pory"
	checktrainerflag TRAINER_CAFE_JUNA
	goto_if 1, BattleCafe_Owner_15
	goto BattleCafe_Owner_1


BattleCafe_GiveDiancie::
# 32 "data/maps/BattleCafe/scripts.pory"
	goto_if_unset FLAG_BATTLE_CAFE_DIANCIE_READY, BattleCafe_GiveDiancie_2
# 48 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_GiveDiancie_Text_2, MSGBOX_YESNO
# 52 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_GiveDiancie_5
BattleCafe_GiveDiancie_4:
# 58 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DIANCIE
# 59 "data/maps/BattleCafe/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_DIANCIE
# 60 "data/maps/BattleCafe/scripts.pory"
	givemon SPECIES_DIANCIE, 70
# 61 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq BattleCafe_GiveDiancie_8
BattleCafe_GiveDiancie_7:
# 64 "data/maps/BattleCafe/scripts.pory"
	showgivemonpic 10, 3
# 65 "data/maps/BattleCafe/scripts.pory"
	call Common_EventScript_GiftMon
# 66 "data/maps/BattleCafe/scripts.pory"
	hidemonpic
# 67 "data/maps/BattleCafe/scripts.pory"
	clearflag FLAG_BATTLE_CAFE_DIANCIE_READY
# 68 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_DIANCIE_RECEIVED
# 69 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_GiveDiancie_Text_4
# 71 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_GiveDiancie_2:
# 33 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_GiveDiancie_Text_0
# 39 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_GiveDiancie_Text_1
# 43 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_DIANCIE_READY
# 44 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_GiveDiancie_5:
# 53 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_GiveDiancie_Text_3
# 55 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_GiveDiancie_4

BattleCafe_GiveDiancie_8:
# 62 "data/maps/BattleCafe/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
	goto BattleCafe_GiveDiancie_7


BattleCafe_OwnerMenu::
# 75 "data/maps/BattleCafe/scripts.pory"
	goto_if_unset FLAG_CAFE_INTRO_DONE, BattleCafe_OwnerMenu_2
BattleCafe_OwnerMenu_1:
# 95 "data/maps/BattleCafe/scripts.pory"
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_OwnerMenu_6
BattleCafe_OwnerMenu_4:
# 103 "data/maps/BattleCafe/scripts.pory"
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_OwnerMenu_11
BattleCafe_OwnerMenu_9:
# 112 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_OwnerMenu_Text_3
# 113 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_OwnerMenu_15
# 114 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_OwnerMenu_15
BattleCafe_OwnerMenu_14:
# 136 "data/maps/BattleCafe/scripts.pory"
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_OwnerMenu_Text_4, BattleCafe_OwnerMenu_Text_5, BattleCafe_OwnerMenu_Text_6, BattleCafe_OwnerMenu_Text_7, BattleCafe_OwnerMenu_Text_9, BattleCafe_OwnerMenu_Text_10, BattleCafe_OwnerMenu_Text_11
# 144 "data/maps/BattleCafe/scripts.pory"
	switch VAR_RESULT
# 145 "data/maps/BattleCafe/scripts.pory"
	case 0, BattleCafe_OwnerMenu_20
# 146 "data/maps/BattleCafe/scripts.pory"
	case 1, BattleCafe_OwnerMenu_21
# 147 "data/maps/BattleCafe/scripts.pory"
	case 2, BattleCafe_OwnerMenu_22
# 148 "data/maps/BattleCafe/scripts.pory"
	case 3, BattleCafe_OwnerMenu_23
# 149 "data/maps/BattleCafe/scripts.pory"
	case 4, BattleCafe_OwnerMenu_24
# 150 "data/maps/BattleCafe/scripts.pory"
	case 5, BattleCafe_OwnerMenu_25
# 151 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_Goodbye
	return

BattleCafe_OwnerMenu_2:
# 76 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_OwnerMenu_Text_0
# 92 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_CAFE_INTRO_DONE
	goto BattleCafe_OwnerMenu_1

BattleCafe_OwnerMenu_5:
# 97 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_OwnerMenu_Text_1
# 101 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED
	goto BattleCafe_OwnerMenu_4

BattleCafe_OwnerMenu_6:
# 96 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_CHALLENGE_WON, BattleCafe_OwnerMenu_5
	goto BattleCafe_OwnerMenu_4

BattleCafe_OwnerMenu_10:
# 105 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_OwnerMenu_Text_2
# 109 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED
	goto BattleCafe_OwnerMenu_9

BattleCafe_OwnerMenu_11:
# 104 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_RUSH_WON, BattleCafe_OwnerMenu_10
	goto BattleCafe_OwnerMenu_9

BattleCafe_OwnerMenu_15:
# 115 "data/maps/BattleCafe/scripts.pory"
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_OwnerMenu_Text_4, BattleCafe_OwnerMenu_Text_5, BattleCafe_OwnerMenu_Text_6, BattleCafe_OwnerMenu_Text_7, BattleCafe_OwnerMenu_Text_8, BattleCafe_OwnerMenu_Text_9, BattleCafe_OwnerMenu_Text_10, BattleCafe_OwnerMenu_Text_11
# 124 "data/maps/BattleCafe/scripts.pory"
	switch VAR_RESULT
# 125 "data/maps/BattleCafe/scripts.pory"
	case 0, BattleCafe_OwnerMenu_28
# 126 "data/maps/BattleCafe/scripts.pory"
	case 1, BattleCafe_OwnerMenu_29
# 127 "data/maps/BattleCafe/scripts.pory"
	case 2, BattleCafe_OwnerMenu_30
# 128 "data/maps/BattleCafe/scripts.pory"
	case 3, BattleCafe_OwnerMenu_31
# 129 "data/maps/BattleCafe/scripts.pory"
	case 4, BattleCafe_OwnerMenu_32
# 130 "data/maps/BattleCafe/scripts.pory"
	case 5, BattleCafe_OwnerMenu_33
# 131 "data/maps/BattleCafe/scripts.pory"
	case 6, BattleCafe_OwnerMenu_34
# 132 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_Goodbye
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_20:
# 145 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskDailyChallenge
	return

BattleCafe_OwnerMenu_21:
# 146 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskRushMode
	return

BattleCafe_OwnerMenu_22:
# 147 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskSuperChallenge
	return

BattleCafe_OwnerMenu_23:
# 148 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskSuperRush
	return

BattleCafe_OwnerMenu_24:
# 149 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_OwnerMenu_25:
# 150 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OptionsMenu
	return

BattleCafe_OwnerMenu_28:
# 125 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskDailyChallenge
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_29:
# 126 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskRushMode
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_30:
# 127 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskSuperChallenge
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_31:
# 128 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskSuperRush
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_32:
# 129 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_33:
# 130 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_OwnerMenu_14

BattleCafe_OwnerMenu_34:
# 131 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OptionsMenu
	goto BattleCafe_OwnerMenu_14


BattleCafe_OptionsMenu::
# 156 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_OptionsMenu_Text_0
# 157 "data/maps/BattleCafe/scripts.pory"
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_OptionsMenu_Text_1, BattleCafe_OptionsMenu_Text_2, BattleCafe_OptionsMenu_Text_3, BattleCafe_OptionsMenu_Text_4, BattleCafe_OptionsMenu_Text_5
# 163 "data/maps/BattleCafe/scripts.pory"
	switch VAR_RESULT
# 164 "data/maps/BattleCafe/scripts.pory"
	case 0, BattleCafe_OptionsMenu_2
# 165 "data/maps/BattleCafe/scripts.pory"
	case 1, BattleCafe_OptionsMenu_3
# 166 "data/maps/BattleCafe/scripts.pory"
	case 2, BattleCafe_OptionsMenu_4
# 167 "data/maps/BattleCafe/scripts.pory"
	case 3, BattleCafe_OptionsMenu_5
# 168 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_OptionsMenu_2:
# 164 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseBattleBgm
	return

BattleCafe_OptionsMenu_3:
# 165 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ViewHighScores
	return

BattleCafe_OptionsMenu_4:
# 166 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseInnates
	return

BattleCafe_OptionsMenu_5:
# 167 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ExplainRules
	return


BattleCafe_ChooseBattleBgm::
# 173 "data/maps/BattleCafe/scripts.pory"
	call BattleFrontier_EventScript_ChooseBattleBgm
# 174 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return


BattleCafe_ViewHighScores::
# 178 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 179 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_ShowRecordsWindow
# 180 "data/maps/BattleCafe/scripts.pory"
	waitbuttonpress
# 181 "data/maps/BattleCafe/scripts.pory"
	special RemoveRecordsWindow
# 182 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return


BattleCafe_ChooseInnates::
# 186 "data/maps/BattleCafe/scripts.pory"
	call BattleFrontier_EventScript_ChooseInnates
# 187 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OptionsMenu
	return


BattleCafe_ExplainRules::
# 191 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainRules_Text_0
# 201 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainRules_Text_1
# 208 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainRules_Text_2
# 216 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainRules_Text_3
# 223 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_ExplainRules_2
# 224 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_ExplainRules_2
BattleCafe_ExplainRules_1:
# 238 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_ExplainRules_2:
# 225 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainRules_Text_4
# 231 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainRules_Text_5
	goto BattleCafe_ExplainRules_1


BattleCafe_AskDailyChallenge::
# 242 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_CHALLENGE_WON, BattleCafe_AskDailyChallenge_2
BattleCafe_AskDailyChallenge_1:
# 250 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskDailyChallenge_Text_1, MSGBOX_YESNO
# 257 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskDailyChallenge_5
BattleCafe_AskDailyChallenge_4:
# 260 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY
# 261 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskDailyChallenge_2:
# 243 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskDailyChallenge_Text_0
# 248 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskDailyChallenge_1

BattleCafe_AskDailyChallenge_5:
# 258 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskDailyChallenge_4


BattleCafe_AskRushMode::
# 265 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_RUSH_WON, BattleCafe_AskRushMode_2
BattleCafe_AskRushMode_1:
# 273 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskRushMode_Text_1, MSGBOX_YESNO
# 280 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskRushMode_5
BattleCafe_AskRushMode_4:
# 283 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_RUSH
# 284 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskRushMode_2:
# 266 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskRushMode_Text_0
# 271 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskRushMode_1

BattleCafe_AskRushMode_5:
# 281 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskRushMode_4


BattleCafe_AskSuperChallenge::
# 288 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_CHALLENGE_WON, BattleCafe_AskSuperChallenge_2
BattleCafe_AskSuperChallenge_1:
# 296 "data/maps/BattleCafe/scripts.pory"
	specialvar VAR_RESULT, CountPartyNonEggMons
# 297 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskSuperChallenge_5
BattleCafe_AskSuperChallenge_4:
# 303 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskSuperChallenge_Text_2, MSGBOX_YESNO
# 309 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskSuperChallenge_8
BattleCafe_AskSuperChallenge_7:
# 312 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_CHALLENGE
# 313 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskSuperChallenge_2:
# 289 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskSuperChallenge_Text_0
# 294 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperChallenge_1

BattleCafe_AskSuperChallenge_5:
# 298 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskSuperChallenge_Text_1
# 301 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperChallenge_4

BattleCafe_AskSuperChallenge_8:
# 310 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperChallenge_7


BattleCafe_AskSuperRush::
# 317 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SUPER_RUSH_WON, BattleCafe_AskSuperRush_2
BattleCafe_AskSuperRush_1:
# 325 "data/maps/BattleCafe/scripts.pory"
	specialvar VAR_RESULT, CountPartyNonEggMons
# 326 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskSuperRush_5
BattleCafe_AskSuperRush_4:
# 334 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskSuperRush_Text_2, MSGBOX_YESNO
# 341 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskSuperRush_8
BattleCafe_AskSuperRush_7:
# 344 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_RUSH
# 345 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskSuperRush_2:
# 318 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskSuperRush_Text_0
# 323 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperRush_1

BattleCafe_AskSuperRush_5:
# 327 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskSuperRush_Text_1
# 332 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperRush_4

BattleCafe_AskSuperRush_8:
# 342 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	goto BattleCafe_AskSuperRush_7


BattleCafe_EndlessMenu::
# 349 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_EndlessMenu_Text_0
# 350 "data/maps/BattleCafe/scripts.pory"
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, BattleCafe_EndlessMenu_Text_1, BattleCafe_EndlessMenu_Text_2, BattleCafe_EndlessMenu_Text_3, BattleCafe_OptionsMenu_Text_5
# 355 "data/maps/BattleCafe/scripts.pory"
	switch VAR_RESULT
# 356 "data/maps/BattleCafe/scripts.pory"
	case 0, BattleCafe_EndlessMenu_2
# 357 "data/maps/BattleCafe/scripts.pory"
	case 1, BattleCafe_EndlessMenu_3
# 358 "data/maps/BattleCafe/scripts.pory"
	case 2, BattleCafe_EndlessMenu_4
# 359 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_EndlessMenu_2:
# 356 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskEndlessChallenge
	return

BattleCafe_EndlessMenu_3:
# 357 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_AskEndlessRush
	return

BattleCafe_EndlessMenu_4:
# 358 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ExplainEndlessRules
	return


BattleCafe_ExplainEndlessRules::
# 364 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainEndlessRules_Text_0
# 371 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainEndlessRules_Text_1
# 378 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ExplainEndlessRules_Text_2
# 381 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	return


BattleCafe_AskEndlessChallenge::
# 385 "data/maps/BattleCafe/scripts.pory"
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_CHALLENGE_UNLOCKED, BattleCafe_AskEndlessChallenge_2
BattleCafe_AskEndlessChallenge_1:
# 390 "data/maps/BattleCafe/scripts.pory"
	specialvar VAR_RESULT, CountPartyNonEggMons
# 391 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskEndlessChallenge_5
BattleCafe_AskEndlessChallenge_4:
# 399 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskEndlessChallenge_Text_2, MSGBOX_YESNO
# 406 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskEndlessChallenge_8
BattleCafe_AskEndlessChallenge_7:
# 409 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
# 410 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskEndlessChallenge_2:
# 386 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskEndlessChallenge_Text_0
# 388 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessChallenge_1

BattleCafe_AskEndlessChallenge_5:
# 392 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskEndlessChallenge_Text_1
# 397 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessChallenge_4

BattleCafe_AskEndlessChallenge_8:
# 407 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessChallenge_7


BattleCafe_AskEndlessRush::
# 414 "data/maps/BattleCafe/scripts.pory"
	goto_if_unset FLAG_BATTLE_CAFE_ENDLESS_RUSH_UNLOCKED, BattleCafe_AskEndlessRush_2
BattleCafe_AskEndlessRush_1:
# 419 "data/maps/BattleCafe/scripts.pory"
	specialvar VAR_RESULT, CountPartyNonEggMons
# 420 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, PARTY_SIZE
	goto_if_lt BattleCafe_AskEndlessRush_5
BattleCafe_AskEndlessRush_4:
# 428 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskEndlessRush_Text_1, MSGBOX_YESNO
# 435 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_AskEndlessRush_8
BattleCafe_AskEndlessRush_7:
# 438 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
# 439 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_BeginChallenge
	return

BattleCafe_AskEndlessRush_2:
# 415 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskEndlessRush_Text_0
# 417 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessRush_1

BattleCafe_AskEndlessRush_5:
# 421 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_AskEndlessChallenge_Text_1
# 426 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessRush_4

BattleCafe_AskEndlessRush_8:
# 436 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessMenu
	goto BattleCafe_AskEndlessRush_7


BattleCafe_BeginChallenge::
# 443 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 444 "data/maps/BattleCafe/scripts.pory"
	hidefollower
# 445 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 446 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_InitChallenge
# 447 "data/maps/BattleCafe/scripts.pory"
	moveobjecttocoords LOCALID_PLAYER, 6, 13, DIR_EAST
# 448 "data/maps/BattleCafe/scripts.pory"
	waitmovement 0
# 449 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_9, 0
# 450 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_C, 0
# 451 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
	goto_if_eq BattleCafe_BeginChallenge_2
# 452 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
	goto_if_eq BattleCafe_BeginChallenge_2
# 456 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_BeginChallenge_Text_1
BattleCafe_BeginChallenge_1:
# 459 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 460 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChallengeNextRound
	return

BattleCafe_BeginChallenge_2:
# 453 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_BeginChallenge_Text_0
	goto BattleCafe_BeginChallenge_1


BattleCafe_ChallengeNextRound::
# 464 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_RunRound
# 465 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_ne BattleCafe_ChallengeNextRound_2
BattleCafe_ChallengeNextRound_1:
# 469 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_AdvanceWinCount
# 470 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
	goto_if_eq BattleCafe_ChallengeNextRound_5
BattleCafe_ChallengeNextRound_4:
# 491 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
	goto_if_eq BattleCafe_ChallengeNextRound_8
BattleCafe_ChallengeNextRound_7:
# 523 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_9, 3
	goto_if_ge BattleCafe_ChallengeNextRound_14
BattleCafe_ChallengeNextRound_13:
# 527 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY
	goto_if_eq BattleCafe_ChallengeNextRound_21
# 533 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_CHALLENGE
	goto_if_eq BattleCafe_ChallengeNextRound_27
# 539 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_RUSH
	goto_if_eq BattleCafe_ChallengeNextRound_30
# 543 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeNextRound_Text_6
BattleCafe_ChallengeNextRound_20:
# 548 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 549 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChallengeNextRound
	return

BattleCafe_ChallengeNextRound_2:
# 466 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChallengeLost
	goto BattleCafe_ChallengeNextRound_1

BattleCafe_ChallengeNextRound_5:
# 471 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, 1
# 472 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_AwardPoints
# 473 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_B, VAR_RESULT
# 474 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 475 "data/maps/BattleCafe/scripts.pory"
	playse SE_SHOP
# 476 "data/maps/BattleCafe/scripts.pory"
	waitse
# 477 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_9
# 478 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_2, VAR_TEMP_B
# 479 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeNextRound_Text_0, MSGBOX_YESNO
# 484 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChallengeNextRound_11
BattleCafe_ChallengeNextRound_10:
# 487 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 488 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChallengeNextRound
	goto BattleCafe_ChallengeNextRound_4

BattleCafe_ChallengeNextRound_8:
# 492 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, 2
# 493 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_AwardPoints
# 494 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_B, VAR_RESULT
# 495 "data/maps/BattleCafe/scripts.pory"
	addvar VAR_TEMP_C, 1
# 496 "data/maps/BattleCafe/scripts.pory"
	playse SE_SHOP
# 497 "data/maps/BattleCafe/scripts.pory"
	waitse
# 498 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_9
# 499 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_2, VAR_TEMP_B
# 500 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_C, 3
	goto_if_ge BattleCafe_ChallengeNextRound_17
# 510 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeNextRound_Text_2, MSGBOX_YESNO
BattleCafe_ChallengeNextRound_16:
# 516 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChallengeNextRound_25
BattleCafe_ChallengeNextRound_24:
# 519 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 520 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChallengeNextRound
	goto BattleCafe_ChallengeNextRound_7

BattleCafe_ChallengeNextRound_11:
# 485 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessRetired
	goto BattleCafe_ChallengeNextRound_10

BattleCafe_ChallengeNextRound_14:
# 524 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChallengeWon
	goto BattleCafe_ChallengeNextRound_13

BattleCafe_ChallengeNextRound_17:
# 501 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_C, 0
# 502 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 503 "data/maps/BattleCafe/scripts.pory"
	playse SE_USE_ITEM
# 504 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeNextRound_Text_1, MSGBOX_YESNO
	goto BattleCafe_ChallengeNextRound_16

BattleCafe_ChallengeNextRound_21:
# 528 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 529 "data/maps/BattleCafe/scripts.pory"
	playse SE_USE_ITEM
# 530 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeNextRound_Text_3
	goto BattleCafe_ChallengeNextRound_20

BattleCafe_ChallengeNextRound_25:
# 517 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_EndlessRetired
	goto BattleCafe_ChallengeNextRound_24

BattleCafe_ChallengeNextRound_27:
# 534 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 535 "data/maps/BattleCafe/scripts.pory"
	playse SE_USE_ITEM
# 536 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeNextRound_Text_4
	goto BattleCafe_ChallengeNextRound_20

BattleCafe_ChallengeNextRound_30:
# 540 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeNextRound_Text_5
	goto BattleCafe_ChallengeNextRound_20


BattleCafe_EndlessRetired::
# 553 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 554 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_EndChallenge
# 555 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 556 "data/maps/BattleCafe/scripts.pory"
	moveobjecttocoords LOCALID_PLAYER, 6, 24, DIR_NORTH
# 557 "data/maps/BattleCafe/scripts.pory"
	waitmovement 0
# 558 "data/maps/BattleCafe/scripts.pory"
	turnobject LOCALID_CAFE_OWNER, DIR_SOUTH
# 559 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_9
# 560 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_EndlessRetired_Text_0
# 564 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return


BattleCafe_RunRound::
# 568 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_0x8004, VAR_TEMP_9
# 569 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_SelectOpponent
# 570 "data/maps/BattleCafe/scripts.pory"
	setobjectxy LOCALID_BATTLE_CAFE_OPPONENT, 14, 17
# 571 "data/maps/BattleCafe/scripts.pory"
	addobject LOCALID_BATTLE_CAFE_OPPONENT
# 572 "data/maps/BattleCafe/scripts.pory"
	moveobjecttocoords LOCALID_BATTLE_CAFE_OPPONENT, 10, 13, DIR_WEST
# 573 "data/maps/BattleCafe/scripts.pory"
	waitmovement 0
# 574 "data/maps/BattleCafe/scripts.pory"
	tower_getopponentintro FRONTIER_BEFORE_TEXT
# 575 "data/maps/BattleCafe/scripts.pory"
	msgbox gStringVar4
# 576 "data/maps/BattleCafe/scripts.pory"
	closemessage
# 577 "data/maps/BattleCafe/scripts.pory"
	dofacilitytrainerbattle FACILITY_BATTLE_CAFE
# 578 "data/maps/BattleCafe/scripts.pory"
	waitstate
# 579 "data/maps/BattleCafe/scripts.pory"
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
# 580 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_A, VAR_RESULT
# 582 "data/maps/BattleCafe/scripts.pory"
	moveobjecttocoords LOCALID_BATTLE_CAFE_OPPONENT, 14, 17, DIR_EAST
# 583 "data/maps/BattleCafe/scripts.pory"
	waitmovement 0
# 584 "data/maps/BattleCafe/scripts.pory"
	removeobject LOCALID_BATTLE_CAFE_OPPONENT
# 586 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_A, B_OUTCOME_WON
	goto_if_eq BattleCafe_RunRound_2
# 589 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_RESULT, FALSE
BattleCafe_RunRound_1:
	return

BattleCafe_RunRound_2:
# 587 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_RESULT, TRUE
	goto BattleCafe_RunRound_1


BattleCafe_ChallengeLost::
# 595 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_EndChallenge
# 596 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 597 "data/maps/BattleCafe/scripts.pory"
	moveobjecttocoords LOCALID_PLAYER, 6, 24, DIR_NORTH
# 598 "data/maps/BattleCafe/scripts.pory"
	waitmovement 0
# 599 "data/maps/BattleCafe/scripts.pory"
	turnobject LOCALID_CAFE_OWNER, DIR_SOUTH
# 600 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_CHALLENGE
	goto_if_eq BattleCafe_ChallengeLost_2
# 601 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_ENDLESS_RUSH
	goto_if_eq BattleCafe_ChallengeLost_2
# 611 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeLost_Text_1
BattleCafe_ChallengeLost_1:
# 618 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_ChallengeLost_2:
# 602 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_9
# 603 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeLost_Text_0
	goto BattleCafe_ChallengeLost_1


BattleCafe_ChallengeWon::
# 622 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_EndChallenge
# 623 "data/maps/BattleCafe/scripts.pory"
	special HealPlayerParty
# 624 "data/maps/BattleCafe/scripts.pory"
	moveobjecttocoords LOCALID_PLAYER, 6, 24, DIR_NORTH
# 625 "data/maps/BattleCafe/scripts.pory"
	waitmovement 0
# 626 "data/maps/BattleCafe/scripts.pory"
	turnobject LOCALID_CAFE_OWNER, DIR_SOUTH
# 628 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_DAILY
	goto_if_eq BattleCafe_ChallengeWon_2
# 638 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_RUSH
	goto_if_eq BattleCafe_ChallengeWon_5
# 649 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_8, BATTLE_CAFE_MODE_SUPER_CHALLENGE
	goto_if_eq BattleCafe_ChallengeWon_8
# 660 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_SUPER_RUSH_WON
# 661 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, 10
# 662 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_AwardPoints
# 663 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_B, VAR_RESULT
# 664 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_B
# 665 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeWon_Text_3
BattleCafe_ChallengeWon_1:
# 675 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_UnlockClearAchievement
# 676 "data/maps/BattleCafe/scripts.pory"
	playse SE_SHOP
# 677 "data/maps/BattleCafe/scripts.pory"
	waitse
# 678 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_ChallengeWon_2:
# 629 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_CHALLENGE_WON
# 630 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, 3
# 631 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_AwardPoints
# 632 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_B, VAR_RESULT
# 633 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_B
# 634 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeWon_Text_0
	goto BattleCafe_ChallengeWon_1

BattleCafe_ChallengeWon_5:
# 639 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_RUSH_WON
# 640 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, 5
# 641 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_AwardPoints
# 642 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_B, VAR_RESULT
# 643 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_B
# 644 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeWon_Text_1
	goto BattleCafe_ChallengeWon_1

BattleCafe_ChallengeWon_8:
# 650 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_SUPER_CHALLENGE_WON
# 651 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, 5
# 652 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_AwardPoints
# 653 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_B, VAR_RESULT
# 654 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_TEMP_B
# 655 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChallengeWon_Text_2
	goto BattleCafe_ChallengeWon_1


BattleCafe_RewardMenu::
# 682 "data/maps/BattleCafe/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_BATTLE_CAFE_POINTS
# 683 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_RewardMenu_Text_0
# 685 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_GetParadoxRewardEligibility
# 686 "data/maps/BattleCafe/scripts.pory"
	copyvar VAR_TEMP_C, VAR_RESULT
# 687 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_1, 10
# 688 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_2, 11
# 689 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_3, 12
# 690 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_4, 7
# 691 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_5, 8
# 692 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_6, 9
# 693 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_7, 0
# 694 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_8, 1
# 695 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_9, 2
# 696 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_10, 3
# 697 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_11, 4
# 698 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_12, 5
# 699 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_13, 6
# 700 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_14, 16
# 701 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_15, 17
# 702 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_16, 18
# 703 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_17, 19
# 704 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_MIRAIDON
	goto_if_eq BattleCafe_RewardMenu_2
# 705 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_MIRAIDON + BATTLE_CAFE_PARADOX_REWARD_KORAIDON
	goto_if_eq BattleCafe_RewardMenu_2
BattleCafe_RewardMenu_1:
# 708 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_KORAIDON
	goto_if_eq BattleCafe_RewardMenu_7
# 709 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_C, BATTLE_CAFE_PARADOX_REWARD_MIRAIDON + BATTLE_CAFE_PARADOX_REWARD_KORAIDON
	goto_if_eq BattleCafe_RewardMenu_7
BattleCafe_RewardMenu_6:
# 712 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_OptionsMenu_Text_5, 15
# 713 "data/maps/BattleCafe/scripts.pory"
	dynmultistack 0, 0, FALSE, 6, FALSE, 10, DYN_MULTICHOICE_CB_NONE
# 714 "data/maps/BattleCafe/scripts.pory"
	switch VAR_RESULT
# 715 "data/maps/BattleCafe/scripts.pory"
	case 0, BattleCafe_RewardMenu_12
# 716 "data/maps/BattleCafe/scripts.pory"
	case 1, BattleCafe_RewardMenu_13
# 717 "data/maps/BattleCafe/scripts.pory"
	case 2, BattleCafe_RewardMenu_14
# 718 "data/maps/BattleCafe/scripts.pory"
	case 3, BattleCafe_RewardMenu_15
# 719 "data/maps/BattleCafe/scripts.pory"
	case 4, BattleCafe_RewardMenu_16
# 720 "data/maps/BattleCafe/scripts.pory"
	case 5, BattleCafe_RewardMenu_17
# 721 "data/maps/BattleCafe/scripts.pory"
	case 6, BattleCafe_RewardMenu_18
# 722 "data/maps/BattleCafe/scripts.pory"
	case 7, BattleCafe_RewardMenu_19
# 723 "data/maps/BattleCafe/scripts.pory"
	case 8, BattleCafe_RewardMenu_20
# 724 "data/maps/BattleCafe/scripts.pory"
	case 9, BattleCafe_RewardMenu_21
# 725 "data/maps/BattleCafe/scripts.pory"
	case 10, BattleCafe_RewardMenu_22
# 726 "data/maps/BattleCafe/scripts.pory"
	case 11, BattleCafe_RewardMenu_23
# 727 "data/maps/BattleCafe/scripts.pory"
	case 12, BattleCafe_RewardMenu_24
# 728 "data/maps/BattleCafe/scripts.pory"
	case 13, BattleCafe_RewardMenu_25
# 729 "data/maps/BattleCafe/scripts.pory"
	case 14, BattleCafe_RewardMenu_26
# 730 "data/maps/BattleCafe/scripts.pory"
	case 16, BattleCafe_RewardMenu_27
# 731 "data/maps/BattleCafe/scripts.pory"
	case 17, BattleCafe_RewardMenu_28
# 732 "data/maps/BattleCafe/scripts.pory"
	case 18, BattleCafe_RewardMenu_29
# 733 "data/maps/BattleCafe/scripts.pory"
	case 19, BattleCafe_RewardMenu_30
# 734 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_OwnerMenu
	return

BattleCafe_RewardMenu_2:
# 706 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_18, 13
	goto BattleCafe_RewardMenu_1

BattleCafe_RewardMenu_7:
# 710 "data/maps/BattleCafe/scripts.pory"
	dynmultipush BattleCafe_RewardMenu_Text_19, 14
	goto BattleCafe_RewardMenu_6

BattleCafe_RewardMenu_12:
# 715 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseArticuno
	return

BattleCafe_RewardMenu_13:
# 716 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseZapdos
	return

BattleCafe_RewardMenu_14:
# 717 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseMoltres
	return

BattleCafe_RewardMenu_15:
# 718 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseTornadus
	return

BattleCafe_RewardMenu_16:
# 719 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseThundurus
	return

BattleCafe_RewardMenu_17:
# 720 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseLandorus
	return

BattleCafe_RewardMenu_18:
# 721 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseEnamorus
	return

BattleCafe_RewardMenu_19:
# 722 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseShinyGenome
	return

BattleCafe_RewardMenu_20:
# 723 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseGoldBottleCaps
	return

BattleCafe_RewardMenu_21:
# 724 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseMoney
	return

BattleCafe_RewardMenu_22:
# 725 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseVitaminSetAtk
	return

BattleCafe_RewardMenu_23:
# 726 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseVitaminSetDef
	return

BattleCafe_RewardMenu_24:
# 727 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseVitaminSetSpe
	return

BattleCafe_RewardMenu_25:
# 728 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseMiraidon
	return

BattleCafe_RewardMenu_26:
# 729 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseKoraidon
	return

BattleCafe_RewardMenu_27:
# 730 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseTapuKoko
	return

BattleCafe_RewardMenu_28:
# 731 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseTapuLele
	return

BattleCafe_RewardMenu_29:
# 732 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseTapuBulu
	return

BattleCafe_RewardMenu_30:
# 733 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ChooseTapuFini
	return


BattleCafe_ChooseArticuno::
# 739 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_ARTICUNO_RECEIVED, BattleCafe_ChooseArticuno_2
BattleCafe_ChooseArticuno_1:
# 744 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ARTICUNO_GALAR
# 745 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 0
# 746 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseArticuno_2:
# 740 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseArticuno_Text_0
# 742 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseArticuno_1


BattleCafe_ChooseZapdos::
# 750 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_ZAPDOS_RECEIVED, BattleCafe_ChooseZapdos_2
BattleCafe_ChooseZapdos_1:
# 755 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZAPDOS_GALAR
# 756 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 1
# 757 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseZapdos_2:
# 751 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseZapdos_Text_0
# 753 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseZapdos_1


BattleCafe_ChooseMoltres::
# 761 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_MOLTRES_RECEIVED, BattleCafe_ChooseMoltres_2
BattleCafe_ChooseMoltres_1:
# 766 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MOLTRES_GALAR
# 767 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 2
# 768 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseMoltres_2:
# 762 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseMoltres_Text_0
# 764 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseMoltres_1


BattleCafe_ChooseTornadus::
# 772 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_TORNADUS_RECEIVED, BattleCafe_ChooseTornadus_2
BattleCafe_ChooseTornadus_1:
# 777 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TORNADUS
# 778 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 3
# 779 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTornadus_2:
# 773 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseTornadus_Text_0
# 775 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTornadus_1


BattleCafe_ChooseThundurus::
# 783 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_THUNDURUS_RECEIVED, BattleCafe_ChooseThundurus_2
BattleCafe_ChooseThundurus_1:
# 788 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_THUNDURUS
# 789 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 4
# 790 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseThundurus_2:
# 784 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseThundurus_Text_0
# 786 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseThundurus_1


BattleCafe_ChooseLandorus::
# 794 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_LANDORUS_RECEIVED, BattleCafe_ChooseLandorus_2
BattleCafe_ChooseLandorus_1:
# 799 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LANDORUS
# 800 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 5
# 801 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseLandorus_2:
# 795 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseLandorus_Text_0
# 797 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseLandorus_1


BattleCafe_ChooseEnamorus::
# 805 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_ENAMORUS_RECEIVED, BattleCafe_ChooseEnamorus_2
BattleCafe_ChooseEnamorus_1:
# 810 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ENAMORUS
# 811 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 6
# 812 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseEnamorus_2:
# 806 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseEnamorus_Text_0
# 808 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseEnamorus_1


BattleCafe_ChooseTapuKoko::
# 816 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_TAPU_KOKO_RECEIVED, BattleCafe_ChooseTapuKoko_2
BattleCafe_ChooseTapuKoko_1:
# 821 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_KOKO
# 822 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 7
# 823 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuKoko_2:
# 817 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseTapuKoko_Text_0
# 819 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuKoko_1


BattleCafe_ChooseTapuLele::
# 827 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_TAPU_LELE_RECEIVED, BattleCafe_ChooseTapuLele_2
BattleCafe_ChooseTapuLele_1:
# 832 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_LELE
# 833 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 8
# 834 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuLele_2:
# 828 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseTapuLele_Text_0
# 830 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuLele_1


BattleCafe_ChooseTapuBulu::
# 838 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_TAPU_BULU_RECEIVED, BattleCafe_ChooseTapuBulu_2
BattleCafe_ChooseTapuBulu_1:
# 843 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_BULU
# 844 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 9
# 845 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuBulu_2:
# 839 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseTapuBulu_Text_0
# 841 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuBulu_1


BattleCafe_ChooseTapuFini::
# 849 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_TAPU_FINI_RECEIVED, BattleCafe_ChooseTapuFini_2
BattleCafe_ChooseTapuFini_1:
# 854 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAPU_FINI
# 855 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 10
# 856 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmRewardMon
	return

BattleCafe_ChooseTapuFini_2:
# 850 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseTapuFini_Text_0
# 852 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseTapuFini_1


BattleCafe_ConfirmRewardMon::
# 860 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 5
	goto_if_lt BattleCafe_ConfirmRewardMon_2
BattleCafe_ConfirmRewardMon_1:
# 863 "data/maps/BattleCafe/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
# 864 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ConfirmRewardMon_Text_0, MSGBOX_YESNO
# 866 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ConfirmRewardMon_5
BattleCafe_ConfirmRewardMon_4:
# 870 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_B, 3
	goto_if_ge BattleCafe_ConfirmRewardMon_10
BattleCafe_ConfirmRewardMon_7:
# 877 "data/maps/BattleCafe/scripts.pory"
	givemon VAR_TEMP_TRANSFERRED_SPECIES, 70
# 878 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq BattleCafe_ConfirmRewardMon_15
BattleCafe_ConfirmRewardMon_14:
# 881 "data/maps/BattleCafe/scripts.pory"
	showgivemonpic 10, 3
# 882 "data/maps/BattleCafe/scripts.pory"
	call Common_EventScript_GiftMon
# 883 "data/maps/BattleCafe/scripts.pory"
	hidemonpic
# 884 "data/maps/BattleCafe/scripts.pory"
	subvar VAR_BATTLE_CAFE_POINTS, 5
# 885 "data/maps/BattleCafe/scripts.pory"
	switch VAR_TEMP_B
# 886 "data/maps/BattleCafe/scripts.pory"
	case 0, BattleCafe_ConfirmRewardMon_21
# 887 "data/maps/BattleCafe/scripts.pory"
	case 1, BattleCafe_ConfirmRewardMon_22
# 888 "data/maps/BattleCafe/scripts.pory"
	case 2, BattleCafe_ConfirmRewardMon_23
# 889 "data/maps/BattleCafe/scripts.pory"
	case 3, BattleCafe_ConfirmRewardMon_24
# 890 "data/maps/BattleCafe/scripts.pory"
	case 4, BattleCafe_ConfirmRewardMon_25
# 891 "data/maps/BattleCafe/scripts.pory"
	case 5, BattleCafe_ConfirmRewardMon_26
# 892 "data/maps/BattleCafe/scripts.pory"
	case 6, BattleCafe_ConfirmRewardMon_27
# 893 "data/maps/BattleCafe/scripts.pory"
	case 7, BattleCafe_ConfirmRewardMon_28
# 894 "data/maps/BattleCafe/scripts.pory"
	case 8, BattleCafe_ConfirmRewardMon_29
# 895 "data/maps/BattleCafe/scripts.pory"
	case 9, BattleCafe_ConfirmRewardMon_30
# 896 "data/maps/BattleCafe/scripts.pory"
	case 10, BattleCafe_ConfirmRewardMon_31
BattleCafe_ConfirmRewardMon_19:
# 898 "data/maps/BattleCafe/scripts.pory"
	special Achievement_CheckAll
# 899 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_B, 3
	goto_if_ge BattleCafe_ConfirmRewardMon_34
BattleCafe_ConfirmRewardMon_32:
# 905 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ConfirmRewardMon_Text_2
# 907 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ConfirmRewardMon_2:
# 861 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughPoints
	goto BattleCafe_ConfirmRewardMon_1

BattleCafe_ConfirmRewardMon_5:
# 867 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ConfirmRewardMon_4

BattleCafe_ConfirmRewardMon_8:
# 871 "data/maps/BattleCafe/scripts.pory"
	checkitemspace ITEM_REVEAL_GLASS, 1
# 872 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ConfirmRewardMon_17
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_9:
	checkitem ITEM_REVEAL_GLASS
# 0 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ConfirmRewardMon_8
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_10:
# 870 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_B, 6
	goto_if_le BattleCafe_ConfirmRewardMon_9
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_15:
# 879 "data/maps/BattleCafe/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
	goto BattleCafe_ConfirmRewardMon_14

BattleCafe_ConfirmRewardMon_17:
# 873 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ConfirmRewardMon_7

BattleCafe_ConfirmRewardMon_21:
# 886 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_ARTICUNO_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_22:
# 887 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_ZAPDOS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_23:
# 888 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_MOLTRES_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_24:
# 889 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_TORNADUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_25:
# 890 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_THUNDURUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_26:
# 891 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_LANDORUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_27:
# 892 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_ENAMORUS_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_28:
# 893 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_TAPU_KOKO_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_29:
# 894 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_TAPU_LELE_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_30:
# 895 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_TAPU_BULU_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_31:
# 896 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_TAPU_FINI_RECEIVED
	goto BattleCafe_ConfirmRewardMon_19

BattleCafe_ConfirmRewardMon_33:
	checkitem ITEM_REVEAL_GLASS
# 0 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ConfirmRewardMon_37
	goto BattleCafe_ConfirmRewardMon_32

BattleCafe_ConfirmRewardMon_34:
# 899 "data/maps/BattleCafe/scripts.pory"
	compare VAR_TEMP_B, 6
	goto_if_le BattleCafe_ConfirmRewardMon_33
	goto BattleCafe_ConfirmRewardMon_32

BattleCafe_ConfirmRewardMon_37:
# 901 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ConfirmRewardMon_Text_1
# 902 "data/maps/BattleCafe/scripts.pory"
	giveitem ITEM_REVEAL_GLASS
	goto BattleCafe_ConfirmRewardMon_32


BattleCafe_ChooseMiraidon::
# 911 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_MIRAIDON_RECEIVED, BattleCafe_ChooseMiraidon_2
BattleCafe_ChooseMiraidon_1:
# 916 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MIRAIDON
# 917 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 0
# 918 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmParadoxLegend
	return

BattleCafe_ChooseMiraidon_2:
# 912 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseMiraidon_Text_0
# 914 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseMiraidon_1


BattleCafe_ChooseKoraidon::
# 922 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_BATTLE_CAFE_KORAIDON_RECEIVED, BattleCafe_ChooseKoraidon_2
BattleCafe_ChooseKoraidon_1:
# 927 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KORAIDON
# 928 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_TEMP_B, 1
# 929 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_ConfirmParadoxLegend
	return

BattleCafe_ChooseKoraidon_2:
# 923 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseKoraidon_Text_0
# 925 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseKoraidon_1


BattleCafe_ConfirmParadoxLegend::
# 933 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 25
	goto_if_lt BattleCafe_ConfirmParadoxLegend_2
BattleCafe_ConfirmParadoxLegend_1:
# 936 "data/maps/BattleCafe/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
# 937 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ConfirmParadoxLegend_Text_0, MSGBOX_YESNO
# 939 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ConfirmParadoxLegend_5
BattleCafe_ConfirmParadoxLegend_4:
# 942 "data/maps/BattleCafe/scripts.pory"
	givemon VAR_TEMP_TRANSFERRED_SPECIES, 70
# 943 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq BattleCafe_ConfirmParadoxLegend_8
BattleCafe_ConfirmParadoxLegend_7:
# 946 "data/maps/BattleCafe/scripts.pory"
	showgivemonpic 10, 3
# 947 "data/maps/BattleCafe/scripts.pory"
	call Common_EventScript_GiftMon
# 948 "data/maps/BattleCafe/scripts.pory"
	hidemonpic
# 949 "data/maps/BattleCafe/scripts.pory"
	subvar VAR_BATTLE_CAFE_POINTS, 25
# 950 "data/maps/BattleCafe/scripts.pory"
	switch VAR_TEMP_B
# 951 "data/maps/BattleCafe/scripts.pory"
	case 0, BattleCafe_ConfirmParadoxLegend_12
# 952 "data/maps/BattleCafe/scripts.pory"
	case 1, BattleCafe_ConfirmParadoxLegend_13
BattleCafe_ConfirmParadoxLegend_10:
# 954 "data/maps/BattleCafe/scripts.pory"
	special Achievement_CheckAll
# 955 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ConfirmParadoxLegend_Text_1
# 957 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ConfirmParadoxLegend_2:
# 934 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughLegendPoints
	goto BattleCafe_ConfirmParadoxLegend_1

BattleCafe_ConfirmParadoxLegend_5:
# 940 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ConfirmParadoxLegend_4

BattleCafe_ConfirmParadoxLegend_8:
# 944 "data/maps/BattleCafe/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
	goto BattleCafe_ConfirmParadoxLegend_7

BattleCafe_ConfirmParadoxLegend_12:
# 951 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_MIRAIDON_RECEIVED
	goto BattleCafe_ConfirmParadoxLegend_10

BattleCafe_ConfirmParadoxLegend_13:
# 952 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_BATTLE_CAFE_KORAIDON_RECEIVED
	goto BattleCafe_ConfirmParadoxLegend_10


BattleCafe_ChooseShinyGenome::
# 961 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 4
	goto_if_lt BattleCafe_ChooseShinyGenome_2
BattleCafe_ChooseShinyGenome_1:
# 964 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseShinyGenome_Text_0, MSGBOX_YESNO
# 966 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseShinyGenome_5
BattleCafe_ChooseShinyGenome_4:
# 969 "data/maps/BattleCafe/scripts.pory"
	checkitemspace ITEM_SHIN_GENOME, 1
# 970 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ChooseShinyGenome_8
BattleCafe_ChooseShinyGenome_7:
# 973 "data/maps/BattleCafe/scripts.pory"
	giveitem ITEM_SHIN_GENOME
# 974 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_ne BattleCafe_ChooseShinyGenome_11
BattleCafe_ChooseShinyGenome_10:
# 977 "data/maps/BattleCafe/scripts.pory"
	subvar VAR_BATTLE_CAFE_POINTS, 4
# 978 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseShinyGenome_Text_1
# 981 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseShinyGenome_2:
# 962 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughFourPoints
	goto BattleCafe_ChooseShinyGenome_1

BattleCafe_ChooseShinyGenome_5:
# 967 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseShinyGenome_4

BattleCafe_ChooseShinyGenome_8:
# 971 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseShinyGenome_7

BattleCafe_ChooseShinyGenome_11:
# 975 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseShinyGenome_10


BattleCafe_ChooseGoldBottleCaps::
# 985 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 5
	goto_if_lt BattleCafe_ChooseGoldBottleCaps_2
BattleCafe_ChooseGoldBottleCaps_1:
# 988 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseGoldBottleCaps_Text_0, MSGBOX_YESNO
# 990 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseGoldBottleCaps_5
BattleCafe_ChooseGoldBottleCaps_4:
# 993 "data/maps/BattleCafe/scripts.pory"
	checkitemspace ITEM_GOLD_BOTTLE_CAP, 2
# 994 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq BattleCafe_ChooseGoldBottleCaps_8
BattleCafe_ChooseGoldBottleCaps_7:
# 997 "data/maps/BattleCafe/scripts.pory"
	giveitem ITEM_GOLD_BOTTLE_CAP, 2
# 998 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_ne BattleCafe_ChooseGoldBottleCaps_11
BattleCafe_ChooseGoldBottleCaps_10:
# 1001 "data/maps/BattleCafe/scripts.pory"
	subvar VAR_BATTLE_CAFE_POINTS, 5
# 1002 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseGoldBottleCaps_Text_1
# 1004 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseGoldBottleCaps_2:
# 986 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughPoints
	goto BattleCafe_ChooseGoldBottleCaps_1

BattleCafe_ChooseGoldBottleCaps_5:
# 991 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseGoldBottleCaps_4

BattleCafe_ChooseGoldBottleCaps_8:
# 995 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseGoldBottleCaps_7

BattleCafe_ChooseGoldBottleCaps_11:
# 999 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseGoldBottleCaps_10


BattleCafe_ChooseMoney::
# 1008 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 5
	goto_if_lt BattleCafe_ChooseMoney_2
BattleCafe_ChooseMoney_1:
# 1011 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseMoney_Text_0, MSGBOX_YESNO
# 1013 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseMoney_5
BattleCafe_ChooseMoney_4:
# 1016 "data/maps/BattleCafe/scripts.pory"
	subvar VAR_BATTLE_CAFE_POINTS, 5
# 1017 "data/maps/BattleCafe/scripts.pory"
	showmoneybox 0, 0
# 1018 "data/maps/BattleCafe/scripts.pory"
	addmoney 250000
# 1019 "data/maps/BattleCafe/scripts.pory"
	updatemoneybox 0
# 1020 "data/maps/BattleCafe/scripts.pory"
	playse SE_SHOP
# 1021 "data/maps/BattleCafe/scripts.pory"
	waitse
# 1022 "data/maps/BattleCafe/scripts.pory"
	hidemoneybox
# 1023 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseMoney_Text_1
# 1025 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseMoney_2:
# 1009 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughPoints
	goto BattleCafe_ChooseMoney_1

BattleCafe_ChooseMoney_5:
# 1014 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseMoney_4


BattleCafe_ChooseVitaminSetAtk::
# 1029 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 4
	goto_if_lt BattleCafe_ChooseVitaminSetAtk_2
BattleCafe_ChooseVitaminSetAtk_1:
# 1032 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseVitaminSetAtk_Text_0, MSGBOX_YESNO
# 1034 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseVitaminSetAtk_5
BattleCafe_ChooseVitaminSetAtk_4:
# 1037 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, BATTLE_CAFE_VITAMIN_SET_ATK
# 1038 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_TryPurchaseVitaminSet
# 1039 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_NOT_ENOUGH_POINTS
	goto_if_eq BattleCafe_ChooseVitaminSetAtk_8
BattleCafe_ChooseVitaminSetAtk_7:
# 1042 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS
	goto_if_ne BattleCafe_ChooseVitaminSetAtk_11
BattleCafe_ChooseVitaminSetAtk_10:
# 1045 "data/maps/BattleCafe/scripts.pory"
	playse SE_SHOP
# 1046 "data/maps/BattleCafe/scripts.pory"
	waitse
# 1047 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseVitaminSetAtk_Text_1
# 1049 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseVitaminSetAtk_2:
# 1030 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetAtk_1

BattleCafe_ChooseVitaminSetAtk_5:
# 1035 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseVitaminSetAtk_4

BattleCafe_ChooseVitaminSetAtk_8:
# 1040 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetAtk_7

BattleCafe_ChooseVitaminSetAtk_11:
# 1043 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseVitaminSetAtk_10


BattleCafe_ChooseVitaminSetDef::
# 1053 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 4
	goto_if_lt BattleCafe_ChooseVitaminSetDef_2
BattleCafe_ChooseVitaminSetDef_1:
# 1056 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseVitaminSetDef_Text_0, MSGBOX_YESNO
# 1058 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseVitaminSetDef_5
BattleCafe_ChooseVitaminSetDef_4:
# 1061 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, BATTLE_CAFE_VITAMIN_SET_DEF
# 1062 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_TryPurchaseVitaminSet
# 1063 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_NOT_ENOUGH_POINTS
	goto_if_eq BattleCafe_ChooseVitaminSetDef_8
BattleCafe_ChooseVitaminSetDef_7:
# 1066 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS
	goto_if_ne BattleCafe_ChooseVitaminSetDef_11
BattleCafe_ChooseVitaminSetDef_10:
# 1069 "data/maps/BattleCafe/scripts.pory"
	playse SE_SHOP
# 1070 "data/maps/BattleCafe/scripts.pory"
	waitse
# 1071 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseVitaminSetDef_Text_1
# 1073 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseVitaminSetDef_2:
# 1054 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetDef_1

BattleCafe_ChooseVitaminSetDef_5:
# 1059 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseVitaminSetDef_4

BattleCafe_ChooseVitaminSetDef_8:
# 1064 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetDef_7

BattleCafe_ChooseVitaminSetDef_11:
# 1067 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseVitaminSetDef_10


BattleCafe_ChooseVitaminSetSpe::
# 1077 "data/maps/BattleCafe/scripts.pory"
	compare VAR_BATTLE_CAFE_POINTS, 2
	goto_if_lt BattleCafe_ChooseVitaminSetSpe_2
BattleCafe_ChooseVitaminSetSpe_1:
# 1080 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseVitaminSetSpe_Text_0, MSGBOX_YESNO
# 1082 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_ne BattleCafe_ChooseVitaminSetSpe_5
BattleCafe_ChooseVitaminSetSpe_4:
# 1085 "data/maps/BattleCafe/scripts.pory"
	setvar VAR_0x8004, BATTLE_CAFE_VITAMIN_SET_SPE
# 1086 "data/maps/BattleCafe/scripts.pory"
	special BattleCafe_TryPurchaseVitaminSet
# 1087 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_NOT_ENOUGH_POINTS
	goto_if_eq BattleCafe_ChooseVitaminSetSpe_8
BattleCafe_ChooseVitaminSetSpe_7:
# 1090 "data/maps/BattleCafe/scripts.pory"
	compare VAR_RESULT, BATTLE_CAFE_VITAMIN_PURCHASE_SUCCESS
	goto_if_ne BattleCafe_ChooseVitaminSetSpe_11
BattleCafe_ChooseVitaminSetSpe_10:
# 1093 "data/maps/BattleCafe/scripts.pory"
	playse SE_SHOP
# 1094 "data/maps/BattleCafe/scripts.pory"
	waitse
# 1095 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_ChooseVitaminSetSpe_Text_1
# 1096 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return

BattleCafe_ChooseVitaminSetSpe_2:
# 1078 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetSpe_1

BattleCafe_ChooseVitaminSetSpe_5:
# 1083 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	goto BattleCafe_ChooseVitaminSetSpe_4

BattleCafe_ChooseVitaminSetSpe_8:
# 1088 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughVitaminSetPoints
	goto BattleCafe_ChooseVitaminSetSpe_7

BattleCafe_ChooseVitaminSetSpe_11:
# 1091 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_NotEnoughBagSpace
	goto BattleCafe_ChooseVitaminSetSpe_10


BattleCafe_NotEnoughPoints::
# 1100 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_NotEnoughPoints_Text_0
# 1103 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughLegendPoints::
# 1107 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_NotEnoughLegendPoints_Text_0
# 1110 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughFourPoints::
# 1114 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_NotEnoughFourPoints_Text_0
# 1117 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughVitaminSetPoints::
# 1121 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_NotEnoughVitaminSetPoints_Text_0
# 1126 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return


BattleCafe_NotEnoughBagSpace::
# 1130 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_NotEnoughBagSpace_Text_0
# 1133 "data/maps/BattleCafe/scripts.pory"
	goto BattleCafe_RewardMenu
	return


BattleCafe_Goodbye::
# 1137 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_Goodbye_Text_0
# 1138 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_GiveDailyCandyReward::
# 1143 "data/maps/BattleCafe/scripts.pory"
	random 3
# 1144 "data/maps/BattleCafe/scripts.pory"
	addvar VAR_RESULT, 1
# 1145 "data/maps/BattleCafe/scripts.pory"
	giveitem ITEM_EXP_CANDY_XL, VAR_RESULT
	return


BattleCafe_TrainerAthena::
# 1150 "data/maps/BattleCafe/scripts.pory"
	lock
# 1151 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1153 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_ATHENA, BattleCafe_TrainerAthena_2
# 1159 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerAthena_Text_1
# 1161 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_ATHENA, BattleCafe_TrainerAthena_Text_2
# 1162 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_ATHENA
# 1163 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerAthena_Text_3
# 1164 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1165 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerAthena_2:
# 1154 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerAthena_Text_0
# 1156 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_TrainerDoves::
# 1170 "data/maps/BattleCafe/scripts.pory"
	lock
# 1171 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1173 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_DOVES, BattleCafe_TrainerDoves_2
# 1180 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerDoves_Text_1
# 1182 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_DOVES, BattleCafe_TrainerDoves_Text_2
# 1183 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_DOVES
# 1184 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerDoves_Text_3
# 1187 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1188 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerDoves_2:
# 1174 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerDoves_Text_0
# 1177 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_TrainerElton::
# 1193 "data/maps/BattleCafe/scripts.pory"
	lock
# 1194 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1196 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_ELTON, BattleCafe_TrainerElton_2
# 1201 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerElton_Text_1
# 1203 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_ELTON, BattleCafe_TrainerElton_Text_2
# 1204 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_ELTON
# 1205 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerElton_Text_3
# 1207 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1208 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerElton_2:
# 1197 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerElton_Text_0
# 1198 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_TrainerNem::
# 1213 "data/maps/BattleCafe/scripts.pory"
	lock
# 1214 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1216 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_NEM, BattleCafe_TrainerNem_2
# 1221 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerNem_Text_1
# 1222 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_NEM, BattleCafe_TrainerNem_Text_2
# 1223 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_NEM
# 1224 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerNem_Text_3
# 1225 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1226 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerNem_2:
# 1217 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerNem_Text_0
# 1218 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_TrainerBai::
# 1231 "data/maps/BattleCafe/scripts.pory"
	lock
# 1232 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1234 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_BAI, BattleCafe_TrainerBai_2
# 1240 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerBai_Text_1
# 1242 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_BAI, BattleCafe_TrainerBai_Text_2
# 1243 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_BAI
# 1244 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerBai_Text_3
# 1246 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1247 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerBai_2:
# 1235 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerBai_Text_0
# 1237 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_TrainerDrac::
# 1252 "data/maps/BattleCafe/scripts.pory"
	lock
# 1253 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1255 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_DRAC, BattleCafe_TrainerDrac_2
# 1261 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerDrac_Text_1
# 1262 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_DRAC, BattleCafe_TrainerDrac_Text_2
# 1263 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_DRAC
# 1264 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerDrac_Text_0
# 1266 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1267 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerDrac_2:
# 1256 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerDrac_Text_0
# 1258 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_TrainerSimpli::
# 1272 "data/maps/BattleCafe/scripts.pory"
	lock
# 1273 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1275 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_SIMPLI, BattleCafe_TrainerSimpli_2
# 1280 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerSimpli_Text_1
# 1281 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_JUNA, BattleCafe_TrainerSimpli_Text_2
# 1282 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_SIMPLI
# 1283 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerSimpli_Text_3
# 1284 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1285 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerSimpli_2:
# 1276 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerSimpli_Text_0
# 1277 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_TrainerTylarie::
# 1290 "data/maps/BattleCafe/scripts.pory"
	lock
# 1291 "data/maps/BattleCafe/scripts.pory"
	faceplayer
# 1293 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_DAILY_BATTLE_CAFE_TYLARIE, BattleCafe_TrainerTylarie_2
# 1299 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerTylarie_Text_1
# 1301 "data/maps/BattleCafe/scripts.pory"
	trainerbattle_no_intro TRAINER_CAFE_TYLARIE, BattleCafe_TrainerTylarie_Text_2
# 1302 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_DAILY_BATTLE_CAFE_TYLARIE
# 1303 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerTylarie_Text_3
# 1305 "data/maps/BattleCafe/scripts.pory"
	call BattleCafe_GiveDailyCandyReward
# 1306 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_TrainerTylarie_2:
# 1294 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_TrainerTylarie_Text_0
# 1296 "data/maps/BattleCafe/scripts.pory"
	release
	end


BattleCafe_FreshWaterFountain::
# 1311 "data/maps/BattleCafe/scripts.pory"
	goto_if_set FLAG_GOT_FRESH_WATER, BattleCafe_FreshWaterFountain_1
# 1314 "data/maps/BattleCafe/scripts.pory"
	lock
# 1315 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_FreshWaterFountain_Text_1
# 1317 "data/maps/BattleCafe/scripts.pory"
	finditem ITEM_FRESH_WATER
# 1318 "data/maps/BattleCafe/scripts.pory"
	setflag FLAG_GOT_FRESH_WATER
# 1319 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_FreshWaterFountain_Text_2
# 1320 "data/maps/BattleCafe/scripts.pory"
	release
	end

BattleCafe_FreshWaterFountain_1:
# 1312 "data/maps/BattleCafe/scripts.pory"
	msgbox BattleCafe_FreshWaterFountain_Text_0, MSGBOX_SIGN
	return


BattleCafe_GiveDiancie_Text_0:
# 33 "data/maps/BattleCafe/scripts.pory"
	.string "Well, look at that. You've beaten\n"
	.string "every one of my regulars at least\l"
	.string "once.\p"
	.string "Seems only right you leave with a\n"
	.string "rare dining companion, Diancie!$"

BattleCafe_GiveDiancie_Text_1:
# 39 "data/maps/BattleCafe/scripts.pory"
	.string "It'll be waiting right here. Make\n"
	.string "whatever preparations you need, then\l"
	.string "come talk to me when you're ready to\l"
	.string "welcome it aboard.$"

BattleCafe_GiveDiancie_Text_2:
# 48 "data/maps/BattleCafe/scripts.pory"
	.string "Diancie is waiting for you.\p"
	.string "Are you ready to receive it?$"

BattleCafe_GiveDiancie_Text_3:
# 53 "data/maps/BattleCafe/scripts.pory"
	.string "No rush. Diancie will be right\n"
	.string "here whenever you're ready.$"

BattleCafe_GiveDiancie_Text_4:
# 69 "data/maps/BattleCafe/scripts.pory"
	.string "Diancie's a fine addition to the menu.\n"
	.string "Take good care of it!$"

BattleCafe_OwnerMenu_Text_0:
# 76 "data/maps/BattleCafe/scripts.pory"
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
# 97 "data/maps/BattleCafe/scripts.pory"
	.string "After seeing you clear Super Challenge,\n"
	.string "I can offer you a new format:\p"
	.string "Endless Challenge!$"

BattleCafe_OwnerMenu_Text_2:
# 105 "data/maps/BattleCafe/scripts.pory"
	.string "After seeing you conquer Super Rush,\n"
	.string "I can offer you one final format:\p"
	.string "Endless Rush!$"

BattleCafe_OwnerMenu_Text_3:
# 112 "data/maps/BattleCafe/scripts.pory"
	.string "Welcome! What'll it be today?$"

BattleCafe_OwnerMenu_Text_4:
# 116 "data/maps/BattleCafe/scripts.pory"
	.string "Daily Challenge$"

BattleCafe_OwnerMenu_Text_5:
# 117 "data/maps/BattleCafe/scripts.pory"
	.string "Rush Mode$"

BattleCafe_OwnerMenu_Text_6:
# 118 "data/maps/BattleCafe/scripts.pory"
	.string "Super Challenge$"

BattleCafe_OwnerMenu_Text_7:
# 119 "data/maps/BattleCafe/scripts.pory"
	.string "Super Rush$"

BattleCafe_OwnerMenu_Text_8:
# 120 "data/maps/BattleCafe/scripts.pory"
	.string "Endless Modes$"

BattleCafe_OwnerMenu_Text_9:
# 121 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange Points$"

BattleCafe_OwnerMenu_Text_10:
# 122 "data/maps/BattleCafe/scripts.pory"
	.string "Café Options$"

BattleCafe_OwnerMenu_Text_11:
# 123 "data/maps/BattleCafe/scripts.pory"
	.string "Leave$"

BattleCafe_OptionsMenu_Text_0:
# 156 "data/maps/BattleCafe/scripts.pory"
	.string "What would you like to check?$"

BattleCafe_OptionsMenu_Text_1:
# 158 "data/maps/BattleCafe/scripts.pory"
	.string "Battle BGM$"

BattleCafe_OptionsMenu_Text_2:
# 159 "data/maps/BattleCafe/scripts.pory"
	.string "High Scores$"

BattleCafe_OptionsMenu_Text_3:
# 160 "data/maps/BattleCafe/scripts.pory"
	.string "Innates$"

BattleCafe_OptionsMenu_Text_4:
# 161 "data/maps/BattleCafe/scripts.pory"
	.string "Café Rules$"

BattleCafe_OptionsMenu_Text_5:
# 162 "data/maps/BattleCafe/scripts.pory"
	.string "Back$"

BattleCafe_ExplainRules_Text_0:
# 191 "data/maps/BattleCafe/scripts.pory"
	.string "Three Café visitors will answer each\n"
	.string "challenge, one after another.\p"
	.string "In the Daily Challenge, they bring\n"
	.string "dependable teams of four.\p"
	.string "I'll tend to your Pokémon after each\n"
	.string "battle.\p"
	.string "Win all three for 3 Café Points.$"

BattleCafe_ExplainRules_Text_1:
# 201 "data/maps/BattleCafe/scripts.pory"
	.string "Rush Mode draws seasoned battlers with\n"
	.string "teams of four.\p"
	.string "Anything goes, and I can't heal\n"
	.string "your Pokémon between the matches.\p"
	.string "Win all three for 5 points.$"

BattleCafe_ExplainRules_Text_2:
# 208 "data/maps/BattleCafe/scripts.pory"
	.string "Super Challenge and Super Rush pit\n"
	.string "you against full teams of six Pokémon.\p"
	.string "Anyone might show up so prepare to\n"
	.string "face literally anything.\p"
	.string "Same rules apply here for healing\n"
	.string "between the rounds.$"

BattleCafe_ExplainRules_Text_3:
# 216 "data/maps/BattleCafe/scripts.pory"
	.string "There are no breaks once service\n"
	.string "begins.\p"
	.string "A loss ends the run, though\n"
	.string "you may retry until you win.\p"
	.string "Each challenge can be won once per day.$"

BattleCafe_ExplainRules_Text_4:
# 225 "data/maps/BattleCafe/scripts.pory"
	.string "Both Endless formats use full teams\n"
	.string "of six and continue until you lose\l"
	.string "or choose to retire.\p"
	.string "Endless Challenge heals your party\n"
	.string "after every win and awards 1 point.$"

BattleCafe_ExplainRules_Text_5:
# 231 "data/maps/BattleCafe/scripts.pory"
	.string "Endless Rush restores your party\n"
	.string "after every third victory and awards\l"
	.string "2 points per win.\p"
	.string "Your best streak in each format is\n"
	.string "saved under High Scores.$"

BattleCafe_AskDailyChallenge_Text_0:
# 243 "data/maps/BattleCafe/scripts.pory"
	.string "You've already cleared today's\n"
	.string "Daily Challenge.\p"
	.string "Come back tomorrow,\n"
	.string "or try another challenge!$"

BattleCafe_AskDailyChallenge_Text_1:
# 250 "data/maps/BattleCafe/scripts.pory"
	.string "Three Café visitors are ready with\n"
	.string "teams of four.\p"
	.string "I'll tend to your party\n"
	.string "after rounds one and two.\p"
	.string "Begin today's challenge?$"

BattleCafe_AskRushMode_Text_0:
# 266 "data/maps/BattleCafe/scripts.pory"
	.string "You've already conquered Rush Mode\n"
	.string "today.\p"
	.string "Come back tomorrow, or take\n"
	.string "another challenge!$"

BattleCafe_AskRushMode_Text_1:
# 273 "data/maps/BattleCafe/scripts.pory"
	.string "Three seasoned visitors are waiting\n"
	.string "with teams of four.\p"
	.string "I can't tend to your party between \n"
	.string "these battles.\p"
	.string "Begin today's rush?$"

BattleCafe_AskSuperChallenge_Text_0:
# 289 "data/maps/BattleCafe/scripts.pory"
	.string "You've already cleared today's\n"
	.string "Super Challenge.\p"
	.string "Come back tomorrow,\n"
	.string "or attempt another challenge!$"

BattleCafe_AskSuperChallenge_Text_1:
# 298 "data/maps/BattleCafe/scripts.pory"
	.string "Every Pokémon gets a seat in Super\n"
	.string "Challenge. Bring a full party of six\l"
	.string "before entering.$"

BattleCafe_AskSuperChallenge_Text_2:
# 303 "data/maps/BattleCafe/scripts.pory"
	.string "Three visitors will each meet your full\n"
	.string "party with six Pokémon of their own.\p"
	.string "I'll tend to your team between battles.\p"
	.string "Begin the Super Challenge?$"

BattleCafe_AskSuperRush_Text_0:
# 318 "data/maps/BattleCafe/scripts.pory"
	.string "You've already conquered Super Rush\n"
	.string "today.\p"
	.string "Come back tomorrow for\n"
	.string "another full-team trial!$"

BattleCafe_AskSuperRush_Text_1:
# 327 "data/maps/BattleCafe/scripts.pory"
	.string "Every Pokémon gets a seat in Super\n"
	.string "Rush.\p"
	.string "Bring a full party of six\n"
	.string "before entering.$"

BattleCafe_AskSuperRush_Text_2:
# 334 "data/maps/BattleCafe/scripts.pory"
	.string "Three visitors will each bring a full\n"
	.string "team of six.\p"
	.string "Once the rush begins, I can't heal\n"
	.string "your Pokémon between the battles.\p"
	.string "Begin the Super Rush?$"

BattleCafe_EndlessMenu_Text_0:
# 349 "data/maps/BattleCafe/scripts.pory"
	.string "Which Endless format will you try?$"

BattleCafe_EndlessMenu_Text_1:
# 351 "data/maps/BattleCafe/scripts.pory"
	.string "Endless Challenge$"

BattleCafe_EndlessMenu_Text_2:
# 352 "data/maps/BattleCafe/scripts.pory"
	.string "Endless Rush$"

BattleCafe_EndlessMenu_Text_3:
# 353 "data/maps/BattleCafe/scripts.pory"
	.string "Endless Rules$"

BattleCafe_ExplainEndlessRules_Text_0:
# 364 "data/maps/BattleCafe/scripts.pory"
	.string "Endless Challenge restores your party\n"
	.string "after every victory. \p"
	.string "Each win immediately awards 1 \n"
	.string "Café Point.\p"
	.string "Clear Super Challenge to unlock it.$"

BattleCafe_ExplainEndlessRules_Text_1:
# 371 "data/maps/BattleCafe/scripts.pory"
	.string "Endless Rush restores your party after\n"
	.string "every third victory. \p"
	.string "Each win immediately awards 2 \n"
	.string "Café Points.\p"
	.string "Clear Super Rush to unlock it.$"

BattleCafe_ExplainEndlessRules_Text_2:
# 378 "data/maps/BattleCafe/scripts.pory"
	.string "Both formats use full 6-vs-6 battles.\n"
	.string "You may retire after any victory,\l"
	.string "and your best streak is saved.$"

BattleCafe_AskEndlessChallenge_Text_0:
# 386 "data/maps/BattleCafe/scripts.pory"
	.string "Clear Super Challenge to unlock\n"
	.string "Endless Challenge.$"

BattleCafe_AskEndlessChallenge_Text_1:
# 392 "data/maps/BattleCafe/scripts.pory"
	.string "Every Endless opponent brings\n"
	.string "six Pokémon.\p"
	.string "Bring a full party of six before\n"
	.string "taking your seat.$"

BattleCafe_AskEndlessChallenge_Text_2:
# 399 "data/maps/BattleCafe/scripts.pory"
	.string "Full teams of six will keep coming\n"
	.string "until you lose or retire.\p"
	.string "I'll restore your party after every win,\n"
	.string "and each victory earns 1 Café Point.\p"
	.string "Begin Endless Challenge?$"

BattleCafe_AskEndlessRush_Text_0:
# 415 "data/maps/BattleCafe/scripts.pory"
	.string "Clear Super Rush to unlock\n"
	.string "Endless Rush.$"

BattleCafe_AskEndlessRush_Text_1:
# 428 "data/maps/BattleCafe/scripts.pory"
	.string "Full teams of six will keep coming\n"
	.string "until you lose or retire.\p"
	.string "I'll restore your party after every third\n"
	.string "victory. Each win earns 2 Café Points.\p"
	.string "Begin Endless Rush?$"

BattleCafe_BeginChallenge_Text_0:
# 453 "data/maps/BattleCafe/scripts.pory"
	.string "No final course. No final opponent.\n"
	.string "Endless service begins now!$"

BattleCafe_BeginChallenge_Text_1:
# 456 "data/maps/BattleCafe/scripts.pory"
	.string "Three courses. Three opponents.\n"
	.string "Service begins now!$"

BattleCafe_ChallengeNextRound_Text_0:
# 479 "data/maps/BattleCafe/scripts.pory"
	.string "Victory! Streak: {STR_VAR_1}.\n"
	.string "You received {STR_VAR_2} Café Points,\l"
	.string "and your party was restored.\p"
	.string "Continue the run?$"

BattleCafe_ChallengeNextRound_Text_1:
# 504 "data/maps/BattleCafe/scripts.pory"
	.string "Victory! Streak: {STR_VAR_1}.\n"
	.string "You received {STR_VAR_2} Café Points.\p"
	.string "Three battles cleared! Your party\n"
	.string "was restored. Continue the run?$"

BattleCafe_ChallengeNextRound_Text_2:
# 510 "data/maps/BattleCafe/scripts.pory"
	.string "Victory! Streak: {STR_VAR_1}.\n"
	.string "You received {STR_VAR_2} Café Points.\p"
	.string "Your party has not been restored.\n"
	.string "Continue the run?$"

BattleCafe_ChallengeNextRound_Text_3:
# 530 "data/maps/BattleCafe/scripts.pory"
	.string "Your party was restored.\n"
	.string "The next challenger is arriving!$"

BattleCafe_ChallengeNextRound_Text_4:
# 536 "data/maps/BattleCafe/scripts.pory"
	.string "Your party was restored.\n"
	.string "The next full team is arriving!$"

BattleCafe_ChallengeNextRound_Text_5:
# 540 "data/maps/BattleCafe/scripts.pory"
	.string "No healing in Super Rush!\n"
	.string "The next full team is arriving!$"

BattleCafe_ChallengeNextRound_Text_6:
# 543 "data/maps/BattleCafe/scripts.pory"
	.string "No healing in Rush Mode!\n"
	.string "The next challenger is arriving!$"

BattleCafe_EndlessRetired_Text_0:
# 560 "data/maps/BattleCafe/scripts.pory"
	.string "Run retired at {STR_VAR_1} wins.\p"
	.string "Your party is fully restored, your record\n"
	.string "is safe, and every point is yours to keep.$"

BattleCafe_ChallengeLost_Text_0:
# 603 "data/maps/BattleCafe/scripts.pory"
	.string "Your Endless run ends at {STR_VAR_1}\n"
	.string "wins. I've fully\l"
	.string "restored your party.\p"
	.string "Every Café Point you earned is yours\n"
	.string "to keep. Try to push even farther\l"
	.string "next time!$"

BattleCafe_ChallengeLost_Text_1:
# 611 "data/maps/BattleCafe/scripts.pory"
	.string "Tough course, huh? I've fully restored\n"
	.string "your party.\p"
	.string "Catch your breath, rework\n"
	.string "your strategy, and come at it again\l"
	.string "whenever you like!$"

BattleCafe_ChallengeWon_Text_0:
# 634 "data/maps/BattleCafe/scripts.pory"
	.string "Daily Challenge complete!\p"
	.string "That's {STR_VAR_1} Café Points for you.$"

BattleCafe_ChallengeWon_Text_1:
# 644 "data/maps/BattleCafe/scripts.pory"
	.string "Rush Mode complete! That took\n"
	.string "some real grit.\p"
	.string "Here's {STR_VAR_1} Café Points.$"

BattleCafe_ChallengeWon_Text_2:
# 655 "data/maps/BattleCafe/scripts.pory"
	.string "Super Challenge complete!\n"
	.string "Full team, full effort!\p"
	.string "That's {STR_VAR_1} Café Points.$"

BattleCafe_ChallengeWon_Text_3:
# 665 "data/maps/BattleCafe/scripts.pory"
	.string "Incredible! You have beaten\n"
	.string "the Super Rush mode!\p"
	.string "I can hardly believe it!\p"
	.string "Here's your reward of\n"
	.string "{STR_VAR_1} Café Points.$"

BattleCafe_RewardMenu_Text_0:
# 683 "data/maps/BattleCafe/scripts.pory"
	.string "You have {STR_VAR_1} Café Points.\n"
	.string "Anything you want to exchange for?$"

BattleCafe_RewardMenu_Text_1:
# 687 "data/maps/BattleCafe/scripts.pory"
	.string "Vitamin Set Atk - 4$"

BattleCafe_RewardMenu_Text_2:
# 688 "data/maps/BattleCafe/scripts.pory"
	.string "Vitamin Set Def - 4$"

BattleCafe_RewardMenu_Text_3:
# 689 "data/maps/BattleCafe/scripts.pory"
	.string "Vitamin Set Spe - 2$"

BattleCafe_RewardMenu_Text_4:
# 690 "data/maps/BattleCafe/scripts.pory"
	.string "Shiny Genome - 4$"

BattleCafe_RewardMenu_Text_5:
# 691 "data/maps/BattleCafe/scripts.pory"
	.string "2 Gold Caps - 5$"

BattleCafe_RewardMenu_Text_6:
# 692 "data/maps/BattleCafe/scripts.pory"
	.string "¥250,000 - 5$"

BattleCafe_RewardMenu_Text_7:
# 693 "data/maps/BattleCafe/scripts.pory"
	.string "G. Articuno - 5$"

BattleCafe_RewardMenu_Text_8:
# 694 "data/maps/BattleCafe/scripts.pory"
	.string "G. Zapdos - 5$"

BattleCafe_RewardMenu_Text_9:
# 695 "data/maps/BattleCafe/scripts.pory"
	.string "G. Moltres - 5$"

BattleCafe_RewardMenu_Text_10:
# 696 "data/maps/BattleCafe/scripts.pory"
	.string "Tornadus - 5$"

BattleCafe_RewardMenu_Text_11:
# 697 "data/maps/BattleCafe/scripts.pory"
	.string "Thundurus - 5$"

BattleCafe_RewardMenu_Text_12:
# 698 "data/maps/BattleCafe/scripts.pory"
	.string "Landorus - 5$"

BattleCafe_RewardMenu_Text_13:
# 699 "data/maps/BattleCafe/scripts.pory"
	.string "Enamorus - 5$"

BattleCafe_RewardMenu_Text_14:
# 700 "data/maps/BattleCafe/scripts.pory"
	.string "Tapu Koko - 5$"

BattleCafe_RewardMenu_Text_15:
# 701 "data/maps/BattleCafe/scripts.pory"
	.string "Tapu Lele - 5$"

BattleCafe_RewardMenu_Text_16:
# 702 "data/maps/BattleCafe/scripts.pory"
	.string "Tapu Bulu - 5$"

BattleCafe_RewardMenu_Text_17:
# 703 "data/maps/BattleCafe/scripts.pory"
	.string "Tapu Fini - 5$"

BattleCafe_RewardMenu_Text_18:
# 706 "data/maps/BattleCafe/scripts.pory"
	.string "Miraidon - 25$"

BattleCafe_RewardMenu_Text_19:
# 710 "data/maps/BattleCafe/scripts.pory"
	.string "Koraidon - 25$"

BattleCafe_ChooseArticuno_Text_0:
# 740 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Galarian\n"
	.string "Articuno to you.$"

BattleCafe_ChooseZapdos_Text_0:
# 751 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Galarian\n"
	.string "Zapdos to you.$"

BattleCafe_ChooseMoltres_Text_0:
# 762 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Galarian\n"
	.string "Moltres to you.$"

BattleCafe_ChooseTornadus_Text_0:
# 773 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Tornadus\n"
	.string "to you.$"

BattleCafe_ChooseThundurus_Text_0:
# 784 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Thundurus\n"
	.string "to you.$"

BattleCafe_ChooseLandorus_Text_0:
# 795 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Landorus\n"
	.string "to you.$"

BattleCafe_ChooseEnamorus_Text_0:
# 806 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Enamorus\n"
	.string "to you.$"

BattleCafe_ChooseTapuKoko_Text_0:
# 817 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Tapu Koko\n"
	.string "to you.$"

BattleCafe_ChooseTapuLele_Text_0:
# 828 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Tapu Lele\n"
	.string "to you.$"

BattleCafe_ChooseTapuBulu_Text_0:
# 839 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Tapu Bulu\n"
	.string "to you.$"

BattleCafe_ChooseTapuFini_Text_0:
# 850 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Tapu Fini\n"
	.string "to you.$"

BattleCafe_ConfirmRewardMon_Text_0:
# 864 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 5 Café Points for\n"
	.string "{STR_VAR_1}?$"

BattleCafe_ConfirmRewardMon_Text_1:
# 901 "data/maps/BattleCafe/scripts.pory"
	.string "You might find this useful.$"

BattleCafe_ConfirmRewardMon_Text_2:
# 905 "data/maps/BattleCafe/scripts.pory"
	.string "A fair trade. I'm sure it'll fit right\n"
	.string "into your team.$"

BattleCafe_ChooseMiraidon_Text_0:
# 912 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Miraidon\n"
	.string "to you.$"

BattleCafe_ChooseKoraidon_Text_0:
# 923 "data/maps/BattleCafe/scripts.pory"
	.string "I've already entrusted Koraidon\n"
	.string "to you.$"

BattleCafe_ConfirmParadoxLegend_Text_0:
# 937 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 25 Café Points for\n"
	.string "{STR_VAR_1}?$"

BattleCafe_ConfirmParadoxLegend_Text_1:
# 955 "data/maps/BattleCafe/scripts.pory"
	.string "A rare specimen from Paldea. Take good\n"
	.string "care of it!$"

BattleCafe_ChooseShinyGenome_Text_0:
# 964 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 4 Café Points for a\n"
	.string "Shiny Genome?$"

BattleCafe_ChooseShinyGenome_Text_1:
# 978 "data/maps/BattleCafe/scripts.pory"
	.string "A rare find. Use it on whichever\n"
	.string "Pokémon you want to bring out the\l"
	.string "shine.$"

BattleCafe_ChooseGoldBottleCaps_Text_0:
# 988 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 5 Café Points for two\n"
	.string "Gold Bottle Caps?$"

BattleCafe_ChooseGoldBottleCaps_Text_1:
# 1002 "data/maps/BattleCafe/scripts.pory"
	.string "Two Gold Bottle Caps, polished up and\n"
	.string "ready. Here you go!$"

BattleCafe_ChooseMoney_Text_0:
# 1011 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 5 Café Points for\n"
	.string "¥250,000?$"

BattleCafe_ChooseMoney_Text_1:
# 1023 "data/maps/BattleCafe/scripts.pory"
	.string "Use it well, and perhaps spend a little\n"
	.string "on dessert!$"

BattleCafe_ChooseVitaminSetAtk_Text_0:
# 1032 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 4 Café Points for two each of\n"
	.string "Protein EX and Calcium EX?$"

BattleCafe_ChooseVitaminSetAtk_Text_1:
# 1047 "data/maps/BattleCafe/scripts.pory"
	.string "Two Protein EX and two Calcium EX,\n"
	.string "power and wisdom!$"

BattleCafe_ChooseVitaminSetDef_Text_0:
# 1056 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 4 Café Points for two each of\n"
	.string "Iron EX and Zinc EX?$"

BattleCafe_ChooseVitaminSetDef_Text_1:
# 1071 "data/maps/BattleCafe/scripts.pory"
	.string "Two Iron EX and two Zinc EX,\n"
	.string "time to bulk up!$"

BattleCafe_ChooseVitaminSetSpe_Text_0:
# 1080 "data/maps/BattleCafe/scripts.pory"
	.string "Exchange 2 Café Points for\n"
	.string "two Carbos EX?$"

BattleCafe_ChooseVitaminSetSpe_Text_1:
# 1095 "data/maps/BattleCafe/scripts.pory"
	.string "Two Carbos EX, ready to speed up!$"

BattleCafe_NotEnoughPoints_Text_0:
# 1100 "data/maps/BattleCafe/scripts.pory"
	.string "That prize costs 5 Café Points.\n"
	.string "Complete one of my challenges and try\l"
	.string "again!$"

BattleCafe_NotEnoughLegendPoints_Text_0:
# 1107 "data/maps/BattleCafe/scripts.pory"
	.string "That prize costs 25 Café Points.\n"
	.string "Complete more of my challenges and\l"
	.string "try again!$"

BattleCafe_NotEnoughFourPoints_Text_0:
# 1114 "data/maps/BattleCafe/scripts.pory"
	.string "The Shiny Genome costs 4 Café Points.\n"
	.string "Complete one of my challenges and try\l"
	.string "again!$"

BattleCafe_NotEnoughVitaminSetPoints_Text_0:
# 1121 "data/maps/BattleCafe/scripts.pory"
	.string "You don't have enough Café Points for\n"
	.string "that vitamin set. \p"
	.string "Complete one of my\n"
	.string "challenges and try again!$"

BattleCafe_NotEnoughBagSpace_Text_0:
# 1130 "data/maps/BattleCafe/scripts.pory"
	.string "Your Bag is too full for that prize.\n"
	.string "Make some room and come back whenever\l"
	.string "you're ready!$"

BattleCafe_Goodbye_Text_0:
# 1137 "data/maps/BattleCafe/scripts.pory"
	.string "Come back hungry for another battle!$"

BattleCafe_TrainerAthena_Text_0:
# 1154 "data/maps/BattleCafe/scripts.pory"
	.string "Did you have fun? Let's try this\n"
	.string "again tomorrow!$"

BattleCafe_TrainerAthena_Text_1:
# 1159 "data/maps/BattleCafe/scripts.pory"
	.string "Let's see if you can survive this\n"
	.string "stall!$"

BattleCafe_TrainerAthena_Text_2:
# 1161 "data/maps/BattleCafe/scripts.pory"
	.string "Huh?$"

BattleCafe_TrainerAthena_Text_3:
# 1163 "data/maps/BattleCafe/scripts.pory"
	.string "Did you have fun?$"

BattleCafe_TrainerDoves_Text_0:
# 1174 "data/maps/BattleCafe/scripts.pory"
	.string "Doves: Let's fight again tomorrow when \n"
	.string "my Genesect is allowed on the \l"
	.string "battlefield.$"

BattleCafe_TrainerDoves_Text_1:
# 1180 "data/maps/BattleCafe/scripts.pory"
	.string "Doves: Let me show you the power of \n"
	.string "Genesect!$"

BattleCafe_TrainerDoves_Text_2:
# 1182 "data/maps/BattleCafe/scripts.pory"
	.string "Banned again from Overused...$"

BattleCafe_TrainerDoves_Text_3:
# 1184 "data/maps/BattleCafe/scripts.pory"
	.string "Doves: Let's fight again tomorrow when\n"
	.string "my Genesect is allowed on the \l"
	.string "battlefield.$"

BattleCafe_TrainerElton_Text_0:
# 1197 "data/maps/BattleCafe/scripts.pory"
	.string "Elton: Rematch tomorrow! Be there!$"

BattleCafe_TrainerElton_Text_1:
# 1201 "data/maps/BattleCafe/scripts.pory"
	.string "Elton: Let's have a battle with our\n"
	.string "favourite Pokémon!$"

BattleCafe_TrainerElton_Text_2:
# 1203 "data/maps/BattleCafe/scripts.pory"
	.string "You handled every trick I had!$"

BattleCafe_TrainerElton_Text_3:
# 1205 "data/maps/BattleCafe/scripts.pory"
	.string "Elton: Even Gengar's impressed, and it\n"
	.string "rarely takes a loss seriously.$"

BattleCafe_TrainerNem_Text_0:
# 1217 "data/maps/BattleCafe/scripts.pory"
	.string "Nem: Come back tomorrow.$"

BattleCafe_TrainerNem_Text_1:
# 1221 "data/maps/BattleCafe/scripts.pory"
	.string "Nem: Think fast!$"

BattleCafe_TrainerNem_Text_2:
# 1222 "data/maps/BattleCafe/scripts.pory"
	.string "I'll be watching.$"

BattleCafe_TrainerNem_Text_3:
# 1224 "data/maps/BattleCafe/scripts.pory"
	.string "Nem: We can fight again tomorrow.$"

BattleCafe_TrainerBai_Text_0:
# 1235 "data/maps/BattleCafe/scripts.pory"
	.string "Bai: That was a good match!\n"
	.string "Let's fight again tomorrow!$"

BattleCafe_TrainerBai_Text_1:
# 1240 "data/maps/BattleCafe/scripts.pory"
	.string "Bai: Let's see what you bring to \n"
	.string "the table!$"

BattleCafe_TrainerBai_Text_2:
# 1242 "data/maps/BattleCafe/scripts.pory"
	.string "Guess I'm cooked this time...$"

BattleCafe_TrainerBai_Text_3:
# 1244 "data/maps/BattleCafe/scripts.pory"
	.string "Bai: Good match! Let's try this again \n"
	.string "tomorrow!$"

BattleCafe_TrainerDrac_Text_0:
# 1256 "data/maps/BattleCafe/scripts.pory"
	.string "Drac: You're really tough! Let's fight\n"
	.string "again tomorrow!$"

BattleCafe_TrainerDrac_Text_1:
# 1261 "data/maps/BattleCafe/scripts.pory"
	.string "Drac: Care for a double battle?$"

BattleCafe_TrainerDrac_Text_2:
# 1262 "data/maps/BattleCafe/scripts.pory"
	.string "Soothed.$"

BattleCafe_TrainerSimpli_Text_0:
# 1276 "data/maps/BattleCafe/scripts.pory"
	.string "Tomorrow will surely be better.$"

BattleCafe_TrainerSimpli_Text_1:
# 1280 "data/maps/BattleCafe/scripts.pory"
	.string "Gamble with the rain!$"

BattleCafe_TrainerSimpli_Text_2:
# 1281 "data/maps/BattleCafe/scripts.pory"
	.string "Weathered...$"

BattleCafe_TrainerSimpli_Text_3:
# 1283 "data/maps/BattleCafe/scripts.pory"
	.string "Maybe tomorrow will go better.$"

BattleCafe_TrainerTylarie_Text_0:
# 1294 "data/maps/BattleCafe/scripts.pory"
	.string "Steelix has settled down for\n"
	.string "lunch. We'll be ready tomorrow!$"

BattleCafe_TrainerTylarie_Text_1:
# 1299 "data/maps/BattleCafe/scripts.pory"
	.string "Tylarie: Let me show you how sturdy my\n"
	.string "team is!$"

BattleCafe_TrainerTylarie_Text_2:
# 1301 "data/maps/BattleCafe/scripts.pory"
	.string "Ouch.$"

BattleCafe_TrainerTylarie_Text_3:
# 1303 "data/maps/BattleCafe/scripts.pory"
	.string "Tylarie: Not bad. We can go at it again\n"
	.string "another day.$"

BattleCafe_FreshWaterFountain_Text_0:
# 1312 "data/maps/BattleCafe/scripts.pory"
	.string "It's a small fountain of water.$"

BattleCafe_FreshWaterFountain_Text_1:
# 1315 "data/maps/BattleCafe/scripts.pory"
	.string "You decide to grab some fresh water\n"
	.string "from the fountain.$"

BattleCafe_FreshWaterFountain_Text_2:
# 1319 "data/maps/BattleCafe/scripts.pory"
	.string "Stay hydrated.$"
