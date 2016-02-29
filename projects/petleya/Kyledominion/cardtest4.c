#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//4=copper, 5=silver, 6 = gold

int main(){
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(4, k, 99, &G);
	G.discardCount[2] = G.deckCount[2];
	G.deckCount[2]=0;
	int handC = G.handCount[2];
	adventurerCard(&G, 2);

	int counts = G.handCount[2]+1- handC;
	int i;
	int c=0;
	if(G.deckCount + counts < 1){
		printf("Fail: the deck as not shuffled\n");
	}
	else{
		for(i=0; i<G.handCount[1]; i++){
			if(G.discard[1][i] == 4 || G.discard[1][i] == 5 || G.discard[1][i]==6){
				c++;
			}
				
		}
		if(c>0){
			printf("Fail: %d treasure cards were discarded\n", c);
		}
		else{
			printf("Pass: no treasure cards were discarded\n");
		}
	}
	int hcP1 = G.handCount[1];
	adventurerCard(&G, 2);

	if(G.handCount[1] - hcP1 < 1){
		printf("Fail: The player hand increases by at least one card\n");
	}
	else{
		printf("Pass: The player has the minimum amount of added cards\n");
		for(i=0; i<G.handCount[1]; i++){
			if(G.hand[1][i] == 4 || G.hand[1][i] == 5 || G.hand[1][i]==6){
				c++;
			}
				
		}
		if(c<2){
			printf("Fail: the player does not have the correct amount of treasure cards\n");
		}
	}
	return 0;	
}

