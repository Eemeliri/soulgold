VajraPyramidFloor1_MapScripts::
	.byte 0


VajraPyramid1_Urn::
	lock
	goto_if_set FLAG_VAJRAPYRAMID1_URN, VajraPyramid1_Urn_2
	finditem ITEM_RELIC_GOLD
	setflag FLAG_VAJRAPYRAMID1_URN
	release
	end

VajraPyramid1_Urn_2:
	msgbox VajraPyramid1_Urn_Text_0
	release
	end


VajraPyramid1_Urn_Text_0:
	.string "The urn is empty.$"
