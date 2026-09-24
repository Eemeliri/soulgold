
OlivineCity_Mart_MapScripts::
	.byte 0

OlivineCity_EventScript_Trainer1::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Lass::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartLass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_MartCooltrainerF:
	.string "Do your Pokémon already know\n"
	.string "the move for carrying people\l"
	.string "across water?$"

OlivineCity_Text_MartLass:
	.string "My Butterfree came from my\n"
	.string "boyfriend overseas.\p"
	.string "It carried some Mail from him.\p"
	.string "Want to know what it says?\p"
	.string "Let's see... Nope! It's a\n"
	.string "secret!$"

Olivine_Mart2::
	lock
	faceplayer
	message Olivine_Mart2_Text_0
	waitmessage
	pokemart Olivine2
	msgbox Olivine_Mart2_Text_1
	release
	end


	.align 2
Olivine2:
	.2byte ITEM_TM_DRAINING_KISS
	.2byte ITEM_TM_BRUTAL_SWING
	.2byte ITEM_TM_CHARGE_BEAM
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_NONE

Olivine_Mart2_Text_0:
	.string "Welcome! How may I help you?$"

Olivine_Mart2_Text_1:
	.string "Come back soon!$"
