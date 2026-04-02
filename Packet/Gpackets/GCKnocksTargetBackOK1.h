//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_KNOCKS_TARGET_BACK_OK_1_H__
#define __GC_KNOCKS_TARGET_BACK_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"
//#include "ModifyItemInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1 : public ModifyInfo {

public :
	
	// constructor
	GCKnocksTargetBackOK1 ();
	
	// destructor
	~GCKnocksTargetBackOK1 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_KNOCKS_TARGET_BACK_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szSkillType + szDir + szCoord*2 + szObjectID + szBullet + szbool + ModifyInfo::getPacketSize() ;}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCKnocksTargetBackOK1"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set Success
	bool getSkillSuccess() const { return m_bSuccess; }
	void setSkillSuccess( bool Success ) { m_bSuccess = Success; }
	
	// get / set Bullet Num
	Bullet_t getBullet() const { return m_BulletNum; }
	void setBulletNum( Bullet_t BulletNum ) { m_BulletNum = BulletNum; }

	void setXYDir( Coord_t x, Coord_t y, Coord_t dir)
	{
		m_X = x; m_Y = y; m_dir = dir;
	}
	Coord_t getX() const { return m_X;}
	Coord_t getY() const { return m_Y;}
	Dir_t getDir() const { return m_dir;}

	SkillType_t getSkillType() const { return m_SkillType;}
	void setSkillType( SkillType_t s) { m_SkillType = s;}


private :

	// ObjectID
	ObjectID_t m_ObjectID;

	// Bullet Num
	Bullet_t m_BulletNum;

	bool m_bSuccess;
	
	Coord_t m_X, m_Y;	// �̵��� ��ǥ.
	Dir_t m_dir;		// �з��� ����.
	SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1Factory;
//
// Factory for GCKnocksTargetBackOK1
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCKnocksTargetBackOK1Factory () {}
	
	// destructor
	virtual ~GCKnocksTargetBackOK1Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCKnocksTargetBackOK1(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCKnocksTargetBackOK1"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_KNOCKS_TARGET_BACK_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szSkillType + szDir + szCoord*2 + szObjectID + szBullet + szbool + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1Handler {

public :

	// execute packet's handler
	static void execute ( GCKnocksTargetBackOK1 * pGCKnocksTargetBackOK1 , Player * pPlayer );

};

#endif
