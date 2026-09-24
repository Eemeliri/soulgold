
BlackthornCity_Mart_MapScripts::
	.byte 0

BlackthornMart_EventScript_CoolTrainerM::
	msgbox BlackthornMart_Text_CooltrainerM, MSGBOX_NPC
	end

BlackthornMart_EventScript_BlackBelt::
	msgbox BlackthornMart_Text_BlackBelt, MSGBOX_NPC
	end

BlackthornMart_Text_CooltrainerM:
	.string "You can't buy Max Revive, but it\n"
	.string "fully restores a fainted Pokémon.\p"
	.string "Beware--it won't restore PP, the\n"
	.string "Power Points needed for moves.$"

BlackthornMart_Text_BlackBelt:
	.string "Max Repel keeps weak Pokémon away\n"
	.string "from you.\p"
	.string "It's the longest lasting of the\n"
	.string "Repel sprays.$"

Blackthorn_Mart2::
	lock
	faceplayer
	message Blackthorn_Mart2_Text_0
	waitmessage
	pokemart Blackthorn2
	msgbox Blackthorn_Mart2_Text_1
	release
	end


	.align 2
Blackthorn2:
	.2byte ITEM_TM_ACROBATICS
	.2byte ITEM_TM_DRAGON_TAIL
	.2byte ITEM_TM_SKY_DROP
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_PREMIER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_RETRO_MAIL
	.2byte ITEM_NONE

Blackthorn_Mart2_Text_0:
	.string "Welcome! How may I help you?$"

Blackthorn_Mart2_Text_1:
	.string "Come back soon!$"
