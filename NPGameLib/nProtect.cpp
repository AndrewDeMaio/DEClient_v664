//#include "Client_PCH.h"
//#include "DebugInfo.h"

#ifndef OUTPUT_DEBUG
//#define __OLD_VERSION__
//#define __RUN_GAMEHACK__

//#define __TEST_SERVER__
//#define __REAL_SERVER__

#pragma warning(disable:4786)

#include <windows.h>
#include <process.h>
#include "ContentsFilter.h"
#include "nProtect.h"
#include "npfgmsdk.h"	

bool		g_bIsNT = false, g_bIsStartGameHack = false;
HINSTANCE	g_nProtectInstance = NULL;
HINSTANCE	g_NPFGMInstance = NULL;
HINSTANCE	g_nPSICEInstance = NULL;
DWORD		g_OsVersion[2];
MYCHECKNPMON *pCheckNPMON = NULL;

//#ifdef __REAL_SERVER__
//20081223 �� ���� ���� ���� .ini���� �̸��� �ٸ��� �����Ұ�� �Ʒ� ���ڰ��� ���� �Ͽ� �̿��Ѵ�.
#if __CONTENTS(__NPROTECT)
#ifdef __DESIGNED_KOREA
	CNPGameLib npgl("DarkEden");
#elif __DESIGNED_ITEMMANIA
	CNPGameLib npgl("DarkEden");
#elif __DESIGNED_JAPAN
	CNPGameLib npgl("DarkEdenJP");
#endif
#endif //__NPROTECT
	//CNPGameLib npgl("DarkEdenChina");
//#elif defined(__TEST_SERVER__)
//	CNPGameLib npgl("DarkEdenTest");
//#endif

DWORD	g_delayTime_npmon = 60000;			// 20�� �ĺ��� üũ ����	

extern	HWND				g_hWnd;
extern void Send_nProtect_Auth(DWORD dwVal);

BOOL CALLBACK NPGameMonCallback(DWORD dwMsg, DWORD dwArg);

bool	CheckWindowVersion()
{
	OSVERSIONINFOEXW VersionInfo = {};
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);

	typedef NTSTATUS(WINAPI* RtlGetVersionFn)(PRTL_OSVERSIONINFOW);
	RtlGetVersionFn pfnRtlGetVersion = (RtlGetVersionFn)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion");

	if (!pfnRtlGetVersion || pfnRtlGetVersion((PRTL_OSVERSIONINFOW)&VersionInfo) != 0)
	{
		MessageBox(NULL, "�������� �ʴ� ������ �����Դϴ�.","Execute Error", MB_OK);
		return false;
	}

	g_bIsNT = (VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT);

	g_OsVersion[0] = VersionInfo.dwPlatformId;
	g_OsVersion[1] = VersionInfo.dwMajorVersion;

	return true;
}
//
//bool	ChecknProtectCRC(HINSTANCE dll, char* FilePath)
//{
//	CheckCRC		MyCheckCRC;
//		
//	DEBUG_ADD_FORMAT("[nProtect] CheckCRC %s",FilePath);
//	MyCheckCRC = (CheckCRC)GetProcAddress( dll, "CheckCRC" );
//	return MyCheckCRC( (LPTSTR)(LPCTSTR) FilePath ) != FALSE;
//}

int		CheckNPROTECT(int CurTime)
{
#ifdef __OLD_VERSION__
	static DWORD time = 0;
	HWND hWnd;
	
	time++;
	if(time >= 512)
		time = 0;
	
	if(time == 4)
	{
		hWnd = FindWindow("TfrmNPMON", "WWW.NPROTECT.COM");	
		
		if( hWnd != 0 )
			return NPROTECT_OK;
		
		DEBUG_ADD("[nProtect] Cannot Find nProtect");
		return NPROTECT_ERROR;
	} //else
#endif
	
//	if(time == 15)
//	if( TimerCheckNPMON() )
//	{
//		BOOL Result = pCheckNPMON();
//
//		if(!Result)
//			return NPROTECT_ERROR;
//
//		return NPROTECT_OK;
//		
//#ifdef __RUN_GAMEHACK__
//		if ( !pnPFindSICE())
//			return NPROTECT_OK;
//		
//		DEBUG_ADD("[nProtect] Find SoftICE");
//		return NPROTECT_ERROR;
//#endif
	//	}
	if (npgl.Check() != NPGAMEMON_SUCCESS) 
	{
		MessageBox(g_hWnd, "���Ӱ��尡 ���� �� ���� �ʽ��ϴ�. ������������ ���� �˴ϴ�.", "Error", MB_OK|MB_ICONERROR);
		return NPROTECT_ERROR;
	}

	return NPROTECT_OK;
}

