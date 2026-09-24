
Route29_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route29_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route29_Trigger_Monview::
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1 
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	special RemoveCameraObject
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	end

Route29_Text_PressAorB:
	.string "Press A or B to stop viewing.$"

Route29_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route29_EventScript_OldMan2
	msgbox Route29_Text_OldMan1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan2::
	msgbox Route29_Text_OldMan2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route29_EventScript_OldMan_Tutorial
	waitmessage
	msgbox Route29_Text_OldManDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan_Tutorial::
	msgbox Route29_Text_OldManExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Lass::
	lock
	faceplayer
	msgbox Route29_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route29_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end


Route29_EventScript_Tuscany::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SILK_SCARF, Route29_EventScript_TuscanyCompleted
	msgbox Route29_Text_MeetTuscany, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route29_EventScript_TuscanyNope
	case 1, Route29_EventScript_TuscanyNope
	case 2, Route29_EventScript_TuscanyYes
	case 3, Route29_EventScript_TuscanyNope
	case 4, Route29_EventScript_TuscanyNope
	case 5, Route29_EventScript_TuscanyNope
	case 6, Route29_EventScript_TuscanyNope
	case 7 Route29_EventScript_TuscanyCancel
	case MULTI_B_PRESSED, Route29_EventScript_TuscanyCancel
	closemessage
	release
	end
Route29_EventScript_TuscanyYes::
	msgbox Route29_Text_TuscanyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SILK_SCARF
	msgbox Route29_Text_TuscanyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyCancel::
	closemessage
	release
	end
Route29_EventScript_TuscanyCompleted::
	msgbox Route29_Text_TuscanyTuesday, MSGBOX_DEFAULT
	closemessage
	release
	end



Route29_EventScript_Girl::
	lock
	faceplayer
	msgbox Route29_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_NIGHT_POKEMON, Route29_EventScript_Boy2
	msgbox Route29_Text_Boy_WaitingForDay, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy2::
	msgbox Route29_Text_Boy_WaitingForNight, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Sign::
	lock
	msgbox Route29_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route29_Text_OldMan1:
	.string "Pokémon hide in the grass.\n"
	.string "Who knows when they'll pop out…$"

Route29_Text_OldMan2:
	.string "I've seen you a couple times.\n"
	.string "How many Pokémon have you caught?\p"
	.string "Would you like me to tell you\n"
	.string "how to catch Pokémon?$"

Route29_Text_OldManExplanation:
	.string "If you weaken them first,\n"
	.string "Pokémon are easier to catch.\p"
	.string "Then, throw a ball at them from\n"
	.string "your bag! Any ball will do.\p"
	.string "If you want to learn more,\n"
	.string "go to the Academy in Violet City!\p"
	.string "The students there know a lot\n"
	.string "about Pokémon.$"

Route29_Text_OldManDeclined:
	.string "Oh. Fine, then.\p"
	.string "Check every route to find\n"
	.string "different types of Pokémon.\p"
	.string "Your Pokédex shows where you can\n"
	.string "find them too!\p"
	.string "If you want to learn more,\n"
	.string "go to the Academy in Violet City!\p"
	.string "The students know a lot about\n"
	.string "Pokémon.$"

Route29_Text_Youngster:
	.string "Yo. How are your Pokémon?\p"
	.string "If they're weak and not ready\n"
	.string "for battle, keep out of the grass.$"

Route29_Text_Lass:
	.string "See those ledges?\n"
	.string "It's scary to jump off them.\p"
	.string "But you can go to New Bark\n"
	.string "without walking through the grass.$"

Route29_Text_Girl:
	.string "I wanted to take a break,\n"
	.string "so I saved to record my progress.$"

Route29_Text_Boy_WaitingForDay:
	.string "I'm waiting for Pokémon that\n"
	.string "appear only later in the day.$"

Route29_Text_Boy_WaitingForNight:
	.string "I'm waiting for Pokémon that\n"
	.string "appear only at night.$"

Route29_Text_MeetTuscany:
	.string "Tuscany: I do believe that this\n"
	.string "is the first time we've met?\p"
	.string "I'm Tuscany of the Weekday Family.\p"
	.string "If you can guess my favorite day,\n"
	.string "I'll give you a reward.$"

Route29_Text_TuscanyNope:
	.string "Not quite!$"

Route29_Text_TuscanyGivesGift:
	.string "Yes! By way of introduction,\n"
	.string "please accept this gift, a Silk\l"
	.string "Scarf.$"

Route29_Text_TuscanyGaveGift:
	.string "Tuscany: Wouldn't you agree\n"
	.string "that it is most adorable?\p"
	.string "It strengthens Normal-type\n"
	.string "moves.\p"
	.string "I am certain it will be of use.$"

Route29_Text_TuscanyTuesday:
	.string "Tuscany: Have you met Monica,\n"
	.string "my older sister?\p"
	.string "Or my younger brother, Wesley?\p"
	.string "I am the third of seven\n"
	.string "children.$"

Route29_Text_Sign1:
	.string "Route 29\p"
	.string "Cherrygrove City - New Bark Town$"

Route29ExNightNpc::
	msgbox Route29ExNightNpc_Text_0, MSGBOX_NPC
	return


Route29ExNightNpc_Text_0:
	.string "I'm checking my Pokégear for a map\n"
	.string "to see where I am going!$"
