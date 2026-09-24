GoldenrodApartment_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodApartment_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

GoldenrodApartment_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_MAGERNA_DOOR_OPENED, GoldenrodApartment_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

GoldenrodApartment_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 62, 8, 0x401, FALSE
	return


GoldenrodApartments_BasementGuard::
	msgbox GoldenrodApartments_BasementGuard_Text_0
	checkspecies SPECIES_ROTOM
	compare VAR_RESULT, FALSE
	goto_if_eq GoldenrodApartments_BasementGuard_2
	msgbox GoldenrodApartments_BasementGuard_Text_1
	closemessage
	setflag FLAG_HIDE_GROD_APARTMENTS_GUARD
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_APARTMENT_GUARD
	delay 60
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

GoldenrodApartments_BasementGuard_2:
	release
	end


GoldenrodApartments_OldLady::
	msgbox GoldenrodApartments_OldLady_Text_0, MSGBOX_NPC
	return


GoldenrodApartments_Child::
	msgbox GoldenrodApartments_Child_Text_0, MSGBOX_NPC
	return


GoldenrodApartments_Girl::
	msgbox GoldenrodApartments_Girl_Text_0, MSGBOX_NPC
	return


GoldenrodApartments_Breloom::
	lock
	playmoncry SPECIES_BRELOOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox GoldenrodApartments_Breloom_Text_0
	waitmessage
	release
	end


GoldenrodApartments_Gameboykid::
	msgbox GoldenrodApartments_Gameboykid_Text_0, MSGBOX_NPC
	return


GoldenrodApartments_ScientistF::
	msgbox GoldenrodApartments_ScientistF_Text_0, MSGBOX_NPC
	return


GoldenrodApartments_ScientistM::
	msgbox GoldenrodApartments_ScientistM_Text_0, MSGBOX_NPC
	return


GoldenrodApartments_LockedDoor::
	lock
	goto_if_set FLAG_MAGERNA_DOOR_OPENED, GoldenrodApartments_LockedDoor_2
	goto_if_set FLAG_GOT_MAGERNA_KEY, GoldenrodApartments_LockedDoor_5
	msgbox GoldenrodApartments_LockedDoor_Text_3
	release
	end

GoldenrodApartments_LockedDoor_2:
	msgbox GoldenrodApartments_LockedDoor_Text_0
	release
	end

GoldenrodApartments_LockedDoor_5:
	msgbox GoldenrodApartments_LockedDoor_Text_1
	closemessage
	playse SE_UNLOCK
	setmetatile 62, 8, 0x401, FALSE
	special DrawWholeMapView
	setflag FLAG_MAGERNA_DOOR_OPENED
	waitse
	setflag FLAG_HIDE_MAGERNA_POLICE
	removeobject LOCALID_M_POLICE1
	removeobject LOCALID_M_POLICE2
	msgbox GoldenrodApartments_LockedDoor_Text_2
	release
	end


GoldenrodApartments_Apartment1::
	msgbox GoldenrodApartments_Apartment1_Text_0, MSGBOX_SIGN
	return


GoldenrodApartments_Apartment2::
	msgbox GoldenrodApartments_Apartment2_Text_0, MSGBOX_SIGN
	return


GoldenrodApartments_Apartment3::
	msgbox GoldenrodApartments_Apartment3_Text_0, MSGBOX_SIGN
	return


MagearnaEncounter::
	lock
	faceplayer
	bosslegendaryencounterwithmoves SPECIES_MAGEARNA, 75, LOCALID_MAGEARNA, FLAG_HIDE_MAGEARNA, 4, SPECIES_NONE, 110, MOVE_SHIFT_GEAR, MOVE_CALM_MIND, MOVE_DRAINING_KISS, MOVE_STORED_POWER
	release
	end


