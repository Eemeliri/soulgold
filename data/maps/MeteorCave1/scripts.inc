MeteorCave1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorCave1_MapScripts_MAP_SCRIPT_ON_LOAD
	map_script MAP_SCRIPT_ON_TRANSITION, MeteorCave1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

MeteorCave1_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_ALL_PASTMONS, MeteorCave1_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

MeteorCave1_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	setmetatile 36, 2, 0x4DD, FALSE
	return

MeteorCave1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_VISITED_METEOR_CAVE
	end


MeteorCave1_WallIns::
	lock
	goto_if_set FLAG_ALL_PASTMONS, MeteorCave1_WallIns_2
	msgbox MeteorCave1_WallIns_Text_1
	getcaughtmon SPECIES_GREAT_TUSK
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_WallIns_5
MeteorCave1_WallIns_4:
	getcaughtmon SPECIES_SCREAM_TAIL
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_WallIns_8
MeteorCave1_WallIns_7:
	getcaughtmon SPECIES_BRUTE_BONNET
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_WallIns_11
MeteorCave1_WallIns_10:
	getcaughtmon SPECIES_FLUTTER_MANE
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_WallIns_14
MeteorCave1_WallIns_13:
	getcaughtmon SPECIES_SLITHER_WING
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_WallIns_17
MeteorCave1_WallIns_16:
	getcaughtmon SPECIES_SANDY_SHOCKS
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_WallIns_20
MeteorCave1_WallIns_19:
	getcaughtmon SPECIES_ROARING_MOON
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_WallIns_23
MeteorCave1_WallIns_22:
	closemessage
	playse SE_BANG
	setmetatile 36, 2, 0x4DD, FALSE
	special DrawWholeMapView
	setflag FLAG_ALL_PASTMONS
	waitse
	release
	return

MeteorCave1_WallIns_2:
	msgbox MeteorCave1_WallIns_Text_0
	release
	end

MeteorCave1_WallIns_5:
	goto MeteorCave1_NothingHappens
	goto MeteorCave1_WallIns_4

MeteorCave1_WallIns_8:
	goto MeteorCave1_NothingHappens
	goto MeteorCave1_WallIns_7

MeteorCave1_WallIns_11:
	goto MeteorCave1_NothingHappens
	goto MeteorCave1_WallIns_10

MeteorCave1_WallIns_14:
	goto MeteorCave1_NothingHappens
	goto MeteorCave1_WallIns_13

MeteorCave1_WallIns_17:
	goto MeteorCave1_NothingHappens
	goto MeteorCave1_WallIns_16

MeteorCave1_WallIns_20:
	goto MeteorCave1_NothingHappens
	goto MeteorCave1_WallIns_19

MeteorCave1_WallIns_23:
	goto MeteorCave1_NothingHappens
	goto MeteorCave1_WallIns_22


MeteorCave1_NothingHappens::
	delay 30
	msgbox MeteorCave1_NothingHappens_Text_0
	release
	end


FlutterManeEnc::
	lock
	faceplayer
	legendaryencounter SPECIES_FLUTTER_MANE, 70, LOCALID_FLUTTERMANE, FLAG_HIDE_FLUTTERMANE
	release
	end


MeteorCave1_WallIns_Text_0:
	.string "The way is open.$"

MeteorCave1_WallIns_Text_1:
	.string "There's an inscription on the wall.\p"
	.string "GATHER ALL\n"
	.string "ANCIENTS$"

MeteorCave1_NothingHappens_Text_0:
	.string "Nothing seems to happen.$"
