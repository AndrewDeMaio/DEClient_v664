"""dpkunmask - recover files from a newer-format .dpk that dpkget extracts corrupt.

Why this exists
---------------
VFS_Macro.h's encrypt_data() XORs a masking string over the compressed payload
at `key % (size - masksize)`, where `key` is a djb2 hash of the file path. The
v664 client uses a 16-byte mask; 2019-era archives (e.g. sandbox_v9) use a
32-byte mask AND a different key derivation, so dpkget applies the wrong mask.

That damages exactly 32 bytes in the middle of the deflate stream, which is why
the result is *silently* wrong rather than a hard failure: zlib inflates
correctly up to the damaged bytes and then produces garbage. The client's
uncompress() leaves the rest of its buffer as uninitialized heap, so the file
looks like half-good art. Every data/ui/spk/*.spk in sandbox_v9 is affected.

We do not know the 2019 key derivation, and we do not need it: zlib's Adler-32
makes a candidate offset self-verifying, so we locate the mask empirically.

Usage
-----
    dpkraw.exe <vfsbase> <rawdir> <vpath> [vpath ...]      # dump stored bytes
    python dpkunmask.py <rawdir> <outdir>                  # repair them

Multi-megabyte files are slow: each probe costs a full inflate.
"""
import os
import struct
import sys
import zlib

MASK = b'HGHYPWXB5BRelease01u-n:s8hrecpin'   # 2019-era archives
CHUNK = 64                                    # input-sampling granularity


# ------------------------------------------------------------------ container
def parse(raw):
    """Split a dpkraw dump into its headers and the stored payload.

    Layout: VirtualFileHeader (6) + CVFHeader (5) + payload.
    """
    filesize, version, iscompressed = struct.unpack_from('<IBB', raw, 0)
    compsize, incompressible = struct.unpack_from('<IB', raw, 6)
    return filesize, version, iscompressed, compsize, incompressible, raw[11:11 + compsize]


# ----------------------------------------------------------------- spk probing
def spk_bad_offset(d):
    """First output offset where .spk sprite structure breaks, else None.

    Mirrors CSprite565::LoadFromFile: WORD count, then per sprite WORD width,
    WORD height, then `height` rows of WORD len + len*2 bytes.
    """
    if len(d) < 2:
        return 0
    count = struct.unpack_from('<H', d, 0)[0]
    p = 2
    for i in range(count):
        if p + 4 > len(d):
            return p
        w, h = struct.unpack_from('<HH', d, p)
        p += 4
        if w == 0 or h == 0:
            continue
        for _ in range(h):
            if p + 2 > len(d):
                return p
            ln = struct.unpack_from('<H', d, p)[0]
            p += 2 + ln * 2
            if p > len(d):
                return min(p, len(d))
    return None if p == len(d) else p


def scan(payload):
    """Inflate as far as the damage allows.

    Returns (partial_output, curve), curve being [(input_consumed, output_len)]
    sampled every CHUNK bytes. Feeding incrementally keeps the output produced
    before zlib gives up, which a single decompress() would discard with the
    exception.
    """
    d = zlib.decompressobj()
    points, chunks, out = [], [], 0
    for i in range(0, len(payload), CHUNK):
        try:
            piece = d.decompress(payload[i:i + CHUNK])
        except zlib.error:
            break
        chunks.append(piece)
        out += len(piece)
        points.append((i + CHUNK, out))
        if d.eof:
            break
    return b''.join(chunks), points


def estimate(payload):
    """Guess the mask offset: find where output stops being a valid .spk, then
    map that back to an input offset through the stream's own I/O curve."""
    partial, points = scan(payload)
    if not points:
        return 0
    bad = spk_bad_offset(partial)
    if bad is None:
        bad = len(partial)
    for consumed, produced in points:
        if produced >= bad:
            return max(0, consumed - CHUNK)
    return max(0, points[-1][0] - CHUNK)


# --------------------------------------------------------------------- recover
def solve(raw):
    """Return (data, mask_offset). mask_offset is None if the file needed no
    repair, -1 if it was stored uncompressed, else the offset we un-masked."""
    filesize, _, _, compsize, incompressible, payload = parse(raw)
    if incompressible:
        return payload[:filesize], -1
    try:
        out = zlib.decompress(payload)
        if len(out) == filesize:
            return out, None
    except zlib.error:
        pass

    limit = compsize - len(MASK)
    if limit < 0:
        return None, None

    start = min(max(estimate(payload), 0), limit)
    buf = bytearray(payload)
    seen = set()
    for delta in range(0, limit + 2):
        for p in (start - delta, start + delta):
            if not (0 <= p <= limit) or p in seen:
                continue
            seen.add(p)
            for i in range(len(MASK)):
                buf[p + i] ^= MASK[i]
            try:
                out = zlib.decompress(bytes(buf))
                if len(out) == filesize:
                    return out, p
            except zlib.error:
                pass
            for i in range(len(MASK)):
                buf[p + i] ^= MASK[i]
        if len(seen) > limit + 1:
            break
    return None, None


def make_spki(spk):
    """Rebuild a .spki from a .spk. 14 of sandbox_v9's 233 .spki files hold
    unrelated UTF-16 path fragments; only LoadFromFileRunning reads them, but
    regenerating costs nothing and keeps the pair consistent."""
    count = struct.unpack_from('<H', spk, 0)[0]
    p, offsets = 2, []
    for _ in range(count):
        offsets.append(p)
        w, h = struct.unpack_from('<HH', spk, p)
        p += 4
        if w == 0 or h == 0:
            continue
        for _ in range(h):
            p += 2 + struct.unpack_from('<H', spk, p)[0] * 2
    return struct.pack('<H', count) + b''.join(struct.pack('<I', o) for o in offsets)


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    rawdir, outdir = sys.argv[1], sys.argv[2]
    os.makedirs(outdir, exist_ok=True)

    names = sorted(n for n in os.listdir(rawdir) if n.endswith('.raw'))
    names.sort(key=lambda n: os.path.getsize(os.path.join(rawdir, n)))   # quick wins first
    ok = bad = 0
    for n in names:
        name = n[:-4]
        raw = open(os.path.join(rawdir, n), 'rb').read()
        data, offset = solve(raw)
        if data is None:
            print('  FAILED  %s' % name, flush=True)
            bad += 1
            continue
        open(os.path.join(outdir, name), 'wb').write(data)
        note = 'clean' if offset is None else ('stored' if offset == -1 else 'mask@%d' % offset)
        if name.endswith('.spk'):
            open(os.path.join(outdir, name + 'i'), 'wb').write(make_spki(data))
        print('  ok      %-44s %s' % (name, note), flush=True)
        ok += 1
    print('\nrecovered %d, failed %d' % (ok, bad))
    return 0 if bad == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
