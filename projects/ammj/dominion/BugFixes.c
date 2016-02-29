/**
 * Class: CS362 Winter 2016
 * Student:  Jeannine Amm
 * Assignment 5
 * BugFixes.c
 *
 * Bug 1:
 * Reported by Teammate1 (Janel Buckingham):
 * If a player has cards in their deck when Adventurer is played, but there are not sufficient
 * coin cards in the deck, the player will discard the remainder of the deck but not re-shuffle
 * to continue looking for coin cards.  This results in a deck of size 0 and an incorrect hand
 * count, although the handcount is not in keeping with a bug that only skips shuffling.  In that
 * case, it should not change if there are no coins in the deck, but it can still increment by one.
 *
 * Expected Results indicated by Teammate1:
 * Expected handcount to increase by two if shuffling is working the middle of adventurer card play,
 * or expected 0 handcount if shuffling is not working, but result is not keeping with either.
 *
 * Actual Results indicated by Teammate1:
 * Handcount incremented by one
 *
 *************
 * TestSetup:
 *************
 * An additional test was added to Cardtest 2 in the format Teammate1 outlined:
 * Steps to Produce/Reproduce
		--------------------------
		Found in random testing.
		Initialize a 2 player game.
		Manipulate the first player's deck so that it has a few cards but none are coin cards.
		Discard should have at least 2 coins in it. This would allow the game to shuffle correctly.
		Store the player's handcount.
		Store the player's deckcount.

		TestCode Added for confirmation:  See cardtest2.c lines 594-630
 *
 ***********************************************************************
 * Hypothesis generated during debug (See "Steps to debug" below for further detail)
 ***********************************************************************
 *
 * Handcount is not correct due to the following factors:
 * Played card not removed from hand
 * Played card not added to played pile
 *
 * Reshuffle of discard into deck was confirmed after shuffle but did occur in cardDrawn routine.
 * Shuffle performs no purpose on a deck with 0 cards as it only returns -1.
 *
 *
 ***********************************************************************
 * Hypothesis confirmed using fixed with the following actions:
 ***********************************************************************
 * First in cardtest2:
 * Played card was removed from hand and last card in hand put into it's place
 * Played card was added to the played pile.
 * Lines 1249 to 1251 were removed as decks are updated in drawCard:
			if (state->deckCount[player] < 1){//if the deck is empty we need to shuffle discard and add to deck
				 shuffle(player, state);
			}
 *
 *
 * Hypothesis was reconfirmed with randtomtestadventurer using fixed code highlighted 2
 * errors in testcode and once fixed all issues tested as a pass:
 * Line 608: removed
 * 	result->deckCount = random_number(0, 50);
 * Line 376 and Line 378 were calculating coin values not cards and were changed to
 * calcCoinCards instead of calcCoins to correct the bug in the testSuite:
 * 		int countDeckCoins = calcCoinCards(controlGame->deck[curPlayer],
					controlGame->deckCount[curPlayer]);
			int countDiscardCoins = calcCoinCards(controlGame->discard[curPlayer],
					controlGame->discardCount[curPlayer]);
 *
***********
Fixed Code:
***********
randomtestCard.c removed extraneous line 608: 	result->deckCount = random_number(0, 50);

int playAdventurer(struct gameState *state, int handPos)
{
	//int z, cardDrawn, drawntreasure;
	int temphand[MAX_HAND];
	int player = whoseTurn(state);

	// refactored version introduced bugs with not setting these values
	int drawntreasure=0;
	int cardDrawn;
	int z = 0, i=0;// this is the counter for the temp hand

	// add card to played pile
	state->playedCardCount++;
	state->playedCards[state->playedCardCount - 1] = state->hand[player][handPos];
	// put the last card in handPos
	state->hand[player][handPos] = state->hand[player][state->handCount[player] - 1];
	state->handCount--;

	while(drawntreasure<2){

		// attempt to drawCard and shuffle if deck < 0
		drawCard(player, state);
		cardDrawn = state->hand[player][state->handCount[player]-1];//top card of hand is most recently drawn card.

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		  drawntreasure++;
		else{
		  temphand[z]=cardDrawn;
		  state->handCount[player]--; //this should just remove the top card (the most recently drawn one).
		  z++;
		}

		// availableCards updated to fix endless looping
		availCards = state->deckCount[player] + state->discardCount[player];
	}

	z--;
	while(z-1>=0){
		state->discard[player][state->discardCount[player]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;

	}
}

****************************************************
Steps to Debug:
****************************************************
 * 1. Issue first verified by running cardtest2 with additional test added.
 * 2. gdb was used to step through and check the values of the variables to identify the cause
 * 4. Fixes put in place and confirmed as fix using cardtest2 and randomtestadventurer.
 *
 * Outputs from test:

	TEST FOR NO COINS IN DECK OR DISCARD
	Test 0: FAIL: HandCount: 4, Expected: 3
	Test 0: FAIL: playedCardCount: 0, Expected: 1
	Test 0: FAIL: playedCard: 0, Expected: 7
	Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
	Test 0: FAIL: DiscardCount: 5, Expected: 6, ControlHandCount: 4, PostHandCount: 4,
	ControlDeckCount: 3, PostDeckCount: 0, ControlDiscardCount: 3, PostDiscardCount: 5

	TEST FOR NO COINS IN DECK but coins in DISCARD
	Test 0: FAIL: HandCount: 10, Expected: 9
	Test 0: FAIL: playedCardCount: 0, Expected: 1
	Test 0: FAIL: playedCard: 0, Expected: 7
	Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
	Test 0: FAIL: DiscardCount: 3, Expected: 4, ControlHandCount: 8, PostHandCount: 10,
	ControlDeckCount: 4, PostDeckCount: 2, ControlDiscardCount: 4, PostDiscardCount: 3

 ********************************************************************************************
 * Bug 2:
 * Reported by Teammate2 (Paul Zotz)
 * Cards not discarded as expected.  Stacking the deck to ensure a predictable discard amount
 * results in one less card discarded than expected.
 *
 *************
 * TestSetup:
 *************
 * Current tests in cardTest2 confirmed the error.
 *
 ***********************************************************************
 * Hypothesis generated during debug (See "Steps to debug" below for further detail)
 ***********************************************************************
 *
 * Discardcount is not correct due to the following factors:
 *  testing for drawn cards does not account for the number of cards left in the deck
 *  and keeps attempting to draw cards and increment z when there are no cards left.
 *  	Line 1249: while(drawntreasure<2)
 *
 *  Line 1269 decrements z putting one less card into discard.
 * 		z-- (added bug) was putting one less card back into discard
 *
 ***********************************************************************
 * Hypothesis confirmed using fixed with the following actions:
 ***********************************************************************
 * First in cardtest2:
 *
 * Refactored to allow Line 1249 to test for available cards to draw more treasures from.
 * Line 1269: removed
 * 		z--;
 *
 * Hypothesis was reconfirmed with randtomtestadventurer using fixed code highlighted 2
 * errors in testcode and once fixed all issues tested as a pass:
 * Line 608: removed
 * 	result->deckCount = random_number(0, 50);
 * Line 376 and Line 378 were calculating coin values not cards and were changed to
 * calcCoinCards instead of calcCoins to correct the bug in the testSuite:
 * 		int countDeckCoins = calcCoinCards(controlGame->deck[curPlayer],
					controlGame->deckCount[curPlayer]);
			int countDiscardCoins = calcCoinCards(controlGame->discard[curPlayer],
					controlGame->discardCount[curPlayer]);
 *
***********
Fixed Code:
***********
randomtestCard.c removed extraneous line 608: 	result->deckCount = random_number(0, 50);

int playAdventurer(struct gameState *state, int handPos)
{
	//int z, cardDrawn, drawntreasure;
	int temphand[MAX_HAND];
	int player = whoseTurn(state);

	// refactored version introduced bugs with not setting these values
	int drawntreasure=0;
	int cardDrawn;
	int z = 0, i=0;// this is the counter for the temp hand
	int availCards = state->deckCount[player] + state->discardCount[player];

	// add card to played pile
	state->playedCardCount++;
	state->playedCards[state->playedCardCount - 1] = state->hand[player][handPos];
	// put the last card in handPos
	state->hand[player][handPos] = state->hand[player][state->handCount[player] - 1];
	state->handCount--;

	while(drawntreasure<2 && availCards > 0){

		// attempt to drawCard and shuffle if deck < 0
		drawCard(player, state);
		cardDrawn = state->hand[player][state->handCount[player]-1];//top card of hand is most recently drawn card.

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		  drawntreasure++;
		else{
		  temphand[z]=cardDrawn;
		  state->handCount[player]--; //this should just remove the top card (the most recently drawn one).
		  z++;
		}

		// availableCards updated to fix endless looping
		availCards = state->deckCount[player] + state->discardCount[player];
	}

	while(z-1>=0){
		state->discard[player][state->discardCount[player]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;

	}
}

****************************************************
Steps to Debug:
****************************************************
 * 1. Issue first verified by running cardtest2 with additional test added.
 * 2. gdb was used to step through and check the values of the variables to identify the cause
 * 3. Fixes put in place and confirmed as fix using cardtest2 and randomtestadventurer.
 *
 * Outputs from test:

	TEST FOR NO COINS IN DECK OR DISCARD
	Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
	Test 0: FAIL: DiscardCount: 5, Expected: 6, ControlHandCount: 4, PostHandCount: 4,
	ControlDeckCount: 3, PostDeckCount: 0, ControlDiscardCount: 3, PostDiscardCount: 5

	TEST FOR NO COINS IN DECK but coins in DISCARD
	Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
	Test 0: FAIL: DiscardCount: 3, Expected: 4, ControlHandCount: 8, PostHandCount: 10,
	ControlDeckCount: 4, PostDeckCount: 2, ControlDiscardCount: 4, PostDiscardCount: 3
 *
 ******************************************************************************************
 * Introduced Bugs fixed:
 *
		Adventurer: Add z--; Fixed in bug teammate2 found
		playSmithy: removed Line 1305:  updateCoins(player, state, 1) which added coins;
		Ambassador: Line 1386 reverted toFlag passed by gainCard to 0.
		Steward: Line 1439: reverted trashflag to 0
 */
