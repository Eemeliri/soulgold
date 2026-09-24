RailwayCave_MapScripts::
	.byte 0


RailwayCave1_Keira::
	trainerbattle_single TRAINER_KEIRA, RailwayCave1_Keira_Text_0, RailwayCave1_Keira_Text_1
	msgbox RailwayCave1_Keira_Text_2, MSGBOX_AUTOCLOSE
	return


RailwayCave1_Tammy::
	trainerbattle_single TRAINER_TAMMY, RailwayCave1_Tammy_Text_0, RailwayCave1_Tammy_Text_1
	msgbox RailwayCave1_Tammy_Text_2, MSGBOX_AUTOCLOSE
	return


RailwayCave1_Keira_Text_0:
	.string "Hey! It's dangerous here!$"

RailwayCave1_Keira_Text_1:
	.string "Just be careful, we're still working \n"
	.string "here...$"

RailwayCave1_Keira_Text_2:
	.string "We've been expanding the railway lines\n"
	.string "with the help of Pokémon found here.$"

RailwayCave1_Tammy_Text_0:
	.string "This place is filled with electricity!$"

RailwayCave1_Tammy_Text_1:
	.string "It's sending shivers down my spine!$"

RailwayCave1_Tammy_Text_2:
	.string "This place seems ideal for training\n"
	.string "Ground-type Pokémon.$"
