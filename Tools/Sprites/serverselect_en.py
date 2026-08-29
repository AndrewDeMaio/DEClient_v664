"""
serverselect_en.py - repaint the server/channel select screen in English.

serverselect.spk holds ten pieces of baked Korean text:

    frame 0   panel title    차원선택            -> SERVER
    frame 1   panel title    채널선택            -> CHANNEL
    frame 1   column headers 채 널 / 상 태 /
                             채널별 종족 정보    -> CHANNEL / STATUS / RACE INFO
    frames 2,3  button       이전화면            -> BACK      (hover, normal)
    frames 4,5  button       다음화면            -> NEXT      (hover, normal)
    frame 16    legend       슬레이어 / 뱀파이어 /
                             아우스터즈          -> SLAYER / VAMPIRE / OUSTERS

Frames 6..9 are the coloured race dots, 10..13 the selection highlight bars,
14/15 the message panel - none carry text, so they are left alone.

usage:  python serverselect_en.py <name>    # reads <name>.spk/.spki, rewrites them
"""
import sys, os
from collections import Counter
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from spk import load_pack, save_pack, from565, to565
from optiontitle_en import FONT

# (frame, ex0, ex1, anchorL, anchorR, ey0, ey1, textTop, label, gap, darkText)
REGIONS = [
    # Panel titles - light text on the ornate plate. Glyphs occupy rows 12..22,
    # so the erase band must reach 23 or the last row of Korean survives.
    (0,  62, 117,  60, 119, 11, 23, 14, "SERVER",    1, False),
    (1, 132, 187, 130, 189, 11, 23, 14, "CHANNEL",   1, False),

    # Column headers - DARK text on a light grey plate (tone ~121). The plate
    # spans rows 47..61 with glyphs on 49..60; anchors sit inside the plate,
    # clear of the centred text.
    (1,  40, 127,  38, 129, 48, 60, 51, "CHANNEL",   1, True),
    (1, 146, 198, 144, 200, 48, 60, 51, "STATUS",    1, True),
    (1, 211, 285, 209, 286, 48, 60, 51, "RACE INFO", 1, True),

    # buttons - same 73x23 plate as the title menu buttons
    (2, 10, 63,  9, 64,  6, 16,  8, "BACK", 1, False),
    (3, 10, 63,  9, 64,  6, 16,  8, "BACK", 1, False),
    (4, 10, 63,  9, 64,  6, 16,  8, "NEXT", 1, False),
    (5, 10, 63,  9, 64,  6, 16,  8, "NEXT", 1, False),

    # Legend strip: 143x10 and almost entirely TRANSPARENT - the labels sit on
    # nothing, not on a plate. Interpolating a background is meaningless here,
    # so these regions are cleared to transparency instead (see CLEAR_FRAMES).
    # Only 143px wide for three labels, so letters are packed with no gap.
    # Coloured dots occupy x 1..3, 50..52 and 99..101 - clear starts just past
    # each dot so the dot survives but no Korean fragment does.
    (16,   4,  47,   4,  47, 0, 9, 2, "SLAYER",  0, False),
    (16,  53,  96,  53,  96, 0, 9, 2, "VAMPIRE", 0, False),
    (16, 102, 142, 102, 142, 0, 9, 2, "OUSTERS", 0, False),
]

# Frames whose text sits on transparency rather than a drawn plate.
CLEAR_FRAMES = {16}


def lum(v):
    r, g, b = from565(v)
    return (r*299 + g*587 + b*114) // 1000

def lerp(a, b, t):
    return tuple(round(a[i] + (b[i]-a[i])*t) for i in range(3))

def text_width(s, gap=1):
    return sum(len(FONT[c][0]) for c in s) + max(0, len(s)-1) * gap


