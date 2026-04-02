//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddMonsterFromTransformationHandler.cpp
// Written By  : elca@ewestsoft.com
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddMonsterFromTransformation.h"
#include "ClientDef.h"
#include "SkillDef.h"
#include "MTopView.h"


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddMonsterFromTransformationHandler::execute ( GCAddMonsterFromTransformation * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
	

	EFFECTSTATUS	statusShadowCheck;
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
		#ifdef __DEBUG_OUTPUT__
			DEBUG_ADD_FORMAT("[AddMonster] type=%d, id=%d, xy=(%d,%d), dir=%d", 
								pPacket->getMonsterType(),
								pPacket->getObjectID(), 
								pPacket->getX(), pPacket->getY(), 
								pPacket->getDir());
		#endif

		//AfxMessageBox( pPacket->toString().c_str() );
		MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());


#if __CONTENTS(__TIPOJYU_CASTLE)	//���� ������ �׸��� ����
		EffectInfo* pTempEffectInfo = pPacket->getEffectInfo();
		
		if(NULL != pTempEffectInfo)
		{
			if(pTempEffectInfo->getListNum()>0)
			{
				std::list<std::pair<WORD,DWORD> > TemList = pTempEffectInfo->GetList();
				std::list<std::pair<WORD,DWORD> >::iterator itr = TemList.begin();

				for(;itr != TemList.end(); ++itr)
				{
					EFFECTSTATUS	status		= (EFFECTSTATUS)itr->first;
					if(status	== EFFECT_CLASS_TRANSLUCENCY)
						statusShadowCheck	= EFFECT_CLASS_TRANSLUCENCY;
				}	
			}
		}
#endif // __TIPOJYU_CASTLE

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreature;

			pCreature->SetZone( g_pZone );

			//pCreature->SetCreatureType( 0 );
			pCreature->SetCreatureType( pPacket->getMonsterType() );
			pCreature->SetGroundCreature();
			pCreature->SetID(pPacket->getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			// [ TEST CODE ]
			// �̸� ����
			//char str[20];
			//sprintf(str, "ID=%d", pCreature->GetID());
			//by kim 2021-08-13 �����̸� Ŭ�� ���� 
			pCreature->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
			//pCreature->SetName( pPacket->getMonsterName().c_str() );

			// �ӽ÷�..
			pCreature->SetGuildNumber( 1 );

			// �̸�
			//pCreature->SetName( pPacket->getName().toString().c_str() );


#if __CONTENTS(__TIPOJYU_CASTLE)	//���� ������ �׸��� ����
			if(statusShadowCheck == EFFECT_CLASS_TRANSLUCENCY)
			{
				SMonsterHalfAlpha	MonsterHalfAlpha;
				MonsterHalfAlpha.Release();
				MonsterHalfAlpha.bHalfAlpha			= true;
				MonsterHalfAlpha.iCreatureObjectID	= pPacket->getObjectID();
				MonsterHalfAlpha.iCreatureID		= pCreature->GetCreatureType();
				pCreature->SetAlpha(TRUE);

				if(g_pTopView)
				{
					g_pTopView->SetMonsterHalfAlpha(MonsterHalfAlpha);
				}
			}
#endif


			// ���� ����
			if (!g_pZone->AddCreature( pCreature ))
			{	
				delete pCreature;
				pCreature = NULL;
			}
			else
			{
				//------------------------------------------------------------
				// Load���� �ʾ����� load�Ѵ�.
				//------------------------------------------------------------
//				LoadCreatureType( pPacket->getMonsterType() );			
			}
		}
		else
		{
			// creature�� �ƴϸ� �����.
			bool reAdd = false;

			if (pCreature->GetClassType()!=MCreature::CLASS_CREATURE)
			{
				g_pZone->RemoveCreature( pCreature->GetID() );

				pCreature = new MCreature;

				pCreature->SetID(pPacket->getObjectID());

				pCreature->SetZone( g_pZone );
				
				//by kim 2021-08-13 �����̸� Ŭ�� ����
				pCreature->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
				//pCreature->SetName( pPacket->getMonsterName().c_str() );
				//end kim
				pCreature->SetPosition( pPacket->getX(), pPacket->getY() );				

				reAdd = true;
			}
			else
			{
				pCreature->MovePosition( pPacket->getX(), pPacket->getY() );				
			}

			pCreature->SetCreatureType( pPacket->getMonsterType() );
			pCreature->SetGroundCreature();
			
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			// �ӽ÷�..
			pCreature->SetGuildNumber( 1 );	
			
			if (reAdd)
			{
				if (!g_pZone->AddCreature( pCreature ))
				{	
					delete pCreature;
					pCreature = NULL;
				}
				else
				{
					//------------------------------------------------------------
					// Load���� �ʾ����� load�Ѵ�.
					//------------------------------------------------------------
//					LoadCreatureType( pPacket->getMonsterType() );			
				}
			}
		}

		if (pCreature!=NULL)
		{
			//--------------------------------------------------
			// Effect ���̱�..
			//--------------------------------------------------
			SetEffectInfo( pCreature, pPacket->getEffectInfo() );

			//--------------------------------------------------
			// Burrow���� ���������� Effect == Burrowing�ϴ� Effect
			//--------------------------------------------------		
			ExecuteActionInfoFromMainNode(
				RESULT_MAGIC_HIDE,										// ��� ��� ��ȣ
			
				pCreature->GetX(), pCreature->GetY(), 0,
				pCreature->GetDirection(),														// ��� ����
				
				OBJECTID_NULL,												// ��ǥ�� ���� ����
				pCreature->GetX(), pCreature->GetY(), 0, 
				
				0,													// ����� (����) ���� �ð�		
				
				NULL,
				
				false);			// ��� ÷���� �����Ѵ�.

			TYPE_CREATURETYPE	creatureType = pCreature->GetCreatureType();

			// ���� ����Ʈ�� �ٴ� Creature��� ����Ʈ�� �ٿ��ش�.
			if(creatureType < g_pCreatureTable->GetSize())
			{
				CREATURETABLE_INFO &creatureInfo = g_pCreatureTable->Get(creatureType);

				if(creatureInfo.EffectStatus != EFFECTSTATUS_NULL)
				{
					pCreature->AddEffectStatus((EFFECTSTATUS)creatureInfo.EffectStatus, 0xFFFF);
				}

				if(creatureInfo.EffectSpriteType != MAX_EFFECTSPRITETYPE)
				{
					pCreature->CreateAttachEffect((ENUM_EFFECTSPRITETYPE)creatureInfo.EffectSpriteType, 0xFFFF, 0);
				}
			}
		}
	}

	// [����] ���� ��Ÿ����
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_CREATURE_APPEAR_MONSTER );
//	__END_HELP_EVENT
#endif

	__END_CATCH
}
