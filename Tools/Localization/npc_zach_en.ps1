$ErrorActionPreference='Stop'
$scratch=$PSScriptRoot
. (Join-Path $scratch 'npcscript.ps1')

# NPC 16 - Zach Vermeulen, zone 12 (X 217). Teaches GUN, issues starter weapons.
# Register kept gruff and military, as in the source.
# Option order is load-bearing: Triggers map AnswerID 1..N to the Nth option.

# 4101 main menu. Answers: 1->4109, 2->4102, 3->4103, 4->4104, 5->4105,
# 6 TeachSkill GUN, 7 TradeGQuestEventItem, 8->4108
Set-DEScript 4101 'Vampires are dead bodies to begin with, so they regenerate almost at once from any ordinary bullet or blade. You know that much already, rookie. That is the one principle you must never forget. More than a few have turned their backs on a vampire without finishing it off and paid for it. This instructor nearly died the same way. Well. You have the face of someone with a question. Anything to ask?' @(
 'There is something I would like to ask.'
 'Yes. Explain the difference between a sword and a blade.'
 'What exactly do AR, SMG, SG and SR mean?'
 'How does a cross differ from a mace?'
 'What weapons can I choose from?'
 'I have come to learn gun skills. Please teach me.'
 'I would like to trade in an instructor notebook.'
 'Understood. Keep up the good work, Mister Zach.'
)

# 4102 sword vs blade. Answers: 1->4103, 2->4104, 3->4105, 4->4108
Set-DEScript 4102 'Not knowing the difference between a sword and a blade. A prize rookie indeed. Still, it happens. A sword is relatively light and edged on both sides, so it can cut and thrust. But do not imagine a thrust works on a vampire. The body is already dead and feels no pain. Unless you run it clean through the heart and kill it outright, you may not get the weapon back out, and then the attacker is the one in danger. So whether the weapon is a light sword or a heavy blade, the safest course is to swing with everything you have and cut the thing in two, reducing what it can do and how fast it can move. A blade is edged on one side only, heavier than a sword and slower to swing, but it can cut a vampire in half in a single stroke. Understood?' @(
 'I would like to know the difference between AR, SMG, SG and SR.'
 'The cross and the mace seem much alike. How do they differ?'
 'Understood. Then I will choose a weapon.'
 'Understood. Keep up the good work.'
)

# 4103 firearm types. Answers: 1->4102, 2->4104, 3->4105, 4->4108
Set-DEScript 4103 'AR is the Assault Rifle. When people say a gun, they usually mean a rifle. Reasonable firepower, reasonable accuracy, an ordinary weapon, and the one most Slayers carry. Next. SMG is the Sub Machine Gun, the compact weapon used by counter-terrorist and special forces units. Easy to carry and light, though the firepower drops off somewhat. SG is the ShotGun, which as you know fires shot. Used at close range it will tear a vampire to rags in an instant. SR stands for Sniper Rifle, and as the name says, you use it to take a vampire''s head or heart off from a distance. What next?' @(
 'Zach, could you explain the sword and the blade?'
 'A cross and a mace? What sort of weapons are those? This is hardly the Middle Ages.'
 'Let me choose a weapon.'
 'Ha. You hardly need a weapon to deal with vampires. Keep up the good work.'
)

# 4104 cross and mace. Answers: 1->4102, 2->4103, 3->4105, 4->4108
Set-DEScript 4104 'The cross and the mace. Honestly, not my field. They are carried by Slayers who came out of the Vatican priesthood. The ones who carry a cross tend to be strong in healing and restoration, and I understand the mace belongs to those who use blessing magic. These weapons are made to order by the Holy See, and they are said to do terrible damage to a vampire. For the details, ask one of the other rookies who came from the Vatican. Next?' @(
 'Explain the difference between a sword and a blade.'
 'What exactly do AR, SMG, SG and SR mean?'
 'What weapons can I choose from?'
 'Thank you for the explanation, Mister Zach. Until next time.'
)

# 4105 weapon issue. Answers 1-8 are the weapon given, in this exact order:
# SWORD, BLADE, AR, SMG, SG, SR, CROSS, MACE. 9->4108, 10->4106.
Set-DEScript 4105 'Decided? You can change to another weapon later, so there is no need to agonise over it. Now then, which will it be? And do you know how to equip and use what you are issued? A soldier heading into battle who cannot fit or fire his weapon is no soldier at all. Watch the demonstration and make no mistakes in the field. Your issued weapon is in the inventory that appears when you press TAB. Bring up that inventory and the gear window together with CTRL + TAB, then drag each item from the inventory onto the matching slot in the gear window. If an equipped item shows in red, it means your stats fall short of what the item requires. If you want to use it properly, raise your stats. Remember that. You fire with a left mouse click. You are still a beginner, so train hard, press Ctrl + K to check your level, and once you reach level 5 you can learn skills from the instructors on the third floor of each guild in Eslanian.' @(
 'I will take the sword, light and fast.'
 'I will take the blade, heavy but hard-hitting.'
 'I will take the Assault Rifle (AR).'
 'I will take the Sub Machine Gun (SMG).'
 'I will take the Shotgun (SG).'
 'I will take the Sniper Rifle (SR).'
 'I will take the cross.'
 'I will take the mace.'
 'Ha. You hardly need a weapon to deal with vampires. Keep up the good work.'
 'Forgive me, Zach, but could you go over that once more?'
)

