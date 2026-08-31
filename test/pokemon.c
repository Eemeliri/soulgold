#include "global.h"
#include "achievements.h"
#include "battle.h"
#include "data.h"
#include "egg_hatch.h"
#include "event_data.h"
#include "item_menu.h"
#include "load_save.h"
#include "move.h"
#include "new_game.h"
#include "ow_synchronize.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "string_util.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/characters.h"
#include "constants/daycare.h"
#include "constants/move_relearner.h"
#include "constants/songs.h"
#include "constants/vars.h"

TEST("Cute Charm does not request an impossible wild Pokemon gender")
{
    CreateMon(&gPlayerParty[0], SPECIES_NINETALES_ALOLA, 100, 0, OTID_STRUCT_PLAYER_ID);

    ASSUME(GetMonGender(&gPlayerParty[0]) == MON_FEMALE);
    ASSUME(MonHasTrait(&gPlayerParty[0], ABILITY_CUTE_CHARM));

    EXPECT_EQ(GetSynchronizedGender(WILDMON_ORIGIN, SPECIES_CHANSEY), MON_GENDER_RANDOM);
    EXPECT_EQ(GetSynchronizedGender(WILDMON_ORIGIN, SPECIES_TAUROS), MON_GENDER_RANDOM);
    EXPECT_EQ(GetSynchronizedGender(WILDMON_ORIGIN, SPECIES_MAGNEMITE), MON_GENDER_RANDOM);
}

TEST("Facility BGM overrides exclude Pyramid and Pike wild encounters")
{
    u32 savedBattleTypeFlags = gBattleTypeFlags;
    u16 savedBgmChoice = VarGet(VAR_BATTLE_FACILITY_BGM);

    // First selectable track after Default and Random.
    VarSet(VAR_BATTLE_FACILITY_BGM, 2);

    gBattleTypeFlags = BATTLE_TYPE_PYRAMID;
    EXPECT_EQ(GetBattleBGM(), MUS_HG_VS_WILD);

    gBattleTypeFlags = BATTLE_TYPE_PIKE;
    EXPECT_EQ(GetBattleBGM(), MUS_HG_VS_WILD);

    gBattleTypeFlags = BATTLE_TYPE_PYRAMID | BATTLE_TYPE_TRAINER;
    EXPECT_EQ(GetBattleBGM(), MUS_VS_TRAINER);

    gBattleTypeFlags = savedBattleTypeFlags;
    VarSet(VAR_BATTLE_FACILITY_BGM, savedBgmChoice);
}

TEST("Nature independent from Hidden Nature")
{
    u32 i, j, nature = 0, hiddenNature = 0;
    struct Pokemon mon;
    for (i = 0; i < NUM_NATURES; i++)
    {
        for (j = 0; j < NUM_NATURES; j++)
        {
            PARAMETRIZE { nature = i; hiddenNature = j; }
        }
    }
    u32 species = SPECIES_WOBBUFFET;
    u32 personality = GetMonPersonality(species, MON_GENDER_RANDOM, nature, RANDOM_UNOWN_LETTER);
    CreateMon(&mon, species, 100, personality, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_HIDDEN_NATURE, &hiddenNature);
    EXPECT_EQ(GetNature(&mon), nature);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HIDDEN_NATURE), hiddenNature);
}

TEST("BoxPokemon secure data is plaintext and fixed-order")
{
    struct Pokemon mon;
    enum Item item = ITEM_LEFTOVERS;
    u32 species;
    u32 heldItem;

    CreateMon(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    species = mon.box.secure.species;
    heldItem = mon.box.secure.heldItem;

    EXPECT_EQ(species, SPECIES_WOBBUFFET);
    EXPECT_EQ(heldItem, ITEM_LEFTOVERS);
}

TEST("Facility Sketch cleanup preserves taught moves on other species")
{
    struct Pokemon savedMon;
    struct Pokemon facilityMon;

    CreateMon(&savedMon, SPECIES_RAYQUAZA, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&savedMon, MOVE_EARTHQUAKE, 0);
    facilityMon = savedMon;
    SetMonMoveSlot(&facilityMon, MOVE_EARTH_POWER, 0);

    RestoreFacilitySketchedMoves(&savedMon, &facilityMon);

    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_MOVE1), MOVE_EARTH_POWER);
}

#if P_FAMILY_SMEARGLE
TEST("Facility Sketch cleanup restores copied moves without changing other moves")
{
    struct Pokemon savedMon;
    struct Pokemon facilityMon;

    CreateMon(&savedMon, SPECIES_SMEARGLE, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&savedMon, MOVE_SKETCH, 0);
    SetMonMoveSlot(&savedMon, MOVE_TACKLE, 1);
    facilityMon = savedMon;
    SetMonMoveSlot(&facilityMon, MOVE_EARTH_POWER, 0);

    RestoreFacilitySketchedMoves(&savedMon, &facilityMon);

    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_MOVE1), MOVE_SKETCH);
    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_MOVE2), MOVE_TACKLE);
}

