#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "item_menu.h"
#include "party_menu.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "test/overworld_script.h"
#include "test/test.h"

TEST("Items are stored in their correct bag pockets")
{
    struct BagPocket *medicinePocket = &gBagPockets[POCKET_MEDICINE];
    struct BagPocket *battleItemsPocket = &gBagPockets[POCKET_BATTLE_ITEMS];
    struct BagPocket *megaStonesPocket = &gBagPockets[POCKET_MEGASTONES];

    memset(medicinePocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.medicine));
    memset(battleItemsPocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.battleItems));
    memset(megaStonesPocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));

    EXPECT_EQ(GetItemPocket(ITEM_POTION), POCKET_MEDICINE);
    EXPECT_EQ(GetItemPocket(ITEM_LEFTOVERS), POCKET_BATTLE_ITEMS);
    EXPECT_EQ(GetItemPocket(ITEM_ROCKY_HELMET), POCKET_BATTLE_ITEMS);
    EXPECT_EQ(GetItemPocket(ITEM_GRASSTITE), POCKET_MEGASTONES);

    RUN_OVERWORLD_SCRIPT(
        additem ITEM_POTION;
        additem ITEM_LEFTOVERS;
        additem ITEM_ROCKY_HELMET;
        additem ITEM_GRASSTITE;
    );

    EXPECT_EQ(medicinePocket->itemSlots[0].itemId, ITEM_POTION);
    EXPECT_EQ(medicinePocket->itemSlots[0].quantity, 1);
    EXPECT_EQ(medicinePocket->itemSlots[1].itemId, ITEM_NONE);

    EXPECT_EQ(battleItemsPocket->itemSlots[0].itemId, ITEM_LEFTOVERS);
    EXPECT_EQ(battleItemsPocket->itemSlots[0].quantity, 1);
    EXPECT_EQ(battleItemsPocket->itemSlots[1].itemId, ITEM_ROCKY_HELMET);
    EXPECT_EQ(battleItemsPocket->itemSlots[1].quantity, 1);
    EXPECT_EQ(battleItemsPocket->itemSlots[2].itemId, ITEM_NONE);

    EXPECT_EQ(megaStonesPocket->itemSlots[0].itemId, ITEM_GRASSTITE);
    EXPECT_EQ(megaStonesPocket->itemSlots[0].quantity, 1);
    EXPECT_EQ(megaStonesPocket->itemSlots[1].itemId, ITEM_NONE);
}

TEST("Infinite held items stay unlocked when moved between the bag and Pokemon")
{
    struct BagPocket *megaStonesPocket = &gBagPockets[POCKET_MEGASTONES];

    memset(megaStonesPocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));

    EXPECT(IsItemInfiniteHold(ITEM_GRASSTITE));
    EXPECT(IsItemInfiniteHold(ITEM_BONDSTONE));
    EXPECT(!IsItemInfiniteHold(ITEM_VENUSAURITE));
    EXPECT(!CanItemBeTossed(ITEM_GRASSTITE));
    EXPECT(!CanItemBeTossed(ITEM_BONDSTONE));
    EXPECT(CanItemBeTossed(ITEM_VENUSAURITE));

    EXPECT(AddBagItem(ITEM_GRASSTITE, 1));
    EXPECT(RemoveHeldItemFromBag(ITEM_GRASSTITE));
    EXPECT(CheckBagHasItem(ITEM_GRASSTITE, 1));

    EXPECT(AddHeldItemToBag(ITEM_GRASSTITE));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GRASSTITE), 1);

    EXPECT(!CheckBagHasItem(ITEM_BONDSTONE, 1));
    EXPECT(AddHeldItemToBag(ITEM_BONDSTONE));
    EXPECT(CheckBagHasItem(ITEM_BONDSTONE, 1));
}

