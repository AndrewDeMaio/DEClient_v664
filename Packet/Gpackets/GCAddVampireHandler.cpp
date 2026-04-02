//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddVampireHandler.cc
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddVampire.h"
#include "ClientDef.h"
#include "MCreatureTable.h"
#include "MTestDef.h"
#include "MGameStringTable.h"
#include "EffectSpriteTypeDef.h"
#include "MTopView.h"

extern void SetPetInfo(PetInfo* pPetInfo, TYPE_OBJECTID objectID);
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddVampireHandler::execute ( GCAddVampire * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

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
		const PCVampireInfo3 & vi = pPacket->getVampireInfo ();

		MCreature* pCreature = g_pZone->GetCreature(vi.getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreatureWear;
			
			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, vi.getAdvancementLevel() );
			pCreature->SetZone( g_pZone );

			pCreature->SetName( vi.getName().c_str() );
				
			//--------------------------------------------------
			// CreatureType ����
			//--------------------------------------------------
			Shape_t shape	= vi.getShape();
			bool bMale		= vi.getSex() == MALE;
			
			ItemType_t coatType		= vi.getCoatType();
#if __CONTENTS(__SECOND_TRANSFORTER)
			DWORD wingItemType = vi.getWingItemType();
#endif //__SECOND_TRANSFORTER

			if(shape == SHAPE_BAT && vi.getAdvancementLevel() > 0)
				shape = SHAPE_VAMPIRE_GHOST;

			//if(shape == CREATURETYPE_BAT && vi.getCoatType() )

			if( vi.getBatColor() != 0 )
				pCreature->SetBatColor( vi.getBatColor() );
			else
				pCreature->SetBatColor( 0xFFFF );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
			if(vi.getWingColor() != 0)
				pCreature->SetWingColor(vi.getWingColor());
			else
				pCreature->SetWingColor(403);
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
			pCreature->SetAdvanceBatColor( vi.getAdvanceBatColor() );

			if (vi.getCompetence()==0)
			{
				pCreature->SetCompetence( 0 );
				pCreature->SetCreatureType( CREATURETYPE_VAMPIRE_OPERATOR );
				pCreature->SetMale( bMale );
			}
			else
			{
				pCreature->SetCreatureType( GetVampireCreatureType( shape, bMale, coatType
#if __CONTENTS(__SECOND_TRANSFORTER)
					,wingItemType
#endif //__SECOND_TRANSFORTER
					));
			}

			pCreature->SetMale( bMale );

			const int CreatureType = pCreature->GetCreatureType();

			if (CreatureType==CREATURETYPE_BAT)
			{
				pCreature->SetFlyingCreature();
			}
			else
			{
				pCreature->SetGroundCreature();
			}

			pCreature->SetID(vi.getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( vi.getX(), vi.getY() );
			pCreature->SetServerPosition( vi.getX(), vi.getY() );
			pCreature->SetDirection( vi.getDir() );
			pCreature->SetCurrentDirection( vi.getDir() );
			pCreature->SetAction( ACTION_STAND );
 
			// ����
			
			if(CreatureType == CREATURETYPE_WER_WOLF)
			{
				pCreature->SetBodyColor1( vi.getCoatColor() );
				pCreature->SetBodyColor2( vi.getCoatColor() );
			} else
			{
				pCreature->SetBodyColor1( vi.getSkinColor() );
				pCreature->SetBodyColor2( vi.getCoatColor() );
			}

			// ����Ʈ
			pCreature->SetMasterEffectType( vi.getMasterEffectColor() );

			//--------------------------------------------------
			// [ TEST CODE ]
			//--------------------------------------------------
			// �� ���� �����ϱ�
			//--------------------------------------------------
			/*
			if (pCreature->IsMale())
			{
				pCreature->SetBodyColor2( 91 );
			}
			else
			{
				pCreature->SetBodyColor2( 38 );
			}
			*/

			pCreature->SetStatus( MODIFY_MAX_HP, vi.getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, vi.getCurrentHP() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, vi.getAlignment() );
			pCreature->SetStatus( MODIFY_RANK, vi.getRank() );
#if __CONTENTS(__CONTRIBUTE_SYSTEM)
			pCreature->SetStatus( MODIFY_CONTRIBUTE_POINT, vi.getContributePoint());
#endif //CONTRIBUTE_SYSTEM


			//vi.getName()
			// ���� ����

			pCreature->SetWeaponSpeed( vi.getAttackSpeed() );
			
			// �ӽ÷�
			pCreature->SetGuildNumber( vi.getGuildID() );
			pCreature->SetOriginServerNum( vi.getBorn() );
			pCreature->SetUnionGuildID( vi.getUnionID() );
			
			if(pCreature->IsNPC() == false)
				pCreature->SetPersnalShop(pPacket->getStoreOutlook().isOpen());
			if(pPacket->getStoreOutlook().isOpen()&& g_pPlayer->IsVampire()== true && pCreature->IsNPC() == false)
			{
				// 2006.04.25 chyaya
				WORD colorIndex = pPacket->getStoreOutlook().getPaintColor();
				pCreature->SetPersnalShopColor( MCreature::s_PersnalShopColor[colorIndex] );

				/*
				if(!pPacket->getStoreOutlook().getSign().empty())
					pCreature->SetPersnalString((char*)pPacket->getStoreOutlook().getSign().c_str(),g_pUserOption->ChattingColor);
				else
					pCreature->SetPersnalString((*g_pGameStringTable)[UI_STRING_MESSAGE_PERSNAL_DEFAULT_MESSGE].GetString(),g_pUserOption->ChattingColor);
				*/

				if(!pPacket->getStoreOutlook().getSign().empty())
					pCreature->SetPersnalString( (char*)pPacket->getStoreOutlook().getSign().c_str() );
				else
					pCreature->SetPersnalString( (*g_pGameStringTable)[UI_STRING_MESSAGE_PERSNAL_DEFAULT_MESSGE].GetString() );
				// by chyaya 2006.04.19

			}

			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
				pCreature = NULL;
			}

		}
		//--------------------------------------------------
		// �̹� �ִ� Creature�� ���
		//--------------------------------------------------
		else
		{
			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, vi.getAdvancementLevel() );
			//--------------------------------------------------
			// CreatureType ����
			//--------------------------------------------------
			Shape_t shape	= vi.getShape();
			bool bMale		= vi.getSex()==MALE;
			ItemType_t coatType = vi.getCoatType();
