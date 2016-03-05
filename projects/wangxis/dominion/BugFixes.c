Bugs found from teammate #1:
1.	smithy - hand count is correct but deck count also decrease one more than it should.
Fix: bug introduce by me. And it is fixed by change the line:   for (i = 0; i <= 3; i++) to for (i = 0; i < 3; i++).
2.	adventurer - hand drawn is one more than it should (3 instead of 2) while deck count is decreased by 4 instead of 2.
Fix: bug from me. It is fixed by changing the line while(drawntreasure<4)  to while(drawntreasure<2).
3.	village - action doesn't increase by 2 and player doesn't draw addtional card (should be 1)
Fix: this seems not the bug as the code actually does two thing. More test needed. 
4.	council_room - buy doesn't increase by 1 and players don't draw additional cards (should be 4 for the current player and 1 for everyone else)
Fix: the code does all these. This seems not the bugs, and more test needed. 

Bugs found from teammate #2:
1.	In smithyCard:   a). The last 3 cards from the player's deck are not moved into the player's hand. b).  The deck count does not decrease by 3 and the hand count does not increase by 2.  c)  The smithy card is not moved to the discard deck. d). The discardCount does not increase by 1.
Fix: a, b, d is from the  bug introduce by me. And it is fixed by change the line:   for (i = 0; i <= 3; i++) to for (i = 0; i < 3; i++). For bug1c, the discard card shouldn’t go to the discard card pile immediately after playing. It should go to the played pile first and goes to the discard pile at the end of turn.
2.	In  adventureCard:  a)   The temporary hand is not discarded properly. In other words, the number of cards in the discard does not match the number of cards in the temporary hand -2 for the 2 treasure cards that should be delivered to the player's hand.  b) .  The player's hand count does not increase by 2. This indicates an improper number of treasure cards  delivered to the player's hand (too many or too few). c) deckCount improperly decreased: This indicates again that either too many or too few cards were drawn from the deck into the temp hand.
Fix: these behaviors  are due to introduce bug from me. It is fixed by changing the line while(drawntreasure<4)  to while(drawntreasure<2).
3.	isGameOver() function:  fail to identify certain game over conditions. This occurs when three supply piles are emptied, if any of the empty supply piles is card #25 or 26 (sea_hag or treasure_map). Suspect the following line in isGameOver(): "for (i = 0; i < 25; i++)" should instead be "... i<27; ..." or better yet, less than some constant. 
Fix: Chang the line for (i = 0; i < 25; i++) to for (i = 0; i < 27; i++) since there are 27 cards instead of 25.

Bug introduce by me:
1.	smithyCard:  Change statement: for (i = 0; i < 3; i++) to: for (i = 0; i < =3; i++) 
Fix: fixed from teammate finding.
2.	adventurerCard: Change statement: while(drawntreasure<2) to: while(drawntreasure<4)
Fix: fixed from teammate finding.
3.	feastCard: Missing statement x = 1 before while loop
Fix: add the statement x + 1.
4.	ambassadorCard: Change statement: if (choice2 > 2 || choice2 < 0) to: if (choice2 > 2 && choice2 < 0)
Fix: change || back to &&
