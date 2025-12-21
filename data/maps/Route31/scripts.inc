# 1 "data/maps/Route31/scripts.pory"

# 2 "data/maps/Route31/scripts.pory"
Route31_MapScripts::
# 3 "data/maps/Route31/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route31_OnTransition
# 4 "data/maps/Route31/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 5 "data/maps/Route31/scripts.pory"
	.byte 0
# 6 "data/maps/Route31/scripts.pory"

# 7 "data/maps/Route31/scripts.pory"
Route31_OnTransition: 
# 8 "data/maps/Route31/scripts.pory"
	callnative SetTimeBasedEncounters
# 9 "data/maps/Route31/scripts.pory"
	end
# 10 "data/maps/Route31/scripts.pory"

# 11 "data/maps/Route31/scripts.pory"
Route31_EventScript_Bugcatcher_Wade::
# 12 "data/maps/Route31/scripts.pory"
	trainerbattle_single TRAINER_WADE, Route31_Text_BugCatcherWade1_Seen, Route31_Text_BugCatcherWade1_Beaten
# 13 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_BugCatcherWade1_After, MSGBOX_AUTOCLOSE
# 14 "data/maps/Route31/scripts.pory"
	end
# 15 "data/maps/Route31/scripts.pory"

# 16 "data/maps/Route31/scripts.pory"
Route31_EventScript_Youngster::
# 17 "data/maps/Route31/scripts.pory"
	lock
# 18 "data/maps/Route31/scripts.pory"
	faceplayer
# 19 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_CooltrainerM, MSGBOX_DEFAULT
# 20 "data/maps/Route31/scripts.pory"
	closemessage
# 21 "data/maps/Route31/scripts.pory"
	release
# 22 "data/maps/Route31/scripts.pory"
	end
# 23 "data/maps/Route31/scripts.pory"

# 24 "data/maps/Route31/scripts.pory"
Route31_EventScript_SleepyMan::
# 25 "data/maps/Route31/scripts.pory"
	lock
# 26 "data/maps/Route31/scripts.pory"
	faceplayer
# 27 "data/maps/Route31/scripts.pory"
	goto_if_eq VAR_KENYA, 1, Route31_EventScript_SleepyMan_AskForKenya
# 28 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_SleepyMan, MSGBOX_DEFAULT
# 29 "data/maps/Route31/scripts.pory"
	closemessage
# 30 "data/maps/Route31/scripts.pory"
	release
# 31 "data/maps/Route31/scripts.pory"
	end
# 32 "data/maps/Route31/scripts.pory"

# 33 "data/maps/Route31/scripts.pory"
Route31_EventScript_SleepyMan_AskForKenya::
# 34 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_SleepyManGotMail MSGBOX_YESNO
# 35 "data/maps/Route31/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route31_EventScript_SleepyMan_GiveKenya
# 36 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
# 37 "data/maps/Route31/scripts.pory"
	closemessage
# 38 "data/maps/Route31/scripts.pory"
	release
# 39 "data/maps/Route31/scripts.pory"
	end
# 40 "data/maps/Route31/scripts.pory"

# 41 "data/maps/Route31/scripts.pory"
Route31_EventScript_SleepyMan_GiveKenya::
# 42 "data/maps/Route31/scripts.pory"
	removenamedmon 1
# 43 "data/maps/Route31/scripts.pory"
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Route31_EventScript_SleepyMan_Fail
# 44 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_HandOverMailMon, MSGBOX_DEFAULT
# 45 "data/maps/Route31/scripts.pory"
	delay 55
# 46 "data/maps/Route31/scripts.pory"
	callnative UpdateFollowingPokemon
# 47 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_ReadingMail, MSGBOX_DEFAULT
# 48 "data/maps/Route31/scripts.pory"
	giveitem ITEM_TM_TORMENT
# 49 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_DescribeNightmare, MSGBOX_DEFAULT
# 50 "data/maps/Route31/scripts.pory"
	closemessage
# 51 "data/maps/Route31/scripts.pory"
	setvar VAR_KENYA, 2
# 52 "data/maps/Route31/scripts.pory"
	release
# 53 "data/maps/Route31/scripts.pory"
	end
# 54 "data/maps/Route31/scripts.pory"

# 55 "data/maps/Route31/scripts.pory"
Route31_EventScript_SleepyMan_Fail::
# 56 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
# 57 "data/maps/Route31/scripts.pory"
	release
