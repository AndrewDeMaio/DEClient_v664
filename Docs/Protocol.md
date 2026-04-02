# DarkEden MMORPG — Client/Server Packet Protocol Reference

**Project:** DEClient\_v664 / DEServer\_v664
**Date:** 2026-04-02
**Source:** `Packet/Packet.h`, `Packet/Cpackets/`, `Packet/Gpackets/`, `Packet/Lpackets/`, `Packet/Types/`

---

## 1. Overview

### Wire Header

Every packet begins with a fixed 6-byte header (with `#pragma pack(1)` alignment):

| Field | Type | Size | Description |
|-------|------|------|-------------|
| PacketID | `PacketID_t` (ushort) | 2 bytes | Opcode — identifies the packet class |
| PacketSize | `PacketSize_t` (uint) | 4 bytes | Body length in bytes (excludes header) |

When the `__CONTENTS(__CRYPT)` preprocessor flag is enabled, the header is replaced by an encrypted structure of size `MSG_HEADER_SIZE` (the `PACKETDATA` struct). In that mode the server calls `oStream.EncryptHeader()` before transmitting.

### Byte Order

Little-endian throughout.

### String Encoding

Variable-length strings are sent as: `BYTE length` followed by `length` raw bytes (no null terminator on the wire). The receiver allocates `std::string` from those bytes.

### Packet Dispatch

`PacketFactoryManager` maps each opcode to a `PacketFactory` instance. On arrival the factory calls `createPacket()`, then `read()` deserialises the body, and finally `execute()` dispatches to the handler class. Handlers named `*Handler` live server-side; on the client the `execute()` method directly drives game-state.

---

## 2. Server Architecture

```
  ┌────────────────────────────────────────────────────────┐
  │  Client                                                │
  │  (DEClient_v664)                                       │
  └───┬──────────────┬──────────────┬──────────────────────┘
      │ CG / GC      │ CL / LC      │ CU / UC   │ CR / RC
      ▼              ▼              ▼            ▼
  Game Server    Login Server   Update Svr   Recorder Svr
      │                │
      │ GS / SG        │ GL / LG
      ▼                ▼
  Shared Server   Game Server
      │
      │ GG  (cross-server)
      ▼
  Game Server (peer)
```

- **CG / GC** — Client ↔ Game Server (gameplay traffic)
- **CL / LC** — Client ↔ Login Server (authentication, character list)
- **CU / UC** — Client ↔ Update Server (patch downloads)
- **CR / RC** — Client ↔ Recorder Server (replay / spectator)
- **GL / LG** — Game Server ↔ Login Server (session hand-off)
- **GS / SG** — Game Server ↔ Shared Server (guild, friend, cross-zone state)
- **GG**      — Game Server ↔ Game Server (cross-server commands)

---

## 3. Packet Direction Prefixes

| Prefix | From | To | Notes |
|--------|------|----|-------|
| CG | Client | Game Server | Client-initiated gameplay requests |
| GC | Game Server | Client | Server push to one or many clients |
| CL | Client | Login Server | Login / character management |
| LC | Login Server | Client | Login responses |
| CU | Client | Update Server | Update requests |
| UC | Update Server | Client | Update responses |
| CR | Client | Recorder Server | Spectator connect / whisper |
| RC | Recorder Server | Client | Spectator responses |
| GL | Game Server | Login Server | Notify login server of incoming connection |
| LG | Login Server | Game Server | Login hand-off, kick |
| GS | Game Server | Shared Server | Guild/friend actions |
| SG | Shared Server | Game Server | Guild/friend responses |
| GG | Game Server | Game Server | Cross-server commands / chat |
| GM | Game (internal) | — | Server-info broadcast |

---

## 4. Core Type Definitions

Types are defined across `Packet/Types/*.h` and `Packet/CreatureTypes.h` (inlined in `CreatureTypes.h` via `Types.h`).

### Primitive Aliases (`SystemTypes.h`)

| Typedef | Underlying C++ | Size | Description |
|---------|---------------|------|-------------|
| `uchar` | `unsigned char` | 1 | Unsigned byte alias |
| `ushort` | `unsigned short` | 2 | Unsigned 16-bit |
| `uint` | `unsigned int` | 4 | Unsigned 32-bit |
| `ulong` | `unsigned long` | 4 | Unsigned 32-bit (Win32) |
| `BYTE` | `unsigned char` | 1 | Windows-style byte |
| `WORD` | `unsigned short` | 2 | Windows-style 16-bit |
| `DWORD` | `unsigned long` | 4 | Windows-style 32-bit |
| `ulonglong` | `unsigned long long` | 8 | 64-bit unsigned |

### Network / Identity Types

| Typedef | Underlying | Size | Description |
|---------|-----------|------|-------------|
| `PacketID_t` | `ushort` | 2 | Wire opcode |
| `PacketSize_t` | `uint` | 4 | Body byte count |
| `ObjectID_t` | `DWORD` | 4 | Unique ID for any in-world object |
| `ServerGroupID_t` | `BYTE` | 1 | Server group identifier |
| `ServerID_t` | `WORD` | 2 | Sub-server identifier |
| `WorldID_t` | `BYTE` | 1 | World identifier |
| `IP_t` | `unsigned long` | 4 | IPv4 address (little-endian) |
| `UserNum_t` | `WORD` | 2 | Connected user count |

### Zone & Position Types

| Typedef | Underlying | Size | Description |
|---------|-----------|------|-------------|
| `Coord_t` | `BYTE` | 1 | Zone-local tile coordinate (0–255) |
| `Dir_t` | `BYTE` | 1 | Direction (0=LEFT … 7=LEFTUP) |
| `CoordInven_t` | `BYTE` | 1 | Inventory grid coordinate |
| `ZoneID_t` | `WORD` | 2 | Zone identifier |
| `ZoneGroupID_t` | `WORD` | 2 | Zone group identifier |
| `ZoneLevel_t` | `BYTE` | 1 | Zone difficulty level |
| `ZoneCoord_t` | `WORD` | 2 | World-space zone coordinate |

### Character / Combat Types

| Typedef | Underlying | Size | Description |
|---------|-----------|------|-------------|
| `PCType` (enum) | `BYTE` | 1 | Character race: SLAYER=0, VAMPIRE=1, OUSTERS=2 |
| `Sex` (enum) | `BYTE` | 1 | FEMALE=0, MALE=1 |
| `HairStyle` (enum) | `BYTE` | 1 | Hair style index |
| `Slot` (enum) | `BYTE` | 1 | Character slot (SLOT1–SLOT3) |
| `Level_t` | `BYTE` | 1 | Character level |
| `HP_t` | `WORD` | 2 | Hit points |
| `MP_t` | `WORD` | 2 | Magic/mana points |
| `Attr_t` | `WORD` | 2 | STR/DEX/INT/etc attribute value |
| `Rank_t` | `BYTE` | 1 | Rank (0–?) |
| `RankExp_t` | `DWORD` | 4 | Rank experience points |
| `Exp_t` | `DWORD` | 4 | Experience points |
| `Fame_t` | `DWORD` | 4 | Fame / reputation |
| `Gold_t` | `DWORD` | 4 | Silver/gold currency (max 2,000,000,000) |
| `Damage_t` | `WORD` | 2 | Damage value |
| `Defense_t` | `WORD` | 2 | Defense rating |
| `ToHit_t` | `WORD` | 2 | To-hit rating |
| `Turn_t` | `DWORD` | 4 | Duration in 0.1-second turns |
| `Alignment_t` | `int` | 4 | Alignment (LESS_EVIL to MORE_GOOD) |
| `Shape_t` | `BYTE` | 1 | Transformation shape (0=normal, 1=wolf, 2=bat…) |
| `Resist_t` | `short` | 2 | Elemental resistance (max 90) |
| `Luck_t` | `short` | 2 | Luck stat |
| `ClanType_t` | `WORD` | 2 | Clan type |

### Skill / Effect Types

| Typedef | Underlying | Size | Description |
|---------|-----------|------|-------------|
| `SkillType_t` | `WORD` | 2 | Skill identifier |
| `SkillLevel_t` | `BYTE` | 1 | Skill level |
| `SkillDomainType_t` | `BYTE` | 1 | Skill domain (blade/sword/gun/heal/enchant/etc) |
| `SkillExp_t` | `DWORD` | 4 | Skill experience |
| `SkillBonus_t` | `WORD` | 2 | Skill bonus points |
| `EffectID_t` | `WORD` | 2 | Server-side effect identifier |
| `CEffectID_t` | `WORD` | 2 | Client-side effect identifier |
| `SlotID_t` | `BYTE` | 1 | Gear slot identifier |
| `ExpLevel_t` | `WORD` | 2 | Experience level |
| `Bullet_t` | `BYTE` | 1 | Remaining ammo count |

### Item / Shop Types

| Typedef | Underlying | Size | Description |
|---------|-----------|------|-------------|
| `ItemType_t` | `WORD` | 2 | Item class/type identifier |
| `ItemClass_t` | `BYTE` | 1 | Broad item class (weapon, armour, etc.) |
| `ItemID_t` | `DWORD` | 4 | Database item record ID |
| `StorageID_t` | `DWORD` | 4 | Storage container identifier |
| `OptionType_t` | `BYTE` | 1 | Item option/affix type |
| `Durability_t` | varies | — | Item durability |
| `Silver_t` | varies | — | Silver-coating amount |
| `EnchantLevel_t` | varies | — | Enchant level |
| `Grade_t` | `int` | 4 | Item grade |
| `Price_t` | `DWORD` | 4 | Item price in gold |
| `ItemNum_t` | varies | — | Stack count |
| `ShopRackType_t` | `BYTE` | 1 | Shop rack: NORMAL=0, SPECIAL=1, MYSTERIOUS=2 |
| `ShopVersion_t` | `long` | 4 | Shop inventory version number |
| `MarketCond_t` | `short` | 2 | Market buy/sell condition modifier |

### NPC / Zone Misc

| Typedef | Underlying | Size | Description |
|---------|-----------|------|-------------|
| `MonsterType_t` | `WORD` | 2 | Monster type ID |
| `SpriteType_t` | `WORD` | 2 | Visual sprite type |
| `NPCType_t` | `WORD` | 2 | NPC type ID |
| `NPCID_t` | `WORD` | 2 | NPC instance identifier |
| `ScriptID_t` | varies | — | NPC dialogue script ID |
| `Moral_t` | `BYTE` | 1 | Moral alignment byte |
| `Nation_t` | `BYTE` | 1 | Nation (KOREA=0, USA=1, JAPAN=2) |

