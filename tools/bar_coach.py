#!/usr/bin/env python3
"""Target page for the mono-pair exposure-lock test (docs/15 item 2).

Two targets, one page, both driven off the display's own vsync so the timing is
known without trusting any host clock:

  seq   a bright/dark random sequence, one decision per displayed frame.
        This is the one that MEASURES the offset. Each mono camera integrates the
        screen over its own exposure window, so a frame that straddles a
        bright/dark boundary comes out at an intermediate level. Fitting each
        camera's brightness sequence against the commanded sequence recovers that
        camera's exposure phase, and the difference between the two cameras is
        the exposure offset. It is global, so fisheye distortion and the 83 deg
        between the cameras do not matter at all.

  bar   a bar that jumps STEP rows per displayed frame. This one does NOT give a
        clean cross-camera offset: each camera maps a screen row to an image row
        differently, and that static warp bias is the same size as the effect
        being looked for. What it does give, cleanly, is the SHUTTER MODEL - a
        rolling sensor smears a sweeping bar into a slanted band, a global sensor
        keeps it horizontal - and that decides how the seq result must be read.

Nothing advances until the operator clicks START.

Files written next to the server's working directory:
  bar_timeline.csv   displayed-frame index -> page clock, as reported by the page
  bar_state.json     run parameters and status
"""

import json
import os
import sys
import time
import threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8095
DIR = os.environ.get("COACH_DIR", os.path.dirname(os.path.abspath(__file__)))
TIMELINE = os.path.join(DIR, "bar_timeline.csv")
STATE = os.path.join(DIR, "bar_state.json")

LOCK = threading.RLock()
S = {
    "phase": "waiting",          # waiting | countdown | running | done
    "mode": "seq",               # seq | bar
    "seconds": 20,
    "step": 24,                  # bar: rows per displayed frame
    "bar_px": 10,                # bar thickness in CSS px
    "seed": 1,                   # seq: LCG seed, reproducible in analysis
    "note": "Put a monitor directly in front of the headset, headset on a table "
            "facing it, nothing else in view. Then click START.",
    "started_at": None,
    "frames": 0,                 # displayed frames reported by the page
    "page_fps": 0.0,
    "screen_h": 0,
    "posted_at": None,
    "wall_epoch": None,          # wall-clock time the page's performance.now()=0
}

LCG_A = 1103515245
LCG_C = 12345


def sequence(seed, n):
    """The commanded bright/dark pattern, identical to the page's JS."""
    x = seed & 0xFFFFFFFF
    out = []
    for _ in range(n):
        x = (LCG_A * x + LCG_C) & 0xFFFFFFFF
        out.append((x >> 16) & 1)
    return out


