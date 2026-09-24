Kitakami_MapScripts::
	.byte 0


Kitakami_OldLady::
	msgbox Kitakami_OldLady_Text_0, MSGBOX_NPC
	return


Kitakami_Trigger::
	setflag FLAG_VISITED_KITAKAMI
	setvar VAR_KITAKAMI_STATE, 1
	end


Kitakami_OgerponTrigger::
	lock
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	turnobject LOCALID_KITAKAMI_OGERPON, DIR_SOUTH
	applymovement LOCALID_KITAKAMI_OGERPON, Common_Movement_ExclamationMark
	delay 30
	playmoncry SPECIES_OGERPON, CRY_MODE_NORMAL
	waitmoncry
	playse SE_LEDGE
	applymovement LOCALID_KITAKAMI_OGERPON, Kitakami_OgerponTrigger_Movement_0
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_KITAKAMI_OGERPON, Kitakami_OgerponTrigger_Movement_1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_KITAKAMI_OGERPON, Kitakami_OgerponTrigger_Movement_0
	waitmovement 0
	playmoncry SPECIES_OGERPON, CRY_MODE_NORMAL
	waitmoncry
	delay 20
	playse SE_LEDGE
	applymovement LOCALID_KITAKAMI_OGERPON, Kitakami_OgerponTrigger_Movement_2
	waitmovement 0
	waitse
	playse SE_LEDGE
	applymovement LOCALID_KITAKAMI_OGERPON, Kitakami_OgerponTrigger_Movement_2
	waitmovement 0
	waitse
	playse SE_LEDGE
	applymovement LOCALID_KITAKAMI_OGERPON, Kitakami_OgerponTrigger_Movement_2
	waitmovement 0
	waitse
	playse SE_LEDGE
	applymovement LOCALID_KITAKAMI_OGERPON, Kitakami_OgerponTrigger_Movement_2
	waitmovement 0
	waitse
	setflag FLAG_HIDE_KITAKAMI_OGERPON
	removeobject LOCALID_KITAKAMI_OGERPON
	setvar VAR_KITAKAMI_STATE, 2
	release
	end


Kitakami_Fatman::
	msgbox Kitakami_Fatman_Text_0, MSGBOX_NPC
	return


Kitakami_Battlegirl::
	msgbox Kitakami_Battlegirl_Text_0, MSGBOX_NPC
	return


Kitakami_Littlegirl::
	msgbox Kitakami_Littlegirl_Text_0, MSGBOX_NPC
	return


Kitakami_WestSign::
	msgbox Kitakami_WestSign_Text_0, MSGBOX_SIGN
	return


Kitakami_WellSign::
	msgbox Kitakami_WellSign_Text_0, MSGBOX_SIGN
	return


Kitakami_OgerponTrigger_Movement_0:
	jump_in_place_down
	delay_16
	step_end

Kitakami_OgerponTrigger_Movement_1:
	jump_in_place_up
	delay_16
	step_end

Kitakami_OgerponTrigger_Movement_2:
	jump_up
	step_end

Kitakami_OldLady_Text_0:
	.string "Oh a visitor? Where are you from?\n"
	.string "...\l"
	.string "Newbark Town? That's quite a journey\l"
	.string "to get here!$"

Kitakami_Fatman_Text_0:
	.string "There's no technology here!\n"
	.string "WHAT AM I SUPPOSED TO DO??$"

Kitakami_Battlegirl_Text_0:
	.string "I come here to train once a year. It's a\n"
	.string "nice middle ground between the busy\l"
	.string "city life and harshness of Mt. Silver.$"

Kitakami_Littlegirl_Text_0:
	.string "Mom used to say bad children are taken\n"
	.string "to the cave down there. \p"
	.string "It's a place where Fezandipiti \n"
	.string "roosts during the summer.$"

Kitakami_WestSign_Text_0:
	.string "Kitakami Town - Timeless traditions$"

Kitakami_WellSign_Text_0:
	.string "Old Well - Careful with the ladder!$"
