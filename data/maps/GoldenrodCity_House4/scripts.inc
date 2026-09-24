GoldenrodCity_House4_MapScripts::
	.byte 0


Golderod_House4_Fatman::
	msgbox Golderod_House4_Fatman_Text_0, MSGBOX_NPC
	return


Goldenrod_House4_Venipede::
	lock
	faceplayer
	playmoncry SPECIES_VENIPEDE, CRY_MODE_NORMAL
	msgbox Goldenrod_House4_Venipede_Text_0
	waitmoncry
	release
	end


Golderod_House4_Fatman_Text_0:
	.string "Some say once Pokémon reaches a\n"
	.string "certain level, it starts to gain more\l"
	.string "abilities. Could that be true?$"

Goldenrod_House4_Venipede_Text_0:
	.string "Hiss!$"
