// CD3D9Present.cpp
//
// See CD3D9Present.h for what this is and why it exists.

#include "CD3D9Present.h"

#include <d3d9.h>

//---------------------------------------------------------------------------
// State
//---------------------------------------------------------------------------

static bool                    s_bEnabled     = true;
static bool                    s_bSmoothScale = false;   // true = plain bilinear, no integer prescale
static IDirect3D9*             s_pD3D         = NULL;
static IDirect3DDevice9*       s_pDevice      = NULL;
static D3DPRESENT_PARAMETERS   s_pp;

// Source texture: the software frame is uploaded here every frame.
static IDirect3DTexture9*      s_pSrcTex      = NULL;
static D3DFORMAT               s_SrcTexFormat = D3DFMT_UNKNOWN;
static bool                    s_bSrcTexDynamic = false;   // DEFAULT pool + D3DLOCK_DISCARD
static int                     s_nTexW        = 0;         // allocated (pow2-rounded if required)
static int                     s_nTexH        = 0;

// Intermediate render target for the nearest-neighbour integer upscale.
static IDirect3DTexture9*      s_pScaleRT     = NULL;
static int                     s_nRTW         = 0;
static int                     s_nRTH         = 0;

// What the current resources were built for.
static HWND                    s_hWnd         = NULL;
static int                     s_nClientW     = 0;
static int                     s_nClientH     = 0;
static int                     s_nSrcW        = 0;
static int                     s_nSrcH        = 0;
static int                     s_nScale       = 0;         // integer prescale factor k

static bool                    s_bDeviceLost  = false;
static bool                    s_bPow2Only    = false;
static bool                    s_bDynamicTex  = false;
static DWORD                   s_dwMaxTexW    = 0;
static DWORD                   s_dwMaxTexH    = 0;

// Native-resolution text overlay: destination-sized ARGB texture composited
// 1:1 after the upscale. Re-armed every frame by UpdateOverlay; expires after
// one Present so a frame without text (or a DD-fallback frame) never shows a
// stale overlay.
static IDirect3DTexture9*      s_pOvTex       = NULL;
static int                     s_nOvTexW      = 0;         // allocated (pow2-rounded if required)
static int                     s_nOvTexH      = 0;
static int                     s_nOvW         = 0;         // logical (destination rect size)
static int                     s_nOvH         = 0;
static bool                    s_bOvFresh     = false;
static int                     s_nOvAlpha     = 255;       // global overlay opacity

// Geometry of the last successful Present, for GetPresentGeometry.
static int                     s_nLastSrcW    = 0;
static int                     s_nLastSrcH    = 0;
static int                     s_nLastDstW    = 0;
static int                     s_nLastDstH    = 0;
static bool                    s_bLastPresentOk = false;

// After this many consecutive hard failures (device creation / reset) the
// presenter turns itself off for the rest of the session so a machine with
// no usable GPU (RDP, VM) is not paying a per-frame retry.
static int                     s_nHardFails   = 0;
static const int               FAIL_LIMIT     = 8;

struct PRESENTVERTEX
{
	float x, y, z, rhw;
	float u, v;
};
#define PRESENTVERTEX_FVF (D3DFVF_XYZRHW | D3DFVF_TEX1)

//---------------------------------------------------------------------------
// Teardown helpers
//---------------------------------------------------------------------------

// DEFAULT-pool resources - everything that dies with a device reset.
static void s_ReleaseVolatile()
{
	if (s_pScaleRT) { s_pScaleRT->Release(); s_pScaleRT = NULL; }
	s_nRTW = s_nRTH = 0;

	// A MANAGED source texture would survive a reset, but releasing it too
	// keeps the resource logic to a single path.
	if (s_pSrcTex) { s_pSrcTex->Release(); s_pSrcTex = NULL; }
	s_SrcTexFormat = D3DFMT_UNKNOWN;
	s_nTexW = s_nTexH = 0;
	s_nSrcW = s_nSrcH = 0;
	s_nScale = 0;

	if (s_pOvTex) { s_pOvTex->Release(); s_pOvTex = NULL; }
	s_nOvTexW = s_nOvTexH = 0;
	s_nOvW = s_nOvH = 0;
	s_bOvFresh = false;
	s_bLastPresentOk = false;
}

