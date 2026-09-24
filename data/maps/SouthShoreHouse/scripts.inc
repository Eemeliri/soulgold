SouthShoreHouse_MapScripts::
	.byte 0


SouthShoreHouseMan::
	lock
	faceplayer
	goto_if_set FLAG_SHOWN_MIRROR, SouthShoreHouseMan_2
	msgbox SouthShoreHouseMan_Text_1
	checkitem ITEM_BLACK_MIRROR
	compare VAR_RESULT, TRUE
	goto_if_eq SouthShoreHouseMan_5
	release
	end

SouthShoreHouseMan_2:
	msgbox SouthShoreHouseMan_Text_0
	release
	end

SouthShoreHouseMan_5:
	goto_if_unset FLAG_SHOWN_MIRROR, SouthShoreHouseMan_7
	msgbox SouthShoreHouseMan_Text_0
	release
	end

SouthShoreHouseMan_7:
	msgbox SouthShoreHouseMan_Text_2
	setflag FLAG_SHOWN_MIRROR
	release
	end


SouthShoreHouseSableye::
	lock
	faceplayer
	playmoncry SPECIES_SABLEYE, CRY_MODE_NORMAL
	msgbox SouthShoreHouseSableye_Text_0
	waitmoncry
	release
	end


SouthShoreHouseMan_Text_0:
	.string "You must follow the ravens with the\n"
	.string "mirror in hand to find the lair of the\l"
	.string "beast.$"

SouthShoreHouseMan_Text_1:
	.string "My grandparent always used to tell\n"
	.string "stories of a beast hiding in the\l"
	.string "depths of the forest.\p"
	.string "No normal person could ever hope to \n"
	.string "find it no matter how hard they looked,\l"
	.string "for it lived on a path that could only\l"
	.string "be revealed by a mirror that does not\l"
	.string "reflect its owner.\p"
	.string "I wonder if such object even exists.$"

SouthShoreHouseMan_Text_2:
	.string "Oh! That object you hold! That looks\n"
	.string "exactly like the item my grandpa\l"
	.string "described to me!\p"
	.string "To think that the stories were true.\p"
	.string "He told me that the path can be\n"
	.string "found by following the ravens. \p"
	.string "Best of luck finding the beast, trainer.$"

SouthShoreHouseSableye_Text_0:
	.string "Sableye: Sablblbllblb!$"
