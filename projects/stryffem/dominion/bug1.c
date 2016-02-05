/*	Author: 	Martin Stryffeler
	Filename:	bug1.c
	Date:		2/2/2016

Unit Tests

Unit test 2 exposed a bug in the scoreFor() function which causes it to miscount the score of cards in the deck.

The loop that iterates over deck cards and adds their score to the total iterates from 0 to the size of
the discard pile rather than the size of the deck. 

In my tests, this causes the score of the deck to not be counted if the deck is larger than the discard 
pile, but if the discard pile is larger than the deck, then the function will iterate outside the bounds 
of the deck array.

Unit tests of the isGameOver, updateCoins, and gainCard functions have discovered no bugs so far.


Card Tests

Card test 1 exposes a bug in the Smithy card effect. This bug miscounts the number of cards drawn, causing
only two cards to be drawn rather than the required three. This is a bug that I introduced in assignment 2.
The effects of this bug are that the player's deck count and hand count are both off by one.

Card test 2 exposes a bug in the Adventurer card effect. This bug miscounts the number of coins drawn,
adding extra cards to the player's hand. This is a bug that I introduced in assignment 2. The effects of
this bug are that the player's hand count, discard count, and deck counts are off after using Adventurer.

Card test 3 exposes a bug in the Village card effect. This bug sets the number of available actions to the
wront value. This corresponds to a bug that I introduced in assignment 2. This bug causes the number of 
actions to be set to the number of coins + 2 rather than the number of actions + 2.

Card test 4 has uncovered no bugs so far.

*/