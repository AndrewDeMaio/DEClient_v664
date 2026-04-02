//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddEffectToTileHandler.cc
// Written By  : crazydog
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddEffectToTile.h"
#include "ClientDef.h"
#include "MEffectStatusTable.h"
#include "SkillDef.h"
#include "MTopView.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"

#include "OperatorOption.h"

extern void SetDragonTorando(int Type, DWORD ObjectID, int TileX, int TileY);
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddEffectToTileHandler::execute ( GCAddEffectToTile * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
		
	//------------------------------------------------------
	// ����� �޽��� ����
	//------------------------------------------------------
	if(g_pUserInformation->attrOperator.GetValue() &&
	   g_pOperatorOption->bShowAddEffect)
	{
		DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

		char szBuf[128];
		sprintf(szBuf, "x=%d, y=%d, eid=%d, duration=%d, delayFrame=%d",			
			pPacket->getX(), pPacket->getY(),
			pPacket->getEffectID(), pPacket->getDuration(), delayFrame);

		UI_AddChatToHistory(szBuf, "Recv GCAddEffectToTile", 6, RGB(255, 255, 0));
	}
		
	// ���� ó��
	if( pPacket->getEffectID() == EFFECTSTATUS_TRAP_INSTALLED && !g_pPlayer->IsSlayer() )
		return;

#if __CONTENTS(__QUEST_RENEWAL)
	DWORD EffectStatusType = (EFFECTSTATUS)pPacket->getEffectID();

	if(EffectStatusType	== EFFECTSTATUS_QUEST_FINISH)
	{
		switch(g_pPlayer->GetRace())
		{
		case RACE_SLAYER:
			EffectStatusType = EFFECTSTATUS_CLIENT_QUEST_FINISH_SLAYER;
			break;
		case RACE_VAMPIRE:
			EffectStatusType = EFFECTSTATUS_CLIENT_QUEST_FINISH_VAMPIRE;
			break;	
		case RACE_OUSTERS:
			EffectStatusType = EFFECTSTATUS_CLIENT_QUEST_FINISH_OUSTERS;
			break;
		}
	}
#else
	EFFECTSTATUS EffectStatusType = (EFFECTSTATUS)pPacket->getEffectID();
#endif

	int skillType	= (*g_pEffectStatusTable)[ EffectStatusType ].ActionInfo;
	
	// 2004, 9, 3, sobeit add start
	if(EffectStatusType == EFFECTSTATUS_TURRET_LASER && g_pPlayer) // ������ Ʈ����..�������� �Ⱥ��̴� ����
	{
		if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_1) || 
			g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_2) || 
			g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_3) || 
			g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_4) || 
			g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_5) )
			return;
	}
	// 2004, 9, 3, sobeit add end

	// 2005, 1, 6, sobeit add start - �巹�� ����̵� ���� ó���� �� ��Ŷ�� ����´�..-_-
	if(EffectStatusType == EFFECTSTATUS_DRAGON_TORNADO || EffectStatusType == EFFECTSTATUS_DRAGON_TORNADO_CHILD)
	{
		SetDragonTorando(EffectStatusType, pPacket->getObjectID(), pPacket->getX(), pPacket->getY());
		return;
	}


	// 2005, 1, 6, sobeit add end
	//------------------------------------------------------------
	// Effect�� ���õ� ����� ������..
	//------------------------------------------------------------
	if (skillType!=ACTIONINFO_NULL)
	{
		int x			= pPacket->getX();
		int y			= pPacket->getY();
		DWORD delayFrame	= ConvertDurationToFrame( pPacket->getDuration() );
		
//		switch(skillType)
//		{
//		case SKILL_CLIENT_TRAP_ICICLE_DROP:
//			delayFrame = 16;
//			break;
//		case SKILL_CLIENT_TRAP_ICICLE_AUGER:
//			delayFrame = 14;
//			break;
//		case SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER:
//			delayFrame = 12;
//			break;
//		}

		ExecuteActionInfoFromMainNode(
				skillType,		// �� ��ü�� RESULT_ACTIONINFO�̴�.
			
				x, y, 0,
				DIRECTION_DOWN,
				
				OBJECTID_NULL,
				x, y, 0,
				
				delayFrame,	
				
				NULL
		);
	}
	else
	{
		DEBUG_ADD_FORMAT("[Error] No ActionInfo with EffectStatusID=%d", pPacket->getEffectID());
	}


		switch( EffectStatusType )
	{
	case EFFECTSTATUS_TRYING :
		ExecuteActionInfoFromMainNode(
			REGEN_TOWER_TRING_POSITION_LIGHT,
			pPacket->getX(),
			pPacket->getY(),
			0,
			DIRECTION_DOWN,
			OBJECTID_NULL,
			pPacket->getX(),
			pPacket->getY(),
			0,
			ConvertDurationToFrame( pPacket->getDuration() ),
			NULL
			);
		break;
		
	case EFFECTSTATUS_GROUND_ELEMENTAL_AURA:
		if( g_pZone != NULL )
		{
			const_cast<MSector &>(g_pZone->GetSector(pPacket->getX(), pPacket->getY())).SetGroundElemental();
		}
		break;

	case EFFECTSTATUS_DARKNESS_FORBIDDEN:
		if( g_pZone != NULL )
		{
			const_cast<MSector &>(g_pZone->GetSector(pPacket->getX(), pPacket->getY())).SetDarknessForbidden();
		}
		break;
	case EFFECTSTATUS_LUCKY:
		ExecuteActionInfoFromMainNode(
			RESULT_LUCKY_AURA,
			pPacket->getX(),
			pPacket->getY(),
			0,
			DIRECTION_DOWN,
			OBJECTID_NULL,
			pPacket->getX(),
			pPacket->getY(),
			0,
			ConvertDurationToFrame( pPacket->getDuration() ),
			NULL
			);
		break;
	case EFFECTSTATUS_MISFORTUNE:
		ExecuteActionInfoFromMainNode(
			RESULT_MISFORTUNE_AURA,
			pPacket->getX(),
			pPacket->getY(),
			0,
			DIRECTION_DOWN,
			OBJECTID_NULL,
			pPacket->getX(),
			pPacket->getY(),
			0,
			ConvertDurationToFrame( pPacket->getDuration() ),
			NULL
			);
		break;
	case EFFECTSTATUS_FURY_OF_GNOME:
		if( g_pZone != NULL )
		{
			// �� ��ġ�� �߰��� �� �ִ��� üũ�� ����Ʈ
			MEffect*	pEffect = new MEffect(BLT_EFFECT);
			TYPE_FRAMEID frameID = (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FURY_OF_GNOME_GROUND_START].FrameID;

			pEffect->SetFrameID(frameID, 0);	
			pEffect->SetPosition(pPacket->getX(), pPacket->getY());		// Sector ��ǥ

			if(g_pZone->CanAddEffect(pEffect))
			{
				DWORD continueFrame = ConvertDurationToFrame( pPacket->getDuration() );
				const_cast<MSector &>(g_pZone->GetSector(pPacket->getX(), pPacket->getY())).SetFuryOfGnome(continueFrame);
			}

			delete pEffect;
		}
		break;

	case EFFECTSTATUS_HALO:
		if( g_pZone != NULL )
		{
			MCreature * pTargetCreature = g_pZone->GetCreature(pPacket->getObjectID());
			if(pTargetCreature != NULL && g_pTopView != NULL)
			{
				int TempDir = g_pTopView->GetDirectionToPosition(pPacket->getX(), pPacket->getY(), pTargetCreature->GetX(), pTargetCreature->GetY());
//				if(rand()%2)
//					TempDir = (TempDir+2)%8;
//				else
//					TempDir = (TempDir+6)%8;
				ExecuteActionInfoFromMainNode(SKILL_CLIENT_HALO_ATTACK, pPacket->getX(), pPacket->getY(), 0,TempDir,	pTargetCreature->GetID(),	
					pTargetCreature->GetX(), pTargetCreature->GetY(), 0, 12, NULL, true);	
			}
		}
		break;
	case EFFECTSTATUS_DELETE_TILE:
		if( g_pZone != NULL )
		{
			const_cast<MSector &>(g_pZone->GetSector(pPacket->getX(), pPacket->getY())).SetDisableTileImage();
		}
		break;
	case EFFECTSTATUS_TILE_PORTAL:
		if( g_pZone != NULL )
		{
			if(g_pZone->GetID() == 4001) // ���� ���� �Ա�
				ExecuteActionInfoFromMainNode(SKILL_CLIENT_QUEST_MAGIC_ZONE,16, 16, 0,0,	0,	
								16, 16, 0, 0xffff, NULL, false);			
		}
		break;
	}

#endif

	__END_CATCH
}
