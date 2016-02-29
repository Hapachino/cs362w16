#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing council function

int main(){
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(3, k, 49, &G);
	int hcount = G.handCount[0];
	int hcount1 = G.handCount[1];
	int hcount2 = G.handCount[2];
	int nBuy = G.numBuys;
	council(&G, 2, 1);
	if(G.handCount[0] == hcount +3){
		printf("Pass: Players hand increase by 3\n");
	}
	else{
		printf("Fail: Players hand not properly increase\n");
	}
	if(G.numBuys == nBuy + 1){
		printf("Pass: number of buys increase by 1\n");
	}
	else{
		printf("Fail: number of buys should increase by 1\n");
	}
	if(G.handCount[1] == hcount1 + 1 && G.handCount[2] == hcount2 + 1 ){
		printf("Pass: The other players each gain a card\n");
	}
	else{
		printf("Fail: The other players should have gained a card each\n");
	}
	return 0;
}