MadScientistEvent::
	lock
	msgbox MadScientistEvent_Text_0
	msgbox MadScientistEvent_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MadScientistEvent_2
	closemessage
	moveobjecttocoords LOCALID_PLAYER, 53, 14, DIR_NORTH
	waitmovement 0
	delay 15
	playbgm MUS_HG_TEAM_ROCKET_HQ, FALSE
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_1
	waitmovement 0
	msgbox MadScientistEvent_Text_2
	playse SE_LEDGE
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_2
	playse SE_LEDGE
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_2
	waitmovement
	msgbox MadScientistEvent_Text_3
	msgbox MadScientistEvent_Text_4
	delay 30
	turnobject LOCALID_MADSC, DIR_SOUTH
	msgbox MadScientistEvent_Text_5
	msgbox MadScientistEvent_Text_6
	closemessage
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_3
	waitmovement 0
	trainerbattle_no_intro TRAINER_MAD_SCIENTIST, MadScientistEvent_Text_7
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_4
	msgbox MadScientistEvent_Text_8
	closemessage
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_5
	waitmovement 0
	msgbox MadScientistEvent_Text_9
	closemessage
	playmoncry SPECIES_MAGEARNA, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_MAGEARNA, MadScientistEvent_Movement_6
	waitmovement 0
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_7
	waitmovement 0
	bosslegendaryencounterwithmoves SPECIES_MAGEARNA, 75, LOCALID_MAGEARNA, FLAG_HIDE_MAGEARNA, 4, SPECIES_NONE, 110, MOVE_SHIFT_GEAR, MOVE_CALM_MIND, MOVE_DRAINING_KISS, MOVE_STORED_POWER
	playbgm MUS_HG_TEAM_ROCKET_HQ, FALSE
	msgbox MadScientistEvent_Text_10
	msgbox MadScientistEvent_Text_11
	closemessage
	playse SE_PIN
	applymovement LOCALID_MADSC, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	turnobject LOCALID_PLAYER, DIR_SOUTH
	turnobject LOCALID_MADSC, DIR_SOUTH
	waitse
	clearflag FLAG_HIDE_MAGERNA_POLICE
	addobject LOCALID_M_POLICE1
	addobject LOCALID_M_POLICE2
	applymovement LOCALID_M_POLICE1, MadScientistEvent_Movement_8
	applymovement LOCALID_M_POLICE2, MadScientistEvent_Movement_9
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_EAST
	msgbox MadScientistEvent_Text_12
	applymovement LOCALID_MADSC, MadScientistEvent_Movement_4
	waitmovement 0
	msgbox MadScientistEvent_Text_13
	applymovement LOCALID_M_POLICE2, MadScientistEvent_Movement_10
	waitmovement
	msgbox MadScientistEvent_Text_14
	turnobject LOCALID_M_POLICE1, DIR_WEST
	fadedefaultbgm
	msgbox MadScientistEvent_Text_15
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MADSC
	removeobject LOCALID_M_POLICE1
	removeobject LOCALID_M_POLICE2
	setflag FLAG_HIDE_MAGERNA_POLICE
	setflag FLAG_HIDE_MAD_SCIENTIST
	delay 45
	fadescreen FADE_FROM_BLACK
	setvar VAR_MAD_SCIENTIST_EVENT_STATE, 1
	release
	end

MadScientistEvent_2:
	applymovement LOCALID_PLAYER, MadScientistEvent_Movement_0
	waitmovement 0
	release
	end


MadScientistEvent_Movement_0:
	walk_right
	step_end

MadScientistEvent_Movement_1:
	walk_in_place_up
	step_end

MadScientistEvent_Movement_2:
	jump_in_place_up
	step_end

MadScientistEvent_Movement_3:
	walk_down
	step_end

MadScientistEvent_Movement_4:
	walk_in_place_down
	step_end

MadScientistEvent_Movement_5:
	walk_right
	face_up
	step_end

MadScientistEvent_Movement_6:
	walk_down
	delay_16
	walk_down
	step_end

MadScientistEvent_Movement_7:
	face_left
	step_end

MadScientistEvent_Movement_8:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MadScientistEvent_Movement_9:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	face_left
	step_end

MadScientistEvent_Movement_10:
	walk_in_place_left
	step_end

GoldenrodApartments_BasementGuard_Text_0:
	.string "Sorry but this stairway leads to the\n"
	.string "apartments storage. Besides, I don't\l"
	.string "think there's any reason why a trainer\l"
	.string "would want to check out old house\l"
	.string "appliances that have been abandoned\l"
	.string "due to rampant consumerism.$"

GoldenrodApartments_BasementGuard_Text_1:
	.string "...What? You have a Rotom that wants\n"
	.string "check out the appliances? Well... \l"
	.string "I suppose the tenants wouldn't\l"
	.string "use them anyway. Let's say I never\l"
	.string "saw you if anyone asks. I'm going to\l"
	.string "have a coffee break.$"

GoldenrodApartments_OldLady_Text_0:
	.string "The city has been expanding a lot in\n"
	.string "recent years. I fear I've been left\l"
	.string "behind by the rapid changes.$"

GoldenrodApartments_Child_Text_0:
	.string "Mom always comes home late...$"

GoldenrodApartments_Girl_Text_0:
	.string "Our mother works at the radio tower,\n"
	.string "which makes her very busy. Luckily\l"
	.string "we have mom's Breloom to help with\l"
	.string "everything!$"

