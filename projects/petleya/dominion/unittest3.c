#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing gainCard

int main(){
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	initializeGame(2, k, 88, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	G.supplyCount[3] = 0;
	int rval = gainCard(3, &G, 1, 2);
	if(rval != -1){
		printf("Fail: function did not detect and empty card pile\n");
	}
	G = testG;
	int deckNum = G.deckCount[2];
	deckNum = deckNum +1;
	gainCard(4, &G, 1, 2);
	if(G.deckCount[2] == deckNum){
		if(G.deck[2][deckNum-1] == 4){
			printf("Pass: card added to deck successfully\n");
		}
		else{
			printf("Fail: wrong card added to the deck %d\n", G.deck[2][deckNum]);
		}	
	}
	else{
		printf("Fail: deckCount not adjusted\n");
	}
	int handNum = G.handCount[2];
	gainCard(5, &G, 2, 2);
	if(G.handCount[2] == (handNum + 1)){
		if(G.hand[2][handNum] == 5){
			printf("Pass: card added to hand successfully\n");
		}
		else{
			printf("Fail: wrong card added to hand\n");
		}
	}
	else{
		printf("Fail: The handCount was not increased\n");
	}
	int disNum = G.discardCount[1];
	int supNum = G.supplyCount[6];
	gainCard(6, &G, 0, 1);
	if(G.discardCount[1] == disNum + 1){
		if(G.discard[1][disNum] == 6){
			printf("Pass: card added to discard pile successfully\n");
		}
		else{
			printf("Fail: wrong card added to discard\n");
		}
	}
	else{
		printf("Fail: The handCount was not increased\n");
	}
	if(G.supplyCount[6] != supNum -1){
		printf("Fail: The supply of card was not decreased\n");
	}
	return 0;
}
