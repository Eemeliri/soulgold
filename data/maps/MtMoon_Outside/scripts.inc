MtMoon_Outside_MapScripts::
	.byte 0

MtMoon_Outside_EventScript_Sign::
	msgbox MtMoon_Outside_Text_DontLitterSign, MSGBOX_SIGN
	end

MtMoon_Outside_EventScript_Clefairy::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox MtMoon_Outside_Text_Clefairy, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MtMoon_Outside_Text_DontLitterSign:
	.string "MT.MOON SQUARE\n"
	.string "DON'T LITTER$"

MtMoon_Outside_Text_Clefairy:
    .string "CLEFAIRY: Pi pippippi!$"

