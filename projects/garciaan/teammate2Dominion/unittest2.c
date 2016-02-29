#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTMETHOD "endTurn"

int main() {
  int numPlayers = 2;
  int seed = 1004;
  struct gameState G, storeG;
  int p1 = 0;
  int p2 = 1;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

   initializeGame(numPlayers, kcards, seed, &G);

   printf("********Testing %s***********\n", TESTMETHOD);

   memcpy(&storeG, &G, sizeof(struct gameState));

   endTurn(&G);

   printf("Size of discards: %d  Expected number of discards: %d\n",
           G.discardCount[p1],
           storeG.discardCount[p1] + storeG.handCount[p1]);

   printf("Player Hand: %d  Expected Player Hand: %d\n",
           G.handCount[p1], storeG.handCount[p1-5]);

  printf("Player turn: %d  Expected Turn: %d\n", G.whoseTurn, storeG.whoseTurn+1);

  printf("New Player Hand: %d  Expected Player Hand: %d\n",
          G.handCount[p2], storeG.handCount[p2]+5);

  printf("\n\n\n");
    return 0;
}
