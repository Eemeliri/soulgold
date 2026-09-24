OlivineCity_House4_MapScripts::
	.byte 0


OlivineTutorMoveMaster::
	lock
	faceplayer
	goto_if_set FLAG_TUTOR_MOVES_UNLOCKED, OlivineTutorMoveMaster_2
	msgbox OlivineTutorMoveMaster_Text_1
	showmoneybox 0, 0
	msgbox OlivineTutorMoveMaster_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq OlivineTutorMoveMaster_5
	hidemoneybox
	msgbox OlivineTutorMoveMaster_Text_6
	release
	end

OlivineTutorMoveMaster_2:
	msgbox OlivineTutorMoveMaster_Text_0
	release
	end

OlivineTutorMoveMaster_4:
	release
	end

OlivineTutorMoveMaster_5:
	checkmoney 44444
	compare VAR_RESULT, FALSE
	goto_if_eq OlivineTutorMoveMaster_9
	removemoney 44444
	updatemoneybox 0
	playse SE_SHOP
	waitse
	setflag FLAG_TUTOR_MOVES_UNLOCKED
	special Achievement_CheckAll
	msgbox OlivineTutorMoveMaster_Text_4
	hidemoneybox
	closemessage
	fadescreen FADE_TO_BLACK
	delay 60
	fadescreen FADE_FROM_BLACK
	delay 20
	playfanfare MUS_OBTAIN_ITEM
	msgbox OlivineTutorMoveMaster_Text_5
	waitse
	msgbox OlivineTutorMoveMaster_Text_0
	goto OlivineTutorMoveMaster_4

OlivineTutorMoveMaster_9:
	msgbox OlivineTutorMoveMaster_Text_3
	hidemoneybox
	release
	end


OlivineTutorMoveMaster_Text_0:
	.string "You can teach Tutor Moves by\n"
	.string "pressing Start on the Battle Moves\l"
	.string "page of the Summary Screen and\l"
	.string "switching to the Tutor Moves page.$"

OlivineTutorMoveMaster_Text_1:
	.string "I'm the Tutor Move Master.\p"
	.string "I know all there is to know about Tutor\n"
	.string "Moves.\p"
	.string "If you wish, I can teach you all that I \n"
	.string "know for a one-time fee of ¥44,444.$"

OlivineTutorMoveMaster_Text_2:
	.string "What do you say? Do you wish to learn\n"
	.string "everything about Tutor Moves?$"

OlivineTutorMoveMaster_Text_3:
	.string "It seems you do not have the money\n"
	.string "to learn. Shame.$"

OlivineTutorMoveMaster_Text_4:
	.string "Thank you for the business!\p"
	.string "Now let me teach you the grand\n"
	.string "secrets of the Tutor Moves.$"

OlivineTutorMoveMaster_Text_5:
	.string "You can now teach Tutor Moves to\n"
	.string "your Pokémon!$"

OlivineTutorMoveMaster_Text_6:
	.string "A pity.$"
