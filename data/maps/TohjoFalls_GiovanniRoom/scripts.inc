
TohjoFalls_GiovanniRoom_MapScripts::
	.byte 0

TohjoPassGuard::
	lock
	faceplayer
	playmoncry SPECIES_RHYPERIOR, CRY_MODE_NORMAL
	msgbox TohjoPassGuard_Text_0
	waitmoncry
	msgbox TohjoPassGuard_Text_1
	release
	end


TohjoPassGuard_Text_0:
	.string "Rhyperior: Grr...$"

TohjoPassGuard_Text_1:
	.string "The Rhyperior is guarding the entrance\n"
	.string "with a menacing presence.\p"
	.string "You decide to come back another time.$"
