//--------------------------------------------------------------------------------
//
// Filename    : LCReconnectHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "LCReconnect.h"
#include "ClientDef.h"
#include "ServerInfoFileParser.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CGConnect.h"
	#include "Cpackets/CGPortCheck.h"
	#include "UserInformation.h"
	#include "Properties.h"
	#include "ClientCommunicationManager.h"
#endif

#ifdef OUTPUT_DEBUG
	#include <time.h>

	struct tempStruct
	{
		SYSTEMTIME st;
		DWORD reconnectTickCount;
		DWORD sendCGConnectTickCount;
	};
#endif

extern int g_Dimension;
extern bool		UpdateSocketOutput();
extern BYTE g_macAddress[6];
extern std::string g_GetReconnectIP(const std::string& serverIP);
//--------------------------------------------------------------------------------
// �α��μ����κ��� ���� ������ �ּҿ� ��Ʈ, �׸��� ����Ű�� ���� ���
// ���� ������ ������ ��, ����Ű�� ���� CGConnect ��Ŷ�� �����Ѵ�.
//--------------------------------------------------------------------------------
void LCReconnectHandler::execute ( LCReconnect * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

		/*
#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	// �α��� �������� ������ �����Ѵ�
	// �̶� �α��� ������ LCReconnect ��Ŷ�� �����鼭 ������ �����Ѵٴ� ��ǿ� �����϶�.
	cout << "Disconnecting from login server" << endl;
	pClientPlayer->disconnect();

	// LCReconnect ��Ŷ�� ����ִ� ������ ����ؼ�, ���� ������ �����Ѵ�.
	cout << "Reconnecting to " << pPacket->getGameServerIP() << ":" << pPacket->getGameServerPort() << endl;

	try {

		pClientPlayer->getSocket()->reconnect( pPacket->getGameServerIP() , pPacket->getGameServerPort() );

		// reconnect�ϰ� �Ǹ� ������ ���� ��������� �ȴ�.
		// ����, �� ���� ���� �ɼ��� ���� ��������� �Ѵ�.
		pClientPlayer->getSocket()->setNonBlocking();
		pClientPlayer->getSocket()->setLinger(0);

	} catch ( ConnectException & ce ) {
		throw Error(ce.toString());
	}

	// ������ �̷������, �ٷ� CGConnect ��Ŷ�� �����Ѵ�.
	// ������ Select �� PC�� Ÿ�԰� �̸��� Ŭ���̾�Ʈ �÷��̾� ��ü�� �����صд�.
	cout << "Sending CGConnect with Key(" << pPacket->getKey() << ")" << endl;

	CGConnect cgConnect;
	cgConnect.setKey( pPacket->getKey() );
	cgConnect.setPCType( pClientPlayer->getPCType() );
	cgConnect.setPCName( pClientPlayer->getPCName() );

	pClientPlayer->sendPacket( &cgConnect );
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CG_CONNECT );

#endif
 */
#ifdef OUTPUT_DEBUG
	FILE *fp = NULL;
	DWORD tickCount = 0;


	std::list<struct tempStruct> tempStructList;
	struct tempStruct currentTempStruct;

	fp = fopen("Log\\ConnectTime.txt", "rt");
	if(fp != NULL)
	{
		char readTemp[512];
		fgets(readTemp, 512, fp);
		while(fgets(readTemp, 512, fp) != NULL)
		{
			if(readTemp[0] == 'r')break;
			
			struct tempStruct ts;

			DWORD reconnectTickCount = 0, sendCGConnectTickCount = 0;
			sscanf(readTemp, "%4d/%2d/%2d %2d:%2d:%2d\t%8d\t%8d\n", 
				&ts.st.wYear, &ts.st.wMonth, &ts.st.wDay, &ts.st.wHour, &ts.st.wMinute, &ts.st.wSecond,
				&ts.reconnectTickCount,
				&ts.sendCGConnectTickCount);

			tempStructList.push_back(ts);
		}

		fclose(fp);
	}

// 	fp = fopen("Log\\ConnectTime.txt", "wt");
//	if(fp != NULL)
//	{
// 		fprintf(fp, "CurrentTime\tReconnect TickCount\tSend cgConnect TickCount\n");

		SYSTEMTIME st;
		GetLocalTime(&st);

		currentTempStruct.st = st;
//		fprintf(fp, "%4d/%2d/%2d %2d:%2d:%2d\t", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );
//		fclose(fp);
// 	}
#endif

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	// �α��� �������� ������ �����Ѵ�
	// �̶� �α��� ������ LCReconnect ��Ŷ�� �����鼭 ������ �����Ѵٴ� ��ǿ� �����϶�.
	
	pClientPlayer->disconnect();

	const std::string gameServerIP = g_GetReconnectIP( pPacket->getGameServerIP() );

	DEBUG_ADD_FORMAT("Reconnecting to %s:%d",
										gameServerIP.c_str(),
										pPacket->getGameServerPort());

	try {
#ifdef OUTPUT_DEBUG
		tickCount = timeGetTime();//GetTickCount();
#endif
		pClientPlayer->getSocket()->reconnect( gameServerIP , pPacket->getGameServerPort() );
#ifdef OUTPUT_DEBUG
		currentTempStruct.reconnectTickCount = timeGetTime()-tickCount;
#endif
		// reconnect�ϰ� �Ǹ� ������ ���� ��������� �ȴ�.
		// ����, �� ���� ���� �ɼ��� ���� ��������� �Ѵ�.
		pClientPlayer->getSocket()->setNonBlocking();
		pClientPlayer->getSocket()->setLinger(0);

	} catch ( ConnectException & ce ) {
		throw Error(ce.toString());
	}

	// ������ �̷������, �ٷ� CGConnect ��Ŷ�� �����Ѵ�.
	// ������ Select �� PC�� Ÿ�԰� �̸��� Ŭ���̾�Ʈ �÷��̾� ��ü�� �����صд�.
	DEBUG_ADD_FORMAT("Sending CGConnect with Key(%ld)", 
												pPacket->getKey());

	

	// ������..
	CGConnect cgConnect;
	cgConnect.setKey( pPacket->getKey() );
	cgConnect.setPCType( pClientPlayer->getPCType() );
	cgConnect.setPCName( pClientPlayer->getPCName() );
	cgConnect.setMacAddress( g_macAddress );
	
#ifdef OUTPUT_DEBUG
	tickCount = timeGetTime();
#endif
	pClientPlayer->sendPacket( &cgConnect );
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CG_CONNECT );	

	// �ٷ� ������.
	UpdateSocketOutput();
