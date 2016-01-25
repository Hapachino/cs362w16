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

//Unit test for playCard function
//Preconditions:
//function accepts int handPos, int choice1, int choice2, int choice3, struct gameState *state) 
//game state :


//oracle makes sure returns valid 
int unitTest(struct gameState *post){
    srand(time(NULL));

    //define variables
    int sucess;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    //create an array to hold four integer inputs
    int input[4];
    //randomly generate 4 ints
    for(int i=0; i<4; i++){
        input[i]= rand();
    }

    //call function
    sucess=playCard(input[0],input[1],input[2],input[3], post);
    //memcmp game state size
    assert (memcmp(&pre,post, sizeof(struct gameState))==0);
    assert (sucess == 0);
    //specific function check 
    //confirm that actions is one less
    assert (pre.numActions == post->numActions+1);

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
    unitTest(&G);
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
	  unitTest(&G);
	}
      }
    }
  }

  return 0;
}
