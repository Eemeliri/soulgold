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
	msgbox Route31_Text_DescribeNightmare, MSGBOX_DEFAULT
# 49 "data/maps/Route31/scripts.pory"
	closemessage
# 50 "data/maps/Route31/scripts.pory"
	setvar VAR_KENYA, 2
# 51 "data/maps/Route31/scripts.pory"
	release
# 52 "data/maps/Route31/scripts.pory"
	end
# 53 "data/maps/Route31/scripts.pory"

# 54 "data/maps/Route31/scripts.pory"
Route31_EventScript_SleepyMan_Fail::
# 55 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
# 56 "data/maps/Route31/scripts.pory"
	release
# 57 "data/maps/Route31/scripts.pory"
	end
# 58 "data/maps/Route31/scripts.pory"

# 59 "data/maps/Route31/scripts.pory"

# 60 "data/maps/Route31/scripts.pory"
Route31_EventScript_Boy::
# 61 "data/maps/Route31/scripts.pory"
	lock
# 62 "data/maps/Route31/scripts.pory"
	faceplayer
# 63 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_Youngster, MSGBOX_DEFAULT
# 64 "data/maps/Route31/scripts.pory"
	closemessage
# 65 "data/maps/Route31/scripts.pory"
	release
# 66 "data/maps/Route31/scripts.pory"
	end
# 67 "data/maps/Route31/scripts.pory"

# 68 "data/maps/Route31/scripts.pory"
Route31_EventScript_DarkCaveSign::
# 69 "data/maps/Route31/scripts.pory"
	lock
# 70 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_DarkCaveSign, MSGBOX_SIGN
# 71 "data/maps/Route31/scripts.pory"
	closemessage
# 72 "data/maps/Route31/scripts.pory"
	release
# 73 "data/maps/Route31/scripts.pory"
	end
# 74 "data/maps/Route31/scripts.pory"

# 75 "data/maps/Route31/scripts.pory"
Route31_EventScript_Sign::
# 76 "data/maps/Route31/scripts.pory"
	lock
# 77 "data/maps/Route31/scripts.pory"
	msgbox Route31_Text_Sign, MSGBOX_SIGN
# 78 "data/maps/Route31/scripts.pory"
	closemessage
# 79 "data/maps/Route31/scripts.pory"
	release
# 80 "data/maps/Route31/scripts.pory"
	end
# 81 "data/maps/Route31/scripts.pory"

# 82 "data/maps/Route31/scripts.pory"
Route31_EventScript_ItemPokeBall::
# 83 "data/maps/Route31/scripts.pory"
	finditem ITEM_POKE_BALL
# 84 "data/maps/Route31/scripts.pory"
	end
# 85 "data/maps/Route31/scripts.pory"

# 86 "data/maps/Route31/scripts.pory"
Route31_EventScript_ItemAntidote::
# 87 "data/maps/Route31/scripts.pory"
	finditem ITEM_ANTIDOTE
# 88 "data/maps/Route31/scripts.pory"
	end
# 89 "data/maps/Route31/scripts.pory"

# 90 "data/maps/Route31/scripts.pory"
Route31_Text_CooltrainerM:
# 91 "data/maps/Route31/scripts.pory"
	.string "Dark Cave…\p"
# 92 "data/maps/Route31/scripts.pory"
	.string "If Pokémon could light it up,\n"
# 93 "data/maps/Route31/scripts.pory"
	.string "I'd explore it.$"
# 94 "data/maps/Route31/scripts.pory"

# 95 "data/maps/Route31/scripts.pory"
Route31_Text_BugCatcherWade1_Seen:
# 96 "data/maps/Route31/scripts.pory"
	.string "I caught a bunch of Pokémon.\n"
# 97 "data/maps/Route31/scripts.pory"
	.string "Let me battle with you!$"
# 98 "data/maps/Route31/scripts.pory"

# 99 "data/maps/Route31/scripts.pory"
Route31_Text_BugCatcherWade1_Beaten:
# 100 "data/maps/Route31/scripts.pory"
	.string "Awwwww…$"
# 101 "data/maps/Route31/scripts.pory"

# 102 "data/maps/Route31/scripts.pory"
Route31_Text_BugCatcherWade1_After:
# 103 "data/maps/Route31/scripts.pory"
	.string "You can catch Pokémon even if\n"
# 104 "data/maps/Route31/scripts.pory"
	.string "you have six with you.\p"
# 105 "data/maps/Route31/scripts.pory"
	.string "If you catch one, it'll go to\n"
# 106 "data/maps/Route31/scripts.pory"
	.string "your Box automatically.$"
# 107 "data/maps/Route31/scripts.pory"

# 108 "data/maps/Route31/scripts.pory"
Route31_Text_SleepyMan:
# 109 "data/maps/Route31/scripts.pory"
	.string "… Hnuurg… Huh?\p"
# 110 "data/maps/Route31/scripts.pory"
	.string "I walked too far today looking\n"
