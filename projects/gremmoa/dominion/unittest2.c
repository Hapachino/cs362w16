/* Test for isGameOver
 * Requirements
 * 1. If Province cards are empty, game is over
 * 2. If 3 stacks of supply cards are empty, game is over
 * 3. No other conditions should trigger a game win
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "isGameOver"

int main() {
  int seed = 1000;
  int numPlayers = 2;
  int province = 3;
  struct gameState G, testG;
  int k[10] = {adventurer, smithy, council_room, remodel, great_hall, mine,
      baron, feast, gardens, village};

  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  printf("*** TEST 1:  Test with 0 provinces in supply ***\n");
  testG.supplyCount[province] = 0;
  printf("Game over = %d, expected = %d\n", isGameOver(&testG), 1);
  assert(isGameOver(&testG) == 1);

  memcpy(&testG, &G, sizeof(struct gameState));
  printf("*** TEST 2:  Test with 3 empty supply piles ***\n");
  testG.supplyCount[7] = 0;
  testG.supplyCount[8] = 0;
  testG.supplyCount[9] = 0;
  printf("Game over = %d, expected = %d\n", isGameOver(&testG), 1);
  assert(isGameOver(&testG) == 1);

  memcpy(&testG, &G, sizeof(struct gameState));
  printf("*** TEST 3:  Test with 2 empty supply piles ***\n");
  testG.supplyCount[8] = 0;
  testG.supplyCount[9] = 0;
  printf("Game over = %d, expected = %d\n", isGameOver(&testG), 0);
  assert(isGameOver(&testG) == 0);

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

  return 0;
}