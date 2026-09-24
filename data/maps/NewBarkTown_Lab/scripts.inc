

NewBarkTown_Lab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Lab_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_Lab_OnFrame
	.byte 0

NewBarkTown_Lab_OnTransition::
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, NewBarkTown_Lab_EventScript_ElmAtComputer
	end
	
NewBarkTown_Lab_OnFrame::
	map_script_2 VAR_NEWBARKTOWN_LABSTATE, 4, NewBarkTown_Lab_EventScript_PoliceEpisode
	.2byte 0

NewBarkTown_Lab_EventScript_ElmAtComputer::
	setobjectxyperm LOCALID_ELM, 3, 2
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
	end

NewBarkTown_Lab_EventScript_TriggerStartLabLeft::	
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLabRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLab::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_ElmIntro
	end

NewBarkTown_EventScript_Aide1::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2Testimony::
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_NEWBARKTOWN_LAB_AIDE, NewBarkTown_Lab_EventScript_ElmAideIsWaiting
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmPostgameHint

	goto_if_set FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_CallMe
	call_if_unset FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_Check_Togepi
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5

	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmAideIsWaiting::
	msgbox NewBarkTown_Lab_Text_ElmAideIsWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Text_ElmAideIsWaiting:
	.string "{PLAYER}!\p"
	.string "What are you doing here?\p"
	.string "My aide is still waiting for you\n"
	.string "In Violet City!$"

NewBarkTown_Lab_EventScript_ElmIntro::
	createfieldmugshot MUGSHOT_ELM
	call ElmIntro
	@msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmRefused::
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmAccepted::
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
	delay 30
	playse SE_PC_LOGIN
	waitse
	playse SE_PIN
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
	delay 60
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
	waitmovement LOCALID_ELM
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
	removefieldmugshot
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
	waitmovement 0
	delay 30
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmChoosePokemon::
	removefieldmugshot
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Right
    waitmovement 0
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
	closemessage
	removefieldmugshot
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Down
    waitmovement 0
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
	release
	end

NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
	lock
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
	closemessage
	removefieldmugshot
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
	waitmovement 0
	release
	end

NewBarkTown_Lab_EventScript_ShouldntTouch::
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	closemessage
	end

NewBarkTown_Lab_EventScript_hideStarterCase::
    setflag FLAG_HIDE_STARTER_CASE
    return

NewBarkTown_Lab_EventScript_StarterCase::
    lock
	goto_if_eq VAR_FACING, DIR_SOUTH, NewBarkTown_Lab_EventScript_StarterCaseWrongSide
	callnative MigrateNationalPokedex
    goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
    goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_StarterCase_Choice
    msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	release
	closemessage
	end
NewBarkTown_Lab_EventScript_StarterCaseWrongSide::
	msgbox NewBarkTown_Lab_Text_StarterCaseWrongSide, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_StarterCase_Choice::
   callnative StartNewPokeballCaseUI
   waitstate
   goto NewBarkTown_Lab_EventScript_ChoseStarter

NewBarkTown_Lab_EventScript_ChoseStarter::
	showmonpic VAR_PLAYER_STARTER_SPECIES, 10, 3
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	bufferspeciesname STR_VAR_1, VAR_PLAYER_STARTER_SPECIES
	message NewBarkTown_Lab_Text_ReceivedStarter
	setvar VAR_STARTER_PICKING_STATE 1
	waitfanfare
	hidemonpic
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_StepBackFromStarter
	waitmovement 0
	updatefollowingmon
	setobjectxy OBJ_EVENT_ID_FOLLOWER, 9, 5
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterLeavesBall
	playse SE_BALL_OPEN
	waitmovement OBJ_EVENT_ID_FOLLOWER
	playmoncry VAR_PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterGreetsPlayer
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmoncry
	delay 45
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
	waitmessage
    closemessage
	removefieldmugshot
	release
	end

NewBarkTown_Lab_EventScript_ChoseStarter2::
    moveobjecttocoords OBJ_EVENT_ID_PLAYER, 6, 4, DIR_NORTH
    waitmovement 0
    @applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
    @waitmovement 0
    clearflag FLAG_HIDE_NEWBARK_RIVALMARILL
	setvar VAR_RIVAL_STATE, 2
	setvar VAR_STARTER_PICKING_STATE, 2
    goto NewBarkTown_Lab_EventScript_MrPokemon

