# 1 "data/maps/OlivineCity/scripts.pory"

# 2 "data/maps/OlivineCity/scripts.pory"

# 3 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScripts::
# 4 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
# 5 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 6 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_OnFrame
# 7 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, OlivineCity_OnLoad
# 8 "data/maps/OlivineCity/scripts.pory"
	.byte 0
# 9 "data/maps/OlivineCity/scripts.pory"

# 10 "data/maps/OlivineCity/scripts.pory"
OlivineCity_OnLoad::
# 11 "data/maps/OlivineCity/scripts.pory"
	setrespawn HEAL_LOCATION_OLIVINE_CITY
# 12 "data/maps/OlivineCity/scripts.pory"
	end
# 13 "data/maps/OlivineCity/scripts.pory"

# 14 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScript_OnTransition::
# 15 "data/maps/OlivineCity/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 16 "data/maps/OlivineCity/scripts.pory"
	goto OlivineCity_MapScript_CheckWeather
# 17 "data/maps/OlivineCity/scripts.pory"

# 18 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScript_CheckWeather::
# 19 "data/maps/OlivineCity/scripts.pory"
	callnative SetTimeBasedEncounters
# 20 "data/maps/OlivineCity/scripts.pory"
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
# 21 "data/maps/OlivineCity/scripts.pory"
	end
# 22 "data/maps/OlivineCity/scripts.pory"

# 23 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScript_ClearWeather::
# 24 "data/maps/OlivineCity/scripts.pory"
	setweather WEATHER_NONE
# 25 "data/maps/OlivineCity/scripts.pory"
	end
# 26 "data/maps/OlivineCity/scripts.pory"

# 27 "data/maps/OlivineCity/scripts.pory"
OlivineCity_OnFrame::
# 28 "data/maps/OlivineCity/scripts.pory"
	map_script_2 VAR_SAFARI_ZONE_GATE_STATE, 1, OlivineCity_EventScript_BaobaCall
# 29 "data/maps/OlivineCity/scripts.pory"
	.2byte 0
# 30 "data/maps/OlivineCity/scripts.pory"

# 31 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_BaobaCall::
# 32 "data/maps/OlivineCity/scripts.pory"
	lock
# 33 "data/maps/OlivineCity/scripts.pory"
	pokenavcall OlivineCity_Text_Baoba
# 34 "data/maps/OlivineCity/scripts.pory"
	waitmessage
# 35 "data/maps/OlivineCity/scripts.pory"
	delay 30
# 36 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_SAFARI_ZONE_GATE_STATE, 2
# 37 "data/maps/OlivineCity/scripts.pory"
	release
# 38 "data/maps/OlivineCity/scripts.pory"
	end
# 39 "data/maps/OlivineCity/scripts.pory"

# 40 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Baoba:
# 41 "data/maps/OlivineCity/scripts.pory"
	.string "{PLAYER}!\p"
# 42 "data/maps/OlivineCity/scripts.pory"
	.string "This is Warden Baoba.\p"
# 43 "data/maps/OlivineCity/scripts.pory"
	.string "Sorry to have kept you waiting.\n"
# 44 "data/maps/OlivineCity/scripts.pory"
	.string "We've finally opened the Safari\l"
# 45 "data/maps/OlivineCity/scripts.pory"
	.string "Zone!\p"
# 46 "data/maps/OlivineCity/scripts.pory"
	.string "Do you know where it is?\p"
# 47 "data/maps/OlivineCity/scripts.pory"
	.string "You know the Gate inside the cavern\n"
# 48 "data/maps/OlivineCity/scripts.pory"
	.string "in Cianwood City?\p"
# 49 "data/maps/OlivineCity/scripts.pory"
	.string "If you go through there and walk for\n"
# 50 "data/maps/OlivineCity/scripts.pory"
	.string "a short while, you should soon see\l"
# 51 "data/maps/OlivineCity/scripts.pory"
	.string "the Safari Zone!\p"
# 52 "data/maps/OlivineCity/scripts.pory"
	.string "We're a little out of the way, but\n"
# 53 "data/maps/OlivineCity/scripts.pory"
	.string "please come visit!$"
# 54 "data/maps/OlivineCity/scripts.pory"

