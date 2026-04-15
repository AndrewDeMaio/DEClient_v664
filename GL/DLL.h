/*-----------------------------------------------------------------------------

	DLL.h

	Dynamic Link Library general header file.

	2000.8.8. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __DLL_H__
#define __DLL_H__

#define _CPP

#ifndef _CPP
#define _dllexport extern "C" __declspec (dllexport)
#define _dllimport extern "C" __declspec (dllimport)
#else
#define _dllexport __declspec (dllexport)
#define _dllimport __declspec (dllimport)
#endif

#define DllExport		_dllexport
#define DllImport		_dllimport

#ifdef _DLL_EXPORT
#define DllClass		DllExport
#else
#define DllClass		DllImport
#endif

#endif