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

Bug 2: while testing the adventurerCard function, I 
discovered the following bugs: 
    a.  2 treasures are not delivered to the hand

    b.  The player hand count is not increased by 2

    c.  The player deck count is not decreased by the
        correct amount. 

The likely cause of all 3 test failures is the same bug:
an incorrect number of treasure cards being moved from the
deck to the hand.  After briefly examining the code the 
issue is probably the line: "while(drawntreasure <1)" in 
adventurerCard.  This should be "while(drawntreasure <=1)" 
or "while(drawntreasure <2)"

Bug 3: while testing villageCard I discovered the following
bug: 
     a.  improper discard

This is likely due to the same problem as in bug 1c, above. 

Bug 4: while unit testing the isGameOver() function I 
discovered the following bug: 
     a.  isGameOver fails to identify certain game over
         conditions. This occurs when three supply 
         piles are emptied, if any of the empty 
         supply piles is card #25 or 26 (sea_hag or
         treasure_map).

Suspect the following line in isGameOver():
"for (i = 0; i < 25; i++)" should instead be
"... i<27; ..." or better yet, less than some 
constant. 



   
