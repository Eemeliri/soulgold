const struct AbilityInfo gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("No special ability."),
        .longDescription = COMPOUND_STRING("No special ability.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "               "),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = _("Stench"),
        .description = COMPOUND_STRING("May cause a foe to flinch."),
        .longDescription = COMPOUND_STRING("Moves that deal damage\n"
                                           "have a 10% flinch chance.\n"
                                           "When first in the party,\n"
                                           "wild encounter rate is\n"
                                           "reduced by 50%."),
        .aiRating = 1,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = _("Drizzle"),
        .description = COMPOUND_STRING("Summons rain in battle."),
        .longDescription = COMPOUND_STRING("Summons rain for 5 turns\n"
                                           "when the Pokémon enters\n"
                                           "a battle."),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = _("Speed Boost"),
        .description = COMPOUND_STRING("Gradually boosts Speed."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "Speed stat by 1 stage at\n"
                                           "the end of every turn."),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = _("Battle Armor"),
        .description = COMPOUND_STRING("Blocks critical hits."),
        .longDescription = COMPOUND_STRING("Attacks landed on the\n"
                                           "Pokémon will never be\n"
                                           "critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_STURDY] =
    {
        .name = _("Sturdy"),
        .description = COMPOUND_STRING("Negates 1-hit KO attacks."),
        .longDescription = COMPOUND_STRING("If the Pokémon has full\n"
                                           "HP and takes damage\n"
                                           "from a move that would\n"
                                           "knock it out in one hit,\n"
                                           "it will endure the hit\n"
                                           "with 1 HP"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = _("Damp"),
        .description = COMPOUND_STRING("Prevents self-destruction."),
        .longDescription = COMPOUND_STRING("All Pokémon become\n"
                                           "unable to use explosive\n"
                                           "moves or Abilities."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = _("Limber"),
        .description = COMPOUND_STRING("Prevents paralysis."),
        .longDescription = COMPOUND_STRING("The Pokémon's limber\n"
                                           "body prevents it from\n"
                                           "being paralyzed."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = _("Sand Veil"),
        .description = COMPOUND_STRING("Ups evasion in a sandstorm."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "evasiveness by 25% in a\n"
                                           "sandstorm. Reduces wild\n"
                                           "encounter rate by 50%\n"
                                           "when first in the party."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = _("Static"),
        .description = COMPOUND_STRING("Paralyzes on contact."),
        .longDescription = COMPOUND_STRING("Contact has a 30% chance\n"
                                           "to paralyze the attacker.\n"
                                           "When first in the party,\n"
                                           "Electric Pokemon appear\n"
                                           "more often."),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = _("Volt Absorb"),
        .description = COMPOUND_STRING("Turns electricity into HP."),
        .longDescription = COMPOUND_STRING("Electric-type moves do\n"
                                           "not work on the Pokémon.\n"
                                           "Instead, they restore\n"
                                           "1/4 of its max HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = _("Water Absorb"),
        .description = COMPOUND_STRING("Changes water into HP."),
        .longDescription = COMPOUND_STRING("Water-type moves do\n"
                                           "not work on the Pokémon.\n"
                                           "Instead, they restore\n"
                                           "1/4 of its max HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = _("Oblivious"),
        .description = COMPOUND_STRING("Prevents attraction."),
        .longDescription = COMPOUND_STRING("Not affected by Taunt,\n"
                                           "Infatuation, or\n"
                                           "Intimidate."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = _("Cloud Nine"),
        .description = COMPOUND_STRING("Negates weather effects."),
        .longDescription = COMPOUND_STRING("Eliminates the effects\n"
                                           "of weather."),
        .aiRating = 5,
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .name = _("Compound Eyes"),
        .description = COMPOUND_STRING("Raises accuracy."),
        .longDescription = COMPOUND_STRING("Boosts the accuracy of\n"
                                           "the Pokémon's moves\n"
                                           "by 30%."),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = _("Insomnia"),
        .description = COMPOUND_STRING("Prevents sleep."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot\n"
                                           "become drowsy or be\n"
                                           "put to sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = _("Color Change"),
        .description = COMPOUND_STRING("Changes type to foe's move."),
        .longDescription = COMPOUND_STRING("The Pokémon's type\n"
                                           "becomes the type of the\n"
                                           "move used on it."),
        .aiRating = 2,
    },

    [ABILITY_IMMUNITY] =
    {
        .name = _("Immunity"),
        .description = COMPOUND_STRING("Prevents poisoning."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot be\n"
                                           "poisoned or\n"
                                           "badly poisoned."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = _("Flash Fire"),
        .description = COMPOUND_STRING("Powers up if hit by fire."),
        .longDescription = COMPOUND_STRING("Absorbs Fire-type moves\n"
                                           "to boost own Fire moves\n"
                                           "by 50%. When first in\n"
                                           "party, Fire Pokemon\n"
                                           "appear more often."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = _("Shield Dust"),
        .description = COMPOUND_STRING("Prevents added effects."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune to\n"
                                           "additional effects\n"
                                           "from attacks."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = _("Own Tempo"),
        .description = COMPOUND_STRING("Prevents confusion."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot\n"
                                           #if B_UPDATED_INTIMIDATE < GEN_8
                                           "become confused."),
                                           #else
                                           "become confused and is\n"
                                           "unaffected by\n"
                                           "Intimidate."),
                                           #endif
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = _("Suction Cups"),
        .description = COMPOUND_STRING("Firmly anchors the body."),
        .longDescription = COMPOUND_STRING("Cannot be forced to\n"
                                           "switch out. When first\n"
                                           "in party, increases the\n"
                                           "chance of fishing bites."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = _("Intimidate"),
        .description = COMPOUND_STRING("Lowers the foe's Attack."),
        .longDescription = COMPOUND_STRING("When entering a battle,\n"
                                           "lowers the Attack of\n"
                                           "of opponents by 1 stage.\n"
                                           "Reduces wild encounters\n"
                                           "5 levels or lower by 50%\n"
                                           "when first in the party."),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = _("Shadow Tag"),
        .description = COMPOUND_STRING("Prevents the foe's escape."),
        .longDescription = COMPOUND_STRING("Opponents cannot switch\n"
                                           "out of battle. Does not\n"
                                           #if B_SHADOW_TAG_ESCAPE < GEN_4
                                           "affect Ghost Pokémon."),
                                           #else
                                           "affect Ghost Pokémon.\n"
                                           "Negated if opponents\n"
                                           "also have Shadow Tag."),
                                           #endif
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = _("Rough Skin"),
        .description = COMPOUND_STRING("Hurts to touch."),
        .longDescription = COMPOUND_STRING("When the Pokémon is hit\n"
                                           "by a contact move, the\n"
                                           "attacker takes damage\n"
                                           "equal to 1/8 of its\n"
                                           "max HP."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = _("Wonder Guard"),
        .description = COMPOUND_STRING("Only “Supereffective” hits."),
        .longDescription = COMPOUND_STRING("Moves can only deal\n"
                                           "Supereffective damage.\n"
                                           "Indirect damage is\n"
                                           "unaffected."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_LEVITATE] =
    {
        .name = _("Levitate"),
        .description = COMPOUND_STRING("Not hit by Ground attacks."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune to\n"
                                           "Ground-type moves, as\n"
                                           "well as the Spikes,\n"
                                           "Toxic Spikes, and\n"
                                           "Sticky Web statuses."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .name = _("Effect Spore"),
        .description = COMPOUND_STRING("Leaves spores on contact."),
        .longDescription = COMPOUND_STRING("When hit by a move that\n"
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_4
                                           "makes contact, has a 33%\n"
                                           #else
                                           "makes contact, has a 30%\n"
                                           #endif
                                           "chance to inflict\n"
                                           "poison, sleep,\n"
                                           "or paralysis."),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = _("Synchronize"),
        .description = COMPOUND_STRING("Passes on status problems."),
        .longDescription = COMPOUND_STRING("Copies paralysis, poison,\n"
                                           "or burn statuses onto\n"
                                           "the Pokémon inflicting\n"
                                           "them. When first in the\n"
                                           "party, wild pokemon will\n"
                                           "have a matching nature."),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = _("Clear Body"),
        .description = COMPOUND_STRING("Prevents ability reduction."),
        .longDescription = COMPOUND_STRING("The Pokémon's stats\n"
                                           "cannot be lowered by\n"
                                           "other Pokémon's moves or\n"
                                           "Abilities."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = _("Natural Cure"),
        .description = COMPOUND_STRING("Heals upon switching out."),
        .longDescription = COMPOUND_STRING("The Pokémon's status\n"
                                           "conditions are cured\n"
                                           "when it switches out of\n"
                                           "battle."),
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = _("Lightning Rod"),
        .description = COMPOUND_STRING("Draws electrical moves."),
        .longDescription = COMPOUND_STRING("Draws Electric moves to\n"
                                           "raise Sp. Atk by 1 stage.\n"
                                           "When first in the party,\n"
                                           "Electric Pokemon appear\n"
                                           "more often."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = _("Serene Grace"),
        .description = COMPOUND_STRING("Promotes added effects."),
        .longDescription = COMPOUND_STRING("Doubles the likelihood\n"
                                           "of additional effects\n"
                                           "occurring when the\n"
                                           "Pokémon uses its moves."
                                           #if B_SERENE_GRACE_BOOST < GEN_5
                                           "\nKing's Rock and Razor\n"
                                           "Fang are excluded."
                                           #endif
                                           ),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = _("Swift Swim"),
        .description = COMPOUND_STRING("Raises Speed in rain."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Speed stat in rain."),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = _("Chlorophyll"),
        .description = COMPOUND_STRING("Raises Speed in sunshine."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Speed stat in harsh\n"
                                           "sunlight."),
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = _("Illuminate"),
        .description = COMPOUND_STRING("Encounter rate increases."),
        .longDescription = COMPOUND_STRING("Doubles wild encounter\n"
                                           "rate. In battle, ignores\n"
                                           "foes' evasion and blocks\n"
                                           "accuracy drops."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_TRACE] =
    {
        .name = _("Trace"),
        .description = COMPOUND_STRING("Copies special ability."),
        .longDescription = COMPOUND_STRING("When the Pokémon enters\n"
                                           "a battle, it changes its \n"
                                           "Ability to match that of\n"
                                           "an opponent with some\n"
                                           "exceptions."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE, //B_UPDATED_ABILITY_DATA >= GEN_4
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = _("Huge Power"),
        .description = COMPOUND_STRING("Raises Attack."),
        .longDescription = COMPOUND_STRING("Doubles the power of\n"
                                           "the Pokémon's physical\n"
                                           "moves.\n"),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = _("Poison Point"),
        .description = COMPOUND_STRING("Poisons foe on contact."),
        .longDescription = COMPOUND_STRING("When the Pokémon is hit\n"
                                           "by a contact move,\n"
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_4
                                           "the attacker has a 33%\n"
                                           #else
                                           "the attacker has a 30%\n"
                                           #endif
                                           "chance of being\n"
                                           "poisoned."),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = _("Inner Focus"),
        .description = COMPOUND_STRING("Prevents flinching."),
        .longDescription = COMPOUND_STRING("The Pokémon never\n"
                                           #if B_UPDATED_INTIMIDATE < GEN_8
                                           "flinches when attacked.),"
                                           #else
                                           "flinches when attacked\n"
                                           "and is unaffected by\n"
                                           "Intimidate."),
                                           #endif

        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = _("Magma Armor"),
        .description = COMPOUND_STRING("Prevents freezing."),
        .longDescription = COMPOUND_STRING("Prevents freezing. Eggs\n"
                                           "hatch faster while this\n"
                                           "Pokemon is in the party."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_WATER_VEIL] =
    {
        .name = _("Water Veil"),
        .description = COMPOUND_STRING("Prevents burns."),
        .longDescription = COMPOUND_STRING("The Pokémon's water veil\n"
                                           "prevents it from being\n"
                                           "burned."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = _("Magnet Pull"),
        .description = COMPOUND_STRING("Traps Steel-type Pokémon."),
        .longDescription = COMPOUND_STRING("Prevents adjacent\n"
                                           "Steel-type foes from\n"
                                           "fleeing or switching.\n"
                                           "In the lead party slot,\n"
                                           "Steel Pokemon appear\n"
                                           "more often."),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = _("Soundproof"),
        .description = COMPOUND_STRING("Avoids sound-based moves."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune to\n"
                                           "sound-based moves,\n"
                                           "including its own."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = _("Rain Dish"),
        .description = COMPOUND_STRING("Slight HP recovery in rain."),
        .longDescription = COMPOUND_STRING("Restores 1/16 max HP\n"
                                           "at the end of each turn\n"
                                           "while rain is active."),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = _("Sand Stream"),
        .description = COMPOUND_STRING("Summons a sandstorm."),
        .longDescription = COMPOUND_STRING("Summons a sandstorm for\n"
                                           "5 turns when the Pokémon\n"
                                           "enters a battle."),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = _("Pressure"),
        .description = COMPOUND_STRING("Raises foe's PP usage."),
        .longDescription = COMPOUND_STRING("Opponents use 2 PP per\n"
                                           "move used against the\n"
                                           "Pokémon instead of 1."),
        .aiRating = 5,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = _("Thick Fat"),
        .description = COMPOUND_STRING("Heat-and-cold protection."),
        .longDescription = COMPOUND_STRING("Halves the damage taken\n"
                                           "from Fire-type and\n"
                                           "Ice-type moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = _("Early Bird"),
        .description = COMPOUND_STRING("Awakens quickly from sleep."),
        .longDescription = COMPOUND_STRING("The Pokémon recovers\n"
                                           "from sleep in half the\n"
                                           "usual number of turns."),
        .aiRating = 4,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = _("Flame Body"),
        .description = COMPOUND_STRING("Burns the foe on contact."),
        .longDescription = COMPOUND_STRING("Contact with the Pokemon\n"
                                           "has a 30% chance to burn.\n"
                                           "Eggs hatch faster while\n"
                                           "this Pokemon is in the\n"
                                           "party."),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = _("Run Away"),
        .description = COMPOUND_STRING("Makes escaping easier."),
        .longDescription = COMPOUND_STRING("The Pokémon can always\n"
                                           "flee from wild battles,\n"
                                           "even when trapped."),
        .aiRating = 0,
    },

    [ABILITY_KEEN_EYE] =
    {
        .name = _("Keen Eye"),
        .description = COMPOUND_STRING("Prevents loss of accuracy."),
        .longDescription = COMPOUND_STRING("Prevents loss of\n"
                                           "accuracy. Additionally Boosts\n"
                                           "the accuracy of the Pokémon's\n"
                                           "moves by 30%."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .name = _("Hyper Cutter"),
        .description = COMPOUND_STRING("Prevents Attack reduction."),
        .longDescription = COMPOUND_STRING("Attack cannot be lowered\n"
                                           "by other Pokemon's moves\n"
                                           "or Abilities."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = _("Pickup"),
        .description = COMPOUND_STRING("May pick up items."),
        .longDescription = COMPOUND_STRING("May pick up an item\n"
                                           "after battle if not\n"
                                           "already holding one."),
        .aiRating = 1,
    },

    [ABILITY_TRUANT] =
    {
        .name = _("Truant"),
        .description = COMPOUND_STRING("Moves only every two turns."),
        .longDescription = COMPOUND_STRING("Every other turn, the\n"
                                           "Pokemon loafs around\n"
                                           "instead of using a move."),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HUSTLE] =
    {
        .name = _("Hustle"),
        .description = COMPOUND_STRING("Trades accuracy for power."),
        .longDescription = COMPOUND_STRING("Physical moves deal 50%\n"
                                           "more damage, but their\n"
                                           "accuracy is reduced to\n"
                                           "80%."),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = _("Cute Charm"),
        .description = COMPOUND_STRING("Infatuates on contact."),
        .longDescription = COMPOUND_STRING("When hit by a contact\n"
                                           "move, has a 30% chance\n"
                                           "of infatuating an\n"
                                           "opposite-gender\n"
                                           "attacker."),
        .aiRating = 2,
    },

    [ABILITY_PLUS] =
    {
        .name = _("Plus"),
        .description = COMPOUND_STRING("Powers up with Minus."),
        .longDescription = COMPOUND_STRING("Raises Sp. Atk by 50%\n"
                                           "if an ally in battle\n"
                                           "has Plus or Minus."),
        .aiRating = 0,
    },

    [ABILITY_MINUS] =
    {
        .name = _("Minus"),
        .description = COMPOUND_STRING("Powers up with Plus."),
        .longDescription = COMPOUND_STRING("Raises Sp. Atk by 50%\n"
                                           "if an ally in battle\n"
                                           "has Plus or Minus."),
        .aiRating = 0,
    },

    [ABILITY_FORECAST] =
    {
        .name = _("Forecast"),
        .description = COMPOUND_STRING("Changes with the weather."),
        .longDescription = COMPOUND_STRING("During rain, sun, or icy\n"
                                           "weather, Castform changes\n"
                                           "to Water, Fire, or Ice\n"
                                           "type and matching form."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_4,
        .failsOnImposter = B_UPDATED_ABILITY_DATA >= GEN_5,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = _("Sticky Hold"),
        .description = COMPOUND_STRING("Prevents item theft."),
        .longDescription = COMPOUND_STRING("The Pokémon's held item\n"
                                           "cannot be removed or\n"
                                           "stolen by other Pokémon."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = _("Shed Skin"),
        .description = COMPOUND_STRING("Heals the body by shedding."),
        .longDescription = COMPOUND_STRING("Pokemon may cure it's  \n"
                                           "status problems by shedding\n"
                                           "its skin.                  \n"
                                           "               "),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = _("Guts"),
        .description = COMPOUND_STRING("Ups Attack if suffering."),
        .longDescription = COMPOUND_STRING("Boosts Attack by 50%\n"
                                           "when the Pokémon is\n"
                                           "afflicted by a status\n"
                                           "condition. Burn's Attack\n"
                                           "drop is also ignored."),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = _("Marvel Scale"),
        .description = COMPOUND_STRING("Ups Defense if suffering."),
        .longDescription = COMPOUND_STRING("Raises Defense by 50% when\n"
                                           "inflicted by a major status\n"
                                           "effect such as Poison.  \n"
                                           "               "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = _("Liquid Ooze"),
        .description = COMPOUND_STRING("Draining causes injury."),
        .longDescription = COMPOUND_STRING("Pokémon that drain HP\n"
                                           "from this Pokémon lose\n"
                                           "HP instead of gaining it."),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = _("Overgrow"),
        .description = COMPOUND_STRING("Ups Grass moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Grass-type moves by\n"
                                           "50% when its HP drops to 1/3\n"
                                           "or less of its max."),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = _("Blaze"),
        .description = COMPOUND_STRING("Ups Fire moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Fire-type moves by\n"
                                           "50% when its HP drops to 1/3\n"
                                           "or less of its max."),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = _("Torrent"),
        .description = COMPOUND_STRING("Ups Water moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Water-type moves by\n"
                                           "50% when its HP drops to 1/3\n"
                                           "or less of its max."),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = _("Swarm"),
        .description = COMPOUND_STRING("Ups Bug moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Bug-type moves by\n"
                                           "50% when its HP drops to 1/3\n"
                                           "or less of its max."),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = _("Rock Head"),
        .description = COMPOUND_STRING("Prevents recoil damage."),
        .longDescription = COMPOUND_STRING("The Pokémon takes no\n"
                                           "recoil damage from its\n"
                                           "own attacking moves."),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = _("Drought"),
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .longDescription = COMPOUND_STRING("Summons harsh sunlight in\n"
                                           "battle. Lasts for 5 turns\n"
                                           "unless cleared by Air Lock\n"
                                           "or Cloud Nine. "),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = _("Arena Trap"),
        .description = COMPOUND_STRING("Prevents fleeing."),
        .longDescription = COMPOUND_STRING("Opponents cannot switch\n"
                                           "out or flee. Does not\n"
                                           "affect Flying-types or\n"
                                           "Pokémon that are\n"
                                           "airborne."),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = _("Vital Spirit"),
        .description = COMPOUND_STRING("Prevents sleep."),
        .longDescription = COMPOUND_STRING("The Pokémon is alert\n"
                                           "and cannot become\n"
                                           "drowsy or fall asleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = _("White Smoke"),
        .description = COMPOUND_STRING("Prevents ability reduction."),
        .longDescription = COMPOUND_STRING("Prevents other Pokémon\n"
                                           "from lowering its stats\n"
                                           "                        \n"
                                           "               "),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = _("Pure Power"),
        .description = COMPOUND_STRING("Raises Attack."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Attack stat."),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = _("Shell Armor"),
        .description = COMPOUND_STRING("Blocks critical hits."),
        .longDescription = COMPOUND_STRING("Attacks landed on the\n"
                                           "Pokémon will never be\n"
                                           "critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_AIR_LOCK] =
    {
        .name = _("Air Lock"),
        .description = COMPOUND_STRING("Negates weather effects."),
        .longDescription = COMPOUND_STRING("Suppresses all weather\n"
                                           "effects while the Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = _("Tangled Feet"),
        .description = COMPOUND_STRING("Ups evasion if confused."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "evasiveness while it\n"
                                           "is confused."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = _("Motor Drive"),
        .description = COMPOUND_STRING("Electricity raises Speed."),
        .longDescription = COMPOUND_STRING("Being hit by electricity\n"
                                           "raisesd Speed by one stage.\n"
                                           "                        \n"
                                           "               "),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = _("Rivalry"),
        .description = COMPOUND_STRING("Powers up against rivals."),
        .longDescription = COMPOUND_STRING("Deals more damage against\n"
                                           "Pokémon of the same gender.\n"
                                           "                        \n"
                                           "               "),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = _("Steadfast"),
        .description = COMPOUND_STRING("Flinching raises Speed."),
        .longDescription = COMPOUND_STRING("Raises the Pokémon's\n"
                                           "Speed by 1 stage each\n"
                                           "time it flinches."),
        .aiRating = 2,
    },

    [ABILITY_SNOW_CLOAK] =
    {
        .name = _("Snow Cloak"),
        .description = COMPOUND_STRING("Ups evasion in Hail or Snow."),
        .longDescription = COMPOUND_STRING("Ups evasion in Hail or\n"
                                           "Snow by 20%. Also gives\n"
                                           "immunity to hail damage.\n"
                                           "               "),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .name = _("Gluttony"),
        .description = COMPOUND_STRING("Eats Berries early."),
        .longDescription = COMPOUND_STRING("The Pokémon eats its\n"
                                           "held Berry when its HP\n"
                                           "drops to 1/2 instead\n"
                                           "of the usual 1/4."),
        .aiRating = 3,
    },

    [ABILITY_ANGER_POINT] =
    {
        .name = _("Anger Point"),
        .description = COMPOUND_STRING("Critical hits raise Attack."),
        .longDescription = COMPOUND_STRING("Taking a critical hit\n"
                                           "raises Attack to the\n"
                                           "maximum of 6 stages."),
        .aiRating = 4,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = _("Unburden"),
        .description = COMPOUND_STRING("Using a hold item ups Speed."),
        .longDescription = COMPOUND_STRING("Using or losing a held\n"
                                           "item doubles Speed until\n"
                                           "the Pokemon leaves battle\n"
                                           "or gains a new item."),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = _("Heatproof"),
        .description = COMPOUND_STRING("Heat and burn protection."),
        .longDescription = COMPOUND_STRING("Halves damage from\n"
                                           "Fire-type moves and burn\n"
                                           "damage."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("Simple"),
        .description = COMPOUND_STRING("Prone to wild stat changes."),
        .longDescription = COMPOUND_STRING("Stat changes count double\n"
                                           "for this Pokemon, still\n"
                                           "capped at -6 and +6."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = _("Dry Skin"),
        .description = COMPOUND_STRING("Prefers moisture to heat."),
        .longDescription = COMPOUND_STRING("Heals 1/8 HP in rain,\n"
                                           "loses 1/8 HP in sun,\n"
                                           "absorbs Water moves, and\n"
                                           "takes extra Fire damage."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = _("Download"),
        .description = COMPOUND_STRING("Adjusts power favorably."),
        .longDescription = COMPOUND_STRING("On entry, raises Attack\n"
                                           "or Sp. Atk by 1 stage,\n"
                                           "whichever counters the\n"
                                           "foe's lower defense."),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = _("Iron Fist"),
        .description = COMPOUND_STRING("Boosts punching moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "punching moves by 20%."),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = _("Poison Heal"),
        .description = COMPOUND_STRING("Restores HP if poisoned."),
        .longDescription = COMPOUND_STRING("Restores 1/8 of max HP\n"
                                           "each turn when poisoned\n"
                                           "instead of taking\n"
                                           "poison damage."),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = _("Adaptability"),
        .description = COMPOUND_STRING("Boosts same type attacks."),
        .longDescription = COMPOUND_STRING("Same-type attack bonus\n"
                                           "is 2x instead of 1.5x\n"
                                           "for the Pokémon's moves."),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = _("Skill Link"),
        .description = COMPOUND_STRING("Multi-hit moves hit 5 times."),
        .longDescription = COMPOUND_STRING("Multi-hit moves that hit\n"
                                           "2 to 5 times always land\n"
                                           "all 5 hits."),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = _("Hydration"),
        .description = COMPOUND_STRING("Cures status in rain."),
        .longDescription = COMPOUND_STRING("Cures any status\n"
                                           "condition at the end of\n"
                                           "each turn while it is\n"
                                           "raining."),
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .name = _("Solar Power"),
        .description = COMPOUND_STRING("Powers up in sunshine."),
        .longDescription = COMPOUND_STRING("In harsh sunlight,\n"
                                           "raises Sp. Atk by 50%\n"
                                           "but loses 1/8 of max HP\n"
                                           "at the end of each turn."),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = _("Quick Feet"),
        .description = COMPOUND_STRING("Ups Speed if suffering."),
        .longDescription = COMPOUND_STRING("Boosts Speed by 50%\n"
                                           "when afflicted by a\n"
                                           "status condition, and\n"
                                           "ignores paralysis'\n"
                                           "Speed drop."),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = _("Normalize"),
        .description = COMPOUND_STRING("Moves become Normal-type."),
        .longDescription = COMPOUND_STRING("All of the Pokémon's\n"
                                           "moves become Normal-type\n"
                                           "and deal 20% more damage."),
        .aiRating = -1,
    },

    [ABILITY_SNIPER] =
    {
        .name = _("Sniper"),
        .description = COMPOUND_STRING("Boosts critical hits."),
        .longDescription = COMPOUND_STRING("Critical hits deal 2.25x\n"
                                           "damage instead of the\n"
                                           "usual 1.5x."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = _("Magic Guard"),
        .description = COMPOUND_STRING("Only damaged by attacks."),
        .longDescription = COMPOUND_STRING("The Pokémon only takes\n"
                                           "damage from direct\n"
                                           "attacks. Indirect damage\n"
                                           "does not affect it."),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = _("No Guard"),
        .description = COMPOUND_STRING("Ensures that all moves hit."),
        .longDescription = COMPOUND_STRING("All moves used by or\n"
                                           "against this Pokemon\n"
                                           "never miss."),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = _("Stall"),
        .description = COMPOUND_STRING("Always moves last."),
        .longDescription = COMPOUND_STRING("The Pokémon moves last\n"
                                           "within its priority\n"
                                           "bracket every turn."),
        .aiRating = -1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = _("Technician"),
        .description = COMPOUND_STRING("Boosts weaker moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "moves with 60 base\n"
                                           "power or less by 50%."),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = _("Leaf Guard"),
        .description = COMPOUND_STRING("Blocks status in sunshine."),
        .longDescription = COMPOUND_STRING("Prevents major status\n"
                                           "conditions while harsh\n"
                                           "sunlight is active."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = _("Klutz"),
        .description = COMPOUND_STRING("Can't use hold items."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot use\n"
                                           "the effects of its\n"
                                           "held item."),
        .aiRating = -1,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = _("Mold Breaker"),
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .longDescription = COMPOUND_STRING("Moves ignore Abilities\n"
                                           "that would hinder or\n"
                                           "prevent their effects."),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = _("Super Luck"),
        .description = COMPOUND_STRING("Critical hits land often."),
        .longDescription = COMPOUND_STRING("Raises this Pokemon's\n"
                                           "critical-hit ratio by\n"
                                           "1 stage."),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = _("Aftermath"),
        .description = COMPOUND_STRING("Fainting damages the foe."),
        .longDescription = COMPOUND_STRING("If knocked out by a\n"
                                           "contact move, damages the\n"
                                           "attacker for 1/4 of its\n"
                                           "max HP."),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = _("Anticipation"),
        .description = COMPOUND_STRING("Senses dangerous moves."),
        .longDescription = COMPOUND_STRING("On entry, shudders if a\n"
                                           "foe has a supereffective\n"
                                           "or OHKO move."),
        .aiRating = 2,
    },

    [ABILITY_FOREWARN] =
    {
        .name = _("Forewarn"),
        .description = COMPOUND_STRING("Determines a foe's move."),
        .longDescription = COMPOUND_STRING("On entry, reveals the\n"
                                           "move with the highest\n"
                                           "power among the foe's\n"
                                           "Pokémon."),
        .aiRating = 2,
    },

    [ABILITY_UNAWARE] =
    {
        .name = _("Unaware"),
        .description = COMPOUND_STRING("Ignores stat changes."),
        .longDescription = COMPOUND_STRING("Ignores the foe's stat\n"
                                           "stage changes when\n"
                                           "dealing or taking damage."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = _("Tinted Lens"),
        .description = COMPOUND_STRING("Ups “not very effective”."),
        .longDescription = COMPOUND_STRING("Doubles the damage of\n"
                                           "not very effective moves\n"
                                           "used by this Pokemon."),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = _("Filter"),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .longDescription = COMPOUND_STRING("Reduces damage from\n"
                                           "super effective moves to\n"
                                           "75%."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = _("Slow Start"),
        .description = COMPOUND_STRING("Takes a while to get going."),
        .longDescription = COMPOUND_STRING("For 5 turns after entry,\n"
                                           "Attack and Speed are\n"
                                           "halved."),
        .aiRating = -2,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = _("Scrappy"),
        .description = COMPOUND_STRING("Hits Ghost-type Pokémon."),
        .longDescription = COMPOUND_STRING("Normal- and Fighting-\n"
                                           "type moves can hit Ghost-\n"
                                           "type Pokemon."),
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .name = _("Storm Drain"),
        .description = COMPOUND_STRING("Draws in Water moves."),
        .longDescription = COMPOUND_STRING("Draws in all Water-type\n"
                                           "moves, taking no damage\n"
                                           "and raising its Sp. Atk\n"
                                           "by 1 stage instead."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .name = _("Ice Body"),
        .description = COMPOUND_STRING("HP recovery in Hail or Snow."),
        .longDescription = COMPOUND_STRING("Restores 1/16 max HP at\n"
                                           "each turn's end during\n"
                                           "hail or snow, and blocks\n"
                                           "hail damage."),
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .name = _("Solid Rock"),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .longDescription = COMPOUND_STRING("Reduces damage from\n"
                                           "super effective moves to\n"
                                           "75%."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = _("Snow Warning"),
    #if B_SNOW_WARNING >= GEN_9
        .description = COMPOUND_STRING("Summons snow in battle."),
        .longDescription = COMPOUND_STRING("Summons a snowstorm for\n"
                                           "5 turns when the Pokémon\n"
                                           "enters a battle."),
    #else
        .description = COMPOUND_STRING("Summons hail in battle."),
        .longDescription = COMPOUND_STRING("Summons hail in battle.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "               "),
    #endif
        .aiRating = 8,
    },

    [ABILITY_HONEY_GATHER] =
    {
        .name = _("Honey Gather"),
        .description = COMPOUND_STRING("May gather Honey."),
        .longDescription = COMPOUND_STRING("May gather a Honey item\n"
                                           "after battle if not\n"
                                           "holding an item."),
        .aiRating = 0,
    },

    [ABILITY_FRISK] =
    {
        .name = _("Frisk"),
        .description = COMPOUND_STRING("Checks a foe's item."),
        .longDescription = COMPOUND_STRING("On entry, reveals the\n"
                                           "held items of opposing\n"
                                           "Pokémon."),
        .aiRating = 3,
    },

    [ABILITY_RECKLESS] =
    {
        .name = _("Reckless"),
        .description = COMPOUND_STRING("Boosts moves with recoil."),
        .longDescription = COMPOUND_STRING("Boosts recoil and crash\n"
                                           "moves by 20%."),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = _("Multitype"),
        .description = COMPOUND_STRING("Changes type to its Plate."),
        .longDescription = COMPOUND_STRING("Changes Arceus's type to\n"
                                           "match its held Plate and\n"
                                           "prevents item removal."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = B_UPDATED_ABILITY_DATA >= GEN_5,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .name = _("Flower Gift"),
        .description = COMPOUND_STRING("Allies power up in sunshine."),
        .longDescription = COMPOUND_STRING("In harsh sunlight, allies'\n"
                                           "Attack and Sp. Def are\n"
                                           "raised by 50%."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_5,
        .breakable = TRUE,
    },

    [ABILITY_BAD_DREAMS] =
    {
        .name = _("Bad Dreams"),
        .description = COMPOUND_STRING("Damages sleeping Pokémon."),
        .longDescription = COMPOUND_STRING("Sleeping opposing Pokemon\n"
                                           "lose 1/8 max HP at the\n"
                                           "end of each turn."),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = _("Pickpocket"),
        .description = COMPOUND_STRING("Steals the foe's held item."),
        .longDescription = COMPOUND_STRING("If hit by a contact move\n"
                                           "while itemless, steals\n"
                                           "the attacker's held item."),
        .aiRating = 3,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = _("Sheer Force"),
        .description = COMPOUND_STRING("Trades effects for power."),
        .longDescription = COMPOUND_STRING("Moves with added effects\n"
                                           "hit 30% harder, but those\n"
                                           "added effects do not\n"
                                           "activate."),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = _("Contrary"),
        .description = COMPOUND_STRING("Inverts stat changes."),
        .longDescription = COMPOUND_STRING("Stat changes are\n"
                                           "reversed: boosts become\n"
                                           "drops and drops become\n"
                                           "boosts."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = _("Unnerve"),
        .description = COMPOUND_STRING("Foes can't eat Berries."),
        .longDescription = COMPOUND_STRING("Opposing Pokémon are too\n"
                                           "nervous to eat their\n"
                                           "held Berries."),
        .aiRating = 3,
    },

    [ABILITY_DEFIANT] =
    {
        .name = _("Defiant"),
        .description = COMPOUND_STRING("Lowered stats up Attack."),
        .longDescription = COMPOUND_STRING("Sharply raises Attack by\n"
                                           "2 stages whenever any of\n"
                                           "the Pokémon's stats are\n"
                                           "lowered by a foe."),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = _("Defeatist"),
        .description = COMPOUND_STRING("Gives up at half HP."),
        .longDescription = COMPOUND_STRING("Halves Attack and Sp.\n"
                                           "Atk when the Pokémon's\n"
                                           "HP drops to 1/2 or less."),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = _("Cursed Body"),
        .description = COMPOUND_STRING("Disables moves on contact."),
        .longDescription = COMPOUND_STRING("Moves that hit this\n"
                                           "Pokemon have a 30% chance\n"
                                           "to be Disabled."),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = _("Healer"),
        .description = COMPOUND_STRING("Heals partner Pokémon."),
        .longDescription = COMPOUND_STRING("Has a 30% chance each\n"
                                           "turn to cure an ally's\n"
                                           "status condition."),
        .aiRating = 0,
    },

    [ABILITY_FRIEND_GUARD] =
    {
        .name = _("Friend Guard"),
        .description = COMPOUND_STRING("Lowers damage to partner."),
        .longDescription = COMPOUND_STRING("Allied Pokemon take 25%\n"
                                           "less direct damage from\n"
                                           "moves."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = _("Weak Armor"),
        .description = COMPOUND_STRING("Its stats change when hit."),
        .longDescription = COMPOUND_STRING("Being hit by a physical\n"
                                           "move lowers Defense by 1\n"
                                           "stage and raises Speed by\n"
                                           "1 stage."),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = _("Heavy Metal"),
        .description = COMPOUND_STRING("Doubles weight."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "weight, affecting\n"
                                           "weight-based moves."),
        .aiRating = -1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = _("Light Metal"),
        .description = COMPOUND_STRING("Halves weight."),
        .longDescription = COMPOUND_STRING("Halves the Pokémon's\n"
                                           "weight, affecting\n"
                                           "weight-based moves."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = _("Multiscale"),
        .description = COMPOUND_STRING("Halves damage at full HP."),
        .longDescription = COMPOUND_STRING("Damage taken from moves is\n"
                                           "halved while this Pokemon\n"
                                           "is at full HP."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = _("Toxic Boost"),
        .description = COMPOUND_STRING("Ups Attack if poisoned."),
        .longDescription = COMPOUND_STRING("Boosts Attack by 50%\n"
                                           "while the Pokémon is\n"
                                           "poisoned."),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = _("Flare Boost"),
        .description = COMPOUND_STRING("Ups Sp. Atk if burned."),
        .longDescription = COMPOUND_STRING("Boosts Sp. Atk by 50%\n"
                                           "while the Pokémon is\n"
                                           "burned."),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = _("Harvest"),
        .description = COMPOUND_STRING("May recycle a used Berry."),
        .longDescription = COMPOUND_STRING("At each turn's end, may\n"
                                           "restore a consumed Berry;\n"
                                           "always succeeds in sun."),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = _("Telepathy"),
        .description = COMPOUND_STRING("Can't be damaged by an ally."),
        .longDescription = COMPOUND_STRING("Prevents damage from\n"
                                           "allied Pokemon's moves."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = _("Moody"),
        .description = COMPOUND_STRING("Stats change gradually."),
        .longDescription = COMPOUND_STRING("Each turn, raises one\n"
                                           "random stat by 2 stages\n"
                                           "and lowers another by\n"
                                           "1 stage."),
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .name = _("Overcoat"),
        .description = COMPOUND_STRING("Blocks weather and powder."),
        .longDescription = COMPOUND_STRING("Prevents weather damage\n"
                                           "and powder or spore move\n"
                                           "effects."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .name = _("Poison Touch"),
        .description = COMPOUND_STRING("Poisons foe on contact."),
        .longDescription = COMPOUND_STRING("Has a 30% chance to\n"
                                           "poison foes when the\n"
                                           "Pokémon hits them with\n"
                                           "a contact move."),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = _("Regenerator"),
        .description = COMPOUND_STRING("Heals upon switching out."),
        .longDescription = COMPOUND_STRING("Restores 1/3 max HP when\n"
                                           "this Pokemon switches out\n"
                                           "without fainting."),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = _("Big Pecks"),
        .description = COMPOUND_STRING("Prevents Defense loss."),
        .longDescription = COMPOUND_STRING("The Pokémon's Defense\n"
                                           "cannot be lowered by\n"
                                           "other Pokémon."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = _("Sand Rush"),
        .description = COMPOUND_STRING("Ups Speed in a sandstorm."),
        .longDescription = COMPOUND_STRING("Doubles Speed in a\n"
                                           "sandstorm and prevents\n"
                                           "sandstorm damage."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = _("Wonder Skin"),
        .description = COMPOUND_STRING("May avoid status problems."),
        .longDescription = COMPOUND_STRING("Status moves used against\n"
                                           "this Pokemon have their\n"
                                           "accuracy lowered to 50%."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = _("Analytic"),
        .description = COMPOUND_STRING("Moving last boosts power."),
        .longDescription = COMPOUND_STRING("Moves hit 30% harder when\n"
                                           "this Pokemon moves last."),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = _("Illusion"),
        .description = COMPOUND_STRING("Appears as a partner."),
        .longDescription = COMPOUND_STRING("On entry, takes the\n"
                                           "appearance of the last\n"
                                           "party Pokémon until it\n"
                                           "is hit by an attack."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = _("Imposter"),
        .description = COMPOUND_STRING("Transforms into the foe."),
        .longDescription = COMPOUND_STRING("Transforms into a random\n"
                                           "opposing Pokemon on entry."),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .name = _("Infiltrator"),
        .description = COMPOUND_STRING("Passes through barriers."),
        .longDescription = COMPOUND_STRING("The Pokémon's moves\n"
                                           "ignore the foe's\n"
                                           "screens, Safeguard,\n"
                                           "Mist, and Substitute."),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = _("Mummy"),
        .description = COMPOUND_STRING("Spreads with contact."),
        .longDescription = COMPOUND_STRING("Contact with the Pokémon\n"
                                           "changes the attacker's\n"
                                           "Ability to Mummy."),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = _("Moxie"),
        .description = COMPOUND_STRING("KOs raise Attack."),
        .longDescription = COMPOUND_STRING("Raises Attack by 1 stage\n"
                                           "each time the Pokémon\n"
                                           "knocks out a foe."),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = _("Justified"),
        .description = COMPOUND_STRING("Dark hits raise Attack."),
        .longDescription = COMPOUND_STRING("Raises Attack by 1 stage\n"
                                           "when hit by a\n"
                                           "Dark-type move."),
        .aiRating = 4,
    },

    [ABILITY_RATTLED] =
    {
        .name = _("Rattled"),
        .description = COMPOUND_STRING("Raises Speed when scared."),
        .longDescription = COMPOUND_STRING("Taking Bug-, Ghost-, or\n"
                                           "Dark-type damage raises\n"
                                           "Speed by 1 stage."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = _("Magic Bounce"),
        .description = COMPOUND_STRING("Reflects status moves."),
        .longDescription = COMPOUND_STRING("Reflects status moves\n"
                                           "back at the Pokémon\n"
                                           "that used them."),
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .name = _("Sap Sipper"),
        .description = COMPOUND_STRING("Grass increases Attack."),
        .longDescription = COMPOUND_STRING("Grass-type moves do not\n"
                                           "work on the Pokémon.\n"
                                           "Instead, they raise its\n"
                                           "Attack by 1 stage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = _("Prankster"),
        .description = COMPOUND_STRING("Status moves go first."),
        .longDescription = COMPOUND_STRING("Gives status moves +1\n"
                                           "priority. They miss\n"
                                           "against Dark-types."),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = _("Sand Force"),
        .description = COMPOUND_STRING("Powers up in a sandstorm."),
        .longDescription = COMPOUND_STRING("In sandstorm, Rock-,\n"
                                           "Ground-, and Steel-type\n"
                                           "moves hit 30% harder and\n"
                                           "sand damage is blocked."),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = _("Iron Barbs"),
        .description = COMPOUND_STRING("Hurts to touch."),
        .longDescription = COMPOUND_STRING("When hit by a contact\n"
                                           "move, the attacker takes\n"
                                           "damage equal to 1/8 of\n"
                                           "its max HP."),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = _("Zen Mode"),
        .description = COMPOUND_STRING("Transforms at half HP."),
        .longDescription = COMPOUND_STRING("Changes to Zen Mode when\n"
                                           "HP drops to 1/2 or less,\n"
                                           "and back when above."),
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = B_UPDATED_ABILITY_DATA >= GEN_7,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = B_UPDATED_ABILITY_DATA >= GEN_7,
        .cantBeOverwritten = B_UPDATED_ABILITY_DATA >= GEN_7,
        .failsOnImposter = TRUE,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .name = _("Victory Star"),
        .description = COMPOUND_STRING("Raises party accuracy."),
        .longDescription = COMPOUND_STRING("Raises the accuracy of\n"
                                           "the Pokémon and its\n"
                                           "allies by 10%."),
        .aiRating = 6,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = _("Turboblaze"),
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .longDescription = COMPOUND_STRING("Moves hit through\n"
                                           "abilities such as Levitate.\n"
                                           "                        \n"
                                           "               "),
        .aiRating = 7,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = _("Teravolt"),
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .longDescription = COMPOUND_STRING("Moves hit through\n"
                                           "abilities such as Levitate.\n"
                                           "                        \n"
                                           "               "),
        .aiRating = 7,
    },

    [ABILITY_AROMA_VEIL] =
    {
        .name = _("Aroma Veil"),
        .description = COMPOUND_STRING("Prevents limiting of moves."),
        .longDescription = COMPOUND_STRING("Protects allies from\n"
                                           "mental effects that limit\n"
                                           "move choice or action."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = _("Flower Veil"),
        .description = COMPOUND_STRING("Protects Grass-types."),
        .longDescription = COMPOUND_STRING("Allied Grass-types\n"
                                           "cannot have their stats\n"
                                           "lowered or be afflicted\n"
                                           "with status conditions."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = _("Cheek Pouch"),
        .description = COMPOUND_STRING("Eating Berries restores HP."),
        .longDescription = COMPOUND_STRING("Eating a Berry restores\n"
                                           "HP in addition to the\n"
                                           "Berry's normal effect."),
        .aiRating = 4,
    },

    [ABILITY_PROTEAN] =
    {
        .name = _("Protean"),
        .description = COMPOUND_STRING("Changes type to used move."),
        .longDescription = COMPOUND_STRING("Changes the Pokemon's\n"
                                           "type to match the move it\n"
                                           "uses before attacking."),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = _("Fur Coat"),
        .description = COMPOUND_STRING("Raises Defense."),
        .longDescription = COMPOUND_STRING("Halves the damage the\n"
                                           "Pokémon takes from\n"
                                           "physical moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .name = _("Magician"),
        .description = COMPOUND_STRING("Steals the foe's held item."),
        .longDescription = COMPOUND_STRING("When this Pokemon uses a\n"
                                           "damaging move, it steals\n"
                                           "the target's held item."),
        .aiRating = 3,
    },

    [ABILITY_BULLETPROOF] =
    {
        .name = _("Bulletproof"),
        .description = COMPOUND_STRING("Avoids some projectiles."),
        .longDescription = COMPOUND_STRING("Protects the Pokémon\n"
                                           "from ball and bomb\n"
                                           "moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = _("Competitive"),
        .description = COMPOUND_STRING("Lowered stats up Sp. Atk."),
        .longDescription = COMPOUND_STRING("When any stat is lowered,\n"
                                           "raises Sp. Atk by 2\n"
                                           "stages."),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = _("Strong Jaw"),
        .description = COMPOUND_STRING("Boosts biting moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "biting moves by 50%."),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = _("Refrigerate"),
        .description = COMPOUND_STRING("Normal moves become Ice."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Ice-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = _("Sweet Veil"),
        .description = COMPOUND_STRING("Prevents party from sleep."),
        .longDescription = COMPOUND_STRING("Prevents this Pokemon\n"
                                           "and its allies from being\n"
                                           "put to sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = _("Stance Change"),
        .description = COMPOUND_STRING("Transforms as it battles."),
        .longDescription = COMPOUND_STRING("Transforms as it.\n"
                                           "battles                 \n"
                                           "                        \n"
                                           "               "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .name = _("Gale Wings"),
        .description = COMPOUND_STRING("Flying moves go first."),
        .longDescription = COMPOUND_STRING("Gives Flying-type moves\n"
                                           "+1 priority while the\n"
                                           "Pokémon is at full HP."),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = _("Mega Launcher"),
        .description = COMPOUND_STRING("Boosts pulse moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "pulse and aura moves\n"
                                           "by 50%."),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = _("Grass Pelt"),
        .description = COMPOUND_STRING("Ups Defense in grass."),
        .longDescription = COMPOUND_STRING("Raises Defense by 50%\n"
                                           "while Grassy Terrain\n"
                                           "is active."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = _("Symbiosis"),
        .description = COMPOUND_STRING("Passes its item to an ally."),
        .longDescription = COMPOUND_STRING("Passes its held item to\n"
                                           "an ally immediately after\n"
                                           "the ally uses its item."),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = _("Tough Claws"),
        .description = COMPOUND_STRING("Boosts contact moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "contact moves by 30%."),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = _("Pixilate"),
        .description = COMPOUND_STRING("Normal moves become Fairy."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Fairy-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = _("Gooey"),
        .description = COMPOUND_STRING("Lowers Speed on contact."),
        .longDescription = COMPOUND_STRING("Lowers the attacker's\n"
                                           "Speed by 1 stage when\n"
                                           "hit by a contact move."),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = _("Aerilate"),
        .description = COMPOUND_STRING("Normal moves become Flying."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Flying-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = _("Parental Bond"),
        .description = COMPOUND_STRING("Moves hit twice."),
        .longDescription = COMPOUND_STRING("The Pokémon attacks\n"
                                           "twice; the second hit\n"
                                           "deals 1/4 of the\n"
                                           "normal damage."),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = _("Dark Aura"),
        .description = COMPOUND_STRING("Boosts Dark moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of all\n"
                                           "Dark-type moves in\n"
                                           "battle by 33%."),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = _("Fairy Aura"),
        .description = COMPOUND_STRING("Boosts Fairy moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of all\n"
                                           "Fairy-type moves in\n"
                                           "battle by 33%."),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = _("Aura Break"),
        .description = COMPOUND_STRING("Reverse aura abilities."),
        .longDescription = COMPOUND_STRING("Reverses the effects of\n"
                                           "Dark Aura and Fairy\n"
                                           "Aura, weakening those\n"
                                           "moves instead."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = _("Primordial Sea"),
        .description = COMPOUND_STRING("Summons heavy rain."),
        .longDescription = COMPOUND_STRING("Summons heavy rain that\n"
                                           "makes Fire-type moves\n"
                                           "fail, lasting while the\n"
                                           "Pokémon is in battle."),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = _("Desolate Land"),
        .description = COMPOUND_STRING("Summons intense sunlight."),
        .longDescription = COMPOUND_STRING("Turns sunlight extremely\n"
                                           "harsh on entry, blocking\n"
                                           "damaging Water moves\n"
                                           "until the Pokemon leaves."),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = _("Delta Stream"),
        .description = COMPOUND_STRING("Summons strong winds."),
        .longDescription = COMPOUND_STRING("Summons strong winds\n"
                                           "that remove Flying-type\n"
                                           "weaknesses while the\n"
                                           "Pokémon is in battle."),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = _("Stamina"),
        .description = COMPOUND_STRING("Boosts Defense when hit."),
        .longDescription = COMPOUND_STRING("Raises Defense by 1\n"
                                           "stage each time the\n"
                                           "Pokémon is hit by an\n"
                                           "attack."),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = _("Wimp Out"),
        .description = COMPOUND_STRING("Flees at half HP."),
        .longDescription = COMPOUND_STRING("The Pokémon switches out\n"
                                           "when its HP drops to\n"
                                           "1/2 or less."),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = _("Emergency Exit"),
        .description = COMPOUND_STRING("Flees at half HP."),
        .longDescription = COMPOUND_STRING("The Pokémon switches out\n"
                                           "when its HP drops to\n"
                                           "1/2 or less."),
        .aiRating = 3,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = _("Water Compaction"),
        .description = COMPOUND_STRING("Water boosts Defense."),
        .longDescription = COMPOUND_STRING("Raises Defense by 2\n"
                                           "stages when hit by a\n"
                                           "Water-type move."),
        .aiRating = 4,
    },

    [ABILITY_MERCILESS] =
    {
        .name = _("Merciless"),
        .description = COMPOUND_STRING("Criticals poisoned foes."),
        .longDescription = COMPOUND_STRING("The Pokémon's attacks\n"
                                           "always land critical\n"
                                           "hits on poisoned foes."),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = _("Shields Down"),
        .description = COMPOUND_STRING("Shell breaks at half HP."),
        .longDescription = COMPOUND_STRING("Above 1/2 HP its shell\n"
                                           "blocks status. At 1/2\n"
                                           "or less it breaks and\n"
                                           "switches to Attack mode."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .name = _("Stakeout"),
        .description = COMPOUND_STRING("Stronger as foes switch in."),
        .longDescription = COMPOUND_STRING("Moves deal double damage\n"
                                           "against targets that\n"
                                           "switched in this turn."),
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .name = _("Water Bubble"),
        .description = COMPOUND_STRING("Guards from fire and burns."),
        .longDescription = COMPOUND_STRING("Halves incoming Fire\n"
                                           "damage, doubles Water\n"
                                           "moves, and prevents burns."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_STEELWORKER] =
    {
        .name = _("Steelworker"),
        .description = COMPOUND_STRING("Powers up Steel moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Steel-type\n"
                                           "moves by 50%."),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = _("Berserk"),
        .description = COMPOUND_STRING("Boosts Sp. Atk at low HP."),
        .longDescription = COMPOUND_STRING("When damage drops HP\n"
                                           "below half, raises Sp.\n"
                                           "Atk by 1 stage."),
        .aiRating = 5,
    },

    [ABILITY_SLUSH_RUSH] =
    {
        .name = _("Slush Rush"),
        .description = COMPOUND_STRING("Raises Speed in Hail/Snow."),
        .longDescription = COMPOUND_STRING("Doubles Speed during\n"
                                           "hail or snow and prevents\n"
                                           "hail damage."),
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .name = _("Long Reach"),
        .description = COMPOUND_STRING("Never makes contact."),
        .longDescription = COMPOUND_STRING("The Pokémon's moves do\n"
                                           "not make contact with\n"
                                           "the target."),
        .aiRating = 3,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = _("Liquid Voice"),
        .description = COMPOUND_STRING("Makes sound moves Water."),
        .longDescription = COMPOUND_STRING("All of the Pokémon's\n"
                                           "sound-based moves become\n"
                                           "Water-type."),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = _("Triage"),
        .description = COMPOUND_STRING("Healing moves go first."),
        .longDescription = COMPOUND_STRING("Gives healing moves\n"
                                           "+3 priority in battle."),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = _("Galvanize"),
        .description = COMPOUND_STRING("Normal moves turn Electric."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Electric-type and deal\n"
                                           "20% more damage."),
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .name = _("Surge Surfer"),
        .description = COMPOUND_STRING("Faster on electricity."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Speed while Electric\n"
                                           "Terrain is active."),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = _("Schooling"),
        .description = COMPOUND_STRING("Forms a school when strong."),
        .longDescription = COMPOUND_STRING("At level 20+, Wishiwashi\n"
                                           "becomes School Form at\n"
                                           "1/4 HP or above, else\n"
                                           "Solo Form."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .name = _("Disguise"),
        .description = COMPOUND_STRING("Decoy protects it once."),
        .longDescription = COMPOUND_STRING("A cloak blocks the\n"
                                           "damage from one attack,\n"
                                           "then breaks, costing\n"
                                           "1/8 of max HP."),
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .name = _("Battle Bond"),
        .description = COMPOUND_STRING("Changes form after a KO."),
        .longDescription = COMPOUND_STRING("After knocking out a\n"
                                           "foe, Greninja transforms\n"
                                           "into its Ash form."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_CONSTRUCT] =
    {
        .name = _("Power Construct"),
        .description = COMPOUND_STRING("Cells aid it when weakened."),
        .longDescription = COMPOUND_STRING("When Zygarde falls below\n"
                                           "half HP, it changes into\n"
                                           "Complete Forme."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_CORROSION] =
    {
        .name = _("Corrosion"),
        .description = COMPOUND_STRING("Poisons any type."),
        .longDescription = COMPOUND_STRING("The Pokémon can poison\n"
                                           "even Steel-type and\n"
                                           "Poison-type targets."),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = _("Comatose"),
        .description = COMPOUND_STRING("Always drowsing."),
        .longDescription = COMPOUND_STRING("The Pokémon is always\n"
                                           "drowsing and acts as if\n"
                                           "asleep, but cannot gain\n"
                                           "another status."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .name = _("Queenly Majesty"),
        .description = COMPOUND_STRING("Protects from priority."),
        .longDescription = COMPOUND_STRING("Opposing Pokémon cannot\n"
                                           "hit it with increased\n"
                                           "priority moves."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_INNARDS_OUT] =
    {
        .name = _("Innards Out"),
        .description = COMPOUND_STRING("Hurts foe when defeated."),
        .longDescription = COMPOUND_STRING("When knocked out by an\n"
                                           "attack, deals damage to\n"
                                           "the attacker equal to\n"
                                           "the HP it had left."),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = _("Dancer"),
        .description = COMPOUND_STRING("Dances along with others."),
        .longDescription = COMPOUND_STRING("When another Pokemon uses\n"
                                           "a dance move, this\n"
                                           "Pokemon copies it right\n"
                                           "afterward."),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = _("Battery"),
        .description = COMPOUND_STRING("Boosts ally's Sp. Atk."),
        .longDescription = COMPOUND_STRING("Raises the power of\n"
                                           "allies' special moves\n"
                                           "by 30%."),
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .name = _("Fluffy"),
        .description = COMPOUND_STRING("Tougher but flammable."),
        .longDescription = COMPOUND_STRING("Halves contact-move\n"
                                           "damage but doubles\n"
                                           "damage from Fire-type\n"
                                           "moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = _("Dazzling"),
        .description = COMPOUND_STRING("Protects from priority."),
        .longDescription = COMPOUND_STRING("Opposing Pokémon cannot\n"
                                           "hit it with increased\n"
                                           "priority moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SOUL_HEART] =
    {
        .name = _("Soul-Heart"),
        .description = COMPOUND_STRING("KOs raise Sp. Atk."),
        .longDescription = COMPOUND_STRING("Raises Sp. Atk by 1\n"
                                           "stage each time any\n"
                                           "Pokémon is knocked out."),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = _("Tangling Hair"),
        .description = COMPOUND_STRING("Lowers Speed on contact."),
        .longDescription = COMPOUND_STRING("Lowers the attacker's\n"
                                           "Speed by 1 stage when\n"
                                           "hit by a contact move."),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = _("Receiver"),
        .description = COMPOUND_STRING("Copies ally's ability."),
        .longDescription = COMPOUND_STRING("Inherits the Ability of\n"
                                           "a defeated ally."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = _("Power Of Alchemy"),
        .description = COMPOUND_STRING("Copies ally's ability."),
        .longDescription = COMPOUND_STRING("Inherits the Ability of\n"
                                           "a defeated ally."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = _("Beast Boost"),
        .description = COMPOUND_STRING("KOs boost best stat."),
        .longDescription = COMPOUND_STRING("Raises its highest stat\n"
                                           "by 1 stage each time it\n"
                                           "knocks out a foe."),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = _("RKS System"),
        .description = COMPOUND_STRING("Memories change its type."),
        .longDescription = COMPOUND_STRING("Changes Silvally's type\n"
                                           "to match its held Memory\n"
                                           "and resists replacement."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .name = _("Electric Surge"),
        .description = COMPOUND_STRING("Field becomes Electric."),
        .longDescription = COMPOUND_STRING("Turns the ground into\n"
                                           "Electric Terrain for 5\n"
                                           "turns when entering\n"
                                           "battle."),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = _("Psychic Surge"),
        .description = COMPOUND_STRING("Field becomes weird."),
        .longDescription = COMPOUND_STRING("Turns the ground into\n"
                                           "Psychic Terrain for 5\n"
                                           "turns when entering\n"
                                           "battle."),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = _("Misty Surge"),
        .description = COMPOUND_STRING("Field becomes misty."),
        .longDescription = COMPOUND_STRING("Turns the ground into\n"
                                           "Misty Terrain for 5\n"
                                           "turns when entering\n"
                                           "battle."),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = _("Grassy Surge"),
        .description = COMPOUND_STRING("Field becomes grassy."),
        .longDescription = COMPOUND_STRING("Turns the ground into\n"
                                           "Grassy Terrain for 5\n"
                                           "turns when entering\n"
                                           "battle."),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = _("Full Metal Body"),
        .description = COMPOUND_STRING("Prevents stat reduction."),
        .longDescription = COMPOUND_STRING("The Pokémon's stats\n"
                                           "cannot be lowered by\n"
                                           "other Pokémon's moves\n"
                                           "or Abilities."),
        .aiRating = 4,
    },

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = _("Shadow Shield"),
        .description = COMPOUND_STRING("Halves damage at full HP."),
        .longDescription = COMPOUND_STRING("Damage from moves is\n"
                                           "halved while this Pokemon\n"
                                           "is at full HP; it cannot\n"
                                           "be bypassed."),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = _("Prism Armor"),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .longDescription = COMPOUND_STRING("Reduces super effective\n"
                                           "damage to 75%; it cannot\n"
                                           "be bypassed."),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = _("Neuroforce"),
        .description = COMPOUND_STRING("Ups “supereffective”."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "supereffective moves\n"
                                           "by 25%."),
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .name = _("Intrepid Sword"),
        .description = COMPOUND_STRING("Ups Attack on entry."),
        .longDescription = COMPOUND_STRING("Raises Attack by 1 stage\n"
                                           "when the Pokémon enters\n"
                                           "a battle."),
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .name = _("Dauntless Shield"),
        .description = COMPOUND_STRING("Ups Defense on entry."),
        .longDescription = COMPOUND_STRING("Raises Defense by 1\n"
                                           "stage when the Pokémon\n"
                                           "enters a battle."),
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .name = _("Libero"),
        .description = COMPOUND_STRING("Changes type to move's."),
        .longDescription = COMPOUND_STRING("Changes the Pokémon's\n"
                                           "type to match the move\n"
                                           "it is about to use."),
    },

    [ABILITY_BALL_FETCH] =
    {
        .name = _("Ball Fetch"),
        .description = COMPOUND_STRING("Fetches failed Poké Ball."),
        .longDescription = COMPOUND_STRING("If itemless, fetches the\n"
                                           "first failed Poke Ball at\n"
                                           "the end of a turn."),
        .aiRating = 0,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = _("Cotton Down"),
        .description = COMPOUND_STRING("Lower Speed of all when hit."),
        .longDescription = COMPOUND_STRING("When hit by an attack,\n"
                                           "lowers every other\n"
                                           "Pokemon's Speed by 1\n"
                                           "stage."),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = _("Propeller Tail"),
        .description = COMPOUND_STRING("Ignores foe's redirection."),
        .longDescription = COMPOUND_STRING("Ignores moves and\n"
                                           "Abilities that redirect\n"
                                           "the target of its moves."),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = _("Mirror Armor"),
        .description = COMPOUND_STRING("Reflect stat decreases."),
        .longDescription = COMPOUND_STRING("Bounces back only the\n"
                                           "stat-lowering effects\n"
                                           "the Pokémon receives."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = _("Gulp Missile"),
        .description = COMPOUND_STRING("If hit, spits prey from sea."),
        .longDescription = COMPOUND_STRING("After using Surf or Dive,\n"
                                           "Cramorant catches prey;\n"
                                           "when hit, spits it at the\n"
                                           "attacker."),
        .aiRating = 3,
        .cantBeSwapped = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeCopied = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeTraced = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .name = _("Stalwart"),
        .description = COMPOUND_STRING("Ignores foe's redirection."),
        .longDescription = COMPOUND_STRING("Ignores moves and\n"
                                           "Abilities that redirect\n"
                                           "the target of its moves."),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = _("Steam Engine"),
        .description = COMPOUND_STRING("Fire or Water hits up Speed."),
        .longDescription = COMPOUND_STRING("Raises Speed by 3 stages\n"
                                           "when hit by a Fire- or\n"
                                           "Water-type move."),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("Punk Rock"),
        .description = COMPOUND_STRING("Ups and resists sound."),
        .longDescription = COMPOUND_STRING("Boosts sound moves by\n"
                                           "30% and halves the\n"
                                           "damage taken from\n"
                                           "sound-based moves."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = _("Sand Spit"),
        .description = COMPOUND_STRING("Creates a sandstorm if hit."),
        .longDescription = COMPOUND_STRING("Creates a sandstorm when\n"
                                           "this Pokemon is hit by an\n"
                                           "attack."),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = _("Ice Scales"),
        .description = COMPOUND_STRING("Halves special damage."),
        .longDescription = COMPOUND_STRING("Halves the damage the\n"
                                           "Pokémon takes from\n"
                                           "special moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = _("Ripen"),
        .description = COMPOUND_STRING("Doubles effect of Berries."),
        .longDescription = COMPOUND_STRING("Doubles the effects of\n"
                                           "Berries used by this\n"
                                           "Pokemon."),
        .aiRating = 4,
    },

    [ABILITY_ICE_FACE] =
    {
        .name = _("Ice Face"),
        .description = COMPOUND_STRING("Hail or Snow renew free hit."),
        .longDescription = COMPOUND_STRING("In Ice Face form, blocks\n"
                                           "one physical hit. Hail or\n"
                                           "snow restores Ice Face."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .name = _("Power Spot"),
        .description = COMPOUND_STRING("Powers up ally moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "allies' moves by 30%."),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = _("Mimicry"),
        .description = COMPOUND_STRING("Changes type on terrain."),
        .longDescription = COMPOUND_STRING("The Pokémon's type\n"
                                           "changes to match the\n"
                                           "current terrain."),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = _("Screen Cleaner"),
        .description = COMPOUND_STRING("Removes walls of light."),
        .longDescription = COMPOUND_STRING("On entry, removes Light\n"
                                           "Screen, Reflect, and\n"
                                           "Aurora Veil on both\n"
                                           "sides of the field."),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = _("Steely Spirit"),
        .description = COMPOUND_STRING("Boosts ally's Steel moves."),
        .longDescription = COMPOUND_STRING("Powers up Steel-type\n"
                                           "moves used by this\n"
                                           "Pokemon and its allies."),
        .aiRating = 2,
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = _("Perish Body"),
        .description = COMPOUND_STRING("Foe faints in 3 turns if hit."),
        .longDescription = COMPOUND_STRING("Contact with this Pokemon\n"
                                           "starts a 3-turn Perish\n"
                                           "Count on both battlers."),
        .aiRating = -1,
    },

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = _("Wandering Spirit"),
        .description = COMPOUND_STRING("Trade abilities on contact."),
        .longDescription = COMPOUND_STRING("When hit by contact, this\n"
                                           "Pokemon swaps Abilities\n"
                                           "with the attacker."),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = _("Gorilla Tactics"),
        .description = COMPOUND_STRING("Ups Attack and locks move."),
        .longDescription = COMPOUND_STRING("Raises Attack, but locks\n"
                                           "this Pokemon into the\n"
                                           "first move it selects."),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = _("Neutralizing Gas"),
        .description = COMPOUND_STRING("All Abilities are nullified."),
        .longDescription = COMPOUND_STRING("While this Pokemon is in\n"
                                           "battle, other Abilities\n"
                                           "are nullified or cannot\n"
                                           "trigger."),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = _("Pastel Veil"),
        .description = COMPOUND_STRING("Protects team from poison."),
        .longDescription = COMPOUND_STRING("Prevents this Pokemon\n"
                                           "and allies from poisoning\n"
                                           "and cures allies on entry."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = _("Hunger Switch"),
        .description = COMPOUND_STRING("Changes form each turn."),
        .longDescription = COMPOUND_STRING("Switches between Full\n"
                                           "and Hangry forms at the\n"
                                           "end of each turn."),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .name = _("Quick Draw"),
        .description = COMPOUND_STRING("Moves first occasionally."),
        .longDescription = COMPOUND_STRING("Damaging moves have a\n"
                                           "30% chance to move first\n"
                                           "within their priority\n"
                                           "bracket."),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = _("Unseen Fist"),
        .description = COMPOUND_STRING("Contact evades protection."),
        .longDescription = COMPOUND_STRING("Contact moves hit through\n"
                                           "protection effects such\n"
                                           "as Protect and Detect."),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = _("Curious Medicine"),
        .description = COMPOUND_STRING("Remove ally's stat changes."),
        .longDescription = COMPOUND_STRING("On entry, removes all\n"
                                           "stat changes from allied\n"
                                           "Pokemon."),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("Transistor"),
        .description = COMPOUND_STRING("Ups Electric-type moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Electric-type\n"
                                           "moves by 30%."),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = _("Dragon's Maw"),
        .description = COMPOUND_STRING("Ups Dragon-type moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Dragon-type\n"
                                           "moves by 50%."),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = _("Chilling Neigh"),
        .description = COMPOUND_STRING("KOs boost Attack stat."),
        .longDescription = COMPOUND_STRING("Raises Attack by 1 stage\n"
                                           "each time the Pokémon\n"
                                           "knocks out a foe."),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = _("Grim Neigh"),
        .description = COMPOUND_STRING("KOs boost Sp. Atk stat."),
        .longDescription = COMPOUND_STRING("Raises Sp. Atk by 1\n"
                                           "stage each time the\n"
                                           "Pokémon knocks out a foe."),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = _("As One"),
        .description = COMPOUND_STRING("Unnerve and Chilling Neigh."),
        .longDescription = COMPOUND_STRING("Combines the effects of\n"
                                           "Unnerve and Chilling\n"
                                           "Neigh."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .name = _("As One"),
        .description = COMPOUND_STRING("Unnerve and Grim Neigh."),
        .longDescription = COMPOUND_STRING("Combines the effects of\n"
                                           "Unnerve and Grim Neigh:\n"
                                           "foes can't eat Berries\n"
                                           "and KOs raise Sp. Atk."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_LINGERING_AROMA] =
    {
        .name = _("Lingering Aroma"),
        .description = COMPOUND_STRING("Spreads with contact."),
        .longDescription = COMPOUND_STRING("Contact with the Pokémon\n"
                                           "changes the attacker's\n"
                                           "Ability to Lingering\n"
                                           "Aroma."),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = _("Seed Sower"),
        .description = COMPOUND_STRING("Affects terrain when hit."),
        .longDescription = COMPOUND_STRING("When hit by an attack,\n"
                                           "the Pokémon turns the\n"
                                           "field into Grassy\n"
                                           "Terrain."),
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = _("Thermal Exchange"),
        .description = COMPOUND_STRING("Fire hits up Attack."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot be\n"
                                           "burned. Fire-type moves\n"
                                           "that hit it raise its\n"
                                           "Attack by 1 stage."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = _("Anger Shell"),
        .description = COMPOUND_STRING("Gets angry at half HP."),
        .longDescription = COMPOUND_STRING("When damage drops HP to\n"
                                           "half or less, Attack,\n"
                                           "Sp. Atk, and Speed rise\n"
                                           "by 1 stage while Defense\n"
                                           "and Sp. Def fall by 1\n"
                                           "stage."),
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = _("Purifying Salt"),
        .description = COMPOUND_STRING("Protected by pure salts."),
        .longDescription = COMPOUND_STRING("Halves damage from\n"
                                           "Ghost-type moves. The\n"
                                           "Pokémon is immune to\n"
                                           "status conditions."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = _("Well-Baked Body"),
        .description = COMPOUND_STRING("Strengthened by Fire."),
        .longDescription = COMPOUND_STRING("Fire-type moves do not\n"
                                           "work. Instead, they\n"
                                           "sharply raise the\n"
                                           "Pokémon's Defense stat."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = _("Wind Rider"),
        .description = COMPOUND_STRING("Ups Attack if hit by wind."),
        .longDescription = COMPOUND_STRING("Immune to wind moves.\n"
                                           "Instead, they raise\n"
                                           "Attack. Tailwind also\n"
                                           "raises the Pokémon's\n"
                                           "Attack."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = _("Guard Dog"),
        .description = COMPOUND_STRING("Cannot be intimidated."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot be\n"
                                           "intimidated or forced\n"
                                           "out. Intimidate raises\n"
                                           "its Attack instead."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = _("Rocky Payload"),
        .description = COMPOUND_STRING("Powers up Rock moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Rock-type\n"
                                           "moves by 50%."),
        .aiRating = 6,
    },

    [ABILITY_WIND_POWER] =
    {
        .name = _("Wind Power"),
        .description = COMPOUND_STRING("Gets charged by wind."),
        .longDescription = COMPOUND_STRING("Wind moves give the\n"
                                           "Pokémon the Charged\n"
                                           "status, doubling its\n"
                                           "next Electric move."),
        .aiRating = 4,
    },

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = _("Zero to Hero"),
        .description = COMPOUND_STRING("Changes form on switch out."),
        .longDescription = COMPOUND_STRING("The Pokémon transforms\n"
                                           "into its Hero Form when\n"
                                           "it switches out."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .name = _("Commander"),
        .description = COMPOUND_STRING("Commands from Dondozo."),
        .longDescription = COMPOUND_STRING("On entry, if ally\n"
                                           "Dondozo is present, the\n"
                                           "Pokémon enters its mouth\n"
                                           "and commands from there."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = _("Electromorphosis"),
        .description = COMPOUND_STRING("Gets Charged when hit."),
        .longDescription = COMPOUND_STRING("Taking damage gives the\n"
                                           "Pokémon the Charged\n"
                                           "status, doubling its\n"
                                           "next Electric move."),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = _("Protosynthesis"),
        .description = COMPOUND_STRING("Sun boosts best stat."),
        .longDescription = COMPOUND_STRING("Harsh sunlight or\n"
                                           "Booster Energy boosts\n"
                                           "the Pokémon's highest\n"
                                           "stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = _("Quark Drive"),
        .description = COMPOUND_STRING("Elec. field ups best stat."),
        .longDescription = COMPOUND_STRING("Electric Terrain or\n"
                                           "Booster Energy boosts\n"
                                           "the Pokémon's highest\n"
                                           "stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = _("Good as Gold"),
        .description = COMPOUND_STRING("Avoids status moves."),
        .longDescription = COMPOUND_STRING("A body of pure gold\n"
                                           "gives the Pokémon full\n"
                                           "immunity to status\n"
                                           "moves."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = _("Vessel of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' sp. damage."),
        .longDescription = COMPOUND_STRING("The power of the vessel\n"
                                           "lowers the Sp. Atk of\n"
                                           "all Pokémon except\n"
                                           "itself."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = _("Sword of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' Defense."),
        .longDescription = COMPOUND_STRING("The power of the sword\n"
                                           "lowers the Defense of\n"
                                           "all Pokémon except\n"
                                           "itself."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = _("Tablets of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' damage."),
        .longDescription = COMPOUND_STRING("The power of the tablets\n"
                                           "lowers the Attack of all\n"
                                           "Pokémon except itself."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = _("Beads of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' Sp. Defense."),
        .longDescription = COMPOUND_STRING("The power of the beads\n"
                                           "lowers the Sp. Def of\n"
                                           "all Pokémon except\n"
                                           "itself."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = _("Orichalcum Pulse"),
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .longDescription = COMPOUND_STRING("Turns sunlight harsh on\n"
                                           "entry. In harsh\n"
                                           "sunlight, the Pokémon's\n"
                                           "Attack is boosted."),
        .aiRating = 8,
        .cantBeSwapped = TRUE,
        .cantBeCopied = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = _("Hadron Engine"),
        .description = COMPOUND_STRING("Field becomes Electric."),
        .longDescription = COMPOUND_STRING("Turns the ground\n"
                                           "electric on entry. On\n"
                                           "Electric Terrain, Sp.\n"
                                           "Atk is boosted."),
        .aiRating = 8,
        .cantBeSwapped = TRUE,
        .cantBeCopied = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = _("Opportunist"),
        .description = COMPOUND_STRING("Copies foe's stat change."),
        .longDescription = COMPOUND_STRING("When an opponent's stats\n"
                                           "are boosted, the Pokémon\n"
                                           "copies those stat\n"
                                           "boosts."),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = _("Cud Chew"),
        .description = COMPOUND_STRING("Eats a used berry again."),
        .longDescription = COMPOUND_STRING("After eating a Berry,\n"
                                           "the Pokémon eats that\n"
                                           "same Berry again at the\n"
                                           "next turn's end."),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = _("Sharpness"),
        .description = COMPOUND_STRING("Strengthens slicing moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's slicing moves\n"
                                           "by 50%."),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = _("Supreme Overlord"),
        .description = COMPOUND_STRING("Inherits fallen's strength."),
        .longDescription = COMPOUND_STRING("On entry, moves gain 10%\n"
                                           "power for each defeated\n"
                                           "party member, up to 50%."),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = _("Costar"),
        .description = COMPOUND_STRING("Copies ally's stat changes."),
        .longDescription = COMPOUND_STRING("When the Pokémon enters\n"
                                           "battle, it copies an\n"
                                           "ally's stat changes."),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = _("Toxic Debris"),
        .description = COMPOUND_STRING("Throws poison spikes if hit."),
        .longDescription = COMPOUND_STRING("When hit by a physical\n"
                                           "move, it scatters Toxic\n"
                                           "Spikes on the opponent's\n"
                                           "field."),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = _("Armor Tail"),
        .description = COMPOUND_STRING("Protects from priority."),
        .longDescription = COMPOUND_STRING("Opponents cannot use\n"
                                           "priority moves against\n"
                                           "the Pokémon or its\n"
                                           "allies."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = _("Earth Eater"),
        .description = COMPOUND_STRING("Eats ground to heal HP."),
        .longDescription = COMPOUND_STRING("Ground-type moves do not\n"
                                           "work. Instead, they\n"
                                           "restore 1/4 of max HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = _("Mycelium Might"),
        .description = COMPOUND_STRING("Status moves never fail."),
        .longDescription = COMPOUND_STRING("Status moves act last\n"
                                           "but ignore the target's\n"
                                           "Ability protections."),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = _("Hospitality"),
        .description = COMPOUND_STRING("Restores ally's HP."),
        .longDescription = COMPOUND_STRING("When the Pokémon enters\n"
                                           "a battle, it restores 1/4\n"
                                           "of its ally's max HP."),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = _("Mind's Eye"),
        .description = COMPOUND_STRING("Keen Eye and Scrappy."),
        .longDescription = COMPOUND_STRING("Ignores foes' evasion,\n"
                                           "prevents accuracy loss,\n"
                                           "and lets Normal or\n"
                                           "Fighting hit Ghost."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Speed."),
        .longDescription = COMPOUND_STRING("When Terastallized, the\n"
                                           "Teal Mask shines and\n"
                                           "raises Speed by 1 stage."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Attack."),
        .longDescription = COMPOUND_STRING("When Terastallized, the\n"
                                           "Hearthflame Mask shines\n"
                                           "and raises Attack by 1\n"
                                           "stage."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Sp. Def."),
        .longDescription = COMPOUND_STRING("When Terastallized, the\n"
                                           "Wellspring Mask shines\n"
                                           "and raises Sp. Def by 1\n"
                                           "stage."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Defense."),
        .longDescription = COMPOUND_STRING("When Terastallized, the\n"
                                           "Cornerstone Mask shines\n"
                                           "and raises Defense by 1\n"
                                           "stage."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = _("Toxic Chain"),
        .description = COMPOUND_STRING("Moves can poison."),
        .longDescription = COMPOUND_STRING("The Pokémon's toxic\n"
                                           "chain may badly poison\n"
                                           "any target it hits with\n"
                                           "a move."),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = _("Supersweet Syrup"),
        .description = COMPOUND_STRING("Lowers the foe's Evasion."),
        .longDescription = COMPOUND_STRING("On first entry each\n"
                                           "battle, lowers opposing\n"
                                           "Pokémon's evasiveness by\n"
                                           "1 stage."),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = _("Tera Shift"),
        .description = COMPOUND_STRING("Terastallizes upon entry."),
        .longDescription = COMPOUND_STRING("When the Pokémon enters\n"
                                           "battle, it absorbs\n"
                                           "nearby energy and\n"
                                           "becomes Terastal Form."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .name = _("Tera Shell"),
        .description = COMPOUND_STRING("Resists all at full HP."),
        .longDescription = COMPOUND_STRING("At full HP, all\n"
                                           "damage-dealing moves\n"
                                           "that hit the Pokémon are\n"
                                           "not very effective."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = _("Teraform Zero"),
        .description = COMPOUND_STRING("Zeroes weather and terrain."),
        .longDescription = COMPOUND_STRING("When Stellar Form\n"
                                           "appears, the Pokémon\n"
                                           "eliminates all weather\n"
                                           "and terrain effects."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = _("Poison Puppeteer"),
        .description = COMPOUND_STRING("Confuses poisoned foes."),
        .longDescription = COMPOUND_STRING("Pokémon poisoned by the\n"
                                           "user's moves also become\n"
                                           "confused."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INVERSION] =
    {
        .name = _("Inversion"),
        .description = COMPOUND_STRING("Weaknesses and resists swap."),
        .longDescription = COMPOUND_STRING("When attacked, this\n"
                                           "Pokemon's weaknesses\n"
                                           "and resistances are\n"
                                           "reversed."),
        .aiRating = 7,
    },

    [ABILITY_FIGHTING_ATE] =
    {
        .name = _("Fightilate"),
        .description = COMPOUND_STRING("Normal moves turn Fighting."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Fighting-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_POISON_ATE] =
    {
        .name = _("Venomate"),
        .description = COMPOUND_STRING("Normal moves turn Poison."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Poison-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_GROUND_ATE] =
    {
        .name = _("Terrate"),
        .description = COMPOUND_STRING("Normal moves turn Ground."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Ground-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_ROCK_ATE] =
    {
        .name = _("Rockate"),
        .description = COMPOUND_STRING("Normal moves turn Rock."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Rock-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_BUG_ATE] =
    {
        .name = _("Swarmate"),
        .description = COMPOUND_STRING("Normal moves turn Bug."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Bug-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_GHOST_ATE] =
    {
        .name = _("Spectrate"),
        .description = COMPOUND_STRING("Normal moves turn Ghost."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Ghost-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_STEEL_ATE] =
    {
        .name = _("Steelate"),
        .description = COMPOUND_STRING("Normal moves turn Steel."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Steel-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_FIRE_ATE] =
    {
        .name = _("Flamilate"),
        .description = COMPOUND_STRING("Normal moves turn Fire."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Fire-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_WATER_ATE] =
    {
        .name = _("Aquate"),
        .description = COMPOUND_STRING("Normal moves turn Water."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Water-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_GRASS_ATE] =
    {
        .name = _("Florate"),
        .description = COMPOUND_STRING("Normal moves turn Grass."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Grass-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_ATE] =
    {
        .name = _("Psychate"),
        .description = COMPOUND_STRING("Normal moves turn Psychic."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Psychic-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_DRAGON_ATE] =
    {
        .name = _("Draconate"),
        .description = COMPOUND_STRING("Normal moves turn Dragon."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Dragon-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_DARK_ATE] =
    {
        .name = _("Dreadate"),
        .description = COMPOUND_STRING("Normal moves turn Dark."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Dark-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_STEEL_FEET] =
    {
        .name = _("Steel Feet"),
        .description = COMPOUND_STRING("Boosts kicking moves."),
        .longDescription = COMPOUND_STRING("Kicking moves used by this\n"
                                           "Pokemon deal 20% more\n"
                                           "damage."),
        .aiRating = 6,
    },

    [ABILITY_DUAL_STRIKE] =
    {
        .name = _("Dual Strike"),
        .description = COMPOUND_STRING("Moves hit twice."),
        .longDescription = COMPOUND_STRING("Single-target attacks hit\n"
                                           "twice, with the second\n"
                                           "hit reduced in power."),
        .aiRating = 10,
    },

    [ABILITY_UNSTOPPABLE] =
    {
        .name = _("Unstoppable"),
        .description = COMPOUND_STRING("Prevents fatigue confuse."),
        .longDescription = COMPOUND_STRING("Prevents fatigue confusion\n"
                                           "and frees the Pokemon\n"
                                           "from Sky Drop."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_UNCANNY] =
    {
        .name = _("Uncanny"),
        .description = COMPOUND_STRING("Lowers foes' Sp. Atk."),
        .longDescription = COMPOUND_STRING("On entry, lowers opposing\n"
                                           "Pokemon's Sp. Atk by\n"
                                           "1 stage."),
        .aiRating = 5,
    },

    [ABILITY_MYSTIC_FORCE] =
    {
        .name = _("Mystic Force"),
        .description = COMPOUND_STRING("Psychic Terrain ups Speed."),
        .longDescription = COMPOUND_STRING("Doubles Speed while\n"
                                           "Psychic Terrain is active."),
        .aiRating = 5,
    },

    [ABILITY_MANEUVERABILITY] =
    {
        .name = _("Maneuverability"),
        .description = COMPOUND_STRING("Prioritizes weaker attacks."),
        .longDescription = COMPOUND_STRING("Damaging moves under 60\n"
                                           "power gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_ADRENALINE] =
    {
        .name = _("Adrenaline"),
        .description = COMPOUND_STRING("Boosts Speed in a pinch."),
        .longDescription = COMPOUND_STRING("At 1/3 HP or less, Speed\n"
                                           "is raised by 30%."),
        .aiRating = 5,
    },

    [ABILITY_PACK_LEADER] =
    {
        .name = _("Pack Leader"),
        .description = COMPOUND_STRING("Boosts attacks with allies."),
        .longDescription = COMPOUND_STRING("Moves deal 5% more damage\n"
                                           "for each living ally."),
        .aiRating = 6,
    },

    [ABILITY_REACTIVE] =
    {
        .name = _("Reactive"),
        .description = COMPOUND_STRING("Reacts to super hits."),
        .longDescription = COMPOUND_STRING("Moves gain +1 priority if\n"
                                           "the foe chooses a super\n"
                                           "effective attack."),
        .aiRating = 5,
    },

    [ABILITY_TRUE_GRIT] =
    {
        .name = _("True Grit"),
        .description = COMPOUND_STRING("Powers up Normal moves."),
        .longDescription = COMPOUND_STRING("Normal-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_WARRIOR_SPIRIT] =
    {
        .name = _("Warrior Spirit"),
        .description = COMPOUND_STRING("Powers up Fighting moves."),
        .longDescription = COMPOUND_STRING("Fighting-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_WIND_FORCE] =
    {
        .name = _("Wind Force"),
        .description = COMPOUND_STRING("Powers up Flying moves."),
        .longDescription = COMPOUND_STRING("Flying-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_TOXIC_CORE] =
    {
        .name = _("Toxic Core"),
        .description = COMPOUND_STRING("Powers up Poison moves."),
        .longDescription = COMPOUND_STRING("Poison-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_EARTHBOUND] =
    {
        .name = _("Earthbound"),
        .description = COMPOUND_STRING("Powers up Ground moves."),
        .longDescription = COMPOUND_STRING("Ground-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_HIVE_FORCE] =
    {
        .name = _("Hive Force"),
        .description = COMPOUND_STRING("Powers up Bug moves."),
        .longDescription = COMPOUND_STRING("Bug-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_SPECTRAL_FORCE] =
    {
        .name = _("Spectral Force"),
        .description = COMPOUND_STRING("Powers up Ghost moves."),
        .longDescription = COMPOUND_STRING("Ghost-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_FIERY_HEART] =
    {
        .name = _("Fire Mane"),
        .description = COMPOUND_STRING("Powers up Fire moves."),
        .longDescription = COMPOUND_STRING("Fire-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_SEABOUND] =
    {
        .name = _("Seabound"),
        .description = COMPOUND_STRING("Powers up Water moves."),
        .longDescription = COMPOUND_STRING("Water-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_VERDANT_SOUL] =
    {
        .name = _("Verdant Soul"),
        .description = COMPOUND_STRING("Powers up Grass moves."),
        .longDescription = COMPOUND_STRING("Grass-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_MIND_FORCE] =
    {
        .name = _("Mind Force"),
        .description = COMPOUND_STRING("Powers up Psychic moves."),
        .longDescription = COMPOUND_STRING("Psychic-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_FROST_FORCE] =
    {
        .name = _("Frost Force"),
        .description = COMPOUND_STRING("Powers up Ice moves."),
        .longDescription = COMPOUND_STRING("Ice-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_NIGHTFALL] =
    {
        .name = _("Nightfall"),
        .description = COMPOUND_STRING("Powers up Dark moves."),
        .longDescription = COMPOUND_STRING("Dark-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_FAE_HEART] =
    {
        .name = _("Fae Heart"),
        .description = COMPOUND_STRING("Powers up Fairy moves."),
        .longDescription = COMPOUND_STRING("Fairy-type moves used by\n"
                                           "this Pokemon deal 50%\n"
                                           "more damage."),
        .aiRating = 6,
    },

    [ABILITY_PLANTATION] =
    {
        .name = _("Plantation"),
        .description = COMPOUND_STRING("Attacks may seed foes."),
        .longDescription = COMPOUND_STRING("Damaging moves have a\n"
                                           "30% chance to seed the\n"
                                           "target if it is not Grass."),
        .aiRating = 5,
    },

    [ABILITY_ECHOING] =
    {
        .name = _("Echoing"),
        .description = COMPOUND_STRING("Sound moves may flinch."),
        .longDescription = COMPOUND_STRING("Sound moves have a 30%\n"
                                           "chance to make the target\n"
                                           "flinch."),
        .aiRating = 5,
    },

    [ABILITY_TIRELESS] =
    {
        .name = _("Tireless"),
        .description = COMPOUND_STRING("Skips recharge turns."),
        .longDescription = COMPOUND_STRING("Moves that normally need\n"
                                           "to recharge skip their\n"
                                           "recharge turn."),
        .aiRating = 6,
    },

    [ABILITY_AURA_SHIELD] =
    {
        .name = _("Aura Shield"),
        .description = COMPOUND_STRING("Blocks one attack."),
        .longDescription = COMPOUND_STRING("Blocks the first attack\n"
                                           "that would hit this\n"
                                           "Pokemon."),
        .aiRating = 7,
    },

    [ABILITY_PLAIN_SOUL] =
    {
        .name = _("Plain Soul"),
        .description = COMPOUND_STRING("Adds Normal typing."),
        .longDescription = COMPOUND_STRING("Adds Normal as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 4,
    },

    [ABILITY_FIGHTER_SOUL] =
    {
        .name = _("Fighter Soul"),
        .description = COMPOUND_STRING("Adds Fighting typing."),
        .longDescription = COMPOUND_STRING("Adds Fighting as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_WIND_SOUL] =
    {
        .name = _("Wind Soul"),
        .description = COMPOUND_STRING("Adds Flying typing."),
        .longDescription = COMPOUND_STRING("Adds Flying as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_VENOM_SOUL] =
    {
        .name = _("Venom Soul"),
        .description = COMPOUND_STRING("Adds Poison typing."),
        .longDescription = COMPOUND_STRING("Adds Poison as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_EARTH_SOUL] =
    {
        .name = _("Earth Soul"),
        .description = COMPOUND_STRING("Adds Ground typing."),
        .longDescription = COMPOUND_STRING("Adds Ground as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_STONE_SOUL] =
    {
        .name = _("Stone Soul"),
        .description = COMPOUND_STRING("Adds Rock typing."),
        .longDescription = COMPOUND_STRING("Adds Rock as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_HIVE_SOUL] =
    {
        .name = _("Hive Soul"),
        .description = COMPOUND_STRING("Adds Bug typing."),
        .longDescription = COMPOUND_STRING("Adds Bug as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_PHANTOM_SOUL] =
    {
        .name = _("Phantom Soul"),
        .description = COMPOUND_STRING("Adds Ghost typing."),
        .longDescription = COMPOUND_STRING("Adds Ghost as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_STEEL_SOUL] =
    {
        .name = _("Steel Soul"),
        .description = COMPOUND_STRING("Adds Steel typing."),
        .longDescription = COMPOUND_STRING("Adds Steel as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_FLAME_SOUL] =
    {
        .name = _("Flame Soul"),
        .description = COMPOUND_STRING("Adds Fire typing."),
        .longDescription = COMPOUND_STRING("Adds Fire as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_SEA_SOUL] =
    {
        .name = _("Sea Soul"),
        .description = COMPOUND_STRING("Adds Water typing."),
        .longDescription = COMPOUND_STRING("Adds Water as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_VERDANT_SOUL_TYPE] =
    {
        .name = _("Lifetree Soul"),
        .description = COMPOUND_STRING("Adds Grass typing."),
        .longDescription = COMPOUND_STRING("Adds Grass as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_THUNDER_SOUL] =
    {
        .name = _("Thunder Soul"),
        .description = COMPOUND_STRING("Adds Electric typing."),
        .longDescription = COMPOUND_STRING("Adds Electric as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_MIND_SOUL] =
    {
        .name = _("Mind Soul"),
        .description = COMPOUND_STRING("Adds Psychic typing."),
        .longDescription = COMPOUND_STRING("Adds Psychic as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_FROST_SOUL] =
    {
        .name = _("Frost Soul"),
        .description = COMPOUND_STRING("Adds Ice typing."),
        .longDescription = COMPOUND_STRING("Adds Ice as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_DRAGON_SOUL] =
    {
        .name = _("Dragon Soul"),
        .description = COMPOUND_STRING("Adds Dragon typing."),
        .longDescription = COMPOUND_STRING("Adds Dragon as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_NIGHT_SOUL] =
    {
        .name = _("Night Soul"),
        .description = COMPOUND_STRING("Adds Dark typing."),
        .longDescription = COMPOUND_STRING("Adds Dark as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_FAE_SOUL] =
    {
        .name = _("Fae Soul"),
        .description = COMPOUND_STRING("Adds Fairy typing."),
        .longDescription = COMPOUND_STRING("Adds Fairy as an extra\n"
                                           "type while this Pokemon\n"
                                           "is in battle."),
        .aiRating = 5,
    },

    [ABILITY_SHOWTIME] =
    {
        .name = _("Showtime"),
        .description = COMPOUND_STRING("Sets Trick Room on entry."),
        .longDescription = COMPOUND_STRING("Sets Trick Room for 5\n"
                                           "turns when this Pokemon\n"
                                           "enters battle."),
        .aiRating = 7,
    },

    [ABILITY_ROOTED] =
    {
        .name = _("Rooted"),
        .description = COMPOUND_STRING("Gain Ingrain on entry."),
        .longDescription = COMPOUND_STRING("Gains Ingrain when this\n"
                                           "Pokemon enters battle."),
        .aiRating = 5,
    },

    [ABILITY_RESTORING] =
    {
        .name = _("Restoring"),
        .description = COMPOUND_STRING("Gain Aqua Ring on entry."),
        .longDescription = COMPOUND_STRING("Gains Aqua Ring when this\n"
                                           "Pokemon enters battle."),
        .aiRating = 5,
    },

    [ABILITY_READY_STANCE] =
    {
        .name = _("Ready Stance"),
        .description = COMPOUND_STRING("Normal moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Normal-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_FIRST_STRIKE] =
    {
        .name = _("First Strike"),
        .description = COMPOUND_STRING("Fighting moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Fighting-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_REFLEX] =
    {
        .name = _("Toxic Reflex"),
        .description = COMPOUND_STRING("Poison moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Poison-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_EARTHEN_RUSH] =
    {
        .name = _("Earthen Rush"),
        .description = COMPOUND_STRING("Ground moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Ground-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_STONE_SENTINEL] =
    {
        .name = _("Stone Sentinel"),
        .description = COMPOUND_STRING("Rock moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Rock-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_SWARM_INSTINCT] =
    {
        .name = _("Swarm Instinct"),
        .description = COMPOUND_STRING("Bug moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Bug-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_PHANTOM_STEP] =
    {
        .name = _("Phantom Step"),
        .description = COMPOUND_STRING("Ghost moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Ghost-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_QUICK_FORGE] =
    {
        .name = _("Quick Forge"),
        .description = COMPOUND_STRING("Steel moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Steel-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_FLAME_RUSH] =
    {
        .name = _("Heat Rush"),
        .description = COMPOUND_STRING("Fire moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Fire-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_TIDAL_REFLEX] =
    {
        .name = _("Tidal Reflex"),
        .description = COMPOUND_STRING("Water moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Water-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_VERDANT_GALE] =
    {
        .name = _("Verdant Gale"),
        .description = COMPOUND_STRING("Grass moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Grass-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_STATIC_BURST] =
    {
        .name = _("Static Burst"),
        .description = COMPOUND_STRING("Electric moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Electric-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_THINK_AHEAD] =
    {
        .name = _("Think Ahead"),
        .description = COMPOUND_STRING("Psychic moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Psychic-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_FROST_SNAP] =
    {
        .name = _("Frost Snap"),
        .description = COMPOUND_STRING("Ice moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Ice-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_DRACONIC_REFLEX] =
    {
        .name = _("Draconic Sense"),
        .description = COMPOUND_STRING("Dragon moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Dragon-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_NIGHT_STALKER] =
    {
        .name = _("Nightstalker"),
        .description = COMPOUND_STRING("Dark moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Dark-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_FAIRY_BLINK] =
    {
        .name = _("Sprite shift"),
        .description = COMPOUND_STRING("Fairy moves go first."),
        .longDescription = COMPOUND_STRING("At full HP, Fairy-type\n"
                                           "moves gain +1 priority."),
        .aiRating = 5,
    },

    [ABILITY_ELEMENTAL_FIST] =
    {
        .name = _("Elemental Fist"),
        .description = COMPOUND_STRING("Punches use Sp. Atk."),
        .longDescription = COMPOUND_STRING("Punching moves use Sp.\n"
                                           "Atk instead of Attack."),
        .aiRating = 5,
    },

    [ABILITY_ELEMENTALIST] =
    {
        .name = _("Elementalist"),
        .description = COMPOUND_STRING("Physical uses Sp. Atk."),
        .longDescription = COMPOUND_STRING("Physical moves use Sp.\n"
                                           "Atk instead of Attack."),
        .aiRating = 5,
    },

    [ABILITY_SOOTHING] =
    {
        .name = _("Soothing"),
        .description = COMPOUND_STRING("May lull foes to sleep."),
        .longDescription = COMPOUND_STRING("Damaging moves have a\n"
                                           "10% chance to put the\n"
                                           "target to sleep."),
        .aiRating = 4,
    },

    [ABILITY_ROLLING_STONE] =
    {
        .name = _("Rolling Stones"),
        .description = COMPOUND_STRING("Rollout hits raise Speed."),
        .longDescription = COMPOUND_STRING("Each successful Rollout\n"
                                           "hit raises Speed by\n"
                                           "1 stage."),
        .aiRating = 5,
    },
    [ABILITY_GENERALIST] =
    {
        .name = _("Generalist"),
        .description = COMPOUND_STRING("Boosts varied types."),
        .longDescription = COMPOUND_STRING("Moves not matching this\n"
                                           "Pokemon's type deal 25%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_WINDBURST] =
    {
        .name = _("Windburst"),
        .description = COMPOUND_STRING("Sets Tailwind on entry."),
        .longDescription = COMPOUND_STRING("Sets Tailwind for its\n"
                                           "side when this Pokemon\n"
                                           "enters battle."),
        .aiRating = 8,
    },

    [ABILITY_BATTLE_FERVOR] =
    {
        .name = _("Battle Fervor"),
        .description = COMPOUND_STRING("Ups Attack on entry."),
        .longDescription = COMPOUND_STRING("On entry, raises Attack\n"
                                           "by 1 stage."),
        .aiRating = 3,
    },

    [ABILITY_GUARD_STANCE] =
    {
        .name = _("Guard Stance"),
        .description = COMPOUND_STRING("Ups Defense on entry."),
        .longDescription = COMPOUND_STRING("On entry, raises Defense\n"
                                           "by 1 stage."),
        .aiRating = 3,
    },

    [ABILITY_MENTAL_SURGE] =
    {
        .name = _("Mental Surge"),
        .description = COMPOUND_STRING("Ups Sp. Atk on entry."),
        .longDescription = COMPOUND_STRING("On entry, raises Sp. Atk\n"
                                           "by 1 stage."),
        .aiRating = 3,
    },

    [ABILITY_RESOLUTE_GUARD] =
    {
        .name = _("Resolute Guard"),
        .description = COMPOUND_STRING("Ups Sp. Def on entry."),
        .longDescription = COMPOUND_STRING("On entry, raises Sp. Def\n"
                                           "by 1 stage."),
        .aiRating = 3,
    },

    [ABILITY_SKIP_STEP] =
    {
        .name = _("Skip Step"),
        .description = COMPOUND_STRING("Ups Speed on entry."),
        .longDescription = COMPOUND_STRING("On entry, raises Speed\n"
                                           "by 1 stage."),
        .aiRating = 3,
    },

    [ABILITY_BREAKING_PRESENCE] =
    {
        .name = _("Breaking"),
        .description = COMPOUND_STRING("Lowers foes' Defense."),
        .longDescription = COMPOUND_STRING("On entry, lowers opposing\n"
                                           "Pokemon's Defense by\n"
                                           "1 stage."),
        .aiRating = 5,
    },

    [ABILITY_DISQUIET] =
    {
        .name = _("Disquiet"),
        .description = COMPOUND_STRING("Lowers foes' Sp. Def."),
        .longDescription = COMPOUND_STRING("On entry, lowers opposing\n"
                                           "Pokemon's Sp. Def by\n"
                                           "1 stage."),
        .aiRating = 5,
    },

    [ABILITY_HOBBLE] =
    {
        .name = _("Tangling"),
        .description = COMPOUND_STRING("Lowers foes' Speed."),
        .longDescription = COMPOUND_STRING("On entry, lowers opposing\n"
                                           "Pokemon's Speed by\n"
                                           "1 stage."),
        .aiRating = 5,
    },

    [ABILITY_SEER] =
    {
        .name = _("Seer"),
        .description = COMPOUND_STRING("Psychic hits boost Speed."),
        .longDescription = COMPOUND_STRING("Psychic-type attacks that\n"
                                           "deal damage raise Speed\n"
                                           "by 1 stage."),
        .aiRating = 5,
    },

    [ABILITY_SMOULDERING] =
    {
        .name = _("Smouldering"),
        .description = COMPOUND_STRING("Water raises Sp. Def."),
        .longDescription = COMPOUND_STRING("Absorbs Water-type moves\n"
                                           "and raises Sp. Def by\n"
                                           "1 stage."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_CONSUME] =
    {
        .name = _("Consume"),
        .description = COMPOUND_STRING("Heals after a KO."),
        .longDescription = COMPOUND_STRING("After knocking out foes,\n"
                                           "restores 1/2 max HP for\n"
                                           "each foe that fainted."),
        .aiRating = 6,
    },

    [ABILITY_LIFESTEAL] =
    {
        .name = _("Lifesteal"),
        .description = COMPOUND_STRING("Drains HP from damage."),
        .longDescription = COMPOUND_STRING("Damaging moves heal 1/8\n"
                                           "of the damage dealt."),
        .aiRating = 6,
    },

    [ABILITY_HAUNTING] =
    {
        .name = _("Haunting"),
        .description = COMPOUND_STRING("Ghost moves may flinch."),
        .longDescription = COMPOUND_STRING("Ghost-type attacks have\n"
                                           "a 20% chance to make the\n"
                                           "target flinch."),
        .aiRating = 5,
    },

    [ABILITY_WINDCALLER] =
    {
        .name = _("Windcaller"),
        .description = COMPOUND_STRING("Bolsters Flying/Tailwind."),
        .longDescription = COMPOUND_STRING("Flying-type moves deal\n"
                                           "30% more damage, and\n"
                                           "Tailwind lasts longer."),
        .aiRating = 7,
    },

    [ABILITY_SIEGEBREAKER] =
    {
        .name = _("Siegebreaker"),
        .description = COMPOUND_STRING("Attacks use Defense."),
        .longDescription = COMPOUND_STRING("Attacks use 2/3 of Defense\n"
                                           "instead of Attack or\n"
                                           "Sp. Atk."),
        .aiRating = 6,
    },

    [ABILITY_SANDSHIELD] =
    {
        .name = _("Sandshield"),
        .description = COMPOUND_STRING("Doubles Def in sandstorm."),
        .longDescription = COMPOUND_STRING("Doubles Defense during\n"
                                           "a sandstorm."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_JADE_BLOOM] =
    {
        .name = _("Jade Bloom"),
        .description = COMPOUND_STRING("Heals and blooms each turn."),
        .longDescription = COMPOUND_STRING("At turn end, if not\n"
                                           "statused, restores 1/16\n"
                                           "max HP and raises either\n"
                                           "Sp. Atk or Sp. Def."),
        .aiRating = 6,
    },

    [ABILITY_BRIMSTONE] =
    {
        .name = _("Brimstone"),
        .description = COMPOUND_STRING("Fire bypasses immunities."),
        .longDescription = COMPOUND_STRING("Fire-type moves ignore\n"
                                           "Flash Fire and other Fire\n"
                                           "immunities when this\n"
                                           "Pokemon attacks."),
        .aiRating = 5,
    },

    [ABILITY_STYGIAN] =
    {
        .name = _("Stygian"),
        .description = COMPOUND_STRING("Act first vs. sleep."),
        .longDescription = COMPOUND_STRING("Moves gain +1 priority\n"
                                           "when they are expected to\n"
                                           "hit a sleeping target."),
        .aiRating = 4,
    },

    [ABILITY_OMEGA] =
    {
        .name = _("Omega"),
        .description = COMPOUND_STRING("Deals SE; takes NVE hits."),
        .longDescription = COMPOUND_STRING("This Pokemon's attacks\n"
                                           "are always super\n"
                                           "effective; damage it\n"
                                           "takes is never very\n"
                                           "effective."),
        .aiRating = 8,
    },

    [ABILITY_PERMAFROST] =
    {
        .name = _("Permafrost"),
        .description = COMPOUND_STRING("Resists burns and Atk loss."),
        .longDescription = COMPOUND_STRING("Cannot be burned or have\n"
                                           "Attack lowered. Damaging\n"
                                           "moves may freeze or\n"
                                           "frostbite the target."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_STONE_FACE] =
    {
        .name = _("Stone Face"),
        .description = COMPOUND_STRING("Sturdy; blocks stat loss."),
        .longDescription = COMPOUND_STRING("Endures a full-HP KO at\n"
                                           "1/4 max HP and prevents\n"
                                           "other Pokemon from\n"
                                           "lowering its stats."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_VOIDTOUCH] =
    {
        .name = _("Voidtouch"),
        .description = COMPOUND_STRING("Ignores defensive screens."),
        .longDescription = COMPOUND_STRING("Damaging moves ignore\n"
                                           "Reflect, Light Screen,\n"
                                           "Aurora Veil, Safeguard,\n"
                                           "and Mist."),
        .aiRating = 5,
    },

    [ABILITY_GLACIAL] =
    {
        .name = _("Glacial"),
        .description = COMPOUND_STRING("Sp. Def rises; heals in hail."),
        .longDescription = COMPOUND_STRING("Raises Sp. Def by 1 on\n"
                                           "entry. In hail or snow,\n"
                                           "restores 1/8 max HP at\n"
                                           "turn's end."),
        .aiRating = 6,
    },

    [ABILITY_LUNAR_CYCLE] =
    {
        .name = _("Lunar Cycle"),
        .description = COMPOUND_STRING("Attacks raise Speed."),
        .longDescription = COMPOUND_STRING("After damaging a target\n"
                                           "with an attack, raises\n"
                                           "Speed by 1 stage."),
        .aiRating = 5,
    },

    [ABILITY_FROST_NOVA] =
    {
        .name = _("Frost Nova"),
        .description = COMPOUND_STRING("Freezes on being KO'd."),
        .longDescription = COMPOUND_STRING("When knocked out by an\n"
                                           "attack, freezes the\n"
                                           "attacker for exactly\n"
                                           "1 turn."),
        .aiRating = 4,
    },

    [ABILITY_SHOCKWIRING] =
    {
        .name = _("Shockwiring"),
        .description = COMPOUND_STRING("Charges on entry."),
        .longDescription = COMPOUND_STRING("On entry, gives this\n"
                                           "Pokemon the charged\n"
                                           "state."),
        .aiRating = 4,
    },

    [ABILITY_RITUAL] =
    {
        .name = _("Ritualist"),
        .description = COMPOUND_STRING("Absorbs Ghost; powers Hex."),
        .longDescription = COMPOUND_STRING("Absorbs Ghost-type moves\n"
                                           "to restore HP, and raises\n"
                                           "Hex's power to 75."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_OVERLOCK] =
    {
        .name = _("Overclock"),
        .description = COMPOUND_STRING("Shift Gear boosts Steel."),
        .longDescription = COMPOUND_STRING("After using Shift Gear,\n"
                                           "the next Steel-type move\n"
                                           "used by this Pokemon has\n"
                                           "double power."),
        .aiRating = 6,
    },

    [ABILITY_SPECTRAL_DRAIN] =
    {
        .name = _("Spectral Drain"),
        .description = COMPOUND_STRING("Ground/Ghost drains HP."),
        .longDescription = COMPOUND_STRING("Ground- and Ghost-type\n"
                                           "moves heal 25% of damage\n"
                                           "dealt. Immune to Leech\n"
                                           "Seed."),
        .aiRating = 6,
    },

    [ABILITY_BLAZING_SUN] =
    {
        .name = _("Blazing Sun"),
        .description = COMPOUND_STRING("Fire attacks always burn."),
        .longDescription = COMPOUND_STRING("Damaging Fire-type moves\n"
                                           "always burn the target if\n"
                                           "it can be burned."),
        .aiRating = 5,
    },

    [ABILITY_OVERLOAD] =
    {
        .name = _("Overload"),
        .description = COMPOUND_STRING("Ignores defense items."),
        .longDescription = COMPOUND_STRING("When attacking, ignores\n"
                                           "defensive effects from\n"
                                           "the target's held items."),
        .aiRating = 6,
    },

    [ABILITY_FILL_VOID] =
    {
        .name = _("Fill Void"),
        .description = COMPOUND_STRING("KOs raise Def and Sp. Atk."),
        .longDescription = COMPOUND_STRING("After this Pokemon knocks\n"
                                           "out a foe, raises Def and\n"
                                           "Sp. Atk by 1 stage."),
        .aiRating = 6,
    },

    [ABILITY_DUST_DEVIL] =
    {
        .name = _("Dust Devil"),
        .description = COMPOUND_STRING("Attacks may confuse."),
        .longDescription = COMPOUND_STRING("Damaging moves have a\n"
                                           "15% chance to confuse the\n"
                                           "target."),
        .aiRating = 4,
    },

    [ABILITY_SOLIDIFY] =
    {
        .name = _("Solidify"),
        .description = COMPOUND_STRING("Special hits raise Sp. Def."),
        .longDescription = COMPOUND_STRING("When hit by a special\n"
                                           "attack, raises Sp. Def by\n"
                                           "1 stage."),
        .aiRating = 5,
    },

    [ABILITY_UNLEASHED] =
    {
        .name = _("Unleashed"),
        .description = COMPOUND_STRING("Shell Smash ups all stats."),
        .longDescription = COMPOUND_STRING("Shell Smash raises all\n"
                                           "stats, but this Pokemon\n"
                                           "cannot use held items."),
        .aiRating = 6,
    },

    [ABILITY_TETHER] =
    {
        .name = _("Tether"),
        .description = COMPOUND_STRING("Copies foe stat boosts."),
        .longDescription = COMPOUND_STRING("Copies opposing stat\n"
                                           "boosts when they are\n"
                                           "raised."),
        .aiRating = 5,
    },

    [ABILITY_SOLAR_PANEL] =
    {
        .name = _("Solar Panel"),
        .description = COMPOUND_STRING("Sun guides Electric moves."),
        .longDescription = COMPOUND_STRING("In harsh sunlight,\n"
                                           "Electric-type moves used\n"
                                           "by this Pokemon never\n"
                                           "miss."),
        .aiRating = 4,
    },

    [ABILITY_INFERNAL] =
    {
        .name = _("Infernal"),
        .description = COMPOUND_STRING("Lowers foes' Atk and Def."),
        .longDescription = COMPOUND_STRING("On entry, lowers opposing\n"
                                           "Pokemon's Attack and\n"
                                           "Defense by 1 stage."),
        .aiRating = 6,
    },

    [ABILITY_REEF_WARDEN] =
    {
        .name = _("Reef Warden"),
        .description = COMPOUND_STRING("Heals out; blocks healing."),
        .longDescription = COMPOUND_STRING("Restores 1/2 max HP on\n"
                                           "switch-out; contact with\n"
                                           "this Pokemon blocks the\n"
                                           "attacker's healing."),
        .aiRating = 5,
    },

    [ABILITY_SOLAR_ARMOR] =
    {
        .name = _("Solar Armor"),
        .description = COMPOUND_STRING("Blocks status moves."),
        .longDescription = COMPOUND_STRING("Blocks status moves used\n"
                                           "against this Pokemon."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_ABYSSAL_VEIL] =
    {
        .name = _("Abyssal Veil"),
        .description = COMPOUND_STRING("Blocks status at high HP."),
        .longDescription = COMPOUND_STRING("Blocks status moves while\n"
                                           "this Pokemon has more\n"
                                           "than 75% HP."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_PLASMA_SURGE] =
    {
        .name = _("Plasma Surge"),
        .description = COMPOUND_STRING("Terrain attacks paralyze."),
        .longDescription = COMPOUND_STRING("During Electric Terrain,\n"
                                           "damaging attacks always\n"
                                           "paralyze targets if they\n"
                                           "can be paralyzed."),
        .aiRating = 6,
    },

    [ABILITY_PHALANX] =
    {
        .name = _("Phalanx"),
        .description = COMPOUND_STRING("Halves physical damage."),
        .longDescription = COMPOUND_STRING("Halves physical move\n"
                                           "damage taken by this\n"
                                           "Pokemon."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SPECTRAL] =
    {
        .name = _("Spectral"),
        .description = COMPOUND_STRING("Halves special damage."),
        .longDescription = COMPOUND_STRING("Halves special move\n"
                                           "damage taken by this\n"
                                           "Pokemon."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SUNHARDENED] =
    {
        .name = _("Sunhardened"),
        .description = COMPOUND_STRING("Doubles Sp. Def in sun."),
        .longDescription = COMPOUND_STRING("Doubles Sp. Def while\n"
                                           "harsh sunlight is active."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_HEATSTORM] =
    {
        .name = _("Heatstorm"),
        .description = COMPOUND_STRING("Scorches field on entry."),
        .longDescription = COMPOUND_STRING("Creates a Scorched Field\n"
                                           "on entry. It strengthens\n"
                                           "Fire moves and Scald while\n"
                                           "weakening Water and Ice\n"
                                           "moves."),
        .aiRating = 8,
    },

    [ABILITY_COALWALKER] =
    {
        .name = _("Coalwalker"),
        .description = COMPOUND_STRING("Doubles Def when scorched."),
        .longDescription = COMPOUND_STRING("Doubles Defense while a\n"
                                           "Scorched Field is active."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_LAVA_SURFER] =
    {
        .name = _("Lava Surfer"),
        .description = COMPOUND_STRING("Scorched doubles Speed."),
        .longDescription = COMPOUND_STRING("Doubles Speed while a\n"
                                           "Scorched Field is active."),
        .aiRating = 6,
    },

    [ABILITY_ASH_ASSETS] =
    {
        .name = _("Ash Assets"),
        .description = COMPOUND_STRING("Thrives in scorched fields."),
        .longDescription = COMPOUND_STRING("After a KO, creates a\n"
                                           "scorched field if absent;\n"
                                           "attacks deal 15% more in\n"
                                           "scorched fields."),
        .aiRating = 7,
    },

    [ABILITY_FORCE_RETURN] =
    {
        .name = _("Force Return"),
        .description = COMPOUND_STRING("Reflects attack damage."),
        .longDescription = COMPOUND_STRING("When hit by an attack,\n"
                                           "the attacker takes 30% of\n"
                                           "the damage dealt."),
        .aiRating = 6,
    },

    [ABILITY_ENIGMA] =
    {
        .name = _("Enigma"),
        .description = COMPOUND_STRING("Doubles Power moves."),
        .longDescription = COMPOUND_STRING("Moves with Power in their\n"
                                           "name deal double damage."),
        .aiRating = 6,
    },

    [ABILITY_BURROWER] =
    {
        .name = _("Burrower"),
        .description = COMPOUND_STRING("Dig is instant, stronger."),
        .longDescription = COMPOUND_STRING("Dig executes in 1 turn\n"
                                           "and deals 50% more\n"
                                           "damage."),
        .aiRating = 5,
    },

    [ABILITY_DIVER] =
    {
        .name = _("Diver"),
        .description = COMPOUND_STRING("Dive is instant, stronger."),
        .longDescription = COMPOUND_STRING("Dive executes in 1 turn\n"
                                           "and deals 50% more\n"
                                           "damage."),
        .aiRating = 5,
    },

    [ABILITY_LAST_STAND] =
    {
        .name = _("Last Stand"),
        .description = COMPOUND_STRING("Boosts attacks, costs HP."),
        .longDescription = COMPOUND_STRING("Damaging attacks hit 30%\n"
                                           "harder, but this Pokemon\n"
                                           "loses 10% max HP after\n"
                                           "attacking."),
        .aiRating = 6,
    },

    [ABILITY_HUNTER] =
    {
        .name = _("Hunter"),
        .description = COMPOUND_STRING("Preys on paralysis."),
        .longDescription = COMPOUND_STRING("Glare also confuses.\n"
                                           "Attack is raised 50% while\n"
                                           "a foe is paralyzed."),
        .aiRating = 6,
    },

    [ABILITY_NINE_LIVES] =
    {
        .name = _("Nine Lives"),
        .description = COMPOUND_STRING("Sturdy; fast when low."),
        .longDescription = COMPOUND_STRING("Endures full-HP KOs like\n"
                                           "Sturdy, and gains +2\n"
                                           "priority at 1/3 HP or\n"
                                           "less."),
        .aiRating = 7,
    },

    [ABILITY_DEBILITATE] =
    {
        .name = _("Debilitate"),
        .description = COMPOUND_STRING("Drains foe PP faster."),
        .longDescription = COMPOUND_STRING("Opposing Pokemon spend\n"
                                           "3 extra PP when using\n"
                                           "moves against this\n"
                                           "Pokemon."),
        .aiRating = 5,
    },

    [ABILITY_TITAN_GRIP] =
    {
        .name = _("Titan Grip"),
        .description = COMPOUND_STRING("Turns recoil drops on foes."),
        .longDescription = COMPOUND_STRING("Close Combat and\n"
                                           "Superpower lower the\n"
                                           "opposing Pokemon's stats\n"
                                           "instead of this one's."),
        .aiRating = 6,
    },

    [ABILITY_FLEXIBLE] =
    {
        .name = _("Prepared"),
        .description = COMPOUND_STRING("Two-turn moves are instant."),
        .longDescription = COMPOUND_STRING("Two-turn moves execute\n"
                                           "in a single turn."),
        .aiRating = 5,
    },

    [ABILITY_REBORN] =
    {
        .name = _("Reborn"),
        .description = COMPOUND_STRING("Revives itself once."),
        .longDescription = COMPOUND_STRING("Once per battle, if this\n"
                                           "Pokemon would faint, it\n"
                                           "survives and heals to\n"
                                           "full HP instead."),
        .aiRating = 8,
    },

    [ABILITY_REJUVENATION] =
    {
        .name = _("Rejuvenation"),
        .description = COMPOUND_STRING("Heals if unhurt."),
        .longDescription = COMPOUND_STRING("At turn's end, restores\n"
                                           "1/10 max HP if it took no\n"
                                           "damage that turn."),
        .aiRating = 6,
    },

    [ABILITY_TIDAL_DEITY] =
    {
        .name = _("Tidal Deity"),
        .description = COMPOUND_STRING("Full HP pierces defenses."),
        .longDescription = COMPOUND_STRING("At full HP, bypasses\n"
                                           "protection and screens.\n"
                                           "When HP drops below full,\n"
                                           "sets rain for 5 turns."),
        .aiRating = 8,
    },

    [ABILITY_ROCKSTORM] =
    {
        .name = _("Rockstorm"),
        .description = COMPOUND_STRING("Rock moves hit in sand."),
        .longDescription = COMPOUND_STRING("In a sandstorm, Rock-\n"
                                           "type moves used by this\n"
                                           "Pokemon cannot miss."),
        .aiRating = 5,
    },

    [ABILITY_STORMRIDER] =
    {
        .name = _("Stormrider"),
        .description = COMPOUND_STRING("Lowers foes' Sp. Def."),
        .longDescription = COMPOUND_STRING("At each turn's end,\n"
                                           "lowers the opposing\n"
                                           "Pokemon's Sp. Def by\n"
                                           "1 stage."),
        .aiRating = 6,
    },

    [ABILITY_VOLCANO_HOWL] =
    {
        .name = _("Volcano Howl"),
        .description = COMPOUND_STRING("Lowers foes' Defense."),
        .longDescription = COMPOUND_STRING("At each turn's end,\n"
                                           "lowers the opposing\n"
                                           "Pokemon's Defense by\n"
                                           "1 stage."),
        .aiRating = 6,
    },

    [ABILITY_ARCTIC_AURA] =
    {
        .name = _("Arctic Aura"),
        .description = COMPOUND_STRING("Lowers foes' Attack."),
        .longDescription = COMPOUND_STRING("At each turn's end,\n"
                                           "lowers the opposing\n"
                                           "Pokemon's Attack by\n"
                                           "1 stage."),
        .aiRating = 6,
    },

    [ABILITY_BLOODLUST] =
    {
        .name = _("Bloodlust"),
        .description = COMPOUND_STRING("Crits raise Atk and Speed."),
        .longDescription = COMPOUND_STRING("Landing a critical hit\n"
                                           "raises Attack and Speed\n"
                                           "by 1 stage each."),
        .aiRating = 5,
    },

    [ABILITY_GANG_UP] =
    {
        .name = _("Gang Up"),
        .description = COMPOUND_STRING("Preys on hurt foes."),
        .longDescription = COMPOUND_STRING("Moves deal 20% more\n"
                                           "damage to foes already\n"
                                           "hurt this turn."),
        .aiRating = 5,
    },

    [ABILITY_PENDULUM] =
    {
        .name = _("Pendulum"),
        .description = COMPOUND_STRING("Repeated moves power up."),
        .longDescription = COMPOUND_STRING("Consecutive uses of the\n"
                                           "same move gain 20% more\n"
                                           "power, up to 60%."),
        .aiRating = 5,
    },

    [ABILITY_MOMENTUM] =
    {
        .name = _("Momentum"),
        .description = COMPOUND_STRING("Priority raises Speed."),
        .longDescription = COMPOUND_STRING("After using a priority\n"
                                           "move, Speed rises by\n"
                                           "1 stage."),
        .aiRating = 4,
    },

    [ABILITY_DESPERADO] =
    {
        .name = _("Desperado"),
        .description = COMPOUND_STRING("SE hits raise offenses."),
        .longDescription = COMPOUND_STRING("Taking super-effective\n"
                                           "damage raises Attack and\n"
                                           "Sp. Atk by 1 stage."),
        .aiRating = 5,
    },

    [ABILITY_GLASS_CANNON] =
    {
        .name = _("Glass Cannon"),
        .description = COMPOUND_STRING("Stronger but frailer."),
        .longDescription = COMPOUND_STRING("On entry, raises its\n"
                                           "higher offense by 2 and\n"
                                           "lowers both defenses by 2."),
        .aiRating = 4,
    },

    [ABILITY_AEGIS] =
    {
        .name = _("Aegis"),
        .description = COMPOUND_STRING("Caps one hit per turn."),
        .longDescription = COMPOUND_STRING("Once per turn, direct\n"
                                           "attack damage cannot\n"
                                           "exceed 1/4 max HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MARTYR] =
    {
        .name = _("Martyr"),
        .description = COMPOUND_STRING("Fainting heals allies."),
        .longDescription = COMPOUND_STRING("When this Pokemon faints,\n"
                                           "its allies recover\n"
                                           "1/4 max HP."),
        .aiRating = 4,
    },

    [ABILITY_INDOMITABLE] =
    {
        .name = _("Indomitable"),
        .description = COMPOUND_STRING("No flinch; dodges status."),
        .longDescription = COMPOUND_STRING("Prevents flinching.\n"
                                           "Incoming status moves\n"
                                           "have halved accuracy."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_COLOSSAL] =
    {
        .name = _("Colossal"),
        .description = COMPOUND_STRING("Blocks weak attacks."),
        .longDescription = COMPOUND_STRING("Damaging moves with\n"
                                           "44 power or less do not\n"
                                           "affect this Pokemon."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PARRYING] =
    {
        .name = _("Parrying"),
        .description = COMPOUND_STRING("Focuses through hits."),
        .longDescription = COMPOUND_STRING("Focus Punch is not\n"
                                           "interrupted, and charging\n"
                                           "hits raise Defense."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FAINTRATTLE] =
    {
        .name = _("Faintrattle"),
        .description = COMPOUND_STRING("Poisons contact KOs."),
        .longDescription = COMPOUND_STRING("If a contact attack\n"
                                           "knocks it out, the\n"
                                           "attacker is badly poisoned."),
        .aiRating = 4,
    },

    [ABILITY_SHARDPLATE] =
    {
        .name = _("Shardplate"),
        .description = COMPOUND_STRING("Plate weakens over battle."),
        .longDescription = COMPOUND_STRING("Direct damage is reduced\n"
                                           "at first, weakening with\n"
                                           "each hit this battle."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_HAUNTED] =
    {
        .name = _("Haunted"),
        .description = COMPOUND_STRING("Counts as statused."),
        .longDescription = COMPOUND_STRING("Acts as if statused for\n"
                                           "status-based effects, but\n"
                                           "blocks major status."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_MENDING] =
    {
        .name = _("Mending"),
        .description = COMPOUND_STRING("May heal at turn end."),
        .longDescription = COMPOUND_STRING("At turn's end, has a 30%\n"
                                           "chance to cure status and\n"
                                           "heal 1/8 max HP."),
        .aiRating = 5,
    },

    [ABILITY_PLAGUETOUCH] =
    {
        .name = _("Plaguetouch"),
        .description = COMPOUND_STRING("Contact may inflict status."),
        .longDescription = COMPOUND_STRING("Contact attacks have a\n"
                                           "20% chance to inflict a\n"
                                           "random major status."),
        .aiRating = 5,
    },

    [ABILITY_MONSOON] =
    {
        .name = _("Monsoon"),
        .description = COMPOUND_STRING("Rain empowers Water."),
        .longDescription = COMPOUND_STRING("In rain, Water moves do\n"
                                           "not miss and bypass Water\n"
                                           "immunities."),
        .aiRating = 6,
    },

    [ABILITY_MIRAGE] =
    {
        .name = _("Mirage"),
        .description = COMPOUND_STRING("Sun may confuse foes."),
        .longDescription = COMPOUND_STRING("In sun, damaging moves\n"
                                           "have a 25% chance to\n"
                                           "confuse the target."),
        .aiRating = 4,
    },

    [ABILITY_BLIZZARD_HEART] =
    {
        .name = _("Blizzard Heart"),
        .description = COMPOUND_STRING("Snow may freeze foes."),
        .longDescription = COMPOUND_STRING("In snow or hail, Ice\n"
                                           "attacks have a 20% chance\n"
                                           "to freeze or frostbite."),
        .aiRating = 5,
    },

    [ABILITY_MUDSLIDE] =
    {
        .name = _("Mudslide"),
        .description = COMPOUND_STRING("Sand absorbs Water."),
        .longDescription = COMPOUND_STRING("In sand, absorbs Water\n"
                                           "moves and raises Defense\n"
                                           "by 2 stages."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_CHANNEL_EARTH] =
    {
        .name = _("Channel Earth"),
        .description = COMPOUND_STRING("Terrain heals HP."),
        .longDescription = COMPOUND_STRING("At turn's end, heals\n"
                                           "1/16 max HP while any\n"
                                           "terrain is active."),
        .aiRating = 4,
    },

    [ABILITY_MAGNIFY_FIELD] =
    {
        .name = _("Magnify Field"),
        .description = COMPOUND_STRING("Extends weather/terrain."),
        .longDescription = COMPOUND_STRING("On entry, extends finite\n"
                                           "active weather and terrain\n"
                                           "by 2 turns."),
        .aiRating = 6,
    },

    [ABILITY_BLITZ] =
    {
        .name = _("Blitz"),
        .description = COMPOUND_STRING("Next hit is stronger."),
        .longDescription = COMPOUND_STRING("After using Protect, its\n"
                                           "next damaging move deals\n"
                                           "20% more damage."),
        .aiRating = 5,
    },

    [ABILITY_GUARDIAN] =
    {
        .name = _("Guardian"),
        .description = COMPOUND_STRING("Draws and softens attacks."),
        .longDescription = COMPOUND_STRING("Draws single-target foe\n"
                                           "attacks from allies and\n"
                                           "takes 15% less damage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_BACKDRAFT] =
    {
        .name = _("Backdraft"),
        .description = COMPOUND_STRING("Switching lowers foe Speed."),
        .longDescription = COMPOUND_STRING("When this Pokemon switches\n"
                                           "out voluntarily, opposing\n"
                                           "Pokemon's Speed falls by\n"
                                           "1 stage."),
        .aiRating = 5,
    },

    [ABILITY_RALLY] =
    {
        .name = _("Rally"),
        .description = COMPOUND_STRING("Boosts ally's best stat."),
        .longDescription = COMPOUND_STRING("On entry in doubles,\n"
                                           "raises its ally's highest\n"
                                           "non-HP stat by 1."),
        .aiRating = 5,
    },

    [ABILITY_ECHO_CHAMBER] =
    {
        .name = _("Echo Chamber"),
        .description = COMPOUND_STRING("Sound moves echo."),
        .longDescription = COMPOUND_STRING("Single-target sound moves\n"
                                           "strike twice, with the\n"
                                           "second hit weaker."),
        .aiRating = 6,
    },

    [ABILITY_FLARE] =
    {
        .name = _("Flare"),
        .description = COMPOUND_STRING("Burned foes fuel Fire."),
        .longDescription = COMPOUND_STRING("Fire-type moves deal\n"
                                           "50% more damage to burned\n"
                                           "targets."),
        .aiRating = 5,
    },

    [ABILITY_SPLINTER] =
    {
        .name = _("Splinter"),
        .description = COMPOUND_STRING("Damaged foes take chips."),
        .longDescription = COMPOUND_STRING("At turn's end, damaged\n"
                                           "foes lose 1/16 max HP."),
        .aiRating = 4,
    },

    [ABILITY_MAIM_AND_MEND] =
    {
        .name = _("Maim and Mend"),
        .description = COMPOUND_STRING("Crits heal the user."),
        .longDescription = COMPOUND_STRING("Landing a critical hit\n"
                                           "heals the user by 1/4 of\n"
                                           "damage dealt."),
        .aiRating = 5,
    },

    [ABILITY_VALKYRIE] =
    {
        .name = _("Valkyrie"),
        .description = COMPOUND_STRING("Gains Steel resistances."),
        .longDescription = COMPOUND_STRING("Gains Steel-type\n"
                                           "resistances and Poison\n"
                                           "immunity without gaining\n"
                                           "Steel-type weaknesses."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_IMMOVABLE] =
    {
        .name = _("Immovable"),
        .description = COMPOUND_STRING("Moves last; cannot be forced."),
        .longDescription = COMPOUND_STRING("Moves last within its\n"
                                           "priority bracket and\n"
                                           "blocks being forced out."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_TRANSMUTE] =
    {
        .name = _("Transmute"),
        .description = COMPOUND_STRING("Weakens first attack."),
        .longDescription = COMPOUND_STRING("Once per battle, changes\n"
                                           "a foe's direct attack to\n"
                                           "a resisted type."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TWIN_STARS] =
    {
        .name = _("Twin Stars"),
        .description = COMPOUND_STRING("Twins boost together."),
        .longDescription = COMPOUND_STRING("In doubles, paired Twin\n"
                                           "Stars users each gain\n"
                                           "+1 to five stats once."),
        .aiRating = 7,
    },

    [ABILITY_COSMIC_FORM] =
    {
        .name = _("Cosmic Form"),
        .description = COMPOUND_STRING("Bends type matchups."),
        .longDescription = COMPOUND_STRING("Its moves bypass type\n"
                                           "immunities, and super-\n"
                                           "effective damage is cut."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_TIME_SPIRAL] =
    {
        .name = _("Time Spiral"),
        .description = COMPOUND_STRING("Warps priority and fields."),
        .longDescription = COMPOUND_STRING("Inverts move priority.\n"
                                           "Finite weather and terrain\n"
                                           "lose an extra turn at each\n"
                                           "turn's end."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_NULL_SPACE] =
    {
        .name = _("Null Space"),
        .description = COMPOUND_STRING("Pierces protection."),
        .longDescription = COMPOUND_STRING("Damaging moves bypass\n"
                                           "single-turn protection,\n"
                                           "but deal half damage."),
        .aiRating = 6,
    },

    [ABILITY_SPACETIME_RIFT] =
    {
        .name = _("Spacetime Rift"),
        .description = COMPOUND_STRING("Protects cosmic twins."),
        .longDescription = COMPOUND_STRING("On a side with Palkia and\n"
                                           "Dialga, protects them from\n"
                                           "spread attacks."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_UNDERDOG] =
    {
        .name = _("Underdog"),
        .description = COMPOUND_STRING("Hits stronger foes harder."),
        .longDescription = COMPOUND_STRING("Deals 30% more damage to\n"
                                           "targets with a higher base\n"
                                           "stat total."),
        .aiRating = 5,
    },

    [ABILITY_ROCK_AND_STONE] =
    {
        .name = _("Rock and Stone"),
        .description = COMPOUND_STRING("KOs set Stealth Rock."),
        .longDescription = COMPOUND_STRING("When it knocks out a foe,\n"
                                           "sets Stealth Rock on the\n"
                                           "opposing side."),
        .aiRating = 6,
    },

    [ABILITY_POLARITY_SHIFT] =
    {
        .name = _("Polarity Shift"),
        .description = COMPOUND_STRING("Entry swaps foe's Speed."),
        .longDescription = COMPOUND_STRING("On entry, swaps Speed\n"
                                           "with the opposing Pokemon."),
        .aiRating = 5,
    },

    [ABILITY_HORSE_COUNCIL] =
    {
        .name = _("Horse Council"),
        .description = COMPOUND_STRING("Horses boost attacks."),
        .longDescription = COMPOUND_STRING("Physical and special\n"
                                           "attacks deal 10% more\n"
                                           "damage per living horse\n"
                                           "ally in the party."),
        .aiRating = 6,
    },

    [ABILITY_POWER_SHIFT] =
    {
        .name = _("Power Shift"),
        .description = COMPOUND_STRING("Entry swaps foe offenses."),
        .longDescription = COMPOUND_STRING("On entry, swaps Attack\n"
                                           "and Sp. Atk with the\n"
                                           "opposing Pokemon."),
        .aiRating = 5,
    },

    [ABILITY_WISHMAKER] =
    {
        .name = _("Wishmaker"),
        .description = COMPOUND_STRING("Casts Wish on entry."),
        .longDescription = COMPOUND_STRING("On entry, casts Wish\n"
                                           "for itself."),
        .aiRating = 5,
    },

    [ABILITY_FLIER] =
    {
        .name = _("Flier"),
        .description = COMPOUND_STRING("Fly is instant, stronger."),
        .longDescription = COMPOUND_STRING("Fly executes in 1 turn\n"
                                           "and deals 50% more\n"
                                           "damage."),
        .aiRating = 5,
    },

    [ABILITY_FLAMEBURST] =
    {
        .name = _("Flameburst"),
        .description = COMPOUND_STRING("Burns foes on fainting."),
        .longDescription = COMPOUND_STRING("When this Pokemon faints\n"
                                           "from a damaging attack,\n"
                                           "it burns the opposing\n"
                                           "side."),
        .aiRating = 5,
    },

    [ABILITY_INKY] =
    {
        .name = _("Inky"),
        .description = COMPOUND_STRING("Hits lower Accuracy."),
        .longDescription = COMPOUND_STRING("When hit by a damaging\n"
                                           "move, lowers the\n"
                                           "attacker's Accuracy."),
        .aiRating = 4,
    },

    [ABILITY_BRAND_OF_TORMENT] =
    {
        .name = _("Brand of Torment"),
        .description = COMPOUND_STRING("Contact may torment."),
        .longDescription = COMPOUND_STRING("Contact attacks have a\n"
                                           "30% chance to torment\n"
                                           "the attacker."),
        .aiRating = 4,
    },

    [ABILITY_DRAGONIZE] =
    {
        .name = _("Dragonize"),
        .description = COMPOUND_STRING("Normal moves turn Dragon."),
        .longDescription = COMPOUND_STRING("Normal-type moves become\n"
                                           "Dragon-type and deal 20%\n"
                                           "more damage."),
        .aiRating = 8,
    },

    [ABILITY_EELEVATE] =
    {
        .name = _("Eelevate"),
        .description = COMPOUND_STRING("Levitate and boosts KOs."),
        .longDescription = COMPOUND_STRING("The Pokemon is immune\n"
                                           "to Ground-type moves.\n"
                                           "When it knocks out a foe,\n"
                                           "its highest stat rises."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_MEGA_SOL] =
    {
        .name = _("Mega Sol"),
        .description = COMPOUND_STRING("Acts as sun for itself."),
        .longDescription = COMPOUND_STRING("The Pokemon's own moves\n"
                                           "and effects behave as if\n"
                                           "the sunlight is harsh."),
        .aiRating = 8,
    },

    [ABILITY_SPICY_SPRAY] =
    {
        .name = _("Spicy Spray"),
        .description = COMPOUND_STRING("Burns foes when damaged."),
        .longDescription = COMPOUND_STRING("When damaged by a direct\n"
                                           "attack, this Pokemon\n"
                                           "burns the attacker."),
        .aiRating = 5,
    },

    [ABILITY_WIND_CHIME] =
    {
        .name = _("Wind Chime"),
        .description = COMPOUND_STRING("Ups Sp. Atk if hit by wind."),
        .longDescription = COMPOUND_STRING("Immune to wind moves.\n"
                                           "Instead, they raise\n"
                                           "Sp. Atk. Tailwind also\n"
                                           "raises the Pokémon's\n"
                                           "Sp. Atk."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GRAVITY_WELL] =
    {
        .name = _("Gravity Well"),
        .description = COMPOUND_STRING("Sets Gravity on entry."),
        .longDescription = COMPOUND_STRING("Intensifies Gravity for\n"
                                           "5 turns when this Pokémon\n"
                                           "enters battle."),
        .aiRating = 6,
    },

    [ABILITY_ALLSEEING_IDOL] =
    {
        .name = _("Allseeing Idol"),
        .description = COMPOUND_STRING("Levitate; Gravity ups Def."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune to\n"
                                           "Ground moves and hazards,\n"
                                           "even during Gravity, which\n"
                                           "also boosts Defense by 30%."),
        .aiRating = 8,
        .breakable = TRUE,
    },
};
