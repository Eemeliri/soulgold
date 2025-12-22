# 1 "data/maps/VioletCity/scripts.pory"

# 2 "data/maps/VioletCity/scripts.pory"
.set LOCALID_VIOLETCITY_EARL, 4
# 3 "data/maps/VioletCity/scripts.pory"
.set LOCALID_VIOLET_KIMONO, 31
# 4 "data/maps/VioletCity/scripts.pory"

# 5 "data/maps/VioletCity/scripts.pory"
VioletCity_MapScripts::
# 6 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VioletCity_OnFrame
# 7 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_OnTransition
# 8 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 9 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, VioletCity_OnLoad
# 10 "data/maps/VioletCity/scripts.pory"
	.byte 0
# 11 "data/maps/VioletCity/scripts.pory"

# 12 "data/maps/VioletCity/scripts.pory"
VioletCity_OnFrame::
# 13 "data/maps/VioletCity/scripts.pory"
	map_script_2 VAR_VIOLET_CITY_KIMONO_GIRL, 1, VioletCity_EventScript_Kimono_Girl
# 14 "data/maps/VioletCity/scripts.pory"
	map_script_2 VAR_VIOLET_CITY_STATE, 3, VioletCity_EventScript_ElmCall_Trigger
# 15 "data/maps/VioletCity/scripts.pory"
	.2byte 0
# 16 "data/maps/VioletCity/scripts.pory"

# 17 "data/maps/VioletCity/scripts.pory"
VioletCity_OnTransition::
# 18 "data/maps/VioletCity/scripts.pory"
	callnative SetTimeBasedEncounters
# 19 "data/maps/VioletCity/scripts.pory"
	end
# 20 "data/maps/VioletCity/scripts.pory"

# 21 "data/maps/VioletCity/scripts.pory"
VioletCity_OnLoad::
# 22 "data/maps/VioletCity/scripts.pory"
	setrespawn HEAL_LOCATION_VIOLET_CITY
# 23 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_VISITED_VIOLET_CITY
# 24 "data/maps/VioletCity/scripts.pory"
	end
# 25 "data/maps/VioletCity/scripts.pory"

# 26 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Trigger::
# 27 "data/maps/VioletCity/scripts.pory"
	@LOCAL FLAGHEAP
# 28 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_RECEIVED_TOGEPI_EGG
# 29 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_VIOLET_NPC_TRADE_COMPLETED
# 30 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_SPROUT_TOWER_SILVER
# 31 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_JOHTO_GYM_LEADERS
# 32 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HOOH_BROUGHT
# 33 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_OMANYTE_BROUGHT
# 34 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_AERODACTYL_BROUGHT
# 35 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_KABUTO_BROUGHT
# 36 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_SUDOWOODO
# 37 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_GOT_HARD_STONE
# 38 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_GOT_POISON_BARB
# 39 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_UNION_CAVE_LAPRAS
# 40 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_GOT_BLACK_GLASSES
# 41 "data/maps/VioletCity/scripts.pory"
	
# 42 "data/maps/VioletCity/scripts.pory"
	setvar VAR_SLOWPOKE_TAIL, 0
# 43 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 0
# 44 "data/maps/VioletCity/scripts.pory"
	setvar VAR_RUINSOFALPH_STATE, 0
# 45 "data/maps/VioletCity/scripts.pory"
	
# 46 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_ITEM_GS_BALL
# 47 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_ITEM_DOME_FOSSIL
# 48 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_ITEM_HELIX_FOSSIL
# 49 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_ITEM_OLD_AMBER
# 50 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_TRAINER_SCHOOL_EARL
# 51 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_AIDE
# 52 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
# 53 "data/maps/VioletCity/scripts.pory"
	
# 54 "data/maps/VioletCity/scripts.pory"
	setvar VAR_SPROUT_TOWER, 0
# 55 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_STATE, 1
# 56 "data/maps/VioletCity/scripts.pory"
	end
# 57 "data/maps/VioletCity/scripts.pory"

# 58 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Earl::
# 59 "data/maps/VioletCity/scripts.pory"
	lock
# 60 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 61 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
# 62 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 63 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 64 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_EarlAsksIfYouBeatFalkner MSGBOX_YESNO
# 65 "data/maps/VioletCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, VioletCity_EventScript_EarlTrainerSchool
# 66 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_VeryNiceIndeed, MSGBOX_DEFAULT
# 67 "data/maps/VioletCity/scripts.pory"
	closemessage
# 68 "data/maps/VioletCity/scripts.pory"
	release
