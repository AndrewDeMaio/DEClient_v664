//---------------------------------------------------------------------------
// CDirectDrawSmooth.cpp
//---------------------------------------------------------------------------
// Filtered upscale for the present path.
//
// The original version of this file was correct but pathologically slow: it
// locked the PRIMARY surface every frame and wrote the scaled image straight
// into it. On a composited desktop a primary-surface lock has to synchronise
// with the compositor, which is expensive, and gets dramatically worse when
// another window holds focus - which is why frame rate here used to depend on
// whether the game was the foreground window. It also unpacked every pixel
// into separate R/G/B channels, roughly 40 integer ops per output pixel.
//
// This version fixes both:
//
//   1. It renders into a persistent offscreen surface and lets the driver blit
//      that 1:1 to the primary. Same path the unfiltered present already used,
//      and the primary is never locked by us.
//
//   2. It interpolates the packed 16-bit pixels directly using the two-field
//      trick - R and B interpolate together because a carry out of B cannot
//      reach R, and G interpolates on its own. That is about 8 ops per output
//      pixel instead of 40, and it collapses the 565/555 handling down to a
//      choice of two mask constants.
//
//   3. The scale is separable: each source row is stretched horizontally once
//      and kept, then dest rows are produced by blending two of those rows
//      vertically. The vertical pass walks contiguous memory, so the compiler
//      can vectorise it. A rolling two-row cache means each source row is
//      stretched exactly once no matter how many dest rows sample it.
//
// The offscreen surface is created in the back buffer's own pixel format, so
// the whole path is format-preserving and there is no conversion anywhere.
//---------------------------------------------------------------------------

#include "CDirectDraw.h"

// Default on. Flip() checks this before calling. Overridden at startup from
// "SmoothScale" in Data\Info\Resolution.inf.
bool CDirectDraw::m_bSmoothScale = true;

//---------------------------------------------------------------------------
// Scratch that persists between frames
//---------------------------------------------------------------------------
static LPDIRECTDRAWSURFACE7	s_pScale  = NULL;	// offscreen render target
static int					s_scaleW  = 0;
static int					s_scaleH  = 0;

static int*					s_xi      = NULL;	// source column per dest column
static int*					s_xw      = NULL;	// and its 5 bit weight
static int					s_xCap    = 0;
static int					s_xForDW  = -1;		// what (dw,sw) the tables describe
static int					s_xForSW  = -1;

static WORD*				s_rowA    = NULL;	// two horizontally stretched
static WORD*				s_rowB    = NULL;	// source rows
static int					s_rowCap  = 0;

//---------------------------------------------------------------------------
// ReleaseSmoothScaleSurface
//
// Called from CDirectDraw::ReleaseSurface() so the offscreen surface does not
// outlive the DirectDraw object it came from.
//---------------------------------------------------------------------------
void CDirectDraw::ReleaseSmoothScaleSurface()
{
	if (s_pScale != NULL)
	{
		s_pScale->Release();
		s_pScale = NULL;
	}

	s_scaleW = 0;
	s_scaleH = 0;

	delete [] s_xi;		s_xi   = NULL;
	delete [] s_xw;		s_xw   = NULL;
	s_xCap   = 0;
	s_xForDW = -1;
	s_xForSW = -1;

	delete [] s_rowA;	s_rowA = NULL;
	delete [] s_rowB;	s_rowB = NULL;
	s_rowCap = 0;
}

