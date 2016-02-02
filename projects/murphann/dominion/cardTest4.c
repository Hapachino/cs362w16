#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

int main() {
  int numPlayers = 2;
  int seed = 1004;
  struct gameState G, storeG;
  int p1 = 0;
  int p2 = 1;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

   initializeGame(numPlayers, kcards, seed, &G);

   printf("********Testing %s***********\n", TESTCARD);

   memcpy(&storeG, &G, sizeof(struct gameState));

   cardEffect(council_room, 0, 0, 0, &G, 0, 0);

   printf("Player 1 Cards in Hand:  %d, Cards Expected: %d\n",
            G.handCount[p1], storeG.handCount[p1]+4);
   printf("Cards in Deck: %d, cards Expected: %d\n",
           G.deckCount[p1], storeG.deckCount[p1]-4);

   printf("Player 2 Cards in Hand:  %d, Cards Expected: %d\n",
            G.handCount[p2], storeG.handCount[p2]+1);
   printf("Cards in Deck: %d, cards Expected: %d\n",
           G.deckCount[p2], storeG.deckCount[p2]-1);


   printf("Number of Buys:  %d, Number Expected: %d\n",
            G.numBuys, storeG.numBuys+1);

   return 0;
}
