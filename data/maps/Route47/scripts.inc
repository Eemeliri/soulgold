# 1 "data/maps/Route47/scripts.pory"

# 2 "data/maps/Route47/scripts.pory"
Route47_MapScripts::
# 3 "data/maps/Route47/scripts.pory"
	.byte 0
# 4 "data/maps/Route47/scripts.pory"

# 5 "data/maps/Route47/scripts.pory"

# 6 "data/maps/Route47/scripts.pory"
Route47_EventScript_Hiker::
# 7 "data/maps/Route47/scripts.pory"
	trainerbattle_single TRAINER_DEVIN, Route47_Text_HikerSeen, Route47_Text_HikerBeaten
# 8 "data/maps/Route47/scripts.pory"
	msgbox Route47_Text_HikerAfter, MSGBOX_AUTOCLOSE
# 9 "data/maps/Route47/scripts.pory"
	end
# 10 "data/maps/Route47/scripts.pory"

# 11 "data/maps/Route47/scripts.pory"
Route47_Text_HikerSeen::
# 12 "data/maps/Route47/scripts.pory"
	.string "Longing for others is...\n"
# 13 "data/maps/Route47/scripts.pory"
	.string "what it is. \p"
# 14 "data/maps/Route47/scripts.pory"
	.string "But battles are battles,\n"
# 15 "data/maps/Route47/scripts.pory"
	.string "so let's go!$"
# 16 "data/maps/Route47/scripts.pory"

# 17 "data/maps/Route47/scripts.pory"
Route47_Text_HikerBeaten::
# 18 "data/maps/Route47/scripts.pory"
	.string "Wahaha!$"
# 19 "data/maps/Route47/scripts.pory"

# 20 "data/maps/Route47/scripts.pory"
Route47_Text_HikerAfter::
# 21 "data/maps/Route47/scripts.pory"
	.string "After a battle you should always leave\n"
# 22 "data/maps/Route47/scripts.pory"
	.string "with a parting laugh!$"
# 23 "data/maps/Route47/scripts.pory"

# 24 "data/maps/Route47/scripts.pory"
Route47_EventScript_Camper::
# 25 "data/maps/Route47/scripts.pory"
	trainerbattle_single TRAINER_GRANT, Route47_Text_CamperSeen, Route47_Text_CamperBeaten
# 26 "data/maps/Route47/scripts.pory"
	msgbox Route47_Text_CamperAfter, MSGBOX_AUTOCLOSE
# 27 "data/maps/Route47/scripts.pory"
	end
# 28 "data/maps/Route47/scripts.pory"

# 29 "data/maps/Route47/scripts.pory"
Route47_Text_CamperSeen::
# 30 "data/maps/Route47/scripts.pory"
	.string "I'm not good with large crowds, so\n"
# 31 "data/maps/Route47/scripts.pory"
	.string "I'm camping out here with my\l"
# 32 "data/maps/Route47/scripts.pory"
	.string "Pokémon!$"
# 33 "data/maps/Route47/scripts.pory"

# 34 "data/maps/Route47/scripts.pory"
Route47_Text_CamperBeaten::
# 35 "data/maps/Route47/scripts.pory"
	.string "I should be headed deeper into the\n"
# 36 "data/maps/Route47/scripts.pory"
	.string "mountain I guess...$"
# 37 "data/maps/Route47/scripts.pory"

# 38 "data/maps/Route47/scripts.pory"
Route47_Text_CamperAfter::
# 39 "data/maps/Route47/scripts.pory"
	.string "See ya!$"
# 40 "data/maps/Route47/scripts.pory"

# 41 "data/maps/Route47/scripts.pory"
Route47_EventScript_Thom::
# 42 "data/maps/Route47/scripts.pory"
	trainerbattle_double TRAINER_THOM_AND_KAE, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
# 43 "data/maps/Route47/scripts.pory"
	special GetPlayerBigGuyGirlString
# 44 "data/maps/Route47/scripts.pory"
	msgbox Route47_Text_Couple1After1, MSGBOX_AUTOCLOSE
# 45 "data/maps/Route47/scripts.pory"
	end
# 46 "data/maps/Route47/scripts.pory"

