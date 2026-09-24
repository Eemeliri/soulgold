VajraPyramidFinalChamber_MapScripts::
	.byte 0


FinalChamber_HoopaPrison::
	lock
	goto_if_set FLAG_CAUGHT_HOOPA, FinalChamber_HoopaPrison_2
	msgbox FinalChamber_HoopaPrison_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FinalChamber_HoopaPrison_4
	msgbox FinalChamber_HoopaPrison_Text_3
	release
	end

FinalChamber_HoopaPrison_2:
	msgbox FinalChamber_HoopaPrison_Text_0
	release
	end

FinalChamber_HoopaPrison_4:
	playmoncry SPECIES_HOOPA, 0
	waitmoncry
	bosslegendaryencounter SPECIES_HOOPA, 80, LOCALID_NONE, FLAG_CAUGHT_HOOPA, 3, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_HOOPA
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq FinalChamber_HoopaPrison_7
	release
	end

FinalChamber_HoopaPrison_7:
	msgbox FinalChamber_HoopaPrison_Text_2
	finditem ITEM_PRISON_BOTTLE
	release
	end


FinalChamber_HoopaPrison_Text_0:
	.string "The contraption is empty.$"

FinalChamber_HoopaPrison_Text_1:
	.string "Something seems to be sealed inside\n"
	.string "this contraption. Release it?$"

FinalChamber_HoopaPrison_Text_2:
	.string "Something is at the bottom of the\n"
	.string "now empty contraption.$"

FinalChamber_HoopaPrison_Text_3:
	.string "Mom did always warn about touching\n"
	.string "strange objects found deep within\l"
	.string "ancient pyramids.$"
