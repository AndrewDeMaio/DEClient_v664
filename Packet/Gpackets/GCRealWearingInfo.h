//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRealWearingInfo.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REAL_WEARING_INFO_H__
#define __GC_REAL_WEARING_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCRealWearingInfo;
//
//////////////////////////////////////////////////////////////////////

class GCRealWearingInfo : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_REAL_WEARING_INFO; }
	
	// get packet's body size
	size_t getPacketSize () const { return szDWORD; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRealWearingInfo"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	DWORD getInfo(void) const { return m_Info;}
	void setInfo(DWORD info) { m_Info = info;}

private :
	
	DWORD m_Info;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRealWearingInfoFactory;
//
// Factory for GCRealWearingInfo
//
//////////////////////////////////////////////////////////////////////

class GCRealWearingInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCRealWearingInfo(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRealWearingInfo"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_REAL_WEARING_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRealWearingInfoPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szDWORD; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRealWearingInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRealWearingInfoHandler {
	
public :

	// execute packet's handler
	static void execute ( GCRealWearingInfo * pPacket , Player * player );
};

#endif
