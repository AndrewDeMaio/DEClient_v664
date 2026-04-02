//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCRegisterPlayerOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_REGISTER_PLAYER_OK_H__
#define __LC_REGISTER_PLAYER_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOK;
//
// �α��μ����� Ŭ���̾�Ʈ���� �α��� ������ �˷��ִ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOK : public Packet {

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_LC_REGISTER_PLAYER_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCRegisterPlayerOKPacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return szBYTE + m_GroupName.size() + szBYTE; }
	
	
    // get / set Groupname
	const std::string& getGroupName() const { return m_GroupName; }
	void setGroupName( const std::string & GroupName ) { m_GroupName = GroupName; }
	
	// get / set GoreLevel
	bool isAdult() const { return m_isAdult; }
	void setAdult( bool isAdult ) { m_isAdult = isAdult; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "LCRegisterPlayerOK"; }

		// get packet's debug std::string
		std::string toString () const { return "LCRegisterPlayerOK"; }
	#endif

private :
	// ���� �׷� �̸�.
	std::string m_GroupName;
	
	// ���� ���� : ���� �÷��̾ �̼����� �ΰ�?
	// true�� ��� ����
	// false �� ��� �̼�����
	bool m_isAdult;
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOKFactory;
//
// Factory for LCRegisterPlayerOK
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new LCRegisterPlayerOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LCRegisterPlayerOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_LC_REGISTER_PLAYER_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szBYTE + 20 + szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOKHandler {

public :

	// execute packet's handler
	static void execute ( LCRegisterPlayerOK * pPacket , Player * pPlayer );

};

#endif
