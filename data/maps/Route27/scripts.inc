# 1 "data/maps/Route27/scripts.pory"

# 2 "data/maps/Route27/scripts.pory"

# 3 "data/maps/Route27/scripts.pory"
Route27_MapScripts::
# 4 "data/maps/Route27/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route27_OnTransition
# 5 "data/maps/Route27/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 6 "data/maps/Route27/scripts.pory"
	.byte 0
# 7 "data/maps/Route27/scripts.pory"

# 8 "data/maps/Route27/scripts.pory"
Route27_OnTransition: 
# 9 "data/maps/Route27/scripts.pory"
	callnative SetTimeBasedEncounters
# 10 "data/maps/Route27/scripts.pory"
	end
# 11 "data/maps/Route27/scripts.pory"

# 12 "data/maps/Route27/scripts.pory"
Route27_EventScript_BaobaCall::
# 13 "data/maps/Route27/scripts.pory"
	pokenavcall BlackthornCity_Text_BaobaCall
# 14 "data/maps/Route27/scripts.pory"
	waitmessage
# 15 "data/maps/Route27/scripts.pory"
	delay 30
# 16 "data/maps/Route27/scripts.pory"
	setflag FLAG_SAFARI_ZONE_WEST_EXPANSION
# 17 "data/maps/Route27/scripts.pory"
    setvar VAR_ROUTE27_BAOBA_CALL, 1
# 18 "data/maps/Route27/scripts.pory"
	end
# 19 "data/maps/Route27/scripts.pory"

# 20 "data/maps/Route27/scripts.pory"
Route27_Movement_WalkTop:
# 21 "data/maps/Route27/scripts.pory"
    face_left
# 22 "data/maps/Route27/scripts.pory"
    walk_left
# 23 "data/maps/Route27/scripts.pory"
    step_end
# 24 "data/maps/Route27/scripts.pory"

# 25 "data/maps/Route27/scripts.pory"
Route27_Movement_WalkBot:
# 26 "data/maps/Route27/scripts.pory"
    walk_down
# 27 "data/maps/Route27/scripts.pory"
    walk_left
# 28 "data/maps/Route27/scripts.pory"
    step_end
# 29 "data/maps/Route27/scripts.pory"

# 30 "data/maps/Route27/scripts.pory"
Route27_EventScript_Fatman::
# 31 "data/maps/Route27/scripts.pory"
    msgbox Route27_Text_FisherMessage, MSGBOX_NPC
# 32 "data/maps/Route27/scripts.pory"
    end
# 33 "data/maps/Route27/scripts.pory"

# 34 "data/maps/Route27/scripts.pory"
Route27_EventScript_Blake::
# 35 "data/maps/Route27/scripts.pory"
	trainerbattle_single TRAINER_BLAKE Route27_Text_CooltrainermBlakeSeen, Route27_Text_CooltrainermBlakeBeaten
# 36 "data/maps/Route27/scripts.pory"
	msgbox Route27_Text_CooltrainermBlakeAfter, MSGBOX_AUTOCLOSE
# 37 "data/maps/Route27/scripts.pory"
	end
# 38 "data/maps/Route27/scripts.pory"

# 39 "data/maps/Route27/scripts.pory"
Route27_EventScript_Brian::
# 40 "data/maps/Route27/scripts.pory"
	trainerbattle_single TRAINER_BRIAN Route27_Text_CooltrainermBrianSeen, Route27_Text_CooltrainermBrianBeaten
# 41 "data/maps/Route27/scripts.pory"
	msgbox Route27_Text_CooltrainermBrianAfter, MSGBOX_AUTOCLOSE
# 42 "data/maps/Route27/scripts.pory"
	end
# 43 "data/maps/Route27/scripts.pory"

# 44 "data/maps/Route27/scripts.pory"
Route27_EventScript_Reena::
# 45 "data/maps/Route27/scripts.pory"
	trainerbattle_single TRAINER_REENA Route27_Text_CooltrainerfReenaSeen, Route27_Text_CooltrainerfReenaBeaten
# 46 "data/maps/Route27/scripts.pory"
	msgbox Route27_Text_CooltrainerfReenaAfter, MSGBOX_AUTOCLOSE
