/**
 * Bugs.c
 * Student: Jeannine Amm
 * Email:  ammj@oregonstate.edu
 * Class: CS362w2016
 *
 * unittest1:
 *
 * unittest2:
 * Tested:  updateCoins();
 * No bugs found using unittest2
 *
 * unittest3:
 * bug1 (low severity)
 * a small percentage of the time, the deck is shuffled and cards are in the same position as before.
 * The more cards that are shuffled the lower the percentage of occurance.
 *
 * unittest4:
 * bug1:  getWinner calls get scoreFor (int player, struct gameState *state) which returns
 * 	the wrong score.  scoreFor calls fullDeckCount() which is intended to calculate the number
 * 	of cards in the deck but instead counts the instance of the card it is passed.  In the
 * 	calculation of gardens it uses the result of fullDeckCount divided by 10 for the
 * 	multiplier.  When the # of total cards are higher and gardens is in the deck the difference
 * 	between the actual score and the score calculated with score for grows.
 *
 * cardtest1: playSmithy
 * 	No bugs found with test
 *
 * cardtest2: playAdventurer
 * bug1:  program crashes due to z not intialized to a value
 *  test started but crashed Program: resulted from z not initialized in
 *  refactor of playAdventurer causing it to crash when a card drawn was
 *  not a treasure card.
 *
 * bug2:  program crashes due to drawnTreasure not being initialized
 * 	after correction for above and re-run of test
 *	test started but again crashed Program.
 *	resulted from drawnTreasure not being initialized to a value in
 *	playAdventurer causing it initialize with a random value.  Occurred
 *	in refactor.
 *
 * bug3:  Adventurer card is never put onto the played pile
 *
 * bug4:  program throws segmentation fault when temphand attempts to copy to discard
 * pile. (introduced z-- bug)
 *
 * bug5: (introduced bug) temphand never fully added to discard due to
 * line 1267: z--; // originally line 1262
 *
 *Test1:
 *	after correction and re-run:
 *  cardtest2: cardtest2.c:182: verifyResults: Assertion `activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] + addedCards - 1' failed.
 *
 *	after replacing with output instead of assert to continue:
 *	cardtest2: cardtest2.c:197: verifyResults: Assertion `activeGame->playedCardCount >= 1' failed.
 *	traced the bug to not calling discardCard to discard adventurer
 *
 *	after replacing with output instead of assert to continue:
 *	cardtest2: cardtest2.c:209: verifyResults: Assertion `activeGame->playedCards[activeGame->playedCardCount - 1] == adventurer' failed.
 *	traced the bug to not calling discardCard to discard adventurer
 *
 *	after replacing with output instead of assert to continue:
 *	cardtest2: cardtest2.c:259: verifyResults: Assertion `activeGame->hand[curPlayer][i] == copper || activeGame->hand[curPlayer][i] == silver || activeGame->hand[curPlayer][i] == gold' failed.
 *	traced the bug to adventurer card not being removed from hand.  coin cards are
 *	added to unexpected indexes as a result
 *
 *	after replacing with output instead of assert to continue:
 *	cardtest2: cardtest2.c:294: verifyResults: Assertion `activeGame->discardCount[curPlayer] != discardCheck' failed.
 *	traced the bug to the introduced bug z-- causes it to never enter the discard loop.
 *
 *	Test2:  0 discardCount and 0 deckCount
 *	Result:  Hard Crash
 *	When test2 was entered, the program crashed and shutdown when it ran out of cards.  This is due to
 *	getting into an endless loop when there are 0 cards to draw from and 0 discards to shuffle in.  The
 *	function never checks if the result is 0, just keeps re-attempting the draw and shuffle. With every
 *	attempt it adds another element to temphand until temphand grows past allocated memory and overwrites
 *	a value that causes the program to crash.
 *
 *	Test4:  no treasure cards in discard or deck
 *	Result:  expected hard crash but reported: Test 0: FAIL: HandCount: 6, Expected: 5
 *	This resulted in finding a new bug.  When deckCount reached 0 and discardCount reached 0 it reported
 *	the tested the last card in the hand as the drawn card.  If the last card in the hand a coin
 *	it adds 1 to drawn treasures otherwise it discards it thinking it is a drawn card with no value.
 *
 *	To ensure the program runs through all testing the tests have been setup to ensure the last card in the hand
 *	is a treasure card.  To confirm hard crashes the if statement on lines 435 and 486 can be commented out.
 *
 *	When running on linux it was able to run-through, print-out errors and successfully complete.
 *	When running on flip a segmentation fault occured in Test 3.  Another side effect of the introduced
 *	but z--.  When a coin was found it flipped the index to -1 and tried to write
 *	to temphand[-1].  Since the area is write protected it threw SIGSEGV and aborted the program.
 *
 *	To allow the program to run and produce results for unittestresult.out z-- was moved outside the loop.
 *
 * cardtest3:
 * bug1:  baron is never put onto the played pile
 * this makes baron available again the next turn
 *
 * bug2: bonus coins are added to coins instead of variable to store bonus
 * gameState->coins are reset in playCard function before buy state to value in hand
 * variable to store bonus is passed into updateCoins to add bonus coins
 * in the current configuration gameState->coins are cleared and no bonus coins are
 * added
 *
 * bug3:
 * estate supply decrements twice when estate card drawn from supply
 * This error was caused by call to gainCard decrementing estate supply and
 * Baron routine also decrementing estate supply
 *
 * Test1:
 * 	cardtest3: cardtest3.c:192: verifyResults: Assertion `postCount == preCount - 1' failed.
 * 	This bug is due to baron not being putting on played pile
 * 	cardtest3: cardtest3.c:201: verifyResults: Assertion `activeGame->playedCards[activeGame->playedCardCount -1] == baron' failed.
 * 	This bug is due to baron not being putting on played pile
 *	cardtest3: cardtest3.c:210: verifyResults: Assertion `activeGame->playedCardCount > controlGame->playedCardCount' failed.
 * 	This bug is due to baron not being putting on played pile
 *	cardtest3: cardtest3.c:234: verifyResults: Assertion `activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] - 2' failed.
 * 	This bug is due to baron not being putting on played pile
 *	cardtest3: cardtest3.c:257: verifyResults: Assertion `result->coinBonus == 4' failed.
 *	This bug is due coins not added to bonus but added to state->coins in error.  state->coins clears
 *	before buy phase.
 *  cardtest3: cardtest3.c:379: verifyResults: Assertion `memcmp(controlGame, activeGame, sizeof(struct gameState)) == 0' failed.
 *  This bug is due to update to state->coins instead of adding them to bonus.
 *
 * Test2:
 * 	FAIL: Post Hand Baron Count: 1, Expected: 0
 *	FAIL: Last Card Played: 0, Expected: 15
 *	FAIL: playedCardCount: 0, Expected: 1
 *	FAIL: Hand Count: 4, Expected: 3
 *	cardtest3: cardtest3.c:300: verifyResults: Assertion `activeGame->supplyCount[estate] == (controlGame->supplyCount[estate] - 1)' failed.
 *	This error was caused by call to gainCard decrementing estate supply and Baron routine also decrementing estate supply
 *
 *Test3:
 *	FAIL: Post Hand Baron Count: 1, Expected: 0
 *	FAIL: Last Card Played: 0, Expected: 15
 *	FAIL: playedCardCount: 0, Expected: 1
 *	FAIL: Hand Count: 10, Expected: 9
 *	FAIL: Estate Supply Count: 10, Expected: 11
 *
 *Test4:
 *	FAIL: Post Hand Baron Count: 2, Expected: 1
 *	FAIL: Last Card Played: 0, Expected: 15
 *	FAIL: playedCardCount: 0, Expected: 1
 *	FAIL: Hand Count: 6, Expected: 5
 *	FAIL: Estate Supply Count: 10, Expected: 11
 *
 *Test5:
 *	FAIL: Post Hand Baron Count: 3, Expected: 2
 *	FAIL: Last Card Played: 0, Expected: 15
 *	FAIL: playedCardCount: 0, Expected: 1
 *	FAIL: Hand Count: 9, Expected: 8
 *
 *Test6:
 *	FAIL: Post Hand Baron Count: 2, Expected: 1
 *	FAIL: Last Card Played: 0, Expected: 15
 *	FAIL: playedCardCount: 0, Expected: 1
 *	FAIL: Hand Count: 8, Expected: 7
 *	FAIL: Estate Supply Count: -1, Expected: 0
 *	This failure highlights another effect of the gainCard decrementing estate supply twice.  isGameOver()
 *	is intended to run when supply count is 0 but since it jumps from 1 to -1 due to the bug isGameOver never
 *	runs unless supply Count is set to 2.
 *
 * cardtest4:
 * bug1:
 * TEST1 FAIL: Reported total Actions: 7, Expected total Actions: 1 (Control: 1, Bonus Actions Calculated: 0)
 * line 998: for loop cycles 3x when it should only cycle 2
 * line 1008: runs if not a treasure or a victory and adds to actions
 * when card is dead it falls into line 1008
 * due to line 998 it runs one more time than revealed cards and adds 1 extra action
 *
 * bug2: the card that is played is never added to the played pile it is left in the hand
 * Sample test fail:
 * TEST1 FAIL: Reported playedCardCount: 0, Expected: 1 (Control: 0, Cards Played: 1)
 * TEST1 FAIL: Reported last playedCard: 0, Expected: 19
 * TEST2 FAIL: HandIndex to check for bonus card: 4 card: 19, Expected: 4
 *
 * bug3: the revealed cards are never added to the discard pile
 * TEST1 FAIL: Reported discardCount: 0, Expected: 2 (Control: 0 + Revealed Card(s): 2)
 *
 * bug4:
 * When nextPlayer's deck count + nextPlayer's discard count combined are greater than 1
 * the following lines decrement the count for the deck 4x.  The expected decrement
 * is 2x (one for each card):

  			tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
  			state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
  			state->deckCount[nextPlayer]--;
  			tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
  			state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
  			state->deckCount[nextPlayer]--;

 * this is due to the -- used in the deck index also decrementing the count value
 * followed by the line to decrement the count value
 * sample test fail:
 * TEST1 FAIL: Reported deckCount: 6, Expected: 8 (Control: 10 - Revealed Card(s): 2 (Expected may include Discard: 0)
 *
 * bug5:  bonus coins are added to coins instead of variable to store bonus
 * gameState->coins are reset in playCard function before buy state to value in hand
 * variable to store bonus is passed into updateCoins to add bonus coins
 * in the current configuration gameState->coins are cleared and no bonus coins are
 * added
 */
