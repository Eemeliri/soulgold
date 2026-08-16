from __future__ import annotations

import unittest

from tools.soulgold_docs.parsers.gifts import FOSSIL_REVIVAL_ITEMS, add_gift_species_locations


class GiftLocationTests(unittest.TestCase):
    def test_achievement_rewards_include_their_trophy_milestones(self) -> None:
        expected = {
            "SPECIES_GRENINJA_BOND": 30,
            "SPECIES_POIPOLE": 45,
            "SPECIES_FLOETTE_ETERNAL": 60,
            "SPECIES_ZARUDE": 75,
            "SPECIES_MAGEARNA_ORIGINAL": 100,
        }
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {species: object() for species in expected},
        )

        for species, trophies in expected.items():
            with self.subTest(species=species):
                self.assertEqual(len(locations[species]), 1)
                location = locations[species][0]
                self.assertEqual(location["map"], "MAP_ROUTE40_HOUSE4")
                self.assertEqual(
                    location["name"],
                    f"Route 40 Achievement reward ({trophies} trophies)",
                )
                self.assertEqual(location["method"], "Gift")

    def test_fossil_revivals_are_not_presented_as_ordinary_gifts(self) -> None:
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {species: object() for species in FOSSIL_REVIVAL_ITEMS},
        )

        for species, fossil in FOSSIL_REVIVAL_ITEMS.items():
            with self.subTest(species=species):
                expected_count = 2 if species == "SPECIES_KABUTO" else 1
                self.assertEqual(len(locations[species]), expected_count)
                location = locations[species][0]
                self.assertEqual(location["map"], "MAP_RUINS_OF_ALPH_LAB")
                self.assertEqual(location["name"], "Ruins of Alph Lab")
                self.assertIn(
                    fossil.removeprefix("ITEM_").replace("_", " ").title(),
                    location["method"],
                )
                self.assertNotEqual(location["method"], "Gift")

        for species in {
            "SPECIES_LILEEP",
            "SPECIES_KABUTO",
            "SPECIES_AERODACTYL",
            "SPECIES_ARCHEN",
            "SPECIES_TYRUNT",
            "SPECIES_AMAURA",
        }:
            self.assertIn("found via Rock Smash in Ruins of Alph", locations[species][0]["method"])

        self.assertEqual(locations["SPECIES_KABUTO"][0]["minLevel"], 5)
        self.assertIn("before 4th badge", locations["SPECIES_KABUTO"][0]["method"])
        self.assertEqual(locations["SPECIES_KABUTO"][1]["minLevel"], 20)
        self.assertIn("after 4th badge", locations["SPECIES_KABUTO"][1]["method"])


if __name__ == "__main__":
    unittest.main()
