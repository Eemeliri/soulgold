
RuinsOfAlph_Lab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Lab_OnTransition
	.byte 0

RuinsOfAlph_Lab_OnTransition:
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RuinsOfAlph_Lab_EventScript_Scientist1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist1, MSGBOX_DEFAULT
	release
	end
RuinsOfAlph_Lab_EventScript_Scientist2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist2, MSGBOX_DEFAULT
	release
	end
RuinsOfAlph_Lab_EventScript_Fossils::
	lock
	msgbox RuinsOfAlph_Lab_Text_Fossils, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Lab_Text_Scientist1:
	.string "The Ruins are about 1500 years old.\p"
	.string "But it's not known why they were\n"
	.string "built--or by whom.$"

RuinsOfAlph_Lab_Text_Scientist2:
	.string "There are odd patterns drawn on\n"
	.string "on the walls of the Ruins.\p"
	.string "They must be the keys for\n"
	.string "unraveling the Ruins' mystery.$"

RuinsOfAlph_Lab_Text_Fossils:
	.string "Fossils found within the Ruins.\n"
	.string "Maybe there are more somewhere...$"


RuinsOfAlph_Lab_EventScript_FossilScientist::
	lock
	faceplayer
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RuinsOfAlph_Lab_EventScript_FossilMonReady
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RuinsOfAlph_Lab_EventScript_StillRegenerating
	msgbox RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	goto RuinsOfAlph_Lab_EventScript_ChooseFossil

RuinsOfAlph_Lab_EventScript_GiveRootFossil::
	bufferitemname STR_VAR_1, ITEM_ROOT_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_ROOT_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_LileepReady

RuinsOfAlph_Lab_EventScript_GiveClawFossil::
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_CLAW_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_AnorithReady

RuinsOfAlph_Lab_EventScript_GiveHelixFossil::
	bufferitemname STR_VAR_1, ITEM_HELIX_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_HELIX_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_OmanyteReady

RuinsOfAlph_Lab_EventScript_GiveDomeFossil::
	bufferitemname STR_VAR_1, ITEM_DOME_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_DOME_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_KabutoReady

RuinsOfAlph_Lab_EventScript_GiveOldAmber::
	bufferitemname STR_VAR_1, ITEM_OLD_AMBER
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_OLD_AMBER
	goto RuinsOfAlph_Lab_EventScript_AeroReady

RuinsOfAlph_Lab_EventScript_GivePlumeFossil::
	bufferitemname STR_VAR_1, ITEM_PLUME_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_PLUME_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_ArchenReady

RuinsOfAlph_Lab_EventScript_GiveJawFossil::
	bufferitemname STR_VAR_1, ITEM_JAW_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_JAW_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_TyruntReady

RuinsOfAlph_Lab_EventScript_GiveSailFossil::
	bufferitemname STR_VAR_1, ITEM_SAIL_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_SAIL_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_AmauraReady

RuinsOfAlph_Lab_EventScript_DeclineGiveFossil::
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2::
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo2, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_StillRegenerating::
	msgbox RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_FossilMonReady::
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 1, RuinsOfAlph_Lab_EventScript_LileepReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 2, RuinsOfAlph_Lab_EventScript_AnorithReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 3, RuinsOfAlph_Lab_EventScript_OmanyteReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 4, RuinsOfAlph_Lab_EventScript_KabutoReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 5, RuinsOfAlph_Lab_EventScript_AeroReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 6, RuinsOfAlph_Lab_EventScript_ArchenReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 7, RuinsOfAlph_Lab_EventScript_TyruntReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 8, RuinsOfAlph_Lab_EventScript_AmauraReady
	end

RuinsOfAlph_Lab_EventScript_LileepReady::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveLileep
	end

RuinsOfAlph_Lab_EventScript_AnorithReady::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveAnorith
	end

RuinsOfAlph_Lab_EventScript_OmanyteReady::
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveOmanyte
	end

RuinsOfAlph_Lab_EventScript_KabutoReady::
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveKabuto
	end

RuinsOfAlph_Lab_EventScript_AeroReady::
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveAero
	end

