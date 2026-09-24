
VioletCity_Mart_MapScripts::
	.byte 0

VioletCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

VioletCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Mart_EventScript_Rocker::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end
	
VioletCity_Mart_Text_Granny:
	.string "When you first catch a Pokémon,\n"
	.string "it may be weak.\p"
	.string "But it will eventually grow to\n"
	.string "be strong.\p"
	.string "It's important to treat Pokémon\n"
	.string "with love.$"

VioletCity_Mart_Text_CooltrainerM:
	.string "Pokémon can hold items like\n"
	.string "Potion and Antidote.\p"
	.string "But they don't appear to know\n"
	.string "how to use man-made items.$"

Violetcity_Mart2::
	lock
	faceplayer
	message Violetcity_Mart2_Text_0
	waitmessage
	pokemart Violetcity2
	msgbox Violetcity_Mart2_Text_1
	release
	end


	.align 2
Violetcity2:
	.2byte ITEM_TM_HONE_CLAWS
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_NONE

Violetcity_Mart2_Text_0:
	.string "Welcome! How may I help you?$"

Violetcity_Mart2_Text_1:
	.string "Come back soon!$"
