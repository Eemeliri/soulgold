
CherrygroveCity_Mart_MapScripts::
	.byte 0

Cherrygrove_Pokemart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_ge VAR_NEWBARK_TOWN_STATE, 5, Cherrygrove_Pokemart_EventScript_Clerk2
	pokemart Cherrygrove_Pokemart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Cherrygrove_Pokemart_EventScript_Youngster::
	lock
	faceplayer
	msgbox Cherrygrove_Pokemart_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Cherrygrove_Pokemart_EventScript_Bugcatcher::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 5, Cherrygrove_Pokemart_EventScript_Bugcatcher2
	msgbox Cherrygrove_Pokemart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end
	
Cherrygrove_Pokemart_EventScript_Bugcatcher2::
	msgbox Cherrygrove_Pokemart_Text_CooltrainerM_PokeBallsInStock, MSGBOX_DEFAULT
	closemessage
	release
	end

Cherrygrove_Pokemart_EventScript_Clerk2::
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 3
Cherrygrove_Pokemart_Pokemart:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_NONE
	release
	end

Cherrygrove_Pokemart_Text_CooltrainerM:
	.string "They're fresh out of Poké Balls!\p"
	.string "When will they get more of them?$"

Cherrygrove_Pokemart_Text_CooltrainerM_PokeBallsInStock:
	.string "Poké Balls are in stock!\n"
	.string "Now I can catch Pokémon!$"

Cherrygrove_Pokemart_Text_Youngster:
	.string "When I was walking in the grass, a\n"
	.string "bug Pokémon poisoned my Pokémon!\p"
	.string "I just kept going, but then my\n"
	.string "Pokémon fainted.\p"
	.string "You should keep an Antidote\n"
	.string "with you.$"

Cherrygrove_Mart2::
	lock
	faceplayer
	compare VAR_NEWBARK_TOWN_STATE, 5
	goto_if_lt Cherrygrove_Mart2_2
	message Cherrygrove_Mart2_Text_1
	waitmessage
	pokemart Cherrygrove2
	msgbox Cherrygrove_Mart2_Text_2
	release
	end

Cherrygrove_Mart2_2:
	msgbox Cherrygrove_Mart2_Text_0
	release
	end


	.align 2
Cherrygrove2:
	.2byte ITEM_TM_SAFEGUARD
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_NONE

Cherrygrove_Mart2_Text_0:
	.string "We're still setting up, come back\n"
	.string "a bit later.$"

Cherrygrove_Mart2_Text_1:
	.string "Welcome!$"

Cherrygrove_Mart2_Text_2:
	.string "Come back soon.$"
