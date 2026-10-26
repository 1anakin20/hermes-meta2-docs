#!/usr/bin/env python3
"""Colour coach: settle which YUV422 chroma phase is U and which is V.

User-paced, like the other coaches: nothing advances until you click. One capture
session covers BOTH colours, which matters - a colour shown in one session and a
colour shown in another are confounded by whatever exposure/gain the two sessions
landed on. Inside one session the only thing that changes is the screen.

Flow: START -> arming (gate attempts shown) -> hold RED -> BEGIN -> 3 2 1 -> 20 s
window -> CONTINUE -> hold BLUE -> BEGIN -> window -> CONTINUE -> verdict.

The live graph is the per-frame mean of the two chroma phases, straight from
meta2_rgb_color's CSV, so you can watch the two lines swap as you change the
screen. If they swap, the test worked; if they don't, the target was not saturated
or not in frame, and the page says so instead of guessing.
"""
import json
import os
import subprocess
import sys
import threading
import time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

BIN = os.environ.get("META2_RGB_BIN", "/home/hermes/work/meta2lib/build/meta2_rgb_color")
D = os.environ.get("COACH_DIR", "/home/hermes/work/metavision/re")
CSV = D + "/colour_cal.csv"
OUT = D + "/colour_results.txt"
LOG = D + "/colour_capture.log"
RAW = D + "/colour_windows.json"

CAPTURE_SECONDS = int(os.environ.get("COACH_WINDOW", "300"))
COUNT_S = int(os.environ.get("COACH_COUNT", "3"))
ACT_SECONDS = int(os.environ.get("COACH_ACT", "25"))
GATE = int(os.environ.get("COACH_GATE", "12"))

LOCK = threading.RLock()
PROC = None
S = {"phase": "waiting", "note": "Get the screen ready: full-screen RED and full-screen BLUE, "
     "switchable in one click. Then click START.", "log": [], "act_end": 0.0,
     "windows": [], "rows": 0, "graph": ""}


def read_rows():
    out = []
    try:
        with open(CSV) as f:
            for line in f:
                if not line or line[0] == "#" or line.startswith("host_s"):
                    continue
                p = line.split(",")
                if len(p) != 5:
                    continue
                try:
                    out.append((float(p[0]), int(p[1]), float(p[2]), float(p[3]), float(p[4])))
                except ValueError:
                    pass
    except OSError:
        pass
    return out


def svg_graph():
    rows = read_rows()
    if len(rows) < 4:
        return "<p class=muted>waiting for frames...</p>"
    now = time.monotonic()
    rows = [r for r in rows if now - r[0] < 90]
    if len(rows) < 4:
        return "<p class=muted>waiting for frames...</p>"
    W, H, PAD = 640, 190, 26
    t0, t1 = rows[0][0], rows[-1][0]
    if t1 - t0 < 1:
        t1 = t0 + 1
    vals = [r[2] for r in rows] + [r[3] for r in rows]
    lo, hi = min(vals), max(vals)
    if hi - lo < 4:
        mid = (hi + lo) / 2.0
        lo, hi = mid - 2, mid + 2
    span = hi - lo

    def X(t):
        return PAD + (t - t0) / (t1 - t0) * (W - 2 * PAD)

    def Y(v):
        return H - PAD - (v - lo) / span * (H - 2 * PAD)

    def poly(idx, colour):
        pts = " ".join("%.1f,%.1f" % (X(r[0]), Y(r[idx])) for r in rows)
        return '<polyline fill="none" stroke="%s" stroke-width="2" points="%s"/>' % (colour, pts)

    marks = ""
    for name, a, b in S["windows"]:
        if b < t0 or a > t1:
            continue
        marks += '<line x1="%.1f" y1="%d" x2="%.1f" y2="%d" stroke="var(--border)" stroke-dasharray="4 4"/>' % (
            X(max(a, t0)), PAD, X(max(a, t0)), H - PAD)
        marks += '<text x="%.1f" y="%d" font-size="10" fill="var(--muted-foreground)">%s</text>' % (
            X(max(a, t0)) + 3, PAD + 10, name)
    return ('<svg viewBox="0 0 %d %d" width="100%%" style="max-width:%dpx">'
            '<text x="%d" y="14" font-size="11">chroma phase 0 (solid) and phase 2 (dashed), '
            'mean per frame, range %.1f - %.1f</text>%s%s%s'
            '<text x="%d" y="%d" font-size="10" fill="var(--muted-foreground)">%.0f s ago</text>'
            '<text x="%d" y="%d" font-size="10" fill="var(--muted-foreground)">now</text></svg>') % (
        W, H, W, PAD, lo, hi,
        poly(2, "var(--accent)"),
        '<polyline fill="none" stroke="#e0a030" stroke-width="2" stroke-dasharray="6 4" points="%s"/>'
        % " ".join("%.1f,%.1f" % (X(r[0]), Y(r[3])) for r in rows),
        marks, PAD, H - 8, t1 - t0, W - PAD - 22, H - 8)


