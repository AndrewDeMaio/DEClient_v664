// NPGameStubs.cpp - Stub implementations for nProtect GameGuard SDK functions
// These are normally provided by the GameGuard vendor SDK (NPGameLib DLL).
// For dev builds without GameGuard, these stubs allow linking.

#include <windows.h>
#include <map>
#include <string>
#include "NPGameLib.h"

// g_nProtectMessage is declared extern in nProtect.h.
// Definition is now in Client.cpp, so we don't duplicate it here.

#ifdef __cplusplus
extern "C" {
#endif

DWORD __cdecl CheckNPGameMon()          { return NPGAMEMON_SUCCESS; }
BOOL  __cdecl CloseNPGameMon()          { return TRUE; }
DWORD __cdecl InitNPGameMon()           { return NPGAMEMON_SUCCESS; }
void  __cdecl SetHwndToGameMon(HWND)    {}
DWORD __cdecl PreInitNPGameMonA(LPCSTR) { return NPGAMEMON_SUCCESS; }
DWORD __cdecl PreInitNPGameMonW(LPCWSTR){ return NPGAMEMON_SUCCESS; }
BOOL  __cdecl SendUserIDToGameMonA(LPCSTR)  { return TRUE; }
BOOL  __cdecl SendUserIDToGameMonW(LPCWSTR) { return TRUE; }
BOOL  __cdecl SendCSAuthToGameMon(DWORD)    { return TRUE; }
BOOL  __cdecl SendCSAuth2ToGameMon(PGG_AUTH_DATA) { return TRUE; }
LPSTR __cdecl NPDect(LPSTR s)          { return s; }
BOOL  __cdecl NPGuardData(LPVOID, DWORD)   { return TRUE; }
BOOL  __cdecl NPReleaseData(LPVOID, DWORD) { return TRUE; }
LPCSTR __cdecl GetInfoFromGameMon()     { return ""; }
LPBYTE __cdecl GetHackInfoFromGameMon(DWORD* dwSize) { if (dwSize) *dwSize = 0; return NULL; }
BOOL  __cdecl ResourceAuthA(LPCSTR, bool)   { return TRUE; }
BOOL  __cdecl ResourceAuthW(LPCWSTR, bool)  { return TRUE; }
BOOL  __cdecl CheckD3DDevice(LPVOID, LPSTR) { return TRUE; }
DWORD __cdecl GGGetLastError()          { return 0; }

DWORD __cdecl InitPacketProtect(LPCSTR) { return 0; }
DWORD __cdecl EncryptPacket(LPVOID, DWORD dwLength)     { return dwLength; }
DWORD __cdecl DecryptPacket(LPVOID, DWORD dwLength)     { return dwLength; }
DWORD __cdecl EncryptPeerPacket(LPVOID, DWORD dwLength) { return dwLength; }
DWORD __cdecl DecryptPeerPacket(LPVOID, DWORD dwLength) { return dwLength; }
DWORD __cdecl PPGetLastError()          { return 0; }

BOOL  __cdecl FixVC80DEP()              { return TRUE; }
void  __cdecl SetCallbackToGameMon(NPGMCALLBACK) {}

DWORD __cdecl SetModulePathA(LPCSTR)    { return 0; }
DWORD __cdecl SetModulePathW(LPCWSTR)   { return 0; }

BOOL  __cdecl IsAdminPrivilege()        { return FALSE; }

#ifdef __cplusplus
}
#endif

// CNPDword manager stubs
BOOL  __cdecl RegisterToMgr(LPVOID)           { return FALSE; }
void  __cdecl RemoveFromMgr(LPVOID)           {}
DWORD __cdecl GetDataFromMgr(LPVOID)          { return 0; }
void  __cdecl SetDataToMgr(LPVOID, DWORD)     {}
