
EcruteakCity_Mart_MapScripts::
	.byte 0

EcruteakCity_Mart_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakMart_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox EcruteakMart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakMart_Text_SuperNerd:
	.string "My Eevee evolved into an Espeon.\p"
	.string "But my friend's Eevee turned into\n"
	.string "an Umbreon.\p"
	.string "I wonder why? We both were raising\n"
	.string "our Eevee in the same way…$"

EcruteakMart_Text_Granny:
	.string "If you use Revive, a Pokémon that's\n"
	.string "fainted will wake right up.$"

Ecruteak_Mart2::
	lock
	faceplayer
	message Ecruteak_Mart2_Text_0
	waitmessage
	pokemart Ecruteak2
	msgbox Ecruteak_Mart2_Text_1
	release
	end


	.align 2
Ecruteak2:
	.2byte ITEM_TM_SNARL
	.2byte ITEM_TM_TRAILBLAZE
	.2byte ITEM_TM_TRICK_ROOM
	.2byte ITEM_TM_WILL_O_WISP
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NONE

Ecruteak_Mart2_Text_0:
	.string "Welcome! How may I help you?$"

Ecruteak_Mart2_Text_1:
	.string "Come back soon!$"
