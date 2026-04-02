//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycleOK.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RIDE_MOTORCYCLE_OK_H__
#define __GC_RIDE_MOTORCYCLE_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleOK;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleOK : public Packet {

public :
	
	// constructor
	GCRideMotorCycleOK ();
	
	// destructor
	~GCRideMotorCycleOK ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_RIDE_MOTORCYCLE_OK; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const {
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
		PacketSize_t size;

		size =  szObjectID + szBYTE; 

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
		return szObjectID; 
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCRideMotorCycleOK"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	BYTE getMotorType() { return m_MotorType; }
	void setMotorType(BYTE Type) { m_MotorType = Type; }

	Color_t getWingBodyColor() { return m_WingBodyColor; }
	void setWingBodyColor(Color_t Color) { m_WingBodyColor = Color; }
	
	Color_t getWingEffectColor() { return m_WingEffectColor; }
	void setWingEffectColor(Color_t Color) { m_WingEffectColor = Color; }
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	BYTE m_MotorType;
	Color_t m_WingBodyColor;
	Color_t m_WingEffectColor;
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleOKFactory;
//
// Factory for GCRideMotorCycleOK
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleOKFactory : public PacketFactory {

public :
	
	// constructor
	GCRideMotorCycleOKFactory () {}
	
	// destructor
	virtual ~GCRideMotorCycleOKFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCRideMotorCycleOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRideMotorCycleOK"; }	
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_RIDE_MOTORCYCLE_OK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
		 + szBYTE + szColor * 2
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER	
		; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleOKHandler;
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleOKHandler {

public :

	// execute packet's handler
	static void execute ( GCRideMotorCycleOK * pGCRideMotorCycleOK , Player * pPlayer );

};

#endif
