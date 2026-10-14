const FORMAT = 2;
const PREFIX_SIZE = 5;
const CRC_SIZE = 4;
const MAX_PARTY = 6;
const MAX_FRAGMENT = 400;
const NICKNAME_LENGTH = 12;
const MAX_BADGES = 8;
const BASE32 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
const STAT_NAMES = ["HP", "Atk", "Def", "Spe", "SpA", "SpD"];
const STAT_ORDER = [0, 1, 2, 4, 5, 3];
const DIFFICULTIES = ["Easy", "Normal", "Hard"];
const HEADER_FIELDS = [
  ["source", 1], ["difficulty", 2], ["newGamePlus", 2], ["badges", 4],
  ["playerGender", 1], ["playHours", 10], ["playMinutes", 6],
];
const THEME_KEY = "soulgold-docs-theme";
const LINK_INVALID = "This party link is incomplete or invalid. Scan the QR code again.";
const DATA_INVALID = "This party link contains invalid data. Scan the QR code again.";
const MAP_ERROR = "The game data for this team is invalid or incompatible. Please try again later.";

export function crc32(bytes) {
  let crc = 0xffffffff;
  for (const byte of bytes) {
    crc ^= byte;
    for (let bit = 0; bit < 8; bit++) crc = (crc >>> 1) ^ ((crc & 1) ? 0xedb88320 : 0);
  }
  return (crc ^ 0xffffffff) >>> 0;
}

function requireValue(condition, message) {
  if (!condition) throw new Error(message);
}

export function base32Encode(bytes) {
  let output = "";
  let buffer = 0;
  let bits = 0;
  for (const byte of bytes) {
    buffer = ((buffer << 8) | byte) & 0xfff;
    bits += 8;
    while (bits >= 5) {
      bits -= 5;
      output += BASE32[(buffer >> bits) & 31];
    }
  }
  if (bits) output += BASE32[(buffer << (5 - bits)) & 31];
  return output;
}

export function base32Decode(text) {
  requireValue(typeof text === "string" && text.length >= 16 && text.length <= MAX_FRAGMENT && /^[A-Za-z2-7]+$/.test(text), LINK_INVALID);
  const bytes = [];
  let buffer = 0;
  let bits = 0;
  for (const character of text.toUpperCase()) {
    buffer = ((buffer << 5) | BASE32.indexOf(character)) & 0xfff;
    bits += 5;
    if (bits >= 8) {
      bits -= 8;
      bytes.push((buffer >> bits) & 0xff);
    }
  }
  requireValue(bits < 5 && (buffer & ((1 << bits) - 1)) === 0, LINK_INVALID);
  return Uint8Array.from(bytes);
}

class BitReader {
  constructor(bytes) {
    this.bytes = bytes;
    this.bit = 0;
  }

  read(width) {
    requireValue(this.bit + width <= this.bytes.length * 8, LINK_INVALID);
    let value = 0;
    for (let index = 0; index < width; index++, this.bit++) {
      value |= ((this.bytes[this.bit >> 3] >> (this.bit & 7)) & 1) << index;
    }
    return value;
  }

  readBytes(count) {
    return Array.from({ length: count }, () => this.read(8));
  }
}

function decodeMember(reader) {
  const read = width => reader.read(width);
  const member = {
    species: read(11),
    item: read(11),
    ability: read(10),
    moves: Array.from({ length: 4 }, () => read(11)),
    level: read(7),
    nature: read(5),
    friendship: read(8),
    gender: read(2),
    shiny: Boolean(read(1)),
    gigantamax: Boolean(read(1)),
    unlockedInnates: read(1) | (read(1) << 1) | (read(1) << 2),
    evs: Array.from({ length: 6 }, () => read(8)),
    ivs: Array.from({ length: 6 }, () => read(5)),
    hyperTrained: Array.from({ length: 6 }, (_, stat) => read(1) << stat).reduce((bits, bit) => bits | bit, 0),
    teraType: read(5),
    dynamaxLevel: read(4),
    ball: read(6),
    statMultiplier: read(2),
  };
  const nicknameLength = read(4);
  requireValue(nicknameLength <= NICKNAME_LENGTH, DATA_INVALID);
  member.nickname = reader.readBytes(nicknameLength);
  requireValue(member.species !== 0 && member.level >= 1 && member.nature < 25 && member.gender !== 3
    && member.dynamaxLevel <= 10 && member.statMultiplier >= 1, "This party link contains invalid Pokémon data. Scan the QR code again.");
  return member;
}

