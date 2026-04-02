//////////////////////////////////////////////////////////////////////
// 
// Filename    :  
// Written By  : rappi76
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __FRIEND_WAIT_INFO_H__
#define __FRIEND_WAIT_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

#include "StringInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class FriendWaitInfo;
//
//
//////////////////////////////////////////////////////////////////////

#if __CONTENTS(__FRIEND_ADDITION)
class FriendWaitInfo {

public :
	
	// constructor
	FriendWaitInfo ();
	
	// destructor
	~FriendWaitInfo ();

public :
	
	static const int m_iMaxFriendName;
	
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
	
	void SetFriendName(const string& strFriendName) { m_FriendName.SetString(strFriendName); }
	string GetFriendName() const  { return m_FriendName.GetString(); }

private :
	StringInfo m_FriendName;		// ģ�� �̸�
};
#endif //__FRIEND_ADDITION

#endif
