/***********************************
* Testing Jason Ridder's dominion card functions

There is a bug in the smithyCardFunc. These are the following errors I get:
	ERROR: hand count for player 0:  Expected: 162, Actual: 163
	ERROR: deck count for player 0:  Expected: 84, Actual: 83
	It seems like there is an extra card from the deck in the hand.

For the adventurerCardFunc, there were several warnings, as an example:
	****TEST 1****
	Player playing adventurer: #0
	ERROR: played card counts:  Expected: 1, Actual: 0
	ERROR: Score for 0: Expected: 73, Actual: 79
	ERROR: hand count for player 0:  Expected: 161, Actual: 176
	ERROR: deck count for player 0:  Expected: 72, Actual: 71
	ERROR: discard count for  for player 0:  Expected: 13, Actual: 14
	****FINISHED TEST 0****

	It seems like the card is not counted as played or discarded.
	Elsewhere in the function, cards are getting lost or moved to the
	wrong place, because several deck numbers are off.
	Finally, the test does not finish all testing because it hits a seg fault soon
	after test #12.
	
* Testing Jim Linnenburger's dominion card functions
**Bug in playing smithy:
		ERROR: playedCardCount is incorrect. Expected: 338 Actual: 337. 
	Bug in playing adventurer:
		ERROR: hand counts should match. Pre: 73, Post: 74
		ERROR: number of actions should match. Pre: 3, Post: 2

***********************************/
