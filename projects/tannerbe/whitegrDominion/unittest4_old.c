/* unittest4.c - testing isGameOver()

	REQUIREMENTS:
        The game ends at the end of any player's turn in which at least one of the following is true:
        Any three Supply piles are empty. (Any four piles when playing with five or six players.) 
	This includes all the Supply piles, not just the 10 Kingdom card piles that are selected for each game. 
        
	int isGameOver(struct gameState *state) {
  	int i;
  	int j;
	
  	//if stack of Province cards is empty, the game ends
  	if (state->supplyCount[province] == 0)
    	{
      	return 1;
    	}

  	//if three supply pile are at 0, the game ends
  	j = 0;
  	
	for (i = 0; i < 25; i++)
    	{
      	if (state->supplyCount[i] == 0)
		{
	  	j++;
		}
    	}
  	if ( j >= 3)
    	{
      	return 1;
    	}

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
 	
	
	printf("Testing isGameOver() unittest4.c\n");

	struct gameState G;
    	int seed = 1000;
    	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};	
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 2;
    G.numActions = 10;
    G.whoseTurn = 0;

	printf("Test 1:\n");
		G.supplyCount[province]=0;
		if (isGameOver(&G)){
			printf("Provence Cards 0 = Game Over....Passed\n");	
		}else{
			printf("Provence Cards 0 = Game Over....Fail\n");
		}	
		//G.supplyCount[province]=10;
	printf("Test 2:\n");
		//initializeGame(numPlayers, k, seed, &G);
		G.supplyCount[adventurer]=0;
		G.supplyCount[embargo]=0;
		G.supplyCount[village]=0;
		if (isGameOver(&G)){
			printf("Three Piles Empty = Game Over....Passed\n");	
		}else{
			printf("Three Piles Empty = Game Over....Fail\n");
		}	


	 //Check if no decrease in coins
    	if (G.coins != 2){
		printf("State Promblem: coins");
    	}

	//Check if no change in actions
     	if (G.numActions != 10){
		printf("State Problem: numActions");
    	}

	//check if no change in turns
    	if (G.whoseTurn != 0){
		printf("State Problem: Turn");
    	}



	printf("END Testing isGameOver() unittest4.c\n");
	
	return 0;

} 