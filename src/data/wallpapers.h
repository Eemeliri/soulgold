enum {
    WALLPAPER_HEART,
    WALLPAPER_SOUL,
    WALLPAPER_SPIKYPIKA,
    WALLPAPER_TRIO3,
    WALLPAPER_PIKAPIKA2,
    WALLPAPER_KIMONOGIRL,
    WALLPAPER_TRIO1,
    WALLPAPER_RENEGADE,
    WALLPAPER_TRIO2,
    WALLPAPER_TIMEANDSPACE,
    WALLPAPER_NOSTALGIC2,
    WALLPAPER_SEAFLOOR,
    WALLPAPER_NOSTALGIC1,
    WALLPAPER_DISTORTION,
    WALLPAPER_SPACE,
    WALLPAPER_BACKYARD,
    WALLPAPER_TORCHIC,
    WALLPAPER_PIKAPIKA1,
    WALLPAPER_CONTEST,
    WALLPAPER_REVIVAL,
    WALLPAPER_POKEATHLON,
    WALLPAPER_FOREST,
    WALLPAPER_CITY,
    WALLPAPER_DESERT,
    WALLPAPER_SAVANNA,
    WALLPAPER_CRAG,
    WALLPAPER_VOLCANO,
    WALLPAPER_SNOW,
    WALLPAPER_CAVE,
    WALLPAPER_BEACH,
    WALLPAPER_RIVER,
    WALLPAPER_SKY,
    WALLPAPER_POLKADOT,
    WALLPAPER_POKECENTER,
    WALLPAPER_MACHINE,
    WALLPAPER_PLAIN,
    WALLPAPER_GALACTIC1,
    WALLPAPER_GALACTIC2,
    WALLPAPER_BIGBROTHER,
    WALLPAPER_CROAGUNK,
    WALLPAPER_FRIENDS, // The one received as a gift from Walda's parents,
    WALLPAPER_COUNT
};
#define MAX_DEFAULT_WALLPAPER WALLPAPER_POKEATHLON

