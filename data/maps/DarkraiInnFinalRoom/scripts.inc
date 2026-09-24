DarkraiInnFinalRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DarkraiInnFinalRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

DarkraiInnFinalRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	return


DarkraiEncounter::
	lock
	faceplayer
	bosslegendaryencounterwithmoves SPECIES_DARKRAI, 70, LOCALID_DARKRAI, FLAG_HIDE_DARKRAI, 4, SPECIES_DARKRAI_MEGA, 110, MOVE_DARK_PULSE, MOVE_ICE_BEAM, MOVE_DARK_VOID, MOVE_DREAM_EATER
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq DarkraiEncounter_2
DarkraiEncounter_1:
	release
	end

DarkraiEncounter_2:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 4
	goto_if_eq DarkraiEncounter_4
	goto DarkraiEncounter_1

DarkraiEncounter_4:
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto DarkraiEncounter_1


WarpPlayerOutDarkraiRoom::
	warpwhitefade MAP_CHERRYGROVE_CITY, 29, 21
	waitstate
	end

