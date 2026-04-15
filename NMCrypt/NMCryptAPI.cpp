//================================================================================================|
// SampleNMCryptAPI.cpp : Netmarble Crypt Library Test Application
//================================================================================================|


#include "stdafx.h"
#include "NMCrypt.h"
#include "NMCryptAPI.h"
#include <string.h>

//-------------------------------------------------------------------------------------------------

class CConnectInfo
{
public:

	CString m_strConnectServerIP;
	UINT    m_uiServerPort;

	CString m_strLoginID;
	CString m_strLoginPW;
	CString m_strExtra;

public:

	CConnectInfo()
	{
		m_strConnectServerIP.Format( _T("") );
		m_uiServerPort = 0;

		m_strLoginID.Format( _T("") );
		m_strLoginPW.Format( _T("") );
		m_strExtra.Format( _T("") );
	}
};

CConnectInfo g_CI;

//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------

char* StrTok( char *lpStr, char chSeparator )
{
	static const int TOK_BUFSIZE = 1024*40;

	static char chBuf[TOK_BUFSIZE];
	static char chToken[TOK_BUFSIZE];

	static char *lpNow = NULL;

	if( lpStr )
	{
		int nlen = strlen( lpStr );
		_ASSERT( nlen < TOK_BUFSIZE );

		strcpy( chBuf, lpStr );
		lpNow = chBuf;
	}

	if( !lpNow || *lpNow == 0 ) return NULL;

	int nTLen = 0;
	char *porg = lpNow;
	while( *lpNow != 0 )
	{
		if( *lpNow == chSeparator )
		{
			++lpNow;
			break;
		}
		++nTLen;
		++lpNow;
	}

	if( nTLen > 0 )
	{
		strncpy( chToken, porg, nTLen );
		chToken[nTLen] = 0;
	}
	else
	 chToken[0] = 0;

  return chToken;
}

//-------------------------------------------------------------------------------------------------

