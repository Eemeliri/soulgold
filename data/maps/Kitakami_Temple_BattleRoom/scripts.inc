Kitakami_Temple_BattleRoom_MapScripts::
	.byte 0


BattleRoom_Audino::
	lock
	faceplayer
	playmoncry SPECIES_AUDINO, CRY_MODE_NORMAL
	msgbox BattleRoom_Audino_Text_0
	waitmoncry
	release
	end


BattleRoom_Machamp::
	lock
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	msgbox BattleRoom_Machamp_Text_0
	waitmoncry
	release
	end


BattleRoom_Mienshao::
	lock
	playmoncry SPECIES_MIENSHAO, CRY_MODE_NORMAL
	msgbox BattleRoom_Mienshao_Text_0
	waitmoncry
	release
	end


BattleRoom_BattleGirl::
	lock
	msgbox BattleRoom_BattleGirl_Text_0
	playmoncry SPECIES_MIENSHAO, CRY_MODE_NORMAL
	applymovement LOCALID_KITAKAMI_MIENSHAO, BattleRoom_BattleGirl_Movement_0
	waitmovement 0
	waitmoncry
	release
	end


BattleRoom_BlackBelt::
	lock
	msgbox BattleRoom_BlackBelt_Text_0
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	applymovement LOCALID_KITAKAMI_MACHAMP, BattleRoom_BlackBelt_Movement_0
	waitmovement 0
	waitmoncry
	release
	end


BattleRoom_MoneyTrainer::
	lock
	faceplayer
	goto_if_unset FLAG_TEMP_1, BattleRoom_MoneyTrainer_2
BattleRoom_MoneyTrainer_1:
	showmoneybox 0, 0
	msgbox BattleRoom_MoneyTrainer_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BattleRoom_MoneyTrainer_5
	hidemoneybox
	msgbox BattleRoom_MoneyTrainer_Text_6
	release
	end

BattleRoom_MoneyTrainer_2:
	msgbox BattleRoom_MoneyTrainer_Text_0
	setflag FLAG_TEMP_1
	goto BattleRoom_MoneyTrainer_1

BattleRoom_MoneyTrainer_4:
	release
	end

BattleRoom_MoneyTrainer_5:
	checkmoney 10000
	compare VAR_RESULT, FALSE
	goto_if_eq BattleRoom_MoneyTrainer_9
	removemoney 10000
	updatemoneybox 0
	playse SE_SHOP
	waitse
	hidemoneybox
	msgbox BattleRoom_MoneyTrainer_Text_3
	trainerbattle_no_intro TRAINER_DOJO_AUDINO, BattleRoom_MoneyTrainer_Text_4
	msgbox BattleRoom_MoneyTrainer_Text_5
	goto BattleRoom_MoneyTrainer_4

BattleRoom_MoneyTrainer_9:
	msgbox BattleRoom_MoneyTrainer_Text_2
	hidemoneybox
	release
	end


BattleRoom_BattleGirl_Movement_0:
	jump_in_place_left
	jump_in_place_left
	step_end

BattleRoom_BlackBelt_Movement_0:
	jump_in_place_right
	jump_in_place_right
	step_end

BattleRoom_Audino_Text_0:
	.string "Audino: Audiini!$"

BattleRoom_Machamp_Text_0:
	.string "Machamp: Mach!$"

BattleRoom_Mienshao_Text_0:
	.string "Mienshao: Mii!$"

BattleRoom_BattleGirl_Text_0:
	.string "Now Mienshao, use Hi Jump Kick!$"

BattleRoom_BlackBelt_Text_0:
	.string "Machamp, counter with Protect!$"

BattleRoom_MoneyTrainer_Text_0:
	.string "Greetings, we offer paid training\n"
	.string "services for visitors. \p"
	.string "The money will be used to support our \n"
	.string "temple and the village. Interested?$"

BattleRoom_MoneyTrainer_Text_1:
	.string "For a low price of ¥10,000, we will\n"
	.string "let you train with our Audinos and \l"
	.string "Blisseys.$"

BattleRoom_MoneyTrainer_Text_2:
	.string "Oh my, it seems you do not have the\n"
	.string "money right now. \p"
	.string "Please come back when you have some.$"

BattleRoom_MoneyTrainer_Text_3:
	.string "Thank you, let us begin.$"

BattleRoom_MoneyTrainer_Text_4:
	.string "Thank you for your support.$"

BattleRoom_MoneyTrainer_Text_5:
	.string "Come back if you wish to train again.$"

BattleRoom_MoneyTrainer_Text_6:
	.string "That's fine.$"
