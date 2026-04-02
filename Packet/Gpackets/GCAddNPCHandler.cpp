//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddNPCHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddNPC.h"
#include "ClientDef.h"
#include "MNPC.h"
#include "MGuildType.h"
#include "EffectSpriteTypeDef.h"
#include "MINtr.h"

extern int					g_nZoneLarge;
extern int					g_nZoneSmall;
extern bool					g_bZonePlayerInLarge;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddNPCHandler::execute ( GCAddNPC * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	// message

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
		

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{			
			int npcID = pPacket->getNPCID();

			MNPC* pNPC = new MNPC;
			
			pNPC->SetZone( g_pZone );

			int zoneID	= (g_bZonePlayerInLarge?g_nZoneLarge : g_nZoneSmall);

			// EVE ��� ��ũ
			int creatureType = npcID;
			int spriteType = (*g_pCreatureTable)[creatureType].SpriteTypes[0];
			
			CREATURESPRITETABLE_INFO& spriteInfo = (*g_pCreatureSpriteTable)[spriteType];
#if __CONTENTS(__MENEGROTH)
			SetEffectInfo( pNPC, pPacket->getEffectInfo() );
#endif //__MENEGROTH
			if (spriteInfo.IsNPCSprite()
				&& spriteInfo.IsSlayerSprite()
				|| spriteInfo.IsSlayerSprite())
			{
				// slayer NPC
				pNPC->SetGuildNumber( GUILDID_EVE );
			} else
			if( spriteInfo.IsOustersSprite() )
			{
				pNPC->SetGuildNumber( GUILDID_OUSTERS );
			}
			else if (zoneID==1007 || zoneID==1114 || zoneID==1115)
			{
				// ������
				pNPC->SetGuildNumber( GUILDID_TEPEZ );
			}
			else
			{
				// ���丮
				pNPC->SetGuildNumber( GUILDID_BATHORY );
			}

			//pNPC->SetCreatureType( 0 );
			pNPC->SetCreatureType( npcID );
			pNPC->SetGroundCreature();
			pNPC->SetID(pPacket->getObjectID());
			//pNPC->SetAction(ACTION_MOVE);
			pNPC->SetPosition( pPacket->getX(), pPacket->getY() );
			pNPC->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pNPC->SetDirection( pPacket->getDir() );
			pNPC->SetCurrentDirection( pPacket->getDir() );
			pNPC->SetAction( ACTION_STAND );

			if(zoneID>= 1500 && zoneID<=1506)
				pNPC->SetName( pPacket->getName().c_str() );
			else
				pNPC->SetName( (*g_pCreatureTable)[creatureType].Name );

			pNPC->SetBodyColor1( pPacket->getMainColor() );
			pNPC->SetBodyColor2( pPacket->getSubColor() );

			// NPC ID
			pNPC->SetNPCID( pPacket->getNPCID() );
			
			//
			pNPC->SetStatus( MODIFY_MAX_HP, 100 );
			
			// ���� ����Ʈ�� �ٴ� Creature��� ����Ʈ�� �ٿ��ش�.
			if(creatureType < g_pCreatureTable->GetSize())
			{
				CREATURETABLE_INFO &creatureInfo = g_pCreatureTable->Get(creatureType);

				if(creatureInfo.EffectStatus != EFFECTSTATUS_NULL)
				{
					pNPC->AddEffectStatus((EFFECTSTATUS)creatureInfo.EffectStatus, 0xFFFF);
				}
			}

//			_MinTrace("AddNPC : %s Dir:%d Pos(%d,%d) CreatureType : %d\n",pNPC->GetName(), pPacket->getDir(), pPacket->getX(), pPacket->getY(), pPacket->getNPCID() );
			//------------------------------------------------------------
			// ���丮�� ���.. �ϵ��ڵ�(-_-);
			//------------------------------------------------------------
			if (npcID==217)
			{
				pNPC->SetStatus( MODIFY_CURRENT_HP, 10 );
				pNPC->SetStatus( MODIFY_ALIGNMENT, -10000 );	// �� �ǹ̾���
			}
			else
			{
				pNPC->SetStatus( MODIFY_CURRENT_HP, 100 );
			}

			if (!g_pZone->AddCreature( pNPC ))
			{
				delete pNPC;
				pNPC = NULL;
			}
			else
			{			
				//------------------------------------------------------------
				// Slayer NPC�� ��� ������ ������.
				//------------------------------------------------------------
				SetAddonToSlayer( (MNPC*)pNPC, npcID );

				//------------------------------------------------------------
				// Load���� �ʾ����� load�Ѵ�.
				//------------------------------------------------------------
//				LoadCreatureType( pPacket->getNPCID() );

				MAttachEffect* pEffect = NULL;

				if( pNPC->GetCreatureType() == 638 || pNPC->GetCreatureType() == 657)					
					pEffect = pNPC->CreateAttachEffect( EFFECTSPRITETYPE_AMATA, 0xffff,0);
				else
				if( pNPC->GetCreatureType() == 639 || pNPC->GetCreatureType() == 654)
					pEffect = pNPC->CreateAttachEffect( EFFECTSPRITETYPE_RIPATY, 0xffff,0);

#if __CONTENTS(__TIPOJYU_CASTLE)	//NPC ����Ʈ ���̱�
				if( pNPC->GetCreatureType() == 1041)
				{
					pEffect = pNPC->CreateAttachEffect( EFFECTSPRITETYPE_TIPOJYU_LIFE_CASTLE_ADDMISION_NPC1, 0xffff,0);
				}
#endif // __TIPOJYU_CASTLE

				if(creatureType < g_pCreatureTable->GetSize())
				{
					CREATURETABLE_INFO &creatureInfo = g_pCreatureTable->Get(creatureType);
					
					if(creatureInfo.EffectSpriteType != MAX_EFFECTSPRITETYPE)
					{
						pEffect = pNPC->CreateAttachEffect((ENUM_EFFECTSPRITETYPE)creatureInfo.EffectSpriteType, 0xFFFF, 0);
					}
				}

				if(pEffect != NULL)
				{
					pEffect->SetDirection( pNPC->GetDirection() );					
					pEffect->SetLink( ACTIONINFO_NULL, NULL );
					pEffect->SetAttachCreatureID( pNPC->GetID() );
				}
			}
		}
		//--------------------------------------------------
		// �̹� �ִ� Creature�� ���
		//--------------------------------------------------
		else
		{
			if (pCreature->GetClassType()==MCreature::CLASS_NPC)
			{
				// �̹� �ִ�..
				pCreature->SetGroundCreature();
#if __CONTENTS(__MENEGROTH)
				SetEffectInfo( pCreature, pPacket->getEffectInfo() );
#endif //__CONTENTS(__MENEGROTH)				
				//pCreature->SetAction(ACTION_MOVE);
				pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );				
				pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
				pCreature->SetDirection( pPacket->getDir() );
				pCreature->SetCurrentDirection( pPacket->getDir() );
				pCreature->SetAction( ACTION_STAND );

				pCreature->SetBodyColor1( pPacket->getMainColor() );
				pCreature->SetBodyColor2( pPacket->getSubColor() );

				//
				//pCreature->SetStatus( MODIFY_MAX_HP, 100 );
				//pCreature->SetStatus( MODIFY_CURRENT_HP, 100 );
			}
			else
			{
				DEBUG_ADD_FORMAT("[Error] The Creature is Not NPC. id=%d", pPacket->getObjectID());
			}
		}
	}

	// [����] NPC�� ��Ÿ����
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_CREATURE_APPEAR_NPC );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
