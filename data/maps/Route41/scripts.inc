# 1 "data/maps/Route41/scripts.pory"

# 2 "data/maps/Route41/scripts.pory"
Route41_MapScripts::
# 3 "data/maps/Route41/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route41_MapScript_OnTransition
# 4 "data/maps/Route41/scripts.pory"
	.byte 0
# 5 "data/maps/Route41/scripts.pory"

# 6 "data/maps/Route41/scripts.pory"
Route41_MapScript_OnTransition::
# 7 "data/maps/Route41/scripts.pory"
	goto_if_eq VAR_COMPLETED_LUGIA, 4, Route41_MapScript_DoNothing
# 8 "data/maps/Route41/scripts.pory"
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
# 9 "data/maps/Route41/scripts.pory"
	end
# 10 "data/maps/Route41/scripts.pory"

# 11 "data/maps/Route41/scripts.pory"
Route41_MapScript_DoNothing::
# 12 "data/maps/Route41/scripts.pory"
	end
# 13 "data/maps/Route41/scripts.pory"

# 14 "data/maps/Route41/scripts.pory"
Route41_EventScript_Charlie::
# 15 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_CHARLIE, Route41_Text_SwimmermCharlieSeen, Route41_Text_SwimmermCharlieBeaten
# 16 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmermCharlieAfter, MSGBOX_AUTOCLOSE
# 17 "data/maps/Route41/scripts.pory"
	end
# 18 "data/maps/Route41/scripts.pory"

# 19 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermCharlieSeen:
# 20 "data/maps/Route41/scripts.pory"
	.string "The water's warm here.\n"
# 21 "data/maps/Route41/scripts.pory"
	.string "I'm loose and limber.\p"
# 22 "data/maps/Route41/scripts.pory"
	.string "Sure, I'll take you on!$"
# 23 "data/maps/Route41/scripts.pory"

# 24 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermCharlieBeaten:
# 25 "data/maps/Route41/scripts.pory"
	.string "Yikes! I've got prune skin!$"
# 26 "data/maps/Route41/scripts.pory"

# 27 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermCharlieAfter:
# 28 "data/maps/Route41/scripts.pory"
	.string "Isn't it relaxing just floating\n"
# 29 "data/maps/Route41/scripts.pory"
	.string "like this?$"
# 30 "data/maps/Route41/scripts.pory"

# 31 "data/maps/Route41/scripts.pory"
Route41_EventScript_George::
# 32 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_GEORGE, Route41_Text_SwimmermGeorgeSeen, Route41_Text_SwimmermGeorgeBeaten
# 33 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmermGeorgeAfter, MSGBOX_AUTOCLOSE
# 34 "data/maps/Route41/scripts.pory"
	end
# 35 "data/maps/Route41/scripts.pory"

# 36 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermGeorgeSeen:
# 37 "data/maps/Route41/scripts.pory"
	.string "I'm a bit tired.\n"
# 38 "data/maps/Route41/scripts.pory"
	.string "If I win, lend me your Pokémon.$"
# 39 "data/maps/Route41/scripts.pory"

# 40 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermGeorgeBeaten:
# 41 "data/maps/Route41/scripts.pory"
	.string "Pant, pant…$"
# 42 "data/maps/Route41/scripts.pory"

# 43 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermGeorgeAfter:
# 44 "data/maps/Route41/scripts.pory"
	.string "It's so far to Cianwood.\p"
# 45 "data/maps/Route41/scripts.pory"
	.string "But it's no easy return trip\n"
# 46 "data/maps/Route41/scripts.pory"
	.string "to Olivine either.\p"
# 47 "data/maps/Route41/scripts.pory"
	.string "What should I do?$"
# 48 "data/maps/Route41/scripts.pory"

# 49 "data/maps/Route41/scripts.pory"
Route41_EventScript_Berke::
# 50 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_BERKE, Route41_Text_SwimmermBerkeSeen, Route41_Text_SwimmermBerkeBeaten
# 51 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmermBerkeAfter, MSGBOX_AUTOCLOSE
# 52 "data/maps/Route41/scripts.pory"
	end
