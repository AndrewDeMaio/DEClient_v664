"""
charmanager_en.py - repaint the character-select screen in English.

charmanager.spk, frame map from enum CHAR_MANAGER_SPK_ID (VS_UI_Newtitle.h):

    9/10   CREATE_BUTTON_PUSHED / CREATE_BUTTON        캐릭터생성 -> CREATE
    11/12  DELETE_BUTTON_PUSHED / DELETE_BUTTON        캐릭터삭제 -> DELETE
    13/14  GAME_START_PUSHED / GAME_START              게임시작   -> START
    15/16  PREV_SCREEN_BUTTON_PUSHED / PREV_SCREEN     이전화면   -> BACK
    7      CAHR_INFO_ANGLE_1024_768                    "Character info" header

The header is already English, but in an ornate serif that overruns its plate.
Rather than replace it with the blocky pixel font used elsewhere, the existing
"Character" lettering is kept: " info" is erased and "Character" is shifted
right so it sits centred on the plate.

Erasing there cannot use the usual left/right interpolation - the plate is an
oval with a vertical gradient, so interpolating across would smear its shape.
The band is rebuilt by interpolating each column between the row above and the
row below the text instead.

usage:  python charmanager_en.py <name>
"""
import sys, os
from collections import Counter
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from spk import load_pack, save_pack, from565, to565
from optiontitle_en import FONT
from serverselect_en import paint, lum, lerp, text_width

# 73x23 plates, same geometry as the title-menu and server-select buttons.
BUTTONS = [
    (9,  "CREATE"), (10, "CREATE"),
    (11, "DELETE"), (12, "DELETE"),
    (13, "START"),  (14, "START"),
    (15, "BACK"),   (16, "BACK"),
]
BTN_EX0, BTN_EX1, BTN_AL, BTN_AR = 10, 63, 9, 64
BTN_EY0, BTN_EY1, BTN_TOP = 6, 16, 8

# --- header (frame 7) -------------------------------------------------------
#
# The header already reads "Character info" in an ornate serif. Keeping that
# lettering beats redrawing it in the blocky pixel font, so " info" is dropped
# and "Character" is shifted right to sit centred on the plate.
#
# Two earlier approaches failed and are worth recording:
#
#  * Rebuilding the plate by interpolating between the rows above and below the
#    text. The plate is a shallow oval only ~13 rows tall and the lettering
#    fills nearly all of it, so those rows are the silver frame, not plate --
#    the oval washed out completely.
#  * Capturing letters by luminance threshold. The plate tone swings from 8 to
#    130 down its gradient, so no single cut-off separates ink from plate.
#
# What works: erase with the per-row modal colour (rowmode), which reproduces
# the dark oval correctly, then recover the lettering by DIFFING the original
# against that erased plate. Whatever changed is ink, with no threshold needed.
# The header reads "Character info" in an ornate serif with a decorative
# flourish at each end. It is not misaligned - it is symmetric between the
# flourishes - the plate is simply too narrow, so the "o" of "info" collides
# with the right flourish.
#
# The text is therefore left completely alone and the PLATE is widened instead.
# Two earlier approaches, both abandoned:
#
#  * Drop " info" and re-centre "Character". The ornate C's flourish sweeps down
#    and to the left of the letter body, so moving only the letters strands the
#    flourish as a blob. A column census suggested a clean gap at x 65..67, but
#    that gap is an artifact of pooling rows - the flourish occupies different
#    ROWS at those columns, not different columns.
#  * Rebuild the vacated plate by interpolation or per-row modal fill. The first
#    washes the dark oval into a pale gradient; the second picks the highlight
#    tone on the glossy row and draws a hard line across the plate.
#
# Widening keeps every glyph byte-exact. Bare plate columns are inserted at two
# seams that carry no ink, so the caps slide outward and the oval simply gets
# longer:
#
#   x  54..157  plate today
#   x  66       bare seam, between the left cap and the flourish
#   x 145       bare seam, between "info" and the right flourish
#
# Rows 0..19 float on transparency; from row 20 the plate overlaps the panel's
# arcs, so transparent pixels are not written there - that would punch holes in
# the panel behind it.
HDR_FRAME = 7
HDR_K      = 4            # columns inserted at EACH seam -> plate grows 2K
HDR_LSEAM  = 66
HDR_RSEAM  = 145
HDR_PL, HDR_PR = 54, 157  # plate extent before widening
HDR_TOP, HDR_BOT = 0, 35  # plate's vertical extent
HDR_FLOAT_TO = 19         # last row where the plate floats on transparency


