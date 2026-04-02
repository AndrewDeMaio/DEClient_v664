//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSetVampireHotKey.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SET_VAMPIRE_HOT_KEY_H__
#define __CG_SET_VAMPIRE_HOT_KEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKey;
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKey : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_SET_VAMPIRE_HOT_KEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGSetVampireHotKeyPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szSkillType * 8; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGSetVampireHotKey"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get/set X Coordicate
	SkillType_t getHotKey ( BYTE pos ) const { return m_HotKey[pos]; }
	void setHotKey ( BYTE pos , SkillType_t SkillType ) { m_HotKey[pos] = SkillType; }

private :

	SkillType_t m_HotKey[8];
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKeyFactory;
//
// Factory for CGSetVampireHotKey
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGSetVampireHotKeyFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGSetVampireHotKey(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGSetVampireHotKey"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_SET_VAMPIRE_HOT_KEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGSetVampireHotKeyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szSkillType * 8; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKeyHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGSetVampireHotKeyHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGSetVampireHotKey * pPacket , Player * player );
	};
#endif

#endif
