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
	//add Adventurer card to Player 1 hand for testing
	gainCard(adventurer, &G, 2, 0);
	memcpy(&prevG, &G, sizeof(struct gameState));
	
	
	printf ("Testing the 'Adventurer' card\n");
	
	cardEffect(adventurer, 0, 0, 0, &G, G.handCount[0]-1, 0);
	if(prevG.handCount[0]+1 != G.handCount[0]){
		printf("TEST FAILED: Adventurer added incorrect number of cards to your hand\n");
		flag = 1;
	}
	if(G.hand[0][G.handCount[0]-2] != copper && G.hand[0][G.handCount[0]-2] != silver && G.hand[0][G.handCount[0]-2] != gold){
		printf("TEST FAILED: Adventurer added a card beside a treasure\n");
		flag = 1;
	}
	if(G.hand[0][G.handCount[0]-1] != copper && G.hand[0][G.handCount[0]-1] != silver && G.hand[0][G.handCount[0]-1] != gold){
		printf("TEST FAILED: Adventurer added a card beside a treasure\n");
		flag = 1;
	}
	if(prevG.deckCount[0]-2 < G.deckCount[0]){
		printf("TEST FAILED: Adventurer didn't draw enough cards from the deck\n");
		flag = 1;
	}
	if(prevG.handCount[1] != G.handCount[1]){
		printf("TEST FAILED: Adventurer altered Player 2's cards\n");
		flag = 1;
	}
	if(prevG.deckCount[1] != G.deckCount[1]){
		printf("TEST FAILED: Adventurer altered Player 2's cards\n");
		flag = 1;
	}
	if(prevG.discardCount[1] != G.discardCount[1]){
		printf("TEST FAILED: Adventurer altered Player 2's cards\n");
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