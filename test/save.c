#include "global.h"
#include "agb_flash.h"
#include "event_data.h"
#include "gba/flash_internal.h"
#include "malloc.h"
#include "pokemon.h"
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
#define T_POKEMONSTORAGE_SIZE 39336
#define T_POKEMONSTORAGE_LEGACY_SIZE 34740
#define T_POKEMONSTORAGE_BX16_SIZE 37036
#define T_POKEMONSTORAGE_REGULAR_SIZE (SECTOR_DATA_SIZE * 9)
#define T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE (T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE)
#define T_POKEMONSTORAGE_OVERFLOW_SIZE (T_POKEMONSTORAGE_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE)
#define T_POKEMONSTORAGE_BX17_OVERFLOW_OFFSET (T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE)
#define T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE (T_POKEMONSTORAGE_LEGACY_SIZE - SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START))

static const u8 ALIGNED(4) sLegacyReleaseSave[] = INCBIN_U8("test/fixtures/save/legacy-release.sav");
static const u8 ALIGNED(4) sBx16ReleaseSave[] = INCBIN_U8("test/fixtures/save/bx16-release.sav");

STATIC_ASSERT(sizeof(sLegacyReleaseSave) == SECTORS_COUNT * SECTOR_SIZE, LegacyReleaseSaveFixtureSize);
STATIC_ASSERT(sizeof(sBx16ReleaseSave) == SECTORS_COUNT * SECTOR_SIZE, Bx16ReleaseSaveFixtureSize);

static const u16 sFrozenFixtureSpecies[] =
{
    SPECIES_BULBASAUR,
    SPECIES_CHARMANDER,
    SPECIES_SQUIRTLE,
    SPECIES_PIKACHU,
    SPECIES_EEVEE,
    SPECIES_CHIKORITA,
    SPECIES_CYNDAQUIL,
    SPECIES_TOTODILE,
    SPECIES_TREECKO,
    SPECIES_TORCHIC,
    SPECIES_MUDKIP,
    SPECIES_TURTWIG,
    SPECIES_CHIMCHAR,
    SPECIES_PIPLUP,
    SPECIES_SNIVY,
    SPECIES_TEPIG,
};

static const u8 sLegacyFixtureNames[LEGACY_BOXES_COUNT][BOX_NAME_LENGTH + 1] =
{
    COMPOUND_STRING("LEGBOX01"),
    COMPOUND_STRING("LEGBOX02"),
    COMPOUND_STRING("LEGBOX03"),
    COMPOUND_STRING("LEGBOX04"),
    COMPOUND_STRING("LEGBOX05"),
    COMPOUND_STRING("LEGBOX06"),
    COMPOUND_STRING("LEGBOX07"),
    COMPOUND_STRING("LEGBOX08"),
    COMPOUND_STRING("LEGBOX09"),
    COMPOUND_STRING("LEGBOX10"),
    COMPOUND_STRING("LEGBOX11"),
    COMPOUND_STRING("LEGBOX12"),
    COMPOUND_STRING("LEGBOX13"),
    COMPOUND_STRING("LEGBOX14"),
    COMPOUND_STRING("LEGBOX15"),
};

static const u8 sBx16FixtureNames[LEGACY_BOXES_COUNT + 1][BOX_NAME_LENGTH + 1] =
{
    COMPOUND_STRING("RELBOX01"),
    COMPOUND_STRING("RELBOX02"),
    COMPOUND_STRING("RELBOX03"),
    COMPOUND_STRING("RELBOX04"),
    COMPOUND_STRING("RELBOX05"),
    COMPOUND_STRING("RELBOX06"),
    COMPOUND_STRING("RELBOX07"),
    COMPOUND_STRING("RELBOX08"),
    COMPOUND_STRING("RELBOX09"),
    COMPOUND_STRING("RELBOX10"),
    COMPOUND_STRING("RELBOX11"),
    COMPOUND_STRING("RELBOX12"),
    COMPOUND_STRING("RELBOX13"),
    COMPOUND_STRING("RELBOX14"),
    COMPOUND_STRING("RELBOX15"),
    COMPOUND_STRING("RELBOX16"),
};

static u16 CalculateTestSaveChecksum(void *data, u16 size);
static void ResetPokemonStorageTestFlash(void);

