#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTMETHOD "drawCard"

int main() {
  int numPlayers = 2;
  int seed = 1004;
  struct gameState G, storeG;
  int p1 = 0;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

  initializeGame(numPlayers, kcards, seed, &G);

  printf("********Testing %s***********\n", TESTMETHOD);

  memcpy(&storeG, &G, sizeof(struct gameState));

  drawCard(p1, &G);

  printf("Expected hand size: %d  New Hand Size: %d\n",
           storeG.handCount[p1]+1, G.handCount[p1]);

  printf("Expected Deck Size: %d  New Deck Size: %d\n",
          storeG.deckCount[p1]-1, G.deckCount[p1]);
  printf("\n\n\n");
  return 0;
}
