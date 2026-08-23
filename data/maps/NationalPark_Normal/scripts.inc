# 1 "data/maps/NationalPark_Normal/scripts.pory"

# 2 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_MapScripts::
# 3 "data/maps/NationalPark_Normal/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, NationalPark_Normal_OnTransition
# 4 "data/maps/NationalPark_Normal/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 5 "data/maps/NationalPark_Normal/scripts.pory"
	.byte 0
# 6 "data/maps/NationalPark_Normal/scripts.pory"

# 7 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_OnTransition: 
# 8 "data/maps/NationalPark_Normal/scripts.pory"
	callnative SetTimeBasedEncounters
# 9 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 10 "data/maps/NationalPark_Normal/scripts.pory"

# 11 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Lass::
# 12 "data/maps/NationalPark_Normal/scripts.pory"
	lock
# 13 "data/maps/NationalPark_Normal/scripts.pory"
	faceplayer
# 14 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_Lass, MSGBOX_DEFAULT
# 15 "data/maps/NationalPark_Normal/scripts.pory"
	closemessage
# 16 "data/maps/NationalPark_Normal/scripts.pory"
	release
# 17 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 18 "data/maps/NationalPark_Normal/scripts.pory"

# 19 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Youngster1::
# 20 "data/maps/NationalPark_Normal/scripts.pory"
	lock
# 21 "data/maps/NationalPark_Normal/scripts.pory"
	faceplayer
# 22 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_Youngster1, MSGBOX_DEFAULT
# 23 "data/maps/NationalPark_Normal/scripts.pory"
	closemessage
# 24 "data/maps/NationalPark_Normal/scripts.pory"
	release
# 25 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 26 "data/maps/NationalPark_Normal/scripts.pory"

# 27 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Youngster2::
# 28 "data/maps/NationalPark_Normal/scripts.pory"
	lock
# 29 "data/maps/NationalPark_Normal/scripts.pory"
	faceplayer
# 30 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_Youngster2, MSGBOX_DEFAULT
# 31 "data/maps/NationalPark_Normal/scripts.pory"
	closemessage
# 32 "data/maps/NationalPark_Normal/scripts.pory"
	release
# 33 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 34 "data/maps/NationalPark_Normal/scripts.pory"

# 35 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Teacher2::
# 36 "data/maps/NationalPark_Normal/scripts.pory"
	lock
# 37 "data/maps/NationalPark_Normal/scripts.pory"
	faceplayer
# 38 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_Teacher2, MSGBOX_DEFAULT
# 39 "data/maps/NationalPark_Normal/scripts.pory"
	closemessage
# 40 "data/maps/NationalPark_Normal/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 41 "data/maps/NationalPark_Normal/scripts.pory"
	release
# 42 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 43 "data/maps/NationalPark_Normal/scripts.pory"

# 44 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_TeacherQuickclaw::
# 45 "data/maps/NationalPark_Normal/scripts.pory"
	lock
# 46 "data/maps/NationalPark_Normal/scripts.pory"
	faceplayer
# 47 "data/maps/NationalPark_Normal/scripts.pory"
	goto_if_set FLAG_GOT_QUICK_CLAW, NationalPark_Normal_EventScript_TeacherQuickclaw2
# 48 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_Teacher1, MSGBOX_DEFAULT
# 49 "data/maps/NationalPark_Normal/scripts.pory"
	giveitem ITEM_QUICK_CLAW
# 50 "data/maps/NationalPark_Normal/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 51 "data/maps/NationalPark_Normal/scripts.pory"
	setflag FLAG_GOT_QUICK_CLAW
# 52 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_TeacherQuickclaw2::
# 53 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_Teacher1_QuickClaw, MSGBOX_DEFAULT
# 54 "data/maps/NationalPark_Normal/scripts.pory"
	closemessage
# 55 "data/maps/NationalPark_Normal/scripts.pory"
	release
# 56 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 57 "data/maps/NationalPark_Normal/scripts.pory"

# 58 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Persian::
# 59 "data/maps/NationalPark_Normal/scripts.pory"
	lock
