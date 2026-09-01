#include "global.h"
#include "item.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"

static struct BoxPokemon *CreateStorageTestMon(u8 boxId, u8 boxPosition, u16 species, bool8 isEgg)
{
    struct BoxPokemon *boxMon = GetBoxedMonPtr(boxId, boxPosition);

    CreateBoxMon(boxMon, species, 5, 0, OTID_STRUCT_PLAYER_ID);
    if (isEgg)
        SetBoxMonData(boxMon, MON_DATA_IS_EGG, &isEgg);
    return boxMon;
}

static void ResetStorageTestMons(u8 partyCount)
{
    u8 boxId;
    u8 boxPosition;
    u8 partyPosition;

    for (partyPosition = 0; partyPosition < PARTY_SIZE; partyPosition++)
        ZeroMonData(&gPlayerParty[partyPosition]);
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
            ZeroBoxMonAt(boxId, boxPosition);
    }
    for (partyPosition = 0; partyPosition < partyCount; partyPosition++)
        CreateMon(&gPlayerParty[partyPosition], SPECIES_PIKACHU, 5, 0, OTID_STRUCT_PLAYER_ID);

    ClearBag();
}

static void FillMedicinePocket(enum Item item, u16 quantity)
{
    struct BagPocket *pocket = &gBagPockets[POCKET_MEDICINE];
    u16 slot;

    for (slot = 0; slot < pocket->capacity; slot++)
        BagPocket_SetSlotItemIdAndCount(pocket, slot, item, quantity);
}

TEST("Pokemon Storage clears a stale deferred palette destination before enabling VBlank")
{
    EXPECT(PokemonStorageSystem_TestClearsStalePaletteSwapDestination());
}

TEST("Bulk storage Egg release preserves non-Egg Pokemon")
{
    u8 boxId = TOTAL_BOXES_COUNT - 1;

    ResetStorageTestMons(2);
    CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    CreateStorageTestMon(boxId, 1, SPECIES_CHARMANDER, TRUE);
    CreateStorageTestMon(boxId, IN_BOX_COUNT - 1, SPECIES_SQUIRTLE, TRUE);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, TRUE, FALSE), 2);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 1, MON_DATA_SPECIES), SPECIES_NONE);
    EXPECT_EQ(GetBoxMonDataAt(boxId, IN_BOX_COUNT - 1, MON_DATA_SPECIES), SPECIES_NONE);
}

TEST("Bulk storage whole Box release removes Pokemon and Eggs only from its target Box")
{
    u8 boxId = TOTAL_BOXES_COUNT - 1;
    u8 otherBoxId = boxId == 0 ? 1 : 0;

    ResetStorageTestMons(2);
    CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    CreateStorageTestMon(boxId, 1, SPECIES_CHARMANDER, TRUE);
    CreateStorageTestMon(otherBoxId, 0, SPECIES_SQUIRTLE, FALSE);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, FALSE), 2);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_NONE);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 1, MON_DATA_SPECIES), SPECIES_NONE);
    EXPECT_EQ(GetBoxMonDataAt(otherBoxId, 0, MON_DATA_SPECIES), SPECIES_SQUIRTLE);
}

TEST("Bulk storage release is a no-op when no Pokemon match")
{
    u8 boxId = TOTAL_BOXES_COUNT - 1;

    ResetStorageTestMons(2);
    CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, TRUE, FALSE), 0);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
}

TEST("Bulk storage release messages fit the storage message window")
{
    EXPECT(PokemonStorageSystem_TestBulkReleaseMessagesFit());
}

TEST("Bulk storage release is hidden while carrying an item or selecting a Pokemon")
{
    EXPECT(PokemonStorageSystem_TestGuardsBoxReleaseMenu());
}

TEST("Bulk storage release preserves two Pokemon including a held Pokemon")
{
    u8 boxId = TOTAL_BOXES_COUNT - 1;

    ResetStorageTestMons(1);
    CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    CreateStorageTestMon(boxId, 1, SPECIES_CHARMANDER, FALSE);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, FALSE), 0);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 1, MON_DATA_SPECIES), SPECIES_CHARMANDER);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, TRUE), 2);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_NONE);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 1, MON_DATA_SPECIES), SPECIES_NONE);
}

