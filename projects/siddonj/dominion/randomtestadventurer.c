#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"

#define INITGAME_PASS "initializeGame() PASS: "
#define INITGAME_FAIL "initializeGame() FAIL: "

#define NUM_TESTS 1000

void testRandomCard() {
  int i = 0;
  int playerHandSize = 0;       // Get hand size.
  int playerActions = 0;
  int handSizeIncrease = 0;
  int actionDecrease = 0;
  int smithyHandCount = 0;
  int smithyDiscardCount = 0;
  int smithyPlayedCount = 0;

  int otherHandIncrease = 0;
  int otherDeckIncrease = 0;
  int otherDiscardIncrease = 0;


  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.
  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();

  initializeGame(numPlayers, kingdomCards, randomSeed, state);    // Initialize game with valid game values.


  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  // Test playing smithy correctly increments player's handsize.
  playerHandSize = numHandCards(testGame);       // Get hand size.
  playerActions = testGame->numActions;          // Get initial action amount.

  handSizeIncrease = 0;
  otherHandIncrease = 0;
  otherDeckIncrease = 0;
  otherDiscardIncrease = 0;

  for(i = 0; i < NUM_TESTS; i++) {
    printf("Hello!\n");
  }

  // Free memory.
  free(state);
  state = 0;

  free(testGame);
  testGame = 0;
}


int main() {

  return 0;
}
