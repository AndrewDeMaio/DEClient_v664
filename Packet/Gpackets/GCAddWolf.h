//--------------------------------------------------------------------------------
// 
// Filename    : GCAddWolf.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_ADD_WOLF_H__
#define __GC_ADD_WOLF_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "types\GuildTypes.h"

//--------------------------------------------------------------------------------
//
// class GCAddWolf;
//
// �þ� �ȿ� Wolf �� ������ ���, �� ��Ŷ�� Wolf ������ ��Ƽ� ���۹޴´�.
//
//--------------------------------------------------------------------------------
class GCAddWolf : public Packet 
{

public :

	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream);
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_ADD_WOLF; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddWolfPacketSize �� ����, �����϶�.
	size_t getPacketSize() const 
	{ 
		return szObjectID 
			+ szBYTE + m_Name.size() 
//			+ szSpriteType 
//			+ szColor + szColor
			+ szItemType
			+ szCoord + szCoord + szDir
			+ szHP*2
			+ szGuildID
			+ szColor
			;
	}

	#ifdef __DEBUG_OUTPUT__	
		// get packet's name
		std::string getPacketName() const { return "GCAddWolf"; }
	
		// get packet's debug std::string
		std::string toString() const;
	#endif


public :

	// get/set object id
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) { m_ObjectID = creatureID; }

	// get/set name
	const std::string& getName() const { return m_Name; }
	void setName(std::string name) { m_Name = name; }

/*
	// get/set sprite type
	SpriteType_t getSpriteType() const { return m_SpriteType; }
	void setSpriteType(SpriteType_t spriteType) { m_SpriteType = spriteType; }

	// get/set main color
	Color_t getMainColor() const { return m_MainColor; }
	void setMainColor(Color_t color) { m_MainColor = color; }

	// get/set sub color
	Color_t getSubColor() const { return m_SubColor; }
	void setSubColor(Color_t color) { m_SubColor = color; }
*/
	// get/set X
	Coord_t getX() const { return m_X; }
	void setXYDir(Coord_t x, Coord_t y, Dir_t Dir) { m_X = x; m_Y = y; m_Dir = Dir; }
	
	// get/set Y
	Coord_t getY() const { return m_Y; }

	// get/set Dir
	Dir_t getDir() const { return m_Dir; }

	// get /set MaxHP
	HP_t getMaxHP() const { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP) { m_MaxHP = MaxHP; }

	// get /set CurrentHP
	HP_t getCurrentHP() const { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) { m_CurrentHP = CurrentHP; }

	// get/set ItemType
	ItemType_t getItemType() const { return m_ItemType; }
	void setItemType(ItemType_t ItemType) { m_ItemType = ItemType; }

	// get/set GuildID
	GuildID_t getGuildID() const { return m_GuildID; }
	void setGuildID(GuildID_t GuildID) { m_GuildID = GuildID; }

	Color_t getColor() const { return m_MainColor; }
	void setColor( Color_t color ) { m_MainColor = color; }

private :
	
	// �� �������� ����ũ�� ���̵�� ��ü ������ ���ؼ� ����Ѵ�.
	ObjectID_t m_ObjectID;

	// Wolf�� �̸�
	std::string m_Name;
	
	// ���� �������� ����
	ItemType_t m_ItemType;

/*
	// ��������Ʈ Ÿ��
	SpriteType_t m_SpriteType;

	// ���� ����
	Color_t m_SubColor;
*/
	Color_t m_MainColor;
	
	// X, Y �� ����
	Coord_t m_X;
	Coord_t m_Y;
	Dir_t m_Dir;

	HP_t m_CurrentHP;
	HP_t m_MaxHP;
	GuildID_t m_GuildID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddWolfFactory;
//
// Factory for GCAddWolf
//
//////////////////////////////////////////////////////////////////////

class GCAddWolfFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCAddWolf(); }

	#ifdef __DEBUG_OUTPUT__	
		// get packet name
		std::string getPacketName() const { return "GCAddWolf"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_ADD_WOLF; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddWolfPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const 
	{
		int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
		localLongName = 12;
#endif //__LOCALIZING_LONGNAME
		
		return szObjectID 
			+ szBYTE + 20 + localLongName
//			+ szSpriteType 
//			+ szColor + szColor
			+ szItemType
			+ szCoord + szCoord + szDir
			+ szHP*2
			+ szGuildID
			+ szColor
			;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddWolfHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddWolfHandler {

public :

	// execute packet's handler
	static void execute(GCAddWolf* pPacket, Player* pPlayer);

};

#endif
