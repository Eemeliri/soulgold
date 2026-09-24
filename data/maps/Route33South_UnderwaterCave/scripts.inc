Route33South_UnderwaterCave_MapScripts::
	.byte 0


Route33Kyogre::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_KYOGRE, 80, LOCALID_KYOGRE, FLAG_HIDE_KYOGRE, 4, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_KYOGRE
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Route33Kyogre_2
Route33Kyogre_1:
	release
	end

Route33Kyogre_2:
	goto_if_unset FLAG_GOT_BLUEORB, Route33Kyogre_5
Route33Kyogre_4:
	goto_if_unset FLAG_ONETIME_KYOGRE, Route33Kyogre_7
	goto Route33Kyogre_1

Route33Kyogre_5:
	finditem ITEM_BLUE_ORB
	setflag FLAG_GOT_BLUEORB
	goto Route33Kyogre_4

Route33Kyogre_7:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 7
	goto_if_eq Route33Kyogre_10
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 8
	goto_if_eq Route33Kyogre_10
Route33Kyogre_9:
	setflag FLAG_ONETIME_KYOGRE
	goto Route33Kyogre_1

Route33Kyogre_10:
	addvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 1
	goto Route33Kyogre_9

