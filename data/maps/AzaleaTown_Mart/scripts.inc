
AzaleaTown_Mart_MapScripts::
	.byte 0

AzaleaTown_Mart_EventScriptBugCatcher::
	lock
	faceplayer
	msgbox AzaleaMart_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaMart_Text_BugCatcher:
	.string "A Great Ball is better for catch-\n"
	.string "ing Pokémon than a Poké Ball.\p"
	.string "But Kurt's might be better some-\n"
	.string "times.$"

AzaleaTownMart2::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, AzaleaTownMart2_2
	message AzaleaTownMart2_Text_2
	waitmessage
	pokemart GalaricaVendor
	msgbox AzaleaTownMart2_Text_1
	release
	end

AzaleaTownMart2_2:
	msgbox AzaleaTownMart2_Text_0
	waitmessage
	pokemart GalaricaNoneVendor
	msgbox AzaleaTownMart2_Text_1
	release
	end


	.align 2
GalaricaVendor:
	.2byte ITEM_TM_INFESTATION
	.2byte ITEM_TM_GIGA_DRAIN
	.2byte ITEM_TM_X_SCISSOR
	.2byte ITEM_GALARICA_WREATH
	.2byte ITEM_GALARICA_CUFF
	.2byte ITEM_NEST_BALL
	.2byte ITEM_MECH_MAIL
	.2byte ITEM_NONE

	.align 2
GalaricaNoneVendor:
	.2byte ITEM_TM_GIGA_DRAIN
	.2byte ITEM_NEST_BALL
	.2byte ITEM_MECH_MAIL
	.2byte ITEM_NONE

AzaleaTownMartNpc::
	lock
	faceplayer
	goto_if_set FLAG_BADGE04_GET, AzaleaTownMartNpc_2
	msgbox AzaleaTownMartNpc_Text_1
	release
	end

AzaleaTownMartNpc_2:
	msgbox AzaleaTownMartNpc_Text_0
	release
	end


AzaleaTownMart2_Text_0:
	.string "We're out of Galarica wreaths\n"
	.string "and cuffs currently.\p"
	.string "We hope to have them restocked soon.\n"
	.string "Regardless, welcome!$"

AzaleaTownMart2_Text_1:
	.string "Come back again soon!$"

AzaleaTownMart2_Text_2:
	.string "Welcome! The Galarian items back \n"
	.string "in stock!$"

AzaleaTownMartNpc_Text_0:
	.string "Galarian evolution items are back in\n"
	.string "stock!$"

AzaleaTownMartNpc_Text_1:
	.string "Apparently the Team Rocket had taken \n"
	.string "all evolution items specifically for\l"
	.string "Galarian Slowpoke.$"
