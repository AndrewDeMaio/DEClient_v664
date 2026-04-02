//---------------------------------------------------------------------------
// RequestFileManager.h 
//---------------------------------------------------------------------------
// client ������ file�ְ��ޱ⸦ ����ϴ� �κ��̴�.
//
// ���� ��û�ϴ°Ŵ� �ް�..
// ���� ��û�ϴ°Ŵ� �ְ�..
//
// ������ ��� ���ư����� �ϸ鼭 file�� �ְ��ޱ� ���ؼ�
// �ٸ� thread�� ���ư��� �Ѵ�(������ priority�� ����?)...�� �����ߴµ�..
// �� loop���� �������ݾ�(�󸶳�?) �����ִ°� �������� �𸣰ڴ�.
//
// ���ÿ� �ʹ� ���� file���� �ְ������� ���ϰ� ���� �ɸ��Ƿ�
// �ѹ��� �ϳ��� �ְ��ް�(�ְ�/�޴°� ����?) �ϴ°� ���..�;��µ� -_-;
// ��ٸ��� �ð��� �� ���� ������...�;.. �� �� ������� �ϰڴ�.
//
//
// REQUEST_RECEIVE_MAP : ���� ��û�� file���� ����
//
//    - ������ ��û�ҷ��� file�� ������ ���� �־�ΰ� ��û�ϸ�
//      �� file�� ���� �����ٶ�, ���⼭ ������ �����ؼ� ���� �� �ִ�.
//
//	  - RequestClientPlayer::processCommand()����
//      file�� �޴� ���̶�� ReceiveMyRequest(RequestClientPlayer*)�� ���ָ� �ȴ�.
//
//
// REQUESTED_SEND_MAP : ���� ��û�ϴ� file���� ����
//    - ���� � file�� ��û�ϸ�.. �ϴ� ���� ������ �־�ΰ�
//		SendOtherRequest(RequestServerPlayer*)
//
// �� ���� class�� �и��ϴ°� ������ ������... ��... - -;
//---------------------------------------------------------------------------

#ifndef __REQUEST_FILE_MANAGER_H__
#define __REQUEST_FILE_MANAGER_H__

#pragma warning(disable:4786)

#include <Windows.h>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include "types\RequestTypes.h"
class RequestClientPlayer;
class RequestServerPlayer;
class ConnectException;
class RCRequestedFile;

//---------------------------------------------------------------------------
// REQUEST_FILE_MODE
//---------------------------------------------------------------------------
enum REQUEST_FILE_MODE
{
	REQUEST_FILE_MODE_BEFORE,
	REQUEST_FILE_MODE_SEND,
	REQUEST_FILE_MODE_RECEIVE,
	REQUEST_FILE_MODE_AFTER,
};

//---------------------------------------------------------------------------
// SendFileInfo
//---------------------------------------------------------------------------
// ���� ������ ��û�� ��
//---------------------------------------------------------------------------
class SendFileInfo
{
	private :
		REQUEST_FILE_MODE		m_Mode;

		// ������ ����
		std::string				m_Filename;		// �����ִ� file�̸�		
		REQUEST_FILE_TYPE		m_FileType;		// � file�ΰ�?
		
		// ������ ����		
		std::ifstream			m_FileStream;	// �����ִ� Filename�� open�� ��		
		DWORD					m_FileSizeLeft;

	public :
		SendFileInfo(const char* pFilename, REQUEST_FILE_TYPE fileType);
		~SendFileInfo();

		void		StartSend();
		bool		IsSendMode() const	{ return m_Mode==REQUEST_FILE_MODE_SEND; }
		DWORD		Send(char* pBuffer);		// Get()�� �� ��︮�µ�.. - -;
		void		SendBack(DWORD nBack);
		void		EndSend();

		// Get
		REQUEST_FILE_MODE	GetMode() const			{ return m_Mode; }
		REQUEST_FILE_TYPE	GetFileType() const		{ return m_FileType; }
		const std::string&	GetFilename() const		{ return m_Filename; }
		DWORD			GetFileSizeLeft() const	{ return m_FileSizeLeft; }
};

//---------------------------------------------------------------------------
// ReceiveFileInfo
//---------------------------------------------------------------------------
class ReceiveFileInfo
{
	public :
		REQUEST_FILE_MODE		m_Mode;

		std::string				m_Filename;		// ��û�� filename
		REQUEST_FILE_TYPE		m_FileType;		// ��� �� file�ΰ�?
		
		// �޴� ����
		std::string				m_FilenameTemp;	// ��û�� file�� �޾Ƽ� ��� �����ص� filename
		std::ofstream			m_FileStream;		// FilenameTemp�� open�� ��..		
		DWORD					m_FileSizeLeft;

	public :
		ReceiveFileInfo(const char* pFilename, REQUEST_FILE_TYPE fileType);
		~ReceiveFileInfo();
		