export function decodePartyFragment(fragment) {
  requireValue(typeof fragment === "string", LINK_INVALID);
  const bytes = base32Decode(fragment.startsWith("#") ? fragment.slice(1) : fragment);
  requireValue(bytes.length >= PREFIX_SIZE + CRC_SIZE + 1, LINK_INVALID);
  requireValue(bytes[0] <= FORMAT, "This party link uses a newer format. Please refresh this page.");
  requireValue(bytes[0] === FORMAT, "This party link comes from an older test build and cannot be opened.");
  const view = new DataView(bytes.buffer);
  requireValue(crc32(bytes.subarray(0, -CRC_SIZE)) === view.getUint32(bytes.length - CRC_SIZE, true),
    "This party link is damaged. Scan the QR code again.");
  const reader = new BitReader(bytes.subarray(PREFIX_SIZE, -CRC_SIZE));
  const count = reader.read(3);
  const header = Object.fromEntries(HEADER_FIELDS.map(([name, width]) => [name, reader.read(width)]));
  const trainerName = reader.readBytes(reader.read(3));
  requireValue(count >= 1 && count <= MAX_PARTY, "This party link has an invalid team size. Scan the QR code again.");
  requireValue(header.difficulty < DIFFICULTIES.length && header.newGamePlus < 3 && header.badges <= MAX_BADGES
    && header.playHours <= 999 && header.playMinutes < 60, DATA_INVALID);
  const members = Array.from({ length: count }, () => decodeMember(reader));
  requireValue(reader.bytes.length === Math.ceil(reader.bit / 8)
    && (reader.bit % 8 === 0 || (reader.bytes.at(-1) >> (reader.bit % 8)) === 0), DATA_INVALID);
  return { format: FORMAT, dataId: view.getUint32(1, true).toString(16).padStart(8, "0"), ...header, trainerName, members };
}

const isObject = value => value !== null && typeof value === "object" && !Array.isArray(value);
const isId = value => Number.isInteger(value) && value >= 0 && value <= 65535;
const isName = value => typeof value === "string" && value.length > 0 && value.length <= 100
  && !/[\x00-\x1f\x7f\u2028\u2029]/.test(value);
const isConstant = value => typeof value === "string" && /^[A-Z][A-Z0-9_]*$/.test(value);
const isIdList = (value, length) => Array.isArray(value) && value.length === length && value.every(isId);
const own = (object, key) => Object.prototype.hasOwnProperty.call(object, key);

function validateTable(table, validEntry) {
  requireValue(isObject(table) && Object.keys(table).length > 0 && Object.keys(table).length <= 65536, MAP_ERROR);
  for (const [id, entry] of Object.entries(table)) {
    requireValue(/^(0|[1-9][0-9]*)$/.test(id) && isId(Number(id)) && isObject(entry) && validEntry(entry), MAP_ERROR);
  }
}

