/*
Kyle Johnson
CS362
Assignment 3
bug1.c

My unit tests for the 4 functions did not uncover any new bugs.  I could have improved these tests
by designing the test suites to cover a broader range of random scenarios as well as more carefully crafted
custom scenarios where the outcomes are know.  As they are, I mostly focused on whether they performed as 
expected within normally expected game scenarios, so it is not surprising that I didn't discover any new
bugs resulting in fringe cases.

The unit tests for the cards did uncover the bugs I implemented in the smithy, adventurer, and village
cards, and each had multiple failed tests.

The bug introduced to the adventurerCard():

	counter for the temp hand loop initialized to z = 1 instead of 0, so player
	will have 1 extra card in hand that was not discarded after drawing for treasure cards,

did not show up as I expected.  While the hand and deck counts changed by different amounts than expected
which means I did not correctly anticipate how changing the temp hand loop would effect the outcome.

Another interesting bug I found while testing the cards is that the number of estate cards changed 
when they should have remained the same for the smithy and village cards:
estate = 6, expected = 8
FAILED - supply count does not match

I didn't have time to fully investigate why this was occurring, but the estate count passed for
the other modified cards so it was only an issue with the smithy and village cards.  

The other card bugs saw failure more in line with what I had anticipated and tried to introduce.  I also
tested a card I did not change, the council room, and all tests were passed successfully.  

Bug results from modified cards:

smithyCard() - drawCard() currentPlayer parameter changed to currentPlayer+1, which is the nextPlayer,
so the other player will draw three cards instead.

results:
TEST 1: +3 cards
hand count = 4, expected = 7
FAILED - player hand count does not match
deck count = 4, expected = 2
FAILED - player deck count changed
hand count = 3, expected = 0
FAILED - next player hand count does not match
deck count = 7, expected = 10
FAILED - next player deck count changed
played card count = 2, expected = 1

villageCard() - state->numActions changed from +2 to +1, so only 1 action will be added instead of 2.

results:
TEST 2: +2 actions
actions count = 2, expected = 3
FAILED - number of actions does not match



*/