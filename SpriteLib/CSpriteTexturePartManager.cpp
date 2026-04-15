//----------------------------------------------------------------------
// CSpriteTexturePartManager.cpp
//----------------------------------------------------------------------
#include "SpriteLib_PCH.h"
#include "DX3D.h"
#include "CFileIndexTable.h"
#include "CSpriteTexturePartManager.h"

#include "DebugInfo.h"
//#include "MFileDef.h"
#include "Properties.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

#ifdef OUTPUT_DEBUG
#undef OUTPUT_DEBUG
#endif

//----------------------------------------------------------------------
//
// contructor/destructor
//
//----------------------------------------------------------------------
//CSpriteTexturePartManager::CSpriteTexturePartManager(CAlphaSpritePack* pSPK, WORD partSize)
CSpriteTexturePartManager::CSpriteTexturePartManager(const char* spkFilename, WORD partSize)
{
	//m_pSPK = NULL;
	m_pWidth = NULL;
	m_pHeight = NULL;

	//	m_bOpen = false;
	Init(spkFilename, partSize);

	m_historySprPal.clear();

	//Init(pSPK, partSize);
}

CSpriteTexturePartManager::~CSpriteTexturePartManager()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Init(spkFilename, indexFilename)
//----------------------------------------------------------------------
// spkFilename�� AlphaSpritePack�̴�.
// indexFilename�� AlphaSpritePack Index�̴�.
//
// spkFilename�� ȭ���� ��� ���߿� ���� �� �ֵ��� �صΰ�
// indexFilename�� ��� �о ����صд�.
//----------------------------------------------------------------------
void
//CSpriteTexturePartManager::Init(CAlphaSpritePack* pSPK, WORD partSize)
CSpriteTexturePartManager::Init(const char* spkFilename, WORD partSize)
{
	Release();

	///*
	// Index File�� Load�Ѵ�.
//	std::ifstream indexFile(indexFilename, ios::binary);
//	m_SPKIndex.LoadFromFile( indexFile );
//	indexFile.close();
//
//	// SPK�� �ʱ�ȭ �Ѵ�. (������ŭ..)
//	m_SPK.Init( m_SPKIndex.GetSize());//, CDirectDraw::Is565() );
//
//	// SPK File�� ����д�.
//	m_SPKFile.open(spkFilename, ios::binary);
//
//	TYPE_SPRITEID size;
//	m_SPKFile.read((char*)&size, SIZE_SPRITEID);
//
	m_SPK.LoadFromFileRunning(spkFilename);

	int allSize = m_SPK.GetSize();
	//*/


	//m_pSPK = pSPK;

	//int allSize = pSPK->GetSize();

	// Base class�� Init�� �̿��ؼ�..
	// ( ��ü ����, �޸� ��� ���� )
	CPartManager<WORD, WORD, CSpriteSurface*>::Init(allSize, partSize);

	// NULL�� �ʱ�ȭ
	for (int i = 0; i < m_nPart; i++)
	{
		m_pData[i] = NULL;
	}


	m_pWidth = new int[allSize];
	m_pHeight = new int[allSize];

	for (int i = 0; i < allSize; i++)
	{
		m_pWidth[i] = 0;
		m_pHeight[i] = 0;
	}

	/*
	int spWidth, spHeight;
	int width, height;

	if (CDirect3D::IsTexturePow2())
	{
		for (i=0; i<allSize; i++)
		{
			if ((*pSPK)[i].IsInit())
			{
				spWidth = (*pSPK)[i].GetWidth();
				spHeight = (*pSPK)[i].GetHeight();
				width = 1;
				height = 1;

				// width�� height�� spWidth�� spHeight���� Ŀ�� �Ѵ�.
				// square�� �����ش�.
				while (width < spWidth || height < spHeight)
				{
					width <<= 1;
					height <<= 1;
				}

				m_pWidth[i] = width;
				m_pHeight[i] = height;
			}
			else
			{
				m_pWidth[i] = 0;
				m_pHeight[i] = 0;
			}
		}
	}
	else
	{
		for (i=0; i<allSize; i++)
		{
			if ((*pSPK)[i].IsInit())
			{
				spWidth = (*pSPK)[i].GetWidth();
				spHeight = (*pSPK)[i].GetHeight();
				width = spWidth;
				height = spHeight;

				// ū ũ��� ���߾ Square�� �����.
				if (CDirect3D::IsTextureSquareOnly())
				{
					if (width > height)
					{
						height = width;
					}
					else if (width < height)
					{
						width = height;
					}
				}

				m_pWidth[i] = width;
				m_pHeight[i] = height;
			}
			else
			{
				m_pWidth[i] = 0;
				m_pHeight[i] = 0;
			}
		}
	}
	*/

	// 	m_bOpen = true;
	m_EffectScreenPPK.LoadFromFile(g_pFileDef->getProperty("FILE_PALETTE_SCREENEFFECT").c_str());
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
// ������ SPK file�� �ݴ´�.
//----------------------------------------------------------------------
void
CSpriteTexturePartManager::Release()
{
	///*
//	if (m_bOpen)
//	{
//		m_SPKFile.close();
//		m_bOpen = false;
//	}
	//*/
	if (m_pData != NULL)
	{
		for (int i = 0; i < m_nPart; i++)
		{
			if (m_pData[i] != NULL)
			{
				delete m_pData[i];
				m_pData[i] = NULL;
			}
		}
	}

	if (m_pWidth != NULL)
	{
		delete[] m_pWidth;
		m_pWidth = NULL;
	}

	if (m_pHeight != NULL)
	{
		delete[] m_pHeight;
		m_pHeight = NULL;
	}

	DeleteRemoved();
}

//----------------------------------------------------------------------
// Delete Removed
//----------------------------------------------------------------------
// ������ �� �͵�
//----------------------------------------------------------------------
void
CSpriteTexturePartManager::DeleteRemoved()
{
	SPRITESURFACE_LIST::iterator iSurface = m_listRemoved.begin();

	while (iSurface != m_listRemoved.end())
	{
		CSpriteSurface* pSurface = *iSurface;

		delete pSurface;

		iSurface++;
	}

	m_listRemoved.clear();
}

//----------------------------------------------------------------------
// Clear
//----------------------------------------------------------------------
// Video Memory�� ������ clear�Ѵ�.
// �����δ�... �� ���������� ���̴�.
//----------------------------------------------------------------------
void
CSpriteTexturePartManager::Clear()
{
	DeleteRemoved();

	// video memory�� ����~�ش�.
	for (int i = 0; i < m_nPart; i++)
	{
		if (m_pData[i] != NULL)
		{
			m_pData[i]->Restore();
			delete m_pData[i];
			m_pData[i] = NULL;
		}
	}

	// Base class�� Init�� �̿��ؼ�..
	// ( ��ü ����, �޸� ��� ���� )
	CPartManager<WORD, WORD, CSpriteSurface*>::Init(m_nIndex, m_nPart);

	// NULL�� �ʱ�ȭ
	for (int i = 0; i < m_nPart; i++)
	{
		m_pData[i] = NULL;
	}

}

//----------------------------------------------------------------------
// GetTexture( id )
//----------------------------------------------------------------------
// SPK���� ID�� id�� AlphaSprite�� Load�� Surface�� �Ѱ���� �ϴµ�,
//
// Load���� �ʾ�����,
// Index�� �����ؼ� ������ SPK File����
// id�� �ش��ϴ� AlphaSprite�� Load�ؼ� Surface�� �ϳ� �����ϰ�
// �� Surface�� AlphaSprite�� ������ش�.
//
// �� �κп��� �ӵ��� ����� �������� ������...
//----------------------------------------------------------------------
CSpriteSurface*
CSpriteTexturePartManager::GetTexture(TYPE_SPRITEID id, int index)
{
	//static int reload	= 0;
	//static int reuse	= 0;

	//-----------------------------------------------------------
	// ������ --> Load & return
	//-----------------------------------------------------------
	if (IsDataNotNULL(id) && GetUsedPalette(id) == index)
	{
#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD_FORMAT("CSpriteTexturePartManager::GetTexture(%d)", id);
		}
#endif

		CSpriteSurface* pTextureSurface;
		m_historySprPal[id] = index;
		if (GetData(id, pTextureSurface))
		{
			return pTextureSurface;
		}

#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD("No Exist!");
		}
#endif

		//reuse ++;
	}
	else
	{
#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD_FORMAT("CSpriteTexturePartManager::GetTexture New(%d)", id);
		}
