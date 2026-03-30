#ifndef __LIB_WRAPPER__
#define __LIB_WRAPPER__

#include "GL_import.h"
#include "PlatformService.h"

typedef enum
{
	BACKSCREEN, // ÈÄ¸é
//	BACKUPOFFSCREEN, // backup offscreen

} E_TARGET_SCREEN;

void InitilizeWrapper(E_TARGET_SCREEN e_target = BACKSCREEN);
//E_TARGET_SCREEN GetTargetScreen();
//extern void (*_Cls)(int);
extern void (*_FillRect)(S_RECT &, int);
//extern void (*_ClearScreen)(int);
extern void (*_PutPixel)(int, int, int);
extern int  (*_GetPixel)(int, int);
extern void (*_Rectangle)(int, int, int, int, int);
extern void (*_Line)(int, int, int, int, int);
extern void (*_Vertline)(int, int, int, int, int);
extern void (*_Horzline)(int, int, int, int, int);
extern void (*_PrintString)(int, int, char *, int);
extern void (*_Bltck)(int x, int y, RECT &);
extern int GetResolutionX();
extern int GetResolutionY();
extern void TerminateProgram();

#endif
