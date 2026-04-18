#include "client_PCH.h"
#include "SkinManager.h"
#include "RarFile.h"
#include "vs_ui_filepath.h"


#include <map>
#include <string>

SkinManager *g_pSkinManager = NULL;

InterfaceInformation::InterfaceInformation()
{
	m_ID = 0;
	m_PointList.clear();
	m_RectList.clear();
}

InterfaceInformation::~InterfaceInformation()
{
}

bool		InterfaceInformation::LoadFromLinePointList( const char *szLine )
{
	POINT pt;

	sscanf(szLine,"%d %d",&pt.x, &pt.y);
	
	m_PointList.push_back( pt );
	return true;
}

bool		InterfaceInformation::LoadFromLineRectList( const char *szLine )
{
	RECT rect;
	
	sscanf(szLine,"%d %d %d %d",&rect.left, &rect.top, &rect.right, &rect.bottom );

	m_RectList.push_back( rect );
	return true;
}

SkinManager::SkinManager()
{
	Init( INTERFACE_MAX );
}

SkinManager::~SkinManager()
{
}

bool			SkinManager::LoadInformation(const char *szFileName)
{
	CRarFile rarfile;
	rarfile.SetRAR(RPK_INFO,RPK_PASSWORD);
	bool bOpened = rarfile.Open(szFileName);

	if( !bOpened || !rarfile.IsSet() )
	{
		char cwd[MAX_PATH] = {0};
		GetCurrentDirectoryA(MAX_PATH, cwd);

		// Check if the RPK is reachable from CWD
		DWORD rpkAttr = GetFileAttributesA(RPK_INFO);

		char msg[1024];
		sprintf(msg, "SkinManager: Failed to open \"%s\" from RPK \"%s\"\n"
		             "  Open returned: %s\n"
		             "  IsSet: %s  size=%d  ptr=%p\n"
		             "  CWD: %s\n"
		             "  RPK exists at CWD: %s",
		        szFileName, RPK_INFO,
		        bOpened ? "true" : "false",
		        rarfile.IsSet() ? "true" : "false",
		        rarfile.GetSize(),
		        rarfile.GetFilePointer(),
		        cwd,
		        (rpkAttr != INVALID_FILE_ATTRIBUTES) ? "YES" : "NO");
		MessageBox(NULL, msg, "SkinManager Debug", MB_OK);
		return false;
	}

	Init( INTERFACE_MAX );

	char szLine[256];

	std::map< std::string, int >	MapStringToKey;

	MapStringToKey["INFO"] = 0;
	MapStringToKey["GAME_MENU"] = 1;
	MapStringToKey["OPTION"] = 2;
	MapStringToKey["TITLE"] = 3;
	MapStringToKey["NEW_CHAR"] = 4;
	MapStringToKey["LOGIN_1024_768"] = 5;
	MapStringToKey["LOGIN_800_600"] = 6;

	while( rarfile.GetString( szLine, 256 ) )
	{
		if( szLine[0] == ';' ) continue;
		if( strlen(szLine) <= 0 ) continue;

		if( szLine[0] == '*' )
		{
			int key;
			char szType[40],szKey[40];
			sscanf( szLine+1, "%s %s", szKey,szType);

			std::map< std::string, int >::iterator itr = MapStringToKey.find( szKey );
			if(  itr != MapStringToKey.end() )
			{		
				key = itr->second;
				if( !strcmp( szType, "POINT_LIST" ) )
					LoadPointList( key, reinterpret_cast<void*>(&rarfile) );			
				else if ( !strcmp( szType, "RECT_LIST" ) )
					LoadRectList( key, reinterpret_cast<void*>(&rarfile) );			
			}
		}
	}
	rarfile.Release();
	return true;
}

void		SkinManager::LoadRectList( int k , void* rar )
{
	char szLine[256];
	
	CRarFile *rarfile = reinterpret_cast<CRarFile*>(rar);
	while( rarfile->GetString( szLine, 256 ) )
	{
		if( szLine[0] == ';' ) continue;
		if( strlen(szLine) <= 0 ) continue;
		
		if( szLine[0] == '*' )
		{
			char szKey[256];
			sscanf(szLine+1,"%s",szKey);

			if( !strcmp( szKey,"END") )
				break;
		}
		if( k >= 0 && k < INTERFACE_MAX )
			m_pTypeInfo[k].LoadFromLineRectList( szLine );
	}
}

void		SkinManager::LoadPointList(int k, void *rar )
{
	char szLine[256];
	CRarFile *rarfile = reinterpret_cast<CRarFile*>(rar);
	while( rarfile->GetString( szLine, 256 ) )
	{
		if( szLine[0] == ';' ) continue;
		if( strlen(szLine) <= 0 ) continue;
		
		if( szLine[0] == '*' )
		{
			char szKey[256];
			sscanf(szLine+1,"%s",szKey);

			if( !strcmp( szKey,"END") )
				break;
		}
		if( k >= 0 && k < INTERFACE_MAX )
			m_pTypeInfo[k].LoadFromLinePointList( szLine );
	}
}
