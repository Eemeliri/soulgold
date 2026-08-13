Kitakami_Houses_MapScripts::
	.byte 0


KitakamiHouses_1_Oldman::
# 4 "data/maps/Kitakami_Houses/scripts.pory"
	lock
# 5 "data/maps/Kitakami_Houses/scripts.pory"
	faceplayer
# 6 "data/maps/Kitakami_Houses/scripts.pory"
	goto_if_set FLAG_CANDY_KITAKAMI, KitakamiHouses_1_Oldman_2
# 12 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_1_Oldman_Text_1
# 18 "data/maps/Kitakami_Houses/scripts.pory"
	random 3
# 19 "data/maps/Kitakami_Houses/scripts.pory"
	switch VAR_RESULT
# 20 "data/maps/Kitakami_Houses/scripts.pory"
	case 0, KitakamiHouses_1_Oldman_6
# 22 "data/maps/Kitakami_Houses/scripts.pory"
	case 1, KitakamiHouses_1_Oldman_7
# 25 "data/maps/Kitakami_Houses/scripts.pory"
	case 2, KitakamiHouses_1_Oldman_8
KitakamiHouses_1_Oldman_4:
# 29 "data/maps/Kitakami_Houses/scripts.pory"
	setflag FLAG_CANDY_KITAKAMI
# 30 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_1_Oldman_Text_0
# 32 "data/maps/Kitakami_Houses/scripts.pory"
	release
	end

KitakamiHouses_1_Oldman_2:
# 7 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_1_Oldman_Text_0
# 9 "data/maps/Kitakami_Houses/scripts.pory"
	release
	end

KitakamiHouses_1_Oldman_6:
# 21 "data/maps/Kitakami_Houses/scripts.pory"
	giveitem ITEM_EXP_CANDY_M, 3
	goto KitakamiHouses_1_Oldman_4

KitakamiHouses_1_Oldman_7:
# 23 "data/maps/Kitakami_Houses/scripts.pory"
	giveitem ITEM_EXP_CANDY_L, 2
# 24 "data/maps/Kitakami_Houses/scripts.pory"
	giveitem ITEM_EXP_CANDY_M, 1
	goto KitakamiHouses_1_Oldman_4

KitakamiHouses_1_Oldman_8:
# 26 "data/maps/Kitakami_Houses/scripts.pory"
	giveitem ITEM_EXP_CANDY_XL, 1
# 27 "data/maps/Kitakami_Houses/scripts.pory"
	giveitem ITEM_EXP_CANDY_L, 1
	goto KitakamiHouses_1_Oldman_4


KitakamiHouses_3_Sinistea::
# 38 "data/maps/Kitakami_Houses/scripts.pory"
	lock
# 39 "data/maps/Kitakami_Houses/scripts.pory"
	faceplayer
# 40 "data/maps/Kitakami_Houses/scripts.pory"
	playmoncry SPECIES_SINISTEA, CRY_MODE_NORMAL
# 41 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_3_Sinistea_Text_0
# 42 "data/maps/Kitakami_Houses/scripts.pory"
	waitmoncry
# 43 "data/maps/Kitakami_Houses/scripts.pory"
	release
	end


KitakamiHouses_2_Steven::
# 48 "data/maps/Kitakami_Houses/scripts.pory"
	lock
# 49 "data/maps/Kitakami_Houses/scripts.pory"
	faceplayer
# 50 "data/maps/Kitakami_Houses/scripts.pory"
	goto_if_set FLAG_MET_STEVEN, KitakamiHouses_2_Steven_2
# 126 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_7
# 135 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_8
# 153 "data/maps/Kitakami_Houses/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_BELDUM
# 154 "data/maps/Kitakami_Houses/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_BELDUM
# 155 "data/maps/Kitakami_Houses/scripts.pory"
	givemon SPECIES_BELDUM, 15, ITEM_IRON_PLATE, ITEM_LUXURY_BALL
# 156 "data/maps/Kitakami_Houses/scripts.pory"
	showgivemonpic 10, 3
# 157 "data/maps/Kitakami_Houses/scripts.pory"
	call Common_EventScript_GiftMon
# 158 "data/maps/Kitakami_Houses/scripts.pory"
	hidemonpic
# 159 "data/maps/Kitakami_Houses/scripts.pory"
	setflag FLAG_MET_STEVEN