TEST("Infinite held item unlocks cannot be tossed from the bag or a Pokemon")
{
    enum Item heldItem;
    struct BagPocket *megaStonesPocket = &gBagPockets[POCKET_MEGASTONES];
    struct BagPocket *battleItemsPocket = &gBagPockets[POCKET_BATTLE_ITEMS];

    memset(megaStonesPocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));
    memset(battleItemsPocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.battleItems));
    EXPECT(AddBagItem(ITEM_WATERTITE, 1));
    EXPECT(AddBagItem(ITEM_LEFTOVERS, 1));

    EXPECT(!ItemMenu_TestTossItemFromBag(ITEM_WATERTITE, 1));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_WATERTITE), 1);
    EXPECT(ItemMenu_TestTossItemFromBag(ITEM_LEFTOVERS, 1));
    EXPECT(!CheckBagHasItem(ITEM_LEFTOVERS, 1));

    CreateMon(&gPlayerParty[0], SPECIES_GYARADOS, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(SwShPartyMenu_TestGiveHeldItemToMon(0, ITEM_WATERTITE));

    EXPECT(!SwShPartyMenu_TestTossHeldItem(0));
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_WATERTITE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_WATERTITE), 1);

    heldItem = ITEM_LEFTOVERS;
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &heldItem);
    EXPECT(SwShPartyMenu_TestTossHeldItem(0));
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_NONE);
}

TEST("Canceling a held item switch from the party menu does not duplicate the selected item")
{
    enum Item heldItem = ITEM_POWER_ANKLET;
    struct BagPocket *pocket = &gBagPockets[POCKET_ITEMS];

    memset(pocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.items));
    CreateMon(&gPlayerParty[0], SPECIES_PIKACHU, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &heldItem);
    EXPECT(AddBagItem(ITEM_BOTTLE_CAP, 1));

    EXPECT(SwShPartyMenu_TestCancelHeldItemSwitch(ITEM_BOTTLE_CAP));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_BOTTLE_CAP), 1);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_POWER_ANKLET);
}

TEST("SwSh party slot animations ignore missing sprites")
{
    EXPECT(SwShPartyMenu_TestMissingSlotSpritesAreIgnored());
}

TEST("Infinite held item migration flag does not alias Pokemon received progress")
{
    FlagClear(FLAG_SYS_POKEMON_GET);
    FlagClear(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);

    FlagSet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
    EXPECT(FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));
    EXPECT(!FlagGet(FLAG_SYS_POKEMON_GET));

    FlagSet(FLAG_SYS_POKEMON_GET);
    FlagClear(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
    EXPECT(FlagGet(FLAG_SYS_POKEMON_GET));
    EXPECT(!FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));
}

TEST("Switch party GIVE and storage TAKE preserve the Watertite unlock")
{
    enum Item heldItem = ITEM_WATERTITE;
    struct BagPocket *pocket = &gBagPockets[POCKET_MEGASTONES];

    memset(pocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));
    CreateMon(&gPlayerParty[0], SPECIES_GYARADOS, 50, 0, OTID_STRUCT_PLAYER_ID);
    FlagSet(FLAG_ITEM_WHIRL_ISLANDS_B2F_CALCIUM);
    RUN_OVERWORLD_SCRIPT(
        additem ITEM_WATERTITE;
    );
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_WATERTITE), 1);

    EXPECT(SwShPartyMenu_TestGiveHeldItemToMon(0, ITEM_WATERTITE));
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_WATERTITE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_WATERTITE), 1);

    SetBoxMonAt(0, 0, &gPlayerParty[0].box);
    ZeroMonData(&gPlayerParty[0]);
    EXPECT(PokemonStorageSystem_TestTakeItemToBag(0, 0));
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_WATERTITE), 1);

    SetBoxMonDataAt(0, 0, MON_DATA_HELD_ITEM, &heldItem);
    EXPECT(RemoveBagItem(ITEM_WATERTITE, 1));
    EXPECT(!CheckBagHasItem(ITEM_WATERTITE, 1));
    EXPECT(PokemonStorageSystem_TestTakeItemToBag(0, 0));
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_WATERTITE), 1);
}

TEST("Infinite held item migration restores only obtained unlocks")
{
    struct BagPocket *pocket = &gBagPockets[POCKET_MEGASTONES];

    memset(pocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));
    FlagClear(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
    FlagSet(FLAG_ITEM_TOHJOFALLS_HEART_SCALE);
    FlagSet(FLAG_ITEM_WHIRL_ISLANDS_B2F_CALCIUM);
    FlagSet(FLAG_HIDE_GRASSTITE);
    FlagClear(FLAG_MTMORTAR_DEPTHS_FIRETITE);
    FlagSet(FLAG_HIDE_LAKE_OF_RAGE_GYARADOS);
    VarSet(VAR_NEWBARKTOWN_LABSTATE, 8);

    EXPECT(AddBagItem(ITEM_GRASSTITE, 1));
    MigrateInfiniteHeldItems();

    EXPECT(CheckBagHasItem(ITEM_NORMALITE, 1));
    EXPECT(CheckBagHasItem(ITEM_WATERTITE, 1));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GRASSTITE), 1);
    EXPECT(!CheckBagHasItem(ITEM_FIRETITE, 1));
    EXPECT(CheckBagHasItem(ITEM_FAIRYTITE, 1));
    EXPECT(CheckBagHasItem(ITEM_BONDSTONE, 1));
    EXPECT(FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));

    MigrateInfiniteHeldItems();
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_NORMALITE), 1);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_WATERTITE), 1);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_FAIRYTITE), 1);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_BONDSTONE), 1);
}