---

## 5. Complete Opcode Table

> 602 opcodes total. Direction uses the prefix of the enum name.

### 0–23: Core Gameplay (CG — Client to Game Server)

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 0 | PACKET_CG_ATTACK | C→G | Client attacks a target object |
| 1 | PACKET_CG_ADD_GEAR_TO_MOUSE | C→G | Pick up gear slot item to mouse cursor |
| 2 | PACKET_CG_ADD_INVENTORY_TO_MOUSE | C→G | Pick up inventory item to mouse cursor |
| 3 | PACKET_CG_ADD_MOUSE_TO_GEAR | C→G | Place mouse-held item into gear slot |
| 4 | PACKET_CG_ADD_MOUSE_TO_INVENTORY | C→G | Place mouse-held item into inventory |
| 5 | PACKET_CG_ADD_MOUSE_TO_QUICKSLOT | C→G | Place item into quickslot |
| 6 | PACKET_CG_ADD_MOUSE_TO_ZONE | C→G | Drop mouse-held item to zone |
| 7 | PACKET_CG_ADD_QUICKSLOT_TO_MOUSE | C→G | Pick up quickslot item to mouse cursor |
| 8 | PACKET_CG_ADD_ZONE_TO_MOUSE | C→G | Pick up zone (ground) item to mouse cursor |
| 9 | PACKET_CG_ADD_ZONE_TO_INVENTORY | C→G | Pick up zone item directly to inventory |
| 10 | PACKET_CG_CONNECT | C→G | Connect/enter game with auth key and character name |
| 11 | PACKET_CG_GET_OFF_MOTORCYCLE | C→G | Dismount motorcycle |
| 12 | PACKET_CG_LEARN_SKILL | C→G | Learn a skill from NPC |
| 13 | PACKET_CG_LOGOUT | C→G | Graceful client logout |
| 14 | PACKET_CG_MOVE | C→G | Move character to tile (X, Y, Dir) |
| 15 | PACKET_CG_READY | C→G | Client ready acknowledgement after zone load |
| 16 | PACKET_CG_RELOAD_FROM_INVENTORY | C→G | Reload weapon from inventory ammo |
| 17 | PACKET_CG_RELOAD_FROM_QUICKSLOT | C→G | Reload weapon from quickslot ammo |
| 18 | PACKET_CG_RIDE_MOTORCYCLE | C→G | Mount motorcycle |
| 19 | PACKET_CG_SAY | C→G | Local chat message |
| 20 | PACKET_CG_SKILL_TO_INVENTORY | C→G | Use skill targeting own inventory item |
| 21 | PACKET_CG_THROW_ITEM | C→G | Throw an item as a projectile |
| 22 | PACKET_CG_USE_POTION_FROM_INVENTORY | C→G | Use potion from inventory slot |
| 23 | PACKET_CG_USE_POTION_FROM_QUICKSLOT | C→G | Use potion from quickslot |

### 24–46: Login, Update Server, Chat System

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 24 | PACKET_CL_CREATE_PC | C→L | Create a new player character |
| 25 | PACKET_CL_DELETE_PC | C→L | Delete a player character |
| 26 | PACKET_CL_GET_PC_LIST | C→L | Request character list |
| 27 | PACKET_CL_LOGIN | C→L | Authenticate with ID and password |
| 28 | PACKET_CL_LOGOUT | C→L | Logout from login server |
| 29 | PACKET_CL_QUERY_PLAYER_ID | C→L | Query player ID from name |
| 30 | PACKET_CL_REGISTER_PLAYER | C→L | Register a new player account |
| 31 | PACKET_CL_SELECT_PC | C→L | Select character to play |
| 32 | PACKET_CG_GLOBAL_CHAT | C→G | Send a global (world-wide) chat message |
| 33 | PACKET_GC_GLOBAL_CHAT | G→C | Broadcast global chat to clients |
| 34 | PACKET_GC_SYSTEM_MESSAGE | G→C | System notification message |
| 35 | PACKET_GC_USE_OK | G→C | Generic item/action use success |
| 36 | PACKET_GC_TAKE_OFF | G→C | Force item removal from gear slot |
| 37 | PACKET_CG_CASTING_SKILL | C→G | Begin skill casting animation |
| 38 | PACKET_GC_CASTING_SKILL | G→C | Broadcast skill casting to nearby clients |
| 39 | PACKET_GC_RELOAD_OK | G→C | Weapon reload success |
| 40 | PACKET_CG_NPC_TALK | C→G | Initiate dialogue with NPC |
| 41 | PACKET_GC_NPC_ASK | G→C | NPC sends dialogue/menu to client |
| 42 | PACKET_GC_NPC_SAY | G→C | NPC broadcasts text to nearby players |
| 43 | PACKET_CG_DISSECTION_CORPSE | C→G | Dissect a monster corpse |
| 44 | PACKET_CU_BEGIN_UPDATE | C→U | Begin patch/update download |
| 45 | PACKET_CU_END_UPDATE | C→U | Finish patch/update download |
| 46 | PACKET_CU_REQUEST | C→U | Request specific update file |

### 47–130: Creature & Combat

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 47 | PACKET_GC_ADD_MONSTER | G→C | Spawn monster in client viewport |
| 48 | PACKET_GC_ADD_MONSTER_CORPSE | G→C | Add monster corpse to zone |
| 49 | PACKET_GC_ADD_NEW_ITEM_TO_ZONE | G→C | Add new item object to zone floor |
| 50 | PACKET_GC_ADD_NPC | G→C | Add NPC to viewport |
| 51 | PACKET_GC_ADD_SLAYER | G→C | Add Slayer (PC) to viewport |
| 52 | PACKET_GC_ADD_SLAYER_CORPSE | G→C | Add Slayer corpse to zone |
| 53 | PACKET_GC_ADD_VAMPIRE | G→C | Add Vampire (PC) to viewport |
| 54 | PACKET_GC_ADD_VAMPIRE_CORPSE | G→C | Add Vampire corpse to zone |
| 55 | PACKET_GC_ATTACK_ARMS_OK_1 | G→C | Ranged attack success — self (modify info) |
| 56 | PACKET_GC_ATTACK_ARMS_OK_2 | G→C | Ranged attack success — target creature |
| 57 | PACKET_GC_ATTACK_ARMS_OK_3 | G→C | Ranged attack success — variant 3 |
| 58 | PACKET_GC_ATTACK_ARMS_OK_4 | G→C | Ranged attack success — variant 4 |
| 59 | PACKET_GC_ATTACK_ARMS_OK_5 | G→C | Ranged attack success — variant 5 |
| 60 | PACKET_GC_ATTACK_MELEE_OK_1 | G→C | Melee attack success — self (modify info) |
| 61 | PACKET_GC_ATTACK_MELEE_OK_2 | G→C | Melee attack success — target creature |
| 62 | PACKET_GC_ATTACK_MELEE_OK_3 | G→C | Melee attack success — variant 3 |
| 63 | PACKET_GC_ATTACK | G→C | Broadcast attack animation to nearby clients |
| 64 | PACKET_GC_CANNOT_ADD | G→C | Cannot add item (inventory full, etc.) |
| 65 | PACKET_GC_CANNOT_USE | G→C | Cannot use item/skill |
| 66 | PACKET_GC_CHANGE_SHAPE | G→C | Creature shape changed (transform/untransform) |
| 67 | PACKET_GC_CHANGE_DARK_LIGHT | G→C | Zone dark/light level changed |
| 68 | PACKET_GC_CHANGE_WEATHER | G→C | Zone weather changed |
| 69 | PACKET_GC_CREATURE_DIED | G→C | Creature death notification |
| 70 | PACKET_GC_DELETE_OBJECT | G→C | Remove object from viewport |
| 71 | PACKET_GC_DELETE_AND_PICKUP_OK | G→C | Item deleted from zone and picked up |
| 72 | PACKET_GC_DISCONNECT | G→C | Server-forced disconnect |
| 73 | PACKET_GC_GET_DAMAGE | G→C | Creature received damage |
| 74 | PACKET_GC_GET_OFF_MOTORCYCLE | G→C | Motorcycle dismount broadcast |
| 75 | PACKET_GC_GET_OFF_MOTORCYCLE_FAILED | G→C | Dismount attempt failed |
| 76 | PACKET_GC_GET_OFF_MOTORCYCLE_OK | G→C | Dismount self success |
| 77 | PACKET_GC_LEARN_SKILL_FAILED | G→C | Skill learning failed |
| 78 | PACKET_GC_LEARN_SKILL_OK | G→C | Skill learning succeeded |
| 79 | PACKET_GC_LEARN_SKILL_READY | G→C | Skill is ready to learn |
| 80 | PACKET_GC_LIGHTNING | G→C | Lightning environmental effect |
| 81 | PACKET_GC_MODIFY_INFORMATION | G→C | Update character stats/info (self) |
| 82 | PACKET_GC_MOVE | G→C | Broadcast creature movement |
| 83 | PACKET_GC_MOVE_ERROR | G→C | Movement validation failed |
| 84 | PACKET_GC_MOVE_OK | G→C | Self movement accepted |
| 85 | PACKET_GC_RECONNECT | G→C | Request client reconnect to new server |
| 86 | PACKET_GC_RIDE_MOTORCYCLE | G→C | Motorcycle mount broadcast |
| 87 | PACKET_GC_RIDE_MOTORCYCLE_FAILED | G→C | Motorcycle mount failed |
| 88 | PACKET_GC_RIDE_MOTORCYCLE_OK | G→C | Motorcycle mount self success |
| 89 | PACKET_GC_SAY | G→C | Broadcast chat message from creature |
| 90 | PACKET_GC_SET_POSITION | G→C | Teleport/warp creature to tile |
| 91 | PACKET_GC_SKILL_FAILED_1 | G→C | Skill execution failed (variant 1) |
| 92 | PACKET_GC_SKILL_FAILED_2 | G→C | Skill execution failed (variant 2) |
| 93 | PACKET_GC_SKILL_TO_INVENTORY_OK_1 | G→C | Inventory-targeted skill success (self) |
| 94 | PACKET_GC_SKILL_TO_INVENTORY_OK_2 | G→C | Inventory-targeted skill success (other) |
| 95 | PACKET_GC_SKILL_TO_OBJECT_OK_1 | G→C | Object-targeted skill success (self view) |
| 96 | PACKET_GC_SKILL_TO_OBJECT_OK_2 | G→C | Object-targeted skill success (target view) |
| 97 | PACKET_GC_SKILL_TO_OBJECT_OK_3 | G→C | Object-targeted skill success (variant 3) |
| 98 | PACKET_GC_SKILL_TO_OBJECT_OK_4 | G→C | Object-targeted skill success (variant 4) |
| 99 | PACKET_GC_SKILL_TO_OBJECT_OK_5 | G→C | Object-targeted skill success (variant 5) |
| 100 | PACKET_GC_SKILL_TO_SELF_OK_1 | G→C | Self-targeted skill success (variant 1) |
| 101 | PACKET_GC_SKILL_TO_SELF_OK_2 | G→C | Self-targeted skill success (variant 2) |
| 102 | PACKET_GC_SKILL_TO_TILE_OK_1 | G→C | Tile-targeted skill success (variant 1) |
| 103 | PACKET_GC_SKILL_TO_TILE_OK_2 | G→C | Tile-targeted skill success (variant 2) |
| 104 | PACKET_GC_SKILL_TO_TILE_OK_3 | G→C | Tile-targeted skill success (variant 3) |
| 105 | PACKET_GC_SKILL_TO_TILE_OK_4 | G→C | Tile-targeted skill success (variant 4) |
| 106 | PACKET_GC_SKILL_TO_TILE_OK_5 | G→C | Tile-targeted skill success (variant 5) |
| 107 | PACKET_GC_THROW_ITEM_OK_1 | G→C | Throw item success (variant 1) |
| 108 | PACKET_GC_THROW_ITEM_OK_2 | G→C | Throw item success (variant 2) |
| 109 | PACKET_GC_UPDATE_INFO | G→C | Full character info update packet |
| 110 | PACKET_GL_INCOMING_CONNECTION_ERROR | G→L | Error during game→login connection |
| 111 | PACKET_GL_INCOMING_CONNECTION_OK | G→L | Game→login connection successful |
| 112 | PACKET_LC_CREATE_PC_ERROR | L→C | Character creation failed |
| 113 | PACKET_LC_CREATE_PC_OK | L→C | Character creation successful |
| 114 | PACKET_LC_DELETE_PC_ERROR | L→C | Character deletion failed |
| 115 | PACKET_LC_DELETE_PC_OK | L→C | Character deletion successful |
| 116 | PACKET_LC_LOGIN_ERROR | L→C | Login failed (bad credentials, banned, etc.) |
| 117 | PACKET_LC_LOGIN_OK | L→C | Login successful |
| 118 | PACKET_LC_PC_LIST | L→C | Character select list |
| 119 | PACKET_LC_QUERY_RESULT_PLAYER_ID | L→C | Player ID lookup result |
| 120 | PACKET_LC_RECONNECT | L→C | Redirect client to reconnect |
| 121 | PACKET_LC_REGISTER_PLAYER_ERROR | L→C | Account registration failed |
| 122 | PACKET_LC_REGISTER_PLAYER_OK | L→C | Account registration successful |
| 123 | PACKET_LC_SELECT_PC_ERROR | L→C | Character select failed |
| 124 | PACKET_LG_INCOMING_CONNECTION | L→G | Login→game connection notification |
| 125 | PACKET_CG_BLOOD_DRAIN | C→G | Vampire blood drain attack |
| 126 | PACKET_GC_BLOOD_DRAIN_OK_1 | G→C | Blood drain success (self view) |
| 127 | PACKET_GC_BLOOD_DRAIN_OK_2 | G→C | Blood drain success (target view) |
| 128 | PACKET_GC_BLOOD_DRAIN_OK_3 | G→C | Blood drain success (variant 3) |
| 129 | PACKET_GC_ADD_GEAR_TO_INVENTORY | G→C | Move equipped item to inventory |
| 130 | PACKET_GC_ADD_GEAR_TO_ZONE | G→C | Drop equipped item to zone floor |

