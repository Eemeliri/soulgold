from __future__ import annotations

import unittest
from dataclasses import dataclass

from tools.soulgold_docs.parsers.encounters import parse_wild_encounters


@dataclass
class StubSpecies:
    name: str
    sprite: str | None = None


class WildEncounterAggregationTests(unittest.TestCase):
    def test_battle_cafe_encounters_are_hidden(self) -> None:
        encounters = parse_wild_encounters(
            {"SPECIES_CHI_YU": StubSpecies("Chi-Yu")}
        )

        self.assertNotIn("MAP_BATTLE_CAFE", {encounter["map"] for encounter in encounters})

    def test_kanto_and_legacy_encounters_are_hidden(self) -> None:
        encounters = parse_wild_encounters({})
        maps = {encounter["map"] for encounter in encounters}

        self.assertNotIn("MAP_VERMILION_CITY_PORT_OUTSIDE", maps)
        self.assertNotIn("MAP_SOUTHERN_ISLAND_EXTERIOR", maps)
        self.assertIn("MAP_ROUTE28", maps)

    def test_repeated_rotom_slots_are_combined(self) -> None:
        encounters = parse_wild_encounters(
            {"SPECIES_ROTOM": StubSpecies("Rotom")}  # type: ignore[dict-item]
        )
        nameless_cave_1f = next(
            encounter
            for encounter in encounters
            if encounter["map"] == "MAP_CERULEAN_CAVE_1F"
        )
        land_mons = next(
            method["mons"]
            for method in nameless_cave_1f["variants"][0]["methods"]
            if method["key"] == "land_mons"
        )
        rotom = [mon for mon in land_mons if mon["species"] == "SPECIES_ROTOM"]

        self.assertEqual(len(rotom), 1)
        self.assertEqual(rotom[0]["minLevel"], 58)
        self.assertEqual(rotom[0]["maxLevel"], 69)
        self.assertEqual(rotom[0]["rate"], 5)

    def test_species_aliases_resolve_to_their_documented_form(self) -> None:
        encounters = parse_wild_encounters(
            {
                "SPECIES_TATSUGIRI_CURLY": StubSpecies(
                    "Tatsugiri",
                    "sprites/pokemon/tatsugiri_curly.png",
                )
            }  # type: ignore[dict-item]
        )
        dragons_den = next(
            encounter
            for encounter in encounters
            if encounter["map"] == "MAP_DRAGONS_DEN_CAVERN"
        )
        tatsugiri = [
            mon
            for variant in dragons_den["variants"]
            for method in variant["methods"]
            for mon in method["mons"]
            if mon["species"] == "SPECIES_TATSUGIRI_CURLY"
        ]

        self.assertTrue(tatsugiri)
        self.assertTrue(all(mon["hasSpecies"] for mon in tatsugiri))
        self.assertTrue(all(mon["sprite"] for mon in tatsugiri))


if __name__ == "__main__":
    unittest.main()
