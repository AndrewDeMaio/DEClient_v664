//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeDarkLight.h 
// Written By  : reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_CHANGE_DARK_LIGHT_H__
#define __GC_CHANGE_DARK_LIGHT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCChangeDarkLight;
//
//--------------------------------------------------------------------------------

class GCChangeDarkLight : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_CHANGE_DARK_LIGHT; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCChangeDarkLightPacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return szDarkLevel + szLightLevel; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCChangeDarkLight"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set dark level
	DarkLevel_t getDarkLevel () const { return m_DarkLevel; }
	void setDarkLevel ( DarkLevel_t darkLevel ) { m_DarkLevel = darkLevel; }

	// get/set light level
	LightLevel_t getLightLevel () const { return m_LightLevel; }
	void setLightLevel ( LightLevel_t lightLevel ) { m_LightLevel = lightLevel; }


public :

	// ���� ��ӱ� ( 0 - 15 )
	DarkLevel_t m_DarkLevel;

	// ���� ���� ũ�� ( 1 - 13 )
	LightLevel_t m_LightLevel;

};


//--------------------------------------------------------------------------------
//
// class GCChangeDarkLightFactory;
//
// Factory for GCChangeDarkLight
//
//--------------------------------------------------------------------------------

class GCChangeDarkLightFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCChangeDarkLight(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCChangeDarkLight"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_CHANGE_DARK_LIGHT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCChangeDarkLightPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szDarkLevel + szLightLevel; }

};


//--------------------------------------------------------------------------------
//
// class GCChangeDarkLightHandler;
//
//--------------------------------------------------------------------------------

class GCChangeDarkLightHandler {

public :

	// execute packet's handler
	static void execute ( GCChangeDarkLight * pPacket , Player * pPlayer );

};

#endif
