"""
titlemenu_en.py - repaint titlemenudefault.spk button labels in English.

Erases the Korean glyphs from the button plate (rebuilding the panel gradient
underneath) and draws English text in the plate's own text colours.

Frame order follows enum TITLE_SPK in UI/VSUI/VS_UI_Newtitle.h:
even = hover (bright), odd = normal.

usage:  python titlemenu_en.py <name>     # reads <name>.spk/.spki, rewrites them
"""
import sys, os
from collections import Counter
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from spk import load_pack, save_pack, from565, to565

LABELS = ["CONNECT", "CONNECT", "OPTIONS", "OPTIONS", "CREDITS",
          "CREDITS", "EXIT", "EXIT", "REGISTER", "REGISTER"]

# erase window - inside the flat part of the plate, clear of the bevel
EX0, EX1, EY0, EY1 = 10, 63, 6, 16
AL, AR = 9, 64          # background anchor columns (known clean)
TEXT_TOP = 8            # 7px font -> rows 8..14, centred in the 6..16 band

F = {
' ': ["     "]*7,
'A': [".###.","#...#","#...#","#####","#...#","#...#","#...#"],
'C': [".###.","#...#","#....","#....","#....","#...#",".###."],
'D': ["####.","#...#","#...#","#...#","#...#","#...#","####."],
'E': ["#####","#....","#....","####.","#....","#....","#####"],
'G': [".###.","#...#","#....","#.###","#...#","#...#",".###."],
'I': ["###",".#.",".#.",".#.",".#.",".#.","###"],
'N': ["#...#","##..#","##..#","#.#.#","#..##","#..##","#...#"],
'O': [".###.","#...#","#...#","#...#","#...#","#...#",".###."],
'P': ["####.","#...#","#...#","####.","#....","#....","#...."],
'R': ["####.","#...#","#...#","####.","#.#..","#..#.","#...#"],
'S': [".####","#....","#....",".###.","....#","....#","####."],
'T': ["#####","..#..","..#..","..#..","..#..","..#..","..#.."],
'U': ["#...#","#...#","#...#","#...#","#...#","#...#",".###."],
'X': ["#...#","#...#",".#.#.","..#..",".#.#.","#...#","#...#"],
}

def text_width(s):
    return sum(len(F[c][0]) for c in s) + max(0, len(s)-1)

def lerp(a, b, t):
    return tuple(round(a[i] + (b[i]-a[i])*t) for i in range(3))

def repaint(frames):
    out = []
    for fi, (w, h, rows) in enumerate(frames):
        rows = [list(r) for r in rows]
        hover = (fi % 2 == 0)

        # colours sampled from the plate this frame actually uses
        body   = (210, 219, 219) if hover else (150, 152, 160)
        shadow = (0, 40, 48)     if hover else (0, 0, 16)

        # 1. erase: rebuild the panel background across the text window
        for y in range(EY0, EY1+1):
            cl, cr = rows[y][AL], rows[y][AR]
            if cl is None or cr is None:
                continue
            a, b = from565(cl), from565(cr)
            span = AR - AL
            for x in range(EX0, EX1+1):
                rows[y][x] = to565(*lerp(a, b, (x-AL)/span))

        # 2. draw the label, centred, shadow first
        label = LABELS[fi]
        tw = text_width(label)
        x0 = EX0 + ((EX1-EX0+1) - tw)//2
        for dx, dy, col in ((1, 1, shadow), (0, 0, body)):
            cx = x0 + dx
            for ch in label:
                g = F[ch]
                for gy, line in enumerate(g):
                    for gx, p in enumerate(line):
                        if p != '#':
                            continue
                        px, py = cx+gx, TEXT_TOP+gy+dy
                        if EX0 <= px <= EX1 and EY0 <= py <= EY1:
                            rows[py][px] = to565(*col)
                cx += len(g[0]) + 1
        out.append((w, h, rows))
    return out

if __name__ == '__main__':
    name = sys.argv[1]
    frames = load_pack(name)
    print(f"{name}: {len(frames)} frames")
    for i, l in enumerate(LABELS[:len(frames)]):
        print(f"   frame {i}: {l:9s} width={text_width(l):2d}px  (window {EX1-EX0+1}px)")
    save_pack(name, repaint(frames))
    print(f"wrote {name}.spk + {name}.spki")
