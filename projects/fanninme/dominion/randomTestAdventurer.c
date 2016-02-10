//Adventurer
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

//Unit test for Adventurer Card
//function accepts: currentplayer, struct gameState *state 

//oracle makes sure returns valid 
int unitTest(int player,struct gameState *post){
    srand(time(NULL));

    //define variables
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));

    //call function
    adventurerCard(player, post);

    //memcmp game state size
    if(memcmp(&pre,post, sizeof(struct gameState))!=0){
        #if (NOISY_TEST == 1)
        printf("gameState memory is wrong\n");
        #endif
        return 1;
    }
    //card specific checks 
    if(post->hand[player][post->handCount[player]] < 0){
        #if (NOISY_TEST==1)
        printf("invalid hand size\n");
        #endif
    }
    
    //player hand size should be 2 larger after gaining treasure
    if(post->handCount != pre.handCount +2){
        #if (NOISY_TEST == 1)
        printf("Player did not receive 2 additional cards correctly\n");
        #endif
        return 2;
    }
    //player should have at least 2 more treasures
    if(post->coins < pre.coins +2){
        #if (NOISY_TEST ==1)
        printf("player did not receive 2 additional coins\n");
        #endif
        return 3;
    }

    return 0;
}

//section directly uses code from betterCardTest.c
int main () {
  //define variables  
  int i, n, r, p, error,errorA,errorB,errorC;
  errorA =0;
  errorB =0;
  errorC =0;
  //define a gamestate
  struct gameState G;

  printf ("Testing adventurer card.\n");

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
    G.numBuys = floor(Random() * MAX_HAND);//NEW
    G.coins = floor(Random() * MAX_DECK);//NEW
    G.numPlayers = floor(Random() * MAX_PLAYERS);

    //int player = 1; //floor(Random() * MAX_PLAYERS);
    //G.hand[player][G.handCount[player]]=floor(Random() * MAX_HAND);

    for (int i =0; i< G.numPlayers +1; i++){
    	G.deckCount[i] = floor(Random() * MAX_DECK);
        G.handCount[i]= floor(Random() * MAX_DECK);
        G.hand[i][G.handCount[i]] = floor(Random() * MAX_HAND);
    }

    //call function with test input
    error=unitTest(G.numPlayers,&G);

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
   printf("gameState memory is wrong\n");

  printf ("Errors type 2: %d ",errorB);
  printf("Player did not receive 2 additional cards correctly\n");

  printf ("Errors type 3: %d ",errorC);
  printf("player did not receive 2 additional coins\n");

  return 0;
}
