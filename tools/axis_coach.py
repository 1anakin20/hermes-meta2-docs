#!/usr/bin/env python3
"""Map the IMU sensor axes onto the headset's physical axes.

Gravity is the calibration source. Six table poses each point a known unit
vector upward, and an accelerometer at rest reads +1 g along the axis that
points up. Six poses are enough to get the whole signed map, the counts-per-g
scale, and the sensor bias - with no matrix fitting needed:

    m_i(pose with up = +e_j) = k * R[i][j]
    m_i(pose with up = -e_j) = -k * R[i][j]
    k * R[i][j] = (m_i(+e_j) - m_i(-e_j)) / 2      <- opposite poses cancel bias
    bias_i      = (m_i(+e_j) + m_i(-e_j)) / 2

Nothing on screen advances until you click. The only timed thing is the 2 s
averaging window after CAPTURE, and you must not touch the headset during it.

    usage: python3 axis_coach.py [port]
"""
import json
import math
import os
import subprocess
import sys
import threading
import time
from collections import deque
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

HERE = os.path.dirname(os.path.abspath(__file__))
BIN = "/home/hermes/work/meta2lib/build/meta2_imu_log"
CSV = os.path.join(HERE, "axis_cal.csv")
OUT = os.path.join(HERE, "axis_results.txt")
RAW = os.path.join(HERE, "axis_poses.json")

CAPTURE_SECONDS = 900
SETTLE_SECONDS = 0.6
AVERAGE_SECONDS = 2.0
GRAPH_POINTS = 300

# Headset basis, right-handed:
#   X forward - out through the screens / RGB camera
#   Y left    - toward the wearer's LEFT ear
#   Z up      - toward the crown of the headset
# Each pose is described by which part rests on the table, and therefore which
# headset direction points at the ceiling.
POSES = [
    ("Z+", "Bottom of the headset on the table",
     "Rest it the way it would sit on a desk with the strap opening down: the "
     "crown points at the ceiling.", (0, 0, 1)),
    ("Z-", "Top / crown of the headset on the table",
     "Flip it over so the crown rests on the table and the strap opening faces "
     "the ceiling.", (0, 0, -1)),
    ("Y+", "Wearer's RIGHT side on the table",
     "Lay it on its side so the wearer's right temple touches the table; the "
     "wearer's left side points up.", (0, 1, 0)),
    ("Y-", "Wearer's LEFT side on the table",
     "Lay it on the other side so the wearer's left temple touches the table; "
     "the wearer's right side points up.", (0, -1, 0)),
    ("X+", "Back of the headset on the table",
     "Screens face the ceiling, the back panel rests on the table.", (1, 0, 0)),
    ("X-", "Screens face the table",
     "The display side rests on the table and the back panel points up.", (-1, 0, 0)),
]

# RLock, not Lock: the done path holds the lock and then calls analyse(), which
# takes it again. With a plain Lock that self-deadlocks the whole server - the
# capture thread blocks holding the lock and every /state poll blocks behind it.
LOCK = threading.RLock()
S = {
    "phase": "waiting",          # waiting | arming | poses | sampling | done | failed
    "pose_i": 0,
    "results": [],               # (pose_id, up, IMU0 mean, IMU1 mean)
    "log": [],
    "note": "Put the headset on a table where you can flip it freely. Click START.",
    "t0": 0.0,
    "capture_end": 0.0,
}
SAMPLES = {"IMU0": deque(maxlen=2000), "IMU1": deque(maxlen=2000)}


def monotonic():
    return time.monotonic()


# --------------------------------------------------------------------------
# CSV tailer: meta2_imu_log writes rows and flushes per batch, so the graph
# sees samples within tens of milliseconds.
# --------------------------------------------------------------------------
def tailer(stop):
    pos = 0
    while not stop.is_set():
        try:
            size = os.path.getsize(CSV)
        except OSError:
            time.sleep(0.3)
            continue
        if size < pos:                      # logger recreated the file
            pos = 0
            with LOCK:
                SAMPLES["IMU0"].clear()
                SAMPLES["IMU1"].clear()
        if size == pos:
            time.sleep(0.15)
            continue
        with open(CSV, "r") as f:
            f.seek(pos)
            chunk = f.read()
            pos = f.tell()
        lines = chunk.split("\n")
        if not lines[-1]:
            lines.pop()
        else:
            pos -= len(lines[-1])           # partial line: re-read it next pass
        for line in lines:
            p = line.split(",")
            if len(p) < 10 or p[0] == "host_us" or line.startswith("#"):
                continue
            try:
                host = int(p[0]); tag = int(p[3])
                g = (int(p[4]), int(p[5]), int(p[6]))
                a = (int(p[7]), int(p[8]), int(p[9]))
            except ValueError:
                continue
            key = "IMU0" if tag == 119 else "IMU1"
            with LOCK:
                SAMPLES[key].append((host, a, g))


