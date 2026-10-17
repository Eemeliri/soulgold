import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import test from "node:test";
import {
  base32Decode, base32Encode, computeStats, crc32, decodePartyFragment, describeParty, formatPartyExport,
  fragmentFromText, mountPartyExport, routeSlug, validateDictionary,
} from "../../../docs/src/assets/party-export.mjs";

const DATA_ID = "1234abcd";
const GOLDEN_BITS = [
  0x61, 0x77, 0x8F, 0x96, 0xC5, 0xE6, 0xDD, 0xE7, 0x29, 0xC4, 0x8E, 0x06, 0x55, 0xC0, 0x41, 0x82,
  0x0A, 0x92, 0x7B, 0xC8, 0x04, 0x06, 0x11, 0x1C, 0x27, 0x2D, 0xB8, 0x0F, 0xFC, 0x31, 0x25, 0x62,
  0xA0, 0x54, 0xD1, 0xD5, 0xE7, 0xDC, 0xED,
];
const CHARSET = { 0: " ", 187: "A", 197: "K", 209: "W", 213: "a", 220: "h", 221: "i", 230: "r", 231: "s", 237: "y", 195: "I", 202: "P", 218: "f" };
const named = (name, constant) => ({ name, constant });
const dictionary = {
  format: 2, id: DATA_ID, romVersion: "v1.2.3",
  species: {
    25: { name: "Pikachu", constant: "SPECIES_PIKACHU", types: [13, 13], stats: [35, 55, 40, 90, 50, 50], innates: [2, 0, 3] },
    201: { name: "Unown", constant: "SPECIES_UNOWN", types: [1, 1], stats: [48, 72, 48, 48, 72, 48], innates: [0, 0, 0] },
    445: { name: "Garchomp", constant: "SPECIES_GARCHOMP", types: [16, 4], stats: [108, 130, 95, 102, 80, 85], innates: [0, 0, 0] },
    1065: { name: "Rotom-Wash", constant: "SPECIES_ROTOM_WASH", types: [13, 12], stats: [50, 65, 107, 86, 105, 107], innates: [2, 0, 0], baseConstant: "SPECIES_ROTOM" },
  },
  items: { 1: named("Light Ball", "ITEM_LIGHT_BALL"), 10: named("Dusk Ball", "ITEM_DUSK_BALL"), 472: named("Leftovers", "ITEM_LEFTOVERS") },
  abilities: { 1: named("Static", "ABILITY_STATIC"), 2: named("Lightning Rod", "ABILITY_LIGHTNING_ROD"), 3: named("Surge Surfer", "ABILITY_SURGE_SURFER"), 26: named("Levitate", "ABILITY_LEVITATE") },
  moves: {
    1: { ...named("Thunderbolt", "MOVE_THUNDERBOLT"), type: 13 },
    2: { ...named("Hidden Power", "MOVE_HIDDEN_POWER"), type: 1 },
    3: { ...named("Return", "MOVE_RETURN"), type: 1 },
    4: { ...named("Protect", "MOVE_PROTECT"), type: 1 },
    56: { ...named("Hydro Pump", "MOVE_HYDRO_PUMP"), type: 12 },
    85: { ...named("Thunderbolt", "MOVE_THUNDERBOLT"), type: 13 },
    261: { ...named("Will-O-Wisp", "MOVE_WILL_O_WISP"), type: 11 },
    521: { ...named("Volt Switch", "MOVE_VOLT_SWITCH"), type: 13 },
  },
  natures: { 0: { name: "Hardy", up: 1, down: 1 }, 10: { name: "Timid", up: 3, down: 1 }, 13: { name: "Jolly", up: 3, down: 4 }, 15: { name: "Modest", up: 4, down: 1 } },
  types: {
    1: named("Normal", "TYPE_NORMAL"), 2: named("Fighting", "TYPE_FIGHTING"), 3: named("Flying", "TYPE_FLYING"),
    4: named("Ground", "TYPE_GROUND"), 11: named("Fire", "TYPE_FIRE"), 12: named("Water", "TYPE_WATER"),
    13: named("Electric", "TYPE_ELECTRIC"), 16: named("Dragon", "TYPE_DRAGON"), 18: named("Dark", "TYPE_DARK"),
    19: named("Fairy", "TYPE_FAIRY"),
  },
  balls: { 1: { name: "Poke Ball", item: 1 }, 10: { name: "Dusk Ball", item: 10 } },
  charset: CHARSET,
  innateUnlockLevels: [75, 85, 95],
  friendshipStatBoost: false,
  hiddenPowerMoveId: 2,
  hiddenPowerTypes: [2, 3, 11, 12, 18, 19],
};

