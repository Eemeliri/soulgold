VajraPyramidFloor2_MapScripts::
	.byte 0


VajraPyramid2_Urn1::
	lock
	goto_if_set FLAG_VAJRAPYRAMID2_URN1, VajraPyramid2_Urn1_2
	finditem ITEM_RELIC_GOLD
	setflag FLAG_VAJRAPYRAMID2_URN1
	release
	end

VajraPyramid2_Urn1_2:
	msgbox VajraPyramid2_Urn1_Text_0
	release
	end


VajraPyramid2_Urn2::
	lock
	goto_if_set FLAG_VAJRAPYRAMID2_URN2, VajraPyramid2_Urn2_2
	finditem ITEM_RELIC_GOLD
	setflag FLAG_VAJRAPYRAMID2_URN2
	release
	end

VajraPyramid2_Urn2_2:
	msgbox VajraPyramid2_Urn1_Text_0
	release
	end


PyramidDusknoir1::
	lockall
	playmoncry SPECIES_DUSKNOIR, 0
	waitmoncry
	warpteleport MAP_VAJRA_PYRAMID_FLOOR2, 30, 28
	waitstate
	releaseall
	end


VajraPyramid2_Urn1_Text_0:
	.string "The urn is empty.$"