TEST("Infinite held item migration waits for room in the Mega Stone pocket")
{
    u32 i;
    struct BagPocket *pocket = &gBagPockets[POCKET_MEGASTONES];

    memset(pocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));
    FlagClear(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
    FlagSet(FLAG_ITEM_TOHJOFALLS_HEART_SCALE);

    for (i = 0; i < pocket->capacity; i++)
        BagPocket_SetSlotItemIdAndCount(pocket, i, ITEM_VENUSAURITE, 1);

    MigrateInfiniteHeldItems();
    EXPECT(!CheckBagHasItem(ITEM_NORMALITE, 1));
    EXPECT(!FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));

    BagPocket_SetSlotItemIdAndCount(pocket, pocket->capacity - 1, ITEM_NONE, 0);
    MigrateInfiniteHeldItems();
    EXPECT(CheckBagHasItem(ITEM_NORMALITE, 1));
    EXPECT(FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));
}

TEST("Infinite held item migration does not replace an unexchanged Red Scale")
{
    struct BagPocket *megaStonesPocket = &gBagPockets[POCKET_MEGASTONES];
    struct BagPocket *keyItemsPocket = &gBagPockets[POCKET_KEY_ITEMS];

    memset(megaStonesPocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));
    memset(keyItemsPocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.keyItems));
    FlagClear(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
    FlagSet(FLAG_HIDE_LAKE_OF_RAGE_GYARADOS);
    VarSet(VAR_NEWBARKTOWN_LABSTATE, 0);
    EXPECT(AddBagItem(ITEM_RED_SCALE, 1));

    MigrateInfiniteHeldItems();

    EXPECT(CheckBagHasItem(ITEM_RED_SCALE, 1));
    EXPECT(!CheckBagHasItem(ITEM_FAIRYTITE, 1));
    EXPECT(FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));
}

TEST("Infinite held item migration waits until the normal bag is active")
{
    struct BagPocket *pocket = &gBagPockets[POCKET_MEGASTONES];

    memset(pocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.megaStones));
    FlagClear(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE);
    FlagSet(FLAG_ITEM_TOHJOFALLS_HEART_SCALE);
    FlagSet(FLAG_STORING_ITEMS_IN_PYRAMID_BAG);

    MigrateInfiniteHeldItems();
    EXPECT(!CheckBagHasItem(ITEM_NORMALITE, 1));
    EXPECT(!FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));

    FlagClear(FLAG_STORING_ITEMS_IN_PYRAMID_BAG);
    MigrateInfiniteHeldItems();
    EXPECT(CheckBagHasItem(ITEM_NORMALITE, 1));
    EXPECT(FlagGet(FLAG_INFINITE_HELD_ITEMS_MIGRATION_COMPLETE));
}