# 58 "data/maps/Route31/scripts.pory"
	end
# 59 "data/maps/Route31/scripts.pory"

# 60 "data/maps/Route31/scripts.pory"

# 61 "data/maps/Route31/scripts.pory"
Route31_EventScript_Boy::
# 62 "data/maps/Route31/scripts.pory"
	lock
# 63 "data/maps/Route31/scripts.pory"
	faceplayer
# 64 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_Youngster, MSGBOX_DEFAULT
# 65 "data/maps/Route31/scripts.pory"
	closemessage
# 66 "data/maps/Route31/scripts.pory"
	release
# 67 "data/maps/Route31/scripts.pory"
	end
# 68 "data/maps/Route31/scripts.pory"

# 69 "data/maps/Route31/scripts.pory"
Route31_EventScript_DarkCaveSign::
# 70 "data/maps/Route31/scripts.pory"
	lock
# 71 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_DarkCaveSign, MSGBOX_SIGN
# 72 "data/maps/Route31/scripts.pory"
	closemessage
# 73 "data/maps/Route31/scripts.pory"
	release
# 74 "data/maps/Route31/scripts.pory"
	end
# 75 "data/maps/Route31/scripts.pory"

# 76 "data/maps/Route31/scripts.pory"
Route31_EventScript_Sign::
# 77 "data/maps/Route31/scripts.pory"
	lock
# 78 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_Sign, MSGBOX_SIGN
# 79 "data/maps/Route31/scripts.pory"
	closemessage
# 80 "data/maps/Route31/scripts.pory"
	release
# 81 "data/maps/Route31/scripts.pory"
	end
# 82 "data/maps/Route31/scripts.pory"

# 83 "data/maps/Route31/scripts.pory"
Route31_EventScript_ItemPokeBall::
# 84 "data/maps/Route31/scripts.pory"
	finditem ITEM_POKE_BALL
# 85 "data/maps/Route31/scripts.pory"
	end
# 86 "data/maps/Route31/scripts.pory"

# 87 "data/maps/Route31/scripts.pory"
Route31_EventScript_ItemAntidote::
# 88 "data/maps/Route31/scripts.pory"
	finditem ITEM_ANTIDOTE
# 89 "data/maps/Route31/scripts.pory"
	end
# 90 "data/maps/Route31/scripts.pory"

# 91 "data/maps/Route31/scripts.pory"
Route31_Text_CooltrainerM:
# 92 "data/maps/Route31/scripts.pory"
	.string "DARK CAVE…\p"
# 93 "data/maps/Route31/scripts.pory"
	.string "If POKéMON could light it up,\n"
# 94 "data/maps/Route31/scripts.pory"
	.string "I'd explore it.$"
# 95 "data/maps/Route31/scripts.pory"

# 96 "data/maps/Route31/scripts.pory"
Route31_Text_BugCatcherWade1_Seen:
# 97 "data/maps/Route31/scripts.pory"
	.string "I caught a bunch of POKéMON.\n"
# 98 "data/maps/Route31/scripts.pory"
	.string "Let me battle with you!$"
# 99 "data/maps/Route31/scripts.pory"

# 100 "data/maps/Route31/scripts.pory"
Route31_Text_BugCatcherWade1_Beaten:
# 101 "data/maps/Route31/scripts.pory"
	.string "Awwwww…$"
# 102 "data/maps/Route31/scripts.pory"

# 103 "data/maps/Route31/scripts.pory"
Route31_Text_BugCatcherWade1_After:
# 104 "data/maps/Route31/scripts.pory"
	.string "You can catch POKéMON even if\n"
# 105 "data/maps/Route31/scripts.pory"
	.string "you have six with you.\p"
# 106 "data/maps/Route31/scripts.pory"
	.string "If you catch one, it'll go to\n"
# 107 "data/maps/Route31/scripts.pory"
	.string "your BOX automatically.$"
# 108 "data/maps/Route31/scripts.pory"

# 109 "data/maps/Route31/scripts.pory"
Route31_Text_SleepyMan:
# 110 "data/maps/Route31/scripts.pory"
	.string "… Hnuurg… Huh?\p"
# 111 "data/maps/Route31/scripts.pory"
	.string "I walked too far today looking\n"
# 112 "data/maps/Route31/scripts.pory"
	.string "for POKéMON.\p"
# 113 "data/maps/Route31/scripts.pory"
	.string "My feet hurt and I'm sleepy…\p"
