#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_KNOCK_OFF) == EFFECT_KNOCK_OFF);
    ASSUME(GetMoveEffect(MOVE_THIEF) == EFFECT_STEAL_ITEM);
    ASSUME(GetMoveEffect(MOVE_COVET) == EFFECT_STEAL_ITEM);
    ASSUME(GetMoveEffect(MOVE_TRICK) == EFFECT_TRICK);
    ASSUME(GetMoveEffect(MOVE_SWITCHEROO) == EFFECT_TRICK);
    ASSUME(GetMoveEffect(MOVE_CORROSIVE_GAS) == EFFECT_CORROSIVE_GAS);
    ASSUME(GetMoveEffect(MOVE_BESTOW) == EFFECT_BESTOW);
}

SINGLE_BATTLE_TEST("Multitype prevents held items from being removed")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_KNOCK_OFF; }
    PARAMETRIZE { move = MOVE_THIEF; }
    PARAMETRIZE { move = MOVE_COVET; }
    PARAMETRIZE { move = MOVE_TRICK; }
    PARAMETRIZE { move = MOVE_SWITCHEROO; }
    PARAMETRIZE { move = MOVE_CORROSIVE_GAS; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ARCEUS) { Ability(ABILITY_MULTITYPE); Item(ITEM_CHOICE_SPECS); }
    } WHEN {
        TURN { MOVE(player, move); }
    } THEN {
        EXPECT_EQ(opponent->item, ITEM_CHOICE_SPECS);
        EXPECT_EQ(player->item, ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Multitype does not prevent receiving a held item")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_CHOICE_SPECS); }
        OPPONENT(SPECIES_ARCEUS) { Ability(ABILITY_MULTITYPE); }
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } THEN {
        EXPECT_EQ(opponent->item, ITEM_CHOICE_SPECS);
        EXPECT_EQ(player->item, ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Knock Off does not boost damage dealth to Multitype user", s16 damage)
{
    enum Item item;

    PARAMETRIZE { item = ITEM_NONE; }
    PARAMETRIZE { item = ITEM_CHOICE_SPECS; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ARCEUS) { Ability(ABILITY_MULTITYPE); Item(item); }
    } WHEN {
        TURN { MOVE(player, MOVE_KNOCK_OFF); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}
