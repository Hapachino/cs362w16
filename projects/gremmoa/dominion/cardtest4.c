/* Test for playCouncilRoom
 * Requirements
 * 1. Current player receives 4 card
 * 2. 4 cards comes from players own pile
 * 3. Current player recieves extra buy
 * 4. Each other player receives 1 additional card
 * 5. Additional cards come from each players own pile
 * 6. No state change should occur to the victory/kingdom card piles
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

int main() {
  int i;
  int cardTypes = 27;
  int newCards = 4;
  int otherPlayerNewCards = 1;
  int discarded = 1;
  int extraBuys = 1;

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

  cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
  printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + extraBuys);
  assert(testG.numBuys == G.numBuys + extraBuys);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] + otherPlayerNewCards);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer] + otherPlayerNewCards);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer] - otherPlayerNewCards);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer] - otherPlayerNewCards);

  printf("--- Kingdom/Victory Pile ---\n");
  for (i = 0; i < cardTypes; i++) {
    printf("Card type %d count = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
    assert(testG.supplyCount[i] == G.supplyCount[i]);
  }

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}