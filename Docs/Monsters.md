# Monster IDs and the summon command

Generated from the `MonsterInfo` table in the `DARKEDEN` database.
Source of truth: that table, loaded once at server start by `MonsterInfo.cpp` (`SELECT MType, SType, HName, EName, ... FROM MonsterInfo`).

**652 monsters**, MType 4-850, levels 1-350, 87 flagged as Chief (boss).

## The GM command

GM commands are chat messages starting with `*` **at position 0** - no space before it.
Handled in `Core/Cpackets/CGSayHandler.cpp`; `*summon` dispatches to `opsummon()` at line 3919.

```
*summon {MType} <count>        summon by monster type id (the MType column below)
*summon <SpriteType> <count>   first token numeric => treated as SpriteType
*summon <ChiefName> <count>    first token non-numeric => looked up as a chief monster name
```

Examples:

```
*summon {4} 1        one Dead Body
*summon {850} 3      three of MType 850
```

### Requirements and caveats

- Requires **GOD or DM** rank (`pCreature->isGOD() || pCreature->isDM()`). A normal player is ignored silently.
- Spawns at a walkable spot near you, found via `findSuitablePosition()`. It **refuses inside a safe zone**
  (`pZone->getZoneLevel(pt.x, pt.y) & SAFE_ZONE`), so step outside town first or nothing appears.
- Every summon is logged server-side to `summon.txt` with your name, zone id and the raw command.
- `opsummon` parses two further optional trailing tokens after `<count>` (internally `mad` and a group
  name). Their behaviour is not documented here because it was not tested - see the parser if you need them.

## Bosses (Chief flag set)

| MType | Level | Name |
|------:|------:|------|
| 463 | 5 | Chief Dead Body [1] |
| 464 | 5 | Chief Dead Body [1] |
| 564 | 5 | Chief Dead Body [1] |
| 466 | 7 | Chief Kid [1] |
| 565 | 8 | Chief Turning D [1] |
| 461 | 9 | Chief Soldier [1] |
| 462 | 9 | Chief Soldier [1] |
| 566 | 10 | Chief Turning S [1] |
| 567 | 12 | Chief Kid [1] |
| 568 | 12 | Chief Wolf [7] |
| 640 | 12 | Quest Kid |
| 469 | 19 | Chief Alcan [2] |
| 569 | 24 | Chief Captain [2] |
| 472 | 25 | Chief Mutant [2] |
| 474 | 28 | Chief Moderas [3] |
| 641 | 28 | Quest Moderas |
| 570 | 30 | Chief Alcan [2] |
| 468 | 32 | Chief 32 Strider [3] |
| 571 | 32 | Chief IronTeeth [2] |
| 473 | 35 | Chief Estroider [3] |
| 572 | 36 | Chief Red Eye [2] |
| 573 | 40 | Chief Mutant [2] |
| 465 | 45 | Chief Warlock [4] |
| 574 | 46 | Chief Moderas [3] |
| 467 | 50 | Chief Golemer [4] |
| 575 | 50 | Chief Vandaliz [3] |
| 576 | 54 | Chief 54 Strider [3] |
| 471 | 55 | Chief Dark Wing [5] |
| 577 | 60 | Chief Estroider [3] |
| 476 | 65 | Chief Chaos Kn. [6] |
| 477 | 65 | Chief Black Kn. [6] |
| 578 | 66 | Chief Widows [3] |
| 642 | 66 | Quest Widows |
| 479 | 68 | Chief Hell Wiz. [6] |
| 579 | 70 | Chief Hoble [4] |
| 475 | 71 | Chief Dark Scr. [6] |
| 470 | 75 | Chief Chaos B [7] |
| 580 | 76 | Chief Big Fang [3] |
| 581 | 80 | Chief  Warlock [4] |
| 643 | 80 | Quest Blood Warlock |
| 582 | 90 | Chief Golemer [4] |
| 478 | 95 | Chief Lo. Pink [9] |
| 480 | 100 | Chief Guardian [8] |
| 481 | 100 | Chief Chaos [8] |
| 583 | 100 | Chief Dark Wing [5] |
| 819 | 100 | Plumpy Boar [14] |
| 584 | 110 | Chief Cri. Slau [5] |
| 644 | 110 | Quest Crimson Slaughter |
| 585 | 116 | Chief Reaper [5] |
| 586 | 120 | Chief Chaos K. [6] |
| 682 | 120 | Boss Crimson Slaughter |
| 587 | 126 | Chief Hell Wiz. [6] |
| 588 | 132 | Chief Dark Scr [6] |
| 589 | 140 | Chief Chaos R [7] |
| 645 | 140 | Quest Chaos Gurdian |
| 683 | 140 | Boss Lord Chaos |
| 845 | 140 | Morgoth [14+20%] |
| 590 | 146 | Chief Hell Fie. [7] |
| 591 | 154 | Chief Guardian [11] |
| 647 | 154 | Quest Dark Guardian |
| 838 | 158 | Cabracam [11+20%] |
| 684 | 160 | Boss Dark Berith |
| 592 | 162 | Chief L.Chaos [10] |
| 646 | 162 | Quest Lord Chaos |
| 593 | 180 | Chief Lo. Brown [9] |
| 594 | 198 | Chief H.Fiend [10] |
| 595 | 198 | Chief Ch.Greed [10] |
| 596 | 198 | Chief Haze [10] |
| 648 | 198 | Quest Chaos Greed |
| 597 | 200 | Chief Shaman [10] |
| 598 | 200 | Chief Rimmon [10] |
| 649 | 200 | Quest Dun Wolfarch |
| 685 | 200 | Boss Ash Balog [15] |
| 817 | 200 | BogletB  [15] |
| 818 | 200 | Massacre [14] |
| 600 | 210 | Chief Berith [11] |
| 686 | 220 | Boss Turning Dead |
| 601 | 224 | Chief Giant Os [12] |
| 602 | 236 | Chief  Crag [14] |
| 603 | 240 | Chief Lich Jel [14] |
| 599 | 250 | Chief Wolfarch [10] |
| 850 | 250 | Poisoned Ruffian Skull |
| 814 | 350 | Cerberus [14] |
| 815 | 350 | Manticoret [14] |
| 816 | 350 | BogletH [15] |
| 824 | 350 | Cerberus [14] |
| 825 | 350 | Manticoret [14] |

