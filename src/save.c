#include "global.h"
#include "agb_flash.h"
#include "gba/flash_internal.h"
#include "fieldmap.h"
#include "save.h"
#include "task.h"
#include "decompress.h"
#include "load_save.h"
#include "overworld.h"
#include "hall_of_fame.h"
#include "pokemon_storage_system.h"
#include "trainer_hill.h"
#include "link.h"
#include "constants/game_stat.h"

static u16 CalculateChecksum(void *, u16);
static bool8 ReadFlashSector(u8, struct SaveSector *);
static u8 GetSaveValidStatus(const struct SaveSectorLocation *);
static u8 CopySaveSlotData(u16, struct SaveSectorLocation *);
static u8 TryWriteSector(u8, u8 *);
static u8 HandleWriteSector(u16, const struct SaveSectorLocation *);
static u8 HandleReplaceSector(u16, const struct SaveSectorLocation *);
static void CopyToSaveBlock3(u32, struct SaveSector *);
static void CopyFromSaveBlock3(u32, struct SaveSector *);
static void PreparePokemonStorageExtensions(void);
static u8 WritePokemonStorageOverflow(void);
static bool8 IsPokemonStorageOverflowValid(u8, u32);
static void LoadPokemonStorageOverflow(void);

enum PokemonStorageOverflowStatus
{
    PKMN_STORAGE_OVERFLOW_INVALID,
    PKMN_STORAGE_OVERFLOW_BX16,
    PKMN_STORAGE_OVERFLOW_BX17,
};

// Divide save blocks into individual chunks to be written to flash sectors

/*
 * Sector Layout:
 *
 * Sectors 0 - 13:      Save Slot 1
 * Sectors 14 - 27:     Save Slot 2
 * Sectors 28 - 29:     Hall of Fame
 * Sector 30:           Pokémon Storage overflow for Save Slot 1
 * Sector 31:           Pokémon Storage overflow for Save Slot 2
 *
 * There are two save slots for saving the player's game data. We alternate between
 * them each time the game is saved, so that if the current save slot is corrupt,
 * we can load the previous one. We also rotate the sectors in each save slot
 * so that the same data is not always being written to the same sector. This
 * might be done to reduce wear on the flash memory, but I'm not sure, since all
 * 14 sectors get written anyway.
 *
 * See SECTOR_ID_* constants in save.h
 */

#define SAVEBLOCK_CHUNK(structure, chunkNum)                                   \
{                                                                              \
    chunkNum * SECTOR_DATA_SIZE,                                               \
    sizeof(structure) >= chunkNum * SECTOR_DATA_SIZE ?                         \
    min(sizeof(structure) - chunkNum * SECTOR_DATA_SIZE, SECTOR_DATA_SIZE) : 0 \
}

struct
{
    u16 offset;
    u16 size;
} static const sSaveSlotLayout[NUM_SECTORS_PER_SLOT] =
{
    SAVEBLOCK_CHUNK(struct SaveBlock2, 0), // SECTOR_ID_SAVEBLOCK2

    SAVEBLOCK_CHUNK(struct SaveBlock1, 0), // SECTOR_ID_SAVEBLOCK1_START
    SAVEBLOCK_CHUNK(struct SaveBlock1, 1),
    SAVEBLOCK_CHUNK(struct SaveBlock1, 2),
    SAVEBLOCK_CHUNK(struct SaveBlock1, 3), // SECTOR_ID_SAVEBLOCK1_END

    SAVEBLOCK_CHUNK(struct PokemonStorage, 0), // SECTOR_ID_PKMN_STORAGE_START
    SAVEBLOCK_CHUNK(struct PokemonStorage, 1),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 2),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 3),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 4),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 5),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 6),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 7),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 8), // SECTOR_ID_PKMN_STORAGE_END
};

// These will produce an error if a save struct is larger than the space
// alloted for it in the flash.
STATIC_ASSERT(sizeof(struct SaveBlock3) <= SAVE_BLOCK_3_CHUNK_SIZE * NUM_SECTORS_PER_SLOT, SaveBlock3FreeSpace);
STATIC_ASSERT(sizeof(struct SaveBlock2) <= SECTOR_DATA_SIZE, SaveBlock2FreeSpace);
STATIC_ASSERT(sizeof(struct SaveBlock1) <= SECTOR_DATA_SIZE * (SECTOR_ID_SAVEBLOCK1_END - SECTOR_ID_SAVEBLOCK1_START + 1), SaveBlock1FreeSpace);
STATIC_ASSERT(offsetof(struct SaveBlock2, playerTrainerId) == 0xA, SaveBlock2TrainerIdOffset);
STATIC_ASSERT(offsetof(struct SaveBlock2, pokedex) == 0x20, SaveBlock2PokedexOffset);
STATIC_ASSERT(offsetof(struct SaveBlock2, encryptionKey) == 0xB4, SaveBlock2EncryptionKeyOffset);
STATIC_ASSERT(offsetof(struct SaveBlock2, playerApprentice) == 0xB8, SaveBlock2ApprenticeOffset);
STATIC_ASSERT(offsetof(struct SaveBlock2, contestLinkResults) == 0x254, SaveBlock2ContestResultsOffset);
STATIC_ASSERT(offsetof(struct SaveBlock2, frontier) == 0x27C, SaveBlock2FrontierOffset);
STATIC_ASSERT(sizeof(struct SaveBlock2) == 0xB30, SaveBlock2LegacySize);
STATIC_ASSERT(offsetof(struct SaveBlock3, dexNavChain) == 0xC, SaveBlock3DexNavChainOffset);
STATIC_ASSERT(offsetof(struct SaveBlock3, hiddenGrottoContents) == 0x10, SaveBlock3HiddenGrottoOffset);
STATIC_ASSERT(offsetof(struct SaveBlock3, candyJarExp) == 0x60, SaveBlock3CandyJarOffset);
STATIC_ASSERT(sizeof(struct SaveBlock3) == 0x64, SaveBlock3LegacySize);
STATIC_ASSERT(offsetof(struct SaveBlock1, registeredItemCompat) == 0x47E, SaveBlock1LegacyRegisteredItemOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, registeredItems) == 0x3484, SaveBlock1RegisteredItemsOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, optionsPartyMenuStyle) == 0x348C, SaveBlock1PartyMenuStyleOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, registeredShortcutsMagic) == 0x348E, SaveBlock1ShortcutMagicOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, registeredShortcutTypes) == 0x3492, SaveBlock1ShortcutTypesOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, futureReserved) == 0x349A, SaveBlock1FutureReserveOffset);
STATIC_ASSERT(sizeof(struct SaveBlock1) == 0x3C54, SaveBlock1LegacySize);

