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
	special Achievement_CheckAll
# 41 "data/maps/VioletCity_Gym/scripts.pory"
	setflag FLAG_DEFEATED_VIOLET_GYM
# 42 "data/maps/VioletCity_Gym/scripts.pory"
	addvar VAR_NUM_BADGES, 1
# 43 "data/maps/VioletCity_Gym/scripts.pory"
	setvar VAR_0x8008, 1
# 44 "data/maps/VioletCity_Gym/scripts.pory"
	call Common_EventScript_SetGymTrainers
# 45 "data/maps/VioletCity_Gym/scripts.pory"
	giveitem ITEM_TM_ROOST
# 46 "data/maps/VioletCity_Gym/scripts.pory"
	call violetExplainTm
# 47 "data/maps/VioletCity_Gym/scripts.pory"
	setvar VAR_VIOLET_CITY_STATE, 3
# 48 "data/maps/VioletCity_Gym/scripts.pory"
	clearflag FLAG_HIDE_TUESCANY
# 49 "data/maps/VioletCity_Gym/scripts.pory"
	setrespawn HEAL_LOCATION_VIOLET_CITY
# 50 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 51 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 52 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 53 "data/maps/VioletCity_Gym/scripts.pory"

# 54 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Falkner_Defeated::
# 55 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletGym_Text_Falkner_AfterFight, MSGBOX_DEFAULT
# 56 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 57 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 58 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 59 "data/maps/VioletCity_Gym/scripts.pory"

# 60 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_Intro:
# 61 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'm Falkner, the Violet Pokémon\n"
# 62 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Gym leader!\p"
# 63 "data/maps/VioletCity_Gym/scripts.pory"
	.string "People say you can clip\n"
# 64 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Flying-type Pokémon's wings\p"
# 65 "data/maps/VioletCity_Gym/scripts.pory"
	.string "with a jolt of electricity…\n"
# 66 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I won't allow such insults to bird\l"
# 67 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Pokémon!\p"
# 68 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'll show you the real power\n"
# 69 "data/maps/VioletCity_Gym/scripts.pory"
	.string "of the magnificent bird Pokémon!$"
# 70 "data/maps/VioletCity_Gym/scripts.pory"

# 71 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_WinLoss:
# 72 "data/maps/VioletCity_Gym/scripts.pory"
	.string "…Darn! My dad's cherished bird\n"
# 73 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Pokémon…\p"
# 74 "data/maps/VioletCity_Gym/scripts.pory"
	.string "All right. Take this.\p"
# 75 "data/maps/VioletCity_Gym/scripts.pory"
	.string "It's the official Pokémon League\n"
# 76 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Zephyrbadge.$"
# 77 "data/maps/VioletCity_Gym/scripts.pory"

# 78 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_ReceivedZephyrBadge:
# 79 "data/maps/VioletCity_Gym/scripts.pory"
	.string "{PLAYER} received Zephyrbadge.$"
# 80 "data/maps/VioletCity_Gym/scripts.pory"

# 81 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_BadgeExplain:
# 82 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Zephyrbadge allows Pokémon to\n"
# 83 "data/maps/VioletCity_Gym/scripts.pory"
	.string "use Flash, if they can\l"
# 84 "data/maps/VioletCity_Gym/scripts.pory"
	.string "learn it, anytime.\p"
# 85 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Here--take this too.$"
# 86 "data/maps/VioletCity_Gym/scripts.pory"

# 87 "data/maps/VioletCity_Gym/scripts.pory"

# 88 "data/maps/VioletCity_Gym/scripts.pory"

# 89 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_AfterFight:
# 90 "data/maps/VioletCity_Gym/scripts.pory"
	.string "There are Pokémon Gyms in cities\n"
# 91 "data/maps/VioletCity_Gym/scripts.pory"
	.string "and towns ahead.\p"
# 92 "data/maps/VioletCity_Gym/scripts.pory"
	.string "You should test your skills at\n"
# 93 "data/maps/VioletCity_Gym/scripts.pory"
	.string "these Gyms.\p"
# 94 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'm going to train harder to\n"
# 95 "data/maps/VioletCity_Gym/scripts.pory"
	.string "become the greatest bird master!$"
# 96 "data/maps/VioletCity_Gym/scripts.pory"

# 97 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_Rematch:
# 98 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Congratulations on defeating\n"
# 99 "data/maps/VioletCity_Gym/scripts.pory"
	.string "the Elite 4!\p"
# 100 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I've been training my\n"
# 101 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Flying-type Pokémon even harder.\p"
# 102 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Think you can take on the power\n"
# 103 "data/maps/VioletCity_Gym/scripts.pory"
	.string "of the skies again?$"
# 104 "data/maps/VioletCity_Gym/scripts.pory"

# 105 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_Falkner_RematchLoss:
# 106 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Wow… You beat me again.\p"
# 107 "data/maps/VioletCity_Gym/scripts.pory"
	.string "I'm going to train harder to\n"
# 108 "data/maps/VioletCity_Gym/scripts.pory"
	.string "become the greatest bird master!$"
# 109 "data/maps/VioletCity_Gym/scripts.pory"

# 110 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperRod_Seen:
# 111 "data/maps/VioletCity_Gym/scripts.pory"
	.string "The keyword is guts!\p"
