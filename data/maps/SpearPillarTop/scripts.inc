SpearPillarTop_MapScripts::
	.byte 0


exitPortalSP::
	lock
	warp MAP_RUINS_OF_ALPH_SECRET_ROOM, 9, 7
	waitstate
	release
	end


PortalDialga::
	lock
	faceplayer
	msgbox PortalDialga_Text_0
	msgbox PortalDialga_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PortalDialga_2
PortalDialga_1:
	release
	end

PortalDialga_2:
	bosslegendaryencounter SPECIES_DIALGA, 85, LOCALID_SPEAR_PILLAR_DIALGA_PORTAL, FLAG_HIDE_SPEAR_PILLAR_DIALGA_PORTAL, 4, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_DIALGA
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq PortalDialga_4
	goto PortalDialga_1

PortalDialga_4:
	goto_if_unset FLAG_GOT_ADAMANT_ORB, PortalDialga_6
	goto PortalDialga_1

PortalDialga_6:
	finditem ITEM_ADAMANT_ORB
	setflag FLAG_GOT_ADAMANT_ORB
	goto PortalDialga_1


PortalPalkia::
	lock
	faceplayer
	msgbox PortalPalkia_Text_0
	msgbox PortalDialga_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PortalPalkia_2
PortalPalkia_1:
	release
	end

PortalPalkia_2:
	bosslegendaryencounter SPECIES_PALKIA, 85, LOCALID_SPEAR_PILLAR_PALKIA_PORTAL, FLAG_HIDE_SPEAR_PILLAR_PALKIA_PORTAL, 4, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_PALKIA
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq PortalPalkia_4
	goto PortalPalkia_1

PortalPalkia_4:
	goto_if_unset FLAG_GOT_LUSTROUS_ORB, PortalPalkia_6
	goto PortalPalkia_1

PortalPalkia_6:
	finditem ITEM_LUSTROUS_ORB
	setflag FLAG_GOT_LUSTROUS_ORB
	goto PortalPalkia_1


PortalGiratina::
	lock
	faceplayer
	msgbox PortalGiratina_Text_0
	msgbox PortalDialga_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PortalGiratina_2
PortalGiratina_1:
	release
	end

PortalGiratina_2:
	bosslegendaryencounter SPECIES_GIRATINA, 85, LOCALID_SPEAR_PILLAR_GIRATINA_PORTAL, FLAG_HIDE_SPEAR_PILLAR_GIRATINA_PORTAL, 4, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_GIRATINA
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq PortalGiratina_4
	goto PortalGiratina_1

PortalGiratina_4:
	goto_if_unset FLAG_GOT_GRISEOUS_ORB, PortalGiratina_6
	goto PortalGiratina_1

PortalGiratina_6:
	finditem ITEM_GRISEOUS_ORB
	setflag FLAG_GOT_GRISEOUS_ORB
	goto PortalGiratina_1


TimeGearPrimal::
	lock
	faceplayer
	msgbox TimeGearPrimal_Text_0
	checkspecies SPECIES_GROVYLE
	compare VAR_RESULT, FALSE
	goto_if_eq TimeGearPrimal_2
TimeGearPrimal_1:
	checkspecies SPECIES_DUSKNOIR
	compare VAR_RESULT, FALSE
	goto_if_eq TimeGearPrimal_5
TimeGearPrimal_4:
	checkspecies SPECIES_CELEBI
	compare VAR_RESULT, FALSE
	goto_if_eq TimeGearPrimal_8
TimeGearPrimal_7:
	msgbox TimeGearPrimal_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq TimeGearPrimal_11
TimeGearPrimal_10:
	release
	end

TimeGearPrimal_2:
	goto TimeGearDoesNotReact
	goto TimeGearPrimal_1

TimeGearPrimal_5:
	goto TimeGearDoesNotReact
	goto TimeGearPrimal_4

TimeGearPrimal_8:
	goto TimeGearDoesNotReact
	goto TimeGearPrimal_7

TimeGearPrimal_11:
	bosslegendaryencounterwithmoves SPECIES_DIALGA_PRIMAL, 85, LOCALID_SPEAR_PILLAR_TIME_GEAR, FLAG_HIDE_SPEAR_PILLAR_TIME_GEAR, 4, SPECIES_NONE, 110, MOVE_ROAR_OF_TIME, MOVE_FLASH_CANNON, MOVE_EARTH_POWER, MOVE_THUNDER
	goto TimeGearPrimal_10


TimeGearDoesNotReact::
	msgbox TimeGearDoesNotReact_Text_0
	release
	end


PortalDialga_Text_0:
	.string "You gaze deep into the portal.\p"
	.string "It shows you the sea of flowing time.$"

PortalDialga_Text_1:
	.string "Touch the portal?$"

PortalPalkia_Text_0:
	.string "You gaze deep into the portal.\p"
	.string "It shows you a vast and endless space.$"

PortalGiratina_Text_0:
	.string "You gaze deep into the portal.\p"
	.string "It shows you a bottomless abyss.$"

TimeGearPrimal_Text_0:
	.string "A strange gear lies on the ground.$"

TimeGearPrimal_Text_1:
	.string "The Time Gear suddenly started glowing!\p"
	.string "Touch it?$"

TimeGearDoesNotReact_Text_0:
	.string "It does not react to your presence.$"
