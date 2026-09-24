HiddenGrotto_Route32_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HiddenGrotto_Route32_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

HiddenGrotto_Route32_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto handleRoute32GrottoEvent
	return


handleRoute32GrottoEvent::
	special HiddenGrotto_InitializeCurrent
	switch VAR_RESULT
	case 0, handleRoute32GrottoEvent_2
	case 1, handleRoute32GrottoEvent_3
	case 2, handleRoute32GrottoEvent_4
	case 3, handleRoute32GrottoEvent_5
	case 4, handleRoute32GrottoEvent_6
	return

handleRoute32GrottoEvent_2:
	clearflag FLAG_ROUTE32_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE32, 28, 27
	return

handleRoute32GrottoEvent_3:
	setflag FLAG_ROUTE32_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE32, 28, 27
	return

handleRoute32GrottoEvent_4:
	clearflag FLAG_ROUTE32_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE32, 28, 27
	return

handleRoute32GrottoEvent_5:
	clearflag FLAG_ROUTE32_GROTTO
	setobjectxyperm 2, 28, 27
	setobjectxyperm 1, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE32, 28, 27
	return

handleRoute32GrottoEvent_6:
	clearflag FLAG_ROUTE32_GROTTO
	setobjectxyperm LOCALID_GROTTO_ITEM_ROUTE32, 28, 27
	setobjectxyperm LOCALID_GROTTO_POKEMON_ROUTE32, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE32, 14, 11
	return


Route32GrottoPokemon::
	lock
	faceplayer
	special HiddenGrotto_GetCurrentContentId
	copyvar VAR_0x8004, VAR_RESULT
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	special HiddenGrotto_CreateCurrentMon
	compare VAR_RESULT, FALSE
	goto_if_eq Route32GrottoPokemon_2
	waitse
	delay 40
	waitmoncry
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE32_GROTTO
	dowildbattle
	removeobject 2
	release
	end

Route32GrottoPokemon_2:
	release
	end


FindItem_Route32Grotto::
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindItem_Route32Grotto_2
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE32_GROTTO
	removeobject 1
	end

FindItem_Route32Grotto_2:
	end


FindHiddenItem_Route32Grotto::
	special HiddenGrotto_GetCurrentContentType
	compare VAR_RESULT, 4
	goto_if_ne FindHiddenItem_Route32Grotto_2
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindHiddenItem_Route32Grotto_5
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE32_GROTTO
	end

FindHiddenItem_Route32Grotto_2:
	end

FindHiddenItem_Route32Grotto_5:
	end

