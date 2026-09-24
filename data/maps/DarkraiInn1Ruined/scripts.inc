DarkraiInn1Ruined_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DarkraiInn1Ruined_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

DarkraiInn1Ruined_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	return


Inn_RuinedPiano::
	lock
	compare VAR_DARKRAI_INN_PROGRESS, 6
	goto_if_lt Inn_RuinedPiano_2
	compare VAR_DARKRAI_INN_PROGRESS, 6
	goto_if_eq Inn_RuinedPiano_5
	compare VAR_DARKRAI_INN_PROGRESS, 7
	goto_if_ge Inn_RuinedPiano_8
	release
	end

Inn_RuinedPiano_2:
	playse SE_NOTE_G
	msgbox Inn_RuinedPiano_Text_0
	waitse
	release
	end

Inn_RuinedPiano_5:
	msgbox Inn_RuinedPiano_Text_1
	playfanfare MUS_HG_OBTAIN_ITEM
	msgbox Inn_RuinedPiano_Text_2
	waitfanfare
	setvar VAR_DARKRAI_INN_PROGRESS, 7
	release
	end

Inn_RuinedPiano_8:
	msgbox Inn_RuinedPiano_Text_3
	release
	end


Inn_RuinedDrums::
	msgbox Inn_RuinedDrums_Text_0, MSGBOX_SIGN
	return


Inn_RuinedSafe::
	compare VAR_DARKRAI_INN_PROGRESS, 7
	goto_if_lt Inn_RuinedSafe_2
Inn_RuinedSafe_1:
	compare VAR_DARKRAI_INN_PROGRESS, 7
	goto_if_eq Inn_RuinedSafe_5
Inn_RuinedSafe_4:
	release
	end

Inn_RuinedSafe_2:
	msgbox Inn_RuinedSafe_Text_0, MSGBOX_SIGN
	goto Inn_RuinedSafe_1

Inn_RuinedSafe_5:
	msgbox Inn_RuinedSafe_Text_1
	msgbox Inn_RuinedSafe_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Inn_RuinedSafe_7
	goto Inn_RuinedSafe_4

Inn_RuinedSafe_7:
	warp MAP_DARKRAI_INN_FINAL_ROOM, 0
	waitstate
	end


InnHideCresselia::
	setflag FLAG_HIDE_DARKRAI_INN_NPC
	removeobject 1
	setvar VAR_TEMP_0, 1
	return


Inn_RuinedTelephone::
	lock
	compare VAR_DARKRAI_INN_PROGRESS, 4
	goto_if_lt Inn_RuinedTelephone_2
	compare VAR_DARKRAI_INN_PROGRESS, 4
	goto_if_eq Inn_RuinedTelephone_5
Inn_RuinedTelephone_4:
	compare VAR_DARKRAI_INN_PROGRESS, 5
	goto_if_eq Inn_RuinedTelephone_8
Inn_RuinedTelephone_7:
	compare VAR_DARKRAI_INN_PROGRESS, 5
	goto_if_gt Inn_RuinedTelephone_13
	return

Inn_RuinedTelephone_2:
	msgbox Inn_RuinedTelephone_Text_0
	release
	end

Inn_RuinedTelephone_5:
	msgbox Inn_RuinedTelephone_Text_1
	setvar VAR_DARKRAI_INN_PROGRESS, 5
	msgbox Inn_RuinedTelephone_Text_2
	dynmultichoice 20, 4, TRUE, 4, 0, DYN_MULTICHOICE_CB_NONE, Inn_RuinedTelephone_Text_3, Inn_RuinedTelephone_Text_4, Inn_RuinedTelephone_Text_5
	switch VAR_RESULT
	case 0, Inn_RuinedTelephone_11
	case 2, Inn_RuinedTelephone_11
	case 1, Inn_RuinedTelephone_12
	goto Inn_RuinedTelephone_4

Inn_RuinedTelephone_8:
	msgbox Inn_RuinedTelephone_Text_2
	dynmultichoice 20, 4, TRUE, 4, 0, DYN_MULTICHOICE_CB_NONE, Inn_RuinedTelephone_Text_3, Inn_RuinedTelephone_Text_4, Inn_RuinedTelephone_Text_5
	switch VAR_RESULT
	case 0, Inn_RuinedTelephone_16
	case 2, Inn_RuinedTelephone_16
	case 1, Inn_RuinedTelephone_17
	goto Inn_RuinedTelephone_7

Inn_RuinedTelephone_11:
	msgbox Inn_RuinedTelephone_Text_6
	release
	end

Inn_RuinedTelephone_12:
	playse SE_CLICK
	turnobject LOCALID_PLAYER, DIR_EAST
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	setvar VAR_DARKRAI_INN_PROGRESS, 6
	release
	end

