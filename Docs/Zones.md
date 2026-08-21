# Zone reference (`*warp`)

Every zone the game server loads, read from `DARKEDEN.ZoneInfo`.

Generated from the live database. Regenerate with the query at the bottom.


## Using `*warp`

```
*warp <zone> <x> <y>
```

- Requires a character whose **Competence** is `GOD` (0), `DM` (1) or `HELPER` (2).
  A plain `PLAYER` (3) is ignored **silently** — no error is shown.
- Both coordinates must be **under 256**. Out of range does nothing, silently.
- A non-existent zone also does nothing, silently.
- `<zone>` may be a zone **ID** or a **name**. `getZoneInfoByName()` checks `ShortName`
  first, then `FullName`.

> **Names with spaces do not work.** `opwarp()` splits the command on spaces, so the
> zone token ends at the first one. Only **32 of 150** zones have a space-free ASCII
> name; for every other zone you must use the numeric ID.


## Summary

| | count |
|---|---|
| Zones total | 150 |
| PK enabled | 45 |
| Zone group 1 | 79 |
| Zone group 2 | 71 |
| Map file missing from `data/` | 2 |
| Reachable by name | 32 |


## Reachable by name

These accept a name instead of an ID:

| ID | Type as | Zone |
|---:|---|---|
| 11 | `ESNE` | Eslania NE |
| 12 | `ESNW` | Eslania NW |
| 13 | `ESSE` | Eslania SE |
| 14 | `ESSW` | Eslania SW |
| 21 | `LimboNE` | Limbo Lair NE |
| 22 | `LimboNW` | Limbo Lair NW |
| 23 | `LimboSE` | Limbo Lair SE |
| 24 | `LimboSW` | Limbo Lair SW |
| 31 | `DrobetaNE` | Drobeta NE |
| 32 | `DrobetaNW` | Drobeta NW |
| 33 | `DrobetaSE` | Drobeta SE |
| 34 | `DrobetaSW` | Drobeta SW |
| 42 | `RodinNW` | Rodin NW |
| 43 | `RodinSE` | Rodin SE |
| 44 | `RodinSW` | Rodin SW |
| 1005 | `OX` | Event OX |
| 1114 | `Tephezrare` | Tephezrare |
| 1205 | `pentanus` | pentanus |
| 1301 | `Olt` | Olt |
| 1302 | `Oltenia` | Oltenia |
| 1303 | `FreePK` | Banatul |
| 1601 | `IKO` | IK Office |
| 1602 | `IKL` | IK Lab |
| 1603 | `IK1` | IK Lab B1F |
| 1604 | `IK2` | IK Lab B2F |
| 2010 | `GuildCleric` | GuildCleric |
| 3002 | `TrapZone` | trap zone |
| 4001 | `GOA` | altar entrance |
| 4002 | `AOB` | Altar of Blood |
| 4003 | `SMOA` | Slayer Abyssal Mirror |
| 4004 | `VMOA` | Vampire Abyssal Mirror |
| 4005 | `OMOA` | Austerz Mirror of the Abyss |


## Broken zones

These are in `ZoneInfo` but their map file is absent from `data/`, so they fail
to load (logged to `bin/ZoneLoadError.log`, non-fatal):

| ID | Zone | Missing file |
|---:|---|---|
| 5002 | Asylion 2F | `Asylion_Evo2.smp` |
| 5003 | Asylion 3F | `Asylion_Evo3.smp` |


## All zones

`PK` = player killing enabled. `Grp` = zone group.

