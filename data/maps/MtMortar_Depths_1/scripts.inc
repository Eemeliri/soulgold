MtMortar_Depths_1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_MTMORTAR_DEPTHS_PUZZLE1SOLVED, MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD_2
MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	goto_if_set FLAG_MTMORTAR_DEPTHS_HEATRANPUZZLED, MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD_4
	return

MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD_2:
	setmetatile 20, 18, 0x404, FALSE
	setmetatile 20, 19, 0x404, FALSE
	setmetatile 20, 20, 0x404, FALSE
	goto MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD_1

MtMortar_Depths_1_MapScripts_MAP_SCRIPT_ON_LOAD_4:
	setmetatile 40, 1, 0x414, FALSE
	setmetatile 40, 0, 0x40C, FALSE
	setmetatile 40, 4, 0x4F3, FALSE
	setmetatile 38, 6, 0x4F3, FALSE
	setmetatile 39, 6, 0x4F3, FALSE
	setmetatile 40, 6, 0x4F3, FALSE
	setmetatile 41, 6, 0x4F3, FALSE
	setmetatile 42, 6, 0x4F3, FALSE
	setvar VAR_TEMP_E, 1
	return


firetitePuzzleButton1::
	lock
	addvar VAR_TEMP_A, 1
	playse SE_PIN
	setmetatile 27, 14, 0x4E5, FALSE
	special DrawWholeMapView
	call firetitePuzzleCall
	addvar VAR_TEMP_0, 1
	release
	end


firetitePuzzleButton2::
	lock
	addvar VAR_TEMP_A, 1
	playse SE_PIN
	setmetatile 12, 11, 0x4E5, FALSE
	special DrawWholeMapView
	call firetitePuzzleCall
	addvar VAR_TEMP_1, 1
	release
	end


firetitePuzzleButton3::
	lock
	addvar VAR_TEMP_A, 1
	playse SE_PIN
	setmetatile 23, 34, 0x4E6, FALSE
	special DrawWholeMapView
	call firetitePuzzleCall
	addvar VAR_TEMP_2, 1
	release
	end


firetitePuzzleCall::
	compare VAR_TEMP_A, 3
	goto_if_ge firetitePuzzleCall_2
firetitePuzzleCall_1:
	return

firetitePuzzleCall_2:
	playse SE_CLICK
	delay 30
	setmetatile 20, 18, 0x404, FALSE
	setmetatile 20, 19, 0x404, FALSE
	setmetatile 20, 20, 0x404, FALSE
	setflag FLAG_MTMORTAR_DEPTHS_PUZZLE1SOLVED
	special DrawWholeMapView
	goto firetitePuzzleCall_1


heatranPuzzleButtonCorrect1::
	goto_if_set FLAG_TEMP_3, heatranPuzzleButtonCorrect1_2
	lock
	setflag FLAG_TEMP_3
	playse SE_PIN
	setmetatile 40, 4, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleButtonCorrect1_2:
	release
	end


heatranPuzzleButtonCorrect2::
	goto_if_set FLAG_TEMP_6, heatranPuzzleButtonCorrect2_2
	lock
	setflag FLAG_TEMP_6
	playse SE_PIN
	setmetatile 38, 6, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleButtonCorrect2_2:
	release
	end


heatranPuzzleButtonCorrect3::
	goto_if_set FLAG_TEMP_7, heatranPuzzleButtonCorrect3_2
	lock
	setflag FLAG_TEMP_7
	playse SE_PIN
	setmetatile 39, 6, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleButtonCorrect3_2:
	release
	end


heatranPuzzleButtonCorrect4::
	goto_if_set FLAG_TEMP_8, heatranPuzzleButtonCorrect4_2
	lock
	setflag FLAG_TEMP_8
	playse SE_PIN
	setmetatile 40, 6, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleButtonCorrect4_2:
	release
	end


heatranPuzzleButtonCorrect5::
	goto_if_set FLAG_TEMP_9, heatranPuzzleButtonCorrect5_2
	lock
	setflag FLAG_TEMP_9
	playse SE_PIN
	setmetatile 41, 6, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleButtonCorrect5_2:
	release
	end


