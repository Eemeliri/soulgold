SouthPassageEnd_MapScripts::
	.byte 0


SouthPassageSign::
	msgbox SouthPassageSign_Text_0, MSGBOX_SIGN
	return


SouthPassageAriana::
	lock
	faceplayer
	msgbox SouthPassageAriana_Text_0
	turnobject LOCALID_SP_ARIANA, DIR_NORTH
	msgbox SouthPassageAriana_Text_1
	faceplayer
	msgbox SouthPassageAriana_Text_2
	closemessage
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_SP_ARIANA
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setflag FLAG_SOUTHPASSAGE_ARIANA
	release
	end


SouthPassageSign_Text_0:
	.string "Research Facility, keep out!\p"
	.string "The text is faded and difficult\n"
	.string "to read.$"

SouthPassageAriana_Text_0:
	.string "Oh. It's you.\p"
	.string "Didn't expect you to wander all the\n"
	.string "way over here.$"

SouthPassageAriana_Text_1:
	.string "Archer sent me to check on something\n"
	.string "here.\p"
	.string "This place had been conducting illegal\n"
	.string "operations in the name of Team Rocket.\p"
	.string "Even Giovanni had not given an approval\n"
	.string "for them. \p"
	.string "Once he caught wind of it, he sent an\n"
	.string "order to cease the operations and fired\l"
	.string "all the scientists and grunts involved.$"

SouthPassageAriana_Text_2:
	.string "They tried to burn all evidence, but\n"
	.string "they were caught quickly.\p"
	.string "If you wish to explore around, then I'm \n"
	.string "not going to stop you, but don't expect\l"
	.string "to find much.\p"
	.string "I got what I need already, so I'll be\n"
	.string "heading back.$"
