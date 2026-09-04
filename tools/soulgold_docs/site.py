"""Static site output preparation and JSON payload assembly."""

from __future__ import annotations

import json
import re
import shutil

from .models import (
    AbilityUsage,
    DocsPayload,
    GuideRow,
    ImportantItemRow,
    MegaEvolutionRow,
    NamedRecord,
    OutputPaths,
    SpeciesRow,
    TMRow,
    TrainerRow,
    WildEncounterRow,
)
from .paths import OUT_DIR, SRC_DIR

SECTION_ROUTES = ("pokedex", "moves", "encounters", "machines", "items", "trainers", "abilities", "guides")

SECTION_PRELOADS = {
    "pokedex": ("ui.json", "ability-index.json", "species.json"),
    "moves": ("ui.json", "ability-index.json", "moves.json"),
    "encounters": ("encounters.json",),
    "machines": ("ui.json", "machines.json"),
    "items": ("items.json",),
    "trainers": ("ability-index.json", "move-index.json", "trainers.json"),
    "abilities": ("abilities.json",),
    "guides": ("guides.json",),
}

DETAIL_PRELOADS = {
    "pokedex": ("ui.json", "ability-index.json", "species-meta.json", "species.json", "moves.json"),
    "moves": ("ui.json", "ability-index.json", "moves.json", "species.json", "species-details.json"),
    "machines": ("ui.json", "machines.json", "species.json", "species-details.json"),
    "items": ("items.json",),
    "abilities": ("abilities.json", "ability-usage.json"),
    "guides": ("guides.json",),
}


def route_slug(constant: str, prefix: str = "") -> str:
    """Return a stable, URL-safe slug derived from a unique game constant."""
    value = constant.removeprefix(prefix).lower()
    return re.sub(r"[^a-z0-9]+", "-", value).strip("-")


def prepare_output_tree() -> OutputPaths:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    # These directories are generated entry points. Remove them first so
    # deleted or renamed records cannot leave stale shareable URLs behind.
    for route in SECTION_ROUTES:
        route_dir = OUT_DIR / route
        if route_dir.exists():
            shutil.rmtree(route_dir)
    for item in SRC_DIR.rglob("*"):
        relative = item.relative_to(SRC_DIR)
        # Guide Markdown is authoring source embedded into the JSON payload.
        # Only its attached assets need to be copied to the published site.
        if relative.parts[0] == "guides" and (item.suffix == ".md" or item.name == ".gitkeep"):
            continue
        dest = OUT_DIR / relative
        if item.is_dir():
            dest.mkdir(parents=True, exist_ok=True)
        else:
            shutil.copy2(item, dest)
    write_section_routes()
    (OUT_DIR / ".nojekyll").write_text("", encoding="utf-8")
    (OUT_DIR / "data").mkdir(parents=True, exist_ok=True)
    return OutputPaths(
        sprite_dir=OUT_DIR / "sprites" / "pokemon",
        trainer_sprite_dir=OUT_DIR / "sprites" / "trainers",
        item_icon_dir=OUT_DIR / "sprites" / "items",
    )


def add_data_preloads(index_html: str, filenames: tuple[str, ...]) -> str:
    """Start route-specific JSON downloads while the main script is loading."""
    version_match = re.search(r'assets/app\.js\?v=([^"\']+)', index_html)
    version = f"?v={version_match.group(1)}" if version_match else ""
    links = "\n".join(
        f'    <link rel="preload" href="data/{filename}{version}" as="fetch" crossorigin="anonymous">'
        for filename in filenames
    )
    return index_html.replace("  </head>", f"{links}\n  </head>", 1)


def write_section_routes() -> None:
    """Create static entry points so section URLs work without server rewrites."""
    index_html = (OUT_DIR / "index.html").read_text(encoding="utf-8")
    route_html = index_html.replace('<base href="./">', '<base href="../">', 1)
    if route_html == index_html:
        raise ValueError('docs/src/index.html must contain <base href="./">')
    (OUT_DIR / "index.html").write_text(
        add_data_preloads(index_html, SECTION_PRELOADS["pokedex"]),
        encoding="utf-8",
    )
    for route in SECTION_ROUTES:
        route_dir = OUT_DIR / route
        route_dir.mkdir(parents=True, exist_ok=True)
        (route_dir / "index.html").write_text(
            add_data_preloads(route_html, SECTION_PRELOADS[route]),
            encoding="utf-8",
        )


