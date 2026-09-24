VerityCavern_MapScripts::
	.byte 0


VerityCavern_Mesprit::
	lock
	faceplayer
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 1, 1, 1, 1, 0, 0
	legendaryencounter SPECIES_MESPRIT, 50, LOCALID_VERITY_MESPRIT, FLAG_HIDE_MESPRIT
	release
	end

