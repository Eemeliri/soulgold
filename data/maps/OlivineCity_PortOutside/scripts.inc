
.set LOCALID_OLIVINE_SABRINA, 3

OlivineCity_PortOutside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
	.byte 0

OlivineCity_PortOutside_EventScript_Sabrina::
    lock
    faceplayer
    msgbox OlivineCity_PortOutside_Text_Sabrina, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_OLIVINE_SABRINA
    removeobject LOCALID_OLIVINE_SABRINA
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_SABRINA
    release
    end

OlivineCity_PortOutside_Text_Sabrina:
    .string "Sabrina: Out of the blue,\n"
	.string "I get the urge to see the ocean.\p"
	.string "I'll see you at the Fighting\n"
	.string "Dojo.$"

OlivineCity_PortOutside_EventScript_Fisherman1::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_PortFisherman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_EventScript_Fisherman2::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_Fisherman2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_Text_PortFisherman1:
	.string "Fast Ship S.S.Aqua used to sail to\n"
	.string "Kanto on Mondays and Fridays. But\l"
	.string "now, it sails almost constantly!$"

OlivineCity_PortOutside_Text_Fisherman2:
	.string "Aw yeah, I'm fishin'.$"

OlivinePortFisher::
	msgbox OlivinePortFisher_Text_0, MSGBOX_NPC
	return


OlivinePortFisher_Text_0:
	.string "I heard the ship broke down,\n"
	.string "I wonder when it will sail again.$"
