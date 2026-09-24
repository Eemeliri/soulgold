Gate_Route39North_MapScripts::
	.byte 0


Route39North_Police::
	msgbox Route39North_Police_Text_0, MSGBOX_NPC
	return


Route39North_Elder::
	msgbox Route39North_Elder_Text_0, MSGBOX_NPC
	return


Route39North_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_R39_NORTH_ROCKY_HELMET, Route39North_Hiker_2
	msgbox Route39North_Hiker_Text_1
	giveitem ITEM_ROCKY_HELMET
	setflag FLAG_R39_NORTH_ROCKY_HELMET
	msgbox Route39North_Hiker_Text_2
	release
	end

Route39North_Hiker_2:
	msgbox Route39North_Hiker_Text_0
	release
	end


Route39North_Poster::
	msgbox Route39North_Poster_Text_0, MSGBOX_SIGN
	return


Route39North_Binoculars::
	msgbox Route39North_Binoculars_Text_0, MSGBOX_SIGN
	return


Route39North_Gameboykid::
	lock
	faceplayer
	goto_if_set FLAG_R39_NORTH_TRADE, Route39North_Gameboykid_2
	ingame_trade INGAME_TRADE_ROTOM, Route39North_Gameboykid_Text_1, RotomTrade_Declined, RotomTrade_NotRequested, Route39North_Gameboykid_Text_2
	setflag FLAG_R39_NORTH_TRADE
Route39North_Gameboykid_1:
	release
	end

Route39North_Gameboykid_2:
	msgbox Route39North_Gameboykid_Text_0
	goto Route39North_Gameboykid_1


RotomTrade_Declined::
	msgbox RotomTrade_Declined_Text_0
	release
	end


RotomTrade_NotRequested::
	msgbox RotomTrade_NotRequested_Text_0
	release
	end


Route39North_Police_Text_0:
	.string "If you want to head further north, you\n"
	.string "should find yourself some protection\l"
	.string "against the cold. The higher altitude\l"
	.string "takes a toll on the body.$"

Route39North_Elder_Text_0:
	.string "When I was younger, I would hike the\n"
	.string "trail to the mountain every day, uphill\l"
	.string "both ways! I didn't have any Pokémon\l"
	.string "carrying me or any of those fancy bikes\l"
	.string "you kids have these days!$"

Route39North_Hiker_Text_0:
	.string "Rocky Helmet makes sure your enemies\n"
	.string "will also suffer the pain they inflict\l"
	.string "upon you!$"

Route39North_Hiker_Text_1:
	.string "Tired of only taking the beating? Try\n"
	.string "this!$"

Route39North_Hiker_Text_2:
	.string "That should put the pain back to your\n"
	.string "enemies.$"

Route39North_Poster_Text_0:
	.string "There's a sign about a large bird \n"
	.string "Pokémon being sighted in the mountains.$"

Route39North_Binoculars_Text_0:
	.string "You peer into the binoculars...\n"
	.string "...\l"
	.string "..!\l"
	.string "A majestic snowy mountain towers in the\l"
	.string "distance!$"

Route39North_Gameboykid_Text_0:
	.string "I hear Rotom can possess common\n"
	.string "household appliances to change\l"
	.string "form.$"

Route39North_Gameboykid_Text_1:
	.string "There's this rare Pokémon\n"
	.string "I've been seeking for a while.\l"
	.string "Would you happen to have a Zorua?\l"
	.string "I would trade it for Rotom.$"

Route39North_Gameboykid_Text_2:
	.string "Much appreciated! I'm a huge fan\n"
	.string "of Unova, I can't wait to show this\l"
	.string "to my friends!$"

RotomTrade_Declined_Text_0:
	.string "Shame, it is quite a rare Pokémon.$"

RotomTrade_NotRequested_Text_0:
	.string "Uh, no, I don't think so.\n"
	.string "That doesn't look like a Zorua.$"
