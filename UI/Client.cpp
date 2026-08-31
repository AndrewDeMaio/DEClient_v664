#include "Client_PCH.h"
#include "ContentsFilter.h"
#if __CONTENTS(__XTRAP)
#pragma comment(lib, "XTrap4Client_mt")
#pragma comment(lib, "XTrap4Client_ClientPart_mt")
#pragma comment(lib, "XTrap_Unipher_mt")
#include "XTrap4Client.h"
#endif //__XTRAP
#define __NPROTECT__
//#define __NPROTECT_OLD_VERSION__



//-----------------------------------------------------------------------------
// Client.cpp
//-----------------------------------------------------------------------------


#pragma warning(disable:4786)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500 /* version 5.0 */
#endif /* !_WIN32_WINNT */

//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#endif

#include "DebugInfo.h"
// #ifndef _DEBUG
// #include "CrashReport.h"
// #endif

#if defined(OUTPUT_DEBUG) || defined(_DEBUG) || defined(__DEBUG_OUTPUT__)
#undef __NPROTECT__
#define NO_GAMEGUARD 
#endif

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <crtdbg.h>
#include <string>
#include <process.h>
#include <sys/stat.h>
#include <cerrno>
#include "Client.h"
#include "GameObject.h"
#include "VS_UI.h"
#include "MMusic.h"
#include "UIDialog.h"
#include "UpdateManager.h"
#include "MZLib.h"
#include <Commctrl.h>
#include "AppendPatchInfo.h"
#include "EffectSpriteTypeDef.h"
#include "MFileDef.h"
#include "Properties.h"
#include "ServerInfo.h"
#include "MTestDef.h"
#include "Resource.h"
#include "UserInformation.h"
#include "MFileDef.h"
#include "SoundSetting.h"
#include "OperatorOption.h"
#include "Resource.h"

#if !__CONTENTS(__INTERNATIONAL_UI)
#	define __USE_CRASH_REPORT
#endif

#ifdef __USE_CRASH_REPORT
#ifdef	__BUGTRAP
#include "CrashReport/CrashReport.h"
#endif //__BUGTRAP
#endif


#ifdef __NPROTECT__
#include "nProtect.h"
#endif

#if __CONTENTS(__CRYPT)
#include "Crypt.h"
#endif

#ifdef	_DEBUG
	//#include <vld.h>
#endif

//#define	UPDATER_FILENAME	"Updater.exe" 
#define DIRECTORY_UPDATE	"Update"

#ifndef OUTPUT_DEBUG
#define	USE_UPDATER
#endif

#if defined(OUTPUT_DEBUG) && defined(__METROTECH_TEST__)
//	#define	__WM_OUTPUT_DEBUG__
#endif

#ifdef OUTPUT_DEBUG
extern CRITICAL_SECTION		g_Lock;
#endif

#ifdef OUTPUT_DEBUG
//	int CLogFile = -1;
#endif
//-----------------------------------------------------------------------------
// Global
//-----------------------------------------------------------------------------

#ifdef __NPROTECT__
NPROTECT_STATUS g_nProtectSTATUS = NPROTECT_NORMAL;
#endif
HWND				g_hWnd;
HINSTANCE			g_hInstance;
int					g_x = 400;
int					g_y = 300;
//bool				g_bHALAvailable = false;
DWORD				g_dwVideoMemory = 0;

char				g_CWD[_MAX_PATH];

int					g_Dimension = 0;
DWORD				g_TimerNPMON = 0;

// FPS
DWORD				g_CurrentTime = 0;		// ?ð?
DWORD				g_CurrentFrame = 0;		// frame??

int					g_FrameCount = 0;
int					g_StartFrameCount = 0;
DWORD				g_StartTime = timeGetTime();
DWORD				g_EndTime = g_StartTime;
int					g_FrameRate = 0;
bool				g_bGoodFPS = true;

const int			g_FrameGood = 15;

//---------------------------------------------------------------------------
// Frame limiter
//---------------------------------------------------------------------------
// The client had no frame pacing of any kind. The main loop spins,
// CGameUpdate::UpdateDraw() runs on every iteration (the literal "|| 1" in
// its redraw test), and CDirectDraw::Flip() presents with a plain Blt to the
// primary surface - DDBLT_WAIT waits for the blitter, not for the vertical
// blank. Frames therefore landed at arbitrary phases against the desktop
// refresh, which reads as judder however high the average frame rate is.
//
// Pace to a fixed rate with QueryPerformanceCounter. timeGetTime cannot
// express 16.666ms, so a millisecond clock drifts roughly a frame every two
// seconds. Sleep covers the bulk of the wait and a short spin covers the
// tail, because Sleep still overshoots by about a millisecond even at 1ms
// timer resolution.
//---------------------------------------------------------------------------
const int			g_FrameLimitFPS = 60;		// target frame rate; 0 disables pacing
const double		g_FrameLimitSpinMs = 2.0;	// spin, rather than Sleep, for the last 2ms

static LARGE_INTEGER	s_FrameLimitFreq = { 0 };
static LONGLONG			s_FrameLimitNext = 0;

static void FrameLimiterInit()
{
	if (!QueryPerformanceFrequency(&s_FrameLimitFreq))
	{
		s_FrameLimitFreq.QuadPart = 0;	// no usable timer: pacing turns itself off
		return;
	}

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	s_FrameLimitNext = now.QuadPart;
}

static void FrameLimiterWait()
{
	if (g_FrameLimitFPS <= 0 || s_FrameLimitFreq.QuadPart == 0)
		return;

	const LONGLONG period = s_FrameLimitFreq.QuadPart / g_FrameLimitFPS;
	const LONGLONG spin   = (LONGLONG)(s_FrameLimitFreq.QuadPart * g_FrameLimitSpinMs / 1000.0);

	s_FrameLimitNext += period;

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	// More than a frame behind - a zone load, an alt-tab, a long stall. Drop
	// the backlog instead of running a burst of uncapped frames to catch up.
	if (now.QuadPart > s_FrameLimitNext + period)
	{
		s_FrameLimitNext = now.QuadPart;
		return;
	}

	for (;;)
	{
		QueryPerformanceCounter(&now);

		const LONGLONG remain = s_FrameLimitNext - now.QuadPart;
		if (remain <= 0)
			break;

		if (remain > spin)
		{
			const DWORD ms = (DWORD)((remain - spin) * 1000 / s_FrameLimitFreq.QuadPart);
			if (ms > 0)
			{
				Sleep(ms);
				continue;
			}
		}

		YieldProcessor();
	}
}

LONG				g_lGameRunBreakTime = 0;	//???? ?????? ???? ?? ??(????? ?? ??? Pause Break)
//2009.01.05 shootkj

// Application Time
DWORD				gGetApplcationRunTime(bool bReset)
{
	//DWORD static time = timeGetTime();
	DWORD dwCurrentTime = timeGetTime();
	if (bReset)
		g_gameStartTime = dwCurrentTime;
	return dwCurrentTime - g_gameStartTime;
}
DWORD				g_gameStartTime = timeGetTime();
#if __CONTENTS(__XTRAP)
DWORD WINAPI XTrap_Check_Alive(LPVOID temp)
{
	DWORD dwTime = 20000;
	while (1)
	{
		Sleep(20000);
		XTrap_C_CallbackAlive(dwTime);
	}
}
#endif //__XTRAP
// Execute Program --> bActiveApp
// minimize | anotherWnd click--> !ActiveGame
BOOL				g_bActiveApp = FALSE; // Is application active?
BOOL				g_bActiveGame = FALSE; // Is Game Active?
BOOL				g_bNeedUpdate = FALSE; // update??????

DWORD				g_double_click_time = 0;

bool				g_bTestMode = false;
//BOOL				g_WindowsNT = FALSE;
bool				g_bForceExitBynProtect = false;
bool				g_bForceExitBynProtect2 = false;
DWORD				g_nProtectErrorMessage = 0;
DWORD				g_nProtectErrorMessage2 = 0;
int					g_LeftPremiumDays = 0;
bool				g_bFamily = false;
BYTE				g_PayType = 1;
//bool				g_bSuperUser			= false;

//void SizeOfObjects();
//#define				__WEB_BROWSER__
//IWebBrowser2*			g_pWebBrowser = NULL; 
// [Futec????]
char g_FutecIP[20] = { 0, };
unsigned int g_FutecPort = 0;
BYTE g_AdvanceVampireActionMaxCount[ACTION_ADVANCEMENT_MAX - ACTION_ADVANCEMENT_STOP];
BYTE g_AdvanceSlayerActionMaxCount[ACTION_ADVANCEMENT_SLAYER_MAX - ACTION_ADVANCEMENT_SLAYER_STOP_SWORD];
BYTE g_AdvanceOustersActionMaxCount[ACTION_ADVANCEMENT_OUSTERS_MAX - ACTION_ADVANCEMENT_OUSTERS_CHAKRAM_STOP];

enum DARKEDEN_LANGUAGE
{
	DARKEDEN_KOREAN = 0,
	DARKEDEN_CHINESE,
	DARKEDEN_JAPANESE,
	DARKEDEN_ENGLISH,
	DARKEDEN_TAIWAN,

	DARKEDEN_LANGUAGE_MAX
};

struct NETMARBLE_INFO
{
	MString ID;
	MString Password;
	int WorldID;
	int ServerID;
	bool bGore;
};

// 2004, 7, 14, sobeit add start
struct REALSERVER_INFO
{
	REALSERVER_INFO() { bMode = false; WorldID = 0; }
	bool bMode;		// 0: ????????, 1:????????
	int WorldID;	// 0: ???, 1: ????
	MString ID;		// id
	MString Key;	// Key
};
// 2004, 7, 14, sobeit add end

BYTE g_macAddress[6];
extern bool CheckMacScreenMode();
extern BOOL GetMacAddressFromSock();
//-----------------------------------------------------------------------------
// define function
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// addFile?? ??? originalFile?? ???? ?????.
//-----------------------------------------------------------------------------			
#define WRITE_FROM_FILE(originalFile, patchFile)		\
		{												\
			char buffer[4096];							\
			int n;										\
														\
			while (1)									\
			{											\
				patchFile.read(buffer, 4096);			\
				n = patchFile.gcount();					\
														\
				if (n > 0)								\
				{										\
					originalFile.write(buffer, n);		\
				}										\
				else									\
				{										\
					break;								\
				}										\
			}											\
		}

//-----------------------------------------------------------------------
// Get Futec Address [Futec????]
//-----------------------------------------------------------------------
// DarkEden.exe Futec(IP:Port)
//              01234567890123
//-----------------------------------------------------------------------
bool
GetFutecAddress(const char* pStr)
{
	const char* pFutecStr = strstr(pStr, "Futec");
	const char* pLeftParen = strchr(pStr, '(');
	const char* pSeperator = strchr(pStr, ':');
	const char* pRightParen = strchr(pStr, ')');

	if (pFutecStr == NULL
		|| pLeftParen == NULL
		|| pSeperator == NULL
		|| pRightParen == NULL
		|| !(pFutecStr < pLeftParen
			&& pLeftParen < pSeperator
			&& pSeperator < pRightParen))
		return false;

	char str[20];

	strncpy(g_FutecIP, pLeftParen + 1, pSeperator - (pLeftParen + 1));
	strncpy(str, pSeperator + 1, pRightParen - (pSeperator + 1));
	g_FutecPort = atoi(str);

	return true;
}

bool ParsingNetmarble(const char* pCommandLine, NETMARBLE_INFO& info);
//bool ParsingRealServer(const char* pCommandLine,  int Dimention, REALSERVER_INFO &info);

bool
ParsingRealServer(const char* pCommandLine, int Dimention, REALSERVER_INFO& info)
{
	if (pCommandLine == NULL)
		return false;

	char szTemp[4096];
	if (strlen(pCommandLine) < 16)
		return false;

	const char* pString = strchr(pCommandLine, ' ');
	if (pString == NULL)
	{
		return false;
	}

	strcpy(szTemp, pString + 1);

	int argcnt = 0;
	char* token = NULL;
	//??? ??????? 32??????? ?ø??? NULL???? ?????? ?????? ????? +1 ?????.
	char arg2[4][32 + 1];
	argcnt = 0;

	token = strtok(szTemp, "|");
	if (NULL == token)
		return false;
	while (token && argcnt < 4)
	{
		strcpy(arg2[argcnt], token);
		argcnt++;
		token = strtok(NULL, "|");
		//	if(NULL == token)
		//		return false;
	}
	// mode|demention|ID|key
	info.bMode = atoi(arg2[0]) ? 1 : 0;
	info.WorldID = atoi(arg2[1]);
	info.ID = arg2[2];
	info.Key = arg2[3];

	return true;
}
//-----------------------------------------------------------------------------
// Name: InitFail()
// Desc: This function is called if an initialization function fails
//-----------------------------------------------------------------------------
HRESULT InitFail(LPCTSTR szError, ...)
{
	// ?????? ???..
	g_bActiveApp = FALSE;

	ShowCursor(TRUE);
	ShowWindow(g_hWnd, SW_HIDE);

	char		szBuff[1024];
	va_list		vl;

	va_start(vl, szError);
	vsprintf(szBuff, szError, vl);

	//ReleaseAllObjects();
	DEBUG_ADD(szBuff);

	MessageBox(g_hWnd, szBuff, PROGRAM_TITLE, MB_OK);
	DestroyWindow(g_hWnd);
	va_end(vl);

	return 0;
}

//-----------------------------------------------------------------------------
// ProgressBar
//-----------------------------------------------------------------------------
bool g_bUseProgressBar = true;
HWND g_hWndProgress = NULL;
const int progressBarWidth = 300;
const int progressBarHeight = 40;
const int g_numAppendFiles = 16;		// AppendPatch.inf?? file?? ????

std::map<DWORD, std::string> g_nProtectMessage;

void
RemoveProgressBar()
{
	if (g_hWndProgress != NULL)
	{
		DestroyWindow(g_hWndProgress);
		g_hWndProgress = NULL;
	}
}

// DE_FORCE_LANGUAGE
//
// Language normally comes from Language.inf inside Data\Info\infodata.rpk.
// That archive is left byte-for-byte original on purpose: it is a classic
// RAR the client reads with its own bundled unrar, and an archive rebuilt by
// modern WinRAR/7-Zip - even as -ma4 with matching Rar!\x1A\x07\x00 magic -
// fails to decode at runtime (SkinManager reports Open()==false, size 0).
//
// So the language is selected here instead. Comment the define out to go back
// to reading Language.inf from the archive.
//
// Note this also selects the socket encryption seed - see
// ClientPlayer::setEncryptCode and DE_ENGLISH_ENCRYPT_ALIGNED there.
#define DE_FORCE_LANGUAGE  DARKEDEN_ENGLISH

DARKEDEN_LANGUAGE CheckDarkEdenLanguage()
{
#ifdef DE_FORCE_LANGUAGE
	return DE_FORCE_LANGUAGE;
#else
	// Language ?????? DATA\INFO\Infodata.rpk ?? ??????.

	CRarFile rarfile;

	if (g_pFileDef == NULL)
		return DARKEDEN_KOREAN;

	rarfile.SetRAR(g_pFileDef->getProperty("FILE_INFO_DATA").c_str(), RPK_PASSWORD);
	rarfile.Open(g_pFileDef->getProperty("FILE_LANGUAGE_INFO").c_str());

	if (!rarfile.IsSet())
		return DARKEDEN_KOREAN;

	char szLine[512];
	int num = 0;

	while (rarfile.GetString(szLine, 512))
	{
		if (szLine[0] == ';' || strlen(szLine) <= 0)
			continue;

		if (strncmp(szLine, "LANGUAGE", 8) == 0)
		{
			sscanf(szLine + 8, "%d", &num);
			break;
		}
	}

	rarfile.Release();

	return (DARKEDEN_LANGUAGE)(DARKEDEN_KOREAN + num);
#endif	// DE_FORCE_LANGUAGE
}

bool DE_IsEnglish()
{
	return CheckDarkEdenLanguage() == DARKEDEN_ENGLISH;
}

void PrecalculateAdvancementClassCreatureFrames()
{
	memset(g_AdvanceVampireActionMaxCount, 0, sizeof(g_AdvanceVampireActionMaxCount));
	memset(g_AdvanceSlayerActionMaxCount, 0, sizeof(g_AdvanceSlayerActionMaxCount));
	memset(g_AdvanceOustersActionMaxCount, 0, sizeof(g_AdvanceOustersActionMaxCount));

	int i;


	for (i = ACTION_ADVANCEMENT_SLAYER_STOP_SWORD; i < ACTION_ADVANCEMENT_SLAYER_MAX; ++i)
	{
		int actionindex = i - ADVANCEMENT_ACTION_START;

		char part = 0;

		if (i == ACTION_ADVANCEMENT_SLAYER_BIKE_MOVE)
		{
			g_AdvanceSlayerActionMaxCount[actionindex] = 4;
			continue;
		}
		// ||
		//i == ACTION_ADVANCEMENT_SLAYER_BIKE_STOP )
		//part = AC_BIKE_1;


		g_AdvanceSlayerActionMaxCount[actionindex] =
			g_pTopView->m_AdvancementSlayerManFPK[part][actionindex][2].GetSize();
	}


	for (i = ACTION_ADVANCEMENT_STOP; i < ACTION_ADVANCEMENT_MAX; ++i)
	{
		int actionindex = i - ADVANCEMENT_ACTION_START;

		g_AdvanceVampireActionMaxCount[actionindex] =
			g_pTopView->m_AdvancementVampireManFPK[0][actionindex][2].GetSize();
	}

	for (i = ACTION_ADVANCEMENT_OUSTERS_CHAKRAM_STOP; i < ACTION_ADVANCEMENT_OUSTERS_MAX; ++i)
	{
		int actionindex = i - ADVANCEMENT_ACTION_START;

		g_AdvanceOustersActionMaxCount[actionindex] =
			g_pTopView->m_AdvancementOustersFPK[1][actionindex][2].GetSize();
	}
}

