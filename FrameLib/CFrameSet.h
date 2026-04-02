//----------------------------------------------------------------------
// CFrameSet.h
//----------------------------------------------------------------------
//
// FramePack���� Ư�� Frame�� Load�� �� �ְ� �Ѵ�.
//
// FrameSet file(index��)���� ������ �о 
// FramePack���� Ư���� Frame�� �о���δ�.
//
// FrameSet IndexFile�� ������ �̿��ؼ� FramePack���� 
// Ư�� ��ġ(File Position)�� Frame�� Load�Ѵ�.
//
//----------------------------------------------------------------------

#ifndef	__CFRAMESET_H__
#define	__CFRAMESET_H__

#include "CFrame.h"


template <class Type>
class CFrameSet {
public:
	CFrameSet();
	~CFrameSet();

	//--------------------------------------------------------
	// Init/Release
	//--------------------------------------------------------
	void		Init(TYPE_FRAMEID count);
	void		Release();

	//--------------------------------------------------------
	// file I/O		
	//--------------------------------------------------------
	// FramePack File���� Frame�� Load�Ѵ�.
	// indexFile = FilePointer File, packFile = FramePack File
	bool		LoadFromFile(ivfstream& indexFile, std::ifstream& packFile);


	//--------------------------------------------------------
	// operator
	//--------------------------------------------------------
	Type& operator [] (TYPE_FRAMEID n) { return m_pFrames[n]; }


protected:
	TYPE_FRAMEID		m_nFrames;			// Frame ID�� ����
	Type* m_pFrames;			// Type�� Set
};


//----------------------------------------------------------------------
// CFrameSet.cpp
//----------------------------------------------------------------------

//#include "CFramePack.h"
//#include "CFrameSet.h"

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------
template <class Type>
CFrameSet<Type>::CFrameSet()
{
	m_nFrames = 0;
	m_pFrames = NULL;
}

template <class Type>
CFrameSet<Type>::~CFrameSet()
{
	// array�� �޸𸮿��� �����Ѵ�.
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Init
//----------------------------------------------------------------------
template <class Type>
void
CFrameSet<Type>::Init(TYPE_FRAMEID count)
{
	// ������ ���� ��� 
	if (count == 0)
		return;

	// �ϴ� ����
	Release();

	// �޸� ���
	m_nFrames = count;

	m_pFrames = new Type[m_nFrames];
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
template <class Type>
void
CFrameSet<Type>::Release()
{
	if (m_pFrames != NULL)
	{
		// ��� MFrame�� �����.
		delete[] m_pFrames;
		m_pFrames = NULL;

		m_nFrames = 0;
	}
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
// FrameSet IndexFile�� �̿��ؼ� FramePack File���� 
// Ư�� ��ġ�� Frame���� Load�Ѵ�.
//----------------------------------------------------------------------
template <class Type>
bool
CFrameSet<Type>::LoadFromFile(ivfstream& indexFile, std::ifstream& packFile)
{
	TYPE_FRAMEID	count;

	//------------------------------------------------------
	// FrameSet�� Frame������ �о���δ�.
	//------------------------------------------------------
	indexFile.read((char*)&count, SIZE_FRAMEID);


	long* pIndex = new long[count];	// file position

	//------------------------------------------------------
	// FrameSet IndexFile�� ��� �о���δ�.
	//------------------------------------------------------
	for (TYPE_FRAMEID i = 0; i < count; i++)
	{
		indexFile.read((char*)&pIndex[i], 4);
	}

	// Loop�� ���� ����ϴ� ������ 
	// �ƹ����� �ΰ��� file�� ���ÿ� access�ϸ�
	// ������ �� ���Ƽ�... �����ϱ�? - -;;


	//------------------------------------------------------
	// Frame�� Load�� memory�� ��´�.
	//------------------------------------------------------
	Init(count);

	//------------------------------------------------------
	// Index(File Position)�� �̿��ؼ� FramePack����
	// Ư�� Frame���� Load�Ѵ�.
	//------------------------------------------------------
	for (int i = 0; i < count; i++)
	{
		packFile.seekg(pIndex[i], std::ios::beg);
		m_pFrames[i].LoadFromFile(packFile);
	}

	delete[] pIndex;

	return true;
}


//----------------------------------------------------------------------
// FrameSet�� define�Ѵ�.
//----------------------------------------------------------------------
typedef CFrameSet<FRAME_ARRAY>			CThingFrameSet;
typedef	CFrameSet<ACTION_FRAME_ARRAY>	CCreatureFrameSet;


#endif

