VajraDesertWest_2_MapScripts::
	.byte 0


VajraCrossroad_Girl::
	msgbox VajraCrossroad_Girl_Text_0, MSGBOX_NPC
	return


VajraCrossroad_Sign::
	msgbox VajraCrossroad_Sign_Text_0, MSGBOX_SIGN
	return


VajraCrossroad_SignBP::
	msgbox VajraCrossroad_SignBP_Text_0, MSGBOX_SIGN
	return


VajraCrossroad_Girl_Text_0:
	.string "Many strong trainers around the world \n"
	.string "come to visit our village to partake\l"
	.string "in the Battle Pyramid challenge. \p"
	.string "It was relocated here from Hoenn region\n"
	.string "some time ago.$"

VajraCrossroad_Sign_Text_0:
	.string "{LEFT_ARROW} Old Pyramid\n"
	.string "{RIGHT_ARROW} Rinto Village$"

VajraCrossroad_SignBP_Text_0:
	.string "Battle Pyramid, brave trainers welcome!$"
