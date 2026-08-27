.set LOCALID_DRAGONSDEN3_CLAIR, 4
.set LOCALID_DRAGONSDEN3_ELDER, 1

DragonsDen_Shrine_MapScripts::
	@map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonsDen_Shrine_OnFrame
	.byte 0

DragonsDen_Shrine_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 2, DragonsDen_Shrine_Trigger_ElderQuizTop
	.2byte 0

DragonsDen_Shrine_EventScript_Elder::
	lock
	faceplayer
	goto_if_ge VAR_BLACKTHORN_CITY_STATE, 4, DragonsDen_Shrine_EventScript_ElderChooseDratini
	msgbox DragonsDen_Shrine_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Trigger_ElderQuizLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderLeft
	applymovement OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_MonWalkToElderLeft
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizTop::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	applymovement OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderRight
	applymovement OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_MonWalkToElderRight
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz


DragonsDen_Shrine_Movement_PlayerWalkToElderLeft:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_MonWalkToElderLeft:
	walk_left
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderTop:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderRight:
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
DragonsDen_Shrine_Movement_MonWalkToElderRight:
	walk_right
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_EventScript_ElderOfferQuiz::
	msgbox DragonsDen_Shrine_Text_ElderGreeting, MSGBOX_DEFAULT
	setvar VAR_DRAGONS_DEN_QUIZ, 0
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

DragonsDen_Shrine_EventScript_ElderQuiz1::
	message DragonsDen_Shrine_Text_Question1
	multichoice 20, 6, MULTI_ELDERQUIIZ1, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz1Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz1Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz1
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

DragonsDen_Shrine_EventScript_ElderQuiz1Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_ElderQuiz2::
	message DragonsDen_Shrine_Text_Question2
	multichoice 20, 6, MULTI_ELDERQUIIZ2, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz2Correct
	case 1, DragonsDen_Shrine_EventScript_ElderQuiz2Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz2
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_ElderQuiz2Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_ElderQuiz3::
	message DragonsDen_Shrine_Text_Question3
	multichoice 20, 6, MULTI_ELDERQUIIZ3, FALSE 
	switch VAR_RESULT
	case 1, DragonsDen_Shrine_EventScript_ElderQuiz3Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz3Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz3
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_ElderQuiz3Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_ElderQuiz4::
	message DragonsDen_Shrine_Text_Question4
	multichoice 20, 6, MULTI_ELDERQUIIZ4, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz4Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz4Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz4
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_ElderQuiz4Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_ElderQuiz5::
	message DragonsDen_Shrine_Text_Question5
	multichoice 20, 6, MULTI_ELDERQUIIZ5, FALSE 
	switch VAR_RESULT
	case 2, DragonsDen_Shrine_EventScript_ElderQuizFinish
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz5
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_ElderWrong::
	msgbox DragonsDen_Shrine_Text_WrongAnswer1, MSGBOX_DEFAULT
	addvar VAR_DRAGONS_DEN_QUIZ, 1
	return

DragonsDen_Shrine_EventScript_ElderQuizFinish::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	delay 20
	msgbox DragonsDen_Shrine_Text_PassedTest, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_ClairEnter


DragonsDen_Shrine_Text_ElderGreeting:
    .string "Hm… Good to see you here.\p"
    .string "No need to explain why you came.\n"
    .string "Clair sent you here, didn't she?\p"
    .string "That girl is a handful…\n"
    .string "I am sorry, but I must test you.\p"
    .string "Not to worry, you are to answer\n"
    .string "only a few questions.\l"
    .string "Ready?$"

DragonsDen_Shrine_Text_Question1:
    .string "What are Pokémon to you?$"

DragonsDen_Shrine_Text_Question2:
    .string "What helps you to win battles?$"

DragonsDen_Shrine_Text_Question3:
    .string "What kind of trainer do you wish\n"
    .string "to battle?$"

DragonsDen_Shrine_Text_Question4:
    .string "What is most important for\n"
    .string "raising Pokémon?$"

DragonsDen_Shrine_Text_Question5:
    .string "Strong Pokémon. Weak Pokémon.\n"
    .string "Which is more important?$"

DragonsDen_Shrine_Text_WrongAnswer1:
    .string "Hah? I didn't quite catch that…$"

DragonsDen_Shrine_Text_WrongAnswer2:
    .string "What was it you said?$"

DragonsDen_Shrine_Text_RightAnswer:
    .string "Oh, I understand…$"

