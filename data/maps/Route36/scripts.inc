# 1 "data/maps/Route36/scripts.pory"

# 2 "data/maps/Route36/scripts.pory"
.set LOCALID_ROUTE36_SUDOWOODO, 6
# 3 "data/maps/Route36/scripts.pory"
.set LOCALID_ROUTE36_ROCKSMASHGUY, 3
# 4 "data/maps/Route36/scripts.pory"
.set LOCALID_ROUTE36_SUDOWOODO_HINT_LADY, 18
# 5 "data/maps/Route36/scripts.pory"

# 6 "data/maps/Route36/scripts.pory"
Route36_MapScripts::
# 7 "data/maps/Route36/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route36_OnTransition
# 8 "data/maps/Route36/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 9 "data/maps/Route36/scripts.pory"
	.byte 0
# 10 "data/maps/Route36/scripts.pory"

# 11 "data/maps/Route36/scripts.pory"
Route36_OnTransition: 
# 12 "data/maps/Route36/scripts.pory"
	callnative SetTimeBasedEncounters
# 13 "data/maps/Route36/scripts.pory"
	end
# 14 "data/maps/Route36/scripts.pory"

# 15 "data/maps/Route36/scripts.pory"
Route36_EventScript_RockSmashGuy::
# 16 "data/maps/Route36/scripts.pory"
	lock
# 17 "data/maps/Route36/scripts.pory"
	faceplayer
# 18 "data/maps/Route36/scripts.pory"
	goto_if_set FLAG_HIDE_SUDOWOODO, Route36_EventScript_RockSmashGuy2
# 19 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_RockSmashGuy1, MSGBOX_DEFAULT
# 20 "data/maps/Route36/scripts.pory"
	closemessage
# 21 "data/maps/Route36/scripts.pory"
	release
# 22 "data/maps/Route36/scripts.pory"
	end
# 23 "data/maps/Route36/scripts.pory"
Route36_EventScript_RockSmashGuy2::
# 24 "data/maps/Route36/scripts.pory"
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, Route36_EventScript_RockSmashGuy3
# 25 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_RockSmashGuy2, MSGBOX_DEFAULT
# 26 "data/maps/Route36/scripts.pory"
	giveitem ITEM_HM_ROCK_SMASH
# 27 "data/maps/Route36/scripts.pory"
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
# 28 "data/maps/Route36/scripts.pory"
Route36_EventScript_RockSmashGuy3::
# 29 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_RockSmashGuy3
# 30 "data/maps/Route36/scripts.pory"
	closemessage
# 31 "data/maps/Route36/scripts.pory"
	release
# 32 "data/maps/Route36/scripts.pory"
	end
# 33 "data/maps/Route36/scripts.pory"

# 34 "data/maps/Route36/scripts.pory"
Route36_EventScript_Lass::
# 35 "data/maps/Route36/scripts.pory"
	lock
# 36 "data/maps/Route36/scripts.pory"
	faceplayer
# 37 "data/maps/Route36/scripts.pory"
	goto_if_set FLAG_HIDE_SUDOWOODO, Route36_EventScript_Lass2
# 38 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_Lass1, MSGBOX_DEFAULT
# 39 "data/maps/Route36/scripts.pory"
	closemessage
# 40 "data/maps/Route36/scripts.pory"
	release
# 41 "data/maps/Route36/scripts.pory"
	end
# 42 "data/maps/Route36/scripts.pory"
Route36_EventScript_Lass2::
# 43 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_Lass2_ClearedSudowoodo, MSGBOX_DEFAULT
# 44 "data/maps/Route36/scripts.pory"
	closemessage
# 45 "data/maps/Route36/scripts.pory"
	release
# 46 "data/maps/Route36/scripts.pory"
	end
# 47 "data/maps/Route36/scripts.pory"

# 48 "data/maps/Route36/scripts.pory"
Route36_EventScript_Arthur::
# 49 "data/maps/Route36/scripts.pory"
	lock
# 50 "data/maps/Route36/scripts.pory"
	faceplayer
# 51 "data/maps/Route36/scripts.pory"
	goto_if_set FLAG_GOT_HARD_STONE, Route36_EventScript_ArthurCompleted
# 52 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_MeetArthur, MSGBOX_DEFAULT
# 53 "data/maps/Route36/scripts.pory"
	closemessage
