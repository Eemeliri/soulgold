LatiTempleLatios_MapScripts::
	.byte 0


LatiTemple_Latios::
	lock
	faceplayer
	bosslegendaryencounterwithmoves SPECIES_LATIOS, 80, LOCALID_LATIOS, FLAG_HIDE_LATIOS, 3, SPECIES_NONE, 110, MOVE_LUSTER_PURGE, MOVE_AURA_SPHERE, MOVE_SURF, MOVE_DRAGON_PULSE
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq LatiTemple_Latios_2
LatiTemple_Latios_1:
	release
	end

LatiTemple_Latios_2:
	setflag FLAG_CAUGHT_LATIOS
	goto LatiTemple_Latios_1

