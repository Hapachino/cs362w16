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


//oracle makes sure returns valid 
int unitTest(int player, struct gameState *post,int handPos, int choice){
    srand(time(NULL));

    //define variables
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));

    //call function
    int success;
    success=playSalvager(post, handPos, choice);
    if (success!=0){
        #if (NOISY_TEST == 1)
        printf("error returned from function \n");
        #endif
        return 1;

    }


    //memcmp game state size
    if (memcmp(&pre,post, sizeof(struct gameState))!=0){
        #if (NOISY_TEST == 1)
        printf("memory match error \n");
        #endif
        return 1;

    }
    //card specific checks
    if(post->numBuys != pre.numBuys+1){
        #if (NOISY_TEST == 1)
        printf("numbuys not incrimented by 1 \n");
        #endif
        return 2;
    }   

    //card specific checks
    if(post->handCount < pre.handCount){
        #if (NOISY_TEST == 1)
        printf("hand count was not decrimented \n");
        #endif
        return 3;
    }    
 
    return 0;
}


int main () {
  //define variables  
  int i, n, r, p,error,errorA,errorB,errorC;
  errorA =0;
  errorB =0;
  errorC=0;
  //define a array of cards

  //define a gamestate
  struct gameState G;

  printf ("Testing Salvager Card.\n");

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
    G.numPlayers = floor(Random()* MAX_PLAYERS);
    int choice= floor(Random() *MAX_DECK); 
    int handPos=floor(Random() * MAX_DECK);    

   //call function with test input
    error=unitTest(G.numPlayers,&G,handPos,choice);

    if (error > 0){
        if(error == 1){
            errorA++;
        }else if(error > 1){
            errorB++;
        }else if(error > 2){
            errorC++;
        }

    }
  }
  printf ("ALL Random TESTS Complete\n");
  printf ("Errors type 1: %d ",errorA);
  printf ("memory not same size \n");
  printf ("Errors type 2: %d ",errorB);
  printf("buy count not incrimented \n");
  printf ("Errors type 3: %d ",errorB);
  printf("hand count not decrimented \n");

  return 0;
}
