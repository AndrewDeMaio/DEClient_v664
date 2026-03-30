/*-----------------------------------------------------------------------------

	PlatformService.h

	UI는 UI가 실행될 수 있는 환경에 독립되어 있다. 곳 그것은 Platform Service를
	분리함으로써 가능해진다. 이것은 M$ Windows에서 UI가 돌아갈 수 있는 모든
	조건을 제공하는 것이다.

	이것의 재정의가 또다른 OS상에서 돌아갈 수 있는 길이길 바란다...

	2000.1.20. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __PLATFORMSERVICE_H__
#define __PLATFORMSERVICE_H__

#include <assert.h>
#include <windows.h>
#include "dx_lib.h"
#include "PS.h"

/*-----------------------------------------------------------------------------
  Public Function.
-----------------------------------------------------------------------------*/
bool ConvertKeyboardMessage(WPARAM wParam, UINT &message, UINT &key);

HWND InitWindowsBasicCode(HINSTANCE hinstance, 
									WNDPROC window_proc, // Window procedure
									UINT resolution_x,
									UINT resolution_y,
									int winmode, // WinMain()의 마지막 인자
									CDirectDraw::SCREENMODE screen_mode);

/*-----------------------------------------------------------------------------
  Extern.
-----------------------------------------------------------------------------*/
extern CDirectDrawSurface	gC_DDS_back;

#endif