int	GetPersnalShopUpdateTime()
{
	CRarFile rarfile;

	rarfile.SetRAR(g_pFileDef->getProperty("FILE_INFO_DATA").c_str(), RPK_PASSWORD);
	rarfile.Open(g_pFileDef->getProperty("FILE_UPDATE_PERSNALSHOPTIME").c_str());

	if (!rarfile.IsSet())
		return 60000;

	char szLine[512];
	int num = 0;

	while (rarfile.GetString(szLine, 512))
	{
		if (strncmp(szLine, "UPDATETIME", 10) == 0)
		{
			sscanf(szLine + 10, "%d", &num);
			break;
		}
	}

	rarfile.Release();

	return num;
}

void CreateProgressBar(const char* str)
{
	if (g_bUseProgressBar)
	{
		RemoveProgressBar();

		InitCommonControls();

		int cyVScroll = GetSystemMetrics(SM_CYVSCROLL);
		g_hWndProgress = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS, str,
			WS_VISIBLE | PBS_SMOOTH,
			GetSystemMetrics(SM_CXSCREEN) / 2 - progressBarWidth / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - progressBarHeight / 2,
			progressBarWidth, progressBarHeight,
			NULL, (HMENU)0, g_hInstance, NULL);
	}
}

void SetProgressBarCount(int count)
{
	if (!g_bUseProgressBar || g_hWndProgress == NULL)
	{
		return;
	}

	SendMessage(g_hWndProgress, PBM_SETRANGE, 0, MAKELPARAM(0, count));
	SendMessage(g_hWndProgress, PBM_SETSTEP, (WPARAM)1, 0);
	SendMessage(g_hWndProgress, PBM_SETPOS, (WPARAM)0, 0);
}

void SetProgressBarText(const char* str)
{
	if (g_bUseProgressBar)
	{
		if (g_hWndProgress == NULL)
		{
			CreateProgressBar(str);
			SetProgressBarCount(g_numAppendFiles);
		}
		else
		{
			SetWindowText(g_hWndProgress, str);
		}
	}
}

void UpdateProgressBar()
{
	if (!g_bUseProgressBar || g_hWndProgress == NULL)
	{
		return;
	}

	SendMessage(g_hWndProgress, PBM_STEPIT, 0, 0);
}


//-----------------------------------------------------------------------------
// Patch Log Window
//-----------------------------------------------------------------------------
HWND		g_hPatchLogWnd = NULL;
HWND		g_hPatchLogEdit = NULL;
char* g_pPatchLogBuffer = NULL;	// ???? ??? ?????? global?? ???.

LRESULT FAR PASCAL PatchLogWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0L;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool ReadPatchLogFromFile()
{
	char strBuffer[256];

	const char* filename = "PatchLog.txt";

	if (_access(filename, 0))
	{
		return false;
	}

	std::ifstream file(filename);	// text file???.

	file.seekg(0, std::ios::end);
	long fpEnd = file.tellg();

	if (g_pPatchLogBuffer != NULL)
	{
		delete[] g_pPatchLogBuffer;
	}
	g_pPatchLogBuffer = new char[fpEnd * 2];

	file.seekg(0);

	char* pBuffer = g_pPatchLogBuffer;

	while (!file.eof())
	{
		file.getline(strBuffer, 254);
		int n = file.gcount();

		if (n == 0)
		{
			break;
		}

		if (strBuffer[n - 1] == '\0')
		{
			n -= 1;
		}

		// \r\n?? ?????? ???????? ???.		
		strBuffer[n] = '\r';
		strBuffer[n + 1] = '\n';

		strncpy(pBuffer, strBuffer, n + 2);
		pBuffer += n + 2;
	}
	*pBuffer = '\0';

	file.close();

	SetWindowText(g_hPatchLogEdit, g_pPatchLogBuffer);

	delete[] g_pPatchLogBuffer;
	g_pPatchLogBuffer = NULL;

	return true;
}

void OutPutClassSize()
{
	//#ifdef __DEBUG_OUTPUT__
	//	SizeOfObjects();
	//#endif
}

void ShowPatchLogWindow()
{
	/*	int width = 600;
		int height = 350;

		WNDCLASS               wc;

		wc.style			= CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc		= (WNDPROC)PatchLogWindowProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hInstance		= g_hInstance;
		wc.hIcon			= LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_DARKEDEN));
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH )GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName		= NULL;
		wc.lpszClassName	= "PatchLog";
		RegisterClass(&wc);

		DWORD style = WS_OVERLAPPEDWINDOW;
		style &= ~WS_MINIMIZEBOX;
		style &= ~WS_MAXIMIZEBOX;
		style &= ~WS_THICKFRAME;

		g_hPatchLogWnd = CreateWindow("PatchLog", "??????? ???????",
								style,
								GetSystemMetrics(SM_CXSCREEN)/2 - width/2,
								GetSystemMetrics(SM_CYSCREEN)/2 - height/2,
								width,	height,
								NULL, NULL, g_hInstance, NULL);

		if (!g_hPatchLogWnd)
		{
			return;
		}

		RECT rect;
		GetClientRect(g_hPatchLogWnd, &rect);
		g_hPatchLogEdit = CreateWindow(TEXT("edit"), NULL,
							   WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE  |

	ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_READONLY,
							   0,0,
							   rect.right-rect.left, rect.bottom-rect.top,
							   g_hPatchLogWnd, NULL, g_hInstance, NULL);

		if (!ReadPatchLogFromFile())
		{
			DestroyWindow( g_hPatchLogWnd );

			// ??? return??? main window?? ??´?. - -;
		}
		else
		{
			ShowWindow(g_hPatchLogWnd, SW_SHOW);
			UpdateWindow(g_hPatchLogWnd);
			SetFocus(g_hPatchLogWnd);
		}

		MSG		msg;
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (!GetMessage(&msg, NULL, 0, 0))
					break;
					//return msg.wParam;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				WaitMessage();
			}
		}
	*/
}