# 55 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_CityTrigger:: @FLAGHEAP
# 56 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
# 57 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_OLIVINE_SILVER
# 58 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_VISITED_OLIVINE_CITY
# 59 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_BATTLEFRONTIER_ENGINEER
# 60 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_LIGHTHOUSE_JASMINE
# 61 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
# 62 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_GETFLY, 0
# 63 "data/maps/OlivineCity/scripts.pory"
	
# 64 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_OLIVINE_CITY_STATE, 1
# 65 "data/maps/OlivineCity/scripts.pory"

# 66 "data/maps/OlivineCity/scripts.pory"
	@cianwood flags
# 67 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_SUICUNE_ENCOUNTERS, 1
# 68 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_CIANWOOD_SUICUNE
# 69 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_CIANWOOD_EUSINE
# 70 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_CIANWOOD_CITY_STATE, 1
# 71 "data/maps/OlivineCity/scripts.pory"
	end
# 72 "data/maps/OlivineCity/scripts.pory"

# 73 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverTrigger::
# 74 "data/maps/OlivineCity/scripts.pory"
	lock
# 75 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_OLIVINE_SILVER
# 76 "data/maps/OlivineCity/scripts.pory"
	opendoor 11, 27
# 77 "data/maps/OlivineCity/scripts.pory"
	addobject LOCALID_OLIVINE_SILVER
# 78 "data/maps/OlivineCity/scripts.pory"
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
# 79 "data/maps/OlivineCity/scripts.pory"
	delay 20 
# 80 "data/maps/OlivineCity/scripts.pory"
	closedoor 11, 27
# 81 "data/maps/OlivineCity/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 82 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverWalkToPlayer1
# 83 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverWalkToPlayer2
# 84 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverWalkToPlayer3
# 85 "data/maps/OlivineCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 86 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_SilverEncounter, MSGBOX_DEFAULT
# 87 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 88 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverLeaveAdjust1
# 89 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverLeaveAdjust2
# 90 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverLeaveAdjust2
# 91 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER, OlivineCity_Movement_SilverLeave
# 92 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 93 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_OLIVINE_CITY_STATE, 2
# 94 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_OLIVINE_SILVER
# 95 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_MAREANIES
# 96 "data/maps/OlivineCity/scripts.pory"
	removeobject LOCALID_OLIVINE_SILVER
# 97 "data/maps/OlivineCity/scripts.pory"
	fadedefaultbgm
# 98 "data/maps/OlivineCity/scripts.pory"
	release
# 99 "data/maps/OlivineCity/scripts.pory"
	end
# 100 "data/maps/OlivineCity/scripts.pory"

# 101 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverWalkToPlayer1::
# 102 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer1
# 103 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 104 "data/maps/OlivineCity/scripts.pory"
	return
# 105 "data/maps/OlivineCity/scripts.pory"

# 106 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverWalkToPlayer2::
# 107 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer2
# 108 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 109 "data/maps/OlivineCity/scripts.pory"
	return
# 110 "data/maps/OlivineCity/scripts.pory"

# 111 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverWalkToPlayer3::
# 112 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer3
# 113 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 114 "data/maps/OlivineCity/scripts.pory"
	return
# 115 "data/maps/OlivineCity/scripts.pory"

# 116 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverLeaveAdjust1::
# 117 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkDown1
# 118 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 119 "data/maps/OlivineCity/scripts.pory"
	return
# 120 "data/maps/OlivineCity/scripts.pory"

# 121 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverLeaveAdjust2::
# 122 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkUp1
# 123 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 124 "data/maps/OlivineCity/scripts.pory"
	return
# 125 "data/maps/OlivineCity/scripts.pory"

# 126 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverWalkToPlayer1:
# 127 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 128 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 129 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 130 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 131 "data/maps/OlivineCity/scripts.pory"
	step_end
# 132 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverWalkToPlayer2:
# 133 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 134 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 135 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 136 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 137 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 138 "data/maps/OlivineCity/scripts.pory"
	step_end
# 139 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverWalkToPlayer3:
# 140 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 141 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 142 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 143 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 144 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 145 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 146 "data/maps/OlivineCity/scripts.pory"
	step_end
# 147 "data/maps/OlivineCity/scripts.pory"

# 148 "data/maps/OlivineCity/scripts.pory"

