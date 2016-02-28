/*****
 ** Author: Tim Robinson
 ** Date created: 2/27/2015
 ** CS 362, Oregon State University

===============================================================================
Isaiah (perotti) Report
===============================================================================

Title:
Playing Adventurer causes player to draw an additional treasure card.

Class:
Gameplay bug

Date:  2/27/2016         
Reported By:	Tim Robinson
Email:	robinsti@oregonstate.edu


Product: Dominion
Platform: Mac OSX 	Version: 10.11.3

Is it reproducible: Yes

Description
===========
When adventurer card is played, the player draws an additional treasure card.


Steps to Produce/Reproduce
--------------------------
1. Initialize 2-player game of Dominion.
2. Play adventurer card as first action (call adventurer function)
3. Count the players hand, it will have 1 more than expected.


Expected Results
----------------
Player draws 2 treasure cards from their deck.


Actual Results
--------------
Player draws 3 tresure cards from their deck.



Workarounds
-----------
None


Other information
-----------------
Test results can be seen in robinsti_unittestresults.out

===============================================================================
Will (thomasw) Report
===============================================================================


Title: 
Playing adventurer causes player to have 1 fewer card in their possession than 
expected.

Class:
Gameplay bug

Date: 2/27/2016
Reported By: Tim Robinson
Email: robinsti@oregonstate.edu

Product: Dominion
Platform: Mac OSX 	Version: 10.11.3

Is it reproducible: Yes

Description
===========
The player does not discard the expected number of non-treasure cards drawn.


Steps to Produce/Reproduce
--------------------------
1. Initialize 2-player game of Dominion.
2. Play adventurer card as first action (call adventurer function)
3. Count the cards in the player's hand, discard pile and deck. A card has
   disappeared.


Expected Results
----------------
Player has 2 additional cards in their hand.
Player's total number of cards remains constant.


Actual Results
--------------
Player has 2 additional cards in their hand.
PLayer has 1 fewer card than previously.


Workarounds
-----------
None


Other Information
-----------------
Test results can be seen in robinsti_unittestresults.out

 *****************************************************************************/