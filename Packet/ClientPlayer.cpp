//--------------------------------------------------------------------------------
// 
// Filename    : ClientPlyaer.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------


// include files
#include "Client_PCH.h"
#include "ClientPlayer.h"
#include "Assert.h"
#include "Packet.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "ClientConfig.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "DebugInfo.h"
//#include "MPlayer.h"
#include "MZone.h"
#include "UserInformation.h"
//#include "minTR.H" 
#include <fstream>
//#include "AutoQA/AutoQA.h"

#if __CONTENTS(__CRYPT)
#include "Crypt.h"
#endif //__CRYPT

#ifdef OUTPUT_DEBUG


// �׽�Ʈ �ڵ�
#if __CONTENTS(__AUTO_ITEM_ROOTING)
	#include "MPlayer.h"
	#include "packet\CPackets\CGSay.h"

	extern MPlayer*			g_pPlayer;
	extern ClientPlayer*	g_pSocket;
#endif //__AUTO_ITEM_ROOTING

// ��Ŷ�� �ʴ� ���ŷ��� ���ϱ� ���� �Ҽ����� - chyaya
class CComputPacketRecvForSec
{
public:
	CComputPacketRecvForSec();
	~CComputPacketRecvForSec();

public:
	void OnPacketRecv(DWORD dwBytes)
	{ m_dwSumOfRecvByte += dwBytes;	}

private:
	DWORD	m_dwStatingTick;
	DWORD	m_dwSumOfRecvByte;

}; // class CComputPacketRecvForSec End

CComputPacketRecvForSec::CComputPacketRecvForSec()
	: m_dwStatingTick(GetTickCount()), m_dwSumOfRecvByte(0)
{

}

CComputPacketRecvForSec::~CComputPacketRecvForSec()
{
	std::ofstream file("Log\\RecvByteForSec.log", std::ios_base::out | std::ios_base::app);

	DWORD	dwTickGap = GetTickCount() - m_dwStatingTick;

	double	dbRecvByteForSec = ( m_dwSumOfRecvByte / (double)dwTickGap ) * 1000.0;

	file	<< "SEC="<< dwTickGap/1000.0f
			<< "\tBYTE=" << m_dwSumOfRecvByte
			<< "\tBYTE/SEC= " << dbRecvByteForSec << '\n';
}

#endif


