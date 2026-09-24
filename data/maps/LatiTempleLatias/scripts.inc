LatiTempleLatias_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LatiTempleLatias_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

LatiTempleLatias_MapScripts_MAP_SCRIPT_ON_LOAD:
	call LatiTemple_RefreshPuzzle
	return


LatiTemple_Latias::
	lock
	faceplayer
	bosslegendaryencounterwithmoves SPECIES_LATIAS, 80, LOCALID_LATIAS, FLAG_HIDE_LATIAS, 3, SPECIES_NONE, 110, MOVE_MIST_BALL, MOVE_ICE_BEAM, MOVE_SHADOW_BALL, MOVE_THUNDERBOLT
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq LatiTemple_Latias_2
LatiTemple_Latias_1:
	release
	end

LatiTemple_Latias_2:
	setflag FLAG_CAUGHT_LATIAS
	goto LatiTemple_Latias_1


ResetLatiasPuzzle::
	lock
	msgbox ResetLatiasPuzzle_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq ResetLatiasPuzzle_2
ResetLatiasPuzzle_1:
	releaseall
	end

ResetLatiasPuzzle_2:
	clearflag FLAG_LATITEMPLE_SWITCH1
	clearflag FLAG_LATITEMPLE_SWITCH2
	clearflag FLAG_LATITEMPLE_SWITCH3
	clearflag FLAG_LATITEMPLE_SWITCH4
	clearflag FLAG_LATITEMPLE_SWITCH5
	playse SE_PIN
	call LatiTemple_RefreshPuzzle
	special DrawWholeMapView
	waitse
	goto ResetLatiasPuzzle_1


LatiTemple_Switch1::
	lockall
	goto_if_set FLAG_LATITEMPLE_SWITCH1, LatiTemple_Switch1_2
	setflag FLAG_LATITEMPLE_SWITCH1
LatiTemple_Switch1_1:
	playse SE_PIN
	call LatiTemple_RefreshPuzzle
	special DrawWholeMapView
	waitse
	releaseall
	return

LatiTemple_Switch1_2:
	clearflag FLAG_LATITEMPLE_SWITCH1
	goto LatiTemple_Switch1_1


LatiTemple_Switch2::
	lockall
	goto_if_set FLAG_LATITEMPLE_SWITCH2, LatiTemple_Switch2_2
	setflag FLAG_LATITEMPLE_SWITCH2
LatiTemple_Switch2_1:
	playse SE_PIN
	call LatiTemple_RefreshPuzzle
	special DrawWholeMapView
	waitse
	releaseall
	return

LatiTemple_Switch2_2:
	clearflag FLAG_LATITEMPLE_SWITCH2
	goto LatiTemple_Switch2_1


LatiTemple_Switch3::
	lockall
	goto_if_set FLAG_LATITEMPLE_SWITCH3, LatiTemple_Switch3_2
	setflag FLAG_LATITEMPLE_SWITCH3
LatiTemple_Switch3_1:
	playse SE_PIN
	call LatiTemple_RefreshPuzzle
	special DrawWholeMapView
	waitse
	releaseall
	return

LatiTemple_Switch3_2:
	clearflag FLAG_LATITEMPLE_SWITCH3
	goto LatiTemple_Switch3_1


LatiTemple_Switch4::
	lockall
	goto_if_set FLAG_LATITEMPLE_SWITCH4, LatiTemple_Switch4_2
	setflag FLAG_LATITEMPLE_SWITCH4
LatiTemple_Switch4_1:
	playse SE_PIN
	call LatiTemple_RefreshPuzzle
	special DrawWholeMapView
	waitse
	releaseall
	return

LatiTemple_Switch4_2:
	clearflag FLAG_LATITEMPLE_SWITCH4
	goto LatiTemple_Switch4_1


LatiTemple_Switch5::
	lockall
	goto_if_set FLAG_LATITEMPLE_SWITCH5, LatiTemple_Switch5_2
	setflag FLAG_LATITEMPLE_SWITCH5
LatiTemple_Switch5_1:
	playse SE_PIN
	call LatiTemple_RefreshPuzzle
	special DrawWholeMapView
	waitse
	releaseall
	return

LatiTemple_Switch5_2:
	clearflag FLAG_LATITEMPLE_SWITCH5
	goto LatiTemple_Switch5_1


LatiTemple_RefreshPuzzle::
	call LatiTemple_SetSwitch1State
	call LatiTemple_SetSwitch2State
	call LatiTemple_SetSwitch3State
	call LatiTemple_SetSwitch4State
	call LatiTemple_SetSwitch5State
	return


