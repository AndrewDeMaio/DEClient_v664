//--------------------------------------------------------------------------------
//
// Filename    : GCFastMoveHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCFastMove.h"
#include "Player.h"
#include "ClientDef.h"
#include "SkillDef.h"
#include "MTopView.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCFastMoveHandler::execute ( GCFastMove * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	int objectID = pPacket->getObjectID();

	// (ox, oy) --> (nx, ny)
	int ox = pPacket->getFromX();
	int oy = pPacket->getFromY();
	int nx = pPacket->getToX();
	int ny = pPacket->getToY();
	ACTIONINFO skillType = (ACTIONINFO)pPacket->getSkillType();
	int IsMe = false;

	MCreature* pCreature = NULL;
	
	//------------------------------------------------------------------
	// Player�� ���
	//------------------------------------------------------------------
	if (objectID==g_pPlayer->GetID())
	{
		//------------------------------------------------------------------
		// Player�� ��ٸ��� skill�� ���������� �����޾Ҵ�.
		//------------------------------------------------------------------
		if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_SKILL_SUCCESS)
		{		
			g_pPlayer->SetWaitVerifyNULL();
		}
		else
		{
			DEBUG_ADD("[Error] Player is not WaitVerifySkillSuccess");
		}

		pCreature = g_pPlayer;
		IsMe = true;
	}
	else
	{
		pCreature = g_pZone->GetCreature( objectID );
	}

	if (pCreature == NULL)
	{
		// ĳ���� ����.
		DEBUG_ADD_FORMAT("[Error] There is no such Creature. id=%d", objectID);
	}
	// Creature���� ��.. 		
	else
	{
		switch(skillType)
		{
		case SKILL_CHARGING_ATTACK:
				ExecuteActionInfoFromMainNode(
							SKILL_CLIENT_CHARGING_ATTACK,										// ��� ��� ��ȣ
						
							ox, oy, 0,
							pCreature->GetDirection(),														// ��� ����
							
							pCreature->GetID(),												// ��ǥ�� ���� ����
							nx, ny, 0,
							
							17, //5*16, 
							
							NULL,
							
							false,
							
							0, 0);	

				if(pCreature == g_pPlayer)
				{
					g_pPlayer->SetDelay(1000);
				}
				pCreature->FastMovePosition( nx, ny, true );
				pCreature->SetGhost(3, 16);
			break;
			
		case SKILL_TELEPORT:
			{
				ExecuteActionInfoFromMainNode(
							SKILL_CLIENT_TELEPORT,										// ��� ��� ��ȣ
						
							ox, oy, 0,
							pCreature->GetDirection(),														// ��� ����
							
							pCreature->GetID(),												// ��ǥ�� ���� ����
							ox, oy, 0,
							
							20, //5*16, 
							
							NULL,
							
							false,
							
							0, 0);	

				//pCreature->SetPosition(nx, ny);
				pCreature->FastMovePosition( nx, ny, true );

				if(pCreature == g_pPlayer)
				{
					g_pPlayer->SetDelay(1250);
				}
				pCreature->SetGhost(0xFF, 18);

				ExecuteActionInfoFromMainNode(
							SKILL_CLIENT_TELEPORT2,										// ��� ��� ��ȣ
						
							nx, ny, 0,
							pCreature->GetDirection(),														// ��� ����
							
							pCreature->GetID(),												// ��ǥ�� ���� ����
							nx, ny, 0,
							
							20, //5*16, 
							
							NULL,
							
							false,
							
							0, 0);	

			}
			break;

		case SKILL_DUCKING_WALLOP:
			{
				ExecuteActionInfoFromMainNode(
							SKILL_CLIENT_DUCKING_WALLOP,										// ��� ��� ��ȣ
						
							ox, oy, 0,
							pCreature->GetDirectionToPosition(nx, ny),														// ��� ����
							
							pCreature->GetID(),												// ��ǥ�� ���� ����
							ox, oy, 0,
							
							10, //5*16, 
							
							NULL,
							
							false,
							
							0, 0);	

				pCreature->FastMovePosition( nx, ny, true );
				pCreature->SetGhost(0xFF, 9);
				if(pCreature == g_pPlayer)
				{
					g_pPlayer->SetDelay(565);
				}
			}
			break;
		case SKILL_BIKE_CRASH:
			{
				MItem*	pItem = MItem::NewItem( ITEM_CLASS_MOTORCYCLE );
				if(pItem != NULL)
				{
					pCreature->AddEffectStatus(EFFECTSTATUS_BIKE_CRASH, 0xffff);
					pItem->SetItemType( 6 );
					((MCreatureWear*)pCreature)->SetAddonItem( pItem );
					delete pItem;
					int TempDir = MTopView::GetDirectionToPosition(pCreature->GetX(), pCreature->GetY(), nx, ny);
					pCreature->SetInstallTurretDirect(TempDir);
					pCreature->SetDirection(TempDir);
					pCreature->SetCurrentDirection(TempDir);
					pCreature->SetInstallTurretCount(0);
					if(pCreature->GetID() == g_pPlayer->GetID())
						g_pPlayer->SetDelay(3000);
				}
				pCreature->FastMovePosition( nx, ny, true );
			}
			break;			
		case SKILL_BOMB_CRASH_WALK:
			{
				ExecuteActionInfoFromMainNode(
							SKILL_CLIENT_BOMB_CRASH_WALK,						// ��� ��� ��ȣ
		
							ox, oy, 0,
							pCreature->GetDirection(),							// ��� ����
		
							pCreature->GetID(),									// ��ǥ�� ���� ����
							nx, ny, 0,
							
							20, //5*16, 
							
							NULL,
							
							false,
							
							0, 0);	


				//pCreature->SetPosition(nx, ny);
				pCreature->FastMovePosition( nx, ny, true );
				if(pCreature == g_pPlayer)
				{
					g_pPlayer->SetDelay(500);
				}

				pCreature->SetGhost(0xFF, 5);

				int TempDir = MTopView::GetDirectionToPosition(pCreature->GetX(), pCreature->GetY(), nx, ny);
				pCreature->SetDirection(TempDir);
				pCreature->SetCurrentDirection(TempDir);
			}
			break;
			
		case SKILL_BLOODS_SYMPOSION_ATTACK:
			{
				pCreature->FastMovePosition( nx, ny, true );
				if(pCreature == g_pPlayer)
				{
					g_pPlayer->SetDelay(500);
				}

				pCreature->SetBloodyZenith(8);

				int TempDir = MTopView::GetDirectionToPosition(pCreature->GetX(), pCreature->GetY(), nx, ny);
				pCreature->SetDirection(TempDir);
				pCreature->SetCurrentDirection(TempDir);
			}
			break;

		default:
			{
//							
				pCreature->FastMovePosition( nx, ny, true );
			}
		}
	}


#endif

	__END_CATCH
}