TEST("Facility Sketch cleanup handles reordered Sketch slots")
{
    enum Move reorderedSketchMove;
    struct Pokemon savedMon;
    struct Pokemon facilityMon;

    PARAMETRIZE { reorderedSketchMove = MOVE_SKETCH; }
    PARAMETRIZE { reorderedSketchMove = MOVE_EARTHQUAKE; }

    CreateMon(&savedMon, SPECIES_SMEARGLE, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&savedMon, MOVE_SKETCH, 0);
    SetMonMoveSlot(&savedMon, MOVE_TACKLE, 1);
    facilityMon = savedMon;
    SetMonMoveSlot(&facilityMon, MOVE_TACKLE, 0);
    SetMonMoveSlot(&facilityMon, reorderedSketchMove, 1);

    RestoreFacilitySketchedMoves(&savedMon, &facilityMon);

    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_MOVE1), MOVE_TACKLE);
    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_MOVE2), MOVE_SKETCH);
}

TEST("Facility Sketch cleanup preserves PP of reordered Sketch")
{
    struct Pokemon savedMon;
    struct Pokemon facilityMon;
    u32 pp = 0;

    CreateMon(&savedMon, SPECIES_SMEARGLE, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&savedMon, MOVE_SKETCH, 0);
    SetMonMoveSlot(&savedMon, MOVE_TACKLE, 1);
    facilityMon = savedMon;
    SetMonMoveSlot(&facilityMon, MOVE_TACKLE, 0);
    SetMonMoveSlot(&facilityMon, MOVE_SKETCH, 1);
    SetMonData(&facilityMon, MON_DATA_PP2, &pp);

    RestoreFacilitySketchedMoves(&savedMon, &facilityMon);

    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_MOVE1), MOVE_TACKLE);
    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_MOVE2), MOVE_SKETCH);
    EXPECT_EQ(GetMonData(&facilityMon, MON_DATA_PP2), 0);
}
#endif

TEST("Updating personality does not move BoxPokemon secure data")
{
    struct Pokemon mon;
    u32 oldPersonality = 0;
    u32 newPersonality = 5;
    enum Item item = ITEM_LEFTOVERS;

    CreateMon(&mon, SPECIES_WOBBUFFET, 50, oldPersonality, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    SetMonMoveSlot(&mon, MOVE_SPLASH, 0);
    UpdateMonPersonality(&mon.box, newPersonality);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), newPersonality);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_WOBBUFFET);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), MOVE_SPLASH);
}

TEST("Setting a nickname terminates unused nickname storage")
{
    struct Pokemon mon;
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u8 storedNickname[POKEMON_NAME_LENGTH + 1];

    CreateMon(&mon, SPECIES_ANNIHILAPE, 50, 0, OTID_STRUCT_PLAYER_ID);
    StringCopy(nickname, COMPOUND_STRING("Annihilape"));
    nickname[11] = CHAR_G;
    SetMonData(&mon, MON_DATA_NICKNAME, nickname);
    GetMonData(&mon, MON_DATA_NICKNAME, storedNickname);

    EXPECT_EQ(StringCompare(storedNickname, COMPOUND_STRING("Annihilape")), 0);
    EXPECT_EQ(storedNickname[11], EOS);
}

TEST("Primal Dialga is independent of nickname form changes")
{
    struct Pokemon mon;
    u8 nickname[POKEMON_NAME_LENGTH + 1];

    StringCopy(nickname, COMPOUND_STRING("Primal"));
    CreateMon(&mon, SPECIES_DIALGA, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_NICKNAME, nickname);
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_NICKNAME));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_DIALGA);

    StringCopy(nickname, COMPOUND_STRING("Dialga"));
    CreateMon(&mon, SPECIES_DIALGA_PRIMAL, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_NICKNAME, nickname);
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_NICKNAME));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_DIALGA_PRIMAL);
}

TEST("Lugia and Shadow Lugia are independent of nickname form changes")
{
    struct Pokemon mon;
    u8 nickname[POKEMON_NAME_LENGTH + 1];

    StringCopy(nickname, COMPOUND_STRING("XD001"));
    CreateMon(&mon, SPECIES_LUGIA, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_NICKNAME, nickname);
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_NICKNAME));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_LUGIA);

    StringCopy(nickname, COMPOUND_STRING("Lugia"));
    CreateMon(&mon, SPECIES_LUGIA_SHADOW, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_NICKNAME, nickname);
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_NICKNAME));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_LUGIA_SHADOW);
}

TEST("Pokemon save bit repack preserves extended met location and modern fateful encounter")
{
    struct Pokemon mon;
    u16 metLocation = 0x7FFF;
    u8 abilityNum = 2;
    u8 enabled = TRUE;

    CreateMon(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_MET_LOCATION, &metLocation);
    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilityNum);
    SetMonData(&mon, MON_DATA_MODERN_FATEFUL_ENCOUNTER, &enabled);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_MET_LOCATION), metLocation);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ABILITY_NUM), abilityNum);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MODERN_FATEFUL_ENCOUNTER), enabled);
}

