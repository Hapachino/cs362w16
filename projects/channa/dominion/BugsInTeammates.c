Nancy Chan
CS 362
Winter 2016
Assignment 5: BugsInTeammates.c

/**********************************
teammate1Dominion - Andrew Calhoun
**********************************/

	unittest1: updateCoins()
		All tests passed.

	unittest2: fullDeckCount()
		All tests passed.

	unittest3: isGameOver()
		All tests passed.

	unittest4: scoreFor()
		***Bug found***
		2/2 tests failed.
		Scores do not equal expected values:

		----------------- Test 1 - Player 0:
		Adding the following to discard:
		    1 duchy
		    2 provinces
		    5 great halls
		    4 gardens
		    2 curses
		deckCount: 5
		discardCount: 14
		handCount: 5
		Player 0 score: 22, expected: 29

		----------------- Test 2 - Player 1:
		No changes and all cards in deck:
		deckCount: 10
		discardCount: 0
		handCount: 0
		Player 1 score: 0, expected: 3

	cardtest1: smithy
		Changes in my test to match teammate's refactored code:
			- changed playSmithy(p, &G, 5); to playSmithy(&G, p, 5);

		***Possible bug found***
			Given a deck of 10 cards, an empty discard pile, and a hand of 6 cards that includes smithy,
			3 cards are correctly drawn from the deck and added to the hand. However, the played smithy
			card is not added to the discard pile which remains empty. Whether or not this is an actual
			bug is up for debate as discussed here: https://piazza.com/class/iip31fywxe72b0?cid=103

			It is unclear if discardCard() should be true to its name and actually put a card in the
			discard pile as it may be the case that this happens in endTurn() instead.

	cardtest2: adventurer
		Changes in my test to match teammate's refactored code:
			- changed playAdventurer(&testG, p); to playAdventurer(&testG, p, 0, 0, 0, 0);

		***Bug found***
			----------------- Testing adventurer
			----------------- Player 0:
			----------------- Test 1: coppers at top of deck
			----------------- Initial counts
			DECK COUNT
			1
			1
			4
			4
			4
			DISCARD COUNT
			HAND COUNT
			4
			4
			1
			4
			4
			----------------- After playAdventurer
			DECK COUNT
			1
			1
			4
			4
			Card count: 4, Expected: 3
			Assertion failed: testG.deckCount[p] == count, file cardtest2.c, line 87

			After the adventurer card is played, only one treasure card (one copper which is represented
			by the 4) is revealed/drawn instead of two.

	cardtest3: cutpurse
		Changes in my test to match teammate's refactored code:
			- changed playCutpurse(p, &testG, 5); to cardEffect(cutpurse, 0, 0, 0, &testG, 5, 0);

		***Bug found***
			3/4 tests passed.
			3 tests passed: 4 hands with coppers, 3 hands with coppers, 2 hands with coppers.
			1 test failed: One of the players has zero coppers.
			Check if satisfied condition for revealing cards
			(j == handCount):
			j = 9, handCount: 10
			----------------- TEST FAILED!

			Playing the cutpurse card when all players have coppers in their hands results in all tests passing.
			Each other player correctly discards a copper.

			A bug appears when one of the players has a hand with no coppers.
			In this case, the player with no coppers to discard should be revealing his hand. The code to reveal cards
			in the hand is executed when (j == state->handCount[i]). However, j does not increment enough to satisfy
			that condition.

	cardtest4: remodel
		Changes in my test to match teammate's refactored code:
			- changed playRemodel(state, p, 1, toTest[i], 0); to cardEffect(remodel, 1, toTest[i], 0, state, 0, 0);

		***Bug found***
			choice1 is the card to trash
			choice2 is the card to gain
			Remodel makes the player trash a card to gain a card costing up to 2 more coins than the trashed card.
			A successful trash for gain returns 0. If unsuccessful, it returns -1.

			Most of the tests failed. Here are a few examples:
				choice1 cost: 2, choice2 cost: 2
				Result: -1, Expected: 0

				choice1 cost: 2, choice2 cost: 3
				Result: -1, Expected: 0

				choice1 cost: 2, choice2 cost: 4
				Result: 0, Expected: 0

				choice1 cost: 2, choice2 cost: 5
				Result: 0, Expected: -1

				choice1 cost: 2, choice2 cost: 6
				Result: 0, Expected: -1

