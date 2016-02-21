//baron
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1

// +1 Buy, You may discard an Estate card. 
// If you do, +4 coins. Otherwise, gain an Estate card.

//oracle makes sure returns valid 
int unitTest(int player, struct gameState *post,int choice1){
    srand(time(NULL));

    //define variables
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    int handPos= rand();

    //call function
        baronCard(player,post,choice1);

    //memcmp game state size
    if (memcmp(&pre,post, sizeof(struct gameState))!=0){
        #if (NOISY_TEST == 1)
        printf("Memory mismatch");
        #endif
        exit(1);
    }
    //card specific checks
    //plus one buy
    if (post->numBuys != pre.numBuys){
        #if (NOISY_TEST == 1) 
        printf("Player did not get an additional buy");
        #endif
        return 1;
    }
    //if they discard an estate
    if(post->discard == pre.discard+1){
        if(post->supplyCount[estate] == pre.supply[estate]-1){
            if(post->coins != pre.coins+4){
                #if (NOISY_TEST == 1)
                printf("player discarded estate but did not");
                #endif
                return 2;
            }
        }
        else{
            #if (NOISY_TEST == 1)
            printf("card discarded was not an estate");
            #endif
            return 2;
        }
    }else{
        //if they don't discard and estate
        if(post->estateCount != pre.estateCount+1){
            #if (NOISY_TEST == 1)
            printf("player didn't discard an estate and did not gain one after");
            #endif
            return 2;

        }
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
    int choice1=floor(Random() * 1);//boolean yes or no
    //call function with test input
    error=unitTest(G.numPlayers,&G,choice1);

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
