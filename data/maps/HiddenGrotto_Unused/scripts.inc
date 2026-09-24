HiddenGrotto_Unused_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HiddenGrotto_Unused_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

HiddenGrotto_Unused_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto handleVajraDesertWestGrottoEvent
	return


handleVajraDesertWestGrottoEvent::
	special HiddenGrotto_InitializeCurrent
	switch VAR_RESULT
	case 0, handleVajraDesertWestGrottoEvent_2
	case 1, handleVajraDesertWestGrottoEvent_3
	case 2, handleVajraDesertWestGrottoEvent_4
	case 3, handleVajraDesertWestGrottoEvent_5
	case 4, handleVajraDesertWestGrottoEvent_6
	return

handleVajraDesertWestGrottoEvent_2:
	clearflag FLAG_VAJRA_DESERT_WEST_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_VAJRA_DESERT_WEST, 28, 27
	return

handleVajraDesertWestGrottoEvent_3:
	setflag FLAG_VAJRA_DESERT_WEST_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_VAJRA_DESERT_WEST, 28, 27
	return

handleVajraDesertWestGrottoEvent_4:
	clearflag FLAG_VAJRA_DESERT_WEST_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_VAJRA_DESERT_WEST, 28, 27
	return

handleVajraDesertWestGrottoEvent_5:
	clearflag FLAG_VAJRA_DESERT_WEST_GROTTO
	setobjectxyperm 2, 28, 27
	setobjectxyperm 1, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_VAJRA_DESERT_WEST, 28, 27
	return

handleVajraDesertWestGrottoEvent_6:
	clearflag FLAG_VAJRA_DESERT_WEST_GROTTO
	setobjectxyperm LOCALID_GROTTO_ITEM_VAJRA_DESERT_WEST, 28, 27
	setobjectxyperm LOCALID_GROTTO_POKEMON_VAJRA_DESERT_WEST, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_VAJRA_DESERT_WEST, 14, 11
	return


VajraDesertWest_GrottoPokemon::
	lock
	faceplayer
	special HiddenGrotto_GetCurrentContentId
	copyvar VAR_0x8004, VAR_RESULT
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	special HiddenGrotto_CreateCurrentMon
	compare VAR_RESULT, FALSE
	goto_if_eq VajraDesertWest_GrottoPokemon_2
	waitse
	delay 40
	waitmoncry
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_VAJRA_DESERT_WEST_GROTTO
	dowildbattle
	removeobject 2
	release
	end

VajraDesertWest_GrottoPokemon_2:
	release
	end


FindItem_VajraDesertWest_Grotto::
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindItem_VajraDesertWest_Grotto_2
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_VAJRA_DESERT_WEST_GROTTO
	removeobject 1
	end

FindItem_VajraDesertWest_Grotto_2:
	end


FindHiddenItem_VajraDesertWest_Grotto::
	special HiddenGrotto_GetCurrentContentType
	compare VAR_RESULT, 4
	goto_if_ne FindHiddenItem_VajraDesertWest_Grotto_2
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindHiddenItem_VajraDesertWest_Grotto_5
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_VAJRA_DESERT_WEST_GROTTO
	end

FindHiddenItem_VajraDesertWest_Grotto_2:
	end

FindHiddenItem_VajraDesertWest_Grotto_5:
	end

