#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
  int numPlayers = 2;
  int seed = 14;
  struct gameState G, storeG;
  int p1 = 0;
  int i = 0;
  int coinsInDeck = 0;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

  initializeGame(numPlayers, kcards, seed, &G);

  printf("********Testing %s***********\n", TESTCARD);

  memcpy(&storeG, &G, sizeof(struct gameState));

  for (i = 0; i < storeG.deckCount[p1]; i++) {
    if (storeG.deck[p1][i] == 4){
      coinsInDeck = coinsInDeck + 1;
    }
    if (coinsInDeck == 2) {
      coinsInDeck = i+1;
      break;
    }
  }

  cardEffect(adventurer, 0, 0, 0, &G, 0, 0);
  updateCoins(p1, &G, 0);
  updateCoins(p1, &storeG, 0);
  printf("Cards in Hand:  %d, Cards Excted: %d\n",
           G.handCount[p1], storeG.handCount[p1]+2);
  printf("Cards in Deck: %d, cards Expected: %d\n",
          G.deckCount[p1], storeG.deckCount[p1]-coinsInDeck);
  printf("Cards in discard:  %d, Cards Expected: %d\n",
           G.discardCount[p1], storeG.discardCount[p1]+coinsInDeck-2);
  printf("Coins: %d, Coins expected: %d\n",
          G.coins, storeG.coins+2);


  return 0;
}
