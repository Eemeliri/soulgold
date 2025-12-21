# 1 "data/maps/Route46/scripts.pory"

# 2 "data/maps/Route46/scripts.pory"
Route46_MapScripts::
# 3 "data/maps/Route46/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
# 4 "data/maps/Route46/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 5 "data/maps/Route46/scripts.pory"
	.byte 0
# 6 "data/maps/Route46/scripts.pory"

# 7 "data/maps/Route46/scripts.pory"
Route46_OnTransition: 
# 8 "data/maps/Route46/scripts.pory"
	callnative SetTimeBasedEncounters
# 9 "data/maps/Route46/scripts.pory"
	end
# 10 "data/maps/Route46/scripts.pory"

# 11 "data/maps/Route46/scripts.pory"
Route46_EventScript_Bailey::
# 12 "data/maps/Route46/scripts.pory"
	trainerbattle_single TRAINER_BAILEY, Route46_Text_HikerBaileySeen, Route46_Text_HikerBaileyBeaten
# 13 "data/maps/Route46/scripts.pory"
	msgbox Route46_Text_HikerBaileyAfterBattle, MSGBOX_AUTOCLOSE
# 14 "data/maps/Route46/scripts.pory"
	end
# 15 "data/maps/Route46/scripts.pory"

# 16 "data/maps/Route46/scripts.pory"
Route46_EventScript_Ted::
# 17 "data/maps/Route46/scripts.pory"
	trainerbattle_single TRAINER_TED, Route46_Text_CamperTedSeen, Route46_Text_CamperTedBeaten
# 18 "data/maps/Route46/scripts.pory"
	msgbox Route46_Text_CamperTedAfterBattle, MSGBOX_AUTOCLOSE
# 19 "data/maps/Route46/scripts.pory"
	end
# 20 "data/maps/Route46/scripts.pory"

# 21 "data/maps/Route46/scripts.pory"
Route46_EventScript_Erin::
# 22 "data/maps/Route46/scripts.pory"
	trainerbattle_single TRAINER_ERIN, Route46_Text_PicnickerErinSeen, Route46_Text_PicnickerErinBeaten
# 23 "data/maps/Route46/scripts.pory"
	msgbox Route46_Text_PicnickerErinAfterBattle, MSGBOX_AUTOCLOSE
# 24 "data/maps/Route46/scripts.pory"
	end
# 25 "data/maps/Route46/scripts.pory"

# 26 "data/maps/Route46/scripts.pory"
Route46_EventScript_Sign::
# 27 "data/maps/Route46/scripts.pory"
	lock
# 28 "data/maps/Route46/scripts.pory"
	msgbox Route46_Text_Sign, MSGBOX_SIGN
# 29 "data/maps/Route46/scripts.pory"
	closemessage
# 30 "data/maps/Route46/scripts.pory"
	release
# 31 "data/maps/Route46/scripts.pory"
	end
# 32 "data/maps/Route46/scripts.pory"

# 33 "data/maps/Route46/scripts.pory"
Route46_EventScript_Item_Revive::
# 34 "data/maps/Route46/scripts.pory"
	finditem ITEM_REVIVE
# 35 "data/maps/Route46/scripts.pory"
	end
# 36 "data/maps/Route46/scripts.pory"

# 37 "data/maps/Route46/scripts.pory"
Route46_Text_HikerBaileySeen:
# 38 "data/maps/Route46/scripts.pory"
	.string "Awright! I'll show you the\n"
# 39 "data/maps/Route46/scripts.pory"
	.string "power of mountain POKéMON!$"
# 40 "data/maps/Route46/scripts.pory"

# 41 "data/maps/Route46/scripts.pory"
Route46_Text_HikerBaileyBeaten:
# 42 "data/maps/Route46/scripts.pory"
	.string "Mercy! You showed me your\n"
# 43 "data/maps/Route46/scripts.pory"
	.string "power!$"
# 44 "data/maps/Route46/scripts.pory"

