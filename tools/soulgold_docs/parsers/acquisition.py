from __future__ import annotations

from dataclasses import dataclass
import re

from ..c_parser import parse_define_constants, preprocess_source, read, strip_c_comments
from ..models import AcquisitionPath, AcquisitionStep, ItemRecord, SpeciesRow
from ..paths import REPO_ROOT, SPECIES_H
from .items import item_display_name


@dataclass(frozen=True)
class BreedingRules:
    incense_required: bool
    mixed_gender_offspring: bool
    scatterbug: str
    incense_babies: dict[str, tuple[str, str]]


def parse_breeding_rules() -> BreedingRules:
    text = preprocess_source(
        '#include "global.h"\n'
        '#if P_INCENSE_BREEDING < GEN_9\nDOCS_INCENSE\n#endif\n'
        '#if P_NIDORAN_M_DITTO_BREED >= GEN_5\nDOCS_MIXED_GENDER\n#endif\n'
        'DOCS_SCATTERBUG P_SCATTERBUG_LINE_FORM_BREED\n'
    )
    _, by_id = parse_define_constants(SPECIES_H, "SPECIES_")
    scatterbug = re.search(r"DOCS_SCATTERBUG\s+(\d+)", text)
    if not scatterbug:
        raise ValueError("Could not read the configured Scatterbug offspring")
    daycare = strip_c_comments(read(REPO_ROOT / "src/daycare.c"))
    table = re.search(r"sIncenseBabyTable\[\]\s*=\s*\{(.*?)\};", daycare, re.DOTALL)
    if not table:
        raise ValueError("Could not read the daycare incense table")
    babies = {
        baby: (regular, item)
        for regular, item, baby in re.findall(
            r"\{\s*(SPECIES_\w+)\s*,\s*(ITEM_\w+)\s*,\s*(SPECIES_\w+)\s*\}",
            table.group(1),
        )
    }
    return BreedingRules(
        "DOCS_INCENSE" in text,
        "DOCS_MIXED_GENDER" in text,
        by_id[int(scatterbug.group(1))],
        babies,
    )


def egg_species(constant: str, parents: dict[str, str]) -> str | None:
    seen = set()
    for _ in range(5):
        if constant not in parents:
            return constant
        if constant in seen:
            return None
        seen.add(constant)
        constant = parents[constant]
    return constant if constant not in seen else None