#define PKMN_STORAGE_REGULAR_SIZE (SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START + 1))
#define PKMN_STORAGE_OVERFLOW_SIZE (sizeof(struct PokemonStorage) - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_BX16_SIZE 37036
#define PKMN_STORAGE_BX16_OVERFLOW_SIZE (PKMN_STORAGE_BX16_SIZE - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_BX17_PAYLOAD_SIZE (sizeof(struct PokemonStorage) - offsetof(struct PokemonStorage, box17))
#define PKMN_STORAGE_BX17_OVERFLOW_OFFSET (offsetof(struct PokemonStorage, box17ExtensionMagic) - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_BX17_PAYLOAD_OVERFLOW_OFFSET (offsetof(struct PokemonStorage, box17) - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_EXTENSION_SECTOR_OFFSET (offsetof(struct PokemonStorage, boxExtensionMagic) - (SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START)))

STATIC_ASSERT(offsetof(struct PokemonStorage, boxExtensionMagic) == 34740, PokemonStorageLegacyLayout);
STATIC_ASSERT(PKMN_STORAGE_REGULAR_SIZE == 35712, PokemonStorageRegularSize);
STATIC_ASSERT(PKMN_STORAGE_BX16_OVERFLOW_SIZE == 1324, PokemonStorageBx16OverflowSize);
STATIC_ASSERT(PKMN_STORAGE_OVERFLOW_SIZE == 3624, PokemonStorageOverflowSize);
STATIC_ASSERT(SECTOR_DATA_SIZE - PKMN_STORAGE_OVERFLOW_SIZE == 344, PokemonStorageOverflowTrailingFreeSpace);
STATIC_ASSERT(PKMN_STORAGE_BX17_OVERFLOW_OFFSET == 1324, PokemonStorageBx17OverflowOffset);
STATIC_ASSERT(PKMN_STORAGE_BX17_PAYLOAD_OVERFLOW_OFFSET == 1332, PokemonStorageBx17PayloadOverflowOffset);
STATIC_ASSERT(PKMN_STORAGE_BX17_PAYLOAD_SIZE == 2292, PokemonStorageBx17PayloadSize);
STATIC_ASSERT(sizeof(struct PokemonStorage) > PKMN_STORAGE_REGULAR_SIZE, PokemonStorageUsesOverflow);
STATIC_ASSERT(PKMN_STORAGE_OVERFLOW_SIZE <= SECTOR_DATA_SIZE, PokemonStorageOverflowFreeSpace);
STATIC_ASSERT(PKMN_STORAGE_OVERFLOW_SIZE % sizeof(u32) == 0, PokemonStorageOverflowChecksumAlignment);
STATIC_ASSERT(PKMN_STORAGE_BX16_OVERFLOW_SIZE % sizeof(u32) == 0, PokemonStorageBx16OverflowChecksumAlignment);
STATIC_ASSERT(PKMN_STORAGE_BX17_PAYLOAD_SIZE % sizeof(u32) == 0, PokemonStorageBx17ChecksumAlignment);

COMMON_DATA u16 gLastWrittenSector = 0;
COMMON_DATA u32 gLastSaveCounter = 0;
COMMON_DATA u16 gLastKnownGoodSector = 0;
COMMON_DATA u32 gDamagedSaveSectors = 0;
COMMON_DATA u32 gSaveCounter = 0;
COMMON_DATA struct SaveSector *gReadWriteSector = NULL; // Pointer to a buffer for reading/writing a sector
COMMON_DATA u16 gIncrementalSectorId = 0;
COMMON_DATA u16 gSaveUnusedVar = 0;
COMMON_DATA u16 gSaveFileStatus = 0;
COMMON_DATA MainCallback gGameContinueCallback = NULL;
COMMON_DATA struct SaveSectorLocation gRamSaveSectorLocations[NUM_SECTORS_PER_SLOT] = {0};
COMMON_DATA u16 gSaveUnusedVar2 = 0;
COMMON_DATA u16 gSaveAttemptStatus = 0;

EWRAM_DATA struct SaveSector gSaveDataBuffer = {0}; // Buffer used for reading/writing sectors
EWRAM_DATA static bool8 sPokemonStorageOverflowWriteFailed = FALSE;

void ClearSaveData(void)
{
    u16 i;

    // Clear the full save two sectors at a time
    for (i = 0; i < SECTORS_COUNT / 2; i++)
    {
        EraseFlashSector(i);
        EraseFlashSector(i + SECTORS_COUNT / 2);
    }
}

void Save_ResetSaveCounters(void)
{
    gSaveCounter = 0;
    gLastWrittenSector = 0;
    gDamagedSaveSectors = 0;
}

static bool32 SetDamagedSectorBits(u8 op, u8 sectorId)
{
    bool32 retVal = FALSE;

    switch (op)
    {
    case ENABLE:
        gDamagedSaveSectors |= ((u32)1 << sectorId);
        break;
    case DISABLE:
        gDamagedSaveSectors &= ~((u32)1 << sectorId);
        break;
    case CHECK: // unused
        if (gDamagedSaveSectors & ((u32)1 << sectorId))
            retVal = TRUE;
        break;
    }

    return retVal;
}

