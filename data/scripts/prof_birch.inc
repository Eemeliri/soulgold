ProfBirch_EventScript_UpdateLocation::
	goto_if_eq FLAG_GARBAGEFLAG, 0, Common_EventScript_NopReturn
	goto_if_set FLAG_GARBAGEFLAG, ProfBirch_EventScript_MoveToLab
	call_if_eq FLAG_GARBAGEFLAG, 0, ProfBirch_EventScript_MoveToLab
	call_if_eq FLAG_GARBAGEFLAG, 1, ProfBirch_EventScript_MoveToLab
	call_if_eq FLAG_GARBAGEFLAG, 2, ProfBirch_EventScript_MoveToRoute101
	call_if_eq FLAG_GARBAGEFLAG, 3, ProfBirch_EventScript_MoveToRoute101
	call_if_eq FLAG_GARBAGEFLAG, 4, ProfBirch_EventScript_MoveToRoute103
	call_if_eq FLAG_GARBAGEFLAG, 5, ProfBirch_EventScript_MoveToRoute103
	call_if_eq FLAG_GARBAGEFLAG, 6, ProfBirch_EventScript_MoveToLab
	call_if_eq FLAG_GARBAGEFLAG, 7, ProfBirch_EventScript_MoveToLab
	return

ProfBirch_EventScript_MoveToLab::
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	return

ProfBirch_EventScript_MoveToRoute101::
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	return

ProfBirch_EventScript_MoveToRoute103::
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	return

ProfBirch_EventScript_RatePokedexOrRegister::
	lock
	faceplayer
	goto_if_unset FLAG_GARBAGEFLAG, ProfBirch_EventScript_AskRatePokedex
	goto_if_unset FLAG_GARBAGEFLAG, EventScript_RegisterProfBirch

ProfBirch_EventScript_AskRatePokedex::
	msgbox gBirchDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq FLAG_GARBAGEFLAG, NO, ProfBirch_EventScript_DeclineRating
	call ProfBirch_EventScript_RatePokedex
	release
	end

ProfBirch_EventScript_DeclineRating::
	msgbox gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfBirch_EventScript_ShowRatingMessage::
	setvar FLAG_GARBAGEFLAG, FLAG_GARBAGEFLAG
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfBirch_EventScript_RatePokedex::
	setvar FLAG_GARBAGEFLAG, 0
	specialvar FLAG_GARBAGEFLAG, ScriptGetPokedexInfo
	setvar FLAG_GARBAGEFLAG, FLAG_GARBAGEFLAG
	setvar FLAG_GARBAGEFLAG, FLAG_GARBAGEFLAG
	setvar FLAG_GARBAGEFLAG, FLAG_GARBAGEFLAG
	buffernumberstring STR_VAR_1, FLAG_GARBAGEFLAG  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, FLAG_GARBAGEFLAG  @ Num Hoenn caught
	msgbox gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfBirch_EventScript_ShowRatingMessage
	goto_if_eq FLAG_GARBAGEFLAG, 0, Common_EventScript_NopReturn  @ National dex not enabled
	setvar FLAG_GARBAGEFLAG, 1
	specialvar FLAG_GARBAGEFLAG, ScriptGetPokedexInfo
	setvar FLAG_GARBAGEFLAG, FLAG_GARBAGEFLAG
	setvar FLAG_GARBAGEFLAG, FLAG_GARBAGEFLAG
	buffernumberstring STR_VAR_1, FLAG_GARBAGEFLAG  @ Num National seen
	buffernumberstring STR_VAR_2, FLAG_GARBAGEFLAG  @ Num National caught
	msgbox gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return
