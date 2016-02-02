/* Test for discardCard
 * Requirements
 * 1. Card at selected position is removed from player's hand
 * 2. Card is added to played pile if trash flag is not set
 * 3. Last card in player's hand replaces card that is discarded
 * 4. If only card in hand or is the last card in hand, no other cards move in hand
 * 4. No state change occurs for other player
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "discardCard"

int main() {
  int seed = 1000;
  int cardsToDiscard = 1;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, smithy, council_room, remodel, great_hall, mine,
      baron, feast, gardens, village};

  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

  printf("*** TEST 1:  Discard first card w/ full hand no trashFlag ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  discardCard(0, thisPlayer, &testG, 0);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - cardsToDiscard);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - cardsToDiscard);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

  printf("--- Played Pile ---\n");
  printf("Played pile count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + cardsToDiscard);
  assert(testG.playedCardCount == G.playedCardCount + cardsToDiscard);

  printf("*** TEST 2:  Discard first card w/ full hand w/ trashFlag ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  discardCard(0, thisPlayer, &testG, 1);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - cardsToDiscard);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - cardsToDiscard);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

  printf("--- Played Pile ---\n");
  printf("Played pile count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
  assert(testG.playedCardCount == G.playedCardCount);

  printf("*** TEST 3:  Discard last card w/ full hand no trashFlag ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  discardCard(4, thisPlayer, &testG, 0);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - cardsToDiscard);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - cardsToDiscard);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

  printf("--- Played Pile ---\n");
  printf("Played pile count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + cardsToDiscard);
  assert(testG.playedCardCount == G.playedCardCount + cardsToDiscard);

  printf("*** TEST 4:  Discard only card w/ no trashFlag ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  testG.handCount[thisPlayer] = 1;
  testG.hand[thisPlayer][1] = -1;
  testG.hand[thisPlayer][2] = -1;
  testG.hand[thisPlayer][3] = -1;
  testG.hand[thisPlayer][4] = -1;
  discardCard(4, thisPlayer, &testG, 0);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], 0);
  assert(testG.handCount[thisPlayer] == 0);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

  printf("--- Played Pile ---\n");
  printf("Played pile count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + cardsToDiscard);
  assert(testG.playedCardCount == G.playedCardCount + cardsToDiscard);

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

  return 0;
}