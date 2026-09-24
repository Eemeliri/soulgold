FoggyShore2_MapScripts::
	.byte 0


NijoTrainer::
	trainerbattle_single TRAINER_NIJO, NijoTrainer_Text_0, NijoTrainer_Text_1
	msgbox NijoTrainer_Text_2, MSGBOX_AUTOCLOSE
	end


SaeTrainer::
	trainerbattle_single TRAINER_SAE, SaeTrainer_Text_0, SaeTrainer_Text_1
	msgbox SaeTrainer_Text_2, MSGBOX_AUTOCLOSE
	end


FoggyShoreSign::
	msgbox FoggyShoreSign_Text_0, MSGBOX_SIGN
	return


FoggyShoreBuizel::
	lock
	faceplayer
	playmoncry SPECIES_BUIZEL, CRY_MODE_NORMAL
	msgbox FoggyShoreBuizel_Text_0
	waitmoncry
	release
	end


NijoTrainer_Text_0:
	.string "What are you doing here so far off the\n"
	.string "beaten path?$"

NijoTrainer_Text_1:
	.string "You'll be fine.$"

NijoTrainer_Text_2:
	.string "Nearby path leads to a forest where\n"
	.string "many get lost. \p"
	.string "Be careful if you decide to \n"
	.string "venture there.$"

SaeTrainer_Text_0:
	.string "A quiet beach, the perfect getaway!$"

SaeTrainer_Text_1:
	.string "Peace, ruined!$"

SaeTrainer_Text_2:
	.string "Not that many wander down here due to\n"
	.string "the rumours of the spooky woods\l"
	.string "nearby.$"

FoggyShoreSign_Text_0:
	.string "{UP_ARROW} Lost Woods$"

FoggyShoreBuizel_Text_0:
	.string "Buizel: Buibuibuiiii!$"