# 69 "data/maps/VioletCity/scripts.pory"
	end
# 70 "data/maps/VioletCity/scripts.pory"

# 71 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchool::
# 72 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_FollowEarl, MSGBOX_DEFAULT
# 73 "data/maps/VioletCity/scripts.pory"
	closemessage
# 74 "data/maps/VioletCity/scripts.pory"
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
# 75 "data/maps/VioletCity/scripts.pory"
	switch VAR_FACING
# 76 "data/maps/VioletCity/scripts.pory"
	case DIR_NORTH, VioletCity_EventScript_EarlTrainerSchoolSouth
# 77 "data/maps/VioletCity/scripts.pory"
	case DIR_WEST, VioletCity_EventScript_EarlTrainerSchoolEast
# 78 "data/maps/VioletCity/scripts.pory"
	release
# 79 "data/maps/VioletCity/scripts.pory"
	end
# 80 "data/maps/VioletCity/scripts.pory"

# 81 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchoolSouth::
# 82 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_South_Adjustment
# 83 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 84 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
# 85 "data/maps/VioletCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Player_South_Adjustment
# 86 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 87 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 88 "data/maps/VioletCity/scripts.pory"
	goto VioletCity_EventScript_EarlTrainerSchoolTransition
# 89 "data/maps/VioletCity/scripts.pory"
	release
# 90 "data/maps/VioletCity/scripts.pory"
	end
# 91 "data/maps/VioletCity/scripts.pory"

# 92 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchoolEast::
# 93 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_East_Adjustment
# 94 "data/maps/VioletCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Player_East_Adjustment
# 95 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 96 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 97 "data/maps/VioletCity/scripts.pory"
	goto VioletCity_EventScript_EarlTrainerSchoolTransition
# 98 "data/maps/VioletCity/scripts.pory"
	release
# 99 "data/maps/VioletCity/scripts.pory"
	end
# 100 "data/maps/VioletCity/scripts.pory"

# 101 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchoolTransition:
# 102 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Walk_To_School
# 103 "data/maps/VioletCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Walk_To_School
# 104 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 105 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 106 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
# 107 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 108 "data/maps/VioletCity/scripts.pory"
	turnobject LOCALID_VIOLETCITY_EARL, DIR_WEST
# 109 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_HereTeacherIAm, MSGBOX_DEFAULT
# 110 "data/maps/VioletCity/scripts.pory"
	closemessage
# 111 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Walk_Inside
# 112 "data/maps/VioletCity/scripts.pory"
	delay 20
# 113 "data/maps/VioletCity/scripts.pory"
	opendoor 39, 36
# 114 "data/maps/VioletCity/scripts.pory"
	waitdooranim
# 115 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 116 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_EARL
# 117 "data/maps/VioletCity/scripts.pory"
	removeobject LOCALID_VIOLETCITY_EARL
# 118 "data/maps/VioletCity/scripts.pory"
	closedoor 39, 36
# 119 "data/maps/VioletCity/scripts.pory"
	waitdooranim
# 120 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_TRAINER_SCHOOL_EARL
# 121 "data/maps/VioletCity/scripts.pory"
	fadedefaultbgm
# 122 "data/maps/VioletCity/scripts.pory"
	release
# 123 "data/maps/VioletCity/scripts.pory"
	end
# 124 "data/maps/VioletCity/scripts.pory"

# 125 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Youngster::
# 126 "data/maps/VioletCity/scripts.pory"
	lock
# 127 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 128 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Youngster, MSGBOX_DEFAULT
# 129 "data/maps/VioletCity/scripts.pory"
	closemessage
# 130 "data/maps/VioletCity/scripts.pory"
	release
# 131 "data/maps/VioletCity/scripts.pory"
	end
# 132 "data/maps/VioletCity/scripts.pory"

# 133 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Boy::
# 134 "data/maps/VioletCity/scripts.pory"
	lock
# 135 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 136 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Boy, MSGBOX_DEFAULT
# 137 "data/maps/VioletCity/scripts.pory"
	closemessage
# 138 "data/maps/VioletCity/scripts.pory"
	release
# 139 "data/maps/VioletCity/scripts.pory"
	end
# 140 "data/maps/VioletCity/scripts.pory"

# 141 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Gramps::
# 142 "data/maps/VioletCity/scripts.pory"
	lock
# 143 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 144 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Gramps, MSGBOX_DEFAULT
# 145 "data/maps/VioletCity/scripts.pory"
	closemessage
# 146 "data/maps/VioletCity/scripts.pory"
	release
