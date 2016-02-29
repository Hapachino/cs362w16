/*
**FordSamDominion**

Bug Report 1
==========
 
Title: Smithy card is not discarded after use
Class: bug
 
Priority: high
 
Date: 2/27/2016
Reported By: Joseph vidal
Email: vidalj@oregonstate.edu
 
Is it reproducible?: Yes, each time the Smithy card is played.
 
 
Description
===========
Each time the Smithy card is played it appears to remain in the hand after having been used.
 
Steps to Produce/Reproduce
--------------------------
Play the Smithy card
 
Expected Results
----------------
Smithy card will be discarded
 
Actual Results
--------------
Smithy card is not discarded
 
Attachments
-----------
Test for Smithy card
randomtestcard.c 




Bug Report 2
==========
 
Title: Smithy card does not always draw all 3 cards
Class: bug
 
Priority: Low
 
Date: 2/27/2016
Reported By: Joseph vidal
Email: vidalj@oregonstate.edu
 
Is it reproducible?: Yes, when there are fewer than 3 cards in the deck
 
 
Description
===========
If there are fewer than 3 cards in the deck the Smithy card will draw the remaining amount but it will not call for a shuffle to get any remaining cards.
 
Steps to Produce/Reproduce
--------------------------
Play the Smithy card with deck that has 2 or fewer cards
 
Expected Results
----------------
The player will draw 3 cards
 
Actual Results
--------------
The player draws 2 or fewer cards
 
Attachments
-----------
Test for Smithy card
randomtestcard.c 



**CurtisJoshuaDominion**

Bug Report 1
==========
 
Title: Smithy card draws only two cards
Class: bug
 
Priority: High
 
Date: 2/27/2016
Reported By: Joseph vidal
Email: vidalj@oregonstate.edu
 
Is it reproducible?: Yes, when you play smithy
 
 
Description
===========
Smithy will only draw two cards from the deck
 
Steps to Produce/Reproduce
--------------------------
Play the Smithy card 
 
Expected Results
----------------
The player will draw 3 cards
 
Actual Results
--------------
The player draws 2 cards
 
Attachments
-----------
Test for Smithy card
randomtestcard.c 




Bug Report 2
==========
 
Title: Smithy card does not draw if end of deck is reached
Class: bug
 
Priority: Low
 
Date: 2/27/2016
Reported By: Joseph vidal
Email: vidalj@oregonstate.edu
 
Is it reproducible?: Yes, when there are fewer than 2 cards in the deck
 
 
Description
===========
If there are fewer than 2 cards in the deck the Smithy card will draw the remaining amount but it will not call for a shuffle to get any remaining cards.
 
Steps to Produce/Reproduce
--------------------------
Play the Smithy card with deck that has 1 or fewer cards
 
Expected Results
----------------
The player will draw 3 cards
 
Actual Results
--------------
The player draws 1 or fewer cards
 
Attachments
-----------
Test for Smithy card
randomtestcard.

*/