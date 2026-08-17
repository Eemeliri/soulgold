from __future__ import annotations

import unittest

from tools.learnset_helpers.preview_legacy_levelups import (
    DEFAULT_CONFIG,
    DEFAULT_CURRENT,
    DEFAULT_LEGACY,
    MOVES_HEADER,
    MergeConfig,
    canonical_move,
    load_config,
    merged_learnset,
    parse_learnsets,
    parse_move_aliases,
    prepare_additions,
)


class LegacyLevelUpTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.aliases = parse_move_aliases(MOVES_HEADER)
        cls.current = parse_learnsets(DEFAULT_CURRENT, "current")
        cls.legacy = parse_learnsets(DEFAULT_LEGACY, "legacy")
        cls.config = load_config(DEFAULT_CONFIG, cls.aliases)

    def additions(self, symbol: str, config: MergeConfig | None = None):
        return prepare_additions(
            symbol,
            self.current[symbol],
            self.legacy[symbol],
            config or self.config,
            self.aliases,
        )

    def test_blaziken_capstone_is_automatically_spaced(self) -> None:
        additions = self.additions("sBlazikenLevelUpLearnset")
        levels = {row.move: row.level for row in additions}

        self.assertEqual(levels["MOVE_SKY_UPPERCUT"], 60)
        self.assertEqual(levels["MOVE_PECK"], 14)

    def test_move_alias_does_not_create_a_duplicate(self) -> None:
        additions = self.additions("sBlazikenLevelUpLearnset")

        self.assertNotIn("MOVE_HIGH_JUMP_KICK", {row.move for row in additions})
        self.assertEqual(
            canonical_move("MOVE_HI_JUMP_KICK", self.aliases),
            canonical_move("MOVE_HIGH_JUMP_KICK", self.aliases),
        )

    def test_species_exclusions_and_overrides_are_applied_last(self) -> None:
        config = MergeConfig(
            minimum_spacing_level=40,
            minimum_spacing=3,
            globally_excluded_moves=frozenset(),
            species={
                "blaziken": {
                    "excludedMoves": ["MOVE_PECK"],
                    "levelOverrides": {"MOVE_SKY_UPPERCUT": 61},
                }
            },
        )
        additions = self.additions("sBlazikenLevelUpLearnset", config)

        self.assertEqual([(row.move, row.level) for row in additions], [("MOVE_SKY_UPPERCUT", 61)])

    def test_merge_retains_every_current_blaziken_row(self) -> None:
        symbol = "sBlazikenLevelUpLearnset"
        rows = merged_learnset(self.current[symbol], self.additions(symbol))

        for current_row in self.current[symbol]:
            self.assertIn(current_row, rows)


if __name__ == "__main__":
    unittest.main()
