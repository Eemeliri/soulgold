Route50UnderwaterCave2_MapScripts::
	.byte 0


GroudonEncounter::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_GROUDON, 80, LOCALID_GROUDON, FLAG_HIDE_GROUDON, 4, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_GROUDON
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq GroudonEncounter_2
GroudonEncounter_1:
	release
	end

GroudonEncounter_2:
	goto_if_unset FLAG_GOT_REDORB, GroudonEncounter_5
GroudonEncounter_4:
	goto_if_unset FLAG_ONETIME_GROUDON, GroudonEncounter_7
	goto GroudonEncounter_1

GroudonEncounter_5:
	finditem ITEM_RED_ORB
	setflag FLAG_GOT_REDORB
	goto GroudonEncounter_4

GroudonEncounter_7:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 7
	goto_if_eq GroudonEncounter_10
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 8
	goto_if_eq GroudonEncounter_10
GroudonEncounter_9:
	setflag FLAG_ONETIME_GROUDON
	goto GroudonEncounter_1

GroudonEncounter_10:
	addvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 1
	goto GroudonEncounter_9

