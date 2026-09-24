SnowtopMountain_MapScripts::
	.byte 0


SnowtopMountain_Sage::
	lock
	faceplayer
	msgbox SnowtopMountain_Sage_Text_0
	msgbox SnowtopMountain_Sage_Text_1
	release
	end


SnowtopMountain_Slowking::
	lock
	faceplayer
	playmoncry SPECIES_SLOWKING, CRY_MODE_NORMAL
	msgbox SnowtopMountain_Slowking_Text_0
	waitmoncry
	release
	end


SnowtopMountain_Sage_Text_0:
	.string "Only those who have proven themself to\n"
	.string "be more than just the region's \l"
	.string "champion may proceed past \l"
	.string "here.$"

SnowtopMountain_Sage_Text_1:
	.string "...You are not worthy yet.$"

SnowtopMountain_Slowking_Text_0:
	.string "Slooooow...!$"
