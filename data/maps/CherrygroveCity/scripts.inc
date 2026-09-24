

CherrygroveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CherrygroveCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, CherrygroveCity_OnLoad
	.byte 0

CherrygroveCity_OnTransition::
	callnative SetTimeBasedEncounters
	end

CherrygroveCity_OnLoad::
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY
	end

CherryGroveCity_EventScript_TriggerGent_Top::
	lock
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Top
	waitmovement 0 
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0 
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Mid::
	lock
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0 
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Bottom::
	lock
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0 
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Bottom
	waitmovement 0 
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Cancel::
	msgbox CherrygroveCity_Text_GuideGentDecline, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CHERRYGROVE_CITY_STATE, 1 @ CHANGE THIS TO 1 LATER
	release
	end

CherryGroveCity_EventScript_GentTour::
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokecenter
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokecenter
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentPokecenter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokemart
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokemart
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentMart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Route30
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Route30
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentRoute30, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Sea
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Sea
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_House_Gent
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_House_Player
	waitmovement 0
	waitmovement 0
	delay 20
	msgbox CherrygroveCity_Text_GuideGentMap, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Gent_Leave
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 20
	opendoor 42, 14
	waitdooranim
	waitmovement 0
	removeobject LOCALID_GUIDE_GENT
	closedoor 42, 14
	waitdooranim
	
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	setvar VAR_CHERRYGROVE_CITY_STATE, 1
	fadedefaultbgm
	release
	end

CherryGroveCity_EventScript_Fisherman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_MYSTICWATER, CherryGroveCity_EventScript_Fisherman2
	msgbox CherrygroveCity_Text_MysticWaterGuyBefore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_Fisherman2
	giveitem ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull 
	closemessage
	setflag FLAG_GOT_MYSTICWATER
	release
	end

CherryGroveCity_EventScript_Fisherman2::
	msgbox CherrygroveCity_Text_MysticWaterGuyAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Lass::
	lock
	faceplayer
	msgbox CherrygroveCity_Text_TeacherHaveMapCard, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, CherryGroveCity_EventScript_Boy2
	msgbox CherrygroveCity_Text_YoungsterNoPokedex, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Boy2::
	msgbox CherrygroveCity_Text_YoungsterHavePokedex, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Staryu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_STARYU, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Staryu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Corsola::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CORSOLA, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Corsola, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Krabby::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KRABBY, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Krabby, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Sign::
	lock
	msgbox CherrygroveCity_Text_CitySign, MSGBOX_SIGN
	closemessage
	release
	end	

CherryGroveCity_EventScript_TriggerSilver_Top::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Top
	waitmovement 0
	goto CherryGroveCity_EventScript_TriggerSilver
	end

CherryGroveCity_EventScript_TriggerSilver_Bottom::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Bottom
	waitmovement 0
	goto CherryGroveCity_EventScript_TriggerSilver
	end

CherryGroveCity_EventScript_TriggerSilver::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Enter
	waitmovement 0
	createfieldmugshot MUGSHOT_SILVER
	msgbox CherrygroveCity_Text_RivalSeen, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_STARTER_MON, 0, CherryGroveCity_Silver_Battle_Cyndaquil
	goto_if_eq VAR_STARTER_MON, 1, CherryGroveCity_Silver_Battle_Totodile
	goto_if_eq VAR_STARTER_MON, 2, CherryGroveCity_Silver_Battle_Chikorita
	release
	end

CherryGroveCity_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_1, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_1, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_1, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_AfterBattle::
	playbgm MUS_HG_RIVAL_EXIT, TRUE
	createfieldmugshot MUGSHOT_SILVER
	msgbox CherrygroveCity_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Silver_Leave1Player
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave1
	waitmovement 0
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_CHERRYGROVE_SILVER, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_EAST
	delay 60
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_SOUTH
	delay 30
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Return
	waitmovement 0
	createfieldmugshot MUGSHOT_SILVER
	msgbox CherrygroveCity_Text_RivalID, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave2
	waitmovement 0
	removeobject LOCALID_CHERRYGROVE_SILVER
	setflag FLAG_HIDE_SILVER_CHERRYGROVE
	setvar VAR_CHERRYGROVE_CITY_STATE, 4
	fadedefaultbgm
	release
	end

CherrygroveCity_Text_GuideGentIntro:
	.string "You're a rookie trainer,\n"
	.string "aren't you? I can tell!\p"
	.string "That's Ok! Everyone is a\n"
	.string "rookie at some point!\p"
	.string "If you'd like, I can teach\n"
	.string "you a few things.$"

