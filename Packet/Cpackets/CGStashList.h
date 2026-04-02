////////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashList.h 
// Written By  : �輺��
// Description : 
// Ŭ���̾�Ʈ�� ������ �ȿ� ����ִ� �������� ����Ʈ�� �䱸�� �� ���̴�
// ��Ŷ�̴�. 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_STASH_LIST_H__
#define __CG_STASH_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashList;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashList : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_CG_STASH_LIST; }
	size_t getPacketSize () const { return szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGStashList"; }
		std::string toString () const;
	#endif

public:
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID(ObjectID_t id) { m_ObjectID = id; }

private:
	ObjectID_t m_ObjectID; // �÷��̾� ũ������ object id

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashListFactory;
//
// Factory for CGStashList
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGStashListFactory : public PacketFactory 
{
public :
	Packet * createPacket () { return new CGStashList(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGStashList"; }
	#endif	

	PacketID_t getPacketID () const { return Packet::PACKET_CG_STASH_LIST; }
	PacketSize_t getPacketMaxSize () const { return szObjectID; }

};
#endif

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashListHandler;
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGStashListHandler 
	{
	public :
		static void execute ( CGStashList * pPacket , Player * player );

	};
#endif

#endif
