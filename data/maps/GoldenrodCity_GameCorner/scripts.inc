# 1 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 2 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_MapScripts::
# 3 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	.byte 0
# 4 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 5 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons::
# 6 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 7 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 8 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 9 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
# 10 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
# 11 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon
# 12 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 13 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 14 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon::
# 15 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 16 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 17 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	waitmessage
# 18 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	multichoice 20, 0, MULTI_PRIZE_MONS, FALSE
# 19 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 20 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Pawniard
# 21 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax
# 22 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_SneaselHisui
# 23 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Deino
# 24 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon
# 25 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
# 26 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case 127, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
# 27 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 28 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 29 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange::
# 30 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 31 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 32 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 33 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 34 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 35 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_Pawniard::
# 36 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_PAWNIARD
# 37 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_2, 250
# 38 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
# 39 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 40 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 41 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax::
# 42 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_MUNCHLAX
# 43 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_2, 500
# 44 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
# 45 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 46 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 47 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_SneaselHisui::
# 48 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_SNEASEL_HISUI
# 49 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_2, 1200
# 50 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
# 51 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 52 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 53 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_Deino::
# 54 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_DEINO
# 55 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_2, 2400
# 56 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
# 57 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 58 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 59 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon::
# 60 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_PORYGON
# 61 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_2, 3000
# 62 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
# 63 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 64 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 65 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon::
# 66 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
# 67 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize, MSGBOX_YESNO
# 68 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
# 69 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	checkcoins VAR_RESULT
# 70 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_lt VAR_RESULT, VAR_TEMP_2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins
# 71 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	switch VAR_TEMP_1
# 72 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 73 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 74 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case SPECIES_PAWNIARD,     GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePawniard
# 75 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case SPECIES_SNEASEL_HISUI, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveSneaselHisui
# 76 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case SPECIES_DEINO,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDeino
# 77 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case SPECIES_MUNCHLAX,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax
# 78 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case SPECIES_PORYGON,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon
# 79 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	case SPECIES_PINSIR,   GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir
# 80 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 81 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 82 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePawniard::
# 83 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	givemon VAR_TEMP_1, 15
# 84 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
# 85 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 86 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 87 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveSneaselHisui::
# 88 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	givemon VAR_TEMP_1, 15
# 89 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
# 90 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 91 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 92 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDeino::
# 93 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	givemon VAR_TEMP_1, 15
# 94 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
# 95 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 96 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 97 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax::
# 98 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	givemon VAR_TEMP_1, 15
# 99 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
# 100 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 101 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 102 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon::
# 103 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	givemon VAR_TEMP_1, 15
# 104 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
# 105 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 106 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 107 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir::
# 108 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	givemon VAR_TEMP_1, 15
# 109 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
# 110 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 111 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 112 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon::
# 113 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	showgivemonpic 10, 3
# 114 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
# 115 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty
# 116 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC
# 117 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull
# 118 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 119 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 120 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull::
# 121 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox Route119_WeatherInstitute_2F_Text_NoRoomForPokemon
# 122 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 123 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 124 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 125 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 126 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 127 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon::
# 128 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	getpartysize
# 129 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	subvar VAR_RESULT, 1
# 130 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 131 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 132 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 133 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
# 134 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 135 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 136 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase::
# 137 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase
# 138 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 139 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 140 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 141 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins::
# 142 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins
# 143 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
# 144 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 145 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 146 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty::
# 147 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	removecoins VAR_TEMP_2
# 148 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 149 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 150 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
# 151 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 152 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
# 153 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	waitmessage
# 154 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	waitfanfare
# 155 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	hidemonpic
# 156 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodGamecorner_Text_GiveNicknameToThisMon, MSGBOX_YESNO
# 157 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon
# 158 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
# 159 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 160 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 161 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC::
# 162 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	removecoins VAR_TEMP_2
# 163 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 164 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 165 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
# 166 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 167 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
# 168 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	waitmessage
# 169 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	waitfanfare
# 170 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	hidemonpic
# 171 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC
# 172 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 173 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 174 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC::
# 175 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	call Common_EventScript_TransferredToPC
# 176 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
# 177 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 178 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 179 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyMon::
# 180 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 181 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 182 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 183 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_EventScript_PcMon::
# 184 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 185 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_EventScript_SendMon
# 186 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 187 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	goto GoldenrodCity_GameCorner_EventScript_SendMon
# 188 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 189 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 190 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 191 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 192 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 193 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_SendMon::
# 194 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	call Common_EventScript_TransferredToPC
# 195 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 196 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 197 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 198 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 199 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 200 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_PokefanM::
# 201 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 202 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 203 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_PokefanM1, MSGBOX_DEFAULT
# 204 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 205 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 206 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 207 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 208 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_Hiker::
# 209 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 210 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 211 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_MoveTutorInside, MSGBOX_DEFAULT
# 212 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 213 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 214 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 215 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 216 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_Woman::
# 217 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 218 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 219 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_Woman, MSGBOX_DEFAULT
# 220 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 221 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 222 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 223 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 224 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_Gentleman::
# 225 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 226 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 227 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_Gentleman, MSGBOX_DEFAULT
# 228 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 229 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 230 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 231 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 232 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_PokefanF::
# 233 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 234 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 235 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_PokefanF, MSGBOX_DEFAULT
# 236 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 237 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 238 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 239 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 240 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_PokefanM2::
# 241 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 242 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 243 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_PokefanM2, MSGBOX_DEFAULT
# 244 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 245 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 246 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 247 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 248 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_CooltrainerM::
# 249 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 250 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 251 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_CooltrainerM, MSGBOX_DEFAULT
# 252 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 253 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 254 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 255 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 256 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_EventScript_Pharmacist::
# 257 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	lock
# 258 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	faceplayer
# 259 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	msgbox GoldenrodCity_GameCorner_Text_Pharmacist, MSGBOX_DEFAULT
# 260 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	closemessage
# 261 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	release
# 262 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	end
# 263 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 264 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize:
# 265 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	.string "{STR_VAR_1} is what you want?$"
# 266 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 267 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon:
# 268 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	.string "{PLAYER} got {STR_VAR_1}!$"
# 269 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 270 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodGamecorner_Text_GiveNicknameToThisMon:
# 271 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
	.string "Nickname {STR_VAR_1}?$"