# 47 "data/maps/Route27/scripts.pory"
	end
# 48 "data/maps/Route27/scripts.pory"

# 49 "data/maps/Route27/scripts.pory"
Route27_EventScript_Megan::
# 50 "data/maps/Route27/scripts.pory"
	trainerbattle_single TRAINER_MEGAN Route27_Text_CooltrainerfMeganSeen, Route27_Text_CooltrainerfMeganBeaten
# 51 "data/maps/Route27/scripts.pory"
	msgbox Route27_Text_CooltrainerfMeganAfter, MSGBOX_AUTOCLOSE
# 52 "data/maps/Route27/scripts.pory"
	end
# 53 "data/maps/Route27/scripts.pory"

# 54 "data/maps/Route27/scripts.pory"
Route27_EventScript_Gilbert::
# 55 "data/maps/Route27/scripts.pory"
	trainerbattle_single TRAINER_GILBERT Route27_Text_PsychicGilbertSeen, Route27_Text_PsychicGilbertBeaten
# 56 "data/maps/Route27/scripts.pory"
	msgbox Route27_Text_PsychicGilbertAfter, MSGBOX_AUTOCLOSE
# 57 "data/maps/Route27/scripts.pory"
	end
# 58 "data/maps/Route27/scripts.pory"

# 59 "data/maps/Route27/scripts.pory"
Route27_EventScript_Jose::
# 60 "data/maps/Route27/scripts.pory"
	trainerbattle_single TRAINER_JOSE Route27_Text_BirdKeeperJoseSeen, Route27_Text_BirdKeeperJoseBeaten
# 61 "data/maps/Route27/scripts.pory"
	msgbox Route27_Text_BirdKeeperJoseAfter, MSGBOX_AUTOCLOSE
# 62 "data/maps/Route27/scripts.pory"
	end
# 63 "data/maps/Route27/scripts.pory"

# 64 "data/maps/Route27/scripts.pory"
Route27_EventScript_Scott::
# 65 "data/maps/Route27/scripts.pory"
	trainerbattle_single TRAINER_SCOTT Route27_Text_FisherScottSeen, Route27_Text_FisherScottBeaten
# 66 "data/maps/Route27/scripts.pory"
	msgbox Route27_Text_FisherScottAfter, MSGBOX_AUTOCLOSE
# 67 "data/maps/Route27/scripts.pory"
	end
# 68 "data/maps/Route27/scripts.pory"

# 69 "data/maps/Route27/scripts.pory"
Route27_EventScript_TohjoFallsSign::
# 70 "data/maps/Route27/scripts.pory"
    msgbox TohjoFalls_Text_Sign, MSGBOX_SIGN
# 71 "data/maps/Route27/scripts.pory"
    end
# 72 "data/maps/Route27/scripts.pory"

# 73 "data/maps/Route27/scripts.pory"
Route27_Text_FisherHey:
# 74 "data/maps/Route27/scripts.pory"
    .string "Hey!$"
# 75 "data/maps/Route27/scripts.pory"

# 76 "data/maps/Route27/scripts.pory"
Route27_Text_FisherMessage:
# 77 "data/maps/Route27/scripts.pory"
    .string "Do you know what you just did?\p"
# 78 "data/maps/Route27/scripts.pory"
    .string "You've taken your first step into\n"
# 79 "data/maps/Route27/scripts.pory"
    .string "Kanto.\p"
# 80 "data/maps/Route27/scripts.pory"
    .string "Check your Pokégear Map and see.$"
# 81 "data/maps/Route27/scripts.pory"

# 82 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainermBlakeSeen:
# 83 "data/maps/Route27/scripts.pory"
    .string "You look pretty strong.\n"
# 84 "data/maps/Route27/scripts.pory"
    .string "Let me battle you!$"
# 85 "data/maps/Route27/scripts.pory"

# 86 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainermBlakeBeaten:
# 87 "data/maps/Route27/scripts.pory"
    .string "Yow!$"
# 88 "data/maps/Route27/scripts.pory"

