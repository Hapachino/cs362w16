#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"

#define UPDATECOINS_PASS "updateCoins() PASS: "
#define UPDATECOINS_FAIL "updateCoins() FAIL: "

void testUpdateCoins() {
  int i = 0;                  // Initialize iterators.

  // Initilize game variables.
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 3;
  int bonusCoins = 0;
  int player = 0;

  // Create game.
  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();

  initializeGame(numPlayers, kingdomCards, randomSeed, state);


  printf("\n***** TESTING UPDATE COINS *****\n");

  // Start Test
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  // Check a hand made of only copper is correct.
  bonusCoins = 0;
  player = testGame->whoseTurn;

  // Set hand to only copper.
  for (i = 0; i < testGame->handCount[player]; i++) {
    testGame->hand[player][i] = copper;
  }

  updateCoins(player, testGame, bonusCoins);

  if (testGame->coins != 5) {
    printf(UPDATECOINS_FAIL);
  } else {
    printf(UPDATECOINS_PASS);
  }
  printf("expected coin count to total '5' coins with a hand made entirely of copper, got: '%d' \n", testGame->coins);
  // END


  // Start Test
  // Check a hand made of only silver is correct.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  bonusCoins = 0;
  player = testGame->whoseTurn;

  // Set hand to only copper.
  for (i = 0; i < testGame->handCount[player]; i++) {
    testGame->hand[player][i] = silver;
  }

  updateCoins(player, testGame, bonusCoins);

  if (testGame->coins != 10) {
    printf(UPDATECOINS_FAIL);
  } else {
    printf(UPDATECOINS_PASS);
  }
  printf("expected coin count to total '10' coins with a hand made entirely of silver, got: '%d' \n", testGame->coins);
  //END


  // Start Test
  // Check a hand made of only gold is correct.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  bonusCoins = 0;
  player = testGame->whoseTurn;

  // Set hand to only gold.
  for (i = 0; i < testGame->handCount[player]; i++) {
    testGame->hand[player][i] = gold;
  }

  updateCoins(player, testGame, bonusCoins);

  if (testGame->coins != 15) {
    printf(UPDATECOINS_FAIL);
  } else {
    printf(UPDATECOINS_PASS);
  }
  printf("expected coin count to total '15' coins with a hand made entirely of gold, got: '%d' \n", testGame->coins);
  //END

  // Start Test
  // Check a hand made of non-treasure is correct.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  bonusCoins = 0;
  player = testGame->whoseTurn;

  // Set hand to only gold.
  for (i = 0; i < testGame->handCount[player]; i++) {
    testGame->hand[player][i] = duchy;
  }

  updateCoins(player, testGame, bonusCoins);

  if (testGame->coins != 0) {
    printf(UPDATECOINS_FAIL);
  } else {
    printf(UPDATECOINS_PASS);
  }
  printf("expected coin count to total '0' coins with a hand made entirely of 'duchy', got: '%d' \n", testGame->coins);
  //END

  // Start Test
  // Checks that a hand with no cards correctly calculates 0 coins.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  bonusCoins = 0;
  player = testGame->whoseTurn;
  testGame->handCount[player] = 0;                     // Set hand total to 0.

  updateCoins(player, testGame, bonusCoins);

  if (testGame->coins > 0) {
    printf(UPDATECOINS_FAIL);
  } else {
    printf(UPDATECOINS_PASS);
  }
  printf("expected coin count to total '0' coins with a no cards in hand, got: '%d' \n", testGame->coins);
  //END

  // Start Test
  // Checks that a bonusCoin correctly increases number of coins.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  bonusCoins = 3;
  player = testGame->whoseTurn;
  testGame->handCount[player] = 0;                     // Set hand total to 0.

  updateCoins(player, testGame, bonusCoins);

  if (testGame->coins != 3) {
    printf(UPDATECOINS_FAIL);
  } else {
    printf(UPDATECOINS_PASS);
  }
  printf("expected coin count to total '3' coins with '3' bonus coins set and no cards in hand, got: '%d' \n", testGame->coins);
  //END


  // Start Test
  // Checks that coin total is correctly calculated even when the coin total value is already set.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  bonusCoins = 0;
  player = testGame->whoseTurn;
  testGame->coins = 45;
  testGame->handCount[player] = 0;

  updateCoins(player, testGame, bonusCoins);

  if (testGame->coins > 0) {
    printf(UPDATECOINS_FAIL);
  } else {
    printf(UPDATECOINS_PASS);
  }
  printf("expected coin count to total '0' coins when coin total was set before calling updateCoins(), got: '%d' \n", testGame->coins);
  //END

}


int main() {
  testUpdateCoins();
  return 0;
}
