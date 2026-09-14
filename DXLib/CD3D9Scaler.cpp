// CD3D9Scaler.cpp - see CD3D9Scaler.h

#include "CD3D9Scaler.h"

#include <d3d9.h>

#include "shaders/ps_sharp.h"
#include "shaders/ps_cas.h"

//---------------------------------------------------------------------------
// State
//---------------------------------------------------------------------------

static int                    s_nMode      = 0;
static int                    s_nSharpen   = 50;

static IDirect3DDevice9*      s_pDevice    = NULL;    // device the shaders were created on
static IDirect3DPixelShader9* s_pPSSharp   = NULL;
static IDirect3DPixelShader9* s_pPSCas     = NULL;
static bool                   s_bShaderFail = false;  // caps too low / creation failed: stay off

// Destination-sized intermediate for the sharpen pass.
static IDirect3DTexture9*     s_pRT        = NULL;
static int                    s_nRTW       = 0;       // allocated (pow2-rounded if required)
static int                    s_nRTH       = 0;
static int                    s_nRTUsedW   = 0;       // logical size the RT was made for
static int                    s_nRTUsedH   = 0;
static bool                   s_bRTFail    = false;

struct SCALERVERTEX
{
	float x, y, z, rhw;
	float u, v;
};
#define SCALERVERTEX_FVF (D3DFVF_XYZRHW | D3DFVF_TEX1)

//---------------------------------------------------------------------------

void CD3D9Scaler::SetMode(int nMode, int nSharpen)
{
	if (nMode < 0) nMode = 0;
	if (nMode > 2) nMode = 2;
	if (nSharpen < 0) nSharpen = 0;
	if (nSharpen > 100) nSharpen = 100;
	s_nMode    = nMode;
	s_nSharpen = nSharpen;
}

int CD3D9Scaler::GetMode()
{
	return s_nMode;
}

void CD3D9Scaler::ReleaseVolatile()
{
	if (s_pRT) { s_pRT->Release(); s_pRT = NULL; }
	s_nRTW = s_nRTH = 0;
	s_nRTUsedW = s_nRTUsedH = 0;
	s_bRTFail = false;
}

void CD3D9Scaler::ReleaseAll()
{
	ReleaseVolatile();
	if (s_pPSSharp) { s_pPSSharp->Release(); s_pPSSharp = NULL; }
	if (s_pPSCas)   { s_pPSCas->Release();   s_pPSCas   = NULL; }
	s_pDevice = NULL;
	s_bShaderFail = false;
}

//---------------------------------------------------------------------------

static int s_RoundUpPow2(int n)
{
	int p = 1;
	while (p < n)
		p <<= 1;
	return p;
}

static bool s_EnsureShaders(IDirect3DDevice9* pDevice)
{
	if (pDevice != s_pDevice)
	{
		CD3D9Scaler::ReleaseAll();
		s_pDevice = pDevice;
	}
	if (s_bShaderFail)
		return false;
	if (s_pPSSharp && s_pPSCas)
		return true;

	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(caps));
	if (FAILED(pDevice->GetDeviceCaps(&caps)) || caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
	{
		s_bShaderFail = true;
		return false;
	}
	if (FAILED(pDevice->CreatePixelShader((const DWORD*)g_psSharp, &s_pPSSharp)) ||
	    FAILED(pDevice->CreatePixelShader((const DWORD*)g_psCas, &s_pPSCas)))
	{
		if (s_pPSSharp) { s_pPSSharp->Release(); s_pPSSharp = NULL; }
		if (s_pPSCas)   { s_pPSCas->Release();   s_pPSCas   = NULL; }
		s_bShaderFail = true;
		return false;
	}
	return true;
}

static bool s_EnsureRT(IDirect3DDevice9* pDevice, int nW, int nH, bool bPow2Only, DWORD dwMaxTexW, DWORD dwMaxTexH)
{
	if (s_pRT && nW == s_nRTUsedW && nH == s_nRTUsedH)
		return true;
	if (s_bRTFail)
		return false;

	CD3D9Scaler::ReleaseVolatile();
	int rtW = bPow2Only ? s_RoundUpPow2(nW) : nW;
	int rtH = bPow2Only ? s_RoundUpPow2(nH) : nH;
	if ((DWORD)rtW > dwMaxTexW || (DWORD)rtH > dwMaxTexH ||
	    FAILED(pDevice->CreateTexture(rtW, rtH, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8,
	                                  D3DPOOL_DEFAULT, &s_pRT, NULL)))
	{
		s_pRT = NULL;
		s_bRTFail = true;
		return false;
	}
	s_nRTW = rtW;
	s_nRTH = rtH;
	s_nRTUsedW = nW;
	s_nRTUsedH = nH;
	return true;
}

