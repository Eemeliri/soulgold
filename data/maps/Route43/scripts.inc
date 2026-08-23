# 1 "data/maps/Route43/scripts.pory"

# 2 "data/maps/Route43/scripts.pory"
.set LOCALID_R43_EXPERT, 3
# 3 "data/maps/Route43/scripts.pory"

# 4 "data/maps/Route43/scripts.pory"
Route43_MapScripts::
# 5 "data/maps/Route43/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route43_MapScript_OnTransition
# 6 "data/maps/Route43/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 7 "data/maps/Route43/scripts.pory"
	.byte 0
# 8 "data/maps/Route43/scripts.pory"

# 9 "data/maps/Route43/scripts.pory"
Route43_MapScript_OnTransition::
# 10 "data/maps/Route43/scripts.pory"
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
# 11 "data/maps/Route43/scripts.pory"
	callnative SetTimeBasedEncounters
# 12 "data/maps/Route43/scripts.pory"
	end
# 13 "data/maps/Route43/scripts.pory"

# 14 "data/maps/Route43/scripts.pory"
Route43_EventScript_Brent::
# 15 "data/maps/Route43/scripts.pory"
	trainerbattle_single TRAINER_BRENT Route43_Text_PokemaniacBrentSeen, Route43_Text_PokemaniacBrentBeaten
# 16 "data/maps/Route43/scripts.pory"
	msgbox Route43_Text_PokemaniacBrentAfter, MSGBOX_AUTOCLOSE
# 17 "data/maps/Route43/scripts.pory"
	end
# 18 "data/maps/Route43/scripts.pory"

# 19 "data/maps/Route43/scripts.pory"
Route43_EventScript_Ron::
# 20 "data/maps/Route43/scripts.pory"
	trainerbattle_single TRAINER_RON Route43_Text_PokemaniacRonSeen, Route43_Text_PokemaniacRonBeaten
# 21 "data/maps/Route43/scripts.pory"
	msgbox Route43_Text_PokemaniacRonAfter, MSGBOX_AUTOCLOSE
# 22 "data/maps/Route43/scripts.pory"
	end
# 23 "data/maps/Route43/scripts.pory"

# 24 "data/maps/Route43/scripts.pory"
Route43_EventScript_Marvin::
# 25 "data/maps/Route43/scripts.pory"
	trainerbattle_single TRAINER_MARVIN Route43_Text_FisherMarvinSeen, Route43_Text_FisherMarvinBeaten
# 26 "data/maps/Route43/scripts.pory"
	msgbox Route43_Text_FisherMarvinAfter, MSGBOX_AUTOCLOSE
# 27 "data/maps/Route43/scripts.pory"
	end
# 28 "data/maps/Route43/scripts.pory"
	
# 29 "data/maps/Route43/scripts.pory"
Route43_EventScript_Spencer::
# 30 "data/maps/Route43/scripts.pory"
	trainerbattle_single TRAINER_SPENCER Route43_Text_CamperSpencerSeen, Route43_Text_CamperSpencerBeaten
# 31 "data/maps/Route43/scripts.pory"
	msgbox Route43_Text_CamperSpencerAfter, MSGBOX_AUTOCLOSE
# 32 "data/maps/Route43/scripts.pory"
	end
# 33 "data/maps/Route43/scripts.pory"

# 34 "data/maps/Route43/scripts.pory"
Route43_EventScript_Tiffany::
# 35 "data/maps/Route43/scripts.pory"
	trainerbattle_single TRAINER_TIFFANY Route43_Text_PicnickerTiffanySeen, Route43_Text_PicnickerTiffanyBeaten
# 36 "data/maps/Route43/scripts.pory"
	msgbox Route43_Text_PicnickerTiffanyWantsPicnic, MSGBOX_AUTOCLOSE
# 37 "data/maps/Route43/scripts.pory"
	end
# 38 "data/maps/Route43/scripts.pory"

# 39 "data/maps/Route43/scripts.pory"
Route43_EventScript_Sign1::
# 40 "data/maps/Route43/scripts.pory"
	msgbox Route43_Sign2, MSGBOX_SIGN
# 41 "data/maps/Route43/scripts.pory"
	end
# 42 "data/maps/Route43/scripts.pory"