TEST("Custom event boss moves replace every move slot and preserve event metadata")
{
    gSpecialVar_0x8004 = SPECIES_DARKRAI;
    gSpecialVar_0x8005 = 50;
    gSpecialVar_0x8006 = ITEM_NONE;
    CreateEnemyEventMon();

    RUN_OVERWORLD_SCRIPT(
        seteventmonmoves MOVE_DARK_PULSE, MOVE_ICE_BEAM, MOVE_HYPNOSIS, MOVE_NONE;
    );

    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MODERN_FATEFUL_ENCOUNTER), TRUE);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), MOVE_DARK_PULSE);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE2), MOVE_ICE_BEAM);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE3), MOVE_HYPNOSIS);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE4), MOVE_NONE);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_PP1), GetMovePP(MOVE_DARK_PULSE));
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_PP2), GetMovePP(MOVE_ICE_BEAM));
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_PP3), GetMovePP(MOVE_HYPNOSIS));
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_PP4), 0);
}

TEST("Terastallization type defaults to primary or secondary type")
{
    u32 i;
    enum Type teraType;
    struct Pokemon mon;
    for (i = 0; i < 128; i++) PARAMETRIZE {}
    CreateRandomMonWithIVs(&mon, SPECIES_PIDGEY, 100, 0);
    teraType = GetMonData(&mon, MON_DATA_TERA_TYPE);
    EXPECT(teraType == GetSpeciesType(SPECIES_PIDGEY, 0)
        || teraType == GetSpeciesType(SPECIES_PIDGEY, 1));
}

TEST("Terastallization type can be set to any type except TYPE_NONE")
{
    u32 i;
    enum Type teraType;
    struct Pokemon mon;
    for (i = 1; i < NUMBER_OF_MON_TYPES; i++)
    {
        PARAMETRIZE { teraType = i; }
    }
    CreateRandomMonWithIVs(&mon, SPECIES_WOBBUFFET, 100, 0);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &teraType);
    EXPECT_EQ(teraType, GetMonData(&mon, MON_DATA_TERA_TYPE));
}

TEST("Outside-battle dynamic move types use the displayed Pokemon's traits")
{
    struct Pokemon mon;
    enum Item item = ITEM_FAIRYTITE;
    enum Ability savedBattlerAbility = gBattleMons[0].ability;

    ASSUME(GetMoveType(MOVE_HYPER_VOICE) == TYPE_NORMAL);

    CreateMon(&mon, SPECIES_GARDEVOIR, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    gBattleMons[0].ability = ABILITY_PIXILATE;
    EXPECT_EQ(CheckDynamicMoveType(&mon, MOVE_HYPER_VOICE, 0, MON_OUTSIDE_BATTLE), TYPE_NORMAL);

    CreateMon(&mon, SPECIES_GARDEVOIR_MEGA, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(CheckDynamicMoveType(&mon, MOVE_HYPER_VOICE, 0, MON_OUTSIDE_BATTLE), TYPE_FAIRY);

    gBattleMons[0].ability = savedBattlerAbility;
}

TEST("Outside-battle Natural Gift uses the held berry's type")
{
    struct Pokemon mon;
    enum Item item = ITEM_CHERI_BERRY;

    ASSUME(GetMoveEffect(MOVE_NATURAL_GIFT) == EFFECT_NATURAL_GIFT);

    CreateMon(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    EXPECT_EQ(CheckDynamicMoveType(&mon, MOVE_NATURAL_GIFT, 0, MON_OUTSIDE_BATTLE), TYPE_FIRE);
}

TEST("Gracidea toggles Shaymin form without automatic reversion")
{
    struct Pokemon mon;
    u32 status = STATUS1_FREEZE;

    CreateMon(&mon, SPECIES_SHAYMIN_LAND, 50, 0, OTID_STRUCT_PLAYER_ID);
    gSpecialVar_ItemId = ITEM_GRACIDEA;

    EXPECT(TryFormChange(&mon, FORM_CHANGE_ITEM_USE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_SHAYMIN_SKY);

    SetMonData(&mon, MON_DATA_STATUS, &status);
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_STATUS));
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_TIME_OF_DAY));
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_WITHDRAW));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_SHAYMIN_SKY);

    EXPECT(TryFormChange(&mon, FORM_CHANGE_ITEM_USE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_SHAYMIN_LAND);
}

