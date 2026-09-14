// CD3D9Scaler.h
//
// Optional pixel-shader scaling for the GPU present layer (CD3D9Present).
//
// Mode 0 (default): not used - CD3D9Present keeps its fixed-function
//                   sharp-bilinear path exactly as before.
// Mode 1:           "sharp" pixel shader - each source texel is a solid
//                   block with a one-screen-pixel blend at the edges, at any
//                   scale ratio. Crisper than sharp-bilinear at 1.5x.
// Mode 2:           mode 1 followed by a contrast-adaptive sharpen pass
//                   (AMD CAS) at destination resolution. Strength 0..100.
//
// Only the game frame goes through these; the native-resolution text
// overlay is composited afterwards and is never filtered. Everything here
// is self-contained: shaders are embedded bytecode (shaders/ps_*.h, built
// by shaders/build_shaders.bat), resources live in this file, and Draw()
// returns false whenever it cannot run so the caller falls back to the
// legacy path. Removing this feature = "Scaler: 0" in Resolution.inf, or
// dropping the three hook lines in CD3D9Present.cpp.

#ifndef __CD3D9SCALER_H__
#define __CD3D9SCALER_H__

#include <windows.h>

struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct IDirect3DSurface9;

class CD3D9Scaler
{
public:
	// Selected mode (0/1/2) and sharpen strength 0..100 (mode 2 only).
	static void SetMode(int nMode, int nSharpen);
	static int  GetMode();

	// Draw the region (srcX,srcY,srcW,srcH) of pSrcTex (allocated nTexW x
	// nTexH) into rcDst on pBackBuffer with the selected mode. Returns false
	// if the device cannot run the shaders or a resource failed; nothing has
	// been drawn in that case and the caller should use its own path.
	// Leaves the device with no pixel shader bound and pBackBuffer as the
	// render target.
	static bool Draw(IDirect3DDevice9* pDevice, IDirect3DTexture9* pSrcTex, int nTexW, int nTexH,
	                 int srcX, int srcY, int srcW, int srcH, const RECT& rcDst,
	                 IDirect3DSurface9* pBackBuffer, bool bPow2Only, DWORD dwMaxTexW, DWORD dwMaxTexH);

	// Release DEFAULT-pool resources (device reset) / everything (device
	// release). Both safe to call at any time.
	static void ReleaseVolatile();
	static void ReleaseAll();
};

#endif // __CD3D9SCALER_H__
