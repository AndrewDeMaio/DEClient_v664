//////////////////////////////////////////////////////////////////////
// 
// Filename    : RCRequestedFile.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __RC_REQUESTED_FILE_H__
#define __RC_REQUESTED_FILE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "../types/RequestTypes.h"

class RCRequestedFileInfo
{
public :
	RCRequestedFileInfo();

   // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// get packet's body size
	size_t getPacketSize () const { return szBYTE + 4 + szBYTE + m_Filename.size() + 4; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "RCRequestedFile"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get/set RequestFileType
	REQUEST_FILE_TYPE getRequestFileType () const { return m_RequestFileType; }
	void setRequestFileType ( REQUEST_FILE_TYPE RequestFileType ) { m_RequestFileType = RequestFileType; }

	// get/set version
	DWORD getVersion () const { return m_Version; }
	void setVersion ( DWORD version ) { m_Version = version; }
	
	// get/set filename
	const std::string& getFilename () const { return m_Filename; }
	void setFilename ( const std::string & filename ) { m_Filename = filename; }

	// get/set filesize
	DWORD getFileSize () const { return m_FileSize; }
	void setFileSize ( DWORD filesize ) { m_FileSize = filesize; }	
	
private :

	REQUEST_FILE_TYPE		m_RequestFileType;
	DWORD					m_Version;
	std::string					m_Filename;		// �ٿ�޾ƾ� �� ���ϸ�
	DWORD					m_FileSize;		// ���� ũ��
};

//////////////////////////////////////////////////////////////////////
//
// class RCRequestedFile;
//
// ���� ������ Ư�� �÷��̾��� Whisper �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� Whisper ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class RCRequestedFile : public Packet {

public :
	
	RCRequestedFile();
	~RCRequestedFile();

	void	Release();

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_RC_REQUESTED_FILE; }
	
	// get packet's body size
	size_t getPacketSize () const;

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "RCRequestedFile"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	DWORD getListNum () const { return m_FileInfos.size(); }
	
	void	addInfo(RCRequestedFileInfo* pInfo)	{ m_FileInfos.push_back( pInfo ); }
	RCRequestedFileInfo* popInfo()	{ if (m_FileInfos.empty()) return NULL; RCRequestedFileInfo* pInfo = m_FileInfos.front(); m_FileInfos.pop_front(); return pInfo; }
	
private :

	std::list<RCRequestedFileInfo*>	m_FileInfos;
};


//////////////////////////////////////////////////////////////////////
//
// class RCRequestedFileFactory;
//
// Factory for RCRequestedFile
//
//////////////////////////////////////////////////////////////////////

class RCRequestedFileFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new RCRequestedFile(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "RCRequestedFile"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_RC_REQUESTED_FILE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static RCRequestedFilePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return 1 + 4 + ( 1 + 256 ) + 4; }

};


//////////////////////////////////////////////////////////////////////
//
// class RCRequestedFileHandler;
//
//////////////////////////////////////////////////////////////////////

class RCRequestedFileHandler {
	
public :
	
	// execute packet's handler
	static void execute ( RCRequestedFile * pPacket , Player * pPlayer );

};

#endif