static void s_ReleaseAll()
{
	s_ReleaseVolatile();
	if (s_pDevice) { s_pDevice->Release(); s_pDevice = NULL; }
	if (s_pD3D)    { s_pD3D->Release();    s_pD3D    = NULL; }
	s_hWnd = NULL;
	s_nClientW = s_nClientH = 0;
	s_bDeviceLost = false;
}

//---------------------------------------------------------------------------
// Device
//---------------------------------------------------------------------------

// Render states are lost on Reset, so both create and reset funnel through
// this.
static void s_ApplyStates()
{
	s_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	s_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	s_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	s_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	s_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	s_pDevice->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);
	s_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	s_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE);

	s_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	s_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	s_pDevice->SetFVF(PRESENTVERTEX_FVF);
}

static bool s_CreateDevice(HWND hWnd, int nClientW, int nClientH)
{
	s_ReleaseAll();

	s_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (s_pD3D == NULL)
	{
		// No runtime at all - never try again.
		s_bEnabled = false;
		return false;
	}

	ZeroMemory(&s_pp, sizeof(s_pp));
	s_pp.Windowed             = TRUE;             // pseudo-fullscreen is still a window
	s_pp.SwapEffect           = D3DSWAPEFFECT_DISCARD;
	s_pp.BackBufferWidth      = nClientW;
	s_pp.BackBufferHeight     = nClientH;
	s_pp.BackBufferFormat     = D3DFMT_UNKNOWN;   // = current display format
	s_pp.BackBufferCount      = 1;
	s_pp.hDeviceWindow        = hWnd;
	s_pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;   // vsync: this paces the frame loop

	// D3DCREATE_FPU_PRESERVE matters: without it D3D9 drops the x87 FPU to
	// single precision for the whole process, and this codebase does its
	// timing and game math in doubles.
	HRESULT hr = s_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
	                                  D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
	                                  &s_pp, &s_pDevice);
	if (FAILED(hr) || s_pDevice == NULL)
	{
		s_pDevice = NULL;
		s_pD3D->Release();
		s_pD3D = NULL;
		if (++s_nHardFails >= FAIL_LIMIT)
			s_bEnabled = false;
		return false;
	}

	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(caps));
	s_pDevice->GetDeviceCaps(&caps);
	s_bPow2Only  = (caps.TextureCaps & D3DPTEXTURECAPS_POW2) != 0 &&
	               (caps.TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL) == 0;
	s_bDynamicTex = (caps.Caps2 & D3DCAPS2_DYNAMICTEXTURES) != 0;
	s_dwMaxTexW  = caps.MaxTextureWidth;
	s_dwMaxTexH  = caps.MaxTextureHeight;

	s_ApplyStates();

	s_hWnd     = hWnd;
	s_nClientW = nClientW;
	s_nClientH = nClientH;
	s_nHardFails = 0;
	return true;
}

static int s_RoundUpPow2(int n)
{
	int p = 1;
	while (p < n)
		p <<= 1;
	return p;
}

//---------------------------------------------------------------------------
// Resources
//---------------------------------------------------------------------------