# 147 "data/maps/VioletCity/scripts.pory"
	end
# 148 "data/maps/VioletCity/scripts.pory"

# 149 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Lass::
# 150 "data/maps/VioletCity/scripts.pory"
	lock
# 151 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 152 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Lass, MSGBOX_DEFAULT
# 153 "data/maps/VioletCity/scripts.pory"
	closemessage
# 154 "data/maps/VioletCity/scripts.pory"
	release
# 155 "data/maps/VioletCity/scripts.pory"
	end
# 156 "data/maps/VioletCity/scripts.pory"

# 157 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Pichu::
# 158 "data/maps/VioletCity/scripts.pory"
	lock
# 159 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 160 "data/maps/VioletCity/scripts.pory"
	waitse
# 161 "data/maps/VioletCity/scripts.pory"
	playmoncry SPECIES_PICHU, CRY_MODE_NORMAL
# 162 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Pichu, MSGBOX_DEFAULT
# 163 "data/maps/VioletCity/scripts.pory"
	waitmoncry
# 164 "data/maps/VioletCity/scripts.pory"
	release
# 165 "data/maps/VioletCity/scripts.pory"
	end
# 166 "data/maps/VioletCity/scripts.pory"

# 167 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Bellsprout::
# 168 "data/maps/VioletCity/scripts.pory"
	lock
# 169 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 170 "data/maps/VioletCity/scripts.pory"
	waitse
# 171 "data/maps/VioletCity/scripts.pory"
	playmoncry SPECIES_BELLSPROUT, CRY_MODE_NORMAL
# 172 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Bellsprout, MSGBOX_DEFAULT
# 173 "data/maps/VioletCity/scripts.pory"
	waitmoncry
# 174 "data/maps/VioletCity/scripts.pory"
	release
# 175 "data/maps/VioletCity/scripts.pory"
	end
# 176 "data/maps/VioletCity/scripts.pory"

# 177 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Rattata::
# 178 "data/maps/VioletCity/scripts.pory"
	lock
# 179 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 180 "data/maps/VioletCity/scripts.pory"
	waitse
# 181 "data/maps/VioletCity/scripts.pory"
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
# 182 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Rattata, MSGBOX_DEFAULT
# 183 "data/maps/VioletCity/scripts.pory"
	waitmoncry
# 184 "data/maps/VioletCity/scripts.pory"
	release
# 185 "data/maps/VioletCity/scripts.pory"
	end
# 186 "data/maps/VioletCity/scripts.pory"

# 187 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ElmCall_Trigger::
# 188 "data/maps/VioletCity/scripts.pory"
	lock
# 189 "data/maps/VioletCity/scripts.pory"
	pokenavcall VioletCity_Text_Elm_Call
# 190 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 191 "data/maps/VioletCity/scripts.pory"
	delay 30
# 192 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_VIOLET_CITY_AIDE
# 193 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
# 194 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_STATE, 4
# 195 "data/maps/VioletCity/scripts.pory"
	release
# 196 "data/maps/VioletCity/scripts.pory"
	end
# 197 "data/maps/VioletCity/scripts.pory"

# 198 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Kimono_Girl::
# 199 "data/maps/VioletCity/scripts.pory"
	lock
# 200 "data/maps/VioletCity/scripts.pory"
	playbgm MUS_HG_KIMONO_GIRL, TRUE
# 201 "data/maps/VioletCity/scripts.pory"
	playse SE_PIN
# 202 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, Common_Movement_ExclamationMark
# 203 "data/maps/VioletCity/scripts.pory"
	delay 60
# 204 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_1
# 205 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 206 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl1, MSGBOX_DEFAULT
# 207 "data/maps/VioletCity/scripts.pory"
	closemessage
# 208 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_2
# 209 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 210 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl2, MSGBOX_DEFAULT
# 211 "data/maps/VioletCity/scripts.pory"
	closemessage
# 212 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_3
# 213 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 214 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl3, MSGBOX_DEFAULT
# 215 "data/maps/VioletCity/scripts.pory"
	closemessage
# 216 "data/maps/VioletCity/scripts.pory"
	playse SE_M_PETAL_DANCE
# 217 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_4
# 218 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 219 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl4, MSGBOX_DEFAULT
# 220 "data/maps/VioletCity/scripts.pory"
	closemessage
# 221 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_5
# 222 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 223 "data/maps/VioletCity/scripts.pory"
	fadedefaultbgm
