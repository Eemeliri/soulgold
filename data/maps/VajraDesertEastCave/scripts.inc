VajraDesertEastCave_MapScripts::
	.byte 0


VajraDesertEastCave_TrainerDylan::
	trainerbattle_single TRAINER_VAJRA_EAST_DYLAN, VajraDesertEastCave_TrainerDylan_Text_0, VajraDesertEastCave_TrainerDylan_Text_1
	msgbox VajraDesertEastCave_TrainerDylan_Text_2, MSGBOX_AUTOCLOSE
	end


VajraDesertEastCave_TrainerDylan_Text_0:
	.string "Are you trying to find the hidden \n"
	.string "temple?$"

VajraDesertEastCave_TrainerDylan_Text_1:
	.string "Untold riches await!$"

VajraDesertEastCave_TrainerDylan_Text_2:
	.string "There's no way to access the oasis\n"
	.string "either side of the lower areas.\p"
	.string "Perhaps it might be possible\n"
	.string "from above?$"