# 53 "data/maps/Route41/scripts.pory"

# 54 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermBerkeSeen:
# 55 "data/maps/Route41/scripts.pory"
	.string "See those islands that are\n"
# 56 "data/maps/Route41/scripts.pory"
	.string "blocked by whirlpools?\p"
# 57 "data/maps/Route41/scripts.pory"
	.string "There just has to be a secret!$"
# 58 "data/maps/Route41/scripts.pory"

# 59 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermBerkeBeaten:
# 60 "data/maps/Route41/scripts.pory"
	.string "What's the secret to your\n"
# 61 "data/maps/Route41/scripts.pory"
	.string "strength?$"
# 62 "data/maps/Route41/scripts.pory"

# 63 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermBerkeAfter:
# 64 "data/maps/Route41/scripts.pory"
	.string "It was a dark and stormy night…\p"
# 65 "data/maps/Route41/scripts.pory"
	.string "I saw this giant Pokémon flying\n"
# 66 "data/maps/Route41/scripts.pory"
	.string "from the islands.\p"
# 67 "data/maps/Route41/scripts.pory"
	.string "It was scattering feathers\n"
# 68 "data/maps/Route41/scripts.pory"
	.string "from its silver wings.$"
# 69 "data/maps/Route41/scripts.pory"

# 70 "data/maps/Route41/scripts.pory"
Route41_EventScript_Kirk::
# 71 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_KIRK, Route41_Text_SwimmermKirkSeen, Route41_Text_SwimmermKirkBeaten
# 72 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmermKirkAfter, MSGBOX_AUTOCLOSE
# 73 "data/maps/Route41/scripts.pory"
	end
# 74 "data/maps/Route41/scripts.pory"

# 75 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermKirkSeen:
# 76 "data/maps/Route41/scripts.pory"
	.string "The waves are wild here.\p"
# 77 "data/maps/Route41/scripts.pory"
	.string "They tire you out while\n"
# 78 "data/maps/Route41/scripts.pory"
	.string "you swim.$"
# 79 "data/maps/Route41/scripts.pory"

# 80 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermKirkBeaten:
# 81 "data/maps/Route41/scripts.pory"
	.string "I'm beat!$"
# 82 "data/maps/Route41/scripts.pory"

# 83 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermKirkAfter:
# 84 "data/maps/Route41/scripts.pory"
	.string "The currents keep me from\n"
# 85 "data/maps/Route41/scripts.pory"
	.string "reaching that island.$"
# 86 "data/maps/Route41/scripts.pory"

# 87 "data/maps/Route41/scripts.pory"
Route41_EventScript_Mathew::
# 88 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_MATHEW, Route41_Text_SwimmermMathewSeen, Route41_Text_SwimmermMathewBeaten
# 89 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmermMathewAfter, MSGBOX_AUTOCLOSE
# 90 "data/maps/Route41/scripts.pory"
	end
# 91 "data/maps/Route41/scripts.pory"

# 92 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermMathewSeen:
# 93 "data/maps/Route41/scripts.pory"
	.string "Are you seeking the secrets\n"
# 94 "data/maps/Route41/scripts.pory"
	.string "of Whirl Islands?$"
# 95 "data/maps/Route41/scripts.pory"

# 96 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermMathewBeaten:
# 97 "data/maps/Route41/scripts.pory"
	.string "Ooh, you've got great endurance!$"
# 98 "data/maps/Route41/scripts.pory"

# 99 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmermMathewAfter:
# 100 "data/maps/Route41/scripts.pory"
	.string "A secret about Whirl Islands…\p"
# 101 "data/maps/Route41/scripts.pory"
	.string "It's pitch-black inside!$"
# 102 "data/maps/Route41/scripts.pory"

# 103 "data/maps/Route41/scripts.pory"
Route41_EventScript_Kaylee::
# 104 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_KAYLEE, Route41_Text_SwimmerfKayleeSeen, Route41_Text_SwimmerfKayleeBeaten
# 105 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmerfKayleeAfter, MSGBOX_AUTOCLOSE
# 106 "data/maps/Route41/scripts.pory"
	end