TEST("Prison Bottle toggles Hoopa form without automatic reversion")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_HOOPA_CONFINED, 50, 0, OTID_STRUCT_PLAYER_ID);
    gSpecialVar_ItemId = ITEM_PRISON_BOTTLE;

    EXPECT(TryFormChange(&mon, FORM_CHANGE_ITEM_USE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_HOOPA_UNBOUND);

    EXPECT(!TryFormChange(&mon, FORM_CHANGE_WITHDRAW));
    EXPECT(!TryFormChange(&mon, FORM_CHANGE_DAYS_PASSED));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_HOOPA_UNBOUND);

    EXPECT(TryFormChange(&mon, FORM_CHANGE_ITEM_USE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_HOOPA_CONFINED);
}

TEST("Terastallization type is reset to the default types when setting Tera Type back to TYPE_NONE")
{
    u32 i;
    enum Type teraType, typeNone;
    struct Pokemon mon;
    for (i = 1; i < NUMBER_OF_MON_TYPES; i++)
    {
        PARAMETRIZE { teraType = i; typeNone = TYPE_NONE; }
    }
    CreateRandomMonWithIVs(&mon, SPECIES_PIDGEY, 100, 0);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &teraType);
    EXPECT_EQ(teraType, GetMonData(&mon, MON_DATA_TERA_TYPE));
    if (typeNone == TYPE_NONE)
        typeNone = GetTeraTypeFromPersonality(&mon);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &typeNone);
    typeNone = GetMonData(&mon, MON_DATA_TERA_TYPE);
    EXPECT(typeNone == GetSpeciesType(SPECIES_PIDGEY, 0)
        || typeNone == GetSpeciesType(SPECIES_PIDGEY, 1));
}

TEST("Shininess independent from PID and OTID")
{
    u32 pid, otId, data;
    bool32 isShiny;
    struct Pokemon mon;
    PARAMETRIZE { pid = 0; otId = 0; }
    CreateMon(&mon, SPECIES_WOBBUFFET, 100, pid, OTID_STRUCT_PRESET(otId));
    isShiny = IsMonShiny(&mon);
    data = !isShiny;
    SetMonData(&mon, MON_DATA_IS_SHINY, &data);
    EXPECT_EQ(pid, GetMonData(&mon, MON_DATA_PERSONALITY));
    EXPECT_EQ(otId, GetMonData(&mon, MON_DATA_OT_ID));
    EXPECT_EQ(!isShiny, GetMonData(&mon, MON_DATA_IS_SHINY));
}

TEST("Shininess set on an Egg persists after hatching")
{
    u32 personality = SHINY_ODDS;
    u32 trainerId = 0;
    bool32 isShiny = TRUE;
    bool8 isEgg = TRUE;

    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
    CreateMon(&gPlayerParty[0], SPECIES_TOGEPI, EGG_HATCH_LEVEL, personality, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &isEgg);
    SetMonData(&gPlayerParty[0], MON_DATA_IS_SHINY, &isShiny);

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_IS_SHINY), TRUE);

    gSpecialVar_0x8004 = 0;
    ScriptHatchMon();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG), FALSE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_IS_SHINY), TRUE);
}

TEST("Ability slot set on an Egg persists after hatching")
{
    u8 abilityNum = NUM_NORMAL_ABILITY_SLOTS;
    bool8 isEgg = TRUE;

    ASSUME(P_FAMILY_DRILBUR == TRUE);
    ASSUME(GetSpeciesAbility(SPECIES_DRILBUR, abilityNum) == ABILITY_MOLD_BREAKER);

    CreateMon(&gPlayerParty[0], SPECIES_DRILBUR, EGG_HATCH_LEVEL, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &isEgg);
    SetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM, &abilityNum);

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM), abilityNum);

    gSpecialVar_0x8004 = 0;
    ScriptHatchMon();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM), abilityNum);
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), ABILITY_MOLD_BREAKER);
}

TEST("Egg sprite and icon palettes reflect shininess")
{
    EXPECT(GetMonSpritePalFromSpeciesIsEgg(SPECIES_TOGEPI, FALSE, FALSE, TRUE) == gSpeciesInfo[SPECIES_EGG].palette);
    EXPECT(GetMonSpritePalFromSpeciesIsEgg(SPECIES_TOGEPI, TRUE, FALSE, TRUE) == gSpeciesInfo[SPECIES_EGG].shinyPalette);
    EXPECT(GetIconPaletteIsEgg(SPECIES_TOGEPI, FALSE, 0, TRUE) == gSpeciesInfo[SPECIES_EGG].iconPalette);
    EXPECT(GetIconPaletteIsEgg(SPECIES_TOGEPI, TRUE, 0, TRUE) == gSpeciesInfo[SPECIES_EGG].shinyIconPalette);

#if P_FAMILY_MANAPHY
    EXPECT(GetMonSpritePalFromSpeciesIsEgg(SPECIES_MANAPHY, FALSE, FALSE, TRUE) == gEggDatas[EGG_ID_MANAPHY].eggPalette);
    EXPECT(GetMonSpritePalFromSpeciesIsEgg(SPECIES_MANAPHY, TRUE, FALSE, TRUE) == gEggDatas[EGG_ID_MANAPHY].eggShinyPalette);
    EXPECT(GetIconPaletteIsEgg(SPECIES_MANAPHY, FALSE, 0, TRUE) == gEggDatas[EGG_ID_MANAPHY].eggIconPalette);
    EXPECT(GetIconPaletteIsEgg(SPECIES_MANAPHY, TRUE, 0, TRUE) == gEggDatas[EGG_ID_MANAPHY].eggShinyIconPalette);
#endif
}

