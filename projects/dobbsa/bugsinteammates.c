==gremmoaDominion==

Title: Other players do not draw cards when Council Room played
Class: Serious
Date: 2.28.16  
Reported By: Amy Dobbs
Email: dobbsa@oregonstate.edu

Product: dominion.c
Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
	  (mockbuild@c6b8.bsys.dev.centos.org)
	  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))        

Is it reproducible: Yes

Description
===========
When the Council Room card is played, the current player will gain four cards as intended. Other players will not gain any cards when they should draw one each.


Steps to Produce/Reproduce
--------------------------
Play the Council Room card.

Expected Results
----------------
The active player draws 4 cards and each other player draws 1.

Actual Results
--------------
The active player draws 4 cards and the other players draw none.

*****************************

Title: Treasure cards appear in discard pile
Class: Serious
Date: 2.28.16  
Reported By: Amy Dobbs
Email: dobbsa@oregonstate.edu

Product: dominion.c
Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
	  (mockbuild@c6b8.bsys.dev.centos.org)
	  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))        

Is it reproducible: Yes

Description
===========
When the Adventurer card is played, Silver and Gold cards are discarded.


Steps to Produce/Reproduce
--------------------------
Ensure that gold or silver will be drawn before copper cards. Play the Adventurer card.

Expected Results
----------------
The first two treasure cards of any type will be put into the hand. All other cards are put into discard.

Actual Results
--------------
The first two copper cards will be put into the hand. All other cards, including Silver and Gold, are put into discard.

*****************************
==winlawsDominion==
*****************************

Title: Treasure cards appear in discard pile
Class: Serious
Date: 2.28.16  
Reported By: Amy Dobbs
Email: dobbsa@oregonstate.edu

Product: dominion.c
Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
	  (mockbuild@c6b8.bsys.dev.centos.org)
	  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))        

Is it reproducible: Yes

Description
===========
When the Adventurer card is played, Silver cards are discarded.


Steps to Produce/Reproduce
--------------------------
Ensure that silver will be drawn before copper or gold cards. Play the Adventurer card.

Expected Results
----------------
The first two treasure cards of any type will be put into the hand. All other cards are put into discard.

Actual Results
--------------
The first two copper or gold cards will be put into the hand. All other cards, including Silver, are put into discard.

*****************************

Title: Council Room causes player to draw 5 cards and other players to draw none
Class: Serious
Date: 2.28.16  
Reported By: Amy Dobbs
Email: dobbsa@oregonstate.edu

Product: dominion.c
Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
	  (mockbuild@c6b8.bsys.dev.centos.org)
	  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))        

Is it reproducible: Yes

Description
===========
When the Council Room card is played, the player draws five cards instead of four and other players draw no cards.


Steps to Produce/Reproduce
--------------------------
Play the Council Room card.

Expected Results
----------------
The player draws 4 cards and other players draw 1 card each.

Actual Results
--------------
The player draws 5 cards and other players draw no cards.

*****************************