def log_tail():
    try:
        with open(LOG) as f:
            lines = [l.rstrip() for l in f if l.strip()]
        return lines[-8:]
    except OSError:
        return []


def launch():
    global PROC
    open(LOG, "w").close()
    try:
        open(CSV, "w").close()
    except OSError:
        pass
    cmd = ([sys.executable, BIN] if BIN.endswith(".py") else [BIN])
    PROC = subprocess.Popen(cmd + ["SESSION", str(CAPTURE_SECONDS), "csv=" + CSV, "gate=%d" % GATE],
                            stdout=open(LOG, "a"), stderr=subprocess.STDOUT)
    threading.Thread(target=monitor, daemon=True).start()


def monitor():
    t0 = time.monotonic()
    while True:
        time.sleep(1.0)
        rc = PROC.poll()
        with LOCK:
            S["log"] = log_tail()
            S["rows"] = len(read_rows())
            if S["phase"] == "arming" and any("READY" in l for l in S["log"]):
                S["phase"] = "ready_red"
                S["note"] = ("Streaming. Point the front of the headset at the screen showing "
                            "full RED, about 30-50 cm away, then click BEGIN.")
            if rc is not None:
                if S["phase"] not in ("done",):
                    S["phase"] = "failed"
                    S["note"] = "Capture ended before the test finished (exit %s). Usual cause: " \
                               "the health gate rejected every attempt. Replug the headset and " \
                               "try again." % rc
                return
        if time.monotonic() - t0 > CAPTURE_SECONDS + 90:
            PROC.kill()
            return


def window_mean(name, a, b):
    sel = [r for r in read_rows() if a <= r[0] <= b]
    if not sel:
        return None
    n = len(sel)
    return {"n": n, "c0": sum(r[2] for r in sel) / n, "c2": sum(r[3] for r in sel) / n,
            "y": sum(r[4] for r in sel) / n}


