
Route28_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route28_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route28_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route28_EventScript_Sign::
	msgbox Route28_Text_Sign, MSGBOX_SIGN
	end

Route28_Text_Sign:
	.string "Route 28$"

Route28Guard::
	msgbox Route28Guard_Text_0, MSGBOX_NPC
	return


Route28Guard_Text_0:
	.string "The road beyond leads to the fierce\n"
	.string "heights of Mt Silver. Only those with\l"
	.string "explicit permission from the League\l"
	.string "are allowed to explore further.$"