static bool32 IsErasedFixtureSector(const u8 *sectorData)
{
    u32 i;

    for (i = 0; i < SECTOR_SIZE; i++)
    {
        if (sectorData[i] != 0xFF)
            return FALSE;
    }

    return TRUE;
}

static void LoadFrozenSaveFixture(const u8 *fixture)
{
    u8 *sectorData;
    u32 sector;

    ResetPokemonStorageTestFlash();
    sectorData = Alloc(SECTOR_SIZE);
    for (sector = 0; sector < SECTORS_COUNT; sector++)
    {
        const u8 *fixtureSector = &fixture[sector * SECTOR_SIZE];

        if (IsErasedFixtureSector(fixtureSector))
            continue;

        memcpy(sectorData, fixtureSector, SECTOR_SIZE);
        EXPECT_EQ(ProgramFlashSectorAndVerify(sector, sectorData), 0);
    }
    Free(sectorData);
    Save_ResetSaveCounters();
}

static const struct SaveSector *FindFrozenSaveSector(const u8 *fixture, u16 sectorId)
{
    u32 sector;

    for (sector = 0; sector < SECTORS_COUNT; sector++)
    {
        const struct SaveSector *saveSector = (const struct SaveSector *)&fixture[sector * SECTOR_SIZE];

        if (saveSector->signature == SECTOR_SIGNATURE && saveSector->id == sectorId)
            return saveSector;
    }

    return NULL;
}

static void CopyFrozenStoragePrefix(const u8 *fixture, void *destination, u32 size)
{
    u8 *dest = destination;
    u32 sectorId;

    for (sectorId = SECTOR_ID_PKMN_STORAGE_START; sectorId <= SECTOR_ID_PKMN_STORAGE_END && size != 0; sectorId++)
    {
        const struct SaveSector *saveSector = FindFrozenSaveSector(fixture, sectorId);
        u32 copySize = min(size, (u32)SECTOR_DATA_SIZE);

        EXPECT(saveSector != NULL);
        if (saveSector == NULL)
            return;

        memcpy(dest, saveSector->data, copySize);
        dest += copySize;
        size -= copySize;
    }

    if (size != 0)
    {
        const struct SaveSector *saveSector = FindFrozenSaveSector(fixture, SECTOR_ID_PKMN_STORAGE_OVERFLOW_1);

        if (saveSector == NULL)
            saveSector = FindFrozenSaveSector(fixture, SECTOR_ID_PKMN_STORAGE_OVERFLOW_2);
        EXPECT(saveSector != NULL);
        if (saveSector == NULL)
            return;

        memcpy(dest, saveSector->data, size);
        size = 0;
    }

    EXPECT_EQ(size, 0);
}

static void VerifyFrozenStorageContents(u32 boxCount,
                                        const u8 (*boxNames)[BOX_NAME_LENGTH + 1],
                                        u32 personalityBase,
                                        u32 otIdBase,
                                        u32 fusionPersonalityBase,
                                        u32 fusionOtIdBase)
{
    u32 box;
    u32 position;

    EXPECT_EQ(StorageGetCurrentBox(), boxCount - 1);
    for (box = 0; box < boxCount; box++)
    {
        EXPECT_EQ(memcmp(GetBoxNamePtr(box), boxNames[box], BOX_NAME_LENGTH + 1), 0);
        EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(box), box);
        for (position = 0; position < IN_BOX_COUNT; position++)
        {
            EXPECT_EQ(GetBoxMonDataAt(box, position, MON_DATA_SPECIES), sFrozenFixtureSpecies[box]);
            EXPECT_EQ(GetBoxMonDataAt(box, position, MON_DATA_PERSONALITY),
                      personalityBase + box * IN_BOX_COUNT + position);
            EXPECT_EQ(GetBoxMonDataAt(box, position, MON_DATA_OT_ID), otIdBase + box);
        }
    }

    for (position = 0; position < MAX_FUSION_STORAGE; position++)
    {
        EXPECT_EQ(GetMonData(&gPokemonStoragePtr->fusions[position], MON_DATA_SPECIES), sFrozenFixtureSpecies[position]);
        EXPECT_EQ(GetMonData(&gPokemonStoragePtr->fusions[position], MON_DATA_PERSONALITY), fusionPersonalityBase + position);
        EXPECT_EQ(GetMonData(&gPokemonStoragePtr->fusions[position], MON_DATA_OT_ID), fusionOtIdBase + position);
    }
}

