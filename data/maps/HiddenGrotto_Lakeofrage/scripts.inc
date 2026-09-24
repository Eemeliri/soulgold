HiddenGrotto_Lakeofrage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HiddenGrotto_Lakeofrage_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

HiddenGrotto_Lakeofrage_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto handleLAKEOFRAGEGrottoEvent
	return


handleLAKEOFRAGEGrottoEvent::
	special HiddenGrotto_InitializeCurrent
	switch VAR_RESULT
	case 0, handleLAKEOFRAGEGrottoEvent_2
	case 1, handleLAKEOFRAGEGrottoEvent_3
	case 2, handleLAKEOFRAGEGrottoEvent_4
	case 3, handleLAKEOFRAGEGrottoEvent_5
	case 4, handleLAKEOFRAGEGrottoEvent_6
	return

handleLAKEOFRAGEGrottoEvent_2:
	clearflag FLAG_LAKEOFRAGE_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_LAKEOFRAGE, 28, 27
	return

handleLAKEOFRAGEGrottoEvent_3:
	setflag FLAG_LAKEOFRAGE_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_LAKEOFRAGE, 28, 27
	return

handleLAKEOFRAGEGrottoEvent_4:
	clearflag FLAG_LAKEOFRAGE_GROTTO
	setobjectxyperm 1, 28, 27
	setobjectxyperm 2, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_LAKEOFRAGE, 28, 27
	return

handleLAKEOFRAGEGrottoEvent_5:
	clearflag FLAG_LAKEOFRAGE_GROTTO
	setobjectxyperm 2, 28, 27
	setobjectxyperm 1, 14, 11
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_LAKEOFRAGE, 28, 27
	return

handleLAKEOFRAGEGrottoEvent_6:
	clearflag FLAG_LAKEOFRAGE_GROTTO
	setobjectxyperm LOCALID_GROTTO_ITEM_LAKEOFRAGE, 28, 27
	setobjectxyperm LOCALID_GROTTO_POKEMON_LAKEOFRAGE, 28, 27
	setobjectxyperm LOCALID_GROTTO_HIDDEN_ITEM_LAKEOFRAGE, 14, 11
	return


LAKEOFRAGE_GrottoPokemon::
	lock
	faceplayer
	special HiddenGrotto_GetCurrentContentId
	copyvar VAR_0x8004, VAR_RESULT
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	special HiddenGrotto_CreateCurrentMon
	compare VAR_RESULT, FALSE
	goto_if_eq LAKEOFRAGE_GrottoPokemon_2
	waitse
	delay 40
	waitmoncry
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_LAKEOFRAGE_GROTTO
	dowildbattle
	removeobject 2
	release
	end

LAKEOFRAGE_GrottoPokemon_2:
	release
	end


FindItem_LAKEOFRAGE_Grotto::
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindItem_LAKEOFRAGE_Grotto_2
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_LAKEOFRAGE_GROTTO
	removeobject 1
	end

FindItem_LAKEOFRAGE_Grotto_2:
	end


FindHiddenItem_LAKEOFRAGE_Grotto::
	special HiddenGrotto_GetCurrentContentType
	compare VAR_RESULT, 4
	goto_if_ne FindHiddenItem_LAKEOFRAGE_Grotto_2
	special HiddenGrotto_GetCurrentContentId
	finditem VAR_RESULT
	compare VAR_0x8007, FALSE
	goto_if_eq FindHiddenItem_LAKEOFRAGE_Grotto_5
	special HiddenGrotto_EmptyCurrent
	setflag FLAG_LAKEOFRAGE_GROTTO
	end

FindHiddenItem_LAKEOFRAGE_Grotto_2:
	end

FindHiddenItem_LAKEOFRAGE_Grotto_5:
	end

