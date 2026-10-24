from __future__ import annotations

import unittest

from tools.soulgold_docs.parsers.frontier import parse_frontier_entries, resolve_alias


SET = """
    [FRONTIER_MON_HERACROSS_5] = {
        .species = SPECIES_HERACROSS,
        .moves = {MOVE_CLOSE_COMBAT, MOVE_MEGAHORN, MOVE_STONE_EDGE, MOVE_NONE},
        .heldItem = ITEM_CHOICE_SCARF,
        .iv = TRAINER_PARTY_IVS(31, 30, 29, 28, 27, 26),
        .ev = TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0),
        .ability = ABILITY_MOXIE,
        .nature = NATURE_JOLLY
    },
"""


class FrontierParserTests(unittest.TestCase):
    def test_legacy_names_and_form_aliases_resolve_without_loops(self):
        aliases = {"MOVE_ANCIENTPOWER": "MOVE_ANCIENT_POWER", "SPECIES_LANDORUS": "SPECIES_LANDORUS_INCARNATE"}
        self.assertEqual(resolve_alias("MOVE_ANCIENTPOWER", aliases), "MOVE_ANCIENT_POWER")
        self.assertEqual(resolve_alias("SPECIES_LANDORUS", aliases), "SPECIES_LANDORUS_INCARNATE")
        with self.assertRaisesRegex(ValueError, "Cyclic"):
            resolve_alias("A", {"A": "B", "B": "A"})

    def test_stat_macro_order_is_mapped_to_display_order(self):
        mon = parse_frontier_entries([SET])[0]
        self.assertEqual(mon["evs"], [4, 252, 0, 0, 0, 252])
        self.assertEqual(mon["ivs"], [31, 30, 29, 27, 26, 28])
        self.assertEqual(mon["itemConstant"], "ITEM_CHOICE_SCARF")
        self.assertEqual(mon["nature"], "Jolly")
        self.assertEqual(mon["setNumber"], 5)
        self.assertEqual(len(mon["moves"]), 3)

    def test_expansion_braces_and_numeric_neutral_nature(self):
        source = SET.replace("ITEM_CHOICE_SCARF,", "{ITEM_CHOICE_SCARF},").replace("NATURE_JOLLY", "0")
        mon = parse_frontier_entries([source])[0]
        self.assertEqual(mon["nature"], "Hardy")
        self.assertEqual(mon["itemConstant"], "ITEM_CHOICE_SCARF")

    def test_both_tables_are_included_without_renumbering(self):
        expansion = SET.replace("HERACROSS_5", "HERACROSS_7")
        self.assertEqual([mon["setNumber"] for mon in parse_frontier_entries([SET, expansion])], [5, 7])

    def test_named_sets_are_preserved(self):
        mon = parse_frontier_entries([SET.replace("HERACROSS_5", "PIKACHU_PARTNER")])[0]
        self.assertEqual(mon["setId"], "FRONTIER_MON_PIKACHU_PARTNER")
        self.assertIsNone(mon["setNumber"])

    def test_duplicate_and_unsupported_tables_fail_instead_of_losing_sets(self):
        with self.assertRaisesRegex(ValueError, "Duplicate"):
            parse_frontier_entries([SET, SET])
        with self.assertRaisesRegex(ValueError, "Duplicate"):
            parse_frontier_entries([SET + SET])
        with self.assertRaisesRegex(ValueError, "preprocessing"):
            parse_frontier_entries(["#if SOMETHING\n" + SET + "#endif"])
        with self.assertRaisesRegex(ValueError, "spread"):
            parse_frontier_entries([SET.replace("TRAINER_PARTY_EVS(4, 252, 0, 252, 0, 0)", "0")])


if __name__ == "__main__":
    unittest.main()
