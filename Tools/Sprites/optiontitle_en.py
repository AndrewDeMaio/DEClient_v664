"""
optiontitle_en.py - repaint the title-screen Options tab labels in English.

optiontitle1024.spk layout (22 frames):
    2..5    tab labels, selected/bright   HOTKEYS DISPLAY SOUND GAME
    6..9    the same four, normal/dark
    18..20  the reset button, three states
Everything else (panel art, checkbox and radio glyphs, scrollbar) is untouched.

Korean originals: 단축키 / 화면조정 / 소리음악 / 게임설정 / 설정초기화

usage:  python optiontitle_en.py <name>    # reads <name>.spk/.spki, rewrites them
"""
import sys, os
from collections import Counter
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from spk import load_pack, save_pack, from565, to565
from titlemenu_en import F as BASE_FONT, text_width as _tw

# glyphs the title-menu font does not carry
FONT = dict(BASE_FONT)
FONT.update({
'B': ["####.","#...#","#...#","####.","#...#","#...#","####."],
'F': ["#####","#....","#....","####.","#....","#....","#...."],
'V': ["#...#","#...#","#...#","#...#","#...#",".#.#.","..#.."],
'H': ["#...#","#...#","#...#","#####","#...#","#...#","#...#"],
'K': ["#...#","#..#.","#.#..","##...","#.#..","#..#.","#...#"],
'L': ["#....","#....","#....","#....","#....","#....","#####"],
'M': ["#...#","##.##","#.#.#","#.#.#","#...#","#...#","#...#"],
'Y': ["#...#","#...#",".#.#.","..#..","..#..","..#..","..#.."],
})

# frame -> label. Even/odd pairs share text; only the plate colour differs.
LABELS = {
    2: "HOTKEYS", 3: "DISPLAY", 4: "SOUND", 5: "GAME",
    6: "HOTKEYS", 7: "DISPLAY", 8: "SOUND", 9: "GAME",
    18: "RESET",  19: "RESET",  20: "RESET",
}

# erase window inside the plate border, and the clean columns to sample from
EX0, EX1, EY0, EY1 = 5, 63, 4, 16
AL, AR = 4, 64
TEXT_TOP = 7          # 7px font inside the 4..16 band

# Frame 0 is the panel background, and the four tab labels are painted INTO it.
# ShowButtonWidget only blits a tab sprite while that tab has focus, so the
# three unselected tabs you see are this background, not frames 2..9. Translating
# only the sprites gives English on hover and Korean at rest.
#
# The baked tabs are different art from frames 2..9 (a pixel match scores ~24%),
# so they are repainted in place rather than composited over.
BG_FRAME   = 0
BG_TABS    = [(0, "HOTKEYS"), (70, "DISPLAY"), (140, "SOUND"), (210, "GAME")]
BG_EX0, BG_EX1 = 8, 61        # erase window, relative to each tab's origin
BG_AL, BG_AR   = 7, 62        # clean anchor columns, relative to origin
BG_EY0, BG_EY1 = 6, 17
BG_TEXT_TOP    = 8

# Frame 1 (TITLE_HOTKEY_WINDOW) carries the hotkey list's two column headers,
# also baked in: 기능설명 (what the action is) and 바로가기 키 (its key).
# Each entry is (erase x0, erase x1, left anchor, right anchor, label).
HK_FRAME   = 1
HK_HEADERS = [
    (10, 93,  8,  95,  "FUNCTION"),
    (112, 243, 110, 245, "SHORTCUT"),
]
HK_EY0, HK_EY1 = 4, 15
HK_TEXT_TOP    = 6

def text_width(s):
    return sum(len(FONT[c][0]) for c in s) + max(0, len(s) - 1)

def lum(v):
    r, g, b = from565(v)
    return (r*299 + g*587 + b*114) // 1000

def lerp(a, b, t):
    return tuple(round(a[i] + (b[i]-a[i])*t) for i in range(3))

