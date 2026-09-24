

BellchimeTrail_MapScripts::
	.byte 0


BellchimeTrail_EventScript_Morty::
	lock
	faceplayer
	msgbox BellchimeTrail_Text_Morty, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_BELLCHIME_MORTY
	removeobject LOCALID_BELLCHIME_MORTY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_MORTY
	release
	end

BellchimeTrail_Text_Morty:
	.string "Morty: The legendary Pokémon\n"
	.string "did not choose me...\p"
	.string "But that does not mean that I\n"
	.string "have lost out on my future.\p"
	.string "I will continue my training until I\n"
	.string "I discover a new future for me.\p"
	.string "If you seek another battle, find\n"
	.string "me at the Fighting Dojo.$"

EcruteakBellchimeTrail_EventScript_DoorTrigger::
	lock
	opendoor 28, 12
	waitdooranim
	addobject OBJ_EVENT_ID_CAMERA
	removeobject OBJ_EVENT_ID_PLAYER
	closedoor 28, 12
	applymovement OBJ_EVENT_ID_CAMERA, EcruteakBellchimeTrail_Movement_CameraPanUp
	waitmovement 0
	warp MAP_TIN_TOWER_1F, 1
	release
	end

EcruteakBellchimeTrail_Movement_CameraPanUp::
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

BellchimeTrail_MortyRematch::
	lock
	faceplayer
	msgbox BellchimeTrail_MortyRematch_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, TRUE
	goto_if_eq BellchimeTrail_MortyRematch_2
BellchimeTrail_MortyRematch_1:
	release
	end

BellchimeTrail_MortyRematch_2:
	msgbox BellchimeTrail_MortyRematch_Text_1
	trainerbattle_no_intro TRAINER_MORTY_2, BellchimeTrail_MortyRematch_Text_2
	msgbox BellchimeTrail_MortyRematch_Text_3
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_BELLCHIME_MORTY
	removeobject LOCALID_BELLCHIME_MORTY
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	goto BellchimeTrail_MortyRematch_1


BellchimeTrail_MortyRematch_Text_0:
	.string "Morty: In the end, the Legendary\n"
	.string "Pokémon did not choose me.\p"
	.string "I wonder the reason often when I walk\n"
	.string "this trail.\p"
	.string "I would like to confirm their reason by\n"
	.string "battling you again if that is\l"
	.string "acceptable to you, {PLAYER}.$"

BellchimeTrail_MortyRematch_Text_1:
	.string "Thank you, I will show those watching\n"
	.string "that I can be as worthy as you!$"

BellchimeTrail_MortyRematch_Text_2:
	.string "I see now why they chose you.$"

BellchimeTrail_MortyRematch_Text_3:
	.string "Merely being strong or wise is not\n"
	.string "always enough. It also takes something\l"
	.string "more intangible that you possess. I hope\l"
	.string "the spirits continue to bless you.\p"
	.string "Until our next meeting.$"