GoldenrodApartments_Breloom_Text_0:
	.string "Breloom is joyfully doing the dishes!$"

GoldenrodApartments_Gameboykid_Text_0:
	.string "Strange noises can be heard from the\n"
	.string "floor above this. I have never seen\l"
	.string "anyone who lives there though, strange.$"

GoldenrodApartments_ScientistF_Text_0:
	.string "Goldenrod recently invited scientists\n"
	.string "from other regions to the Radio Tower\l"
	.string "for a business meeting.$"

GoldenrodApartments_ScientistM_Text_0:
	.string "These SkyBNB apartments are barely\n"
	.string "equipped with the most basics of\l"
	.string "tools... How vexing.$"

GoldenrodApartments_LockedDoor_Text_0:
	.string "The door is now open.$"

GoldenrodApartments_LockedDoor_Text_1:
	.string "The way seems to be barred by a metal\n"
	.string "door. A small keyhole is visible. \p"
	.string "You used the Apartment Key.$"

GoldenrodApartments_LockedDoor_Text_2:
	.string "The way is now open.$"

GoldenrodApartments_LockedDoor_Text_3:
	.string "The way seems to be barred by a metal\n"
	.string "door. A small keyhole is visible, but\l"
	.string "you have nothing that would fit it.$"

GoldenrodApartments_Apartment1_Text_0:
	.string "Goldenrod Sky Apartments F1$"

GoldenrodApartments_Apartment2_Text_0:
	.string "Goldenrod Sky Apartments F2$"

GoldenrodApartments_Apartment3_Text_0:
	.string "Goldenrod Sky Apartments F3$"

MadScientistEvent_Text_0:
	.string "You sense trouble in this direction.$"

MadScientistEvent_Text_1:
	.string "Are you prepared to go forward?$"

MadScientistEvent_Text_2:
	.string "Scientist: Ha haa! The machine is nearly\n"
	.string "complete! \p"
	.string "I shall have my revenge on those \n"
	.string "Rocket executives for taking my\l"
	.string "research funding!$"

MadScientistEvent_Text_3:
	.string "Scientist: And then! The rest of those\n"
	.string "snobby scientific committee members!\p"
	.string "This will be my ultimate creation!\n"
	.string "Ahahahahahahahahaaaaaaaaaaaaaa!$"

MadScientistEvent_Text_4:
	.string "But first...$"

MadScientistEvent_Text_5:
	.string "Scientist: Who are you and how \n"
	.string "did you get in?!$"

MadScientistEvent_Text_6:
	.string "I don't have time for \n"
	.string "debt collectors or salespeople! \p"
	.string "I will be rid of you!$"

MadScientistEvent_Text_7:
	.string "No! I can't afford this!$"

MadScientistEvent_Text_8:
	.string "Scientist: It seems the tax office has \n"
	.string "sent quite a tough customer this time. \p"
	.string "No matter!\p"
	.string "I've been looking for volunteers\n"
	.string "actually, so this will work out nicely!\p"
	.string "You shall be the first to witness the\n"
	.string "raw power of my mechanical Pokémon!$"

MadScientistEvent_Text_9:
	.string "Scientist: Magearna! Destroy this \n"
	.string "foolish intruder!$"

MadScientistEvent_Text_10:
	.string "Scientist: This... THIS CANNOT BE!\p"
	.string "My creation... Gone? JUST LIKE THAT?\p"
	.string "It was supposed to be invincible!\p"
	.string "This isn't over! I can still-$"

MadScientistEvent_Text_11:
	.string "??? Hold it right there!$"

MadScientistEvent_Text_12:
	.string "Police: You're under arrest for tax \n"
	.string "evasion, having ties to the Team Rocket\l"
	.string "and for developing illegal Pokémon.$"

MadScientistEvent_Text_13:
	.string "Scientist: B-But I was the one whom \n"
	.string "Team Rocket abandoned!\p"
	.string "I'm innocent! I just wanted\n"
	.string "to show them they were in the wrong!$"

MadScientistEvent_Text_14:
	.string "Save it for the judge.$"

MadScientistEvent_Text_15:
	.string "Police: I thank you for help \n"
	.string "subduing this crook. \p"
	.string "They've been holed up here\n"
	.string "for a while, causing all sorts of\l"
	.string "disturbance.\p"
	.string "We'll let you keep the Pokémon if\n"
	.string "you stay quiet about it. \p"
	.string "We trust it will be in good \n"
	.string "hands with you.$"