# 272 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 273 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PrizeVendorIntro:
# 274 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Welcome!\p"
# 275 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "We exchange your game coins for\n"
# 276 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "fabulous prizes!$"
# 277 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 278 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize:
# 279 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Which prize would you like?$"
# 280 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 281 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo:
# 282 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Here you go!$"
# 283 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 284 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins:
# 285 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Sorry! You need more coins.$"
# 286 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 287 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PrizeVendorNoMoreRoom:
# 288 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Sorry. You can't carry any more.$"
# 289 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 290 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PrizeVendorQuit:
# 291 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Ok. Please save your coins and come\n"
# 292 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "again!$"
# 293 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 294 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase:
# 295 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Oh? You don't have a Coin Case.$"
# 296 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 297 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_Pharmacist:
# 298 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I always play this slot machine.\n"
# 299 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "It pays out more than others,\l"
# 300 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I think.$"
# 301 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 302 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_Woman:
# 303 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I can't stop winning!$"
# 304 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 305 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PokefanM1:
# 306 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I just love this new slot machine.\p"
# 307 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "It's more of a challenge than the\n"
# 308 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "ones in Celadon.$"
# 309 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 310 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_CooltrainerM:
# 311 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Life is a gamble. I'm going to pull\n"
# 312 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "till I drop!$"
# 313 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 314 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PokefanF:
# 315 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Roulette…\p"
# 316 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I prefer it over the slots because\n"
# 317 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "it's easier to figure the odds.\p"
# 318 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "But the payout is much lower.$"
# 319 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 320 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_CooltrainerF:
# 321 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I won't quit until I win!$"
# 322 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 323 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_Gentleman:
# 324 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I taught Blizzard to my Pokémon.\p"
# 325 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "It was hard to get enough coins for\n"
# 326 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "it, but it was worth it.$"
# 327 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 328 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_PokefanM2:
# 329 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I couldn't win at the slots, and I\n"
# 330 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "blew it on roulette.\p"
# 331 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "I got so furious, I tossed out my\n"
# 332 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Coin Case in the Underground.$"
# 333 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 334 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_MoveTutorInside:
# 335 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Wahahah! The coins keep rolling in!$"
# 336 "data/maps/GoldenrodCity_GameCorner/scripts.pory"

# 337 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
GoldenrodCity_GameCorner_Text_LeftTheirDrink:
# 338 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "Someone left their drink.\p"
# 339 "data/maps/GoldenrodCity_GameCorner/scripts.pory"
    .string "It smells sweet.$"
