#include "global.h"
#include "agb_flash.h"
#include "credits.h"
#include "event_data.h"
#include "hall_of_fame.h"
#include "link.h"
#include "main.h"
#include "gba/flash_internal.h"
#include "malloc.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "overworld.h"
#include "save.h"
#include "start_menu.h"
#include "task.h"
#include "trade.h"
#include "mystery_gift_menu.h"
#include "union_room_chat.h"
#include "test/test.h"
#include "constants/characters.h"
#include "constants/game_stat.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
#define T_SAVEBLOCK1_SIZE 15444
#define T_SAVEBLOCK2_SIZE 2864
#define T_SAVEBLOCK3_SIZE 100
#define T_POKEMON_SECURE_DATA_SIZE 44
#define T_BOX_POKEMON_SIZE 76
#define T_POKEMON_SIZE 96
#define T_POKEMONSTORAGE_SIZE 43916
#define T_POKEMONSTORAGE_LEGACY_SIZE 34740
#define T_POKEMONSTORAGE_BX16_SIZE 37036
#define T_POKEMONSTORAGE_BX17_SIZE 39336
#define T_POKEMONSTORAGE_BX18_SIZE 41624
#define T_POKEMONSTORAGE_REGULAR_SIZE (SECTOR_DATA_SIZE * 9)
#define T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE (T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE)
#define T_POKEMONSTORAGE_BX18_OVERFLOW_OFFSET (T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE)
#define T_POKEMONSTORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET (offsetof(struct PokemonStorage, extensionBoxes) - T_POKEMONSTORAGE_REGULAR_SIZE)
#define T_POKEMONSTORAGE_EXTENSION_TAIL_OFFSET (T_POKEMONSTORAGE_REGULAR_SIZE + SECTOR_DATA_SIZE)
#define T_SAVEBLOCK1_EXTENSION_TAIL_SECTOR_OFFSET (offsetof(struct SaveBlock1, pokemonStorageExtensionTail) - 3 * SECTOR_DATA_SIZE)
#define T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE (T_POKEMONSTORAGE_LEGACY_SIZE - SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START))
#define T_SAVEBLOCK1_LAST_SECTOR_SIZE (T_SAVEBLOCK1_SIZE - 3 * SECTOR_DATA_SIZE)
#define T_BX19_HEADER_SIZE 12
#define T_BX19_BOX_RECORD_SIZE 2292
#define T_BX19_ARCHIVE_OFFSET (T_BX19_HEADER_SIZE + T_BX19_BOX_RECORD_SIZE)
#define T_BX19_TEAMS_OFFSET (T_BX19_ARCHIVE_OFFSET + 4)
#define T_BX19_USED_SIZE 3892
#define T_BX19_PAYLOAD_SIZE (T_BX19_USED_SIZE - T_BX19_HEADER_SIZE)
#define T_VS_SEEKER_SAVE_MAGIC_OFFSET 11109
#define T_VS_SEEKER_CHARGE_STEPS_OFFSET 11110
#define T_VS_SEEKER_SAVE_MAGIC_INV_OFFSET 11120
#define T_OBJECT_EVENT_TEMPLATE_SIZE 24
#define T_OBJECT_EVENT_TEMPLATE_TRAINER_TYPE_OFFSET 12
#define T_OBJECT_EVENT_TEMPLATE_SCRIPT_OFFSET 16
#define T_OBJECT_EVENT_TEMPLATE_FLAG_ID_OFFSET 20


#define T_BX16_CURRENT_BOX_OFFSET       0
#define T_BX16_BOXES_OFFSET             4
#define T_BX16_BOX_NAMES_OFFSET         34204
#define T_BX16_BOX_WALLPAPERS_OFFSET    34339
#define T_BX16_EXTENSION_MAGIC_OFFSET   34740
#define T_BX16_EXTRA_BOX_OFFSET         34744
#define T_BX16_EXTRA_BOX_NAME_OFFSET    37024
#define T_BX16_EXTRA_BOX_WALLPAPER_OFFSET 37033
#define T_BX16_EXTRA_BOX_PADDING_OFFSET 37034

#define T_FROZEN_BOXMON_PERSONALITY_OFFSET 0
#define T_FROZEN_BOXMON_OT_ID_OFFSET       4
#define T_FROZEN_BOXMON_FLAGS_OFFSET       19
#define T_FROZEN_BOXMON_SECURE_OFFSET      32
#define T_FROZEN_BOXMON_HAS_SPECIES        (1 << 1)

static const u16 sReleaseFormatSpecies[] =
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

static const u8 sFrozenBx16Box1Name[BOX_NAME_LENGTH + 1] = COMPOUND_STRING("FROZEN01");
static const u8 sFrozenBx16Box16Name[BOX_NAME_LENGTH + 1] = COMPOUND_STRING("FROZEN16");

static u16 CalculateTestSaveChecksum(void *data, u16 size);
static void ResetPokemonStorageTestFlash(void);

static void WriteFrozenU16(u8 *dst, u16 value)
{
    dst[0] = value;
    dst[1] = value >> 8;
}

static void WriteFrozenU32(u8 *dst, u32 value)
{
    dst[0] = value;
    dst[1] = value >> 8;
    dst[2] = value >> 16;
    dst[3] = value >> 24;
}

static void WriteFrozenBx16BoxMon(u8 *dst, u16 species, u32 personality, u32 otId)
{
    WriteFrozenU32(&dst[T_FROZEN_BOXMON_PERSONALITY_OFFSET], personality);
    WriteFrozenU32(&dst[T_FROZEN_BOXMON_OT_ID_OFFSET], otId);
    dst[T_FROZEN_BOXMON_FLAGS_OFFSET] = T_FROZEN_BOXMON_HAS_SPECIES;
    WriteFrozenU16(&dst[T_FROZEN_BOXMON_SECURE_OFFSET], species);
}

static void BuildFrozenBx16StorageImage(u8 *image)
{
    u32 box;

    memset(image, 0, T_POKEMONSTORAGE_BX16_SIZE);
    image[T_BX16_CURRENT_BOX_OFFSET] = 15;
    image[1] = 0xA1;
    image[2] = 0xA2;
    image[3] = 0xA3;

    for (box = 0; box < LEGACY_BOXES_COUNT; box++)
        image[T_BX16_BOX_NAMES_OFFSET + box * (BOX_NAME_LENGTH + 1)] = EOS;
    image[T_BX16_EXTRA_BOX_NAME_OFFSET] = EOS;

    memcpy(&image[T_BX16_BOX_NAMES_OFFSET], sFrozenBx16Box1Name, sizeof(sFrozenBx16Box1Name));
    memcpy(&image[T_BX16_EXTRA_BOX_NAME_OFFSET], sFrozenBx16Box16Name, sizeof(sFrozenBx16Box16Name));
    image[T_BX16_BOX_WALLPAPERS_OFFSET] = 3;
    image[T_BX16_EXTRA_BOX_WALLPAPER_OFFSET] = 7;
    image[T_BX16_EXTRA_BOX_PADDING_OFFSET] = 0x5A;
    image[T_BX16_EXTRA_BOX_PADDING_OFFSET + 1] = 0xA5;
    WriteFrozenU32(&image[T_BX16_EXTENSION_MAGIC_OFFSET], POKEMON_STORAGE_EXTENSION_MAGIC);

    WriteFrozenBx16BoxMon(&image[T_BX16_BOXES_OFFSET],
                         SPECIES_PIKACHU,
                         0x12345678,
                         0x89ABCDEF);
    WriteFrozenBx16BoxMon(&image[T_BX16_EXTRA_BOX_OFFSET + 7 * T_BOX_POKEMON_SIZE],
                         SPECIES_EEVEE,
                         0x0BADCAFE,
                         0x10203040);
}

static void VerifyReleasedStorageContents(u32 boxCount,
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
            EXPECT_EQ(GetBoxMonDataAt(box, position, MON_DATA_SPECIES), sReleaseFormatSpecies[box]);
            EXPECT_EQ(GetBoxMonDataAt(box, position, MON_DATA_PERSONALITY),
                      personalityBase + box * IN_BOX_COUNT + position);
            EXPECT_EQ(GetBoxMonDataAt(box, position, MON_DATA_OT_ID), otIdBase + box);
        }
    }

    for (position = 0; position < MAX_FUSION_STORAGE; position++)
    {
        EXPECT_EQ(GetMonData(&gPokemonStoragePtr->fusions[position], MON_DATA_SPECIES), sReleaseFormatSpecies[position]);
        EXPECT_EQ(GetMonData(&gPokemonStoragePtr->fusions[position], MON_DATA_PERSONALITY), fusionPersonalityBase + position);
        EXPECT_EQ(GetMonData(&gPokemonStoragePtr->fusions[position], MON_DATA_OT_ID), fusionOtIdBase + position);
    }
}

static void PopulateReleasedStorageContents(u32 boxCount,
                                            const u8 (*boxNames)[BOX_NAME_LENGTH + 1],
                                            u32 personalityBase,
                                            u32 otIdBase,
                                            u32 fusionPersonalityBase,
                                            u32 fusionOtIdBase)
{
    u32 box;
    u32 position;

    ResetPokemonStorageSystem();
    gPokemonStoragePtr->currentBox = boxCount - 1;
    for (box = 0; box < boxCount; box++)
    {
        memcpy(GetBoxNamePtr(box), boxNames[box], BOX_NAME_LENGTH + 1);
        PokemonStorageSystem_TestSetBoxWallpaper(box, box);
        for (position = 0; position < IN_BOX_COUNT; position++)
        {
            struct BoxPokemon *boxMon = GetBoxedMonPtr(box, position);
            u32 personality = personalityBase + box * IN_BOX_COUNT + position;
            u32 otId = otIdBase + box;
            u16 species = sReleaseFormatSpecies[box];

            ZeroBoxMonData(boxMon);
            SetBoxMonData(boxMon, MON_DATA_PERSONALITY, &personality);
            SetBoxMonData(boxMon, MON_DATA_OT_ID, &otId);
            SetBoxMonData(boxMon, MON_DATA_SPECIES, &species);
        }
    }

    for (position = 0; position < MAX_FUSION_STORAGE; position++)
    {
        struct Pokemon *mon = &gPokemonStoragePtr->fusions[position];
        u32 personality = fusionPersonalityBase + position;
        u32 otId = fusionOtIdBase + position;
        u16 species = sReleaseFormatSpecies[position];

        ZeroMonData(mon);
        SetMonData(mon, MON_DATA_PERSONALITY, &personality);
        SetMonData(mon, MON_DATA_OT_ID, &otId);
        SetMonData(mon, MON_DATA_SPECIES, &species);
    }
}

static u16 FailProgramFlashSector(u16 sectorNum, u8 *src)
{
    (void)sectorNum;
    (void)src;
    return 1;
}

static u16 (*sRealProgramFlashSector)(u16, u8 *);
static u16 sFailWriteCall;
static u16 sProgramFlashWriteCall;

