
.set LOCALID_DRAGONSDEN2_CLAIR, 5
.set LOCALID_DEN_CLAIR, 35

DragonsDen_Cavern_MapScripts::
	@map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonsDen_Cavern_OnFrame
	.byte 0

DragonsDen_Cavern_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 3, DragonsDen_Cavern_EventScript_Clair
	.2byte 0

DragonsDen_EventScript_ClairRematch::
    lock
    faceplayer
    msgbox DragonsDen_Text_Clair, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_DEN_CLAIR
    removeobject LOCALID_DEN_CLAIR
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_CLAIR
    release
    end

DragonsDen_Text_Clair:
    .string "{PLAYER}… So you're here.\p"
	.string "If you think you can keep up,\n"
	.string "with me, come to the Fighting\l"
	.string "Dojo in Saffron.$"



DragonsDen_Cavern_Trigger_ClairMid::
	lock 
	playse SE_PIN
	applymovement LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 60
	approachobject LOCALID_DRAGONSDEN2_CLAIR, LOCALID_PLAYER, DIR_EAST, DIR_WEST
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_WEST
	call DragonsDen_Cavern_EventScript_Clair
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	delay 45
	fadescreen FADE_FROM_BLACK
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	release
	end

DragonsDen_Cavern_EventScript_Clair::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Cavern_Text_ClairGiveDragonclaw, MSGBOX_DEFAULT
	giveitem ITEM_TM_DRAGON_CLAW
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Cavern_Text_ClairDescribeDragonclaw, MSGBOX_DEFAULT
	closemessage
	delay 30
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Cavern_Text_ClairWhatsTheMatter, MSGBOX_DEFAULT
	closemessage
	delay 10
	clearflag FLAG_GOT_DRATINI
	return

DragonsDen_Cavern_Movement_ClairLeaveLeft:
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveMid:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveRight:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Text_ClairGiveDragonclaw:
    .string "Clair: Wait!\p"
	.string "I'm sorry about this.\n"
    .string "Here, take this as my apology.$"

DragonsDen_Cavern_Text_ClairDescribeDragonclaw:
    .string "That contains Dragon Claw.\p"
    .string "No, it doesn't have anything to\n"
    .string "do with my nails.\p"
    .string "If you don't want it, you don't\n"
    .string "have to take it.$"

DragonsDen_Cavern_Text_ClairWhatsTheMatter:
    .string "What's the matter? Aren't\n"
    .string "you going on to the Pokémon\l"
    .string "League?\p"
    .string "After you become Champion, you\n"
    .string "can rematch any Gym Leader you\l"
    .string "want.\p"
    .string "Go to the Pokémon League.\p"
    .string "Do you know how to get there?\p"
    .string "From here, go to New Bark Town.\p"
    .string "Then Surf east to Pokémon League.\p"
    .string "The route there is very tough.\p"
    .string "Don't you dare lose at the Pokémon\n"
    .string "League!\p"
    .string "If you do, I'll feel even worse\n"
    .string "about having lost to you!\p"
    .string "Give it everything you've got.$"

DragonsDen_Cavern_EventScript_Darin::
	trainerbattle_single TRAINER_DARIN DragonsDen_Cavern_Text_CooltrainermDarinSeen, DragonsDen_Cavern_Text_CooltrainermDarinBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainermDarinAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_Cara::
	trainerbattle_single TRAINER_CARA DragonsDen_Cavern_Text_CooltrainerfCaraSeen, DragonsDen_Cavern_Text_CooltrainerfCaraBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainerfCaraAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_TwinLea::
	trainerbattle_double TRAINER_LEA_AND_PIA, DragonsDen_Cavern_Text_TwinsLeaandPia1Seen, DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia1After, MSGBOX_DEFAULT
	release
	end
	
