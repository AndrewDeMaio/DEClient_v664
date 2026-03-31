#include "client_PCH.h"
#include "AutoQAFunctions.h"
#include "VS_UI_Base.h"
#include "VS_UI_GameCommon.h"
#include "MInventory.h"
#include "UIFunction.h"
#include "Packet/Packet.h"
#include "../Script/lua/lua.hpp"


//////////////////////////////////////////////////////////////////////////
// Functions

int AQAFunc_ChatMessage(int nParam, float fParam, const std::string& sParam)
{
	char *pHeapMsg = new char[sParam.size()+1];
	strcpy(pHeapMsg, sParam.c_str());

	gpC_base->SendMessage(UI_CHAT_RETURN, nParam, 0, pHeapMsg);
	return 0;
}

static int AQAScriptFunc_ChatMessage(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 1);
	const char *msg = lua_tostring(L, 1);

	AQAFunc_ChatMessage(0, 0, msg);

	return 0;
}

//--

int AQAFunc_ClearInventory(int nParam, float fParam, const std::string& sParam)
{
	AQAFunc_ChatMessage(CLD_NORMAL, 0, "*command clearInventory");
	aqa::Robot::Instance().WaitForPacket(Packet::PACKET_GC_UPDATE_INFO);

	return 0;
}

static int AQAScriptFunc_ClearInventory(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 0);
	
	AQAFunc_ClearInventory(0, 0, "");

	return 0;
}

//--

int AQAFunc_CreateItem(int nParam, float fParam, const std::string& sParam)
{
	char buffer[256];

	WORD itemClass = HIWORD(nParam);
	WORD itemType = LOWORD(nParam);

	sprintf(buffer, "*create %d %d", itemClass, itemType);

	AQAFunc_ChatMessage(CLD_NORMAL, 0, buffer);
	aqa::Robot::Instance().WaitForPacket(Packet::PACKET_GC_CREATE_ITEM);
	
	return 0;
}

static int AQAScriptFunc_CreateItem(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 2);
	WORD itemClass = (WORD)lua_tonumber(L, 1);
	WORD itemType = (WORD)lua_tonumber(L, 2);
	
	AQAFunc_CreateItem(MAKEDWORD(itemClass, itemType), 0, "");

	return 0;
}

//--

int AQAFunc_UseItem(int nParam, float fParam, const std::string& sParam)
{
	WORD invenX = HIWORD(nParam);
	WORD invenY = LOWORD(nParam);

	MItem* pItem = g_pInventory->GetItem(invenX, invenY);

	if(pItem)
	{
		gpC_base->SendMessage(UI_ITEM_USE, pItem->GetID(), 0, (MItem *)pItem);
	}
		
	return 0;
}

static int AQAScriptFunc_UseItem(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 2);
	WORD invenX = (WORD)lua_tonumber(L, 1);
	WORD invenY = (WORD)lua_tonumber(L, 2);
	
	AQAFunc_UseItem(MAKEDWORD(invenX, invenY), 0, "");

	return 0;
}

//--

int AQAFunc_GetItem(int nParam, float fParam, const std::string& sParam)
{
	WORD invenX = HIWORD(nParam);
	WORD invenY = LOWORD(nParam);

	return (int)g_pInventory->GetItem(invenX, invenY);
}

static int AQAScriptFunc_GetItem(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 2);
	WORD invenX = (WORD)lua_tonumber(L, 1);
	WORD invenY = (WORD)lua_tonumber(L, 2);
	
	MItem *item = (MItem *)AQAFunc_GetItem(MAKEDWORD(invenX, invenY), 0, "");

	lua_pushlightuserdata(L, item);

	return 1;
}

//--

int AQAFunc_PickUpItem(int nParam, float fParam, const std::string& sParam)
{
	WORD invenX = HIWORD(nParam);
	WORD invenY = LOWORD(nParam);

	MItem* pItem = g_pInventory->GetItem(invenX, invenY);

	if(pItem)
	{
		gpC_base->SendMessage(UI_REMOVE_ITEM, invenX, invenY);
		aqa::Robot::Instance().WaitForGuiMessage(UI_REMOVE_ITEM);

		gpC_base->SendMessage(UI_ITEM_PICKUP_FROM_INVENTORY, pItem->GetID(), 0, (MItem *)pItem);
		aqa::Robot::Instance().WaitForGuiMessage(UI_ITEM_PICKUP_FROM_INVENTORY);
	}
		
	return 0;
}

static int AQAScriptFunc_PickUpItem(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 2);
	WORD invenX = (WORD)lua_tonumber(L, 1);
	WORD invenY = (WORD)lua_tonumber(L, 2);
	
	AQAFunc_PickUpItem(MAKEDWORD(invenX, invenY), 0, "");

	return 0;
}

//--

int AQAFunc_ItemToItem(int nParam, float fParam, const std::string& sParam)
{
	WORD invenX = HIWORD(nParam);
	WORD invenY = LOWORD(nParam);

	MItem* pItem = g_pInventory->GetItem(invenX, invenY);

	if(pItem)
	{
		gpC_base->SendMessage(UI_ENCHANT_ACCEPT, invenX, invenY, (MItem *)pItem);
		aqa::Robot::Instance().WaitForPacket(Packet::PACKET_GC_CREATE_ITEM);
	}
		
	return 0;
}

static int AQAScriptFunc_ItemToItem(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 2);
	WORD invenX = (WORD)lua_tonumber(L, 1);
	WORD invenY = (WORD)lua_tonumber(L, 2);
	
	AQAFunc_ItemToItem(MAKEDWORD(invenX, invenY), 0, "");

	return 0;
}

//--

int AQAFunc_WaitForPacket(int nParam, float fParam, const std::string& sParam)
{
	aqa::Robot::Instance().WaitForPacket(nParam);
	return 0;
}

static int AQAScriptFunc_WaitForPacket(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 1);
	WORD packetId = (WORD)lua_tonumber(L, 1);
	
	AQAFunc_WaitForPacket(packetId, 0, "");

	return 0;
}

//--


//////////////////////////////////////////////////////////////////////////
// Register

#define REGISTER(a)				\
	Register(#a, AQAFunc_##a);	\
	lua_register(GetScriptState(), #a, AQAScriptFunc_##a)

AQAFunctions::AQAFunctions()
{
	REGISTER(ChatMessage);

	REGISTER(ClearInventory);
	REGISTER(CreateItem);
	REGISTER(UseItem);
	REGISTER(GetItem);
	REGISTER(PickUpItem);
	REGISTER(ItemToItem);

	REGISTER(WaitForPacket);
}