static u16 FailSelectedProgramFlashWrite(u16 sectorNum, u8 *src)
{
    u16 call = sProgramFlashWriteCall++;

    if (call >= sFailWriteCall && call < sFailWriteCall + 3)
        return 1;
    return sRealProgramFlashSector(sectorNum, src);
}

static void FillPokemonStoragePattern(u8 seed)
{
    u32 i;
    u8 *storage = (u8 *)gPokemonStoragePtr;

    for (i = 0; i < sizeof(*gPokemonStoragePtr); i++)
        storage[i] = seed + i * 37 + (i >> 8);

    gPokemonStoragePtr->currentBox = seed % TOTAL_BOXES_COUNT;
    gPokemonStoragePtr->boxExtensionMagic = POKEMON_STORAGE_EXTENSION_MAGIC;
    gPokemonStoragePtr->box18ExtensionMagic = POKEMON_STORAGE_BOX18_MAGIC;
    gPokemonStoragePtr->box18Checksum = CalculateTestSaveChecksum(
        &gPokemonStoragePtr->extensionBoxes,
        T_POKEMONSTORAGE_BX18_SIZE - offsetof(struct PokemonStorage, extensionBoxes));
    gPokemonStoragePtr->box18ChecksumInverse = (u16)~gPokemonStoragePtr->box18Checksum;
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
    ResetHallOfFameArchive();
}

static u8 GetNewestOverflowSectorId(void)
{
    return SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + (gSaveCounter % NUM_SAVE_SLOTS);
}

static u8 GetNewestAuxiliarySectorId(void)
{
    return SECTOR_ID_BX19_AUXILIARY_1 + (gSaveCounter % NUM_SAVE_SLOTS);
}

static u8 GetNewestSaveSectorId(u16 logicalSectorId)
{
    u8 sectorId = (logicalSectorId + gLastWrittenSector) % NUM_SECTORS_PER_SLOT;
    return sectorId + NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);
}

static void ReadNewestOverflowSector(struct SaveSector *sector)
{
    ReadFlash(GetNewestOverflowSectorId(), 0, (u8 *)sector, sizeof(*sector));
}

static void ReadNewestAuxiliarySector(struct SaveSector *sector)
{
    ReadFlash(GetNewestAuxiliarySectorId(), 0, (u8 *)sector, sizeof(*sector));
}

static void WriteNewestOverflowSector(struct SaveSector *sector)
{
    EXPECT_EQ(ProgramFlashSectorAndVerify(GetNewestOverflowSectorId(), (u8 *)sector), 0);
}

static void ReadNewestSaveBlock1TailSector(struct SaveSector *sector)
{
    ReadFlash(GetNewestSaveSectorId(SECTOR_ID_SAVEBLOCK1_END), 0, (u8 *)sector, sizeof(*sector));
}

static void InstallFrozenBx16StorageImage(const u8 *image)
{
    struct SaveSector *sector = Alloc(sizeof(*sector));
    u16 logicalSector;
    u8 physicalSector;

    for (logicalSector = SECTOR_ID_PKMN_STORAGE_START;
         logicalSector <= SECTOR_ID_PKMN_STORAGE_END;
         logicalSector++)
    {
        physicalSector = GetNewestSaveSectorId(logicalSector);
        ReadFlash(physicalSector, 0, (u8 *)sector, sizeof(*sector));
        memset(sector->data, 0, SECTOR_DATA_SIZE);
        memcpy(sector->data,
               &image[(logicalSector - SECTOR_ID_PKMN_STORAGE_START) * SECTOR_DATA_SIZE],
               SECTOR_DATA_SIZE);
        sector->id = logicalSector;
        sector->checksum = CalculateTestSaveChecksum(sector->data, SECTOR_DATA_SIZE);
        sector->signature = SECTOR_SIGNATURE;
        sector->counter = gSaveCounter;
        EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)sector), 0);
    }

    memset(sector, 0, sizeof(*sector));
    physicalSector = GetNewestOverflowSectorId();
    memcpy(sector->data,
           &image[T_POKEMONSTORAGE_REGULAR_SIZE],
           T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE);
    sector->id = physicalSector;
    sector->checksum = CalculateTestSaveChecksum(sector->data, T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE);
    sector->signature = SECTOR_SIGNATURE;
    sector->counter = gSaveCounter;
    EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)sector), 0);
    EXPECT_EQ(EraseFlashSector(GetNewestAuxiliarySectorId()), 0);

    Free(sector);
}

static void ConvertNewestSaveToLegacy(struct SaveSector *sector)
{
    u8 physicalSector = GetNewestSaveSectorId(SECTOR_ID_PKMN_STORAGE_END);

    ReadFlash(physicalSector, 0, (u8 *)sector, sizeof(*sector));
    memset(&sector->data[T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE],
           0,
           SECTOR_DATA_SIZE - T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE);
    sector->checksum = CalculateTestSaveChecksum(sector->data, T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE);
    EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)sector), 0);
    EXPECT_EQ(EraseFlashSector(GetNewestOverflowSectorId()), 0);
}

static void ConvertNewestOverflowToBx16(struct SaveSector *sector)
{
    ReadNewestOverflowSector(sector);
    memset(&sector->data[T_POKEMONSTORAGE_BX18_OVERFLOW_OFFSET],
           0,
           SECTOR_DATA_SIZE - T_POKEMONSTORAGE_BX18_OVERFLOW_OFFSET);
    sector->checksum = CalculateTestSaveChecksum(sector->data, T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE);
    WriteNewestOverflowSector(sector);
}

static void ConvertNewestOverflowToBx17(struct SaveSector *sector)
{
    u16 checksum;
    u16 payloadOffset = T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE + 8;
    u16 magicOffset = T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE;

    ReadNewestOverflowSector(sector);
    memset(&sector->data[magicOffset], 0, SECTOR_DATA_SIZE - magicOffset);
    *(u32 *)&sector->data[magicOffset] = POKEMON_STORAGE_BOX17_MAGIC;
    memcpy(&sector->data[payloadOffset],
           gPokemonStoragePtr->extensionBoxes[0],
           sizeof(gPokemonStoragePtr->extensionBoxes[0]));
    memcpy(&sector->data[payloadOffset + sizeof(gPokemonStoragePtr->extensionBoxes[0])],
           gPokemonStoragePtr->extensionBoxNames[0],
           sizeof(gPokemonStoragePtr->extensionBoxNames[0]));
    sector->data[payloadOffset + sizeof(gPokemonStoragePtr->extensionBoxes[0])
                 + sizeof(gPokemonStoragePtr->extensionBoxNames[0])] =
        gPokemonStoragePtr->extensionBoxWallpapers[0];
    checksum = CalculateTestSaveChecksum(&sector->data[payloadOffset],
                                         T_POKEMONSTORAGE_BX17_SIZE - T_POKEMONSTORAGE_BX16_SIZE - 8);
    *(u16 *)&sector->data[magicOffset + 4] = checksum;
    *(u16 *)&sector->data[magicOffset + 6] = (u16)~checksum;
    sector->checksum = CalculateTestSaveChecksum(sector->data, T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE);
    WriteNewestOverflowSector(sector);
    EXPECT_EQ(EraseFlashSector(GetNewestAuxiliarySectorId()), 0);
}

static void ConvertNewestOverflowToBx18(struct SaveSector *sector)
{
    u16 checksum;
    u16 magicOffset = T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE;

    ReadNewestOverflowSector(sector);
    *(u32 *)&sector->data[magicOffset] = POKEMON_STORAGE_BOX18_MAGIC;
    checksum = CalculateTestSaveChecksum(
        &gPokemonStoragePtr->extensionBoxes,
        T_POKEMONSTORAGE_BX18_SIZE - offsetof(struct PokemonStorage, extensionBoxes));
    *(u16 *)&sector->data[magicOffset + sizeof(u32)] = checksum;
    *(u16 *)&sector->data[magicOffset + sizeof(u32) + sizeof(u16)] = (u16)~checksum;
    WriteNewestOverflowSector(sector);
    EXPECT_EQ(EraseFlashSector(GetNewestAuxiliarySectorId()), 0);
}

static void WriteLegacyHallOfFameTeams(u8 teamCount)
{
    u8 *data = AllocZeroed(SECTOR_DATA_SIZE * NUM_HOF_SECTORS);
    struct HallofFameTeam *teams = (struct HallofFameTeam *)data;
    struct SaveSector *sector = AllocZeroed(sizeof(*sector));
    u32 i;
    u32 sectorIndex;

    for (i = 0; i < teamCount; i++)
    {
        teams[i].mon[0].species = SPECIES_BULBASAUR;
        teams[i].mon[0].tid = 1000 + i;
        teams[i].mon[0].personality = 2000 + i;
        teams[i].mon[0].lvl = 50 + i;
    }

    for (sectorIndex = 0; sectorIndex < NUM_HOF_SECTORS; sectorIndex++)
    {
        memset(sector, 0, sizeof(*sector));
        memcpy(sector->data,
               &data[sectorIndex * SECTOR_DATA_SIZE],
               SECTOR_DATA_SIZE);
        sector->id = CalculateTestSaveChecksum(sector->data, SECTOR_DATA_SIZE);
        sector->signature = SECTOR_SIGNATURE;
        EXPECT_EQ(ProgramFlashSectorAndVerify(SECTOR_ID_HOF_1 + sectorIndex, (u8 *)sector), 0);
    }

    Free(sector);
    Free(data);
}

