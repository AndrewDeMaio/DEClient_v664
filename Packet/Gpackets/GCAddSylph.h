//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddSlyph.h 
// Written By  : rappi76
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_SYLPH_H__
#define __GC_ADD_SYLPH_H__

#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////////////
// class GCAddSlyph;
//
// �þ� �ȿ� ���� Slyph �� ������ ���, �� ��Ŷ�� Slyph ������ ��Ƽ� ���۹޴´�.
//////////////////////////////////////////////////////////////////////////////

class GCAddSylph : public Packet 
{
public:
	virtual ~GCAddSylph() {}
	void read(SocketInputStream & iStream);
	void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_GC_ADD_SYLPH; }
	size_t getPacketSize() const;

	string getPacketName() const { return "GCAddSylph"; }
	string toString() const;

public:
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) { m_ObjectID = creatureID; }

	uchar getSylphType() { return m_SylphType; }
	void setSylphType(uchar Type) { m_SylphType = Type; }

#if __CONTENTS(__SECOND_TRANSFORTER)
	ItemType_t getWingItemType() { return m_WingItemType; }
	void setWingItemType(ItemType_t ItemType) { m_WingItemType = ItemType; }
#endif //__SECOND_TRANSFORTER

	Color_t getWingBodyColor() { return m_WingBodyColor; }
	void setWingBodyColor(Color_t Color) { m_WingBodyColor = Color; }
	
	Color_t getWingEffectColor() { return m_WingEffectColor; }
	void setWingEffectColor(Color_t Color) { m_WingEffectColor = Color; }

private:
	ObjectID_t   m_ObjectID;

#if __CONTENTS(__SECOND_TRANSFORTER)
	ItemType_t m_WingItemType;
#endif //__SECOND_TRANSFORTER

	uchar m_SylphType;
	Color_t m_WingBodyColor;
	Color_t m_WingEffectColor;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddSlyphFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddSylphFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new GCAddSylph(); }
	string getPacketName() const { return "GCAddSlyph"; }
	PacketID_t getPacketID() const { return Packet::PACKET_GC_ADD_SYLPH; }
	PacketSize_t getPacketMaxSize() const;

};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlyphHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddSylphHandler 
{
public:
	static void execute(GCAddSylph* pPacket, Player* pPlayer);

};

#endif
