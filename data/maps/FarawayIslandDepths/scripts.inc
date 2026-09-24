FarawayIslandDepths_MapScripts::
	.byte 0


MewEncounter::
	lock
	faceplayer
	legendaryencounter SPECIES_MEW, 55, LOCALID_MEW, FLAG_HIDE_MEW
	release
	end