#ifdef OUTPUT_DEBUG
	currentTempStruct.sendCGConnectTickCount = timeGetTime()-tickCount;
#endif
	
	// 2002.6.28 [UDP����]
	// ������ UDP port�� �˷��ֱ� ���ؼ�
	CGPortCheck cgPortCheck;
	cgPortCheck.setPCName( g_pUserInformation->CharacterID.GetString() );

	std::string ServerAddress;
	uint ServerPort;

	if( g_pUserInformation->bKorean )
	{
		ServerAddress = g_pConfigKorean->getProperty("LoginServerAddress");
		ServerPort = g_pConfigKorean->getPropertyInt("LoginServerCheckPort");
	}
	else
	{
		ServerAddress = g_pConfigForeign->getProperty("LoginServerAddress" );	
		ServerPort = g_pConfigForeign->getPropertyInt("LoginServerCheckPort");
	}
	
				
	DEBUG_ADD("[ ClientPacket] Send CGPortCheck ");
	g_pClientCommunicationManager->sendPacket( ServerAddress,
		ServerPort,
		&cgPortCheck );

	DEBUG_ADD("[ MODE ] START SETMODE MODE_WAIT_UPDATEINFO");
	SetMode( MODE_WAIT_UPDATEINFO );
	DEBUG_ADD("[ MODE ] END SETMODE MODE_WAIT_UPDATEINFO");

#ifdef OUTPUT_DEBUG
 	fp = fopen("Log\\ConnectTime.txt", "wt");
	if(fp != NULL)
	{
		tempStructList.push_back(currentTempStruct);

 		fprintf(fp, "CurrentTime\tReconnect TickCount\tSend cgConnect TickCount\n");
		
		DWORD minReconnectTickCount = 0xffffffff, minCGTickCount = 0xffffffff, maxReconnectTickCount = 0, maxCGTickCount = 0, reconnectSum = 0, CGSum = 0;
		int size = tempStructList.size();

		while(!tempStructList.empty())
		{
			tempStruct ts;
			ts = tempStructList.front();
			tempStructList.pop_front();

			fprintf(fp, "%4d/%2d/%2d %2d:%2d:%2d\t%8d\t%8d\n", 
				ts.st.wYear, ts.st.wMonth, ts.st.wDay, ts.st.wHour, ts.st.wMinute, ts.st.wSecond,
				ts.reconnectTickCount,
				ts.sendCGConnectTickCount);

			if(ts.reconnectTickCount < minReconnectTickCount)minReconnectTickCount = ts.reconnectTickCount;
			if(ts.reconnectTickCount > maxReconnectTickCount)maxReconnectTickCount = ts.reconnectTickCount;
			if(ts.sendCGConnectTickCount < minCGTickCount)minCGTickCount = ts.sendCGConnectTickCount;
			if(ts.sendCGConnectTickCount > maxCGTickCount)maxCGTickCount = ts.sendCGConnectTickCount;

			reconnectSum += ts.reconnectTickCount;
			CGSum += ts.sendCGConnectTickCount;

		}

		fprintf(fp, "reconnect TickCount Min : %d Max : %d Avr : %d\n", minReconnectTickCount, maxReconnectTickCount, reconnectSum/size);
		fprintf(fp, "send cgConnect TickCount Min : %d Max : %d Avr : %d\n", minCGTickCount, maxCGTickCount, CGSum/size);
		fclose(fp);
	}
#endif
	__END_CATCH
}
