//--------------------------------------------------------------------------------
// 
// Filename    : CGRequestInfo.h 
// Written By  : �輺��
// 
//--------------------------------------------------------------------------------

#ifndef __CG_REQUEST_INFO_H__
#define __CG_REQUEST_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"



//--------------------------------------------------------------------------------
//
// class CGRequestInfo;
//
//--------------------------------------------------------------------------------

class CGRequestInfo : public Packet {

public :
	enum REQUEST_INFO_CODE
	{
		REQUEST_CHARACTER_INFO,
		
		REQUEST_INFO_MAX
	};

public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_REQUEST_INFO; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGRequestInfoPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize() const { return szBYTE + szuint; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGRequestInfo"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif
	
public:

	// get / set Code
	BYTE getCode() const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

	// get / set Code
	uint getValue() const { return m_Value; }
	void setValue(uint value) { m_Value = value; }

private :
	
	// Code
	BYTE    m_Code;
	uint    m_Value;

};


//--------------------------------------------------------------------------------
//
// class CGRequestInfoFactory;
//
// Factory for CGRequestInfo
//
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__

class CGRequestInfoFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new CGRequestInfo(); }

	// get packet name
	std::string getPacketName() const { return "CGRequestInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_REQUEST_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGRequestInfoPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + szuint; }

};
#endif

//--------------------------------------------------------------------------------
//
// class CGRequestInfoHandler;
//
//--------------------------------------------------------------------------------
#ifndef __GAME_CLIENT__
class CGRequestInfoHandler {
	
public:

	// execute packet's handler
	static void execute(CGRequestInfo* pPacket, Player* player);
};
#endif

#endif
