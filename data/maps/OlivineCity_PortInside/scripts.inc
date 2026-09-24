


OlivineCity_PortInside_Movement_OakFixDex:
	walk_in_place_up
	walk_in_place_up
	step_end

OlivineCity_PortInside_Movement_PlayerMoveOver:
	walk_up
	walk_left
	face_right
	step_end

OlivineCity_PortInside_Movement_OakLeave:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OlivineCity_PortInside_Text_Nationaldex1:
	.string "Prof.Oak: Hello!\n"
	.string "You are starting to have the\l"
	.string "attitude of a Champion, {PLAYER}!\p"
	.string "It's time for your Pokédex to\n"
	.string "match who you are.\p"
	.string "Let me see your Pokédex for a\n"
	.string "second.\p"
	.string "I'll upgrade your Pokédex with the\n"
	.string "National Mode.$"
OlivineCity_PortInside_Text_Nationaldex2:
	.string "{PLAYER}'s Pokédex was upgraded\n"
	.string "with the National Mode!$"
OlivineCity_PortInside_Text_Nationaldex3:
	.string "Prof.Oak: It won't be easy to\n"
	.string "complete the National Pokédex...\p"
	.string "However, I'm sure you will make\n"
	.string "honest attempt on our behalf!$"
OlivineCity_PortInside_Text_Nationaldex4:
	.string "Oh, time flies!\p"
	.string "I have a radio show to record at\n"
	.string "Goldenrod Radio Tower.\p"
	.string "You must be heading for Sevii.\p"
	.string "I hear strong trainers are\n"
	.string "gathering there. How exciting!$"

OlivinePort_EventScript_CooltrainerF::
	msgbox OlivinePort_Text_CooltrainerF, MSGBOX_NPC
	end

OlivinePort_EventScript_Fisher1::
	msgbox OlivinePort_Text_FishingGuru1, MSGBOX_NPC
	end

OlivinePort_EventScript_Fisher2::
	msgbox OlivinePort_Text_FishingGuru2, MSGBOX_NPC
	end

OlivinePort_EventScript_Youngster::
	msgbox OlivinePort_Text_Youngster, MSGBOX_NPC
	end


OlivinePort_Movement_SailorEnterBoat:
	walk_down
	walk_down
	step_end

OlivinePort_Movement_PlayerEnterBoat:
	walk_down
	walk_down
	walk_in_place_down
	step_end

OlivinePort_Movement_BoatLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

OlivinePort_Text_NoPass:
    .string "{PLAYER} tried to show the\n"
    .string "{STR_VAR_1}…\p"
    .string "…But no {STR_VAR_1}!\p"
    .string "Sorry!\n"
    .string "You may board only if you have an\l"
    .string "{STR_VAR_1}.$"

OlivinePort_Text_SailorGetOnBoard:
    .string "We're departing soon.\n"
    .string "Please get on board.$"

OlivinePort_Text_CantBoard:
    .string "Sorry. You can't board now.$"

OlivinePort_Text_WhereSail:
    .string "Where would you like to sail?$"

OlivinePort_Text_AskBoard:
    .string "Welcome to Fast Ship S.S.Aqua.\p"
    .string "Will you be boarding today?$"

OlivinePort_Text_AskTicket:
    .string "May I see your S.S.Ticket?$"

OlivinePort_Text_ComeAgain:
    .string "We hope to see you again!$"

OlivinePort_Text_FlashTicket:
    .string "{PLAYER} flashed the S.S.Ticket.\p"
    .string "That's it. Thank you!$"

OlivinePort_Text_NoTicket:
    .string "{PLAYER} tried to show the\n"
    .string "S.S.Ticket…\p"
    .string "…But no Ticket!\p"
    .string "Sorry!\n"
    .string "You may board only\l"
    .string "if you have an S.S.Ticket.$"

OlivinePort_Text_FishingGuru1:
    .string "Mareanie are easy to catch here.\p"
    .string "They're kind of rare elsewhere.$"

OlivinePort_Text_FishingGuru2:
    .string "How many Rods do you have?\p"
    .string "Different Rods catch different\n"
    .string "Pokémon.$"

OlivinePort_Text_Youngster:
    .string "S.S.Aqua uses jets to skim\n"
    .string "over the waves!$"

OlivinePort_Text_CooltrainerF:
    .string "There are lots of Pokémon in\p"
    .string "the world. I wish I could travel...$"

OlivinePort_Text_SailorBeforeHOF:
    .string "We don't want you to fall into the\n"
    .string "sea, so you're not allowed in.$"

OlivineCity_PortInside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto_if_set FLAG_BADGE08_GET, OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION_3
OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION_2:
	setflag FLAG_HIDE_BLAINE_OLIVINEPORT
	return

OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	clearflag FLAG_HIDE_BLAINE_OLIVINEPORT
	return

OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION_3:
	goto_if_unset FLAG_CANSAIL_FARAWAYISLAND, OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	goto OlivineCity_PortInside_MapScripts_MAP_SCRIPT_ON_TRANSITION_2


OlivinePort_Sailor::
	goto_if_unset FLAG_CANSAIL_FARAWAYISLAND, OlivinePort_Sailor_1
	msgbox OlivinePort_Sailor_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OlivinePort_Sailor_5
	msgbox OlivinePort_Sailor_Text_3
	closemessage
	warp MAP_FARAWAY_ISLAND_OUTSIDE, 13, 38
	waitstate
	release
	end

OlivinePort_Sailor_1:
	msgbox OlivinePort_Sailor_Text_0, MSGBOX_NPC
	return

OlivinePort_Sailor_5:
	msgbox OlivinePort_Sailor_Text_2
	release
	end


