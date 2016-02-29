#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 1
#define NOISY_TEST 1

int checkUpdateCoins(int p, struct gameState *post, int bonus) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int r;
  r = updateCoins (p, post, bonus);
  assert (r == 0);
  assert(pre.coins + bonus == post->coins);
}

int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount, randomHandCount, randomCard;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing updateCoins.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 1000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    randomHandCount = floor(Random() * MAX_HAND);
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = randomHandCount;

    /* initialize hand */

    // give the player real cards
    for ( j=0; j< randomHandCount; j++)
    {
      G.hand[p][j] = 0;
      randomCard = floor(Random() * 3);
      switch (randomCard) {
        case 0:
          G.hand[p][j] = copper;
          break;
        case 1:
          G.hand[p][j] = silver;
          break;
        case 2:
          G.hand[p][j] = gold;
          break;
      }
    }
    G.coins = 0;

    // a stub for the updateCoins function
    for (i = 0; i < randomHandCount; i++)
    {
      if (G.hand[p][i] == copper)
      {
        G.coins += 1;
      }
      else if (G.hand[p][i] == silver)
      {
        G.coins += 2;
      }
      else if (G.hand[p][i] == gold)
      {
        G.coins += 3;
      }
    }

    // random bonus number
    int bonus = floor(Random() * 100);
    //printf(" bonus %d\n", bonus);
    //G.coins = 9;
    checkUpdateCoins(p, &G, bonus);
  }
  printf ("ALL TESTS OK FOR UPDATECOINS\n\n");
  exit(0);
  return 0;
}
