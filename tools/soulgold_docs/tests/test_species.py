from __future__ import annotations

import unittest

from tools.soulgold_docs.parsers.species import egg_move_symbol_for_family, is_dex_visible_species, johto_dex_species_order, parse_species


class SpeciesExtraDataTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.species = parse_species().by_constant

    def test_ev_yields_are_parsed(self) -> None:
        self.assertEqual(self.species["SPECIES_BULBASAUR"].ev_yield, {"spa": 1})
        self.assertEqual(
            self.species["SPECIES_ROTOM"].ev_yield,
            {"spa": 1, "spe": 1},
        )

    def test_egg_groups_are_named_and_deduplicated(self) -> None:
        self.assertEqual(
            self.species["SPECIES_BULBASAUR"].egg_groups,
            ["EGG_GROUP_MONSTER", "EGG_GROUP_GRASS"],
        )
        self.assertEqual(
            self.species["SPECIES_ROTOM"].egg_groups,
            ["EGG_GROUP_AMORPHOUS"],
        )
        self.assertEqual(
            self.species["SPECIES_MEWTWO"].egg_groups,
            ["EGG_GROUP_NO_EGGS_DISCOVERED"],
        )

    def test_dex_filter_categories_are_parsed(self) -> None:
        self.assertIn("legendary", self.species["SPECIES_MEWTWO"].categories)
        self.assertIn("mythical", self.species["SPECIES_MEW"].categories)
        self.assertIn("paradox", self.species["SPECIES_GREAT_TUSK"].categories)
        self.assertIn("mega", self.species["SPECIES_VENUSAUR_MEGA"].categories)
        self.assertIn("regional", self.species["SPECIES_RAICHU_ALOLA"].categories)
        self.assertIn("fossil", self.species["SPECIES_LILEEP"].categories)
        self.assertIn("fossil", self.species["SPECIES_CRADILY"].categories)
        self.assertIn("fossil", self.species["SPECIES_AERODACTYL_MEGA"].categories)
        self.assertEqual(self.species["SPECIES_RATTATA"].categories, [])

    def test_unobtainable_dada_zarude_is_hidden_from_the_dex(self) -> None:
        self.assertTrue(is_dex_visible_species("SPECIES_ZARUDE"))
        self.assertFalse(is_dex_visible_species("SPECIES_ZARUDE_DADA"))

    def test_display_numbers_follow_the_active_johto_dex_order(self) -> None:
        order = johto_dex_species_order()
        tatsugiri_number = order.index("SPECIES_TATSUGIRI") + 1

        self.assertEqual(self.species["SPECIES_BULBASAUR"].display_dex, 1)
        self.assertEqual(
            self.species["SPECIES_TATSUGIRI_CURLY"].display_dex,
            tatsugiri_number,
        )
        self.assertEqual(
            self.species["SPECIES_TATSUGIRI_DROOPY"].display_dex,
            tatsugiri_number,
        )
        self.assertEqual(
            self.species["SPECIES_TATSUGIRI_STRETCHY"].display_dex,
            tatsugiri_number,
        )

    def test_egg_moves_prefer_the_nearest_family_learnset(self) -> None:
        parent_map = {
            "SPECIES_MARILL": "SPECIES_AZURILL",
            "SPECIES_AZUMARILL": "SPECIES_MARILL",
        }

        self.assertEqual(
            egg_move_symbol_for_family(
                self.species["SPECIES_AZURILL"],
                self.species,
                parent_map,
            ),
            "sAzurillEggMoveLearnset",
        )
        self.assertEqual(
            egg_move_symbol_for_family(
                self.species["SPECIES_MARILL"],
                self.species,
                parent_map,
            ),
            "sMarillEggMoveLearnset",
        )
        self.assertEqual(
            egg_move_symbol_for_family(
                self.species["SPECIES_AZUMARILL"],
                self.species,
                parent_map,
            ),
            "sMarillEggMoveLearnset",
        )


if __name__ == "__main__":
    unittest.main()
