//-----------------------------------------------------------------------------
// MZoneSoundManager.h
//-----------------------------------------------------------------------------
// Zone���� �Ҹ��� ���� �ִ� ���߿�..
// Player�� ������������.. �Ҹ����� ����� ũ�Ⱑ �޶�����.
// ���������� ���� �Ҹ����� �����ϴ���...
// �ݺ��Ǵ� �Ҹ����� �͵��̳�.. �� ��͵���.. �ٲ�����Ѵ�.. ��.
//
// ZONESOUND_NODE�� ���� play�ǰ� �ִ� �Ҹ� �ϳ��� ���� �����̰�
// MZoneSoundManager�� �� �Ҹ����� �����Ѵ�..
//-----------------------------------------------------------------------------

#ifndef	__MZONESOUNDMANAGER_H__
#define __MZONESOUNDMANAGER_H__

#include "MZoneSound.h"
#include "CTypeMap.h"
#include <DSound.h>
#include <map>

//-----------------------------------------------------------------------------
// ZONESOUND_NODE
//-----------------------------------------------------------------------------
// ���� Play�ǰ� �ִ� �Ҹ��� ���� ����
// m_pBuffer�� g_pSoundTable�� Buffer�� Duplicate�ؼ� ���� �ִ´�.
//-----------------------------------------------------------------------------
class ZONESOUND_NODE
{
	public :
		ZONESOUND_NODE(TYPE_SOUNDID id=SOUNDID_NULL);
		~ZONESOUND_NODE();

		//---------------------------------------------------------------
		// Get
		//---------------------------------------------------------------
		TYPE_SOUNDID			GetSoundID() const		{ return m_SoundID; }
		LPDIRECTSOUNDBUFFER		GetBuffer() const		{ return m_pBuffer; }
		int						GetX() const			{ return m_X; }
		int						GetY() const			{ return m_Y; }
		bool					IsLoop() const			{ return m_bLoop; }

		//---------------------------------------------------------------
		// Play
		//---------------------------------------------------------------
		void					Play(int x=0, int y=0, bool bLoop=false);
		void					Stop();
		
		//---------------------------------------------------------------
		// Loop
		//---------------------------------------------------------------
		void					StopLoop();			
		bool					IsContinueLoop() const	{ return m_bContinueLoop; }
		void					SetContinueLoop()		{ m_bContinueLoop = true; }
		void					UnSetContinueLoop()		{ m_bContinueLoop = false; }
		
		//---------------------------------------------------------------
		// File I/O
		//---------------------------------------------------------------
		void					SaveToFile(std::ofstream& file);
		void					LoadFromFile(ivfstream& file);

	protected :
		TYPE_SOUNDID				m_SoundID;				// Sound ID
		LPDIRECTSOUNDBUFFER			m_pBuffer;				// buffer
		int							m_X, m_Y;				// �Ҹ��� ��µǴ� ��ǥ
		bool						m_bLoop;				// �ݺ� ����
		bool						m_bContinueLoop;		// ��� �ݺ��ؼ� �Ҹ�����?
		int							m_playerX, m_playerY;	// �� �Ҹ��� ������ player�� ��ǥ
};


//-----------------------------------------------------------------------------
// MZoneSoundTable
//-----------------------------------------------------------------------------
// Zone�� �����ϴ� �Ҹ��鿡 ���� ����
//-----------------------------------------------------------------------------
class MZoneSoundTable : public CTypeMap<ZONESOUND_INFO>
{
	public :
		MZoneSoundTable();
		~MZoneSoundTable();
};

//-----------------------------------------------------------------------------
// MZoneSoundManager
//-----------------------------------------------------------------------------
// id==ZoneSoundID. ���� Play�ǰ� �ִ� �Ҹ��� ����
//-----------------------------------------------------------------------------
class MZoneSoundManager : public CTypeMap<ZONESOUND_NODE>
{
	public :
		MZoneSoundManager();
		~MZoneSoundManager();

		//---------------------------------------------------------------------
		// Update Sound
		//---------------------------------------------------------------------		
		void			UpdateSound();

	protected :
		TYPE_SECTORPOSITION		m_LastX, m_LastY;
		DWORD					m_LastUpdateTime;
};

//-----------------------------------------------------------------------------
// global
//-----------------------------------------------------------------------------
extern MZoneSoundTable*		g_pZoneSoundTable;

extern MZoneSoundManager*	g_pZoneSoundManager;

#endif
