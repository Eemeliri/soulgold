BattleFactoryGrounds_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFactoryGrounds_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

BattleFactoryGrounds_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto setFactoryFlightFlag
	return


setFactoryFlightFlag::
	setflag FLAG_VISITED_BATTLE_FACTORY
	end


FactoryGrounds_CooltrainerF::
	msgbox FactoryGrounds_CooltrainerF_Text_0, MSGBOX_NPC
	return


FactoryGrounds_Fisher::
	lock
	msgbox FactoryGrounds_Fisher_Text_0
	release
	end


FactoryGrounds_Boy::
	lock
	faceplayer
	msgbox FactoryGrounds_Boy_Text_0
	applymovement LOCALID_FACTORY_ESPURR, FactoryGrounds_Boy_Movement_0
	waitmovement
	applymovement LOCALID_FACTORY_KID, FactoryGrounds_Boy_Movement_1
	waitmovement
	msgbox FactoryGrounds_Boy_Text_1
	delay 30
	msgbox FactoryGrounds_Boy_Text_1
	faceplayer
	msgbox FactoryGrounds_Boy_Text_2
	release
	end


FactoryGrounds_Espurr::
	lock
	faceplayer
	playmoncry SPECIES_ESPURR, CRY_MODE_NORMAL
	msgbox FactoryGrounds_Espurr_Text_0
	waitmoncry
	release
	end


FactoryGrounds_OldLady::
	msgbox FactoryGrounds_OldLady_Text_0, MSGBOX_NPC
	return


FactoryGrounds_Boy_Movement_0:
	face_right
	step_end

FactoryGrounds_Boy_Movement_1:
	face_left
	step_end

FactoryGrounds_CooltrainerF_Text_0:
	.string "The battles in the Factory are tough!\p"
	.string "You can't use your own Pokémon,\n"
	.string "so you must think on your feet.$"

FactoryGrounds_Fisher_Text_0:
	.string "Hmm, there's no Magikarps in this pond,\n"
	.string "only Tynamos and Chinchous...$"

FactoryGrounds_Boy_Text_0:
	.string "Me and Espurr can converse without\n"
	.string "speaking! Watch!$"

FactoryGrounds_Boy_Text_1:
	.string "...$"

FactoryGrounds_Boy_Text_2:
	.string "Cool, right?$"

FactoryGrounds_Espurr_Text_0:
	.string "Espurr: Essss!$"

FactoryGrounds_OldLady_Text_0:
	.string "I'm not fond of these modern\n"
	.string "buildings being placed so near\l"
	.string "our beloved Ecruteak City.$"
