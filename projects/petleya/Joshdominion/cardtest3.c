#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing stew function

int main(){
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(3, k, 76, &G);
	int hcount = G.handCount[0];
	if(G.handCount[0] < 4){
		printf("Fail: the hand count is too low\n");
	}
	cardEffect(steward, 2, 2, 2, &G, 3, 0);
	if(G.handCount[0]==hcount + 1){
		printf("Pass: Hand count up by one card 2 added 1 discarded\n");
	}
	else{
		printf("Fail: Hand count not adjusted correctly\n");
	}
	int ccount = G.coins;
	cardEffect(steward, 2, 2, 2, &G, 3, 0);
	if(G.coins == ccount +2){
		printf("Pass: The amount of coins increases by 2\n");
	}
	else{
		printf("Fail: The amount of coins increase by 2\n");
	}
return 0;
}
