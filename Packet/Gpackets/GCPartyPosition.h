//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPartyPosition.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_POSITION_H__
#define __GC_PARTY_POSITION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPartyPosition;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCPartyPosition : public Packet
{
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_PARTY_POSITION; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCPartyPositionPacketSize �� ����, �����϶�.
	size_t getPacketSize() const { return szBYTE + m_Name.size() + szZoneID + szZoneCoord*2+ szHP*2; }

#ifdef __DEBUG_OUTPUT__
	// get packet's name
	string getPacketName() const { return "GCPartyPosition"; }
	
	// get packet's debug string
	string toString() const;
#endif

public :
	const std::string&	getName() const { return m_Name; }
	void	setName( const string& name ) { m_Name = name; }

	void		setZoneID( ZoneID_t zoneID ) { m_ZoneID = zoneID; }
	ZoneID_t	getZoneID() const { return m_ZoneID; }

	void	setXY( ZoneCoord_t X, ZoneCoord_t Y) { m_X = X; m_Y = Y; }
	void	setHP( HP_t MaxHP, HP_t HP) { m_MaxHP = MaxHP; m_HP = HP; }
	ZoneCoord_t	getX() const { return m_X; }
	ZoneCoord_t getY() const { return m_Y; }
	HP_t		getMaxHP() const { return m_MaxHP; }
	HP_t		getHP() const { return m_HP; }
	
private :
	string	m_Name;
	ZoneID_t	m_ZoneID;
	ZoneCoord_t	m_X, m_Y;
	HP_t		m_MaxHP;
	HP_t		m_HP;
};


//////////////////////////////////////////////////////////////////////
//
// class GCPartyPositionFactory;
//
// Factory for GCPartyPosition
//
//////////////////////////////////////////////////////////////////////

class GCPartyPositionFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCPartyPosition(); }

	// get packet name
	string getPacketName() const { return "GCPartyPosition"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_PARTY_POSITION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPartyPositionPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + 20 + szZoneID + szZoneCoord*2+ szHP*2; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPartyPositionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPartyPositionHandler {

public :

	// execute packet's handler
	static void execute(GCPartyPosition* pPacket, Player* pPlayer);

};

#endif
