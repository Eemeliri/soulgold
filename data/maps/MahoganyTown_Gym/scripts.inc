
MahoganyTown_Gym_MapScripts::
	.byte 0


MahoganyTown_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM,  MahoganyTown_Gym_EventScript_Statue2
	msgbox MahoganyTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_Statue2::
	msgbox MahoganyTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_GymStatue:
	.string "Mahogany Town Pokémon Gym$"

MahoganyTown_Gym_Text_GymStatueCertified:
	.string "Mahogany Town Pokémon Gym\p"
	.string "Pryce's Certified Trainers:\n"
	.string "{PLAYER}$"


MahoganyTown_GymEventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_GymGuy2
	msgbox MahoganyTown_Gym_Text_Guide, MSGBOX_DEFAULT
	closemessage
	release
	end
	
MahoganyTown_Gym_EventScript_GymGuy2::
	msgbox MahoganyTown_Gym_Text_GuideWin, MSGBOX_DEFAULT
	release
	end	

MahoganyTown_Gym_EventScript_Ronald::
	trainerbattle_single TRAINER_RONALD MahoganyTown_Gym_Text_BoarderRonaldSeen, MahoganyTown_Gym_Text_BoarderRonaldBeaten
	msgbox MahoganyTown_Gym_Text_BoarderRonaldAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Brad::
	trainerbattle_single TRAINER_BRAD MahoganyTown_Gym_Text_BoarderBradSeen, MahoganyTown_Gym_Text_BoarderBradBeaten
	msgbox MahoganyTown_Gym_Text_BoarderBradAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Douglas::
	trainerbattle_single TRAINER_DOUGLAS MahoganyTown_Gym_Text_BoarderDouglasSeen, MahoganyTown_Gym_Text_BoarderDouglasBeaten
	msgbox MahoganyTown_Gym_Text_BoarderDouglasAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE MahoganyTown_Gym_Text_SkierRoxanneSeen, MahoganyTown_Gym_Text_SkierRoxanneBeaten
	msgbox MahoganyTown_Gym_Text_SkierRoxanneAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Clarissa::
	trainerbattle_single TRAINER_CLARISSA MahoganyTown_Gym_Text_SkierClarissaSeen, MahoganyTown_Gym_Text_SkierClarissaBeaten
	msgbox MahoganyTown_Gym_Text_SkierClarissaAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Pryce::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_Pryce_Defeated
	msgbox MahoganyTown_Gym_Text_PryceIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_OlivineCheckCianwood
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_CianwoodCheckOlivine
	goto MahoganyTown_Gym_EventScript_Pryce_Battle1

MahoganyTown_Gym_EventScript_PryceVictory::
	message MahoganyTown_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MahoganyTown_Gym_Text_GlacierBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE07_GET
    setflag FLAG_SOUTHPASSAGE_ARIANA
	special Achievement_CheckAll
	setflag FLAG_DEFEATED_MAHOGANY_TOWN_GYM
    addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	giveitem ITEM_TM_HAIL
	msgbox MahoganyTown_Gym_Text_HailSpeech, MSGBOX_DEFAULT
	setvar VAR_MAHOGANY_TOWN_STATE, 15
    setrespawn HEAL_LOCATION_MAHOGANYTOWN
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_OlivineCheckCianwood::
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2

MahoganyTown_Gym_EventScript_CianwoodCheckOlivine::
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2
	
MahoganyTown_Gym_EventScript_Pryce_Battle1::
	trainerbattle_no_intro TRAINER_PRYCE_1, MahoganyTown_Gym_Text_PryceImpressed
    setflag FLAG_RECEIVED_BADGE_5
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle2::
	trainerbattle_no_intro TRAINER_PRYCE_1_2, MahoganyTown_Gym_Text_PryceImpressed
    setflag FLAG_RECEIVED_BADGE_6
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle3::
	trainerbattle_no_intro TRAINER_PRYCE_1_3, MahoganyTown_Gym_Text_PryceImpressed
    setflag FLAG_RECEIVED_BADGE_7
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Defeated::
	msgbox MahoganyTown_Gym_Text_CherishPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_PryceIntro:
    .string "Pokémon have many experiences\n"
    .string "in their lives, just like we do.\p"
    .string "I, too, have seen and suffered\n"
    .string "much in my life.\p"
    .string "Since I am your elder, let me\n"
    .string "show you what I mean.\p"
    .string "I have been with Pokémon since\n"
    .string "before you were born.\p"
    .string "I do not lose easily.\p"
    .string "I, Pryce--the winter trainer--\n"
    .string "shall demonstrate my power!$"

MahoganyTown_Gym_Text_PryceImpressed:
    .string "Ah, I am impressed by your\n"
    .string "prowess.\p"
    .string "With your strong will, I know you\n"
    .string "will overcome all life's obstacles.\p"
    .string "You are worthy of this Badge!$"

