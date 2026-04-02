//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCQueryResultCharacterName.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_QUERY_RESULT_CHARACTER_NAME_H__
#define __LC_QUERY_RESULT_CHARACTER_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterName;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterName : public Packet {

public:

	// constructor
	LCQueryResultCharacterName() : m_bExist(false) {}

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_LC_QUERY_RESULT_CHARACTER_NAME; }
	
	// get packet's body size
	size_t getPacketSize() const 
	{ 
		return szbool
			+ szBYTE + m_CharacterName.size(); 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "LCQueryResultCharacterName"; }
		
		// get packet's debug std::string
		std::string toString() const;
	#endif

public:

	// get/set player id
	const std::string& getCharacterName() const { return m_CharacterName; }
	void setCharacterName(const std::string & playerID) { m_CharacterName = playerID; }

	// get/set player id's existence
	bool isExist() const { return m_bExist; }
	void setExist(bool bExist = true) { m_bExist = bExist; }

private :

	// player id
	std::string m_CharacterName;

	// player id's existence
	bool m_bExist;

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterNameFactory;
//
// Factory for LCQueryResultCharacterName
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterNameFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new LCQueryResultCharacterName(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "LCQueryResultCharacterName"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const
	{ 
		return szbool
			+ szBYTE + 20; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterNameHandler;
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterNameHandler {

public:

	// execute packet's handler
	static void execute(LCQueryResultCharacterName* pPacket, Player* pPlayer);

};

#endif