# 45 "data/maps/Route46/scripts.pory"
Route46_Text_HikerBaileyAfterBattle:
# 46 "data/maps/Route46/scripts.pory"
	.string "It's over. I don't mind.\n"
# 47 "data/maps/Route46/scripts.pory"
	.string "We HIKERS are like that.$"
# 48 "data/maps/Route46/scripts.pory"

# 49 "data/maps/Route46/scripts.pory"
Route46_Text_CamperTedSeen:
# 50 "data/maps/Route46/scripts.pory"
	.string "I'm raising POKéMON too!\p"
# 51 "data/maps/Route46/scripts.pory"
	.string "Will you battle with me?$"
# 52 "data/maps/Route46/scripts.pory"

# 53 "data/maps/Route46/scripts.pory"
Route46_Text_CamperTedBeaten:
# 54 "data/maps/Route46/scripts.pory"
	.string "Wha…?$"
# 55 "data/maps/Route46/scripts.pory"

# 56 "data/maps/Route46/scripts.pory"
Route46_Text_CamperTedAfterBattle:
# 57 "data/maps/Route46/scripts.pory"
	.string "I did my best but came up\n"
# 58 "data/maps/Route46/scripts.pory"
	.string "short.\p"
# 59 "data/maps/Route46/scripts.pory"
	.string "No excuses--I admit I lost.$"
# 60 "data/maps/Route46/scripts.pory"

# 61 "data/maps/Route46/scripts.pory"
Route46_Text_PicnickerErinSeen:
# 62 "data/maps/Route46/scripts.pory"
	.string "I raise POKéMON too!\p"
# 63 "data/maps/Route46/scripts.pory"
	.string "Will you battle with me?$"
# 64 "data/maps/Route46/scripts.pory"

# 65 "data/maps/Route46/scripts.pory"
Route46_Text_PicnickerErinBeaten:
# 66 "data/maps/Route46/scripts.pory"
	.string "Oh, rats!$"
# 67 "data/maps/Route46/scripts.pory"

# 68 "data/maps/Route46/scripts.pory"
Route46_Text_PicnickerErinAfterBattle:
# 69 "data/maps/Route46/scripts.pory"
	.string "I've been to many GYMS, but the\n"
# 70 "data/maps/Route46/scripts.pory"
	.string "GYM in GOLDENROD is my favorite.\p"
# 71 "data/maps/Route46/scripts.pory"
	.string "It's filled with pretty flowers!$"
# 72 "data/maps/Route46/scripts.pory"

# 73 "data/maps/Route46/scripts.pory"
Route46_Text_PicnickerErin2Beaten:
# 74 "data/maps/Route46/scripts.pory"
	.string "Aww… I keep losing all the time!\p"
# 75 "data/maps/Route46/scripts.pory"
	.string "I'll just have to try harder!\n"
# 76 "data/maps/Route46/scripts.pory"
	.string "Anyway, thanks for battling\n"
# 77 "data/maps/Route46/scripts.pory"
	.string "me again and again.\p"
# 78 "data/maps/Route46/scripts.pory"
	.string "Here's that present from the\n"
# 79 "data/maps/Route46/scripts.pory"
	.string "other time.$"
# 80 "data/maps/Route46/scripts.pory"

# 81 "data/maps/Route46/scripts.pory"
Route46_Text_Sign:
# 82 "data/maps/Route46/scripts.pory"
	.string "ROUTE 46\n"
# 83 "data/maps/Route46/scripts.pory"
	.string "MOUNTAIN RD. AHEAD$"

Route46_ConfusedBugCatcher::
# 87 "data/maps/Route46/scripts.pory"
	lock
# 88 "data/maps/Route46/scripts.pory"
	msgbox Route46_ConfusedBugCatcher_Text_0
# 89 "data/maps/Route46/scripts.pory"
	release
	end


Route46_ConfusedBugCatcher_Text_0:
# 88 "data/maps/Route46/scripts.pory"
	.string "Huh, I was hoping to get to Blackthorn\n"
	.string "City from here. I guess there's no way\l"
	.string "to climb those ledges...$"
