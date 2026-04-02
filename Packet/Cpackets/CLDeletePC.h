//----------------------------------------------------------------------
// 
// Filename    : CLDeletePC.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __CL_DELETE_PC_H__
#define __CL_DELETE_PC_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//----------------------------------------------------------------------
//
// class CLDeletePC;
//
// Ư�� ������ PC �� �����ϴ� ��Ŷ�̴�.
//
//----------------------------------------------------------------------

class CLDeletePC : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CL_DELETE_PC; }
	
	// get packet's body size
	size_t getPacketSize () const { return szBYTE + m_Name.size() + szSlot + szBYTE + m_SSN.size(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "CLDeletePC"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get/set name
	const std::string& getName () const { return m_Name; }
	void setName ( std::string name ) { m_Name = name; }

	// get/set Slot
	Slot getSlot () const { return m_Slot; }
	void setSlot ( Slot slot ) { m_Slot = slot; }

	// get/set SSN
	const std::string& getSSN() const { return m_SSN; }
	void setSSN( const std::string & SSN ) { m_SSN = SSN; }

private :
	
	// PC name
	std::string m_Name;

	// Slot
	Slot m_Slot;

	// �ֹε�Ϲ�ȣ
	std::string m_SSN;

};


//////////////////////////////////////////////////////////////////////
//
// class CLDeletePCFactory;
//
// Factory for CLDeletePC
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CLDeletePCFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CLDeletePC(); }

	// get packet name
	std::string getPacketName () const { return "CLDeletePC"; }
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_DELETE_PC; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szBYTE + 20 + szSlot + szBYTE + 20; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CLDeletePCHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CLDeletePCHandler {

	public :

		// execute packet's handler
		static void execute ( CLDeletePC * pPacket , Player * pPlayer );

	};
#endif

#endif
