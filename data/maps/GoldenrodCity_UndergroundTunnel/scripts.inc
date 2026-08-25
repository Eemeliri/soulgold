# 1 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 2 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 3 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_MapScripts::
# 4 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_UndergroundTunnel_OnLoad
# 5 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.byte 0
# 6 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 7 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_OnLoad::
# 8 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	call GoldenrodCity_UndergroundTunnel_MapScript_TryOpenDoor
# 9 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	call_if_ge VAR_NEWBARK_TOWN_STATE, 12, Goldenrod_TryOpenRocketArcadeDoor
# 10 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 11 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_EventScript_KimonoTriggerBot::
# 12 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 13 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playbgm MUS_HG_KIMONO_GIRL, TRUE
# 14 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerBot
# 15 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 16 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	createfieldmugshot MUGSHOT_KIMONO_GIRL
# 17 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono1, MSGBOX_DEFAULT
# 18 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 19 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playse SE_PIN
# 20 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, Common_Movement_ExclamationMark
# 21 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	delay 60
# 22 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	createfieldmugshot MUGSHOT_KIMONO_GIRL
# 23 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono2, MSGBOX_DEFAULT
# 24 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 25 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, Common_Movement_WalkUp1
# 26 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 27 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave1
# 28 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 29 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playse SE_M_PETAL_DANCE
# 30 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Spin
# 31 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 32 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave2
# 33 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 34 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
# 35 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	removeobject LOCALID_GOLDENROD_UNDERGROUND_KIMONO
# 36 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	fadedefaultbgm
# 37 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setvar VAR_GOLDENROD_CITY_STATE, 8
# 38 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 39 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 40 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_EventScript_KimonoTriggerTop::
# 41 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 42 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playbgm MUS_HG_KIMONO_GIRL, TRUE
# 43 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerTop
# 44 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 45 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	createfieldmugshot MUGSHOT_KIMONO_GIRL
# 46 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono1, MSGBOX_DEFAULT
# 47 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 48 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playse SE_PIN
# 49 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, Common_Movement_ExclamationMark
# 50 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	delay 60
# 51 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	createfieldmugshot MUGSHOT_KIMONO_GIRL
# 52 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono2, MSGBOX_DEFAULT
# 53 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 54 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, Common_Movement_WalkDown1
# 55 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 56 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave1
# 57 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 58 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playse SE_M_PETAL_DANCE
# 59 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Spin
# 60 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 61 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave2
# 62 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmovement 0
# 63 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
# 64 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	removeobject LOCALID_GOLDENROD_UNDERGROUND_KIMONO
# 65 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	savebgm MUS_DUMMY
# 66 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	fadedefaultbgm
# 67 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setvar VAR_GOLDENROD_CITY_STATE, 8
# 68 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 69 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 70 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 71 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerBot:
# 72 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 73 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 74 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 75 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 76 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	step_end
# 77 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 78 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerTop:
# 79 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_up
# 80 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 81 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 82 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 83 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 84 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	step_end
# 85 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 86 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave1:
# 87 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 88 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 89 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 90 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 91 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 92 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 93 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_left
# 94 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	step_end
# 95 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 96 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_Movement_Kimono_Spin:
# 97 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	face_down
# 98 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	face_right
# 99 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	face_up
# 100 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	face_left
# 101 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	face_down
# 102 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	face_right
# 103 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	face_up
# 104 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	step_end
# 105 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 106 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave2:
# 107 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_up
# 108 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_up
# 109 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_up
# 110 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_up
# 111 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_up
# 112 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	walk_up
# 113 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	step_end
# 114 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 115 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 116 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_Text_Kimono1:
# 117 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Team Rocket members in black suits\n"
# 118 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "have been running around...\p"
# 119 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "I was wondering what was going on.\n"
# 120 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "So, you took on Team Rocket?\l"
# 121 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "You are impressive!\p"
# 122 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "You may be able to face the\n"
# 123 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "legendary Pokémon...$"
# 124 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 125 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_Text_Kimono2:
# 126 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Hahaha! Never mind.\n"
# 127 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "I must go now.$"
# 128 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 129 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Eric::
# 130 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	trainerbattle_single TRAINER_ERIC GoldenrodUnderground_Text_SupernerdEricSeen, GoldenrodUnderground_Text_SupernerdEricBeaten
# 131 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_SupernerdEricAfterBattle, MSGBOX_AUTOCLOSE
# 132 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 133 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 134 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Teru::
# 135 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	trainerbattle_single TRAINER_TERU GoldenrodUnderground_Text_SupernerdTeruSeen, GoldenrodUnderground_Text_SupernerdTeruBeaten
# 136 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_SupernerdTeruAfterBattle, MSGBOX_AUTOCLOSE
# 137 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 138 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 139 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Issac::
# 140 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	trainerbattle_single TRAINER_ISSAC GoldenrodUnderground_Text_PokemaniacIssacSeen, GoldenrodUnderground_Text_PokemaniacIssacBeaten
# 141 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_PokemaniacIssacAfterBattle, MSGBOX_AUTOCLOSE
# 142 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 143 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 144 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Donald::
# 145 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	trainerbattle_single TRAINER_DONALD GoldenrodUnderground_Text_PokemaniacDonaldSeen, GoldenrodUnderground_Text_PokemaniacDonaldBeaten
# 146 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_PokemaniacDonaldAfterBattle, MSGBOX_AUTOCLOSE
# 147 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 148 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 149 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Brother_Haircut1::
# 150 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 151 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	faceplayer
# 152 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_set FLAG_GOT_HAIRCUT, GoldenrodUnderground_EventScript_Already_Got_Haircut1
# 153 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	showmoneybox 0, 0
# 154 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherOffer, MSGBOX_YESNO
# 155 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, GoldenrodUnderground_EventScript_Haircut1
# 156 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherThatsAShame, MSGBOX_DEFAULT
# 157 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 158 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 159 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 160 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 161 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Haircut1::
# 162 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherAskWhich
# 163 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	special ChoosePartyMon
# 164 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitstate
# 165 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	showmoneybox 0, 0
# 166 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 167 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	faceplayer
# 168 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_ge VAR_0x8004, PARTY_SIZE, GoldenrodUnderground_EventScript_Declined_Haircut1
# 169 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
# 170 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_EGG, GoldenrodUnderground_EventScript_Declined_Haircut1
# 171 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	checkmoney 500, 0
# 172 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodUnderground_EventScript_NotEnough_Haircut1
# 173 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	removemoney 500
# 174 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	updatemoneybox 0
# 175 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playse SE_SHOP
# 176 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherWatchItBeautiful
# 177 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 178 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	fadescreen FADE_TO_BLACK
# 179 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playfanfare MUS_HEAL
# 180 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitfanfare
# 181 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	special HaircutBrother1
# 182 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 183 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	special BufferMonNickname
# 184 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherAllDone
# 185 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 186 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setflag FLAG_GOT_HAIRCUT
# 187 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 188 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 189 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 190 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Declined_Haircut1::
# 191 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherThatsAShame, MSGBOX_DEFAULT
# 192 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 193 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 194 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 195 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 196 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 197 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Already_Got_Haircut1::
# 198 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherOnePerDay, MSGBOX_DEFAULT
# 199 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 200 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 201 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 202 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 203 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_NotEnough_Haircut1::
# 204 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_OlderBrotherNeedMoreMoney, MSGBOX_DEFAULT
# 205 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 206 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 207 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 208 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 209 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 210 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 211 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Brother_Haircut2::
# 212 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 213 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	faceplayer
# 214 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_set FLAG_GOT_HAIRCUT, GoldenrodUnderground_EventScript_Already_Got_Haircut2
# 215 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	showmoneybox 0, 0
# 216 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherOffer, MSGBOX_YESNO
# 217 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, GoldenrodUnderground_EventScript_Haircut2
# 218 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherDisappointed, MSGBOX_DEFAULT
# 219 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 220 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 221 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 222 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 223 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Haircut2::
# 224 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherAskWhich
# 225 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	special ChoosePartyMon
# 226 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitstate
# 227 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	showmoneybox 0, 0
# 228 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 229 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	faceplayer
# 230 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_ge VAR_0x8004, PARTY_SIZE, GoldenrodUnderground_EventScript_Declined_Haircut2
# 231 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
# 232 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_EGG, GoldenrodUnderground_EventScript_Declined_Haircut2
# 233 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	checkmoney 300, 0
# 234 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodUnderground_EventScript_NotEnough_Haircut2
# 235 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	removemoney 300
# 236 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	updatemoneybox 0
# 237 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playse SE_SHOP
# 238 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherLookCool
# 239 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 240 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	fadescreen FADE_TO_BLACK
# 241 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playfanfare MUS_HEAL
# 242 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitfanfare
# 243 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	special HaircutBrother1
# 244 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 245 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	special BufferMonNickname
# 246 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherAllDone
# 247 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 248 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setflag FLAG_GOT_HAIRCUT
# 249 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 250 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 251 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 252 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Declined_Haircut2::
# 253 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherDisappointed, MSGBOX_DEFAULT
# 254 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 255 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 256 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 257 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 258 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 259 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_Already_Got_Haircut2::
# 260 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherOnePerDay, MSGBOX_DEFAULT
# 261 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 262 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 263 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 264 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 265 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_EventScript_NotEnough_Haircut2::
# 266 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_YoungerBrotherShortOnFunds, MSGBOX_DEFAULT
# 267 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 268 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	hidemoneybox
# 269 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 270 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 271 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 272 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 273 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_MapScript_TryOpenDoor::
# 274 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	call_if_set FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR, GoldenrodCity_UndergroundTunnel_MapScript_OpenDoor
# 275 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	return
# 276 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 277 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_MapScript_OpenDoor::
# 278 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setmetatile 12, 10, 0x45D, FALSE
# 279 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	return
# 280 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 281 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_EventScript_Door::
# 282 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 283 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_set FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR, GoldenrodCity_UndergroundTunnel_EventScript_DoorAlreadyOpened
# 284 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	checkitem ITEM_BASEMENT_KEY
# 285 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_UndergroundTunnel_EventScript_OpenDoor
# 286 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_DoorsLocked, MSGBOX_DEFAULT
# 287 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 288 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 289 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 290 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 291 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_EventScript_OpenDoor::
# 292 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_KeyOpenedDoor, MSGBOX_DEFAULT
# 293 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 294 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setflag FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
# 295 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setmetatile 12, 10, 0x45D, FALSE
# 296 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	playse SE_BANG
# 297 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	special DrawWholeMapView
# 298 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitse
# 299 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 300 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 301 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 302 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodCity_UndergroundTunnel_EventScript_DoorAlreadyOpened::
# 303 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox GoldenrodUnderground_Text_DoorIsOpen, MSGBOX_DEFAULT
# 304 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	closemessage
# 305 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 306 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 307 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 308 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_HerbShop_EventScript_Clerk::
# 309 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 310 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	faceplayer
# 311 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	message LavaridgeTown_HerbShop_Text_WelcomeToHerbShop
# 312 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmessage
# 313 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	pokemart GoldenrodUnderground_HerbShop_Pokemart
# 314 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 315 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
# 316 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	end
# 317 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 318 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.align 2
# 319 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_HerbShop_Pokemart:
# 320 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_ENERGY_POWDER
# 321 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_ENERGY_ROOT
# 322 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_HEAL_POWDER
# 323 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_REVIVAL_HERB
# 324 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_WITHERED_HERB
# 325 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_GRIMY_HERB
# 326 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_BRITTLE_HERB
# 327 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_GOOPY_HERB
# 328 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_DULL_HERB
# 329 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_SOGGY_HERB
# 330 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	pokemartlistend
# 331 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 332 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 333 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_YoungerBrotherOffer:
# 334 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Welcome to the Pokémon Salon!\p"
# 335 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I'm the younger and less expensive\n"
# 336 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "of the two Haircut Brothers.\p"
# 337 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I'll spiff up your Pokémon for just\n"
# 338 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "¥300.\p"
# 339 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "So? How about it?$"
# 340 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 341 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_YoungerBrotherAskWhich:
# 342 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Ok, which Pokémon should I do?$"
# 343 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 344 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_YoungerBrotherLookCool:
# 345 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Ok! I'll make it look cool!$"
# 346 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 347 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_YoungerBrotherAllDone:
# 348 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "There we go! All done!$"
# 349 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 350 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_YoungerBrotherDisappointed:
# 351 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "No? How disappointing!$"
# 352 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 353 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_YoungerBrotherShortOnFunds:
# 354 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "You're a little short on funds.$"
# 355 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 356 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_YoungerBrotherOnePerDay:
# 357 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I can do only one haircut a day.\p"
# 358 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Sorry, but I'm all done for today.$"
# 359 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 360 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 361 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 362 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_OlderBrotherOffer:
# 363 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Welcome!\p"
# 364 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I run the Pokémon Salon!\p"
# 365 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I'm the older and better of the two\n"
# 366 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Haircut Brothers.\p"
# 367 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I can make your Pokémon beautiful\n"
# 368 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "for just ¥500.\p"
# 369 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Would you like me to do that?$"
# 370 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 371 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_OlderBrotherAskWhich:
# 372 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Which Pokémon should I work on?$"
# 373 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 374 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_OlderBrotherWatchItBeautiful:
# 375 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Ok! Watch it become beautiful!$"
# 376 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 377 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_OlderBrotherAllDone:
# 378 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "There! All done!$"
# 379 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 380 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_OlderBrotherThatsAShame:
# 381 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Is that right? That's a shame!$"
# 382 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 383 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_OlderBrotherNeedMoreMoney:
# 384 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "You'll need more money than that.$"
# 385 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 386 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_OlderBrotherOnePerDay:
# 387 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I do only one haircut a day.\n"
# 388 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I'm done for today.$"
# 389 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 390 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_SupernerdEricSeen:
# 391 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I got booted out of the Game Corner.\p"
# 392 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I was trying to cheat using my\n"
# 393 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Pokémon…$"
# 394 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 395 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_SupernerdEricBeaten:
# 396 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "…Grumble…$"
# 397 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 398 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_SupernerdEricAfterBattle:
# 399 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I guess I have to do things fair and\n"
# 400 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "square…$"
# 401 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 402 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_SupernerdTeruSeen:
# 403 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Do you consider type alignments in\n"
# 404 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "battle?\p"
# 405 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "If you know your type advantages,\n"
# 406 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "you'll do better in battle.$"
# 407 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 408 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_SupernerdTeruBeaten:
# 409 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Ow, ow, ow!$"
# 410 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 411 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_SupernerdTeruAfterBattle:
# 412 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I know my Pokémon type alignments.\p"
# 413 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "But I only use one type of Pokémon.$"
# 414 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 415 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_PokemaniacIssacSeen:
# 416 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "My Pokémon just got a haircut!\p"
# 417 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I'll show you how strong it is!$"
# 418 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 419 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_PokemaniacIssacBeaten:
# 420 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Aiyeeee!$"
# 421 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 422 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_PokemaniacIssacAfterBattle:
# 423 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Your Pokémon will like you more if\n"
# 424 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "you give them haircuts.$"
# 425 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 426 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_PokemaniacDonaldSeen:
# 427 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "I think you have some rare Pokémon\n"
# 428 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "with you.\p"
# 429 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Let me see them!$"
# 430 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 431 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_PokemaniacDonaldBeaten:
# 432 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Gaah! I lost! That makes me mad!$"
# 433 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 434 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_PokemaniacDonaldAfterBattle:
# 435 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "When I was walking near the Bike\n"
# 436 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Shop last night, I felt like I was\l"
# 437 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "being watched from the rooftops...$"
# 438 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 439 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_PokemaniacDonaldAfterBattleOld:
# 440 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Are you making a Pokédex? Here's a\n"
# 441 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "hot tip.\p"
# 442 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "The Hiker on Route 33, Anthony, is a\n"
# 443 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "good guy.\p"
# 444 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "He'll phone you if he sees any rare\n"
# 445 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "Pokémon.$"
# 446 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 447 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_DoorsLocked:
# 448 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "The door's locked…$"
# 449 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 450 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_DoorIsOpen:
# 451 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "The door is open.$"
# 452 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 453 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_KeyOpenedDoor:
# 454 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "The Basement Key opened the door.$"
# 455 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"

