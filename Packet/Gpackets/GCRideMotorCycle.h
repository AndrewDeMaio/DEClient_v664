//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycle.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RIDE_MOTORCYCLE_H__
#define __GC_RIDE_MOTORCYCLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycle;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCRideMotorCycle : public Packet {

public :
	
	// constructor
	GCRideMotorCycle ();
	
	// destructor
	~GCRideMotorCycle ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_RIDE_MOTORCYCLE; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { 
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
		PacketSize_t size;
		
		size =  szObjectID + szObjectID + szBYTE; 
		
		switch(m_MotorType)
		{
		case 4 :
			size += szColor * 2;
			break;
		default :
			break;
		}
		
		return size;
#else
		return szObjectID + szObjectID; 
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	}
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	BYTE getMotorType() { return m_MotorType; }
	void setMotorType(BYTE Type) { m_MotorType = Type; }

	Color_t getWingBodyColor() { return m_WingBodyColor; }
	void setWingBodyColor(Color_t Color) { m_WingBodyColor = Color; }
	
	Color_t getWingEffectColor() { return m_WingEffectColor; }
	void setWingEffectColor(Color_t Color) { m_WingEffectColor = Color; }
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER


	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCRideMotorCycle"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID( ObjectID_t TargetObjectID ) { m_TargetObjectID = TargetObjectID; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	BYTE m_MotorType;
	ItemID_t m_MotorItemType;
	Color_t m_WingBodyColor;
	Color_t m_WingEffectColor;
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFactory;
//
// Factory for GCRideMotorCycle
//
//////////////////////////////////////////////////////////////////////

class GCRideMotorCycleFactory : public PacketFactory {

public :
	
	// constructor
	GCRideMotorCycleFactory () {}
	
	// destructor
	virtual ~GCRideMotorCycleFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCRideMotorCycle(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRideMotorCycle"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_RIDE_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + szObjectID
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
		+ szBYTE + szColor * 2
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
		; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRideMotorCycleHandler {

public :

	// execute packet's handler
	static void execute ( GCRideMotorCycle * pGCRideMotorCycle , Player * pPlayer );

};

#endif
