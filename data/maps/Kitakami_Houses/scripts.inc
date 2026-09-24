Kitakami_Houses_MapScripts::
	.byte 0


KitakamiHouses_1_Oldman::
	lock
	faceplayer
	goto_if_set FLAG_CANDY_KITAKAMI, KitakamiHouses_1_Oldman_2
	msgbox KitakamiHouses_1_Oldman_Text_1
	random 3
	switch VAR_RESULT
	case 0, KitakamiHouses_1_Oldman_6
	case 1, KitakamiHouses_1_Oldman_7
	case 2, KitakamiHouses_1_Oldman_8
KitakamiHouses_1_Oldman_4:
	setflag FLAG_CANDY_KITAKAMI
	msgbox KitakamiHouses_1_Oldman_Text_0
	release
	end

KitakamiHouses_1_Oldman_2:
	msgbox KitakamiHouses_1_Oldman_Text_0
	release
	end

KitakamiHouses_1_Oldman_6:
	giveitem ITEM_EXP_CANDY_M, 3
	goto KitakamiHouses_1_Oldman_4

KitakamiHouses_1_Oldman_7:
	giveitem ITEM_EXP_CANDY_L, 2
	giveitem ITEM_EXP_CANDY_M, 1
	goto KitakamiHouses_1_Oldman_4

KitakamiHouses_1_Oldman_8:
	giveitem ITEM_EXP_CANDY_XL, 1
	giveitem ITEM_EXP_CANDY_L, 1
	goto KitakamiHouses_1_Oldman_4


KitakamiHouses_3_Sinistea::
	lock
	faceplayer
	playmoncry SPECIES_SINISTEA, CRY_MODE_NORMAL
	msgbox KitakamiHouses_3_Sinistea_Text_0
	waitmoncry
	release
	end


KitakamiHouses_2_Steven::
	lock
	faceplayer
	goto_if_set FLAG_MET_STEVEN, KitakamiHouses_2_Steven_2
	msgbox KitakamiHouses_2_Steven_Text_7
	msgbox KitakamiHouses_2_Steven_Text_8
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_BELDUM
	bufferspeciesname STR_VAR_1, SPECIES_BELDUM
	givemon SPECIES_BELDUM, 15, ITEM_IRON_BALL, ITEM_LUXURY_BALL
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setflag FLAG_MET_STEVEN
	createfieldmugshot MUGSHOT_STEVEN
	msgbox KitakamiHouses_2_Steven_Text_9
	waitmessage
	release
	end

KitakamiHouses_2_Steven_2:
	goto_if_set FLAG_IS_CHAMPION, KitakamiHouses_2_Steven_5
	msgbox KitakamiHouses_2_Steven_Text_6
	release
	end

KitakamiHouses_2_Steven_5:
	goto_if_unset FLAG_TEMP_10, KitakamiHouses_2_Steven_9
KitakamiHouses_2_Steven_8:
	msgbox KitakamiHouses_2_Steven_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq KitakamiHouses_2_Steven_11
	release
	end

KitakamiHouses_2_Steven_9:
	playse SE_PIN
	applymovement LOCALID_KITAKAMI_STEVEN, Common_Movement_ExclamationMark
	applymovement LOCALID_KITAKAMI_STEVEN, KitakamiHouses_2_Steven_Movement_0
	waitmovement 0
	waitse
	msgbox KitakamiHouses_2_Steven_Text_0
	setflag FLAG_TEMP_10
	goto KitakamiHouses_2_Steven_8

KitakamiHouses_2_Steven_11:
	msgbox KitakamiHouses_2_Steven_Text_2
	trainerbattle_no_intro TRAINER_STEVEN, KitakamiHouses_2_Steven_Text_3
	msgbox KitakamiHouses_2_Steven_Text_4
	giveitem ITEM_JADE_ORB
	waitmessage
	msgbox KitakamiHouses_2_Steven_Text_5
	waitmessage
	closemessage
	setflag FLAG_BEAT_STEVEN_KITAKAMI
	moveobjecttocoords LOCALID_KITAKAMI_STEVEN, 28, 8, DIR_SOUTH
	waitmovement LOCALID_KITAKAMI_STEVEN
	delay 15
	playse SE_EXIT
	removeobject LOCALID_KITAKAMI_STEVEN
	release
	end


PorygonPC::
	lockall
	playmoncry SPECIES_PORYGON_Z, CRY_MODE_NORMAL
	msgbox PorygonPC_Text_0
	goto EventScript_PCMainMenu
	return


KitakamiHouses_3_Lady::
	msgbox KitakamiHouses_3_Lady_Text_0, MSGBOX_NPC
	return


KitakamiHouses_3_Man::
	msgbox KitakamiHouses_3_Man_Text_0, MSGBOX_NPC
	return


KitakamiHouses_2_Steven_Movement_0:
	face_player
	step_end

KitakamiHouses_1_Oldman_Text_0:
	.string "Come back tomorrow when I have\n"
	.string "prepared another batch!$"

KitakamiHouses_1_Oldman_Text_1:
	.string "Ho ho ho! \p"
	.string "I'm the best candy baker in the\n"
	.string "entire Johto! \p"
	.string "Here, have some from my daily batch!$"

KitakamiHouses_3_Sinistea_Text_0:
	.string "Sinistea: Siii!$"

KitakamiHouses_2_Steven_Text_0:
	.string "That face of determination... I assume\n"
	.string "you have become the Champion of Johto?\p"
	.string "...\p"
	.string "Impressive! I was right about your\n"
	.string "potential as a trainer.\p"
	.string "I'd be more than happy to battle you\n"
	.string "now, if you are alright with that.$"

KitakamiHouses_2_Steven_Text_1:
	.string "Are you ready to face me?$"

KitakamiHouses_2_Steven_Text_2:
	.string "Splendid, I'll hold nothing back\n"
	.string "and I expect you to do the same!$"

KitakamiHouses_2_Steven_Text_3:
	.string "Outstanding, you truly have earned\n"
	.string "the title of a Champion.$"

KitakamiHouses_2_Steven_Text_4:
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
	.string "I think I'll start heading out to \n"
	.string "explore new places now. \p"
	.string "I hope our paths cross again some day, \n"
	.string "{PLAYER}.$"

KitakamiHouses_2_Steven_Text_6:
	.string "If you end up becoming a Champion of\n"
	.string "the region, you should come see me.\p"
	.string "I would love to battle you with my\n"
	.string "full strength.$"

KitakamiHouses_2_Steven_Text_7:
	.string "Oh, hello. Who might you be?\p"
	.string "...\p"
	.string "{PLAYER}? \n"
	.string "Nice to meet you.\p"
	.string "My name is Steven, I hail from the Hoenn\n"
	.string "region in search of rare stones.$"

KitakamiHouses_2_Steven_Text_8:
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
	.string "I have high expectations for you.$"

PorygonPC_Text_0:
	.string "{PLAYER} booted up the Porygon \n"
	.string "remote PC.$"

KitakamiHouses_3_Lady_Text_0:
	.string "Life is peaceful here with my family,\n"
	.string "I couldn't ask for much else.$"

KitakamiHouses_3_Man_Text_0:
	.string "This town is protected by Ogerpon, who\n"
	.string "sometimes visits this town. \p"
	.string "Personally I have never seen it, \n"
	.string "but kids say they have.$"
