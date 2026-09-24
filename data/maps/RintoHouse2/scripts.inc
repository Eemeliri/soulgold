RintoHouse2_MapScripts::
	.byte 0


RintoHouse2_BottleCapManiac::
	lock
	faceplayer
	msgbox RintoHouse2_BottleCapManiac_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_2
RintoHouse2_BottleCapManiac_1:
	goto RintoHouse2_BottleCapManiac_ChooseMon
	return

RintoHouse2_BottleCapManiac_2:
	goto RintoHouse2_BottleCapManiac_Goodbye
	goto RintoHouse2_BottleCapManiac_1


RintoHouse2_BottleCapManiac_ChooseMon::
	msgbox RintoHouse2_BottleCapManiac_ChooseMon_Text_0
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge RintoHouse2_BottleCapManiac_ChooseMon_2
RintoHouse2_BottleCapManiac_ChooseMon_1:
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_5
RintoHouse2_BottleCapManiac_ChooseMon_4:
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	setvar VAR_0x8005, FALSE
	canhypertrain STAT_HP, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_8
RintoHouse2_BottleCapManiac_ChooseMon_7:
	canhypertrain STAT_ATK, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_11
RintoHouse2_BottleCapManiac_ChooseMon_10:
	canhypertrain STAT_DEF, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_14
RintoHouse2_BottleCapManiac_ChooseMon_13:
	canhypertrain STAT_SPEED, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_17
RintoHouse2_BottleCapManiac_ChooseMon_16:
	canhypertrain STAT_SPATK, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_20
RintoHouse2_BottleCapManiac_ChooseMon_19:
	canhypertrain STAT_SPDEF, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_23
RintoHouse2_BottleCapManiac_ChooseMon_22:
	compare VAR_0x8005, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseMon_26
RintoHouse2_BottleCapManiac_ChooseMon_25:
	goto RintoHouse2_BottleCapManiac_ChooseCap
	return

RintoHouse2_BottleCapManiac_ChooseMon_2:
	goto RintoHouse2_BottleCapManiac_Goodbye
	goto RintoHouse2_BottleCapManiac_ChooseMon_1

RintoHouse2_BottleCapManiac_ChooseMon_5:
	msgbox RintoHouse2_BottleCapManiac_ChooseMon_Text_1
	goto RintoHouse2_BottleCapManiac_ChooseMon
	goto RintoHouse2_BottleCapManiac_ChooseMon_4

RintoHouse2_BottleCapManiac_ChooseMon_8:
	setvar VAR_0x8005, TRUE
	goto RintoHouse2_BottleCapManiac_ChooseMon_7

RintoHouse2_BottleCapManiac_ChooseMon_11:
	setvar VAR_0x8005, TRUE
	goto RintoHouse2_BottleCapManiac_ChooseMon_10

RintoHouse2_BottleCapManiac_ChooseMon_14:
	setvar VAR_0x8005, TRUE
	goto RintoHouse2_BottleCapManiac_ChooseMon_13

RintoHouse2_BottleCapManiac_ChooseMon_17:
	setvar VAR_0x8005, TRUE
	goto RintoHouse2_BottleCapManiac_ChooseMon_16

RintoHouse2_BottleCapManiac_ChooseMon_20:
	setvar VAR_0x8005, TRUE
	goto RintoHouse2_BottleCapManiac_ChooseMon_19

RintoHouse2_BottleCapManiac_ChooseMon_23:
	setvar VAR_0x8005, TRUE
	goto RintoHouse2_BottleCapManiac_ChooseMon_22

RintoHouse2_BottleCapManiac_ChooseMon_26:
	msgbox RintoHouse2_BottleCapManiac_ChooseMon_Text_2
	goto RintoHouse2_BottleCapManiac_ChooseMon
	goto RintoHouse2_BottleCapManiac_ChooseMon_25


RintoHouse2_BottleCapManiac_ChooseCap::
	msgbox RintoHouse2_BottleCapManiac_ChooseCap_Text_0
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, RintoHouse2_BottleCapManiac_ChooseCap_Text_1, RintoHouse2_BottleCapManiac_ChooseCap_Text_2, RintoHouse2_BottleCapManiac_ChooseCap_Text_3, RintoHouse2_BottleCapManiac_ChooseCap_Text_4
	switch VAR_RESULT
	case 0, RintoHouse2_BottleCapManiac_ChooseCap_2
	case 1, RintoHouse2_BottleCapManiac_ChooseCap_3
	case 2, RintoHouse2_BottleCapManiac_ChooseCap_4
	goto RintoHouse2_BottleCapManiac_Goodbye
	return

