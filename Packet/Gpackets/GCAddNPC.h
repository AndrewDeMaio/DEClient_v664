//--------------------------------------------------------------------------------
// 
// Filename    : GCAddNPC.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_ADD_NPC_H__
#define __GC_ADD_NPC_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"

//--------------------------------------------------------------------------------
//
// class GCAddNPC;
//
// �þ� �ȿ� NPC �� ������ ���, �� ��Ŷ�� NPC ������ ��Ƽ� ���۹޴´�.
//
//--------------------------------------------------------------------------------

class GCAddNPC : public Packet 
{
public:
	GCAddNPC();
	virtual ~GCAddNPC();

public :
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( SocketInputStream & iStream );
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_NPC; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddNPCPacketSize �� ����, �����϶�.
	size_t getPacketSize () const 
	{ 
		return szObjectID 
			+ szBYTE + m_Name.size() + szNPCID
			+ szSpriteType 
			+ szColor + szColor
			+ szCoord + szCoord + szDir
#if __CONTENTS(__MENEGROTH)
			+ m_pEffectInfo->getSize()
#endif //__MENEGROTH
			;
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAddNPC"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get/set object id
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t creatureID ) { m_ObjectID = creatureID; }

	// get/set name
	const std::string& getName () const { return m_Name; }
	void setName ( std::string name ) { m_Name = name; }

	// get/set NPC id
	NPCID_t getNPCID(void) const { return m_NPCID;}
	void setNPCID(NPCID_t NPCID) { m_NPCID = NPCID;}

	// get/set sprite type
	SpriteType_t getSpriteType () const { return m_SpriteType; }
	void setSpriteType ( SpriteType_t spriteType ) { m_SpriteType = spriteType; }

	// get/set main color
	Color_t getMainColor () const { return m_MainColor; }
	void setMainColor ( Color_t color ) { m_MainColor = color; }

	// get/set sub color
	Color_t getSubColor () const { return m_SubColor; }
	void setSubColor ( Color_t color ) { m_SubColor = color; }

	// get/set X
	Coord_t getX () const { return m_X; }
	void setX ( Coord_t x ) { m_X = x; }
	
	// get/set Y
	Coord_t getY () const { return m_Y; }
	void setY ( Coord_t y ) { m_Y = y; }

	// get/set Dir
	Dir_t getDir () const { return m_Dir; }
	void setDir ( Dir_t dir ) { m_Dir = dir; }

//#if __CONTENTS(__MENEGROTH)
	EffectInfo* getEffectInfo() const { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) { m_pEffectInfo = pEffectInfo; }
//#endif

private :
	
	// �� �������� ����ũ�� ���̵�� ��ü ������ ���ؼ� ����Ѵ�.
	ObjectID_t m_ObjectID;

	// NPC�� �̸�
	std::string m_Name;

	// NPC�� ���̵� ( ������Ʈ ���̵� �ƴϴ�. )
	NPCID_t m_NPCID;

	// ��������Ʈ Ÿ��
	SpriteType_t m_SpriteType;

	// ���� ����
	Color_t m_MainColor;
	Color_t m_SubColor;

	// X, Y �� ����
	Coord_t m_X;
	Coord_t m_Y;
	Dir_t m_Dir;

//#if __CONTENTS(__MENEGROTH)
	EffectInfo* m_pEffectInfo;
//#endif //__MENEGROTH

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddNPCFactory;
//
// Factory for GCAddNPC
//
//////////////////////////////////////////////////////////////////////

class GCAddNPCFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCAddNPC(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddNPC"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_NPC; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddNPCPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{
		int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
		localLongName = 12;
#endif //__LOCALIZING_LONGNAME
		return szObjectID 
			+ szBYTE + 20 + localLongName + szNPCID
			+ szSpriteType 
			+ szColor + szColor
			+ szCoord + szCoord + szDir
#if __CONTENTS(__MENEGROTH)
			+ EffectInfo::getMaxSize()
#endif //__MENEGROTH
			;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddNPCHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddNPCHandler {

public :

	// execute packet's handler
	static void execute ( GCAddNPC * pPacket , Player * pPlayer );

};

#endif
