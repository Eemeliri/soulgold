EcruteakCity_House4_MapScripts::
	.byte 0


Itemfinder_Cooltrainer::
	lock
	faceplayer
	goto_if_set FLAG_GOT_DOWSING_MACHINE, Itemfinder_Cooltrainer_2
	msgbox Itemfinder_Cooltrainer_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Itemfinder_Cooltrainer_5
	msgbox Itemfinder_Cooltrainer_Text_3
Itemfinder_Cooltrainer_4:
	release
	end

Itemfinder_Cooltrainer_2:
	msgbox Itemfinder_Cooltrainer_Text_0
	release
	end

Itemfinder_Cooltrainer_5:
	msgbox Itemfinder_Cooltrainer_Text_2
	giveitem ITEM_DOWSING_MACHINE
	setflag FLAG_GOT_DOWSING_MACHINE
	msgbox Itemfinder_Cooltrainer_Text_0
	goto Itemfinder_Cooltrainer_4


Itemfinder_Cooltrainer_Text_0:
	.string "There are many items lying about\n"
	.string "that aren't obvious.\p"
	.string "Use the Dowsing Machine for a while\n"
	.string "to see if it points you towards them.\p"
	.string "When it does, you know there's an\n"
	.string "item near you.$"

Itemfinder_Cooltrainer_Text_1:
	.string "Ah. You're on an adventure with\n"
	.string "your Pokémon?\p"
	.string "Well, what's an adventure without\n"
	.string "treasure hunting?\p"
	.string "Am I right, or am I right?$"

Itemfinder_Cooltrainer_Text_2:
	.string "Good! You understand the true\n"
	.string "spirit of adventure.\p"
	.string "I like that! Take this with you.$"

Itemfinder_Cooltrainer_Text_3:
	.string "Oh... To each his own, I suppose...$"
