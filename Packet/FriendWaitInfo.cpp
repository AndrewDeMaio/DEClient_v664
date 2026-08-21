//////////////////////////////////////////////////////////////////////
// 
// Filename    : 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "Packet_PCH.h"
#include "FriendWaitInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#if __CONTENTS(__FRIEND_ADDITION)
const int FriendWaitInfo::m_iMaxFriendName = 20;

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
FriendWaitInfo::FriendWaitInfo () 
{
	__BEGIN_TRY
	
	m_FriendName.SetMaxLength(20);
	
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
FriendWaitInfo::~FriendWaitInfo () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void FriendWaitInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	m_FriendName.read(iStream);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void FriendWaitInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	m_FriendName.write(oStream);

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t FriendWaitInfo::getSize() const
{
	__BEGIN_TRY

	PacketSize_t PacketSize;
	
	PacketSize = m_FriendName.getSize();
	
	return PacketSize;

	__END_CATCH
}

uint FriendWaitInfo::getMaxSize() 
{
	PacketSize_t PacketSize;
	
	PacketSize =  StringInfo::getMaxSize();
	
	return PacketSize;
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string FriendWaitInfo::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;

	msg << "FriendWaitInfo(" 
		<< "FriendName:" << GetFriendName() 
		<< ")";
	
	return msg.toString();

	__END_CATCH
}
#endif //__FRIEND_ADDITION
