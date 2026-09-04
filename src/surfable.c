#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_effect.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "field_weather.h"
#include "item.h"
#include "main.h"
#include "party_menu.h"
#include "sprite.h"
#include "surfable.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/moves.h"
#include "constants/species.h"
#include "config/surfable_species_enabled.h"

extern const struct OamData gObjectEventBaseOam_32x32;
extern const struct OamData gObjectEventBaseOam_64x64;
extern const struct SpriteTemplate *const gFieldEffectObjectTemplatePointers[];

extern void SynchronizeSurfAnim(struct ObjectEvent *playerObj, struct Sprite *sprite);
extern void SynchronizeSurfPosition(struct ObjectEvent *playerObj, struct Sprite *sprite);

static void CreateOverlaySprite(void);
static void UpdateSurfMonOverlay(struct Sprite *sprite);

struct RideablePokemon
{
    u16 species;
    u8 trainerPose;
    const u32 *shinyPic;
};

#define SURFABLE_POKEMON_DEFAULT_FRAME_COUNT 6
#define SURFABLE_POKEMON_MAX_FRAME_COUNT     8

#include "data/object_events/surfable/surfable_pokemon_graphics.h"
#include "data/object_events/surfable/surfable_pokemon.h"
#include "data/object_events/surfable/surfable_pokemon_pic_tables.h"
#include "data/object_events/surfable/surfable_pokemon_templates.h"

STATIC_ASSERT(ARRAY_COUNT(gSurfablePokemon) == ARRAY_COUNT(sSurfablePokemonPalettes), SurfSpeciesAndPalettesCountMismatch);
STATIC_ASSERT(ARRAY_COUNT(gSurfablePokemon) == ARRAY_COUNT(sSurfablePokemonShinyPalettes), SurfSpeciesAndShinyPalettesCountMismatch);
STATIC_ASSERT(ARRAY_COUNT(gSurfablePokemon) == ARRAY_COUNT(gSurfablePokemonOverworldSprites), SurfSpeciesAndSpritesCountMismatch);
STATIC_ASSERT(ARRAY_COUNT(gSurfablePokemon) == ARRAY_COUNT(gSurfablePokemonOverlaySprites), SurfSpeciesAndOverlaysCountMismatch);

static EWRAM_DATA u16 sCurrentSurfMon = {0};
static EWRAM_DATA u8 sCurrentSurfMonPartySlot = {0};
static EWRAM_DATA bool8 sUseShinySurfSheet = FALSE;
static EWRAM_DATA struct SpriteFrameImage sShinySurfFrames[SURFABLE_POKEMON_MAX_FRAME_COUNT] = {0};
static EWRAM_DATA struct SpriteFrameImage sShinySurfOverlayFrames[SURFABLE_POKEMON_MAX_FRAME_COUNT] = {0};

static u16 GetSurfablePokemonIndex(u16 species)
{
    if (species == SPECIES_PIKACHU_PARTNER || species == SPECIES_PIKACHU_STARTER)
        species = SPECIES_PIKACHU;

    for (u32 surfMon = 1; surfMon < ARRAY_COUNT(gSurfablePokemon); surfMon++)
    {
        if (species == gSurfablePokemon[surfMon].species)
            return surfMon;
    }

    return 0xFFFF;
}

static u16 GetSurfablePokemonIndexForMon(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);

#if P_MEGA_EVOLUTIONS
    if (CheckBagHasItem(ITEM_MEGA_RING, 1))
    {
        u32 megaSpecies = GetFormChangeTargetSpecies(mon, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM);

        if (megaSpecies == species)
            megaSpecies = GetFormChangeTargetSpecies(mon, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE);

        if (megaSpecies < NUM_SPECIES && GetSurfablePokemonIndex(megaSpecies) != 0xFFFF)
            species = megaSpecies;
    }
#endif

    return GetSurfablePokemonIndex(species);
}

u8 GetSurfablePokemonPartySlot(void)
{
    for (u32 partySlot = 0; partySlot < PARTY_SIZE; partySlot++)
    {
        if (GetMonData(&gPlayerParty[partySlot], MON_DATA_IS_EGG))
            continue;

        if (GetSurfablePokemonIndexForMon(&gPlayerParty[partySlot]) != 0xFFFF)
            return partySlot;
    }

    return PARTY_SIZE;
}

static u16 GetSurfablePokemonSprite(void)
{
    sCurrentSurfMonPartySlot = GetSurfablePokemonPartySlot();
    if (sCurrentSurfMonPartySlot == PARTY_SIZE)
        return 0xFFFF;

    return GetSurfablePokemonIndexForMon(&gPlayerParty[sCurrentSurfMonPartySlot]);
}

static void LoadSurfOverworldPalette(void)
{
    u8 paletteNum;

    if (IsMonShiny(&gPlayerParty[sCurrentSurfMonPartySlot]) == TRUE)
        paletteNum = LoadSpritePalette(&sSurfablePokemonShinyPalettes[sCurrentSurfMon]);
    else
        paletteNum = LoadSpritePalette(&sSurfablePokemonPalettes[sCurrentSurfMon]);

    if (paletteNum != 0xFF)
        UpdateSpritePaletteWithWeather(paletteNum, FALSE);
}

