//--------------------------------------------------------------------------------
//
// Filename    : GCAddOustersHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddOusters.h"
#include "ClientDef.h"
#include "MCreatureTable.h"
#include "MTestDef.h"
#include "MGameStringTable.h"

extern void SetPetInfo(PetInfo* pPetInfo, TYPE_OBJECTID objectID);
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddOustersHandler::execute ( GCAddOusters * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
		
	
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
		const PCOustersInfo3 & oi = pPacket->getOustersInfo ();

		MCreature* pCreature = g_pZone->GetCreature(oi.getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreatureWear;
			
			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, oi.getAdvancementLevel() );

			pCreature->SetZone( g_pZone );

			pCreature->SetName( oi.getName().c_str() );

			//--------------------------------------------------
			// CreatureType ����
			//--------------------------------------------------
			ItemType_t coatType = oi.getCoatType();

			if (oi.getCompetence()==0)
			{
				pCreature->SetCompetence( 0 );
				pCreature->SetCreatureType( CREATURETYPE_OUSTERS_OPERATOR );
			}
			else
			{
				pCreature->SetCreatureType( GetOustersCreatureType( coatType ) );
			}

			pCreature->SetID(oi.getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( oi.getX(), oi.getY() );
			pCreature->SetServerPosition( oi.getX(), oi.getY() );
			pCreature->SetDirection( oi.getDir() );
			pCreature->SetCurrentDirection( oi.getDir() );
			pCreature->SetAction( ACTION_STAND );

			// ����
			pCreature->SetBodyColor1( oi.getHairColor() );
			pCreature->SetBodyColor2( oi.getCoatColor() );

#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
			pCreature->SetWingType(oi.getWingSylphType());
			pCreature->SetWingColor(oi.getWingBodyColor());
			pCreature->SetWingEffectColor(oi.getWingEffectColor());
#if __CONTENTS(__SECOND_TRANSFORTER)
			pCreature->SetWingItemType(oi.getWingItemType());
#endif //__SECOND_TRANSFORTER
#endif//__FAST_TRANSFORTER||__SECOND_TRANSFORTER
			pCreature->SetMasterEffectType( oi.getMasterEffectColor() );
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

			pCreature->SetStatus( MODIFY_MAX_HP, oi.getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, oi.getCurrentHP() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, oi.getAlignment() );
			pCreature->SetStatus( MODIFY_RANK, oi.getRank() );
#if __CONTENTS(__CONTRIBUTE_SYSTEM)
			pCreature->SetStatus( MODIFY_CONTRIBUTE_POINT, oi.getContributePoint());
#endif //__CONTRIBUTE_SYSTEM
			//oi.getName()
			// ���� ����

			pCreature->SetWeaponSpeed( oi.getAttackSpeed() );
			
			// �ӽ÷�
			pCreature->SetGuildNumber( oi.getGuildID() );
			pCreature->SetOriginServerNum( oi.getBorn() );
			pCreature->SetUnionGuildID( oi.getUnionID() );
			if(pCreature->IsNPC() == false)
				pCreature->SetPersnalShop(pPacket->getStoreOutlook().isOpen());
			if(pPacket->getStoreOutlook().isOpen()&& g_pPlayer->IsOusters()== true && pCreature->IsNPC() == false)
			{
				// 2006.04.25 chyaya
				WORD colorIndex = pPacket->getStoreOutlook().getPaintColor();
				pCreature->SetPersnalShopColor( MCreature::s_PersnalShopColor[colorIndex] );


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
			//--------------------------------------------------
			// CreatureType ����
			//--------------------------------------------------
			ItemType_t coatType = oi.getCoatType();

			if (oi.getCompetence()==0)
			{
				pCreature->SetCompetence( 0 );
				pCreature->SetCreatureType( CREATURETYPE_OUSTERS_OPERATOR );
			}
			else
			{
				pCreature->SetCreatureType( GetOustersCreatureType( coatType ) );
			}

			// �ӽ÷�
			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, oi.getAdvancementLevel() );
			pCreature->SetGuildNumber( oi.getGuildID() );
			pCreature->SetOriginServerNum( oi.getBorn() );
			pCreature->SetUnionGuildID( oi.getUnionID() );
			
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( oi.getX(), oi.getY() );
			pCreature->SetServerPosition( oi.getX(), oi.getY() );			
			pCreature->SetDirection( oi.getDir() );
			pCreature->SetCurrentDirection( oi.getDir() );
			pCreature->SetAction( ACTION_STAND );

			// ����
			pCreature->SetBodyColor1( oi.getHairColor() );
			pCreature->SetBodyColor2( oi.getCoatColor() );
			pCreature->SetMasterEffectType( oi.getMasterEffectColor() );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
			pCreature->SetWingType(oi.getWingSylphType());
			pCreature->SetWingColor(oi.getWingBodyColor());
			pCreature->SetWingEffectColor(oi.getWingEffectColor());
#if __CONTENTS(__SECOND_TRANSFORTER)
			pCreature->SetWingItemType(oi.getWingItemType());
#endif //__SECOND_TRANSFORTER
#endif//__FAST_TRANSFORTER||__SECOND_TRANSFORTER
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

			pCreature->SetStatus( MODIFY_MAX_HP, oi.getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, oi.getCurrentHP() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, oi.getAlignment() );
			pCreature->SetStatus( MODIFY_RANK, oi.getRank() );

			pCreature->SetWeaponSpeed( oi.getAttackSpeed() );
			
			if(pCreature->IsNPC() == false)
				pCreature->SetPersnalShop(pPacket->getStoreOutlook().isOpen());

			if(pPacket->getStoreOutlook().isOpen()&& g_pPlayer->IsOusters()== true && pCreature->IsNPC() == false)
			{

			// 2006.04.25 chyaya
				WORD colorIndex = pPacket->getStoreOutlook().getPaintColor();
				pCreature->SetPersnalShopColor( MCreature::s_PersnalShopColor[colorIndex] );


				if(!pPacket->getStoreOutlook().getSign().empty())
					pCreature->SetPersnalString( (char*)pPacket->getStoreOutlook().getSign().c_str() );
				else
					pCreature->SetPersnalString( (*g_pGameStringTable)[UI_STRING_MESSAGE_PERSNAL_DEFAULT_MESSGE].GetString() );
				// by chyaya 2006.04.19
 
//				pCreature->SetPersnalString((char *)pPacket->getStoreOutlook().getSign().c_str());
//				pCreature->SetPersnalShop(pPacket->getStoreOutlook().isOpen());
			}

			
		}

		if (pCreature!=NULL)
		{
			//--------------------------------------------------
			// Effect ���̱�..
			//--------------------------------------------------
			SetEffectInfo( pCreature, pPacket->getEffectInfo() );
			
			SetAddonToOusters( (MCreatureWear*)pCreature, &oi );			

			// �� ó��
			if(pPacket->getPetInfo() != NULL)
				SetPetInfo(pPacket->getPetInfo(), pCreature->GetID());

			DEBUG_ADD_FORMAT("[GCADDOUSTERS] ID = %d", pCreature->GetName());	
			
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

		}
	}

#endif

	__END_CATCH
}
