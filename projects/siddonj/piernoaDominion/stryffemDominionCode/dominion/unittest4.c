#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 1
#define NOISY_TEST 1

int checkIsGameOver(struct gameState *post, int testFlag) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  r = isGameOver(post);

  if (pre.supplyCount[province] == 0)
  {
    assert( r == 1 );
    return 0;
  }

  if( testFlag )
  {
    assert( r == 1);
    return 0;
  }

  assert( r == 0 );
  return 0;
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing isGameOver.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 1; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);

    G.supplyCount[province] = 0;
    checkIsGameOver(&G, 0); // testing provinces at 0;

    G.supplyCount[province] = 10;
    /* Testing if three supplies are empty but there are still provinces */
    G.supplyCount[silver] = 0;
    G.supplyCount[gold] = 0;
    G.supplyCount[copper] = 0;
    checkIsGameOver(&G, 1); // testing three items at 0;

    G.supplyCount[silver] = 2;
    G.supplyCount[gold] = 0;
    G.supplyCount[copper] = 0;
    checkIsGameOver(&G, 0); // testing two items at 0;

  }
  printf ("ALL TESTS OK FOR ISGAMEOVER \n\n");
  exit(0);
  return 0;
}
