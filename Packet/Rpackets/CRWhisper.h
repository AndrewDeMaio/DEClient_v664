//////////////////////////////////////////////////////////////////////
// 
// Filename    : CRWhisper.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CR_WHISPER_H__
#define __CR_WHISPER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "WhisperTypes.h"

//////////////////////////////////////////////////////////////////////
//
// class CRWhisper;
//
// ���� ������ Ư�� �÷��̾��� Whisper �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� Whisper ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class CRWhisper : public Packet {

public :

	CRWhisper();
	~CRWhisper();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CR_WHISPER; }
	
	// get packet's body size
	size_t getPacketSize () const;	 

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CRWhisper"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// ���� ���
	const std::string& getName() const { return m_Name ; }
	void setName ( const std::string & Name ) { m_Name = Name ; }

	// �޴� ���
	const std::string& getTargetName() const { return m_TargetName ; }
	void setTargetName ( const std::string & Name ) { m_TargetName = Name ; }

	// get / set ListNumber
	BYTE getMessageSize() const { return m_Messages.size(); }
	
	// get/set chatting message
	WHISPER_MESSAGE*	popMessage ()	{ WHISPER_MESSAGE* pStr = m_Messages.front(); m_Messages.pop_front(); return pStr; }	
	void addMessage ( const WHISPER_MESSAGE & msg )	{ WHISPER_MESSAGE* pStr = new WHISPER_MESSAGE; *pStr = msg; m_Messages.push_back( pStr ); }

	// race
	bool isVampire () const { return m_eRace == RACE_VAMPIRE; }
	bool isSlayer () const { return m_eRace == RACE_VAMPIRE; }
	bool isOusters () const { return m_eRace == RACE_OUSTERS; }
	Race_t getRace() const { return m_eRace; }
	void setRace (Race eRace) { m_eRace = eRace; }

	// World
	void setWorldID(const WorldID_t id)	{ m_WorldID = id; }
	const WorldID_t getWorldID() const	{ return m_WorldID; }

private :
	
	// character's creature Name
	std::string m_Name;

	std::string m_TargetName;
	
	// chatting message
	std::list<WHISPER_MESSAGE*> m_Messages;

	// Race
	Race_t m_eRace;

	// World
	WorldID_t	m_WorldID;

	
};


//////////////////////////////////////////////////////////////////////
//
// class CRWhisperFactory;
//
// Factory for CRWhisper
//
//////////////////////////////////////////////////////////////////////

class CRWhisperFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CRWhisper(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CRWhisper"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CR_WHISPER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CRWhisperPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szBYTE + 10 + szBYTE + 10 + szBYTE + 32768 + szBYTE + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class CRWhisperHandler;
//
//////////////////////////////////////////////////////////////////////

class CRWhisperHandler {
	
public :
	
	// execute packet's handler
	static void execute ( CRWhisper * pPacket , Player * pPlayer );

};

#endif
