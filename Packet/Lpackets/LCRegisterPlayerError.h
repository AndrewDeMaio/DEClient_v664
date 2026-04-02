//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCRegisterPlayerError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_REGISTER_PLAYER_ERROR_H__
#define __LC_REGISTER_PLAYER_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerError;
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerError : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_LC_REGISTER_PLAYER_ERROR; }
	
	// get packet's body size
	size_t getPacketSize () const { return szBYTE; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "LCRegisterPlayerError"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
	BYTE getErrorID() const { return m_ErrorID; }
	void setErrorID( BYTE ErrorID ) { m_ErrorID = ErrorID; }

private : 

	// ���� ID
	BYTE m_ErrorID;

};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerErrorFactory;
//
// Factory for LCRegisterPlayerError
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerErrorFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new LCRegisterPlayerError(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LCRegisterPlayerError"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_LC_REGISTER_PLAYER_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerErrorHandler {

public :

	// execute packet's handler
	static void execute ( LCRegisterPlayerError * pPacket , Player * pPlayer );

};

#endif