static void AllocateHallOfFameTestBuffer(void)
{
    gHoFSaveBuffer = AllocZeroed(sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
    EXPECT(gHoFSaveBuffer != NULL);
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
    EXPECT_EQ(offsetof(struct SaveBlock1, pokemonStorageExtensionTail), 0x349A);
    EXPECT_EQ(sizeof(gSaveBlock1Ptr->pokemonStorageExtensionTail), 1944);
    EXPECT_EQ(offsetof(struct SaveBlock1, futureReserved), 0x3C32);
    EXPECT_EQ(sizeof(gSaveBlock1Ptr->futureReserved), 34);
    EXPECT_EQ(sizeof(struct ObjectEventTemplate), T_OBJECT_EVENT_TEMPLATE_SIZE);
    EXPECT_EQ(offsetof(struct ObjectEventTemplate, trainerType), T_OBJECT_EVENT_TEMPLATE_TRAINER_TYPE_OFFSET);
    EXPECT_EQ(offsetof(struct ObjectEventTemplate, script), T_OBJECT_EVENT_TEMPLATE_SCRIPT_OFFSET);
    EXPECT_EQ(offsetof(struct ObjectEventTemplate, flagId), T_OBJECT_EVENT_TEMPLATE_FLAG_ID_OFFSET);
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
    EXPECT_EQ(LEGACY_BOXES_COUNT, 15);
    EXPECT_EQ(TOTAL_BOXES_COUNT, 19);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxes), 4);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxNames), 34204);
    EXPECT_EQ(offsetof(struct PokemonStorage, legacyBoxWallpapers), 34339);
    EXPECT_EQ(offsetof(struct PokemonStorage, fusions), 34356);
    EXPECT_EQ(offsetof(struct PokemonStorage, boxExtensionMagic), 34740);
    EXPECT_EQ(offsetof(struct PokemonStorage, extraBox), 34744);
    EXPECT_EQ(offsetof(struct PokemonStorage, extraBoxName), 37024);
    EXPECT_EQ(offsetof(struct PokemonStorage, extraBoxWallpaper), 37033);
    EXPECT_EQ(offsetof(struct PokemonStorage, box18ExtensionMagic), 37036);
    EXPECT_EQ(offsetof(struct PokemonStorage, box18Checksum), 37040);
    EXPECT_EQ(offsetof(struct PokemonStorage, box18ChecksumInverse), 37042);
    EXPECT_EQ(offsetof(struct PokemonStorage, extensionBoxes), 37044);
    EXPECT_EQ(offsetof(struct PokemonStorage, extensionBoxes[1]), 39324);
    EXPECT_EQ(offsetof(struct PokemonStorage, extensionBoxNames), 41604);
    EXPECT_EQ(offsetof(struct PokemonStorage, extensionBoxNames[1]), 41613);
    EXPECT_EQ(offsetof(struct PokemonStorage, extensionBoxWallpapers), 41622);
    EXPECT_EQ(offsetof(struct PokemonStorage, extensionBoxWallpapers[1]), 41623);
    EXPECT_EQ(sizeof(gPokemonStoragePtr->extensionBoxes), 4560);
    EXPECT_EQ(sizeof(gPokemonStoragePtr->extensionBoxNames), 18);
    EXPECT_EQ(sizeof(gPokemonStoragePtr->extensionBoxWallpapers), 2);
    EXPECT_EQ(offsetof(struct PokemonStorage, box19), T_POKEMONSTORAGE_BX18_SIZE);
    EXPECT_EQ(offsetof(struct PokemonStorage, box19Name), 43904);
    EXPECT_EQ(offsetof(struct PokemonStorage, box19Wallpaper), 43913);
    EXPECT_EQ(offsetof(struct PokemonStorage, box19Padding), 43914);
    EXPECT_EQ(sizeof(struct PokemonStorage), T_POKEMONSTORAGE_SIZE);
    EXPECT_EQ(T_POKEMONSTORAGE_BX18_SIZE - offsetof(struct PokemonStorage, box18ExtensionMagic), 4588);
    EXPECT_EQ(T_POKEMONSTORAGE_BX18_SIZE - offsetof(struct PokemonStorage, extensionBoxes), 4580);
    EXPECT_EQ(T_POKEMONSTORAGE_REGULAR_SIZE, 35712);
    EXPECT_EQ(T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE, 1324);
    EXPECT_EQ(SECTOR_DATA_SIZE, 3968);
    EXPECT_EQ(T_POKEMONSTORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET, 1332);
    EXPECT_EQ(SECTOR_DATA_SIZE - T_POKEMONSTORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET, 2636);
    EXPECT_EQ(T_POKEMONSTORAGE_EXTENSION_TAIL_OFFSET, 39680);
    EXPECT_EQ(T_POKEMONSTORAGE_BX18_SIZE - T_POKEMONSTORAGE_EXTENSION_TAIL_OFFSET, 1944);
    EXPECT_EQ(T_POKEMONSTORAGE_SIZE - T_POKEMONSTORAGE_BX18_SIZE, 2292);
}

TEST("PokemonStorage routes boxes 16 through 19 through distinct storage")
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
            else if (boxId < TOTAL_BOXES_COUNT - 1)
                expected = &gPokemonStoragePtr->extensionBoxes[boxId - LEGACY_BOXES_COUNT - 1][boxPosition];
            else
                expected = &gPokemonStoragePtr->box19[boxPosition];

            EXPECT_EQ((uintptr_t)GetBoxedMonPtr(boxId, boxPosition), (uintptr_t)expected);
        }

        if (boxId < LEGACY_BOXES_COUNT)
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->legacyBoxNames[boxId]);
        else if (boxId == LEGACY_BOXES_COUNT)
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->extraBoxName);
        else if (boxId < TOTAL_BOXES_COUNT - 1)
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->extensionBoxNames[boxId - LEGACY_BOXES_COUNT - 1]);
        else
            EXPECT_EQ((uintptr_t)GetBoxNamePtr(boxId), (uintptr_t)gPokemonStoragePtr->box19Name);
    }

    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);
    EXPECT_EQ((uintptr_t)GetBoxedMonPtr(TOTAL_BOXES_COUNT, 0), (uintptr_t)NULL);
    EXPECT_EQ((uintptr_t)GetBoxedMonPtr(0, IN_BOX_COUNT), (uintptr_t)NULL);
    EXPECT_EQ((uintptr_t)GetBoxNamePtr(TOTAL_BOXES_COUNT), (uintptr_t)NULL);

    PokemonStorageSystem_TestSetBoxWallpaper(15, 3);
    PokemonStorageSystem_TestSetBoxWallpaper(16, 7);
    PokemonStorageSystem_TestSetBoxWallpaper(17, 11);
    PokemonStorageSystem_TestSetBoxWallpaper(18, 13);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(15), 3);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(16), 7);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(17), 11);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(18), 13);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(TOTAL_BOXES_COUNT), 0);
}

TEST("PokemonStorage extension initialization preserves all legacy bytes and defaults Boxes 16 through 19")
{
    static const u8 sBox16Name[] = COMPOUND_STRING("Box16");
    static const u8 sBox17Name[] = COMPOUND_STRING("Box17");
    static const u8 sBox18Name[] = COMPOUND_STRING("Box18");
    static const u8 sBox19Name[] = COMPOUND_STRING("Box19");
    void *legacyData;

    FillPokemonStoragePattern(0x51);
    legacyData = Alloc(T_POKEMONSTORAGE_LEGACY_SIZE);
    memcpy(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE);

    InitPokemonStorageExtension();

    EXPECT_EQ(memcmp(legacyData, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 1, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 2, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 3, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(memcmp(gPokemonStoragePtr->extraBoxName, sBox16Name, sizeof(sBox16Name)), 0);
    EXPECT_EQ(memcmp(gPokemonStoragePtr->extensionBoxNames[0], sBox17Name, sizeof(sBox17Name)), 0);
    EXPECT_EQ(memcmp(gPokemonStoragePtr->extensionBoxNames[1], sBox18Name, sizeof(sBox18Name)), 0);
    EXPECT_EQ(memcmp(gPokemonStoragePtr->box19Name, sBox19Name, sizeof(sBox19Name)), 0);
    EXPECT_EQ(gPokemonStoragePtr->extraBoxWallpaper, 15);
    EXPECT_EQ(gPokemonStoragePtr->extensionBoxWallpapers[0], 16);
    EXPECT_EQ(gPokemonStoragePtr->extensionBoxWallpapers[1], 17);
    EXPECT_EQ(gPokemonStoragePtr->box19Wallpaper, 18);
    Free(legacyData);
}

TEST("BX18 initialization preserves every released BX16 byte")
{
    void *bx16Data;

    FillPokemonStoragePattern(0x91);
    bx16Data = Alloc(T_POKEMONSTORAGE_BX16_SIZE);
    memcpy(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE);

    InitPokemonStorageBox18Extension();

    EXPECT_EQ(memcmp(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 1, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 2, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 3, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    Free(bx16Data);
}

TEST("PokemonStorage chooses the shorter direction with 19 boxes")
{
    ResetPokemonStorageSystem();
    gPokemonStoragePtr->currentBox = 0;
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(9), 1);
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(10), -1);

    gPokemonStoragePtr->currentBox = 18;
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(8), 1);
    EXPECT_EQ(PokemonStorageSystem_TestDetermineBoxScrollDirection(9), -1);
}

TEST("PokemonStorage survives a real flash save and load byte for byte")
{
    struct PokemonStorage *expected;

    gTestRunnerState.timeoutSeconds = 120;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x27);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);

    Free(expected);
}

TEST("A failed full save preserves the committed partial-save storage snapshot")
{
    struct PokemonStorage *expected;
    u8 *committedTail;
    u16 (*realProgramFlashSector)(u16, u8 *);

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x35);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    expected = Alloc(sizeof(*expected));
    committedTail = Alloc(sizeof(gSaveBlock1Ptr->pokemonStorageExtensionTail));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));
    memcpy(committedTail,
           gSaveBlock1Ptr->pokemonStorageExtensionTail,
           sizeof(gSaveBlock1Ptr->pokemonStorageExtensionTail));

    FillPokemonStoragePattern(0xC7);
    realProgramFlashSector = ProgramFlashSector;
    ProgramFlashSector = FailProgramFlashSector;
    HandleSavingData(SAVE_NORMAL);
    ProgramFlashSector = realProgramFlashSector;

    EXPECT(gDamagedSaveSectors != 0);
    EXPECT_EQ(memcmp(committedTail,
                     gSaveBlock1Ptr->pokemonStorageExtensionTail,
                     sizeof(gSaveBlock1Ptr->pokemonStorageExtensionTail)),
              0);

    // A partial save after the failed full save must retain the old storage
    // record as one valid combined BX18 snapshot.
    EXPECT_EQ(TrySavingData(SAVE_LINK), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);

    Free(committedTail);
    Free(expected);
}

TEST("Failures during overflow regular and auxiliary writes preserve the previous candidate")
{
    static const u16 sFailCalls[] = {0, 5, 15};
    struct PokemonStorage *expected;
    u32 i;

    gTestRunnerState.timeoutSeconds = 360;
    for (i = 0; i < ARRAY_COUNT(sFailCalls); i++)
    {
        u8 loadStatus;
        u32 committedCounter;
        u16 committedRotation;

        ResetPokemonStorageTestFlash();
        FillPokemonStoragePattern(0x41 + i);
        EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
        expected = Alloc(sizeof(*expected));
        memcpy(expected, gPokemonStoragePtr, sizeof(*expected));
        committedCounter = gSaveCounter;
        committedRotation = gLastWrittenSector;

        FillPokemonStoragePattern(0xB0 + i);
        sRealProgramFlashSector = ProgramFlashSector;
        sFailWriteCall = sFailCalls[i];
        sProgramFlashWriteCall = 0;
        ProgramFlashSector = FailSelectedProgramFlashWrite;
        HandleSavingData(SAVE_NORMAL);
        ProgramFlashSector = sRealProgramFlashSector;

        EXPECT(gDamagedSaveSectors != 0);
        EXPECT_EQ(gSaveCounter, committedCounter);
        EXPECT_EQ(gLastWrittenSector, committedRotation);
        memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
        loadStatus = LoadGameSave(SAVE_NORMAL);
        EXPECT(loadStatus == SAVE_STATUS_OK || loadStatus == SAVE_STATUS_ERROR);
        EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);
        Free(expected);
    }
}

