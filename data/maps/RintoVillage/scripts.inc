RintoVillage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RintoVillage_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

RintoVillage_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_VISITED_RINTO_VILLAGE
	goto_if_set FLAG_IS_CHAMPION, RintoVillage_MapScripts_MAP_SCRIPT_ON_TRANSITION_2
RintoVillage_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	end

RintoVillage_MapScripts_MAP_SCRIPT_ON_TRANSITION_2:
	setvar VAR_POSTGAME_UNLOCKS_STATE, 1
	goto RintoVillage_MapScripts_MAP_SCRIPT_ON_TRANSITION_1


Rinto_Sign::
	msgbox Rinto_Sign_Text_0, MSGBOX_SIGN
	return


Rinto_OldLady::
	msgbox Rinto_OldLady_Text_0, MSGBOX_NPC
	return


Rinto_TempleSage::
	msgbox Rinto_TempleSage_Text_0, MSGBOX_NPC
	return


Rinto_Gible::
	lock
	faceplayer
	playmoncry SPECIES_GIBLE, CRY_MODE_NORMAL
	msgbox Rinto_Gible_Text_0
	waitmoncry
	release
	end


Rinto_Maractus::
	lock
	faceplayer
	playmoncry SPECIES_MARACTUS, CRY_MODE_NORMAL
	msgbox Rinto_Maractus_Text_0
	waitmoncry
	release
	end


Rinto_Piplup::
	lock
	msgbox Rinto_Piplup_Text_0
	release
	end


Rinto_Gentleman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_REST, Rinto_Gentleman_2
	msgbox Rinto_Gentleman_Text_1
	giveitem ITEM_TM_REST
	setflag FLAG_GOT_TM_REST
	msgbox Rinto_Gentleman_Text_0
	release
	end

Rinto_Gentleman_2:
	msgbox Rinto_Gentleman_Text_0
	release
	end


Rinto_EastGuard::
	msgbox Rinto_EastGuard_Text_0, MSGBOX_NPC
	return


Rinto_TriggerEastGuard::
	lock
	applymovement LOCALID_RINTO_EAST_GUARD, Rinto_TriggerEastGuard_Movement_0
	waitmovement
	applymovement LOCALID_PLAYER, Rinto_TriggerEastGuard_Movement_1
	waitmovement
	msgbox Rinto_EastGuard_Text_0
	closemessage
	applymovement LOCALID_PLAYER, Rinto_TriggerEastGuard_Movement_2
	waitmovement
	release
	end


Rinto_LittleGirl::
	msgbox Rinto_LittleGirl_Text_0, MSGBOX_NPC
	return


Rinto_Fatman::
	msgbox Rinto_Fatman_Text_0, MSGBOX_NPC
	return


Rinto_Dancer::
	lock
	msgbox Rinto_Dancer_Text_0
	release
	end


Rinto_DancerOricorio::
	lock
	playmoncry SPECIES_ORICORIO_SENSU, CRY_MODE_NORMAL
	msgbox Rinto_DancerOricorio_Text_0
	waitmoncry
	release
	end


Rinto_Merchant::
	lock
	faceplayer
	msgbox Rinto_Merchant_Text_0
	pokemart Rinto_Stall
	msgbox Rinto_Merchant_Text_1
	release
	end


	.align 2
Rinto_Stall:
	.2byte ITEM_RING_TARGET
	.2byte ITEM_BINDING_BAND
	.2byte ITEM_EJECT_BUTTON
	.2byte ITEM_WIDE_LENS
	.2byte ITEM_WISE_GLASSES
	.2byte ITEM_EXPERT_BELT
	.2byte ITEM_NONE

Rinto_GameboyKid::
	msgbox Rinto_GameboyKid_Text_0, MSGBOX_NPC
	return


Rinto_TriggerEastGuard_Movement_0:
	walk_in_place_down
	step_end

Rinto_TriggerEastGuard_Movement_1:
	face_up
	step_end

Rinto_TriggerEastGuard_Movement_2:
	walk_left
	step_end

Rinto_Sign_Text_0:
	.string "Rinto Village\n"
	.string "Sunbathed Village$"

Rinto_OldLady_Text_0:
	.string "Oh more tourists?\p"
	.string "I hope you don't mind the\n"
	.string "temperature variations! Ho ho ho!$"

Rinto_TempleSage_Text_0:
	.string "I used to be a member of the Team\n"
	.string "Magma. \p"
	.string "After leaving I decided that I want\n"
	.string "to travel the world as a pilgrim.\p"
	.string "It has been quite refreshing, seeing\n"
	.string "the beauty of the world.$"

Rinto_Gible_Text_0:
	.string "Gible: Gibgib!$"

Rinto_Maractus_Text_0:
	.string "Maractus: Maaaai!$"

Rinto_Piplup_Text_0:
	.string "...The Piplup appears to have dozed off.$"

Rinto_Gentleman_Text_0:
	.string "Rest let's you restore health and\n"
	.string "keep going. \p"
	.string "Do not push yourself without taking \n"
	.string "the time to heal.$"

Rinto_Gentleman_Text_1:
	.string "Resting after travelling afar is\n"
	.string "equally important! Do not neglect\l"
	.string "your health even at a young age!\p"
	.string "Take this.$"

Rinto_EastGuard_Text_0:
	.string "The sandstorms are too intense right\n"
	.string "now. I cannot allow you to pass until\l"
	.string "they calm down.$"

Rinto_LittleGirl_Text_0:
	.string "I saw it! \p"
	.string "Red and blue!\p"
	.string "They flew over the town to the east!$"

Rinto_Fatman_Text_0:
	.string "The blazing sun would make this place\n"
	.string "uninhabitable if not for the small\l"
	.string "opening to the sea.$"

Rinto_Dancer_Text_0:
	.string "Let's go Oricorio, show them our moves!$"

Rinto_DancerOricorio_Text_0:
	.string "Oriiii!$"

Rinto_Merchant_Text_0:
	.string "Hey check out my wares!$"

Rinto_Merchant_Text_1:
	.string "Come back soon!$"

Rinto_GameboyKid_Text_0:
	.string "The pyramid in the west has been locked\n"
	.string "up for a long time. \p"
	.string "I wonder if the key to opening \n"
	.string "it even exists anymore?$"
