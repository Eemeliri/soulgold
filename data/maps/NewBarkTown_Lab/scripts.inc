# 1 "data/maps/NewBarkTown_Lab/scripts.pory"

# 2 "data/maps/NewBarkTown_Lab/scripts.pory"

# 3 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_MapScripts::
# 4 "data/maps/NewBarkTown_Lab/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Lab_OnTransition
# 5 "data/maps/NewBarkTown_Lab/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_Lab_OnFrame
# 6 "data/maps/NewBarkTown_Lab/scripts.pory"
	.byte 0
# 7 "data/maps/NewBarkTown_Lab/scripts.pory"

# 8 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_OnTransition::
# 9 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmAtComputer
# 10 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, NewBarkTown_Lab_EventScript_ElmAtComputer
# 11 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, NewBarkTown_Lab_EventScript_ElmAtComputer
# 12 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 13 "data/maps/NewBarkTown_Lab/scripts.pory"
	
# 14 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_OnFrame::
# 15 "data/maps/NewBarkTown_Lab/scripts.pory"
	map_script_2 VAR_NEWBARKTOWN_LABSTATE, 4, NewBarkTown_Lab_EventScript_PoliceEpisode
# 16 "data/maps/NewBarkTown_Lab/scripts.pory"
	.2byte 0
# 17 "data/maps/NewBarkTown_Lab/scripts.pory"

# 18 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAtComputer::
# 19 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxyperm LOCALID_ELM, 3, 2
# 20 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
# 21 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 22 "data/maps/NewBarkTown_Lab/scripts.pory"

# 23 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabLeft::	
# 24 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 25 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
# 26 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 27 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 28 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 29 "data/maps/NewBarkTown_Lab/scripts.pory"

# 30 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabRight::
# 31 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 32 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
# 33 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 34 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 35 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 36 "data/maps/NewBarkTown_Lab/scripts.pory"

# 37 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLab::
# 38 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 39 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
# 40 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 41 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmIntro
# 42 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 43 "data/maps/NewBarkTown_Lab/scripts.pory"

# 44 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide1::
# 45 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 46 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 47 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
# 48 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 49 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 50 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 51 "data/maps/NewBarkTown_Lab/scripts.pory"

# 52 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2::
# 53 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 54 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 55 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
# 56 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
# 57 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 58 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 59 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 60 "data/maps/NewBarkTown_Lab/scripts.pory"

# 61 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2Testimony::
# 62 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
# 63 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 64 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 65 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 66 "data/maps/NewBarkTown_Lab/scripts.pory"

# 67 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm::
# 68 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 69 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 70 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_HIDE_NEWBARKTOWN_LAB_AIDE, NewBarkTown_Lab_EventScript_ElmAideIsWaiting
# 71 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
# 72 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
# 73 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
# 74 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmSSTicket
# 75 "data/maps/NewBarkTown_Lab/scripts.pory"

# 76 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_CallMe
# 77 "data/maps/NewBarkTown_Lab/scripts.pory"
	call_if_unset FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_Check_Togepi
# 78 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
# 79 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5
# 80 "data/maps/NewBarkTown_Lab/scripts.pory"

# 81 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
# 82 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
# 83 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
# 84 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
# 85 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 86 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 87 "data/maps/NewBarkTown_Lab/scripts.pory"

# 88 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAideIsWaiting::
# 89 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAideIsWaiting, MSGBOX_DEFAULT
# 90 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 91 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 92 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 93 "data/maps/NewBarkTown_Lab/scripts.pory"

# 94 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAideIsWaiting:
# 95 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 96 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What are you doing here?\p"
# 97 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "My aide is still waiting for you\n"
# 98 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "In VIOLET CITY!$"
# 99 "data/maps/NewBarkTown_Lab/scripts.pory"

# 100 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmIntro::
# 101 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
# 102 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 103 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 104 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 105 "data/maps/NewBarkTown_Lab/scripts.pory"

# 106 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmRefused::
# 107 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
# 108 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 109 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 110 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 111 "data/maps/NewBarkTown_Lab/scripts.pory"

# 112 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAccepted::
# 113 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
# 114 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
# 115 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 116 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_LOGIN
# 117 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 118 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 119 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
# 120 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 121 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
# 122 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
# 123 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 124 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 125 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
# 126 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 127 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
# 128 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 129 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 130 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 131 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 132 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
# 133 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 134 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 135 "data/maps/NewBarkTown_Lab/scripts.pory"