TEST("Boxes 17 through 19 metadata and current-box values survive full saves")
{
    static const u8 sBox17Name[] = COMPOUND_STRING("BoxXVII");
    static const u8 sBox18Name[] = COMPOUND_STRING("BoxXVIII");
    static const u8 sBox19Name[] = COMPOUND_STRING("BoxXIX");
    struct Pokemon mon17;
    struct Pokemon mon18;
    struct Pokemon mon19;
    struct PokemonStorage *expected;

    gTestRunnerState.timeoutSeconds = 120;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    CreateMon(&mon17, SPECIES_PIKACHU, 42, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&mon18, SPECIES_EEVEE, 37, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&mon19, SPECIES_BULBASAUR, 51, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(16, 29, &mon17.box);
    SetBoxMonAt(17, 0, &mon18.box);
    SetBoxMonAt(18, 14, &mon19.box);
    memcpy(gPokemonStoragePtr->extensionBoxNames[0], sBox17Name, sizeof(sBox17Name));
    memcpy(gPokemonStoragePtr->extensionBoxNames[1], sBox18Name, sizeof(sBox18Name));
    memcpy(gPokemonStoragePtr->box19Name, sBox19Name, sizeof(sBox19Name));
    gPokemonStoragePtr->extensionBoxWallpapers[0] = 7;
    gPokemonStoragePtr->extensionBoxWallpapers[1] = 11;
    gPokemonStoragePtr->box19Wallpaper = 13;
    gPokemonStoragePtr->currentBox = 16;

    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);
    EXPECT_EQ(GetBoxMonDataAt(16, 29, MON_DATA_SPECIES), SPECIES_PIKACHU);
    EXPECT_EQ(GetBoxMonDataAt(17, 0, MON_DATA_SPECIES), SPECIES_EEVEE);
    EXPECT_EQ(GetBoxMonDataAt(18, 14, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(memcmp(GetBoxNamePtr(16), sBox17Name, sizeof(sBox17Name)), 0);
    EXPECT_EQ(memcmp(GetBoxNamePtr(17), sBox18Name, sizeof(sBox18Name)), 0);
    EXPECT_EQ(memcmp(GetBoxNamePtr(18), sBox19Name, sizeof(sBox19Name)), 0);
    EXPECT_EQ(gPokemonStoragePtr->extensionBoxWallpapers[0], 7);
    EXPECT_EQ(gPokemonStoragePtr->extensionBoxWallpapers[1], 11);
    EXPECT_EQ(gPokemonStoragePtr->box19Wallpaper, 13);
    EXPECT_EQ(StorageGetCurrentBox(), 16);

    gPokemonStoragePtr->currentBox = 17;
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(StorageGetCurrentBox(), 17);

    gPokemonStoragePtr->currentBox = 18;
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(StorageGetCurrentBox(), 18);

    Free(expected);
}

TEST("PokemonStorage loads a legacy save and initializes Boxes 16 through 19")
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
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 1, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 2, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(LEGACY_BOXES_COUNT + 3, 0), MON_DATA_SANITY_HAS_SPECIES), FALSE);

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
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);
    EXPECT_EQ(GetBoxMonDataAt(16, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonDataAt(17, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonDataAt(18, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);

    // The in-RAM migration is committed by the next full save.
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    memcpy(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(bx16Data, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX19_MAGIC);
    EXPECT_EQ(GetBoxMonDataAt(16, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonDataAt(17, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);
    EXPECT_EQ(GetBoxMonDataAt(18, 0, MON_DATA_SANITY_HAS_SPECIES), FALSE);

    Free(overflowSector);
    Free(bx16Data);
}

TEST("Deterministic legacy release-format save preserves every storage field during migration")
{
    struct SaveSector *sector;
    u8 *expectedStorage;

    gTestRunnerState.timeoutSeconds = 300;
    ResetPokemonStorageTestFlash();
    PopulateReleasedStorageContents(LEGACY_BOXES_COUNT,
                                    sLegacyFixtureNames,
                                    0x15000000,
                                    0x15150000,
                                    0xF1500000,
                                    0xF1515000);
    expectedStorage = Alloc(T_POKEMONSTORAGE_LEGACY_SIZE);
    memcpy(expectedStorage, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestSaveToLegacy(sector);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expectedStorage, gPokemonStoragePtr, T_POKEMONSTORAGE_LEGACY_SIZE), 0);
    VerifyReleasedStorageContents(LEGACY_BOXES_COUNT,
                                  sLegacyFixtureNames,
                                  0x15000000,
                                  0x15150000,
                                  0xF1500000,
                                  0xF1515000);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT), 0);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 1), 0);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 2), 0);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 3), 0);
    EXPECT_EQ(gPokemonStoragePtr->boxExtensionMagic, POKEMON_STORAGE_EXTENSION_MAGIC);
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);

    Free(sector);
    Free(expectedStorage);
}

TEST("Deterministic BX16 release-format save preserves every storage field during migration")
{
    struct SaveSector *sector;
    u8 *expectedStorage;

    gTestRunnerState.timeoutSeconds = 300;
    ResetPokemonStorageTestFlash();
    PopulateReleasedStorageContents(LEGACY_BOXES_COUNT + 1,
                                    sBx16FixtureNames,
                                    0x16000000,
                                    0x16160000,
                                    0xF1600000,
                                    0xF1616000);
    expectedStorage = Alloc(T_POKEMONSTORAGE_BX16_SIZE);
    memcpy(expectedStorage, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx16(sector);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expectedStorage, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    VerifyReleasedStorageContents(LEGACY_BOXES_COUNT + 1,
                                  sBx16FixtureNames,
                                  0x16000000,
                                  0x16160000,
                                  0xF1600000,
                                  0xF1616000);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 1), 0);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 2), 0);
    EXPECT_EQ(CountMonsInBox(LEGACY_BOXES_COUNT + 3), 0);
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);

    Free(sector);
    Free(expectedStorage);
}

TEST("Frozen independent BX16 image migrates without current storage setters or writer")
{
    u8 *image;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    image = Alloc(T_POKEMONSTORAGE_BX16_SIZE);
    BuildFrozenBx16StorageImage(image);
    InstallFrozenBx16StorageImage(image);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(image, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    EXPECT_EQ(StorageGetCurrentBox(), 15);
    EXPECT_EQ(memcmp(GetBoxNamePtr(0), sFrozenBx16Box1Name, sizeof(sFrozenBx16Box1Name)), 0);
    EXPECT_EQ(memcmp(GetBoxNamePtr(15), sFrozenBx16Box16Name, sizeof(sFrozenBx16Box16Name)), 0);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(0), 3);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(15), 7);
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_SPECIES), SPECIES_PIKACHU);
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_PERSONALITY), 0x12345678);
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_OT_ID), 0x89ABCDEF);
    EXPECT_EQ(GetBoxMonDataAt(15, 7, MON_DATA_SPECIES), SPECIES_EEVEE);
    EXPECT_EQ(GetBoxMonDataAt(15, 7, MON_DATA_PERSONALITY), 0x0BADCAFE);
    EXPECT_EQ(GetBoxMonDataAt(15, 7, MON_DATA_OT_ID), 0x10203040);
    EXPECT_EQ(CountMonsInBox(16), 0);
    EXPECT_EQ(CountMonsInBox(17), 0);
    EXPECT_EQ(CountMonsInBox(18), 0);
    EXPECT_EQ(gPokemonStoragePtr->box18ExtensionMagic, POKEMON_STORAGE_BOX18_MAGIC);

    Free(image);
}

TEST("Unreleased BX17 migration preserves Box 17 and initializes Boxes 18 and 19")
{
    static const u8 sName[] = COMPOUND_STRING("DevBX17");
    struct Pokemon mon;
    struct SaveSector *sector;
    u8 *expectedBx16;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_EEVEE, 44, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(16, 7, &mon.box);
    memcpy(GetBoxNamePtr(16), sName, sizeof(sName));
    PokemonStorageSystem_TestSetBoxWallpaper(16, 9);
    gPokemonStoragePtr->currentBox = 16;
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    expectedBx16 = Alloc(T_POKEMONSTORAGE_BX16_SIZE);
    memcpy(expectedBx16, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx17(sector);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expectedBx16, gPokemonStoragePtr, T_POKEMONSTORAGE_BX16_SIZE), 0);
    EXPECT_EQ(GetBoxMonDataAt(16, 7, MON_DATA_SPECIES), SPECIES_EEVEE);
    EXPECT_EQ(memcmp(GetBoxNamePtr(16), sName, sizeof(sName)), 0);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(16), 9);
    EXPECT_EQ(CountMonsInBox(17), 0);
    EXPECT_EQ(CountMonsInBox(18), 0);
    EXPECT_EQ(StorageGetCurrentBox(), 16);

    Free(sector);
    Free(expectedBx16);
}

TEST("Unreleased BX18 migration preserves its frozen 41624-byte image and initializes Box 19")
{
    struct SaveSector *sector;
    u8 *expectedBx18;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x76);
    gPokemonStoragePtr->currentBox = 17;
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    expectedBx18 = Alloc(T_POKEMONSTORAGE_BX18_SIZE);
    memcpy(expectedBx18, gPokemonStoragePtr, T_POKEMONSTORAGE_BX18_SIZE);
    *(u32 *)&expectedBx18[offsetof(struct PokemonStorage, box18ExtensionMagic)] = POKEMON_STORAGE_BOX18_MAGIC;
    *(u16 *)&expectedBx18[offsetof(struct PokemonStorage, box18Checksum)] =
        CalculateTestSaveChecksum(
            &expectedBx18[offsetof(struct PokemonStorage, extensionBoxes)],
            T_POKEMONSTORAGE_BX18_SIZE - offsetof(struct PokemonStorage, extensionBoxes));
    *(u16 *)&expectedBx18[offsetof(struct PokemonStorage, box18ChecksumInverse)] =
        (u16)~*(u16 *)&expectedBx18[offsetof(struct PokemonStorage, box18Checksum)];
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);

    memset(gPokemonStoragePtr, 0xCC, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expectedBx18, gPokemonStoragePtr, T_POKEMONSTORAGE_BX18_SIZE), 0);
    EXPECT_EQ(CountMonsInBox(18), 0);
    EXPECT_EQ(memcmp(GetBoxNamePtr(18), COMPOUND_STRING("Box19"), 6), 0);
    EXPECT_EQ(PokemonStorageSystem_TestGetBoxWallpaper(18), 18);

    Free(sector);
    Free(expectedBx18);
}

TEST("PokemonStorage falls back when the newest overflow sector is lost")
{
    struct PokemonStorage *previousSave;
    u8 newestOverflowSector;

    // This test performs a chip erase, two full saves, and a sector erase.
    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x19);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0xA4);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    newestOverflowSector = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + (gSaveCounter % NUM_SAVE_SLOTS);
    EXPECT_EQ(EraseFlashSector(newestOverflowSector), 0);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(previousSave);
}

