VajraDesert_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, VajraDesert_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

VajraDesert_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_SUS_DESERT_DOOR, VajraDesert_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

VajraDesert_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 37, 6, 0x4AE, FALSE
	return


VajraDesert_ManSighing::
	msgbox VajraDesert_ManSighing_Text_0, MSGBOX_NPC
	return


VajraDesert_TrainerJill::
	trainerbattle_single TRAINER_JILL, VajraDesert_TrainerJill_Text_0, VajraDesert_TrainerJill_Text_1
	msgbox VajraDesert_TrainerJill_Text_2, MSGBOX_AUTOCLOSE
	return


VajraDesert_TrainerRodaros::
	trainerbattle_single TRAINER_RODAROS, VajraDesert_TrainerRodaros_Text_0, VajraDesert_TrainerRodaros_Text_1
	msgbox VajraDesert_TrainerRodaros_Text_2, MSGBOX_AUTOCLOSE
	return


VajraDesert_TrainerBelmare::
	trainerbattle_single TRAINER_BELMARE, VajraDesert_TrainerBelmare_Text_0, VajraDesert_TrainerBelmare_Text_1
	msgbox VajraDesert_TrainerBelmare_Text_2, MSGBOX_AUTOCLOSE
	return


VajraDesert_TrainerKennedy::
	trainerbattle_single TRAINER_KENNEDY, VajraDesert_TrainerKennedy_Text_0, VajraDesert_TrainerKennedy_Text_1
	msgbox VajraDesert_TrainerKennedy_Text_2, MSGBOX_AUTOCLOSE
	return



VajraDesert_BrailleRegirock:
	.braille "TYRANT OF\n"
	.braille "THE DESERT\n"
	.braille "FULLY EVOLVED.$"

VajraDesert_SusDoor::
	lock
	msgbox VajraDesert_SusDoor_Text_0
	closemessage
	braillemsgbox VajraDesert_BrailleRegirock
	checkspecies SPECIES_TYRANITAR
	compare VAR_RESULT, TRUE
	goto_if_eq VajraDesert_SusDoor_2
VajraDesert_SusDoor_1:
	release
	end

VajraDesert_SusDoor_2:
	setflag FLAG_SUS_DESERT_DOOR
	setmetatile 37, 6, 0x4AE, FALSE
	playse SE_EXIT
	special DrawWholeMapView
	goto VajraDesert_SusDoor_1


VajraDesertWest_GrottoDoor::
	msgbox VajraDesertWest_GrottoDoor_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq VajraDesertWest_GrottoDoor_2
VajraDesertWest_GrottoDoor_1:
	release
	end

VajraDesertWest_GrottoDoor_2:
	warp MAP_HIDDEN_GROTTO_UNUSED, 0
	waitstate
	goto VajraDesertWest_GrottoDoor_1


VajraDesertWest_WestSign::
	msgbox VajraDesertWest_WestSign_Text_0, MSGBOX_SIGN
	return


VajraDesertWest_EastSign::
	msgbox VajraDesertWest_EastSign_Text_0, MSGBOX_SIGN
	return


VajraDesert_ManSighing_Text_0:
	.string "Man... The sandpits seem terrible at\n"
	.string "this moment. The path to the village\l"
	.string "is blocked. I hope it clears up soon.$"

VajraDesert_TrainerJill_Text_0:
	.string "I read in a magazine that training in\n"
	.string "harsh environments is great for you!$"

VajraDesert_TrainerJill_Text_1:
	.string "I wanna go home...$"

VajraDesert_TrainerJill_Text_2:
	.string "I should've listened to mom, that\n"
	.string "magazine was really sketchy...$"

VajraDesert_TrainerRodaros_Text_0:
	.string "Behold the might of the sandstorm!$"

VajraDesert_TrainerRodaros_Text_1:
	.string "Gah! Sand in my mouth!$"

VajraDesert_TrainerRodaros_Text_2:
	.string "The area can be unstable with the\n"
	.string "sandpits shifting around by phases\l"
	.string "of the moon.$"

VajraDesert_TrainerBelmare_Text_0:
	.string "Let me show you my cutest Pokémon!$"

VajraDesert_TrainerBelmare_Text_1:
	.string "Oh dear...$"

VajraDesert_TrainerBelmare_Text_2:
	.string "My Maractus is absolutely the most\n"
	.string "adorable Pokémon. We come here to\l"
	.string "sunbathe!$"

VajraDesert_TrainerKennedy_Text_0:
	.string "Overcoming harsh ordeals with your\n"
	.string "Pokémon is the spirit of the journey!$"

VajraDesert_TrainerKennedy_Text_1:
	.string "Marvelous battling skills!$"

VajraDesert_TrainerKennedy_Text_2:
	.string "I've lived in the nearby village for the\n"
	.string "past 40 years, we've never missed a\l"
	.string "training day.$"

VajraDesert_SusDoor_Text_0:
	.string "Something is carved on the door...$"

VajraDesertWest_GrottoDoor_Text_0:
	.string "There seems to be a small path in\n"
	.string "the sand. Enter?$"

VajraDesertWest_WestSign_Text_0:
	.string "Vajra Desert\n"
	.string "{RIGHT_ARROW} Rinto Village$"

VajraDesertWest_EastSign_Text_0:
	.string "{UP_ARROW}{RIGHT_ARROW} Rinto Village$"
