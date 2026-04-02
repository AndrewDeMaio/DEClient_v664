//----------------------------------------------------------------------
// 
// Filename    : LCCreatePCError.h 
// Written By  : Reiot
// Description :
// 
//----------------------------------------------------------------------

#ifndef __LC_CREATE_PC_ERROR_H__
#define __LC_CREATE_PC_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//----------------------------------------------------------------------
//
// class LCCreatePCError;
//
// PC Creation �� �������� ���, �α��� ������ Ŭ���̾�Ʈ���� �� ��Ŷ��
// ������.
//
//----------------------------------------------------------------------

class LCCreatePCError : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_LC_CREATE_PC_ERROR; }
	
	// get packet's body size
	size_t getPacketSize () const { return szBYTE; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "LCCreatePCError"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
	// get/set error message
//	std::string getMessage () const { return m_Message; }
//  void setMessage ( std::string message ) { m_Message = message; }

	// get /set ErrorID
	BYTE getErrorID() const { return m_ErrorID; }
	void setErrorID( BYTE ErrorID ) { m_ErrorID = ErrorID; }

private : 

	// ���� ID
	BYTE m_ErrorID;

};


//////////////////////////////////////////////////////////////////////
//
// class LCCreatePCErrorFactory;
//
// Factory for LCCreatePCError
//
//////////////////////////////////////////////////////////////////////

class LCCreatePCErrorFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new LCCreatePCError(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LCCreatePCError"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_LC_CREATE_PC_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCCreatePCErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCCreatePCErrorHandler {

public :

	// execute packet's handler
	static void execute ( LCCreatePCError * pPacket , Player * pPlayer );

};

#endif