static bool s_EnsureResources(int nSrcW, int nSrcH, bool bSrc565, int nScale)
{
	// Clamp the prescale factor to what the hardware can hold as a render
	// target. Worst case k drops to 1 and the result is plain bilinear -
	// still correct, just softer.
	while (nScale > 1 &&
	       ((DWORD)(nSrcW * nScale) > s_dwMaxTexW || (DWORD)(nSrcH * nScale) > s_dwMaxTexH))
		nScale--;

	if (s_pSrcTex != NULL && s_pScaleRT != NULL &&
	    nSrcW == s_nSrcW && nSrcH == s_nSrcH && nScale == s_nScale)
		return true;

	s_ReleaseVolatile();

	// ---- Source texture -------------------------------------------------
	int texW = s_bPow2Only ? s_RoundUpPow2(nSrcW) : nSrcW;
	int texH = s_bPow2Only ? s_RoundUpPow2(nSrcH) : nSrcH;

	const DWORD   dwUsage = s_bDynamicTex ? D3DUSAGE_DYNAMIC : 0;
	const D3DPOOL pool    = s_bDynamicTex ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;

	// Prefer a texture in the surface's own 16-bit layout so the upload is a
	// straight row copy; fall back to X8R8G8B8 with expansion on the way in.
	const D3DFORMAT fmt16 = bSrc565 ? D3DFMT_R5G6B5 : D3DFMT_X1R5G5B5;

	if (SUCCEEDED(s_pDevice->CreateTexture(texW, texH, 1, dwUsage, fmt16, pool, &s_pSrcTex, NULL)))
	{
		s_SrcTexFormat = fmt16;
	}
	else if (SUCCEEDED(s_pDevice->CreateTexture(texW, texH, 1, dwUsage, D3DFMT_X8R8G8B8, pool, &s_pSrcTex, NULL)))
	{
		s_SrcTexFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		s_pSrcTex = NULL;
		return false;
	}

	s_bSrcTexDynamic = s_bDynamicTex;
	s_nTexW = texW;
	s_nTexH = texH;

	// ---- Intermediate render target (only needed when k > 1) ------------
	if (nScale > 1)
	{
		int rtW = nSrcW * nScale;
		int rtH = nSrcH * nScale;
		if (s_bPow2Only)
		{
			rtW = s_RoundUpPow2(rtW);
			rtH = s_RoundUpPow2(rtH);
		}

		if (FAILED(s_pDevice->CreateTexture(rtW, rtH, 1, D3DUSAGE_RENDERTARGET,
		                                    D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &s_pScaleRT, NULL)))
		{
			// No render target support - degrade to single-pass bilinear.
			s_pScaleRT = NULL;
			nScale = 1;
		}
		else
		{
			s_nRTW = rtW;
			s_nRTH = rtH;
		}
	}

	s_nSrcW  = nSrcW;
	s_nSrcH  = nSrcH;
	s_nScale = nScale;
	return true;
}

//---------------------------------------------------------------------------
// Upload: locked DirectDraw surface -> source texture
//---------------------------------------------------------------------------

static bool s_UploadSrc(LPDIRECTDRAWSURFACE7 pSrc, bool* pbSrc565, int* pnW, int* pnH)
{
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if (FAILED(pSrc->Lock(NULL, &ddsd, DDLOCK_READONLY | DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL)))
		return false;

	bool bOk = false;

	// Only the 16-bit layouts the game actually produces are handled.
	if (ddsd.ddpfPixelFormat.dwRGBBitCount == 16)
	{
		const bool bSrc565 = (ddsd.ddpfPixelFormat.dwGBitMask == 0x07E0u);
		const int  nW      = (int)ddsd.dwWidth;
		const int  nH      = (int)ddsd.dwHeight;

		*pbSrc565 = bSrc565;
		*pnW      = nW;
		*pnH      = nH;

		if (s_pSrcTex != NULL && nW == s_nSrcW && nH == s_nSrcH)
		{
			D3DLOCKED_RECT lr;
			const DWORD dwLockFlags = s_bSrcTexDynamic ? D3DLOCK_DISCARD : 0;

			if (SUCCEEDED(s_pSrcTex->LockRect(0, &lr, NULL, dwLockFlags)))
			{
				const BYTE* pSrcRow = (const BYTE*)ddsd.lpSurface;
				BYTE*       pDstRow = (BYTE*)lr.pBits;

				if (s_SrcTexFormat != D3DFMT_X8R8G8B8)
				{
					// Same 16-bit layout on both sides: straight row copy.
					const int nBytes = nW * 2;
					for (int y = 0; y < nH; y++)
					{
						memcpy(pDstRow, pSrcRow, nBytes);
						pSrcRow += ddsd.lPitch;
						pDstRow += lr.Pitch;
					}
				}
				else if (bSrc565)
				{
					// 565 -> X8R8G8B8, replicating high bits into low bits so
					// white stays white.
					for (int y = 0; y < nH; y++)
					{
						const WORD* s = (const WORD*)pSrcRow;
						DWORD*      d = (DWORD*)pDstRow;
						for (int x = 0; x < nW; x++)
						{
							const WORD p = s[x];
							const DWORD r = (p >> 11) & 0x1F;
							const DWORD g = (p >>  5) & 0x3F;
							const DWORD b =  p        & 0x1F;
							d[x] = ((r << 3 | r >> 2) << 16) |
							       ((g << 2 | g >> 4) <<  8) |
							        (b << 3 | b >> 2);
						}
						pSrcRow += ddsd.lPitch;
						pDstRow += lr.Pitch;
					}
				}
				else
				{
					// 555 -> X8R8G8B8
					for (int y = 0; y < nH; y++)
					{
						const WORD* s = (const WORD*)pSrcRow;
						DWORD*      d = (DWORD*)pDstRow;
						for (int x = 0; x < nW; x++)
						{
							const WORD p = s[x];
							const DWORD r = (p >> 10) & 0x1F;
							const DWORD g = (p >>  5) & 0x1F;
							const DWORD b =  p        & 0x1F;
							d[x] = ((r << 3 | r >> 2) << 16) |
							       ((g << 3 | g >> 2) <<  8) |
							        (b << 3 | b >> 2);
						}
						pSrcRow += ddsd.lPitch;
						pDstRow += lr.Pitch;
					}
				}

				s_pSrcTex->UnlockRect(0);
				bOk = true;
			}
		}
	}

	pSrc->Unlock(NULL);
	return bOk;
}

