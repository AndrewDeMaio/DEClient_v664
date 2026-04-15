/*-----------------------------------------------------------------------------

	dx_input.h

	Direct Input Class library.

	2000.3.2. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __DX_INPUT_H__
#define __DX_INPUT_H__

#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>

#define BUFFER_SIZE           32

/*-----------------------------------------------------------------------------
  Class Direct Input
-----------------------------------------------------------------------------*/
class CDirectInput
{
private:
	IDirectInput *          m_pDI;
	IDirectInputDevice *    m_pMouse;
	IDirectInputDevice *		m_pKeyboard;
	BOOL                    m_bSwapMouseButtons;
	int							m_mouse_info[3]; // Mouse 정보를 얻기 위한 integer array.

public:
	int							m_mouse_x;
	int							m_mouse_y;
	int							m_mouse_z; // wheel action
	bool							m_lb_down; // left button - down or up
	bool							m_rb_down; // right button - down or up
	bool							m_cb_down; // center button - down or up

	enum E_EXCLUSIVE // debugging 할 때를 위해서...
	{
		EXCLUSIVE,
		NONEXCLUSIVE,
	};

	enum E_MOUSE_EVENT // MOUSE_EVENT는 wincon.h에 정의 되어 있음! ~.~
	{
		MOVE = 0,
		LEFTDOWN,
		LEFTUP,
		RIGHTDOWN,
		RIGHTUP,
		CENTERDOWN,
		CENTERUP,
		WHEELDOWN,
		WHEELUP,
	};

	enum E_KEYBOARD_EVENT
	{
		KEYUP,
		KEYDOWN,
	};

private:
	enum
	{
		FIRST_THRESHOLD,
		SECOND_THRESHOLD,
		ACCEL_LEVEL,
	};

	int							m_limit_x; // mouse 이동 제한
	int							m_limit_y; // mouse 이동 제한

	HRESULT	InitDI(HWND hWnd, HINSTANCE hInst, E_EXCLUSIVE ex);
	void		FreeDirectInput();
	void		OnMouseInput();
	void		OnKeyboardInput();
	void		SetMouseSpeed();
	int		GetMouseAcceleration(int value);

	void		(*m_fp_mouse_event_receiver)(E_MOUSE_EVENT event, int x, int y, int z);
	void		(*m_fp_keyboard_event_receiver)(E_KEYBOARD_EVENT event, DWORD scan_code);

public:
	CDirectInput();
	~CDirectInput();

	void		Init(HWND hWnd, HINSTANCE hInst, E_EXCLUSIVE ex=EXCLUSIVE);
	HRESULT	SetAcquire(bool active_app);
	void		SetMouseEventReceiver(void (*fp_receiver)(E_MOUSE_EVENT, int, int, int));
	void		SetKeyboardEventReceiver(void (*fp_receiver)(E_KEYBOARD_EVENT, DWORD));
	void		SetMouseMoveLimit(int x, int y);
	void		UpdateInput();

	//int 		GetMouseInfo1() const { return m_mouse_info[0]; }
	//int 		GetMouseInfo2() const { return m_mouse_info[1]; }
	//int 		GetMouseInfo3() const { return m_mouse_info[2]; }
};

#endif