# 149 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverLeave:
# 150 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 151 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 152 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 153 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 154 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 155 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 156 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 157 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 158 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 159 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 160 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 161 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 162 "data/maps/OlivineCity/scripts.pory"
	step_end
# 163 "data/maps/OlivineCity/scripts.pory"

# 164 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_SilverEncounter:
# 165 "data/maps/OlivineCity/scripts.pory"
	.string "You again?\n"
# 166 "data/maps/OlivineCity/scripts.pory"
	.string "There's no need to be alert.\p"
# 167 "data/maps/OlivineCity/scripts.pory"
	.string "I don't bother with wimps\n"
# 168 "data/maps/OlivineCity/scripts.pory"
	.string "like you.\p"
# 169 "data/maps/OlivineCity/scripts.pory"
	.string "Speaking of weaklings, the\n"
# 170 "data/maps/OlivineCity/scripts.pory"
	.string "city's Gym Leader isn't here,\l"
# 171 "data/maps/OlivineCity/scripts.pory"
	.string "and is supposedly taking care\l"
# 172 "data/maps/OlivineCity/scripts.pory"
	.string "of a sick Pokémon at the\l"
# 173 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse.\p"
# 174 "data/maps/OlivineCity/scripts.pory"
	.string "Humph! Boo-hoo!\n"
# 175 "data/maps/OlivineCity/scripts.pory"
	.string "Just let sick Pokémon go!\p"
# 176 "data/maps/OlivineCity/scripts.pory"
	.string "A Pokémon that can't battle\n"
# 177 "data/maps/OlivineCity/scripts.pory"
	.string "is worthless!\p"
# 178 "data/maps/OlivineCity/scripts.pory"
	.string "Why don't you go train at the\n"
# 179 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse?\p"
# 180 "data/maps/OlivineCity/scripts.pory"
	.string "Who knows? It may make you a\n"
# 181 "data/maps/OlivineCity/scripts.pory"
	.string "bit of a better Trainer!$"
# 182 "data/maps/OlivineCity/scripts.pory"

# 183 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Sailor1::
# 184 "data/maps/OlivineCity/scripts.pory"
	lock
# 185 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 186 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Sailor1, MSGBOX_DEFAULT
# 187 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 188 "data/maps/OlivineCity/scripts.pory"
	release
# 189 "data/maps/OlivineCity/scripts.pory"
	end
# 190 "data/maps/OlivineCity/scripts.pory"

# 191 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Sailor2::
# 192 "data/maps/OlivineCity/scripts.pory"
	lock
# 193 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 194 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Sailor2, MSGBOX_DEFAULT
# 195 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 196 "data/maps/OlivineCity/scripts.pory"
	release
# 197 "data/maps/OlivineCity/scripts.pory"
	end
# 198 "data/maps/OlivineCity/scripts.pory"

# 199 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Youngster::
# 200 "data/maps/OlivineCity/scripts.pory"
	lock
# 201 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 202 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_YoungsterPokegear, MSGBOX_DEFAULT
# 203 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 204 "data/maps/OlivineCity/scripts.pory"
	release
# 205 "data/maps/OlivineCity/scripts.pory"
	end
# 206 "data/maps/OlivineCity/scripts.pory"

# 207 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Machoke::
# 208 "data/maps/OlivineCity/scripts.pory"
	lock
# 209 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 210 "data/maps/OlivineCity/scripts.pory"
	waitse
# 211 "data/maps/OlivineCity/scripts.pory"
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
# 212 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Machoke, MSGBOX_DEFAULT
# 213 "data/maps/OlivineCity/scripts.pory"
	waitmoncry
# 214 "data/maps/OlivineCity/scripts.pory"
	release
# 215 "data/maps/OlivineCity/scripts.pory"
	end
# 216 "data/maps/OlivineCity/scripts.pory"

# 217 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Sign::
# 218 "data/maps/OlivineCity/scripts.pory"
	lock
# 219 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Sign, MSGBOX_SIGN
# 220 "data/maps/OlivineCity/scripts.pory"
	end
# 221 "data/maps/OlivineCity/scripts.pory"

# 222 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_PortSign::
# 223 "data/maps/OlivineCity/scripts.pory"
	lock
# 224 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_PortSign, MSGBOX_SIGN
# 225 "data/maps/OlivineCity/scripts.pory"
	end
# 226 "data/maps/OlivineCity/scripts.pory"

