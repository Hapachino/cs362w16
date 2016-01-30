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
#define NOISY_TEST 0

//Unit test for isgameOver function
//Preconditions:
//function accepts struct gameState *state 

//oracle makes sure returns valid 
int unitTest(struct gameState *post){
    srand(time(NULL));

    //define variables
    int success;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));

    //call function
    success=isGameOver(post);

    //memcmp game state size
    if (memcmp(&pre,post, sizeof(struct gameState))!=0){
        #if (NOISY_TEST == 1)
        printf ("Error in size of gamestate.\n");
        #endif
        return 1;
        
    }

    //assert (success==0);
    if (success == -1){
        #if (NOISY_TEST == 1)
        printf ("Error in playCard function bad exit status.\n");
        #endif
        return 2;
    }

    //if stack of Province cards is empty, the game ends
    if (post->supplyCount[province] < 0){
        #if (NOISY_TEST == 1)
        printf ("supply count is negative.\n");
        #endif
        return 3;
    }

    return 0;
}

int main () {
  //define variables  
  int error, errorA, errorB,errorC;
  errorB=0;
  errorA=0; 
  errorC=0;
  int i, n, r, p;
  //define a gamestate
  struct gameState G;

  printf ("Testing game is over function.\n");

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

    //call function with test input
    error=unitTest(&G);

    if (error > 0){
        if(error == 1){
            errorA++;
        }else if(error == 2){
            errorB++;
        }else{
            errorC++;
        }
    }
  }
  printf ("ALL Random TESTS Complete\n");
  printf ("Errors type 1: %d ",errorA);
  printf ("Error memory size wrong.\n");
  printf ("Errors type 2: %d ",errorB);
  printf("Error bad return value from function \n");
  printf ("Errors type 3: %d ",errorC);
  printf("Error negative supply count \n");

  return 0;
}
