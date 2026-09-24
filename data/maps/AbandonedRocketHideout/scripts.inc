AbandonedRocketHideout_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_ARH_PUZZLE1, AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD_2
AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	goto_if_set FLAG_ARH_PUZZLE3, AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD_4
	return

AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD_2:
	setmetatile 17, 10, 0x500, FALSE
	setmetatile 18, 10, 0x500, FALSE
	setmetatile 19, 10, 0x500, FALSE
	setmetatile 17, 11, 0x500, FALSE
	setmetatile 18, 11, 0x500, FALSE
	setmetatile 19, 11, 0x500, FALSE
	goto AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD_1

AbandonedRocketHideout_MapScripts_MAP_SCRIPT_ON_LOAD_4:
	setmetatile 10, 10, 0x500, FALSE
	setmetatile 11, 10, 0x500, FALSE
	setmetatile 12, 10, 0x500, FALSE
	setmetatile 10, 11, 0x500, FALSE
	setmetatile 11, 11, 0x500, FALSE
	setmetatile 12, 11, 0x500, FALSE
	return


ARH_Note1::
	msgbox ARH_Note1_Text_0, MSGBOX_SIGN
	return


ARH_MiddleDoor::
	goto_if_set FLAG_ARH_PUZZLE3, ARH_MiddleDoor_1
	msgbox ARH_MiddleDoor_Text_1, MSGBOX_SIGN
	return

ARH_MiddleDoor_1:
	msgbox ARH_MiddleDoor_Text_0, MSGBOX_SIGN
	return


ARH_RightDoor::
	goto_if_set FLAG_ARH_PUZZLE1, ARH_RightDoor_1
	msgbox ARH_RightDoor_Text_1, MSGBOX_SIGN
	return

ARH_RightDoor_1:
	msgbox ARH_RightDoor_Text_0, MSGBOX_SIGN
	return


ARH_Note2::
	msgbox ARH_Note2_Text_0, MSGBOX_SIGN
	return


ARH_Computer1::
	lock
	goto_if_set FLAG_ARH_PUZZLE1, ARH_Computer1_2
	playse SE_PC_ON
	msgbox ARH_Computer1_Text_1
	waitse
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, ARH_Computer1_Text_2, ARH_Computer1_Text_3, ARH_Computer1_Text_4, ARH_Computer1_Text_5, ARH_Computer1_Text_6
	switch VAR_RESULT
	case 3, ARH_Computer1_6
	case 4, ARH_Computer1_7
	playse SE_FAILURE
	msgbox ARH_Computer1_Text_8
ARH_Computer1_4:
	release
	return

ARH_Computer1_2:
	msgbox ARH_Computer1_Text_0, MSGBOX_SIGN
	release
	end

ARH_Computer1_6:
	playse SE_SUCCESS
	msgbox ARH_Computer1_Text_7
	setflag FLAG_ARH_PUZZLE1
	setmetatile 17, 10, 0x500, FALSE
	setmetatile 18, 10, 0x500, FALSE
	setmetatile 19, 10, 0x500, FALSE
	setmetatile 17, 11, 0x500, FALSE
	setmetatile 18, 11, 0x500, FALSE
	setmetatile 19, 11, 0x500, FALSE
	playse SE_EXIT
	special DrawWholeMapView
	goto ARH_Computer1_4

ARH_Computer1_7:
	playse SE_PC_OFF
	goto ARH_Computer1_4


ARH_BoxLeft::
	msgbox ARH_BoxLeft_Text_0, MSGBOX_SIGN
	return


ARH_BoxRight1::
	msgbox ARH_BoxRight1_Text_0, MSGBOX_SIGN
	return


ARH_BoxRightRoomRightOne2::
	goto_if_set FLAG_ARH_PUZZLE2, ARH_BoxRightRoomRightOne2_2
	lock
	msgbox ARH_BoxRightRoomRightOne2_Text_1
	playfanfare MUS_HG_OBTAIN_ITEM
	msgbox ARH_BoxRightRoomRightOne2_Text_2
	waitfanfare
	setflag FLAG_ARH_PUZZLE2
	release
	return

