MtSilver_1F_RegigigasRoom_MapScripts::
	.byte 0


MtSilver_Regigigas::
	lock
	checkspecies SPECIES_REGISTEEL
	compare VAR_RESULT, TRUE
	goto_if_eq MtSilver_Regigigas_2
	goto RegigigasSlumbers
MtSilver_Regigigas_1:
	release
	end

MtSilver_Regigigas_2:
	checkspecies SPECIES_REGIROCK
	compare VAR_RESULT, TRUE
	goto_if_eq MtSilver_Regigigas_5
	goto RegigigasSlumbers
	goto MtSilver_Regigigas_1

MtSilver_Regigigas_5:
	checkspecies SPECIES_REGICE
	compare VAR_RESULT, TRUE
	goto_if_eq MtSilver_Regigigas_8
	goto RegigigasSlumbers
	goto MtSilver_Regigigas_1

MtSilver_Regigigas_8:
	msgbox MtSilver_Regigigas_Text_0
	bosslegendaryencounter SPECIES_REGIGIGAS, 70, LOCALID_MTSILVER_REGIGIGAS, FLAG_HIDE_REGIGIGAS, 4, SPECIES_NONE, 110
	release
	end


RegigigasSlumbers::
	msgbox RegigigasSlumbers_Text_0
	release
	end


MtSilver_Regigigas_Text_0:
	.string "...!\p"
	.string "The statue suddenly started moving\n"
	.string "in reaction to your Pokémon!\p"
	.string "The statue attacked!$"

RegigigasSlumbers_Text_0:
	.string "A large, almost statue-like Pokémon\n"
	.string "seems to be resting here.\p"
	.string "...\p"
	.string "It does not react to your presence.$"