# 112 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Those here are training night and\n"
# 113 "data/maps/VioletCity_Gym/scripts.pory"
	.string "day to become bird Pokémon masters.\p"
# 114 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Come on!$"
# 115 "data/maps/VioletCity_Gym/scripts.pory"

# 116 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperRod_Beaten:
# 117 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Gaaah!$"
# 118 "data/maps/VioletCity_Gym/scripts.pory"

# 119 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperRod_After:
# 120 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Falkner's skills are for real!\p"
# 121 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Don't get cocky just because\n"
# 122 "data/maps/VioletCity_Gym/scripts.pory"
	.string "you beat me!$"
# 123 "data/maps/VioletCity_Gym/scripts.pory"

# 124 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperAbe_Seen:
# 125 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Let me see if you are good\n"
# 126 "data/maps/VioletCity_Gym/scripts.pory"
	.string "enough to face Falkner!$"
# 127 "data/maps/VioletCity_Gym/scripts.pory"

# 128 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperAbe_Beaten:
# 129 "data/maps/VioletCity_Gym/scripts.pory"
	.string "This can't be true!$"
# 130 "data/maps/VioletCity_Gym/scripts.pory"

# 131 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_BirdKeeperAbe_After:
# 132 "data/maps/VioletCity_Gym/scripts.pory"
	.string "This is pathetic, losing to some\n"
# 133 "data/maps/VioletCity_Gym/scripts.pory"
	.string "rookie trainer…$"
# 134 "data/maps/VioletCity_Gym/scripts.pory"

# 135 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_GymGuide_Intro:
# 136 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Hey! What's up? I'm no trainer,\n"
# 137 "data/maps/VioletCity_Gym/scripts.pory"
	.string "but I can give some advice!\p"
# 138 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Believe me! If you believe, a\n"
# 139 "data/maps/VioletCity_Gym/scripts.pory"
	.string "championship dream can come true.\p"
# 140 "data/maps/VioletCity_Gym/scripts.pory"
	.string "You believe? Then listen.\p"
# 141 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Falkner's ace is a bulky bird\n"
# 142 "data/maps/VioletCity_Gym/scripts.pory"
	.string "that loves to eat Berries.\p"
# 143 "data/maps/VioletCity_Gym/scripts.pory"
	.string "While it's not the strongest,\n"
# 144 "data/maps/VioletCity_Gym/scripts.pory"
	.string "it can take a lot of hits.\p"
# 145 "data/maps/VioletCity_Gym/scripts.pory"
	.string "You can hurt it with Electric \n"
# 146 "data/maps/VioletCity_Gym/scripts.pory"
	.string "and Rock-type moves, but watch out\l"
# 147 "data/maps/VioletCity_Gym/scripts.pory"
	.string "for Mud-Slap!\p"
# 148 "data/maps/VioletCity_Gym/scripts.pory"
	.string "If you want more help, go visit the\n"
# 149 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Pokémon Academy.\p"
# 150 "data/maps/VioletCity_Gym/scripts.pory"
	.string "The students there really know\n"
# 151 "data/maps/VioletCity_Gym/scripts.pory"
	.string "their stuff!$"
# 152 "data/maps/VioletCity_Gym/scripts.pory"

# 153 "data/maps/VioletCity_Gym/scripts.pory"
VioletGym_Text_GymGuide_Win:
# 154 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Nice battle! Keep it up,\n"
# 155 "data/maps/VioletCity_Gym/scripts.pory"
	.string "and you'll be the Champ in no\l"
# 156 "data/maps/VioletCity_Gym/scripts.pory"
	.string "time at all!$"
# 157 "data/maps/VioletCity_Gym/scripts.pory"

# 158 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Statue::
# 159 "data/maps/VioletCity_Gym/scripts.pory"
	lock
# 160 "data/maps/VioletCity_Gym/scripts.pory"
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Statue2
# 161 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
# 162 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 163 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 164 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 165 "data/maps/VioletCity_Gym/scripts.pory"

# 166 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_EventScript_Statue2::
# 167 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox VioletCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
# 168 "data/maps/VioletCity_Gym/scripts.pory"
	closemessage
# 169 "data/maps/VioletCity_Gym/scripts.pory"
	release
# 170 "data/maps/VioletCity_Gym/scripts.pory"
	end
# 171 "data/maps/VioletCity_Gym/scripts.pory"

# 172 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_Text_GymStatue:
# 173 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Violet City Pokémon Gym$"
# 174 "data/maps/VioletCity_Gym/scripts.pory"

# 175 "data/maps/VioletCity_Gym/scripts.pory"
VioletCity_Gym_Text_GymStatueCertified:
# 176 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Violet City Pokémon Gym\p"
# 177 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Falkner's Certified Trainers:\n"
# 178 "data/maps/VioletCity_Gym/scripts.pory"
	.string "{PLAYER}$"

violetExplainTm::
# 182 "data/maps/VioletCity_Gym/scripts.pory"
	msgbox violetExplainTm_Text_0
	return


violetExplainTm_Text_0:
# 182 "data/maps/VioletCity_Gym/scripts.pory"
	.string "Pokémon can learn new moves with TMs.\p"
	.string "This one contains Roost, which restores\n"
	.string "HP to Flying-type Pokémon.\p"
	.string "You may use it as many times as you\n"
	.string "want.\p"
	.string "Your next stop should be Azalea Town.\n"
	.string "Good luck.$"
