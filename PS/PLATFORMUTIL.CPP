#include "PlatformUtil.h"


/*-----------------------------------------------------------------------------
- g_GetCtrlPushState
- control key 눌림 상태를 반환한다.
-----------------------------------------------------------------------------*/
bool g_GetCtrlPushState()
{
	//
	// control key가 눌려 있는지 검사하는데 아래의 
	// 함수를 쓴다. 반환값이 음수이면 눌려 있는 것이다.
	// control key가 눌려 있는지 아는 또 다른 방법은
	// WM_KEYUP을 검사하는 것이다.
	//
	if (GetKeyState(VK_CONTROL) < 0)
	{
		return true;
	}
	else
		return false;
}