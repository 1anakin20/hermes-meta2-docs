#!/usr/bin/env python3
"""Coaching page for the gyro scale-factor calibration - user-paced.

Nothing advances until you click. The previous version ran on a fixed clock and
outpaced the person holding the headset. Here each rotation is:

    instruction  ->  you click BEGIN when you are set
    3 2 1        ->  you perform the rotation inside the window
    settled      ->  you click CONTINUE

Only the action window is clock-driven, and it is deliberately generous: the
analysis finds the rotation from the gyro signal itself, not from the window
edges, so taking a second longer costs nothing.

Every timestamp is CLOCK_MONOTONIC on this machine, the same clock meta2_imu_log
writes into its CSV, so marks and samples align with no clock-skew reasoning.

The capture starts first and the steps only begin once meta2_stream_start() has
passed the health gate - a rotation during arming is not a measurement.

Serves on :8095.
"""
import json
import os
import re
import subprocess
import sys
import threading
import time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

HERE = os.path.dirname(os.path.abspath(__file__))
BIN = "/home/hermes/work/meta2lib/build/meta2_imu_log"
CSV = os.path.join(HERE, "gyro_cal.csv")
MARKS = os.path.join(HERE, "gyro_marks.txt")

CAPTURE_SECONDS = 400
COUNTDOWN = 3.0

# id, axis, headline, how to do it, action window seconds
STEPS = [
    dict(sid="REST0", axis="-", head="Hold the headset still",
         how="Both hands, arms relaxed, no rotation. This measures the gyro bias. "
             "Click BEGIN, then stay still until it says SETTLED.",
         act=8),

    dict(sid="Y1", axis="vertical", head="Turn 360 degrees - normal pace",
         how="Stand up. Hold the headset still against your chest. Pivot on your feet and "
             "turn ONE full circle to your right, in about 4 seconds. "
             "Finish facing the way you started, and stop moving.",
         act=8),

    dict(sid="Y2", axis="vertical", head="Turn 360 degrees - SLOW",
         how="Same full circle to your right, but take about 8 seconds. "
             "Start from a dead stop and end at a dead stop.",
         act=14),

    dict(sid="R1", axis="front-back", head="Steering-wheel turn 360 degrees - normal pace",
         how="Hold the headset out in front of you, cameras facing AWAY from you. "
             "Rotate it like a steering wheel, ONE full turn clockwise, in about 4 seconds. "
             "The headset spins in place - do not move your arms around.",
         act=8),

    dict(sid="R2", axis="front-back", head="Steering-wheel turn 360 degrees - SLOW",
         how="Same wheel turn, about 8 seconds. Start and end at a dead stop.",
         act=14),

    dict(sid="P1", axis="left-right", head="End-over-end turn 360 degrees - normal pace",
         how="Hold the headset with the cameras pointing to your RIGHT. "
             "Roll it end over end, ONE full turn, in about 4 seconds - like a wheel rolling "
             "forward, hands going over the top and back down.",
         act=8),

    dict(sid="P2", axis="left-right", head="End-over-end turn 360 degrees - SLOW",
         how="Same end-over-end turn, about 8 seconds. Start and end at a dead stop.",
         act=14),

    dict(sid="REST1", axis="-", head="Hold still - finishing",
         how="Hold the headset completely still while the recording closes out.",
         act=8),
]

S = dict(phase="waiting", step_i=-1, t0=None, log=[], live="", proc=None,
         note="Click START when you are standing at the headset with room to turn.",
         cd_end=0.0, act_start=0.0, act_end=0.0)
LOCK = threading.Lock()


def monotonic():
    return time.clock_gettime(time.CLOCK_MONOTONIC)