# --------------------------------------------------------------------------
# capture
# --------------------------------------------------------------------------
def run_capture_once():
    with LOCK:
        S["phase"] = "arming"
        S["note"] = ("Arming. It re-arms from a USB port reset until it passes the health gate, "
                     "which can take several attempts. Leave the headset alone until it says READY.")
        S["log"] = []
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
    for line in p.stdout:
        line = line.rstrip()
        with LOCK:
            S["log"].append(line)
            S["log"] = S["log"][-40:]
        if not ready and line.startswith("imu_log: mask="):
            ready = True
            with LOCK:
                S["phase"] = "poses"
                S["pose_i"] = 0
                S["results"] = []
                S["t0"] = monotonic()
                S["note"] = "Streaming. Work through the poses - the page waits for you at each one."
    p.wait()
    with LOCK:
        if S["phase"] in ("poses", "sampling"):
            S["phase"] = "done"
            S["note"] = "Capture window ended."
            return True
        S["phase"] = "failed"
        S["note"] = ("The device would not pass the health gate. Click START to try again; if it "
                     "keeps failing, unplug and replug the headset first.")
        return False


def start_capture():
    for _ in range(3):
        if run_capture_once():
            return


def capture_current_pose():
    with LOCK:
        if S["phase"] != "poses":
            return
        pid = POSES[S["pose_i"]][0]
        S["phase"] = "sampling"
        S["capture_end"] = monotonic() + SETTLE_SECONDS + AVERAGE_SECONDS
    threading.Thread(target=_finish_capture, args=(pid,), daemon=True).start()


def _mean_over(tag, a, b):
    with LOCK:
        rows = [s for s in SAMPLES[tag] if a <= s[0] <= b]
    if not rows:
        return None, 0
    n = len(rows)
    return [sum(r[1][i] for r in rows) / n for i in range(3)], n


def _finish_capture(pid):
    t_end = S["capture_end"]
    t_start = t_end - AVERAGE_SECONDS
    while monotonic() < t_end:
        time.sleep(0.05)
    # results tuple shape, used by analyse() and state_json():
    #   (pose_id, up_vector, IMU0_mean, IMU0_n, IMU1_mean, IMU1_n)
    m0, n0 = _mean_over("IMU0", t_start * 1e6, t_end * 1e6)
    m1, n1 = _mean_over("IMU1", t_start * 1e6, t_end * 1e6)
    with LOCK:
        up = POSES[S["pose_i"]][3]
        S["results"].append((pid, up, m0, n0, m1, n1))
        if n0 < 20 or n1 < 20:
            S["note"] = ("Pose %s captured too few samples (%s / %s) - the stream may have stalled. "
                         "Move to the next pose anyway; we can retake it after."
                         % (pid, n0, n1))
        if S["pose_i"] + 1 >= len(POSES):
            S["phase"] = "done"
            S["note"] = "All six poses recorded."
            write_results()
        else:
            S["pose_i"] += 1
            S["phase"] = "poses"
            S["note"] = "Recorded. Next pose on screen."