export function validateDictionary(dictionary, dataId) {
  requireValue(isObject(dictionary) && dictionary.format === FORMAT && dictionary.id === dataId
    && /^[0-9a-f]{8}$/.test(dataId) && isName(dictionary.romVersion), MAP_ERROR);
  const named = entry => isName(entry.name) && isConstant(entry.constant);
  validateTable(dictionary.types, named);
  validateTable(dictionary.items, named);
  validateTable(dictionary.abilities, named);
  validateTable(dictionary.species, entry => named(entry) && isIdList(entry.types, 2) && isIdList(entry.stats, 6)
    && isIdList(entry.innates, 3) && (entry.baseConstant === undefined || isConstant(entry.baseConstant)));
  validateTable(dictionary.moves, entry => named(entry) && isId(entry.type));
  validateTable(dictionary.natures, entry => isName(entry.name) && isId(entry.up) && isId(entry.down)
    && entry.up < 6 && entry.down < 6);
  validateTable(dictionary.balls, entry => isName(entry.name) && isId(entry.item));
  requireValue(isObject(dictionary.charset) && Object.entries(dictionary.charset).every(([key, value]) =>
    /^(0|[1-9][0-9]*)$/.test(key) && Number(key) < 256 && typeof value === "string" && value.length === 1
    && !/[\x00-\x1f\x7f]/.test(value)), MAP_ERROR);
  requireValue(isIdList(dictionary.innateUnlockLevels, 3) && typeof dictionary.friendshipStatBoost === "boolean", MAP_ERROR);
  requireValue(isId(dictionary.hiddenPowerMoveId) && own(dictionary.moves, dictionary.hiddenPowerMoveId)
    && Array.isArray(dictionary.hiddenPowerTypes) && dictionary.hiddenPowerTypes.length >= 2
    && dictionary.hiddenPowerTypes.length <= 32
    && dictionary.hiddenPowerTypes.every(id => isId(id) && own(dictionary.types, id))
    && new Set(dictionary.hiddenPowerTypes).size === dictionary.hiddenPowerTypes.length, MAP_ERROR);
  return dictionary;
}

function lookup(table, id, kind) {
  return own(table, id) ? table[id] : { name: `Unknown ${kind} #${id}`, constant: null, unknown: true };
}

export function decodeText(bytes, charset) {
  return bytes.map(byte => (own(charset, byte) ? charset[byte] : "?")).join("").trim();
}

export function routeSlug(constant, prefix) {
  return constant.slice(prefix.length).toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-+|-+$/g, "");
}

export function computeStats(member, species, nature, friendshipBoost) {
  return species.stats.map((base, stat) => {
    const iv = member.hyperTrained & (1 << stat) ? 31 : member.ivs[stat];
    const scaled = Math.floor(((2 * base * member.statMultiplier + iv + Math.floor(member.evs[stat] / 4)) * member.level) / 100);
    if (stat === 0) return species.constant === "SPECIES_SHEDINJA" ? 1 : scaled + member.level + 10;
    let value = scaled + 5;
    if (nature.up !== nature.down && stat === nature.up) value = Math.floor((value * 110) / 100);
    else if (nature.up !== nature.down && stat === nature.down) value = Math.floor((value * 90) / 100);
    if (friendshipBoost) value += Math.floor((value * 10 * member.friendship) / (255 * 100));
    return value;
  });
}

function hiddenPowerType(member, dictionary) {
  const parity = member.ivs.reduce((bits, iv, stat) => bits | ((iv & 1) << stat), 0);
  const typeId = dictionary.hiddenPowerTypes[Math.floor(((dictionary.hiddenPowerTypes.length - 1) * parity) / 63)];
  return { id: typeId, ...dictionary.types[typeId] };
}

function modeLabel(party) {
  if (party.newGamePlus === 2) return "NG+ Lunatic";
  const difficulty = DIFFICULTIES[party.difficulty];
  return party.newGamePlus === 1 ? `NG+ Standard (${difficulty})` : difficulty;
}