TEST("PokemonStorage falls back for every corrupt BX18 overflow integrity field")
{
    static const u16 sCorruptOffsets[] =
    {
        offsetof(struct PokemonStorage, box18ExtensionMagic) - T_POKEMONSTORAGE_REGULAR_SIZE,
        offsetof(struct PokemonStorage, box18Checksum) - T_POKEMONSTORAGE_REGULAR_SIZE,
        offsetof(struct PokemonStorage, box18ChecksumInverse) - T_POKEMONSTORAGE_REGULAR_SIZE,
        offsetof(struct PokemonStorage, extensionBoxes) - T_POKEMONSTORAGE_REGULAR_SIZE + 137,
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

TEST("BX19 cannot be reinterpreted as BX18 after its distinguishing magic bit is cleared")
{
    struct PokemonStorage *previousSave;
    struct SaveSector *overflowSector;
    u16 magicOffset = T_POKEMONSTORAGE_BX16_SIZE - T_POKEMONSTORAGE_REGULAR_SIZE;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x11);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    // Keep currentBox below 18 so the frozen BX18 bounds check cannot detect
    // the corruption on its own.
    FillPokemonStoragePattern(0x20);
    EXPECT(gPokemonStoragePtr->currentBox < 18);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    overflowSector = Alloc(sizeof(*overflowSector));
    ReadNewestOverflowSector(overflowSector);
    EXPECT_EQ(*(u32 *)&overflowSector->data[magicOffset], POKEMON_STORAGE_BOX19_MAGIC);
    *(u32 *)&overflowSector->data[magicOffset] = POKEMON_STORAGE_BOX18_MAGIC;
    WriteNewestOverflowSector(overflowSector);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(overflowSector);
    Free(previousSave);
}

TEST("PokemonStorage falls back when the BX18 SaveBlock1 suffix is corrupt")
{
    static const u16 sCorruptOffsets[] = {0, 971, 1943};
    struct PokemonStorage *previousSave;
    struct SaveSector *originalSector;
    struct SaveSector *corruptSector;
    u32 i;
    u8 newestSaveBlock1Sector;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x4A);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0xD3);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    newestSaveBlock1Sector = GetNewestSaveSectorId(SECTOR_ID_SAVEBLOCK1_END);
    originalSector = Alloc(sizeof(*originalSector));
    corruptSector = Alloc(sizeof(*corruptSector));
    ReadNewestSaveBlock1TailSector(originalSector);

    for (i = 0; i < ARRAY_COUNT(sCorruptOffsets); i++)
    {
        memcpy(corruptSector, originalSector, sizeof(*corruptSector));
        corruptSector->data[T_SAVEBLOCK1_EXTENSION_TAIL_SECTOR_OFFSET + sCorruptOffsets[i]] ^= 1;
        // Keep the normal SaveBlock1 sector checksum valid so this specifically
        // exercises the combined BX18 checksum.
        corruptSector->checksum = CalculateTestSaveChecksum(corruptSector->data, T_SAVEBLOCK1_LAST_SECTOR_SIZE);
        EXPECT_EQ(ProgramFlashSectorAndVerify(newestSaveBlock1Sector, (u8 *)corruptSector), 0);

        memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
        EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
        EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);
    }

    Free(corruptSector);
    Free(originalSector);
    Free(previousSave);
}

TEST("PokemonStorage overflow footer retains the released BX16 checksum")
{
    struct SaveSector *overflowSector;

    gTestRunnerState.timeoutSeconds = 120;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x6D);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    overflowSector = Alloc(sizeof(*overflowSector));
    ReadNewestOverflowSector(overflowSector);
    EXPECT_EQ(overflowSector->checksum,
              CalculateTestSaveChecksum(overflowSector->data, T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE));
    EXPECT_EQ(memcmp(overflowSector->data,
                     (u8 *)gPokemonStoragePtr + T_POKEMONSTORAGE_REGULAR_SIZE,
                     SECTOR_DATA_SIZE),
              0);

    Free(overflowSector);
}

TEST("BX19 auxiliary record has the fixed layout and round-trips Box 19")
{
    struct SaveSector *auxiliary;
    u32 i;

    gTestRunnerState.timeoutSeconds = 120;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0xA9);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    auxiliary = Alloc(sizeof(*auxiliary));
    ReadNewestAuxiliarySector(auxiliary);
    EXPECT_EQ(auxiliary->id, GetNewestAuxiliarySectorId());
    EXPECT_EQ(auxiliary->signature, SECTOR_SIGNATURE);
    EXPECT_EQ(auxiliary->counter, gSaveCounter);
    EXPECT_EQ(auxiliary->checksum, CalculateTestSaveChecksum(auxiliary->data, SECTOR_DATA_SIZE));
    EXPECT_EQ(*(u32 *)&auxiliary->data[0], POKEMON_STORAGE_BOX19_MAGIC);
    EXPECT_EQ(*(u16 *)&auxiliary->data[4], 1);
    EXPECT_EQ(*(u16 *)&auxiliary->data[6], T_BX19_PAYLOAD_SIZE);
    EXPECT_EQ(*(u16 *)&auxiliary->data[10], (u16)~*(u16 *)&auxiliary->data[8]);
    EXPECT_EQ(*(u16 *)&auxiliary->data[8],
              CalculateTestSaveChecksum(&auxiliary->data[T_BX19_HEADER_SIZE], T_BX19_PAYLOAD_SIZE));
    EXPECT_EQ(memcmp(&auxiliary->data[T_BX19_HEADER_SIZE],
                     &gPokemonStoragePtr->box19,
                     T_BX19_BOX_RECORD_SIZE),
              0);
    EXPECT_EQ(auxiliary->data[T_BX19_ARCHIVE_OFFSET], 0);
    for (i = T_BX19_USED_SIZE; i < SECTOR_DATA_SIZE; i++)
        EXPECT_EQ(auxiliary->data[i], 0);

    Free(auxiliary);
}

TEST("BX19 rejects every malformed auxiliary integrity field and falls back")
{
    static const u16 sInternalOffsets[] = {0, 4, 6, 8, 10, T_BX19_HEADER_SIZE + 137};
    struct PokemonStorage *previousSave;
    struct SaveSector *original;
    struct SaveSector *corrupt;
    u8 physicalSector;
    u32 i;

    gTestRunnerState.timeoutSeconds = 300;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x24);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0xD1);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    physicalSector = GetNewestAuxiliarySectorId();
    original = Alloc(sizeof(*original));
    corrupt = Alloc(sizeof(*corrupt));
    ReadFlash(physicalSector, 0, (u8 *)original, sizeof(*original));

    for (i = 0; i < ARRAY_COUNT(sInternalOffsets); i++)
    {
        memcpy(corrupt, original, sizeof(*corrupt));
        corrupt->data[sInternalOffsets[i]] ^= 1;
        corrupt->checksum = CalculateTestSaveChecksum(corrupt->data, SECTOR_DATA_SIZE);
        EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)corrupt), 0);
        memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
        EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
        EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);
    }

    memcpy(corrupt, original, sizeof(*corrupt));
    corrupt->checksum ^= 1;
    EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)corrupt), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    memcpy(corrupt, original, sizeof(*corrupt));
    corrupt->signature ^= 1;
    EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)corrupt), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    memcpy(corrupt, original, sizeof(*corrupt));
    corrupt->counter++;
    EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)corrupt), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(corrupt);
    Free(original);
    Free(previousSave);
}