# 47 "data/maps/Route47/scripts.pory"
Route47_EventScript_Kae::
# 48 "data/maps/Route47/scripts.pory"
	trainerbattle_double TRAINER_THOM_AND_KAE, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
# 49 "data/maps/Route47/scripts.pory"
	special GetPlayerBigGuyGirlString
# 50 "data/maps/Route47/scripts.pory"
	msgbox Route47_Text_Couple1After2, MSGBOX_AUTOCLOSE
# 51 "data/maps/Route47/scripts.pory"
	end
# 52 "data/maps/Route47/scripts.pory"

# 53 "data/maps/Route47/scripts.pory"
Route47_Text_Couple1Seen::
# 54 "data/maps/Route47/scripts.pory"
	.string "Thom: One plus one is two. But the\n"
# 55 "data/maps/Route47/scripts.pory"
	.string "two of us together is much\l"
# 56 "data/maps/Route47/scripts.pory"
	.string "stronger!\p"
# 57 "data/maps/Route47/scripts.pory"
	.string "Kae: The two of us aren't just some\n"
# 58 "data/maps/Route47/scripts.pory"
	.string "boring pair!$"
# 59 "data/maps/Route47/scripts.pory"

# 60 "data/maps/Route47/scripts.pory"
Route47_Text_Couple1Beaten::
# 61 "data/maps/Route47/scripts.pory"
	.string "Thom: That wasn't what I expected.\l"
# 62 "data/maps/Route47/scripts.pory"
	.string "Kae: You're unusual too!$"
# 63 "data/maps/Route47/scripts.pory"

# 64 "data/maps/Route47/scripts.pory"
Route47_Text_Couple1After1::
# 65 "data/maps/Route47/scripts.pory"
	.string "Thom: It seems your power is\n"
# 66 "data/maps/Route47/scripts.pory"
	.string "impossible to predict!$"
# 67 "data/maps/Route47/scripts.pory"

# 68 "data/maps/Route47/scripts.pory"
Route47_Text_Couple1After2::
# 69 "data/maps/Route47/scripts.pory"
	.string "Kae: I figured you were an ordinary\n"
# 70 "data/maps/Route47/scripts.pory"
	.string "lone trainer. Boy was I wrong!$"
# 71 "data/maps/Route47/scripts.pory"

# 72 "data/maps/Route47/scripts.pory"
Route47_EventScript_Duff::
# 73 "data/maps/Route47/scripts.pory"
	trainerbattle_double TRAINER_DUFF_AND_EDA, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
# 74 "data/maps/Route47/scripts.pory"
	special GetPlayerBigGuyGirlString
# 75 "data/maps/Route47/scripts.pory"
	msgbox Route47_Text_Couple2After1, MSGBOX_AUTOCLOSE
# 76 "data/maps/Route47/scripts.pory"
	end
# 77 "data/maps/Route47/scripts.pory"

# 78 "data/maps/Route47/scripts.pory"
Route47_EventScript_Eda::
# 79 "data/maps/Route47/scripts.pory"
	trainerbattle_double TRAINER_DUFF_AND_EDA, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
# 80 "data/maps/Route47/scripts.pory"
	msgbox Route47_Text_Couple2After2, MSGBOX_AUTOCLOSE
# 81 "data/maps/Route47/scripts.pory"
	end
# 82 "data/maps/Route47/scripts.pory"

# 83 "data/maps/Route47/scripts.pory"
Route47_Text_Couple2Seen::
# 84 "data/maps/Route47/scripts.pory"
	.string "Duff: Watching over my girlfriend\n"
# 85 "data/maps/Route47/scripts.pory"
	.string "makes my heart soar!\p"
# 86 "data/maps/Route47/scripts.pory"
	.string "Eda: My heart's feelings for my\n"
# 87 "data/maps/Route47/scripts.pory"
	.string "boyfriend are as wide and deep\l"
# 88 "data/maps/Route47/scripts.pory"
	.string "the ocean!$"
# 89 "data/maps/Route47/scripts.pory"

# 90 "data/maps/Route47/scripts.pory"
Route47_Text_Couple2Beaten::
# 91 "data/maps/Route47/scripts.pory"
	.string "Duff: I was no match for you...\l"
