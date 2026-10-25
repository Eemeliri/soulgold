// Additional sets shared by the Frontier and New Game+ trainer generation.
// Included inside gBattleFrontierMons. IDs are appended to preserve saved rentals.
// EV/IV macro order: HP, Attack, Defense, Speed, Sp. Attack, Sp. Defense.

// Standard tier.


    [FRONTIER_MON_VENUSAUR_6] = {
        .species = SPECIES_VENUSAUR,
        .moves = {MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_EARTH_POWER, MOVE_GROWTH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_VENUSAUR_7] = {
        .species = SPECIES_VENUSAUR,
        .moves = {MOVE_POWER_WHIP, MOVE_POISON_JAB, MOVE_EARTHQUAKE, MOVE_SWORDS_DANCE},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_OVERGROW,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_CHARIZARD_6] = {
        .species = SPECIES_CHARIZARD,
        .moves = {MOVE_FIRE_BLAST, MOVE_AIR_SLASH, MOVE_FOCUS_BLAST, MOVE_SCORCHING_SANDS},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BLAZE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_CHARIZARD_7] = {
        .species = SPECIES_CHARIZARD,
        .moves = {MOVE_FLAMETHROWER, MOVE_SCORCHING_SANDS, MOVE_WILL_O_WISP, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_BLAZE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_BLASTOISE_6] = {
        .species = SPECIES_BLASTOISE,
        .moves = {MOVE_SCALD, MOVE_BODY_PRESS, MOVE_IRON_DEFENSE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_RAIN_DISH,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_BLASTOISE_7] = {
        .species = SPECIES_BLASTOISE,
        .moves = {MOVE_WATER_SPOUT, MOVE_SURF, MOVE_ICE_BEAM, MOVE_AURA_SPHERE},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_BUTTERFREE_5] = {
        .species = SPECIES_BUTTERFREE,
        .moves = {MOVE_BUG_BUZZ, MOVE_HURRICANE, MOVE_PSYCHIC, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TINTED_LENS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_BUTTERFREE_6] = {
        .species = SPECIES_BUTTERFREE,
        .moves = {MOVE_HURRICANE, MOVE_STUN_SPORE, MOVE_ROOST, MOVE_DEFOG},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_COMPOUND_EYES,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_BEEDRILL_5] = {
        .species = SPECIES_BEEDRILL,
        .moves = {MOVE_TOXIC_SPIKES, MOVE_U_TURN, MOVE_POISON_JAB, MOVE_ENDEAVOR},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWARM,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BEEDRILL_6] = {
        .species = SPECIES_BEEDRILL,
        .moves = {MOVE_FOCUS_ENERGY, MOVE_POISON_JAB, MOVE_DRILL_RUN, MOVE_X_SCISSOR},
        .heldItem = {ITEM_SCOPE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SNIPER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PIDGEOT_5] = {
        .species = SPECIES_PIDGEOT,
        .moves = {MOVE_HURRICANE, MOVE_HEAT_WAVE, MOVE_HYPER_BEAM, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BIG_PECKS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PIDGEOT_6] = {
        .species = SPECIES_PIDGEOT,
        .moves = {MOVE_BRAVE_BIRD, MOVE_U_TURN, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_BIG_PECKS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_RATICATE_5] = {
        .species = SPECIES_RATICATE,
        .moves = {MOVE_ENDURE, MOVE_REVERSAL, MOVE_CRUNCH, MOVE_QUICK_ATTACK},
        .heldItem = {ITEM_LIECHI_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GUTS,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_RATICATE_6] = {
        .species = SPECIES_RATICATE,
        .moves = {MOVE_QUICK_ATTACK, MOVE_ENDEAVOR, MOVE_THUNDER_WAVE, MOVE_U_TURN},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GUTS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_RATICATE_ALOLA_5] = {
        .species = SPECIES_RATICATE_ALOLA,
        .moves = {MOVE_BULK_UP, MOVE_CRUNCH, MOVE_RETURN, MOVE_REST},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GLUTTONY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_RATICATE_ALOLA_6] = {
        .species = SPECIES_RATICATE_ALOLA,
        .moves = {MOVE_SWITCHEROO, MOVE_DOUBLE_EDGE, MOVE_KNOCK_OFF, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_HUSTLE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ARBOK_5] = {
        .species = SPECIES_ARBOK,
        .moves = {MOVE_COIL, MOVE_GUNK_SHOT, MOVE_EARTHQUAKE, MOVE_REST},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SHED_SKIN,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_ARBOK_6] = {
        .species = SPECIES_ARBOK,
        .moves = {MOVE_GLARE, MOVE_KNOCK_OFF, MOVE_POISON_JAB, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_RAICHU_5] = {
        .species = SPECIES_RAICHU,
        .moves = {MOVE_THUNDERBOLT, MOVE_SURF, MOVE_FOCUS_BLAST, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LIGHTNING_ROD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_RAICHU_6] = {
        .species = SPECIES_RAICHU,
        .moves = {MOVE_VOLT_SWITCH, MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_ENCORE},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_LIGHTNING_ROD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_RAICHU_ALOLA_5] = {
        .species = SPECIES_RAICHU_ALOLA,
        .moves = {MOVE_THUNDERBOLT, MOVE_PSYSHOCK, MOVE_SURF, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SURGE_SURFER,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_RAICHU_ALOLA_6] = {
        .species = SPECIES_RAICHU_ALOLA,
        .moves = {MOVE_CALM_MIND, MOVE_THUNDERBOLT, MOVE_PSYCHIC, MOVE_DRAINING_KISS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SURGE_SURFER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SANDSLASH_5] = {
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_SWORDS_DANCE, MOVE_DRILL_RUN, MOVE_LEECH_LIFE, MOVE_NIGHT_SLASH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SAND_RUSH,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SANDSLASH_6] = {
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_SPIKES, MOVE_EARTHQUAKE, MOVE_KNOCK_OFF, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SAND_VEIL,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_SANDSLASH_ALOLA_5] = {
        .species = SPECIES_SANDSLASH_ALOLA,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_IRON_HEAD, MOVE_EARTHQUAKE, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SLUSH_RUSH,
        .nature = NATURE_ADAMANT,
    },

    [FRONTIER_MON_SANDSLASH_ALOLA_6] = {
        .species = SPECIES_SANDSLASH_ALOLA,
        .moves = {MOVE_SNOWSCAPE, MOVE_AURORA_VEIL, MOVE_RAPID_SPIN, MOVE_ICICLE_CRASH},
        .heldItem = {ITEM_ICY_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SLUSH_RUSH,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_NIDOQUEEN_5] = {
        .species = SPECIES_NIDOQUEEN,
        .moves = {MOVE_EARTH_POWER, MOVE_SLUDGE_WAVE, MOVE_ICE_BEAM, MOVE_FLAMETHROWER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_NIDOQUEEN_6] = {
        .species = SPECIES_NIDOQUEEN,
        .moves = {MOVE_EARTH_POWER, MOVE_SLUDGE_BOMB, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_POISON_POINT,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_NIDOKING_5] = {
        .species = SPECIES_NIDOKING,
        .moves = {MOVE_POISON_JAB, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_NIDOKING_6] = {
        .species = SPECIES_NIDOKING,
        .moves = {MOVE_SUBSTITUTE, MOVE_EARTH_POWER, MOVE_SLUDGE_WAVE, MOVE_ICE_BEAM},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_CLEFABLE_5] = {
        .species = SPECIES_CLEFABLE,
        .moves = {MOVE_MOONBLAST, MOVE_FLAMETHROWER, MOVE_THUNDERBOLT, MOVE_SOFT_BOILED},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_MAGIC_GUARD,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CLEFABLE_6] = {
        .species = SPECIES_CLEFABLE,
        .moves = {MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_MOONLIGHT, MOVE_AROMATHERAPY},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_NINETALES_5] = {
        .species = SPECIES_NINETALES,
        .moves = {MOVE_OVERHEAT, MOVE_SOLAR_BEAM, MOVE_SCORCHING_SANDS, MOVE_DARK_PULSE},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_DROUGHT,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_NINETALES_6] = {
        .species = SPECIES_NINETALES,
        .moves = {MOVE_FLAMETHROWER, MOVE_ENCORE, MOVE_WILL_O_WISP, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_DROUGHT,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_NINETALES_ALOLA_5] = {
        .species = SPECIES_NINETALES_ALOLA,
        .moves = {MOVE_BLIZZARD, MOVE_FREEZE_DRY, MOVE_MOONBLAST, MOVE_DARK_PULSE},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SNOW_WARNING,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_NINETALES_ALOLA_6] = {
        .species = SPECIES_NINETALES_ALOLA,
        .moves = {MOVE_FREEZE_DRY, MOVE_MOONBLAST, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_SNOW_WARNING,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_WIGGLYTUFF_5] = {
        .species = SPECIES_WIGGLYTUFF,
        .moves = {MOVE_NASTY_PLOT, MOVE_HYPER_VOICE, MOVE_DAZZLING_GLEAM, MOVE_FIRE_BLAST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_WIGGLYTUFF_6] = {
        .species = SPECIES_WIGGLYTUFF,
        .moves = {MOVE_DAZZLING_GLEAM, MOVE_THUNDER_WAVE, MOVE_WISH, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_VILEPLUME_6] = {
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_SLEEP_POWDER, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_EFFECT_SPORE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_VILEPLUME_7] = {
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_SWORDS_DANCE, MOVE_SEED_BOMB, MOVE_DRAIN_PUNCH, MOVE_SLEEP_POWDER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DUGTRIO_5] = {
        .species = SPECIES_DUGTRIO,
        .moves = {MOVE_SWORDS_DANCE, MOVE_EARTHQUAKE, MOVE_STONE_EDGE, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ARENA_TRAP,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DUGTRIO_6] = {
        .species = SPECIES_DUGTRIO,
        .moves = {MOVE_ENDURE, MOVE_REVERSAL, MOVE_EARTHQUAKE, MOVE_NIGHT_SLASH},
        .heldItem = {ITEM_LIECHI_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ARENA_TRAP,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DUGTRIO_ALOLA_5] = {
        .species = SPECIES_DUGTRIO_ALOLA,
        .moves = {MOVE_SWORDS_DANCE, MOVE_EARTHQUAKE, MOVE_IRON_HEAD, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SAND_FORCE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DUGTRIO_ALOLA_6] = {
        .species = SPECIES_DUGTRIO_ALOLA,
        .moves = {MOVE_STEALTH_ROCK, MOVE_MEMENTO, MOVE_EARTHQUAKE, MOVE_IRON_HEAD},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TANGLING_HAIR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PERSIAN_5] = {
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_SLASH, MOVE_NIGHT_SLASH, MOVE_PLAY_ROUGH, MOVE_U_TURN},
        .heldItem = {ITEM_SCOPE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PERSIAN_6] = {
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_BODY_SLAM, MOVE_KNOCK_OFF, MOVE_U_TURN, MOVE_HYPNOSIS},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PERSIAN_ALOLA_5] = {
        .species = SPECIES_PERSIAN_ALOLA,
        .moves = {MOVE_FOUL_PLAY, MOVE_PARTING_SHOT, MOVE_TAUNT, MOVE_REST},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_FUR_COAT,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PERSIAN_ALOLA_6] = {
        .species = SPECIES_PERSIAN_ALOLA,
        .moves = {MOVE_DARK_PULSE, MOVE_THUNDERBOLT, MOVE_ICY_WIND, MOVE_SWITCHEROO},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PRIMEAPE_5] = {
        .species = SPECIES_PRIMEAPE,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_FACADE, MOVE_STONE_EDGE, MOVE_U_TURN},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PRIMEAPE_6] = {
        .species = SPECIES_PRIMEAPE,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_RAGE_FIST, MOVE_ICE_PUNCH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_VITAL_SPIRIT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_ARCANINE_5] = {
        .species = SPECIES_ARCANINE,
        .moves = {MOVE_FLARE_BLITZ, MOVE_FACADE, MOVE_CLOSE_COMBAT, MOVE_EXTREME_SPEED},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_ARCANINE_6] = {
        .species = SPECIES_ARCANINE,
        .moves = {MOVE_FLAMETHROWER, MOVE_SCORCHING_SANDS, MOVE_SNARL, MOVE_MORNING_SUN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_POLIWRATH_5] = {
        .species = SPECIES_POLIWRATH,
        .moves = {MOVE_LIQUIDATION, MOVE_CLOSE_COMBAT, MOVE_ICE_PUNCH, MOVE_RAIN_DANCE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_POLIWRATH_6] = {
        .species = SPECIES_POLIWRATH,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_LIQUIDATION, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_ALAKAZAM_5] = {
        .species = SPECIES_ALAKAZAM,
        .moves = {MOVE_PSYSHOCK, MOVE_FOCUS_BLAST, MOVE_SHADOW_BALL, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MAGIC_GUARD,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_ALAKAZAM_6] = {
        .species = SPECIES_ALAKAZAM,
        .moves = {MOVE_PSYCHIC, MOVE_FOCUS_BLAST, MOVE_NASTY_PLOT, MOVE_ENCORE},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MAGIC_GUARD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MACHAMP_5] = {
        .species = SPECIES_MACHAMP,
        .moves = {MOVE_SUBSTITUTE, MOVE_DYNAMIC_PUNCH, MOVE_STONE_EDGE, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_NO_GUARD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MACHAMP_6] = {
        .species = SPECIES_MACHAMP,
        .moves = {MOVE_DYNAMIC_PUNCH, MOVE_HEAVY_SLAM, MOVE_ICE_PUNCH, MOVE_BULLET_PUNCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_NO_GUARD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_VICTREEBEL_6] = {
        .species = SPECIES_VICTREEBEL,
        .moves = {MOVE_SUNNY_DAY, MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_WEATHER_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_VICTREEBEL_7] = {
        .species = SPECIES_VICTREEBEL,
        .moves = {MOVE_SUBSTITUTE, MOVE_LEAF_STORM, MOVE_SLUDGE_BOMB, MOVE_ENCORE},
        .heldItem = {ITEM_SALAC_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_GLUTTONY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_TENTACRUEL_5] = {
        .species = SPECIES_TENTACRUEL,
        .moves = {MOVE_SCALD, MOVE_KNOCK_OFF, MOVE_HAZE, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_LIQUID_OOZE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_TENTACRUEL_6] = {
        .species = SPECIES_TENTACRUEL,
        .moves = {MOVE_ACID_SPRAY, MOVE_SURF, MOVE_GIGA_DRAIN, MOVE_ICE_BEAM},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GOLEM_5] = {
        .species = SPECIES_GOLEM,
        .moves = {MOVE_ROCK_POLISH, MOVE_EARTHQUAKE, MOVE_ROCK_BLAST, MOVE_FIRE_PUNCH},
        .heldItem = {ITEM_WEAKNESS_POLICY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_STURDY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_GOLEM_6] = {
        .species = SPECIES_GOLEM,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_ROCK_BLAST, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_GOLEM_ALOLA_5] = {
        .species = SPECIES_GOLEM_ALOLA,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_STONE_EDGE, MOVE_EARTHQUAKE, MOVE_EXPLOSION},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_GALVANIZE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_GOLEM_ALOLA_6] = {
        .species = SPECIES_GOLEM_ALOLA,
        .moves = {MOVE_CURSE, MOVE_WILD_CHARGE, MOVE_EARTHQUAKE, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_MAGNET_PULL,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_RAPIDASH_5] = {
        .species = SPECIES_RAPIDASH,
        .moves = {MOVE_FLARE_BLITZ, MOVE_HIGH_HORSEPOWER, MOVE_PLAY_ROUGH, MOVE_MORNING_SUN},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_RAPIDASH_6] = {
        .species = SPECIES_RAPIDASH,
        .moves = {MOVE_FLARE_BLITZ, MOVE_WILL_O_WISP, MOVE_MORNING_SUN, MOVE_HIGH_HORSEPOWER},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SLOWBRO_5] = {
        .species = SPECIES_SLOWBRO,
        .moves = {MOVE_SCALD, MOVE_FUTURE_SIGHT, MOVE_SLACK_OFF, MOVE_YAWN},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SLOWBRO_6] = {
        .species = SPECIES_SLOWBRO,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_SCALD, MOVE_SLACK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_FARFETCHD_5] = {
        .species = SPECIES_FARFETCHD,
        .moves = {MOVE_LEAF_BLADE, MOVE_NIGHT_SLASH, MOVE_CLOSE_COMBAT, MOVE_ROOST},
        .heldItem = {ITEM_LEEK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_FARFETCHD_6] = {
        .species = SPECIES_FARFETCHD,
        .moves = {MOVE_BRAVE_BIRD, MOVE_LEAF_BLADE, MOVE_CLOSE_COMBAT, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DEWGONG_5] = {
        .species = SPECIES_DEWGONG,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_RAIN_DANCE, MOVE_REST},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_DEWGONG_6] = {
        .species = SPECIES_DEWGONG,
        .moves = {MOVE_BLIZZARD, MOVE_SURF, MOVE_ENCORE, MOVE_SNOWSCAPE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ICE_BODY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_MUK_5] = {
        .species = SPECIES_MUK,
        .moves = {MOVE_POISON_JAB, MOVE_KNOCK_OFF, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_STICKY_HOLD,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MUK_6] = {
        .species = SPECIES_MUK,
        .moves = {MOVE_INFESTATION, MOVE_TOXIC, MOVE_PAIN_SPLIT, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_POISON_TOUCH,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_MUK_ALOLA_5] = {
        .species = SPECIES_MUK_ALOLA,
        .moves = {MOVE_CURSE, MOVE_POISON_JAB, MOVE_KNOCK_OFF, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_FIGY_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GLUTTONY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MUK_ALOLA_6] = {
        .species = SPECIES_MUK_ALOLA,
        .moves = {MOVE_POISON_JAB, MOVE_KNOCK_OFF, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_POISON_TOUCH,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CLOYSTER_5] = {
        .species = SPECIES_CLOYSTER,
        .moves = {MOVE_ICICLE_SPEAR, MOVE_ROCK_BLAST, MOVE_LIQUIDATION, MOVE_ICE_SHARD},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SKILL_LINK,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_CLOYSTER_6] = {
        .species = SPECIES_CLOYSTER,
        .moves = {MOVE_SHELL_SMASH, MOVE_ICICLE_SPEAR, MOVE_HYDRO_PUMP, MOVE_ROCK_BLAST},
        .heldItem = {ITEM_WHITE_HERB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 4, 0),
        .ability = ABILITY_SKILL_LINK,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_GENGAR_5] = {
        .species = SPECIES_GENGAR,
        .moves = {MOVE_WILL_O_WISP, MOVE_HEX, MOVE_SUBSTITUTE, MOVE_DISABLE},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GENGAR_6] = {
        .species = SPECIES_GENGAR,
        .moves = {MOVE_SHADOW_BALL, MOVE_SLUDGE_BOMB, MOVE_FOCUS_BLAST, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ELECTRODE_5] = {
        .species = SPECIES_ELECTRODE,
        .moves = {MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_VOLT_SWITCH, MOVE_TAUNT},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_AFTERMATH,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ELECTRODE_6] = {
        .species = SPECIES_ELECTRODE,
        .moves = {MOVE_CHARGE_BEAM, MOVE_SUBSTITUTE, MOVE_THUNDERBOLT, MOVE_FOUL_PLAY},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_STATIC,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_EXEGGUTOR_5] = {
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_SUBSTITUTE, MOVE_LEECH_SEED, MOVE_GIGA_DRAIN, MOVE_PSYCHIC},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HARVEST,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_EXEGGUTOR_6] = {
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_BULLET_SEED, MOVE_ZEN_HEADBUTT, MOVE_LOW_KICK, MOVE_EXPLOSION},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_EXEGGUTOR_ALOLA_5] = {
        .species = SPECIES_EXEGGUTOR_ALOLA,
        .moves = {MOVE_GIGA_DRAIN, MOVE_DRAGON_PULSE, MOVE_FLAMETHROWER, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_HARVEST,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_EXEGGUTOR_ALOLA_6] = {
        .species = SPECIES_EXEGGUTOR_ALOLA,
        .moves = {MOVE_BULLET_SEED, MOVE_DRAGON_HAMMER, MOVE_EARTHQUAKE, MOVE_LOW_KICK},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_HARVEST,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_MAROWAK_5] = {
        .species = SPECIES_MAROWAK,
        .moves = {MOVE_BONEMERANG, MOVE_KNOCK_OFF, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_THICK_CLUB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_BATTLE_ARMOR,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MAROWAK_6] = {
        .species = SPECIES_MAROWAK,
        .moves = {MOVE_BONEMERANG, MOVE_DOUBLE_EDGE, MOVE_KNOCK_OFF, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_THICK_CLUB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MAROWAK_ALOLA_5] = {
        .species = SPECIES_MAROWAK_ALOLA,
        .moves = {MOVE_FLAME_CHARGE, MOVE_FLARE_BLITZ, MOVE_SHADOW_BONE, MOVE_BONEMERANG},
        .heldItem = {ITEM_THICK_CLUB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MAROWAK_ALOLA_6] = {
        .species = SPECIES_MAROWAK_ALOLA,
        .moves = {MOVE_FLARE_BLITZ, MOVE_SHADOW_BONE, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_THICK_CLUB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_HITMONLEE_5] = {
        .species = SPECIES_HITMONLEE,
        .moves = {MOVE_FAKE_OUT, MOVE_CLOSE_COMBAT, MOVE_KNOCK_OFF, MOVE_POISON_JAB},
        .heldItem = {ITEM_NORMAL_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNBURDEN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_HITMONLEE_6] = {
        .species = SPECIES_HITMONLEE,
        .moves = {MOVE_HIGH_JUMP_KICK, MOVE_DOUBLE_EDGE, MOVE_STONE_EDGE, MOVE_MACH_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_RECKLESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HITMONCHAN_5] = {
        .species = SPECIES_HITMONCHAN,
        .moves = {MOVE_DRAIN_PUNCH, MOVE_MACH_PUNCH, MOVE_ICE_PUNCH, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_HITMONCHAN_6] = {
        .species = SPECIES_HITMONCHAN,
        .moves = {MOVE_DRAIN_PUNCH, MOVE_FACADE, MOVE_MACH_PUNCH, MOVE_THUNDER_PUNCH},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_WEEZING_5] = {
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_FLAMETHROWER, MOVE_THUNDERBOLT, MOVE_DARK_PULSE},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_NEUTRALIZING_GAS,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_WEEZING_6] = {
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_WILL_O_WISP, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CHANSEY_5] = {
        .species = SPECIES_CHANSEY,
        .moves = {MOVE_SEISMIC_TOSS, MOVE_THUNDER_WAVE, MOVE_SOFT_BOILED, MOVE_HEALING_WISH},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CHANSEY_6] = {
        .species = SPECIES_CHANSEY,
        .moves = {MOVE_SEISMIC_TOSS, MOVE_GRAVITY, MOVE_SOFT_BOILED, MOVE_TOXIC},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_KANGASKHAN_5] = {
        .species = SPECIES_KANGASKHAN,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_DRAIN_PUNCH, MOVE_EARTHQUAKE, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_KANGASKHAN_6] = {
        .species = SPECIES_KANGASKHAN,
        .moves = {MOVE_BODY_SLAM, MOVE_CRUNCH, MOVE_CURSE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_EARLY_BIRD,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_STARMIE_5] = {
        .species = SPECIES_STARMIE,
        .moves = {MOVE_SCALD, MOVE_PSYCHIC, MOVE_FLIP_TURN, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_STARMIE_6] = {
        .species = SPECIES_STARMIE,
        .moves = {MOVE_COSMIC_POWER, MOVE_STORED_POWER, MOVE_SURF, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MR_MIME_5] = {
        .species = SPECIES_MR_MIME,
        .moves = {MOVE_PSYCHIC, MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_ENCORE},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_FILTER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MR_MIME_6] = {
        .species = SPECIES_MR_MIME,
        .moves = {MOVE_CALM_MIND, MOVE_DAZZLING_GLEAM, MOVE_PSYSHOCK, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PINSIR_5] = {
        .species = SPECIES_PINSIR,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_X_SCISSOR, MOVE_CLOSE_COMBAT, MOVE_STONE_EDGE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PINSIR_6] = {
        .species = SPECIES_PINSIR,
        .moves = {MOVE_SWORDS_DANCE, MOVE_X_SCISSOR, MOVE_CLOSE_COMBAT, MOVE_QUICK_ATTACK},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TAUROS_5] = {
        .species = SPECIES_TAUROS,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_CLOSE_COMBAT, MOVE_EARTHQUAKE, MOVE_RAGING_BULL},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TAUROS_6] = {
        .species = SPECIES_TAUROS,
        .moves = {MOVE_BODY_SLAM, MOVE_FIRE_BLAST, MOVE_ICE_BEAM, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 4, 0),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_GYARADOS_5] = {
        .species = SPECIES_GYARADOS,
        .moves = {MOVE_WATERFALL, MOVE_DRAGON_TAIL, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_GYARADOS_6] = {
        .species = SPECIES_GYARADOS,
        .moves = {MOVE_DRAGON_DANCE, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_TAUNT},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LAPRAS_5] = {
        .species = SPECIES_LAPRAS,
        .moves = {MOVE_RAIN_DANCE, MOVE_FREEZE_DRY, MOVE_SURF, MOVE_REST},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_LAPRAS_6] = {
        .species = SPECIES_LAPRAS,
        .moves = {MOVE_HYDRO_PUMP, MOVE_FREEZE_DRY, MOVE_THUNDERBOLT, MOVE_PSYCHIC},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_DITTO_5] = {
        .species = SPECIES_DITTO,
        .moves = {MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_IMPOSTER,
        .nature = NATURE_RELAXED,
    },


    [FRONTIER_MON_DITTO_6] = {
        .species = SPECIES_DITTO,
        .moves = {MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_IMPOSTER,
        .nature = NATURE_RELAXED,
    },


    [FRONTIER_MON_VAPOREON_5] = {
        .species = SPECIES_VAPOREON,
        .moves = {MOVE_CALM_MIND, MOVE_SCALD, MOVE_ICE_BEAM, MOVE_WISH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_VAPOREON_6] = {
        .species = SPECIES_VAPOREON,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_RAIN_DANCE, MOVE_REST},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_JOLTEON_5] = {
        .species = SPECIES_JOLTEON,
        .moves = {MOVE_THUNDERBOLT, MOVE_SHADOW_BALL, MOVE_ALLURING_VOICE, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_JOLTEON_6] = {
        .species = SPECIES_JOLTEON,
        .moves = {MOVE_CALM_MIND, MOVE_THUNDERBOLT, MOVE_SHADOW_BALL, MOVE_ALLURING_VOICE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FLAREON_5] = {
        .species = SPECIES_FLAREON,
        .moves = {MOVE_CURSE, MOVE_FLARE_BLITZ, MOVE_FACADE, MOVE_WISH},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GUTS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_FLAREON_6] = {
        .species = SPECIES_FLAREON,
        .moves = {MOVE_CALM_MIND, MOVE_LAVA_PLUME, MOVE_SHADOW_BALL, MOVE_WISH},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_KABUTOPS_5] = {
        .species = SPECIES_KABUTOPS,
        .moves = {MOVE_SWORDS_DANCE, MOVE_LIQUIDATION, MOVE_STONE_EDGE, MOVE_LEECH_LIFE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_KABUTOPS_6] = {
        .species = SPECIES_KABUTOPS,
        .moves = {MOVE_LIQUIDATION, MOVE_STONE_EDGE, MOVE_KNOCK_OFF, MOVE_AQUA_JET},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_AERODACTYL_5] = {
        .species = SPECIES_AERODACTYL,
        .moves = {MOVE_STEALTH_ROCK, MOVE_TAUNT, MOVE_ROCK_TOMB, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNNERVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_AERODACTYL_6] = {
        .species = SPECIES_AERODACTYL,
        .moves = {MOVE_STONE_EDGE, MOVE_ROOST, MOVE_TAUNT, MOVE_TOXIC},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SNORLAX_6] = {
        .species = SPECIES_SNORLAX,
        .moves = {MOVE_FACADE, MOVE_CRUNCH, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_THICK_FAT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_SNORLAX_7] = {
        .species = SPECIES_SNORLAX,
        .moves = {MOVE_BODY_SLAM, MOVE_HIGH_HORSEPOWER, MOVE_HEAT_CRASH, MOVE_CRUNCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_THICK_FAT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MEGANIUM_5] = {
        .species = SPECIES_MEGANIUM,
        .moves = {MOVE_GROWTH, MOVE_GIGA_DRAIN, MOVE_DRAINING_KISS, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_OVERGROW,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MEGANIUM_6] = {
        .species = SPECIES_MEGANIUM,
        .moves = {MOVE_GIGA_DRAIN, MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_AROMATHERAPY},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_OVERGROW,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TYPHLOSION_5] = {
        .species = SPECIES_TYPHLOSION,
        .moves = {MOVE_FLARE_BLITZ, MOVE_EARTHQUAKE, MOVE_THUNDER_PUNCH, MOVE_OVERHEAT},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 4, 0),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_TYPHLOSION_6] = {
        .species = SPECIES_TYPHLOSION,
        .moves = {MOVE_SUBSTITUTE, MOVE_FLAMETHROWER, MOVE_FOCUS_BLAST, MOVE_SCORCHING_SANDS},
        .heldItem = {ITEM_PETAYA_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BLAZE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FERALIGATR_5] = {
        .species = SPECIES_FERALIGATR,
        .moves = {MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICE_PUNCH, MOVE_AQUA_JET},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_FERALIGATR_6] = {
        .species = SPECIES_FERALIGATR,
        .moves = {MOVE_DRAGON_DANCE, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MANDIBUZZ_3] = {
        .species = SPECIES_MANDIBUZZ,
        .moves = {MOVE_FOUL_PLAY, MOVE_U_TURN, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_OVERCOAT,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_MANDIBUZZ_4] = {
        .species = SPECIES_MANDIBUZZ,
        .moves = {MOVE_KNOCK_OFF, MOVE_TAUNT, MOVE_WHIRLWIND, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_OVERCOAT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_NOCTOWL_5] = {
        .species = SPECIES_NOCTOWL,
        .moves = {MOVE_HURRICANE, MOVE_HYPER_VOICE, MOVE_SHADOW_BALL, MOVE_MOONBLAST},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TINTED_LENS,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_NOCTOWL_6] = {
        .species = SPECIES_NOCTOWL,
        .moves = {MOVE_HURRICANE, MOVE_HYPNOSIS, MOVE_NIGHT_SHADE, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_INSOMNIA,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_ARIADOS_5] = {
        .species = SPECIES_ARIADOS,
        .moves = {MOVE_FOCUS_ENERGY, MOVE_CROSS_POISON, MOVE_MEGAHORN, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_SCOPE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SNIPER,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_ARIADOS_6] = {
        .species = SPECIES_ARIADOS,
        .moves = {MOVE_TOXIC, MOVE_INFESTATION, MOVE_LEECH_LIFE, MOVE_PROTECT},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_INSOMNIA,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CROBAT_5] = {
        .species = SPECIES_CROBAT,
        .moves = {MOVE_BRAVE_BIRD, MOVE_CROSS_POISON, MOVE_U_TURN, MOVE_LEECH_LIFE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_CROBAT_6] = {
        .species = SPECIES_CROBAT,
        .moves = {MOVE_BRAVE_BIRD, MOVE_SUPER_FANG, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LANTURN_5] = {
        .species = SPECIES_LANTURN,
        .moves = {MOVE_SCALD, MOVE_VOLT_SWITCH, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_LANTURN_6] = {
        .species = SPECIES_LANTURN,
        .moves = {MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_SURF, MOVE_ICE_BEAM},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_XATU_5] = {
        .species = SPECIES_XATU,
        .moves = {MOVE_PSYCHIC, MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_U_TURN},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_MAGIC_BOUNCE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_XATU_6] = {
        .species = SPECIES_XATU,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_HEAT_WAVE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MAGIC_BOUNCE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_AMPHAROS_6] = {
        .species = SPECIES_AMPHAROS,
        .moves = {MOVE_DISCHARGE, MOVE_DRAGON_PULSE, MOVE_FOCUS_BLAST, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_STATIC,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_AMPHAROS_7] = {
        .species = SPECIES_AMPHAROS,
        .moves = {MOVE_COTTON_GUARD, MOVE_DISCHARGE, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_STATIC,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_BELLOSSOM_5] = {
        .species = SPECIES_BELLOSSOM,
        .moves = {MOVE_GROWTH, MOVE_SOLAR_BLADE, MOVE_MOONBLAST, MOVE_WEATHER_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_BELLOSSOM_6] = {
        .species = SPECIES_BELLOSSOM,
        .moves = {MOVE_QUIVER_DANCE, MOVE_GIGA_DRAIN, MOVE_MOONBLAST, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_AZUMARILL_5] = {
        .species = SPECIES_AZUMARILL,
        .moves = {MOVE_WHIRLPOOL, MOVE_PERISH_SONG, MOVE_PROTECT, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_SAP_SIPPER,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_AZUMARILL_6] = {
        .species = SPECIES_AZUMARILL,
        .moves = {MOVE_LIQUIDATION, MOVE_PLAY_ROUGH, MOVE_SUPERPOWER, MOVE_AQUA_JET},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_HUGE_POWER,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SUDOWOODO_5] = {
        .species = SPECIES_SUDOWOODO,
        .moves = {MOVE_CURSE, MOVE_HEAD_SMASH, MOVE_WOOD_HAMMER, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_SUDOWOODO_6] = {
        .species = SPECIES_SUDOWOODO,
        .moves = {MOVE_STONE_EDGE, MOVE_EARTHQUAKE, MOVE_SUCKER_PUNCH, MOVE_COUNTER},
        .heldItem = {ITEM_WEAKNESS_POLICY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_POLITOED_5] = {
        .species = SPECIES_POLITOED,
        .moves = {MOVE_HYDRO_PUMP, MOVE_HYPER_VOICE, MOVE_ICE_BEAM, MOVE_FOCUS_BLAST},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_DRIZZLE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_POLITOED_6] = {
        .species = SPECIES_POLITOED,
        .moves = {MOVE_WHIRLPOOL, MOVE_PERISH_SONG, MOVE_ENCORE, MOVE_PROTECT},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_DRIZZLE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_JUMPLUFF_5] = {
        .species = SPECIES_JUMPLUFF,
        .moves = {MOVE_SUNNY_DAY, MOVE_SLEEP_POWDER, MOVE_U_TURN, MOVE_ENCORE},
        .heldItem = {ITEM_HEAT_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 252, 0, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_JUMPLUFF_6] = {
        .species = SPECIES_JUMPLUFF,
        .moves = {MOVE_TAILWIND, MOVE_ACROBATICS, MOVE_SEED_BOMB, MOVE_MEMENTO},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_QUAGSIRE_5] = {
        .species = SPECIES_QUAGSIRE,
        .moves = {MOVE_CURSE, MOVE_LIQUIDATION, MOVE_EARTHQUAKE, MOVE_RECOVER},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_QUAGSIRE_6] = {
        .species = SPECIES_QUAGSIRE,
        .moves = {MOVE_EARTHQUAKE, MOVE_SPIKES, MOVE_HAZE, MOVE_RECOVER},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_RELAXED,
    },


    [FRONTIER_MON_ESPEON_5] = {
        .species = SPECIES_ESPEON,
        .moves = {MOVE_PSYCHIC, MOVE_DAZZLING_GLEAM, MOVE_SHADOW_BALL, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MAGIC_BOUNCE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ESPEON_6] = {
        .species = SPECIES_ESPEON,
        .moves = {MOVE_PSYCHIC, MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_YAWN},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_MAGIC_BOUNCE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_UMBREON_5] = {
        .species = SPECIES_UMBREON,
        .moves = {MOVE_FOUL_PLAY, MOVE_TAUNT, MOVE_MOONLIGHT, MOVE_TOXIC},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INNER_FOCUS,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_UMBREON_6] = {
        .species = SPECIES_UMBREON,
        .moves = {MOVE_CALM_MIND, MOVE_DARK_PULSE, MOVE_MOONLIGHT, MOVE_SNARL},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SYNCHRONIZE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SLOWKING_5] = {
        .species = SPECIES_SLOWKING,
        .moves = {MOVE_FUTURE_SIGHT, MOVE_SCALD, MOVE_CHILLY_RECEPTION, MOVE_SLACK_OFF},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_SLOWKING_6] = {
        .species = SPECIES_SLOWKING,
        .moves = {MOVE_SURF, MOVE_PSYCHIC, MOVE_FIRE_BLAST, MOVE_ICE_BEAM},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_UNOWN_5] = {
        .species = SPECIES_UNOWN,
        .moves = {MOVE_HIDDEN_POWER, MOVE_NONE, MOVE_NONE, MOVE_NONE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 30, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_UNOWN_6] = {
        .species = SPECIES_UNOWN,
        .moves = {MOVE_HIDDEN_POWER, MOVE_NONE, MOVE_NONE, MOVE_NONE},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 30, 30, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_WOBBUFFET_5] = {
        .species = SPECIES_WOBBUFFET,
        .moves = {MOVE_COUNTER, MOVE_MIRROR_COAT, MOVE_ENCORE, MOVE_CHARM},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SHADOW_TAG,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_WOBBUFFET_6] = {
        .species = SPECIES_WOBBUFFET,
        .moves = {MOVE_COUNTER, MOVE_MIRROR_COAT, MOVE_ENCORE, MOVE_SAFEGUARD},
        .heldItem = {ITEM_MENTAL_HERB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_SHADOW_TAG,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_GIRAFARIG_5] = {
        .species = SPECIES_GIRAFARIG,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SAP_SIPPER,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_GIRAFARIG_6] = {
        .species = SPECIES_GIRAFARIG,
        .moves = {MOVE_HYPER_VOICE, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SAP_SIPPER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_DUNSPARCE_5] = {
        .species = SPECIES_DUNSPARCE,
        .moves = {MOVE_COIL, MOVE_BODY_SLAM, MOVE_EARTHQUAKE, MOVE_ROOST},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DUNSPARCE_6] = {
        .species = SPECIES_DUNSPARCE,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_FLAMETHROWER, MOVE_ROOST},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_GLIGAR_5] = {
        .species = SPECIES_GLIGAR,
        .moves = {MOVE_EARTHQUAKE, MOVE_U_TURN, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_IMMUNITY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_GLIGAR_6] = {
        .species = SPECIES_GLIGAR,
        .moves = {MOVE_SWORDS_DANCE, MOVE_EARTHQUAKE, MOVE_KNOCK_OFF, MOVE_ROOST},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_IMMUNITY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_STEELIX_6] = {
        .species = SPECIES_STEELIX,
        .moves = {MOVE_GYRO_BALL, MOVE_EARTHQUAKE, MOVE_STONE_EDGE, MOVE_EXPLOSION},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_RELAXED,
    },


    [FRONTIER_MON_STEELIX_7] = {
        .species = SPECIES_STEELIX,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_EARTHQUAKE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_QWILFISH_5] = {
        .species = SPECIES_QWILFISH,
        .moves = {MOVE_WATERFALL, MOVE_SPIKES, MOVE_TAUNT, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_QWILFISH_6] = {
        .species = SPECIES_QWILFISH,
        .moves = {MOVE_LIQUIDATION, MOVE_POISON_JAB, MOVE_AQUA_JET, MOVE_EXPLOSION},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },

    [FRONTIER_MON_SCIZOR_5] = {
        .species = SPECIES_SCIZOR,
        .moves = {MOVE_SWORDS_DANCE, MOVE_BULLET_PUNCH, MOVE_CLOSE_COMBAT, MOVE_ROOST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SCIZOR_6] = {
        .species = SPECIES_SCIZOR,
        .moves = {MOVE_BULLET_PUNCH, MOVE_U_TURN, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_HERACROSS_5] = {
        .species = SPECIES_HERACROSS,
        .moves = {MOVE_PIN_MISSILE, MOVE_CLOSE_COMBAT, MOVE_ROCK_BLAST, MOVE_BULLET_SEED},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GUTS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HERACROSS_6] = {
        .species = SPECIES_HERACROSS,
        .moves = {MOVE_PIN_MISSILE, MOVE_CLOSE_COMBAT, MOVE_ROCK_BLAST, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_URSARING_5] = {
        .species = SPECIES_URSARING,
        .moves = {MOVE_FACADE, MOVE_CLOSE_COMBAT, MOVE_CRUNCH, MOVE_PROTECT},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUICK_FEET,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_URSARING_6] = {
        .species = SPECIES_URSARING,
        .moves = {MOVE_BULK_UP, MOVE_BODY_SLAM, MOVE_CRUNCH, MOVE_REST},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GUTS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CORSOLA_5] = {
        .species = SPECIES_CORSOLA,
        .moves = {MOVE_SCALD, MOVE_POWER_GEM, MOVE_EARTH_POWER, MOVE_ICE_BEAM},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CORSOLA_6] = {
        .species = SPECIES_CORSOLA,
        .moves = {MOVE_CALM_MIND, MOVE_EARTH_POWER, MOVE_SCALD, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_DELIBIRD_5] = {
        .species = SPECIES_DELIBIRD,
        .moves = {MOVE_FAKE_OUT, MOVE_DOUBLE_EDGE, MOVE_BRAVE_BIRD, MOVE_ICE_SHARD},
        .heldItem = {ITEM_NORMAL_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_HUSTLE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DELIBIRD_6] = {
        .species = SPECIES_DELIBIRD,
        .moves = {MOVE_SPIKES, MOVE_RAPID_SPIN, MOVE_FREEZE_DRY, MOVE_DESTINY_BOND},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_INSOMNIA,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MANTINE_5] = {
        .species = SPECIES_MANTINE,
        .moves = {MOVE_RAIN_DANCE, MOVE_HYDRO_PUMP, MOVE_HURRICANE, MOVE_ICE_BEAM},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_MANTINE_6] = {
        .species = SPECIES_MANTINE,
        .moves = {MOVE_SCALD, MOVE_HAZE, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SKARMORY_5] = {
        .species = SPECIES_SKARMORY,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_SPIKES, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_SKARMORY_6] = {
        .species = SPECIES_SKARMORY,
        .moves = {MOVE_SPIKES, MOVE_STEALTH_ROCK, MOVE_TAUNT, MOVE_BRAVE_BIRD},
        .heldItem = {ITEM_CUSTAP_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HOUNDOOM_6] = {
        .species = SPECIES_HOUNDOOM,
        .moves = {MOVE_FIRE_BLAST, MOVE_DARK_PULSE, MOVE_SLUDGE_BOMB, MOVE_DESTINY_BOND},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_HOUNDOOM_7] = {
        .species = SPECIES_HOUNDOOM,
        .moves = {MOVE_NASTY_PLOT, MOVE_DARK_PULSE, MOVE_FLAMETHROWER, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_EARLY_BIRD,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_KINGDRA_5] = {
        .species = SPECIES_KINGDRA,
        .moves = {MOVE_FOCUS_ENERGY, MOVE_DRACO_METEOR, MOVE_HYDRO_PUMP, MOVE_AGILITY},
        .heldItem = {ITEM_SCOPE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SNIPER,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_KINGDRA_6] = {
        .species = SPECIES_KINGDRA,
        .moves = {MOVE_DRAGON_DANCE, MOVE_WATERFALL, MOVE_OUTRAGE, MOVE_IRON_HEAD},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DONPHAN_5] = {
        .species = SPECIES_DONPHAN,
        .moves = {MOVE_EARTHQUAKE, MOVE_HEAD_SMASH, MOVE_KNOCK_OFF, MOVE_ICE_SHARD},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DONPHAN_6] = {
        .species = SPECIES_DONPHAN,
        .moves = {MOVE_BODY_PRESS, MOVE_EARTHQUAKE, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_PORYGON2_5] = {
        .species = SPECIES_PORYGON2,
        .moves = {MOVE_AGILITY, MOVE_TRI_ATTACK, MOVE_SHADOW_BALL, MOVE_RECOVER},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_DOWNLOAD,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_PORYGON2_6] = {
        .species = SPECIES_PORYGON2,
        .moves = {MOVE_FOUL_PLAY, MOVE_DISCHARGE, MOVE_TOXIC, MOVE_RECOVER},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_TRACE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_STANTLER_5] = {
        .species = SPECIES_STANTLER,
        .moves = {MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_REST},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_STANTLER_6] = {
        .species = SPECIES_STANTLER,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_MEGAHORN, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HITMONTOP_5] = {
        .species = SPECIES_HITMONTOP,
        .moves = {MOVE_TRIPLE_AXEL, MOVE_MACH_PUNCH, MOVE_FAKE_OUT, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_HITMONTOP_6] = {
        .species = SPECIES_HITMONTOP,
        .moves = {MOVE_BULK_UP, MOVE_CLOSE_COMBAT, MOVE_MACH_PUNCH, MOVE_STONE_EDGE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MILTANK_5] = {
        .species = SPECIES_MILTANK,
        .moves = {MOVE_CURSE, MOVE_BODY_SLAM, MOVE_BODY_PRESS, MOVE_MILK_DRINK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MILTANK_6] = {
        .species = SPECIES_MILTANK,
        .moves = {MOVE_BODY_SLAM, MOVE_HEAL_BELL, MOVE_MILK_DRINK, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SAP_SIPPER,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_BLISSEY_5] = {
        .species = SPECIES_BLISSEY,
        .moves = {MOVE_SEISMIC_TOSS, MOVE_THUNDER_WAVE, MOVE_STEALTH_ROCK, MOVE_SOFT_BOILED},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_BLISSEY_6] = {
        .species = SPECIES_BLISSEY,
        .moves = {MOVE_CALM_MIND, MOVE_FLAMETHROWER, MOVE_SHADOW_BALL, MOVE_SOFT_BOILED},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SCEPTILE_5] = {
        .species = SPECIES_SCEPTILE,
        .moves = {MOVE_LEAF_BLADE, MOVE_ACROBATICS, MOVE_DRAIN_PUNCH, MOVE_SWORDS_DANCE},
        .heldItem = {ITEM_GRASS_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNBURDEN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SCEPTILE_6] = {
        .species = SPECIES_SCEPTILE,
        .moves = {MOVE_LEAF_STORM, MOVE_DRAGON_PULSE, MOVE_FOCUS_BLAST, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_OVERGROW,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_BLAZIKEN_5] = {
        .species = SPECIES_BLAZIKEN,
        .moves = {MOVE_FIRE_BLAST, MOVE_CLOSE_COMBAT, MOVE_VACUUM_WAVE, MOVE_PROTECT},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_BLAZIKEN_6] = {
        .species = SPECIES_BLAZIKEN,
        .moves = {MOVE_SWORDS_DANCE, MOVE_FIRE_PUNCH, MOVE_CLOSE_COMBAT, MOVE_THUNDER_PUNCH},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SWAMPERT_5] = {
        .species = SPECIES_SWAMPERT,
        .moves = {MOVE_STEALTH_ROCK, MOVE_EARTHQUAKE, MOVE_FLIP_TURN, MOVE_YAWN},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_SWAMPERT_6] = {
        .species = SPECIES_SWAMPERT,
        .moves = {MOVE_LIQUIDATION, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_LINOONE_5] = {
        .species = SPECIES_LINOONE,
        .moves = {MOVE_EXTREME_SPEED, MOVE_DOUBLE_EDGE, MOVE_STOMPING_TANTRUM, MOVE_SEED_BOMB},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GLUTTONY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_LINOONE_6] = {
        .species = SPECIES_LINOONE,
        .moves = {MOVE_TRICK, MOVE_EXTREME_SPEED, MOVE_GUNK_SHOT, MOVE_SEED_BOMB},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GLUTTONY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_FERROTHORN_5] = {
        .species = SPECIES_FERROTHORN,
        .moves = {MOVE_GYRO_BALL, MOVE_POWER_WHIP, MOVE_KNOCK_OFF, MOVE_BODY_PRESS},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_IRON_BARBS,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_FERROTHORN_6] = {
        .species = SPECIES_FERROTHORN,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_LEECH_SEED, MOVE_SPIKES},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_IRON_BARBS,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_GOGOAT_3] = {
        .species = SPECIES_GOGOAT,
        .moves = {MOVE_GRASSY_TERRAIN, MOVE_BULK_UP, MOVE_HORN_LEECH, MOVE_ROCK_SLIDE},
        .heldItem = {ITEM_GRASSY_SEED},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GRASS_PELT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_GOGOAT_4] = {
        .species = SPECIES_GOGOAT,
        .moves = {MOVE_HORN_LEECH, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_WILD_CHARGE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SAP_SIPPER,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_NINJASK_5] = {
        .species = SPECIES_NINJASK,
        .moves = {MOVE_SUBSTITUTE, MOVE_SWORDS_DANCE, MOVE_LEECH_LIFE, MOVE_ACROBATICS},
        .heldItem = {ITEM_LIECHI_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_NINJASK_6] = {
        .species = SPECIES_NINJASK,
        .moves = {MOVE_LEECH_LIFE, MOVE_U_TURN, MOVE_TOXIC, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SHEDINJA_5] = {
        .species = SPECIES_SHEDINJA,
        .moves = {MOVE_POLTERGEIST, MOVE_SHADOW_SNEAK, MOVE_TOXIC, MOVE_PROTECT},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_WONDER_GUARD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SHEDINJA_6] = {
        .species = SPECIES_SHEDINJA,
        .moves = {MOVE_X_SCISSOR, MOVE_SHADOW_SNEAK, MOVE_WILL_O_WISP, MOVE_PROTECT},
        .heldItem = {ITEM_SAFETY_GOGGLES},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_WONDER_GUARD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BRELOOM_5] = {
        .species = SPECIES_BRELOOM,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_SEED_BOMB, MOVE_SPORE},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_POISON_HEAL,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_BRELOOM_6] = {
        .species = SPECIES_BRELOOM,
        .moves = {MOVE_BULLET_SEED, MOVE_MACH_PUNCH, MOVE_FORCE_PALM, MOVE_ROCK_TOMB},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_PELIPPER_5] = {
        .species = SPECIES_PELIPPER,
        .moves = {MOVE_WEATHER_BALL, MOVE_HURRICANE, MOVE_ICE_BEAM, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_DRIZZLE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_PELIPPER_6] = {
        .species = SPECIES_PELIPPER,
        .moves = {MOVE_SCALD, MOVE_U_TURN, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_DRIZZLE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CLAYDOL_5] = {
        .species = SPECIES_CLAYDOL,
        .moves = {MOVE_CALM_MIND, MOVE_EARTH_POWER, MOVE_PSYCHIC, MOVE_ICE_BEAM},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ALLSEEING_IDOL,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CLAYDOL_6] = {
        .species = SPECIES_CLAYDOL,
        .moves = {MOVE_EARTH_POWER, MOVE_STEALTH_ROCK, MOVE_RAPID_SPIN, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_ALLSEEING_IDOL,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_TORKOAL_5] = {
        .species = SPECIES_TORKOAL,
        .moves = {MOVE_ERUPTION, MOVE_OVERHEAT, MOVE_SOLAR_BEAM, MOVE_EARTH_POWER},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_DROUGHT,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_TORKOAL_6] = {
        .species = SPECIES_TORKOAL,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_LAVA_PLUME, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_DROUGHT,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SABLEYE_5] = {
        .species = SPECIES_SABLEYE,
        .moves = {MOVE_CALM_MIND, MOVE_DARK_PULSE, MOVE_WILL_O_WISP, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SABLEYE_6] = {
        .species = SPECIES_SABLEYE,
        .moves = {MOVE_TRICK, MOVE_KNOCK_OFF, MOVE_ENCORE, MOVE_RECOVER},
        .heldItem = {ITEM_LAGGING_TAIL},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_WHISCASH_5] = {
        .species = SPECIES_WHISCASH,
        .moves = {MOVE_HYDRO_PUMP, MOVE_SURF, MOVE_EARTH_POWER, MOVE_ICE_BEAM},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_OBLIVIOUS,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_WHISCASH_6] = {
        .species = SPECIES_WHISCASH,
        .moves = {MOVE_DRAGON_DANCE, MOVE_LIQUIDATION, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_OBLIVIOUS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MILOTIC_5] = {
        .species = SPECIES_MILOTIC,
        .moves = {MOVE_HYDRO_PUMP, MOVE_ICE_BEAM, MOVE_ALLURING_VOICE, MOVE_FLIP_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_MILOTIC_6] = {
        .species = SPECIES_MILOTIC,
        .moves = {MOVE_SCALD, MOVE_DRAGON_TAIL, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MARVEL_SCALE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SHARPEDO_5] = {
        .species = SPECIES_SHARPEDO,
        .moves = {MOVE_HYDRO_PUMP, MOVE_DARK_PULSE, MOVE_ICE_BEAM, MOVE_PROTECT},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_SHARPEDO_6] = {
        .species = SPECIES_SHARPEDO,
        .moves = {MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_CLOSE_COMBAT, MOVE_FLIP_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ROUGH_SKIN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_FLYGON_5] = {
        .species = SPECIES_FLYGON,
        .moves = {MOVE_DRACO_METEOR, MOVE_EARTH_POWER, MOVE_BOOMBURST, MOVE_FLAMETHROWER},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FLYGON_6] = {
        .species = SPECIES_FLYGON,
        .moves = {MOVE_EARTHQUAKE, MOVE_U_TURN, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HARIYAMA_5] = {
        .species = SPECIES_HARIYAMA,
        .moves = {MOVE_DRAIN_PUNCH, MOVE_KNOCK_OFF, MOVE_BULLET_PUNCH, MOVE_FAKE_OUT},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_THICK_FAT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_HARIYAMA_6] = {
        .species = SPECIES_HARIYAMA,
        .moves = {MOVE_DRAIN_PUNCH, MOVE_KNOCK_OFF, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GUTS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MANECTRIC_6] = {
        .species = SPECIES_MANECTRIC,
        .moves = {MOVE_THUNDERBOLT, MOVE_FLAMETHROWER, MOVE_VOLT_SWITCH, MOVE_SNARL},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LIGHTNING_ROD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MANECTRIC_7] = {
        .species = SPECIES_MANECTRIC,
        .moves = {MOVE_CHARGE_BEAM, MOVE_FLAMETHROWER, MOVE_SUBSTITUTE, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LIGHTNING_ROD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_CAMERUPT_5] = {
        .species = SPECIES_CAMERUPT,
        .moves = {MOVE_CURSE, MOVE_EARTHQUAKE, MOVE_HEAT_CRASH, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SOLID_ROCK,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CAMERUPT_6] = {
        .species = SPECIES_CAMERUPT,
        .moves = {MOVE_ERUPTION, MOVE_FIRE_BLAST, MOVE_EARTH_POWER, MOVE_FLASH_CANNON},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_SOLID_ROCK,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_WALREIN_5] = {
        .species = SPECIES_WALREIN,
        .moves = {MOVE_BLIZZARD, MOVE_SURF, MOVE_ICE_BEAM, MOVE_SIGNAL_BEAM},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ICE_BODY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_WALREIN_6] = {
        .species = SPECIES_WALREIN,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_THICK_FAT,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CACTURNE_5] = {
        .species = SPECIES_CACTURNE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_SEED_BOMB, MOVE_SUCKER_PUNCH, MOVE_DRAIN_PUNCH},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_CACTURNE_6] = {
        .species = SPECIES_CACTURNE,
        .moves = {MOVE_LEAF_STORM, MOVE_DARK_PULSE, MOVE_FOCUS_BLAST, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GLALIE_5] = {
        .species = SPECIES_GLALIE,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_EXPLOSION},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INNER_FOCUS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GLALIE_6] = {
        .species = SPECIES_GLALIE,
        .moves = {MOVE_FREEZE_DRY, MOVE_TAUNT, MOVE_SPIKES, MOVE_EXPLOSION},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_ICE_BODY,
        .nature = NATURE_TIMID,
    },

    [FRONTIER_MON_MAWILE_5] = {
        .species = SPECIES_MAWILE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_PLAY_ROUGH, MOVE_SUCKER_PUNCH, MOVE_FIRE_FANG},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MAWILE_6] = {
        .species = SPECIES_MAWILE,
        .moves = {MOVE_PLAY_ROUGH, MOVE_IRON_HEAD, MOVE_KNOCK_OFF, MOVE_ICE_PUNCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MEDICHAM_5] = {
        .species = SPECIES_MEDICHAM,
        .moves = {MOVE_HIGH_JUMP_KICK, MOVE_PSYCHO_CUT, MOVE_ICE_PUNCH, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PURE_POWER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MEDICHAM_6] = {
        .species = SPECIES_MEDICHAM,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_PSYCHO_CUT, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_PURE_POWER,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_ALTARIA_6] = {
        .species = SPECIES_ALTARIA,
        .moves = {MOVE_COTTON_GUARD, MOVE_FLAMETHROWER, MOVE_DRAGON_PULSE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_ALTARIA_7] = {
        .species = SPECIES_ALTARIA,
        .moves = {MOVE_DRACO_METEOR, MOVE_FLAMETHROWER, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_CLOUD_NINE,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_TROPIUS_5] = {
        .species = SPECIES_TROPIUS,
        .moves = {MOVE_DRAGON_DANCE, MOVE_LEAF_BLADE, MOVE_EARTHQUAKE, MOVE_ROOST},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_HARVEST,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_TROPIUS_6] = {
        .species = SPECIES_TROPIUS,
        .moves = {MOVE_LEAF_STORM, MOVE_AIR_SLASH, MOVE_DRAGON_PULSE, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SOLAR_POWER,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_ABSOL_5] = {
        .species = SPECIES_ABSOL,
        .moves = {MOVE_KNOCK_OFF, MOVE_SUCKER_PUNCH, MOVE_CLOSE_COMBAT, MOVE_PLAY_ROUGH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SUPER_LUCK,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ABSOL_6] = {
        .species = SPECIES_ABSOL,
        .moves = {MOVE_NIGHT_SLASH, MOVE_PSYCHO_CUT, MOVE_STONE_EDGE, MOVE_CLOSE_COMBAT},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SUPER_LUCK,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BANETTE_5] = {
        .species = SPECIES_BANETTE,
        .moves = {MOVE_POLTERGEIST, MOVE_KNOCK_OFF, MOVE_GUNK_SHOT, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INSOMNIA,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BANETTE_6] = {
        .species = SPECIES_BANETTE,
        .moves = {MOVE_CURSE, MOVE_PAIN_SPLIT, MOVE_WILL_O_WISP, MOVE_SHADOW_SNEAK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_AGGRON_5] = {
        .species = SPECIES_AGGRON,
        .moves = {MOVE_ROCK_POLISH, MOVE_HEAD_SMASH, MOVE_HEAVY_SLAM, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 252, 252, 0, 0),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_AGGRON_6] = {
        .species = SPECIES_AGGRON,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_HEAVY_SLAM, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 4, 0, 0, 252),
        .ability = ABILITY_STURDY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CRADILY_5] = {
        .species = SPECIES_CRADILY,
        .moves = {MOVE_STOCKPILE, MOVE_GIGA_DRAIN, MOVE_EARTH_POWER, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CRADILY_6] = {
        .species = SPECIES_CRADILY,
        .moves = {MOVE_STEALTH_ROCK, MOVE_GIGA_DRAIN, MOVE_TOXIC, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_GARDEVOIR_5] = {
        .species = SPECIES_GARDEVOIR,
        .moves = {MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_PSYSHOCK, MOVE_DRAINING_KISS},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TRACE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GARDEVOIR_6] = {
        .species = SPECIES_GARDEVOIR,
        .moves = {MOVE_MOONBLAST, MOVE_PSYSHOCK, MOVE_FOCUS_BLAST, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TRACE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_CHIMECHO_5] = {
        .species = SPECIES_CHIMECHO,
        .moves = {MOVE_EXPANDING_FORCE, MOVE_HYPER_VOICE, MOVE_DAZZLING_GLEAM, MOVE_SHADOW_BALL},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_MIND_FLOAT,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CHIMECHO_6] = {
        .species = SPECIES_CHIMECHO,
        .moves = {MOVE_TRICK_ROOM, MOVE_EXPANDING_FORCE, MOVE_DAZZLING_GLEAM, MOVE_RECOVER},
        .heldItem = {ITEM_TERRAIN_EXTENDER},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_MIND_FLOAT,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_TORTERRA_5] = {
        .species = SPECIES_TORTERRA,
        .moves = {MOVE_SHELL_SMASH, MOVE_BULLET_SEED, MOVE_HEADLONG_RUSH, MOVE_ROCK_BLAST},
        .heldItem = {ITEM_WHITE_HERB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHELL_ARMOR,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_TORTERRA_6] = {
        .species = SPECIES_TORTERRA,
        .moves = {MOVE_CURSE, MOVE_SEED_BOMB, MOVE_EARTHQUAKE, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SHELL_ARMOR,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_INFERNAPE_5] = {
        .species = SPECIES_INFERNAPE,
        .moves = {MOVE_STEALTH_ROCK, MOVE_FIRE_BLAST, MOVE_CLOSE_COMBAT, MOVE_TAUNT},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_BLAZE,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_INFERNAPE_6] = {
        .species = SPECIES_INFERNAPE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_DRAIN_PUNCH, MOVE_FIRE_PUNCH, MOVE_MACH_PUNCH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_EMPOLEON_5] = {
        .species = SPECIES_EMPOLEON,
        .moves = {MOVE_HYDRO_PUMP, MOVE_FLASH_CANNON, MOVE_ICE_BEAM, MOVE_GRASS_KNOT},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_EMPOLEON_6] = {
        .species = SPECIES_EMPOLEON,
        .moves = {MOVE_SURF, MOVE_ROOST, MOVE_STEALTH_ROCK, MOVE_HAZE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_STARAPTOR_5] = {
        .species = SPECIES_STARAPTOR,
        .moves = {MOVE_BRAVE_BIRD, MOVE_CLOSE_COMBAT, MOVE_ROOST, MOVE_QUICK_ATTACK},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_RECKLESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_STARAPTOR_6] = {
        .species = SPECIES_STARAPTOR,
        .moves = {MOVE_BRAVE_BIRD, MOVE_ENDEAVOR, MOVE_TAILWIND, MOVE_U_TURN},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LUXRAY_5] = {
        .species = SPECIES_LUXRAY,
        .moves = {MOVE_WILD_CHARGE, MOVE_FACADE, MOVE_CRUNCH, MOVE_ICE_FANG},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GUTS,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_LUXRAY_6] = {
        .species = SPECIES_LUXRAY,
        .moves = {MOVE_THUNDERBOLT, MOVE_VOLT_SWITCH, MOVE_SNARL, MOVE_PSYCHIC_FANGS},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_ROSERADE_5] = {
        .species = SPECIES_ROSERADE,
        .moves = {MOVE_GROWTH, MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_DAZZLING_GLEAM},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ROSERADE_6] = {
        .species = SPECIES_ROSERADE,
        .moves = {MOVE_LEAF_STORM, MOVE_SLUDGE_BOMB, MOVE_SLEEP_POWDER, MOVE_TOXIC_SPIKES},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FLOATZEL_5] = {
        .species = SPECIES_FLOATZEL,
        .moves = {MOVE_WAVE_CRASH, MOVE_AQUA_JET, MOVE_ICE_SPINNER, MOVE_FLIP_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_FLOATZEL_6] = {
        .species = SPECIES_FLOATZEL,
        .moves = {MOVE_BULK_UP, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_TAUNT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_WATER_VEIL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GASTRODON_5] = {
        .species = SPECIES_GASTRODON_WEST,
        .moves = {MOVE_SCALD, MOVE_EARTH_POWER, MOVE_ICE_BEAM, MOVE_SLUDGE_BOMB},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GASTRODON_6] = {
        .species = SPECIES_GASTRODON_WEST,
        .moves = {MOVE_SPIKES, MOVE_EARTH_POWER, MOVE_CLEAR_SMOG, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_AMBIPOM_5] = {
        .species = SPECIES_AMBIPOM,
        .moves = {MOVE_TAIL_SLAP, MOVE_LOW_KICK, MOVE_TRIPLE_AXEL, MOVE_U_TURN},
        .heldItem = {ITEM_LOADED_DICE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_AMBIPOM_6] = {
        .species = SPECIES_AMBIPOM,
        .moves = {MOVE_DOUBLE_HIT, MOVE_KNOCK_OFF, MOVE_LOW_KICK, MOVE_SWITCHEROO},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DRIFBLIM_5] = {
        .species = SPECIES_DRIFBLIM,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_THUNDERBOLT, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_UNBURDEN,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_DRIFBLIM_6] = {
        .species = SPECIES_DRIFBLIM,
        .moves = {MOVE_ACROBATICS, MOVE_PHANTOM_FORCE, MOVE_TAILWIND, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_FLYING_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNBURDEN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_LOPUNNY_5] = {
        .species = SPECIES_LOPUNNY,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_CLOSE_COMBAT, MOVE_TRIPLE_AXEL, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_LIMBER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LOPUNNY_6] = {
        .species = SPECIES_LOPUNNY,
        .moves = {MOVE_SWITCHEROO, MOVE_ENCORE, MOVE_DRAIN_PUNCH, MOVE_HEALING_WISH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_KLUTZ,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MISMAGIUS_5] = {
        .species = SPECIES_MISMAGIUS,
        .moves = {MOVE_SHADOW_BALL, MOVE_DAZZLING_GLEAM, MOVE_MYSTICAL_FIRE, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MISMAGIUS_6] = {
        .species = SPECIES_MISMAGIUS,
        .moves = {MOVE_HEX, MOVE_WILL_O_WISP, MOVE_SUBSTITUTE, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_HONCHKROW_5] = {
        .species = SPECIES_HONCHKROW,
        .moves = {MOVE_BRAVE_BIRD, MOVE_NIGHT_SLASH, MOVE_SUPERPOWER, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HONCHKROW_6] = {
        .species = SPECIES_HONCHKROW,
        .moves = {MOVE_BRAVE_BIRD, MOVE_SUCKER_PUNCH, MOVE_HEAT_WAVE, MOVE_ROOST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 4, 0),
        .ability = ABILITY_SUPER_LUCK,
        .nature = NATURE_NAUGHTY,
    },


    [FRONTIER_MON_SPIRITOMB_5] = {
        .species = SPECIES_SPIRITOMB,
        .moves = {MOVE_CALM_MIND, MOVE_DARK_PULSE, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SPIRITOMB_6] = {
        .species = SPECIES_SPIRITOMB,
        .moves = {MOVE_POLTERGEIST, MOVE_SUCKER_PUNCH, MOVE_PURSUIT, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_LUCARIO_5] = {
        .species = SPECIES_LUCARIO,
        .moves = {MOVE_NASTY_PLOT, MOVE_AURA_SPHERE, MOVE_FLASH_CANNON, MOVE_VACUUM_WAVE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_INNER_FOCUS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LUCARIO_6] = {
        .species = SPECIES_LUCARIO,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_METEOR_MASH, MOVE_CRUNCH, MOVE_EXTREME_SPEED},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INNER_FOCUS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HIPPOWDON_6] = {
        .species = SPECIES_HIPPOWDON,
        .moves = {MOVE_EARTHQUAKE, MOVE_STONE_EDGE, MOVE_ICE_FANG, MOVE_CRUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SAND_STREAM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_HIPPOWDON_7] = {
        .species = SPECIES_HIPPOWDON,
        .moves = {MOVE_BODY_PRESS, MOVE_WHIRLWIND, MOVE_STEALTH_ROCK, MOVE_SLACK_OFF},
        .heldItem = {ITEM_SMOOTH_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SAND_STREAM,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_DRAPION_5] = {
        .species = SPECIES_DRAPION,
        .moves = {MOVE_AGILITY, MOVE_CROSS_POISON, MOVE_NIGHT_SLASH, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_SCOPE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SNIPER,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DRAPION_6] = {
        .species = SPECIES_DRAPION,
        .moves = {MOVE_SWORDS_DANCE, MOVE_KNOCK_OFF, MOVE_POISON_JAB, MOVE_TAUNT},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_BATTLE_ARMOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LUMINEON_5] = {
        .species = SPECIES_LUMINEON,
        .moves = {MOVE_RAIN_DANCE, MOVE_SURF, MOVE_ICE_BEAM, MOVE_U_TURN},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_LUMINEON_6] = {
        .species = SPECIES_LUMINEON,
        .moves = {MOVE_SCALD, MOVE_U_TURN, MOVE_ENCORE, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_ABOMASNOW_5] = {
        .species = SPECIES_ABOMASNOW,
        .moves = {MOVE_BLIZZARD, MOVE_LEAF_STORM, MOVE_EARTH_POWER, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SNOW_WARNING,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_ABOMASNOW_6] = {
        .species = SPECIES_ABOMASNOW,
        .moves = {MOVE_AURORA_VEIL, MOVE_BLIZZARD, MOVE_LEECH_SEED, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_SNOW_WARNING,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_WEAVILE_5] = {
        .species = SPECIES_WEAVILE,
        .moves = {MOVE_BEAT_UP, MOVE_TRIPLE_AXEL, MOVE_ICE_SHARD, MOVE_LOW_KICK},
        .heldItem = {ITEM_LOADED_DICE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_WEAVILE_6] = {
        .species = SPECIES_WEAVILE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_ICICLE_CRASH, MOVE_KNOCK_OFF, MOVE_LOW_KICK},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MAGNEZONE_5] = {
        .species = SPECIES_MAGNEZONE,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_THUNDERBOLT, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MAGNET_PULL,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MAGNEZONE_6] = {
        .species = SPECIES_MAGNEZONE,
        .moves = {MOVE_THUNDERBOLT, MOVE_FLASH_CANNON, MOVE_VOLT_SWITCH, MOVE_TRI_ATTACK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_ANALYTIC,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_LICKILICKY_5] = {
        .species = SPECIES_LICKILICKY,
        .moves = {MOVE_CURSE, MOVE_BODY_SLAM, MOVE_KNOCK_OFF, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_OBLIVIOUS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_LICKILICKY_6] = {
        .species = SPECIES_LICKILICKY,
        .moves = {MOVE_SURF, MOVE_FIRE_BLAST, MOVE_ICE_BEAM, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_CLOUD_NINE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_RHYPERIOR_6] = {
        .species = SPECIES_RHYPERIOR,
        .moves = {MOVE_SWORDS_DANCE, MOVE_STONE_EDGE, MOVE_EARTHQUAKE, MOVE_FIRE_PUNCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SOLID_ROCK,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_RHYPERIOR_7] = {
        .species = SPECIES_RHYPERIOR,
        .moves = {MOVE_ROCK_BLAST, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_DRAGON_TAIL},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SOLID_ROCK,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_TANGROWTH_6] = {
        .species = SPECIES_TANGROWTH,
        .moves = {MOVE_POWER_WHIP, MOVE_EARTHQUAKE, MOVE_KNOCK_OFF, MOVE_ROCK_SLIDE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_TANGROWTH_7] = {
        .species = SPECIES_TANGROWTH,
        .moves = {MOVE_GIGA_DRAIN, MOVE_EARTHQUAKE, MOVE_LEECH_SEED, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_RELAXED,
    },


    [FRONTIER_MON_ELECTIVIRE_5] = {
        .species = SPECIES_ELECTIVIRE,
        .moves = {MOVE_THUNDER, MOVE_FOCUS_BLAST, MOVE_FLAMETHROWER, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VITAL_SPIRIT,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ELECTIVIRE_6] = {
        .species = SPECIES_ELECTIVIRE,
        .moves = {MOVE_THUNDER_PUNCH, MOVE_CROSS_CHOP, MOVE_ICE_PUNCH, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 4, 0),
        .ability = ABILITY_MOTOR_DRIVE,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_MAGMORTAR_5] = {
        .species = SPECIES_MAGMORTAR,
        .moves = {MOVE_FLAMETHROWER, MOVE_THUNDERBOLT, MOVE_FOCUS_BLAST, MOVE_SCORCHING_SANDS},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_VITAL_SPIRIT,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_MAGMORTAR_6] = {
        .species = SPECIES_MAGMORTAR,
        .moves = {MOVE_SUNNY_DAY, MOVE_FIRE_BLAST, MOVE_SOLAR_BEAM, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_HEAT_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VITAL_SPIRIT,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TOGEKISS_5] = {
        .species = SPECIES_TOGEKISS,
        .moves = {MOVE_NASTY_PLOT, MOVE_AIR_SLASH, MOVE_AURA_SPHERE, MOVE_ROOST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TOGEKISS_6] = {
        .species = SPECIES_TOGEKISS,
        .moves = {MOVE_AIR_SLASH, MOVE_DAZZLING_GLEAM, MOVE_FIRE_BLAST, MOVE_ROOST},
        .heldItem = {ITEM_SCOPE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SUPER_LUCK,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_YANMEGA_5] = {
        .species = SPECIES_YANMEGA,
        .moves = {MOVE_SUBSTITUTE, MOVE_BUG_BUZZ, MOVE_AIR_SLASH, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_YANMEGA_6] = {
        .species = SPECIES_YANMEGA,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_LEECH_LIFE, MOVE_QUICK_ATTACK, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TINTED_LENS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LEAFEON_5] = {
        .species = SPECIES_LEAFEON,
        .moves = {MOVE_LEAF_BLADE, MOVE_KNOCK_OFF, MOVE_X_SCISSOR, MOVE_DOUBLE_EDGE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LEAFEON_6] = {
        .species = SPECIES_LEAFEON,
        .moves = {MOVE_SWORDS_DANCE, MOVE_LEAF_BLADE, MOVE_KNOCK_OFF, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_JOLLY,
    },

    [FRONTIER_MON_GLACEON_6] = {
        .species = SPECIES_GLACEON,
        .moves = {MOVE_SNOWSCAPE, MOVE_BLIZZARD, MOVE_FREEZE_DRY, MOVE_SHADOW_BALL},
        .heldItem = {ITEM_ICY_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ICE_BODY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GLACEON_7] = {
        .species = SPECIES_GLACEON,
        .moves = {MOVE_CALM_MIND, MOVE_ICE_BEAM, MOVE_WISH, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_ICE_BODY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_GLISCOR_5] = {
        .species = SPECIES_GLISCOR,
        .moves = {MOVE_SPIKES, MOVE_EARTHQUAKE, MOVE_U_TURN, MOVE_PROTECT},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_POISON_HEAL,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_GLISCOR_6] = {
        .species = SPECIES_GLISCOR,
        .moves = {MOVE_SWORDS_DANCE, MOVE_EARTHQUAKE, MOVE_KNOCK_OFF, MOVE_TAUNT},
        .heldItem = {ITEM_TOXIC_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_POISON_HEAL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MAMOSWINE_6] = {
        .species = SPECIES_MAMOSWINE,
        .moves = {MOVE_ICICLE_CRASH, MOVE_EARTHQUAKE, MOVE_ICE_SHARD, MOVE_SUPERPOWER},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_THICK_FAT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MAMOSWINE_7] = {
        .species = SPECIES_MAMOSWINE,
        .moves = {MOVE_CURSE, MOVE_ICICLE_SPEAR, MOVE_EARTHQUAKE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_THICK_FAT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_PORYGON_Z_5] = {
        .species = SPECIES_PORYGON_Z,
        .moves = {MOVE_TRI_ATTACK, MOVE_SHADOW_BALL, MOVE_THUNDERBOLT, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PORYGON_Z_6] = {
        .species = SPECIES_PORYGON_Z,
        .moves = {MOVE_AGILITY, MOVE_TRI_ATTACK, MOVE_SHADOW_BALL, MOVE_ICE_BEAM},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_DOWNLOAD,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GALLADE_6] = {
        .species = SPECIES_GALLADE,
        .moves = {MOVE_SACRED_SWORD, MOVE_PSYCHO_CUT, MOVE_LEAF_BLADE, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHARPNESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GALLADE_7] = {
        .species = SPECIES_GALLADE,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_PSYCHO_CUT, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SHARPNESS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_PROBOPASS_5] = {
        .species = SPECIES_PROBOPASS,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_FLASH_CANNON, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MAGNET_PULL,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_PROBOPASS_6] = {
        .species = SPECIES_PROBOPASS,
        .moves = {MOVE_FLASH_CANNON, MOVE_POWER_GEM, MOVE_EARTH_POWER, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_DUSKNOIR_5] = {
        .species = SPECIES_DUSKNOIR,
        .moves = {MOVE_POLTERGEIST, MOVE_SHADOW_SNEAK, MOVE_ICE_PUNCH, MOVE_THUNDER_PUNCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_FRISK,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DUSKNOIR_6] = {
        .species = SPECIES_DUSKNOIR,
        .moves = {MOVE_NIGHT_SHADE, MOVE_WILL_O_WISP, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_FROSLASS_6] = {
        .species = SPECIES_FROSLASS,
        .moves = {MOVE_ICE_BEAM, MOVE_SHADOW_BALL, MOVE_THUNDERBOLT, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FROSLASS_7] = {
        .species = SPECIES_FROSLASS,
        .moves = {MOVE_SPIKES, MOVE_TAUNT, MOVE_ICE_BEAM, MOVE_DESTINY_BOND},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SERPERIOR_5] = {
        .species = SPECIES_SERPERIOR,
        .moves = {MOVE_LEAF_STORM, MOVE_DRAGON_PULSE, MOVE_GLARE, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CONTRARY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SERPERIOR_6] = {
        .species = SPECIES_SERPERIOR,
        .moves = {MOVE_LEAF_STORM, MOVE_DRAGON_PULSE, MOVE_KNOCK_OFF, MOVE_GLARE},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CONTRARY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_EMBOAR_5] = {
        .species = SPECIES_EMBOAR,
        .moves = {MOVE_FLARE_BLITZ, MOVE_CLOSE_COMBAT, MOVE_WILD_CHARGE, MOVE_HEAD_SMASH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_RECKLESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_EMBOAR_6] = {
        .species = SPECIES_EMBOAR,
        .moves = {MOVE_FIRE_BLAST, MOVE_CLOSE_COMBAT, MOVE_GRASS_KNOT, MOVE_SCALD},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_RECKLESS,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_SAMUROTT_5] = {
        .species = SPECIES_SAMUROTT,
        .moves = {MOVE_RAZOR_SHELL, MOVE_SACRED_SWORD, MOVE_MEGAHORN, MOVE_AQUA_JET},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHELL_ARMOR,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SAMUROTT_6] = {
        .species = SPECIES_SAMUROTT,
        .moves = {MOVE_WORK_UP, MOVE_HYDRO_PUMP, MOVE_ICE_BEAM, MOVE_SACRED_SWORD},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_EXCADRILL_5] = {
        .species = SPECIES_EXCADRILL,
        .moves = {MOVE_EARTHQUAKE, MOVE_IRON_HEAD, MOVE_ROCK_SLIDE, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },

    [FRONTIER_MON_EXCADRILL_6] = {
        .species = SPECIES_EXCADRILL,
        .moves = {MOVE_SWORDS_DANCE, MOVE_EARTHQUAKE, MOVE_IRON_HEAD, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_AIR_BALLOON},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SAND_RUSH,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_AUDINO_6] = {
        .species = SPECIES_AUDINO,
        .moves = {MOVE_HYPER_VOICE, MOVE_DAZZLING_GLEAM, MOVE_FIRE_BLAST, MOVE_ICE_BEAM},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_AUDINO_7] = {
        .species = SPECIES_AUDINO,
        .moves = {MOVE_KNOCK_OFF, MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_HEALING_WISH},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_LEAVANNY_5] = {
        .species = SPECIES_LEAVANNY,
        .moves = {MOVE_LEAF_BLADE, MOVE_X_SCISSOR, MOVE_KNOCK_OFF, MOVE_POISON_JAB},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LEAVANNY_6] = {
        .species = SPECIES_LEAVANNY,
        .moves = {MOVE_SUNNY_DAY, MOVE_STICKY_WEB, MOVE_LEAF_BLADE, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SCOLIPEDE_5] = {
        .species = SPECIES_SCOLIPEDE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_POISON_JAB, MOVE_MEGAHORN, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SCOLIPEDE_6] = {
        .species = SPECIES_SCOLIPEDE,
        .moves = {MOVE_MEGAHORN, MOVE_POISON_JAB, MOVE_EARTHQUAKE, MOVE_AQUA_TAIL},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_WHIMSICOTT_6] = {
        .species = SPECIES_WHIMSICOTT,
        .moves = {MOVE_SUNNY_DAY, MOVE_MOONBLAST, MOVE_ENCORE, MOVE_U_TURN},
        .heldItem = {ITEM_HEAT_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_WHIMSICOTT_7] = {
        .species = SPECIES_WHIMSICOTT,
        .moves = {MOVE_MOONBLAST, MOVE_LEECH_SEED, MOVE_SUBSTITUTE, MOVE_ENCORE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LILLIGANT_6] = {
        .species = SPECIES_LILLIGANT,
        .moves = {MOVE_QUIVER_DANCE, MOVE_GIGA_DRAIN, MOVE_POLLEN_PUFF, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_OWN_TEMPO,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LILLIGANT_7] = {
        .species = SPECIES_LILLIGANT,
        .moves = {MOVE_LEAF_STORM, MOVE_ENERGY_BALL, MOVE_POLLEN_PUFF, MOVE_HEALING_WISH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_BASCULIN_RED_STRIPED_4] = {
        .species = SPECIES_BASCULIN_RED_STRIPED,
        .moves = {MOVE_WAVE_CRASH, MOVE_AQUA_JET, MOVE_CRUNCH, MOVE_SUPERPOWER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BASCULIN_RED_STRIPED_5] = {
        .species = SPECIES_BASCULIN_RED_STRIPED,
        .moves = {MOVE_WAVE_CRASH, MOVE_HEAD_SMASH, MOVE_PSYCHIC_FANGS, MOVE_FLIP_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BASCULIN_BLUE_STRIPED_3] = {
        .species = SPECIES_BASCULIN_BLUE_STRIPED,
        .moves = {MOVE_AGILITY, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICE_FANG},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BASCULIN_BLUE_STRIPED_4] = {
        .species = SPECIES_BASCULIN_BLUE_STRIPED,
        .moves = {MOVE_WAVE_CRASH, MOVE_HEAD_SMASH, MOVE_AQUA_JET, MOVE_ENDEAVOR},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_KROOKODILE_5] = {
        .species = SPECIES_KROOKODILE,
        .moves = {MOVE_EARTHQUAKE, MOVE_KNOCK_OFF, MOVE_CLOSE_COMBAT, MOVE_GUNK_SHOT},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_KROOKODILE_6] = {
        .species = SPECIES_KROOKODILE,
        .moves = {MOVE_EARTHQUAKE, MOVE_KNOCK_OFF, MOVE_STEALTH_ROCK, MOVE_DRAGON_TAIL},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_DARMANITAN_5] = {
        .species = SPECIES_DARMANITAN_STANDARD,
        .moves = {MOVE_FLARE_BLITZ, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DARMANITAN_6] = {
        .species = SPECIES_DARMANITAN_STANDARD,
        .moves = {MOVE_BULK_UP, MOVE_FIRE_PUNCH, MOVE_HAMMER_ARM, MOVE_ROCK_SLIDE},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MARACTUS_5] = {
        .species = SPECIES_MARACTUS,
        .moves = {MOVE_SUNNY_DAY, MOVE_SOLAR_BEAM, MOVE_WEATHER_BALL, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_MARACTUS_6] = {
        .species = SPECIES_MARACTUS,
        .moves = {MOVE_GIGA_DRAIN, MOVE_LEECH_SEED, MOVE_SPIKES, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SCRAFTY_5] = {
        .species = SPECIES_SCRAFTY,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_KNOCK_OFF, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SHED_SKIN,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_SCRAFTY_6] = {
        .species = SPECIES_SCRAFTY,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_KNOCK_OFF, MOVE_ICE_PUNCH, MOVE_POISON_JAB},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_COFAGRIGUS_5] = {
        .species = SPECIES_COFAGRIGUS,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_SHADOW_BALL, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MUMMY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_COFAGRIGUS_6] = {
        .species = SPECIES_COFAGRIGUS,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MUMMY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_ARCHEOPS_5] = {
        .species = SPECIES_ARCHEOPS,
        .moves = {MOVE_HEAD_SMASH, MOVE_DUAL_WINGBEAT, MOVE_EARTHQUAKE, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFEATIST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ARCHEOPS_6] = {
        .species = SPECIES_ARCHEOPS,
        .moves = {MOVE_HEAT_WAVE, MOVE_EARTH_POWER, MOVE_HEAD_SMASH, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_DEFEATIST,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_ZOROARK_5] = {
        .species = SPECIES_ZOROARK,
        .moves = {MOVE_DARK_PULSE, MOVE_FLAMETHROWER, MOVE_SLUDGE_BOMB, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ILLUSION,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ZOROARK_6] = {
        .species = SPECIES_ZOROARK,
        .moves = {MOVE_NIGHT_DAZE, MOVE_FOCUS_BLAST, MOVE_U_TURN, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ILLUSION,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_CINCCINO_5] = {
        .species = SPECIES_CINCCINO,
        .moves = {MOVE_WORK_UP, MOVE_TAIL_SLAP, MOVE_BULLET_SEED, MOVE_ROCK_BLAST},
        .heldItem = {ITEM_LOADED_DICE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_CINCCINO_6] = {
        .species = SPECIES_CINCCINO,
        .moves = {MOVE_TAIL_SLAP, MOVE_KNOCK_OFF, MOVE_ENCORE, MOVE_U_TURN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SKILL_LINK,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_REUNICLUS_5] = {
        .species = SPECIES_REUNICLUS,
        .moves = {MOVE_CALM_MIND, MOVE_PSYSHOCK, MOVE_FOCUS_BLAST, MOVE_RECOVER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MAGIC_GUARD,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_REUNICLUS_6] = {
        .species = SPECIES_REUNICLUS,
        .moves = {MOVE_PSYCHIC, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_ENERGY_BALL},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_EMOLGA_5] = {
        .species = SPECIES_EMOLGA,
        .moves = {MOVE_TAILWIND, MOVE_THUNDERBOLT, MOVE_AIR_SLASH, MOVE_ENERGY_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MOTOR_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_EMOLGA_6] = {
        .species = SPECIES_EMOLGA,
        .moves = {MOVE_VOLT_SWITCH, MOVE_NUZZLE, MOVE_ENCORE, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_MOTOR_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GALVANTULA_5] = {
        .species = SPECIES_GALVANTULA,
        .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_COMPOUND_EYES,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GALVANTULA_6] = {
        .species = SPECIES_GALVANTULA,
        .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_SUBSTITUTE, MOVE_DISABLE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_COMPOUND_EYES,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_EELEKTROSS_5] = {
        .species = SPECIES_EELEKTROSS,
        .moves = {MOVE_DRAIN_PUNCH, MOVE_THUNDER_PUNCH, MOVE_KNOCK_OFF, MOVE_U_TURN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_EELEKTROSS_6] = {
        .species = SPECIES_EELEKTROSS,
        .moves = {MOVE_COIL, MOVE_DRAIN_PUNCH, MOVE_THUNDER_PUNCH, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CHANDELURE_5] = {
        .species = SPECIES_CHANDELURE,
        .moves = {MOVE_OVERHEAT, MOVE_SHADOW_BALL, MOVE_ENERGY_BALL, MOVE_PSYCHIC},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CHANDELURE_6] = {
        .species = SPECIES_CHANDELURE,
        .moves = {MOVE_WILL_O_WISP, MOVE_HEX, MOVE_FLAMETHROWER, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_HAXORUS_5] = {
        .species = SPECIES_HAXORUS,
        .moves = {MOVE_OUTRAGE, MOVE_CLOSE_COMBAT, MOVE_POISON_JAB, MOVE_SHADOW_CLAW},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HAXORUS_6] = {
        .species = SPECIES_HAXORUS,
        .moves = {MOVE_SWORDS_DANCE, MOVE_SCALE_SHOT, MOVE_EARTHQUAKE, MOVE_IRON_HEAD},
        .heldItem = {ITEM_LOADED_DICE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_STUNFISK_5] = {
        .species = SPECIES_STUNFISK,
        .moves = {MOVE_DISCHARGE, MOVE_EARTH_POWER, MOVE_STEALTH_ROCK, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STATIC,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_STUNFISK_6] = {
        .species = SPECIES_STUNFISK,
        .moves = {MOVE_SCALD, MOVE_DISCHARGE, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_STATIC,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_MIENSHAO_5] = {
        .species = SPECIES_MIENSHAO,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_KNOCK_OFF, MOVE_U_TURN, MOVE_TAUNT},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MIENSHAO_6] = {
        .species = SPECIES_MIENSHAO,
        .moves = {MOVE_SWORDS_DANCE, MOVE_DRAIN_PUNCH, MOVE_TRIPLE_AXEL, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GOLURK_6] = {
        .species = SPECIES_GOLURK,
        .moves = {MOVE_EARTHQUAKE, MOVE_DYNAMIC_PUNCH, MOVE_DRAIN_PUNCH, MOVE_POLTERGEIST},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_NO_GUARD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_GOLURK_7] = {
        .species = SPECIES_GOLURK,
        .moves = {MOVE_TRICK, MOVE_EARTHQUAKE, MOVE_SHADOW_PUNCH, MOVE_DRAIN_PUNCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_KLUTZ,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BISHARP_5] = {
        .species = SPECIES_BISHARP,
        .moves = {MOVE_SWORDS_DANCE, MOVE_KNOCK_OFF, MOVE_IRON_HEAD, MOVE_LOW_KICK},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BISHARP_6] = {
        .species = SPECIES_BISHARP,
        .moves = {MOVE_KNOCK_OFF, MOVE_IRON_HEAD, MOVE_LOW_KICK, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BRAVIARY_5] = {
        .species = SPECIES_BRAVIARY,
        .moves = {MOVE_BRAVE_BIRD, MOVE_CLOSE_COMBAT, MOVE_ROCK_SLIDE, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BRAVIARY_6] = {
        .species = SPECIES_BRAVIARY,
        .moves = {MOVE_SUBSTITUTE, MOVE_BULK_UP, MOVE_BRAVE_BIRD, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_VOLCARONA_5] = {
        .species = SPECIES_VOLCARONA,
        .moves = {MOVE_QUIVER_DANCE, MOVE_FIERY_DANCE, MOVE_GIGA_DRAIN, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_VOLCARONA_6] = {
        .species = SPECIES_VOLCARONA,
        .moves = {MOVE_FIRE_BLAST, MOVE_BUG_BUZZ, MOVE_GIGA_DRAIN, MOVE_PSYCHIC},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CHESNAUGHT_5] = {
        .species = SPECIES_CHESNAUGHT,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_SPIKES, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_BULLETPROOF,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_CHESNAUGHT_6] = {
        .species = SPECIES_CHESNAUGHT,
        .moves = {MOVE_BELLY_DRUM, MOVE_DRAIN_PUNCH, MOVE_SEED_BOMB, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_BULLETPROOF,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DELPHOX_5] = {
        .species = SPECIES_DELPHOX,
        .moves = {MOVE_OVERHEAT, MOVE_PSYSHOCK, MOVE_DAZZLING_GLEAM, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BLAZE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_DELPHOX_6] = {
        .species = SPECIES_DELPHOX,
        .moves = {MOVE_CALM_MIND, MOVE_FLAMETHROWER, MOVE_GRASS_KNOT, MOVE_WISH},
        .heldItem = {ITEM_GRASS_GEM},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MAGICIAN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GRENINJA_5] = {
        .species = SPECIES_GRENINJA,
        .moves = {MOVE_ICE_BEAM, MOVE_GUNK_SHOT, MOVE_LOW_KICK, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_PROTEAN,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_GRENINJA_6] = {
        .species = SPECIES_GRENINJA,
        .moves = {MOVE_NASTY_PLOT, MOVE_SURF, MOVE_DARK_PULSE, MOVE_WATER_SHURIKEN},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TALONFLAME_5] = {
        .species = SPECIES_TALONFLAME,
        .moves = {MOVE_BRAVE_BIRD, MOVE_WILL_O_WISP, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TALONFLAME_6] = {
        .species = SPECIES_TALONFLAME,
        .moves = {MOVE_SWORDS_DANCE, MOVE_BRAVE_BIRD, MOVE_FLARE_BLITZ, MOVE_ROOST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GALE_WINGS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PYROAR_5] = {
        .species = SPECIES_PYROAR,
        .moves = {MOVE_FIRE_BLAST, MOVE_HYPER_VOICE, MOVE_DARK_PULSE, MOVE_EARTH_POWER},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_UNNERVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PYROAR_6] = {
        .species = SPECIES_PYROAR,
        .moves = {MOVE_WORK_UP, MOVE_HYPER_VOICE, MOVE_FLAMETHROWER, MOVE_DARK_PULSE},
        .heldItem = {ITEM_THROAT_SPRAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_UNNERVE,
        .nature = NATURE_TIMID,
    },

    [FRONTIER_MON_FLOETTE_ETERNAL_4] = {
        .species = SPECIES_FLOETTE_ETERNAL,
        .moves = {MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_GIGA_DRAIN, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLOWER_VEIL,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FLOETTE_ETERNAL_5] = {
        .species = SPECIES_FLOETTE_ETERNAL,
        .moves = {MOVE_LIGHT_OF_RUIN, MOVE_MOONBLAST, MOVE_PSYCHIC, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLOWER_VEIL,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FLORGES_6] = {
        .species = SPECIES_FLORGES_RED,
        .moves = {MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_WISH, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_FLOWER_VEIL,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_FLORGES_7] = {
        .species = SPECIES_FLORGES_RED,
        .moves = {MOVE_MOONBLAST, MOVE_PSYCHIC, MOVE_ENERGY_BALL, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_FLOWER_VEIL,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_MEOWSTIC_4] = {
        .species = SPECIES_MEOWSTIC_M,
        .moves = {MOVE_RAIN_DANCE, MOVE_PSYCHIC, MOVE_THUNDER_WAVE, MOVE_YAWN},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MEOWSTIC_5] = {
        .species = SPECIES_MEOWSTIC_M,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MEOWSTIC_F_4] = {
        .species = SPECIES_MEOWSTIC_F,
        .moves = {MOVE_EXPANDING_FORCE, MOVE_THUNDERBOLT, MOVE_SHADOW_BALL, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MEOWSTIC_F_5] = {
        .species = SPECIES_MEOWSTIC_F,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_THUNDERBOLT, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_AEGISLASH_5] = {
        .species = SPECIES_AEGISLASH_SHIELD,
        .moves = {MOVE_SUBSTITUTE, MOVE_TOXIC, MOVE_SHADOW_BALL, MOVE_KINGS_SHIELD},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_STANCE_CHANGE,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_AEGISLASH_6] = {
        .species = SPECIES_AEGISLASH_SHIELD,
        .moves = {MOVE_SHADOW_CLAW, MOVE_IRON_HEAD, MOVE_SACRED_SWORD, MOVE_SHADOW_SNEAK},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_STANCE_CHANGE,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_MALAMAR_5] = {
        .species = SPECIES_MALAMAR,
        .moves = {MOVE_SUPERPOWER, MOVE_KNOCK_OFF, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_CONTRARY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MALAMAR_6] = {
        .species = SPECIES_MALAMAR,
        .moves = {MOVE_SUPERPOWER, MOVE_PSYCHO_CUT, MOVE_KNOCK_OFF, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CONTRARY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BARBARACLE_5] = {
        .species = SPECIES_BARBARACLE,
        .moves = {MOVE_SHELL_SMASH, MOVE_STONE_EDGE, MOVE_CROSS_CHOP, MOVE_NIGHT_SLASH},
        .heldItem = {ITEM_WHITE_HERB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SNIPER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BARBARACLE_6] = {
        .species = SPECIES_BARBARACLE,
        .moves = {MOVE_LIQUIDATION, MOVE_STONE_EDGE, MOVE_CROSS_CHOP, MOVE_POISON_JAB},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TOUGH_CLAWS,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DRAGALGE_5] = {
        .species = SPECIES_DRAGALGE,
        .moves = {MOVE_DRACO_METEOR, MOVE_SLUDGE_WAVE, MOVE_HYDRO_PUMP, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_DRAGALGE_6] = {
        .species = SPECIES_DRAGALGE,
        .moves = {MOVE_DRAGON_PULSE, MOVE_SLUDGE_BOMB, MOVE_FLIP_TURN, MOVE_SCALD},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_CLAWITZER_5] = {
        .species = SPECIES_CLAWITZER,
        .moves = {MOVE_WATER_PULSE, MOVE_AURA_SPHERE, MOVE_DARK_PULSE, MOVE_FLIP_TURN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_MEGA_LAUNCHER,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CLAWITZER_6] = {
        .species = SPECIES_CLAWITZER,
        .moves = {MOVE_WATER_PULSE, MOVE_AURA_SPHERE, MOVE_DARK_PULSE, MOVE_ICE_BEAM},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MEGA_LAUNCHER,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_TYRANTRUM_5] = {
        .species = SPECIES_TYRANTRUM,
        .moves = {MOVE_HEAD_SMASH, MOVE_OUTRAGE, MOVE_CLOSE_COMBAT, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TYRANTRUM_6] = {
        .species = SPECIES_TYRANTRUM,
        .moves = {MOVE_DRAGON_DANCE, MOVE_DRAGON_CLAW, MOVE_CRUNCH, MOVE_PSYCHIC_FANGS},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_STRONG_JAW,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_AURORUS_5] = {
        .species = SPECIES_AURORUS,
        .moves = {MOVE_HYPER_VOICE, MOVE_FREEZE_DRY, MOVE_EARTH_POWER, MOVE_ANCIENT_POWER},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_REFRIGERATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_AURORUS_6] = {
        .species = SPECIES_AURORUS,
        .moves = {MOVE_STEALTH_ROCK, MOVE_AURORA_VEIL, MOVE_FREEZE_DRY, MOVE_ENCORE},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_SNOW_WARNING,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SYLVEON_5] = {
        .species = SPECIES_SYLVEON,
        .moves = {MOVE_CALM_MIND, MOVE_HYPER_VOICE, MOVE_WISH, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PIXILATE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SYLVEON_6] = {
        .species = SPECIES_SYLVEON,
        .moves = {MOVE_HYPER_VOICE, MOVE_PSYSHOCK, MOVE_SHADOW_BALL, MOVE_QUICK_ATTACK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_PIXILATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_HAWLUCHA_5] = {
        .species = SPECIES_HAWLUCHA,
        .moves = {MOVE_SWORDS_DANCE, MOVE_ACROBATICS, MOVE_DRAIN_PUNCH, MOVE_TAUNT},
        .heldItem = {ITEM_FLYING_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNBURDEN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_HAWLUCHA_6] = {
        .species = SPECIES_HAWLUCHA,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_BRAVE_BIRD, MOVE_ENCORE, MOVE_U_TURN},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_KLEFKI_5] = {
        .species = SPECIES_KLEFKI,
        .moves = {MOVE_CALM_MIND, MOVE_DRAINING_KISS, MOVE_FLASH_CANNON, MOVE_IRON_DEFENSE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_KLEFKI_6] = {
        .species = SPECIES_KLEFKI,
        .moves = {MOVE_SUNNY_DAY, MOVE_SPIKES, MOVE_THUNDER_WAVE, MOVE_DAZZLING_GLEAM},
        .heldItem = {ITEM_HEAT_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_TREVENANT_5] = {
        .species = SPECIES_TREVENANT,
        .moves = {MOVE_CURSE, MOVE_HORN_LEECH, MOVE_POLTERGEIST, MOVE_PROTECT},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_HARVEST,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_TREVENANT_6] = {
        .species = SPECIES_TREVENANT,
        .moves = {MOVE_WOOD_HAMMER, MOVE_POLTERGEIST, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_AVALUGG_5] = {
        .species = SPECIES_AVALUGG,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_AVALANCHE, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_AVALUGG_6] = {
        .species = SPECIES_AVALUGG,
        .moves = {MOVE_AVALANCHE, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_SUPERPOWER},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_NOIVERN_5] = {
        .species = SPECIES_NOIVERN,
        .moves = {MOVE_HURRICANE, MOVE_U_TURN, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_NOIVERN_6] = {
        .species = SPECIES_NOIVERN,
        .moves = {MOVE_BOOMBURST, MOVE_DRACO_METEOR, MOVE_FLAMETHROWER, MOVE_TAILWIND},
        .heldItem = {ITEM_THROAT_SPRAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_DECIDUEYE_5] = {
        .species = SPECIES_DECIDUEYE,
        .moves = {MOVE_LEAF_BLADE, MOVE_SPIRIT_SHACKLE, MOVE_LOW_KICK, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_LONG_REACH,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DECIDUEYE_6] = {
        .species = SPECIES_DECIDUEYE,
        .moves = {MOVE_SPIRIT_SHACKLE, MOVE_KNOCK_OFF, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_LONG_REACH,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_INCINEROAR_5] = {
        .species = SPECIES_INCINEROAR,
        .moves = {MOVE_FLARE_BLITZ, MOVE_KNOCK_OFF, MOVE_PARTING_SHOT, MOVE_TAUNT},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_INCINEROAR_6] = {
        .species = SPECIES_INCINEROAR,
        .moves = {MOVE_FLARE_BLITZ, MOVE_KNOCK_OFF, MOVE_DRAIN_PUNCH, MOVE_FAKE_OUT},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_PRIMARINA_6] = {
        .species = SPECIES_PRIMARINA,
        .moves = {MOVE_CALM_MIND, MOVE_SURF, MOVE_DRAINING_KISS, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_PRIMARINA_7] = {
        .species = SPECIES_PRIMARINA,
        .moves = {MOVE_MOONBLAST, MOVE_SURF, MOVE_ICE_BEAM, MOVE_FLIP_TURN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_VIKAVOLT_5] = {
        .species = SPECIES_VIKAVOLT,
        .moves = {MOVE_AGILITY, MOVE_THUNDERBOLT, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_VIKAVOLT_6] = {
        .species = SPECIES_VIKAVOLT,
        .moves = {MOVE_STICKY_WEB, MOVE_VOLT_SWITCH, MOVE_BUG_BUZZ, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CRABOMINABLE_5] = {
        .species = SPECIES_CRABOMINABLE,
        .moves = {MOVE_ICE_HAMMER, MOVE_DRAIN_PUNCH, MOVE_THUNDER_PUNCH, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_CRABOMINABLE_6] = {
        .species = SPECIES_CRABOMINABLE,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_ICE_PUNCH, MOVE_THUNDER_PUNCH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_RIBOMBEE_5] = {
        .species = SPECIES_RIBOMBEE,
        .moves = {MOVE_QUIVER_DANCE, MOVE_MOONBLAST, MOVE_BUG_BUZZ, MOVE_PSYCHIC},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SHIELD_DUST,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_RIBOMBEE_6] = {
        .species = SPECIES_RIBOMBEE,
        .moves = {MOVE_MOONBLAST, MOVE_BUG_BUZZ, MOVE_PSYCHIC, MOVE_SWITCHEROO},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SHIELD_DUST,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LYCANROC_4] = {
        .species = SPECIES_LYCANROC_MIDDAY,
        .moves = {MOVE_STONE_EDGE, MOVE_PLAY_ROUGH, MOVE_CLOSE_COMBAT, MOVE_ACCELEROCK},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SAND_RUSH,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_LYCANROC_5] = {
        .species = SPECIES_LYCANROC_MIDDAY,
        .moves = {MOVE_STEALTH_ROCK, MOVE_TAUNT, MOVE_ENDEAVOR, MOVE_ACCELEROCK},
        .heldItem = {ITEM_CUSTAP_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_KEEN_EYE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LYCANROC_MIDNIGHT_4] = {
        .species = SPECIES_LYCANROC_MIDNIGHT,
        .moves = {MOVE_STONE_EDGE, MOVE_CLOSE_COMBAT, MOVE_IRON_TAIL, MOVE_PLAY_ROUGH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_NO_GUARD,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LYCANROC_MIDNIGHT_5] = {
        .species = SPECIES_LYCANROC_MIDNIGHT,
        .moves = {MOVE_BULK_UP, MOVE_STONE_EDGE, MOVE_CLOSE_COMBAT, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_NO_GUARD,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_LYCANROC_DUSK_4] = {
        .species = SPECIES_LYCANROC_DUSK,
        .moves = {MOVE_SWORDS_DANCE, MOVE_ACCELEROCK, MOVE_CLOSE_COMBAT, MOVE_CRUNCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TOUGH_CLAWS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LYCANROC_DUSK_5] = {
        .species = SPECIES_LYCANROC_DUSK,
        .moves = {MOVE_STONE_EDGE, MOVE_ACCELEROCK, MOVE_CLOSE_COMBAT, MOVE_PLAY_ROUGH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TOUGH_CLAWS,
        .nature = NATURE_JOLLY,
    },

    [FRONTIER_MON_TOXAPEX_5] = {
        .species = SPECIES_TOXAPEX,
        .moves = {MOVE_SCALD, MOVE_KNOCK_OFF, MOVE_HAZE, MOVE_RECOVER},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_TOXAPEX_6] = {
        .species = SPECIES_TOXAPEX,
        .moves = {MOVE_INFESTATION, MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_RECOVER},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MERCILESS,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_GOLISOPOD_5] = {
        .species = SPECIES_GOLISOPOD,
        .moves = {MOVE_FIRST_IMPRESSION, MOVE_LIQUIDATION, MOVE_AQUA_JET, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_EMERGENCY_EXIT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_GOLISOPOD_6] = {
        .species = SPECIES_GOLISOPOD,
        .moves = {MOVE_SPIKES, MOVE_FIRST_IMPRESSION, MOVE_LEECH_LIFE, MOVE_LIQUIDATION},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_EMERGENCY_EXIT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_PYUKUMUKU_5] = {
        .species = SPECIES_PYUKUMUKU,
        .moves = {MOVE_SOAK, MOVE_TOXIC, MOVE_PROTECT, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_PYUKUMUKU_6] = {
        .species = SPECIES_PYUKUMUKU,
        .moves = {MOVE_COUNTER, MOVE_PAIN_SPLIT, MOVE_RECOVER, MOVE_MEMENTO},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INNARDS_OUT,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MIMIKYU_5] = {
        .species = SPECIES_MIMIKYU_DISGUISED,
        .moves = {MOVE_PLAY_ROUGH, MOVE_SHADOW_CLAW, MOVE_SHADOW_SNEAK, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DISGUISE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MIMIKYU_6] = {
        .species = SPECIES_MIMIKYU_DISGUISED,
        .moves = {MOVE_SWORDS_DANCE, MOVE_PLAY_ROUGH, MOVE_DRAIN_PUNCH, MOVE_SHADOW_SNEAK},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DISGUISE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DRAMPA_5] = {
        .species = SPECIES_DRAMPA,
        .moves = {MOVE_HYPER_VOICE, MOVE_DRACO_METEOR, MOVE_THUNDER, MOVE_SURF},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_BERSERK,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_DRAMPA_6] = {
        .species = SPECIES_DRAMPA,
        .moves = {MOVE_CALM_MIND, MOVE_HYPER_VOICE, MOVE_DRAGON_PULSE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_BERSERK,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_RILLABOOM_5] = {
        .species = SPECIES_RILLABOOM,
        .moves = {MOVE_GRASSY_GLIDE, MOVE_DRAIN_PUNCH, MOVE_KNOCK_OFF, MOVE_U_TURN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_GRASSY_SURGE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_RILLABOOM_6] = {
        .species = SPECIES_RILLABOOM,
        .moves = {MOVE_BULK_UP, MOVE_GRASSY_GLIDE, MOVE_DRAIN_PUNCH, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GRASSY_SURGE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CINDERACE_5] = {
        .species = SPECIES_CINDERACE,
        .moves = {MOVE_PYRO_BALL, MOVE_HIGH_JUMP_KICK, MOVE_U_TURN, MOVE_GUNK_SHOT},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_LIBERO,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_CINDERACE_6] = {
        .species = SPECIES_CINDERACE,
        .moves = {MOVE_BULK_UP, MOVE_PYRO_BALL, MOVE_HIGH_JUMP_KICK, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_LIBERO,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_INTELEON_5] = {
        .species = SPECIES_INTELEON,
        .moves = {MOVE_HYDRO_PUMP, MOVE_ICE_BEAM, MOVE_DARK_PULSE, MOVE_SURF},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TORRENT,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_INTELEON_6] = {
        .species = SPECIES_INTELEON,
        .moves = {MOVE_FOCUS_ENERGY, MOVE_SUBSTITUTE, MOVE_SNIPE_SHOT, MOVE_ICE_BEAM},
        .heldItem = {ITEM_SCOPE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SNIPER,
        .nature = NATURE_MODEST,
    },

    [FRONTIER_MON_CORVIKNIGHT_5] = {
        .species = SPECIES_CORVIKNIGHT,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_DEFOG, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MIRROR_ARMOR,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_CORVIKNIGHT_6] = {
        .species = SPECIES_CORVIKNIGHT,
        .moves = {MOVE_BRAVE_BIRD, MOVE_IRON_HEAD, MOVE_BODY_PRESS, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_MIRROR_ARMOR,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_FLAPPLE_5] = {
        .species = SPECIES_FLAPPLE,
        .moves = {MOVE_GRAV_APPLE, MOVE_OUTRAGE, MOVE_SUCKER_PUNCH, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_HUSTLE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_FLAPPLE_6] = {
        .species = SPECIES_FLAPPLE,
        .moves = {MOVE_DRAGON_DANCE, MOVE_GRAV_APPLE, MOVE_DRAGON_RUSH, MOVE_RECYCLE},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_RIPEN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_APPLETUN_5] = {
        .species = SPECIES_APPLETUN,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_APPLE_ACID, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_THICK_FAT,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_APPLETUN_6] = {
        .species = SPECIES_APPLETUN,
        .moves = {MOVE_GROWTH, MOVE_APPLE_ACID, MOVE_DRAGON_PULSE, MOVE_RECOVER},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_RIPEN,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_SANDACONDA_5] = {
        .species = SPECIES_SANDACONDA,
        .moves = {MOVE_COIL, MOVE_BODY_PRESS, MOVE_EARTHQUAKE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SHED_SKIN,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_SANDACONDA_6] = {
        .species = SPECIES_SANDACONDA,
        .moves = {MOVE_EARTHQUAKE, MOVE_GLARE, MOVE_STEALTH_ROCK, MOVE_BODY_PRESS},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SAND_SPIT,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_TOXTRICITY_LOW_KEY_2] = {
        .species = SPECIES_TOXTRICITY_LOW_KEY,
        .moves = {MOVE_OVERDRIVE, MOVE_BOOMBURST, MOVE_SLUDGE_WAVE, MOVE_HEX},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PUNK_ROCK,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TOXTRICITY_LOW_KEY_3] = {
        .species = SPECIES_TOXTRICITY_LOW_KEY,
        .moves = {MOVE_OVERDRIVE, MOVE_BOOMBURST, MOVE_SNARL, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_PUNK_ROCK,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_TOXTRICITY_4] = {
        .species = SPECIES_TOXTRICITY_AMPED,
        .moves = {MOVE_SHIFT_GEAR, MOVE_BOOMBURST, MOVE_OVERDRIVE, MOVE_DRAIN_PUNCH},
        .heldItem = {ITEM_THROAT_SPRAY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_PUNK_ROCK,
        .nature = NATURE_MILD,
    },


    [FRONTIER_MON_TOXTRICITY_5] = {
        .species = SPECIES_TOXTRICITY_AMPED,
        .moves = {MOVE_BOOMBURST, MOVE_OVERDRIVE, MOVE_SLUDGE_WAVE, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PUNK_ROCK,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CENTISKORCH_5] = {
        .species = SPECIES_CENTISKORCH,
        .moves = {MOVE_COIL, MOVE_FIRE_LASH, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CENTISKORCH_6] = {
        .species = SPECIES_CENTISKORCH,
        .moves = {MOVE_FIRE_LASH, MOVE_LEECH_LIFE, MOVE_KNOCK_OFF, MOVE_POWER_WHIP},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_POLTEAGEIST_5] = {
        .species = SPECIES_POLTEAGEIST_PHONY,
        .moves = {MOVE_SHELL_SMASH, MOVE_SHADOW_BALL, MOVE_GIGA_DRAIN, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_WHITE_HERB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_POLTEAGEIST_6] = {
        .species = SPECIES_POLTEAGEIST_PHONY,
        .moves = {MOVE_SHADOW_BALL, MOVE_GIGA_DRAIN, MOVE_PSYCHIC, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_WEAK_ARMOR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GRIMMSNARL_6] = {
        .species = SPECIES_GRIMMSNARL,
        .moves = {MOVE_BULK_UP, MOVE_SPIRIT_BREAK, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_GRIMMSNARL_7] = {
        .species = SPECIES_GRIMMSNARL,
        .moves = {MOVE_SPIRIT_BREAK, MOVE_DARKEST_LARIAT, MOVE_SUCKER_PUNCH, MOVE_DRAIN_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_FRISK,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_OBSTAGOON_5] = {
        .species = SPECIES_OBSTAGOON,
        .moves = {MOVE_BULK_UP, MOVE_FACADE, MOVE_KNOCK_OFF, MOVE_CLOSE_COMBAT},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_GUTS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_OBSTAGOON_6] = {
        .species = SPECIES_OBSTAGOON,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_KNOCK_OFF, MOVE_CLOSE_COMBAT, MOVE_SWITCHEROO},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PERRSERKER_5] = {
        .species = SPECIES_PERRSERKER,
        .moves = {MOVE_IRON_HEAD, MOVE_CLOSE_COMBAT, MOVE_KNOCK_OFF, MOVE_FAKE_OUT},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_STEELY_SPIRIT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_PERRSERKER_6] = {
        .species = SPECIES_PERRSERKER,
        .moves = {MOVE_SWORDS_DANCE, MOVE_IRON_HEAD, MOVE_CLOSE_COMBAT, MOVE_CRUNCH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_TOUGH_CLAWS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CURSOLA_5] = {
        .species = SPECIES_CURSOLA,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_GIGA_DRAIN, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PERISH_BODY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CURSOLA_6] = {
        .species = SPECIES_CURSOLA,
        .moves = {MOVE_SHADOW_BALL, MOVE_ICE_BEAM, MOVE_EARTH_POWER, MOVE_HYDRO_PUMP},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_WEAK_ARMOR,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_SIRFETCHD_5] = {
        .species = SPECIES_SIRFETCHD,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_LEAF_BLADE, MOVE_NIGHT_SLASH, MOVE_BRAVE_BIRD},
        .heldItem = {ITEM_LEEK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SIRFETCHD_6] = {
        .species = SPECIES_SIRFETCHD,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_LEAF_BLADE, MOVE_KNOCK_OFF, MOVE_FIRST_IMPRESSION},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_MR_RIME_5] = {
        .species = SPECIES_MR_RIME,
        .moves = {MOVE_NASTY_PLOT, MOVE_FREEZE_DRY, MOVE_PSYSHOCK, MOVE_SLACK_OFF},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SCREEN_CLEANER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MR_RIME_6] = {
        .species = SPECIES_MR_RIME,
        .moves = {MOVE_ICE_BEAM, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SCREEN_CLEANER,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_RUNERIGUS_5] = {
        .species = SPECIES_RUNERIGUS,
        .moves = {MOVE_TRICK_ROOM, MOVE_EARTHQUAKE, MOVE_POLTERGEIST, MOVE_BODY_PRESS},
        .heldItem = {ITEM_MENTAL_HERB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_WANDERING_SPIRIT,
        .nature = NATURE_BRAVE,
    },

    [FRONTIER_MON_RUNERIGUS_6] = {
        .species = SPECIES_RUNERIGUS,
        .moves = {MOVE_BODY_PRESS, MOVE_WILL_O_WISP, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_WANDERING_SPIRIT,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_FALINKS_5] = {
        .species = SPECIES_FALINKS,
        .moves = {MOVE_NO_RETREAT, MOVE_CLOSE_COMBAT, MOVE_THROAT_CHOP, MOVE_REST},
        .heldItem = {ITEM_CHESTO_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_FALINKS_6] = {
        .species = SPECIES_FALINKS,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_MEGAHORN, MOVE_POISON_JAB, MOVE_ROCK_SLIDE},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_INDEEDEE_3] = {
        .species = SPECIES_INDEEDEE_M,
        .moves = {MOVE_EXPANDING_FORCE, MOVE_DAZZLING_GLEAM, MOVE_SHADOW_BALL, MOVE_HEALING_WISH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PSYCHIC_SURGE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_INDEEDEE_4] = {
        .species = SPECIES_INDEEDEE_M,
        .moves = {MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_HYPER_VOICE, MOVE_SHADOW_BALL},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PSYCHIC_SURGE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_INDEEDEE_F_3] = {
        .species = SPECIES_INDEEDEE_F,
        .moves = {MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_DRAINING_KISS, MOVE_HEALING_WISH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PSYCHIC_SURGE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_INDEEDEE_F_4] = {
        .species = SPECIES_INDEEDEE_F,
        .moves = {MOVE_FOLLOW_ME, MOVE_HELPING_HAND, MOVE_PSYCHIC, MOVE_PROTECT},
        .heldItem = {ITEM_SAFETY_GOGGLES},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PSYCHIC_SURGE,
        .nature = NATURE_BOLD,
        .tags = FACILITY_MON_TAG_DOUBLES_ONLY,
    },


    [FRONTIER_MON_DURALUDON_5] = {
        .species = SPECIES_DURALUDON,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_FLASH_CANNON, MOVE_REST},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_LIGHT_METAL,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_DURALUDON_6] = {
        .species = SPECIES_DURALUDON,
        .moves = {MOVE_STEALTH_ROCK, MOVE_DRAGON_TAIL, MOVE_BODY_PRESS, MOVE_THUNDER_WAVE},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_LIGHT_METAL,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_RAPIDASH_GALAR_5] = {
        .species = SPECIES_RAPIDASH_GALAR,
        .moves = {MOVE_SWORDS_DANCE, MOVE_PLAY_ROUGH, MOVE_PSYCHO_CUT, MOVE_MORNING_SUN},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PASTEL_VEIL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_RAPIDASH_GALAR_6] = {
        .species = SPECIES_RAPIDASH_GALAR,
        .moves = {MOVE_PLAY_ROUGH, MOVE_PSYCHO_CUT, MOVE_HIGH_HORSEPOWER, MOVE_HEALING_WISH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PASTEL_VEIL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SLOWBRO_GALAR_4] = {
        .species = SPECIES_SLOWBRO_GALAR,
        .moves = {MOVE_TOXIC, MOVE_SLUDGE_BOMB, MOVE_PSYCHIC, MOVE_SLACK_OFF},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SLOWBRO_GALAR_5] = {
        .species = SPECIES_SLOWBRO_GALAR,
        .moves = {MOVE_SHELL_SIDE_ARM, MOVE_PSYCHIC, MOVE_FIRE_BLAST, MOVE_ICE_BEAM},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_QUICK_DRAW,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_SLOWKING_GALAR_6] = {
        .species = SPECIES_SLOWKING_GALAR,
        .moves = {MOVE_FUTURE_SIGHT, MOVE_SLUDGE_BOMB, MOVE_CHILLY_RECEPTION, MOVE_SLACK_OFF},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_SASSY,
    },


    [FRONTIER_MON_SLOWKING_GALAR_7] = {
        .species = SPECIES_SLOWKING_GALAR,
        .moves = {MOVE_EERIE_SPELL, MOVE_SLUDGE_WAVE, MOVE_FLAMETHROWER, MOVE_SURF},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_WEEZING_GALAR_5] = {
        .species = SPECIES_WEEZING_GALAR,
        .moves = {MOVE_STRANGE_STEAM, MOVE_WILL_O_WISP, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_NEUTRALIZING_GAS,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_WEEZING_GALAR_6] = {
        .species = SPECIES_WEEZING_GALAR,
        .moves = {MOVE_STRANGE_STEAM, MOVE_SLUDGE_BOMB, MOVE_FLAMETHROWER, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_MISTY_SURGE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CORSOLA_GALAR_4] = {
        .species = SPECIES_CORSOLA_GALAR,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_GIGA_DRAIN, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CORSOLA_GALAR_5] = {
        .species = SPECIES_CORSOLA_GALAR,
        .moves = {MOVE_NIGHT_SHADE, MOVE_HAZE, MOVE_WILL_O_WISP, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_CURSED_BODY,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_DARMANITAN_GALAR_7] = {
        .species = SPECIES_DARMANITAN_GALAR_STANDARD,
        .moves = {MOVE_BULK_UP, MOVE_ICE_PUNCH, MOVE_FIRE_PUNCH, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_SALAC_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ZEN_MODE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DARMANITAN_GALAR_8] = {
        .species = SPECIES_DARMANITAN_GALAR_STANDARD,
        .moves = {MOVE_ICICLE_CRASH, MOVE_EARTHQUAKE, MOVE_SUPERPOWER, MOVE_U_TURN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_GORILLA_TACTICS,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_STUNFISK_GALAR_4] = {
        .species = SPECIES_STUNFISK_GALAR,
        .moves = {MOVE_EARTHQUAKE, MOVE_SNAP_TRAP, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_MIMICRY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_STUNFISK_GALAR_5] = {
        .species = SPECIES_STUNFISK_GALAR,
        .moves = {MOVE_EARTHQUAKE, MOVE_THUNDER_WAVE, MOVE_STEALTH_ROCK, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MIMICRY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_WYRDEER_5] = {
        .species = SPECIES_WYRDEER,
        .moves = {MOVE_TRICK_ROOM, MOVE_EXPANDING_FORCE, MOVE_THUNDERBOLT, MOVE_EARTH_POWER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_WYRDEER_6] = {
        .species = SPECIES_WYRDEER,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_SHADOW_BALL, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_BASCULEGION_M_4] = {
        .species = SPECIES_BASCULEGION_M,
        .moves = {MOVE_LAST_RESPECTS, MOVE_WAVE_CRASH, MOVE_AQUA_JET, MOVE_FLIP_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BASCULEGION_M_5] = {
        .species = SPECIES_BASCULEGION_M,
        .moves = {MOVE_RAIN_DANCE, MOVE_WAVE_CRASH, MOVE_PHANTOM_FORCE, MOVE_AQUA_JET},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BASCULEGION_F_3] = {
        .species = SPECIES_BASCULEGION_F,
        .moves = {MOVE_HYDRO_PUMP, MOVE_SHADOW_BALL, MOVE_ICE_BEAM, MOVE_SURF},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_MODEST,
    },

    [FRONTIER_MON_BASCULEGION_F_4] = {
        .species = SPECIES_BASCULEGION_F,
        .moves = {MOVE_RAIN_DANCE, MOVE_HYDRO_PUMP, MOVE_SHADOW_BALL, MOVE_ICE_BEAM},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_KLEAVOR_6] = {
        .species = SPECIES_KLEAVOR,
        .moves = {MOVE_STONE_AXE, MOVE_X_SCISSOR, MOVE_CLOSE_COMBAT, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHARPNESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_KLEAVOR_7] = {
        .species = SPECIES_KLEAVOR,
        .moves = {MOVE_SWORDS_DANCE, MOVE_STONE_AXE, MOVE_X_SCISSOR, MOVE_ROOST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHARPNESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ARCANINE_HISUI_5] = {
        .species = SPECIES_ARCANINE_HISUI,
        .moves = {MOVE_HEAD_SMASH, MOVE_FLARE_BLITZ, MOVE_CLOSE_COMBAT, MOVE_EXTREME_SPEED},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ROCK_HEAD,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ARCANINE_HISUI_6] = {
        .species = SPECIES_ARCANINE_HISUI,
        .moves = {MOVE_ROCK_SLIDE, MOVE_FLARE_BLITZ, MOVE_WILL_O_WISP, MOVE_MORNING_SUN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_BRAVIARY_HISUI_5] = {
        .species = SPECIES_BRAVIARY_HISUI,
        .moves = {MOVE_HYPER_VOICE, MOVE_HURRICANE, MOVE_HEAT_WAVE, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_TINTED_LENS,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_BRAVIARY_HISUI_6] = {
        .species = SPECIES_BRAVIARY_HISUI,
        .moves = {MOVE_CALM_MIND, MOVE_ESPER_WING, MOVE_HURRICANE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TINTED_LENS,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_ZOROARK_HISUI_5] = {
        .species = SPECIES_ZOROARK_HISUI,
        .moves = {MOVE_SHADOW_BALL, MOVE_HYPER_VOICE, MOVE_FOCUS_BLAST, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ILLUSION,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ZOROARK_HISUI_6] = {
        .species = SPECIES_ZOROARK_HISUI,
        .moves = {MOVE_NASTY_PLOT, MOVE_BITTER_MALICE, MOVE_FLAMETHROWER, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ILLUSION,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ELECTRODE_HISUI_5] = {
        .species = SPECIES_ELECTRODE_HISUI,
        .moves = {MOVE_TAUNT, MOVE_SUBSTITUTE, MOVE_THUNDERBOLT, MOVE_GIGA_DRAIN},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_STATIC,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ELECTRODE_HISUI_6] = {
        .species = SPECIES_ELECTRODE_HISUI,
        .moves = {MOVE_LEAF_STORM, MOVE_THUNDERBOLT, MOVE_FOUL_PLAY, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_AFTERMATH,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_URSALUNA_5] = {
        .species = SPECIES_URSALUNA,
        .moves = {MOVE_SWORDS_DANCE, MOVE_FACADE, MOVE_EARTHQUAKE, MOVE_CRUNCH},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_GUTS,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_URSALUNA_6] = {
        .species = SPECIES_URSALUNA,
        .moves = {MOVE_BULK_UP, MOVE_BODY_PRESS, MOVE_EARTHQUAKE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_BULLETPROOF,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_SNEASLER_5] = {
        .species = SPECIES_SNEASLER,
        .moves = {MOVE_SWORDS_DANCE, MOVE_CLOSE_COMBAT, MOVE_DIRE_CLAW, MOVE_ACROBATICS},
        .heldItem = {ITEM_FLYING_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNBURDEN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SNEASLER_6] = {
        .species = SPECIES_SNEASLER,
        .moves = {MOVE_FAKE_OUT, MOVE_CLOSE_COMBAT, MOVE_DIRE_CLAW, MOVE_U_TURN},
        .heldItem = {ITEM_NORMAL_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNBURDEN,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_QWILFISH_HISUI_2] = {
        .species = SPECIES_QWILFISH_HISUI,
        .moves = {MOVE_BARB_BARRAGE, MOVE_CRUNCH, MOVE_TAUNT, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_QWILFISH_HISUI_3] = {
        .species = SPECIES_QWILFISH_HISUI,
        .moves = {MOVE_SWORDS_DANCE, MOVE_BARB_BARRAGE, MOVE_CRUNCH, MOVE_LIQUIDATION},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_OVERQWIL_4] = {
        .species = SPECIES_OVERQWIL,
        .moves = {MOVE_BARB_BARRAGE, MOVE_CRUNCH, MOVE_SPIKES, MOVE_PAIN_SPLIT},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_OVERQWIL_5] = {
        .species = SPECIES_OVERQWIL,
        .moves = {MOVE_RAIN_DANCE, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_GUNK_SHOT},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWIFT_SWIM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_LILLIGANT_HISUI_5] = {
        .species = SPECIES_LILLIGANT_HISUI,
        .moves = {MOVE_LEAF_BLADE, MOVE_CLOSE_COMBAT, MOVE_ICE_SPINNER, MOVE_POISON_JAB},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LILLIGANT_HISUI_6] = {
        .species = SPECIES_LILLIGANT_HISUI,
        .moves = {MOVE_VICTORY_DANCE, MOVE_LEAF_BLADE, MOVE_DRAIN_PUNCH, MOVE_SYNTHESIS},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_HUSTLE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_AVALUGG_HISUI_5] = {
        .species = SPECIES_AVALUGG_HISUI,
        .moves = {MOVE_RAPID_SPIN, MOVE_BODY_PRESS, MOVE_AVALANCHE, MOVE_RECOVER},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_AVALUGG_HISUI_6] = {
        .species = SPECIES_AVALUGG_HISUI,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_STONE_EDGE, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_STURDY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DECIDUEYE_HISUI_5] = {
        .species = SPECIES_DECIDUEYE_HISUI,
        .moves = {MOVE_BULK_UP, MOVE_TRIPLE_ARROWS, MOVE_LEAF_BLADE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DECIDUEYE_HISUI_6] = {
        .species = SPECIES_DECIDUEYE_HISUI,
        .moves = {MOVE_TRIPLE_ARROWS, MOVE_LEAF_BLADE, MOVE_KNOCK_OFF, MOVE_BRAVE_BIRD},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_TYPHLOSION_HISUI_5] = {
        .species = SPECIES_TYPHLOSION_HISUI,
        .moves = {MOVE_ERUPTION, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_FLAMETHROWER},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BLAZE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TYPHLOSION_HISUI_6] = {
        .species = SPECIES_TYPHLOSION_HISUI,
        .moves = {MOVE_CALM_MIND, MOVE_INFERNAL_PARADE, MOVE_FLAMETHROWER, MOVE_WILL_O_WISP},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FRISK,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SAMUROTT_HISUI_5] = {
        .species = SPECIES_SAMUROTT_HISUI,
        .moves = {MOVE_CEASELESS_EDGE, MOVE_RAZOR_SHELL, MOVE_KNOCK_OFF, MOVE_FLIP_TURN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHARPNESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SAMUROTT_HISUI_6] = {
        .species = SPECIES_SAMUROTT_HISUI,
        .moves = {MOVE_CEASELESS_EDGE, MOVE_AQUA_JET, MOVE_TAUNT, MOVE_SACRED_SWORD},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SHARPNESS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TAUROS_PALDEA_AQUA_3] = {
        .species = SPECIES_TAUROS_PALDEA_AQUA,
        .moves = {MOVE_BULK_UP, MOVE_RAGING_BULL, MOVE_BODY_PRESS, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TAUROS_PALDEA_AQUA_4] = {
        .species = SPECIES_TAUROS_PALDEA_AQUA,
        .moves = {MOVE_BULK_UP, MOVE_WAVE_CRASH, MOVE_CLOSE_COMBAT, MOVE_AQUA_JET},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_CUD_CHEW,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_TAUROS_PALDEA_BLAZE_3] = {
        .species = SPECIES_TAUROS_PALDEA_BLAZE,
        .moves = {MOVE_FLARE_BLITZ, MOVE_CLOSE_COMBAT, MOVE_STONE_EDGE, MOVE_RAGING_BULL},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TAUROS_PALDEA_BLAZE_4] = {
        .species = SPECIES_TAUROS_PALDEA_BLAZE,
        .moves = {MOVE_BULK_UP, MOVE_RAGING_BULL, MOVE_BODY_PRESS, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_CUD_CHEW,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_TAUROS_PALDEA_COMBAT_3] = {
        .species = SPECIES_TAUROS_PALDEA_COMBAT,
        .moves = {MOVE_BULK_UP, MOVE_BODY_PRESS, MOVE_STONE_EDGE, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_TAUROS_PALDEA_COMBAT_4] = {
        .species = SPECIES_TAUROS_PALDEA_COMBAT,
        .moves = {MOVE_BULK_UP, MOVE_CLOSE_COMBAT, MOVE_EARTHQUAKE, MOVE_WILD_CHARGE},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CUD_CHEW,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MEOWSCARADA_3] = {
        .species = SPECIES_MEOWSCARADA,
        .moves = {MOVE_FLOWER_TRICK, MOVE_KNOCK_OFF, MOVE_LOW_KICK, MOVE_U_TURN},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PROTEAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MEOWSCARADA_4] = {
        .species = SPECIES_MEOWSCARADA,
        .moves = {MOVE_SPIKES, MOVE_FLOWER_TRICK, MOVE_KNOCK_OFF, MOVE_TAUNT},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_OVERGROW,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_QUAQUAVAL_3] = {
        .species = SPECIES_QUAQUAVAL,
        .moves = {MOVE_SWORDS_DANCE, MOVE_AQUA_STEP, MOVE_CLOSE_COMBAT, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_QUAQUAVAL_4] = {
        .species = SPECIES_QUAQUAVAL,
        .moves = {MOVE_BULK_UP, MOVE_AQUA_STEP, MOVE_CLOSE_COMBAT, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_SKELEDIRGE_3] = {
        .species = SPECIES_SKELEDIRGE,
        .moves = {MOVE_TORCH_SONG, MOVE_SHADOW_BALL, MOVE_ROAR, MOVE_SLACK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_SKELEDIRGE_4] = {
        .species = SPECIES_SKELEDIRGE,
        .moves = {MOVE_TORCH_SONG, MOVE_SHADOW_BALL, MOVE_EARTH_POWER, MOVE_SNARL},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_PAWMOT_3] = {
        .species = SPECIES_PAWMOT,
        .moves = {MOVE_REVIVAL_BLESSING, MOVE_FAKE_OUT, MOVE_CLOSE_COMBAT, MOVE_DOUBLE_SHOCK},
        .heldItem = {ITEM_LEPPA_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PAWMOT_4] = {
        .species = SPECIES_PAWMOT,
        .moves = {MOVE_BULK_UP, MOVE_MACH_PUNCH, MOVE_THUNDER_PUNCH, MOVE_ICE_PUNCH},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MAUSHOLD_3] = {
        .species = SPECIES_MAUSHOLD_THREE,
        .moves = {MOVE_FOLLOW_ME, MOVE_SUPER_FANG, MOVE_ENCORE, MOVE_PROTECT},
        .heldItem = {ITEM_SAFETY_GOGGLES},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 252, 0, 0),
        .ability = ABILITY_FRIEND_GUARD,
        .nature = NATURE_JOLLY,
        .tags = FACILITY_MON_TAG_DOUBLES_ONLY,
    },


    [FRONTIER_MON_MAUSHOLD_4] = {
        .species = SPECIES_MAUSHOLD_THREE,
        .moves = {MOVE_POPULATION_BOMB, MOVE_TIDY_UP, MOVE_U_TURN, MOVE_ENCORE},
        .heldItem = {ITEM_WIDE_LENS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GARGANACL_3] = {
        .species = SPECIES_GARGANACL,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_SALT_CURE, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_PURIFYING_SALT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_GARGANACL_4] = {
        .species = SPECIES_GARGANACL,
        .moves = {MOVE_SALT_CURE, MOVE_STEALTH_ROCK, MOVE_RECOVER, MOVE_PROTECT},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PURIFYING_SALT,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_ARMAROUGE_3] = {
        .species = SPECIES_ARMAROUGE,
        .moves = {MOVE_TRICK_ROOM, MOVE_ARMOR_CANNON, MOVE_EXPANDING_FORCE, MOVE_ENERGY_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_ARMAROUGE_4] = {
        .species = SPECIES_ARMAROUGE,
        .moves = {MOVE_ARMOR_CANNON, MOVE_PSYCHIC, MOVE_AURA_SPHERE, MOVE_ENERGY_BALL},
        .heldItem = {ITEM_EJECT_PACK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_WEAK_ARMOR,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_CERULEDGE_3] = {
        .species = SPECIES_CERULEDGE,
        .moves = {MOVE_BULK_UP, MOVE_BITTER_BLADE, MOVE_SHADOW_SNEAK, MOVE_TAUNT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CERULEDGE_4] = {
        .species = SPECIES_CERULEDGE,
        .moves = {MOVE_BITTER_BLADE, MOVE_POLTERGEIST, MOVE_CLOSE_COMBAT, MOVE_SHADOW_SNEAK},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_KILOWATTREL_3] = {
        .species = SPECIES_KILOWATTREL,
        .moves = {MOVE_TAILWIND, MOVE_THUNDERBOLT, MOVE_HURRICANE, MOVE_ROOST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_WIND_POWER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_KILOWATTREL_4] = {
        .species = SPECIES_KILOWATTREL,
        .moves = {MOVE_VOLT_SWITCH, MOVE_HURRICANE, MOVE_THUNDER_WAVE, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SCOVILLAIN_3] = {
        .species = SPECIES_SCOVILLAIN,
        .moves = {MOVE_GROWTH, MOVE_FLAMETHROWER, MOVE_GIGA_DRAIN, MOVE_SUNNY_DAY},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_SCOVILLAIN_4] = {
        .species = SPECIES_SCOVILLAIN,
        .moves = {MOVE_GROWTH, MOVE_SEED_BOMB, MOVE_FIRE_BLAST, MOVE_STOMPING_TANTRUM},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 4, 0),
        .ability = ABILITY_CHLOROPHYLL,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_ESPATHRA_3] = {
        .species = SPECIES_ESPATHRA,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_DAZZLING_GLEAM, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SPEED_BOOST,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_ESPATHRA_4] = {
        .species = SPECIES_ESPATHRA,
        .moves = {MOVE_LUMINA_CRASH, MOVE_DAZZLING_GLEAM, MOVE_SHADOW_BALL, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_OPPORTUNIST,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TINKATON_3] = {
        .species = SPECIES_TINKATON,
        .moves = {MOVE_GIGATON_HAMMER, MOVE_KNOCK_OFF, MOVE_THUNDER_WAVE, MOVE_ENCORE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_TINKATON_4] = {
        .species = SPECIES_TINKATON,
        .moves = {MOVE_GIGATON_HAMMER, MOVE_PLAY_ROUGH, MOVE_KNOCK_OFF, MOVE_BRICK_BREAK},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_PALAFIN_3] = {
        .species = SPECIES_PALAFIN_ZERO,
        .moves = {MOVE_WAVE_CRASH, MOVE_JET_PUNCH, MOVE_CLOSE_COMBAT, MOVE_FLIP_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ZERO_TO_HERO,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_PALAFIN_4] = {
        .species = SPECIES_PALAFIN_ZERO,
        .moves = {MOVE_BULK_UP, MOVE_JET_PUNCH, MOVE_DRAIN_PUNCH, MOVE_FLIP_TURN},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_ZERO_TO_HERO,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CYCLIZAR_3] = {
        .species = SPECIES_CYCLIZAR,
        .moves = {MOVE_DRACO_METEOR, MOVE_HYPER_VOICE, MOVE_OVERHEAT, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_CYCLIZAR_4] = {
        .species = SPECIES_CYCLIZAR,
        .moves = {MOVE_RAPID_SPIN, MOVE_KNOCK_OFF, MOVE_U_TURN, MOVE_TAUNT},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GLIMMORA_3] = {
        .species = SPECIES_GLIMMORA,
        .moves = {MOVE_SPIKES, MOVE_MORTAL_SPIN, MOVE_POWER_GEM, MOVE_SLUDGE_WAVE},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_TOXIC_DEBRIS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GLIMMORA_4] = {
        .species = SPECIES_GLIMMORA,
        .moves = {MOVE_POWER_GEM, MOVE_SLUDGE_WAVE, MOVE_EARTH_POWER, MOVE_ENERGY_BALL},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CORROSION,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FLAMIGO_3] = {
        .species = SPECIES_FLAMIGO,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_BRAVE_BIRD, MOVE_LIQUIDATION, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_FLAMIGO_4] = {
        .species = SPECIES_FLAMIGO,
        .moves = {MOVE_BULK_UP, MOVE_BRAVE_BIRD, MOVE_CLOSE_COMBAT, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SCRAPPY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DONDOZO_3] = {
        .species = SPECIES_DONDOZO,
        .moves = {MOVE_BODY_PRESS, MOVE_LIQUIDATION, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DONDOZO_4] = {
        .species = SPECIES_DONDOZO,
        .moves = {MOVE_WAVE_CRASH, MOVE_EARTHQUAKE, MOVE_HEAVY_SLAM, MOVE_OUTRAGE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_TATSUGIRI_DROOPY_1] = {
        .species = SPECIES_TATSUGIRI_DROOPY,
        .moves = {MOVE_DRACO_METEOR, MOVE_HYDRO_PUMP, MOVE_SURF, MOVE_ICY_WIND},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_TATSUGIRI_DROOPY_2] = {
        .species = SPECIES_TATSUGIRI_DROOPY,
        .moves = {MOVE_SURF, MOVE_DRAGON_PULSE, MOVE_RAPID_SPIN, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_TATSUGIRI_STRETCHY_1] = {
        .species = SPECIES_TATSUGIRI_STRETCHY,
        .moves = {MOVE_NASTY_PLOT, MOVE_SURF, MOVE_DRAGON_PULSE, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TATSUGIRI_STRETCHY_2] = {
        .species = SPECIES_TATSUGIRI_STRETCHY,
        .moves = {MOVE_SURF, MOVE_DRACO_METEOR, MOVE_ICY_WIND, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_ANNIHILAPE_3] = {
        .species = SPECIES_ANNIHILAPE,
        .moves = {MOVE_FACADE, MOVE_RAGE_FIST, MOVE_DRAIN_PUNCH, MOVE_U_TURN},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ANNIHILAPE_4] = {
        .species = SPECIES_ANNIHILAPE,
        .moves = {MOVE_BULK_UP, MOVE_RAGE_FIST, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CLODSIRE_3] = {
        .species = SPECIES_CLODSIRE,
        .moves = {MOVE_SPIKES, MOVE_EARTHQUAKE, MOVE_HAZE, MOVE_RECOVER},
        .heldItem = {ITEM_BLACK_SLUDGE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_UNAWARE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CLODSIRE_4] = {
        .species = SPECIES_CLODSIRE,
        .moves = {MOVE_CURSE, MOVE_EARTHQUAKE, MOVE_POISON_JAB, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_FARIGIRAF_3] = {
        .species = SPECIES_FARIGIRAF,
        .moves = {MOVE_EXPANDING_FORCE, MOVE_HYPER_VOICE, MOVE_THUNDERBOLT, MOVE_ENERGY_BALL},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_ARMOR_TAIL,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_FARIGIRAF_4] = {
        .species = SPECIES_FARIGIRAF,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_DAZZLING_GLEAM, MOVE_WISH},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_CUD_CHEW,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_DUDUNSPARCE_TWO_SEGMENT_1] = {
        .species = SPECIES_DUDUNSPARCE_TWO_SEGMENT,
        .moves = {MOVE_COIL, MOVE_BODY_SLAM, MOVE_EARTHQUAKE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DUDUNSPARCE_TWO_SEGMENT_2] = {
        .species = SPECIES_DUDUNSPARCE_TWO_SEGMENT,
        .moves = {MOVE_GLARE, MOVE_BOOMBURST, MOVE_FLAMETHROWER, MOVE_ROOST},
        .heldItem = {ITEM_THROAT_SPRAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_DUDUNSPARCE_THREE_SEGMENT_1] = {
        .species = SPECIES_DUDUNSPARCE_THREE_SEGMENT,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_BOOMBURST, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_DUDUNSPARCE_THREE_SEGMENT_2] = {
        .species = SPECIES_DUDUNSPARCE_THREE_SEGMENT,
        .moves = {MOVE_HYPER_DRILL, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_POISON_JAB},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_KINGAMBIT_3] = {
        .species = SPECIES_KINGAMBIT,
        .moves = {MOVE_KOWTOW_CLEAVE, MOVE_IRON_HEAD, MOVE_LOW_KICK, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SUPREME_OVERLORD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_KINGAMBIT_4] = {
        .species = SPECIES_KINGAMBIT,
        .moves = {MOVE_SUBSTITUTE, MOVE_SWORDS_DANCE, MOVE_KOWTOW_CLEAVE, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SUPREME_OVERLORD,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_DIPPLIN_2] = {
        .species = SPECIES_DIPPLIN,
        .moves = {MOVE_SYRUP_BOMB, MOVE_DRAGON_TAIL, MOVE_RECOVER, MOVE_REFLECT},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SUPERSWEET_SYRUP,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_DIPPLIN_3] = {
        .species = SPECIES_DIPPLIN,
        .moves = {MOVE_GROWTH, MOVE_DRAGON_PULSE, MOVE_GIGA_DRAIN, MOVE_RECOVER},
        .heldItem = {ITEM_EVIOLITE},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_STICKY_HOLD,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_PIKACHU_PARTNER_1] = {
        .species = SPECIES_PIKACHU_STARTER,
        .moves = {MOVE_THUNDERBOLT, MOVE_SURF, MOVE_GRASS_KNOT, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_LIGHT_BALL},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LIGHTNING_ROD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PIKACHU_PARTNER_2] = {
        .species = SPECIES_PIKACHU_STARTER,
        .moves = {MOVE_ZIPPY_ZAP, MOVE_VOLT_TACKLE, MOVE_KNOCK_OFF, MOVE_BRICK_BREAK},
        .heldItem = {ITEM_LIGHT_BALL},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_STATIC,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_EEVEE_PARTNER_2] = {
        .species = SPECIES_EEVEE_STARTER,
        .moves = {MOVE_BOUNCY_BUBBLE, MOVE_BADDY_BAD, MOVE_SAPPY_SEED, MOVE_SPARKLY_SWIRL},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_EEVEE_PARTNER_3] = {
        .species = SPECIES_EEVEE_STARTER,
        .moves = {MOVE_CURSE, MOVE_RETURN, MOVE_SIZZLY_SLIDE, MOVE_WISH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_ADAPTABILITY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SINISTCHA_2] = {
        .species = SPECIES_SINISTCHA_UNREMARKABLE,
        .moves = {MOVE_TRICK_ROOM, MOVE_MATCHA_GOTCHA, MOVE_SHADOW_BALL, MOVE_STRENGTH_SAP},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_HEATPROOF,
        .nature = NATURE_QUIET,
    },


    [FRONTIER_MON_SINISTCHA_3] = {
        .species = SPECIES_SINISTCHA_UNREMARKABLE,
        .moves = {MOVE_RAGE_POWDER, MOVE_MATCHA_GOTCHA, MOVE_LIFE_DEW, MOVE_PROTECT},
        .heldItem = {ITEM_ROCKY_HELMET},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HOSPITALITY,
        .nature = NATURE_BOLD,
        .tags = FACILITY_MON_TAG_DOUBLES_ONLY,
    },


    [FRONTIER_MON_ARCHALUDON_3] = {
        .species = SPECIES_ARCHALUDON,
        .moves = {MOVE_ELECTRO_SHOT, MOVE_DRACO_METEOR, MOVE_FLASH_CANNON, MOVE_BODY_PRESS},
        .heldItem = {ITEM_POWER_HERB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_STAMINA,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_ARCHALUDON_4] = {
        .species = SPECIES_ARCHALUDON,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_FLASH_CANNON, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_STAMINA,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_HYDRAPPLE_3] = {
        .species = SPECIES_HYDRAPPLE,
        .moves = {MOVE_GIGA_DRAIN, MOVE_FICKLE_BEAM, MOVE_EARTH_POWER, MOVE_INFESTATION},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_HYDRAPPLE_4] = {
        .species = SPECIES_HYDRAPPLE,
        .moves = {MOVE_NASTY_PLOT, MOVE_GIGA_DRAIN, MOVE_EARTH_POWER, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_PIKACHU_2] = {
        .species = SPECIES_PIKACHU,
        .moves = {MOVE_NASTY_PLOT, MOVE_THUNDERBOLT, MOVE_SURF, MOVE_GRASS_KNOT},
        .heldItem = {ITEM_LIGHT_BALL},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LIGHTNING_ROD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PIKACHU_3] = {
        .species = SPECIES_PIKACHU,
        .moves = {MOVE_VOLT_TACKLE, MOVE_KNOCK_OFF, MOVE_FAKE_OUT, MOVE_ENCORE},
        .heldItem = {ITEM_LIGHT_BALL},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_STATIC,
        .nature = NATURE_JOLLY,
    },

// High tier.


    [FRONTIER_MON_ARTICUNO_5] = {
        .species = SPECIES_ARTICUNO,
        .moves = {MOVE_BLIZZARD, MOVE_FREEZE_DRY, MOVE_HURRICANE, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_ARTICUNO_6] = {
        .species = SPECIES_ARTICUNO,
        .moves = {MOVE_FREEZE_DRY, MOVE_TOXIC, MOVE_SUBSTITUTE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ZAPDOS_5] = {
        .species = SPECIES_ZAPDOS,
        .moves = {MOVE_THUNDER, MOVE_HURRICANE, MOVE_WEATHER_BALL, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_STATIC,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ZAPDOS_6] = {
        .species = SPECIES_ZAPDOS,
        .moves = {MOVE_THUNDER, MOVE_HURRICANE, MOVE_ROOST, MOVE_U_TURN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_STATIC,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MOLTRES_5] = {
        .species = SPECIES_MOLTRES,
        .moves = {MOVE_FIRE_BLAST, MOVE_AIR_SLASH, MOVE_SOLAR_BEAM, MOVE_SCORCHING_SANDS},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MOLTRES_6] = {
        .species = SPECIES_MOLTRES,
        .moves = {MOVE_FLAMETHROWER, MOVE_WILL_O_WISP, MOVE_ROOST, MOVE_U_TURN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_FLAME_BODY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_DRAGONITE_5] = {
        .species = SPECIES_DRAGONITE,
        .moves = {MOVE_DRAGON_DANCE, MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MULTISCALE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DRAGONITE_6] = {
        .species = SPECIES_DRAGONITE,
        .moves = {MOVE_HURRICANE, MOVE_THUNDER, MOVE_SURF, MOVE_ROOST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MULTISCALE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_RAIKOU_5] = {
        .species = SPECIES_RAIKOU,
        .moves = {MOVE_THUNDERBOLT, MOVE_SCALD, MOVE_SHADOW_BALL, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_INNER_FOCUS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_RAIKOU_6] = {
        .species = SPECIES_RAIKOU,
        .moves = {MOVE_CALM_MIND, MOVE_SUBSTITUTE, MOVE_THUNDERBOLT, MOVE_AURA_SPHERE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ENTEI_5] = {
        .species = SPECIES_ENTEI,
        .moves = {MOVE_FLARE_BLITZ, MOVE_STONE_EDGE, MOVE_EXTREME_SPEED, MOVE_STOMPING_TANTRUM},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INNER_FOCUS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ENTEI_6] = {
        .species = SPECIES_ENTEI,
        .moves = {MOVE_SACRED_FIRE, MOVE_STONE_EDGE, MOVE_SUBSTITUTE, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SUICUNE_5] = {
        .species = SPECIES_SUICUNE,
        .moves = {MOVE_SCALD, MOVE_CALM_MIND, MOVE_SUBSTITUTE, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SUICUNE_6] = {
        .species = SPECIES_SUICUNE,
        .moves = {MOVE_CALM_MIND, MOVE_HYDRO_PUMP, MOVE_ICE_BEAM, MOVE_SHADOW_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_INNER_FOCUS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TYRANITAR_5] = {
        .species = SPECIES_TYRANITAR,
        .moves = {MOVE_STONE_EDGE, MOVE_CRUNCH, MOVE_SUPERPOWER, MOVE_FIRE_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SAND_STREAM,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_TYRANITAR_6] = {
        .species = SPECIES_TYRANITAR,
        .moves = {MOVE_STEALTH_ROCK, MOVE_CRUNCH, MOVE_FIRE_BLAST, MOVE_ICE_BEAM},
        .heldItem = {ITEM_SMOOTH_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SAND_STREAM,
        .nature = NATURE_SASSY,
    },


    [FRONTIER_MON_SALAMENCE_5] = {
        .species = SPECIES_SALAMENCE,
        .moves = {MOVE_HURRICANE, MOVE_DRACO_METEOR, MOVE_FLAMETHROWER, MOVE_ROOST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SALAMENCE_6] = {
        .species = SPECIES_SALAMENCE,
        .moves = {MOVE_OUTRAGE, MOVE_DUAL_WINGBEAT, MOVE_EARTHQUAKE, MOVE_STONE_EDGE},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_METAGROSS_5] = {
        .species = SPECIES_METAGROSS,
        .moves = {MOVE_AGILITY, MOVE_METEOR_MASH, MOVE_EARTHQUAKE, MOVE_THUNDER_PUNCH},
        .heldItem = {ITEM_WEAKNESS_POLICY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_METAGROSS_6] = {
        .species = SPECIES_METAGROSS,
        .moves = {MOVE_METEOR_MASH, MOVE_ZEN_HEADBUTT, MOVE_HAMMER_ARM, MOVE_BULLET_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_REGIROCK_5] = {
        .species = SPECIES_REGIROCK,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_ROCK_SLIDE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_STURDY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_REGIROCK_6] = {
        .species = SPECIES_REGIROCK,
        .moves = {MOVE_STONE_EDGE, MOVE_DRAIN_PUNCH, MOVE_ICE_PUNCH, MOVE_THUNDER_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_REGICE_5] = {
        .species = SPECIES_REGICE,
        .moves = {MOVE_ICE_BEAM, MOVE_BLIZZARD, MOVE_THUNDERBOLT, MOVE_FOCUS_BLAST},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_REGICE_6] = {
        .species = SPECIES_REGICE,
        .moves = {MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_ICE_BODY,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_REGISTEEL_5] = {
        .species = SPECIES_REGISTEEL,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_REGISTEEL_6] = {
        .species = SPECIES_REGISTEEL,
        .moves = {MOVE_CURSE, MOVE_HEAVY_SLAM, MOVE_EARTHQUAKE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_LATIAS_6] = {
        .species = SPECIES_LATIAS,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_DRAINING_KISS, MOVE_RECOVER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LATIAS_7] = {
        .species = SPECIES_LATIAS,
        .moves = {MOVE_DRACO_METEOR, MOVE_PSYSHOCK, MOVE_TRICK, MOVE_HEALING_WISH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LATIOS_6] = {
        .species = SPECIES_LATIOS,
        .moves = {MOVE_DRACO_METEOR, MOVE_LUSTER_PURGE, MOVE_SURF, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },

    [FRONTIER_MON_LATIOS_7] = {
        .species = SPECIES_LATIOS,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_AURA_SPHERE, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GARCHOMP_6] = {
        .species = SPECIES_GARCHOMP,
        .moves = {MOVE_SCALE_SHOT, MOVE_EARTHQUAKE, MOVE_FIRE_FANG, MOVE_SWORDS_DANCE},
        .heldItem = {ITEM_LOADED_DICE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ROUGH_SKIN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GARCHOMP_7] = {
        .species = SPECIES_GARCHOMP,
        .moves = {MOVE_EARTHQUAKE, MOVE_DRAGON_CLAW, MOVE_STONE_EDGE, MOVE_POISON_JAB},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ROUGH_SKIN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_UXIE_5] = {
        .species = SPECIES_UXIE,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_UXIE_6] = {
        .species = SPECIES_UXIE,
        .moves = {MOVE_RAIN_DANCE, MOVE_STEALTH_ROCK, MOVE_U_TURN, MOVE_MEMENTO},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 252, 0, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MESPRIT_5] = {
        .species = SPECIES_MESPRIT,
        .moves = {MOVE_PSYCHIC, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MESPRIT_6] = {
        .species = SPECIES_MESPRIT,
        .moves = {MOVE_PSYCHIC, MOVE_ICE_BEAM, MOVE_TRICK, MOVE_HEALING_WISH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_AZELF_5] = {
        .species = SPECIES_AZELF,
        .moves = {MOVE_PSYCHIC, MOVE_FLAMETHROWER, MOVE_U_TURN, MOVE_EXPLOSION},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_MIND_FLOAT,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_AZELF_6] = {
        .species = SPECIES_AZELF,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_ZEN_HEADBUTT, MOVE_KNOCK_OFF, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MIND_FLOAT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_HEATRAN_5] = {
        .species = SPECIES_HEATRAN,
        .moves = {MOVE_OVERHEAT, MOVE_FLASH_CANNON, MOVE_EARTH_POWER, MOVE_DRAGON_PULSE},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_HEATRAN_6] = {
        .species = SPECIES_HEATRAN,
        .moves = {MOVE_MAGMA_STORM, MOVE_EARTH_POWER, MOVE_SUBSTITUTE, MOVE_TAUNT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_FLASH_FIRE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_REGIGIGAS_5] = {
        .species = SPECIES_REGIGIGAS,
        .moves = {MOVE_SUBSTITUTE, MOVE_PROTECT, MOVE_BODY_SLAM, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_SLOW_START,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_REGIGIGAS_6] = {
        .species = SPECIES_REGIGIGAS,
        .moves = {MOVE_DRAIN_PUNCH, MOVE_KNOCK_OFF, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SLOW_START,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CRESSELIA_5] = {
        .species = SPECIES_CRESSELIA,
        .moves = {MOVE_PSYCHO_SHIFT, MOVE_PSYCHIC, MOVE_MOONBLAST, MOVE_LUNAR_BLESSING},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CRESSELIA_6] = {
        .species = SPECIES_CRESSELIA,
        .moves = {MOVE_MOONBLAST, MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_LUNAR_DANCE},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_HYDREIGON_5] = {
        .species = SPECIES_HYDREIGON,
        .moves = {MOVE_DRACO_METEOR, MOVE_DARK_PULSE, MOVE_EARTH_POWER, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_HYDREIGON_6] = {
        .species = SPECIES_HYDREIGON,
        .moves = {MOVE_NASTY_PLOT, MOVE_DARK_PULSE, MOVE_TAUNT, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_COBALION_5] = {
        .species = SPECIES_COBALION,
        .moves = {MOVE_IRON_DEFENSE, MOVE_BODY_PRESS, MOVE_FLASH_CANNON, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_JUSTIFIED,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_COBALION_6] = {
        .species = SPECIES_COBALION,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_IRON_HEAD, MOVE_STONE_EDGE, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_JUSTIFIED,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TERRAKION_5] = {
        .species = SPECIES_TERRAKION,
        .moves = {MOVE_STONE_EDGE, MOVE_SACRED_SWORD, MOVE_MEGAHORN, MOVE_QUICK_ATTACK},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_JUSTIFIED,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TERRAKION_6] = {
        .species = SPECIES_TERRAKION,
        .moves = {MOVE_STEALTH_ROCK, MOVE_TAUNT, MOVE_STONE_EDGE, MOVE_CLOSE_COMBAT},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_JUSTIFIED,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_VIRIZION_5] = {
        .species = SPECIES_VIRIZION,
        .moves = {MOVE_CALM_MIND, MOVE_GIGA_DRAIN, MOVE_FOCUS_BLAST, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_JUSTIFIED,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_VIRIZION_6] = {
        .species = SPECIES_VIRIZION,
        .moves = {MOVE_LEAF_BLADE, MOVE_CLOSE_COMBAT, MOVE_STONE_EDGE, MOVE_ZEN_HEADBUTT},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_JUSTIFIED,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TORNADUS_4] = {
        .species = SPECIES_TORNADUS_INCARNATE,
        .moves = {MOVE_RAIN_DANCE, MOVE_HURRICANE, MOVE_FOCUS_BLAST, MOVE_U_TURN},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TORNADUS_5] = {
        .species = SPECIES_TORNADUS_INCARNATE,
        .moves = {MOVE_BULK_UP, MOVE_ACROBATICS, MOVE_SUPERPOWER, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_FLYING_GEM},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TORNADUS_THERIAN_4] = {
        .species = SPECIES_TORNADUS_THERIAN,
        .moves = {MOVE_HURRICANE, MOVE_HEAT_WAVE, MOVE_KNOCK_OFF, MOVE_U_TURN},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TORNADUS_THERIAN_5] = {
        .species = SPECIES_TORNADUS_THERIAN,
        .moves = {MOVE_NASTY_PLOT, MOVE_HURRICANE, MOVE_HEAT_WAVE, MOVE_FOCUS_BLAST},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_THUNDURUS_4] = {
        .species = SPECIES_THUNDURUS_INCARNATE,
        .moves = {MOVE_NASTY_PLOT, MOVE_THUNDER, MOVE_FOCUS_BLAST, MOVE_WEATHER_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_THUNDURUS_5] = {
        .species = SPECIES_THUNDURUS_INCARNATE,
        .moves = {MOVE_THUNDER_WAVE, MOVE_TAUNT, MOVE_THUNDER, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_PRANKSTER,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_THUNDURUS_THERIAN_4] = {
        .species = SPECIES_THUNDURUS_THERIAN,
        .moves = {MOVE_THUNDER, MOVE_FOCUS_BLAST, MOVE_WEATHER_BALL, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_THUNDURUS_THERIAN_5] = {
        .species = SPECIES_THUNDURUS_THERIAN,
        .moves = {MOVE_AGILITY, MOVE_THUNDER, MOVE_FOCUS_BLAST, MOVE_WEATHER_BALL},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_LANDORUS_4] = {
        .species = SPECIES_LANDORUS_INCARNATE,
        .moves = {MOVE_NASTY_PLOT, MOVE_EARTH_POWER, MOVE_SLUDGE_WAVE, MOVE_FOCUS_BLAST},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SHEER_FORCE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LANDORUS_5] = {
        .species = SPECIES_LANDORUS_INCARNATE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_EARTHQUAKE, MOVE_STONE_EDGE, MOVE_FLY},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SAND_FORCE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LANDORUS_THERIAN_4] = {
        .species = SPECIES_LANDORUS_THERIAN,
        .moves = {MOVE_EARTHQUAKE, MOVE_STONE_EDGE, MOVE_U_TURN, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LANDORUS_THERIAN_5] = {
        .species = SPECIES_LANDORUS_THERIAN,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_U_TURN, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_INTIMIDATE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_GOODRA_5] = {
        .species = SPECIES_GOODRA,
        .moves = {MOVE_ACID_ARMOR, MOVE_BODY_PRESS, MOVE_DRAGON_PULSE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_GOODRA_6] = {
        .species = SPECIES_GOODRA,
        .moves = {MOVE_DRACO_METEOR, MOVE_THUNDER, MOVE_SURF, MOVE_SLUDGE_WAVE},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_MODEST,
    },

    [FRONTIER_MON_KOMMO_O_6] = {
        .species = SPECIES_KOMMO_O,
        .moves = {MOVE_CLANGOROUS_SOUL, MOVE_CLANGING_SCALES, MOVE_AURA_SPHERE, MOVE_FLAMETHROWER},
        .heldItem = {ITEM_THROAT_SPRAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SOUNDPROOF,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_KOMMO_O_7] = {
        .species = SPECIES_KOMMO_O,
        .moves = {MOVE_DRAGON_DANCE, MOVE_DRAIN_PUNCH, MOVE_DRAGON_CLAW, MOVE_POISON_JAB},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_BULLETPROOF,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_TAPU_KOKO_5] = {
        .species = SPECIES_TAPU_KOKO,
        .moves = {MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_TAUNT, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_LIGHT_CLAY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_ELECTRIC_SURGE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TAPU_KOKO_6] = {
        .species = SPECIES_TAPU_KOKO,
        .moves = {MOVE_CALM_MIND, MOVE_THUNDERBOLT, MOVE_DAZZLING_GLEAM, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_ELECTRIC_SURGE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TAPU_LELE_5] = {
        .species = SPECIES_TAPU_LELE,
        .moves = {MOVE_PSYSHOCK, MOVE_MOONBLAST, MOVE_FOCUS_BLAST, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PSYCHIC_SURGE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TAPU_LELE_6] = {
        .species = SPECIES_TAPU_LELE,
        .moves = {MOVE_CALM_MIND, MOVE_PSYSHOCK, MOVE_DRAINING_KISS, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PSYCHIC_SURGE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_TAPU_BULU_5] = {
        .species = SPECIES_TAPU_BULU,
        .moves = {MOVE_BULK_UP, MOVE_HORN_LEECH, MOVE_SUPERPOWER, MOVE_STONE_EDGE},
        .heldItem = {ITEM_GRASSY_SEED},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_GRASSY_SURGE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_TAPU_BULU_6] = {
        .species = SPECIES_TAPU_BULU,
        .moves = {MOVE_NATURES_MADNESS, MOVE_HORN_LEECH, MOVE_TAUNT, MOVE_PROTECT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_GRASSY_SURGE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_TAPU_FINI_5] = {
        .species = SPECIES_TAPU_FINI,
        .moves = {MOVE_SURF, MOVE_MOONBLAST, MOVE_ICE_BEAM, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MISTY_SURGE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TAPU_FINI_6] = {
        .species = SPECIES_TAPU_FINI,
        .moves = {MOVE_CALM_MIND, MOVE_SURF, MOVE_DRAINING_KISS, MOVE_TAUNT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MISTY_SURGE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_NAGANADEL_5] = {
        .species = SPECIES_NAGANADEL,
        .moves = {MOVE_SLUDGE_WAVE, MOVE_DRACO_METEOR, MOVE_TOXIC_SPIKES, MOVE_FLAMETHROWER},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BEAST_BOOST,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_NAGANADEL_6] = {
        .species = SPECIES_NAGANADEL,
        .moves = {MOVE_DRACO_METEOR, MOVE_SLUDGE_WAVE, MOVE_FLAMETHROWER, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BEAST_BOOST,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_DRAGAPULT_5] = {
        .species = SPECIES_DRAGAPULT,
        .moves = {MOVE_DRAGON_DARTS, MOVE_PHANTOM_FORCE, MOVE_STEEL_WING, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_DRAGAPULT_6] = {
        .species = SPECIES_DRAGAPULT,
        .moves = {MOVE_WILL_O_WISP, MOVE_HEX, MOVE_SUBSTITUTE, MOVE_DRACO_METEOR},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_INFILTRATOR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ARTICUNO_GALAR_5] = {
        .species = SPECIES_ARTICUNO_GALAR,
        .moves = {MOVE_FREEZING_GLARE, MOVE_HURRICANE, MOVE_SHADOW_BALL, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ARTICUNO_GALAR_6] = {
        .species = SPECIES_ARTICUNO_GALAR,
        .moves = {MOVE_CALM_MIND, MOVE_FREEZING_GLARE, MOVE_HURRICANE, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_COMPETITIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ZAPDOS_GALAR_5] = {
        .species = SPECIES_ZAPDOS_GALAR,
        .moves = {MOVE_FACADE, MOVE_CLOSE_COMBAT, MOVE_BRAVE_BIRD, MOVE_PROTECT},
        .heldItem = {ITEM_FLAME_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_ZAPDOS_GALAR_6] = {
        .species = SPECIES_ZAPDOS_GALAR,
        .moves = {MOVE_BULK_UP, MOVE_THUNDEROUS_KICK, MOVE_BRAVE_BIRD, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_MOLTRES_GALAR_5] = {
        .species = SPECIES_MOLTRES_GALAR,
        .moves = {MOVE_FIERY_WRATH, MOVE_HURRICANE, MOVE_TAUNT, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_BERSERK,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MOLTRES_GALAR_6] = {
        .species = SPECIES_MOLTRES_GALAR,
        .moves = {MOVE_FIERY_WRATH, MOVE_HURRICANE, MOVE_U_TURN, MOVE_MEMENTO},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BERSERK,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GOODRA_HISUI_5] = {
        .species = SPECIES_GOODRA_HISUI,
        .moves = {MOVE_DRACO_METEOR, MOVE_FLASH_CANNON, MOVE_FLAMETHROWER, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_SAP_SIPPER,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GOODRA_HISUI_6] = {
        .species = SPECIES_GOODRA_HISUI,
        .moves = {MOVE_SHELTER, MOVE_BODY_PRESS, MOVE_DRAGON_TAIL, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SHELL_ARMOR,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_URSALUNA_BLOODMOON_3] = {
        .species = SPECIES_URSALUNA_BLOODMOON,
        .moves = {MOVE_BLOOD_MOON, MOVE_EARTH_POWER, MOVE_VACUUM_WAVE, MOVE_MOONBLAST},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_MINDS_EYE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_URSALUNA_BLOODMOON_4] = {
        .species = SPECIES_URSALUNA_BLOODMOON,
        .moves = {MOVE_CALM_MIND, MOVE_EARTH_POWER, MOVE_BLOOD_MOON, MOVE_MOONLIGHT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MINDS_EYE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_TATSUGIRI_CURLY_1] = {
        .species = SPECIES_TATSUGIRI_CURLY,
        .moves = {MOVE_DRACO_METEOR, MOVE_HYDRO_PUMP, MOVE_DRAGON_PULSE, MOVE_MUDDY_WATER},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_TATSUGIRI_CURLY_2] = {
        .species = SPECIES_TATSUGIRI_CURLY,
        .moves = {MOVE_NASTY_PLOT, MOVE_SURF, MOVE_DRAGON_PULSE, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_STORM_DRAIN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GREAT_TUSK_3] = {
        .species = SPECIES_GREAT_TUSK,
        .moves = {MOVE_BULK_UP, MOVE_HEADLONG_RUSH, MOVE_ICE_SPINNER, MOVE_RAPID_SPIN},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GREAT_TUSK_4] = {
        .species = SPECIES_GREAT_TUSK,
        .moves = {MOVE_HEADLONG_RUSH, MOVE_CLOSE_COMBAT, MOVE_KNOCK_OFF, MOVE_STONE_EDGE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_SCREAM_TAIL_3] = {
        .species = SPECIES_SCREAM_TAIL,
        .moves = {MOVE_ENCORE, MOVE_DISABLE, MOVE_WISH, MOVE_DAZZLING_GLEAM},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SCREAM_TAIL_4] = {
        .species = SPECIES_SCREAM_TAIL,
        .moves = {MOVE_CALM_MIND, MOVE_STORED_POWER, MOVE_DAZZLING_GLEAM, MOVE_WISH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_BRUTE_BONNET_3] = {
        .species = SPECIES_BRUTE_BONNET,
        .moves = {MOVE_SPORE, MOVE_BULLET_SEED, MOVE_CRUNCH, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_LOADED_DICE},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BRUTE_BONNET_4] = {
        .species = SPECIES_BRUTE_BONNET,
        .moves = {MOVE_RAGE_POWDER, MOVE_SPORE, MOVE_SEED_BOMB, MOVE_PROTECT},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_CAREFUL,
        .tags = FACILITY_MON_TAG_DOUBLES_ONLY,
    },


    [FRONTIER_MON_FLUTTER_MANE_3] = {
        .species = SPECIES_FLUTTER_MANE,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_MOONBLAST, MOVE_SUBSTITUTE},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FLUTTER_MANE_4] = {
        .species = SPECIES_FLUTTER_MANE,
        .moves = {MOVE_SHADOW_BALL, MOVE_MOONBLAST, MOVE_MYSTICAL_FIRE, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_SLITHER_WING_3] = {
        .species = SPECIES_SLITHER_WING,
        .moves = {MOVE_BULK_UP, MOVE_LEECH_LIFE, MOVE_CLOSE_COMBAT, MOVE_MORNING_SUN},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_SLITHER_WING_4] = {
        .species = SPECIES_SLITHER_WING,
        .moves = {MOVE_FIRST_IMPRESSION, MOVE_CLOSE_COMBAT, MOVE_FLARE_BLITZ, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_SANDY_SHOCKS_3] = {
        .species = SPECIES_SANDY_SHOCKS,
        .moves = {MOVE_EARTH_POWER, MOVE_THUNDERBOLT, MOVE_FLASH_CANNON, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SANDY_SHOCKS_4] = {
        .species = SPECIES_SANDY_SHOCKS,
        .moves = {MOVE_GRAVITY, MOVE_SPIKES, MOVE_EARTH_POWER, MOVE_THUNDER},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_TREADS_3] = {
        .species = SPECIES_IRON_TREADS,
        .moves = {MOVE_EARTHQUAKE, MOVE_IRON_HEAD, MOVE_ICE_SPINNER, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_IRON_TREADS_4] = {
        .species = SPECIES_IRON_TREADS,
        .moves = {MOVE_EARTHQUAKE, MOVE_KNOCK_OFF, MOVE_RAPID_SPIN, MOVE_STEALTH_ROCK},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_IRON_BUNDLE_3] = {
        .species = SPECIES_IRON_BUNDLE,
        .moves = {MOVE_FREEZE_DRY, MOVE_HYDRO_PUMP, MOVE_SUBSTITUTE, MOVE_ENCORE},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_BUNDLE_4] = {
        .species = SPECIES_IRON_BUNDLE,
        .moves = {MOVE_SNOWSCAPE, MOVE_BLIZZARD, MOVE_HYDRO_PUMP, MOVE_AURORA_VEIL},
        .heldItem = {ITEM_ICY_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_HANDS_3] = {
        .species = SPECIES_IRON_HANDS,
        .moves = {MOVE_BELLY_DRUM, MOVE_DRAIN_PUNCH, MOVE_THUNDER_PUNCH, MOVE_ICE_PUNCH},
        .heldItem = {ITEM_SITRUS_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_IRON_HANDS_4] = {
        .species = SPECIES_IRON_HANDS,
        .moves = {MOVE_SWORDS_DANCE, MOVE_DRAIN_PUNCH, MOVE_THUNDER_PUNCH, MOVE_REST},
        .heldItem = {ITEM_CHESTO_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_IRON_JUGULIS_3] = {
        .species = SPECIES_IRON_JUGULIS,
        .moves = {MOVE_ELECTRIC_TERRAIN, MOVE_HURRICANE, MOVE_DARK_PULSE, MOVE_EARTH_POWER},
        .heldItem = {ITEM_TERRAIN_EXTENDER},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_JUGULIS_4] = {
        .species = SPECIES_IRON_JUGULIS,
        .moves = {MOVE_DARK_PULSE, MOVE_HURRICANE, MOVE_EARTH_POWER, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_MOTH_3] = {
        .species = SPECIES_IRON_MOTH,
        .moves = {MOVE_FIERY_DANCE, MOVE_SLUDGE_WAVE, MOVE_DISCHARGE, MOVE_MORNING_SUN},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_MOTH_4] = {
        .species = SPECIES_IRON_MOTH,
        .moves = {MOVE_OVERHEAT, MOVE_SLUDGE_WAVE, MOVE_ENERGY_BALL, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_THORNS_3] = {
        .species = SPECIES_IRON_THORNS,
        .moves = {MOVE_STONE_EDGE, MOVE_WILD_CHARGE, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_IRON_THORNS_4] = {
        .species = SPECIES_IRON_THORNS,
        .moves = {MOVE_STEALTH_ROCK, MOVE_SPIKES, MOVE_STONE_EDGE, MOVE_THUNDER_WAVE},
        .heldItem = {ITEM_CUSTAP_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_IRON_VALIANT_3] = {
        .species = SPECIES_IRON_VALIANT,
        .moves = {MOVE_SWORDS_DANCE, MOVE_CLOSE_COMBAT, MOVE_SPIRIT_BREAK, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_IRON_VALIANT_4] = {
        .species = SPECIES_IRON_VALIANT,
        .moves = {MOVE_MOONBLAST, MOVE_AURA_SPHERE, MOVE_SHADOW_BALL, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_BAXCALIBUR_3] = {
        .species = SPECIES_BAXCALIBUR,
        .moves = {MOVE_GLAIVE_RUSH, MOVE_ICICLE_CRASH, MOVE_EARTHQUAKE, MOVE_ICE_SHARD},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_THERMAL_EXCHANGE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_BAXCALIBUR_4] = {
        .species = SPECIES_BAXCALIBUR,
        .moves = {MOVE_DRAGON_DANCE, MOVE_SUBSTITUTE, MOVE_ICICLE_CRASH, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ICE_BODY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GHOLDENGO_3] = {
        .species = SPECIES_GHOLDENGO,
        .moves = {MOVE_MAKE_IT_RAIN, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_GOOD_AS_GOLD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GHOLDENGO_4] = {
        .species = SPECIES_GHOLDENGO,
        .moves = {MOVE_NASTY_PLOT, MOVE_MAKE_IT_RAIN, MOVE_SHADOW_BALL, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_GOOD_AS_GOLD,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CHIEN_PAO_3] = {
        .species = SPECIES_CHIEN_PAO,
        .moves = {MOVE_SWORDS_DANCE, MOVE_ICE_SPINNER, MOVE_SACRED_SWORD, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWORD_OF_RUIN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_CHIEN_PAO_4] = {
        .species = SPECIES_CHIEN_PAO,
        .moves = {MOVE_ICICLE_CRASH, MOVE_CRUNCH, MOVE_SACRED_SWORD, MOVE_RECOVER},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_SWORD_OF_RUIN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_CHI_YU_3] = {
        .species = SPECIES_CHI_YU,
        .moves = {MOVE_NASTY_PLOT, MOVE_FLAMETHROWER, MOVE_DARK_PULSE, MOVE_PSYCHIC},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BEADS_OF_RUIN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_CHI_YU_4] = {
        .species = SPECIES_CHI_YU,
        .moves = {MOVE_SUBSTITUTE, MOVE_WILL_O_WISP, MOVE_FLAMETHROWER, MOVE_DARK_PULSE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BEADS_OF_RUIN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ROARING_MOON_3] = {
        .species = SPECIES_ROARING_MOON,
        .moves = {MOVE_DRAGON_DANCE, MOVE_CRUNCH, MOVE_ACROBATICS, MOVE_TAUNT},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ROARING_MOON_4] = {
        .species = SPECIES_ROARING_MOON,
        .moves = {MOVE_OUTRAGE, MOVE_KNOCK_OFF, MOVE_EARTHQUAKE, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_WALKING_WAKE_3] = {
        .species = SPECIES_WALKING_WAKE,
        .moves = {MOVE_SUNNY_DAY, MOVE_HYDRO_STEAM, MOVE_DRAGON_PULSE, MOVE_FLAMETHROWER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_WALKING_WAKE_4] = {
        .species = SPECIES_WALKING_WAKE,
        .moves = {MOVE_HYDRO_STEAM, MOVE_DRACO_METEOR, MOVE_FLAMETHROWER, MOVE_FLIP_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_LEAVES_3] = {
        .species = SPECIES_IRON_LEAVES,
        .moves = {MOVE_ELECTRIC_TERRAIN, MOVE_PSYBLADE, MOVE_LEAF_BLADE, MOVE_CLOSE_COMBAT},
        .heldItem = {ITEM_TERRAIN_EXTENDER},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_IRON_LEAVES_4] = {
        .species = SPECIES_IRON_LEAVES,
        .moves = {MOVE_PSYBLADE, MOVE_LEAF_BLADE, MOVE_CLOSE_COMBAT, MOVE_MEGAHORN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_FEZANDIPITI_3] = {
        .species = SPECIES_FEZANDIPITI,
        .moves = {MOVE_TOXIC, MOVE_MOONBLAST, MOVE_ROOST, MOVE_TAUNT},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_TOXIC_CHAIN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_FEZANDIPITI_4] = {
        .species = SPECIES_FEZANDIPITI,
        .moves = {MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_SLUDGE_BOMB, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_KORAIDON_3] = {
        .species = SPECIES_KORAIDON,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_DRAGON_CLAW, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_ORICHALCUM_PULSE,
        .nature = NATURE_ADAMANT,
    },


    [FRONTIER_MON_KORAIDON_4] = {
        .species = SPECIES_KORAIDON,
        .moves = {MOVE_COLLISION_COURSE, MOVE_DRAGON_CLAW, MOVE_FLARE_BLITZ, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_ORICHALCUM_PULSE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MIRAIDON_3] = {
        .species = SPECIES_MIRAIDON,
        .moves = {MOVE_ELECTRO_DRIFT, MOVE_DRACO_METEOR, MOVE_OVERHEAT, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_HADRON_ENGINE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MIRAIDON_4] = {
        .species = SPECIES_MIRAIDON,
        .moves = {MOVE_CALM_MIND, MOVE_ELECTRO_DRIFT, MOVE_DRAGON_PULSE, MOVE_PARABOLIC_CHARGE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_HADRON_ENGINE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_OGERPON_TEAL_1] = {
        .species = SPECIES_OGERPON_TEAL,
        .moves = {MOVE_SWORDS_DANCE, MOVE_IVY_CUDGEL, MOVE_KNOCK_OFF, MOVE_PLAY_ROUGH},
        .heldItem = {ITEM_MIRACLE_SEED},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_OGERPON_TEAL_2] = {
        .species = SPECIES_OGERPON_TEAL,
        .moves = {MOVE_HORN_LEECH, MOVE_GRASSY_GLIDE, MOVE_U_TURN, MOVE_ENCORE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_DEFIANT,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_OGERPON_WELLSPRING_1] = {
        .species = SPECIES_OGERPON_WELLSPRING,
        .moves = {MOVE_SWORDS_DANCE, MOVE_IVY_CUDGEL, MOVE_HORN_LEECH, MOVE_ENCORE},
        .heldItem = {ITEM_WELLSPRING_MASK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_OGERPON_WELLSPRING_2] = {
        .species = SPECIES_OGERPON_WELLSPRING,
        .moves = {MOVE_FOLLOW_ME, MOVE_IVY_CUDGEL, MOVE_HORN_LEECH, MOVE_SPIKY_SHIELD},
        .heldItem = {ITEM_WELLSPRING_MASK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_WATER_ABSORB,
        .nature = NATURE_JOLLY,
        .tags = FACILITY_MON_TAG_DOUBLES_ONLY,
    },


    [FRONTIER_MON_OGERPON_HEARTHFLAME_1] = {
        .species = SPECIES_OGERPON_HEARTHFLAME,
        .moves = {MOVE_IVY_CUDGEL, MOVE_POWER_WHIP, MOVE_PLAY_ROUGH, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_HEARTHFLAME_MASK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_OGERPON_HEARTHFLAME_2] = {
        .species = SPECIES_OGERPON_HEARTHFLAME,
        .moves = {MOVE_SWORDS_DANCE, MOVE_IVY_CUDGEL, MOVE_HORN_LEECH, MOVE_TAUNT},
        .heldItem = {ITEM_HEARTHFLAME_MASK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOLD_BREAKER,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_OGERPON_CORNERSTONE_1] = {
        .species = SPECIES_OGERPON_CORNERSTONE,
        .moves = {MOVE_IVY_CUDGEL, MOVE_POWER_WHIP, MOVE_SUPERPOWER, MOVE_U_TURN},
        .heldItem = {ITEM_CORNERSTONE_MASK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_STURDY,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_OGERPON_CORNERSTONE_2] = {
        .species = SPECIES_OGERPON_CORNERSTONE,
        .moves = {MOVE_FOLLOW_ME, MOVE_IVY_CUDGEL, MOVE_HORN_LEECH, MOVE_SPIKY_SHIELD},
        .heldItem = {ITEM_CORNERSTONE_MASK},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_STURDY,
        .nature = NATURE_JOLLY,
        .tags = FACILITY_MON_TAG_DOUBLES_ONLY,
    },


    [FRONTIER_MON_GOUGING_FIRE_3] = {
        .species = SPECIES_GOUGING_FIRE,
        .moves = {MOVE_DRAGON_DANCE, MOVE_HEAT_CRASH, MOVE_DRAGON_CLAW, MOVE_MORNING_SUN},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_GOUGING_FIRE_4] = {
        .species = SPECIES_GOUGING_FIRE,
        .moves = {MOVE_BURNING_BULWARK, MOVE_HEAT_CRASH, MOVE_DRAGON_TAIL, MOVE_MORNING_SUN},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_RAGING_BOLT_3] = {
        .species = SPECIES_RAGING_BOLT,
        .moves = {MOVE_DRACO_METEOR, MOVE_THUNDERBOLT, MOVE_THUNDERCLAP, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_RAGING_BOLT_4] = {
        .species = SPECIES_RAGING_BOLT,
        .moves = {MOVE_CALM_MIND, MOVE_DRAGON_PULSE, MOVE_THUNDERCLAP, MOVE_REST},
        .heldItem = {ITEM_CHESTO_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PROTOSYNTHESIS,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_IRON_CROWN_3] = {
        .species = SPECIES_IRON_CROWN,
        .moves = {MOVE_CALM_MIND, MOVE_TACHYON_CUTTER, MOVE_STORED_POWER, MOVE_FOCUS_BLAST},
        .heldItem = {ITEM_BOOSTER_ENERGY},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_CROWN_4] = {
        .species = SPECIES_IRON_CROWN,
        .moves = {MOVE_TACHYON_CUTTER, MOVE_PSYCHIC, MOVE_FOCUS_BLAST, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_IRON_BOULDER_3] = {
        .species = SPECIES_IRON_BOULDER,
        .moves = {MOVE_MIGHTY_CLEAVE, MOVE_PSYCHO_CUT, MOVE_CLOSE_COMBAT, MOVE_EARTHQUAKE},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_IRON_BOULDER_4] = {
        .species = SPECIES_IRON_BOULDER,
        .moves = {MOVE_SWORDS_DANCE, MOVE_MIGHTY_CLEAVE, MOVE_CLOSE_COMBAT, MOVE_TAUNT},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_QUARK_DRIVE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ENAMORUS_3] = {
        .species = SPECIES_ENAMORUS_INCARNATE,
        .moves = {MOVE_MOONBLAST, MOVE_EARTH_POWER, MOVE_MYSTICAL_FIRE, MOVE_HEALING_WISH},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CONTRARY,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ENAMORUS_4] = {
        .species = SPECIES_ENAMORUS_INCARNATE,
        .moves = {MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_EARTH_POWER, MOVE_DRAINING_KISS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_CUTE_CHARM,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ENAMORUS_THERIAN_3] = {
        .species = SPECIES_ENAMORUS_THERIAN,
        .moves = {MOVE_IRON_DEFENSE, MOVE_CALM_MIND, MOVE_DRAINING_KISS, MOVE_EARTH_POWER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_OVERCOAT,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_ENAMORUS_THERIAN_4] = {
        .species = SPECIES_ENAMORUS_THERIAN,
        .moves = {MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_EARTH_POWER, MOVE_MYSTICAL_FIRE},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 0, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_OVERCOAT,
        .nature = NATURE_QUIET,
    },

    [FRONTIER_MON_MEWTWO_10] = {
        .species = SPECIES_MEWTWO,
        .moves = {MOVE_CALM_MIND, MOVE_PSYSTRIKE, MOVE_AURA_SPHERE, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MEWTWO_11] = {
        .species = SPECIES_MEWTWO,
        .moves = {MOVE_PSYSTRIKE, MOVE_ICE_BEAM, MOVE_AURA_SPHERE, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_UNNERVE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_MEW_8] = {
        .species = SPECIES_MEW,
        .moves = {MOVE_COSMIC_POWER, MOVE_STORED_POWER, MOVE_BODY_PRESS, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SYNCHRONIZE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MEW_9] = {
        .species = SPECIES_MEW,
        .moves = {MOVE_SPIKES, MOVE_STEALTH_ROCK, MOVE_TAUNT, MOVE_EXPLOSION},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 252, 0, 0),
        .ability = ABILITY_SYNCHRONIZE,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_LUGIA_6] = {
        .species = SPECIES_LUGIA,
        .moves = {MOVE_AEROBLAST, MOVE_TOXIC, MOVE_SUBSTITUTE, MOVE_ROOST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_MULTISCALE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_LUGIA_7] = {
        .species = SPECIES_LUGIA,
        .moves = {MOVE_DRAGON_TAIL, MOVE_AEROBLAST, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_HO_OH_6] = {
        .species = SPECIES_HO_OH,
        .moves = {MOVE_SACRED_FIRE, MOVE_BRAVE_BIRD, MOVE_WHIRLWIND, MOVE_RECOVER},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_HO_OH_7] = {
        .species = SPECIES_HO_OH,
        .moves = {MOVE_CURSE, MOVE_SACRED_FIRE, MOVE_BRAVE_BIRD, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_REGENERATOR,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_CELEBI_7] = {
        .species = SPECIES_CELEBI,
        .moves = {MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_GIGA_DRAIN, MOVE_RECOVER},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_CELEBI_8] = {
        .species = SPECIES_CELEBI,
        .moves = {MOVE_LEAF_STORM, MOVE_PSYCHIC, MOVE_DAZZLING_GLEAM, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_TIMID,
    },

    [FRONTIER_MON_KYOGRE_7] = {
        .species = SPECIES_KYOGRE,
        .moves = {MOVE_CALM_MIND, MOVE_SURF, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_DRIZZLE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_KYOGRE_8] = {
        .species = SPECIES_KYOGRE,
        .moves = {MOVE_WATER_SPOUT, MOVE_SURF, MOVE_THUNDER, MOVE_ICE_BEAM},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_DRIZZLE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GROUDON_7] = {
        .species = SPECIES_GROUDON,
        .moves = {MOVE_BULK_UP, MOVE_PRECIPICE_BLADES, MOVE_STONE_EDGE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_DROUGHT,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_GROUDON_8] = {
        .species = SPECIES_GROUDON,
        .moves = {MOVE_ERUPTION, MOVE_FIRE_BLAST, MOVE_EARTH_POWER, MOVE_SOLAR_BEAM},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_DROUGHT,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_RAYQUAZA_7] = {
        .species = SPECIES_RAYQUAZA,
        .moves = {MOVE_DRACO_METEOR, MOVE_HURRICANE, MOVE_FIRE_BLAST, MOVE_SURF},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_AIR_LOCK,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_RAYQUAZA_8] = {
        .species = SPECIES_RAYQUAZA,
        .moves = {MOVE_DRAGON_DANCE, MOVE_DRAGON_ASCENT, MOVE_EARTHQUAKE, MOVE_REST},
        .heldItem = {ITEM_LUM_BERRY},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_AIR_LOCK,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_JIRACHI_7] = {
        .species = SPECIES_JIRACHI,
        .moves = {MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_WISH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_JIRACHI_8] = {
        .species = SPECIES_JIRACHI,
        .moves = {MOVE_IRON_HEAD, MOVE_BODY_SLAM, MOVE_SUBSTITUTE, MOVE_WISH},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DIALGA_5] = {
        .species = SPECIES_DIALGA,
        .moves = {MOVE_DRACO_METEOR, MOVE_FLASH_CANNON, MOVE_FIRE_BLAST, MOVE_THUNDER},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_DIALGA_6] = {
        .species = SPECIES_DIALGA,
        .moves = {MOVE_BULK_UP, MOVE_DRAGON_CLAW, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DIALGA_ORIGIN_2] = {
        .species = SPECIES_DIALGA_ORIGIN,
        .moves = {MOVE_BULK_UP, MOVE_BODY_PRESS, MOVE_DRACO_METEOR, MOVE_REST},
        .heldItem = {ITEM_ADAMANT_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_DIALGA_ORIGIN_3] = {
        .species = SPECIES_DIALGA_ORIGIN,
        .moves = {MOVE_STEALTH_ROCK, MOVE_DRAGON_TAIL, MOVE_FLASH_CANNON, MOVE_FIRE_BLAST},
        .heldItem = {ITEM_ADAMANT_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 4, 252),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_CALM,
    },


    [FRONTIER_MON_PALKIA_5] = {
        .species = SPECIES_PALKIA,
        .moves = {MOVE_SPACIAL_REND, MOVE_HYDRO_PUMP, MOVE_THUNDER, MOVE_ICE_BEAM},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PALKIA_6] = {
        .species = SPECIES_PALKIA,
        .moves = {MOVE_SUBSTITUTE, MOVE_SPACIAL_REND, MOVE_SURF, MOVE_THUNDER_WAVE},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PALKIA_ORIGIN_2] = {
        .species = SPECIES_PALKIA_ORIGIN,
        .moves = {MOVE_SPACIAL_REND, MOVE_SURF, MOVE_EARTH_POWER, MOVE_REST},
        .heldItem = {ITEM_LUSTROUS_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PALKIA_ORIGIN_3] = {
        .species = SPECIES_PALKIA_ORIGIN,
        .moves = {MOVE_SUBSTITUTE, MOVE_SPACIAL_REND, MOVE_HYDRO_PUMP, MOVE_THUNDER_WAVE},
        .heldItem = {ITEM_LUSTROUS_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GIRATINA_ORIGIN_3] = {
        .species = SPECIES_GIRATINA_ORIGIN,
        .moves = {MOVE_HEX, MOVE_WILL_O_WISP, MOVE_DRACO_METEOR, MOVE_DEFOG},
        .heldItem = {ITEM_GRISEOUS_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GIRATINA_ORIGIN_4] = {
        .species = SPECIES_GIRATINA_ORIGIN,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_DRAGON_PULSE, MOVE_AURA_SPHERE},
        .heldItem = {ITEM_GRISEOUS_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_LEVITATE,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_GIRATINA_4] = {
        .species = SPECIES_GIRATINA_ALTERED,
        .moves = {MOVE_DRAGON_TAIL, MOVE_WILL_O_WISP, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_IMPISH,
    },


    [FRONTIER_MON_GIRATINA_5] = {
        .species = SPECIES_GIRATINA_ALTERED,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_PRESSURE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MANAPHY_8] = {
        .species = SPECIES_MANAPHY,
        .moves = {MOVE_TAKE_HEART, MOVE_SCALD, MOVE_RAIN_DANCE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MANAPHY_9] = {
        .species = SPECIES_MANAPHY,
        .moves = {MOVE_TAIL_GLOW, MOVE_SURF, MOVE_ENERGY_BALL, MOVE_PSYCHIC},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_PHIONE_6] = {
        .species = SPECIES_PHIONE,
        .moves = {MOVE_RAIN_DANCE, MOVE_SURF, MOVE_ICE_BEAM, MOVE_REST},
        .heldItem = {ITEM_DAMP_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_PHIONE_7] = {
        .species = SPECIES_PHIONE,
        .moves = {MOVE_TAKE_HEART, MOVE_SCALD, MOVE_RAIN_DANCE, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_HYDRATION,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_DARKRAI_6] = {
        .species = SPECIES_DARKRAI,
        .moves = {MOVE_DARK_VOID, MOVE_DARK_PULSE, MOVE_SUBSTITUTE, MOVE_NASTY_PLOT},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BAD_DREAMS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_DARKRAI_7] = {
        .species = SPECIES_DARKRAI,
        .moves = {MOVE_DARK_PULSE, MOVE_FOCUS_BLAST, MOVE_SLUDGE_BOMB, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_BAD_DREAMS,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SHAYMIN_7] = {
        .species = SPECIES_SHAYMIN_LAND,
        .moves = {MOVE_SEED_FLARE, MOVE_EARTH_POWER, MOVE_DAZZLING_GLEAM, MOVE_PSYCHIC},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SHAYMIN_8] = {
        .species = SPECIES_SHAYMIN_LAND,
        .moves = {MOVE_GIGA_DRAIN, MOVE_LEECH_SEED, MOVE_SUBSTITUTE, MOVE_SYNTHESIS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
        .ability = ABILITY_NATURAL_CURE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SHAYMIN_SKY_6] = {
        .species = SPECIES_SHAYMIN_SKY,
        .moves = {MOVE_SEED_FLARE, MOVE_AIR_SLASH, MOVE_PSYCHIC, MOVE_SUNNY_DAY},
        .heldItem = {ITEM_HEAT_ROCK},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_SHAYMIN_SKY_7] = {
        .species = SPECIES_SHAYMIN_SKY,
        .moves = {MOVE_GROWTH, MOVE_SEED_FLARE, MOVE_AIR_SLASH, MOVE_EARTH_POWER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_VICTINI_6] = {
        .species = SPECIES_VICTINI,
        .moves = {MOVE_WORK_UP, MOVE_SEARING_SHOT, MOVE_PSYCHIC, MOVE_THUNDER},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VICTORY_STAR,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_VICTINI_7] = {
        .species = SPECIES_VICTINI,
        .moves = {MOVE_V_CREATE, MOVE_WILD_CHARGE, MOVE_U_TURN, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_VICTORY_STAR,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MELOETTA_6] = {
        .species = SPECIES_MELOETTA_ARIA,
        .moves = {MOVE_CALM_MIND, MOVE_HYPER_VOICE, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MELOETTA_7] = {
        .species = SPECIES_MELOETTA_ARIA,
        .moves = {MOVE_HYPER_VOICE, MOVE_PSYSHOCK, MOVE_FOCUS_BLAST, MOVE_U_TURN},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_SERENE_GRACE,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_GENESECT_5] = {
        .species = SPECIES_GENESECT,
        .moves = {MOVE_FLAME_CHARGE, MOVE_BUG_BUZZ, MOVE_ICE_BEAM, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_LIFE_ORB},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(0, 4, 0, 252, 252, 0),
        .ability = ABILITY_DOWNLOAD,
        .nature = NATURE_NAIVE,
    },


    [FRONTIER_MON_GENESECT_6] = {
        .species = SPECIES_GENESECT,
        .moves = {MOVE_BUG_BUZZ, MOVE_FLASH_CANNON, MOVE_ICE_BEAM, MOVE_FLAMETHROWER},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_DOWNLOAD,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_DIANCIE_6] = {
        .species = SPECIES_DIANCIE,
        .moves = {MOVE_DIAMOND_STORM, MOVE_BODY_PRESS, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_DIANCIE_7] = {
        .species = SPECIES_DIANCIE,
        .moves = {MOVE_METEOR_BEAM, MOVE_MOONBLAST, MOVE_EARTH_POWER, MOVE_TRICK_ROOM},
        .heldItem = {ITEM_POWER_HERB},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_CLEAR_BODY,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_HOOPA_7] = {
        .species = SPECIES_HOOPA_CONFINED,
        .moves = {MOVE_SHADOW_BALL, MOVE_PSYSHOCK, MOVE_FOCUS_BLAST, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MAGICIAN,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_HOOPA_8] = {
        .species = SPECIES_HOOPA_CONFINED,
        .moves = {MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_REST},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_MAGICIAN,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_HOOPA_UNBOUND_5] = {
        .species = SPECIES_HOOPA_UNBOUND,
        .moves = {MOVE_DARK_PULSE, MOVE_PSYSHOCK, MOVE_FOCUS_BLAST, MOVE_THUNDERBOLT},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_MAGICIAN,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_HOOPA_UNBOUND_6] = {
        .species = SPECIES_HOOPA_UNBOUND,
        .moves = {MOVE_HYPERSPACE_FURY, MOVE_ZEN_HEADBUTT, MOVE_DRAIN_PUNCH, MOVE_TRICK},
        .heldItem = {ITEM_CHOICE_SCARF},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MAGICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MAGEARNA_7] = {
        .species = SPECIES_MAGEARNA,
        .moves = {MOVE_CALM_MIND, MOVE_SHIFT_GEAR, MOVE_STORED_POWER, MOVE_DRAINING_KISS},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 252, 0, 0, 4),
        .ability = ABILITY_SOUL_HEART,
        .nature = NATURE_BOLD,
    },


    [FRONTIER_MON_MAGEARNA_8] = {
        .species = SPECIES_MAGEARNA,
        .moves = {MOVE_FLEUR_CANNON, MOVE_FLASH_CANNON, MOVE_AURA_SPHERE, MOVE_VOLT_SWITCH},
        .heldItem = {ITEM_ASSAULT_VEST},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 252, 4),
        .ability = ABILITY_SOUL_HEART,
        .nature = NATURE_MODEST,
    },


    [FRONTIER_MON_MARSHADOW_6] = {
        .species = SPECIES_MARSHADOW,
        .moves = {MOVE_SPECTRAL_THIEF, MOVE_CLOSE_COMBAT, MOVE_SHADOW_SNEAK, MOVE_ENDEAVOR},
        .heldItem = {ITEM_FOCUS_SASH},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MARSHADOW_7] = {
        .species = SPECIES_MARSHADOW,
        .moves = {MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_SPECTRAL_THIEF, MOVE_SHADOW_SNEAK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_TECHNICIAN,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ZERAORA_7] = {
        .species = SPECIES_ZERAORA,
        .moves = {MOVE_THUNDERBOLT, MOVE_VOLT_SWITCH, MOVE_FOCUS_BLAST, MOVE_GRASS_KNOT},
        .heldItem = {ITEM_CHOICE_SPECS},
        .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(4, 0, 0, 252, 252, 0),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_TIMID,
    },


    [FRONTIER_MON_ZERAORA_8] = {
        .species = SPECIES_ZERAORA,
        .moves = {MOVE_BULK_UP, MOVE_PLASMA_FISTS, MOVE_DRAIN_PUNCH, MOVE_KNOCK_OFF},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_VOLT_ABSORB,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_MELMETAL_7] = {
        .species = SPECIES_MELMETAL,
        .moves = {MOVE_DOUBLE_IRON_BASH, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_SUPERPOWER},
        .heldItem = {ITEM_CHOICE_BAND},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 0, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_BRAVE,
    },


    [FRONTIER_MON_MELMETAL_8] = {
        .species = SPECIES_MELMETAL,
        .moves = {MOVE_ACID_ARMOR, MOVE_DOUBLE_IRON_BASH, MOVE_REST, MOVE_SLEEP_TALK},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_IRON_FIST,
        .nature = NATURE_CAREFUL,
    },


    [FRONTIER_MON_URSHIFU_SINGLE_STRIKE_5] = {
        .species = SPECIES_URSHIFU_SINGLE_STRIKE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_WICKED_BLOW, MOVE_CLOSE_COMBAT, MOVE_SUCKER_PUNCH},
        .heldItem = {ITEM_BLACK_GLASSES},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNSEEN_FIST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_URSHIFU_SINGLE_STRIKE_6] = {
        .species = SPECIES_URSHIFU_SINGLE_STRIKE,
        .moves = {MOVE_WICKED_BLOW, MOVE_DRAIN_PUNCH, MOVE_U_TURN, MOVE_TAUNT},
        .heldItem = {ITEM_PROTECTIVE_PADS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNSEEN_FIST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_URSHIFU_RAPID_STRIKE_5] = {
        .species = SPECIES_URSHIFU_RAPID_STRIKE,
        .moves = {MOVE_SWORDS_DANCE, MOVE_SURGING_STRIKES, MOVE_CLOSE_COMBAT, MOVE_AQUA_JET},
        .heldItem = {ITEM_MYSTIC_WATER},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNSEEN_FIST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_URSHIFU_RAPID_STRIKE_6] = {
        .species = SPECIES_URSHIFU_RAPID_STRIKE,
        .moves = {MOVE_SURGING_STRIKES, MOVE_DRAIN_PUNCH, MOVE_U_TURN, MOVE_TAUNT},
        .heldItem = {ITEM_PROTECTIVE_PADS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_UNSEEN_FIST,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ZARUDE_5] = {
        .species = SPECIES_ZARUDE,
        .moves = {MOVE_SUBSTITUTE, MOVE_BULK_UP, MOVE_DARKEST_LARIAT, MOVE_JUNGLE_HEALING},
        .heldItem = {ITEM_LEFTOVERS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_LEAF_GUARD,
        .nature = NATURE_JOLLY,
    },


    [FRONTIER_MON_ZARUDE_6] = {
        .species = SPECIES_ZARUDE,
        .moves = {MOVE_POWER_WHIP, MOVE_U_TURN, MOVE_ENCORE, MOVE_JUNGLE_HEALING},
        .heldItem = {ITEM_HEAVY_DUTY_BOOTS},
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 0, 31),
        .ev = TRAINER_PARTY_EVS(252, 4, 0, 0, 0, 252),
        .ability = ABILITY_LEAF_GUARD,
        .nature = NATURE_CAREFUL,
    },
