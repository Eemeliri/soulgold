

OlivineCity_Cafe_MapScripts::
	.byte 0

OlivineCity_Cafe_EventScript_Jasmine::
	lock
	faceplayer
	msgbox OlivineCity_Cafe_Text_Jasmine, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAFE_JASMINE
	removeobject LOCALID_CAFE_JASMINE
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_JASMINE
	release
	end

OlivineCity_Cafe_Text_Jasmine:
	.string "Oh... Hello, {PLAYER}.\p"
	.string "These dishes in front of me are\n"
	.string "not all mine...\p"
	.string "Uh...\p"
	.string "Actually, the person who sat here\n"
	.string "before me ate a lot...\p"
	.string "If you'd like to battle again,\n"
	.string "please visit me at the Fighting\l"
	.string "Dojo in Saffron City.$"

OlivineCity_EventScript_SailorA::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_STRENGTH, OlivineCity_EventScript_SailorA2
	msgbox OlivineCity_Text_CafeSailorStrength, MSGBOX_DEFAULT
	giveitem ITEM_HM_STRENGTH
	setflag FLAG_RECEIVED_HM_STRENGTH
OlivineCity_EventScript_SailorA2::
	msgbox OlivineCity_Text_CafeSailorGotStrength, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Cook::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeFishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_SailorB::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSailorStrength:
	.string "Hah! Your Pokémon sure look like\n"
	.string "lightweights!\p"
	.string "They don't have the power to\n"
	.string "move boulders aside.\p"
	.string "Here, use this and teach them\n"
	.string "Strength!$"

OlivineCity_Text_CafeSailorGotStrength:
	.string "On the sea, the only thing you\n"
	.string "can count on is your own self!\p"
	.string "I'm so proud of my buff bod!\n"
	.string "You should train like me!$"

OlivineCity_Text_CafeFishingGuru:
	.string "Olivine Cafe's menu is packed\n"
	.string "with hearty fare for beefy\l"
	.string "Sailors like me!$"

OlivineCity_Text_CafeSailor:
	.string "Whenever I roll into this town,\n"
	.string "I always visit the Olivine Cafe.\p"
	.string "Everything on the menu makes me\n"
	.string "feel stronger. I can't stop eating!$"

OlivineCafe_JasmineRematch::
	lock
	faceplayer
	msgbox OlivineCafe_JasmineRematch_Text_0
	msgbox OlivineCafe_JasmineRematch_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq OlivineCafe_JasmineRematch_2
OlivineCafe_JasmineRematch_1:
	release
	end

OlivineCafe_JasmineRematch_2:
	trainerbattle_no_intro TRAINER_JASMINE_2, OlivineCafe_JasmineRematch_Text_2
	msgbox OlivineCafe_JasmineRematch_Text_3
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAFE_JASMINE
	removeobject LOCALID_CAFE_JASMINE
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	goto OlivineCafe_JasmineRematch_1


OlivineCafe_JasmineRematch_Text_0:
	.string "Oh, Hello {PLAYER}...\p"
	.string "Did you come here to eat too..?\n"
	.string "I really enjoy the seafood served here.\l"
	.string "It always makes me feel nostalgic for\l"
	.string "some reason.$"

OlivineCafe_JasmineRematch_Text_1:
	.string "I was hoping we could have another \n"
	.string "battle again, if that is okay.$"

OlivineCafe_JasmineRematch_Text_2:
	.string "You really are amazing, \n"
	.string "{PLAYER}.$"

OlivineCafe_JasmineRematch_Text_3:
	.string "You fight with both kindness and grace.\n"
	.string "Something I strive for every day...\l"
	.string "Thank you for this battle, I won't\l"
	.string "forget it.$"