# 92 "data/maps/Route47/scripts.pory"
	.string "Eda: You are really something...$"
# 93 "data/maps/Route47/scripts.pory"

# 94 "data/maps/Route47/scripts.pory"
Route47_Text_Couple2After1::
# 95 "data/maps/Route47/scripts.pory"
	.string "Duff: Thank you for the awe-\n"
# 96 "data/maps/Route47/scripts.pory"
	.string "inspiring battle! Bye!$"
# 97 "data/maps/Route47/scripts.pory"

# 98 "data/maps/Route47/scripts.pory"
Route47_Text_Couple2After2::
# 99 "data/maps/Route47/scripts.pory"
	.string "Eda: You should really find a\n"
# 100 "data/maps/Route47/scripts.pory"
	.string "wonderful partner, too!$"
# 101 "data/maps/Route47/scripts.pory"

# 102 "data/maps/Route47/scripts.pory"
Route47_EventScript_Sage::
# 103 "data/maps/Route47/scripts.pory"
	lock
# 104 "data/maps/Route47/scripts.pory"
	faceplayer
# 105 "data/maps/Route47/scripts.pory"
	msgbox EmbeddedTower_Text_OldManIntro, MSGBOX_DEFAULT
# 106 "data/maps/Route47/scripts.pory"
	closemessage
# 107 "data/maps/Route47/scripts.pory"
	release
# 108 "data/maps/Route47/scripts.pory"
	end
# 109 "data/maps/Route47/scripts.pory"

# 110 "data/maps/Route47/scripts.pory"
EmbeddedTower_Text_OldManIntro:
# 111 "data/maps/Route47/scripts.pory"
	.string "Well, hello!\p"
# 112 "data/maps/Route47/scripts.pory"
	.string "It's said that past this hole used to\n"
# 113 "data/maps/Route47/scripts.pory"
	.string "be a huge tower reaching far into\l"
# 114 "data/maps/Route47/scripts.pory"
	.string "the sky.\p"
# 115 "data/maps/Route47/scripts.pory"
	.string "They say that it was a rather strange\n"
# 116 "data/maps/Route47/scripts.pory"
	.string "tower with half of it embedded\l"
# 117 "data/maps/Route47/scripts.pory"
	.string "in the cliff.\p"
# 118 "data/maps/Route47/scripts.pory"
	.string "It was not just a tall tower reaching\n"
# 119 "data/maps/Route47/scripts.pory"
	.string "up to the sky, but also reaching deep\l"
# 120 "data/maps/Route47/scripts.pory"
	.string "down underground!\p"
# 121 "data/maps/Route47/scripts.pory"
	.string "It is rumored that it even reached\n"
# 122 "data/maps/Route47/scripts.pory"
	.string "the bottom of the ocean!\p"
# 123 "data/maps/Route47/scripts.pory"
	.string "In short, the ruins used to connect\n"
# 124 "data/maps/Route47/scripts.pory"
	.string "the sky, the land, and the sea to\l"
# 125 "data/maps/Route47/scripts.pory"
	.string "each other...\p"
# 126 "data/maps/Route47/scripts.pory"
	.string "Most of the tower is now crumbled,\n"
# 127 "data/maps/Route47/scripts.pory"
	.string "and the only things that remain are\l"
# 128 "data/maps/Route47/scripts.pory"
	.string "the entrance and its interior, where\l"
# 129 "data/maps/Route47/scripts.pory"
	.string "you'll see strange patterns.$"
# 130 "data/maps/Route47/scripts.pory"

# 131 "data/maps/Route47/scripts.pory"
Route47_EventScript_Chinchou::
# 132 "data/maps/Route47/scripts.pory"
	lock
# 133 "data/maps/Route47/scripts.pory"
	faceplayer
# 134 "data/maps/Route47/scripts.pory"
	waitse
# 135 "data/maps/Route47/scripts.pory"
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
# 136 "data/maps/Route47/scripts.pory"
	msgbox Route47_Text_Chinchou, MSGBOX_DEFAULT
# 137 "data/maps/Route47/scripts.pory"
	waitmoncry
# 138 "data/maps/Route47/scripts.pory"
	release
