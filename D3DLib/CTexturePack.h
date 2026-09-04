//----------------------------------------------------------------------
// CTexturePack.h
//----------------------------------------------------------------------

#ifndef	__CTEXTUREPACK_H__
#define	__CTEXTUREPACK_H__

#include "CSpriteSurface.h"
#include "CAlphaSpritePack.h"
#include "CShadowSprite.h"
//#include "CShadowSpritePack.h"

class CTexturePack {
	public :
		CTexturePack();
		~CTexturePack();

		//--------------------------------------------------------
		// Init/Release
		//--------------------------------------------------------
		void			Init(int count);
		bool			Init( CAlphaSpritePack& ASPK );		
		void			Release();

		//--------------------------------------------------------
		// Part
		//--------------------------------------------------------
		bool			InitPart(CShadowSpriteTypePack& SSPK, TYPE_SPRITEID firstShadowSpriteID, TYPE_SPRITEID lastShadowSpriteID );

		//--------------------------------------------------------
		// file I/O
		//--------------------------------------------------------
		//void			SaveToFile(std::ofstream& spkFile, std::ofstream& indexFile);
		//void			LoadFromFile(ivfstream& file);		
		
		//--------------------------------------------------------
		// size
		//--------------------------------------------------------
		int	GetSize() const		{ return m_nTextures; }

		//--------------------------------------------------------
		// operator
		//--------------------------------------------------------
		CSpriteSurface&		operator [] (int n) { return m_pTextures[n]; }

	protected :
		int					m_nTextures;		// Number of Textures
		CSpriteSurface*		m_pTextures;		// Array of Textures
};

#endif


