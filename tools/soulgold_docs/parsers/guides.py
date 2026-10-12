from __future__ import annotations

import re
from pathlib import Path
from urllib.parse import unquote

from ..models import GuideRow
from ..paths import GUIDES_DIR, SRC_DIR


FRONT_MATTER_BOUNDARY = "---"
IMAGE_SIZES = {"small", "medium", "large"}


def _front_matter(text: str) -> tuple[dict[str, str], str]:
    lines = text.splitlines()
    if not lines or lines[0].strip() != FRONT_MATTER_BOUNDARY:
        return {}, text.strip()

    metadata: dict[str, str] = {}
    end = next(
        (index for index, line in enumerate(lines[1:], start=1) if line.strip() == FRONT_MATTER_BOUNDARY),
        None,
    )
    if end is None:
        return {}, text.strip()

    for line in lines[1:end]:
        key, separator, value = line.partition(":")
        if separator:
            metadata[key.strip().lower()] = value.strip().strip('"\'')
    return metadata, "\n".join(lines[end + 1:]).strip()


def _title_from_content(content: str, fallback: str) -> tuple[str, str]:
    lines = content.splitlines()
    for index, line in enumerate(lines):
        match = re.fullmatch(r"#\s+(.+?)\s*", line)
        if not match:
            continue
        title = match.group(1).strip()
        del lines[index]
        return title, "\n".join(lines).strip()
    return fallback, content


def _plain_summary(content: str) -> str:
    for block in re.split(r"\n\s*\n", content):
        line = " ".join(part.strip() for part in block.splitlines()).strip()
        if not line or line.startswith(("#", "!", "```", "- ", "* ", "> ")) or line.lower().startswith("[spoiler"):
            continue
        line = re.sub(r"!?\[([^]]+)]\([^)]+\)", r"\1", line)
        line = re.sub(r"[*_`~]", "", line)
        return line[:220]
    return ""


def _slug(path: Path) -> str:
    return re.sub(r"[^a-z0-9]+", "-", path.stem.lower()).strip("-")


def _normalized_slug(value: str) -> str:
    return re.sub(r"[^a-z0-9]+", "-", value.lower()).strip("-")


def _local_markdown_targets(content: str) -> list[tuple[bool, str]]:
    pattern = re.compile(r"(!?)\[[^]]*]\((?:<([^>]+)>|([^\s)]+))(?:\s+\"[^\"]*\")?\)")
    return [(bool(match.group(1)), match.group(2) or match.group(3)) for match in pattern.finditer(content)]


def _validate_image_sizes(path: Path, content: str) -> None:
    pattern = re.compile(r"!\[[^]]*]\([^)]+\)\{([^{}]+)\}")
    for match in pattern.finditer(content):
        size = match.group(1).strip().lower()
        if size not in IMAGE_SIZES:
            choices = ", ".join(sorted(IMAGE_SIZES))
            raise ValueError(f"Unknown guide image size '{size}' in {path}; use one of: {choices}")


def _validate_spoilers(path: Path, content: str) -> None:
    open_line: int | None = None
    in_code = False
    for line_number, line in enumerate(content.splitlines(), start=1):
        stripped = line.strip()
        if stripped.startswith("```"):
            in_code = not in_code
            continue
        if in_code:
            continue
        if re.fullmatch(r"\[spoiler(?:=[^\]]+)?\]", stripped, re.I):
            if open_line is not None:
                raise ValueError(f"Nested spoiler in {path}:{line_number}; close the spoiler opened on line {open_line} first")
            open_line = line_number
        elif re.fullmatch(r"\[/spoiler\]", stripped, re.I):
            if open_line is None:
                raise ValueError(f"Closing spoiler without an opening tag in {path}:{line_number}")
            open_line = None
    if open_line is not None:
        raise ValueError(f"Unclosed spoiler in {path}:{open_line}; add [/spoiler]")


def _validate_local_targets(path: Path, content: str, guide_paths: set[Path]) -> None:
    guides_root = GUIDES_DIR.resolve()
    for is_image, raw_target in _local_markdown_targets(content):
        target = raw_target.split("#", 1)[0].split("?", 1)[0]
        if not target or target.startswith(("#", "/")) or re.match(r"^[a-z][a-z0-9+.-]*:", target, re.I):
            continue
        resolved = (path.parent / unquote(target)).resolve()
        if not resolved.is_relative_to(guides_root):
            raise ValueError(f"Guide link escapes docs/src/guides: {path}: {raw_target}")
        if is_image and (not resolved.is_file() or resolved.suffix.lower() == ".md"):
            raise ValueError(f"Missing guide image: {path}: {raw_target}")
        if not is_image and resolved.suffix.lower() == ".md" and resolved not in guide_paths:
            raise ValueError(f"Guide links to an unpublished Markdown file: {path}: {raw_target}")
        if not is_image and resolved.suffix.lower() != ".md" and not resolved.exists():
            raise ValueError(f"Missing guide attachment: {path}: {raw_target}")


def parse_guides() -> list[GuideRow]:
    if not GUIDES_DIR.exists():
        return []

    guide_paths = {
        path.resolve()
        for path in GUIDES_DIR.rglob("*.md")
        if path.name.lower() != "readme.md" and not path.name.startswith("_")
    }
    guides: list[GuideRow] = []
    slugs: dict[str, Path] = {}
    for path in sorted(guide_paths):

        metadata, content = _front_matter(path.read_text(encoding="utf-8"))
        fallback_title = path.stem.replace("-", " ").replace("_", " ").title()
        content_title, content = _title_from_content(content, fallback_title)
        title = metadata.get("title") or content_title
        try:
            order = int(metadata.get("order", "1000"))
        except ValueError:
            order = 1000

        slug = _normalized_slug(metadata.get("slug") or _slug(path))
        if not slug:
            raise ValueError(f"Guide has an empty slug: {path}")
        if slug in slugs:
            raise ValueError(f"Duplicate guide slug '{slug}': {slugs[slug]} and {path}")
        slugs[slug] = path
        _validate_image_sizes(path, content)
        _validate_spoilers(path, content)
        _validate_local_targets(path, content, guide_paths)

        guides.append({
            "slug": slug,
            "title": title,
            "summary": metadata.get("summary") or _plain_summary(content),
            "category": metadata.get("category") or "Guide",
            "order": order,
            "source": path.relative_to(SRC_DIR).as_posix(),
            "content": content,
        })

    return sorted(guides, key=lambda guide: (guide["order"], guide["title"].casefold()))