def run_capture_once():
    with LOCK:
        S["phase"] = "arming"
        S["note"] = ("Arming the device. It re-arms from a USB port reset until it passes the health "
                     "gate, and it may need several attempts. Hold the headset STILL. "
                     "Nothing will move until it says READY.")
    try:
        p = subprocess.Popen([BIN, CSV, str(CAPTURE_SECONDS), "gate=10"],
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             text=True, bufsize=1)
    except OSError as e:
        with LOCK:
            S["phase"] = "waiting"
            S["note"] = "could not start the capture: %s" % e
        return False

    ready = False
    mf = None
    try:
        for line in p.stdout:
            line = line.rstrip()
            with LOCK:
                S["log"].append(line)
                S["log"] = S["log"][-60:]
                if line.startswith("t="):
                    S["live"] = line
            if not ready and line.startswith("imu_log: mask="):
                ready = True
                with LOCK:
                    S["phase"] = "brief"
                    S["step_i"] = 0
                    S["t0"] = monotonic()
                    S["note"] = "Session is healthy. Follow the screen - it waits for you."
                # Open the marks file only once THIS session is known healthy.
                # Opening it before the gate passes let a failed retry erase a
                # finished session's step windows (it did, on 2026-10-25).
                if os.path.exists(MARKS):
                    prev = [l for l in open(MARKS) if l.strip() and not l.startswith("#")]
                    if prev:
                        keep = MARKS + ".%d.prev" % int(S["t0"])
                        os.replace(MARKS, keep)
                        print("previous marks kept at %s" % keep, flush=True)
                mf = open(MARKS, "w")
                mf.write("# step  axis        action_start_host_us  action_end_host_us\n")
                mf.write("# capture t0_host_us = %d\n" % int(S["t0"] * 1e6))
                mf.write("# capture seconds = %d\n" % CAPTURE_SECONDS)
                mf.flush()
        p.wait()
    finally:
        if mf:
            mf.close()
    with LOCK:
        if S["phase"] in ("brief", "countdown", "action", "rest"):
            S["phase"] = "done"
            S["note"] = "Recording finished. You can put the headset down."
            return True
        S["phase"] = "waiting"
        S["note"] = ("The device would not pass the health gate. Click START to try again. "
                     "If it keeps failing, unplug and replug the headset first.")
        return False


def start_capture():
    for _ in range(3):
        if run_capture_once():
            return


def action_timer(step_i, act_s):
    time.sleep(COUNTDOWN)
    with LOCK:
        if S["phase"] != "countdown" or S["step_i"] != step_i:
            return
        S["phase"] = "action"
        S["act_start"] = monotonic()
        # act_end has to exist the moment the window opens, or the on-screen
        # countdown reads 0 for the whole window (it was only set at close).
        S["act_end"] = S["act_start"] + act_s
    time.sleep(act_s)
    with LOCK:
        if S["phase"] != "action" or S["step_i"] != step_i:
            return
        S["phase"] = "rest"
        S["act_end"] = monotonic()
        st = STEPS[step_i]
        with open(MARKS, "a") as mf:
            mf.write("%-6s %-11s %16d %16d\n" %
                     (st["sid"], st["axis"], int(S["act_start"] * 1e6), int(S["act_end"] * 1e6)))
            mf.flush()


def begin_step():
    with LOCK:
        if S["phase"] != "brief" or not (0 <= S["step_i"] < len(STEPS)):
            return
        S["phase"] = "countdown"
        S["cd_end"] = monotonic() + COUNTDOWN
        i, act = S["step_i"], STEPS[S["step_i"]]["act"]
    threading.Thread(target=action_timer, args=(i, act), daemon=True).start()


def next_step():
    with LOCK:
        if S["phase"] != "rest":
            return
        S["step_i"] += 1
        if S["step_i"] >= len(STEPS):
            S["phase"] = "done"
            S["note"] = "All steps recorded. You can put the headset down."
            return
        S["phase"] = "brief"


