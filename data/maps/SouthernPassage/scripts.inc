SouthernPassage_MapScripts::
	.byte 0


BlockSouthJohtoAccess::
	lock
	msgbox BlockSouthJohtoAccess_Text_0
	applymovement LOCALID_PLAYER, BlockSouthJohtoAccess_Movement_0
	release
	end


BlockSouthJohtoAccess_Movement_0:
	walk_up
	step_end

BlockSouthJohtoAccess_Text_0:
	.string "The tides ahead seem too strong to \n"
	.string "proceed right now. Better turn back\l"
	.string "for now.\p"
	.string "System note: The area ahead is not \n"
	.string "yet accessible in this version.$"
