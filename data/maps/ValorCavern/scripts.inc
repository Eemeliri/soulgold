ValorCavern_MapScripts::
	.byte 0


ValorCavern_Azelf::
	lock
	faceplayer
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 1, 1, 1, 1, 0, 0
	legendaryencounter SPECIES_AZELF, 50, LOCALID_VALOR_AZELF, FLAG_HIDE_AZELF
	release
	end

