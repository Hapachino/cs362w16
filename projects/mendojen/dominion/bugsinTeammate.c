Bug:
unittest 1: getCost
All tests pass.

unittest 2: updateCoins
All tests pass

unitTest 3: isGameOver
Bug found when setting random piles of 3 to 0. Some pass and some fail, meaning that there is a bug
with one or more of the cards. My test indicates that the bug is when treasure map and/or sea hag is
set to 0. These 2 cards are the source of the bug.

unitTest 4: buyCard
All tests pass.

cardtest1: village
Changed function call to match teammates code.
Bug found when checking for numActions. The player playing the card does not get a +2 increase.

Card Test 2: salvager
My card test 2 was for the salvager card. Partner did not refactor this function, therefore I was unable 
to incorporate this test.

Card Test3: Smithy
Test fails when checking handCount and playedCardCount. 

Card Test 4:adventurer
Card test execution results in segmentation fault error.

Random tests
Random test: Smithy
Tests fail when checking handCount(decreased instead of increased), deckCount(should have stayed the same), and playedCardCount(incorrect increase) for current player.

Random test: Adventurer
Tests fail when checking current player's handCount (negative), discardCount(increased), and deckCount(decreased).
For my fixed tests, test hits a segmentation fault when calling adventurer card more than once.