### 131–200: Items, Economy & Movement

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 131 | PACKET_UC_UPDATE_LIST | U→C | List of available update files |
| 132 | PACKET_UC_UPDATE | U→C | Update file data chunk |
| 133 | PACKET_GC_DROP_ITEM_TO_ZONE | G→C | Broadcast item dropped to zone |
| 134 | PACKET_GC_MORPH_1 | G→C | Creature morph visual (variant 1) |
| 135 | PACKET_GC_MORPH_SLAYER_2 | G→C | Slayer morph visual (variant 2) |
| 136 | PACKET_GC_MORPH_VAMPIRE_2 | G→C | Vampire morph visual (variant 2) |
| 137 | PACKET_GC_CREATE_ITEM | G→C | Item created and sent to client |
| 138 | PACKET_CG_NPC_ASK_ANSWER | C→G | Client answer to NPC menu option |
| 139 | PACKET_CG_SHOP_REQUEST_LIST | C→G | Request NPC shop item list |
| 140 | PACKET_CG_SHOP_REQUEST_BUY | C→G | Buy item from NPC shop |
| 141 | PACKET_GC_SHOP_VERSION | G→C | Shop version for cache validation |
| 142 | PACKET_GC_SHOP_LIST | G→C | NPC shop inventory listing |
| 143 | PACKET_GC_SHOP_BUY_OK | G→C | Shop purchase success |
| 144 | PACKET_GC_SHOP_BUY_FAIL | G→C | Shop purchase failed |
| 145 | PACKET_GC_SHOP_SOLD | G→C | Item sold to NPC confirmation |
| 146 | PACKET_GC_KNOCKS_TARGET_BACK_OK_1 | G→C | Knockback success (self view) |
| 147 | PACKET_GC_KNOCKS_TARGET_BACK_OK_2 | G→C | Knockback success (target view) |
| 148 | PACKET_GC_KNOCKS_TARGET_BACK_OK_4 | G→C | Knockback success (variant 4) |
| 149 | PACKET_GC_KNOCKS_TARGET_BACK_OK_5 | G→C | Knockback success (variant 5) |
| 150 | PACKET_CG_SHOP_REQUEST_SELL | C→G | Sell item to NPC shop |
| 151 | PACKET_GC_SHOP_SELL_FAIL | G→C | Shop sell failed |
| 152 | PACKET_GC_SHOP_SELL_OK | G→C | Shop sell success |
| 153 | PACKET_GC_SHOP_BOUGHT | G→C | Another player bought item from your store |
| 154 | PACKET_GC_REMOVE_EFFECT | G→C | Remove status effect from creature |
| 155 | PACKET_GC_ADD_VAMPIRE_FROM_BURROWING | G→C | Vampire emerges from underground |
| 156 | PACKET_GC_ADD_MONSTER_FROM_BURROWING | G→C | Monster emerges from underground |
| 157 | PACKET_GC_ADD_BURROWING_CREATURE | G→C | Creature begins burrowing |
| 158 | PACKET_CG_UNBURROW | C→G | Vampire rises from underground |
| 159 | PACKET_GC_UNBURROW_OK | G→C | Unburrow success |
| 160 | PACKET_GC_UNBURROW_FAIL | G→C | Unburrow failed |
| 161 | PACKET_GC_ADD_EFFECT | G→C | Add status effect to creature |
| 162 | PACKET_CG_USE_BONUS_POINT | C→G | Spend a bonus attribute point |
| 163 | PACKET_GC_USE_BONUS_POINT_FAIL | G→C | Bonus point use failed |
| 164 | PACKET_GC_USE_BONUS_POINT_OK | G→C | Bonus point use success |
| 165 | PACKET_GC_SHOP_LIST_MYSTERIOUS | G→C | Mysterious (special event) shop list |
| 166 | PACKET_GC_SHOP_MARKET_CONDITION | G→C | Market buy/sell condition update |
| 167 | PACKET_GC_TEACH_SKILL_INFO | G→C | Skill teachable info from NPC |
| 168 | PACKET_CG_DIAL_UP | C→G | Initiate inter-player phone call |
| 169 | PACKET_CG_PHONE_DISCONNECT | C→G | Hang up phone call |
| 170 | PACKET_CG_PHONE_SAY | C→G | Chat over phone connection |
| 171 | PACKET_CG_WHISPER | C→G | Send whisper to player by name |
| 172 | PACKET_GC_PHONE_CONNECTED | G→C | Phone call connected |
| 173 | PACKET_GC_RING | G→C | Incoming call ring notification |
| 174 | PACKET_GC_PHONE_DISCONNECTED | G→C | Phone call ended |
| 175 | PACKET_GC_PHONE_CONNECTION_FAILED | G→C | Phone call could not connect |
| 176 | PACKET_GC_PHONE_SAY | G→C | Phone chat message received |
| 177 | PACKET_GC_WHISPER | G→C | Whisper message received |
| 178 | PACKET_GC_WHISPER_FAILED | G→C | Whisper delivery failed |
| 179 | PACKET_CG_PICKUP_MONEY | C→G | Pick up money from zone floor |
| 180 | PACKET_CG_DROP_MONEY | C→G | Drop money to zone floor |
| 181 | PACKET_GC_SKILL_INFO | G→C | Detailed skill information |
| 182 | PACKET_GC_ADD_EFFECT_TO_TILE | G→C | Apply visual effect to zone tile |
| 183 | PACKET_GC_SEARCH_MOTORCYCLE_OK | G→C | Motorcycle search/locate success |
| 184 | PACKET_GC_SEARCH_MOTORCYCLE_FAIL | G→C | Motorcycle search failed |
| 185 | PACKET_GC_STATUS_CURRENT_HP | G→C | Current HP status update |
| 186 | PACKET_CL_VERSION_CHECK | C→L | Send client version string for validation |
| 187 | PACKET_LC_VERSION_CHECK_OK | L→C | Client version accepted |
| 188 | PACKET_LC_VERSION_CHECK_ERROR | L→C | Client version rejected |
| 189 | PACKET_GC_REAL_WEARING_INFO | G→C | Full equipped item info |
| 190 | PACKET_GC_REMOVE_FROM_GEAR | G→C | Item removed from gear slot |
| 191 | PACKET_CG_REQUEST_REPAIR | C→G | Request item repair from NPC |
| 192 | PACKET_GC_THROW_ITEM_OK_3 | G→C | Throw item success (variant 3) |
| 193 | PACKET_CG_SET_SLAYER_HOT_KEY | C→G | Set Slayer skill hotkey binding |
| 194 | PACKET_GC_SKILL_TO_SELF_OK_3 | G→C | Self-targeted skill success (variant 3) |
| 195 | PACKET_GC_SKILL_TO_TILE_OK_6 | G→C | Tile-targeted skill success (variant 6) |
| 196 | PACKET_GC_SKILL_TO_OBJECT_OK_6 | G→C | Object-targeted skill success (variant 6) |
| 197 | PACKET_GC_DELETE_EFFECT_FROM_TILE | G→C | Remove visual effect from tile |
| 198 | PACKET_CG_MOUSE_TO_STASH | C→G | Move mouse-held item to stash |
| 199 | PACKET_CG_STASH_TO_MOUSE | C→G | Move stash item to mouse cursor |
| 200 | PACKET_CG_STASH_LIST | C→G | Request stash contents |

