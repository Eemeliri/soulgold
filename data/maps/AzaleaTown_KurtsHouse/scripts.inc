# 1 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 2 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 3 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_MapScripts::
# 4 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_KurtsHouse_OnFrame
# 5 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_KurtsHouse_OnTransition
# 6 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.byte 0
# 7 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 8 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_OnTransition::
# 9 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup
# 10 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 11 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 12 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_OnFrame::
# 13 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	map_script_2 VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWell
# 14 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.2byte 0
# 15 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 16 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtBefore::
# 17 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 18 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 19 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtMakingBallsMustWait, MSGBOX_DEFAULT
# 20 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 21 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_PlayerMove
# 22 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
# 23 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 24 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_EXIT
# 25 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
# 26 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_KURT_1
# 27 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
# 28 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_AZALEA_TOWN_STATE, 2
# 29 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 30 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 31 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 32 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_PlayerMove::
# 33 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_KurtsHouse_Movement_Player
# 34 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 35 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
# 36 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 37 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_EXIT
# 38 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
# 39 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_KURT_1
# 40 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
# 41 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 42 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 43 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 44 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl::
# 45 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 46 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 47 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_unset FLAG_HIDE_KURT_2, AzaleaTown_KurtsHouse_EventScript_Girl2
# 48 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_set FLAG_HIDE_KURT_1, AzaleaTown_KurtsHouse_EventScript_Girl3
# 49 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_DEFAULT
# 50 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 51 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 52 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 53 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl2::
# 54 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_Girl4
# 55 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 4, AzaleaTown_KurtsHouse_EventScript_Girl4
# 56 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_KurtsHouse_EventScript_Girl4
# 57 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_KurtsHouse_EventScript_Girl4
# 58 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_Girl5
# 59 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_Girl5
# 60 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 61 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterDad, MSGBOX_DEFAULT
# 62 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 63 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 64 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 65 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 66 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl3::
# 67 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterLonely, MSGBOX_DEFAULT
# 68 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 69 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 70 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 71 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 72 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl4::
# 73 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterSlowpokeBack, MSGBOX_DEFAULT
# 74 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 75 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 76 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end	
# 77 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 78 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl5::
# 79 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterSound, MSGBOX_DEFAULT
# 80 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 81 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 82 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end	
# 83 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 84 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup::
# 85 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setobjectmovementtype LOCALID_AZALEA_TOWN_KURT, MOVEMENT_TYPE_FACE_DOWN
# 86 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 87 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 88 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_ReturnFromWell::
# 89 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 90 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 91 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtHonoredToMakeBalls, MSGBOX_DEFAULT
# 92 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FAST_BALL
# 93 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_DAILY_KURT_FREE_BALLS
# 94 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 95 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtMakesBallsDaily
# 96 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 97 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 98 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_AZALEA_TOWN_STATE, 4
# 99 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 100 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 101 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 102 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall::
# 103 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_GS_BALL
# 104 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, AzaleaTown_KurtsHouse_EventScript_KurtGsBall
# 105 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 106 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 107 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt::
# 108 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 109 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 110 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_KurtGsBall2
# 111 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_KurtGsBall3
# 112 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_unset FLAG_CAUGHT_CELEBI, AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall
# 113 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtDaily
# 114 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 115 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	AzaleaTown_KurtsHouse_EventScript_Kurt2::
# 116 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		multichoice 20, 0, MULTI_KURT_BALLS, FALSE
# 117 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		switch VAR_RESULT
# 118 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 0, AzaleaTown_KurtsHouse_EventScript_Kurt_Love
# 119 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 1, AzaleaTown_KurtsHouse_EventScript_Kurt_Lure
# 120 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 2, AzaleaTown_KurtsHouse_EventScript_Kurt_Friend
# 121 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 3, AzaleaTown_KurtsHouse_EventScript_Kurt_Heavy
# 122 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 4, AzaleaTown_KurtsHouse_EventScript_Kurt_Moon
# 123 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 5, AzaleaTown_KurtsHouse_EventScript_Kurt_Fast
# 124 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 6, AzaleaTown_KurtsHouse_EventScript_Kurt_Level
# 125 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case 7, AzaleaTown_KurtsHouse_EventScript_KurtCancel
# 126 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		case MULTI_B_PRESSED, AzaleaTown_KurtsHouse_EventScript_KurtCancel
# 127 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
		closemessage
