Kitakami_Temple_TrainingRoom_MapScripts::
	.byte 0


dojoFexpert::
	lock
	faceplayer
	msgbox dojoFexpert_Text_0
	goto_if_unset FLAG_RECEIVED_FOCUS_SASH, dojoFexpert_2
dojoFexpert_1:
	release
	end

dojoFexpert_2:
	msgbox dojoFexpert_Text_1
	giveitem ITEM_FOCUS_SASH
	setflag FLAG_RECEIVED_FOCUS_SASH
	goto dojoFexpert_1


dojoTrainer::
	lock
	msgbox dojoTrainer_Text_0
	closemessage
	release
	end


dojoFexpert_Text_0:
	.string "Training yourself mentally and \n"
	.string "physically is as important as \l"
	.string "training your Pokémon. \p"
	.string "Tough challenges cannot be faced \n"
	.string "with weak body and mind.$"

dojoFexpert_Text_1:
	.string "Perhaps this will help you focus on your\n"
	.string "training.$"

dojoTrainer_Text_0:
	.string "The trainee is meditating, \n"
	.string "it would be rude to disturb them.$"
