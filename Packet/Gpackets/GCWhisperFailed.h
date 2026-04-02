//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWhisperFailed.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_WHISPER_FAILED_H__
#define __GC_WHISPER_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFailed;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFailed : public Packet {

public :
	
	// constructor
	GCWhisperFailed ();
	
	// destructor
	~GCWhisperFailed ();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_WHISPER_FAILED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return 0; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCWhisperFailed"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

private :

};

//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFailedFactory;
//
// Factory for GCWhisperFailed
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCWhisperFailedFactory () {}
	
	// destructor
	virtual ~GCWhisperFailedFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCWhisperFailed(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCWhisperFailed"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_WHISPER_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFailedHandler {

public :

	// execute packet's handler
	static void execute ( GCWhisperFailed * pGCWhisperFailed , Player * pPlayer );

};

#endif
