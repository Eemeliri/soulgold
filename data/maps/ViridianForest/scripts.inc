.set LOCALID_VIRIDIAN_BUGSY, 16

ViridianForest_MapScripts::
	.byte 0

ViridianForest_EventScript_Bugsy::
	lock
	faceplayer
	msgbox ViridianForest_Text_Bugsy, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_VIRIDIAN_BUGSY
	removeobject LOCALID_VIRIDIAN_BUGSY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_BUGSY
	release
	end

ViridianForest_Text_Bugsy:
	.string "BUGSY: I came to KANTO to look for\n"
	.string "BUG-TYPE POKéMON, so I can become\l"
	.string "a stronger BUG-TYPE POKéMON\l"
	.string "TRAINER!\p"
    .string "If you're ready for another match,\n"
    .string "I'll be at the DOJO in SAFFRON!$"

