//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestPowerPoint.h 
// Written By  : bezz
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_POWER_POINT_H__
#define __CG_REQUEST_POWER_POINT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestPowerPoint;
//////////////////////////////////////////////////////////////////////////////

class CGRequestPowerPoint : public Packet
{
public:
	CGRequestPowerPoint ();
	~CGRequestPowerPoint ();
	
public:
    void read ( SocketInputStream & iStream );
    void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
    PacketID_t getPacketID () const { return PACKET_CG_REQUEST_POWER_POINT; }
	size_t getPacketSize () const { return szBYTE + m_CellNum.size(); }
#ifdef __DEBUG_OUTPUT__
	string getPacketName () const { return "CGRequestPowerPoint"; }
	string toString () const;
#endif
public:
	// get / set cell number
	const std::string& getCellNum() const { return m_CellNum; }
	void setCellNum( const string& cellnum ) { m_CellNum = cellnum; }

protected:
	string			m_CellNum;
};

//////////////////////////////////////////////////////////////////////////////
// class CGRequestPowerPointFactory;
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGRequestPowerPointFactory : public PacketFactory 
{
public:
	Packet * createPacket () { return new CGRequestPowerPoint(); }
	string getPacketName () const { return "CGRequestPowerPoint"; }
	PacketID_t getPacketID () const { return Packet::PACKET_CG_REQUEST_POWER_POINT; }
	PacketSize_t getPacketMaxSize () const { return szBYTE + 12;}
};
#endif
//////////////////////////////////////////////////////////////////////////////
// class CGRequestPowerPointHandler;
//////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGRequestPowerPointHandler 
{
public:
	static void execute ( CGRequestPowerPoint * pCGRequestPowerPoint , Player * pPlayer );
};
#endif

#endif

