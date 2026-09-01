#ifndef GUARD_POKEMON_STORAGE_SYSTEM_H
#define GUARD_POKEMON_STORAGE_SYSTEM_H

#include "main.h"

#define LEGACY_BOXES_COUNT      15
#define TOTAL_BOXES_COUNT       19
#define IN_BOX_ROWS             5 // Number of rows, 6 Pokémon per row
#define IN_BOX_COLUMNS          6 // Number of columns, 5 Pokémon per column
#define IN_BOX_COUNT            (IN_BOX_ROWS * IN_BOX_COLUMNS)
#define BOX_NAME_LENGTH         8
#define MAX_FUSION_STORAGE      4

// Magic numbers, don't worry about them...
#define POKEMON_STORAGE_EXTENSION_MAGIC 0x36315842 // "BX16"
#define POKEMON_STORAGE_BOX17_MAGIC     0x37315842 // "BX17"
#define POKEMON_STORAGE_BOX18_MAGIC     0x38315842 // "BX18"
#define POKEMON_STORAGE_BOX19_MAGIC     0x39315842 // "BX19"

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

    /*0x90AC*/ u32 box18ExtensionMagic;
    /*0x90B0*/ u16 box18Checksum;
    /*0x90B2*/ u16 box18ChecksumInverse;
    /*0x90B4*/ struct BoxPokemon extensionBoxes[2][IN_BOX_COUNT];
    /*0xA284*/ u8 extensionBoxNames[2][BOX_NAME_LENGTH + 1];
    /*0xA296*/ u8 extensionBoxWallpapers[2];

    /*0xA298*/ struct BoxPokemon box19[IN_BOX_COUNT];
    /*0xAB80*/ u8 box19Name[BOX_NAME_LENGTH + 1];
    /*0xAB89*/ u8 box19Wallpaper;
    /*0xAB8A*/ u8 box19Padding[2];
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
STATIC_ASSERT(offsetof(struct PokemonStorage, box18ExtensionMagic) == 37036, PokemonStorageBox18MagicOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box18Checksum) == 37040, PokemonStorageBox18ChecksumOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box18ChecksumInverse) == 37042, PokemonStorageBox18ChecksumInverseOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extensionBoxes) == 37044, PokemonStorageExtensionBoxesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extensionBoxes[1]) == 39324, PokemonStorageExtensionBox18Offset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extensionBoxNames) == 41604, PokemonStorageExtensionBoxNamesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extensionBoxNames[1]) == 41613, PokemonStorageExtensionBox18NameOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extensionBoxWallpapers) == 41622, PokemonStorageExtensionBoxWallpapersOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, extensionBoxWallpapers[1]) == 41623, PokemonStorageExtensionBox18WallpaperOffset);
STATIC_ASSERT(sizeof(((struct PokemonStorage *)0)->extensionBoxes) == 4560, PokemonStorageExtensionBoxesSize);
STATIC_ASSERT(sizeof(((struct PokemonStorage *)0)->extensionBoxNames) == 18, PokemonStorageExtensionBoxNamesSize);
STATIC_ASSERT(sizeof(((struct PokemonStorage *)0)->extensionBoxWallpapers) == 2, PokemonStorageExtensionBoxWallpapersSize);
STATIC_ASSERT(offsetof(struct PokemonStorage, box19) == 41624, PokemonStorageBox19Offset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box19Name) == 43904, PokemonStorageBox19NameOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box19Wallpaper) == 43913, PokemonStorageBox19WallpaperOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, box19Padding) == 43914, PokemonStorageBox19PaddingOffset);
STATIC_ASSERT(sizeof(((struct PokemonStorage *)0)->box19) == 2280, PokemonStorageBox19PokemonSize);
STATIC_ASSERT(sizeof(struct PokemonStorage) == 43916, PokemonStorageSize);

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
void InitPokemonStorageBox18Extension(void);
void InitPokemonStorageBox19Extension(void);
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
bool32 PokemonStorageSystem_TestClearsStalePaletteSwapDestination(void);
bool32 PokemonStorageSystem_TestTakeItemToBag(u8 boxId, u8 boxPosition);
s8 PokemonStorageSystem_TestDetermineBoxScrollDirection(u8 boxId);
u8 PokemonStorageSystem_TestGetBoxWallpaper(u8 boxId);
void PokemonStorageSystem_TestSetBoxWallpaper(u8 boxId, u8 wallpaperId);
u8 PokemonStorageSystem_TestReleaseBox(u8 boxId, bool8 eggsOnly, bool8 hasHeldMon);
bool32 PokemonStorageSystem_TestBulkReleaseMessagesFit(void);
bool32 PokemonStorageSystem_TestGuardsBoxReleaseMenu(void);
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
