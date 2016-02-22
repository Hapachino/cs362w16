


/***********************************
* Testing Jason Ridder's dominion card functions
* smithyCardFunc
* Bugs:
	ERROR: hand count for player 0:  Expected: 162, Actual: 163
	ERROR: deck count for player 0:  Expected: 84, Actual: 83
* Description:
	It seems like there is an extra card from the deck in the hand.
*********************/

Extra drawCard on line 684. Deleted. Show below.

for (i = 0; i < 3; i++)
   {
   drawCard(currentPlayer, state);
   }
      drawCard(currentPlayer, state);  //LINE 684 - Removed to fix bug.
      
/***********************************
* adventurerCardFunc
* Bugs:
	Player playing adventurer: #0
	ERROR: played card counts:  Expected: 1, Actual: 0
	ERROR: Score for 0: Expected: 73, Actual: 79
	ERROR: hand count for player 0:  Expected: 161, Actual: 176
	ERROR: deck count for player 0:  Expected: 72, Actual: 71
	ERROR: discard count for  for player 0:  Expected: 13, Actual: 14
* Description:
	It seems like the card is not counted as played or discarded.
	Elsewhere in the function, cards are getting lost or moved to the
	wrong place, because several deck numbers are off.
	Finally, the test does not finish all testing because it hits a seg fault soon
	after test #12.
*********************/

Line 662 update from this:
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-2]; //LINE 662

To this:
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //LINE 662

Negative 2 update to negative 1, cardDrawn now take from top of card.