static void FillPokemonStoragePattern(u8 seed)
{
    u32 i;
    u8 *storage = (u8 *)gPokemonStoragePtr;

    for (i = 0; i < sizeof(*gPokemonStoragePtr); i++)
        storage[i] = seed + i * 37 + (i >> 8);

    gPokemonStoragePtr->currentBox = seed % TOTAL_BOXES_COUNT;
    gPokemonStoragePtr->boxExtensionMagic = POKEMON_STORAGE_EXTENSION_MAGIC;
    gPokemonStoragePtr->box17ExtensionMagic = POKEMON_STORAGE_BOX17_MAGIC;
    gPokemonStoragePtr->box17Checksum = CalculateTestSaveChecksum(
        &gPokemonStoragePtr->box17,
        sizeof(*gPokemonStoragePtr) - offsetof(struct PokemonStorage, box17));
    gPokemonStoragePtr->box17ChecksumInverse = (u16)~gPokemonStoragePtr->box17Checksum;
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

static u8 GetNewestOverflowSectorId(void)
{
    return SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + (gSaveCounter % NUM_SAVE_SLOTS);
}

static void ReadNewestOverflowSector(struct SaveSector *sector)
{
    ReadFlash(GetNewestOverflowSectorId(), 0, (u8 *)sector, sizeof(*sector));
}

static void WriteNewestOverflowSector(struct SaveSector *sector)
{
    EXPECT_EQ(ProgramFlashSectorAndVerify(GetNewestOverflowSectorId(), (u8 *)sector), 0);
}

static void ConvertNewestOverflowToBx16(struct SaveSector *sector)
{
    ReadNewestOverflowSector(sector);
    memset(&sector->data[T_POKEMONSTORAGE_BX17_OVERFLOW_OFFSET],
           0,
           SECTOR_DATA_SIZE - T_POKEMONSTORAGE_BX17_OVERFLOW_OFFSET);
    sector->checksum = CalculateTestSaveChecksum(sector->data, T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE);
    WriteNewestOverflowSector(sector);
}

static void RunLinkFullSave(void)
{
    EXPECT(!LinkFullSave_Init());
    while (!LinkFullSave_WriteSector())
        ;
    EXPECT(!LinkFullSave_ReplaceLastSector());
    EXPECT(!LinkFullSave_SetLastSectorSignature());
    EXPECT_EQ(gDamagedSaveSectors, 0);
}

TEST("SaveBlock1 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), T_SAVEBLOCK1_SIZE);
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
    EXPECT_EQ(LEGACY_BOXES_COUNT, 15);
    EXPECT_EQ(TOTAL_BOXES_COUNT, 17);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxes), 4);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxNames), 34204);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxWallpapers), 34339);
    EXPECT_EQ(offsetof(struct PokemonStorage, fusions), 34356);
    EXPECT_EQ(offsetof(struct PokemonStorage, boxExtensionMagic), 34740);
    EXPECT_EQ(offsetof(struct PokemonStorage, extraBox), 34744);
    EXPECT_EQ(offsetof(struct PokemonStorage, extraBoxName), 37024);
    EXPECT_EQ(offsetof(struct PokemonStorage, extraBoxWallpaper), 37033);
    EXPECT_EQ(offsetof(struct PokemonStorage, box17ExtensionMagic), 37036);
    EXPECT_EQ(offsetof(struct PokemonStorage, box17Checksum), 37040);
    EXPECT_EQ(offsetof(struct PokemonStorage, box17ChecksumInverse), 37042);
    EXPECT_EQ(offsetof(struct PokemonStorage, box17), 37044);
    EXPECT_EQ(offsetof(struct PokemonStorage, box17Name), 39324);
    EXPECT_EQ(offsetof(struct PokemonStorage, box17Wallpaper), 39333);
    EXPECT_EQ(sizeof(struct PokemonStorage), T_POKEMONSTORAGE_SIZE);
    EXPECT_EQ(T_POKEMONSTORAGE_REGULAR_SIZE, 35712);
    EXPECT_EQ(T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE, 1324);
    EXPECT_EQ(T_POKEMONSTORAGE_OVERFLOW_SIZE, 3624);
    EXPECT_EQ(SECTOR_DATA_SIZE - T_POKEMONSTORAGE_OVERFLOW_SIZE, 344);
}

