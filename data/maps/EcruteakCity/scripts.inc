
.set LOCALID_ECRUTEAK_GRAMPS, 4
.set LOCALID_ECRUTEK_SILVER, 33

EcruteakCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, EcruteakCity_OnLoad
	.byte 0

EcruteakCity_OnTransition::
	call Common_EventScript_SetupRivalGfxId

EcruteakCity_OnTransition_SetTime::
	callnative SetTimeBasedEncounters
	end

EcruteakCity_OnLoad::
	setrespawn HEAL_LOCATION_ECRUTEAK_CITY
	end

EcruteakCity_Test_Lugia::
	setvar VAR_LUGIA_OR_HOOH, 1
	end
EcruteakCity_Test_League::
	setvar VAR_COMPLETED_HO_OH, 4
	setvar VAR_COMPLETED_LUGIA, 4
	end


EcruteakCity_EventScript_Trigger::
	@flagheap
	clearflag FLAG_RELEASED_BEASTS
	clearflag FLAG_AMPHAROS_HEALED
	clearflag FLAG_HIDE_ECRUTEAK_BILL
	clearflag FLAG_DEFEATED_HO_OH
	clearflag FLAG_CAUGHT_HO_OH
	clearflag FLAG_DEFEATED_LUGIA
	clearflag FLAG_CAUGHT_LUGIA
	clearflag FLAG_HIDE_ECRUTEAK_ROCKET
	clearflag FLAG_HIDE_BURNED_TOWER_NPCS  
	clearflag FLAG_HIDE_BURNED_TOWER_BEASTS
	clearflag FLAG_HIDE_BURNED_TOWER_B1F_EUSINE
	clearflag FLAG_HIDE_ECRUTEAK_CITY_SAGE
	clearflag FLAG_CAUGHT_ENTEI
	clearflag FLAG_CAUGHT_RAIKOU
	clearflag FLAG_GOT_TM_SNATCH
	clearflag FLAG_HIDE_ROUTE42_SUICUNE
	clearflag FLAG_GOT_TYROGUE
	clearflag FLAG_BEAT_KIYO
	clearflag FLAG_ENABLE_BAOBA_MATCH_CALL
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag FLAG_HIDE_TINTOWER_GUARD
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	clearflag FLAG_HIDE_LUGIA
	clearflag FLAG_HIDE_HO_OH

	setflag FLAG_VISITED_ECRUTEAK_CITY
	setflag FLAG_HIDE_ROUTE42_EUSINE

	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	setflag FLAG_HIDE_ROUTE39_SHADOW
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setvar VAR_COMPLETED_HO_OH, 0
	setvar VAR_COMPLETED_LUGIA, 0
	setvar VAR_ECRUTEAK_CITY_THEATER, 0 
	setvar VAR_ECRUTEAK_CITY_STATE, 1
	end

EcruteakCity_Trigger_Silver::
	lockall
	opendoor 39, 40
	waitdooranim
	delay 10
	clearflag FLAG_HIDE_ECRUTEAK_SILVER
	addobject LOCALID_ECRUTEK_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	playse SE_BANG
	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver1
	applymovement OBJ_EVENT_ID_PLAYER, EcruteakCity_Movement_Silver1
	message EcruteakCity_Text_Silver1
	
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_ECRUTEK_SILVER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	closedoor 39, 40
	waitdooranim
	createfieldmugshot MUGSHOT_SILVER
	msgbox EcruteakCity_Text_Silver2, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ECRUTEK_SILVER, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_ECRUTEK_SILVER, DIR_SOUTH
	createfieldmugshot MUGSHOT_SILVER
	msgbox EcruteakCity_Text_Silver3, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver2
	waitmovement LOCALID_ECRUTEK_SILVER


	setflag FLAG_HIDE_ECRUTEAK_SILVER
	removeobject LOCALID_ECRUTEK_SILVER
	fadedefaultbgm

	setvar VAR_ECRUTEAK_CITY_THEATER, 5
	releaseall
	end