# 136 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmChoosePokemon::
# 137 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
# 138 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 139 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
# 140 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 141 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 142 "data/maps/NewBarkTown_Lab/scripts.pory"

# 143 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
# 144 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 145 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
# 146 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 147 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
# 148 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 149 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 150 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 151 "data/maps/NewBarkTown_Lab/scripts.pory"

# 152 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ShouldntTouch::
# 153 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 154 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 155 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 156 "data/maps/NewBarkTown_Lab/scripts.pory"

# 157 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_hideStarterCase::
# 158 "data/maps/NewBarkTown_Lab/scripts.pory"
    setflag FLAG_HIDE_STARTER_CASE
# 159 "data/maps/NewBarkTown_Lab/scripts.pory"
    return
# 160 "data/maps/NewBarkTown_Lab/scripts.pory"

# 161 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase::
# 162 "data/maps/NewBarkTown_Lab/scripts.pory"
    lock
# 163 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
# 164 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_StarterCase_Choice
# 165 "data/maps/NewBarkTown_Lab/scripts.pory"
    msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 166 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 167 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 168 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 169 "data/maps/NewBarkTown_Lab/scripts.pory"

# 170 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase_Choice::
# 171 "data/maps/NewBarkTown_Lab/scripts.pory"
   callnative StartNewPokeballCaseUI
# 172 "data/maps/NewBarkTown_Lab/scripts.pory"
   waitstate
# 173 "data/maps/NewBarkTown_Lab/scripts.pory"
   goto NewBarkTown_Lab_EventScript_ChoseStarter
# 174 "data/maps/NewBarkTown_Lab/scripts.pory"

# 175 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter::
# 176 "data/maps/NewBarkTown_Lab/scripts.pory"
    removeobject VAR_LAST_TALKED
# 177 "data/maps/NewBarkTown_Lab/scripts.pory"
    showmonpic VAR_PLAYER_STARTER_SPECIES, 10, 3
# 178 "data/maps/NewBarkTown_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 179 "data/maps/NewBarkTown_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_PLAYER_STARTER_SPECIES
# 180 "data/maps/NewBarkTown_Lab/scripts.pory"
	message NewBarkTown_Lab_Text_ReceivedStarter
# 181 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitfanfare
# 182 "data/maps/NewBarkTown_Lab/scripts.pory"
    hidemonpic
# 183 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
# 184 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 185 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 186 "data/maps/NewBarkTown_Lab/scripts.pory"

# 187 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_DeclinedStarter::
# 188 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 189 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
# 190 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 191 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 192 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 193 "data/maps/NewBarkTown_Lab/scripts.pory"

# 194 "data/maps/NewBarkTown_Lab/scripts.pory"

# 195 "data/maps/NewBarkTown_Lab/scripts.pory"

# 196 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_NicknameStarter::
# 197 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_0x8004, 0
# 198 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 199 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 200 "data/maps/NewBarkTown_Lab/scripts.pory"

# 201 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemon::
# 202 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
# 203 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 204 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 205 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 206 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 207 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 208 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
# 209 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
# 210 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 211 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 212 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_POTION
# 213 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 214 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 215 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 216 "data/maps/NewBarkTown_Lab/scripts.pory"

# 217 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
# 218 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
# 219 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 220 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 221 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_POTION
# 222 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 223 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 224 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 225 "data/maps/NewBarkTown_Lab/scripts.pory"

# 226 "data/maps/NewBarkTown_Lab/scripts.pory"
CopNewBarkTown_Lab_EventScript_ElmState2::
# 227 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 228 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 229 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
# 230 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 231 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 232 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 233 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 234 "data/maps/NewBarkTown_Lab/scripts.pory"

# 235 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine1::
# 236 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 237 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
# 238 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
# 239 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 240 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 241 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 242 "data/maps/NewBarkTown_Lab/scripts.pory"

# 243 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine2::
# 244 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 245 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 246 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 247 "data/maps/NewBarkTown_Lab/scripts.pory"

# 248 "data/maps/NewBarkTown_Lab/scripts.pory"

