MtMortar_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMortar_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtMortar_B1F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

MountMortar4_EventScript_Kiyo::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TYROGUE, MountMortar4_EventScript_KiyoAfter
	goto_if_set FLAG_BEAT_KIYO, MountMortar4_EventScript_KiyoTryGiveTyrogue
	msgbox MountMortar4_Text_KiyoIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KIYO, MountMortar4_Text_KiyoWin
	setflag FLAG_BEAT_KIYO
MountMortar4_EventScript_KiyoTryGiveTyrogue::
	createfieldmugshot MUGSHOT_BLACK_BELT
	msgbox MountMortar4_Text_KiyoTyrogueReward, MSGBOX_DEFAULT
	@HnS gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TYROGUE
	bufferspeciesname STR_VAR_1, SPECIES_TYROGUE
	removefieldmugshot
	givemon SPECIES_TYROGUE, 25
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setflag FLAG_GOT_TYROGUE
MountMortar4_EventScript_KiyoAfter::
	msgbox MountMortar4_Text_KiyoGotTyrogue, MSGBOX_DEFAULT
	closemessage
	release
	end


MountMortar4_Text_KiyoIntro:
	.string "Hey!\p"
	.string "I am the Karate King!\n"
	.string "I train alone here in the dark!\p"
	.string "You! Battle with me!\n"
	.string "Hwaaarggh!$"

MountMortar4_Text_KiyoWin:
	.string "Waaaarggh!\n"
	.string "I'm beaten!$"

MountMortar4_Text_KiyoTyrogueReward:
	.string "I... I'm crushed...\p"
	.string "My training is still not\n"
	.string "enough...\p"
	.string "But a loss is a loss.\n"
	.string "I admit it.\p"
	.string "As proof that you defeated me,\n"
	.string "I'll give you a rare fighting\l"
	.string "Pokémon.$"

MountMortar4_Text_ReceiveTyrogue:
	.string "{PLAYER} received Tyrogue.$"

MountMortar4_Text_KiyoGotTyrogue:
	.string "Tyrogue is a Fighting-type.\p"
	.string "It evolves into a tougher\n"
	.string "Pokémon.\p"
	.string "Keep up the hard work.\n"
	.string "I'll keep training too.\p"
	.string "Farewell!$"

MountMortar4_Text_KiyoFullParty:
	.string "You have no room in your party!$"
