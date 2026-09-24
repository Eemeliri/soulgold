
OlivineCity_House1_MapScripts::
	.byte 0

Olivine_VoltorbTrade::
	lock
	faceplayer
	goto_if_set FLAG_OLIVINE_NPC_TRADE_COMPLETED, Olivine_VoltorbTrade_2
	ingame_trade INGAME_TRADE_VOLTORB, Olivine_VoltorbTrade_Text_1, VoltorbTrade_Declined, VoltorbTrade_NotRequested, Olivine_VoltorbTrade_Text_2
	setflag FLAG_OLIVINE_NPC_TRADE_COMPLETED
Olivine_VoltorbTrade_1:
	release
	end

Olivine_VoltorbTrade_2:
	msgbox Olivine_VoltorbTrade_Text_0
	goto Olivine_VoltorbTrade_1


VoltorbTrade_Declined::
	msgbox VoltorbTrade_Declined_Text_0
	release
	end


VoltorbTrade_NotRequested::
	msgbox VoltorbTrade_NotRequested_Text_0
	release
	end


Olivine_VoltorbTrade_Text_0:
	.string "Hi, how is my old Voltorb doing?$"

Olivine_VoltorbTrade_Text_1:
	.string "I collect Pokémon\n"
	.string "Do you have a Mareanie?\l"
	.string "Want to trade it for my\l"
	.string "Hisuian Voltorb?$"

Olivine_VoltorbTrade_Text_2:
	.string "Yay! I got myself a Mareanie!\n"
	.string "Voltorb, you take care!$"

VoltorbTrade_Declined_Text_0:
	.string "You don't want to trade? Aww...$"

VoltorbTrade_NotRequested_Text_0:
	.string "Uh, no, I don't think so.\n"
	.string "That doesn't look like a Mareanie.$"