class BitWriter {
  bytes = [];
  bit = 0;
  write(value, width) {
    for (let index = 0; index < width; index++, this.bit++) {
      if (this.bit % 8 === 0) this.bytes.push(0);
      if ((value >> index) & 1) this.bytes[this.bytes.length - 1] |= 1 << (this.bit % 8);
    }
  }
}

const defaultMember = {
  species: 25, item: 1, ability: 1, moves: [1, 2, 3, 4], level: 50, nature: 10, friendship: 200,
  gender: 2, shiny: true, gigantamax: false, unlockedInnates: 1, evs: [4, 0, 0, 252, 252, 0],
  ivs: [31, 30, 29, 28, 27, 26], hyperTrained: 0b100010, teraType: 11, dynamaxLevel: 10, ball: 1,
  statMultiplier: 1, nickname: [],
};

function payload({ members = [defaultMember], format = 2, dataId = DATA_ID, header = {}, trainer = [197, 230, 221, 231], extraByte = false } = {}) {
  const writer = new BitWriter();
  const context = { source: 0, difficulty: 2, newGamePlus: 0, badges: 8, playerGender: 1, playHours: 42, playMinutes: 7, ...header };
  writer.write(members.length, 3);
  for (const [name, width] of [["source", 1], ["difficulty", 2], ["newGamePlus", 2], ["badges", 4], ["playerGender", 1], ["playHours", 10], ["playMinutes", 6]]) writer.write(context[name], width);
  writer.write(trainer.length, 3);
  for (const byte of trainer) writer.write(byte, 8);
  for (const partial of members) {
    const member = { ...defaultMember, ...partial };
    for (const [value, width] of [[member.species, 11], [member.item, 11], [member.ability, 10]]) writer.write(value, width);
    for (const move of member.moves) writer.write(move, 11);
    writer.write(member.level, 7);
    writer.write(member.nature, 5);
    writer.write(member.friendship, 8);
    writer.write(member.gender, 2);
    writer.write(Number(member.shiny), 1);
    writer.write(Number(member.gigantamax), 1);
    for (let slot = 0; slot < 3; slot++) writer.write((member.unlockedInnates >> slot) & 1, 1);
    for (const ev of member.evs) writer.write(ev, 8);
    for (const iv of member.ivs) writer.write(iv, 5);
    for (let stat = 0; stat < 6; stat++) writer.write((member.hyperTrained >> stat) & 1, 1);
    writer.write(member.teraType, 5);
    writer.write(member.dynamaxLevel, 4);
    writer.write(member.ball, 6);
    writer.write(member.statMultiplier, 2);
    writer.write(member.nickname.length, 4);
    for (const byte of member.nickname) writer.write(byte, 8);
  }
  if (extraByte) writer.bytes.push(0);
  return withCrc([format, ...le32(parseInt(dataId, 16)), ...writer.bytes]);
}

function le32(value) {
  return [value & 0xff, (value >>> 8) & 0xff, (value >>> 16) & 0xff, value >>> 24];
}

function withCrc(bytes) {
  const data = Uint8Array.from(bytes);
  return Uint8Array.from([...data, ...le32(crc32(data))]);
}

const link = bytes => base32Encode(bytes);

test("CRC32 matches the standard reference vector", () => {
  assert.equal(crc32(new TextEncoder().encode("123456789")), 0xcbf43926);
});

test("base32 round trips every remainder length and accepts lowercase scans", () => {
  for (let length = 10; length < 16; length++) {
    const bytes = Uint8Array.from({ length }, (_, index) => (index * 37 + length) & 0xff);
    assert.deepEqual(base32Decode(base32Encode(bytes)), bytes);
    assert.deepEqual(base32Decode(base32Encode(bytes).toLowerCase()), bytes);
  }
  assert.equal(base32Encode(Uint8Array.from([0xfb, 0xff, 0xff, 0x00, 0x01])), "7P776AAB");
});

