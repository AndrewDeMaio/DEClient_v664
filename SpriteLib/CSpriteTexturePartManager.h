//----------------------------------------------------------------------
// CSpriteTexturePartManager.h
//----------------------------------------------------------------------
// Ư��File(SPK)�� ���ؼ�
// FileIndex(SPKI)�� �����ؼ�
// �Ϻ��� Sprite�� Load�ؼ� ����ϰ� �ϴ� class
//----------------------------------------------------------------------

#ifndef	__CSPRITETEXTUREPARTMANAGER_H__
#define	__CSPRITETEXTUREPARTMANAGER_H__

#include "CPartManager.h"
#include "CSpriteSurface.h"
#include <list>
#include <map>
//std::ifstream;
//class CFileIndexTable;
#include "CSpritePack.h"
#include "CSpritePal.h"
#include "MPalettePack.h"

class CSpriteTexturePartManager : public CPartManager<WORD, WORD, CSpriteSurface*>
{
	public :
		typedef std::list<CSpriteSurface*>	SPRITESURFACE_LIST;
		typedef std::map<int, int>			SPRITE_PALETTE;			// ����� ��������Ʈ ���̵� �������� ����� �ķ�Ʈ ��ȣ

	public :
		//CTexturePartManager(CAlphaSpritePack* pSPK, WORD partSize=100);
		CSpriteTexturePartManager(const char* spkFilename, WORD partSize=100);
		~CSpriteTexturePartManager();

		//---------------------------------------------------
		// Init / Release
		//---------------------------------------------------
		//void				Init(CAlphaSpritePack* pSPK, WORD partSize);
		void				Init(const char* spkFilename, WORD partSize);
		void				Release();

		// data������ �ʱ�ȭ ��Ų��.
		void				Clear();

		//---------------------------------------------------
		// SPK�� id��° AlphaSprite�� �Ѱܹ޴´�.
		//---------------------------------------------------
		CSpriteSurface*		GetTexture(TYPE_SPRITEID id, int index);

		// AlphaSprite�� ���� ũ�⸦ �Ѱ��ش�.
		int					GetWidth(TYPE_SPRITEID id)	{ return m_pWidth[id]; }
		int					GetHeight(TYPE_SPRITEID id)	{ return m_pHeight[id]; }

		int					GetSpriteWidth(TYPE_SPRITEID id)	{ return m_SPK[id].GetWidth(); }
		int					GetSpriteHeight(TYPE_SPRITEID id)	{ return m_SPK[id].GetHeight(); }

		//---------------------------------------------------
		// ������ �� �͵�
		//---------------------------------------------------
		void				DeleteRemoved();

		int					GetUsedPalette(int spriteID);

	protected :
//		bool				m_bOpen;		// SPK File�� Open�ߴ°�?
//		std::ifstream		m_SPKFile;		// SPK File
//		CFileIndexTable		m_SPKIndex;		// SPK Index ����
		CSpritePalPack			m_SPK;			// SPK

		//CAlphaSpritePack	*m_pSPK;			// SPK

		// Texture ����Ҷ��� ũ��
		int					*m_pWidth;
		int					*m_pHeight;

		// �������� �͵�..
		SPRITESURFACE_LIST	m_listRemoved;
		SPRITE_PALETTE		m_historySprPal;
		MPalettePack		m_EffectScreenPPK;
};

class CNormalSpriteTexturePartManager : public CPartManager<WORD, WORD, CSpriteSurface*>
{
	public :
		typedef std::list<CSpriteSurface*>	SPRITESURFACE_LIST;
		typedef std::map<int, int>			SPRITE_PALETTE;			// ����� ��������Ʈ ���̵� �������� ����� �ķ�Ʈ ��ȣ

	public :
		CNormalSpriteTexturePartManager(CSpritePack* pSPK, WORD partSize=100);
//		CNormalSpriteTexturePartManager(const char* spkFilename, WORD partSize=100);
		~CNormalSpriteTexturePartManager();

		//---------------------------------------------------
		// Init / Release
		//---------------------------------------------------
		//void				Init(CAlphaSpritePack* pSPK, WORD partSize);
		void				Init(CSpritePack *pSPK, WORD partSize);
		void				Release();

		// data������ �ʱ�ȭ ��Ų��.
		void				Clear();

		//---------------------------------------------------
		// SPK�� id��° AlphaSprite�� �Ѱܹ޴´�.
		//---------------------------------------------------
		CSpriteSurface*		GetTexture(TYPE_SPRITEID id);

		// AlphaSprite�� ���� ũ�⸦ �Ѱ��ش�.
		int					GetWidth(TYPE_SPRITEID id)	{ return m_pWidth[id]; }
		int					GetHeight(TYPE_SPRITEID id)	{ return m_pHeight[id]; }

		int					GetSpriteWidth(TYPE_SPRITEID id)	{ return (*m_pSPK)[id].GetWidth(); }
		int					GetSpriteHeight(TYPE_SPRITEID id)	{ return (*m_pSPK)[id].GetHeight(); }

		//---------------------------------------------------
		// ������ �� �͵�
		//---------------------------------------------------
		void				DeleteRemoved();

	protected :
//		bool				m_bOpen;		// SPK File�� Open�ߴ°�?
//		std::ifstream		m_SPKFile;		// SPK File
//		CFileIndexTable		m_SPKIndex;		// SPK Index ����
		CSpritePack			*m_pSPK;			// SPK

		// Texture ����Ҷ��� ũ��
		int					*m_pWidth;
		int					*m_pHeight;

		// �������� �͵�..
		SPRITESURFACE_LIST	m_listRemoved;
};


#endif

