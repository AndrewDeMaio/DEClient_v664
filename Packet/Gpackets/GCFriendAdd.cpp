//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFriendAdd.cpp 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCFriendAdd.h"

#if __CONTENTS(__FRIEND_ADDITION)
GCFriendAdd::~GCFriendAdd()
{
}

void GCFriendAdd::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	m_FriendSimpleInfo.read(iStream);
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCFriendAdd::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	m_FriendSimpleInfo.write( oStream );

	__END_CATCH
}

PacketSize_t GCFriendAdd::getPacketSize() const 
{ 
	return m_FriendSimpleInfo.getSize(); 
}

void GCFriendAdd::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCFriendAddHandler::execute(this, pPlayer);
		
	__END_CATCH
}

void GCFriendAdd::SetFriendSimpleInfo(FriendSimpleInfo& Info)
{
	m_FriendSimpleInfo = Info;
}

FriendSimpleInfo& GCFriendAdd::GetFriendSimpleInfo()
{
	return m_FriendSimpleInfo;
}

string GCFriendAdd::toString () const
{
	StringStream msg;

	msg << "GCFriendAdd ("
		<< "FriendSimpleInfo:" << m_FriendSimpleInfo.toString() << ")";

	return msg.toString();
}
#endif //__FRIEND_ADDITION