test("decodes the golden Rotom-Wash bitstream shared with the ROM and Python serializers", () => {
  const party = decodePartyFragment(`#${link(withCrc([2, ...le32(0x12345678), ...GOLDEN_BITS]))}`);
  assert.equal(party.dataId, "12345678");
  assert.deepEqual({ ...party, members: undefined }, {
    format: 2, dataId: "12345678", source: 0, difficulty: 2, newGamePlus: 1, badges: 7, playerGender: 1,
    playHours: 123, playMinutes: 45, trainerName: [197, 230, 221, 231], members: undefined,
  });
  assert.deepEqual(party.members, [{
    species: 1065, item: 472, ability: 26, moves: [85, 56, 521, 261], level: 57, nature: 15, friendship: 200,
    gender: 0, shiny: true, gigantamax: false, unlockedInnates: 0, evs: [12, 34, 56, 78, 90, 112],
    ivs: [31, 0, 30, 7, 6, 5], hyperTrained: 17, teraType: 12, dynamaxLevel: 0, ball: 10, statMultiplier: 1,
    nickname: [209, 213, 231, 220, 237],
  }]);
  const view = describeParty({ ...party, dataId: DATA_ID }, dictionary);
  assert.equal(view.title, "Kris’s team");
  assert.equal(view.members[0].nickname, "Washy");
  assert.equal(formatPartyExport(view).paste.split("\r\n")[0], "Washy (Rotom-Wash) @ Leftovers");
});

test("the largest party fits the 400-character fragment limit and decodes every member", () => {
  const members = Array.from({ length: 6 }, () => ({ nickname: Array(12).fill(187), level: 120 }));
  const bytes = payload({ members, trainer: Array(7).fill(187) });
  assert.equal(bytes.length, 248);
  const encoded = link(bytes);
  assert.ok(encoded.length <= 400);
  const party = decodePartyFragment(encoded);
  assert.equal(party.members.length, 6);
  assert.equal(party.members[5].level, 120);
  assert.equal(describeParty(party, dictionary).members[0].nickname, "AAAAAAAAAAAA");
});

test("rejects missing, oversized, noncanonical and non-base32 links", () => {
  const valid = link(payload());
  const lastValue = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567".indexOf(valid.at(-1));
  const noncanonical = valid.slice(0, -1) + "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"[lastValue | 1];
  for (const invalid of [null, {}, "", "#", "abc", "A".repeat(401), `${valid}=`, `%23${valid}`, `${valid}\n`, `${valid}0`]) {
    assert.throws(() => decodePartyFragment(invalid), /invalid|incomplete/i, String(invalid).slice(0, 20));
  }
  if (noncanonical !== valid) assert.throws(() => decodePartyFragment(noncanonical), /invalid|damaged/i);
});

test("rejects damage, other formats, team sizes and trailing bytes", () => {
  const corrupt = payload();
  corrupt[8] ^= 1;
  assert.throws(() => decodePartyFragment(link(corrupt)), /damaged/);
  assert.throws(() => decodePartyFragment(link(payload({ format: 3 }))), /newer format/);
  assert.throws(() => decodePartyFragment(link(payload({ format: 1 }))), /older test build/);
  assert.throws(() => decodePartyFragment(link(payload({ members: Array(7).fill(defaultMember) }))), /team size/);
  assert.throws(() => decodePartyFragment(link(payload({ extraByte: true }))), /invalid data/);
});

test("rejects invalid Pokémon fields and impossible header values", () => {
  for (const partial of [{ species: 0 }, { level: 0 }, { nature: 25 }, { gender: 3 }, { dynamaxLevel: 11 }, { statMultiplier: 0 }]) {
    assert.throws(() => decodePartyFragment(link(payload({ members: [partial] }))), /invalid Pokémon data/, JSON.stringify(partial));
  }
  assert.throws(() => decodePartyFragment(link(payload({ members: [{ nickname: Array(13).fill(187) }] }))), /invalid data/);
  for (const header of [{ difficulty: 3 }, { newGamePlus: 3 }, { badges: 9 }, { playMinutes: 60 }, { playHours: 1000 }]) {
    assert.throws(() => decodePartyFragment(link(payload({ header }))), /invalid data/, JSON.stringify(header));
  }
});

