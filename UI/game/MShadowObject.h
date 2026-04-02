//----------------------------------------------------------------------
// MShadowObject.h
//----------------------------------------------------------------------
// ImageObject�� ���ٰ� ���� �Ǵµ�..
// ��µǴ� image�� Shadow��..
//----------------------------------------------------------------------

#ifndef	__MSHADOWOBJECT_H__
#define	__MSHADOWOBJECT_H__

#include "MTypeDef.h"
#include "DrawTypeDef.h"
#include "MImageObject.h"

//----------------------------------------------------------------------
//
// MShadowObject class
//
//----------------------------------------------------------------------
class MShadowObject : public MImageObject {
	public :
		MShadowObject();
		MShadowObject(TYPE_OBJECTID id, TYPE_OBJECTID shadowObjectID, TYPE_SPRITEID nSprite, int pX, int pY, TYPE_SECTORPOSITION viewpoint, bool trans);
		~MShadowObject();
};


#endif