NewBarkTown_Lab_EventScript_DeclinedStarter::
	hidemonpic
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
	closemessage
	release
	end



NewBarkTown_Lab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	end

NewBarkTown_Lab_EventScript_MrPokemon::
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
	setvar VAR_NEWBARK_TOWN_STATE, 3
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	closemessage
	removefieldmugshot
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
	waitmovement 0
	clearflag FLAG_RECEIVED_FIRST_BALLS
	clearflag FLAG_RECEIVED_EXP_SHARE
	setvar VAR_NEWBARK_TOWN_STATE, 3
	release
	end

NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
	waitmovement 0
	clearflag FLAG_RECEIVED_FIRST_BALLS
	clearflag FLAG_RECEIVED_EXP_SHARE
	setvar VAR_NEWBARK_TOWN_STATE, 3
	release
	end

CopNewBarkTown_Lab_EventScript_ElmState2::
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine1::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine2::
	call Common_EventScript_OutOfCenterPartyHeal
	release
	end



NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
	closemessage
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_PoliceEpisode::
	lock
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
	call NewBarkTown_Lab_EventScript_hideStarterCase
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
	waitmovement 0
	setflag FLAG_HIDE_LAB_POLICEMAN
	turnobject LOCALID_COP DIR_WEST
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceNameRival
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceYes
	end

NewBarkTown_Lab_EventScript_PoliceNo::
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
	end

NewBarkTown_Lab_EventScript_PoliceNameRival::
	special NameRival
	waitstate
	setflag FLAG_NAMED_SILVER
	goto NewBarkTown_Lab_EventScript_PoliceYes3


NewBarkTown_Lab_EventScript_PoliceNameRival2::
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_Lab_EventScript_PoliceYes3

NewBarkTown_Lab_EventScript_PoliceYes::
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_Lab_EventScript_PoliceYes2

NewBarkTown_Lab_EventScript_PoliceYes3::
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
	waitmovement 0
	removeobject LOCALID_COP

	@ setobjectxyperm LOCALID_COP, 25, 4
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
	waitmovement 0
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
	removefieldmugshot
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
	waitmovement 0
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
	delay 20
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
	waitmovement 0
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	clearflag FLAG_HIDE_MOMS_FRIEND2
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_EXP_SHARE
	removeitem ITEM_MYSTERY_EGG
	end

NewBarkTown_Lab_EventScript_PoliceYes2::
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
	waitmovement 0
	removeobject LOCALID_COP

	@ setobjectxyperm LOCALID_COP, 25, 4
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
	waitmovement 0
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
	removefieldmugshot
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
	waitmovement 0
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
	delay 20
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
	waitmovement 0
	createfieldmugshot MUGSHOT_ELM
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	clearflag FLAG_HIDE_MOMS_FRIEND2
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_EXP_SHARE
	removeitem ITEM_MYSTERY_EGG
	end

NewBarkTown_Lab_EventScript_ElmState5::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
	release
	end

NewBarkTown_Lab_EventScript_ElmMasterBall::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
	closemessage
	delay 20
	playse SE_PIN
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
	delay 60
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
	call NewBarkTown_Lab_GiveStarterMega
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	release
	end

NewBarkTown_Lab_EventScript_ElmKimono::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmLeague::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmSSTicket::
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
	giveitem ITEM_SS_TICKET
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
	release
	end

NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POKE_BALL, 10
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FIRST_BALLS
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
	msgbox NewBarkTown_Lab_Text_ExplainDexnav, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_Togepi::
	specialvar VAR_RESULT, CheckTogepi
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	return

NewBarkTown_Lab_EventScript_Elm_Togepi_Seen::
	msgbox NewBarkTown_Lab_Text_ShowTogepi1, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi2, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi3, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone1, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_SHINY_STONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SHOWN_ELM_TOGEPI
	release
	end

NewBarkTown_Lab_EventScript_Elm_CallMe::
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Movement_WalkRight:
	walk_right
	step_end

NewBarkTown_Lab_Movement_WalkLeft:
	walk_left
	step_end

NewBarkTown_Lab_Movement_StepBackFromStarter:
	walk_down
	face_up
	step_end

