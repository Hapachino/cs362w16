#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
  int numPlayers = 2;
  int seed = 1004;
  struct gameState G, storeG;
  int p1 = 0;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

   initializeGame(numPlayers, kcards, seed, &G);

   printf("********Testing %s***********\n", TESTCARD);

   memcpy(&storeG, &G, sizeof(struct gameState));

   cardEffect(village, 0, 0, 0, &G, 0, 0);

  printf("Cards in Hand:  %d, Cards Expected: %d\n",
          G.handCount[p1], storeG.handCount[p1]);
  printf("Cards in Deck: %d, cards Expected: %d\n",
          G.deckCount[p1], storeG.deckCount[p1]-1);
  printf("Number of Actions:  %d, Number Expected: %d\n",
          G.numActions, storeG.numActions+2);
  printf("Cards in Discard: %d, cards Expected: %d\n",
          G.discardCount[p1], storeG.discardCount[p1]+1);
  printf("\n\n\n");
   return 0;
}
