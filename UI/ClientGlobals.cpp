/*-----------------------------------------------------------------------------

    ClientGlobals.cpp

    Definitions of global variables and stub functions originally from
    DECOMMISSIONED\Client.cpp that are referenced throughout the UI build.

-----------------------------------------------------------------------------*/

#include <windows.h>
#include <stdarg.h>
#include <string.h>
#include "MTypeDef.h"
#include "NPGameLib.h"
#include "Client.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

DWORD           g_dwVideoMemory         = 0;
BYTE            g_macAddress[6]         = { 0 };
BYTE            g_PayType               = 1;
char            g_FutecIP[20]           = { 0 };
unsigned int    g_FutecPort             = 0;
DWORD           g_nProtectErrorMessage  = 0;
DWORD           g_nProtectErrorMessage2 = 0;
DWORD           g_TimerNPMON            = 0;
bool            g_bForceExitBynProtect  = false;

BYTE            g_AdvanceVampireActionMaxCount[ACTION_ADVANCEMENT_MAX  - ACTION_ADVANCEMENT_STOP];
BYTE            g_AdvanceSlayerActionMaxCount [ACTION_ADVANCEMENT_SLAYER_MAX  - ACTION_ADVANCEMENT_SLAYER_STOP_SWORD];
BYTE            g_AdvanceOustersActionMaxCount[ACTION_ADVANCEMENT_OUSTERS_MAX - ACTION_ADVANCEMENT_OUSTERS_CHAKRAM_STOP];

CNPGameLib      npgl("DarkEden");

//-----------------------------------------------------------------------------
// InitFail
// Ported from DECOMMISSIONED\Client.cpp:344
//-----------------------------------------------------------------------------
HRESULT InitFail(LPCTSTR szError, ...)
{
    char    szBuff[1024];
    va_list vl;

    va_start(vl, szError);
    vsprintf(szBuff, szError, vl);
    va_end(vl);

    MessageBox(NULL, szBuff, "Error", MB_OK);
    return 0;
}

//-----------------------------------------------------------------------------
// GetPersnalShopUpdateTime
// Original reads interval from a RAR data file. Return safe default.
//-----------------------------------------------------------------------------
int GetPersnalShopUpdateTime()
{
    return 60000;
}

//-----------------------------------------------------------------------------
// PrecalculateAdvancementClassCreatureFrames
// Original (Client.cpp:424) populates the arrays from g_pTopView sprite sets.
// Zero-init here; runtime init completes the fill once g_pTopView is ready.
//-----------------------------------------------------------------------------
void PrecalculateAdvancementClassCreatureFrames()
{
    memset(g_AdvanceVampireActionMaxCount, 0, sizeof(g_AdvanceVampireActionMaxCount));
    memset(g_AdvanceSlayerActionMaxCount,  0, sizeof(g_AdvanceSlayerActionMaxCount));
    memset(g_AdvanceOustersActionMaxCount, 0, sizeof(g_AdvanceOustersActionMaxCount));
}
