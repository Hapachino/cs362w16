/* Test the playMine() function
   NOTE: playMine() should:
     * Trash a treasure card for a treasure card costing up to 3 coins more.
       * The new treasure card should be added to the player's hand.
     * Move the played card to the playedCards pile.
*/
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "fordsamTest.h"

#define P1 0
#define P2 1
#define HANDPOS 1
#define COPPERPOS 2
#define BARONPOS 3
#define ESTATEPOS 4

int testPlayMine() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  struct gameState initialState = {0};
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};

  printf("----- Testing Mine card -----\n");

  /* Set up game state */
  state.whoseTurn = P1;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = silver;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = cutpurse;
  state.deckCount[P1] = 5;
  state.hand[P1][0] = copper;
  state.hand[P1][1] = mine;
  state.hand[P1][2] = copper;
  state.hand[P1][3] = baron;
  state.hand[P1][4] = estate;
  state.handCount[P1] = 5;
  state.discardCount[P1] = 0;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  state.supplyCount[silver] = 10;
  memcpy(&initialState, &state, sizeof(struct gameState));

  /* Test playMine() using a non-treasure card for choice1 */
  printf("----- Test: choice1 = estate, choice2 = silver\n");
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playMine(HANDPOS, ESTATEPOS, silver, &state);

  /* Should not make any changes when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't treasure (< copper)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't treasure (< copper)",
    (result == -1)
  );

  /* Test playMine() using a non-treasure card for choice1 */
  printf("\n----- Test: choice1 = baron, choice2 = silver\n");
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playMine(HANDPOS, BARONPOS, silver, &state);

  /* Should not make any changes when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't treasure (> gold)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't treasure (> gold)",
    (result == -1)
  );

  /* Test playMine() using a treasure card for choice 1 and a non-card for
     choice2 */
  printf("\n----- Test: choice1 = copper, choice2 = treasure_map + 999\n");
  memcpy(&initialState, &state, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playMine(HANDPOS, COPPERPOS, treasure_map+999, &state);

  /* Should not make any changes when choice1 isn't a real card */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't a card (> treasure_map)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't a card (> treasure_map)",
    (result == -1)
  );

  /* Test playMine() using a treasure card for choice 1 and a non-card for
     choice2 */
  printf("\n----- Test: choice1 = copper, choice2 = curse - 999\n");
  memcpy(&initialState, &state, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playMine(HANDPOS, COPPERPOS, curse-999, &state);

  /* Should not make any changes when choice1 isn't a real card */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't a card (< curse)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't a card (< curse)",
    (result == -1)
  );

  /* Test playMine() using a treasure card for choice1 and a non-treasure card
     for choice 2 */
  printf("\n----- Test: choice1 = copper, choice2 = estate\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playMine(HANDPOS, COPPERPOS, estate, &state);

  /* Should not make any changes when choice2 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice2 isn't treasure",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice2 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice2 isn't treasure",
    (result == -1)
  );

  /* Test playMine() using a treasure card for choice1 and a treasure card
     that's more than 3 coins more expensive */
  printf("\n----- Test: choice1 = copper, choice2 = gold\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playMine(HANDPOS, COPPERPOS, gold, &state);

  /* Should not make any changes when choice2 is too costly */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice2 is too costly",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice2 is too costly */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice2 is too costly",
    (result == -1)
  );

  /* Test playMine() using a treasure card for choice1 and a treasure card
     that's up to 3 coins more (silver) */
  printf("\n----- Test: choice1 = copper, choice2 = silver\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playMine(HANDPOS, COPPERPOS, silver, &state);
  compareState(&state, &preState, &gsc);

  /* Should add choice2 card to hand */
  testCount += 1;
  passCount += fakeAssert(
    "Should add choice2 card to hand",
    (containsCard(silver, state.hand[P1], state.handCount[P1]))
  );

  /* Should trash choice1 card */
  testCount += 1;
  passCount += fakeAssert(
    "Should trash choice1 card",
    (state.hand[P1][COPPERPOS] != copper
    && !containsCard(copper, state.deck[P1], state.deckCount[P1])
    && !containsCard(copper, state.discard[P1], state.discardCount[P1])
    && !containsCard(copper, state.playedCards, state.playedCardCount))
  );

  /* Should only trash ONE instance of choice1 card */
  testCount += 1;
  passCount += fakeAssert(
    "Should only affect one instance of choice1 card",
    (containsCard(copper, state.hand[P1], state.handCount[P1])
    && !containsCard(copper, state.deck[P1], state.deckCount[P1])
    && !containsCard(copper, state.discard[P1], state.discardCount[P1])
    && !containsCard(copper, state.playedCards, state.playedCardCount))
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
    (!containsCard(mine, state.hand[P1], state.handCount[P1])
    && containsCard(mine, state.playedCards, state.playedCardCount))
  );

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);

  return 0;
}

int main() {
  testPlayMine();
  return 0;
}
