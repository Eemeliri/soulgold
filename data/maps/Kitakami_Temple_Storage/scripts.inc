Kitakami_Temple_Storage_MapScripts::
	.byte 0


StorageMienfoo::
	lock
	faceplayer
	playmoncry SPECIES_MIENFOO, CRY_MODE_NORMAL
	msgbox StorageMienfoo_Text_0
	waitmoncry
	release
	end


StorageKeeper::
	lock
	faceplayer
	goto_if_set FLAG_OBTAINED_OGERPON_MASKS, StorageKeeper_2
	msgbox StorageKeeper_Text_1
	checkspecies SPECIES_OGERPON
	compare VAR_RESULT, TRUE
	goto_if_eq StorageKeeper_5
	release
	end

StorageKeeper_2:
	msgbox StorageKeeper_Text_0
	release
	end

	release
	end

StorageKeeper_5:
	playse SE_PIN
	applymovement LOCALID_TEMPLE_STOREKEEPER, Common_Movement_ExclamationMark
	waitse
	delay 30
	msgbox StorageKeeper_Text_2
	giveitem ITEM_CORNERSTONE_MASK
	giveitem ITEM_WELLSPRING_MASK
	giveitem ITEM_HEARTHFLAME_MASK
	setflag FLAG_OBTAINED_OGERPON_MASKS
	msgbox StorageKeeper_Text_0
	release
	end


StorageMienfoo_Text_0:
	.string "Mienfoo: Foo!$"

StorageKeeper_Text_0:
	.string "These masks allow Ogerpon to wield\n"
	.string "powers from other types in battle.$"

StorageKeeper_Text_1:
	.string "My task is to manage the sacred relics\n"
	.string "of Kitakami. \p"
	.string "Our villages guardian, Ogerpon once\n"
	.string "entrusted powerful relics to us.\p"
	.string "We've been guarding them ever since\n"
	.string "until Ogerpon once again requires\l"
	.string "them.$"

StorageKeeper_Text_2:
	.string "Could it be...? Ogerpon has chosen you\n"
	.string "as it's partner?\p"
	.string "Incredible!\p"
	.string "In that case, you should be the one\n"
	.string "holding its sacred relics.$"
