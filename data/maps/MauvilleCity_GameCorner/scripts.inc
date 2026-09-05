# 1 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 2 "data/maps/MauvilleCity_GameCorner/scripts.pory"
.set LOCALID_BOUNCER, 24
# 3 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 4 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_MapScripts::
# 5 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerId_Onframe
# 6 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.byte 0
# 7 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 8 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	@ Game Corner prices
# 9 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_DOUBLE_TEAM_COINS, 1500
# 10 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_PSYCHIC_COINS, 3500
# 11 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_FLAMETHROWER_COINS, 4000
# 12 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_THUNDER_COINS, 4000
# 13 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_ICE_BEAM_COINS, 4000
# 14 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set DOLL_COINS, 1000
# 15 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set OLD_AMBER_COINS, 4000
# 16 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set SUNSTONE_COINS, 2000
# 17 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set MOONSTONE_COINS, 2000
# 18 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set FIRESTONE_COINS, 2000
# 19 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set THUNDERSTONE_COINS, 2000
# 20 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set WATERSTONE_COINS, 2000
# 21 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set LEAFSTONE_COINS, 2000
# 22 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set LINKING_CORD_COINS, 2500
# 23 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set PRISM_SCALE_COINS, 3000
# 24 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 25 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set COINS_PRICE_50,  1000
# 26 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set COINS_PRICE_500, 10000
# 27 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set COINS_PRICE_2000, 35000
# 28 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 29 "data/maps/MauvilleCity_GameCorner/scripts.pory"
TrainerId_Onframe:
# 30 "data/maps/MauvilleCity_GameCorner/scripts.pory"
.if GAME_CORNER_VAR_ID_CHECK != 0
# 31 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	map_script_2 GAME_CORNER_VAR_ID_CHECK, 0, BouncerCheck
# 32 "data/maps/MauvilleCity_GameCorner/scripts.pory"
.endif
# 33 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.2byte 0
# 34 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 35 "data/maps/MauvilleCity_GameCorner/scripts.pory"
BouncerCheck::
# 36 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 37 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	applymovement LOCALID_BOUNCER, Common_Movement_WalkInPlaceFasterLeft
# 38 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmovement 0
# 39 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_PIN
# 40 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	applymovement LOCALID_BOUNCER, Common_Movement_ExclamationMark
# 41 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmovement 0
# 42 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	applymovement LOCALID_BOUNCER, Common_Movement_Delay48
# 43 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmovement 0
# 44 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	applymovement LOCALID_BOUNCER, Movement_Bouncer_Approach
# 45 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmovement 0
# 46 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Bouncer1, MSGBOX_DEFAULT
# 47 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 48 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar GAME_CORNER_VAR_ID_CHECK, 1
# 49 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	applymovement LOCALID_BOUNCER, Movement_Bouncer_Leave
# 50 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmovement 0
# 51 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 52 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 53 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 54 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Movement_Bouncer_Approach:
# 55 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	walk_left
# 56 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	walk_left
# 57 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	step_end
# 58 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 59 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Movement_Bouncer_Leave:
# 60 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	walk_right
# 61 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	walk_right
# 62 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	walk_in_place_faster_left
# 63 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	step_end
# 64 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 65 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Blackjack::
# 66 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 67 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 68 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 69 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_BlackJack, MSGBOX_YESNO
# 70 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 71 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelBJ
# 72 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 73 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special StartBlackJack
# 74 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitstate
# 75 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 76 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 77 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 78 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 79 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 80 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Derby::
# 81 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 82 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 83 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 84 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Derby, MSGBOX_YESNO
# 85 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 86 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelBJ
# 87 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_PEWTER, FALSE
# 88 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special StartDerby
# 89 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitstate
# 90 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 91 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 92 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CheckWinnings::
# 93 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
# 94 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 95 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
# 96 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
# 97 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 98 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins GAME_CORNER_VAR_WINNINGS
# 99 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar GAME_CORNER_VAR_WINNINGS, 0
# 100 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 101 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 102 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 103 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_CancelVF::
# 104 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 105 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_CancelBJ::
# 106 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 107 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_NoWin::
# 108 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 109 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 110 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 111 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Snake::
# 112 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 113 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 114 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 115 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 116 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 25, Onix_Not_Enough
# 117 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 118 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Snake, MSGBOX_YESNO
# 119 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 120 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 121 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 25
# 122 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 123 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 124 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 125 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 126 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_NONE, FALSE
# 127 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special StartSnake
# 128 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitstate
# 129 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 130 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 131 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings
# 132 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 133 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_FlappyBird::
# 134 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 135 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 136 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 137 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 138 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 25, Butterfree_Not_Enough
# 139 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 140 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Bird, MSGBOX_YESNO
# 141 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 142 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 143 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 25
# 144 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 145 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 146 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 147 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 148 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_NONE, FALSE
# 149 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special StartFlappyBird
# 150 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitstate
# 151 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 152 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 153 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings
# 154 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 155 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BlockStacker::
# 156 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 157 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 158 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 159 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 160 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 25, BlockStacker_Not_Enough
# 161 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 162 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_BS, MSGBOX_YESNO
# 163 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 164 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 165 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 25
# 166 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 167 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 168 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 169 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 170 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_CASINO_PLUS_1, FALSE
# 171 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special StartBlockStacker
# 172 "data/maps/MauvilleCity_GameCorner/scripts.pory"
    waitstate
# 173 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 174 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 175 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings
# 176 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 177 "data/maps/MauvilleCity_GameCorner/scripts.pory"
BlockStacker_Not_Enough::
# 178 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox BS_Not_Enough, MSGBOX_DEFAULT
# 179 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 180 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 181 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 182 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Pinball_Not_Enough::
# 183 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox PB_Not_Enough, MSGBOX_DEFAULT
# 184 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 185 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 186 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 187 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Onix_Not_Enough::
# 188 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox Snake_Not_Enough, MSGBOX_DEFAULT
# 189 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 190 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 191 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 192 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Juice_Not_Enough::
# 193 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox Bjuice_Not_Enough, MSGBOX_DEFAULT
# 194 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 195 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 196 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 197 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 198 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Butterfree_Not_Enough::
# 199 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox Bird_Not_Enough, MSGBOX_DEFAULT
# 200 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 201 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 202 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 203 "data/maps/MauvilleCity_GameCorner/scripts.pory"
VF_Not_Enough::
# 204 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox Flip_Not_Enough, MSGBOX_DEFAULT
# 205 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 206 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 207 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 208 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Pachinko::
# 209 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 210 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 211 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 212 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Pachinko, MSGBOX_YESNO
# 213 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 214 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 215 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_ROUTE1, FALSE
# 216 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	callnative PlayPachinko
# 217 "data/maps/MauvilleCity_GameCorner/scripts.pory"
    waitstate
