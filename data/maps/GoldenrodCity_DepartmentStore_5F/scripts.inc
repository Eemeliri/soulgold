
GoldenrodCity_DepartmentStore_5F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
    map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodDeptSundayNpc
	.byte 0


GoldenrodDeptStore5_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Girl::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_5FReceptionistOhYourMon:
    .string "Hello. Oh, your Pokémon…$"

GoldenrodDeptStore_Text_5FReceptionistWait:
    .string "Wait, I already gave you that TM!$"

GoldenrodDeptStore_Text_5FReceptionistPutInSomeMoreEffort:
	.string "Hmm…\n"
	.string "It's not bad, but it's also not good.\p"
	.string "You, as the Trainer, need to put in\n"
	.string "some more effort.$"


GoldenrodDeptStore_Text_5FReceptionistThisMoveShouldBePerfect:
    .string "Every evening we hand out free samples of TM. Please, take this.$"

GoldenrodDeptStore_Text_5FReceptionistThisMoveShouldBePerfect2:
    .string "We hope that you found use for the TM.$"

GoldenrodDeptStore_Text_5FReceptionistItLooksEvilHowAboutThisTM:
    .string "It looks evil. How about this TM\n"
    .string "for it?$"

GoldenrodDeptStore_Text_5FReceptionistThereAreTMsPerfectForMon:
    .string "There are sure to be TMs that are\n"
    .string "just perfect for your Pokémon.$"

GoldenrodDeptStore_Text_5FLass:
    .string "During evenings, a lady comes to hand\n"
    .string "out free TMs!$"

GoldenrodDeptStore_Text_5FPokefanM:
    .string "You can't rename a Pokémon you get\n"
    .string "in a trade.\p"
    .string "The name is a reflection of the\n"
    .string "original trainer's feelings for it.$"

GoldenrodDeptStore_Text_Girl:
	.string "A kind lady gave me Return\n"
    .string "last evening!$"

GoldenrodDeptStore_Text_5FDirectory:
    .string "Customize Your Pokémon\p"
    .string "5F TM Corner$"

GoldenrodDeptSundayNpc::
	compare VAR_DAY_OF_WEEK, 0
	goto_if_ne GoldenrodDeptSundayNpc_1
	return

GoldenrodDeptSundayNpc_1:
	setflag FLAG_TEMP_A
	return


Goldenrod_F5_ReturnClerk::
	lock
	goto_if_set FLAG_GOT_RETURN, Goldenrod_F5_ReturnClerk_2
	msgbox Goldenrod_F5_ReturnClerk_Text_1
	giveitem ITEM_TM_RETURN
	setflag FLAG_GOT_RETURN
	msgbox Goldenrod_F5_ReturnClerk_Text_0
	release
	end

Goldenrod_F5_ReturnClerk_2:
	msgbox Goldenrod_F5_ReturnClerk_Text_0
	release
	end


GoldenrodDept5FMart::
	lock
	msgbox GoldenrodDept5FMart_Text_0
	waitmessage
	pokemart Goldenrod_F5_TMMart
	msgbox GoldenrodDept5FMart_Text_1
	release
	end


	.align 2
Goldenrod_F5_TMMart:
	.2byte ITEM_TM_PROTECT
	.2byte ITEM_TM_REFLECT
	.2byte ITEM_TM_LIGHT_SCREEN
	.2byte ITEM_TM_DIG
	.2byte ITEM_TM_FIRE_PUNCH
	.2byte ITEM_TM_ICE_PUNCH
	.2byte ITEM_TM_THUNDER_PUNCH
	.2byte ITEM_TM_HYPER_BEAM
	.2byte ITEM_NONE

Goldenrod_F5_ReturnClerk_Text_0:
	.string "Return grows in power the more your\n"
	.string "Pokémon loves you!$"

Goldenrod_F5_ReturnClerk_Text_1:
	.string "We're currently handing out free\n"
	.string "samples of our most popular TM. \p"
	.string "Here, have one!$"

GoldenrodDept5FMart_Text_0:
	.string "Welcome to the TMs department!$"

GoldenrodDept5FMart_Text_1:
	.string "Come back soon!$"