# NOT DONE: capitalising the "i" of "info".
#
# There is no capital I anywhere in this sprite, so it has to be constructed,
# and the face is too small to carry one. Metrics from a luminance dump of
# rows 13..24:
#
#   x 123..125  the lowercase "i" - dot on rows 14..15, a ONE-pixel stem at x124
#   x 125..126  gap
#   x 127       the "n" left stem
#
# With a 1px stem and a 10-row cap height, a serif capital I differs from a
# lowercase i only in the top serif, and three weights were tried:
#
#   stem from the "h" ascender  - too bold. "Character" is set heavier than
#                                 "info" (stem luminance 121..235 vs 72), so it
#                                 read as a different, more detailed face.
#   1px stem, 3px serif         - indistinguishable from the lowercase i.
#   2px stem, 4-5px serif       - the serif reads as a dash floating above a
#                                 thin stem, not as a letter.
#
# So the lowercase "info" is kept. Widening the plate was the real fix for the
# cramped look; capitalising adds nothing this typeface can express at 10px.
#
# (Also worth recording: the "n" begins at x127. An early attempt wiped through
# 127 and clipped it.)


def repaint_header(w, h, rows):
    out = [list(r) for r in rows]

    def src_for(nx):
        if nx < HDR_LSEAM - HDR_K:  return nx + HDR_K      # left cap, shifted out
        if nx < HDR_LSEAM:          return HDR_LSEAM       # inserted plate
        if nx < HDR_RSEAM:          return nx              # text, untouched
        if nx < HDR_RSEAM + HDR_K:  return HDR_RSEAM       # inserted plate
        return nx - HDR_K                                  # right cap, shifted out

    nl, nr = HDR_PL - HDR_K, HDR_PR + HDR_K
    for y in range(HDR_TOP, HDR_BOT+1):
        newvals = {}
        for nx in range(nl, nr+1):
            sx = src_for(nx)
            newvals[nx] = rows[y][sx] if 0 <= sx < w else None
        for nx, v in newvals.items():
            if v is None and y > HDR_FLOAT_TO:
                continue      # keep the panel visible behind the plate's corners
            out[y][nx] = v
    return out


def repaint(frames):
    out = [(w, h, [list(r) for r in rows]) for (w, h, rows) in frames]
    for fi, label in BUTTONS:
        w, h, rows = out[fi]
        paint(rows, w, BTN_EX0, BTN_EX1, BTN_AL, BTN_AR,
              BTN_EY0, BTN_EY1, BTN_TOP, label, 1, False)

    w, h, rows = out[HDR_FRAME]
    out[HDR_FRAME] = (w, h, repaint_header(w, h, rows))
    return out


if __name__ == '__main__':
    name = sys.argv[1]
    frames = load_pack(name)
    print(f"{name}: {len(frames)} frames")
    for fi, label in BUTTONS:
        print(f"   frame {fi:2}: {label:7s} {text_width(label,1):2d}px in {BTN_EX1-BTN_EX0+1}px plate")
    print(f"   frame {HDR_FRAME:2}: header -> 'Character' shifted +{HDR_SHIFT}px, ' info' removed")
    save_pack(name, repaint(frames))
    print(f"wrote {name}.spk + {name}.spki")
