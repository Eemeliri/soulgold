
.set LOCALID_DIRECTOR_OFFICE, 1
.set LOCALID_GOLDENROD_ARCHER, 2
.set LOCALID_GOLDENROD_ARIANA, 3
.set LOCALID_PETREL_OFFICE, 4

GoldenrodCity_RadioTower_5F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_5F_OnLoad
	.byte 0

@ During Rocket Takeover, hide Petrel and show the Director (Petrel in disguise)
GoldenrodCity_RadioTower_5F_OnLoad::
	call_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_5F_MapScript_HidePetrel
	end

GoldenrodCity_RadioTower_5F_MapScript_HidePetrel::
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	return


@=======[OFFICE]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Petrel::
	lock
	@ After Rocket Takeover, this is the real Director
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_5F_EventScript_Director
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth
	playse SE_SELECT
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_DIRECTOR_OFFICE
    removeobject LOCALID_RADIOTOWER_OAK
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	addobject LOCALID_PETREL_OFFICE
	applymovement LOCALID_PETREL_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PETREL_2, GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setvar VAR_GOLDENROD_CITY_STATE, 7
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	clearflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth::
	end

GoldenrodCity_RadioTower_5F_EventScript_Petrel2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2, MSGBOX_DEFAULT
	closemessage
	release
	end

@ Modified in 1.2.2 to retroactively fix the Baoba Sequence Break on a 1.2.1 save file
GoldenrodCity_RadioTower_5F_EventScript_Director::
	lock
	faceplayer
	playse SE_SELECT
	goto GoldenrodCity_RadioTower_5F_EventScript_DirectorPath
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_DirectorDone::
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_DirectorWest::
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorWest, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Movement_Spin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_4
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Movement_Spin2:
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Text_FakeDirector1:
	.string "Y-you! You came to rescue me?$"

GoldenrodCity_RadioTower_5F_Text_FakeDirector2:
	.string "Is that what you were expecting?\p"
	.string "Wrong! I'm an imposter!\p"
	.string "I pretended to be the real thing to\n"
	.string "prepare for our takeover.\p"
	.string "Do you want to know where we hid\n"
	.string "the real Director?\p"
	.string "Sure, I'll tell you. But only if you\n"
	.string "can beat me!$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin:
	.string "Ok, Ok. I'll tell you where he is.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter:
	.string "The boss stashed the Director in\n"
	.string "the Underground Warehouse.\p"
	.string "It's at the far end of the Under-\n"
	.string "Ground.\p"
	.string "I am a nice guy, I will give you\n"
	.string "the Basement Key to get to the\l"
	.string "Underground Warehouse.\p"
	.string "But I doubt you'll get that far.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2:
	.string "The boss stashed the Director in\n"
	.string "the Underground Warehouse.\p"
	.string "It's at the far end of the Under-\n"
	.string "Ground.\p"
	.string "You can use the Basement Key to\n"
	.string "get to the Underground Warehouse.\p"
	.string "But I doubt you'll get that far.$"

@=======[STUDIO]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Ben::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_Ben, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_ARIANA::
	trainerbattle_single TRAINER_ARIANA_2 GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen, GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten
	msgbox GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_5F_EventScript_Trigger_NPCS::
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	clearflag FLAG_HIDE_RADIOF5DUDE
	setvar VAR_GOLDENROD_CITY_STATE, 11
	end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveTop:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end


GoldenrodCity_RadioTower_5F_Movement_LeaveMid:
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveBot:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave1:
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave2:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen:
	.string "Remember me from the Hideout in\n"
	.string "Mahogany Town?\p"
	.string "My boss scolded me but I'm stronger.\p"
	.string "I lost then, but I won't this time.$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten:
	.string "This can't be happening!\p"
	.string "I fought hard, but I still lost…\p"
	.string "I'm so sorry Giovanni…$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After:
	.string "{PLAYER}, isn't it?\p"
	.string "A brat like you won't appreciate\n"
	.string "the magnificence of Team Rocket.\p"
	.string "That's too bad. I really admire\n"
	.string "your power.$"