void	SendBugReport(const char *bug, ...);
//--------------------------------------------------------------------------------
//
// constructor
//
//--------------------------------------------------------------------------------
ClientPlayer::ClientPlayer ( Socket * pSocket )
: m_PlayerStatus(CPS_NONE)
{
	__BEGIN_TRY
		
	Assert( pSocket != NULL );
	m_pSocket = pSocket;

#ifdef __USE_ENCRYPTER__
	// create socket input stream
	m_pInputStream = new SocketEncryptInputStream( m_pSocket, 32768 );

	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SocketEncryptOutputStream( m_pSocket, 32768 );

	Assert( m_pOutputStream != NULL );
#else
	// create socket input stream
	m_pInputStream = new SocketInputStream( m_pSocket, 32768 );

	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SocketOutputStream( m_pSocket, 32768 );

	Assert( m_pOutputStream != NULL );
#endif
	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// destructor
//
//--------------------------------------------------------------------------------
ClientPlayer::~ClientPlayer ()
{
	__BEGIN_TRY
		
	// �� � �÷��̾� ��ü�� ������ ������, �� ���´� �α׾ƿ��̾�� �Ѵ�.
	// �� � �÷��̾ ���� ���� ��Ű����, �� ���¸� �α׾ƿ����� ������ �Ѵ�.
	Assert( m_PlayerStatus == CPS_END_SESSION );

	// delete all previous packets
	while ( ! m_PacketHistory.empty() ) {
		Packet * pPacket = m_PacketHistory.front();
		delete pPacket;
		m_PacketHistory.pop_front();
	}
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// parse packet and execute handler for the packet
//
//--------------------------------------------------------------------------------
void ClientPlayer::processCommand ()
{
	__BEGIN_TRY

	Packet * pPacket;
#if __CONTENTS(__CRYPT)
	PACKETDATA pData;
	pData.m_wMsgSize = 0;
#endif

	try {
		try {

			// ����� �ӽ������� ���� ����
			//char header[szPacketHeader];
			PacketID_t packetID = 0;
			PacketSize_t packetSize = 0;		
			pPacket = NULL;

			//---------------------------------------------------------
			// �̹� Loop���� ó���� packet�� ����
			//---------------------------------------------------------
			// packet�� �ʹ� ���� ���.. 
			// �� ó���ϴٺ��� .. �ð��� ���� �ɷ��� client�� �� ���ư���
			// �׷��� ���� ������ ó���Ѵ�.
			//---------------------------------------------------------
			int maxProcessPacket = g_pClientConfig->MAX_PROCESS_PACKET;
			int processedPacket = 0;
 
			// �Է¹��ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
			while ( true ) {
			
				// �Է½�Ʈ������ ��Ŷ���ũ�⸸ŭ �о��.
				// ���� ������ ũ�⸸ŭ ��Ʈ������ ���� �� ���ٸ�,
				// Insufficient ���ܰ� �߻��ϰ�, ������ ����������.
#if __CONTENTS(__CRYPT)
				m_pInputStream->peek((char*)&pData , szPacketHeader);
#else
				m_pInputStream->peek( header , szPacketHeader );
#endif

#if __CONTENTS(__CRYPT)
            m_pInputStream->DecryptHeader(&pData); // �켱 ����� ��ũ��Ʈ �Ѵ�.
       		packetSize = pData.m_wMsgSize;

            packetID = pData.m_wMsgType;
#else
			// ��Ŷ���̵� �� ��Ŷũ�⸦ �˾Ƴ���.
			// �̶� ��Ŷũ��� ����� �����Ѵ�.
			memcpy( &packetID   , &header[0] , szPacketID ); 	
			memcpy( &packetSize , &header[szPacketID] , szPacketSize );
#endif
			
#ifdef __DEBUG_OUTPUT__
				std::ofstream file("templog.log", std::ios::out | std::ios::app);
				file << "*** RECEIVED PacketID=" << packetID << ", PacketSize=" << packetSize << std::endl;
				file.close();
#endif
				//#ifdef	__DEBUG_OUTPUT__
					//	DEBUG_ADD_FORMAT("ID=%d (%s), size=%d", packetID, g_pPacketFactoryManager->getPacketName( packetID ), packetSize);
				//#else
					//	DEBUG_ADD_FORMAT("ID=%d, size=%d", packetID, packetSize);
				//#endif

				// ��Ŷ ���̵� �̻��ϸ� �������� ������ �����Ѵ�.

// �׽�Ʈ �ڵ�
#if __CONTENTS(__AUTO_ITEM_ROOTING)
//				if(g_pZone != NULL)
//				{
//					if(strstr(g_pPlayer->arrchRootingTest, "*command autoItemRooting"))
//					{
//						if(g_CurrentFrame % 320 == 0)
//						{
//							CGSay _CGSay;
//							_CGSay.setMessage( g_pPlayer->arrchSummon );//+ 1 );	//pWansungString+1 );
//							_CGSay.setColor( 0 );
//							g_pSocket->sendPacket( &_CGSay );
//						}
//					}
//				}
#endif // __AUTO_ITEM_ROOTING
				DEBUG_ADD_FORMAT_ERR("*** RECEIVED PacketID=%d, Size=%d",  (int)packetID, (int)packetSize);
				if ( packetID >= Packet::PACKET_MAX ) 
				{					
					DEBUG_ADD_FORMAT_ERR("[PacketError-ClientPlayer::processCommand] exceed MAX=%d. packetID=%d", Packet::PACKET_MAX, packetID);
					SendBugReport("Exceed PacketID:%d",packetID);
					
					throw InvalidProtocolException("[PacketError-ClientPlayer::processCommand] exceed MAX packetID");
				}

				

				#ifdef __DEBUG_OUTPUT__
					DEBUG_ADD_FORMAT("[RECEIVE] [ID=%d] %s", packetID, g_pPacketFactoryManager->getPacketName(packetID).c_str());
				#endif
				
				BOOL bExecute = TRUE;

				try {
					if ( ! g_pPacketValidator->isValidPacketID( getPlayerStatus() , packetID ) )
					{
						//---------------------------------------------------------------
						// Logout�ؼ� ĳ���� ����ȭ������ ���� ���
						//---------------------------------------------------------------
						if (getPlayerStatus()==CPS_WAITING_FOR_GC_RECONNECT_LOGIN)
						{
							DEBUG_ADD_ERR("[PacketError] ignore Packet when RECONNECT");

							// �о�� execute�� ���� �ʴ´�.
							bExecute = FALSE;
							
							// ������.. ����~~ -_-;
							maxProcessPacket = 0xFFFF;
						}
						//---------------------------------------------------------------
						// �Ϲ����� ���� ������ ���´�.
						//---------------------------------------------------------------
						else
						{
							throw InvalidProtocolException("invalid packet ORDER");
						}				
					}
				//} catch (InvalidProtocolException& t) {
				} catch (IgnorePacketException& t)	{
					
					DEBUG_ADD_ERR(t.toString().c_str());

					bExecute = FALSE;
				}
				
				// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
				if ( packetSize > g_pPacketFactoryManager->getPacketMaxSize( packetID ) )
				{
					DEBUG_ADD_FORMAT_ERR("[PacketError] too large packet SIZE: %d/%d", (int)packetSize, (int)g_pPacketFactoryManager->getPacketMaxSize( packetID ));		
					SendBugReport("too large PacketSize ID)%d %d/%d", packetID, packetSize, g_pPacketFactoryManager->getPacketMaxSize( packetID ) );
					throw InvalidProtocolException("too large packet SIZE");
				}
				
				// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
				// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
				if ( m_pInputStream->length() < szPacketHeader + packetSize )
				{
					DEBUG_ADD_FORMAT_ERR("[PacketError] InsufficientDataException: %d/%d", m_pInputStream->length(), szPacketHeader + packetSize);
		
					throw InsufficientDataException();
				}

/*#if __CONTENTS(__CRYPT)
			if(pData.m_wMsgSize > 0)
			{
				if(pData.m_wMsgSize > 10000)
				{
//					cout << "pData.m_wMsgSize > 10000" << endl;
				}

	            pData.m_Buffer = new char[pData.m_wMsgSize];
				m_pInputStream->peek(pData.m_Buffer , pData.m_wMsgSize, MSG_HEADER_SIZE);
			}


            if(!g_pCryptManager->Decrypt(&pData))
            {
//                filelog("CryptError.txt", "Packet Decrypt Error, RECV ID[%s],Host[%s]",
//                   m_ID.c_str(),
//                    getSocket()->getHost().c_str());

                throw InvalidProtocolException("Packet Decrypt Error");
            }
            m_pInputStream->Replace(&pData, (pData.m_wMsgSize + MSG_HEADER_SIZE));
#endif*/

				#ifdef OUTPUT_DEBUG
				// ��Ŷ�� �ʴ� ���ŷ��� ���ϱ� ���� �Ҽ����� - chyaya
				static CComputPacketRecvForSec ComputPacketRecvForSec;
				ComputPacketRecvForSec.OnPacketRecv(szPacketHeader + packetSize);				
				#endif
				
				// ������� �Դٸ� �Է¹��ۿ��� ������ ��Ŷ �ϳ� �̻��� ����ִٴ� ���̴�.
				// ��Ŷ���丮�Ŵ����κ��� ��Ŷ���̵� ����ؼ� ��Ŷ ��Ʈ��ó�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ���丮�Ŵ������� ó���Ѵ�.
				pPacket = g_pPacketFactoryManager->createPacket( packetID );

				// ���� �� ��Ŷ��Ʈ��ó�� �ʱ�ȭ�Ѵ�.
				// ��Ŷ����Ŭ������ ���ǵ� read()�� virtual ��Ŀ���� ���ؼ� ȣ��Ǿ�
				// �ڵ������� �ʱ�ȭ�ȴ�.
				m_pInputStream->read( pPacket );
/*#if __CONTENTS(__CRYPT)
				if(pData.m_wMsgSize > 0)
				{
					if(iMod > 0)
						m_pInputStream->skip( sizeof(DWORD));
					if(m_pInputStream->length() > 0)
					{
						int adf = 0;
					}
					delete [] pData.m_Buffer;
				}
#endif */

				
				// ���� �� ��Ŷ��Ʈ��ó�� ������ ��Ŷ�ڵ鷯�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ�ڵ鷯�Ŵ������� ó���Ѵ�.			

				if (bExecute)
				{
					#ifdef __DEBUG_OUTPUT__
						DEBUG_ADD(pPacket->toString().c_str());
					#endif

//					_MinTrace("Incomming Packet ID : %d\n",pPacket->getPacketID());

					pPacket->execute( this );

	//				aqa::Robot::Instance().PacketExcuted(pPacket->getPacketID());					

					//DEBUG_ADD_FORMAT("[Executed] %s", pPacket->toString().c_str());
					DEBUG_ADD("[PacketExecute OK]");				
				}
				
				
				// ���� ��Ŷ�� ��Ŷ �����丮�� �� �ڿ� �ִ´�.
				m_PacketHistory.push_back(pPacket);
				pPacket = NULL;

				// ��Ŷ�� nPacketHistory ����ŭ�� �����Ѵ�.
				while ( m_PacketHistory.size() > nPacketHistory ) {
					Packet * oldPacket = m_PacketHistory.front();
					delete oldPacket;
					m_PacketHistory.pop_front();
				}
				DEBUG_ADD("[PacketExecute OK2]");
				
				//---------------------------------------------------------	
				// �ѹ��� ó���ϴ� packet�� �Ѱ� ������ �Ѿ ���
				// �������� ���� turn�� ó���Ѵ�.
				//---------------------------------------------------------
				if (++processedPacket > maxProcessPacket)
				{
					DEBUG_ADD_FORMAT("[PacketSkip] So many Packets. MaxProcessPacket:%d, CurrentPacket:%d, File:%s, Line:%s",maxProcessPacket,processedPacket, __FILE__,__LINE__);
					//DEBUG_ADD_FORMAT_WAR(szBuf);

					break;
				}			
			}

		} catch ( InsufficientDataException& ) {

			// ���� ������ Ż�� ������ ���̴�. ������ ������ �ʿ�� ����.
		}

	} catch (Throwable&)	{
		
		if (pPacket!=NULL)
		{
			delete pPacket;
			pPacket = NULL;
		}

		throw;
	}

	__END_CATCH
}
		    

//--------------------------------------------------------------------------------
// disconnect player
//--------------------------------------------------------------------------------
void ClientPlayer::disconnect ( bool bDisconnected )
{
	__BEGIN_TRY

	if ( bDisconnected == UNDISCONNECTED ) {

		// Ŭ���̾�Ʈ���� GCDisconnect ��Ŷ�� �����Ѵ�.
		//GCDisconnect gcDisconnect;
		//sendPacket( gcDisconnect );

		// ��� ���ۿ� �����ִ� ����Ÿ�� �����Ѵ�.
		try {
			m_pOutputStream->flush();
		} catch (ConnectException& t)	{
			DEBUG_ADD_ERR(t.toString().c_str());
		} catch (Throwable& t) {
			DEBUG_ADD_ERR(t.toString().c_str());
		}

	}

	// ���� ������ �ݴ´�.
	try {
		m_pSocket->close();
	} catch (Throwable& ) {
		// �׳� ����
	}

	// �÷��̾��� ���¸� �α׾ƿ����� �����.
	//cout<< "PlayerStatus : " << (int)m_PlayerStatus << endl;
	// 2001.10.5 �ּ�ó�� ..����..
	//Assert( m_PlayerStatus != CPS_END_SESSION );
	m_PlayerStatus = CPS_END_SESSION;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// �ֱ� N ��°�� ��Ŷ�� �����Ѵ�.
// 
// N == 0 �� ���, ���� �ֱ��� ��Ŷ�� �����ϰ� �ȴ�.
//
// �ִ� nPacketHistory - 1 ���� ������ �� �ִ�. 
//
//--------------------------------------------------------------------------------
Packet * ClientPlayer::getOldPacket ( uint prev )
{
	__BEGIN_TRY

	if ( prev >= nPacketHistory )
		throw OutOfBoundException();

	// if prev == 0 , return m_PacketHistory[9]
	// if prev == 9 , return m_PacketHistory[0]
	Packet * pPacket = m_PacketHistory[ nPacketHistory - prev - 1 ];

	if ( pPacket == NULL )
		throw NoSuchElementException("packet history is empty");

	return pPacket;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// Ư�� ��Ŷ���̵� ���� ���� �ֱ��� ��Ŷ�� �����Ѵ�.
//
//--------------------------------------------------------------------------------
Packet * ClientPlayer::getOldPacket ( PacketID_t packetID )
{
	__BEGIN_TRY

	Packet * pPacket = NULL;

	for ( std::deque<Packet*>::reverse_iterator ritr = m_PacketHistory.rbegin() ;
			ritr != m_PacketHistory.rend() ;
			ritr ++ ) {
		if ( (*ritr)->getPacketID() == packetID ) {
			pPacket = (*ritr);
			break;
		}	
	}

	if ( pPacket == NULL )
		throw NoSuchElementException();

	return pPacket;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// get debug std::string
//
//--------------------------------------------------------------------------------
std::string ClientPlayer::toString () const

{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "ClientPlayer("
		<< "SocketID:" << (uint)m_pSocket->getSOCKET()
		<< ",Host:" << m_pSocket->getHost()
		<< ")" ;

	return msg.toString();

	__END_CATCH
}



// ��ȣȭ �ڵ带 �����Ѵ�.

void ClientPlayer::setEncryptCode()
{
#ifdef __USE_ENCRYPTER__
    __BEGIN_TRY

//	Assert(g_pPlayer!=NULL);
	Assert(g_pZone!=NULL);

	// �ϴ��� ObjectID�� �̿��Ѵ�.
//	ObjectID_t objectID = g_pPlayer->GetID();
	ZoneID_t zoneID = g_pZone->GetID();
	int serverID = g_pUserInformation->ServerID;

//	if (objectID!=0)
	{
//		uchar code = (uchar)(objectID / zoneID + objectID);		
		uchar code;

		if( g_pUserInformation->IsNetmarble )
			code = (uchar)( ( ( ( zoneID ) >> 8 ) ^ ( zoneID ) ) ^ ( ( ( serverID ) + 1 ) << 4 ) );
//		else if ( g_pUserInformation->bChinese )
//			code = (uchar) ( ( ( ( ( serverID ) + 1 ) << 4 ) | ( zoneID ) ) ^ ( ( zoneID ) >> 8 ) );
//			code = (uchar)( ( ( ( zoneID ) >> 8 ) ^ ( zoneID ) ) ^ ( ( ( serverID ) + 1 ) << 4 ) );
		else if ( g_pUserInformation->bEnglish )
			code = (uchar)( ( ( ( zoneID ) >> 8 ) ^ ( zoneID ) ) ^ ( ( ( serverID ) + 1 ) * 51 ) );
		else
			code = (uchar)( ( ( ( zoneID ) >> 8 ) ^ ( zoneID ) ) ^ ( ( ( serverID ) + 1 ) << 4 ) );

		SocketEncryptOutputStream* pEOS = dynamic_cast<SocketEncryptOutputStream*>(m_pOutputStream);
		Assert(pEOS!=NULL);

		SocketEncryptInputStream* pEIS = dynamic_cast<SocketEncryptInputStream*>(m_pInputStream);
		Assert(pEIS!=NULL);

		pEOS->setEncryptCode(code);
		pEIS->setEncryptCode(code);
	}

	__END_CATCH
#endif
}