# 89 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainermBlakeAfter:
# 90 "data/maps/Route27/scripts.pory"
    .string "If you prevail on this harsh trek,\p"
# 91 "data/maps/Route27/scripts.pory"
    .string "the truth will be revealed!\p"
# 92 "data/maps/Route27/scripts.pory"
    .string "Heh, sorry, I just wanted to say\n"
# 93 "data/maps/Route27/scripts.pory"
    .string "something cool.$"
# 94 "data/maps/Route27/scripts.pory"

# 95 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainermBrianSeen:
# 96 "data/maps/Route27/scripts.pory"
    .string "Hm? You're good, aren't you?$"
# 97 "data/maps/Route27/scripts.pory"

# 98 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainermBrianBeaten:
# 99 "data/maps/Route27/scripts.pory"
    .string "Just as I thought!$"
# 100 "data/maps/Route27/scripts.pory"

# 101 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainermBrianAfter:
# 102 "data/maps/Route27/scripts.pory"
    .string "A good trainer can recognize other\n"
# 103 "data/maps/Route27/scripts.pory"
    .string "good trainers.$"
# 104 "data/maps/Route27/scripts.pory"

# 105 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainerfReenaSeen:
# 106 "data/maps/Route27/scripts.pory"
    .string "You shouldn't underestimate the\n"
# 107 "data/maps/Route27/scripts.pory"
    .string "wild Pokémon in these parts.$"
# 108 "data/maps/Route27/scripts.pory"

# 109 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainerfReenaBeaten:
# 110 "data/maps/Route27/scripts.pory"
    .string "Oh! You're much too strong!$"
# 111 "data/maps/Route27/scripts.pory"

# 112 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainerfReenaAfter:
# 113 "data/maps/Route27/scripts.pory"
    .string "You're just a kid, but you're not\n"
# 114 "data/maps/Route27/scripts.pory"
    .string "to be underestimated either.$"
# 115 "data/maps/Route27/scripts.pory"

# 116 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainerfMeganSeen:
# 117 "data/maps/Route27/scripts.pory"
    .string "It's rare to see anyone come here.\p"
# 118 "data/maps/Route27/scripts.pory"
    .string "Are you training on your own?$"
# 119 "data/maps/Route27/scripts.pory"

# 120 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainerfMeganBeaten:
# 121 "data/maps/Route27/scripts.pory"
    .string "Oh! You're really strong!$"
# 122 "data/maps/Route27/scripts.pory"

# 123 "data/maps/Route27/scripts.pory"
Route27_Text_CooltrainerfMeganAfter:
# 124 "data/maps/Route27/scripts.pory"
    .string "I'm checking out pre- and post-\n"
# 125 "data/maps/Route27/scripts.pory"
    .string "evolution Pokémon.\p"
# 126 "data/maps/Route27/scripts.pory"
    .string "Evolution really does make\n"
# 127 "data/maps/Route27/scripts.pory"
    .string "Pokémon stronger.\p"
# 128 "data/maps/Route27/scripts.pory"
    .string "But evolved forms also learn\n"
# 129 "data/maps/Route27/scripts.pory"
    .string "moves later on.$"
# 130 "data/maps/Route27/scripts.pory"

# 131 "data/maps/Route27/scripts.pory"
Route27_Text_PsychicGilbertSeen:
# 132 "data/maps/Route27/scripts.pory"
    .string "Don't say a thing!\p"
# 133 "data/maps/Route27/scripts.pory"
    .string "Let me guess what you're thinking.\p"
# 134 "data/maps/Route27/scripts.pory"
    .string "Mmmmmmm…\p"
# 135 "data/maps/Route27/scripts.pory"
    .string "I got it! You're on the Pokémon\n"
# 136 "data/maps/Route27/scripts.pory"
    .string "League challenge!$"
# 137 "data/maps/Route27/scripts.pory"

# 138 "data/maps/Route27/scripts.pory"
Route27_Text_PsychicGilbertBeaten:
# 139 "data/maps/Route27/scripts.pory"
    .string "You're too much!$"
# 140 "data/maps/Route27/scripts.pory"

