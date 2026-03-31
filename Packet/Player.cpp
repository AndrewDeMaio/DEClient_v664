//////////////////////////////////////////////////////////////////////
// 
// Filename    : Plyaer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : �÷��̾� ���̽� Ŭ����
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "Player.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"
#include "Packet.h"
#include "PacketFactoryManager.h"
#include "DebugInfo.h"

void	SendBugReport(const char *bug, ...);

//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
Player::Player ()
: m_pSocket(NULL), m_pInputStream(NULL), m_pOutputStream(NULL)
{
	__BEGIN_TRY

	Assert( m_pSocket == NULL );

	// create socket input stream
	m_pInputStream = NULL;

	Assert( m_pInputStream == NULL );
	
	// create socket output stream
	m_pOutputStream = NULL;

	Assert( m_pOutputStream == NULL );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
Player::Player ( Socket * pSocket )
: m_pSocket(pSocket), m_pInputStream(NULL), m_pOutputStream(NULL)
{
	__BEGIN_TRY
		
	Assert( m_pSocket != NULL );

	// create socket input stream
	m_pInputStream = new SocketInputStream( m_pSocket, 32768 );

	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SocketOutputStream( m_pSocket, 32768 );

	Assert( m_pOutputStream != NULL );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
Player::~Player ()
{
	__BEGIN_TRY
		
	// delete socket input stream
	if ( m_pInputStream != NULL ) {
		delete m_pInputStream;
		m_pInputStream = NULL;
	}

	// delete socket output stream
	if ( m_pOutputStream != NULL ) {
		delete m_pOutputStream;
		m_pOutputStream = NULL;
	}

	// delete socket
	if ( m_pSocket != NULL ) {
		m_pSocket->close();
		delete m_pSocket;
		m_pSocket = NULL;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////
void Player::processInput ()
{
	__BEGIN_TRY

	try {
		m_pInputStream->fill();
	} catch ( NonBlockingIOException ) {
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void Player::processCommand ()
{
	__BEGIN_TRY

	try {

		// ����� �ӽ������� ���� ����
		char header[szPacketHeader];
		PacketID_t packetID;
		PacketSize_t packetSize;
		Packet * pPacket;

		// �Է¹��ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
		while ( true ) {
		
			// �Է½�Ʈ������ ��Ŷ���ũ�⸸ŭ �о��.
			// ���� ������ ũ�⸸ŭ ��Ʈ������ ���� �� ���ٸ�,
			// Insufficient ���ܰ� �߻��ϰ�, ������ ����������.
			m_pInputStream->peek( header , szPacketHeader );

			// ��Ŷ���̵� �� ��Ŷũ�⸦ �˾Ƴ���.
			// �̶� ��Ŷũ��� ����� �����Ѵ�.
			memcpy( &packetID   , &header[0] , szPacketID );	
			memcpy( &packetSize , &header[szPacketID] , szPacketSize );

			// ��Ŷ ���̵� �̻��ϸ� �������� ������ �����Ѵ�.
			if ( packetID >= Packet::PACKET_MAX )
				throw InvalidProtocolException("[Player::processCommand]invalid packet id");
			
			// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
			if ( packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID) )
			{
				SendBugReport("too large PacketSize ID)%d %d/%d", packetID, packetSize, g_pPacketFactoryManager->getPacketMaxSize( packetID ) );
				throw InvalidProtocolException("too large packet size");
			}
			
			// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
			// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
			if ( m_pInputStream->length() < szPacketHeader + packetSize )
				throw InsufficientDataException();
			
			// ������� �Դٸ� �Է¹��ۿ��� ������ ��Ŷ �ϳ� �̻��� ����ִٴ� ���̴�.
			// ��Ŷ���丮�Ŵ����κ��� ��Ŷ���̵� ����ؼ� ��Ŷ ��Ʈ��ó�� �����ϸ� �ȴ�.
			// ��Ŷ���̵� �߸��� ���� ��Ŷ���丮�Ŵ������� ó���Ѵ�.
			pPacket = g_pPacketFactoryManager->createPacket( packetID );

			// ���� �� ��Ŷ��Ʈ��ó�� �ʱ�ȭ�Ѵ�.
			// ��Ŷ����Ŭ������ ���ǵ� read()�� virtual ��Ŀ���� ���ؼ� ȣ��Ǿ�
			// �ڵ������� �ʱ�ȭ�ȴ�.
			m_pInputStream->read( pPacket );
			
			// ���� �� ��Ŷ��Ʈ��ó�� ������ ��Ŷ�ڵ鷯�� �����ϸ� �ȴ�.
			// ��Ŷ���̵� �߸��� ���� ��Ŷ�ڵ鷯�Ŵ������� ó���Ѵ�.
			pPacket->execute( this );
			
			// ��Ŷ�� �����Ѵ�
			delete pPacket;

		}

	} catch ( NoSuchElementException & nsee ) {

		// PacketFactoryManager::createPacket(PacketID_t)
		// PacketFactoryManager::getPacketMaxSize(PacketID_t)
		// ���� ���� ���ɼ��� �ִ�.
		throw Error( nsee.toString() );

	} catch ( InsufficientDataException ) {

		// do nothing

	} 

	__END_CATCH
}
		    

//////////////////////////////////////////////////////////////////////
//
// flush output buffer to socket's send buffer
//
//////////////////////////////////////////////////////////////////////
void Player::processOutput ()
{
	__BEGIN_TRY

	m_pOutputStream->flush();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void Player::sendPacket ( Packet * pPacket )
{
	__BEGIN_TRY

	#ifdef __DEBUG_OUTPUT__
		DEBUG_ADD_FORMAT("[Send] %s", pPacket->toString().c_str() );							
	#endif
//Test - ������ ��Ŷ ����Ʈ
//	std::ofstream file("DebugInfo.log", std::ios::out | std::ios::app);
//	file << "SendPacket = " << pPacket->toString().c_str() << std::endl;
//	file.close();
//--
	m_pOutputStream->write( pPacket );
#if __CONTENTS(__CRYPT)
	m_pOutputStream->flush();
#endif
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// disconnect ( close socket )
//
//////////////////////////////////////////////////////////////////////
void Player::disconnect ( bool bDisconnected )
{
	__BEGIN_TRY

	// �����ϰ� �α׾ƿ��� ��쿡�� ��� ���۸� �÷����� �� �ִ�.
	// �׷���, �ҹ����� �𽺸� �ɾ��ٸ� ������ �ݰ����Ƿ�
	// �÷����� ��� SIG_PIPE �� �ް� �ȴ�.
	if ( bDisconnected == UNDISCONNECTED ) {

		//
		m_pOutputStream->flush();

	}

	m_pSocket->close();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// set socket
//////////////////////////////////////////////////////////////////////
void Player::setSocket ( Socket * pSocket )
{
	__BEGIN_TRY

	m_pSocket = pSocket;

	if ( m_pInputStream != NULL ) {
		delete m_pInputStream;
		m_pInputStream = new SocketInputStream( m_pSocket );
	}

	if ( m_pOutputStream != NULL ) {
		delete m_pOutputStream;
		m_pOutputStream = new SocketOutputStream( m_pSocket );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
std::string Player::toString () const

{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "Player("
		<< "SocketID:" << (uint)m_pSocket->getSOCKET()
		<< ",Host:" << m_pSocket->getHost()
		<< ",ID:" << m_ID
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