export function describeParty(party, dictionary) {
  validateDictionary(dictionary, party.dataId);
  const trainerName = decodeText(party.trainerName, dictionary.charset);
  const hallOfFame = party.source === 1;
  const teamLabel = hallOfFame ? "Hall of Fame team" : "team";
  const members = party.members.map((member, index) => {
    const species = lookup(dictionary.species, member.species, "species");
    const nature = lookup(dictionary.natures, member.nature, "nature");
    const moves = member.moves.filter(Boolean).map(id => {
      const move = lookup(dictionary.moves, id, "move");
      const type = id === dictionary.hiddenPowerMoveId ? hiddenPowerType(member, dictionary) : { id: move.type, ...lookup(dictionary.types, move.type, "type") };
      return { id, ...move, type, hiddenPower: id === dictionary.hiddenPowerMoveId };
    });
    const stats = species.unknown || nature.unknown ? null : computeStats(member, species, nature, dictionary.friendshipStatBoost);
    return {
      index,
      nickname: decodeText(member.nickname, dictionary.charset),
      species,
      speciesName: species.name,
      types: species.unknown ? [] : [...new Set(species.types)].map(id => ({ id, ...lookup(dictionary.types, id, "type") })),
      level: member.level,
      gender: member.gender,
      shiny: member.shiny,
      item: member.item ? lookup(dictionary.items, member.item, "item") : null,
      ability: member.ability ? lookup(dictionary.abilities, member.ability, "ability") : null,
      innates: species.unknown ? [] : species.innates.flatMap((id, slot) => id ? [{
        ...lookup(dictionary.abilities, id, "innate ability"),
        unlocked: Boolean(member.unlockedInnates & (1 << slot)),
        unlockLevel: dictionary.innateUnlockLevels[slot],
      }] : []),
      nature,
      teraType: member.teraType ? lookup(dictionary.types, member.teraType, "Tera Type") : null,
      gigantamax: member.gigantamax,
      friendship: member.friendship,
      ball: own(dictionary.balls, member.ball) ? { ...dictionary.balls[member.ball], itemConstant: lookup(dictionary.items, dictionary.balls[member.ball].item, "item").constant } : null,
      moves,
      statMultiplier: member.statMultiplier,
      stats: STAT_ORDER.map(stat => ({
        stat,
        name: STAT_NAMES[stat],
        base: species.unknown ? null : species.stats[stat],
        iv: member.hyperTrained & (1 << stat) ? 31 : member.ivs[stat],
        rawIv: member.ivs[stat],
        hyperTrained: Boolean(member.hyperTrained & (1 << stat)),
        ev: member.evs[stat],
        value: stats ? stats[stat] : null,
        nature: nature.up === nature.down ? 0 : stat === nature.up ? 1 : stat === nature.down ? -1 : 0,
      })),
      raw: member,
    };
  });
  return {
    dataId: party.dataId,
    romVersion: dictionary.romVersion,
    trainerName,
    hallOfFame,
    title: trainerName ? `${trainerName}’s ${teamLabel}` : hallOfFame ? "Hall of Fame team" : "Soulgold team",
    mode: modeLabel(party),
    badges: party.badges,
    playTime: `${party.playHours}:${String(party.playMinutes).padStart(2, "0")}`,
    members,
  };
}

function badgeLabel(count) {
  return `${count} ${count === 1 ? "badge" : "badges"}`;
}

function statLine(stats, pick, include = () => true) {
  return stats.filter(stat => include(pick(stat))).map(stat => `${pick(stat)} ${stat.name}`).join(" / ");
}

