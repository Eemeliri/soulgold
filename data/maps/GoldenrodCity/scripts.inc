

GoldenrodCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Goldenrod_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_OnLoad
	.byte 0

GoldenrodCity_OnLoad::
	setrespawn HEAL_LOCATION_GOLDENROD_CITY
	end

GoldenrodCity_EventScript_Trigger:: @flagheap
	call_if_unset FLAG_SHOWN_ELM_TOGEPI, GoldenrodCity_Elm_Togepi_Call
	setflag FLAG_VISITED_GOLDENROD_CITY
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	setflag FLAG_HIDE_GOLDENROD_BILL
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	setflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	setflag FLAG_HIDE_RADIOTOWER_OAK
	
	clearflag FLAG_HIDE_GOLDENROD_BEAUTY
	clearflag FLAG_HIDE_GOLDENROD_ROCKET_SCOUT
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	clearflag FLAG_HIDE_RADIOF5DUDE
	clearflag FLAG_GOT_RETURN
	clearflag FLAG_GOT_FRUSTRATION
	clearflag FLAG_RECEIVED_BIKE
	clearflag FLAG_RECEIVED_SQUIRTBOTTLE
	clearflag FLAG_GOT_BILL_GIFTMON
	clearflag FLAG_SYS_PC_BILL
	clearflag FLAG_RETURNED_MACHINE_PART
	clearflag FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
	clearflag FLAG_GOLDENROD_MACHOKE_1
	clearflag FLAG_GOLDENROD_MACHOKE_2
	clearflag FLAG_GOLDENROD_MACHOKE_3
	clearflag FLAG_COMPLETED_SWITCHES
	clearflag FLAG_ENABLE_RADIO
	clearflag FLAG_KANTO_RADIO_GOT
	clearflag FLAG_GOLDENROD_NPC_TRADE_COMPLETED
	clearflag FLAG_GOT_SKILL_SWAP
	clearflag FLAG_HIDE_RADIOTOWER_GATE
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	clearflag FLAG_GOT_MARY_BRIGHT_POWDER
	clearflag FLAG_GOT_QUICK_CLAW
	clearflag FLAG_GOT_MAGNET

	setvar VAR_BUG_CONTEST_STATE, 0
	setvar VAR_KENYA, 0
	setvar VAR_LUGIA_OR_HOOH, 0
	setvar VAR_TRAIN, 0
	setvar VAR_ELEVATOR, 0
	setvar VAR_GOLDENROD_CITY_STATE, 1
	release
	end

GoldenrodCity_Elm_Togepi_Call::
	lock
	pokenavcall GoldenrodCity_Text_ElmCall
	waitmessage
	delay 30
	release
	return

GoldenrodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Youngster::
	msgbox GoldenrodCity_Text_Youngster1, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Youngster2::
	msgbox GoldenrodCity_Text_Youngster2, MSGBOX_NPC
	end

GoldenrodCity_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_GOLDENROD_ROCKET_SCOUT, GoldenrodCity_EventScript_CooltrainerFCleared
	msgbox GoldenrodCity_Text_CooltrainerF1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_CooltrainerFCleared::
	msgbox GoldenrodCity_Text_CooltrainerF1_Cleared, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_NameRaterSign::
	msgbox GoldenrodCity_Text_NameRaterSign, MSGBOX_SIGN
	end

GoldenrodCity_EventScript_RocketScout::
	lock
	msgbox GoldenrodCity_Text_RocketScout1, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROCKET_SCOUT, Common_Movement_ExclamationMark
	delay 20
	faceplayer
	msgbox GoldenrodCity_Text_RocketScout2, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROCKET_SCOUT, DIR_NORTH
	release
	end

GoldenrodCity_EventScript_Rocket1::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket2::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket3::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket4::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket5::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket5, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket6::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket6, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Woman::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_DAY_POKEMON, GoldenrodCity_EventScript_Hiker2
	msgbox GoldenrodCity_Text_HikerDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker2::
	msgbox GoldenrodCity_Text_HikerNight, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Snubbull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AUDINO, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_Snubbull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_Mime::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MR_MIME, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_MrMime, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_SignUnderground::
	lock
	msgbox GoldenrodCity_Text_UndergroundSouthSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignDept::
	lock
	msgbox GoldenrodCity_Text_DeptStoreSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignBike::
	lock
	msgbox GoldenrodCity_Text_BikeShopSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignTrain::
	lock
	msgbox GoldenrodCity_Text_StationSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignGym::
	lock
	msgbox GoldenrodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignFlower::
	lock
	msgbox GoldenrodCity_Text_FlowerShopSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignRadio::
	lock
	msgbox GoldenrodCity_Text_RadioTowerSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignGameCorner::
	lock
	msgbox GoldenrodCity_Text_GameCornerSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_Beauty::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Beauty:
	.string "This is the Goldenrod Gym!\p"
	.string "Our leader Whitney is not here\n"
	.string "right now. She might be at the\l"
	.string "Radio Tower.$"