NewBarkTown_Lab_Movement_StarterLeavesBall:
	exit_pokeball
	face_down
	set_visible
	step_end

NewBarkTown_Lab_Movement_StarterGreetsPlayer:
	face_player
	delay_4
	jump_in_place_down
	emote_heart
	face_player
	step_end

NewBarkTown_LabMovement_WalkToElm:
	walk_up
	walk_up
	walk_up
	step_end

NewBarkTown_Lab_Movement_ReturnPlayer:
	walk_up
	step_end

NewBarkTown_Lab_Movement_CheckEmail:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	step_end

NewBarkTown_Lab_Movement_CheckEmailSlow:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

NewBarkTown_Lab_Movement_GotoComputerSafe:
	walk_up
	walk_left
	walk_left
	walk_left
	face_up
	step_end

NewBarkTown_Lab_Movement_ReturnFromEmail:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end

NewBarkTown_Lab_Movement_Look_Left:
	face_left
	step_end

NewBarkTown_Lab_Movement_Look_Up:
	face_up
	step_end


NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

NewBarkTown_Lab_Movement_Aide1LeavePlayer:
	walk_left
	walk_left
	walk_up
	walk_up
	face_down
	step_end

NeBarkTownLab_Movement_PlayerWalkToCop:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_up
	face_right
	step_end

NewBarkTownLab_Movement_Elm_Right:
    face_right
    step_end

NewBarkTownLab_Movement_Elm_Down:
    face_down
    step_end

NewBarkTown_Lab_Movement_CopLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_Lab_Movement_PlayerStepsToElm:
	walk_right
	face_up
	step_end

NewBarkTown_Lab_Movement_ElmStepBack:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	step_end

NewBarkTown_Lab_Movement_ElmStepForward:
	walk_fast_down
	step_end

NewBarkTown_Lab_Text_ShouldntTouch:
	.string "Probably shouldn't touch!$"

NewBarkTown_Lab_Text_StarterCaseWrongSide:
	.string "Oops, the case does not open\n"
	.string "from this side!$"

NewBarkTown_Lab_Text_ElmAccepted:
	.string "Thanks, {PLAYER}!\n"
	.string "You're a great help!$"

NewBarkTown_Lab_Text_ElmRefused:
	.string "But… Please, I need your\n"
	.string "help!$"

NewBarkTown_Lab_Text_ElmResearchAmbitions:
	.string "When I announce my findings,\n"
	.string "I'm sure we'll delve deeper\p"
	.string "into the many mysteries of\n"
	.string "Pokémon.\p"
	.string "You can count on it!$"

NewBarkTown_Lab_Text_ElmGotAnEmail:
	.string "Oh, hey! I got an e-mail!\p"
	.string "… … … … … … … …\n"
	.string "Hm… Uh-huh…\p"
	.string "Okay…$"

NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
	.string "Hey, listen.\p"
	.string "I have an acquaintance called\n"
	.string "Mr. Pokémon.\p"
	.string "He keeps finding weird things and\n"
	.string "raving about his discoveries.\p"
	.string "Anyway, I just got an e-mail\n"
	.string "from him saying that this\l"
	.string "time it's real.\p"
	.string "It is intriguing, but we're\n"
	.string "busy with our Pokémon research...\p"
	.string "Wait!\n"
	.string "I know!\p"
	.string "{PLAYER}, can you go in our\n"
	.string "place?$"

NewBarkTown_Lab_Text_ElmChooseAPokemon:
	.string "I want you to raise one of\n"
	.string "the Pokémon contained in this case.\p"
	.string "You'll be that Pokémon's\n"
	.string "first partner, {PLAYER}!\p"
	.string "Go on. Pick one!$"

NewBarkTown_Lab_Text_ElmWhereGoing:
	.string "Elm: Wait! Where are you\n"
	.string "going?$"

NewBarkTown_Lab_Text_ChooseCyndaquil:
	.string "Elm: You'll take Cyndaquil,\n"
	.string "the fire Pokémon?$"

NewBarkTown_Lab_Text_ChooseTotodile:
	.string "Elm: Do you want Totodile,\n"
	.string "the water Pokémon?$"

NewBarkTown_Lab_Text_ChooseChikorita:
	.string "Elm: So, you like Chikorita,\n"
	.string "the grass Pokémon?$"