CherrygroveCity_Text_GuideGentTourStart:
	.string "Ok, then!\n"
	.string "Follow me!$"

CherrygroveCity_Text_GuideGentPokecenter:
	.string "This is a Pokémon Center.\p"
	.string "They heal your Pokémon in no\n"
	.string "time at all.\p"
	.string "You'll be relying on them a lot,\n"
	.string "so you better learn about them.$"

CherrygroveCity_Text_GuideGentMart:
	.string "This is a Pokémon Mart.\p"
	.string "They sell Balls for catching wild\n"
	.string "Pokémon and other useful items.$"

CherrygroveCity_Text_GuideGentRoute30:
	.string "Route 30 is out this way.\p"
	.string "Trainers will be battling\n"
	.string "their prized Pokémon there.$"

CherrygroveCity_Text_GuideGentSea:
	.string "This is the sea, as you can see.\p"
	.string "Some Pokémon are found only in\n"
	.string "in water.$"

CherrygroveCity_Text_GuideGentMap:
	.string "Here…\p"
	.string "It's my house! Thanks for\n"
	.string "your company.\p"
	.string "Oh, and if you're ever lost, check\n"
	.string "the Map on your Pokégear!\p"
	.string "I wish you luck on your journey!$"

CherrygroveCity_Text_GuideGentDecline:
	.string "Oh… It's something I enjoy\n"
	.string "doing…\p"
	.string "Fine. Come see me whenever\n"
	.string "you like.$"

CherrygroveCity_Text_RivalSeen:
	.string "… … … … … … … …\p"
	.string "You got a Pokémon at the Lab.\p"
	.string "What a waste.\n"
	.string "A wimp like you.\p"
	.string "… … … … … … … …\p"
	.string "Don't you get what I'm saying?\n"
	.string "Well, I too, have a good Pokémon.\p"
	.string "I'll show you what I mean!$"

CherrygroveCity_Text_SilverWin:
	.string "Humph. Are you happy you won?$"

CherrygroveCity_Text_RivalAfter:
	.string "… … … … … … … …\p"
	.string "Do you want to know who I am?\p"
	.string "I'm going to be the world's\n"
	.string "greatest Pokémon trainer.$"

CherrygroveCity_Text_RivalID:
	.string "Give it back!\n"
	.string "That's my Trainer Card!\p"
	.string "Oh no!\n"
	.string "You saw my name...$"

CherrygroveCity_Text_TeacherHaveMapCard:
	.string "When you're with Pokémon,\n"
	.string "going anywhere is fun.$"

CherrygroveCity_Text_YoungsterNoPokedex:
	.string "Mr. Pokémon's house is still\n"
	.string "farther up ahead.$"

CherrygroveCity_Text_YoungsterHavePokedex:
	.string "I battled the trainers on the\n"
	.string "road.\p"
	.string "My Pokémon lost. They're a\n"
	.string "mess! I must take them to a\l"
	.string "Pokémon Center.$"

CherrygroveCity_Text_MysticWaterGuyBefore:
	.string "A Pokémon I caught had an\n"
	.string "item.\p"
	.string "I think it's Mystic Water.\p"
	.string "I don't need it, so do you\n"
	.string "want it?$"

CherrygroveCity_Text_MysticWaterGuyAfter:
	.string "Back to fishing for me, then.$"

CherrygroveCity_Text_CitySign:
	.string "Cherrygrove City\p"
	.string "The City of Cute, Fragrant\n"
	.string "Flowers$"

CherrygroveCity_Text_GuideGentsHouseSign:
	.string "Guide Gent's House$"

CherryGroveCity_Text_Staryu:
	.string "Staryu: Yuuuuuuuu.$"

CherryGroveCity_Text_Corsola:
	.string "Corsola: Corsola! La!$"

CherryGroveCity_Text_Krabby:
	.string "Krabby: Kooookeee!$"

CherryGroveCity_Movement_Trigger_Gent:
	walk_down
	walk_left
	walk_down
	face_left
	step_end

CherryGroveCity_Movement_Trigger_Top:
	walk_down
	face_up
	step_end

CherryGroveCity_Movement_Trigger_Bottom:
	walk_up
	face_up
	step_end

CherryGroveCity_Movement_Pokecenter:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

CherryGroveCity_Movement_Pokemart:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

CherryGroveCity_Movement_Route30:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

