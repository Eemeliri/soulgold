GoldenrodShore_MapScripts::
	.byte 0


GoldenrodShore_Expert::
# 4 "data/maps/GoldenrodShore/scripts.pory"
	lock
# 5 "data/maps/GoldenrodShore/scripts.pory"
	faceplayer
# 6 "data/maps/GoldenrodShore/scripts.pory"
	goto_if_set FLAG_GOLDENRODSHORE_EXPERT, GoldenrodShore_Expert_2
# 14 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_Expert_Text_1
# 19 "data/maps/GoldenrodShore/scripts.pory"
	goto_if_set FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED, GoldenrodShore_Expert_5
# 19 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_SAMUEL
	goto_if 1, GoldenrodShore_Expert_9
GoldenrodShore_Expert_4:
# 46 "data/maps/GoldenrodShore/scripts.pory"
	release
	end

GoldenrodShore_Expert_2:
# 7 "data/maps/GoldenrodShore/scripts.pory"
	setflag FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED
# 8 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_Expert_Text_0
# 11 "data/maps/GoldenrodShore/scripts.pory"
	release
	end

GoldenrodShore_Expert_5:
# 22 "data/maps/GoldenrodShore/scripts.pory"
	setflag FLAG_GOLDENRODSHORE_EXPERT_QUALIFIED
# 23 "data/maps/GoldenrodShore/scripts.pory"
	applymovement LOCALID_GOLDENRODSHORE_EXPERT, Common_Movement_ExclamationMark
# 24 "data/maps/GoldenrodShore/scripts.pory"
	playse SE_PIN
# 25 "data/maps/GoldenrodShore/scripts.pory"
	waitse
# 26 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_Expert_Text_2
# 31 "data/maps/GoldenrodShore/scripts.pory"
	trainerbattle_no_intro TRAINER_GOLDENROD_SHORE_EXPERT, GoldenrodShore_Expert_Text_3
# 32 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_Expert_Text_4
# 38 "data/maps/GoldenrodShore/scripts.pory"
	giveitem ITEM_LOADED_DICE
# 39 "data/maps/GoldenrodShore/scripts.pory"
	setflag FLAG_GOLDENRODSHORE_EXPERT
# 40 "data/maps/GoldenrodShore/scripts.pory"
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
# 41 "data/maps/GoldenrodShore/scripts.pory"
	special Achievement_CheckAll
# 42 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_Expert_Text_5
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_8:
# 19 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_TODD
	goto_if 1, GoldenrodShore_Expert_13
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_9:
# 19 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_BRANDON
	goto_if 1, GoldenrodShore_Expert_8
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_12:
# 19 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_GINA
	goto_if 1, GoldenrodShore_Expert_17
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_13:
# 19 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_IAN
	goto_if 1, GoldenrodShore_Expert_12
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_16:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_ELLIOT
	goto_if 1, GoldenrodShore_Expert_21
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_17:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_KIM
	goto_if 1, GoldenrodShore_Expert_16
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_20:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_IVAN
	goto_if 1, GoldenrodShore_Expert_25
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_21:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_BROOKE
	goto_if 1, GoldenrodShore_Expert_20
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_24:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_WALT
	goto_if 1, GoldenrodShore_Expert_29
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_25:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_IRWIN
	goto_if 1, GoldenrodShore_Expert_24
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_28:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_BRYAN
	goto_if 1, GoldenrodShore_Expert_33
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_29:
# 20 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_ARNIE
	goto_if 1, GoldenrodShore_Expert_28
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_32:
# 21 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_ALAN
	goto_if 1, GoldenrodShore_Expert_5
	goto GoldenrodShore_Expert_4

GoldenrodShore_Expert_33:
# 21 "data/maps/GoldenrodShore/scripts.pory"
	checktrainerflag TRAINER_MARK
	goto_if 1, GoldenrodShore_Expert_32
	goto GoldenrodShore_Expert_4


GoldenrodShore_Sign::
# 51 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_Sign_Text_0, MSGBOX_SIGN
	return


GoldenrodShore_Engineer::
# 55 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_Engineer_Text_0, MSGBOX_NPC
	return


GoldenrodShore_HiddenGrotto::
# 61 "data/maps/GoldenrodShore/scripts.pory"
	msgbox GoldenrodShore_HiddenGrotto_Text_0, MSGBOX_YESNO
# 63 "data/maps/GoldenrodShore/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq GoldenrodShore_HiddenGrotto_2
GoldenrodShore_HiddenGrotto_1:
# 67 "data/maps/GoldenrodShore/scripts.pory"
	release
	end

GoldenrodShore_HiddenGrotto_2:
# 64 "data/maps/GoldenrodShore/scripts.pory"
	warp MAP_HIDDEN_GROTTO_GOLDENROD_SHORE, 0
# 65 "data/maps/GoldenrodShore/scripts.pory"
	waitstate
	goto GoldenrodShore_HiddenGrotto_1


MareaniesGoldenrodShore::
# 72 "data/maps/GoldenrodShore/scripts.pory"
	msgbox MareaniesGoldenrodShore_Text_0, MSGBOX_NPC
	return


GoldenrodShore_Expert_Text_0:
# 8 "data/maps/GoldenrodShore/scripts.pory"
	.string "Guess I'm free to go home now\n"
	.string "that I no longer have to maintain\l"
	.string "this route expert title.$"

GoldenrodShore_Expert_Text_1:
# 14 "data/maps/GoldenrodShore/scripts.pory"
	.string "Hi! I'm the route expert of local area!\p"
	.string "If you can beat every trainer on routes\n"
	.string "34, 35 and 36. Come have a battle with\l"
	.string "me.$"

GoldenrodShore_Expert_Text_2:
# 26 "data/maps/GoldenrodShore/scripts.pory"
	.string "I've heard the words of your victories!\p"
	.string "Let's have a battle then, I'll show\n"
	.string "you a new type of strategy!$"

GoldenrodShore_Expert_Text_3:
# 31 "data/maps/GoldenrodShore/scripts.pory"
	.string "Outsmarted!$"

GoldenrodShore_Expert_Text_4:
# 32 "data/maps/GoldenrodShore/scripts.pory"
	.string "Even against my unrelenting tide\n"
	.string "of attacks, you prevailed. \p"
	.string "Please, have this item to boost \n"
	.string "your odds of keeping up the \l"
	.string "winning streak.$"

GoldenrodShore_Expert_Text_5:
# 42 "data/maps/GoldenrodShore/scripts.pory"
	.string "Loaded Dice boosts the minimum hit \n"
	.string "count of multi-hit moves, you should \l"
	.string "try it with moves like Bullet Seed!$"

GoldenrodShore_Sign_Text_0:
# 51 "data/maps/GoldenrodShore/scripts.pory"
	.string "Goldenrod Shore, no littering!$"

GoldenrodShore_Engineer_Text_0:
# 55 "data/maps/GoldenrodShore/scripts.pory"
	.string "Alright, time to start digging a path \n"
	.string "here. The Pokéathlon construction\l"
	.string "starts here!$"

GoldenrodShore_HiddenGrotto_Text_0:
# 61 "data/maps/GoldenrodShore/scripts.pory"
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"

MareaniesGoldenrodShore_Text_0:
# 72 "data/maps/GoldenrodShore/scripts.pory"
	.string "Mareanies seem to be blocking the way.\p"
	.string "Perhaps there is another way to\n"
	.string "the Olivine City?$"
