# 1 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 2 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_MapScripts::
# 3 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.byte 0
# 4 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 5 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_Grunt::
# 6 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	lock
# 7 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	faceplayer
# 8 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_GruntM3Seen, MSGBOX_DEFAULT
# 9 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	trainerbattle_no_intro TRAINER_GRUNT_2,  RadioTower1F_Text_GruntM3Beaten
# 10 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_GruntM3After, MSGBOX_AUTOCLOSE
# 11 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	turnobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT, DIR_EAST
# 12 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	applymovement LOCALID_GOLDENROD_RADIOTOWER_GRUNT, RadioTower1F_Movement_Rocket
# 13 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	waitmovement 0
# 14 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	playse SE_EXIT
# 15 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	removeobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT
# 16 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
# 17 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 18 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 19 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 20 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Movement_Rocket::
# 21 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_in_place_right
# 22 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	step_end
# 23 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 24 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_Lass::
# 25 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	lock
# 26 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	faceplayer
# 27 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_Lass, MSGBOX_DEFAULT
# 28 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 29 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 30 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 31 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 32 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_Youngster::
# 33 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	lock
# 34 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	faceplayer
# 35 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_Youngster, MSGBOX_DEFAULT
# 36 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 37 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 38 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 39 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 40 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_Whitney::
# 41 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	lock
# 42 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	faceplayer
# 43 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_Whitney1, MSGBOX_DEFAULT
# 44 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 45 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_SOUTH
# 46 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 47 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 48 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 49 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_Whitney1::
# 50 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Whitney: Hi!\p"
# 51 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "My name is Whitney!\p"
# 52 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "I heard about the Radio Quiz and\n"
# 53 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "its special prize, so I came here\l"
# 54 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "to enter...\p"
# 55 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "But this Quiz is so hard!$"
# 56 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 57 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_Whitney2::
# 58 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Whitney: Wow, you did it!\p"
# 59 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "I thought the answer to the third\n"
# 60 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "question was surely apricorns!\l"
# 61 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Oops!\p"
# 62 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "It's time to go back to the Gym!$"
# 63 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 64 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_Reception::
# 65 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	lock
# 66 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	faceplayer
# 67 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_ReceptionistWelcome, MSGBOX_DEFAULT
# 68 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	checkitem ITEM_RADIO
# 69 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ExchangeLegacyRadio
# 70 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_unset FLAG_ENABLE_RADIO, RadioTower1F_EventScript_ReceptionOfferQuiz
# 71 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto RadioTowerReceiptionist
# 72 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 73 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 74 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 75 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 76 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ExchangeLegacyRadio::
# 77 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	checkitem ITEM_VS_SEEKER
# 78 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ExchangeLegacyRadioForBigNugget
# 79 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_ExchangeLegacyRadioForVsSeeker, MSGBOX_DEFAULT
# 80 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	removeitem ITEM_RADIO
# 81 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	giveitem ITEM_VS_SEEKER
# 82 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	special MigrateLegacyRadioShortcut
# 83 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setflag FLAG_ENABLE_RADIO
# 84 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_LegacyExchangeComplete, MSGBOX_DEFAULT
# 85 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 86 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 87 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 88 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 89 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ExchangeLegacyRadioForBigNugget::
# 90 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	checkitemspace ITEM_BIG_NUGGET
# 91 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_LegacyExchangeNoRoom
# 92 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_ExchangeLegacyRadioForBigNugget, MSGBOX_DEFAULT
# 93 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	removeitem ITEM_RADIO
# 94 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	giveitem ITEM_BIG_NUGGET
# 95 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	special MigrateLegacyRadioShortcut
# 96 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setflag FLAG_ENABLE_RADIO
# 97 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_LegacyExchangeComplete, MSGBOX_DEFAULT
# 98 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 99 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 100 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 101 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 102 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_LegacyExchangeNoRoom::
# 103 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_LegacyExchangeNoRoom, MSGBOX_DEFAULT
# 104 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 105 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 106 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 107 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 108 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ReceptionOfferQuiz::
# 109 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_RadioCardWomanOfferQuiz, MSGBOX_YESNO
# 110 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz1
# 111 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_DeclineQuiz, MSGBOX_DEFAULT
# 112 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 113 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 114 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 115 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 116 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ReceptionQuiz1::
# 117 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_QuizQuestion1, MSGBOX_YESNO
# 118 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz2
# 119 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
# 120 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 121 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 122 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 123 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 124 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ReceptionQuiz2::
# 125 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_QuizQuestion2, MSGBOX_YESNO
# 126 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionQuiz3
# 127 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
# 128 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 129 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 130 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 131 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 132 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ReceptionQuiz3::
# 133 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_QuizQuestion3, MSGBOX_YESNO
# 134 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionQuiz4
# 135 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
# 136 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 137 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 138 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 139 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 140 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ReceptionQuiz4::
# 141 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_QuizQuestion4, MSGBOX_YESNO
# 142 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz5
# 143 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
# 144 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 145 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 146 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 147 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 148 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ReceptionQuiz5::
# 149 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_QuizQuestion5, MSGBOX_YESNO
# 150 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionGivePrize
# 151 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
# 152 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 153 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 154 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 155 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 156 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_ReceptionGivePrize::
# 157 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_QuizWin, MSGBOX_DEFAULT
# 158 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 159 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	giveitem ITEM_VS_SEEKER
# 160 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_QuizPrizeNoRoom
# 161 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 162 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	playse SE_PIN
# 163 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	applymovement LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, Common_Movement_ExclamationMark
# 164 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	delay 60
# 165 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_EAST
# 166 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	delay 20
# 167 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 168 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	createfieldmugshot MUGSHOT_WHITNEY
# 169 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_Whitney2, MSGBOX_DEFAULT
# 170 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 171 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	applymovement LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave
# 172 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	waitmovement 0
# 173 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	playse SE_EXIT
# 174 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	removeobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY
# 175 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setflag FLAG_ENABLE_RADIO
# 176 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setflag FLAG_HIDE_GOLDENROD_BEAUTY
# 177 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setvar VAR_GOLDENROD_CITY_STATE, 2
# 178 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 179 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 180 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 181 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_EventScript_QuizPrizeNoRoom::
# 182 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_QuizPrizeNoRoom, MSGBOX_DEFAULT
# 183 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 184 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 185 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 186 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 187 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave:
# 188 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	face_left
# 189 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_left
# 190 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_left
# 191 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_left
# 192 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_left
# 193 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_down
# 194 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_down
# 195 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	walk_in_place_down
# 196 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	step_end
# 197 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 198 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_Sign::
# 199 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	lock
# 200 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTower1F_Text_Directory, MSGBOX_SIGN
# 201 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	closemessage
# 202 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 203 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 204 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 205 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_ReceptionistWelcome:
# 206 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Welcome!$"
# 207 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 208 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_ReceptionistNoTours:
# 209 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "I'm sorry, but we're not\n"
# 210 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "offering any tours today.$"
# 211 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 212 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_ExchangeLegacyRadioForVsSeeker:
# 213 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Oh! You still have one of our old\n"
# 214 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "standalone Radios.\p"
# 215 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Radio reception is now built into\n"
# 216 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "every Pokégear, so we'll replace it\l"
# 217 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "with a Vs. Seeker.$"
# 218 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 219 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_ExchangeLegacyRadioForBigNugget:
# 220 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Oh! You still have one of our old\n"
# 221 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "standalone Radios.\p"
# 222 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "You already own its replacement, so\n"
# 223 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "please accept a Big Nugget instead.$"
# 224 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 225 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_LegacyExchangeComplete:
# 226 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Thank you for returning the old\n"
# 227 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "model. Please enjoy our broadcasts!$"
# 228 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 229 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_LegacyExchangeNoRoom:
# 230 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "I'd like to exchange that old Radio,\n"
# 231 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "but your Items Pocket is full.\p"
# 232 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Please make room and speak to me\n"
# 233 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "again.$"
# 234 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 235 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_RadioCardWomanOfferQuiz:
# 236 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "We have a special quiz campaign on\n"
# 237 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "right now.\p"
# 238 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Answer five questions correctly to\n"
# 239 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "win a Vs. Seeker.\p"
# 240 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "It lets you challenge route Trainers\n"
# 241 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "again after recharged by walking.\p"
# 242 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Would you like to take the quiz?$"
# 243 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 244 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_QuizQuestion1:
# 245 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Question 1:\p"
# 246 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Is there a Pokémon that appears only\n"
# 247 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "in the daytime?$"
# 248 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 249 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_QuizQuestion2:
# 250 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Correct!\n"
# 251 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Question 2:\p"
# 252 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Is this statement correct?\p"
# 253 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "You can't buy a Berry at a Mart.$"
# 254 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 255 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_QuizQuestion3:
# 256 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Bull's-eye!\n"
# 257 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Question 3:\p"
# 258 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Kurt, the Poké Ball creator, uses\n"
# 259 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "apricorns as ingredients?$"
# 260 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 261 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_QuizQuestion4:
# 262 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "So far so good!\n"
# 263 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Question 4:\p"
# 264 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Is Falkner the Violet Gym Leader\n"
# 265 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "who uses bird Pokémon?$"
# 266 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 267 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_QuizQuestion5:
# 268 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Wow! Right again!\n"
# 269 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Here's the final question:\p"
# 270 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Do Goldenrod Game Corner's slots\n"
# 271 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "have Charmander on their reels?$"
# 272 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 273 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_QuizWin:
# 274 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Bingo! You got it!\n"
# 275 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Congratulations!\p"
# 276 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Here's your prize, a Vs. Seeker!$"
# 277 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 278 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_TuneIn:
# 279 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "The Radio is already built into your\n"
# 280 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Pokégear.\p"
# 281 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Buena's Password airs every day\n"
# 282 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "from 6 PM to midnight!$"
# 283 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 284 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_QuizPrizeNoRoom:
# 285 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Oh, your Key Items Pocket is full.\p"
# 286 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Please make room, then take the quiz\n"
# 287 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "again to receive your prize.$"
# 288 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 289 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_WrongAnswer:
# 290 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Oh, dear.\n"
# 291 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Sorry, but you got it wrong.\p"
# 292 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Please try again!$"
# 293 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 294 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_DeclineQuiz:
# 295 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Oh. I see. Please see me if you\n"
# 296 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "change your mind.$"
# 297 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 298 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_Lass:
# 299 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Ben is a fabulous Dj.\p"
# 300 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "His sweet voice makes me melt!$"
# 301 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 302 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_Youngster:
# 303 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "I love Mary, from Pokémon Talk.\p"
# 304 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "I only know what she sounds like,\n"
# 305 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "though.$"
# 306 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 307 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_GruntM3Seen:
# 308 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "We've finally taken over the\n"
# 309 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Radio Tower!\p"
# 310 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Now everyone will get to experience\n"
# 311 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "the true terror of Team Rocket!\p"
# 312 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "We'll show you how scary we are!$"
# 313 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 314 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_GruntM3Beaten:
# 315 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Too strong! I'm sorry boss…$"
# 316 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 317 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_GruntM3After:
# 318 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "You're too strong.\p"
# 319 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "Our plan could be ruined. I must\n"
# 320 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "warn the others…$"
# 321 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 322 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
RadioTower1F_Text_Directory:
# 323 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "1F Reception\n"
# 324 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "2F Sales\p"
# 325 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "3F Personnel\n"
# 326 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "4F Production\p"
# 327 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
    .string "5F Director's Office$"