TEST("Hatching Jirachi unlocks its achievement")
{
    bool8 isEgg = TRUE;

    CreateMon(&gPlayerParty[0], SPECIES_JIRACHI, EGG_HATCH_LEVEL, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &isEgg);
    gSpecialVar_0x8004 = 0;

    ScriptHatchMon();

    EXPECT(Achievement_IsUnlocked(ACH_OBTAIN_JIRACHI));
}

TEST("Hyper Training increases stats without affecting IVs")
{
    u32 data, hp, atk, def, speed, spatk, spdef, friendship = 0;
    struct Pokemon mon;
    CreateMonWithIVs(&mon, SPECIES_WOBBUFFET, 100, 0, OTID_STRUCT_PRESET(0), 3);
    // Consider B_FRIENDSHIP_BOOST.
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    CalculateMonStats(&mon);

    hp = GetMonData(&mon, MON_DATA_HP);
    atk = GetMonData(&mon, MON_DATA_ATK);
    def = GetMonData(&mon, MON_DATA_DEF);
    speed = GetMonData(&mon, MON_DATA_SPEED);
    spatk = GetMonData(&mon, MON_DATA_SPATK);
    spdef = GetMonData(&mon, MON_DATA_SPDEF);

    data = TRUE;
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_HP, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_ATK, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_DEF, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_SPEED, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_SPATK, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_SPDEF, &data);
    CalculateMonStats(&mon);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_DEF_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPATK_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPDEF_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_IV), 3);

    EXPECT_EQ(hp - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_HP));
    EXPECT_EQ(atk - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_ATK));
    EXPECT_EQ(def - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_DEF));
    EXPECT_EQ(speed - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_SPEED));
    EXPECT_EQ(spatk - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_SPATK));
    EXPECT_EQ(spdef - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_SPDEF));
}

TEST("Status1 round-trips through BoxPokemon")
{
    u32 status1;
    struct Pokemon mon1, mon2;
    PARAMETRIZE { status1 = STATUS1_NONE; }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(1); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(2); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(3); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(4); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(5); }
    PARAMETRIZE { status1 = STATUS1_POISON; }
    PARAMETRIZE { status1 = STATUS1_BURN; }
    PARAMETRIZE { status1 = STATUS1_FREEZE; }
    PARAMETRIZE { status1 = STATUS1_PARALYSIS; }
    PARAMETRIZE { status1 = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status1 = STATUS1_FROSTBITE; }
    CreateRandomMonWithIVs(&mon1, SPECIES_WOBBUFFET, 100, 0);
    SetMonData(&mon1, MON_DATA_STATUS, &status1);
    BoxMonToMon(&mon1.box, &mon2);
    EXPECT_EQ(GetMonData(&mon2, MON_DATA_STATUS), status1);
}

TEST("canhypertrain/hypertrain affect MON_DATA_HYPER_TRAINED_* and recalculate stats")
{
    u32 atk, friendship = 0;
    CreateRandomMonWithIVs(&gPlayerParty[0], SPECIES_WOBBUFFET, 100, 0);

    // Consider B_FRIENDSHIP_BOOST.
    SetMonData(&gPlayerParty[0], MON_DATA_FRIENDSHIP, &friendship);
    CalculateMonStats(&gPlayerParty[0]);

    atk = GetMonData(&gPlayerParty[0], MON_DATA_ATK);

    RUN_OVERWORLD_SCRIPT(
        canhypertrain STAT_ATK, 0;
    );
    EXPECT(VarGet(VAR_RESULT));

    RUN_OVERWORLD_SCRIPT(
        hypertrain STAT_ATK, 0;
        canhypertrain STAT_ATK, 0;
    );
    EXPECT(GetMonData(&gPlayerParty[0], MON_DATA_HYPER_TRAINED_ATK));
    EXPECT_EQ(atk + 31, GetMonData(&gPlayerParty[0], MON_DATA_ATK));
    EXPECT(!VarGet(VAR_RESULT));
}

TEST("hasgigantamaxfactor/togglegigantamaxfactor affect MON_DATA_GIGANTAMAX_FACTOR")
{
    CreateRandomMonWithIVs(&gPlayerParty[0], SPECIES_WOBBUFFET, 100, 0);

    RUN_OVERWORLD_SCRIPT(
        hasgigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));

    RUN_OVERWORLD_SCRIPT(
        togglegigantamaxfactor 0;
        hasgigantamaxfactor 0;
    );
    EXPECT(VarGet(VAR_RESULT));
    EXPECT(GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR));

    RUN_OVERWORLD_SCRIPT(
        togglegigantamaxfactor 0;
        hasgigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));
    EXPECT(!GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR));
}

