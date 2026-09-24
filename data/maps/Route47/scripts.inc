
Route47_MapScripts::
	.byte 0


Route47_EventScript_Hiker::
	trainerbattle_single TRAINER_DEVIN, Route47_Text_HikerSeen, Route47_Text_HikerBeaten
	msgbox Route47_Text_HikerAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_HikerSeen::
	.string "Longing for others is...\n"
	.string "what it is. \p"
	.string "But battles are battles,\n"
	.string "so let's go!$"

Route47_Text_HikerBeaten::
	.string "Wahaha!$"

Route47_Text_HikerAfter::
	.string "After a battle you should always leave\n"
	.string "with a parting laugh!$"

Route47_EventScript_Camper::
	trainerbattle_single TRAINER_GRANT, Route47_Text_CamperSeen, Route47_Text_CamperBeaten
	msgbox Route47_Text_CamperAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_CamperSeen::
	.string "I'm not good with large crowds, so\n"
	.string "I'm camping out here with my\l"
	.string "Pokémon!$"

Route47_Text_CamperBeaten::
	.string "I should be headed deeper into the\n"
	.string "mountain I guess...$"

Route47_Text_CamperAfter::
	.string "See ya!$"

Route47_EventScript_Thom::
	trainerbattle_double TRAINER_THOM_AND_KAE, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Kae::
	trainerbattle_double TRAINER_THOM_AND_KAE, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple1Seen::
	.string "Thom: One plus one is two. But the\n"
	.string "two of us together is much\l"
	.string "stronger!\p"
	.string "Kae: The two of us aren't just some\n"
	.string "boring pair!$"

Route47_Text_Couple1Beaten::
	.string "Thom: That wasn't what I expected.\l"
	.string "Kae: You're unusual too!$"

Route47_Text_Couple1After1::
	.string "Thom: It seems your power is\n"
	.string "impossible to predict!$"

Route47_Text_Couple1After2::
	.string "Kae: I figured you were an ordinary\n"
	.string "lone trainer. Boy was I wrong!$"

Route47_EventScript_Duff::
	trainerbattle_double TRAINER_DUFF_AND_EDA, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple2After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Eda::
	trainerbattle_double TRAINER_DUFF_AND_EDA, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	msgbox Route47_Text_Couple2After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple2Seen::
	.string "Duff: Watching over my girlfriend\n"
	.string "makes my heart soar!\p"
	.string "Eda: My heart's feelings for my\n"
	.string "boyfriend are as wide and deep\l"
	.string "the ocean!$"

Route47_Text_Couple2Beaten::
	.string "Duff: I was no match for you...\l"
	.string "Eda: You are really something...$"

Route47_Text_Couple2After1::
	.string "Duff: Thank you for the awe-\n"
	.string "inspiring battle! Bye!$"

Route47_Text_Couple2After2::
	.string "Eda: You should really find a\n"
	.string "wonderful partner, too!$"

Route47_EventScript_Sage::
	lock
	faceplayer
	msgbox EmbeddedTower_Text_OldManIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

EmbeddedTower_Text_OldManIntro:
	.string "Well, hello!\p"
	.string "It's said that past this hole used to\n"
	.string "be a huge tower reaching far into\l"
	.string "the sky.\p"
	.string "They say that it was a rather strange\n"
	.string "tower with half of it embedded\l"
	.string "in the cliff.\p"
	.string "It was not just a tall tower reaching\n"
	.string "up to the sky, but also reaching deep\l"
	.string "down underground!\p"
	.string "It is rumored that it even reached\n"
	.string "the bottom of the ocean!\p"
	.string "In short, the ruins used to connect\n"
	.string "the sky, the land, and the sea to\l"
	.string "each other...\p"
	.string "Most of the tower is now crumbled,\n"
	.string "and the only things that remain are\l"
	.string "the entrance and its interior, where\l"
	.string "you'll see strange patterns.$"

Route47_EventScript_Chinchou::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
	msgbox Route47_Text_Chinchou, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route47_Text_Chinchou:
	.string "Chinchou: Chou!$"

Route47_HiddenGrotto::
	msgbox Route47_HiddenGrotto_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route47_HiddenGrotto_2
Route47_HiddenGrotto_1:
	release
	end

Route47_HiddenGrotto_2:
	warp MAP_HIDDEN_GROTTO_ROUTE47, 0
	waitstate
	goto Route47_HiddenGrotto_1


