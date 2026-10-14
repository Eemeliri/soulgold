from __future__ import annotations

import hashlib
import json
import re
import shutil
from html import escape
from pathlib import Path

from .c_parser import strip_c_comments
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
from .paths import OUT_DIR, SRC_DIR, VERSION_H

SECTION_ROUTES = ("pokedex", "moves", "encounters", "machines", "items", "trainers", "abilities", "guides")

SITE_NAME = "Soulgold Documentation"
SITE_DESCRIPTION = "Pokédex, moves, encounters, items, trainers and guides for the Soulgold ROM hack."

SECTION_LABELS = {
    "pokedex": "Pokédex",
    "moves": "Movedex",
    "encounters": "Wild Encounters",
    "machines": "TMs/HMs",
    "items": "Items",
    "trainers": "Trainers",
    "abilities": "Abilities",
    "guides": "Guides",
}

SECTION_DESCRIPTIONS = {
    "pokedex": "Base stats, types, abilities, learnsets and locations for every Pokémon in Soulgold.",
    "moves": "Every move in with its type, category, power, accuracy, PP and priority.",
    "encounters": "Wild Pokémon in every map.",
    "machines": "Every TM and HM in alongside the move data and where to find them.",
    "items": "Notable items and where to find them.",
    "trainers": "Trainer parties with levels, abilities, moves and held items.",
    "abilities": "Every ability and which Pokémon gets them.",
    "guides": "Guides for Soulgold.",
}

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
    "moves": ("ui.json", "ability-index.json", "moves.json", "species.json"),
    "machines": ("ui.json", "machines.json", "species.json"),
    "items": ("items.json",),
    "abilities": ("abilities.json", "ability-usage.json"),
    "guides": ("guides.json",),
}

MOVE_LEARNER_FIELDS = ("levelUp", "tmhm", "tutors", "eggMoves")

META_DESCRIPTION_LIMIT = 300

ASSET_REFERENCE = re.compile(r'((?:href|src)=")(assets/[^"?#]+)(?:\?[^"]*)?(")')


def route_slug(constant: str, prefix: str = "") -> str:
    value = constant.removeprefix(prefix).lower()
    return re.sub(r"[^a-z0-9]+", "-", value).strip("-")


def species_form_label(constant: str, name: str) -> str:
    ogerpon = re.fullmatch(r"SPECIES_OGERPON_(TEAL|WELLSPRING|HEARTHFLAME|CORNERSTONE)(?:_TERA)?", constant)
    if ogerpon:
        return f"{name} ({ogerpon.group(1).capitalize()} Mask)"
    tatsugiri = re.fullmatch(r"SPECIES_TATSUGIRI_(CURLY|DROOPY|STRETCHY)(_MEGA)?", constant)
    if tatsugiri:
        return f"{name} ({tatsugiri.group(1).capitalize()}{' Mega' if tatsugiri.group(2) else ''})"
    if constant == "SPECIES_ZACIAN_CROWNED":
        return f"{name} (Crowned Sword)"
    if constant == "SPECIES_ZAMAZENTA_CROWNED":
        return f"{name} (Crowned Shield)"
    for suffix, label in (("_MEGA_X", "X"), ("_MEGA_Y", "Y"), ("_MEGA_Z", "Z"), ("_MEGA", "Mega"), ("_GMAX", "Mega"), ("_DMAX", "Mega")):
        if constant.endswith(suffix):
            return f"{name} {label}"
    return name


def prepare_output_tree() -> OutputPaths:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    for route in SECTION_ROUTES:
        route_dir = OUT_DIR / route
        if route_dir.exists():
            shutil.rmtree(route_dir)
    copy_static_sources()
    (OUT_DIR / ".nojekyll").write_text("", encoding="utf-8")
    (OUT_DIR / "data").mkdir(parents=True, exist_ok=True)
    return OutputPaths(
        sprite_dir=OUT_DIR / "sprites" / "pokemon",
        trainer_sprite_dir=OUT_DIR / "sprites" / "trainers",
        item_icon_dir=OUT_DIR / "sprites" / "items",
    )