# 249 "data/maps/NewBarkTown_Lab/scripts.pory"

# 250 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
# 251 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 252 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 253 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 254 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 255 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
# 256 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 257 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POTION
# 258 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 259 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_FIRST_POTION
# 260 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
# 261 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 262 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 263 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 264 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 265 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 266 "data/maps/NewBarkTown_Lab/scripts.pory"

# 267 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceEpisode::
# 268 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 269 "data/maps/NewBarkTown_Lab/scripts.pory"
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
# 270 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_hideStarterCase
# 271 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
# 272 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 273 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_LAB_POLICEMAN
# 274 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject LOCALID_COP DIR_WEST
# 275 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
# 276 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceNameRival
# 277 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceYes
# 278 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 279 "data/maps/NewBarkTown_Lab/scripts.pory"

# 280 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNo::
# 281 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
# 282 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
# 283 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
# 284 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 285 "data/maps/NewBarkTown_Lab/scripts.pory"

# 286 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival::
# 287 "data/maps/NewBarkTown_Lab/scripts.pory"
	special NameRival
# 288 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_NAMED_SILVER
# 289 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 290 "data/maps/NewBarkTown_Lab/scripts.pory"

# 291 "data/maps/NewBarkTown_Lab/scripts.pory"

# 292 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival2::
# 293 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 294 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 295 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 296 "data/maps/NewBarkTown_Lab/scripts.pory"

# 297 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes::
# 298 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
# 299 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 300 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes2
# 301 "data/maps/NewBarkTown_Lab/scripts.pory"

# 302 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes3::
# 303 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT @okay, for some reason this script doesn't take effect at all... Added a duplicate after this because it was a workaround.
# 304 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 305 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 306 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 307 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 308 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 309 "data/maps/NewBarkTown_Lab/scripts.pory"

# 310 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 311 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 312 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 313 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 314 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 315 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 316 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 317 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 318 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 319 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 320 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 321 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 322 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 323 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 324 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 325 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 326 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 327 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 328 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 329 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 330 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 331 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 332 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 333 "data/maps/NewBarkTown_Lab/scripts.pory"

# 334 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes2::
# 335 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 336 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 337 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 338 "data/maps/NewBarkTown_Lab/scripts.pory"

# 339 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 340 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 341 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 342 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 343 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 344 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 345 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 346 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 347 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 348 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 349 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 350 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 351 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 352 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 353 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 354 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 355 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 356 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 357 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 358 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 359 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 360 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 361 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 362 "data/maps/NewBarkTown_Lab/scripts.pory"

# 363 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmState5::
# 364 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 365 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 366 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
# 367 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 368 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
# 369 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 370 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 371 "data/maps/NewBarkTown_Lab/scripts.pory"
	
# 372 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmMasterBall::
# 373 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 374 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 375 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
# 376 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_MASTER_BALL
# 377 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
# 378 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 379 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 380 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 381 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
# 382 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 383 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
# 384 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 385 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
# 386 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
# 387 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_SILVER
# 388 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
# 389 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
# 390 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 391 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 392 "data/maps/NewBarkTown_Lab/scripts.pory"

# 393 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmKimono::
# 394 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 395 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 396 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
# 397 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 398 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 399 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 400 "data/maps/NewBarkTown_Lab/scripts.pory"

# 401 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmLeague::
# 402 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 403 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 404 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
# 405 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 406 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 407 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 408 "data/maps/NewBarkTown_Lab/scripts.pory"

# 409 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmSSTicket::
# 410 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
# 411 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_SS_TICKET
# 412 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
# 413 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 414 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
# 415 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 416 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
# 417 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 418 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 419 "data/maps/NewBarkTown_Lab/scripts.pory"

# 420 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
# 421 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 422 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 423 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 424 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 425 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
# 426 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 427 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POKE_BALL, 5
# 428 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 429 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_FIRST_BALLS
# 430 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
# 431 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 432 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 433 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 434 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 435 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 436 "data/maps/NewBarkTown_Lab/scripts.pory"

# 437 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
# 438 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
# 439 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 440 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 441 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 442 "data/maps/NewBarkTown_Lab/scripts.pory"

# 443 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_Togepi::
# 444 "data/maps/NewBarkTown_Lab/scripts.pory"
	specialvar VAR_RESULT, CheckTogepi
