
.set LOCALID_ICEPATH1_KIMONO, 9
IcePath_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcePath_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

IcePath_1F_OnTransition: 
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_HIDE_ICEPATH_RIVAL
	goto_if_ne VAR_RIVAL_STATE, 9, IcePath_1F_OnTransition_SetTime
	clearflag FLAG_HIDE_ICEPATH_RIVAL

IcePath_1F_OnTransition_SetTime:
	callnative SetTimeBasedEncounters
	end

IcePath_1F_EventScript_KimonoGirl::
	lock
	playbgm MUS_HG_KIMONO_GIRL, TRUE
	goto_if_eq VAR_FACING, DIR_SOUTH, IcePath_1F_EventScript_KimonoGirlPushPrompt
	msgbox IcePath_1F_Text_Stuck1, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

IcePath_1F_Trigger_KimonoGirl::
	lock
	msgbox IcePath_1F_Text_Leave, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	release
	end

IcePath_1F_EventScript_KimonoGirlPushPrompt::
	msgbox IcePath_1F_Text_Stuck2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, IcePath_1F_EventScript_KimonoGirlRefused
IcePath_1F_EventScript_KimonoGirlPush::
	msgbox IcePath_1F_Text_Shove, MSGBOX_AUTOCLOSE
	closemessage
	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_PLAYER, IcePath_Movement_PlayerJump
	waitmovement 0
	waitse
	playse SE_M_ICY_WIND
	applymovement LOCALID_ICEPATH1_KIMONO, IcePath_Movement_KimonoSlide
	waitmovement 0
	createfieldmugshot MUGSHOT_KIMONO_GIRL
	msgbox IcePath_1F_Text_Thanks, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ICEPATH1_KIMONO, IcePath_Movement_KimonoLeave
	waitmovement LOCALID_ICEPATH1_KIMONO
	setflag FLAG_HIDE_ICE_PATH_KIMONO
	removeobject LOCALID_ICEPATH1_KIMONO
	playse SE_EXIT
	fadedefaultbgm
	setvar VAR_ICE_PATH_STATE, 2
	release
	end

IcePath_1F_EventScript_KimonoGirlRefused::
	msgbox IcePath_1F_Text_Cruel, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, IcePath_1F_EventScript_KimonoGirlPush
	goto_if_eq VAR_RESULT, FALSE, IcePath_1F_EventScript_KimonoGirlRefused

IcePath_Movement_PlayerJump:
	jump_in_place_down
	step_end

IcePath_Movement_KimonoSlide:
	slide_down
	slide_down
	slide_down
	slide_down
	walk_in_place_fast_down
	face_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

IcePath_Movement_KimonoLeave:
	walk_down
	walk_down
	walk_down
	step_end

IcePath_1F_Text_Leave:
	.string "Kimono Girl: .....................$"

IcePath_1F_Text_Stuck1:
    .string "Me oh my... Is that you, {PLAYER}?\n"
    .string "Fancy meeting you here!\p"
    .string "To tell the truth... my sandals are\n"
    .string "frozen on the ice, and I am stuck.\p"
    .string "In other words, my flip-flops are\n"
    .string "quick-frozen to the ground.\p"
    .string "Tee hee.\p"
    .string "Well, it's no laughing matter.\p"
    .string "Would you come around and push\n"
    .string "my back?$"

IcePath_1F_Text_Stuck2:
    .string "Me oh my... Is that you, {PLAYER}?\n"
    .string "Fancy meeting you here!\p"
    .string "To tell the truth... my sandals are\n"
    .string "frozen on the ice, and I am stuck.\p"
    .string "In other words, my flip-flops are\n"
    .string "quick-frozen with the ground.\p"
    .string "Tee hee.\p"
    .string "Well, it's no laughing matter.\n"
    .string "Would you push my back?$"

IcePath_1F_Text_Shove:
    .string "....Shove!....$"

IcePath_1F_Text_Cruel:
    .string "Don't be so cruel.\n"
    .string "You will push my back, won't you?$"

IcePath_1F_Text_Thanks:
    .string "You really are kind.\n"
    .string "Thank you so much!$"

IcePath_1F_Rival::
	compare VAR_RIVAL_STATE, 9
	goto_if_eq IcePath_1F_Rival_2
IcePath_1F_Rival_1:
	end

IcePath_1F_Rival_2:
	lock
	playse SE_PIN
	applymovement LOCALID_ICEPATH_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ICEPATH_RIVAL, IcePath_1F_Rival_Movement_0
	waitmovement 0
	waitse
	approachobject LOCALID_PLAYER, LOCALID_ICEPATH_RIVAL, DIR_EAST, DIR_WEST
	waitmovement 0
	delay 30
	createfieldmugshotrival
	msgbox IcePath_1F_Rival_Text_0
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq IcePath_1F_Rival_5
	trainerbattle_no_intro TRAINER_RIVAL_GOLD_ICEPATH, IcePath_1F_Rival_Text_1
IcePath_1F_Rival_4:
	createfieldmugshotrival
	msgbox IcePath_1F_Rival_Text_2
	closemessage
	applymovement LOCALID_ICEPATH_RIVAL, IcePath_1F_Rival_Movement_1
	waitmovement 0
	delay 30
	createfieldmugshotrival
	msgbox IcePath_1F_Rival_Text_3
	removefieldmugshot
	closemessage
	applymovement LOCALID_ICEPATH_RIVAL, IcePath_1F_Rival_Movement_2
	waitmovement 0
	setvar VAR_RIVAL_STATE, 10
	setflag FLAG_HIDE_ICEPATH_RIVAL
	clearflag FLAG_HIDE_VICTORYROAD_RIVAL
	removeobject LOCALID_ICEPATH_RIVAL
	release
	goto IcePath_1F_Rival_1

IcePath_1F_Rival_5:
	trainerbattle_no_intro TRAINER_RIVAL_CRYSTAL_ICEPATH, IcePath_1F_Rival_Text_1
	goto IcePath_1F_Rival_4


IcePath_1F_Rival_Movement_0:
	face_left
	step_end

IcePath_1F_Rival_Movement_1:
	walk_in_place_left
	step_end

IcePath_1F_Rival_Movement_2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

IcePath_1F_Rival_Text_0:
	.string "So you've made it here too... With all\n"
	.string "those badges in tow...\p"
	.string "I'm not surprised, you just have the\n"
	.string "raw talent for it I suppose.\p"
	.string "However!\n"
	.string "I've been training so hard now!\p"
	.string "There's just no way you can make\n"
	.string "up for that. Let me prove it to you,\l"
	.string "right here, right now, {PLAYER}!$"

IcePath_1F_Rival_Text_1:
	.string "How...?$"

IcePath_1F_Rival_Text_2:
	.string "I trained every route from\n"
	.string "here to Cianwood. Without any breaks.\p"
	.string "And you just do it without breaking a\n"
	.string "sweat, like it's all a fun little game\l"
	.string "to you.$"

IcePath_1F_Rival_Text_3:
	.string "I'm just... So frustrated with my\n"
	.string "progress.\p"
	.string "No matter how much I train...\p"
	.string "I need to keep pushing on.$"
