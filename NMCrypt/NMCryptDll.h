// NMCryptDll.h : main header file for the NMCRYPTDLL DLL
//

#if !defined(AFX_NMCRYPTDLL_H__DB03DBD9_0E5D_48A8_B6C1_76484FC1161C__INCLUDED_)
#define AFX_NMCRYPTDLL_H__DB03DBD9_0E5D_48A8_B6C1_76484FC1161C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNMCryptDllApp
// See NMCryptDll.cpp for the implementation of this class
//

class CNMCryptDllApp : public CWinApp
{
public:
	CNMCryptDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNMCryptDllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNMCryptDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NMCRYPTDLL_H__DB03DBD9_0E5D_48A8_B6C1_76484FC1161C__INCLUDED_)
