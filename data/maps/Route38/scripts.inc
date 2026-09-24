
Route38_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route38_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route38_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route38_EventScript_Toby::
	trainerbattle_single TRAINER_TOBY, Route38_Text_BirdKeeperTobySeen, Route38_Text_BirdKeeperTobyBeaten
	msgbox Route38_Text_BirdKeeperTobyAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Chad::
	trainerbattle_single TRAINER_CHAD, Route38_Text_SchoolboyChad1Seen, Route38_Text_SchoolboyChad1Beaten
	msgbox Route38_Text_SchoolboyChadAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Dana::
	trainerbattle_single TRAINER_DANA, Route38_Text_LassDana1Seen, Route38_Text_LassDana1Beaten
	msgbox Route38_Text_LassDanaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE, Route38_Text_BeautyValerieSeen, Route38_Text_BeautyValerieBeaten
	msgbox Route38_Text_BeautyValerieAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Harry::
	trainerbattle_single TRAINER_HARRY, Route38_Text_SailorHarrySeen, Route38_Text_SailorHarryBeaten
	msgbox Route38_Text_SailorHarryAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, Route38_Text_BeautyOliviaSeen, Route38_Text_BeautyOliviaBeaten
	msgbox Route38_Text_BeautyOliviaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Sign1::
	lock
	msgbox Route38_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Sign2::
	lock
	msgbox Route38_Text_WaterSign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_Text_BirdKeeperTobySeen:
	.string "Fly high into the sky,\n"
	.string "my beloved bird Pokémon!$"

Route38_Text_BirdKeeperTobyBeaten:
	.string "I feel like just flying\n"
	.string "away now.$"

Route38_Text_BirdKeeperTobyAfter:
	.string "I plan to train in Cianwood City\n"
	.string "to teach my Pokémon how to Fly.$"

Route38_Text_SchoolboyChad1Seen:
	.string "Let me try something\n"
	.string "I learned today.$"

Route38_Text_SchoolboyChad1Beaten:
	.string "I didn't study enough,\n"
	.string "I guess.$"

Route38_Text_SchoolboyChadAfter:
	.string "I have to take so many\n"
	.string "tests, I don't have much\l"
	.string "time for Pokémon.\p"
	.string "So when I do get to play,\n"
	.string "I really concentrate.$"

Route38_Text_LassDana1Seen:
	.string "You seem to be good at\n"
	.string "Pokémon.\p"
	.string "If you are, how about\n"
	.string "giving me some advice?$"

Route38_Text_LassDana1Beaten:
	.string "I see. So you can battle\n"
	.string "that way.$"

Route38_Text_LassDanaAfter:
	.string "I know something good!\p"
	.string "Moomoo Farm's milk is\n"
	.string "famous for its flavor.$"

Route38_Text_BeautyValerieSeen:
	.string "Hi! Aren't you a cute\n"
	.string "trainer!\p"
	.string "May I see your Pokémon?$"

Route38_Text_BeautyValerieBeaten:
	.string "I'm glad I got to see\n"
	.string "your Pokémon!$"

Route38_Text_BeautyValerieAfter:
	.string "When I see Pokémon, it\n"
	.string "seems to soothe my nerves.$"

Route38_Text_SailorHarrySeen:
	.string "I've been overseas, so I\n"
	.string "know about all sorts of\l"
	.string "Pokémon!$"

Route38_Text_SailorHarryBeaten:
	.string "Your skill is world class!$"

Route38_Text_SailorHarryAfter:
	.string "All kinds of people around\n"
	.string "the world live happily with\l"
	.string "Pokémon.$"

Route38_Text_BeautyOliviaSeen:
	.string "Don't you think my Pokémon\n"
	.string "and I are beautiful?$"

Route38_Text_BeautyOliviaBeaten:
	.string "We drink Moomoo Milk every\n"
	.string "day.$"

Route38_Text_BeautyOliviaAfter:
	.string "Moomoo Milk is good for\n"
	.string "beauty and health,\p"
	.string "but inconveniently, they\n"
	.string "only sell one bottle at a time.$"

Route38_Text_Sign:
	.string "Route 38\p"
	.string "Olivine City - Ecruteak City$"

Route38_Text_TrainerTips:
	.string "Trainer Tips\p"
	.string "If a Pokémon is trying to\n"
	.string "evolve, you can stop it.\p"
	.string "Press the B Button during\n"
	.string "evolution to cancel it.\p"
	.string "That startles the Pokémon\n"
	.string "and stops its evolution.$"


Route38_Text_WaterSign:
	.string "No Swimming Or Fishing.\n"
	.string "Water For Farming Only.\p"
	.string "-Ecruteak Council$"

Route38_HiddenGrotto::
	msgbox Route38_HiddenGrotto_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route38_HiddenGrotto_2
Route38_HiddenGrotto_1:
	release
	end

Route38_HiddenGrotto_2:
	warp MAP_HIDDEN_GROTTO_ROUTE38, 0
	waitstate
	goto Route38_HiddenGrotto_1


Route38_HiddenGrotto_Text_0:
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"
