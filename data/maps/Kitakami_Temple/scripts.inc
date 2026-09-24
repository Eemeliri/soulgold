Kitakami_Temple_MapScripts::
	.byte 0


megaKickTrainer::
	lock
	msgbox megaKickTrainer_Text_0
	release
	end


megaPunchTrainer::
	lock
	msgbox megaPunchTrainer_Text_0
	release
	end


DojoTourist::
	lock
	faceplayer
	msgbox DojoTourist_Text_0
	release
	end


DojoTrainee::
	lock
	faceplayer
	msgbox DojoTrainee_Text_0
	release
	end


DojoTeacher::
	lock
	faceplayer
	msgbox DojoTeacher_Text_0
	release
	end


DojoTeacher2::
	msgbox DojoTeacher2_Text_0, MSGBOX_NPC
	return


megaKickTrainer_Text_0:
	.string "No no, you don't get it, Mega Punch is\n"
	.string "the superior move!$"

megaPunchTrainer_Text_0:
	.string "Fool! Everyone knows Mega Kick is the\n"
	.string "true path to power!$"

DojoTourist_Text_0:
	.string "The traditions here have been kept\n"
	.string "alive for countless lifetimes.\p"
	.string "It is quite impressive!$"

DojoTrainee_Text_0:
	.string "We offer paid courses for visitors. \p"
	.string "If you wish to grow stronger fast,\n"
	.string "please consider supporting our temple.$"

DojoTeacher_Text_0:
	.string "Behind me is the practice room. \p"
	.string "Take care not to disturb their\n"
	.string "training.$"

DojoTeacher2_Text_0:
	.string "These doors lead to the sleeping \n"
	.string "quarters.$"
