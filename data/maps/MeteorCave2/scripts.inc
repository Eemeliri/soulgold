MeteorCave2_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorCave2_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

MeteorCave2_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_ALL_FUTUREMONS, MeteorCave2_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

MeteorCave2_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 8, 32, 0x4D5, FALSE
	return


IronValiantEnc::
	lock
	faceplayer
	legendaryencounter SPECIES_IRON_VALIANT, 70, LOCALID_IRON_VALIANT, FLAG_HIDE_IRONVALIANT
	release
	end


AncientWallMet::
	lock
	goto_if_set FLAG_ALL_FUTUREMONS, AncientWallMet_2
	msgbox AncientWallMet_Text_1
	getcaughtmon SPECIES_IRON_TREADS
	compare VAR_RESULT, FALSE
	goto_if_eq AncientWallMet_5
AncientWallMet_4:
	getcaughtmon SPECIES_IRON_BUNDLE
	compare VAR_RESULT, FALSE
	goto_if_eq AncientWallMet_8
AncientWallMet_7:
	getcaughtmon SPECIES_IRON_HANDS
	compare VAR_RESULT, FALSE
	goto_if_eq AncientWallMet_11
AncientWallMet_10:
	getcaughtmon SPECIES_IRON_JUGULIS
	compare VAR_RESULT, FALSE
	goto_if_eq AncientWallMet_14
AncientWallMet_13:
	getcaughtmon SPECIES_IRON_MOTH
	compare VAR_RESULT, FALSE
	goto_if_eq AncientWallMet_17
AncientWallMet_16:
	getcaughtmon SPECIES_IRON_THORNS
	compare VAR_RESULT, FALSE
	goto_if_eq AncientWallMet_20
AncientWallMet_19:
	getcaughtmon SPECIES_IRON_VALIANT
	compare VAR_RESULT, FALSE
	goto_if_eq AncientWallMet_23
AncientWallMet_22:
	closemessage
	playse SE_BANG
	setmetatile 8, 32, 0x4D5, FALSE
	special DrawWholeMapView
	setflag FLAG_ALL_FUTUREMONS
	waitse
	release
	return

AncientWallMet_2:
	msgbox AncientWallMet_Text_0
	release
	end

AncientWallMet_5:
	goto MeteorCave1_NothingHappens
	goto AncientWallMet_4

AncientWallMet_8:
	goto MeteorCave1_NothingHappens
	goto AncientWallMet_7

AncientWallMet_11:
	goto MeteorCave1_NothingHappens
	goto AncientWallMet_10

AncientWallMet_14:
	goto MeteorCave1_NothingHappens
	goto AncientWallMet_13

AncientWallMet_17:
	goto MeteorCave1_NothingHappens
	goto AncientWallMet_16

AncientWallMet_20:
	goto MeteorCave1_NothingHappens
	goto AncientWallMet_19

AncientWallMet_23:
	goto MeteorCave1_NothingHappens
	goto AncientWallMet_22


AncientWallMet_Text_0:
	.string "The way is open.$"

AncientWallMet_Text_1:
	.string "There's an inscription on the wall.\p"
	.string "GATHER ALL\n"
	.string "OF THE FUTURE$"