//---------------------------------------------------------------------------
// EnsureScaleSurface
//
// An offscreen system memory surface of exactly the destination size, in the
// back buffer's pixel format. System memory because we write it with the CPU;
// the driver handles getting it to the primary.
//---------------------------------------------------------------------------
static bool EnsureScaleSurface(int w, int h)
{
	if (s_pScale != NULL && s_scaleW == w && s_scaleH == h)
	{
		if (s_pScale->IsLost() == DD_OK)
			return true;

		if (SUCCEEDED(s_pScale->Restore()))
			return true;
	}

	// Wrong size, or lost beyond recovery - start over.
	if (s_pScale != NULL)
	{
		s_pScale->Release();
		s_pScale = NULL;
		s_scaleW = 0;
		s_scaleH = 0;
	}

	LPDIRECTDRAW7 pDD = CDirectDraw::GetDD();
	if (pDD == NULL)
		return false;

	DDSURFACEDESC2 ddsd;
	::ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize  = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth  = (DWORD)w;
	ddsd.dwHeight = (DWORD)h;

	ddsd.ddpfPixelFormat.dwSize        = sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags       = DDPF_RGB;
	ddsd.ddpfPixelFormat.dwRGBBitCount = 16;

	if (CDirectDraw::Is565())
	{
		ddsd.ddpfPixelFormat.dwRBitMask = 0xF800;
		ddsd.ddpfPixelFormat.dwGBitMask = 0x07E0;
		ddsd.ddpfPixelFormat.dwBBitMask = 0x001F;
	}
	else
	{
		ddsd.ddpfPixelFormat.dwRBitMask = 0x7C00;
		ddsd.ddpfPixelFormat.dwGBitMask = 0x03E0;
		ddsd.ddpfPixelFormat.dwBBitMask = 0x001F;
	}

	if (FAILED(pDD->CreateSurface(&ddsd, &s_pScale, NULL)))
	{
		s_pScale = NULL;
		return false;
	}

	s_scaleW = w;
	s_scaleH = h;
	return true;
}

//---------------------------------------------------------------------------
// Two-field interpolation
//
// mRB covers red and blue, mG covers green. Because the two fields never touch
// within a word, a carry produced inside one cannot corrupt the other, so both
// channels of a field interpolate in a single multiply. Weights are 5 bit, so
// (field * 32) needs 21 bits at most and stays inside a DWORD.
//---------------------------------------------------------------------------
#define DE_LERP2(a, b, w, iw, mRB, mG)                                        \
	(WORD)(((((((a) & (mRB)) * (iw)) + (((b) & (mRB)) * (w))) >> 5) & (mRB))   \
	     | ((((((a) & (mG))  * (iw)) + (((b) & (mG))  * (w))) >> 5) & (mG)))

//---------------------------------------------------------------------------
// ScaleRowH - stretch one source row across the full destination width
//---------------------------------------------------------------------------
static void ScaleRowH(WORD* pDst, const WORD* pSrc, int dw, int sw,
                      const int* xi, const int* xw, DWORD mRB, DWORD mG)
{
	for (int x = 0; x < dw; ++x)
	{
		const int   x0 = xi[x];
		const int   x1 = (x0 + 1 < sw) ? (x0 + 1) : x0;
		const DWORD w  = (DWORD)xw[x];

		if (w == 0)
		{
			pDst[x] = pSrc[x0];
			continue;
		}

		const DWORD a = pSrc[x0];
		const DWORD b = pSrc[x1];

		pDst[x] = DE_LERP2(a, b, w, 32 - w, mRB, mG);
	}
}

//---------------------------------------------------------------------------
// BlendRowV - one destination row from two stretched source rows
//
// Contiguous in and out, no indirection: this is the pass the compiler can
// vectorise, and it is the larger of the two.
//---------------------------------------------------------------------------
static void BlendRowV(WORD* pDst, const WORD* pA, const WORD* pB, int dw,
                      DWORD w, DWORD mRB, DWORD mG)
{
	if (w == 0)
	{
		::memcpy(pDst, pA, (size_t)dw * sizeof(WORD));
		return;
	}

	const DWORD iw = 32 - w;

	for (int x = 0; x < dw; ++x)
	{
		const DWORD a = pA[x];
		const DWORD b = pB[x];

		pDst[x] = DE_LERP2(a, b, w, iw, mRB, mG);
	}
}

