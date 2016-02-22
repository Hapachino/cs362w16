/*
Rishi Bhandarkar
CS 362

Unit test for Council Room card
Gamestate
	- The game is initiated for 2 players, and both players are dealt 3 estate cards and 7 copper cards
	- Player 1 draws 5 cards and plays Council Room card

Requirements to test
	- After the council room card is played by Player 1
		- Player 1 will draw 4 cards (+3 net after P1 discard Council Room)
		- Player 1 will have an extra buy
		- Player 1 deck will be reduced by 4
		- Player 2 has +1 to hand, -1 to deck
		- Kingdom/Victory cards are unchanged
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
	int seed = 1000, flag = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, council_room, smithy};
	struct gameState G, prevG;

	SelectStream(2);
	PutSeed(3);

	initializeGame(2, k, seed, &G);
	//add council_room card to Player 1 hand for testing
	gainCard(council_room, &G, 2, 0);
	memcpy(&prevG, &G, sizeof(struct gameState));
	
	
	printf ("Testing the 'Council Room' card\n");
	cardEffect(council_room, 0, 0, 0, &G, G.handCount[0]-1, 0);
	if(prevG.handCount[0]+3 != G.handCount[0]){
		printf("TEST FAILED: Council Room added incorrect number of cards to your hand\n");
		flag = 1;
	}
	if(prevG.numBuys+1 != G.numBuys){
		printf("TEST FAILED: Council Room not rewarding 1 buy to Player 1\n");
		flag = 1;
	}
	
	if(prevG.deckCount[0]-4 < G.deckCount[0]){
		printf("TEST FAILED: Council Room didn't draw the right amount of cards from the deck\n");
		flag = 1;
	}
	if(prevG.handCount[1]+1 != G.handCount[1]){
		printf("TEST FAILED: Council Room didn't give Player 2 a card\n");
		flag = 1;
	}
	if(prevG.deckCount[1]-1 != G.deckCount[1]){
		printf("TEST FAILED: Council Room didn't draw from Player 2's deck\n");
		flag = 1;
	}
	if(prevG.discardCount[1] != G.discardCount[1]){
		printf("TEST FAILED: Council Room altered Player 2's cards\n");
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