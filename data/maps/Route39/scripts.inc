

Route39_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route39_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route39_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route39_EventScript_Woman::
	lock
	faceplayer
	msgbox Route39_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_Text_Woman:
	.string "That shadow... Maybe it was a giant\n"
	.string "Pidgey?$"

Route39_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox Route39_Text_Miltank, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route39_Text_Miltank:
	.string "Miltank: Mooo!$"

Route39_EventScript_Eugene::
	trainerbattle_single TRAINER_EUGENE, Route39_Text_SailorEugeneSeen, Route39_Text_SailorEugeneBeaten
	msgbox Route39_Text_SailorEugeneAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_SailorEugeneSeen:
	.string "I just got back to Olivine.\p"
	.string "So how about a Pokémon battle?$"

Route39_Text_SailorEugeneBeaten:
	.string "Awaaargh!$"

Route39_Text_SailorEugeneAfter:
	.string "My Pokémon were caught and\n"
	.string "raised overseas.\p"
	.string "They're my companions on\n"
	.string "those long voyages.$"

Route39_EventScript_Derek::
	trainerbattle_single TRAINER_DEREK, Route39_Text_PokefanMDerekSeen, Route39_Text_PokefanMDerekBeaten
	msgbox Route39_Text_PokefanMDerekAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanMDerekSeen:
	.string "This is a good time to brag\n"
	.string "about my Pikachu!$"

Route39_Text_PokefanMDerekBeaten:
	.string "I had no time to show off\n"
	.string "Pikachu…$"

Route39_Text_PokefanMDerekAfter:
	.string "I'm not listening to your\n"
	.string "bragging!\p"
	.string "We Poké Fans have a policy\n"
	.string "of not listening to bragging!$"

Route39_EventScript_Ruth::
	trainerbattle_single TRAINER_RUTH, Route39_Text_PokefanFRuthSeen, Route39_Text_PokefanFRuthBeaten
	msgbox Route39_Text_PokefanFRuthAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFRuthSeen:
	.string "Such darling Pokémon.\p"
	.string "Let's show our Pokémon\n"
	.string "together at the same time.$"

Route39_Text_PokefanFRuthBeaten:
	.string "I don't mind losing.$"

Route39_Text_PokefanFRuthAfter:
	.string "Do you know about baby\n"
	.string "Pokémon?\p"
	.string "I bet they're just adorable!$"

Route39_EventScript_Norman::
	trainerbattle_single TRAINER_NORMAN, Route39_Text_PsychicNormanSeen, Route39_Text_PsychicNormanBeaten
	msgbox Route39_Text_PsychicNormanAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PsychicNormanSeen:
	.string "Let me see what your\n"
	.string "Pokémon are capable of.$"

Route39_Text_PsychicNormanBeaten:
	.string "Ooh, your Pokémon have\n"
	.string "potential.$"

Route39_Text_PsychicNormanAfter:
	.string "You know how Pokémon have\n"
	.string "different abilities?\p"
	.string "People are like that too.\n"
	.string "Everyone has different\l"
	.string "potential.$"

Route39_EventScript_Jamie::
	trainerbattle_single TRAINER_JAMIE, Route39_Text_PokefanFJaimeSeen, Route39_Text_PokefanFJaimeBeaten
	msgbox Route39_Text_PokefanFJaimeAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFJaimeSeen:
	.string "You came at just the right\n"
	.string "time.\p"
	.string "Let's battle.$"

Route39_Text_PokefanFJaimeBeaten:
	.string "Oh, how disappointing…$"

Route39_Text_PokefanFJaimeAfter:
	.string "I met Umbreon at night right\n"
	.string "here on Route 39.\p"
	.string "I'm not sure why, but it\n"
	.string "seems to like it when I\l"
	.string "train here.\p"
	.string "It seems to become friendlier\n"
	.string "by training here than\l"
	.string "anywhere else.$"

Route39_EventScript_Sign1::
	lock
	msgbox Route39_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_Sign:
	.string "Route 39\p"
	.string "Olivine City - Ecruteak City$"

Route39_EventScript_Sign2::
	lock
	msgbox Route39_Text_MoomooFarmSign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_MoomooFarmSign:
	.string "Moomoo Farm\p"
	.string "Enjoy Our Fresh and Tasty Milk$"

Route39_EventScript_Sign3::
	lock
	msgbox Route39_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_TrainerTips:
	.string "Trainer Tips\p"
	.string "Use Headbutt on trees to shake\n"
	.string "Pokémon out.\p"
	.string "Different kinds of Pokémon\n"
	.string "drop out of trees.\p"
	.string "Use Headbutt on any tree\n"
	.string "you see!$"

Route39_NorthSign::
	msgbox Route39_NorthSign_Text_0, MSGBOX_SIGN
	return


Route39_BaobaTrigger::
	lock
	applymovement LOCALID_R39_BAOBA, Route39_BaobaTrigger_Movement_0
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_R39_BAOBA, Common_Movement_ExclamationMark
	waitmovement 0
	approachobject LOCALID_R39_BAOBA, LOCALID_PLAYER, DIR_EAST, DIR_WEST
	waitmovement 0
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox Route39_BaobaTrigger_Text_0
	waitmessage
	removefieldmugshot
	msgbox Route39_BaobaTrigger_Text_1
	waitmessage
	playse MUS_HG_POKEGEAR_REGISTERED
	msgbox Route39_BaobaTrigger_Text_2
	waitse
	createfieldmugshot MUGSHOT_GENTLEMAN
	msgbox Route39_BaobaTrigger_Text_3
	closemessage
	applymovement LOCALID_R39_BAOBA, Route39_BaobaTrigger_Movement_1
	waitmovement 0
	setflag FLAG_ENABLE_BAOBA_MATCH_CALL
	removeobject LOCALID_R39_BAOBA
	setvar VAR_ROUTE39_BAOBA_STATE, 1
	release
	end


Route39_BaobaTrigger_Movement_0:
	face_right
	step_end

Route39_BaobaTrigger_Movement_1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route39_NorthSign_Text_0:
	.string "{UP_ARROW} Snowtop Mountain trail$"

Route39_BaobaTrigger_Text_0:
	.string "Baoba: ...Ohh! \n"
	.string "What you are holding is...\l"
	.string "what they call... a Pokédex!\l"
	.string "Haven't seen one of those in ages.\p"
	.string "My name is Baoba!\p"
	.string "I used to run a Safari Zone in Fuchsia\n"
	.string "City, but it was becoming out of date\l"
	.string "with the new entertainment options\l"
	.string "coming out.\p"
	.string "I decided to go overseas to learn the\n"
	.string "newest technology and open a\l"
	.string "state-of-the-art Safari Zone in\l"
	.string "Cianwood.\p"
	.string "It may be more than a coincidence that\n"
	.string "we are chatting.\p"
	.string "Why don't we register each other's\n"
	.string "numbers in the Pokégear?\p"
	.string "I can give you a call once the Safari\n"
	.string "Zone is open before I call anyone else!$"

Route39_BaobaTrigger_Text_1:
	.string "...$"

Route39_BaobaTrigger_Text_2:
	.string "{PLAYER} registered Baoba\n"
	.string "in the Pokégear!$"

Route39_BaobaTrigger_Text_3:
	.string "That's the way! I'll let you know\n"
	.string "over the Pokégear once it's ready!$"
