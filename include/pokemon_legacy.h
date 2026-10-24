#ifndef GUARD_POKEMON_LEGACY_H
#define GUARD_POKEMON_LEGACY_H

#include "pokemon.h"

struct PokemonSecureDataV19
{
    u16 species:11; // 2047 species.
    enum Type teraType:5; // 30 types.
    u16 heldItem:10; // 1023 items.
    u16 pokeball:6; // 63 balls.
    u32 experience:24; // 16777215 exp.
    u32 heldItem2:10; // 1023 items.
    u32 metLocationHiBit0:1;
    u8 ppBonuses;
    u8 friendship;

    enum Move move1:11; // 2047 moves.
    u16 evolutionTracker1:5;
    enum Move move2:11; // 2047 moves.
    u16 evolutionTracker2:5;
    enum Move move3:11; // 2047 moves.
    u16 metLocationHiBits1_5:5;
    enum Move move4:11; // 2047 moves.
    u16 metLocationHiBit6:1;
    u16 abilityNum:2;
    u16 hyperTrainedHP:1;
    u16 hyperTrainedAttack:1;
    u8 pp1:7; // 127 PP.
    u8 hyperTrainedDefense:1;
    u8 pp2:7; // 127 PP.
    u8 hyperTrainedSpeed:1;
    u8 pp3:7; // 127 PP.
    u8 hyperTrainedSpAttack:1;
    u8 pp4:7; // 127 PP.
    u8 hyperTrainedSpDefense:1;

    u8 hpEV;
    u8 attackEV;
    u8 defenseEV;
    u8 speedEV;
    u8 spAttackEV;
    u8 spDefenseEV;
    u8 cool;
    u8 beauty;
    u8 cute;
    u8 smart;
    u8 tough;
    u8 sheen;

    u8 pokerus;
    u8 metLocation;
    u16 metLevel:7;
    u16 metGame:4;
    u16 otGender:1;
    u32 hpIV:5;
    u32 attackIV:5;
    u32 defenseIV:5;
    u32 speedIV:5;
    u32 spAttackIV:5;
    u32 spDefenseIV:5;
    u32 isEgg:1;
    u32 gigantamaxFactor:1;
};

struct BoxPokemonV19
{
    u32 personality;
    u32 otId;
    u8 nickname[12];
    u8 language:3;
    u8 hiddenNatureModifier:5; // 31 natures.
    u8 isBadEgg:1;
    u8 hasSpecies:1;
    u8 isEgg:1;
    u8 blockBoxRS:1; // Unused, but Pokémon Box Ruby & Sapphire will refuse to deposit a Pokémon with this flag set.
    u8 daysSinceFormChange:3; // 7 days.
    u8 otName[7];
    u8 markings:4;
    u8 compressedStatus:4;
    u16 hpLost:14; // 16383 HP.
    u16 shinyModifier:1;
    // See MON_DATA_MODERN_FATEFUL_ENCOUNTER.
    u16 modernFatefulEncounter:1;

    struct PokemonSecureDataV19 secure;
};

struct PokemonV19
{
    struct BoxPokemonV19 box;
    u32 status;
    u8 level;
    u8 mail;
    u16 hp;
    u16 maxHP;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spAttack;
    u16 spDefense;
};

STATIC_ASSERT(sizeof(struct PokemonSecureDataV19) == 44, LegacySecureSize);
STATIC_ASSERT(sizeof(struct BoxPokemonV19) == 76, LegacyBoxSize);
STATIC_ASSERT(offsetof(struct BoxPokemonV19, secure) == 32, LegacySecureOffset);
STATIC_ASSERT(sizeof(struct PokemonV19) == 96, LegacyPartySize);
STATIC_ASSERT(offsetof(struct PokemonV19, status) == 76, LegacyStatusOffset);

void BoxPokemonV19ToCurrent(struct BoxPokemon *, const struct BoxPokemonV19 *);
void CurrentBoxPokemonToV19(struct BoxPokemonV19 *, const struct BoxPokemon *);

#endif // GUARD_POKEMON_LEGACY_H