# --------------------------------------------------------------------------
# analysis - closed form, no fitting library
# --------------------------------------------------------------------------
def analyse():
    with LOCK:
        res = list(S["results"])
    if len(res) < 6:
        return None
    by_id = {r[0]: r for r in res}
    out = {}
    for ti, tag in enumerate(("IMU0", "IMU1")):
        C = [[0.0] * 3 for _ in range(3)]     # C[i][j] = k * R[i][j]
        B = [[0.0] * 3 for _ in range(3)]     # bias estimates
        pairs = [("X+", "X-"), ("Y+", "Y-"), ("Z+", "Z-")]
        for j, (pa, pb) in enumerate(pairs):
            if pa not in by_id or pb not in by_id:
                return None
            ma = by_id[pa][2 + ti * 2]
            mb = by_id[pb][2 + ti * 2]
            for i in range(3):
                C[i][j] = (ma[i] - mb[i]) / 2.0
                B[i][j] = (ma[i] + mb[i]) / 2.0
        col_norm = [math.sqrt(sum(C[i][j] ** 2 for i in range(3))) for j in range(3)]
        k = sum(col_norm) / 3.0
        R = [[C[i][j] / k for j in range(3)] for i in range(3)]
        bias = [sum(B[i][j] for j in range(3)) / 3.0 for i in range(3)]
        # |a| at rest is 1 g whatever the orientation, but the reading carries the
        # sensor bias, so the raw magnitudes scatter by up to |bias|. Compare them
        # after bias removal, or a real 0.06 g bias looks like a botched pose.
        raw_mag, net_mag = [], []
        for r in res:
            m = r[2 + ti * 2]
            raw_mag.append(math.sqrt(sum(x * x for x in m)))
            net_mag.append(math.sqrt(sum((m[i] - bias[i]) ** 2 for i in range(3))))
        row_norm = [math.sqrt(sum(R[i][j] ** 2 for j in range(3))) for i in range(3)]
        # angles between the three headset directions as the sensor sees them.
        # They must be 90 degrees for the map to be a rotation - and they must be
        # 90 degrees whether or not the sensor happens to line up with the headset.
        angles = {}
        for x in range(3):
            for y in range(x + 1, 3):
                dot = sum(C[i][x] * C[i][y] for i in range(3)) / (col_norm[x] * col_norm[y])
                angles[(x, y)] = math.degrees(math.acos(max(-1.0, min(1.0, dot))))
        det = (R[0][0] * (R[1][1] * R[2][2] - R[1][2] * R[2][1])
               - R[0][1] * (R[1][0] * R[2][2] - R[1][2] * R[2][0])
               + R[0][2] * (R[1][0] * R[2][1] - R[1][1] * R[2][0]))
        out[tag] = {"k": k, "R": R, "C": C, "bias": bias, "col_norm": col_norm,
                    "mag_raw": raw_mag, "mag_net": net_mag, "det": det,
                    "row_norms": row_norm, "angles": angles}
    return out


HNAMES = ("X forward", "Y wearer's-left", "Z up")
SNAMES = ("ax", "ay", "az")


def axis_map(R):
    """Row i of R is sensor axis i expressed in headset coordinates.

    This deliberately does NOT snap to the nearest headset axis. The chips turned
    out to be mounted ~45 deg off the headset frame, and reporting "closest axis:
    X, purity 0.70" would hide that rather than state it.
    """
    m = []
    for i in range(3):
        row = R[i]
        norm = math.sqrt(sum(x * x for x in row))
        ang = [math.degrees(math.acos(max(-1.0, min(1.0, row[j] / norm)))) for j in range(3)]
        m.append((i, norm, row, ang))
    return m


def verdict(a):
    """The fit is over-determined, so it can grade itself - without assuming the
    sensor axes line up with the headset axes.

    1. every headset axis must measure the same 1 g (column norms agree)
    2. the three headset directions must be 90 deg apart in sensor space (it is a
       rotation, whatever its orientation)
    3. every pose's |a|, after bias removal, must agree with k
    4. det(R) must be +1: both frames are right-handed, so the map is a proper
       rotation. This is the check that catches a swapped pose pair - swapping the
       two poses of one axis just negates that column, which leaves 1, 2 and 3
       untouched and turns the frame left-handed.

    A mislabelled pose fails check 2 (two headset directions land on the same
    sensor direction, an angle of 0 or 180 instead of 90) and check 1.
    """
    out = []
    for tag in ("IMU0", "IMU1"):
        d = a[tag]
        coldev = max(abs(c - d["k"]) / d["k"] for c in d["col_norm"])
        angdev = max(abs(90.0 - v) for v in d["angles"].values())
        magdev = max(abs(m - d["k"]) / d["k"] for m in d["mag_net"])
        detdev = abs(d["det"] - 1.0)
        ok = coldev < 0.04 and angdev < 10.0 and magdev < 0.05 and detdev < 0.15
        out.append("%s: %s  (1 g agrees across poses to %.1f%%, headset axes are within "
                   "10 deg of 90 deg in sensor space (worst %.1f deg off), |a| agrees to %.1f%% "
                   "after removing a %.0f-count bias, det = %+.3f)"
                   % (tag, "CONSISTENT" if ok else "INCONSISTENT - retake these poses",
                      coldev * 100, angdev, magdev * 100,
                      math.sqrt(sum(x * x for x in d["bias"])), d["det"]))
    return "\n".join(out)