# 43 "data/maps/Route43/scripts.pory"
Route43_EventScript_Sign2::
# 44 "data/maps/Route43/scripts.pory"
	msgbox Route43_TrainerTips, MSGBOX_SIGN
# 45 "data/maps/Route43/scripts.pory"
	end
# 46 "data/maps/Route43/scripts.pory"

# 47 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacBenSeen:
# 48 "data/maps/Route43/scripts.pory"
    .string "I love Pokémon!\p"
# 49 "data/maps/Route43/scripts.pory"
    .string "That's why I started--and why I'll\n"
# 50 "data/maps/Route43/scripts.pory"
    .string "keep on collecting Pokémon!$"
# 51 "data/maps/Route43/scripts.pory"

# 52 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacBenBeaten:
# 53 "data/maps/Route43/scripts.pory"
    .string "How could you do this to me?$"
# 54 "data/maps/Route43/scripts.pory"

# 55 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacBenAfter:
# 56 "data/maps/Route43/scripts.pory"
    .string "What else do I like besides\n"
# 57 "data/maps/Route43/scripts.pory"
    .string "Pokémon?\p"
# 58 "data/maps/Route43/scripts.pory"
    .string "Mary on the radio. I bet she's\n"
# 59 "data/maps/Route43/scripts.pory"
    .string "cute!$"
# 60 "data/maps/Route43/scripts.pory"

# 61 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacBrentSeen:
# 62 "data/maps/Route43/scripts.pory"
    .string "Hey! Do you have any rare\n"
# 63 "data/maps/Route43/scripts.pory"
    .string "Pokémon?$"
# 64 "data/maps/Route43/scripts.pory"

# 65 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacBrentBeaten:
# 66 "data/maps/Route43/scripts.pory"
    .string "Oh, my poor Pokémon! Darlings!$"
# 67 "data/maps/Route43/scripts.pory"

# 68 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacBrentAfter:
# 69 "data/maps/Route43/scripts.pory"
    .string "I'd be happy just to own a single\n"
# 70 "data/maps/Route43/scripts.pory"
    .string "rare Pokémon.$"
# 71 "data/maps/Route43/scripts.pory"

# 72 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacRonSeen:
# 73 "data/maps/Route43/scripts.pory"
    .string "Would you get this?\p"
# 74 "data/maps/Route43/scripts.pory"
    .string "Some Silver guy made fun of my\n"
# 75 "data/maps/Route43/scripts.pory"
    .string "Pokémon!\p"
# 76 "data/maps/Route43/scripts.pory"
    .string "Darn it! My Pokémon's great!$"
# 77 "data/maps/Route43/scripts.pory"

# 78 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacRonBeaten:
# 79 "data/maps/Route43/scripts.pory"
    .string "My Nidoking did pretty right on!$"
# 80 "data/maps/Route43/scripts.pory"

# 81 "data/maps/Route43/scripts.pory"
Route43_Text_PokemaniacRonAfter:
# 82 "data/maps/Route43/scripts.pory"
    .string "It's okay for people to like\n"
# 83 "data/maps/Route43/scripts.pory"
    .string "different types of Pokémon.\p"
# 84 "data/maps/Route43/scripts.pory"
    .string "Pokémon isn't just about having the\n"
# 85 "data/maps/Route43/scripts.pory"
    .string "most powerful one.$"
# 86 "data/maps/Route43/scripts.pory"

# 87 "data/maps/Route43/scripts.pory"
Route43_Text_FisherMarvinSeen:
# 88 "data/maps/Route43/scripts.pory"
    .string "I'm in a slump.\p"
# 89 "data/maps/Route43/scripts.pory"
    .string "Maybe it's the gear I'm using.\p"
# 90 "data/maps/Route43/scripts.pory"
    .string "Let's battle for a change of pace!$"
# 91 "data/maps/Route43/scripts.pory"

# 92 "data/maps/Route43/scripts.pory"
Route43_Text_FisherMarvinBeaten:
# 93 "data/maps/Route43/scripts.pory"
    .string "I lost, but I feel better anyway.$"
# 94 "data/maps/Route43/scripts.pory"

# 95 "data/maps/Route43/scripts.pory"
Route43_Text_FisherMarvinAfter:
# 96 "data/maps/Route43/scripts.pory"
    .string "Kurt's Lure Ball is the best for\n"
