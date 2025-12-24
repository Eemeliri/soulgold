MtSilver_1F_WaterfallRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_1F_WaterfallRoom_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtSilver_1F_WaterfallRoom_OnTransition: 
	callnative SetTimeBasedEncounters
	end