### 201–285: Trade, Skills, Stash, Pets, Misc

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 201 | PACKET_GC_STASH_LIST | G→C | Stash item list |
| 202 | PACKET_CG_STASH_DEPOSIT | C→G | Deposit item to stash |
| 203 | PACKET_CG_STASH_WITHDRAW | C→G | Withdraw item from stash |
| 204 | PACKET_CG_STASH_REQUEST_BUY | C→G | Buy extra stash space |
| 205 | PACKET_GC_STASH_SELL | G→C | Stash space purchase confirmation |
| 206 | PACKET_GC_KNOCK_BACK | G→C | Creature knocked backward |
| 207 | PACKET_CG_TRADE_PREPARE | C→G | Initiate trade with player |
| 208 | PACKET_CG_TRADE_ADD_ITEM | C→G | Add item to trade window |
| 209 | PACKET_CG_TRADE_REMOVE_ITEM | C→G | Remove item from trade window |
| 210 | PACKET_CG_TRADE_MONEY | C→G | Set trade money amount |
| 211 | PACKET_CG_TRADE_FINISH | C→G | Confirm/complete trade |
| 212 | PACKET_GC_TRADE_PREPARE | G→C | Trade invitation received |
| 213 | PACKET_GC_TRADE_ADD_ITEM | G→C | Partner added item to trade window |
| 214 | PACKET_GC_TRADE_REMOVE_ITEM | G→C | Partner removed item from trade window |
| 215 | PACKET_GC_TRADE_MONEY | G→C | Partner set trade money amount |
| 216 | PACKET_GC_TRADE_FINISH | G→C | Trade completed successfully |
| 217 | PACKET_GC_TRADE_ERROR | G→C | Trade error / cancelled |
| 218 | PACKET_GC_TRADE_VERIFY | G→C | Trade verification check |
| 219 | PACKET_CG_SKILL_TO_OBJECT | C→G | Use skill targeting a specific object |
| 220 | PACKET_CG_SKILL_TO_SELF | C→G | Use skill targeting self |
| 221 | PACKET_CG_SKILL_TO_TILE | C→G | Use skill targeting a tile |
| 222 | PACKET_GC_ADD_WOLF | G→C | Add wolf (vampire transform) to viewport |
| 223 | PACKET_GC_ADD_BAT | G→C | Add bat (vampire transform) to viewport |
| 224 | PACKET_GC_ADD_MONSTER_FROM_TRANSFORMATION | G→C | Monster transformed into view |
| 225 | PACKET_GC_ADD_VAMPIRE_FROM_TRANSFORMATION | G→C | Vampire transformed into view |
| 226 | PACKET_GC_CROSS_COUNTER_OK_1 | G→C | Cross-counter skill success (variant 1) |
| 227 | PACKET_GC_CROSS_COUNTER_OK_2 | G→C | Cross-counter skill success (variant 2) |
| 228 | PACKET_GC_CROSS_COUNTER_OK_3 | G→C | Cross-counter skill success (variant 3) |
| 229 | PACKET_GC_FAST_MOVE | G→C | Teleport-style fast movement (skill-based) |
| 230 | PACKET_CG_UNTRANSFORM | C→G | Revert from transformation shape |
| 231 | PACKET_GC_UNTRANSFORM_OK | G→C | Untransform success |
| 232 | PACKET_GC_UNTRANSFORM_FAIL | G→C | Untransform failed |
| 233 | PACKET_CG_VISIBLE | C→G | Toggle visibility (stealth) |
| 234 | PACKET_GC_VISIBLE_OK | G→C | Visibility toggle success |
| 235 | PACKET_GC_VISIBLE_FAIL | G→C | Visibility toggle failed |
| 236 | PACKET_GC_MAKE_ITEM_OK | G→C | Item crafting success |
| 237 | PACKET_GC_MAKE_ITEM_FAIL | G→C | Item crafting failed |
| 238 | PACKET_GC_DELETE_INVENTORY_ITEM | G→C | Remove item from inventory |
| 239 | PACKET_GC_ADD_INSTALLED_MINE_TO_ZONE | G→C | Mine placed in zone |
| 240 | PACKET_CG_THROW_BOMB | C→G | Throw explosive/bomb |
| 241 | PACKET_GC_THROW_BOMB_OK_1 | G→C | Bomb throw success (variant 1) |
| 242 | PACKET_GC_THROW_BOMB_OK_2 | G→C | Bomb throw success (variant 2) |
| 243 | PACKET_GC_THROW_BOMB_OK_3 | G→C | Bomb throw success (variant 3) |
| 244 | PACKET_GC_MINE_EXPLOSION_OK_1 | G→C | Mine exploded (variant 1) |
| 245 | PACKET_GC_MINE_EXPLOSION_OK_2 | G→C | Mine exploded (variant 2) |
| 246 | PACKET_CG_MAKE_ITEM | C→G | Craft an item |
| 247 | PACKET_CL_GET_SERVER_LIST | C→L | Request game server list |
| 248 | PACKET_LC_SERVER_LIST | L→C | Game server list |
| 249 | PACKET_CL_CHANGE_SERVER | C→L | Request switch to different server |
| 250 | PACKET_CL_RECONNECT_LOGIN | C→L | Reconnect after disconnection |
| 251 | PACKET_GC_RECONNECT_LOGIN | G→C | Game server sends reconnect token |
| 252 | PACKET_GL_INCOMING_CONNECTION | G→L | Game notifies login of new connection |
| 253 | PACKET_LG_INCOMING_CONNECTION_OK | L→G | Login confirms connection |
| 254 | PACKET_LG_INCOMING_CONNECTION_ERROR | L→G | Login rejects connection |
| 255 | PACKET_GC_HP_RECOVERY_START_TO_SELF | G→C | HP regeneration started (self) |
| 256 | PACKET_GC_HP_RECOVERY_START_TO_OTHERS | G→C | HP regeneration started (broadcast) |
| 257 | PACKET_GC_HP_RECOVERY_END_TO_SELF | G→C | HP regeneration ended (self) |
| 258 | PACKET_GC_HP_RECOVERY_END_TO_OTHERS | G→C | HP regeneration ended (broadcast) |
| 259 | PACKET_GC_MP_RECOVERY_START | G→C | MP regeneration started |
| 260 | PACKET_GC_MP_RECOVERY_END | G→C | MP regeneration ended |
| 261 | PACKET_CG_SILVER_COATING | C→G | Apply silver coating to weapon |
| 262 | PACKET_GC_NPC_RESPONSE | G→C | NPC response to player action |
| 263 | PACKET_CG_SELECT_PORTAL | C→G | Enter a portal |
| 264 | PACKET_CG_REQUEST_NEWBIE_ITEM | C→G | Request starting items (new character) |
| 265 | PACKET_GC_REMOVE_CORPSE_HEAD | G→C | Remove corpse from zone |
| 266 | PACKET_GC_NPC_ASK_DYNAMIC | G→C | Dynamic (scripted) NPC dialogue |
| 267 | PACKET_GC_NPC_SAY_DYNAMIC | G→C | Dynamic NPC spoken text |
| 268 | PACKET_CG_SET_VAMPIRE_HOT_KEY | C→G | Set Vampire skill hotkey binding |
| 269 | PACKET_CG_USE_ITEM_FROM_INVENTORY | C→G | Use item from inventory |
| 270 | PACKET_CG_SELECT_WAYPOINT | C→G | Teleport to saved waypoint |
| 271 | PACKET_GC_ADD_HELICOPTER | G→C | Add helicopter object to viewport |
| 272 | PACKET_GC_ADD_VAMPIRE_PORTAL | G→C | Add vampire portal to zone |
| 273 | PACKET_CG_VERIFY_TIME | C→G | Anti-cheat time verification |
| 274 | PACKET_GC_ENTER_VAMPIRE_PORTAL | G→C | Enter vampire portal success |
| 275 | PACKET_CG_SELECT_TILE_EFFECT | C→G | Activate tile effect |
| 276 | PACKET_CG_PARTY_INVITE | C→G | Send/respond to party invitation |
| 277 | PACKET_CG_PARTY_LEAVE | C→G | Leave party |
| 278 | PACKET_GC_PARTY_INVITE | G→C | Party invitation received |
| 279 | PACKET_GC_PARTY_LEAVE | G→C | Party member left/expelled |
| 280 | PACKET_GC_PARTY_JOINED | G→C | Successfully joined party (member list) |
| 281 | PACKET_GC_PARTY_ERROR | G→C | Party action failed |
| 282 | PACKET_CG_RESURRECT | C→G | Request resurrection |
| 283 | PACKET_CG_REQUEST_IP | C→G | Request server IP |
| 284 | PACKET_GC_REQUESTED_IP | G→C | Server IP response |
| 285 | PACKET_CR_CONNECT | C→R | Connect to recorder server |

### 285–308: Recorder & World Selection

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 286 | PACKET_RC_CONNECT_VERIFY | R→C | Recorder connection verified |
| 287 | PACKET_CR_REQUEST | C→R | Request data from recorder |
| 288 | PACKET_RC_POSITION_INFO | R→C | Creature position info from recorder |
| 289 | PACKET_CR_DISCONNECT | C→R | Disconnect from recorder |
| 290 | PACKET_RC_SAY | R→C | Chat message from recorder |
| 291 | PACKET_RC_STATUS_HP | R→C | HP status from recorder |
| 292 | PACKET_CR_WHISPER | C→R | Whisper via recorder |
| 293 | PACKET_RC_REQUEST_VERIFY | R→C | Recorder request verification |
| 294 | PACKET_GC_REQUEST_FAILED | G→C | Generic request failure |
| 295 | PACKET_RC_REQUESTED_FILE | R→C | Requested file from recorder |
| 296 | PACKET_GC_ADD_INJURIOUS_CREATURE | G→C | Add hazardous creature to viewport |
| 297 | PACKET_GC_REMOVE_INJURIOUS_CREATURE | G→C | Remove hazardous creature from viewport |
| 298 | PACKET_GC_OTHER_MODIFY_INFO | G→C | Another player's stats modified |
| 299 | PACKET_GM_SERVER_INFO | internal | Server information broadcast |
| 300 | PACKET_CL_GET_WORLD_LIST | C→L | Request world/server group list |
| 301 | PACKET_LC_WORLD_LIST | L→C | World list response |
| 302 | PACKET_CL_SELECT_WORLD | C→L | Select a world |
| 303 | PACKET_CL_SELECT_SERVER | C→L | Select a game server |
| 304 | PACKET_CL_QUERY_CHARACTER_NAME | C→L | Query character name |
| 305 | PACKET_LC_QUERY_RESULT_CHARACTER_NAME | L→C | Character name query result |
| 306 | PACKET_RC_CHARACTER_INFO | R→C | Character info from recorder |
| 307 | PACKET_LG_KICK_CHARACTER | L→G | Login kicks character from game |
| 308 | PACKET_GL_KICK_VERIFY | G→L | Game confirms character kicked |

