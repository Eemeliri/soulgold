LakeOfRageCresseliaDen_MapScripts::
	.byte 0


CresseliaEncounter::
	lock
	faceplayer
	bosslegendaryencounterwithmoves SPECIES_CRESSELIA, 60, LOCALID_CRESSELIA, FLAG_HIDE_CRESSELIA, 3, SPECIES_NONE, 110, MOVE_PSYCHIC, MOVE_MOONBLAST, MOVE_TOXIC, MOVE_CALM_MIND
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq CresseliaEncounter_2
CresseliaEncounter_1:
	release
	end

CresseliaEncounter_2:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 2
	goto_if_eq CresseliaEncounter_4
	goto CresseliaEncounter_1

CresseliaEncounter_4:
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 3
	goto CresseliaEncounter_1