heatranPuzzleButtonCorrect6::
	goto_if_set FLAG_TEMP_A, heatranPuzzleButtonCorrect6_2
	lock
	setflag FLAG_TEMP_A
	playse SE_PIN
	setmetatile 42, 6, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleButtonCorrect6_2:
	release
	end


heatranPuzzleWrongButton1::
	goto_if_set FLAG_TEMP_1, heatranPuzzleWrongButton1_2
	lock
	setflag FLAG_TEMP_1
	setflag FLAG_WRONG_BUTTON_HEATRAN
	playse SE_PIN
	setmetatile 38, 4, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleWrongButton1_2:
	release
	end


heatranPuzzleWrongButton2::
	goto_if_set FLAG_TEMP_2, heatranPuzzleWrongButton2_2
	lock
	setflag FLAG_TEMP_2
	setflag FLAG_WRONG_BUTTON_HEATRAN
	playse SE_PIN
	setmetatile 39, 4, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleWrongButton2_2:
	release
	end


heatranPuzzleWrongButton3::
	goto_if_set FLAG_TEMP_4, heatranPuzzleWrongButton3_2
	lock
	setflag FLAG_TEMP_4
	setflag FLAG_WRONG_BUTTON_HEATRAN
	playse SE_PIN
	setmetatile 41, 4, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleWrongButton3_2:
	release
	end


heatranPuzzleWrongButton4::
	goto_if_set FLAG_TEMP_5, heatranPuzzleWrongButton4_2
	lock
	setflag FLAG_TEMP_5
	setflag FLAG_WRONG_BUTTON_HEATRAN
	playse SE_PIN
	setmetatile 42, 4, 0x4F3, FALSE
	special DrawWholeMapView
	addvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 1
	call heatranPuzzleCall
	release
	end

heatranPuzzleWrongButton4_2:
	release
	end


heatranPuzzleCall::
	goto_if_set FLAG_WRONG_BUTTON_HEATRAN, heatranPuzzleCall_3
heatranPuzzleCall_1:
	compare VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 6
	goto_if_eq heatranPuzzleCall_7
heatranPuzzleCall_6:
	return

heatranPuzzleCall_2:
	goto heatranPuzzleReset
	goto heatranPuzzleCall_1

heatranPuzzleCall_3:
	compare VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 6
	goto_if_eq heatranPuzzleCall_2
	goto heatranPuzzleCall_1

heatranPuzzleCall_7:
	setflag FLAG_MTMORTAR_DEPTHS_HEATRANPUZZLED
	playse SE_BANG
	setmetatile 40, 1, 0x414, FALSE
	setmetatile 40, 0, 0x40C, FALSE
	setvar VAR_TEMP_E, 1
	special DrawWholeMapView
	goto heatranPuzzleCall_6


heatranPuzzleReset::
	setvar VAR_MTMORTAR_DEPTHS_HEATRAN_BUTTONS, 0
	clearflag FLAG_WRONG_BUTTON_HEATRAN
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_4
	clearflag FLAG_TEMP_5
	clearflag FLAG_TEMP_6
	clearflag FLAG_TEMP_7
	clearflag FLAG_TEMP_8
	clearflag FLAG_TEMP_9
	clearflag FLAG_TEMP_A
	playse SE_FAILURE
	waitse
	setmetatileinrange 38, 4, 42, 4, 0x4E3
	setmetatileinrange 38, 6, 42, 6, 0x4E3
	playse SE_NOT_EFFECTIVE
	special DrawWholeMapView
	release
	end


heatranPuzzleHint::
	msgbox heatranPuzzleHint_Text_0, MSGBOX_SIGN
	return


MtMortarDepthsHeatran::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_HEATRAN, 70, 1, FLAG_HIDE_HEATRAN, 4, SPECIES_NONE, 110
	release
	end


heatranPuzzleHint_Text_0:
	.string "Face of the heat,\n"
	.string "wielder of the magma storm.$"