ARH_BoxRightRoomRightOne2_2:
	msgbox ARH_BoxRightRoomRightOne2_Text_0, MSGBOX_SIGN
	end


ARH_BoxWrong::
	random 6
	switch VAR_RESULT
	case 0, ARH_BoxWrong_2
	case 1, ARH_BoxWrong_3
	case 2, ARH_BoxWrong_4
	case 3, ARH_BoxWrong_5
	case 4, ARH_BoxWrong_6
	case 5, ARH_BoxWrong_7
	return

ARH_BoxWrong_2:
	msgbox ARH_BoxWrong_Text_0, MSGBOX_SIGN
	return

ARH_BoxWrong_3:
	msgbox ARH_BoxWrong_Text_1, MSGBOX_SIGN
	return

ARH_BoxWrong_4:
	msgbox ARH_BoxWrong_Text_2, MSGBOX_SIGN
	return

ARH_BoxWrong_5:
	msgbox ARH_BoxWrong_Text_3, MSGBOX_SIGN
	return

ARH_BoxWrong_6:
	msgbox ARH_BoxWrong_Text_4, MSGBOX_SIGN
	return

ARH_BoxWrong_7:
	msgbox ARH_BoxWrong_Text_5, MSGBOX_SIGN
	return


ARH_MachineRight::
	goto_if_set FLAG_ARH_PUZZLE3, ARH_MachineRight_2
	goto_if_unset FLAG_ARH_PUZZLE2, ARH_MachineRight_5
	lock
	msgbox ARH_MachineRight_Text_2
	playse SE_CLICK
	waitse
	setflag FLAG_ARH_PUZZLE3
	setmetatile 10, 10, 0x500, FALSE
	setmetatile 11, 10, 0x500, FALSE
	setmetatile 12, 10, 0x500, FALSE
	setmetatile 10, 11, 0x500, FALSE
	setmetatile 11, 11, 0x500, FALSE
	setmetatile 12, 11, 0x500, FALSE
	playse SE_EXIT
	special DrawWholeMapView
	msgbox ARH_MachineRight_Text_3
	release
	return

ARH_MachineRight_2:
	msgbox ARH_MachineRight_Text_0, MSGBOX_SIGN
	end

ARH_MachineRight_5:
	msgbox ARH_MachineRight_Text_1, MSGBOX_SIGN
	end


ARH_MachineRight2::
	msgbox ARH_MachineRight2_Text_0, MSGBOX_SIGN
	return


ARH_Note1_Text_0:
	.string "A brittle memo is pinned beneath\n"
	.string "the dust...\p"
	.string "PROJECT SHADOW - CLOSURE ORDER\p"
	.string "All Shadow specimens are to be\n"
	.string "discarded immediately.\p"
	.string "Burn the research.\p"
	.string "Leave nothing.$"

ARH_MiddleDoor_Text_0:
	.string "The central shutter is open.$"

ARH_MiddleDoor_Text_1:
	.string "CENTRAL ARCHIVE\p"
	.string "POWER RELAY: NOT DETECTED\p"
	.string "The shutter is locked in place.$"

ARH_RightDoor_Text_0:
	.string "STORAGE BAY R\p"
	.string "ACCESS GRANTED$"

ARH_RightDoor_Text_1:
	.string "STORAGE BAY R\p"
	.string "SEALED BY SHADOW PROTOCOL\p"
	.string "Remote authorization is required.$"

ARH_Note2_Text_0:
	.string "Most of the report has been shredded.\n"
	.string "One paragraph survives...\p"
	.string "'Houndour was the first subject to\n"
	.string "retain a stable Shadow response.\p"
	.string "Earlier Rattata and Zubat trials were\n"
	.string "judged unusable.'$"

ARH_Computer1_Text_0:
	.string "The terminal displays a single line:\p"
	.string "STORAGE BAY R - UNSEALED$"

