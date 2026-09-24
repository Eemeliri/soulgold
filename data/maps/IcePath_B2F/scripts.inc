
IcePath_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SetBoulders
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

SetBoulders::
	goto_if_unset FLAG_ICEPATH_BOULDER3, SetBoulders_2
SetBoulders_1:
	goto_if_unset FLAG_ICEPATH_BOULDER4, SetBoulders_5
SetBoulders_4:
	goto_if_unset FLAG_ICEPATH_BOULDER2, SetBoulders_8
SetBoulders_7:
	goto_if_unset FLAG_ICEPATH_BOULDER1, SetBoulders_10
	return

SetBoulders_2:
	setflag FLAG_TEMP_3
	goto SetBoulders_1

SetBoulders_5:
	setflag FLAG_TEMP_4
	goto SetBoulders_4

SetBoulders_8:
	setflag FLAG_TEMP_2
	goto SetBoulders_7

SetBoulders_10:
	setflag FLAG_TEMP_1
	return

