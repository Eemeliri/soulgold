Route40_House5_MapScripts::
	.byte 0


Route40Cafe_InpatientWoman::
	lock
	faceplayer
	msgbox Route40Cafe_InpatientWoman_Text_0
	release
	end


Route40Cafe_Fatman::
	lock
	faceplayer
	msgbox Route40Cafe_Fatman_Text_0
	release
	end


Route40Cafe_Rocker::
	lock
	msgbox Route40Cafe_Rocker_Text_0
	release
	end


Route40Cafe_Lady::
	lock
	faceplayer
	msgbox Route40Cafe_Lady_Text_0
	release
	end


Route40Cafe_SellerLady::
	lock
	faceplayer
	msgbox Route40Cafe_SellerLady_Text_0
	pokemart CafeCook2
	msgbox Route40Cafe_SellerLady_Text_1
	release
	end


Route40Cafe_SellerCook::
	lock
	faceplayer
	msgbox Route40Cafe_SellerCook_Text_0
	pokemart CafeCook
	msgbox Route40Cafe_SellerCook_Text_1
	release
	end


	.align 2
CafeCook:
	.2byte ITEM_SWEET_APPLE
	.2byte ITEM_TART_APPLE
	.2byte ITEM_SYRUPY_APPLE
	.2byte ITEM_FRESH_WATER
	.2byte ITEM_SODA_POP
	.2byte ITEM_LEMONADE
	.2byte ITEM_SWEET_HEART
	.2byte ITEM_PEWTER_CRUNCHIES
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_OLD_GATEAU
	.2byte ITEM_CASTELIACONE
	.2byte ITEM_LUMIOSE_GALETTE
	.2byte ITEM_SHALOUR_SABLE
	.2byte ITEM_BIG_MALASADA
	.2byte ITEM_NONE

	.align 2
CafeCook2:
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_SERIOUS_MINT
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_HASTY_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_LAX_MINT
	.2byte ITEM_LONELY_MINT
	.2byte ITEM_MILD_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_NAIVE_MINT
	.2byte ITEM_NAUGHTY_MINT
	.2byte ITEM_QUIET_MINT
	.2byte ITEM_RASH_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_SASSY_MINT
	.2byte ITEM_TIMID_MINT
	.2byte ITEM_NONE

Route40Cafe_InpatientWoman_Text_0:
	.string "Where's my order?! I've been waiting for\n"
	.string "10 minutes already!$"

Route40Cafe_Fatman_Text_0:
	.string "This cafe has been a hit among the \n"
	.string "tourists ever since it opened last year.$"

Route40Cafe_Rocker_Text_0:
	.string "I'll have uhh...$"

Route40Cafe_Lady_Text_0:
	.string "I bought a mint from the lady over\n"
	.string "there and my Pokémon's nature changed!$"

Route40Cafe_SellerLady_Text_0:
	.string "Welcome! We sell mints for Pokémon!$"

Route40Cafe_SellerLady_Text_1:
	.string "We hope to see you again!$"

Route40Cafe_SellerCook_Text_0:
	.string "Welcome, what will you have?$"

Route40Cafe_SellerCook_Text_1:
	.string "Come back soon!$"
