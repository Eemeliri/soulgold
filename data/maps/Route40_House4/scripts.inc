Route40_House4_MapScripts::
	.byte 0


AchievementGuy::
	lock
	faceplayer
	msgbox AchievementGuy_Text_0
	special GetCompletedAchievementsCount
	copyvar VAR_TEMP_0, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_TEMP_0
	compare VAR_ACHIEVEMENT_REWARD_MILESTONE, 15
	goto_if_lt AchievementGuy_3
AchievementGuy_1:
	compare VAR_ACHIEVEMENT_REWARD_MILESTONE, 30
	goto_if_lt AchievementGuy_8
AchievementGuy_6:
	compare VAR_ACHIEVEMENT_REWARD_MILESTONE, 45
	goto_if_lt AchievementGuy_13
AchievementGuy_11:
	compare VAR_ACHIEVEMENT_REWARD_MILESTONE, 60
	goto_if_lt AchievementGuy_18
AchievementGuy_16:
	compare VAR_ACHIEVEMENT_REWARD_MILESTONE, 75
	goto_if_lt AchievementGuy_23
AchievementGuy_21:
	compare VAR_ACHIEVEMENT_REWARD_MILESTONE, 100
	goto_if_lt AchievementGuy_28
AchievementGuy_26:
	compare VAR_TEMP_0, 100
	goto_if_ge AchievementGuy_32
	setvar VAR_TEMP_1, 15
	compare VAR_TEMP_0, 15
	goto_if_ge AchievementGuy_35
AchievementGuy_34:
	compare VAR_TEMP_0, 30
	goto_if_ge AchievementGuy_38
AchievementGuy_37:
	compare VAR_TEMP_0, 45
	goto_if_ge AchievementGuy_41
AchievementGuy_40:
	compare VAR_TEMP_0, 60
	goto_if_ge AchievementGuy_44
AchievementGuy_43:
	compare VAR_TEMP_0, 75
	goto_if_ge AchievementGuy_47
AchievementGuy_46:
	copyvar VAR_TEMP_2, VAR_TEMP_1
	subvar VAR_TEMP_2, VAR_TEMP_0
	buffernumberstring STR_VAR_2, VAR_TEMP_2
	msgbox AchievementGuy_Text_2
	release
	end

AchievementGuy_2:
	goto AchievementGuy_Reward15
	goto AchievementGuy_1

AchievementGuy_3:
	compare VAR_TEMP_0, 15
	goto_if_ge AchievementGuy_2
	goto AchievementGuy_1

AchievementGuy_7:
	goto AchievementGuy_Reward30
	goto AchievementGuy_6

AchievementGuy_8:
	compare VAR_TEMP_0, 30
	goto_if_ge AchievementGuy_7
	goto AchievementGuy_6

AchievementGuy_12:
	goto AchievementGuy_Reward45
	goto AchievementGuy_11

AchievementGuy_13:
	compare VAR_TEMP_0, 45
	goto_if_ge AchievementGuy_12
	goto AchievementGuy_11

AchievementGuy_17:
	goto AchievementGuy_Reward60
	goto AchievementGuy_16

AchievementGuy_18:
	compare VAR_TEMP_0, 60
	goto_if_ge AchievementGuy_17
	goto AchievementGuy_16

AchievementGuy_22:
	goto AchievementGuy_Reward75
	goto AchievementGuy_21

AchievementGuy_23:
	compare VAR_TEMP_0, 75
	goto_if_ge AchievementGuy_22
	goto AchievementGuy_21

AchievementGuy_27:
	goto AchievementGuy_Reward100
	goto AchievementGuy_26

AchievementGuy_28:
	compare VAR_TEMP_0, 100
	goto_if_ge AchievementGuy_27
	goto AchievementGuy_26

AchievementGuy_32:
	msgbox AchievementGuy_Text_1
	release
	end

AchievementGuy_35:
	setvar VAR_TEMP_1, 30
	goto AchievementGuy_34

AchievementGuy_38:
	setvar VAR_TEMP_1, 45
	goto AchievementGuy_37

AchievementGuy_41:
	setvar VAR_TEMP_1, 60
	goto AchievementGuy_40

AchievementGuy_44:
	setvar VAR_TEMP_1, 75
	goto AchievementGuy_43

AchievementGuy_47:
	setvar VAR_TEMP_1, 100
	goto AchievementGuy_46


keepUpTheGoodWork::
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox keepUpTheGoodWork_Text_0
	release
	end


AchievementGuy_Reward15::
	msgbox AchievementGuy_Reward15_Text_0
	giveitem ITEM_SHIN_GENOME
	setvar VAR_ACHIEVEMENT_REWARD_MILESTONE, 15
	goto keepUpTheGoodWork
	release
	end


