//////////////////////////////////////////////////////////////////////
// 
// Filename    :  
// Written By  : rappi76
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __FRIEND_SIMPLE_INFO_H__
#define __FRIEND_SIMPLE_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

#include "StringInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class FriendSimpleInfo;
//
//
//////////////////////////////////////////////////////////////////////

#if __CONTENTS(__FRIEND_ADDITION)
class FriendSimpleInfo {

public :
	
	// constructor
	FriendSimpleInfo ();
	
	// destructor
	~FriendSimpleInfo ();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () const;
	static uint getMaxSize();

	// get packet's debug string
	string toString () const;
	
	void SetFriendName(const string& strName) { m_FriendName.SetString(strName); }
	string GetFriendName() const  { return m_FriendName.GetString(); }
	
	void SetConnect(bool bConnect) { m_bConnect = bConnect; }
	BYTE GetConnect() const  { return m_bConnect; }
	
	void SetServerName(const string& strName) { m_ServerName.SetString(strName); }
	string GetServerName() const  { return m_ServerName.GetString(); }
	
	void SetZoneID(ZoneID_t zoneID) { m_ZoneID = zoneID; }
	ZoneID_t GetZoneID() const  { return m_ZoneID; }

private :
	StringInfo m_FriendName;		// ģ�� �̸�
	BYTE m_bConnect;			// ���� ����		0 - ������, 1 - ����
	StringInfo m_ServerName;		// ���� ���� �̸�
	ZoneID_t m_ZoneID;			// ���� �� ��ġ

};
#endif //__FRIEND_ADDITION

#endif