def write_detail_routes(payload: DocsPayload) -> None:
    """Create static entry points for every shareable record URL."""
    # Read the source template so the Pokédex preloads added to docs/index.html
    # are not inherited by every detail route.
    index_html = (SRC_DIR / "index.html").read_text(encoding="utf-8")
    detail_html = index_html.replace('<base href="./">', '<base href="../../">', 1)
    if detail_html == index_html:
        raise ValueError('docs/src/index.html must contain <base href="./">')

    records = {
        "pokedex": payload["species"],
        "moves": payload["moves"].values(),
        "machines": payload["tms"],
        "items": payload["items"],
        "abilities": payload["abilities"].values(),
        "guides": payload["guides"],
    }
    for route, entries in records.items():
        seen_slugs: dict[str, str] = {}
        for entry in entries:
            if entry.get("constant") in {"MOVE_NONE", "ABILITY_NONE"}:
                continue
            slug = entry.get("slug")
            if not slug:
                continue
            identity = entry.get("constant") or entry.get("label") or entry.get("title") or slug
            if slug in seen_slugs:
                raise ValueError(f"Duplicate {route} route slug '{slug}': {seen_slugs[slug]} and {identity}")
            seen_slugs[slug] = identity
            route_dir = OUT_DIR / route / slug
            route_dir.mkdir(parents=True, exist_ok=True)
            preloads = list(DETAIL_PRELOADS[route])
            if route == "pokedex":
                preloads.append(f"species-details/{slug}.json")
            (route_dir / "index.html").write_text(
                add_data_preloads(detail_html, tuple(preloads)),
                encoding="utf-8",
            )


def build_docs_payload(
    visible_species: list[SpeciesRow],
    dedicated_tutors: dict[str, str],
    moves: dict[str, NamedRecord],
    abilities: dict[str, NamedRecord],
    ability_usage: AbilityUsage,
    tms: list[TMRow],
    important_items: list[ImportantItemRow],
    encounters: list[WildEncounterRow],
    trainers: list[TrainerRow],
    type_icons: dict[str, str],
    category_icons: dict[str, str],
    shiny_toggle_icon: str | None,
    mega_evolutions: list[MegaEvolutionRow],
    guides: list[GuideRow],
) -> DocsPayload:
    payload: DocsPayload = {
        "meta": {"generatedFrom": "tools/soulgold_docs/build_docs.py"},
        "dedicatedTutors": dedicated_tutors,
        "species": [
            {
                "id": row.id,
                "constant": row.constant,
                "dex": row.display_dex,
                "name": row.name,
                "types": row.types,
                "stats": row.stats,
                "evYield": row.ev_yield,
                "eggGroups": row.egg_groups,
                "categories": row.categories,
                "bst": sum(row.stats.values()),
                "abilities": row.abilities,
                "regularAbilities": row.regular_abilities,
                "hiddenAbilities": row.hidden_abilities,
                "innates": row.innates,
                "sprite": row.sprite,
                "shinySprite": row.shiny_sprite,
                "levelUp": row.level_up,
                "tmhm": row.tmhm,
                "tutors": row.tutors,
                "eggMoves": row.egg_moves,
                "evolutions": row.evolutions,
                "locations": row.locations,
                "heldItems": row.held_items,
                "slug": route_slug(row.constant, "SPECIES_"),
            }
            for row in visible_species
        ],
        "moves": {
            key: {**value, "slug": route_slug(key, "MOVE_")}
            for key, value in moves.items()
        },
        "abilities": {
            key: {
                **value,
                "slug": route_slug(key, "ABILITY_"),
                "usage": ability_usage.get(key, {"base": [], "innate": []}),
            }
            for key, value in abilities.items()
        },
        "tms": [{**row, "slug": row["label"].lower()} for row in tms],
        "items": [
            {**row, "slug": route_slug(row["constant"], "ITEM_")}
            for row in important_items
        ],
        "encounters": encounters,
        "trainers": trainers,
        "typeIcons": type_icons,
        "categoryIcons": category_icons,
        "uiIcons": {"shiny": shiny_toggle_icon} if shiny_toggle_icon else {},
        "megaEvolutions": mega_evolutions,
        "guides": guides,
    }
    return payload