# 54 "data/maps/Route36/scripts.pory"
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
# 55 "data/maps/Route36/scripts.pory"
	switch VAR_RESULT
# 56 "data/maps/Route36/scripts.pory"
	case 0, Route36_EventScript_ArthurNope
# 57 "data/maps/Route36/scripts.pory"
	case 1, Route36_EventScript_ArthurNope
# 58 "data/maps/Route36/scripts.pory"
	case 2, Route36_EventScript_ArthurNope
# 59 "data/maps/Route36/scripts.pory"
	case 3, Route36_EventScript_ArthurNope
# 60 "data/maps/Route36/scripts.pory"
	case 4, Route36_EventScript_ArthurYes
# 61 "data/maps/Route36/scripts.pory"
	case 5, Route36_EventScript_ArthurNope
# 62 "data/maps/Route36/scripts.pory"
	case 6, Route36_EventScript_ArthurNope
# 63 "data/maps/Route36/scripts.pory"
	case 7, Route36_EventScript_ArthurCancel
# 64 "data/maps/Route36/scripts.pory"
	case MULTI_B_PRESSED, Route36_EventScript_ArthurCancel
# 65 "data/maps/Route36/scripts.pory"
	closemessage
# 66 "data/maps/Route36/scripts.pory"
	release
# 67 "data/maps/Route36/scripts.pory"
	end
# 68 "data/maps/Route36/scripts.pory"
Route36_EventScript_ArthurYes::
# 69 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_ArthurGivesGift, MSGBOX_DEFAULT
# 70 "data/maps/Route36/scripts.pory"
	giveitem ITEM_HARD_STONE
# 71 "data/maps/Route36/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 72 "data/maps/Route36/scripts.pory"
	setflag FLAG_GOT_HARD_STONE
# 73 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_ArthurGaveGift, MSGBOX_DEFAULT
# 74 "data/maps/Route36/scripts.pory"
	closemessage
# 75 "data/maps/Route36/scripts.pory"
	release
# 76 "data/maps/Route36/scripts.pory"
	end
# 77 "data/maps/Route36/scripts.pory"
Route36_EventScript_ArthurNope::
# 78 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_ArthurNope, MSGBOX_DEFAULT
# 79 "data/maps/Route36/scripts.pory"
	closemessage
# 80 "data/maps/Route36/scripts.pory"
	release
# 81 "data/maps/Route36/scripts.pory"
	end
# 82 "data/maps/Route36/scripts.pory"
Route36_EventScript_ArthurCancel::
# 83 "data/maps/Route36/scripts.pory"
	closemessage
# 84 "data/maps/Route36/scripts.pory"
	release
# 85 "data/maps/Route36/scripts.pory"
	end
# 86 "data/maps/Route36/scripts.pory"
Route36_EventScript_ArthurCompleted::
# 87 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_ArthurThursday, MSGBOX_DEFAULT
# 88 "data/maps/Route36/scripts.pory"
	closemessage
# 89 "data/maps/Route36/scripts.pory"
	release
# 90 "data/maps/Route36/scripts.pory"
	end
# 91 "data/maps/Route36/scripts.pory"

# 92 "data/maps/Route36/scripts.pory"

# 93 "data/maps/Route36/scripts.pory"
Route36_EventScript_SudoWoodo::
# 94 "data/maps/Route36/scripts.pory"
	lock
# 95 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_OddTree, MSGBOX_DEFAULT
# 96 "data/maps/Route36/scripts.pory"
	checkitem ITEM_SQUIRTBOTTLE
# 97 "data/maps/Route36/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route36_EventScript_SudoWoodoChoice
# 98 "data/maps/Route36/scripts.pory"
	closemessage
# 99 "data/maps/Route36/scripts.pory"
	release
# 100 "data/maps/Route36/scripts.pory"
	end
# 101 "data/maps/Route36/scripts.pory"
Route36_EventScript_SudoWoodoChoice::
# 102 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_UseSquirtbottle, MSGBOX_YESNO
# 103 "data/maps/Route36/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route36_EventScript_SudoWoodoWater
# 104 "data/maps/Route36/scripts.pory"
	closemessage
# 105 "data/maps/Route36/scripts.pory"
	release
# 106 "data/maps/Route36/scripts.pory"
	end
