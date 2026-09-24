HiddenGrotto_Route47_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HiddenGrotto_Route47_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

HiddenGrotto_Route47_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto handleROUTE47GrottoEvent
	return


handleROUTE47GrottoEvent::
	special HiddenGrotto_InitializeCurrent
	switch VAR_RESULT
	case 0, handleROUTE47GrottoEvent_2
	case 1, handleROUTE47GrottoEvent_3
	case 2, handleROUTE47GrottoEvent_4
	case 3, handleROUTE47GrottoEvent_5
	case 4, handleROUTE47GrottoEvent_6
	return

handleROUTE47GrottoEvent_2:
	clearflag FLAG_ROUTE47_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE47, 28, 27
	return

handleROUTE47GrottoEvent_3:
	setflag FLAG_ROUTE47_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE47, 28, 27
	return

handleROUTE47GrottoEvent_4:
	clearflag FLAG_ROUTE47_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE47, 28, 27
	return

handleROUTE47GrottoEvent_5:
	clearflag FLAG_ROUTE47_GROTTO
	setobjectxyperm 2, 28, 27
	setobjectxyperm 1, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE47, 28, 27
	return

handleROUTE47GrottoEvent_6:
	clearflag FLAG_ROUTE47_GROTTO
	setobjectxyperm LOCALID_GROTTO_ITEM_ROUTE47, 28, 27
	setobjectxyperm LOCALID_GROTTO_POKEMON_ROUTE47, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE47, 14, 11
	return


ROUTE47_GrottoPokemon::
	lock
	faceplayer
	special HiddenGrotto_GetCurrentContentId
	copyvar VAR_0x8004, VAR_RESULT
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	special HiddenGrotto_CreateCurrentMon
	compare VAR_RESULT, FALSE
	goto_if_eq ROUTE47_GrottoPokemon_2
	waitse
	delay 40
	waitmoncry
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE47_GROTTO
	dowildbattle
	removeobject 2
	release
	end

ROUTE47_GrottoPokemon_2:
	release
	end


FindItem_ROUTE47_Grotto::
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindItem_ROUTE47_Grotto_2
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE47_GROTTO
	removeobject 1
	end

FindItem_ROUTE47_Grotto_2:
	end


FindHiddenItem_ROUTE47_Grotto::
	special HiddenGrotto_GetCurrentContentType
	compare VAR_RESULT, 4
	goto_if_ne FindHiddenItem_ROUTE47_Grotto_2
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindHiddenItem_ROUTE47_Grotto_5
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE47_GROTTO
	end

FindHiddenItem_ROUTE47_Grotto_2:
	end

FindHiddenItem_ROUTE47_Grotto_5:
	end