TEST("TMs and HMs are sorted correctly in the bag")
{
    struct BagPocket *pocket = &gBagPockets[POCKET_TM_HM];

    ASSUME(GetItemPocket(ITEM_HM07) == POCKET_TM_HM);
    ASSUME(GetItemPocket(ITEM_TM25) == POCKET_TM_HM);
    ASSUME(GetItemPocket(ITEM_TM14) == POCKET_TM_HM);
    ASSUME(GetItemPocket(ITEM_TM42) == POCKET_TM_HM);
    ASSUME(GetItemPocket(ITEM_HM05) == POCKET_TM_HM);
    ASSUME(GetItemPocket(ITEM_TM05) == POCKET_TM_HM);
    ASSUME(GetItemPocket(ITEM_TM01) == POCKET_TM_HM);
    ASSUME(GetItemPocket(ITEM_HM02) == POCKET_TM_HM);

    /*
     * Note: I would add a test to make sure that TMs are sorted correctly by move name,
     * but downstream users are likely to rearrange TMs so this would just be a nuisance.
     */

    RUN_OVERWORLD_SCRIPT(
        additem ITEM_HM07;
        additem ITEM_TM25;
        additem ITEM_TM14;
        additem ITEM_TM42;
        additem ITEM_HM05;
        additem ITEM_TM05;
        additem ITEM_TM01;
        additem ITEM_HM02;
    );

    SortItemsInBag(&gBagPockets[POCKET_TM_HM], SORT_BY_INDEX);

    EXPECT_EQ(pocket->itemSlots[0].itemId, ITEM_TM01);
    EXPECT_EQ(pocket->itemSlots[1].itemId, ITEM_TM05);
    EXPECT_EQ(pocket->itemSlots[2].itemId, ITEM_TM14);
    EXPECT_EQ(pocket->itemSlots[3].itemId, ITEM_TM25);
    EXPECT_EQ(pocket->itemSlots[4].itemId, ITEM_TM42);
    EXPECT_EQ(pocket->itemSlots[5].itemId, ITEM_HM02);
    EXPECT_EQ(pocket->itemSlots[6].itemId, ITEM_HM05);
    EXPECT_EQ(pocket->itemSlots[7].itemId, ITEM_HM07);
    EXPECT_EQ(pocket->itemSlots[8].itemId, ITEM_NONE);
}

TEST("Berries are sorted correctly in the bag")
{
    struct BagPocket *pocket = &gBagPockets[POCKET_BERRIES];

    ASSUME(GetItemPocket(ITEM_POMEG_BERRY) == POCKET_BERRIES);
    ASSUME(GetItemPocket(ITEM_MAGOST_BERRY) == POCKET_BERRIES);
    ASSUME(GetItemPocket(ITEM_KELPSY_BERRY) == POCKET_BERRIES);
    ASSUME(GetItemPocket(ITEM_MICLE_BERRY) == POCKET_BERRIES);
    ASSUME(GetItemPocket(ITEM_CHARTI_BERRY) == POCKET_BERRIES);
    ASSUME(GetItemPocket(ITEM_GANLON_BERRY) == POCKET_BERRIES);
    ASSUME(GetItemPocket(ITEM_ORAN_BERRY) == POCKET_BERRIES);
    ASSUME(GetItemPocket(ITEM_CHERI_BERRY) == POCKET_BERRIES);

    RUN_OVERWORLD_SCRIPT(
        additem ITEM_POMEG_BERRY;
        additem ITEM_MAGOST_BERRY;
        additem ITEM_KELPSY_BERRY;
        additem ITEM_MICLE_BERRY;
        additem ITEM_CHARTI_BERRY;
        additem ITEM_GANLON_BERRY;
        additem ITEM_ORAN_BERRY;
        additem ITEM_CHERI_BERRY;
    );

    SortItemsInBag(&gBagPockets[POCKET_BERRIES], SORT_BY_INDEX);

    EXPECT_EQ(pocket->itemSlots[0].itemId, ITEM_CHERI_BERRY);
    EXPECT_EQ(pocket->itemSlots[1].itemId, ITEM_ORAN_BERRY);
    EXPECT_EQ(pocket->itemSlots[2].itemId, ITEM_POMEG_BERRY);
    EXPECT_EQ(pocket->itemSlots[3].itemId, ITEM_KELPSY_BERRY);
    EXPECT_EQ(pocket->itemSlots[4].itemId, ITEM_MAGOST_BERRY);
    EXPECT_EQ(pocket->itemSlots[5].itemId, ITEM_CHARTI_BERRY);
    EXPECT_EQ(pocket->itemSlots[6].itemId, ITEM_GANLON_BERRY);
    EXPECT_EQ(pocket->itemSlots[7].itemId, ITEM_MICLE_BERRY);
    EXPECT_EQ(pocket->itemSlots[8].itemId, ITEM_NONE);

    SortItemsInBag(&gBagPockets[POCKET_BERRIES], SORT_ALPHABETICALLY);

    EXPECT_EQ(pocket->itemSlots[0].itemId, ITEM_CHARTI_BERRY);
    EXPECT_EQ(pocket->itemSlots[1].itemId, ITEM_CHERI_BERRY);
    EXPECT_EQ(pocket->itemSlots[2].itemId, ITEM_GANLON_BERRY);
    EXPECT_EQ(pocket->itemSlots[3].itemId, ITEM_KELPSY_BERRY);
    EXPECT_EQ(pocket->itemSlots[4].itemId, ITEM_MAGOST_BERRY);
    EXPECT_EQ(pocket->itemSlots[5].itemId, ITEM_MICLE_BERRY);
    EXPECT_EQ(pocket->itemSlots[6].itemId, ITEM_ORAN_BERRY);
    EXPECT_EQ(pocket->itemSlots[7].itemId, ITEM_POMEG_BERRY);
    EXPECT_EQ(pocket->itemSlots[8].itemId, ITEM_NONE);
}

