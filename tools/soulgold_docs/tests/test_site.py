from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools.soulgold_docs import site

TEMPLATE = """<html><head><base href="./">
    <title>Soulgold Documentation</title>
    <meta name="description" content="Default">
    <meta property="og:title" content="Soulgold Documentation">
    <meta property="og:description" content="Default">
    <meta name="docs-data-version" content="{{DATA_VERSION}}">
    <link rel="stylesheet" href="assets/styles.css">
  </head><span class="header-version">{{LATEST_VERSION}}</span><script src="assets/app.js?v=stale"></script></html>"""


class StaticSiteRefreshTests(unittest.TestCase):
    def setUp(self) -> None:
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        root = Path(directory.name)
        self.source = root / "source"
        self.output = root / "output"
        self.header = root / "version.h"
        (self.source / "assets").mkdir(parents=True)
        (self.source / "index.html").write_text(TEMPLATE)
        (self.source / "assets" / "app.js").write_text("console.log('app');")
        (self.source / "assets" / "styles.css").write_text("body {}")
        (self.source / "version.json").write_text('{"latestVersion":"v1.1.3"}')
        self.header.write_text('#define DISPLAY_VERSION "v1.2.0"\n')
        (self.source / "guides").mkdir()
        (self.source / "guides" / "example.md").write_text("Authoring source")
        for patcher in (
            patch.object(site, "SRC_DIR", self.source),
            patch.object(site, "OUT_DIR", self.output),
            patch.object(site, "VERSION_H", self.header),
        ):
            patcher.start()
            self.addCleanup(patcher.stop)

    def write_published_data(self) -> None:
        data = self.output / "data"
        data.mkdir(parents=True)
        (data / "species.json").write_text(json.dumps([{
            "id": 3, "constant": "SPECIES_VENUSAUR_MEGA", "dex": 3, "name": "Venusaur",
            "formLabel": "Venusaur Mega", "types": ["TYPE_GRASS", "TYPE_POISON"],
            "stats": {"hp": 80, "atk": 100, "def": 123, "spa": 122, "spd": 120, "spe": 80}, "bst": 625,
            "regularAbilities": ["ABILITY_THICK_FAT"], "hiddenAbilities": ["ABILITY_THICK_FAT"],
            "innates": ["ABILITY_SEED_SOWER"], "slug": "venusaur-mega",
        }]))
        (data / "abilities.json").write_text(json.dumps({
            "ABILITY_THICK_FAT": {"constant": "ABILITY_THICK_FAT", "name": "Thick Fat", "description": "Halves fire & ice damage.", "slug": "thick-fat"},
            "ABILITY_SEED_SOWER": {"constant": "ABILITY_SEED_SOWER", "name": "Seed Sower", "description": "Grassy terrain.", "slug": "seed-sower"},
        }))
        (data / "moves.json").write_text(json.dumps({
            "MOVE_EARTHQUAKE": {"id": 89, "constant": "MOVE_EARTHQUAKE", "name": "Earthquake", "type": "TYPE_GROUND",
                                "category": "DAMAGE_CATEGORY_PHYSICAL", "power": 100, "accuracy": 100, "pp": 10,
                                "description": "A powerful quake.", "slug": "earthquake"},
        }))
        (data / "machines.json").write_text(json.dumps([{
            "label": "TM26", "move": "MOVE_EARTHQUAKE", "moveName": "Earthquake", "type": "TYPE_GROUND",
            "category": "DAMAGE_CATEGORY_PHYSICAL", "power": 100, "accuracy": 100, "pp": 10,
            "description": "A powerful quake.", "location": "Victory Road", "slug": "tm26", "moveSlug": "earthquake",
        }]))
        (data / "items.json").write_text("[]")
        (data / "guides.json").write_text(json.dumps([{"slug": "example", "title": "Example", "summary": "An example guide"}]))

    def test_refresh_preserves_data_and_sprites_and_rewrites_routes(self) -> None:
        self.write_published_data()
        preserved = ["sprites/pokemon/bulbasaur.png", "guides/image.png"]
        for relative in preserved:
            path = self.output / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(b"existing data")
        species_json = (self.output / "data" / "species.json").read_bytes()

        site.refresh_static_site()

        for relative in preserved:
            self.assertEqual((self.output / relative).read_bytes(), b"existing data")
        self.assertEqual((self.output / "data" / "species.json").read_bytes(), species_json)
        app_version = site.content_hash([self.source / "assets" / "app.js"], self.source)
        data_version = site.data_version()

        detail = (self.output / "pokedex" / "venusaur-mega" / "index.html").read_text()
        self.assertIn('<base href="../../">', detail)
        self.assertIn(f'assets/app.js?v={app_version}"', detail)
        self.assertNotIn("v=stale", detail)
        self.assertIn(f'<meta name="docs-data-version" content="{data_version}">', detail)
        self.assertIn('<span class="header-version">v1.2.0</span>', detail)
        self.assertIn("<title>#3 Venusaur Mega · Pokédex · Soulgold Documentation</title>", detail)
        self.assertIn('<meta property="og:title" content="#3 Venusaur Mega · Pokédex">', detail)
        self.assertIn("Abilities: Thick Fat. Innates: Seed Sower.", detail)
        self.assertIn(f'href="data/species-details/venusaur-mega.json?v={data_version}"', detail)
        self.assertIn(f'href="data/species-meta.json?v={data_version}"', detail)

        move = (self.output / "moves" / "earthquake" / "index.html").read_text()
        self.assertIn(f'href="data/move-learners/earthquake.json?v={data_version}"', move)
        self.assertNotIn("species-details", move)
        machine = (self.output / "machines" / "tm26" / "index.html").read_text()
        self.assertIn("<title>TM26 Earthquake · TMs/HMs · Soulgold Documentation</title>", machine)
        self.assertIn(f'href="data/move-learners/earthquake.json?v={data_version}"', machine)
        ability = (self.output / "abilities" / "thick-fat" / "index.html").read_text()
        self.assertIn('content="Halves fire &amp; ice damage."', ability)

        guide_detail = (self.output / "guides" / "example" / "index.html").read_text()
        self.assertIn(f'href="data/guides.json?v={data_version}"', guide_detail)
        self.assertNotIn('href="data/species.json', guide_detail)
        for route in site.SECTION_ROUTES:
            section_html = (self.output / route / "index.html").read_text()
            self.assertIn('<base href="../">', section_html)
            self.assertIn('<span class="header-version">v1.2.0</span>', section_html)
            self.assertIn(f"<title>{site.SECTION_LABELS[route]} · Soulgold Documentation</title>", section_html)
            for filename in site.SECTION_PRELOADS[route]:
                self.assertIn(f'href="data/{filename}?v={data_version}"', section_html)
        root_html = (self.output / "index.html").read_text()
        self.assertIn('<base href="./">', root_html)
        self.assertIn("<title>Soulgold Documentation</title>", root_html)
        self.assertEqual((self.output / "version.json").read_text(), (self.source / "version.json").read_text())
        self.assertEqual(json.loads((self.output / "version.json").read_text()), {"latestVersion": "v1.2.0"})
        self.assertFalse((self.output / "guides" / "example.md").exists())

    def test_data_version_changes_with_data(self) -> None:
        self.write_published_data()
        before = site.data_version()
        (self.output / "data" / "romhack-docs.json").write_text("{}")
        self.assertEqual(site.data_version(), before)
        (self.output / "data" / "items.json").write_text('[{"name": "Potion"}]')
        self.assertNotEqual(site.data_version(), before)

    def test_full_build_uses_header_version(self) -> None:
        self.header.write_text('#define DISPLAY_VERSION "v1.2.1" // Release version\n')
        site.prepare_output_tree()
        self.assertEqual(json.loads((self.output / "version.json").read_text()), {"latestVersion": "v1.2.1"})
        self.assertEqual((self.output / "version.json").read_text(), (self.source / "version.json").read_text())
        site.write_pages({"species": [], "moves": {}, "abilities": {}, "tms": [], "items": [], "guides": []})
        self.assertIn('<span class="header-version">v1.2.1</span>', (self.output / "index.html").read_text())

    def test_missing_asset_reference_fails_the_build(self) -> None:
        (self.source / "assets" / "styles.css").unlink()
        with self.assertRaises(ValueError):
            site.read_site_template()


