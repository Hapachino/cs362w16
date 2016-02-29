/******************************************************************************
 ** Author: Tim Robinson
 ** Date: February 16, 2015

	Improvements in coverage over previous card unit testing:

	Previous Card Test Function Coverage
	------------------------------------
	playSmithy: 87.5%
	playAdventurer: 94.12%

	Random Card Test Function Coverage
	----------------------------------
	playSmithy: 100%
	playAdventurer: 100%

	Clearly there is an improvement in the coverage for both card functions. The
	use of random game state generation caused the corner cases missed in the
	manually created tests to be covered. 

	For the Smithy card, in the previous tests I failed to initialize a game that
	appropriately tested the card's play for different players. Previously I was
	only triggering some code for one of the players. In the random testing, I
	was able to produce a wider variety of valid game states, causing the missed
	code from the previous test to now be covered.

	For the Adventurer card, in the previous tests I failed to trigger the
	necessity of reshuffling the deck while undergoing the effect of the card.
	This is an important aspect to test, which I was able to trigger with the
	randomly generated game states.

	Due to the above considerations, I believe my random tests to be better tests
	than the tests I had previously. Randomly generating the game states gives
	me more confidence in the correct behavior (and bug-finding ability) in more
	diverse game states. Each test was able to find the (same) bugs that I 
	planted originally.

	A difficulty that I ran into while implementing the random tests for each 
	function was ensuring that valid game states were generated at random. The
	largest difficult in this regard was the adventurer card needing valid card
	numbers to be initialized in the hand, the deck, and the discard pile.
	Otherwise randomly generating the game state ended up being fairly 
	straightforward - I just had to carefully ensure that each attribute was
	appropriately randomly assigned.

 *****************************************************************************/
