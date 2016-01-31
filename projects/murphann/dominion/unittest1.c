#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTMETHOD "shuffle"

int main() {
  int numPlayers = 2;
  int i = 0;
  int discarded =0;
  int seed = 1004;
  struct gameState G, storeG;
  int thisPlayer = 0;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

  initializeGame(numPlayers, kcards, seed, &G);

  printf("********Testing %s***********\n", TESTMETHOD);

  memcpy(&storeG, &G, sizeof(struct gameState));

  shuffle(thisPlayer, &G);

  printf("BEFORE SHUFFLE\n");
  for (i = 0; i < storeG.deckCount[thisPlayer]; i++) {
    printf("%d\n", storeG.deck[thisPlayer][i]);
  }

  printf("AFTER SHUFFLE\n");
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    printf("%d\n", G.deck[thisPlayer][i]);
  }

  return 0;
}
