
.set LOCALID_R43_EXPERT, 3

Route43_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route43_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route43_MapScript_OnTransition::
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route43_EventScript_Brent::
	trainerbattle_single TRAINER_BRENT Route43_Text_PokemaniacBrentSeen, Route43_Text_PokemaniacBrentBeaten
	msgbox Route43_Text_PokemaniacBrentAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Ron::
	trainerbattle_single TRAINER_RON Route43_Text_PokemaniacRonSeen, Route43_Text_PokemaniacRonBeaten
	msgbox Route43_Text_PokemaniacRonAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Marvin::
	trainerbattle_single TRAINER_MARVIN Route43_Text_FisherMarvinSeen, Route43_Text_FisherMarvinBeaten
	msgbox Route43_Text_FisherMarvinAfter, MSGBOX_AUTOCLOSE
	end
	
Route43_EventScript_Spencer::
	trainerbattle_single TRAINER_SPENCER Route43_Text_CamperSpencerSeen, Route43_Text_CamperSpencerBeaten
	msgbox Route43_Text_CamperSpencerAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY Route43_Text_PicnickerTiffanySeen, Route43_Text_PicnickerTiffanyBeaten
	msgbox Route43_Text_PicnickerTiffanyWantsPicnic, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Sign1::
	msgbox Route43_Sign2, MSGBOX_SIGN
	end

Route43_EventScript_Sign2::
	msgbox Route43_TrainerTips, MSGBOX_SIGN
	end

Route43_Text_PokemaniacBenSeen:
    .string "I love Pokémon!\p"
    .string "That's why I started--and why I'll\n"
    .string "keep on collecting Pokémon!$"

Route43_Text_PokemaniacBenBeaten:
    .string "How could you do this to me?$"

Route43_Text_PokemaniacBenAfter:
    .string "What else do I like besides\n"
    .string "Pokémon?\p"
    .string "Mary on the radio. I bet she's\n"
    .string "cute!$"

Route43_Text_PokemaniacBrentSeen:
    .string "Hey! Do you have any rare\n"
    .string "Pokémon?$"

Route43_Text_PokemaniacBrentBeaten:
    .string "Oh, my poor Pokémon! Darlings!$"

Route43_Text_PokemaniacBrentAfter:
    .string "I'd be happy just to own a single\n"
    .string "rare Pokémon.$"

Route43_Text_PokemaniacRonSeen:
    .string "Would you get this?\p"
    .string "Some Silver guy made fun of my\n"
    .string "Pokémon!\p"
    .string "Darn it! My Pokémon's great!$"

Route43_Text_PokemaniacRonBeaten:
    .string "My Nidoking did pretty right on!$"

Route43_Text_PokemaniacRonAfter:
    .string "It's okay for people to like\n"
    .string "different types of Pokémon.\p"
    .string "Pokémon isn't just about having the\n"
    .string "most powerful one.$"

Route43_Text_FisherMarvinSeen:
    .string "I'm in a slump.\p"
    .string "Maybe it's the gear I'm using.\p"
    .string "Let's battle for a change of pace!$"

Route43_Text_FisherMarvinBeaten:
    .string "I lost, but I feel better anyway.$"

Route43_Text_FisherMarvinAfter:
    .string "Kurt's Lure Ball is the best for\n"
    .string "catching hooked Pokémon.\p"
    .string "It's much more effective than a\n"
    .string "Ultra Ball.$"

Route43_Text_CamperSpencerSeen:
    .string "I can do so much with my\n"
    .string "Pokémon--it's super-fun!$"

Route43_Text_CamperSpencerBeaten:
    .string "Losing isn't fun at all…$"

Route43_Text_CamperSpencerAfter:
    .string "What is going on at Lake Of Rage?\p"
    .string "We were planning to camp there.$"

Route43_Text_PicnickerTiffanySeen:
    .string "Are you going to Lake Of Rage too?\p"
    .string "Let's play for a little while!$"

Route43_Text_PicnickerTiffanyBeaten:
    .string "I played too much!$"

