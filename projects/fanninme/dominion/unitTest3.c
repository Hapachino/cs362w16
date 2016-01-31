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

//Unit test for endTurn function
//function accepts struct gameState *state 

//oracle makes sure returns valid 
int unitTest(struct gameState *post){
    srand(time(NULL));

    //define variables
    int success;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));

    //call function
    success=endTurn(post);

    //memcmp game state size
    assert (memcmp(&pre,post, sizeof(struct gameState))==0);


    if( post->playedCardCount != 0){
        #if(NOISY_TEST == 1)
        printf("played card count is not 0 \n");
        #endif
    }

    if(post->handCount[post->whoseTurn] == 0){
        #if(NOISY_TEST == 1)
        printf("Hand count was never increased!\n");
        #endif
    }

    //check to see if whose turn it is has changed
    if(post->numPlayers > 1){
        if( post->whoseTurn != pre.whoseTurn ){
            #if (NOISY_TEST == 1)
            printf ("current players turn has not properly changed.\n");
            #endif
            return 1;
        }
    }

    if (success == -1){
        #if (NOISY_TEST == 1)
        printf ("Error in end turn function.\n");
        #endif
        return 2;
    }
    return 0;
}


int main () {
  //define variables  
  int i, n, r, p, error,errorA,errorB;
  errorA=0;
  errorB=0;
  //define a gamestate
  struct gameState G;

  printf ("Testing end turn function.\n");

  printf ("RANDOM TESTS.\n");
  //create random seed
  SelectStream(2);
  PutSeed(3);
  //for 2000 test cases
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      //fill gamestate with random bits between 0-256 using ofset
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.numPlayers = floor(Random() * MAX_PLAYERS);
    //call function with test input
    error=unitTest(&G);

    if (error > 0){
        if(error == 1){
            errorA++;
        }else if(error > 1){
            errorB++;
        }
    }
  }

  printf ("ALL TESTS complete\n");
   printf ("Errors type 1: %d ",errorA);
  printf ("Current player has not been changed at end of turn.\n");
  printf ("Errors type 2: %d ",errorB);
  printf("function received bad input/found a error returned a 1 \n");

  return 0;
}
