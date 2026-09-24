DarkraiInn1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DarkraiInn1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_LOAD, DarkraiInn1_MapScripts_MAP_SCRIPT_ON_LOAD
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	return

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_OPEN_INN_DOOR, DarkraiInn1_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 24, 3, 0x03C, FALSE
	setmetatile 24, 2, 0x034, FALSE
	return

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_DARKRAI_INN_PROGRESS, 0, DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	msgbox DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	closemessage
	moveobjecttocoords LOCALID_PLAYER, 28, 15, DIR_NORTH
	waitmovement 0
	msgbox DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_1
	playfanfare MUS_HG_OBTAIN_ITEM
	msgbox DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_2
	waitfanfare
	msgbox DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_3
	msgbox DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_4
	setvar VAR_DARKRAI_INN_PROGRESS, 1
	release
	end


Inn_Door404::
	lock
	goto_if_set FLAG_OPEN_INN_DOOR, Inn_Door404_2
	msgbox Inn_Door404_Text_1
	setmetatile 24, 3, 0x03C, FALSE
	setmetatile 24, 2, 0x034, FALSE
	playse SE_EXIT
	special DrawWholeMapView
	setflag FLAG_OPEN_INN_DOOR
	release
	end

	release
	end

Inn_Door404_2:
	msgbox Inn_Door404_Text_0
	release
	end


Inn_Keeper::
	msgbox Inn_Keeper_Text_0, MSGBOX_NPC
	return


Inn_AnimalHead::
	msgbox Inn_AnimalHead_Text_0, MSGBOX_NPC
	return


Inn_LockedDoor::
	msgbox Inn_LockedDoor_Text_0, MSGBOX_NPC
	return


FoggyWindow_Inn::
	msgbox FoggyWindow_Inn_Text_0, MSGBOX_NPC
	return


Inn_OrnatePiano::
	msgbox Inn_OrnatePiano_Text_0, MSGBOX_SIGN
	return


Inn_Drums::
	msgbox Inn_Drums_Text_0, MSGBOX_SIGN
	return


Inn_LockedSafe::
	msgbox Inn_LockedSafe_Text_0, MSGBOX_SIGN
	return


Inn_NoteOnWall::
	msgbox Inn_NoteOnWall_Text_0, MSGBOX_SIGN
	return


Inn_PapersOnWall::
	msgbox Inn_PapersOnWall_Text_0, MSGBOX_SIGN
	return


Inn_TryingToExit::
	lock
	turnobject LOCALID_PLAYER, DIR_SOUTH
	msgbox Inn_TryingToExit_Text_0
	closemessage
	applymovement LOCALID_PLAYER, Inn_TryingToExit_Movement_0
	waitmovement
	release
	end


Inn_ReceptionPhone::
	msgbox Inn_ReceptionPhone_Text_0, MSGBOX_SIGN
	return


Inn_TryingToExit_Movement_0:
	walk_up
	step_end

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "Welcome, honored guest!$"

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_1:
	.string "We are delighted to have you stay\n"
	.string "at our humble inn. \p"
	.string "Here is your room key.$"

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_2:
	.string "{PLAYER} obtained the Moon Key!$"

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_3:
	.string "Your room is number 404, take the stairs\n"
	.string "on your left and it will be right in\l"
	.string "front of you.$"

DarkraiInn1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_4:
	.string "We hope you enjoy your stay.$"

Inn_Door404_Text_0:
	.string "The door to your room is now open.$"

Inn_Door404_Text_1:
	.string "Room 404\p"
	.string "You use your key to unlock the door,\n"
	.string "however the key is now stuck in the\l"
	.string "lock.$"

Inn_Keeper_Text_0:
	.string "We hope you enjoy a peaceful rest\n"
	.string "at our inn.$"

Inn_AnimalHead_Text_0:
	.string "A stuffed trophy depicting a head\n"
	.string "of a Pokémon.\p"
	.string "...\p"
	.string "It feels like the eyes are following \n"
	.string "you.$"

Inn_LockedDoor_Text_0:
	.string "You try to open the door but it\n"
	.string "seems to be locked.$"

FoggyWindow_Inn_Text_0:
	.string "You peek out of the window...\p"
	.string "A thick fog seems to cover your\n"
	.string "view.$"

Inn_OrnatePiano_Text_0:
	.string "An ornate piano sits in front of you.\n"
	.string "It seems to be well maintained.$"

Inn_Drums_Text_0:
	.string "A seemingly new drumset. How cool!$"

Inn_LockedSafe_Text_0:
	.string "A locked safe, you wonder what is\n"
	.string "kept inside.$"

Inn_NoteOnWall_Text_0:
	.string "Seems to be some sort of notice about\n"
	.string "closure of the inn. Odd...$"

Inn_PapersOnWall_Text_0:
	.string "Various notes litter the wall, the text\n"
	.string "is blurry and hard to read.$"

Inn_TryingToExit_Text_0:
	.string "You just arrived, surely there's no\n"
	.string "reason to leave just yet...$"

Inn_ReceptionPhone_Text_0:
	.string "This is probably used to call the \n"
	.string "residents.$"