//---------------------------------------------------------------------------
// Draw one textured quad. Coordinates carry the classic D3D9 -0.5 texel
// offset; without it everything lands half a pixel off and the point-sampled
// pass blurs - which would defeat the entire exercise.
//---------------------------------------------------------------------------

static void s_DrawQuad(float x0, float y0, float x1, float y1,
                       float u0, float v0, float u1, float v1)
{
	PRESENTVERTEX v[4];

	v[0].x = x0 - 0.5f; v[0].y = y0 - 0.5f; v[0].u = u0; v[0].v = v0;
	v[1].x = x1 - 0.5f; v[1].y = y0 - 0.5f; v[1].u = u1; v[1].v = v0;
	v[2].x = x0 - 0.5f; v[2].y = y1 - 0.5f; v[2].u = u0; v[2].v = v1;
	v[3].x = x1 - 0.5f; v[3].y = y1 - 0.5f; v[3].u = u1; v[3].v = v1;

	for (int i = 0; i < 4; i++)
	{
		v[i].z   = 0.0f;
		v[i].rhw = 1.0f;
	}

	s_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(PRESENTVERTEX));
}

//---------------------------------------------------------------------------
// Overlay upload helper: convert one colorkeyed 0RGB rect into ARGB texels.
//---------------------------------------------------------------------------

static void s_OvConvertRect(const DWORD* pBits, int nPitchPx, const RECT& rc,
                            const D3DLOCKED_RECT& lr, DWORD dwColorKey)
{
	for (LONG y = rc.top; y < rc.bottom; y++)
	{
		const DWORD* src = pBits + (size_t)y * nPitchPx + rc.left;
		DWORD*       dst = (DWORD*)((BYTE*)lr.pBits + (size_t)(y - rc.top) * lr.Pitch);

		for (LONG x = 0; x < rc.right - rc.left; x++)
		{
			const DWORD p = src[x];
			dst[x] = (p == dwColorKey) ? 0u : (0xFF000000u | p);
		}
	}
}

//---------------------------------------------------------------------------
// Public API
//---------------------------------------------------------------------------

bool CD3D9Present::GetPresentGeometry(D3D9PresentGeometry* pOut)
{
	if (pOut == NULL)
		return false;

	pOut->srcW    = s_nLastSrcW;
	pOut->srcH    = s_nLastSrcH;
	pOut->dstW    = s_nLastDstW;
	pOut->dstH    = s_nLastDstH;
	pOut->bActive = s_bLastPresentOk;
	return s_bLastPresentOk;
}

