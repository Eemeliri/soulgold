GoldenrodBattleAracdeLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodBattleAracdeLobby_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, GoldenrodBattleAracdeLobby_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	.byte 0

GoldenrodBattleAracdeLobby_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleArcade_Registration_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleArcade_Registration_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleArcade_Registration_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleArcade_Registration_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleArcade_Registration_EventScript_LostChallenge
	.2byte 0

GoldenrodBattleAracdeLobby_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_TEMP_1, 0, BattleArcade_Lobby_EventScript_PlayerFaceNorth
	.2byte 0


GoldenrodArcadeLobby_Rocker::
	lock
	msgbox GoldenrodArcadeLobby_Rocker_Text_0
	release
	end


GoldenrodArcadeLobby_Oldman::
	lock
	msgbox GoldenrodArcadeLobby_Oldman_Text_0
	release
	end


GoldenrodArcadeLobby_Battlegirl::
	lock
	msgbox GoldenrodArcadeLobby_Battlegirl_Text_0
	release
	end


GoldenrodArcadeLobby_Shop::
	lock
	msgbox GoldenrodArcadeLobby_Shop_Text_0
	waitmessage
	pokemart GoldenrodArcade_Shop
	msgbox GoldenrodArcadeLobby_Shop_Text_1
	release
	end


	.align 2
GoldenrodArcade_Shop:
	.2byte ITEM_MASTER_BALL
	.2byte ITEM_SHIN_GENOME
	.2byte ITEM_SCROLL_OF_WATERS
	.2byte ITEM_SCROLL_OF_DARKNESS
	.2byte ITEM_HP_UP_EX
	.2byte ITEM_PROTEIN_EX
	.2byte ITEM_IRON_EX
	.2byte ITEM_CALCIUM_EX
	.2byte ITEM_ZINC_EX
	.2byte ITEM_CARBOS_EX
	.2byte ITEM_PP_MAX
	.2byte ITEM_NONE

GoldenrodArcade_Queue2::
	msgbox GoldenrodArcade_Queue2_Text_0, MSGBOX_NPC
	return


GoldenrodArcade_Queue3::
	msgbox GoldenrodArcade_Queue3_Text_0, MSGBOX_NPC
	return


GoldenrodArcade_Queue4::
	msgbox GoldenrodArcade_Queue4_Text_0, MSGBOX_NPC
	return


ArcadeLobby_GameMachine::
	msgbox ArcadeLobby_GameMachine_Text_0, MSGBOX_NPC
	return


MagernaKeyBurglar::
	lock
	faceplayer
	goto_if_set FLAG_GOT_MAGERNA_KEY, MagernaKeyBurglar_2
	goto_if_unset FLAG_GOT_MAGERNA_KEY_INTRODONE, MagernaKeyBurglar_5
MagernaKeyBurglar_4:
	msgbox MagernaKeyBurglar_Text_3
	specialvar VAR_RESULT, GetRocketArcadeWins
	compare VAR_RESULT, 25
	goto_if_ge MagernaKeyBurglar_8
	release
	end

MagernaKeyBurglar_2:
	msgbox MagernaKeyBurglar_Text_0
	msgbox MagernaKeyBurglar_Text_1
	release
	end

MagernaKeyBurglar_5:
	msgbox MagernaKeyBurglar_Text_2
	setflag FLAG_GOT_MAGERNA_KEY_INTRODONE
	goto MagernaKeyBurglar_4

MagernaKeyBurglar_8:
	msgbox MagernaKeyBurglar_Text_4
	playfanfare MUS_HG_OBTAIN_KEY_ITEM
	msgbox MagernaKeyBurglar_Text_5
	waitfanfare
	msgbox MagernaKeyBurglar_Text_6
	msgbox MagernaKeyBurglar_Text_7
	setflag FLAG_GOT_MAGERNA_KEY
	release
	end


GoldenrodArcadeLobby_Rocker_Text_0:
	.string "These machines have to be rigged!\n"
	.string "There's no way I just lost it all!$"

GoldenrodArcadeLobby_Oldman_Text_0:
	.string "Hah! Another win! I'll get to buy my\n"
	.string "daughter something nice this weekend!$"

GoldenrodArcadeLobby_Battlegirl_Text_0:
	.string "RAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH!\n"
	.string "JUST ONE MORE WIN AND I'LL STOP!$"

GoldenrodArcadeLobby_Shop_Text_0:
	.string "Welcome.$"

GoldenrodArcadeLobby_Shop_Text_1:
	.string "Pleasure doing business.$"

GoldenrodArcade_Queue2_Text_0:
	.string "I can't wait to see the next battle\n"
	.string "from the front-row seats!$"

GoldenrodArcade_Queue3_Text_0:
	.string "Hey! No shoving! I was here first!$"

GoldenrodArcade_Queue4_Text_0:
	.string "Is this the Goldenrod Casino? I think\n"
	.string "I'm a little lost...$"

ArcadeLobby_GameMachine_Text_0:
	.string "Bright flashes and vivid pictures are\n"
	.string "flashing across the screen. Better not\l"
	.string "try...$"

MagernaKeyBurglar_Text_0:
	.string "You can use the key to access the top \n"
	.string "floor of Goldenrod apartment building.$"

MagernaKeyBurglar_Text_1:
	.string "As for me, I'm rich beyond belief \n"
	.string "now! Good bye ice soup, hello gravlax!$"

MagernaKeyBurglar_Text_2:
	.string "Hey there champ, may I interest\n"
	.string "you in some special wares that\l"
	.string "may or may not have been legally\l"
	.string "acquired?\p"
	.string "For example, this key to the top\n"
	.string "floor apartment residence in the\l"
	.string "Goldenrod apartment building!\p"
	.string "Who knows what kind of riches are\n"
	.string "available for the taking up there?\p"
	.string "I just need you to do me a tiny\n"
	.string "favour and it could be yours for\l"
	.string "the taking.$"

MagernaKeyBurglar_Text_3:
	.string "I need you to win at least 25 battles\n"
	.string "in the Rocket Arcade battles, my\l"
	.string "bets are riding on you winning\l"
	.string "me a fortune!$"

MagernaKeyBurglar_Text_4:
	.string "You... You did it!\p"
	.string "I can't thank you enough. Here, it's\n"
	.string "yours as promised.$"

MagernaKeyBurglar_Text_5:
	.string "{PLAYER} obtained Apartment Key!$"

MagernaKeyBurglar_Text_6:
	.string "You can use it to access the top floor\n"
	.string "of Goldenrod apartment building.$"

MagernaKeyBurglar_Text_7:
	.string "As for me, it's time to say goodbye\n"
	.string "to ice soup!$"