PAGE = """<!doctype html><html><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Meta 2 - gyro calibration</title>
<style>
 body{font:18px/1.5 system-ui,sans-serif;background:#101418;color:#e8ecf1;margin:0;padding:28px}
 .wrap{max-width:820px}
 h1{font-size:20px;margin:0 0 2px}
 .sub{color:#8b98a5;font-size:14px;margin-bottom:20px}
 .card{background:#1a2129;border:1px solid #2b3540;border-radius:12px;padding:26px;margin-bottom:16px}
 .step{font-size:14px;letter-spacing:.16em;text-transform:uppercase;color:#7fd1c1}
 .head{font-size:40px;font-weight:800;margin:12px 0 10px;line-height:1.15}
 .how{font-size:21px;color:#c9d4de}
 .axis{display:inline-block;background:#243040;border-radius:6px;padding:3px 10px;font-size:14px;color:#9fd8ca;margin-top:12px}
 button{font-size:24px;padding:18px 40px;border-radius:10px;border:0;background:#7fd1c1;color:#0d1117;font-weight:800;cursor:pointer}
 .big{font-size:96px;font-weight:900;color:#7fd1c1;text-align:center;font-variant-numeric:tabular-nums;line-height:1}
 .live{font:13px/1.5 ui-monospace,monospace;color:#8fd8c8;margin-top:14px}
 .log{font:12px/1.45 ui-monospace,monospace;color:#7f8b98;white-space:pre-wrap;max-height:150px;overflow:auto}
 .warn{color:#e8b45c;font-size:16px;margin-top:10px}
</style></head><body><div class="wrap">
<h1>Meta 2 &mdash; gyro scale calibration</h1>
<div class="sub">Six full 360&deg; turns: three axes, two speeds. Nothing moves on its own &mdash; click when you are ready.</div>
<div class="card">
  <div class="step" id="sid">not started</div>
  <div class="head" id="head">Press START</div>
  <div class="how" id="how"></div>
  <div id="axis"></div>
  <div class="big" id="big"></div>
  <div class="live" id="live"></div>
  <div style="margin-top:20px"><button id="btn" onclick="act()">START</button></div>
</div>
<div class="card"><div class="step">capture</div><div class="log" id="log"></div></div>
<script>
let phase='waiting';
function act(){
  const url = phase==='waiting' ? '/start' : (phase==='brief' ? '/begin' : '/continue');
  fetch(url,{method:'POST'}).catch(function(){ fetch(url); });
}
async function poll(){
  try{
    const d = await (await fetch('/state')).json();
    phase = d.phase;
    document.getElementById('sid').textContent = d.sid;
    document.getElementById('head').innerHTML = d.head;
    document.getElementById('how').textContent = d.how;
    document.getElementById('axis').innerHTML = d.axis && d.axis!=='-' ? '<div class="axis">axis being tested: '+d.axis+'</div>' : '';
    document.getElementById('big').textContent = d.big;
    document.getElementById('live').textContent = d.live || '';
    document.getElementById('log').textContent = d.log.join('\\n');
    const b = document.getElementById('btn');
    if(phase==='waiting'){ b.textContent='START'; b.disabled=false; }
    else if(phase==='brief'){ b.textContent='BEGIN'; b.disabled=false; }
    else if(phase==='rest'){ b.textContent='CONTINUE'; b.disabled=false; }
    else if(phase==='arming'){ b.textContent='ARMING...'; b.disabled=true; }
    else if(phase==='countdown'||phase==='action'){ b.textContent=phase==='action'?'TURN NOW':'...'; b.disabled=true; }
    else { b.textContent='FINISHED'; b.disabled=true; }
  }catch(e){}
  setTimeout(poll, 150);
}
poll();
</script></div></body></html>"""


class H(BaseHTTPRequestHandler):
    def log_message(self, *a):
        pass

    def _send(self, body, ctype="text/html; charset=utf-8"):
        b = body.encode()
        self.send_response(200)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(b)))
        self.end_headers()
        self.wfile.write(b)

    def _route(self):
        path = self.path.split("?")[0]
        if path in ("/start", "/begin", "/continue"):
            if path == "/start":
                with LOCK:
                    already = S["phase"] != "waiting"
                if not already:
                    threading.Thread(target=start_capture, daemon=True).start()
            elif path == "/begin":
                begin_step()
            else:
                next_step()
            self._send(json.dumps({"ok": True}), "application/json")
            return True
        return False

    def do_GET(self):
        if self._route():
            return
        if self.path.startswith("/state"):
            with LOCK:
                i = S["step_i"]
                sid, head, how, axis, big, live = "not started", S["note"], "", "-", "", S["live"]
                if 0 <= i < len(STEPS) and S["phase"] in ("brief", "countdown", "action", "rest"):
                    st = STEPS[i]
                    sid = "step %d of %d  (%s)" % (i + 1, len(STEPS), st["sid"])
                    head, how, axis = st["head"], st["how"], st["axis"]
                    if S["phase"] == "brief":
                        big = ""
                    elif S["phase"] == "countdown":
                        big = "%.0f" % max(0.0, S["cd_end"] - monotonic())
                    elif S["phase"] == "action":
                        big = "%.0f" % max(0.0, S["act_end"] - monotonic())
                        how = st["how"] + "   (window closes in %ds - take your time, the "  \
                              "analysis finds the turn from the gyro itself)" % int(big)
                    else:
                        big = "SETTLED"
                body = json.dumps({"phase": S["phase"], "sid": sid, "head": head,
                                   "how": how, "axis": axis, "big": big, "live": live,
                                   "log": S["log"][-8:]})
            self._send(body, "application/json")
            return
        self._send(PAGE)

    def do_POST(self):
        if self._route():
            return
        self._send(json.dumps({"ok": False}), "application/json")


if __name__ == "__main__":
    if not os.path.exists(BIN):
        sys.exit("missing %s - build meta2lib first" % BIN)
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8095
    print("gyro coach on http://192.168.2.251:%d/  (csv=%s marks=%s)" % (port, CSV, MARKS))
    ThreadingHTTPServer(("0.0.0.0", port), H).serve_forever()
