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
#include "malloc.h"
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
static bool8 PreparePokemonStorageExtensions(bool8);
static void FinishPokemonStorageExtensions(bool8);
static bool8 CopyPokemonStorageExtensionTailToSaveSector(u16);
static u8 WritePokemonStorageOverflow(void);
static u8 WriteBx19AuxiliarySector(void);
static bool8 IsBx19AuxiliarySectorValid(u8, u32);
static void LoadPokemonStorageOverflow(void);
static u8 LoadLegacyHallOfFameArchive(struct HallOfFameArchive *);
static u8 LoadLegacyHallOfFameTeams(struct HallofFameTeam *, u8 *);
static void ClearLegacyHallOfFameRetryArchive(void);

enum PokemonStorageOverflowStatus
{
    PKMN_STORAGE_OVERFLOW_INVALID,
    PKMN_STORAGE_OVERFLOW_BX16,
    PKMN_STORAGE_OVERFLOW_BX17,
    PKMN_STORAGE_OVERFLOW_BX18,
    PKMN_STORAGE_OVERFLOW_BX19,
};

enum LegacyHallOfFameLoadStatus
{
    LEGACY_HOF_ARCHIVE_UNAVAILABLE,
    LEGACY_HOF_ARCHIVE_VALID,
};

// Divide save blocks into individual chunks to be written to flash sectors

