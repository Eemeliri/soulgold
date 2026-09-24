
VioletCity_TrainerSchool_MapScripts::
	.byte 0

VioletCity_TrainerSchool_EventScript_Earl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_EarlIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy1::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy2::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Girl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Twin::
	msgbox VioletCity_TrainerSchool_Text_Twin, MSGBOX_NPC
	end

VioletCity_TrainerSchool_EventScript_BlackBoard::
	lock
	msgbox VioletCity_TrainerSchool_Text_Blackboard, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_Text_Twin:
	.string "I'm not a Gba kid, but I love\n"
	.string "playing Pokémon games!\p"
	.string "In the old games, you had to battle\n"
	.string "a lot of wild Pokémon to get enough\l"
	.string "Exp.\p"
	.string "But in newer games, the Exp share\n"
	.string "makes your Pokémon level up too fast.\p"
	.string "In this game, the Exp share is\n"
	.string "balanced to put your Pokémon at just\l"
	.string "the right level. Or slightly higher,\l"
	.string "depending on how many battles you do.\p"
	.string "If you want a traditional Gen 1-4\n"
	.string "experience, turn Exp Share off.\l"
	.string "If you want a modern experience,\l"
	.string "turn Exp Share On.\p"
	.string "You choose how you want to play!$"

VioletCity_TrainerSchool_Text_EarlIntro:
	.string "Earl, I am!\p"
	.string "Wonderful are Pokémon, yes!\p"
	.string "Teach you I will to be a better\n"
	.string "trainer!$"

VioletCity_TrainerSchool_Text_Teacher:
	.string "Certain Pokémon start off weak and\n"
	.string "require much more Exp to become\l"
	.string "strong than others do.\p"
	.string "For example, Larvitar is quite weak\n"
	.string "but will eventually become a\l"
	.string "mighty Tyranitar, at the cost of\l"
	.string "much Exp.\p"
	.string "Only the most dedicated trainers\n"
	.string "should attempt to train such a\l"
	.string "Pokémon.$"

VioletCity_TrainerSchool_Text_TeachHowToWin:
	.string "Good! Teach you, I will!\p"
	.string "In battle, Pokémon top on list\n"
	.string "jump out first!\p"
	.string "Change order in list, make\n"
	.string "battle easy, maybe!\p"
	.string "More from me you want to hear?$"

VioletCity_TrainerSchool_Text_TeachMore:
	.string "So, want to know how to raise\n"
	.string "Pokémon well?$"

VioletCity_TrainerSchool_Text_TeachRaiseWell:
	.string "Fine! Teach you, I will!\p"
	.string "If Pokémon come out in battle\n"
	.string "even briefly, some Exp. Points\p"
	.string "it gets.\n"
	.string "At top of list put weak Pokémon\p"
	.string "Switch in battle quick!\n"
	.string "This way, weak Pokémon strong\p"
	.string "become!$"

VioletCity_TrainerSchool_Text_NoMoreToTeach:
	.string "Oh! Smart student you are!\n"
	.string "Nothing more do I teach!\p"
	.string "If you want more, talk to\n"
	.string "pupils!$"

VioletCity_TrainerSchool_Text_Youngster1:
	.string "Pokémon previously thought to\n"
	.string "only evolve through trade can\p"
	.string "evolve through leveling.\n"
	.string "Machoke and Graveler evolve\p"
	.string "at Lvl 38, while Kadabra and\n"
	.string "Haunter evolve at Lvl 42.\p"
	.string "Some items, like the Metal\n"
	.string "Coat, have also been found to\p"
	.string "evolve certain Pokémon\n"
	.string "while holding and leveling up.$"

VioletCity_TrainerSchool_Text_GameboyKid1:
	.string "Notable Pokémon available in an\n"
	.string "area can be seen in the overworld!\p"
	.string "But make sure to check routes\n"
	.string "at Day and Night!$"

VioletCity_TrainerSchool_Text_GameboyKid2:
	.string "Berries in the Johto region are\n"
	.string "good for healing and making balls.\p"
	.string "Berries in Kanto are good for\n"
	.string "reducing a Pokémon's stats.\p"
	.string "The Dojo in Kanto helps Pokémon\n"
	.string "perfect individual stats.$"

VioletCity_TrainerSchool_Text_Youngster2:
	.string "Be aware that your opponents\n"
	.string "now use teams with better type\l"
	.string "coverage,so expect a much\l"
	.string "more challenging journey ahead.$"

VioletCity_TrainerSchool_Text_Blackboard:
	.string "The blackboard describes\n"
	.string "Pokémon HM moves.\p"
	.string "HMs, once unlocked, don't need to\n"
	.string "be taught to be used.$"

VioletCity_TrainerSchool_Text_Notebook:
	.string "It's this kid's notebook…\p"
	.string "Catch Pokémon using Poké Balls.\p"
	.string "Up to six can be in your party.\p"
	.string "Keep reading?$"