NewBarkTown_Lab_Text_DidntChooseStarter:
	.string "Elm: Think it over carefully.\p"
	.string "Your partner is important.$"

NewBarkTown_Lab_Text_ChoseStarter:
	.string "Elm: I think that's a great\n"
	.string "Pokémon too!$"

NewBarkTown_Lab_Text_ReceivedStarter:
	.string "{PLAYER} received {STR_VAR_1}!$"

NewBarkTown_Lab_Text_Nickname:
	.string "Would you like to give your\n"
	.string "{STR_VAR_1} a nickname?$"

NewBarkTown_Lab_Text_ElmDirections1:
	.string "Mr. Pokémon lives a little bit\n"
	.string "beyond Cherrygrove, the next\l"
	.string "city over.\p"
	.string "It's almost a direct route\n"
	.string "there, so you can't miss it.\p"
	.string "But just in case, you have my\n"
	.string "phone number. Call me if\l"
	.string "anything comes up!$"


NewBarkTown_Lab_Text_ElmLetYourMonBattle:
	.string "If a wild Pokémon appears,\n"
	.string "let your Pokémon battle it!$"

NewBarkTown_Lab_Text_ElmDirections2:
	.string "If a wild Pokémon appears, let\n"
	.string "your Pokémon battle it!\p"
	.string "If your Pokémon is hurt, you\n"
	.string "should heal it with the machine\l"
	.string "to my right, or at the Pokémon Center.\p"
	.string "I'm counting on you!$"

NewBarkTown_Lab_Text_GotElmsNumber:
	.string "{PLAYER} got Elm's phone\n"
	.string "number.$"

NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
	.string "Mr. Pokémon goes everywhere and\n"
	.string "finds rarities.\p"
	.string "Too bad they're just rare and\n"
	.string "not very useful…$"

NewBarkTown_Lab_Text_ElmPokeBall:
	.string "It contains Pokémon caught\n"
	.string "by Prof. Elm.$"

@THEFT================================================================================

NewBarkTown_Lab_Text_ElmAfterTheft1:
	.string "Elm: {PLAYER}, this is terrible…\p"
	.string "Oh, yes, what was Mr. Pokémon's\n"
	.string "big discovery?$"

NewBarkTown_Lab_Text_ElmAfterTheft2:
	.string "{PLAYER} handed the Mystery Egg\n"
	.string "to Prof. Elm.$"

NewBarkTown_Lab_Text_ElmAfterTheft3:
	.string "Elm: This?$"

NewBarkTown_Lab_Text_ElmAfterTheft4:
	.string "But… Is it a Pokémon Egg?\p"
	.string "If it is, it is a great\n"
	.string "discovery!\p"
	.string "Elm: What?!?\p"
	.string "Prof. Oak gave you a Pokédex?\p"
	.string "{PLAYER}, is that true?\n"
	.string "Th-that's incredible!\p"
	.string "He is superb at seeing the\n"
	.string "potential of people as trainers.\p"
	.string "Wow, {PLAYER}. You may have what\n"
	.string "it takes to become the Champion.\p"
	.string "You seem to be getting on\n"
	.string "great with Pokémon too.\p"
	.string "You should take the Pokémon\n"
	.string "Gym challenge.\p"
	.string "The closest Gym would be the\n"
	.string "one in Violet City.\p"
	.string "…{PLAYER}. The road to the\n"
	.string "championship will be a long one.\p"
	.string "Before you leave, make sure\n"
	.string "that you talk to your mom.$"

NewBarkTown_Lab_Text_ElmStudyingEgg:
	.string "Elm: Don't give up!\n"
	.string "I'll call if I learn anything\l"
	.string "about that Egg!$"

NewBarkTown_Lab_Text_ElmAideHasEgg:
	.string "Elm: {PLAYER}? Didn't you meet\n"
	.string "my assistant?\p"
	.string "He should have met you with\n"
	.string "the Egg at Violet City's\p"
	.string "Pokémon Center.\p"
	.string "You must have just missed him.\n"
	.string "Try to catch him there.$"

NewBarkTown_Lab_Text_ElmWaitingEggHatch:
	.string "Elm: Hey, has that Egg changed\n"
	.string "any?$"

