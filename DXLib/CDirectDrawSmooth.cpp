//---------------------------------------------------------------------------
// CDirectDrawSmooth.cpp
//---------------------------------------------------------------------------

#include "CDirectDraw.h"

// Default on. Flip() checks this before calling.
bool CDirectDraw::m_bSmoothScale = true;

//---------------------------------------------------------------------------
// BltSmoothStretch
//
// pSrcRect : region of the back buffer to present, or NULL for all of it.
//            Fullscreen passes NULL; window mode passes m_rcViewport, which
//            is what the original Blt used as its source rect.
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
	if (sw <= 1 || sh <= 1 || (sw >= dw && sh >= dh))
	{
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	//-----------------------------------------------------------------------
	// Destination
	//-----------------------------------------------------------------------
	DDSURFACEDESC2 dd;
	::ZeroMemory(&dd, sizeof(dd));
	dd.dwSize = sizeof(dd);
	if (m_pDDSPrimary->Lock(&m_rcScreen, &dd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL) != DD_OK)
	{
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	const DWORD dstBpp = dd.ddpfPixelFormat.dwRGBBitCount;
	const DWORD dstG   = dd.ddpfPixelFormat.dwGBitMask;
	const bool  dst565 = (dstG == 0x07E0);

	bool dstOK = false;
	if (dd.lpSurface != NULL)
	{
		if (dstBpp == 32)					dstOK = true;
		else if (dstBpp == 16 && dst565)	dstOK = true;
		else if (dstBpp == 16 && dstG == 0x03E0) dstOK = true;
	}
	if (!dstOK)
	{
		m_pDDSPrimary->Unlock(&m_rcScreen);
		m_pDDSBack->Unlock(NULL);
		return false;
	}

	const BYTE*	pSrc     = (const BYTE*)sd.lpSurface;
	BYTE*		pDst     = (BYTE*)dd.lpSurface;
	const int	srcPitch = (int)sd.lPitch;
	const int	dstPitch = (int)dd.lPitch;

	//-----------------------------------------------------------------------
	// 16.16 fixed point mapping, destination edges onto source edges.
	//-----------------------------------------------------------------------
	const int xStep = ((sw - 1) << 16) / (dw - 1);
	const int yStep = ((sh - 1) << 16) / (dh - 1);

	// Column index/weight pairs are the same for every row, so build them once
	// per frame. Kept between frames and grown only when the width grows.
	static int*	s_xi    = NULL;
	static int*	s_xw    = NULL;
	static int	s_xiCap = 0;
	if (s_xiCap < dw)
	{
		delete [] s_xi;
		delete [] s_xw;
		s_xi = new int[dw];
		s_xw = new int[dw];
		s_xiCap = dw;
	}

	{
		int xacc = 0;
		for (int x = 0; x < dw; x++)
		{
			int x0 = xacc >> 16;
			if (x0 > sw - 1) x0 = sw - 1;
			s_xi[x] = x0;
			s_xw[x] = (xacc >> 11) & 0x1F;		// 5 bit weight, 0..31
			xacc += xStep;
		}
	}

	const int srcShiftR = src565 ? 11 : 10;

	int yacc = 0;
	for (int y = 0; y < dh; y++)
	{
		int y0 = yacc >> 16;
		if (y0 > sh - 1) y0 = sh - 1;
		const int wy = (yacc >> 11) & 0x1F;
		yacc += yStep;

		const WORD* row0 = (const WORD*)(pSrc + (size_t)(srcY + y0) * srcPitch) + srcX;
		const WORD* row1 = (y0 + 1 < sh)
						 ? (const WORD*)(pSrc + (size_t)(srcY + y0 + 1) * srcPitch) + srcX
						 : row0;
		BYTE* outRow = pDst + (size_t)y * dstPitch;

		for (int x = 0; x < dw; x++)
		{
			const int x0 = s_xi[x];
			const int x1 = (x0 + 1 < sw) ? x0 + 1 : x0;
			const int wx = s_xw[x];

			const WORD a = row0[x0], b = row0[x1];
			const WORD c = row1[x0], e = row1[x1];

			// Unpack to 5/6/5. Each channel is handled on its own so a borrow
			// during interpolation can never run across a channel boundary.
			int ar = (a >> srcShiftR) & 0x1F, ag, ab = a & 0x1F;
			int br = (b >> srcShiftR) & 0x1F, bg, bb = b & 0x1F;
			int cr = (c >> srcShiftR) & 0x1F, cg, cb = c & 0x1F;
			int er = (e >> srcShiftR) & 0x1F, eg, eb = e & 0x1F;

			if (src565)
			{
				ag = (a >> 5) & 0x3F;
				bg = (b >> 5) & 0x3F;
				cg = (c >> 5) & 0x3F;
				eg = (e >> 5) & 0x3F;
			}
			else
			{
				// 555: promote the 5 bit green to 6 bits so the inner loop is
				// uniform. Replicating the top bit keeps full scale at full.
				const int a5 = (a >> 5) & 0x1F;
				const int b5 = (b >> 5) & 0x1F;
				const int c5 = (c >> 5) & 0x1F;
				const int e5 = (e >> 5) & 0x1F;
				ag = (a5 << 1) | (a5 >> 4);
				bg = (b5 << 1) | (b5 >> 4);
				cg = (c5 << 1) | (c5 >> 4);
				eg = (e5 << 1) | (e5 >> 4);
			}

			// Horizontal lerp on each row, then vertical between the two.
			const int tr = ar + (((br - ar) * wx) >> 5);
			const int tg = ag + (((bg - ag) * wx) >> 5);
			const int tb = ab + (((bb - ab) * wx) >> 5);

			const int ur = cr + (((er - cr) * wx) >> 5);
			const int ug = cg + (((eg - cg) * wx) >> 5);
			const int ub = cb + (((eb - cb) * wx) >> 5);

			const int fr = tr + (((ur - tr) * wy) >> 5);	// 5 bits
			const int fg = tg + (((ug - tg) * wy) >> 5);	// 6 bits
			const int fb = tb + (((ub - tb) * wy) >> 5);	// 5 bits

			if (dstBpp == 32)
			{
				// 5/6/5 -> 8/8/8. Replicating the high bits into the low ones
				// makes full scale land on 255 rather than 248/252.
				const DWORD r8 = (DWORD)((fr << 3) | (fr >> 2));
				const DWORD g8 = (DWORD)((fg << 2) | (fg >> 4));
				const DWORD b8 = (DWORD)((fb << 3) | (fb >> 2));
				((DWORD*)outRow)[x] = (r8 << 16) | (g8 << 8) | b8;
			}
			else if (dst565)
			{
				((WORD*)outRow)[x] = (WORD)((fr << 11) | (fg << 5) | fb);
			}
			else
			{
				// 555 destination: drop green back to 5 bits.
				((WORD*)outRow)[x] = (WORD)((fr << 10) | ((fg >> 1) << 5) | fb);
			}
		}
	}

	m_pDDSPrimary->Unlock(&m_rcScreen);
	m_pDDSBack->Unlock(NULL);
	return true;
}
