AzaleaTown_House2_MapScripts::
	.byte 0


Azalea_SlowpokeTrade::
	lock
	faceplayer
	goto_if_set FLAG_SLOWPOKE_TRADE, Azalea_SlowpokeTrade_2
	ingame_trade INGAME_TRADE_SLOWPOKE, Azalea_SlowpokeTrade_Text_1, SlowpokeTrade_Declined, SlowpokeTrade_NotRequested, Azalea_SlowpokeTrade_Text_2
	setflag FLAG_SLOWPOKE_TRADE
Azalea_SlowpokeTrade_1:
	release
	end

Azalea_SlowpokeTrade_2:
	msgbox Azalea_SlowpokeTrade_Text_0
	goto Azalea_SlowpokeTrade_1


SlowpokeTrade_Declined::
	msgbox SlowpokeTrade_Declined_Text_0
	release
	end


SlowpokeTrade_NotRequested::
	msgbox SlowpokeTrade_NotRequested_Text_0
	release
	end


Azalea_SlowpokeTrade_Text_0:
# 7 "data/maps/AzaleaTown_House2/scripts.pory"
	.string "Have you been amassing more slowpoke?$"

Azalea_SlowpokeTrade_Text_1:
# 9 "data/maps/AzaleaTown_House2/scripts.pory"
	.string "I love Slowpoke! They are adorable,\n"
	.string "cuddly, cute, sweet, amazing and\l"
	.string "awesome! How about I prove it to you?\l"
	.string "I'll give you one of my finest slowpoke\l"
	.string "if you give me one of yours.$"

Azalea_SlowpokeTrade_Text_2:
	.string "Another one joins the cult of slowpoke.$"

SlowpokeTrade_Declined_Text_0:
	.string "Huh? Don't you understand how amazing\n"
	.string "slowpoke are?!?$"

SlowpokeTrade_NotRequested_Text_0:
	.string "Hey! That's not a real slowpoke! Are you\n"
	.string "trying to offer me an inferior Pokémon?$"