//-----------------------------------------------------------------------------
// Check DX Version
//-----------------------------------------------------------------------------
// DirectX Version?? check???.
//-----------------------------------------------------------------------------
/*
bool
CheckDXVersion()
{
	DWORD dwVer, dwPlatform;
	CDirectSetup::GetVersion( &dwVer, &dwPlatform );

	//------------------------------------------------------
	// Platform check
	//------------------------------------------------------
	//switch( dwPlatform )
	//{
	  //  case DXVER_PLATFORM_WINDOWS:
			//strcpy( strBuff, "OS:\tWindows 9x\n" );
		//    break;
		//case DXVER_PLATFORM_NT:
			//strcpy( strBuff, "OS:\tWindows NT\n" );
		  //  break;
		//default:
			//strcpy( strBuff, "Error!\n" );
		  //  break;
	//}


	//------------------------------------------------------
	// DirectX Version check
	//------------------------------------------------------
	// DX 7.0 ???
	if (dwVer==DXVER_DX_7)
	{
		return true;
	}

	//InitFail("You need to install DirectX 7.0 or later version...");

	// ?? ??????? ??? ????????..
	char directory[_MAX_PATH];

	// ???? ?????? ???
	GetCurrentDirectory( _MAX_PATH, directory );

	// ??????? ????? ?????.
	sprintf(directory, "%s\\%s", directory, PROGRAM_FILENAME);

	CDirectSetup::SetRestartProgram(directory);
	CDirectSetup::DirectXInstall(g_hWnd, g_hInstance, "DirectX7", true);

	// ???? ??? ???? ??? ??????? ??°???
	// rebooting ??????? ????????

	return true;
	//return false;
}
*/

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
LRESULT FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//MINMAXINFO      *pMinMax;

	switch (message)
	{
#ifdef __NPROTECT__
#ifdef __NPROTECT_OLD_VERSION__
	case WM_NPROTECT_SOFTICE:
		DEBUG_ADD("[nProtect] GameClose By nProtect (Window Message : WM_NPROTECT_SOFTICE)");
		//		SetMode( MODE_QUIT );
		g_nProtectSTATUS = NPROTECT_SOFTICE;
		break;

	case WM_NPROTECT_EXIT_TWO:
		DEBUG_ADD("[nProtect] GameClose By nProtect (Window Message : WM_NPROTECT_EXIT_TWO)");
		//		SetMode( MODE_QUIT );
		g_nProtectSTATUS = NPROTECT_EXIT_TWO;
		break;
	case WM_NPROTECT_FORCEEXIT:
		DEBUG_ADD("[nProtect] GameClose By nProtect (Window Message : WM_NPROTECT_FORCEEXIT)");
		//		SetMode( MODE_QUIT );
		g_nProtectSTATUS = NPROTECT_FORCE_EXIT;
		break;
	case WM_NPROTECT_SH_ERROR:
		DEBUG_ADD("[nProtect] GameClose By nProtect (Window Message : WM_NPROTECT_SH_ERROR)");
		g_nProtectSTATUS = NPROTECT_SH_ERROR;
		break;
	case WM_NPROTECT_SPEEDHACK:
		g_nProtectSTATUS = NPROTECT_SPEEDHACK;
		break;
#endif
#endif
		// zzi	-  20071010 ?????? ???? ????.
		//			IME ??? ??? ??????? ????~~~ ??????.. NONCONVERSION ????????.
		//		??????? ?????? WM_IME_NOTIFY ó?? case???? ??????? ó????? ???????, ?????? ??????. 
#if !__CONTENTS (__LANGUAGE_CHANGE)
	case WM_IME_NOTIFY:
	{
		if ((DWORD)wParam == IMN_SETCONVERSIONMODE)
		{
			HIMC hImc = ImmGetContext(hWnd);
			if (hImc)
			{
				// Get current IME status
				DWORD dwConvMode, dwSentMode;
				ImmGetConversionStatus(hImc, &dwConvMode, &dwSentMode);
				// notify ime mode change
				bool nativeMode = ((dwConvMode & IME_CMODE_NATIVE) != 0);

				//					if( nativeMode )
				//						dwConvMode |= IME_CMODE_NATIVE;
				//					else
				//						dwConvMode &= ~IME_CMODE_NATIVE;

				dwConvMode = IME_CMODE_NOCONVERSION;

				ImmSetConversionStatus(hImc, dwConvMode, dwSentMode);
				// Release input context
				ImmReleaseContext(hWnd, hImc);
			}
		}
	}
	return 0;
#endif
	//---------------------------------------------------------------
	//
	//						MM_MCINOTIFY
	//
	//---------------------------------------------------------------
	case MM_MCINOTIFY:
	{
		// Mid?? ?? ????????? ?????.
		if (wParam == MCI_NOTIFY_SUCCESSFUL)
		{
			// Opening ???????? ???? ???
			if (g_pAvi != NULL && (DWORD)lParam == g_pAvi->dwID)
			{
				g_pAvi->bEndFlag = true;
				g_pAvi->Close();

				// Login ???????...
				SetMode(MODE_MAINMENU);
			}
			// ???? ????? ???? ???
			else
			{
				/*
				// ??? ???? ?????.
				if (g_pUserOption->PlayMusic)//g_Music.IsPause())	// ???? ??????.. - -;
				{
					if (g_pUserOption->PlayWaveMusic)
					{
						g_pDXSoundStream->Play( FALSE );
					}
					else
					{
						g_Music.RePlay();
					}
				}
				*/
				//else
				//{
					// ?????? ???????.
				//	g_Music.RePlay();
				//}
//					if(g_pMP3->IsLoop())
//						g_pMP3->Play(true);
			}
		}
	}
	return 0L;

	//---------------------------------------------------------------
	//
	//	WM_SYSCOMMAND
	// 
	//---------------------------------------------------------------
	case WM_SYSCOMMAND:
		// Prevent moving/sizing and power loss in fullscreen mode
		switch (wParam)
		{
		case SC_HOTKEY:
		case SC_KEYMENU:
		case SC_TASKLIST:
#if !defined(OUTPUT_DEBUG) && !defined(__DEBUG_OUTPUT__)
		case SC_PREVWINDOW:
		case SC_NEXTWINDOW:
#endif
			return 1;

		case SC_CLOSE:
		case SC_MOVE:
		case SC_SIZE:
		case SC_MAXIMIZE:
		case SC_MONITORPOWER:
		case SC_SCREENSAVE:
			if (CDirectDraw::IsFullscreen())
				return 1;
			break;
		}
		break;//return 0L;


		//---------------------------------------------------------------
		//
		//							WM_ACTIVATE
		//
		//---------------------------------------------------------------
		/*
		case WM_ACTIVATE :
		{
			#ifdef __WM_OUTPUT_DEBUG__
					DEBUG_ADD("[WM_ACTIVATE]");
			#endif

					/*
			//WORD fActive = LOWORD(wParam);           // activation flag
			//BOOL fMinimized = (BOOL) HIWORD(wParam); // minimized flag

			// active??? minimized?? ??? ???°? ActiveGame???..
			//BOOL bActive = (fActive==WA_ACTIVE) || (fActive==WA_CLICKACTIVE);
			//				//&& !fMinimized;

			//g_double_click_time = GetDoubleClickTime();

			//if (g_bActiveApp)
			{
			//	CheckActivate(bActive);

			//	g_bActiveGame = bActive;
			}

			BOOL bActive = (wParam == WA_ACTIVE) || (wParam == WA_CLICKACTIVE);

			if (g_pDXInput!=NULL)
			{
				// acquire
				g_pDXInput->SetAcquire(bActive);

				// ????? ???????.
				g_pDXInput->Clear();
			}
		}
		break;//return 0L;
		*/

		//---------------------------------------------------------------
		//
		//							WM_ACTIVATEAPP
		//
		//---------------------------------------------------------------
		///*
//		case WM_ACTIVATE :
	case WM_ACTIVATEAPP:
	{
#ifdef __WM_OUTPUT_DEBUG__
		DEBUG_ADD("[WM_ACTIVATEAPP]");
#endif

		// Pause if minimized or not the top window
		//WORD fActive = LOWORD(wParam);
		//WORD fMinimized = (BOOL) HIWORD(wParam); 
		//g_bActiveGame = (fActive == WA_ACTIVE) || (fActive == WA_CLICKACTIVE);

		g_double_click_time = GetDoubleClickTime();

		BOOL bActiveGame = (BOOL)wParam;

		//if (g_bActiveApp)
		{
			CheckActivate(bActiveGame);
			// 
			g_bActiveGame = bActiveGame;
		}

		gC_vs_ui.CloseGameMenu();
	}
	break;//return 0L;
	//*/

	/*
	case WM_SIZE :
	{
		BOOL bActive;

		// Check to see if we are losing our window...
		if( SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam )
			bActive = FALSE;
		else
			bActive = TRUE;

		g_double_click_time = GetDoubleClickTime();

		if (g_bActiveApp)
		{
			CheckActivate(bActive);

			g_bActiveGame = bActive;
		}
	}
	break;
	*/

	//---------------------------------------------------------------
	//
	//							WM_SIZE
	//
	//---------------------------------------------------------------
	//case WM_SIZE:
		// Check to see if we are losing our window...
		//if (SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam)
		  //  g_bActiveGame = FALSE;
		//else
		  //  g_bActiveGame = TRUE;
	//return 0L;

	//---------------------------------------------------------------
	//
	//							WM_DESTROY
	//
	//---------------------------------------------------------------
	case WM_DESTROY:
		// Clean up and close the app            
		PostQuitMessage(0);
		return 0L;

	case WM_GETMINMAXINFO:
	{
		// Fix the size of the window to 640x480 (client size)
		MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;

		pMinMax->ptMinTrackSize.x = SURFACE_WIDTH + GetSystemMetrics(SM_CXSIZEFRAME) * 2;
		pMinMax->ptMinTrackSize.y = SURFACE_HEIGHT + GetSystemMetrics(SM_CYSIZEFRAME) * 2
			+ GetSystemMetrics(SM_CYMENU);

		pMinMax->ptMaxTrackSize.x = pMinMax->ptMinTrackSize.x;
		pMinMax->ptMaxTrackSize.y = pMinMax->ptMinTrackSize.y;
	}
	break;

	/*
	case WM_PAINT:
		if (g_bActiveApp)
			CDirectDraw::OnPaint();
		return 0L;
	*/

	//---------------------------------------------------------------
	//
	//							WM_MOVE
	//
	//---------------------------------------------------------------
	case WM_MOVE:
		if (g_bActiveApp && !CDirectDraw::IsFullscreen())
			CDirectDraw::OnMove();
		break;

		/*
		case WM_MOUSEMOVE :
			//fwKeys = wParam;        // key flags
			//g_x = LOWORD(lParam);  // horizontal position of cursor
			//g_y = HIWORD(lParam);  // vertical position of cursor

			return 0L;
		*/

		//---------------------------------------------------------------
		//
		//							WM_KEYDOWN
		//
		//---------------------------------------------------------------
	case WM_KEYDOWN:
#ifdef __WM_OUTPUT_DEBUG__
		DEBUG_ADD("[WM_KEYDOWN]");
#endif

		if (g_Mode == MODE_OPENING)
		{
			// Opening?? ??????.
			if (wParam == VK_ESCAPE || wParam == VK_RETURN || wParam == VK_SPACE)
			{
				if (g_pAvi != NULL)
				{
					g_pAvi->Close();
				}
				SetMode(MODE_MAINMENU);
			}
			return 0L;
		}

		gC_vs_ui.KeyboardControl(message, wParam, lParam);
		// Handle any non-accelerated key commands

		switch (wParam)
		{
			//-----------------------------------------------
			// Screen Shot
			//-----------------------------------------------
		case VK_SCROLL:

			if (!g_pOperatorOption->bSlideScreenShot)
			{
				MakeScreenShot();
			}

			// 					#ifdef OUTPUT_DEBUG
			// 						if (!g_pOperatorOption->bSlideScreenShot)
			// 						{
			// 							MakeScreenShot();
			// 						}
			// 					#else
			// 						MakeScreenShot();
			// 					#endif

			return 0L;
			//case VK_F11 : 
			//		g_UpdateDelay = (g_UpdateDelay==1)? DELAY_UPDATE_GAME : 1;
			//		return 0L;

			//-----------------------------------------------
			// Toggle Music
			//-----------------------------------------------
			/*
			case VK_F3 :
				//if (g_Music.IsPlay())
				if (g_DXMusic.IsPlay())
				{
					//g_Music.Pause();
					g_DXMusic.Pause();
				}
				else
				{
					//g_Music.Resume();
					g_DXMusic.Resume();
				}
			return 0L;
			*/

			//-----------------------------------------------
			// Volume ????
			//-----------------------------------------------
			/*
			case VK_F5 :
				{
					g_pMasterVolume->SetCurrentVolume(
							g_pMasterVolume->GetCurrentVolume() - 0x1000
						);
				}
				//if (g_pPlayer->IsExistAddon(MCreatureWear::ADDON_COAT))
				//	g_pPlayer->SetAddonNULL(MCreatureWear::ADDON_COAT);
				//else g_pPlayer->SetAddon(MCreatureWear::ADDON_COAT, 0);


			return 0L;

			case VK_F6 :
				{
					//g_DXMusic.AddVolume( 0xF000 );
					g_pMasterVolume->SetCurrentVolume(
							g_pMasterVolume->GetCurrentVolume() + 0x1000
						);
				}
				//if (g_pPlayer->IsExistAddon(MCreatureWear::ADDON_TROUSER))
				//	g_pPlayer->SetAddonNULL(MCreatureWear::ADDON_TROUSER);
				//else g_pPlayer->SetAddon(MCreatureWear::ADDON_TROUSER, 1);
			return 0L;
			*/

			//-----------------------------------------------
			//
			//				Debug Mode ??
			//
			//-----------------------------------------------
#if defined(OUTPUT_DEBUG)

		case VK_PAUSE:
			g_bActiveApp = !g_bActiveApp;

			if (g_bActiveApp)
			{
				g_lGameRunBreakTime = timeGetTime() - g_CurrentTime;
			}

			return 0L;

			//-----------------------------------------------
			// Toggle ActiveMode
			//-----------------------------------------------
			//case VK_F1 :
			//	g_bActiveApp = !g_bActiveApp;
			//	return 0L;	

			//-----------------------------------------------
			// ??????? ??? ????
			//-----------------------------------------------
			/*
			case VK_F2 :
			{
				if (g_pPlayer->IsStop())
				{
					// ??????? ???? ????
					//if (g_pPlayer->GetMoveDevice()==MCreature::MOVE_DEVICE_NULL)
					//{
					//	g_pPlayer->SetMoveDevice( MCreature::MOVE_DEVICE_MOTOR1 );
					//}/
					//else
					//{
						//g_pPlayer->SetMoveDevice( MCreature::MOVE_DEVICE_NULL );
					//}

					g_pPlayer->SetAction( ACTION_STAND );

					int type = g_pPlayer->GetCreatureType();

					type++;

					if (type==g_CreatureTable.GetSize())
					{
						g_pPlayer->SetCreatureType( 0 );
					}
					else
					{
						g_pPlayer->SetCreatureType( type );
					}

					// ???? Slayer
					if (g_pPlayer->GetCreatureType()==0)
					{
						g_pPlayer->RemoveAddon( ADDON_COAT );
						g_pPlayer->RemoveAddon( ADDON_TROUSER );

						MCoat		coat1;
						MTrouser	trouser1;

						coat1.SetItemType( 0 ); coat1.SetItemOption( 0 );
						trouser1.SetItemType( 0 ); trouser1.SetItemOption( 0 );

						g_pPlayer->SetAddonHair(ADDONID_HAIR1_MALE, 0);		// type, color
						g_pPlayer->SetAddonItem( &coat1 );
						g_pPlayer->SetAddonItem( &trouser1 );
					}
					else if (g_pPlayer->GetCreatureType()==1)
					{
						g_pPlayer->RemoveAddon( ADDON_COAT );
						g_pPlayer->RemoveAddon( ADDON_TROUSER );

						MCoat		coat1;
						MTrouser	trouser1;

						coat1.SetItemType( 0 ); coat1.SetItemOption( 0 );
						trouser1.SetItemType( 0 ); trouser1.SetItemOption( 0 );

						g_pPlayer->SetAddonHair(ADDONID_HAIR1_FEMALE, 0);		// type,

color
								g_pPlayer->SetAddonItem( &coat1 );
								g_pPlayer->SetAddonItem( &trouser1 );
							}
							else
							{
								g_pPlayer->RemoveAddon( ADDON_COAT );
								g_pPlayer->RemoveAddon( ADDON_TROUSER );
							}


							// ??½~~
							g_pTopView->SetFadeStart(1, 31, 10,  31,0,0);
						}
					}
					return 0L;
					*/


					/*
					case VK_F7 :
						//{
						//	pWaveVolume->SetCurrentVolume(
						//			pWaveVolume->GetCurrentVolume() - 0x1000
						//		);
						//}
						//if (g_pPlayer->IsExistAddon(MCreatureWear::ADDON_SHOES))
							//g_pPlayer->SetAddonNULL(MCreatureWear::ADDON_SHOES);
						//else g_pPlayer->SetAddon(MCreatureWear::ADDON_SHOES, 2);

						// ???? ??? ???
						if (g_pPlayer->IsAttackModeAggress())
						{
							g_pPlayer->SetAttackModePeace();
						}
						else if (g_pPlayer->IsAttackModePeace())
						{
							g_pPlayer->SetAttackModeNormal();
						}
						else if (g_pPlayer->IsAttackModeNormal())
						{
							g_pPlayer->SetAttackModeAggress();
						}

					return 0L;
					*/

					/*
					case VK_F8 :
					{
						//{
							////g_DXMusic.AddVolume( 0xF000 );
							//pWaveVolume->SetCurrentVolume(
									//pWaveVolume->GetCurrentVolume() + 0x1000
								//);
						//}
						//if (g_pPlayer->IsExistAddon(MCreatureWear::ADDON_HELM))
						//	g_pPlayer->SetAddonNULL(MCreatureWear::ADDON_HELM);
						//else g_pPlayer->SetAddon(MCreatureWear::ADDON_HELM, 3);
						static int a = 0;

						if (a==0)
						{
							gC_vs_ui.ChangeToVampireInterface();
							a = 1;
						}
						else
						{
							gC_vs_ui.ChangeToSlayerInterface();
							a = 0;
						}
					}
					return 0L;
					*/

					//-----------------------------------------------
					// Frame Fixing
					//-----------------------------------------------
		case VK_F11:
#if defined(_DEBUG)
			if (g_pDXInput->KeyDown(DIK_LCONTROL) || g_pDXInput->KeyDown(DIK_RCONTROL))
			{
				g_UpdateDelay = (g_UpdateDelay == 1) ? DELAY_UPDATE_GAME : 1;
			}
#endif
			return 0L;

			//-----------------------------------------------
			// debug ?????
			//-----------------------------------------------
		case VK_F12:
			g_bPutMessage = !g_bPutMessage;
			return 0L;

			//-----------------------------------------------
			// Debug Message û??~???
			//-----------------------------------------------
		case VK_DELETE:
		{
#ifdef	OUTPUT_DEBUG
			if (g_pDebugMessage != NULL)
				g_pDebugMessage->Clear();
#endif
		}
		return 0L;

#endif
		}

		return 0L;
		// 		case WM_TIMER :			
		// 			//for (loop = 0; loop < STREAM_MAX; ++loop)
		// //					if (g_pOGG[loop] ) 
		// #ifndef __USE_MP3__
		// 			if( g_DXSound.IsInit() && g_pOGG != NULL )
		// 				g_pOGG->streamUpdate (g_pOGG);
		// #endif
		// 			break;

				//---------------------------------------------------------------
				//
				//							WM_CHAR
				//
				//---------------------------------------------------------------
	case WM_CHAR:
	{
#ifdef __WM_OUTPUT_DEBUG__
		DEBUG_ADD("[WM_CHAR]");
#endif

		/*
		{
			std::ofstream file("inputtest.txt", ios::app);
			file << "input!" << (char)wParam << endl;
			file.close();
		}
		*/
		gC_vs_ui.KeyboardControl(message, wParam, lParam);


#ifdef __WM_OUTPUT_DEBUG__
		DEBUG_ADD("UI KeyCtrl OK");
#endif

		TCHAR ch = (TCHAR)wParam;    // character code 	

		//switch (ch)
		//{
		//	case '`' : g_bDrawMinimap = !g_bDrawMinimap;
		//	return 0L;
		//}

#if defined(OUTPUT_DEBUG) && defined(_DEBUG)
		if (g_Mode == MODE_GAME)
			switch (ch)
			{
				///*
			case '5':
			{
				/*
				for (int i=0; i<g_MaxNPC; i++)
				{
					MCreature* pCreature = g_pZone->GetCreature(1000+i);
					if (pCreature != NULL)
					{
						if (pCreature->IsDead())
						{
							pCreature->SetAlive();
						}
						else
						{
							pCreature->SetDead();
						}
					}
				}
				*/
				if (g_pDXInput->KeyDown(DIK_LCONTROL) || g_pDXInput->KeyDown(DIK_RCONTROL))
				{
					if (g_pPlayer->IsDead())
					{
						g_pPlayer->SetAlive();
						g_pTopView->SetFadeEnd();
					}
					else
					{
						// ???? ???..
						g_pPlayer->SetDead();
					}
				}
			}
			return 0L;
			//*/

			// [ TEST CODE ]
			case '/':
			{
				// ???? ????
				/*
				int newHP = g_pPlayer->GetHP() - 5;
				int newMP = g_pPlayer->GetMP() - 3;

				if (newHP < 0) newHP = 0;
				if (newMP < 0) newMP = 0;

				MStatus* pStatus = new MStatus;
				pStatus->SetStatus(MODIFY_HP, newHP);
				pStatus->SetStatus(MODIFY_MP, newMP);

				// UI????
				gC_vs_ui.SetHP(newHP, 100);
				gC_vs_ui.SetMP(newMP, 100);

				// ????? HP?? ??????? ????
				MActionResult *pResult = new MActionResult;
				pResult->Add( new MActionResultNodeChangeStatus(g_pPlayer->GetID(), pStatus) );

				// ??? Action ???
				//g_pPlayer->PacketSpecialActionResult( SKILL_ATTACK_MELEE );
				g_pPlayer->PacketSpecialActionResult( RESULT_VAMPIRE_DIE );

				// ??? ???? ???(effectID?? ???? ??µ?..)
				g_pPlayer->PacketAddActionResult(0, pResult);


				//switch (rand()%6)
				//{
				//	case 0 : g_pPlayer->SetChatString("huk!"); break;
				//	case 1 : g_pPlayer->SetChatString("kek!"); break;
				//	case 2 : g_pPlayer->SetChatString("uk!"); break;
				//	case 3 : g_pPlayer->SetChatString("-_-!"); break;
				//	case 4 : g_pPlayer->SetChatString("!!!"); break;
				//	case 5 : g_pPlayer->SetChatString("*_*;"); break;
				//}
				*/
			}
			return 0L;
			//*/

			// ??¦ ??? ?????
			case '6':
			{
				g_pTopView->SetFadeStart(25, 31, 2, 31, 0, 0);
			}
			break;

			// ????
			case '7':
			{
				SetLightning(rand() % 4 * 500 + 500);
			}
			break;


			case '.':
			{
				do {
					int newActionInfo;

					if (g_pPlayer->GetSpecialActionInfo() == ACTIONINFO_NULL)
					{
						newActionInfo = MAGIC_LIGHT;
					}
					else
					{
						newActionInfo = g_pPlayer->GetSpecialActionInfo() + 1;
					}

					if (newActionInfo >= (*g_pActionInfoTable).GetMinResultActionInfo())
						newActionInfo = 0;

					int maxPlayerAction = g_pPlayer->GetActionMax();
					int newActionInfoAction = (*g_pActionInfoTable)[newActionInfo].GetAction();

					g_pPlayer->SetSpecialActionInfo(newActionInfo);

					// player?? ??? action?? ???..
					if (newActionInfoAction <= maxPlayerAction)
						break;
				} while (1);
			}
			return 0L;

			case ',':
			{
				do {
					int newActionInfo;

					if (g_pPlayer->GetSpecialActionInfo() == ACTIONINFO_NULL)
					{
						newActionInfo = MAGIC_LIGHT;
					}
					else
					{
						newActionInfo = g_pPlayer->GetSpecialActionInfo() - 1;
					}

					if (newActionInfo < 0)
						newActionInfo = (*g_pActionInfoTable).GetMinResultActionInfo() - 1;

					int maxPlayerAction = g_pPlayer->GetActionMax();
					int newActionInfoAction = (*g_pActionInfoTable)[newActionInfo].GetAction();

					g_pPlayer->SetSpecialActionInfo(newActionInfo);

					// player?? ??? action?? ???..
					if (newActionInfoAction <= maxPlayerAction)
						break;
				} while (1);
			}
			return 0L;
			case 'L':
				g_pPlayer->AddEffectStatus(EFFECTSTATUS_SHRINE_SHIELD, 0xffff);
				return 0L;

			}
#endif
	}
	return 0L;


	/*
	case WM_SETCURSOR:
		// Turn off the cursor since this is a full-screen app
		//if (CDirectDraw::IsActive() )//&& CDirectDraw::IsFullscreen())
		{
			//SetCursor(LoadCursor(NULL, IDC_ARROW));
			//SetCursor(LoadCursorFromFile("Cursor2.cur"));
			//SetCursor(LoadCursor(g_hInstance, MAKEINTRESOURCE(IDC_MYCROSS)));

			//SetCursor(LoadCursorFromFile("Mono.cur"));
			//SetCursor( LoadCursor(g_hInstance, MAKEINTRESOURCE(IDC_TEST)) );

			//SetCursor( LoadIcon(NULL, IDI_ERROR) );

			SetCursor(NULL);

			SetCapture(g_hWnd);
		}
		return TRUE;
	*/
	// `?????½? IME??ð? ?????? ??????? ???.
	//

	//---------------------------------------------------------------
	//
	//				WM_KEYUP
	//				WM_IME_COMPOSITION
	//				WM_IME_STARTCOMPOSITION
	//				WM_IME_ENDCOMPOSITION
	//
	//---------------------------------------------------------------
	case WM_KEYUP:
	case WM_IME_COMPOSITION:
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_ENDCOMPOSITION:

#ifdef __WM_OUTPUT_DEBUG__
		switch (message)
		{
		case WM_KEYUP:
			DEBUG_ADD("[WM_KEYUP]");
			break;

		case WM_IME_COMPOSITION:
			DEBUG_ADD("[WM_IME_COMPOSITION]");
			break;

		case WM_IME_STARTCOMPOSITION:
			DEBUG_ADD("[WM_IME_STARTCOMPOSITION]");
			break;

		case WM_IME_ENDCOMPOSITION:
			DEBUG_ADD("[WM_IME_ENDCOMPOSITION]");
			break;
		}
#endif

		if (((wParam == 244 || wParam == 243 || wParam == 240) && message == 257) ||
			((wParam == 256) && message == 257) ||
			((wParam == 28) && message == 257 && !gC_ci->IsEngInput() && gC_ci->IsJapanese()))
		{
			if (wParam == 240 || wParam == 28)
			{
				gC_ci->SetComposion(false);
			}
			bool	bComposion = gC_ci->GetComposion();
			gC_ci->SetComposion(!bComposion);
		}

		gC_vs_ui.KeyboardControl(message, wParam, lParam);

#ifdef __WM_OUTPUT_DEBUG__
		DEBUG_ADD("[WM_IME_....] OK");
#endif

		if (message == WM_IME_STARTCOMPOSITION)
			return 0;

		break; // ! break!!!!

	}

#ifdef __WM_OUTPUT_DEBUG__
	DEBUG_ADD("[WM_....]");
#endif

	return DefWindowProc(hWnd, message, wParam, lParam);
}

//-----------------------------------------------------------------------------
// Name: InitApp()
// Desc: Do work required for every instance of the application:
//          Create the window, initialize data
//-----------------------------------------------------------------------------
BOOL InitApp(int nCmdShow)
{
	WNDCLASS                    wc;

	// Set up and register window class
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_DARKEDEN));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;//NAME;
	wc.lpszClassName = PROGRAM_NAME;
	RegisterClass(&wc);

	// Calculate the proper size for the window given a client of 640x480
	int cx, cy;
	DWORD style = 0;
	DWORD exStyle = 0;

#ifdef __WEB_BROWSER__
	CoInitialize(NULL);
	if (HRESULT hr = FAILED(CoCreateInstance(CLSID_InternetExplorer, NULL,
		CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (LPVOID*)&g_pWebBrowser)))
	{
		MessageBox(NULL, "IWebBrowser2 Create failed", "ERROR", MB_OK);
		return FALSE;
	}
#endif


	memset(g_macAddress, 0, 6 * sizeof(BYTE));
	//if(GetMacAddressFromSock())

	// MacAddress Operator Check
	if (GetMacAddressFromNetBIOS(g_macAddress))
	{
		bool bMacAddressCheck = CheckMacScreenMode();
		g_pUserInformation->attrOperator.SetAttr(OPERATORTYPE_MACADDRESS, bMacAddressCheck);
	}

	// RelaseLog Operator Check
#if defined(OUTPUT_DEBUG) || defined(_DEBUG) || defined(__DEBUG_OUTPUT__)
	bool bReleaseLogCheck = true;
	g_pUserInformation->attrOperator.SetAttr(OPERATORTYPE_RELEASELOG, bReleaseLogCheck);