test("computes stats with the game's formula, nature, hyper training and held-item multiplier", () => {
  const garchomp = dictionary.species[445];
  const jolly = dictionary.natures[13];
  const member = { level: 100, ivs: [31, 31, 31, 31, 31, 31], evs: [0, 252, 4, 252, 0, 0], hyperTrained: 0, statMultiplier: 1, friendship: 255 };
  assert.deepEqual(computeStats(member, garchomp, jolly, false), [357, 359, 227, 333, 176, 206]);
  assert.deepEqual(computeStats({ ...member, ivs: [0, 0, 0, 0, 0, 0], hyperTrained: 63 }, garchomp, jolly, false), [357, 359, 227, 333, 176, 206]);
  assert.equal(computeStats({ ...member, statMultiplier: 2 }, garchomp, jolly, false)[0], 573);
  assert.equal(computeStats(member, { ...garchomp, constant: "SPECIES_SHEDINJA" }, jolly, false)[0], 1);
  assert.equal(computeStats(member, garchomp, jolly, true)[1], 359 + Math.floor(359 * 10 * 255 / 25500));
});

test("describes the team with trainer context, innate unlock levels, Hidden Power and Showdown order", () => {
  const view = describeParty(decodePartyFragment(link(payload({ header: { source: 1, newGamePlus: 1, badges: 1 } }))), dictionary);
  assert.equal(view.title, "Kris’s Hall of Fame team");
  assert.equal(view.mode, "NG+ Standard (Hard)");
  assert.equal(view.playTime, "42:07");
  const [pikachu] = view.members;
  assert.deepEqual(pikachu.innates.map(innate => [innate.name, innate.unlocked, innate.unlockLevel]), [["Lightning Rod", true, 75], ["Surge Surfer", false, 95]]);
  assert.deepEqual(pikachu.stats.map(stat => stat.name), ["HP", "Atk", "Def", "SpA", "SpD", "Spe"]);
  assert.deepEqual(pikachu.stats.map(stat => stat.nature), [0, -1, 0, 0, 0, 1]);
  assert.equal(pikachu.moves[1].type.name, "Flying");
  const exported = formatPartyExport(view);
  assert.equal(exported.paste, [
    "Pikachu (F) @ Light Ball", "Ability: Static", "Level: 50", "Shiny: Yes", "Happiness: 200", "Pokeball: Poke Ball",
    "Tera Type: Fire", "EVs: 4 HP / 252 SpA / 252 Spe", "Timid Nature",
    "IVs: 31 HP / 31 Atk / 29 Def / 27 SpA / 31 SpD / 28 Spe", "Hidden Power: Flying",
    "- Thunderbolt", "- Hidden Power [Flying]", "- Return", "- Protect", "",
  ].join("\r\n"));
  assert.match(exported.notes, /by Kris: Hall of Fame team, NG\+ Standard \(Hard\), 1 badge, 42:07 played/);
  assert.match(exported.notes, /Lightning Rod \(unlocked\), Surge Surfer \(locked until Lv 95\)/);
  assert.match(exported.notes, /Original IVs: 31 HP \/ 30 Atk \/ 29 Def \/ 27 SpA \/ 26 SpD \/ 28 Spe/);
  assert.equal(exported.title, "Kris’s Soulgold v1.2.3 Hall of Fame team");
  assert.equal(exported.author, "Kris");
});

test("Hidden Power uses raw IVs even when every effective IV is 31", () => {
  const view = describeParty(decodePartyFragment(link(payload({ members: [{ ivs: [0, 0, 0, 0, 0, 0], hyperTrained: 63 }] }))), dictionary);
  const exported = formatPartyExport(view);
  assert.match(exported.paste, /IVs: 31 HP \/ 31 Atk \/ 31 Def \/ 31 SpA \/ 31 SpD \/ 31 Spe/);
  assert.match(exported.paste, /Hidden Power: Fighting/);
  const highest = describeParty(decodePartyFragment(link(payload({ members: [{ ivs: [31, 31, 31, 31, 31, 31], hyperTrained: 0 }] }))), dictionary);
  assert.match(formatPartyExport(highest).paste, /Hidden Power: Fairy/);
});