EcruteakCity_Movement_Silver1:
	delay_16
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

EcruteakCity_Movement_Silver2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

EcruteakCity_Text_Silver1:
	.string "Thud!!$"

EcruteakCity_Text_Silver2:
	.string "Silver: How...? How is this\n"
	.string "possible? How can I lose to mere\l"
	.string "Kimono Girls...?$"

EcruteakCity_Text_Silver3:
	.string "Silver: You were watching me,\n"
	.string "{PLAYER}...\p"
	.string "Yeah, that's right!\p"
	.string "I never thought defeating five\n"
	.string "Kimono Girls would be so hard...\p"
	.string "I got beaten to a pulp...\p"
	.string "...\p"
	.string "You must have come here for the\n"
	.string "same reason, right?\p"
	.string "Don't get cocky just because you\n"
	.string "defeated Team Rocket!\p"
	.string "These Kimono Girls are insanely\n"
	.string "strong.\p"
	.string "See if you can defeat them.\p"
	.string "But I'm not going back, I don't\n"
	.string "want to see you win.$"

EcruteakCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps1, MSGBOX_DEFAULT
	closemessage
	release
	end
		
EcruteakCity_EventScript_Lass::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RELEASED_BEASTS, EcruteakCity_EventScript_Girl2
	msgbox EcruteakCity_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl2::
	msgbox EcruteakCity_Text_Lass2_ReleasedBeasts, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man::
	lock
	faceplayer
	goto_if_set FLAG_AMPHAROS_HEALED, EcruteakCity_EventScrip_Man2
	msgbox EcruteakCity_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man2::
	msgbox EcruteakCity_Text_Fisher_JasmineReturned, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageRight::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageTower::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps3, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageGym::
	lock
	faceplayer
	msgbox EcruteakCity_Text_SageGym, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_TheaterSign::
	lock
	msgbox EcruteakCity_Text_DanceTheaterSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_OfficeSign::
	lock
	msgbox EcruteakCity_Text_OfficeSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_BurnedSign::
	lock
	msgbox EcruteakCity_Text_BurnedTowerSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_CitySign::
	lock
	msgbox EcruteakCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_GymSign::
	lock
	msgbox EcruteakCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_Eevee::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Eevee, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Vulpix::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VULPIX, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Vulpix, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_Text_Eevee:
	.string "Eevee: Veee!$"

EcruteakCity_Text_Vulpix:
	.string "Vulpix: Vullll Pix!$"


EcruteakCity_Text_UnusedMissingDaughter:
	.string "Oh, no. Oh, no…\p"
	.string "My daughter is missing.\p"
	.string "No… She couldn't have gone to the\n"
	.string "Burned Tower.\p"
	.string "I told her not to go near it…\p"
	.string "People seem to disappear there…\p"
	.string "Oh, what should I do…?$"

EcruteakCity_Text_Gramps1:
	.string "Ecruteak used to have two towers:\n"
	.string "one each in the east and west.$"

EcruteakCity_Text_Gramps2:
	.string "Ah, child. Have you learned to\n"
	.string "dance like the Kimono Girls?\p"
	.string "If you go to their Dance Theater,\n"
	.string "an odd old man will give you\l"
	.string "something nice, I hear.$"

EcruteakCity_Text_Lass1:
	.string "I'm going to practice at the Dance\n"
	.string "Theater. Care to join me?$"

EcruteakCity_Text_Lass2:
	.string "The tower that used to be here…\p"
	.string "My grandma told me it used to be\n"
	.string "much taller.\p"
	.string "I hear there are ghosts in it now.$"

EcruteakCity_Text_Lass2_ReleasedBeasts:
	.string "Three big Pokémon ran off in different\n"
	.string "directions. What were they?$"

EcruteakCity_Text_Fisher:
	.string "I heard a rumor about Olivine\n"
	.string "Lighthouse.\p"
	.string "The Pokémon that serves as the\n"
	.string "beacon fell ill. Sounds like they\l"
	.string "are in trouble.$"