MahoganyTown_Gym_Text_ReceivedBadge:
    .string "{PLAYER} received Glacierbadge.$"

MahoganyTown_Gym_Text_GlacierBadgeSpeech:
    .string "That Badge lets your Pokémon use\n"
    .string "Whirlpool to get across\l"
    .string "real whirlpools.\p"
    .string "And this… This is a gift from me!$"

MahoganyTown_Gym_Text_HailSpeech:
    .string "That TM contains Hail.\p"
    .string "It inflicts damage every\n"
    .string "turn for 5 turns.\p"
    .string "It demonstrates the harshness\n"
    .string "of winter.$"

MahoganyTown_Gym_Text_CherishPokemon:
    .string "When the ice and snow melt,\n"
    .string "spring arrives.\p"
    .string "You and your Pokémon will be\n"
    .string "together for many years to come.\p"
    .string "Cherish your time together!$"

MahoganyTown_Gym_Text_PryceRematch:
    .string "Ah, Johto Champion!\p"
    .string "Your skills are indeed\n"
    .string "remarkable.\p"
    .string "I am impressed.\p"
    .string "But even now, there is much to\n"
    .string "learn from each other.\p"
    .string "I, Pryce--the winter trainer--\n"
    .string "still have a few tricks left.\p"
    .string "Want to have a rematch with me?$"

MahoganyTown_Gym_Text_PryceRematchDefeat:
    .string "Ah, yet again I'm impressed by\n"
    .string "your prowess.\p"
    .string "With your strong will, I know you\n"
    .string "will overcome all life's obstacles.$"

MahoganyTown_Gym_Text_Guide:
    .string "Pryce is a veteran who has\n"
    .string "trained Pokémon for some 50 years.\p"
    .string "He's got a solid lineup of\n"
    .string "Pokémon to cover whatever\l"
    .string "you bring his way.\p"
    .string "Fire is a good place to start,\n"
    .string "but watch out for the rain!$"

MahoganyTown_Gym_Text_GuideWin:
    .string "Pryce is something, but you're\n"
    .string "something else!\p"
    .string "That was a hot battle that\n"
    .string "bridged the generation gap!$"

MahoganyTown_Gym_Text_BoarderRonaldSeen:
    .string "I'll freeze your Pokémon,\n"
    .string "so you can't do a thing!$"

MahoganyTown_Gym_Text_BoarderRonaldBeaten:
    .string "Darn. I couldn't do a thing.$"

MahoganyTown_Gym_Text_BoarderRonaldAfter:
    .string "I think there's a move a\n"
    .string "Pokémon can use while it's\l"
    .string "frozen.$"

MahoganyTown_Gym_Text_BoarderBradSeen:
    .string "This Gym has a slippery floor.\p"
    .string "It's fun, isn't it?\p"
    .string "But hey--we're not playing\n"
    .string "games here!$"

MahoganyTown_Gym_Text_BoarderBradBeaten:
    .string "Do you see how serious we are?$"

MahoganyTown_Gym_Text_BoarderBradAfter:
    .string "This Gym is great.\n"
    .string "I love boarding with my\l"
    .string "Pokémon!$"

MahoganyTown_Gym_Text_BoarderDouglasSeen:
    .string "I know Pryce's secret.$"

MahoganyTown_Gym_Text_BoarderDouglasBeaten:
    .string "Ok. I'll tell you Pryce's secret.$"

MahoganyTown_Gym_Text_BoarderDouglasAfter:
    .string "The secret behind Pryce's power…\p"
    .string "He meditates under a waterfall\n"
    .string "daily to strengthen his mind\l"
    .string "and body.$"

MahoganyTown_Gym_Text_SkierRoxanneSeen:
    .string "To get to Pryce, our Gym Leader,\n"
    .string "you need to think before you skate.$"

MahoganyTown_Gym_Text_SkierRoxanneBeaten:
    .string "I wouldn't lose to you in skiing!$"

MahoganyTown_Gym_Text_SkierRoxanneAfter:
    .string "If you don't skate with precision,\n"
    .string "you won't get far in this Gym.$"

MahoganyTown_Gym_Text_SkierClarissaSeen:
    .string "Check out my parallel turn!$"

MahoganyTown_Gym_Text_SkierClarissaBeaten:
    .string "No! You made me wipe out!$"

MahoganyTown_Gym_Text_SkierClarissaAfter:
    .string "I shouldn't have been bragging\n"
    .string "about my skiing…$"

MahoganyTown_Gym_EventScript_Froslass::
	playmoncry SPECIES_FROSLASS, CRY_MODE_NORMAL
	msgbox MahoganyTown_Gym_EventScript_Froslass_Text_0, MSGBOX_NPC
	return


MahoganyTown_Gym_EventScript_Froslass_Text_0:
	.string "Fross!!$"
