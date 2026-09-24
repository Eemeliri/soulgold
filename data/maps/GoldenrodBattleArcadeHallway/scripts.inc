GoldenrodBattleArcadeHallway_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodBattleArcadeHallway_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

GoldenrodBattleArcadeHallway_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, FALSE, BattleArcade_Hallway_EventScript_EnterCorridor
	.2byte 0


BattleArcade_Hallway_EventScript_EnterCorridor::
	setvar VAR_TEMP_0, TRUE
	applymovement LOCALID_HALLWAY_ATTENDANT, BattleArcade_Hallway_EventScript_EnterCorridor_Movement_0
	applymovement OBJ_EVENT_ID_PLAYER, BattleArcade_Hallway_EventScript_EnterCorridor_Movement_1
	waitmovement LOCALID_HALLWAY_ATTENDANT
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_TEMP_0, FALSE
	warp MAP_GOLDENROD_BATTLE_ARCADE_BATTLE_ROOM, 7, 16
	waitstate
	end


BattleArcade_Hallway_EventScript_EnterCorridor_Movement_0:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

BattleArcade_Hallway_EventScript_EnterCorridor_Movement_1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end
