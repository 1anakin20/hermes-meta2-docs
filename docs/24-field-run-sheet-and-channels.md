# 24. Field run sheet, and the three ways to get work onto the laptop

Written 2026-11-06. Situation: the headset travels with the Windows 11 laptop, the
agent's terminal backend is `server3`, and the headset is never attached to
`server3`. This document is (a) the kit, (b) the run sheet, (c) the measured state
of each channel between the two machines.

Labels: **[measured]** = a command was run here and its output backs the claim.
**[inferred]**. **[untested]** = proposed, not exercised.

---

## 24.1 The field kit

Built today on `server3`, provenance checked:

| | |
|---|---|
| Package | `meta2-field-20261106.zip`, **15,360,280 bytes** |
| sha256 | `06201538b5fbb6dab460bffcddd455f20605db82982e249d64b710a314ca9f1c` |
| Per-file manifest | `meta2-field-20261106/SHA256.txt` (inside the zip) |
| `meta2lib` | `6726541` — contains `#define META2_RGB_PAYLOAD_OFFSET 24` [measured: `git show 6726541`] |
| `meta2-demo-viewer` | `97bf28c` |
| Toolchain | `x86_64-w64-mingw32-gcc 14-posix`, Qt 6.8.2 `mingw_64`, static libusb, `-static-libgcc -static-libstdc++` [measured] |
| Binary timestamp | `meta2_capture_live.exe` 2026-11-06 08:31 [measured] |
| Served | `http://192.168.2.251:8093/meta2-field-20261106.zip` — `GET` returned **200** and the full 15,360,280 bytes [measured] |

**Why a new kit exists.** The kit shipped 2026-10-27 15:22 was built **51 minutes
before** the commit that moved the RGB payload from `offset+32` to `offset+24`.
That commit's own note says using `+32` "decodes every frame 8 bytes — four
pixels — late". The old kit is wrong for anything that reads RGB pixels. Do not
mix the two kits in one session.

Contents: `meta2-viewer.exe`, `meta2_capture_live.exe`, `meta2_imu_log.exe`,
`meta2_mono_bar.exe`, `meta2_rgb_color.exe`, `meta2_capture.exe`,
`meta2_mux_dump.exe`, `meta2_trailer_dump.exe`, Qt 6.8.2 runtime DLLs +
`platforms/qwindows.dll` + `styles/`, `arm_capture.txt`, `data/arm_*.txt`,
`driver/` (`meta2.inf`, `install-driver.ps1`, `install.ps1`, `usb-ports.ps1`),
`README.txt` with the run sheet below.

---

## 24.2 Run sheet

Full text is in `README.txt` inside the kit; this is the order and the reason.

1. **Driver state** — `driver\usb-ports.ps1`, then `driver\install-driver.ps1` if
   the device is not on WinUSB. USB 3 port only: the mono pair alone is 86.6 MB/s.
2. **Health check, every session, first** —
   `meta2_capture_live.exe arm_capture.txt 25 8 150 65536 noreset warm=7e muxasync=8 mux=1f muxhz=100 muxkeep gate tries=3 probe=2`
   Nominal from the measured Windows runs: mono ~87.3 MB/s, rgb ~55.3 MB/s, mono
   completeness 99.8 %, `host dropped bytes … total=0`. Any non-zero drop voids the
   run. Default rings are ~6.8 GB — shorten the window rather than shrinking rings.
3. **Coached IMU** — `meta2_imu_log.exe imu_<axis><angle>_<date>.csv 60 gate=10`.
   One row per IMU record on both clocks. Gyro scale and device tick rate come out
   of the same rotation.
4. **Mono photometry / bar** — `meta2_mono_bar.exe bar_test 10 gate=3`
   (`imu=<path>` to pair a pan rate with the frame it blurred; `raw` only if raw
   frames are wanted — 20 s of raw is 1.7 GB).
5. **Chroma coaching** — `meta2_rgb_color.exe red 12 csv=red.csv` (act on `READY`).
6. **Viewer** — `meta2-viewer.exe`.
7. **Offline** — `meta2_trailer_dump.exe`, `meta2_mux_dump.exe`.

Artefact budget, smallest first: health-check stdout (paste as text) → `.csv`
(hundreds of KB) → `.prof` (~2 MB per 10 s) → raw rings (GB, stays put).

Device hysteresis trap, unchanged: leave the headset powered and untouched for
20 minutes before a session; recovery has been observed at attempt 1, 3 and 5;
never unplug mid-session.

---

## 24.3 The channel problem, measured

The link is **one-way today**: `server3` cannot reach the laptop (`ip neigh` →
`192.168.2.243 FAILED`, TCP/22 closed, `ssh` → `No route to host`) [measured].
Historically the laptop reached `server3` directly (`last` shows `hermes …
192.168.2.243` sessions) [measured, historical]. Every option below is judged
against that asymmetry.

### A. HTTP pull from `server3` — works today, LAN-only

Verified: `GET http://192.168.2.251:8093/meta2-field-20261106.zip` → 200, full
byte count [measured]. Port 8090 is Beszel (wall-dashboard), so 8093 was chosen.

Covers: kit delivery, any artefact the agent produces. Does **not** cover: getting
captures back, and anything done away from the home LAN.

### B. SSH server on the laptop — the highest-value fix