# 111 "data/maps/Route31/scripts.pory"
	.string "for Pokémon.\p"
# 112 "data/maps/Route31/scripts.pory"
	.string "My feet hurt and I'm sleepy…\p"
# 113 "data/maps/Route31/scripts.pory"
	.string "If I were a wild Pokémon, I'd\n"
# 114 "data/maps/Route31/scripts.pory"
	.string "be easy to catch…\p"
# 115 "data/maps/Route31/scripts.pory"
	.string "…Zzzz…$"
# 116 "data/maps/Route31/scripts.pory"

# 117 "data/maps/Route31/scripts.pory"
Route31_Text_SleepyManGotMail:
# 118 "data/maps/Route31/scripts.pory"
	.string "…Zzzz… Huh?\p"
# 119 "data/maps/Route31/scripts.pory"
	.string "What's that? You have Mail\n"
# 120 "data/maps/Route31/scripts.pory"
	.string "for me?$"
# 121 "data/maps/Route31/scripts.pory"

# 122 "data/maps/Route31/scripts.pory"
Route31_Text_SleepyManFail:
# 123 "data/maps/Route31/scripts.pory"
	.string "…Zzzz…$"
# 124 "data/maps/Route31/scripts.pory"

# 125 "data/maps/Route31/scripts.pory"
Route31_Text_HandOverMailMon:
# 126 "data/maps/Route31/scripts.pory"
	.string "{PLAYER} handed over the\n"
# 127 "data/maps/Route31/scripts.pory"
	.string "Pokémon holding the Mail.$"
# 128 "data/maps/Route31/scripts.pory"

# 129 "data/maps/Route31/scripts.pory"
Route31_Text_ReadingMail:
# 130 "data/maps/Route31/scripts.pory"
	.string "Let's see…\p"
# 131 "data/maps/Route31/scripts.pory"
	.string "Thanks for bringing this to\n"
# 132 "data/maps/Route31/scripts.pory"
	.string "me.\p"
# 133 "data/maps/Route31/scripts.pory"
	.string "My friend's a good guy, and\n"
# 134 "data/maps/Route31/scripts.pory"
	.string "you're swell too!\p"
# 135 "data/maps/Route31/scripts.pory"
	.string "I'd like to do something good\n"
# 136 "data/maps/Route31/scripts.pory"
	.string "in return too!\p"
# 137 "data/maps/Route31/scripts.pory"
	.string "I know! I want you to have\n"
# 138 "data/maps/Route31/scripts.pory"
	.string "this!$"
# 139 "data/maps/Route31/scripts.pory"

# 140 "data/maps/Route31/scripts.pory"
Route31_Text_DescribeNightmare:
# 141 "data/maps/Route31/scripts.pory"
	.string "That TM contains Torment.\p"
# 142 "data/maps/Route31/scripts.pory"
	.string "It's a wicked move that\n"
# 143 "data/maps/Route31/scripts.pory"
	.string "makes the enemy super nervous and\l"
# 144 "data/maps/Route31/scripts.pory"
	.string "stops them from using the same\p"
# 145 "data/maps/Route31/scripts.pory"
	.string "move multiple times in a row.$"
# 146 "data/maps/Route31/scripts.pory"

# 147 "data/maps/Route31/scripts.pory"
Route31_Text_WrongMail:
# 148 "data/maps/Route31/scripts.pory"
	.string "This Mail isn't for me.$"
# 149 "data/maps/Route31/scripts.pory"

# 150 "data/maps/Route31/scripts.pory"
Route31_Text_MissingMail:
# 151 "data/maps/Route31/scripts.pory"
	.string "Why is this Pokémon so special?\p"
# 152 "data/maps/Route31/scripts.pory"
	.string "It doesn't have any Mail.$"
# 153 "data/maps/Route31/scripts.pory"

# 154 "data/maps/Route31/scripts.pory"
Route31_Text_DeclinedToHandOverMail:
# 155 "data/maps/Route31/scripts.pory"
	.string "What? You don't want\n"
# 156 "data/maps/Route31/scripts.pory"
	.string "anything?$"
# 157 "data/maps/Route31/scripts.pory"

# 158 "data/maps/Route31/scripts.pory"
Route31_Text_CantTakeLastMon:
# 159 "data/maps/Route31/scripts.pory"
	.string "If I take that Pokémon from\n"
# 160 "data/maps/Route31/scripts.pory"
	.string "you,\p"
# 161 "data/maps/Route31/scripts.pory"
	.string "what are you going to use in\n"
# 162 "data/maps/Route31/scripts.pory"
	.string "battle?$"
# 163 "data/maps/Route31/scripts.pory"

# 164 "data/maps/Route31/scripts.pory"
Route31_Text_Youngster:
# 165 "data/maps/Route31/scripts.pory"
	.string "I found a good Pokémon in Dark\n"
# 166 "data/maps/Route31/scripts.pory"
	.string "Cave.\p"
