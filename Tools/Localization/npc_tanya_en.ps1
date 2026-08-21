$ErrorActionPreference='Stop'
$scratch=$PSScriptRoot
. (Join-Path $scratch 'npcscript.ps1')

# NPC 26 - Tanya Serrano, zone 12 (X 207). Teaches HEAL and ENCHANT.
# Option order is load-bearing: Triggers map AnswerID 1..N to the Nth option.

# 4301 main menu. Answers: 1 ask-about-her, 2 virtual training, 3 weapon
# search, 4 goodbye, 5 learn skills.
Set-DEScript 4301 'I am Tanya Serrano. How can I help you?' @(
 'There is something I would like to ask you.'
 'I would like to take part in the virtual training system.'
 'I want to look up weapon information. Could you help me?'
 'It was good to meet you, Tanya.'
 'I have come to learn a skill.'
)

# 4302. Answers: 1 -> 4303, 2 -> 4304, 3 tutorial, 4 -> 4305
Set-DEScript 4302 'What is it you would like to know about me?' @(
 'Tanya, what is it you do here?'
 'How did you come to join E.V.E?'
 'I want to look up weapon information. Could you help me?'
 'It was good to meet you, Tanya.'
)

# 4303. Answers: 1 -> 4304, 2 tutorial, 3 -> 4305
Set-DEScript 4303 'I handle information strategy within E.V.E. At the moment I am stationed at this temporary command post, helping Slayers look up weapons more easily. Have you heard how things stand in Eslanian? Go and see Deputy Commander Kaiser and he will give you a full briefing.' @(
 'How did you come to join E.V.E?'
 'I want to look up weapon information. Could you help me?'
 'It was good to meet you, Tanya.'
)

# 4304 - her backstory. Answers: 1 -> 4303, 2 tutorial, 3 -> 4305
Set-DEScript 4304 'I once hacked into a CIA machine by chance and found a document marked as a state secret. What it contained was extraordinary: agents of the CIA entangled with vampires. Several of them were handling business during daylight hours on behalf of vampires who could not. There were transcripts of calls, ledgers, stacks of documents. Every click was a thrill. I kept reading, caught up in the thought that I had stumbled into something enormous, and then I was traced and my location was exposed. A careless mistake. People from a government agency came for me and bargained with me over what I had seen. They dug up a drug charge from two years earlier and threatened me with a life sentence. Joining E.V.E was the condition they offered, so I had little choice but to accept, and that is how I came to be here.' @(
 'Tanya, what is it you do here?'
 'I want to look up weapon information. Could you help me?'
 'It was good to meet you, Tanya.'
)

# 4305 - closing advice. Single answer.
Set-DEScript 4305 'If you need to be issued a weapon, go and see Zach. He knows as much about weapons as any computer, so you will get plenty of information from him. Oh, and one more thing. To see how an item you are carrying is used, press TAB to open your inventory, then click the magnifier button at the bottom. Click the item you want to know about and a short description of its use will appear. Keep that in mind. Well then, I wish you luck.' @(
 'Goodbye.'
)

# 4306 - teach menu. Answers: 1 HEAL, 2 ENCHANT, 3 -> 4303, 4 -> 4304,
# 5 tutorial, 6 -> 4305
Set-DEScript 4306 'Would you like to learn the Heal line, or the Enchant line?' @(
 'I will learn the Heal line.'
 'I will learn the Enchant line.'
 'Before skills, I would like to know what you do here.'
 'I will learn skills later. But tell me, how did you come to join E.V.E?'
 'Rather than training, could you help me look up weapon information?'
 'I will learn skills later. It was good to meet you, Tanya.'
)

# 4307-4317 - idle lines chosen at random. No options.
Set-DEScript 4307 'Just call me Tanya.' @()
Set-DEScript 4308 'A computer is only a computer. It is the person using it who is truly remarkable.' @()
Set-DEScript 4309 'Then again, plenty of people these days are worth less than a computer. A computer is at least honest.' @()
Set-DEScript 4310 'Use this computer if you want to look up weapon information.' @()
Set-DEScript 4311 'Do not forget to collect your weapon from Zach. I have seen more than a few people come back because they left without one.' @()
Set-DEScript 4312 'You cannot call a script kiddie a hacker.' @()
Set-DEScript 4313 'I am Tanya, in charge of information strategy.' @()
Set-DEScript 4314 'Ask me anything you do not know. I will give you as much information as I am able to.' @()
Set-DEScript 4315 'Have you had the general briefing from Deputy Commander Kaiser? If not, go and see him. He has a great deal of importance to tell you.' @()
Set-DEScript 4316 'Never forget to stay alert. I have seen plenty of people lose their heads for taking it easy.' @()
Set-DEScript 4317 'Zach knows as much about weapons as any computer. If you want to know more, going to him would help.' @()

'Tanya (NPC 26): 17 scripts updated'
