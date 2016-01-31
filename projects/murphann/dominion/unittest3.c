#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTMETHOD "updateCoins"

int main() {
  int numPlayers = 2;
  int i = 0;
  int seed = 1234;
  struct gameState G, storeG;
  int bonusCoins = 3;
  int pCoins = 0;
  int p1 = 0;
  int p2 = 1;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

  initializeGame(numPlayers, kcards, seed, &G);

  printf("********Testing %s***********\n", TESTMETHOD);

  memcpy(&storeG, &G, sizeof(struct gameState));

  for (i = 0; i < storeG.handCount[p1]; i++) {
    printf("%d\n", storeG.hand[p1][i]);
    if (storeG.hand[p1][i] == 4) {
      pCoins = pCoins + 1;
    }
   }

  printf("initial coins (should be %d): %d\n", pCoins, G.coins);

  updateCoins(p1, &G, bonusCoins);

  printf("Coins after update (should be %d): %d\n", pCoins+3, G.coins);

  return 0;
}