export function formatPartyExport(view) {
  const notes = [
    `Exported from Soulgold ${view.romVersion}${view.trainerName ? ` by ${view.trainerName}` : ""}: ${view.hallOfFame ? "Hall of Fame team, " : ""}${view.mode}, ${badgeLabel(view.badges)}, ${view.playTime} played.`,
    "Soulgold has custom species, moves, abilities and innate abilities. This is a party snapshot; standard Pokémon Showdown formats may not support these mechanics or consider the team legal.",
    "Eggs are omitted. IVs reflect Hyper Training; Hidden Power uses the original IVs. Nature reflects any mint used.",
  ];
  const blocks = view.members.map(member => {
    const gender = ["", " (M)", " (F)"][member.gender];
    const name = member.nickname && member.nickname !== member.speciesName ? `${member.nickname} (${member.speciesName})` : member.speciesName;
    const lines = [name + gender + (member.item ? ` @ ${member.item.name}` : "")];
    if (member.ability) lines.push(`Ability: ${member.ability.name}`);
    lines.push(`Level: ${member.level}`);
    if (member.shiny) lines.push("Shiny: Yes");
    lines.push(`Happiness: ${member.friendship}`);
    if (member.ball) lines.push(`Pokeball: ${member.ball.name}`);
    if (member.teraType) lines.push(`Tera Type: ${member.teraType.name}`);
    if (member.gigantamax) lines.push("Gigantamax: Yes");
    const evs = statLine(member.stats, stat => stat.ev, value => value !== 0);
    if (evs) lines.push(`EVs: ${evs}`);
    lines.push(`${member.nature.name} Nature`);
    lines.push(`IVs: ${statLine(member.stats, stat => stat.iv)}`);
    const hiddenPower = member.moves.find(move => move.hiddenPower);
    if (hiddenPower) lines.push(`Hidden Power: ${hiddenPower.type.name}`);
    for (const move of member.moves) lines.push(`- ${move.name}${move.hiddenPower ? ` [${move.type.name}]` : ""}`);
    const label = `${member.index + 1}. ${member.nickname || member.speciesName}`;
    if (member.innates.length) {
      notes.push(`${label} — Innates: ${member.innates.map(innate => `${innate.name} (${innate.unlocked ? "unlocked" : `locked until Lv ${innate.unlockLevel}`})`).join(", ")}.`);
    }
    if (member.stats.some(stat => stat.hyperTrained)) notes.push(`${label} — Original IVs: ${statLine(member.stats, stat => stat.rawIv)}.`);
    if (member.statMultiplier > 1) notes.push(`${label} — Base stats ×${member.statMultiplier} from its held item.`);
    return lines.join("\r\n");
  });
  return {
    paste: blocks.join("\r\n\r\n") + "\r\n",
    title: `${view.trainerName ? `${view.trainerName}’s ` : ""}Soulgold ${view.romVersion} ${view.hallOfFame ? "Hall of Fame team" : "team"}`,
    author: view.trainerName,
    notes: notes.join("\n\n"),
  };
}

function element(document, tag, props = {}, children = []) {
  const node = document.createElement(tag);
  for (const [key, value] of Object.entries(props)) {
    if (value === undefined || value === null || value === false) continue;
    if (key === "className") node.className = value;
    else if (key === "text") node.textContent = value;
    else node.setAttribute(key, value === true ? "" : String(value));
  }
  for (const child of [children].flat()) {
    if (child === undefined || child === null || child === false || child === "") continue;
    node.append(typeof child === "string" ? document.createTextNode(child) : child);
  }
  return node;
}

function spriteFor(member, links) {
  if (!member.species.constant) return null;
  const linked = links?.species?.[member.species.constant]?.[1];
  const regular = linked || `sprites/pokemon/${member.species.constant.slice("SPECIES_".length).toLowerCase()}.png`;
  return member.shiny ? regular.replace(/\.png$/, "_shiny.png") : regular;
}

function speciesHref(member, links) {
  const species = links?.species;
  if (!species) return null;
  const slug = species[member.species.constant]?.[0] ?? species[member.species.baseConstant]?.[0];
  return slug ? `pokedex/${slug}/` : null;
}

function itemLink(document, item, links) {
  const linked = item.constant ? links?.items?.[item.constant] : null;
  const content = [
    linked?.[1] ? element(document, "img", { className: "party-item-icon", src: linked[1], alt: "", loading: "lazy", decoding: "async" }) : null,
    element(document, "span", { text: item.name }),
  ];
  return linked?.[0]
    ? element(document, "a", { className: "party-item", href: `items/${linked[0]}/` }, content)
    : element(document, "span", { className: "party-item" }, content);
}

function typePill(document, type) {
  return element(document, "span", { className: `type ${type.constant || "TYPE_NONE"}`, text: type.name });
}

function abilityPill(document, ability, className, extra) {
  const props = { className: `pill ability-pill ${className}`, text: ability.name, title: extra };
  return ability.constant
    ? element(document, "a", { ...props, href: `abilities/${routeSlug(ability.constant, "ABILITY_")}/` })
    : element(document, "span", props);
}

