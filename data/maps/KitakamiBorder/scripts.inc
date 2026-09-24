KitakamiBorder_MapScripts::
	.byte 0


KitakamiBorder_OldLady::
	msgbox KitakamiBorder_OldLady_Text_0, MSGBOX_NPC
	return


KitakamiBorder_HikerMoulder::
	trainerbattle_single TRAINER_MOULDER, KitakamiBorder_HikerMoulder_Text_0, KitakamiBorder_HikerMoulder_Text_1
	msgbox KitakamiBorder_HikerMoulder_Text_2, MSGBOX_AUTOCLOSE
	return


KitakamiBorder_OldLady_Text_0:
	.string "I often come here to watch the valley\n"
	.string "between here and Mt. Silver. \p"
	.string "It soothes my mind.$"

KitakamiBorder_HikerMoulder_Text_0:
	.string "Are you heading to visit Kitakami?$"

KitakamiBorder_HikerMoulder_Text_1:
	.string "Enjoy the sights!$"

KitakamiBorder_HikerMoulder_Text_2:
	.string "I visit this place almost every month!$"
