//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeWeather.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCChangeWeather.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCChangeWeather::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	BYTE weather;
	iStream.read( weather );
	m_Weather = (Weather)weather;

	iStream.read( m_WeatherLevel );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCChangeWeather::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( (BYTE)m_Weather );
	oStream.write( m_WeatherLevel );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCChangeWeather::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCChangeWeatherHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCChangeWeather::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCChangeWeather("
			<< "Weather:" << Weather2String[m_Weather]
			<< ",WeatherLevel:" << (int)m_WeatherLevel 
			<< ")";

		return msg.toString();

		__END_CATCH
	}
#endif