DragonsDen_Shrine_Text_PassedTest:
    .string "Hm… I see…\p"
    .string "You care deeply for Pokémon.\p"
    .string "Very commendable.\p"
    .string "That conviction is what is\n"
    .string "important!\p"
    .string "{PLAYER}, don't lose that belief.\p"
    .string "It will see you through at the\n"
    .string "Pokémon League.$"

DragonsDen_Shrine_EventScript_ClairEnter::
	clearflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	addobject LOCALID_DRAGONSDEN3_CLAIR
	playse SE_DOOR
	delay 40
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	delay 20
	turnobject OBJ_EVENT_ID_FOLLOWER, DIR_SOUTH
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairEnter
	waitmovement 0
	turnobject LOCALID_DRAGONSDEN3_ELDER, DIR_WEST	
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	turnobject OBJ_EVENT_ID_FOLLOWER, DIR_NORTH
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_ClairYouPassed, MSGBOX_DEFAULT
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairBackup1
	waitmovement 0
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_ClairThatCantBe, MSGBOX_DEFAULT
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairBackup2
	waitmovement 0
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_ClairYoureLying, MSGBOX_DEFAULT
	removefieldmugshot
	applymovement LOCALID_DRAGONSDEN3_ELDER, DragonsDen_Shrine_Movement_ElderWalkToClair
	waitmovement 0
	turnobject LOCALID_DRAGONSDEN3_CLAIR, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_MustIInformLance, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_DRAGONSDEN3_CLAIR, Common_Movement_ExclamationMark
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_IUnderstand, MSGBOX_DEFAULT
	removefieldmugshot
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairReturnToPlayer
	waitmovement 0
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_HereRisingBadge, MSGBOX_DEFAULT
	removefieldmugshot
	message DragonsDen_Shrine_Text_PlayerReceivedRisingBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_RisingBadgeExplanation, MSGBOX_DEFAULT
	removefieldmugshot
	setflag FLAG_BADGE08_GET
	special Achievement_CheckAll
	setflag FLAG_DEFEATED_BLACKTHORN_GYM
	addvar VAR_NUM_BADGES, 1

	applymovement LOCALID_DRAGONSDEN3_ELDER, DragonsDen_Shrine_Movement_ElderReturnToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	turnobject LOCALID_DRAGONSDEN3_CLAIR, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_ElderScoldsClair, MSGBOX_DEFAULT
	closemessage
	delay 20
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_Speechless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairLeave
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	removeobject LOCALID_DRAGONSDEN3_CLAIR
	clearflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	setvar VAR_BLACKTHORN_CITY_STATE, 3
	release
	end

DragonsDen_Shrine_Movement_ClairEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

DragonsDen_Shrine_Movement_ClairBackup1:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ClairBackup2:
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ElderWalkToClair:
	walk_left
	walk_left
	walk_left
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairReturnToPlayer:
	walk_right
	walk_right
	step_end

DragonsDen_Shrine_Movement_ElderReturnToPlayer:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairLeave:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

DragonsDen_Shrine_Text_ClairYouPassed:
    .string "So how did it go?\p"
    .string "I guess there's no point\n"
	.string "in asking. You did fail?\p"
    .string "..................................\p"
    .string "…What? You passed?$"

DragonsDen_Shrine_Text_ClairThatCantBe:
    .string "That can't be!$"

DragonsDen_Shrine_Text_ClairYoureLying:
    .string "You're lying!\p"
    .string "Even I haven't been approved!$"

DragonsDen_Shrine_Text_MustIInformLance:
    .string "Clair!\p"
    .string "This child is impeccable,\n"
    .string "in skill and spirit!\p"
    .string "Admit defeat and confer the\n"
    .string "Risingbadge!\p"
    .string "…Or must I inform Lance of this?$"

DragonsDen_Shrine_Text_IUnderstand:
    .string "I-I understand…$"

DragonsDen_Shrine_Text_HereRisingBadge:
    .string "Here, this is the Risingbadge…\p"
    .string "Hurry up! Take it!$"

DragonsDen_Shrine_Text_PlayerReceivedRisingBadge:
    .string "{PLAYER} received Risingbadge.$"

DragonsDen_Shrine_Text_RisingBadgeExplanation:
    .string "Risingbadge will enable your\n"
    .string "Pokémon to use the move for\l"
    .string "climbing waterfalls.\p"
    .string "Also, all Pokémon will recognize\n"
    .string "you as a trainer and obey your\l"
    .string "every command without question.$"

