#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing discardCard

int main(){
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	initializeGame(3, k, 50, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	int playpile;
	int i;
	for(i=0; i<3; i++){
		G.playedCardCount=i;
		playpile = G.playedCardCount;
		discardCard(2, 2, &G, 0);
		playpile = playpile + 1;
		if(playpile != G.playedCardCount){
			printf("Discard error expected %d and got %d\n", playpile, G.playedCardCount);
			break;
		}
	}
	printf("Pass: non-trashed moved to played pile\n");
	G=testG;
	G.handCount[2]=2;
	discardCard(1, 2, &G, 1);
	if(G.handCount[2] != 1){
		printf("Fail: expected a hand count of 1 and got %d\n", G.handCount[2]);
	}
	discardCard(0, 2, &G, 1);
	if(G.handCount[2] != 0){
		printf("Fail: expected a hand count of 0 and got %d\n", G.handCount[2]);
	}
	G.handCount[2]=5;
	int lastcard = G.hand[2][4];
	discardCard(3, 2, &G, 1);
	if(G.handCount[2] !=4){
		printf("Fail: expected a hand count of 4 and got %d\n", G.handCount[2]);
	}
	else{
		if(G.hand[2][3]==lastcard){
			printf("Pass: position of card to delete is replaced with last card\n");
		}
		else{
			printf("Fail: last card did not swap with card to delete\n");
		}
	}
return 0;
}