# 107 "data/maps/Route36/scripts.pory"
Route36_EventScript_SudoWoodoWater::
# 108 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_UsedSquirtbottle, MSGBOX_DEFAULT
# 109 "data/maps/Route36/scripts.pory"
	playse SE_DOWNPOUR
# 110 "data/maps/Route36/scripts.pory"
	waitse
# 111 "data/maps/Route36/scripts.pory"
	closemessage
# 112 "data/maps/Route36/scripts.pory"
	playse SE_SUDOWOODO_SHAKE	
# 113 "data/maps/Route36/scripts.pory"
	applymovement LOCALID_ROUTE36_SUDOWOODO, Route36_Movement_SudoWoodo
# 114 "data/maps/Route36/scripts.pory"
	waitmovement 0
# 115 "data/maps/Route36/scripts.pory"
	faceplayer
# 116 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_SudowoodoAttacked	
# 117 "data/maps/Route36/scripts.pory"
	closemessage
# 118 "data/maps/Route36/scripts.pory"
	waitse
# 119 "data/maps/Route36/scripts.pory"
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
# 120 "data/maps/Route36/scripts.pory"
	delay 40
# 121 "data/maps/Route36/scripts.pory"
	waitmoncry
# 122 "data/maps/Route36/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_ROUTE36_SUDOWOODO
# 123 "data/maps/Route36/scripts.pory"
	setwildbattle SPECIES_SUDOWOODO, 30
# 124 "data/maps/Route36/scripts.pory"
	@setflag FLAG_GARBAGEFLAG
# 125 "data/maps/Route36/scripts.pory"
	dowildbattle
# 126 "data/maps/Route36/scripts.pory"
	@clearflag FLAG_GARBAGEFLAG
# 127 "data/maps/Route36/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 128 "data/maps/Route36/scripts.pory"
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route36_EventScript_Defeated_Sudowoodo
# 129 "data/maps/Route36/scripts.pory"
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route36_EventScript_RanSudowoodo
# 130 "data/maps/Route36/scripts.pory"
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route36_EventScript_RanSudowoodo
# 131 "data/maps/Route36/scripts.pory"
Route36_EventScript_Defeated_Sudowoodo::
# 132 "data/maps/Route36/scripts.pory"
	setflag FLAG_HIDE_SUDOWOODO
# 133 "data/maps/Route36/scripts.pory"
	removeobject LOCALID_ROUTE36_SUDOWOODO
# 134 "data/maps/Route36/scripts.pory"
	removeobject LOCALID_ROUTE36_SUDOWOODO_HINT_LADY
# 135 "data/maps/Route36/scripts.pory"
	setflag FLAG_TRAINER_LEVELSCALING
# 136 "data/maps/Route36/scripts.pory"
	setflag FLAG_WILD_LEVELSCALING
# 137 "data/maps/Route36/scripts.pory"
	setflag FLAG_LEVEL_SCALING_ON
# 138 "data/maps/Route36/scripts.pory"
	checkitem ITEM_HM_ROCK_SMASH
# 139 "data/maps/Route36/scripts.pory"
	call_if_eq VAR_RESULT, FALSE, Route36_EventScript_RockSmashGuySudoWoodo
# 140 "data/maps/Route36/scripts.pory"
	release
# 141 "data/maps/Route36/scripts.pory"
	end
# 142 "data/maps/Route36/scripts.pory"

# 143 "data/maps/Route36/scripts.pory"
Route36_EventScript_RanSudowoodo::
# 144 "data/maps/Route36/scripts.pory"
	turnobject LOCALID_ROUTE36_SUDOWOODO, DIR_NORTH
# 145 "data/maps/Route36/scripts.pory"
	release
# 146 "data/maps/Route36/scripts.pory"
	end
# 147 "data/maps/Route36/scripts.pory"

# 148 "data/maps/Route36/scripts.pory"
Route36_EventScript_RockSmashGuySudoWoodo:
# 149 "data/maps/Route36/scripts.pory"
	playse SE_PIN
# 150 "data/maps/Route36/scripts.pory"
	applymovement LOCALID_ROUTE36_ROCKSMASHGUY, Common_Movement_ExclamationMark
# 151 "data/maps/Route36/scripts.pory"
	turnobject LOCALID_ROUTE36_ROCKSMASHGUY, DIR_WEST
# 152 "data/maps/Route36/scripts.pory"
	waitmovement 0