BOOL AnalizeArgument( char *lpArg )
{
#ifdef _TEST_
	MessageBox( NULL, lpArg , "AnalizeArgument CmdLine", MB_OK );
#endif

	if( strlen( lpArg ) >= ( 1024 * 4 ) ) return FALSE;

	char szKey[1024] = {0,};
	char szBuf[1024*4] = {0,};

#ifdef _TEST_
		MessageBox( NULL, szKey, "before GetCryptKey", MB_OK );
#endif

	if( !GetCryptKey( szKey, 1024-1, true ) ) 
	{
#ifdef _TEST_
		MessageBox( NULL, "GetCrypKeyFail", "Sample CmdLine", MB_OK );
#endif
		return FALSE;
	}

#ifdef _TEST_
		MessageBox( NULL, szKey, "Sample CmdLine-Key", MB_OK );
		MessageBox( NULL, lpArg, "Sample CmdLine-lpArg", MB_OK );
		MessageBox( NULL, szBuf, "Sample CmdLine-szBuf", MB_OK );
#endif

	if( CRYPT_SUCCESS != DecryptString( lpArg, szKey, szBuf ) ) return FALSE;

	char szGetArg[5][1024] = {0,};
	char* token = StrTok( szBuf, ',' );

	int nArgCount = 0;
	while( token && nArgCount < 5 )
	{
		strcpy( szGetArg[nArgCount], token );
		nArgCount++;
		token = StrTok( NULL, ',' );
	}

	if( nArgCount < 4 ) return FALSE;
	if( strlen( szGetArg[0] ) > 16 ) return FALSE;

	//--------------------------------------------------------------------------------------------|

	g_CI.m_strConnectServerIP = szGetArg[0];
	g_CI.m_uiServerPort       = (UINT)::atoi( szGetArg[1] );

	g_CI.m_strLoginID = szGetArg[2];
	g_CI.m_strLoginPW = szGetArg[3];
	g_CI.m_strExtra   = szGetArg[4];

	//--------------------------------------------------------------------------------------------|

#ifdef _TEST_

	MessageBox( NULL, g_CI.m_strConnectServerIP, "Decoding Result IP", MB_OK );

	CString strTemp = _T( "" );
	strTemp.Format( "%d", g_CI.m_uiServerPort, "Decoding Result Port", MB_OK );
	MessageBox( NULL, strTemp, "Decoding Result Port", MB_OK );

	MessageBox( NULL, g_CI.m_strLoginID, "Decoding Result ID", MB_OK );
	MessageBox( NULL, g_CI.m_strLoginPW, "Decoding Result PW", MB_OK );
	MessageBox( NULL, g_CI.m_strExtra, "Decoding Result Extra", MB_OK );

#endif

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
/*
void CheckCommandLine( void )
{
	CString szCmnd;
	szCmnd.Format( "%s", ::GetCommandLine() );

#ifdef _TEST_
	MessageBox( NULL, szCmnd, "Sample CmdLine", MB_OK );
#endif

	int nStart = szCmnd.Find( '\"', 0 ) + 1;
	int nEnd = szCmnd.Find( '\"', 1 );

	CString szArg1;
	if( szCmnd.GetAt(0) == '\"' )
	{
		nStart = szCmnd.Find( '\"', 0 ) + 1;
		nEnd = szCmnd.Find( '\"', 1 );

		if( szCmnd.GetLength() > nEnd + 2 ) szArg1 = szCmnd.Mid( nEnd + 1 );
		szArg1.TrimLeft();
	}
	else
	{
		nStart = 0;
		nEnd = szCmnd.Find( ' ', 1 );

		if( szCmnd.GetLength() > nEnd + 1 ) szArg1 = szCmnd.Mid( nEnd + 1 );
	}

	CString szDir;
	szDir.Format( "%s", szCmnd.Mid( nStart, nEnd - nStart ) );

	for( int i = szDir.GetLength(); i > 0; i-- )
	{
		if( szDir.GetAt(i-1) == '\\' )
		{
			szDir = szDir.Mid( 0, i-1 );
			break;
		}
	}

	if( AnalizeArgument( (char*)szArg1.operator LPCTSTR() ) == FALSE )
	{
		MessageBox( NULL, "プログラムに必要な環境を初期化できません", "ERROR", MB_OK );
		return;
	}
}*/

//-------------------------------------------------------------------------------------------------

bool CallWinMain( )
{
	CString szCmnd;
	szCmnd.Format( "%s", ::GetCommandLine() );

#ifdef _TEST_
	MessageBox( NULL, szCmnd, "Sample CmdLine", MB_OK );
#endif
	
	
	int nStart = szCmnd.Find( '\"', 0 ) + 1;
	int nEnd = szCmnd.Find( '\"', 1 );

	CString szArg1;
	if( szCmnd.GetAt(0) == '\"' )
	{
		nStart = szCmnd.Find( '\"', 0 ) + 1;
		nEnd = szCmnd.Find( '\"', 1 );

		if( szCmnd.GetLength() > nEnd + 2 ) szArg1 = szCmnd.Mid( nEnd + 1 );
		szArg1.TrimLeft();
	}
	else
	{
		nStart = 0;
		nEnd = szCmnd.Find( ' ', 1 );

		if( szCmnd.GetLength() > nEnd + 1 ) szArg1 = szCmnd.Mid( nEnd + 1 );
	}

	CString szDir;
	szDir.Format( "%s", szCmnd.Mid( nStart, nEnd - nStart ) );

	for( int i = szDir.GetLength(); i > 0; i-- )
	{
		if (szDir.GetAt(i - 1) == '\\')
		{
			szDir = szDir.Mid(0, i - 1);
			break;
		}
	}
	
	
	char *cStrTok = StrTok((char*)szArg1.operator LPCTSTR() ,  ' ') ;  

	//MessageBox( NULL, cStrTok, "Sample CmdLi111ne", MB_OK );
	
	//char cStr[2048] ;  
	
	int iLength = strlen(cStrTok) + 1;  
	//wsprintf(cStr ,  "Length = %d" , iLength); 
	if(iLength >= 20)	iLength = 0 ; 
	//MessageBox( NULL, cStr , "Sample CmdLine", MB_OK );

	
//	MessageBox( NULL, (char*)szArg1.operator LPCTSTR() + iLength , "Sample CmdLine", MB_OK );

	if( AnalizeArgument( (char*)szArg1.operator LPCTSTR() + iLength ) == FALSE )
	{
		MessageBox( NULL, "プログラムに必要な環境を初期化できません", "ERROR", MB_OK );
		return false;


	}



//	CheckCommandLine();

	return true;
}


char*	GetServerIP()
{
	int iLen = g_CI.m_strConnectServerIP.GetLength() ;  
#ifdef _TEST_
	OutputDebugString(g_CI.m_strConnectServerIP.GetBuffer(iLen+1)) ;
	OutputDebugString("%n") ;
	MessageBox( NULL, g_CI.m_strConnectServerIP.GetBuffer(iLen+1), "ERROR", MB_OK );
#endif
	return g_CI.m_strConnectServerIP.GetBuffer(iLen+1) ; 
}


char*	GetLoginID()
{
	int iLen = g_CI.m_strLoginID.GetLength() ; 
#ifdef _TEST_
	OutputDebugString(g_CI.m_strLoginID.GetBuffer(iLen+1)) ;
	OutputDebugString("%n") ;
	MessageBox( NULL, g_CI.m_strLoginID.GetBuffer(iLen+1), "ERROR", MB_OK );
#endif
	return g_CI .m_strLoginID.GetBuffer(iLen+1) ; 
}

char*	GetLoginPW() 
{
	int iLen = g_CI.m_strLoginPW.GetLength() ; 
#ifdef _TEST_
	OutputDebugString(g_CI.m_strLoginPW.GetBuffer(iLen+1)) ;
	OutputDebugString("%n") ;
	MessageBox( NULL, g_CI.m_strLoginPW.GetBuffer(iLen+1), "ERROR", MB_OK );
#endif
	return g_CI.m_strLoginPW.GetBuffer(iLen+1) ; 
}

UINT	GetWorldID()
{
	int iLen = g_CI.m_strExtra.GetLength() ; 
	char *cExtra  = g_CI.m_strExtra.GetBuffer(iLen+1) ;
	
	char cStr[4]  = { 0 , } ;
	memcpy(cStr , cExtra , 3) ;

#ifdef _TEST_	
	OutputDebugString(g_CI.m_strExtra.GetBuffer(iLen+1)) ;
	OutputDebugString("%n") ;
	MessageBox( NULL, g_CI.m_strExtra.GetBuffer(iLen+1), "GetWorldID", MB_OK );

	OutputDebugString(cStr) ;
	OutputDebugString("%n") ;
	MessageBox( NULL, cStr, "GetWorldID", MB_OK );

	char cStr1[4]  = { 0 , } ;
	wsprintf(cStr1 , "%d" , (UINT)::atoi(cStr ) ) ; 
	MessageBox( NULL, cStr1, "GetWorldID", MB_OK );
#endif

	return (UINT)::atoi(cStr )  ; 
		 
}

UINT	GetServerID()
{
	int iLen = g_CI.m_strExtra.GetLength() ; 
	char *cExtra  = g_CI.m_strExtra.GetBuffer(iLen+1) ;
	char cStr[4] = { 0 , } ;
	memcpy(cStr , cExtra + 4 , 3) ; 
	
#ifdef _TEST_	
	MessageBox( NULL, g_CI.m_strExtra.GetBuffer(iLen+1), "GetServerID", MB_OK );
	OutputDebugString(cStr) ;
	OutputDebugString("%n") ;
	MessageBox( NULL, cStr, "GetServerID", MB_OK );
	char cStr1[4]  = { 0 , } ;
	wsprintf(cStr1 , "%d" , (UINT)::atoi(cStr ) ) ; 
	MessageBox( NULL, cStr1, "GetWorldID", MB_OK );
#endif

	return (UINT)::atoi(cStr )  ; 
}

UINT		GetPort()
{
	return g_CI.m_uiServerPort ;
}