def write_docs_payload(payload: DocsPayload) -> None:
    data_dir = OUT_DIR / "data"

    def write_json(name: str, value: object, *, pretty: bool = False) -> None:
        (data_dir / name).write_text(
            json.dumps(value, indent=2 if pretty else None, separators=None if pretty else (",", ":")),
            encoding="utf-8",
        )

    # Keep the full payload for downstream tooling while the website itself
    # loads compact, section-specific files on demand.
    write_json("romhack-docs.json", payload, pretty=True)
    write_json("ui.json", {
        "typeIcons": payload["typeIcons"],
        "categoryIcons": payload["categoryIcons"],
        "uiIcons": payload["uiIcons"],
    })
    write_json("move-index.json", {
        key: {field: value for field, value in move.items() if field in {"name", "slug"}}
        for key, move in payload["moves"].items()
    })
    write_json("ability-index.json", {
        key: {field: value for field, value in ability.items() if field in {"name", "slug"}}
        for key, ability in payload["abilities"].items()
    })
    write_json("moves.json", payload["moves"])
    write_json("abilities.json", {
        key: {
            **{field: value for field, value in ability.items() if field != "usage"},
            "usageCounts": {
                "base": len(ability["usage"]["base"]),
                "innate": len(ability["usage"]["innate"]),
            },
        }
        for key, ability in payload["abilities"].items()
    })
    write_json("species-meta.json", {
        "dedicatedTutors": payload["dedicatedTutors"],
        "megaEvolutions": payload["megaEvolutions"],
        "speciesEvolutions": {
            row["constant"]: row["evolutions"]
            for row in payload["species"]
            if row["evolutions"]
        },
    })
    write_json("common.json", {
        "meta": payload["meta"],
        "dedicatedTutors": payload["dedicatedTutors"],
        "moves": payload["moves"],
        "abilities": {
            key: {field: value for field, value in ability.items() if field != "usage"}
            for key, ability in payload["abilities"].items()
        },
        "typeIcons": payload["typeIcons"],
        "categoryIcons": payload["categoryIcons"],
        "uiIcons": payload["uiIcons"],
        "megaEvolutions": payload["megaEvolutions"],
    })
    summary_fields = {
        "id", "constant", "dex", "name", "types", "stats", "bst",
        "categories",
        "abilities", "regularAbilities", "hiddenAbilities", "innates",
        "sprite", "slug",
    }
    write_json("species.json", [
        {key: value for key, value in row.items() if key in summary_fields}
        for row in payload["species"]
    ])
    write_json("species-details.json", {
        row["constant"]: {key: value for key, value in row.items() if key not in summary_fields}
        for row in payload["species"]
    })
    species_detail_dir = data_dir / "species-details"
    if species_detail_dir.exists():
        shutil.rmtree(species_detail_dir)
    species_detail_dir.mkdir(parents=True)
    for row in payload["species"]:
        (species_detail_dir / f'{row["slug"]}.json').write_text(
            json.dumps(
                {key: value for key, value in row.items() if key not in summary_fields},
                separators=(",", ":"),
            ),
            encoding="utf-8",
        )
    write_json("ability-usage.json", {
        key: ability["usage"]
        for key, ability in payload["abilities"].items()
    })
    for name, key in (
        ("encounters.json", "encounters"),
        ("machines.json", "tms"),
        ("items.json", "items"),
        ("trainers.json", "trainers"),
        ("guides.json", "guides"),
    ):
        write_json(name, payload[key])
    write_detail_routes(payload)
