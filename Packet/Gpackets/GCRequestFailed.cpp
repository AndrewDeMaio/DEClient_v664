//////////////////////////////////////////////////////////////////////////////
// Filename    : GCRequestFailed.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCRequestFailed.h"

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCRequestFailed::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read(m_Code);

	BYTE num;
	iStream.read( num );

	if (num==0)
		throw InvalidProtocolException("szName==0");

	iStream.read(m_Name, num);

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCRequestFailed::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write(m_Code);

	BYTE num = (BYTE)m_Name.size();
	oStream.write( num );

	if (num==0)
		throw InvalidProtocolException("szName==0");

	oStream.write(m_Name);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCRequestFailed::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCRequestFailedHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
std::string GCRequestFailed::toString () const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCRequestFailed(" 
	    << "Code : " << (int)m_Code 
		<< "Name : " << m_Name
		<< ")";
	return msg.toString();

	__END_CATCH
}


#endif