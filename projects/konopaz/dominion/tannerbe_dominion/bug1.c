cardtest1.c: smithy card

	smithy card draws an extra card due to <= sign instead of < sign in for loop in smithyEffect function

cardtest2.c: adventurer card

	This bug was not added by me, but is also existing in the original dominion.c file (except it is present in the switch block for adventurer card)
	adventurer card is not discarded after it is played. Need to add the following line of code before return statement in order to correct:
	discardCard(handPos, currentPlayer, state, 0);
	also must pass in handPos int to adventurerEffect function


	Another thing I noticed wrong with the original dominion.c code is the following lines that are used to handle the adventurer card effect:
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
		  shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);

	This code is not problematic, but it is redundant. If the deck is empty, the shuffle function will simply fail with a return value of -1.
	Putting the discard pile back into the deck is handled by the drawCard function when you attempt to draw a card from an empty deck.
	So when the deck is empty, and the adventurerEffect function is called, the shuffle function is called and returns -1. Then drawCard is called 
	which detects the empty deck and handles it appropriately and the game continues without issue. 
	In summary, the if block can be removed.


	The last bug I found was that the deck can get corrupted (cards go missing) when the adventurer card is played. 
	This is because the cards that are drawn that are not treasures are not properly put back into the deck.
	This line of code:
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z]; 
	should be
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; 

cardtest3.c: village card

	no bugs found

cardtest4.c: embargo card

	The embargoEffect function does not check to see if the selected card is in play. 
	The card effects are played out regardless if the choice is valid.
