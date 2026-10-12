const downloadUrl = "https://www.hackdex.app/hack/soulgold";
const dismissalStorageKey = "soulgold-docs-dismissed-update";
let updateRequest = null;
let updateToast = null;

export function parseVersion(value) {
  if (typeof value !== "string" || value.length > 100) return null;
  const match = /^v?(0|[1-9]\d*)\.(0|[1-9]\d*)(?:\.(0|[1-9]\d*))?(?:-([0-9A-Za-z-]+(?:\.[0-9A-Za-z-]+)*))?(?:\+([0-9A-Za-z-]+(?:\.[0-9A-Za-z-]+)*))?$/.exec(value);
  if (!match || match[0] !== value) return null;
  const prerelease = match[4] ? match[4].split(".") : [];
  if (prerelease.some((part) => /^0\d+$/.test(part))) return null;
  return { label: `v${value.replace(/^v/, "")}`, core: [match[1], match[2], match[3] ?? "0"], prerelease };
}

function compareNumericStrings(left, right) {
  if (left.length !== right.length) return left.length < right.length ? -1 : 1;
  return left === right ? 0 : left < right ? -1 : 1;
}

export function compareVersions(left, right) {
  for (let i = 0; i < 3; i++) {
    const order = compareNumericStrings(left.core[i], right.core[i]);
    if (order) return order;
  }
  const a = left.prerelease;
  const b = right.prerelease;
  if (!a.length || !b.length) return a.length === b.length ? 0 : a.length ? -1 : 1;
  for (let i = 0; i < Math.max(a.length, b.length); i++) {
    if (a[i] === undefined) return -1;
    if (b[i] === undefined) return 1;
    if (a[i] === b[i]) continue;
    const aNumeric = /^\d+$/.test(a[i]);
    const bNumeric = /^\d+$/.test(b[i]);
    if (aNumeric && bNumeric) return compareNumericStrings(a[i], b[i]);
    if (aNumeric !== bNumeric) return aNumeric ? -1 : 1;
    return a[i] < b[i] ? -1 : 1;
  }
  return 0;
}

function readSession(key) {
  try {
    return sessionStorage.getItem(key);
  } catch {
    return null;
  }
}

function writeSession(key, value) {
  try {
    sessionStorage.setItem(key, value);
  } catch {}
}

function readRomVersion() {
  const values = new URL(window.location.href).searchParams.getAll("version");
  return values.length === 1 ? parseVersion(values[0]) : null;
}

function showUpdateToast(installed, latest, dismissalKey) {
  const toast = document.createElement("aside");
  toast.className = "rom-update-toast";
  toast.setAttribute("aria-label", "Soulgold update");

  const message = document.createElement("div");
  message.className = "rom-update-message";
  message.setAttribute("role", "status");
  message.setAttribute("aria-live", "polite");
  message.setAttribute("aria-atomic", "true");

  const close = document.createElement("button");
  close.className = "rom-update-close";
  close.type = "button";
  close.setAttribute("aria-label", "Dismiss update notice");
  close.textContent = "×";
  close.addEventListener("click", () => {
    writeSession(dismissalStorageKey, dismissalKey);
    toast.remove();
  });
  toast.append(message, close);
  document.body.append(toast);

  const title = document.createElement("strong");
  title.className = "rom-update-title";
  title.textContent = "Hey, you are behind in versions!";
  const versions = document.createElement("p");
  versions.textContent = `You're playing ${installed.label}. Latest: ${latest.label}.`;
  const action = document.createElement("p");
  const link = document.createElement("a");
  link.href = downloadUrl;
  link.target = "_blank";
  link.rel = "noopener noreferrer";
  link.textContent = "hackdex.app/hack/soulgold";
  action.append("Get the latest version from ", link, ".");
  const warning = document.createElement("p");
  warning.className = "rom-update-warning";
  warning.textContent = "All other download sites are fake.";
  message.append(title, versions, action, warning);
  return toast;
}

async function checkForRomUpdate() {
  updateRequest?.abort();
  updateToast?.remove();
  updateToast = null;
  const installed = readRomVersion();
  if (!installed) return;

  const controller = new AbortController();
  updateRequest = controller;
  const timeout = setTimeout(() => controller.abort(), 5000);
  try {
    const response = await fetch(new URL("../version.json", import.meta.url), {
      cache: "no-store",
      credentials: "omit",
      mode: "same-origin",
      redirect: "error",
      signal: controller.signal,
    });
    if (!response.ok) return;
    const manifest = await response.json();
    if (controller.signal.aborted || readRomVersion()?.label !== installed.label) return;
    const latest = parseVersion(manifest?.latestVersion);
    if (!latest || compareVersions(installed, latest) >= 0) return;
    const dismissalKey = `${installed.label}:${latest.label}`;
    if (readSession(dismissalStorageKey) === dismissalKey) return;
    updateToast = showUpdateToast(installed, latest, dismissalKey);
  } catch {} finally {
    clearTimeout(timeout);
    if (updateRequest === controller) updateRequest = null;
  }
}

if (typeof window !== "undefined") {
  window.addEventListener("docs:routechange", checkForRomUpdate);
  void checkForRomUpdate();
}
