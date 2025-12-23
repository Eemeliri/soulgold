# 1 "data/maps/VioletCity_Gym/scripts.pory"

# 2 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_MapScripts::
# 3 "data/maps/VioletCity_Gym/scripts.pory"
	.byte 0
# 4 "data/maps/VioletCity_Gym/scripts.pory"

# 5 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_GymGuy::
# 6 "data/maps/VioletCity_Gym/scripts.pory"
	lock
# 7 "data/maps/VioletCity_Gym/scripts.pory"
	faceplayer
# 8 "data/maps/VioletCity_Gym/scripts.pory"
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_GymGuy2
# 9 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_GymGuide_Intro, MSGBOX_DEFAULT
# 10 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 11 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 12 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 13 "data/maps/VioletCity_Gym/scripts.pory"
	
# 14 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_GymGuy2::
# 15 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_GymGuide_Win, MSGBOX_DEFAULT
# 16 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 17 "data/maps/VioletCity_Gym/scripts.pory"
	end	
# 18 "data/maps/VioletCity_Gym/scripts.pory"

# 19 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Rod::
# 20 "data/maps/VioletCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_ROD VioletGym_Text_BirdKeeperRod_Seen, VioletGym_Text_BirdKeeperRod_Beaten
# 21 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_BirdKeeperRod_After, MSGBOX_AUTOCLOSE
# 22 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 23 "data/maps/VioletCity_Gym/scripts.pory"

# 24 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Abe::
# 25 "data/maps/VioletCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_ABE VioletGym_Text_BirdKeeperAbe_Seen, VioletGym_Text_BirdKeeperAbe_Beaten
# 26 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_BirdKeeperAbe_After, MSGBOX_AUTOCLOSE
# 27 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 28 "data/maps/VioletCity_Gym/scripts.pory"

# 29 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Falkner::
# 30 "data/maps/VioletCity_Gym/scripts.pory"
	lock
# 31 "data/maps/VioletCity_Gym/scripts.pory"
	faceplayer
# 32 "data/maps/VioletCity_Gym/scripts.pory"
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Falkner_Defeated
# 33 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_Falkner_Intro, MSGBOX_DEFAULT
# 34 "data/maps/VioletCity_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_FALKNER_1, VioletGym_Text_Falkner_WinLoss
# 35 "data/maps/VioletCity_Gym/scripts.pory"
	message VioletGym_Text_ReceivedZephyrBadge
# 36 "data/maps/VioletCity_Gym/scripts.pory"
	waitmessage
# 37 "data/maps/VioletCity_Gym/scripts.pory"
	call Common_EventScript_PlayGymBadgeFanfare
# 38 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_Falkner_BadgeExplain, MSGBOX_DEFAULT
# 39 "data/maps/VioletCity_Gym/scripts.pory"
	setflag FLAG_BADGE01_GET
# 40 "data/maps/VioletCity_Gym/scripts.pory"
	setflag FLAG_DEFEATED_VIOLET_GYM
# 41 "data/maps/VioletCity_Gym/scripts.pory"
	addvar VAR_NUM_BADGES, 1
# 42 "data/maps/VioletCity_Gym/scripts.pory"
	setvar VAR_0x8008, 1
# 43 "data/maps/VioletCity_Gym/scripts.pory"
	call Common_EventScript_SetGymTrainers
# 44 "data/maps/VioletCity_Gym/scripts.pory"
	giveitem ITEM_TM_DOUBLE_TEAM
# 45 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_Falkner_TMExplain, MSGBOX_DEFAULT
# 46 "data/maps/VioletCity_Gym/scripts.pory"
	setvar VAR_VIOLET_CITY_STATE, 3
# 47 "data/maps/VioletCity_Gym/scripts.pory"
	setrespawn HEAL_LOCATION_VIOLET_CITY
# 48 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 49 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 50 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 51 "data/maps/VioletCity_Gym/scripts.pory"

# 52 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Falkner_Defeated::
# 53 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_Falkner_AfterFight, MSGBOX_DEFAULT
# 54 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 55 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 56 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 57 "data/maps/VioletCity_Gym/scripts.pory"

# 58 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_Intro:
# 59 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'm FALKNER, the VIOLET POKéMON\n"
# 60 "data/maps/VioletCity_Gym/scripts.pory"
	.string "GYM leader!\p"
# 61 "data/maps/VioletCity_Gym/scripts.pory"
	.string "People say you can clip\n"
# 62 "data/maps/VioletCity_Gym/scripts.pory"
	.string "FLYING-type POKéMON's wings\p"
# 63 "data/maps/VioletCity_Gym/scripts.pory"
	.string "with a jolt of electricity…\n"