# 4106. Answers: 1->4102, 2->4103, 3->4104, 4->4105, 5->4108, 6->4113
Set-DEScript 4106 'Hm. This intake has a great many questions. Well then, soldier. What is it you want to know so badly?' @(
 'Mister Zach, explain the difference between a sword and a blade.'
 'What do AR, SMG, SG and SR stand for?'
 'How does a cross differ from a mace?'
 'I see. Then let me choose a weapon.'
 'Understood. Keep up the good work, Mister Zach.'
 'Looking in my inventory there are ampoules as well as the weapon. What are those for?'
)

# 4107 - shown when the player already drew a weapon. One answer.
Set-DEScript 4107 'What? The record says you were issued a weapon earlier. Is that wrong? Are you playing games with me?' @(
 'My apologies, Mister Zach. Please forgive me.'
)

# 4108 - sign-off. One answer.
Set-DEScript 4108 'For detailed information on weapons, go to Tanya and you can look it up easily on the computer. Be sure to call on her. Good luck to you.' @(
 'Thank you, Zach.'
)

# 4109. Answers: 1->4110, 2->4111, 3->4112, 4->4102, 5->4103, 6->4104,
# 7->4105, 8->4108
Set-DEScript 4109 'What is it you want to know, soldier?' @(
 'Who are you?'
 'What did you do before you came to E.V.E?'
 'I hear you served as a mercenary. I would like to know about that.'
 'Yes. Explain the difference between a sword and a blade.'
 'What exactly do AR, SMG, SG and SR mean?'
 'How does a cross differ from a mace?'
 'What weapons can I choose from?'
 'Understood. Keep up the good work, Mister Zach.'
)

# 4110. Answers: 1->4111, 2->4112, 3->4102, 4->4103, 5->4104, 6->4105, 7->4108
Set-DEScript 4110 'My name is Zach Vermeulen. At this command post I issue you a suitable weapon and a little money. Anything else you want to know?' @(
 'What did you do before you came to E.V.E?'
 'I hear you served as a mercenary. I would like to know about that.'
 'Yes. Explain the difference between a sword and a blade.'
 'What exactly do AR, SMG, SG and SR mean?'
 'How does a cross differ from a mace?'
 'What weapons can I choose from?'
 'Understood. Keep up the good work, Mister Zach.'
)

# 4111. Answers: 1->4110, 2->4112, 3->4102, 4->4103, 5->4104, 6->4105, 7->4108
Set-DEScript 4111 'I enlisted and went straight into Vietnam, and after that I covered most of the battlefields in the world. I finished as a mercenary with the French Foreign Legion and then kept to myself, until Deputy Commander Kaiser, who I had served alongside before, urged me to come here. Anything else?' @(
 'Who are you?'
 'I hear you served as a mercenary. I would like to know about that.'
 'Yes. Explain the difference between a sword and a blade.'
 'What exactly do AR, SMG, SG and SR mean?'
 'How does a cross differ from a mace?'
 'What weapons can I choose from?'
 'Understood. Keep up the good work, Mister Zach.'
)

# 4112. Answers: 1->4110, 2->4111, 3->4102, 4->4103, 5->4104, 6->4105, 7->4108
Set-DEScript 4112 'A mercenary is a soldier who serves for pay. The drawbacks are a shortage of loyalty and of genuinely capable men, but the practice has been used since ancient times to protect a population or to make up a shortfall in troops. Beyond loyalty and ability, a mercenary is hired with money, and will change sides as pay and terms dictate, caring little whether the flag is friendly or hostile. Because mercenaries are mostly foreigners, living alongside a country''s own soldiers or running joint operations often causes trouble. Today, besides the guard of the Holy See, the French Foreign Legion is the best known name in mercenary service. Clear now, soldier?' @(
 'Who are you?'
 'What did you do before you came to E.V.E?'
 'Yes. Explain the difference between a sword and a blade.'
 'What exactly do AR, SMG, SG and SR mean?'
 'How does a cross differ from a mace?'
 'What weapons can I choose from?'
 'Understood. Keep up the good work, Mister Zach.'
)

# 4113 ampoules. One answer.
Set-DEScript 4113 'There are two kinds of ampoule: the red healing ampoule and the blue mana ampoule. Watch the two bars at the top left of the interface, health and mana, and use them accordingly. If you have no belt, open your inventory and right-click to use one. You can also assign them to shortcuts: buy a belt from a shop and drag the ampoules onto it. Depending on the number of pockets you can assign them from F1 through to F8 and use them as shortcuts. When things look dangerous, put a healing ampoule into your system to restore health, and use the blue mana ampoule to top up the magic that your skills consume.' @(
 'Understood. I will not forget it in the field.'
)

# 4114-4124 - idle lines chosen at random. No options.
Set-DEScript 4114 'When you meet a vampire, destroy the heart first, then take the head off. Understood?' @()
Set-DEScript 4115 'In the end a gun, like a sword or a blade, has to become as familiar to you as your own limbs.' @()
Set-DEScript 4116 'When you address me, it is Mister Zach. Always.' @()
Set-DEScript 4117 'Rookies are to report to me by rank and name, then collect their weapon.' @()
Set-DEScript 4118 'You will keep silent during Deputy Commander Kaiser''s briefing.' @()
Set-DEScript 4119 'Handling a gun like that. What do you expect to achieve with an attitude like yours, soldier?' @()
Set-DEScript 4120 'If it were not for Deputy Commander Kaiser I would likely be a wreck by now. I owe that man a great deal.' @()
Set-DEScript 4121 'With my own hands, those creatures...' @()
Set-DEScript 4122 'I have been all over the world, but I have never seen a place where they run as freely as they do here.' @()
Set-DEScript 4123 'If you want to know more, go to Tanya. You can look up whatever weapon information you need yourself.' @()
Set-DEScript 4124 'Do not treat this as a game. Keep it in mind at all times that this is the real thing.' @()

'Zach (NPC 16): 24 scripts updated'