# 445 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
# 446 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 447 "data/maps/NewBarkTown_Lab/scripts.pory"

# 448 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Togepi_Seen::
# 449 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShowTogepi1, MSGBOX_DEFAULT
# 450 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 451 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShowTogepi2, MSGBOX_DEFAULT
# 452 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 453 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShowTogepi3, MSGBOX_DEFAULT
# 454 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 455 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone1, MSGBOX_DEFAULT
# 456 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 457 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_EVERSTONE
# 458 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 459 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone2, MSGBOX_DEFAULT
# 460 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 461 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_SHOWN_ELM_TOGEPI
# 462 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 463 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 464 "data/maps/NewBarkTown_Lab/scripts.pory"

# 465 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_CallMe::
# 466 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
# 467 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 468 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 469 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 470 "data/maps/NewBarkTown_Lab/scripts.pory"

# 471 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkRight:
# 472 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 473 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 474 "data/maps/NewBarkTown_Lab/scripts.pory"

# 475 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkLeft:
# 476 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 477 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 478 "data/maps/NewBarkTown_Lab/scripts.pory"

# 479 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_LabMovement_WalkToElm:
# 480 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 481 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 482 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 483 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 484 "data/maps/NewBarkTown_Lab/scripts.pory"

# 485 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnPlayer:
# 486 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 487 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 488 "data/maps/NewBarkTown_Lab/scripts.pory"

# 489 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmail:
# 490 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 491 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 492 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 493 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 494 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 495 "data/maps/NewBarkTown_Lab/scripts.pory"

# 496 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmailSlow:
# 497 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 498 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 499 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 500 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 501 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 502 "data/maps/NewBarkTown_Lab/scripts.pory"

# 503 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_GotoComputerSafe:
# 504 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 505 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 506 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 507 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 508 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 509 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 510 "data/maps/NewBarkTown_Lab/scripts.pory"

# 511 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnFromEmail:
# 512 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 513 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 514 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 515 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 516 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 517 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 518 "data/maps/NewBarkTown_Lab/scripts.pory"

# 519 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Left:
# 520 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_left
# 521 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 522 "data/maps/NewBarkTown_Lab/scripts.pory"

# 523 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Up:
# 524 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 525 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 526 "data/maps/NewBarkTown_Lab/scripts.pory"

# 527 "data/maps/NewBarkTown_Lab/scripts.pory"

# 528 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
# 529 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 530 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 531 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 532 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 533 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 534 "data/maps/NewBarkTown_Lab/scripts.pory"

# 535 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1LeavePlayer:
# 536 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 537 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 538 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 539 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 540 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 541 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 542 "data/maps/NewBarkTown_Lab/scripts.pory"

# 543 "data/maps/NewBarkTown_Lab/scripts.pory"
NeBarkTownLab_Movement_PlayerWalkToCop:
# 544 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 545 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 546 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 547 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 548 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 549 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 550 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 551 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 552 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 553 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_right
# 554 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 555 "data/maps/NewBarkTown_Lab/scripts.pory"

# 556 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CopLeaves:
# 557 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 558 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 559 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 560 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 561 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 562 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 563 "data/maps/NewBarkTown_Lab/scripts.pory"

# 564 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_PlayerStepsToElm:
# 565 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 566 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 567 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 568 "data/maps/NewBarkTown_Lab/scripts.pory"

# 569 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepBack:
# 570 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock_facing_direction
# 571 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 572 "data/maps/NewBarkTown_Lab/scripts.pory"
	unlock_facing_direction
# 573 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 574 "data/maps/NewBarkTown_Lab/scripts.pory"

# 575 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepForward:
# 576 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 577 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 578 "data/maps/NewBarkTown_Lab/scripts.pory"

# 579 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShouldntTouch:
# 580 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Probably shouldn't touch!$"
# 581 "data/maps/NewBarkTown_Lab/scripts.pory"