# 141 "data/maps/Route27/scripts.pory"
Route27_Text_PsychicGilbertAfter:
# 142 "data/maps/Route27/scripts.pory"
    .string "With your skills, you'll do well at\n"
# 143 "data/maps/Route27/scripts.pory"
    .string "the League.\p"
# 144 "data/maps/Route27/scripts.pory"
    .string "That's what my premonition says.$"
# 145 "data/maps/Route27/scripts.pory"

# 146 "data/maps/Route27/scripts.pory"
Route27_Text_BirdKeeperJoseSeen:
# 147 "data/maps/Route27/scripts.pory"
    .string "Tweet! Tweet! Tetweet!$"
# 148 "data/maps/Route27/scripts.pory"

# 149 "data/maps/Route27/scripts.pory"
Route27_Text_BirdKeeperJoseBeaten:
# 150 "data/maps/Route27/scripts.pory"
    .string "Tweet!$"
# 151 "data/maps/Route27/scripts.pory"

# 152 "data/maps/Route27/scripts.pory"
Route27_Text_BirdKeeperJoseAfter:
# 153 "data/maps/Route27/scripts.pory"
    .string "Bird Keepers like me mimic bird\n"
# 154 "data/maps/Route27/scripts.pory"
    .string "whistles to command Pokémon.$"
# 155 "data/maps/Route27/scripts.pory"

# 156 "data/maps/Route27/scripts.pory"
TohjoFalls_Text_Sign:
# 157 "data/maps/Route27/scripts.pory"
    .string "Tohjo Falls\p"
# 158 "data/maps/Route27/scripts.pory"
    .string "The Link Between Kanto And Johto$"
# 159 "data/maps/Route27/scripts.pory"

# 160 "data/maps/Route27/scripts.pory"
Route27_Text_FisherScottSeen:
# 161 "data/maps/Route27/scripts.pory"
    .string "I'm feeling great today!\p"
# 162 "data/maps/Route27/scripts.pory"
    .string "I feel like I could boot even the\n"
# 163 "data/maps/Route27/scripts.pory"
    .string "League Champ!$"
# 164 "data/maps/Route27/scripts.pory"

# 165 "data/maps/Route27/scripts.pory"
Route27_Text_FisherScottBeaten:
# 166 "data/maps/Route27/scripts.pory"
    .string "No! Not in this battle!$"
# 167 "data/maps/Route27/scripts.pory"

# 168 "data/maps/Route27/scripts.pory"
Route27_Text_FisherScottAfter:
# 169 "data/maps/Route27/scripts.pory"
    .string "Just like in fish-ing, it's all over\n"
# 170 "data/maps/Route27/scripts.pory"
    .string "in Pokémon if you give up.$"

Route27_RouteExpert::
# 174 "data/maps/Route27/scripts.pory"
	lock
# 175 "data/maps/Route27/scripts.pory"
	faceplayer
# 176 "data/maps/Route27/scripts.pory"
	goto_if_set FLAG_ROUTE27_EXPERT, Route27_RouteExpert_2
# 185 "data/maps/Route27/scripts.pory"
	msgbox Route27_RouteExpert_Text_1
# 195 "data/maps/Route27/scripts.pory"
	goto_if_set FLAG_ROUTE27_EXPERT_QUALIFIED, Route27_RouteExpert_5
# 195 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_BLAKE
	goto_if 1, Route27_RouteExpert_9
Route27_RouteExpert_4:
# 228 "data/maps/Route27/scripts.pory"
	release
	end

Route27_RouteExpert_2:
# 177 "data/maps/Route27/scripts.pory"
	setflag FLAG_ROUTE27_EXPERT_QUALIFIED
# 178 "data/maps/Route27/scripts.pory"
	msgbox Route27_RouteExpert_Text_0
# 181 "data/maps/Route27/scripts.pory"
	release
	end

Route27_RouteExpert_5:
# 208 "data/maps/Route27/scripts.pory"
	setflag FLAG_ROUTE27_EXPERT_QUALIFIED
# 209 "data/maps/Route27/scripts.pory"
	playse SE_PIN
# 210 "data/maps/Route27/scripts.pory"
	applymovement LOCALID_ROUTE27_EXPERT, Common_Movement_ExclamationMark
