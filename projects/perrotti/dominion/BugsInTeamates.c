/*BUG REPORT 
Isaiah Fentress
CS 362-400
2/27/2016

*******************************************************************************
REPORT 1: thomasw
*******************************************************************************
Title: 
DOM-01: Playing Village card only adds one action for the player, not two

Class:
Gameplay bug

Date: 2/27/2016          
Reported By: Isaiah Fentress
Email: perrotti@oregonstate.edu     

Product: Dominion                    
Platform: Linux Redhat                     

Is it reproducible: Yes

Description
===========
When a player (chosen at random) plays the "Village" card from their hand, it only adds one additional action instead of two.


Steps to Produce/Reproduce
--------------------------
1. Launch a 2+ player game of Dominion.
2. As any player, play the Village card from your hand.
3. Your action count will increase by 1 (NET of 0 in full game because action was used to play card)
4. End turn.


Expected Results
----------------
1. 1 extra card in hand.
2. 2 extra action points (for a NET of 1 after discard)
4. Active player's deck decremented by 1.
5. Active player's hand size the same (one discard one draw).
6. Active player's discard incremented by 1.
5. All other player's hands remain unchanged.

Actual Results
--------------
1. 1 extra card in hand.
2. (BUG) 1 extra action points (for a NET of 0 after discard)
4. Active player's deck decremented by 1.
5. Active player's hand size the same (one discard one draw).
6. Active player's discard incremented by 1.
5. All other player's hands remain unchanged.


Workarounds
-----------
None


*******************************************************************************
REPORT 2: robinsti
*******************************************************************************
Title: 
DOM-02: For player 1, the Smithy card draws 4 cards instead of 3

Class:
Gameplay bug

Date: 2/28/2016          
Reported By: Isaiah Fentress  
Email: perrotti@oregonstate.edu     


Product: Dominion                    
Platform: Linux Redhat                     

Is it reproducible: Yes

Description
===========
When a player other than player 1 plays the "Smithy" card, 4 cards are drawn instead of 3


Steps to Produce/Reproduce
--------------------------
1. Launch a 2 player game of Dominion.
2. As the second player, play the Smithy card.
3. You will now see that 4 additional cards were added to player 2's hand (minus the discard of smithy).


Expected Results
----------------
1. Smithy card is played
2. Draw 3 cards from active player's deck.
3. Smithy card discarded from active player's hand.
4. Player now has 3 new cards.


Actual Results
--------------
1. Smithy card is played
2. (BUG) Draw 4 cards from active player's deck (if any player ther than player 1).
3. Smithy card discarded from active player's hand.
4. Player now has 3 new cards.


Workarounds
-----------
None