RuinsOfAlph_Lab_EventScript_ArchenReady::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ARCHEN
	goto RuinsOfAlph_Lab_EventScript_NewFossilReady

RuinsOfAlph_Lab_EventScript_TyruntReady::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TYRUNT
	goto RuinsOfAlph_Lab_EventScript_NewFossilReady

RuinsOfAlph_Lab_EventScript_AmauraReady::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_AMAURA
	goto RuinsOfAlph_Lab_EventScript_NewFossilReady

RuinsOfAlph_Lab_EventScript_NewFossilReady::
	bufferspeciesname STR_VAR_2, VAR_TEMP_TRANSFERRED_SPECIES
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMon
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileep::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LILEEP
	givemon SPECIES_LILEEP, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveLileepParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveLileepPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferLileepToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_LILEEP
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingLileep::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorith::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ANORITH
	givemon SPECIES_ANORITH, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
	end

RuinsOfAlph_Lab_EventScript_TransferAnorithToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	end

RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_ANORITH
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyte::
	setvar VAR_TEMP_1, SPECIES_OMANYTE
	givemon SPECIES_OMANYTE, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC::
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabuto::
	setvar VAR_TEMP_1, SPECIES_KABUTO
	call_if_unset FLAG_BADGE04_GET, RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto
	call_if_set FLAG_BADGE04_GET, RuinsOfAlph_Lab_EventScript_GiveLateKabuto
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto::
	givemon SPECIES_KABUTO, 5
	return

RuinsOfAlph_Lab_EventScript_GiveLateKabuto::
	givemon SPECIES_KABUTO, 20
	return

RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end


RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferKabutoToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end

RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_KABUTO
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveAero::
	setvar VAR_TEMP_1, SPECIES_AERODACTYL
	givemon SPECIES_AERODACTYL, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveAeroParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveAeroPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferAeroToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_AERODACTYL
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingAero::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMon::
	givemon VAR_TEMP_TRANSFERRED_SPECIES, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedNewFossilMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon
	end

RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedNewFossilMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferNewFossilMonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferNewFossilMonToPC
	end

RuinsOfAlph_Lab_EventScript_TransferNewFossilMonToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon
	end

RuinsOfAlph_Lab_EventScript_ReceivedNewFossilMonFanfare::
	bufferspeciesname STR_VAR_2, VAR_TEMP_TRANSFERRED_SPECIES
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end


RuinsOfAlph_Lab_EventScript_ChooseFossil::
	msgbox RuinsOfAlph_Lab_Text_PickFossilFromBag, MSGBOX_DEFAULT
	chooseitem POCKET_ITEMS
	switch VAR_ITEM_ID
	case ITEM_NONE, RuinsOfAlph_Lab_EventScript_CancelFossilSelect
	case ITEM_DOME_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveDomeFossil
	case ITEM_ROOT_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveRootFossil
	case ITEM_PLUME_FOSSIL, RuinsOfAlph_Lab_EventScript_GivePlumeFossil
	case ITEM_JAW_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveJawFossil
	case ITEM_SAIL_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveSailFossil
	case ITEM_OLD_AMBER, RuinsOfAlph_Lab_EventScript_GiveOldAmber
	msgbox RuinsOfAlph_Lab_Text_ThatsNotAFossil, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ChooseFossil
	end

RuinsOfAlph_Lab_EventScript_ChooseClawFossil::
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveClawFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseRootFossil::
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveRootFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseHelixFossil::
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveHelixFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseDomeFossil::
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveDomeFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseOldAmber::
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveOldAmber
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_CancelFossilSelect::
	release
	end

RuinsOfAlph_Lab_EventScript_WorkOnNext::
	msgbox RuinsOfAlph_Lab_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_Text_DeviceForTalkingToPokemon:
	.string "We're developing a device for talking\n"
	.string "with Pokémon.\p"
	.string "But we haven't had much success…$"

RuinsOfAlph_Lab_Text_DevelopingNewBalls:
	.string "I'm developing new kinds of\n"
	.string "Poké Balls…\p"
	.string "But I haven't made much headway…$"

