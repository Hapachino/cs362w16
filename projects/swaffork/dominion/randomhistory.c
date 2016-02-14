/*
In randomtestadventurer.out, we see that although 0 out of 1000 tests are reported to have passed, it is because of the introduced bug in the playAdventurer() function where the drawn card variable is assigned inside the if-statement, so the player is never guaranteed to actually draw treasure cards, and the hand count is therefore incorrect as well.

The fact that none of the other print statements in the testAdventurer() function printed to the .out file means that the only unexpected result is in the player's hand count. The player's deck, discard, and played piles are as expected, and the non-current player's deck, discard, and hand are also as expected.

This file executed about 21% of dominion.c (not bad, since it's mostly just calling the playAdventurer() function) and about 60% of randomtestadventurer.c; since a lot of the code in randomtestadventurer.c is for what happens when a test fails, this coverage is about as expected.

In randomtestcard.out, we test the ____ card.
*/