int		RunNPROTECT()
{	
	//zzi - Ŭ�ι� ���񽺿��� nProtect�� �� ���ٰ� �Ѵ�. ������.. OK....
#ifdef __DESIGNED_INTERNATION
	return NPROTECT_OK;
#endif
	//-
#ifdef __OLD_VERSION__
	int		ExecuteResult;


	g_nProtectMessage[NPROTECT_NORMAL]= "�� �� ���� ���� �Դϴ�. ��ũ������ �����մϴ�.";
	g_nProtectMessage[NPROTECT_EXIT_TWO] = "nProtect �� ���� ��ũ������ ����˴ϴ�.(1)";
	g_nProtectMessage[NPROTECT_FORCE_EXIT] = "nProtect �� ���� ��ũ������ ����˴ϴ�.(2)";
	g_nProtectMessage[NPROTECT_SPEEDHACK] = "���ǵ����� �߰ߵǾ� ��ũ������ ����˴ϴ�.";
	g_nProtectMessage[NPROTECT_SOFTICE] = "�������� �߰ߵǾ� ��ũ������ ����˴ϴ�.";
	g_nProtectMessage[NPROTECT_SH_ERROR] ="nProtect �� ���� ��ũ������ ����˴ϴ�(SHERROR)";
	g_nProtectMessage[NPROTECT_CHECK_ERROR] = "nProtect Check ������ ���� ��ũ������ ����˴ϴ�.";	
	
	DEBUG_ADD("[nProtect] Execute nProtect");
	ExecuteResult = spawnl(P_WAIT, "findhack.exe","findhack.exe",NULL);
	
	switch(ExecuteResult)
	{
	case 1024 :				// �޸𸮻� ��ŷ���� �������� ���� ���
		DEBUG_ADD("[nProtect] Cannot Find Hacking program");
		break;
	case 1025 :				// �޸𸮻� ��ŷ���� �����ϳ� ���������� ġ�Ḧ ���� ���
		DEBUG_ADD("[nProtect] Find Hacking program. - fixed it.");
		break;
	case 1026 :				// �޸𸮻��� ��ŷ���� ���������� ����ڰ� ġ�Ḧ �������� �ʰų� ���α׷����� ���������� ġ�Ḧ ���� ������ ���
		DEBUG_ADD("[nProtect] did not Fix Hacking program.");		
		return NPROTECT_EXECUTE_ERROR_DID_NOT_FIX;		
	case 1027 :				// ��ŷ�� ���� ���α׷��� ���������� �ٿ�ε� ���� �ʾ��� ���(URL�� �߸��Ǿ��ų� ������ ���������� �������� ���� ���)
		DEBUG_ADD("[nProtect] Can not download check program");
		return NPROTECT_EXECUTE_ERROR_CANNOT_DOWNLOAD;		
	case 1028 :				// NPX.DLL ��� ���� �� nProtect ������ �ʿ��� ������ ���� ���
		DEBUG_ADD("[nProtect] Cannot Find DLL File");
		return NPROTECT_EXECUTE_ERROR_CANNOT_FIND_DLL;
	case 1029 :				// ���α׷������� ���ܻ����� �߻����� ���
		DEBUG_ADD("[nProtect] Occured Exception in nProtect");
		return NPROTECT_EXECUTE_ERROR_EXCEPTION;
	case 1030 :				// ����ڰ� ���� ��ư�� Ŭ������ ����� ó����
		DEBUG_ADD("[nProtect] Quit nProtect by user");
		return NPROTECT_EXECUTE_ERROR;
	case 1031 :				// ������Ʈ ���� ������ ������ ���
		DEBUG_ADD("[nProtect] Cannot connect updateserver");
		return NPROTECT_CANNOT_UPDATE;
	}

	DEBUG_ADD("[nProtect] Ok");
	
	if( ( g_nProtectInstance = LoadLibrary(FILE_NPROTECT_DLL)) == NULL )
		return NPROTECT_CANNOT_FIND_DLL;	
/*
	char szBuffer[256] = {0,};
	if( GetSystemDirectory( szBuffer, 256) == 0)
		return NPROTECT_ERROR_GET_WINDOWS_DIRECTORY;
	strcat( szBuffer, "\\NPMON.EXE");	
	bool	Result;
	Result = ChecknProtectCRC(g_nProtectInstance, "FindHack.exe");
	Result |=ChecknProtectCRC(g_nProtectInstance, szBuffer );
	
	if(!Result)
	{
		FreeLibrary( g_nProtectInstance );
		g_nProtectInstance = NULL;
		return NPROTECT_ERROR_CRC_CHECK;	
	}
*/
	if( (pCheckNPMON = (MYCHECKNPMON *)GetProcAddress(g_nProtectInstance, "CheckNPMON")) == NULL)
		return NPROTECT_ERROR_NOT_EXIST_CHECK_NPMON;	
	
#ifdef __RUN_GAMEHACK__
	if( LoadLibraryNPFGM() == false )
		return NPROTECT_ERROR_LOAD_DLL_GAMEHACK;

	EnterGameHack();
#endif


#endif // __OLD_VERSION__

#ifndef __OLD_VERSION__
//	g_nProtectMessage[NPGAMEMON_COMM_ERROR] = "[NPGAMEMON_COMM_ERROR] nProtect���� ��ſ� ������ �߻��Ͽ� ��ũ������ �����մϴ�.";
//	g_nProtectMessage[NPGAMEMON_COMM_CLOSE] = "[NPGAMEMON_COMM_CLOSE] nProtect���� ����� ���� ��ũ������ �����մϴ�.";
//	g_nProtectMessage[NPGAMEMON_INIT_ERROR] = "[NPGAMEMON_INIT_ERROR] �ʱ�ȭ �����Դϴ�. ��ũ������ �����մϴ�.";
//	g_nProtectMessage[NPGAMEMON_SPEEDHACK] = "[NPGAMEMON_SPEEDHACK] ���ǵ����� �߰ߵǾ� ��ũ������ �����մϴ�.";
//	g_nProtectMessage[NPGAMEMON_GAMEHACK_KILLED] = "[NPGAMEMON_GAMEHACK_KILLED] �������� �߰ߵǾ����ϴ�. ��ũ������ �����մϴ�.";
//	g_nProtectMessage[NPGAMEMON_GAMEHACK_DETECT] = "[NPGAMEMON_GAMEHACK_DETECT] �������� �����Ǿ� ��ũ������ �����մϴ�.";
//	g_nProtectMessage[NPGAMEMON_UNDEFINED] = "[NPGAMEMON_UNDEFINED] nProtect ���� ������ �߻��Ͽ� ��ũ������ ����˴ϴ�.";

	g_nProtectMessage[NPGAMEMON_COMM_ERROR] = "[NPGAMEMON_COMM_ERROR] ";
	g_nProtectMessage[NPGAMEMON_COMM_CLOSE] = "[NPGAMEMON_COMM_CLOSE] ";
	g_nProtectMessage[NPGAMEMON_INIT_ERROR] = "[NPGAMEMON_INIT_ERROR] ";
	g_nProtectMessage[NPGAMEMON_SPEEDHACK] = "[NPGAMEMON_SPEEDHACK] ";
	g_nProtectMessage[NPGAMEMON_GAMEHACK_KILLED] = "[NPGAMEMON_GAMEHACK_KILLED] ";
	g_nProtectMessage[NPGAMEMON_GAMEHACK_DETECT] = "[NPGAMEMON_GAMEHACK_DETECT] ";
	g_nProtectMessage[NPGAMEMON_UNDEFINED] = "[NPGAMEMON_UNDEFINED] nProtect ";


//#ifdef __REAL_SERVER__
//	DWORD dwResult = npgl.Init(g_hWnd,"DarkEden");
//#elif defined(__TEST_SERVER__)
//#endif
	//DWORD dwResult = npgl.Init(g_hWnd);

	DWORD dwResult = npgl.Init();
	if (dwResult != NPGAMEMON_SUCCESS)
    {
		// ������ ���� �޽��� ���
		TCHAR msg[512];
		
//		switch( dwResult )
		{
/*		case 110 :
			wsprintf(msg, "[110] �̹� nProtect�� ����Ǿ� �ֽ��ϴ�.\r\n�ٽ� DarkEden�� ������ �ּ���.");
			break;		
		case 112 :
			wsprintf(msg, "[112] ���̷��� �� ��ŷ �� �˻� ��� �ε��� �����߽��ϴ�.\r\n���̷����� �����Ǿ� ���� ���� ������ �ֽ� ������� �˻��غ��ñ� �ٶ��ϴ�.");
			break;
		case 122 :
			wsprintf(msg, "[122] nProtect �� GameMon ������ ���������� �ʽ��ϴ�.");
			break;
		case 140 :
			wsprintf(msg, "[140] nProtect�� Update �� �� �����ϴ�.\r\n���� ���ͳ� ������ �ùٸ��� Ȯ���Ͽ� �ֽð�\r\n�׷��� ������ ������ ����� �������ּ���.");
			break;		
		case 120 :
		case 150 :
		case 180 :
			{
				char szBuffer[256];
				GetCurrentDirectory(255, szBuffer );
				wsprintf(msg, "ErrorCode[%d] ���� �Դϴ�.\r\nnProtect�� �����ϴµ� �ʿ��� ������ ã���� �����ϴ�.\r\n��ũ����Ȩ������(http://www.darkeden.com)���� ���� �ٿ�ε�޾�\r\n%s ������ ������ Ǯ�� �ذ�� �� �ֽ��ϴ�.",dwResult,szBuffer);
			}
			break;
		case 151 :
			wsprintf(msg, "[151] ���Ӱ��� ������Ʈ ����� ���ų� �����Ǿ����ϴ�. ���̷��� �˻縦 �غ��� ��\r\n���Ӱ��� �¾������� �ٿ�޾� ���� ���� ������ �ٽ� ��ġ ���ּ���.");
			break;
		case 210 :			
		case 220 :
		case 230 :
			CheckWindowVersion();
			wsprintf(msg, "[%d][%d/%d] nProtect GameGuard �ʱ�ȭ ���� �Դϴ�.\r\n������ ������ �� �����ϴ�.\r\nDarkEden������ GameGuard������ �ִ� ���ϵ��� �����Ͽ�\r\nnprotect_help@inca.co.kr�� �����ּ���.", dwResult,g_OsVersion[0],g_OsVersion[1]);
			break;
		case 340 :
			wsprintf(msg, "[340] nProtect �� �ٿ�ε忡 �����Ͽ����ϴ�. \r\n��Ʈ��ũ ���°� ���� �ʰų�, ���ͳ� ������ ������ ���� �� �ֽ��ϴ�.");
			break;
		case 360 :
			wsprintf(msg, "[360] ���̷����� �־ ������ ������ �� �����ϴ�.\r\n�ֽ� ������� ���̷����� ġ���Ͻ��Ŀ� ������\r\n�������ּ���.");
			break;
		case NPGMUP_ERROR_DECRYPT :
			wsprintf(msg, "[370] nProtect Decrypt Error");			
			break;
		case 380 :
			wsprintf(msg, "[380] ���Ӱ��� ������Ʈ ���� ���ӿ� �����Ͽ����ϴ�.\r\n��� �� �ٽ� �õ����ּ���.");			
			break;
		case 390 :
			wsprintf(msg, "[390] INI ���Ͽ� ������ �ֽ��ϴ�.");
			break;
		default :
			wsprintf(msg, "nProtect GameGuard ���� ���� : %lu", dwResult);
			break;
		case 110 :
			wsprintf(msg, "[110] �̹� nProtect�� ����Ǿ� �ֽ��ϴ�.\r\n�ٽ� DarkEden�� ������ �ּ���.");
			break;		
		case 112 :
			wsprintf(msg, "[112] ���̷��� �� ��ŷ �� �˻� ��� �ε��� �����߽��ϴ�.\r\n���̷����� �����Ǿ� ���� ���� ������ �ֽ� ������� �˻��غ��ñ� �ٶ��ϴ�.");
			break;
		case 122 :
			wsprintf(msg, "[122] nProtect �� GameMon ������ ���������� �ʽ��ϴ�.");
			break;
		case 140 :
			wsprintf(msg, "[140] nProtect�� Update �� �� �����ϴ�.\r\n���� ���ͳ� ������ �ùٸ��� Ȯ���Ͽ� �ֽð�\r\n�׷��� ������ ������ ����� �������ּ���.");
			break;		
		case 120 :
		case 150 :
		case 180 :
			{
				char szBuffer[256];
				GetCurrentDirectory(255, szBuffer );
				wsprintf(msg, "ErrorCode[%d] ���� �Դϴ�.\r\nnProtect�� �����ϴµ� �ʿ��� ������ ã���� �����ϴ�.\r\n��ũ����Ȩ������(http://www.darkeden.com)���� ���� �ٿ�ε�޾�\r\n%s ������ ������ Ǯ�� �ذ�� �� �ֽ��ϴ�.",dwResult,szBuffer);
			}
			break;
		case 151 :
			wsprintf(msg, "[151] ���Ӱ��� ������Ʈ ����� ���ų� �����Ǿ����ϴ�. ���̷��� �˻縦 �غ��� ��\r\n���Ӱ��� �¾������� �ٿ�޾� ���� ���� ������ �ٽ� ��ġ ���ּ���.");
			break;
		case 210 :			
		case 220 :
		case 230 :
			CheckWindowVersion();
			wsprintf(msg, "[%d][%d/%d] nProtect GameGuard �ʱ�ȭ ���� �Դϴ�.\r\n������ ������ �� �����ϴ�.\r\nDarkEden������ GameGuard������ �ִ� ���ϵ��� �����Ͽ�\r\nnprotect_help@inca.co.kr�� �����ּ���.", dwResult,g_OsVersion[0],g_OsVersion[1]);
			break;
		case 340 :
			wsprintf(msg, "[340] nProtect �� �ٿ�ε忡 �����Ͽ����ϴ�. \r\n��Ʈ��ũ ���°� ���� �ʰų�, ���ͳ� ������ ������ ���� �� �ֽ��ϴ�.");
			break;
		case 360 :
			wsprintf(msg, "[360] ���̷����� �־ ������ ������ �� �����ϴ�.\r\n�ֽ� ������� ���̷����� ġ���Ͻ��Ŀ� ������\r\n�������ּ���.");
			break;
		case NPGMUP_ERROR_DECRYPT :
			wsprintf(msg, "[370] nProtect Decrypt Error");			
			break;
		case 380 :
			wsprintf(msg, "[380] ���Ӱ��� ������Ʈ ���� ���ӿ� �����Ͽ����ϴ�.\r\n��� �� �ٽ� �õ����ּ���.");			
			break;
		case 390 :
			wsprintf(msg, "[390] INI ���Ͽ� ������ �ֽ��ϴ�.");
			break;
		default :
			wsprintf(msg, "nProtect GameGuard ���� ���� : %lu", dwResult);
			break;
*/
//		default :
			//wsprintf(msg, "nProtect GameGuard Error : %lu", dwResult);

			wsprintf(msg, "���Ӱ��� ���� �� ������ �߻��Ͽ����ϴ�. ���� ���� ���� GameGuard ������ �ִ� *.erl ���ϵ��� Game1@inca.co.kr�� ÷���Ͽ� ���� �����ֽñ� �ٶ��ϴ�.") ; 

//			break;
		} 

		


		MessageBox(g_hWnd, msg, "Error", MB_OK|MB_ICONERROR);
		return NPROTECT_ERROR;
    }
	else
	{
		npgl.SetHwnd(g_hWnd);
		SetCallbackToGameMon(NPGameMonCallback);
	}

#endif
	
	return NPROTECT_OK;
}

