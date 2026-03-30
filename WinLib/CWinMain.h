//-----------------------------------------------------------------------------
// CWinMain.h
//-----------------------------------------------------------------------------
// window�� ������Ű�� Loop�� �����ؾ� �Ѵ�.
// ��ӹ޾Ƽ� Update�� �����ؾ� �Ѵ�.
//
// ��ӹ��� class���� Init�� overloading�ϴ� ���,
// ��(!) CWinMain::Init(...)�� ȣ���ؾ� �Ѵ�.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//								[ Example ]
//
//-----------------------------------------------------------------------------
// ���⼭�� CWinUpdate�� ������� �ʾҴ�.
//-----------------------------------------------------------------------------
/*
//------------------------------------------------------------------------------
// AppTestApp.cpp
//------------------------------------------------------------------------------

#include "CWinMain.h"
//#include "CWinUpdate.h"

//------------------------------------------------------------------------------
// OnKeyDown - WM_KEYDOWNó��
//------------------------------------------------------------------------------
void
OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case VK_ESCAPE : case VK_RETURN :
			PostQuitMessage(0);
		break;
	}
}

//------------------------------------------------------------------------------
// WinMain
//------------------------------------------------------------------------------
int PASCAL
WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{
	CWinMain		TestApp;
	WINMAIN_INFO	wi;

	//-------------------------------------------------------------
	// WINMAIN_INFO �ʱ�ȭ
	//-------------------------------------------------------------
	wi.hInstance			= hInstance;
	strcpy(wi.ProgramName, "SiGi's Test Application");
	wi.SizeX				= 640;
	wi.SizeY				= 480;
	wi.Mode					= WINMAIN_WINDOW_STYPE_WINDOWMODE;
	
	//-------------------------------------------------------------
	// message ����
	//-------------------------------------------------------------
	TestApp.SetWMFunction(WM_KEYDOWN, OnKeyDown);

	//-------------------------------------------------------------
	// Window ���
	//-------------------------------------------------------------
	TestApp.Init( &wi );
	TestApp.ShowWindow();

	//-------------------------------------------------------------
	// ó�� Loop
	//-------------------------------------------------------------
	TestApp.Loop();

	return 0;
}
*/
//-----------------------------------------------------------------------------

#ifndef	__CWINMAIN_H__
#define	__CWINMAIN_H__

#include <Windows.h>
#include "CWinMainInfo.h"
class CWinUpdate;


class CWinMain {
	public :
		typedef void	(*FUNCTION_MESSAGE)(WPARAM wParam, LPARAM lParam);


	public :
		CWinMain();
		virtual ~CWinMain();

		//-----------------------------------------------------------
		//
		//					Init / Release
		//
		//-----------------------------------------------------------
		virtual bool		Init(const WINMAIN_INFO* pInfo);
		virtual void		Release();

		//-----------------------------------------------------------
		// window�� ���̰� �Ѵ�.
		//-----------------------------------------------------------
		void				ShowWindow();


		//-----------------------------------------------------------
		//
		//					Set
		//
		//-----------------------------------------------------------
		// Update�Լ��� �����Ѵ�.
		//-----------------------------------------------------------
		void				SetUpdate(CWinUpdate* pWinUpdate)	{ m_pWinUpdate = pWinUpdate; }
		
		//-----------------------------------------------------------
		// Window Message�� ó���� �Լ��� �����Ѵ�.
		//-----------------------------------------------------------
		bool				SetWMFunction(UINT message, FUNCTION_MESSAGE function);		

		

		//-----------------------------------------------------------
		//
		//					Loop
		//
		//-----------------------------------------------------------
		void				Loop();	
		

		//-----------------------------------------------------------
		//
		//					Get
		//
		//-----------------------------------------------------------
		HWND				GetHWnd() const			{ return m_hWnd; }
		HINSTANCE			GetHInstance() const	{ return m_hInstance; }
		bool				IsActive() const		{ return m_bActiveApp; }



		//-----------------------------------------------------------
		// Error MessageBox�� ���� window�����Ѵ�.
		//-----------------------------------------------------------
		static void			Error(HWND hWnd, LPCSTR pProgramName, LPCTSTR szError,...);

	protected :
		virtual	void		Update();

		static LRESULT CALLBACK WMProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		//-----------------------------------------------------------
		// Default Window Message Functions
		//-----------------------------------------------------------
		static void			OnDestroy(WPARAM wParam, LPARAM lParam);


	protected :
		//-----------------------------------------------------------
		// app data
		//-----------------------------------------------------------
		HWND					m_hWnd;
		HINSTANCE				m_hInstance;

		bool					m_bActiveApp;		// Is application active?		

		char*					m_pProgramName;		// Program name

		CWinUpdate*				m_pWinUpdate;		// Update class			

	
		//-----------------------------------------------------------
		// message
		//-----------------------------------------------------------
		static FUNCTION_MESSAGE	m_WMFunctions[WM_USER];		// window message ó��		
};

#endif