# 160 "data/maps/Kitakami_Houses/scripts.pory"
	createfieldmugshot MUGSHOT_STEVEN
# 161 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_9
# 162 "data/maps/Kitakami_Houses/scripts.pory"
	waitmessage
# 163 "data/maps/Kitakami_Houses/scripts.pory"
	release
	end

KitakamiHouses_2_Steven_2:
# 51 "data/maps/Kitakami_Houses/scripts.pory"
	goto_if_set FLAG_IS_CHAMPION, KitakamiHouses_2_Steven_5
# 116 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_6
# 122 "data/maps/Kitakami_Houses/scripts.pory"
	release
	end

KitakamiHouses_2_Steven_5:
# 53 "data/maps/Kitakami_Houses/scripts.pory"
	goto_if_unset FLAG_TEMP_10, KitakamiHouses_2_Steven_9
KitakamiHouses_2_Steven_8:
# 71 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_1, MSGBOX_YESNO
# 72 "data/maps/Kitakami_Houses/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq KitakamiHouses_2_Steven_11
# 111 "data/maps/Kitakami_Houses/scripts.pory"
	release
	end

KitakamiHouses_2_Steven_9:
# 54 "data/maps/Kitakami_Houses/scripts.pory"
	playse SE_PIN
# 55 "data/maps/Kitakami_Houses/scripts.pory"
	applymovement LOCALID_KITAKAMI_STEVEN, Common_Movement_ExclamationMark
# 56 "data/maps/Kitakami_Houses/scripts.pory"
	applymovement LOCALID_KITAKAMI_STEVEN, KitakamiHouses_2_Steven_Movement_0
# 57 "data/maps/Kitakami_Houses/scripts.pory"
	waitmovement 0
# 58 "data/maps/Kitakami_Houses/scripts.pory"
	waitse
# 59 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_0
# 69 "data/maps/Kitakami_Houses/scripts.pory"
	setflag FLAG_TEMP_10
	goto KitakamiHouses_2_Steven_8

KitakamiHouses_2_Steven_11:
# 74 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_2
# 76 "data/maps/Kitakami_Houses/scripts.pory"
	trainerbattle_no_intro TRAINER_STEVEN, KitakamiHouses_2_Steven_Text_3
# 78 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_4
# 91 "data/maps/Kitakami_Houses/scripts.pory"
	giveitem ITEM_JADE_ORB
# 92 "data/maps/Kitakami_Houses/scripts.pory"
	waitmessage
# 93 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_2_Steven_Text_5
# 98 "data/maps/Kitakami_Houses/scripts.pory"
	waitmessage
# 99 "data/maps/Kitakami_Houses/scripts.pory"
	closemessage
# 100 "data/maps/Kitakami_Houses/scripts.pory"
	setflag FLAG_BEAT_STEVEN_KITAKAMI
# 101 "data/maps/Kitakami_Houses/scripts.pory"
	moveobjecttocoords LOCALID_KITAKAMI_STEVEN, 28, 8, DIR_SOUTH
# 102 "data/maps/Kitakami_Houses/scripts.pory"
	waitmovement LOCALID_KITAKAMI_STEVEN
# 103 "data/maps/Kitakami_Houses/scripts.pory"
	delay 15
# 104 "data/maps/Kitakami_Houses/scripts.pory"
	playse SE_EXIT
# 106 "data/maps/Kitakami_Houses/scripts.pory"
	removeobject LOCALID_KITAKAMI_STEVEN
# 107 "data/maps/Kitakami_Houses/scripts.pory"
	release
	end


PorygonPC::
# 168 "data/maps/Kitakami_Houses/scripts.pory"
	lockall
# 169 "data/maps/Kitakami_Houses/scripts.pory"
	playmoncry SPECIES_PORYGON_Z, CRY_MODE_NORMAL
# 170 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox PorygonPC_Text_0
# 172 "data/maps/Kitakami_Houses/scripts.pory"
	goto EventScript_PCMainMenu
	return


KitakamiHouses_3_Lady::
# 176 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_3_Lady_Text_0, MSGBOX_NPC
	return


KitakamiHouses_3_Man::
# 181 "data/maps/Kitakami_Houses/scripts.pory"
	msgbox KitakamiHouses_3_Man_Text_0, MSGBOX_NPC
	return