class FormLabelTests(unittest.TestCase):
    def test_form_labels(self) -> None:
        self.assertEqual(site.species_form_label("SPECIES_CHARIZARD_MEGA_X", "Charizard"), "Charizard X")
        self.assertEqual(site.species_form_label("SPECIES_VENUSAUR_MEGA", "Venusaur"), "Venusaur Mega")
        self.assertEqual(site.species_form_label("SPECIES_OGERPON_TEAL_TERA", "Ogerpon"), "Ogerpon (Teal Mask)")
        self.assertEqual(site.species_form_label("SPECIES_TATSUGIRI_CURLY_MEGA", "Tatsugiri"), "Tatsugiri (Curly Mega)")
        self.assertEqual(site.species_form_label("SPECIES_ZACIAN_CROWNED", "Zacian"), "Zacian (Crowned Sword)")
        self.assertEqual(site.species_form_label("SPECIES_PIKACHU", "Pikachu"), "Pikachu")


class MoveLearnerTests(unittest.TestCase):
    def test_one_file_per_move_lists_each_species_once(self) -> None:
        with tempfile.TemporaryDirectory() as directory, patch.object(site, "OUT_DIR", Path(directory)):
            payload = {
                "species": [
                    {"constant": "SPECIES_A", "levelUp": [{"level": 1, "move": "MOVE_X"}, {"level": 9, "move": "MOVE_X"}],
                     "tmhm": ["MOVE_X"], "tutors": [], "eggMoves": []},
                    {"constant": "SPECIES_B", "levelUp": [], "tmhm": ["MOVE_X"], "tutors": [], "eggMoves": ["MOVE_X"]},
                ],
                "moves": {
                    "MOVE_NONE": {"slug": "none"},
                    "MOVE_X": {"slug": "x"},
                    "MOVE_Y": {"slug": "y"},
                },
            }
            site.write_move_learners(payload)
            learner_dir = Path(directory) / "data" / "move-learners"
            self.assertEqual(json.loads((learner_dir / "x.json").read_text()), {
                "levelUp": ["SPECIES_A"],
                "tmhm": ["SPECIES_A", "SPECIES_B"],
                "eggMoves": ["SPECIES_B"],
            })
            self.assertEqual(json.loads((learner_dir / "y.json").read_text()), {})
            self.assertFalse((learner_dir / "none.json").exists())


if __name__ == "__main__":
    unittest.main()
