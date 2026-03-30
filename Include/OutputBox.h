#ifndef __OUTPUTBOX__
#define __OUTPUTBOX__

#include "dialog_base.h"
#include "GL_import.h"

/*-----------------------------------------------------------------------------
  C_OUTPUTBOX
-----------------------------------------------------------------------------*/
class C_OUTPUTBOX : public C_DIALOG
{
private:
	bool					m_bl_image_lock;
   int               m_res_x, m_res_y; // resolution x, y
   int               m_bpp; // bit per pixel
   void *            m_p_buffer_mem;
	void *				m_p_lock_buffer;

   //
   // m_p_buffer_mem의 좌표 (source coordinates)
   // `(0 <= rx < m_res_x), (0 <= ry < m_res_y)
   //
   UINT              m_s_rx, m_s_ry;

	//
	// buffer에 쓰여질 data를 갱신하기 위한 fp.
	// `buffer에 쓰여질 data는 한 곳에 있다.
	//
	void (*m_fp_update_data)(void);
	int m_background_color;

	//
	// image file name
	// `출력된 image를 refresh해주기 위해 파일명을 기억한다.
	//
	//char *m_sz_file_name;

	//
	// App로 보내는 전용 Mouse control
	// `App의 입장에서는 어디서 Mouse control 메시지가 들어온지 모르므로 특별히 
	//  자신의 객체포인터를 인자로 해서 넘겨준다.
	//
	void (*m_fp_AppMouseControl)(UINT, int, int, C_OUTPUTBOX *);

public:
	void	GetLockImageSurfaceInfo(S_SURFACEINFO *surfaceinfo);
	void	GetImageSurfaceInfo(S_SURFACEINFO *surfaceinfo);
	bool	RefreshImage();
	bool	SetAppMouseControl(void (*AppMouseControl)(UINT, int, int, C_OUTPUTBOX *));
	int	GetBackgroundColor() const { return m_background_color; }
	void	ExecMethodToUpdate() const;
	bool	SetViewUpdateFpointer(void (*fp_view_update)(void));
	void	SetBackgroundColor(int color);
	void	SetSrcRy(UINT new_ry);
	void	SetSrcRx(UINT new_rx);
	UINT	Get_Y_AmountToScroll() const { return m_s_ry; }
	UINT	Get_X_AmountToScroll() const { return m_s_rx; }
	void	IncreaseSrcRy(int plus_y);
	void	IncreaseSrcRx(int plus_x);
	UINT	Get_X_AmountForScroll() const;
	UINT	Get_Y_AmountForScroll() const;
	void	ImageOut(int ix, int iy, char *filename, bool lock);
	void	TextOut(int ix, int iy, char *str, int color) const;
	void	SetSize();
	void	Show();
	void	MouseControl(UINT message, int x, int y);
	void	KeyboardControl(UINT message, UINT key);

   C_OUTPUTBOX(int resolution_x, int resolution_y, int bit_per_pixel);
   ~C_OUTPUTBOX();
};

#endif