If the laptop runs OpenSSH Server and is reachable, the agent can simply `ssh`
into it from the existing terminal tool: no Hermes config change, no restart, and
it covers both directions including running the capture tools on the laptop while
the user coaches. The laptop was previously reachable this way (a key exists at
`~/.ssh/id_ed25519_laptop`) [measured, historical].

Blocker today is purely reachability, not software. Options: be on the home LAN,
or a VPN (Tailscale/WireGuard — `server3` has neither installed [measured]), or a
router port forward (user-only action).

Scope note: this grants arbitrary execution on a personal machine, which conflicts
with the standing laptop rule (only `filmcraft-cli` without permission, no deletes
without asking). If we do this, it should be with an explicit, written scope.

### C. An MCP server on the laptop, with Hermes as the client

Grounded from Hermes' own MCP reference: Hermes has a native MCP client that reads
`mcp_servers` from `~/.hermes/config.yaml`, supports **stdio** (`command` +
`args`) and **HTTP** (`url` + optional `headers`) transports, registers tools as
`mcp_<server>_<tool>`, injects them into all platform toolsets, retries connection
5 times with backoff, and **requires an agent restart** to add or remove a server
(no hot reload) [measured from `references/native-mcp.md`].

Two things follow:

1. **VS Code is not the server.** VS Code is an MCP *client* — it consumes MCP
   servers. What would expose the laptop is a standalone MCP server running on it
   (a filesystem server, a shell server). "VS Code with MCP" alone does not open a
   path in. [The existence of editor-state MCP servers for VS Code is plausible but
   **[untested]** today: the search backend returned two empty result sets in a
   row and the Hermes docs site is blocked by the extract policy.]
2. **MCP's real advantage over SSH is scope.** A filesystem MCP server takes
   explicit allowed directories — e.g. one folder, `C:\Users\tomas\meta2-field`.
   That is a strictly narrower grant than an SSH session on a personal laptop, and
   it is the right shape for "hand me captures, give me the kit, don't see the rest
   of my machine." A shell MCP server would erase that advantage, so if we go this
   way it should be filesystem-scoped first and shell only if actually needed.

Blockers: the same reachability problem (the server must listen on an address
`server3` can dial), plus the config change lives on the **gateway host
`192.168.2.21`**, and `ssh` from `server3` to `.21` returns `Permission denied
(publickey,password)` [measured] — so this is a user action on the gateway, not
something the agent can do from here. A `url`-based server also needs the `mcp`
package's `mcp.client.streamable_http` support on the gateway; if it is missing the
server fails with ImportError [documented behaviour, not observed here].

Alternative that avoids the gateway config entirely: the `mcporter` hub skill
(catalog id `official/mcp/mcporter`) is a CLI for ad-hoc MCP calls from a terminal
[measured: present in the catalog, not installed]. Installed on `server3`, the
agent could call a laptop-hosted MCP server directly, no restart, no gateway edit.
**[untested]**.

### D. Hermes inside VS Code on the laptop (ACP) — the other direction

Hermes ships an ACP adapter (`hermes acp`), and ACP is stdio JSON-RPC: the editor
spawns the agent. VS Code via the ACP Client extension (publisher `formulahendry`)
or a manual `acp.agents` entry; verify first with `hermes acp --version` and
`hermes acp --check`. ACP binds the session to the editor's cwd, curates the
toolset for editor UX, and **must not be published on a port** — stdio only by
design [measured from `hermes-acp-ide-integration`].

This is not "the agent reaches the laptop" — it is **a second Hermes running on
the laptop**, with full tool access, sitting next to the headset. Its value: the
coding happens where the device is. Its cost: it is a separate profile, so it does
not inherit this session's memory or the `meta2-device-re` skill. It would need
`meta2-docs` cloned (it is pushed, so that is easy) and the skill copied deliberately.

---

## 24.4 Recommendation

Ranked by what actually unblocks a laptop-only day:

1. **Today: option A.** The kit is built, hashed and served. Download it while the
   laptop is on the home LAN, run the run sheet, paste the health-check output and
   the CSVs back. This works with zero new infrastructure and it is verified.
2. **Then: option B or C, chosen by scope, not by novelty.** If the goal is "the
   agent helps operate the device remotely", SSH on the laptop is the least work
   and the most capable — but it is a whole-machine grant. If the goal is "the
   agent helps with files on the laptop without seeing the machine", a
   filesystem-scoped MCP server on the laptop plus `mcp_servers.url` on the gateway
   (or `mcporter` on `server3`) is the better shape.
3. **ACP (option D) is worth doing for a different reason**: when the coding work
   itself needs the device in hand, a Hermes inside VS Code on the laptop is the
   right placement, with `meta2-docs` cloned there and the skill copied over.
4. **All three need a network path.** Tailscale (or WireGuard, or a router port
   forward) on both machines is the single change that makes B, C and D usable from
   anywhere. It is a user action.

---

## 24.5 Search backend status, today

`web_search` returned `success: true` with an **empty** result array twice in a row
today (queries about Hermes MCP docs). `web_extract` of
`https://hermes-agent.nousresearch.com/docs` was **blocked** with "URL targets a
private or internal network address". So the Hermes documentation was not
reachable through the web tools; the MCP and ACP facts above come from the locally
installed Hermes skills instead, which is why they are labelled measured.

This is the intermittent-empty behaviour recorded in `docs/23`, not a new failure.
It has not been fixed; it has been routed around by using local references, and
that routing is stated here rather than hidden.
