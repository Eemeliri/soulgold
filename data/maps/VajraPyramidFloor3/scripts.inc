VajraPyramidFloor3_MapScripts::
	.byte 0


PyramidDusknoir2::
	lockall
	playmoncry SPECIES_DUSKNOIR, 0
	waitmoncry
	delay 10
	warpteleport MAP_VAJRA_PYRAMID_FLOOR3, 1, 4
	waitstate
	releaseall
	end

