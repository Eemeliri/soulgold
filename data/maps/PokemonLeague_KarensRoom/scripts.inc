PokemonLeague_KarensRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonLeague_KarensRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KarensRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KarensRoom_OnTransition::
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KarensRoom_SetTitleDefenseWarp
	setdynamicwarp MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM, 0
	end

PokemonLeague_KarensRoom_SetTitleDefenseWarp::
	setdynamicwarp MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM_TITLE_DEFENSE, 0
	end

PokemonLeague_KarensRoom_OnResume::
	setvar VAR_0x8004, 3
	@special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KarensRoom_EventScript_Karen::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 5, PokemonLeague_KarensRoom_EventScript_KarenDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematch
	msgbox PokemonLeague_KarensRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_1, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematch::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	goto_if_eq VAR_TEMP_1, 1, PokemonLeague_KarensRoom_EventScript_KarenRematchAlt
	trainerbattle_no_intro TRAINER_KAREN_2, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeatPostgame

PokemonLeague_KarensRoom_EventScript_KarenRematchAlt::
	trainerbattle_no_intro TRAINER_KAREN_REMATCH_ALT, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeatPostgame

PokemonLeague_KarensRoom_EventScript_KarenOnDefeat::
    clearflag FLAG_TEMP_5
	createfieldmugshot MUGSHOT_KAREN
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x40E, FALSE
	setmetatile 6, 2, 0x416, FALSE	
	playse SE_BANG
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar VAR_LEAGUE_STATE, 5
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenDefeated::
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenOnDefeatPostgame::
    clearflag FLAG_TEMP_5
	createfieldmugshot MUGSHOT_KAREN
	msgbox PokemonLeague_KarensRoom_Text_DefeatPostgame, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x40E, FALSE
	setmetatile 6, 2, 0x416, FALSE	
	playse SE_BANG
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar VAR_LEAGUE_STATE, 5
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenDefeatedPostgame::
	msgbox PokemonLeague_KarensRoom_Text_DefeatPostgame, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KarensRoom_Text_RematchBefore:
    .string "Karen: Ah, it's you again.\p"
    .string "I trust you haven't forgotten\n"
    .string "my belief:\p"
    .string "True strength arises from trust\n"
    .string "in one's Pokémon.\p"
    .string "Since our last encounter, my\n"
    .string "bond with my Pokémon has\l"
    .string "deepened further.\p"
    .string "Are you ready to face a team\n"
    .string "united by an unbreakable bond?\p"
    .string "Show me the power of the bond\n"
    .string "with your Pokémon.$"

PokemonLeague_KarensRoom_Text_Before:
    .string "I am Karen of the Elite Four.\p"
    .string "You're {PLAYER}? How amusing.\p"
    .string "I love Dark-type Pokémon.\p"
    .string "I find their wild, tough image\n"
    .string "to be so appealing. And they're\l"
    .string "so strong.\p"
    .string "Think you can take them?\n"
    .string "Just try to entertain me.\p"
    .string "Let's go.$"

PokemonLeague_KarensRoom_Text_Beaten:
    .string "Well, aren't you good. I like that\n"
    .string "in a trainer.$"

PokemonLeague_KarensRoom_Text_Defeat:
    .string "Strong Pokémon.\p"
    .string "Weak Pokémon.\p"
    .string "That is only the selfish\n"
    .string "perception of people.\p"
    .string "Truly skilled trainers should\n"
    .string "try to win with their favorites.\p"
    .string "I like your style. You understand\n"
    .string "what's important.\p"
    .string "Go on--the Champion is waiting.$"

PokemonLeague_KarensRoom_Text_DefeatPostgame:
    .string "Strong Pokémon.\p"
    .string "Weak Pokémon.\p"
    .string "That is only the selfish\n"
    .string "perception of people.\p"
    .string "Truly skilled trainers should\n"
    .string "try to win with their favorites.\p"
    .string "I like your style. You understand\n"
    .string "what's important.\p"
    .string "Go on--the Challenger will arrive.$"
