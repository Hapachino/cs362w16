#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#define DEBUG 1
#define NOISY_TEST 1

int checkGainCard(int supplyPos, struct gameState *post, int toFlag, int p) {


  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
//state->supplyCount[supplyPos]--;
  int r;
   //printf ("drawCard PRE: p %d HC %d DeC %d DiC %d Supply Count Before %d \n",
  	//  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.supplyCount[supplyPos]);
  //
  //printf("post.discard[p][ post.discardCount[p] ] in test before call %d \n", pre.discard[p][ pre.discardCount[p] ]);
  r = gainCard(supplyPos, post, toFlag, p);
  // //
  // printf ("drawCard POST: p %d HC %d DeC %d DiC %d Supply Count AFTER %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->supplyCount[supplyPos]);
   if (toFlag == -1)
   {
    assert( r == -1 );
    return 0;
   }

   if (toFlag == 1)          assert( pre.deckCount[p] + 1 == post->deckCount[p] );
   else if (toFlag == 2)     assert( pre.handCount[p] + 1 == post->handCount[p] );
   else                      assert( pre.discardCount[p] + 1 == post->discardCount[p] );

   assert( supplyPos == post->discard[p][ post->discardCount[p] - 1 ]);
   assert(pre.supplyCount[supplyPos] -1 == post->supplyCount[supplyPos]); // assert supply count has been decremented;
   assert( r == 0 );
  return 0;
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount, toFlag, supplyPos;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing gainCard.\n");

  SelectStream(2);
  PutSeed(3);

  for (i = 0; i < sizeof(struct gameState); i++) {
    ((char*)&G)[i] = floor(Random() * 256);
  }
  int handCountConst = floor(Random() * MAX_HAND);
  p = 0;

  G.deckCount[p] = 40;
  G.discardCount[p] = 10;
  G.handCount[p] = 8;
  G.discard[p][G.discardCount[p]] = 100;
  supplyPos = 0;
  //(int supplyPos, struct gameState *state, int toFlag, int player)
  checkGainCard(supplyPos, &G, 0, p);    // checking toFlag = 0
  checkGainCard(supplyPos, &G, 1, p); // checking toFlag = 1
  checkGainCard(supplyPos, &G, 2, p); // checking toFlag = 2
  checkGainCard(-1, &G, -1, p); ////check if supply pile is empty (0) or card is not used in game (-1)

  printf ("ALL TESTS OK FOR GAINCARD\n\n");
  exit(0);
  return 0;
}