# 107 "data/maps/Route41/scripts.pory"

# 108 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfKayleeSeen:
# 109 "data/maps/Route41/scripts.pory"
	.string "I'm on my way to Whirl Islands.\p"
# 110 "data/maps/Route41/scripts.pory"
	.string "I'm going exploring with friends.$"
# 111 "data/maps/Route41/scripts.pory"

# 112 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfKayleeBeaten:
# 113 "data/maps/Route41/scripts.pory"
	.string "Is that how you do it?$"
# 114 "data/maps/Route41/scripts.pory"

# 115 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfKayleeAfter:
# 116 "data/maps/Route41/scripts.pory"
	.string "There's supposed to be a big\n"
# 117 "data/maps/Route41/scripts.pory"
	.string "Pokémon deep beneath Whirl Islands.\p"
# 118 "data/maps/Route41/scripts.pory"
	.string "I wonder what it could be?$"
# 119 "data/maps/Route41/scripts.pory"

# 120 "data/maps/Route41/scripts.pory"
Route41_EventScript_Susie::
# 121 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_SUSIE, Route41_Text_SwimmerfSusieSeen, Route41_Text_SwimmerfSusieBeaten
# 122 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmerfSusieAfter, MSGBOX_AUTOCLOSE
# 123 "data/maps/Route41/scripts.pory"
	end
# 124 "data/maps/Route41/scripts.pory"

# 125 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfSusieSeen:
# 126 "data/maps/Route41/scripts.pory"
	.string "You look so elegant,\n"
# 127 "data/maps/Route41/scripts.pory"
	.string "riding your Pokémon.$"
# 128 "data/maps/Route41/scripts.pory"

# 129 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfSusieBeaten:
# 130 "data/maps/Route41/scripts.pory"
	.string "I'm crushed…$"
# 131 "data/maps/Route41/scripts.pory"

# 132 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfSusieAfter:
# 133 "data/maps/Route41/scripts.pory"
	.string "Wasn't there a hit song about\n"
# 134 "data/maps/Route41/scripts.pory"
	.string "a boy riding a Lapras?$"
# 135 "data/maps/Route41/scripts.pory"

# 136 "data/maps/Route41/scripts.pory"
Route41_EventScript_Denise::
# 137 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_DENISE, Route41_Text_SwimmerfDeniseSeen, Route41_Text_SwimmerfDeniseBeaten
# 138 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmerfDeniseAfter, MSGBOX_AUTOCLOSE
# 139 "data/maps/Route41/scripts.pory"
	end
# 140 "data/maps/Route41/scripts.pory"

# 141 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfDeniseSeen:
# 142 "data/maps/Route41/scripts.pory"
	.string "The weather is so beautiful,\n"
# 143 "data/maps/Route41/scripts.pory"
	.string "I'm in a daze!$"
# 144 "data/maps/Route41/scripts.pory"

# 145 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfDeniseBeaten:
# 146 "data/maps/Route41/scripts.pory"
	.string "Ohhh!$"
# 147 "data/maps/Route41/scripts.pory"

# 148 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfDeniseAfter:
# 149 "data/maps/Route41/scripts.pory"
	.string "A sunburn is the worst for skin.\p"
# 150 "data/maps/Route41/scripts.pory"
	.string "But I don't use a sunblock.\p"
# 151 "data/maps/Route41/scripts.pory"
	.string "I won't pollute the water.$"
# 152 "data/maps/Route41/scripts.pory"

# 153 "data/maps/Route41/scripts.pory"
Route41_EventScript_Kara::
# 154 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_KARA, Route41_Text_SwimmerfKaraSeen, Route41_Text_SwimmerfKaraBeaten
# 155 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmerfKaraAfter, MSGBOX_AUTOCLOSE
# 156 "data/maps/Route41/scripts.pory"
	end
# 157 "data/maps/Route41/scripts.pory"

