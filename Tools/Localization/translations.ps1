# translations.ps1 - index -> English for Data\Info\String.inf
#
# Rules followed throughout:
#  * printf specifiers (%d %s %02d ...) are preserved in the SAME ORDER as the
#    Korean, because the client passes arguments positionally. Where English
#    word order would reorder them, the sentence is rephrased instead.
#  * proper nouns are left alone (Slayer, Vampire, Ousters, place names).
#  * stats read as bare HP / MP / STR / DEX / INT - not spelled out.
#  * the old darkeden.com website and support address are cut, not carried
#    over; the sentence is reworded rather than left with a dead contact.
#  * Korean has paired variants of many lines that differ only by the subject
#    particle (-ga / -i). Both map to the same English string; that is expected.

$TRANSLATIONS = @{

# --- connection / session -------------------------------------------------
0  = "Your connection quality is poor."
1  = "You can revive in %d seconds."

# --- pure format strings: leave exactly as they are ------------------------
# 2,3,4,5 are %s (%d,%d) / %d/%d/%d / %02d:%02d:%02d / %s(%d)

# --- account creation -----------------------------------------------------
6  = "New user registration is not available."
7  = "You can register on the website."
8  = "A required field has not been filled in."
9  = "That ID is not valid."
10 = "An ID must be %d-%d characters long."
11 = "Please remove special characters from the ID."
12 = "A password must be %d-%d characters long."
13 = "Please remove special characters from the password."
14 = "A password cannot be numbers only."
15 = "A name can be up to %d characters long."
16 = "That registration number is not valid."
17 = "Registration number format: 123456-1234567"

# --- shop / inventory / storage -------------------------------------------
18 = "There is no empty slot."
19 = "You do not have enough money."
20 = "You do not have that item."
21 = "This cannot be sold."
22 = "This cannot be repaired."
23 = "This cannot be silver-plated."
24 = "You cannot buy any more."
25 = "This cannot be placed in storage."
26 = "Storage purchased."
27 = "You do not have any storage."

# --- trading --------------------------------------------------------------
28 = "The trade was refused."
29 = "There is no one to trade with."
30 = "You cannot trade while riding a motorcycle."
31 = "You can only trade inside a safe zone."
32 = "You cannot exchange in your current state."
33 = "You cannot trade."
34 = "You are already trading."
35 = "There is not enough space to exchange."

# --- skills ---------------------------------------------------------------
36 = "That is a different skill domain."
37 = "The skill level is too high."
38 = "You cannot learn this yet."
39 = "This skill is not supported yet."
40 = "I do not know where it is."
41 = "You do not have a motorcycle key."
42 = "In %s, at (%d, %d)."
43 = "You cannot use bonus points."
44 = "Which of the %s skills would you like to learn?"
45 = "There are no skills you can learn right now."
46 = "You can learn a new skill."
47 = "Your %s domain level is now %d."
48 = "Your %s domain level is now %d."

# --- relics ---------------------------------------------------------------
49 = "You cannot enter your own safe zone while carrying a relic!"

# --- team (Slayer guild) registration NPC ---------------------------------
50 = "Let me see now. It says here you already belong to another team."
51 = "You left another team only recently. Think it over more carefully."
52 = "Your team was disbanded only recently. Build yourself up to meet the requirements, and watch for the right moment."
53 = "Impressive, but you lack the makings of a leader. Go and hone your skills."
54 = "Founding a team takes a great deal of money. You do not appear to have it."
55 = "%s, is it? I have never heard that name, which tells me you are a novice. Hone your skills and come back."
56 = "That team name is already taken. Think of another."
57 = "Your application was refused."
58 = "You already belong to another team."
59 = "You left another team only recently. Think it over more carefully."
60 = "Your team was disbanded only recently. Build yourself up to meet the conditions, and watch for the right moment."
61 = "You still have a great deal to learn. Hone your skills and come back."
62 = "%s, you need more money to register a team."
63 = "%s, is it? I have never heard that name, which tells me you are a novice. Hone your skills and come back."
64 = "Your application was refused."

# --- clan (Vampire guild) registration NPC --------------------------------
65 = "Let me see now. It says here you have already sworn yourself to another clan."
66 = "You left another clan only recently. Moving about so freely does you no credit. Be careful."
67 = "Your clan was dissolved only recently. Watch for the right moment."
68 = "Impressive, but you lack the makings of a chief. Go and hone your skills."
69 = "Registering a clan takes a great deal of money. You do not appear to have it."
70 = "%s, is it? You must still be a young vampire. Drink more blood and come back."
71 = "That clan name is already taken. Think of another."
72 = "Your application was refused."
73 = "You already belong to another clan."
74 = "You left another clan only recently. Moving about so freely does you no credit. Be careful."
75 = "Your clan was dissolved only recently. Watch for the right moment."
76 = "You lack the makings of a worthy aide. Go and train further."
77 = "However great your skill, a clan without the money to sustain it will soon collapse."
78 = "%s, is it? I have never heard that name, which tells me you are a novice. Hone your skills and come back."
79 = "Your application was refused."

# --- character stats ------------------------------------------------------
80 = "Some fields have not been filled in."
81 = "Your maximum HP is now %d."
82 = "Your maximum HP is now %d."
83 = "Your maximum MP is now %d."
84 = "Your maximum MP is now %d."
85 = "Your Strength (STR) is now %d."
86 = "Your Strength (STR) is now %d."
87 = "Your Dexterity (DEX) is now %d."
88 = "Your Dexterity (DEX) is now %d."
89 = "Your Intelligence (INT) is now %d."


# --- BATCH 2: login / account / chat / party / shop UI --------------------
90  = "Your Intelligence (INT) is now %d."
91  = "You are now level %d."
92  = "You learned the [%s] skill."
93  = "Your alignment changed to %s."
94  = "Your alignment changed to %s."
95  = "Your alignment has worsened."
96  = "Your alignment has improved."

# login / account
97  = "The ID or password is incorrect."
98  = "You are already logged in."
99  = "That ID is already registered."
100 = "That registration number is already registered."
101 = "No ID was entered."
102 = "The ID is too short."
103 = "No password was entered."
104 = "The password is too short."
105 = "No name was entered."
106 = "No registration number was entered."
107 = "The registration number is incorrect."
108 = "No such player."
109 = "No such ID."
110 = "This account is in an abnormal state. Please contact customer support."
111 = "That is not valid."
112 = "This account is in an abnormal state. Please contact customer support."
113 = "Your subscription has expired. Please contact customer support."
114 = "The server is under maintenance. Please wait a moment."

# chat / whisper
115 = "The item broke."
116 = "Your whisper was not delivered."
117 = "You cannot whisper to yourself."
118 = "You are now blocking messages from %s."
119 = "You are now allowing messages from %s."
120 = "You are now blocking all messages."
121 = "You are now allowing all messages."
122 = "Please keep it civil. :)"
123 = "All messages will be shown exactly as written."
124 = "Offensive language will be filtered out."
125 = "You cannot log out while dead."
126 = "You cannot shout right now."
127 = "Please wait a moment."
128 = "Connecting to the server."

# donation / invitation / party
129 = "You made a donation."
130 = "You cannot donate."
131 = "Your invitation was refused."
132 = "There is no one to invite."
133 = "You can only do that inside a safe zone."
134 = "You cannot send an invitation."
135 = "You are of different races."
136 = "You cannot do that while transformed."
137 = "You must wait one hour after joining a party."
138 = "You cannot form a party."
139 = "You expelled %s from the party."
140 = "%s expelled you from the party."
141 = "%s expelled %s from the party."
142 = "The party has been disbanded."
143 = "%s left the party."
144 = "You left the party."
145 = "You already belong to another party."
146 = "The party is full."
147 = "%s joined the party."
148 = "You will be logged out in %d seconds."

# shop / repair / enchant
149 = "You do not have enough stars."
150 = "You cannot buy that."
151 = "You can register."
152 = "Press CTRL+H for help."
153 = "You can get a basic weapon from Zach at the Field Headquarters."
154 = "   Going to the character selection screen.     Please wait."
155 = "This cannot be enchanted."
156 = "You must hold only one at a time."
157 = "This can be enchanted."
158 = "Do you want to sell this item?"
159 = "Do you want to sell it?"
160 = 'That comes to $%s.'
161 = "Do you want to repair it?"
162 = "Click the item you want to trade."
163 = "Click the item you want to repair."
164 = "Click OK when you are finished."
165 = "Repair this item?"
166 = "Recharge this item?"
167 = "Silver-plate this item?"
168 = "Click the item you want silver-plated."

# window options / equip / misc
169 = "Windows will be shown semi-transparent."
170 = "Windows will not be shown semi-transparent."
171 = "This can be equipped."
172 = "This cannot be equipped."
173 = "Drop money"
174 = "View item description"
175 = "Store money"
176 = "You have a party invitation."
177 = "You have a party join request."
178 = "You will revive at the designated location."
179 = "You will be transported to the designated location."
180 = "You cannot level up any further."
181 = "Your stats cannot increase any further."
182 = "Join"
183 = "Tip: right-click to sell all vampire heads at once."
184 = "Tip: right-click to repair all your equipment at once."
185 = "Auto-hide on"
186 = "Auto-hide off"
187 = "Game Menu"
188 = "Info"
189 = "Community"


# --- BATCH 3: window titles, tooltips, chat modes, equip slots -------------
190 = "Team"
191 = "Shop"
192 = "Help"
193 = "Inventory"
194 = "Gear"
195 = "Character Info"
196 = "Party"
197 = "Quest"
198 = "Team Info"
199 = "Team Member List"
200 = "Basic Help"
201 = "Chat Help"
202 = "Combat Help"
203 = "Skill Help"
204 = "Team Help"
205 = "Clan"
206 = "Clan Info"
207 = "Clan Member List"
208 = "Clan Help"
209 = "Magic Help"

# experience readout - the Korean pads these so the colons line up, so the
# English is padded to a common width for the same reason. Trailing space kept.
210 = "Current EXP : "
211 = "Next Level  : "
212 = "EXP to Next : "

# equip slot tooltips
213 = "Equip a hat"
214 = "Equip a necklace"
215 = "Equip armor"
216 = "Equip a shield"
217 = "Equip a weapon"
218 = "Equip gloves"
219 = "Equip a belt"
220 = "Equip trousers"
221 = "Equip a bracelet"
222 = "Equip a ring"
223 = "Equip shoes"
224 = "Equip clothing"
225 = "Equip earrings"
226 = "Equip an amulet"
227 = "First weapon set"
228 = "Second weapon set"

# chat bar controls
229 = "Special characters"
230 = "Set text color"
231 = "Toggle Korean/English"
232 = "Show recent whisper IDs"
233 = "Send normal chat"
234 = "Send zone chat"
235 = "Send whisper"
236 = "Send party chat"
237 = "Send team chat"
238 = "Show normal chat"
239 = "Show zone chat"
240 = "Show whispers"
241 = "Show party chat"
242 = "Show team chat"
243 = "Hide normal chat"
244 = "Hide zone chat"
245 = "Hide whispers"
246 = "Hide party chat"
247 = "Hide team chat"
248 = "Hide clan chat"
249 = "Show clan chat"
250 = "Send clan chat"

# team / clan membership
251 = "Leave"
252 = "Expel"
253 = "Block invitations"
254 = "Allow invitations"
255 = "Block join requests"
256 = "Allow join requests"

# stat buttons
257 = "Increase Strength"
258 = "Increase Dexterity"
259 = "Increase Intelligence"

# window open tooltips
260 = "View the skill window"
261 = "View the character window"
262 = "View the magic window"
263 = "View the class change window"

# skill / magic domains
264 = "View Blade domain info"
265 = "View Sword domain info"
266 = "View Gun domain info"
267 = "View Healing domain info"
268 = "View Blessing domain info"
269 = "View all domain info"
270 = "View Poison domain info"
271 = "View Acid domain info"
272 = "View Curse domain info"
273 = "View Summoning domain info"
274 = "View Blood domain info"
275 = "View Unique domain info"

# per-window help tooltips
276 = "View help for the magic window"
277 = "View help for the skill window"
278 = "View help for the Inventory window"
279 = "View help for the Party window"
280 = "View help for the character window"
281 = "View help for the Gear window"
282 = "View help for the Storage window"
283 = "View help for the Shop window"
284 = "View help for the Exchange window"

# close tooltips
285 = "Close the Inventory window"
286 = "Close the Party window"
287 = "Close the character window"
288 = "Close the Gear window"
289 = "Close the magic window"
290 = "Close the skill window"
291 = "Close the description window"
292 = "Close the Storage window"
# NOTE: the Korean for 293 reads "Gear(Shop)" - a typo in the original data.
# It is the Shop close button, so it is translated by function, not literally.
293 = "Close the Shop window"
294 = "Close the bookshelf"
295 = "Close the book"

296 = "No team registered"
297 = "No clan registered"
298 = "Infrared Scanning Helmet"
299 = "Infra Scanning Helmet"


# --- BATCH 4: stats, status bars, guild list UI, place names --------------
# 303-306 (STR/DEX/INT/GM), 333 (Passive), 393-399 (X:%d Y:%d, F1-F5) are
# already English in the source and are deliberately left untouched.
300 = "Shut down the computer"
301 = "View the next page"
302 = "View the previous page"
307 = "Please do not spam!!!"
308 = "Help"

# stat names
309 = "Strength"
310 = "Dexterity"
311 = "Intelligence"
312 = "HP"
313 = "MP"
314 = "Accuracy"
315 = "Damage"
316 = "Defense"
317 = "Protection"
318 = "Alignment"
319 = "Very Evil"
320 = "Evil"
321 = "Neutral"
322 = "Good"
323 = "Very Good"

# base-stat readout - the Korean pads the labels so the colons align, so the
# English labels are padded to a common 12-character width for the same reason
324 = "Base STR     : %d"
325 = "Base DEX     : %d"
326 = "Base INT     : %d"
327 = "Base total   : %d"
328 = "Stat total   : %d"

329 = "Slow"
330 = "Normal"
331 = "Fast"
332 = "Attack speed : %s[%d]"
334 = "Passive"

# status bars
335 = "Level :%d"
336 = "EXP:%s/%s (remaining:%s)"
337 = "MP:%d/%d"
338 = "HP:%d/%d(S:%d)"
339 = "HP:%d/%d"

# vampire infection countdown
340 = "You will become a vampire in %d days %d hours %d minutes"
341 = "You will become a vampire in %d hours %d minutes"
342 = "You will become a vampire in %d minutes"
343 = "You will become a vampire soon"

# HP bar layout options
344 = "Show the HP bar vertically"
345 = "Show the HP bar small"
346 = "Show the HP bar horizontally"
347 = "Show the HP bar large"
348 = "Show horizontally"
349 = "Show vertically"
350 = "View help"
351 = "Close the window"
352 = "Register"

# guild / clan browser
353 = "Scroll up"
354 = "Scroll down"
355 = "Refresh the list"
356 = "Sort by team name"
357 = "Sort by leader name"
358 = "Sort by expiry date"
359 = "Sort by member count"
360 = "Sort by rank"
361 = "Change search method"
362 = "Search"
363 = "Master"
364 = "Sub-master"
365 = "Pending applicant"
366 = "Member"

# guild / clan detail labels. The Korean carries an English gloss in
# parentheses; with the label itself in English the gloss is redundant.
367 = "Grade : %s"
368 = "Name : %s"
369 = "Leader : %s"
370 = 'Reg. Fee : $%s'
371 = "Members : "
372 = "Introduction : "
373 = "Clan Introduction : "
374 = "Team Introduction : "
375 = "Ranking : %d"
376 = "Team Name : %s"
377 = "Clan Name : %s"
378 = 'Registration Fee : $%s'
379 = "Self Introduction : "

380 = "Up"
381 = "Down"
382 = "Expel"
383 = "Approve"
384 = "Reject"
385 = "Cancel"

# place names - proper nouns. "Limbo Castle" matches the spelling already used
# by the English quest text shipped in the dpk.
386 = "Limbo Castle"
387 = "Eslanian"
388 = "Mt. Rodin"
389 = "Drobeta"
390 = "Perona Highway"
391 = "Lake Timor"
392 = "Branco"


# --- BATCH 5: weapon types, item stat labels, shop and exchange dialogs ----
# 400-422 (F6-F12, ESC, SKILL, INVENTORY, GEAR, ...) are already English and
# are left untouched.

# weapon categories. The Korean already carries the English name in
# parentheses, so the parenthetical is dropped except where the abbreviation
# is what actually appears in item text.
423 = "Sword"
424 = "Blade"
425 = "Cross"
426 = "Mace"
427 = "Mine"
428 = "Bomb"
429 = "Mine Material"
430 = "Bomb Material"
431 = "Shotgun (SG)"
432 = "Submachine Gun (SMG)"
433 = "Assault Rifle (AR)"
434 = "Sniper Rifle (SR)"

# item detail labels - trailing " : " is significant, the value is appended
435 = "Type : "
436 = "Durability : "
437 = "Silver Plating : "
438 = "Damage : "
439 = "Critical Hit : "
440 = "Defense : "
441 = "Protection : "
442 = "Magic Defense : "
443 = "Accuracy : "
444 = "HP : "
445 = "MP : "
446 = "Range : "
447 = "Ammo : "
448 = "Pockets : "
449 = "Item Count : "
450 = "Uses Remaining : "
451 = "Destination : "
452 = "None"

# counter words - these are appended directly after a number
453 = "pcs"
454 = "rounds"
455 = "slots"
456 = "Party"

457 = "Options : "
458 = "Requirements : "
459 = "%d or higher"
460 = "Male only"
461 = "Female only"
462 = "Slayer only"
463 = "Vampire only"
464 = "Ousters only"
465 = "Total stats "
466 = "Level "
467 = "Price : "
468 = "Silver Plating Price : "
469 = "Recharge Price : "
470 = "Repair Price : "
471 = "HP Cost : "
472 = "MP Cost : "
473 = "Required Level : "
474 = "EXP : "
475 = "Growth Limit Level : "

# these two carry literal double quotes in the source data - preserved
476 = '"You cannot learn this yet."'
477 = '"You can learn this."'

# elevator / movement
478 = "Move"
479 = "Cancel movement"
480 = "Go to floor 1"
481 = "Go to floor 2"
482 = "Go to floor 3"
483 = "Go to floor 4"
484 = "Go to basement 1"

# exchange window
485 = "Press to exchange"
486 = "Cancel your OK"
487 = "Cancel the items you offered"
488 = "Take back the money you offered"
489 = "Exchange money"
490 = "Money the other party has offered"
491 = "Amount remaining after the exchange"
492 = "Amount to exchange"
493 = "Enter the amount to drop."
494 = "Enter the amount to store."
495 = "Enter the amount to withdraw."
496 = "Enter the amount to trade."
497 = "Enter the amount to take out."
498 = "Do you want to buy this item?"

# the gap in 499 is where the client draws the quantity, so the run of
# spaces is load-bearing and is kept at the same width
499 = "Buy            of this item?"


# --- BATCH 6: item detail lines, character creation, monsters, server status
500 = 'Buy storage for $%d?'
501 = "Do you want to trade with %s?"
502 = "Waiting for a reply from %s."
503 = "Press Cancel to abort."
504 = "%s is requesting to join your %s."
505 = "%s has invited you to %s."
506 = "No search results found."
507 = "Do you want to enchant this item?"

# indented item detail lines - the leading tab is significant
508 = "`tType : SG"
509 = "`tType : SMG"
510 = "`tType : AR"
511 = "`tType : SR"
512 = "`tDurability : %d"
513 = "`tSilver Plating : %d"
514 = "`tDamage : %d~%d"
515 = "`tCritical Hit : %d"
516 = "`tDefense : %d"
517 = "`tProtection : %d"
518 = "`tAccuracy : %d"
519 = "`tHP : +%d"
520 = "`tMP : +%d"
521 = "`tRange : %d slots"
522 = "`tAmmo : %d rounds"
523 = "`tPockets : %d"
524 = "`tOptions : %s +%d"
525 = "`t       %s +%d"
# 526 is tab + spaces only - left exactly as it is
527 = "`tRequirements : "
528 = "STR %d or higher"
529 = "DEX %d or higher"
530 = "INT %d or higher"
531 = "Total stats %d or higher"
532 = "Level %d or higher"
533 = "`tPrice : %s"

# file / profile pickers
534 = "Select a picture for your profile."
535 = "Select the files to send (CTRL for multiple)."
536 = "Select this file"
537 = "Cancel and close the window"
# 538-542 (BLADE, SWORD, ENCHANT, GUN, HEAL) are already English
543 = "This menu is not supported yet."

# login and character creation
544 = "You did not enter an ID or password."
545 = "The registration number entered is not valid."
546 = "Please enter a name."
547 = "Cannot connect to the server."
548 = "Please select a character."
549 = "The character was deleted."
550 = "You must create a new character and then select it."
551 = "You cannot create any more characters."
552 = "Character creation failed."
553 = "Not all required fields have been filled in."
554 = "That ID is already in use."
555 = "That ID is available."
556 = "Please re-enter the password."

# monster names - taken from the EName column of the MonsterInfo table so they
# match the server. 570 and 576 are stored truncated there ("Crimson Slaugh.",
# "Chaos Guardi") and are spelled out in full here. 564, 579 and 581 have no
# DB row and are transliterated.
557 = "Turning Dead"
558 = "Arkhan"
559 = "Estroider"
560 = "Golemer"
561 = "Dark Screamer"
562 = "Dead Body"
563 = "Moderas"
564 = "Vandalizer"
565 = "Dirty Strider"
566 = "Hell Wizard"
567 = "Turning Soul"
568 = "Iron Teeth"
569 = "Red Eye"
570 = "Crimson Slaughter"
571 = "Hell Guardian"
572 = "Soldier"
573 = "Ripper"
574 = "Big Fang"
575 = "Lord Chaos"
576 = "Chaos Guardian"
577 = "Hobble"
578 = "Chaos Knight"
579 = "Widows"
580 = "Kid"
581 = "Shadow Wing"

# server status
582 = "Excellent"
583 = "Good"
584 = "Smooth"
585 = "Normal"
586 = "Another server recommended"
587 = "Server down"
588 = "Open"
589 = "Closed"

# item classes and storage
590 = "Normal item"
591 = "Special item"
592 = "Unknown item"
593 = "First storage"
594 = "Second storage"
595 = "Third storage"
596 = "Fourth storage"
597 = "Fifth storage"
598 = "Withdraw money"
599 = "Delete"


# --- BATCH 7: character sheet, game options, rank ladder ------------------
600 = "Cancel"
601 = "Do you really want to delete this character?"
602 = "Please enter the registration number correctly."

# character sheet labels - trailing " : " is significant
603 = "Name : "
604 = "Level : "
605 = "Base STR : "
606 = "Base DEX : "
607 = "Base INT : "
608 = "Sword domain level : "
609 = "Blade domain level : "
610 = "Gun domain level : "
611 = "Healing domain level : "
612 = "Blessing domain level : "
613 = "Fame : "
614 = "Press Create to make a"
615 = "new character."
616 = "Rank : "
617 = "Rank EXP : "

# game options
618 = "Enter chat"
619 = "Normal chat"
620 = "Use 3D acceleration"
621 = "Transparent HP/MP bar"
622 = "Bleed (when HP is below 30%)"
623 = "Smooth window auto-hide"
624 = "Game brightness"
625 = "Show chat in speech bubbles"
626 = "Show FPS"
627 = "Make main windows semi-transparent"
628 = "Transparency level"
629 = "Sound effect volume"
630 = "Background music volume"
631 = "Show beginner help"
632 = "Filter offensive language"
633 = "Preload monster images when changing maps"
634 = "Show all chat in white"
635 = "Use teen version"
636 = "Open the chat window on whisper"
637 = "Press the new shortcut key."
638 = "Press ESC to cancel."
639 = "Hide my character info"

# --- rank ladder ---------------------------------------------------------
# There are no English rank names anywhere on the server (RankEXPInfo holds
# only numeric EXP thresholds), so these come from the Korean phonetics.
#
# 650-659 are a coherent German noble progression and are confident:
#   Ritter -> Reichsritter -> Baronet -> Freiherr -> Graf -> Markgraf ->
#   Pfalzgraf -> Fuerst -> Herzog -> Landesherr
#
# 640-649 are a stylised military ladder. Private, Sergeant and Marshal are
# clear; 642 / 644 / 646-648 are best-effort readings of the Korean and are
# the ones to correct if the community already uses other names.
640 = "Private"
641 = "Sergeant"
642 = "Ficel"
643 = "Lieutenant"
644 = "Colonel"
645 = "General"
646 = "Fore General"
647 = "Majoris General"
648 = "Cloel General"
649 = "Marshal"
650 = "Ritter"
651 = "Reichsritter"
652 = "Baronet"
653 = "Freiherr"
654 = "Graf"
655 = "Markgraf"
656 = "Pfalzgraf"
657 = "Fuerst"
658 = "Herzog"
659 = "Landesherr"

660 = "Version"
661 = "Netmarble version"

662 = "Base STR : "
663 = "Base DEX : "
664 = "Base INT : "
665 = "Current STR : "
666 = "Current DEX : "
667 = "Current INT : "
668 = "Fame"
669 = "Team Name : "
670 = "Clan Name : "
671 = "You can change the picture"
672 = "You have been promoted."
673 = "Rank Name : "
674 = "Rank Level : "
# 675-679 (Blade, Sword, Enchant, Gun, Heal) are already English
680 = "Type"

681 = "You must be a premium user, and this cannot be used inside a guild."
682 = "You must be a premium user, and this cannot be used inside a town."
683 = "You will be expelled in %d seconds."
684 = "Change the introduction text."
685 = "Start tracking"
686 = "Cancel tracking"
687 = "Tracking character %s"
688 = "Failed to track character %s"
689 = "Hide war-related messages"


# --- BATCH 8: rank bonuses, skill learning, events, castle tax ------------
690 = "Hide lair master messages"
691 = "View the lower rank skill window"
692 = "View the higher rank skill window"

# rank bonus / item option effects. The Korean carries an English gloss in
# parentheses; with the term itself in English the gloss is redundant. These
# glosses are also the source of the Defense/Protection naming used throughout.
693 = "Increased Critical attack power"
694 = "Increased Defense"
695 = "Increased To hit"
696 = "Increased HP"
697 = "Increased MP"
698 = "Increased Damage"
699 = "Increased attack speed"
700 = "Increased HP"
701 = "Increased Defense"
702 = "Increased Protection"
703 = "Reduced HP cost when using skills"
704 = "Increased damage from Enchant attack skills"
705 = "Increased damage from Heal attack skills"
706 = "Increased damage from melee attack skills"
707 = "Increased HP recovery rate"
708 = "Increased Acid resistance"
709 = "Increased Blood resistance"
710 = "Increased Curse resistance"
711 = "Increased Poison resistance"
712 = "Increased damage from Storm skills"
713 = "Increased range of Storm skills"
714 = "Increased success rate of Poison skills"
715 = "Increased success rate of Acid skills"
716 = "Increased success rate of Curse skills"
717 = "Increased success rate of Blood skills"
718 = "Increased success rate of Innate skills"
719 = "Increased success rate of Summon skills"
720 = "Reduced MP cost when using skills"
721 = "Increased HP steal"
722 = "Increased MP steal"
723 = "Increased Luck"
724 = "Increased Acid Swamp duration"
725 = "Increased Paralyze duration"
726 = "Increased Darkness duration"
727 = "Increased Darkness range"

728 = "Your rank cannot increase any further."

# billing
729 = "You cannot play because this is not a paid account."
730 = "Your payment information has not been confirmed yet. Please wait a moment."
731 = "Your character has reached the free service limit. A paid service is required to connect."

# skill learning - these carry literal double quotes and trailing padding in
# the source, both preserved
732 = '"You cannot learn this skill."'
733 = '"You have already learned this skill."   '
734 = '"You cannot learn this yet."  '
735 = '"You can learn this now."  '
# 736-737 (GRADE1, GRADE2) are already English
738 = "If you learn this skill you will not be able to learn the other rank skill at your current rank. Are you sure?"

# christmas tree event
739 = "Use the tree."
740 = "Cancel using the tree."
741 = "Merry Christmas~*"
742 = "Get a present from your friends and come back."
743 = "Greedy thing! Be off with you!"
744 = "This is too close to another tree."

745 = "Some fields are empty. Please fill in every field."
746 = "This cannot be used in a safe zone."
747 = "This cannot be used inside a town or a guild."
748 = "The item may break if this fails."
749 = "You cannot store more than 2 billion."
750 = "You cannot carry more than 2 billion."

751 = "In this zone you can buy ampoules at half price."
752 = "In this zone you can buy serum at half price."
753 = "The half-price ampoule event has ended."
754 = "The half-price serum event has ended."
755 = "You received your reward."
756 = "You cannot receive the reward."
757 = "There is no empty slot."
758 = "Hide messages about Adam's Sanctuary"

# castle tax
759 = "Total tax"
760 = "Tax to collect"
761 = "Total tax available to collect"
762 = "Enter the amount of tax to collect"
763 = "Click to enter the amount of tax to collect"
764 = "Collect the amount entered"
765 = "You do not belong to a team."
766 = "You do not belong to a clan."
767 = "You are not the team master."
768 = "You are not the clan master."
769 = "Your team does not own a castle."
770 = "Your clan does not own a castle."
771 = "This castle does not belong to your team."
772 = "This castle does not belong to your clan."
773 = "Tax collected."
774 = "Failed to collect the tax."
# 775 has a leading space in the source - kept
775 = " The master of the team or clan that owns this castle may collect the tax it earns."
776 = "The tax you collect plus the money you carry cannot exceed 2 billion."

777 = "Race war"
778 = "The war schedule is full."
779 = "You have already applied for a war."


# --- BATCH 9: war, relics, race war, couple event -------------------------
780 = "You do not have enough money."
781 = "You have been added to the war schedule."
782 = "You cannot enter your own safe zone while carrying the Blood Bible!"
783 = "You already own a castle."
784 = "You cannot apply for a war."
785 = "%d hours %d minutes"
786 = "Time remaining"
787 = "Civil war"

# relic bonuses
788 = "MP or HP cost when using skills reduced by 50%"
789 = "Luck +10"
790 = "INT +7, DEX +7"
791 = "Physical attack damage +10"
792 = "Sight +5, all stats +4"
793 = "All resistances +9"
794 = "Magic attack damage +10"
795 = "Translates the other race's language"
796 = "Gambling prices reduced by 50%"
797 = "Potion prices reduced by 50%"
798 = "HP +50"
799 = "STR +7, INT +7"

# relic names. Indices 812-823 already hold these same names in upper case
# (ARMEGA, MIHOLE, ...), so the spellings come from the data, not from me.
800 = "Armega"
801 = "Mihole"
802 = "Kiro"
803 = "Ini"
804 = "Gregori"
805 = "Concilia"
806 = "Legios"
807 = "Hillel"
808 = "Jave"
809 = "Nema"
810 = "Arosa"
811 = "Chaspa"

# relic status
824 = "Lying on the ground"
825 = "Held by a Slayer"
826 = "Held by a Vampire"
827 = "No information available"
828 = "In the Slayer guardian shrine"
829 = "In the Vampire guardian shrine"
830 = "Location : "
831 = "Status : "
832 = "Holder : "
833 = "Attack"
834 = "Defense"

# race war
835 = "The race war roster for %s's level range is full."
836 = "You have applied to join the race war."
837 = "Last owner : "
838 = "Slayer"
839 = "Vampire"
840 = "Race wars can only be applied for and joined on the first server of each world."

# event items
841 = "You cannot receive the event item right now."
842 = "You cannot receive the event item."
843 = "You received the event item."
844 = "Only premium service users can receive this."

# couple event
845 = "You are now a couple. The couple item has been added to your inventory."
846 = "The couple could not be formed."
847 = "The request timed out and was cancelled."
848 = "You have broken up."
849 = "You cannot break up right now."
850 = "The request timed out and was cancelled."

# 851, 852 and 855 carry real line breaks in the source; the same break
# positions are kept here using `n
851 = "A couple must be formed by mutual agreement. `nTo apply, enter the name of the partner you wish to pair with. If that partner comes to me and agrees within one minute, the couple is formed. Please remember this.`nNow, please enter the name of the person you wish to be paired with."
852 = "A mutual separation must be agreed by both sides. Enter the name of the partner you wish to separate from, and if that partner comes to me and agrees within one minute, the separation takes effect. When you separate, the couple ring that symbolises your love will disappear. Please remember this.`nNow, please enter your partner's name."
853 = "Done"
854 = "The other character's name"
855 = "A one-sided separation can be completed without the other person's consent, but it will reduce your alignment considerably. Enter the name of your current partner and the separation will take effect. When it does, the couple ring that symbolises your love will disappear.  Please remember this.`nNow, please enter your partner's name."
856 = "Couple"
857 = "You will be moved in %d seconds."
858 = "Looking for your partner."
859 = "Your partner could not be found."
860 = "The couple event is not running."
861 = "You are already waiting for someone."
862 = "The other person is not logged in."
863 = "You are of different races."
864 = "A couple can only be formed between a man and a woman."
865 = "You are not a paid user."
866 = "You are already in a couple."
867 = "You have been in a couple before."
868 = "You do not have enough money."
869 = "Your stats are too low."


# --- BATCH 10: billing, monster hunt quests, event lottery, quest dialogue -
870 = "Your level is too low."
871 = "You do not have space to receive the couple ring."
872 = "No partner is waiting for you."
873 = "You are not in a couple."
874 = "A skill that moves you to where your partner is."

875 = "Go to the payment page?"
876 = "Going to the payment page."
877 = "Your paid time has expired."
878 = "Your stats have reached the free service limit."
879 = "Your level has reached the free service limit."
880 = "You cannot level up because your fame is too low."
881 = "Fame required"
882 = "Limited"
# 883 is already "Limited" in English
884 = "%d days"
885 = "%d hours"
886 = "%d minutes"
887 = "%d seconds"
888 = "Time remaining :"
889 = "This disappears when you log out."

# quest briefings
890 = "This assignment comes directly from E.V.E. To counter the sharp rise in vampire numbers, new orders have been issued: choose a type of vampire in advance and destroy the given quantity. Quests must be taken one at a time, and logging out during a quest cancels it. The number of vampires varies with the type you choose. Complete this assignment and E.V.E will provide a special reward. Please choose the quest you want."
891 = "Would you take on a little task for me? Heh heh. It is only a hobby of mine, but I do so detest anything that is not beautiful. For the sake of our pure and noble vampire bloodline, I think the low-born creatures of unknown origin need clearing away. Heh heh. What do you say? Will you work with me and thin out the wretched rabble? Quests must be taken one at a time, and logging out during a quest cancels it. The number of monsters varies with the type you choose; simply go and hunt them. What will it be? You will be paid well, I assure you. Please choose the quest you want."
892 = "I will join another time."
893 = "I will learn it later."
# 894 has a leading space in the source - it is a counter suffix
894 = " creatures"

895 = "Time is up for the monster hunt quest."
896 = "The monster hunt quest objective is complete."
897 = "You can claim your reward from the NPC within this time."
898 = "The monster hunt quest has started."
899 = "A quest is already in progress."
900 = "Your stats do not qualify you for this quest."
901 = "You completed the monster hunt quest. The quest item has been added to your inventory."
902 = "The monster hunt quest is not finished yet."
903 = "There is no space in your inventory."
904 = "You are not on a quest."
905 = "You failed the quest: the time limit expired."
906 = "Time limit : "
907 = "You cannot apply for a quest right now."
908 = "Quest objective complete"
909 = "Time limit exceeded"
910 = "Meet %s"
911 = "You cannot claim a reward from that NPC."
912 = "A problem occurred. Please try again."
913 = "Find %s"
# 914/915: the Korean order is monster, count, time limit. English would
# naturally lead with the count, which would reorder the arguments, so the
# sentence is built around the original order instead.
914 = "Then take on the %s: %d of them, within %s."
915 = "Then take on the %s: %d of them, within %s."
916 = "I will check my equipment and come back."
917 = "Yes, understood."
918 = "Monster Hunt Quest"
919 = "Meet NPC Quest"
920 = "Item Retrieval Quest"

# quest timer readout - padded so the colons align, as in the Korean
921 = "Total time limit : "
922 = "Elapsed time     : "
923 = "Time remaining   : "
924 = "None"
925 = "Quest failed"

# event lottery
926 = "Choose one of the stage %d event prizes"
927 = "Please scratch the image above."
928 = "Three matching pictures wins."
929 = "Congratulations."
# 936 and 930 are concatenated around the prize name:
#   [name] + 936 + [prize] + 930
930 = "."
931 = "A resident who claims to have seen a strangely shaped person, thought to be an Ousters, has been reported living near Eslania. Go at once, find the witness, and gather as much information as you can."
932 = "Two residents who claim to have seen a strangely shaped person, thought to be an Ousters, are wandering fearlessly near Limbo Castle. Find them at once and gather as much information as you can."
933 = "I will restore my magic and come back."
# 934 carries a literal two-character \n in the source, not a real line break
934 = "Unfortunately you did not win.\nPlease try again next time.\nIf you take the event quest again you will have another chance at a ticket."
935 = "You have won a prize."
936 = " has won "

# scripted scene at Adam's Sanctuary. 946-954 repeat 937-945 with two lines
# changed, which is how the source has it.
937 = "The spirit stone you brought has freed Lord Karisas's soul from the world of death."
938 = "Look. Our kin, restored to life. All of it thanks to you."
939 = "The thirteenth Blood Bible, you say? Hohohohohoho. "
940 = "Humans really are beyond foolish."
941 = "It is far too dangerous a thing to fall into worldly hands like yours."
942 = "Our kind awoke in order to guard it."
943 = "Ever since we came to this place, we have watched over Adam's Sanctuary."
944 = "In any case, you have learned far too much."
945 = "So now I would be grateful if you kept your silence, in eternal darkness."
946 = "The spirit stone you brought has freed Lord Karisas's soul from the world of death."
947 = "Look. Our kin, restored to life. All of it thanks to you."
948 = "The thirteenth Blood Bible, you say? Hohohohohoho. "
949 = "That filthy greed has not changed in five hundred years."
950 = "It is far too dangerous a thing to fall into the hands of those who live steeped in blood."
951 = "Our kind awoke in order to guard it."
952 = "Ever since we came to this place, we have watched over Adam's Sanctuary."
953 = "In any case, you have learned far too much."
954 = "So now I would be grateful if you kept your silence, in eternal darkness."

955 = "Ancient Document Quest"
956 = "Ancient Map Quest"
957 = "Spirit Stone Quest"
958 = "You have no quest in progress."
959 = "The item was moved to your inventory."


# --- BATCH 11: item collection, mixing forge, Ousters skills and elements --
960 = "The item could not be moved to your inventory."
961 = "You cannot collect the purchased item right now."
962 = "Do you want to collect the selected item?"
963 = "Click an item name to collect that item."
964 = "The skill for the selected rank has been deleted."
965 = "You do not have the required qualification."
966 = "You have already deleted the skill for that rank."

# bulletin board
967 = "Use the bulletin board."
968 = "Cancel using the bulletin board."
969 = "This is too close to another bulletin board."

970 = "You can switch the gender restriction on an item."
971 = "Do you want to switch this item's gender restriction?"
972 = "Revive using an elixir."
973 = "Revive using a resurrection scroll."
974 = "This cannot be used."

# mixing forge
975 = "Use the mixing forge."
976 = "Cancel using the mixing forge."
977 = "The two items were successfully combined."
978 = "Combining the items failed."
979 = "Only members of the guild that owns the castle can use this."
980 = "This cannot be used while riding a motorcycle."
981 = "Unique and Limited items cannot be mixed."
982 = "Only items with a single option can be mixed."
983 = "You cannot select this: the item classes differ."
984 = "You cannot select this: the item types differ."
985 = "You cannot select this: both items have the same option."

# option removal. 990 and 991 are drawn as two lines of one sentence.
986 = "Which option do you want to remove?"
987 = "Do you really want to remove the selected option?"
988 = "You can remove an option from an item."
989 = "You cannot remove an option from this item."
990 = "Remove the %s option"
991 = "from this item?"
992 = "Removing the option failed."
993 = "The selected option was removed."
994 = "Other race only"

# Ousters gear slots
995 = "EP Cost : "
996 = "Equip a circlet."
997 = "Equip clothing."
998 = "Equip a chakram or wristlet."
999 = "Equip boots."
1000 = "Equip an armband."
1001 = "Equip a ring."
1002 = "Equip a necklace."
1003 = "Equip a spirit stone."
1004 = "%s spirit level : "

# The ten Sephirot of the Kabbalah tree of life, in their usual English
# spellings, ascending from Malkuth to Kether as the Korean does.
1005 = "Malkuth"
1006 = "Yesod"
1007 = "Hod"
1008 = "Netzach"
1009 = "Tiphareth"
1010 = "Geburah"
1011 = "Chesed"
1012 = "Binah"
1013 = "Chokmah"
1014 = "Kether"

# skill learning
1015 = "Skill level : %d"
1016 = "Required attribute level (%s)(%d)"
1017 = "Do you want to learn this skill?"
1018 = "Learning this skill fixes your element. From the next skill onward you will only be able to learn skills of this element."
1019 = "Do you want to raise this skill's level?"
1020 = "Skill points required : %d points"

# elements
1021 = "Fire"
1022 = "Water"
1023 = "Earth"
1024 = "Wind"
1025 = "Union"
1026 = "EP"

1027 = "Hide guild chat"
1028 = "Show guild chat"
1029 = "Send guild chat"

# Ousters rank bonuses
1030 = "Increased Protection"
1031 = "Increased Defense"
1032 = "Increased To Hit"
1033 = "Increased HP"
1034 = "Increased EP"
1035 = "Increased damage from combat skills"
1036 = "Increased attack speed"
1037 = "Increased damage from Fire attack magic"
1038 = "Increased damage from Water attack magic"
1039 = "Increased damage from Earth attack magic"
1040 = "Increased Acid resistance"
1041 = "Increased Bloody resistance"
1042 = "Increased Curse resistance"
1043 = "Increased Poison resistance"
1044 = "Reduced silver damage"
1045 = "Reduced EP cost when using skills"
1046 = "Increased HP steal"
1047 = "Increased EP steal"
1048 = "Increased Luck"
1049 = "EP:%d/%d"


# --- BATCH 12: guild UI and NPC, Ousters skills, trials, Capture the Flag --
1050 = "You must distribute your bonus points."
1051 = "Guild"
1052 = "Guild Info"
1053 = "Guild Member List"
1054 = "Guild Help"
# 1055-1059 (Fire/Water/Earth/Wind :%d, EP : ) are already English
1060 = "View the previous map."
1061 = "View the next map."
1062 = "Cancel the Earth Spirit's Horn."
1063 = "Attack speed : "
1064 = "Your maximum EP is now %d."
1065 = "Your maximum EP is now %d."
1066 = "Magic damage : "
1067 = "%s has opened."
1068 = "%s has closed."
1069 = "%s can be entered for %d more minutes."
1070 = "You must go to Sioram and make a contract before you can use this."
1071 = "You have made the contract to use the Earth Spirit's Horn."

# skill level reduction
1072 = "You cannot lower the skill level."
1073 = "You do not have enough money to lower the skill level."
1074 = 'The %s skill will change from level %d to %d. The cost is $%s. Proceed?'
1075 = "The change was successful."
1076 = "Skill points recovered : %d"
1077 = "Do you want to lower this skill's level?"
1078 = "You are not an Ousters."
1079 = "The skill level is too low."
1080 = "The skill level is too high."
1081 = "That is not a valid skill."
1082 = "You have not learned that skill yet."
1083 = "Once a skill reaches the maximum level of 30 the points cannot be recovered. Raise it to level 30?"
1084 = "Ousters cannot use this."
1085 = "These cannot be mixed: the items share the same option group."

# gender switch
1086 = "Do you really want to switch the gender?"
1087 = "You cannot switch gender while wearing clothing."
1088 = "A character in a couple cannot switch gender."

# trial list - these carry a literal two-character \n, not a real line break
1089 = "1. Judgement of Wisdom\nObjective: complete the given puzzle"
1090 = "2. Key of the Barrier\nObjective: collect the minerals set for your level (8)"
1091 = "3. The Invisible Wall\nObjective: pass through the maze and obtain Lipinium"
1092 = "4. The Talking Doll\nFind and assemble the puzzle pieces in the given dungeon"
1093 = "5. The Door to the Future\nFind magic stones from certain monster classes and assemble the code sheet"
1094 = "Two trials are prepared. Choose one of them."
1095 = "Arrow Tiles. Follow the arrows and reach the goal safely."
1096 = "Crazy Mine. A puzzle game combining number guessing and minesweeper."
1097 = "You obtained Lipinium."
# 1098-1100 (Arrow Tiles, Crazy Mine, All Stage Clear!) are already English

# guild registration NPC - the guild counterpart of the team/clan lines at
# 50-79, and phrased the same way
1101 = "Let me see now. It says here you already belong to the %s guild."
1102 = "You left another guild only recently. Think it over more carefully."
1103 = "Your guild was disbanded only recently. Build yourself up to meet the requirements, and watch for the right moment."
1104 = "Impressive, but you lack the makings of a leader. Go and hone your skills."
1105 = "Founding a guild takes a great deal of money. You do not appear to have it."
1106 = "%s, is it? I have never heard that name, which tells me you are a novice. Hone your skills and come back."
1107 = "That guild name is already taken. Think of another."
1108 = "Refused."
1109 = "You already belong to another guild."
1110 = "You left another guild only recently. Think it over more carefully."
1111 = "Your guild was disbanded only recently. Build yourself up to meet the conditions, and watch for the right moment."
1112 = "You still have a great deal to learn. Hone your skills and come back."
1113 = "%s, you need more money to register a guild."
1114 = "%s, is it? I have never heard that name, which tells me you are a novice. Hone your skills and come back."
1115 = "Click to see the details."
1116 = "Ousters"

# Capture the Flag event
1117 = "The Capture the Flag! event begins in 5 minutes."
1118 = "The Capture the Flag! event has started."
1119 = "The Capture the Flag! event has ended."
1120 = "The %s race won with %d flags."
1121 = "Items will burst in the flag area in 3 minutes."
1122 = "Capture the Flag event items have appeared."
1123 = "Flags captured : %d"
1124 = "You have been muted by a GM."
1125 = "You cannot enter a safe zone while carrying a flag."
1126 = "You cannot drop items near the flagpole."
1127 = "Items will burst in the flag area in %d seconds."
1128 = "You cannot mount or dismount a motorcycle near the flagpole."

1129 = "Guild Name : %s"
1130 = "Guild Introduction : "
1131 = "Guild Name : "
1132 = "No guild registered"

1133 = "You are revived by the Eternity skill."
1134 = "You must learn the Vivid Magazine skill to use this."
1135 = "You will revive in %d seconds."
1136 = "You cannot trade while riding the Wind Spirit."
1137 = "You cannot use this while riding the Wind Spirit."
1138 = "Your %s skill level is now %d."
1139 = "Your %s skill level is now %d."


# --- BATCH 13: premium service, pets, mailbox, weapon categories ----------
1140 = "Move to the beginner-only hunting ground."
1141 = "Your premium service has %d days remaining."
1142 = "You are not a paid user."
1143 = "Your premium service ends today."
1144 = "Renew before your premium service ends and you can receive mileage and"
1145 = "a variety of other benefits such as item tickets."
# the source names www.darkeden.com here; that site is dead for this server,
# so the sentence keeps its meaning without the address
1146 = "Details are available on the official website."
1147 = "Caligo floor %d"

# relic bonuses (repeated in groups of three, as in the source)
1148 = "HP absorb +15"
1149 = "HP +50, all stats +7"
1150 = "Physical/magic attack damage +10"
1151 = "HP absorb +15"
1152 = "Sight +5, all stats +7"
1153 = "Physical/magic attack damage +10"
1154 = "HP absorb +15"
1155 = "Sight +5, all stats +7"
1156 = "Physical/magic attack damage +10"
1157 = "HP absorb +15"
1158 = "Sight +5, all stats +7"
1159 = "Physical/magic attack damage +10"

1160 = "Join the war."
1161 = "Click to move to that regen zone tower."
1162 = "Held by an Ousters."
1163 = "In the Ousters guardian shrine."

# mailbox
1164 = "Mailbox"
1165 = "Close the mailbox."
1166 = "Read the letter."
1167 = "View the help."
1168 = "This is not supported yet."

1169 = "The bat color has been changed."
1170 = "The advanced character's bat color has been changed."
1171 = "Level War"
1172 = "Your family service has %d days remaining."
1173 = "Your family service ends today."
1174 = "You need to get closer."

# pet system
1175 = "Food remaining : "
1176 = "Attribute : "
1177 = "View the pet info window."
1178 = "The enchant failed."
1179 = "Food remaining"
1180 = "Do you want to revive your pet?"
1181 = "Close the pet info window."
1182 = "You can grant a second ability."
1183 = "You cannot grant a second ability yet."
1184 = "%s's level is now %d."
1185 = "%s's level is now %d."
# pet names - indices 1201-1204 already hold these in English
1186 = "Lucky"
1187 = "Minion"
1188 = "Nut"
1189 = "Crunch"
1190 = "%s has only %s of food left."
1191 = "Please refill the food."
1192 = "%s has died."
1193 = "%s has been summoned."
1194 = "You can grant an attribute."
1195 = "You granted a second ability to %s."
1196 = "You can loot monster heads along with items."
1197 = "You can loot soul stones along with items."
1198 = "You can grant an option to %s."
# %% is a literal percent sign, not a specifier - kept as-is
1199 = "EXP remaining : %s (%s%%)"
1200 = "Granting the second ability failed."
# 1201-1204 (Lucky, Minion, Nut, Crunch) are already English
1205 = "This can be revived."
1206 = "This can only be used when dead."
1207 = "Head looting available"
1208 = "Head looting unavailable"
1209 = "Do you want to erase your pet's option?"
1210 = "Both sides must have a gift box to exchange."

1211 = "Congratulations! You are now eligible to take part in the school event."
1212 = "The 99 Netmarble cards are your entry tickets."
1213 = "Please keep them safe until the event ends."
1214 = "Without the cards you cannot take part in the event."
1215 = "Right-click to feed your pet."
1216 = "Right-click to separate the item."
1217 = "Do you want to feed your pet?"
1218 = "You can only separate the item while your pet is not summoned."

# weapon category filters
1219 = "Sword & Blade"
1220 = "Sword"
1221 = "Blade"
1222 = "Gun"
# 1223-1226 (SMG, AR, SG, SR) are already English
1227 = "Cross & Mace"
1228 = "Cross"
1229 = "Mace"


# --- BATCH 14: item categories, in-game library, quest objectives ---------
# armour and accessory filters
1230 = "Armor"
1231 = "Helmet"
1232 = "Top"
1233 = "Bottom"
1234 = "Shield"
1235 = "Gloves"
1236 = "Belt"
1237 = "Shoes"
1238 = "Accessory"
1239 = "Necklace"
1240 = "Bracelet"
1241 = "Ring"
1242 = "Etc"
1243 = "Potion"
1244 = "Flask & Holy Water"
1245 = "Magazine"
1246 = "Bomb & Mine"
1247 = "Radio"
1248 = "Other Items"

# titles of the in-game library articles (the article text itself lives in
# book.rpk inside the dpk, not in this table)
1249 = "Vampires Examined Scientifically"
1250 = "A Scientific Look: Do Vampire Bats Really Drink Human Blood?"
1251 = "Vampire Legends of Romania and Czechoslovakia"
1252 = "Vlad Tepes of Romania"
1253 = "Vampire Legends of Mexico and Arabia"
1254 = "Vampires A to Z"
1255 = "What Is a Vampire"
1256 = "Vampire Abilities"
1257 = "Vampire Habits"
1258 = "Vampire Weaknesses and How to Destroy Them"
1259 = "A History of Vampires"
1260 = "Vampire Legends of the West Indies and Polynesia"
1261 = "Vampires in the Bible"
1262 = "Vampire Tales in Slavic Folk Belief"
1263 = "Vampire Legends of Japan and the Malay Peninsula"
1264 = "The Killer Said to Be Bluebeard: Gilles de Rais"
1265 = "Hungary's Blood Countess: Erzsebet Bathory"
1266 = "Precautions Against Vampires"
1267 = "Vampire Legends"
1268 = "Characteristics of Vampires"
1269 = "Vampire Bats and Werewolves"

# 1270-1294 are the client's own English monster names - already English

# skill domain filters
1295 = "Blade"
1296 = "Sword"
1297 = "Enchant"
1298 = "Gun"
1299 = "Heal"
1300 = "Etc"
1301 = "Vampire"
1302 = "Ousters"
# 1303-1305 (Etc, Vampire, Ousters) are already English
1306 = "Soul Stone"

1307 = "This can be transformed."
1308 = "This cannot be transformed."
1309 = "Do you want to transform your pet into a Wolverine?"
1310 = "Billing information could not be found."
1311 = "You cannot create a character because you are not a paid user."
1312 = "%d days have passed since death."
1313 = "Luck : "

# NPC names
1314 = "Gruber"
1315 = "Capatini"
1316 = "Amata"

# Timed hunt quests. The Korean order is minutes, monster, count; English
# would naturally put the count before the monster, which would reorder the
# arguments, so the objective is phrased to keep the original order.
1317 = "Centauro Quest\nObjective: within %d minutes\nhunt {%s} x{%d}"
1318 = "Sturge Quest\nObjective: within %d minutes\nhunt {%s} x{%d}"
1319 = "Pixie Quest\nObjective: within %d minutes\nhunt {%s} x{%d}"


# --- BATCH 15: pet abilities, SMS, nicknames, quest list, siege -----------
# 1320 is a suffix appended after an NPC name
1320 = " - return to them."
1321 = "You can grant a third ability."
1322 = "You cannot grant a third ability yet."
1323 = "Granting the third ability failed."
1324 = "You granted a third ability to %s."
1325 = "You cannot summon a second-tier pet below level 40."
1326 = "Mines to find : %d   Mines checked : %d"
1327 = "Items more than two grades apart cannot be mixed."
# 1328-1329 (game over, All stage clear) are already English
1330 = "Monster numbers have surged of late, and the barrier grows weaker because of them. For the sake of our race's revival we must deal with these monsters and hold the barrier. Take care: this assignment is void if you log out partway through. Hunt the number of monsters the quest calls for and return, and I will give you a fine reward. Now then, which quest will you choose?"
# 1331 is already English
1332 = "Do you want to store your pet?"
1333 = "Do you want to collect your pet?"
1334 = "There is already another item."
# 1335 is a run of Roman numerals - left as-is
1336 = "Grade :"

# SMS window
1337 = "The message was sent successfully."
1338 = "Failed to send the message."
1339 = "Failed to add to the list."
1340 = "Failed to delete from the list."
1341 = "You have exceeded the number of entries you can save."
1342 = "That information is not valid."
1343 = "The information could not be found."
1344 = "You do not have enough credit."
1345 = "SMS Window"
1346 = "Send the message."
1347 = "View the phone book."
1348 = "Select a special character."
1349 = "Add the selected number to the send list."
1350 = "Delete the selected number."
1351 = "Register a new number."
1352 = "Do you want to use the SMS item?"

# nickname window
1353 = "Nickname Window"
1354 = "Change your pet's nickname."
1355 = "Change your free user nickname."
1356 = "Add a nickname."
1357 = "Change to the selected nickname."
1358 = "The nickname has been changed."
1359 = "A nickname assigned by a GM cannot be changed."
1360 = "Do you want to use the naming item?"
1361 = "This cannot be used."
1362 = "You can only change the nickname while your pet is summoned."
1363 = "A Wolverine's nickname can be changed without a pen item."
1364 = "The item could not be found."

# set bonuses
1365 = "Physical attack +%d"
1366 = "Magic attack +%d"
1367 = "Physical defense +%d"
1368 = "Magic defense +%d"
1369 = "All stats +%d (4 Set)"
1370 = "All resistances +%d (4 Set)"
# leading tab is significant on both of these
1371 = "`t       %s"
1372 = "`tOptions : %s"

# quest states and quest list
1373 = "Unavailable"
1374 = "Available"
1375 = "In progress"
1376 = "Success"
1377 = "Complete"
1378 = "Failed"
1379 = "Repeatable"
1380 = "Mission %d: %s"
1381 = "Accept the quest."
1382 = "Abandon the quest."
1383 = "View the list in progress."
1384 = "View the completed list."
1385 = "You have collected %d gold medals."

1386 = "Your authentication key has expired. Please reconnect."
1387 = "Your authentication key is missing or invalid. Please reconnect."
1388 = "Quest information has been updated."
1389 = "You can sell the event item for %d."

# castle siege applications
1390 = "Too many guilds have applied for the siege, so you cannot apply."
1391 = "Your defender application was already refused, so you cannot reapply."
1392 = "A guild has already been approved as defender, so you cannot apply."
1393 = "No guild has applied for the siege, so you cannot apply as defender."
1394 = "The defender application cannot be accepted."
1395 = "The application has been accepted."
1396 = "The defender application cannot be refused."
1397 = "The application has been refused."
1398 = "Move to the trap zone"
1399 = "Move in front of the inner gate"
1400 = "Move inside the inner castle"
1401 = "Move inside the inner castle"
1402 = "Your character's level is too high to connect. Please use another server."

# beginner event notices
1403 = "A beginner event from DarkEden. For new players still finding their feet, we are giving a small gift along with a lottery ticket. Use the ticket you earn by completing the event and you could win any of the prizes on offer, and more gifts are waiting when you reach the next level. Collect all the event items and try out some high-performance gear. The event comes in 8 parts, awarded as you level up. The quest window shortcut is Ctrl + Q. Enjoy your time in the world of DarkEden, and do not miss the chance to build your character and collect gifts at the same time."
1404 = "A beginner event from DarkEden. You have reached level %d, so a %s box has been added for you. Press Ctrl + Q to check it, and if you have a box from earlier you can collect its items too. The items given to you are time-limited. They are of a higher grade than the usual level-restricted gear, and because they are event items they cannot be traded or exchanged. Once you obtain better equipment you can sell them through an NPC. The time remaining is shown at the bottom of the item. Note that this timer runs in real time even while you are away from the DarkEden world, so use it wisely. Enjoy the rest of your time here."
1405 = "You have reached level %d. Press Ctrl + Q to check. If you have a box you received earlier, you can collect its items."

# colours
1406 = "Red"
1407 = "Orange"
1408 = "Yellow"
1409 = "Green"


# --- BATCH 16: colours, set bonuses, alliance system, castle tax ----------
1410 = "Blue"
1411 = "Navy"
1412 = "Purple"
1413 = "Black"

# set / option bonuses
1414 = "All stats +2"
1415 = "INT +5"
1416 = "DEX +5"
1417 = "STR +5"
1418 = "Acid resistance +10%"
1419 = "Blood resistance +10%"
1420 = "Curse resistance +10%"
1421 = "Poison resistance +10%"
1422 = "All resistances +3%"
1423 = "Protection +5%"
1424 = "Defense +5%"
1425 = "To hit +5%"
1426 = "MP +5%"
1427 = "Critical attack +5%"
1428 = "HP +5%"
# 1429 carries a trailing space in the source
1429 = "Defense +5% "
1430 = "To hit +5%"
1431 = "MP +5%"
1432 = "Critical attack +5%"
1433 = "Enemy Acid resistance -10%"
1434 = "Enemy Blood resistance -10%"
1435 = "Enemy Curse resistance -10%"
1436 = "Enemy Poison resistance -10%"
1437 = "Enemy all resistances -3%"
1438 = "Fire spirit +1"
1439 = "Water spirit +1"
1440 = "Earth spirit +1"

# siege participant states
1441 = "(Attacker)"
1442 = "(Defender)"
1443 = "(Offline)"

# member list columns
1444 = "ID"
1445 = "Server"
1446 = "Grade"

# team / clan / guild menus
1447 = "Team Commands"
1448 = "Team List"
1449 = "Pending Team List"
1450 = "Team Alliance"
1451 = "Clan Commands"
1452 = "Clan List"
1453 = "Pending Clan List"
1454 = "Clan Alliance"
1455 = "Guild Commands"
1456 = "Guild List"
1457 = "Pending Guild List"
1458 = "Guild Alliance"

# alliance system
1459 = "Join the selected alliance."
1460 = "Leave the selected alliance. "
1461 = "Expel the selected guild from the alliance."
1462 = "You have already joined a guild."
1463 = "An alliance application has already been made."
1464 = "The other person is not a master."
1465 = "You are not in an alliance."
1466 = "The alliance's master guild cannot leave on its own."
1467 = "There is no such alliance."
1468 = "You do not belong to that alliance."
1469 = "The applicant is not a master."
1470 = "Once you belong to one alliance you cannot join another.   Do you want to join?"
1471 = "Processed successfully."
1472 = "The other guild master refused."
1473 = "The alliance was created successfully."
1474 = "Do you really want to leave?"
1475 = "Request the guild master's approval."
1476 = "Leave immediately"
1477 = "If you apply to leave and the guild master approves, there is no penalty. Do you want to apply?"
1478 = "Leaving immediately is possible, but it carries a penalty. Do you want to leave now?"
1479 = "Do you really want to expel them?"
# the source uses a capital %S here, which is preserved
1480 = "%S has been forcibly expelled."
1481 = "The %s guild is applying to join the alliance."
1482 = "The %s guild is applying to leave the alliance."
1483 = "There is a record of being forcibly removed from an alliance."
1484 = "Do you want to summon %s?"
1485 = "Skill learned at level : %d"
1486 = "Accept the alliance withdrawal"
1487 = "Refuse the alliance withdrawal."
1488 = "Only a guild master can apply for an alliance."
1489 = "You already belong to an alliance."
1490 = "You are not the alliance master."
1491 = "The alliance has no free slots."

# Blood Bible tokens
1492 = "Equip the Blood Bible token."
1493 = "Borrow the Blood Bible token."
1494 = "Borrow the %s token. (%s)"
1495 = "I will borrow it later."
# 1496 (Ranger/) is already English

# castle tax rate
1497 = "The tax rate was changed successfully."
1498 = "Failed to change the tax rate."
1499 = "Enter the new tax rate."


# --- BATCH 17: personal shop, Powerzzang, item grades, class titles -------
1500 = "Ranger"
# 1501 is a heart symbol - left as-is
1502 = "Love"
1503 = "I love you"
1504 = "I love you"
1505 = "The war has begun. To take part, move to the Acheron server from Transylvania, or to the Rune server from Brasov. In the war between the races you must secure as many bibles as you can."
1506 = "Appoint as sub-master."
1507 = "Skill points can be recovered"
1508 = "Skill points cannot be recovered"
1509 = "The points cannot be recovered."
1510 = "There are more than 50 members, so you cannot join."
1511 = 'The skill points for the %s skill will be recovered. The cost is $%s. Proceed?'
1512 = "Send alliance chat"
1513 = "Show alliance chat"
1514 = "Hide alliance chat"
1515 = "Revive in front of the inner gate."

# Powerzzang points. The source repeats www.powerzzang.com in every error
# message; that service is gone, so the messages keep their meaning without it.
1516 = "Collect Powerzzang points"
1517 = "My accumulated Powerzzang points"
1518 = "Points available to exchange"
1519 = "Mobile phone"
1520 = "Number"
1521 = "Collect your Powerzzang points."
1522 = "Exchange Powerzzang points for items."
1523 = "Your Powerzzang points were applied successfully. Points transferred : %d"
1524 = "You are not a Powerzzang member."
1525 = "There is a problem with the Powerzzang server. Please try again."
1526 = "There is a problem with the Powerzzang database. Please try again."
1527 = "You do not have enough accumulated Powerzzang points."
1528 = "No matching information was found."
1529 = "There is a problem connecting to the Powerzzang server."

1530 = "Functions"
1531 = "Personal Shop"
1532 = "Powerzzang"

# personal shop
1533 = "Enter the price to sell the item."
1534 = "Enter your personal shop advertisement!!"
1535 = "Open your personal shop."
1536 = "Close your personal shop."
1537 = "Write a personal shop advertisement"
1538 = "That seller could not be found."
1539 = "The shop has already closed."
1540 = "That item has already been sold or withdrawn by the seller."
1541 = "The seller is carrying too much money, so you cannot buy it."
1542 = "That item is already on display."
1543 = "A variety of goods are available."
1544 = "Show game money in Korean as well"

# item grades, named after Egyptian gods
1545 = "Horus grade %d"
1546 = "Seth grade %d"
1547 = "Maat grade %d"
1548 = "Osiris grade %d"
1549 = "Thoth grade %d"
1550 = "Nut grade %d"
1551 = "Geb grade %d"
1552 = "Shu grade %d"
1553 = "Ra grade %d"
1554 = "Ptah grade %d"
1555 = "Nun grade %d"

# Ousters gear slots
1556 = "Equip a carrying receiver."
1557 = "Equip shoulder armor."
1558 = "Equip a tattoo."
1559 = "Equip a mask."
1560 = "Equip a waist ornament."
1561 = "Equip gloves."
1562 = "Title"

# advancement item exchange
1563 = "Click the item you want to exchange for an advancement item."
1564 = "Do you want to exchange it for an advancement item?"
1565 = "You have not advanced, so the item cannot be exchanged."
1566 = "This cannot be exchanged for an advancement item."

# charity donation
1567 = "Please enter the amount you wish to donate."
1568 = "Your donation will be put to good use for neighbours in need. `nThank you for taking part in the collection."

# currency names
1569 = "Rey"
1570 = "Geld"
1571 = "Zad"

# grade requirements
1572 = "Horus grade %d or higher"
1573 = "Seth grade %d or higher"
1574 = "Maat grade %d or higher"
1575 = "Osiris grade %d or higher"
1576 = "Thoth grade %d or higher"
1577 = "Nut grade %d or higher"
1578 = "Geb grade %d or higher"
1579 = "Shu grade %d or higher"
1580 = "Ra grade %d or higher"
1581 = "Ptah grade %d or higher"
1582 = "Nun grade %d or higher"

# advancement class titles
1583 = "Splitter"
1584 = "Defender"
1585 = "Heavy Shooter"
1586 = "Priest"
1587 = "Granter"
1588 = "Vamp Noble"
1589 = "Custos"


# --- BATCH 18: comeback events, PK consent, dyeing, spirit bond -----------
1590 = "Ignicer "
1591 = "Aquan "
1592 = "Terranos "
1593 = "Hide personal shop messages"
1594 = "Do you want to receive the comeback event item on this character?"
1595 = "You received the event item."
1596 = "You have already collected the event item."
1597 = "Failed to receive the event item."
1598 = "You are not eligible for this event."
1599 = "Congratulations! Your event prize has been awarded."
1600 = "The web page could not be opened."

# enchanting restrictions
1601 = "Advanced characters cannot use this."
1602 = "Items of grade %d or higher cannot be enchanted."
1603 = "Advancement-only items cannot be enchanted."
1604 = "Items with two or more options cannot be enchanted."

# charity donation
1605 = "Please enter the gift amount yourself.`n(in units of 10,000 / minimum 10,000 to maximum 100,000)."
1606 = "Thank you. It will be delivered safely."
1607 = "You are already on the donor list. You cannot donate twice."

# 1608 is NOT translated on purpose. It is the original publisher's personal
# data consent notice, naming CJ Internet and Softon Entertainment as the
# parties receiving player data. Rendering that in English would state
# something untrue about what this server does with data. Replace it with your
# own privacy text when you have one; until then it stays as shipped.
1609 = "I agree to the above."
1610 = "You cannot connect because you have not agreed to the revised terms."
1611 = "Characters that have not advanced cannot use this."
1612 = "Characters below level 99 and advanced characters cannot use this."
1613 = "That color is already applied. "
1614 = "The effect has been applied. "
1615 = "Available once the Force Scroll effect wears off. "
1616 = "Once used, this item disappears. Do you want to use it?"
1617 = "This type of item cannot be used."
1618 = "A set amount of Geld is consumed each time this is used."
1619 = "You do not have enough Geld to use the Seal."
1620 = "The recharge cost varies with level."
1621 = "This can be recharged and used."

# expired seasonal comeback events, kept for completeness
1622 = "Congratulations! You are eligible for the Summer COME BACK, 2005 event.`n`nYou receive premium benefits for 5 days from the moment you log in during the event period.`n`nYou can also claim a commemorative item, so please visit the NPC for your race.`n`n(Note: the event item can be claimed by only one character per account.)`n`n*Event NPCs`n`nSlayer: Christine (Priest Guild, 1st floor)`n`nVampire: Seth (inside Limbo Castle)`n`nOusters: Hora (inside the Ousters village)`n`n"
1623 = "Your payment went through successfully. You can now enjoy DarkEden with premium benefits.`n`nAs a bonus for this event we are giving you the training set sold in the Daden Market.`n`n(Note: the event item can be claimed by only one character per account.)`n`n*Event NPCs`n`nSlayer: Christine (Priest Guild, 1st floor)`n`nVampire: Seth (inside Limbo Castle)`n`nOusters: Hora (inside the Ousters village)`n`nNow put on the training set and enjoy DarkEden to the full.`n`n"
1624 = "Congratulations. You have been recommended by someone eligible for the Summer COME BACK, 2005 event.`n`nThe person who recommended you receives a small gift, so please visit an event NPC to collect it.`n`n(Note: the event item can be claimed by only one character per account.)`n`n*Event NPCs`n`nSlayer: Christine (Priest Guild, 1st floor)`n`nVampire: Seth (inside Limbo Castle)`n`nOusters: Hora (inside the Ousters village)`n`nThank you."

# pet rampage counters
1625 = "Attack rampage %d / %d"
1626 = "Defense rampage %d / %d"
1627 = "Party rampage %d / %d"
1628 = "Do you want to reset your pet's attribute?"
1629 = "The attribute cannot be reset right now."
1630 = "There is no telling which monster it will become. Transform it?"
1631 = "Do you want to improve your pet?"
1632 = "Do you want to upgrade the weapon? "
1633 = "Do you want to reset your rank skills?"
1634 = "This character already has a 2x4 pack."
1635 = "Magical pet activation :"
1636 = "Do you want to upgrade this item?"
1637 = "This game is rated 18+ and may not be played by minors."
1638 = "This feature is unavailable while the servers are being merged."

# world names
1639 = "Moldavia"
1640 = "Transylvania"
1641 = "Wallachia"
1642 = "Histria"
1643 = "Brasov"

# PK consent
1644 = "The server you selected allows players to attack one another without mutual consent. You cannot enter unless you consent to being attacked by other players. Do you consent?"
1645 = "If you would rather not be attacked by other players, please use a Non PK server."
1646 = "This map is an area where players can attack one another."
1647 = "HP reduced by 30% (until alignment recovers)"
1648 = "All character settings will be reset. Do you want to reset them?"
1649 = "Daden Market"
1650 = "Shopping cart"
1651 = "Congratulations! You are eligible for the COME BACK, 2006 event.`n`nYou receive premium benefits for 5 days from the moment you log in during the event period.`n`nYou can also claim a commemorative item, so please visit the NPC for your race.`n`n(Note: the event item can be claimed by only one character per account.)`n`n*Event NPCs`n`nSlayer: Christine (Priest Guild, 1st floor)`n`nVampire: Seth (inside Limbo Castle)`n`nOusters: Hora (inside the Ousters village)`n`n"
1652 = "Your payment went through successfully. You can now enjoy DarkEden with premium benefits.`n`nAs a bonus for this event we are giving you the training set sold in the Daden Market.`n`n(Note: the event item can be claimed by only one character per account.)`nThe item goes to the first character you log in with, so please take care which character you enter on.`n`n*Event NPCs`n`nSlayer: Christine (Priest Guild, 1st floor)`n`nVampire: Seth (inside Limbo Castle)`n`nOusters: Hora (inside the Ousters village)`n`nNow put on the training set and enjoy DarkEden to the full.`n`n"

1653 = "A guild master cannot delete their character."
1654 = "Please type delete exactly."
1655 = "The input is incorrect."

# play-time health notices
1656 = "Playing for long periods can harm your health."
1657 = "Just as study and work need breaks, so does playing games."
1658 = "%d hours have passed."
1659 = "%d hours have passed. Please take a short break."

# dyeing
1660 = "That color is already applied, so it cannot be dyed."
1661 = "You do not have enough money to dye this."
1662 = "Dyeing is complete."

# spirit bond - the Ousters counterpart of the couple system at 851-869
1663 = "A spirit bond must be formed by mutual agreement.`nTo apply, enter the name of the person you wish to bond with. If they come to me and agree within one minute, the bond is formed. Please remember this.`nNow, please enter the name of the person you wish to bond with."
1664 = "If you wish to break the bond there are two ways.`nOne is dissolution by mutual agreement, the other a one-sided break without agreement. `nRemember that choosing a one-sided break will reduce your alignment."
1665 = "If you wish to break the bond there are two ways.`nOne is dissolution by mutual agreement, the other a one-sided break without agreement. `nRemember that choosing a one-sided break will reduce your alignment."
1666 = "The spirit bond event is not running."
1667 = "You are already waiting for someone."
1668 = "The other person is not logged in."
1669 = "You are of different races."
1670 = "A couple can only be formed between a man and a woman."
1671 = "You are not a paid user."
1672 = "You are already in a spirit bond."
1673 = "You have been in a spirit bond before."
1674 = "You do not have enough money."
1675 = "Your stats are too low."
1676 = "Your level is too low."
1677 = "You do not have space to receive the bond pendant."
1678 = "No one is waiting for you."
1679 = "You are not in a spirit bond."


# --- BATCH 19: spirit bond, guild authority, siege rules, enchanting ------
1680 = "The spirit bond has been formed. The bond pendant has been added to your inventory."
1681 = "The spirit bond could not be formed."
1682 = "Spirit Bond"
1683 = "Looking for your bonded character."
1684 = "Your bonded character could not be found."
1685 = "Do you want to use the item?"
1686 = "The same item is already in use."
1687 = "You do not have enough money to exchange."
1688 = "You are carrying too much money to exchange."
1689 = "There are no items available to exchange."
1690 = "The exchange completed successfully."
1691 = "That is not a valid target."
1692 = "You do not have enough footballs to exchange for a prize."
1693 = "You do not have enough items to make a seal stone."
# 1694-1695 are screen resolutions
1696 = "This is a post-paid account."
1697 = "You can set the tax rate."
# 1698 is the bare format string %d%%

# guild authority transfer
1699 = "%s leadership will pass to %s. Do you want to transfer authority to %s?"
1700 = "Transfer authority."
1701 = "Authority cannot be transferred to that character."
1702 = "The guild master can only be changed once a week."
1703 = "You cannot change the guild master while a siege application is pending."
1704 = "The authority transfer was stopped."

# siege eligibility
1705 = "A guild whose master is level 130 or below cannot apply for a siege."
1706 = "A guild with 20 or fewer members cannot apply for a siege."
1707 = "A guild whose members average below level 60 cannot apply for a siege."

# 1708-1710 (STR/DEX/INT +%d) and 1713 (MP +%d) are already English
1711 = "Defense +%d"
1712 = "All stats +%d"
1714 = "To hit +%d"
1715 = "Damage +%d"
1716 = "You cannot enter right now."
# the source uses %u here, not %d
1717 = "You received the item for %u accumulated points."
1718 = "Your accumulated points have been reset."
1719 = "You do not have enough event items to exchange."

# skill line selection
1720 = "Skill learned at level : %s"
1721 = "You have chosen the %s skill. From now on you can only learn %s skills. Do you want to continue?"
# the source wraps the name in literal double quotes
1722 = '"%s" has chosen %s. Once a line is decided it cannot be changed. Is that all right?'
1723 = "Warrior line"
1724 = "Mage line"
1725 = "World map"
1726 = "You do not have enough items to exchange."
# 1727-1730 (Connect, Option, Credit, Exit) are already English

# toggles
1731 = "Forced attack enabled."
1732 = "Forced attack disabled."
1733 = "Background music on."
1734 = "Background music off."
1735 = "Sound effects on."
1736 = "Sound effects off."
1737 = "You revive with another player's help."
1738 = "Free"
1739 = "Paid"
1740 = "%s points %d will be converted into %d bonus points. Do you want to use the item?"
1741 = "You cannot use the Crystal of Oblivion any more."

# Korean game rating notices
1742 = "The DarkEden Black version is classified as an 18+ title under Article 21 of the Game Industry Promotion Act."
1743 = "The DarkEden White version is classified as a 12+ title under Article 21 of the Game Industry Promotion Act."
1744 = "This server cannot be accessed by anyone under 15."
1745 = "This cannot be listed in a personal shop."
# 1746 is NewID
1747 = "Do you want to quit?"

# daily check-in event
1748 = "Only newly registered members can take part in the event."
1749 = "You have already checked in today. Please come back tomorrow."
1750 = "%s has checked in %d times."

# pet capsule abilities
1751 = "No capsule ability"
1752 = "Has Shock ability"
1753 = "Has Ice ability"
1754 = "Has Diet ability"
1755 = "The pet's level does not meet the requirement, so it cannot be enchanted."
1756 = "The enchant effect is already applied, so this cannot be used."
1757 = "The pet enchant succeeded."

1758 = "This game may not be played by minors."
1759 = "This game may not be played by anyone under 12."
1760 = "Rating information"
# 1761-1763 are already English

# rare skills and enchanting
1764 = "Do you want to learn the selected rare skill?"
1765 = "View the rare skill window."
1766 = "Can be used to enchant attack weapons of Unique option or below."
1767 = "Can be used to enchant attack magic items of Unique option or below."
1768 = "Can be used to enchant armor of Unique option or below."
1769 = "The enchant succeeded. A new option was created on the item."
1770 = "The enchant failed. The enchant option was lost."
1771 = "The enchant failed. The item's grade dropped by one."
1772 = "Enchant option : "
1773 = "Your stats are too low to learn the skill."
1774 = "Your level is too low to learn the skill."
1775 = "Show the GPS window."

# NPC names
1776 = "Grun"
1777 = "Khan"
1778 = "Gabri"
1779 = "Phantom"


# --- BATCH 20: final block - bonuses, celestial names, upgrades, UI help ---
1780 = "Red"
1781 = "Ose"
1782 = "Borrow the %s %s token. (%s %s)"

# 1783-1854: generated from the Korean source (four repeating patterns with an
# escalating value), so each number is guaranteed to match its own line.
1783 = "Defense +2"
1784 = "All stats +1"
1785 = "Protection +2"
1786 = "Defense +2"
1787 = "Protection +2"
1788 = "Protection +2"
1789 = "Defense +2"
1790 = "All resistances +1"
1791 = "All stats +1"
1792 = "All resistances +1"
1793 = "All resistances +1"
1794 = "Protection +2"
1795 = "Defense +3"
1796 = "All stats +2"
1797 = "Protection +3"
1798 = "Defense +3"
1799 = "Protection +3"
1800 = "Protection +3"
1801 = "Defense +3"
1802 = "All resistances +2"
1803 = "All stats +2"
1804 = "All resistances +2"
1805 = "All resistances +2"
1806 = "Protection +3"
1807 = "Defense +4"
1808 = "All stats +3"
1809 = "Protection +4"
1810 = "Defense +4"
1811 = "Protection +4"
1812 = "Protection +4"
1813 = "Defense +4"
1814 = "All resistances +3"
1815 = "All stats +3"
1816 = "All resistances +3"
1817 = "All resistances +3"
1818 = "Protection +4"
1819 = "Defense +5"
1820 = "All stats +4"
1821 = "Protection +5"
1822 = "Defense +5"
1823 = "Protection +5"
1824 = "Protection +5"
1825 = "Defense +5"
1826 = "All resistances +4"
1827 = "All stats +4"
1828 = "All resistances +4"
1829 = "All resistances +4"
1830 = "Protection +5"
1831 = "Defense +6"
1832 = "All stats +5"
1833 = "Protection +6"
1834 = "Defense +6"
1835 = "Protection +6"
1836 = "Protection +6"
1837 = "Defense +6"
1838 = "All resistances +5"
1839 = "All stats +5"
1840 = "All resistances +5"
1841 = "All resistances +5"
1842 = "Protection +6"
1843 = "Defense +7"
1844 = "All stats +6"
1845 = "Protection +7"
1846 = "Defense +7"
1847 = "Protection +7"
1848 = "Protection +7"
1849 = "Defense +7"
1850 = "All resistances +6"
1851 = "All stats +6"
1852 = "All resistances +6"
1853 = "All resistances +6"
1854 = "Protection +7"

1855 = "Contribution"

# celestial hierarchy, then demonic and angelic names, in standard English forms
1856 = "Principalities"
1857 = "Powers"
1858 = "Virtues"
1859 = "Dominions"
1860 = "Thrones"
1861 = "Cherubim"
1862 = "Seraphim"
1863 = "Caim"
1864 = "Belial"
1865 = "Beelzebub"
1866 = "Astaroth"
1867 = "Lucifuge"
1868 = "Marbas"
1869 = "Lucifer"
1870 = "Michael"
1871 = "Gabriel"
1872 = "Marut"
1873 = "Harut"
1874 = "Iblis"
1875 = "Azrael"
1876 = "Israfel"

1877 = "Your paid zone pass has %d days remaining."
1878 = "Swap the gear window"
1879 = "A quest is in progress."
1880 = "Available after a premium payment."
1881 = "The game will close in %d seconds."

# item upgrades
1882 = "You can use the %s item. Upgrade to a grade %s item?"
1883 = "Used on a %s item, this upgrades it to a grade %s item."
1884 = "You can use the %s item. Upgrade to the next tier?"
1885 = "Used on a %s item, this upgrades it to the next tier."
# the Korean already carries the English name in parentheses for these
1886 = "Horus"
1887 = "Seth"
1888 = "Maat"
1889 = "Osiris"
1890 = "Thoth"
1891 = "Nut"
1892 = "Geb"
1893 = "Shu"
1894 = "Ra"
1895 = "Ptah"
1896 = "Nun"
1897 = "This can be upgraded."
1898 = "This cannot be upgraded."
1899 = "This item is %s. The upgrade item cannot be used."
1900 = "Unique and Limited items cannot be upgraded."
1901 = "The %s item can be used at grade %s or higher."
1902 = "The %s item can be used with a domain total of %d or higher."
1903 = "The %s item can be used at level %d or higher."
1904 = "%s can be upgraded to the next tier. (Requires: grade %s or higher)"
1905 = "%s can be upgraded to the next tier. (Requires: domain total %d or higher)"
1906 = "%s can be upgraded to the next tier. (Requires: level %d or higher)"

# quest states
1907 = "(In progress)"
1908 = "(Waiting)"
1909 = "(Complete)"
1910 = "Quest "
1911 = "Grade"
1912 = "Turn off one-click attack"
1913 = "Server"
1914 = "Status info"
1915 = "Race info by server"
1916 = "Total sigils collected: %d`nSigils remaining: %d"
1917 = "You obtained %s."
1918 = "You can connect to the Blitz server while you are a premium user."
1919 = "Receive your premium item."
1920 = "Receive the selected premium item."
1921 = "Receive all premium items."
1922 = "That item can no longer be traded."
1923 = "No functional food"
1924 = "Luck + 10"
1925 = "Translates the other race's language"
1926 = "The name contains an inappropriate word. Please change it."

# server and character select help text
1927 = "Please select a server to connect to."
1928 = "Each server runs independently, but characters and items are shared and chat works across servers."
1929 = "Select a character to play. To create a new character press the Create Character button,"
1930 = "and to delete an existing character press the Delete button next to its name."
1931 = "To enter the game, select a character and press the Start Game button."
1932 = "Create a new Slayer, Vampire or Ousters."
1933 = "Create a new Slayer or Vampire."
1934 = "Decide your character's name, gender, face and color, then use the Reset button to set the stats."
1935 = "Use the Save and Load buttons to store and recall stat sets. Vampires cannot choose hair color or stats."
1936 = "Ousters cannot choose gender or skin color, and their stats are raised by hand."

1937 = "Discount price : "
1938 = "Calculating the repair cost."
1939 = "Confirm item drop"
1940 = "Do you really want to drop the item?"
1941 = "The enchant level is higher than the requirement, so it cannot be used."
1942 = "EXP + 20%"
1943 = "Abnormal play has been detected. You will be logged out in %d seconds."

# pet combiner
1944 = "That is not a pet item."
1945 = "A dead pet cannot be used."
1946 = "The pet's level is too low."
1947 = "The pet's level makes it ineligible as a combination or as material."
1948 = "That pet has already been combined."
1949 = "Use the pet combiner."
1950 = "Cancel using the pet combiner."
1951 = "A summoned pet cannot be used."
1952 = "Combination : "
1953 = "The pet combination failed."
1954 = "Do you want to erase your pet's combination option?"

1955 = "Rating"
1956 = "%d hours have passed since you started playing."
1957 = "%d hours have passed since you started playing. Please take a short break."
1958 = "Friend System"
1959 = "Friend Requests"
1960 = "Anyone under 18 cannot connect."

# boxes and cores
1961 = "There is not enough space to open the box."
1962 = "There are no items in the box."
1963 = "The box and key do not match."
1964 = "The Retard Yellow Core prevented the item from being destroyed."
1965 = "The Retard Release Core preserved the release option."
1966 = "The item mixing failed."
1967 = "Feeding removes the effects of the previous food."
1968 = "Limited items cannot be stacked or separated."

}

$TRANSLATIONS