RintoHouse2_BottleCapManiac_ChooseCap_2:
	checkitem ITEM_BOTTLE_CAP
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_7
RintoHouse2_BottleCapManiac_ChooseCap_6:
	goto RintoHouse2_BottleCapManiac_ChooseStat
	return

RintoHouse2_BottleCapManiac_ChooseCap_3:
	checkitem ITEM_GOLD_BOTTLE_CAP
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_10
RintoHouse2_BottleCapManiac_ChooseCap_9:
	msgbox RintoHouse2_BottleCapManiac_ChooseCap_Text_7, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_13
RintoHouse2_BottleCapManiac_ChooseCap_12:
	removeitem ITEM_GOLD_BOTTLE_CAP, 1
	canhypertrain STAT_HP, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_16
RintoHouse2_BottleCapManiac_ChooseCap_15:
	canhypertrain STAT_ATK, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_19
RintoHouse2_BottleCapManiac_ChooseCap_18:
	canhypertrain STAT_DEF, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_22
RintoHouse2_BottleCapManiac_ChooseCap_21:
	canhypertrain STAT_SPEED, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_25
RintoHouse2_BottleCapManiac_ChooseCap_24:
	canhypertrain STAT_SPATK, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_28
RintoHouse2_BottleCapManiac_ChooseCap_27:
	canhypertrain STAT_SPDEF, VAR_0x8004
	compare VAR_RESULT, TRUE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseCap_31
RintoHouse2_BottleCapManiac_ChooseCap_30:
	goto RintoHouse2_BottleCapManiac_TrainingDone
	return

RintoHouse2_BottleCapManiac_ChooseCap_4:
	goto RintoHouse2_BottleCapManiac_ChooseMon
	return

RintoHouse2_BottleCapManiac_ChooseCap_7:
	msgbox RintoHouse2_BottleCapManiac_ChooseCap_Text_5
	goto RintoHouse2_BottleCapManiac_ChooseCap
	goto RintoHouse2_BottleCapManiac_ChooseCap_6

RintoHouse2_BottleCapManiac_ChooseCap_10:
	msgbox RintoHouse2_BottleCapManiac_ChooseCap_Text_6
	goto RintoHouse2_BottleCapManiac_ChooseCap
	goto RintoHouse2_BottleCapManiac_ChooseCap_9

RintoHouse2_BottleCapManiac_ChooseCap_13:
	goto RintoHouse2_BottleCapManiac_ChooseCap
	goto RintoHouse2_BottleCapManiac_ChooseCap_12

RintoHouse2_BottleCapManiac_ChooseCap_16:
	hypertrain STAT_HP, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_ChooseCap_15

RintoHouse2_BottleCapManiac_ChooseCap_19:
	hypertrain STAT_ATK, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_ChooseCap_18

RintoHouse2_BottleCapManiac_ChooseCap_22:
	hypertrain STAT_DEF, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_ChooseCap_21

RintoHouse2_BottleCapManiac_ChooseCap_25:
	hypertrain STAT_SPEED, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_ChooseCap_24

RintoHouse2_BottleCapManiac_ChooseCap_28:
	hypertrain STAT_SPATK, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_ChooseCap_27

RintoHouse2_BottleCapManiac_ChooseCap_31:
	hypertrain STAT_SPDEF, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_ChooseCap_30