PAGE = """<!doctype html>
<meta charset=utf-8><title>meta2 exposure target</title>
<style>
 html,body{margin:0;padding:0;background:#000;color:#eee;
           font:16px/1.4 system-ui,sans-serif}
 #wrap{display:flex;flex-direction:column;height:100vh}
 #ui{padding:22px;max-width:46rem}
 #cv{flex:1;display:none;width:100%}
 button{font:inherit;padding:14px 26px;margin:6px 10px 6px 0;cursor:pointer}
 .big{font-size:26px;padding:18px 40px}
 code{background:#111;padding:2px 6px}
 #hud{position:fixed;right:10px;top:8px;font:13px ui-monospace,monospace;
      color:#666;display:none}
 label{display:inline-block;margin-right:16px}
</style>
<div id=wrap>
 <div id=ui>
  <h2>meta2 exposure target</h2>
  <p id=note></p>
  <p>
   <label>target
    <select id=mode>
     <option value=seq>bright/dark sequence &mdash; measures the offset</option>
     <option value=bar>sweeping bar &mdash; measures the shutter model</option>
    </select>
   </label>
   <label>seconds <input id=secs type=number value=20 min=5 max=120 style=width:5em></label>
   <label>rows / frame <input id=step type=number value=24 min=2 max=200 style=width:4em></label>
  </p>
  <p>
   <button id=start class=big>START</button>
   <button id=stop>STOP</button>
  </p>
  <p id=status>waiting</p>
  <p style=color:#888>START also goes fullscreen. The screen must fill the monitor,
     and the headset must be looking straight at it.</p>
 </div>
 <canvas id=cv></canvas>
 <div id=hud></div>
</div>
<script>
let i=0, run=false, t0=0, buf=[], raf=0, lastPost=0, mode='seq', step=24, secs=20;
let wallEpoch = 0;
const cv=document.getElementById('cv'), cx=cv.getContext('2d');
const hud=document.getElementById('hud');

function lcg(x){ return (Math.imul(1103515245, x) + 12345) >>> 0; }
/* Advance one step per displayed frame, so the page and the analysis walk the
   same sequence in the same order. Recomputing from the seed every frame would
   be O(n^2) over a run. */
let lcgState = 1, lcgAt = -1, lcgBit = 0;
function bit(seed, n){
  if (lcgAt !== n) {
    if (lcgAt < 0 || lcgAt > n) { lcgState = seed >>> 0; lcgAt = -1; }
    while (lcgAt < n) { lcgState = lcg(lcgState); lcgAt++; lcgBit = (lcgState >>> 16) & 1; }
  }
  return lcgBit;
}

function size(){ cv.width = window.innerWidth; cv.height = window.innerHeight; }
window.addEventListener('resize', size);

function draw(){
  const H = cv.height;
  if (mode === 'bar') {
    cx.fillStyle = '#000'; cx.fillRect(0,0,cv.width,H);
    const row = (i * step) % H;
    cx.fillStyle = '#fff';
    cx.fillRect(0, row, cv.width, Math.max(2, Math.round(H*0.012)));
  } else {
    cx.fillStyle = bit(SEED, i) ? '#fff' : '#000';
    cx.fillRect(0,0,cv.width,H);
  }
}

let SEED = 1;
function frame(){
  if (!run) return;
  i++;
  draw();
  buf.push([i, performance.now()]);
  const el=(performance.now()-t0)/1000;
  hud.textContent = 'frame '+i+'  fps '+(i/el).toFixed(2)+'  t '+el.toFixed(1)+'s';
  if (performance.now()-lastPost > 1000){ post(); lastPost=performance.now(); }
  if (el >= secs){ finish(); return; }
  raf = requestAnimationFrame(frame);
}

function post(){
  if (!buf.length) return;
  const body = JSON.stringify({frames: buf, fps: i/((performance.now()-t0)/1000),
                               h: cv.height});
  fetch('/timeline', {method:'POST', body}).catch(()=>{});
  buf = [];
}

function finish(){
  run=false; cancelAnimationFrame(raf); post();
  cx.fillStyle='#000'; cx.fillRect(0,0,cv.width,cv.height);
  fetch('/finish', {method:'POST', body:JSON.stringify({frames:i,
        fps:i/((performance.now()-t0)/1000), h:cv.height})}).catch(()=>{});
  if (document.fullscreenElement) document.exitFullscreen();
  document.getElementById('status').textContent = 'done: '+i+' displayed frames';
}

document.getElementById('start').onclick = async () => {
  mode = document.getElementById('mode').value;
  secs = parseInt(document.getElementById('secs').value, 10);
  step = parseInt(document.getElementById('step').value, 10);
  await fetch('/start', {method:'POST', body:JSON.stringify({mode, secs, step})});
  const r = await fetch('/state'); const s = await r.json();
  SEED = s.seed;
  try { await document.documentElement.requestFullscreen(); } catch(e) {}
  size();
  /* A countdown, so the capture tool and the page do not have to be started in
     lockstep. The operator starts the recorder, then clicks START, then has four
     seconds to put the headset down and step back. */
  document.getElementById('ui').style.display='none';
  cv.style.display='block'; hud.style.display='block';
  cx.fillStyle='#000'; cx.fillRect(0,0,cv.width,cv.height);
  cx.fillStyle='#fff'; cx.textAlign='center';
  cx.font = Math.round(cv.height*0.35) + 'px system-ui,sans-serif';
  const cd = performance.now() + 4000;
  await new Promise(res => {
    (function tick(){
      const left = (cd - performance.now())/1000;
      cx.fillStyle='#000'; cx.fillRect(0,0,cv.width,cv.height);
      if (left <= 0) { res(); return; }
      cx.fillStyle='#fff';
      cx.fillText(Math.ceil(left), cv.width/2, cv.height/2 + cv.height*0.12);
      requestAnimationFrame(tick);
    })();
  });
  i=0; buf=[]; lcgAt=-1; run=true; t0=performance.now(); lastPost=performance.now();
  wallEpoch = Date.now() - t0;
  fetch('/start2', {method:'POST', body:JSON.stringify({wall_epoch: wallEpoch/1000})})
    .catch(()=>{});
  raf = requestAnimationFrame(frame);
};
document.getElementById('stop').onclick = () => { if (run) finish(); };
document.getElementById('mode').onchange = e => { mode = e.target.value; };
size();
fetch('/state').then(r=>r.json()).then(s=>{
  document.getElementById('note').textContent = s.note;
  document.getElementById('status').textContent = s.phase;
});
</script>
"""


