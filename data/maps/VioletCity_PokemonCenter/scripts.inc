
.set LOCALID_NURSE, 1

VioletCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_Pokecenter_OnTransition
	.byte 0

VioletCity_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_VIOLET_CITY
	end

VioletCity_PokemonCenter_EventScript_Aide::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TOGEPI_EGG, VioletCity_PokemonCenter_EventScript_Aide_Received
	msgbox VioletCity_PokeCenter_Text_ElmsAideFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end


VioletCity_PokemonCenter_EventScript_AideNoRoom::
	msgbox VioletCity_PokeCenter_Text_ElmsAideNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Refuse::
	msgbox VioletCity_PokeCenter_Text_ElmsAideRefuse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Accepted::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	giveegg SPECIES_TOGEPI
    call VioletPCGiveExpJar
    closemessage
	setflag FLAG_RECEIVED_TOGEPI_EGG
	setflag FLAG_HIDE_VIOLET_CITY_AIDE
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
	clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Received::
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EVentScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Man::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokeCenter_Text_ElmsAideFavor:
	.string "{PLAYER}, long time, no see.\p"
	.string "Prof. Elm asked me to find you.\p"
	.string "He has another favor to ask.\p"
	.string "Would you take the Pokémon Egg?$"

VioletCity_PokeCenter_Text_ElmsAideNoRoom:
	.string "{PLAYER}, long time, no see.\p"
	.string "Prof. Elm asked me to find you.\p"
	.string "He has another favor to ask.\p"
	.string "Would you take the Pokémon Egg?\p"
	.string "Oh, wait... You need to make room\n"
	.string "in your party first.$"

VioletCity_PokeCenter_Text_ElmsAideGiveEgg:
	.string "We discovered that a Pokémon won't\n"
	.string "hatch until it grows in the Egg.\p"
	.string "It also has to be with other\n"
	.string "active Pokémon to hatch.\p"
	.string "{PLAYER}, you're the only person\n"
	.string "we can rely on.$"

VioletCity_PokeCenter_Text_ElmsAideGiveItem:
	.string "Oh, and this might help when it hatches.$"

VioletCity_PokeCenter_Text_ElmsAideFullParty:
	.string "Oh, no. You can't carry any more\n"
	.string "Pokémon with you.\p"
	.string "I'll wait here while you make\n"
	.string "room for the Egg.$"

VioletCity_PokeCenter_Text_ElmsAideRefuse:
	.string "B-but… Prof. Elm asked for you…$"

VioletCity_PokeCenter_Text_FarawayLink:
	.string "I've been thinking it'd be great\n"
	.string "to link up and battle with my\n"
	.string "friends who live far away.$"

VioletCity_PokeCenter_Text_MobileAdapter:
	.string "I just battled a friend in\n"
	.string "Cianwood over a link.\p"
	.string "If you connect a Mobile Adapter,\n"
	.string "you can link with a friend far\n"
	.string "away.$"

VioletCity_PokeCenter_Text_GameboyKid:
	.string "A guy named Bill made the\n"
	.string "Pokémon PC storage system.$"

VioletCity_PokeCenter_Text_Gentleman:
	.string "It was around three years ago.\p"
	.string "Team Rocket was up to no good\n"
	.string "with Pokémon.\p"
	.string "But justice prevailed--a young\n"
	.string "kid broke 'em up.$"

VioletCity_PokeCenter_Text_Youngster:
	.string "Pokémon are smart. They won't\n"
	.string "obey a trainer they don't respect.\p"
	.string "Without the right Gym Badges,\n"
	.string "they will just do as they please.$"

VioletPCGiveExpJar::
	msgbox VioletPCGiveExpJar_Text_0
	giveitem ITEM_CANDY_JAR
	msgbox VioletPCGiveExpJar_Text_1
	return


VioletPCGiveExpJar_Text_0:
	.string "You should also take this for raising\n"
	.string "more Pokémon.$"

VioletPCGiveExpJar_Text_1:
	.string "{PLAYER}, you're the only \n"
	.string "person we can rely on.$"