# 56 "data/maps/Kitakami_Houses/scripts.pory"
KitakamiHouses_2_Steven_Movement_0:
# 56 "data/maps/Kitakami_Houses/scripts.pory"
	face_player
	step_end

KitakamiHouses_1_Oldman_Text_0:
# 7 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Come back tomorrow when I have\n"
	.string "prepared another batch!$"

KitakamiHouses_1_Oldman_Text_1:
# 12 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Ho ho ho! \p"
	.string "I'm the best candy baker in the\n"
	.string "entire Johto! \p"
	.string "Here, have some from my daily batch!$"

KitakamiHouses_3_Sinistea_Text_0:
# 41 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Sinistea: Siii!$"

KitakamiHouses_2_Steven_Text_0:
# 59 "data/maps/Kitakami_Houses/scripts.pory"
	.string "That face of determination... I assume\n"
	.string "you have become the Champion of Johto?\p"
	.string "...\p"
	.string "Impressive! I was right about your\n"
	.string "potential as a trainer.\p"
	.string "I'd be more than happy to battle you\n"
	.string "now, if you are alright with that.$"

KitakamiHouses_2_Steven_Text_1:
# 71 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Are you ready to face me?$"

KitakamiHouses_2_Steven_Text_2:
# 74 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Splendid, I'll hold nothing back\n"
	.string "and I expect you to do the same!$"

KitakamiHouses_2_Steven_Text_3:
# 76 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Outstanding, you truly have earned\n"
	.string "the title of a Champion.$"

KitakamiHouses_2_Steven_Text_4:
# 78 "data/maps/Kitakami_Houses/scripts.pory"
	.string "It cannot be overstated how happy\n"
	.string "this battle made me. \p"
	.string "You are a trainer of exceptional skill.\p"
	.string "I want you to have this as a gift\n"
	.string "of our meeting. \p"
	.string "I excavated it from the mountain. \n"
	.string "up north. \p"
	.string "You might find some use for it \n"
	.string "near Route 47.$"

KitakamiHouses_2_Steven_Text_5:
# 93 "data/maps/Kitakami_Houses/scripts.pory"
	.string "I think I'll start heading out to \n"
	.string "explore new places now. \p"
	.string "I hope our paths cross again some day, \n"
	.string "{PLAYER}.$"

KitakamiHouses_2_Steven_Text_6:
# 116 "data/maps/Kitakami_Houses/scripts.pory"
	.string "If you end up becoming a Champion of\n"
	.string "the region, you should come see me.\p"
	.string "I would love to battle you with my\n"
	.string "full strength.$"

KitakamiHouses_2_Steven_Text_7:
# 126 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Oh, hello. Who might you be?\p"
	.string "...\p"
	.string "{PLAYER}? \n"
	.string "Nice to meet you.\p"
	.string "My name is Steven, I hail from the Hoenn\n"
	.string "region in search of rare stones.$"

KitakamiHouses_2_Steven_Text_8:
# 135 "data/maps/Kitakami_Houses/scripts.pory"
	.string "You look like a trainer, are you on the\n"
	.string "quest to collect badges in Johto?\p"
	.string "Hmm.. Perhaps... \p"
	.string "Yes, you may have the\n"
	.string "potential for what it takes.\p"
	.string "Would you be willing to hear my request?\p"
	.string "I would like you to have this Beldum.\n"
	.string "It's a rare Pokémon from Hoenn.\p"
	.string "Take care of it and come see me again\n"
	.string "if you become the Champion. \p"
	.string "I would like to battle you then \n"
	.string "in return.$"

KitakamiHouses_2_Steven_Text_9:
# 161 "data/maps/Kitakami_Houses/scripts.pory"
	.string "I have high expectations for you.$"

PorygonPC_Text_0:
# 170 "data/maps/Kitakami_Houses/scripts.pory"
	.string "{PLAYER} booted up the Porygon \n"
	.string "remote PC.$"

KitakamiHouses_3_Lady_Text_0:
# 176 "data/maps/Kitakami_Houses/scripts.pory"
	.string "Life is peaceful here with my family,\n"
	.string "I couldn't ask for much else.$"

KitakamiHouses_3_Man_Text_0:
# 181 "data/maps/Kitakami_Houses/scripts.pory"
	.string "This town is protected by Ogerpon, who\n"
	.string "sometimes visits this town. \p"
	.string "Personally I have never seen it, \n"
	.string "but kids say they have.$"
