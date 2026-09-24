BlackthornCave_MapScripts::
	.byte 0


BlackthornCave_Hint::
	msgbox BlackthornCave_Hint_Text_0, MSGBOX_SIGN
	return


BlackThornCave_Expert::
	lock
	faceplayer
	goto_if_set FLAG_GOT_KUBFU, BlackThornCave_Expert_2
	msgbox BlackThornCave_Expert_Text_1
	closemessage
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KUBFU
	bufferspeciesname STR_VAR_1, SPECIES_KUBFU
	givemon SPECIES_KUBFU, 5
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setflag FLAG_GOT_KUBFU
	msgbox BlackThornCave_Expert_Text_2
	release
	end

BlackThornCave_Expert_2:
	msgbox BlackThornCave_Expert_Text_0
	release
	end


BlackthornCave_Hint_Text_0:
	.string "Noon o'clock, one to add,\n"
	.string "another to subtract.$"

BlackThornCave_Expert_Text_0:
	.string "Now leave me be! I wish to meditate!$"

BlackThornCave_Expert_Text_1:
	.string "Hmph, \n"
	.string "of course someone had figure it out.\p"
	.string "I've been living as a hermit in this\n"
	.string "cave to hone my martial and spiritual\l"
	.string "talents.\p"
	.string "I suppose you are expecting something\n"
	.string "from me. Fine! Take this and leave.$"

BlackThornCave_Expert_Text_2:
	.string "I hear a batch of scrolls for evolving\n"
	.string "that Pokémon were stolen by Team\l"
	.string "Rocket.\p"
	.string "Such an act of disgrace! If I was 30\n"
	.string "years younger, I would hunt them down\l"
	.string "myself!$"
