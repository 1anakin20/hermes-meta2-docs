# 23. Working without the Linux box and without the laptop

Written 2026-11-06. The situation this plans for: the agent's terminal backend is a
Linux box at home (`server3`), the headset has been plugged into that box, and the
user is working away with only a Windows 11 laptop. Today the laptop is not
available at all, so the plan has to say what is doable *now* and what is only
doable when the laptop is back.

Every claim below is labelled **[measured]** (a command was run and its output is
quoted or summarised), **[inferred]** (a conclusion drawn from measured facts), or
**[untested]** (a proposal that has not been exercised here). Do not treat an
`[untested]` line as a capability.

---

## 23.1 The connectivity picture, measured today

| Fact | Status |
|---|---|
| The agent's terminal backend is `ssh` to `server3`, Debian 13, kernel 6.12.111+deb13-amd64, user `hermes` | [measured] |
| That `ssh` session originates from **a home-LAN host** — the Hermes gateway host, not the laptop (`ss` shows one established `:22` connection from the gateway host; addresses deliberately not published) | [measured] |
| Therefore: **as long as this chat is alive, the agent's Linux-side work continues**, independent of where the laptop is or whether the laptop can reach home | [inferred, from the two facts above] |
| `server3` **cannot reach the laptop**: `ip neigh` shows `<laptop> … FAILED`, TCP/22 connect fails, `ssh` gives `No route to host` | [measured] |
| Historically the laptop *did* ssh to `server3` directly (`last` shows `hermes … <laptop>` sessions on Oct 16–17) — so the laptop→server3 direction works when the laptop is on the home LAN | [measured, historical] |
| `server3` has **no Tailscale, no WireGuard**; interfaces are one LAN address on `eno1` plus Docker bridges; the public egress address is not published | [measured] |
| A hairpin probe from `server3` to its own public address on port 22 failed. **Inconclusive** for the outside-in direction — NAT hairpinning commonly fails even when a port forward exists | [measured, inconclusive] |
| Port **8090 is now occupied by Beszel** (`/beszel serve --http=0.0.0.0:8090`, docker-proxy), part of the wall-dashboard stack. The old ad-hoc HTTP file server on 8090 is gone | [measured] |
| `8420` (Glance) and `22` are the other listeners on `0.0.0.0` | [measured] |
| Disk: `106G` total, `69G` used, **`36G` free** on `/` | [measured] |
| The headset is **not attached to `server3` right now** — `lsusb` lists only root hubs, no `2cfa:00f3` | [measured] |
| Cross-build toolchain present: `x86_64-w64-mingw32-gcc (GCC) 14-posix`; existing Windows build dirs `meta2lib/build-win`, `meta2-demo-viewer/build-win`, `build-win2` | [measured] |

**The structural consequence.** The link is **one-way**: the agent can produce
artefacts on `server3`, and the laptop must *pull* them; the agent cannot push to
the laptop, cannot run anything on it, and cannot read a capture the moment it
lands there. Every workflow below is built around that asymmetry.

---

## 23.2 Two lanes

### Lane A — available right now: no laptop, no headset

Everything here runs on `server3` against source trees and captures that already
exist. Nothing in Lane A is blocked by today's constraints.

| # | Task | Why it is unblocked | Output |
|---|---|---|---|
| A1 | **Decide Monado route A vs A′** from the cloned source at `~/work/monado-src` (`63f43c25`): the `xrt_tracking.h` interface, how the WMR driver feeds SLAM frames, the `drivers/remote` wire structs (`mndrmt3`), `u_device_setup_split_side_by_side`, and the curved-combiner AR driver already found in §21.4d | Source is on disk; no device needed | A written decision + the exact client-side spec we would have to implement for A′ |
| A2 | **Alignment/visor-projection protocol** (docs/22 is a 256-line design with no code yet): define what gets printed on the panel, what the cameras observe, what gets fitted, and build the **synthetic harness** that proves the fitting works before any real measurement | The protocol is geometry + code; the real measurement is what needs the headset | A runnable synthetic test that fails or passes before the device is available |
| A3 | **VIO input contract from existing captures**: define the dataset format (mono frames + mux IMU + trailer timestamps + calibration) and write the exporter against raw captures already on disk | Existing captures are sufficient; no new capture needed | A dataset + exporter that a Basalt-class tracker could consume, so the tracking phase is de-risked device-free |
| A4 | **Renderer prototype (option B)**: borderless-fullscreen 1440×2560 portrait, 72 Hz pacing, test pattern. Buildable and testable on Linux now; cross-buildable for Windows with the mingw toolchain that is present | Needs no headset to prove pacing, orientation and frame budget on a normal monitor | A small app + a measured frame-time histogram |
| A5 | **Docs hygiene**: the 60 Hz vs 72 Hz open item, decision 2a/2c status, `docs/14` project state | Pure documentation | Current state of the plan |

