
NewBarkTown_House3_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_House3_OnTransition
	.byte 0

NewBarkTown_House3_OnTransition::
    call Common_EventScript_SetupRivalGfxId
    end

NewBarkTown_RivalsMom::
	lock
	faceplayer
	checkplayergender
	msgbox NewBarkTown_RivalsMom_Text_0
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_RivalsMom_2
	compare VAR_RIVAL_STATE, 4
	goto_if_ge NewBarkTown_RivalsMom_12
NewBarkTown_RivalsMom_10:
	msgbox NewBarkTown_RivalsMom_Text_4
NewBarkTown_RivalsMom_1:
	release
	end

NewBarkTown_RivalsMom_2:
	compare VAR_RIVAL_STATE, 4
	goto_if_ge NewBarkTown_RivalsMom_7
NewBarkTown_RivalsMom_5:
	msgbox NewBarkTown_RivalsMom_Text_2
	goto NewBarkTown_RivalsMom_1

NewBarkTown_RivalsMom_6:
	msgbox NewBarkTown_RivalsMom_Text_1
	release
	end

NewBarkTown_RivalsMom_7:
	compare VAR_RIVAL_STATE, 12
	goto_if_lt NewBarkTown_RivalsMom_6
	goto NewBarkTown_RivalsMom_5

NewBarkTown_RivalsMom_11:
	msgbox NewBarkTown_RivalsMom_Text_3
	release
	end

NewBarkTown_RivalsMom_12:
	compare VAR_RIVAL_STATE, 12
	goto_if_lt NewBarkTown_RivalsMom_11
	goto NewBarkTown_RivalsMom_10


NewBarkTown_RivalsSister::
	lock
	faceplayer
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_RivalsSister_2
	msgbox NewBarkTown_RivalsSister_Text_1
NewBarkTown_RivalsSister_1:
	release
	end

NewBarkTown_RivalsSister_2:
	msgbox NewBarkTown_RivalsSister_Text_0
	goto NewBarkTown_RivalsSister_1


NewBarkTownRivalHouseRival::
	lock
	faceplayer
	createfieldmugshotrival
	compare VAR_RIVAL_STATE, 12
	goto_if_lt NewBarkTownRivalHouseRival_2
	compare VAR_RIVAL_STATE, 12
	goto_if_ge NewBarkTownRivalHouseRival_5
NewBarkTownRivalHouseRival_4:
	release
	end

NewBarkTownRivalHouseRival_2:
	msgbox NewBarkTownRivalHouseRival_Text_0, MSGBOX_NPC
	release
	end

NewBarkTownRivalHouseRival_5:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 7
	goto_if_ge NewBarkTownRivalHouseRival_9
NewBarkTownRivalHouseRival_7:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_ge NewBarkTownRivalHouseRival_14
NewBarkTownRivalHouseRival_12:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 0
	goto_if_eq NewBarkTownRivalHouseRival_20
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 1
	goto_if_eq NewBarkTownRivalHouseRival_27
NewBarkTownRivalHouseRival_26:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 2
	goto_if_eq NewBarkTownRivalHouseRival_30
NewBarkTownRivalHouseRival_29:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 3
	goto_if_eq NewBarkTownRivalHouseRival_33
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 4
	goto_if_eq NewBarkTownRivalHouseRival_36
NewBarkTownRivalHouseRival_35:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_eq NewBarkTownRivalHouseRival_39
NewBarkTownRivalHouseRival_38:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 6
	goto_if_eq NewBarkTownRivalHouseRival_42
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 7
	goto_if_eq NewBarkTownRivalHouseRival_45
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 8
	goto_if_eq NewBarkTownRivalHouseRival_45
NewBarkTownRivalHouseRival_44:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 7
	goto_if_eq NewBarkTownRivalHouseRival_53
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 8
	goto_if_eq NewBarkTownRivalHouseRival_53
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 9
	goto_if_eq NewBarkTownRivalHouseRival_65
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 10
	goto_if_eq NewBarkTownRivalHouseRival_67
	goto NewBarkTownRivalHouseRival_4

NewBarkTownRivalHouseRival_8:
	checkitem ITEM_HM_DIVE
	compare VAR_RESULT, FALSE
	goto_if_eq NewBarkTownRivalHouseRival_17
	goto NewBarkTownRivalHouseRival_7

NewBarkTownRivalHouseRival_9:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 10
	goto_if_le NewBarkTownRivalHouseRival_8
	goto NewBarkTownRivalHouseRival_7

NewBarkTownRivalHouseRival_13:
	getcaughtmon SPECIES_DARKRAI
	compare VAR_RESULT, FALSE
	goto_if_eq NewBarkTownRivalHouseRival_22
	goto NewBarkTownRivalHouseRival_12

NewBarkTownRivalHouseRival_14:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 10
	goto_if_le NewBarkTownRivalHouseRival_13
	goto NewBarkTownRivalHouseRival_12

