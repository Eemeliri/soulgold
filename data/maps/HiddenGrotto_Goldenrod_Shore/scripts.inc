HiddenGrotto_Goldenrod_Shore_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HiddenGrotto_Goldenrod_Shore_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

HiddenGrotto_Goldenrod_Shore_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto handleGoldenrodShoreGrottoEvent
	return


handleGoldenrodShoreGrottoEvent::
	special HiddenGrotto_InitializeCurrent
	switch VAR_RESULT
	case 0, handleGoldenrodShoreGrottoEvent_2
	case 1, handleGoldenrodShoreGrottoEvent_3
	case 2, handleGoldenrodShoreGrottoEvent_4
	case 3, handleGoldenrodShoreGrottoEvent_5
	case 4, handleGoldenrodShoreGrottoEvent_6
	return

handleGoldenrodShoreGrottoEvent_2:
	clearflag FLAG_GOLDENROD_SHORE_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_GOLDENROD, 28, 27
	return

handleGoldenrodShoreGrottoEvent_3:
	setflag FLAG_GOLDENROD_SHORE_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_GOLDENROD, 28, 27
	return

handleGoldenrodShoreGrottoEvent_4:
	clearflag FLAG_GOLDENROD_SHORE_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_GOLDENROD, 28, 27
	return

handleGoldenrodShoreGrottoEvent_5:
	clearflag FLAG_GOLDENROD_SHORE_GROTTO
	setobjectxyperm 2, 28, 27
	setobjectxyperm 1, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_GOLDENROD, 28, 27
	return

handleGoldenrodShoreGrottoEvent_6:
	clearflag FLAG_GOLDENROD_SHORE_GROTTO
	setobjectxyperm LOCALID_GROTTO_ITEM_GOLDENROD, 28, 27
	setobjectxyperm LOCALID_GROTTO_POKEMON_GOLDENROD, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_GOLDENROD, 14, 11
	return


GoldenrodShore_GrottoPokemon::
	lock
	faceplayer
	special HiddenGrotto_GetCurrentContentId
	copyvar VAR_0x8004, VAR_RESULT
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	special HiddenGrotto_CreateCurrentMon
	compare VAR_RESULT, FALSE
	goto_if_eq GoldenrodShore_GrottoPokemon_2
	waitse
	delay 40
	waitmoncry
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_GOLDENROD_SHORE_GROTTO
	dowildbattle
	removeobject 2
	release
	end

GoldenrodShore_GrottoPokemon_2:
	release
	end


FindItem_GoldenrodShore_Grotto::
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindItem_GoldenrodShore_Grotto_2
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_GOLDENROD_SHORE_GROTTO
	removeobject 1
	end

FindItem_GoldenrodShore_Grotto_2:
	end


FindHiddenItem_GoldenrodShore_Grotto::
	special HiddenGrotto_GetCurrentContentType
	compare VAR_RESULT, 4
	goto_if_ne FindHiddenItem_GoldenrodShore_Grotto_2
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindHiddenItem_GoldenrodShore_Grotto_5
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_GOLDENROD_SHORE_GROTTO
	end

FindHiddenItem_GoldenrodShore_Grotto_2:
	end

FindHiddenItem_GoldenrodShore_Grotto_5:
	end