def sample_colours(rows, w, h):
    """Pick the plate's text colour: the brightest common tone in the glyph area."""
    bg = Counter()
    for y in range(EY0, EY1+1):
        for x in (AL, AL+2, AR-2, AR):
            v = rows[y][x]
            if v is not None: bg[v] += 1
    bgv = bg.most_common(1)[0][0]
    fg = Counter()
    for y in range(EY0, EY1+1):
        for x in range(18, min(w-4, 50)):
            v = rows[y][x]
            if v is not None and lum(v) > lum(bgv) + 30: fg[v] += 1

    # Take the BRIGHTEST tone that occurs often enough to be glyph core, not the
    # most frequent one -- on antialiased text the commonest bright pixel is an
    # edge blend, which on the orange plates reads as orange-on-orange.
    body = None
    for v, n in sorted(fg.items(), key=lambda kv: -lum(kv[0])):
        if n >= 3:
            body = from565(v)
            break
    if body is None:
        body = (240, 240, 240)

    # Guarantee separation from the plate regardless of what was sampled.
    if lum(to565(*body)) < lum(bgv) + 70:
        body = (245, 245, 245)

    r, g, b = from565(bgv)
    shadow = (max(0, r-90), max(0, g-90), max(0, b-90))
    return body, shadow

def repaint_background(w, h, rows):
    """Repaint the four tab labels baked into the panel background (frame 0)."""
    rows = [list(r) for r in rows]
    for ox, label in BG_TABS:
        # colours sampled from this tab only, so each keeps its own plate tone
        bg = Counter()
        for y in range(BG_EY0, BG_EY1+1):
            for x in (ox+BG_AL, ox+BG_AL+1, ox+BG_AR-1, ox+BG_AR):
                if x < w and rows[y][x] is not None: bg[rows[y][x]] += 1
        if not bg:
            continue
        bgv = bg.most_common(1)[0][0]

        fg = Counter()
        for y in range(BG_EY0, BG_EY1+1):
            for x in range(ox+BG_EX0, min(ox+BG_EX1, w-1)+1):
                v = rows[y][x]
                if v is not None and lum(v) > lum(bgv) + 30: fg[v] += 1
        body = None
        for v, n in sorted(fg.items(), key=lambda kv: -lum(kv[0])):
            if n >= 3:
                body = from565(v); break
        if body is None or lum(to565(*body)) < lum(bgv) + 70:
            body = (240, 240, 240)
        r, g, b = from565(bgv)
        shadow = (max(0, r-90), max(0, g-90), max(0, b-90))

        # erase
        for y in range(BG_EY0, BG_EY1+1):
            cl = rows[y][ox+BG_AL]
            cr = rows[y][min(ox+BG_AR, w-1)]
            if cl is None or cr is None: continue
            a, bb = from565(cl), from565(cr)
            span = BG_AR - BG_AL
            for x in range(ox+BG_EX0, min(ox+BG_EX1, w-1)+1):
                rows[y][x] = to565(*lerp(a, bb, (x-(ox+BG_AL))/span))

        # draw
        tw = text_width(label)
        x0 = ox + BG_EX0 + ((BG_EX1-BG_EX0+1) - tw)//2
        for dx, dy, col in ((1, 1, shadow), (0, 0, body)):
            cx = x0 + dx
            for ch in label:
                gl = FONT[ch]
                for gy, line in enumerate(gl):
                    for gx, p in enumerate(line):
                        if p != '#': continue
                        px, py = cx+gx, BG_TEXT_TOP+gy+dy
                        if ox+BG_EX0 <= px <= min(ox+BG_EX1, w-1) and BG_EY0 <= py <= BG_EY1:
                            rows[py][px] = to565(*col)
                cx += len(gl[0]) + 1
    return rows