TEST("Bulk storage release refuses a selection containing Mail")
{
    enum Item mail = ITEM_ORANGE_MAIL;
    u8 boxId = TOTAL_BOXES_COUNT - 1;
    struct BoxPokemon *boxMon;

    ResetStorageTestMons(2);
    boxMon = CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &mail);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, FALSE), 0);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_HELD_ITEM), ITEM_ORANGE_MAIL);
}

#if OW_PC_RELEASE_ITEM >= GEN_8
TEST("Bulk storage release returns multiple held items to the Bag")
{
    enum Item potion = ITEM_POTION;
    enum Item antidote = ITEM_ANTIDOTE;
    u8 boxId = TOTAL_BOXES_COUNT - 1;
    struct BoxPokemon *boxMon;

    ResetStorageTestMons(2);
    boxMon = CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &potion);
    boxMon = CreateStorageTestMon(boxId, 1, SPECIES_CHARMANDER, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &antidote);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, FALSE), 2);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_NONE);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 1, MON_DATA_SPECIES), SPECIES_NONE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POTION), 1);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ANTIDOTE), 1);
}

TEST("Bulk storage release aborts when a held item's pocket is full")
{
    enum Item item = ITEM_POTION;
    u8 boxId = TOTAL_BOXES_COUNT - 1;
    struct BoxPokemon *boxMon;

    ResetStorageTestMons(2);
    FillMedicinePocket(ITEM_POTION, MAX_BAG_ITEM_CAPACITY);
    boxMon = CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &item);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, FALSE), 0);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_HELD_ITEM), ITEM_POTION);
    EXPECT_EQ(GetFreeSpaceForItemInBag(ITEM_POTION), 0);
}

TEST("Bulk storage release reserves aggregate capacity for repeated items")
{
    enum Item item = ITEM_POTION;
    struct BagPocket *pocket = &gBagPockets[POCKET_MEDICINE];
    u8 boxId = TOTAL_BOXES_COUNT - 1;
    struct BoxPokemon *boxMon;

    ResetStorageTestMons(2);
    FillMedicinePocket(ITEM_POTION, MAX_BAG_ITEM_CAPACITY);
    BagPocket_SetSlotItemIdAndCount(pocket, 0, ITEM_POTION, MAX_BAG_ITEM_CAPACITY - 1);
    boxMon = CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &item);
    boxMon = CreateStorageTestMon(boxId, 1, SPECIES_CHARMANDER, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &item);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, FALSE), 0);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 1, MON_DATA_SPECIES), SPECIES_CHARMANDER);
    EXPECT_EQ(GetFreeSpaceForItemInBag(ITEM_POTION), 1);
}

TEST("Bulk storage release reserves shared empty slots for different items")
{
    enum Item antidote = ITEM_ANTIDOTE;
    enum Item paralyzeHeal = ITEM_PARALYZE_HEAL;
    struct BagPocket *pocket = &gBagPockets[POCKET_MEDICINE];
    u8 boxId = TOTAL_BOXES_COUNT - 1;
    struct BoxPokemon *boxMon;

    ResetStorageTestMons(2);
    FillMedicinePocket(ITEM_POTION, MAX_BAG_ITEM_CAPACITY);
    BagPocket_SetSlotItemIdAndCount(pocket, 0, ITEM_NONE, 0);
    boxMon = CreateStorageTestMon(boxId, 0, SPECIES_BULBASAUR, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &antidote);
    boxMon = CreateStorageTestMon(boxId, 1, SPECIES_CHARMANDER, FALSE);
    SetBoxMonData(boxMon, MON_DATA_HELD_ITEM, &paralyzeHeal);

    EXPECT_EQ(PokemonStorageSystem_TestReleaseBox(boxId, FALSE, FALSE), 0);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetBoxMonDataAt(boxId, 1, MON_DATA_SPECIES), SPECIES_CHARMANDER);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ANTIDOTE), 0);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_PARALYZE_HEAL), 0);
}
#endif