### 309–400: Guild & Quest System

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 309 | PACKET_GS_ADD_GUILD | G→S | Register new guild on shared server |
| 310 | PACKET_SG_ADD_GUILD_OK | S→G | Guild registration confirmed |
| 311 | PACKET_GC_SHOW_GUILD_REGIST | G→C | Show guild registration UI |
| 312 | PACKET_CG_REGIST_GUILD | C→G | Submit guild registration (name + intro) |
| 313 | PACKET_GC_WAIT_GUILD_LIST | G→C | Pending guild application list |
| 314 | PACKET_GC_SHOW_GUILD_INFO | G→C | Display guild information |
| 315 | PACKET_CG_SELECT_GUILD | C→G | Select a guild from list |
| 316 | PACKET_CG_TRY_JOIN_GUILD | C→G | Apply to join a guild |
| 317 | PACKET_GC_SHOW_GUILD_JOIN | G→C | Show guild join confirmation |
| 318 | PACKET_CG_JOIN_GUILD | C→G | Confirm guild join |
| 319 | PACKET_GS_ADD_GUILD_MEMBER | G→S | Add member to guild on shared server |
| 320 | PACKET_SG_ADD_GUILD_MEMBER_OK | S→G | Guild member addition confirmed |
| 321 | PACKET_GC_SHOW_MESSAGE_BOX | G→C | Show modal message box |
| 322 | PACKET_GC_MODIFY_MONEY | G→C | Player money balance updated |
| 323 | PACKET_GC_SHOW_WAIT_GUILD_INFO | G→C | Show waiting guild info |
| 324 | PACKET_GC_ACTIVE_GUILD_LIST | G→C | Active guild listing |
| 325 | PACKET_CG_QUIT_GUILD | C→G | Leave guild |
| 326 | PACKET_GS_QUIT_GUILD | G→S | Notify shared server of guild quit |
| 327 | PACKET_SG_QUIT_GUILD_OK | S→G | Guild quit confirmed |
| 328 | PACKET_CG_REQUEST_GUILD_MEMBER_LIST | C→G | Request guild member list |
| 329 | PACKET_GC_GUILD_MEMBER_LIST | G→C | Guild member list |
| 330 | PACKET_CG_SELECT_GUILD_MEMBER | C→G | Select a guild member for info |
| 331 | PACKET_GC_SHOW_GUILD_MEMBER_INFO | G→C | Show guild member details |
| 332 | PACKET_CG_EXPEL_GUILD_MEMBER | C→G | Expel member from guild (master only) |
| 333 | PACKET_GS_EXPEL_GUILD_MEMBER | G→S | Notify shared server of expulsion |
| 334 | PACKET_SG_EXPEL_GUILD_MEMBER_OK | S→G | Expulsion confirmed |
| 335 | PACKET_CG_MODIFY_GUILD_MEMBER | C→G | Modify guild member rank/intro |
| 336 | PACKET_GS_MODIFY_GUILD_MEMBER | G→S | Propagate member modification |
| 337 | PACKET_SG_MODIFY_GUILD_MEMBER_OK | S→G | Member modification confirmed |
| 338 | PACKET_SG_DELETE_GUILD_OK | S→G | Guild deleted confirmation |
| 339 | PACKET_SG_MODIFY_GUILD_OK | S→G | Guild info modification confirmed |
| 340 | PACKET_GC_MODIFY_GUILD_MEMBER_INFO | G→C | Guild member info updated |
| 341 | PACKET_GG_COMMAND | G→G | Cross-server command |
| 342 | PACKET_CG_RELIC_TO_OBJECT | C→G | Apply relic to object |
| 343 | PACKET_LC_PORT_CHECK | L→C | Port connectivity check |
| 344 | PACKET_CG_PORT_CHECK | C→G | Port check response |
| 345 | PACKET_CG_GUILD_CHAT | C→G | Guild chat message |
| 346 | PACKET_GC_GUILD_CHAT | G→C | Guild chat broadcast |
| 347 | PACKET_GG_GUILD_CHAT | G→G | Cross-server guild chat relay |
| 348 | PACKET_CG_COMMAND_MONSTER | C→G | Issue command to pet/summoned monster |
| 349 | PACKET_CG_ADD_ITEM_TO_ITEM | C→G | Combine item into another item |
| 350 | PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY | G→C | Item combination verification |
| 351 | PACKET_GS_REQUEST_GUILD_INFO | G→S | Request guild info from shared server |
| 352 | PACKET_SG_GUILD_INFO | S→G | Guild info from shared server |
| 353 | PACKET_CG_REQUEST_INFO | C→G | Request own character info |
| 354 | PACKET_GC_NOTICE_EVENT | G→C | Server event notice |
| 355 | PACKET_GC_FAKE_MOVE | G→C | Visual-only (fake) movement animation |
| 356 | PACKET_CG_MODIFY_GUILD_INTRO | C→G | Edit guild introduction text |
| 357 | PACKET_GS_MODIFY_GUILD_INTRO | G→S | Propagate guild intro modification |
| 358 | PACKET_SG_MODIFY_GUILD_INTRO_OK | S→G | Guild intro modification confirmed |
| 359 | PACKET_CG_MODIFY_GUILDMEMBER_INTRO | C→G | Edit own guild member introduction |
| 360 | PACKET_CG_SKILL_TO_NAMED | C→G | Use skill targeting named player |
| 361 | PACKET_GS_GUILDMEMBER_LOGON | G→S | Guild member logged on |
| 362 | PACKET_SG_GUILDMEMBER_LOGON_OK | S→G | Guild logon propagation confirmed |
| 363 | PACKET_CG_SELECT_RANK_BONUS | C→G | Select rank bonus reward |
| 364 | PACKET_GC_SELECT_RANK_BONUS_OK | G→C | Rank bonus selection success |
| 365 | PACKET_GC_SELECT_RANK_BONUS_FAILED | G→C | Rank bonus selection failed |
| 366 | PACKET_GC_RANK_BONUS_INFO | G→C | Rank bonus information |
| 367 | PACKET_COMMON_BILLING | internal | Billing/subscription validation |
| 368 | PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY | C→G | Use message/greeting item from inventory |
| 369 | PACKET_CG_WITHDRAW_TAX | C→G | Withdraw tax money from guild vault |
| 370 | PACKET_GC_NPC_INFO | G→C | NPC detailed info |
| 371 | PACKET_GC_NPC_ASK_VARIABLE | G→C | Variable/dynamic NPC question |
| 372 | PACKET_GC_WAR_SCHEDULE_LIST | G→C | War schedule listing |
| 373 | PACKET_GC_WAR_LIST | G→C | Active war list |
| 374 | PACKET_GC_HOLY_LAND_BONUS_INFO | G→C | Holy land control bonus info |
| 375 | PACKET_GC_BLOOD_BIBLE_STATUS | G→C | Blood bible status update |
| 376 | PACKET_CG_TYPE_STRING_LIST | C→G | Send string list to server |
| 377 | PACKET_CG_USE_ITEM_FROM_GEAR | C→G | Use item currently equipped in gear slot |
| 378 | PACKET_GC_KICK_MESSAGE | G→C | Kick/ban message to client |
| 379 | PACKET_GC_TIME_LIMIT_ITEM_INFO | G→C | Time-limited item expiry info |
| 380 | PACKET_GC_SELECT_QUEST_ID | G→C | Send available quest IDs |
| 381 | PACKET_CG_SELECT_QUEST | C→G | Accept a quest |
| 382 | PACKET_GC_QUEST_STATUS | G→C | Quest progress status |
| 383 | PACKET_GC_MONSTER_KILL_QUEST_INFO | G→C | Monster kill quest tracking info |
| 384 | PACKET_CG_LOTTERY_SELECT | C→G | Participate in lottery |
| 385 | PACKET_GC_NOTIFY_WIN | G→C | Lottery win notification |
| 386 | PACKET_GC_GOODS_LIST | G→C | Reward goods list |
| 387 | PACKET_CG_TAKE_OUT_GOOD | C→G | Claim a reward item |
| 388 | PACKET_GC_TAKE_OUT_OK | G→C | Reward claim success |
| 389 | PACKET_GC_TAKE_OUT_FAIL | G→C | Reward claim failed |
| 390 | PACKET_GC_ADD_OUSTERS | G→C | Add Ousters (PC) to viewport |
| 391 | PACKET_CG_MIX_ITEM | C→G | Mix/blend items together |
| 392 | PACKET_GC_ADD_OUSTERS_CORPSE | G→C | Add Ousters corpse to zone |
| 393 | PACKET_CG_ABSORB_SOUL | C→G | Absorb a soul/essence |
| 394 | PACKET_CG_DOWN_SKILL | C→G | Downgrade a skill level |
| 395 | PACKET_GC_DOWN_SKILL_OK | G→C | Skill downgrade success |
| 396 | PACKET_GC_DOWN_SKILL_FAILED | G→C | Skill downgrade failed |
| 397 | PACKET_GC_MINI_GAME_SCORES | G→C | Mini-game score board |
| 398 | PACKET_CG_SUBMIT_SCORE | C→G | Submit mini-game score |
| 399 | PACKET_CG_FAIL_QUEST | C→G | Abandon/fail a quest |
| 400 | PACKET_CG_ADD_ITEM_TO_CODE_SHEET | C→G | Register item serial code |

