
#ifndef _NMCRYPTAPI_H_
#define _NMCRYPTAPI_H_

#ifdef _MAKE_DLL
	#define	CLIENTCORE_API	__declspec(dllexport)
#elif defined(_LIB)
	#define	CLIENTCORE_API
#else
	#define	CLIENTCORE_API	__declspec(dllimport)
#endif


CLIENTCORE_API bool CallWinMain() ; 

CLIENTCORE_API char*	GetServerIP() ; 
CLIENTCORE_API char*	GetLoginID() ; 
CLIENTCORE_API char*	GetLoginPW() ; 
CLIENTCORE_API UINT		GetWorldID(); 
CLIENTCORE_API UINT		GetServerID() ; 
CLIENTCORE_API UINT		GetPort();	

#endif 