# 224 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 2
# 225 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
# 226 "data/maps/VioletCity/scripts.pory"
	removeobject LOCALID_VIOLET_KIMONO
# 227 "data/maps/VioletCity/scripts.pory"
	release
# 228 "data/maps/VioletCity/scripts.pory"
	end
# 229 "data/maps/VioletCity/scripts.pory"

# 230 "data/maps/VioletCity/scripts.pory"

# 231 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ItemRareCandy::
# 232 "data/maps/VioletCity/scripts.pory"
	finditem ITEM_RARE_CANDY
# 233 "data/maps/VioletCity/scripts.pory"
	end
# 234 "data/maps/VioletCity/scripts.pory"

# 235 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ItemPechaBerry::
# 236 "data/maps/VioletCity/scripts.pory"
	finditem ITEM_PECHA_BERRY
# 237 "data/maps/VioletCity/scripts.pory"
	end
# 238 "data/maps/VioletCity/scripts.pory"

# 239 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ItemHyperPotion::
# 240 "data/maps/VioletCity/scripts.pory"
	finditem ITEM_HYPER_POTION
# 241 "data/maps/VioletCity/scripts.pory"
	end
# 242 "data/maps/VioletCity/scripts.pory"

# 243 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_Spin:
# 244 "data/maps/VioletCity/scripts.pory"
	face_down
# 245 "data/maps/VioletCity/scripts.pory"
	face_right
# 246 "data/maps/VioletCity/scripts.pory"
	face_up
# 247 "data/maps/VioletCity/scripts.pory"
	face_left
# 248 "data/maps/VioletCity/scripts.pory"
	face_down
# 249 "data/maps/VioletCity/scripts.pory"
	face_right
# 250 "data/maps/VioletCity/scripts.pory"
	face_up
# 251 "data/maps/VioletCity/scripts.pory"
	face_left
# 252 "data/maps/VioletCity/scripts.pory"
	face_down
# 253 "data/maps/VioletCity/scripts.pory"
	face_right
# 254 "data/maps/VioletCity/scripts.pory"
	face_up
# 255 "data/maps/VioletCity/scripts.pory"
	face_left
# 256 "data/maps/VioletCity/scripts.pory"
	face_down
# 257 "data/maps/VioletCity/scripts.pory"
	step_end
# 258 "data/maps/VioletCity/scripts.pory"

# 259 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_East_Adjustment:
# 260 "data/maps/VioletCity/scripts.pory"
	walk_down
# 261 "data/maps/VioletCity/scripts.pory"
	walk_down
# 262 "data/maps/VioletCity/scripts.pory"
	walk_down
# 263 "data/maps/VioletCity/scripts.pory"
	walk_right
# 264 "data/maps/VioletCity/scripts.pory"
	step_end
# 265 "data/maps/VioletCity/scripts.pory"

# 266 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Player_East_Adjustment:
# 267 "data/maps/VioletCity/scripts.pory"
	walk_down
# 268 "data/maps/VioletCity/scripts.pory"
	walk_down
# 269 "data/maps/VioletCity/scripts.pory"
	walk_left
# 270 "data/maps/VioletCity/scripts.pory"
	walk_down
# 271 "data/maps/VioletCity/scripts.pory"
	face_right
# 272 "data/maps/VioletCity/scripts.pory"
	step_end
# 273 "data/maps/VioletCity/scripts.pory"

# 274 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_South_Adjustment:
# 275 "data/maps/VioletCity/scripts.pory"
	walk_right
# 276 "data/maps/VioletCity/scripts.pory"
	walk_down
# 277 "data/maps/VioletCity/scripts.pory"
	walk_down
# 278 "data/maps/VioletCity/scripts.pory"
	walk_down
# 279 "data/maps/VioletCity/scripts.pory"
	face_right
# 280 "data/maps/VioletCity/scripts.pory"
	step_end
# 281 "data/maps/VioletCity/scripts.pory"

# 282 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Player_South_Adjustment:
# 283 "data/maps/VioletCity/scripts.pory"
	walk_down
# 284 "data/maps/VioletCity/scripts.pory"
	walk_down
# 285 "data/maps/VioletCity/scripts.pory"
	step_end
# 286 "data/maps/VioletCity/scripts.pory"

# 287 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Walk_To_School:
# 288 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 289 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 290 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 291 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 292 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 293 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 294 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 295 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 296 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 297 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 298 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 299 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 300 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 301 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 302 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 303 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 304 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 305 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 306 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 307 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 308 "data/maps/VioletCity/scripts.pory"
	step_end