TEST("PokemonStorage routes boxes 16 and 17 through distinct extensions")
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
            else if (boxId == LEGACY_BOXES_COUNT)
                expected = &gPokemonStoragePtr->extraBox[boxPosition];
            else
                expected = &gPokemonStoragePtr->box17[boxPosition];

            EXPECT_EQ((uintptr_t)GetBoxedMonPtr(boxId, boxPosition), (uintptr_t)expected);
        }

        if (boxId < LEGACY_BOXES_COUNT)
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->legacyBoxNames[boxId]);
        else if (boxId == LEGACY_BOXES_COUNT)
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->extraBoxName);
        else
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->box17Name);
    }

    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);
    EXPECT_EQ((uintptr_t)GetBoxedMonPtr(TOTAL_BOXES_COUNT, 0), (uintptr_t)NULL);
    EXPECT_EQ((uintptr_t)GetBoxedMonPtr(0, IN_BOX_COUNT), (uintptr_t)NULL);
    EXPECT_EQ((uintptr_t)GetBoxNamePtr(TOTAL_BOXES_COUNT), (uintptr_t)NULL);

    PokemonStorageSystem_TestSetBoxWallpaper(15, 3);
    PokemonStorageSystem_TestSetBoxWallpaper(16, 7);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(15), 3);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(16), 7);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(TOTAL_BOXES_COUNT), 0);
}

TEST("PokemonStorage extension initialization preserves all legacy bytes and defaults both boxes")
{
    static const u8 sBox16Name[] = COMPOUND_STRING("Box16");
    static const u8 sBox17Name[] = COMPOUND_STRING("Box17");
    void *legacyData;

    FillPokemonStoragePattern(0x51);
    legacyData = Alloc(T_POKEMONSTORAGE_LEGACY_SIZE);
    memcpy(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE);

    InitPokemonStorageExtension();

    EXPECT_EQ(memcmp(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 1, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(memcmp(gPokemonStoragePtr->extraBoxName, sBox16Name, sizeof(sBox16Name)), 0);
    EXPECT_EQ(memcmp(gPokemonStoragePtr->box17Name, sBox17Name, sizeof(sBox17Name)), 0);
    EXPECT_EQ(gPokemonStoragePtr->extraBoxWallpaper, 15);
    EXPECT_EQ(gPokemonStoragePtr->box17Wallpaper, 16);
    Free(legacyData);
}

TEST("Box 17 initialization preserves every BX16 byte")
{
    void *bx16Data;

    FillPokemonStoragePattern(0x91);
    bx16Data = Alloc(T_POKEMONSTORAGE_BX16_SIZE);
    memcpy(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE);

    InitPokemonStorageBox17Extension();

    EXPECT_EQ(memcmp(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 1, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    Free(bx16Data);
}

TEST("PokemonStorage chooses the shorter direction with 17 boxes")
{
    ResetPokemonStorageSystem();
    gPokemonStoragePtr->currentBox = 0;
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(8), 1);
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(9), -1);

    gPokemonStoragePtr->currentBox = 16;
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(7), 1);
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(8), -1);
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

TEST("Box 17 Pokemon metadata and current-box selection survive a full save")
{
    static const u8 sCustomName[] = COMPOUND_STRING("BoxXVII");
    struct Pokemon mon;
    struct PokemonStorage *expected;

    gTestRunnerState.timeoutSeconds = 120;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_PIKACHU, 42, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(16, 29, &mon.box);
    memcpy(gPokemonStoragePtr->box17Name, sCustomName, sizeof(sCustomName));
    gPokemonStoragePtr->box17Wallpaper = 7;
    gPokemonStoragePtr->currentBox = 16;

    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);
    EXPECT_EQ(GetBoxMonDataAt(16, 29, MON_DATA_SPECIES), SPECIES_PIKACHU);
    EXPECT_EQ(memcmp(GetBoxNamePtr(16), sCustomName, sizeof(sCustomName)), 0);
    EXPECT_EQ(gPokemonStoragePtr->box17Wallpaper, 7);
    EXPECT_EQ(StorageGetCurrentBox(), 16);

    Free(expected);
}

TEST("PokemonStorage loads a legacy save and initializes only boxes 16 and 17")
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
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 1, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);

    Free(lastStorageSector);
    Free(legacyData);
}

