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

//Unit test for full Deck Count function
//Preconditions:
//function accepts  int player, int card, struct gameState *state,
//oracle makes sure returns valid 
int unitTest(int player, struct gameState *post){
    srand(time(NULL));

    //define variables
    int success;
    int card;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    //randomly card int within size limits
    card= rand()%10;
    
    //call function
    success=fullDeckCount(player,card, post);

    if (success > MAX_DECK){
        #if (NOISY_TEST == 1)
        printf ("Error in end turn function.\n");
        #endif
        return 1;
    }

    if (success == -1){
       #if (NOISY_TEST == 1) 
       printf ("Error in full deck function.\n");
        #endif
        return 2;
    }
    //memcmp game state size
    if (memcmp(&pre,post, sizeof(struct gameState))!=0){
        #if (NOISY_TEST == 1)
        printf ("Memory size different.\n");
        #endif
        return 3;
    }
    return 0;
}


int main () {
  //define variables  
  int i, n, r, p, error,errorA,errorB,errorC;
  errorA=0;
  errorB=0;
  errorC=0;
  //define a gamestate
  struct gameState G;

  printf ("Testing full deck count.\n");

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
    error=unitTest(p,&G);

    if (error > 0){
        if(error == 1){
            errorA++;
        }else if(error == 2){
            errorB++;
        }else if(error == 3){
            errorC++;
        }
    }

  }

  printf ("ALL TESTS OK\n");
  printf ("ALL Random TESTS Complete\n");
  printf ("Errors type 1: %d ",errorA);
  printf ("Error in end turn function.\n");
  printf ("Errors type 2: %d ",errorB);
  printf ("Error in full deck function.\n");
  printf ("Errors type 3: %d ",errorC);
  printf ("Memory size different.\n");

  return 0;
}
