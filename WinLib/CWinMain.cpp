//-----------------------------------------------------------------------------
// CWinMain.cpp
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "CWinMain.h"
#include "CWinUpdate.h"

//-----------------------------------------------------------------------------
// static members
//-----------------------------------------------------------------------------
CWinMain::FUNCTION_MESSAGE	CWinMain::m_WMFunctions[WM_USER] = { nullptr, };

//-----------------------------------------------------------------------------
//
// constructor/destructor
//
//-----------------------------------------------------------------------------
CWinMain::CWinMain()
{
	m_hWnd = nullptr;
	m_hInstance = nullptr;
	m_bActiveApp = false;
	m_pProgramName = nullptr;

	m_pWinUpdate = nullptr;

	// Default Window Message Functions
	SetWMFunction(WM_DESTROY, OnDestroy);
}

CWinMain::~CWinMain()
{
	if (m_pProgramName!=nullptr)
	{
		delete [] m_pProgramName;
		m_pProgramName = nullptr;
	}

	Release();
}

//-----------------------------------------------------------------------------
//
// member functions
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Error
//-----------------------------------------------------------------------------
void CWinMain::Error(HWND hWnd, LPCSTR pProgramName, LPCTSTR szError,...)
{
    char		szBuff[128];
    va_list		vl;

    va_start(vl, szError);
    vsprintf_s(szBuff, sizeof(szBuff), szError, vl);

    //ReleaseAllObjects();

    MessageBox(hWnd, szBuff, pProgramName, MB_OK);
    DestroyWindow(hWnd);
    va_end(vl);
}

//-----------------------------------------------------------------------------
// Set WM Function
//-----------------------------------------------------------------------------
bool CWinMain::SetWMFunction(UINT message, FUNCTION_MESSAGE function)
{
	if (message < WM_USER)
	{
		m_WMFunctions[message] = function;

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
// WM Process
//-----------------------------------------------------------------------------
LRESULT CALLBACK CWinMain::WMProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//---------------------------------------------------------
	// ������ Window Message�� ��쿡..
	//---------------------------------------------------------
	if (message < WM_USER)
	{
		//---------------------------------------------------------
		// �� message�� ���� handling code�� �ִ� ���
		//---------------------------------------------------------
		if (m_WMFunctions[message] != nullptr)
		{
			(*m_WMFunctions[message])(wParam, lParam);
		}

		//---------------------------------------------------------	
		// ������ �⺻~~�� �θ���..
		//---------------------------------------------------------
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	//---------------------------------------------------------
	// ����.. - -;
	// Ȥ��.. WM_USER�� �Ѵ� Window Message�� ���� ������? ���.
	//---------------------------------------------------------
	//Error(hWnd, NULL, "Unknown Window Message : %d", message);

	return -1;	// ��? - -;;		
}

//-----------------------------------------------------------------------------
// Init
//-----------------------------------------------------------------------------
bool CWinMain::Init(const WINMAIN_INFO* pInfo)
{
	//---------------------------------------------------------------
	// �⺻ ���� ����
	//---------------------------------------------------------------
	m_hInstance = pInfo->hInstance;	

	// Program �̸� ����
	if (m_pProgramName!=nullptr)
	{
		delete [] m_pProgramName;
	}

	size_t len = strlen(pInfo->ProgramName) + 1;
	m_pProgramName = new char[len];
	strcpy_s(m_pProgramName, len, pInfo->ProgramName);



	//---------------------------------------------------------------
	// WNDCLASS�� �����ؼ� ���
	//---------------------------------------------------------------
	WNDCLASS                    wc;

    // Set up and register window class
    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= WMProcess;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= m_hInstance;
    wc.hIcon			= nullptr;
    wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground	= (HBRUSH )GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName		= nullptr;
    wc.lpszClassName	= m_pProgramName;
    RegisterClass(&wc);

	//---------------------------------------------------------------
	// Window Style�� �°� ���� �����Ѵ�.
	//---------------------------------------------------------------
    int cx,cy;	
	DWORD style;
	DWORD exStyle;

	switch (pInfo->Mode)
	{
		case WINMAIN_WINDOW_STYPE_FULLSCREEN :
			exStyle = WS_EX_TOPMOST;// | WS_EX_APPWINDOW;
			style = WS_POPUP;
			cx = GetSystemMetrics(SM_CXSCREEN);
			cy = GetSystemMetrics(SM_CYSCREEN);				  
		break;
	
		case WINMAIN_WINDOW_STYPE_WINDOWMODE :
			exStyle = WS_EX_APPWINDOW;
			style = WS_OVERLAPPED | WS_THICKFRAME | WS_MINIMIZEBOX;
			cx = pInfo->SizeX + GetSystemMetrics(SM_CXSIZEFRAME)*2;
			cy = pInfo->SizeY + GetSystemMetrics(SM_CYSIZEFRAME)*2+GetSystemMetrics(SM_CYMENU);	
		break;

		default :
			Error(m_hWnd, m_pProgramName, "Wrong WinMain WindowStyle!");
		return false;
	}

	//---------------------------------------------------------------
	// Create a window
	//---------------------------------------------------------------
    m_hWnd = CreateWindowEx(exStyle,
							  m_pProgramName,
							  m_pProgramName,
							  style,
							  0,
							  0,
							  cx,
							  cy,
							  nullptr,
							  nullptr,
							  m_hInstance,
							  nullptr);

    if (!m_hWnd)
	{
		Error(m_hWnd, m_pProgramName, "Can't Create Window!");
        return false;
	}

	// ����� �ʱ�ȭ �ƴٰ� ǥ��..
	m_bActiveApp = true;

	return true;
}

//-----------------------------------------------------------------------------
// Release
//-----------------------------------------------------------------------------
void CWinMain::Release()
{
}

//-----------------------------------------------------------------------------
// Window�� ��Ÿ���� �Ѵ�.
//-----------------------------------------------------------------------------
void CWinMain::ShowWindow()
{
	::ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	SetFocus(m_hWnd);
}

//-----------------------------------------------------------------------------
// Loop
//-----------------------------------------------------------------------------
void CWinMain::Loop()
{
	MSG	msg;

	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, nullptr, 0, 0))
				return;// msg.wParam;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (m_bActiveApp)
		{
			Update();
		}
		else
		{
			//------------------------------------------------
			// Make sure we go to sleep if we have nothing else to do
			//------------------------------------------------
			WaitMessage();
		}
	}
}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------
void CWinMain::Update()
{
	if (m_pWinUpdate != nullptr)
	{
		m_pWinUpdate->Update();
	}
}

//-----------------------------------------------------------------------------
// Default Message Functions
//-----------------------------------------------------------------------------
void CWinMain::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}