/********************************************
Bugs Found for Teammate 1: Huy Pham

Bug 1: 
While testing the smithyCard function, I discovered 
the following business rule violations (bugs):
  a. The last 3 cards from the player's deck are not
     moved into the player's hand (the final 2 cards 
     in the hand are not the correct cards from the 
     player's deck).
 
  b. The deck count does not decrease by 3 and the 
     hand count does not increase by 2.  

  c. The smithy card is not moved to the discard deck

  d. The discardCount does not increase by 1 (for the
     smithy card).  

Probable cause of a, b, and d above is the following 
line in smithyCard(): 
   for (i = 0; i < 4; i++)

This causes 4 cards to be drawn instead of the required
3 cards.  Bug 1c is likely caused by a problem in the 
design of discardCard, which moves discarded cards to 
the playedCards array, instead of the discard Deck. 

