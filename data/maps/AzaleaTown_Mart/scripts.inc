# 1 "data/maps/AzaleaTown_Mart/scripts.pory"

# 2 "data/maps/AzaleaTown_Mart/scripts.pory"
AzaleaTown_Mart_MapScripts::
# 3 "data/maps/AzaleaTown_Mart/scripts.pory"
	.byte 0
# 4 "data/maps/AzaleaTown_Mart/scripts.pory"

# 5 "data/maps/AzaleaTown_Mart/scripts.pory"
AzaleaTown_Mart_EventScriptBugCatcher::
# 6 "data/maps/AzaleaTown_Mart/scripts.pory"
	lock
# 7 "data/maps/AzaleaTown_Mart/scripts.pory"
	faceplayer
# 8 "data/maps/AzaleaTown_Mart/scripts.pory"
	msgbox AzaleaMart_Text_BugCatcher, MSGBOX_DEFAULT
# 9 "data/maps/AzaleaTown_Mart/scripts.pory"
	closemessage
# 10 "data/maps/AzaleaTown_Mart/scripts.pory"
	release
# 11 "data/maps/AzaleaTown_Mart/scripts.pory"
	end
# 12 "data/maps/AzaleaTown_Mart/scripts.pory"

# 13 "data/maps/AzaleaTown_Mart/scripts.pory"
AzaleaMart_Text_BugCatcher:
# 14 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "A Great Ball is better for catch-\n"
# 15 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "ing Pokémon than a Poké Ball.\p"
# 16 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "But Kurt's might be better some-\n"
# 17 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "times.$"

AzaleaTownMart2::
# 22 "data/maps/AzaleaTown_Mart/scripts.pory"
	lock
# 23 "data/maps/AzaleaTown_Mart/scripts.pory"
	faceplayer
# 24 "data/maps/AzaleaTown_Mart/scripts.pory"
	goto_if_unset FLAG_BADGE04_GET, AzaleaTownMart2_2
# 36 "data/maps/AzaleaTown_Mart/scripts.pory"
	message AzaleaTownMart2_Text_2
# 38 "data/maps/AzaleaTown_Mart/scripts.pory"
	waitmessage
# 39 "data/maps/AzaleaTown_Mart/scripts.pory"
	pokemart GalaricaVendor
# 40 "data/maps/AzaleaTown_Mart/scripts.pory"
	msgbox AzaleaTownMart2_Text_1
# 41 "data/maps/AzaleaTown_Mart/scripts.pory"
	release
	end

AzaleaTownMart2_2:
# 25 "data/maps/AzaleaTown_Mart/scripts.pory"
	msgbox AzaleaTownMart2_Text_0
# 30 "data/maps/AzaleaTown_Mart/scripts.pory"
	waitmessage
# 31 "data/maps/AzaleaTown_Mart/scripts.pory"
	pokemart GalaricaNoneVendor
# 32 "data/maps/AzaleaTown_Mart/scripts.pory"
	msgbox AzaleaTownMart2_Text_1
# 33 "data/maps/AzaleaTown_Mart/scripts.pory"
	release
	end


	.align 2
# 45 "data/maps/AzaleaTown_Mart/scripts.pory"
GalaricaVendor:
# 46 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_TM_INFESTATION
# 47 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_TM_GIGA_DRAIN
# 48 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_TM_X_SCISSOR
# 49 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_GALARICA_WREATH
# 50 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_GALARICA_CUFF
# 51 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_NEST_BALL
# 52 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_MECH_MAIL
	.2byte ITEM_NONE

	.align 2
# 55 "data/maps/AzaleaTown_Mart/scripts.pory"
GalaricaNoneVendor:
# 56 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_TM_GIGA_DRAIN
# 57 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_NEST_BALL
# 58 "data/maps/AzaleaTown_Mart/scripts.pory"
	.2byte ITEM_MECH_MAIL
	.2byte ITEM_NONE

AzaleaTownMartNpc::
# 62 "data/maps/AzaleaTown_Mart/scripts.pory"
	lock
# 63 "data/maps/AzaleaTown_Mart/scripts.pory"
	faceplayer
# 64 "data/maps/AzaleaTown_Mart/scripts.pory"
	goto_if_set FLAG_BADGE04_GET, AzaleaTownMartNpc_2
# 70 "data/maps/AzaleaTown_Mart/scripts.pory"
	msgbox AzaleaTownMartNpc_Text_1
# 73 "data/maps/AzaleaTown_Mart/scripts.pory"
	release
	end

AzaleaTownMartNpc_2:
# 65 "data/maps/AzaleaTown_Mart/scripts.pory"
	msgbox AzaleaTownMartNpc_Text_0
# 67 "data/maps/AzaleaTown_Mart/scripts.pory"
	release
	end


AzaleaTownMart2_Text_0:
# 25 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "We're out of Galarica wreaths\n"
	.string "and cuffs currently.\p"
	.string "We hope to have them restocked soon.\n"
	.string "Regardless, welcome!$"

AzaleaTownMart2_Text_1:
# 32 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "Come back again soon!$"

AzaleaTownMart2_Text_2:
# 36 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "Welcome! The Galarian items back \n"
	.string "in stock!$"

AzaleaTownMartNpc_Text_0:
# 65 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "Galarian evolution items are back in\n"
	.string "stock!$"

AzaleaTownMartNpc_Text_1:
# 70 "data/maps/AzaleaTown_Mart/scripts.pory"
	.string "Apparently the Team Rocket had taken \n"
	.string "all evolution items specifically for\l"
	.string "Galarian Slowpokes.$"
