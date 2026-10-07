GoldenrodCity_DepartmentStore_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore2_EventScript_Youngster::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Gent::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FGentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_2FYoungster:
    .string "Pokégear can store up to 25 phone\n"
    .string "numbers.\p"
    .string "It's hard to decide which numbers\n"
    .string "to keep.$"

GoldenrodDeptStore_Text_2FCooltrainerF:
    .string "I got my Deino at the Game Corner.\p"
    .string "Now it's my best partner.$"

GoldenrodDeptStore_Text_2FGentleman:
    .string "This Dept.Store makes me realize\n"
    .string "that Goldenrod is a big city.\p"
    .string "The selection here is unmatched\n"
    .string "anywhere else.$"

GoldenrodDeptStore_Text_2FDirectory:
    .string "Your Travel Companion\p"
    .string "2F Trainer's Market$"
