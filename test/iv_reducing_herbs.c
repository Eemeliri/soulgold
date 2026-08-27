#include "global.h"
#include "item.h"
#include "item_use.h"
#include "party_menu.h"
#include "pokemon.h"
#include "string_util.h"
#include "test/test.h"
#include "constants/item_effects.h"
#include "constants/items.h"

extern enum ItemEffectType BwPartyMenu_GetItemEffectType(enum Item item);
extern enum ItemEffectType HgssPartyMenu_GetItemEffectType(enum Item item);
extern enum ItemEffectType SwShPartyMenu_GetItemEffectType(enum Item item);

struct IVReducingHerb
{
    enum Item item;
    enum MonData ivField;
    enum MonData hyperTrainedField;
    enum ItemEffectType effectType;
    const u8 *name;
};

static const struct IVReducingHerb sIVReducingHerbs[] =
{
    { ITEM_WITHERED_HERB, MON_DATA_HP_IV,    MON_DATA_HYPER_TRAINED_HP,    ITEM_EFFECT_HP_IV_REDUCE,    COMPOUND_STRING("Withered Herb") },
    { ITEM_GRIMY_HERB,    MON_DATA_ATK_IV,   MON_DATA_HYPER_TRAINED_ATK,   ITEM_EFFECT_ATK_IV_REDUCE,   COMPOUND_STRING("Grimy Herb") },
    { ITEM_BRITTLE_HERB,  MON_DATA_DEF_IV,   MON_DATA_HYPER_TRAINED_DEF,   ITEM_EFFECT_DEF_IV_REDUCE,   COMPOUND_STRING("Brittle Herb") },
    { ITEM_GOOPY_HERB,    MON_DATA_SPEED_IV, MON_DATA_HYPER_TRAINED_SPEED, ITEM_EFFECT_SPEED_IV_REDUCE, COMPOUND_STRING("Goopy Herb") },
    { ITEM_DULL_HERB,     MON_DATA_SPATK_IV, MON_DATA_HYPER_TRAINED_SPATK, ITEM_EFFECT_SPATK_IV_REDUCE, COMPOUND_STRING("Dull Herb") },
    { ITEM_SOGGY_HERB,    MON_DATA_SPDEF_IV, MON_DATA_HYPER_TRAINED_SPDEF, ITEM_EFFECT_SPDEF_IV_REDUCE, COMPOUND_STRING("Soggy Herb") },
};

TEST("IV-reducing herbs lower only their matching IV by the selected quantity")
{
    u32 herbId, statId;

    for (herbId = 0; herbId < ARRAY_COUNT(sIVReducingHerbs); herbId++)
    {
        struct Pokemon mon;

        CreateMonWithIVs(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID, 10);
        EXPECT(!PokemonUseItemEffects(&mon, sIVReducingHerbs[herbId].item, 0, 0, FALSE, TRUE, 3));

        for (statId = 0; statId < NUM_STATS; statId++)
        {
            u32 expectedIV = (MON_DATA_HP_IV + statId == sIVReducingHerbs[herbId].ivField) ? 7 : 10;
            EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV + statId), expectedIV);
        }
    }
}

TEST("IV-reducing herbs clamp at zero and then have no effect")
{
    struct Pokemon mon;

    CreateMonWithIVs(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID, 2);
    EXPECT(!PokemonUseItemEffects(&mon, ITEM_GRIMY_HERB, 0, 0, FALSE, TRUE, 10));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 0);
    EXPECT(PokemonUseItemEffects(&mon, ITEM_GRIMY_HERB, 0, 0, FALSE, TRUE, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 0);
}

TEST("IV-reducing herb previews do not modify the Pokemon")
{
    struct Pokemon mon;

    CreateMonWithIVs(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID, 10);
    EXPECT(!PokemonUseItemEffects(&mon, ITEM_SOGGY_HERB, 0, 0, FALSE, FALSE, 5));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPDEF_IV), 10);
}

TEST("IV herbs force Hyper-Trained IVs to 31 before lowering them")
{
    u32 herbId;

    for (herbId = 0; herbId < ARRAY_COUNT(sIVReducingHerbs); herbId++)
    {
        bool32 hyperTrained = TRUE;
        struct Pokemon mon;

        CreateMonWithIVs(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID, 3);
        SetMonData(&mon, sIVReducingHerbs[herbId].hyperTrainedField, &hyperTrained);

        EXPECT(!PokemonUseItemEffects(&mon, sIVReducingHerbs[herbId].item, 0, 0, FALSE, TRUE, 2));
        EXPECT_EQ(GetMonData(&mon, sIVReducingHerbs[herbId].ivField), MAX_PER_STAT_IVS - 2);
        EXPECT(!GetMonData(&mon, sIVReducingHerbs[herbId].hyperTrainedField));
    }
}

TEST("IV herbs can replace Hyper Training when the underlying IV is zero")
{
    bool32 hyperTrained = TRUE;
    struct Pokemon mon;

    CreateMonWithIVs(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID, 0);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_ATK, &hyperTrained);

    EXPECT(!PokemonUseItemEffects(&mon, ITEM_GRIMY_HERB, 0, 0, FALSE, FALSE, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 0);
    EXPECT(GetMonData(&mon, MON_DATA_HYPER_TRAINED_ATK));

    EXPECT(!PokemonUseItemEffects(&mon, ITEM_GRIMY_HERB, 0, 0, FALSE, TRUE, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), MAX_PER_STAT_IVS - 1);
    EXPECT(!GetMonData(&mon, MON_DATA_HYPER_TRAINED_ATK));
}

TEST("Every party menu recognizes all six IV-reducing herbs")
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sIVReducingHerbs); i++)
    {
        EXPECT_EQ(BwPartyMenu_GetItemEffectType(sIVReducingHerbs[i].item), sIVReducingHerbs[i].effectType);
        EXPECT_EQ(HgssPartyMenu_GetItemEffectType(sIVReducingHerbs[i].item), sIVReducingHerbs[i].effectType);
        EXPECT_EQ(SwShPartyMenu_GetItemEffectType(sIVReducingHerbs[i].item), sIVReducingHerbs[i].effectType);
    }
}

TEST("IV-reducing herbs use EV berry prices and party-menu medicine behavor")
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sIVReducingHerbs); i++)
    {
        EXPECT_EQ(GetItemPrice(sIVReducingHerbs[i].item), GetItemPrice(ITEM_POMEG_BERRY));
        EXPECT_EQ(GetItemFieldFunc(sIVReducingHerbs[i].item), ItemUseOutOfBattle_Medicine);
        EXPECT_EQ(StringCompare(GetItemName(sIVReducingHerbs[i].item), sIVReducingHerbs[i].name), 0);
    }
}