def copy_static_sources() -> None:
    write_version_manifest()
    for item in SRC_DIR.rglob("*"):
        relative = item.relative_to(SRC_DIR)
        if relative.parts[0] == "guides" and (item.suffix == ".md" or item.name == ".gitkeep"):
            continue
        if relative.as_posix() in {"index.html", "party/index.html"}:
            continue
        dest = OUT_DIR / relative
        if item.is_dir():
            dest.mkdir(parents=True, exist_ok=True)
        else:
            shutil.copy2(item, dest)


def content_hash(paths: list[Path], root: Path) -> str:
    digest = hashlib.sha256()
    for path in sorted(paths):
        digest.update(path.relative_to(root).as_posix().encode("utf-8") + b"\0")
        digest.update(path.read_bytes())
    return digest.hexdigest()[:12]


def data_version() -> str:
    data_dir = OUT_DIR / "data"
    # Party dictionaries are immutable beta snapshots, independent of public docs.
    files = [path for path in data_dir.rglob("*.json")
             if path.name not in {"romhack-docs.json", "party-links.json"}
             and "party-export" not in path.relative_to(data_dir).parts]
    return content_hash(files, data_dir)


def version_asset_references(html: str) -> str:

    def replace(match: re.Match[str]) -> str:
        path = SRC_DIR / match.group(2)
        if not path.is_file():
            raise ValueError(f"docs/src references missing asset {match.group(2)}")
        return f"{match.group(1)}{match.group(2)}?v={content_hash([path], SRC_DIR)}{match.group(3)}"

    return ASSET_REFERENCE.sub(replace, html)


def read_site_template() -> str:
    template = (SRC_DIR / "index.html").read_text(encoding="utf-8")
    if '<base href="./">' not in template:
        raise ValueError('docs/src/index.html must contain <base href="./">')
    manifest = json.loads((SRC_DIR / "version.json").read_text(encoding="utf-8"))
    template = template.replace("{{LATEST_VERSION}}", escape(manifest["latestVersion"]))
    template = template.replace("{{DATA_VERSION}}", data_version())
    return version_asset_references(template)


def write_version_manifest() -> None:
    header = strip_c_comments(VERSION_H.read_text(encoding="utf-8"))
    values = re.findall(r'^[ \t]*#[ \t]*define[ \t]+DISPLAY_VERSION[ \t]+("[^"\r\n]+")[ \t]*$', header, re.MULTILINE)
    if len(values) != 1:
        raise ValueError(f"{VERSION_H}: expected one quoted DISPLAY_VERSION definition")
    manifest = {"latestVersion": json.loads(values[0])}
    (SRC_DIR / "version.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")


def refresh_static_site() -> None:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    copy_static_sources()
    write_pages(load_published_records())


def load_published_records() -> dict[str, object]:
    data_dir = OUT_DIR / "data"

    def read(name: str, default: object) -> object:
        path = data_dir / name
        return json.loads(path.read_text(encoding="utf-8")) if path.exists() else default

    return {
        "species": read("species.json", []),
        "moves": read("moves.json", {}),
        "abilities": read("abilities.json", {}),
        "tms": read("machines.json", []),
        "items": read("items.json", []),
        "guides": read("guides.json", []),
    }


def constant_label(value: str, prefix: str) -> str:
    return value.removeprefix(prefix).replace("_", " ").title()


def plain_text(value: object) -> str:
    return " ".join(str(value or "").split())


def metric(value: object) -> str:
    return "—" if str(value) in {"", "0", "None"} else str(value)


def move_summary(record: dict) -> str:
    return " · ".join((
        constant_label(record.get("type") or "", "TYPE_"),
        constant_label(record.get("category") or "", "DAMAGE_CATEGORY_"),
        f"Power {metric(record.get('power'))}",
        f"Accuracy {metric(record.get('accuracy'))}",
        f"PP {metric(record.get('pp'))}",
    ))