static u8 WriteSaveSectorOrSlot(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u32 status;
    u16 i;

    gReadWriteSector = &gSaveDataBuffer;

    if (sectorId != FULL_SAVE_SLOT)
    {
        // A sector was specified, just write that sector.
        // This is never reached, FULL_SAVE_SLOT is always used instead.
        status = HandleWriteSector(sectorId, locations);
    }
    else
    {
        // No sector was specified, write full save slot.
        PreparePokemonStorageExtensions();
        gLastKnownGoodSector = gLastWrittenSector; // backup the current written sector before attempting to write.
        gLastSaveCounter = gSaveCounter;
        gLastWrittenSector++;
        gLastWrittenSector = gLastWrittenSector % NUM_SECTORS_PER_SLOT;
        gSaveCounter++;
        status = SAVE_STATUS_OK;

        // Write this first. The regular slot contains a marker which makes the
        // overflow sector mandatory for new saves, so an interrupted save will
        // fall back to the other complete slot.
        status = WritePokemonStorageOverflow();
        if (status == SAVE_STATUS_OK)
        {
            for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
                HandleWriteSector(i, locations);
        }

        if (gDamagedSaveSectors)
        {
            // At least one sector save failed
            status = SAVE_STATUS_ERROR;
            gLastWrittenSector = gLastKnownGoodSector;
            gSaveCounter = gLastSaveCounter;
        }
    }

    return status;
}

static u8 HandleWriteSector(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u16 i;
    u16 sector;
    u8 *data;
    u16 size;

    // Adjust sector id for current save slot
    sector = sectorId + gLastWrittenSector;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Get current save data
    data = locations[sectorId].data;
    size = locations[sectorId].size;

    // Clear temp save sector
    for (i = 0; i < SECTOR_SIZE; i++)
        ((u8 *)gReadWriteSector)[i] = 0;

    // Set footer data
    gReadWriteSector->id = sectorId;
    gReadWriteSector->signature = SECTOR_SIGNATURE;
    gReadWriteSector->counter = gSaveCounter;

    // Copy current data to temp buffer for writing
    for (i = 0; i < size; i++)
        gReadWriteSector->data[i] = data[i];

    CopyFromSaveBlock3(sectorId, gReadWriteSector);

    gReadWriteSector->checksum = CalculateChecksum(data, size);

    return TryWriteSector(sector, gReadWriteSector->data);
}

static u8 HandleWriteSectorNBytes(u8 sectorId, u8 *data, u16 size)
{
    u16 i;
    struct SaveSector *sector = &gSaveDataBuffer;

    // Clear temp save sector
    for (i = 0; i < SECTOR_SIZE; i++)
        ((u8 *)sector)[i] = 0;

    sector->signature = SECTOR_SIGNATURE;

    // Copy data to temp buffer for writing
    for (i = 0; i < size; i++)
        sector->data[i] = data[i];

    sector->id = CalculateChecksum(data, size); // though this appears to be incorrect, it might be some sector checksum instead of a whole save checksum and only appears to be relevent to HOF data, if used.
    return TryWriteSector(sectorId, sector->data);
}