NewBarkTown_Lab_Text_ElmThoughtEggHatched:
	.string "{PLAYER}? I thought the Egg\n"
	.string "hatched.\p"
	.string "Where is the Pokémon?$"

NewBarkTown_Lab_Text_ShowTogepi1:
	.string "Elm: {PLAYER}, you look great!$"

NewBarkTown_Lab_Text_ShowTogepi2:
	.string "What? That Pokémon!?!$"

NewBarkTown_Lab_Text_ShowTogepi3:
	.string "The Egg hatched! So, Pokémon\n"
	.string "are born from Eggs…\p"
	.string "No, perhaps not all Pokémon\n"
	.string "are.\p"
	.string "Wow, there's still a lot of\n"
	.string "research to be done.$"

NewBarkTown_Lab_Text_ElmGiveEverstone1:
	.string "Thanks, {PLAYER}! You're helping\n"
	.string "unravel Pokémon mysteries for us!\p"
	.string "I want you to have this as a\n"
	.string "token of our appreciation.$"

NewBarkTown_Lab_Text_ElmGiveEverstone2:
	.string "That's a Shiny Stone.\p"
	.string "Some species of Pokémon evolve\n"
	.string "when they grow to certain levels.\p"
	.string "A Togetic will evolve\n"
	.string "with this one.$"

NewBarkTown_Lab_Text_ElmCallYou:
	.string "Elm: {PLAYER}, I'll call you if\n"
	.string "anything comes up.$"

NewBarkTown_Lab_Text_AideAfterTheft:
	.string "…sigh… That stolen Pokémon.\p"
	.string "I wonder how it's doing.\p"
	.string "They say a Pokémon raised by a\n"
	.string "bad person turns bad itself.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall1:
	.string "Elm: Hi, {PLAYER}!\p"
	.string "Thanks to you, my research is\n"
	.string "going great!\p"
	.string "Take this as a token of my\n"
	.string "appreciation.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall2:
	.string "The Master Ball is the best!\p"
	.string "It's the ultimate Ball! It'll\n"
	.string "catch any Pokémon without fail.\p"
	.string "It's given only to recognized\n"
	.string "Pokémon researchers.\p"
	.string "I think you can make much better\n"
	.string "use of it than I can, {PLAYER}!$"

NewBarkTown_Lab_Text_KimonoGirls:
	.string "By the way...\n"
	.string "A group of beautiful Kimono\l"
	.string "Girls were looking for you.\p"
	.string "They told me they are\n"
	.string "waiting for you at the\l"
	.string "Ecruteak Dance Theater.\p"
	.string "I know you've gone through many\n"
	.string "things since that Egg got you\l"
	.string "involved in all this...\p"
	.string "I hope you'll carry through it.$"

NewBarkTown_Lab_Text_KimonoWaiting:
	.string "Prof. Elm: The Kimono\n"
	.string "Girls are waiting for you at\l"
	.string "the Ecruteak Dance Theater.$"

NewBarkTown_Lab_Text_League:
	.string "Prof. Elm: Hahaha...\n"
	.string "Good job!\p"
	.string "That rare Egg has brought you\n"
	.string "a lot of trouble, huh?\p"
	.string "The Kimono Girls said something\n"
	.string "about me?\p"
	.string "I have nothing to do with it.\p"
	.string "You made your decision and went\n"
	.string "through with it.\p"
	.string "Having done so much, you should\n"
	.string "be able to face the League now!\p"
	.string "You should head for Indigo\n"
	.string "Plateau!\p"
	.string "Do you know how to get there?\n"
	.string "Follow Route 27 to Route 26.\p"
	.string "Once there, go straight north!$"


NewBarkTown_Lab_Text_ElmGiveTicket1:
	.string "Elm: {PLAYER}! There you are!\p"
	.string "I called because I have\n"
	.string "something for you.\p"
	.string "See? It's an S.S.Ticket.\p"
	.string "Now you can catch Pokémon in\n"
	.string "Sevii.$"

NewBarkTown_Lab_Text_ElmGiveTicket2:
	.string "The ship departs from Olivine\n"
	.string "City.\p"
	.string "But you knew that already,\n"
	.string "{PLAYER}.\p"
	.string "After all, you've traveled all\n"
	.string "over with your Pokémon.$"