def write_results():
    a = analyse()
    if not a:
        return
    lines = ["# IMU axis map from six gravity poses", ""]
    for tag in ("IMU0", "IMU1"):
        d = a[tag]
        lines.append("%s:" % tag)
        lines.append("  gravity magnitude = %.1f counts  (1 g)" % d["k"])
        for fs in (1, 2, 4, 8, 16):
            cpg = 32768.0 / fs
            lines.append("    full scale +/-%2dg -> nominal %8.1f counts/g : measured is %+.1f%% off"
                         % (fs, cpg, (d["k"] - cpg) / cpg * 100))
        lines.append("  bias: " + " ".join("%s=%+.1f" % (SNAMES[i], d["bias"][i]) for i in range(3))
                     + "  (|bias| = %.0f counts = %.3f g)"
                     % (math.sqrt(sum(x * x for x in d["bias"])),
                        math.sqrt(sum(x * x for x in d["bias"])) / d["k"]))
        lines.append("  per-pose |a| raw:  " + " ".join("%8.1f" % x for x in d["mag_raw"]))
        lines.append("  per-pose |a| net:  " + " ".join("%8.1f" % x for x in d["mag_net"]))
        lines.append("  each headset axis, as the sensor sees it (unit vector in sensor coords):")
        for j in range(3):
            v = [d["C"][i][j] / d["col_norm"][j] for i in range(3)]
            lines.append("    headset %-16s -> %s   (measures %.1f counts, should be %.1f)"
                         % (HNAMES[j], " ".join("%s=%+.3f" % (SNAMES[i], v[i]) for i in range(3)),
                            d["col_norm"][j], d["k"]))
        for (x, y), ang in sorted(d["angles"].items()):
            lines.append("    angle between headset %s and %s in sensor space: %.1f deg"
                         % (HNAMES[x], HNAMES[y], ang))
        lines.append("  det(R) = %+.3f (must be +1: both frames are right-handed)" % d["det"])
        lines.append("  each sensor axis, in the headset frame (unit vector, and its angle "
                     "to each headset axis):")
        for i, norm, row, ang in axis_map(d["R"]):
            lines.append("    %s: norm %.3f  components %s  angles to %s: %s"
                         % (SNAMES[i], norm, " ".join("%+.3f" % v for v in row),
                            "/".join(HNAMES), " ".join("%.0f deg" % a for a in ang)))
        lines.append("")
    lines.append(verdict(a))
    with open(OUT, "w") as f:
        f.write("\n".join(lines))
    # keep the raw pose means so a restart re-grades a finished session with the
    # current analysis instead of losing it
    with LOCK:
        res = list(S["results"])
    with open(RAW, "w") as f:
        json.dump([[r[0], list(r[1]), list(r[2]), r[3], list(r[4]), r[5]] for r in res], f)
    with LOCK:
        S["log"].append("results written to %s" % OUT)


# --------------------------------------------------------------------------
# HTTP
# --------------------------------------------------------------------------
class H(BaseHTTPRequestHandler):
    def log_message(self, *a):
        pass

    def _send(self, body, ctype="text/html; charset=utf-8"):
        b = body.encode()
        self.send_response(200)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(b)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(b)

    def do_GET(self):
        path = self.path.split("?")[0]
        if path == "/":
            self._send(PAGE)
        elif path == "/state":
            self._send(json.dumps(state_json()), "application/json")
        elif path == "/samples":
            self._send(json.dumps(samples_json()), "application/json")
        elif path in ("/start", "/capture"):
            self.do_POST()
        else:
            self.send_error(404)

    def do_POST(self):
        path = self.path.split("?")[0]
        if path == "/start":
            if S["phase"] in ("waiting", "failed"):
                threading.Thread(target=start_capture, daemon=True).start()
        elif path == "/capture":
            capture_current_pose()
        self._send(json.dumps(state_json()), "application/json")