test("omits empty moves, item, gender, EVs, Tera and the unused Dynamax level without inventing data", () => {
  const view = describeParty(decodePartyFragment(link(payload({ members: [{
    species: 201, item: 0, moves: [1, 0, 0, 0], gender: 0, gigantamax: true, evs: [0, 0, 0, 0, 0, 0], dynamaxLevel: 0,
    teraType: 0, hyperTrained: 0, unlockedInnates: 0, ball: 1,
  }] }))), dictionary);
  const exported = formatPartyExport(view);
  assert.ok(exported.paste.startsWith("Unown\r\n"));
  assert.match(exported.paste, /Gigantamax: Yes/);
  assert.doesNotMatch(exported.paste, /EVs:|Tera Type:|Dynamax|Hidden Power| @ |\(M\)|\(F\)/);
  assert.equal(exported.paste.match(/^- /gm).length, 1);
  assert.doesNotMatch(exported.notes, /Innates:|Original IVs:/);
});

test("unknown IDs degrade to labelled placeholders instead of hiding the whole team", () => {
  const view = describeParty(decodePartyFragment(link(payload({ members: [{ species: 999, item: 999, ability: 999, moves: [999, 0, 0, 0], teraType: 31, ball: 50 }] }))), dictionary);
  const [member] = view.members;
  assert.equal(member.speciesName, "Unknown species #999");
  assert.equal(member.item.name, "Unknown item #999");
  assert.equal(member.ability.name, "Unknown ability #999");
  assert.equal(member.moves[0].name, "Unknown move #999");
  assert.equal(member.teraType.name, "Unknown Tera Type #31");
  assert.equal(member.ball, null);
  assert.equal(member.stats[0].value, null);
  assert.match(formatPartyExport(view).paste, /^Unknown species #999 \(F\) @ Unknown item #999/);
});

test("validates dictionary identity, schema, names and tables", () => {
  assert.equal(validateDictionary(dictionary, DATA_ID), dictionary);
  const broken = [
    null, { ...dictionary, format: 1 }, { ...dictionary, id: "ffffffff" }, { ...dictionary, romVersion: null },
    { ...dictionary, species: [] }, { ...dictionary, species: { 25: { ...dictionary.species[25], innates: [1, 2, 3, 4] } } },
    { ...dictionary, species: { 25: { ...dictionary.species[25], stats: [1, 2, 3] } } },
    { ...dictionary, items: { 1: { name: "Injected\n- Earthquake", constant: "ITEM_X" } } }, { ...dictionary, items: { "01": named("Item", "ITEM_X") } },
    { ...dictionary, items: { 1: { name: "Item", constant: "<img>" } } },
    { ...dictionary, charset: { 187: "AB" } }, { ...dictionary, moves: { 1: { ...named("Thunderbolt", "MOVE_THUNDERBOLT") } } },
    { ...dictionary, hiddenPowerMoveId: 55 }, { ...dictionary, hiddenPowerTypes: [11] },
    { ...dictionary, hiddenPowerTypes: [11, 11] }, { ...dictionary, hiddenPowerTypes: [11, 999] },
    { ...dictionary, friendshipStatBoost: "no" },
  ];
  for (const invalid of broken) assert.throws(() => validateDictionary(invalid, DATA_ID), /invalid or incompatible/);
});

test("slugs and pasted links follow the docs routes and accept scanned test URLs", () => {
  assert.equal(routeSlug("MOVE_WILL_O_WISP", "MOVE_"), "will-o-wisp");
  assert.equal(routeSlug("ABILITY_AS_ONE_ICE_RIDER", "ABILITY_"), "as-one-ice-rider");
  assert.equal(fragmentFromText("http://192.168.1.20:8000/party/#ABCDEF234567"), "ABCDEF234567");
  assert.equal(fragmentFromText("  abcdef  "), "abcdef");
  assert.equal(fragmentFromText("https://pokepast.es/1234abcd"), null);
});

class Node {
  constructor(tagName, document) {
    this.tagName = tagName;
    this.ownerDocument = document;
    this.children = [];
    this.attributes = {};
    this.listeners = {};
    this.hidden = false;
    this.value = "";
    this.className = "";
    this.dataset = {};
    this._text = undefined;
  }
  get textContent() { return this._text ?? this.children.map(child => child.textContent).join(""); }
  set textContent(value) { this._text = String(value); this.children = []; }
  set innerHTML(_value) { throw new Error("Unsafe DOM HTML write"); }
  setAttribute(name, value) { this.attributes[name] = String(value); if (name === "src") this.src = String(value); if (name === "href") this.href = String(value); }
  getAttribute(name) { return this.attributes[name] ?? null; }
  append(...nodes) { this._text = undefined; this.children.push(...nodes); }
  replaceChildren(...nodes) { this._text = undefined; this.children = [...nodes]; }
  addEventListener(name, listener) { this.listeners[name] = listener; }
  focus() { this.focused = true; }
  select() { this.selected = true; }
  click() { this.clicked = true; }
  findAll(predicate) { return this.children.flatMap(child => child instanceof Node ? [...(predicate(child) ? [child] : []), ...child.findAll(predicate)] : []); }
}

function browser(hash = `#${link(payload())}`, fetchData = async url => ({
  ok: true, json: async () => (url.includes("party-links") ? { species: { SPECIES_PIKACHU: ["pikachu", "sprites/pokemon/pikachu.png"] }, items: { ITEM_LIGHT_BALL: ["light-ball", "sprites/items/light_ball.png"] } } : dictionary),
})) {
  const elements = new Map();
  const document = {
    title: "Soulgold team · Soulgold Documentation",
    baseURI: "https://example.test/soulgold/",
    documentElement: { dataset: { theme: "dark" } },
    createElement: tag => new Node(tag, document),
    createTextNode: text => ({ textContent: text }),
    getElementById: id => {
      if (!elements.has(id)) elements.set(id, new Node("div", document));
      return elements.get(id);
    },
    querySelector: () => ({ getAttribute: () => "abc123" }),
  };
  const writes = [];
  const timers = new Map();
  const window = {
    location: { href: `https://example.test/soulgold/party/${hash}`, hash },
    navigator: { clipboard: { writeText: async text => { writes.push(text); } } },
    localStorage: { setItem() {} },
    setTimeout(callback) { const id = Symbol(); timers.set(id, callback); return id; },
    clearTimeout(id) { timers.delete(id); },
    listeners: {}, addEventListener(name, listener) { this.listeners[name] = listener; },
  };
  const requests = [];
  const mounted = mountPartyExport({ document, window, fetch: async (...args) => {
    requests.push(args); return fetchData(...args);
  } });
  const get = id => document.getElementById(id);
  return { ...mounted, document, window, get, requests, writes, timers };
}

test("empty and invalid links never fetch and keep the loader visible", async () => {
  for (const hash of ["", "#", "#invalid"]) {
    const app = browser(hash);
    await app.initialLoad;
    assert.equal(app.requests.length, 0);
    assert.equal(app.get("partyView").hidden, true);
    assert.equal(app.get("partyIntro").hidden, false);
    assert.notEqual(app.get("partyStatus").textContent, "");
  }
});

test("loads the exact dictionary and link index, renders the team and sends no publish request", async () => {
  const app = browser();
  await app.initialLoad;
  await new Promise(resolve => setImmediate(resolve));
  assert.deepEqual(app.requests.map(([url]) => url), [
    `https://example.test/soulgold/data/party-export/${DATA_ID}.json`,
    "https://example.test/soulgold/data/party-links.json?v=abc123",
  ]);
  assert.ok(app.requests.every(([, options]) => options.credentials === "omit"));
  assert.equal(app.get("partyView").hidden, false);
  assert.equal(app.get("partyIntro").hidden, true);
  assert.equal(app.get("partyHeading").textContent, "Kris’s team");
  assert.equal(app.document.title, "Kris’s team · Soulgold");
  const cards = app.get("partyMembers").children;
  assert.equal(cards.length, 1);
  const hrefs = cards[0].findAll(node => node.href).map(node => node.href);
  assert.ok(hrefs.includes("pokedex/pikachu/"));
  assert.ok(hrefs.includes("items/light-ball/"));
  assert.ok(hrefs.includes("moves/thunderbolt/"));
  assert.ok(hrefs.includes("abilities/static/"));
  assert.ok(cards[0].findAll(node => node.src === "sprites/pokemon/pikachu_shiny.png").length > 0);
  assert.match(app.get("partyMeta").textContent, /Hard/);
  assert.match(app.get("partyPaste").value, /Pikachu/);
  app.get("partyPaste").value = "Edited team";
  await app.get("partyCopy").listeners.click();
  await app.get("partyCopyLink").listeners.click();
  assert.deepEqual(app.writes, ["Edited team", app.window.location.href]);
  let prevented = false;
  app.get("partyForm").listeners.submit({ preventDefault() { prevented = true; } });
  assert.equal(prevented, false);
  app.get("partyPaste").value = " \n";
  app.get("partyForm").listeners.submit({ preventDefault() { prevented = true; } });
  assert.equal(prevented, true);
});

test("a missing link index still renders the team without docs links", async () => {
  const app = browser(undefined, async url => (url.includes("party-links") ? { ok: false } : { ok: true, json: async () => dictionary }));
  await app.initialLoad;
  assert.equal(app.get("partyView").hidden, false);
  const hrefs = app.get("partyMembers").children[0].findAll(node => node.href).map(node => node.href);
  assert.ok(!hrefs.some(href => href.startsWith("pokedex/")));
  assert.ok(hrefs.includes("moves/thunderbolt/"));
});

test("a stalled optional index does not block the team and late links preserve edited export text", async () => {
  let respond;
  const app = browser(undefined, url => url.includes("party-links")
    ? new Promise(resolve => { respond = resolve; })
    : Promise.resolve({ ok: true, json: async () => dictionary }));
  assert.equal(app.get("partyIntro").hidden, true);
  await app.initialLoad;
  assert.equal(app.get("partyView").hidden, false);
  assert.equal(app.get("partyMembers").children.length, 1);
  assert.equal(app.timers.size, 0);
  app.get("partyPaste").value = "Edited while links load";
  respond({ ok: true, json: async () => ({ species: { SPECIES_PIKACHU: ["pikachu", "sprites/pokemon/pikachu.png"] } }) });
  await new Promise(resolve => setImmediate(resolve));
  assert.ok(app.get("partyMembers").children[0].findAll(node => node.href === "pokedex/pikachu/").length);
  assert.equal(app.get("partyPaste").value, "Edited while links load");
});

test("slow game data offers retry without aborting the original download or showing the intro", async () => {
  let respond;
  const app = browser(undefined, url => url.includes("party-links")
    ? Promise.resolve({ ok: false })
    : new Promise(resolve => { respond = resolve; }));
  for (const callback of app.timers.values()) callback();
  assert.equal(app.get("partyIntro").hidden, true);
  assert.equal(app.get("partyView").hidden, true);
  assert.equal(app.get("partyRetry").hidden, false);
  assert.match(app.get("partyStatus").textContent, /keep waiting/);
  assert.equal(app.requests[0][1].signal.aborted, false);
  respond({ ok: true, json: async () => dictionary });
  await app.initialLoad;
  assert.equal(app.get("partyView").hidden, false);
  assert.equal(app.get("partyRetry").hidden, true);
  assert.equal(app.timers.size, 0);
});

test("transient network and server failures retry once and recover without reloading", async () => {
  for (const failure of [
    () => { throw new TypeError("connection reset"); },
    () => ({ ok: false, status: 503 }),
    () => ({ ok: true, json: async () => { throw new TypeError("body interrupted"); } }),
  ]) {
    let attempts = 0;
    const app = browser(undefined, async url => {
      if (url.includes("party-links")) return { ok: false };
      if (++attempts === 1) return failure();
      return { ok: true, json: async () => dictionary };
    });
    await app.initialLoad;
    assert.equal(attempts, 2);
    assert.equal(app.get("partyView").hidden, false);
  }
});

test("a failed load can be retried in place with the same party link", async () => {
  let offline = true;
  const app = browser(undefined, async url => {
    if (url.includes("party-links")) return { ok: false };
    if (offline) throw new TypeError("offline");
    return { ok: true, json: async () => dictionary };
  });
  await app.initialLoad;
  assert.equal(app.requests.filter(([url]) => url.includes("party-export/")).length, 2);
  assert.equal(app.get("partyRetry").hidden, false);
  offline = false;
  await app.get("partyRetry").listeners.click();
  assert.equal(app.get("partyView").hidden, false);
  assert.equal(app.get("partyRetry").hidden, true);
});

test("late optional links cannot restore a team after the URL changes", async () => {
  let respond;
  const app = browser(undefined, url => url.includes("party-links")
    ? new Promise(resolve => { respond = resolve; })
    : Promise.resolve({ ok: true, json: async () => dictionary }));
  await app.initialLoad;
  app.window.location.hash = "";
  await app.window.listeners.hashchange();
  respond({ ok: true, json: async () => ({ species: { SPECIES_PIKACHU: ["pikachu"] } }) });
  await new Promise(resolve => setImmediate(resolve));
  assert.equal(app.get("partyMembers").children.length, 0);
  assert.equal(app.get("partyView").hidden, true);
  assert.equal(app.timers.size, 0);
});

test("missing dictionaries and network failures keep the team hidden and offer retry", async () => {
  for (const failedFetch of [
    async () => ({ ok: false }),
    async () => { throw new TypeError("offline"); },
    async url => ({ ok: true, json: async () => (url.includes("party-links") ? {} : { ...dictionary, id: "ffffffff" }) }),
  ]) {
    const app = browser(undefined, failedFetch);
    await app.initialLoad;
    assert.equal(app.get("partyView").hidden, true);
    assert.equal(app.get("partyRetry").hidden, false);
    assert.match(app.get("partyStatus").className, /error/);
  }
});

test("a stale dictionary response cannot restore a team after the URL changes", async () => {
  let respond;
  const app = browser(undefined, url => (url.includes("party-links") ? Promise.resolve({ ok: false }) : new Promise(resolve => { respond = resolve; })));
  app.window.location.hash = "";
  await app.window.listeners.hashchange();
  respond({ ok: true, json: async () => dictionary });
  await app.initialLoad;
  assert.equal(app.requests[0][1].signal.aborted, true);
  assert.equal(app.get("partyView").hidden, true);
  assert.equal(app.get("partyPaste").value, "");
  assert.match(app.get("partyStatus").textContent, /scan the QR code/);
});

test("pasted links open through the URL fragment and clipboard denial selects the text", async () => {
  const app = browser("");
  await app.initialLoad;
  app.get("partyLinkInput").value = `http://192.168.1.20:8000/party/#${link(payload())}`;
  app.get("partyLinkForm").listeners.submit({ preventDefault() {} });
  assert.equal(app.window.location.hash, link(payload()));
  app.get("partyLinkInput").value = "https://pokepast.es/abc";
  app.get("partyLinkForm").listeners.submit({ preventDefault() {} });
  assert.match(app.get("partyStatus").className, /error/);

  const loaded = browser();
  await loaded.initialLoad;
  loaded.window.navigator.clipboard.writeText = async () => { throw new Error("denied"); };
  await loaded.get("partyCopy").listeners.click();
  assert.equal(loaded.get("partyPaste").selected, true);
  assert.match(loaded.get("partyStatus").textContent, /Copy is unavailable/);
});

test("decodes the beta golden record against its archived dictionary", () => {
  const dataId = "cc2a9518";
  const actual = JSON.parse(readFileSync(new URL(`../../../docs/src/data/party-export/${dataId}.json`, import.meta.url), "utf8"));
  const party = decodePartyFragment(link(withCrc([2, ...le32(parseInt(dataId, 16)), ...GOLDEN_BITS])));
  const view = describeParty(party, actual);
  const [member] = view.members;
  assert.equal(view.title, "Kris’s team");
  assert.equal(view.mode, "NG+ Standard (Hard)");
  assert.equal(member.nickname, "Washy");
  assert.equal(member.speciesName, "Rotom-Wash");
  assert.deepEqual(member.types.map(type => type.name), ["Electric", "Water"]);
  assert.equal(member.item.name, "Leftovers");
  assert.equal(member.ability.name, "Levitate");
  assert.equal(member.ball.name, "Dusk Ball");
  assert.deepEqual(member.moves.map(move => move.name), ["Thunderbolt", "Hydro Pump", "Volt Switch", "Will-O-Wisp"]);
  assert.equal(member.teraType.name, "Water");
  assert.ok(member.stats.every(stat => Number.isInteger(stat.value)));
  assert.equal(formatPartyExport(view).paste.split("\r\n")[0], "Washy (Rotom-Wash) @ Leftovers");
  assert.doesNotMatch(formatPartyExport(view).paste, /Dynamax/);
});