def verdict():
    win = {w[0]: w for w in S["windows"]}
    red = win.get("RED")
    blue = win.get("BLUE")
    if not red or not blue:
        return "INCOMPLETE: both colour windows were not recorded."
    mr = window_mean("RED", red[1], red[2])
    mb = window_mean("BLUE", blue[1], blue[2])
    if not mr or not mb:
        return "INCOMPLETE: no RGB frames landed inside a colour window."
    dr = mr["c0"] - mr["c2"]
    db = mb["c0"] - mb["c2"]
    lines = []
    lines.append("# Which YUV422 chroma phase is U and which is V")
    lines.append("")
    lines.append("RED  window: %4d frames  chroma0 %6.2f  chroma2 %6.2f  luma %6.2f  (chroma0-chroma2 = %+6.2f)"
                 % (mr["n"], mr["c0"], mr["c2"], mr["y"], dr))
    lines.append("BLUE window: %4d frames  chroma0 %6.2f  chroma2 %6.2f  luma %6.2f  (chroma0-chroma2 = %+6.2f)"
                 % (mb["n"], mb["c0"], mb["c2"], mb["y"], db))
    lines.append("")
    flipped = (dr > 0) != (db > 0)
    margin = min(abs(dr), abs(db))
    if not flipped or margin < 5.0:
        lines.append("INCONCLUSIVE. The two chroma phases did not swap places between the colours "
                    "(difference %+0.2f under red, %+0.2f under blue, smaller of the two %.2f). "
                    "Either the screen was not filling the frame, or it was not saturated enough. "
                    "Nothing is concluded and frame.h keeps its current default."
                    % (dr, db, margin))
        return "\n".join(lines)
    cr = "chroma0" if dr > 0 else "chroma2"
    cb = "chroma2" if dr > 0 else "chroma0"
    packing = "VYUY" if cr == "chroma0" else "UYVY"
    lines.append("The chroma phases swap between the two colours, which is the whole test:")
    lines.append("  %s rises with red and falls with blue  ->  %s is Cr" % (cr, cr))
    lines.append("  %s falls with red and rises with blue  ->  %s is Cb" % (cb, cb))
    lines.append("")
    lines.append("4-byte group order is therefore %s, and frame.h's default should be META2_YUV_%s."
                 % (packing, packing))
    lines.append("Margin: the two phases differ by %.2f under red and %.2f under blue, in opposite "
                 "directions." % (dr, db))
    lines.append("")
    lines.append("Luma stayed at %.2f (red) and %.2f (blue). A large luma change between the two "
                 "would mean auto-exposure moved and would weaken the reading." % (mr["y"], mb["y"]))
    return "\n".join(lines)


def finish():
    global PROC
    txt = verdict()
    with open(OUT, "w") as f:
        f.write(txt + "\n")
    with open(RAW, "w") as f:
        json.dump({"windows": [[w[0], w[1], w[2]] for w in S["windows"]],
                   "rows": len(read_rows())}, f)
    if PROC and PROC.poll() is None:
        PROC.kill()
    with LOCK:
        S["phase"] = "done"
        S["note"] = txt


def begin_action():
    with LOCK:
        if S["phase"] == "ready_red":
            S["phase"] = "act_red"
            S["act_end"] = time.monotonic() + COUNT_S + ACT_SECONDS
            S["windows"].append(("RED", time.monotonic() + COUNT_S, time.monotonic() + COUNT_S + ACT_SECONDS))
        elif S["phase"] == "ready_blue":
            S["phase"] = "act_blue"
            S["act_end"] = time.monotonic() + COUNT_S + ACT_SECONDS
            S["windows"].append(("BLUE", time.monotonic() + COUNT_S, time.monotonic() + COUNT_S + ACT_SECONDS))


def tick():
    with LOCK:
        if S["phase"] == "act_red" and time.monotonic() >= S["act_end"]:
            S["phase"] = "settle_red"
            S["note"] = "Red window recorded. Switch the screen to full BLUE, then click CONTINUE."
        elif S["phase"] == "act_blue" and time.monotonic() >= S["act_end"]:
            S["phase"] = "done"
            finish()


def cont():
    with LOCK:
        if S["phase"] == "settle_red":
            S["phase"] = "ready_blue"
            S["note"] = "Hold the screen showing full BLUE in front of the headset, then click BEGIN."


def state():
    tick()
    with LOCK:
        left = 0
        if S["phase"] in ("act_red", "act_blue"):
            left = max(0, int(round(S["act_end"] - time.monotonic())))
        return {"phase": S["phase"], "note": S["note"], "log": S["log"], "rows": S["rows"],
                "left": left, "graph": svg_graph(),
                "windows": [[w[0], round(w[2] - w[1])] for w in S["windows"]]}


