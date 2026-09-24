HiddenGrotto_Route35_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HiddenGrotto_Route35_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

HiddenGrotto_Route35_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto handleROUTE35GrottoEvent
	return


handleROUTE35GrottoEvent::
	special HiddenGrotto_InitializeCurrent
	switch VAR_RESULT
	case 0, handleROUTE35GrottoEvent_2
	case 1, handleROUTE35GrottoEvent_3
	case 2, handleROUTE35GrottoEvent_4
	case 3, handleROUTE35GrottoEvent_5
	case 4, handleROUTE35GrottoEvent_6
	return

handleROUTE35GrottoEvent_2:
	clearflag FLAG_ROUTE35_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE35, 28, 27
	return

handleROUTE35GrottoEvent_3:
	setflag FLAG_ROUTE35_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE35, 28, 27
	return

handleROUTE35GrottoEvent_4:
	clearflag FLAG_ROUTE35_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE35, 28, 27
	return

handleROUTE35GrottoEvent_5:
	clearflag FLAG_ROUTE35_GROTTO
	setobjectxyperm 2, 28, 27
	setobjectxyperm 1, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE35, 28, 27
	return

handleROUTE35GrottoEvent_6:
	clearflag FLAG_ROUTE35_GROTTO
	setobjectxyperm LOCALID_GROTTO_ITEM_ROUTE35, 28, 27
	setobjectxyperm LOCALID_GROTTO_POKEMON_ROUTE35, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_ROUTE35, 14, 11
	return


ROUTE35_GrottoPokemon::
	lock
	faceplayer
	special HiddenGrotto_GetCurrentContentId
	copyvar VAR_0x8004, VAR_RESULT
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	special HiddenGrotto_CreateCurrentMon
	compare VAR_RESULT, FALSE
	goto_if_eq ROUTE35_GrottoPokemon_2
	waitse
	delay 40
	waitmoncry
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE35_GROTTO
	dowildbattle
	removeobject 2
	release
	end

ROUTE35_GrottoPokemon_2:
	release
	end


FindItem_ROUTE35_Grotto::
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindItem_ROUTE35_Grotto_2
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE35_GROTTO
	removeobject 1
	end

FindItem_ROUTE35_Grotto_2:
	end


FindHiddenItem_ROUTE35_Grotto::
	special HiddenGrotto_GetCurrentContentType
	compare VAR_RESULT, 4
	goto_if_ne FindHiddenItem_ROUTE35_Grotto_2
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindHiddenItem_ROUTE35_Grotto_5
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_ROUTE35_GROTTO
	end

FindHiddenItem_ROUTE35_Grotto_2:
	end

FindHiddenItem_ROUTE35_Grotto_5:
	end

