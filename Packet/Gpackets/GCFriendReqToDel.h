//----------------------------------------------------------------------
// 
// Filename    : GCFriendReqToDel.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GC_FRIEND_REQ_TO_DEL_H__
#define __GC_FRIEND_REQ_TO_DEL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

#if __CONTENTS(__FRIEND_ADDITION)
class GCFriendReqToDel : public Packet {

public:
	virtual ~GCFriendReqToDel() {}
	
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);

	PacketID_t getPacketID() const { return PACKET_GC_FRIEND_REQ_TO_DEL; }
	size_t getPacketSize() const
	{ 
		return szBYTE + m_strPCName.size();
	}

	string getPacketName() const { return "GCFriendReqToDel"; }
	string toString() const;

public:
	enum ResultCode
	{
		RESULT_SUCCESS = 0,
		RESULT_UNKNOWN_ERROR,		
		RESULT_NOT_EXIST			// �������� �ʴ� ĳ������
	};

	string& getPCName() { return m_strPCName; }
	void setPCName(const string& strPCName) { m_strPCName = strPCName; }
	
	ResultCode getResult() { return (ResultCode)m_Result; }
	void setResult(ResultCode result) { m_Result = (BYTE)result; }

private :
	string m_strPCName;		// ��û�� ĳ���� �̸�
	BYTE m_Result;			// ��û ���

};


//////////////////////////////////////////////////////////////////////
//
// class GCFriendReqToDelFactory;
//
// Factory for GCFriendReqToDel
//
//////////////////////////////////////////////////////////////////////

class GCFriendReqToDelFactory : public PacketFactory {

public:
	
	Packet* createPacket() { return new GCFriendReqToDel(); }
	string getPacketName() const { return "GCFriendReqToDel"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_FRIEND_REQ_TO_DEL; }

	PacketSize_t getPacketMaxSize() const 
	{ 
		return szBYTE + 20;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFriendReqToDelHandler {
	
public:

	// execute packet's handler
	static void execute(GCFriendReqToDel* pPacket, Player* pPlayer);

};
#endif //__FRIEND_ADDITION

#endif
