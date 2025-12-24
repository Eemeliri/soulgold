RockTunnel_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RockTunnel_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

RockTunnel_B1F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