Inn_RuinedTelephone_13:
	msgbox Inn_RuinedTelephone_Text_7
	release
	end

Inn_RuinedTelephone_16:
	msgbox Inn_RuinedTelephone_Text_6
	release
	end

Inn_RuinedTelephone_17:
	playse SE_CLICK
	turnobject LOCALID_PLAYER, DIR_EAST
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	setvar VAR_DARKRAI_INN_PROGRESS, 6
	release
	end


Inn_RuinedDoor::
	msgbox Inn_RuinedDoor_Text_0, MSGBOX_SIGN
	return


Inn_NotesOnWall::
	lock
	compare VAR_DARKRAI_INN_PROGRESS, 2
	goto_if_eq Inn_NotesOnWall_2
	msgbox Inn_NotesOnWall_Text_1
Inn_NotesOnWall_1:
	release
	end

Inn_NotesOnWall_2:
	msgbox Inn_NotesOnWall_Text_0
	setvar VAR_DARKRAI_INN_PROGRESS, 3
	goto Inn_NotesOnWall_1


Inn_LuxrayHead::
	lock
	compare VAR_DARKRAI_INN_PROGRESS, 3
	goto_if_eq Inn_LuxrayHead_1
	msgbox Inn_LuxrayHead_Text_2
	release
	end

Inn_LuxrayHead_1:
	msgbox Inn_LuxrayHead_Text_0
	playfanfare MUS_HG_OBTAIN_ITEM
	msgbox Inn_LuxrayHead_Text_1
	waitfanfare
	setvar VAR_DARKRAI_INN_PROGRESS, 4
	release
	end


Inn_RuinedPiano_Text_0:
	.string "The piano has a sound, but\n"
	.string "something feels off.$"

Inn_RuinedPiano_Text_1:
	.string "One of the notes is loose now.\p"
	.string "...\p"
	.string "Under it you find a small key!$"

Inn_RuinedPiano_Text_2:
	.string "{PLAYER} obtained a small key!$"

Inn_RuinedPiano_Text_3:
	.string "Nothing of note is left in the piano.$"

Inn_RuinedDrums_Text_0:
	.string "The drums are covered in dust.$"

Inn_RuinedSafe_Text_0:
	.string "The safe is locked tight.$"

Inn_RuinedSafe_Text_1:
	.string "The key you found fits perfectly into\n"
	.string "the lock of the safe.\p"
	.string "Inside the safe seems to be a hidden\n"
	.string "tunnel dug through the wall.$"

Inn_RuinedSafe_Text_2:
	.string "Enter?$"

Inn_RuinedTelephone_Text_0:
	.string "An old telephone. The dial\n"
	.string "appears to be missing.$"

Inn_RuinedTelephone_Text_1:
	.string "You fit the dial to the telephone.\p"
	.string "...\p"
	.string "It fits perfectly!$"

Inn_RuinedTelephone_Text_2:
	.string "Which number should you try to dial?$"

Inn_RuinedTelephone_Text_3:
	.string "4114$"

Inn_RuinedTelephone_Text_4:
	.string "1144$"

Inn_RuinedTelephone_Text_5:
	.string "4141$"

Inn_RuinedTelephone_Text_6:
	.string "There's no response...$"

Inn_RuinedTelephone_Text_7:
	.string "The telephone is unresponsive.$"

Inn_RuinedDoor_Text_0:
	.string "The door is locked tight, maybe there's\n"
	.string "a key somewhere?$"

Inn_NotesOnWall_Text_0:
	.string "The notes on the wall seem to detail\n"
	.string "the floor plan of the inn. \p"
	.string "There's a detailed marking for all the\n"
	.string "furniture.\p"
	.string "11 Wall Lamps\n"
	.string "4 Large Windows\l"
	.string "4 Sawsbuck Trophies\p"
	.string "...$"

Inn_NotesOnWall_Text_1:
	.string "11 Wall Lamps\n"
	.string "4 Large Windows\l"
	.string "4 Sawsbuck Trophies\p"
	.string "...$"

Inn_LuxrayHead_Text_0:
	.string "This trophy was not accounted for\n"
	.string "in the floor plan. \p"
	.string "You take a closer look...\p"
	.string "In the mouth of the trophy,\n"
	.string "there's a dial.$"

Inn_LuxrayHead_Text_1:
	.string "{PLAYER} obtained a Dial!$"

Inn_LuxrayHead_Text_2:
	.string "A stuffed trophy depicting a head\n"
	.string "of a Pokémon.\p"
	.string "...\p"
	.string "It feels like the eyes are following \n"
	.string "you.$"
