import assert from "node:assert/strict";
import { chromium } from "playwright";

const base = process.env.DOCS_TEST_URL || "http://127.0.0.1:8000/";
const browser = await chromium.launch({ headless: true });
try {
  for (const width of [1280, 390, 320]) {
    const page = await browser.newPage({ viewport: { width, height: 900 }, isMobile: width < 500, hasTouch: width < 500 });
    const errors = [];
    page.on("pageerror", (error) => errors.push(error.message));
    page.on("response", (response) => {
      if (response.status() >= 400) errors.push(`${response.status()} ${response.url()}`);
    });
    await page.goto(new URL("frontier/?q=heracross+choice+scarf", base).href);
    const pool = await (await page.request.get(new URL("data/frontier.json", base).href)).json();
    await page.waitForFunction(() => document.querySelectorAll(".frontier-set").length === 2);
    assert.equal(await page.locator("#frontierStatus").isHidden(), true);
    assert.match(await page.locator(".frontier-set").first().innerText(), /252 Spe/);
    assert.match(await page.locator(".frontier-set").first().innerText(), /IVs\s+0 SpA/);
    assert.match(await page.locator(".frontier-set").first().innerText(), /Jolly/);
    assert.match(await page.locator(".frontier-set").first().innerText(), /Speed\s+Lv 50 225 · Lv 100 442 with Choice Scarf/);
    assert.equal(await page.locator(".frontier-item").first().innerText(), "Choice Scarf");

    await page.locator(".frontier-set .ability-pill").first().click();
    await page.waitForSelector("#detailDialog[open]");
    await page.waitForFunction(() => document.querySelector("#modalTitle").textContent === "Moxie");
    assert.equal(await page.locator("#modalTitle").innerText(), "Moxie");
    await page.locator("#closeDialog").click();
    await page.waitForSelector("#frontier.active");
    assert.equal(await page.locator("#globalSearch").inputValue(), "heracross choice scarf");

    const setId = await page.locator(".frontier-set").first().getAttribute("data-set-id");
    await page.locator(".frontier-set-link").first().click();
    await page.waitForFunction(() => document.querySelectorAll(".frontier-set").length === 1);
    assert.equal(await page.locator(".frontier-set").getAttribute("data-set-id"), setId);
    await page.reload();
    await page.waitForSelector(".frontier-set");
    assert.equal(await page.locator(".frontier-set").count(), 1);

    await page.locator("#globalSearch").fill("slowbro quick draw");
    await page.waitForFunction(() => [...document.querySelectorAll(".frontier-set h3")].every((el) => el.textContent.toLowerCase().includes("slowbro")) && document.querySelectorAll(".frontier-set").length > 0);
    assert.match(await page.locator(".frontier-set").first().innerText(), /Quick Draw/);
    await page.locator("#globalSearch").fill("landorus choice scarf");
    await page.waitForFunction(() => document.querySelector(".frontier-set h3")?.textContent.toLowerCase().includes("landorus"));
    await page.locator(".frontier-set .species-link").first().click();
    await page.waitForSelector("#detailDialog[open]");
    await page.waitForFunction(() => document.querySelector("#modalTitle").textContent.includes("Landorus"));
    assert.match(await page.locator("#modalTitle").innerText(), /Landorus/);
    await page.locator("#closeDialog").click();
    await page.waitForSelector("#frontier.active");

    if (width === 1280) {
      const [legacyMoveSetId] = pool.sets.find(([, , , , , moves]) => moves.includes("MOVE_ANCIENT_POWER"));
      await page.locator("#globalSearch").fill(legacyMoveSetId);
      await page.waitForSelector('.frontier-set [data-move="MOVE_ANCIENT_POWER"]');
      await page.locator('.frontier-set [data-move="MOVE_ANCIENT_POWER"]').click();
      await page.waitForFunction(() => document.querySelector("#modalTitle").textContent.includes("Ancient Power"));
      await page.locator("#closeDialog").click();
      await page.waitForSelector("#frontier.active");
    }

    await page.locator("#globalSearch").fill("no-such-frontier-set");
    await page.waitForFunction(() => document.querySelector("#frontierStatus").textContent.startsWith("No Frontier"));
    assert.equal(await page.locator(".frontier-set").count(), 0);
    await page.locator("#globalSearch").fill("heracross choice scarf");
    await page.waitForSelector(".frontier-set");
    const dimensions = await page.evaluate(() => ({ scroll: document.documentElement.scrollWidth, client: document.documentElement.clientWidth }));
    assert.equal(dimensions.scroll, dimensions.client, `Horizontal overflow at ${width}px`);
    await page.screenshot({ path: `/tmp/frontier-${width}-dark.png`, fullPage: true });
    await page.locator("#themeToggle").click();
    await page.screenshot({ path: `/tmp/frontier-${width}-light.png`, fullPage: true });
    if (width < 500) await page.locator("#mobileMenuToggle").click();
    await page.locator('[data-tab="moves"]').click();
    await page.waitForSelector("#moves.active");
    if (width < 500) await page.locator("#mobileMenuToggle").click();
    await page.locator('[data-tab="frontier"]').click();
    await page.waitForSelector("#frontier.active .frontier-set");
    await page.waitForTimeout(500);
    assert.equal(await page.locator("#frontierStatus").isHidden(), true);
    assert.ok(await page.locator(".frontier-set").count() < pool.sets.length, "Frontier sets should render as the page scrolls");
    assert.deepEqual(errors, []);
    console.log(`Frontier search, links, details, navigation and layout passed at ${width}px`);
    await page.close();
  }
} finally {
  await browser.close();
}
