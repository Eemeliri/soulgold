#include "global.h"
#include "agb_flash.h"
#include "gba/flash_internal.h"
#include "malloc.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "test/test.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
#define T_SAVEBLOCK1_SIZE 15444
#define T_SAVEBLOCK2_SIZE 2864
#define T_SAVEBLOCK3_SIZE 100
#define T_POKEMON_SECURE_DATA_SIZE 44
#define T_BOX_POKEMON_SIZE 76
#define T_POKEMON_SIZE 96
#define T_POKEMONSTORAGE_SIZE 37036
#define T_POKEMONSTORAGE_LEGACY_SIZE 34740
#define T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE (T_POKEMONSTORAGE_LEGACY_SIZE - SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START))
#define T_VS_SEEKER_SAVE_MAGIC_OFFSET 11109
#define T_VS_SEEKER_CHARGE_STEPS_OFFSET 11110
#define T_VS_SEEKER_SAVE_MAGIC_INV_OFFSET 11120

static void FillPokemonStoragePattern(u8 seed)
{
    u32 i;
    u8 *storage = (u8 *)gPokemonStoragePtr;

    for (i = 0; i < sizeof(*gPokemonStoragePtr); i++)
        storage[i] = seed + i * 37 + (i >> 8);

    gPokemonStoragePtr->currentBox = seed % TOTAL_BOXES_COUNT;
    gPokemonStoragePtr->boxExtensionMagic = POKEMON_STORAGE_EXTENSION_MAGIC;
}

static u16 CalculateTestSaveChecksum(void *data, u16 size)
{
    u16 i;
    u32 checksum = 0;

    for (i = 0; i < size / sizeof(u32); i++)
    {
        checksum += *(u32 *)data;
        data += sizeof(u32);
    }

    return (checksum >> 16) + checksum;
}

static void ResetPokemonStorageTestFlash(void)
{
    // A chip erase is equivalent here and substantially faster than the
    // production ClearSaveData path, which erases all 32 sectors individually.
    EXPECT_EQ(EraseFlashChip(), 0);
    Save_ResetSaveCounters();
}

TEST("SaveBlock1 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), T_SAVEBLOCK1_SIZE);
    EXPECT_EQ(offsetof(struct SaveBlock1, vsSeekerSaveMagic), T_VS_SEEKER_SAVE_MAGIC_OFFSET);
    EXPECT_EQ(offsetof(struct SaveBlock1, vsSeekerChargeSteps), T_VS_SEEKER_CHARGE_STEPS_OFFSET);
    EXPECT_EQ(offsetof(struct SaveBlock1, vsSeekerSaveMagicInv), T_VS_SEEKER_SAVE_MAGIC_INV_OFFSET);
}

TEST("SaveBlock2 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock2), T_SAVEBLOCK2_SIZE);
}

TEST("SaveBlock3 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock3), T_SAVEBLOCK3_SIZE);
}

TEST("PokemonStorage is backwards compatible")
{
    EXPECT_EQ(TOTAL_BOXES_COUNT, 16);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxes), 4);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxNames), 34204);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxWallpapers), 34339);
    EXPECT_EQ(offsetof(struct PokemonStorage, fusions), 34356);
    EXPECT_EQ(offsetof(struct PokemonStorage, boxExtensionMagic), 34740);
    EXPECT_EQ(sizeof(struct PokemonStorage), T_POKEMONSTORAGE_SIZE);
}

TEST("PokemonStorage routes box 16 through the extension")
{
    u32 boxId;
    u32 boxPosition;

    ResetPokemonStorageSystem();

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            struct BoxPokemon *expected;

            if (boxId < LEGACY_BOXES_COUNT)
                expected = &gPokemonStoragePtr->legacyBoxes[boxId][boxPosition];
            else
                expected = &gPokemonStoragePtr->extraBox[boxPosition];

            EXPECT_EQ((uintptr_t)GetBoxedMonPtr(boxId, boxPosition), (uintptr_t)expected);
        }

        if (boxId < LEGACY_BOXES_COUNT)
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->legacyBoxNames[boxId]);
        else
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->extraBoxName);
    }

    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
}

TEST("PokemonStorage extension initialization preserves all legacy bytes")
{
    void *legacyData;

    FillPokemonStoragePattern(0x51);
    legacyData = Alloc(T_POKEMONSTORAGE_LEGACY_SIZE);
    memcpy(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE);

    InitPokemonStorageExtension();

    EXPECT_EQ(memcmp(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    Free(legacyData);
}

TEST("PokemonStorage survives a real flash save and load byte for byte")
{
    struct PokemonStorage *expected;

    gTestRunnerState.timeoutSeconds = 120;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x27);
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));

    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);

    Free(expected);
}

TEST("PokemonStorage loads a legacy save and initializes only box 16")
{
    struct SaveSector *lastStorageSector;
    u8 *legacyData;
    u16 physicalSector;

    gTestRunnerState.timeoutSeconds = 120;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x63);

    legacyData = Alloc(T_POKEMONSTORAGE_LEGACY_SIZE);
    memcpy(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    // Convert the newly written last storage sector to the old 34,740-byte
    // format: no extension marker/data and a checksum over the legacy bytes.
    physicalSector = (SECTOR_ID_PKMN_STORAGE_END + gLastWrittenSector) % NUM_SECTORS_PER_SLOT;
    physicalSector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);
    lastStorageSector = Alloc(sizeof(*lastStorageSector));
    ReadFlash(physicalSector, 0, (u8 *)lastStorageSector, sizeof(*lastStorageSector));
    memset(&lastStorageSector->data[T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE],
           0,
           SECTOR_DATA_SIZE - T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE);
    lastStorageSector->checksum = CalculateTestSaveChecksum(lastStorageSector->data, T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE);
    EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)lastStorageSector), 0);
    EXPECT_EQ(EraseFlashSector(SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + (gSaveCounter % NUM_SAVE_SLOTS)), 0);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);

    Free(lastStorageSector);
    Free(legacyData);
}

TEST("PokemonStorage falls back when the newest overflow sector is lost")
{
    struct PokemonStorage *previousSave;
    u8 newestOverflowSector;

    // This test performs a chip erase, two full saves, and a sector erase.
    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x19);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    FillPokemonStoragePattern(0xA4);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    newestOverflowSector = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + (gSaveCounter % NUM_SAVE_SLOTS);
    EXPECT_EQ(EraseFlashSector(newestOverflowSector), 0);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(previousSave);
}

TEST("Pokemon save structs are expected sizes")
{
    EXPECT_EQ(sizeof(struct PokemonSecureData), T_POKEMON_SECURE_DATA_SIZE);
    EXPECT_EQ(sizeof(struct BoxPokemon), T_BOX_POKEMON_SIZE);
    EXPECT_EQ(sizeof(struct Pokemon), T_POKEMON_SIZE);
}

#undef T_SAVEBLOCK1_SIZE
#undef T_SAVEBLOCK2_SIZE
#undef T_SAVEBLOCK3_SIZE
#undef T_POKEMON_SECURE_DATA_SIZE
#undef T_BOX_POKEMON_SIZE
#undef T_POKEMON_SIZE
#undef T_POKEMONSTORAGE_SIZE
#undef T_POKEMONSTORAGE_LEGACY_SIZE
#undef T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE
#undef T_VS_SEEKER_SAVE_MAGIC_OFFSET
#undef T_VS_SEEKER_CHARGE_STEPS_OFFSET
#undef T_VS_SEEKER_SAVE_MAGIC_INV_OFFSET
