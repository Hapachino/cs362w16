Nancy Chan
CS 362
Winter 2016
Assignment 5: BugFixes.c

/**********************************
teammate1Dominion - Andrew Calhoun
**********************************/
At first, Andrew's tests were reporting bugs for adventurer and smithy. However, when I examined Andrew's
adventurer test, I discovered that his test was only testing an internal implementation of adventurer and
not my implementation. By setting a breakpoint at my adventurer function in my dominion.c, it confirmed
my suspicions that my code was not actually being executed in his test since there were no calls to my function
either directly with playAdventurer() nor indirectly with the cardEffect function.

Andrew's smithy test was resulting in a segmentation fault. Upon closer inspection, I learned that his call
to my smithy function had not been changed to match my refactored implementation. The parameter order needed
to be corrected. Once corrected, the segmentation fault no longer occurred. There was one last remaining issue
in which a conditional statement in his test needed to be corrected as well. Once corrected, expected values
equaled actual values from my smithy function.

In summary, Andrew's test suite did not find any bugs in my code. Rather than fixing bugs in my code, I instead
assisted in fixing bugs in the tests.

/**********************************
teammate2Dominion - Jonathan Lagrew
**********************************/
Bug 1: scoreFor() - "Scores do not equal the expected values."

	Jonathan's bug report mentioned fullDeckCount() using the number of curses and not accounting for the number of gardens. 
	I used GDB to set a breakpoint at the scoreFor() function. I stepped through the scoreFor() function and printed 
	"fullDeckCount(player, 0, state)". The number printed was indeed the number of curses and not the number of gardens.
	I changed the code to "fullDeckCount(player, 10, state)" in 3 places (3 for loops: hand, discard, and deck), 10 being the
	card index for gardens. Printing "fullDeckCount(player, 10, state)" gave the number of gardens this time.

	However, the changes did not enable the code to pass the tests. I noticed that the for loops for the discard and deck 
	used the same conditions: "i < state->discardCount[player]". I changed the conditon for the deck to be "i < state->deckCount[player]".
	This solved the problem of computing victory points from the deck when the discardCount and deckCount were not equal.

	In GDB, printing "fullDeckCount(player, 10, state) / 10" revealed that this always evaluated to 0 because the numerator
	would be the number of gardens (4) divided by the denominator 10. Thus, gardens was having no effect on the score.

	According to: http://dominioncg.wikia.com/wiki/Gardens, the gardens card "does nothing until the end of the game, when it is worth
	1 victory point per 10 cards in your Deck (counting all of your cards – your Discard pile and hand are part of your Deck at that point).
	Round down; if you have 39 cards, Gardens is worth 3 victory points."

	Removing gardens from the 3 for loops in scoreFor() and adding the following code to adhere to the logic of gardens fixed the bug:

	  // Number of gardens
	  gardens_count = fullDeckCount(player, 10, state);
	  // All cards in deck (discard and hand are part of the deck at this point)
	  allDeck_count = state->handCount[player] + state->discardCount[player] + state->deckCount[player];
	  // Gardens is worth 1 VP for every 10 cards in your deck (rounded down)
	  gardens_effect = (allDeck_count / 10) * gardens_count;

	  // Add gardens effect
	  score = score + gardens_effect;

Bug 2: smithy - "The test found that the wrong amount of the player's cards after playing the smithy card. Instead of 
	3 cards there should of been 4. This also affected the deckCount and discard pile for the counts."

	I used GDB to set a breakpoint at playSmithy. As I stepped through the function, I saw that "drawCard(currentPlayer, state);"
	was called 4 times instead of 3 times, resulting in an extra card being drawn. I fixed the bug by changing the "<=" to "<" in
	"for (i = 0; i <= 3; i++)".

	Continuing to step through the function, I saw that the trash flag had been set in discardCard(handPos, currentPlayer, state, 1);
	which was not correct as smithy should be discarded after play, not trashed. Fixing the flag only required changing the 1 to a 0.

Bug 3: adventurer - "...non-treasure cards that are drawn after the card is played are not properly accounted for."