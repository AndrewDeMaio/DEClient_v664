$ErrorActionPreference='Stop'
$scratch=$PSScriptRoot
. (Join-Path $scratch 'npcscript.ps1')

# NPC 17 - Kaiser Heinrich, zone 12 (X 222). Deputy commander of E.V.E's 2nd
# mercenary unit. Teaches SWORD and BLADE, and runs the barrier-seal event quest.
# Note his option separator is TAB TAB **, unlike Tanya (CR LF) and Zach (LF).
# Set-DEScript reuses whatever the source row had, so only the text is supplied.

# 4000 main menu. Answers: 1->4002, 2->4007, 3 TeachSkill SWORD,
# 4 TeachSkill BLADE, 5 give event quest, 6 reward, 7 cancel, 8->4006
Set-DEScript 4000 'Welcome, soldier. The situation is pressing, so I will keep this brief. Listen closely. My name is Kaiser Heinrich, deputy commander of the 2nd mercenary unit of E.V.E and officer in overall charge of this operation. The operation you are being committed to will most likely be the final and the fiercest war we fight against them. Now then, I will begin with a short briefing.' @(
 'Forgive me, but may I ask a question?'
 'Yes. Please begin the briefing.'
 'I have come to learn sword skills, Commander.'
 'I have come to learn blade skills, Commander.'
 'I would like to take on the Seal of the Barrier quest.'
 'I would like to claim my reward for the Seal of the Barrier quest.'
 'I would like to abandon the Seal of the Barrier quest.'
 'I have already been told the situation. Good day, Commander.'
)

# 4002. Answers: 1->4003, 2->4004, 3->4005, 4->4007, 5->4006
Set-DEScript 4002 'If you have not heard the briefing, you would do well to hear it before you set out. Given the situation, you should go into battle knowing it thoroughly. There is no telling how many vampires their number grows by in a single day. That makes what you do all the more important. If you have questions I will answer those that fall within what you need to know. What is it you want to ask?' @(
 'Who are you?'
 'Forgive me, but what sort of organisation is E.V.E?'
 'Where exactly are we?'
 'I will hear the briefing first.'
 'Good day, Commander.'
)

# 4003. Answers: 1->4004, 2->4005, 3->4007, 4->4006
Set-DEScript 4003 'As I said, my name is Kaiser Heinrich, deputy commander of the 2nd mercenary unit of E.V.E and the officer directing this operation. First go to Tanya for information on weapons, then draw the weapon you will carry from Zach. Once you leave this place no one can give you a weapon, and a weapon is your life. Do not neglect it. Any other questions?' @(
 'What sort of organisation is E.V.E?'
 'Where are we?'
 'I will hear the briefing.'
 'Then I will set out.'
)

# 4004. Answers: 1->4003, 2->4005, 3->4007, 4->4006
Set-DEScript 4004 'Hm. You have likely heard of us. E.V.E is an anti-vampire unit supported by the European Union and the Holy See. Outsiders take us for a counter-terrorist force under EU command. Our unit is not yet a year old. In truth the countries of Europe each ran their own special units for dealing with vampires, and the Bloody Monday incident of last year prompted a full unification, which is how this unit came to exist. For more detail, ask Smith of TEAM TWO, who is deployed in Eslanian. Any other questions?' @(
 'Forgive me, but who are you?'
 'Where exactly are we?'
 'Please begin the briefing.'
 'I will take my leave.'
)

# 4005. Answers: 1->4003, 2->4004, 3->4007, 4->4006
Set-DEScript 4005 'The virtual training ground is for those receiving their first instruction. It is set in a wide forest, and in forest fighting danger will be all around you. Checking your information and level between engagements will serve you well. Ctrl + I brings up the information window, Ctrl + K the level window. Once you reach level 5 you can learn skills from the instructors on the third floor of each guild in Eslanian. Any other questions?' @(
 'Who are you?'
 'What sort of organisation is E.V.E?'
 'I will hear the briefing first.'
 'Then I will set out.'
)

# 4006 sign-off. One answer.
Set-DEScript 4006 'I expect you to train and return in one piece. And go to Cain on the second floor of the Priest Guild for material on vampires. You should know the basics about what you will be facing. Good luck to you, soldier.' @(
 'Understood.'
)