# 128 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 129 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt_Love::
# 130 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 131 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_PECHA_BERRY
# 132 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_PECHA_BERRY, 5
# 133 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
# 134 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 135 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 136 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 137 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 138 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 139 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 140 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 141 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 142 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 143 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 144 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 145 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LOVE_BALL, 5
# 146 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_PECHA_BERRY, 5
# 147 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 148 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 149 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 150 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 151 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 152 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 153 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt_Lure::
# 154 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 155 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_RAWST_BERRY
# 156 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_RAWST_BERRY, 5
# 157 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
# 158 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 159 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 160 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 161 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 162 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 163 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 164 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 165 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 166 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 167 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 168 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 169 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LURE_BALL, 5
# 170 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_RAWST_BERRY, 5
# 171 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 172 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 173 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 174 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 175 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 176 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 177 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt_Friend::
# 178 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 179 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_CHERI_BERRY
# 180 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_CHERI_BERRY, 5
# 181 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
# 182 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 183 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 184 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 185 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 186 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 187 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 188 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 189 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 190 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 191 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 192 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 193 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FRIEND_BALL, 5
# 194 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_CHERI_BERRY, 5
# 195 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 196 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 197 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 198 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 199 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 200 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 201 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt_Heavy::
# 202 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 203 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_ORAN_BERRY
# 204 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_ORAN_BERRY, 5
# 205 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
# 206 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 207 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 208 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 209 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 210 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 211 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 212 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 213 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 214 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 215 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 216 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 217 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_HEAVY_BALL, 5
# 218 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_ORAN_BERRY, 5
# 219 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 220 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 221 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 222 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 223 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 224 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 225 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt_Moon::
# 226 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 227 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_CHESTO_BERRY
# 228 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_CHESTO_BERRY, 5
# 229 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
# 230 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 231 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 232 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 233 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 234 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 235 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 236 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 237 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 238 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 239 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 240 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 241 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_MOON_BALL, 5
# 242 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_CHESTO_BERRY, 5
# 243 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 244 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 245 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 246 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 247 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 248 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 249 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt_Fast::
# 250 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 251 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_ASPEAR_BERRY
# 252 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_ASPEAR_BERRY, 5
# 253 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
# 254 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 255 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 256 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 257 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 258 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 259 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 260 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 261 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 262 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 263 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 264 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 265 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FAST_BALL, 5
# 266 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_ASPEAR_BERRY, 5
# 267 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 268 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 269 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 270 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 271 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 272 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 273 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt_Level::
# 274 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 275 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_PERSIM_BERRY
# 276 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_PERSIM_BERRY, 5
# 277 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
# 278 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 279 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 280 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 281 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 282 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 283 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 284 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 285 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 286 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 287 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 288 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 289 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LEVEL_BALL, 5
# 290 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_PERSIM_BERRY, 5
# 291 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 292 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 293 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 294 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 295 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 296 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 297 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 298 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_DontHaveBerry::
# 299 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtThatsALetdown, MSGBOX_DEFAULT
# 300 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 301 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto AzaleaTown_KurtsHouse_EventScript_Kurt2
# 302 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 303 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 304 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	
# 305 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtCancel::
# 306 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 307 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 308 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 309 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 310 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 311 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtGsBall::
# 312 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtWhatIsThat, MSGBOX_DEFAULT
# 313 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 314 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_GS_BALL
# 315 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 316 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 317 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 318 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 319 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 320 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 321 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 322 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtThisBallStartedToShake, MSGBOX_DEFAULT
# 323 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 324 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_M_PETAL_DANCE
# 325 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitse
# 326 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_PIN
# 327 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, Common_Movement_ExclamationMark
# 328 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
# 329 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay 60
# 330 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitse
# 331 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_M_PETAL_DANCE
# 332 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitse
# 333 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Look_Around
# 334 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTownKurt_Movement_Look_Around
# 335 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 336 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 337 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtGsBall2::
# 338 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_Kurt_Whatwasthat, MSGBOX_DEFAULT
# 339 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_AZALEA_TOWN_STATE, 8
# 340 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 341 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 342 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 343 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 344 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtGsBall3::
# 345 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_Forest, MSGBOX_DEFAULT
# 346 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 347 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay 30
# 348 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_BallAnyway, MSGBOX_DEFAULT
# 349 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 350 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtDaily
# 351 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 352 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 353 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_BallAnyway:
# 354 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Anyway, can I make you some Balls?$"
# 355 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 356 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_OakPhoto::
# 357 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_OakPhoto, MSGBOX_SIGN
# 358 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 359 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 360 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 361 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_CelebiStatue::
# 362 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_CelebiStatue, MSGBOX_SIGN
# 363 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 364 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 365 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 366 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTownKurt_Movement_Look_Around:
# 367 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_left
# 368 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 369 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_right
# 370 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 371 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_up
# 372 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 373 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_down
# 374 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 375 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_left
# 376 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 377 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 378 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTownKurt_Movement_Making_Ball:
# 379 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_up
# 380 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_in_place_fast_up
# 381 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 382 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_in_place_fast_up
# 383 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 384 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_in_place_fast_up
# 385 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 386 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 387 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_Movement_Player:
# 388 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_right
# 389 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock_facing_direction
# 390 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_left
# 391 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	unlock_facing_direction
# 392 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 393 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 394 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_Movement_KurtWalkDown:
# 395 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 396 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 397 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 398 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 399 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 400 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 401 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 402 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 403 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtGetStarted:
# 404 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Kurt: I'll get started right now!$"
# 405 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 406 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtMakingBallsMustWait:
# 407 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Hm? Who are you?\p"
# 408 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{PLAYER}, eh? You want me to make\n"
# 409 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "some Balls?\p"
# 410 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Sorry, but that'll have to wait.\p"
# 411 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Do you know Team Rocket?\n"
# 412 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ah, don't worry.\p"
# 413 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I'll tell you anyhow.\p"
# 414 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Team Rocket's an evil gang that\n"
# 415 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "uses Pokémon for their dirty work.\p"
# 416 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "They're supposed to have disbanded\n"
# 417 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "three years ago.\p"
# 418 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Anyway, they're at the Well,\n"
# 419 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "cutting off Slowpoketails to sell!\p"
# 420 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "So I'm going to go give them a\n"
# 421 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "lesson in pain!\p"
# 422 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Hang on, Slowpoke! Old Kurt\n"
# 423 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "is on his way!$"
# 424 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 425 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtHonoredToMakeBalls:
# 426 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Kurt: Hi, {PLAYER}!\p"
# 427 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "You handled yourself like a\n"
# 428 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "real hero at the Well.\p"
# 429 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I like your style!\p"
# 430 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I would be honored to make\n"
# 431 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Balls for a trainer like you.\p"
# 432 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "This is all I have now, \n"
# 433 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "but take it.$"
# 434 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 435 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtBallsFromApricorns:
# 436 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Kurt: I make Balls from Berries.\p"
# 437 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Collect them from trees and bring\n"
# 438 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "'em to me in batches of 5.\p"
# 439 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I'll make Balls out of them.$"
# 440 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 441 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtAskYouHaveAnApricorn:
# 442 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Kurt: You have 5 Berries for me?\p"
# 443 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Fine! I'll turn them into Balls.$"
# 444 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 445 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtThatsALetdown:
# 446 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Kurt: I don't see 5 {STR_VAR_1}s!$"
# 447 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 448 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtJustFinishedYourBall:
# 449 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Kurt: Ah, {PLAYER}! \p"
# 450 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I just finished your Ball. Here!$"
# 451 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 452 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtTurnedOutGreat:
# 453 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Kurt: That turned out great.\p"
# 454 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Try catching Pokémon with it.$"
# 455 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 456 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtWhatIsThat:
# 457 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Wh-what is that?\p"
# 458 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I've never seen one before.\p"
# 459 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It looks a like a Poké Ball, but\n"
# 460 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "it appears to be something else.\p"
# 461 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Let me check it for you.$"
# 462 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 463 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtImCheckingItNow:
# 464 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I'm checking it now.$"
# 465 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 466 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtAhHaISee:
# 467 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ah-ha! I see! So…$"
# 468 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 469 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtThisBallStartedToShake:
# 470 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{PLAYER}!\p"
# 471 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "This Ball started to shake\n"
# 472 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "while I was checking it.\p"
# 473 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "There must be something to this!$"
# 474 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 475 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_Kurt_Whatwasthat:
# 476 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "What was that sound?!\p"
# 477 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Let's go outside to investigate!$"
# 478 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 479 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterSlowpokeGone:
# 480 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "The Slowpoke are gone… \n"
# 481 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Were they taken away by bad people?$"
# 482 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 483 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterLonely:
# 484 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Grandpa's gone… I'm so lonely…$"
# 485 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 486 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterSlowpokeBack:
# 487 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "The Slowpoke my dad gave me came back!\p"
# 488 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Its Tail is growing back too!$"
# 489 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 490 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterDad:
# 491 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Dad works at Silph where\n"
# 492 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "he studies Poké Balls.\p"
# 493 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I have to stay home\n"
# 494 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "with Grandpa and Slowpoke.$"
# 495 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 496 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterHelp:
# 497 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I get to help Grandpa now!\p"
# 498 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "We'll make good Balls\n"
# 499 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "for you, so please wait!$"
# 500 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 501 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterFun:
# 502 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It's fun to make Balls!$"
# 503 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 504 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterSound:
# 505 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Did that sound come from\n"
# 506 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ilex Forest????$"
# 507 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 508 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_Forest:
# 509 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Did you check Ilex Forest yet?\n"
# 510 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It sounds very restless.$"
# 511 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 512 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_Slowpoke:
# 513 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Slowpoke: … Yawn?$"
# 514 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 515 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_OakPhoto:
# 516 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "…A young Prof. Oak?$"
# 517 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 518 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_CelebiStatue:
# 519 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It's a statue of the forest's\n"
# 520 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "protector.$"

