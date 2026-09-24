GoldenrodApartmentBasement_MapScripts::
	.byte 0


RotomMachine_Wash::
	lock
	special ChoosePartyMon
	waitstate
	lock
	setvar VAR_0x8000, MOVE_HYDRO_PUMP
	special ChangeRotomForm
	compare VAR_RESULT, TRUE
	goto_if_eq RotomMachine_Wash_2
RotomMachine_Wash_1:
	release
	end

RotomMachine_Wash_2:
	msgbox RotomMachine_Wash_Text_0
	goto RotomMachine_Wash_1


RotomMachine_Fan::
	lock
	special ChoosePartyMon
	waitstate
	lock
	setvar VAR_0x8000, MOVE_AIR_SLASH
	special ChangeRotomForm
	compare VAR_RESULT, TRUE
	goto_if_eq RotomMachine_Fan_2
RotomMachine_Fan_1:
	release
	end

RotomMachine_Fan_2:
	msgbox RotomMachine_Wash_Text_0
	goto RotomMachine_Fan_1


RotomMachine_Fridge::
	lock
	special ChoosePartyMon
	waitstate
	lock
	setvar VAR_0x8000, MOVE_BLIZZARD
	special ChangeRotomForm
	compare VAR_RESULT, TRUE
	goto_if_eq RotomMachine_Fridge_2
RotomMachine_Fridge_1:
	release
	end

RotomMachine_Fridge_2:
	msgbox RotomMachine_Wash_Text_0
	goto RotomMachine_Fridge_1


RotomMachine_Lawnmower::
	lock
	special ChoosePartyMon
	waitstate
	lock
	setvar VAR_0x8000, MOVE_LEAF_STORM
	special ChangeRotomForm
	compare VAR_RESULT, TRUE
	goto_if_eq RotomMachine_Lawnmower_2
RotomMachine_Lawnmower_1:
	release
	end

RotomMachine_Lawnmower_2:
	msgbox RotomMachine_Wash_Text_0
	goto RotomMachine_Lawnmower_1


RotomMachine_Oven::
	lock
	special ChoosePartyMon
	waitstate
	lock
	setvar VAR_0x8000, MOVE_OVERHEAT
	special ChangeRotomForm
	compare VAR_RESULT, TRUE
	goto_if_eq RotomMachine_Oven_2
RotomMachine_Oven_1:
	release
	end

RotomMachine_Oven_2:
	msgbox RotomMachine_Wash_Text_0
	goto RotomMachine_Oven_1


RotomMachine_Wash_Text_0:
	.string "Rotom's form was changed!$"