TEST("togglegigantamaxfactor fails for Melmetal")
{
    CreateRandomMonWithIVs(&gPlayerParty[0], SPECIES_MELMETAL, 100, 0);

    RUN_OVERWORLD_SCRIPT(
        hasgigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));

    RUN_OVERWORLD_SCRIPT(
        togglegigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));
    EXPECT(!GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR));
}

TEST("givemon [simple]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_WOBBUFFET, 100;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_WOBBUFFET);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
}

TEST("givemon respects perfectIVCount")
{
    ZeroPlayerPartyMons();
    u32 perfectIVs[6] = {0};

    ASSUME(gSpeciesInfo[SPECIES_MEW].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_CELEBI].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_JIRACHI].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_MANAPHY].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_VICTINI].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_DIANCIE].perfectIVCount == 3);

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_MEW, 100;
        givemon SPECIES_CELEBI, 100;
        givemon SPECIES_JIRACHI, 100;
        givemon SPECIES_MANAPHY, 100;
        givemon SPECIES_VICTINI, 100;
        givemon SPECIES_DIANCIE, 100;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_MEW);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_CELEBI);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_SPECIES), SPECIES_JIRACHI);
    EXPECT_EQ(GetMonData(&gPlayerParty[3], MON_DATA_SPECIES), SPECIES_MANAPHY);
    EXPECT_EQ(GetMonData(&gPlayerParty[4], MON_DATA_SPECIES), SPECIES_VICTINI);
    EXPECT_EQ(GetMonData(&gPlayerParty[5], MON_DATA_SPECIES), SPECIES_DIANCIE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[3], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[4], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[5], MON_DATA_LEVEL), 100);
    for (u32 j = 0; j < 6; j++)
    {
        for (u32 k = 0; k < NUM_STATS; k++)
        {
            if (GetMonData(&gPlayerParty[j], MON_DATA_HP_IV + k) == MAX_PER_STAT_IVS)
                perfectIVs[j]++;
        }
        EXPECT_GE(perfectIVs[j], 3);
    }
}

TEST("givemon respects perfectIVCount but does overwrite fixed IVs (1)")
{
    ZeroPlayerPartyMons();

    ASSUME(gSpeciesInfo[SPECIES_MEW].perfectIVCount == 3);
    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_MEW, 100, hpIv=7, atkIv=8, defIv=9, speedIv=10, spAtkIv=11, spDefIv=12
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_IV), 7);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_IV), 8);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_IV), 9);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_IV), 10);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_IV), 11);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_IV), 12);
}

TEST("givemon respects perfectIVCount but does overwrite fixed IVs (2)")
{
    ZeroPlayerPartyMons();

    ASSUME(gSpeciesInfo[SPECIES_MEW].perfectIVCount == 3);
    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_MEW, 100, hpIv=7, atkIv=8, defIv=9
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_IV), 7);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_IV), 8);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_IV), 9);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_IV), MAX_PER_STAT_IVS);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_IV), MAX_PER_STAT_IVS);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_IV), MAX_PER_STAT_IVS);
}

TEST("givemon respects FORM_CHANGE_ITEM_HOLD")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_ARCEUS_NORMAL, 100, item=ITEM_ZAP_PLATE;
        givemon SPECIES_ARCEUS_GRASS, 100, item=ITEM_ZAP_PLATE;
        givemon SPECIES_ARCEUS_ELECTRIC, 100, item=ITEM_ZAP_PLATE;
        givemon SPECIES_GIRATINA_ORIGIN, 100, item=ITEM_POTION;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_ARCEUS_ELECTRIC);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_ARCEUS_ELECTRIC);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_SPECIES), SPECIES_ARCEUS_ELECTRIC);
    EXPECT_EQ(GetMonData(&gPlayerParty[3], MON_DATA_SPECIES), SPECIES_GIRATINA_ALTERED);
}

TEST("givemon [moves]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_WOBBUFFET, 100, move1=MOVE_SCRATCH, move2=MOVE_SPLASH, move3=MOVE_NONE, move4=MOVE_NONE;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_WOBBUFFET);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1), MOVE_SCRATCH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE2), MOVE_SPLASH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE3), MOVE_NONE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE4), MOVE_NONE);
}

TEST("givemon [moves (default)]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_PYUKUMUKU, 100, move1=MOVE_DEFAULT, move2=MOVE_DEFAULT, move3=MOVE_DEFAULT;
    );

    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(SPECIES_PYUKUMUKU);
    u32 learnsetLength;
    for (learnsetLength = 0; learnset[learnsetLength].move != LEVEL_UP_MOVE_END; learnsetLength++)
    {
        ; // we just want to get length of the learnset array
    }
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_PYUKUMUKU);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1), learnset[learnsetLength - 4].move);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE2), learnset[learnsetLength - 3].move);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE3), learnset[learnsetLength - 2].move);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE4), learnset[learnsetLength - 1].move);
}

