AcuityCavern_MapScripts::
	.byte 0


AcuityCavern_Uxie::
	lock
	faceplayer
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 1, 1, 1, 1, 0, 0
	legendaryencounter SPECIES_UXIE, 50, LOCALID_ACUITY_UXIE, FLAG_HIDE_UXIE
	release
	end