KurtMakesBallsDaily::
# 524 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtMakesBallsDaily_Text_0
# 526 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
	return


KurtDaily::
# 531 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_set FLAG_DAILY_KURT_FREE_BALLS, KurtDaily_2
# 537 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtDaily_Text_1
# 539 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	compare VAR_KURT_PROFICIENCY, 4
	goto_if_ge KurtDaily_5
# 542 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	random 15
KurtDaily_4:
# 544 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	switch VAR_RESULT
# 545 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 0, KurtDaily_10
# 547 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 1, KurtDaily_11
# 549 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 2, KurtDaily_12
# 551 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 3, KurtDaily_13
# 553 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 4, KurtDaily_14
# 555 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 5, KurtDaily_15
# 557 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 6, KurtDaily_16
# 559 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 7, KurtDaily_17
# 561 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 8, KurtDaily_18
# 563 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 9, KurtDaily_19
# 565 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 10, KurtDaily_20
# 567 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 11, KurtDaily_21
# 569 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 12, KurtDaily_22
# 571 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 13, KurtDaily_23
# 573 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 14, KurtDaily_24
# 575 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 15, KurtDaily_25
KurtDaily_8:
# 584 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_DAILY_KURT_FREE_BALLS
# 585 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	compare VAR_KURT_PROFICIENCY, 255
	goto_if_lt KurtDaily_27