# 456 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
GoldenrodUnderground_Text_NoEntry:
# 457 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
    .string "No Entry Beyond This Point$"

goldenrod_utility_shop_girl::
# 462 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 463 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox goldenrod_utility_shop_girl_Text_0
# 464 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmessage
# 465 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	pokemart goldenrod_utility_shop
# 466 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox goldenrod_utility_shop_girl_Text_1
# 467 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
	return


	.align 2
# 470 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
goldenrod_utility_shop:
# 471 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_UTILITY_UMBRELLA
# 472 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_COVERT_CLOAK
# 473 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_ABILITY_SHIELD
# 474 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_CLEAR_AMULET
# 475 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.2byte ITEM_AIR_BALLOON
	.2byte ITEM_NONE

suspiciousdoor_goldenrod_underground::
# 479 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 480 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	compare VAR_NEWBARK_TOWN_STATE, 12
	goto_if_lt suspiciousdoor_goldenrod_underground_2
# 487 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox suspiciousdoor_goldenrod_underground_Text_1
suspiciousdoor_goldenrod_underground_1:
# 492 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
	end

suspiciousdoor_goldenrod_underground_2:
# 481 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox suspiciousdoor_goldenrod_underground_Text_0
# 484 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	waitmessage
	goto suspiciousdoor_goldenrod_underground_1