void	CloseNPROTECT()
{
#ifdef __OLD_VERSION__
	HWND nProtecthWnd;

	nProtecthWnd = FindWindow( NULL, "WWW.NPROTECT.COM" );

#ifdef __RUN_GAMEHACK__
	ReleaseGameHack();
#endif
	

	if(nProtecthWnd != 0)
	{
		DEBUG_ADD("[nProtect] Close nProtect");
		SendMessage( nProtecthWnd, WM_NPROTECT_FORCEEXIT, NULL, NULL );
	}
	if(g_nProtectInstance != NULL)
	{
		FreeLibrary( g_nProtectInstance );
		g_nProtectInstance = NULL;
	}
	if(g_NPFGMInstance != NULL)
	{
		FreeLibrary( g_NPFGMInstance );
		g_NPFGMInstance = NULL;
	}
#ifdef __RUN_GAMEHACK__
	if(g_nPSICEInstance != NULL)
	{
		FreeLibrary( g_nPSICEInstance );
		g_nPSICEInstance = NULL;
	}
#endif

#endif // __OLD_VERSION__
//	npgl.Close();
}

//bool	LoadLibraryNPFGM()
//{
//	if( CheckWindowVersion() == false)
//		return false;
//
//#ifdef __RUN_GAMEHACK__
//
//	if(g_bIsNT)
//		g_NPFGMInstance = LoadLibrary( NPFGM_NT );
//	else
//		g_NPFGMInstance = LoadLibrary( NPFGM_9X );
//
//	g_nPSICEInstance = LoadLibrary( NPFGM_NT );
//#endif
//	
//	if(g_NPFGMInstance == NULL 
//#ifdef __RUN_GAMEHACK__
//		|| g_nPSICEInstance == NULL
//#endif
//		)
//		return false;
//	
//	if( ((pEnterProtect = (EnterProtect) GetProcAddress(g_NPFGMInstance, "EnterProtect")) == NULL) ||
//		((pReleaseProtect = (ReleaseProtect) GetProcAddress( g_NPFGMInstance, "ReleaseProtect")) == NULL)
//#ifdef __RUN_GAMEHACK__
//		||((pnPFindSICE = (nPFindSICE) GetProcAddress( g_nPSICEInstance, "nPFindSICE")) == NULL)
//#endif
//		)
//		return false;
//	else
//		return true;	
//}
//
//void	EnterGameHack()
//{
//#ifdef __RUN_GAMEHACK__
//	if(g_bIsStartGameHack == true)
//		return;
//
//	pEnterProtect();
//	g_bIsStartGameHack = true;
//#endif
//
//}
//
//void	ReleaseGameHack()
//{
//#ifdef __RUN_GAMEHACK__
//	if(g_bIsStartGameHack == false)
//		return;
//
//	pReleaseProtect();
//	g_bIsStartGameHack = false;
//#endif
//}

