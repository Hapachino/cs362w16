BugsInTeammates.c
Bug Report
==========

Title: After playing the adventurer card the hand count is one greater than expected. 7 instead of 6.
Class: bug

Priority: high

Date: 2/25/2016
Reported By: Joshua Curtis
Email: curtisjo@oregonstate.edu
 
Is it reproducible?: Yes when the adventurer card is played and the current player has five cards in their hand.


Description
===========
After the adventurer card is played from current player’s hand the players hand count should increase to six (plus two treasure minus the discarded adventurer card), but instead it increases to 7.

Steps to Produce/Reproduce
--------------------------
Play the adventurer card when the current player has five cards in their hand.

Expected Results
----------------
Current player’s hand count should equal 6

Actual Results
--------------
Current player’s hand count equals 7

Attachments
-----------
Test for the adventurer card
Cardtest2.c 



Teammate2: Joseph Vidal
Bug Report
==========

Title: council room card adds more cards to current players hand than it should
Class: bug

Priority: high

Date: 2/25/2016
Reported By: Joshua Curtis
Email: curtisjo@oregonstate.edu
 
Is it reproducible?: Yes when the village card is played and the current player has five cards in their hand.


Description
===========
After the council room card is played from current player’s hand the players hand count should increase to 8 (plus 4 card minus discarded council room card), but instead hand count is at 9.

Steps to Produce/Reproduce
--------------------------
Play the council room card when the current player has five cards in their hand.

Expected Results
----------------
Current player’s hand count should equal 8

Actual Results
--------------
Current player’s hand count equals 9

Attachments
-----------
Test for the council card
Cardtest3.c 