EcruteakCity_Text_Fisher_JasmineReturned:
	.string "The Pokémon at Olivine Lighthouse\n"
	.string "has been cured.\p"
	.string "Boats can safely sail out to sea at\n"
	.string "night again.$"

EcruteakCity_Text_Youngster:
	.string "I hear Pokémon are rampaging at the\n"
	.string "Lake Of Rage. I'd like to see that.$"

EcruteakCity_Text_Gramps3:
	.string "In the distant past…\p"
	.string "This tower burned in a fire. Three\n"
	.string "nameless Pokémon perished in it.\p"
	.string "A rainbow-colored Pokémon descended\n"
	.string "from the sky and resurrected them…\p"
	.string "It's a legend that has been passed\n"
	.string "down by Ecruteak Gym Leaders.\p"
	.string "Me?\p"
	.string "I was a trainer way back when.\n"
	.string "Hohoho!$"

EcruteakCity_Text_SageGym:
	.string "Gym Leader Morty is not here right\n"
	.string "now. You may find him at the\l"
	.string "Burned Tower.$"

EcruteakCity_Text_Sign:
	.string "Ecruteak City\n"
	.string "A Historical City\p"
	.string "Where the Past Meets the Present$"

EcruteakCity_Text_TinTowerSign:
	.string "Tin Tower\p"
	.string "A legendary Pokémon is said to\n"
	.string "roost here.$"

EcruteakCity_Text_OfficeSign:
	.string "Barrier Station to Tin Tower\p"
	.string "No Trespassing by the Unworthy.$"

EcruteakCity_Text_GymSign:
	.string "Ecruteak City Pokémon Gym\n"
	.string "Leader: Morty\p"
	.string "The Mystic Seer of the Future$"

EcruteakCity_Text_DanceTheaterSign:
	.string "Ecruteak Dance Theater$"

EcruteakCity_Text_BurnedTowerSign:
	.string "Burned Tower\p"
	.string "It was destroyed by a mysterious\n"
	.string "fire.\p"
	.string "Please stay away, as it is unsafe.$"

EcruteakCity_RivalPostBattle::
	lock
	faceplayer
	createfieldmugshotrival
	msgbox EcruteakCity_RivalPostBattle_Text_0
	removefieldmugshot
	closemessage
	moveobjecttocoords LOCALID_ECRUTEAK_RIVAL, 8, 35, DIR_WEST
	waitmovement 0
	delay 60
	applymovement LOCALID_ECRUTEAK_RIVAL, EcruteakCity_RivalPostBattle_Movement_0
	delay 30
	createfieldmugshotrival
	msgbox EcruteakCity_RivalPostBattle_Text_1
	removefieldmugshot
	closemessage
	applymovement LOCALID_ECRUTEAK_RIVAL, EcruteakCity_RivalPostBattle_Movement_1
	waitmovement 0
	playse SE_EXIT
	delay 30
	setvar VAR_RIVAL_STATE, 8
	setflag FLAG_HIDE_ECRUTEAK_RIVAL
	clearflag FLAG_HIDE_OLIVINE_RIVAL
	removeobject LOCALID_ECRUTEAK_RIVAL
	release
	end


EcruteakCity_RivalPostBattle_Movement_0:
	face_right
	step_end

EcruteakCity_RivalPostBattle_Movement_1:
	face_left
	step_end

EcruteakCity_RivalPostBattle_Text_0:
	.string "What's up {PLAYER}?\p"
	.string "Mowing down more gyms left and right?\p"
	.string "Same as always. You're on a roll,\n"
	.string "woohoo.\p"
	.string "I can't even beat Morty yet...\p"
	.string "I'm going to train in Olivine for a while.\n"
	.string "Don't wait up.$"

EcruteakCity_RivalPostBattle_Text_1:
	.string "...You're doing really well.\n"
	.string "I mean that.$"