static u8 TryWriteSector(u8 sector, u8 *data)
{
    if (ProgramFlashSectorAndVerify(sector, data)) // is damaged?
    {
        // Failed
        SetDamagedSectorBits(ENABLE, sector);
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

static u8 WritePokemonStorageOverflow(void)
{
    u16 i;
    u8 sectorId = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + (gSaveCounter % NUM_SAVE_SLOTS);
    u8 *src = (u8 *)gPokemonStoragePtr + PKMN_STORAGE_REGULAR_SIZE;

    for (i = 0; i < SECTOR_SIZE; i++)
        ((u8 *)gReadWriteSector)[i] = 0;

    for (i = 0; i < PKMN_STORAGE_OVERFLOW_SIZE; i++)
        gReadWriteSector->data[i] = src[i];

    gReadWriteSector->id = sectorId;
    // Keep this footer checksum limited to the historical BX16 prefix. An
    // older BX16 ROM can therefore still validate and load Boxes 1-16.
    gReadWriteSector->checksum = CalculateChecksum(src, PKMN_STORAGE_BX16_OVERFLOW_SIZE);
    gReadWriteSector->signature = SECTOR_SIGNATURE;
    gReadWriteSector->counter = gSaveCounter;

    return TryWriteSector(sectorId, gReadWriteSector->data);
}

static bool8 IsZeroed(const u8 *data, u16 size)
{
    u16 i;

    for (i = 0; i < size; i++)
    {
        if (data[i] != 0)
            return FALSE;
    }

    return TRUE;
}

static enum PokemonStorageOverflowStatus GetPokemonStorageOverflowStatus(u8 slotId, u32 counter)
{
    u8 sectorId = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + slotId;
    u8 *data;
    u16 checksum;

    ReadFlashSector(sectorId, gReadWriteSector);
    data = gReadWriteSector->data;
    if (gReadWriteSector->id != sectorId
     || gReadWriteSector->checksum != CalculateChecksum(data, PKMN_STORAGE_BX16_OVERFLOW_SIZE)
     || gReadWriteSector->signature != SECTOR_SIGNATURE
     || gReadWriteSector->counter != counter)
        return PKMN_STORAGE_OVERFLOW_INVALID;

    // BX16 ROMs zeroed the whole sector before writing their 1,324-byte
    // overflow. Anything nonzero beyond that prefix must be a valid BX17 tail.
    if (IsZeroed(&data[PKMN_STORAGE_BX17_OVERFLOW_OFFSET],
                 SECTOR_DATA_SIZE - PKMN_STORAGE_BX17_OVERFLOW_OFFSET))
        return PKMN_STORAGE_OVERFLOW_BX16;

    if (!IsZeroed(&data[PKMN_STORAGE_OVERFLOW_SIZE],
                  SECTOR_DATA_SIZE - PKMN_STORAGE_OVERFLOW_SIZE))
        return PKMN_STORAGE_OVERFLOW_INVALID;
    if (*(u32 *)&data[PKMN_STORAGE_BX17_OVERFLOW_OFFSET] != POKEMON_STORAGE_BOX17_MAGIC)
        return PKMN_STORAGE_OVERFLOW_INVALID;

    checksum = *(u16 *)&data[PKMN_STORAGE_BX17_OVERFLOW_OFFSET + sizeof(u32)];
    if (*(u16 *)&data[PKMN_STORAGE_BX17_OVERFLOW_OFFSET + sizeof(u32) + sizeof(u16)] != (u16)~checksum
     || checksum != CalculateChecksum(&data[PKMN_STORAGE_BX17_PAYLOAD_OVERFLOW_OFFSET], PKMN_STORAGE_BX17_PAYLOAD_SIZE))
        return PKMN_STORAGE_OVERFLOW_INVALID;

    return PKMN_STORAGE_OVERFLOW_BX17;
}

static bool8 IsPokemonStorageOverflowValid(u8 slotId, u32 counter)
{
    return GetPokemonStorageOverflowStatus(slotId, counter) != PKMN_STORAGE_OVERFLOW_INVALID;
}

static void LoadPokemonStorageOverflow(void)
{
    u8 *dst;
    enum PokemonStorageOverflowStatus status;

    if (gPokemonStoragePtr->boxExtensionMagic != POKEMON_STORAGE_EXTENSION_MAGIC)
    {
        InitPokemonStorageExtension();
        return;
    }

    status = GetPokemonStorageOverflowStatus(gSaveCounter % NUM_SAVE_SLOTS, gSaveCounter);
    if (status == PKMN_STORAGE_OVERFLOW_INVALID)
        return;

    dst = (u8 *)gPokemonStoragePtr + PKMN_STORAGE_REGULAR_SIZE;
    if (status == PKMN_STORAGE_OVERFLOW_BX16)
    {
        memcpy(dst, gReadWriteSector->data, PKMN_STORAGE_BX16_OVERFLOW_SIZE);
        InitPokemonStorageBox17Extension();
    }
    else
    {
        memcpy(dst, gReadWriteSector->data, PKMN_STORAGE_OVERFLOW_SIZE);
    }
}

static void PreparePokemonStorageExtensions(void)
{
    gPokemonStoragePtr->boxExtensionMagic = POKEMON_STORAGE_EXTENSION_MAGIC;
    gPokemonStoragePtr->box17ExtensionMagic = POKEMON_STORAGE_BOX17_MAGIC;
    gPokemonStoragePtr->box17Checksum = CalculateChecksum(
        &gPokemonStoragePtr->box17,
        PKMN_STORAGE_BX17_PAYLOAD_SIZE);
    gPokemonStoragePtr->box17ChecksumInverse = (u16)~gPokemonStoragePtr->box17Checksum;
}

static u32 RestoreSaveBackupVarsAndIncrement(const struct SaveSectorLocation *locations)
{
    gReadWriteSector = &gSaveDataBuffer;
    gLastKnownGoodSector = gLastWrittenSector;
    gLastSaveCounter = gSaveCounter;
    gLastWrittenSector++;
    gLastWrittenSector %= NUM_SECTORS_PER_SLOT;
    gSaveCounter++;
    gIncrementalSectorId = 0;
    gDamagedSaveSectors = 0;
    return 0;
}

static u32 RestoreSaveBackupVars(const struct SaveSectorLocation *locations)
{
    gReadWriteSector = &gSaveDataBuffer;
    gLastKnownGoodSector = gLastWrittenSector;
    gLastSaveCounter = gSaveCounter;
    gIncrementalSectorId = 0;
    gDamagedSaveSectors = 0;
    return 0;
}

static u8 HandleWriteIncrementalSector(u16 numSectors, const struct SaveSectorLocation *locations)
{
    u8 status;

    if (gIncrementalSectorId < numSectors - 1)
    {
        status = SAVE_STATUS_OK;
        HandleWriteSector(gIncrementalSectorId, locations);
        gIncrementalSectorId++;
        if (gDamagedSaveSectors)
        {
            status = SAVE_STATUS_ERROR;
            gLastWrittenSector = gLastKnownGoodSector;
            gSaveCounter = gLastSaveCounter;
        }
    }
    else
    {
        // Exceeded max sector, finished
        status = SAVE_STATUS_ERROR;
    }

    return status;
}

static u8 HandleReplaceSectorAndVerify(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u8 status = SAVE_STATUS_OK;

    HandleReplaceSector(sectorId - 1, locations);

    if (gDamagedSaveSectors)
    {
        status = SAVE_STATUS_ERROR;
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
    }
    return status;
}

// Similar to HandleWriteSector, but fully erases the sector first, and skips writing the first signature byte
static u8 HandleReplaceSector(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u16 i;
    u16 sector;
    u8 *data;
    u16 size;
    u8 status;

    // Adjust sector id for current save slot
    sector = sectorId + gLastWrittenSector;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Get current save data
    data = locations[sectorId].data;
    size = locations[sectorId].size;

    // Clear temp save sector.
    for (i = 0; i < SECTOR_SIZE; i++)
        ((u8 *)gReadWriteSector)[i] = 0;

    // Set footer data
    gReadWriteSector->id = sectorId;
    gReadWriteSector->signature = SECTOR_SIGNATURE;
    gReadWriteSector->counter = gSaveCounter;

    // Copy current data to temp buffer for writing
    for (i = 0; i < size; i++)
        gReadWriteSector->data[i] = data[i];

    CopyFromSaveBlock3(sectorId, gReadWriteSector);

    gReadWriteSector->checksum = CalculateChecksum(data, size);

    // Erase old save data
    EraseFlashSector(sector);

    status = SAVE_STATUS_OK;

    // Write new save data up to signature field
    for (i = 0; i < SECTOR_SIGNATURE_OFFSET; i++)
    {
        if (ProgramFlashByte(sector, i, ((u8 *)gReadWriteSector)[i]))
        {
            status = SAVE_STATUS_ERROR;
            break;
        }
    }

    if (status == SAVE_STATUS_ERROR)
    {
        // Writing save data failed
        SetDamagedSectorBits(ENABLE, sector);
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Writing save data succeeded, write signature and counter
        status = SAVE_STATUS_OK;

        // Write signature (skipping the first byte) and counter fields.
        // The byte of signature that is skipped is instead written by WriteSectorSignatureByte or WriteSectorSignatureByte_NoOffset
        for (i = 0; i < SECTOR_SIZE - (SECTOR_SIGNATURE_OFFSET + 1); i++)
        {
            if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET + 1 + i, ((u8 *)gReadWriteSector)[SECTOR_SIGNATURE_OFFSET + 1 + i]))
            {
                status = SAVE_STATUS_ERROR;
                break;
            }
        }

        if (status == SAVE_STATUS_ERROR)
        {
            // Writing signature/counter failed
            SetDamagedSectorBits(ENABLE, sector);
            return SAVE_STATUS_ERROR;
        }
        else
        {
            // Succeeded
            SetDamagedSectorBits(DISABLE, sector);
            return SAVE_STATUS_OK;
        }
    }
}