# 227 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_CafeSign::
# 228 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_CafeSign, MSGBOX_SIGN
# 229 "data/maps/OlivineCity/scripts.pory"
	end
# 230 "data/maps/OlivineCity/scripts.pory"

# 231 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_GymSign::
# 232 "data/maps/OlivineCity/scripts.pory"
	lock
# 233 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_GymSign, MSGBOX_SIGN
# 234 "data/maps/OlivineCity/scripts.pory"
	end
# 235 "data/maps/OlivineCity/scripts.pory"

# 236 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_LighthouseSign::
# 237 "data/maps/OlivineCity/scripts.pory"
	lock
# 238 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_LighthouseSign, MSGBOX_SIGN
# 239 "data/maps/OlivineCity/scripts.pory"
	end
# 240 "data/maps/OlivineCity/scripts.pory"

# 241 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_EonTicketWoman::
# 242 "data/maps/OlivineCity/scripts.pory"
	lock
# 243 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 244 "data/maps/OlivineCity/scripts.pory"
	checkitem ITEM_AURORA_TICKET
# 245 "data/maps/OlivineCity/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_EventScript_EonTicketWomanAfter
# 246 "data/maps/OlivineCity/scripts.pory"
	goto_if_set FLAG_IS_KANTO_CHAMPION, OlivineCity_EventScript_EonTicketWomanChamp
# 247 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_EonTicketWoman1, MSGBOX_DEFAULT
# 248 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 249 "data/maps/OlivineCity/scripts.pory"
	release
# 250 "data/maps/OlivineCity/scripts.pory"
	end
# 251 "data/maps/OlivineCity/scripts.pory"

# 252 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_EonTicketWomanChamp::
# 253 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_EonTicketWoman2, MSGBOX_DEFAULT
# 254 "data/maps/OlivineCity/scripts.pory"
	giveitem ITEM_AURORA_TICKET
# 255 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 256 "data/maps/OlivineCity/scripts.pory"
	release
# 257 "data/maps/OlivineCity/scripts.pory"
	end
# 258 "data/maps/OlivineCity/scripts.pory"

# 259 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_EonTicketWomanAfter::
# 260 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_EonTicketWoman3, MSGBOX_DEFAULT
# 261 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 262 "data/maps/OlivineCity/scripts.pory"
	release
# 263 "data/maps/OlivineCity/scripts.pory"
	end
# 264 "data/maps/OlivineCity/scripts.pory"

# 265 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_CafeSign:
# 266 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine Cafe\n"
# 267 "data/maps/OlivineCity/scripts.pory"
	.string "Where Strong Sailors Enjoy\l"
# 268 "data/maps/OlivineCity/scripts.pory"
	.string "Hearty Meals Of Strength$"
# 269 "data/maps/OlivineCity/scripts.pory"

# 270 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_EonTicketWoman1:
# 271 "data/maps/OlivineCity/scripts.pory"
	.string "My name is Mary!\p"
# 272 "data/maps/OlivineCity/scripts.pory"
	.string "Just kidding, but I love Mary's\n"
# 273 "data/maps/OlivineCity/scripts.pory"
	.string "radio show!$"
# 274 "data/maps/OlivineCity/scripts.pory"

# 275 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_EonTicketWoman2:
# 276 "data/maps/OlivineCity/scripts.pory"
	.string "You must be {PLAYER}!!!\p"
# 277 "data/maps/OlivineCity/scripts.pory"
	.string "Oh my goodness! The champion!\p"
# 278 "data/maps/OlivineCity/scripts.pory"
	.string "I heard about you on Mary's\n"
# 279 "data/maps/OlivineCity/scripts.pory"
	.string "radio show!\p"
# 280 "data/maps/OlivineCity/scripts.pory"
	.string "Here, take this!$"
# 281 "data/maps/OlivineCity/scripts.pory"

# 282 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_EonTicketWoman3:
# 283 "data/maps/OlivineCity/scripts.pory"
	.string "I can't believe I met the\n"
# 284 "data/maps/OlivineCity/scripts.pory"
	.string "champion!!!$"
# 285 "data/maps/OlivineCity/scripts.pory"

# 286 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Sailor1:
# 287 "data/maps/OlivineCity/scripts.pory"
	.string "Dark roads are dangerous\n"
