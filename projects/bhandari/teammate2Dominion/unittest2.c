/*
Rishi Bhandarkar
CS 362

Unit test for drawCard() function
Gamestate
	- We start by initializing the game with 2 players
	- Each player has 3 estate cards and 7 copper cards in their deck
	- Player 1 draws 5 cards into their hand
Requirements to test
	- After Player 1 draws a card from their deck	
		- Player 1 hand should increase by 1
		- Player 1 deck should decrease by 1
		- Player 1 discard pile, and all player 2 piles should be unchanged
	- After Player 2 draws a card from their deck
		- Changes to Player 1 state from last draw should remain
		- Player 2 should have one more card in hand, one less in deck, same amount in discard
	- Kingdom and Victory piles should remain unchanged
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
	memcpy(&prevG, &G, sizeof(struct gameState));

	printf ("Testing the drawCard() method\n");
	printf("Player 1 drawing..\n");
	drawCard(0, &G);
	if(!(prevG.handCount[0]+1 == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0]-1 == G.deckCount[0])){
		printf("TEST FAILED: Player 1 deck count incorrect\n");
		flag = 1;
	}
	if(!(prevG.discardCount[0] == G.discardCount[0])){
		printf("TEST FAILED: Player 1 discard count incorrect\n");
		flag = 1;
	}
	if(!(prevG.handCount[1] == G.handCount[1])){
		printf("TEST FAILED: Player 2 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[1] == G.deckCount[1])){
		printf("TEST FAILED: Player 2 deck count incorrect\n");
		flag = 1;
	}
	if(!(prevG.discardCount[1] == G.discardCount[1])){
		printf("TEST FAILED: Player 2 discard count incorrect\n");
		flag = 1;
	}

	printf("Player 2 drawing..\n");
	drawCard(1, &G);	
	if(!(prevG.handCount[0]+1 == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0]-1 == G.deckCount[0])){
		printf("TEST FAILED: Player 1 deck count incorrect\n");
		flag = 1;
	}
	if(!(prevG.discardCount[0] == G.discardCount[0])){
		printf("TEST FAILED: Player 1 discard count incorrect\n");
		flag = 1;
	}
	if(!(prevG.handCount[1]+1 == G.handCount[1])){
		printf("TEST FAILED: Player 2 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[1]-1 == G.deckCount[1])){
		printf("TEST FAILED: Player 2 deck count incorrect\n");
		flag = 1;
	}
	if(!(prevG.discardCount[1] == G.discardCount[1])){
		printf("TEST FAILED: Player 2 discard count incorrect\n");
		flag = 1;
	}
	
	printf("Test if Victory and Kingdom piles are unchanged..\n");
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
