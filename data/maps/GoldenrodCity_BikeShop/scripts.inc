
GoldenrodCity_BikeShop_MapScripts::
	.byte 0

GoldenrodCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, receivedBikePostDialogue
	msgbox GoldenrodCity_BikeShop_Text_ClerkIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed
	msgbox GoldenrodCity_BikeShop_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed::
	msgbox GoldenrodCity_BikeShop_Text_ClerkAgreed, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	setflag FLAG_RECEIVED_BIKE
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived::
	msgbox GoldenrodCity_BikeShop_Text_Mainshop, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk2::
	lock
	faceplayer
	msgbox GoldenrodCity_BikeShop_Text_Clerk2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Bike::
	lock
	msgbox GoldenrodCity_BikeShop_Text_Bicycle, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Clerk2:
	.string "Riding the bike is as simple as\n"
	.string "pressing a button if you\l"
	.string "Register it from the Bag.$"

GoldenrodCity_BikeShop_Text_ClerkIntro:
    .string "…sigh… I moved here, but I can't\n"
    .string "sell my Bicycles. Why is that?\p"
    .string "Could you ride a Bicycle and\n"
    .string "advertise for me?$"

GoldenrodCity_BikeShop_Text_ClerkAgreed:
    .string "Really? Great!\p"
    .string "Give me your name and phone number,\n"
    .string "and I'll loan you a Bicycle.$"

GoldenrodCity_BikeShop_Text_BorrowedBicycle:
    .string "{PLAYER} borrowed a Bicycle.$"

GoldenrodCity_BikeShop_Text_Mainshop:
	.string "The main shop is at Cerulean back\n"
	.string "in Kanto.\p"
	.string "Say hello to the shop manager if\n"
	.string "if you happen to go there!$"

GoldenrodCity_BikeShop_Text_Refused:
    .string "…sigh… Oh, for the kindness of\n"
    .string "people…$"

GoldenrodCity_BikeShop_Text_JustReleasedCompact:
    .string "Just released!\p"
    .string "First-rate compact Bicycles!$"

GoldenrodCity_BikeShop_Text_Bicycle:
    .string "It's a shiny new Bicycle!$"

receivedBikePostDialogue::
	goto_if_set FLAG_SYS_GAME_CLEAR, receivedBikePostDialogue_2
	msgbox receivedBikePostDialogue_Text_1
	closemessage
	release
	end

receivedBikePostDialogue_2:
	msgbox receivedBikePostDialogue_Text_0
	closemessage
	release
	end


receivedBikePostDialogue_Text_0:
	.string "Hey kid! Thanks to you, my business\n"
	.string "is booming! I owe it to you!$"

receivedBikePostDialogue_Text_1:
	.string "I hope people start paying attention\n"
	.string "to my Bicycles now!$"
