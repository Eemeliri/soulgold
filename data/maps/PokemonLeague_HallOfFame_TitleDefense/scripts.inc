PokemonLeague_HallOfFame_TitleDefense_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_HallOfFame_TitleDefense_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

PokemonLeague_HallOfFame_TitleDefense_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_LEAGUE_STATE, 6, TitleDefense_RegisterToHallOfFame
	.2byte 0


TitleDefense_RegisterToHallOfFame::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, TitleDefense_RegisterToHallOfFame_Movement_0
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD
	delay 40
	setvar VAR_TEMP_1, 1
	call PokemonLeague_HallOfFame_EventScript_SetGameClearFlags
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end


TitleDefense_RegisterToHallOfFame_Movement_0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end
