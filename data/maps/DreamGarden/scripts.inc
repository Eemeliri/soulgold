DreamGarden_MapScripts::
	.byte 0


ShayminEncounter::
	lock
	faceplayer
	legendaryencounter SPECIES_SHAYMIN, 50, LOCALID_SHAYMIN, FLAG_HIDE_SHAYMIN
	release
	end

