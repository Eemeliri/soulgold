import unittest
from collections import defaultdict

from tools.soulgold_docs.constants import ADDITIONAL_IMPORTANT_ITEMS
from tools.soulgold_docs.parsers.items import (
    IMPORTANT_ITEM_LOCATION_OVERRIDES,
    add_bug_contest_reward_locations,
)


class ImportantItemExceptionTests(unittest.TestCase):
    def test_includes_special_use_items(self):
        self.assertTrue(
            {
                "ITEM_ABILITY_CAPSULE",
                "ITEM_ABILITY_PATCH",
                "ITEM_GRACIDEA",
            }.issubset(ADDITIONAL_IMPORTANT_ITEMS)
        )

    def test_gracidea_has_story_location_override(self):
        self.assertEqual(
            IMPORTANT_ITEM_LOCATION_OVERRIDES["ITEM_GRACIDEA"],
            [
                {
                    "map": "Goldenrod Flower Shop after showing Shaymin",
                    "source": "",
                }
            ],
        )


class BugContestItemLocationTests(unittest.TestCase):
    def test_adds_the_correct_place_choice_to_each_reward_stone(self):
        first_place = {
            "ITEM_MOON_STONE",
            "ITEM_SUN_STONE",
            "ITEM_LEAF_STONE",
            "ITEM_DAWN_STONE",
            "ITEM_SHINY_STONE",
            "ITEM_DUSK_STONE",
            "ITEM_ICE_STONE",
        }
        second_place = {
            "ITEM_FIRE_STONE",
            "ITEM_THUNDER_STONE",
            "ITEM_WATER_STONE",
        }
        locations = defaultdict(list)

        add_bug_contest_reward_locations(locations, first_place | second_place)

        for item in first_place:
            self.assertIn(
                {"map": "Bug Catching Contest", "source": "1st place choice"},
                locations[item],
            )
        for item in second_place:
            self.assertIn(
                {"map": "Bug Catching Contest", "source": "2nd place choice"},
                locations[item],
            )


if __name__ == "__main__":
    unittest.main()