NewBarkTownRivalHouseRival_17:
	msgbox NewBarkTownRivalHouseRival_Text_1
	giveitem ITEM_HM_DIVE
	createfieldmugshotrival
	checkitem ITEM_HM_DIVE
	compare VAR_RESULT, FALSE
	goto_if_eq NewBarkTownRivalHouseRival_24
	goto NewBarkTownRivalHouseRival_7

NewBarkTownRivalHouseRival_20:
	msgbox NewBarkTownRivalHouseRival_Text_3
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 1
	release
	end

NewBarkTownRivalHouseRival_22:
	msgbox NewBarkTownRivalHouseRival_Text_2
	release
	end

NewBarkTownRivalHouseRival_24:
	release
	end

NewBarkTownRivalHouseRival_27:
	msgbox NewBarkTownRivalHouseRival_Text_4
	goto NewBarkTownRivalHouseRival_26

NewBarkTownRivalHouseRival_30:
	msgbox NewBarkTownRivalHouseRival_Text_5
	goto NewBarkTownRivalHouseRival_29

NewBarkTownRivalHouseRival_33:
	msgbox NewBarkTownRivalHouseRival_Text_6
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 4
	release
	end

NewBarkTownRivalHouseRival_36:
	msgbox NewBarkTownRivalHouseRival_Text_7
	goto NewBarkTownRivalHouseRival_35

NewBarkTownRivalHouseRival_39:
	msgbox NewBarkTownRivalHouseRival_Text_8
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 6
	goto NewBarkTownRivalHouseRival_38

NewBarkTownRivalHouseRival_42:
	msgbox NewBarkTownRivalHouseRival_Text_9
	checkitem ITEM_HM_DIVE
	compare VAR_RESULT, FALSE
	goto_if_eq NewBarkTownRivalHouseRival_50
NewBarkTownRivalHouseRival_49:
	checkitem ITEM_HM_DIVE
	compare VAR_RESULT, FALSE
	goto_if_eq NewBarkTownRivalHouseRival_62
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 7
	createfieldmugshotrival
	msgbox NewBarkTownRivalHouseRival_Text_10
	release
	end

NewBarkTownRivalHouseRival_45:
	goto_if_set FLAG_ONETIME_GROUDON, NewBarkTownRivalHouseRival_58
	goto NewBarkTownRivalHouseRival_44

NewBarkTownRivalHouseRival_50:
	giveitem ITEM_HM_DIVE
	goto NewBarkTownRivalHouseRival_49

NewBarkTownRivalHouseRival_53:
	msgbox NewBarkTownRivalHouseRival_Text_11
	release
	end

NewBarkTownRivalHouseRival_57:
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 9
	goto NewBarkTownRivalHouseRival_44

NewBarkTownRivalHouseRival_58:
	goto_if_set FLAG_ONETIME_KYOGRE, NewBarkTownRivalHouseRival_57
	goto NewBarkTownRivalHouseRival_44

NewBarkTownRivalHouseRival_62:
	release
	end

NewBarkTownRivalHouseRival_65:
	msgbox NewBarkTownRivalHouseRival_Text_12
	giveitem ITEM_OVAL_CHARM
	createfieldmugshotrival
	msgbox NewBarkTownRivalHouseRival_Text_13
	setvar VAR_POSTGAME_RIVAL_LEGENDARYQ, 10
	release
	end

NewBarkTownRivalHouseRival_67:
	msgbox NewBarkTownRivalHouseRival_Text_14
	goto NewBarkTownRivalHouseRival_4


NewBarkTownRivalHouseMarill::
	lock
	faceplayer
	playmoncry SPECIES_MARILL, CRY_MODE_NORMAL
	msgbox NewBarkTownRivalHouseMarill_Text_0
	waitmoncry
	release
	end


NewBarkTownRivalHouseAzumarill::
	lock
	faceplayer
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox NewBarkTownRivalHouseAzumarill_Text_0
	waitmoncry
	release
	end


NewBarkTown_RivalsMom_Text_0:
	.string "Oh, hello {PLAYER}!$"

NewBarkTown_RivalsMom_Text_1:
	.string "Crystal is currently out, if you were\n"
	.string "looking for her.$"

NewBarkTown_RivalsMom_Text_2:
	.string "Crystal is currently upstairs if\n"
	.string "you are looking for her. She is playing\l"
	.string "with her Pokémon.$"

NewBarkTown_RivalsMom_Text_3:
	.string "Gold is currently out, if you were\n"
	.string "looking for him.$"

NewBarkTown_RivalsMom_Text_4:
	.string "Gold is currently upstairs if\n"
	.string "you are looking for him. He is playing\l"
	.string "with his Pokémon.$"

NewBarkTown_RivalsSister_Text_0:
	.string "Elm gave my sister a Marill, I hope I\n"
	.string "can get a Pokémon to play with \l"
	.string "soon, too!$"

NewBarkTown_RivalsSister_Text_1:
	.string "Elm gave my brother a Marill, I hope I\n"
	.string "can get a Pokémon to play with \l"
	.string "soon, too!$"