bool CD3D9Present::UpdateOverlay(const unsigned long* pBits, int nW, int nH, int nPitchPx,
                                 const RECT* pRects, int nRects, unsigned long dwColorKey)
{
	if (!s_bEnabled || s_pDevice == NULL || s_bDeviceLost)
		return false;

	// Re-arm only: a frame that presents twice keeps its overlay visible.
	if (nRects == 0)
	{
		if (s_pOvTex != NULL && s_nOvW > 0)
		{
			s_bOvFresh = true;
			return true;
		}
		return false;
	}

	if (pBits == NULL || pRects == NULL || nW <= 0 || nH <= 0 || nPitchPx < nW)
		return false;

	bool bFullUpload = false;

	// (Re)create the texture when the destination size changes.
	if (s_pOvTex == NULL || nW != s_nOvW || nH != s_nOvH)
	{
		if (s_pOvTex) { s_pOvTex->Release(); s_pOvTex = NULL; }
		s_nOvW = s_nOvH = 0;
		s_bOvFresh = false;

		int texW = s_bPow2Only ? s_RoundUpPow2(nW) : nW;
		int texH = s_bPow2Only ? s_RoundUpPow2(nH) : nH;
		if ((DWORD)texW > s_dwMaxTexW || (DWORD)texH > s_dwMaxTexH)
			return false;

		// MANAGED, never DYNAMIC: the overlay takes many small sub-rect
		// locks per frame, and sub-rect locks on a DEFAULT-pool dynamic
		// texture (no DISCARD possible) synchronize with the GPU each time -
		// enough stalls to halve the frame rate. Managed locks are CPU-side
		// and the runtime uploads the dirtied regions at draw time.
		if (FAILED(s_pDevice->CreateTexture(texW, texH, 1, 0, D3DFMT_A8R8G8B8,
		                                    D3DPOOL_MANAGED, &s_pOvTex, NULL)))
		{
			s_pOvTex = NULL;
			return false;
		}

		s_nOvTexW = texW;
		s_nOvTexH = texH;
		s_nOvW    = nW;
		s_nOvH    = nH;

		// Fresh texture memory is undefined (pow2 padding included): clear it
		// all to transparent once, then upload the whole logical area.
		D3DLOCKED_RECT lrAll;
		if (SUCCEEDED(s_pOvTex->LockRect(0, &lrAll, NULL, 0)))
		{
			for (int y = 0; y < texH; y++)
				memset((BYTE*)lrAll.pBits + (size_t)y * lrAll.Pitch, 0, (size_t)texW * 4);
			s_pOvTex->UnlockRect(0);
		}
		bFullUpload = true;
	}

	if (bFullUpload)
	{
		RECT rcAll = { 0, 0, nW, nH };
		D3DLOCKED_RECT lr;
		if (SUCCEEDED(s_pOvTex->LockRect(0, &lr, &rcAll, 0)))
		{
			s_OvConvertRect((const DWORD*)pBits, nPitchPx, rcAll, lr, dwColorKey);
			s_pOvTex->UnlockRect(0);
		}
	}
	else
	{
		for (int i = 0; i < nRects; i++)
		{
			RECT rc = pRects[i];
			if (rc.left < 0)   rc.left = 0;
			if (rc.top < 0)    rc.top = 0;
			if (rc.right > nW)  rc.right = nW;
			if (rc.bottom > nH) rc.bottom = nH;
			if (rc.right <= rc.left || rc.bottom <= rc.top)
				continue;

			D3DLOCKED_RECT lr;
			if (SUCCEEDED(s_pOvTex->LockRect(0, &lr, &rc, 0)))
			{
				s_OvConvertRect((const DWORD*)pBits, nPitchPx, rc, lr, dwColorKey);
				s_pOvTex->UnlockRect(0);
			}
		}
	}

	s_bOvFresh = true;
	return true;
}

void CD3D9Present::SetSmoothScale(bool bSmooth)
{
	s_bSmoothScale = bSmooth;
}

void CD3D9Present::SetOverlayAlpha(int nAlpha255)
{
	if (nAlpha255 < 0)   nAlpha255 = 0;
	if (nAlpha255 > 255) nAlpha255 = 255;
	s_nOvAlpha = nAlpha255;
}

void CD3D9Present::SetEnabled(bool bEnable)
{
	s_bEnabled = bEnable;
	if (!bEnable)
		s_ReleaseAll();
}

void CD3D9Present::Release()
{
	s_ReleaseAll();
}

