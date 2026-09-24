
Gate_Route31_VioletCity_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Gate_Route31_VioletCity_OnTransition
	.byte 0

Gate_Route31_VioletCity_OnTransition::
    call Common_EventScript_SetupRivalGfxId
    end

Gate_Route31_VioletCity_EventScript_Policeman::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_Text_Policeman:
	.string "Hi there! Did you visit\n"
	.string "Sprout Tower?$"

Gate_Route31_VioletCity_Text_CooltrainerF:
	.string "I saw the cutest Pokémon out\n"
	.string "there.\p"
	.string "It looked a lot like Pikachu!$"

Gate_Route31_VioletCity_RivalExpShare::
	lock
	playse SE_EXIT
	playbgm MUS_HG_LYRA, TRUE
	msgbox Gate_Route31_VioletCity_RivalExpShare_Text_0
	closemessage
	moveobjecttocoords LOCALID_PLAYER, 6, 5, DIR_EAST
	clearflag FLAG_HIDE_RIVAL_VIOLETGATEHOUSE
	addobject LOCALID_GATEHOUSE_RIVAL
	applymovement LOCALID_GATEHOUSE_RIVAL, Gate_Route31_VioletCity_RivalExpShare_Movement_0
	waitmovement 0
	createfieldmugshotrival
	msgbox Gate_Route31_VioletCity_RivalExpShare_Text_1
	giveitem ITEM_EXP_SHARE
	setflag FLAG_RECEIVED_EXP_SHARE
	setflag FLAG_EXP_SHARE_OPTION
	createfieldmugshotrival
	msgbox Gate_Route31_VioletCity_RivalExpShare_Text_2
	msgbox Gate_Route31_VioletCity_RivalExpShare_Text_3
	msgbox Gate_Route31_VioletCity_RivalExpShare_Text_4
	closemessage
	setflag FLAG_HIDE_RIVAL_VIOLETGATEHOUSE
	setvar VAR_RIVAL_STATE, 4
	applymovement LOCALID_GATEHOUSE_RIVAL, Gate_Route31_VioletCity_RivalExpShare_Movement_1
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GATEHOUSE_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end


Gate_Route31_VioletCity_RivalExpShare_Movement_0:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Gate_Route31_VioletCity_RivalExpShare_Movement_1:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Gate_Route31_VioletCity_RivalExpShare_Text_0:
	.string "{PLAYER}! Wait up!$"

Gate_Route31_VioletCity_RivalExpShare_Text_1:
	.string "Professor Elm forgot to give you this.$"

Gate_Route31_VioletCity_RivalExpShare_Text_2:
	.string "It lets you train multiple Pokémon at\n"
	.string "once, quite a handy piece of tech!$"

Gate_Route31_VioletCity_RivalExpShare_Text_3:
	.string "If you haven't already, you should make\n"
	.string "use of those Poké Balls and catch lots\l"
	.string "of new Pokémon.$"

Gate_Route31_VioletCity_RivalExpShare_Text_4:
	.string "Anyway, I need to head back home.\n"
	.string "Hope to see you soon {PLAYER}!$"
