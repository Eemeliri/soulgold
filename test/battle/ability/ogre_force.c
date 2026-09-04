#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(MoveIsAffectedBySheerForce(MOVE_NUZZLE) == TRUE);
    ASSUME(MoveIsAffectedBySheerForce(MOVE_SCRATCH) == FALSE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_TEAL].innates[2] == ABILITY_OGRE_FORCE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_WELLSPRING].innates[2] == ABILITY_OGRE_FORCE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_HEARTHFLAME].innates[2] == ABILITY_OGRE_FORCE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_CORNERSTONE].innates[2] == ABILITY_OGRE_FORCE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_TEAL_TERA].innates[2] == ABILITY_OGRE_FORCE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_WELLSPRING_TERA].innates[2] == ABILITY_OGRE_FORCE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_HEARTHFLAME_TERA].innates[2] == ABILITY_OGRE_FORCE);
    ASSUME(gSpeciesInfo[SPECIES_OGERPON_CORNERSTONE_TERA].innates[2] == ABILITY_OGRE_FORCE);
}

SINGLE_BATTLE_TEST("Ogre Force boosts moves with added effects by 15%", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_OGRE_FORCE; }
    GIVEN {
        PLAYER(SPECIES_OGERPON) { Ability(ability); Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_NUZZLE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.15), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Ogre Force does not boost moves without added effects", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_OGRE_FORCE; }
    GIVEN {
        PLAYER(SPECIES_OGERPON) { Ability(ability); Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Ogre Force preserves added effects")
{
    GIVEN {
        PLAYER(SPECIES_OGERPON) { Ability(ABILITY_OGRE_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_NUZZLE); }
    } SCENE {
        STATUS_ICON(opponent, paralysis: TRUE);
    }
}