AchievementGuy_Reward30::
	msgbox AchievementGuy_Reward30_Text_0
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_GRENINJA_BOND
	bufferspeciesname STR_VAR_1, SPECIES_GRENINJA_BOND
	givemon SPECIES_GRENINJA_BOND, 36
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setvar VAR_ACHIEVEMENT_REWARD_MILESTONE, 30
	goto keepUpTheGoodWork
	release
	end


AchievementGuy_Reward45::
	msgbox AchievementGuy_Reward45_Text_0
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_POIPOLE
	bufferspeciesname STR_VAR_1, SPECIES_POIPOLE
	givemon SPECIES_POIPOLE, 5
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setvar VAR_ACHIEVEMENT_REWARD_MILESTONE, 45
	goto keepUpTheGoodWork
	release
	end


AchievementGuy_Reward60::
	msgbox AchievementGuy_Reward60_Text_0
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_FLOETTE_ETERNAL
	bufferspeciesname STR_VAR_1, SPECIES_FLOETTE_ETERNAL
	givemon SPECIES_FLOETTE_ETERNAL, 30
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setvar VAR_ACHIEVEMENT_REWARD_MILESTONE, 60
	goto keepUpTheGoodWork
	release
	end


AchievementGuy_Reward75::
	msgbox AchievementGuy_Reward75_Text_0
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZARUDE
	bufferspeciesname STR_VAR_1, SPECIES_ZARUDE
	givemon SPECIES_ZARUDE, 50
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setvar VAR_ACHIEVEMENT_REWARD_MILESTONE, 75
	goto keepUpTheGoodWork
	release
	end


AchievementGuy_Reward100::
	msgbox AchievementGuy_Reward100_Text_0
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MAGEARNA_ORIGINAL
	bufferspeciesname STR_VAR_1, SPECIES_MAGEARNA_ORIGINAL
	givemon SPECIES_MAGEARNA_ORIGINAL, 80
	showgivemonpic 10, 3
	call Common_EventScript_GiftMon
	hidemonpic
	setvar VAR_ACHIEVEMENT_REWARD_MILESTONE, 100
	goto keepUpTheGoodWork
	release
	end


AchievementGuy_Text_0:
	.string "I've achieved many things in my life.\n"
	.string "Now, I want to see what the younger\l"
	.string "generation can do.\p"
	.string "Let me have a closer look at you...$"

AchievementGuy_Text_1:
	.string "You've achieved everything possible!\n"
	.string "There is nothing further I could bestow\l"
	.string "upon you, true master of Pokémon.$"

AchievementGuy_Text_2:
	.string "Hmm... \n"
	.string "You've achieved {STR_VAR_1} things \l"
	.string "so far!\p"
	.string "If you were to achieve {STR_VAR_2} more\n"
	.string "things, I might have something for you!$"

keepUpTheGoodWork_Text_0:
	.string "Never stop reaching for greater\n"
	.string "heights. I look forward to\l"
	.string "seeing what you will do next.$"

AchievementGuy_Reward15_Text_0:
	.string "Hmm! \p"
	.string "You have at least {STR_VAR_1} \n"
	.string "achievements under your belt! \p"
	.string "A great start! I will bestow you this\n"
	.string "as a reward!$"

AchievementGuy_Reward30_Text_0:
	.string "Excellent! \p"
	.string "You've achieved {STR_VAR_1}\n"
	.string "things and reached the next step\l"
	.string "on your journey! \p"
	.string "I have something nice for you!$"

AchievementGuy_Reward45_Text_0:
	.string "Superb! \p"
	.string "You've achieved {STR_VAR_1}\n"
	.string "things and reached the next\l"
	.string "milestone!\p"
	.string "I have something nice for you!$"

AchievementGuy_Reward60_Text_0:
	.string "Woah! You've achieved {STR_VAR_1}\n"
	.string "things and are known around\l"
	.string "the Johto!\p"
	.string "I have something for you\n"
	.string "to commemorate this achievement!$"

AchievementGuy_Reward75_Text_0:
	.string "Incredible! \p"
	.string "You've achieved {STR_VAR_1}\n"
	.string "things and reached the next\l"
	.string "milestone!\p"
	.string "Another reward just for you!$"

AchievementGuy_Reward100_Text_0:
	.string "Amazing! \p"
	.string "You've achieved {STR_VAR_1}\n"
	.string "things and reached my final\l"
	.string "milestone!\p"
	.string "These items are the only thing\n"
	.string "left to give. I have nothing\l"
	.string "further for you!$"
