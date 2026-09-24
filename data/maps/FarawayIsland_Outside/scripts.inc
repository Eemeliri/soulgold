FarawayIsland_Outside_MapScripts::
	.byte 0


FarawayIslandSailor::
	lock
	faceplayer
	msgbox FarawayIslandSailor_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq FarawayIslandSailor_2
	msgbox FarawayIslandSailor_Text_2
	closemessage
	hidefollower
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FARAWAY_SAILOR, MAP_FARAWAY_ISLAND_OUTSIDE
	setvar VAR_0x8004, LOCALID_SS_TIDAL_FARAWAY
	call Common_EventScript_FerryDepartIsland
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE, 8, 16
	waitstate
	release
	end

FarawayIslandSailor_2:
	msgbox FarawayIslandSailor_Text_1
	release
	end


FarawayIslandSailor_Text_0:
	.string "Do you want to head back to Olivine?$"

FarawayIslandSailor_Text_1:
	.string "Alright, I'll be waiting here.$"

FarawayIslandSailor_Text_2:
	.string "Aye, right!\n"
	.string "Then sail home we will!$"
