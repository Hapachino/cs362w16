/*
Rishi Bhandarkar
CS 362

Unit test for Smithy card
Gamestate
	- The game is initiated for 2 players, and both players are dealt 3 estate cards and 7 copper cards
	- Player 1 draws 5 cards and plays Smithy card
	
Requirements to test
	- After Smithy card is played by Player 1
		- Player 1 should have 2 additional cards in their hand (Gain 3, discard Smithy)
		- Player 1 should have 3 less cards in their deck
		- Player 1 discard pile / Player 2 piles should be unchanged
		- No change for Kingdom/Victory piles
*/
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
	//add Smithy card to Player 1 hand for testing
	gainCard(smithy, &G, 2, 0);
	memcpy(&prevG, &G, sizeof(struct gameState));

	
	printf ("Testing the 'Smithy' card..\n");
	cardEffect(smithy, 0, 0, 0, &G, G.handCount[0]-1, 0);
	if(prevG.handCount[0]+2 != G.handCount[0]){
		printf("TEST FAILED: Smithy did not add 3 cards to your hand\n");
		flag = 1;
	}
	if(prevG.deckCount[0]-3 != G.deckCount[0]){
		printf("TEST FAILED: Smithy did not take 3 cards from your deck\n");
		flag = 1;
	}
	if(prevG.discardCount[0] != G.discardCount[0]){
		printf("TEST FAILED: Smithy altered discard pile\n");
		flag = 1;
	}
	if(prevG.handCount[1] != G.handCount[1]){
		printf("TEST FAILED: Smithy altered Player 2's cards\n");
		flag = 1;
	}
	if(prevG.deckCount[1] != G.deckCount[1]){
		printf("TEST FAILED: Smithy altered Player 2's cards\n");
		flag = 1;
	}
	if(prevG.discardCount[1] != G.discardCount[1]){
		printf("TEST FAILED: Smithy altered Player 2's cards\n");
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

	return 0;
}
