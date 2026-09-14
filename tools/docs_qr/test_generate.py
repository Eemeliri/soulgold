"""Checks for pinned QR destinations and generated integrity metadata."""

import re
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
from urllib.parse import urlencode
from zlib import crc32

import generate


class DocsQrGenerationTests(unittest.TestCase):
    def test_official_destinations_allow_version_updates(self):
        for version in ("v1.1.3", "v1.2.0-rc.1", "v1.2.0+build.2"):
            for path in ("/soulgold/", "/soulgold/guides/"):
                url = f"https://eemeliri.github.io{path}?{urlencode({'version': version})}"
                generate.validate_docs_url(url, version)

    def test_modified_destinations_are_rejected(self):
        for url in (
            "http://eemeliri.github.io/soulgold/?version=v1.1.3",
            "https://evil.example/soulgold/?version=v1.1.3",
            "https://eemeliri.github.io.evil.example/soulgold/?version=v1.1.3",
            "https://eemeliri.github.io@evil.example/soulgold/?version=v1.1.3",
            "https://user@eemeliri.github.io/soulgold/?version=v1.1.3",
            "https://eemeliri.github.io:443/soulgold/?version=v1.1.3",
            "https://eemeliri.github.io/other/?version=v1.1.3",
            "https://eemeliri.github.io/soulgold/guides/../other/?version=v1.1.3",
            "https://eemeliri.github.io/soulgold/?version=v1.1.3#other",
            "https://eemeliri.github.io/soulgold/?version=v1.1.3&next=https://evil.example",
            "https://eemeliri.github.io/soulgold/?version=v1.1.3&version=v1.1.4",
            "https://eemeliri.github.io/soulgold/?version=v1.1.4",
            "https://eemeliri.github.io/soulgold/",
            "\nhttps://eemeliri.github.io/soulgold/?version=v1.1.3",
        ):
            with self.subTest(url=url), self.assertRaises(ValueError):
                generate.validate_docs_url(url, "v1.1.3")

    def test_unofficial_generator_url_does_not_overwrite_existing_output(self):
        with tempfile.TemporaryDirectory() as directory:
            header = Path(directory) / "version.h"
            header.write_text('#define DISPLAY_VERSION "v1.1.3"\n')
            output = Path(directory) / "docs_qr.h"
            output.write_text("previous valid output")
            with patch.object(generate, "URLS", (generate.URLS[0], "https://evil.example/soulgold/")):
                with self.assertRaises(ValueError):
                    generate.generate(header, output)
            self.assertEqual(output.read_text(), "previous valid output")

    def test_generated_checksums_cover_both_packed_matrices_after_version_bumps(self):
        with tempfile.TemporaryDirectory() as directory:
            header = Path(directory) / "version.h"
            output = Path(directory) / "docs_qr.h"
            previous_checksums = None
            for version in ("v1.1.3", "v1.1.4"):
                header.write_text(f'#define DISPLAY_VERSION "{version}"\n')
                generate.generate(header, output)
                matrices, metadata = output.read_text().split("static const u32 sDocsQrChecksums[]")
                data = bytes(int(value, 16) for value in re.findall(r"0x([0-9A-F]{2})\b", matrices))
                checksums = [int(value, 16) for value in re.findall(r"0x([0-9A-F]{8})\b", metadata)]
                self.assertEqual(len(data), 2 * 33 * 5)
                self.assertEqual(checksums, [crc32(data[:165]), crc32(data[165:])])
                for base in generate.URLS:
                    self.assertIn(f"{base}?version={version}", matrices)
                if previous_checksums is not None:
                    self.assertTrue(all(a != b for a, b in zip(checksums, previous_checksums)))
                previous_checksums = checksums


if __name__ == "__main__":
    unittest.main()