function fact(document, label, value) {
  return value ? element(document, "div", { className: "party-fact" }, [
    element(document, "dt", { text: label }),
    element(document, "dd", {}, value),
  ]) : null;
}

function renderMember(document, member, links) {
  const sprite = spriteFor(member, links);
  const href = speciesHref(member, links);
  const displayName = member.nickname || member.speciesName;
  const image = sprite ? element(document, "img", {
    className: "party-sprite", src: sprite, alt: "", width: 64, height: 64, decoding: "async",
  }) : null;
  if (image && member.shiny) {
    image.addEventListener?.("error", () => {
      if (image.src.endsWith("_shiny.png")) image.src = image.src.replace(/_shiny\.png$/, ".png");
    });
  }
  const title = element(document, "h3", { className: "party-mon-name" }, [
    href ? element(document, "a", { href, text: displayName }) : displayName,
    member.gender ? element(document, "span", { className: `party-gender party-gender-${member.gender === 1 ? "m" : "f"}`, text: member.gender === 1 ? "♂" : "♀", title: member.gender === 1 ? "Male" : "Female" }) : null,
    member.shiny ? element(document, "span", { className: "party-shiny", text: "★", title: "Shiny" }) : null,
  ]);
  const subtitle = [member.nickname && member.nickname !== member.speciesName ? member.speciesName : null, `Lv ${member.level}`].filter(Boolean).join(" · ");
  const innates = member.innates.length ? element(document, "div", { className: "pill-list" }, member.innates.map(innate =>
    abilityPill(document, innate, innate.unlocked ? "innate-ability-pill" : "innate-ability-pill party-locked",
      innate.unlocked ? "Unlocked innate" : `Unlocks at Lv ${innate.unlockLevel}`))) : null;
  const nature = member.nature.up === member.nature.down || member.nature.unknown
    ? member.nature.name
    : `${member.nature.name} (+${STAT_NAMES[member.nature.up]} −${STAT_NAMES[member.nature.down]})`;
  const moves = element(document, "ol", { className: "party-moves" }, member.moves.map(move => element(document, "li", {}, [
    typePill(document, move.type),
    move.constant
      ? element(document, "a", { className: "party-move-name", href: `moves/${routeSlug(move.constant, "MOVE_")}/`, text: move.name })
      : element(document, "span", { className: "party-move-name", text: move.name }),
  ])));
  const stats = element(document, "table", { className: "party-stats" }, [
    element(document, "thead", {}, element(document, "tr", {}, ["", "Base", "IV", "EV", "Stat"].map(text => element(document, "th", { scope: "col", text })))),
    element(document, "tbody", {}, member.stats.map(stat => element(document, "tr", {
      className: stat.nature > 0 ? "party-stat-up" : stat.nature < 0 ? "party-stat-down" : null,
    }, [
      element(document, "th", { scope: "row", text: stat.name }),
      element(document, "td", { className: "party-stat-base" }, [
        element(document, "span", { className: "bar", "aria-hidden": "true" }, element(document, "span", { style: `width:${Math.min(100, (stat.base ?? 0) / 2)}%` })),
        element(document, "span", { text: stat.base ?? "?" }),
      ]),
      element(document, "td", { text: stat.hyperTrained ? `${stat.iv}*` : String(stat.iv), title: stat.hyperTrained ? `Hyper Trained (original ${stat.rawIv})` : null }),
      element(document, "td", { text: String(stat.ev) }),
      element(document, "td", { className: "party-stat-value", text: stat.value ?? "?" }),
    ]))),
  ]);
  return element(document, "article", { className: "party-mon data-panel" }, [
    element(document, "header", { className: "party-mon-head" }, [
      href && image ? element(document, "a", { className: "party-sprite-link", href, "aria-hidden": "true", tabindex: "-1" }, image) : image,
      element(document, "div", { className: "party-mon-title" }, [
        title,
        element(document, "p", { className: "party-mon-subtitle", text: subtitle }),
        element(document, "div", { className: "type-list" }, member.types.map(type => typePill(document, type))),
      ]),
    ]),
    element(document, "dl", { className: "party-facts" }, [
      fact(document, "Item", member.item ? itemLink(document, member.item, links) : element(document, "span", { className: "muted", text: "None" })),
      fact(document, "Ability", member.ability ? abilityPill(document, member.ability, "base-ability-pill") : null),
      fact(document, "Innates", innates),
      fact(document, "Nature", nature),
      fact(document, "Tera", member.teraType ? typePill(document, member.teraType) : null),
      fact(document, "Ball", member.ball ? itemLink(document, { name: member.ball.name, constant: member.ball.itemConstant }, links) : null),
      fact(document, "Extras", [
        member.gigantamax ? "Gigantamax" : null,
        member.statMultiplier > 1 ? `Base stats ×${member.statMultiplier} (held item)` : null,
      ].filter(Boolean).join(" · ")),
    ]),
    moves,
    stats,
  ]);
}

