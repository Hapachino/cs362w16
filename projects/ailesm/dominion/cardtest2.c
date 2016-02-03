#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
	int seed = 1000, flag = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState G, prevG;

	SelectStream(2);
	PutSeed(3);

	initializeGame(2, k, seed, &G);
	//add Village card to Player 1 hand for testing
	gainCard(village, &G, 2, 0);	
	memcpy(&prevG, &G, sizeof(struct gameState));

	printf ("Testing the 'Village' card\n");
	cardEffect(village, 0, 0, 0, &G, G.handCount[0]-1, 0);
	if(prevG.handCount[0] != G.handCount[0]){
		printf("TEST FAILED: Village added incorrect number of cards to your hand\n");
		flag = 1;
	}
	if(G.numActions != 2){
		printf("TEST FAILED: Actions not set to 2 after Village played\n");
		flag = 1;
	}
	
	if(prevG.deckCount[0]-1 < G.deckCount[0]){
		printf("TEST FAILED: Village didn't draw the right amount of cards from the deck\n");
		flag = 1;
	}
	if(prevG.handCount[1] != G.handCount[1]){
		printf("TEST FAILED: Village altered Player 2's cards\n");
		flag = 1;
	}
	if(prevG.deckCount[1] != G.deckCount[1]){
		printf("TEST FAILED: Village altered Player 2's cards\n");
		flag = 1;
	}
	if(prevG.discardCount[1] != G.discardCount[1]){
		printf("TEST FAILED: Village altered Player 2's cards\n");
		flag = 1;
	}
	
	printf("Test Victory and Kingdom piles..\n");
	int arraySize = sizeof(G.supplyCount) / sizeof(int);
	for(int i = 0; i < arraySize; i++){
		if(G.supplyCount[i] != prevG.supplyCount[i]){
			printf("TEST FAILED: Kingdom/Victory supplied have been altered\n");
			flag = 1;
		}
	}
	
	if(flag == 0){
		printf("TEST SUCCEEDED\n");
	}
	
	return 0;
}