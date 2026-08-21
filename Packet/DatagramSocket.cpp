//////////////////////////////////////////////////////////////////////
//
// Filename   : DatagramSocket.cpp
// Written By : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Packet_PCH.h"
#include "DatagramSocket.h"
#include "Assert.h"
#include "FileAPILocal.h"
#include "DebugInfo.h"
//#include "MTestDef.h"

//////////////////////////////////////////////////////////////////////
//
// constructor for UDP Client Socket
//
// UDP Ŭ���̾�Ʈ ������ ���� nonamed ���ϸ� ������ �θ� �ȴ�.
// �ֳ��ϸ�, ������ send�� ������ Datagram�� �ּҸ� �����صθ�
// �Ǳ� �����̴�.
//
//////////////////////////////////////////////////////////////////////
DatagramSocket::DatagramSocket ()
: m_SocketID(INVALID_SOCKET)
{
	__BEGIN_TRY 

	__BEGIN_DEBUG
	m_SocketID = SocketAPI::socket_ex( AF_INET , SOCK_DGRAM , 0 );
	__END_DEBUG

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// constructor for UDP Server Socket
//
// UDP ���� ������ ������ �����ϰ�, port �� ���ε���Ű�� �غ� �Ϸ�ȴ�.
//
//////////////////////////////////////////////////////////////////////
DatagramSocket::DatagramSocket ( uint port )
: m_SocketID(INVALID_SOCKET)
{
	__BEGIN_TRY 

	m_SocketID = SocketAPI::socket_ex( AF_INET , SOCK_DGRAM , 0 );

	// clear memory
	memset( &m_SockAddr , 0 , szSOCKADDR_IN );
	m_SockAddr.sin_family      = AF_INET;
	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_SockAddr.sin_port        = htons(port);

	int opt = 1;
	SocketAPI::setsockopt_ex( m_SocketID, SOL_SOCKET , SO_REUSEADDR , &opt , sizeof(opt) );

	// bind address to socket
	SocketAPI::bind_ex( m_SocketID , (SOCKADDR*)&m_SockAddr , szSOCKADDR_IN );

	// set host
	const char* pIP = inet_ntoa( m_SockAddr.sin_addr );
	int port2 = m_SockAddr.sin_port;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
DatagramSocket::~DatagramSocket ()
{
	__BEGIN_TRY
	
	if ( m_SocketID != INVALID_SOCKET )
	{
		try {
			SocketAPI::closesocket_ex( m_SocketID );
		} catch (Throwable& t) {
			DEBUG_ADD( t.toString().c_str() );
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// send datagram to peer
//////////////////////////////////////////////////////////////////////
uint DatagramSocket::send ( Datagram * pDatagram )
{
	__BEGIN_TRY 

	Assert( pDatagram != NULL );

	int nSent = SocketAPI::sendto_ex( m_SocketID , pDatagram->getData() , pDatagram->getLength() , 0 , pDatagram->getAddress() , szSOCKADDR_IN );

	return (uint)nSent;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// receive datagram from peer
//
// ���࿡ �� Ŭ������ blocking ���� ����Ѵٸ�, (�� select �������)
// �Ƹ��� nReceived �� 0 ������ ���� ��������� �Ǵܵȴ�.
//
//////////////////////////////////////////////////////////////////////
Datagram * DatagramSocket::receive ()
{
	__BEGIN_TRY 

	Datagram * pDatagram = NULL;

	SOCKADDR_IN SockAddr;
	uint _szSOCKADDR_IN = szSOCKADDR_IN;

	// ������ �ִ��� üũ�Ѵ�.
	ulong available = SocketAPI::availablesocket_ex( m_SocketID );		
	
	if (available > 0)
	{
		#ifdef __METROTECH_TEST__
			g_UDPTest.UDPPacketAvailable ++;
		#endif

		DEBUG_ADD_FORMAT("[DatagramSocket] available=%d", available);

		// ���� ���ۿ��ٰ� �����صд�.
		int nReceived = SocketAPI::recvfrom_ex( m_SocketID , m_Buffer , DATAGRAM_SOCKET_BUFFER_LEN , 0 , (SOCKADDR*)&SockAddr , &_szSOCKADDR_IN );

		if ( nReceived > 0 ) 
		{
			#ifdef __METROTECH_TEST__
				g_UDPTest.UDPPacketReceive ++;
			#endif

			DEBUG_ADD_FORMAT("[DatagramSocket] received=%d", nReceived);

			pDatagram = new Datagram();
			pDatagram->setData( m_Buffer , nReceived );
			pDatagram->setAddress( &SockAddr );
		}
	}	

	return pDatagram;

	__END_CATCH
}
