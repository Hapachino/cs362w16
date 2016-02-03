#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {copper, silver, gold, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing updateCoins\n");
	
	G.handCount[0] = 1;
	G.hand[0][0] = copper;
	updateCoins(0, &G, 0);
	if(G.coins == 1){
		printf("Passed copper test\n");
	}
	else{
		printf("Failed copper test\n");
	}
	G.coins = 0;
	
	G.hand[0][0] = silver;
	updateCoins(0, &G, 0);
	if(G.coins == 2){
		printf("Passed silver test\n");
	}
	else{
		printf("Failed silver test\n");
	}
	G.coins = 0;
	
	G.hand[0][0] = gold;
	updateCoins(0, &G, 0);
	if(G.coins == 3){
		printf("Passed copper test\n");
	}
	else{
		printf("Failed copper test\n");
	}
	G.coins = 0;

	G.handCount[0] = 3;	
	G.hand[0][0] = copper;
	G.hand[0][1] = silver;
	G.hand[0][2] = gold;
	updateCoins(0, &G, 4);
	if(G.coins == 10){
		printf("Passed all plus bonus test\n");
	}
	else{
		printf("Failed all plus bonus test.\n");
		printf("Expected: 10, Actual: %d\n", G.coins);
	}

	return 0;
}
