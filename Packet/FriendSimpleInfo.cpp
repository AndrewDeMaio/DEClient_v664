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
#include "Client_PCH.h"
#include "FriendSimpleInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#if __CONTENTS(__FRIEND_ADDITION)
//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
FriendSimpleInfo::FriendSimpleInfo () 
{
	__BEGIN_TRY
	
	m_FriendName.SetMaxLength(20);
	m_ServerName.SetMaxLength(20);
	
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
FriendSimpleInfo::~FriendSimpleInfo () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void FriendSimpleInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	m_FriendName.read(iStream);
	iStream.read( m_bConnect );
	m_ServerName.read(iStream);
	iStream.read( m_ZoneID );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void FriendSimpleInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	m_FriendName.write(oStream);
	oStream.write( m_bConnect );
	m_ServerName.write(oStream);	
	oStream.write( m_ZoneID );
	

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t FriendSimpleInfo::getSize() const
{
	__BEGIN_TRY

	PacketSize_t PacketSize;
	
	PacketSize = 
		m_FriendName.getSize() + 
		szBYTE + 
		m_ServerName.getSize() +
		sizeof(m_ZoneID);
	
	return PacketSize;

	__END_CATCH
}

uint FriendSimpleInfo::getMaxSize() 
{
	PacketSize_t PacketSize;
	
	PacketSize =  
			StringInfo::getMaxSize() + 
			szBYTE + 
			StringInfo::getMaxSize() +
			sizeof(ZoneID_t);
	
	return PacketSize;
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string FriendSimpleInfo::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;

	msg << "FriendSimpleInfo(" 
		<< "FriendName:" << m_FriendName.toString() << ","
		<< "Connect:" << GetConnect() << ","
		<< "ServerName:" << m_ServerName.toString() << ","
		<< "ZoneID:" << GetZoneID()
		<< ")";
	
	return msg.toString();

	__END_CATCH
}
#endif //__FRIEND_ADDITION