# 288 "data/maps/OlivineCity/scripts.pory"
	.string "at night.\p"
# 289 "data/maps/OlivineCity/scripts.pory"
	.string "But in the pitch-black of\n"
# 290 "data/maps/OlivineCity/scripts.pory"
	.string "night, the sea is even more\l"
# 291 "data/maps/OlivineCity/scripts.pory"
	.string "treacherous!\p"
# 292 "data/maps/OlivineCity/scripts.pory"
	.string "Without the beacon of the\n"
# 293 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse to guide it,\l"
# 294 "data/maps/OlivineCity/scripts.pory"
	.string "no ship can sail.$"
# 295 "data/maps/OlivineCity/scripts.pory"

# 296 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_YoungsterPokegear:
# 297 "data/maps/OlivineCity/scripts.pory"
	.string "That thing you have--\n"
# 298 "data/maps/OlivineCity/scripts.pory"
	.string "it's a Pokégear, right?\l"
# 299 "data/maps/OlivineCity/scripts.pory"
	.string "Wow, that's cool.$"
# 300 "data/maps/OlivineCity/scripts.pory"

# 301 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_YoungsterPokedex:
# 302 "data/maps/OlivineCity/scripts.pory"
	.string "Wow, you have a Pokédex!\p"
# 303 "data/maps/OlivineCity/scripts.pory"
	.string "That is just so awesome.$"
# 304 "data/maps/OlivineCity/scripts.pory"

# 305 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Sailor2:
# 306 "data/maps/OlivineCity/scripts.pory"
	.string "The league has Jasmine\n"
# 307 "data/maps/OlivineCity/scripts.pory"
	.string "pegged as the sixth\l"
# 308 "data/maps/OlivineCity/scripts.pory"
	.string "strongest Gym Leader!\p"
# 309 "data/maps/OlivineCity/scripts.pory"
	.string "Hah! That's a load of crud.\p"
# 310 "data/maps/OlivineCity/scripts.pory"
	.string "There's no way Pryce could\n"
# 311 "data/maps/OlivineCity/scripts.pory"
	.string "hurt Jasmine's Steel-type\l"
# 312 "data/maps/OlivineCity/scripts.pory"
	.string "Pokémon!\p"
# 313 "data/maps/OlivineCity/scripts.pory"
	.string "Bureaucracy if you ask me.\p"
# 314 "data/maps/OlivineCity/scripts.pory"
	.string "She's something to be feared,\n"
# 315 "data/maps/OlivineCity/scripts.pory"
	.string "that's for sure!$"
# 316 "data/maps/OlivineCity/scripts.pory"

# 317 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Sign:
# 318 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine City\p"
# 319 "data/maps/OlivineCity/scripts.pory"
	.string "The Port Closest to Foreign Lands$"
# 320 "data/maps/OlivineCity/scripts.pory"

# 321 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_PortSign:
# 322 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine Port\n"
# 323 "data/maps/OlivineCity/scripts.pory"
	.string "Fast Ship Pier$"
# 324 "data/maps/OlivineCity/scripts.pory"

# 325 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_GymSign:
# 326 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine City Pokémon Gym\n"
# 327 "data/maps/OlivineCity/scripts.pory"
	.string "Leader: Jasmine\p"
# 328 "data/maps/OlivineCity/scripts.pory"
	.string "The Steel-Clad Defense Girl$"
# 329 "data/maps/OlivineCity/scripts.pory"

# 330 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_LighthouseSign:
# 331 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine Lighthouse\n"
# 332 "data/maps/OlivineCity/scripts.pory"
	.string "Also known as the Glitter\l"
# 333 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse$"
# 334 "data/maps/OlivineCity/scripts.pory"

# 335 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_BattleTowerSign:
# 336 "data/maps/OlivineCity/scripts.pory"
	.string "Battle Tower Ahead\n"
# 337 "data/maps/OlivineCity/scripts.pory"
	.string "Opening Now!$"
# 338 "data/maps/OlivineCity/scripts.pory"

# 339 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Machoke:
# 340 "data/maps/OlivineCity/scripts.pory"
	.string "Machoke: Cho!$"

OlivineCity_Littlegirl_Warf::
# 344 "data/maps/OlivineCity/scripts.pory"
	lock
