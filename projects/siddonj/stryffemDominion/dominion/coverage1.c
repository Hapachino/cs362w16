/*
	Author: 	Martin Stryffeler
	Filename:	coverage1.c
	Date:		2/2/2016

Line Coverage

Together, my tests provide line coverage of 36.77% of the dominion.c code. Looking through 
the gcov file, this makes sense, as a lot of functions are not relevant to my tests and are 
never called. Much of the missed code is gameplay functions that are not covered by my tests, 
such as playCard, endTurn, and getCost. 

Looking at the cards I did test, steward, smithy, and village have full line coverage, 
although the village card function is called only once. The adventurer card does not have full
coverage; looking over the gcov file, I see that the deck is never empty, so shuffling never 
occurs. In addition, the drawn cards are all treasures, so we are not testing the setting aside 
and discarding of non treasure cards. I thought that I was testing this case, so viewing the 
actual coverage data was enlightening.

For the unit tests, scoreFor, isGameOver, upDateCoins, and gainCard all have 100% line coverage.
This is not too surprising, as I had access to the functions while writing the tests, and could
easily choose inputs to reach each different state. While I have achieved 100% coverage here, I
still cannot assume that I have caught every bug in these functions.


Branch Coverage

43% of branches were executed, but only 33% of branches are taken at least once. Only 25% of calls
are executed. The low number of branches executed and taken makes sense, as again we are only testing
a few cards and functions. We are not even touching the 27 branch but otherwise trivial getCost
function. The cardEffect switch statement also shows that we are visiting only a few cards. These 
of course affect our branch percentage, but they don't have any bearing on our coverage of the
chosen functions and cards. The low percentage of calls executed makes sense, as we are working in a
highly simulated environment and ignoring many of the normal gameplay functions. This can of course
be improved but is outside the scope of the assignment.

The smithy, village, steward, gainCard, updateCoins, and isGameOver functions all have 100% block and
execution coverage.

The scoreFor function calls 100% of blocks, but executes only 86% of them. This is due to the bug in the
scoreFor function causing it not to actually iterate through deck cards, but the test could still be 
improved to execute all blocks despite the bug. It is interesting to note that the scoreFor function has 
100% line coverage because all lines are executed, but does not provide full branch coverage because the 
if clauses are never true.

In the adventurer function, 100% of blocks are called, but only 64% are executed. These are the missed 
branches mentioned above. The adventurer is never called with an empty deck, and never draws non 
treasure cards in my tests. This results in the subpar branch execution coverage of 64%. Of the tests
that I have written, the adventurer card tests have the most to be improved upon. Adding additional test
cases that explicitly start with an empty deck, and that seed the deck with varying cards would likely 
be enough to rectify the tests and achieve 100% line and branch coverage.


Boundary Coverage

The boundary coverage of my unit tests seems pretty good. Most of the unit tests explicitly test
boundary conditions such as 1/0 cards remaining in the deck or supply pile, or all possible 
combinations of decks / hands / etc.

The boundary coverage of my card tests could be improved. The card tests could be improved by testing
what happens when the card is the last card in the hand before being played, and by testing having too
few or just enough cards in the deck to draw.

*/