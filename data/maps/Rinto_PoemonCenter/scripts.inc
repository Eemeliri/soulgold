Rinto_PoemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Rinto_PoemonCenter_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

Rinto_PoemonCenter_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_TEMP_1
	setrespawn HEAL_LOCATION_RINTO_VILLAGE_POKEMON_CENTER
	end


RintoPC_Gbakid1::
	msgbox RintoPC_Gbakid1_Text_0, MSGBOX_NPC
	return


RintoPC_Battlegirl::
	msgbox RintoPC_Battlegirl_Text_0, MSGBOX_NPC
	return


RintoPC_Hiker::
	msgbox RintoPC_Hiker_Text_0, MSGBOX_NPC
	return


RintoPC_Gbakid1_Text_0:
	.string "I wish I could fight against my friends\n"
	.string "around the globe.$"

RintoPC_Battlegirl_Text_0:
	.string "The sandstorms make travelling into\n"
	.string "this village difficult at times.$"

RintoPC_Hiker_Text_0:
	.string "I heard that an unusual looking pair of\n"
	.string "flying Pokémon have been spotted\l"
	.string "nearby.$"