RintoHouse2_BottleCapManiac_ChooseStat::
	msgbox RintoHouse2_BottleCapManiac_ChooseStat_Text_0
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, RintoHouse2_BottleCapManiac_ChooseStat_Text_1, RintoHouse2_BottleCapManiac_ChooseStat_Text_2, RintoHouse2_BottleCapManiac_ChooseStat_Text_3, RintoHouse2_BottleCapManiac_ChooseStat_Text_4, RintoHouse2_BottleCapManiac_ChooseStat_Text_5, RintoHouse2_BottleCapManiac_ChooseStat_Text_6, RintoHouse2_BottleCapManiac_ChooseStat_Text_7
	switch VAR_RESULT
	case 0, RintoHouse2_BottleCapManiac_ChooseStat_2
	case 1, RintoHouse2_BottleCapManiac_ChooseStat_3
	case 2, RintoHouse2_BottleCapManiac_ChooseStat_4
	case 3, RintoHouse2_BottleCapManiac_ChooseStat_5
	case 4, RintoHouse2_BottleCapManiac_ChooseStat_6
	case 5, RintoHouse2_BottleCapManiac_ChooseStat_7
	goto RintoHouse2_BottleCapManiac_ChooseCap
	return

RintoHouse2_BottleCapManiac_ChooseStat_2:
	canhypertrain STAT_HP, VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseStat_10
RintoHouse2_BottleCapManiac_ChooseStat_9:
	goto RintoHouse2_BottleCapManiac_ConfirmHP
	return

RintoHouse2_BottleCapManiac_ChooseStat_3:
	canhypertrain STAT_ATK, VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseStat_13
RintoHouse2_BottleCapManiac_ChooseStat_12:
	goto RintoHouse2_BottleCapManiac_ConfirmAttack
	return

RintoHouse2_BottleCapManiac_ChooseStat_4:
	canhypertrain STAT_DEF, VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseStat_16
RintoHouse2_BottleCapManiac_ChooseStat_15:
	goto RintoHouse2_BottleCapManiac_ConfirmDefense
	return

RintoHouse2_BottleCapManiac_ChooseStat_5:
	canhypertrain STAT_SPATK, VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseStat_19
RintoHouse2_BottleCapManiac_ChooseStat_18:
	goto RintoHouse2_BottleCapManiac_ConfirmSpAttack
	return

RintoHouse2_BottleCapManiac_ChooseStat_6:
	canhypertrain STAT_SPDEF, VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseStat_22
RintoHouse2_BottleCapManiac_ChooseStat_21:
	goto RintoHouse2_BottleCapManiac_ConfirmSpDefense
	return

RintoHouse2_BottleCapManiac_ChooseStat_7:
	canhypertrain STAT_SPEED, VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq RintoHouse2_BottleCapManiac_ChooseStat_25
RintoHouse2_BottleCapManiac_ChooseStat_24:
	goto RintoHouse2_BottleCapManiac_ConfirmSpeed
	return

RintoHouse2_BottleCapManiac_ChooseStat_10:
	goto RintoHouse2_BottleCapManiac_StatAlreadyMaxed
	goto RintoHouse2_BottleCapManiac_ChooseStat_9

RintoHouse2_BottleCapManiac_ChooseStat_13:
	goto RintoHouse2_BottleCapManiac_StatAlreadyMaxed
	goto RintoHouse2_BottleCapManiac_ChooseStat_12

RintoHouse2_BottleCapManiac_ChooseStat_16:
	goto RintoHouse2_BottleCapManiac_StatAlreadyMaxed
	goto RintoHouse2_BottleCapManiac_ChooseStat_15

RintoHouse2_BottleCapManiac_ChooseStat_19:
	goto RintoHouse2_BottleCapManiac_StatAlreadyMaxed
	goto RintoHouse2_BottleCapManiac_ChooseStat_18

RintoHouse2_BottleCapManiac_ChooseStat_22:
	goto RintoHouse2_BottleCapManiac_StatAlreadyMaxed
	goto RintoHouse2_BottleCapManiac_ChooseStat_21

RintoHouse2_BottleCapManiac_ChooseStat_25:
	goto RintoHouse2_BottleCapManiac_StatAlreadyMaxed
	goto RintoHouse2_BottleCapManiac_ChooseStat_24


RintoHouse2_BottleCapManiac_StatAlreadyMaxed::
	msgbox RintoHouse2_BottleCapManiac_StatAlreadyMaxed_Text_0
	goto RintoHouse2_BottleCapManiac_ChooseStat
	return


RintoHouse2_BottleCapManiac_ConfirmHP::
	msgbox RintoHouse2_BottleCapManiac_ConfirmHP_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_ConfirmHP_2