# 153 "data/maps/Route36/scripts.pory"
	applymovement LOCALID_ROUTE36_ROCKSMASHGUY, Route36_Movement_RockSmashGuy
# 154 "data/maps/Route36/scripts.pory"
	playse SE_LEDGE
# 155 "data/maps/Route36/scripts.pory"
	waitse
# 156 "data/maps/Route36/scripts.pory"
	playse SE_LEDGE
# 157 "data/maps/Route36/scripts.pory"
	waitse
# 158 "data/maps/Route36/scripts.pory"
	playse SE_LEDGE
# 159 "data/maps/Route36/scripts.pory"
	waitse
# 160 "data/maps/Route36/scripts.pory"
	playse SE_LEDGE
# 161 "data/maps/Route36/scripts.pory"
	waitmovement 0
# 162 "data/maps/Route36/scripts.pory"
	return
# 163 "data/maps/Route36/scripts.pory"

# 164 "data/maps/Route36/scripts.pory"
Route36_Movement_RockSmashGuy:
# 165 "data/maps/Route36/scripts.pory"
	jump_in_place_left
# 166 "data/maps/Route36/scripts.pory"
	delay_2
# 167 "data/maps/Route36/scripts.pory"
	jump_in_place_left
# 168 "data/maps/Route36/scripts.pory"
	delay_2
# 169 "data/maps/Route36/scripts.pory"
	jump_in_place_left
# 170 "data/maps/Route36/scripts.pory"
	delay_2
# 171 "data/maps/Route36/scripts.pory"
	jump_in_place_left
# 172 "data/maps/Route36/scripts.pory"
	step_end
# 173 "data/maps/Route36/scripts.pory"

# 174 "data/maps/Route36/scripts.pory"
Route36_EventScript_Mark::
# 175 "data/maps/Route36/scripts.pory"
	trainerbattle_single TRAINER_MARK Route36_Text_PsychicMarkSeen, Route36_Text_PsychicMarkBeaten
# 176 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_PsychicMarkAfter, MSGBOX_AUTOCLOSE
# 177 "data/maps/Route36/scripts.pory"
	end
# 178 "data/maps/Route36/scripts.pory"

# 179 "data/maps/Route36/scripts.pory"
Route36_EventScript_Schoolboy::
# 180 "data/maps/Route36/scripts.pory"
	trainerbattle_single TRAINER_ALAN Route36_Text_SchoolboyAlan1Seen, Route36_Text_SchoolboyAlan1Beaten
# 181 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_SchoolboyAlanAfter, MSGBOX_AUTOCLOSE
# 182 "data/maps/Route36/scripts.pory"
	end
# 183 "data/maps/Route36/scripts.pory"

# 184 "data/maps/Route36/scripts.pory"
Route36_EventScript_Sign::
# 185 "data/maps/Route36/scripts.pory"
	lock
# 186 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_Sign_RuinsNorth, MSGBOX_SIGN
# 187 "data/maps/Route36/scripts.pory"
	closemessage
# 188 "data/maps/Route36/scripts.pory"
	release
# 189 "data/maps/Route36/scripts.pory"
	end
# 190 "data/maps/Route36/scripts.pory"

# 191 "data/maps/Route36/scripts.pory"
Route36_EventScript_Sign2::
# 192 "data/maps/Route36/scripts.pory"
	lock
# 193 "data/maps/Route36/scripts.pory"
	msgbox Route36_Text_Tips1, MSGBOX_SIGN
# 194 "data/maps/Route36/scripts.pory"
	closemessage
# 195 "data/maps/Route36/scripts.pory"
	release
# 196 "data/maps/Route36/scripts.pory"
	end
# 197 "data/maps/Route36/scripts.pory"

# 198 "data/maps/Route36/scripts.pory"
Route36_Movement_SudoWoodo:
# 199 "data/maps/Route36/scripts.pory"
	face_right
# 200 "data/maps/Route36/scripts.pory"
	delay_8
# 201 "data/maps/Route36/scripts.pory"
	face_down
# 202 "data/maps/Route36/scripts.pory"
	delay_8
# 203 "data/maps/Route36/scripts.pory"
	face_left
# 204 "data/maps/Route36/scripts.pory"
	delay_8
# 205 "data/maps/Route36/scripts.pory"
	face_down
# 206 "data/maps/Route36/scripts.pory"
	delay_8