DragonsDen_Cavern_EventScript_TwinPia::
	trainerbattle_double TRAINER_LEA_AND_PIA, DragonsDen_Cavern_Text_TwinsLeaandPia2Seen, DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia2After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_Text_DragonShrineSign:
    .string "Dragon Shrine\p"
    .string "A shrine honoring the dragon\n"
    .string "Pokémon\p"
    .string "said to have lived in Dragon's\n"
    .string "Den.$"

DragonsDen_Cavern_Text_SilverTraining1:
    .string "…\n"
    .string "What? {PLAYER}?\p"
    .string "…No, I won't battle you now…\p"
    .string "My Pokémon aren't ready to beat\n"
    .string "you.\p"
    .string "I can't push them too hard now.\p"
    .string "I have to be disciplined to become\n"
    .string "the greatest Pokémon trainer…$"

DragonsDen_Cavern_Text_SilverTraining2:
    .string "…\p"
    .string "Whew…\p"
    .string "Learn to stay out of my way…$"

DragonsDen_Cavern_Text_CooltrainermDarinSeen:
    .string "You! How dare you enter\n"
    .string "uninvited!$"

DragonsDen_Cavern_Text_CooltrainermDarinBeaten:
    .string "S-strong!$"

DragonsDen_Cavern_Text_CooltrainermDarinAfter:
    .string "The Shrine ahead is home to the\n"
    .string "Master of our dragon-user clan.\p"
    .string "You're not allowed to just go in!$"

DragonsDen_Cavern_Text_CooltrainerfCaraSeen:
    .string "You shouldn't be in here!$"

DragonsDen_Cavern_Text_CooltrainerfCaraBeaten:
    .string "Oh yikes, I lost!$"

DragonsDen_Cavern_Text_CooltrainerfCaraAfter:
    .string "Soon I'm going to get permission\n"
    .string "from our Master to use dragons.\p"
    .string "When I do, I'm going to become an\n"
    .string "admirable dragon trainer and gain\l"
    .string "our Master's approval.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Seen:
    .string "It's a stranger we don't know.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten:
    .string "Ouchies.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1After:
    .string "It was like having to battle\n"
    .string "Lance.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Seen:
    .string "Who are you?$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten:
    .string "Meanie.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2After:
    .string "We'll tell on you.\p"
    .string "Master will be angry with you.$"

DragonsDen_ClairRematch::
	lock
	faceplayer
	msgbox DragonsDen_ClairRematch_Text_0
	msgbox DragonsDen_ClairRematch_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, TRUE
	goto_if_eq DragonsDen_ClairRematch_2
DragonsDen_ClairRematch_1:
	release
	end

DragonsDen_ClairRematch_2:
	trainerbattle_no_intro TRAINER_CLAIR_2, DragonsDen_ClairRematch_Text_2
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_ClairRematch_Text_3
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_DEN_CLAIR
	setflag FLAG_CLAIR_ON_TRIP
	removeobject LOCALID_CLAIR_REMATCH
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	goto DragonsDen_ClairRematch_1


DragonsDen_ClairRematch_Text_0:
	.string "Hey {PLAYER}.\n"
	.string "I heard from Lance that you became the\l"
	.string "new Champion. I guess the elders were\l"
	.string "right, I was just blinded by my own ego.\l"
	.string "Sorry.$"

DragonsDen_ClairRematch_Text_1:
	.string "Could we have another match right\n"
	.string "here? I'd like to fight the new\l"
	.string "Champion without anything holding\l"
	.string "us back.$"

DragonsDen_ClairRematch_Text_2:
	.string "Crazy how much stronger you can grow\n"
	.string "in such a short amount of time.$"

DragonsDen_ClairRematch_Text_3:
	.string "I've got a long way to go still if I want\n"
	.string "to surpass you or even Lance. I think\l"
	.string "I will leave for a trip soon. Go see\l"
	.string "places and hopefully learn from all\l"
	.string "kinds of people. Then I will face you\l"
	.string "again with all I've learned. Thank you\l"
	.string "for this lesson in battle. I won't\l"
	.string "forget it.$"