# 4007 situation briefing. One answer.
Set-DEScript 4007 'Vampire movement has been detected here in Eslanian. According to our informants they are searching for something, and regrettably they move about unaffected by sunlight. Whether by coincidence or not, the vampire masters scattered across the world are said to be gathering in this region as well. Their appearance has us on the highest alert. When the creatures appeared, the Eslanian government found its regular forces had no firepower to match them. On learning the creatures were vampires they placed the region and the press under control. The Eslanian premier asked the Pope for help, and the Pope asked us. Our command, already uneasy at the masters moving, sent several agents in secret, and we have since lost contact with them. So this time every Slayer we can muster will be committed to the operation. With the press and the region sealed off, conditions for us are good. I regard this as the opportunity to show what we are capable of. I expect a great deal of you, soldier.' @(
 'Yes. Understood, Commander.'
)

# 4008 regional briefing. One answer.
Set-DEScript 4008 'Now a short briefing on the region. The operation will take place in Helea, in Eslania, known for its harsh mountains and its scenery, but so deep in the country that few people pass through. Most of the inhabitants do not live on tourist income; they get by by such means as slash-and-burn farming. Education there is poor and the standard of living the lowest in Eslania. Helea covers a wide area but has almost no flatland, so it holds only five settlements, barely large enough to be called towns. It appears the vampires have surfaced around these settlements. They lie only some 200km from the capital, but the mountains are severe and the roads poor, and that isolation is likely why sealing the region and the press proved easy. There are five villages in all, spaced roughly 10km apart around the city of Eslanian.' @(
 'It sounds like ideal ground for an operation. Please go on.'
)

# 4009 the masters. One answer.
Set-DEScript 4009 'Taking all our information together, the masters are said to be slipping into the region one after another. They rest in lairs prepared by their subordinates and set those subordinates to searching for something. Their lairs are arranged so as to encircle the villages. The problem is that all twelve are gathering. In all our records there is not one instance of all twelve masters assembling. We do not know what they are looking for, but it is of great importance, and it appears to be what allows the vampires of that region to move by day. If so, it is beyond question something enormous, for them and for us alike. Your task is to seize whatever it is the masters are seeking, and where possible to eliminate the masters themselves.' @(
 'I understand my orders. Any further instructions?'
)

# 4010 final orders. One answer.
Set-DEScript 4010 'The Slayers'' assembly point is the government building in the village. All weapons and equipment you will use are issued there first. Avoid acting alone, and move in groups wherever possible. A great many local people have already been lost to the vampires, and many more still cannot get out because the region is sealed. Do not forget that their safety is part of your task as well. See to it that no more people are left wandering, having lost home and family to vampires. This operation is not a matter of facing one or two vampires but numbers on an enormous scale, so take particular care. And should you be bitten, our regulations require you to take your own life. Good luck.' @(
 'Understood. Then I will take my leave.'
)

# 4011-4021 - idle lines chosen at random. No options.
Set-DEScript 4011 'Keep in mind above all else that your own life is what matters most.' @()
Set-DEScript 4012 'Recruit. Go to Zach, who handles weapons, and be sure to draw yours.' @()
Set-DEScript 4013 'I am Kaiser Heinrich. Have you ever heard of Kaiser''s law? Ha.' @()
Set-DEScript 4014 'I hold that the 2nd mercenary unit of E.V.E is the strongest of the eleven.' @()
Set-DEScript 4015 'Go to Cain on the second floor of the Priest Guild and you can obtain any number of books on vampires.' @()
Set-DEScript 4016 'You there. When you have time, read the works of Noam Chomsky. You will likely come to realise something.' @()
Set-DEScript 4017 'I have heard there exists a grimoire of Albertus that can break any barrier. Have you heard anything of it?' @()
Set-DEScript 4018 'Are we truly so short of men with the wit to break an Ousters barrier?' @()
Set-DEScript 4019 'Do not be too shaken by the sight before you. This is nothing at all.' @()
Set-DEScript 4020 'There are times I want to leave it all behind and go somewhere far away.' @()
Set-DEScript 4021 'When I watch the sun come up in the morning, I think to myself that I am alive another day.' @()

'Kaiser (NPC 17) core: 21 scripts updated'
