HiddenGrotto_Ilex_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HiddenGrotto_Ilex_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

HiddenGrotto_Ilex_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto handleILEXGrottoEvent
	return


handleILEXGrottoEvent::
	special HiddenGrotto_InitializeCurrent
	switch VAR_RESULT
	case 0, handleILEXGrottoEvent_2
	case 1, handleILEXGrottoEvent_3
	case 2, handleILEXGrottoEvent_4
	case 3, handleILEXGrottoEvent_5
	case 4, handleILEXGrottoEvent_6
	return

handleILEXGrottoEvent_2:
	clearflag FLAG_ILEX_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ILEX, 28, 27
	return

handleILEXGrottoEvent_3:
	setflag FLAG_ILEX_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ILEX, 28, 27
	return

handleILEXGrottoEvent_4:
	clearflag FLAG_ILEX_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ILEX, 28, 27
	return

handleILEXGrottoEvent_5:
	clearflag FLAG_ILEX_GROTTO
	setobjectxyperm 2, 28, 27
	setobjectxyperm 1, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ILEX, 28, 27
	return

handleILEXGrottoEvent_6:
	clearflag FLAG_ILEX_GROTTO
	setobjectxyperm LOCALID_GROTTO_ITEM_ILEX, 28, 27
	setobjectxyperm LOCALID_GROTTO_POKEMON_ILEX, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ILEX, 14, 11
	return


ILEX_GrottoPokemon::
	lock
	faceplayer
	special HiddenGrotto_GetCurrentContentId
	copyvar VAR_0x8004, VAR_RESULT
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	special HiddenGrotto_CreateCurrentMon
	compare VAR_RESULT, FALSE
	goto_if_eq ILEX_GrottoPokemon_2
	waitse
	delay 40
	waitmoncry
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ILEX_GROTTO
	dowildbattle
	removeobject 2
	release
	end

ILEX_GrottoPokemon_2:
	release
	end


FindItem_ILEX_Grotto::
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindItem_ILEX_Grotto_2
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ILEX_GROTTO
	removeobject 1
	end

FindItem_ILEX_Grotto_2:
	end


FindHiddenItem_ILEX_Grotto::
	special HiddenGrotto_GetCurrentContentType
	compare VAR_RESULT, 4
	goto_if_ne FindHiddenItem_ILEX_Grotto_2
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindHiddenItem_ILEX_Grotto_5
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ILEX_GROTTO
	end

FindHiddenItem_ILEX_Grotto_2:
	end

FindHiddenItem_ILEX_Grotto_5:
	end

