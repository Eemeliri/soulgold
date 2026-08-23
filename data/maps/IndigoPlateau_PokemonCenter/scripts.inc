# 1 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 2 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
.set LOCALID_NURSE, 1
# 3 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 4 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_PokemonCenter_MapScripts::
# 5 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	@map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
# 6 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, IndigoPlateau_PokemonCenter_OnFrame 
# 7 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, IndigoPlateau_PokemonCenter_OnLoad
# 8 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.byte 0
# 9 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 10 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_PokemonCenter_OnLoad::
# 11 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU_POKEMON_CENTER
# 12 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	end
# 13 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 14 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_PokemonCenter_OnFrame::
# 15 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script_2 VAR_LEAGUE_STATE, 0, IndigoPlateau_PokemonCenter_Enter
# 16 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script_2 VAR_LEAGUE_STATE, 2, IndigoPlateau_PokemonCenter_Enter
# 17 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script_2 VAR_LEAGUE_STATE, 3, IndigoPlateau_PokemonCenter_Enter
# 18 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script_2 VAR_LEAGUE_STATE, 4, IndigoPlateau_PokemonCenter_Enter
# 19 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script_2 VAR_LEAGUE_STATE, 5, IndigoPlateau_PokemonCenter_Enter
# 20 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	map_script_2 VAR_LEAGUE_STATE, 6, IndigoPlateau_PokemonCenter_Enter
# 21 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte 0
# 22 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 23 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_PokemonCenter_Enter::
# 24 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	setflag FLAG_VISITED_INDIGO_PLATEAU
# 25 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	setvar VAR_LEAGUE_STATE, 1
# 26 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	end
# 27 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 28 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_EventScript_Cooltrainer::
# 29 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_Text_CooltrainerM, MSGBOX_NPC
# 30 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	end
# 31 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 32 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_EventScript_BlackBelt::
# 33 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_Text_Blackbelt, MSGBOX_NPC
# 34 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	end
# 35 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 36 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_EventScript_ShigyNinja::
# 37 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_Text_ShigyNinja, MSGBOX_NPC
# 38 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	end
# 39 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 40 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_ShigyNinja:
# 41 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "Congrats on making it here!\p"
# 42 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "I've seen tons of trainers come\n"
# 43 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "through here over the years, and\l"
# 44 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "all of them are wonderfully unique.\p"
# 45 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "You should be proud of yourself\n"
# 46 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "for getting this far!\p"
# 47 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "Now, go get em'!$"
# 48 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 49 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_Blackbelt:
# 50 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "The Pokémon League is not taking\n"
# 51 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "new challengers at the moment.\p"
# 52 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "Please check back later.$"
# 53 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 54 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_CooltrainerM:
# 55 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "At the Pokémon League, you'll get\n"
# 56 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "tested by the Elite Four.\p"
# 57 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "You have to beat them all. If you\n"
# 58 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "lose, you have to start all over!$"
# 59 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 60 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_EventScript_Silver::
# 61 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	lock
# 62 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	faceplayer 
# 63 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	goto_if_set FLAG_DAILY_BEAT_SILVER, IndigoPlateau_EventScript_SilverBeat
# 64 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_Text_RivalEntrance1, MSGBOX_DEFAULT
# 65 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	call_if_eq VAR_STARTER_MON, 0, IndigoPlateau_Silver_Battle_Cyndaquil
# 66 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	call_if_eq VAR_STARTER_MON, 1, IndigoPlateau_Silver_Battle_Totodile
# 67 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	call_if_eq VAR_STARTER_MON, 2, IndigoPlateau_Silver_Battle_Chikorita
# 68 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
# 69 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	setflag FLAG_DAILY_BEAT_SILVER
# 70 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	release
# 71 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	end
# 72 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 73 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_EventScript_SilverBeat::
# 74 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
# 75 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	closemessage
# 76 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	release
# 77 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	end
# 78 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 79 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Silver_Battle_Cyndaquil::
# 80 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_7, IndigoPlateau_Text_RivalWin
# 81 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	return
# 82 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 83 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Silver_Battle_Totodile::
# 84 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_7, IndigoPlateau_Text_RivalWin
# 85 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	return
# 86 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 87 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Silver_Battle_Chikorita::
# 88 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_7, IndigoPlateau_Text_RivalWin
# 89 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	return
# 90 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 91 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_RivalEntrance1:
# 92 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Hold it.\p"
# 93 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "You're going to take the Pokémon\n"
# 94 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "League challenge now?\p"
# 95 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "That's not going to happen.\p"
# 96 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "My super-well-trained Pokémon\n"
# 97 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "are going to pound you.\p"
# 98 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "{PLAYER}!\n"
# 99 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "I challenge you!$"
# 100 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 101 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_RivalWin:
# 102 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "…\p"
# 103 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Ok--I lost…$"
# 104 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 105 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_RivalAfter:
# 106 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "…Darn… I still can't win…\p"
# 107 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "I… I have to think more about my\n"
# 108 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Pokémon…\p"
# 109 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Humph! Try not to lose!$"
# 110 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 111 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_TeleportGuy1:
# 112 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Ah! You're challenging the Elite\n"
# 113 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Four? Are you sure you're ready?\p"
# 114 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "If you need to train some more,\n"
# 115 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "my Abra can help you.\p"
# 116 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "It can Teleport you home.\p"
# 117 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Would you like to go home now?$"
# 118 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 119 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_TeleportGuyYes:
# 120 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Ok, Ok. Picture your house in your\n"
# 121 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "mind…$"
# 122 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 123 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_TeleportGuyNo:
# 124 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Ok, Ok. The best of luck to you!$"
# 125 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"

