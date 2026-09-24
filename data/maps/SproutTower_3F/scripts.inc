
SproutTower_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SproutTower_3F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

SproutTower_3F_OnTransition: 
	callnative SetTimeBasedEncounters
	end


SproutTower_3F_EventScript_SageJin::
	trainerbattle_single TRAINER_JIN SproutTower_Text_SageJin_Seen, SproutTower_Text_SageJin_Beaten
	msgbox SproutTower_Text_SageJin_AfterBattle, MSGBOX_AUTOCLOSE
	end


SproutTower_3F_EventScript_SageNeal::
	trainerbattle_single TRAINER_NEAL SproutTower_Text_SageNeal_Seen, SproutTower_Text_SageNeal_Beaten
	msgbox SproutTower_Text_SageNeal_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_SageTroy::
	trainerbattle_single TRAINER_TROY SproutTower_Text_SageTroy_Seen, SproutTower_Text_SageTroy_Beaten
	msgbox SproutTower_Text_SageTroy_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_Painting::
	lock
	msgbox SproutTower_Text_3F_Painting, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_3F_EventScript_TriggerSceneLeft::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_Silver1
	waitmovement 0
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SPROUT_TOWER_SILVER, Common_Movement_ExclamationMark	
	delay 60
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_SilverLeft
	waitmovement 0
	createfieldmugshot MUGSHOT_SILVER
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	delay 30
	removefieldmugshot
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement LOCALID_SPROUT_TOWER_SILVER SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_SPROUT_TOWER_SILVER
	removeobject LOCALID_SPROUT_TOWER_SILVER
	delay 55
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	delay 15
	setvar VAR_SPROUT_TOWER, 1
	fadedefaultbgm
	release
	end

SproutTower_3F_EventScript_TriggerSceneRight::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_Silver1
	waitmovement 0
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SPROUT_TOWER_SILVER, Common_Movement_ExclamationMark	
	delay 60
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_SilverRight
	waitmovement 0
	waitmovement 0
	createfieldmugshot MUGSHOT_SILVER
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	removefieldmugshot
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement LOCALID_SPROUT_TOWER_SILVER SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_SPROUT_TOWER_SILVER
	removeobject LOCALID_SPROUT_TOWER_SILVER
	savebgm MUS_DUMMY
	fadedefaultbgm
	delay 55
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	delay 15
	setvar VAR_SPROUT_TOWER, 1
	release
	end

SproutTower_3F_EventScript_SageLi::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, SproutTower_3F_EventScript_SageLi_Beaten
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SproutTower_Text_SageLi_Seen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_LI, SproutTower_Text_SageLi_Beaten
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SproutTower_Text_SageLi_TakeFlash, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SproutTower_Text_SageLi_FlashExplain, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_EventScript_SageLi_Beaten::
	goto_if_set FLAG_BADGE08_GET, SageLiPostBadges
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SproutTower_Text_SageLi_AfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_Movement_Silver1:
	walk_fast_up
	walk_fast_up
	step_end

SproutTower_3F_Movement_SilverLeft:
	face_down
	delay_16
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_SilverRight:
	face_down
	delay_16
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_EscapeRope:
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	step_end

SproutTower_Text_ElderLecturesRival:
	.string "Elder: You are indeed skilled\n"
	.string "as a trainer.\p"
	.string "As promised, here is your HM.\p"
	.string "But let me say this: You should\n"
	.string "treat your Pokémon better.\p"
	.string "The way you battle is far too\n"
	.string "harsh.\p"
	.string "Pokémon are not tools of war…$"

SproutTower_Text_RivalOnlyCaresStrong:
	.string "…\n"
	.string "…Humph!\p"
	.string "He claims to be the Elder but\n"
	.string "he's weak.\p"
	.string "It stands to reason.\p"
	.string "I'd never lose to fools who babble\n"
	.string "about being nice to Pokémon.\p"
	.string "I only care about strong\n"
	.string "Pokémon that can win.\p"
	.string "I really couldn't care less\n"
	.string "about weak Pokémon.$"

SproutTower_Text_RivalUsedEscapeRope:
	.string "{RIVAL} used an Escape Rope!$"