# 309 "data/maps/VioletCity/scripts.pory"

# 310 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Walk_To_School_Player:
# 311 "data/maps/VioletCity/scripts.pory"
	walk_right
# 312 "data/maps/VioletCity/scripts.pory"
	walk_right
# 313 "data/maps/VioletCity/scripts.pory"
	walk_right
# 314 "data/maps/VioletCity/scripts.pory"
	walk_right
# 315 "data/maps/VioletCity/scripts.pory"
	walk_right
# 316 "data/maps/VioletCity/scripts.pory"
	walk_right
# 317 "data/maps/VioletCity/scripts.pory"
	walk_right
# 318 "data/maps/VioletCity/scripts.pory"
	walk_right
# 319 "data/maps/VioletCity/scripts.pory"
	walk_right
# 320 "data/maps/VioletCity/scripts.pory"
	walk_right
# 321 "data/maps/VioletCity/scripts.pory"
	walk_right
# 322 "data/maps/VioletCity/scripts.pory"
	walk_right
# 323 "data/maps/VioletCity/scripts.pory"
	walk_right
# 324 "data/maps/VioletCity/scripts.pory"
	walk_right
# 325 "data/maps/VioletCity/scripts.pory"
	walk_right
# 326 "data/maps/VioletCity/scripts.pory"
	walk_right
# 327 "data/maps/VioletCity/scripts.pory"
	walk_right
# 328 "data/maps/VioletCity/scripts.pory"
	walk_right
# 329 "data/maps/VioletCity/scripts.pory"
	walk_right
# 330 "data/maps/VioletCity/scripts.pory"
	walk_right
# 331 "data/maps/VioletCity/scripts.pory"
	step_end
# 332 "data/maps/VioletCity/scripts.pory"

# 333 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_Walk_Inside:
# 334 "data/maps/VioletCity/scripts.pory"
	walk_up
# 335 "data/maps/VioletCity/scripts.pory"
	walk_up
# 336 "data/maps/VioletCity/scripts.pory"
	step_end
# 337 "data/maps/VioletCity/scripts.pory"

# 338 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_1:
# 339 "data/maps/VioletCity/scripts.pory"
	walk_left
# 340 "data/maps/VioletCity/scripts.pory"
	walk_left
# 341 "data/maps/VioletCity/scripts.pory"
	walk_left
# 342 "data/maps/VioletCity/scripts.pory"
	walk_left
# 343 "data/maps/VioletCity/scripts.pory"
	face_up
# 344 "data/maps/VioletCity/scripts.pory"
	step_end
# 345 "data/maps/VioletCity/scripts.pory"

# 346 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_2:
# 347 "data/maps/VioletCity/scripts.pory"
	walk_up
# 348 "data/maps/VioletCity/scripts.pory"
	step_end
# 349 "data/maps/VioletCity/scripts.pory"

# 350 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_3:
# 351 "data/maps/VioletCity/scripts.pory"
	lock_facing_direction
# 352 "data/maps/VioletCity/scripts.pory"
	walk_down
# 353 "data/maps/VioletCity/scripts.pory"
	unlock_facing_direction
# 354 "data/maps/VioletCity/scripts.pory"
	step_end
# 355 "data/maps/VioletCity/scripts.pory"

# 356 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_4:
# 357 "data/maps/VioletCity/scripts.pory"
	face_right
# 358 "data/maps/VioletCity/scripts.pory"
	delay_8
# 359 "data/maps/VioletCity/scripts.pory"
	face_down
# 360 "data/maps/VioletCity/scripts.pory"
	delay_8
# 361 "data/maps/VioletCity/scripts.pory"
	face_left
# 362 "data/maps/VioletCity/scripts.pory"
	delay_8
# 363 "data/maps/VioletCity/scripts.pory"
	face_up
# 364 "data/maps/VioletCity/scripts.pory"
	delay_8
# 365 "data/maps/VioletCity/scripts.pory"
	face_right
# 366 "data/maps/VioletCity/scripts.pory"
	delay_8
# 367 "data/maps/VioletCity/scripts.pory"
	face_down
# 368 "data/maps/VioletCity/scripts.pory"
	delay_8
# 369 "data/maps/VioletCity/scripts.pory"
	face_left
# 370 "data/maps/VioletCity/scripts.pory"
	delay_8
# 371 "data/maps/VioletCity/scripts.pory"
	face_up
# 372 "data/maps/VioletCity/scripts.pory"
	delay_8
# 373 "data/maps/VioletCity/scripts.pory"
	step_end