bool	TimerCheckNPMON(int CurTime)
{
	DWORD		nCurrentTime;
	if(CurTime)
		nCurrentTime = CurTime;
	else
		nCurrentTime = timeGetTime();
	
	if( (nCurrentTime - g_TimerNPMON) > g_delayTime_npmon )
	{
		g_TimerNPMON = nCurrentTime;
		g_delayTime_npmon = 30000;
		return true;
	}
	return false;
}


BOOL CALLBACK NPGameMonCallback(DWORD dwMsg, DWORD dwArg)
{
//	TCHAR msg[128];

	g_nProtectErrorMessage = dwMsg;	
	g_nProtectErrorMessage2 = dwArg;
	switch (dwMsg)
    {		
	case NPGAMEMON_COMM_ERROR:
	case NPGAMEMON_COMM_CLOSE:
		g_bForceExitBynProtect = true;
		return false; // �ݵ�� ����
		
	case NPGAMEMON_INIT_ERROR:
//		wsprintf(msg, "nProtect GameGuard �ʱ�ȭ ���� : %lu", dwArg);
//		MessageBox(hWnd, msg, "Error", MB_OK);
		g_bForceExitBynProtect = true;
		return false; // �ݵ�� ����
		
	case NPGAMEMON_SPEEDHACK:
//		MessageBox(hWnd, "���ǵ����� �����Ǿ����ϴ�.", "Warning", MB_OK);
		g_bForceExitBynProtect = true;
		return false; // ����
		
	case NPGAMEMON_GAMEHACK_KILLED:
//		MessageBox(hWnd, "�������� �߰ߵǾ����ϴ�.", "Warning", MB_OK);
		return true; // ��� ����
		
	case NPGAMEMON_GAMEHACK_DETECT:
//		MessageBox(hWnd, "�������� �����Ǿ����ϴ�.", "Warning", MB_OK);
		g_bForceExitBynProtect = true;
		return false; // ����
	case NPGAMEMON_CHECK_CSAUTH:
		//MessageBox(g_hWnd, "NPGAMEMON_CHECK_CSAUTH����", "Warning", MB_OK);
		Send_nProtect_Auth(dwArg);
		return true;
	}	
	return true;
}
void Set_Auth(DWORD dwVal)
{
	npgl.Auth(dwVal);
}
#endif