LatiTemple_SetSwitch1State::
	goto_if_set FLAG_LATITEMPLE_SWITCH1, LatiTemple_SetSwitch1State_2
	setmetatile 17, 27, METATILE_LatiTemple_ActiveGray, FALSE
	setmetatile 33, 33, METATILE_LatiTemple_ActiveGray, FALSE
	setmetatile 36, 21, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 18, 23, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 18, 17, METATILE_LatiTemple_InactiveGray, TRUE
	setmetatile 34, 1, METATILE_LatiTemple_InactiveGray, TRUE
	setmetatile 21, 4, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 51, 31, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 32, 21, METATILE_LatiTemple_CrystalSwitchInactive, TRUE
LatiTemple_SetSwitch1State_1:
	return

LatiTemple_SetSwitch1State_2:
	setmetatile 17, 27, METATILE_LatiTemple_InactiveGray, TRUE
	setmetatile 33, 33, METATILE_LatiTemple_InactiveGray, TRUE
	setmetatile 36, 21, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 18, 23, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 18, 17, METATILE_LatiTemple_ActiveGray, FALSE
	setmetatile 34, 1, METATILE_LatiTemple_ActiveGray, FALSE
	setmetatile 21, 4, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 51, 31, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 32, 21, METATILE_LatiTemple_CrystalSwitchActive, TRUE
	goto LatiTemple_SetSwitch1State_1


LatiTemple_SetSwitch2State::
	goto_if_set FLAG_LATITEMPLE_SWITCH2, LatiTemple_SetSwitch2State_2
	setmetatile 45, 25, METATILE_LatiTemple_InactiveGray, TRUE
	setmetatile 54, 20, METATILE_LatiTemple_InactiveGray, TRUE
	setmetatile 32, 3, METATILE_LatiTemple_CrystalSwitchInactive, TRUE
LatiTemple_SetSwitch2State_1:
	return

LatiTemple_SetSwitch2State_2:
	setmetatile 45, 25, METATILE_LatiTemple_ActiveGray, FALSE
	setmetatile 54, 20, METATILE_LatiTemple_ActiveGray, FALSE
	setmetatile 32, 3, METATILE_LatiTemple_CrystalSwitchActive, TRUE
	goto LatiTemple_SetSwitch2State_1


LatiTemple_SetSwitch3State::
	goto_if_set FLAG_LATITEMPLE_SWITCH3, LatiTemple_SetSwitch3State_2
	setmetatile 37, 30, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 28, 21, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 45, 11, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 43, 18, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 51, 23, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 14, 10, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 46, 21, METATILE_LatiTemple_CrystalSwitchInactive, TRUE
LatiTemple_SetSwitch3State_1:
	return

LatiTemple_SetSwitch3State_2:
	setmetatile 37, 30, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 28, 21, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 45, 11, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 43, 18, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 51, 23, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 14, 10, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 46, 21, METATILE_LatiTemple_CrystalSwitchActive, TRUE
	goto LatiTemple_SetSwitch3State_1


LatiTemple_SetSwitch4State::
	goto_if_set FLAG_LATITEMPLE_SWITCH4, LatiTemple_SetSwitch4State_2
	setmetatile 21, 30, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 41, 31, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 15, 6, METATILE_LatiTemple_CrystalSwitchInactive, TRUE
LatiTemple_SetSwitch4State_1:
	return

LatiTemple_SetSwitch4State_2:
	setmetatile 21, 30, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 41, 31, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 15, 6, METATILE_LatiTemple_CrystalSwitchActive, TRUE
	goto LatiTemple_SetSwitch4State_1


LatiTemple_SetSwitch5State::
	goto_if_set FLAG_LATITEMPLE_SWITCH5, LatiTemple_SetSwitch5State_2
	setmetatile 30, 5, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 51, 11, METATILE_LatiTemple_ActiveBlue, FALSE
	setmetatile 12, 30, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 5, 23, METATILE_LatiTemple_InactiveGreen, TRUE
	setmetatile 51, 28, METATILE_LatiTemple_CrystalSwitchInactive, TRUE
LatiTemple_SetSwitch5State_1:
	return

LatiTemple_SetSwitch5State_2:
	setmetatile 30, 5, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 51, 11, METATILE_LatiTemple_InactiveBlue, TRUE
	setmetatile 12, 30, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 5, 23, METATILE_LatiTemple_ActiveGreen, FALSE
	setmetatile 51, 28, METATILE_LatiTemple_CrystalSwitchActive, TRUE
	goto LatiTemple_SetSwitch5State_1


ResetLatiasPuzzle_Text_0:
	.string "Would you like to reset the puzzle?$"