TEST("givemon [all]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_WOBBUFFET, 100, item=ITEM_LEFTOVERS, ball=BALL_MASTER, nature=NATURE_BOLD, abilityNum=2, gender=MON_MALE, hpEv=1, atkEv=2, defEv=3, speedEv=4, spAtkEv=5, spDefEv=6, hpIv=7, atkIv=8, defIv=9, speedIv=10, spAtkIv=11, spDefIv=12, move1=MOVE_SCRATCH, move2=MOVE_SPLASH, move3=MOVE_CELEBRATE, move4=MOVE_EXPLOSION, shinyMode=SHINY_MODE_ALWAYS, gmaxFactor=TRUE, teraType=TYPE_FIRE;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_WOBBUFFET);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_POKEBALL), BALL_MASTER);
    EXPECT_EQ(GetNature(&gPlayerParty[0]), NATURE_BOLD);
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), GetSpeciesAbility(SPECIES_WOBBUFFET, 2));
    EXPECT_EQ(GetMonGender(&gPlayerParty[0]), MON_MALE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 1);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_EV), 2);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_EV), 3);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_EV), 4);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_EV), 5);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_EV), 6);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_IV), 7);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_IV), 8);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_IV), 9);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_IV), 10);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_IV), 11);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_IV), 12);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1), MOVE_SCRATCH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE2), MOVE_SPLASH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE3), MOVE_CELEBRATE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE4), MOVE_EXPLOSION);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_IS_SHINY), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_TERA_TYPE), TYPE_FIRE);
}

TEST("givemon [vars]")
{
    ZeroPlayerPartyMons();

    VarSet(VAR_TEMP_C, SPECIES_WOBBUFFET);
    VarSet(VAR_TEMP_D, 100);
    VarSet(VAR_0x8000, ITEM_LEFTOVERS);
    VarSet(VAR_0x8001, BALL_MASTER);
    VarSet(VAR_0x8002, NATURE_BOLD);
    VarSet(VAR_0x8003, 2);
    VarSet(VAR_0x8004, MON_MALE);
    VarSet(VAR_0x8005, 1);
    VarSet(VAR_0x8006, 2);
    VarSet(VAR_0x8007, 3);
    VarSet(VAR_0x8008, 4);
    VarSet(VAR_0x8009, 5);
    VarSet(VAR_0x800A, 6);
    VarSet(VAR_0x800B, 7);
    VarSet(VAR_TEMP_0, 8);
    VarSet(VAR_TEMP_1, 9);
    VarSet(VAR_TEMP_2, 10);
    VarSet(VAR_TEMP_3, 11);
    VarSet(VAR_TEMP_4, 12);
    VarSet(VAR_TEMP_5, MOVE_SCRATCH);
    VarSet(VAR_TEMP_6, MOVE_SPLASH);
    VarSet(VAR_TEMP_7, MOVE_CELEBRATE);
    VarSet(VAR_TEMP_8, MOVE_EXPLOSION);
    VarSet(VAR_TEMP_9, SHINY_MODE_ALWAYS);
    VarSet(VAR_TEMP_A, TRUE);
    VarSet(VAR_TEMP_B, TYPE_FIRE);

    RUN_OVERWORLD_SCRIPT(
        givemon VAR_TEMP_C, VAR_TEMP_D, item=VAR_0x8000, ball=VAR_0x8001, nature=VAR_0x8002, abilityNum=VAR_0x8003, gender=VAR_0x8004, hpEv=VAR_0x8005, atkEv=VAR_0x8006, defEv=VAR_0x8007, speedEv=VAR_0x8008, spAtkEv=VAR_0x8009, spDefEv=VAR_0x800A, hpIv=VAR_0x800B, atkIv=VAR_TEMP_0, defIv=VAR_TEMP_1, speedIv=VAR_TEMP_2, spAtkIv=VAR_TEMP_3, spDefIv=VAR_TEMP_4, move1=VAR_TEMP_5, move2=VAR_TEMP_6, move3=VAR_TEMP_7, move4=VAR_TEMP_8, shinyMode=VAR_TEMP_9, gmaxFactor=VAR_TEMP_A, teraType=VAR_TEMP_B;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_WOBBUFFET);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_POKEBALL), BALL_MASTER);
    EXPECT_EQ(GetNature(&gPlayerParty[0]), NATURE_BOLD);
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), GetSpeciesAbility(SPECIES_WOBBUFFET, 2));
    EXPECT_EQ(GetMonGender(&gPlayerParty[0]), MON_MALE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 1);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_EV), 2);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_EV), 3);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_EV), 4);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_EV), 5);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_EV), 6);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_IV), 7);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_IV), 8);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_IV), 9);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_IV), 10);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_IV), 11);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_IV), 12);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1), MOVE_SCRATCH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE2), MOVE_SPLASH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE3), MOVE_CELEBRATE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE4), MOVE_EXPLOSION);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_IS_SHINY), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_TERA_TYPE), TYPE_FIRE);
}

