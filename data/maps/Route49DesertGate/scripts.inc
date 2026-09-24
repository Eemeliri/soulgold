Route49DesertGate_MapScripts::
	.byte 0


Route49GateJoy::
	lock
	faceplayer
	msgbox Route49GateJoy_Text_0
	playse SE_USE_ITEM
	special HealPlayerParty
	msgbox Route49GateJoy_Text_1
	release
	end


Route49GateJoy_Text_0:
	.string "Hi! Let me heal your Pokémon!$"

Route49GateJoy_Text_1:
	.string "Done! All good to go!$"