# 211 "data/maps/Route27/scripts.pory"
	waitse
# 212 "data/maps/Route27/scripts.pory"
	msgbox Route27_RouteExpert_Text_2
# 216 "data/maps/Route27/scripts.pory"
	trainerbattle_no_intro TRAINER_CHOICE_BAND_EXPERT, Route27_RouteExpert_Text_3
# 217 "data/maps/Route27/scripts.pory"
	msgbox Route27_RouteExpert_Text_4
# 220 "data/maps/Route27/scripts.pory"
	giveitem ITEM_CHOICE_BAND
# 221 "data/maps/Route27/scripts.pory"
	setflag FLAG_ROUTE27_EXPERT
# 222 "data/maps/Route27/scripts.pory"
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
# 223 "data/maps/Route27/scripts.pory"
	special Achievement_CheckAll
# 224 "data/maps/Route27/scripts.pory"
	msgbox Route27_RouteExpert_Text_0
	goto Route27_RouteExpert_4

Route27_RouteExpert_8:
# 197 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_REENA
	goto_if 1, Route27_RouteExpert_13
	goto Route27_RouteExpert_4

Route27_RouteExpert_9:
# 196 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_BRIAN
	goto_if 1, Route27_RouteExpert_8
	goto Route27_RouteExpert_4

Route27_RouteExpert_12:
# 199 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_GILBERT
	goto_if 1, Route27_RouteExpert_17
	goto Route27_RouteExpert_4

Route27_RouteExpert_13:
# 198 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_MEGAN
	goto_if 1, Route27_RouteExpert_12
	goto Route27_RouteExpert_4

Route27_RouteExpert_16:
# 201 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_SCOTT
	goto_if 1, Route27_RouteExpert_21
	goto Route27_RouteExpert_4

Route27_RouteExpert_17:
# 200 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_JOSE
	goto_if 1, Route27_RouteExpert_16
	goto Route27_RouteExpert_4

Route27_RouteExpert_20:
# 204 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_GAVEN
	goto_if 1, Route27_RouteExpert_25
	goto Route27_RouteExpert_4

Route27_RouteExpert_21:
# 203 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_JAKE
	goto_if 1, Route27_RouteExpert_20
	goto Route27_RouteExpert_4

Route27_RouteExpert_24:
# 206 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_BETH
	goto_if 1, Route27_RouteExpert_28
	goto Route27_RouteExpert_4

Route27_RouteExpert_25:
# 205 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_JOYCE
	goto_if 1, Route27_RouteExpert_24
	goto Route27_RouteExpert_4

Route27_RouteExpert_28:
# 207 "data/maps/Route27/scripts.pory"
	checktrainerflag TRAINER_RICHARD
	goto_if 1, Route27_RouteExpert_5
	goto Route27_RouteExpert_4


Route27_RouteExpert_Text_0:
# 178 "data/maps/Route27/scripts.pory"
	.string "Choice items lock you into one move,\n"
	.string "but they offset that cost with a\l"
	.string "big boost to your battling power.$"

Route27_RouteExpert_Text_1:
# 185 "data/maps/Route27/scripts.pory"
	.string "The final stretch before the mighty\n"
	.string "Elite Four extends before you now.\p"
	.string "Here you will only find the most\n"
	.string "skilled trainers in Johto who\l"
	.string "aspire to take on the challenge.\p"
	.string "If you can overcome them all, find\n"
	.string "me again and I shall test you one\l"
	.string "last time.$"

Route27_RouteExpert_Text_2:
# 212 "data/maps/Route27/scripts.pory"
	.string "You cut through every challenge\n"
	.string "on this long road. Now show me\l"
	.string "if you really are worthy for the\l"
	.string "Elite Four!$"

Route27_RouteExpert_Text_3:
# 216 "data/maps/Route27/scripts.pory"
	.string "Nothing can stand against you now.$"

Route27_RouteExpert_Text_4:
# 217 "data/maps/Route27/scripts.pory"
	.string "A perfect choice, backed by real\n"
	.string "conviction. Take this and let it\l"
	.string "amplify your strongest attacks.$"