# 374 "data/maps/VioletCity/scripts.pory"

# 375 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_5:
# 376 "data/maps/VioletCity/scripts.pory"
	walk_left
# 377 "data/maps/VioletCity/scripts.pory"
	walk_left
# 378 "data/maps/VioletCity/scripts.pory"
	walk_left
# 379 "data/maps/VioletCity/scripts.pory"
	walk_left
# 380 "data/maps/VioletCity/scripts.pory"
	walk_left
# 381 "data/maps/VioletCity/scripts.pory"
	walk_up
# 382 "data/maps/VioletCity/scripts.pory"
	walk_up
# 383 "data/maps/VioletCity/scripts.pory"
	walk_up
# 384 "data/maps/VioletCity/scripts.pory"
	walk_up
# 385 "data/maps/VioletCity/scripts.pory"
	walk_up
# 386 "data/maps/VioletCity/scripts.pory"
	walk_up
# 387 "data/maps/VioletCity/scripts.pory"
	walk_up
# 388 "data/maps/VioletCity/scripts.pory"
	walk_up
# 389 "data/maps/VioletCity/scripts.pory"
	walk_up
# 390 "data/maps/VioletCity/scripts.pory"
	step_end	
# 391 "data/maps/VioletCity/scripts.pory"

# 392 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_LiquidJustice::
# 393 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_LiquidJustice, MSGBOX_NPC
# 394 "data/maps/VioletCity/scripts.pory"
	end
# 395 "data/maps/VioletCity/scripts.pory"

# 396 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_GymSign::
# 397 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_GymSign, MSGBOX_SIGN
# 398 "data/maps/VioletCity/scripts.pory"
	end
# 399 "data/maps/VioletCity/scripts.pory"

# 400 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_LiquidJustice:
# 401 "data/maps/VioletCity/scripts.pory"
	.string "Look around!\p"
# 402 "data/maps/VioletCity/scripts.pory"
	.string "It's easy to see what POKéMON\n"
# 403 "data/maps/VioletCity/scripts.pory"
	.string "you can catch in an area without\l"
# 404 "data/maps/VioletCity/scripts.pory"
	.string "having to run around in tall\l"
# 405 "data/maps/VioletCity/scripts.pory"
	.string "grass all day!$"
# 406 "data/maps/VioletCity/scripts.pory"

# 407 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_EarlAsksIfYouBeatFalkner:
# 408 "data/maps/VioletCity/scripts.pory"
	.string "Hello!\n"
# 409 "data/maps/VioletCity/scripts.pory"
	.string "You are trainer?\p"
# 410 "data/maps/VioletCity/scripts.pory"
	.string "Battle GYM LEADER,\n"
# 411 "data/maps/VioletCity/scripts.pory"
	.string "win you did?$"
# 412 "data/maps/VioletCity/scripts.pory"

# 413 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_VeryNiceIndeed:
# 414 "data/maps/VioletCity/scripts.pory"
	.string "Ooh, la la!\n"
# 415 "data/maps/VioletCity/scripts.pory"
	.string "Very indeed nice!$"
# 416 "data/maps/VioletCity/scripts.pory"

# 417 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_FollowEarl:
# 418 "data/maps/VioletCity/scripts.pory"
	.string "Is that so? Then study shall\n"
# 419 "data/maps/VioletCity/scripts.pory"
	.string "you! Follow me!$"
# 420 "data/maps/VioletCity/scripts.pory"

# 421 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_HereTeacherIAm:
# 422 "data/maps/VioletCity/scripts.pory"
	.string "Here, teacher I am.\n"
# 423 "data/maps/VioletCity/scripts.pory"
	.string "Good it is you study here!$"
# 424 "data/maps/VioletCity/scripts.pory"

# 425 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Lass:
# 426 "data/maps/VioletCity/scripts.pory"
	.string "Ghosts are rumored to appear\n"
# 427 "data/maps/VioletCity/scripts.pory"
	.string "in SPROUT TOWER.\p"
# 428 "data/maps/VioletCity/scripts.pory"
	.string "They say that GHOST-type\n"
# 429 "data/maps/VioletCity/scripts.pory"
	.string "moves can bypass the defenses\p"
# 430 "data/maps/VioletCity/scripts.pory"
	.string "of tough POKéMON like ONIX\n"
# 431 "data/maps/VioletCity/scripts.pory"
	.string "and GEODUDE.$"
# 432 "data/maps/VioletCity/scripts.pory"