GoldenrodCity_RadioTower_5F_Text_RocketBossSeen:
	.string "Oh? You managed to get this far?\p"
	.string "You must be quite the trainer.\p"
	.string "We intend to take over this Radio\n"
	.string "Station and announce our comeback.\p"
	.string "That should bring our boss Giovanni\n"
	.string "back from his solitary training.\p"
	.string "We are going to regain our former\n"
	.string "glory...\p"
	.string "I won't allow you to interfere with\n"
	.string "our meticulous plans!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten:
	.string "No! Forgive me, Giovanni!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossAfter:
	.string "How could this be?\p"
	.string "Our dreams have come to naught.\p"
	.string "I wasn't up to the task after all.\p"
	.string "Like Giovanni did before me, I will\n"
	.string "disband Team Rocket here today.\p"
	.string "Farewell.$"

GoldenrodCity_RadioTower_5F_Text_DirectorThanks:
	.string "Director: {PLAYER}, thank you!\p"
	.string "Your courageous actions have saved\n"
	.string "Pokémon nationwide.\p"
	.string "I know it's not much, but please\n"
	.string "take this.$"

GoldenrodCity_RadioTower_5F_Text_DirectorThanksAgain:
	.string "Director: {PLAYER}, once again, thank you!\p"
	.string "The large winged Pokémon that flew past\n"
	.string "reminded me, I have a reward for your\l"
	.string "courageous actions.\p"
	.string "I know it's not much, but please\n"
	.string "take this.$"

GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation:
	.string "There used to be a tower right here\n"
	.string "in Goldenrod City.\p"
	.string "But it was old and creaky.\p"
	.string "So we replaced it with our Radio\n"
	.string "Tower.\p"
	.string "We dug up that wing during\n"
	.string "construction.\p"
	.string "I heard that all sorts of Pokémon\n"
	.string "lived in Goldenrod in the past.\p"
	.string "Perhaps…\p"
	.string "That wing has some connection to the\n"
	.string "Tin Tower in Ecruteak City…\p"
	.string "Ok, I better go to my Office.$"

@ 1.2.1 Sequence Break version - slightly different text
GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation2:
	.string "There used to be a tower right here\n"
	.string "in Goldenrod City.\p"
	.string "But it was old and creaky.\p"
	.string "So we replaced it with our Radio\n"
	.string "Tower.\p"
	.string "We dug up that wing during\n"
	.string "construction.\p"
	.string "I heard that all sorts of Pokémon\n"
	.string "lived in Goldenrod in the past.\p"
	.string "Perhaps…\p"
	.string "That wing has some connection to the\n"
	.string "Tin Tower in Ecruteak City…$"

GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation:
	.string "There used to be a tower right here\n"
	.string "in Goldenrod City.\p"
	.string "But it was old and creaky.\p"
	.string "So we replaced it with our Radio\n"
	.string "Tower.\p"
	.string "We dug up that wing during\n"
	.string "construction.\p"
	.string "I heard that all sorts of Pokémon\n"
	.string "lived in Goldenrod in the past.\p"
	.string "Perhaps…\p"
	.string "That wing has some connection to the\n"
	.string "Whirl Islands near Cianwood City…\p"
	.string "Ok, I better go to my Office.$"

@ 1.2.1 Sequence Break version - slightly different text
GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation2:
	.string "There used to be a tower right here\n"
	.string "in Goldenrod City.\p"
	.string "But it was old and creaky.\p"
	.string "So we replaced it with our Radio\n"
	.string "Tower.\p"
	.string "We dug up that wing during\n"
	.string "construction.\p"
	.string "I heard that all sorts of Pokémon\n"
	.string "lived in Goldenrod in the past.\p"
	.string "Perhaps…\p"
	.string "That wing has some connection to the\n"
	.string "Whirl Islands near Cianwood City…$"

GoldenrodCity_RadioTower_5F_Text_DirectorLegendary:
	.string "Ah!\p"
	.string "That reminds me…\p"
	.string "That wing I gave you... I think\n"
	.string "it's related to the Legendary\l"
	.string "Pokémon.\p"
	.string "But! The Legendary Pokémon won't\n"
	.string "appear with just that wing...\p"
	.string "Apparently there is something else\n"
	.string "you need... Or something like that.\p"
	.string "I wonder what it was...\p"
	.string "I can't remember.$"

