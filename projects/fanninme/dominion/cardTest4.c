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

//Unit test for village Card
//function accepts int currentPlayer,struct gameState *state,int handPos

//oracle makes sure returns valid 
int unitTest(int player, struct gameState *post){
    srand(time(NULL));

    //define variables
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    int handPos= rand();

    //call function
    smithyCard(player,post,handPos);
    //memcmp game state size
    if (memcmp(&pre,post, sizeof(struct gameState))!=0){
        #if (NOISY_TEST == 1)
        printf("Memory mismatch");
        #endif
        exit(1);
    }
    //card specific checks
    //plus one card- minus village card, hand remains the same
    if (post->handCount != pre.handCount){
        #if (NOISY_TEST == 1) 
        printf("HandSize changed");
        #endif
        return 1;
    }
    //plus 2 actions
    if(post->numActions != pre.numActions+2){
        #if (NOISY_TEST == 1)
        printf("Not the correct number of actions");
        #endif
        return 2;
    }

    
    return 0;
}

int main () {
  //define variables  
  int i, n, r, p,error,errorA,errorB;
  errorA =0;
  errorB =0;
  //define a gamestate
  struct gameState G;

  printf ("Testing village Card.\n");

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
    G.numPlayers= floor(Random() * MAX_PLAYERS);
    //call function with test input
    error=unitTest(G.numPlayers,&G);

    if (error > 0){
        if(error == 1){
            errorA++;
        }else if(error > 1){
            errorB++;
        }
    }
  }
  printf ("ALL Random TESTS Complete\n");
  printf ("Errors type 1: %d ",errorA);
  printf ("Incorrect handsize.\n");
  printf ("Errors type 2: %d ",errorB);
  printf("incorrect number of actions\n");

  return 0;
}