static void s_DrawQuad(IDirect3DDevice9* pDevice, float x0, float y0, float x1, float y1,
                       float u0, float v0, float u1, float v1)
{
	SCALERVERTEX v[4];
	v[0].x = x0 - 0.5f; v[0].y = y0 - 0.5f; v[0].u = u0; v[0].v = v0;
	v[1].x = x1 - 0.5f; v[1].y = y0 - 0.5f; v[1].u = u1; v[1].v = v0;
	v[2].x = x0 - 0.5f; v[2].y = y1 - 0.5f; v[2].u = u0; v[2].v = v1;
	v[3].x = x1 - 0.5f; v[3].y = y1 - 0.5f; v[3].u = u1; v[3].v = v1;
	for (int i = 0; i < 4; i++)
	{
		v[i].z   = 0.0f;
		v[i].rhw = 1.0f;
	}
	pDevice->SetFVF(SCALERVERTEX_FVF);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(SCALERVERTEX));
}

//---------------------------------------------------------------------------

bool CD3D9Scaler::Draw(IDirect3DDevice9* pDevice, IDirect3DTexture9* pSrcTex, int nTexW, int nTexH,
                       int srcX, int srcY, int srcW, int srcH, const RECT& rcDst,
                       IDirect3DSurface9* pBackBuffer, bool bPow2Only, DWORD dwMaxTexW, DWORD dwMaxTexH)
{
	if (s_nMode == 0 || pDevice == NULL || pSrcTex == NULL || pBackBuffer == NULL)
		return false;
	if (srcW <= 0 || srcH <= 0 || nTexW <= 0 || nTexH <= 0)
		return false;
	const int nDstW = rcDst.right - rcDst.left;
	const int nDstH = rcDst.bottom - rcDst.top;
	if (nDstW <= 0 || nDstH <= 0)
		return false;
	if (!s_EnsureShaders(pDevice))
		return false;

	const bool bSharpen = (s_nMode >= 2) && s_EnsureRT(pDevice, nDstW, nDstH, bPow2Only, dwMaxTexW, dwMaxTexH);

	// ---- pass 1: sharp scale of the source into the RT (or straight out) ----
	IDirect3DSurface9* pRTSurf = NULL;
	if (bSharpen)
	{
		if (FAILED(s_pRT->GetSurfaceLevel(0, &pRTSurf)) || pRTSurf == NULL)
			return false;
		pDevice->SetRenderTarget(0, pRTSurf);
		pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	}
	else
	{
		pDevice->SetRenderTarget(0, pBackBuffer);
		pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	}

	float c0[4] = { (float)nTexW, (float)nTexH, 1.0f / nTexW, 1.0f / nTexH };
	float c1[4] = { (float)srcW / (float)nDstW, (float)srcH / (float)nDstH, s_nSharpen / 100.0f, 0.0f };
	pDevice->SetPixelShaderConstantF(0, c0, 1);
	pDevice->SetPixelShaderConstantF(1, c1, 1);
	pDevice->SetPixelShader(s_pPSSharp);
	pDevice->SetTexture(0, pSrcTex);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	if (bSharpen)
		s_DrawQuad(pDevice, 0.0f, 0.0f, (float)nDstW, (float)nDstH,
		           (float)srcX / nTexW, (float)srcY / nTexH,
		           (float)(srcX + srcW) / nTexW, (float)(srcY + srcH) / nTexH);
	else
		s_DrawQuad(pDevice, (float)rcDst.left, (float)rcDst.top, (float)rcDst.right, (float)rcDst.bottom,
		           (float)srcX / nTexW, (float)srcY / nTexH,
		           (float)(srcX + srcW) / nTexW, (float)(srcY + srcH) / nTexH);

	// ---- pass 2: sharpen 1:1 from the RT to the destination rect ----
	if (bSharpen)
	{
		pDevice->SetRenderTarget(0, pBackBuffer);
		pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		float r0[4] = { (float)s_nRTW, (float)s_nRTH, 1.0f / s_nRTW, 1.0f / s_nRTH };
		pDevice->SetPixelShaderConstantF(0, r0, 1);
		pDevice->SetPixelShader(s_pPSCas);
		pDevice->SetTexture(0, s_pRT);
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		s_DrawQuad(pDevice, (float)rcDst.left, (float)rcDst.top, (float)rcDst.right, (float)rcDst.bottom,
		           0.0f, 0.0f, (float)nDstW / s_nRTW, (float)nDstH / s_nRTH);
		pRTSurf->Release();
	}

	pDevice->SetPixelShader(NULL);
	pDevice->SetTexture(0, NULL);
	return true;
}