# 433 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Boy:
# 434 "data/maps/VioletCity/scripts.pory"
	.string "Hey, you're a POKéMON trainer?\p"
# 435 "data/maps/VioletCity/scripts.pory"
	.string "If you head to the ACADEMY,\n"
# 436 "data/maps/VioletCity/scripts.pory"
	.string "you might learn something new!$"
# 437 "data/maps/VioletCity/scripts.pory"

# 438 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Gramps:
# 439 "data/maps/VioletCity/scripts.pory"
	.string "FALKNER, from the VIOLET\n"
# 440 "data/maps/VioletCity/scripts.pory"
	.string "POKéMON GYM, is a fine trainer!\p"
# 441 "data/maps/VioletCity/scripts.pory"
	.string "He inherited his father's gym\n"
# 442 "data/maps/VioletCity/scripts.pory"
	.string "and has done a great job with\l"
# 443 "data/maps/VioletCity/scripts.pory"
	.string "it.$"
# 444 "data/maps/VioletCity/scripts.pory"

# 445 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Youngster:
# 446 "data/maps/VioletCity/scripts.pory"
	.string "I saw a wiggly tree up ahead!\p"
# 447 "data/maps/VioletCity/scripts.pory"
	.string "If you touch it, it squirms\n"
# 448 "data/maps/VioletCity/scripts.pory"
	.string "and dances! Cool!$"
# 449 "data/maps/VioletCity/scripts.pory"

# 450 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Sign:
# 451 "data/maps/VioletCity/scripts.pory"
	.string "VIOLET CITY\p"
# 452 "data/maps/VioletCity/scripts.pory"
	.string "The City of Nostalgic Scents$"
# 453 "data/maps/VioletCity/scripts.pory"

# 454 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_GymSign:
# 455 "data/maps/VioletCity/scripts.pory"
	.string "VIOLET CITY POKéMON GYM\p"
# 456 "data/maps/VioletCity/scripts.pory"
	.string "LEADER: FALKNER, The Elegant\n"
# 457 "data/maps/VioletCity/scripts.pory"
	.string "Master of Flying POKéMON$"
# 458 "data/maps/VioletCity/scripts.pory"

# 459 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_SproutTowerSign:
# 460 "data/maps/VioletCity/scripts.pory"
	.string "SPROUT TOWER\p"
# 461 "data/maps/VioletCity/scripts.pory"
	.string "Experience the Way of POKéMON$"
# 462 "data/maps/VioletCity/scripts.pory"

# 463 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_EarlsAcademySign:
# 464 "data/maps/VioletCity/scripts.pory"
	.string "EARL'S POKéMON ACADEMY$"
# 465 "data/maps/VioletCity/scripts.pory"

# 466 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Pichu:
# 467 "data/maps/VioletCity/scripts.pory"
	.string "PICHU: Chuuuu!$"
# 468 "data/maps/VioletCity/scripts.pory"

# 469 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Bellsprout:
# 470 "data/maps/VioletCity/scripts.pory"
	.string "BELLSPROUT: Sprouuuut.$"
# 471 "data/maps/VioletCity/scripts.pory"

# 472 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Rattata:
# 473 "data/maps/VioletCity/scripts.pory"
	.string "RATTATA: RATTATARATTA!$"
# 474 "data/maps/VioletCity/scripts.pory"

# 475 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Elm_Call:
# 476 "data/maps/VioletCity/scripts.pory"
	.string "ELM: Hello, {PLAYER}? We\n"
# 477 "data/maps/VioletCity/scripts.pory"
	.string "discovered something about the EGG!\p"
# 478 "data/maps/VioletCity/scripts.pory"
	.string "My assistant is at the POKéMON\n"
# 479 "data/maps/VioletCity/scripts.pory"
	.string "CENTER in VIOLET CITY.\p"
# 480 "data/maps/VioletCity/scripts.pory"
	.string "Could you talk to him?$"
# 481 "data/maps/VioletCity/scripts.pory"

# 482 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl1:
# 483 "data/maps/VioletCity/scripts.pory"
.string "Me oh my...\n"
# 484 "data/maps/VioletCity/scripts.pory"
.string "That Egg must be...!$"
# 485 "data/maps/VioletCity/scripts.pory"

# 486 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl2:
# 487 "data/maps/VioletCity/scripts.pory"
.string "I see...\p"
# 488 "data/maps/VioletCity/scripts.pory"
.string "So it was handed from MR. POKéMON\n"
# 489 "data/maps/VioletCity/scripts.pory"
.string "to PROF. ELM, then from \l"
# 490 "data/maps/VioletCity/scripts.pory"
.string "PROF. ELM to you.\p"
# 491 "data/maps/VioletCity/scripts.pory"
.string "Now I get it...$"
# 492 "data/maps/VioletCity/scripts.pory"

