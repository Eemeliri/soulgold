SproutTower_Basement_MapScripts::
	.byte 0


MarshadowEncounter::
	lock
	faceplayer
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 1, 1, 1, 1, 0, 0
	legendaryencounter SPECIES_MARSHADOW, 50, LOCALID_MARSHADOW, FLAG_HIDE_MARSHADOW
	release
	end


BasementSage::
	msgbox BasementSage_Text_0, MSGBOX_NPC
	return


BasementSage_Text_0:
	.string "Guarding Marshadow has been one of our\n"
	.string "secret tasks for a very long time.$"