def up_text(up):
    names = {0: ("+X forward", "-X back"),
             1: ("+Y wearer's-left", "-Y wearer's-right"),
             2: ("+Z up", "-Z down")}
    parts = []
    for i, v in enumerate(up):
        if v > 0:
            parts.append(names[i][0])
        elif v < 0:
            parts.append(names[i][1])
    return " and ".join(parts)


def state_json():
    with LOCK:
        ph = S["phase"]
        pi = S["pose_i"]
        pose = None
        if ph in ("poses", "sampling") and pi < len(POSES):
            pid, title, how, up = POSES[pi]
            pose = {"id": pid, "title": title, "how": how, "up": up_text(up),
                    "n": pi + 1, "total": len(POSES)}
        v = None
        if ph == "done" and len(S["results"]) == len(POSES):
            try:
                v = verdict(analyse())
            except Exception as e:
                v = "analysis failed: %s" % e
        return {"phase": ph, "pose": pose, "note": S["note"], "verdict": v,
                "log": S["log"][-8:],
                "done": len(S["results"]),
                "results": [[r[0]] + r[2] + r[4] for r in S["results"]]}


def samples_json():
    out = {}
    with LOCK:
        for tag in ("IMU0", "IMU1"):
            rows = list(SAMPLES[tag])
            if len(rows) > GRAPH_POINTS:
                step = len(rows) // GRAPH_POINTS + 1
                rows = rows[::step]
            last_host = rows[-1][0] if rows else 0
            out[tag] = [[(r[0] - last_host) / 1000.0, r[1][0], r[1][1], r[1][2]] for r in rows]
            recent = [r for r in list(SAMPLES[tag]) if last_host - r[0] <= 1_000_000]
            if recent:
                out[tag + "_mean"] = [sum(r[1][i] for r in recent) / len(recent) for i in range(3)]
                out[tag + "_n"] = len(recent)
            else:
                out[tag + "_mean"] = None
                out[tag + "_n"] = 0
    return out


