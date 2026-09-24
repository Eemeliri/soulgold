GoldenrodShore_MapScripts::
	.byte 0


GoldenrodShore_Expert::
	lock
	faceplayer
	goto_if_set FLAG_GOLDENRODSHORE_EXPERT, GoldenrodShore_Expert_2
	msgbox GoldenrodShore_Expert_Text_1
	goto_if_set FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED, GoldenrodShore_Expert_5
	checktrainerflag TRAINER_SAMUEL
	goto_if 1, GoldenrodShore_Expert_9
GoldenrodShore_Expert_4:
	release
	end

GoldenrodShore_Expert_2:
	setflag FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED
	msgbox GoldenrodShore_Expert_Text_0
	release
	end

GoldenrodShore_Expert_5:
	setflag FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED
	applymovement LOCALID_GOLDENRODSHORE_EXPERT, Common_Movement_ExclamationMark
	playse SE_PIN
	waitse
	msgbox GoldenrodShore_Expert_Text_2
	trainerbattle_no_intro TRAINER_GOLDENROD_SHORE_EXPERT, GoldenrodShore_Expert_Text_3
	msgbox GoldenrodShore_Expert_Text_4
	giveitem ITEM_LOADED_DICE
	setflag FLAG_GOLDENRODSHORE_EXPERT
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
	special Achievement_CheckAll
	msgbox GoldenrodShore_Expert_Text_5
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_8:
	checktrainerflag TRAINER_TODD
	goto_if 1, GoldenrodShore_Expert_13
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_9:
	checktrainerflag TRAINER_BRANDON
	goto_if 1, GoldenrodShore_Expert_8
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_12:
	checktrainerflag TRAINER_GINA
	goto_if 1, GoldenrodShore_Expert_17
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_13:
	checktrainerflag TRAINER_IAN
	goto_if 1, GoldenrodShore_Expert_12
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_16:
	checktrainerflag TRAINER_ELLIOT
	goto_if 1, GoldenrodShore_Expert_21
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_17:
	checktrainerflag TRAINER_KIM
	goto_if 1, GoldenrodShore_Expert_16
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_20:
	checktrainerflag TRAINER_IVAN
	goto_if 1, GoldenrodShore_Expert_25
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_21:
	checktrainerflag TRAINER_BROOKE
	goto_if 1, GoldenrodShore_Expert_20
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_24:
	checktrainerflag TRAINER_WALT
	goto_if 1, GoldenrodShore_Expert_29
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_25:
	checktrainerflag TRAINER_IRWIN
	goto_if 1, GoldenrodShore_Expert_24
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_28:
	checktrainerflag TRAINER_BRYAN
	goto_if 1, GoldenrodShore_Expert_33
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_29:
	checktrainerflag TRAINER_ARNIE
	goto_if 1, GoldenrodShore_Expert_28
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_32:
	checktrainerflag TRAINER_ALAN
	goto_if 1, GoldenrodShore_Expert_5
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_33:
	checktrainerflag TRAINER_MARK
	goto_if 1, GoldenrodShore_Expert_32
	goto GoldenrodShore_Expert_4


GoldenrodShore_Sign::
	msgbox GoldenrodShore_Sign_Text_0, MSGBOX_SIGN
	return


GoldenrodShore_Engineer::
	msgbox GoldenrodShore_Engineer_Text_0, MSGBOX_NPC
	return


GoldenrodShore_HiddenGrotto::
	msgbox GoldenrodShore_HiddenGrotto_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq GoldenrodShore_HiddenGrotto_2
GoldenrodShore_HiddenGrotto_1:
	release
	end

GoldenrodShore_HiddenGrotto_2:
	warp MAP_HIDDEN_GROTTO_GOLDENROD_SHORE, 0
	waitstate
	goto GoldenrodShore_HiddenGrotto_1


MareaniesGoldenrodShore::
	msgbox MareaniesGoldenrodShore_Text_0, MSGBOX_NPC
	return


GoldenrodShore_Expert_Text_0:
	.string "Guess I'm free to go home now\n"
	.string "that I no longer have to maintain\l"
	.string "this route expert title.$"

GoldenrodShore_Expert_Text_1:
	.string "Hi! I'm the route expert of local area!\p"
	.string "If you can beat every trainer on routes\n"
	.string "34, 35 and 36. Come have a battle with\l"
	.string "me.$"

GoldenrodShore_Expert_Text_2:
	.string "I've heard the words of your victories!\p"
	.string "Let's have a battle then, I'll show\n"
	.string "you a new type of strategy!$"

GoldenrodShore_Expert_Text_3:
	.string "Outsmarted!$"

GoldenrodShore_Expert_Text_4:
	.string "Even against my unrelenting tide\n"
	.string "of attacks, you prevailed. \p"
	.string "Please, have this item to boost \n"
	.string "your odds of keeping up the \l"
	.string "winning streak.$"

GoldenrodShore_Expert_Text_5:
	.string "Loaded Dice boosts the minimum hit \n"
	.string "count of multi-hit moves, you should \l"
	.string "try it with moves like Bullet Seed!$"

GoldenrodShore_Sign_Text_0:
	.string "Goldenrod Shore, no littering!$"

GoldenrodShore_Engineer_Text_0:
	.string "Alright, time to start digging a path \n"
	.string "here. The Pokéathlon construction\l"
	.string "starts here!$"

GoldenrodShore_HiddenGrotto_Text_0:
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"

MareaniesGoldenrodShore_Text_0:
	.string "Mareanies seem to be blocking the way.\p"
	.string "Perhaps there is another way to\n"
	.string "the Olivine City?$"
