#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing updateCoins

int main () {
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	initializeGame(2, k, 98, &G);
	G.handCount[0] = 5;
	srand(100);
	int i;
	int r;
	int tcoin=0;
	G.coins=0;
	for(i=0; i < 5; i++){
		r = rand() % 3;
		if(r == 3){
			G.hand[0][i] = copper;
			tcoin = tcoin + 1;
		}
		if(r == 2){
			G.hand[0][i] = silver;
			tcoin = tcoin + 2;
		}
		if (r !=2 && r!=3){
			G.hand[0][i] = gold;
			tcoin = tcoin + 3;
		}
	}
	updateCoins(0, &G, 0);
	if(tcoin != G.coins){
	printf("Error with update coin tcoin is %d and Gcoins is %d\n", tcoin, G.coins);
	}
	else{
		printf("Test complete, no error\n");
	}
	return 0;
}
