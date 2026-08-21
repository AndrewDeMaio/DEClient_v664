//--------------------------------------------------------------------------------
// ClientCommunicationManager.h
//--------------------------------------------------------------------------------
// Processes the data received from the server packet
//--------------------------------------------------------------------------------

#ifndef __CLIENT_COMMUNICATION_MANAGER_H__
#define __CLIENT_COMMUNICATION_MANAGER_H__

#include <Windows.h>
#include "Types.h"
#include "Exception.h"
#include "DatagramSocket.h"

class Datagram;
class DatagramPacket;

class ClientCommunicationManager {
public:
	ClientCommunicationManager();
	~ClientCommunicationManager();

	//------------------------------------------------------------------
	// Update
	//------------------------------------------------------------------
	void	Update();

	//------------------------------------------------------------------
	// Send
	//------------------------------------------------------------------
	void	sendDatagram(Datagram* pDatagram);
	void	sendPacket(const std::string& host, uint port, DatagramPacket* pPacket);

private:
	// Handle UDP packets
	DatagramSocket* m_pDatagramSocket;
};


extern ClientCommunicationManager* g_pClientCommunicationManager;

#endif
