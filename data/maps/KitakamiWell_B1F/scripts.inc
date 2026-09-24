KitakamiWell_B1F_MapScripts::
	.byte 0


KitakamiWellFezandipiti::
	lock
	faceplayer
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 1, 1, 1, 1, 0, 0
	legendaryencounter SPECIES_FEZANDIPITI, 55, LOCALID_FEZANDIPITI, FLAG_HIDE_FEZANDIPITI
	release
	end