def species_description(mon: dict, ability_names: dict[str, str]) -> str:
    def name(constant: str) -> str:
        return ability_names.get(constant) or constant_label(constant, "ABILITY_")

    def unique(constants: list[str] | None) -> list[str]:
        return [c for c in dict.fromkeys(constants or []) if c and c != "ABILITY_NONE"]

    regular = unique(mon.get("regularAbilities"))
    hidden = [c for c in unique(mon.get("hiddenAbilities")) if c not in regular]
    abilities = [name(c) for c in regular] + [f"{name(c)} (hidden)" for c in hidden]
    innates = [name(c) for c in unique(mon.get("innates"))]
    stats = mon.get("stats") or {}
    parts = [
        " / ".join(constant_label(t, "TYPE_") for t in dict.fromkeys(mon.get("types") or []) if t) + ".",
        "Base stats " + "/".join(str(stats.get(key, "?")) for key in ("hp", "atk", "def", "spa", "spd", "spe")) + f" (BST {mon.get('bst', '?')}).",
    ]
    if abilities:
        parts.append(f"Abilities: {', '.join(abilities)}.")
    if innates:
        parts.append(f"Innates: {', '.join(innates)}.")
    return " ".join(parts)


def detail_page(route: str, record: dict, ability_names: dict[str, str]) -> tuple[str, str, tuple[str, ...]]:
    if route == "pokedex":
        label = record.get("formLabel") or record["name"]
        heading = f"#{record.get('dex') or record.get('id')} {label}"
        return heading, species_description(record, ability_names), (f"species-details/{record['slug']}.json",)
    if route == "moves":
        heading = f"#{record.get('id') or '-'} {record['name']}"
        description = f"{move_summary(record)}. {plain_text(record.get('description'))}"
        return heading, description, (f"move-learners/{record['slug']}.json",)
    if route == "machines":
        heading = f"{record['label']} {record['moveName']}"
        description = f"{move_summary(record)}. {plain_text(record.get('description'))}"
        if record.get("location"):
            description += f" Location: {plain_text(record['location'])}."
        return heading, description, (f"move-learners/{route_slug(record['move'], 'MOVE_')}.json",)
    if route == "items":
        description = plain_text(record.get("description"))
        if record.get("location"):
            description += f" Location: {plain_text(record['location'])}."
        return record["name"], description, ()
    if route == "abilities":
        return record["name"], plain_text(record.get("description")), ()
    if route == "guides":
        return record["title"], plain_text(record.get("summary")), ()
    raise ValueError(f"Unknown detail route {route}")


def truncate(text: str, limit: int = META_DESCRIPTION_LIMIT) -> str:
    text = text.strip()
    if len(text) <= limit:
        return text
    return text[: limit - 1].rsplit(" ", 1)[0].rstrip(" ,.;:") + "…"


def replace_once(html: str, pattern: str, replacement: str) -> str:
    result, count = re.subn(pattern, lambda _: replacement, html, count=1)
    if count != 1:
        raise ValueError(f"docs/src/index.html is missing {pattern}")
    return result


def render_page(
    template: str,
    *,
    depth: int,
    title: str,
    description: str,
    preloads: tuple[str, ...],
    version: str,
) -> str:
    html = template.replace('<base href="./">', f'<base href="{"../" * depth or "./"}">', 1)
    og_title = title.removesuffix(f" · {SITE_NAME}")
    description = escape(truncate(description))
    html = replace_once(html, r"<title>[^<]*</title>", f"<title>{escape(title)}</title>")
    html = replace_once(html, r'<meta name="description" content="[^"]*">', f'<meta name="description" content="{description}">')
    html = replace_once(html, r'<meta property="og:title" content="[^"]*">', f'<meta property="og:title" content="{escape(og_title)}">')
    html = replace_once(html, r'<meta property="og:description" content="[^"]*">', f'<meta property="og:description" content="{description}">')
    links = "".join(
        f'    <link rel="preload" href="data/{filename}?v={version}" as="fetch" crossorigin="anonymous">\n'
        for filename in preloads
    )
    return html.replace("  </head>", f"{links}  </head>", 1)


def write_party_links(records: dict[str, object]) -> None:
    data_dir = OUT_DIR / "data"
    data_dir.mkdir(parents=True, exist_ok=True)
    links = {
        "species": {
            row["constant"]: [row["slug"], row.get("sprite") or ""]
            for row in records["species"] if row.get("constant") and row.get("slug")
        },
        "items": {
            row["constant"]: [row["slug"], row.get("itemIcon") or ""]
            for row in records["items"] if row.get("constant") and row.get("slug")
        },
    }
    (data_dir / "party-links.json").write_text(json.dumps(links, sort_keys=True, separators=(",", ":")), encoding="utf-8")