# 207 "data/maps/Route36/scripts.pory"
	face_right
# 208 "data/maps/Route36/scripts.pory"
	delay_8
# 209 "data/maps/Route36/scripts.pory"
	face_down
# 210 "data/maps/Route36/scripts.pory"
	delay_8
# 211 "data/maps/Route36/scripts.pory"
	face_left
# 212 "data/maps/Route36/scripts.pory"
	delay_8
# 213 "data/maps/Route36/scripts.pory"
	face_down
# 214 "data/maps/Route36/scripts.pory"
	step_end
# 215 "data/maps/Route36/scripts.pory"

# 216 "data/maps/Route36/scripts.pory"
Route36_Text_UseSquirtbottle:
# 217 "data/maps/Route36/scripts.pory"
	.string "Use Squirtbottle?$"
# 218 "data/maps/Route36/scripts.pory"

# 219 "data/maps/Route36/scripts.pory"
Route36_Text_UsedSquirtbottle:
# 220 "data/maps/Route36/scripts.pory"
	.string "{PLAYER} used the Squirtbottle.$"
# 221 "data/maps/Route36/scripts.pory"

# 222 "data/maps/Route36/scripts.pory"
Route36_Text_SudowoodoAttacked:
# 223 "data/maps/Route36/scripts.pory"
	.string "The weird tree doesn't like the\n"
# 224 "data/maps/Route36/scripts.pory"
	.string "Squirtbottle!\p"
# 225 "data/maps/Route36/scripts.pory"
	.string "The weird tree attacked!$"
# 226 "data/maps/Route36/scripts.pory"

# 227 "data/maps/Route36/scripts.pory"
Route36_Text_RockSmashGuy1:
# 228 "data/maps/Route36/scripts.pory"
	.string "Wa-hey!\p"
# 229 "data/maps/Route36/scripts.pory"
	.string "I was going to snap that tree\n"
# 230 "data/maps/Route36/scripts.pory"
	.string "with my straight-arm punch.\p"
# 231 "data/maps/Route36/scripts.pory"
	.string "But I couldn't! I'm a failure!$"
# 232 "data/maps/Route36/scripts.pory"

# 233 "data/maps/Route36/scripts.pory"
Route36_Text_RockSmashGuy2:
# 234 "data/maps/Route36/scripts.pory"
	.string "Did you clear that wretched tree?\p"
# 235 "data/maps/Route36/scripts.pory"
	.string "I'm impressed!\n"
# 236 "data/maps/Route36/scripts.pory"
	.string "I want you to have this.$"
# 237 "data/maps/Route36/scripts.pory"

# 238 "data/maps/Route36/scripts.pory"
Route36_Text_RockSmashGuy3:
# 239 "data/maps/Route36/scripts.pory"
	.string "That happens to be Rock Smash.\p"
# 240 "data/maps/Route36/scripts.pory"
	.string "You can shatter rocks with just a\n"
# 241 "data/maps/Route36/scripts.pory"
	.string "single well-aimed smack.\p"
# 242 "data/maps/Route36/scripts.pory"
	.string "If any rocks are in your way,\n"
# 243 "data/maps/Route36/scripts.pory"
	.string "just smash 'em up!$"
# 244 "data/maps/Route36/scripts.pory"

# 245 "data/maps/Route36/scripts.pory"
Route36_Text_OddTree:
# 246 "data/maps/Route36/scripts.pory"
	.string "A weird tree is blocking the way.$"
# 247 "data/maps/Route36/scripts.pory"

# 248 "data/maps/Route36/scripts.pory"
Route36_Text_Lass1:
# 249 "data/maps/Route36/scripts.pory"
	.string "Be careful at night on this route!\p"
# 250 "data/maps/Route36/scripts.pory"
	.string "I saw a Pokémon that looked like\n"
# 251 "data/maps/Route36/scripts.pory"
	.string "Growlithe, but it had a scary aura\l"
# 252 "data/maps/Route36/scripts.pory"
	.string "to it.$"
# 253 "data/maps/Route36/scripts.pory"

# 254 "data/maps/Route36/scripts.pory"
Route36_Text_Lass2_ClearedSudowoodo:
# 255 "data/maps/Route36/scripts.pory"
	.string "That odd tree disappeared without\n"
# 256 "data/maps/Route36/scripts.pory"
	.string "a trace.\p"