NewBarkTown_Lab_Text_LabMonEgg:
	.string "It's the Pokémon Egg being\n"
	.string "studied by Prof. Elm.$"

NewBarkTown_Lab_Text_AideGivePotion:
	.string "{PLAYER}, I want you to have\n"
	.string "this for your errand.$"

NewBarkTown_Lab_Text_AideAlwaysBusy:
	.string "There are only three of us, so\n"
	.string "we're always busy.$"

NewBarkTown_Lab_Text_AideSave:
	.string "Don't forget to save your game\n"
	.string "regularly!\p"
	.string "Press the Start button, then\n"
	.string "Save the game!$"

NewBarkTown_Lab_Text_AideTheftTestimony:
	.string "There was a loud noise\n"
	.string "outside…\p"
	.string "When we went to look,\n"
	.string "someone stole a Pokémon.\p"
	.string "It's unbelievable that anyone\n"
	.string "would do that!\p"
	.string "…sigh… That stolen Pokémon.\p"
	.string "I wonder how it's doing.\p"
	.string "They say a Pokémon raised by a\n"
	.string "bad person turns bad itself.$"

NewBarkTown_Lab_Text_AideGiveBalls:
	.string "{PLAYER}!\p"
	.string "Use these on your Pokédex\n"
	.string "quest!$"

NewBarkTown_Lab_Text_ExplainDexnav:
	.string "We've also sent a Dexnav\n"
	.string "application to your Pokégear!\p"
	.string "Use it to catch lots of Pokémon!$"

NewBarkTown_Lab_Text_AideExplainBalls:
	.string "To add to your Pokédex, you\n"
	.string "have to catch Pokémon.\p"
	.string "Throw Poké Balls at wild\n"
	.string "Pokémon to get them.$"

NewBarkTown_Lab_Text_Officer1:
	.string "I heard a Pokémon was stolen\n"
	.string "here…\p"
	.string "I was just getting some\n"
	.string "information from Prof. Elm.\p"
	.string "Apparently, it was a young\n"
	.string "male with long, red hair…\p"
	.string "What?\p"
	.string "You battled a trainer like\n"
	.string "that?\p"
	.string "Did you happen to get his\n"
	.string "name?$"

NewBarkTown_Lab_Text_Officer2:
	.string "Ok! So Silver was his name.\p"
	.string "Thanks for helping my\n"
	.string "investigation!$"

NewBarkTown_Lab_Text_Officer3:
	.string "Ok! So {RIVAL} was his name.\p"
	.string "Thanks for helping my\n"
	.string "investigation!$"

NewBarkTown_Lab_Text_OfficerNo:
	.string "Surely you got his name?!$"

NewBarkTown_Lab_Text_Elm_CallMe:
	.string "Ah, {PLAYER}!\p"
	.string "How's your Pokédex coming along?\n"
	.string "I'm busy now, but call me sometime\l"
	.string "and I can check your progress!$"

NewBarkTown_Lab_GiveStarterMega::
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_0
	giveitem ITEM_BONDSTONE, 1
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_1
	return


NewBarkTown_Lab_EventScript_ElmPostgameHint::
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_PIN
	waitse
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2
	setflag FLAG_POSTGAME_FEATURES
	setflag FLAG_HIDE_VICTORYROAD_RIVAL
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_Lab_EventScript_ElmPostgameHint_2
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4
NewBarkTown_Lab_EventScript_ElmPostgameHint_1:
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5
	setflag FLAG_HIDE_MTSILVER_GUARD
	setflag FLAG_ALLOW_SOUTH_JOHTO_PASS
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
	setvar VAR_NEWBARK_TOWN_STATE, 11
	release
	end

NewBarkTown_Lab_EventScript_ElmPostgameHint_2:
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3
	goto NewBarkTown_Lab_EventScript_ElmPostgameHint_1


ElmIntro::
	msgbox ElmIntro_Text_0, MSGBOX_YESNO
	return


NewBarkTown_Lab_EventScript_ArtifactOfChaos::
	lock
	goto_if_set FLAG_ALL_INNATES_UNLOCKED, NewBarkTown_Lab_EventScript_ArtifactOfChaos_2
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_8
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8
NewBarkTown_Lab_EventScript_ArtifactOfChaos_1:
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ArtifactOfChaos_2:
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_0
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_5
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_5:
	playse SE_PC_OFF
	waitse
	clearflag FLAG_ALL_INNATES_UNLOCKED
	compare VAR_NEWBARKTOWN_LABSTATE, 11
	goto_if_lt NewBarkTown_Lab_EventScript_ArtifactOfChaos_12
	setflag FLAG_POSTGAME_FEATURES
