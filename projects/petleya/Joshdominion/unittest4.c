#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing isGameOver

int main(){
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	initializeGame(4, k, 43, &G);
	int rval = isGameOver(&G);
	if(rval !=0){
		printf("Fail: declaring game over at the start of game\n");
	}
	else{
		printf("Pass: game not ended correctly identified\n");
	}
	G.supplyCount[province] = 0;
	rval = isGameOver(&G);
	if(rval != 1){
		printf("Fail: out of province cards and game not declared over\n");
	}
	else{
		printf("Pass: Correctly identified end of game due to provinces out\n");
	}
	G.supplyCount[province] = 12;
	G.supplyCount[2] = 0;
	G.supplyCount[3] = 0;
	G.supplyCount[4] = 0;
	rval = isGameOver(&G);
	if(rval != 1){
		printf("Fail: out of cards in three piles and game not declared over\n");
	}
	else{
		printf("Pass: Correctly identified end of game for three piles empty\n");
	}
	return 0;
}
