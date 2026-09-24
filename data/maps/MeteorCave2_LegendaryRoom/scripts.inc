MeteorCave2_LegendaryRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_LEAVESDOOR, MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_2
MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	goto_if_set FLAG_BOULDERDOOR, MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_5
MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_4:
	goto_if_set FLAG_CROWNDOOR, MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_7
	return

MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_2:
	setmetatileinrange 5, 35, 5, 29, 0x482, TRUE
	setmetatileinrange 6, 35, 6, 29, 0x498
	setmetatileinrange 7, 35, 7, 29, 0x486
	setmetatileinrange 8, 35, 8, 29, 0x49A
	setmetatileinrange 9, 34, 9, 29, 0x480, TRUE
	goto MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_1

MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_5:
	setmetatileinrange 17, 34, 17, 29, 0x482, TRUE
	setmetatileinrange 18, 35, 18, 29, 0x498
	setmetatileinrange 19, 35, 19, 29, 0x486
	setmetatileinrange 20, 35, 20, 29, 0x49A
	setmetatileinrange 21, 34, 21, 29, 0x480, TRUE
	goto MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_4

MeteorCave2_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_7:
	setmetatileinrange 29, 34, 29, 29, 0x482, TRUE
	setmetatileinrange 30, 35, 30, 29, 0x498
	setmetatileinrange 31, 35, 31, 29, 0x486
	setmetatileinrange 32, 35, 32, 29, 0x49A
	setmetatileinrange 33, 34, 33, 29, 0x480, TRUE
	return


MeteorCave1_LegendaryRoom_IronLeavesDoor::
	lock
	goto_if_set FLAG_LEAVESDOOR, MeteorCave1_LegendaryRoom_IronLeavesDoor_2
	msgbox MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_1
	checkspecies SPECIES_VIRIZION
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_LegendaryRoom_IronLeavesDoor_5
	closemessage
	playse SE_BANG
	setmetatileinrange 5, 35, 5, 29, 0x482, TRUE
	setmetatileinrange 6, 35, 6, 29, 0x498
	setmetatileinrange 7, 35, 7, 29, 0x486
	setmetatileinrange 8, 35, 8, 29, 0x49A
	setmetatileinrange 9, 34, 9, 29, 0x480, TRUE
	special DrawWholeMapView
	setflag FLAG_LEAVESDOOR
	waitse
	release
	return

MeteorCave1_LegendaryRoom_IronLeavesDoor_2:
	msgbox MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_0
	release
	end

MeteorCave1_LegendaryRoom_IronLeavesDoor_5:
	delay 30
	msgbox MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_2
	release
	end


MeteorCave1_LegendaryRoom_IronBoulderDoor::
	lock
	goto_if_set FLAG_BOULDERDOOR, MeteorCave1_LegendaryRoom_IronBoulderDoor_2
	msgbox MeteorCave1_LegendaryRoom_IronBoulderDoor_Text_0
	checkspecies SPECIES_TERRAKION
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_LegendaryRoom_IronBoulderDoor_5
	closemessage
	playse SE_BANG
	setmetatileinrange 17, 34, 17, 29, 0x482, TRUE
	setmetatileinrange 18, 35, 18, 29, 0x498
	setmetatileinrange 19, 35, 19, 29, 0x486
	setmetatileinrange 20, 35, 20, 29, 0x49A
	setmetatileinrange 21, 34, 21, 29, 0x480, TRUE
	special DrawWholeMapView
	setflag FLAG_BOULDERDOOR
	waitse
	release
	return

MeteorCave1_LegendaryRoom_IronBoulderDoor_2:
	msgbox MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_0
	release
	end

MeteorCave1_LegendaryRoom_IronBoulderDoor_5:
	delay 30
	msgbox MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_2
	release
	end


MeteorCave1_LegendaryRoom_IronCrownDoor::
	lock
	goto_if_set FLAG_CROWNDOOR, MeteorCave1_LegendaryRoom_IronCrownDoor_2
	msgbox MeteorCave1_LegendaryRoom_IronCrownDoor_Text_0
	checkspecies SPECIES_COBALION
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_LegendaryRoom_IronCrownDoor_5
	closemessage
	playse SE_BANG
	setmetatileinrange 29, 34, 29, 29, 0x482, TRUE
	setmetatileinrange 30, 35, 30, 29, 0x498
	setmetatileinrange 31, 35, 31, 29, 0x486
	setmetatileinrange 32, 35, 32, 29, 0x49A
	setmetatileinrange 33, 34, 33, 29, 0x480, TRUE
	special DrawWholeMapView
	setflag FLAG_CROWNDOOR
	waitse
	release
	return

MeteorCave1_LegendaryRoom_IronCrownDoor_2:
	msgbox MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_0
	release
	end

MeteorCave1_LegendaryRoom_IronCrownDoor_5:
	delay 30
	msgbox MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_2
	release
	end


MeteorCave2_LegeRoom_IronLeaves::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_IRON_LEAVES, 75, LOCALID_IRONLEAVES, FLAG_HIDE_IRONLEAVES
	release
	end


MeteorCave2_LegeRoom_IronBoulder::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_IRON_BOULDER, 75, LOCALID_IRON_BOULDER, FLAG_HIDE_IRONBOULDER
	release
	end


MeteorCave2_LegeRoom_IronCrown::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_IRON_CROWN, 75, LOCALID_IRONCROWN, FLAG_HIDE_IRONCROWN
	release
	end


MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_0:
	.string "The path is open.$"

MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_1:
	.string "There's an inscription on the wall.\p"
	.string "BRING LEAVES$"

MeteorCave1_LegendaryRoom_IronLeavesDoor_Text_2:
	.string "Nothing seems to happen.$"

MeteorCave1_LegendaryRoom_IronBoulderDoor_Text_0:
	.string "There's an inscription on the wall.\p"
	.string "BRING TERRA$"

MeteorCave1_LegendaryRoom_IronCrownDoor_Text_0:
	.string "There's an inscription on the wall.\p"
	.string "BRING WILL$"