# 114 "data/maps/Route31/scripts.pory"
	.string "If I were a wild POKéMON, I'd\n"
# 115 "data/maps/Route31/scripts.pory"
	.string "be easy to catch…\p"
# 116 "data/maps/Route31/scripts.pory"
	.string "…Zzzz…$"
# 117 "data/maps/Route31/scripts.pory"

# 118 "data/maps/Route31/scripts.pory"
Route31_Text_SleepyManGotMail:
# 119 "data/maps/Route31/scripts.pory"
	.string "…Zzzz… Huh?\p"
# 120 "data/maps/Route31/scripts.pory"
	.string "What's that? You have MAIL\n"
# 121 "data/maps/Route31/scripts.pory"
	.string "for me?$"
# 122 "data/maps/Route31/scripts.pory"

# 123 "data/maps/Route31/scripts.pory"
Route31_Text_SleepyManFail:
# 124 "data/maps/Route31/scripts.pory"
	.string "…Zzzz…$"
# 125 "data/maps/Route31/scripts.pory"

# 126 "data/maps/Route31/scripts.pory"
Route31_Text_HandOverMailMon:
# 127 "data/maps/Route31/scripts.pory"
	.string "{PLAYER} handed over the\n"
# 128 "data/maps/Route31/scripts.pory"
	.string "POKéMON holding the MAIL.$"
# 129 "data/maps/Route31/scripts.pory"

# 130 "data/maps/Route31/scripts.pory"
Route31_Text_ReadingMail:
# 131 "data/maps/Route31/scripts.pory"
	.string "Let's see…\p"
# 132 "data/maps/Route31/scripts.pory"
	.string "Thanks for bringing this to\n"
# 133 "data/maps/Route31/scripts.pory"
	.string "me.\p"
# 134 "data/maps/Route31/scripts.pory"
	.string "My friend's a good guy, and\n"
# 135 "data/maps/Route31/scripts.pory"
	.string "you're swell too!\p"
# 136 "data/maps/Route31/scripts.pory"
	.string "I'd like to do something good\n"
# 137 "data/maps/Route31/scripts.pory"
	.string "in return too!\p"
# 138 "data/maps/Route31/scripts.pory"
	.string "I know! I want you to have\n"
# 139 "data/maps/Route31/scripts.pory"
	.string "this!$"
# 140 "data/maps/Route31/scripts.pory"

# 141 "data/maps/Route31/scripts.pory"
Route31_Text_DescribeNightmare:
# 142 "data/maps/Route31/scripts.pory"
	.string "That TM contains TORMENT.\p"
# 143 "data/maps/Route31/scripts.pory"
	.string "It's a wicked move that\n"
# 144 "data/maps/Route31/scripts.pory"
	.string "makes the enemy super nervous and\l"
# 145 "data/maps/Route31/scripts.pory"
	.string "stops them from using the same\p"
# 146 "data/maps/Route31/scripts.pory"
	.string "move multiple times in a row.$"
# 147 "data/maps/Route31/scripts.pory"

# 148 "data/maps/Route31/scripts.pory"
Route31_Text_WrongMail:
# 149 "data/maps/Route31/scripts.pory"
	.string "This MAIL isn't for me.$"
# 150 "data/maps/Route31/scripts.pory"

# 151 "data/maps/Route31/scripts.pory"
Route31_Text_MissingMail:
# 152 "data/maps/Route31/scripts.pory"
	.string "Why is this POKéMON so special?\p"
# 153 "data/maps/Route31/scripts.pory"
	.string "It doesn't have any MAIL.$"
# 154 "data/maps/Route31/scripts.pory"

# 155 "data/maps/Route31/scripts.pory"
Route31_Text_DeclinedToHandOverMail:
# 156 "data/maps/Route31/scripts.pory"
	.string "What? You don't want\n"
# 157 "data/maps/Route31/scripts.pory"
	.string "anything?$"
# 158 "data/maps/Route31/scripts.pory"

# 159 "data/maps/Route31/scripts.pory"
Route31_Text_CantTakeLastMon:
# 160 "data/maps/Route31/scripts.pory"
	.string "If I take that POKéMON from\n"
# 161 "data/maps/Route31/scripts.pory"
	.string "you,\p"
# 162 "data/maps/Route31/scripts.pory"
	.string "what are you going to use in\n"