PAGE = """<!doctype html><meta charset=utf-8><title>Meta 2 - U or V</title>
<style>
body{font:15px/1.5 system-ui;margin:0;padding:24px;color:var(--foreground);background:transparent}
h1{font-size:20px;margin:0 0 4px}
.card{border:1px solid var(--border);border-radius:10px;padding:16px 18px;margin:14px 0;max-width:700px}
button{font:inherit;padding:10px 22px;border-radius:8px;border:1px solid var(--border);
background:var(--accent);color:var(--foreground);cursor:pointer}
.muted{color:var(--muted-foreground)}
pre{white-space:pre-wrap;font-size:12px;color:var(--muted-foreground)}
.big{font-size:34px;font-weight:600}
.sw{display:inline-block;width:14px;height:14px;border-radius:3px;vertical-align:middle}
</style>
<h1>Which chroma phase is U, which is V</h1>
<div class=muted>EP 0x83 is YUV422 with chroma at the two even byte phases. Which one is Cr has
never been measured - every capture so far was near-neutral. A saturated screen settles it.</div>
<div class=card id=card></div>
<script>
function post(u){fetch(u,{method:'POST'}).catch(function(){fetch(u);});}
function render(st){
  var c=document.getElementById('card');
  var g=st.graph||'';
  var act=(st.phase=='act_red'||st.phase=='act_blue');
  var colour=st.phase.indexOf('red')>=0?'#d03030':'#3060d0';
  var name=st.phase.indexOf('red')>=0?'RED':'BLUE';
  var h='';
  if(st.phase=='waiting'){h='<div class=big>Ready when you are</div><p>'+st.note+'</p><button onclick="post(\\'/start\\')">START</button>';}
  else if(st.phase=='arming'){h='<div class=big>Arming...</div><p class=muted>The health gate can need several attempts. Keep the headset steady and pointed at '+
      '<span class=sw style="background:#d03030"></span> red - the capture window is already running.</p><pre>'+st.log.join('\\n')+'</pre>';}
  else if(st.phase=='ready_red'||st.phase=='ready_blue'){h='<div class=big>Hold <span class=sw style="background:'+colour+'"></span> '+name+
      '</div><p>'+st.note+'</p><button onclick="post(\\'/begin\\')">BEGIN</button>';}
  else if(act){h='<div class=big>Hold <span class=sw style="background:'+colour+'"></span> '+name+
      '</div><p>'+st.left+' s left. Keep the headset still and the screen filling its view.</p>'+g;}
  else if(st.phase=='settle_red'){h='<div class=big>Red recorded</div><p>'+st.note+'</p>'+g+'<button onclick="post(\\'/continue\\')">CONTINUE</button>';}
  else if(st.phase=='done'){h='<div class=big>Done</div><pre>'+st.note+'</pre>';}
  else if(st.phase=='failed'){h='<div class=big>Not captured</div><p>'+st.note+'</p><pre>'+st.log.join('\\n')+'</pre><button onclick="post(\\'/start\\')">TRY AGAIN</button>';}
  h+='<p class=muted>frames logged: '+st.rows+'</p>';
  c.innerHTML=h;
}
function poll(){fetch('/state').then(function(r){return r.json();}).then(render).catch(function(){});}
poll();setInterval(poll,1000);
</script>
"""


class H(BaseHTTPRequestHandler):
    def _send(self, body, ctype="text/html; charset=utf-8"):
        b = body.encode()
        self.send_response(200)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(b)))
        self.end_headers()
        self.wfile.write(b)

    def do_GET(self):
        if self.path.startswith("/state"):
            self._send(json.dumps(state()), "application/json")
        elif self.path.startswith("/results"):
            try:
                self._send(open(OUT).read(), "text/plain; charset=utf-8")
            except OSError:
                self._send("no results yet", "text/plain; charset=utf-8")
        elif self.path.startswith("/start"):
            self.do_POST()
        else:
            self._send(PAGE)

    def do_POST(self):
        if self.path.startswith("/start"):
            with LOCK:
                if PROC and PROC.poll() is None:
                    PROC.kill()
                    time.sleep(1)
                S["windows"] = []
                S["phase"] = "arming"
                S["note"] = "Arming"
                S["log"] = []
            launch()
        elif self.path.startswith("/begin"):
            begin_action()
        elif self.path.startswith("/continue"):
            cont()
        self._send(json.dumps(state()), "application/json")

    def log_message(self, *a):
        pass


if __name__ == "__main__":
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8095
    print("colour coach on :%d" % port, flush=True)
    ThreadingHTTPServer(("0.0.0.0", port), H).serve_forever()