# 158 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfKaraSeen:
# 159 "data/maps/Route41/scripts.pory"
	.string "If you need to rest,\n"
# 160 "data/maps/Route41/scripts.pory"
	.string "just tread water.\p"
# 161 "data/maps/Route41/scripts.pory"
	.string "You'll get your wind back,\n"
# 162 "data/maps/Route41/scripts.pory"
	.string "so you can keep on going strong.$"
# 163 "data/maps/Route41/scripts.pory"

# 164 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfKaraBeaten:
# 165 "data/maps/Route41/scripts.pory"
	.string "Oh! You have more energy than I do.$"
# 166 "data/maps/Route41/scripts.pory"

# 167 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfKaraAfter:
# 168 "data/maps/Route41/scripts.pory"
	.string "I heard roars from deep inside\n"
# 169 "data/maps/Route41/scripts.pory"
	.string "the Islands.$"
# 170 "data/maps/Route41/scripts.pory"

# 171 "data/maps/Route41/scripts.pory"
Route41_EventScript_Wendy::
# 172 "data/maps/Route41/scripts.pory"
	trainerbattle_single TRAINER_WENDY, Route41_Text_SwimmerfWendySeen, Route41_Text_SwimmerfWendyBeaten
# 173 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_SwimmerfWendyAfter, MSGBOX_AUTOCLOSE
# 174 "data/maps/Route41/scripts.pory"
	end
# 175 "data/maps/Route41/scripts.pory"

# 176 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfWendySeen:
# 177 "data/maps/Route41/scripts.pory"
	.string "At night, Staryu gather near\n"
# 178 "data/maps/Route41/scripts.pory"
	.string "the water's surface.$"
# 179 "data/maps/Route41/scripts.pory"

# 180 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfWendyBeaten:
# 181 "data/maps/Route41/scripts.pory"
	.string "Oh, dear…$"
# 182 "data/maps/Route41/scripts.pory"

# 183 "data/maps/Route41/scripts.pory"
Route41_Text_SwimmerfWendyAfter:
# 184 "data/maps/Route41/scripts.pory"
	.string "The clusters of Staryu light up\n"
# 185 "data/maps/Route41/scripts.pory"
	.string "at the same time.\p"
# 186 "data/maps/Route41/scripts.pory"
	.string "It's so beautiful, it's scary.$"
# 187 "data/maps/Route41/scripts.pory"

# 188 "data/maps/Route41/scripts.pory"
Route41_EventScript_Tentacruel1::
# 189 "data/maps/Route41/scripts.pory"
	lock
# 190 "data/maps/Route41/scripts.pory"
	faceplayer
# 191 "data/maps/Route41/scripts.pory"
	waitse
# 192 "data/maps/Route41/scripts.pory"
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
# 193 "data/maps/Route41/scripts.pory"
	goto_if_ge VAR_TEMP_0, 2, Route41_EventScript_TentacruelAttack1
# 194 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
# 195 "data/maps/Route41/scripts.pory"
	waitmoncry
# 196 "data/maps/Route41/scripts.pory"
	addvar VAR_TEMP_0, 1
# 197 "data/maps/Route41/scripts.pory"
	release
# 198 "data/maps/Route41/scripts.pory"
	end
# 199 "data/maps/Route41/scripts.pory"
Route41_EventScript_TentacruelAttack1::
# 200 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
# 201 "data/maps/Route41/scripts.pory"
	waitmessage
# 202 "data/maps/Route41/scripts.pory"
	setflag FLAG_SYS_NO_CATCHING
# 203 "data/maps/Route41/scripts.pory"
	setflag FLAG_GARBAGEFLAG
# 204 "data/maps/Route41/scripts.pory"
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
# 205 "data/maps/Route41/scripts.pory"
	dowildbattle
# 206 "data/maps/Route41/scripts.pory"
	closemessage
# 207 "data/maps/Route41/scripts.pory"
	clearflag FLAG_SYS_NO_CATCHING
# 208 "data/maps/Route41/scripts.pory"
	clearflag FLAG_GARBAGEFLAG
