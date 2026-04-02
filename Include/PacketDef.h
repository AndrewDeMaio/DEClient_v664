//----------------------------------------------------------------------
// PacketDef.h
//----------------------------------------------------------------------
// Client에서 사용하는 Packet에 대한 정의
//----------------------------------------------------------------------
#ifndef	__PACKETDEF_H__
#define	__PACKETDEF_H__

//-----------------------------------------------------------------------------
// Login
//-----------------------------------------------------------------------------
#include "Cpackets\CLVersionCheck.h"
#include "Cpackets\CLLogout.h"
#include "Cpackets\CLLogin.h"
#include "Cpackets\CLRegisterPlayer.h"
#include "Cpackets\CLGetPCList.h"
#include "Cpackets\CLCreatePC.h"
#include "Cpackets\CLDeletePC.h"
#include "Cpackets\CLSelectPC.h"
#include "Cpackets\CLQueryPlayerID.h"

//-----------------------------------------------------------------------------
// core
//-----------------------------------------------------------------------------
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "Properties.h"
#include "ClientPlayer.h"
#include "Socket.h"

//-----------------------------------------------------------------------------
// connect
//-----------------------------------------------------------------------------
#include "Cpackets\CGConnect.h"
#include "Cpackets\CGReady.h"
#include "Cpackets\CGMove.h"
#include "Cpackets\CGLogout.h"

//-----------------------------------------------------------------------------
// Phone / Whisper
//-----------------------------------------------------------------------------
#include "Cpackets\CGDialUp.h"
#include "Cpackets\CGPhoneDisconnect.h"
#include "Cpackets\CGPhoneSay.h"
#include "Cpackets\CGWhisper.h"

//-----------------------------------------------------------------------------
// 채팅
//-----------------------------------------------------------------------------
#include "Cpackets\CGSay.h"
#include "Cpackets\CGGlobalChat.h"


//-----------------------------------------------------------------------------
// 기술 사용
//-----------------------------------------------------------------------------
#include "Cpackets\CGAttack.h"
#include "Cpackets\CGCastingSkill.h"
#include "Cpackets\CGSkillToInventory.h"
#include "Cpackets\CGSkillToSelf.h"
#include "Cpackets\CGSkillToTile.h"
#include "Cpackets\CGSkillToObject.h"
#include "Cpackets\CGUnburrow.h"
#include "Cpackets\CGBloodDrain.h"
// 2001.4.23에 추가
#include "Cpackets\CGThrowBomb.h"
#include "Cpackets\CGUntransform.h"
#include "Cpackets\CGVisible.h"
#include "Cpackets\CGAbsorbSoul.h"

//-----------------------------------------------------------------------------
// skill 배움 / skill 단축키
//-----------------------------------------------------------------------------
#include "Cpackets\CGLearnSkill.h"
#include "Cpackets\CGUseBonusPoint.h"		// for vampire lev up
#include "Cpackets\CGSetSlayerHotKey.h"
#include "Cpackets\CGSetVampireHotKey.h"


//-----------------------------------------------------------------------------
// Item 
//-----------------------------------------------------------------------------
#include "Cpackets\CGAddGearToMouse.h"
#include "Cpackets\CGAddInventoryToMouse.h"
#include "Cpackets\CGAddMouseToGear.h"
#include "Cpackets\CGAddMouseToInventory.h"
#include "Cpackets\CGAddMouseToQuickSlot.h"
#include "Cpackets\CGAddMouseToZone.h"
#include "Cpackets\CGAddQuickSlotToMouse.h"
#include "Cpackets\CGAddZoneToInventory.h"
#include "Cpackets\CGAddZoneToMouse.h"
#include "Cpackets\CGPickupMoney.h"
#include "Cpackets\CGDropMoney.h"
#include "Cpackets\CGRequestRepair.h"
#include "Cpackets\CGMakeItem.h"

//-----------------------------------------------------------------------------
// 시체 click
//-----------------------------------------------------------------------------
#include "Cpackets\CGDissectionCorpse.h"

// 탄창
#include "Cpackets\CGReloadFromInventory.h"
#include "Cpackets\CGReloadFromQuickSlot.h"

// 오토바이
#include "Cpackets\CGGetOffMotorCycle.h"
#include "Cpackets\CGRideMotorCycle.h"

// 던지기
#include "Cpackets\CGThrowItem.h"

// potion
#include "Cpackets\CGUsePotionFromInventory.h"
#include "Cpackets\CGUsePotionFromQuickSlot.h"

#include "Cpackets\CGUseItemFromInventory.h"

//-----------------------------------------------------------------------------
// NPC
//-----------------------------------------------------------------------------
#include "Cpackets\CGNPCTalk.h"
#include "Cpackets\CGNPCAskAnswer.h"

//-----------------------------------------------------------------------------
// 상점
//-----------------------------------------------------------------------------
#include "Cpackets\CGShopRequestList.h"
#include "Cpackets\CGShopRequestBuy.h"
#include "Cpackets\CGShopRequestSell.h"

//-----------------------------------------------------------------------------
// 보관
//-----------------------------------------------------------------------------
#include "Cpackets\CGStashRequestBuy.h"
#include "Cpackets\CGStashList.h"
#include "Cpackets\CGMouseToStash.h"
#include "Cpackets\CGStashToMouse.h"
#include "Cpackets\CGStashDeposit.h"
#include "Cpackets\CGStashWithdraw.h"

//-----------------------------------------------------------------------------
// 교환
//-----------------------------------------------------------------------------
#include "Cpackets\CGTradePrepare.h"
#include "Cpackets\CGTradeAddItem.h"
#include "Cpackets\CGTradeRemoveItem.h"
#include "Cpackets\CGTradeMoney.h"
#include "Cpackets\CGTradeFinish.h"





#endif