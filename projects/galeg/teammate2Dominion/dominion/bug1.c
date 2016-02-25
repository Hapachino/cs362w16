Scott Williams
CS 362 - Assignment 3
bug1.c


unitTest1.c: updateCoins()
    I had some initial problems comparing values, but once I fixed that there were no bugs.

unitTest2.c: discardCard()
    No bugs found during testing.

unitTest3.c: buyCard()
    No bugs found during testing. All buys are successful as long as player has enough coins to make the purchase.

unitTest4.c: endTurn()
    No bugs found during unit testing.

cardTest1.c: playAdventurer()
    Adventurer card will give two drawnTreasures instead of one, causing the loop to terminate early. This can cause problems with seeding in the game, as well as the ratio.

cardTest2.c: playSmithy()
    Smithy does not properly add 3 cards due to an incrementation error. Rather than using a post-increment (i++), the code is using a prefix increment (++i), this results in only two cards
    being given. During tests, a +4 is taken into account because the card is granted to the player. If the player does not have 4 more cards in their hand during a test, then the test fails.

cardTest3.c: playVillage()
    The village is not properly discarded, which causes it to remain in the player's hand.

cardTest4.c: playMinion()
    The minion was really buggy. The minion properly increments actions, but removes coins from the player's stash under choice 1. Under choice 2, it does not properly grant cards or discard them. This
    results in other players ending up with additional cards, on top of the one's they already have in their hand and does not force other players to discard their cards. The current way the system is set up as well,
    it does not appear that cards are properly incremented into player hands.