static u8 WriteSectorSignatureByte_NoOffset(u16 sectorId, const struct SaveSectorLocation *locations)
{
    // Adjust sector id for current save slot
    // This first line lacking -1 is the only difference from WriteSectorSignatureByte
    u16 sector = sectorId + gLastWrittenSector;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Write just the first byte of the signature field, which was skipped by HandleReplaceSector
    if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET, SECTOR_SIGNATURE & 0xFF))
    {
        // Sector is damaged, so enable the bit in gDamagedSaveSectors and restore the last written sector and save counter.
        SetDamagedSectorBits(ENABLE, sector);
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

static u8 CopySectorSignatureByte(u16 sectorId, const struct SaveSectorLocation *locations)
{
    // Adjust sector id for current save slot
    u16 sector = sectorId + gLastWrittenSector - 1;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Copy just the first byte of the signature field from the read/write buffer
    if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET, ((u8 *)gReadWriteSector)[SECTOR_SIGNATURE_OFFSET]))
    {
        // Sector is damaged, so enable the bit in gDamagedSaveSectors and restore the last written sector and save counter.
        SetDamagedSectorBits(ENABLE, sector);
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

static u8 WriteSectorSignatureByte(u16 sectorId, const struct SaveSectorLocation *locations)
{
    // Adjust sector id for current save slot
    u16 sector = sectorId + gLastWrittenSector - 1;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Write just the first byte of the signature field, which was skipped by HandleReplaceSector
    if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET, SECTOR_SIGNATURE & 0xFF))
    {
        // Sector is damaged, so enable the bit in gDamagedSaveSectors and restore the last written sector and save counter.
        SetDamagedSectorBits(ENABLE, sector);
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

static u8 TryLoadSaveSlot(u16 sectorId, struct SaveSectorLocation *locations)
{
    u8 status;
    gReadWriteSector = &gSaveDataBuffer;
    if (sectorId != FULL_SAVE_SLOT)
    {
        // This function may not be used with a specific sector id
        status = SAVE_STATUS_ERROR;
    }
    else
    {
        status = GetSaveValidStatus(locations);
        CopySaveSlotData(FULL_SAVE_SLOT, locations);
        LoadPokemonStorageOverflow();
    }

    return status;
}

// sectorId arg is ignored, this always reads the full save slot
static u8 CopySaveSlotData(u16 sectorId, struct SaveSectorLocation *locations)
{
    u16 i;
    u16 checksum;
    u16 slotOffset = NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);
    u16 id;

    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i + slotOffset, gReadWriteSector);

        id = gReadWriteSector->id;
        if (id == 0)
            gLastWrittenSector = i;

        // Only copy data for sectors whose id, signature, and checksum fields are correct.
        if (id < NUM_SECTORS_PER_SLOT)
        {
            checksum = CalculateChecksum(gReadWriteSector->data, locations[id].size);
            if (gReadWriteSector->signature == SECTOR_SIGNATURE && gReadWriteSector->checksum == checksum)
            {
                u16 j;
                for (j = 0; j < locations[id].size; j++)
                    ((u8 *)locations[id].data)[j] = gReadWriteSector->data[j];
                CopyToSaveBlock3(id, gReadWriteSector);
            }
        }
    }

    return SAVE_STATUS_OK;
}