# 60 "data/maps/NationalPark_Normal/scripts.pory"
	faceplayer
# 61 "data/maps/NationalPark_Normal/scripts.pory"
	waitse
# 62 "data/maps/NationalPark_Normal/scripts.pory"
	playmoncry SPECIES_PERSIAN, CRY_MODE_NORMAL
# 63 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_Persian, MSGBOX_DEFAULT
# 64 "data/maps/NationalPark_Normal/scripts.pory"
	waitmoncry
# 65 "data/maps/NationalPark_Normal/scripts.pory"
	release
# 66 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 67 "data/maps/NationalPark_Normal/scripts.pory"

# 68 "data/maps/NationalPark_Normal/scripts.pory"

# 69 "data/maps/NationalPark_Normal/scripts.pory"

# 70 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Lass:
# 71 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Look! Check out my bag!\p"
# 72 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I printed out my favorites from my\n"
# 73 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Pokédex and stuck them on my bag.$"
# 74 "data/maps/NationalPark_Normal/scripts.pory"

# 75 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_PokefanF:
# 76 "data/maps/NationalPark_Normal/scripts.pory"
	.string "This is Mail I got from my daughter.\n"
# 77 "data/maps/NationalPark_Normal/scripts.pory"
	.string "It cheers me up.$"
# 78 "data/maps/NationalPark_Normal/scripts.pory"

# 79 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Teacher1:
# 80 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Pay attention, please!\p"
# 81 "data/maps/NationalPark_Normal/scripts.pory"
	.string "…Oops, I have to quit thinking like\n"
# 82 "data/maps/NationalPark_Normal/scripts.pory"
	.string "a teacher all the time.\p"
# 83 "data/maps/NationalPark_Normal/scripts.pory"
	.string "You must be a Pokémon trainer.\p"
# 84 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Since you're working so hard, I\n"
# 85 "data/maps/NationalPark_Normal/scripts.pory"
	.string "want you to have this.$"
# 86 "data/maps/NationalPark_Normal/scripts.pory"

# 87 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Teacher1_QuickClaw:
# 88 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Let a Pokémon hold that Quick Claw.\p"
# 89 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Sometimes it will strike first\n"
# 90 "data/maps/NationalPark_Normal/scripts.pory"
	.string "during battle.$"
# 91 "data/maps/NationalPark_Normal/scripts.pory"

# 92 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Youngster1:
# 93 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I'm playing with stickers I printed\n"
# 94 "data/maps/NationalPark_Normal/scripts.pory"
	.string "from my Pokédex.$"
# 95 "data/maps/NationalPark_Normal/scripts.pory"

# 96 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Youngster2:
# 97 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I get the other guy's Pokédex sticker\n"
# 98 "data/maps/NationalPark_Normal/scripts.pory"
	.string "if I win.$"
# 99 "data/maps/NationalPark_Normal/scripts.pory"

# 100 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Teacher2:
# 101 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I take walks in the Park, but I\n"
# 102 "data/maps/NationalPark_Normal/scripts.pory"
	.string "never go into the grass.\p"
# 103 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Trainers always want to battle…\p"
# 104 "data/maps/NationalPark_Normal/scripts.pory"
	.string "You must have been in many battles.\n"
# 105 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Let me heal your Pokémon for you.$"
# 106 "data/maps/NationalPark_Normal/scripts.pory"

# 107 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Persian:
# 108 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Persian: Fufushaa!$"
# 109 "data/maps/NationalPark_Normal/scripts.pory"

# 110 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Jack::
# 111 "data/maps/NationalPark_Normal/scripts.pory"
	trainerbattle_single TRAINER_JACK NationalPark_Normal_Text_SchoolboyJack1_Seen, NationalPark_Normal_Text_SchoolboyJack1_Beaten
# 112 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_SchoolboyJack_After, MSGBOX_AUTOCLOSE
# 113 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 114 "data/maps/NationalPark_Normal/scripts.pory"

# 115 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Beverly::
# 116 "data/maps/NationalPark_Normal/scripts.pory"
	trainerbattle_single TRAINER_BEVERLY NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten
# 117 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
# 118 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 119 "data/maps/NationalPark_Normal/scripts.pory"

# 120 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_William::
# 121 "data/maps/NationalPark_Normal/scripts.pory"
	trainerbattle_single TRAINER_WILLIAM NationalPark_Normal_Text_PokefanmWilliam_Seen, NationalPark_Normal_Text_PokefanmWilliam_Beaten
# 122 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_PokefanmWilliam_After, MSGBOX_AUTOCLOSE
# 123 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 124 "data/maps/NationalPark_Normal/scripts.pory"

# 125 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_EventScript_Krise::
# 126 "data/maps/NationalPark_Normal/scripts.pory"
	trainerbattle_single TRAINER_KRISE NationalPark_Normal_Text_LassKrise_Seen, NationalPark_Normal_Text_LassKrise_Beaten
# 127 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_Normal_Text_LassKrise_After, MSGBOX_AUTOCLOSE
# 128 "data/maps/NationalPark_Normal/scripts.pory"
	end
# 129 "data/maps/NationalPark_Normal/scripts.pory"

# 130 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_SchoolboyJack1_Seen:
# 131 "data/maps/NationalPark_Normal/scripts.pory"
	.string "The world of Pokémon is deep.\p"
# 132 "data/maps/NationalPark_Normal/scripts.pory"
	.string "There are still lots of things we\n"
# 133 "data/maps/NationalPark_Normal/scripts.pory"
	.string "don't know.\p"
# 134 "data/maps/NationalPark_Normal/scripts.pory"
	.string "But I know more than you do!$"
# 135 "data/maps/NationalPark_Normal/scripts.pory"

# 136 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_SchoolboyJack1_Beaten:
# 137 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Wha-wha-what?$"
# 138 "data/maps/NationalPark_Normal/scripts.pory"

# 139 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_SchoolboyJack_After:
# 140 "data/maps/NationalPark_Normal/scripts.pory"
	.string "There is a lot to learn.\p"
# 141 "data/maps/NationalPark_Normal/scripts.pory"
	.string "For example…\p"
# 142 "data/maps/NationalPark_Normal/scripts.pory"
	.string "There are 100 kinds of TMs.\p"
# 143 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Traded Pokémon level up faster.$"
# 144 "data/maps/NationalPark_Normal/scripts.pory"

# 145 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_PokefanFBeverly1_Seen:
# 146 "data/maps/NationalPark_Normal/scripts.pory"
	.string "My Pokémon are simply darling.\p"
# 147 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Let me tell you how proud my\n"
# 148 "data/maps/NationalPark_Normal/scripts.pory"
	.string "darlings make me.$"
# 149 "data/maps/NationalPark_Normal/scripts.pory"

# 150 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_PokefanFBeverly1_Beaten:
# 151 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I can beat you in pride, but…$"
# 152 "data/maps/NationalPark_Normal/scripts.pory"

# 153 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_PokefanFBeverly_After:
# 154 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I must say, your Pokémon are quite\n"
# 155 "data/maps/NationalPark_Normal/scripts.pory"
	.string "cute, too.$"
# 156 "data/maps/NationalPark_Normal/scripts.pory"

# 157 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_PokefanmWilliam_Seen:
# 158 "data/maps/NationalPark_Normal/scripts.pory"
	.string "We adore our Pokémon, even if they\n"
# 159 "data/maps/NationalPark_Normal/scripts.pory"
	.string "dislike us.\p"
# 160 "data/maps/NationalPark_Normal/scripts.pory"
	.string "That's what being a Fan is about.$"
# 161 "data/maps/NationalPark_Normal/scripts.pory"

# 162 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_PokefanmWilliam_Beaten:
# 163 "data/maps/NationalPark_Normal/scripts.pory"
	.string "M-my Pokémon!$"
# 164 "data/maps/NationalPark_Normal/scripts.pory"

# 165 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_PokefanmWilliam_After:
# 166 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I lost the battle, but my Pokémon win\n"
# 167 "data/maps/NationalPark_Normal/scripts.pory"
	.string "the prize for being most lovely.$"