TEST("Items are correctly sorted and compacted in the bag")
{
    struct BagPocket *pocket = &gBagPockets[POCKET_ITEMS];
    memset(pocket->itemSlots, 0, sizeof(gSaveBlock1Ptr->bag.items));

    ASSUME(GetItemPocket(ITEM_NUGGET) == POCKET_ITEMS);
    ASSUME(GetItemPocket(ITEM_BIG_NUGGET) == POCKET_ITEMS);
    ASSUME(GetItemPocket(ITEM_TINY_MUSHROOM) == POCKET_ITEMS);
    ASSUME(GetItemPocket(ITEM_BIG_MUSHROOM) == POCKET_ITEMS);
    ASSUME(GetItemPocket(ITEM_PEARL) == POCKET_ITEMS);
    ASSUME(GetItemPocket(ITEM_BIG_PEARL) == POCKET_ITEMS);

    RUN_OVERWORLD_SCRIPT(
        additem ITEM_NUGGET;
        additem ITEM_BIG_NUGGET;
        additem ITEM_TINY_MUSHROOM;
        additem ITEM_BIG_MUSHROOM;
        additem ITEM_PEARL;
        additem ITEM_BIG_PEARL;
    );

    EXPECT_EQ(pocket->itemSlots[0].itemId, ITEM_NUGGET);
    EXPECT_EQ(pocket->itemSlots[0].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[1].itemId, ITEM_BIG_NUGGET);
    EXPECT_EQ(pocket->itemSlots[1].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[2].itemId, ITEM_TINY_MUSHROOM);
    EXPECT_EQ(pocket->itemSlots[2].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[3].itemId, ITEM_BIG_MUSHROOM);
    EXPECT_EQ(pocket->itemSlots[3].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[4].itemId, ITEM_PEARL);
    EXPECT_EQ(pocket->itemSlots[4].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[5].itemId, ITEM_BIG_PEARL);
    EXPECT_EQ(pocket->itemSlots[5].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[6].itemId, ITEM_NONE);

    SortItemsInBag(&gBagPockets[POCKET_ITEMS], SORT_ALPHABETICALLY);

    EXPECT_EQ(pocket->itemSlots[0].itemId, ITEM_BIG_MUSHROOM);
    EXPECT_EQ(pocket->itemSlots[1].itemId, ITEM_BIG_NUGGET);
    EXPECT_EQ(pocket->itemSlots[2].itemId, ITEM_BIG_PEARL);
    EXPECT_EQ(pocket->itemSlots[3].itemId, ITEM_NUGGET);
    EXPECT_EQ(pocket->itemSlots[4].itemId, ITEM_PEARL);
    EXPECT_EQ(pocket->itemSlots[5].itemId, ITEM_TINY_MUSHROOM);
    EXPECT_EQ(pocket->itemSlots[6].itemId, ITEM_NONE);

    // Try removing the big items, check that everything is compacted correctly

    RUN_OVERWORLD_SCRIPT(
        removeitem ITEM_BIG_NUGGET;
        removeitem ITEM_BIG_MUSHROOM;
        removeitem ITEM_BIG_PEARL;
    );

    CompactItemsInBagPocket(POCKET_ITEMS);

    EXPECT_EQ(pocket->itemSlots[0].itemId, ITEM_NUGGET);
    EXPECT_EQ(pocket->itemSlots[0].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[1].itemId, ITEM_PEARL);
    EXPECT_EQ(pocket->itemSlots[1].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[2].itemId, ITEM_TINY_MUSHROOM);
    EXPECT_EQ(pocket->itemSlots[2].quantity, 1);
    EXPECT_EQ(pocket->itemSlots[3].itemId, ITEM_NONE);
    EXPECT_EQ(pocket->itemSlots[4].itemId, ITEM_NONE);
    EXPECT_EQ(pocket->itemSlots[5].itemId, ITEM_NONE);
    EXPECT_EQ(pocket->itemSlots[6].itemId, ITEM_NONE);
}
