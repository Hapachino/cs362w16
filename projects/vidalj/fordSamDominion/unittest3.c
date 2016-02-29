/* Test the buyCard() function
   NOTE: If the correct preconditions are met, buyCard() should purchase the
   card that the player specifies and add it to their discard pile.  The preconditions for buying a card are as follows:

   * Player must have at least one buy available.
   * supplyCount of card must be 1 or greater.
   * The player must have coins greater than or equal to the cost of the card.
*/
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "fordsamTest.h"

#define P1 0
#define P2 1
#define CARD feast

void testBuyCard() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  struct gameState initialState = {0};
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};

  printf("----- Testing buyCard() -----\n");

  /* Set state.numBuys to 0, supplyCount of CARD to 5, and coins to 10 */
  printf("----- Test: numBuys = 0, supplyCount = 5, coins = 10\n");
  state.numBuys = 0;
  state.supplyCount[CARD] = 5;
  state.coins = 10;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = buyCard(CARD, &state);

  /* Should not modify state when numBuys < 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should not modify game state when numBuys < 1",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when numBuys < 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when numBuys < 1",
    (result == -1)
  );

  /* Set state.numBuys to 2, supplyCount of CARD to 0, and coins to 10 */
  printf("\n----- Test: numBuys = 2, supplyCount = 0, coins = 10\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.numBuys = 2;
  state.supplyCount[CARD] = 0;
  state.coins = 10;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = buyCard(CARD, &state);

  /* Should not modify state when supplyCount < 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should not modify game state when supplyCount < 1",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when supplyCount < 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when supplyCount < 1",
    (result == -1)
  );

  /* Set state.numBuys to 2, supplyCount of CARD to 5, and coins to 0 */
  printf("\n----- Test: numBuys = 2, supplyCount = 5, coins = 0\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.numBuys = 2;
  state.supplyCount[CARD] = 5;
  state.coins = 0;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = buyCard(CARD, &state);

  /* Should not modify state when coins < cost */
  testCount += 1;
  passCount += fakeAssert(
    "Should not modify game state when coins < cost",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when coins < cost */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when coins < cost",
    (result == -1)
  );

  /* Set state.numBuys to 2, supplyCount of CARD to 5, and coins to 10 */
  printf("\n----- Test: numBuys = 2, supplyCount = 5, coins == 10\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.numBuys = 2;
  state.supplyCount[CARD] = 5;
  state.coins = 10;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = buyCard(CARD, &state);
  compareState(&state, &preState, &gsc);

  /* Should add card to discard pile when bought */
  testCount += 1;
  passCount += fakeAssert(
    "Should add bought card to player's discard pile",
    (containsCard(CARD, state.discard[P1], state.discardCount[P1]))
  );

  /* Should increase discardCount by 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should increase player's discardCount by 1",
    (state.discardCount[P1] == preState.discardCount[P1] + 1)
  );

  /* Should reduce supplyCount of card by 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should reduce supplyCount of card by 1",
    (state.supplyCount[CARD] == preState.supplyCount[CARD] - 1)
  );

  /* Should reduce coins by cost of purchased card */
  testCount += 1;
  passCount += fakeAssert(
    "Should reduce player's coins by cost of purchased card",
    (state.coins == preState.coins - getCost(CARD))
  );

  /* Should reduce numBuys by 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should reduce numBuys by 1",
    (state.numBuys == preState.numBuys - 1)
  );

  /* Should not affect other players */
  testCount += 1;
  passCount += fakeAssert(
    "Should not affect other players",
    (gsc.handChanged[P2] == 0
    && gsc.deckChanged[P2] == 0
    && gsc.discardChanged[P2] == 0
    && state.handCount[P2] == preState.handCount[P2]
    && state.deckCount[P2] == preState.deckCount[P2]
    && state.discardCount[P2] == preState.discardCount[P2])
  );

  /* Should return 0 when a card is bought */
  testCount += 1;
  passCount += fakeAssert(
    "Should return 0 when a card is bought",
    (result == 0)
  );

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);
}

int main() {
  testBuyCard();
  return 0;
}