# 493 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl3:
# 494 "data/maps/VioletCity/scripts.pory"
.string "That Egg is truly an important Egg.\p"
# 495 "data/maps/VioletCity/scripts.pory"
.string "Please do take good care of it\n"
# 496 "data/maps/VioletCity/scripts.pory"
.string "for me. Is that understood?$"
# 497 "data/maps/VioletCity/scripts.pory"

# 498 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl4:
# 499 "data/maps/VioletCity/scripts.pory"
.string "I am counting on you.$"

berrytrader_juggler::
# 505 "data/maps/VioletCity/scripts.pory"
	lock
# 506 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 507 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_0
# 508 "data/maps/VioletCity/scripts.pory"
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, berrytrader_juggler_Text_1, berrytrader_juggler_Text_2, berrytrader_juggler_Text_3, berrytrader_juggler_Text_4, berrytrader_juggler_Text_5
# 509 "data/maps/VioletCity/scripts.pory"
	switch VAR_RESULT
# 510 "data/maps/VioletCity/scripts.pory"
	case 0, berrytrader_juggler_3
# 526 "data/maps/VioletCity/scripts.pory"
	case 1, berrytrader_juggler_4
# 542 "data/maps/VioletCity/scripts.pory"
	case 2, berrytrader_juggler_5
# 558 "data/maps/VioletCity/scripts.pory"
	case 3, berrytrader_juggler_6
# 575 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_11, MSGBOX_DEFAULT
# 576 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 577 "data/maps/VioletCity/scripts.pory"
	release
	end

# 580 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_3:
# 511 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_RED_SHARD
# 512 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_9
# 522 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 523 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_4:
# 527 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_BLUE_SHARD
# 528 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_12
# 538 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 539 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_5:
# 543 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_YELLOW_SHARD
# 544 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_15
# 554 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 555 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_6:
# 559 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_GREEN_SHARD
# 560 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_18
# 570 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 571 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_9:
# 513 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_6
# 514 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_RED_SHARD, 1
# 515 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_CHERI_BERRY
# 516 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_PECHA_BERRY
# 517 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_LEPPA_BERRY
# 518 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 519 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_12:
# 529 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_8
# 530 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_BLUE_SHARD, 1
# 531 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_ORAN_BERRY
# 532 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_CHESTO_BERRY
# 533 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_WIKI_BERRY
# 534 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 535 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_15:
# 545 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_9
# 546 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_YELLOW_SHARD, 1
# 547 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_ASPEAR_BERRY
# 548 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_SITRUS_BERRY
# 549 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_IAPAPA_BERRY
# 550 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 551 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_18:
# 561 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_10
# 562 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_GREEN_SHARD, 1
# 563 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_RAWST_BERRY
# 564 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_LUM_BERRY
# 565 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_AGUAV_BERRY
# 566 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 567 "data/maps/VioletCity/scripts.pory"
	release
	end


berrytrader_juggler_Text_0:
# 507 "data/maps/VioletCity/scripts.pory"
	.string "Yah yah! I'm a huge fan of colored\n"
	.string "shards. Do you have any to trade for\l"
	.string "me? I will give you three berries for\l"
	.string "each shard.$"

berrytrader_juggler_Text_1:
# 508 "data/maps/VioletCity/scripts.pory"
	.string "Red Shard$"

berrytrader_juggler_Text_2:
# 508 "data/maps/VioletCity/scripts.pory"
	.string "Blue Shard$"

berrytrader_juggler_Text_3:
# 508 "data/maps/VioletCity/scripts.pory"
	.string "Yellow Shard$"

berrytrader_juggler_Text_4:
# 508 "data/maps/VioletCity/scripts.pory"
	.string "Green Shard$"

berrytrader_juggler_Text_5:
# 508 "data/maps/VioletCity/scripts.pory"
	.string "Cancel$"

berrytrader_juggler_Text_6:
# 513 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set A for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_7:
# 522 "data/maps/VioletCity/scripts.pory"
	.string "You don't seem to have that shard with\n"
	.string "you.$"

berrytrader_juggler_Text_8:
# 529 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set B for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_9:
# 545 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set C for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_10:
# 561 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set D for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_11:
# 575 "data/maps/VioletCity/scripts.pory"
	.string "Not interested huh? Shame...$"
