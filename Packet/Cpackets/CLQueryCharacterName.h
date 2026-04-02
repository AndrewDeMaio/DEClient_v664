//--------------------------------------------------------------------------------
// 
// Filename    : CLQueryCharacterName.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_QUERY_CHARACTER_NAME_H__
#define __CL_QUERY_CHARACTER_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLQueryCharacterName;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//--------------------------------------------------------------------------------

class CLQueryCharacterName : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }
	
	// get packet's body size
	size_t getPacketSize() const 
	{ 
		return szBYTE + m_CharacterName.size(); 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "CLQueryCharacterName"; }
		
		// get packet's debug std::string
		std::string toString() const;
	#endif

public:

	// get/set player's id
	const std::string& getCharacterName() const { return m_CharacterName; }
	void setCharacterName(const std::string & playerID) { m_CharacterName = playerID; }

private :

	// �÷��̾� ���̵�
	std::string m_CharacterName;

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameFactory;
//
// Factory for CLQueryCharacterName
//
//--------------------------------------------------------------------------------

class CLQueryCharacterNameFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new CLQueryCharacterName(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "CLQueryCharacterName"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const 
	{ 
		return szBYTE + 20; 
	}

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameHandler;
//
//--------------------------------------------------------------------------------
#ifndef __GAME_CLIENT__
	class CLQueryCharacterNameHandler {

	public:

		// execute packet's handler
		static void execute(CLQueryCharacterName* pPacket, Player* pPlayer);

	};
#endif

#endif
