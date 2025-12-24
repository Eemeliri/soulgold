IcePath_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcePath_B2F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

IcePath_B2F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

