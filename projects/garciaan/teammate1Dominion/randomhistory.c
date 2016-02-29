/*
The randomtestadventurer.c program generates 1000 games, each time with random decks, hands, and discards for each player. We then randomly decide which player is the active player and attempt to play the adventurer card, which should go through the player's deck until 2 treasure cards are drawn, and discard the cards drawn that were treasure cards. We find that in randomtestadventurer.out, we see that although 0 out of 1000 tests are reported to have passed, it is because of the introduced bug in the playAdventurer() function where the drawn card variable is assigned inside the if-statement, so the player is never guaranteed to actually draw treasure cards, and the hand count is therefore incorrect as well.

The fact that none of the other print statements in the testAdventurer() function printed to the .out file means that the only unexpected result is in the player's hand count. The player's deck, discard, and played piles are as expected, and the non-current player's deck, discard, and hand are also as expected.

This file executed about 21% of dominion.c (not bad, since it's mostly just calling the playAdventurer() function) and about 60% of randomtestadventurer.c; since a lot of the code in randomtestadventurer.c is for what happens when a test fails, this coverage is about as expected.
*/

///////////////////////////////////////////////////////////////////////////////

/*
The randomtestcard.c program also generates 1000 games to test, each one with random decks, hands, and discards for each player. We randomly decide which player goes first and then play the smithy() card, which should simply draw three cards from the active player's deck into the active player's hand. In randomtestcard.out, we test the smithy card and find similar results to that in randomtestadventurer: the expected handCount and playedCardCount are not as expected, which again is because of introduced bug, outlined in refactor.c, where each time a card is drawn, the card at handPos is discarded, which effectively only lets the player keep 1 of his or her drawn cards.

Again, it is notable that when this particular condition is fulfilled, the other tests passed; the other player's deck, discard, and hand count are all as expected.

This file executed about 19% of dominion.c (again, since we're primarily just calling the playSmithy() card, this low percent is not alarming) and about 55% of randomtestcard.c. Because much of the code in randomtestcard.c lays within if statements that are only executed if certain conditions are not met (when the test fails a certain way), this lowish coverage is unsurprising.
*/