# 168 "data/maps/NationalPark_Normal/scripts.pory"

# 169 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_LassKrise_Seen:
# 170 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Hello? Why are you staring at me?\p"
# 171 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Oh, a battle?$"
# 172 "data/maps/NationalPark_Normal/scripts.pory"

# 173 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_LassKrise_Beaten:
# 174 "data/maps/NationalPark_Normal/scripts.pory"
	.string "…Hmmm…$"
# 175 "data/maps/NationalPark_Normal/scripts.pory"

# 176 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_LassKrise_After:
# 177 "data/maps/NationalPark_Normal/scripts.pory"
	.string "I thought you were staring at me\n"
# 178 "data/maps/NationalPark_Normal/scripts.pory"
	.string "because I'm cute!$"
# 179 "data/maps/NationalPark_Normal/scripts.pory"

# 180 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Sign_RelaxationSquare:
# 181 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Relaxation Square\n"
# 182 "data/maps/NationalPark_Normal/scripts.pory"
	.string "National Park$"
# 183 "data/maps/NationalPark_Normal/scripts.pory"

# 184 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_Sign_BattleNotice:
# 185 "data/maps/NationalPark_Normal/scripts.pory"
	.string "What is this notice?\p"
# 186 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Please battle only in the grass.\p"
# 187 "data/maps/NationalPark_Normal/scripts.pory"
	.string "National Park Warden's Office$"
# 188 "data/maps/NationalPark_Normal/scripts.pory"

# 189 "data/maps/NationalPark_Normal/scripts.pory"
NationalPark_Normal_Text_TrainerTips:
# 190 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Trainer Tips\p"
# 191 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Print out Mail by opening it then\n"
# 192 "data/maps/NationalPark_Normal/scripts.pory"
	.string "pressing Start.$"

NationalPark_BugsyRematch::
# 196 "data/maps/NationalPark_Normal/scripts.pory"
	lock
# 197 "data/maps/NationalPark_Normal/scripts.pory"
	faceplayer
# 198 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_BugsyRematch_Text_0, MSGBOX_YESNO
# 207 "data/maps/NationalPark_Normal/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq NationalPark_BugsyRematch_2
NationalPark_BugsyRematch_1:
# 224 "data/maps/NationalPark_Normal/scripts.pory"
	release
	end

NationalPark_BugsyRematch_2:
# 208 "data/maps/NationalPark_Normal/scripts.pory"
	trainerbattle_no_intro TRAINER_BUGSY_2, NationalPark_BugsyRematch_Text_1
# 209 "data/maps/NationalPark_Normal/scripts.pory"
	msgbox NationalPark_BugsyRematch_Text_2
# 217 "data/maps/NationalPark_Normal/scripts.pory"
	closemessage
# 218 "data/maps/NationalPark_Normal/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 219 "data/maps/NationalPark_Normal/scripts.pory"
	setflag FLAG_HIDE_NATIONAL_BUGSY
# 220 "data/maps/NationalPark_Normal/scripts.pory"
	removeobject LOCALID_NATIONAL_BUGSY
# 221 "data/maps/NationalPark_Normal/scripts.pory"
	delay 30
# 222 "data/maps/NationalPark_Normal/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
	goto NationalPark_BugsyRematch_1


NationalPark_BugsyRematch_Text_0:
# 198 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Heyo, {PLAYER}!\p"
	.string "I'm checking on the Bug Pokémon here in\n"
	.string "Ilex, making sure any ruffians are not\l"
	.string "causing trouble to them.\p"
	.string "I've gotten quite a bit stronger since\n"
	.string "we last fought, how about I show it to\l"
	.string "you?$"

NationalPark_BugsyRematch_Text_1:
# 208 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Way to go! You're crazy strong!$"

NationalPark_BugsyRematch_Text_2:
# 209 "data/maps/NationalPark_Normal/scripts.pory"
	.string "Looks like my team still got ways to go\n"
	.string "if I want to beat you.\p"
	.string "Maybe we should have another tussle\n"
	.string "like this once everyone has gotten\l"
	.string "together. \p"
	.string "Until then, laters!$"
