
VioletCity_House1_MapScripts::
	.byte 0

VioletCity_House1_EventScript_Kyle::
	lock
	faceplayer
	msgbox VioletCity_House1_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House1_Text_PokefanM:
	.string "A Pokémon you get in a trade\n"
	.string "grows quickly.\p"
	.string "But if you don't have the right\n"
	.string "Gym Badge, they may disobey you.$"

Violet_PawmiTrade::
	lock
	faceplayer
	goto_if_set FLAG_VIOLET_NPC_TRADE_COMPLETED, Violet_PawmiTrade_2
	ingame_trade INGAME_TRADE_PAWMI, Violet_PawmiTrade_Text_1, PawmiTrade_Declined, PawmiTrade_NotRequested, Violet_PawmiTrade_Text_2
	setflag FLAG_VIOLET_NPC_TRADE_COMPLETED
Violet_PawmiTrade_1:
	release
	end

Violet_PawmiTrade_2:
	msgbox Violet_PawmiTrade_Text_0
	goto Violet_PawmiTrade_1


PawmiTrade_Declined::
	msgbox PawmiTrade_Declined_Text_0
	release
	end


PawmiTrade_NotRequested::
	msgbox PawmiTrade_NotRequested_Text_0
	release
	end


Violet_PawmiTrade_Text_0:
	.string "Hi, how is my old Pawmi doing?$"

Violet_PawmiTrade_Text_1:
	.string "I collect Pokémon\n"
	.string "Do you have a Cottonee?\l"
	.string "Want to trade it for my\l"
	.string "Pawmi?$"

Violet_PawmiTrade_Text_2:
	.string "Yay! I got myself a Cottonee!\n"
	.string "Pawmi, you take care!$"

PawmiTrade_Declined_Text_0:
	.string "You don't want to trade? Aww...$"

PawmiTrade_NotRequested_Text_0:
	.string "Uh, no, I don't think so.\n"
	.string "That doesn't look like a Cottonee.$"
