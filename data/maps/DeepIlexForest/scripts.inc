DeepIlexForest_MapScripts::
	.byte 0


Ilex_Larvesta::
	lock
	faceplayer
	legendaryencounter SPECIES_LARVESTA, 30, LOCALID_ILEX_LARVESTA, FLAG_HIDE_LARVESTA
	release
	end


DeepIlex_Hex::
	msgbox DeepIlex_Hex_Text_0, MSGBOX_NPC
	return


DeepIlex_Hex_Text_0:
	.string "Engineers from Hoenn tried to\n"
	.string "build another Battle Factory here.\p"
	.string "They were chased away by the\n"
	.string "guardian of the forest before\l"
	.string "they made much progress.$"
