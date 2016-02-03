I found a bug in adventerer where it was not discarding the adventerer card.  I fixed this and 
the test now accounts for that change.

isGameOver(): This fails if a stack is empty, that wasn't initially included in the game.  
	I tested by reducing the stack of minion(not in the set of 10 cards in the given game) and
	when testing, it said the game was over, but it shouldn't have been.

scoreFor(): This looks at the contents of the player's hand, discard pile and deck to see what their score is.
	It was set to loop through the deck for a number of times equal to the size of the discard pile.
	This is now fixed.

	Not sure if this is a bug, but it doesn't count cards in the playedCards pile.  
	I decided to ignore this, as it's probably not a bug.  Just make sure to discard all playedCards
	before calling scoreFor().

fullDeckCount(): This function is straightup broken.  It actually checks the number of a specific card,
	not the total number of cards in the deck.

	refactored it to just add the deck/hand/and discard Counts.
	-note: this implementation is far from bulletproof, as it relies on the Count
	 values to be accurate.