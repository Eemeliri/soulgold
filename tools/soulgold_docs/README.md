# Soulgold documentation website

Edit the website in `docs/src/`. The published static files live in `docs/`.

Refresh the UI, release manifest and existing page shells without regenerating
game data or sprites:

```sh
python3 tools/soulgold_docs/build_docs.py --static-only
```

Run without `--static-only` when game data or guide Markdown changes; that also
creates/removes detail routes to match the current records.

Both build modes read `DISPLAY_VERSION` from `include/config/version.h` and
generate `docs/src/version.json` and its published copy, `docs/version.json`.
Update the header when bumping a release; manual edits to either JSON file are
overwritten on the next docs build.

## ROM update notice

The in-game QR codes already include the installed ROM version, for example:

- `https://eemeliri.github.io/soulgold/?version=v1.1.2`
- `https://eemeliri.github.io/soulgold/guides/?version=v1.1.2`

The website compares that version with the generated `version.json`. When it is
older, a dismissible toast directs the player to
`https://www.hackdex.app/hack/soulgold` and warns about other download sites.
The download destination is fixed in `docs/src/assets/version-check.mjs`;
query parameters and the release manifest cannot supply a different link.
Version strings follow [Semantic Versioning precedence](https://semver.org/#spec-item-11),
with an optional leading `v`. Invalid versions are ignored. The comparison does
not authenticate the ROM or check the ROM file itself.

The version must be present as a single valid `version` parameter in the current
URL. Visits without it never fetch release data or show an update notice, even
after scanning a QR code earlier in the same tab. Navigating to a URL without the
parameter removes any visible notice and cancels a pending check.

Dismissal is remembered for the current browser tab's session, so reloading the
same versioned link does not repeat a dismissed notice. A new version pair can
show a new notice. Blocked storage still allows a notice, but cannot remember a
dismissal. A failed/offline release request leaves the docs usable.

When a release is available on Hackdex:

1. Set `DISPLAY_VERSION` in `include/config/version.h` to that published version.
2. Run the static refresh command above and publish the updated website files.

The header is the shared version source for the ROM, its QR codes and the website.
Publishing the generated website advertises that header version as the latest
release. There is no Hackdex scraping, emulator integration, or automatic
publishing step.

The website changes live under `docs/` and `tools/soulgold_docs/` and can be
committed separately from the ROM/QR implementation.

Checks:

```sh
node --test tools/soulgold_docs/tests/version-check.test.mjs
python3 -m unittest tools.soulgold_docs.tests.test_site
```