# 167 "data/maps/Route31/scripts.pory"
	.string "I'm going to raise it to take\n"
# 168 "data/maps/Route31/scripts.pory"
	.string "on Falkner.\p"
# 169 "data/maps/Route31/scripts.pory"
	.string "He's the leader of Violet\n"
# 170 "data/maps/Route31/scripts.pory"
	.string "City's Gym.$"
# 171 "data/maps/Route31/scripts.pory"

# 172 "data/maps/Route31/scripts.pory"
Route31_Text_Sign:
# 173 "data/maps/Route31/scripts.pory"
	.string "Route 31\p"
# 174 "data/maps/Route31/scripts.pory"
	.string "Violet City - Cherrygrove City$"
# 175 "data/maps/Route31/scripts.pory"

# 176 "data/maps/Route31/scripts.pory"
Route31_Text_DarkCaveSign:
# 177 "data/maps/Route31/scripts.pory"
	.string "Dark Cave$"

Route31_Expert::
# 181 "data/maps/Route31/scripts.pory"
	lock
# 182 "data/maps/Route31/scripts.pory"
	faceplayer
# 183 "data/maps/Route31/scripts.pory"
	goto_if_set FLAG_ROUTE31_EXPERT, Route31_Expert_2
# 200 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_1
# 208 "data/maps/Route31/scripts.pory"
	goto_if_set FLAG_ROUTE31_EXPERT_QUALIFIED, Route31_Expert_5
# 208 "data/maps/Route31/scripts.pory"
	checktrainerflag TRAINER_WADE
	goto_if 1, Route31_Expert_9
Route31_Expert_4:
# 237 "data/maps/Route31/scripts.pory"
	release
	end

Route31_Expert_2:
# 184 "data/maps/Route31/scripts.pory"
	setflag FLAG_ROUTE31_EXPERT_QUALIFIED
# 185 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_0
# 197 "data/maps/Route31/scripts.pory"
	release
	end

Route31_Expert_5:
# 209 "data/maps/Route31/scripts.pory"
	setflag FLAG_ROUTE31_EXPERT_QUALIFIED
# 210 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_2
# 214 "data/maps/Route31/scripts.pory"
	trainerbattle_no_intro TRAINER_ROUTE_31_EXPERT, Route31_Expert_Text_3
# 215 "data/maps/Route31/scripts.pory"
	createfieldmugshot MUGSHOT_COOLTRAINER_M
# 216 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_4
# 219 "data/maps/Route31/scripts.pory"
	giveitem ITEM_AIR_BALLOON
# 220 "data/maps/Route31/scripts.pory"
	setflag FLAG_ROUTE31_EXPERT
# 221 "data/maps/Route31/scripts.pory"
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
# 222 "data/maps/Route31/scripts.pory"
	special Achievement_CheckAll
# 223 "data/maps/Route31/scripts.pory"
	createfieldmugshot MUGSHOT_COOLTRAINER_M
# 224 "data/maps/Route31/scripts.pory"
	msgbox Route31_Expert_Text_0
	goto Route31_Expert_4

Route31_Expert_8:
# 208 "data/maps/Route31/scripts.pory"
	checktrainerflag TRAINER_MIKEY
	goto_if 1, Route31_Expert_12
	goto Route31_Expert_4

Route31_Expert_9:
# 208 "data/maps/Route31/scripts.pory"
	checktrainerflag TRAINER_JOEY
	goto_if 1, Route31_Expert_8
	goto Route31_Expert_4

Route31_Expert_12:
# 208 "data/maps/Route31/scripts.pory"
	checktrainerflag TRAINER_DON
	goto_if 1, Route31_Expert_5
	goto Route31_Expert_4


Route31_Expert_Text_0:
# 185 "data/maps/Route31/scripts.pory"
	.string "Air Balloon lets a Pokémon avoid \n"
	.string "Ground-type moves until it \l"
	.string "takes a hit.\p"
	.string "It might prove useful in the \n"
	.string "coming battles.\p"
	.string "Held items similar to this can\n"
	.string "be activated once per battle.\p"
	.string "They will be restored after the\n"
	.string "battle is over.$"

Route31_Expert_Text_1:
# 200 "data/maps/Route31/scripts.pory"
	.string "I'm what they call a route expert. \p"
	.string "If you manage to beat every trainer on \n"
	.string "Route 30 and 31, come find me again \l"
	.string "and we will have a battle.\p"
	.string "I'll make it worth your while,\n"
	.string "if you manage to win.$"

Route31_Expert_Text_2:
# 210 "data/maps/Route31/scripts.pory"
	.string "Oh, you have indeed defeated \n"
	.string "all the trainers on this route.\p"
	.string "I will battle you as promised.$"

Route31_Expert_Text_3:
# 214 "data/maps/Route31/scripts.pory"
	.string "Popped off...$"

Route31_Expert_Text_4:
# 216 "data/maps/Route31/scripts.pory"
	.string "You are better than I had assumed. \p"
	.string "Take this for your victory.$"
