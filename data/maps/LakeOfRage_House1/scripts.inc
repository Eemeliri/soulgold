
LakeOfRage_House1_MapScripts::
	.byte 0

LakeOfRage_House1_EventScript_HiddenPowerGuy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HIDDEN_POWER, LakeOfRage_House1_EventScript_HiddenPowerGuyAfter
	msgbox HiddenPowerGuy_Text_Intro, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	msgbox HiddenPowerGuy_Text_Explanation, MSGBOX_DEFAULT
	setflag FLAG_GOT_HIDDEN_POWER
	closemessage
	release
	end

LakeOfRage_House1_EventScript_HiddenPowerGuyAfter::
	goto_if_eq VAR_POSTGAME_RIVAL_LEGENDARYQ, 1, LakeOfRageMystic_CresseliaQuest
	goto_if_eq VAR_POSTGAME_RIVAL_LEGENDARYQ, 2, LakeOfRageMystic_CresseliaQuest
	msgbox HiddenPowerGuy_Text_Meditating, MSGBOX_DEFAULT
	closemessage
	release
	end

HiddenPowerGuy_Text_Intro:
    .string "…You have strayed far…\p"
    .string "Here I have meditated. Inside me,\n"
    .string "a new power has been awakened.\p"
    .string "Let me share my power with your\n"
    .string "Pokémon. Take this, child.$"

HiddenPowerGuy_Text_Explanation:
    .string "Do you see it? It is Hidden Power!\p"
    .string "It draws out the power of Pokémon\n"
    .string "for attacking.\p"
    .string "Remember this: its type and power\n"
    .string "depend on the Pokémon using it.$"

HiddenPowerGuy_Text_Meditating:
    .string "I am meditating…$"

LakeOfRageMystic_CresseliaQuest::
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 2
	goto_if_eq LakeOfRageMystic_CresseliaQuest_2
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 3
	goto_if_ge LakeOfRageMystic_CresseliaQuest_5
	msgbox LakeOfRageMystic_CresseliaQuest_Text_2
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 2
	release
	end

LakeOfRageMystic_CresseliaQuest_2:
	msgbox LakeOfRageMystic_CresseliaQuest_Text_0
	release
	end

LakeOfRageMystic_CresseliaQuest_5:
	msgbox LakeOfRageMystic_CresseliaQuest_Text_1
	release
	end


LakeOfRageMystic_CresseliaQuest_Text_0:
	.string "Perhaps there is a hidden trail among\n"
	.string "the trees if you look carefully enough.$"

LakeOfRageMystic_CresseliaQuest_Text_1:
	.string "I am meditating...$"

LakeOfRageMystic_CresseliaQuest_Text_2:
	.string "Hmm? \n"
	.string "You wish to know about Cresselia?\p"
	.string "Fascinating. \p"
	.string "It is quite rare for someone seek me\n"
	.string "for knowledge willingly.\p"
	.string "I have indeed seen the creature in\n"
	.string "question, basking in the bright\l"
	.string "moonlight on a rare occasion.\p"
	.string "Then it vanishes into the far corners \n"
	.string "of the lake when spotted!\p"
	.string "Perhaps there is a hidden trail among\n"
	.string "the trees if you look carefully enough.$"
