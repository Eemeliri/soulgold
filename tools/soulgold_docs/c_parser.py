from __future__ import annotations

import ast
import re
import subprocess
from pathlib import Path

from .constants import COMPOUND_STRING_MACRO
from .paths import REPO_ROOT


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8")

def clean_constant_name(value: str, prefix: str) -> str:
    return value.removeprefix(prefix).replace("_", " ").title()

def format_identifier_name(value: str) -> str:
    value = value.removeprefix("MAP_")
    value = re.sub(r"([a-z])([A-Z])", r"\1 \2", value)
    value = value.replace("_", " ")
    value = re.sub(r"([A-Za-z]+)(\d+)", r"\1 \2", value)
    value = re.sub(r"\b([BF]) (\d+)([FR])\b", r"\1\2\3", value)
    value = re.sub(r"\b([A-Z])\s+(\d)\b", r"\1\2", value)
    return value.title().replace("Tm", "TM").replace("Hm", "HM")

def normalize_token(value: str) -> str:
    return re.sub(r"[^a-z0-9]+", "", value.lower())

def slugify(value: str) -> str:
    return re.sub(r"[^a-z0-9]+", "_", value.lower()).strip("_")

def asset_stem(value: str) -> str:
    value = re.sub(r"([A-Z]+)([A-Z][a-z])", r"\1_\2", value)
    value = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", value)
    return slugify(value)

def decode_c_string(value: str) -> str:
    value = value.replace("\\p", "\\n\\n")
    try:
        decoded = ast.literal_eval(f'"{value}"')
    except (SyntaxError, ValueError):
        decoded = value.replace("\\n", " ")
    decoded = decoded.replace("\n", " ")
    decoded = decoded.replace("{PKMN}", "Pokemon")
    decoded = decoded.replace("{POKEBLOCK}", "Pokeblock")
    decoded = decoded.replace("♀", " F").replace("♂", " M")
    decoded = decoded.replace("é", "e")
    return decoded.strip()

def collect_strings(expr: str) -> str:
    parts = re.findall(r'"((?:[^"\\]|\\.)*)"', expr)
    decoded = [decode_c_string(part) for part in parts]
    if decoded and len(set(decoded)) == 1:
        decoded = decoded[:1]
    return re.sub(r"\s+", " ", " ".join(decoded)).strip()

def strip_c_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)
    return re.sub(r"//.*", "", text)

def parse_define_constants(path: Path, prefix: str) -> tuple[dict[str, int], dict[int, str]]:
    name_to_id: dict[str, int] = {}
    id_to_name: dict[int, str] = {}
    pattern = re.compile(rf"^\s*#define\s+({prefix}[A-Z0-9_]+)\s+(\d+)\b")
    for line in read(path).splitlines():
        match = pattern.match(line)
        if not match:
            continue
        name, value = match.group(1), int(match.group(2))
        name_to_id[name] = value
        id_to_name[value] = name
    return name_to_id, id_to_name

def parse_define_aliases(path: Path, prefix: str) -> dict[str, str]:
    aliases = dict(re.findall(
        rf"^#define\s+({prefix}[A-Z0-9_]+)\s+({prefix}[A-Z0-9_]+)\s*$",
        read(path),
        re.MULTILINE,
    ))
    for alias in aliases:
        target = aliases[alias]
        seen = {alias}
        while target in aliases and target not in seen:
            seen.add(target)
            target = aliases[target]
        aliases[alias] = target
    return aliases

def parse_enum_constants(path: Path, prefix: str) -> tuple[dict[str, int], dict[int, str]]:
    name_to_id: dict[str, int] = {}
    id_to_name: dict[int, str] = {}
    next_value = 0
    pattern = re.compile(rf"\b({prefix}[A-Z0-9_]+)\b(?:\s*=\s*([^,/\n]+))?")
    for raw in read(path).splitlines():
        line = raw.split("//", 1)[0].strip()
        if not line or line.startswith("#"):
            continue
        match = pattern.search(line)
        if not match:
            continue
        name, expr = match.groups()
        if expr:
            expr = expr.strip()
            if expr.isdigit():
                next_value = int(expr)
            elif expr in name_to_id:
                name_to_id[name] = name_to_id[expr]
                continue
            else:
                continue
        name_to_id[name] = next_value
        id_to_name.setdefault(next_value, name)
        next_value += 1
    return name_to_id, id_to_name