GoldenrodCity_RadioTower_5F_Text_DirectorFakeout:
	.string "Are you expecting something?\n"
	.string "This is what they call Fake Out.\p"
	.string "I really must go back to my office\n"
	.string "this time. See ya!$"

GoldenrodCity_RadioTower_5F_Text_DirectorIntro:
	.string "Director: Hello, {PLAYER}!\p"
	.string "You know, I love Pokémon.\p"
	.string "I built this Radio Tower so I could\n"
	.string "express my love of Pokémon.\p"
	.string "It would be nice if people enjoyed\n"
	.string "our programs.$"

@ 1.2.1 Sequence Break - Directs player toward Baoba
GoldenrodCity_RadioTower_5F_Text_DirectorWest:
	.string "Director: Hello, {PLAYER}!\p"
	.string "Did you see the large winged Pokémon\n"
	.string "that flew past earlier?\p"
	.string "It's the talk of the town!\n"
	.string "Or should I say, of the Radio Tower?\p"
	.string "It seemed to be headed West, in the\n"
	.string "direction of Route 39.$"

GoldenrodCity_RadioTower_5F_Text_Ben:
	.string "Ben: Do you listen to our music?$"

GoldenrodCity_RadioTower_5F_Text_DirectorOfficeSign:
	.string "5F Director's   Office$"

GoldenrodCity_RadioTower_5F_Text_Studio1Sign:
	.string "5F Studio 1$"

OakRadioTowerF5::
	moveobjecttocoords OBJ_EVENT_ID_PLAYER, 28, 11, DIR_NORTH
	waitmovement 0
	playbgm MUS_HG_OAK, TRUE
	moveobjecttocoords LOCALID_RADIOTOWER_OAK, 28, 10, DIR_SOUTH
	waitmovement 0
	msgbox OakRadioTowerF5_Text_0
	msgbox OakRadioTowerF5_Text_1
	giveitem ITEM_MEGA_RING
	clearflag FLAG_SOUTHPASSAGE_ARIANA
	msgbox OakRadioTowerF5_Text_2
	msgbox OakRadioTowerF5_Text_3
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_RADIOTOWER_OAK
	fadedefaultbgm
	delay 100
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end


RadioTower_5F_Archer::
	lock
	faceplayer
	msgbox RadioTower_5F_Archer_Text_0
	trainerbattle_no_intro TRAINER_ARCHER, RadioTower_5F_Archer_Text_1
	createfieldmugshot MUGSHOT_ARCHER
	msgbox RadioTower_5F_Archer_Text_2
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	playse SE_EXIT
	setvar VAR_GOLDENROD_CITY_STATE, 10
	removeobject LOCALID_GOLDENROD_ARCHER
	removeobject LOCALID_GOLDENROD_ARIANA
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_PETREL_OFFICE
	addobject LOCALID_F5_DIRECTOR_2
	addobject LOCALID_RADIOTOWER_OAK
	playbgm MUS_HG_GOLDENROD, TRUE
	delay 60
	fadescreen FADE_FROM_BLACK
	approachobject LOCALID_F5_DIRECTOR_2, LOCALID_PLAYER, DIR_WEST, DIR_EAST
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_EAST
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox RadioTower_5F_Archer_Text_3
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, RadioTower_5F_Archer_Text_4, RadioTower_5F_Archer_Text_5
	switch VAR_RESULT
	case 0, RadioTower_5F_Archer_3
	case 1, RadioTower_5F_Archer_4