# 218 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 219 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 220 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 221 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 222 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 223 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PinballMeowth::
# 224 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 225 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 226 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 227 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 228 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 25, Pinball_Not_Enough
# 229 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 230 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Pinball_Meowth, MSGBOX_YESNO
# 231 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 232 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 233 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 25
# 234 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 235 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 236 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 237 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 238 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_POKE_CENTER, FALSE
# 239 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	callnative PlayMeowthPinballGame
# 240 "data/maps/MauvilleCity_GameCorner/scripts.pory"
    waitstate
# 241 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 242 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 243 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings
# 244 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 245 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PinballDiglett::
# 246 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 247 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 248 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 249 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 250 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 50, Pinball_Not_Enough
# 251 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 252 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Pinball_Diglett, MSGBOX_YESNO
# 253 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 254 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 255 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 50
# 256 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 257 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 258 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 259 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 260 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_POKE_JUMP, FALSE
# 261 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	callnative PlayDiglettPinballGame
# 262 "data/maps/MauvilleCity_GameCorner/scripts.pory"
    waitstate
# 263 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 264 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 265 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings
# 266 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 267 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PinballSeel::
# 268 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 269 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 270 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 271 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 272 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 25, Pinball_Not_Enough
# 273 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 274 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Pinball_Seel, MSGBOX_YESNO
# 275 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 276 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 277 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 25
# 278 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 279 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 280 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 281 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 282 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_SS_ANNE, FALSE
# 283 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	callnative PlaySeelPinballGame
# 284 "data/maps/MauvilleCity_GameCorner/scripts.pory"
    waitstate
# 285 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 286 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 287 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings
# 288 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 289 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PinballGengar::
# 290 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 291 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 292 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 293 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 294 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 100, Pinball_Not_Enough
# 295 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 296 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Pinball_Gengar, MSGBOX_YESNO
# 297 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 298 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 299 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 100
# 300 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 301 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 302 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 303 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 304 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_POKE_TOWER, FALSE
# 305 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	callnative PlayGengarPinballGame
# 306 "data/maps/MauvilleCity_GameCorner/scripts.pory"
    waitstate
