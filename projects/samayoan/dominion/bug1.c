Bug 1: 
	The players score is not always correctly calculated.

The failure: 
	The scoreFor() method sometimes does not calculate the player's score when
	there are point cards (estates, gardens, great_hall) in the deck. If the point
	cards are only in the hand and discard piles, the score will be calculated correctly.
	The conditions required for the bug to show are as follows:
		1. The total number of discard cards (discardCount) is greater than
			the total number of cards in the deck pile (deckCount) OR  
		2. The total number of discard cards (discardCount) is less than
			the total number of cards in the deck pile (deckCount) and the deck has point
			cards at the higher indexes. 
		3. The deck pile contains at least one card that would contribute to their final score.
 
How I found it:
	In my test code I have two test cases that catch this bug. One test cases test the scenario where
	the amount of cards in the deck pile is less that the amount in the discard pile. The other test
	case tests the scenario where the deck pile has more than the discard pile. Upon running both
	portions of test code, the calculated scores came back different from what I calculated manually.
	
Part of code or usage case that causes the bug:
	In the scoreFor() method in dominion.c there are 3 for loops. The last for loop uses the wrong
	max value (it should use state->deckCount but instead uses state->discardCount).
	
	//score from deck
  	for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
	...........

	This means that if the discardCount is less or greater than the deckCount, only some cards from the 	deck pile will be counted or some -1 values will be counted in the final score, resulting in an
	incorrect score for that player.



Bug 2:
	The players score is not always correctly calculated when Garden cards are present.
	The effect of the Garden card is not applied.

The failure: 
	The scoreFor() method does not count all cards when applying the Garden card's effect. The
	Garden card is supposed to give the player 1 point for every 10 cards he or she has (regardless of
	type). However, scoreFor() does not apply the effect at all.

How I found it:
	I have a test case that uses two Garden cards, and 28 Province cards. The expected score then is
	170 because 168 come from the Province cards, then 2 from the Garden cards because the deck has two
	sets of 10 cards. The actual score return is 168.

Part of code or usage case that causes the bug:
	The code at fault is a combination of how scoreFor() calls fullDeckCount() and also the fact that 
	fullDeckCount() does not have a way to count all cards regardless of type. Firstly, scoreFor() calls
	fullDeckCount() passing 0 for the card type, meaning that the number returned is the total count of 
	curse cards, not all cards. Secondly, the fallDeckCount() method doesn't have a way to count all 
	cards, so there is no "quick fix" that can be made to scoreFor(). The fix would be a medium sized
	refactoring of the fullDeckCount() method.
