BlackthornCave_MapScripts::
	.byte 0


BlackthornCave_Hint::
# 4 "data/maps/BlackthornCave/scripts.pory"
	msgbox BlackthornCave_Hint_Text_0, MSGBOX_SIGN
	return


BlackThornCave_Expert::
# 9 "data/maps/BlackthornCave/scripts.pory"
	lock
# 10 "data/maps/BlackthornCave/scripts.pory"
	faceplayer
# 11 "data/maps/BlackthornCave/scripts.pory"
	goto_if_set FLAG_GOT_KUBFU, BlackThornCave_Expert_2
# 16 "data/maps/BlackthornCave/scripts.pory"
	msgbox BlackThornCave_Expert_Text_1
# 25 "data/maps/BlackthornCave/scripts.pory"
	closemessage
# 26 "data/maps/BlackthornCave/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KUBFU
# 27 "data/maps/BlackthornCave/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_KUBFU
# 28 "data/maps/BlackthornCave/scripts.pory"
	givemon SPECIES_KUBFU, 5
# 29 "data/maps/BlackthornCave/scripts.pory"
	showgivemonpic 10, 3
# 30 "data/maps/BlackthornCave/scripts.pory"
	call Common_EventScript_GiftMon
# 31 "data/maps/BlackthornCave/scripts.pory"
	hidemonpic
# 32 "data/maps/BlackthornCave/scripts.pory"
	setflag FLAG_GOT_KUBFU
# 33 "data/maps/BlackthornCave/scripts.pory"
	msgbox BlackThornCave_Expert_Text_2
# 40 "data/maps/BlackthornCave/scripts.pory"
	release
	end

BlackThornCave_Expert_2:
# 12 "data/maps/BlackthornCave/scripts.pory"
	msgbox BlackThornCave_Expert_Text_0
# 13 "data/maps/BlackthornCave/scripts.pory"
	release
	end


BlackthornCave_Hint_Text_0:
# 4 "data/maps/BlackthornCave/scripts.pory"
	.string "Noon o'clock, one to add,\n"
	.string "another to subtract.$"

BlackThornCave_Expert_Text_0:
# 12 "data/maps/BlackthornCave/scripts.pory"
	.string "Now leave me be! I wish to meditate!$"

BlackThornCave_Expert_Text_1:
# 16 "data/maps/BlackthornCave/scripts.pory"
	.string "Hmph, \n"
	.string "of course someone had figure it out.\p"
	.string "I've been living as a hermit in this\n"
	.string "cave to hone my martial and spiritual\l"
	.string "talents.\p"
	.string "I suppose you are expecting something\n"
	.string "from me. Fine! Take this and leave.$"

BlackThornCave_Expert_Text_2:
# 33 "data/maps/BlackthornCave/scripts.pory"
	.string "I hear a batch of scrolls for evolving\n"
	.string "that Pokémon were stolen by Team\l"
	.string "Rocket.\p"
	.string "Such an act of disgrace! If I was 30\n"
	.string "years younger, I would hunt them down\l"
	.string "myself!$"