RadioTower_5F_Archer_1:
	msgbox RadioTower_5F_Archer_Text_8
	closemessage
	applymovement LOCALID_F5_DIRECTOR_2, RadioTower_5F_Archer_Movement_0
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_F5_DIRECTOR_2, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_F5_DIRECTOR_2, DIR_WEST
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox RadioTower_5F_Archer_Text_9
	closemessage
	moveobjecttocoords LOCALID_F5_DIRECTOR_2, 29, 5, DIR_NORTH
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	removeobject LOCALID_F5_DIRECTOR_2
	setvar VAR_MAHOGANY_TOWN_STATE, 17
	moveobjecttocoords OBJ_EVENT_ID_PLAYER, 28, 11, DIR_NORTH
	waitmovement 0
	playbgm MUS_HG_OAK, TRUE
	moveobjecttocoords LOCALID_RADIOTOWER_OAK, 28, 10, DIR_SOUTH
	waitmovement 0
	createfieldmugshot MUGSHOT_OAK
	msgbox OakRadioTowerF5_Text_0
	msgbox OakRadioTowerF5_Text_1
	giveitem ITEM_MEGA_RING
	createfieldmugshot MUGSHOT_OAK
	msgbox RadioTower_5F_Archer_Text_10
	msgbox RadioTower_5F_Archer_Text_11
	closemessage
	moveobjecttocoords LOCALID_RADIOTOWER_OAK, 24, 5, DIR_WEST
	waitmovement 0
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	setvar VAR_GOLDENROD_CITY_STATE, 11
	setflag FLAG_ROCKET_TAKEOVER_CAP
	playse SE_EXIT
	removeobject LOCALID_RADIOTOWER_OAK
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

RadioTower_5F_Archer_3:
	setvar VAR_LUGIA_OR_HOOH, 2
	giveitem ITEM_RAINBOW_WING
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox RadioTower_5F_Archer_Text_6
	goto RadioTower_5F_Archer_1

RadioTower_5F_Archer_4:
	setvar VAR_LUGIA_OR_HOOH, 1
	giveitem ITEM_SILVER_WING
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox RadioTower_5F_Archer_Text_7
	goto RadioTower_5F_Archer_1


GoldenrodCity_RadioTower_5F_EventScript_DirectorPath::
	goto_if_set FLAG_IS_CHAMPION, GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_2
	goto GoldenrodCity_RadioTower_5F_EventScript_DirectorDone
GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_1:
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_2:
	goto_if_set FLAG_BEAT_DIRECTOR, GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_5
	msgbox GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_0
	msgbox GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_1
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, FALSE
	msgbox GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_2
	trainerbattle_no_intro TRAINER_DIRECTOR, GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_3
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_4
	compare VAR_LUGIA_OR_HOOH, 1
	goto_if_eq GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_9
	giveitem ITEM_SILVER_WING
	setvar VAR_COMPLETED_LUGIA, 4
	setflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_8:
	setflag FLAG_BEAT_DIRECTOR
	msgbox GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_5
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_5:
	goto GoldenrodCity_RadioTower_5F_EventScript_DirectorDone
	goto GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_1

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_9:
	giveitem ITEM_RAINBOW_WING
	setvar VAR_COMPLETED_HO_OH, 4
	setflag FLAG_HIDE_TINTOWER_GUARD
	goto GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_8


DirectorGotSilver::
	msgbox DirectorGotSilver_Text_0
	release
	end


DirectorGotRainbow::
	msgbox DirectorGotRainbow_Text_0
	release
	end


RadioTower_5F_Archer_Movement_0:
	walk_right
	walk_right
	step_end

OakRadioTowerF5_Text_0:
	.string "{PLAYER}! You've pulled off a miracle\n"
	.string "by taking down Team Rocket!$"

OakRadioTowerF5_Text_1:
	.string "I knew it was the right choice to\n"
	.string "entrust Pokédex to you. I want you to\l"
	.string "have this, I think you've more than\l"
	.string "earned it.$"

OakRadioTowerF5_Text_2:
	.string "That is a Mega Ring. When combined with\n"
	.string "a Mega stone, it allows the bond\l"
	.string "between trainer and Pokémon to fully\l"
	.string "manifest. I'm sure you'll be able to pull\l"
	.string "it off.$"

OakRadioTowerF5_Text_3:
	.string "Now I must start heading back to Kanto,\n"
	.string "I hope you'll pay a visit to the Pallet\l"
	.string "Town at some point! Give my regards to\l"
	.string "Prof. Elm.$"

RadioTower_5F_Archer_Text_0:
	.string "Archer: Oh? You managed to get\n"
	.string "this far...?\p"
	.string "You must be quite the Trainer.\p"
	.string "We intend to take over this\n"
	.string "Radio Tower and officially announce \l"
	.string "our comeback.\p"
	.string "That should bring our boss Giovanni\n"
	.string "back from his solitary training.\p"
	.string "We are going to regain our former\n"
	.string "glory... \p"
	.string "I will not allow you to interfere with\n"
	.string "our meticulous plans!$"