GoldenrodCity_Text_Woman:
	.string "I used to train in Whitney's Gym,\n"
	.string "but all her crying gave me a\l"
	.string "headache.$"

GoldenrodCity_Text_HikerDay:
	.string "When I went into the Game Corner\n"
	.string "it was night time... How long was I\l"
	.string "in there?!$"

GoldenrodCity_Text_HikerNight:
	.string "When I went into the Game Corner\n"
	.string "it was day time... How long was I\l"
	.string "in there?!$"

GoldenrodCity_Text_Snubbull:
	.string "Audino: Audiiinii!$"

GoldenrodCity_Text_MrMime:
	.string "............................$"

GoldenrodCity_Text_ElmCall:
	.string "Elm: Hello, {PLAYER}?\n"
	.string "Has that egg hatched yet?\p"
	.string "Once it hatches, don't forget to\n"
	.string "bring it by the lab! I need to\l"
	.string "see it!$"

GoldenrodCity_Text_PokefanM:
	.string "They built the new Radio Tower\n"
	.string "to replace the old creaky one.$"

GoldenrodCity_Text_Youngster1:
	.string "I know there's a new Bike Shop,\n"
	.string "but I can't find it anywhere.$"

GoldenrodCity_Text_CooltrainerF1:
	.string "Is that man in black dressed up\n"
	.string "like a Team Rocket member?\p"
	.string "How silly!$"

GoldenrodCity_Text_CooltrainerF1_Cleared:
	.string "Was that man in black really part\n"
	.string "of Team Rocket? I can't believe it!$"

GoldenrodCity_Text_CooltrainerF2:
	.string "The Radio Tower in Goldenrod City\n"
	.string "is quite the landmark.\p"
	.string "They're running a campaign now.\p"
	.string "They'll give you a shiny new\n"
	.string "Radio if you can pass their quiz.$"

GoldenrodCity_Text_CooltrainerF2_GotCard:
	.string "Oh, your Pokégear already works\n"
	.string "as a radio!$"

GoldenrodCity_Text_Youngster2:
	.string "E-he-he-he…\p"
	.string "I got in trouble for playing in\n"
	.string "the Dept.Store basement.$"

GoldenrodCity_Text_Lass:
	.string "That man inside rates your\n"
	.string "Pokémon nicknames.\p"
	.string "He can even rename them.$"

GoldenrodCity_Text_Gramps:
	.string "Whew! This city is so big,\n"
	.string "I can't find anything at all.$"

GoldenrodCity_Text_RocketScout1:
	.string "So this is the Radio Tower…$"

GoldenrodCity_Text_RocketScout2:
	.string "What do you want, pest?\n"
	.string "Scram already!$"

GoldenrodCity_Text_Rocket1:
	.string "Stay out of the way!\n"
	.string "Beat it, kid!$"

GoldenrodCity_Text_Rocket2:
	.string "Take over the Radio Tower…\p"
	.string "What? It's none of your business!$"

GoldenrodCity_Text_Rocket3:
	.string "Pokémon? They're just tools\n"
	.string "we use to make money!$"

GoldenrodCity_Text_Rocket4:
	.string "Our dream will soon come true…\p"
	.string "It was a long, hard struggle…$"

GoldenrodCity_Text_Rocket5:
	.string "Hey, brat! You don't belong here!\n"
	.string "Get lost already!$"

GoldenrodCity_Text_Rocket6:
	.string "Come and taste the terror of\n"
	.string "Team Rocket!$"

GoldenrodCity_Text_StationSign:
	.string "Goldenrod City Station$"

GoldenrodCity_Text_RadioTowerSign:
	.string "Goldenrod City Radio Tower$"

GoldenrodCity_Text_DeptStoreSign:
	.string "Full Selection of Pokémon Goods!\p"
	.string "Goldenrod City Dept.Store$"

GoldenrodCity_Text_GymSign:
	.string "Goldenrod City Pokémon Gym\n"
	.string "Leader: Whitney\p"
	.string "The Incredibly Pretty Girl!$"

