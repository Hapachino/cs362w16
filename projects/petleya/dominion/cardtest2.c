#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing vill function

int main(){
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(2, k, 50, &G);
	int hcount = G.handCount[0];
	int acNum = G.numActions;
	if(acNum > 1){
		printf("Fail: the actions start at 1\n");
	}
	vill(&G, 3, 0);
	if(hcount == G.handCount[0]){
		printf("Pass: the hand count doesn't change\n");
	}
	else{
		printf("Fail: The hand count doesn't change\n");
		printf("expected %d but got %d\n", hcount, G.handCount[0]);
	}
	if(G.numActions == acNum +2){
		printf("Pass: two actions added\n");
	}
	else{
		printf("Fail: actions should be added\n");
	}
	
	return 0;
}
