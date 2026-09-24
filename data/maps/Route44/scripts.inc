
Route44_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route44_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route44_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route44_EventScript_Wilton::
	trainerbattle_single TRAINER_WILTON Route44_Text_FisherWilton1Seen, Route44_Text_FisherWilton1Beaten
	msgbox Route44_Text_FisherWiltonHugePoliwag, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR Route44_Text_FisherEdgarSeen, Route44_Text_FisherEdgarBeaten
	msgbox Route44_Text_FisherEdgarAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Vance::
	trainerbattle_single TRAINER_VANCE Route44_Text_BirdKeeperVance1Seen, Route44_Text_BirdKeeperVance1Beaten
	msgbox Route44_Text_BirdKeeperVanceBirds, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Phil::
	trainerbattle_single TRAINER_PHIL Route44_Text_PsychicPhilSeen, Route44_Text_PsychicPhilBeaten
	msgbox Route44_Text_PsychicPhilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Zach::
	trainerbattle_single TRAINER_ZACH Route44_Text_PokemaniacZachSeen, Route44_Text_PokemaniacZachBeaten
	msgbox Route44_Text_PokemaniacZachAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN Route44_Text_CooltrainermAllenSeen, Route44_Text_CooltrainermAllenBeaten
	msgbox Route44_Text_CooltrainermAllenAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Cybil::
	trainerbattle_single TRAINER_CYBIL Route44_Text_CooltrainerfCybilSeen, Route44_Text_CooltrainerfCybilBeaten
	msgbox Route44_Text_CooltrainerfCybilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Sign1::
	msgbox Route44_Text_Sign1, MSGBOX_SIGN
	end

Route44_EventScript_Sign2::
	msgbox Route44_Text_Sign2, MSGBOX_SIGN
	end

Route44_Text_FisherWilton1Seen:
    .string "Aack!\p"
    .string "You made me lose a Poliwag!\n"
    .string "What are you going to do about it?$"

Route44_Text_FisherWilton1Beaten:
    .string "Just forget about it.$"

Route44_Text_FisherWiltonHugePoliwag:
    .string "That Poliwag that got away…\n"
    .string "it was huge.\p"
    .string "I swear it must've been\n"
    .string "16 feet long!$"

Route44_Text_FisherEdgarSeen:
    .string "I fish until I can't anymore.\p"
    .string "I also battle until I drop.\p"
    .string "That's my relationship with my\n"
    .string "Pokémon.$"

Route44_Text_FisherEdgarBeaten:
    .string "Hmmmm… This isn't right.$"

Route44_Text_FisherEdgarAfter:
    .string "That's 100 wins to 101 losses.\p"
    .string "I won't battle again for a while.$"

Route44_Text_BirdKeeperVance1Seen:
    .string "Do you know about the legendary\n"
    .string "bird Pokémon?$"

Route44_Text_BirdKeeperVance1Beaten:
    .string "Whew! You're hot stuff.$"

Route44_Text_BirdKeeperVanceBirds:
    .string "Articuno, Zapdos and Moltres are\n"
    .string "the three legendary bird Pokémon.\p"
    .string "I heard there are other legendary\n"
    .string "birds, though.$"

Route44_Text_PsychicPhilSeen:
    .string "I'm gonna win, for sure!$"

Route44_Text_PsychicPhilBeaten:
    .string "Arrgh… That's a shocking loss…$"

Route44_Text_PsychicPhilAfter:
    .string "It's important to have conviction\n"
    .string "on your side.$"

Route44_Text_PokemaniacZachSeen:
    .string "I'll do anything to get my hands\n"
    .string "on rare Pokémon!$"

Route44_Text_PokemaniacZachBeaten:
    .string "Oooh, your Pokémon are so\n"
    .string "appealing.$"

Route44_Text_PokemaniacZachAfter:
    .string "If a Pokémon has different colors\n"
    .string "from usual, it's more valuable.\p"
    .string "What? You mean that's not true?$"

Route44_Text_CooltrainermAllenSeen:
    .string "I can tell you're a good trainer\n"
    .string "by looking at you.\p"
    .string "I'm good at Pokémon, and I can\n"
    .string "see that you are too.$"

Route44_Text_CooltrainermAllenBeaten:
    .string "Tch! It's a total loss on my part.$"

Route44_Text_CooltrainermAllenAfter:
    .string "Wow. You have a lot of Badges.\p"
    .string "No wonder you're so tough.\p"
    .string "I wonder if Ecruteak Gym's Morty\n"
    .string "is still in training?\p"
    .string "He really hammered me.$"

Route44_Text_CooltrainerfCybilSeen:
    .string "You look strong.\p"
    .string "Good trainers seek tough\n"
    .string "opponents instinctively.$"

Route44_Text_CooltrainerfCybilBeaten:
    .string "Nope! This won't do at all.$"

Route44_Text_CooltrainerfCybilAfter:
    .string "We all get better by experiencing\n"
    .string "many battles.\p"
    .string "I battled a lot to become what I\n"
    .string "am today--an elite.$"

Route44_Text_Sign1:
    .string "Route 44\n"
    .string "Ice Path Ahead$"

Route44_Text_Sign2:
    .string "Route 44\p"
    .string "Mahogany Town - Blackthorn City$"

Route44_HiddenGrotto::
	msgbox Route44_HiddenGrotto_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route44_HiddenGrotto_2
Route44_HiddenGrotto_1:
	release
	end

Route44_HiddenGrotto_2:
	warp MAP_HIDDEN_GROTTO_ROUTE44, 0
	waitstate
	goto Route44_HiddenGrotto_1


Route44_HiddenGrotto_Text_0:
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"
