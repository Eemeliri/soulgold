
GoldenrodCity_FlowerShop_MapScripts::
	.byte 0

GoldenrodCity_FlowerShop_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Normal
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner2, MSGBOX_DEFAULT
	giveitem ITEM_SQUIRTBOTTLE
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Normal::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria1::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Floria3
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_Floria2
	msgbox GoldenrodCity_FlowerShop_Text_Floria, MSGBOX_DEFAULT
	closemessage
	release
	end
	
GoldenrodCity_FlowerShop_EventScript_Floria2::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria3::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaItWasAMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY, Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry
	msgbox Route104_PrettyPetalFlowerShop_Text_ImGrowingFlowers, MSGBOX_DEFAULT
	random 8
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry::
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_MintOwner::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, Route104_PrettyPetalFlowerShop_EventScript_NoSellMints
	msgbox Route104_PrettyPetalFlowerShop_Text_Mints1, MSGBOX_DEFAULT
	waitmessage
	pokemart Route104_PrettyPetalFlowerShop_MintShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_Text_Mints1:
	.string "Our Nature Mints are back!\n"
	.string "Have a look!$"

Route104_PrettyPetalFlowerShop_Text_Mints2:
	.string "Hi, dear trainer. If you are looking\n"
	.string "to buy Nature Mints, you should have\l"
	.string "come earlier. I just sold the last one.\n"
	.string "Come back later.$"

	.align 2
Route104_PrettyPetalFlowerShop_MintShop:
	.2byte ITEM_SERIOUS_MINT
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_CAREFUL_MINT
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
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_NoSellMints::
	msgbox Route104_PrettyPetalFlowerShop_Text_Mints2, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_AlreadyMet::
	msgbox Route104_PrettyPetalFlowerShop_Text_LearnAboutBerries, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries
	call_if_eq VAR_RESULT, NO, Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries::
	msgbox Route104_PrettyPetalFlowerShop_Text_BerriesExplanation, MSGBOX_DEFAULT
	return

Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries::
	msgbox Route104_PrettyPetalFlowerShop_Text_FlowersBringHappiness, MSGBOX_DEFAULT
	return

GoldenrodCity_FlowerShop_Text_Floria:
	.string "When I told my sis about the jiggly\n"
	.string "tree, she said it's dangerous.\p"
	.string "If I beat Whitney, I wonder if\n"
	.string "she'll lend me her water bottle…$"

GoldenrodCity_FlowerShop_Text_Owner1:
.string "Apparently, there is an odd tree\n"
.string "on Route 36.\p"
.string "They say it dances when you water\n"
.string "it...\p"
.string "Oh, of course not!\p"
.string "This is a flower shop, so we do\n"
.string "have watering cans...\p"
.string "But I cannot let you have one!\n"
.string "It's too dangerous!\p"
.string "Well, maybe if you manage to\n"
.string "defeat gym leader Whitney, it\l"
.string "might be okay.$"

GoldenrodCity_FlowerShop_Text_Owner2:
.string "Apparently, there is an odd tree\n"
.string "on Route 36.\p"
.string "They say it dances when you water\n"
.string "it...\p"
.string "Oh, that's a Plainbadge from\n"
.string "The Goldenrod Gym!\p"
.string "Did you defeat Whitney?!\p"
.string "Well, then there's nothing to worry\n"
.string "about, is there?\p"
.string "I'll let you use this Squirtbottle\n"
.string "for a while then.\l"
.string "...\p"
.string "Oh, never mind. Keep it!$"

GoldenrodCity_FlowerShop_Text_Owner3:
.string "The odd tree is on Route 36.\n"
.string "Please be careful!$"

GoldenrodCity_FlowerShop_Text_Owner4:
    .string "Lalala lalalala. Have plenty of\n"
    .string "water, my lovely!$"

GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney:
    .string "Wow, you beat Whitney? Cool!$"

GoldenrodCity_FlowerShop_Text_FloriaItWasAMon:
    .string "So it really was a Pokémon!$"