class H(BaseHTTPRequestHandler):
    def log_message(self, *a):
        pass

    def _send(self, code, body, ctype="text/html; charset=utf-8"):
        b = body.encode() if isinstance(body, str) else body
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(b)))
        self.end_headers()
        self.wfile.write(b)

    def do_GET(self):
        # /state must be matched before the catch-all: every path starts with "/".
        if self.path.startswith("/state"):
            with LOCK:
                self._send(200, json.dumps(S), "application/json")
        elif self.path.startswith("/sequence"):
            with LOCK:
                self._send(200, json.dumps({
                    "seed": S["seed"], "mode": S["mode"], "step": S["step"],
                    "seconds": S["seconds"], "fps": S["page_fps"],
                    "screen_h": S["screen_h"], "frames": S["frames"]}),
                    "application/json")
        elif self.path.startswith("/"):
            self._send(200, PAGE)
        else:
            self._send(404, "no")

    def _body(self):
        n = int(self.headers.get("Content-Length") or 0)
        try:
            return json.loads(self.rfile.read(n) or b"{}")
        except Exception:
            return {}

    def do_POST(self):
        d = self._body()
        # /start2 before /start: startswith("/start") also matches "/start2", and
        # matching it there silently restarted the run and discarded the epoch.
        if self.path.startswith("/start2"):
            with LOCK:
                S["wall_epoch"] = float(d.get("wall_epoch", 0))
                with open(STATE, "w") as f:
                    json.dump(S, f, indent=1)
                self._send(200, "ok", "text/plain")
        elif self.path.startswith("/start"):
            with LOCK:
                S["mode"] = d.get("mode", S["mode"])
                S["seconds"] = int(d.get("secs", S["seconds"]))
                S["step"] = int(d.get("step", S["step"]))
                S["seed"] = int(time.time()) & 0xFFFFFFFF
                S["phase"] = "running"
                S["started_at"] = time.time()
                S["frames"] = 0
                S["page_fps"] = 0.0
                with open(STATE, "w") as f:
                    json.dump(S, f, indent=1)
                with open(TIMELINE, "w") as f:
                    f.write("# frame_index,page_clock_ms,server_clock_s\n")
                self._send(200, json.dumps({"seed": S["seed"], "phase": "running"}),
                           "application/json")
        elif self.path.startswith("/timeline"):
            with LOCK:
                with open(TIMELINE, "a") as f:
                    for fi, t in d.get("frames", []):
                        f.write("%d,%.3f,%.6f\n" % (fi, t, time.time()))
                S["frames"] = d.get("frames", [[0, 0]])[-1][0]
                S["page_fps"] = float(d.get("fps", 0))
                S["screen_h"] = int(d.get("h", 0))
                S["posted_at"] = time.time()
                self._send(200, "ok", "text/plain")
        elif self.path.startswith("/finish"):
            with LOCK:
                S["phase"] = "done"
                fr = d.get("frames")
                if isinstance(fr, list) and fr:
                    S["frames"] = int(fr[-1][0])
                S["page_fps"] = float(d.get("fps", S["page_fps"]))
                S["screen_h"] = int(d.get("h", S["screen_h"]))
                with open(STATE, "w") as f:
                    json.dump(S, f, indent=1)
                self._send(200, "ok", "text/plain")
        else:
            self._send(404, "no")


if __name__ == "__main__":
    print("bar coach on :%d  (seq / bar)" % PORT, flush=True)
    ThreadingHTTPServer(("0.0.0.0", PORT), H).serve_forever()
