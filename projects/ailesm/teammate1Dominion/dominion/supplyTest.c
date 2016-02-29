#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main () {

  int r;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  r = initializeGame(2, k, 1, &G);
  SelectStream(2);
  PutSeed(3);

  printf ("initializeGame(4, k, 1, &G) = %d\n", r);
  assert(r == 0);
  int i =0;
  int j = 0;

  int n = 0;
  for (i;i<200000;i++){
        for (n;n<sizeof(struct gameState);n++){
            ((char*)&G)[n] = floor(Random()* 256);
        }
        int m = 0;
        int p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK) + 1;
        G.discardCount[p] = floor(Random()* MAX_DECK);
        G.handCount[p] = floor(Random()* MAX_HAND);
        G.numBuys = floor(Random() * 3);
        //printf("deck count: %d\n",G.deckCount[p]);
        //printf("discard count: %d\n",G.discardCount[p]);
        //printf("hand count: %d\n",G.handCount[p]);
        printf("buys: %d\n\n",G.numBuys);
        int aCard = adventurer;
        for (m;m<10;m++){
            aCard = floor(Random() * treasure_map);
            G.deck[p][m] = aCard;
        }


        int preCount = G.deckCount[p];
        assert(shuffle(p,&G)==0);
        printf("run %d\n",i);
        assert(preCount == G.deckCount[p]);




  }

  return 0;
}
