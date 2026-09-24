
GoldenrodCity_BillsHouse_MapScripts::
	.byte 0

GoldenrodCity_BillsHouse_EventScript_Sister::
	lock
	faceplayer
	msgbox BillHouse_Text_SisterStorageSystem, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_SYS_PC_BILL, GoldenrodCity_BillsHouse_EventScript_Mom2
	msgbox BillHouse_Text_MomBeforeEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom2::
	msgbox BillHouse_Text_MomAfterEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

BillHouse_Text_EeveeMayEvolve:
    .string "Bill: Prof. Elm claims Eevee may\n"
    .string "evolve in new and unknown ways.$"

BillHouse_Text_PartyFull:
    .string "Whoa, wait. You can't carry any\n"
    .string "more Pokémon.$"

BillHouse_Text_NoEevee:
    .string "Oh… Now what to do?$"

BillHouse_Text_PopWontWork:
    .string "Bill: My pop, he won't work. All he\n"
    .string "does is goof off all day long.\p"
    .string "He's getting to be a real headache…$"

BillHouse_Text_MomBeforeEcruteak:
    .string "Oh, you collect Pokémon? My son\n"
    .string "Bill is an expert.\p"
    .string "He just got called to the Pokémon\n"
    .string "Center in Ecruteak City.\p"
    .string "My husband went off to the Game\n"
    .string "Corner without being called…$"

BillHouse_Text_MomAfterEcruteak:
    .string "My husband was once known as a\n"
    .string "Pokémaniac.\p"
    .string "Bill must have taken after his\n"
    .string "father.$"

BillHouse_Text_SisterUsefulNumber:
    .string "Are you a trainer?\p"
    .string "I've got a useful phone number\n"
    .string "for you.$"

BillHouse_Text_RecordedBillsNumber:
    .string "{PLAYER} recorded Bill's number.$"

BillHouse_Text_SisterRefusedNumber:
    .string "My brother made the PC Pokémon\n"
    .string "storage system.\p"
    .string "I was going to give you Bill's\n"
    .string "number…$"

BillHouse_Text_SisterPhoneFull:
    .string "You can't record any more numbers.$"

BillHouse_Text_SisterStorageSystem:
    .string "My big brother Bill made the PC\n"
    .string "Pokémon storage system.$"

GoldenrodCity_Bill_GiveEeveeOrPikachu::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_BILL_GIFTMON, GoldenrodCity_Bill_GiveEeveeOrPikachu_2
	msgbox GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_6
	release
	end

GoldenrodCity_Bill_GiveEeveeOrPikachu_2:
	msgbox GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_0
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_1, GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_2, GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_3
	switch VAR_RESULT
	case 0, GoldenrodCity_Bill_GiveEeveeOrPikachu_5
	case 1, GoldenrodCity_Bill_GiveEeveeOrPikachu_6
	msgbox GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_5
	release
	end

GoldenrodCity_Bill_GiveEeveeOrPikachu_5:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EEVEE_STARTER
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE_STARTER
	givemon SPECIES_EEVEE_STARTER, 25
	setflag FLAG_GOT_BILL_GIFTMON
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE_STARTER
	msgbox GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_4
	release
	end

GoldenrodCity_Bill_GiveEeveeOrPikachu_6:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_PIKACHU_STARTER
	bufferspeciesname STR_VAR_1, SPECIES_PIKACHU_STARTER
	givemon SPECIES_PIKACHU_STARTER, 25
	setflag FLAG_GOT_BILL_GIFTMON
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	bufferspeciesname STR_VAR_1, SPECIES_PIKACHU_STARTER
	msgbox GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_4
	release
	end


GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_0:
	.string "Bill: Hi, {PLAYER}! Do us a favor and\n"
	.string "take one of these two Pokémon. \p"
	.string "Both of them came over when I \n"
	.string "was adjusting the Time Capsule.\p"
	.string "I don't have time to take care \n"
	.string "of both of them even with help of\l"
	.string "my family. \p"
	.string "I think both of them have some special\n"
	.string "characteristics, so can I count on you\l"
	.string "to take either one, {PLAYER}?$"

GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_1:
	.string "Eevee$"

GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_2:
	.string "Pikachu$"

GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_3:
	.string "No thanks$"

GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_4:
	.string "Bill: I knew you'd come through!\n"
	.string "Way to go! I'm counting on you\l"
	.string "to take good care of it!$"

GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_5:
	.string "Oh… Now what to do?$"

GoldenrodCity_Bill_GiveEeveeOrPikachu_Text_6:
	.string "Come to think of it. I've heard rumours\n"
	.string "of rare Pokémon being distributed in\l"
	.string "the Game Corner.$"