static u8 GetSaveValidStatus(const struct SaveSectorLocation *locations)
{
    u16 i;
    u16 checksum;
    u32 saveSlot1Counter = 0;
    u32 saveSlot2Counter = 0;
    u32 validSectorFlags = 0;
    bool8 signatureValid = FALSE;
    bool8 saveSlot1UsesStorageOverflow = FALSE;
    bool8 saveSlot2UsesStorageOverflow = FALSE;
    u8 saveSlot1Status;
    u8 saveSlot2Status;

    // Check save slot 1
    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i, gReadWriteSector);
        if (gReadWriteSector->signature == SECTOR_SIGNATURE)
        {
            signatureValid = TRUE;
            if (gReadWriteSector->id < NUM_SECTORS_PER_SLOT)
            {
                checksum = CalculateChecksum(gReadWriteSector->data, locations[gReadWriteSector->id].size);
                if (gReadWriteSector->checksum == checksum)
                {
                    saveSlot1Counter = gReadWriteSector->counter;
                    validSectorFlags |= 1 << gReadWriteSector->id;
                    if (gReadWriteSector->id == SECTOR_ID_PKMN_STORAGE_END
                     && *(u32 *)&gReadWriteSector->data[PKMN_STORAGE_EXTENSION_SECTOR_OFFSET] == POKEMON_STORAGE_EXTENSION_MAGIC)
                        saveSlot1UsesStorageOverflow = TRUE;
                }
            }
        }
    }

    if (signatureValid)
    {
        if (validSectorFlags == (1 << NUM_SECTORS_PER_SLOT) - 1
         && (!saveSlot1UsesStorageOverflow || IsPokemonStorageOverflowValid(0, saveSlot1Counter)))
            saveSlot1Status = SAVE_STATUS_OK;
        else
            saveSlot1Status = SAVE_STATUS_ERROR;
    }
    else
    {
        // No sectors in slot 1 have the correct signature, treat it as empty
        saveSlot1Status = SAVE_STATUS_EMPTY;
    }

    validSectorFlags = 0;
    signatureValid = FALSE;

    // Check save slot 2
    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i + NUM_SECTORS_PER_SLOT, gReadWriteSector);
        if (gReadWriteSector->signature == SECTOR_SIGNATURE)
        {
            signatureValid = TRUE;
            if (gReadWriteSector->id < NUM_SECTORS_PER_SLOT)
            {
                checksum = CalculateChecksum(gReadWriteSector->data, locations[gReadWriteSector->id].size);
                if (gReadWriteSector->checksum == checksum)
                {
                    saveSlot2Counter = gReadWriteSector->counter;
                    validSectorFlags |= 1 << gReadWriteSector->id;
                    if (gReadWriteSector->id == SECTOR_ID_PKMN_STORAGE_END
                     && *(u32 *)&gReadWriteSector->data[PKMN_STORAGE_EXTENSION_SECTOR_OFFSET] == POKEMON_STORAGE_EXTENSION_MAGIC)
                        saveSlot2UsesStorageOverflow = TRUE;
                }
            }
        }
    }

    if (signatureValid)
    {
        if (validSectorFlags == (1 << NUM_SECTORS_PER_SLOT) - 1
         && (!saveSlot2UsesStorageOverflow || IsPokemonStorageOverflowValid(1, saveSlot2Counter)))
            saveSlot2Status = SAVE_STATUS_OK;
        else
            saveSlot2Status = SAVE_STATUS_ERROR;
    }
    else
    {
        // No sectors in slot 2 have the correct signature, treat it as empty.
        saveSlot2Status = SAVE_STATUS_EMPTY;
    }

    if (saveSlot1Status == SAVE_STATUS_OK && saveSlot2Status == SAVE_STATUS_OK)
    {
        if ((saveSlot1Counter == -1 && saveSlot2Counter ==  0)
         || (saveSlot1Counter ==  0 && saveSlot2Counter == -1))
        {
            if ((unsigned)(saveSlot1Counter + 1) < (unsigned)(saveSlot2Counter + 1))
                gSaveCounter = saveSlot2Counter;
            else
                gSaveCounter = saveSlot1Counter;
        }
        else
        {
            if (saveSlot1Counter < saveSlot2Counter)
                gSaveCounter = saveSlot2Counter;
            else
                gSaveCounter = saveSlot1Counter;
        }
        return SAVE_STATUS_OK;
    }

    // One or both save slots are not OK

    if (saveSlot1Status == SAVE_STATUS_OK)
    {
        gSaveCounter = saveSlot1Counter;
        if (saveSlot2Status == SAVE_STATUS_ERROR)
            return SAVE_STATUS_ERROR; // Slot 2 errored
        return SAVE_STATUS_OK; // Slot 1 is OK, slot 2 is empty
    }

    if (saveSlot2Status == SAVE_STATUS_OK)
    {
        gSaveCounter = saveSlot2Counter;
        if (saveSlot1Status == SAVE_STATUS_ERROR)
            return SAVE_STATUS_ERROR; // Slot 1 errored
        return SAVE_STATUS_OK; // Slot 2 is OK, slot 1 is empty
    }

    // Neither slot is OK, check if both are empty
    if (saveSlot1Status == SAVE_STATUS_EMPTY
     && saveSlot2Status == SAVE_STATUS_EMPTY)
    {
        gSaveCounter = 0;
        gLastWrittenSector = 0;
        return SAVE_STATUS_EMPTY;
    }

    // Both slots errored
    gSaveCounter = 0;
    gLastWrittenSector = 0;
    return SAVE_STATUS_CORRUPT;
}

static u8 TryLoadSaveSector(u8 sectorId, u8 *data, u16 size)
{
    u16 i;
    struct SaveSector *sector = &gSaveDataBuffer;
    ReadFlashSector(sectorId, sector);
    if (sector->signature == SECTOR_SIGNATURE)
    {
        u16 checksum = CalculateChecksum(sector->data, size);
        if (sector->id == checksum)
        {
            // Signature and checksum are correct, copy data
            for (i = 0; i < size; i++)
                data[i] = sector->data[i];
            return SAVE_STATUS_OK;
        }
        else
        {
            // Incorrect checksum
            return SAVE_STATUS_CORRUPT;
        }
    }
    else
    {
        // Incorrect signature value
        return SAVE_STATUS_EMPTY;
    }
}

// Return value always ignored
static bool8 ReadFlashSector(u8 sectorId, struct SaveSector *sector)
{
    ReadFlash(sectorId, 0, sector->data, SECTOR_SIZE);
    return TRUE;
}

static u16 CalculateChecksum(void *data, u16 size)
{
    u16 i;
    u32 checksum = 0;

    for (i = 0; i < (size / 4); i++)
    {
        checksum += *((u32 *)data);
        data += sizeof(u32);
    }

    return ((checksum >> 16) + checksum);
}