def paint_label(rows, w, ex0, ex1, al, ar, ey0, ey1, text_top, label):
    """Erase a box by rebuilding its background, then draw label centred in it."""
    ex1 = min(ex1, w-1); ar = min(ar, w-1)

    bgc = Counter()
    for y in range(ey0, ey1+1):
        for x in (al, al+1, ar-1, ar):
            if 0 <= x < w and rows[y][x] is not None: bgc[rows[y][x]] += 1
    if not bgc:
        return
    bgv = bgc.most_common(1)[0][0]

    fgc = Counter()
    for y in range(ey0, ey1+1):
        for x in range(ex0, ex1+1):
            v = rows[y][x]
            if v is not None and lum(v) > lum(bgv) + 30: fgc[v] += 1
    body = None
    for v, n in sorted(fgc.items(), key=lambda kv: -lum(kv[0])):
        if n >= 3:
            body = from565(v); break
    if body is None or lum(to565(*body)) < lum(bgv) + 70:
        body = (240, 240, 240)
    r, g, b = from565(bgv)
    shadow = (max(0, r-90), max(0, g-90), max(0, b-90))

    for y in range(ey0, ey1+1):
        cl, cr = rows[y][al], rows[y][ar]
        if cl is None or cr is None: continue
        a, bb = from565(cl), from565(cr)
        span = ar - al
        for x in range(ex0, ex1+1):
            rows[y][x] = to565(*lerp(a, bb, (x-al)/span))

    tw = text_width(label)
    x0 = ex0 + ((ex1-ex0+1) - tw)//2
    for dx, dy, col in ((1, 1, shadow), (0, 0, body)):
        cx = x0 + dx
        for ch in label:
            gl = FONT[ch]
            for gy, line in enumerate(gl):
                for gx, p in enumerate(line):
                    if p != '#': continue
                    px, py = cx+gx, text_top+gy+dy
                    if ex0 <= px <= ex1 and ey0 <= py <= ey1:
                        rows[py][px] = to565(*col)
            cx += len(gl[0]) + 1


def repaint_headers(w, h, rows):
    """Repaint the hotkey list's two baked column headers (frame 1)."""
    rows = [list(r) for r in rows]
    for ex0, ex1, al, ar, label in HK_HEADERS:
        paint_label(rows, w, ex0, ex1, al, ar, HK_EY0, HK_EY1, HK_TEXT_TOP, label)
    return rows


def repaint(frames):
    out = []
    for fi, (w, h, rows) in enumerate(frames):
        if fi == BG_FRAME:
            out.append((w, h, repaint_background(w, h, rows)))
            continue
        if fi == HK_FRAME:
            out.append((w, h, repaint_headers(w, h, rows)))
            continue
        if fi not in LABELS:
            out.append((w, h, rows))
            continue
        rows = [list(r) for r in rows]
        body, shadow = sample_colours(rows, w, h)

        ex1 = min(EX1, w - 6)
        ar  = min(AR, w - 5)

        # 1. erase: rebuild the plate background across the text window
        for y in range(EY0, EY1+1):
            cl, cr = rows[y][AL], rows[y][ar]
            if cl is None or cr is None: continue
            a, b = from565(cl), from565(cr)
            span = ar - AL
            for x in range(EX0, ex1+1):
                rows[y][x] = to565(*lerp(a, b, (x-AL)/span))

        # 2. draw the label, centred, shadow first
        label = LABELS[fi]
        tw = text_width(label)
        x0 = EX0 + ((ex1-EX0+1) - tw)//2
        for dx, dy, col in ((1, 1, shadow), (0, 0, body)):
            cx = x0 + dx
            for ch in label:
                g = FONT[ch]
                for gy, line in enumerate(g):
                    for gx, p in enumerate(line):
                        if p != '#': continue
                        px, py = cx+gx, TEXT_TOP+gy+dy
                        if EX0 <= px <= ex1 and EY0 <= py <= EY1:
                            rows[py][px] = to565(*col)
                cx += len(g[0]) + 1
        out.append((w, h, rows))
    return out

if __name__ == '__main__':
    name = sys.argv[1]
    frames = load_pack(name)
    print(f"{name}: {len(frames)} frames")
    for fi in sorted(LABELS):
        w = frames[fi][0]
        print(f"   frame {fi:2}: {LABELS[fi]:8s} {text_width(LABELS[fi]):2d}px in {w}px plate")
    save_pack(name, repaint(frames))
    print(f"wrote {name}.spk + {name}.spki")