		void		StartReceive(DWORD filesize);
		bool		IsReceiveMode() const	{ return m_Mode==REQUEST_FILE_MODE_RECEIVE; }
		void		Receive(const char* pBuffer, DWORD size);
		void		EndReceive(const std::string& requestUser);

		// Get
		REQUEST_FILE_MODE	GetMode() const			{ return m_Mode; }
		REQUEST_FILE_TYPE	GetFileType() const		{ return m_FileType; }
		const std::string&	GetFilename() const		{ return m_Filename; }
		DWORD			GetFileSizeLeft() const	{ return m_FileSizeLeft; }
};

//---------------------------------------------------------------------------
// RequestReceiveInfo
//---------------------------------------------------------------------------
// ���� ������ ��û�� ��
//---------------------------------------------------------------------------
class RequestReceiveInfo
{
	private :
		// �ޱ� ����
		std::string				m_RequestUser;	// file�� ������ ������ ���

		std::list<ReceiveFileInfo*>	m_FileInfos;

	public :
		RequestReceiveInfo(const char* pRequestUser);
		~RequestReceiveInfo();

		void				AddReceiveFileInfo(ReceiveFileInfo* pInfo)	{ m_FileInfos.push_back( pInfo ); }

		const std::string&	GetRequestUser() const	{ return m_RequestUser; }

		DWORD				GetSize() const		{ return m_FileInfos.size(); }
		ReceiveFileInfo*	GetFront()			{ return (m_FileInfos.empty()? NULL : m_FileInfos.front()); }
		void				DeleteFront()		{ if (!m_FileInfos.empty()) { delete m_FileInfos.front(); m_FileInfos.pop_front(); } }		
		bool				IsEnd()	const		{ return m_FileInfos.empty(); }

};

//---------------------------------------------------------------------------
// RequestSendInfo
//---------------------------------------------------------------------------
// ���� ������ ��û�� ��
//---------------------------------------------------------------------------
class RequestSendInfo
{
	private :
		std::string				m_RequestUser;	// ���� file�� ������ ���

		std::list<SendFileInfo*>	m_FileInfos;

	public :
		RequestSendInfo(const char* pRequestUser);
		~RequestSendInfo();
		
		void				AddSendFileInfo(SendFileInfo* pInfo)	{ m_FileInfos.push_back( pInfo ); }

		const std::string&	GetRequestUser() const	{ return m_RequestUser; }

		DWORD				GetSize() const		{ return m_FileInfos.size(); }
		SendFileInfo*		GetFront()			{ return (m_FileInfos.empty()? NULL : m_FileInfos.front()); }
		void				DeleteFront()		{ if (!m_FileInfos.empty()) { delete m_FileInfos.front(); m_FileInfos.pop_front(); } }		
		bool				IsEnd()	const		{ return m_FileInfos.empty(); }

		void				MakeRCRequestedFilePacket(RCRequestedFile& packet) const;
};


//---------------------------------------------------------------------------
// RequestFileManager
//---------------------------------------------------------------------------
class RequestFileManager {
	public :
		//-----------------------------------------------------------------
		// ���� ��û�� �� : < ��û�ѻ��, ���� ��û��file���� >
		//-----------------------------------------------------------------
		typedef std::map<std::string, RequestReceiveInfo*>		REQUEST_RECEIVE_MAP;

		//-----------------------------------------------------------------
		// �ٸ� ����� ��û�� �� : < ��û�ѻ��, �ٸ� ����� ��û��file���� >
		//-----------------------------------------------------------------
		typedef std::map<std::string, RequestSendInfo*>			REQUEST_SEND_MAP;

	public :
		RequestFileManager();
		~RequestFileManager();

		//--------------------------------------------------------------
		// Release
		//--------------------------------------------------------------
		void			Release();

		//--------------------------------------------------------------
		// MyRequest - ���� ��û�� fileó��
		//--------------------------------------------------------------
		bool			AddMyRequest(RequestReceiveInfo* pInfo);
		bool			RemoveMyRequest(const std::string& name);
		bool			HasMyRequest(const std::string& name) const;
		bool			ReceiveMyRequest(const std::string& name, RequestClientPlayer* pRequestClientPlayer);

		//--------------------------------------------------------------
		// OtherRequest - �ٸ� ����� ��û�� fileó��
		//--------------------------------------------------------------
		bool			AddOtherRequest(RequestSendInfo* pInfo);
		bool			RemoveOtherRequest(const std::string& name);
		bool			HasOtherRequest(const std::string& name) const;
		bool			SendOtherRequest(const std::string& name, RequestServerPlayer* pRequestServerPlayer);

		//--------------------------------------------------------------
		// Update
		//--------------------------------------------------------------
		void			Update();

	protected :
		REQUEST_RECEIVE_MAP			m_MyRequests;		// ���� ��û�� file��
		REQUEST_SEND_MAP		m_OtherRequests;	// �ٸ� ����� ��û�� file��
};

extern RequestFileManager* g_pRequestFileManager;

#endif