SproutTower_Text_SageLi_Seen:
	.string "So good of you to come here!\p"
	.string "Sprout Tower is a place of\n"
	.string "training.\p"
	.string "People and Pokémon test their\n"
	.string "bonds to build a bright future\l"
	.string "together.\p"
	.string "I am the final test.\p"
	.string "Allow me to check the ties\n"
	.string "between your Pokémon and you!$"

SproutTower_Text_SageLi_Beaten:
	.string "Ah, excellent!$"

SproutTower_Text_SageLi_TakeFlash:
	.string "You and your Pokémon should\n"
	.string "have no problem using this move.\p"
	.string "Take this Flash HM.$"

SproutTower_Text_SageLi_FlashExplain:
	.string "Flash illuminates even the\n"
	.string "darkest of all places.\p"
	.string "But to use it out of battle, you\n"
	.string "need the Badge from Violet's Gym.$"

SproutTower_Text_SageLi_AfterBattle:
	.string "I hope you learn and grow from\n"
	.string "your journey.$"

SproutTower_Text_SageJin_Seen:
	.string "I train to find enlightenment\n"
	.string "in Pokémon!$"

SproutTower_Text_SageJin_Beaten:
	.string "My training is incomplete…$"

SproutTower_Text_SageJin_AfterBattle:
	.string "As Pokémon grow stronger,\n"
	.string "so does the trainer.\p"
	.string "No, wait. As the trainer\n"
	.string "grows stronger, so do the\l"
	.string "Pokémon.$"

SproutTower_Text_SageTroy_Seen:
	.string "Let me see how much you trust\n"
	.string "your Pokémon.$"

SproutTower_Text_SageTroy_Beaten:
	.string "Yes, your trust is real!$"

SproutTower_Text_SageTroy_AfterBattle:
	.string "It is not far to the Elder.$"

SproutTower_Text_SageNeal_Seen:
	.string "The Elder's HM lights even\n"
	.string "pitch-black darkness.$"

SproutTower_Text_SageNeal_Beaten:
	.string "It is my head that is bright!$"

SproutTower_Text_SageNeal_AfterBattle:
	.string "Let there be light on your\n"
	.string "journey.$"

SproutTower_Text_3F_Painting:
	.string "It's a powerful painting of a\n"
	.string "Bellsprout.$"

SageLiPostBadges::
	goto_if_unset FLAG_HIDE_SPROUT_BASEMENT_GUARD, SageLiPostBadges_2
	msgbox SageLiPostBadges_Text_4
SageLiPostBadges_1:
	release
	end

SageLiPostBadges_2:
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SageLiPostBadges_Text_0
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, FALSE
	msgbox SageLiPostBadges_Text_1
	trainerbattle_no_intro TRAINER_LI_2, SageLiPostBadges_Text_2
	createfieldmugshot MUGSHOT_ELDER_LI
	msgbox SageLiPostBadges_Text_3
	msgbox SageLiPostBadges_Text_4
	setflag FLAG_HIDE_SPROUT_BASEMENT_GUARD
	goto SageLiPostBadges_1


SageLiPostBadges_Text_0:
	.string "{PLAYER}!\p"
	.string "I have heard of your triumphs across\n"
	.string "Johto!\p"
	.string "I am overjoyed to see how far the bonds\n"
	.string "between Trainers and Pokémon can go.\p"
	.string "To that end, I would like to test you\n"
	.string "once again. \p"
	.string "This time I won't be holding back.$"

SageLiPostBadges_Text_1:
	.string "Prepare yourself!$"

SageLiPostBadges_Text_2:
	.string "Future generations shine brighter than\n"
	.string "ever! Walk this path, young Trainer.$"

SageLiPostBadges_Text_3:
	.string "A marvelous display of skill!\p"
	.string "I believe the borders of Johto won't\n"
	.string "be enough for you at your current pace.\p"
	.string "I will allow you access to this tower's\n"
	.string "basement floor.\p"
	.string "A strong Pokémon resides there.\p"
	.string "Guarding it has been one of our\n"
	.string "tasks for a very long time.$"

SageLiPostBadges_Text_4:
	.string "I look forward to hearing where your\n"
	.string "journey next takes you.$"
