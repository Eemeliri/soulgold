#ifndef GUARD_POKEMON_STORAGE_LEGACY_H
#define GUARD_POKEMON_STORAGE_LEGACY_H

#include "pokemon_legacy.h"
#include "pokemon_storage_system.h"

struct PokemonStorageV19
{
    /*0x0000*/ u8 currentBox;
    /*0x0004*/ struct BoxPokemonV19 legacyBoxes[15][30];
    /*0x859C*/ u8 legacyBoxNames[15][9];
    /*0x8623*/ u8 legacyBoxWallpapers[15];
    /*0x8634*/ struct PokemonV19 fusions[4];

    /*0x87B4*/ u32 boxExtensionMagic;
    /*0x87B8*/ struct BoxPokemonV19 extraBox[30];
    /*0x90A0*/ u8 extraBoxName[9];
    /*0x90A9*/ u8 extraBoxWallpaper;
    /*0x90AA*/ u8 extraBoxPadding[2];

    /*0x90AC*/ u32 box18ExtensionMagic;
    /*0x90B0*/ u16 box18Checksum;
    /*0x90B2*/ u16 box18ChecksumInverse;
    /*0x90B4*/ struct BoxPokemonV19 extensionBoxes[2][30];
    /*0xA284*/ u8 extensionBoxNames[2][9];
    /*0xA296*/ u8 extensionBoxWallpapers[2];

    /*0xA298*/ struct BoxPokemonV19 box19[30];
    /*0xAB80*/ u8 box19Name[9];
    /*0xAB89*/ u8 box19Wallpaper;
    /*0xAB8A*/ u8 box19Padding[2];
};

STATIC_ASSERT(sizeof(struct BoxPokemonV19) == 76, BoxPokemonStorageSize);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, currentBox) == 0, PokemonStorageCurrentBoxOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, legacyBoxes) == 4, PokemonStorageBoxesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, legacyBoxNames) == 34204, PokemonStorageBoxNamesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, legacyBoxWallpapers) == 34339, PokemonStorageBoxWallpapersOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, fusions) == 34356, PokemonStorageFusionsOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, boxExtensionMagic) == 34740, PokemonStorageExtensionMagicOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extraBox) == 34744, PokemonStorageExtraBoxOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extraBoxName) == 37024, PokemonStorageExtraBoxNameOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extraBoxWallpaper) == 37033, PokemonStorageExtraBoxWallpaperOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extraBoxPadding) == 37034, PokemonStorageExtraBoxPaddingOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, box18ExtensionMagic) == 37036, PokemonStorageBox18MagicOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, box18Checksum) == 37040, PokemonStorageBox18ChecksumOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, box18ChecksumInverse) == 37042, PokemonStorageBox18ChecksumInverseOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extensionBoxes) == 37044, PokemonStorageExtensionBoxesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extensionBoxes[1]) == 39324, PokemonStorageExtensionBox18Offset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extensionBoxNames) == 41604, PokemonStorageExtensionBoxNamesOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extensionBoxNames[1]) == 41613, PokemonStorageExtensionBox18NameOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extensionBoxWallpapers) == 41622, PokemonStorageExtensionBoxWallpapersOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, extensionBoxWallpapers[1]) == 41623, PokemonStorageExtensionBox18WallpaperOffset);
STATIC_ASSERT(sizeof(((struct PokemonStorageV19 *)0)->extensionBoxes) == 4560, PokemonStorageExtensionBoxesSize);
STATIC_ASSERT(sizeof(((struct PokemonStorageV19 *)0)->extensionBoxNames) == 18, PokemonStorageExtensionBoxNamesSize);
STATIC_ASSERT(sizeof(((struct PokemonStorageV19 *)0)->extensionBoxWallpapers) == 2, PokemonStorageExtensionBoxWallpapersSize);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, box19) == 41624, PokemonStorageBox19Offset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, box19Name) == 43904, PokemonStorageBox19NameOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, box19Wallpaper) == 43913, PokemonStorageBox19WallpaperOffset);
STATIC_ASSERT(offsetof(struct PokemonStorageV19, box19Padding) == 43914, PokemonStorageBox19PaddingOffset);
STATIC_ASSERT(sizeof(((struct PokemonStorageV19 *)0)->box19) == 2280, PokemonStorageBox19PokemonSize);
STATIC_ASSERT(sizeof(struct PokemonStorageV19) == 43916, PokemonStorageSize);

#endif // GUARD_POKEMON_STORAGE_LEGACY_H
