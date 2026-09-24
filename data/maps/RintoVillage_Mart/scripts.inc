RintoVillage_Mart_MapScripts::
	.byte 0


Rinto_Mart2::
	lock
	faceplayer
	message Rinto_Mart2_Text_0
	waitmessage
	pokemart Rinto2
	msgbox Rinto_Mart2_Text_1
	release
	end


	.align 2
Rinto2:
	.2byte ITEM_TM_BRICK_BREAK
	.2byte ITEM_TM_FACADE
	.2byte ITEM_TM_PLAY_ROUGH
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_NONE

RintoMart_Youngster::
	msgbox RintoMart_Youngster_Text_0, MSGBOX_NPC
	return


RintoMart_Beauty::
	msgbox RintoMart_Beauty_Text_0, MSGBOX_NPC
	return


Rinto_Mart2_Text_0:
	.string "Welcome! How may I help you?$"

Rinto_Mart2_Text_1:
	.string "Come back soon!$"

RintoMart_Youngster_Text_0:
	.string "Every Poké Mart in Johto stocks its\n"
	.string "own selection of TMs.\p"
	.string "Collecting them all gets expensive!$"

RintoMart_Beauty_Text_0:
	.string "I'm just hanging out here for the air\n"
	.string "conditioning.$"