## All monsters

SType is the sprite type (the second `*summon` form).

| MType | SType | Level | Name |
|------:|------:|------:|------|
| 4 | 5 | 1 | Dead Body |
| 5 | 8 | 1 | Turning Dead [1] |
| 6 | 6 | 2 | Kid [1] |
| 7 | 7 | 1 | Turning Soul [1] |
| 8 | 9 | 10 | Captain [2] |
| 9 | 4 | 5 | Soldier [2] |
| 17 | 16 | 250 | Kaiser |
| 28 | 27 | 40 | Blood Warlock [4] |
| 29 | 5 | 1 | Dead Body [1] |
| 30 | 5 | 1 | Dead Body [1] |
| 31 | 5 | 1 | Dead Body [1] |
| 32 | 5 | 1 | Dead Body [1] |
| 33 | 5 | 1 | Dead Body [1] |
| 34 | 5 | 1 | Dead Body [1] |
| 35 | 5 | 1 | Dead Body [1] |
| 36 | 5 | 1 | Dead Body [1] |
| 37 | 5 | 1 | Dead Body [1] |
| 38 | 8 | 1 | Turning Dead [1] |
| 39 | 8 | 1 | Turning Dead [1] |
| 40 | 8 | 1 | Turning Dead [1] |
| 41 | 8 | 1 | Turning Dead [1] |
| 42 | 8 | 1 | Turning Dead [1] |
| 43 | 8 | 1 | Turning Dead [1] |
| 44 | 8 | 1 | Turning Dead [1] |
| 45 | 8 | 1 | Turning Dead [1] |
| 46 | 8 | 1 | Turning Dead [1] |
| 47 | 6 | 2 | Kid [1] |
| 48 | 6 | 2 | Kid [1] |
| 49 | 6 | 2 | Kid [1] |
| 50 | 6 | 2 | Kid [1] |
| 51 | 6 | 2 | Kid [1] |
| 52 | 6 | 2 | Kid [1] |
| 53 | 6 | 2 | Kid [1] |
| 54 | 6 | 2 | Kid [1] |
| 55 | 6 | 2 | Kid [1] |
| 56 | 7 | 1 | Turning Soul [1] |
| 57 | 7 | 1 | Turning Soul [1] |
| 58 | 7 | 1 | Turning Soul [1] |
| 59 | 7 | 1 | Turning Soul [1] |
| 60 | 7 | 1 | Turning Soul [1] |
| 61 | 7 | 1 | Turning Soul [1] |
| 62 | 7 | 1 | Turning Soul [1] |
| 63 | 7 | 1 | Turning Soul [1] |
| 64 | 7 | 1 | Turning Soul [1] |
| 65 | 9 | 10 | Captain [2] |
| 66 | 9 | 10 | Captain [2] |
| 67 | 9 | 10 | Captain [2] |
| 68 | 9 | 10 | Captain [2] |
| 69 | 9 | 10 | Captain [2] |
| 70 | 9 | 10 | Captain [2] |
| 71 | 9 | 10 | Captain [2] |
| 72 | 9 | 10 | Captain [2] |
| 73 | 9 | 10 | Captain [2] |
| 74 | 4 | 5 | Soldier [2] |
| 75 | 4 | 5 | Soldier [2] |
| 76 | 4 | 5 | Soldier [2] |
| 77 | 4 | 5 | Soldier [2] |
| 78 | 4 | 5 | Soldier [2] |
| 79 | 4 | 5 | Soldier [2] |
| 80 | 4 | 5 | Soldier [2] |
| 81 | 4 | 5 | Soldier [2] |
| 82 | 4 | 5 | Soldier [2] |
| 83 | 27 | 40 | Blood Warlock [4] |
| 84 | 27 | 40 | Blood Warlock [4] |
| 85 | 27 | 40 | Blood Warlock [4] |
| 86 | 27 | 40 | Blood Warlock [4] |
| 87 | 27 | 40 | Blood Warlock [4] |
| 88 | 27 | 40 | Blood Warlock [4] |
| 89 | 27 | 40 | Blood Warlock [4] |
| 90 | 27 | 40 | Blood Warlock [4] |
| 91 | 27 | 40 | Blood Warlock [4] |
| 92 | 37 | 250 | Vricolacas |
| 104 | 40 | 45 | Golemer [4] |
| 105 | 41 | 27 | Dirty Strider [3] |
| 106 | 42 | 14 | Alcan [2] |
| 107 | 43 | 18 | Red Eye [2] |
| 111 | 40 | 45 | Golemer [4] |
| 112 | 40 | 45 | Golemer [4] |
| 113 | 40 | 45 | Golemer [4] |
| 114 | 40 | 45 | Golemer [4] |
| 115 | 40 | 45 | Golemer [4] |
| 116 | 40 | 45 | Golemer [4] |
| 117 | 40 | 45 | Golemer [4] |
| 118 | 40 | 45 | Golemer [4] |
| 119 | 40 | 45 | Golemer [4] |
| 120 | 41 | 27 | Dirty Strider [3] |
| 121 | 41 | 27 | Dirty Strider [3] |
| 122 | 41 | 27 | Dirty Strider [3] |
| 123 | 41 | 27 | Dirty Strider [3] |
| 124 | 41 | 27 | Dirty Strider [3] |
| 125 | 41 | 27 | Dirty Strider [3] |
| 126 | 41 | 27 | Dirty Strider [3] |
| 127 | 41 | 27 | Dirty Strider [3] |
| 128 | 41 | 27 | Dirty Strider [3] |
| 129 | 42 | 14 | Alcan [2] |
| 130 | 42 | 14 | Alcan [2] |
| 131 | 42 | 14 | Alcan [2] |
| 132 | 42 | 14 | Alcan [2] |
| 133 | 42 | 14 | Alcan [2] |
| 134 | 42 | 14 | Alcan [2] |
| 135 | 42 | 14 | Alcan [2] |
| 136 | 42 | 14 | Alcan [2] |
| 137 | 42 | 14 | Alcan [2] |
| 138 | 43 | 18 | Red Eye [2] |
| 139 | 43 | 18 | Red Eye [2] |
| 140 | 43 | 18 | Red Eye [2] |
| 141 | 43 | 18 | Red Eye [2] |
| 142 | 43 | 18 | Red Eye [2] |
| 143 | 43 | 18 | Red Eye [2] |
| 144 | 43 | 18 | Red Eye [2] |
| 145 | 43 | 18 | Red Eye [2] |
| 146 | 43 | 18 | Red Eye [2] |
| 147 | 47 | 70 | Chaos Guardi [7] |
| 148 | 47 | 70 | Chaos Guardi [7] |
| 149 | 47 | 70 | Chaos Guardi [7] |
| 150 | 47 | 70 | Chaos Guardi [7] |
| 151 | 47 | 70 | Chaos Guardi [7] |
| 152 | 47 | 70 | Chaos Guardi [7] |
| 153 | 47 | 70 | Chaos Guardi [7] |
| 154 | 47 | 70 | Chaos Guardi [7] |
| 155 | 47 | 70 | Chaos Guardi [7] |
| 156 | 47 | 70 | Chaos Guardi [7] |
| 165 | 48 | 35 | Hoble [4] |
| 166 | 57 | 50 | Shadow Wing [5] |
| 167 | 48 | 35 | Hoble [4] |
| 168 | 48 | 35 | Hoble [4] |
| 169 | 48 | 35 | Hoble [4] |
| 170 | 48 | 35 | Hoble [4] |
| 171 | 48 | 35 | Hoble [4] |
| 172 | 48 | 35 | Hoble [4] |
| 173 | 48 | 35 | Hoble [4] |
| 174 | 48 | 35 | Hoble [4] |
| 175 | 48 | 35 | Hoble [4] |
| 176 | 57 | 50 | Shadow Wing [5] |
| 177 | 57 | 50 | Shadow Wing [5] |
| 178 | 57 | 50 | Shadow Wing [5] |
| 179 | 57 | 50 | Shadow Wing [5] |
| 180 | 57 | 50 | Shadow Wing [5] |
| 181 | 57 | 50 | Shadow Wing [5] |
| 182 | 57 | 50 | Shadow Wing [5] |
| 183 | 57 | 50 | Shadow Wing [5] |
| 184 | 57 | 50 | Shadow Wing [5] |
| 187 | 60 | 20 | Mutant [2] |
| 188 | 60 | 20 | Mutant [2] |
| 189 | 60 | 20 | Mutant [2] |
| 190 | 60 | 20 | Mutant [2] |
| 191 | 60 | 20 | Mutant [2] |
| 192 | 60 | 20 | Mutant [2] |
| 193 | 60 | 20 | Mutant [2] |
| 194 | 60 | 20 | Mutant [2] |
| 195 | 60 | 20 | Mutant [2] |
| 196 | 60 | 20 | Mutant [2] |
| 197 | 61 | 33 | Widows [3] |
| 198 | 61 | 33 | Widows [3] |
| 199 | 61 | 33 | Widows [3] |
| 200 | 61 | 33 | Widows [3] |
| 201 | 61 | 33 | Widows [3] |
| 202 | 61 | 33 | Widows [3] |
| 203 | 61 | 33 | Widows [3] |
| 204 | 61 | 33 | Widows [3] |
| 205 | 61 | 33 | Widows [3] |
| 206 | 61 | 33 | Widows [3] |
| 207 | 62 | 30 | Estroider [3] |
| 208 | 62 | 30 | Estroider [3] |
| 209 | 62 | 30 | Estroider [3] |
| 210 | 62 | 30 | Estroider [3] |
| 211 | 62 | 30 | Estroider [3] |
| 212 | 62 | 30 | Estroider [3] |
| 213 | 62 | 30 | Estroider [3] |
| 214 | 62 | 30 | Estroider [3] |
| 215 | 62 | 30 | Estroider [3] |
| 216 | 62 | 30 | Estroider [3] |
| 218 | 64 | 23 | Moderas [3] |
| 221 | 64 | 23 | Moderas [3] |
| 222 | 64 | 23 | Moderas [3] |
| 223 | 64 | 23 | Moderas [3] |
| 224 | 64 | 23 | Moderas [3] |
| 225 | 64 | 23 | Moderas [3] |
| 226 | 64 | 23 | Moderas [3] |
| 227 | 64 | 23 | Moderas [3] |
| 228 | 64 | 23 | Moderas [3] |
| 229 | 64 | 23 | Moderas [3] |
| 230 | 67 | 25 | Vandalizer [3] |
| 231 | 67 | 25 | Vandalizer [3] |
| 232 | 67 | 25 | Vandalizer [3] |
| 233 | 67 | 25 | Vandalizer [3] |
| 234 | 67 | 25 | Vandalizer [3] |
| 235 | 67 | 25 | Vandalizer [3] |
| 236 | 67 | 25 | Vandalizer [3] |
| 237 | 67 | 25 | Vandalizer [3] |
| 238 | 67 | 25 | Vandalizer [3] |
| 239 | 67 | 25 | Vandalizer [3] |
| 240 | 68 | 38 | Big Fang [3] |
| 241 | 68 | 38 | Big Fang [3] |
| 242 | 68 | 38 | Big Fang [3] |
| 243 | 68 | 38 | Big Fang [3] |
| 244 | 68 | 38 | Big Fang [3] |
| 245 | 68 | 38 | Big Fang [3] |
| 246 | 68 | 38 | Big Fang [3] |
| 247 | 68 | 38 | Big Fang [3] |
| 248 | 68 | 38 | Big Fang [3] |
| 249 | 68 | 38 | Big Fang [3] |
| 256 | 69 | 15 | Iron Teeth [2] |
| 257 | 69 | 15 | Iron Teeth [2] |
| 258 | 69 | 15 | Iron Teeth [2] |
| 259 | 69 | 15 | Iron Teeth [2] |
| 260 | 69 | 15 | Iron Teeth [2] |
| 261 | 69 | 15 | Iron Teeth [2] |
| 262 | 69 | 15 | Iron Teeth [2] |
| 263 | 69 | 15 | Iron Teeth [2] |
| 264 | 69 | 15 | Iron Teeth [2] |
| 265 | 69 | 15 | Iron Teeth [2] |
| 266 | 70 | 66 | Dark Screamer [6] |
| 267 | 70 | 66 | Dark Screamer [6] |
| 268 | 70 | 66 | Dark Screamer [6] |
| 269 | 70 | 66 | Dark Screamer [6] |
| 270 | 70 | 66 | Dark Screamer [6] |
| 271 | 70 | 66 | Dark Screamer [6] |
| 272 | 70 | 66 | Dark Screamer [6] |
| 273 | 70 | 66 | Dark Screamer [6] |
| 274 | 70 | 66 | Dark Screamer [6] |
| 275 | 70 | 66 | Dark Screamer [6] |
| 276 | 71 | 60 | Chaos Knight [6] |
| 277 | 71 | 60 | Chaos Knight [6] |
| 278 | 71 | 60 | Chaos Knight [6] |
| 279 | 71 | 60 | Chaos Knight [6] |
| 280 | 71 | 60 | Chaos Knight [6] |
| 281 | 71 | 60 | Chaos Knight [6] |
| 282 | 71 | 60 | Chaos Knight [6] |
| 283 | 71 | 60 | Chaos Knight [6] |
| 284 | 71 | 60 | Chaos Knight [6] |
| 285 | 71 | 60 | Chaos Knight [6] |
| 286 | 72 | 55 | Crimson Slaugh. [5] |
| 287 | 72 | 55 | Crimson Slaugh. [5] |
| 288 | 72 | 55 | Crimson Slaugh. [5] |
| 289 | 72 | 55 | Crimson Slaugh. [5] |
| 290 | 72 | 55 | Crimson Slaugh. [5] |
| 291 | 72 | 55 | Crimson Slaugh. [5] |
| 292 | 72 | 55 | Crimson Slaugh. [5] |
| 293 | 72 | 55 | Crimson Slaugh. [5] |
| 294 | 72 | 55 | Crimson Slaugh. [5] |
| 295 | 72 | 55 | Crimson Slaugh. [5] |
| 318 | 73 | 90 | Lord Darkness [9] |
| 319 | 73 | 90 | Lord Darkness [9] |
| 320 | 73 | 90 | Lord Darkness [9] |
| 321 | 73 | 90 | Lord Darkness [9] |
| 322 | 73 | 90 | Lord Darkness [9] |
| 323 | 73 | 90 | Lord Darkness [9] |
| 324 | 73 | 90 | Lord Darkness [9] |
| 325 | 73 | 90 | Lord Darkness [9] |
| 326 | 73 | 90 | Lord Darkness [9] |
| 327 | 73 | 90 | Lord Darkness [9] |
| 328 | 74 | 58 | Reaper [5] |
| 329 | 74 | 58 | Reaper [5] |
| 330 | 74 | 58 | Reaper [5] |
| 331 | 74 | 58 | Reaper [5] |
| 332 | 74 | 58 | Reaper [5] |
| 333 | 74 | 58 | Reaper [5] |
| 334 | 74 | 58 | Reaper [5] |
| 335 | 74 | 58 | Reaper [5] |
| 336 | 74 | 58 | Reaper [5] |
| 337 | 74 | 58 | Reaper [5] |
| 338 | 75 | 73 | Hell Guardian [7] |
| 339 | 75 | 73 | Hell Guardian [7] |
| 340 | 75 | 73 | Hell Guardian [7] |
| 341 | 75 | 73 | Hell Guardian [7] |
| 342 | 75 | 73 | Hell Guardian [7] |
| 343 | 75 | 73 | Hell Guardian [7] |
| 344 | 75 | 73 | Hell Guardian [7] |
| 345 | 75 | 73 | Hell Guardian [7] |
| 346 | 75 | 73 | Hell Guardian [7] |
| 347 | 75 | 73 | Hell Guardian [7] |
| 348 | 76 | 63 | Hell Wizard [6] |
| 349 | 76 | 63 | Hell Wizard [6] |
| 350 | 76 | 63 | Hell Wizard [6] |
| 351 | 76 | 63 | Hell Wizard [6] |
| 352 | 76 | 63 | Hell Wizard [6] |
| 353 | 76 | 63 | Hell Wizard [6] |
| 354 | 76 | 63 | Hell Wizard [6] |
| 355 | 76 | 63 | Hell Wizard [6] |
| 356 | 76 | 63 | Hell Wizard [6] |
| 357 | 76 | 63 | Hell Wizard [6] |
| 358 | 78 | 70 | Santa1 |
| 359 | 78 | 1 | Santa2 |
| 360 | 77 | 65 | Rudolf2 |
| 361 | 77 | 1 | Rudolf2 |
| 362 | 77 | 1 | Rudolf2 |
| 363 | 77 | 1 | Rudolf2 |
| 364 | 77 | 1 | Rudolf2 |
| 365 | 77 | 1 | Rudolf2 |
| 366 | 77 | 1 | Rudolf2 |
| 367 | 77 | 1 | Rudolf2 |
| 368 | 77 | 1 | Rudolf2 |
| 369 | 77 | 1 | Rudolf2 |
| 370 | 77 | 1 | Rudolf2 |
| 371 | 86 | 1 | Relic1 |
| 372 | 86 | 1 | Relic2 |
| 373 | 86 | 1 | Relic3 |
| 374 | 87 | 1 | Relic4 |
| 375 | 87 | 1 | Relic5 |
| 376 | 87 | 1 | Relic6 |
| 377 | 88 | 99 | Dark Guardian [8] |
| 378 | 88 | 99 | Dark Guardian [8] |
| 379 | 88 | 99 | Dark Guardian [8] |
| 380 | 88 | 99 | Dark Guardian [8] |
| 381 | 88 | 99 | Dark Guardian [8] |
| 382 | 88 | 99 | Dark Guardian [8] |
| 383 | 88 | 99 | Dark Guardian [8] |
| 384 | 88 | 99 | Dark Guardian [8] |
| 385 | 88 | 99 | Dark Guardian [8] |
| 386 | 88 | 99 | Dark Guardian [8] |
| 387 | 89 | 99 | Lord Chaos [8] |
| 388 | 89 | 99 | Lord Chaos [8] |
| 389 | 89 | 99 | Lord Chaos [8] |
| 390 | 89 | 99 | Lord Chaos [8] |
| 391 | 89 | 99 | Lord Chaos [8] |
| 392 | 89 | 99 | Lord Chaos [8] |
| 393 | 89 | 99 | Lord Chaos [8] |
| 394 | 89 | 99 | Lord Chaos [8] |
| 395 | 89 | 99 | Lord Chaos [8] |
| 396 | 89 | 99 | Lord Chaos [8] |
| 397 | 90 | 99 | Chaos Greed [10] |
| 398 | 90 | 99 | Chaos Greed [10] |
| 399 | 90 | 99 | Chaos Greed [10] |
| 400 | 90 | 99 | Chaos Greed [10] |
| 401 | 90 | 99 | Chaos Greed [10] |
| 402 | 90 | 99 | Chaos Greed [10] |
| 403 | 90 | 99 | Chaos Greed [10] |
| 404 | 90 | 99 | Chaos Greed [10] |
| 405 | 90 | 99 | Chaos Greed [10] |
| 406 | 90 | 99 | Chaos Greed [10] |
| 407 | 91 | 99 | Hell Fiend [10] |
| 408 | 91 | 99 | Hell Fiend [10] |
| 409 | 91 | 99 | Hell Fiend [10] |
| 410 | 91 | 99 | Hell Fiend [10] |
| 411 | 91 | 99 | Hell Fiend [10] |
| 412 | 91 | 99 | Hell Fiend [10] |
| 413 | 91 | 99 | Hell Fiend [10] |
| 414 | 91 | 99 | Hell Fiend [10] |
| 415 | 91 | 99 | Hell Fiend [10] |
| 416 | 91 | 99 | Hell Fiend [10] |
| 417 | 92 | 99 | Dark Haze [10] |
| 418 | 92 | 99 | Dark Haze [10] |
| 419 | 92 | 99 | Dark Haze [10] |
| 420 | 92 | 99 | Dark Haze [10] |
| 421 | 92 | 99 | Dark Haze [10] |
| 422 | 92 | 99 | Dark Haze [10] |
| 423 | 92 | 99 | Dark Haze [10] |
| 424 | 92 | 99 | Dark Haze [10] |
| 425 | 92 | 99 | Dark Haze [10] |
| 426 | 92 | 99 | Dark Haze [10] |
| 431 | 97 | 125 | Bathory |
| 432 | 98 | 125 | Bathory |
| 433 | 100 | 135 | Tepez |
| 434 | 99 | 135 | Tepez |
| 435 | 98 | 100 | Bathory |
| 436 | 99 | 10 | Tepez |
| 437 | 101 | 100 | Dun Wolfarch [10] |
| 438 | 102 | 100 | Mum Rimmon [10] |
| 439 | 102 | 100 | Mum Rimmon [10] |
| 440 | 102 | 100 | Mum Rimmon [10] |
| 441 | 102 | 100 | Mum Rimmon [10] |
| 442 | 102 | 100 | Mum Rimmon [10] |
| 443 | 102 | 100 | Mum Rimmon [10] |
| 444 | 102 | 100 | Mum Rimmon [10] |
| 445 | 102 | 100 | Mum Rimmon [10] |
| 446 | 102 | 100 | Mum Rimmon [10] |
| 447 | 102 | 100 | Mum Rimmon [10] |
| 448 | 103 | 100 | Shaman Oaf [10] |
| 449 | 103 | 100 | Shaman Oaf [10] |
| 450 | 103 | 100 | Shaman Oaf [10] |
| 451 | 103 | 100 | Shaman Oaf [10] |
| 452 | 103 | 100 | Shaman Oaf [10] |
| 453 | 103 | 100 | Shaman Oaf [10] |
| 454 | 103 | 100 | Shaman Oaf [10] |
| 455 | 103 | 100 | Shaman Oaf [10] |
| 456 | 103 | 100 | Shaman Oaf [10] |
| 457 | 103 | 100 | Shaman Oaf [10] |
| 458 | 59 | 70 | Dark Wolf [7] |
| 459 | 101 | 100 | Blood Wolfarch [11] |
| 460 | 59 | 70 | Blood Wolf [7] |
| 461 | 4 | 9 | Chief Soldier [1] |
| 462 | 4 | 9 | Chief Soldier [1] |
| 463 | 5 | 5 | Chief Dead Body [1] |
| 464 | 5 | 5 | Chief Dead Body [1] |
| 465 | 27 | 45 | Chief Warlock [4] |
| 466 | 6 | 7 | Chief Kid [1] |
| 467 | 40 | 50 | Chief Golemer [4] |
| 468 | 41 | 32 | Chief 32 Strider [3] |
| 469 | 42 | 19 | Chief Alcan [2] |
| 470 | 47 | 75 | Chief Chaos B [7] |
| 471 | 57 | 55 | Chief Dark Wing [5] |
| 472 | 60 | 25 | Chief Mutant [2] |
| 473 | 62 | 35 | Chief Estroider [3] |
| 474 | 64 | 28 | Chief Moderas [3] |
| 475 | 70 | 71 | Chief Dark Scr. [6] |
| 476 | 71 | 65 | Chief Chaos Kn. [6] |
| 477 | 71 | 65 | Chief Black Kn. [6] |
| 478 | 73 | 95 | Chief Lo. Pink [9] |
| 479 | 76 | 68 | Chief Hell Wiz. [6] |
| 480 | 88 | 100 | Chief Guardian [8] |
| 481 | 89 | 100 | Chief Chaos [8] |
| 482 | 104 | 1 | Christmas Tree |
| 483 | 105 | 110 | Dark Berith [11] |
| 484 | 105 | 110 | Dark Berith [11] |
| 485 | 105 | 110 | Dark Berith [11] |
| 486 | 105 | 110 | Dark Berith [11] |
| 487 | 105 | 110 | Dark Berith [11] |
| 488 | 105 | 110 | Dark Berith [11] |
| 489 | 105 | 110 | Dark Berith [11] |
| 490 | 105 | 110 | Dark Berith [11] |
| 491 | 105 | 110 | Dark Berith [11] |
| 492 | 105 | 110 | Dark Berith [11] |
| 493 | 106 | 140 | Lich Jel [14] |
| 494 | 106 | 140 | Lich Jel [14] |
| 495 | 106 | 140 | Lich Jel [14] |
| 496 | 106 | 140 | Lich Jel [14] |
| 497 | 106 | 140 | Lich Jel [14] |
| 498 | 106 | 140 | Lich Jel [14] |
| 499 | 106 | 140 | Lich Jel [14] |
| 500 | 106 | 140 | Lich Jel [14] |
| 501 | 106 | 140 | Lich Jel [14] |
| 502 | 106 | 140 | Lich Jel [14] |
| 503 | 107 | 118 | Mount Crag [12] |
| 504 | 108 | 112 | Giant Os [12] |
| 505 | 108 | 112 | Giant Os [12] |
| 506 | 108 | 112 | Giant Os [12] |
| 507 | 108 | 112 | Giant Os [12] |
| 508 | 108 | 112 | Giant Os [12] |
| 509 | 108 | 112 | Giant Os [12] |
| 510 | 108 | 112 | Giant Os [12] |
| 511 | 108 | 112 | Giant Os [12] |
| 512 | 108 | 112 | Giant Os [12] |
| 513 | 108 | 112 | Giant Os [12] |
| 526 | 123 | 2 | Armega Guard Shrine |
| 527 | 123 | 1 | Mihole Guard Shrine |
| 528 | 123 | 1 | Kiro Guard Shrine |
| 529 | 123 | 1 | Ini Guard Shrine |
| 530 | 123 | 1 | Gregori Guard Shrine |
| 531 | 123 | 1 | Concilia Guard Shrine |
| 532 | 123 | 1 | Legios Guard Shrine |
| 533 | 123 | 1 | Hillel Guard Shrine |
| 534 | 123 | 1 | Jave Guard Shrine |
| 535 | 123 | 1 | Nema Guard Shrine |
| 536 | 123 | 1 | Arosa Guard Shrine |
| 537 | 123 | 1 | Chaspa Guard Shrine |
| 538 | 124 | 1 | Armega Holy Shrine |
| 539 | 124 | 1 | Mihole Holy Shrine |
| 540 | 124 | 1 | Kiro Holy Shrine |
| 541 | 124 | 1 | Ini Holy Shrine |
| 542 | 124 | 1 | Gregori Holy Shrine |
| 543 | 124 | 1 | Concilia Holy Shrine |
| 544 | 124 | 1 | Legios Holy Shrine |
| 545 | 124 | 1 | Hillel Holy Shrine |
| 546 | 124 | 1 | Jave Holy Shrine |
| 547 | 124 | 1 | Nema Holy Shrine |
| 548 | 124 | 1 | Arosa Holy Shrine |
| 549 | 124 | 1 | Chaspa Holy Shrine |
| 560 | 86 | 1 | Praoroth Guard Shrine |
| 561 | 86 | 1 | Fafnir Guard Shrine |
| 562 | 86 | 1 | Arioch Guard Shrine |
| 563 | 86 | 1 | Immortality Guard Shrine |
| 564 | 5 | 5 | Chief Dead Body [1] |
| 565 | 8 | 8 | Chief Turning D [1] |
| 566 | 7 | 10 | Chief Turning S [1] |
| 567 | 6 | 12 | Chief Kid [1] |
| 568 | 59 | 12 | Chief Wolf [7] |
| 569 | 9 | 24 | Chief Captain [2] |
| 570 | 42 | 30 | Chief Alcan [2] |
| 571 | 69 | 32 | Chief IronTeeth [2] |
| 572 | 43 | 36 | Chief Red Eye [2] |
| 573 | 60 | 40 | Chief Mutant [2] |
| 574 | 64 | 46 | Chief Moderas [3] |
| 575 | 67 | 50 | Chief Vandaliz [3] |
| 576 | 41 | 54 | Chief 54 Strider [3] |
| 577 | 62 | 60 | Chief Estroider [3] |
| 578 | 61 | 66 | Chief Widows [3] |
| 579 | 48 | 70 | Chief Hoble [4] |
| 580 | 68 | 76 | Chief Big Fang [3] |
| 581 | 27 | 80 | Chief  Warlock [4] |
| 582 | 40 | 90 | Chief Golemer [4] |
| 583 | 57 | 100 | Chief Dark Wing [5] |
| 584 | 72 | 110 | Chief Cri. Slau [5] |
| 585 | 74 | 116 | Chief Reaper [5] |
| 586 | 71 | 120 | Chief Chaos K. [6] |
| 587 | 76 | 126 | Chief Hell Wiz. [6] |
| 588 | 70 | 132 | Chief Dark Scr [6] |
| 589 | 47 | 140 | Chief Chaos R [7] |
| 590 | 75 | 146 | Chief Hell Fie. [7] |
| 591 | 88 | 154 | Chief Guardian [11] |
| 592 | 89 | 162 | Chief L.Chaos [10] |
| 593 | 73 | 180 | Chief Lo. Brown [9] |
| 594 | 91 | 198 | Chief H.Fiend [10] |
| 595 | 90 | 198 | Chief Ch.Greed [10] |
| 596 | 92 | 198 | Chief Haze [10] |
| 597 | 103 | 200 | Chief Shaman [10] |
| 598 | 102 | 200 | Chief Rimmon [10] |
| 599 | 101 | 250 | Chief Wolfarch [10] |
| 600 | 105 | 210 | Chief Berith [11] |
| 601 | 108 | 224 | Chief Giant Os [12] |
| 602 | 107 | 236 | Chief  Crag [14] |
| 603 | 106 | 240 | Chief Lich Jel [14] |
| 604 | 132 | 103 | Dim Gargoyle [11] |
| 605 | 132 | 103 | Dim Gargoyle [11] |
| 606 | 132 | 103 | Dim Gargoyle [11] |
| 607 | 132 | 103 | Dim Gargoyle [11] |
| 608 | 132 | 103 | Dim Gargoyle [11] |
| 609 | 132 | 103 | Dim Gargoyle [11] |
| 610 | 132 | 103 | Dim Gargoyle [11] |
| 611 | 132 | 103 | Dim Gargoyle [11] |
| 612 | 132 | 103 | Dim Gargoyle [11] |
| 613 | 132 | 103 | Dim Gargoyle [11] |
| 614 | 133 | 128 | Volva Medusa [13] |
| 615 | 133 | 128 | Volva Medusa [13] |
| 616 | 133 | 128 | Volva Medusa [13] |
| 617 | 133 | 128 | Volva Medusa [13] |
| 618 | 133 | 128 | Volva Medusa [13] |
| 619 | 133 | 128 | Volva Medusa [13] |
| 620 | 133 | 128 | Volva Medusa [13] |
| 621 | 133 | 128 | Volva Medusa [13] |
| 622 | 133 | 128 | Volva Medusa [13] |
| 623 | 133 | 128 | Volva Medusa [13] |
| 624 | 134 | 135 | Ash Balog [14] |
| 625 | 134 | 135 | Ash Balog [14] |
| 626 | 134 | 135 | Ash Balog [14] |
| 627 | 134 | 135 | Ash Balog [14] |
| 628 | 134 | 135 | Ash Balog [14] |
| 629 | 134 | 135 | Ash Balog [14] |
| 630 | 134 | 135 | Ash Balog [14] |
| 631 | 134 | 135 | Ash Balog [14] |
| 632 | 134 | 135 | Ash Balog [14] |
| 633 | 134 | 135 | Ash Balog [14] |
| 640 | 6 | 12 | Quest Kid |
| 641 | 64 | 28 | Quest Moderas |
| 642 | 61 | 66 | Quest Widows |
| 643 | 27 | 80 | Quest Blood Warlock |
| 644 | 72 | 110 | Quest Crimson Slaughter |
| 645 | 47 | 140 | Quest Chaos Gurdian |
| 646 | 89 | 162 | Quest Lord Chaos |
| 647 | 88 | 154 | Quest Dark Guardian |
| 648 | 90 | 198 | Quest Chaos Greed |
| 649 | 101 | 200 | Quest Dun Wolfarch |
| 660 | 150 | 1 | Ore |
| 661 | 150 | 1 | Ore |
| 662 | 150 | 1 | Ore |
| 663 | 150 | 1 | Ore |
| 664 | 150 | 1 | Ore |
| 665 | 150 | 1 | Ore |
| 666 | 150 | 1 | Ore |
| 667 | 150 | 1 | Ore |
| 668 | 150 | 1 | Ore |
| 669 | 150 | 1 | Ore |
| 670 | 151 | 1 | Flag Pole |
| 672 | 153 | 1 | Sweeper Safe |
| 673 | 154 | 1 | Regen Zone Tower |
| 682 | 72 | 120 | Boss Crimson Slaughter |
| 683 | 89 | 140 | Boss Lord Chaos |
| 684 | 105 | 160 | Boss Dark Berith |
| 685 | 134 | 200 | Boss Ash Balog [15] |
| 686 | 8 | 220 | Boss Turning Dead |
| 687 | 163 | 1 | Junior WolfArch |
| 698 | 174 | 1 | Ground Elemental |
| 705 | 47 | 70 | Blue Chaos Guardian |
| 717 | 200 | 180 | Gilles de Rais |
| 718 | 192 | 135 | Blunt Crag [14] |
| 719 | 193 | 104 | Mutant Edger [11] |
| 720 | 194 | 117 | Bone Guardian [12] |
| 721 | 200 | 140 | Duplicated Gilles de Rais |
| 722 | 195 | 150 | Hymez Frozen Statue |
| 723 | 200 | 170 | Awakened Gilles de Rais |
| 724 | 2 | 200 | Vampire Test Model 1 |
| 725 | 2 | 200 | Vampire Test Model 2 |
| 726 | 196 | 200 | Castle Gate 1 |
| 727 | 197 | 200 | Castle Gate 2 |
| 728 | 198 | 200 | Castle Gate 3 |
| 729 | 199 | 200 | Castle Gate 4 |
| 733 | 205 | 140 | War Defender |
| 734 | 206 | 150 | Guild Tower |
| 735 | 0 | 200 | Slayer Guard |
| 736 | 131 | 150 | Vampire Guard |
| 737 | 142 | 200 | Ousters Guard |
| 738 | 207 | 1 | Pleasure Station |
| 739 | 208 | 1 | Land Mine |
| 740 | 212 | 1 | Claymore |
| 741 | 210 | 1 | Auto Turret |
| 743 | 213 | 1 | Drum |
| 744 | 214 | 1 | Tripod A |
| 745 | 215 | 1 | Tripod B |
| 746 | 216 | 1 | Tripod C |
| 747 | 217 | 1 | Obstacle A |
| 748 | 218 | 1 | Obstacle B |
| 753 | 219 | 1 | Gore Gland |
| 754 | 205 | 142 | Rum Guarder [14] |
| 755 | 220 | 146 | Icy Ruffian [14] |
| 756 | 220 | 146 | Icy Ruffian [14] |
| 757 | 220 | 146 | Icy Ruffian [14] |
| 758 | 220 | 146 | Icy Ruffian [14] |
| 759 | 220 | 146 | Icy Ruffian [14] |
| 760 | 220 | 146 | Icy Ruffian [14] |
| 761 | 220 | 146 | Icy Ruffian [14] |
| 762 | 220 | 146 | Icy Ruffian [14] |
| 763 | 220 | 146 | Icy Ruffian [14] |
| 764 | 228 | 230 | Great Ruffian |
| 765 | 229 | 250 | Great Ruffian Skull |
| 768 | 191 | 1 | Miga |
| 769 | 232 | 102 | Flieger [11] |
| 770 | 233 | 102 | Gefreiter [11] |
| 771 | 234 | 185 | Trasla [14] |
| 772 | 235 | 194 | Pusca [14] |
| 774 | 237 | 177 | Nod Copila [14] |
| 775 | 238 | 165 | Razor [14] |
| 777 | 240 | 96 | Tug Leg [11] |
| 778 | 240 | 132 | Tug Legger [14] |
| 779 | 241 | 148 | Roi Cadavru [14] |
| 780 | 242 | 115 | Siamese [12] |
| 781 | 243 | 124 | Lunga Testa [13] |
| 782 | 244 | 93 | Oberschutze [10] |
| 783 | 244 | 93 | Oberschutze [10] |
| 784 | 245 | 86 | Sturmmann [10] |
| 785 | 246 | 115 | Hauptmann [12] |
| 786 | 246 | 133 | Oberst [14] |
| 790 | 205 | 120 | War Defender Black |
| 791 | 205 | 120 | War Defender Red |
| 792 | 247 | 1 | Sealing of Reason |
| 793 | 0 | 1 | Sealing of Reason |
| 794 | 131 | 1 | Sealing of Reason |
| 795 | 142 | 1 | Sealing of Reason |
| 796 | 0 | 100 | Mono Slayer M |
| 797 | 1 | 100 | Mono Slayer F |
| 798 | 131 | 100 | Mono Vampire M |
| 799 | 111 | 100 | Mono Vampire F |
| 800 | 142 | 100 | Mono Ousters |
| 801 | 220 | 146 | Pinguin |
| 802 | 220 | 146 | Military Bear |
| 803 | 220 | 146 | Gargoyle |
| 814 | 265 | 350 | Cerberus [14] |
| 815 | 266 | 350 | Manticoret [14] |
| 816 | 267 | 350 | BogletH [15] |
| 817 | 268 | 200 | BogletB  [15] |
| 818 | 269 | 200 | Massacre [14] |
| 819 | 270 | 100 | Plumpy Boar [14] |
| 820 | 271 | 160 | Cabracam [14] |
| 824 | 265 | 350 | Cerberus [14] |
| 825 | 267 | 350 | Manticoret [14] |
| 836 | 133 | 146 | Chief Medusa [14] |
| 837 | 134 | 146 | Chief Balog [14] |
| 838 | 271 | 158 | Cabracam [11+20%] |
| 839 | 132 | 146 | Chief Bat [14] |
| 840 | 200 | 200 | Ninja  [15] |
| 841 | 200 | 146 | test1 [14] |
| 845 | 285 | 140 | Morgoth [14+20%] |
| 850 | 229 | 250 | Poisoned Ruffian Skull |