CherryGroveCity_Movement_Sea:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

CherryGroveCity_Movement_House_Gent:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

CherryGroveCity_Movement_House_Player:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

CherryGroveCity_Movement_Gent_Leave:
	walk_up
	step_end

CherryGroveCity_Movement_Trigger_Silver_Top:
	walk_down
	face_right
	step_end

CherryGroveCity_Movement_Trigger_Silver_Bottom:
	walk_up
	face_right
	step_end

CherryGroveCity_Movement_Silver_Enter:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

CherryGroveCity_Movement_Silver_Leave1:
	delay_16
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

CherryGroveCity_Movement_Silver_Leave1Player:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	face_up
	step_end

CherryGroveCity_Movement_Silver_Return:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end


CherryGroveCity_Movement_Silver_Leave2:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Cherrygrove_FadedSign::
	msgbox Cherrygrove_FadedSign_Text_0, MSGBOX_SIGN
	return


Cherrygrove_DarkraiEventDoor::
	lock
	getcaughtmon SPECIES_DARKRAI
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 4
	goto_if_eq Cherrygrove_DarkraiEventDoor_2
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_ge Cherrygrove_DarkraiEventDoor_7
Cherrygrove_DarkraiEventDoor_3:
	msgbox Cherrygrove_DarkraiEventDoor_Text_7
	release
	end

Cherrygrove_DarkraiEventDoor_2:
	msgbox Cherrygrove_DarkraiEventDoor_Text_0
	checkspecies SPECIES_CRESSELIA
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_DarkraiEventDoor_12
	msgbox Cherrygrove_DarkraiEventDoor_Text_2
	dynmultichoice 20, 8, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_DarkraiEventDoor_Text_3, Cherrygrove_DarkraiEventDoor_Text_4
	compare VAR_RESULT, 1
	goto_if_eq Cherrygrove_DarkraiEventDoor_14
	msgbox Cherrygrove_DarkraiEventDoor_Text_6
	release
	end

Cherrygrove_DarkraiEventDoor_6:
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_DarkraiEventDoor_2
	goto Cherrygrove_DarkraiEventDoor_3

Cherrygrove_DarkraiEventDoor_7:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 10
	goto_if_le Cherrygrove_DarkraiEventDoor_6
	goto Cherrygrove_DarkraiEventDoor_3

Cherrygrove_DarkraiEventDoor_12:
	msgbox Cherrygrove_DarkraiEventDoor_Text_1
	release
	end

Cherrygrove_DarkraiEventDoor_14:
	msgbox Cherrygrove_DarkraiEventDoor_Text_5
	closemessage
	compare VAR_DARKRAI_INN_PROGRESS, 2
	goto_if_ge Cherrygrove_DarkraiEventDoor_18
	warpwhitefade MAP_DARKRAI_INN1, 1
Cherrygrove_DarkraiEventDoor_17:
	waitstate
	end

Cherrygrove_DarkraiEventDoor_18:
	warpwhitefade MAP_DARKRAI_INN1RUINED, 28, 18
	goto Cherrygrove_DarkraiEventDoor_17


Cherrygrove_Littlegirl::
	lock
	faceplayer
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_eq Cherrygrove_Littlegirl_2
	msgbox Cherrygrove_Littlegirl_Text_1
	release
	end

Cherrygrove_Littlegirl_2:
	msgbox Cherrygrove_Littlegirl_Text_0
	release
	end


Cherrygrove_Zigzagoon::
	lock
	faceplayer
	playmoncry SPECIES_ZIGZAGOON_GALAR, CRY_MODE_NORMAL
	msgbox Cherrygrove_Zigzagoon_Text_0
	release
	end


Cherrygrove_Rattata::
	lock
	faceplayer
	playmoncry SPECIES_RATTATA_ALOLA, CRY_MODE_NORMAL
	msgbox Cherrygrove_Rattata_Text_0
	release
	end


Cherrygrove_FriendlyTrader::
	lock
	faceplayer
	goto_if_set FLAG_PICKED_ZIGZAGOON, Cherrygrove_FriendlyTrader_2
	goto_if_set FLAG_PICKED_RATTATA, Cherrygrove_FriendlyTrader_2
	goto_if_set FLAG_RECEIVED_FIRST_BALLS, Cherrygrove_FriendlyTrader_7
	msgbox Cherrygrove_FriendlyTrader_Text_7
	release
	end