### 401–489: Premium, Pets, SMS, Player Store, Power Points

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 401 | PACKET_GC_FLAG_WAR_STATUS | G→C | Flag war zone status update |
| 402 | PACKET_GC_OTHER_GUILD_NAME | G→C | Another player's guild name |
| 403 | PACKET_GC_SYSTEM_AVAILABILITIES | G→C | Server feature availability flags |
| 404 | PACKET_GTO_ACKNOWLEDGEMENT | G→C | Generic acknowledgement |
| 405 | PACKET_GC_SWEEPER_BONUS_INFO | G→C | Zone sweeper bonus information |
| 406 | PACKET_CG_SELECT_REGEN_ZONE | C→G | Select resurrection zone |
| 407 | PACKET_GC_REGEN_ZONE_STATUS | G→C | Resurrection zone status |
| 408 | PACKET_GC_PET_INFO | G→C | Pet information packet |
| 409 | PACKET_CG_TAME_MONSTER | C→G | Attempt to tame a monster |
| 410 | PACKET_CG_PET_GAMBLE | C→G | Pet gambling action |
| 411 | PACKET_CG_CRASH_REPORT | C→G | Client crash/error report |
| 412 | PACKET_GC_PET_USE_SKILL | G→C | Pet used a skill |
| 413 | PACKET_CG_PARTY_POSITION | C→G | Update party position sharing |
| 414 | PACKET_GC_PARTY_POSITION | G→C | Party member position update |
| 415 | PACKET_CG_PARTY_SAY | C→G | Party chat message |
| 416 | PACKET_GC_PARTY_SAY | G→C | Party chat broadcast |
| 417 | PACKET_GG_SERVER_CHAT | G→G | Cross-server chat relay |
| 418 | PACKET_GC_PET_STASH_LIST | G→C | Pet stash listing |
| 419 | PACKET_CG_WITHDRAW_PET | C→G | Withdraw pet from stash |
| 420 | PACKET_CG_DEPOSIT_PET | C→G | Deposit pet to stash |
| 421 | PACKET_GC_PET_STASH_VERIFY | G→C | Pet stash operation verified |
| 422 | PACKET_CG_SMS_ADDRESS_LIST | C→G | Request SMS address book |
| 423 | PACKET_GC_SMS_ADDRESS_LIST | G→C | SMS address book response |
| 424 | PACKET_CG_ADD_SMS_ADDRESS | C→G | Add SMS address entry |
| 425 | PACKET_CG_DELETE_SMS_ADDRESS | C→G | Delete SMS address entry |
| 426 | PACKET_GC_ADDRESS_LIST_VERIFY | G→C | SMS address operation confirmed |
| 427 | PACKET_CG_SMS_SEND | C→G | Send SMS message |
| 428 | PACKET_GC_NICKNAME_LIST | G→C | Character nickname list |
| 429 | PACKET_GC_ADD_NICKNAME | G→C | Nickname added |
| 430 | PACKET_CG_MODIFY_NICKNAME | C→G | Modify nickname |
| 431 | PACKET_CG_SELECT_NICKNAME | C→G | Select active nickname |
| 432 | PACKET_GC_NICKNAME_VERIFY | G→C | Nickname operation confirmed |
| 433 | PACKET_GC_MODIFY_NICKNAME | G→C | Broadcast nickname modification |
| 434 | PACKET_GC_GQUEST_STATUS_INFO | G→C | General quest status information |
| 435 | PACKET_GC_GQUEST_STATUS_MODIFY | G→C | General quest status changed |
| 436 | PACKET_CG_GQUEST_ACCEPT | C→G | Accept/complete general quest |
| 437 | PACKET_CG_GQUEST_CANCEL | C→G | Cancel general quest |
| 438 | PACKET_GC_EXECUTE_ELEMENT | G→C | Execute script/message element |
| 439 | PACKET_GC_GQUEST_INVENTORY | G→C | General quest inventory listing |
| 440 | PACKET_CU_REQUEST_LOGIN_MODE | C→U | Request login mode from update server |
| 441 | PACKET_UC_REQUEST_LOGIN_MODE | U→C | Login mode response |
| 442 | PACKET_GC_AUTH_KEY | G→C | nProtect CSAuth key (server→client) |
| 443 | PACKET_CG_AUTH_KEY | C→G | nProtect CSAuth key (client→server) |
| 444 | PACKET_CG_USE_ITEM_FROM_GQUEST_INVENTORY | C→G | Use item from general quest inventory |
| 445 | PACKET_GC_GUILD_RESPONSE | G→C | Guild action response |
| 446 | PACKET_CG_REQUEST_GUILD_LIST | C→G | Request guild list (with filter) |
| 447 | PACKET_CG_APPOINT_SUBMASTER | C→G | Appoint sub-master of guild |
| 448 | PACKET_CG_REQUEST_UNION | C→G | Request guild union formation |
| 449 | PACKET_CG_ACCEPT_UNION | C→G | Accept union request |
| 450 | PACKET_CG_DENY_UNION | C→G | Deny union request |
| 451 | PACKET_CG_REQUEST_UNION_INFO | C→G | Request union information |
| 452 | PACKET_CG_EXPEL_GUILD | C→G | Expel guild from union |
| 453 | PACKET_CG_QUIT_UNION | C→G | Withdraw guild from union |
| 454 | PACKET_CG_QUIT_UNION_ACCEPT | C→G | Accept union withdrawal request |
| 455 | PACKET_CG_QUIT_UNION_DENY | C→G | Deny union withdrawal request |
| 456 | PACKET_GC_SHOW_UNION_INFO | G→C | Display union information |
| 457 | PACKET_GC_UNION_OFFER_LIST | G→C | Union offer/join/quit request list |
| 458 | PACKET_GS_GUILD_ACTION | G→S | Guild action on shared server |
| 459 | PACKET_SG_GUILD_RESPONSE | S→G | Guild action response from shared server |
| 460 | PACKET_GC_BLOOD_BIBLE_LIST | G→C | Blood bible listing |
| 461 | PACKET_CG_SELECT_BLOOD_BIBLE | C→G | Select a blood bible |
| 462 | PACKET_GC_BLOOD_BIBLE_SIGN_INFO | G→C | Blood bible signature information |
| 463 | PACKET_CG_RANGER_SAY | C→G | Ranger-area broadcast chat |
| 464 | PACKET_CG_MODIFY_TAX_RATIO | C→G | Modify guild tax rate |
| 465 | PACKET_CG_DISPLAY_ITEM | C→G | Display item in player store |
| 466 | PACKET_CG_UNDISPLAY_ITEM | C→G | Remove item from player store |
| 467 | PACKET_CG_STORE_SIGN | C→G | Set player store sign text |
| 468 | PACKET_CG_STORE_OPEN | C→G | Open player store |
| 469 | PACKET_CG_STORE_CLOSE | C→G | Close player store |
| 470 | PACKET_CG_REQUEST_STORE_INFO | C→G | Request player store information |
| 471 | PACKET_GC_MY_STORE_INFO | G→C | Own player store information |
| 472 | PACKET_GC_OTHER_STORE_INFO | G→C | Another player's store information |
| 473 | PACKET_CG_BUY_STORE_ITEM | C→G | Buy item from player store |
| 474 | PACKET_GC_REMOVE_STORE_ITEM | G→C | Item removed from player store |
| 475 | PACKET_GC_ADD_STORE_ITEM | G→C | Item added to player store |
| 476 | PACKET_CG_REQUEST_POWER_POINT | C→G | Request power point balance |
| 477 | PACKET_GC_REQUEST_POWER_POINT_RESULT | G→C | Power point balance response |
| 478 | PACKET_CG_USE_POWER_POINT | C→G | Spend power points |
| 479 | PACKET_GC_USE_POWER_POINT_RESULT | G→C | Power point spend result |
| 480 | PACKET_CG_DONATION_MONEY | C→G | Donate money in event |
| 481 | PACKET_CG_GET_EVENT_ITEM | C→G | Claim event reward item |
| 482 | PACKET_GC_SUB_INVENTORY_INFO | G→C | Sub-inventory items info |
| 483 | PACKET_CL_AGREEMENT | C→L | Accept terms of service agreement |
| 484 | PACKET_LC_SHOW_WEB_PAGE | L→C | Open external web page |
| 485 | PACKET_CG_REQUEST_WEB_MARKET | C→G | Request web market access |
| 486 | PACKET_GC_SHOW_WEB_MARKET | G→C | Open web market UI |
| 487 | PACKET_CG_CHANGE_GEARSLOT | C→G | Swap gear slot set (`__GEAR_SWAP_CHANGE`) |
| 488 | PACKET_GC_CHANGE_GEARSLOT | G→C | Gear slot swap broadcast |
| 489 | PACKET_GC_ADD_SYLPH | G→C | Add Sylph (Ousters transport) to viewport |

