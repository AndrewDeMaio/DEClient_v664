//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_ARMS_OK_1_H__
#define __GC_ATTACK_ARMS_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"
//#include "ModifyItemInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK1 : public ModifyInfo {

public :
	
	// constructor
	GCAttackArmsOK1 ();
	
	// destructor
	~GCAttackArmsOK1 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ATTACK_ARMS_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize() const { return szObjectID + szBullet + szbool + ModifyInfo::getPacketSize() + szSkillType; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAttackArmsOK1"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set Success
	bool getSkillSuccess() const { return m_bSuccess; }
	void setSkillSuccess( bool Success ) { m_bSuccess = Success; }
	
	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set Bullet Num
	Bullet_t getBullet() const { return m_BulletNum; }
	void setBulletNum( Bullet_t BulletNum ) { m_BulletNum = BulletNum; }

	void setSkillType( SkillType_t		SkillType ) { m_SkillType = SkillType; }
	SkillType_t getSkillType() const { return m_SkillType; }		

private :

	// ObjectID
	ObjectID_t m_ObjectID;

	// Bullet Num
	Bullet_t m_BulletNum;

	// success(damage �� ������?)
	bool m_bSuccess;
	SkillType_t		m_SkillType;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK1Factory;
//
// Factory for GCAttackArmsOK1
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackArmsOK1Factory () {}
	
	// destructor
	virtual ~GCAttackArmsOK1Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCAttackArmsOK1(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAttackArmsOK1"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ATTACK_ARMS_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szSkillType + szObjectID + szBullet + szbool + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK1Handler {

public :

	// execute packet's handler
	static void execute ( GCAttackArmsOK1 * pGCAttackArmsOK1 , Player * pPlayer );

};

#endif