Route47_ChuckRematch::
	lock
	msgbox Route47_ChuckRematch_Text_0
	waitmessage
	faceplayer
	msgbox Route47_ChuckRematch_Text_1
	msgbox Route47_ChuckRematch_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, TRUE
	goto_if_eq Route47_ChuckRematch_2
Route47_ChuckRematch_1:
	release
	end

Route47_ChuckRematch_2:
	trainerbattle_no_intro TRAINER_CHUCK_2, Route47_ChuckRematch_Text_3
	msgbox Route47_ChuckRematch_Text_4
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_R47_CHUCK
	removeobject LOCALID_R47_CHUCK
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Route47_ChuckRematch_1


Route47OrbExpert::
	lock
	faceplayer
	goto_if_set FLAG_ROUTE47_EXPERT, Route47OrbExpert_2
	msgbox Route47OrbExpert_Text_1
	goto_if_set FLAG_ROUTE47_EXPERT_QUALIFIED, Route47OrbExpert_5
	checktrainerflag TRAINER_DEVIN
	goto_if 1, Route47OrbExpert_9
Route47OrbExpert_4:
	release
	end

Route47OrbExpert_2:
	setflag FLAG_ROUTE47_EXPERT_QUALIFIED
	msgbox Route47OrbExpert_Text_0
	release
	end

Route47OrbExpert_5:
	setflag FLAG_ROUTE47_EXPERT_QUALIFIED
	playse SE_PIN
	applymovement LOCALID_R47_EXPERT, Common_Movement_ExclamationMark
	waitse
	msgbox Route47OrbExpert_Text_2
	trainerbattle_no_intro TRAINER_ORB_EXPERT, Route47OrbExpert_Text_3
	msgbox Route47OrbExpert_Text_4
	giveitem ITEM_FLAME_ORB
	giveitem ITEM_TOXIC_ORB
	setflag FLAG_ROUTE47_EXPERT
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
	special Achievement_CheckAll
	msgbox Route47OrbExpert_Text_0
	goto Route47OrbExpert_4

Route47OrbExpert_8:
	checktrainerflag TRAINER_THOM_AND_KAE
	goto_if 1, Route47OrbExpert_12
	goto Route47OrbExpert_4

Route47OrbExpert_9:
	checktrainerflag TRAINER_GRANT
	goto_if 1, Route47OrbExpert_8
	goto Route47OrbExpert_4

Route47OrbExpert_12:
	checktrainerflag TRAINER_DUFF_AND_EDA
	goto_if 1, Route47OrbExpert_5
	goto Route47OrbExpert_4


Route47_HiddenGrotto_Text_0:
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"

Route47_ChuckRematch_Text_0:
	.string "Hmm, the current isn't strong\n"
	.string "enough here...$"

Route47_ChuckRematch_Text_1:
	.string "{PLAYER}! I was searching for a\n"
	.string "stream of water with strong enough\l"
	.string "currents to train my battling skills!\l"
	.string "Wahahaha!$"

Route47_ChuckRematch_Text_2:
	.string "What? That has nothing to do with\n"
	.string "battles? Bah! Well I know a way\l"
	.string "we both can agree on! A fight, here\l"
	.string "and now!$"

Route47_ChuckRematch_Text_3:
	.string "That's the way!$"

Route47_ChuckRematch_Text_4:
	.string "Perfect form, peak physical condition,\n"
	.string "the ideal Pokémon battle!\p"
	.string "I should start a dojo just for the\n"
	.string "strongest trainers! Great idea,\l"
	.string "{PLAYER}! I'll invite you once\l"
	.string "it's finished! See you there!$"

Route47OrbExpert_Text_0:
	.string "There are many ways to pull potential\n"
	.string "out of these orbs, I hope you can\l"
	.string "find them all.$"

Route47OrbExpert_Text_1:
	.string "Orbs! They hold power beyond measure!\p"
	.string "But do you know how to utilize them\n"
	.string "correctly?\p"
	.string "Prove you are worthy of this\n"
	.string "wisdom by defeating all trainers\l"
	.string "on this route and then we'll talk.$"

Route47OrbExpert_Text_2:
	.string "You are indeed worthy of this orb\n"
	.string "knowledge! Allow me to demonstrate it\l"
	.string "to you!$"

Route47OrbExpert_Text_3:
	.string "Splendid moves.$"

Route47OrbExpert_Text_4:
	.string "You are more worthy of these orbs\n"
	.string "now. I will pass them to you.$"