export function renderParty(document, view, links) {
  return {
    members: view.members.map(member => renderMember(document, member, links)),
    meta: [
      `Soulgold ${view.romVersion}`,
      view.hallOfFame ? "Hall of Fame" : null,
      view.mode,
      badgeLabel(view.badges),
      `${view.playTime} played`,
      `${view.members.length} Pokémon`,
    ].filter(Boolean).map(text => element(document, "li", { text })),
  };
}

export function fragmentFromText(text) {
  const trimmed = String(text ?? "").trim();
  const hash = trimmed.includes("#") ? trimmed.slice(trimmed.lastIndexOf("#") + 1) : trimmed;
  return /^[A-Za-z2-7]+$/.test(hash) ? hash : null;
}

function applyTheme(document, theme) {
  const dark = theme === "dark";
  document.documentElement.dataset.theme = dark ? "dark" : "light";
  const button = document.getElementById("themeToggle");
  if (button) {
    button.setAttribute("aria-label", `Switch to ${dark ? "light" : "dark"} mode`);
    button.setAttribute("aria-pressed", String(dark));
  }
}

function setupTheme(document, window) {
  const button = document.getElementById("themeToggle");
  if (!button || !document.documentElement) return;
  applyTheme(document, document.documentElement.dataset.theme);
  button.addEventListener("click", () => {
    const theme = document.documentElement.dataset.theme === "dark" ? "light" : "dark";
    applyTheme(document, theme);
    try {
      window.localStorage.setItem(THEME_KEY, theme);
    } catch {}
  });
}