# 257 "data/maps/Route36/scripts.pory"
	.string "Oh! That tree was really a\n"
# 258 "data/maps/Route36/scripts.pory"
	.string "Pokémon?$"
# 259 "data/maps/Route36/scripts.pory"

# 260 "data/maps/Route36/scripts.pory"
Route36_Text_PsychicMarkSeen:
# 261 "data/maps/Route36/scripts.pory"
	.string "I'm going to read your thoughts!$"
# 262 "data/maps/Route36/scripts.pory"

# 263 "data/maps/Route36/scripts.pory"
Route36_Text_PsychicMarkBeaten:
# 264 "data/maps/Route36/scripts.pory"
	.string "I misread you!$"
# 265 "data/maps/Route36/scripts.pory"

# 266 "data/maps/Route36/scripts.pory"
Route36_Text_PsychicMarkAfter:
# 267 "data/maps/Route36/scripts.pory"
	.string "I'd be strong if only I could tell\n"
# 268 "data/maps/Route36/scripts.pory"
	.string "what my opponent was thinking.$"
# 269 "data/maps/Route36/scripts.pory"

# 270 "data/maps/Route36/scripts.pory"
Route36_Text_SchoolboyAlan1Seen:
# 271 "data/maps/Route36/scripts.pory"
	.string "Thanks to my studies, I'm ready\n"
# 272 "data/maps/Route36/scripts.pory"
	.string "for any Pokémon!$"
# 273 "data/maps/Route36/scripts.pory"

# 274 "data/maps/Route36/scripts.pory"
Route36_Text_SchoolboyAlan1Beaten:
# 275 "data/maps/Route36/scripts.pory"
	.string "Oops! Computation error?$"
# 276 "data/maps/Route36/scripts.pory"

# 277 "data/maps/Route36/scripts.pory"
Route36_Text_SchoolboyAlanAfter:
# 278 "data/maps/Route36/scripts.pory"
	.string "Darn. I study five hours a day too.\p"
# 279 "data/maps/Route36/scripts.pory"
	.string "There's more to learning than just\n"
# 280 "data/maps/Route36/scripts.pory"
	.string "reading books.$"
# 281 "data/maps/Route36/scripts.pory"

# 282 "data/maps/Route36/scripts.pory"
Route36_Text_MeetArthur:
# 283 "data/maps/Route36/scripts.pory"
	.string "Arthur: Who are you?\n"
# 284 "data/maps/Route36/scripts.pory"
	.string "I'm Arthur of the Weekday Family.\p"
# 285 "data/maps/Route36/scripts.pory"
	.string "If you can guess my favorite day,\n"
# 286 "data/maps/Route36/scripts.pory"
	.string "I'll give you a reward.$"
# 287 "data/maps/Route36/scripts.pory"

# 288 "data/maps/Route36/scripts.pory"
Route36_Text_ArthurNope:
# 289 "data/maps/Route36/scripts.pory"
	.string "Not quite!$"
# 290 "data/maps/Route36/scripts.pory"

# 291 "data/maps/Route36/scripts.pory"
Route36_Text_ArthurGivesGift:
# 292 "data/maps/Route36/scripts.pory"
	.string "Here. You can have this.$"
# 293 "data/maps/Route36/scripts.pory"

# 294 "data/maps/Route36/scripts.pory"
Route36_Text_ArthurGaveGift:
# 295 "data/maps/Route36/scripts.pory"
	.string "Arthur: A Pokémon that uses rock-\n"
# 296 "data/maps/Route36/scripts.pory"
	.string "type moves should hold on to that.\p"
# 297 "data/maps/Route36/scripts.pory"
	.string "It pumps up rock-type attacks.$"
# 298 "data/maps/Route36/scripts.pory"

# 299 "data/maps/Route36/scripts.pory"
Route36_Text_ArthurThursday:
# 300 "data/maps/Route36/scripts.pory"
	.string "Arthur: I'm Arthur of Thursday.\n"
# 301 "data/maps/Route36/scripts.pory"
	.string "I'm the fifth son out of seven.$"
# 302 "data/maps/Route36/scripts.pory"

# 303 "data/maps/Route36/scripts.pory"
Route36_Text_Sign:
# 304 "data/maps/Route36/scripts.pory"
	.string "Route 36$"
# 305 "data/maps/Route36/scripts.pory"

