AbandonedRocketHideoutBackroom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto_if_set FLAG_IS_CHAMPION, AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_3
AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_2:
	setflag FLAG_HIDE_GENESECT
	return

AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	clearflag FLAG_HIDE_GENESECT
	return

AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_3:
	goto_if_unset FLAG_CAUGHT_GENESECT, AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	goto AbandonedRocketHideoutBackroom_MapScripts_MAP_SCRIPT_ON_TRANSITION_2


ARH_LaptopBackroom::
	msgbox ARH_LaptopBackroom_Text_0, MSGBOX_NPC
	return


ARH_NotesBackroom::
	msgbox ARH_NotesBackroom_Text_0, MSGBOX_SIGN
	return


ARH_Strangewall::
	msgbox ARH_Strangewall_Text_0, MSGBOX_SIGN
	return


GenesectEncounter::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_GENESECT, 70, LOCALID_GENESECT, FLAG_HIDE_GENESECT, 2, SPECIES_NONE, 110
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq GenesectEncounter_2
GenesectEncounter_1:
	release
	end

GenesectEncounter_2:
	setflag FLAG_CAUGHT_GENESECT
	goto GenesectEncounter_1


ARH_LaptopBackroom_Text_0:
	.string "While the laptop no longer has power,\n"
	.string "there's a small post-it note under it.\p"
	.string "SUBJECT SHADOW L????\p"
	.string "The rest of the text has been drenched\n"
	.string "by what seems to be coffee stains.$"

ARH_NotesBackroom_Text_0:
	.string "Log - Emotion Compression Studies\p"
	.string "By crystallizing energy found from a\n"
	.string "certain legendary Pokémon, we have\l"
	.string "managed to create containers for\l"
	.string "holding strong negative emotions. \p"
	.string "These can be used like magnets on\n"
	.string "creatures of high purity to invert\l"
	.string "their emotions to the opposite end.\p"
	.string "Further testing will be required to\n"
	.string "see the long term effects.$"

ARH_Strangewall_Text_0:
	.string "Something about this wall feels off,\n"
	.string "but there's no visible keyholes or\l"
	.string "card readers.$"