# 126 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_Text_Abra:
# 127 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
    .string "Abra: Aabra…$"

IndigoPlateau_StoneMerchant::
# 131 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	lock
# 132 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	faceplayer
# 133 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	message IndigoPlateau_StoneMerchant_Text_0
# 134 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	waitmessage
# 135 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	pokemart IndigoPlateau_StoneMerchantMart
# 136 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_StoneMerchant_Text_1
# 137 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	release
	end


IndigoPlateau_GemMerchant::
# 142 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	lock
# 143 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	faceplayer
# 144 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	message IndigoPlateau_StoneMerchant_Text_0
# 145 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	waitmessage
# 146 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	pokemart IndigoPlateau_GemMerchantMart
# 147 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	msgbox IndigoPlateau_StoneMerchant_Text_1
# 148 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	release
	end


	.align 2
# 152 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_StoneMerchantMart:
# 153 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_FIRE_STONE
# 154 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_WATER_STONE
# 155 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_LEAF_STONE
# 156 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_THUNDER_STONE
# 157 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_MOON_STONE
# 158 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_ICE_STONE
# 159 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_SUN_STONE
# 160 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_SHINY_STONE
# 161 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_DUSK_STONE
# 162 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_DAWN_STONE
# 163 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_LINKING_CORD
# 164 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_AUSPICIOUS_ARMOR
# 165 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_MALICIOUS_ARMOR
	.2byte ITEM_NONE

	.align 2
# 168 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
IndigoPlateau_GemMerchantMart:
# 169 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_NORMAL_GEM
# 170 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_FIRE_GEM
# 171 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_WATER_GEM
# 172 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_ELECTRIC_GEM
# 173 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_GRASS_GEM
# 174 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_ICE_GEM
# 175 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_FIGHTING_GEM
# 176 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_POISON_GEM
# 177 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_GROUND_GEM
# 178 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_FLYING_GEM
# 179 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_PSYCHIC_GEM
# 180 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_BUG_GEM
# 181 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_ROCK_GEM
# 182 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_GHOST_GEM
# 183 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_DRAGON_GEM
# 184 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_DARK_GEM
# 185 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_STEEL_GEM
# 186 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.2byte ITEM_FAIRY_GEM
	.2byte ITEM_NONE

IndigoPlateau_StoneMerchant_Text_0:
# 133 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "Welcome! How may I help you?$"

IndigoPlateau_StoneMerchant_Text_1:
# 136 "data/maps/IndigoPlateau_PokemonCenter/scripts.pory"
	.string "Come back soon!$"
