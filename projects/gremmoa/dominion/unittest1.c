/* Test for updateCoins
 * Requirements
 * 1. Treasure card in current players hand is counted
 * 2. Coin state is reset before counting
 * 3. If there is a bonus, it is added to the coin count
 * 4. No state change should occur to the player's hand
 * 5. No state change should occur to the other player's hand
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "updateCoins"

int main() {
  int bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, smithy, council_room, remodel, great_hall, mine,
      baron, feast, gardens, village};

  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  //Setting players hand to adventurer, copper, silver, gold, copper (7 coins)
  testG.hand[thisPlayer][0] = 7;
  testG.hand[thisPlayer][1] = 4;
  testG.hand[thisPlayer][2] = 5;
  testG.hand[thisPlayer][3] = 6;
  testG.hand[thisPlayer][4] = 4;
  updateCoins(thisPlayer, &testG, bonus);

  printf("*** TEST 1:  Test Treasure Cards w/ no bonus ***");
  printf("--- Current Player ---\n");
  printf("coin count = %d, expected = %d\n", testG.coins, 7);
  assert(testG.coins == 7);
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

  printf("*** TEST 2:  Test Treasure Cards w/ bonus ***");
  //Setting players hand to gold x 5 (15 coins)
  testG.hand[thisPlayer][0] = 6;
  testG.hand[thisPlayer][1] = 6;
  testG.hand[thisPlayer][2] = 6;
  testG.hand[thisPlayer][3] = 6;
  testG.hand[thisPlayer][4] = 6;
  bonus = 10;
  updateCoins(thisPlayer, &testG, bonus);
  printf("--- Current Player ---\n");
  printf("coin count = %d, expected = %d\n", testG.coins, 25);
  assert(testG.coins == 25);
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

  printf("*** TEST 3:  Test No Treasure Cards w/ bonus ***");
  //Setting players hand to gold x 5 (15 coins)
  testG.hand[thisPlayer][0] = 0;
  testG.hand[thisPlayer][1] = 0;
  testG.hand[thisPlayer][2] = 0;
  testG.hand[thisPlayer][3] = 0;
  testG.hand[thisPlayer][4] = 0;
  bonus = 12;
  updateCoins(thisPlayer, &testG, bonus);
  printf("--- Current Player ---\n");
  printf("coin count = %d, expected = %d\n", testG.coins, 12);
  assert(testG.coins == 12);
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

  printf("--- Other Player ---\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
  assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
  printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
  assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);


  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

  return 0;
}