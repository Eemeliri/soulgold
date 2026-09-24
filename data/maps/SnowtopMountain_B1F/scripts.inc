SnowtopMountain_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SnowtopMountain_B1F_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

SnowtopMountain_B1F_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_SNOWTOP_REGICE_DOOR, SnowtopMountain_B1F_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

SnowtopMountain_B1F_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 5, 36, 0x414, FALSE
	setmetatile 5, 35, 0x40C, FALSE
	return



Snowtopmountain_BrailleRegice:
	.braille "TYRANT OF\n"
	.braille "THE SNOW\n"
	.braille "FULLY EVOLVED.$"

B1F_Snowtopmountain_Bearnese::
	trainerbattle_single TRAINER_BEARNESE, B1F_Snowtopmountain_Bearnese_Text_0, B1F_Snowtopmountain_Bearnese_Text_1
	msgbox B1F_Snowtopmountain_Bearnese_Text_2, MSGBOX_AUTOCLOSE
	return


B1F_Snowtopmountain_Susdoor::
	lock
	msgbox B1F_Snowtopmountain_Susdoor_Text_0
	closemessage
	braillemsgbox Snowtopmountain_BrailleRegice
	checkspecies SPECIES_BAXCALIBUR
	compare VAR_RESULT, TRUE
	goto_if_eq B1F_Snowtopmountain_Susdoor_2
B1F_Snowtopmountain_Susdoor_1:
	release
	end

B1F_Snowtopmountain_Susdoor_2:
	setflag FLAG_SNOWTOP_REGICE_DOOR
	setmetatile 5, 36, 0x414, FALSE
	setmetatile 5, 35, 0x40C, FALSE
	playse SE_EXIT
	special DrawWholeMapView
	goto B1F_Snowtopmountain_Susdoor_1


B1F_Snowtopmountain_Bearnese_Text_0:
	.string "Check it out, my breath is forming\n"
	.string "icicles!$"

B1F_Snowtopmountain_Bearnese_Text_1:
	.string "Feeling kind of chilly here.$"

B1F_Snowtopmountain_Bearnese_Text_2:
	.string "They say an ancient ice Pokémon sleeps\n"
	.string "somewhere inside the mountain. \l"
	.string "I wonder where it could be?$"

B1F_Snowtopmountain_Susdoor_Text_0:
	.string "Something is carved on the wall...$"