# 582 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmIntro:
# 583 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: {PLAYER}! There you are!\p"
# 584 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I needed to ask you a favor.\p"
# 585 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm conducting new POKéMON\n"
# 586 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "research right now. I was\l"
# 587 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "wondering if you could help\l"
# 588 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "me with it, {PLAYER}.\p"
# 589 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You see…\p"
# 590 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm writing a paper that I\n"
# 591 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "want to present at a conference.\p"
# 592 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But there are some things I\n"
# 593 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "don't quite understand yet.\p"
# 594 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "So!\p"
# 595 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd like you to raise a\n"
# 596 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "POKéMON that I recently caught.$"
# 597 "data/maps/NewBarkTown_Lab/scripts.pory"

# 598 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAccepted:
# 599 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks, {PLAYER}!\n"
# 600 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're a great help!$"
# 601 "data/maps/NewBarkTown_Lab/scripts.pory"

# 602 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmRefused:
# 603 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Please, I need your\n"
# 604 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "help!$"
# 605 "data/maps/NewBarkTown_Lab/scripts.pory"

# 606 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmResearchAmbitions:
# 607 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When I announce my findings,\n"
# 608 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm sure we'll delve deeper\p"
# 609 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "into the many mysteries of\n"
# 610 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "POKéMON.\p"
# 611 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can count on it!$"
# 612 "data/maps/NewBarkTown_Lab/scripts.pory"

# 613 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGotAnEmail:
# 614 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, hey! I got an e-mail!\p"
# 615 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "… … … … … … … …\n"
# 616 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hm… Uh-huh…\p"
# 617 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Okay…$"
# 618 "data/maps/NewBarkTown_Lab/scripts.pory"

# 619 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
# 620 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hey, listen.\p"
# 621 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have an acquaintance called\n"
# 622 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "MR. POKéMON.\p"
# 623 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He keeps finding weird things and\n"
# 624 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "raving about his discoveries.\p"
# 625 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Anyway, I just got an e-mail\n"
# 626 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from him saying that this\l"
# 627 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "time it's real.\p"
# 628 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It is intriguing, but we're\n"
# 629 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "busy with our POKéMON research...\p"
# 630 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wait!\n"
# 631 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I know!\p"
# 632 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, can you go in our\n"
# 633 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "place?$"
# 634 "data/maps/NewBarkTown_Lab/scripts.pory"

# 635 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmChooseAPokemon:
# 636 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I want you to raise one of\n"
# 637 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the POKéMON contained in these Balls.\p"
# 638 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You'll be that POKéMON's\n"
# 639 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "first partner, {PLAYER}!\p"
# 640 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Go on. Pick one!$"
# 641 "data/maps/NewBarkTown_Lab/scripts.pory"

# 642 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWhereGoing:
# 643 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: Wait! Where are you\n"
# 644 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going?$"
# 645 "data/maps/NewBarkTown_Lab/scripts.pory"

# 646 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseCyndaquil:
# 647 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: You'll take CYNDAQUIL,\n"
# 648 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the fire POKéMON?$"
# 649 "data/maps/NewBarkTown_Lab/scripts.pory"

# 650 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseTotodile:
# 651 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: Do you want TOTODILE,\n"
# 652 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the water POKéMON?$"
# 653 "data/maps/NewBarkTown_Lab/scripts.pory"

# 654 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseChikorita:
# 655 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: So, you like CHIKORITA,\n"
# 656 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the grass POKéMON?$"
# 657 "data/maps/NewBarkTown_Lab/scripts.pory"

# 658 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_DidntChooseStarter:
# 659 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: Think it over carefully.\p"
# 660 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Your partner is important.$"
# 661 "data/maps/NewBarkTown_Lab/scripts.pory"

# 662 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChoseStarter:
# 663 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: I think that's a great\n"
# 664 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "POKéMON too!$"
# 665 "data/maps/NewBarkTown_Lab/scripts.pory"

# 666 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ReceivedStarter:
# 667 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} received {STR_VAR_1}!$"
# 668 "data/maps/NewBarkTown_Lab/scripts.pory"

# 669 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Nickname:
# 670 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Would you like to give your\n"
# 671 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{STR_VAR_1} a nickname?$"
# 672 "data/maps/NewBarkTown_Lab/scripts.pory"

# 673 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections1:
# 674 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "MR. POKéMON lives a little bit\n"
# 675 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "beyond CHERRYGROVE, the next\l"
# 676 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "city over.\p"
# 677 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's almost a direct route\n"
# 678 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "there, so you can't miss it.\p"
# 679 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But just in case, you have my\n"
# 680 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "phone number. Call me if\l"
# 681 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "anything comes up!$"
# 682 "data/maps/NewBarkTown_Lab/scripts.pory"

