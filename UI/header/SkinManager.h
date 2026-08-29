//--------------------------------------------------------------------------
//
// In the multi-lingual version this needs to be managed 
// separately for each coordinate.
// 
// It's hard to put everything into the source code, so I'll put it like this
// for now.
//
//--------------------------------------------------------------------------

#pragma once

#pragma warning (disable:4786)

#include "CTypeTable.h"
#include <vector>

class InterfaceInformation
{
public :
	InterfaceInformation();
	~InterfaceInformation();

	const POINT&				GetPoint( int n ) const { return m_PointList[n]; }
	const RECT&					GetRect( int n ) const { return m_RectList[n]; }
	
	bool						LoadFromLinePointList( const char *szLine );
	bool						LoadFromLineRectList( const char *szLine );
	
private :
	std::vector< POINT >		m_PointList;
	std::vector< RECT >			m_RectList;
	int							m_ID;					// Interface ID
};

class SkinManager : public CTypeTable< InterfaceInformation >
{
public :
	enum
	{
		INFO = 0,
		GAME_MENU,
		OPTION,
		TITLE,
		NEW_CHAR,

#if __CONTENTS(__TITLE_UI_RENWEAL)
		LOGIN_1024_768,
		LOGIN_800_600,
#endif //__TITLE_UI_RENWEAL
		INTERFACE_MAX
	};

	SkinManager();
	~SkinManager();
	
	bool			LoadInformation(const char *szFileName);

protected :
	void			LoadPointList(int k, void *rar );
	void			LoadRectList(int k, void *rar );
};

extern SkinManager *g_pSkinManager;