Cherrygrove_FriendlyTrader_2:
	msgbox Cherrygrove_FriendlyTrader_Text_0
	release
	end

	release
	end

Cherrygrove_FriendlyTrader_7:
	msgbox Cherrygrove_FriendlyTrader_Text_1
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_FriendlyTrader_Text_2, Cherrygrove_FriendlyTrader_Text_3, Cherrygrove_FriendlyTrader_Text_4
	switch VAR_RESULT
	case 0, Cherrygrove_FriendlyTrader_11
	case 1, Cherrygrove_FriendlyTrader_12
	msgbox Cherrygrove_FriendlyTrader_Text_6
	release
	end

Cherrygrove_FriendlyTrader_11:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZIGZAGOON_GALAR
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
	givemon SPECIES_ZIGZAGOON_GALAR, 5
	showgivemonpic 10, 3
	removeobject LOCALID_CHERRY_ZIGZAGOON
	call Common_EventScript_GiftMon
	hidemonpic
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
	msgbox Cherrygrove_FriendlyTrader_Text_5
	release
	end

Cherrygrove_FriendlyTrader_12:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_RATTATA_ALOLA
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
	givemon SPECIES_RATTATA_ALOLA, 5
	showgivemonpic 10, 3
	removeobject LOCALID_CHERRY_RATTATA
	call Common_EventScript_GiftMon
	hidemonpic
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
	msgbox Cherrygrove_FriendlyTrader_Text_5
	release
	end


Cherrygrove_FadedSign_Text_0:
	.string "Cherrygrove inn...\n"
	.string "The text is too faded to read.$"

Cherrygrove_DarkraiEventDoor_Text_0:
	.string "Darkrai might be residing in this \n"
	.string "old inn.\p"
	.string "It would be best to prepare for\n"
	.string "anything.$"

Cherrygrove_DarkraiEventDoor_Text_1:
	.string "You should also bring Cresselia with \n"
	.string "you.$"

Cherrygrove_DarkraiEventDoor_Text_2:
	.string "Are you absolutely sure you are ready?$"

Cherrygrove_DarkraiEventDoor_Text_3:
	.string "Prepare first$"

Cherrygrove_DarkraiEventDoor_Text_4:
	.string "Go in$"

Cherrygrove_DarkraiEventDoor_Text_5:
	.string "You grab the door handle and-$"

Cherrygrove_DarkraiEventDoor_Text_6:
	.string "Best to prepare first.$"

Cherrygrove_DarkraiEventDoor_Text_7:
	.string "The door won't budge. It seems\n"
	.string "to be stuck.$"

Cherrygrove_Littlegirl_Text_0:
	.string "I saw you dozing off in front of the\n"
	.string "old inn's door. Are you okay?$"

Cherrygrove_Littlegirl_Text_1:
	.string "That inn... I don't think it\n"
	.string "has ever been open. My mom said it was\l"
	.string "abandoned even in her youth.$"

Cherrygrove_Zigzagoon_Text_0:
	.string "Zig!$"

Cherrygrove_Rattata_Text_0:
	.string "Rat!$"

Cherrygrove_FriendlyTrader_Text_0:
	.string "Hi! Has my Pokémon been helpful?$"

Cherrygrove_FriendlyTrader_Text_1:
	.string "Hello! Are you a new trainer per chance?\p"
	.string "Listen, I received two exotic Pokémon\n"
	.string "as a gift from my uncle in the Safari\l"
	.string "Zone, but I can't keep both. \p"
	.string "Would you be willing to take one of \n"
	.string "them with you?\p"
	.string "I'm sure either one would love to go on\n"
	.string "an adventure with you!$"

Cherrygrove_FriendlyTrader_Text_2:
	.string "Zigzagoon$"

Cherrygrove_FriendlyTrader_Text_3:
	.string "Rattata$"

Cherrygrove_FriendlyTrader_Text_4:
	.string "No thanks$"

Cherrygrove_FriendlyTrader_Text_5:
	.string "Take good care of my {STR_VAR_1}!\p"
	.string "Say hi to my uncle, Baoba if you are\n"
	.string "ever visiting the Safari Zone!$"

Cherrygrove_FriendlyTrader_Text_6:
	.string "Oh... That's a shame...$"

Cherrygrove_FriendlyTrader_Text_7:
	.string "Hey! Can I ask you a favour? \p"
	.string "Wait... You don't have any\n"
	.string "Poké Balls...\p"
	.string "Sorry,\n"
	.string "I thought you were a trainer.$"