KurtDaily_26:
# 588 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
	end

KurtDaily_2:
# 532 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtDaily_Text_0
# 534 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
	end

KurtDaily_5:
# 540 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	random 16
	goto KurtDaily_4

KurtDaily_10:
# 546 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LUXURY_BALL, 5
	goto KurtDaily_8

KurtDaily_11:
# 548 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LEVEL_BALL, 5
	goto KurtDaily_8

KurtDaily_12:
# 550 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LURE_BALL, 5
	goto KurtDaily_8

KurtDaily_13:
# 552 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_MOON_BALL, 5
	goto KurtDaily_8

KurtDaily_14:
# 554 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FRIEND_BALL, 5
	goto KurtDaily_8

KurtDaily_15:
# 556 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LOVE_BALL, 5
	goto KurtDaily_8

KurtDaily_16:
# 558 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FAST_BALL, 5
	goto KurtDaily_8

KurtDaily_17:
# 560 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_HEAVY_BALL, 5
	goto KurtDaily_8

KurtDaily_18:
# 562 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_DREAM_BALL, 5
	goto KurtDaily_8

KurtDaily_19:
# 564 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_SAFARI_BALL, 5
	goto KurtDaily_8

KurtDaily_20:
# 566 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_SPORT_BALL, 5
	goto KurtDaily_8

KurtDaily_21:
# 568 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_PARK_BALL, 5
	goto KurtDaily_8

KurtDaily_22:
# 570 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_BEAST_BALL, 5
	goto KurtDaily_8

KurtDaily_23:
# 572 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_CHERISH_BALL, 5
	goto KurtDaily_8

KurtDaily_24:
# 574 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_STRANGE_BALL, 5
	goto KurtDaily_8

KurtDaily_25:
# 576 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtDaily_Text_2
# 580 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_MASTER_BALL, 1
# 581 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_KURT_CRAFTED_MASTER_BALL
# 582 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	special Achievement_CheckAll
	goto KurtDaily_8

KurtDaily_27:
# 586 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	addvar VAR_KURT_PROFICIENCY, 1
	goto KurtDaily_26


KurtMakesBallsDaily_Text_0:
# 524 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I will give you any surplus Poké Balls\n"
	.string "I create every day, so stop by!$"

KurtDaily_Text_0:
# 532 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Come back tomorrow when I have crafted\n"
	.string "some more.$"

KurtDaily_Text_1:
# 537 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Here's what I got for you today.\n"
	.string "Stop by tomorrow again for more.$"

KurtDaily_Text_2:
# 576 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "This once is a masterpiece!\p"
	.string "I can hardly believe I managed\n"
	.string "to craft it.$"