/**********************************
teammate2Dominion - Jonathan Lagrew
**********************************/

	unittest1: updateCoins()
		All tests passed.

	unittest2: fullDeckCount()
		All tests passed.

	unittest3: isGameOver()
		All tests passed.

	unittest4: scoreFor()
		***Bug found***
		2/2 tests failed.
		Scores do not equal expected values:

		----------------- Test 1 - Player 0:
		Adding the following to discard:
		    1 duchy
		    2 provinces
		    5 great halls
		    4 gardens
		    2 curses
		deckCount: 5
		discardCount: 14
		handCount: 5
		Player 0 score: 22, expected: 29

		----------------- Test 2 - Player 1:
		No changes and all cards in deck:
		deckCount: 10
		discardCount: 0
		handCount: 0
		Player 1 score: 0, expected: 3

	cardtest1: smithy
		Changes in my test to match teammate's refactored code:
			- changed playSmithy(p, &G, 5); to playSmithy(&G, 5);

		***Possible bug found***
			Given a deck of 10 cards, an empty discard pile, and a hand of 6 cards that includes smithy,
			3 cards are correctly drawn from the deck and added to the hand. However, the played smithy
			card is not added to the discard pile which remains empty. Whether or not this is an actual
			bug is up for debate as discussed here: https://piazza.com/class/iip31fywxe72b0?cid=103

			It is unclear if discardCard() should be true to its name and actually put a card in the
			discard pile as it may be the case that this happens in endTurn() instead.

	cardtest2: adventurer
		Changes in my test to match teammate's refactored code:
			- changed playAdventurer(&testG, p); to playAdventurer(&testG);

		***Bug found***
			The adventurer card works correctly when there are treasure cards at the top of the deck.
			However, when the treasure cards are interspersed through the deck or at the bottom of the deck,
			the number of cards in the discard pile is one fewer than expected.

	cardtest3: cutpurse
		Changes in my test to match teammate's refactored code:
			- changed playCutpurse(p, &testG, 5); to cardEffect(cutpurse, 0, 0, 0, &testG, 5, 0);

		***Bug found***
			3/4 tests passed.
			3 tests passed: 4 hands with coppers, 3 hands with coppers, 2 hands with coppers.
			1 test failed: One of the players has zero coppers.
			Check if satisfied condition for revealing cards
			(j == handCount):
			j = 9, handCount: 10
			----------------- TEST FAILED!

			Playing the cutpurse card when all players have coppers in their hands results in all tests passing.
			Each other player correctly discards a copper.

			A bug appears when one of the players has a hand with no coppers.
			In this case, the player with no coppers to discard should be revealing his hand. The code to reveal cards
			in the hand is executed when (j == state->handCount[i]). However, j does not increment enough to satisfy
			that condition.

	cardtest4: remodel
		Changes in my test to match teammate's refactored code:
			- changed playRemodel(state, p, 1, toTest[i], 0); to cardEffect(remodel, 1, toTest[i], 0, state, 0, 0);

		***Bug found***
			choice1 is the card to trash
			choice2 is the card to gain
			Remodel makes the player trash a card to gain a card costing up to 2 more coins than the trashed card.
			A successful trash for gain returns 0. If unsuccessful, it returns -1.

			Most of the tests failed. Here are a few examples:
				choice1 cost: 2, choice2 cost: 2
				Result: -1, Expected: 0

				choice1 cost: 2, choice2 cost: 3
				Result: -1, Expected: 0

				choice1 cost: 2, choice2 cost: 4
				Result: 0, Expected: 0

				choice1 cost: 2, choice2 cost: 5
				Result: 0, Expected: -1

				choice1 cost: 2, choice2 cost: 6
				Result: 0, Expected: -1