export function mountPartyExport({ document, window, fetch: fetchData = window.fetch.bind(window) }) {
  const get = id => document.getElementById(id);
  const status = get("partyStatus");
  const retry = get("partyRetry");
  const view = get("partyView");
  const intro = get("partyIntro");
  const paste = get("partyPaste");
  const form = get("partyForm");
  const linkInput = get("partyLinkInput");
  const baseTitle = document.title;
  let request;
  let generation = 0;
  let snapshot = "";
  let shareTitle = "";
  let ready = false;

  setupTheme(document, window);
  const setStatus = (message, error = false) => {
    status.textContent = message;
    status.className = `panel-status${error ? " error" : ""}`;
  };
  const reset = () => {
    ready = false;
    view.hidden = true;
    retry.hidden = true;
    intro.hidden = false;
    paste.value = "";
    get("partyNotes").value = "";
    get("partyPasteTitle").value = "";
    get("partyAuthor").value = "";
    get("partyMembers").replaceChildren();
    get("partyMeta").replaceChildren();
    get("partyHeading").textContent = "";
    document.title = baseTitle;
    snapshot = "";
  };
  const fetchJson = async (path, error) => {
    const response = await fetchData(new URL(path, document.baseURI).href, { signal: request.signal, credentials: "omit" });
    if (!response.ok) throw new Error(error);
    try {
      return await response.json();
    } catch {
      throw new Error(MAP_ERROR);
    }
  };
  const load = async () => {
    const current = ++generation;
    request?.abort();
    request = new AbortController();
    reset();
    const fragment = window.location.hash;
    if (!fragment || fragment === "#") {
      setStatus("Nothing here yet!");
      return;
    }
    let party;
    try {
      party = decodePartyFragment(fragment);
    } catch (error) {
      setStatus(error.message, true);
      return;
    }
    setStatus("Loading your party…");
    try {
      const version = document.querySelector?.('meta[name="docs-data-version"]')?.getAttribute("content") || "";
      const [dictionary, links] = await Promise.all([
        fetchJson(`data/party-export/${party.dataId}.json`, "Game data for this party is not available yet. Please try again after the Soulgold website has been updated."),
        fetchJson(`data/party-links.json${version && !version.includes("{") ? `?v=${version}` : ""}`, "links").catch(error => {
          if (error?.name === "AbortError") throw error;
          return null;
        }),
      ]);
      const described = describeParty(party, dictionary);
      if (current !== generation) return;
      const rendered = renderParty(document, described, links);
      const exported = formatPartyExport(described);
      get("partyHeading").textContent = described.title;
      get("partyMeta").replaceChildren(...rendered.meta);
      get("partyMembers").replaceChildren(...rendered.members);
      paste.value = exported.paste;
      get("partyPasteTitle").value = exported.title;
      get("partyAuthor").value = exported.author;
      get("partyNotes").value = exported.notes;
      document.title = `${described.title} · Soulgold`;
      shareTitle = described.title;
      snapshot = window.location.href;
      ready = true;
      intro.hidden = true;
      view.hidden = false;
      setStatus(`${described.members.length} Pokémon loaded.`);
    } catch (error) {
      if (current !== generation || error?.name === "AbortError") return;
      setStatus(error instanceof TypeError ? "Your party could not load. Check your connection and try again." : error.message, true);
      retry.hidden = false;
    }
  };
  const copy = async (value, message, fallback) => {
    const current = generation;
    try {
      await window.navigator.clipboard.writeText(value);
      if (current === generation) setStatus(message);
    } catch {
      if (current !== generation) return;
      if (fallback) {
        fallback.focus();
        fallback.select();
      }
      setStatus(fallback ? "Copy is unavailable. The team text is selected; use your browser'ss Copy command." : "Copy is unavailable. Copy this page's address from your browser to share the team.", true);
    }
  };
  const openFragment = value => {
    const fragment = fragmentFromText(value);
    if (!fragment) {
      setStatus("Invalid format for party.", true);
      return;
    }
    window.location.hash = fragment;
  };
  get("partyShare").addEventListener("click", async () => {
    if (!ready) return;
    if (typeof window.navigator.share === "function") {
      try {
        await window.navigator.share({ title: shareTitle, url: snapshot });
        return;
      } catch (error) {
        if (error?.name === "AbortError") return;
      }
    }
    return copy(snapshot, "Team link copied.");
  });
  get("partyCopyLink").addEventListener("click", () => { if (ready) return copy(snapshot, "Team link copied."); });
  get("partyCopy").addEventListener("click", () => { if (ready) return copy(paste.value, "Team text copied.", paste); });
  get("partyDownload").addEventListener("click", () => {
    if (!ready) return;
    const url = window.URL.createObjectURL(new Blob([paste.value], { type: "text/plain;charset=utf-8" }));
    const link = document.createElement("a");
    link.href = url;
    link.download = "soulgold-party.txt";
    link.click();
    window.setTimeout(() => window.URL.revokeObjectURL(url), 1000);
  });
  form.addEventListener("submit", event => {
    if (!ready || !paste.value.trim()) {
      event.preventDefault();
      setStatus("Add your team text before creating a PokePaste.", true);
    }
  });
  get("partyLinkForm").addEventListener("submit", event => {
    event.preventDefault();
    openFragment(linkInput.value);
  });
  retry.addEventListener("click", load);
  window.addEventListener("hashchange", load);
  return { load, initialLoad: load() };
}

if (typeof document !== "undefined" && document.getElementById("partyView")) {
  mountPartyExport({ document, window });
}
