//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddSlyph.cpp
// Written By  : rappi76
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCAddSylph.h"
#include "ClientDef.h"
#include "SkillDef.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"

void GCAddSylphHandler ::execute ( GCAddSylph* pPacket , Player * pPlayer )
{
	__BEGIN_TRY
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
		
	}	
	//------------------------------------------------------
	// ����.. 
	//------------------------------------------------------
	else
	{
		MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());
		if (pCreature==NULL)
		{
			//�̷� ����� �ƿ찡 ���ͷ� �߰� �� ����̴�.
		}
		else
		{
			pCreature->SetWingType(pPacket->getSylphType());
#if __CONTENTS(__SECOND_TRANSFORTER)	
			pCreature->SetWingItemType(pPacket->getWingItemType());
#endif //__SECOND_TRANSFORTER
			pCreature->SetWingColor(pPacket->getWingBodyColor());
			pCreature->SetWingEffectColor(pPacket->getWingEffectColor());

			switch(pCreature->GetWingType())
			{
			case 0:
			case 1:
			case 2:
				{
#if __CONTENTS(__SECOND_TRANSFORTER)
					switch(pCreature->GetWingItemType())
					{
					case 0:
#endif //__SECOND_TRANSFORTER
						pCreature->SetWingEffect1();
						pCreature->AddEffectStatus(EFFECTSTATUS_CLIENT_WING_SYLPH ,0xFFFFFFFA);	//���ӽð��� ���� �ִ밪�̴�.
						pCreature->SetAction(ACTION_OUSTERS_WING_STAND);
					break;
#if __CONTENTS(__SECOND_TRANSFORTER)
					case 1:
						pCreature->SetWingEffect2();
						pCreature->AddEffectStatus(EFFECTSTATUS_CLIENT_UNICORN ,0xFFFFFFFA); //���ӽð��� ���� �ִ밪�̴�.
						pCreature->SetAction(ACTION_OUSTERS_UNICORN_STAND);
					break;
					}
#endif //__SECOND_TRANSFORTER
				}
			default:
				break;
			}
		}

	}
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	__END_CATCH

}
