#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

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

  cardEffect(smithy, 0, 0, 0, &G, 0, 0);
  printf("Cards in Hnad:  %d, Cards Excted: %d\n",
           G.handCount[p1], storeG.handCount[p1]+3);
  printf("Cards in Deck: %d, cards Expected: %d\n",
          G.deckCount[p1], storeG.deckCount[p1]-3);

  printf("End of %s test\n", TESTCARD);


   return 0;
}
