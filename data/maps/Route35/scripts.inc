
Route35_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route35_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route35_OnTransition: 
	callnative SetTimeBasedEncounters
	end	

Route35_EventScript_CamperIvan::
	trainerbattle_single TRAINER_IVAN Route35_Text_CamperIvanSeen, Route35_Text_CamperIvanBeaten
	msgbox Route35_Text_CamperIvanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_CamperElliot::
	trainerbattle_single TRAINER_ELLIOT Route35_Text_CamperElliotSeen, Route35_Text_CamperElliotBeaten
	msgbox Route35_Text_CamperElliotAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerBrooke::
	trainerbattle_single TRAINER_BROOKE Route35_Text_PicnickerBrookeSeen, Route35_Text_PicnickerBrookeBeaten
	msgbox Route35_Text_PicnickerBrookeAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerKim::
	trainerbattle_single TRAINER_KIM Route35_Text_PicnickerKimSeen, Route35_Text_PicnickerKimBeaten
	msgbox Route35_Text_PicnickerKimAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BirdKeeperBryan::
	trainerbattle_single TRAINER_BRYAN Route35_Text_BirdKeeperBryanSeen, Route35_Text_BirdKeeperBryanBeaten
	msgbox Route35_Text_BirdKeeperBryanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_JugglerIrwin::
	trainerbattle_single TRAINER_IRWIN Route35_Text_JugglerIrwinSeen, Route35_Text_JugglerIrwinBeaten
	msgbox Route35_Text_JugglerIrwinAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BugCatcherArnie::
	trainerbattle_single TRAINER_ARNIE Route35_Text_BugCatcherArnieSeen, Route35_Text_BugCatcherArnieBeaten
	msgbox Route35_Text_BugCatcherArnieAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_FirebreatherWalt::
	trainerbattle_single TRAINER_WALT Route35_Text_FirebreatherWaltSeen, Route35_Text_FirebreatherWaltBeaten
	msgbox Route35_Text_FirebreatherWaltAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PolicemanDirk::
	trainerbattle_single TRAINER_DIRK Route35_Text_OfficerDirkSeen, Route35_Text_OfficerDirkBeaten
	msgbox Route35_Text_OfficerDirkAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_Sign1::
	lock
	msgbox Route35_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route35_EventScript_Sign2::
	lock
	msgbox Route35_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route35_Text_CamperIvanSeen:
	.string "I've been getting Pokémon data off\n"
	.string "my radio. I think I'm good.$"

Route35_Text_CamperIvanBeaten:
	.string "I give!$"

Route35_Text_CamperIvanAfter:
	.string "Music on the radio changes the\n"
	.string "moods of wild Pokémon.$"

Route35_Text_CamperElliotSeen:
	.string "I'm gonna show my girlfriend I'm\n"
	.string "hot stuff!$"

Route35_Text_CamperElliotBeaten:
	.string "I wish you would have lost for me…$"

Route35_Text_CamperElliotAfter:
	.string "I was humiliated in front of my\n"
	.string "girlfriend…$"

Route35_Text_PicnickerBrookeSeen:
	.string "My boyfriend's weak, so I can't rely\n"
	.string "on him.$"

Route35_Text_PicnickerBrookeBeaten:
	.string "Oh, my! You're so strong!$"

Route35_Text_PicnickerBrookeAfter:
	.string "I can count on my Pokémon more than\n"
	.string "my boyfriend.$"

Route35_Text_PicnickerKimSeen:
	.string "Are you going to the Gym? Me too!$"

Route35_Text_PicnickerKimBeaten:
	.string "Oh. I couldn't win…$"

Route35_Text_PicnickerKimAfter:
	.string "The Gym Badges are pretty. I collect\n"
	.string "them.$"

Route35_Text_BirdKeeperBryanSeen:
	.string "What kinds of Balls do you use?$"

Route35_Text_BirdKeeperBryanBeaten:
	.string "Yikes! Not fast enough!$"

Route35_Text_BirdKeeperBryanAfter:
	.string "Whenever I find a Nugget, I\n"
	.string "take it to Mart.\p"
	.string "It's an easy way to get money.$"

Route35_Text_JugglerIrwinSeen:
	.string "Behold my graceful Ball dexterity!$"

Route35_Text_JugglerIrwinBeaten:
	.string "Whew! That was a jolt!$"

Route35_Text_JugglerIrwinAfter:
	.string "I was going to dazzle you with my\n"
	.string "prize Pokémon.\p"
	.string "But your prowess electrified me!$"

Route35_Text_BugCatcherArnieSeen:
	.string "I'll go anywhere if bug Pokémon\n"
	.string "appear there.$"

Route35_Text_BugCatcherArnieBeaten:
	.string "Huh? I shouldn't have lost that…$"

Route35_Text_BugCatcherArnieAfter:
	.string "My Venonat won me the Bug-Catching\n"
	.string "Contest at the National Park.$"

Route35_Text_BugCatcherArnieYanma:
	.string "Wow… Look at all those Yanma!\p"
	.string "I'm so blown away, I can't move.$"

Route35_Text_FirebreatherWaltSeen:
	.string "I'm practicing my fire breathing.$"

Route35_Text_FirebreatherWaltBeaten:
	.string "Ow! I scorched the tip of my nose!$"

Route35_Text_FirebreatherWaltAfter:
	.string "The Pokémon March on the radio\n"
	.string "lures wild Pokémon.$"

Route35_Text_OfficerDirkSeen:
	.string "Danger lurks in the night!$"

Route35_Text_OfficerDirkBeaten:
	.string "Whoops!$"

Route35_Text_OfficerDirkAfter:
	.string "You know, nighttime is fun in its\n"
	.string "own ways.\p"
	.string "But don't overdo it, Ok?$"

Route35_Text_OfficerDirkTough:
	.string "Your Pokémon look pretty tough.\p"
	.string "You could go anywhere safely.$"

Route35_Text_Sign:
	.string "Route 35$"

Route35_Text_Sign2:
	.string "National Park Gate$"

Route35_HiddenGrotto::
	msgbox Route35_HiddenGrotto_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route35_HiddenGrotto_2
Route35_HiddenGrotto_1:
	release
	end

Route35_HiddenGrotto_2:
	warp MAP_HIDDEN_GROTTO_ROUTE35, 0
	waitstate
	goto Route35_HiddenGrotto_1


Route35_HiddenGrotto_Text_0:
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"
