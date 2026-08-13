#ifndef GUARD_POKEMON_STORAGE_SYSTEM_H
#define GUARD_POKEMON_STORAGE_SYSTEM_H

#include "main.h"

#define LEGACY_BOXES_COUNT      15
#define TOTAL_BOXES_COUNT       17
#define IN_BOX_ROWS             5 // Number of rows, 6 Pokémon per row
#define IN_BOX_COLUMNS          6 // Number of columns, 5 Pokémon per column
#define IN_BOX_COUNT            (IN_BOX_ROWS * IN_BOX_COLUMNS)
#define BOX_NAME_LENGTH         8
#define MAX_FUSION_STORAGE      4

// Marks saves which use sectors 30 and 31 for the sixteenth box overflow data.
#define POKEMON_STORAGE_EXTENSION_MAGIC 0x36315842 // "BX16"
// Marks the separately checksummed seventeenth box appended to the BX16 data.
#define POKEMON_STORAGE_BOX17_MAGIC     0x37315842 // "BX17"

/*
            COLUMNS
ROWS        0   1   2   3   4   5
            6   7   8   9   10  11
            12  13  14  15  16  17
            18  19  20  21  22  23
            24  25  26  27  28  29
*/

struct PokemonStorage
{
    /*0x0000*/ u8 currentBox;
    // Access these legacy arrays through the storage accessors below so the
    // extension boxes cannot accidentally be omitted.
    /*0x0004*/ struct BoxPokemon legacyBoxes[LEGACY_BOXES_COUNT][IN_BOX_COUNT];
    /*0x859C*/ u8 legacyBoxNames[LEGACY_BOXES_COUNT][BOX_NAME_LENGTH + 1];
    /*0x8623*/ u8 legacyBoxWallpapers[LEGACY_BOXES_COUNT];
    /*0x8634*/ struct Pokemon fusions[MAX_FUSION_STORAGE];

    // Keep all fields above in their original locations for save compatibility.
    /*0x87B4*/ u32 boxExtensionMagic;
    /*0x87B8*/ struct BoxPokemon extraBox[IN_BOX_COUNT];
    /*0x90A0*/ u8 extraBoxName[BOX_NAME_LENGTH + 1];
    /*0x90A9*/ u8 extraBoxWallpaper;
    /*0x90AA*/ u8 extraBoxPadding[2];

    // Keep the complete BX16 layout above byte-for-byte compatible. Box 17 is
    // an append-only extension with its own checksum because the overflow
    // sector footer remains compatible with BX16 ROMs.
    /*0x90AC*/ u32 box17ExtensionMagic;
    /*0x90B0*/ u16 box17Checksum;
    /*0x90B2*/ u16 box17ChecksumInverse;
    /*0x90B4*/ struct BoxPokemon box17[IN_BOX_COUNT];
    /*0x999C*/ u8 box17Name[BOX_NAME_LENGTH + 1];
    /*0x99A5*/ u8 box17Wallpaper;
    /*0x99A6*/ u8 box17Padding[2];
};

// Save-format contract. If one of these fails, the storage migration and
// sector split in save.c must be reviewed before changing the values.
STATIC_ASSERT(sizeof(struct BoxPokemon) == 76, BoxPokemonStorageSize);
STATIC_ASSERT(offsetof(struct PokemonStorage, currentBox) == 0, PokemonStorageCurrentBoxOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, legacyBoxes) == 4, PokemonStorageBoxesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, legacyBoxNames) == 34204, PokemonStorageBoxNamesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, legacyBoxWallpapers) == 34339, PokemonStorageBoxWallpapersOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, fusions) == 34356, PokemonStorageFusionsOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, boxExtensionMagic) == 34740, PokemonStorageExtensionMagicOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extraBox) == 34744, PokemonStorageExtraBoxOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extraBoxName) == 37024, PokemonStorageExtraBoxNameOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extraBoxWallpaper) == 37033, PokemonStorageExtraBoxWallpaperOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extraBoxPadding) == 37034, PokemonStorageExtraBoxPaddingOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box17ExtensionMagic) == 37036, PokemonStorageBox17MagicOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box17Checksum) == 37040, PokemonStorageBox17ChecksumOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box17ChecksumInverse) == 37042, PokemonStorageBox17ChecksumInverseOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box17) == 37044, PokemonStorageBox17Offset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box17Name) == 39324, PokemonStorageBox17NameOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box17Wallpaper) == 39333, PokemonStorageBox17WallpaperOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box17Padding) == 39334, PokemonStorageBox17PaddingOffset);
STATIC_ASSERT(sizeof(struct PokemonStorage) == 39336, PokemonStorageSize);

