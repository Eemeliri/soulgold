
Gate_Route40_TrainerHill_Courtyard_MapScripts::
	.byte 0

BattleTowerGuard::
	msgbox BattleTowerGuard_Text_0, MSGBOX_NPC
	return


BattleTowerTunnelFrustrationNPC::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_FRUSTRATION, BattleTowerTunnelFrustrationNPC_2
BattleTowerTunnelFrustrationNPC_1:
	msgbox BattleTowerTunnelFrustrationNPC_Text_1
	release
	end

BattleTowerTunnelFrustrationNPC_2:
	msgbox BattleTowerTunnelFrustrationNPC_Text_0
	giveitem ITEM_TM_FRUSTRATION
	setflag FLAG_GOT_FRUSTRATION
	goto BattleTowerTunnelFrustrationNPC_1


BattleTowerGuard_Text_0:
	.string "Ahead is the Battle Tower, where strong\n"
	.string "trainers gather.$"

BattleTowerTunnelFrustrationNPC_Text_0:
	.string "I lost on first round of the Battle\n"
	.string "Tower, I need to release my frustration\l"
	.string "by giving you this.$"

BattleTowerTunnelFrustrationNPC_Text_1:
	.string "Frustration deals more damage the less\n"
	.string "your Pokémon likes you. It can happen\l"
	.string "if you keep losing battles like me!$"