# 97 "data/maps/Route43/scripts.pory"
    .string "catching hooked Pokémon.\p"
# 98 "data/maps/Route43/scripts.pory"
    .string "It's much more effective than a\n"
# 99 "data/maps/Route43/scripts.pory"
    .string "Ultra Ball.$"
# 100 "data/maps/Route43/scripts.pory"

# 101 "data/maps/Route43/scripts.pory"
Route43_Text_CamperSpencerSeen:
# 102 "data/maps/Route43/scripts.pory"
    .string "I can do so much with my\n"
# 103 "data/maps/Route43/scripts.pory"
    .string "Pokémon--it's super-fun!$"
# 104 "data/maps/Route43/scripts.pory"

# 105 "data/maps/Route43/scripts.pory"
Route43_Text_CamperSpencerBeaten:
# 106 "data/maps/Route43/scripts.pory"
    .string "Losing isn't fun at all…$"
# 107 "data/maps/Route43/scripts.pory"

# 108 "data/maps/Route43/scripts.pory"
Route43_Text_CamperSpencerAfter:
# 109 "data/maps/Route43/scripts.pory"
    .string "What is going on at Lake Of Rage?\p"
# 110 "data/maps/Route43/scripts.pory"
    .string "We were planning to camp there.$"
# 111 "data/maps/Route43/scripts.pory"

# 112 "data/maps/Route43/scripts.pory"
Route43_Text_PicnickerTiffanySeen:
# 113 "data/maps/Route43/scripts.pory"
    .string "Are you going to Lake Of Rage too?\p"
# 114 "data/maps/Route43/scripts.pory"
    .string "Let's play for a little while!$"
# 115 "data/maps/Route43/scripts.pory"

# 116 "data/maps/Route43/scripts.pory"
Route43_Text_PicnickerTiffanyBeaten:
# 117 "data/maps/Route43/scripts.pory"
    .string "I played too much!$"
# 118 "data/maps/Route43/scripts.pory"

# 119 "data/maps/Route43/scripts.pory"
Route43_Text_PicnickerTiffanyWantsPicnic:
# 120 "data/maps/Route43/scripts.pory"
    .string "I'm having a picnic with Pokémon.\p"
# 121 "data/maps/Route43/scripts.pory"
    .string "Won't you join us?$"
# 122 "data/maps/Route43/scripts.pory"

# 123 "data/maps/Route43/scripts.pory"
Route43_Sign1:
# 124 "data/maps/Route43/scripts.pory"
    .string "Route 43\p"
# 125 "data/maps/Route43/scripts.pory"
    .string "Lake Of Rage - Mahogany Town$"
# 126 "data/maps/Route43/scripts.pory"

# 127 "data/maps/Route43/scripts.pory"
Route43_Sign2:
# 128 "data/maps/Route43/scripts.pory"
    .string "Route 43\p"
# 129 "data/maps/Route43/scripts.pory"
    .string "Lake Of Rage - Mahogany Town$"
# 130 "data/maps/Route43/scripts.pory"

# 131 "data/maps/Route43/scripts.pory"
Route43_TrainerTips:
# 132 "data/maps/Route43/scripts.pory"
    .string "Trainer Tips\p"
# 133 "data/maps/Route43/scripts.pory"
    .string "All Pokémon have pros and cons\n"
# 134 "data/maps/Route43/scripts.pory"
    .string "depending on their types.\p"
# 135 "data/maps/Route43/scripts.pory"
    .string "If their types differ, a higher-\n"
# 136 "data/maps/Route43/scripts.pory"
    .string "level Pokémon may lose in battle.\p"
# 137 "data/maps/Route43/scripts.pory"
    .string "Learn which types are strong and\n"
# 138 "data/maps/Route43/scripts.pory"
    .string "weak against your Pokémon's type.$"

Route43Expert::
# 142 "data/maps/Route43/scripts.pory"
	lock
# 143 "data/maps/Route43/scripts.pory"
	faceplayer
# 144 "data/maps/Route43/scripts.pory"
	goto_if_set FLAG_ROUTE43_EXPERT, Route43Expert_2
# 153 "data/maps/Route43/scripts.pory"
	msgbox Route43Expert_Text_1
