/*-----------------------------------------------------------------------------

	sora_monitor_def.h

	defines & const string

	2000.2.28. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __SORA_MONITOR_DEF_H__
#define __SORA_MONITOR_DEF_H__

const char * const MONITOR_VER =				"0.0.1";
char * const MONITOR_TITLE =					"Monitor"; // no const!

const char * const MONITOR_PROMPT =			"> ";

#define M_DEFAULT_X								5
#define M_DEFAULT_Y								5

#define M_LINE(x)									(M_DEFAULT_Y+18*x)

#define __M_PRINT(x, y, str, color)			PrintString(&update_surface, x, y, str, color);

#define _M_PRINT(y, str)						__M_PRINT(M_DEFAULT_X, y, str, 0)


#endif