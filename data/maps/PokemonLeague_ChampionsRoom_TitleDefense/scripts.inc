PokemonLeague_ChampionsRoom_TitleDefense_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonLeague_ChampionsRoom_TitleDefense_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_ChampionsRoom_TitleDefense_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

PokemonLeague_ChampionsRoom_TitleDefense_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, PokemonLeague_ChampionsRoom_TitleDefense_Begin
	.2byte 0


PokemonLeague_ChampionsRoom_TitleDefense_OnTransition::
	setflag FLAG_TEMP_1
	special TitleDefense_SelectChallenger
	end


PokemonLeague_ChampionsRoom_TitleDefense_Begin::
	lockall
	setvar VAR_TEMP_0, 1
	setflag FLAG_TEMP_2
	special DrawWholeMapView
	applymovement OBJ_EVENT_ID_PLAYER, PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_0
	waitmovement OBJ_EVENT_ID_PLAYER
	clearflag FLAG_TEMP_1
	addobject 1
	playse SE_EXIT
	waitse
	applymovement 1, PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_1
	waitmovement 1
	special TitleDefense_ShowIntro
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	special TitleDefense_PrepareBattle
	special PlayTrainerEncounterMusic
	dotrainerbattle
	clearflag FLAG_TEMP_5
	special TitleDefense_ShowFarewell
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_2
	waitmovement 1
	removeobject 1
	setmetatile 6, 1, 0x572, FALSE
	setmetatile 6, 2, 0x416, FALSE
	playse SE_BANG
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 4
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	special TitleDefense_IncrementWins
	setvar VAR_LEAGUE_STATE, 6
	applymovement OBJ_EVENT_ID_PLAYER, PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_3
	waitmovement OBJ_EVENT_ID_PLAYER
	warpsilent MAP_POKEMON_LEAGUE_HALL_OF_FAME_TITLE_DEFENSE, 0
	waitstate
	releaseall
	end


ChampionRoom_DefendTitleTrigger::
	end


PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_1:
	walk_up
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

PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	set_invisible
	step_end

PokemonLeague_ChampionsRoom_TitleDefense_Begin_Movement_3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
