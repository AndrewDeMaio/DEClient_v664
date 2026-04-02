//----------------------------------------------------------------------
// 
// Filename    : CGPortCheck.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __CG_PORT_CHECK_H__
#define __CG_PORT_CHECK_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class CGPortCheck;
//
// �α��� �������� ����ڰ� ���� ������ �����Ϸ��� �� ��, �α��� ������
// �� ���� �������� � �ּҿ��� � ����ڰ� � ũ��ó�� �α�����
// ���̴�.. ��� �˷��ִ� ��Ŷ�̴�.
//
// *CAUTION*
//
// ���� ũ��ó �̸��� �ʿ��Ѱ�? �ϴ� �ǹ��� ���� �� �ְڴµ�, ������ ����
// ��츦 ���������� �ʿ��ϰ� �ȴ�. �α��� �����κ��� Slot3 ĳ���͸� ����
// �س���, ������ ���� ������ �����ؼ��� SLOT2 ĳ���͸� �ε��ش޶�� ��
// ���� �ִ� ���̴�. �̸� ���� ���ؼ�, CLSelectPC�� ������ ĳ���͸� 
// ���� �������� �˷���� �ϸ�, CGConnect ������ ĳ���� ���̵� �����ؼ�
// �ٷ� �ε��ϵ��� �ؾ� �Ѵ�.
//
//----------------------------------------------------------------------

class CGPortCheck : public DatagramPacket {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_PORT_CHECK; }
	
	// get packet's body size
	size_t getPacketSize() const 
	{ 
		return szBYTE + m_PCName.size();		// PC name
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "CGPortCheck"; }
		
		// get packet's debug std::string
		std::string toString() const;
	#endif

public:

	// get/set pcName
	const std::string& getPCName() const { return m_PCName; }
	void setPCName(const std::string& pcName) { m_PCName = pcName; }

private :

	// PC name
	std::string m_PCName;
};


//////////////////////////////////////////////////////////////////////
//
// class CGPortCheckFactory;
//
// Factory for CGPortCheck
//
//////////////////////////////////////////////////////////////////////

class CGPortCheckFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new CGPortCheck(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "CGPortCheck"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_PORT_CHECK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGPortCheckPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const 
	{ 
		return szBYTE + 20;		// PC name
	}

};


//////////////////////////////////////////////////////////////////////
//
// class CGPortCheckHandler;
//
////
//////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGPortCheckHandler {
	
public:

	// execute packet's handler
	static void execute(CGPortCheck* pPacket);

};
#endif

#endif