### 490–535: Instance Dungeons & Friends (Feature-Gated)

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 490 | PACKET_CG_INSTANCEDOUNGEON_ENTER | C→G | Enter instance dungeon (`__TIPOJYU_CASTLE`) |
| 491 | PACKET_GC_INSTANCEDOUNGEON_LOBBY | G→C | Instance dungeon lobby info |
| 492 | PACKET_GC_INSTANCEDOUNGEON_RESULT | G→C | Instance dungeon result |
| 493 | PACKET_GC_ADD_EFFECT_TO_SCREEN | G→C | Full-screen visual effect |
| 494 | PACKET_LC_SELECT_WORLD_ERROR | L→C | World selection failed (`__LC_SELECT_WORLD_ERROR`) |
| 495 | PACKET_GC_UPDATE_WEEKITEM_LIST | G→C | Weekly premium item list (`__PREMIUM_GIVE_ITEM_UI`) |
| 496 | PACKET_CG_SELECT_WEEKITEM | C→G | Select weekly item |
| 497 | PACKET_CG_SELECT_ALL_WEEKITEM | C→G | Select all weekly items |
| 498 | PACKET_CG_REQUEST_REPAIR_INFO | C→G | Request repair cost info (`__REPAIRSYSTEM_RENEWAL`) |
| 499 | PACKET_GC_REPAIR_INFO | G→C | Repair cost information |
| 500 | PACKET_CG_FRIEND_REQ_TO_ADD | C→G | Request to add friend (`__FRIEND_ADDITION`) |
| 501 | PACKET_GC_FRIEND_REQ_TO_ADD | G→C | Friend request received |
| 502 | PACKET_GC_FRIEND_SUGGEST_TO_ADD | G→C | Friend suggestion received |
| 503 | PACKET_CG_FRIEND_RES_TO_ADD | C→G | Respond to friend request |
| 504 | PACKET_GC_FRIEND_RES_TO_ADD | G→C | Friend request response |
| 505 | PACKET_CG_FRIEND_REQ_TO_DEL | C→G | Remove a friend |
| 506 | PACKET_GC_FRIEND_REQ_TO_DEL | G→C | Friend removal notification |
| 507 | PACKET_CG_FRIEND_VIEW_INFO | C→G | View friend's info |
| 508 | PACKET_GC_FRIEND_VIEW_INFO | G→C | Friend info response |
| 509 | PACKET_CG_FRIEND_UPDATE_GLOBAL_OPTION | C→G | Update global friend options |
| 510 | PACKET_CG_FRIEND_UPDATE_INDIVIDUAL_OPTION | C→G | Update per-friend options |
| 511 | PACKET_GC_FRIEND_LIST | G→C | Full friend list |
| 512 | PACKET_GC_FRIEND_WAIT_LIST | G→C | Pending friend request list |
| 513 | PACKET_GC_FRIEND_ADD | G→C | Friend successfully added |
| 514 | PACKET_GC_FRIEND_DEL | G→C | Friend successfully removed |
| 515 | PACKET_GC_FRIEND_UPDATE_CONNECT | G→C | Friend online/offline status change |
| 516 | PACKET_GC_FRIEND_UPDATE_ZONE | G→C | Friend zone change |
| 517 | PACKET_GS_LOGIN | G→S | Friend system: player logged in |
| 518 | PACKET_GS_LOGOUT | G→S | Friend system: player logged out |
| 519 | PACKET_GS_FRIEND_REQ_TO_ADD | G→S | Forward friend add request to shared server |
| 520 | PACKET_SG_FRIEND_REQ_TO_ADD | S→G | Friend add request from shared server |
| 521 | PACKET_SG_FRIEND_SUGGEST_TO_ADD | S→G | Friend suggestion from shared server |
| 522 | PACKET_GS_FRIEND_RES_TO_ADD | G→S | Forward friend add response |
| 523 | PACKET_SG_FRIEND_RES_TO_ADD | S→G | Friend add response from shared server |
| 524 | PACKET_GS_FRIEND_REQ_TO_DEL | G→S | Forward friend delete request |
| 525 | PACKET_GS_FRIEND_VIEW_INFO | G→S | Forward friend view info request |
| 526 | PACKET_SG_FRIEND_VIEW_INFO | S→G | Friend view info response |
| 527 | PACKET_GS_FRIEND_UPDATE_GLOBAL_OPTION | G→S | Forward global option update |
| 528 | PACKET_GS_FRIEND_UPDATE_INDIVIDUAL_OPTION | G→S | Forward individual option update |
| 529 | PACKET_SG_FRIEND_LIST | S→G | Full friend list from shared server |
| 530 | PACKET_SG_FRIEND_WAIT_LIST | S→G | Wait list from shared server |
| 531 | PACKET_SG_FRIEND_ADD | S→G | Friend added on shared server |
| 532 | PACKET_SG_FRIEND_DEL | S→G | Friend removed on shared server |
| 533 | PACKET_SG_FRIEND_UPDATE_CONNECT | S→G | Friend connect update |
| 534 | PACKET_GS_FRIEND_UPDATE_ZONE | G→S | Forward zone update |
| 535 | PACKET_SG_FRIEND_UPDATE_ZONE | S→G | Zone update from shared server |

### 600–601: Anti-Cheat

| ID | Enum Name | Direction | Description |
|----|-----------|-----------|-------------|
| 600 | PACKET_GC_AUTH_XTRAP | G→C | XTrap anti-cheat key (server→client) |
| 601 | PACKET_CG_AUTH_XTRAP | C→G | XTrap anti-cheat key (client→server) |

---

## 6. Packet Field Reference

Type sizes used throughout this section:

- `ObjectID_t` = 4 bytes (DWORD)
- `Coord_t` = 1 byte (BYTE)
- `Dir_t` = 1 byte (BYTE)
- `SkillType_t` = 2 bytes (WORD)
- `HP_t` / `Damage_t` = 2 bytes (WORD)
- `BYTE` = 1 byte, `WORD` = 2 bytes, `DWORD` = 4 bytes
- `bool` = 1 byte (szbool)
- Variable-length string = 1 byte length prefix + N bytes content

---

### Connection & Authentication

#### CGConnect (ID 10)
Direction: Client → Game Server
Trigger: Sent immediately after TCP connection to game server is established.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| Key | DWORD | 4 | Authentication key issued by login server |
| PCType | BYTE | 1 | Character race (0=Slayer, 1=Vampire, 2=Ousters) |
| NameLen | BYTE | 1 | Character name length |
| Name | char[] | N | Character name (no null terminator) |
| MacAddress | BYTE[6] | 6 | Client network adapter MAC address |

Wire size: 12 + len(Name) bytes (variable)

---

#### CLLogin (ID 27)
Direction: Client → Login Server
Trigger: Player submits login credentials.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| IDLen | BYTE | 1 | Account ID length |
| ID | char[] | N | Account ID string |
| PasswordLen | BYTE | 1 | Password length |
| Password | char[] | M | Password string (transmitted encrypted) |
| MacAddress | BYTE[6] | 6 | Client MAC address |
| LoginMode | BYTE | 1 | Login mode flag |

Wire size: 9 + len(ID) + len(Password) bytes (variable)

---

#### LCLoginOK (ID 117)
Direction: Login Server → Client
Trigger: Credentials validated; response to CLLogin.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| isAdult | bool | 1 | Whether account is age-verified adult |
| isUnderFifthteen | bool | 1 | Whether account is under 15 |
| isFamily | bool | 1 | Whether account is family-type |
| Stat | BYTE | 1 | Account status byte |
| LastDays | WORD | 2 | Days remaining on subscription (or similar) |
| PayType | BYTE | 1 | Payment type (`__PAYZONE_PASS_TICKET` only) |
| ReservedValue | BYTE | 1 | Reserved for future use (`__LOGIN_PACKET` only) |

Wire size: 5–7 bytes depending on compile flags.

---

#### LCPCList (ID 118)
Direction: Login Server → Client
Trigger: Response to CLGetPCList; sent after login to show character select screen.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| SlotCount | BYTE | 1 | Number of character slots |
| PCInfo[0..2] | PCSlayerInfo/PCVampireInfo/PCOustersInfo | variable | Per-slot character serialisation; each slot prefixed with BYTE type flag |
| Agree | BYTE | 1 | Terms of service agreement flag |

Wire size: variable (up to `PCSlayerInfo::getMaxSize() * 3 + 4` bytes)

---

### Movement

#### CGMove (ID 14)
Direction: Client → Game Server
Trigger: Player presses a movement key; sent each tile step.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| X | Coord_t (BYTE) | 1 | Target tile X coordinate |
| Y | Coord_t (BYTE) | 1 | Target tile Y coordinate |
| Dir | Dir_t (BYTE) | 1 | Facing direction (0=LEFT … 7=LEFTUP) |

Wire size: 3 bytes (fixed)

---

#### GCMove (ID 82)
Direction: Game Server → Client
Trigger: Broadcast to nearby clients when any creature moves.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Moving creature's object ID |
| X | Coord_t (BYTE) | 1 | New tile X coordinate |
| Y | Coord_t (BYTE) | 1 | New tile Y coordinate |
| Dir | Dir_t (BYTE) | 1 | New facing direction |

Wire size: 7 bytes (fixed)

---

#### GCFastMove (ID 229)
Direction: Game Server → Client
Trigger: Skill-based teleport or rapid movement (e.g. Rush, Charge).

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Moving creature's object ID |
| FromX | Coord_t (BYTE) | 1 | Origin tile X |
| FromY | Coord_t (BYTE) | 1 | Origin tile Y |
| ToX | Coord_t (BYTE) | 1 | Destination tile X |
| ToY | Coord_t (BYTE) | 1 | Destination tile Y |
| SkillType | SkillType_t (WORD) | 2 | Skill that caused the movement |

Wire size: 10 bytes (fixed)

---

### Combat

#### CGAttack (ID 0)
Direction: Client → Game Server
Trigger: Player clicks/targets a creature for basic melee or ranged attack.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Target creature object ID |
| X | Coord_t (BYTE) | 1 | Attacker tile X |
| Y | Coord_t (BYTE) | 1 | Attacker tile Y |
| Dir | Dir_t (BYTE) | 1 | Attack direction |
| ActionStep | BYTE | 1 | Multi-step attack phase index |

Wire size: 8 bytes (fixed)

---

#### GCAttack (ID 63)
Direction: Game Server → Client
Trigger: Broadcast to nearby clients — a creature initiated an attack.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Attacking creature's object ID |
| X | Coord_t (BYTE) | 1 | Attacker tile X |
| Y | Coord_t (BYTE) | 1 | Attacker tile Y |
| Dir | Dir_t (BYTE) | 1 | Attack direction |

Wire size: 7 bytes (fixed)

---

#### GCGetDamage (ID 73)
Direction: Game Server → Client
Trigger: A creature received damage; broadcasts to nearby players.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Damaged creature's object ID |
| Damage | WORD | 2 | Damage amount dealt |

Wire size: 6 bytes (fixed)

---

#### GCCreatureDied (ID 69)
Direction: Game Server → Client
Trigger: A creature in the viewport has died.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Dead creature's object ID |

Wire size: 4 bytes (fixed)

---

#### GCAttackArmsOK1 (ID 55)
Direction: Game Server → Client
Trigger: Sent to the attacker; confirms ranged attack result including ammo and stat changes.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Target creature's object ID |
| BulletNum | Bullet_t (BYTE) | 1 | Remaining bullets after attack |
| bSuccess | bool | 1 | Whether the attack hit |
| ModifyInfo | (variable) | variable | Stat delta fields (from ModifyInfo base) |
| SkillType | SkillType_t (WORD) | 2 | Skill type used |

Wire size: variable (8 + ModifyInfo payload)

---

### Skills

#### CGCastingSkill (ID 37)
Direction: Client → Game Server
Trigger: Player begins channelling a skill (casting animation start).

| Field | Type | Size | Description |
|-------|------|------|-------------|
| SkillType | SkillType_t (WORD) | 2 | Skill being cast |

Wire size: 2 bytes (fixed)

---

#### CGSkillToObject (ID 219)
Direction: Client → Game Server
Trigger: Player activates a skill that targets a specific creature or object.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| SkillType | SkillType_t (WORD) | 2 | Skill being used |
| CEffectID | CEffectID_t (WORD) | 2 | Client-side effect ID for visual sync |
| TargetObjectID | ObjectID_t (DWORD) | 4 | Target object ID |
| ActionStep | BYTE | 1 | Multi-step skill phase index |

