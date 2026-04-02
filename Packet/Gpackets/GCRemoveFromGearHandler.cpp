//////////////////////////////////////////////////////////////////////
//
// Filename    : GCRemoveFromGearHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCRemoveFromGear.h"
#include "ClientDef.h"
#include "MSlayerGear.h"
#include "MVampireGear.h"
#include "MOustersGear.h"
#include "MGameStringTable.h"
#include "MItemOptionTable.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCRemoveFromGearHandler::execute ( GCRemoveFromGear * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
	

	int slotID = pPacket->getSlotID();

	//----------------------------------------------------------------------
	// Slayer�� ���
	//----------------------------------------------------------------------
	switch(g_pPlayer->GetRace())
	{
	case RACE_SLAYER:
	{
		MItem* pRemovedItem = g_pSlayerGear->RemoveItem( (MSlayerGear::GEAR_SLAYER)slotID );

		
		if (pRemovedItem==NULL)
		{
			DEBUG_ADD_FORMAT("[Error] No Removed Item in Slot=%d", slotID);
		}
		else
		{
			//----------------------------------------------------------
			// game message ���
			//----------------------------------------------------------

			if(pRemovedItem->GetItemClass() != ITEM_CLASS_COUPLE_RING && pRemovedItem->GetItemClass() != ITEM_CLASS_VAMPIRE_COUPLE_RING && pRemovedItem->GetItemClass() != ITEM_CLASS_OUSTERS_HARMONIC_PENDENT)
			{
				char str[128]; 
				
				if (pRemovedItem->IsEmptyItemOptionList() )
				{
					sprintf(str, "%s %s",					
						pRemovedItem->GetName(),
						(*g_pGameStringTable)[STRING_MESSAGE_ITEM_BROKEN].GetString());
				}
				else
				{
					std::string option_name;
					for(int i = 0; i < pRemovedItem->GetItemOptionListCount(); i++)
					{
						option_name += pRemovedItem->GetItemOptionName(i);
						if(i != pRemovedItem->GetItemOptionListCount())
							option_name += " ";
					}
					sprintf(str, "%s%s %s",					
						option_name.c_str(),	
						pRemovedItem->GetName(),
						(*g_pGameStringTable)[STRING_MESSAGE_ITEM_BROKEN].GetString());
				}
				
				g_pGameMessage->Add(str);
			}
			
			
			
			int addonSlot[] = 
			{
				ADDON_HELM,			//GEAR_SLAYER_HELM = 0,			// ����
					ADDON_NULL,			//GEAR_SLAYER_NECKLACE,			// �����
					ADDON_COAT,			//GEAR_SLAYER_COAT,				// ����
					ADDON_LEFTHAND,		//GEAR_SLAYER_LEFTHAND,			// �޼�
					ADDON_RIGHTHAND,	//GEAR_SLAYER_RIGHTHAND,			// ������
					ADDON_NULL,			//GEAR_SLAYER_GLOVE,				// �尩
					ADDON_NULL,			//GEAR_SLAYER_BELT,				// ����
					ADDON_TROUSER,		//GEAR_SLAYER_TROUSER,			// ����			
					ADDON_NULL,			//GEAR_SLAYER_BRACELET1,			// ����1
					ADDON_NULL,			//GEAR_SLAYER_BRACELET2,			// ����2
					ADDON_NULL,			//GEAR_SLAYER_RING1,				// ����1
					ADDON_NULL,			//GEAR_SLAYER_RING2,				// ����2
					ADDON_NULL,			//GEAR_SLAYER_RING3,				// ����3
					ADDON_NULL,			//GEAR_SLAYER_RING4,				// ����4
					ADDON_NULL,			//GEAR_SLAYER_SHOES,				// �Ź�
			};
		
			//----------------------------------------------------------
			// �޼��ε�.. �޼��� ����� �����տ� ��� �����̸�..
			// �������� ���־� �Ѵ�.
			//----------------------------------------------------------
			if (slotID==MSlayerGear::GEAR_SLAYER_LEFTHAND)
			{
				const MItem* pLeftItem = g_pSlayerGear->GetItem( MSlayerGear::GEAR_SLAYER_LEFTHAND );
				const MItem* pRightItem = g_pSlayerGear->GetItem( MSlayerGear::GEAR_SLAYER_RIGHTHAND );

				if (pLeftItem==NULL 
					&& pRightItem!=NULL && pRightItem->IsGearSlotTwoHand())
				{
					slotID = MSlayerGear::GEAR_SLAYER_RIGHTHAND;
				}
			}

			//----------------------------------------------------------
			// ������ �ٲ��ش�.
			//----------------------------------------------------------
			int addonSlotID = addonSlot[slotID];

			if (addonSlotID != ADDON_NULL)
			{
				g_pPlayer->SetStop();

				#ifdef	OUTPUT_DEBUG				
					if (g_pPlayer->RemoveAddon( addonSlotID ))
					{
						DEBUG_ADD_FORMAT("[OK] RemoveAddon. Slot=%d", addonSlotID);
					}
					else
					{
						const MCreatureWear::ADDON_INFO& addonInfo = g_pPlayer->GetAddonInfo( addonSlotID );
						DEBUG_ADD_FORMAT("[Error] RemoveAddon. Slot=%d, AddonFrameID=%d", addonSlotID, addonInfo.FrameID);						
					}				
				#else
					g_pPlayer->RemoveAddon( addonSlotID );
				#endif
			}

			// item���� ����
			UI_RemoveDescriptor( (void*)pRemovedItem );

			//----------------------------------------------------------
			// item�� ���ش�.
			//----------------------------------------------------------
			delete pRemovedItem;
		}
	}
	break;

	case RACE_VAMPIRE:
	//----------------------------------------------------------------------
	// Vampire�� ���
	//----------------------------------------------------------------------
	{
		MItem* pRemovedItem = g_pVampireGear->RemoveItem( (MVampireGear::GEAR_VAMPIRE)slotID );

		if (pRemovedItem==NULL)
		{
			DEBUG_ADD_FORMAT("[Error] No Removed Item in Slot=%d", slotID);
		}
		else
		{
			//----------------------------------------------------------
			// game message ���
			//----------------------------------------------------------
			
			if(pRemovedItem->GetItemClass() != ITEM_CLASS_COUPLE_RING && pRemovedItem->GetItemClass() != ITEM_CLASS_VAMPIRE_COUPLE_RING && pRemovedItem->GetItemClass() != ITEM_CLASS_OUSTERS_HARMONIC_PENDENT)
			{
				char str[128]; 
				
				if (pRemovedItem->IsEmptyItemOptionList())
				{
					sprintf(str, "%s %s",					
						pRemovedItem->GetName(),
						(*g_pGameStringTable)[STRING_MESSAGE_ITEM_BROKEN].GetString());
				}
				else
				{
					std::string option_name;
					for(int i = 0; i < pRemovedItem->GetItemOptionListCount(); i++)
					{
						option_name += pRemovedItem->GetItemOptionName(i);
						if(i != pRemovedItem->GetItemOptionListCount())
							option_name += " ";
					}
					sprintf(str, "%s%s %s",					
						option_name.c_str(),	
						pRemovedItem->GetName(),
						(*g_pGameStringTable)[STRING_MESSAGE_ITEM_BROKEN].GetString());
				}
				
				g_pGameMessage->Add(str);
			}

			int addonSlot[] = 
			{
				ADDON_NULL,			//GEAR_VAMPIRE_NECKLACE,			// �����
				ADDON_COAT,			//GEAR_VAMPIRE_COAT,				// ����
				ADDON_NULL,			//GEAR_VAMPIRE_BRACELET1,			// ����1
				ADDON_NULL,			//GEAR_VAMPIRE_BRACELET2,			// ����2
				ADDON_NULL,			//GEAR_VAMPIRE_RING1,				// ����1
				ADDON_NULL,			//GEAR_VAMPIRE_RING2,				// ����2
				ADDON_NULL,			//GEAR_VAMPIRE_RING3,				// ����3
				ADDON_NULL,			//GEAR_VAMPIRE_RING4,				// ����4
				ADDON_NULL,			//GEAR_VAMPIRE_EARRING1,			// �Ͱ���1
				ADDON_NULL,			//GEAR_VAMPIRE_EARRING2,			// �Ͱ���2
				ADDON_NULL,			//GEAR_VAMPIRE_WEAPON1,				// ����1
				ADDON_NULL,			//GEAR_VAMPIRE_WEAPON2,				// ����2
				ADDON_NULL,			//GEAR_VAMPIRE_AMULET1,				// �ƹķ�1
				ADDON_NULL,			//GEAR_VAMPIRE_AMULET2,				// �ƹķ�2
				ADDON_NULL,			//GEAR_VAMPIRE_AMULET3,				// �ƹķ�3
				ADDON_NULL,			//GEAR_VAMPIRE_AMULET4,				// �ƹķ�4
			};

			//----------------------------------------------------------
			// �޼��ε�.. �޼��� ����� �����տ� ��� �����̸�..
			// �������� ���־� �Ѵ�.
			//----------------------------------------------------------
			if (slotID==MVampireGear::GEAR_VAMPIRE_LEFTHAND)
			{
				const MItem* pLeftItem = g_pVampireGear->GetItem( MVampireGear::GEAR_VAMPIRE_LEFTHAND );
				const MItem* pRightItem = g_pVampireGear->GetItem( MVampireGear::GEAR_VAMPIRE_RIGHTHAND );

				if (pLeftItem==NULL 
					&& pRightItem!=NULL && pRightItem->IsGearSlotTwoHand())
				{
					slotID = MVampireGear::GEAR_VAMPIRE_RIGHTHAND;
				}
			}

			//----------------------------------------------------------
			// ������ �ٲ��ش�.
			//----------------------------------------------------------
			int addonSlotID = addonSlot[slotID];

			if (addonSlotID != ADDON_NULL)
			{
				g_pPlayer->SetStop();

				#ifdef	OUTPUT_DEBUG				
					if (g_pPlayer->RemoveAddon( addonSlotID ))
					{
						DEBUG_ADD_FORMAT("[OK] RemoveAddon. Slot=%d", addonSlotID);
					}
					else
					{
						const MCreatureWear::ADDON_INFO& addonInfo = g_pPlayer->GetAddonInfo( addonSlotID );
						DEBUG_ADD_FORMAT("[Error] RemoveAddon. Slot=%d, AddonFrameID=%d", addonSlotID, addonInfo.FrameID);						
					}				
				#else
					g_pPlayer->RemoveAddon( addonSlotID );
				#endif
			}

			// item���� ����
			UI_RemoveDescriptor( (void*)pRemovedItem );

			//----------------------------------------------------------
			// item�� ���ش�.
			//----------------------------------------------------------
			delete pRemovedItem;
		}
	}
	break;

	case RACE_OUSTERS:
	{
		MItem* pRemovedItem = g_pOustersGear->RemoveItem( (MOustersGear::GEAR_OUSTERS)slotID );

		if (pRemovedItem==NULL)
		{
			DEBUG_ADD_FORMAT("[Error] No Removed Item in Slot=%d", slotID);
		}
		else
		{
			//----------------------------------------------------------
			// game message ���
			//----------------------------------------------------------
			if(1)
			{
				char str[128]; 
				
				if (pRemovedItem->IsEmptyItemOptionList())
				{
					sprintf(str, "%s %s",					
						pRemovedItem->GetName(),
						(*g_pGameStringTable)[STRING_MESSAGE_ITEM_BROKEN].GetString());
				}
				else
				{
					std::string option_name;
					for(int i = 0; i < pRemovedItem->GetItemOptionListCount(); i++)
					{
						option_name += pRemovedItem->GetItemOptionName(i);
						if(i != pRemovedItem->GetItemOptionListCount())
							option_name += " ";
					}
					sprintf(str, "%s%s %s",					
						option_name.c_str(),	
						pRemovedItem->GetName(),
						(*g_pGameStringTable)[STRING_MESSAGE_ITEM_BROKEN].GetString());
				}
				
				g_pGameMessage->Add(str);
			}

			int addonSlot[] = 
			{
				ADDON_NULL,			//GEAR_OUSTERS_CIRCLET,			// ��Ŭ��
				ADDON_COAT,			//GEAR_OUSTERS_COAT,				// ��
				ADDON_LEFTHAND,		//GEAR_OUSTERS_LEFTHAND,			// �޼�
				ADDON_RIGHTHAND,	//GEAR_OUSTERS_RIGHTHAND,			// ������
				ADDON_TROUSER,			//GEAR_OUSTERS_BOOTS,				// �Ź�
				ADDON_NULL,			//GEAR_OUSTERS_ARMSBAND1,			// �Ͻ����1
				ADDON_NULL,			//GEAR_OUSTERS_ARMSBAND2,			// �Ͻ����2
				ADDON_NULL,			//GEAR_OUSTERS_RING1,				// ��1
				ADDON_NULL,			//GEAR_OUSTERS_RING2,				// ��2
				ADDON_NULL,			//GEAR_OUSTERS_NECKLACE1,			// �����1
				ADDON_NULL,			//GEAR_OUSTERS_NECKLACE2,			// �����2
				ADDON_NULL,			//GEAR_OUSTERS_NECKLACE3,			// �����3
				ADDON_NULL,			//GEAR_OUSTERS_STONE1,			// ���ɼ�1
				ADDON_NULL,			//GEAR_OUSTERS_STONE2,			// ���ɼ�2
				ADDON_NULL,			//GEAR_OUSTERS_STONE3,			// ���ɼ�3
				ADDON_NULL,			//GEAR_OUSTERS_STONE4,			// ���ɼ�4
			};

			//----------------------------------------------------------
			// �޼��ε�.. �޼��� ����� �����տ� ��� �����̸�..
			// �������� ���־� �Ѵ�.
			//----------------------------------------------------------
			if (slotID==MOustersGear::GEAR_OUSTERS_LEFTHAND)
			{
				const MItem* pLeftItem = g_pOustersGear->GetItem( MOustersGear::GEAR_OUSTERS_LEFTHAND );
				const MItem* pRightItem = g_pOustersGear->GetItem( MOustersGear::GEAR_OUSTERS_RIGHTHAND );

				if (pLeftItem==NULL 
					&& pRightItem!=NULL && pRightItem->IsGearSlotTwoHand())
				{
					slotID = MOustersGear::GEAR_OUSTERS_RIGHTHAND;
				}
			}

			//----------------------------------------------------------
			// ������ �ٲ��ش�.
			//----------------------------------------------------------
			int addonSlotID = addonSlot[slotID];

			if (addonSlotID != ADDON_NULL)
			{
				g_pPlayer->SetStop();

				#ifdef	OUTPUT_DEBUG				
					if (g_pPlayer->RemoveAddon( addonSlotID ))
					{
						DEBUG_ADD_FORMAT("[OK] RemoveAddon. Slot=%d", addonSlotID);
					}
					else
					{
						const MCreatureWear::ADDON_INFO& addonInfo = g_pPlayer->GetAddonInfo( addonSlotID );
						DEBUG_ADD_FORMAT("[Error] RemoveAddon. Slot=%d, AddonFrameID=%d", addonSlotID, addonInfo.FrameID);						
					}				
				#else
					g_pPlayer->RemoveAddon( addonSlotID );
				#endif
			}

			// item���� ����
			UI_RemoveDescriptor( (void*)pRemovedItem );

			//----------------------------------------------------------
			// item�� ���ش�.
			//----------------------------------------------------------
			delete pRemovedItem;
		}
	}
	break;
	}

//	// [����] �������� �μ��� ���
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_ITEM_BROKEN );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