bool CD3D9Present::Present(HWND hWnd, LPDIRECTDRAWSURFACE7 pSrc,
                           const RECT* prcSrc, const RECT& rcDstClient)
{
	// Assume failure until the frame actually goes out; overlay consumers
	// read this via GetPresentGeometry and stand down on fallback frames.
	s_bLastPresentOk = false;

	if (!s_bEnabled || hWnd == NULL || pSrc == NULL)
		return false;

	RECT rcClient;
	if (!GetClientRect(hWnd, &rcClient))
		return false;

	const int nClientW = rcClient.right - rcClient.left;
	const int nClientH = rcClient.bottom - rcClient.top;
	if (nClientW <= 0 || nClientH <= 0)
		return false;

	const int nDstW = rcDstClient.right - rcDstClient.left;
	const int nDstH = rcDstClient.bottom - rcDstClient.top;
	if (nDstW <= 0 || nDstH <= 0)
		return false;

	// Destination outside the client area means the window and the surface
	// disagree about geometry (the startup progress window does this while
	// it is being resized). The DirectDraw clipper handles that case
	// correctly; this path does not pretend to.
	if (rcDstClient.left < 0 || rcDstClient.top < 0 ||
	    rcDstClient.right > nClientW || rcDstClient.bottom > nClientH)
		return false;

	// (Re)create the device when the window or its size changed.
	if (s_pDevice == NULL || hWnd != s_hWnd || nClientW != s_nClientW || nClientH != s_nClientH)
	{
		if (!s_CreateDevice(hWnd, nClientW, nClientH))
			return false;
	}

	// Recover from a lost device (alt-tab away during exclusive-mode apps,
	// workstation lock, driver restart). While it cannot be reset yet the
	// frame simply goes out through DirectDraw.
	if (s_bDeviceLost)
	{
		const HRESULT hrCoop = s_pDevice->TestCooperativeLevel();
		if (hrCoop == D3DERR_DEVICELOST)
			return false;
		if (hrCoop == D3DERR_DEVICENOTRESET || SUCCEEDED(hrCoop))
		{
			s_ReleaseVolatile();
			if (FAILED(s_pDevice->Reset(&s_pp)))
			{
				if (++s_nHardFails >= FAIL_LIMIT)
					s_bEnabled = false;
				return false;
			}
			s_ApplyStates();
			s_bDeviceLost = false;
			s_nHardFails = 0;
		}
	}

	// Source geometry. prcSrc (window mode hands in the viewport) is honoured
	// as a sub-rect of the uploaded texture; the upload itself always covers
	// the whole surface.
	bool bSrc565 = true;
	int  nSurfW  = 0;
	int  nSurfH  = 0;

	{
		DDSURFACEDESC2 ddsd;
		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		if (FAILED(pSrc->GetSurfaceDesc(&ddsd)) || ddsd.ddpfPixelFormat.dwRGBBitCount != 16)
			return false;
		bSrc565 = (ddsd.ddpfPixelFormat.dwGBitMask == 0x07E0u);
		nSurfW  = (int)ddsd.dwWidth;
		nSurfH  = (int)ddsd.dwHeight;
	}

	int nSrcX = 0, nSrcY = 0, nSrcW = nSurfW, nSrcH = nSurfH;
	if (prcSrc != NULL)
	{
		nSrcX = prcSrc->left;
		nSrcY = prcSrc->top;
		nSrcW = prcSrc->right - prcSrc->left;
		nSrcH = prcSrc->bottom - prcSrc->top;
		if (nSrcW <= 0 || nSrcH <= 0 ||
		    nSrcX < 0 || nSrcY < 0 || prcSrc->right > nSurfW || prcSrc->bottom > nSurfH)
			return false;
	}

	// Smallest integer prescale that covers the destination. Smooth mode
	// skips the prescale entirely and lets a single bilinear pass do the
	// whole job.
	int nScale = 1;
	if (!s_bSmoothScale)
	{
		while (nSrcW * nScale < nDstW || nSrcH * nScale < nDstH)
			nScale++;
	}

	if (!s_EnsureResources(nSurfW, nSurfH, bSrc565, nScale))
		return false;
	nScale = s_nScale;   // may have been clamped by texture-size caps

	if (!s_UploadSrc(pSrc, &bSrc565, &nSurfW, &nSurfH))
		return false;

	// An exact integer blow-up needs no second pass: point sampling alone is
	// already pixel-perfect (and identical to what the bilinear pass would
	// produce). Likewise 1:1 window mode.
	const bool bIntegerFit = (nDstW == nSrcW * nScale && nDstH == nSrcH * nScale);
	const bool bTwoPass    = (nScale > 1 && s_pScaleRT != NULL && !bIntegerFit);

	if (FAILED(s_pDevice->BeginScene()))
		return false;

	IDirect3DSurface9* pBackBuffer = NULL;
	s_pDevice->GetRenderTarget(0, &pBackBuffer);

	if (bTwoPass)
	{
		// Pass 1: nearest-neighbour integer upscale into the intermediate RT.
		IDirect3DSurface9* pRTSurf = NULL;
		if (SUCCEEDED(s_pScaleRT->GetSurfaceLevel(0, &pRTSurf)))
		{
			s_pDevice->SetRenderTarget(0, pRTSurf);
			// The RT can be pow2-padded beyond the used region; keep the
			// padding black so the edge texels of the bilinear pass never
			// blend against undefined memory.
			s_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
			s_pDevice->SetTexture(0, s_pSrcTex);
			s_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			s_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

			s_DrawQuad(0.0f, 0.0f,
			           (float)(nSrcW * nScale), (float)(nSrcH * nScale),
			           (float)nSrcX / s_nTexW,           (float)nSrcY / s_nTexH,
			           (float)(nSrcX + nSrcW) / s_nTexW, (float)(nSrcY + nSrcH) / s_nTexH);

			// Pass 2: bilinear from the RT down to the final rect.
			s_pDevice->SetRenderTarget(0, pBackBuffer);
			s_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
			s_pDevice->SetTexture(0, s_pScaleRT);
			s_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			s_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

			s_DrawQuad((float)rcDstClient.left,  (float)rcDstClient.top,
			           (float)rcDstClient.right, (float)rcDstClient.bottom,
			           0.0f, 0.0f,
			           (float)(nSrcW * nScale) / s_nRTW, (float)(nSrcH * nScale) / s_nRTH);

			pRTSurf->Release();
		}
	}
	else
	{
		// Single pass straight to the backbuffer. Integer fit (or 1:1) gets
		// point sampling; a clamped k==1 falls back to plain bilinear.
		s_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		s_pDevice->SetTexture(0, s_pSrcTex);

		const D3DTEXTUREFILTERTYPE filter = bIntegerFit ? D3DTEXF_POINT : D3DTEXF_LINEAR;
		s_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, filter);
		s_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, filter);

		s_DrawQuad((float)rcDstClient.left,  (float)rcDstClient.top,
		           (float)rcDstClient.right, (float)rcDstClient.bottom,
		           (float)nSrcX / s_nTexW,           (float)nSrcY / s_nTexH,
		           (float)(nSrcX + nSrcW) / s_nTexW, (float)(nSrcY + nSrcH) / s_nTexH);
	}

	// Native-resolution text overlay: 1:1 alpha-blended composite over the
	// scaled frame. Skipped when the overlay was built for a different
	// destination size (mid-resize frame).
	if (s_bOvFresh && s_pOvTex != NULL && s_nOvW == nDstW && s_nOvH == nDstH &&
	    s_nOvAlpha > 0)
	{
		s_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		s_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		s_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		s_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		if (s_nOvAlpha < 255)
		{
			// Modulate the whole overlay by the fade factor.
			s_pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, (DWORD)s_nOvAlpha << 24);
			s_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
			s_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
		}
		else
			s_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		s_pDevice->SetTexture(0, s_pOvTex);
		s_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		s_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

		s_DrawQuad((float)rcDstClient.left,  (float)rcDstClient.top,
		           (float)rcDstClient.right, (float)rcDstClient.bottom,
		           0.0f, 0.0f,
		           (float)s_nOvW / s_nOvTexW, (float)s_nOvH / s_nOvTexH);

		s_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		s_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	}

	s_pDevice->SetTexture(0, NULL);
	if (pBackBuffer)
		pBackBuffer->Release();

	s_pDevice->EndScene();

	// Record what this frame looked like for GetPresentGeometry, then expire
	// the overlay - it must be re-submitted every frame.
	s_nLastSrcW = nSrcW;
	s_nLastSrcH = nSrcH;
	s_nLastDstW = nDstW;
	s_nLastDstH = nDstH;
	s_bLastPresentOk = true;
	s_bOvFresh = false;

	const HRESULT hrPresent = s_pDevice->Present(NULL, NULL, NULL, NULL);
	if (hrPresent == D3DERR_DEVICELOST)
	{
		s_bDeviceLost = true;
		s_bLastPresentOk = false;
		return false;   // this frame still reaches the screen via DirectDraw
	}

	return SUCCEEDED(hrPresent);
}
