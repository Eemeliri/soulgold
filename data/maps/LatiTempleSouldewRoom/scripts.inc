LatiTempleSouldewRoom_MapScripts::
	.byte 0


SouldewPlatform::
	lock
	goto_if_set FLAG_OBTAINED_SOULDEW, SouldewPlatform_2
	finditem ITEM_SOUL_DEW
	setflag FLAG_OBTAINED_SOULDEW
	release
	end

SouldewPlatform_2:
	msgbox SouldewPlatform_Text_0
	release
	end


SouldewPlatform_Text_0:
	.string "The pedestal is empty.$"