TEST("BX19 requires its matching auxiliary sector but ignores an orphan")
{
    struct PokemonStorage *previousSave;
    struct SaveSector *auxiliary;
    u8 newestAuxiliary;
    u8 orphanAuxiliary;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x39);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    auxiliary = Alloc(sizeof(*auxiliary));
    ReadNewestAuxiliarySector(auxiliary);
    orphanAuxiliary = SECTOR_ID_BX19_AUXILIARY_1 + ((gSaveCounter + 1) % NUM_SAVE_SLOTS);
    auxiliary->id = orphanAuxiliary;
    auxiliary->counter++;
    EXPECT_EQ(ProgramFlashSectorAndVerify(orphanAuxiliary, (u8 *)auxiliary), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    FillPokemonStoragePattern(0xE4);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    newestAuxiliary = GetNewestAuxiliarySectorId();
    EXPECT_EQ(EraseFlashSector(newestAuxiliary), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(auxiliary);
    Free(previousSave);
}

TEST("Legacy Hall of Fame archives retain the newest eleven teams in chronological order")
{
    static const u8 sCounts[] = {0, 1, 11, 12, 30};
    struct SaveSector *sector;
    u32 caseId;

    gTestRunnerState.timeoutSeconds = 420;
    for (caseId = 0; caseId < ARRAY_COUNT(sCounts); caseId++)
    {
        u8 count = sCounts[caseId];
        u8 retained = min(count, HALL_OF_FAME_RETAINED_TEAMS);
        u8 first = count - retained;
        u32 i;

        ResetPokemonStorageTestFlash();
        ResetPokemonStorageSystem();
        SetGameStat(GAME_STAT_ENTERED_HOF, count);
        EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
        sector = Alloc(sizeof(*sector));
        ConvertNewestOverflowToBx18(sector);
        WriteLegacyHallOfFameTeams(count);

        memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
        EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
        AllocateHallOfFameTestBuffer();
        EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
        for (i = 0; i < retained; i++)
            EXPECT_EQ(gHoFSaveBuffer[i].mon[0].tid, 1000 + first + i);
        if (retained < HALL_OF_FAME_RETAINED_TEAMS)
            EXPECT_EQ((u16)gHoFSaveBuffer[retained].mon[0].species, SPECIES_NONE);

        // Migration remains in RAM/flash-neutral until this successful full save.
        EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
        memset(gHoFSaveBuffer, 0, sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
        memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
        EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
        EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
        for (i = 0; i < retained; i++)
            EXPECT_EQ(gHoFSaveBuffer[i].mon[0].tid, 1000 + first + i);

        Free(gHoFSaveBuffer);
        gHoFSaveBuffer = NULL;
        Free(sector);
    }
}

TEST("A failed first BX19 commit retains legacy Hall of Fame data for fallback and retry")
{
    struct SaveSector *sector;
    u32 committedCounter;
    u8 failedAuxiliary;
    u32 i;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    SetGameStat(GAME_STAT_ENTERED_HOF, 12);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);
    WriteLegacyHallOfFameTeams(12);
    Free(sector);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    committedCounter = gSaveCounter;
    failedAuxiliary = SECTOR_ID_BX19_AUXILIARY_1
                    + ((committedCounter + 1) % NUM_SAVE_SLOTS);

    sRealProgramFlashSector = ProgramFlashSector;
    sFailWriteCall = 15;
    sProgramFlashWriteCall = 0;
    ProgramFlashSector = FailSelectedProgramFlashWrite;
    HandleSavingData(SAVE_NORMAL);
    ProgramFlashSector = sRealProgramFlashSector;

    EXPECT(gDamagedSaveSectors != 0);
    EXPECT_EQ(gSaveCounter, committedCounter);
    // Model a failed flash program that destroyed this half of the old archive.
    EXPECT_EQ(EraseFlashSector(failedAuxiliary), 0);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    AllocateHallOfFameTestBuffer();
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    for (i = 0; i < HALL_OF_FAME_RETAINED_TEAMS; i++)
        EXPECT_EQ(gHoFSaveBuffer[i].mon[0].tid, 1001 + i);

    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    memset(gHoFSaveBuffer, 0, sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    for (i = 0; i < HALL_OF_FAME_RETAINED_TEAMS; i++)
        EXPECT_EQ(gHoFSaveBuffer[i].mon[0].tid, 1001 + i);

    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;
}

TEST("A failed first BX19 Hall of Fame save does not retain the uncommitted team")
{
    struct HallofFameTeam newTeam = {0};
    struct SaveSector *sector;
    u32 committedCounter;
    u8 failedAuxiliary;
    u32 i;

    gTestRunnerState.timeoutSeconds = 300;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    SetGameStat(GAME_STAT_ENTERED_HOF, 12);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);
    WriteLegacyHallOfFameTeams(12);
    Free(sector);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    AllocateHallOfFameTestBuffer();
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    newTeam.mon[0].species = SPECIES_EEVEE;
    newTeam.mon[0].tid = 7777;
    AppendRetainedHallOfFameTeam(gHoFSaveBuffer, &newTeam);
    committedCounter = gSaveCounter;
    failedAuxiliary = SECTOR_ID_BX19_AUXILIARY_1
                    + ((committedCounter + 1) % NUM_SAVE_SLOTS);

    sRealProgramFlashSector = ProgramFlashSector;
    sFailWriteCall = 15;
    sProgramFlashWriteCall = 0;
    ProgramFlashSector = FailSelectedProgramFlashWrite;
    HandleSavingData(SAVE_HALL_OF_FAME);
    ProgramFlashSector = sRealProgramFlashSector;

    EXPECT(gDamagedSaveSectors != 0);
    EXPECT_EQ(gSaveCounter, committedCounter);
    EXPECT_EQ(GetGameStat(GAME_STAT_ENTERED_HOF), 12);
    EXPECT_EQ(EraseFlashSector(failedAuxiliary), 0);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    memset(gHoFSaveBuffer, 0,
           sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    for (i = 0; i < HALL_OF_FAME_RETAINED_TEAMS; i++)
        EXPECT_EQ(gHoFSaveBuffer[i].mon[0].tid, 1001 + i);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;
}

TEST("Pre-write Hall of Fame migration OOM cannot wipe legacy sectors during recovery")
{
    struct SaveSector *sector;
    u8 *legacySectorsBefore;
    void *heapHog;
    MainCallback previousCallback;
    u32 committedCounter;
    u32 i;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    SetGameStat(GAME_STAT_ENTERED_HOF, 12);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);
    WriteLegacyHallOfFameTeams(12);
    Free(sector);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    committedCounter = gSaveCounter;
    legacySectorsBefore = Alloc(SECTOR_SIZE * NUM_HOF_SECTORS);
    for (i = 0; i < NUM_HOF_SECTORS; i++)
    {
        ReadFlash(SECTOR_ID_HOF_1 + i,
                  0,
                  &legacySectorsBefore[i * SECTOR_SIZE],
                  SECTOR_SIZE);
    }
    // Leave less than the one-time 1,588-byte migration retry archive. The
    // normal save path no longer needs the old 3,892 + 7,936-byte snapshots.
    heapHog = AllocUnchecked(HEAP_SIZE - 9500);
    EXPECT(heapHog != NULL);
    previousCallback = gMain.callback2;

    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_PREPARE_ERROR);
    EXPECT_EQ(gDamagedSaveSectors, 0);
    EXPECT_EQ(gSaveCounter, committedCounter);
    EXPECT_EQ(gMain.callback2, previousCallback);

    // Exercise the same wipe step used by the failure-screen recovery. With
    // no flash failures recorded it must touch neither legacy sector.
    EXPECT(!SaveFailedScreen_TestWipeDamagedSectors());
    for (i = 0; i < NUM_HOF_SECTORS; i++)
    {
        ReadFlash(SECTOR_ID_HOF_1 + i,
                  0,
                  (u8 *)&gSaveDataBuffer,
                  SECTOR_SIZE);
        EXPECT_EQ(memcmp(&legacySectorsBefore[i * SECTOR_SIZE],
                         &gSaveDataBuffer,
                         SECTOR_SIZE),
                  0);
    }

    EXPECT(LinkFullSave_Init());
    EXPECT_EQ(gDamagedSaveSectors, 0);
    EXPECT_EQ(gMain.callback2, previousCallback);
    Free(heapHog);
    Free(legacySectorsBefore);

    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    AllocateHallOfFameTestBuffer();
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    EXPECT_EQ(gHoFSaveBuffer[0].mon[0].tid, 1001);
    EXPECT_EQ(gHoFSaveBuffer[HALL_OF_FAME_RETAINED_TEAMS - 1].mon[0].tid, 1011);

    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;
}

TEST("Committed BX19 full saves do not require a sector-sized heap snapshot")
{
    void *heapHog;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    AllocateHallOfFameTestBuffer();
    gHoFSaveBuffer[0].mon[0].species = SPECIES_EEVEE;
    gHoFSaveBuffer[0].mon[0].tid = 4242;
    EXPECT_EQ(TrySavingData(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;

    heapHog = AllocUnchecked(HEAP_SIZE - 3000);
    EXPECT(heapHog != NULL);
    FillPokemonStoragePattern(0xA4);
    gPokemonStoragePtr->box18ExtensionMagic = POKEMON_STORAGE_BOX19_MAGIC;
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(gDamagedSaveSectors, 0);
    Free(heapHog);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(((u8 *)gPokemonStoragePtr)[1234],
              (u8)(0xA4 + 1234 * 37 + (1234 >> 8)));
    AllocateHallOfFameTestBuffer();
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    EXPECT_EQ(gHoFSaveBuffer[0].mon[0].tid, 4242);
    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;
}

TEST("Preparation OOM reaches link trade Mystery Gift and chat error paths")
{
    struct SaveSector *sector;
    void *heapHog;
    u8 taskId;
    u8 mysteryGiftState;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);
    Free(sector);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    heapHog = AllocUnchecked(HEAP_SIZE - 1000);
    EXPECT(heapHog != NULL);

    taskId = CreateTask(Task_LinkFullSave, 0);
    gTasks[taskId].data[0] = 3;
    gTasks[taskId].data[2] = TRUE;
    Task_LinkFullSave(taskId);
    EXPECT_EQ(gTasks[taskId].data[0], 7);
    EXPECT_EQ(GetLinkFullSaveResult(), LINK_FULL_SAVE_RESULT_FAILED);
    EXPECT_EQ(gSaveAttemptStatus, SAVE_STATUS_PREPARE_ERROR);
    EXPECT_EQ(gDamagedSaveSectors, 0);
    DestroyTask(taskId);

    EXPECT(!Trade_TestTryInitFullSave());
    EXPECT_EQ(gSaveAttemptStatus, SAVE_STATUS_PREPARE_ERROR);
    EXPECT_EQ(gDamagedSaveSectors, 0);

    mysteryGiftState = 1;
    EXPECT_EQ(MysteryGiftMenu_TestAdvanceSaveState(&mysteryGiftState), 5);
    EXPECT_EQ(gSaveAttemptStatus, SAVE_STATUS_PREPARE_ERROR);
    EXPECT_EQ(gDamagedSaveSectors, 0);

    EXPECT(!UnionRoomChat_TestTrySave());
    EXPECT_EQ(gSaveAttemptStatus, SAVE_STATUS_PREPARE_ERROR);
    EXPECT_EQ(gDamagedSaveSectors, 0);

    Free(heapHog);
}

TEST("Battle Tower link-save waiter reports preparation OOM after both handshakes")
{
    struct SaveSector *sector;
    u32 regularSignatures[NUM_SECTORS_PER_SLOT];
    u32 regularCounters[NUM_SECTORS_PER_SLOT];
    u32 committedCounter;
    u32 committedLastSector;
    u32 auxiliarySignature;
    u32 auxiliaryCounter;
    u32 overflowSignature;
    u32 overflowCounter;
    void *heapHog;
    u8 regularSlotStart;
    u8 auxiliarySector;
    u8 overflowSector;
    u8 taskId;
    u32 i;
    u32 value;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);
    Free(sector);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    committedCounter = gSaveCounter;
    committedLastSector = gLastWrittenSector;

    regularSlotStart = NUM_SECTORS_PER_SLOT * ((committedCounter + 1) % NUM_SAVE_SLOTS);
    auxiliarySector = SECTOR_ID_BX19_AUXILIARY_1 + ((committedCounter + 1) % NUM_SAVE_SLOTS);
    overflowSector = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + ((committedCounter + 1) % NUM_SAVE_SLOTS);
    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlash(regularSlotStart + i, SECTOR_SIGNATURE_OFFSET, (u8 *)&regularSignatures[i], sizeof(regularSignatures[i]));
        ReadFlash(regularSlotStart + i, SECTOR_COUNTER_OFFSET, (u8 *)&regularCounters[i], sizeof(regularCounters[i]));
    }
    ReadFlash(auxiliarySector, SECTOR_SIGNATURE_OFFSET, (u8 *)&auxiliarySignature, sizeof(auxiliarySignature));
    ReadFlash(auxiliarySector, SECTOR_COUNTER_OFFSET, (u8 *)&auxiliaryCounter, sizeof(auxiliaryCounter));
    ReadFlash(overflowSector, SECTOR_SIGNATURE_OFFSET, (u8 *)&overflowSignature, sizeof(overflowSignature));
    ReadFlash(overflowSector, SECTOR_COUNTER_OFFSET, (u8 *)&overflowCounter, sizeof(overflowCounter));

    heapHog = AllocUnchecked(HEAP_SIZE - 1000);
    EXPECT(heapHog != NULL);
    gWirelessCommType = 0;
    gLinkCallback = NULL;
    SaveForBattleTowerLink();
    taskId = FindTaskIdByFunc(Task_LinkFullSave);
    EXPECT_NE(taskId, TASK_NONE);

    Task_LinkFullSave(taskId); // Enable soft-reset protection.
    Task_LinkFullSave(taskId); // Request the initial standby handshake.
    EXPECT(gLinkCallback != NULL);
    gLinkCallback = NULL;
    Task_LinkFullSave(taskId); // Initial handshake completed.
    Task_LinkFullSave(taskId); // Injected OOM is observed before any write.
    EXPECT_EQ(gTasks[taskId].data[0], 7);
    EXPECT_EQ(GetLinkFullSaveResult(), LINK_FULL_SAVE_RESULT_FAILED);
    EXPECT_EQ(gSaveAttemptStatus, SAVE_STATUS_PREPARE_ERROR);

    Task_LinkFullSave(taskId); // Request the commit-safe handshake.
    EXPECT(gLinkCallback != NULL);
    gLinkCallback = NULL;
    Task_LinkFullSave(taskId);
    Task_LinkFullSave(taskId); // Request the final handshake.
    EXPECT(gLinkCallback != NULL);
    gLinkCallback = NULL;
    Task_LinkFullSave(taskId);
    for (i = 0; i < 6; i++)
        Task_LinkFullSave(taskId);
    EXPECT(!FuncIsActiveTask(Task_LinkFullSave));
    EXPECT(!gSoftResetDisabled);

    gSpecialVar_Result = TRUE;
    EXPECT(StartMenu_TestRunBattleTowerLinkSaveWaiter());
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT_EQ(gSaveCounter, committedCounter);
    EXPECT_EQ(gLastWrittenSector, committedLastSector);
    EXPECT_EQ(gDamagedSaveSectors, 0);

    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlash(regularSlotStart + i, SECTOR_SIGNATURE_OFFSET, (u8 *)&value, sizeof(value));
        EXPECT_EQ(value, regularSignatures[i]);
        ReadFlash(regularSlotStart + i, SECTOR_COUNTER_OFFSET, (u8 *)&value, sizeof(value));
        EXPECT_EQ(value, regularCounters[i]);
    }
    ReadFlash(auxiliarySector, SECTOR_SIGNATURE_OFFSET, (u8 *)&value, sizeof(value));
    EXPECT_EQ(value, auxiliarySignature);
    ReadFlash(auxiliarySector, SECTOR_COUNTER_OFFSET, (u8 *)&value, sizeof(value));
    EXPECT_EQ(value, auxiliaryCounter);
    ReadFlash(overflowSector, SECTOR_SIGNATURE_OFFSET, (u8 *)&value, sizeof(value));
    EXPECT_EQ(value, overflowSignature);
    ReadFlash(overflowSector, SECTOR_COUNTER_OFFSET, (u8 *)&value, sizeof(value));
    EXPECT_EQ(value, overflowCounter);

    // The allocation remains exhausted through task completion, proving the
    // caller-visible failure path does not retry preparation forever.
    EXPECT_EQ(GetLinkFullSaveResult(), LINK_FULL_SAVE_RESULT_FAILED);
    Free(heapHog);
}

