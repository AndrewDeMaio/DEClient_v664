//-----------------------------------------------------------------------------
// File: GetDXVer.cpp
//
// Desc: Demonstrates how applications can detect what version of DirectX
//       is installed.
//
//    (C) Copyright 1995-1997 Microsoft Corp.  All rights reserved.
//-----------------------------------------------------------------------------
#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <dinput.h>
#include <d3d.h>
#include <d3d9.h>
#include "dmusici.h"
#include <VersionHelpers.h>
#include "CDirectSetup.h"

typedef HRESULT(WINAPI* DIRECTDRAWCREATE)(GUID*, LPDIRECTDRAW*, IUnknown*);
typedef HRESULT(WINAPI* DIRECTDRAWCREATEEX)(GUID*, VOID**, REFIID, IUnknown*);
typedef HRESULT(WINAPI* DIRECTINPUTCREATE)(HINSTANCE, DWORD, LPDIRECTINPUT*,
	IUnknown*);



//-----------------------------------------------------------------------------
// Name: GetVersion()
// Desc: This function returns two arguments:
//          dwDXVersion:
//            0x0000 = No DirectX installed
//            0x0100 = DirectX version 1 installed
//            0x0200 = DirectX 2 installed
//            0x0300 = DirectX 3 installed
//            0x0500 = At least DirectX 5 installed.
//            0x0600 = At least DirectX 6 installed.
//            0x0601 = At least DirectX 6.1 installed.
//            0x0700 = At least DirectX 7 installed.
//          dwDXPlatform:
//            0                          = Unknown (This is a failure case)
//            VER_PLATFORM_WIN32_WINDOWS = Windows 9X platform
//            VER_PLATFORM_WIN32_NT      = Windows NT platform
// 
//          Please note that this code is intended as a general guideline. Your
//          app will probably be able to simply query for functionality (via
//          QueryInterface) for one or two components.
//
//          Please also note:
//            "if (dxVer != 0x500) return FALSE;" is BAD. 
//            "if (dxVer < 0x500) return FALSE;" is MUCH BETTER.
//          to ensure your app will run on future releases of DirectX.
//-----------------------------------------------------------------------------
VOID
CDirectSetup::GetVersion(DWORD* pdwDXVersion, DWORD* pdwDXPlatform)
{
	HRESULT              hr;
	HINSTANCE            DDHinst = 0;
	HINSTANCE            DIHinst = 0;
	LPDIRECTDRAW         pDDraw = 0;
	LPDIRECTDRAW2        pDDraw2 = 0;
	DIRECTDRAWCREATE     DirectDrawCreate = 0;
	DIRECTDRAWCREATEEX   DirectDrawCreateEx = 0;
	DIRECTINPUTCREATE    DirectInputCreate = 0;
	LPDIRECTDRAWSURFACE  pSurf = 0;
	LPDIRECTDRAWSURFACE3 pSurf3 = 0;
	LPDIRECTDRAWSURFACE4 pSurf4 = 0;

	if (!IsWindowsVistaOrGreater()) // Vista = NT 6.0
	{
		(*pdwDXPlatform) = 0;
		(*pdwDXVersion) = 0;
		return;
	}

	if (IsWindowsVistaOrGreater())
	{
		(*pdwDXPlatform) = VER_PLATFORM_WIN32_NT;
		(*pdwDXVersion) = 0x500;

		// --- DX6 / DX7 Detection ---
		LPDIRECTDRAW7 pDD7 = nullptr;
		HRESULT hr = DirectDrawCreateEx(nullptr, (void**)&pDD7, IID_IDirectDraw7, nullptr);
		if (SUCCEEDED(hr) && pDD7)
		{
			*pdwDXVersion = 0x600; // DX6 minimum
			LPDIRECT3D7 pD3D7 = nullptr;
			hr = pDD7->QueryInterface(IID_IDirect3D7, (void**)&pD3D7);
			if (SUCCEEDED(hr) && pD3D7)
			{
				*pdwDXVersion = 0x700; // DX7 detected
				pD3D7->Release();
			}
			pDD7->Release();
		}

#if DIRECT3D_VERSION >= 0x0800
		// --- DX8 detection ---
		IDirect3D8* pD3D8 = Direct3DCreate8(D3D_SDK_VERSION);
		if (pD3D8)
		{
			*pdwDXVersion = 0x800; // DX8 detected
			pD3D8->Release();
		}
#endif

#if DIRECT3D_VERSION >= 0x0900
		// --- DX9 detection ---
		IDirect3D9* pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
		if (pD3D9)
		{
			*pdwDXVersion = 0x900; // DX9 detected
			pD3D9->Release();
		}
#endif
	}
	else
	{
		(*pdwDXPlatform) = VER_PLATFORM_WIN32_WINDOWS;
	}

	// Now we know we are in Windows 9x (or maybe 3.1), so anything's possible.
	// First see if DDRAW.DLL even exists.
	DDHinst = LoadLibrary("DDRAW.DLL");
	if (DDHinst == 0)
	{
		(*pdwDXVersion) = 0;
		(*pdwDXPlatform) = 0;
		FreeLibrary(DDHinst);
		return;
	}

	// See if we can create the DirectDraw object.
	DirectDrawCreate = (DIRECTDRAWCREATE)GetProcAddress(DDHinst, "DirectDrawCreate");
	if (DirectDrawCreate == 0)
	{
		(*pdwDXVersion) = 0;
		(*pdwDXPlatform) = 0;
		FreeLibrary(DDHinst);
		OutputDebugString("Couldn't LoadLibrary DDraw\r\n");
		return;
	}

	hr = DirectDrawCreate(NULL, &pDDraw, NULL);
	if (FAILED(hr))
	{
		(*pdwDXVersion) = 0;
		(*pdwDXPlatform) = 0;
		FreeLibrary(DDHinst);
		OutputDebugString("Couldn't create DDraw\r\n");
		return;
	}

	// So DirectDraw exists.  We are at least DX1.
	(*pdwDXVersion) = 0x100;

	// Let's see if IID_IDirectDraw2 exists.
	hr = pDDraw->QueryInterface(IID_IDirectDraw2, (VOID**)&pDDraw2);
	if (FAILED(hr))
	{
		// No IDirectDraw2 exists... must be DX1
		pDDraw->Release();
		FreeLibrary(DDHinst);
		OutputDebugString("Couldn't QI DDraw2\r\n");
		return;
	}

	// IDirectDraw2 exists. We must be at least DX2
	pDDraw2->Release();
	(*pdwDXVersion) = 0x200;


	///////////////////////////////////////////////////////////////////////////
	// DirectX 3.0 Checks
	///////////////////////////////////////////////////////////////////////////

	// DirectInput was added for DX3
	DIHinst = LoadLibrary("DINPUT.DLL");
	if (DIHinst == 0)
	{
		// No DInput... must not be DX3
		OutputDebugString("Couldn't LoadLibrary DInput\r\n");
		pDDraw->Release();
		FreeLibrary(DDHinst);
		return;
	}

	DirectInputCreate = (DIRECTINPUTCREATE)GetProcAddress(DIHinst,
		"DirectInputCreateA");
	if (DirectInputCreate == 0)
	{
		// No DInput... must be DX2
		FreeLibrary(DIHinst);
		FreeLibrary(DDHinst);
		pDDraw->Release();
		OutputDebugString("Couldn't GetProcAddress DInputCreate\r\n");
		return;
	}

	// DirectInputCreate exists. We are at least DX3
	(*pdwDXVersion) = 0x300;
	FreeLibrary(DIHinst);

	// Can do checks for 3a vs 3b here


	///////////////////////////////////////////////////////////////////////////
	// DirectX 5.0 Checks
	///////////////////////////////////////////////////////////////////////////

	// We can tell if DX5 is present by checking for the existence of
	// IDirectDrawSurface3. First, we need a surface to QI off of.
	DDSURFACEDESC ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	hr = pDDraw->SetCooperativeLevel(NULL, DDSCL_NORMAL);
	if (FAILED(hr))
	{
		// Failure. This means DDraw isn't properly installed.
		pDDraw->Release();
		FreeLibrary(DDHinst);
		(*pdwDXVersion) = 0;
		OutputDebugString("Couldn't Set coop level\r\n");
		return;
	}

	hr = pDDraw->CreateSurface(&ddsd, &pSurf, NULL);
	if (FAILED(hr))
	{
		// Failure. This means DDraw isn't properly installed.
		pDDraw->Release();
		FreeLibrary(DDHinst);
		*pdwDXVersion = 0;
		OutputDebugString("Couldn't CreateSurface\r\n");
		return;
	}

	// Query for the IDirectDrawSurface3 interface
	if (FAILED(pSurf->QueryInterface(IID_IDirectDrawSurface3,
		(VOID**)&pSurf3)))
	{
		pDDraw->Release();
		FreeLibrary(DDHinst);
		return;
	}

	// QI for IDirectDrawSurface3 succeeded. We must be at least DX5
	(*pdwDXVersion) = 0x500;


	///////////////////////////////////////////////////////////////////////////
	// DirectX 6.0 Checks
	///////////////////////////////////////////////////////////////////////////

	// The IDirectDrawSurface4 interface was introduced with DX 6.0
	if (FAILED(pSurf->QueryInterface(IID_IDirectDrawSurface4,
		(VOID**)&pSurf4)))
	{
		pDDraw->Release();
		FreeLibrary(DDHinst);
		return;
	}

	// IDirectDrawSurface4 was create successfully. We must be at least DX6
	(*pdwDXVersion) = 0x600;
	pSurf->Release();
	pDDraw->Release();


	///////////////////////////////////////////////////////////////////////////
	// DirectX 6.1 Checks
	///////////////////////////////////////////////////////////////////////////

	// Check for DMusic, which was introduced with DX6.1
	LPDIRECTMUSIC pDMusic = NULL;
	CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_DirectMusic, NULL, CLSCTX_INPROC_SERVER,
		IID_IDirectMusic, (VOID**)&pDMusic);
	if (FAILED(hr))
	{
		OutputDebugString("Couldn't create CLSID_DirectMusic\r\n");
		FreeLibrary(DDHinst);
		return;
	}

	// DirectMusic was created successfully. We must be at least DX6.1
	(*pdwDXVersion) = 0x601;
	pDMusic->Release();
	CoUninitialize();


	///////////////////////////////////////////////////////////////////////////
	// DirectX 7.0 Checks
	///////////////////////////////////////////////////////////////////////////

	// Check for DirectX 7 by creating a DDraw7 object
	LPDIRECTDRAW7 pDD7;
	DirectDrawCreateEx = (DIRECTDRAWCREATEEX)GetProcAddress(DDHinst,
		"DirectDrawCreateEx");
	if (NULL == DirectDrawCreateEx)
	{
		FreeLibrary(DDHinst);
		return;
	}

	if (FAILED(DirectDrawCreateEx(NULL, (VOID**)&pDD7, IID_IDirectDraw7,
		NULL)))
	{
		FreeLibrary(DDHinst);
		return;
	}

	// DDraw7 was created successfully. We must be at least DX7.0
	(*pdwDXVersion) = 0x700;
	pDD7->Release();


	///////////////////////////////////////////////////////////////////////////
	// End of checks
	///////////////////////////////////////////////////////////////////////////

	// Close open libraries and return
	FreeLibrary(DDHinst);

	return;
}
