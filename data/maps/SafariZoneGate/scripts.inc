
SafariZoneGate_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SafariZoneGate_OnTransition
	.byte 0

SafariZoneGate_OnTransition::
	setflag FLAG_VISITED_SAFARI_ZONE_GATE
	call_if_eq VAR_ROUTE27_BAOBA_CALL, 1, SafariZoneGate_EventScript_RestoreWestExpansion
	call_if_eq VAR_SAFFRON_CITY_STATE, 1, SafariZoneGate_EventScript_RestoreEastExpansion
	end

SafariZoneGate_EventScript_Trigger::
	setflag FLAG_VISITED_SAFARI_ZONE_GATE
	setvar VAR_SAFARI_ZONE_GATE_STATE, 3
	end

SafariZoneGate_EventScript_WorkerM::
	lock
	faceplayer
	msgbox SafariZone_Text_ForeignFeeling, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_Silent::
	lock
	faceplayer
	msgbox SafariZone_Text_SilentNPC, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_Kangaskhan::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_NORMAL
	msgbox SafariZone_Text_Kangaskhan, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SafariZoneGate_EventScript_Engineer::
	lock
	faceplayer
	msgbox SafariZone_Text_JigglypuffTrainer, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_Girl::
	lock
	faceplayer
	msgbox SafariZone_Text_FirstCatch, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_SlowpokeLady::
	lock
	faceplayer
	msgbox SafariZone_Text_SlowpokeFan, MSGBOX_DEFAULT
	closemessage
	release
	end


SafariZone_Text_ForeignFeeling:
	.string "Safari Zone...\n"
	.string "It makes me feel like I am in a\l"
	.string "foreign country.\p"
	.string "It brings up a strange feeling.$"

SafariZone_Text_SilentNPC:
	.string "..................\p"
	.string "(I am not a talker.)$"

SafariZone_Text_Kangaskhan:
	.string "Kangaskhan: ..................$"

SafariZone_Text_JigglypuffTrainer:
	.string "This Safari Zone is great!\n"
	.string "I just kept going after Pokémon!\p"
	.string "That made my Jigglypuff upset though.$"

SafariZone_Text_FirstCatch:
	.string "I have always wanted to catch my first\n"
	.string "Pokémon at the Safari Zone.$"

SafariZone_Text_SlowpokeFan:
	.string "There are many Pokémon to choose from,\n"
	.string "but nothing beats the cuteness of\l"
	.string "Slowpoke.\p"
	.string "People often say that I look like one!$"

SafariZone_Text_CustomSystem:
	.string "You may be under the impression there\n"
	.string "is a sophisticated system to\l"
	.string "customizing the Safari Zone, right?\p"
	.string "The real truth is that...$"

SafariZone_Text_Sign:
	.string "Safari Zone\n"
	.string "This is where everything is thrilling.\p"
	.string "Feel free to come by and experience\n"
	.string "the wild!$"


SafariZoneGate_EventScript_IncenseClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SafariZoneGateMart1
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SafariZoneGate_Pokemart_Incenses:
	.2byte ITEM_SEA_INCENSE
	.2byte ITEM_LAX_INCENSE
	.2byte ITEM_ROCK_INCENSE
	.2byte ITEM_FULL_INCENSE
	.2byte ITEM_WAVE_INCENSE
	.2byte ITEM_ROSE_INCENSE
	.2byte ITEM_PURE_INCENSE
	.2byte ITEM_LUCK_INCENSE
	.2byte ITEM_NONE
	release
	end


SafariZoneGate_EventScript_IncenseClerkFinite::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SafariZoneGate_Pokemart_Incenses
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SafariZoneGate_EventScript_VitaminGuru::
	lock
	faceplayer
	message SafariZoneGate_Text_VitaminGuruSellWhatYouNeed
	waitmessage
	pokemart SafariZoneGateMart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end


SafariZoneGate_Text_VitaminGuruSellWhatYouNeed:
	.string "I'm the rare item Guru! I'll go for it and\n"
	.string "sell you what you need!$"

SafariZoneGate_EventScript_RestoreWestExpansion::
	setflag FLAG_SAFARI_ZONE_WEST_EXPANSION
	return

SafariZoneGate_EventScript_RestoreEastExpansion::
	setflag FLAG_SAFARI_ZONE_EAST_EXPANSION
	return

	.align 2
SafariZoneGateMart1:
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_LINKING_CORD
	.2byte ITEM_NONE

	.align 2
SafariZoneGateMart2:
	.2byte ITEM_TM_VENOSHOCK
	.2byte ITEM_TM_GIGA_IMPACT
	.2byte ITEM_TM_LOW_SWEEP
	.2byte ITEM_CRACKED_POT
	.2byte ITEM_CHIPPED_POT
	.2byte ITEM_UPGRADE
	.2byte ITEM_NONE
