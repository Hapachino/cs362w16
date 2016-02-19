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


//oracle makes sure returns valid 
int unitTest(int player, struct gameState *post, int choice1){
    srand(time(NULL));

    //define variables
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));

    //call function
        baronCard(player,post,choice1);

    //memcmp game state size
    if (memcmp(&pre,post, sizeof(struct gameState))!=0){
        #if (NOISY_TEST == 1)
        printf("Memory mismatch \n");
        #endif
        return 1;
    }

    // +1 Buy, You may discard an Estate card. 
    // If you do, +4 coins. Otherwise, gain an Estate card.
    //card specific checks

    //plus one buy
    if (post->numBuys != pre.numBuys){
        #if (NOISY_TEST == 1) 
        printf("Player did not get an additional buy\n");
        #endif
        return 2;
    }
    //if they discard an estate
    if(post-> handCount[player] == pre.handCount[player]-1){
        if(post->supplyCount[estate] == pre.supplyCount[estate]-1){
            if(post->coins != pre.coins+4){
                #if (NOISY_TEST == 1)
                printf("player discarded estate but did not gain coins\n");
                #endif
                return 3;
            }
        }
        else{
            #if (NOISY_TEST == 1)
            printf("card discarded was not an estate\n");
            #endif
            return 4;
        }
    }else{
        //if they don't discard and estate
        if(choice1 < 1){
            #if (NOISY_TEST == 1)
            printf("player choice was to discard an estate but instead they must gain an estate because they have no estates to discard");
            #endif
            return 5;

        }
        if(post->supplyCount[estate] != pre.supplyCount[estate]+1){
            #if (NOISY_TEST == 1)
            printf("player didn't discard an estate and did not gain one after \n");
            #endif
            return 6;
        }
    }
    
    return 0;
}

int main () {
  //define variables  
  int i, n, r, p,error,errorA,errorB,errorC,errorD,errorE,errorF;
  errorA =0;
  errorB =0;
  errorC =0;
  errorD =0;
  errorE =0;
  errorF =0;

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
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.numPlayers= floor(Random() * MAX_PLAYERS);
    G.numBuys = floor(Random() * MAX_HAND);//NEW
    G.coins = floor(Random() * MAX_DECK);//NEW
    //intialize arrays to 0
    for (int i =0; i< G.numPlayers +1; i++){
    	G.deckCount[i] = floor(Random() * MAX_DECK);
    	G.discardCount[i] = floor(Random() * MAX_DECK);
    	G.supplyCount[i]=floor(Random() * MAX_DECK);
        G.discard[i][ G.discardCount[i] ] = floor(Random() * MAX_DECK);
        G.discardCount[i]= floor(Random() * MAX_DECK);
    }
    int choice1 = floor(Random() * 2);//boolean true or false
    //call function with test input
    error=unitTest(G.numPlayers,&G,choice1);

    if (error > 0){
        if(error == 1){
            errorA++;
        }else if(error == 2){
            errorB++;
        }else if(error == 3){
            errorC++;
        }else if(error == 4){
            errorD++;
        }else if(error == 5){
            errorE++;
        }else if(error == 6){
            errorF++;
        }

    }
  }
  printf ("ALL Random TESTS Complete\n");
  printf ("Errors type 1: %d memory mismatch \n",errorA);
  printf ("Errors type 3: %d player didn't receive extra buy\n",errorB);
  printf ("Errors type 3: %d discarded but didn't receive coins\n",errorC);

  printf ("Errors type 4: %d estate not discarded\n",errorC);
  printf ("Errors type 5: %d choice doesn't match action\n",errorD);
  printf ("Errors type 6: %d didn't gain estate\n",errorE);

  return 0;
}
