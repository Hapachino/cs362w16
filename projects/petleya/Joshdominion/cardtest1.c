#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing smith function

int main(){
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(4, k, 200, &G);
	int i;
	for(i=0; i<5; i++){
	drawCard(2, &G);
	}
	int hc = G.handCount[0];
	playSmithy(0, &G);
	if(G.handCount[0] != hc + 2){
		printf("Fail: The players hand should be increase by 2, 3 added 1 discarded\n");
		printf("hand Count: %d hc:%d\n", G.handCount[0], hc);
	}
	else{
		printf("Pass: The correct hand count\n");
	}
return 0;
}