# 64 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I won't allow such insults to bird\l"
# 65 "data/maps/VioletCity_Gym/scripts.pory"
	.string "POKéMON!\p"
# 66 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'll show you the real power\n"
# 67 "data/maps/VioletCity_Gym/scripts.pory"
	.string "of the magnificent bird POKéMON!$"
# 68 "data/maps/VioletCity_Gym/scripts.pory"

# 69 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_WinLoss:
# 70 "data/maps/VioletCity_Gym/scripts.pory"
	.string "…Darn! My dad's cherished bird\n"
# 71 "data/maps/VioletCity_Gym/scripts.pory"
	.string "POKéMON…\p"
# 72 "data/maps/VioletCity_Gym/scripts.pory"
	.string "All right. Take this.\p"
# 73 "data/maps/VioletCity_Gym/scripts.pory"
	.string "It's the official POKéMON LEAGUE\n"
# 74 "data/maps/VioletCity_Gym/scripts.pory"
	.string "ZEPHYRBADGE.$"
# 75 "data/maps/VioletCity_Gym/scripts.pory"

# 76 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_ReceivedZephyrBadge:
# 77 "data/maps/VioletCity_Gym/scripts.pory"
	.string "{PLAYER} received ZEPHYRBADGE.$"
# 78 "data/maps/VioletCity_Gym/scripts.pory"

# 79 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_BadgeExplain:
# 80 "data/maps/VioletCity_Gym/scripts.pory"
	.string "ZEPHYRBADGE raises the ATTACK\n"
# 81 "data/maps/VioletCity_Gym/scripts.pory"
	.string "power of POKéMON.\p"
# 82 "data/maps/VioletCity_Gym/scripts.pory"
	.string "It also enables POKéMON to use\n"
# 83 "data/maps/VioletCity_Gym/scripts.pory"
	.string "FLASH, if they can learn it,\l"
# 84 "data/maps/VioletCity_Gym/scripts.pory"
	.string "anytime.\p"
# 85 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Here--take this too.$"
# 86 "data/maps/VioletCity_Gym/scripts.pory"

# 87 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_TMExplain:
# 88 "data/maps/VioletCity_Gym/scripts.pory"
	.string "By using a TM, a POKéMON will\n"
# 89 "data/maps/VioletCity_Gym/scripts.pory"
	.string "instantly learn a new move.\p"
# 90 "data/maps/VioletCity_Gym/scripts.pory"
	.string "TM32 contains DOUBLE TEAM.\p"
# 91 "data/maps/VioletCity_Gym/scripts.pory"
	.string "It increase a POKéMON's evasion.\p"
# 92 "data/maps/VioletCity_Gym/scripts.pory"
	.string "In other words, your POKéMON\n"
# 93 "data/maps/VioletCity_Gym/scripts.pory"
	.string "will be harder to hit.$"
# 94 "data/maps/VioletCity_Gym/scripts.pory"

# 95 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_AfterFight:
# 96 "data/maps/VioletCity_Gym/scripts.pory"
	.string "There are POKéMON GYMS in cities\n"
# 97 "data/maps/VioletCity_Gym/scripts.pory"
	.string "and towns ahead.\p"
# 98 "data/maps/VioletCity_Gym/scripts.pory"
	.string "You should test your skills at\n"
# 99 "data/maps/VioletCity_Gym/scripts.pory"
	.string "these GYMS.\p"
# 100 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'm going to train harder to\n"
# 101 "data/maps/VioletCity_Gym/scripts.pory"
	.string "become the greatest bird master!$"
# 102 "data/maps/VioletCity_Gym/scripts.pory"

# 103 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_Rematch:
# 104 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Congratulations on defeating\n"
# 105 "data/maps/VioletCity_Gym/scripts.pory"
	.string "the ELITE 4!\p"
# 106 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I've been training my\n"
# 107 "data/maps/VioletCity_Gym/scripts.pory"
	.string "FLYING-type POKéMON even harder.\p"
# 108 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Think you can take on the power\n"
# 109 "data/maps/VioletCity_Gym/scripts.pory"
	.string "of the skies again?$"
# 110 "data/maps/VioletCity_Gym/scripts.pory"

# 111 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_RematchLoss:
# 112 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Wow… You beat me again.\p"
# 113 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'm going to train harder to\n"
# 114 "data/maps/VioletCity_Gym/scripts.pory"
	.string "become the greatest bird master!$"
# 115 "data/maps/VioletCity_Gym/scripts.pory"

# 116 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperRod_Seen:
# 117 "data/maps/VioletCity_Gym/scripts.pory"
	.string "The keyword is guts!\p"
# 118 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Those here are training night and\n"
# 119 "data/maps/VioletCity_Gym/scripts.pory"
	.string "day to become bird POKéMON masters.\p"
