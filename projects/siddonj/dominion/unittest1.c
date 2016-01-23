#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"

#define INITGAME_PASS "initializeGame() PASS: "
#define INITGAME_FAIL "initializeGame() FAIL: "

// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state) {

void testInitializeGame() {
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
  int randomSeed = 0;

  struct gameState *state = newGame();          // Initialize game state.

  printf("%s", "Hello");
  printf("%d", numPlayers);

  initializeGame(numPlayers, kingdomCards, randomSeed, state);

  // Check number of players.
  if (numPlayers == 2) {
    printf(INITGAME_PASS);
    printf("when containing 2 as number of players.\n");
  } else {
    printf(INITGAME_FAIL);
    printf("when containing 2 as number of players.\n");
  }

  // Check number of curse cards for 2 players.
  if (numPlayers == 2) {
    if (state->supplyCount[curse] == 10) {
      printf(INITGAME_PASS);
      printf("when containing 2 players, game contains 10 curse cards.\n");
    } else {
      printf(INITGAME_FAIL);
      printf("when containing 2 players, expects 10 curse cards, got: ");
      printf("%d", state->supplyCount[curse]);
      printf("\n");
    }
  }

  // Check number of victory cards for 2 players.
  if (numPlayers == 2) {
    // Check number of estate cards.
    if (state->supplyCount[estate] == 8) {
      printf(INITGAME_PASS);
      printf("when containing 2 players, game contains 8 'estate' cards.\n");
    } else {
      printf(INITGAME_FAIL);
      printf("when containing 2 players, expects 8 'estate' cards, got: ");
      printf("%d", state->supplyCount[estate]);
      printf("\n");
    }

    // Check number of duchy cards.
    if (state->supplyCount[duchy] == 8) {
      printf(INITGAME_PASS);
      printf("when containing 2 players, game contains 8 'duchy' cards.\n");
    } else {
      printf(INITGAME_FAIL);
      printf("when containing 2 players, expects 8 'duchy' cards, got: ");
      printf("%d", state->supplyCount[duchy]);
      printf("\n");
    }

    // Check number of province cards.
    if (state->supplyCount[province] == 8) {
      printf(INITGAME_PASS);
      printf("when containing 2 players, game contains 8 'province' cards.\n");
    } else {
      printf(INITGAME_FAIL);
      printf("when containing 2 players, expects 8 'province' cards, got: ");
      printf("%d", state->supplyCount[province]);
      printf("\n");
    }

  }


}


int main() {
  testInitializeGame();
  return 0;
}
