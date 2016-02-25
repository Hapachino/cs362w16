/* Test for gainCard
 * Requirements
 * 1. Player's hand, deck or discard pile gains selected card
 * 2. Card comes from supply pile
 * 3. If none of that card type are available, no card is added and -1 is returned
 * 4. No state change occurs for other player
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "gainCard"

int main() {
  int seed = 1000;
  int cardsToGain = 1;
  int cardToSelect = 7;
  int numPlayers = 2;
  int discard = 0;
  int deck = 1;
  int hand = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, smithy, council_room, remodel, great_hall, mine,
      baron, feast, gardens, village};

  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

  printf("*** TEST 1:  Test card to discard ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  gainCard(cardToSelect, &testG, discard, thisPlayer);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
  printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + cardsToGain);
  assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + cardsToGain);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
  printf("discard count = %d, expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  assert(testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);

  printf("--- Supply Pile ---\n");
  printf("supply count = %d, expected = %d\n", testG.supplyCount[cardToSelect], G.supplyCount[cardToSelect] - cardsToGain);
  assert(testG.supplyCount[cardToSelect] == G.supplyCount[cardToSelect] - cardsToGain);

  printf("*** TEST 2:  Test card to hand ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  gainCard(cardToSelect, &testG, hand, thisPlayer);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + cardsToGain);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + cardsToGain);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
  printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
  assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
  printf("discard count = %d, expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  assert(testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);

  printf("--- Supply Pile ---\n");
  printf("supply count = %d, expected = %d\n", testG.supplyCount[cardToSelect], G.supplyCount[cardToSelect] - cardsToGain);
  assert(testG.supplyCount[cardToSelect] == G.supplyCount[cardToSelect] - cardsToGain);

  printf("*** TEST 3:  Test card to deck ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  gainCard(cardToSelect, &testG, deck, thisPlayer);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + cardsToGain);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + cardsToGain);
  printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
  assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
  printf("discard count = %d, expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  assert(testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);

  printf("--- Supply Pile ---\n");
  printf("supply count = %d, expected = %d\n", testG.supplyCount[cardToSelect], G.supplyCount[cardToSelect] - cardsToGain);
  assert(testG.supplyCount[cardToSelect] == G.supplyCount[cardToSelect] - cardsToGain);

  printf("*** TEST 4:  Test no supply available for card ***\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  testG.supplyCount[cardToSelect] = 0;
  gainCard(cardToSelect, &testG, deck, thisPlayer);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
  printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
  assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
  printf("discard count = %d, expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
  assert(testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);

  printf("--- Supply Pile ---\n");
  printf("supply count = %d, expected = %d\n", testG.supplyCount[cardToSelect], 0);
  assert(testG.supplyCount[cardToSelect] == 0);

  printf("Function return = %d, expected = %d\n", gainCard(cardToSelect, &testG, deck, thisPlayer), -1);
  assert(gainCard(cardToSelect, &testG, deck, thisPlayer) == -1);


  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

  return 0;
}