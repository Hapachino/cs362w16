/*
James Linnenburger
Oregon State University
Bug Fixes - CS362 Assignment 5

Bugs Discovered / Reported

1. Smithy Card:  Smithy card was not being removed from the player's hand when played.
(Reported by Jason Ridder)

Bug Fix:
The bug here was that the handPos was getting incremented with each drawCard call once the
Smithy card had been played.  This was mistakenly making the call to the discardCard point to
a card that was not the Smithy card.  To correct this, I removed the line of code from within
the loop to draw 3 cards:
		handPos++;

By making the handPos match with the Smithy card, the call to discardCard now will correctly
discard the Smithy instead of a different card.




2. Smithy Card:  Hand count of current player did not match up with what was expected.
(Reported by Marco Zamora)

Bug Fix:
This bug was caused by a mis-toggled trash flag in the discardCard function call.  Originally
the flag was set to 1 meaning that the card would be completely removed from the player's hand.
To fix this bug, I set the trash flag to 0 instead of 1.
		
           discardCard(handPos, currentPlayer, state, 0);

Now, the discarded card will go to the discard pile instead of the trash pile an remain
in the player's hand.



3. Adventurer Card: Hand counts don't match (extra card in hand)
(Reported by Marco Zamora)

Bug Fix:
The Adventurer card was drawing 3 new treasure cards instead of only 2.  This was causing the 
extra card in the hand reported by this bug.  To fix this bug, I had to change the following
line of code:
		while(drawntreasure<=2)  ----> changed to ----> while(drawntreasure<2) 

Now the Adventurer Card properly draws up to 2 treasures instead of 3.




4.  Adventurer Card:  Playing the adventurer card does not add an action 
(Reported by Marco Zamora)

Bug Fix:
This is a falsely reported bug.  The Adventurer card should not be adding an action
according to the rules of the card.  The card works as it should in regards to this.




5. Cutpurse Card:  Players are not discarding copper cards from their hands. 
(Reported by Jason Ridder)

Bug Fix:
This is a falsely reported bug.  The bug was actually in the testing code, not the
actual dominion code.  This was confirmed later by a follow up email from the 
original reporter.



6. Village Card:  card is not removed from player's hand when played
(Reported by: self)

Bug Fix:
This function was missing the discardCard call.  The following line was added to 
the playCardVillage() function:

	discardCard(handPos, currentPlayer, state, 0);

	

7. Village Card: number of actions is set to 2 instead of adding 2 
(Reported by: self)

Bug Fix:
The following line of code was changed from inside of the playCardVillage function:

state->numActions = 2;       was changed to   state->numActions += 2;

This allows the village card to add 2 to the current number of actions instead of just
setting actions to 2.




8.  Great Hall Card:  playing card does not actually increase action count.
(Reported by: self)

Bug Fix:
The following line of code was added to the playGreatHallCard function:
    state->numActions += 1;
The function had been missing this which was causing the issue.




9.  Minion Card:  Not all required players are forced to discard cards.
(Reported by: self)

Bug Fix:
The original (buggy) loop header to check all the players looked like this:
    for (i = currentPlayer; i < state->numPlayers; i++)
This made it so that only players after the current player would be checked.
This loop header was changed to:
    for (i = 0; i < state->numPlayers; i++)
This allows for all players to be checked and forced to discard if needed.



10.  Minion Card:  Cards in hand are not all discarded before drawing cards, and 
                   some of the wrong cards get discarded.
(Reported by: self)

Bug Fix:
The problem with the code here was that the player was drawing cards before 
discarding their hand.  When new cards were drawn, it was those cards that were
the first to get discarded because the handPos value never got updated.  I fixed
this problem by swapping positions of the loop that discards the entire hand and
the loop that draws 4 new cards so that the discarding happens before the drawing.



11. isGameOver() does not check the supply counts for card #25 (sea hag) or
    card #26 (treasure map) in its check for 3 empty supply counts.
(Reported by: self)

Bug Fix:
The loop to check for empty stacks was only checking from 0 - 25:
    for (i = 0; i < 25; i++)   //buggy version
This was the cause of the bug.  To fix the problem, I changed the 25 to 27
to accomodate all of the cards.
    for (i = 0; i < 27; i++)