TEST("Legacy Hall of Fame loading does not require a migration heap buffer")
{
    struct SaveSector *sector;
    void *heapHog;
    u32 i;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    SetGameStat(GAME_STAT_ENTERED_HOF, 12);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);
    WriteLegacyHallOfFameTeams(12);
    Free(sector);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    AllocateHallOfFameTestBuffer();
    heapHog = AllocUnchecked(HEAP_SIZE - 3000);
    EXPECT(heapHog != NULL);

    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    for (i = 0; i < HALL_OF_FAME_RETAINED_TEAMS; i++)
        EXPECT_EQ(gHoFSaveBuffer[i].mon[0].tid, 1001 + i);

    Free(heapHog);
    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;
}

TEST("A corrupt legacy Hall of Fame archive migrates as empty without rejecting the normal save")
{
    struct SaveSector *sector;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    sector = Alloc(sizeof(*sector));
    ConvertNewestOverflowToBx18(sector);
    WriteLegacyHallOfFameTeams(12);
    ReadFlash(SECTOR_ID_HOF_2, 0, (u8 *)sector, sizeof(*sector));
    sector->signature ^= 1;
    EXPECT_EQ(ProgramFlashSectorAndVerify(SECTOR_ID_HOF_2, (u8 *)sector), 0);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    AllocateHallOfFameTestBuffer();
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    EXPECT_EQ((u16)gHoFSaveBuffer[0].mon[0].species, SPECIES_NONE);

    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;
    Free(sector);
}

TEST("Hall of Fame PC rejects an empty retained archive before drawing sprites")
{
    struct HallofFameTeam *teams;

    teams = AllocZeroed(sizeof(*teams) * HALL_OF_FAME_RETAINED_TEAMS);
    EXPECT_EQ(CountRetainedHallOfFameTeams(teams), 0);
    teams[0].mon[0].species = SPECIES_BULBASAUR;
    EXPECT_EQ(CountRetainedHallOfFameTeams(teams), 1);
    Free(teams);
}

TEST("Hall of Fame retention drops only the oldest and preserves lifetime numbering")
{
    struct HallofFameTeam *teams;
    struct HallofFameTeam newTeam = {0};
    u32 i;

    teams = AllocZeroed(sizeof(*teams) * HALL_OF_FAME_RETAINED_TEAMS);
    for (i = 0; i < HALL_OF_FAME_RETAINED_TEAMS; i++)
    {
        teams[i].mon[0].species = SPECIES_BULBASAUR;
        teams[i].mon[0].tid = i + 1;
    }
    newTeam.mon[0].species = SPECIES_EEVEE;
    newTeam.mon[0].tid = 12;
    AppendRetainedHallOfFameTeam(teams, &newTeam);
    for (i = 0; i < HALL_OF_FAME_RETAINED_TEAMS; i++)
        EXPECT_EQ(teams[i].mon[0].tid, i + 2);

    SetGameStat(GAME_STAT_ENTERED_HOF, 30);
    EXPECT_EQ(GetRetainedHallOfFameTeamNumber(0, HALL_OF_FAME_RETAINED_TEAMS), 20);
    EXPECT_EQ(GetRetainedHallOfFameTeamNumber(10, HALL_OF_FAME_RETAINED_TEAMS), 30);
    Free(teams);
}