/*
 * Sector Layout:
 *
 * Sectors 0 - 13:      Save Slot 1
 * Sectors 14 - 27:     Save Slot 2
 * Sector 28:           Box 19 / Hall of Fame auxiliary for Save Slot 1
 * Sector 29:           Box 19 / Hall of Fame auxiliary for Save Slot 2
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
STATIC_ASSERT(offsetof(struct SaveBlock1, pokemonStorageExtensionTail) == 0x349A, SaveBlock1PokemonStorageExtensionTailOffset);
STATIC_ASSERT(sizeof(((struct SaveBlock1 *)0)->pokemonStorageExtensionTail) == 1944, SaveBlock1PokemonStorageExtensionTailSize);
STATIC_ASSERT(offsetof(struct SaveBlock1, futureReserved) == 0x3C32, SaveBlock1FutureReserveOffset);
STATIC_ASSERT(sizeof(((struct SaveBlock1 *)0)->futureReserved) == 34, SaveBlock1FutureReserveSize);
STATIC_ASSERT(sizeof(struct SaveBlock1) == 0x3C54, SaveBlock1LegacySize);

#define PKMN_STORAGE_REGULAR_SIZE (SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START + 1))
#define PKMN_STORAGE_LEGACY_SIZE 34740
#define PKMN_STORAGE_BX16_SIZE 37036
#define PKMN_STORAGE_BX17_SIZE 39336
#define PKMN_STORAGE_BX18_SIZE 41624
#define PKMN_STORAGE_BX16_OVERFLOW_SIZE (PKMN_STORAGE_BX16_SIZE - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_BX17_OVERFLOW_SIZE (PKMN_STORAGE_BX17_SIZE - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_BX17_PAYLOAD_SIZE (PKMN_STORAGE_BX17_SIZE - offsetof(struct PokemonStorage, extensionBoxes))
#define PKMN_STORAGE_BX18_EXTENSION_SIZE (PKMN_STORAGE_BX18_SIZE - offsetof(struct PokemonStorage, box18ExtensionMagic))
#define PKMN_STORAGE_BX18_PAYLOAD_SIZE (PKMN_STORAGE_BX18_SIZE - offsetof(struct PokemonStorage, extensionBoxes))
#define PKMN_STORAGE_BX18_OVERFLOW_OFFSET (offsetof(struct PokemonStorage, box18ExtensionMagic) - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET (offsetof(struct PokemonStorage, extensionBoxes) - PKMN_STORAGE_REGULAR_SIZE)
#define PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_SIZE (SECTOR_DATA_SIZE - PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET)
#define PKMN_STORAGE_EXTENSION_TAIL_OFFSET (PKMN_STORAGE_REGULAR_SIZE + SECTOR_DATA_SIZE)
#define PKMN_STORAGE_BX18_TAIL_SIZE (PKMN_STORAGE_BX18_SIZE - PKMN_STORAGE_EXTENSION_TAIL_OFFSET)
#define PKMN_STORAGE_BOX19_RECORD_SIZE (sizeof(struct PokemonStorage) - offsetof(struct PokemonStorage, box19))
#define SAVEBLOCK1_EXTENSION_TAIL_SECTOR_OFFSET (offsetof(struct SaveBlock1, pokemonStorageExtensionTail) - 3 * SECTOR_DATA_SIZE)
#define PKMN_STORAGE_EXTENSION_SECTOR_OFFSET (offsetof(struct PokemonStorage, boxExtensionMagic) - (SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START)))

#define BX19_SCHEMA_VERSION 1

struct Bx19AuxiliaryRecord
{
    u32 magic;
    u16 version;
    u16 payloadLength;
    u16 checksum;
    u16 checksumInverse;
    struct BoxPokemon box19[IN_BOX_COUNT];
    u8 box19Name[BOX_NAME_LENGTH + 1];
    u8 box19Wallpaper;
    u8 box19Padding[2];
    struct HallOfFameArchive hallOfFame;
};

STATIC_ASSERT(offsetof(struct PokemonStorage, boxExtensionMagic) == 34740, PokemonStorageLegacyLayout);
STATIC_ASSERT(SECTOR_DATA_SIZE == 3968, PokemonStorageFlashOverflowSize);
STATIC_ASSERT(PKMN_STORAGE_REGULAR_SIZE == 35712, PokemonStorageRegularSize);
STATIC_ASSERT(PKMN_STORAGE_LEGACY_SIZE == 34740, PokemonStorageLegacyFrozenSize);
STATIC_ASSERT(PKMN_STORAGE_BX16_SIZE == 37036, PokemonStorageBx16FrozenSize);
STATIC_ASSERT(PKMN_STORAGE_BX17_SIZE == 39336, PokemonStorageBx17FrozenSize);
STATIC_ASSERT(PKMN_STORAGE_BX18_SIZE == 41624, PokemonStorageBx18FrozenSize);
STATIC_ASSERT(PKMN_STORAGE_BX16_OVERFLOW_SIZE == 1324, PokemonStorageBx16OverflowSize);
STATIC_ASSERT(PKMN_STORAGE_BX17_OVERFLOW_SIZE == 3624, PokemonStorageBx17OverflowSize);
STATIC_ASSERT(PKMN_STORAGE_BX17_PAYLOAD_SIZE == 2292, PokemonStorageBx17PayloadSize);
STATIC_ASSERT(PKMN_STORAGE_BX18_EXTENSION_SIZE == 4588, PokemonStorageBx18ExtensionSize);
STATIC_ASSERT(PKMN_STORAGE_BX18_PAYLOAD_SIZE == 4580, PokemonStorageBx18PayloadSize);
STATIC_ASSERT(PKMN_STORAGE_BX18_OVERFLOW_OFFSET == 1324, PokemonStorageBx18OverflowOffset);
STATIC_ASSERT(PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET == 1332, PokemonStorageBx18PayloadOverflowOffset);
STATIC_ASSERT(PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_SIZE == 2636, PokemonStorageBx18PayloadOverflowSize);
STATIC_ASSERT(PKMN_STORAGE_EXTENSION_TAIL_OFFSET == 39680, PokemonStorageExtensionTailOffset);
STATIC_ASSERT(PKMN_STORAGE_REGULAR_SIZE + SECTOR_DATA_SIZE == 39680, PokemonStoragePersistedPrefixSize);
STATIC_ASSERT(PKMN_STORAGE_BX18_TAIL_SIZE == 1944, PokemonStorageSplitTailSize);
STATIC_ASSERT(sizeof(((struct SaveBlock1 *)0)->pokemonStorageExtensionTail) == 1944, PokemonStorageExtensionTailSize);
STATIC_ASSERT(PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_SIZE + sizeof(((struct SaveBlock1 *)0)->pokemonStorageExtensionTail) == PKMN_STORAGE_BX18_PAYLOAD_SIZE, PokemonStorageBx18SplitPayloadSize);
STATIC_ASSERT(PKMN_STORAGE_BOX19_RECORD_SIZE == 2292, PokemonStorageBox19RecordSize);
STATIC_ASSERT(offsetof(struct Bx19AuxiliaryRecord, box19) == 12, Bx19AuxiliaryHeaderSize);
STATIC_ASSERT(offsetof(struct Bx19AuxiliaryRecord, hallOfFame) == 2304, Bx19AuxiliaryArchiveOffset);
STATIC_ASSERT(offsetof(struct Bx19AuxiliaryRecord, hallOfFame.teams) == 2308, Bx19AuxiliaryTeamsOffset);
STATIC_ASSERT(sizeof(((struct Bx19AuxiliaryRecord *)0)->hallOfFame.teams) == 1584, Bx19AuxiliaryTeamsSize);
STATIC_ASSERT(sizeof(struct Bx19AuxiliaryRecord) == 3892, Bx19AuxiliaryUsedSize);
STATIC_ASSERT(SECTOR_DATA_SIZE - sizeof(struct Bx19AuxiliaryRecord) == 76, Bx19AuxiliaryFreeSpace);
STATIC_ASSERT(sizeof(struct Bx19AuxiliaryRecord) - offsetof(struct Bx19AuxiliaryRecord, box19) == 3880, Bx19AuxiliaryPayloadSize);
STATIC_ASSERT(SAVEBLOCK1_EXTENSION_TAIL_SECTOR_OFFSET == 1562, SaveBlock1ExtensionTailSectorOffset);
STATIC_ASSERT(PKMN_STORAGE_BX16_OVERFLOW_SIZE % sizeof(u32) == 0, PokemonStorageBx16OverflowChecksumAlignment);
STATIC_ASSERT(PKMN_STORAGE_BX17_PAYLOAD_SIZE % sizeof(u32) == 0, PokemonStorageBx17ChecksumAlignment);
STATIC_ASSERT(PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_SIZE % sizeof(u32) == 0, PokemonStorageBx18OverflowChecksumAlignment);
STATIC_ASSERT(sizeof(((struct SaveBlock1 *)0)->pokemonStorageExtensionTail) % sizeof(u32) == 0, PokemonStorageBx18TailChecksumAlignment);
STATIC_ASSERT((sizeof(struct Bx19AuxiliaryRecord) - offsetof(struct Bx19AuxiliaryRecord, box19)) % sizeof(u32) == 0, Bx19AuxiliaryChecksumAlignment);

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
EWRAM_DATA static bool8 sPokemonStorageFullSavePrepared = FALSE;
EWRAM_DATA static bool8 sSaveHallOfFame = FALSE;
EWRAM_DATA static enum LinkFullSaveResult sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_PENDING;
EWRAM_DATA static bool8 sDeferLinkFullSaveErrorScreen = FALSE;
COMMON_DATA static struct HallOfFameArchive *sLegacyHallOfFameRetryArchive = NULL;
COMMON_DATA static u32 sLegacyHallOfFameRetryCounter = 0;
COMMON_DATA static bool8 sResetHallOfFameArchive = FALSE;
EWRAM_DATA static u32 sPreviousBoxExtensionMagic = 0;
EWRAM_DATA static u32 sPreviousBox18ExtensionMagic = 0;
EWRAM_DATA static u16 sPreviousBox18Checksum = 0;
EWRAM_DATA static u16 sPreviousBox18ChecksumInverse = 0;

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

static u8 WriteSaveSectorOrSlot(u16 sectorId, const struct SaveSectorLocation *locations, bool8 saveHallOfFame)
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
        if (!PreparePokemonStorageExtensions(saveHallOfFame))
            return SAVE_STATUS_PREPARE_ERROR;
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
            {
                if (HandleWriteSector(i, locations) != SAVE_STATUS_OK)
                {
                    status = SAVE_STATUS_ERROR;
                    break;
                }
            }
        }

        if (status == SAVE_STATUS_OK)
            status = WriteBx19AuxiliarySector();

        if (status != SAVE_STATUS_OK || gDamagedSaveSectors)
        {
            // At least one sector save failed
            status = SAVE_STATUS_ERROR;
            gLastWrittenSector = gLastKnownGoodSector;
            gSaveCounter = gLastSaveCounter;
            FinishPokemonStorageExtensions(FALSE);
        }
        else
            FinishPokemonStorageExtensions(TRUE);
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

    if (CopyPokemonStorageExtensionTailToSaveSector(sectorId))
        gReadWriteSector->checksum = CalculateChecksum(gReadWriteSector->data, size);
    else
        gReadWriteSector->checksum = CalculateChecksum(data, size);

    return TryWriteSector(sector, gReadWriteSector->data);
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

    for (i = 0; i < SECTOR_DATA_SIZE; i++)
        gReadWriteSector->data[i] = src[i];

    gReadWriteSector->id = sectorId;
    // Keep this footer checksum limited to the historical BX16 prefix. An
    // older BX16 ROM can therefore still validate and load Boxes 1-16.
    gReadWriteSector->checksum = CalculateChecksum(src, PKMN_STORAGE_BX16_OVERFLOW_SIZE);
    gReadWriteSector->signature = SECTOR_SIGNATURE;
    gReadWriteSector->counter = gSaveCounter;

    return TryWriteSector(sectorId, gReadWriteSector->data);
}

static u8 WriteBx19AuxiliarySector(void)
{
    u16 i;
    u8 sectorId = SECTOR_ID_BX19_AUXILIARY_1 + (gSaveCounter % NUM_SAVE_SLOTS);
    struct Bx19AuxiliaryRecord *record;

    if (!sSaveHallOfFame
     && !sResetHallOfFameArchive
     && sPreviousBox18ExtensionMagic == POKEMON_STORAGE_BOX19_MAGIC)
    {
        if (!IsBx19AuxiliarySectorValid(gLastSaveCounter % NUM_SAVE_SLOTS,
                                        gLastSaveCounter))
            return SAVE_STATUS_ERROR;
    }
    else
    {
        for (i = 0; i < SECTOR_SIZE; i++)
            ((u8 *)gReadWriteSector)[i] = 0;
    }

    record = (struct Bx19AuxiliaryRecord *)gReadWriteSector->data;
    record->magic = POKEMON_STORAGE_BOX19_MAGIC;
    record->version = BX19_SCHEMA_VERSION;
    record->payloadLength = sizeof(*record)
                          - offsetof(struct Bx19AuxiliaryRecord, box19);
    memcpy(&record->box19,
           &gPokemonStoragePtr->box19,
           PKMN_STORAGE_BOX19_RECORD_SIZE);

    if (sSaveHallOfFame)
    {
        record->hallOfFame.count = CountRetainedHallOfFameTeams(gHoFSaveBuffer);
        memcpy(record->hallOfFame.teams,
               gHoFSaveBuffer,
               record->hallOfFame.count * sizeof(struct HallofFameTeam));
    }
    else if (!sResetHallOfFameArchive
          && sPreviousBox18ExtensionMagic != POKEMON_STORAGE_BOX19_MAGIC
          && sLegacyHallOfFameRetryArchive != NULL
          && sLegacyHallOfFameRetryCounter == gLastSaveCounter)
    {
        record->hallOfFame = *sLegacyHallOfFameRetryArchive;
    }

    record->checksum = CalculateChecksum(&record->box19, record->payloadLength);
    record->checksumInverse = (u16)~record->checksum;
    gReadWriteSector->id = sectorId;
    gReadWriteSector->checksum = CalculateChecksum(gReadWriteSector->data, SECTOR_DATA_SIZE);
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

static u32 AddChecksumWords(const u8 *data, u16 size, u32 checksum)
{
    u16 i;

    for (i = 0; i < size; i += sizeof(u32))
    {
        checksum += (u32)data[i]
                  | (u32)data[i + 1] << 8
                  | (u32)data[i + 2] << 16
                  | (u32)data[i + 3] << 24;
    }

    return checksum;
}

static u16 FoldChecksum(u32 checksum)
{
    return (checksum >> 16) + checksum;
}

static bool8 IsBx19AuxiliarySectorValid(u8 slotId, u32 counter)
{
    u8 sectorId = SECTOR_ID_BX19_AUXILIARY_1 + slotId;
    struct Bx19AuxiliaryRecord *record;

    ReadFlashSector(sectorId, gReadWriteSector);
    record = (struct Bx19AuxiliaryRecord *)gReadWriteSector->data;
    if (gReadWriteSector->id != sectorId
     || gReadWriteSector->signature != SECTOR_SIGNATURE
     || gReadWriteSector->counter != counter
     || gReadWriteSector->checksum != CalculateChecksum(gReadWriteSector->data, SECTOR_DATA_SIZE))
        return FALSE;

    if (record->magic != POKEMON_STORAGE_BOX19_MAGIC
     || record->version != BX19_SCHEMA_VERSION
     || record->payloadLength != sizeof(*record) - offsetof(struct Bx19AuxiliaryRecord, box19)
     || record->checksumInverse != (u16)~record->checksum
     || record->checksum != CalculateChecksum(&record->box19, record->payloadLength)
     || record->hallOfFame.count > HALL_OF_FAME_RETAINED_TEAMS
     || !IsZeroed(record->hallOfFame.reserved, sizeof(record->hallOfFame.reserved))
     || !IsZeroed(&gReadWriteSector->data[sizeof(*record)], SECTOR_DATA_SIZE - sizeof(*record)))
        return FALSE;

    return TRUE;
}

static enum PokemonStorageOverflowStatus GetPokemonStorageOverflowStatus(
    u8 slotId,
    u32 counter,
    u8 saveBlock1Sector,
    const struct SaveSectorLocation *locations)
{
    u8 sectorId = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + slotId;
    u8 *data;
    u16 checksum;
    u32 rollingChecksum;
    u32 extensionMagic;

    ReadFlashSector(sectorId, gReadWriteSector);
    data = gReadWriteSector->data;
    if (gReadWriteSector->id != sectorId
     || gReadWriteSector->checksum != CalculateChecksum(data, PKMN_STORAGE_BX16_OVERFLOW_SIZE)
     || gReadWriteSector->signature != SECTOR_SIGNATURE
     || gReadWriteSector->counter != counter)
        return PKMN_STORAGE_OVERFLOW_INVALID;

    // Released BX16 ROMs zeroed the whole sector before writing their
    // 1,324-byte overflow. Any nonzero tail must be a complete BX18 record.
    if (IsZeroed(&data[PKMN_STORAGE_BX18_OVERFLOW_OFFSET],
                 SECTOR_DATA_SIZE - PKMN_STORAGE_BX18_OVERFLOW_OFFSET))
        return PKMN_STORAGE_OVERFLOW_BX16;

    extensionMagic = *(u32 *)&data[PKMN_STORAGE_BX18_OVERFLOW_OFFSET];
    if (extensionMagic == POKEMON_STORAGE_BOX17_MAGIC)
    {
        checksum = *(u16 *)&data[PKMN_STORAGE_BX18_OVERFLOW_OFFSET + sizeof(u32)];
        if (!IsZeroed(&data[PKMN_STORAGE_BX17_OVERFLOW_SIZE],
                      SECTOR_DATA_SIZE - PKMN_STORAGE_BX17_OVERFLOW_SIZE)
         || *(u16 *)&data[PKMN_STORAGE_BX18_OVERFLOW_OFFSET + sizeof(u32) + sizeof(u16)] != (u16)~checksum
         || checksum != CalculateChecksum(
                &data[PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET],
                PKMN_STORAGE_BX17_PAYLOAD_SIZE))
            return PKMN_STORAGE_OVERFLOW_INVALID;
        return PKMN_STORAGE_OVERFLOW_BX17;
    }

    if (extensionMagic != POKEMON_STORAGE_BOX18_MAGIC
     && extensionMagic != POKEMON_STORAGE_BOX19_MAGIC)
        return PKMN_STORAGE_OVERFLOW_INVALID;

    checksum = *(u16 *)&data[PKMN_STORAGE_BX18_OVERFLOW_OFFSET + sizeof(u32)];
    if (*(u16 *)&data[PKMN_STORAGE_BX18_OVERFLOW_OFFSET + sizeof(u32) + sizeof(u16)] != (u16)~checksum)
        return PKMN_STORAGE_OVERFLOW_INVALID;

    // BX18's frozen format used a payload-only checksum. BX19 seeds the same
    // rolling checksum with its format marker so a corrupted "BX19" marker
    // cannot be reinterpreted as the otherwise-compatible BX18 layout.
    rollingChecksum = AddChecksumWords(
        &data[PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET],
        PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_SIZE,
        extensionMagic == POKEMON_STORAGE_BOX19_MAGIC
            ? POKEMON_STORAGE_BOX19_MAGIC
            : 0);

    if (saveBlock1Sector >= SECTOR_ID_PKMN_STORAGE_OVERFLOW_1)
        return PKMN_STORAGE_OVERFLOW_INVALID;
    ReadFlashSector(saveBlock1Sector, gReadWriteSector);
    if (gReadWriteSector->id != SECTOR_ID_SAVEBLOCK1_END
     || gReadWriteSector->signature != SECTOR_SIGNATURE
     || gReadWriteSector->counter != counter
     || gReadWriteSector->checksum != CalculateChecksum(
            gReadWriteSector->data,
            locations[SECTOR_ID_SAVEBLOCK1_END].size))
        return PKMN_STORAGE_OVERFLOW_INVALID;

    rollingChecksum = AddChecksumWords(
        &gReadWriteSector->data[SAVEBLOCK1_EXTENSION_TAIL_SECTOR_OFFSET],
        PKMN_STORAGE_BX18_TAIL_SIZE,
        rollingChecksum);
    if (checksum != FoldChecksum(rollingChecksum))
        return PKMN_STORAGE_OVERFLOW_INVALID;

    if (extensionMagic == POKEMON_STORAGE_BOX19_MAGIC)
        return PKMN_STORAGE_OVERFLOW_BX19;
    return PKMN_STORAGE_OVERFLOW_BX18;
}

static u8 FindSaveSlotSector(u8 slotId, u16 logicalSectorId, u32 counter)
{
    u8 i;
    u8 slotOffset = NUM_SECTORS_PER_SLOT * slotId;

    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(slotOffset + i, gReadWriteSector);
        if (gReadWriteSector->id == logicalSectorId
         && gReadWriteSector->signature == SECTOR_SIGNATURE
         && gReadWriteSector->counter == counter)
            return slotOffset + i;
    }

    return SECTOR_ID_PKMN_STORAGE_OVERFLOW_1;
}

static void LoadPokemonStorageOverflow(void)
{
    u8 *dst;
    u8 slotId;
    u8 saveBlock1Sector;
    u8 overflowSector;
    enum PokemonStorageOverflowStatus status;

    if (gPokemonStoragePtr->boxExtensionMagic != POKEMON_STORAGE_EXTENSION_MAGIC)
    {
        InitPokemonStorageExtension();
        return;
    }

    slotId = gSaveCounter % NUM_SAVE_SLOTS;
    saveBlock1Sector = FindSaveSlotSector(slotId, SECTOR_ID_SAVEBLOCK1_END, gSaveCounter);
    status = GetPokemonStorageOverflowStatus(slotId, gSaveCounter, saveBlock1Sector, gRamSaveSectorLocations);
    if (status == PKMN_STORAGE_OVERFLOW_INVALID)
        return;

    overflowSector = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1 + slotId;
    ReadFlashSector(overflowSector, gReadWriteSector);
    dst = (u8 *)gPokemonStoragePtr + PKMN_STORAGE_REGULAR_SIZE;
    if (status == PKMN_STORAGE_OVERFLOW_BX16)
    {
        memcpy(dst, gReadWriteSector->data, PKMN_STORAGE_BX16_OVERFLOW_SIZE);
        InitPokemonStorageBox18Extension();
    }
    else if (status == PKMN_STORAGE_OVERFLOW_BX17)
    {
        memcpy(dst, gReadWriteSector->data, PKMN_STORAGE_BX16_OVERFLOW_SIZE);
        // Initialize Boxes 18 and 19, then restore the accepted BX17 payload
        // directly from the sector which was already validated and read.
        InitPokemonStorageBox18Extension();
        memcpy(gPokemonStoragePtr->extensionBoxes[0],
               &gReadWriteSector->data[PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET],
               sizeof(gPokemonStoragePtr->extensionBoxes[0]));
        memcpy(gPokemonStoragePtr->extensionBoxNames[0],
               &gReadWriteSector->data[PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET
                                     + sizeof(gPokemonStoragePtr->extensionBoxes[0])],
               sizeof(gPokemonStoragePtr->extensionBoxNames[0]));
        gPokemonStoragePtr->extensionBoxWallpapers[0]
            = gReadWriteSector->data[PKMN_STORAGE_BX18_PAYLOAD_OVERFLOW_OFFSET
                                   + sizeof(gPokemonStoragePtr->extensionBoxes[0])
                                   + sizeof(gPokemonStoragePtr->extensionBoxNames[0])];
    }
    else
    {
        memcpy(dst, gReadWriteSector->data, SECTOR_DATA_SIZE);
        memcpy((u8 *)gPokemonStoragePtr + PKMN_STORAGE_EXTENSION_TAIL_OFFSET,
               gSaveBlock1Ptr->pokemonStorageExtensionTail,
               PKMN_STORAGE_BX18_TAIL_SIZE);

        if (status == PKMN_STORAGE_OVERFLOW_BX18)
        {
            InitPokemonStorageBox19Extension();
        }
        else
        {
            struct Bx19AuxiliaryRecord *record;

            ReadFlashSector(SECTOR_ID_BX19_AUXILIARY_1 + slotId, gReadWriteSector);
            record = (struct Bx19AuxiliaryRecord *)gReadWriteSector->data;
            memcpy(&gPokemonStoragePtr->box19, &record->box19, PKMN_STORAGE_BOX19_RECORD_SIZE);
        }
    }
}

static bool8 PreparePokemonStorageExtensions(bool8 saveHallOfFame)
{
    u8 legacyStatus;

    sPreviousBoxExtensionMagic = gPokemonStoragePtr->boxExtensionMagic;
    sPreviousBox18ExtensionMagic = gPokemonStoragePtr->box18ExtensionMagic;
    sPreviousBox18Checksum = gPokemonStoragePtr->box18Checksum;
    sPreviousBox18ChecksumInverse = gPokemonStoragePtr->box18ChecksumInverse;
    sSaveHallOfFame = saveHallOfFame && gHoFSaveBuffer != NULL;

    if (sResetHallOfFameArchive)
    {
        ClearLegacyHallOfFameRetryArchive();
    }
    else if (sPreviousBox18ExtensionMagic == POKEMON_STORAGE_BOX19_MAGIC)
    {
        ClearLegacyHallOfFameRetryArchive();
        if (!sSaveHallOfFame
         && !IsBx19AuxiliarySectorValid(gSaveCounter % NUM_SAVE_SLOTS, gSaveCounter))
            return FALSE;
    }
    else if (sLegacyHallOfFameRetryArchive == NULL
          || sLegacyHallOfFameRetryCounter != gSaveCounter)
    {
        ClearLegacyHallOfFameRetryArchive();
        sLegacyHallOfFameRetryArchive = AllocZeroedUnchecked(sizeof(*sLegacyHallOfFameRetryArchive));
        if (sLegacyHallOfFameRetryArchive == NULL)
            return FALSE;

        // Cache the committed legacy archive, not gHoFSaveBuffer. During a
        // Hall of Fame save that buffer already contains the newly appended
        // team, which must not survive a failed transaction.
        legacyStatus = LoadLegacyHallOfFameArchive(sLegacyHallOfFameRetryArchive);

        if (legacyStatus != LEGACY_HOF_ARCHIVE_VALID
         || sLegacyHallOfFameRetryArchive->count == 0)
            ClearLegacyHallOfFameRetryArchive();
        else
            sLegacyHallOfFameRetryCounter = gSaveCounter;
    }

    sPokemonStorageFullSavePrepared = TRUE;
    gPokemonStoragePtr->boxExtensionMagic = POKEMON_STORAGE_EXTENSION_MAGIC;
    gPokemonStoragePtr->box18ExtensionMagic = POKEMON_STORAGE_BOX19_MAGIC;
    gPokemonStoragePtr->box18Checksum = FoldChecksum(AddChecksumWords(
        (u8 *)&gPokemonStoragePtr->extensionBoxes,
        PKMN_STORAGE_BX18_PAYLOAD_SIZE,
        POKEMON_STORAGE_BOX19_MAGIC));
    gPokemonStoragePtr->box18ChecksumInverse = (u16)~gPokemonStoragePtr->box18Checksum;
    return TRUE;
}

static void FinishPokemonStorageExtensions(bool8 commit)
{
    if (!sPokemonStorageFullSavePrepared)
        return;

    if (commit)
    {
        memcpy(gSaveBlock1Ptr->pokemonStorageExtensionTail,
               (u8 *)gPokemonStoragePtr + PKMN_STORAGE_EXTENSION_TAIL_OFFSET,
               PKMN_STORAGE_BX18_TAIL_SIZE);
        ClearLegacyHallOfFameRetryArchive();
        sResetHallOfFameArchive = FALSE;
    }
    else
    {
        gPokemonStoragePtr->boxExtensionMagic = sPreviousBoxExtensionMagic;
        gPokemonStoragePtr->box18ExtensionMagic = sPreviousBox18ExtensionMagic;
        gPokemonStoragePtr->box18Checksum = sPreviousBox18Checksum;
        gPokemonStoragePtr->box18ChecksumInverse = sPreviousBox18ChecksumInverse;
    }
    sSaveHallOfFame = FALSE;
    sPokemonStorageFullSavePrepared = FALSE;
}

static bool8 CopyPokemonStorageExtensionTailToSaveSector(u16 sectorId)
{
    if (!sPokemonStorageFullSavePrepared || sectorId != SECTOR_ID_SAVEBLOCK1_END)
        return FALSE;

    memcpy(&gReadWriteSector->data[SAVEBLOCK1_EXTENSION_TAIL_SECTOR_OFFSET],
           (u8 *)gPokemonStoragePtr + PKMN_STORAGE_EXTENSION_TAIL_OFFSET,
           PKMN_STORAGE_BX18_TAIL_SIZE);
    return TRUE;
}

static u8 LoadLegacyHallOfFameArchive(struct HallOfFameArchive *archive)
{
    return LoadLegacyHallOfFameTeams(archive->teams, &archive->count);
}

static bool8 AreLegacyHallOfFameSectorsValid(void)
{
    u8 sectorId;

    for (sectorId = SECTOR_ID_HOF_1; sectorId <= SECTOR_ID_HOF_2; sectorId++)
    {
        ReadFlashSector(sectorId, gReadWriteSector);
        if (gReadWriteSector->signature != SECTOR_SIGNATURE
         || gReadWriteSector->id != CalculateChecksum(gReadWriteSector->data,
                                                       SECTOR_DATA_SIZE))
            return FALSE;
    }

    return TRUE;
}

static void ReadLegacyHallOfFameData(u16 offset, void *dst, u16 size)
{
    u8 *bytes = dst;

    while (size != 0)
    {
        u8 sectorId = SECTOR_ID_HOF_1 + offset / SECTOR_DATA_SIZE;
        u16 sectorOffset = offset % SECTOR_DATA_SIZE;
        u16 chunkSize = min(size, SECTOR_DATA_SIZE - sectorOffset);

        ReadFlash(sectorId, sectorOffset, bytes, chunkSize);
        bytes += chunkSize;
        offset += chunkSize;
        size -= chunkSize;
    }
}

static u8 LoadLegacyHallOfFameTeams(struct HallofFameTeam *teams, u8 *retainedCount)
{
    u8 count;
    struct HallofFameMon firstMon;

    *retainedCount = 0;
    memset(teams, 0, sizeof(*teams) * HALL_OF_FAME_RETAINED_TEAMS);
    if (!AreLegacyHallOfFameSectorsValid())
        return LEGACY_HOF_ARCHIVE_UNAVAILABLE;

    for (count = 0; count < HALL_OF_FAME_LEGACY_MAX_TEAMS; count++)
    {
        ReadLegacyHallOfFameData(count * sizeof(struct HallofFameTeam),
                                &firstMon,
                                sizeof(firstMon));
        if (firstMon.species == SPECIES_NONE)
            break;
    }

    *retainedCount = min(count, HALL_OF_FAME_RETAINED_TEAMS);
    ReadLegacyHallOfFameData((count - *retainedCount) * sizeof(struct HallofFameTeam),
                            teams,
                            *retainedCount * sizeof(struct HallofFameTeam));
    return LEGACY_HOF_ARCHIVE_VALID;
}

static void ClearLegacyHallOfFameRetryArchive(void)
{
    TRY_FREE_AND_SET_NULL(sLegacyHallOfFameRetryArchive);
    sLegacyHallOfFameRetryCounter = 0;
}

void ResetHallOfFameArchive(void)
{
    ClearLegacyHallOfFameRetryArchive();
    sResetHallOfFameArchive = TRUE;
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

    // LinkFullSave writes its final regular sector through this replacement
    // path. That sector contains the SaveBlock1 copy of the Box 18 tail, so it
    // must receive the same prepared override as an ordinary full save.
    // Partial SAVE_LINK writes do not prepare storage and remain unchanged.
    if (CopyPokemonStorageExtensionTailToSaveSector(sectorId))
        gReadWriteSector->checksum = CalculateChecksum(gReadWriteSector->data, size);
    else
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

static u8 GetSaveSlotStatus(
    u8 slotId,
    const struct SaveSectorLocation *locations,
    u32 *saveCounter)
{
    u16 i;
    u16 checksum;
    u32 validSectorFlags = 0;
    u8 slotOffset = NUM_SECTORS_PER_SLOT * slotId;
    u8 saveBlock1Sector = SECTOR_ID_PKMN_STORAGE_OVERFLOW_1;
    bool8 signatureValid = FALSE;
    bool8 counterValid = FALSE;
    bool8 countersMatch = TRUE;
    bool8 usesStorageOverflow = FALSE;
    bool8 malformedStorageMarker = FALSE;
    u8 currentBox = 0;
    enum PokemonStorageOverflowStatus overflowStatus = PKMN_STORAGE_OVERFLOW_INVALID;

    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i + slotOffset, gReadWriteSector);
        if (gReadWriteSector->signature == SECTOR_SIGNATURE)
        {
            signatureValid = TRUE;
            if (gReadWriteSector->id < NUM_SECTORS_PER_SLOT)
            {
                checksum = CalculateChecksum(gReadWriteSector->data, locations[gReadWriteSector->id].size);
                if (gReadWriteSector->checksum == checksum)
                {
                    if (!counterValid)
                    {
                        *saveCounter = gReadWriteSector->counter;
                        counterValid = TRUE;
                    }
                    else if (*saveCounter != gReadWriteSector->counter)
                    {
                        countersMatch = FALSE;
                    }

                    validSectorFlags |= 1 << gReadWriteSector->id;
                    if (gReadWriteSector->id == SECTOR_ID_PKMN_STORAGE_START)
                        currentBox = gReadWriteSector->data[0];
                    if (gReadWriteSector->id == SECTOR_ID_SAVEBLOCK1_END)
                        saveBlock1Sector = i + slotOffset;
                    if (gReadWriteSector->id == SECTOR_ID_PKMN_STORAGE_END)
                    {
                        if (*(u32 *)&gReadWriteSector->data[PKMN_STORAGE_EXTENSION_SECTOR_OFFSET] == POKEMON_STORAGE_EXTENSION_MAGIC)
                            usesStorageOverflow = TRUE;
                        else if (!IsZeroed(&gReadWriteSector->data[PKMN_STORAGE_EXTENSION_SECTOR_OFFSET],
                                           SECTOR_DATA_SIZE - PKMN_STORAGE_EXTENSION_SECTOR_OFFSET))
                            malformedStorageMarker = TRUE;
                    }
                }
            }
        }
    }

    if (!signatureValid)
        return SAVE_STATUS_EMPTY;
    if (validSectorFlags != (1 << NUM_SECTORS_PER_SLOT) - 1
     || !countersMatch
     || malformedStorageMarker)
        return SAVE_STATUS_ERROR;
    if (usesStorageOverflow)
    {
        overflowStatus = GetPokemonStorageOverflowStatus(
            slotId, *saveCounter, saveBlock1Sector, locations);
        if (overflowStatus == PKMN_STORAGE_OVERFLOW_INVALID
         || (overflowStatus == PKMN_STORAGE_OVERFLOW_BX19
          && !IsBx19AuxiliarySectorValid(slotId, *saveCounter)))
            return SAVE_STATUS_ERROR;
    }

    switch (overflowStatus)
    {
    case PKMN_STORAGE_OVERFLOW_BX16:
        if (currentBox >= 16)
            return SAVE_STATUS_ERROR;
        break;
    case PKMN_STORAGE_OVERFLOW_BX17:
        if (currentBox >= 17)
            return SAVE_STATUS_ERROR;
        break;
    case PKMN_STORAGE_OVERFLOW_BX18:
        if (currentBox >= 18)
            return SAVE_STATUS_ERROR;
        break;
    case PKMN_STORAGE_OVERFLOW_BX19:
        if (currentBox >= 19)
            return SAVE_STATUS_ERROR;
        break;
    default:
        if (currentBox >= LEGACY_BOXES_COUNT)
            return SAVE_STATUS_ERROR;
        break;
    }

    return SAVE_STATUS_OK;
}

static u8 GetSaveValidStatus(const struct SaveSectorLocation *locations)
{
    u32 saveSlot1Counter = 0;
    u32 saveSlot2Counter = 0;
    u8 saveSlot1Status = GetSaveSlotStatus(0, locations, &saveSlot1Counter);
    u8 saveSlot2Status = GetSaveSlotStatus(1, locations, &saveSlot2Counter);

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
    u8 status = SAVE_STATUS_OK;
    u32 previousHallOfFameCount;
    u32 *backupVar = gTrainerHillVBlankCounter;

    gTrainerHillVBlankCounter = NULL;
    gDamagedSaveSectors = 0;
    UpdateSaveAddresses();
    switch (saveType)
    {
    case SAVE_HALL_OF_FAME:
        previousHallOfFameCount = GetGameStat(GAME_STAT_ENTERED_HOF);
        if (GetGameStat(GAME_STAT_ENTERED_HOF) < 999)
            IncrementGameStat(GAME_STAT_ENTERED_HOF);

        // The newly appended team is already in gHoFSaveBuffer. It is staged
        // into the final commit sector before any flash writes begin.
        CopyPartyAndObjectsToSave();
        status = WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations, TRUE);
        if (status != SAVE_STATUS_OK)
            SetGameStat(GAME_STAT_ENTERED_HOF, previousHallOfFameCount);
        break;
    case SAVE_NORMAL:
    default:
        CopyPartyAndObjectsToSave();
        status = WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations, FALSE);
        break;
    case SAVE_LINK:
    case SAVE_EREADER: // Dummied, now duplicate of SAVE_LINK
        // Used by link / Battle Frontier
        // Write only SaveBlocks 1 and 2 (skips the PC)
        FinishPokemonStorageExtensions(FALSE);
        CopyPartyAndObjectsToSave();
        for (i = SECTOR_ID_SAVEBLOCK2; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
            HandleReplaceSector(i, gRamSaveSectorLocations);
        for (i = SECTOR_ID_SAVEBLOCK2; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
            WriteSectorSignatureByte_NoOffset(i, gRamSaveSectorLocations);
        if (gDamagedSaveSectors != 0)
            status = SAVE_STATUS_ERROR;
        break;
    case SAVE_OVERWRITE_DIFFERENT_FILE:
        // A different file must not inherit detailed teams from the previous
        // player. The alternate auxiliary sector remains intact as backup
        // until the new transaction commits.
        ResetHallOfFameArchive();
        CopyPartyAndObjectsToSave();
        status = WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations, FALSE);
        break;
    }
    gTrainerHillVBlankCounter = backupVar;
    return status;
}

u8 TrySavingData(u8 saveType)
{
    u8 status;

    if (gFlashMemoryPresent != TRUE)
    {
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        return SAVE_STATUS_ERROR;
    }

    status = HandleSavingData(saveType);
    if (status == SAVE_STATUS_OK && !gDamagedSaveSectors)
    {
        gSaveAttemptStatus = SAVE_STATUS_OK;
        return SAVE_STATUS_OK;
    }

    if (gDamagedSaveSectors)
    {
        DoSaveFailedScreen(saveType);
        status = SAVE_STATUS_ERROR;
    }

    gSaveAttemptStatus = status;
    return status;
}

bool8 LinkFullSave_Init(void)
{
    sPokemonStorageOverflowWriteFailed = FALSE;
    sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_PENDING;
    if (gFlashMemoryPresent != TRUE)
    {
        gSaveAttemptStatus = SAVE_STATUS_NO_FLASH;
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_FAILED;
        return TRUE;
    }
    UpdateSaveAddresses();
    CopyPartyAndObjectsToSave();
    if (!PreparePokemonStorageExtensions(FALSE))
    {
        sPokemonStorageOverflowWriteFailed = TRUE;
        gSaveAttemptStatus = SAVE_STATUS_PREPARE_ERROR;
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_FAILED;
        return TRUE;
    }
    RestoreSaveBackupVarsAndIncrement(gRamSaveSectorLocations);
    if (WritePokemonStorageOverflow() != SAVE_STATUS_OK)
    {
        sPokemonStorageOverflowWriteFailed = TRUE;
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_FLASH_ERROR;
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        FinishPokemonStorageExtensions(FALSE);
        if (!sDeferLinkFullSaveErrorScreen)
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
    {
        sPokemonStorageOverflowWriteFailed = TRUE;
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_FLASH_ERROR;
        FinishPokemonStorageExtensions(FALSE);
        if (!sDeferLinkFullSaveErrorScreen)
            DoSaveFailedScreen(SAVE_NORMAL);
    }

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
    {
        sPokemonStorageOverflowWriteFailed = TRUE;
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_FLASH_ERROR;
        FinishPokemonStorageExtensions(FALSE);
        if (!sDeferLinkFullSaveErrorScreen)
            DoSaveFailedScreen(SAVE_NORMAL);
    }
    return FALSE;
}

bool8 LinkFullSave_SetLastSectorSignature(void)
{
    u8 status;

    if (sPokemonStorageOverflowWriteFailed)
        return FALSE;

    status = CopySectorSignatureByte(NUM_SECTORS_PER_SLOT, gRamSaveSectorLocations);
    if (status == SAVE_STATUS_OK)
        status = WriteBx19AuxiliarySector();

    if (status != SAVE_STATUS_OK || gDamagedSaveSectors)
    {
        sPokemonStorageOverflowWriteFailed = TRUE;
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_FLASH_ERROR;
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        FinishPokemonStorageExtensions(FALSE);
        if (!sDeferLinkFullSaveErrorScreen)
            DoSaveFailedScreen(SAVE_NORMAL);
    }
    else
    {
        FinishPokemonStorageExtensions(TRUE);
        gSaveAttemptStatus = SAVE_STATUS_OK;
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_SUCCESS;
    }
    return FALSE;
}

enum LinkFullSaveResult GetLinkFullSaveResult(void)
{
    return sLinkFullSaveResult;
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
        if (status == SAVE_STATUS_OK || status == SAVE_STATUS_ERROR)
            sResetHallOfFameArchive = FALSE;
        if (sLegacyHallOfFameRetryArchive != NULL
         && ((status != SAVE_STATUS_OK
           && status != SAVE_STATUS_ERROR)
          || gPokemonStoragePtr->box18ExtensionMagic == POKEMON_STORAGE_BOX19_MAGIC
          || sLegacyHallOfFameRetryCounter != gSaveCounter))
            ClearLegacyHallOfFameRetryArchive();
        CopyPartyAndObjectsFromSave();
        gSaveFileStatus = status;
        gGameContinueCallback = NULL;
        break;
    case SAVE_HALL_OF_FAME:
        if (gHoFSaveBuffer != NULL)
        {
            u8 legacyStatus;
            u8 retainedCount;

            status = SAVE_STATUS_OK;
            if (!sResetHallOfFameArchive
             && gPokemonStoragePtr->box18ExtensionMagic == POKEMON_STORAGE_BOX19_MAGIC)
            {
                if (IsBx19AuxiliarySectorValid(gSaveCounter % NUM_SAVE_SLOTS, gSaveCounter))
                {
                    struct Bx19AuxiliaryRecord *record = (struct Bx19AuxiliaryRecord *)gReadWriteSector->data;
                    memset(gHoFSaveBuffer,
                           0,
                           sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
                    memcpy(gHoFSaveBuffer,
                           record->hallOfFame.teams,
                           record->hallOfFame.count * sizeof(struct HallofFameTeam));
                }
                else
                {
                    status = SAVE_STATUS_ERROR;
                }
            }
            else if (!sResetHallOfFameArchive)
            {
                if (sLegacyHallOfFameRetryArchive != NULL
                 && sLegacyHallOfFameRetryCounter == gSaveCounter)
                {
                    memset(gHoFSaveBuffer,
                           0,
                           sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
                    memcpy(gHoFSaveBuffer,
                           sLegacyHallOfFameRetryArchive->teams,
                           sLegacyHallOfFameRetryArchive->count * sizeof(struct HallofFameTeam));
                }
                else
                {
                    ClearLegacyHallOfFameRetryArchive();
                    legacyStatus = LoadLegacyHallOfFameTeams(gHoFSaveBuffer,
                                                             &retainedCount);
                    if (legacyStatus != LEGACY_HOF_ARCHIVE_VALID)
                    {
                        memset(gHoFSaveBuffer,
                               0,
                               sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
                    }
                }
            }
            else
            {
                memset(gHoFSaveBuffer,
                       0,
                       sizeof(struct HallofFameTeam) * HALL_OF_FAME_RETAINED_TEAMS);
            }
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
        sLinkFullSaveResult = LINK_FULL_SAVE_RESULT_PENDING;
        sDeferLinkFullSaveErrorScreen = TRUE;
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
        if (LinkFullSave_Init())
        {
            tState = 7;
        }
        else
        {
            tState = 4;
        }
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
            if (sLinkFullSaveResult == LINK_FULL_SAVE_RESULT_PENDING)
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
            sDeferLinkFullSaveErrorScreen = FALSE;
            if (sLinkFullSaveResult == LINK_FULL_SAVE_RESULT_FLASH_ERROR)
                DoSaveFailedScreen(SAVE_NORMAL);
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