### Lane B — only when the laptop is back: device work on Windows

The proven Windows invocation (nominal rates measured on the physical Windows 11
machine: mono 87.3 MB/s, rgb 55.3 MB/s, mono completeness 99.8 %, 88.5 complete
frames/s per camera) is:

```
meta2_capture_live.exe arm_capture.txt 25 8 150 65536 noreset warm=7e muxasync=8 mux=1f muxhz=100 muxkeep gate tries=3 probe=2
```

Lane B is therefore **not a porting problem** — it is a *staging and transfer*
problem, and staging is Lane A work.

---

## 23.3 The staging problem, measured today

The staged Windows packages on disk are **stale**:

| Artefact | Timestamp | Problem |
|---|---|---|
| `scratch/meta2lib-windows.zip` (2.04 MB, sha256 `a684b40679de48e6…`) | 2026-10-27 15:22 | Predates `meta2lib 6726541` *"RGB payload begins at offset+24, not offset+32"* (2026-10-27 16:13) — **the shipped binary has the wrong RGB payload offset** [measured] |
| `scratch/meta2-viewer-win-97bf28c.zip` (13.1 MB, sha256 `d97a39c849704370…`) | 2026-10-27 20:29 | Matches viewer HEAD `97bf28c`, but links a `meta2lib` that predates the offset fix unless it was rebuilt against it [unverified] |

So the first Lane-B-prep action is: **rebuild both Windows binaries from current
HEADs and re-stage them with hashes**, before the laptop is ever needed.

---

## 23.4 Transfer options, ranked by how much setup they need

Because the agent cannot reach the laptop, files move by the laptop pulling.

1. **Pull while at home (recommended for today).** Stage the kit on `server3`,
   serve it over HTTP on a **new** port (8090 is Beszel now), download it on the
   laptop while the laptop is on the home LAN, verify sha256, leave. Zero new
   infrastructure. [measured that the LAN path exists; the specific port choice is
   [untested]]
2. **Return path for captures.** The laptop pulls, and later *pushes* captures back
   with `scp`/`rsync` to `server3:22` when it is back on the LAN — that direction is
   proven historically. Capture windows are GB-scale (a 25 s full-mask window is
   ~5.3 GB of ring data), so the return policy should be: keep the small derived
   artefacts (mux records, pose CSV, health/gate JSON, selected raw windows) and
   discard the rest, rather than shipping whole rings. [measured sizes; policy is a
   proposal]
3. **Tailscale (or WireGuard) on `server3` + laptop.** The durable fix for
   away-from-home file transfer. `server3` has neither today, and it needs an
   account plus an install on both machines — a user action, not an agent action.
   [untested]
4. **Cloudflare quick tunnel** on `server3` (`cloudflared tunnel --url …`) to get a
   public HTTPS URL with no account, `cloudflared access` on the laptop. Plausible,
   not exercised here, and it puts a home box on the public internet — the user's
   call, not mine. [untested]
5. **Router port-forward to `server3`.** User-only action on the router. The
   hairpin probe today could not confirm or deny an existing forward. [untested]

**Do not** assume any away-from-home path works until it has been used once for a
real file with a hash check.

---

## 23.5 What today's session should actually do

Given: laptop unavailable, headset not on `server3`.

1. **A1 first** — it is the decision that gates the whole OpenXR phase, and it is
   pure source reading on a repo already cloned.
2. **A3 in parallel** — the VIO input contract is the other gate, and it is pure
   offline work against captures we already have.
3. **A4 as the visible-progress item** — a 72 Hz portrait pacing prototype is
   something the user can see and measure, and it needs no device.
4. **Lane-B staging** — rebuild and hash the Windows kit so that the moment the
   laptop is back, the session is a download-and-run, not a build.

What today **cannot** include: any coached test, any visor measurement, any new
capture, any ToF emitter work, and anything requiring the headset's HDMI to be on a
specific machine.

---

## 23.6 Open items this playbook does not resolve

- Whether the laptop can reach home from away, and by what path — unmeasured, and
  the hairpin test was inconclusive.
- Whether the headset travels with the laptop or stays home. That single answer
  decides whether Lane B is even possible today.
- 60 Hz vs 72 Hz (EDID says 72 Hz, external spec says 60 Hz). Pacing target is
  recorded as 72 Hz with runtime mode query, per decision 2b.
- Whether `meta2-viewer-win-97bf28c.zip` was linked against a `meta2lib` that
  contains the RGB offset fix.
