TohjoPass_MapScripts::
	.byte 0


TohjoPass_Floette::
	lock
	faceplayer
	playmoncry SPECIES_FLOETTE, CRY_MODE_NORMAL
	msgbox TohjoPass_Floette_Text_0
	waitmoncry
	release
	end


TohjoPass_Floette_Text_0:
	.string "Floette: Floweeeeey!$"