RadioTower_5F_Archer_Text_1:
	.string "No! Forgive me, Giovanni!$"

RadioTower_5F_Archer_Text_2:
	.string "Archer: How could this be...?\p"
	.string "It seems I was not up to the task... \n"
	.string "Yet.\p"
	.string "We shall retreat for now, but know \n"
	.string "that Team Rocket roots run deeper \l"
	.string "in this region than you might think.\p"
	.string "We shall meet again, {PLAYER}.\n"
	.string "Farewell...$"

RadioTower_5F_Archer_Text_3:
	.string "Director: Oh...\p"
	.string "You have already defeated them?\n"
	.string "Thank you!\p"
	.string "Your courageous actions have saved\n"
	.string "Pokémon nationwide.\p"
	.string "You deserve to be rewarded for your\n"
	.string "actions! \p"
	.string "I'll let you pick one of our \n"
	.string "prized treasures! \p"
	.string "Go ahead and pick one!$"

RadioTower_5F_Archer_Text_4:
	.string "Rainbow Wing$"

RadioTower_5F_Archer_Text_5:
	.string "Silver Wing$"

RadioTower_5F_Archer_Text_6:
	.string "There used to be a tower right here.\p"
	.string "When the tower was replaced with the\n"
	.string "Radio Tower, that Rainbow Wing was \l"
	.string "found at the top of the tower.\p"
	.string "I heard from a friend from Cianwood\n"
	.string "City that you can climb the Bell\l"
	.string "Tower in Ecruteak City when you have a\l"
	.string "Rainbow Wing.$"

RadioTower_5F_Archer_Text_7:
	.string "There used to be a tower right here.\p"
	.string "When the tower was replaced with the\n"
	.string "Radio Tower, that Silver Wing was \l"
	.string "found at the top of the tower.\p"
	.string "I heard from a friend from Cianwood\n"
	.string "City that you can go down the cave\l"
	.string "at Whirl Islands when you have a Silver\l"
	.string "Wing.$"

RadioTower_5F_Archer_Text_8:
	.string "I have to get back to my office.\n"
	.string "See you!$"

RadioTower_5F_Archer_Text_9:
	.string "Oh, I almost forgot!\p"
	.string "According to my friend from Cianwood,\n"
	.string "the legendary Pokémon will not appear\l"
	.string "if you just go to the place I mentioned.\l"
	.string "Apparently there is something else you\l"
	.string "need... Or something like that.\p"
	.string "I wonder what it was...\n"
	.string "I can't remember.$"

RadioTower_5F_Archer_Text_10:
	.string "That is a Mega Ring. \p"
	.string "When combined with a Mega stone, \n"
	.string "it allows the bond between trainer \l"
	.string "and Pokémon to fully manifest. \p"
	.string "I'm sure you'll be able to pull it off.$"

RadioTower_5F_Archer_Text_11:
	.string "Now I must get back to my work, I hope\n"
	.string "you'll tune in to my next radio show!$"

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_0:
	.string "Ah, {PLAYER}!\p"
	.string "I heard you became the champion,\n"
	.string "congratulations!$"

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_1:
	.string "I assume you're here for the other \n"
	.string "wing? Ho ho ho!\p"
	.string "I'd be more than happy to give it\n"
	.string "to you on one condition.\p"
	.string "I have been itching for a good\n"
	.string "battle for a very long time.\p"
	.string "Team Rocket ambushed me when I had\n"
	.string "no Pokémon. \p"
	.string "They would have stood no chance \n"
	.string "against my prized team.$"

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_2:
	.string "I'll show you the power of a former\n"
	.string "Elite Four member, ho ho ho!$"

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_3:
	.string "What a nostalgic feeling!$"

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_4:
	.string "You are truly above and beyond other\n"
	.string "trainers in Johto, {PLAYER}!\p"
	.string "I'm more than happy to hand this over\n"
	.string "to you.$"

GoldenrodCity_RadioTower_5F_EventScript_DirectorPath_Text_5:
	.string "Now go on and continue your legend!$"

DirectorGotSilver_Text_0:
	.string "You chose Silver Wing$"

DirectorGotRainbow_Text_0:
	.string "You chose Rainbow Wing$"