GoldenrodCity_Text_CitySign:
	.string "Goldenrod City\p"
	.string "The Festive City of Opulent Charm$"

GoldenrodCity_Text_BikeShopSign:
	.string "The World is a Cycle Path!\n"
	.string "Bike Shop$"

GoldenrodCity_Text_GameCornerSign:
	.string "Your Playground!\p"
	.string "Goldenrod City Game Corner$"

GoldenrodCity_Text_NameRaterSign:
	.string "Name Rater\p"
	.string "Get Your Pokémon Nicknames Rated$"

GoldenrodCity_Text_UndergroundNorthSign:
	.string "Underground Entrance$"

GoldenrodCity_Text_UndergroundSouthSign:
	.string "Underground Entrance$"


GoldenrodCity_Text_FlowerShopSign:
	.string "Blooming Beautiful Flower Shop$"

GoldenrodCity_Text_MoveTutorAsk:
	.string "I can teach your Pokémon some\n"
	.string "amazing moves!\p"
	.string "Should I teach one?$"

GoldenrodCity_Text_MoveTutorCost:
	.string "It'll cost you 1000 coins.\n"
	.string "Okay?$"

GoldenrodCity_Text_MoveTutorDecline:
	.string "Aww… But these moves are great!$"

GoldenrodCity_Text_MoveTutorWhich:
	.string "Wahahah! You won't regret it!\p"
	.string "Which move should I teach?$"

GoldenrodCity_Text_MoveTutorNoCash:
	.string "Too bad. Guess I'll need to\n"
	.string "get some cash from home…$"

GoldenrodCity_Text_MoveTutorUnderstand:
	.string "If you understand this move,\n"
	.string "you've made it as a trainer.$"

GoldenrodCity_Text_MoveTutorFarewell:
	.string "Wahahah! Farewell, kid!$"

GoldenrodCity_Text_MoveTutorBut:
	.string "B-but…$"

GoldenrodCity_Text_MoveTutorNotEnoughCoins:
	.string "…You don't have enough coins…$"

Goldenrod_OnFrame:: 
	map_script_2 VAR_RIVAL_STATE, 6, GoldenrodCity_RivalAfterWhitney
	.2byte 0

Goldenrod_Daytime_ExpertM::
	lock
	msgbox Goldenrod_Daytime_ExpertM_Text_0
	closemessage
	playmoncry SPECIES_STARAVIA, CRY_MODE_NORMAL
	applymovement LOCALID_GOLDENROD_STARAVIA, Goldenrod_Daytime_ExpertM_Movement_0
	waitmovement 0
	release
	end


Goldenrod_Daytime_ExpertF::
	lock
	msgbox Goldenrod_Daytime_ExpertF_Text_0
	closemessage
	playmoncry SPECIES_ELECTABUZZ, CRY_MODE_NORMAL
	applymovement LOCALID_GOLDENROD_ELECTABUZZ, Goldenrod_Daytime_ExpertF_Movement_0
	waitmovement 0
	release
	end


Goldenrod_Daytime_Staravia::
	lock
	playmoncry SPECIES_STARAVIA, CRY_MODE_NORMAL
	msgbox Goldenrod_Daytime_Staravia_Text_0
	waitmoncry
	release
	end


Goldenrod_Daytime_Electabuzz::
	lock
	playmoncry SPECIES_ELECTABUZZ, CRY_MODE_NORMAL
	msgbox Goldenrod_Daytime_Electabuzz_Text_0
	waitmoncry
	release
	end


Goldenrod_Daytime_Bystander::
	lock
	faceplayer
	msgbox Goldenrod_Daytime_Bystander_Text_0
	release
	end


Goldenrod_Nighttime_Burglar::
	lock
	faceplayer
	msgbox Goldenrod_Nighttime_Burglar_Text_0
	release
	end


Goldenrod_Nighttime_Oldlady::
	lock
	faceplayer
	goto_if_set FLAG_GOLDENROD_SMACKDOWN, Goldenrod_Nighttime_Oldlady_2
	msgbox Goldenrod_Nighttime_Oldlady_Text_1
	giveitem ITEM_TM_SMACK_DOWN
	setflag FLAG_GOLDENROD_SMACKDOWN
	msgbox Goldenrod_Nighttime_Oldlady_Text_0
	release
	end

Goldenrod_Nighttime_Oldlady_2:
	msgbox Goldenrod_Nighttime_Oldlady_Text_0
	release
	end