# 209 "data/maps/Route41/scripts.pory"
	playse SE_USE_ITEM
# 210 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
# 211 "data/maps/Route41/scripts.pory"
	setvar VAR_TEMP_0, 0
# 212 "data/maps/Route41/scripts.pory"
	closemessage
# 213 "data/maps/Route41/scripts.pory"
	release
# 214 "data/maps/Route41/scripts.pory"
	end
# 215 "data/maps/Route41/scripts.pory"

# 216 "data/maps/Route41/scripts.pory"
Route41_EventScript_Tentacruel2::
# 217 "data/maps/Route41/scripts.pory"
	lock
# 218 "data/maps/Route41/scripts.pory"
	faceplayer
# 219 "data/maps/Route41/scripts.pory"
	waitse
# 220 "data/maps/Route41/scripts.pory"
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
# 221 "data/maps/Route41/scripts.pory"
	goto_if_ge VAR_TEMP_1, 2, Route41_EventScript_TentacruelAttack2
# 222 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
# 223 "data/maps/Route41/scripts.pory"
	waitmoncry
# 224 "data/maps/Route41/scripts.pory"
	addvar VAR_TEMP_1, 1
# 225 "data/maps/Route41/scripts.pory"
	release
# 226 "data/maps/Route41/scripts.pory"
	end
# 227 "data/maps/Route41/scripts.pory"
Route41_EventScript_TentacruelAttack2::
# 228 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
# 229 "data/maps/Route41/scripts.pory"
	waitmessage
# 230 "data/maps/Route41/scripts.pory"
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
# 231 "data/maps/Route41/scripts.pory"
	dowildbattle
# 232 "data/maps/Route41/scripts.pory"
	closemessage
# 233 "data/maps/Route41/scripts.pory"
	playse SE_USE_ITEM
# 234 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
# 235 "data/maps/Route41/scripts.pory"
	setvar VAR_TEMP_1, 0
# 236 "data/maps/Route41/scripts.pory"
	closemessage
# 237 "data/maps/Route41/scripts.pory"
	release
# 238 "data/maps/Route41/scripts.pory"
	end
# 239 "data/maps/Route41/scripts.pory"

# 240 "data/maps/Route41/scripts.pory"
Route41_EventScript_Tentacruel3::
# 241 "data/maps/Route41/scripts.pory"
	lock
# 242 "data/maps/Route41/scripts.pory"
	faceplayer
# 243 "data/maps/Route41/scripts.pory"
	waitse
# 244 "data/maps/Route41/scripts.pory"
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
# 245 "data/maps/Route41/scripts.pory"
	goto_if_ge VAR_TEMP_2, 2, Route41_EventScript_TentacruelAttack3
# 246 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
# 247 "data/maps/Route41/scripts.pory"
	waitmoncry
# 248 "data/maps/Route41/scripts.pory"
	addvar VAR_TEMP_2, 1
# 249 "data/maps/Route41/scripts.pory"
	release
# 250 "data/maps/Route41/scripts.pory"
	end
# 251 "data/maps/Route41/scripts.pory"
Route41_EventScript_TentacruelAttack3::
# 252 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
# 253 "data/maps/Route41/scripts.pory"
	waitmessage
# 254 "data/maps/Route41/scripts.pory"
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
# 255 "data/maps/Route41/scripts.pory"
	dowildbattle
# 256 "data/maps/Route41/scripts.pory"
	closemessage
# 257 "data/maps/Route41/scripts.pory"
	playse SE_USE_ITEM
# 258 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
# 259 "data/maps/Route41/scripts.pory"
	setvar VAR_TEMP_2, 0
# 260 "data/maps/Route41/scripts.pory"
	closemessage
# 261 "data/maps/Route41/scripts.pory"
	release
# 262 "data/maps/Route41/scripts.pory"
	end
# 263 "data/maps/Route41/scripts.pory"

# 264 "data/maps/Route41/scripts.pory"
Route41_EventScript_Tentacruel4::
# 265 "data/maps/Route41/scripts.pory"
	lock