TEST("Hall of Fame failure cleanup preserves the appended team for the recovery retry")
{
    u32 committedCounter;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    SetGameStat(GAME_STAT_ENTERED_HOF, 0);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    committedCounter = gSaveCounter;

    AllocateHallOfFameTestBuffer();
    gHoFSaveBuffer[0].mon[0].species = SPECIES_BULBASAUR;
    gHoFSaveBuffer[0].mon[0].tid = 777;
    sRealProgramFlashSector = ProgramFlashSector;
    sFailWriteCall = 15;
    sProgramFlashWriteCall = 0;
    ProgramFlashSector = FailSelectedProgramFlashWrite;
    HandleSavingData(SAVE_HALL_OF_FAME);
    ProgramFlashSector = sRealProgramFlashSector;

    EXPECT(gDamagedSaveSectors != 0);
    EXPECT_EQ(GetGameStat(GAME_STAT_ENTERED_HOF), 0);
    EXPECT_EQ(gSaveCounter, committedCounter);
    HallOfFame_TestCleanupAfterSaveFailure();
    EXPECT(gHoFSaveBuffer != NULL);
    EXPECT_EQ(TrySavingData(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    EXPECT_EQ(GetGameStat(GAME_STAT_ENTERED_HOF), 1);
    memset(gHoFSaveBuffer, 0, sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
    EXPECT_EQ(LoadGameSave(SAVE_HALL_OF_FAME), SAVE_STATUS_OK);
    EXPECT_EQ(gHoFSaveBuffer[0].mon[0].tid, 777);
    EXPECT_EQ((u16)gHoFSaveBuffer[1].mon[0].species, SPECIES_NONE);

    Free(gHoFSaveBuffer);
    gHoFSaveBuffer = NULL;
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

TEST("PokemonStorage never classifies malformed nonzero regular extension bytes as legacy")
{
    struct PokemonStorage *previousSave;
    struct SaveSector *sector;
    u8 physicalSector;
    u16 extensionOffset = offsetof(struct PokemonStorage, boxExtensionMagic) - 8 * SECTOR_DATA_SIZE;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x28);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0x91);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    physicalSector = GetNewestSaveSectorId(SECTOR_ID_PKMN_STORAGE_END);
    sector = Alloc(sizeof(*sector));
    ReadFlash(physicalSector, 0, (u8 *)sector, sizeof(*sector));
    *(u32 *)&sector->data[extensionOffset] = 0xDEADBEEF;
    sector->checksum = CalculateTestSaveChecksum(sector->data, SECTOR_DATA_SIZE);
    EXPECT_EQ(ProgramFlashSectorAndVerify(physicalSector, (u8 *)sector), 0);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(sector);
    Free(previousSave);
}

TEST("PokemonStorage falls back for missing and counter-mismatched overflow")
{
    struct PokemonStorage *previousSave;
    struct SaveSector *originalOverflow;
    struct SaveSector *badOverflow;
    struct SaveSector *originalSaveBlock1Sector;
    struct SaveSector *badSaveBlock1Sector;
    u8 newestOverflowSector;
    u8 newestSaveBlock1Sector;

    gTestRunnerState.timeoutSeconds = 240;
    ResetPokemonStorageTestFlash();

    FillPokemonStoragePattern(0x43);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    previousSave = Alloc(sizeof(*previousSave));
    memcpy(previousSave, gPokemonStoragePtr, sizeof(*previousSave));

    FillPokemonStoragePattern(0xC1);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    newestOverflowSector = GetNewestOverflowSectorId();
    newestSaveBlock1Sector = GetNewestSaveSectorId(SECTOR_ID_SAVEBLOCK1_END);
    originalOverflow = Alloc(sizeof(*originalOverflow));
    badOverflow = Alloc(sizeof(*badOverflow));
    originalSaveBlock1Sector = Alloc(sizeof(*originalSaveBlock1Sector));
    badSaveBlock1Sector = Alloc(sizeof(*badSaveBlock1Sector));
    ReadNewestOverflowSector(originalOverflow);
    ReadNewestSaveBlock1TailSector(originalSaveBlock1Sector);

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

    EXPECT_EQ(ProgramFlashSectorAndVerify(newestOverflowSector, (u8 *)originalOverflow), 0);
    EXPECT_EQ(EraseFlashSector(newestSaveBlock1Sector), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    memcpy(badSaveBlock1Sector, originalSaveBlock1Sector, sizeof(*badSaveBlock1Sector));
    badSaveBlock1Sector->counter++;
    EXPECT_EQ(ProgramFlashSectorAndVerify(newestSaveBlock1Sector, (u8 *)badSaveBlock1Sector), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR);
    EXPECT_EQ(memcmp(previousSave, gPokemonStoragePtr, sizeof(*previousSave)), 0);

    Free(badSaveBlock1Sector);
    Free(originalSaveBlock1Sector);
    Free(badOverflow);
    Free(originalOverflow);
    Free(previousSave);
}

TEST("LinkFullSave persists Boxes 17 through 19")
{
    static const u8 sLinkName17[] = COMPOUND_STRING("Link 17");
    static const u8 sLinkName18[] = COMPOUND_STRING("Link 18");
    static const u8 sLinkName19[] = COMPOUND_STRING("Link 19");
    struct Pokemon mon17;
    struct Pokemon mon18;
    struct Pokemon mon19;
    struct PokemonStorage *expected;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    CreateMon(&mon17, SPECIES_EEVEE, 25, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&mon18, SPECIES_PIKACHU, 31, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&mon19, SPECIES_BULBASAUR, 36, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(16, 4, &mon17.box);
    SetBoxMonAt(17, 25, &mon18.box);
    SetBoxMonAt(18, 12, &mon19.box);
    memcpy(gPokemonStoragePtr->extensionBoxNames[0], sLinkName17, sizeof(sLinkName17));
    memcpy(gPokemonStoragePtr->extensionBoxNames[1], sLinkName18, sizeof(sLinkName18));
    memcpy(gPokemonStoragePtr->box19Name, sLinkName19, sizeof(sLinkName19));
    gPokemonStoragePtr->extensionBoxWallpapers[0] = 11;
    gPokemonStoragePtr->extensionBoxWallpapers[1] = 13;
    gPokemonStoragePtr->box19Wallpaper = 15;
    gPokemonStoragePtr->currentBox = 18;

    RunLinkFullSave();
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);

    Free(expected);
}

TEST("Incremental link full saves preserve fallback across every transactional phase")
{
    static const u16 sFailCalls[] = {0, 5, 14};
    struct PokemonStorage *expected;
    u32 i;

    gTestRunnerState.timeoutSeconds = 360;
    for (i = 0; i < ARRAY_COUNT(sFailCalls); i++)
    {
        u8 loadStatus;
        MainCallback previousCallback = gMain.callback2;

        ResetPokemonStorageTestFlash();
        FillPokemonStoragePattern(0x52 + i);
        EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
        expected = Alloc(sizeof(*expected));
        memcpy(expected, gPokemonStoragePtr, sizeof(*expected));
        FillPokemonStoragePattern(0xC0 + i);

        sRealProgramFlashSector = ProgramFlashSector;
        sFailWriteCall = sFailCalls[i];
        sProgramFlashWriteCall = 0;
        ProgramFlashSector = FailSelectedProgramFlashWrite;
        if (!LinkFullSave_Init())
        {
            while (!LinkFullSave_WriteSector())
                ;
            LinkFullSave_ReplaceLastSector();
            LinkFullSave_SetLastSectorSignature();
        }
        ProgramFlashSector = sRealProgramFlashSector;
        SetMainCallback2(previousCallback);

        EXPECT(gDamagedSaveSectors != 0);
        memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
        loadStatus = LoadGameSave(SAVE_NORMAL);
        EXPECT(loadStatus == SAVE_STATUS_OK || loadStatus == SAVE_STATUS_ERROR);
        EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);
        Free(expected);
    }
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

TEST("SAVE_LINK cannot half-save a move between a released box and BX18")
{
    struct Pokemon mon;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_BULBASAUR, 18, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(0, 0, &mon.box);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    SetBoxMonAt(17, 0, GetBoxedMonPtr(0, 0));
    ZeroBoxMonAt(0, 0);
    EXPECT_EQ(TrySavingData(SAVE_LINK), SAVE_STATUS_OK);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetBoxMonDataAt(17, 0, MON_DATA_SPECIES), SPECIES_NONE);
}

TEST("SAVE_LINK cannot half-save moves to or from Box 19")
{
    struct Pokemon mon;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_EEVEE, 28, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(0, 0, &mon.box);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    SetBoxMonAt(18, 0, GetBoxedMonPtr(0, 0));
    ZeroBoxMonAt(0, 0);
    EXPECT_EQ(TrySavingData(SAVE_LINK), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(GetBoxMonDataAt(0, 0, MON_DATA_SPECIES), SPECIES_EEVEE);
    EXPECT_EQ(GetBoxMonDataAt(18, 0, MON_DATA_SPECIES), SPECIES_NONE);

    SetBoxMonAt(18, 0, &mon.box);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    SetBoxMonAt(1, 0, GetBoxedMonPtr(18, 0));
    ZeroBoxMonAt(18, 0);
    EXPECT_EQ(TrySavingData(SAVE_LINK), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(GetBoxMonDataAt(18, 0, MON_DATA_SPECIES), SPECIES_EEVEE);
    EXPECT_EQ(GetBoxMonDataAt(1, 0, MON_DATA_SPECIES), SPECIES_NONE);
}

TEST("An orphan newer overflow record cannot supersede the previous complete slot")
{
    struct PokemonStorage *expected;
    struct SaveSector *overflowSector;
    u8 orphanSector;

    gTestRunnerState.timeoutSeconds = 180;
    ResetPokemonStorageTestFlash();
    FillPokemonStoragePattern(0x2C);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    expected = Alloc(sizeof(*expected));
    memcpy(expected, gPokemonStoragePtr, sizeof(*expected));

    overflowSector = Alloc(sizeof(*overflowSector));
    ReadNewestOverflowSector(overflowSector);
    overflowSector->counter++;
    orphanSector = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + (overflowSector->counter % NUM_SAVE_SLOTS);
    overflowSector->id = orphanSector;
    EXPECT_EQ(ProgramFlashSectorAndVerify(orphanSector, (u8 *)overflowSector), 0);

    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(memcmp(expected, gPokemonStoragePtr, sizeof(*expected)), 0);

    Free(overflowSector);
    Free(expected);
}

TEST("Boxes 17 through 19 participate in fullness and search paths")
{
    struct Pokemon mon;
    u32 boxId;
    u32 boxPosition;

    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&mon, MOVE_NONE, 0);
    SetMonMoveSlot(&mon, MOVE_NONE, 1);
    SetMonMoveSlot(&mon, MOVE_NONE, 2);
    SetMonMoveSlot(&mon, MOVE_NONE, 3);

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT - 1; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
            SetBoxMonAt(boxId, boxPosition, &mon.box);
    }

    EXPECT(!IsPokemonStorageFull());
    EXPECT(CheckFreePokemonStorageSpace());
    EXPECT_EQ(GetFirstFreeBoxSpot(18), 0);

    // Put the searched move only in Box 19 so skipping a new box is caught.
    SetMonMoveSlot(&mon, MOVE_TACKLE, 0);
    SetBoxMonAt(18, IN_BOX_COUNT - 1, &mon.box);
    EXPECT_EQ(CountAllStorageMons(), (TOTAL_BOXES_COUNT - 1) * IN_BOX_COUNT + 1);
    EXPECT(AnyStorageMonWithMove(MOVE_TACKLE));

    for (boxPosition = 0; boxPosition < IN_BOX_COUNT - 1; boxPosition++)
        SetBoxMonAt(18, boxPosition, &mon.box);
    EXPECT(IsPokemonStorageFull());
    EXPECT(!CheckFreePokemonStorageSpace());
}

TEST("Pokemon deposit reaches Boxes 17 through 19 and wraps from Box 19 to Box 1")
{
    struct Pokemon mon;
    u32 boxId;
    u32 boxPosition;

    ResetPokemonStorageSystem();
    CreateMon(&mon, SPECIES_EEVEE, 20, 0, OTID_STRUCT_PLAYER_ID);
    for (boxId = 0; boxId < LEGACY_BOXES_COUNT + 1; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
            SetBoxMonAt(boxId, boxPosition, &mon.box);
    }
    EXPECT_EQ(CopyMonToPC(&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(gSpecialVar_MonBoxId, 16);
    EXPECT_EQ(gSpecialVar_MonBoxPos, 0);
    EXPECT_EQ(GetBoxMonDataAt(16, 0, MON_DATA_SPECIES), SPECIES_EEVEE);

    for (boxPosition = 1; boxPosition < IN_BOX_COUNT; boxPosition++)
        SetBoxMonAt(16, boxPosition, &mon.box);
    EXPECT_EQ(CopyMonToPC(&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(gSpecialVar_MonBoxId, 17);
    EXPECT_EQ(gSpecialVar_MonBoxPos, 0);
    EXPECT_EQ(GetBoxMonDataAt(17, 0, MON_DATA_SPECIES), SPECIES_EEVEE);

    for (boxPosition = 1; boxPosition < IN_BOX_COUNT; boxPosition++)
        SetBoxMonAt(17, boxPosition, &mon.box);
    EXPECT_EQ(CopyMonToPC(&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(gSpecialVar_MonBoxId, 18);
    EXPECT_EQ(gSpecialVar_MonBoxPos, 0);
    EXPECT_EQ(GetBoxMonDataAt(18, 0, MON_DATA_SPECIES), SPECIES_EEVEE);

    ResetPokemonStorageSystem();
    for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        SetBoxMonAt(18, boxPosition, &mon.box);
    gPokemonStoragePtr->currentBox = 18;
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
#undef T_POKEMONSTORAGE_BX17_SIZE
#undef T_POKEMONSTORAGE_BX18_SIZE
#undef T_POKEMONSTORAGE_REGULAR_SIZE
#undef T_POKEMONSTORAGE_BX16_OVERFLOW_SIZE
#undef T_POKEMONSTORAGE_BX18_OVERFLOW_OFFSET
#undef T_POKEMONSTORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET
#undef T_POKEMONSTORAGE_EXTENSION_TAIL_OFFSET
#undef T_SAVEBLOCK1_EXTENSION_TAIL_SECTOR_OFFSET
#undef T_POKEMONSTORAGE_LEGACY_LAST_SECTOR_SIZE
#undef T_SAVEBLOCK1_LAST_SECTOR_SIZE
#undef T_BX16_CURRENT_BOX_OFFSET
#undef T_BX16_BOXES_OFFSET
#undef T_BX16_BOX_NAMES_OFFSET
#undef T_BX16_BOX_WALLPAPERS_OFFSET
#undef T_BX16_EXTENSION_MAGIC_OFFSET
#undef T_BX16_EXTRA_BOX_OFFSET
#undef T_BX16_EXTRA_BOX_NAME_OFFSET
#undef T_BX16_EXTRA_BOX_WALLPAPER_OFFSET
#undef T_BX16_EXTRA_BOX_PADDING_OFFSET
#undef T_FROZEN_BOXMON_PERSONALITY_OFFSET
#undef T_FROZEN_BOXMON_OT_ID_OFFSET
#undef T_FROZEN_BOXMON_FLAGS_OFFSET
#undef T_FROZEN_BOXMON_SECURE_OFFSET
#undef T_FROZEN_BOXMON_HAS_SPECIES
#undef T_VS_SEEKER_SAVE_MAGIC_OFFSET
#undef T_VS_SEEKER_CHARGE_STEPS_OFFSET
#undef T_VS_SEEKER_SAVE_MAGIC_INV_OFFSET
#undef T_OBJECT_EVENT_TEMPLATE_SIZE
#undef T_OBJECT_EVENT_TEMPLATE_TRAINER_TYPE_OFFSET
#undef T_OBJECT_EVENT_TEMPLATE_SCRIPT_OFFSET
#undef T_OBJECT_EVENT_TEMPLATE_FLAG_ID_OFFSET