# 139 "data/maps/Route47/scripts.pory"
	end
# 140 "data/maps/Route47/scripts.pory"

# 141 "data/maps/Route47/scripts.pory"
Route47_Text_Chinchou:
# 142 "data/maps/Route47/scripts.pory"
	.string "Chinchou: Chou!$"

Route47_HiddenGrotto::
# 146 "data/maps/Route47/scripts.pory"
	msgbox Route47_HiddenGrotto_Text_0, MSGBOX_YESNO
# 148 "data/maps/Route47/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Route47_HiddenGrotto_2
Route47_HiddenGrotto_1:
# 152 "data/maps/Route47/scripts.pory"
	release
	end

Route47_HiddenGrotto_2:
# 149 "data/maps/Route47/scripts.pory"
	warp MAP_HIDDEN_GROTTO_ROUTE47, 0
# 150 "data/maps/Route47/scripts.pory"
	waitstate
	goto Route47_HiddenGrotto_1


Route47_ChuckRematch::
# 157 "data/maps/Route47/scripts.pory"
	lock
# 158 "data/maps/Route47/scripts.pory"
	msgbox Route47_ChuckRematch_Text_0
# 160 "data/maps/Route47/scripts.pory"
	waitmessage
# 161 "data/maps/Route47/scripts.pory"
	faceplayer
# 162 "data/maps/Route47/scripts.pory"
	msgbox Route47_ChuckRematch_Text_1
# 166 "data/maps/Route47/scripts.pory"
	msgbox Route47_ChuckRematch_Text_2, MSGBOX_YESNO
# 170 "data/maps/Route47/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq Route47_ChuckRematch_2
Route47_ChuckRematch_1:
# 186 "data/maps/Route47/scripts.pory"
	release
	end

Route47_ChuckRematch_2:
# 171 "data/maps/Route47/scripts.pory"
	trainerbattle_no_intro TRAINER_CHUCK_2, Route47_ChuckRematch_Text_3
# 172 "data/maps/Route47/scripts.pory"
	msgbox Route47_ChuckRematch_Text_4
# 179 "data/maps/Route47/scripts.pory"
	closemessage
# 180 "data/maps/Route47/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 181 "data/maps/Route47/scripts.pory"
	setflag FLAG_HIDE_R47_CHUCK
# 182 "data/maps/Route47/scripts.pory"
	removeobject LOCALID_R47_CHUCK
# 183 "data/maps/Route47/scripts.pory"
	delay 30
# 184 "data/maps/Route47/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Route47_ChuckRematch_1


Route47OrbExpert::
# 191 "data/maps/Route47/scripts.pory"
	lock
# 192 "data/maps/Route47/scripts.pory"
	faceplayer
# 193 "data/maps/Route47/scripts.pory"
	goto_if_set FLAG_ROUTE47_EXPERT, Route47OrbExpert_2
# 202 "data/maps/Route47/scripts.pory"
	msgbox Route47OrbExpert_Text_1
# 210 "data/maps/Route47/scripts.pory"
	goto_if_set FLAG_ROUTE47_EXPERT_QUALIFIED, Route47OrbExpert_5
# 210 "data/maps/Route47/scripts.pory"
	checktrainerflag TRAINER_DEVIN
	goto_if 1, Route47OrbExpert_9
Route47OrbExpert_4:
# 233 "data/maps/Route47/scripts.pory"
	release
	end

Route47OrbExpert_2:
# 194 "data/maps/Route47/scripts.pory"
	setflag FLAG_ROUTE47_EXPERT_QUALIFIED
# 195 "data/maps/Route47/scripts.pory"
	msgbox Route47OrbExpert_Text_0
# 198 "data/maps/Route47/scripts.pory"
	release
	end

Route47OrbExpert_5:
# 214 "data/maps/Route47/scripts.pory"
	setflag FLAG_ROUTE47_EXPERT_QUALIFIED
# 215 "data/maps/Route47/scripts.pory"
	playse SE_PIN
# 216 "data/maps/Route47/scripts.pory"
	applymovement LOCALID_R47_EXPERT, Common_Movement_ExclamationMark
# 217 "data/maps/Route47/scripts.pory"
	waitse
# 218 "data/maps/Route47/scripts.pory"
	msgbox Route47OrbExpert_Text_2
# 221 "data/maps/Route47/scripts.pory"
	trainerbattle_no_intro TRAINER_ORB_EXPERT, Route47OrbExpert_Text_3
# 222 "data/maps/Route47/scripts.pory"
	msgbox Route47OrbExpert_Text_4
# 224 "data/maps/Route47/scripts.pory"
	giveitem ITEM_FLAME_ORB
# 225 "data/maps/Route47/scripts.pory"
	giveitem ITEM_TOXIC_ORB
# 226 "data/maps/Route47/scripts.pory"
	setflag FLAG_ROUTE47_EXPERT
# 227 "data/maps/Route47/scripts.pory"
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
# 228 "data/maps/Route47/scripts.pory"
	special Achievement_CheckAll
# 229 "data/maps/Route47/scripts.pory"
	msgbox Route47OrbExpert_Text_0
	goto Route47OrbExpert_4

Route47OrbExpert_8:
# 212 "data/maps/Route47/scripts.pory"
	checktrainerflag TRAINER_THOM_AND_KAE
	goto_if 1, Route47OrbExpert_12
	goto Route47OrbExpert_4

Route47OrbExpert_9:
# 211 "data/maps/Route47/scripts.pory"
	checktrainerflag TRAINER_GRANT
	goto_if 1, Route47OrbExpert_8
	goto Route47OrbExpert_4

Route47OrbExpert_12:
# 213 "data/maps/Route47/scripts.pory"
	checktrainerflag TRAINER_DUFF_AND_EDA
	goto_if 1, Route47OrbExpert_5
	goto Route47OrbExpert_4


Route47_HiddenGrotto_Text_0:
# 146 "data/maps/Route47/scripts.pory"
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"

Route47_ChuckRematch_Text_0:
# 158 "data/maps/Route47/scripts.pory"
	.string "Hmm, the current isn't strong\n"
	.string "enough here...$"

Route47_ChuckRematch_Text_1:
# 162 "data/maps/Route47/scripts.pory"
	.string "{PLAYER}! I was searching for a\n"
	.string "stream of water with strong enough\l"
	.string "currents to train my battling skills!\l"
	.string "Wahahaha!$"

Route47_ChuckRematch_Text_2:
# 166 "data/maps/Route47/scripts.pory"
	.string "What? That has nothing to do with\n"
	.string "battles? Bah! Well I know a way\l"
	.string "we both can agree on! A fight, here\l"
	.string "and now!$"

Route47_ChuckRematch_Text_3:
# 171 "data/maps/Route47/scripts.pory"
	.string "That's the way!$"

Route47_ChuckRematch_Text_4:
# 172 "data/maps/Route47/scripts.pory"
	.string "Perfect form, peak physical condition,\n"
	.string "the ideal Pokémon battle!\p"
	.string "I should start a dojo just for the\n"
	.string "strongest trainers! Great idea,\l"
	.string "{PLAYER}! I'll invite you once\l"
	.string "it's finished! See you there!$"

Route47OrbExpert_Text_0:
# 195 "data/maps/Route47/scripts.pory"
	.string "There are many ways to pull potential\n"
	.string "out of these orbs, I hope you can\l"
	.string "find them all.$"

Route47OrbExpert_Text_1:
# 202 "data/maps/Route47/scripts.pory"
	.string "Orbs! They hold power beyond measure!\p"
	.string "But do you know how to utilize them\n"
	.string "correctly?\p"
	.string "Prove you are worthy of this\n"
	.string "wisdom by defeating all trainers\l"
	.string "on this route and then we'll talk.$"

Route47OrbExpert_Text_2:
# 218 "data/maps/Route47/scripts.pory"
	.string "You are indeed worthy of this orb\n"
	.string "knowledge! Allow me to demonstrate it\l"
	.string "to you!$"

Route47OrbExpert_Text_3:
# 221 "data/maps/Route47/scripts.pory"
	.string "Splendid moves.$"

Route47OrbExpert_Text_4:
# 222 "data/maps/Route47/scripts.pory"
	.string "You are more worthy of these orbs\n"
	.string "now. I will pass them to you.$"