# 162 "data/maps/Route43/scripts.pory"
	goto_if_set FLAG_ROUTE43_EXPERT_QUALIFIED, Route43Expert_5
# 162 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_BRENT
	goto_if 1, Route43Expert_9
Route43Expert_4:
# 193 "data/maps/Route43/scripts.pory"
	release
	end

Route43Expert_2:
# 145 "data/maps/Route43/scripts.pory"
	setflag FLAG_ROUTE43_EXPERT_QUALIFIED
# 146 "data/maps/Route43/scripts.pory"
	msgbox Route43Expert_Text_0
# 149 "data/maps/Route43/scripts.pory"
	release
	end

Route43Expert_5:
# 172 "data/maps/Route43/scripts.pory"
	setflag FLAG_ROUTE43_EXPERT_QUALIFIED
# 173 "data/maps/Route43/scripts.pory"
	playse SE_PIN
# 174 "data/maps/Route43/scripts.pory"
	applymovement LOCALID_R43_EXPERT, Common_Movement_ExclamationMark
# 175 "data/maps/Route43/scripts.pory"
	waitse
# 176 "data/maps/Route43/scripts.pory"
	msgbox Route43Expert_Text_2
# 180 "data/maps/Route43/scripts.pory"
	trainerbattle_no_intro TRAINER_HERB_EXPERT, Route43Expert_Text_3
# 181 "data/maps/Route43/scripts.pory"
	msgbox Route43Expert_Text_4
# 184 "data/maps/Route43/scripts.pory"
	giveitem ITEM_POWER_HERB
# 185 "data/maps/Route43/scripts.pory"
	giveitem ITEM_WHITE_HERB
# 186 "data/maps/Route43/scripts.pory"
	setflag FLAG_ROUTE43_EXPERT
# 187 "data/maps/Route43/scripts.pory"
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
# 188 "data/maps/Route43/scripts.pory"
	special Achievement_CheckAll
# 189 "data/maps/Route43/scripts.pory"
	msgbox Route43Expert_Text_0
	goto Route43Expert_4

Route43Expert_8:
# 164 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_MARVIN
	goto_if 1, Route43Expert_13
	goto Route43Expert_4

Route43Expert_9:
# 163 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_RON
	goto_if 1, Route43Expert_8
	goto Route43Expert_4

Route43Expert_12:
# 166 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_TIFFANY
	goto_if 1, Route43Expert_17
	goto Route43Expert_4

Route43Expert_13:
# 165 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_SPENCER
	goto_if 1, Route43Expert_12
	goto Route43Expert_4

Route43Expert_16:
# 169 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_RAYMOND
	goto_if 1, Route43Expert_21
	goto Route43Expert_4

Route43Expert_17:
# 168 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_ANDRE
	goto_if 1, Route43Expert_16
	goto Route43Expert_4

Route43Expert_20:
# 171 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_LOIS
	goto_if 1, Route43Expert_5
	goto Route43Expert_4

Route43Expert_21:
# 170 "data/maps/Route43/scripts.pory"
	checktrainerflag TRAINER_AARON
	goto_if 1, Route43Expert_20
	goto Route43Expert_4


Route43Expert_Text_0:
# 146 "data/maps/Route43/scripts.pory"
	.string "Power Herb and White Herb only\n"
	.string "work once per battle, but they\l"
	.string "regrow back after it.$"

Route43Expert_Text_1:
# 153 "data/maps/Route43/scripts.pory"
	.string "Many trainers gather here to see\n"
	.string "what the fuss is about.\p"
	.string "Me? I'm here to find the strongest\n"
	.string "trainer among them.\p"
	.string "Perhaps if you were to defeat all\n"
	.string "the others here and around the\l"
	.string "Lake of Rage, we could have a bout.$"

Route43Expert_Text_2:
# 176 "data/maps/Route43/scripts.pory"
	.string "Impressive battling prowess!\p"
	.string "But can you turn the tides against\n"
	.string "my strategy?$"

Route43Expert_Text_3:
# 180 "data/maps/Route43/scripts.pory"
	.string "I could not turn the situation around.$"

Route43Expert_Text_4:
# 181 "data/maps/Route43/scripts.pory"
	.string "Your strength is in full bloom.\n"
	.string "Take these herbs and use them\l"
	.string "to turn the battle around.$"