# 683 "data/maps/NewBarkTown_Lab/scripts.pory"

# 684 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmLetYourMonBattle:
# 685 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild POKéMON appears,\n"
# 686 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "let your POKéMON battle it!$"
# 687 "data/maps/NewBarkTown_Lab/scripts.pory"

# 688 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections2:
# 689 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild POKéMON appears, let\n"
# 690 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "your POKéMON battle it!\p"
# 691 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If your POKéMON is hurt, you\n"
# 692 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "should heal it with the machine\l"
# 693 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to my right, or at the POKéCENTER.\p"
# 694 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm counting on you!$"
# 695 "data/maps/NewBarkTown_Lab/scripts.pory"

# 696 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_GotElmsNumber:
# 697 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} got ELM's phone\n"
# 698 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "number.$"
# 699 "data/maps/NewBarkTown_Lab/scripts.pory"

# 700 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
# 701 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "MR. POKéMON goes everywhere and\n"
# 702 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "finds rarities.\p"
# 703 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Too bad they're just rare and\n"
# 704 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "not very useful…$"
# 705 "data/maps/NewBarkTown_Lab/scripts.pory"

# 706 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmPokeBall:
# 707 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It contains a POKéMON caught\n"
# 708 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "by PROF.ELM.$"
# 709 "data/maps/NewBarkTown_Lab/scripts.pory"

# 710 "data/maps/NewBarkTown_Lab/scripts.pory"
@THEFT================================================================================
# 711 "data/maps/NewBarkTown_Lab/scripts.pory"

# 712 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft1:
# 713 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: {PLAYER}, this is terrible…\p"
# 714 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, yes, what was MR. POKéMON's\n"
# 715 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "big discovery?$"
# 716 "data/maps/NewBarkTown_Lab/scripts.pory"

# 717 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft2:
# 718 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} handed the MYSTERY EGG\n"
# 719 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to PROF.ELM.$"
# 720 "data/maps/NewBarkTown_Lab/scripts.pory"

# 721 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft3:
# 722 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: This?$"
# 723 "data/maps/NewBarkTown_Lab/scripts.pory"

# 724 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft4:
# 725 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Is it a POKéMON EGG?\p"
# 726 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If it is, it is a great\n"
# 727 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "discovery!\p"
# 728 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: What?!?\p"
# 729 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "PROF.OAK gave you a POKéDEX?\p"
# 730 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, is that true?\n"
# 731 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Th-that's incredible!\p"
# 732 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He is superb at seeing the\n"
# 733 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "potential of people as trainers.\p"
# 734 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wow, {PLAYER}. You may have what\n"
# 735 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it takes to become the CHAMPION.\p"
# 736 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You seem to be getting on\n"
# 737 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "great with POKéMON too.\p"
# 738 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should take the POKéMON\n"
# 739 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "GYM challenge.\p"
# 740 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The closest GYM would be the\n"
# 741 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "one in VIOLET CITY.\p"
# 742 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…{PLAYER}. The road to the\n"
# 743 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "championship will be a long one.\p"
# 744 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Before you leave, make sure\n"
# 745 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that you talk to your mom.$"
# 746 "data/maps/NewBarkTown_Lab/scripts.pory"

# 747 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmStudyingEgg:
# 748 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: Don't give up!\n"
# 749 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll call if I learn anything\l"
# 750 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about that EGG!$"
# 751 "data/maps/NewBarkTown_Lab/scripts.pory"

# 752 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAideHasEgg:
# 753 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: {PLAYER}? Didn't you meet\n"
# 754 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my assistant?\p"
# 755 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He should have met you with\n"
# 756 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the EGG at VIOLET CITY's\p"
# 757 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "POKéMON CENTER.\p"
# 758 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You must have just missed him.\n"
# 759 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Try to catch him there.$"
# 760 "data/maps/NewBarkTown_Lab/scripts.pory"

# 761 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWaitingEggHatch:
# 762 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: Hey, has that EGG changed\n"
# 763 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "any?$"
# 764 "data/maps/NewBarkTown_Lab/scripts.pory"

