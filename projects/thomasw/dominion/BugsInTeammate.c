/*BUG REPORT 
Will Thomas
CS 362-400
2/26/2016

*******************************************************************************
REPORT 1: perotti
*******************************************************************************
Title: 
DOM-01: Playing Great Hall draws card from player 2's deck.    

Class:
Gameplay bug

Date: 2/26/2016          
Reported By: Will Thomas  
Email: thomasw@oregonstate.edu     


Product: Dominion                    
Platform: Linux Redhat                     

Is it reproducible: Yes

Description
===========
When player 1 plays the "Great Hall" card from their hand it draws a card from player 2's deck instead of player 1.


Steps to Produce/Reproduce
--------------------------
1. Launch a 2 player game of Dominion.
2. As player 1 play the Great Hall card from your hand.
3. Check your deck - count will be unchanged. Check hand - 1 new card.
4. End turn.
5. When player 2's turn starts check deck. Count will be decreased by 1 extra card.


Expected Results
----------------
1. 1 extra card in hand.
2. 1 extra action point.
3. 1 extra victory point.
4. Active player's deck decremented by 1.
5. Player 2's hand, deck and discard piles unchanged.


Actual Results
--------------
1. 1 extra card in hand of active player.
2. 1 extra action point for active player.
3. 1 extra victory point for active player.
4. active player's deck decremented by 0.
5. Player 2's deck decremented by 1.


Workarounds
-----------
None

*******************************************************************************
REPORT 2: robinsti
*******************************************************************************
Title: 
DOM-02: Adventurer card does not discard correct number of cards 

Class:
Gameplay bug

Date: 2/26/2016          
Reported By: Will Thomas  
Email: thomasw@oregonstate.edu     


Product: Dominion                    
Platform: Linux Redhat                     

Is it reproducible: Yes

Description
===========
When active player plays the "Adventurer" card it discards the incorrect number of cards.


Steps to Produce/Reproduce
--------------------------
1. Launch a game of Dominion.
2. As active player play Adventurer card.
3. If 2 treasure are not at the top of the deck then it discards fewer cards than it's supposed to.


Expected Results
----------------
1. Draw cards until 2 treasure cards are found.
2. Discard all non treasure cards.
3. Keep both treasure cards in hand.


Actual Results
--------------
1. 2 treasure cards added to hand
2. 1 or more cards are not discarded properly
3. 2 treasure cards are correctly added to hand.


Workarounds
-----------
None

