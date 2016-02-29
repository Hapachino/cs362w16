Bugs found by team mate:

unitTest 3: isGameOver
Bug found when setting random piles of 3 to 0. Some pass and some fail, meaning that there is a bug
with one or more of the cards. My test indicates that the bug is when treasure map and/or sea hag is
set to 0. These 2 cards are the source of the bug.

Fix:


cardtest1: village
Changed function call to match teammates code.
Bug found when checking for numActions. The player playing the card does not get a +2 increase.

Fix:
state->numActions = state->numBuys + 2;
is corrected to
state->numActions = state->numActions + 2;

Card Test2:
feastCard
Test on feastCard seemed like it hit an infinite loop. The test executed but once it called feastCard, the test did not stop.

the variable x which it the condition of the loop was set to zero after gaining a card solving the infinite loop.

Card Test3: Smithy
Test fails when checking handCount and playedCardCount. 

Random tests
Random test: Smithy
Tests fail when checking handCount(decreased instead of increased), deckCount(should have stayed the same), and playedCardCount(incorrect increase) for current player.

Fix:
    for (i = 0; i < 3; i++){
	    drawCard(currentPlayer, state);
        discardCard(handPos, currentPlayer, state, 0);
	}	
is corrected to
    for (i = 0; i < 3; i++){
	    drawCard(currentPlayer, state);
	}		

Card Test 4:adventurer
Card test execution results in segmentation fault error.

Random test: Adventurer
Tests fail when checking current player's handCount (negative), discardCount(increased), and deckCount(decreased).
For my fixed tests, test hits a segmentation fault when calling adventurer card more than once.

Fix:
    state->hand[currentPlayer][state->handCount[currentPlayer]]
changed to
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer-1]];