def breeding_steps(
    species: list[SpeciesRow], rules: BreedingRules, items: dict[str, ItemRecord],
) -> list[AcquisitionStep]:
    by_constant = {row.constant: row for row in species}
    parents: dict[str, str] = {}
    for row in sorted(species, key=lambda row: row.id):
        for edge in row.evolutions:
            parents.setdefault(edge["target"], row.constant)

    steps: list[AcquisitionStep] = []
    for row in species:
        if not row.dex_visible or "mega" in row.categories or not row.egg_groups:
            continue
        if set(row.egg_groups) & {"EGG_GROUP_NO_EGGS_DISCOVERED", "EGG_GROUP_DITTO"}:
            continue
        baby = egg_species(row.constant, parents)
        if baby is None or baby not in by_constant:
            continue

        offspring = [(baby, "")]
        if "regional" in by_constant[baby].categories:
            offspring = [(baby, "Have the parent hold an Everstone to preserve the regional form.")]
            native = next((candidate.constant for candidate in sorted(species, key=lambda s: s.id)
                           if candidate.nat_dex == by_constant[baby].nat_dex
                           and "regional" not in candidate.categories
                           and candidate.dex_visible and "mega" not in candidate.categories), None)
            if native:
                offspring.append((native, "Breed in Johto without an Everstone on either parent."))

        for target, requirement in offspring:
            targets = [target]
            if target in {"SPECIES_NIDORAN_F", "SPECIES_ILLUMISE"}:
                targets.append({"SPECIES_NIDORAN_F": "SPECIES_NIDORAN_M", "SPECIES_ILLUMISE": "SPECIES_VOLBEAT"}[target])
            elif rules.mixed_gender_offspring and target in {"SPECIES_NIDORAN_M", "SPECIES_VOLBEAT"}:
                targets.append({"SPECIES_NIDORAN_M": "SPECIES_NIDORAN_F", "SPECIES_VOLBEAT": "SPECIES_ILLUMISE"}[target])
            elif target == "SPECIES_MANAPHY":
                targets = ["SPECIES_PHIONE"]
            elif target.startswith("SPECIES_ROTOM"):
                targets = ["SPECIES_ROTOM"]
            elif target.startswith("SPECIES_SCATTERBUG"):
                targets = [rules.scatterbug]
            elif target.startswith("SPECIES_FURFROU"):
                targets = ["SPECIES_FURFROU"]
            elif target.startswith("SPECIES_PIKACHU"):
                targets = [egg_species("SPECIES_PIKACHU", parents)]
            elif target.startswith("SPECIES_EEVEE"):
                targets = ["SPECIES_EEVEE"]
            elif target == "SPECIES_SINISTEA_ANTIQUE":
                targets = ["SPECIES_SINISTEA_PHONY"]
            elif target == "SPECIES_POLTCHAGEIST_ARTISAN":
                targets = ["SPECIES_POLTCHAGEIST_COUNTERFEIT"]

            for result in targets:
                variants = [(result, requirement)]
                if rules.incense_required and result in rules.incense_babies:
                    regular, item = rules.incense_babies[result]
                    incense = item_display_name(item, items)
                    variants = [
                        (result, f"{requirement} Have a parent hold {incense}.".strip()),
                        (regular, f"{requirement} Neither parent should hold {incense}.".strip()),
                    ]
                for final, note in variants:
                    if final == row.constant or final not in by_constant or not by_constant[final].dex_visible:
                        continue
                    if len(targets) > 1:
                        note = f"{note} Eggs can hatch as either species; you may need more than one egg.".strip()
                    steps.append({
                        "kind": "breed", "source": row.constant, "target": final,
                        "requirement": note, "evolution": None,
                    })
    return steps


def attach_acquisition_paths(
    species: list[SpeciesRow], items: dict[str, ItemRecord], rules: BreedingRules | None = None,
) -> None:
    visible = {row.constant: row for row in species if row.dex_visible}
    edges: list[AcquisitionStep] = [
        {"kind": "evolve", "source": row.constant, "target": edge["target"],
         "requirement": "", "evolution": edge}
        for row in visible.values() for edge in row.evolutions
        if edge["target"] in visible
    ]
    edges.extend(breeding_steps(species, rules or parse_breeding_rules(), items))
    best: dict[str, AcquisitionPath] = {
        row.constant: {"source": row.constant, "locations": row.locations, "steps": []}
        for row in visible.values() if row.locations
    }

    def extend(edge: AcquisitionStep) -> AcquisitionPath | None:
        path = best.get(edge["source"])
        if path is None or (edge["kind"] == "breed" and "SPECIES_DITTO" not in best):
            return None
        visited = {path["source"], *(step["target"] for step in path["steps"])}
        if edge["target"] in visited:
            return None
        return {**path, "steps": [*path["steps"], edge]}

    changed = True
    while changed:
        changed = False
        for edge in edges:
            path = extend(edge)
            previous = best.get(edge["target"])
            if path and (previous is None or len(path["steps"]) < len(previous["steps"])):
                best[edge["target"]] = path
                changed = True

    for row in species:
        row.acquisition_paths = []
    for edge in edges:
        target = visible[edge["target"]]
        if target.locations:
            continue
        path = extend(edge)
        if path and path not in target.acquisition_paths:
            target.acquisition_paths.append(path)
    for row in species:
        row.acquisition_paths.sort(key=lambda path: (len(path["steps"]), visible[path["source"]].id))
