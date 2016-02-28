/* Test the Smithy card
   NOTE: Smithy should:
     * Draw three cards from the player's deck and add them to their hand.
*/
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "fordsamTest.h"

#define P1 0
#define P2 1
#define HANDPOS 2

int testSmithy() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};

  printf("----- Testing Smithy card -----\n");

  /* Set up state for two players */
  printf("----- Test: 2 players, P1 deckCount = 5, P1 handCount = 4\n");
  state.whoseTurn = P1;
  state.numPlayers = 2;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = silver;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = copper;
  state.deckCount[P1] = 5;
  state.hand[P1][0] = baron;
  state.hand[P1][1] = mine;
  state.hand[P1][2] = smithy;
  state.hand[P1][3] = copper;
  state.handCount[P1] = 4;
  state.discardCount[P1] = 0;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playSmithy(&state, HANDPOS, P1);
  compareState(&state, &preState, &gsc);

  /* Should add 3 cards to player's hand
     NOTE: We subtract one because the Smithy card should be discarded */
  testCount += 1;
  passCount += fakeAssert(
    "Should add 3 cards to player's hand",
    (state.handCount[P1] == preState.handCount[P1] + 3 - 1)
  );

  /* Should draw 3 cards from the player's deck */
  testCount += 1;
  passCount += fakeAssert(
    "Should draw the 3 cards from the player's deck",
    (containsCard(copper, state.hand[P1], state.handCount[P1])
    && containsCard(gardens, state.hand[P1], state.handCount[P1])
    && containsCard(mine, state.hand[P1], state.handCount[P1]))
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

  /* Should move played card to playedCards */
  testCount += 1;
  passCount += fakeAssert(
    "Should move played card to playedCards",
    (!containsCard(smithy, state.hand[P1], state.handCount[P1])
    && containsCard(smithy, state.playedCards, state.playedCardCount))
  );

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);

  return 0;
}

int main() {
  testSmithy();
  return 0;
}
