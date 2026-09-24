MeteorCave1_LegendaryRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD
	.byte 0

MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD:
	goto_if_set FLAG_RAGINGDOOR, MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_2
MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_1:
	goto_if_set FLAG_GOUGINGDOOR, MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_5
MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_4:
	goto_if_set FLAG_WALKINGDOOR, MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_7
	return

MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_2:
	setmetatileinrange 5, 35, 5, 29, 0x482, TRUE
	setmetatileinrange 6, 35, 6, 29, 0x498
	setmetatileinrange 7, 35, 7, 29, 0x486
	setmetatileinrange 8, 35, 8, 29, 0x49A
	setmetatileinrange 9, 34, 9, 29, 0x480, TRUE
	goto MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_1

MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_5:
	setmetatileinrange 17, 34, 17, 29, 0x482, TRUE
	setmetatileinrange 18, 35, 18, 29, 0x498
	setmetatileinrange 19, 35, 19, 29, 0x486
	setmetatileinrange 20, 35, 20, 29, 0x49A
	setmetatileinrange 21, 34, 21, 29, 0x480, TRUE
	goto MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_4

MeteorCave1_LegendaryRoom_MapScripts_MAP_SCRIPT_ON_LOAD_7:
	setmetatileinrange 29, 34, 29, 29, 0x482, TRUE
	setmetatileinrange 30, 35, 30, 29, 0x498
	setmetatileinrange 31, 35, 31, 29, 0x486
	setmetatileinrange 32, 35, 32, 29, 0x49A
	setmetatileinrange 33, 34, 33, 29, 0x480, TRUE
	return


MeteorCave1_LegendaryRoom_RagingBoltDoor::
	lock
	goto_if_set FLAG_RAGINGDOOR, MeteorCave1_LegendaryRoom_RagingBoltDoor_2
	msgbox MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_1
	checkspecies SPECIES_RAIKOU
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_LegendaryRoom_RagingBoltDoor_5
	closemessage
	playse SE_BANG
	setmetatileinrange 5, 35, 5, 29, 0x482, TRUE
	setmetatileinrange 6, 35, 6, 29, 0x498
	setmetatileinrange 7, 35, 7, 29, 0x486
	setmetatileinrange 8, 35, 8, 29, 0x49A
	setmetatileinrange 9, 34, 9, 29, 0x480, TRUE
	special DrawWholeMapView
	setflag FLAG_RAGINGDOOR
	waitse
	release
	end

MeteorCave1_LegendaryRoom_RagingBoltDoor_2:
	msgbox MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_0
	release
	end

MeteorCave1_LegendaryRoom_RagingBoltDoor_5:
	delay 30
	msgbox MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_2
	release
	end


MeteorCave1_LegendaryRoom_GougingFireDoor::
	lock
	goto_if_set FLAG_GOUGINGDOOR, MeteorCave1_LegendaryRoom_GougingFireDoor_2
	msgbox MeteorCave1_LegendaryRoom_GougingFireDoor_Text_0
	checkspecies SPECIES_ENTEI
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_LegendaryRoom_GougingFireDoor_5
	closemessage
	playse SE_BANG
	setmetatileinrange 17, 34, 17, 29, 0x482, TRUE
	setmetatileinrange 18, 35, 18, 29, 0x498
	setmetatileinrange 19, 35, 19, 29, 0x486
	setmetatileinrange 20, 35, 20, 29, 0x49A
	setmetatileinrange 21, 34, 21, 29, 0x480, TRUE
	special DrawWholeMapView
	setflag FLAG_GOUGINGDOOR
	waitse
	release
	end

MeteorCave1_LegendaryRoom_GougingFireDoor_2:
	msgbox MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_0
	release
	end

MeteorCave1_LegendaryRoom_GougingFireDoor_5:
	delay 30
	msgbox MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_2
	release
	end


MeteorCave1_LegendaryRoom_WalkingWakeDoor::
	lock
	goto_if_set FLAG_WALKINGDOOR, MeteorCave1_LegendaryRoom_WalkingWakeDoor_2
	msgbox MeteorCave1_LegendaryRoom_WalkingWakeDoor_Text_0
	checkspecies SPECIES_SUICUNE
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorCave1_LegendaryRoom_WalkingWakeDoor_5
	closemessage
	playse SE_BANG
	setmetatileinrange 29, 34, 29, 29, 0x482, TRUE
	setmetatileinrange 30, 35, 30, 29, 0x498
	setmetatileinrange 31, 35, 31, 29, 0x486
	setmetatileinrange 32, 35, 32, 29, 0x49A
	setmetatileinrange 33, 34, 33, 29, 0x480, TRUE
	special DrawWholeMapView
	setflag FLAG_WALKINGDOOR
	waitse
	release
	end

MeteorCave1_LegendaryRoom_WalkingWakeDoor_2:
	msgbox MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_0
	release
	end

MeteorCave1_LegendaryRoom_WalkingWakeDoor_5:
	delay 30
	msgbox MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_2
	release
	end


MeteorCave1_LegeRoom_RagingBolt::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_RAGING_BOLT, 75, LOCALID_RAGINGBOLT, FLAG_HIDE_RAGINGBOLT
	release
	end


MeteorCave1_LegeRoom_GougingFire::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_GOUGING_FIRE, 75, LOCALID_GOUGINGFIRE, FLAG_HIDE_GOUGINGFIRE
	release
	end


MeteorCave1_LegeRoom_WalkingWake::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_WALKING_WAKE, 75, LOCALID_WALKINGWAKE, FLAG_HIDE_WALKINGWAKE
	release
	end


MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_0:
	.string "The path is open.$"

MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_1:
	.string "There's an inscription on the wall.\p"
	.string "BRING THUNDER$"

MeteorCave1_LegendaryRoom_RagingBoltDoor_Text_2:
	.string "Nothing seems to happen.$"

MeteorCave1_LegendaryRoom_GougingFireDoor_Text_0:
	.string "There's an inscription on the wall.\p"
	.string "BRING VOLCANO$"

MeteorCave1_LegendaryRoom_WalkingWakeDoor_Text_0:
	.string "There's an inscription on the wall.\p"
	.string "BRING AURORA$"