# 163 "data/maps/Route31/scripts.pory"
	.string "battle?$"
# 164 "data/maps/Route31/scripts.pory"

# 165 "data/maps/Route31/scripts.pory"
Route31_Text_Youngster:
# 166 "data/maps/Route31/scripts.pory"
	.string "I found a good POKéMON in DARK\n"
# 167 "data/maps/Route31/scripts.pory"
	.string "CAVE.\p"
# 168 "data/maps/Route31/scripts.pory"
	.string "I'm going to raise it to take\n"
# 169 "data/maps/Route31/scripts.pory"
	.string "on FALKNER.\p"
# 170 "data/maps/Route31/scripts.pory"
	.string "He's the leader of VIOLET\n"
# 171 "data/maps/Route31/scripts.pory"
	.string "CITY's GYM.$"
# 172 "data/maps/Route31/scripts.pory"

# 173 "data/maps/Route31/scripts.pory"
Route31_Text_Sign:
# 174 "data/maps/Route31/scripts.pory"
	.string "ROUTE 31\p"
# 175 "data/maps/Route31/scripts.pory"
	.string "VIOLET CITY - CHERRYGROVE CITY$"
# 176 "data/maps/Route31/scripts.pory"

# 177 "data/maps/Route31/scripts.pory"
Route31_Text_DarkCaveSign:
# 178 "data/maps/Route31/scripts.pory"
	.string "DARK CAVE$"

Route31_Expert::
# 182 "data/maps/Route31/scripts.pory"
	lock
# 183 "data/maps/Route31/scripts.pory"
	faceplayer
# 184 "data/maps/Route31/scripts.pory"
	goto_if_set FLAG_ROUTE31_EXPERT, Route31_Expert_2
# 189 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_1
# 190 "data/maps/Route31/scripts.pory"
	checktrainerflag TRAINER_WADE
	goto_if 1, Route31_Expert_7
Route31_Expert_4:
# 198 "data/maps/Route31/scripts.pory"
	release
	end

Route31_Expert_2:
# 185 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_0
# 186 "data/maps/Route31/scripts.pory"
	release
	end

Route31_Expert_5:
# 191 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_2
# 192 "data/maps/Route31/scripts.pory"
	trainerbattle_no_intro TRAINER_ROUTE_31_EXPERT, Route31_Expert_Text_3
# 193 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_4
# 194 "data/maps/Route31/scripts.pory"
	giveitem ITEM_AIR_BALLOON
# 195 "data/maps/Route31/scripts.pory"
	setflag FLAG_ROUTE31_EXPERT
# 196 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_5
	goto Route31_Expert_4

Route31_Expert_6:
# 190 "data/maps/Route31/scripts.pory"
	checktrainerflag TRAINER_DON
	goto_if 1, Route31_Expert_5
	goto Route31_Expert_4

Route31_Expert_7:
# 190 "data/maps/Route31/scripts.pory"
	checktrainerflag TRAINER_JOEY
	goto_if 1, Route31_Expert_6
	goto Route31_Expert_4


Route31_Expert_Text_0:
# 185 "data/maps/Route31/scripts.pory"
	.string "Air Balloon lets a Pokémon avoid\n"
	.string "Ground-type moves until it takes a hit.\l"
	.string "It might prove useful in the coming\l"
	.string "battles.$"

Route31_Expert_Text_1:
# 189 "data/maps/Route31/scripts.pory"
	.string "I'm what they call a route master. If\n"
	.string "you manage to beat every trainer on\l"
	.string "this route, come find me again and we\l"
	.string "will have a battle. I'll make it worth\l"
	.string "your while if you manage to win.$"

Route31_Expert_Text_2:
# 191 "data/maps/Route31/scripts.pory"
	.string "Oh, you have indeed defeated all the\n"
	.string "trainers on this route. I will battle you\l"
	.string "as promised.$"

Route31_Expert_Text_3:
# 192 "data/maps/Route31/scripts.pory"
	.string "Popped off...$"

Route31_Expert_Text_4:
# 193 "data/maps/Route31/scripts.pory"
	.string "You are better than I had assumed. Take\n"
	.string "this for your victory.$"

Route31_Expert_Text_5:
# 196 "data/maps/Route31/scripts.pory"
	.string "This Air Balloon lets a Pokémon avoid\n"
	.string "Ground-type moves until it takes a hit.\l"
	.string "It might prove useful in the coming\l"
	.string "battles.$"