ARH_Computer1_Text_1:
	.string "The old terminal sputters to life.\p"
	.string "SHADOW FAILSAFE\n"
	.string "Enter the Pokédex index of the first\l"
	.string "viable subject.$"

ARH_Computer1_Text_2:
	.string "019$"

ARH_Computer1_Text_3:
	.string "041$"

ARH_Computer1_Text_4:
	.string "198$"

ARH_Computer1_Text_5:
	.string "228$"

ARH_Computer1_Text_6:
	.string "Cancel$"

ARH_Computer1_Text_7:
	.string "SUBJECT 228: HOUNDOUR\n"
	.string "AUTHORIZATION CONFIRMED\p"
	.string "Storage Bay R is now unsealed.$"

ARH_Computer1_Text_8:
	.string "SUBJECT RECORD REJECTED.$"

ARH_BoxLeft_Text_0:
	.string "A clipboard is wedged between the\n"
	.string "packing foam and the crate wall.\p"
	.string "SUBJECT INDEX\n"
	.string "019 - RATTATA\l"
	.string "041 - ZUBAT\l"
	.string "198 - MURKROW\l"
	.string "228 - HOUNDOUR$"

ARH_BoxRight1_Text_0:
	.string "The crate contains a Rocket uniform\n"
	.string "and a note written in red ink...\p"
	.string "'My locker code is 041.\n"
	.string "Markov, stay out this time.'$"

ARH_BoxRightRoomRightOne2_Text_0:
	.string "The fitted compartment is empty.$"

ARH_BoxRightRoomRightOne2_Text_1:
	.string "Something heavy shifts beneath a false\n"
	.string "bottom.$"

ARH_BoxRightRoomRightOne2_Text_2:
	.string "{PLAYER} found the Magnetic Relay!\p"
	.string "It looks like it belongs in one of the\n"
	.string "warehouse machines.$"

ARH_BoxWrong_Text_0:
	.string "Nothing but crushed Poké Ball\n"
	.string "shells. Every one has been neatly\l"
	.string "stamped REJECTED.$"

ARH_BoxWrong_Text_1:
	.string "Hundreds of left-handed black\n"
	.string "gloves.\p"
	.string "There is not one right glove.$"

ARH_BoxWrong_Text_2:
	.string "A shipping manifest reads:\p"
	.string "SINISTER CAPES - 40\n"
	.string "DRAMATIC WIND MACHINES - 40$"

ARH_BoxWrong_Text_3:
	.string "A fossilized RageCandyBar sticks\n"
	.string "to the packing paper.$"

ARH_BoxWrong_Text_4:
	.string "The crate is full of fake moustaches\n"
	.string "labeled EXECUTIVE EMERGENCY KIT.$"

ARH_BoxWrong_Text_5:
	.string "This crate is labeled\n"
	.string "LOTS OF VOLTORBS.\p"
	.string "It is empty... \p"
	.string "You feel a sense of relief.$"

ARH_MachineRight_Text_0:
	.string "The restored relay hums steadily.\p"
	.string "CENTRAL ARCHIVE - ACCESS ONLINE$"

ARH_MachineRight_Text_1:
	.string "CENTRAL SHUTTER CONTROL\p"
	.string "ERROR: MAGNETIC RELAY MISSING\p"
	.string "A relay-shaped socket is empty.$"

ARH_MachineRight_Text_2:
	.string "The magnetic relay fits the empty\n"
	.string "socket perfectly.$"

ARH_MachineRight_Text_3:
	.string "The old machinery hums to life.\p"
	.string "The central shutter seems to\n"
	.string "have opened in the hallway.$"

ARH_MachineRight2_Text_0:
	.string "UMBRA MEASUREMENT MONITOR\p"
	.string "The final readings are frozen on the\n"
	.string "dim display.\p"
	.string "HEART RATE: 220\n"
	.string "AGGRESSION: ERROR\l"
	.string "EMOTION: 0%$"
