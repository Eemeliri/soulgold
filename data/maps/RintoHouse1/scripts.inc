RintoHouse1_MapScripts::
	.byte 0


RintoHouse1_Vullaby::
	lock
	faceplayer
	playmoncry SPECIES_VULLABY, CRY_MODE_NORMAL
	msgbox RintoHouse1_Vullaby_Text_0
	waitmoncry
	release
	end


RintoHouse1_Girl::
	msgbox RintoHouse1_Girl_Text_0, MSGBOX_NPC
	return


RintoHouse1_Mom::
	msgbox RintoHouse1_Mom_Text_0, MSGBOX_NPC
	return


RintoHouse1_Vullaby_Text_0:
	.string "Vullaby: Vuvaaaaaa!$"

RintoHouse1_Girl_Text_0:
	.string "I heard that several Pokémon evolve\n"
	.string "much earlier in Johto than they do\l"
	.string "in other regions.$"

RintoHouse1_Mom_Text_0:
	.string "Our Vullaby has been eating a lot\n"
	.string "lately.\p"
	.string "It might be close to evolving.$"