def paint(rows, w, ex0, ex1, al, ar, ey0, ey1, top, label, gap, dark,
          clear=False, rowmode=False):
    """
    rowmode: fill each row with that row's most common colour instead of
    interpolating between the anchors. Needed where the plate is dark in the
    middle and light at its ends (an oval), since blending anchor to anchor
    would wash the middle out. Text is a minority of pixels, so the mode is the
    plate colour.
    """
    ex1 = min(ex1, w-1); ar = min(ar, w-1); al = max(al, 0)

    if clear:
        # Text on transparency: take the brightest existing glyph tone, wipe the
        # region to transparent, then draw. No background to reconstruct.
        cand = Counter()
        for y in range(ey0, ey1+1):
            for x in range(ex0, ex1+1):
                v = rows[y][x]
                if v is not None: cand[v] += 1
        body = (240, 240, 240)
        for v, n in sorted(cand.items(), key=lambda kv: -lum(kv[0])):
            if n >= 4:
                body = from565(v); break
        if lum(to565(*body)) < 150:
            body = (240, 240, 240)

        for y in range(ey0, ey1+1):
            for x in range(ex0, ex1+1):
                rows[y][x] = None

        tw = text_width(label, gap)
        x0 = ex0 + ((ex1-ex0+1) - tw)//2
        cx = x0
        for ch in label:
            gl = FONT[ch]
            for gy, line in enumerate(gl):
                for gx, p in enumerate(line):
                    if p != '#': continue
                    px, py = cx+gx, top+gy
                    if ex0 <= px <= ex1 and ey0 <= py <= ey1:
                        rows[py][px] = to565(*body)
            cx += len(gl[0]) + gap
        return

    bgc = Counter()
    for y in range(ey0, ey1+1):
        for x in (al, al+1, ar-1, ar):
            if 0 <= x < w and rows[y][x] is not None: bgc[rows[y][x]] += 1
    if not bgc:
        return
    bgv = bgc.most_common(1)[0][0]
    bl  = lum(bgv)

    # glyph tone: darkest on a light plate, brightest on a dark one
    cand = Counter()
    for y in range(ey0, ey1+1):
        for x in range(ex0, ex1+1):
            v = rows[y][x]
            if v is None: continue
            if dark and lum(v) < bl - 25: cand[v] += 1
            elif not dark and lum(v) > bl + 25: cand[v] += 1

    body = None
    order = sorted(cand.items(), key=lambda kv: (lum(kv[0]) if dark else -lum(kv[0])))
    for v, n in order:
        if n >= 3:
            body = from565(v); break

    if dark:
        if body is None or lum(to565(*body)) > bl - 55: body = (20, 20, 20)
        r, g, b = from565(bgv)
        shadow = (min(255, r+70), min(255, g+70), min(255, b+70))
    else:
        if body is None or lum(to565(*body)) < bl + 55: body = (240, 240, 240)
        r, g, b = from565(bgv)
        shadow = (max(0, r-90), max(0, g-90), max(0, b-90))

    # erase: rebuild the plate across the text window
    for y in range(ey0, ey1+1):
        if rowmode:
            rc = Counter(rows[y][x] for x in range(ex0, ex1+1) if rows[y][x] is not None)
            if not rc: continue
            fill = rc.most_common(1)[0][0]
            for x in range(ex0, ex1+1):
                rows[y][x] = fill
            continue
        cl, cr = rows[y][al], rows[y][ar]
        if cl is None or cr is None: continue
        a, bb = from565(cl), from565(cr)
        span = max(1, ar - al)
        for x in range(ex0, ex1+1):
            rows[y][x] = to565(*lerp(a, bb, (x-al)/span))

    # draw centred, shadow first
    tw = text_width(label, gap)
    x0 = ex0 + ((ex1-ex0+1) - tw)//2
    for dx, dy, col in ((1, 1, shadow), (0, 0, body)):
        cx = x0 + dx
        for ch in label:
            gl = FONT[ch]
            for gy, line in enumerate(gl):
                for gx, p in enumerate(line):
                    if p != '#': continue
                    px, py = cx+gx, top+gy+dy
                    if ex0 <= px <= ex1 and ey0 <= py <= ey1:
                        rows[py][px] = to565(*col)
            cx += len(gl[0]) + gap


def repaint(frames):
    out = [(w, h, [list(r) for r in rows]) for (w, h, rows) in frames]
    for (fi, ex0, ex1, al, ar, ey0, ey1, top, label, gap, dark) in REGIONS:
        w, h, rows = out[fi]
        paint(rows, w, ex0, ex1, al, ar, ey0, ey1, top, label, gap, dark,
              clear=(fi in CLEAR_FRAMES))
    return out


if __name__ == '__main__':
    name = sys.argv[1]
    frames = load_pack(name)
    print(f"{name}: {len(frames)} frames")
    for (fi, ex0, ex1, al, ar, ey0, ey1, top, label, gap, dark) in REGIONS:
        print(f"   frame {fi:2}: {label:10s} {text_width(label,gap):3d}px in {ex1-ex0+1:3d}px"
              f"  {'(dark text)' if dark else ''}")
    save_pack(name, repaint(frames))
    print(f"wrote {name}.spk + {name}.spki")
