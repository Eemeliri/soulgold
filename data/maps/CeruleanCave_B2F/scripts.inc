
CeruleanCave_B2F_MapScripts::
	.byte 0

CeruleanCave3_EventScript_MewtwoNew::
	lock
	faceplayer
	playmoncry SPECIES_MEWTWO, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_MEWTWO, 80
	special BattleSetup_StartLegendaryBattle
waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, CeruleanCave3_EventScript_MewtwoRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CERULEANCAVE_MEWTWO
	setflag FLAG_HIDE_MEWTWO
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

CeruleanCave3_EventScript_MewtwoRan::
	release
	end

NamelessDungeonMewtwo::
	lock
	faceplayer
	bosslegendaryencounterwithmoves SPECIES_MEWTWO, 80, LOCALID_CERULEANCAVE_MEWTWO, FLAG_HIDE_MEWTWO, 4, SPECIES_NONE, 110, MOVE_PSYSTRIKE, MOVE_ICE_BEAM, MOVE_FIRE_BLAST, MOVE_TAUNT, BOSS_PHASE_PROFILE_MEWTWO
	release
	end


NamelessDungeon_Leaf::
	lock
	goto_if_unset FLAG_TEMP_3, NamelessDungeon_Leaf_2
NamelessDungeon_Leaf_1:
	faceplayer
	msgbox NamelessDungeon_Leaf_Text_4, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq NamelessDungeon_Leaf_5
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, FALSE
	msgbox NamelessDungeon_Leaf_Text_6
	trainerbattle_no_intro TRAINER_NAMELESS_LEAF, NamelessDungeon_Leaf_Text_7
	createfieldmugshot MUGSHOT_LEAF
	msgbox NamelessDungeon_Leaf_Text_8
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_LEAF_NAMELESS
	setflag FLAG_POSTGAME_CAP1
	playse SE_EXIT
	removeobject LOCALID_NAMELESS_LEAF
	delay 60
	fadescreen FADE_FROM_BLACK
	release
	end

NamelessDungeon_Leaf_2:
	msgbox NamelessDungeon_Leaf_Text_0
	delay 30
	playse SE_PIN
	applymovement LOCALID_NAMELESS_LEAF, Common_Movement_ExclamationMark
	faceplayer
	waitse
	createfieldmugshot MUGSHOT_LEAF
	msgbox NamelessDungeon_Leaf_Text_1
	turnobject LOCALID_NAMELESS_LEAF, DIR_WEST
	msgbox NamelessDungeon_Leaf_Text_2
	faceplayer
	msgbox NamelessDungeon_Leaf_Text_3
	setflag FLAG_TEMP_3
	goto NamelessDungeon_Leaf_1

NamelessDungeon_Leaf_5:
	msgbox NamelessDungeon_Leaf_Text_5
	turnobject LOCALID_NAMELESS_LEAF, DIR_SOUTH
	release
	end


NamelessDungeon_Leaf_Text_0:
	.string "???: Hmm, Mewtwo should be just ahead...$"

NamelessDungeon_Leaf_Text_1:
	.string "???: Oh, hello! Who might you be?\p"
	.string "...\p"
	.string "Oh, you're {PLAYER}? Nice to meet you!\p"
	.string "I'm Leaf. \p"
	.string "I'm in search of some rarer\n"
	.string "than your average rare Pokémon.$"

NamelessDungeon_Leaf_Text_2:
	.string "I've tracked it down to this cave, and\n"
	.string "the only place it can be hiding in is\l"
	.string "just past this pool of water.$"

NamelessDungeon_Leaf_Text_3:
	.string "Piqued your interest, eh?\p"
	.string "Can't blame you, this one is\n"
	.string "apparently an experiment created\l"
	.string "from the DNA of another Pokémon!\p"
	.string "Unfortunately for you, I was here\n"
	.string "first!\p"
	.string "Only way to convince me otherwise\n"
	.string "would involve beating me in a battle.$"

NamelessDungeon_Leaf_Text_4:
	.string "What do you say? Interested?\n"
	.string "I'll warn you though, I'm really\l"
	.string "tough!$"

NamelessDungeon_Leaf_Text_5:
	.string "Ah shame, I was hoping you'd say\n"
	.string "yes.$"

NamelessDungeon_Leaf_Text_6:
	.string "Great! Get ready for a beatdown!$"

NamelessDungeon_Leaf_Text_7:
	.string "Damn, you're good!$"

NamelessDungeon_Leaf_Text_8:
	.string "Let me tell you, \n"
	.string "I was not expecting that!\p"
	.string "You are a monster in battle!\p"
	.string "What? You're this region's Champion?\p"
	.string "Oh...\p"
	.string "That explains a few things!\p"
	.string "Anyway, as promised, I'll let you have\n"
	.string "this one, but mark my words, I'll get\l"
	.string "the better of you next time we meet!\p"
	.string "Laters!$"
