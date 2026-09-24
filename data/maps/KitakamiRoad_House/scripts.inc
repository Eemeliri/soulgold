KitakamiRoad_House_MapScripts::
	.byte 0


KitakamiBorder_VictiniLady::
	lock
	faceplayer
	goto_if_set FLAG_GOT_VICTINI, KitakamiBorder_VictiniLady_2
	goto_if_unset FLAG_IS_CHAMPION, KitakamiBorder_VictiniLady_5
	goto_if_unset FLAG_STARTED_VICTINI_QUEST, KitakamiBorder_VictiniLady_8
	checktrainerflag TRAINER_FALKNER_2
	goto_if 1, KitakamiBorder_VictiniLady_16
KitakamiBorder_VictiniLady_13:
	msgbox KitakamiBorder_VictiniLady_Text_11
	release
	end

KitakamiBorder_VictiniLady_2:
	msgbox KitakamiBorder_VictiniLady_Text_0
	release
	end

KitakamiBorder_VictiniLady_5:
	goto_if_unset FLAG_MET_VICTINI_LADY, KitakamiBorder_VictiniLady_11
	msgbox KitakamiBorder_VictiniLady_Text_3
	release
	end

KitakamiBorder_VictiniLady_8:
	goto_if_unset FLAG_MET_VICTINI_LADY, KitakamiBorder_VictiniLady_31
	msgbox KitakamiBorder_VictiniLady_Text_5
KitakamiBorder_VictiniLady_30:
	msgbox KitakamiBorder_VictiniLady_Text_6
	setflag FLAG_STARTED_VICTINI_QUEST
	release
	end

KitakamiBorder_VictiniLady_11:
	msgbox KitakamiBorder_VictiniLady_Text_1
	msgbox KitakamiBorder_VictiniLady_Text_2
	setflag FLAG_MET_VICTINI_LADY
	release
	end

KitakamiBorder_VictiniLady_14:
	closemessage
	applymovement LOCALID_VICTINI_LADY, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	msgbox KitakamiBorder_VictiniLady_Text_7
	msgbox KitakamiBorder_VictiniLady_Text_8
	msgbox KitakamiBorder_VictiniLady_Text_9
	closemessage
	delay 30
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_VICTINI
	bufferspeciesname STR_VAR_1, SPECIES_VICTINI
	givemon SPECIES_VICTINI, 50
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setflag FLAG_GOT_VICTINI
	special Achievement_CheckAll
	delay 60
	msgbox KitakamiBorder_VictiniLady_Text_10
	release
	end

KitakamiBorder_VictiniLady_15:
	checktrainerflag TRAINER_WHITNEY_2
	goto_if 1, KitakamiBorder_VictiniLady_20
	goto KitakamiBorder_VictiniLady_13

KitakamiBorder_VictiniLady_16:
	checktrainerflag TRAINER_BUGSY_2
	goto_if 1, KitakamiBorder_VictiniLady_15
	goto KitakamiBorder_VictiniLady_13

KitakamiBorder_VictiniLady_19:
	checktrainerflag TRAINER_CHUCK_2
	goto_if 1, KitakamiBorder_VictiniLady_24
	goto KitakamiBorder_VictiniLady_13

KitakamiBorder_VictiniLady_20:
	checktrainerflag TRAINER_MORTY_2
	goto_if 1, KitakamiBorder_VictiniLady_19
	goto KitakamiBorder_VictiniLady_13

KitakamiBorder_VictiniLady_23:
	checktrainerflag TRAINER_PRYCE_2
	goto_if 1, KitakamiBorder_VictiniLady_27
	goto KitakamiBorder_VictiniLady_13

KitakamiBorder_VictiniLady_24:
	checktrainerflag TRAINER_JASMINE_2
	goto_if 1, KitakamiBorder_VictiniLady_23
	goto KitakamiBorder_VictiniLady_13

KitakamiBorder_VictiniLady_27:
	checktrainerflag TRAINER_CLAIR_2
	goto_if 1, KitakamiBorder_VictiniLady_14
	goto KitakamiBorder_VictiniLady_13

KitakamiBorder_VictiniLady_31:
	msgbox KitakamiBorder_VictiniLady_Text_1
	msgbox KitakamiBorder_VictiniLady_Text_4
	setflag FLAG_MET_VICTINI_LADY
	goto KitakamiBorder_VictiniLady_30


KitakamiBorder_VictiniLady_Text_0:
	.string "Victini chose well.\p"
	.string "Keep our Leaders ambitious, won't\n"
	.string "you? \p"
	.string "Retirement gets dreadfully dull \n"
	.string "otherwise.$"

KitakamiBorder_VictiniLady_Text_1:
	.string "I once served on Johto's Gym\n"
	.string "Leader Board.\p"
	.string "Don't look so impressed. It was\n"
	.string "mostly budgets, bickering, and\l"
	.string "bruised egos.$"

KitakamiBorder_VictiniLady_Text_2:
	.string "These days, I watch promising\n"
	.string "Trainers.\p"
	.string "You look like you are still a bit\n"
	.string "wet behind the ears.\p"
	.string "Still, I'll keep an eye on you.$"

KitakamiBorder_VictiniLady_Text_3:
	.string "Still finding your footing? Good.\p"
	.string "I'll keep an eye on you. Try to give\n"
	.string "me something worth watching.$"

KitakamiBorder_VictiniLady_Text_4:
	.string "A Champion, are you? Good.\p"
	.string "Titles make some Trainers soft.\n"
	.string "Let's see what you're made of.$"

KitakamiBorder_VictiniLady_Text_5:
	.string "So, our promising Trainer is\n"
	.string "a Champion now.\p"
	.string "Not bad. \p"
	.string "Do stop looking so pleased though.\n"
	.string "Titles breed complacency.$"

KitakamiBorder_VictiniLady_Text_6:
	.string "I may be retired, but I still\n"
	.string "cultivate talent.\p"
	.string "Help me test whether the current Gym \n"
	.string "Leaders are still fit for their jobs.\p"
	.string "Beat all eight Leaders at their full\n"
	.string "strength. \p"
	.string "Make them grow and nurture your\n"
	.string "own potential further.$"

KitakamiBorder_VictiniLady_Text_7:
	.string "Well, well. All eight, beaten at\n"
	.string "their best.\p"
	.string "You didn't merely collect victories.\p"
	.string "You gave every one of them a reason\n"
	.string "to keep striving for even greater\l"
	.string "heights.$"

KitakamiBorder_VictiniLady_Text_8:
	.string "I hope they learned as much from\n"
	.string "those battles as you did.\p"
	.string "If not, I'll send them a very\n"
	.string "pointed memo.$"

KitakamiBorder_VictiniLady_Text_9:
	.string "Talent like yours deserves a proper\n"
	.string "investment.\p"
	.string "Take this Victini. \p"
	.string "It seems rather fond of you now, \n"
	.string "having watched you grow stronger \l"
	.string "through every victory.$"

KitakamiBorder_VictiniLady_Text_10:
	.string "Don't look so stunned. I said I\n"
	.string "nurture the region's elite.\p"
	.string "Now off you go. I'm quite busy\n"
	.string "despite being retired.$"

KitakamiBorder_VictiniLady_Text_11:
	.string "Back already? Unless all eight Leaders\n"
	.string "have shown you their full strength,\l"
	.string "you're wasting both our time.\p"
	.string "Go on. Inspire some hope in\n"
	.string "this old lady.$"
