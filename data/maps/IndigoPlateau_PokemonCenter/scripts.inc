
.set LOCALID_NURSE, 1

IndigoPlateau_PokemonCenter_MapScripts::
	@map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, IndigoPlateau_PokemonCenter_OnFrame 
	map_script MAP_SCRIPT_ON_LOAD, IndigoPlateau_PokemonCenter_OnLoad
	.byte 0

IndigoPlateau_PokemonCenter_OnLoad::
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU_POKEMON_CENTER
	end

IndigoPlateau_PokemonCenter_OnFrame::
	map_script_2 VAR_LEAGUE_STATE, 0, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 2, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 3, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 4, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 5, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 6, IndigoPlateau_PokemonCenter_Enter
	.2byte 0

IndigoPlateau_PokemonCenter_Enter::
	setflag FLAG_VISITED_INDIGO_PLATEAU
	setvar VAR_LEAGUE_STATE, 1
	end

IndigoPlateau_EventScript_Cooltrainer::
	msgbox IndigoPlateau_Text_CooltrainerM, MSGBOX_NPC
	end

IndigoPlateau_EventScript_BlackBelt::
	msgbox IndigoPlateau_Text_Blackbelt, MSGBOX_NPC
	end

IndigoPlateau_EventScript_ShigyNinja::
	msgbox IndigoPlateau_Text_ShigyNinja, MSGBOX_NPC
	end

IndigoPlateau_Text_ShigyNinja:
	.string "Congrats on making it here!\p"
	.string "I've seen tons of trainers come\n"
	.string "through here over the years, and\l"
	.string "all of them are wonderfully unique.\p"
	.string "You should be proud of yourself\n"
	.string "for getting this far!\p"
	.string "Now, go get em'!$"

IndigoPlateau_Text_Blackbelt:
	.string "The Pokémon League is not taking\n"
	.string "new challengers at the moment.\p"
	.string "Please check back later.$"

IndigoPlateau_Text_CooltrainerM:
    .string "At the Pokémon League, you'll get\n"
    .string "tested by the Elite Four.\p"
    .string "You have to beat them all. If you\n"
    .string "lose, you have to start all over!$"

IndigoPlateau_EventScript_Silver::
	lock
	faceplayer 
	goto_if_set FLAG_DAILY_BEAT_SILVER, IndigoPlateau_EventScript_SilverBeat
	msgbox IndigoPlateau_Text_RivalEntrance1, MSGBOX_DEFAULT
	call_if_eq VAR_STARTER_MON, 0, IndigoPlateau_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, IndigoPlateau_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, IndigoPlateau_Silver_Battle_Chikorita
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	setflag FLAG_DAILY_BEAT_SILVER
	release
	end

IndigoPlateau_EventScript_SilverBeat::
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_7, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_7, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_7, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Text_RivalEntrance1:
    .string "Hold it.\p"
    .string "You're going to take the Pokémon\n"
    .string "League challenge now?\p"
    .string "That's not going to happen.\p"
    .string "My super-well-trained Pokémon\n"
    .string "are going to pound you.\p"
    .string "{PLAYER}!\n"
    .string "I challenge you!$"

IndigoPlateau_Text_RivalWin:
    .string "…\p"
    .string "Ok--I lost…$"

IndigoPlateau_Text_RivalAfter:
    .string "…Darn… I still can't win…\p"
    .string "I… I have to think more about my\n"
    .string "Pokémon…\p"
    .string "Humph! Try not to lose!$"

IndigoPlateau_Text_TeleportGuy1:
    .string "Ah! You're challenging the Elite\n"
    .string "Four? Are you sure you're ready?\p"
    .string "If you need to train some more,\n"
    .string "my Abra can help you.\p"
    .string "It can Teleport you home.\p"
    .string "Would you like to go home now?$"

IndigoPlateau_Text_TeleportGuyYes:
    .string "Ok, Ok. Picture your house in your\n"
    .string "mind…$"

IndigoPlateau_Text_TeleportGuyNo:
    .string "Ok, Ok. The best of luck to you!$"

IndigoPlateau_Text_Abra:
    .string "Abra: Aabra…$"

IndigoPlateau_StoneMerchant::
	lock
	faceplayer
	message IndigoPlateau_StoneMerchant_Text_0
	waitmessage
	pokemart IndigoPlateau_StoneMerchantMart
	msgbox IndigoPlateau_StoneMerchant_Text_1
	release
	end


IndigoPlateau_GemMerchant::
	lock
	faceplayer
	message IndigoPlateau_StoneMerchant_Text_0
	waitmessage
	pokemart IndigoPlateau_GemMerchantMart
	msgbox IndigoPlateau_StoneMerchant_Text_1
	release
	end


	.align 2
IndigoPlateau_StoneMerchantMart:
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_MOON_STONE
	.2byte ITEM_ICE_STONE
	.2byte ITEM_SUN_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_DUSK_STONE
	.2byte ITEM_DAWN_STONE
	.2byte ITEM_LINKING_CORD
	.2byte ITEM_AUSPICIOUS_ARMOR
	.2byte ITEM_MALICIOUS_ARMOR
	.2byte ITEM_PEAT_BLOCK
	.2byte ITEM_BLACK_AUGURITE
	.2byte ITEM_NONE

	.align 2
IndigoPlateau_GemMerchantMart:
	.2byte ITEM_NORMAL_GEM
	.2byte ITEM_FIRE_GEM
	.2byte ITEM_WATER_GEM
	.2byte ITEM_ELECTRIC_GEM
	.2byte ITEM_GRASS_GEM
	.2byte ITEM_ICE_GEM
	.2byte ITEM_FIGHTING_GEM
	.2byte ITEM_POISON_GEM
	.2byte ITEM_GROUND_GEM
	.2byte ITEM_FLYING_GEM
	.2byte ITEM_PSYCHIC_GEM
	.2byte ITEM_BUG_GEM
	.2byte ITEM_ROCK_GEM
	.2byte ITEM_GHOST_GEM
	.2byte ITEM_DRAGON_GEM
	.2byte ITEM_DARK_GEM
	.2byte ITEM_STEEL_GEM
	.2byte ITEM_FAIRY_GEM
	.2byte ITEM_NONE

IndigoPlateau_StoneMerchant_Text_0:
	.string "Welcome! How may I help you?$"

IndigoPlateau_StoneMerchant_Text_1:
	.string "Come back soon!$"
