
Route33_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route33_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route33_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route33_EventScript_HikerAnthony::
	trainerbattle_single TRAINER_ANTHONY, Route33_Text_HikerAnthony2Seen, Route33_Text_HikerAnthony2Beaten
	msgbox Route33_Text_HikerAnthony2After, MSGBOX_AUTOCLOSE
	end

Route33_EventScript_Lass::
	lock
	faceplayer
	msgbox Route33_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route33_Text_HikerAnthony2Seen:
	.string "I came through the tunnel,\n"
	.string "but I still have plenty\l"
	.string "of energy left.$"

Route33_Text_HikerAnthony2Beaten:
	.string "Whoa! You've got more zip\n"
	.string "than me!$"

Route33_Text_HikerAnthony2After:
	.string "We Hikers are at our best\n"
	.string "in the mountains.$"

Route33_Text_HikerAnthonyDunsparce:
	.string "Hey, did you get a Dunsparce?\p"
	.string "I caught one too.\p"
	.string "Take a look at it in the light.\n"
	.string "It's got a funny face!$"

Route33_Text_Lass:
	.string "Pant, pant…\p"
	.string "That cave was bigger than\n"
	.string "I'd expected.\p"
	.string "I got too tired exploring\n"
	.string "for Marill, so I came outside.$"

Route33_HiddenGrotto::
	msgbox Route33_HiddenGrotto_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route33_HiddenGrotto_2
Route33_HiddenGrotto_1:
	release
	end

Route33_HiddenGrotto_2:
	warp MAP_HIDDEN_GROTTO_ROUTE33, 0
	waitstate
	goto Route33_HiddenGrotto_1


fisherMan_Route33::
	lock
	faceplayer
	msgbox fisherMan_Route33_Text_0
	release
	end


Route33_HiddenGrotto_Text_0:
	.string "There seems to be a path behind the\n"
	.string "trees. Enter?$"

fisherMan_Route33_Text_0:
	.string "I've heard rumours of a very rare\n"
	.string "Pokémon swimming amongst the \l"
	.string "Gastrodon to the south of here.$"
