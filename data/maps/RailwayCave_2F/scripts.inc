RailwayCave_2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RailwayCave_2F_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

RailwayCave_2F_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_SUS_RAILWAY_DOOR, RailwayCave_2F_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

RailwayCave_2F_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 73, 10, 0x45A, FALSE
	setmetatile 73, 9, 0x452, FALSE
	return



RailwayCave_BrailleRegisteel:
	.braille "THE ONE WHO\n"
	.braille "CLANGS THE\n"
	.braille "SCALES.$"

RailwayCave_SusDoor::
	lock
	msgbox RailwayCave_SusDoor_Text_0
	closemessage
	braillemsgbox RailwayCave_BrailleRegisteel
	checkspecies SPECIES_KOMMO_O
	compare VAR_RESULT, TRUE
	goto_if_eq RailwayCave_SusDoor_2
RailwayCave_SusDoor_1:
	release
	end

RailwayCave_SusDoor_2:
	setflag FLAG_SUS_RAILWAY_DOOR
	setmetatile 73, 10, 0x45A, FALSE
	setmetatile 73, 9, 0x452, FALSE
	playse SE_EXIT
	special DrawWholeMapView
	goto RailwayCave_SusDoor_1


RailwayCave_TrainerBob::
	trainerbattle_single TRAINER_RAILWAYBOB, RailwayCave_TrainerBob_Text_0, RailwayCave_TrainerBob_Text_1
	msgbox RailwayCave_TrainerBob_Text_2, MSGBOX_AUTOCLOSE
	return


RailwayCave_TrainerMason::
	trainerbattle_single TRAINER_RAILWAYMASON, RailwayCave_TrainerMason_Text_0, RailwayCave_TrainerMason_Text_1
	msgbox RailwayCave_TrainerMason_Text_2, MSGBOX_AUTOCLOSE
	return


RailwayCave_TrainerYoda::
	trainerbattle_single TRAINER_RAILWAYYODA, RailwayCave_TrainerYoda_Text_0, RailwayCave_TrainerYoda_Text_1
	msgbox RailwayCave_TrainerYoda_Text_2, MSGBOX_AUTOCLOSE
	return


RailwayCave_TrainerSanada::
	trainerbattle_single TRAINER_RAILWAYSANADA, RailwayCave_TrainerSanada_Text_0, RailwayCave_TrainerSanada_Text_1
	msgbox RailwayCave_TrainerSanada_Text_2, MSGBOX_AUTOCLOSE
	return


RailwayCave_SusDoor_Text_0:
	.string "Something is carved on the door...$"

RailwayCave_TrainerBob_Text_0:
	.string "Did you know? Digletts and Dugtrios\n"
	.string "helped us dig these tunnels.$"

RailwayCave_TrainerBob_Text_1:
	.string "Did you know? It still took many years\n"
	.string "to complete!$"

RailwayCave_TrainerBob_Text_2:
	.string "Did you know? This crag is much harder\n"
	.string "than the average mountain rock. \l"
	.string "It has a lot of metal mixed into it, \l"
	.string "making digging take more time.$"

RailwayCave_TrainerMason_Text_0:
	.string "Ow! Something latched onto my foot!$"

RailwayCave_TrainerMason_Text_1:
	.string "Oh, it was only my Stunfisk!$"

RailwayCave_TrainerMason_Text_2:
	.string "Stunfisk like to burrow into the ground\n"
	.string "here. They seem to enjoy the\l"
	.string "atmosphere.$"

RailwayCave_TrainerYoda_Text_0:
	.string "Hya! The electricity running though the\n"
	.string "air is great for my muscles!$"

RailwayCave_TrainerYoda_Text_1:
	.string "We must keep training!$"

RailwayCave_TrainerYoda_Text_2:
	.string "The jolts of electricity that run here\n"
	.string "are great for relaxing the muscles\l"
	.string "after a long workout!$"

RailwayCave_TrainerSanada_Text_0:
	.string "This is the maintenance tunnel for\n"
	.string "the train tracks, how did you get in?$"

RailwayCave_TrainerSanada_Text_1:
	.string "I'm reporting this to my superiors!$"

RailwayCave_TrainerSanada_Text_2:
	.string "Just because you can run into\n"
	.string "any place you want with your Pokémon\l"
	.string "doesn't mean you should!$"