#endif

		CSpritePal* pSprite = &m_SPK[id];
		//CAlphaSprite* pSprite = &(*m_pSPK)[id];

		//// �� Load�Ǿ� �ִٰ� �����Ѵ�..
		///*
		//----------------------------------------
		// �̹� Load�� ���̸�..
		//----------------------------------------
//		if (pSprite->IsInit())
//		{
//		}
//		//----------------------------------------
//		// Load�ؾ� �Ǵ� ���
//		//----------------------------------------
//		else
//		{
//			//-----------------------------------------------------------
//			// AlphaSprite�� Load�Ѵ�.
//			//-----------------------------------------------------------
//			// id�� �´� ������ FilePointer�� �̵��ؼ�
//			int temp = m_SPKIndex[id];
//			m_SPKFile.seekg(m_SPKIndex[id], ios::beg);
//			pSprite->LoadFromFile( m_SPKFile );
//		}
		//*/
		// Texture�� Size�� �����Ѵ�.
		int spWidth, spHeight;
		int width, height;
		BYTE smallShift = 0;

		spWidth = pSprite->GetWidth();
		spHeight = pSprite->GetHeight();

		//-----------------------------------------------------
		// ���̰� 0�� ���..
		//-----------------------------------------------------
		if (spWidth == 0 || spHeight == 0)
		{
			return NULL;
		}

		//-----------------------------------------------------------
		// (�ٽ�) �����Ѵ�.
		//-----------------------------------------------------------
		CSpriteSurface* pTextureSurface = new CSpriteSurface;


		width = spWidth;
		height = spHeight;
		CDirect3D::GetTextureSize(width, height);

		//-----------------------------------------------------------
		// 2�� �¼��� �����ϴ� ���..
		//-----------------------------------------------------------
		bool bDifferentSize;	// sprite�� texture�� ũ�Ⱑ �ٸ���?
		if (CDirect3D::IsTexturePow2())
		{
			bDifferentSize = true;

			// width�� height�� �ٸ� ���...
			// ���� �ʿ� ���缭 �Ȱ��� �Ѵ�.
			// Square�� �����..�� �� �� ����.. ����..

			// ū �ʿ� ���߸�... detail�� �������µ�..
			// ���� ������ �־����� ���⵵ �ѵ�(-_-;)
			// ������ �����ϱ� �Ⱦ... - -;;;
			// ���� �ʿ� ���߸� detail�� ��������.
			// ��ư �� �κ� üũ�� �ؾ��Ѵ�.
			if (width > height)
			{
				height = width;
			}
			else //if (width < height)
			{
				width = height;
			}

			//-----------------------------------------------------------
			// Textureũ�⺸�� Sprite ũ�Ⱑ �� ū ���..
			//-----------------------------------------------------------
			// ��, �ϵ����� Spriteũ�⸸ŭ�� Texture�� �������� ���ϴ� ����̴�.
			// shift�� �̿��ؼ� ũ�⸦ ���δ�.
			while (spWidth > width || spHeight > height)
			{
				smallShift++;

				spWidth >>= 1;
				spHeight >>= 1;
			}
		}
		//-----------------------------------------------------------
		// �ƹ��� size�� ���� ���� ���
		//-----------------------------------------------------------
		else
		{
			if (CDirect3D::IsTextureSquareOnly())
			{
				// width�� height�� �ٸ� ���...
				// ū �ʿ� ���缭 �Ȱ��� �Ѵ�.
				// Square�� �����..�� �� �� ����.. ����..
				if (width > height)
				{
					height = width;
					bDifferentSize = true;
				}
				else if (width < height)
				{
					width = height;
					bDifferentSize = true;
				}
			}
			else
			{
				bDifferentSize = false;
			}
		}

		//---------------------------------------------------
		// TextureSurface ����
		//---------------------------------------------------
		pTextureSurface->InitTextureSurface(width, height, 0, CDirect3D::GetPixelFormat1555());

		POINT point;
		point.x = 0;
		point.y = 0;

		if (!pTextureSurface->Lock())
		{
			delete pTextureSurface;
			return NULL;
		}

		int i;

		//---------------------------------------------------
		// �˰� ĥ�ϴ� �κ�..
		//---------------------------------------------------
		//if (bDifferentSize)
		{
			//---------------------------------------------------
			// Texture Surface �ʱ�ȭ
			//---------------------------------------------------
			WORD* pSurface = (WORD*)pTextureSurface->GetSurfacePointer();
			//,	*pSurfaceTemp;
			long pitch = pTextureSurface->GetSurfacePitch();

			int width2 = width << 1;

			for (i = 0; i < height; i++)
			{
				memset(pSurface, 0, width2);
				pSurface = (WORD*)((BYTE*)pSurface + pitch);
			}

			/*
			// Sprite�� �����ϴ� ������ ������ �κ��� �˰�~~
			DWORD width2 = (width - spWidth) << 1;	// *2
			pSurface += spWidth;

			// ������ ���κ�
			if (width2 > 0)
			{
				i = spHeight;
				do
				{
					memset(pSurface, 0, width2);
					pSurface = (WORD*)((BYTE*)pSurface + pitch);
				} while (--i);
			}

			// �Ʒ���
			pSurface -= spWidth;
			width2 = width << 1;
			i = height - spHeight;

			if (i>0)
			{
				do
				{
					memset(pSurface, 0, width2);
					pSurface = (WORD*)((BYTE*)pSurface + pitch);
				} while (--i);
			}
			*/
		}

		//---------------------------------------------------
		// AlphaSprite���
		//---------------------------------------------------
		// Effect�� ũ�⸦ �����ؼ�..
		if (smallShift == 0)
		{
			//pTextureSurface->BltAlphaSprite4444NotTrans(&point, pSprite);
			pTextureSurface->BltSpritePal1555NotTrans(&point, pSprite, m_EffectScreenPPK[index]);
		}
		else
		{
			pTextureSurface->BltSpritePal1555SmallNotTrans(&point, pSprite, smallShift, m_EffectScreenPPK[index]);
		}

		pTextureSurface->Unlock();


		//-----------------------------------------------------------
		// ����Ҷ� ����� ũ��
		//-----------------------------------------------------------
		// ������ ����� Texture Size�� ������ ���� ���� ���
		//-----------------------------------------------------------
		if (m_pWidth[id] == 0 || m_pHeight[id] == 0)
		{
			spWidth = pSprite->GetWidth();
			spHeight = pSprite->GetHeight();

			if (CDirect3D::IsTexturePow2())
			{
				// texture���� ��µǴ� size�� ���Ѵ�.
				for (int i = 0; i < smallShift; i++)
				{
					spWidth >>= 1;
					spHeight >>= 1;
				}

				// ���� ũ��
				width = width * pSprite->GetWidth() / spWidth;
				height = height * pSprite->GetHeight() / spHeight;
			}
			else
			{
				width = spWidth;
				height = spHeight;

				// ū ũ��� ���߾ Square�� �����.
				if (CDirect3D::IsTextureSquareOnly())
				{
					if (width > height)
					{
						height = width;
					}
					else if (width < height)
					{
						width = height;
					}
				}
			}

			m_pWidth[id] = width;
			m_pHeight[id] = height;
		}

		//---------------------------------------------------
		// Replace������ �������� �޸𸮿��� �����.
		//---------------------------------------------------
		CSpriteSurface* pOld = NULL;
		WORD oldIndex = SetData(id, pTextureSurface, pOld);
		m_historySprPal[id] = index;

		if (oldIndex != m_IndexNULL)
		{
			if (pOld != NULL)
			{
				//------------------------------------------------------------
				// D3D�� Texture�� �ٷ� ������ �ʴ� ��쵵 �ִ�.
				// BeginScene() ~ EndScene() ���� Surface�� ����־�� �ϹǷ�
				// ���⼭ ����� �ȵȴ�.
				//------------------------------------------------------------
				//delete pOld;
				//------------------------------------------------------------
				m_listRemoved.push_back(pOld);
			}

			// loading�Ǿ� �ִ� sprite�� �����Ѵ�... �޸� ������..
			//m_SPK[oldIndex].Release();
		}

#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD("OK");
		}
#endif

		// return
		return pTextureSurface;

		//reload++;
	}

	return NULL;
}

int		CSpriteTexturePartManager::GetUsedPalette(int spriteID)
{
	if (m_historySprPal.empty())
		return  -1;

	SPRITE_PALETTE::iterator itr;
	if ((itr = m_historySprPal.find(spriteID)) != m_historySprPal.end())
		return itr->second;

	return -1;
}
