/* Test for playAdventurer
 * Requirements
 * 1. Current player adds 2 treasure cards to hand
 * 2. 2 treasure cards come from own deck
 * 3. 0-n amount of cards are drawn until 2 treasure cards have been revealed
 * 4. The non-treasure cards that were drawn are discarded
 * 5. No state change should occur for other players
 * 6. No state change should occur to the victory/kingdom card piles
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
  int i;
  int card;
  int cardTypes = 27;
  int newCards = 2;
  int discarded = 1;
  int gameTreasureCount = 4;
  int testGameTreasureCount = 0;

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
  //Setting players hand to adventurer, copper, silver, gold, copper
  G.hand[thisPlayer][0] = 7;
  G.hand[thisPlayer][1] = 4;
  G.hand[thisPlayer][2] = 5;
  G.hand[thisPlayer][3] = 6;
  G.hand[thisPlayer][4] = 4;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

  printf("--- Current Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);

  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    card = testG.hand[thisPlayer][i];
    if (card == 4 || card == 5 || card == 6) {
      testGameTreasureCount++;
    }
  }
  printf("treasure count = %d, expected = %d\n", testGameTreasureCount, gameTreasureCount + newCards);
  assert(testGameTreasureCount == gameTreasureCount + newCards);

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