RuinsOfAlph_Lab_Text_WeFinallyMadeNewBalls:
	.string "We finally made new kinds of\n"
	.string "Poké Balls!\p"
	.string "The Repeat Ball makes it easier to\n"
	.string "catch Pokémon you've caught before.\p"
	.string "The Timer Ball gets better at catching\n"
	.string "Pokémon the longer a battle runs.\p"
	.string "Both are proudly developed by\n"
	.string "the Devon Corporation.\p"
	.string "Please give them a try!$"

RuinsOfAlph_Lab_Text_IMadePokenav:
	.string "I made the Pokégear!\p"
	.string "As an engineer, I feel blessed to have\n"
	.string "made something so great!$"

RuinsOfAlph_Lab_Text_WowThatsAPokenav:
	.string "Oh, wow!\n"
	.string "That's a Pokégear!\p"
	.string "It came about as a result of our\n"
	.string "President's desire to learn about\l"
	.string "the feelings of Pokémon.\p"
	.string "Would you like me to describe its\n"
	.string "features in detail?\p"
	.string "No, no. I think you'll find out just by\n"
	.string "trying the Pokégear out.$"

RuinsOfAlph_Lab_Text_DeviceToVisualizePokemonDreams:
	.string "I'm trying to develop a device that\n"
	.string "visually reproduces the dreams of\l"
	.string "Pokémon…\p"
	.string "But it's not going well.$"

RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils:
	.string "I've been trying to develop a device\n"
	.string "that resurrects Pokémon from fossils…\p"
	.string "And, it's working!$"

RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife:
	.string "Would you like to bring that Pokémon\n"
	.string "back to life?\p"
	.string "I can with my newly developed\n"
	.string "Fossil Regenerator.$"

RuinsOfAlph_Lab_Text_OhIsThatSo:
	.string "Oh, is that so?\p"
	.string "My technological expertise\n"
	.string "is outstanding, I tell you.$"

RuinsOfAlph_Lab_Text_OhIsThatSo2:
	.string "Oh, you don't have this fossil.\n"
	.string "Come back if you manage to find it.$"

RuinsOfAlph_Lab_Text_TwoFossilsPickOne:
	.string "Oh, now that's a surprise!\n"
	.string "You have more than one fossil?\p"
	.string "Unfortunately, my machine can only\n"
	.string "regenerate one Pokémon at a time.\p"
	.string "Which fossil would you like to\n"
	.string "regenerate?$"

RuinsOfAlph_Lab_Text_PickFossilFromBag:
	.string "Please choose the fossil you'd like\n"
	.string "to regenerate.$"

RuinsOfAlph_Lab_Text_ThatsNotAFossil:
	.string "That's not a fossil!$"

RuinsOfAlph_Lab_Text_HandedFossilToResearcher:
	.string "Excellent!\n"
	.string "Let's do this right away.\p"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
	.string "the Ruins Researcher.$"

RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime:
	.string "The Fossil Regenerator, which I made,\n"
	.string "is incredible.\p"
	.string "But it has one drawback--it takes\n"
	.string "a long time to work.\p"
	.string "So, uh… How about you go for a stroll\n"
	.string "and look around for a while?$"

RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife:
	.string "Thanks for waiting!\p"
	.string "Your fossilized Pokémon has been\n"
	.string "brought back to life!\p"
	.string "The fossil was an ancient Pokémon.\n"
	.string "{STR_VAR_2}, it was!$"

RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher:
	.string "{PLAYER} received {STR_VAR_2} from\n"
	.string "the Researcher.$"

@ Unused
RuinsOfAlph_Lab_Text_TooManyPokemon:
	.string "Uh-oh, you've got too many Pokémon.\n"
	.string "You have no room for this one.$"

RuinsOfAlph_Lab_Text_DevelopNewPokenavFeature:
	.string "I'm trying to develop a new feature\n"
	.string "for the Pokégear...\p"
	.string "But it's not going well.$"

RuinsOfAlph_Lab_Text_WhatToWorkOnNext:
	.string "Well, now what shall I work on\n"
	.string "developing next?\p"
	.string "Our company allows us to make our\n"
	.string "inspirations into reality.\p"
	.string "One couldn't ask for a better\n"
	.string "environment as an engineer.$"