# 765 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmThoughtEggHatched:
# 766 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}? I thought the EGG\n"
# 767 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "hatched.\p"
# 768 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Where is the POKéMON?$"
# 769 "data/maps/NewBarkTown_Lab/scripts.pory"

# 770 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShowTogepi1:
# 771 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: {PLAYER}, you look great!$"
# 772 "data/maps/NewBarkTown_Lab/scripts.pory"

# 773 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShowTogepi2:
# 774 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What? That POKéMON!?!$"
# 775 "data/maps/NewBarkTown_Lab/scripts.pory"

# 776 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShowTogepi3:
# 777 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The EGG hatched! So, POKéMON\n"
# 778 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "are born from EGGS…\p"
# 779 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "No, perhaps not all POKéMON\n"
# 780 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "are.\p"
# 781 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wow, there's still a lot of\n"
# 782 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "research to be done.$"
# 783 "data/maps/NewBarkTown_Lab/scripts.pory"

# 784 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveEverstone1:
# 785 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks, {PLAYER}! You're helping\n"
# 786 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "unravel POKéMON mysteries for us!\p"
# 787 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I want you to have this as a\n"
# 788 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "token of our appreciation.$"
# 789 "data/maps/NewBarkTown_Lab/scripts.pory"

# 790 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveEverstone2:
# 791 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That's an EVERSTONE.\p"
# 792 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Some species of POKéMON evolve\n"
# 793 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "when they grow to certain levels.\p"
# 794 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A POKéMON holding the EVERSTONE\n"
# 795 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "won't evolve.\p"
# 796 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Give it to a POKéMON you don't\n"
# 797 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "want to evolve.$"
# 798 "data/maps/NewBarkTown_Lab/scripts.pory"

# 799 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmCallYou:
# 800 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: {PLAYER}, I'll call you if\n"
# 801 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "anything comes up.$"
# 802 "data/maps/NewBarkTown_Lab/scripts.pory"

# 803 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAfterTheft:
# 804 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen POKéMON.\p"
# 805 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 806 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a POKéMON raised by a\n"
# 807 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 808 "data/maps/NewBarkTown_Lab/scripts.pory"

# 809 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall1:
# 810 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: Hi, {PLAYER}!\p"
# 811 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks to you, my research is\n"
# 812 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going great!\p"
# 813 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take this as a token of my\n"
# 814 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "appreciation.$"
# 815 "data/maps/NewBarkTown_Lab/scripts.pory"

# 816 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall2:
# 817 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The MASTER BALL is the best!\p"
# 818 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the ultimate BALL! It'll\n"
# 819 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "catch any POKéMON without fail.\p"
# 820 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's given only to recognized\n"
# 821 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "POKéMON researchers.\p"
# 822 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I think you can make much better\n"
# 823 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "use of it than I can, {PLAYER}!$"
# 824 "data/maps/NewBarkTown_Lab/scripts.pory"

# 825 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoGirls:
# 826 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "By the way...\n"
# 827 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A group of beautiful KIMONO\l"
# 828 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "GIRLS were looking for you.\p"
# 829 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They told me they are\n"
# 830 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "waiting for you at the\l" 
# 831 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ECRUTEAK DANCE THEATER.\p"
# 832 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I know you've gone through many\n"
# 833 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "things since that EGG got you\l"
# 834 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "involved in all this...\p"
# 835 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I hope you'll carry through it.$"
# 836 "data/maps/NewBarkTown_Lab/scripts.pory"

# 837 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoWaiting:
# 838 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "PROF. ELM: The KIMONO\n"
# 839 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "GIRLS are waiting for you at\l"
# 840 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the ECRUTEAK DANCE THEATER.$"
# 841 "data/maps/NewBarkTown_Lab/scripts.pory"

# 842 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_League:
# 843 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "PROF. ELM: Hahaha...\n"
# 844 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Good job!\p"
# 845 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That rare Egg has brought you\n"
# 846 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a lot of trouble, huh?\p"
# 847 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The KIMONO GIRLS said something\n"
# 848 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about me?\p"
# 849 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have nothing to do with it.\p"
# 850 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You made your decision and went\n"
# 851 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "through with it.\p"
# 852 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Having done so much, you should\n"
# 853 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "be able to face the League now!\p"
# 854 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should head for Indigo\n"
# 855 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Plateau!\p"
# 856 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Do you know how to get there?\n"
# 857 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Follow ROUTE 27 to ROUTE 26.\p"
# 858 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Once there, go straight north!$"
# 859 "data/maps/NewBarkTown_Lab/scripts.pory"