Wire size: 9 bytes (fixed)

---

#### GCAddEffect (ID 161)
Direction: Game Server → Client
Trigger: A status effect (buff or debuff) has been applied to a creature.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) — embedded as BYTE prefix | 1 | Note: size field says szBYTE for object |
| EffectID | EffectID_t (WORD) | 2 | Effect type identifier |
| Duration | Turn_t (DWORD) | 4 | Duration in 0.1-second turns |

Wire size: 7 bytes (fixed). Note: The `getPacketSize` formula is `szBYTE + szEffectID + szTurn`; the ObjectID is encoded as a BYTE-prefixed value in this packet.

---

### Inventory

#### CGAddMouseToInventory (ID 4)
Direction: Client → Game Server
Trigger: Player drops mouse-held item into a specific inventory slot.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Object ID of the item on mouse cursor |
| InventoryItemObjectID | ObjectID_t (DWORD) | 4 | Object ID of existing item in target slot (0 if empty) |
| InvenX | CoordInven_t (BYTE) | 1 | Target inventory column |
| InvenY | CoordInven_t (BYTE) | 1 | Target inventory row |

Wire size: 10 bytes (fixed)

---

#### GCAddGearToInventory (ID 129)
Direction: Game Server → Client
Trigger: A gear-slot item was moved into the inventory (e.g., after ShieldStrike skill).

| Field | Type | Size | Description |
|-------|------|------|-------------|
| SlotID | SlotID_t (BYTE) | 1 | Source gear slot identifier |
| InvenX | CoordInven_t (BYTE) | 1 | Destination inventory column |
| InvenY | CoordInven_t (BYTE) | 1 | Destination inventory row |

Wire size: 3 bytes (fixed)

---

#### GCDeleteInventoryItem (ID 238)
Direction: Game Server → Client
Trigger: An item has been removed from the player's inventory (consumed, traded, dropped).

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Object ID of deleted item |

Wire size: 4 bytes (fixed)

---

### Shop

#### CGShopRequestBuy (ID 140)
Direction: Client → Game Server
Trigger: Player clicks "Buy" on an NPC shop item.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | NPC object ID |
| RackType | ShopRackType_t (BYTE) | 1 | Shop rack type (0=Normal, 1=Special, 2=Mysterious) |
| RackIndex | BYTE | 1 | Item rack/slot index |
| ItemNum | ItemNum_t | variable | Quantity to purchase |
| X | Coord_t (BYTE) | 1 | Player inventory destination X |
| Y | Coord_t (BYTE) | 1 | Player inventory destination Y |

Wire size: `szObjectID + szShopRackType + szBYTE + szItemNum + szCoord*2` bytes

---

#### GCShopList (ID 142)
Direction: Game Server → Client
Trigger: Response to CGShopRequestList; client receives NPC shop contents.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | NPC object ID |
| Version | ShopVersion_t (long) | 4 | Shop version for client cache |
| RackType | ShopRackType_t (BYTE) | 1 | Rack type |
| ItemCount | BYTE | 1 | Number of items in rack (up to 20) |
| Items[] | SHOPLISTITEM[20] | variable | Per-item: exist flag, objectID, itemClass, itemType, optionType list, durability, silver, grade, enchantLevel |
| MarketCondBuy | MarketCond_t (short) | 2 | Buy price modifier |
| MarketCondSell | MarketCond_t (short) | 2 | Sell price modifier |
| ShopType | BYTE | 1 | NPC shop type (normal or event) |

Wire size: variable (up to ~700+ bytes for full rack)

---

### NPC & Chat

#### CGNPCTalk (ID 40)
Direction: Client → Game Server
Trigger: Player right-clicks or activates dialogue with an NPC.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | NPC object ID to talk to |

Wire size: 4 bytes (fixed)

---

#### GCNPCAsk (ID 41)
Direction: Game Server → Client
Trigger: NPC dialogue window opens; server sends script reference.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | NPC object ID |
| ScriptID | ScriptID_t | variable | Dialogue script identifier |
| NPCID | NPCID_t (WORD) | 2 | NPC type identifier |

Wire size: `szObjectID + szScriptID + szNPCID` bytes

---

#### GCSay (ID 89)
Direction: Game Server → Client
Trigger: A creature (player or NPC) spoke; broadcast to nearby clients.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ObjectID | ObjectID_t (DWORD) | 4 | Speaking creature's object ID |
| Color | uint | 4 | Text display colour (ARGB) |
| MsgLen | BYTE | 1 | Message length |
| Message | char[] | N | Chat message content |

Wire size: 9 + len(Message) bytes (variable)

---

### Party

#### CGPartyInvite (ID 276)
Direction: Client → Game Server
Trigger: Player invites another player to party, or responds to an invitation.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| TargetObjectID | ObjectID_t (DWORD) | 4 | Target player object ID |
| Code | BYTE | 1 | Action code: 0=REQUEST, 1=CANCEL, 2=ACCEPT, 3=REJECT, 4=BUSY |

Wire size: 5 bytes (fixed)

---

#### GCPartyJoined (ID 280)
Direction: Game Server → Client
Trigger: Player has successfully joined a party; sent with current member list.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| MemberCount | BYTE | 1 | Number of party members in list |
| Members[] | PARTY_MEMBER_INFO[] | variable | Per member: name (BYTE len + chars), sex (BYTE), hair_style (BYTE), ip (IP_t = 4 bytes) |

Wire size: 1 + sum(member sizes) bytes (variable, max ~103 bytes for 6 members)

---

#### GCPartyLeave (ID 279)
Direction: Game Server → Client
Trigger: A party member left or was expelled; notifies remaining members.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| ExpellerLen | BYTE | 1 | Length of expeller name (0 if self-leave) |
| Expeller | char[] | N | Name of the player who expelled (empty string if self-leave) |
| ExpelleeLen | BYTE | 1 | Length of expelled member name |
| Expellee | char[] | M | Name of expelled player |

Wire size: 2 + len(Expeller) + len(Expellee) bytes (variable)

---

### Guild

#### CGRegistGuild (ID 312)
Direction: Client → Game Server
Trigger: Guild master registers a new guild after collecting required members/resources.

| Field | Type | Size | Description |
|-------|------|------|-------------|
| GuildNameLen | BYTE | 1 | Guild name length |
| GuildName | char[] | N | Guild name (max ~30 chars) |
| GuildIntroLen | BYTE | 1 | Introduction length |
| GuildIntro | char[] | M | Guild introduction text (max ~256 chars) |

Wire size: 2 + len(GuildName) + len(GuildIntro) bytes (variable)

---

### Login Flow

#### CLLogin (ID 27) — see Connection & Authentication above.

#### LCLoginOK (ID 117) — see Connection & Authentication above.

#### LCPCList (ID 118) — see Connection & Authentication above.

---

## 7. Feature-Gated Packets

Some opcodes are only compiled when specific `__CONTENTS(flag)` preprocessor conditions are true. In a build where the flag is disabled the opcode range is still reserved but the class is not instantiated.

| Preprocessor Flag | Opcode Range | Packets Controlled |
|-------------------|-------------|-------------------|
| `__CRYPT` | header only | Encrypted packet header (`MSG_HEADER_SIZE`) |
| `__TIPOJYU_CASTLE` | 490–493 | Instance dungeon enter/lobby/result + screen effect |
| `__LC_SELECT_WORLD_ERROR` | 494 | World selection error packet |
| `__PREMIUM_GIVE_ITEM_UI` | 495–497 | Weekly/supply premium item UI packets |
| `__REPAIRSYSTEM_RENEWAL` | 498–499 | Repair info request/response |
| `__FRIEND_ADDITION` | 500–535 | Full friend system (client + GS↔SG) |
| `__GEAR_SWAP_CHANGE` | 487–488 | Gear slot swap packets |
| `__FAST_TRANSFORTER` / `__SECOND_TRANSFORTER` | 489 | Sylph / advanced transform add |
| `__PAYZONE_PASS_TICKET` | LCLoginOK field | Extra pay type byte in login response |
| `__LOGIN_PACKET` | LCLoginOK field | Reserved value byte in login response |

---

## 8. Client vs Server Packet File Counts

The following counts are derived from the source directories present in this repository. "Client" indicates packets handled by `DEClient_v664`; "Server" would apply to `DEServer_v664`.

| Direction | Files in Client Repo | Notes |
|-----------|---------------------|-------|
| CG (Client→Game) | ~120 | Full set; all have Handler classes guarded by `#ifndef __GAME_CLIENT__` |
| GC (Game→Client) | ~200 | Largest group; handlers drive client rendering/UI |
| CL (Client→Login) | ~15 | Login, character create/delete/select |
| LC (Login→Client) | ~18 | Login responses, PC list, version check, reconnect |
| LG (Login→Game) | ~3 | Connection hand-off, kick |
| GL (Game→Login) | ~3 | Connection notification |
| CU (Client→Update) | ~3 | Patch download |
| UC (Update→Client) | ~3 | Patch file delivery |
| CR (Client→Recorder) | ~5 | Spectator connection, whisper, disconnect |
| RC (Recorder→Client) | ~7 | Spectator data responses |
| GS (Game→Shared) | ~25 | Guild, friend, login events (friend system) |
| SG (Shared→Game) | ~25 | Shared server responses |
| GG (Game↔Game) | ~2 | Cross-server command, chat relay |
| **Total** | **~429 class files** | Excluding Rpackets stubs |

---

## 9. Notes on Packet Serialisation

- `read()` / `write()` methods use `SocketInputStream` / `SocketOutputStream` which wrap a TCP socket. Reads are blocking.
- Variable-length strings are written as: `oStream.write((BYTE)str.size()); oStream.write(str.c_str(), str.size());`
- Lists (e.g., GCShopList items, GCPartyJoined members) are prefixed with a BYTE count.
- `ModifyInfo` is a base class used by attack-result packets to carry stat change bitmasks and delta values. The bit flags `MF_STR`, `MF_DEX`, `MF_INT`, `MF_MAX_HP`, `MF_MAX_MP`, `MF_DAM`, `MF_DEFENSE`, `MF_TOHIT` indicate which fields follow.
- The `PacketValidator` class provides size-range checking before dispatch.
- Maximum zone size is 256×256 tiles, constraining `Coord_t` to a single byte.
- Money maximum is `2,000,000,000` (Gold_t / DWORD).