def preprocess_source(source: str, *extra_include_dirs: str) -> str:
    temp = Path("/tmp/soulgold_docs_preprocess.c")
    temp.write_text(source, encoding="utf-8")
    include_args = [f"-I{path}" for path in (".", "include", "src", *extra_include_dirs)]
    result = subprocess.run(
        ["gcc", "-E", "-P", str(temp), *include_args],
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        raise RuntimeError(f"gcc failed preprocessing source:\n{result.stderr}")
    return result.stdout

def preprocess(include_path: str) -> str:
    return preprocess_source(f'#include "global.h"\n#include "{include_path}"\n')

def split_designated_entries(text: str) -> dict[str, str]:
    entries: dict[str, str] = {}
    lines = text.splitlines()
    current_key: str | None = None
    current: list[str] = []
    depth = 0
    entry_re = re.compile(r"^\s*\[\s*([A-Z0-9_]+|\d+)\s*\]\s*=")

    for line in lines:
        if current_key is None:
            match = entry_re.match(line)
            if not match:
                continue
            current_key = match.group(1)
            current = [line]
            depth = line.count("{") - line.count("}")
            if "{" in line and depth <= 0:
                entries[current_key] = "\n".join(current)
                current_key = None
                current = []
            continue

        current.append(line)
        depth += line.count("{") - line.count("}")
        if depth <= 0:
            entries[current_key] = "\n".join(current)
            current_key = None
            current = []
    return entries

def extract_field(entry: str, field_name: str) -> str | None:
    match = re.search(rf"\.{field_name}\s*=", entry)
    if not match:
        return None
    start = match.end()
    depth = 0
    for index in range(start, len(entry)):
        char = entry[index]
        if char in "({":
            depth += 1
        elif char in ")}":
            depth -= 1
        elif char == "," and depth <= 0:
            return entry[start:index].strip()
    return None

def split_top_level_ternary(expr: str) -> tuple[str, str, str] | None:
    depth = 0
    question_index: int | None = None
    nested = 0
    for index, char in enumerate(expr):
        if char in "({[":
            depth += 1
        elif char in ")}]":
            depth -= 1
        elif depth == 0 and char == "?":
            if question_index is None:
                question_index = index
            else:
                nested += 1
        elif depth == 0 and char == ":" and question_index is not None:
            if nested:
                nested -= 1
                continue
            return expr[:question_index], expr[question_index + 1:index], expr[index + 1:]
    return None

def eval_numeric_ast(node: ast.AST) -> int | bool:
    if isinstance(node, ast.Expression):
        return eval_numeric_ast(node.body)
    if isinstance(node, ast.Constant) and isinstance(node.value, (int, bool)):
        return node.value
    if isinstance(node, ast.UnaryOp) and isinstance(node.op, (ast.UAdd, ast.USub, ast.Not)):
        value = eval_numeric_ast(node.operand)
        if isinstance(node.op, ast.UAdd):
            return int(value)
        if isinstance(node.op, ast.USub):
            return -int(value)
        return not bool(value)
    if isinstance(node, ast.BinOp) and isinstance(node.op, (ast.Add, ast.Sub, ast.Mult, ast.Div, ast.FloorDiv, ast.Mod)):
        left = int(eval_numeric_ast(node.left))
        right = int(eval_numeric_ast(node.right))
        if isinstance(node.op, ast.Add):
            return left + right
        if isinstance(node.op, ast.Sub):
            return left - right
        if isinstance(node.op, ast.Mult):
            return left * right
        if isinstance(node.op, (ast.Div, ast.FloorDiv)):
            return left // right
        return left % right
    if isinstance(node, ast.BoolOp) and isinstance(node.op, (ast.And, ast.Or)):
        values = [bool(eval_numeric_ast(value)) for value in node.values]
        return all(values) if isinstance(node.op, ast.And) else any(values)
    if isinstance(node, ast.Compare):
        left = eval_numeric_ast(node.left)
        for op, comparator in zip(node.ops, node.comparators):
            right = eval_numeric_ast(comparator)
            if isinstance(op, ast.Eq) and not left == right:
                return False
            if isinstance(op, ast.NotEq) and not left != right:
                return False
            if isinstance(op, ast.Lt) and not left < right:
                return False
            if isinstance(op, ast.LtE) and not left <= right:
                return False
            if isinstance(op, ast.Gt) and not left > right:
                return False
            if isinstance(op, ast.GtE) and not left >= right:
                return False
            left = right
        return True
    raise ValueError(f"unsupported expression: {ast.dump(node)}")

def eval_int_expr(expr: str) -> int | None:
    expr = expr.strip()
    while expr.startswith("(") and expr.endswith(")"):
        depth = 0
        encloses_expr = True
        for index, char in enumerate(expr):
            if char == "(":
                depth += 1
            elif char == ")":
                depth -= 1
                if depth == 0 and index != len(expr) - 1:
                    encloses_expr = False
                    break
        if not encloses_expr:
            break
        expr = expr[1:-1].strip()

    ternary = split_top_level_ternary(expr)
    if ternary:
        condition, true_expr, false_expr = ternary
        branch = true_expr if eval_int_expr(condition) else false_expr
        return eval_int_expr(branch)

    expr = re.sub(r"\b([0-9]+)[uUlL]+\b", r"\1", expr)
    expr = expr.replace("&&", " and ").replace("||", " or ")
    expr = re.sub(r"!(?!=)", " not ", expr)
    if re.search(r"[A-Za-z_]", expr):
        return None
    try:
        return int(eval_numeric_ast(ast.parse(expr, mode="eval")))
    except (SyntaxError, ValueError, ZeroDivisionError):
        return None

def extract_number(entry: str, field_name: str, default: int = 0) -> int:
    expr = extract_field(entry, field_name)
    if not expr:
        return default
    value = eval_int_expr(expr)
    if value is not None:
        return value
    match = re.search(r"-?\d+", expr)
    return int(match.group(0)) if match else default

def extract_braced_constants(entry: str, field_name: str, prefix: str) -> list[str]:
    expr = extract_field(entry, field_name) or ""
    return re.findall(rf"\b{prefix}[A-Z0-9_]+\b", expr)

def extract_constant(entry: str, field_name: str, prefix: str) -> str | None:
    expr = extract_field(entry, field_name) or ""
    match = re.search(rf"\b{prefix}[A-Z0-9_]+\b", expr)
    return match.group(0) if match else None

def parse_shared_strings(text: str) -> dict[str, str]:
    shared: dict[str, str] = {}
    pattern = re.compile(
        rf"(?:static\s+)?const\s+u8\s+([A-Za-z0-9_]+)\[\]\s*=\s*(?:_|{COMPOUND_STRING_MACRO})\((.*?)\);",
        re.DOTALL,
    )
    for name, expr in pattern.findall(text):
        shared[name] = collect_strings(expr)
    return shared

def split_top_level_braces(text: str) -> list[str]:
    chunks: list[str] = []
    depth = 0
    start: int | None = None
    for index, char in enumerate(text):
        if char == "{":
            if depth == 0:
                start = index + 1
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0 and start is not None:
                chunks.append(text[start:index])
                start = None
    return chunks

def split_top_level_commas(text: str) -> list[str]:
    chunks: list[str] = []
    depth = 0
    start = 0
    for index, char in enumerate(text):
        if char in "{(":
            depth += 1
        elif char in "})":
            depth -= 1
        elif char == "," and depth == 0:
            chunks.append(text[start:index].strip())
            start = index + 1
    chunks.append(text[start:].strip())
    return chunks

def extract_balanced_call(text: str, start: int) -> str | None:
    open_index = text.find("(", start)
    if open_index == -1:
        return None
    depth = 0
    for index in range(open_index, len(text)):
        if text[index] == "(":
            depth += 1
        elif text[index] == ")":
            depth -= 1
            if depth == 0:
                return text[open_index + 1:index]
    return None
