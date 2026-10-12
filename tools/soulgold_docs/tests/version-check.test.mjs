import assert from "node:assert/strict";
import test from "node:test";
import { compareVersions, parseVersion } from "../../../docs/src/assets/version-check.mjs";

test("accepts ROM versions with or without v and normalizes the label", () => {
  assert.equal(parseVersion("1.1.3").label, "v1.1.3");
  assert.equal(parseVersion("v1.1.3").label, "v1.1.3");
  assert.equal(parseVersion("v1.2.0-rc.1+build.007").label, "v1.2.0-rc.1+build.007");
});

test("accepts two-number versions as a zero patch release", () => {
  assert.equal(parseVersion("1.2").label, "v1.2");
  assert.equal(parseVersion("v1.2").label, "v1.2");
  assert.equal(parseVersion("v1.3-rc.1").label, "v1.3-rc.1");
  assert.equal(compareVersions(parseVersion("v1.2"), parseVersion("v1.2.0")), 0);
  assert.equal(compareVersions(parseVersion("v1.1.4"), parseVersion("v1.2")), -1);
  assert.equal(compareVersions(parseVersion("v1.2"), parseVersion("v1.2.1")), -1);
  assert.equal(compareVersions(parseVersion("v1.10"), parseVersion("v1.9.9")), 1);
  assert.equal(compareVersions(parseVersion("v1.2-rc.1"), parseVersion("v1.2")), -1);
});

test("rejects missing, malformed and unsafe values", () => {
  for (const value of [
    null, undefined, 113, {}, "", "v1", "1.", "1.1.", "v01.2", "1.1.3.0", "v01.1.3", "1.1.3-01",
    "1.1.3-rc..1", "1.1.3+", " 1.1.3", "1.1.3\n", "1.1.3 ", "V1.1.3",
    "<img src=x onerror=alert(1)>", "https://evil.example/", `1.1.3-${"a".repeat(100)}`,
  ]) {
    assert.equal(parseVersion(value), null, String(value));
  }
});

test("orders numeric versions correctly, including multi-digit releases", () => {
  for (const [older, newer] of [
    ["v1.1.2", "v1.1.3"], ["v1.1.9", "v1.1.10"], ["v1.9.9", "v1.10.0"],
    ["v1.99.99", "v2.0.0"], ["v0.9.0", "v1.0.0"],
    ["1.0.9007199254740992", "1.0.9007199254740993"],
  ]) {
    assert.equal(compareVersions(parseVersion(older), parseVersion(newer)), -1, `${older} < ${newer}`);
    assert.equal(compareVersions(parseVersion(newer), parseVersion(older)), 1, `${newer} > ${older}`);
  }
});

test("equal versions and build metadata do not trigger updates", () => {
  for (const [left, right] of [["v1.1.3", "1.1.3"], ["1.1.3+one", "v1.1.3+two"], ["1.1.3-rc.1", "1.1.3-rc.1"]]) {
    assert.equal(compareVersions(parseVersion(left), parseVersion(right)), 0);
  }
});

test("follows semantic prerelease precedence", () => {
  const ordered = ["1.0.0-alpha", "1.0.0-alpha.1", "1.0.0-alpha.beta", "1.0.0-beta", "1.0.0-beta.2", "1.0.0-beta.11", "1.0.0-rc.1", "1.0.0"];
  for (let i = 0; i < ordered.length; i++) {
    for (let j = 0; j < ordered.length; j++) {
      assert.equal(compareVersions(parseVersion(ordered[i]), parseVersion(ordered[j])), Math.sign(i - j));
    }
  }
});
