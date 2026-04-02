//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSystemMessage.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSystemMessage.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSystemMessage::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	BYTE szMessage;

	iStream.read( szMessage );

	if ( szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage > 256 )
		throw InvalidProtocolException("too large message length");

	iStream.read( m_Message , szMessage );

	iStream.read( m_Color );

	BYTE t;
	iStream.read( t );
	m_Type = (SystemMessageType)t;

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSystemMessage::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	BYTE szMessage = m_Message.size();

	oStream.write( szMessage );

	if ( szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage > 256 )
		throw InvalidProtocolException("too large message length");

	oStream.write( m_Message );

	oStream.write( m_Color );

	BYTE t = (BYTE)m_Type;
	oStream.write( t );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCSystemMessage::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCSystemMessageHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
std::string GCSystemMessage::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCSystemMessage("
		<< "Type:" << (int)m_Type 
		<< ",Color:" << m_Color 
		<< ",Message:" << m_Message 
		<< ")" ;
	
	return msg.toString();
		
	__END_CATCH
}


