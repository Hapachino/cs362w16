unittest1.c for getCost() - no bugs found.

unittest2.c for updateCoins() - no bugs found.

unittest3.c for isGameOver() - no bugs found.

unittest4.c for fullDeckCount() - no bugs found.

cardtest1.c for smithy

	bug 1 = Player 0 plays smithy expecting to draw 3 cards into hand.
			Player 0 only draws 2 cards into hand.

	bug 2 = Related to bug 1, Player 1 deck has 1 more card remaining than expected.

	bug 3 = smithy shows as being played by player 0 and player 1,
			but only player 0 has used smithy.

cardtest2.c for adventurer

	bug 1 = The adventurer card remains in player hand after being played.

	bug 2 = An action card has been lost in the adventure from deck.
			It is not in discard.

cardtest3.c for council room

	bug 1 = The council room draws 3 cards into player 0 hand instead of 4.

	bug 2 = Related to bug 1, player 0 deck has 2 cards remaining instead of 1.

	bug 3 = Player 1 shows council room played card but player 1 has not played.

cardtest4.c for mine

	bug 1 = mine is not trashing the chosen card and replacing with greater card
            for example replacing copper with silver. 