# 860 "data/maps/NewBarkTown_Lab/scripts.pory"

# 861 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket1:
# 862 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "ELM: {PLAYER}! There you are!\p"
# 863 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I called because I have\n"
# 864 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "something for you.\p"
# 865 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "See? It's an S.S.TICKET.\p"
# 866 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can catch POKéMON in\n"
# 867 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "KANTO.$"
# 868 "data/maps/NewBarkTown_Lab/scripts.pory"

# 869 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket2:
# 870 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The ship departs from OLIVINE\n"
# 871 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "CITY.\p"
# 872 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But you knew that already,\n"
# 873 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}.\p"
# 874 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "After all, you've traveled all\n"
# 875 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "over with your POKéMON.\p"
# 876 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Give my regards to PROF.OAK in\n"
# 877 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "KANTO!$"
# 878 "data/maps/NewBarkTown_Lab/scripts.pory"

# 879 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_LabMonEgg:
# 880 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the POKéMON EGG being\n"
# 881 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "studied by PROF.ELM.$"
# 882 "data/maps/NewBarkTown_Lab/scripts.pory"

# 883 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGivePotion:
# 884 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, I want you to have\n"
# 885 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "this for your errand.$"
# 886 "data/maps/NewBarkTown_Lab/scripts.pory"

# 887 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAlwaysBusy:
# 888 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There are only three of us, so\n"
# 889 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "we're always busy.$"
# 890 "data/maps/NewBarkTown_Lab/scripts.pory"

# 891 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideSave:
# 892 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Don't forget to save your game\n"
# 893 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "regularly!\p"
# 894 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Press the START button, then\n"
# 895 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "SAVE the game!$"
# 896 "data/maps/NewBarkTown_Lab/scripts.pory"

# 897 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideTheftTestimony:
# 898 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There was a loud noise\n"
# 899 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "outside…\p"
# 900 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When we went to look,\n"
# 901 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "someone stole a POKéMON.\p"
# 902 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's unbelievable that anyone\n"
# 903 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "would do that!\p"
# 904 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen POKéMON.\p"
# 905 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 906 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a POKéMON raised by a\n"
# 907 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 908 "data/maps/NewBarkTown_Lab/scripts.pory"

# 909 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGiveBalls:
# 910 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 911 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use these on your POKéDEX\n"
# 912 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "quest!$"
# 913 "data/maps/NewBarkTown_Lab/scripts.pory"

# 914 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideExplainBalls:
# 915 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To add to your POKéDEX, you\n"
# 916 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "have to catch POKéMON.\p"
# 917 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Throw POKé BALLS at wild\n"
# 918 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "POKéMON to get them.$"
# 919 "data/maps/NewBarkTown_Lab/scripts.pory"

# 920 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer1:
# 921 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I heard a POKéMON was stolen\n"
# 922 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "here…\p"
# 923 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I was just getting some\n"
# 924 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "information from PROF.ELM.\p"
# 925 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Apparently, it was a young\n"
# 926 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "male with long, red hair…\p"
# 927 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What?\p"
# 928 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You battled a trainer like\n"
# 929 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that?\p"
# 930 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Did you happen to get his\n"
# 931 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "name?$"
# 932 "data/maps/NewBarkTown_Lab/scripts.pory"

# 933 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer2:
# 934 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "OK! So SILVER was his name.\p"
# 935 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 936 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 937 "data/maps/NewBarkTown_Lab/scripts.pory"

# 938 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer3:
# 939 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "OK! So {RIVAL} was his name.\p"
# 940 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 941 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 942 "data/maps/NewBarkTown_Lab/scripts.pory"

# 943 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_OfficerNo:
# 944 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Surely you got his name?!$"
# 945 "data/maps/NewBarkTown_Lab/scripts.pory"

# 946 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Elm_CallMe:
# 947 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah, {PLAYER}!\p"
# 948 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "How's your POKéDEX coming along?\n"
# 949 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm busy now, but call me sometime\l"
# 950 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and I can check your progress!$"
