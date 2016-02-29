Samuel Ford
CS362-400, Winter 2016
Assignment 5

Bugs Found when Testing Teammates' Code
=======================================

Teammate #1 (Joseph Vidal)
--------------------------

Bug Report
==========

Title: Smithy Can Draw Fewer Cards than Expected

Class: Bug

Priority: High

Date: 18 February 2016
Reported By: Sam Ford
Email: fordsam@oregonstate.edu

Is it reproducible?: Yes, under specific circumstances

Description
===========
When the index of the Smithy card in the player's hand is less than three (e.g. 0, 1, or 2), the Smithy card will draw fewer than three cards.  From my testing, the index of the Smithy card in the player's hand seems to act like an upper bound on the number of cards that are drawn when Smithy is played. As such, playing Smithy may only produce the correct behavior (+3 cards) when the Smithy card's index is 3 or greater.


Steps to Produce/Reproduce
--------------------------
Execute the smithyEffect() function with a handPos argument that is less than the number of cards Smithy should draw (three).


Expected Results
----------------
smithyEffect() should draw three cards from the player's deck.


Actual Results
--------------
smithyEffect() draws fewer than three cards from the player's deck.


Attachments
-----------
Attached is a smithyTest.c file, which contains a simple test to demonstrate this issue using handPos values from 0 to 4.



-------------------------------------------------------------------------------
Teammate #2 (Joshua Curtis)
---------------------------

Bug Report
==========

Title: Council Room Draws Incorrect Number of Cards for Player

Class: Bug

Priority: High

Date: 18 February 2016
Reported By: Sam Ford
Email: fordsam@oregonstate.edu

Is it reproducible?: Yes, under specific circumstances

Description
===========
The Council Room card only adds three cards to the player's hand but it should add four (per the card's specifications).  This happens every time the Council Room card is played (as long as there are enough cards available in the player's deck/discard pile), so it's easy to reproduce.


Steps to Produce/Reproduce
--------------------------
Play the Council Room card, providing it with enough cards in the player's deck and/or discard to draw four cards.


Expected Results
----------------
Four cards should be drawn from the player's deck and added to the player's hand.


Actual Results
--------------
Only three cards are added to the player's hand.


Attachments
-----------
Attached is a councilRoomTest.c file, which contains a simple test to demonstrate this issue.