# 120 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Come on!$"
# 121 "data/maps/VioletCity_Gym/scripts.pory"

# 122 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperRod_Beaten:
# 123 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Gaaah!$"
# 124 "data/maps/VioletCity_Gym/scripts.pory"

# 125 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperRod_After:
# 126 "data/maps/VioletCity_Gym/scripts.pory"
	.string "FALKNER's skills are for real!\p"
# 127 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Don't get cocky just because\n"
# 128 "data/maps/VioletCity_Gym/scripts.pory"
	.string "you beat me!$"
# 129 "data/maps/VioletCity_Gym/scripts.pory"

# 130 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperAbe_Seen:
# 131 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Let me see if you are good\n"
# 132 "data/maps/VioletCity_Gym/scripts.pory"
	.string "enough to face FALKNER!$"
# 133 "data/maps/VioletCity_Gym/scripts.pory"

# 134 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperAbe_Beaten:
# 135 "data/maps/VioletCity_Gym/scripts.pory"
	.string "This can't be true!$"
# 136 "data/maps/VioletCity_Gym/scripts.pory"

# 137 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperAbe_After:
# 138 "data/maps/VioletCity_Gym/scripts.pory"
	.string "This is pathetic, losing to some\n"
# 139 "data/maps/VioletCity_Gym/scripts.pory"
	.string "rookie trainer…$"
# 140 "data/maps/VioletCity_Gym/scripts.pory"

# 141 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_GymGuide_Intro:
# 142 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Hey! What's up? I'm no trainer,\n"
# 143 "data/maps/VioletCity_Gym/scripts.pory"
	.string "but I can give some advice!\p"
# 144 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Believe me! If you believe, a\n"
# 145 "data/maps/VioletCity_Gym/scripts.pory"
	.string "championship dream can come true.\p"
# 146 "data/maps/VioletCity_Gym/scripts.pory"
	.string "You believe? Then listen.\p"
# 147 "data/maps/VioletCity_Gym/scripts.pory"
	.string "FALKNER's ace is a bulky owl\n"
# 148 "data/maps/VioletCity_Gym/scripts.pory"
	.string "that loves to eat BERRIES.\p"
# 149 "data/maps/VioletCity_Gym/scripts.pory"
	.string "While it's not the strongest,\n"
# 150 "data/maps/VioletCity_Gym/scripts.pory"
	.string "it can take a lot of hits.\p"
# 151 "data/maps/VioletCity_Gym/scripts.pory"
	.string "You can hurt it with ELECTRIC \n"
# 152 "data/maps/VioletCity_Gym/scripts.pory"
	.string "and ROCK-type moves, but watch out\l"
# 153 "data/maps/VioletCity_Gym/scripts.pory"
	.string "for MUD-SLAP!\p"
# 154 "data/maps/VioletCity_Gym/scripts.pory"
	.string "If you want more help, go visit the\n"
# 155 "data/maps/VioletCity_Gym/scripts.pory"
	.string "POKéMON ACADEMY.\p"
# 156 "data/maps/VioletCity_Gym/scripts.pory"
	.string "The students there really know\n"
# 157 "data/maps/VioletCity_Gym/scripts.pory"
	.string "their stuff!$"
# 158 "data/maps/VioletCity_Gym/scripts.pory"

# 159 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_GymGuide_Win:
# 160 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Nice battle! Keep it up,\n"
# 161 "data/maps/VioletCity_Gym/scripts.pory"
	.string "and you'll be the CHAMP in no\l"
# 162 "data/maps/VioletCity_Gym/scripts.pory"
	.string "time at all!$"
# 163 "data/maps/VioletCity_Gym/scripts.pory"

# 164 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Statue::
# 165 "data/maps/VioletCity_Gym/scripts.pory"
	lock
# 166 "data/maps/VioletCity_Gym/scripts.pory"
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Statue2
# 167 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
# 168 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 169 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 170 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 171 "data/maps/VioletCity_Gym/scripts.pory"

# 172 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Statue2::
# 173 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
# 174 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 175 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 176 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 177 "data/maps/VioletCity_Gym/scripts.pory"

# 178 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_Text_GymStatue:
# 179 "data/maps/VioletCity_Gym/scripts.pory"
	.string "VIOLET CITY POKéMON GYM$"
# 180 "data/maps/VioletCity_Gym/scripts.pory"

# 181 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_Text_GymStatueCertified:
# 182 "data/maps/VioletCity_Gym/scripts.pory"
	.string "VIOLET CITY POKéMON GYM\p"
# 183 "data/maps/VioletCity_Gym/scripts.pory"
	.string "FALKNER'S CERTIFIED TRAINERS:\n"
# 184 "data/maps/VioletCity_Gym/scripts.pory"
	.string "{PLAYER}$"
