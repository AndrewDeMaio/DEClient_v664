//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRepairInfo.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCRepairInfo.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCRepairInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	iStream.read( m_ItemOID );
	iStream.read( m_RepairPrice );
	iStream.read( m_RepairDiscountPrice );


	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCRepairInfo::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	oStream.write( m_ItemOID );
	oStream.write( m_RepairPrice );
	oStream.write( m_RepairDiscountPrice );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCRepairInfo::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCRepairInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCRepairInfo::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCRepairInfo("
		<< "ObjectID:" << m_ItemOID 
		<< ",RepairPrice:" << m_RepairPrice
		<< ",RepairDiscountPrice:" << m_RepairDiscountPrice 
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


