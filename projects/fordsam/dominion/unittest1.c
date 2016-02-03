/* Test the shuffle() function
   NOTE: shuffle() should simply change the order of the player's deck.
*/
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "fordsamTest.h"

#define P1 0
#define P2 1

void testShuffle() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  struct gameState initialState = {0};
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};

  printf("----- Testing shuffle() -----\n");

  /* Set up deck to have cards but a deckCount of 0 and shuffle */
  printf("----- Test: deckCount = 0, deck array has 5 cards\n");
  state.deck[P1][0] = copper;
  state.deck[P1][1] = remodel;
  state.deck[P1][2] = feast;
  state.deck[P1][3] = adventurer;
  state.deck[P1][4] = estate;
  state.deckCount[P1] = 0;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = shuffle(P1, &state);

  /* Should not change state when deckCount < 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change game state when deckCount < 1",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when deckCount < 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when deckCount < 1",
    (result == -1)
  );

  /* Set up deck to have cards but a deckCount of 1 and then shuffle */
  printf("\n----- Test: deckCount = 1, deck array has 5 cards\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.deck[P1][0] = copper;
  state.deck[P1][1] = remodel;
  state.deck[P1][2] = feast;
  state.deck[P1][3] = adventurer;
  state.deck[P1][4] = estate;
  state.deckCount[P1] = 1;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = shuffle(P1, &state);

  /* Should "shuffle" (technically no state change) when deckCount == 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should \"shuffle\" (technically no state change) when deckCount == 1",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return 0 when deckCount == 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should return 0 when deckCount == 1",
    (result == 0)
  );

  /* Set up deck to *really* have more than one card and then shuffle */
  printf("\n----- Test: deckCount = 5, deck array has 5 cards\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.deck[P1][0] = copper;
  state.deck[P1][1] = remodel;
  state.deck[P1][2] = feast;
  state.deck[P1][3] = adventurer;
  state.deck[P1][4] = estate;
  state.deckCount[P1] = 5;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = shuffle(P1, &state);
  compareState(&state, &preState, &gsc);

  /* Should modify the deck when shuffling */
  testCount += 1;
  passCount += fakeAssert(
    "Should make changes to the deck when shuffling (deckCount > 1)",
    (gsc.deckChanged[P1] == 1)
  );

  /* Should shuffle when deckCount > 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should maintain the same cards in deck when shuffling (deckCount > 1)",
    (containsCard(copper, state.deck[P1], state.deckCount[P1])
    && containsCard(remodel, state.deck[P1], state.deckCount[P1])
    && containsCard(feast, state.deck[P1], state.deckCount[P1])
    && containsCard(adventurer, state.deck[P1], state.deckCount[P1])
    && containsCard(estate, state.deck[P1], state.deckCount[P1]))
  );

  /* Should not change player's deckCount when shuffling */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change player's deckCount when shuffling (deckCount > 1)",
    (gsc.deckCount[P1] == 0)
  );

  /* Should not change player's hand when shuffling */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change player's hand when shuffling (deckCount > 1)",
    (gsc.handChanged[P1] == 0)
  );

  /* Should not change player's discard pile when shuffling */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change player's discard pile when shuffling (deckCount > 1)",
    (gsc.discardChanged[P1] == 0)
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

  /* Should return 0 when deckCount == 1 */
  testCount += 1;
  passCount += fakeAssert(
    "Should return 0 when deckCount > 1",
    (result == 0)
  );

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);
}

int main() {
  testShuffle();
  return 0;
}