extern struct PokemonStorage *gPokemonStoragePtr;

void DrawTextWindowAndBufferTiles(const u8 *string, void *dst, u8 zero1, u8 zero2, s32 bytesToBuffer);
u8 CountMonsInBox(u8 boxId);
s16 GetFirstFreeBoxSpot(u8 boxId);
u8 CountPartyAliveNonEggMonsExcept(u8 slotToIgnore);
u16 CountPartyAliveNonEggMons_IgnoreVar0x8004Slot(void);
u8 CountPartyMons(void);
u8 *StringCopyAndFillWithSpaces(u8 *dst, const u8 *src, u16 n);
void ShowPokemonStorageSystemPC(void);
void ShowPokemonPCFromParty(void);
void CB2_ShowPokemonPCFromParty(void);
void PokemonPC_SetReturnToPartyCallback(MainCallback cb);
void ResetPokemonStorageSystem(void);
void InitPokemonStorageExtension(void);
void InitPokemonStorageBox17Extension(void);
s16 CompactPartySlots(void);
u8 StorageGetCurrentBox(void);
u32 GetBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request);
void SetBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request, const void *value);
u32 GetCurrentBoxMonData(u8 boxPosition, s32 request);
void SetCurrentBoxMonData(u8 boxPosition, s32 request, const void *value);
u32 GetAndCopyBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request, void *dst);
void SetBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon *src);
void CopyBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon *dst);
void ZeroBoxMonAt(u8 boxId, u8 boxPosition);
void BoxMonAtToMon(u8 boxId, u8 boxPosition, struct Pokemon *dst);
struct BoxPokemon *GetBoxedMonPtr(u8 boxId, u8 boxPosition);
u8 *GetBoxNamePtr(u8 boxId);
s16 AdvanceStorageMonIndex(struct BoxPokemon *boxMons, u8 currIndex, u8 maxIndex, u8 mode);
bool8 CheckFreePokemonStorageSpace(void);
bool32 CheckBoxMonSanityAt(u32 boxId, u32 boxPosition);
u32 CountStorageNonEggMons(void);
u32 CountAllStorageMons(void);
bool32 AnyStorageMonWithMove(enum Move move);

#if TESTING
bool32 PokemonStorageSystem_TestTakeItemToBag(u8 boxId, u8 boxPosition);
s8 PokemonStorageSystem_TestDetermineBoxScrollDirection(u8 boxId);
u8 PokemonStorageSystem_TestGetBoxWallpaper(u8 boxId);
void PokemonStorageSystem_TestSetBoxWallpaper(u8 boxId, u8 wallpaperId);
#endif

void ResetWaldaWallpaper(void);
void SetWaldaWallpaperLockedOrUnlocked(bool32 unlocked);
bool32 IsWaldaWallpaperUnlocked(void);
u32 GetWaldaWallpaperPatternId(void);
void SetWaldaWallpaperPatternId(u8 id);
u32 GetWaldaWallpaperIconId(void);
void SetWaldaWallpaperIconId(u8 id);
u16 *GetWaldaWallpaperColorsPtr(void);
void SetWaldaWallpaperColors(u16 color1, u16 color2);
u8 *GetWaldaPhrasePtr(void);
void SetWaldaPhrase(const u8 *src);
bool32 IsWaldaPhraseEmpty(void);

void ChooseMonFromStorage();
u32 CountPartyNonEggMons(void);
void RemoveSelectedPcMon(struct Pokemon *mon);
s32 StorePokemonInBox(struct BoxPokemon *src, u8 *boxId, u8 *position); //HnS

#endif // GUARD_POKEMON_STORAGE_SYSTEM_H