TEST("PokemonStorage migrates a genuine BX16 overflow without changing its bytes")
{
    struct SaveSector *overflowSector;
    u8 *bx16Data;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x5C);
    gPokemonStoragePtr->currentBox = 15;
    bx16Data = Alloc(T_POKEMONSTORAGE_BX16_SIZE);
    memcpy(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    overflowSector = Alloc(sizeof(*overflowSector));
    ConvertNewestOverflowToBx16(overflowSector);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    EXPECT_EQ(StorageGetCurrentBox(), 15);
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);
    EXPECT_EQ(GetBoxMonDataAt(16, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);

    // The in-RAM migration is committed by the next full save.
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    memcpy(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);
    EXPECT_EQ(GetBoxMonDataAt(16, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);

    Free(overflowSector);
    Free(bx16Data);
}

TEST("Frozen legacy release save preserves every storage field during migration")
{
    u8 *expectedStorage;

    gTestRunnerState.timeoutSeconds = 300;
    expectedStorage = Alloc(T_POKEMONSTORAGE_LEGACY_SIZE);
    CopyFrozenStoragePrefix(sLegacyReleaseSave, expectedStorage, T_POKEMONSTORAGE_LEGACY_SIZE);
    LoadFrozenSaveFixture(sLegacyReleaseSave);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expectedStorage, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE), 0);
    VerifyFrozenStorageContents(LEGACY_BOXES_COUNT,
                                sLegacyFixtureNames,
                                0x15000000,
                                0x15150000,
                                0xF1500000,
                                0xF1515000);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT), 0);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 1), 0);
    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);

    Free(expectedStorage);
}

TEST("Frozen BX16 release save preserves every storage field during migration")
{
    u8 *expectedStorage;

    gTestRunnerState.timeoutSeconds = 300;
    expectedStorage = Alloc(T_POKEMONSTORAGE_BX16_SIZE);
    CopyFrozenStoragePrefix(sBx16ReleaseSave, expectedStorage, T_POKEMONSTORAGE_BX16_SIZE);
    LoadFrozenSaveFixture(sBx16ReleaseSave);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expectedStorage, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    VerifyFrozenStorageContents(LEGACY_BOXES_COUNT + 1,
                                sBx16FixtureNames,
                                0x16000000,
                                0x16160000,
                                0xF1600000,
                                0xF1616000);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 1), 0);
    EXPECT_EQ(gPokemonStoragePtr->box17ExtensionMagic, POKEMON_STORAGE_BOX17_MAGIC);

    Free(expectedStorage);
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

TEST("PokemonStorage falls back for every corrupt BX17 integrity field")
{
    static const u16 sCorruptOffsets[] =
    {
        offsetof(struct PokemonStorage, box17ExtensionMagic) - T_POKEMONSTORAGE_REGULAR_SIZE,
        offsetof(struct PokemonStorage, box17Checksum) - T_POKEMONSTORAGE_REGULAR_SIZE,
        offsetof(struct PokemonStorage, box17ChecksumInverse) - T_POKEMONSTORAGE_REGULAR_SIZE,
        offsetof(struct PokemonStorage, box17) - T_POKEMONSTORAGE_REGULAR_SIZE + 137,
    };
    struct PokemonStorage *previousSave;
    struct SaveSector *originalOverflow;
    struct SaveSector *corruptOverflow;
    u32 i;
    u8 newestOverflowSector;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x31);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0xB7);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    newestOverflowSector = GetNewestOverflowSectorId();
    originalOverflow = Alloc(sizeof(*originalOverflow));
    corruptOverflow = Alloc(sizeof(*corruptOverflow));
    ReadNewestOverflowSector(originalOverflow);

    for (i = 0; i < ARRAY_COUNT(sCorruptOffsets); i++)
    {
        memcpy(corruptOverflow, originalOverflow, sizeof(*corruptOverflow));
        corruptOverflow->data[sCorruptOffsets[i]] ^= 1;
        EXPECT_EQ(ProgramFlashSectorAndVerify(newestOverflowSector, (u8 *)corruptOverflow), 0);

        memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
        EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
        EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);
    }

    Free(corruptOverflow);
    Free(originalOverflow);
    Free(previousSave);
}

TEST("PokemonStorage rejects a nonzero malformed BX16 tail")
{
    struct PokemonStorage *previousSave;
    struct SaveSector *overflowSector;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x22);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0x88);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    overflowSector = Alloc(sizeof(*overflowSector));
    ConvertNewestOverflowToBx16(overflowSector);
    overflowSector->data[SECTOR_DATA_SIZE - 1] = 1;
    WriteNewestOverflowSector(overflowSector);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(overflowSector);
    Free(previousSave);
}