VioletCity_TrainerSchool_Text_Notebook1:
	.string "Before throwing a Poké Ball,\n"
	.string "weaken the target first.\p"
	.string "A poisoned or burned Pokémon\n"
	.string "is easier to catch.\p"
	.string "Keep reading?$"

VioletCity_TrainerSchool_Text_Notebook2:
	.string "Some moves may cause confusion.\p"
	.string "Confusion may make a Pokémon\n"
	.string "attack itself.\p"
	.string "Leaving battle clears up any\n"
	.string "confusion.\p"
	.string "Keep reading?$"

VioletCity_TrainerSchool_Text_Notebook3:
	.string "People who catch and use\n"
	.string "Pokémon in battle are Pokémon\n"
	.string "trainers.\p"
	.string "They are expected to visit\n"
	.string "Pokémon Gyms and defeat other\n"
	.string "trainers.\p"
	.string "The next page is… Blank!\p"
	.string "Boy: E-he-he…\p"
	.string "I haven't written anymore…$"

VioletCity_TrainerSchool_Text_StickerMachine:
	.string "This super machine prints data\n"
	.string "out as stickers!$"

VioletTrainerSchool_FalknerRematch::
	lock
	faceplayer
	msgbox VioletTrainerSchool_FalknerRematch_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, TRUE
	goto_if_eq VioletTrainerSchool_FalknerRematch_2
VioletTrainerSchool_FalknerRematch_1:
	release
	end

VioletTrainerSchool_FalknerRematch_2:
	trainerbattle_no_intro TRAINER_FALKNER_2, VioletTrainerSchool_FalknerRematch_Text_1
	msgbox VioletTrainerSchool_FalknerRematch_Text_2
	msgbox VioletTrainerSchool_FalknerRematch_Text_3
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_VIOLET_SCHOOL_FALKNER
	removeobject LOCALID_FALKNER_REMATCH
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	goto VioletTrainerSchool_FalknerRematch_1


VioletCity_TrainerSchool_Kid::
	msgbox VioletCity_TrainerSchool_Kid_Text_0, MSGBOX_NPC
	return


VioletCity_TrainerSchool_Boy1::
	msgbox VioletCity_TrainerSchool_Boy1_Text_0, MSGBOX_NPC
	return


VioletCity_TrainerSchool_Boy2::
	msgbox VioletCity_TrainerSchool_Boy2_Text_0, MSGBOX_NPC
	return


VioletCity_TrainerSchool_Twin::
	msgbox VioletCity_TrainerSchool_Twin_Text_0, MSGBOX_NPC
	return


VioletCity_TrainerSchool_Lass::
	msgbox VioletCity_TrainerSchool_Lass_Text_0, MSGBOX_NPC
	return


VioletTrainerSchool_FalknerRematch_Text_0:
	.string "Nice to see you here too, {PLAYER}.\p"
	.string "I'm occasionally tutoring our future\n"
	.string "generation of trainers, so that they\l"
	.string "too may soar some day.\p"
	.string "They have been asking me to showcase\n"
	.string "my battling skills for a while now,\l"
	.string "would you like to be my opponent?\l"
	.string "I've been waiting for a chance to get\l"
	.string "back at our first battle.$"

VioletTrainerSchool_FalknerRematch_Text_1:
	.string "You soared above us!$"

VioletTrainerSchool_FalknerRematch_Text_2:
	.string "Based on everyone's reactions, I'd say\n"
	.string "you managed to capture the entire\l"
	.string "class with your skills. That should\l"
	.string "inspire them to work hard.$"

VioletTrainerSchool_FalknerRematch_Text_3:
	.string "Time for me to head back to the gym.\n"
	.string "I hope we'll get a chance to have\l"
	.string "another battle soon.$"

VioletCity_TrainerSchool_Kid_Text_0:
	.string "You can simulate trading for evolving\n"
	.string "Pokémon with Linking Cord!$"

VioletCity_TrainerSchool_Boy1_Text_0:
	.string "Huh? The Pokémon I just got is\n"
	.string "holding something!$"

VioletCity_TrainerSchool_Boy2_Text_0:
	.string "I traded my best Pokémon to the\n"
	.string "guy beside me.$"

VioletCity_TrainerSchool_Twin_Text_0:
	.string "Pokémon have what are called\n"
	.string "abilities!\p"
	.string "It seems that each kind of Pokémon has\n"
	.string "distinct abilities.\p"
	.string "They say these abilities come in handy\n"
	.string "in battle!$"

VioletCity_TrainerSchool_Lass_Text_0:
	.string "I'm taking notes of the teacher's\n"
	.string "lecture.\p"
	.string "I'd better copy the stuff on the\n"
	.string "blackboard, too.$"
