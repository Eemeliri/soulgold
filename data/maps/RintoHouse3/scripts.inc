RintoHouse3_MapScripts::
	.byte 0


RintoHouse3_Guard::
	msgbox RintoHouse3_Guard_Text_0, MSGBOX_NPC
	return


RintoHouse3_ResearchGuide::
	msgbox RintoHouse3_ResearchGuide_Text_0, MSGBOX_NPC
	return


RintoHouse3_Hiker::
	msgbox RintoHouse3_Hiker_Text_0, MSGBOX_NPC
	return


RintoHouse3_Researcher::
	msgbox RintoHouse3_Researcher_Text_0, MSGBOX_NPC
	return


RintoHouse3_Excadrill::
	lock
	faceplayer
	playmoncry SPECIES_EXCADRILL, CRY_MODE_NORMAL
	msgbox RintoHouse3_Excadrill_Text_0
	waitmoncry
	release
	end


RintoHouse3_TraderResearcher::
	lock
	faceplayer
	goto_if_set FLAG_RINTO_TRADE_COMPLETE, RintoHouse3_TraderResearcher_2
	ingame_trade INGAME_TRADE_MELTAN, RintoHouse3_TraderResearcher_Text_1, MeltanTrade_Declined, MeltanTrade_NotRequested, RintoHouse3_TraderResearcher_Text_2
	setflag FLAG_RINTO_TRADE_COMPLETE
RintoHouse3_TraderResearcher_1:
	release
	end

RintoHouse3_TraderResearcher_2:
	msgbox RintoHouse3_TraderResearcher_Text_0
	goto RintoHouse3_TraderResearcher_1


MeltanTrade_Declined::
	msgbox MeltanTrade_Declined_Text_0
	release
	end


MeltanTrade_NotRequested::
	msgbox MeltanTrade_NotRequested_Text_0
	release
	end


RintoHouse3_Plaque::
	msgbox RintoHouse3_Plaque_Text_0, MSGBOX_SIGN
	return


RintoHouse3_PlaqueBall::
	msgbox RintoHouse3_PlaqueBall_Text_0, MSGBOX_SIGN
	return


RintoHouse3_Bookshelf::
	msgbox RintoHouse3_Bookshelf_Text_0, MSGBOX_SIGN
	return


RintoHouse3_Painting::
	msgbox RintoHouse3_Painting_Text_0, MSGBOX_SIGN
	return


RintoHouse3_Guard_Text_0:
	.string "Downstairs is reserved for researchers\n"
	.string "only.$"

RintoHouse3_ResearchGuide_Text_0:
	.string "You can see our excavation results\n"
	.string "here!$"

RintoHouse3_Hiker_Text_0:
	.string "We've made a lot of discoveries near the\n"
	.string "pyramid, but no one has been able to get\l"
	.string "in.$"

RintoHouse3_Researcher_Text_0:
	.string "The door to the pyramid...\p"
	.string "It's made of a strange metal that can\n"
	.string "repel even our Excadrill's attacks.$"

RintoHouse3_Excadrill_Text_0:
	.string "Excadrill: Caaaaaaaa!$"

RintoHouse3_TraderResearcher_Text_0:
	.string "Thanks to your Tinkaton, we may\n"
	.string "finally be able to break through one\l"
	.string "of the pyramid's walls!$"

RintoHouse3_TraderResearcher_Text_1:
	.string "I'm researching alternative ways to\n"
	.string "get into the pyramid to the west.\p"
	.string "Would you happen to have a Tinkaton?\p"
	.string "With its powerful hammer strikes, we\n"
	.string "might be able to break through one of\l"
	.string "the pyramid's walls.\p"
	.string "I can offer you this rare Meltan in\n"
	.string "return. What do you say?$"

RintoHouse3_TraderResearcher_Text_2:
	.string "Amazing! Thank you on behalf of the\n"
	.string "whole research team!$"

MeltanTrade_Declined_Text_0:
	.string "Oh... Okay, then...\p"
	.string "I guess I'll have to ask someone to\n"
	.string "find and raise one from the Union Cave...$"

MeltanTrade_NotRequested_Text_0:
	.string "That doesn't look like a Tinkaton to\n"
	.string "me.$"

RintoHouse3_Plaque_Text_0:
	.string "It appears to be some sort of a\n"
	.string "Fossil excavated nearby.$"

RintoHouse3_PlaqueBall_Text_0:
	.string "An ancient Poké Ball. \p"
	.string "It looks much like the ones\n"
	.string "used in ancient Hisui.$"

RintoHouse3_Bookshelf_Text_0:
	.string "A Bookshelf filled with history books.\n"
	.string "Some of them look ancient!$"

RintoHouse3_Painting_Text_0:
	.string "A painting depicting an artist's \n"
	.string "interpretation of this land a thousand \l"
	.string "years ago.\p"
	.string "You have a hard time making out the\n"
	.string "signature.$"
