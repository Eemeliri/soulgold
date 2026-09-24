DarkrainInnBedroom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DarkrainInnBedroom_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

DarkrainInnBedroom_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	compare VAR_DARKRAI_INN_PROGRESS, 1
	goto_if_eq DarkrainInnBedroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	setdynamicwarp MAP_DARKRAI_INN1RUINED, 0
	return

DarkrainInnBedroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	setdynamicwarp MAP_DARKRAI_INN1, 0
	return


DarkraiInnBedroom_Phone::
	msgbox DarkraiInnBedroom_Phone_Text_0, MSGBOX_SIGN
	return


DarkraiInnBedroom_Bed::
	lock
	compare VAR_DARKRAI_INN_PROGRESS, 1
	goto_if_eq DarkraiInnBedroom_Bed_2
	msgbox DarkraiInnBedroom_Bed_Text_8
DarkraiInnBedroom_Bed_1:
	release
	end

DarkraiInnBedroom_Bed_2:
	msgbox DarkraiInnBedroom_Bed_Text_0
	msgbox DarkraiInnBedroom_Bed_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DarkraiInnBedroom_Bed_5
	msgbox DarkraiInnBedroom_Bed_Text_7
	closemessage
	setvar VAR_DARKRAI_INN_PROGRESS, 2
	setdynamicwarp MAP_DARKRAI_INN1RUINED, 0
	playmoncry SPECIES_CRESSELIA, CRY_MODE_NORMAL
	turnobject LOCALID_PLAYER, DIR_SOUTH
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmoncry
	waitmovement 0
	release
	end

DarkraiInnBedroom_Bed_5:
	msgbox DarkraiInnBedroom_Bed_Text_2
	dynmultichoice 20, 4, TRUE, 4, 0, DYN_MULTICHOICE_CB_NONE, DarkraiInnBedroom_Bed_Text_3, DarkraiInnBedroom_Bed_Text_3, DarkraiInnBedroom_Bed_Text_3, DarkraiInnBedroom_Bed_Text_3, DarkraiInnBedroom_Bed_Text_4
	switch VAR_RESULT
	case 0, DarkraiInnBedroom_Bed_9
	case 1, DarkraiInnBedroom_Bed_9
	case 2, DarkraiInnBedroom_Bed_9
	case 3, DarkraiInnBedroom_Bed_9
	case 4, DarkraiInnBedroom_Bed_10
	goto DarkraiInnBedroom_Bed_1

DarkraiInnBedroom_Bed_9:
	msgbox DarkraiInnBedroom_Bed_Text_5
	applymovement LOCALID_PLAYER, DarkraiInnBedroom_Bed_Movement_0
	waitmovement
	fadescreenspeed FADE_TO_BLACK, 24
	special DoSoftReset
	end

DarkraiInnBedroom_Bed_10:
	msgbox DarkraiInnBedroom_Bed_Text_6
	closemessage
	setvar VAR_DARKRAI_INN_PROGRESS, 2
	setdynamicwarp MAP_DARKRAI_INN1RUINED, 0
	playmoncry SPECIES_CRESSELIA, CRY_MODE_NORMAL
	turnobject LOCALID_PLAYER, DIR_SOUTH
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmoncry
	waitmovement 0
	release
	end


DarkraiInnBedroom_Bed_Movement_0:
	walk_slow_right
	face_down
	step_end

DarkraiInnBedroom_Phone_Text_0:
	.string "An antique telephone.\p"
	.string "The cord doesn't seem to connect\n"
	.string "anywhere.$"

DarkraiInnBedroom_Bed_Text_0:
	.string "Just staring at this bed makes you feel\n"
	.string "drowsy.\p"
	.string "Perhaps it's time to take a rest and\n"
	.string "close your eyes for a little while...$"

DarkraiInnBedroom_Bed_Text_1:
	.string "Take a short nap..?$"

DarkraiInnBedroom_Bed_Text_2:
	.string "Was there something you forgot...?$"

DarkraiInnBedroom_Bed_Text_3:
	.string "Sleep$"

DarkraiInnBedroom_Bed_Text_4:
	.string "Resist$"

DarkraiInnBedroom_Bed_Text_5:
	.string "It was probably nothing that can't wait\n"
	.string "a bit...$"

DarkraiInnBedroom_Bed_Text_6:
	.string "You feel a chill and decide to step away\n"
	.string "from the bed.$"

DarkraiInnBedroom_Bed_Text_7:
	.string "You decide to step away from the bed.$"

DarkraiInnBedroom_Bed_Text_8:
	.string "Now's not the time to be napping.$"
