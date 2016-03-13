/* unittest2.c

   SUMMARY:
   1. Check if we have enough player buys.
   2. Check if card is in supply stack
   3. Check if we have enough money
   4. Buy - Call GainCard w/ parameters; and deduct coins, number of buys

   FUNCTION TO TEST: 
     int buyCard(int supplyPos, struct gameState *state) {
     int who;
     if (DEBUG){
         printf("Entering buyCard...\n");
     }

     // I don't know what to do about the phase thing.

     who = state->whoseTurn;

     if (state->numBuys < 1){
        if (DEBUG)
           printf("You do not have any buys left\n");
       return -1;
     } else if (supplyCount(supplyPos, state) <1){
     if (DEBUG)
      printf("There are not any of that type of card left\n");
     return -1;
     } else if (state->coins < getCost(supplyPos)){
      if (DEBUG) 
          printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
          return -1;
      } else {
         state->phase=1;
        //state->supplyCount[supplyPos]--;
        gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
  
        state->coins = (state->coins) - (getCost(supplyPos));
        state->numBuys--;
        if (DEBUG)
        printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
      }

  //state->discard[who][state->discardCount[who]] = supplyPos;
  //state->discardCount[who]++;
    
  return 0;
}
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
   
	 printf("Testing BuyCard() unittest2.c\n");	

	struct gameState G;
    	int seed = 1000;
    	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};	
	initializeGame(numPlayers, k, seed, &G);

	//enough buys
	G.numBuys = 0;
	if (buyCard(smithy,&G) == -1){
		printf("Error if No enough Buy...Passed\n");
	}else {
		printf("Error if No enough Buy...Failed\n");
	}

	//enough cards
	G.numBuys = 1;
	G.supplyCount[village] = 0;
	if (buyCard(village,&G) == -1){
		printf("Check Cant Buy No  Supplies...Passed\n");
	}else {
		printf("Check Cant  Buy No Supplies...Failed\n");
	}

	//do we have enough money
	G.numBuys = 1;
	G.supplyCount[village] = 1;
	G.coins = 1;
	if (buyCard(village,&G) == -1){
		printf("Check if enough money...Passed\n");
	}else {
		printf("Check if enough money...Fail\n");
	}


	//money decreased
	G.numBuys = 1;
	G.supplyCount[village] = 1;
	G.coins = 6;
	buyCard(village,&G);
	if ((G.coins) < 6){
		printf("Check if money dec...Passed\n");
	}else {
		printf("Check if money dec...Fail\n");
	}

	//buys decreased
	G.numBuys = 1;
	G.supplyCount[village] = 5;
	G.coins = 6;
	buyCard(village,&G);
	if ((G.numBuys) < 6){
		printf("Check if buys decreased...Passed\n");
	}else {
		printf("Check if buys decreased...Fail\n");
	}

	G.coins = 2;
    G.numActions = 10;
    G.whoseTurn = 0;
	
	  //Check if no decrease in coins
    if (G.coins != 2){
	printf("State Promblem: coins");
    }

     if (G.numActions != 10){
	printf("State Problem: numActions");
    }

    if (G.whoseTurn != 0){
	printf("State Problem: Turn");
    }


	printf("END Testing BuyCard() unittest2.c\n");	

	return 0;
} 