rocket_bouncer::
# 497 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	lock
# 498 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	faceplayer
# 499 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	compare VAR_NEWBARK_TOWN_STATE, 12
	goto_if_ge rocket_bouncer_2
# 503 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox rocket_bouncer_Text_1
rocket_bouncer_1:
# 505 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	release
	end

rocket_bouncer_2:
# 500 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	msgbox rocket_bouncer_Text_0
	goto rocket_bouncer_1


Goldenrod_TryOpenRocketArcadeDoor::
# 510 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	setmetatile 12, 28, 0x45D, FALSE
	return


goldenrod_utility_shop_girl_Text_0:
# 463 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Hi, take a look at my exclusive wares!$"

goldenrod_utility_shop_girl_Text_1:
# 466 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Come on, buy some more!$"

suspiciousdoor_goldenrod_underground_Text_0:
# 481 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Door seems to be locked, but you can \n"
	.string "faintly discern noise coming from \l"
	.string "somewhere far behind the door.$"

suspiciousdoor_goldenrod_underground_Text_1:
# 487 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "The door is now open. \p"
	.string "A cacophony of noises is echoing from \n"
	.string "the tunnel.$"

rocket_bouncer_Text_0:
# 500 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Welcome,\n"
	.string "Boss told to me to let you pass.$"

rocket_bouncer_Text_1:
# 503 "data/maps/GoldenrodCity_UndergroundTunnel/scripts.pory"
	.string "Sorry kid, only those with special\n"
	.string "permission are allowed past here.$"