# 307 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 308 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 309 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings
# 310 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 311 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_VoltorbFlip::
# 312 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 313 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 314 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 315 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 316 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 50, VF_Not_Enough
# 317 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 318 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_VF, MSGBOX_YESNO
# 319 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 320 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 321 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 50
# 322 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 323 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 324 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 325 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 326 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_OAK, FALSE
# 327 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar GAME_CORNER_VAR_WINNINGS, 0
# 328 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special Special_ViewVoltorbFlip
# 329 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitstate
# 330 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, 0, VF_Come_Again
# 331 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, 1, VF_Go_On
# 332 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 333 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 334 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 335 "data/maps/MauvilleCity_GameCorner/scripts.pory"
VF_Come_Again::
# 336 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 337 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 338 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox VF_Come_Again_Text, MSGBOX_DEFAULT
# 339 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar GAME_CORNER_VAR_WINNINGS, 0
# 340 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 341 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 342 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 343 "data/maps/MauvilleCity_GameCorner/scripts.pory"
VF_Go_On::
# 344 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 345 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
# 346 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_VF_Keep_Going, MSGBOX_YESNO
# 347 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 348 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, VF_Cash_Out
# 349 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto VF_Loop
# 350 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 351 "data/maps/MauvilleCity_GameCorner/scripts.pory"
VF_Loop::
# 352 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 353 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special Special_ViewVoltorbFlip
# 354 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitstate
# 355 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, 0, VF_Come_Again
# 356 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, 1, VF_Go_On
# 357 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 358 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 359 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 360 "data/maps/MauvilleCity_GameCorner/scripts.pory"
VF_Cash_Out::
# 361 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins GAME_CORNER_VAR_WINNINGS
# 362 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar GAME_CORNER_VAR_WINNINGS, 0
# 363 "data/maps/MauvilleCity_GameCorner/scripts.pory"
.if FLIP_VAR_LEVEL != 0
# 364 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar FLIP_VAR_LEVEL, 0
# 365 "data/maps/MauvilleCity_GameCorner/scripts.pory"
.endif
# 366 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 367 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 368 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 369 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 370 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 371 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 372 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 373 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 374 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 375 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Gacha_Basic::
# 376 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 377 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 378 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 379 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 1
# 380 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call MauvilleCity_GameCorner_EventScript_GachaCommon
# 381 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 382 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 383 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 384 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GachaCommon::
# 385 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_RG_CINNABAR, FALSE
# 386 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special StartGacha
# 387 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitstate
# 388 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	savebgm MUS_DUMMY
# 389 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	fadedefaultbgm
# 390 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MauvilleCity_GameCorner_EventScript_RecieveGachaMonParty
# 391 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MauvilleCity_GameCorner_EventScript_RecieveGachaMonPC
# 392 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GachaEnd:
# 393 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	return
# 394 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 395 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_RecieveGachaMonParty:
# 396 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 397 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_GachaEnd
# 398 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 399 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 400 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_GachaEnd
# 401 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 402 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_RecieveGachaMonPC:
# 403 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 404 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_TransferGachaMonToPC
# 405 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 406 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TransferGachaMonToPC:
# 407 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_TransferredToPC
# 408 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_GachaEnd
# 409 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 410 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Gacha_Great::
# 411 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 412 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 413 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 414 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 2
# 415 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call MauvilleCity_GameCorner_EventScript_GachaCommon
# 416 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 417 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 418 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 419 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Gacha_Ultra::
# 420 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 421 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 422 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 423 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 3
# 424 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call MauvilleCity_GameCorner_EventScript_GachaCommon
# 425 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 426 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 427 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 428 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Gacha_Master::
# 429 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 430 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 431 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 432 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 4
# 433 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call MauvilleCity_GameCorner_EventScript_GachaCommon
# 434 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 435 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 436 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 437 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CoinsClerk::
# 438 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 439 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 440 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner, MSGBOX_DEFAULT
# 441 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 442 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
# 443 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WereYouLookingForCoins
# 444 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 445 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showmoneybox 0, 0
# 446 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 6
# 447 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50
# 448 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 449 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50::
# 450 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 0, FALSE
# 451 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 452 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
# 453 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
# 454 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_Buy2000Coins
# 455 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
# 456 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 457 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 458 "data/maps/MauvilleCity_GameCorner/scripts.pory"
@ Unused
# 459 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault500::
# 460 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 1, FALSE
# 461 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 462 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
# 463 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
# 464 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_Buy2000Coins
# 465 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
# 466 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 467 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 468 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Buy50Coins::
# 469 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_1
# 470 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 50), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
# 471 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkmoney COINS_PRICE_50
# 472 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
# 473 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins 50
# 474 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removemoney COINS_PRICE_50
# 475 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatemoneybox
# 476 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 6
# 477 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 478 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
# 479 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 480 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 481 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 482 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 483 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 484 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Buy500Coins::
# 485 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_1
# 486 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 500), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
# 487 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkmoney COINS_PRICE_500
# 488 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
# 489 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins 500
# 490 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removemoney COINS_PRICE_500
# 491 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatemoneybox
# 492 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 6
# 493 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 494 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
# 495 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 496 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 497 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 498 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 499 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 500 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Buy2000Coins::
# 501 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_1
# 502 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 2000), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
# 503 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkmoney COINS_PRICE_2000
# 504 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
# 505 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins 2000
# 506 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removemoney COINS_PRICE_2000
# 507 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatemoneybox
# 508 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 6
# 509 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 510 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
# 511 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 512 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 513 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 514 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 515 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 516 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NeedCoinCase::
# 517 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins, MSGBOX_DEFAULT
# 518 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 519 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 520 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 521 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughMoney::
# 522 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DontHaveEnoughMoney, MSGBOX_DEFAULT
# 523 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 524 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 525 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 526 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 527 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 528 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CancelBuyCoins::
# 529 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DontNeedCoinsThen, MSGBOX_DEFAULT
# 530 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 531 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 532 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 533 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 534 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 535 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForCoins::
# 536 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CoinCaseIsFull, MSGBOX_DEFAULT
# 537 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 538 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 539 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 540 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 541 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 542 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PrizeCornerDolls::
# 543 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 544 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 545 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
# 546 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 547 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage
# 548 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 549 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 550 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 551 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage::
# 552 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 553 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 554 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 0
# 555 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 556 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize
# 557 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 558 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize::
# 559 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 560 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 561 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize
# 562 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 563 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseDollPrize::
# 564 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoice 12, 0, MULTI_GAME_CORNER_DOLLS, FALSE
# 565 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 566 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_TreeckoDoll
# 567 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_TorchicDoll
# 568 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_MudkipDoll
# 569 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_CancelDollSelect
# 570 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelDollSelect
# 571 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 572 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 573 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TreeckoDoll::
# 574 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 1
# 575 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_1, DECOR_TREECKO_DOLL
# 576 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize
# 577 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 578 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TorchicDoll::
# 579 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 2
# 580 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_1, DECOR_TORCHIC_DOLL
# 581 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize
# 582 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 583 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_MudkipDoll::
# 584 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 3
# 585 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_1, DECOR_MUDKIP_DOLL
# 586 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize
# 587 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 588 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ConfirmDollPrize::
# 589 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsX, MSGBOX_YESNO
# 590 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelDollSelect
# 591 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_TEMP_1
# 592 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll
# 593 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_BuyTorchicDoll
# 594 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_BuyMudkipDoll
# 595 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 596 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 597 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll::
# 598 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 599 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
# 600 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
# 601 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TREECKO_DOLL
# 602 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
# 603 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins DOLL_COINS
# 604 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	adddecoration DECOR_TREECKO_DOLL
# 605 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 606 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 607 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
# 608 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 609 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 610 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 611 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTorchicDoll::
# 612 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 613 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
# 614 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
# 615 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TORCHIC_DOLL
# 616 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
# 617 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins DOLL_COINS
# 618 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	adddecoration DECOR_TORCHIC_DOLL
# 619 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 620 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 621 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
# 622 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 623 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 624 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 625 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyMudkipDoll::
# 626 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 627 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
# 628 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
# 629 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_MUDKIP_DOLL
# 630 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
# 631 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins DOLL_COINS
# 632 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	adddecoration DECOR_MUDKIP_DOLL
# 633 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 634 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 635 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
# 636 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 637 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 638 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 639 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll::
# 640 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
# 641 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 642 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 643 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 644 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForDoll::
# 645 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_NoRoomForDecor
# 646 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 647 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 648 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 649 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CancelDollSelect::
# 650 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
# 651 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 652 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 653 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 654 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 655 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PrizeCornerTMs::
# 656 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 657 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 658 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
# 659 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 660 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage
# 661 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 662 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 663 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 664 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PrizeCornerNew::
# 665 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 666 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 667 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
# 668 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 669 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage
# 670 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 671 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 672 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 673 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PrizeCornerNew2::
# 674 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 675 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 676 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
# 677 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 678 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage2
# 679 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 680 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 681 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 682 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage::
# 683 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 684 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 685 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 0
# 686 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 687 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize
# 688 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 689 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage::
# 690 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 691 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 692 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 0
# 693 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 694 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize
# 695 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 696 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage2::
# 697 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 698 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 699 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 0
# 700 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 701 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2
# 702 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 703 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize::
# 704 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 705 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 706 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize
# 707 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 708 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize::
# 709 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 710 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 711 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize
# 712 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 713 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2::
# 714 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 715 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 716 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2
# 717 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 718 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseTMPrize::
# 719 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoice 12, 0, MULTI_GAME_CORNER_TMS, FALSE
# 720 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 721 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_TMDoubleTeam
# 722 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_TMPsychic
# 723 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_TMFlamethrower
# 724 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_TMThunder
# 725 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 4, MauvilleCity_GameCorner_EventScript_TMIceBeam
# 726 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 5, MauvilleCity_GameCorner_EventScript_CancelTMSelect
# 727 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
# 728 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 729 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 730 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 731 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 732 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_LinkingCord::
# 733 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 8
# 734 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_LINKING_CORD
# 735 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_LINKING_CORD
# 736 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 737 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 738 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PrismScale::
# 739 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 9
# 740 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_PRISM_SCALE
# 741 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_PRISM_SCALE
# 742 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 743 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 744 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_OldAmber::
# 745 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 1
# 746 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_OLD_AMBER
# 747 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_OLD_AMBER
# 748 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 749 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 750 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SunStone::
# 751 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 2
# 752 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_SUN_STONE
# 753 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_SUN_STONE
# 754 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 755 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 756 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_MoonStone::
# 757 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 3
# 758 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_MOON_STONE
# 759 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_MOON_STONE
# 760 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 761 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 762 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ThunderStone::
# 763 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 5
# 764 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_THUNDER_STONE
# 765 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_THUNDER_STONE
# 766 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 767 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 768 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_WaterStone::
# 769 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 6
# 770 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_WATER_STONE
# 771 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_WATER_STONE
# 772 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 773 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 774 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_LeafStone::
# 775 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 7
# 776 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_LEAF_STONE
# 777 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_LEAF_STONE
# 778 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 779 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 780 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_FireStone::
# 781 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 4
# 782 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_FIRE_STONE
# 783 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_FIRE_STONE
# 784 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
# 785 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 786 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ConfirmNewPrize::
# 787 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	//special BufferItemName
# 788 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheNewX, MSGBOX_YESNO
# 789 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
# 790 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_TEMP_1
# 791 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_BuyOldAmber
# 792 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_BuySunStone
# 793 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_BuyMoonStone
# 794 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 4, MauvilleCity_GameCorner_EventScript_BuyFireStone
# 795 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 5, MauvilleCity_GameCorner_EventScript_BuyThunderStone
# 796 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 6, MauvilleCity_GameCorner_EventScript_BuyWaterStone
# 797 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 7, MauvilleCity_GameCorner_EventScript_BuyLeafStone
# 798 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 8, MauvilleCity_GameCorner_EventScript_BuyLinkingCord
# 799 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 9, MauvilleCity_GameCorner_EventScript_BuyPrismScale
# 800 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 801 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 802 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 803 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyPrismScale::
# 804 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 805 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, PRISM_SCALE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
# 806 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_set FLAG_BOUGHT_EXP_JAR, MauvilleCity_GameCorner_EventScript_NoRoomForAnother
# 807 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_PRISM_SCALE
# 808 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
# 809 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins PRISM_SCALE_COINS
# 810 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_PRISM_SCALE
# 811 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_BOUGHT_EXP_JAR
# 812 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 813 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 814 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 815 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 816 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 817 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 818 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyLinkingCord::
# 819 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 820 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, LINKING_CORD_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
# 821 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_LINKING_CORD
# 822 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
# 823 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins LINKING_CORD_COINS
# 824 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_LINKING_CORD
# 825 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 826 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 827 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 828 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 829 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 830 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 831 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyOldAmber::
# 832 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 833 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, OLD_AMBER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
# 834 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_OLD_AMBER
# 835 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
# 836 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins OLD_AMBER_COINS
# 837 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_OLD_AMBER
# 838 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 839 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 840 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 841 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 842 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 843 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 844 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuySunStone::
# 845 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 846 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, SUNSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
# 847 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_SUN_STONE
# 848 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
# 849 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins SUNSTONE_COINS
# 850 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_SUN_STONE
# 851 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 852 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 853 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 854 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 855 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 856 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 857 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyMoonStone::
# 858 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 859 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, MOONSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
# 860 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_MOON_STONE
# 861 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
# 862 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins MOONSTONE_COINS
# 863 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_MOON_STONE
# 864 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 865 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 866 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 867 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 868 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 869 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 870 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyFireStone::
# 871 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 872 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, FIRESTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
# 873 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_FIRE_STONE
# 874 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
# 875 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins FIRESTONE_COINS
# 876 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_FIRE_STONE
# 877 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 878 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 879 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 880 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
# 881 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 882 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 883 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyThunderStone::
# 884 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 885 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, THUNDERSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
# 886 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_THUNDER_STONE
# 887 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
# 888 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins THUNDERSTONE_COINS
# 889 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_THUNDER_STONE
# 890 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 891 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 892 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 893 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
# 894 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 895 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 896 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyWaterStone::
# 897 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 898 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, WATERSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
# 899 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_WATER_STONE
# 900 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
# 901 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins WATERSTONE_COINS
# 902 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_WATER_STONE
# 903 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 904 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 905 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 906 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
# 907 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 908 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 909 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyLeafStone::
# 910 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 911 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, LEAFSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
# 912 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_LEAF_STONE
# 913 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
# 914 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins LEAFSTONE_COINS
# 915 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_LEAF_STONE
# 916 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 917 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 918 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 919 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
# 920 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 921 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 922 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMDoubleTeam::
# 923 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 1
# 924 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_DOUBLE_TEAM
# 925 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_DOUBLE_TEAM
# 926 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 927 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 928 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMPsychic::
# 929 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 2
# 930 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_PSYCHIC
# 931 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_PSYCHIC
# 932 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 933 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 934 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMFlamethrower::
# 935 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 3
# 936 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_FLAMETHROWER
# 937 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_FLAMETHROWER
# 938 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 939 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 940 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMThunder::
# 941 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 4
# 942 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_THUNDER
# 943 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_THUNDER
# 944 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 945 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 946 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMIceBeam::
# 947 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 5
# 948 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_ICE_BEAM
# 949 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_ICE_BEAM
# 950 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 951 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 952 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ConfirmTMPrize::
# 953 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem VAR_0x8004
# 954 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_AlreadyHasTM
# 955 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkpcitem VAR_0x8004
# 956 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_AlreadyHasTM
# 957 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special BufferTMHMMoveName
# 958 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX, MSGBOX_YESNO
# 959 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
# 960 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_TEMP_1
# 961 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam
# 962 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_BuyTMPsychic
# 963 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower
# 964 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 4, MauvilleCity_GameCorner_EventScript_BuyTMThunder
# 965 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 5, MauvilleCity_GameCorner_EventScript_BuyTMIceBeam
# 966 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 967 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 968 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam::
# 969 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 970 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_DOUBLE_TEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 971 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_DOUBLE_TEAM
# 972 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 973 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_DOUBLE_TEAM_COINS
# 974 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_TM_DOUBLE_TEAM
# 975 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 976 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 977 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 978 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 979 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 980 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMPsychic::
# 981 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 982 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_PSYCHIC_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 983 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_PSYCHIC
# 984 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 985 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_PSYCHIC_COINS
# 986 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_TM_PSYCHIC
# 987 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 988 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 989 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 990 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 991 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 992 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 993 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower::
# 994 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 995 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 996 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_FLAMETHROWER
# 997 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 998 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_FLAMETHROWER_COINS
# 999 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_TM_FLAMETHROWER
# 1000 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 1001 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 1002 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 1003 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 1004 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1005 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMThunder::
# 1006 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 1007 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_THUNDER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 1008 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_THUNDER
# 1009 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 1010 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_THUNDER_COINS
# 1011 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_TM_THUNDER
# 1012 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 1013 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 1014 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 1015 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 1016 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1017 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1018 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMIceBeam::
# 1019 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 1020 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 1021 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_ICE_BEAM
# 1022 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 1023 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_ICE_BEAM_COINS
# 1024 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_TM_ICE_BEAM
# 1025 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 1026 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 1027 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 1028 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 1029 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1030 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1031 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM::
# 1032 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
# 1033 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 1034 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1035 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1036 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_AlreadyHasTM::
# 1037 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_AlreadyHasTM, MSGBOX_DEFAULT
# 1038 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 1039 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1040 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1041 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew::
# 1042 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
# 1043 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 1044 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1045 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1046 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2::
# 1047 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
# 1048 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
# 1049 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1050 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1051 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForTM::
# 1052 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_BagIsFull
# 1053 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 1054 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1055 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1056 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForNew::
# 1057 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_BagIsFull
# 1058 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 1059 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1060 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1061 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForAnother::
# 1062 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_NoRoomForMore, MSGBOX_DEFAULT
# 1063 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
# 1064 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1065 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1066 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForNew2::
# 1067 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_BagIsFull
# 1068 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
# 1069 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1070 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1071 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CancelTMSelect::
# 1072 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
# 1073 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 1074 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 1075 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1076 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1077 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Woman2::
# 1078 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay, MSGBOX_NPC
# 1079 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1080 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1081 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Dealer::
# 1082 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Dealer, MSGBOX_NPC
# 1083 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1084 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1085 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1086 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Dealer2::
# 1087 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Dealer2, MSGBOX_NPC
# 1088 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1089 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1090 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1091 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_VFGuy1::
# 1092 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_VFGuy1, MSGBOX_NPC
# 1093 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1094 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1095 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1096 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_VFGuy2::
# 1097 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_VFGuy2, MSGBOX_NPC
# 1098 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1099 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1100 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1101 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Gentleman::
# 1102 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_RouletteOnlyLuck, MSGBOX_NPC
# 1103 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1104 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1105 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Girl::
# 1106 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1107 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1108 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_set FLAG_RECEIVED_STARTER_DOLL, MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 1109 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne, MSGBOX_YESNO
# 1110 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_DeclineStarterDoll
# 1111 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_STARTER_MON
# 1112 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll
# 1113 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_GiveTorchicDoll
# 1114 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_GiveMudkipDoll
# 1115 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1116 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1117 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll::
# 1118 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
# 1119 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TREECKO_DOLL
# 1120 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
# 1121 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
# 1122 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	givedecoration DECOR_TREECKO_DOLL
# 1123 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_STARTER_DOLL
# 1124 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 1125 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1126 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1127 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GiveTorchicDoll::
# 1128 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
# 1129 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TORCHIC_DOLL
# 1130 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
# 1131 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
# 1132 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	givedecoration DECOR_TORCHIC_DOLL
# 1133 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_STARTER_DOLL
# 1134 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 1135 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1136 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1137 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GiveMudkipDoll::
# 1138 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
# 1139 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_MUDKIP_DOLL
# 1140 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
# 1141 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
# 1142 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	givedecoration DECOR_MUDKIP_DOLL
# 1143 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_STARTER_DOLL
# 1144 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 1145 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1146 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1147 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll::
# 1148 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_NoRoomForDecor
# 1149 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_YouWantItButNotNow, MSGBOX_DEFAULT
# 1150 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 1151 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1152 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1153 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_DeclineStarterDoll::
# 1154 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DontBeNegative, MSGBOX_DEFAULT
# 1155 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 1156 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1157 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1158 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll::
# 1159 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CantWinJackpot, MSGBOX_DEFAULT
# 1160 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 1161 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1162 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1163 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PokefanM::
# 1164 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1165 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1166 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1167 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_TryGive20Coins
# 1168 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor, MSGBOX_DEFAULT
# 1169 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1170 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1171 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1172 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TryGive20Coins::
# 1173 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_set FLAG_RECEIVED_20_COINS, MauvilleCity_GameCorner_EventScript_PokefanMNormal
# 1174 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_1
# 1175 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_ge VAR_TEMP_1, 1, MauvilleCity_GameCorner_EventScript_PokefanMNormal @ Only give 20 coins if player has no coins
# 1176 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_20_COINS
# 1177 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins 20
# 1178 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins, MSGBOX_DEFAULT
# 1179 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 1180 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_PokefanMNormal
# 1181 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1182 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1183 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PokefanMNormal::
# 1184 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone, MSGBOX_DEFAULT
# 1185 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1186 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1187 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1188 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_OldMan::
# 1189 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1190 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1191 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates, MSGBOX_DEFAULT
# 1192 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1193 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1194 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1195 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PachinkoGuy::
# 1196 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1197 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1198 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_PachinkoGuy, MSGBOX_DEFAULT
# 1199 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1200 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1201 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1202 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Hiker::
# 1203 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1204 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1205 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Hiker, MSGBOX_DEFAULT
# 1206 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1207 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1208 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1209 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Bouncer::
# 1210 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1211 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1212 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Bouncer2, MSGBOX_DEFAULT
# 1213 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1214 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1215 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1216 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_DerbyLady1::
# 1217 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1218 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1219 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Derby_1, MSGBOX_DEFAULT
# 1220 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1221 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1222 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1223 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_DerbyLady2::
# 1224 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1225 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1226 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Derby_2, MSGBOX_DEFAULT
# 1227 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1228 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1229 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1230 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Fisherman::
# 1231 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1232 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1233 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Fisherman, MSGBOX_DEFAULT
# 1234 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1235 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1236 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1237 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Gachalady::
# 1238 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1239 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1240 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Gachalady, MSGBOX_DEFAULT
# 1241 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 1242 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1243 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1244 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Employee::
# 1245 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1246 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1247 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Employee, MSGBOX_DEFAULT
# 1248 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1249 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1250 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1251 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Cook::
# 1252 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1253 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1254 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime, MSGBOX_DEFAULT
# 1255 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1256 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1257 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1258 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Man::
# 1259 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1260 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1261 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed, MSGBOX_DEFAULT
# 1262 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1263 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1264 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1265 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_JuiceLady::
# 1266 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1267 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1268 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1269 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase2
# 1270 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 1271 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_Juice, MSGBOX_YESNO
# 1272 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 1273 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
# 1274 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 1275 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, 10, Juice_Not_Enough
# 1276 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins 10
# 1277 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 1278 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 1279 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	delay 40
# 1280 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 1281 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	giveitem ITEM_BERRY_JUICE
# 1282 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 1283 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1284 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1285 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NPCReturnToSlots::
# 1286 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 1287 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
# 1288 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmovement 0
# 1289 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 1290 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1291 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1292 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Maniac::
# 1293 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1294 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1295 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DifficultToStopOn7, MSGBOX_DEFAULT
# 1296 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1297 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1298 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1299 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Woman::
# 1300 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 1301 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 1302 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo, MSGBOX_DEFAULT
# 1303 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 1304 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1305 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1306 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine0::
# 1307 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1308 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1309 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1310 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 0
# 1311 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1312 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1313 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1314 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1315 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1316 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1317 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine1::
# 1318 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1319 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1320 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1321 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 1
# 1322 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1323 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1324 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1325 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1326 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1327 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1328 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine2::
# 1329 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1330 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1331 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1332 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 2
# 1333 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1334 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1335 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1336 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1337 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1338 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1339 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine3::
# 1340 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1341 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1342 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1343 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 3
# 1344 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1345 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1346 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1347 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1348 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1349 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1350 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine4::
# 1351 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1352 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1353 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1354 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 4
# 1355 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1356 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1357 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1358 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1359 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1360 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1361 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine5::
# 1362 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1363 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1364 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1365 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 5
# 1366 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1367 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1368 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1369 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1370 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1371 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1372 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine6::
# 1373 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1374 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1375 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1376 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 6
# 1377 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1378 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1379 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1380 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1381 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1382 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1383 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine7::
# 1384 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1385 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1386 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1387 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 7
# 1388 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1389 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1390 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1391 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1392 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1393 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1394 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine8::
# 1395 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1396 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1397 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1398 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 8
# 1399 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1400 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1401 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1402 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1403 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1404 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1405 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine9::
# 1406 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1407 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1408 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1409 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 9
# 1410 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1411 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1412 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1413 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1414 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1415 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1416 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine10::
# 1417 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1418 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1419 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1420 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 10
# 1421 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1422 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1423 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1424 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1425 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1426 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1427 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine11::
# 1428 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 1429 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 1430 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 1431 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 11
# 1432 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
# 1433 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playbgm MUS_GAME_CORNER, FALSE
# 1434 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playslotmachine VAR_RESULT
# 1435 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1436 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1437 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1438 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoCoinCase::
# 1439 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase, MSGBOX_DEFAULT
# 1440 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1441 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1442 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1443 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoCoinCase2::
# 1444 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CantBuyWithNoCoinCase, MSGBOX_DEFAULT
# 1445 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 1446 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 1447 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1448 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner:
# 1449 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "This is Goldenrod Game Corner.$"
# 1450 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1451 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_PachinkoGuy:
# 1452 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I used to own one of these dusty old\n"
# 1453 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Dropspin machines.\p"
# 1454 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "The manual always said 'Use the\n"
# 1455 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "directional buttons to tilt and\l"
# 1456 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "change the drop speed…'\p"
# 1457 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I've always wondered what that\n"
# 1458 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "means.$"
# 1459 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1460 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Hiker:
# 1461 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Gah!\n"
# 1462 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I blew it all on that Onix game.\p"
# 1463 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You need to be careful…\p"
# 1464 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You only win 2 Coins for\n"
# 1465 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "every point in these machines.$"
# 1466 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1467 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Derby_1:
# 1468 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Looking to bet on the Derby?\n"
# 1469 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "We've gone digital!\p"
# 1470 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Use one of the tablets\n"
# 1471 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "in front of the counter.$"
# 1472 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1473 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Derby_2:
# 1474 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's not all about condition.\p"
# 1475 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "At the end of the day, it's\n"
# 1476 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "really all luck.\p"
# 1477 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Sometimes it's best to just\n"
# 1478 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "pick your favorite!$"
# 1479 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1480 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Fisherman:
# 1481 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I come here for the food.\p"
# 1482 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's no Celadon Cafe…\n"
# 1483 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "But it'll do.$"
# 1484 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1485 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Gachalady:
# 1486 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "The lottery machines have odds,\n"
# 1487 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "but nothing is guaranteed.\p"
# 1488 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Some machines are better than\n"
# 1489 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "others, and there are different\l"
# 1490 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "rarities in all of them.\p"
# 1491 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "New Pokémon are also weighted\n"
# 1492 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "by your Pokédex, so be wary.$"
# 1493 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1494 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Employee:
# 1495 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I'm on the lookout for cheaters.\n"
# 1496 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Nobody likes a cheater!$"
# 1497 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1498 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Bouncer1:
# 1499 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You need a valid Trainer ID\n"
# 1500 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "to enter the Game Corner.\p"
# 1501 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Let's see…\p"
# 1502 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "…\p"
# 1503 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Hmm…\p"
# 1504 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "…\p"
# 1505 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Everything looks good here.\n"
# 1506 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Enjoy the Game Corner!$"
# 1507 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1508 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Bouncer2:
# 1509 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Enjoy the Game Corner!$"
# 1510 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1511 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Pachinko:
# 1512 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "A Dropspin machine!\n"
# 1513 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's 3 Coins per Ball.$"
# 1514 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1515 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_NoRoomForMore:
# 1516 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Already have it!\n"
# 1517 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "No room for more...$"
# 1518 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1519 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins:
# 1520 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Okay, you wanted some Coins for\n"
# 1521 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the games?\p"
# 1522 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "But you don't have a Coin Case for\n"
# 1523 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "stowing the Coins.$"
# 1524 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1525 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_WereYouLookingForCoins:
# 1526 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Were you looking for Coins?\p"
# 1527 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's ¥1000 for 50 Coins.\n"
# 1528 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Would you like some?$"
# 1529 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1530 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins:
# 1531 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Thank you very much!\n"
# 1532 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here are your Coins!$"
# 1533 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1534 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DontHaveEnoughMoney:
# 1535 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Um… You don't appear to have\n"
# 1536 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "enough money…$"
# 1537 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1538 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CoinCaseIsFull:
# 1539 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh?\n"
# 1540 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Your Coin Case is full.$"
# 1541 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1542 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DontNeedCoinsThen:
# 1543 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh… You don't need Coins, then?\n"
# 1544 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Good luck on your adventure!$"
# 1545 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1546 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes:
# 1547 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Welcome.\p"
# 1548 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You can exchange your Coins for\n"
# 1549 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "prizes here.$"
# 1550 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1551 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_WhichPrize:
# 1552 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Which prize would you like?$"
# 1553 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1554 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX:
# 1555 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "So your choice is\n"
# 1556 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the {STR_VAR_1}?$"
# 1557 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1558 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_SoYourChoiceIsTheNewX:
# 1559 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "So your choice is\n"
# 1560 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the {STR_VAR_1}?$"
# 1561 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1562 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_BlackJack:
# 1563 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's a blackjack table!\n"
# 1564 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Want to play?$"
# 1565 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1566 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Derby:
# 1567 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's the Goldenrod Derby!\n"
# 1568 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Want to place a bet?$"
# 1569 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1570 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Snake:
# 1571 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Onix!\n"
# 1572 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 25 Coins to play.$"
# 1573 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1574 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Bird:
# 1575 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Flutterfree!\n"
# 1576 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 25 Coins to play.$"
# 1577 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1578 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Pinball_Meowth:
# 1579 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's a pinball machine!\n"
# 1580 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 25 Coins to play.$"
# 1581 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1582 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_BS:
# 1583 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Block Builder!\n"
# 1584 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 25 Coins to play.$"
# 1585 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1586 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Pinball_Seel:
# 1587 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's a pinball machine!\n"
# 1588 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 25 Coins to play.$"
# 1589 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1590 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Pinball_Diglett:
# 1591 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's a pinball machine!\n"
# 1592 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 50 Coins to play.$"
# 1593 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1594 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Pinball_Gengar:
# 1595 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's a pinball machine!\n"
# 1596 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 100 Coins to play.$"
# 1597 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1598 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_VF:
# 1599 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Voltorb Flip!\n"
# 1600 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It costs 50 Coins to play.$"
# 1601 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1602 "data/maps/MauvilleCity_GameCorner/scripts.pory"
VF_Come_Again_Text:
# 1603 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Too bad.\n"
# 1604 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Try again soon!$"
# 1605 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1606 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_SendToYourHomePC:
# 1607 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Thank you!\n"
# 1608 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "We'll send it to your PC at home.$"
# 1609 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1610 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_NotEnoughCoins:
# 1611 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough Coins.$"
# 1612 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1613 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_AlreadyHasTM:
# 1614 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You already have that TM.$"
# 1615 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1616 "data/maps/MauvilleCity_GameCorner/scripts.pory"
PB_YOU_WON_TEXT:
# 1617 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You won\n"
# 1618 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "{STR_VAR_1} Coins!$"
# 1619 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1620 "data/maps/MauvilleCity_GameCorner/scripts.pory"
PB_Not_Enough:
# 1621 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's a pinball machine!\p"
# 1622 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough Coins…$"
# 1623 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1624 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Snake_Not_Enough:
# 1625 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Onix!\p"
# 1626 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough Coins…$"
# 1627 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1628 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Bjuice_Not_Enough:
# 1629 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough Coins.$"
# 1630 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1631 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Bird_Not_Enough:
# 1632 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Flutterfree!\p"
# 1633 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough Coins…$"
# 1634 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1635 "data/maps/MauvilleCity_GameCorner/scripts.pory"
BS_Not_Enough:
# 1636 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Block Builder!\p"
# 1637 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough Coins…$"
# 1638 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1639 "data/maps/MauvilleCity_GameCorner/scripts.pory"
Flip_Not_Enough:
# 1640 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's Voltorb Flip!\p"
# 1641 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough Coins…$"
# 1642 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1643 "data/maps/MauvilleCity_GameCorner/scripts.pory"
@ Unused
# 1644 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_NoRoomForPlacingDecor:
# 1645 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "There isn't any room available for\n"
# 1646 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "placing {STR_VAR_1}.$"
# 1647 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1648 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_VF_Keep_Going:
# 1649 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You've made {STR_VAR_1} Coins.\n"
# 1650 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Keep going?$"
# 1651 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1652 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_OhIsThatSo:
# 1653 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh, is that so? \n"
# 1654 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You need to save some Coins before\l"
# 1655 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "coming back here.$"
# 1656 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1657 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_SoYourChoiceIsX:
# 1658 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "So your choice is {STR_VAR_1}?$"
# 1659 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1660 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_HereYouGo:
# 1661 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here you go!$"
# 1662 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1663 "data/maps/MauvilleCity_GameCorner/scripts.pory"
@ Unused
# 1664 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CantCarryAnyMore:
# 1665 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh, you can't carry any more than that.$"
# 1666 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1667 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne:
# 1668 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I made a mistake and got two of\n"
# 1669 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the same Dolls.\p"
# 1670 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Would you like one of them?$"
# 1671 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1672 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_HereYouGo2:
# 1673 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here you go!$"
# 1674 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1675 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_YouWantItButNotNow:
# 1676 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Huh?\n"
# 1677 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You want it, but not right now?$"
# 1678 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1679 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DontBeNegative:
# 1680 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh, don't be so negative!\n"
# 1681 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You can have this!$"
# 1682 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1683 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CantWinJackpot:
# 1684 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "There's a prize I want, but I can't win\n"
# 1685 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the jackpot.$"
# 1686 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1687 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor:
# 1688 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Hey, kid, if you want to play here,\n"
# 1689 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "you need a Coin Case.\p"
# 1690 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I think the young lady next door\n"
# 1691 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "had one. Go see her!$"
# 1692 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1693 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins:
# 1694 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "My luck can only last so long.\n"
# 1695 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "This is too much for me.\l"
# 1696 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here, take some Coins!$"
# 1697 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1698 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone:
# 1699 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Goldenrod has something for\n"
# 1700 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "everyone.\p"
# 1701 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "For me, it's the Game Corner.$"
# 1702 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1703 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates:
# 1704 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "The Roulette tables have different\n"
# 1705 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "rates.\p"
# 1706 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Check your Coins if you're going to\n"
# 1707 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "pick a table.$"
# 1708 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1709 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime:
# 1710 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's easy to lose track of time in here. \n"
# 1711 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I should get back to work.$"
# 1712 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1713 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay:
# 1714 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Coins are needed to play here\n"
# 1715 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "in the Game Corner.$"
# 1716 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1717 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Dealer:
# 1718 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Some say blackjack is about skill.\n"
# 1719 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Others say it's about luck.\p"
# 1720 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I say it's about having fun…\n"
# 1721 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "and maybe winning big!$"
# 1722 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1723 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Dealer2:
# 1724 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You can bet anything divisible\n"
# 1725 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "by 10 here.\p"
# 1726 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Maybe you should go all in!$"
# 1727 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1728 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_VFGuy1:
# 1729 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You want to play Voltorb Flip?\p"
# 1730 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You need to be on the other\n"
# 1731 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "side of the table.$"
# 1732 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1733 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_VFGuy2:
# 1734 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Try the other side of\n"
# 1735 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the table, pal.$"
# 1736 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1737 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_RouletteOnlyLuck:
# 1738 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "This Roulette thing…\n"
# 1739 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's rather demanding.\p"
# 1740 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Win or lose, it's only by luck.$"
# 1741 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1742 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed:
# 1743 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Up to three Coins can be used to play\n"
# 1744 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the Slots.$"
# 1745 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1746 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DifficultToStopOn7:
# 1747 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's very difficult to make it stop\n"
# 1748 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "right on “7.”\p"
# 1749 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "If it stops on “7” during the Reel Time\n"
# 1750 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "bonus game, you'll receive extra Coins.$"
# 1751 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1752 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo:
# 1753 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here's some information for you\n"
# 1754 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "about the Slots.\p"
# 1755 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "The more lightning bolts you stock,\n"
# 1756 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the more Reel Time chances you get.\p"
# 1757 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "In a game with the maximum five\n"
# 1758 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Reel Time chances…\p"
# 1759 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It is possible to receive four regular\n"
# 1760 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "bonuses, then a big bonus.\p"
# 1761 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "That would total 660 Coins, but it's\n"
# 1762 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "very difficult to get.$"
# 1763 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1764 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase:
# 1765 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You can't play if you don't have\n"
# 1766 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "a Coin Case.$"
# 1767 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1768 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CantBuyWithNoCoinCase:
# 1769 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Huh? Looks like you need\n"
# 1770 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "a Coin Case.$"
# 1771 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 1772 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_Juice:
# 1773 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Berry Juice!\n"
# 1774 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Just 10 Coins.$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize::
# 1778 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	dynmultichoice 12, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_0, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_1, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_2, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_3, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_4, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_5
# 1784 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 1786 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_3
# 1787 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_4
# 1788 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_5
# 1789 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_6
# 1790 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 4, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_7
# 1791 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
MauvilleCity_GameCorner_EventScript_ChooseNewPrize_1:
	end

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_3:
# 1786 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_OldAmber
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_4:
# 1787 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_SunStone
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_5:
# 1788 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_MoonStone
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_6:
# 1789 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_LinkingCord
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_7:
# 1790 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_PrismScale
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize_1