#endif


	// ?????? ???? ?????? BoA??~
	// ?????? ??? ??? ????
	// 091112 fakaus
	// ???? ???? â ??? ???? ?????????
	if/*(true)*/ (g_pUserInformation->attrOperator.GetValue())//by kim ??????? 
		// 091112 fakaus	
	{
#if __CONTENTS(__INTERNATIONAL_UI || __CHINESE_UI || __JAPAN_UI)
		int nAnswer = MessageBox(g_hWnd,
			"Do you want to execute darkeden in window mode?", "Question",
			MB_YESNOCANCEL | MB_ICONQUESTION);
#else
		int nAnswer = MessageBox(g_hWnd,
			"â???? ??????ð??????", "â??? ????",
			MB_YESNOCANCEL | MB_ICONQUESTION);
#endif

		if (nAnswer == IDCANCEL)
			return FALSE;

		g_bFullScreen = (nAnswer != IDYES);
	}



	// 2004, 8, 27, sobeit add end - mac address ü? ??, mac screen mode ü?
	if (g_bFullScreen)
	{
		exStyle = WS_EX_APPWINDOW;  // Pseudo-fullscreen: no TOPMOST — InitFullscreen uses HWND_NOTOPMOST to allow alt-tab
		//style = WS_POPUP;
		style = WS_POPUP | WS_CLIPCHILDREN;
		//	style = WS_POPUP|WS_CLIPCHILDREN| WS_CLIPSIBLINGS;
		cx = GetSystemMetrics(SM_CXSCREEN);
		cy = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		// 16??? ???? ??? ???
		//*
		DEVMODE devModeScreen;
		memset(&devModeScreen, 0, sizeof(devModeScreen));
		devModeScreen.dmSize = sizeof(DEVMODE);
		devModeScreen.dmFields = DM_BITSPERPEL;
		devModeScreen.dmBitsPerPel = 16;

		if (ChangeDisplaySettings(&devModeScreen, CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
			ChangeDisplaySettings(&devModeScreen, 0);
		//*/

		exStyle = WS_EX_APPWINDOW;
		style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;//WS_CLIPCHILDREN | WS_OVERLAPPED | WS_THICKFRAME | WS_MINIMIZEBOX;//WS_OVERLAPPEDWINDOW;
		style &= ~WS_MAXIMIZEBOX;

		cx = SURFACE_WIDTH + GetSystemMetrics(SM_CXSIZEFRAME) * 2;
		cy = SURFACE_HEIGHT + GetSystemMetrics(SM_CYSIZEFRAME) * 2 + GetSystemMetrics(SM_CYMENU);
	}

	// Create a window
	g_hWnd = CreateWindowEx(exStyle,//0,
		PROGRAM_NAME,
		PROGRAM_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		cx,
		cy,
		NULL,
		NULL,
		g_hInstance,
		NULL);

	if (!g_hWnd)
	{
		return FALSE;
	}
	/*
	#ifdef __NPROTECT__

	#ifdef __NPROTECT_OLD_VERSION__
		int nProtectResult ;
		// ### nProtect ###
		if( (nProtectResult = RunNPROTECT()) != NPROTECT_OK )
		{
			char szTemp[256];
			wsprintf(szTemp,"nProtect?? ??????? ???????.\n????? ????????? ??? ???????? ????? ??? ????? \n bug@darkeden.com ???? ?????? ??????ñ? ??????.[ErrorCode:%d]",nProtectResult);
			MessageBox(NULL, szTemp,"nProtect Error", MB_OK);
			CloseNPROTECT();
			return FALSE;
		}

		if(g_bForceExitBynProtect2 )
		{
			CloseNPROTECT();
			return FALSE;
		}

	#elif !defined(__NPROTECT_OLD_VERSION__)
		if( RunNPROTECT() != NPROTECT_OK )
		{
			CloseNPROTECT();
			return FALSE;
		}

		if( g_bForceExitBynProtect == true )
		{
			char szTemp[256];

			sprintf(szTemp,"NProtect?? %d ???? ????. ????????? ????????.",g_nProtectErrorMessage);
			MessageBox(NULL,szTemp, "Error", MB_OK);
			return FALSE;
		}
	#endif

	#endif*/

	//
	//ShowWindow(g_hWnd, nCmdShow);
	//UpdateWindow(g_hWnd);
	//SetFocus(g_hWnd);

	//---------------------------------------------------
	// DirectX Version check
	//---------------------------------------------------
	//if (!CheckDXVersion())
	//{
	//	return 0;
	//}

	// cursor?? ???????.
	SetCursor(NULL);
	ShowCursor(FALSE);

	// window?? ???????.
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	//SetFocus(g_hWnd);

#ifdef __NPROTECT__

#ifdef __NPROTECT_OLD_VERSION__
	int nProtectResult;
	// ### nProtect ###
	if ((nProtectResult = RunNPROTECT()) != NPROTECT_OK)
	{
		char szTemp[256];
		wsprintf(szTemp, "nProtect?? ??????? ???????.\n????? ????????? ??? ???????? ????? ??? ????? \n bug@darkeden.com ???? ?????? ??????ñ? ??????.[ErrorCode:%d]", nProtectResult);
		MessageBox(NULL, szTemp, "nProtect Error", MB_OK);
		CloseNPROTECT();
		return FALSE;
	}

	if (g_bForceExitBynProtect2)
	{
		CloseNPROTECT();
		return FALSE;
	}

#elif !defined(__NPROTECT_OLD_VERSION__)
#if __CONTENTS(__NPROTECT)
	if (RunNPROTECT() != NPROTECT_OK)
	{
		CloseNPROTECT();
		return FALSE;
	}

	if (g_bForceExitBynProtect == true)
	{
		char szTemp[256];

		sprintf(szTemp, "NProtect?? %d ???? ????. ????????? ????????.", g_nProtectErrorMessage);
		MessageBox(NULL, szTemp, "Error", MB_OK);
		return FALSE;
	}
#endif //__NPROTECT
#endif

#endif


	//---------------------------------------------------
	// Init Game
	//---------------------------------------------------
	return InitGame();
}


//extern void OutputMemorySize();
//#include "MemoryCheck.cpp"
//#include "UIDialog.h"

//-----------------------------------------------------------------------------
// Check TerriblePatch
//-----------------------------------------------------------------------------
bool CheckTerriblePatch()
{
	bool bCrash = false;
	int errorCode = 0;

	//-----------------------------------------------------------------------------
	// ImageObject Patch
	//-----------------------------------------------------------------------------
	AppendPatchTable apt;

	/*
	#ifdef _DEBUG
		apt.Init( 2 );

		//-----------------------------------------------------------------------------
		// ImageObject Patch
		//-----------------------------------------------------------------------------
		apt[0].SetOriginalInfo( FILE_SPRITE_IMAGEOBJECT, 47564158, 0x04CA );
		apt[0].AddAppendInfo( "Data\\Image\\New18ImageObject.spk", 1968462, 0x82 );
		apt[0].AddAppendInfo( "Data\\Image\\New22ImageObject.spk", 5706400, 0x8A );
		apt[0].SetFinalInfo( 55239016, 0x05D6 );

		//-----------------------------------------------------------------------------
		// Creature Patch
		//-----------------------------------------------------------------------------
		apt[1].SetOriginalInfo( FILE_ISPRITE_CREATURE, 47722828, 0x2A4E );
		apt[1].AddAppendInfo( "Data\\Image\\New18Creature.ispk", 4343846, 0x0418 );
		apt[1].AddAppendInfo( "Data\\Image\\New22Creature.ispk", 9813886, 0x0798 );
		apt[1].SetFinalInfo( 61880556, 0x35FE );


		//-----------------------------------------------------------------------------
		// Save
		//-----------------------------------------------------------------------------
		std::ofstream fileAppendInfo2(FILE_INFO_APPENDPATCH, ios::binary);
		apt.SaveToFile( fileAppendInfo2 );
		fileAppendInfo2.close();
	#endif
	*/

	//-----------------------------------------------------------------------------
	// Load
	//-----------------------------------------------------------------------------
	ivfstream fileAppendInfo;
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_APPENDPATCH").c_str(), fileAppendInfo))
		return false;
	apt.LoadFromFile(fileAppendInfo);
	fileAppendInfo.close();



	//-----------------------------------------------------------------------------
	// Append ????? ???.
	//-----------------------------------------------------------------------------
	errorCode = 0;
	for (int i = 0; i < apt.GetSize(); i++)
	{
		errorCode++;

		if (errorCode == 31)
			int n = 0;

		if (!apt[i].ExecutePatch())
		{
			bCrash = true;
			break;
		}

		errorCode++;
		if (!apt[i].CheckFinalInfo())
		{
#ifdef OUTPUT_DEBUG				
#else
			bCrash = true;
			break;
#endif
		}

	}

	//-----------------------------------------------------------------------
	// ????? ??????? - -; 
	//-----------------------------------------------------------------------
	if (bCrash)
	{
		char str[256];
		sprintf(str, "????? ??????????. ??????? ???????? ????????? [???????:%d]", errorCode);
		MessageBox(NULL, str, PROGRAM_TITLE, MB_OK);

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
// Check TerriblePatch
//-----------------------------------------------------------------------------
// auto-patch?? ????? ?????
// ??¿ ?? ???? ?????????? ü???? ????????? ??????.
// ??????.. ??? ????? ????? ?????.  --;;
//-----------------------------------------------------------------------------
/*
bool
CheckTerriblePatchOLD()
{
	bool bCrash = false;
	int errorCode = 0;

	//-----------------------------------------------------------------------
	//
	// Update SpritePack
	//
	//-----------------------------------------------------------------------
	// Data\\Image\\?? New18ImageObjectSPK.spk?? ??????..
	// ImageObject?? ?????? ??ü?????? ??????.. ???? ??????
	// "??? ????? ??µ? ?ð??? ?? ??????."??? ??????? ??????.
	// ??ü??????? SPK ??? ???
	// ImageObjectSPK?? SPK?? Load???.
	// New18ImageObjectSPK?? SPK?? Load???.
	// SPK?? ImageObjectSPK?? write???.
	// New18ImageObjectSPK.spk?? ?????.
	//
	// [22?? ???????????..]
	// ?????? ????? ????? ?? ?????????????? ???????? ????? ???????
	// 18???????? ?????? 18?? ?????????? ????
	// 22???????? ?????? 22?? ?????????? ????... ???.
	const int numWrite = 2;
	char newSpkFilename[numWrite][80] =
	{
		"Data\\Image\\New18ImageObject.spk",
		"Data\\Image\\New22ImageObject.spk"
	};
	const long writePosition[numWrite] =
	{
		47564158,	// 18?? ??? ?????? file position
		49532618	// 22?? ??? ?????? file position
	};
	const WORD orgSpkSize[numWrite] =
	{
		0x054C,		// 18?? ??? ?????? ????
		0x05D6		// 22?? ??? ?????? ????
	};
	const long orgFileSize[numWrite] =
	{
		49532618,	// 18?? ??? ?????? ????????
		55239016	// 22?? ??? ?????? ????????
	};

	WORD spkSize;
	std::ifstream imageObjectFile;//(FILE_ISPRITEINDEX_CREATURE, ios::binary);
	if (!FileOpenBinary(FILE_SPRITE_IMAGEOBJECT, imageObjectFile))
		return false;
	imageObjectFile.read((char*)&spkSize, 2);	// Sprite?? ????
	imageObjectFile.close();

	//-----------------------------------------------------------------------
	// ?? ????? ???
	//-----------------------------------------------------------------------
	bool bImageObjectPatch;
	if (spkSize==orgSpkSize[numWrite-1])
	{
		 bImageObjectPatch = false;
	}
	else
	{
		bImageObjectPatch = true;
	}

	//-----------------------------------------------------------------------
	// ????? ???????? ??? ???
	//-----------------------------------------------------------------------
	if (bImageObjectPatch)
	{
		//MessageBox(NULL, "??????? ????Ÿ?? ??????? ?????? ????????.\n OK?? ?????? ?????? ?????? ??????? ?????? ??ø? ??

????????.", PROGRAM_TITLE, MB_OK);

		for (int i=0; i<numWrite; i++)
		{
			std::ifstream newfile(newSpkFilename[i], ios::binary | ios::nocreate);

			//-------------------------------------------------------------
			// ??? ????? ???? ???.. ?????? ü?
			//-------------------------------------------------------------
			if (!newfile.is_open())
			{
				continue;
			}
			else
			{
				SetProgressBarText("??? ????? ???????? ??????.");
				UpdateProgressBar();

				std::ofstream imageObjectFile(FILE_SPRITE_IMAGEOBJECT, ios::binary | ios::ate);

				newfile.seekg( 2 );	// size??? ????
				imageObjectFile.seekp( writePosition[i] );

				WRITE_FROM_FILE( imageObjectFile, newfile );

				newfile.close();

				// ???? ????
				spkSize = orgSpkSize[i];
				imageObjectFile.seekp( 0, ios::beg );
				imageObjectFile.write((const char*)&spkSize, 2);
				imageObjectFile.close();

				// ???????? ?????.
				remove( newSpkFilename[i] );
			}
		}
	}


	//-----------------------------------------------------------------------
	//
	// Append SpritePack
	//
	//-----------------------------------------------------------------------
	//
	//-----------------------------------------------------------------------
	// Data\\Image\\New18Creature.ispk - 2001.9.26
	// ??????????, ?????????, ?????????
	// ?? ???????? spki?? ???? ????? ???.
	if (!bCrash)
	{
		const int numAppend = 2;
		char orgFilename[numAppend][80] =
		{
			"Data\\Image\\Creature.ispk",
			"Data\\Image\\Creature.ispk"
		};
		char appFilename[numAppend][80] =
		{
			"Data\\Image\\New18Creature.ispk",
			"Data\\Image\\New22Creature.ispk"
		};

		int total[numAppend] =
		{
			0x2E66,
			0x35FE
		};

		// ?????? append??? total?? ??????? ??? ??? ???.

		WORD orgNum, appNum;

		for (int i=0; i<numAppend; i++)
		{

			class fstream orgFile(orgFilename[i], ios::in | ios::out | ios::binary | ios::nocreate | ios::ate);
			std::ifstream appFile(appFilename[i], ios::binary | ios::nocreate);

			//-------------------------------------------------------------
			// ???? ????? ???? ??? - -;
			//-------------------------------------------------------------
			if (!orgFile.is_open())
			{
				bCrash = true;
				errorCode = 1;
				break;
			}

			orgFile.seekg( 0, ios::beg );
			orgFile.read((char*)&orgNum, 2);	// Sprite?? ????

			if (orgNum>=total[i])
			{
				// ??? ????? ??????. ?????? ü?.
				orgFile.close();
				appFile.close();
				continue;
			}

			//-------------------------------------------------------------
			// app??? ???? ???
			//-------------------------------------------------------------
			if (!appFile.is_open())
			{
				// ?????? ????? app????? ???? ???
				bCrash = true;
				errorCode = 2;
				break;
			}

			// total size?? ü???? append?? ??? ????? ü????.
			appFile.read((char*)&appNum, 2);	// Sprite?? ????

			//-------------------------------------------------------------
			// ??? ????? total?? ????..
			//-------------------------------------------------------------
			if (orgNum+appNum == total[i])
			{
				SetProgressBarText("??? ????? ???????? ??????.");
				UpdateProgressBar();

				// orgFile?? ??????..
				orgFile.seekp(0, ios::end);

				WRITE_FROM_FILE( orgFile, appFile );

				// ???? ????? ?????? ??????.
				orgFile.seekp(0, ios::beg);
				orgFile.write((const char*)&total[i], 2);

				orgFile.close();
				appFile.close();

				//---------------------------------------------------------------
				// App????? ?????.
				//---------------------------------------------------------------
				remove( appFilename[i] );
			}
			//-------------------------------------------------------------
			// size ????.. - -;
			//-------------------------------------------------------------
			else
			{
				// ?? ?? ????? ?????? ????? ?????? ??? ???
				// ????? ??????.
				bCrash = true;
				errorCode = 3;
				break;
			}
		}
	}

	//-----------------------------------------------------------------------
	// ????? ??????.
	//-----------------------------------------------------------------------
	if (bCrash)
	{
		char str[256];
		sprintf(str, "????? ??????????. ??????? ???????? ????????? [???????:%d]", errorCode);
		MessageBox(NULL, str, PROGRAM_TITLE, MB_OK);

		return false;
	}

	return true;
}
*/

//-----------------------------------------------------------------------------
// ConvertScreenEffect
//-----------------------------------------------------------------------------
// ?????? AlphaEffect?? ScreenEffect?? ?°? ????.
//-----------------------------------------------------------------------------
/*
bool
ConvertScreenEffect()
{
	//------------------------------------------------------------
	// Screen SpritePack ???
	//------------------------------------------------------------

//	std::ifstream fileSPK2(FILE_SPRITE_SCREENEFFECT, ios::binary | ios::nocreate);
//	if (fileSPK2.is_open())
//	{
//		TYPE_SPRITEID num;
//		fileSPK2.read((char*)&num, SIZE_SPRITEID);
//
//		// ??? ??????.. convert?? ??? ????.
//		if (num >= 0x06BE)
//		{
//			return false;
//		}
//
//		fileSPK2.close();
//	}

/*	std::ifstream fileSPK2("Data\\Info\\EffectScreenConvert.inf", ios::binary | ios::nocreate);
	if (fileSPK2.is_open())
	{
		fileSPK2.close();
		return false;
	}


	const int MAX_EST = 135;
	const int est[MAX_EST] =
	{
		SCR_EFFECTSPRITETYPE_ACID_BALL_1,		// ???????
		SCR_EFFECTSPRITETYPE_ACID_BALL_2,		// ??????
		SCR_EFFECTSPRITETYPE_ACID_BOLT_1,		// ???????
		SCR_EFFECTSPRITETYPE_ACID_BOLT_2,		// ??????
		SCR_EFFECTSPRITETYPE_ACID_TOUCH,
		SCR_EFFECTSPRITETYPE_AURA_PRISM_SHIELD,	// ???
		SCR_EFFECTSPRITETYPE_AURA_BALL_1,	// ?????
		SCR_EFFECTSPRITETYPE_AURA_BALL_2,	// ???????
		SCR_EFFECTSPRITETYPE_AURA_BALL_3,	// ??????
		SCR_EFFECTSPRITETYPE_AURA_PRISM_1,	// ????? - ???? ???
		SCR_EFFECTSPRITETYPE_AURA_PRISM_2,	// ????? - ?????? ???? ?ö???
		SCR_EFFECTSPRITETYPE_AURA_PRISM_3,	// ??? ????
		SCR_EFFECTSPRITETYPE_AURA_PRISM_4,	// ??? ???
		SCR_EFFECTSPRITETYPE_AURA_PRISM_5,	// ??? ??
		SCR_EFFECTSPRITETYPE_AURA_SHIELD_1,	// ?????
		SCR_EFFECTSPRITETYPE_AURA_SHIELD_2,	// ????
		SCR_EFFECTSPRITETYPE_AURA_SHIELD_3,	// ???? ?? ??½~
		SCR_EFFECTSPRITETYPE_AURA_RING,
		SCR_EFFECTSPRITETYPE_BLESS_GROUND_1,
		SCR_EFFECTSPRITETYPE_BLESS_GROUND_2,
		SCR_EFFECTSPRITETYPE_BLESS_GROUND_3,
		SCR_EFFECTSPRITETYPE_BLESS_GROUND_4,
		SCR_EFFECTSPRITETYPE_BLESS_ING,		// ???
		SCR_EFFECTSPRITETYPE_BLESS,			// ??? ??????? ??? //????
		SCR_EFFECTSPRITETYPE_CHAOS_COMBO,
		SCR_EFFECTSPRITETYPE_CONTINUAL_LIGHT_1,
		SCR_EFFECTSPRITETYPE_CONTINUAL_LIGHT_2,
		SCR_EFFECTSPRITETYPE_CONTINUAL_LIGHT_3,
		SCR_EFFECTSPRITETYPE_CREATE_HOLY_WATER_1,
		SCR_EFFECTSPRITETYPE_CREATE_HOLY_WATER_2,
		SCR_EFFECTSPRITETYPE_CREATE_HOLY_WATER_3,
		SCR_EFFECTSPRITETYPE_CURE_PARALYSIS,
		SCR_EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_1,
		SCR_EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2,
		SCR_EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3,
		SCR_EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_1,
		SCR_EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_2,
		SCR_EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_3,
		SCR_EFFECTSPRITETYPE_CURE_LIGHT_WOUND_1,
		SCR_EFFECTSPRITETYPE_CURE_LIGHT_WOUND_2,
		SCR_EFFECTSPRITETYPE_CURE_LIGHT_WOUND_3,
		SCR_EFFECTSPRITETYPE_CURE_POISON,
		SCR_EFFECTSPRITETYPE_DETECT_HIDDEN,
		SCR_EFFECTSPRITETYPE_DOUBLE_IMPACT,
		SCR_EFFECTSPRITETYPE_ENCHANT_CASTING1_1,
		SCR_EFFECTSPRITETYPE_ENCHANT_CASTING1_2,
		SCR_EFFECTSPRITETYPE_ENCHANT_CASTING1_3,
		SCR_EFFECTSPRITETYPE_ENCHANT_CASTING2_1,
		SCR_EFFECTSPRITETYPE_ENCHANT_CASTING2_2,
		SCR_EFFECTSPRITETYPE_ENCHANT_CASTING2_3,
		SCR_EFFECTSPRITETYPE_EXPLOSION_OLD,
		SCR_EFFECTSPRITETYPE_HEALING_CASTING_1,
		SCR_EFFECTSPRITETYPE_HEALING_CASTING_2,
		SCR_EFFECTSPRITETYPE_HEALING_CASTING_3,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_AR_MALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_SMG_MALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_TR_MALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_SG_MALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_AR_FEMALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_SMG_FEMALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_TR_FEMALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_SG_FEMALE,
		SCR_EFFECTSPRITETYPE_HOLY_SHOOTING_HIT,
		SCR_EFFECTSPRITETYPE_HOLY_WATER_1,	// ?????°?
		SCR_EFFECTSPRITETYPE_HOLY_WATER_2,	// ????? - -;
		SCR_EFFECTSPRITETYPE_HURRICANE_COMBO,
		SCR_EFFECTSPRITETYPE_LIGHT_1,
		SCR_EFFECTSPRITETYPE_LIGHT_2,
		SCR_EFFECTSPRITETYPE_LIGHT_3,
		SCR_EFFECTSPRITETYPE_POISONOUS_HAND,
		SCR_EFFECTSPRITETYPE_POTENTIAL,
		SCR_EFFECTSPRITETYPE_PROTECTION_FROM_CURSE,
		SCR_EFFECTSPRITETYPE_PROTECTION_FROM_PARALYSIS,
		SCR_EFFECTSPRITETYPE_PROTECTION_FROM_POISON,
		SCR_EFFECTSPRITETYPE_RAINBOW_SLASHER,
		SCR_EFFECTSPRITETYPE_REMOVE_CURSE,
		SCR_EFFECTSPRITETYPE_RESTORE_1,
		SCR_EFFECTSPRITETYPE_RESTORE_2,
		SCR_EFFECTSPRITETYPE_RESTORE_3,
		SCR_EFFECTSPRITETYPE_GUN_AR_MALE,
		SCR_EFFECTSPRITETYPE_GUN_SMG_MALE,
		SCR_EFFECTSPRITETYPE_GUN_AR_FEMALE,
		SCR_EFFECTSPRITETYPE_GUN_SMG_FEMALE,
		SCR_EFFECTSPRITETYPE_GUN_TR_MALE,
		SCR_EFFECTSPRITETYPE_GUN_SG_MALE,
		SCR_EFFECTSPRITETYPE_GUN_TR_FEMALE,
		SCR_EFFECTSPRITETYPE_GUN_SG_FEMALE,
		SCR_EFFECTSPRITETYPE_SCREW_SLASHER,
		SCR_EFFECTSPRITETYPE_SINGLE_BLOW,
		SCR_EFFECTSPRITETYPE_SMOKE,
		SCR_EFFECTSPRITETYPE_SMOKE_1,
		SCR_EFFECTSPRITETYPE_SMOKE_2,
		SCR_EFFECTSPRITETYPE_SMOKE_3,
		SCR_EFFECTSPRITETYPE_SMOKE_4,
		SCR_EFFECTSPRITETYPE_SNAKE_COMBO_OLD,
		SCR_EFFECTSPRITETYPE_SPIRAL_SLAY,
		SCR_EFFECTSPRITETYPE_STRIKING_ING_1,
		SCR_EFFECTSPRITETYPE_STRIKING_ING_2,
		SCR_EFFECTSPRITETYPE_STRIKING_ING_3,
		SCR_EFFECTSPRITETYPE_STRIKING_1,
		SCR_EFFECTSPRITETYPE_STRIKING_2,
		SCR_EFFECTSPRITETYPE_STRIKING_3,
		SCR_EFFECTSPRITETYPE_THUNDER_SPARK,
		SCR_EFFECTSPRITETYPE_TRIPLE_BREAK,
		SCR_EFFECTSPRITETYPE_TRIPLE_SLASHER,
		SCR_EFFECTSPRITETYPE_TWIN_BREAK,
		SCR_EFFECTSPRITETYPE_VAMPIRE_DEATH,
		SCR_EFFECTSPRITETYPE_WILD_SMASH,
		SCR_EFFECTSPRITETYPE_DETECT_INVISIBILITY,
		SCR_EFFECTSPRITETYPE_IDENTIFY_1x1,
		SCR_EFFECTSPRITETYPE_IDENTIFY_1x3,
		SCR_EFFECTSPRITETYPE_IDENTIFY_2x2,
		SCR_EFFECTSPRITETYPE_IDENTIFY_2x3,
		SCR_EFFECTSPRITETYPE_SACRIFICE_1,			// casting
		SCR_EFFECTSPRITETYPE_SACRIFICE_2,			// ????
		SCR_EFFECTSPRITETYPE_SNAKE_COMBO,
		SCR_EFFECTSPRITETYPE_SWORD_WAVE_1,			// frame?? ???? ????.
		SCR_EFFECTSPRITETYPE_SWORD_WAVE_2,			// frame?? ???? ????.
		SCR_EFFECTSPRITETYPE_SWORD_WAVE_3,			// frame?? ???? ????.
		SCR_EFFECTSPRITETYPE_TORNADO_SEVER_1,		// ???? ?????°? (5?????? ??? ???)
		SCR_EFFECTSPRITETYPE_TORNADO_SEVER_2,		// ???? ??°?

		SCR_EFFECTSPRITETYPE_EXPLOSION,

		// 2001.9.3
		SCR_EFFECTSPRITETYPE_LIGHTNING_HANDS_1,8
		SCR_EFFECTSPRITETYPE_LIGHTNING_HANDS_2,		// ???
		SCR_EFFECTSPRITETYPE_LIGHTNING_HANDS_3,

		// 2001.9.6
		SCR_EFFECTSPRITETYPE_PROTECTION_FROM_ACID_1,		// ????
		SCR_EFFECTSPRITETYPE_PROTECTION_FROM_ACID_2,		// ????

		// 2001.10.8
		SCR_EFFECTSPRITETYPE_EXPLOSION_2,
		SCR_EFFECTSPRITETYPE_EXPLOSION_3,
		SCR_EFFECTSPRITETYPE_CURE_ALL_1,				// ????
		SCR_EFFECTSPRITETYPE_CURE_ALL_2,				// bless ??????
		SCR_EFFECTSPRITETYPE_ENCHANT_1x1,
		SCR_EFFECTSPRITETYPE_ENCHANT_1x3,
		SCR_EFFECTSPRITETYPE_ENCHANT_2x2,
		SCR_EFFECTSPRITETYPE_ENCHANT_2x3
	};

	//------------------------------------------------------------
	// convert???.. progress.. ??..
	//------------------------------------------------------------
	SetProgressBarText("????Ÿ ????? ü???????.");
	SetProgressBarCount( MAX_EST );

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	ShowWindow(g_hWndProgress, SW_HIDE);
	CDirectDraw::Init(g_hWndProgress, cx, cy, CDirectDraw::FULLSCREEN);

	MoveWindow(g_hWndProgress,
				(cx-progressBarWidth)/2,
				(cy-progressBarHeight)/2,
				progressBarWidth,
				progressBarHeight,
				TRUE);
	ShowWindow(g_hWndProgress, SW_SHOW);


	// 16 bit ???? ???? ???.
	//DDSURFACEDESC2 ddsd;
	//CDirectDraw::GetDD()->GetDisplayMode( &ddsd );
	//CDirectDraw::GetDD()->SetDisplayMode(800, 600, 16, 0, 0);


	//------------------------------------------------------------
	// ????? Frame ???
	//------------------------------------------------------------
	COrderedList<int> intList;

	std::ifstream efpkFile(FILE_EFRAME_ALPHAEFFECT, ios::binary);
	CEffectFramePack	EFPK;
	EFPK.LoadFromFile( efpkFile );
	efpkFile.close();

	CEffectFramePack	NewEFPK;
	NewEFPK.Init( MAX_EST );

	//------------------------------------------------------------
	// ????? EFPK?? ??????? ???? SpriteID?? ?????.
	//------------------------------------------------------------
	for (int e=0; e<MAX_EST; e++)
	{
		int etype = est[e];

		DIRECTION_EFFECTFRAME_ARRAY& DEA = EFPK[etype];

		NewEFPK[e] = DEA;

		for (int d=0; d<8; d++)
		{
			EFFECTFRAME_ARRAY& EA = DEA[d];

			for (int f=0; f<EA.GetSize(); f++)
			{
				CEffectFrame& Frame = EA[f];

				int spriteID = Frame.GetSpriteID();

				intList.Add( spriteID );
			}
		}

		UpdateProgressBar();
	}

	EFPK.Release();

	//------------------------------------------------------------
	// Alpha --> Normal ???..
	//------------------------------------------------------------
	CSpriteSurface	surface;
	surface.InitOffsurface( 640, 480, DDSCAPS_SYSTEMMEMORY );

	POINT point0 = { 0, 0 };


	CAlphaSprite565		ASPR;

	std::ifstream aspkiFile(FILE_ASPRITEINDEX_ALPHAEFFECT, ios::binary);
	std::ifstream aspkFile(FILE_ASPRITE_ALPHAEFFECT, ios::binary);

	TYPE_SPRITEID totalNum;
	int spriteNum = intList.GetSize();

	CSpritePack* pSPK = new CSpritePack;
	pSPK->Init( spriteNum, CDirectDraw::Is565() );

	aspkFile.read((char*)&totalNum, 2);

	int* pNewID = new int [totalNum];

	COrderedList<int>::DATA_LIST::const_iterator iID = intList.GetIterator();
	WORD *lpSurface, lPitch;

	//------------------------------------------------------------
	// convert???.. progress.. ??..
	//------------------------------------------------------------
	SetProgressBarText("????Ÿ ????? ??????????.");
	SetProgressBarCount( spriteNum/8 );


	//------------------------------------------------------------
	// Alpha --> Normal
	//------------------------------------------------------------
	for (int sid=0; sid<spriteNum; sid++)
	{
		int spriteID = *iID;

		aspkFile.seekg( 0 );
		aspkiFile.seekg( 0 );

		//--------------------------------------------------------
		// Load?? FilePointer?? ???´?.
		//--------------------------------------------------------
		long fp;
		aspkiFile.seekg( 2 + spriteID*4 );		// 2(num) + spriteID * (4 bytes)
		aspkiFile.read((char*)&fp, 4);
		aspkFile.seekg( fp );

		//--------------------------------------------------------
		// Load
		//--------------------------------------------------------
		ASPR.LoadFromFile( aspkFile );

		//--------------------------------------------------------
		// ??? ???.. ?? - -
		//--------------------------------------------------------
		int width = ASPR.GetWidth();
		int height = ASPR.GetHeight();

		//--------------------------------------------------------
		// AlphaSprite?? ????? ???
		// Sprite?? ???????.
		//--------------------------------------------------------
		surface.FillSurface( 0 );

		surface.LockW(lpSurface, lPitch);
		surface.BltAlphaSprite( &point0, &ASPR );
		((*pSPK)[sid]).SetPixel(lpSurface, lPitch, width, height);

		surface.Unlock();

		// ?????? ID?? spriteID?????? sid?? ???? ???.
		pNewID[ spriteID ] = sid;

		if ((sid & 0x00000007)==0x00000007)
		{
			UpdateProgressBar();
		}

		iID++;
	}

	aspkiFile.close();
	aspkFile.close();

	// ???????
	//CDirectDraw::GetDD()->RestoreDisplayMode();

	//------------------------------------------------------------
	// SpriteID?? ???????.
	//------------------------------------------------------------
	int numFPK = NewEFPK.GetSize();
	for (e=0; e<numFPK; e++)
	{
		DIRECTION_EFFECTFRAME_ARRAY& DEA = NewEFPK[e];

		for (int d=0; d<8; d++)
		{
			EFFECTFRAME_ARRAY& EA = DEA[d];

			for (int f=0; f<EA.GetSize(); f++)
			{
				CEffectFrame& Frame = EA[f];

				int cx = Frame.GetCX();
				int cy = Frame.GetCY();
				int light = Frame.GetLight();
				int spriteID = pNewID[ Frame.GetSpriteID() ];

				Frame.Set( spriteID, cx, cy, light );
			}
		}
	}

	delete [] pNewID;

	//------------------------------------------------------------
	// FramePack????
	//------------------------------------------------------------
	std::ofstream fileFPK(FILE_EFRAME_SCREENEFFECT, ios::binary);
	std::ofstream fileFPKI(FILE_EFRAMEINDEX_SCREENEFFECT, ios::binary);
	NewEFPK.SaveToFile( fileFPK, fileFPKI );
	fileFPK.close();
	fileFPKI.close();

	//------------------------------------------------------------
	// SpritePack ????
	//------------------------------------------------------------
	std::ofstream fileSPK(FILE_SPRITE_SCREENEFFECT, ios::binary);
	std::ofstream fileSPKI(FILE_SPRITEINDEX_SCREENEFFECT, ios::binary);
	pSPK->SaveToFile( fileSPK, fileSPKI );
	fileSPK.close();
	fileSPKI.close();

	delete pSPK;

	ShowWindow(g_hWndProgress, SW_HIDE);
	CDirectDraw::ReleaseAll();

	MoveWindow(g_hWndProgress,
				(cx-progressBarWidth)/2,
				(cy-progressBarHeight)/2,
				progressBarWidth,
				progressBarHeight,
				TRUE);
	ShowWindow(g_hWndProgress, SW_SHOW);

	//------------------------------------------------------------
	// ??? ü?
	//------------------------------------------------------------
	std::ofstream fileCheck("Data\\Info\\EffectScreenConvert.inf", ios::binary);
	int a = 1;
	fileCheck.write((const char*)&a, 4);
	fileCheck.close();

	return true;
}
*/
//------------------------------------------------------------------------
// ApplyPatch 
//------------------------------------------------------------------------
// ????? ?????? ??? ??? ?????... - -;
//------------------------------------------------------------------------
bool ApplyPatch()
{
	//-----------------------------------------------------------------
	// ???? version
	//-----------------------------------------------------------------
//	std::ifstream versionFile(FILE_INFO_VERSION, ios::binary);
//	int version;
//	versionFile.read((char*)&version, 4);
//	versionFile.close();

	//-----------------------------------------------------------------
	// ???????????? ??? ???
	//-----------------------------------------------------------------
//	char packFilename[256];
//	char infoFilename[256];

//	struct _finddata_t	FileData;
//	long				hFile;

	//-----------------------------------------------------------------
	// *.mpk file?? ã?´?.
	//-----------------------------------------------------------------
//	if ( (hFile = _findfirst( "*.mpk", &FileData )) != -1L )
//	{		
//		int files = 1;
//		do
//		{
//			strcpy(packFilename, FileData.name);
//			files ++;
//		}
//		while (_findnext( hFile, &FileData ) == 0);
//
//		_findclose( hFile );			

		//-----------------------------------------------------------------
		// ???????????? ???? ???? 
		//-----------------------------------------------------------------
//		_mkdir( "Update" );
//
//		SetProgressBarText("??? ????? ?????? ??????? ??????.");
//
//		MZLib mzlib;
//
//		// ??????? Updater???? ???? ??????????? ???? ?????.
//		mzlib.Uncompress( packFilename );	
//
//		//-----------------------------------------------------------------
//		// infofile??? ???? - packFilename?? ????..
//		//-----------------------------------------------------------------
//		int len = strlen(packFilename);
//		char str[256];
//		strncpy(str, packFilename, len-4);	// ?? .???? ?????.
//		str[len-4] = '\0';
//		sprintf(infoFilename, "Update\\%s.inf", str);
//
//	}
	//-----------------------------------------------------------------
	// mpk????? ???? ???? ????????? ??? ü?????????.
	// packFilename?? ??? version?? ?????°??? ??????.
	//-----------------------------------------------------------------
//	else
//	{
//		/*
//		char* pUnder = strchr(packFilename+5, "_");
//		if (pUnder!=NULL)
//		{   
//			char strVersion[10];
//			strncpy(strVersion, packFilename+5, pUnder - packFilename+5);
//			int versionFrom = atoi(strVersion);
//		}
//		*/
//		
//		// ???? ?????? ?´? ???????? ã?´?.
//		sprintf(infoFilename, "Update\\Patch%d_*.inf", version);
//
//		if ( (hFile = _findfirst( infoFilename, &FileData )) != -1L )
//		{	
//			int files = 1;
//			do
//			{
//				sprintf(infoFilename, "Update\\%s", FileData.name);
//				files ++;
//			}
//			while (_findnext( hFile, &FileData ) == 0);
//			
//			_findclose( hFile );
//		}
//		else
//		{
//			// ????????? ???? ??? == ???? ????
//			return false;
//		}
//	}
//
//	//-----------------------------------------------------------------
//	// info ???
//	//-----------------------------------------------------------------	
//	CreateProgressBar("??? ?????? ü? ??????.");
//	
//	UpdateManager	UM;
//	UM.load( infoFilename );
//
//	SetProgressBarCount( UM.getNum()+g_numAppendFiles );	
//
//	SetProgressBarText("??? ????? ???????? ??????.");
//	
//	//-----------------------------------------------------------------
//	// ?????? ????
//	//-----------------------------------------------------------------
//	int newVersion = 0;
//	while (!UM.empty())
//	{
//		Update* pUpdate = UM.front();
//		UM.pop_front();
//		
//		if (!pUpdate->execute())
//		{
//			// -_-;;
//		}	
//
//		// version up????
//		if (pUpdate->getVersion() > newVersion)
//		{
//			newVersion = pUpdate->getVersion();
//		}
//
//		UpdateProgressBar();
//	}
//
//	//-----------------------------------------------------------------
//	// ?? version????
//	//-----------------------------------------------------------------
//	std::ofstream versionFile2(FILE_INFO_VERSION, ios::binary);
//	versionFile2.write((const char*)&newVersion, 4);
//	versionFile2.close();
//	
//	//-----------------------------------------------------------------
//	// ?????????? ????
//	//-----------------------------------------------------------------
//	remove( packFilename );
//
//	//-----------------------------------------------------------------
//	// ?????? ???? - Updater ???? ????? ???? .. ??? ?? ?? ???.
//	//-----------------------------------------------------------------
//
	return true;
}


#ifdef OUTPUT_DEBUG
//-----------------------------------------------------------------------------
// Check LogFile
//-----------------------------------------------------------------------------
//	void
//	CheckCLogFile()
//	{
//		_chdir( g_CWD );
//
//		char filename[256] = { 0, };
//		char buffer[256] = { 0, };
//		char computerName[256] = { 0, };
//
//		struct _finddata_t	FileData;
//		long				hFile;
//
//		//-----------------------------------------------------------------
//		// *.spk file?? ã?´?.
//		//-----------------------------------------------------------------
//		if ( (hFile = _findfirst( "Data\\UI\\txt\\Log*.txt", &FileData )) != -1L )
//		{
//			do
//			{
//				sprintf(filename, "Data\\UI\\txt\\%s", FileData.name);
//				
//				std::ifstream file( filename, ios::binary );
//				file.seekg( 0, ios::end );
//				
//				long fp = file.tellg();
//				
//				file.close();
//				if (fp == 0)
//				{
//					_chmod( filename, _S_IREAD | _S_IWRITE );
//					remove(filename);	
//				}
//				else
//				{
//					//copy
//					if (computerName[0]=='\0')
//					{
//						unsigned long numSize = 255;
//						GetComputerName( computerName,  &numSize );
//					}
//					
//					sprintf(buffer, "\\\\????\\Log\\%s-%s", computerName, FileData.name);
//					
//					_chmod( filename, _S_IREAD | _S_IWRITE );
//					rename(filename, buffer);						
//				}
//			}
//			
//			
//			while (_findnext( hFile, &FileData ) == 0);
//			
//			_findclose( hFile );			
//		}
//	}


void
CheckLogFile()
{
	_chdir(g_CWD);

	char filename[256] = { 0, };
	char buffer[256] = { 0, };
	char computerName[256] = { 0, };

	struct _finddata_t	FileData;
	long				hFile;

	_mkdir("Log");

	//-----------------------------------------------------------------
	// *.spk file?? ã?´?.
	//-----------------------------------------------------------------
	if ((hFile = _findfirst("Log\\Log*.txt", &FileData)) != -1L)
	{
		do
		{
			sprintf(filename, "Log\\%s", FileData.name);

			std::ifstream file(filename, std::ios::binary);
			file.seekg(0, std::ios::end);

			long fp = file.tellg();

			if (fp < 39)
			{
				_chmod(filename, _S_IREAD | _S_IWRITE);
				remove(filename);
			}
			else
			{
				file.seekg(-41, std::ios::end);
				file.read((char*)buffer, 24);
				buffer[24] = '\0';
				file.close();

				if (strcmp(buffer, "Delete DebugMessageArray") == 0)
				{
					_chmod(filename, _S_IREAD | _S_IWRITE);
					remove(filename);
				}
				else
				{
					//copy
//						if (computerName[0]=='\0')
//						{
//							unsigned long numSize = 255;
//							GetComputerName( computerName,  &numSize );
//						}
//						
//						sprintf(buffer, "\\\\????\\Log\\%s-%s", computerName, FileData.name);
//						
//						_chmod( filename, _S_IREAD | _S_IWRITE );
//						rename(filename, buffer);						
				}
			}
		}


		while (_findnext(hFile, &FileData) == 0);

		_findclose(hFile);
	}
}

//-----------------------------------------------------------------------------
// Check Flush LogFile
//-----------------------------------------------------------------------------
void
CheckFlushLogFile()
{
	//#ifdef OUTPUT_DEBUG_UPDATE_LOOP
	const DWORD flushDelay = 3 * 60 * 1000;
	static DWORD flushTime = g_CurrentTime + flushDelay;

	if (g_CurrentTime > flushTime)
	{
		if (g_pDebugMessage != NULL)
		{
			char logFile[128];
			strcpy(logFile, g_pDebugMessage->GetFilename());

			if (g_pDebugMessage != NULL)
			{
				DEBUG_ADD("--------------- Delete DebugMessageArray --------------");
				delete g_pDebugMessage;
				g_pDebugMessage = NULL;
			}
			_chmod(logFile, _S_IREAD | _S_IWRITE);
			remove(logFile);

			sprintf(logFile, "%s\\Log\\Log%d.txt", g_CWD, timeGetTime());
			g_pDebugMessage = new CMessageArray;
			g_pDebugMessage->Init(MAX_DEBUGMESSAGE, 256, logFile);

			DEBUG_ADD_FORMAT("[Time = %d]", g_CurrentTime);
		}

		// 3?? ??
		flushTime = g_CurrentTime + flushDelay;
	}
	//#endif
}
#endif

// HHOOK g_hHook = NULL;

//LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
//{
//    BOOL bSysKeyDown = FALSE;
//    BOOL bWinKeyDown = FALSE;
//    
//    if(nCode == HC_ACTION)
//    {
//        KBDLLHOOKSTRUCT* kbhook = (KBDLLHOOKSTRUCT*)lParam;
//
//// ?????? ??????????....
//        if(kbhook->flags & LLKHF_ALTDOWN)
//        {
//            switch(kbhook->vkCode)
//            {
//            case VK_TAB:
//            case VK_F4:
//			case VK_ESCAPE:
//                bSysKeyDown = TRUE;
//                break;
//            }
//        }
//// Control + ESC?? ????
//		else if(((GetAsyncKeyState( VK_CONTROL ) & 0x8000) || g_pDXInput != NULL && (g_pDXInput->KeyDown(DIK_LCONTROL) || g_pDXInput->KeyDown(DIK_RCONTROL))) && kbhook->vkCode == VK_ESCAPE)
//		{
//			SHORT control = GetAsyncKeyState( VK_CONTROL );
//			bSysKeyDown = TRUE;
//		}
//        else
//        {
//            switch(kbhook->vkCode)
//            {
//            case VK_LWIN:
//            case VK_RWIN:
//                bWinKeyDown = TRUE;
//                break;
//            }
//        }
//        
//        if(bSysKeyDown || bWinKeyDown)
//            return 1;
//    }
//
//    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
//}

//----------------------------------------------------------
// ??? ?????? ???/????????.
//----------------------------------------------------------
void InitResolutionConfig()
{
	int		nResolutionX, nResolutionY, nFullScreen/*add by kim*/;
	try
	{
		Properties ResolutionConfig;
		std::string str = g_pFileDef->getProperty("FILE_INFO_RESOLUTION");
		ResolutionConfig.load(str.c_str());

		nResolutionX = ResolutionConfig.getPropertyInt("ResolutionX");
		nResolutionY = ResolutionConfig.getPropertyInt("ResolutionY");
		nFullScreen = ResolutionConfig.getPropertyInt("FullScreen");	//add by kim
	}
	catch (...)	// ?????? ???? ???
	{
		nResolutionX = 1024;
		nResolutionY = 768;
		nFullScreen = 1;	//add by kim
	}

	// VS_UI?? Client ???????? ???? ?????? ????
//	g_pUserInformation->IsResolution1024	= ( nResolutionX == 1024 );
	g_pUserInformation->iResolution_x = nResolutionX;
	g_pUserInformation->iResolution_y = nResolutionY;

	//add by kim
	if (nFullScreen == 1) {
		g_bFullScreen = true;
	}
	else {
		g_bFullScreen = false;
	}
	//end by kim
}

void SaveResolutionConfig()
{
	if (g_pUserOption)
	{
		std::string str = g_pFileDef->getProperty("FILE_INFO_RESOLUTION");
		std::ofstream file(str.c_str());
		if (file.is_open())
		{
			file << "ResolutionX: " << g_pUserInformation->iResolution_x << std::endl;
			file << "ResolutionY: " << g_pUserInformation->iResolution_y << std::endl;
			file << "FullScreen: " << (g_bFullScreen ? "1" : "0") << '\n';	//add by kim
		}
	}
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Initialization, message loop
//-----------------------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if __CONTENTS(__XTRAP)
	//2009 04 21 ??? ????? ????? ??? ???? ?????? ???..
	//http://patch.wiselogic.co.kr/DarkEden
	//660970B478E9CD6790316D9844CFE862EEE63E3F2BAD301E5F3D81C30324E0EBAAE8D9458994D60E58688AACDA8FE61389ECBD25D6B246C09E4B18F747C51F420F7D04245246E403AE73194E9554761FEBE0CB630673E9ADAFB81AF9B7ECAC
	//660970B47809CDE555336D9844CFE86287416167DEC365483208B760E262AA7D84A0660BAA6116039CE2CBB0C332B21FC86DAE63C50560522AD880E5933D746E0F7D04245246E417A4610E5695477E1EF47455B309945CB0D27B7C7D3821396080E71928F0
	//2009 08 21
	//660970B45809CDE5A0326D9844CFE8621829C8F997F0C6CA40D92E728021A5A1AB0A422D91074689A92CF1A105CE004AAACD58C72EAC47EF8121FDC4B33DCE9E0F7D04245246E409A061005FC9527B086EF36EADBEFB841CA33D4BBD4018E4A4EBA410C2A4B5527AA85D
	XTrap_C_Start("660970B45809CDE5A0326D9844CFE8621829C8F997F0C6CA40D92E728021A5A1AB0A422D91074689A92CF1A105CE004AAACD58C72EAC47EF8121FDC4B33DCE9E0F7D04245246E409A061005FC9527B086EF36EADBEFB841CA33D4BBD4018E4A4EBA410C2A4B5527AA85D", NULL);
#endif //__XTRAP
	//	std::string tttt = "NEWSTART ";
	//	tttt += lpCmdLine;
	//	lpCmdLine = (char *)tttt.c_str();

		/*
		CIndexSpritePack ISPK;
		std::ifstream ispkFile("f:\\vcpp\\clientinfo\\Data\\AppendPatch\\New18Creature.ispk", ios::binary);
		ISPK.LoadFromFile(ispkFile);
		ispkFile.close();

		std::ofstream ispkFile2("f:\\vcpp\\clientinfo\\Data\\AppendPatch\\New18Creature.ispk", ios::binary);
		std::ofstream ispkFile3("f:\\vcpp\\clientinfo\\Data\\AppendPatch\\New18Creature.ispki", ios::binary);
		ISPK.SaveToFile(ispkFile2, ispkFile3);
		ispkFile2.close();
		ispkFile3.close();
		*/


		//opfstream testTemp("Data/Test/File.txt", std::ios_base::binary);
		//testTemp.write("9", 1);
		//testTemp.close();

		//CCompressedTempFileIO::flush_temp_file();

#ifdef OUTPUT_DEBUG
	InitializeCriticalSection(&g_Lock);
#endif

	//----------------------------------------------------------
	// Load Package Information
	//----------------------------------------------------------
	iovfs_base::start_vfs("data/darkeden", O_RDONLY);

	//----------------------------------------------------------
	// Load Package Path Information
	//----------------------------------------------------------
	g_pFileDef = new Properties;
	g_pFileDef->load(FILE_INFO_FILEDEF);

	//----------------------------------------------------------
	// Initialize User Information
	//----------------------------------------------------------
	if (g_pUserInformation == NULL)
		g_pUserInformation = new UserInformation;


	//----------------------------------------------------------
	// Load Version Information
	//----------------------------------------------------------
	int version = 0;
	ivfstream versionFile;
	if (FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_VERSION").c_str(), versionFile))
	{
		versionFile.read((char*)&version, 4);
		versionFile.close();
	}

	g_pUserInformation->GameVersion = version;


#ifdef __USE_CRASH_REPORT
	//----------------------------------------------------------
	// Crash Report
	//----------------------------------------------------------
#ifdef	__BUGTRAP
	if (CrashReport::LoadOptionFile(g_pFileDef->getProperty("FILE_INFO_CRASH_REPORT").c_str()))
	{
		CrashReport::SetAppVersion(g_pUserInformation->GameVersion);
		CrashReport::Install();
	}
#endif //__BUGTRAP
#endif

	//----------------------------------------------------------
	// Initialize Resolution Configuration
	//----------------------------------------------------------
	InitResolutionConfig();

	//----------------------------------------------------------
	// Only allow a single application instance to run
	//----------------------------------------------------------
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = FALSE;

#ifndef OUTPUT_DEBUG
	HANDLE hMutex = CreateMutex(&sa, FALSE, "<<<DarkEden>>>");

	/*
		if (GetLastError()==ERROR_ALREADY_EXISTS)
		{
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage!=NULL)
				{
					DEBUG_ADD("DarkEden is Already Running...");
					DEBUG_ADD("--------------- Delete DebugMessageArray --------------");
					delete g_pDebugMessage;
					g_pDebugMessage = NULL;
				}
			#endif

			ReleaseMutex( hMutex );

			#ifdef OUTPUT_DEBUG
				DeleteCriticalSection(&g_Lock);
			#endif

			#ifndef _DEBUG
				return -1;
			#endif
		}


		if( FindWindow( "DarkEden", "DarkEden" ) != NULL )
		{
			return -1;
		}
		*/
#endif

	//???? directory?? ????????.
	//strcpy(g_CWD, __argv[0]);
	GetModuleFileName(NULL, g_CWD, _MAX_PATH);
	char* tempCut = strrchr(g_CWD, '\\');
	if (tempCut == NULL)
		return FALSE;

	*tempCut = '\0';
	//GetCurrentDirectory( _MAX_PATH, g_CWD );
	SetCurrentDirectory(g_CWD);

	// 	//	// ????? updater????????? ???????..
	//	if (_access(UPDATER_NEW_FILENAME, 0) == 0/* && _access(UPDATER_FILENAME, 0)*/)//updaterNewFile)
	//	{	
	//		// ???? Patcher?? ?????..
	//		if (remove( UPDATER_FILENAME )==0)
	//		{
	//			// ?????? ??????? rename
	//			if (rename( UPDATER_NEW_FILENAME, UPDATER_FILENAME )==0)
	//			{
	//				DEBUG_ADD("Update Updater.exe OK"); 
	//			}
	//		}
	//		// ???? updater?? ?????..
	//		//remove( UPDATER_FILENAME );
	//		// ?????? ??????? rename
	//		if (rename( UPDATER_NEW_FILENAME, UPDATER_FILENAME )==0)
	//		{
	//			DEBUG_ADD("Update Updater.exe OK"); 
	//		}
	//	}	

#ifdef __METROTECH_TEST__
	CheckLogFile();
#endif


	/*
#include "packet\ServerSocket.h"

	// ?? Client?? ???ÿ? ??? ?? Client?? ??????.
	// ?????????? resource(????, profile...)?? ????? ???
	//		ResourceQueue?? ???????? ???? ????? ???.
	// while(1)????? ??? thread?? ??????.
	// RequestManager ????????? mutex?????? ?????.
	// RequestManager?? Update()?? main thread???? ???.
	//
	ServerSocket* pServerSocket = new ServerSocket( 9650 );

	char strClient[256];
	uint port;

	while (1)
	{
		Socket* pSocket = pServerSocket->accept();

		// request?? ???
		RequestServerPlayer* pRequestServerPlayer = new RequestServerPlayer( pSocket );
		g_pRequestManager->AddPlayer( pRequestServerPlayer );

		// g_pRequestManager?? ???? RequestServerPlayer?? ????? processInput/Command/Output ó??

		strcpy(strClient, pSocket->getHost().c_str());
		port = pSocket->getPort();
	}
	*/

	/*
	std::ifstream file("ImageObject.spk", ios::binary);
	std::ofstream file2("ImageObject-2.spk", ios::binary);
	std::ofstream file2index("ImageObject-2.spki", ios::binary);
	CSpritePack SPK;
	SPK.LoadFromFile(file);
	SPK.SaveToFile(file2, file2index);
	file.close();
	file2.close();
	file2index.close();

	return 0;
	*/

	/*
	OSVERSIONINFO        osVer;

	// First get the windows platform
	osVer.dwOSVersionInfoSize = sizeof(osVer);

	if( !GetVersionEx( &osVer ) )
	{
		return 0;
	}

	if (osVer.dwPlatformId == VER_PLATFORM_WIN32_NT )
	{
		g_WindowsNT = TRUE;
	}
	else
	{
		g_WindowsNT = FALSE;
	}
	*/

	//OutputMemorySize();

	/*
	std::ifstream file("f:\\vcpp\\clientexpo\\data\\image\\creatureshadow.cfpk", ios::binary);
	CCreatureFramePack CFPK;
	CFPK.LoadFromFile(file);
	file.close();

	CCreatureFramePack CFPK2;
	CFPK2.Init( CFPK.GetSize()-3 );

	for (int i=0; i<CFPK2.GetSize(); i++)
	{
		CFPK2[i] = CFPK[i];
	}

	std::ofstream file2("f:\\CreatureShadow.cfpk", ios::binary);
	std::ofstream fileindex2("f:\\CreatureShadow.cfpki", ios::binary);
	CFPK2.SaveToFile(file2, fileindex2);
	file2.close();
	fileindex2.close();
	*/

	//-----------------------------------------------------------------------
	// Starting Client
	//-----------------------------------------------------------------------
	g_bNeedUpdate = FALSE;
	//OutPutClassSize();

#ifdef OUTPUT_DEBUG

	OutPutClassSize();
	if (g_pDebugMessage != NULL)
	{
		delete g_pDebugMessage;
	}
	g_pDebugMessage = new CMessageArray;

	//---------------------------------------------------
	// Debug Log File Init...
	//---------------------------------------------------
	if (g_pDebugMessage != NULL)
	{
		char logFile[128];
		sprintf(logFile, "%s\\Log\\Log%d.txt", g_CWD, timeGetTime());

		//#include <fcntl.h>
		//char clogFile[128];
		//sprintf(clogFile, "%s\\Data\\UI\\txt\\Logc%d.txt", g_CWD, timeGetTime());			
		//CLogFile = _open(clogFile, _O_WRONLY | _O_TEXT | _O_CREAT | _O_TRUNC);


		g_pDebugMessage->Init(MAX_DEBUGMESSAGE, 256, logFile);

		DEBUG_ADD_FORMAT("[ Compile Time : %s ]", __TIMESTAMP__);
	}
#endif

	//g_MemLogFile = _open("memlog.txt", _O_WRONLY | _O_TEXT | _O_CREAT | _O_TRUNC);

#ifdef _DEBUG
	int tmpDbgFlag;
	tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	//_CrtSetDbgFlag(tmpDbgFlag);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | tmpDbgFlag);


	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
#endif	


	g_hInstance = hInstance;
	// random
	srand(time(NULL));

	//---------------------------------------------------
	// SpritePack Loading Test
	//---------------------------------------------------
	/*
	CSpritePack tileSPK;
	std::ifstream	fileSPK;//(FILE_ISPRITE_ADDON, ios::binary);
	if (!FileOpenBinary(FILE_SPRITE_TILE, fileSPK))
		return false;
	tileSPK.LoadFromFile(fileSPK);
	fileSPK.close();
	*/

	bool bNetmarble = false;
	bool bNetmarbleLogin = false;
	Properties NetmarbleConfig;
	try
	{
		NetmarbleConfig.load(g_pFileDef->getProperty("FILE_INFO_NETMARBLE").c_str());
		bNetmarble = NetmarbleConfig.getPropertyInt("Netmarble") != 0;
	}
	catch (...)
	{
		bNetmarble = false;
	}
	try
	{
		bNetmarbleLogin = NetmarbleConfig.getPropertyInt("NetmarbleLogin") != 0;
	}
	catch (...)
	{
		bNetmarbleLogin = bNetmarble;
	}

#ifdef 	__DESIGNED_JAPAN
	//??? ??????? ???? ????.
	bool bNetmarbleJapan = false;
	try
	{
		// ????? ????? ???? ????
		bNetmarbleJapan = NetmarbleConfig.getPropertyInt("NetmarbleJapan") != 0;
	}
	catch (...)	// ?????? ????? NetmarbleLogin?? ??????? ????? ???
	{
		bNetmarbleJapan = false;	// ??????? ???? 
	}
#endif

	if (bNetmarble)
	{
		// -------------------------------------------------
		// Read registry
		// -------------------------------------------------
		HKEY newKey = 0;
		LONG ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Netmarble\\NetmarbleDarkEden", NULL, KEY_ALL_ACCESS, &newKey);
		DWORD dwSize = MAX_PATH;
		char filepath[MAX_PATH];

		if (ret == ERROR_SUCCESS)
		{
			RegQueryValueEx(newKey, "RunFileName", NULL, NULL, (unsigned char*)filepath, &dwSize);

			char* pFilename = strstr(filepath, "DarkEden.exe");
			if (pFilename != NULL)
			{
				strcpy(pFilename, "Updater.exe");
				RegSetValueEx(newKey, "RunFileName", NULL, REG_SZ,
					(unsigned char*)&filepath, strlen(filepath));
			}
		}
		RegCloseKey(newKey);
	}

	//MessageBox(g_hWnd, lpCmdLine, NULL, MB_OK);

	//------------------------------------------------------
	// If the server IP is not set ? run the launcher
	//------------------------------------------------------

	if (strlen(lpCmdLine) == 0)
	{
#if defined(USE_UPDATER_1)

#ifndef OUTPUT_DEBUG
		if (!ReleaseMutex(hMutex))
		{
			DEBUG_ADD_FORMAT("Failed to release mutex : %d", GetLastError());
		}
#endif

#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage != NULL)
		{
			DEBUG_ADD("No CommandLine --> Execute Updater.exe");
			DEBUG_ADD("--------------- Delete DebugMessageArray --------------");
			delete g_pDebugMessage;
			g_pDebugMessage = NULL;
		}
#endif



		ReleaseAllObjects();


#ifdef OUTPUT_DEBUG
		DeleteCriticalSection(&g_Lock);
#endif
		//_spawnl(_P_NOWAIT, "Updater.exe", "Updater.exe", NULL);
		_chdir(g_CWD);
		_spawnl(_P_OVERLAY, UPDATER_FILENAME, UPDATER_FILENAME, lpCmdLine, NULL);
		//ShellExecute(g_hWnd, NULL, UPDATER_FILENAME, lpCmdLine, NULL, SW_SHOW);
		return FALSE;
#else

		//strcpy(g_ServerIP, SERVER_IP);
		g_MaxNPC = 0;//MAX_NPC;

		//g_bFullScreen	= true;	//by kim 2021-08-14 ??
		g_bHAL = true;
		g_bMusicSW = true;

#endif
	}
	//------------------------------------------------------
	// If the Server IP is set ? Run the Client
	//------------------------------------------------------
	else
	{
		char* str = lpCmdLine;

		if (strlen(str) < 5)
		{
#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage != NULL)
			{
				DEBUG_ADD("Too short Commandline --> Run Updater.exe");
				DEBUG_ADD("--------------- Delete DebugMessageArray --------------");
				delete g_pDebugMessage;
				g_pDebugMessage = NULL;
			}
#endif

#ifndef OUTPUT_DEBUG
			ReleaseMutex(hMutex);
#endif

			ReleaseAllObjects();


#ifdef OUTPUT_DEBUG
			DeleteCriticalSection(&g_Lock);
#endif

			//_spawnl(_P_NOWAIT, "Updater.exe", "Updater.exe", NULL);	
			_chdir(g_CWD);
			_spawnl(_P_OVERLAY, UPDATER_FILENAME, UPDATER_FILENAME, lpCmdLine, NULL);
			//			ShellExecute(g_hWnd, NULL, UPDATER_FILENAME, lpCmdLine, NULL, SW_SHOW);

			return FALSE;
		}

		bool bCheck = true;
		bool bRunUpdater = false;
		char checkStr[9] = "NEWSTART";
		//char checkStr[9] = "START";

		int i = 0;
#ifdef OUTPUT_DEBUG
		bRunUpdater = false;
#else
		for (i = 0; i < strlen(checkStr); i++)
		{
			if (checkStr[i] != str[i])
			{
				bRunUpdater = true;

				break;
			}
		}
		if (bRunUpdater == false && !bNetmarble && lpCmdLine[8] >= '0' && lpCmdLine[8] <= '9')
		{
			for (int i = 9; ; i++)
			{
				//g_Dimension = lpCmdLine[8]-'0';
				if (lpCmdLine[i] == NULL)
					break;

				if (lpCmdLine[i] >= '0' && lpCmdLine[i] <= '9')
				{
					continue;
				}
				else
					break;
			}
			char szDimen[10];
			memset(szDimen, 0, 10);
			memcpy(szDimen, lpCmdLine + 8, i - 8);
			g_Dimension = atoi(szDimen);

			//	g_Dimension = lpCmdLine[8]-'0';
		}
#endif

#ifdef OUTPUT_DEBUG
		// â??? ????..
		g_bTestMode = true;
		char checkTestMode[] = "TestMode";
		for (i = 0; i < strlen(checkTestMode); i++)
		{
			if (checkTestMode[i] != str[i])
			{
				g_bTestMode = false;

				break;
			}
		}

		if (g_bTestMode)
		{
			bRunUpdater = false;
		}
#endif

		if (bRunUpdater)
		{
#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage != NULL)
			{
				DEBUG_ADD("Wrong Commandline --> Run Updater.exe");
				DEBUG_ADD("--------------- Delete DebugMessageArray --------------");
				delete g_pDebugMessage;
				g_pDebugMessage = NULL;
			}
#endif			

#ifndef OUTPUT_DEBUG
			ReleaseMutex(hMutex);
#endif

			ReleaseAllObjects();

			//bCheck = false;

#ifdef OUTPUT_DEBUG
			DeleteCriticalSection(&g_Lock);
#endif

			//_spawnl(_P_NOWAIT, "Updater.exe", "Updater.exe", NULL);	
			_chdir(g_CWD);

			// ????
			// [Futec????]
//			char szTemp[512];
//			sprintf(szTemp, "%s %s", UPDATER_FILENAME, lpCmdLine);
//			DWORD error = WinExec(szTemp, SW_SHOW);
//			switch(error)
//			{
//			case 0:
//				MessageBox(NULL, "The system is out of memory or resources. ", PROGRAM_TITLE, MB_OK);
//				break;
//
//			case ERROR_BAD_FORMAT:
//				MessageBox(NULL, "The .exe file is invalid (non-Win32 .exe or error in .exe image). ", PROGRAM_TITLE, MB_OK);
//				break;
//
//			case ERROR_FILE_NOT_FOUND:
//				MessageBox(NULL, "The specified file was not found. ", PROGRAM_TITLE, MB_OK);
//				break;
//
//			case ERROR_PATH_NOT_FOUND:
//				MessageBox(NULL, "The specified path was not found. ", PROGRAM_TITLE, MB_OK);
//				break;
//			}

			_spawnl(_P_OVERLAY, UPDATER_FILENAME, UPDATER_FILENAME, lpCmdLine, NULL);
			//ShellExecute(g_hWnd, NULL, UPDATER_FILENAME, lpCmdLine, NULL, SW_SHOW);

			return FALSE;
		}

		//g_bFullScreen	= true;	by kim 2021-08-14 ??

		//strcpy(g_ServerIP, SERVER_IP);
		g_MaxNPC = 0;//MAX_NPC;

		g_bHAL = true;
		g_bMusicSW = true;
	}

	// Futec Settings
	GetFutecAddress(lpCmdLine);

	//------------------------------------------------------------------------
	// ???????? Patch 
	// ????? ?????? ??? ??? ?????... - -;
	//------------------------------------------------------------------------
	//bool bPatched = ApplyPatch();

	//------------------------------------------------------------------------
	// ScreenEffect ????
	//------------------------------------------------------------------------
	//ConvertScreenEffect();

	//------------------------------------------------------------------------
	// ???????? EffectScreen?? Append??? SPK?? 
	// ?? ???????? Append??? ???.
	// CheckTerriblePatch?? ???? ??? ???. - -;;
	//------------------------------------------------------------------------
	//AppendScreenEffect();

	if (!CheckTerriblePatch())
	{
		ReleaseAllObjects();

#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage != NULL)
		{
			delete g_pDebugMessage;
			g_pDebugMessage = NULL;
		}

		ReleaseMutex(hMutex);
		DeleteCriticalSection(&g_Lock);
#endif

		return 0;
	}


	//----------------------------------------------------------------
	// Start the updater
	//----------------------------------------------------------------
	//std::ifstream updaterNewFile(UPDATER_NEW_FILENAME, ios::binary | ios::nocreate);

	// If a new updater exe exists, replace it
	if (!_access(UPDATER_NEW_FILENAME, 0))
	{
		//updaterNewFile.close();

		// Delete previous updater
		if (remove(UPDATER_FILENAME) == 0)
		{
			// Rename the new one to the old one
			if (rename(UPDATER_NEW_FILENAME, UPDATER_FILENAME) == 0)
			{
				DEBUG_ADD("Update Updater.exe OK");
			}
		}
	}

	//strcpy(g_ServerIP, SERVER_IP);
	//---------------------------------------------------
	// Delete the update directory
	//---------------------------------------------------
	// It should be deleted in the updater
	//---------------------------------------------------
	char CWD[_MAX_PATH];
	if (_getcwd(CWD, _MAX_PATH) != NULL)
	{
		char UpdateDir[_MAX_PATH];

		int lenCWD = strlen(CWD);
		if (lenCWD > 1)
		{
			if (CWD[lenCWD - 1] == '\\')
			{
				sprintf(UpdateDir, "%s%s", CWD, DIRECTORY_UPDATE);
			}
			else
			{
				sprintf(UpdateDir, "%s\\%s", CWD, DIRECTORY_UPDATE);
			}
		}

		if (_rmdir(UpdateDir) != 0)
		{
			// PATH?? ????? ???
			if (errno == ENOENT)
			{
			}
			// ???? ??? ?? ?????? ???..		
			else //if (errno==ENOTEMPTY)
			{
				// ???? directory?? ???????.				
				if (_chdir(UpdateDir) == 0)
				{
					//---------------------------------------------------
					// file???????? ???????. T_T;
					//---------------------------------------------------
					struct _finddata_t	FileData;
					long				hFile;

					// ??? ????? ???´?.
					if ((hFile = _findfirst("*.*", &FileData)) != -1L)
					{
						while (_findnext(hFile, &FileData) == 0)
						{
							// .???? ??????? ?? ???? ??? ????..
							if (FileData.name[0] != '.')
							{
								remove(FileData.name);
							}
						}

						// ??
						_findclose(hFile);
					}

					_chdir(CWD);

					if (_rmdir(UpdateDir) == 0)
					{
						// ?? ????????.
					}
				}
			}
		}
	}

	RemoveProgressBar();

	//-----------------------------------------------------------------
	// Print packet contents
	//-----------------------------------------------------------------
	//if (bPatched)
	//{
	//	ShowPatchLogWindow();
	//}	


	BOOL bBadTimer = FALSE;
	MSG msg;
	NETMARBLE_INFO NetmarbleInfo;
	REALSERVER_INFO RealServerInfo;

	if (bNetmarble && bNetmarbleLogin)
	{
		if (ParsingNetmarble(lpCmdLine, NetmarbleInfo) == false)
		{
			if (NetmarbleConfig.getPropertyInt("Netmarble") == 1)
			{
				MessageBox(NULL, "The NetMarble darkEden can only be run through the NetMarble homepage.", PROGRAM_TITLE, MB_OK);
				return -1;
			}

			bNetmarble = false;
		}
	}
	else
	{
		//test  mode|demention|ID|key
		//char szBuf[1024]; 
		//sprintf(szBuf, "%s", lpCmdLine); 

		if (ParsingRealServer(lpCmdLine, g_Dimension, RealServerInfo) == false)
		{
			//#ifndef OUTPUT_DEBUG
				//MessageBox(NULL, "?? ?????? ???? ??? ????????ñ? ??????.", PROGRAM_TITLE, MB_OK);
				//ShellExecute(NULL, NULL, "www.darkeden.com", NULL, NULL, SW_SHOW);
				//return -1;
			//#endif
		}
	}
	
	// Store Netmarble Information in User Information
	g_pUserInformation->IsNetmarble = bNetmarble;
	g_pUserInformation->IsNetmarbleLogin = bNetmarbleLogin;

	bool bTestServer = false;
	Properties TestServerConfig;
	try
	{

		TestServerConfig.load(g_pFileDef->getProperty("FILE_INFO_TESTSERVER").c_str());
		bTestServer = TestServerConfig.getPropertyInt("TestServer") != 0;
	}
	catch (...) {}

	/*	FILE* fp = fopen("Data\\Info\\SuperUser.inf", "rt");
	//	MessageBox(NULL,__TIME__,__TIME__,MB_OK);
	//	if(fp != NULL)
	//	{
	//		char szLine[512];
	//		fgets(szLine,512,fp);
	//		char szCompare[512];
	//		bool	superUser = true;
	//		wsprintf(szCompare,"%d%s",__LINE__,__TIME__);
	//		MessageBox(NULL,szCompare,szCompare,MB_OK);
	//		if(strcmp(szLine,szCompare))
	//			superUser = false;
	//		fgets(szLine,512,fp);
	//		fclose(fp);
	//
	//		int Code=0;
	//		char *tempCode = new char[strlen(szCompare)];
	//		memset(tempCode, 0, strlen(szCompare) );
	//		for(int i=0;i<strlen(szCompare);i++)
	//		{
	//			if( i != 0 )
	//				tempCode[i] = szCompare[1] + szCompare[i];
	//			else
	//				tempCode[i] = szCompare[0] + szCompare[i];
	//		}
	//		MessageBox(NULL, tempCode, tempCode, MB_OK);
	//		if(strcmp(tempCode,szLine))
	//			superUser = false;
	//		delete []tempCode;
	//
	//		std::string myIP;
	//
	//		WORD wVersionRequested;
	//		WSADATA wsaData;
	//		char name[255];
	//		PHOSTENT hostinfo;
	//		wVersionRequested = MAKEWORD( 2, 0 );
	//		if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	//		{
	//			if( gethostname ( name, sizeof(name)) == 0)
	//			{
	//				if((hostinfo = gethostbyname(name)) != NULL)
	//					myIP= inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
	//				else
	//					superUser = false;
	//			} else superUser = false;
	//			WSACleanup( );
	//		} else
	//			superUser = false;
	//		if(strstr(myIP.c_str(),"220.117.154")==NULL)
	//			superUser = false;
	//
	//		MessageBox(NULL, myIP.c_str(), myIP.c_str(), MB_OK);
	//		if(superUser)
	//		{
	//			g_bSuperUser = true;
	//		} else
	//			g_bSuperUser = false;
	//	} */

	DARKEDEN_LANGUAGE Language = CheckDarkEdenLanguage();

	switch (Language)
	{
	case DARKEDEN_CHINESE:
		gC_ci = new CI_CHINESE;
		break;
	case DARKEDEN_JAPANESE:
	{
		gC_ci = new CI_JAPAN;
		break;
	}
	case DARKEDEN_ENGLISH:
		gC_ci = new CI_ENGLISH;
		break;
	default:
		gC_ci = new CI_KOREAN;
		break;
	}

	// BugTrap???? ??ü
	// #ifndef _DEBUG
	// 	if( gC_ci->IsKorean() == true )
	// 		InitCrashReport();
	// #endif

	if (InitApp(nCmdShow))
	{
#if __CONTENTS(__XTRAP)
		XTrap_C_KeepAlive();
#endif //__XTRAP
		DDSCAPS2 ddsCaps2;
		DWORD dwTotal;
		DWORD dwFree;
		ZeroMemory(&ddsCaps2, sizeof(ddsCaps2));
		ddsCaps2.dwCaps = DDSCAPS_VIDEOMEMORY;//DDSCAPS_TEXTURE; 
		HRESULT hr = CDirectDraw::GetDD()->GetAvailableVidMem(&ddsCaps2, &dwTotal, &dwFree);

		DDCAPS	driverCaps;
		ZeroMemory(&driverCaps, sizeof(driverCaps));
		driverCaps.dwSize = sizeof(driverCaps);

		hr = CDirectDraw::GetDD()->GetCaps(&driverCaps, NULL);

		g_dwVideoMemory = driverCaps.dwVidMemTotal;
		g_dwVideoMemory = driverCaps.dwVidMemFree;

		// For NetMarble use
		if (bNetmarble)
		{
			g_pUserInformation->NetmarbleID = NetmarbleInfo.ID;
			g_pUserInformation->NetmarblePassword = NetmarbleInfo.Password;
			g_pUserInformation->WorldID = NetmarbleInfo.WorldID;
			g_pUserInformation->ServerID = NetmarbleInfo.ServerID;
			//g_pUserInformation->GoreLevel = NetmarbleInfo.bGore;
			//g_pUserInformation->bNetmarbleGoreLevel = NetmarbleInfo.bGore;

#ifdef __DESIGNED_JAPAN
			g_pUserInformation->IsNetmarbleJapan = bNetmarbleJapan;
#endif

		}
		else
		{
			// mode|demention|ID|key
			g_pUserInformation->IsAutoLogIn = RealServerInfo.bMode;
			if (true == g_pUserInformation->IsAutoLogIn)
			{
				g_pUserInformation->UserID = RealServerInfo.ID;
				g_pUserInformation->AutoLogInKeyValue = RealServerInfo.Key;

				g_Dimension = RealServerInfo.WorldID;

#ifdef OUTPUT_DEBUG
				char szBuf[1024];
				sprintf(szBuf, "mode = %d, id = %d,world = %s,key = %s", g_pUserInformation->IsAutoLogIn,


					g_Dimension,


					g_pUserInformation->UserID.GetString(),


					g_pUserInformation->AutoLogInKeyValue.GetString());
				DEBUG_ADD(szBuf);
#endif
			}


		}

		if (gC_ci->IsKorean())
			g_pUserInformation->SetKorean();
		else if (gC_ci->IsChinese())
			g_pUserInformation->SetChinese();
		else if (gC_ci->IsJapanese())
			g_pUserInformation->SetJapanese();
		else if (gC_ci->IsEnglish())
			g_pUserInformation->SetEnglish();

		//#if !defined(OUTPUT_DEBUG) && !defined(__DEBUG_OUTPUT__)
		//g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)KeyboardHook, hInstance, 0);

		//SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, TRUE, NULL, NULL); 
		//#endif

		//static DWORD lastTime=1;
		//------------------------------
		// ???? ???? ??????? ???????.
		//------------------------------
		if (!g_pTopView->IsInit())
		{
			g_pTopView->Init();

		}

		g_bActiveApp = TRUE;
		//g_bActiveGame = TRUE;
		DEBUG_CMD(MIN_CLRSCR, "????");
		DEBUG_CMD(MIN_SHOWWND, "------------------------------");

		int iGameRunTime = 0;
		int	iGameBreakTime = 0;

		DWORD dwthread = 0;
#if __CONTENTS(__XTRAP)
		CreateThread(NULL, 0, XTrap_Check_Alive, NULL, 0, &dwthread);
#endif //__XTRAP

		// Sleep() has ~15.6ms granularity at the default timer resolution,
		// which is coarser than one frame. Ask for 1ms while we are running.
		timeBeginPeriod(1);
		FrameLimiterInit();

		while (TRUE)
		{

			g_bActiveGame = TRUE;

			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (!GetMessage(&msg, NULL, 0, 0))
					break;
				//return msg.wParam;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else if (g_bActiveApp
#ifdef OUTPUT_DEBUG
				|| g_bTestMode
#endif
				)
			{
				// Hold the frame here, not around the message pump above:
				// throttling message dispatch would add input lag.
				FrameLimiterWait();

#ifdef OUTPUT_DEBUG
				//	DEBUG_ADD("u-");
#endif
//if ( )
				{
					//UpdateFrame();

					// timer
					g_CurrentTime = timeGetTime();

					//if (g_CurrentTime - lastTime > g_UpdateDelay)
					{
						// CDirectDraw?? ????????? ???? ????? return
						//if (g_bActiveApp)// && CDirectDraw::IsActive())
						if (g_pUpdate != NULL)
						{
							// ?????.. ????.. --;;
							CWinUpdate* pCurrentUpdate = g_pUpdate;

							pCurrentUpdate->Update();

#ifdef __METROTECH_TEST__
							CheckFlushLogFile();
#endif

						}

						//lastTime = g_CurrentTime;
					}
#ifdef __NPROTECT__
#ifndef __DESIGNED_INTERNATION
					//20080902 ??ð? ü? ????? ????? ???? ???? ???? closeNPROTECT?? ??? ???? ????.
#if __CONTENTS(__NPROTECT)
					if (CheckNPROTECT() != NPROTECT_OK)
					{
						g_nProtectSTATUS = NPROTECT_CHECK_ERROR;
						break;
					}
#endif //__NPROTECT
#endif //__DESIGNED_INTERNATION
					if (g_nProtectSTATUS != NPROTECT_NORMAL)
					{
						bBadTimer = TRUE;
						break;
					}
#endif

					if (g_bForceExitBynProtect)
					{
						bBadTimer = TRUE;
						break;
					}

					//#ifdef OUTPUT_DEBUG
					DWORD timeGap = g_CurrentTime - g_StartTime;

					if (timeGap > 1000)
					{
						//UpdateFrame();

						g_FrameRate = (g_FrameCount - g_StartFrameCount) * 1000 / timeGap;

						// 15 fps ???
						g_bGoodFPS = (g_FrameRate >= g_FrameGood);

						g_StartTime = g_CurrentTime;
						g_StartFrameCount = g_FrameCount;
					}
					//#endif

/*
					//--------------------------------------------------
					// ?????????? timer?? ü???? ?????..
					//--------------------------------------------------
					const int checkSecond = 3;
					const int checkMillisecond = 3000;
					const int checkHackMillisecond = 5000;

					static int badTimes = -1;
					static DWORD lastTime = g_CurrentTime;
					static DWORD	lastHackTime = 0;
					//static int	lastSecond = 0;

					//--------------------------------------------------
					// SpeedHack ü?
					//--------------------------------------------------
					if (g_CurrentTime - lastHackTime > checkHackMillisecond)	// 5?????
					{
						static int checker = 0;

						if (++checker & 0x01)
//						{
							// ??????? Spy++?? ????.. WndClass?? ?????.
							if (FindWindow("#32770", "??????? Ver 1.0 ")!=NULL)
							{
								// ?? -_-;
								bBadTimer = TRUE;

								DEBUG_ADD("Find Speeder3!!!!");

								break;
							}
//						}
						else
//						{
							// ??????? Spy++?? ????.. WndClass?? ?????.
							if (FindWindow("#32770", "Brothers Speeder")!=NULL)
							{
								// ?? -_-;
								bBadTimer = TRUE;

								DEBUG_ADD("Find Speeder!!!!");

								break;
							}
//						}
						else
//						{
							// ??????? Spy++?? ????.. WndClass?? ?????.
							if (FindWindow("#32770", "????????")!=NULL)
							{
								// ?? -_-;
								bBadTimer = TRUE;

								DEBUG_ADD("Find Speeder4!!!!");

								break;
							}
//						}
						else
//						{
							// ??????? Spy++?? ????.. WndClass?? ?????.
							if (FindWindow("TApplication", "Macro Express 2000")!=NULL)
							{
								// ?? -_-;
								bBadTimer = TRUE;

								DEBUG_ADD("Find Macro Express!!!!");

								break;
							}
//						}

						lastHackTime = g_CurrentTime;
					}

					//--------------------------------------------------
					// timer?? 3??? ???µ?.. ?ð??? 3??? ?????
					//--------------------------------------------------
					///*
					if (g_CurrentTime - lastTime > checkMillisecond)	// 3?????
					{
						SYSTEMTIME st;
						GetLocalTime( &st );
						static WORD lastSecond = st.wSecond;

						int elapsedSecond;
						if (st.wSecond >= lastSecond)
						{
							elapsedSecond = st.wSecond - lastSecond;
						}
						else
						{
							elapsedSecond = st.wSecond + 60 - lastSecond;
						}

						// ?ð??? 3??? ???????..
						if (elapsedSecond < checkSecond)
						{
							// ????..
							if (++badTimes > 5)
							{
								// ?? -_-;
								bBadTimer = TRUE;

								DEBUG_ADD("Bad Timer!!!!");

								break;
							}
						}
						else
						{
							badTimes = 0;
						}

						lastSecond = st.wSecond;
						lastTime = g_CurrentTime;
					}
					//*/
				}

#ifdef OUTPUT_DEBUG
				//	DEBUG_ADD("-u");
#endif
			}
			else
			{
				// Make sure we go to sleep if we have nothing else to do
				WaitMessage();
			}
		}

		timeEndPeriod(1);
#ifndef __OUTPUT_DEBUG__
		SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, FALSE, NULL, NULL);
#endif
	}
	else
	{
		//	InitFail("Initialize Failed!");        
	}

	//-----------------------------------------------------------------------------
	// When terminating due to timer error/timeout.
	//-----------------------------------------------------------------------------
	if (bBadTimer)
	{
		if (g_pUIDialog != NULL)
		{
#if defined(__NPROTECT_OLD_VERSION__)&&defined(__NPROTECT__)

			if (g_nProtectSTATUS != NPROTECT_NORMAL && g_nProtectSTATUS != NPROTECT_MAX)
			{
				g_pUIDialog->PopupFreeMessageDlg(g_nProtectMessage[g_nProtectSTATUS].c_str());
			}
			else
				g_pUIDialog->PopupFreeMessageDlg("?????? ????????? ????? ????????? ???????. ??????? ??? ????ð?, ?????????? ???? ?????? ??µ? ????? ?????? ?? ??????? bug@darkeden.com???? ?????? ?????????.", -1, -1, 0);
#endif

#if defined(__NPROTECT__)&&!defined(__NPROTECT_OLD_VERSION__)
			if (g_bForceExitBynProtect)
			{
				if (g_nProtectMessage.find(g_nProtectErrorMessage) != g_nProtectMessage.end())
				{
					char szTemp[256];
					wsprintf(szTemp, "%s [%d]", g_nProtectMessage[g_nProtectErrorMessage].c_str(), g_nProtectErrorMessage2);
					g_pUIDialog->PopupFreeMessageDlg(szTemp);
				}
				else
				{
					char szTemp[256];
					wsprintf(szTemp, "nProtect?? ?? ?? ???? ???? ???????[%d][%d]????. ????????? ????????.", g_nProtectErrorMessage, g_nProtectErrorMessage2);
					g_pUIDialog->PopupFreeMessageDlg(szTemp);
				}
			}
#endif

			//			if(g_bForceExitBynProtect2)
			//			{
			//				g_pUIDialog->PopupFreeMessageDlg( "nProtect ???? ???? ???? ?????? ?????????. ?????? ???????? ???????? ?????? ??????ñ? ??????.", -1, -1, 0 );
			//			}else
			//			{
			//				if(g_bForceExitBynProtect)
			//					g_pUIDialog->PopupFreeMessageDlg( "??????? ?? ??? ????? ???? ????????? ???????. ??????? ??? ????ð?, ?????????? ???? ?????? ??µ? ????? ?????? ?? ???????, bug@darkeden.com ???? ?????? ?????????.", -1, -1, 0 );
			//				else
			//					g_pUIDialog->PopupFreeMessageDlg( "?????? ????????? ????? ????????? ???????. ??????? ??? ????ð?, ?????????? ???? ?????? ??µ? ????? ?????? ?? ??????? bug@darkeden.com???? ?????? ?????????.", -1, -1, 0 );
			//			}
			//			//MessageBox(NULL, "Timer Error!", PROGRAM_TITLE, MB_OK | MB_TOPMOST);

			while (1)
			{
				UpdateInput();
				UpdateMouse();

				gC_vs_ui.Show();

				POINT point = { 0, 0 };
				RECT rect = { 0, 0, SURFACE_WIDTH, SURFACE_HEIGHT };

				g_pBack->BltNoColorkey(&point, g_pLast, &rect);
				CDirectDraw::Flip();

				if (g_pDXInput->KeyDown(DIK_ESCAPE)
					|| g_pDXInput->KeyDown(DIK_NUMPADENTER)
					|| g_pDXInput->KeyDown(DIK_RETURN)
					|| g_pDXInput->KeyDown(DIK_SPACE))
				{
					break;
				}
			}
		}
	}

	// Save resolution configuration
	SaveResolutionConfig();

	//-----------------------------------------------------------------------------
	// Remove all objects
	//-----------------------------------------------------------------------------	
	ReleaseAllObjects();
#ifdef __WEB_BROWSER__
	if (NULL != g_pWebBrowser)
	{
		g_pWebBrowser->Quit();
		g_pWebBrowser->Release();
		DeleteObject(g_pWebBrowser);
		g_pWebBrowser = NULL;
		CoUninitialize();
	}
#endif
	//#if defined(OUTPUT_DEBUG) && !defined(_DEBUG)
	delete gC_ci;
#ifdef OUTPUT_DEBUG
	//	_close(CLogFile);
	//	CheckCLogFile();
#endif

	// Restore Resolution
	ChangeDisplaySettings(NULL, 0);

#ifdef OUTPUT_DEBUG	
	if (g_bNeedUpdate)
	{
		DEBUG_ADD("Need to Update! Run Updater.exe");
	}

	DEBUG_ADD("---------------[  End ReleaseAllObjects  ]---------------");

	if (g_pDebugMessage != NULL)
	{
		DEBUG_ADD("--------------- Delete DebugMessageArray --------------");
		delete g_pDebugMessage;
		g_pDebugMessage = NULL;
	}
#endif
	DEBUG_CMD(MIN_HIDEWND, "------------------------------");


	if (g_pClientConfig != NULL)
	{
		delete g_pClientConfig;
		g_pClientConfig = NULL;
	}

#ifdef __NPROTECT__
	CloseNPROTECT();
#endif


#ifndef OUTPUT_DEBUG
	ReleaseMutex(hMutex);
#endif

#ifdef OUTPUT_DEBUG
	DeleteCriticalSection(&g_Lock);
#endif

	//----------------------------------------------------------------
	// Execute the Updater
	//----------------------------------------------------------------
	if (g_bNeedUpdate)
	{
		//_spawnl(_P_NOWAIT, UPDATER_FILENAME, UPDATER_FILENAME, "UPDATE", NULL);
		char szTemp[2048];
		sprintf(szTemp, "UPDATE %s", lpCmdLine);
		_chdir(g_CWD);
		_spawnl(_P_OVERLAY, UPDATER_FILENAME, UPDATER_FILENAME, szTemp, NULL);
		//ShellExecute(g_hWnd, NULL, UPDATER_FILENAME, szTemp, NULL, SW_SHOW);
	}

	return 0;
}

//int SURFACE_WIDTH(){return 1024;}
//int SURFACE_HEIGHT(){return 768;}
