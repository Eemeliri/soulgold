
VictoryRoadKanto_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoadKanto_B1F_OnTransition
	.byte 0

VictoryRoadKanto_B1F_OnTransition::
	call Common_EventScript_SetupRivalGfxId
    end



MtSilver_1F_MoltresRoom_EventScript_MoltresRan::
	release
	end

VictoryRoadKanto_B1F_EventScript_Moltres::
	lock
	faceplayer
	legendaryencounter SPECIES_MOLTRES, 60, LOCALID_VICTORYROAD_MOLTRES, FLAG_HIDE_MOLTRES
	release
	end


VictoryRoad_Rival::
	goto_if_set FLAG_SPOKEN_VICTORYROAD_RIVAL, VictoryRoad_Rival_1
	lock
	faceplayer
	createfieldmugshotrival
	msgbox VictoryRoad_Rival_Text_0
	setflag FLAG_SPOKEN_VICTORYROAD_RIVAL
	release
	end

VictoryRoad_Rival_1:
	goto VictoryRoad_Rival2
	return


VictoryRoad_Rival2::
	lock
	faceplayer
	createfieldmugshotrival
	msgbox VictoryRoad_Rival2_Text_0
	release
	end


VictoryRoad_Rival_Text_0:
	.string "Don't.$"

VictoryRoad_Rival2_Text_0:
	.string "I just need to train more.\p"
	.string "That's all there ever is to it.$"
