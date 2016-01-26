#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"

#define PLAYSMITHY_PASS "playSmithy() PASS: "
#define PLAYSMITHY_FAIL "playSmithy() FAIL: "


void testPlaySmithy() {
  int i = 0;
  int j = 0;

  int numPlayers = 0;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.
  int successfulInit = 0;                       // Variable to hold if the game was created successfully or not.
//  bool gameSuccess = true;                      // Variable to display if the game failed creating or not.

  struct gameState *state = newGame();          // Initialize game state.


  printf("\n***** TESTING INITIALIZE GAME *****\n");
  for(numPlayers = 0; numPlayers < MAX_PLAYERS+2; numPlayers++) {               // Create games with less than, equal to, and more players that supported.

    // Initialize game with valid game values.
    successfulInit = initializeGame(numPlayers, kingdomCards, randomSeed, state);
    // playSmithy(struct gameState *state, int currentPlayer, int handPos);
  }
}

int main() {
  testPlaySmithy();
  return 0;
}