OlivinePortBlaine::
	lock
	goto_if_set FLAG_CANSAIL_FARAWAYISLAND, OlivinePortBlaine_2
	goto_if_unset FLAG_TEMP_5, OlivinePortBlaine_5
OlivinePortBlaine_4:
	goto_if_set FLAG_TEMP_5, OlivinePortBlaine_8
OlivinePortBlaine_7:
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, FALSE
	msgbox OlivinePortBlaine_Text_9
	msgbox OlivinePortBlaine_Text_10
	trainerbattle_no_intro TRAINER_BLAINE_OLIVINE, OlivinePortBlaine_Text_11
	createfieldmugshot MUGSHOT_BLAINE
	msgbox OlivinePortBlaine_Text_12
	closemessage
	moveobjecttocoords LOCALID_OLI_BLAINE, 8, 16, DIR_SOUTH
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_SOUTH
	delay 60
	moveobjecttocoords LOCALID_OLI_BLAINE, 8, 12, DIR_NORTH
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_EAST
	turnobject LOCALID_OLI_BLAINE, DIR_WEST
	createfieldmugshot MUGSHOT_BLAINE
	msgbox OlivinePortBlaine_Text_13
	closemessage
	applymovement LOCALID_OLI_BLAINE, OlivinePortBlaine_Movement_0
	waitmovement
	playse SE_EXIT
	removeobject LOCALID_OLI_BLAINE
	setflag FLAG_CANSAIL_FARAWAYISLAND
	setflag FLAG_HIDE_BLAINE_OLIVINEPORT
	release
	end

OlivinePortBlaine_2:
	msgbox OlivinePortBlaine_Text_0
	release
	end

OlivinePortBlaine_5:
	msgbox OlivinePortBlaine_Text_1
	faceplayer
	msgbox OlivinePortBlaine_Text_2
	msgbox OlivinePortBlaine_Text_3, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq OlivinePortBlaine_11
	msgbox OlivinePortBlaine_Text_5, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OlivinePortBlaine_15
	goto OlivinePortBlaine_4

OlivinePortBlaine_8:
	msgbox OlivinePortBlaine_Text_7, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OlivinePortBlaine_13
	goto OlivinePortBlaine_7

OlivinePortBlaine_11:
	msgbox OlivinePortBlaine_Text_4
	release
	end

OlivinePortBlaine_13:
	msgbox OlivinePortBlaine_Text_8
	release
	end

OlivinePortBlaine_15:
	msgbox OlivinePortBlaine_Text_6
	setflag FLAG_TEMP_5
	release
	end


OlivinePortBlaine_Movement_0:
	walk_up
	walk_up
	walk_up
	step_end

OlivinePort_Sailor_Text_0:
	.string "Sorry, but the ship is not going to\n"
	.string "leave anywhere anytime soon.$"

OlivinePort_Sailor_Text_1:
	.string "I was told to sail you to this\n"
	.string "oddly specific location. Do you\l"
	.string "want to go now?$"

OlivinePort_Sailor_Text_2:
	.string "Oh, alright...$"

OlivinePort_Sailor_Text_3:
	.string "Then let's do it!\p"
	.string "Anchors aweigh! We're setting sail\n"
	.string "to the unknown!$"

OlivinePortBlaine_Text_0:
	.string "Blaine: I let the sailor know about the\n"
	.string "island.$"

OlivinePortBlaine_Text_1:
	.string "???: Ahh... Nothing quite like \n"
	.string "a refreshing Soda Pop!$"

OlivinePortBlaine_Text_2:
	.string "Oh! Are those all 8 badges of Johto?\p"
	.string "You must be quite a trainer to have\n"
	.string "achieved such a feat!\p"
	.string "My name is Blaine. I am a Gym Leader in\n"
	.string "another region.\p"
	.string "Blaine: Ooh! I have an idea!\p"
	.string "Quiz time!$"

OlivinePortBlaine_Text_3:
	.string "Blaine: Are you afraid of the unknown?$"

OlivinePortBlaine_Text_4:
	.string "Oh... Wrong Answer!$"

OlivinePortBlaine_Text_5:
	.string "Blaine: Good!\p"
	.string "Next question!\p"
	.string "Do you think you could beat me in\n"
	.string "a Pokémon battle?$"

OlivinePortBlaine_Text_6:
	.string "Blaine: I respect the honesty, but you\n"
	.string "should have a bit more confidence\l"
	.string "in yourself!$"

OlivinePortBlaine_Text_7:
	.string "Changed your mind about the\n"
	.string "last question?\p"
	.string "Do you think you could beat me in\n"
	.string "a Pokémon battle?$"

OlivinePortBlaine_Text_8:
	.string "Blaine: Still not confident enough?\n"
	.string "Well I can't blame you. \p"
	.string "After all, I am quite the fiery soul!\n"
	.string "Ho ho ho!$"

OlivinePortBlaine_Text_9:
	.string "Blaine: Such a bold statement! \n"
	.string "I shall put that to the test right here!$"

OlivinePortBlaine_Text_10:
	.string "Hope you brought a Burn Heal!$"

OlivinePortBlaine_Text_11:
	.string "Wowzers! You scorched me!$"

OlivinePortBlaine_Text_12:
	.string "Blaine: Yowch! I got burned!\n"
	.string "You're the real deal!\p"
	.string "Here's the thing. I was visiting\n"
	.string "Johto to check up on my old friend\l"
	.string "Oak, who is currently here. \p"
	.string "I found this old map of an island\n"
	.string "we visited long, long ago.\p"
	.string "I don't think anyone has visited it\n"
	.string "since then. \p"
	.string "I will tell the sailor about the island.\n"
	.string "Speak to him if you wish to visit it.\p"
	.string "You might find some rare Pokémon there!$"

OlivinePortBlaine_Text_13:
	.string "Good luck out there!$"
