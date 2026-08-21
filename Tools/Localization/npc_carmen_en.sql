-- Carmen (NPCID 430, zone 64) - English dialogue
--
-- Option order is load-bearing: the Triggers table maps AnswerID 1..N to the
-- Nth option in Content, so options must stay in the same order and keep the
-- same count. Separator is a real LF + TAB + ** (LF + TAB + TAB + ** for the
-- donation scripts 8020-8023), matching the source bytes.
--
-- %(UserName) and %(GuildName) are named substitutions performed by the
-- server and are preserved verbatim.

-- 8000: main menu. AnswerIDs: 1 Heal, 2 Sell, 3 Buy, 4 portal, 5 duel zones,
-- 6 resurrect point, 7 borrow token, 8 return token, 9 quit.
UPDATE Script SET
 Subject='Welcome. How may I help you?',
 Content='I am wounded. Please heal me.\n\t**I need some supplies. Please show me what you have.\n\t**I would like to sell some things. Would you give me a fair price?\n\t**I would like to go to the Field Headquarters.\n\t**I would like to go to the free duel zone.\n\t**Set my recovery point.\n\t**I have come to borrow a Blood Bible token.\n\t**I would like to return my Blood Bible token.\n\t**I will come back another time. I have no business right now.'
 WHERE ScriptID=8000;

-- 8001-8008: idle lines, chosen at random by the RandomSay trigger
UPDATE Script SET Subject='Do take care. This place is always dangerous.' WHERE ScriptID=8001;
UPDATE Script SET Subject='I will pray that you return from here alive.' WHERE ScriptID=8002;
UPDATE Script SET Subject='If you leave a battle wound untreated there is a strong chance you will turn into a vampire, so have it healed quickly.' WHERE ScriptID=8003;
UPDATE Script SET Subject='I keep the things you need in stock. Just tell me what you are after.' WHERE ScriptID=8004;
UPDATE Script SET Subject='A great many people are badly hurt. We must move them and treat them quickly.' WHERE ScriptID=8005;
UPDATE Script SET Subject='Did you know? Blue Drop goes by another name: Adam''s Tears.' WHERE ScriptID=8006;
UPDATE Script SET Subject='There are a great many neighbours in need around us.' WHERE ScriptID=8007;
UPDATE Script SET Subject='May those less fortunate receive more kindness......' WHERE ScriptID=8008;

-- 8010: duel zones. AnswerIDs: 1 Olt (zone 1301), 2 Banatul (zone 1303), 3 quit.
UPDATE Script SET
 Subject='The free duel zones are Olt, for duels within your own race, and Banatul, where you may duel freely regardless of race. Please choose.',
 Content='I would like to go to Olt.\n\t**I would like to go to Banatul.\n\t**I will think it over and decide later.'
 WHERE ScriptID=8010;

-- 8020: donation offer. AnswerIDs: 1 personal, 2 team.
UPDATE Script SET
 Subject='There are still many around us waiting for a kind hand. We are collecting donations so that your kindness can reach them. %(UserName), would you take part in the collection as well?',
 Content='I would like to donate as an individual.\n\t\t**I would like to donate on behalf of my team.'
 WHERE ScriptID=8020;

-- 8021: personal donation. AnswerIDs: 1 donate, 2 quit.
UPDATE Script SET
 Subject='Thank you for your kindness. The amount you donate will be posted on the website. The contribution you make now, %(UserName), will be put to good use exactly where it is needed.',
 Content='I will make the donation.\n\t\t**I will call on you another time.'
 WHERE ScriptID=8021;

-- 8022: shown when the player has no team. AnswerIDs: 1 donate personally, 2 quit.
UPDATE Script SET
 Subject='I am sorry, %(UserName), but you are not currently in a team, or you are not a full member. If you do not belong to a team, please take part as an individual.',
 Content='Then I would like to donate as an individual.\n\t\t**Yes, I understand.'
 WHERE ScriptID=8022;

-- 8023: team donation. AnswerIDs: 1 donate, 2 quit.
UPDATE Script SET
 Subject='Thank you. As a member of %(GuildName), %(UserName), you are donating in the name of %(GuildName). The amount will be posted on the website under your team name, shown as a combined total. The contribution gathered in the name of %(GuildName) will be put to good use exactly where it is needed.',
 Content='I will make the donation.\n\t\t**I will call on you another time.'
 WHERE ScriptID=8023;