NewBarkTown_Lab_EventScript_ArtifactOfChaos_11:
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_8:
	playse SE_SWITCH
	waitse
	setflag FLAG_ALL_INNATES_UNLOCKED
	clearflag FLAG_REPLAY_NO_INNATES
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_12:
	clearflag FLAG_POSTGAME_FEATURES
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_11


NewBarkTown_Lab_GiveStarterMega_Text_0:
	.string "Oh, and you got a Mega Ring from \n"
	.string "Prof. Oak?\l"
	.string "Then I think you are ready to handle\l"
	.string "this.$"

NewBarkTown_Lab_GiveStarterMega_Text_1:
	.string "It's a special Mega Stone, specifically\n"
	.string "for your starter Pokémon. I expect \l"
	.string "great things from you, {PLAYER}!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0:
	.string "Elm: {PLAYER}! There you are!\n"
	.string "I called because I heard that the \l"
	.string "Battle Tower is open! \p"
	.string "I hear strong trainers\n"
	.string "are gathering in there!\p"
	.string "You can get there from Route 40\n"
	.string "near Olivine City.$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1:
	.string "But first, let me upgrade your Pokédex\n"
	.string "with a new feature!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2:
	.string "Now you can view abilities of the\n"
	.string "opposing Pokémon with the L-button\l"
	.string "in battle! \p"
	.string "That will surely be handy as the\n"
	.string "battles get tougher!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3:
	.string "I also heard that Crystal went to train\n"
	.string "in Mt. Silver. \p"
	.string "She looked really tired\n"
	.string "the last time I saw her though... \p"
	.string "Could you check on her at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4:
	.string "I also heard that Gold went to train\n"
	.string "in Mt. Silver. \p"
	.string "He looked really tired\n"
	.string "the last time I saw him though...\p"
	.string "Could you check on him at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5:
	.string "I asked from the League to let you\n"
	.string "pass since you've the new Champion.$"

ElmIntro_Text_0:
	.string "Elm: {PLAYER}! There you are!\p"
	.string "I needed to ask you a favor.\p"
	.string "I'm conducting new Pokémon\n"
	.string "research right now. \p"
	.string "I was wondering if you could help\n"
	.string "me with it, {PLAYER}.\p"
	.string "You see…\p"
	.string "I'm writing a paper that I\n"
	.string "want to present at a conference.\p"
	.string "But there are some things I\n"
	.string "don't quite understand yet.\p"
	.string "So!\p"
	.string "I'd like you to raise a\n"
	.string "Pokémon that I recently caught.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_0:
	.string "The Artifact of Chaos is humming.\p"
	.string "All innate abilities are currently\n"
	.string "active.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1:
	.string "Deactivate the Artifact?$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2:
	.string "The glow from the Artifact fades.\p"
	.string "Innate abilities will now unlock at\n"
	.string "their intended levels again.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3:
	.string "The Artifact continues humming.\n"
	.string "Hope Elm hasn't noticed yet!$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4:
	.string "Amidst the books is Elm's very own\n"
	.string "Artifact of Chaos.\p"
	.string "There's a small label on the side:\n"
	.string "DO NOT TOUCH.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5:
	.string "Important! Activating this Artifact\n"
	.string "unlocks all innate abilities,\l"
	.string "regardless of a Pokémon's level.\p"
	.string "It also lets you inspect enemy\n"
	.string "innates in battle by pressing L.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6:
	.string "This is not the intended way to play\n"
	.string "the game and will not be balanced\l"
	.string "at all.\p"
	.string "If you understand and still wish to\n"
	.string "activate it, choose Yes.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7:
	.string "{PLAYER} tapped the Artifact.\p"
	.string "Game balance quietly\n"
	.string "leaves the building.\p"
	.string "All innates are now active. Press L\n"
	.string "in battle to inspect enemy innates.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8:
	.string "{PLAYER} left the Artifact alone.\n"
	.string "Chaos shall not win today.$"