# 345 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 346 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Littlegirl_Warf_Text_0
# 348 "data/maps/OlivineCity/scripts.pory"
	release
	end


MareanieOlivine::
# 353 "data/maps/OlivineCity/scripts.pory"
	lock
# 354 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 355 "data/maps/OlivineCity/scripts.pory"
	playmoncry SPECIES_MAREANIE, CRY_MODE_NORMAL
# 356 "data/maps/OlivineCity/scripts.pory"
	msgbox MareanieOlivine_Text_0
# 357 "data/maps/OlivineCity/scripts.pory"
	waitmoncry
# 358 "data/maps/OlivineCity/scripts.pory"
	release
	end


OlivineSouvenirMart::
# 363 "data/maps/OlivineCity/scripts.pory"
	lock
# 364 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 365 "data/maps/OlivineCity/scripts.pory"
	message OlivineSouvenirMart_Text_0
# 366 "data/maps/OlivineCity/scripts.pory"
	waitmessage
# 367 "data/maps/OlivineCity/scripts.pory"
	pokemart SouvenirMart
# 368 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineSouvenirMart_Text_1
# 369 "data/maps/OlivineCity/scripts.pory"
	release
	end


	.align 2
# 373 "data/maps/OlivineCity/scripts.pory"
SouvenirMart:
# 374 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_STRANGE_SOUVENIR
# 375 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_UNREMARKABLE_TEACUP
# 376 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_UTILITY_UMBRELLA
# 377 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_RED_NECTAR
# 378 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_YELLOW_NECTAR
# 379 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_PINK_NECTAR
# 380 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_PURPLE_NECTAR
	.2byte ITEM_NONE

OlivineCity_RivalPier::
# 384 "data/maps/OlivineCity/scripts.pory"
	lock
# 385 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 386 "data/maps/OlivineCity/scripts.pory"
	createfieldmugshotrival
# 387 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_0
# 389 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_1
# 391 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_2
# 393 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_3
# 395 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_4
# 397 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_5
# 398 "data/maps/OlivineCity/scripts.pory"
	removefieldmugshot
# 399 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 400 "data/maps/OlivineCity/scripts.pory"
	moveobjecttocoords LOCALID_OLIVINE_RIVAL, 19, 49, DIR_NORTH
# 401 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 402 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_RIVAL_STATE, 9
# 403 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_OLIVINE_RIVAL
# 404 "data/maps/OlivineCity/scripts.pory"
	removeobject LOCALID_OLIVINE_RIVAL
# 405 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_ICEPATH_RIVAL
# 406 "data/maps/OlivineCity/scripts.pory"
	release
	end


OlivineCity_Littlegirl_Warf_Text_0:
# 346 "data/maps/OlivineCity/scripts.pory"
	.string "I'm feeding the Mareanie every day!\n"
	.string "They sometimes let me play with them!$"

MareanieOlivine_Text_0:
# 356 "data/maps/OlivineCity/scripts.pory"
	.string "Maree!$"

OlivineSouvenirMart_Text_0:
# 365 "data/maps/OlivineCity/scripts.pory"
	.string "Welcome! How may I help you?$"

OlivineSouvenirMart_Text_1:
# 368 "data/maps/OlivineCity/scripts.pory"
	.string "Come back soon!$"

OlivineCity_RivalPier_Text_0:
# 387 "data/maps/OlivineCity/scripts.pory"
	.string "Oh. \n"
	.string "Hey...$"

OlivineCity_RivalPier_Text_1:
# 389 "data/maps/OlivineCity/scripts.pory"
	.string "Do you ever think that some people are\n"
	.string "just not... built for this?$"

OlivineCity_RivalPier_Text_2:
# 391 "data/maps/OlivineCity/scripts.pory"
	.string "Like it comes naturally\n"
	.string "and for others it's just...$"

OlivineCity_RivalPier_Text_3:
# 393 "data/maps/OlivineCity/scripts.pory"
	.string "Never mind.\n"
	.string "It's a dumb question.$"

OlivineCity_RivalPier_Text_4:
# 395 "data/maps/OlivineCity/scripts.pory"
	.string "Jasmine's Gym is closed.\n"
	.string "You're already on it, I assume.$"

OlivineCity_RivalPier_Text_5:
# 397 "data/maps/OlivineCity/scripts.pory"
	.string "See you around.$"