GoldenrodCity_OnTransition::
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_HIDE_GOLDENROD_RIVAL
	compare VAR_RIVAL_STATE, 6
	goto_if_eq GoldenrodCity_OnTransition_3
GoldenrodCity_OnTransition_1:
	end

GoldenrodCity_OnTransition_2:
	clearflag FLAG_HIDE_GOLDENROD_RIVAL
	goto GoldenrodCity_OnTransition_1

GoldenrodCity_OnTransition_3:
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_OnTransition_2
	goto GoldenrodCity_OnTransition_1


GoldenrodCity_RivalAfterWhitney::
	compare VAR_RIVAL_STATE, 6
	goto_if_eq GoldenrodCity_RivalAfterWhitney_3
GoldenrodCity_RivalAfterWhitney_1:
	end

GoldenrodCity_RivalAfterWhitney_2:
	lock
	playse SE_PIN
	applymovement LOCALID_GOLDENROD_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	playbgm MUS_HG_LYRA, TRUE
	createfieldmugshotrival
	msgbox GoldenrodCity_RivalAfterWhitney_Text_0
	msgbox GoldenrodCity_RivalAfterWhitney_Text_1
	msgbox GoldenrodCity_RivalAfterWhitney_Text_2
	removefieldmugshot
	closemessage
	applymovement LOCALID_GOLDENROD_RIVAL, GoldenrodCity_RivalAfterWhitney_Movement_0
	waitmovement 0
	setvar VAR_RIVAL_STATE, 7
	setflag FLAG_HIDE_GOLDENROD_RIVAL
	removeobject LOCALID_GOLDENROD_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	goto GoldenrodCity_RivalAfterWhitney_1

GoldenrodCity_RivalAfterWhitney_3:
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_RivalAfterWhitney_2
	goto GoldenrodCity_RivalAfterWhitney_1


Goldenrod_Daytime_ExpertM_Movement_0:
	jump_in_place_right
	jump_in_place_right
	step_end

Goldenrod_Daytime_ExpertF_Movement_0:
	jump_in_place_left
	jump_in_place_left
	step_end

GoldenrodCity_RivalAfterWhitney_Movement_0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Goldenrod_Daytime_ExpertM_Text_0:
	.string "This time I will defeat you, Tiffany!\n"
	.string "We've been training for the whole week!$"

Goldenrod_Daytime_ExpertF_Text_0:
	.string "Hah! If you still have not learned the\n"
	.string "type-matchups, you will never beat me!$"

Goldenrod_Daytime_Staravia_Text_0:
	.string "Staa!$"

Goldenrod_Daytime_Electabuzz_Text_0:
	.string "Bzz!$"

Goldenrod_Daytime_Bystander_Text_0:
	.string "Those two have been going on with their\n"
	.string "rivalry for weeks. The city should build\l"
	.string "a battle arena just for them.$"

Goldenrod_Nighttime_Burglar_Text_0:
	.string "The city's rapid development has\n"
	.string "raised some questions regarding\l"
	.string "where all the money is coming from.\p"
	.string "If they knew just how much money\n"
	.string "changes hands in the underground every\l"
	.string "day, their eyeballs would pop out.\p"
	.string "Perhaps one day you too will learn, if\n"
	.string "you grow strong enough.$"

Goldenrod_Nighttime_Oldlady_Text_0:
	.string "Smack Down lets you ground any target.\n"
	.string "It's also very useful against Flying\l"
	.string "Pokémon.$"

Goldenrod_Nighttime_Oldlady_Text_1:
	.string "Some petty thief tried to jump me on a\n"
	.string "dark alleyway, he was not expecting me\l"
	.string "to Smack Down him with a good old\l"
	.string "Ippon seoinage.\p"
	.string "Here, you should try\n"
	.string "it too.$"

GoldenrodCity_RivalAfterWhitney_Text_0:
	.string "Hey {PLAYER}! \n"
	.string "How did the battle with Whitney go? \p"
	.string "Her Miltank made short work of \n"
	.string "my team a while ago!$"

GoldenrodCity_RivalAfterWhitney_Text_1:
	.string "Oh, you have got the badge... \p"
	.string "Congratulations. \p"
	.string "Another easy victory eh?\n"
	.string "Just like always.$"

GoldenrodCity_RivalAfterWhitney_Text_2:
	.string "Hey, want to head to\n"
	.string "Ecruteak together?\p"
	.string "Actually never mind, you'll probably\n"
	.string "want to catch more Pokémon, I'll\l"
	.string "go visit my grandparents instead.\p"
	.string "Well, see ya!$"