Route43_Text_PicnickerTiffanyWantsPicnic:
    .string "I'm having a picnic with Pokémon.\p"
    .string "Won't you join us?$"

Route43_Sign1:
    .string "Route 43\p"
    .string "Lake Of Rage - Mahogany Town$"

Route43_Sign2:
    .string "Route 43\p"
    .string "Lake Of Rage - Mahogany Town$"

Route43_TrainerTips:
    .string "Trainer Tips\p"
    .string "All Pokémon have pros and cons\n"
    .string "depending on their types.\p"
    .string "If their types differ, a higher-\n"
    .string "level Pokémon may lose in battle.\p"
    .string "Learn which types are strong and\n"
    .string "weak against your Pokémon's type.$"

Route43Expert::
	lock
	faceplayer
	goto_if_set FLAG_ROUTE43_EXPERT, Route43Expert_2
	msgbox Route43Expert_Text_1
	goto_if_set FLAG_ROUTE43_EXPERT_QUALIFIED, Route43Expert_5
	checktrainerflag TRAINER_BRENT
	goto_if 1, Route43Expert_9
Route43Expert_4:
	release
	end

Route43Expert_2:
	setflag FLAG_ROUTE43_EXPERT_QUALIFIED
	msgbox Route43Expert_Text_0
	release
	end

Route43Expert_5:
	setflag FLAG_ROUTE43_EXPERT_QUALIFIED
	playse SE_PIN
	applymovement LOCALID_R43_EXPERT, Common_Movement_ExclamationMark
	waitse
	msgbox Route43Expert_Text_2
	trainerbattle_no_intro TRAINER_HERB_EXPERT, Route43Expert_Text_3
	msgbox Route43Expert_Text_4
	giveitem ITEM_POWER_HERB
	giveitem ITEM_WHITE_HERB
	setflag FLAG_ROUTE43_EXPERT
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
	special Achievement_CheckAll
	msgbox Route43Expert_Text_0
	goto Route43Expert_4

Route43Expert_8:
	checktrainerflag TRAINER_MARVIN
	goto_if 1, Route43Expert_13
	goto Route43Expert_4

Route43Expert_9:
	checktrainerflag TRAINER_RON
	goto_if 1, Route43Expert_8
	goto Route43Expert_4

Route43Expert_12:
	checktrainerflag TRAINER_TIFFANY
	goto_if 1, Route43Expert_17
	goto Route43Expert_4

Route43Expert_13:
	checktrainerflag TRAINER_SPENCER
	goto_if 1, Route43Expert_12
	goto Route43Expert_4

Route43Expert_16:
	checktrainerflag TRAINER_RAYMOND
	goto_if 1, Route43Expert_21
	goto Route43Expert_4

Route43Expert_17:
	checktrainerflag TRAINER_ANDRE
	goto_if 1, Route43Expert_16
	goto Route43Expert_4

Route43Expert_20:
	checktrainerflag TRAINER_LOIS
	goto_if 1, Route43Expert_5
	goto Route43Expert_4

Route43Expert_21:
	checktrainerflag TRAINER_AARON
	goto_if 1, Route43Expert_20
	goto Route43Expert_4


Route43Expert_Text_0:
	.string "Power Herb and White Herb only\n"
	.string "work once per battle, but they\l"
	.string "regrow back after it.$"

Route43Expert_Text_1:
	.string "Many trainers gather here to see\n"
	.string "what the fuss is about.\p"
	.string "Me? I'm here to find the strongest\n"
	.string "trainer among them.\p"
	.string "Perhaps if you were to defeat all\n"
	.string "the others here and around the\l"
	.string "Lake of Rage, we could have a bout.$"

Route43Expert_Text_2:
	.string "Impressive battling prowess!\p"
	.string "But can you turn the tides against\n"
	.string "my strategy?$"

Route43Expert_Text_3:
	.string "I could not turn the situation around.$"

Route43Expert_Text_4:
	.string "Your strength is in full bloom.\n"
	.string "Take these herbs and use them\l"
	.string "to turn the battle around.$"
