
BlackthornCity_House2_MapScripts::
	.byte 0

Blackthorn_GabiteTrade::
	lock
	faceplayer
	goto_if_set FLAG_BLACKTHORN_NPC_TRADE_COMPLETED, Blackthorn_GabiteTrade_2
	ingame_trade INGAME_TRADE_GABITE, Blackthorn_GabiteTrade_Text_1, GabiteTrade_Declined, GabiteTrade_NotRequested, Blackthorn_GabiteTrade_Text_2
	setflag FLAG_BLACKTHORN_NPC_TRADE_COMPLETED
Blackthorn_GabiteTrade_1:
	release
	end

Blackthorn_GabiteTrade_2:
	msgbox Blackthorn_GabiteTrade_Text_0
	goto Blackthorn_GabiteTrade_1


GabiteTrade_Declined::
	msgbox GabiteTrade_Declined_Text_0
	release
	end


GabiteTrade_NotRequested::
	msgbox GabiteTrade_NotRequested_Text_0
	release
	end


Blackthorn_GabiteTrade_Text_0:
	.string "How has my Gabite been?$"

Blackthorn_GabiteTrade_Text_1:
	.string "Hello. I gather Dragon-type Pokémon.\n"
	.string "Do you have Dragonair? I'm willing to \l"
	.string "trade it for Gabite.$"

Blackthorn_GabiteTrade_Text_2:
	.string "Thank you very much.$"

GabiteTrade_Declined_Text_0:
	.string "If you find one, come trade with me!$"

GabiteTrade_NotRequested_Text_0:
	.string "That doesn't look like a Dragonair to\n"
	.string "me.$"