#if __CONTENTS(__SECOND_TRANSFORTER)
			DWORD wingItemType = vi.getWingItemType();
#endif //__SECOND_TRANSFORTER

			if(shape == SHAPE_BAT && vi.getAdvancementLevel() > 0)
				shape = SHAPE_VAMPIRE_GHOST;

			if (vi.getCompetence()==0)
			{
				pCreature->SetCompetence( 0 );
				pCreature->SetCreatureType( CREATURETYPE_VAMPIRE_OPERATOR );
				pCreature->SetMale( bMale );
			}
			else
			{
				pCreature->SetCreatureType( GetVampireCreatureType( shape, bMale, coatType
#if __CONTENTS(__SECOND_TRANSFORTER)
					, wingItemType
#endif //__SECOND_TRANSFORTER
					));
			}

			pCreature->SetMale( bMale );

			const int CreatureType = pCreature->GetCreatureType();

			if (CreatureType==CREATURETYPE_BAT)
			{
				pCreature->SetFlyingCreature();
			}
			else
			{
				pCreature->SetGroundCreature();
			}
			//pCreature->SetGroundCreature();

			// �ӽ÷�
			pCreature->SetGuildNumber( vi.getGuildID() );
			pCreature->SetOriginServerNum( vi.getBorn() );
			pCreature->SetUnionGuildID( vi.getUnionID() );
			
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( vi.getX(), vi.getY() );
			pCreature->SetServerPosition( vi.getX(), vi.getY() );			
			pCreature->SetDirection( vi.getDir() );
			pCreature->SetCurrentDirection( vi.getDir() );
			pCreature->SetAction( ACTION_STAND );

			// ����
			if( CreatureType == CREATURETYPE_WER_WOLF )
			{
				pCreature->SetBodyColor1( vi.getCoatColor() );
				pCreature->SetBodyColor2( vi.getCoatColor() );
			} else
			{
				pCreature->SetBodyColor1( vi.getSkinColor() );
				pCreature->SetBodyColor2( vi.getCoatColor() );
			}

			pCreature->SetMasterEffectType( vi.getMasterEffectColor() );
			
			//--------------------------------------------------
			// [ TEST CODE ]
			//--------------------------------------------------
			// �� ���� �����ϱ�
			//--------------------------------------------------
			/*
			if (pCreature->IsMale())
			{
				pCreature->SetBodyColor2( 91 );
			}
			else
			{
				pCreature->SetBodyColor2( 38 );
			}
			*/

			
			pCreature->SetStatus( MODIFY_MAX_HP, vi.getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, vi.getCurrentHP() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, vi.getAlignment() );
			pCreature->SetStatus( MODIFY_RANK, vi.getRank() );
			
			pCreature->SetWeaponSpeed( vi.getAttackSpeed() );

			if( vi.getBatColor() != 0 )
				pCreature->SetBatColor( vi.getBatColor() );
			else
				pCreature->SetBatColor( 0xFFFF );

			pCreature->SetAdvanceBatColor( vi.getAdvanceBatColor() );

			if(pCreature->IsNPC() == false)
				pCreature->SetPersnalShop(pPacket->getStoreOutlook().isOpen());
			
			if(pPacket->getStoreOutlook().isOpen()&& g_pPlayer->IsVampire()== true && pCreature->IsNPC() == false)
			{
				// 2006.04.25 chyaya
				WORD colorIndex = pPacket->getStoreOutlook().getPaintColor();
				pCreature->SetPersnalShopColor( MCreature::s_PersnalShopColor[colorIndex] );

				/*
				if(!pPacket->getStoreOutlook().getSign().empty())
					pCreature->SetPersnalString((char*)pPacket->getStoreOutlook().getSign().c_str(),g_pUserOption->ChattingColor);
				else
					pCreature->SetPersnalString((*g_pGameStringTable)[UI_STRING_MESSAGE_PERSNAL_DEFAULT_MESSGE].GetString(),g_pUserOption->ChattingColor);
				*/

				if(!pPacket->getStoreOutlook().getSign().empty())
					pCreature->SetPersnalString( (char*)pPacket->getStoreOutlook().getSign().c_str() );
				else
					pCreature->SetPersnalString( (*g_pGameStringTable)[UI_STRING_MESSAGE_PERSNAL_DEFAULT_MESSGE].GetString() );
				// by chyaya 2006.04.19
			}
		
		}

		if (pCreature!=NULL)
		{
			// Vampire Coat & Weapon - chyaya
			MCreatureWear* pCreatureWear = dynamic_cast<MCreatureWear*>(pCreature);
			if(pCreatureWear)
				SetAddonToVampire(pCreatureWear, &vi);

			//--------------------------------------------------
			// Effect ���̱�..
			//--------------------------------------------------
			SetEffectInfo( pCreature, pPacket->getEffectInfo() );
						
			//--------------------------------------------------
			// ������ ��쿡�� 0, ��Ż�� ������ ��쿡�� 1
			//--------------------------------------------------
			if (pPacket->getFromFlag()==1)
			{
				g_pTopView->VampireComeFromPortal( pCreature );
			}
			
			// �� ó��
			if(pPacket->getPetInfo() != NULL)
				SetPetInfo(pPacket->getPetInfo(), pCreature->GetID());
			NicknameInfo* _tempNick = pPacket->getNicknameInfo();
			if(_tempNick != NULL)
			{
				// Ŀ���� �г��� �϶�
				if(_tempNick->getNicknameType() == NicknameInfo::NICK_CUSTOM_FORCED ||
				   _tempNick->getNicknameType() == NicknameInfo::NICK_CUSTOM)
				{
					pCreature->SetNickName(_tempNick->getNicknameType(), (char*)_tempNick->getNickname().c_str());
					
				}
				else // �г��� �ε����� ���� ��
				{
					int TempIndex = _tempNick->getNicknameIndex();
					if(TempIndex >= g_pNickNameStringTable->GetSize())
						TempIndex = 0;
					pCreature->SetNickName(_tempNick->getNicknameType(), (char*)(*g_pNickNameStringTable)[TempIndex].GetString());
				}
			}

			if(pCreature->GetCreatureType() == CREATURETYPE_VAMPIRE_GHOST)
				pCreature->SetAdvanceBatEffect();
#if __CONTENTS(__FAST_TRANSFORTER)
			if(pCreature->GetCreatureType() == CREATURETYPE_FLITTERMOUSE)
				pCreature->SetWingEffect1();
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
			if(pCreature->GetCreatureType() == CREATURETYPE_SHAPE_OF_DEMON)
				pCreature->SetWingEffect2();
#endif //__SECOND_TRANSFORTER
		}
	}

	// [����] Vampire�� ��Ÿ����
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_CREATURE_APPEAR_VAMPIRE );
//	__END_HELP_EVENT

	__END_CATCH
}
