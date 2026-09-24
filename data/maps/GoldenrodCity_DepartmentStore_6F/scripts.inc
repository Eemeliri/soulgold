
GoldenrodCity_DepartmentStore_6F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore6_EventScript_Whitney::
	lock
	faceplayer
	msgbox GoldenrodDeptStore6_Text_Whitney, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_DEPTSTORE_WHITNEY
	removeobject LOCALID_STORE_WHITNEY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_WHITNEY
	release
	end

GoldenrodDeptStore6_Text_Whitney:
	.string "{PLAYER}! Fancy seeing you here!\p"
	.string "I'm picking up something for\n"
	.string "my Miltank.\p"
	.string "If you want another battle, come to\n"
	.string "the Fighting Dojo!$"

GoldenrodCity_DepartmentStore_6F_EventScript_DeclineTrade::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_TradeCompleted::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_After, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_Text_YouWillTradeWontYou:
	.string "I collect Pokémon!\n"
	.string "Do you have a {STR_VAR_1}?\p"
	.string "Want to trade it for my\n"
	.string "{STR_VAR_2}?$"

GoldenrodCity_DepartmentStore_6F_Text_MonYouTakeCare:
	.string "Yay! I got myself {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, you take care!$"

GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon:
	.string "Uh, no, I don't think so.\n"
	.string "That isn't a {STR_VAR_1}.$"

GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe:
	.string "You don't want to trade? Aww...$"

GoldenrodCity_DepartmentStore_6F_Text_After:
	.string "Hi, how's my old Machop doing?$"


GoldenrodDeptStore6_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_6FLass:
    .string "Do you listen to Lucky Channel?\p"
    .string "If you want to win, trade Pokémon\n"
    .string "with as many people as possible to\l"
    .string "get different Id numbers.$"

GoldenrodDeptStore_Text_6FSuperNerd:
    .string "If you're tired, try the vending\n"
    .string "machine's drinks.\p"
    .string "Your Pokémon will love them too.$"

GoldenrodDeptStore_Text_6FDirectory:
    .string "Take a Break from Shopping!\p"
    .string "6F Tranquil Square$"

GoldenrodCity_DepartmentStore_6F_EventScript_Jose::
	lock
	faceplayer
	goto_if_set FLAG_GOLDENROD_NPC_TRADE_COMPLETED, GoldenrodCity_DepartmentStore_6F_EventScript_Jose_2
	ingame_trade INGAME_TRADE_HONEDGE, GoldenrodCity_DepartmentStore_6F_EventScript_Jose_Text_1, HonedgeTrade_Declined, HonedgeTrade_NotRequested, GoldenrodCity_DepartmentStore_6F_EventScript_Jose_Text_2
	setflag FLAG_GOLDENROD_NPC_TRADE_COMPLETED
GoldenrodCity_DepartmentStore_6F_EventScript_Jose_1:
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_Jose_2:
	msgbox GoldenrodCity_DepartmentStore_6F_EventScript_Jose_Text_0
	goto GoldenrodCity_DepartmentStore_6F_EventScript_Jose_1


HonedgeTrade_Declined::
	msgbox HonedgeTrade_Declined_Text_0
	release
	end


HonedgeTrade_NotRequested::
	msgbox HonedgeTrade_NotRequested_Text_0
	release
	end


GoldenrodDEpt6F_WhitneyRematch::
	lock
	msgbox GoldenrodDEpt6F_WhitneyRematch_Text_0
	applymovement LOCALID_STORE_WHITNEY, Common_Movement_ExclamationMark
	applymovement LOCALID_STORE_WHITNEY, GoldenrodDEpt6F_WhitneyRematch_Movement_0
	waitmovement 0
	msgbox GoldenrodDEpt6F_WhitneyRematch_Text_1
	msgbox GoldenrodDEpt6F_WhitneyRematch_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, TRUE
	goto_if_eq GoldenrodDEpt6F_WhitneyRematch_2
GoldenrodDEpt6F_WhitneyRematch_1:
	release
	end

GoldenrodDEpt6F_WhitneyRematch_2:
	trainerbattle_no_intro TRAINER_WHITNEY_2, GoldenrodDEpt6F_WhitneyRematch_Text_3
	msgbox GoldenrodDEpt6F_WhitneyRematch_Text_4
	closemessage
	moveobjecttocoords LOCALID_STORE_WHITNEY, 24, 5, DIR_WEST
	setflag FLAG_HIDE_DEPTSTORE_WHITNEY
	playse SE_EXIT
	removeobject LOCALID_STORE_WHITNEY
	delay 30
	goto GoldenrodDEpt6F_WhitneyRematch_1


GoldenrodDEpt6F_WhitneyRematch_Movement_0:
	face_player
	step_end

GoldenrodCity_DepartmentStore_6F_EventScript_Jose_Text_0:
	.string "Thanks for the Clefairy again!\n"
	.string "Hope my Pokémon has been of use to you!$"

GoldenrodCity_DepartmentStore_6F_EventScript_Jose_Text_1:
	.string "I've been looking for a rare Pokémon\n"
	.string "Clefairy for a while now. Do you have it?\l"
	.string "I'll give you something rare in return!$"

GoldenrodCity_DepartmentStore_6F_EventScript_Jose_Text_2:
	.string "Thanks a lot!$"

HonedgeTrade_Declined_Text_0:
	.string "Shame, I hear Clefairy can be found on\n"
	.string "Route 34 sometimes.$"

HonedgeTrade_NotRequested_Text_0:
	.string "I don't think that's a Clefairy...$"

GoldenrodDEpt6F_WhitneyRematch_Text_0:
	.string "Hmm... Maybe this one...?\n"
	.string "No... That one is cheaper...\l"
	.string "Wait, but if I buy two then...$"

GoldenrodDEpt6F_WhitneyRematch_Text_1:
	.string "Oh, hi there!\n"
	.string "Do you also shop here? I was here\l"
	.string "today to check on some new Pokéfan\l"
	.string "magazines. They have the cutest\l"
	.string "Clefairies!$"

GoldenrodDEpt6F_WhitneyRematch_Text_2:
	.string "Hey I know, how about a battle?\n"
	.string "I promise I'll make you cry this\l"
	.string "time instead!$"

GoldenrodDEpt6F_WhitneyRematch_Text_3:
	.string "Mustn't cry... Mustn't cry...!$"

GoldenrodDEpt6F_WhitneyRematch_Text_4:
	.string "Aaaaargh! I thought I had you there!\n"
	.string "So frustrating...\p"
	.string "That was a really good battle, but I\n"
	.string "always get so frustrated when I lose\l"
	.string "that I want to cry. I've been trying\l"
	.string "really hard to get out of that habit.\p"
	.string "I've decided that next time we battle,\n"
	.string "I'll try even harder and we'll roll\l"
	.string "you over! Until then, you better train \l"
	.string "hard!$"
