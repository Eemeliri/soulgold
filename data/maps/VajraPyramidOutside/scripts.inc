VajraPyramidOutside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_LOAD, VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto_if_set FLAG_RINTO_TRADE_COMPLETE, VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	setflag FLAG_HIDE_PYRAMIDOUT_SCIENTIST
	return

VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	clearflag FLAG_HIDE_PYRAMIDOUT_SCIENTIST
	return

VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_IS_CHAMPION, VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_LOAD_2
	return

VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 16, 6, 0x4D5, FALSE
	return

VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_LOAD_2:
	goto_if_set FLAG_RINTO_TRADE_COMPLETE, VajraPyramidOutside_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return


VajraPyramidOutside_Door::
	goto_if_set FLAG_IS_CHAMPION, VajraPyramidOutside_Door_3
VajraPyramidOutside_Door_2:
	msgbox VajraPyramidOutside_Door_Text_1, MSGBOX_SIGN
	return

VajraPyramidOutside_Door_1:
	msgbox VajraPyramidOutside_Door_Text_0, MSGBOX_SIGN
	return

VajraPyramidOutside_Door_3:
	goto_if_set FLAG_RINTO_TRADE_COMPLETE, VajraPyramidOutside_Door_1
	goto VajraPyramidOutside_Door_2


VajraPyramidOutside_ScientistPostgame::
	goto_if_set FLAG_IS_CHAMPION, VajraPyramidOutside_ScientistPostgame_1
	msgbox VajraPyramidOutside_ScientistPostgame_Text_1, MSGBOX_NPC
	return

VajraPyramidOutside_ScientistPostgame_1:
	msgbox VajraPyramidOutside_ScientistPostgame_Text_0, MSGBOX_NPC
	return


VajraPyramidOutside_ScientistsTinkaton::
	lock
	faceplayer
	playmoncry SPECIES_TINKATON, 0
	msgbox VajraPyramidOutside_ScientistsTinkaton_Text_0
	waitmoncry
	msgbox VajraPyramidOutside_ScientistsTinkaton_Text_1
	release
	end


VajraPyramidOutside_RuinManiac::
	msgbox VajraPyramidOutside_RuinManiac_Text_0, MSGBOX_NPC
	return


VajraPyramidOutside_Door_Text_0:
	.string "The door has been busted open by\n"
	.string "repeated exposure to something\l"
	.string "blunt.$"

VajraPyramidOutside_Door_Text_1:
	.string "The door is sealed shut tightly.$"

VajraPyramidOutside_ScientistPostgame_Text_0:
	.string "We finally managed to break down the\n"
	.string "door to the Pyramid thanks to the\l"
	.string "Tinkaton you gave us!\p"
	.string "Please, feel free to explore it first!$"

VajraPyramidOutside_ScientistPostgame_Text_1:
	.string "We've started working on getting that\n"
	.string "door opened with the help of your\l"
	.string "Tinkaton! \p"
	.string "It might take some time, so\n"
	.string "you should come back later.$"

VajraPyramidOutside_ScientistsTinkaton_Text_0:
	.string "Tinkaton: Tinktii!$"

VajraPyramidOutside_ScientistsTinkaton_Text_1:
	.string "Your old Tinkaton seems to be having\n"
	.string "fun here!$"

VajraPyramidOutside_RuinManiac_Text_0:
	.string "There's mystery here waiting to be\n"
	.string "uncovered! I can sense it!$"