# 328 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 329 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 330 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_LotteryClerk::
# 331 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	lock
# 332 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	faceplayer
# 333 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	dotimebasedevents
# 334 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_ne VAR_POKELOT_PRIZE_ITEM, ITEM_NONE, GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier
# 335 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_set FLAG_DAILY_PICKED_LOTO_TICKET, GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow
# 336 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket, MSGBOX_YESNO
# 337 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain
# 338 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setflag FLAG_DAILY_PICKED_LOTO_TICKET
# 339 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	message GoldenrodCity_RadioTower_1F_Text_PleasePickTicket
# 340 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	waitmessage
# 341 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	special RetrieveLotteryNumber
# 342 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	copyvar VAR_0x8008, VAR_RESULT
# 343 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	special BufferLottoTicketNumber
# 344 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait, MSGBOX_DEFAULT
# 345 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	applymovement 4, Common_Movement_WalkInPlaceFasterRight
# 346 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	waitmovement 0
# 347 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	playse SE_PC_ON
# 348 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	@special DoLotteryCornerComputerEffect
# 349 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	special PickLotteryCornerTicket
# 350 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	delay 220
# 351 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	@special EndLotteryCornerComputerEffect
# 352 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	delay 10
# 353 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	applymovement 4, Common_Movement_FacePlayer
# 354 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	waitmovement 0
# 355 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_0x8004, 0, GoldenrodCity_RadioTower_1F_EventScript_NoMatch
# 356 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	incrementgamestat GAME_STAT_WON_POKEMON_LOTTERY
# 357 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	call_if_eq VAR_0x8006, 0, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon
# 358 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	call_if_eq VAR_0x8006, 1, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon
# 359 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	bufferitemname STR_VAR_1, VAR_0x8005
# 360 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	call_if_eq VAR_0x8004, 1, GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch
# 361 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	call_if_eq VAR_0x8004, 2, GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch
# 362 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	call_if_eq VAR_0x8004, 3, GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch
# 363 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	call_if_eq VAR_0x8004, 4, GoldenrodCity_RadioTower_1F_EventScript_FullMatch
# 364 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	giveitem VAR_0x8005
# 365 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom
# 366 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	special TryPutLotteryWinnerReportOnAir
# 367 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
# 368 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 369 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 370 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon::
# 371 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon, MSGBOX_DEFAULT
# 372 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	return
# 373 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 374 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon::
# 375 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon, MSGBOX_DEFAULT
# 376 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	return
# 377 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 378 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow::
# 379 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow, MSGBOX_DEFAULT
# 380 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 381 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 382 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 383 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain::
# 384 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain, MSGBOX_DEFAULT
# 385 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 386 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 387 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 388 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_NoMatch::
# 389 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched, MSGBOX_DEFAULT
# 390 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
# 391 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 392 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 393 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2::
# 394 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2, MSGBOX_DEFAULT
# 395 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 396 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 397 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 398 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch::
# 399 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched, MSGBOX_DEFAULT
# 400 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	return
# 401 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 402 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch::
# 403 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched, MSGBOX_DEFAULT
# 404 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	return
# 405 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 406 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch::
# 407 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched, MSGBOX_DEFAULT
# 408 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	return
# 409 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 410 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_FullMatch::
# 411 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched, MSGBOX_DEFAULT
# 412 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	return
# 413 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 414 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom::
# 415 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	copyvar VAR_POKELOT_PRIZE_PLACE, VAR_0x8004
# 416 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	copyvar VAR_POKELOT_PRIZE_ITEM, VAR_0x8005
# 417 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
# 418 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 419 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 420 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize::
# 421 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_NoRoomForThis, MSGBOX_DEFAULT
# 422 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 423 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 424 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 425 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier::
# 426 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding, MSGBOX_DEFAULT
# 427 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	giveitem VAR_POKELOT_PRIZE_ITEM
# 428 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
# 429 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	copyvar VAR_0x8004, VAR_POKELOT_PRIZE_PLACE
# 430 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	copyvar VAR_0x8005, VAR_POKELOT_PRIZE_ITEM
# 431 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	special TryPutLotteryWinnerReportOnAir
# 432 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setvar VAR_POKELOT_PRIZE_ITEM, ITEM_NONE
# 433 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	setvar VAR_POKELOT_PRIZE_PLACE, 0
# 434 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
# 435 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	end
# 436 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 437 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket:
# 438 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "This is the Pokémon Lottery Corner.\p"
# 439 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "If the Loto Ticket's number matches\n"
# 440 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "the Id number of any of your Pokémon,\l"
# 441 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "you will receive a fabulous gift.\p"
# 442 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Would you like to draw a Pokémon\n"
# 443 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Loto Ticket?$"
# 444 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 445 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow:
# 446 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Please come back tomorrow.$"
# 447 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 448 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain:
# 449 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Please do visit again.$"
# 450 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 451 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_PleasePickTicket:
# 452 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Please pick a Loto Ticket.\n"
# 453 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}$"
# 454 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 455 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait:
# 456 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "The Loto Ticket number is {STR_VAR_1}.\p"
# 457 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "I need to run a check on this number\n"
# 458 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "to see if it matches any of your\l"
# 459 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Pokémon's Id numbers. Please wait.$"
# 460 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 461 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon:
# 462 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Congratulations!\p"
# 463 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "The Id number of your team's\n"
# 464 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "{STR_VAR_1} matches your\l"
# 465 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Loto Ticket's number!$"
# 466 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 467 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon:
# 468 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Congratulations!\p"
# 469 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "The Id number of your PC-boxed\n"
# 470 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "{STR_VAR_1} matches your\l"
# 471 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Loto Ticket's number!$"
# 472 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 473 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched:
# 474 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "I'm sorry.\n"
# 475 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "None of the numbers matched.$"
# 476 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 477 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched:
# 478 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Two digits matched, so you win the\n"
# 479 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "third prize!\l"
# 480 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "You've won the {STR_VAR_1}!$"
# 481 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 482 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched:
# 483 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Three digits matched, so you win the\n"
# 484 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "second prize!\l"
# 485 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "You've won the {STR_VAR_1}!$"
# 486 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 487 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched:
# 488 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Four digits matched, so you win the\n"
# 489 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "first prize!\l"
# 490 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "You've won the {STR_VAR_1}!$"
# 491 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 492 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched:
# 493 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Oh, my goodness, all five digits\n"
# 494 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "matched!\p"
# 495 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "You've won the jackpot prize!\n"
# 496 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "You've won the {STR_VAR_1}!$"
# 497 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 498 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_NoRoomForThis:
# 499 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Oh?\n"
# 500 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "You seem to have no room for this.\p"
# 501 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Please make room in your Bag and\n"
# 502 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "let me know.$"
# 503 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 504 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding:
# 505 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "{PLAYER}?\n"
# 506 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Yes, I've been expecting you.\p"
# 507 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "This is the prize we've been holding\n"
# 508 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "for you.$"
# 509 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"

# 510 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2:
# 511 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Please do visit again.$"

RadioTowerReceiptionist::
# 517 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	compare VAR_GOLDENROD_CITY_STATE, 6
	goto_if_ge RadioTowerReceiptionist_4
RadioTowerReceiptionist_3:
# 522 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTowerReceiptionist_Text_1
RadioTowerReceiptionist_1:
# 525 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	release
	end

RadioTowerReceiptionist_2:
# 519 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	msgbox RadioTowerReceiptionist_Text_0
	goto RadioTowerReceiptionist_1

RadioTowerReceiptionist_4:
# 518 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	compare VAR_GOLDENROD_CITY_STATE, 10
	goto_if_lt RadioTowerReceiptionist_2
	goto RadioTowerReceiptionist_3


RadioTowerReceiptionist_Text_0:
# 519 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "Wait no, Help! \n"
	.string "Where's the police?$"

RadioTowerReceiptionist_Text_1:
# 522 "data/maps/GoldenrodCity_RadioTower_1F/scripts.pory"
	.string "I'm sorry, but we're not\n"
	.string "offering any tours today.$"