RintoHouse2_BottleCapManiac_ConfirmHP_1:
	removeitem ITEM_BOTTLE_CAP, 1
	hypertrain STAT_HP, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_TrainingDone
	return

RintoHouse2_BottleCapManiac_ConfirmHP_2:
	goto RintoHouse2_BottleCapManiac_ChooseStat
	goto RintoHouse2_BottleCapManiac_ConfirmHP_1


RintoHouse2_BottleCapManiac_ConfirmAttack::
	msgbox RintoHouse2_BottleCapManiac_ConfirmAttack_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_ConfirmAttack_2
RintoHouse2_BottleCapManiac_ConfirmAttack_1:
	removeitem ITEM_BOTTLE_CAP, 1
	hypertrain STAT_ATK, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_TrainingDone
	return

RintoHouse2_BottleCapManiac_ConfirmAttack_2:
	goto RintoHouse2_BottleCapManiac_ChooseStat
	goto RintoHouse2_BottleCapManiac_ConfirmAttack_1


RintoHouse2_BottleCapManiac_ConfirmDefense::
	msgbox RintoHouse2_BottleCapManiac_ConfirmDefense_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_ConfirmDefense_2
RintoHouse2_BottleCapManiac_ConfirmDefense_1:
	removeitem ITEM_BOTTLE_CAP, 1
	hypertrain STAT_DEF, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_TrainingDone
	return

RintoHouse2_BottleCapManiac_ConfirmDefense_2:
	goto RintoHouse2_BottleCapManiac_ChooseStat
	goto RintoHouse2_BottleCapManiac_ConfirmDefense_1


RintoHouse2_BottleCapManiac_ConfirmSpAttack::
	msgbox RintoHouse2_BottleCapManiac_ConfirmSpAttack_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_ConfirmSpAttack_2
RintoHouse2_BottleCapManiac_ConfirmSpAttack_1:
	removeitem ITEM_BOTTLE_CAP, 1
	hypertrain STAT_SPATK, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_TrainingDone
	return

RintoHouse2_BottleCapManiac_ConfirmSpAttack_2:
	goto RintoHouse2_BottleCapManiac_ChooseStat
	goto RintoHouse2_BottleCapManiac_ConfirmSpAttack_1


RintoHouse2_BottleCapManiac_ConfirmSpDefense::
	msgbox RintoHouse2_BottleCapManiac_ConfirmSpDefense_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_ConfirmSpDefense_2
RintoHouse2_BottleCapManiac_ConfirmSpDefense_1:
	removeitem ITEM_BOTTLE_CAP, 1
	hypertrain STAT_SPDEF, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_TrainingDone
	return

RintoHouse2_BottleCapManiac_ConfirmSpDefense_2:
	goto RintoHouse2_BottleCapManiac_ChooseStat
	goto RintoHouse2_BottleCapManiac_ConfirmSpDefense_1


RintoHouse2_BottleCapManiac_ConfirmSpeed::
	msgbox RintoHouse2_BottleCapManiac_ConfirmSpeed_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RintoHouse2_BottleCapManiac_ConfirmSpeed_2
RintoHouse2_BottleCapManiac_ConfirmSpeed_1:
	removeitem ITEM_BOTTLE_CAP, 1
	hypertrain STAT_SPEED, VAR_0x8004
	goto RintoHouse2_BottleCapManiac_TrainingDone
	return

RintoHouse2_BottleCapManiac_ConfirmSpeed_2:
	goto RintoHouse2_BottleCapManiac_ChooseStat
	goto RintoHouse2_BottleCapManiac_ConfirmSpeed_1


RintoHouse2_BottleCapManiac_TrainingDone::
	msgbox RintoHouse2_BottleCapManiac_TrainingDone_Text_0
	closemessage
	fadescreen FADE_TO_BLACK
	delay 30
	playse SE_EXP_MAX
	waitse
	fadescreen FADE_FROM_BLACK
	msgbox RintoHouse2_BottleCapManiac_TrainingDone_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RintoHouse2_BottleCapManiac_TrainingDone_2
RintoHouse2_BottleCapManiac_TrainingDone_1:
	goto RintoHouse2_BottleCapManiac_Goodbye
	return