FlowerShopMulchVendor::
	lock
	faceplayer
	msgbox FlowerShopMulchVendor_Text_0
	goto_if_set FLAG_BADGE06_GET, FlowerShopMulchVendor_2
	pokemart FlowerShopMulches
	msgbox FlowerShopMulchVendor_Text_2
FlowerShopMulchVendor_1:
	release
	end

FlowerShopMulchVendor_2:
	pokemart FlowerShopMulchesSixBadges
	msgbox FlowerShopMulchVendor_Text_1
	goto FlowerShopMulchVendor_1


	.align 2
FlowerShopMulches:
	.2byte ITEM_GRASSY_SEED
	.2byte ITEM_LUMINOUS_MOSS
	.2byte ITEM_GROWTH_MULCH
	.2byte ITEM_DAMP_MULCH
	.2byte ITEM_STABLE_MULCH
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_NONE

	.align 2
FlowerShopMulchesSixBadges:
	.2byte ITEM_CHILAN_BERRY
	.2byte ITEM_OCCA_BERRY
	.2byte ITEM_PASSHO_BERRY
	.2byte ITEM_WACAN_BERRY
	.2byte ITEM_RINDO_BERRY
	.2byte ITEM_YACHE_BERRY
	.2byte ITEM_CHOPLE_BERRY
	.2byte ITEM_KEBIA_BERRY
	.2byte ITEM_SHUCA_BERRY
	.2byte ITEM_COBA_BERRY
	.2byte ITEM_PAYAPA_BERRY
	.2byte ITEM_TANGA_BERRY
	.2byte ITEM_CHARTI_BERRY
	.2byte ITEM_KASIB_BERRY
	.2byte ITEM_HABAN_BERRY
	.2byte ITEM_COLBUR_BERRY
	.2byte ITEM_BABIRI_BERRY
	.2byte ITEM_ROSELI_BERRY
	.2byte ITEM_GRASSY_SEED
	.2byte ITEM_LUMINOUS_MOSS
	.2byte ITEM_GROWTH_MULCH
	.2byte ITEM_DAMP_MULCH
	.2byte ITEM_STABLE_MULCH
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_NONE

UniversityFlorist::
	lock
	faceplayer
	msgbox UniversityFlorist_Text_0
	checkspecies SPECIES_SHAYMIN
	compare VAR_RESULT, TRUE
	goto_if_eq UniversityFlorist_2
UniversityFlorist_1:
	release
	end

UniversityFlorist_2:
	goto GiveGracidea
	goto UniversityFlorist_1


GiveGracidea::
	goto_if_set FLAG_GOT_GRACIDEA, GiveGracidea_2
	playse SE_PIN
	applymovement 5, Common_Movement_ExclamationMark
	waitse
	waitmovement 0
	msgbox GiveGracidea_Text_1
	giveitem ITEM_GRACIDEA
	msgbox GiveGracidea_Text_0
	setflag FLAG_GOT_GRACIDEA
	release
	end

GiveGracidea_2:
	msgbox GiveGracidea_Text_0
	release
	end


FlowerShopMulchVendor_Text_0:
	.string "Welcome! Have a look at our inventory!$"

FlowerShopMulchVendor_Text_1:
	.string "Thank you! Come again!$"

FlowerShopMulchVendor_Text_2:
	.string "Thank you, we hope to stock some \n"
	.string "rare berries in the near future!$"

UniversityFlorist_Text_0:
	.string "I'm studying to become a botanist!\p"
	.string "I strive to learn all about rare\n"
	.string "plants and flowers!$"

GiveGracidea_Text_0:
	.string "It is said that Shaymin can\n"
	.string "change its form with that flower.$"

GiveGracidea_Text_1:
	.string "Oh! That Pokémon you have!\p"
	.string "It really is a Shaymin!\p"
	.string "I have read about it, but I would never\n"
	.string "have even dreamed of seeing it!\p"
	.string "Please, you should try giving it this\n"
	.string "flower.$"
