
MtSilver_SummitDay_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_SummitDay_OnTransition
	.byte 0

MtSilver_SummitDay_OnFrame::
	map_script_2 VAR_TEMP_0, 0 MtSilver_SummitDay_Blizzard
	.2byte 0

MtSilver_SummitDay_Blizzard::
	playse SE_M_BLIZZARD
	setvar VAR_TEMP_0, 1
	end

MtSilver_SummitDay_OnTransition:
    call Common_EventScript_SetupRivalGfxId
	call_if_set FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetDay
	end


MtSilver_SummitDay_OnTransition_SetLayout:
	call_if_set FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetDay
	end

MtSilver_SummitDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_NIGHT
	return

MtSilver_SummitDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_DAY
	return

MtSilver_SummitDay_EventScript_Rival::
	lock
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_0
	delay 30
	faceplayer
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_1
	closemessage
	applymovement LOCALID_MTSILVER_RIVAL, MtSilver_SummitDay_EventScript_Rival_Movement_0
	waitmovement 0
	delay 30
	faceplayer
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_2
	removefieldmugshot
	closemessage
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq MtSilver_SummitDay_EventScript_Rival_2
	trainerbattle_no_intro TRAINER_RIVAL_GOLD_FINAL, MtSilver_SummitDay_EventScript_Rival_Text_3
MtSilver_SummitDay_EventScript_Rival_1:
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN
	createfieldmugshotrival
	delay 30
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_4
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_5
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_6
	playfanfare MUS_OBTAIN_ITEM
	removefieldmugshot
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_7
	waitfanfare
	giveegg SPECIES_JIRACHI
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_8
	removefieldmugshot
	closemessage
	fadescreenspeed FADE_TO_BLACK, 24
	setflag FLAG_HIDE_MTSILVER_RIVAL
	removeobject LOCALID_MTSILVER_RIVAL
	setflag FLAG_DEFEATED_MTSILVER_RIVAL
	setvar VAR_RIVAL_STATE, 12
	clearflag FLAG_HIDE_NEWBARK_RIVAL
	clearflag FLAG_HIDE_RIVAL_AZUMARILL
	setflag FLAG_HIDE_RIVAL_MARILL
	delay 40
	warp MAP_NEW_BARK_TOWN_HOUSE3, 33, 3
	waitstate
	releaseall
	end

MtSilver_SummitDay_EventScript_Rival_2:
	trainerbattle_no_intro TRAINER_RIVAL_CRYSTAL_FINAL, MtSilver_SummitDay_EventScript_Rival_Text_3
	goto MtSilver_SummitDay_EventScript_Rival_1


MtSilver_SummitDay_EventScript_Rival_Movement_0:
	walk_in_place_up
	step_end

MtSilver_SummitDay_EventScript_Rival_Text_0:
	.string "I knew you'd come here.$"

MtSilver_SummitDay_EventScript_Rival_Text_1:
	.string "I've been up here thinking.\n"
	.string "Not much else to do.\p"
	.string "I kept telling myself,\n"
	.string "one more badge. One more win.\p"
	.string "Then I would finally catch up.\p"
	.string "Silly isn't it? In the end I was\n"
	.string "just trying to stand out.\p"
	.string "Assuming everyone had some sort of\n"
	.string "expectation of me to reach these \l"
	.string "heights and become the best.$"

MtSilver_SummitDay_EventScript_Rival_Text_2:
	.string "In the end it was just all in my head\n"
	.string "when you get down to it, haha.\p"
	.string "So! I want you, {PLAYER} to give me\n"
	.string "one last battle to knock some sense\l"
	.string "into me!\p"
	.string "Not asking as a bitter rival, \n"
	.string "but as your best friend!\p"
	.string "I got nothing to prove, but let's\n"
	.string "have fun like we used to.$"

MtSilver_SummitDay_EventScript_Rival_Text_3:
	.string "Hah, nice one.$"

MtSilver_SummitDay_EventScript_Rival_Text_4:
	.string "Okay.\n"
	.string "That's what I needed.$"

MtSilver_SummitDay_EventScript_Rival_Text_5:
	.string "You always do the battling\n"
	.string "with a smile, I felt that too\l"
	.string "in this battle.$"

MtSilver_SummitDay_EventScript_Rival_Text_6:
	.string "When I was just standing here alone, I\n"
	.string "was wishing you could arrive.\p"
	.string "then, I saw this egg in the ground\n"
	.string "here. \p"
	.string "I think it appeared in reaction to my\n"
	.string "wish, but you should have it instead.\p"
	.string "After all, you made my wish come true!\p"
	.string "So, thanks {PLAYER}.$"

MtSilver_SummitDay_EventScript_Rival_Text_7:
	.string "{PLAYER} received an Egg!$"

MtSilver_SummitDay_EventScript_Rival_Text_8:
	.string "Now c'mon, let's race back home!\p"
	.string "My fingers are freezing from just \n"
	.string "standing around here.$"
