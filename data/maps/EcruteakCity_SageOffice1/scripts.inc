.set LOCALID_SAGEOFFICE_SAGE, 3

EcruteakCity_SageOffice1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_SageOffice1_OnTransition
	.byte 0

EcruteakCity_SageOffice1_OnTransition::
	goto_if_set FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice1_EventScript_SageAside
	end

EcruteakCity_SageOffice1_EventScript_SageAside::
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	end

EcruteakCity_SageOffice1_EventScript_Sign::
	msgbox EcruteakCity_SageOffice1_Text_Sign, MSGBOX_SIGN
	end

EcruteakCity_SageOffice1_Text_Sign:
	.string "The bell of tin rings clearly for\n"
	.string "those under the tower's wing.$"

EcruteakCity_SageOffice2_EventScript_SageA::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice2_EventScript_SageA4
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_SageOffice2_EventScript_SageA2
	msgbox EcruteakTinTowerEntrance_Text_SageNoBadge, MSGBOX_DEFAULT
	checkitem ITEM_RAINBOW_WING
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_SageOffice2_EventScript_SageARecallDirector
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageARecallDirector::
	msgbox EcruteakTinTowerEntrance_Text_RecallDirector, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA2::
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell1, MSGBOX_DEFAULT
	waitmessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_SAGEOFFICE_SAGE, Common_Movement_ExclamationMark
	delay 60
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SAGEOFFICE_SAGE, EcruteakCity_SageOffice2_Movement_StandAside
	waitmovement 0
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	setflag FLAG_HIDE_TINTOWER_GUARD
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA3::
	msgbox EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA4::
	msgbox EcruteakTinTowerEntrance_Text_SageDone, MSGBOX_DEFAULT
	closemessage
	release
	end
	
EcruteakCity_SageOffice2_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 10, EcruteakCity_SageOffice2_EventScript_B2
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, EcruteakCity_SageOffice2_EventScript_B2
	msgbox EcruteakTinTowerEntrance_Text_WanderingSage, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_B2::
	msgbox EcruteakTinTowerEntrance_Text_WanderingSageClearBell, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageC::
	lock
	faceplayer
	msgbox EcruteakTinTowerEntrance_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_Movement_StandAside:
	walk_left
	face_down
	step_end

EcruteakTinTowerEntrance_Text_SageNoBadge:
	.string "Tin Tower is off limits to the\n"
	.string "unworthy. Sorry but you'll have\l"
	.string "to leave.$"

EcruteakTinTowerEntrance_Text_RecallDirector:
	.string "You recall the Radio Tower\n"
	.string "Director's words...\p"
	.string "“The legendary Pokémon will not\n"
	.string "appear if you just go to the place\l"
	.string "I mentioned.\p"
	.string "Apparently there is something else\n"
	.string "you need...”\p"
	.string "Perhaps you should return here later.$"

EcruteakTinTowerEntrance_Text_SageWithBadge:
	.string "Tin Tower is off limits to anyone\n"
	.string "without Ecruteak Gym's Badge.\p"
	.string "Ah!\p"
	.string "Ecruteak's Gym Badge! Please, go\n"
	.string "right through.$"

EcruteakTinTowerEntrance_Text_SageNoClearBell:
	.string "A momentous event has occurred.\p"
	.string "I beg your pardon, but I must ask\n"
	.string "you to leave.\p"
	.string "…What soothes the soul…\p"
	.string "The Wise Trio say things that are\n"
	.string "so very difficult to understand…$"

EcruteakTinTowerEntrance_Text_SageHearsClearBell1:
	.string "A momentous event has occurred.\p"
	.string "I beg your pardon, but I must ask\n"
	.string "you to leave.\p"
	.string "..............................$"
EcruteakTinTowerEntrance_Text_SageHearsClearBell2:
	.string "Ah!\p"
	.string "The sound of that Clear Bell!\p"
	.string "It… It's sublime!\p"
	.string "I've never heard so beautiful a\n"
	.string "sound before!\p"
	.string "That bell's chime is indicative of\n"
	.string "the bearer's soul.\p"
	.string "You…\p"
	.string "You may be able to make it through\n"
	.string "Tin Tower.\p"
	.string "Please, do go on.$"

EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn:
	.string "Please, do go on.$"

EcruteakTinTowerEntrance_Text_SageDone:
	.string "That bell's chime is indicative of\n"
	.string "the bearer's soul.\p"
	.string "You…\n"
	.string "Truly are worthy.$"

EcruteakTinTowerEntrance_Text_WanderingSage:
	.string "The Tin Tower ahead is a nine-\n"
	.string "tier tower of divine beauty.\p"
	.string "It soothes the soul of all who\n"
	.string "see it.$"

EcruteakTinTowerEntrance_Text_WanderingSageClearBell:
	.string "The Tin Tower shook! A Pokémon must\n"
	.string "have returned to the top!$"

EcruteakTinTowerEntrance_Text_Gramps:
	.string "Two towers… Two Pokémon…\p"
	.string "But when one burned down, both\n"
	.string "Pokémon flew away, never to return.$"