static bool8 SetupShinySurfFrames(void)
{
    const u8 *shinyPic = (const u8 *)gSurfablePokemon[sCurrentSurfMon].shinyPic;
    const struct SpriteFrameImage *normalFrames = gSurfablePokemonOverworldSprites[sCurrentSurfMon].images;
    const struct SpriteTemplate *overlayTemplate = &gSurfablePokemonOverlaySprites[sCurrentSurfMon];
    u32 frameSize = normalFrames[0].size;
    u32 frameCount = SURFABLE_POKEMON_DEFAULT_FRAME_COUNT;

    if (!IsMonShiny(&gPlayerParty[sCurrentSurfMonPartySlot]) || shinyPic == NULL)
        return FALSE;

    if (overlayTemplate->tileTag == TAG_NONE)
    {
        const u8 *normalPic = normalFrames[0].data;
        const u8 *normalOverlayPic = overlayTemplate->images[0].data;

        frameCount = (normalOverlayPic - normalPic) / frameSize;
    }
    if (frameCount > ARRAY_COUNT(sShinySurfFrames))
        return FALSE;

    for (u32 i = 0; i < frameCount; i++)
    {
        sShinySurfFrames[i].data = shinyPic + frameSize * i;
        sShinySurfFrames[i].size = frameSize;
        sShinySurfFrames[i].relativeFrames = FALSE;
        sShinySurfOverlayFrames[i].data = shinyPic + frameSize * (i + frameCount);
        sShinySurfOverlayFrames[i].size = frameSize;
        sShinySurfOverlayFrames[i].relativeFrames = FALSE;
    }

    return TRUE;
}

u32 CreateSurfablePokemonSprite(void)
{
    u8 spriteId;
    struct Sprite *sprite;

    SetSpritePosToOffsetMapCoords((s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1], 8, 8);

    sCurrentSurfMon = GetSurfablePokemonSprite();
    sUseShinySurfSheet = FALSE;
    if (sCurrentSurfMon != 0xFFFF)
    {
        sUseShinySurfSheet = SetupShinySurfFrames();
        LoadSurfOverworldPalette();
        if (gSurfablePokemonOverlaySprites[sCurrentSurfMon].tileTag == TAG_NONE)
            CreateOverlaySprite();

        spriteId = CreateSpriteAtEnd(&gSurfablePokemonOverworldSprites[sCurrentSurfMon], gFieldEffectArguments[0], gFieldEffectArguments[1], 0x96);
        if (sUseShinySurfSheet && spriteId != MAX_SPRITES)
            gSprites[spriteId].images = sShinySurfFrames;
    }
    else
    {
        // Create surf blob
        spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_SURF_BLOB], gFieldEffectArguments[0], gFieldEffectArguments[1], 0x96);
    }

    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->coordOffsetEnabled = TRUE;
        sprite->data[2] = gFieldEffectArguments[2];
        // Can use either gender's palette, so try to use the one that should be loaded
        if (sCurrentSurfMon == 0xFFFF)
            sprite->oam.paletteNum = LoadPlayerObjectEventPalette(gSaveBlock2Ptr->playerGender);
        sprite->data[3] = -1;
        sprite->data[6] = -1;
        sprite->data[7] = -1;
    }
    FieldEffectActiveListRemove(FLDEFF_SURF_BLOB);
    return spriteId;
}

static void CreateOverlaySprite(void)
{
    u8 overlaySprite;
    u8 subpriority;
    struct Sprite *sprite;

    subpriority = gSprites[gPlayerAvatar.spriteId].subpriority - 1;
    overlaySprite = CreateSpriteAtEnd(&gSurfablePokemonOverlaySprites[sCurrentSurfMon], gFieldEffectArguments[0], gFieldEffectArguments[1], subpriority);

    if (overlaySprite != MAX_SPRITES)
    {
        sprite = &gSprites[overlaySprite];
        if (sUseShinySurfSheet)
            sprite->images = sShinySurfOverlayFrames;
        sprite->coordOffsetEnabled = TRUE;
        sprite->data[2] = gFieldEffectArguments[2];
        sprite->data[3] = -1;
        sprite->data[6] = -1;
        sprite->data[7] = -1;
        sprite->oam.priority = 2;
    }
    SetSurfBlob_BobState(overlaySprite, BOB_PLAYER_AND_MON);
}

static void UpdateSurfMonOverlay(struct Sprite *sprite)
{
    struct ObjectEvent *playerObj;
    struct Sprite *surfSprite;
    u8 subpriority;

    playerObj = &gObjectEvents[gPlayerAvatar.objectEventId];
    surfSprite = &gSprites[playerObj->fieldEffectSpriteId];

    SynchronizeSurfAnim(playerObj, sprite);
    SynchronizeSurfPosition(playerObj, sprite);

    // Reset the subpriority for the overlay sprite so it shows on top of the player
    // We need this here so the subprio is correct after a screen transition (e.g. after exiting a battle)
    subpriority = gSprites[gPlayerAvatar.spriteId].subpriority - 1;
    sprite->subpriority = subpriority;

    sprite->x = surfSprite->x;
    sprite->y = surfSprite->y;
    sprite->x2 = surfSprite->x2;
    sprite->y2 = surfSprite->y2;
    sprite->oam.priority = surfSprite->oam.priority;

    if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_SURFING))
        DestroySprite(sprite);
}
