
Route46_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route46_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route46_EventScript_Bailey::
	trainerbattle_single TRAINER_BAILEY, Route46_Text_HikerBaileySeen, Route46_Text_HikerBaileyBeaten
	msgbox Route46_Text_HikerBaileyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Ted::
	trainerbattle_single TRAINER_TED, Route46_Text_CamperTedSeen, Route46_Text_CamperTedBeaten
	msgbox Route46_Text_CamperTedAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Erin::
	trainerbattle_single TRAINER_ERIN, Route46_Text_PicnickerErinSeen, Route46_Text_PicnickerErinBeaten
	msgbox Route46_Text_PicnickerErinAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Sign::
	lock
	msgbox Route46_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route46_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

Route46_Text_HikerBaileySeen:
	.string "Awright! I'll show you the\n"
	.string "power of mountain Pokémon!$"

Route46_Text_HikerBaileyBeaten:
	.string "Mercy! You showed me your\n"
	.string "power!$"

Route46_Text_HikerBaileyAfterBattle:
	.string "It's over. I don't mind.\n"
	.string "We Hikers are like that.$"

Route46_Text_CamperTedSeen:
	.string "I'm raising Pokémon too!\p"
	.string "Will you battle with me?$"

Route46_Text_CamperTedBeaten:
	.string "Wha…?$"

Route46_Text_CamperTedAfterBattle:
	.string "I did my best but came up\n"
	.string "short.\p"
	.string "No excuses--I admit I lost.$"

Route46_Text_PicnickerErinSeen:
	.string "I raise Pokémon too!\p"
	.string "Will you battle with me?$"

Route46_Text_PicnickerErinBeaten:
	.string "Oh, rats!$"

Route46_Text_PicnickerErinAfterBattle:
	.string "I've been to many Gyms, but the\n"
	.string "Gym in Goldenrod is my favorite.\p"
	.string "It's filled with pretty flowers!$"

Route46_Text_PicnickerErin2Beaten:
	.string "Aww… I keep losing all the time!\p"
	.string "I'll just have to try harder!\n"
	.string "Anyway, thanks for battling\n"
	.string "me again and again.\p"
	.string "Here's that present from the\n"
	.string "other time.$"

Route46_Text_Sign:
	.string "Route 46\n"
	.string "Mountain Rd. Ahead$"

Route46_ConfusedBugCatcher::
	lock
	faceplayer
	msgbox Route46_ConfusedBugCatcher_Text_0
	release
	end


Route46_ConfusedBugCatcher_Text_0:
	.string "Huh, I was hoping to get to Blackthorn\n"
	.string "City from here. I guess there's no way\l"
	.string "to climb those ledges...$"