def write_party_page(version: str) -> None:
    template = SRC_DIR / "party" / "index.html"
    if not template.is_file():
        return
    html = version_asset_references(template.read_text(encoding="utf-8").replace("{{DATA_VERSION}}", version))
    (OUT_DIR / "party").mkdir(parents=True, exist_ok=True)
    (OUT_DIR / "party" / "index.html").write_text(html, encoding="utf-8")


def write_pages(records: dict[str, object]) -> None:
    write_party_links(records)
    template = read_site_template()
    version = data_version()
    write_party_page(content_hash([OUT_DIR / "data" / "party-links.json"], OUT_DIR))
    (OUT_DIR / "index.html").write_text(
        render_page(
            template,
            depth=0,
            title=SITE_NAME,
            description=SITE_DESCRIPTION,
            preloads=SECTION_PRELOADS["pokedex"],
            version=version,
        ),
        encoding="utf-8",
    )
    for route in SECTION_ROUTES:
        route_dir = OUT_DIR / route
        route_dir.mkdir(parents=True, exist_ok=True)
        (route_dir / "index.html").write_text(
            render_page(
                template,
                depth=1,
                title=f"{SECTION_LABELS[route]} · {SITE_NAME}",
                description=SECTION_DESCRIPTIONS[route],
                preloads=SECTION_PRELOADS[route],
                version=version,
            ),
            encoding="utf-8",
        )

    abilities = records["abilities"]
    ability_names = {key: value.get("name", "") for key, value in abilities.items()}
    route_records = {
        "pokedex": records["species"],
        "moves": records["moves"].values(),
        "machines": records["tms"],
        "items": records["items"],
        "abilities": abilities.values(),
        "guides": records["guides"],
    }
    for route, entries in route_records.items():
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
            heading, description, extra_preloads = detail_page(route, entry, ability_names)
            route_dir = OUT_DIR / route / slug
            route_dir.mkdir(parents=True, exist_ok=True)
            (route_dir / "index.html").write_text(
                render_page(
                    template,
                    depth=2,
                    title=f"{heading} · {SECTION_LABELS[route]} · {SITE_NAME}",
                    description=description,
                    preloads=DETAIL_PRELOADS[route] + extra_preloads,
                    version=version,
                ),
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
                **({"formLabel": label} if (label := species_form_label(row.constant, row.name)) != row.name else {}),
                "sprite": row.sprite,
                "shinySprite": row.shiny_sprite,
                "levelUp": row.level_up,
                "tmhm": row.tmhm,
                "tutors": row.tutors,
                "eggMoves": row.egg_moves,
                "evolutions": row.evolutions,
                "locations": row.locations,
                "acquisitionPaths": row.acquisition_paths,
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
        "tms": [
            {**row, "slug": row["label"].lower(), "moveSlug": route_slug(row["move"], "MOVE_")}
            for row in tms
        ],
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
    summary_fields = {
        "id", "constant", "dex", "name", "formLabel", "types", "stats", "bst",
        "categories",
        "abilities", "regularAbilities", "hiddenAbilities", "innates",
        "sprite", "slug",
    }
    write_json("species.json", [
        {key: value for key, value in row.items() if key in summary_fields}
        for row in payload["species"]
    ])
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
    write_move_learners(payload)
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
    for retired in ("common.json", "species-details.json"):
        (data_dir / retired).unlink(missing_ok=True)
    write_pages(payload)


def write_move_learners(payload: DocsPayload) -> None:
    learners: dict[str, dict[str, list[str]]] = {}
    for row in payload["species"]:
        for field in MOVE_LEARNER_FIELDS:
            for entry in row[field] or []:
                move = entry if isinstance(entry, str) else entry["move"]
                species = learners.setdefault(move, {}).setdefault(field, [])
                if not species or species[-1] != row["constant"]:
                    species.append(row["constant"])
    learner_dir = OUT_DIR / "data" / "move-learners"
    if learner_dir.exists():
        shutil.rmtree(learner_dir)
    learner_dir.mkdir(parents=True)
    for constant, move in payload["moves"].items():
        if constant == "MOVE_NONE":
            continue
        methods = learners.get(constant, {})
        (learner_dir / f'{move["slug"]}.json').write_text(
            json.dumps({field: methods[field] for field in MOVE_LEARNER_FIELDS if field in methods}, separators=(",", ":")),
            encoding="utf-8",
        )
