/* Test for playGreatHall
 * Requirements
 * 1. Current player receives 1 card
 * 2. Card comes from players own pile
 * 3. Current player recieves extra turn
 * 4. No state change should occur for other players
 * 5. No state change should occur to the victory/kingdom card piles
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

int main() {
  int i;
  int cardTypes = 27;
  int newCards = 1;
  int discarded = 1;
  int extraTurns = 1;

  int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, smithy, council_room, remodel, great_hall, mine,
      baron, feast, gardens, village};

  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  cardEffect(great_hall, choice1, choice2, choice3, &testG, handPos, &bonus);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
  printf("remaining turns = %d, expected = %d\n", testG.numActions, G.numActions + extraTurns);
  assert(testG.numActions == G.numActions + extraTurns);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

  printf("--- Kingdom/Victory Pile ---\n");
  for (i = 0; i < cardTypes; i++) {
    printf("Card type %d count = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
    assert(testG.supplyCount[i] == G.supplyCount[i]);
  }

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}