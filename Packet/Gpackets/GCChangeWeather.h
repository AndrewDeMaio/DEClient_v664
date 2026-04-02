//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeWeather.h 
// Written By  : reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_CHANGE_WEATHER_H__
#define __GC_CHANGE_WEATHER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCChangeWeather;
//
//--------------------------------------------------------------------------------

class GCChangeWeather : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_CHANGE_WEATHER; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCChangeWeatherPacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return szWeather + szWeatherLevel; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCChangeWeather"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	Weather getWeather () const { return m_Weather; }
	void setWeather ( Weather weather ) { m_Weather = weather; }

	WeatherLevel_t getWeatherLevel () const { return m_WeatherLevel; }
	void setWeatherLevel ( WeatherLevel_t weatherLevel ) { m_WeatherLevel = weatherLevel; }

public :

	Weather m_Weather;

	WeatherLevel_t m_WeatherLevel;

};


//--------------------------------------------------------------------------------
//
// class GCChangeWeatherFactory;
//
// Factory for GCChangeWeather
//
//--------------------------------------------------------------------------------

class GCChangeWeatherFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCChangeWeather(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCChangeWeather"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_CHANGE_WEATHER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCChangeWeatherPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szWeather + szWeatherLevel; }

};


//--------------------------------------------------------------------------------
//
// class GCChangeWeatherHandler;
//
//--------------------------------------------------------------------------------

class GCChangeWeatherHandler {

public :

	// execute packet's handler
	static void execute ( GCChangeWeather * pPacket , Player * pPlayer );

};

#endif
