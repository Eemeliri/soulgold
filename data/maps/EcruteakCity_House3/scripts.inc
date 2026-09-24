EcruteakCity_House3_MapScripts::
	.byte 0


EcruteakCity_House3_HexLady::
	lock
	faceplayer
	goto_if_set FLAG_TM_HEX, EcruteakCity_House3_HexLady_2
	msgbox EcruteakCity_House3_HexLady_Text_1
	waitmessage
	giveitem ITEM_TM_HEX
	setflag FLAG_TM_HEX
	msgbox EcruteakCity_House3_HexLady_Text_0
	release
	end

EcruteakCity_House3_HexLady_2:
	msgbox EcruteakCity_House3_HexLady_Text_0
	release
	end


EcruteakCity_House3_Lampent::
	lock
	faceplayer
	playmoncry SPECIES_LAMPENT, CRY_MODE_NORMAL
	msgbox EcruteakCity_House3_Lampent_Text_0
	release
	end


EcruteakCity_House3_HexLady_Text_0:
	.string "Hex... Doubles in power...\n"
	.string "Against those affected by status\l"
	.string "conditions...$"

EcruteakCity_House3_HexLady_Text_1:
	.string "Attacking when the enemy is afflicted...\n"
	.string "The key strategy to winning a battle...\p"
	.string "Here... Take it...$"

EcruteakCity_House3_Lampent_Text_0:
	.string "Lampent: Lamppp!$"