NewBarkTownRivalHouseRival_Text_0:
	.string "Hey {PLAYER}! Have you visited\n"
	.string "any new places?$"

NewBarkTownRivalHouseRival_Text_1:
	.string "You'll need this to explore the\n"
	.string "underwater areas of Johto!$"

NewBarkTownRivalHouseRival_Text_2:
	.string "We still need to investigate Darkrai.\p"
	.string "Take Cresselia to the old inn in\n"
	.string "Cherrygrove City!$"

NewBarkTownRivalHouseRival_Text_3:
	.string "Hey {PLAYER}! What's up?\p"
	.string "So I've been doing some thinking, and\n"
	.string "decided that I want to help Prof. Elm.\l"
	.string "with his research into legendary\l"
	.string "Pokémon!\p"
	.string "I've started looking into old rumours\n"
	.string "and stories that are circulating in\l"
	.string "Johto, and I've found my first lead.\p"
	.string "If you got time and happen to be in the\n"
	.string "area, would you mind helping me by\l"
	.string "checking them out?\p"
	.string "The first legendary I'm researching\n"
	.string "right now concerns not one but two\l"
	.string "Pokémon actually!\p"
	.string "Have you heard about Darkrai and\n"
	.string "Cresselia?\p"
	.string "One causes nightmares while the other\n"
	.string "cures them, fascinating!\p"
	.string "I think we should track down Cresselia\n"
	.string "first, in order to locate Darkrai.\p"
	.string "I hear that someone living near or in\n"
	.string "the Lake of Rage might know more.$"

NewBarkTownRivalHouseRival_Text_4:
	.string "I hear that someone living near or in\n"
	.string "the Lake of Rage might know more.$"

NewBarkTownRivalHouseRival_Text_5:
	.string "Oh you found Cresselia's location?\p"
	.string "That's great! You should catch it\n"
	.string "if you're able to!$"

NewBarkTownRivalHouseRival_Text_6:
	.string "You caught Cresselia? \n"
	.string "Nice!\p"
	.string "I've been researching Darkrai's\n"
	.string "meanwhile.\p"
	.string "I'm quite sure that it has something\n"
	.string "to do with the old, run down inn in\l"
	.string "Cherrygrove City.\p"
	.string "It was closed due to some child\n"
	.string "falling to sleep and not waking up, real\l"
	.string "bad press for the inn.\p"
	.string "So in short, take Cresselia with you\n"
	.string "and go check out the inn in Cherrygrove\l"
	.string "City. See if you can find out anything!$"

NewBarkTownRivalHouseRival_Text_7:
	.string "Go check out the old inn in\n"
	.string "Cherrygrove City. Remember to\l"
	.string "take Cresselia with you!$"

NewBarkTownRivalHouseRival_Text_8:
	.string "You caught Darkrai! Excellent!\p"
	.string "You look like you just had a\n"
	.string "nightmare though, did something\l"
	.string "happen?\p"
	.string "Anyway!$"

NewBarkTownRivalHouseRival_Text_9:
	.string "{PLAYER}! I've found another lead\n"
	.string "on legendaries!\p"
	.string "Apparently, Hoenn's very own duo\n"
	.string "is resting somewhere underwater\l"
	.string "here in Johto.\p"
	.string "There aren't many deep waters in\n"
	.string "here, so you'll have to look quite\l"
	.string "hard for them.\p"
	.string "You're going to need this!$"

NewBarkTownRivalHouseRival_Text_10:
	.string "They are probably quite far away\n"
	.string "from each other, so you should\l"
	.string "scour the region far and wide.$"

NewBarkTownRivalHouseRival_Text_11:
	.string "Groudon is likely hidden in a cave which\n"
	.string "can only be accessed underwater. Maybe\l"
	.string "close to a hotter climate?\p"
	.string "Kyogre might prefer easier access to\n"
	.string "the open sea. So check on the\l"
	.string "coastlines!$"

NewBarkTownRivalHouseRival_Text_12:
	.string "You caught them both?!\p"
	.string "Send me your Pokédex data about them\n"
	.string "later. Elm is going to be thrilled\l"
	.string "about this!\p"
	.string "There isn't anything currently I'm\n"
	.string "looking for, and it might take a long\l"
	.string "while before I find another target\l"
	.string "we could search for.\p"
	.string "I don't have much to give, but you\n"
	.string "can have this!$"

NewBarkTownRivalHouseRival_Text_13:
	.string "So, thanks {PLAYER}! For being\n"
	.string "a genuine friend!$"

NewBarkTownRivalHouseRival_Text_14:
	.string "Hey {PLAYER}! How's it going?\n"
	.string "Caught any new special Pokémon?$"

NewBarkTownRivalHouseMarill_Text_0:
	.string "Marii!$"

NewBarkTownRivalHouseAzumarill_Text_0:
	.string "Azumarill: Azuu!$"