PAGE = """<!doctype html><meta charset=utf-8><title>IMU axis coach</title>
<style>
 body{font-family:system-ui,sans-serif;margin:0;padding:22px;max-width:1100px}
 h1{font-size:22px;margin:0 0 6px}
 .note{font-size:16px;line-height:1.5;margin-bottom:18px}
 .card{border:1px solid #888;border-radius:10px;padding:18px;margin-bottom:18px}
 .pose{font-size:26px;font-weight:700;margin-bottom:8px}
 .how{font-size:18px;line-height:1.5}
 button{font-size:20px;padding:14px 26px;border-radius:8px;border:1px solid #888;cursor:pointer}
 .grid{display:flex;gap:18px;flex-wrap:wrap}
 canvas{border:1px solid #888;border-radius:8px}
 .lg{font-size:15px;margin-top:6px}
 table{border-collapse:collapse;font-size:15px;margin-top:10px}
 td,th{border:1px solid #888;padding:5px 9px;text-align:right}
 .log{font-family:ui-monospace,monospace;font-size:12px;white-space:pre-wrap;opacity:.8}
 .k{font-family:ui-monospace,monospace}
</style>
<h1>IMU axis coach &mdash; six gravity poses</h1>
<div class=note id=note></div>
<div class=card id=card></div>
<div class=grid>
  <div><canvas id=c0 width=520 height=200></canvas><div class=lg id=l0></div></div>
  <div><canvas id=c1 width=520 height=200></canvas><div class=lg id=l1></div></div>
</div>
<div class=card><b>Recorded poses</b><div id=res></div></div>
<div class=log id=log></div>
<script>
function post(u){return fetch(u,{method:'POST'}).then(r=>r.json()).catch(()=>fetch(u).then(r=>r.json()))}
function get(u){return fetch(u).then(r=>r.json())}
function draw(id,rows,mean){
 const c=document.getElementById(id),x=c.getContext('2d');
 x.clearRect(0,0,c.width,c.height);
 if(!rows.length)return;
 let lo=1e9,hi=-1e9;
 for(const r of rows)for(let i=1;i<4;i++){if(r[i]<lo)lo=r[i];if(r[i]>hi)hi=r[i];}
 lo=Math.min(lo,-500);hi=Math.max(hi,500);
 const pad=6,sc=(c.height-2*pad)/(hi-lo);
 const Y=v=>c.height-pad-(v-lo)*sc;
 x.strokeStyle='#888';x.beginPath();x.moveTo(0,Y(0));x.lineTo(c.width,Y(0));x.stroke();
 const cols=['#e04040','#30a030','#3060e0'];
 for(let i=0;i<3;i++){
  x.strokeStyle=cols[i];x.beginPath();
  rows.forEach((r,j)=>{const px=j/(rows.length-1)*c.width,py=Y(r[i+1]);j?x.lineTo(px,py):x.moveTo(px,py);});
  x.stroke();
 }
 if(mean)mean.forEach((v,i)=>{x.fillStyle=cols[i];x.font='13px monospace';x.fillText(('ax ay az'.split(' ')[i])+' '+v.toFixed(0),6,16+i*15);});
}
async function tick(){
 let s;try{s=await get('/state')}catch(e){return}
 const n=document.getElementById('note');n.textContent=s.note;
 const c=document.getElementById('card');
 if(s.phase==='poses'||s.phase==='sampling'){
  const p=s.pose;
  c.innerHTML='<div class=pose>Pose '+p.n+' of '+p.total+' &mdash; '+p.title+'</div>'+
    '<div class=how>'+p.how+'</div>'+
    '<div class=how style="margin-top:8px">Headset direction pointing at the ceiling: <b>'+p.up+'</b></div>'+
    '<div class=how style="margin-top:14px">Set it down, take your hands off, then press CAPTURE and '
    +'leave it alone for 2 seconds.</div>'+
    '<div style="margin-top:14px"><button onclick="post(\\'/capture\\')">'+(s.phase==='sampling'?'Sampling...':'CAPTURE')+'</button></div>';
 } else if(s.phase==='waiting'){
  c.innerHTML='<button onclick="post(\\'/start\\')">START</button>';
 } else if(s.phase==='arming'){
  c.innerHTML='<b>Arming...</b>';
 } else if(s.phase==='done'){
  c.innerHTML='<b>All six poses recorded.</b><pre style="font-size:16px;margin:10px 0 0">'
   +(s.verdict||'').replace(/</g,'&lt;')+'</pre>'+
   '<div class=how style="margin-top:10px">Full map with per-axis components is written to axis_results.txt.</div>';
 } else {
  c.innerHTML='<button onclick="post(\\'/start\\')">START</button>';
 }
 const r=document.getElementById('res');
 if(s.results.length){
  let h='<table><tr><th>pose</th><th>IMU0 ax</th><th>ay</th><th>az</th><th>IMU1 ax</th><th>ay</th><th>az</th></tr>';
  for(const q of s.results)h+='<tr><td>'+q[0]+'</td>'+q.slice(1).map(v=>'<td class=k>'+v.toFixed(0)+'</td>').join('')+'</tr>';
  r.innerHTML=h+'</table>';
 } else r.innerHTML='<i>none yet</i>';
 document.getElementById('log').textContent=s.log.join('\\n');
 try{
  const d=await get('/samples');
  draw('c0',d.IMU0,d.IMU0_mean);draw('c1',d.IMU1,d.IMU1_mean);
  document.getElementById('l0').textContent='IMU0  samples in last 1 s: '+d.IMU0_n;
  document.getElementById('l1').textContent='IMU1  samples in last 1 s: '+d.IMU1_n;
 }catch(e){}
}
tick();setInterval(tick,700);
</script>
"""


def restore():
    """Re-load the last completed session so the page re-grades it, rather than
    coming back blank after a restart."""
    if not os.path.exists(RAW):
        return
    try:
        with open(RAW) as f:
            raw = json.load(f)
    except Exception:
        return
    if len(raw) != len(POSES):
        return
    with LOCK:
        S["results"] = [(r[0], tuple(r[1]), tuple(r[2]), r[3], tuple(r[4]), r[5]) for r in raw]
        S["phase"] = "done"
        S["log"].append("restored %d poses from %s" % (len(raw), RAW))


def main():
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8095
    restore()
    stop = threading.Event()
    threading.Thread(target=tailer, args=(stop,), daemon=True).start()
    srv = ThreadingHTTPServer(("0.0.0.0", port), H)
    print("axis coach on http://0.0.0.0:%d/  (csv=%s results=%s)" % (port, CSV, OUT), flush=True)
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        stop.set()


if __name__ == "__main__":
    main()