static void UpdateSaveAddresses(void)
{
    int i = SECTOR_ID_SAVEBLOCK2;
    gRamSaveSectorLocations[i].data = (void *)(gSaveBlock2Ptr) + sSaveSlotLayout[i].offset;
    gRamSaveSectorLocations[i].size = sSaveSlotLayout[i].size;

    for (i = SECTOR_ID_SAVEBLOCK1_START; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
    {
        gRamSaveSectorLocations[i].data = (void *)(gSaveBlock1Ptr) + sSaveSlotLayout[i].offset;
        gRamSaveSectorLocations[i].size = sSaveSlotLayout[i].size;
    }

    for (; i <= SECTOR_ID_PKMN_STORAGE_END; i++) //setting i to SECTOR_ID_PKMN_STORAGE_START does not match
    {
        gRamSaveSectorLocations[i].data = (void *)(gPokemonStoragePtr) + sSaveSlotLayout[i].offset;
        gRamSaveSectorLocations[i].size = sSaveSlotLayout[i].size;
    }
}

u8 HandleSavingData(u8 saveType)
{
    u8 i;
    u32 *backupVar = gTrainerHillVBlankCounter;

    gTrainerHillVBlankCounter = NULL;
    UpdateSaveAddresses();
    switch (saveType)
    {
    case SAVE_HALL_OF_FAME_ERASE_BEFORE:
        // Unused. Erases the Hall of Fame before saving.
        for (i = SECTOR_ID_HOF_1; i < SECTOR_ID_PKMN_STORAGE_OVERFLOW_1; i++)
            EraseFlashSector(i);
        // fallthrough
    case SAVE_HALL_OF_FAME:
        if (GetGameStat(GAME_STAT_ENTERED_HOF) < 999)
            IncrementGameStat(GAME_STAT_ENTERED_HOF);

        // Write the full save slot first
        CopyPartyAndObjectsToSave();
        WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);

        // Save the Hall of Fame
        if (gHoFSaveBuffer != NULL)
        {
            u8 *tempAddr = (void *) gHoFSaveBuffer;
            HandleWriteSectorNBytes(SECTOR_ID_HOF_1, tempAddr, SECTOR_DATA_SIZE);
            HandleWriteSectorNBytes(SECTOR_ID_HOF_2, tempAddr + SECTOR_DATA_SIZE, SECTOR_DATA_SIZE);
        }
        break;
    case SAVE_NORMAL:
    default:
        CopyPartyAndObjectsToSave();
        WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);
        break;
    case SAVE_LINK:
    case SAVE_EREADER: // Dummied, now duplicate of SAVE_LINK
        // Used by link / Battle Frontier
        // Write only SaveBlocks 1 and 2 (skips the PC)
        CopyPartyAndObjectsToSave();
        for (i = SECTOR_ID_SAVEBLOCK2; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
            HandleReplaceSector(i, gRamSaveSectorLocations);
        for (i = SECTOR_ID_SAVEBLOCK2; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
            WriteSectorSignatureByte_NoOffset(i, gRamSaveSectorLocations);
        break;
    case SAVE_OVERWRITE_DIFFERENT_FILE:
        // Erase Hall of Fame
        for (i = SECTOR_ID_HOF_1; i < SECTOR_ID_PKMN_STORAGE_OVERFLOW_1; i++)
            EraseFlashSector(i);

        // Overwrite save slot
        CopyPartyAndObjectsToSave();
        WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);
        break;
    }
    gTrainerHillVBlankCounter = backupVar;
    return 0;
}

u8 TrySavingData(u8 saveType)
{
    if (gFlashMemoryPresent != TRUE)
    {
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        return SAVE_STATUS_ERROR;
    }

    HandleSavingData(saveType);
    if (!gDamagedSaveSectors)
    {
        gSaveAttemptStatus = SAVE_STATUS_OK;
        return SAVE_STATUS_OK;
    }
    else
    {
        DoSaveFailedScreen(saveType);
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        return SAVE_STATUS_ERROR;
    }
}

bool8 LinkFullSave_Init(void)
{
    sPokemonStorageOverflowWriteFailed = FALSE;
    if (gFlashMemoryPresent != TRUE)
        return TRUE;
    UpdateSaveAddresses();
    CopyPartyAndObjectsToSave();
    PreparePokemonStorageExtensions();
    RestoreSaveBackupVarsAndIncrement(gRamSaveSectorLocations);
    if (WritePokemonStorageOverflow() != SAVE_STATUS_OK)
    {
        sPokemonStorageOverflowWriteFailed = TRUE;
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        DoSaveFailedScreen(SAVE_NORMAL);
        return TRUE;
    }
    return FALSE;
}

bool8 LinkFullSave_WriteSector(void)
{
    u8 status;

    if (sPokemonStorageOverflowWriteFailed)
        return TRUE;

    status = HandleWriteIncrementalSector(NUM_SECTORS_PER_SLOT, gRamSaveSectorLocations);
    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_NORMAL);

    // In this case "error" either means that an actual error was encountered
    // or that the given max sector has been reached (meaning it has finished successfully).
    // If there was an actual error the save failed screen above will also be shown.
    if (status == SAVE_STATUS_ERROR)
        return TRUE;
    else
        return FALSE;
}

bool8 LinkFullSave_ReplaceLastSector(void)
{
    if (sPokemonStorageOverflowWriteFailed)
        return FALSE;

    HandleReplaceSectorAndVerify(NUM_SECTORS_PER_SLOT, gRamSaveSectorLocations);
    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_NORMAL);
    return FALSE;
}

bool8 LinkFullSave_SetLastSectorSignature(void)
{
    if (sPokemonStorageOverflowWriteFailed)
        return FALSE;

    CopySectorSignatureByte(NUM_SECTORS_PER_SLOT, gRamSaveSectorLocations);
    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_NORMAL);
    return FALSE;
}

bool8 WriteSaveBlock2(void)
{
    if (gFlashMemoryPresent != TRUE)
        return TRUE;

    UpdateSaveAddresses();
    CopyPartyAndObjectsToSave();
    RestoreSaveBackupVars(gRamSaveSectorLocations);

    // Because RestoreSaveBackupVars is called immediately prior, gIncrementalSectorId will always be 0 below,
    // so this function only saves the first sector (SECTOR_ID_SAVEBLOCK2)
    HandleReplaceSectorAndVerify(gIncrementalSectorId + 1, gRamSaveSectorLocations);
    return FALSE;
}