TEST("checkteratype/setteratype work")
{
    CreateRandomMonWithIVs(&gPlayerParty[0], SPECIES_WOBBUFFET, 100, 0);

    RUN_OVERWORLD_SCRIPT(
        checkteratype 0;
    );
    EXPECT(VarGet(VAR_RESULT) == TYPE_PSYCHIC);

    RUN_OVERWORLD_SCRIPT(
        setteratype TYPE_FIRE, 0;
        checkteratype 0;
    );
    EXPECT(VarGet(VAR_RESULT) == TYPE_FIRE);
}

TEST("createmon [simple]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        createmon 1, 0, SPECIES_WOBBUFFET, 100;
        createmon 1, 1, SPECIES_WYNAUT, 10;
    );

    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), SPECIES_WOBBUFFET);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gEnemyParty[1], MON_DATA_SPECIES), SPECIES_WYNAUT);
    EXPECT_EQ(GetMonData(&gEnemyParty[1], MON_DATA_LEVEL), 10);
}

TEST("Pokémon level up learnsets fit within MAX_LEVEL_UP_MOVES and MAX_RELEARNER_MOVES")
{

    u32 j, count, species = 0;
    const struct LevelUpMove *learnset;

    for(j = 0; j < SPECIES_EGG; j++)
    {
        PARAMETRIZE { species = j; }
    }

    learnset = GetSpeciesLevelUpLearnset(species);
    count = 0;
    for (j = 0; learnset[j].move != LEVEL_UP_MOVE_END; j++)
        count++;
    EXPECT_LT(count, MAX_LEVEL_UP_MOVES);
    EXPECT_LT(count, MAX_RELEARNER_MOVES - 1); // - 1 because at least one move is already known
}

TEST("Optimised GetMonData")
{
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 5, Random32(), OTID_STRUCT_PRESET(0x12345678));
    u32 exp = 0x123456;
    SetMonData(&gPlayerParty[0], MON_DATA_EXP, &exp);
    struct Benchmark optimised,
        vanilla = (struct Benchmark) { .ticks = 137 }; // From prior testing
    u32 expGet = 0;
    BENCHMARK(&optimised) { expGet = GetMonData(&gPlayerParty[0], MON_DATA_EXP); }
    EXPECT_EQ(exp, expGet);
    EXPECT_FASTER(optimised, vanilla);
}

TEST("Optimised SetMonData")
{
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 5, Random32(), OTID_STRUCT_PRESET(0x12345678));
    u32 exp = 0x123456;
    struct Benchmark optimised,
        vanilla = (struct Benchmark) { .ticks = 205 }; // From prior testing
    BENCHMARK(&optimised) { SetMonData(&gPlayerParty[0], MON_DATA_EXP, &exp); }
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_BAD_EGG), FALSE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_EXP), exp);
    EXPECT_FASTER(optimised, vanilla);
}

//Sanity check for a CalculateMonStats refactor (could be deleted or improved)
TEST("CalculateMonStats")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_WOBBUFFET, 100, item=ITEM_LEFTOVERS, ball=BALL_MASTER, nature=NATURE_BOLD, abilityNum=2, gender=MON_MALE, hpEv=1, atkEv=2, defEv=3, speedEv=4, spAtkEv=5, spDefEv=6, hpIv=7, atkIv=8, defIv=9, speedIv=10, spAtkIv=11, spDefIv=12, move1=MOVE_SCRATCH, move2=MOVE_SPLASH, move3=MOVE_CELEBRATE, move4=MOVE_EXPLOSION, shinyMode=SHINY_MODE_ALWAYS, gmaxFactor=TRUE, teraType=TYPE_FIRE;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP), 497);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK), 71);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF), 143);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED), 82);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK), 83);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF), 134);

}

TEST("LoadPlayerParty derives cached level from experience")
{
    u8 staleLevel = 70;
    u16 staleStat = 1;
    u32 expectedMaxHP;

    ZeroPlayerPartyMons();
    CreateMonWithIVs(&gPlayerParty[0], SPECIES_WOBBUFFET, 85, 0, OTID_STRUCT_PLAYER_ID, 0);
    expectedMaxHP = GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP);
    SetMonData(&gPlayerParty[0], MON_DATA_LEVEL, &staleLevel);
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &staleStat);
    SetMonData(&gPlayerParty[0], MON_DATA_MAX_HP, &staleStat);
    gPlayerPartyCount = 1;
    SavePlayerParty();

    ZeroPlayerPartyMons();
    LoadPlayerParty();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 85);
    EXPECT_EQ(GetLevelFromMonExp(&gPlayerParty[0]), 85);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP), expectedMaxHP);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), expectedMaxHP);
}
