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
// set NOISY_TEST to 0 to remove printfs from output

/*code leveraged betterCard function and testUpdateCoins functions heavily.
Unit test for playCard function
Preconditions:
function accepts int handPos, int choice1, int choice2, int choice3, struct gameState *state) */

//oracle makes sure returns valid 
int unitTest(struct gameState *post){
    srand(time(NULL));

    //define variables
    int success;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));

    //create an array to hold four integer inputs
    int input[4];
    //randomly generate 4 ints
    for(int i=0; i<4; i++){
        input[i]= rand();
    }

    //call function
    success=playCard(input[0],input[1],input[2],input[3], post);

    //memcmp game state size
    assert (memcmp(&pre,post, sizeof(struct gameState))==0);

    //assert (success==0);
    if (success == -1){
        #if (NOISY_TEST == 1)
        printf ("Error in playCard function bad exit status.\n");
        #endif
        return 1;
    }

    //specific function check 
    //confirm that actions is one less
    if (pre.numActions != post->numActions+1){
        #if (NOISY_TEST == 1)
        printf("Error action count was not decrimented");
        #endif    
        return 2;
    }
    return 0;
}


int main () {
  //define variables  
  int i, n, p;
  int error, errorA, errorB;
  errorB=0;
  errorA=0; 
  //define a gamestate
  struct gameState G;

  printf ("Testing playCard.\n");

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
        }else if(error > 1){
            errorB++;
        }
    }
  }
  printf ("ALL Random TESTS Complete\n");
  printf ("Errors type 1: %d ",errorA);
  printf ("Error in playCard function bad exit status.\n");
  printf ("Errors type 2: %d ",errorB);
  printf("Error action count was not decrimented \n");

  return 0;
}
