// CD3D9Present.h
//
// GPU present layer for the software renderer.
//
// The game composites everything into a 16-bit system-memory DirectDraw
// surface at the logical resolution. This class uploads that surface into a
// Direct3D9 texture once per frame and draws it to the window with a
// "sharp-bilinear" scale: nearest-neighbour up to the smallest integer
// multiple that covers the destination, then a bilinear pass down to the
// final rect. That keeps pixel art crisp at non-integer ratios (the plain
// driver stretch shimmers, and plain bilinear goes soft) and costs the CPU
// nothing - the old software filter did the same job at a flat 5ms/frame.
//
// Present() returns false whenever it cannot (or should not) handle the
// frame - no D3D9, device lost, destination outside the client area - and
// the caller is expected to fall back to the original DirectDraw Blt.
// Presentation runs with vsync (D3DPRESENT_INTERVAL_ONE), which is also
// what paces the frame loop.

#ifndef __CD3D9PRESENT_H__
#define __CD3D9PRESENT_H__

#include <ddraw.h>

// Geometry of the most recent successful GPU present. Consumers (the FL2
// text overlay) size and scale against this; bActive false means the last
// frame went out through the DirectDraw fallback (or nothing presented yet).
struct D3D9PresentGeometry
{
	int  srcW, srcH;   // logical game surface size
	int  dstW, dstH;   // on-screen destination rect size
	bool bActive;
};

class CD3D9Present
{
public:
	// Upload pSrc (the 16-bit back surface) and present it into rcDstClient
	// (client coordinates of hWnd). prcSrc limits the source region; NULL
	// means the whole surface. Returns true if the frame reached the screen;
	// false means the caller must run the DirectDraw path instead.
	static bool Present(HWND hWnd, LPDIRECTDRAWSURFACE7 pSrc,
	                    const RECT* prcSrc, const RECT& rcDstClient);

	// Full teardown. Safe to call at any time; the next Present() lazily
	// rebuilds everything. Hooked into CDirectDraw::ReleaseSurface().
	static void Release();

	// Kill switch (Resolution.inf "D3DPresent: 0"). Disabled = permanent
	// DirectDraw fallback.
	static void SetEnabled(bool bEnable);

	// Filter choice (Resolution.inf "SmoothScale: 1"): true = plain bilinear
	// in one pass (softer, hides the pixel grid), false = sharp-bilinear
	// (crisper, keeps pixel-art definition). Takes effect on the next frame.
	static void SetSmoothScale(bool bSmooth);

	// Geometry of the last successful Present. Returns false (and bActive
	// false) when the presenter has not presented / fell back to DirectDraw.
	static bool GetPresentGeometry(D3D9PresentGeometry* pOut);

	// Native-resolution text overlay. pBits is a 32-bit 0x00RRGGBB buffer of
	// nW x nH (nPitchPx DWORDs per row); pixels equal to dwColorKey become
	// transparent. Only pRects regions are uploaded. The overlay is drawn 1:1
	// over the destination rect on the NEXT Present and expires after it -
	// callers re-submit every frame. nRects == 0 re-arms the existing texture
	// without uploading (for frames that present twice). Returns false when
	// the overlay cannot be shown this frame (no device, device lost).
	static bool UpdateOverlay(const unsigned long* pBits, int nW, int nH, int nPitchPx,
	                          const RECT* pRects, int nRects, unsigned long dwColorKey);

	// Global overlay opacity for the next Present (0 = invisible, 255 = full).
	// Used to fade crisp text in sync with full-screen fades (splash/CI).
	static void SetOverlayAlpha(int nAlpha255);
};

#endif // __CD3D9PRESENT_H__