MauvilleCity_GameCorner_EventScript_ChooseNewPrize2::
# 1797 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	dynmultichoice 12, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_0, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_1, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_2, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_3, MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_5
# 1802 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 1803 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_3
# 1804 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_4
# 1805 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_5
# 1806 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_6
# 1807 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 4, MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_7
# 1808 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_1:
	end

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_3:
# 1803 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_FireStone
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_4:
# 1804 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ThunderStone
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_5:
# 1805 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_WaterStone
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_6:
# 1806 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_LeafStone
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_1

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_7:
# 1807 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_1


GachaExplainer::
# 1814 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox GachaExplainer_Text_0, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_0:
# 1778 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Old Amber{CLEAR_TO 0x40}4000$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_1:
# 1779 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Sun Stone{CLEAR_TO 0x40}2000$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_2:
# 1780 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Moon Stone{CLEAR_TO 0x40}2000$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_3:
# 1781 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Link Cable{CLEAR_TO 0x40}2500$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_4:
# 1782 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Prism Scale{CLEAR_TO 0x40}3000$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize_Text_5:
# 1783 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Cancel$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_0:
# 1797 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Firestone{CLEAR_TO 0x40}2000$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_1:
# 1798 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Thunderstone{CLEAR_TO 0x40}2000$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_2:
# 1799 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Waterstone{CLEAR_TO 0x40}2000$"

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2_Text_3:
# 1800 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Leafstone{CLEAR_TO 0x40}2000$"

GachaExplainer_Text_0:
# 1814 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Hello! Fancy trying your luck with the\n"
	.string "gachapon? For a minimum wager of 3000\l"
	.string "coins, receive one rare Pokémon!\p"
	.string "The grand prize includes a very\n"
	.string "special Eevee and Pikachu! Don't\l"
	.string "miss out! Gamble to your heart's\l"
	.string "content!$"