static const u16 sWallpaperPalettes_Forest[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/forest/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/forest/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Forest[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/forest/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Forest[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/forest/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_City[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/city/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/city/tiles.gbapal"),
};
static const u32 sWallpaperTiles_City[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/city/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_City[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/city/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Desert[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/desert/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/desert/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Desert[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/desert/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Desert[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/desert/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Savanna[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/savanna/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/savanna/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Savanna[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/savanna/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Savanna[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/savanna/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Crag[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/crag/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/crag/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Crag[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/crag/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Crag[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/crag/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Volcano[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/volcano/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/volcano/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Volcano[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/volcano/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Volcano[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/volcano/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Snow[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/snow/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/snow/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Snow[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/snow/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Snow[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/snow/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Cave[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/cave/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/cave/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Cave[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/cave/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Cave[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/cave/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Beach[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/beach/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/beach/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Beach[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/beach/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Beach[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/beach/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Seafloor[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/seafloor/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/seafloor/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Seafloor[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/seafloor/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Seafloor[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/seafloor/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_River[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/river/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/river/tiles.gbapal"),
};
static const u32 sWallpaperTiles_River[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/river/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_River[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/river/tilemap.bin.smolTM");
static const u16 sWallpaperPalettes_Sky[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/sky/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/sky/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Sky[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/sky/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Sky[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/sky/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_PolkaDot[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/polkadot/frame.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/polkadot/bg.gbapal"),
};
static const u32 sWallpaperTiles_PolkaDot[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/polkadot/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_PolkaDot[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/polkadot/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Pokecenter[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pokecenter/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pokecenter/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Pokecenter[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pokecenter/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Pokecenter[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pokecenter/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Machine[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/machine/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/machine/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Machine[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/machine/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Machine[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/machine/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Plain[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/plain/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/plain/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Plain[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/plain/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Plain[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/plain/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Space[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/space/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/space/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Space[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/space/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Space[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/space/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Backyard[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/backyard/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/backyard/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Backyard[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/backyard/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Backyard[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/backyard/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Nostalgic1[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/nostalgic1/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/nostalgic1/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Nostalgic1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/nostalgic1/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Nostalgic1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/nostalgic1/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Torchic[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/torchic/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/torchic/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Torchic[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/torchic/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Torchic[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/torchic/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Trio1[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/trio1/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/trio1/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Trio1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/trio1/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Trio1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/trio1/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Pikapika1[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pikapika1/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pikapika1/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Pikapika1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pikapika1/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Pikapika1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pikapika1/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_TimeAndSpace[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/timeandspace/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/timeandspace/tiles.gbapal"),
};
static const u32 sWallpaperTiles_TimeAndSpace[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/timeandspace/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_TimeAndSpace[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/timeandspace/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Galactic1[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/galactic1/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/galactic1/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Galactic1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/galactic1/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Galactic1[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/galactic1/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Distortion[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/distortion/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/distortion/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Distortion[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/distortion/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Distortion[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/distortion/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Contest[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/contest/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/contest/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Contest[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/contest/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Contest[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/contest/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Nostalgic2[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/nostalgic2/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/nostalgic2/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Nostalgic2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/nostalgic2/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Nostalgic2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/nostalgic2/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Croagunk[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/croagunk/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/croagunk/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Croagunk[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/croagunk/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Croagunk[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/croagunk/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Trio2[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/trio2/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/trio2/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Trio2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/trio2/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Trio2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/trio2/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Pikapika2[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pikapika2/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pikapika2/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Pikapika2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pikapika2/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Pikapika2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pikapika2/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Renegade[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/renegade/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/renegade/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Renegade[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/renegade/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Renegade[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/renegade/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Galactic2[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/galactic2/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/galactic2/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Galactic2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/galactic2/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Galactic2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/galactic2/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Heart[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/heart/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/heart/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Heart[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/heart/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Heart[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/heart/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Soul[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/soul/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/soul/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Soul[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/soul/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Soul[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/soul/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_BigBrother[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/bigbrother/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/bigbrother/tiles.gbapal"),
};
static const u32 sWallpaperTiles_BigBrother[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/bigbrother/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_BigBrother[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/bigbrother/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Pokeathlon[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pokeathlon/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pokeathlon/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Pokeathlon[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pokeathlon/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Pokeathlon[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pokeathlon/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Trio3[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/trio3/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/trio3/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Trio3[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/trio3/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Trio3[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/trio3/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_SpikyPika[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/spikypika/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/spikypika/tiles.gbapal"),
};
static const u32 sWallpaperTiles_SpikyPika[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/spikypika/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_SpikyPika[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/spikypika/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_KimonoGirl[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/kimonogirl/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/kimonogirl/tiles.gbapal"),
};
static const u32 sWallpaperTiles_KimonoGirl[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/kimonogirl/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_KimonoGirl[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/kimonogirl/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Revival[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/revival/tiles.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/revival/tiles.gbapal"),
};
static const u32 sWallpaperTiles_Revival[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/revival/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Revival[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/revival/tilemap.bin.smolTM");

// 12x18 tilemap
static const u32 sWallpaperTilemap_Unused[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/unused.bin");

// Shadow color, text color
static const u16 sBoxTitleColors[WALLPAPER_COUNT][2] =
{
    [WALLPAPER_HEART]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SOUL]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SPIKYPIKA]  = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_TRIO3]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_PIKAPIKA2]  = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KIMONOGIRL] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_TRIO1]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_RENEGADE]   = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_TRIO2]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_TIMEANDSPACE] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_NOSTALGIC2] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SEAFLOOR]   = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_NOSTALGIC1] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_DISTORTION] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SPACE]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_BACKYARD]   = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_TORCHIC]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_PIKAPIKA1]  = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CONTEST]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_REVIVAL]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CROAGUNK]   = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_FOREST]     = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CITY]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_DESERT]     = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SAVANNA]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CRAG]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_VOLCANO]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SNOW]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CAVE]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_BEACH]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_RIVER]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SKY]        = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_POLKADOT]   = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_POKECENTER] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_MACHINE]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_PLAIN]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_GALACTIC1]  = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_GALACTIC2]  = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_BIGBROTHER] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_POKEATHLON] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_FRIENDS]    = {RGB(7, 7, 7), RGB_WHITE},
};

#define WALLPAPER_ENTRY(name) {sWallpaperTiles_##name, sWallpaperTilemap_##name, sWallpaperPalettes_##name[0]}
// A few wallpapers are not defined in this file
#define WALLPAPER_ENTRY_G(name) {gWallpaperTiles_##name, gWallpaperTilemap_##name, gWallpaperPalettes_##name[0]}

static const struct Wallpaper sWallpapers[WALLPAPER_COUNT - 1] =
{
    [WALLPAPER_HEART]      = WALLPAPER_ENTRY(Heart),
    [WALLPAPER_SOUL]       = WALLPAPER_ENTRY(Soul),
    [WALLPAPER_SPIKYPIKA]  = WALLPAPER_ENTRY(SpikyPika),
    [WALLPAPER_TRIO3]      = WALLPAPER_ENTRY(Trio3),
    [WALLPAPER_PIKAPIKA2]  = WALLPAPER_ENTRY(Pikapika2),
    [WALLPAPER_KIMONOGIRL] = WALLPAPER_ENTRY(KimonoGirl),
    [WALLPAPER_TRIO1]      = WALLPAPER_ENTRY(Trio1),
    [WALLPAPER_RENEGADE]   = WALLPAPER_ENTRY(Renegade),
    [WALLPAPER_TRIO2]      = WALLPAPER_ENTRY(Trio2),
    [WALLPAPER_TIMEANDSPACE] = WALLPAPER_ENTRY(TimeAndSpace),
    [WALLPAPER_NOSTALGIC2] = WALLPAPER_ENTRY(Nostalgic2),
    [WALLPAPER_SEAFLOOR]   = WALLPAPER_ENTRY(Seafloor),
    [WALLPAPER_NOSTALGIC1] = WALLPAPER_ENTRY(Nostalgic1),
    [WALLPAPER_DISTORTION] = WALLPAPER_ENTRY(Distortion),
    [WALLPAPER_SPACE]      = WALLPAPER_ENTRY(Space),
    [WALLPAPER_BACKYARD]   = WALLPAPER_ENTRY(Backyard),
    [WALLPAPER_TORCHIC]    = WALLPAPER_ENTRY(Torchic),
    [WALLPAPER_PIKAPIKA1]  = WALLPAPER_ENTRY(Pikapika1),
    [WALLPAPER_CONTEST]    = WALLPAPER_ENTRY(Contest),
    [WALLPAPER_REVIVAL]    = WALLPAPER_ENTRY(Revival),
    [WALLPAPER_CROAGUNK]   = WALLPAPER_ENTRY(Croagunk),
    [WALLPAPER_FOREST]     = WALLPAPER_ENTRY(Forest),
    [WALLPAPER_CITY]       = WALLPAPER_ENTRY(City),
    [WALLPAPER_DESERT]     = WALLPAPER_ENTRY(Desert),
    [WALLPAPER_SAVANNA]    = WALLPAPER_ENTRY(Savanna),
    [WALLPAPER_CRAG]       = WALLPAPER_ENTRY(Crag),
    [WALLPAPER_VOLCANO]    = WALLPAPER_ENTRY(Volcano),
    [WALLPAPER_SNOW]       = WALLPAPER_ENTRY(Snow),
    [WALLPAPER_CAVE]       = WALLPAPER_ENTRY(Cave),
    [WALLPAPER_BEACH]      = WALLPAPER_ENTRY(Beach),
    [WALLPAPER_RIVER]      = WALLPAPER_ENTRY(River),
    [WALLPAPER_SKY]        = WALLPAPER_ENTRY(Sky),
    [WALLPAPER_POLKADOT]   = WALLPAPER_ENTRY(PolkaDot),
    [WALLPAPER_POKECENTER] = WALLPAPER_ENTRY(Pokecenter),
    [WALLPAPER_MACHINE]    = WALLPAPER_ENTRY(Machine),
    [WALLPAPER_PLAIN]      = WALLPAPER_ENTRY(Plain),
    [WALLPAPER_GALACTIC1]  = WALLPAPER_ENTRY(Galactic1),
    [WALLPAPER_GALACTIC2]  = WALLPAPER_ENTRY(Galactic2),
    [WALLPAPER_BIGBROTHER] = WALLPAPER_ENTRY(BigBrother),
    [WALLPAPER_POKEATHLON] = WALLPAPER_ENTRY(Pokeathlon),
};

static const u8 sArrow_Gfx[] = INCBIN_U8("graphics/pokemon_storage/arrow.4bpp");

static const u16 sWallpaperPalettes_Zigzagoon[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame1.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/zigzagoon/bg.gbapal"),
};
static const u32 sWallpaperTiles_Zigzagoon[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/zigzagoon/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Zigzagoon[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/zigzagoon/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Screen[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame1.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/screen/bg.gbapal"),
};
static const u32 sWallpaperTiles_Screen[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/screen/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Screen[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/screen/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Diagonal[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame1.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/diagonal/bg.gbapal"),
};
static const u32 sWallpaperTiles_Diagonal[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/diagonal/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Diagonal[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/diagonal/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Block[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/block/bg.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/block/bg.gbapal"),
};
static const u32 sWallpaperTiles_Block[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/block/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Block[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/block/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Pokecenter2[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pokecenter2/bg.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pokecenter2/bg.gbapal"),
};
static const u32 sWallpaperTiles_Pokecenter2[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/pokecenter2/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Pokecenter2[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pokecenter2/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Frame[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/frame/bg.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/frame/bg.gbapal"),
};
static const u32 sWallpaperTiles_Frame[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/frame/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Frame[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/frame/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Blank[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame1.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/zigzagoon/bg.gbapal"),
};
static const u32 sWallpaperTiles_Blank[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/blank/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Blank[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/blank/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Circles[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame2.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/circles/bg.gbapal"),
};
static const u32 sWallpaperTiles_Circles[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/circles/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Circles[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/circles/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Azumarill[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame2.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/azumarill/bg.gbapal"),
};
static const u32 sWallpaperTiles_Azumarill[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/azumarill/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Azumarill[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/azumarill/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Pikachu[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame2.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/pikachu/bg.gbapal"),
};
static const u32 sWallpaperTiles_Pikachu[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/pikachu/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Pikachu[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/pikachu/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Legendary[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame2.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/legendary/bg.gbapal"),
};
static const u32 sWallpaperTiles_Legendary[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/legendary/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Legendary[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/legendary/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Dusclops[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame2.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/dusclops/bg.gbapal"),
};
static const u32 sWallpaperTiles_Dusclops[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/dusclops/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Dusclops[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/dusclops/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Ludicolo[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame2.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/ludicolo/bg.gbapal"),
};
static const u32 sWallpaperTiles_Ludicolo[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/ludicolo/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Ludicolo[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/ludicolo/tilemap.bin.smolTM");

static const u16 sWallpaperPalettes_Whiscash[][16] =
{
    INCBIN_U16("graphics/pokemon_storage/wallpapers/friends_frame2.gbapal"),
    INCBIN_U16("graphics/pokemon_storage/wallpapers/whiscash/bg.gbapal"),
};
static const u32 sWallpaperTiles_Whiscash[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/whiscash/tiles.4bpp.smol");
static const u32 sWallpaperTilemap_Whiscash[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/whiscash/tilemap.bin.smolTM");

static const u32 sWallpaperIcon_Aqua[]         = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/aqua.4bpp.smol");
static const u32 sWallpaperIcon_Heart[]        = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/heart.4bpp.smol");
static const u32 sWallpaperIcon_FiveStar[]     = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/five_star.4bpp.smol");
static const u32 sWallpaperIcon_Brick[]        = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/brick.4bpp.smol");
static const u32 sWallpaperIcon_FourStar[]     = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/four_star.4bpp.smol");
static const u32 sWallpaperIcon_Asterisk[]     = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/asterisk.4bpp.smol");
static const u32 sWallpaperIcon_Dot[]          = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/dot.4bpp.smol");
static const u32 sWallpaperIcon_CrossJapan[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/cross_japan.4bpp.smol");
static const u32 sWallpaperIcon_LineCircle[]   = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/line_circle.4bpp.smol");
static const u32 sWallpaperIcon_PokeBall[]     = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/pokeball.4bpp.smol");
static const u32 sWallpaperIcon_Maze[]         = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/maze.4bpp.smol");
static const u32 sWallpaperIcon_Footprint[]    = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/footprint.4bpp.smol");
static const u32 sWallpaperIcon_BigAsterisk[]  = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/big_asterisk.4bpp.smol");
static const u32 sWallpaperIcon_Circle[]       = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/circle.4bpp.smol");
static const u32 sWallpaperIcon_Koffing[]      = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/koffing.4bpp.smol");
static const u32 sWallpaperIcon_Ribbon[]       = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/ribbon.4bpp.smol");
static const u32 sWallpaperIcon_BoltJapan[]    = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/bolt_japan.4bpp.smol");
static const u32 sWallpaperIcon_FourCircles[]  = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/four_circles.4bpp.smol");
static const u32 sWallpaperIcon_Lotad[]        = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/lotad.4bpp.smol");
static const u32 sWallpaperIcon_Crystal[]      = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/crystal.4bpp.smol");
static const u32 sWallpaperIcon_Pichu[]        = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/pichu.4bpp.smol");
static const u32 sWallpaperIcon_Diglett[]      = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/diglett.4bpp.smol");
static const u32 sWallpaperIcon_Luvdisc[]      = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/luvdisc.4bpp.smol");
static const u32 sWallpaperIcon_StarInCircle[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/star_in_circle.4bpp.smol");
static const u32 sWallpaperIcon_Spinda[]       = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/spinda.4bpp.smol");
static const u32 sWallpaperIcon_Latis[]        = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/latis.4bpp.smol");
static const u32 sWallpaperIcon_PlusleJapan[]  = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/plusle_japan.4bpp.smol");
static const u32 sWallpaperIcon_Minun[]        = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/minun.4bpp.smol");
static const u32 sWallpaperIcon_Togepi[]       = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/togepi.4bpp.smol");
static const u32 sWallpaperIcon_Magma[]        = INCBIN_U32("graphics/pokemon_storage/wallpapers/icons/magma.4bpp.smol");

static const struct Wallpaper sWaldaWallpapers[] =
{
    WALLPAPER_ENTRY(Zigzagoon),
    WALLPAPER_ENTRY(Screen),
    WALLPAPER_ENTRY_G(Horizontal),
    WALLPAPER_ENTRY(Diagonal),
    WALLPAPER_ENTRY(Block),
    WALLPAPER_ENTRY_G(Ribbon),
    WALLPAPER_ENTRY(Pokecenter2),
    WALLPAPER_ENTRY(Frame),
    WALLPAPER_ENTRY(Blank),
    WALLPAPER_ENTRY(Circles),
    WALLPAPER_ENTRY(Azumarill),
    WALLPAPER_ENTRY(Pikachu),
    WALLPAPER_ENTRY(Legendary),
    WALLPAPER_ENTRY(Dusclops),
    WALLPAPER_ENTRY(Ludicolo),
    WALLPAPER_ENTRY(Whiscash),
};

static const u32 *const sWaldaWallpaperIcons[] =
{
    sWallpaperIcon_Aqua,
    sWallpaperIcon_Heart,
    sWallpaperIcon_FiveStar,
    sWallpaperIcon_Brick,
    sWallpaperIcon_FourStar,
    sWallpaperIcon_Asterisk,
    sWallpaperIcon_Dot,
#if OW_PC_JAPAN_WALDA_ICONS == TRUE
    sWallpaperIcon_CrossJapan,
#else
    gWallpaperIcon_Cross,
#endif
    sWallpaperIcon_LineCircle,
    sWallpaperIcon_PokeBall,
    sWallpaperIcon_Maze,
    sWallpaperIcon_Footprint,
    sWallpaperIcon_BigAsterisk,
    sWallpaperIcon_Circle,
    sWallpaperIcon_Koffing,
    sWallpaperIcon_Ribbon,
#if OW_PC_JAPAN_WALDA_ICONS == TRUE
    sWallpaperIcon_BoltJapan,
#else
    gWallpaperIcon_Bolt,
#endif
    sWallpaperIcon_FourCircles,
    sWallpaperIcon_Lotad,
    sWallpaperIcon_Crystal,
    sWallpaperIcon_Pichu,
    sWallpaperIcon_Diglett,
    sWallpaperIcon_Luvdisc,
    sWallpaperIcon_StarInCircle,
    sWallpaperIcon_Spinda,
    sWallpaperIcon_Latis,
#if OW_PC_JAPAN_WALDA_ICONS == TRUE
    sWallpaperIcon_PlusleJapan,
#else
    gWallpaperIcon_Plusle,
#endif
    sWallpaperIcon_Minun,
    sWallpaperIcon_Togepi,
    sWallpaperIcon_Magma,
};