# 306 "data/maps/Route36/scripts.pory"
Route36_Text_Sign_RuinsNorth:
# 307 "data/maps/Route36/scripts.pory"
	.string "Ruins Of Alph\n"
# 308 "data/maps/Route36/scripts.pory"
	.string "North Entrance$"
# 309 "data/maps/Route36/scripts.pory"

# 310 "data/maps/Route36/scripts.pory"
Route36_Text_Tips1:
# 311 "data/maps/Route36/scripts.pory"
	.string "Trainer Tips\n"
# 312 "data/maps/Route36/scripts.pory"
	.string "Pokémon stats vary--even within\l"
# 313 "data/maps/Route36/scripts.pory"
	.string "the same species.\p"
# 314 "data/maps/Route36/scripts.pory"
	.string "Their stats may be similar at first.\p"
# 315 "data/maps/Route36/scripts.pory"
	.string "However, differences will become\n"
# 316 "data/maps/Route36/scripts.pory"
	.string "pronounced as the Pokémon grow.$"
# 317 "data/maps/Route36/scripts.pory"

# 318 "data/maps/Route36/scripts.pory"
Route36_Text_Tips2:
# 319 "data/maps/Route36/scripts.pory"
	.string "Trainer Tips\n"
# 320 "data/maps/Route36/scripts.pory"
	.string "Use Dig to return to the entrance of\n"
# 321 "data/maps/Route36/scripts.pory"
	.string "any place.\p"
# 322 "data/maps/Route36/scripts.pory"
	.string "It is convenient for exploring\n"
# 323 "data/maps/Route36/scripts.pory"
	.string "caves and other landmarks.$"

Route36_SudowoodoHintLady::
# 327 "data/maps/Route36/scripts.pory"
	lock
# 328 "data/maps/Route36/scripts.pory"
	faceplayer
# 329 "data/maps/Route36/scripts.pory"
	goto_if_set FLAG_IS_CHAMPION, Route36_SudowoodoHintLady_2
# 334 "data/maps/Route36/scripts.pory"
	goto_if_unset FLAG_BADGE03_GET, Route36_SudowoodoHintLady_3
# 344 "data/maps/Route36/scripts.pory"
	goto_if_unset FLAG_RECEIVED_SQUIRTBOTTLE, Route36_SudowoodoHintLady_4
# 353 "data/maps/Route36/scripts.pory"
	msgbox Route36_SudowoodoHintLady_Text_3
# 358 "data/maps/Route36/scripts.pory"
	release
	end

Route36_SudowoodoHintLady_2:
# 330 "data/maps/Route36/scripts.pory"
	msgbox Route36_SudowoodoHintLady_Text_0
# 332 "data/maps/Route36/scripts.pory"
	release
	end

Route36_SudowoodoHintLady_3:
# 335 "data/maps/Route36/scripts.pory"
	msgbox Route36_SudowoodoHintLady_Text_1
# 342 "data/maps/Route36/scripts.pory"
	release
	end

Route36_SudowoodoHintLady_4:
# 345 "data/maps/Route36/scripts.pory"
	msgbox Route36_SudowoodoHintLady_Text_2
# 350 "data/maps/Route36/scripts.pory"
	release
	end


Route36_SudowoodoHintLady_Text_0:
# 330 "data/maps/Route36/scripts.pory"
	.string "How strange... That odd tree has\n"
	.string "returned!$"

Route36_SudowoodoHintLady_Text_1:
# 335 "data/maps/Route36/scripts.pory"
	.string "That strange tree has been blocking\n"
	.string "the road for a while.\p"
	.string "It reacts strangely to water. I think\n"
	.string "my sister in Goldenrod's Flower Shop\l"
	.string "might have a solution, but you'll\l"
	.string "need the 3rd badge to convince her.$"

Route36_SudowoodoHintLady_Text_2:
# 345 "data/maps/Route36/scripts.pory"
	.string "You beat Whitney? You should go see\n"
	.string "my sister in the Goldenrod Flower Shop!\p"
	.string "She might lend you a special watering\n"
	.string "bottle!$"

Route36_SudowoodoHintLady_Text_3:
# 353 "data/maps/Route36/scripts.pory"
	.string "Oh, you have the Squirtbottle!\p"
	.string "You should try soaking the tree over\n"
	.string "there and see how it reacts!$"
