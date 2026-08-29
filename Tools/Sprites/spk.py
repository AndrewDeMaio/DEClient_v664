"""
spk.py - decode/encode DarkEden .spk sprite packs (CSprite555 format).

Format, per SpriteLib/CSprite555.cpp LoadFromFile/SaveToFile:

  .spki : WORD frameCount, then frameCount * DWORD offset-into-.spk
  .spk  : per frame at its offset:
            WORD width, WORD height
            per row (height rows):
              WORD len                 # count of WORDs that follow for this row
              WORD data[len]:
                data[0] = runCount
                then runCount * ( WORD transparentPixels, WORD colorPixels,
                                  WORD colors[colorPixels] )   # RGB565

Transparency is positional (skipped pixels), not a colour key.

usage:
  python spk.py decode <name>          # <name>.spk/.spki -> <name>_NN.png + _sheet.png
  python spk.py encode <name> <n>      # <name>_NN.png (n of them) -> <name>.spk/.spki
"""
import struct, zlib, sys, os

# ---------------------------------------------------------------- PNG helpers
def png_write(path, w, h, rgba):
    def chunk(t, d):
        c = t + d
        return struct.pack('>I', len(d)) + c + struct.pack('>I', zlib.crc32(c) & 0xffffffff)
    raw = b''.join(b'\x00' + bytes(rgba[y*w*4:(y+1)*w*4]) for y in range(h))
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n'
        + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 6, 0, 0, 0))
        + chunk(b'IDAT', zlib.compress(raw, 9)) + chunk(b'IEND', b''))

def png_read(path):
    d = open(path, 'rb').read()
    assert d[:8] == b'\x89PNG\r\n\x1a\n', f"{path}: not a PNG"
    pos, idat, w = 8, b'', None
    while pos < len(d):
        ln, = struct.unpack_from('>I', d, pos)
        typ = d[pos+4:pos+8]
        body = d[pos+8:pos+8+ln]
        if typ == b'IHDR':
            w, h, depth, ctype, comp, filt, inter = struct.unpack('>IIBBBBB', body)
            assert depth == 8 and ctype == 6 and inter == 0, \
                f"{path}: need 8-bit RGBA non-interlaced (got depth={depth} colortype={ctype} interlace={inter})"
        elif typ == b'IDAT':
            idat += body
        pos += 12 + ln
    raw = zlib.decompress(idat)
    out, stride, prev = bytearray(), w*4, bytes(w*4)
    p = 0
    for _ in range(h):
        f = raw[p]; p += 1
        line = bytearray(raw[p:p+stride]); p += stride
        for i in range(stride):
            a = line[i-4] if i >= 4 else 0
            b = prev[i]
            c = prev[i-4] if i >= 4 else 0
            if   f == 1: line[i] = (line[i] + a) & 0xff
            elif f == 2: line[i] = (line[i] + b) & 0xff
            elif f == 3: line[i] = (line[i] + ((a+b) >> 1)) & 0xff
            elif f == 4:
                pa, pb, pc = abs(b-c), abs(a-c), abs(a+b-2*c)
                pr = a if (pa <= pb and pa <= pc) else (b if pb <= pc else c)
                line[i] = (line[i] + pr) & 0xff
        out += line; prev = bytes(line)
    return w, h, out

def to565(r, g, b):  return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)
def from565(v):      return ((v >> 11 & 0x1f)*255//31, (v >> 5 & 0x3f)*255//63, (v & 0x1f)*255//31)

# ------------------------------------------------------------------- decoding
def decode_frame(spk, off):
    w, h = struct.unpack_from('<HH', spk, off)
    pos, rows = off + 4, []
    for _ in range(h):
        ln, = struct.unpack_from('<H', spk, pos); pos += 2
        row = struct.unpack_from('<%dH' % ln, spk, pos); pos += ln*2
        px, idx, x = [None]*w, 1, 0
        for _ in range(row[0]):
            trans, ncol = row[idx], row[idx+1]; idx += 2
            x += trans
            for _ in range(ncol):
                if 0 <= x < w: px[x] = row[idx]
                idx += 1; x += 1
        rows.append(px)
    return w, h, rows, pos

def load_pack(name):
    spk = open(name + '.spk', 'rb').read()
    idx = open(name + '.spki', 'rb').read()
    n, = struct.unpack_from('<H', idx, 0)
    offs = [struct.unpack_from('<I', idx, 2+4*i)[0] for i in range(n)]
    frames = []
    for i, off in enumerate(offs):
        w, h, rows, end = decode_frame(spk, off)
        want = offs[i+1] if i+1 < len(offs) else len(spk)
        if end != want:
            print(f"  WARNING frame {i}: decoder ended at {end}, expected {want}")
        frames.append((w, h, rows))
    return frames

# ------------------------------------------------------------------- encoding
def encode_frame(w, h, rows):
    """rows[y][x] = None (transparent) or WORD colour."""
    out = struct.pack('<HH', w, h)
    for y in range(h):
        runs, x = [], 0
        while x < w:
            t = 0
            while x < w and rows[y][x] is None: t += 1; x += 1
            cols = []
            while x < w and rows[y][x] is not None: cols.append(rows[y][x]); x += 1
            # a run exists only to carry colour; trailing transparency is implicit
            if cols: runs.append((t, cols))
        body = [len(runs)]
        for t, cols in runs:
            body += [t, len(cols)] + cols
        out += struct.pack('<H', len(body)) + struct.pack('<%dH' % len(body), *body)
    return out

def save_pack(name, frames):
    spk, offs = b'', []
    for (w, h, rows) in frames:
        offs.append(len(spk) + 2)          # +2: pack starts with the WORD count
        spk += encode_frame(w, h, rows)
    idx = struct.pack('<H', len(frames)) + b''.join(struct.pack('<I', o) for o in offs)
    open(name + '.spk',  'wb').write(struct.pack('<H', len(frames)) + spk[0:0] + spk)
    open(name + '.spki', 'wb').write(idx)
    return len(spk) + 2

# ----------------------------------------------------------------------- main
if __name__ == '__main__':
    cmd = sys.argv[1] if len(sys.argv) > 1 else ''
    if cmd == 'decode':
        name = sys.argv[2]
        frames = load_pack(name)
        for i, (w, h, rows) in enumerate(frames):
            buf = bytearray()
            for y in range(h):
                for x in range(w):
                    v = rows[y][x]
                    buf += bytes((*from565(v), 255)) if v is not None else b'\x00\x00\x00\x00'
            png_write(f'{name}_{i:02d}.png', w, h, buf)
        print(f"decoded {len(frames)} frames -> {name}_NN.png")
    elif cmd == 'encode':
        name, n = sys.argv[2], int(sys.argv[3])
        frames = []
        for i in range(n):
            w, h, rgba = png_read(f'{name}_{i:02d}.png')
            rows = []
            for y in range(h):
                px = []
                for x in range(w):
                    o = (y*w + x)*4
                    px.append(None if rgba[o+3] < 128 else to565(rgba[o], rgba[o+1], rgba[o+2]))
                rows.append(px)
            frames.append((w, h, rows))
        total = save_pack(name, frames)
        print(f"encoded {n} frames -> {name}.spk ({total} bytes) + {name}.spki")
    else:
        print(__doc__)
