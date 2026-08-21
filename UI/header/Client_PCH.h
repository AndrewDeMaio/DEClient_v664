////////////////////////////////////////////////////////////////////////////////
//	created:	2004/12/22
//	file base:	client_pch.h
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#pragma warning(disable:4290)
#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4786)
#pragma warning(disable:4103)
#pragma warning(disable:4049)

#pragma warning(error: 4067)

#pragma warning(push)

#include <string>
#include <assert.h>
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <bitset>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <MMSystem.h>
#include <Digitalv.h>
#include <DDraw.h>
#include <cstdio>
#include <cstdarg>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "atltypes.h"
#include "ContentsFilter.h"

//-----------------------------------------------------------------------------
// __CRYPT is forced OFF here, after ContentsFilter.h, so that the rest of
// __DESIGNED_INTERNATION stays intact.
//
// __DESIGNED_INTERNATION is the only design that sets __CRYPT __ON, and that
// flag controls the wire header itself (Packet.h): ON gives a 10-byte encrypted
// PACKETDATA header, OFF gives the plain 6-byte PacketID + PacketSize header.
//
// DEServer_v664 has no crypt path at all - no MSG_HEADER_SIZE, no PACKETDATA,
// no CCryptManager anywhere in src/ - so it only ever speaks the 6-byte header.
// With __CRYPT ON the server read our encrypted size field as the packet ID and
// rejected the connection (it reported id 605, which is past PACKET_MAX on both
// sides).
//
// Turning it off also flips Encrypter.h's "#if !__CONTENTS(__CRYPT)" so that
// __USE_ENCRYPTER__ becomes defined and ClientPlayer uses SocketEncrypt*Stream.
// That is required too: the server's Encrypter.h defines __USE_ENCRYPTER__
// unconditionally, and the two Encrypter classes are byte-for-byte identical.
//-----------------------------------------------------------------------------
#undef  __CRYPT
#define __CRYPT __OFF

//-----------------------------------------------------------------------------
// __PCITEMINFO is forced ON for the same reason as __CRYPT above: the server
// does not have this flag at all.
//
// __DESIGNED_INTERNATION sets __PCITEMINFO __OFF, which selects a second,
// completely different implementation of GCAddItemToZone / GCAddNewItemToZone /
// GCDropItemToZone / GCCreateItem / GCTradeAddItem. DEServer_v664 implements
// only the __ON form, e.g. GCAddItemToZone::write is:
//
//     oStream.write( m_X ); oStream.write( m_Y ); m_PCItemInfo.write(oStream);
//
// With the flag OFF the client instead read ObjectID, X, Y, ItemClass,
// ItemType, ... so it consumed the server's X as an ObjectID and the server's Y
// as X. Every ground item therefore landed on a garbage tile, scattering items
// across the whole zone (they were real and pickable, just misplaced).
//-----------------------------------------------------------------------------
#undef  __PCITEMINFO
#define __PCITEMINFO __ON
#pragma warning(pop)

using std::string;
using std::vector;
using std::map;
using std::list;
using std::deque;
using std::bitset;