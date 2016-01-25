#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG 0
#define NOISY_TEST 1

//Unit test for Smithy Card
//function accepts currentPlayer,struct gameState *state,int handPos
//oracle makes sure returns valid 
int unitTest(int player, struct gameState *post){
    srand(time(NULL));

    //define variables
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    int handPos= rand();

    //call function
    smithyCard(player,post, handPos);
    //memcmp game state size
    assert (memcmp(&pre,post, sizeof(struct gameState))==0);
    //card specific checks
    //players handsize should be 3 larger after playing the smithy
    assert(post->handCount == pre.handCount+3);

    return 0;
}

int main () {
  //define variables  
  int i, n, r, player, deckCount, discardCount, handCount;
  //define a array of cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  //define a gamestate
  struct gameState G;

  printf ("RANDOM TESTS.\n");

  //create random seed
  SelectStream(2);
  PutSeed(3);

  //for 2000 test cases
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(rand() * 256);
    }
    player = floor(rand() * 2);
    //game state
    G.deckCount[player] = floor(rand() * MAX_DECK);
    G.discardCount[player] = floor(rand() * MAX_DECK);
    G.handCount[player] = floor(rand() * MAX_HAND);
    //call unit test function with test input
    unitTest(player,&G);
  }
  printf ("ALL TESTS OK\n");
  exit(0);

  //fixed tests
  printf ("SIMPLE FIXED TESTS.\n");
  for (player = 0; player < 2; player++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState)); 
	  r = initializeGame(2, k, 1, &G);  
	  G.deckCount[player] = deckCount;
	  memset(G.deck[player], 0, sizeof(int) * deckCount);
	  G.discardCount[player] = discardCount;
	  memset(G.discard[player], 0, sizeof(int) * discardCount);
	  G.handCount[player] = handCount;
	  memset(G.hand[player], 0, sizeof(int) * handCount);
      //call unit test
	  unitTest(player, &G);
	}
      }
    }
  }

  return 0;
}