# 266 "data/maps/Route41/scripts.pory"
	faceplayer
# 267 "data/maps/Route41/scripts.pory"
	waitse
# 268 "data/maps/Route41/scripts.pory"
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
# 269 "data/maps/Route41/scripts.pory"
	goto_if_ge VAR_TEMP_3, 2, Route41_EventScript_TentacruelAttack4
# 270 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
# 271 "data/maps/Route41/scripts.pory"
	waitmoncry
# 272 "data/maps/Route41/scripts.pory"
	addvar VAR_TEMP_3, 1
# 273 "data/maps/Route41/scripts.pory"
	release
# 274 "data/maps/Route41/scripts.pory"
	end
# 275 "data/maps/Route41/scripts.pory"
Route41_EventScript_TentacruelAttack4::
# 276 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
# 277 "data/maps/Route41/scripts.pory"
	waitmessage
# 278 "data/maps/Route41/scripts.pory"
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
# 279 "data/maps/Route41/scripts.pory"
	dowildbattle
# 280 "data/maps/Route41/scripts.pory"
	closemessage
# 281 "data/maps/Route41/scripts.pory"
	playse SE_USE_ITEM
# 282 "data/maps/Route41/scripts.pory"
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
# 283 "data/maps/Route41/scripts.pory"
	setvar VAR_TEMP_3, 0
# 284 "data/maps/Route41/scripts.pory"
	closemessage
# 285 "data/maps/Route41/scripts.pory"
	release
# 286 "data/maps/Route41/scripts.pory"
	end
# 287 "data/maps/Route41/scripts.pory"

# 288 "data/maps/Route41/scripts.pory"
Route41_Text_Tentacruel:
# 289 "data/maps/Route41/scripts.pory"
	.string "Tentacruel: Cruooo...$"
# 290 "data/maps/Route41/scripts.pory"

# 291 "data/maps/Route41/scripts.pory"
Route41_Text_TentacruelAttack:
# 292 "data/maps/Route41/scripts.pory"
	.string "Tentacruel: Cruoooooo!$"
# 293 "data/maps/Route41/scripts.pory"

# 294 "data/maps/Route41/scripts.pory"
Route41_Text_TentacruelHeal:
# 295 "data/maps/Route41/scripts.pory"
	.string "The Tentacruel used Recover!\n"
# 296 "data/maps/Route41/scripts.pory"
	.string "It is fully healed!$"

GuardingDewgong::
# 300 "data/maps/Route41/scripts.pory"
	lock
# 301 "data/maps/Route41/scripts.pory"
	faceplayer
# 302 "data/maps/Route41/scripts.pory"
	playmoncry SPECIES_DEWGONG, CRY_MODE_NORMAL
# 303 "data/maps/Route41/scripts.pory"
	msgbox GuardingDewgong_Text_0
# 304 "data/maps/Route41/scripts.pory"
	waitmoncry
	checkitem ITEM_SILVER_WING
# 0 "data/maps/Route41/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq GuardingDewgong_2
GuardingDewgong_1:
# 320 "data/maps/Route41/scripts.pory"
	release
	end

GuardingDewgong_2:
	checkitem ITEM_TIDAL_BELL
# 0 "data/maps/Route41/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq GuardingDewgong_4
	goto GuardingDewgong_1

GuardingDewgong_4:
# 307 "data/maps/Route41/scripts.pory"
	msgbox GuardingDewgong_Text_1
	goto GuardingDewgong_1


GuardingDewgong_Text_0:
# 303 "data/maps/Route41/scripts.pory"
	.string "Dewgong: Gong gong!$"

GuardingDewgong_Text_1:
# 307 "data/maps/Route41/scripts.pory"
	.string "You recall the Radio Tower\n"
	.string "Director's words...\p"
	.string "“The legendary Pokémon will not\n"
	.string "appear if you just go to the place\l"
	.string "I mentioned.\p"
	.string "Apparently there is something else\n"
	.string "you need...”\p"
	.string "Perhaps you should return here later.$"
