# Sprite tools — editing baked-in UI text

Some UI text is **not** in any string table. Button labels on the title screen,
the game menu and most UI chrome are **pixels baked into `.spk` sprite packs**
inside `Release/Data/darkeden.dpk`. Grepping `String.inf` for them finds nothing —
that is not "untranslated", it is "not text".

See `Tools/Localization/README.md` for the other two text sources
(string tables and `NPCScript.inf`).

## The three-source rule

| On screen | Lives in | Edit with |
|---|---|---|
| Messages, tooltips, system text | `Data/info/String.inf` → `String.en.inf` | `Tools/Localization/stringtable.ps1` |
| NPC dialogue | `Data/info/NPCScript.inf` | `Tools/Localization/npcscriptinf.ps1` |
| **Button labels, UI chrome** | **`.spk` inside `darkeden.dpk`** | **these tools** |

## Tools

| File | Purpose |
|---|---|
| `dpkget.exe` | Extract named files out of `darkeden.dpk` |
| `dpkget.cpp` / `build.bat` | Source + build (links the client's own `VirtualFileSystem.lib`) |
| `spk.py` | `.spk` ⇄ PNG. Pure stdlib, no PIL needed |

`dpkget` uses the client's own VFS, so decompression is identical to what the
game does at runtime — no format guessing.

## Workflow

Work on a **copy** of the archive (see the warning below).

```
# 1. extract the pack and its index (you need BOTH files)
dpkget.exe darkeden out data/ui/spk/titlemenudefault.spk data/ui/spk/titlemenudefault.spki

# 2. explode to PNGs  ->  titlemenudefault_00.png .. _09.png
python spk.py decode titlemenudefault

# 3. repaint the labels in any image editor.
#    KEEP the canvas size. Save as 8-bit RGBA, non-interlaced.
#    Fully transparent = alpha 0.

# 4. rebuild (second arg = frame count)
python spk.py encode titlemenudefault 10

# 5. install as loose files - NO repacking required
copy titlemenudefault.spk  ..\..\Release\Data\ui\spk\
copy titlemenudefault.spki ..\..\Release\Data\ui\spk\
```

Loose files win over the archive: `VirtualFileSystem/vfstream.cpp:30` does
`_access(szName, 0)` and only falls back to the `.dpk` when the file is absent
from disk. `Release/Data/ui/spk/Minimap.spk` already ships this way.

## Round-trip is lossless

`decode` → `encode` with no edits reproduces the original **byte for byte**.
Verified on `titlemenudefault` (10 frames), `titlemenuselect` (4),
`loginmenu` (6), `gamemenuslayer` (5), `commonbutton` (18) and
`title1024` (4 frames, 1.8 MB).

If you ever get a mismatch on an *unedited* file, stop — the pack is a variant
this decoder does not handle, and encoding it would corrupt the art.

## Title screen frame map

`titlemenudefault.spk`, 10 frames of 73x23. Order matches
`enum TITLE_SPK` in `UI/VSUI/VS_UI_Newtitle.h`. Even = hover (cyan),
odd = normal (grey).

| Frame | Sprite ID | Korean | English |
|---|---|---|---|
| 0 / 1 | `CONNECT_HILIGHT` / `CONNECT_PUST` | 게임접속 | Connect |
| 2 / 3 | `OPTION_HILIGHT` / `OPTION_PUSH` | 게임옵션 | Options |
| 4 / 5 | `CREDIT_HILIGHT` / `CREDIT_PUSH` | 만든사람들 | Credits |
| 6 / 7 | `EXIT_HILIGHT` / `EXIT_PUSH` | 게임종료 | Exit |
| 8 / 9 | `NEWID_HILIGHT` / `NEWID_PUSH` | 계정생성 | Create Account |

Button hit-boxes come from the sprite's own width/height
(`VS_UI_NewTitle.cpp:6889`), so **keep each frame's dimensions unchanged** or the
clickable area moves.

## Format

`.spki` — `WORD frameCount`, then `frameCount` x `DWORD` offset into `.spk`.

`.spk` — `WORD frameCount`, then per frame at its offset:

```
WORD width, WORD height
per row (height rows):
  WORD len              # number of WORDs following for this row
  WORD data[len]
    data[0] = runCount
    runCount x ( WORD transparentPixels, WORD colourPixels, WORD colours[] )
```

Colours are RGB565. Transparency is **positional** — pixels skipped by
`transparentPixels` — not a colour key, so black is a real colour.
Trailing transparency emits no run at all; emitting one still renders correctly
but will not byte-match the original.

Reference implementation: `SpriteLib/CSprite555.cpp`, `LoadFromFile` / `SaveToFile`.

## WARNING — never unpack into `Release/Data`

The archive contains `data/info/*.inf`, including `string.inf`, `creature.inf`
and `npcscript.inf`. Unpacking over `Release/Data` **overwrites the Korean
`String.inf` original and every translated `.inf`** with the 2021 archive copies.

`Data/NewDpkUnpaker.exe` is a debug build that pops a blocking assertion dialog
on bad input — prefer `dpkget.exe`, which takes explicit paths and only writes
the files you name.

Always work on a copy of `darkeden.dpk` + `darkeden.dpi` outside the client tree.