TEST("PokemonStorage falls back for missing and counter-mismatched overflow")
{
    struct PokemonStorage *previousSave;
    struct SaveSector *originalOverflow;
    struct SaveSector *badOverflow;
    u8 newestOverflowSector;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x43);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0xC1);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    newestOverflowSector = GetNewestOverflowSectorId();
    originalOverflow = Alloc(sizeof(*originalOverflow));
    badOverflow = Alloc(sizeof(*badOverflow));
    ReadNewestOverflowSector(originalOverflow);

    EXPECT_EQ(EraseFlashSector(newestOverflowSector), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    memcpy(badOverflow, originalOverflow, sizeof(*badOverflow));
    badOverflow->counter++;
    EXPECT_EQ(ProgramFlashSectorAndVerify(newestOverflowSector, (u8 *)badOverflow), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(badOverflow);
    Free(originalOverflow);
    Free(previousSave);
}

TEST("LinkFullSave persists the complete BX17 extension")
{
    static const u8 sLinkName[] = COMPOUND_STRING("Link 17");
    struct Pokemon mon;
    struct PokemonStorage *expected;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_EEVEE, 25, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(16, 4, &mon.box);
    memcpy(gPokemonStoragePtr->box17Name, sLinkName, sizeof(sLinkName));
    gPokemonStoragePtr->box17Wallpaper = 11;
    gPokemonStoragePtr->currentBox = 16;

    RunLinkFullSave();
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);

    Free(expected);
}

TEST("SAVE_LINK remains partial and does not persist PokemonStorage")
{
    struct PokemonStorage *expected;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x18);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));

    FillPokemonStoragePattern(0xE2);
    EXPECT_EQ(TrySavingData(SAVE_LINK), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);

    Free(expected);
}

TEST("Box 17 participates in fullness and search paths")
{
    struct Pokemon mon;
    u32 boxId;
    u32 boxPosition;

    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&mon, MOVE_TACKLE, 0);

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT - 1; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
            SetBoxMonAt(boxId, boxPosition, &mon.box);
    }

    EXPECT(!IsPokemonStorageFull());
    EXPECT(CheckFreePokemonStorageSpace());
    EXPECT_EQ(GetFirstFreeBoxSpot(16), 0);

    SetBoxMonAt(16, IN_BOX_COUNT - 1, &mon.box);
    EXPECT_EQ(CountAllStorageMons(), (TOTAL_BOXES_COUNT - 1) * IN_BOX_COUNT + 1);
    EXPECT(AnyStorageMonWithMove(MOVE_TACKLE));

    for (boxPosition = 0; boxPosition < IN_BOX_COUNT - 1; boxPosition++)
        SetBoxMonAt(16, boxPosition, &mon.box);
    EXPECT(IsPokemonStorageFull());
    EXPECT(!CheckFreePokemonStorageSpace());
}

TEST("Pokemon deposit reaches Box 17 and wraps from it to Box 1")
{
    struct Pokemon mon;
    u32 boxId;
    u32 boxPosition;

    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_EEVEE, 20, 0, OTID_STRUCT_PLAYER_ID);
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT - 1; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
            SetBoxMonAt(boxId, boxPosition, &mon.box);
    }
    EXPECT_EQ(CopyMonToPC(&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(gSpecialVar_MonBoxId, 16);
    EXPECT_EQ(gSpecialVar_MonBoxPos, 0);
    EXPECT_EQ(GetBoxMonDataAt(16, 0, MON_DATA_SPECIES), SPECIES_EEVEE);

    ResetPokemonStorageSystem();
    for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        SetBoxMonAt(16, boxPosition, &mon.box);
    gPokemonStoragePtr->currentBox = 16;
    EXPECT_EQ(CopyMonToPC(&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(gSpecialVar_MonBoxId, 0);
    EXPECT_EQ(gSpecialVar_MonBoxPos, 0);
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_SPECIES), SPECIES_EEVEE);
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
#undef T_POKEMONSTORAGE_BX16_SIZE
#undef T_POKEMONSTORAGE_REGULAR_SIZE
#undef T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE
#undef T_POKEMONSTORAGE_OVERFLOW_SIZE
#undef T_POKEMONSTORAGE_BX17_OVERFLOW_OFFSET
#undef T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE
