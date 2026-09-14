#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Poison Puppeteer confuses target if it was poisoned by a damaging move")
{
    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_POISON_STING, MOVE_EFFECT_POISON) == TRUE);
        PLAYER(SPECIES_PECHARUNT) { Ability(ABILITY_POISON_PUPPETEER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POISON_STING); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISON_STING, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        STATUS_ICON(opponent, poison: TRUE);
        ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        MESSAGE("The opposing Wobbuffet became confused!");
    }
}

SINGLE_BATTLE_TEST("Poison Puppeteer confuses target if it was (badly) poisoned by a status move")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_POISON_POWDER; }
    PARAMETRIZE { move = MOVE_TOXIC; }

    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_POISON_STING, MOVE_EFFECT_POISON) == TRUE);
        PLAYER(SPECIES_PECHARUNT) { Ability(ABILITY_POISON_PUPPETEER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        if (move == MOVE_POISON_POWDER)
            STATUS_ICON(opponent, poison: TRUE);
        else
            STATUS_ICON(opponent, badPoison: TRUE);
        ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        MESSAGE("The opposing Wobbuffet became confused!");
    }
}

SINGLE_BATTLE_TEST("Poison Puppeteer does not trigger if poison is Toxic Spikes induced")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_TOXIC_SPIKES) == EFFECT_TOXIC_SPIKES);
        PLAYER(SPECIES_PECHARUNT) { Ability(ABILITY_POISON_PUPPETEER); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TOXIC_SPIKES); }
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TOXIC_SPIKES, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        STATUS_ICON(opponent, poison: TRUE);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
            MESSAGE("The opposing Wobbuffet became confused!");
        }
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Poison Puppeteer confuses poisoned targets with species's innate")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_POISON_STING; }
    PARAMETRIZE { move = MOVE_POISON_POWDER; }
    PARAMETRIZE { move = MOVE_TOXIC; }

    GIVEN {
        ASSUME(SpeciesHasInnate(SPECIES_ARIADOS, ABILITY_POISON_PUPPETEER));
        ASSUME(MoveHasAdditionalEffect(MOVE_POISON_STING, MOVE_EFFECT_POISON));
        PLAYER(SPECIES_ARIADOS) { Ability(ABILITY_SWARM); Level(100); USE_DEFAULT_INNATES; }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        if (move == MOVE_POISON_STING)
            HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        if (move == MOVE_TOXIC)
            STATUS_ICON(opponent, badPoison: TRUE);
        else
            STATUS_ICON(opponent, poison: TRUE);
        ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        MESSAGE("The opposing Wobbuffet became confused!");
    }
}

SINGLE_BATTLE_TEST("Poison Puppeteer remains restricted to species with the ability or innate")
{
    bool32 innate;

    PARAMETRIZE { innate = FALSE; }
    PARAMETRIZE { innate = TRUE; }

    GIVEN {
        ASSUME(!SpeciesHasInnate(SPECIES_WOBBUFFET, ABILITY_POISON_PUPPETEER));
        PLAYER(SPECIES_WOBBUFFET) {
            Ability(innate ? ABILITY_SHADOW_TAG : ABILITY_POISON_PUPPETEER);
            Innates(innate ? ABILITY_POISON_PUPPETEER : ABILITY_NONE);
        }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TOXIC); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TOXIC, player);
        STATUS_ICON(opponent, badPoison: TRUE);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        }
    }
}

SINGLE_BATTLE_TEST("Poison Puppeteer confuses target if it was poisoned by a damaging move (Traits)")
{
    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_POISON_STING, MOVE_EFFECT_POISON) == TRUE);
        PLAYER(SPECIES_PECHARUNT) { Ability(ABILITY_LIGHT_METAL); Innates(ABILITY_POISON_PUPPETEER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POISON_STING); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISON_STING, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        STATUS_ICON(opponent, poison: TRUE);
        ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        MESSAGE("The opposing Wobbuffet became confused!");
    }
}

SINGLE_BATTLE_TEST("Poison Puppeteer confuses target if it was (badly) poisoned by a status move (Traits)")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_POISON_POWDER; }
    PARAMETRIZE { move = MOVE_TOXIC; }

    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_POISON_STING, MOVE_EFFECT_POISON) == TRUE);
        PLAYER(SPECIES_PECHARUNT) { Ability(ABILITY_LIGHT_METAL); Innates(ABILITY_POISON_PUPPETEER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        if (move == MOVE_POISON_POWDER)
            STATUS_ICON(opponent, poison: TRUE);
        else
            STATUS_ICON(opponent, badPoison: TRUE);
        ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        MESSAGE("The opposing Wobbuffet became confused!");
    }
}

SINGLE_BATTLE_TEST("Poison Puppeteer does not trigger if poison is Toxic Spikes induced (Traits)")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_TOXIC_SPIKES) == EFFECT_TOXIC_SPIKES);
        PLAYER(SPECIES_PECHARUNT) { Ability(ABILITY_LIGHT_METAL); Innates(ABILITY_POISON_PUPPETEER); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TOXIC_SPIKES);}
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TOXIC_SPIKES, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        STATUS_ICON(opponent, poison: TRUE);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_POISON_PUPPETEER);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
            MESSAGE("The opposing Wobbuffet became confused!");
        }
    }
}
#endif