// Used in conjunction with WriteSaveBlock2 to write both for certain link saves.
// This will be called repeatedly in a task, writing each sector of SaveBlock1 incrementally.
// It returns TRUE when finished.
bool8 WriteSaveBlock1Sector(void)
{
    bool32 finished = FALSE;
    u16 sectorId = ++gIncrementalSectorId; // Because WriteSaveBlock2 will have been called prior, this will be SECTOR_ID_SAVEBLOCK1_START
    if (sectorId <= SECTOR_ID_SAVEBLOCK1_END)
    {
        // Write a single sector of SaveBlock1
        HandleReplaceSectorAndVerify(gIncrementalSectorId + 1, gRamSaveSectorLocations);
        WriteSectorSignatureByte(sectorId, gRamSaveSectorLocations);
    }
    else
    {
        // Beyond SaveBlock1, don't write the sector.
        // Does write 1 byte of the next sector's signature field, but as these
        // are the same for all valid sectors it doesn't matter.
        WriteSectorSignatureByte(sectorId, gRamSaveSectorLocations);
        finished = TRUE;
    }

    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_LINK);

    return finished;
}

u8 LoadGameSave(u8 saveType)
{
    u8 status;

    if (gFlashMemoryPresent != TRUE)
    {
        gSaveFileStatus = SAVE_STATUS_NO_FLASH;
        return SAVE_STATUS_ERROR;
    }

    UpdateSaveAddresses();
    switch (saveType)
    {
    case SAVE_NORMAL:
    default:
        status = TryLoadSaveSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);
        CopyPartyAndObjectsFromSave();
        gSaveFileStatus = status;
        gGameContinueCallback = NULL;
        break;
    case SAVE_HALL_OF_FAME:
        if (gHoFSaveBuffer != NULL)
        {
            u8 *hofData = (u8 *) gHoFSaveBuffer;
            status = TryLoadSaveSector(SECTOR_ID_HOF_1, hofData, SECTOR_DATA_SIZE);
            if (status == SAVE_STATUS_OK)
                status = TryLoadSaveSector(SECTOR_ID_HOF_2, &hofData[SECTOR_DATA_SIZE], SECTOR_DATA_SIZE);
        }
        else
        {
            status = SAVE_STATUS_ERROR;
        }
        break;
    }

    return status;
}

u16 GetSaveBlocksPointersBaseOffset(void)
{
    u16 i, slotOffset;
    struct SaveSector *sector;

    sector = gReadWriteSector = &gSaveDataBuffer;
    if (gFlashMemoryPresent != TRUE)
        return 0;
    UpdateSaveAddresses();
    GetSaveValidStatus(gRamSaveSectorLocations);
    slotOffset = NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);
    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i + slotOffset, gReadWriteSector);

        // Base offset for SaveBlock2 is calculated using the trainer id
        if (gReadWriteSector->id == SECTOR_ID_SAVEBLOCK2)
            return sector->data[offsetof(struct SaveBlock2, playerTrainerId[0])] +
                   sector->data[offsetof(struct SaveBlock2, playerTrainerId[1])] +
                   sector->data[offsetof(struct SaveBlock2, playerTrainerId[2])] +
                   sector->data[offsetof(struct SaveBlock2, playerTrainerId[3])];
    }
    return 0;
}

#define tState         data[0]
#define tTimer         data[1]
#define tInBattleTower data[2]

// Note that this is very different from TrySavingData(SAVE_LINK).
// Most notably it does save the PC data.
void Task_LinkFullSave(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        gSoftResetDisabled = TRUE;
        tState = 1;
        break;
    case 1:
        SetLinkStandbyCallback();
        tState = 2;
        break;
    case 2:
        if (IsLinkTaskFinished())
        {
            if (!tInBattleTower)
                SaveMapView();
            tState = 3;
        }
        break;
    case 3:
        if (!tInBattleTower)
            SetContinueGameWarpStatusToDynamicWarp();
        LinkFullSave_Init();
        tState = 4;
        break;
    case 4:
        if (++tTimer == 5)
        {
            tTimer = 0;
            tState = 5;
        }
        break;
    case 5:
        if (LinkFullSave_WriteSector())
            tState = 6;
        else
            tState = 4; // Not finished, delay again
        break;
    case 6:
        LinkFullSave_ReplaceLastSector();
        tState = 7;
        break;
    case 7:
        if (!tInBattleTower)
            ClearContinueGameWarpStatus2();
        SetLinkStandbyCallback();
        tState = 8;
        break;
    case 8:
        if (IsLinkTaskFinished())
        {
            LinkFullSave_SetLastSectorSignature();
            tState = 9;
        }
        break;
    case 9:
        SetLinkStandbyCallback();
        tState = 10;
        break;
    case 10:
        if (IsLinkTaskFinished())
            tState++;
        break;
    case 11:
        if (++tTimer > 5)
        {
            gSoftResetDisabled = FALSE;
            DestroyTask(taskId);
        }
        break;
    }
}

static u32 SaveBlock3Size(u32 sectorId)
{
    s32 begin = sectorId * SAVE_BLOCK_3_CHUNK_SIZE;
    s32 end = (sectorId + 1) * SAVE_BLOCK_3_CHUNK_SIZE;
    return max(0, min(end, (s32)sizeof(gSaveblock3)) - begin);
}

static void CopyToSaveBlock3(u32 sectorId, struct SaveSector *sector)
{
    u32 size = SaveBlock3Size(sectorId);
    memcpy((u8 *)&gSaveblock3 + (sectorId * SAVE_BLOCK_3_CHUNK_SIZE), sector->saveBlock3Chunk, size);
}

static void CopyFromSaveBlock3(u32 sectorId, struct SaveSector *sector)
{
    u32 size = SaveBlock3Size(sectorId);
    memcpy(sector->saveBlock3Chunk, (u8 *)&gSaveblock3 + (sectorId * SAVE_BLOCK_3_CHUNK_SIZE), size);
}
