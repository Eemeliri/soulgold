Route50_MapScripts::
	.byte 0


Route50_TrainerRowan::
	trainerbattle_single TRAINER_ROUTE50_ROWAN, Route50_TrainerRowan_Text_0, Route50_TrainerRowan_Text_1
	msgbox Route50_TrainerRowan_Text_2, MSGBOX_AUTOCLOSE
	end


Route50_TrainerCaspian::
	trainerbattle_double TRAINER_ROUTE50_CASPIAN, Route50_TrainerCaspian_Text_0, Route50_TrainerCaspian_Text_1, Route50_TrainerCaspian_Text_2
	msgbox Route50_TrainerCaspian_Text_3, MSGBOX_AUTOCLOSE
	end


Route50_TrainerIgnis::
	trainerbattle_single TRAINER_ROUTE50_IGNIS, Route50_TrainerIgnis_Text_0, Route50_TrainerIgnis_Text_1
	msgbox Route50_TrainerIgnis_Text_2, MSGBOX_AUTOCLOSE
	end


Route50_Virizion::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_VIRIZION, 80, LOCALID_VIRIZION, FLAG_HIDE_VIRIZION, 2, SPECIES_NONE, 110
	release
	end


Route50_ObservingWoman::
	lock
	goto_if_unset FLAG_HIDE_VIRIZION, Route50_ObservingWoman_2
	msgbox Route50_ObservingWoman_Text_1
	release
	end

Route50_ObservingWoman_2:
	msgbox Route50_ObservingWoman_Text_0
	release
	end


Route50CafeSign::
	msgbox Route50CafeSign_Text_0, MSGBOX_SIGN
	return


Route50_TrainerRowan_Text_0:
	.string "Let's see if you still got energy left\n"
	.string "to face me!$"

Route50_TrainerRowan_Text_1:
	.string "You never lost your footing!$"

Route50_TrainerRowan_Text_2:
	.string "Lake of Rage ain't far away. The climate\n"
	.string "can change rapidly around here.$"

Route50_TrainerCaspian_Text_0:
	.string "I'm doing a tour of all the routes!$"

Route50_TrainerCaspian_Text_1:
	.string "You might be the strongest trainer so\n"
	.string "far.$"

Route50_TrainerCaspian_Text_2:
	.string "Bring two Pokémon ready to battle!$"

Route50_TrainerCaspian_Text_3:
	.string "Have you been making use of the \n"
	.string "weather? It can turn the tide of\l"
	.string "battle in a flash.$"

Route50_TrainerIgnis_Text_0:
	.string "This place is perfect for practicing\n"
	.string "firebreathing!$"

Route50_TrainerIgnis_Text_1:
	.string "No! My flames!$"

Route50_TrainerIgnis_Text_2:
	.string "Can't accidentally set anything on fire \n"
	.string "here.$"

Route50_ObservingWoman_Text_0:
	.string "What kind of Pokémon is that thing\n"
	.string "over there?$"

Route50_ObservingWoman_Text_1:
	.string "Oh you caught that thing! Nice going!$"

Route50CafeSign_Text_0:
	.string "Battle Cafe\n"
	.string "All challengers welcome!$"