| ID | Zone | Short (KR) | Type as | Map file | Grp | PK |
|---:|---|---|---|---|:--:|:--:|
| 11 | Eslania NE | ESNE | `ESNE` | `eslania_NE.smp` | 2 |  |
| 12 | Eslania NW | ESNW | `ESNW` | `eslania_NW.smp` | 2 |  |
| 13 | Eslania SE | ESSE | `ESSE` | `eslania_SE.smp` | 2 |  |
| 14 | Eslania SW | ESSW | `ESSW` | `eslania_SW.smp` | 2 |  |
| 21 | Limbo Lair NE | LimboNE | `LimboNE` | `limbo_lair_NE.smp` | 1 |  |
| 22 | Limbo Lair NW | LimboNW | `LimboNW` | `limbo_lair_NW.smp` | 1 |  |
| 23 | Limbo Lair SE | LimboSE | `LimboSE` | `limbo_lair_SE.smp` | 1 |  |
| 24 | Limbo Lair SW | LimboSW | `LimboSW` | `limbo_lair_SW.smp` | 1 |  |
| 31 | Drobeta NE | DrobetaNE | `DrobetaNE` | `drobeta_NE.smp` | 2 |  |
| 32 | Drobeta NW | DrobetaNW | `DrobetaNW` | `drobeta_NW.smp` | 2 |  |
| 33 | Drobeta SE | DrobetaSE | `DrobetaSE` | `drobeta_SE.smp` | 2 |  |
| 34 | Drobeta SW | DrobetaSW | `DrobetaSW` | `drobeta_SW.smp` | 2 |  |
| 41 | Mount NE | 로딘북동 | — | `rodin_NE.smp` | 1 |  |
| 42 | Rodin NW | RodinNW | `RodinNW` | `rodin_NW.smp` | 1 |  |
| 43 | Rodin SE | RodinSE | `RodinSE` | `rodin_SE.smp` | 1 |  |
| 44 | Rodin SW | RodinSW | `RodinSW` | `rodin_SW.smp` | 1 |  |
| 51 | Timor NE | 티모르북동 | — | `timore_NE.smp` | 2 |  |
| 52 | Timor NW | 티모르북서 | — | `timore_NW.smp` | 2 |  |
| 53 | Timor SE | 티모르남동 | — | `timore_SE.smp` | 2 |  |
| 54 | Timor SW | 티모르남서 | — | `timore_SW.smp` | 2 |  |
| 61 | Perona NE | 페로나북동 | — | `perona_NE.smp` | 1 |  |
| 62 | Perona NW | 페로나북서 | — | `perona_NW.smp` | 1 |  |
| 63 | Perona SE | 페로나남동 | — | `perona_SE.smp` | 1 |  |
| 64 | Perona SW | 페로나남서 | — | `perona_SW.smp` | 1 |  |
| 71 | Adam's Castle | 아담동 | — | `adam_new_e.smp` | 2 | yes |
| 72 | Adam's Holy Land1 | 아담 | — | `adam_new_c.smp` | 2 | yes |
| 73 | Adam's Holy Book | 아담서 | — | `adam_new_w.smp` | 2 | yes |
| 74 | Adam's Holy Land2 | 아담북 | — | `adam_new_c_n.smp` | 2 | yes |
| 75 | Adam's Holy Land3 | 아담남 | — | `adam_new_c_s.smp` | 1 | yes |
| 81 | Northeast Castalo | 카스북동 | — | `castalo_NE.smp` | 1 |  |
| 91 | Branco Northeast | 브랑코북동 | — | `vranco_NE.smp` | 2 |  |
| 92 | Branco Northwest | 브랑코북서 | — | `vranco_NW.smp` | 2 |  |
| 93 | Branco South East | 브랑코남동 | — | `vranco_SE.smp` | 2 |  |
| 94 | Branco Southwest | 브랑코남서 | — | `vranco_SW.smp` | 2 |  |
| 1001 | to the groundwater | 지하수로 | — | `slayers_training.smp` | 1 |  |
| 1002 | Eslania Dungeon | 에슬던전 | — | `eslania_dungeon.smp` | 1 |  |
| 1003 | Inside Limbo Castle | 바토리마을 | — | `vampire_village.smp` | 1 |  |
| 1004 | Limbo Castle Dungeon | 림보던전 | — | `limbo_dungeon.smp` | 1 |  |
| 1005 | Event OX | OX | `OX` | `drobeta_OX.smp` | 2 | yes |
| 1006 | event arena | 경기장 | — | `drobeta_stadium.smp` | 2 | yes |
| 1007 | Inside Lassen Castle | 테페즈마을 | — | `rasen_yard.smp` | 2 |  |
| 1008 | Kali Grottoes | 칼리석굴 | — | `kali_cave.smp` | 2 |  |
| 1009 | Lassen Training Center | 라센수련장 | — | `rasen_training.smp` | 2 |  |
| 1010 | Payac Tunnel | 페이악터널 | — | `tunnel_peiac.smp` | 2 |  |
| 1011 | Lost Thaian B1 | 타이얀1 | — | `losttaiyan_b1f.smp` | 2 |  |
| 1012 | Lost Thaian B2F | 타이얀2 | — | `losttaiyan_b2f.smp` | 2 |  |
| 1013 | Asilion Dungeon | 아실리온 | — | `asylion_dungeon.smp` | 2 |  |
| 1020 | event arena 2 | 경기장2 | — | `drobeta_stadium.smp` | 1 | yes |
| 1100 | Bathory Dungeon B1 | 바토리1 | — | `bathory_dungeon_B1F.smp` | 1 |  |
| 1101 | Bathory Dungeon B2 | 바토리2 | — | `bathory_dungeon_B2F.smp` | 1 |  |
| 1102 | Bathory Dungeon Basement 3rd floor | 바토리3 | — | `bathory_dungeon_B3F.smp` | 1 |  |
| 1103 | Bathory Dungeon B4 | 바토리4 | — | `bathory_dungeon_B4F.smp` | 1 | yes |
| 1104 | bathory rare | 바토리레어 | — | `bathory_lair.smp` | 1 | yes |
| 1105 | Gorgo Bar Tunnel | 고르고바 | — | `tunnel_ghorgova.smp` | 2 |  |
| 1106 | Clone Batory Rare | 클론바토리레어 | — | `bathory_lair_clon.smp` | 2 | yes |
| 1111 | 1st floor of Lassen Outer Castle | 라센0 | — | `castle_rasen_1_1.smp` | 2 |  |
| 1112 | Lassennaeseong 1st floor | 라센1 | — | `castle_rasen_1_2.smp` | 2 |  |
| 1113 | 2nd floor of Lassen Castle | 라센2 | — | `castle_rasen_2_2.smp` | 2 | yes |
| 1114 | Tephezrare | 테페즈레어 | `Tephezrare` | `tepes_lair.smp` | 2 | yes |
| 1115 | Clonte Pezrare | 클론테페즈레어 | — | `tepes_lair_clon.smp` | 1 | yes |
| 1121 | Raom Dungeon 2nd floor | 라옴2 | — | `slayer_battlezone1.smp` | 1 |  |
| 1122 | Temerier Shrine | 테메리에 | — | `slayer_battlezone2.smp` | 1 |  |
| 1123 | Hillanom Shrine | 힐라놈 | — | `bathory_battlezone.smp` | 1 |  |
| 1124 | Issen Dungeon 2nd floor | 아이센2 | — | `rasen_battlezone.smp` | 1 |  |
| 1125 | Raom Dungeon 1st floor | 라옴1 | — | `drobeta_dungeon_s1f.smp` | 2 |  |
| 1126 | Isen Dungeon 1st floor | 아이센1 | — | `drobeta_dungeon_v1f.smp` | 2 |  |
| 1127 | Isen Dungeon 3rd floor | 아이센3 | — | `icen_Dungeon3F.smp` | 2 |  |
| 1128 | Raom Dungeon 3rd floor | 라옴3 | — | `laom_Dungeon3F.smp` | 2 |  |
| 1129 | Raom Dungeon 4th floor | 라옴4 | — | `laom_Dungeon4F.smp` | 2 |  |
| 1130 | Raohm 5 |  | — | `laom_Dungeon5F.smp` | 2 |  |
| 1131 | Caligo Dungeon 1st floor | 칼리1층 | — | `caligo_dungeon.smp` | 2 |  |
| 1132 | Caligo Dungeon 2nd floor | 칼리2층 | — | `caligo_dungeon.smp` | 2 |  |
| 1133 | Caligo Dungeon 3rd floor | 칼리3층 | — | `caligo_dungeon.smp` | 2 |  |
| 1134 | Caligo Dungeon 4th Floor | 칼리4층 | — | `caligo_dungeon.smp` | 2 |  |
| 1201 | octabus castle | 옥타부스 | — | `castle_octavus.smp` | 1 | yes |
| 1202 | Tertius Castle | 테르티우스 | — | `castle_tertius.smp` | 1 | yes |
| 1203 | septimus castle | 셉티무스 | — | `castle_septimus.smp` | 1 | yes |
| 1204 | Quartus Castle | 쿠아르투스 | — | `castle_quartus.smp` | 1 | yes |
| 1205 | pentanus | 펜타누스 | `pentanus` | `castle_pentanus.smp` | 2 | yes |
| 1206 | Hexirius Castle | 헥시리우스 | — | `castle_hexserius.smp` | 2 | yes |
| 1211 | Octaboo's Dungeon 1B | 옥타1 | — | `octavus_dungeon1f.smp` | 2 | yes |
| 1212 | Octaboo Dungeon 2B | 옥타2 | — | `octavus_dungeon2f.smp` | 2 | yes |
| 1221 | Tertius Dungeon 1B | 테르1 | — | `tertius_dungeon1f.smp` | 1 | yes |
| 1222 | Tertius Dungeon 2B | 테르2 | — | `tertius_dungeon2f.smp` | 1 | yes |
| 1231 | Septimus Dungeon 1B | 셉티1 | — | `septimus_dungeon1f.smp` | 2 | yes |
| 1232 | Septimus Dungeon 2B | 셉티2 | — | `septimus_dungeon2f.smp` | 2 | yes |
| 1241 | Quartus Dungeon 1B | 쿠아1 | — | `quartus_dungeon1f.smp` | 1 | yes |
| 1242 | Quartus Dungeon 2B | 쿠아2 | — | `quartus_dungeon2f.smp` | 1 | yes |
| 1251 | Pentanus Dungeon 1B | 펜타1 | — | `pentanus_dungeon1f.smp` | 2 | yes |
| 1252 | Pentanus Dungeon 2B | 펜타2 | — | `pentanus_dungeon2f.smp` | 2 | yes |
| 1261 | Hexirius Dungeon 1B | 헥시1 | — | `hexserius_dungeon1f.smp` | 1 | yes |
| 1262 | Hexirius Dungeon 2B | 헥시2 | — | `hexserius_dungeon2f.smp` | 1 | yes |
| 1301 | Olt | 슬레PK | `Olt` | `slayerpk.smp` | 1 | yes |
| 1302 | Oltenia | 뱀파PK | `Oltenia` | `vampirepk.smp` | 1 | yes |
| 1303 | Banatul | FreePK | `FreePK` | `freepk.smp` | 1 | yes |
| 1311 | Austers Village | 아우마을 | — | `ousters_village.smp` | 2 |  |
| 1321 | Hanial Dungeon B1 | 하니알1 | — | `ousters_dungeon01.smp` | 1 |  |
| 1322 | Hanial Dungeon B2 | 하니알2 | — | `ousters_dungeon02.smp` | 1 |  |
| 1323 | Hanial Dungeon B3 | 하니알3 | — | `ousters_dungeon03.smp` | 1 |  |
| 1324 | Hanial Dungeon B4 | 하니알4 | — | `ousters_dungeon04.smp` | 1 |  |
| 1401 | Rust Tower 1st floor | 러스트1층 | — | `lusttower_1f.smp` | 1 |  |
| 1402 | Rust Tower 2nd floor | 러스트2층 | — | `lusttower_2f.smp` | 1 |  |
| 1410 | Illusion's Way 1 | 일루젼1 | — | `Gdr_illusion_01.smp` | 2 | yes |
| 1411 | Illusion's Way 2 | 일루젼2 | — | `Gdr_illusion_02.smp` | 2 | yes |
| 1412 | Gildre Rare | 질드레레어 | — | `Gdr_lair_01.smp` | 2 | yes |
| 1413 | Gildre Rare Core | 질드레레어코어 | — | `Gdr_lair_hard.smp` | 2 |  |
| 1500 | siege test | 공성전 | — | `siege_warfare.smp` | 1 | yes |
| 1501 | Octabus Siege Area | 옥타공 | — | `siege_warfare.smp` | 1 | yes |
| 1502 | Siege of Tertius | 테르공 | — | `siege_warfare.smp` | 1 | yes |
| 1503 | Siege of Septimus | 셉티공 | — | `siege_warfare.smp` | 1 | yes |
| 1504 | Siege of Quartus | 쿠아공 | — | `siege_warfare.smp` | 1 | yes |
| 1505 | Siege of Pentanus | 펜타공 | — | `siege_warfare.smp` | 2 | yes |
| 1506 | Siege of Hexirius | 헥시공 | — | `siege_warfare.smp` | 2 | yes |
| 1600 | Path to Pierce | 패투피 | — | `path_to_fears.smp` | 1 |  |
| 1601 | IK Office | IKO | `IKO` | `ik_offic.smp` | 1 |  |
| 1602 | IK Lab | IKL | `IKL` | `ik_lab.smp` | 1 |  |
| 1603 | IK Lab B1F | IK1 | `IK1` | `ik_lab_b1f.smp` | 1 |  |
| 1604 | IK Lab B2F | IK2 | `IK2` | `ik_lab_b2f.smp` | 1 |  |
| 1611 | Junje Tunnel 1st floor | 준저1 | — | `under_pass_1f.smp` | 2 |  |
| 1612 | Junje Tunnel 2nd floor | 준저2 | — | `under_pass_2f.smp` | 2 |  |
| 1621 | New Map | New Map | — | `castellum.smp` | 2 |  |
| 2000 | soldier's guild | 군인0 | — | `guild_army_B1.smp` | 1 |  |
| 2001 | Soldiers Guild 1st Floor | 군인1 | — | `guild_army_1F.smp` | 1 |  |
| 2002 | Soldiers Guild 2nd floor | 군인2 | — | `guild_army_2F.smp` | 1 |  |
| 2003 | Soldiers Guild 3rd floor | 군인3 | — | `guild_army_3F.smp` | 1 |  |
| 2004 | Soldier's Guild Rooftop | 군인4 | — | `guild_army_4F.smp` | 1 |  |
| 2010 | GuildCleric | ?o垂0 | `GuildCleric` | `guild_cleric_B1.smp` | 2 |  |
| 2011 | Cleric Guild 1F | 성직1 | — | `guild_cleric_1F.smp` | 2 |  |
| 2012 | Cleric Guild 2nd floor | 성직2 | — | `guild_cleric_2F.smp` | 2 |  |
| 2013 | Cleric Guild 3F | 성직3 | — | `guild_cleric_3F.smp` | 2 |  |
| 2014 | Cleric Guild 4th Floor | 성직4 | — | `guild_cleric_4F.smp` | 2 |  |
| 2020 | Samurai Guild Underground | 무사0 | — | `guild_knight_B1.smp` | 1 |  |
| 2021 | Samurai Guild 1F | 무사1 | — | `guild_knight_1F.smp` | 1 |  |
| 2022 | Samurai Guild 2nd floor | 무사2 | — | `guild_knight_2F.smp` | 1 |  |
| 2023 | Samurai Guild 3F | 무사3 | — | `guild_knight_3F.smp` | 1 |  |
| 2024 | Warrior Guild Rooftop | 무사4 | — | `guild_knight_4F.smp` | 1 |  |
| 2101 | field command | 초보0 | — | `tutorial_N.smp` | 1 |  |
| 2102 | out of town | 초보1 | — | `tutorial_S.smp` | 1 |  |
| 3001 | Lipinium Coal Mine | 리피탄광 | — | `maze.smp` | 1 |  |
| 3002 | trap zone | TrapZone | `TrapZone` | `trapzone01.smp` | 1 |  |
| 3003 | Lipinium Storage Room | 리피저장실 | — | `trapzone02.smp` | 1 |  |
| 4001 | altar entrance | GOA | `GOA` | `gate_of_alter.smp` | 1 |  |
| 4002 | Altar of Blood | AOB | `AOB` | `alter_of_blood.smp` | 1 |  |
| 4003 | Slayer Abyssal Mirror | SMOA | `SMOA` | `gate_of_alter.smp` | 1 |  |
| 4004 | Vampire Abyssal Mirror | VMOA | `VMOA` | `gate_of_alter.smp` | 1 |  |
| 4005 | Austerz Mirror of the Abyss | OMOA | `OMOA` | `gate_of_alter.smp` | 2 |  |
| 5002 | Asylion 2F | Asylion 2F | — | `Asylion_Evo2.smp` | 2 |  |
| 5003 | Asylion 3F | Asylion 3F | — | `Asylion_Evo3.smp` | 2 |  |
| 8000 | Developer Training Center | 훈련소 | — | `devt.smp` | 1 |  |
| 8001 | 劤藤暠暠 | 劤藤속돨뒈暠 | — | `survival.smp` | 1 |  |


## Regenerating this file

```sql
SELECT ZoneID, FullName, ShortName, ZoneGroupID, PKZone, SmpFileName
FROM ZoneInfo ORDER BY ZoneID;
```

`ShortName` is EUC-KR encoded; decode it as `euc-kr`/`cp949` when reading the column
outside the game. `FullName` is ASCII English for 149 of the 150 zones.
