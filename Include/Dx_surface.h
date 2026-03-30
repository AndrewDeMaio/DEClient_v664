/*-----------------------------------------------------------------------------

	dx_surface.h

	DirectX class library component.

	1999.12.28. KJTINC

-----------------------------------------------------------------------------*/

//----------------------------------------------------------------------
// CDirectDrawSurface.h
//----------------------------------------------------------------------
//
//
// 5:6:5 와  5:5:5의 차이는 
// Bit Mask에 의해 처리되는 부분에서 발생하는데
// CDirectDraw class의 InitMask()에서 Video Card에 맞는
// 적절한 Mask를 생성하므로 그냥~ CDirectDraw의 Mask를 사용하면 된다.
//
//
//
//----------------------------------------------------------------------
/*

  < DDSurface가 생성되는 MEMORY >

	- DDSCAPS_SYSTEMMEMORY는 Lock을 사용할 때 빠르다.
	- DDSCAPS_VIDEOMEMORY는 Blt를 사용할 때 빠르다.
	  단, VIDEOMEMORY가 부족하면 Surface를 생성하지 않으므로 error!
	- 지정을 안 해 주면 VIDEOMEMORY가 사용가능하면 사용하고 
   	  아니면 SYSTEMMEMORY를 사용한다.
	
  < Alpha Blending >
    - 사용하려면 DDSCAPS_SYSTEMMEMORY를 사용하는게 좋다.
	- Surface --> Surface로의 Alpha Blending보다
	  Memory(SpriteFile) --> Surface로의 Alpha Blending이 빠르다.

*/
//----------------------------------------------------------------------

#ifndef	__DX_SURFACE_H__
#define	__DX_SURFACE_H__

#include "dx_draw.h"


// gamma - -; not my code~~
#define GAMMA_MASK_1PIXEL1				00000000000000001111100000011111b
#define GAMMA_MASK_1PIXEL2				00000000000000000000011111100000b
#define GAMMA_MASK_2PIXEL1				11111000000111110000011111100000b
#define GAMMA_MASK_2PIXEL2				00000111111000001111100000011111b
#define GAMMA_MASK_4PIXEL_R			11111000000000001111100000000000b
#define GAMMA_MASK_4PIXEL_G			00000111111000000000011111100000b
#define GAMMA_MASK_4PIXEL_B			00000000000111110000000000011111b


/*-----------------------------------------------------------------------------
  Class DirectDraw Surface
-----------------------------------------------------------------------------*/
class CDirectDrawSurface : public CDirectDraw 
{
public :
	CDirectDrawSurface();
	~CDirectDrawSurface();

	// text out for debugging.
	void	GDI_Text(int x, int y, const char *str, COLORREF fcolor, 
																 COLORREF bcolor = 0, 
																 bool option = true);
	void	ShowFPS(int x, int y, COLORREF bcolor, COLORREF fcolor); // FPS를 출력한다.

	// Gamma
	void	Gamma2Pixel(void *pDest, int len, int p);
	void	Gamma4Pixel(void *pDest, int len, int p);
	void	GammaBox(RECT* pRect, int p);

	//------------------------------------------------------------
	// Init
	//------------------------------------------------------------
	bool	InitBacksurface();	
	bool	InitOffsurface(int wWidth, int wHeight, DWORD dwCaps = 0);	
	bool	InitFromBMP(LPCSTR szBitmap, DWORD dwCaps = 0);
	bool	InitTextureSurface(int wWidth, int wHeight, DWORD dwCaps = 0, LPDDPIXELFORMAT pDDPF = NULL);
	bool	InitTextureSurfaceFromBMP(LPCSTR szBitmap, DWORD dwCaps = 0);

	//------------------------------------------------------------
	// Load bitmap from File
	//------------------------------------------------------------
	bool	ReLoadBMP(LPCSTR szBitmap);		

	//------------------------------------------------------------
	// Restore Lost Surface
	//------------------------------------------------------------
	bool	Restore();

	//------------------------------------------------------------
	// Set Transparency color
	// `Blt할 때 반드시 해줘야 한다.
	//------------------------------------------------------------
	void	SetTransparency(DWORD dwValue);

	//------------------------------------------------------------
	// Blt
	//------------------------------------------------------------
	void	Blt(POINT* pPoint, CDirectDrawSurface* SourceSurface, RECT*  pRect);
	void	BltNoColorkey(POINT* pPoint, CDirectDrawSurface* SourceSurface, RECT*  pRect);

	//------------------------------------------------------------
	// DirectDraw 제공 Drawing 함수들...
	//------------------------------------------------------------
	void	FillSurface(WORD color);
	void	FillRect(RECT* rect, WORD Color);
		
	//------------------------------------------------------------
	// Get
	//------------------------------------------------------------
	inline void *	GetSurfacePointer() { return m_ddsd.lpSurface; }
	inline long		GetSurfacePitch() { return m_ddsd.lPitch; }
	inline LPDIRECTDRAWSURFACE7 &	GetSurface() { return m_pDDSurface; } const
	inline DDSURFACEDESC2 * GetDDSD() { return &m_ddsd; }
	inline int		GetWidth() const	{ return m_Width; } // no const...
	inline int		GetHeight() const	{ return m_Height; } // no const...

	//
	// ! Pitch와 Surface pointer를 얻으려면, CDirectDraw의 GetDDDesc()를 이용한다.
	//

	//------------------------------------------------------------
	// Lock / Unlock
	//------------------------------------------------------------		
	bool		Lock();
	bool		Unlock();
	bool		IsLock() const		{ return m_bLock; }

	// 음... 그냥 cast해서 쓰는게...
	void	LockW(WORD*& lpSurface, WORD& lPitch);
	//void	LockDW(DWORD*& lpSurface, WORD& lPitch);
	//void	LockQW(QWORD*& lpSurface, WORD& lPitch);
	
	// class 내부에서 쓰는 함수
protected :
	bool	CopyBitmap(HBITMAP hbm, int x, int y, int dx, int dy);

protected :
	LPDIRECTDRAWSURFACE7	m_pDDSurface;

	// Surface의 크기, 쓰임새가 많으므로 member로 가지고 있는다.
	int					m_Width;
	int					m_Height;

	// surface가 back surface인가를 나타내는 flag.
	bool					m_bBackSurface;

	// Lock이 된 상태인가?
	bool					m_bLock;
};

#endif