//---------------------------------------------------------------------------
// BltSmoothStretch
//
// pSrcRect : region of the back buffer to present, or NULL for all of it.
//            Fullscreen passes NULL; window mode passes m_rcViewport, which is
//            what the original Blt used as its source rect.
//
// Returns true if it presented, false if it declined (caller must then do the
// normal Blt). On false, neither surface has been modified.
//---------------------------------------------------------------------------
bool CDirectDraw::BltSmoothStretch(const RECT* pSrcRect)
{
	if (m_pDDSPrimary == NULL || m_pDDSBack == NULL)
		return false;

	const int dw = m_rcScreen.right  - m_rcScreen.left;
	const int dh = m_rcScreen.bottom - m_rcScreen.top;
	if (dw <= 1 || dh <= 1)
		return false;

	//-----------------------------------------------------------------------
	// Source
	//-----------------------------------------------------------------------
	DDSURFACEDESC2 sd;
	::ZeroMemory(&sd, sizeof(sd));
	sd.dwSize = sizeof(sd);

	// Lock the whole surface and index into it, rather than locking a sub
	// rect - lPitch then unambiguously describes the full surface stride.
	if (m_pDDSBack->Lock(NULL, &sd, DDLOCK_WAIT | DDLOCK_READONLY | DDLOCK_SURFACEMEMORYPTR, NULL) != DD_OK)
		return false;

	if (sd.ddpfPixelFormat.dwRGBBitCount != 16 || sd.lpSurface == NULL)
	{
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	// 565 has a 6 bit green (0x07E0); 555 has a 5 bit green (0x03E0).
	const DWORD srcG = sd.ddpfPixelFormat.dwGBitMask;
	const bool  src565 = (srcG == 0x07E0);
	if (!src565 && srcG != 0x03E0)
	{
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	const DWORD mRB = src565 ? 0xF81F : 0x7C1F;
	const DWORD mG  = src565 ? 0x07E0 : 0x03E0;

	int srcX = 0, srcY = 0;
	int sw = (int)sd.dwWidth;
	int sh = (int)sd.dwHeight;

	if (pSrcRect != NULL)
	{
		srcX = pSrcRect->left;
		srcY = pSrcRect->top;
		sw   = pSrcRect->right  - pSrcRect->left;
		sh   = pSrcRect->bottom - pSrcRect->top;

		// Refuse anything that is not wholly inside the surface.
		if (srcX < 0 || srcY < 0 || sw <= 1 || sh <= 1
			|| srcX + sw > (int)sd.dwWidth
			|| srcY + sh > (int)sd.dwHeight)
		{
			m_pDDSBack->Unlock(NULL);
			return false;
		}
	}

	// Only worth the work when magnifying. At 1:1 or smaller the plain Blt is
	// both faster and sharper, so hand it back.
	if (sw >= dw && sh >= dh)
	{
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	//-----------------------------------------------------------------------
	// Destination: our own offscreen surface, never the primary
	//-----------------------------------------------------------------------
	if (!EnsureScaleSurface(dw, dh))
	{
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	DDSURFACEDESC2 dd;
	::ZeroMemory(&dd, sizeof(dd));
	dd.dwSize = sizeof(dd);

	if (s_pScale->Lock(NULL, &dd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL) != DD_OK)
	{
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	// It was created to match, but a driver is free to hand back something
	// else. If it did, fall back rather than render garbage.
	if (dd.lpSurface == NULL
		|| dd.ddpfPixelFormat.dwRGBBitCount != 16
		|| dd.ddpfPixelFormat.dwGBitMask != srcG)
	{
		s_pScale->Unlock(NULL);
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	//-----------------------------------------------------------------------
	// Working buffers
	//-----------------------------------------------------------------------
	if (s_xCap < dw)
	{
		delete [] s_xi;
		delete [] s_xw;
		s_xi     = new int[dw];
		s_xw     = new int[dw];
		s_xCap   = dw;
		s_xForDW = -1;			// force a rebuild below
	}

	if (s_rowCap < dw)
	{
		delete [] s_rowA;
		delete [] s_rowB;
		s_rowA   = new WORD[dw];
		s_rowB   = new WORD[dw];
		s_rowCap = dw;
	}

	//-----------------------------------------------------------------------
	// 16.16 fixed point mapping, destination edges onto source edges
	//-----------------------------------------------------------------------
	const int xStep = ((sw - 1) << 16) / (dw - 1);
	const int yStep = ((sh - 1) << 16) / (dh - 1);

	// Column tables depend only on the two widths, so rebuild them only when
	// those change - not every frame.
	if (s_xForDW != dw || s_xForSW != sw)
	{
		int xacc = 0;
		for (int x = 0; x < dw; ++x)
		{
			int x0 = xacc >> 16;
			if (x0 > sw - 1) x0 = sw - 1;

			s_xi[x] = x0;
			s_xw[x] = (xacc >> 11) & 0x1F;		// 5 bit weight, 0..31
			xacc += xStep;
		}

		s_xForDW = dw;
		s_xForSW = sw;
	}

	const BYTE*	pSrcBase = (const BYTE*)sd.lpSurface;
	BYTE*		pDstBase = (BYTE*)dd.lpSurface;
	const int	srcPitch = (int)sd.lPitch;
	const int	dstPitch = (int)dd.lPitch;

	//-----------------------------------------------------------------------
	// Separable scale with a rolling two row cache
	//-----------------------------------------------------------------------
	int cached0 = -1;		// which source row s_rowA currently holds
	int cached1 = -1;		// ... and s_rowB
	int yacc    = 0;

	for (int y = 0; y < dh; ++y)
	{
		int y0 = yacc >> 16;
		if (y0 > sh - 1) y0 = sh - 1;

		const int   y1 = (y0 + 1 < sh) ? (y0 + 1) : y0;
		const DWORD wy = (DWORD)((yacc >> 11) & 0x1F);
		yacc += yStep;

		if (cached0 != y0 || cached1 != y1)
		{
			if (cached1 == y0 && y1 != y0)
			{
				// Advanced by exactly one row: what was the lower row is now
				// the upper one, so only the new lower row needs stretching.
				WORD* pSwap = s_rowA;
				s_rowA = s_rowB;
				s_rowB = pSwap;

				ScaleRowH(s_rowB,
					(const WORD*)(pSrcBase + (size_t)(srcY + y1) * srcPitch) + srcX,
					dw, sw, s_xi, s_xw, mRB, mG);
			}
			else
			{
				ScaleRowH(s_rowA,
					(const WORD*)(pSrcBase + (size_t)(srcY + y0) * srcPitch) + srcX,
					dw, sw, s_xi, s_xw, mRB, mG);

				if (y1 == y0)
					::memcpy(s_rowB, s_rowA, (size_t)dw * sizeof(WORD));
				else
					ScaleRowH(s_rowB,
						(const WORD*)(pSrcBase + (size_t)(srcY + y1) * srcPitch) + srcX,
						dw, sw, s_xi, s_xw, mRB, mG);
			}

			cached0 = y0;
			cached1 = y1;
		}

		BlendRowV((WORD*)(pDstBase + (size_t)y * dstPitch),
			s_rowA, s_rowB, dw, wy, mRB, mG);
	}

	s_pScale->Unlock(NULL);
	m_pDDSBack->Unlock(NULL);

	//-----------------------------------------------------------------------
	// Present. Same size both sides, so this is a straight copy for the
	// driver and we never touch the primary ourselves.
	//-----------------------------------------------------------------------
	HRESULT hr = m_pDDSPrimary->Blt(&m_rcScreen, s_pScale, NULL, DDBLT_WAIT, NULL);

	if (hr == DDERR_SURFACELOST)
	{
		RestoreAllSurfaces();
		return false;			// let the caller retry through the plain path
	}

	return SUCCEEDED(hr);
}