DragonsDen_Shrine_Text_ElderScoldsClair:
    .string "Clair…\p"
    .string "Reflect upon what it is that you\n"
    .string "lack and this child has.$"

DragonsDen_Shrine_Text_Speechless:
    .string "..................................$"

DragonsDen_Shrine_Text_ComeAgain:
    .string "Come again, if you so desire.$"

DragonsDen_Shrine_Text_SilverIsInTraining:
    .string "A boy close to your age is in\n"
    .string "training here.\p"
    .string "He is much like Clair when she was\n"
    .string "younger. It is a little worrisome…$"

DragonsDen_Shrine_EventScript_Elder2::
	msgbox DragonsDen_Shrine_Text_Elder2, MSGBOX_NPC
	end

DragonsDen_Shrine_EventScript_Elder3::
	lock
	faceplayer
	msgbox DragonsDen_Shrine_Text_DracoMeteorTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DragonsDen_Shrine_EventScript_DracoMeteorDeclined
	msgbox DragonsDen_Shrine_Text_DracoMeteorWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DRACO_METEOR
	call MoveTutor_EventScript_OpenBox
	goto_if_eq VAR_RESULT, FALSE, DragonsDen_Shrine_EventScript_DracoMeteorDeclined
	goto DragonsDen_Shrine_EventScript_DracoMeteorTaught
	end

DragonsDen_Shrine_Text_Elder2:
    .string "It's been quite some time since a\n"
    .string "trainer has gained our Master's\l"
    .string "rare approval.\p"
    .string "In fact, not since Master Lance.$"

DragonsDen_Shrine_EventScript_DracoMeteorDeclined::
	msgbox DragonsDen_Shrine_Text_DracoMeteorDeclined, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_EventScript_DracoMeteorTaught::
	msgbox DragonsDen_Shrine_Text_DracoMeteorTaught, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Text_DracoMeteorTeach:
    .string "Only the strongest Dragon Pokémon\n"
    .string "can master Draco Meteor.\p"
    .string "Would you like me to teach it to\n"
    .string "one of your Pokémon?$"

DragonsDen_Shrine_Text_DracoMeteorWhichMon:
    .string "Which Pokémon should learn\n"
    .string "Draco Meteor?$"

DragonsDen_Shrine_Text_DracoMeteorDeclined:
    .string "Come back whenever you wish to\n"
    .string "master the ultimate Dragon move.$"

DragonsDen_Shrine_Text_DracoMeteorTaught:
    .string "May Draco Meteor serve you well.$"

DragonsDen_Shrine_EventScript_ElderChooseDratini::
	goto_if_eq VAR_DRAGONS_DEN_QUIZ, 0, DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini
	goto DragonsDen_Shrine_EventScript_ElderGiveBasicDratini

DragonsDen_Shrine_EventScript_ElderGiveBasicDratini::
	goto_if_set FLAG_GOT_DRATINI, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DRATINI
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	givemon SPECIES_DRATINI, 15, move1=MOVE_EXTREME_SPEED
	call Common_EventScript_GiftMon

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag FLAG_GOT_DRATINI
	release
	end

DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini::
	goto_if_set FLAG_GOT_DRATINI, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DRATINI
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	givemon SPECIES_DRATINI, 15, move1=MOVE_EXTREME_SPEED, move2=MOVE_SPACIAL_REND, shinyMode=SHINY_MODE_ALWAYS
	call Common_EventScript_GiftMon

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag FLAG_GOT_DRATINI
	release
	end

DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini::
	msgbox DragonsDen_Shrine_Text_ClairsGrandfather, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Text_TakeThisDratini:
    .string "Hm… Good to see you here.\p"
    .string "Your arrival is most fortunate.\p"
    .string "I have something for you.\p"
    .string "Take this Dratini as proof that I\n"
    .string "have recognized your worth.$"

DragonsDen_Shrine_Text_SymbolicDragon:
    .string "Dragon Pokémon are symbolic of our\n"
    .string "clan.\p"
    .string "You have shown that you can be\n"
    .string "entrusted with one.$"

DragonsDen_Shrine_Text_ClairsGrandfather:
    .string "Clair appears to have learned an\n"
    .string "invaluable lesson from you.\p"
    .string "I thank you as her grandfather.$"
