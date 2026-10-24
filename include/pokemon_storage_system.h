#ifndef GUARD_POKEMON_STORAGE_SYSTEM_H
#define GUARD_POKEMON_STORAGE_SYSTEM_H

#include "main.h"

#define LEGACY_BOXES_COUNT      15
#define TOTAL_BOXES_COUNT       21
#define IN_BOX_ROWS             5 // Number of rows, 6 Pokémon per row
#define IN_BOX_COLUMNS          6 // Number of columns, 5 Pokémon per column
#define IN_BOX_COUNT            (IN_BOX_ROWS * IN_BOX_COLUMNS)
#define BOX_NAME_LENGTH         8
#define MAX_FUSION_STORAGE      4

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

#define POKEMON_STORAGE_BX21_MAGIC 0x31325842

struct Bx21StorageHeader
{
    u32 magic;
    u16 version;
    u16 payloadLength;
    u16 payloadChecksum;
    u16 checksumInverse;
    u32 magicInverse;
};

struct PokemonStorage
{
    struct Bx21StorageHeader header;
    u8 currentBox;
    u8 reserved[3];
    struct Pokemon fusions[MAX_FUSION_STORAGE];
    struct BoxPokemon boxes[TOTAL_BOXES_COUNT][IN_BOX_COUNT];
    u8 boxNames[TOTAL_BOXES_COUNT][BOX_NAME_LENGTH + 1];
    u8 boxWallpapers[TOTAL_BOXES_COUNT];
    u8 alignmentPadding[2];
};

STATIC_ASSERT(sizeof(struct Bx21StorageHeader) == 16, Bx21HeaderSize);
STATIC_ASSERT(offsetof(struct Bx21StorageHeader, payloadChecksum) == 8, Bx21ChecksumOffset);
STATIC_ASSERT(offsetof(struct Bx21StorageHeader, magicInverse) == 12, Bx21InverseOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, currentBox) == 16, Bx21CurrentBoxOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, fusions) == 20, Bx21FusionsOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, boxes) == 404, Bx21BoxesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, boxNames) == 43244, Bx21NamesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, boxWallpapers) == 43433, Bx21WallpapersOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, alignmentPadding) == 43454, Bx21PaddingOffset);
STATIC_ASSERT(sizeof(struct PokemonStorage) == 43456, Bx21StorageSize);

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
void InitPokemonStorageMissingBoxes(u32 firstBox);
void UpdatePokemonStorageHeader(void);
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