RintoHouse2_BottleCapManiac_TrainingDone_2:
	goto RintoHouse2_BottleCapManiac_ChooseMon
	goto RintoHouse2_BottleCapManiac_TrainingDone_1


RintoHouse2_BottleCapManiac_Goodbye::
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox RintoHouse2_BottleCapManiac_Goodbye_Text_0
	release
	end


RintoHouse2_BottleCapManiac_Text_0:
	.string "The name's Mr. Hyper!\p"
	.string "I can put your Pokémon through my\n"
	.string "amazing Hyper Training!\p"
	.string "A Bottle Cap trains one stat, while a\n"
	.string "Gold Bottle Cap trains every stat.\p"
	.string "Want to get your Pokémon hyped up?$"

RintoHouse2_BottleCapManiac_ChooseMon_Text_0:
	.string "Which one of your Pokémon wants some\n"
	.string "Hyper Training?$"

RintoHouse2_BottleCapManiac_ChooseMon_Text_1:
	.string "An Egg?! I admire the enthusiasm,\n"
	.string "but I can't train that just yet!$"

RintoHouse2_BottleCapManiac_ChooseMon_Text_2:
	.string "But {STR_VAR_1} is already so\n"
	.string "awesome that it doesn't need any\l"
	.string "training!$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_0:
	.string "So, will it be a Bottle Cap or a\n"
	.string "Gold Bottle Cap?$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_1:
	.string "Bottle Cap$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_2:
	.string "Gold Bottle Cap$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_3:
	.string "Choose another Pokémon$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_4:
	.string "Cancel$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_5:
	.string "Oh no! You don't have a\n"
	.string "Bottle Cap!$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_6:
	.string "Oh no! You don't have a\n"
	.string "Gold Bottle Cap!$"

RintoHouse2_BottleCapManiac_ChooseCap_Text_7:
	.string "Exchange a Gold Bottle Cap to\n"
	.string "train all of {STR_VAR_1}'s stats?$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_0:
	.string "Which one of {STR_VAR_1}'s stats\n"
	.string "should I train?$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_1:
	.string "HP$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_2:
	.string "Attack$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_3:
	.string "Defense$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_4:
	.string "Sp. Atk$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_5:
	.string "Sp. Def$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_6:
	.string "Speed$"

RintoHouse2_BottleCapManiac_ChooseStat_Text_7:
	.string "Go back$"

RintoHouse2_BottleCapManiac_StatAlreadyMaxed_Text_0:
	.string "That stat can't get any more hyper!\n"
	.string "It's already as high as it can get!$"

RintoHouse2_BottleCapManiac_ConfirmHP_Text_0:
	.string "Exchange a Bottle Cap to train\n"
	.string "{STR_VAR_1}'s HP?$"

RintoHouse2_BottleCapManiac_ConfirmAttack_Text_0:
	.string "Exchange a Bottle Cap to train\n"
	.string "{STR_VAR_1}'s Attack?$"

RintoHouse2_BottleCapManiac_ConfirmDefense_Text_0:
	.string "Exchange a Bottle Cap to train\n"
	.string "{STR_VAR_1}'s Defense?$"

RintoHouse2_BottleCapManiac_ConfirmSpAttack_Text_0:
	.string "Exchange a Bottle Cap to train\n"
	.string "{STR_VAR_1}'s Sp. Atk?$"

RintoHouse2_BottleCapManiac_ConfirmSpDefense_Text_0:
	.string "Exchange a Bottle Cap to train\n"
	.string "{STR_VAR_1}'s Sp. Def?$"

RintoHouse2_BottleCapManiac_ConfirmSpeed_Text_0:
	.string "Exchange a Bottle Cap to train\n"
	.string "{STR_VAR_1}'s Speed?$"

RintoHouse2_BottleCapManiac_TrainingDone_Text_0:
	.string "Then get hyped! It's time for some\n"
	.string "real Hyper Training!$"

RintoHouse2_BottleCapManiac_TrainingDone_Text_1:
	.string "{STR_VAR_1} grew stronger thanks\n"
	.string "to Hyper Training!\p"
	.string "Want to keep the hype rolling?$"

RintoHouse2_BottleCapManiac_Goodbye_Text_0:
	.string "Come back anytime! I'll always be\n"
	.string "hyped to see you!$"
