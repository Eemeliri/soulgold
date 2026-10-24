#include "global.h"
#include "pokemon_legacy.h"

// Converting old to new
#define COPY_SECURE_FIELDS(dst, src) do { \
    (dst)->secure.species = (src)->secure.species; \
    (dst)->secure.teraType = (src)->secure.teraType; \
    (dst)->secure.heldItem = (src)->secure.heldItem; \
    (dst)->secure.pokeball = (src)->secure.pokeball; \
    (dst)->secure.experience = (src)->secure.experience; \
    (dst)->secure.metLocationHiBit0 = (src)->secure.metLocationHiBit0; \
    (dst)->secure.ppBonuses = (src)->secure.ppBonuses; \
    (dst)->secure.friendship = (src)->secure.friendship; \
    (dst)->secure.move1 = (src)->secure.move1; \
    (dst)->secure.evolutionTracker1 = (src)->secure.evolutionTracker1; \
    (dst)->secure.move2 = (src)->secure.move2; \
    (dst)->secure.evolutionTracker2 = (src)->secure.evolutionTracker2; \
    (dst)->secure.move3 = (src)->secure.move3; \
    (dst)->secure.metLocationHiBits1_5 = (src)->secure.metLocationHiBits1_5; \
    (dst)->secure.move4 = (src)->secure.move4; \
    (dst)->secure.metLocationHiBit6 = (src)->secure.metLocationHiBit6; \
    (dst)->secure.abilityNum = (src)->secure.abilityNum; \
    (dst)->secure.hyperTrainedHP = (src)->secure.hyperTrainedHP; \
    (dst)->secure.hyperTrainedAttack = (src)->secure.hyperTrainedAttack; \
    (dst)->secure.pp1 = (src)->secure.pp1; \
    (dst)->secure.hyperTrainedDefense = (src)->secure.hyperTrainedDefense; \
    (dst)->secure.pp2 = (src)->secure.pp2; \
    (dst)->secure.hyperTrainedSpeed = (src)->secure.hyperTrainedSpeed; \
    (dst)->secure.pp3 = (src)->secure.pp3; \
    (dst)->secure.hyperTrainedSpAttack = (src)->secure.hyperTrainedSpAttack; \
    (dst)->secure.pp4 = (src)->secure.pp4; \
    (dst)->secure.hyperTrainedSpDefense = (src)->secure.hyperTrainedSpDefense; \
    (dst)->secure.hpEV = (src)->secure.hpEV; \
    (dst)->secure.attackEV = (src)->secure.attackEV; \
    (dst)->secure.defenseEV = (src)->secure.defenseEV; \
    (dst)->secure.speedEV = (src)->secure.speedEV; \
    (dst)->secure.spAttackEV = (src)->secure.spAttackEV; \
    (dst)->secure.spDefenseEV = (src)->secure.spDefenseEV; \
    (dst)->secure.pokerus = (src)->secure.pokerus; \
    (dst)->secure.metLocation = (src)->secure.metLocation; \
    (dst)->secure.metLevel = (src)->secure.metLevel; \
    (dst)->secure.metGame = (src)->secure.metGame; \
    (dst)->secure.otGender = (src)->secure.otGender; \
    (dst)->secure.hpIV = (src)->secure.hpIV; \
    (dst)->secure.attackIV = (src)->secure.attackIV; \
    (dst)->secure.defenseIV = (src)->secure.defenseIV; \
    (dst)->secure.speedIV = (src)->secure.speedIV; \
    (dst)->secure.spAttackIV = (src)->secure.spAttackIV; \
    (dst)->secure.spDefenseIV = (src)->secure.spDefenseIV; \
    (dst)->secure.isEgg = (src)->secure.isEgg; \
} while (0)

void BoxPokemonV19ToCurrent(struct BoxPokemon *dst, const struct BoxPokemonV19 *src)
{
    memset(dst, 0, sizeof(*dst));
    memcpy(dst, src, 32);
    dst->reservedOuter = 0;
    COPY_SECURE_FIELDS(dst, src);
    if (src->secure.species == SPECIES_BELDUM
     && src->secure.heldItem == ITEM_IRON_BALL
     && src->secure.heldItem2 == ITEM_LUXURY_BALL
     && src->secure.pokeball == ITEM_POKE_BALL)
        dst->secure.pokeball = ITEM_LUXURY_BALL;
    if (src->secure.heldItem == ITEM_NONE)
        dst->secure.heldItem = src->secure.heldItem2;
}

void CurrentBoxPokemonToV19(struct BoxPokemonV19 *dst, const struct BoxPokemon *src)
{
    memset(dst, 0, sizeof(*dst));
    memcpy(dst, src, 32);
    COPY_SECURE_FIELDS(dst, src);
}
