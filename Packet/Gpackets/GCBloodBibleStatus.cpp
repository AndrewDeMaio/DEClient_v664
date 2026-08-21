//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodBibleStatus.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
// include files
#include "GCBloodBibleStatus.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCBloodBibleStatus::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_ItemType );
	iStream.read( m_ZoneID );
	iStream.read( m_Storage );
	iStream.read( m_Race );
	iStream.read( m_ShrineRace );
	iStream.read( m_X );
	iStream.read( m_Y );

	BYTE szOwnerName;
	iStream.read( szOwnerName );
	if ( szOwnerName > 256 )
		throw InvalidProtocolException("too large message length");

	if (szOwnerName>0)
	{
		iStream.read( m_OwnerName , szOwnerName );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCBloodBibleStatus::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	oStream.write( m_ItemType );
	oStream.write( m_ZoneID );
	oStream.write( m_Storage );
	oStream.write( m_Race );
	oStream.write( m_ShrineRace );
	oStream.write( m_X );
	oStream.write( m_Y );

	BYTE szOwnerName = (BYTE)m_OwnerName.size();
	oStream.write( szOwnerName );
	if ( szOwnerName > 256 )
		throw InvalidProtocolException("too large message length");

	if (szOwnerName>0)
	{
		oStream.write( m_OwnerName );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCBloodBibleStatus::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCBloodBibleStatusHandler::execute( this , pPlayer );

	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////
std::string GCBloodBibleStatus::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCBloodBibleStatus("
		<< "ItemType=" << (int)m_ItemType
		<< ",ZoneID=" << (int)m_ZoneID
		<< ",Storage=" << (int)m_Storage
		<< ",OwnerName=" << m_OwnerName.c_str()
		<< ",Race=" << (int)m_Race
		<< ",ShrineRace=" << (int)m_ShrineRace
		<< ",X=" << (int)m_X
		<< ",Y=" << (int)m_Y
		<< ")";

	return msg.toString();
		
	__END_CATCH
}
#endif

