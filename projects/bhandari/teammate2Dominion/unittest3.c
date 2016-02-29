/*
Rishi Bhandarkar
CS 362

Unit test for discardCard() function
Gamestate
	- Create an inital gamestate with 2 players, and each player is given 3 estate cards and 7 coppers
	- Player 1 draws 5 cards
Requirements to test
	- After Player 1 discards a card from the middle of his hand	
		- Player 1's hand must decrease by 1
		- Player 1's deck must remain unchanged
		- Player 1's discard pile must go up by 1
		- Player 2's hand, deck, and discard should remain unchanged
	- For the 3 times Player 1 removed the last card from his hand
		- Player 1's hand must decrease by 1
		- Player 1's deck must remain unchanged
		- Player 1's discard pile must go up by 1
		- Player 2's hand, deck, and discard should remain unchanged
	- After Player 1 discards the final card from his hand
		- Player 1's hand must decrease by 1
		- Player 1's deck must remain unchanged
		- Player 1's discard pile must go up by 1
		- Player 2's hand, deck, and discard should remain unchanged
	- After all discards, the Kingdom and Victory supplies must remain unchanged
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

	printf ("Testing the discardCard() method\n");
	
	printf("Discarding a card from the middle of Player 1's hand..\n");
	discardCard(2, 0, &G, 0);
	if(!(prevG.handCount[0]-1 == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect [middle card]\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0] == G.deckCount[0])){
		printf("TEST FAILED: Player 1 deck count incorrect [middle card]\n");
		flag = 1;
	}
	if(!(prevG.discardCount[0]+1 == G.discardCount[0])){
		printf("TEST FAILED: Player 1 discard count incorrect [middle card]\n");
		flag = 1;
	}
	if(!(prevG.handCount[1] == G.handCount[1])){
		printf("TEST FAILED: Player 2 hand count incorrect [middle card]\n");
		flag = 1;
	}
	if(!(prevG.deckCount[1] == G.deckCount[1])){
		printf("TEST FAILED: Player 2 deck count incorrect [middle card]\n");
		flag = 1;
	}
	if(!(prevG.discardCount[1] == G.discardCount[1])){
		printf("TEST FAILED: Player 2 discard count incorrect [middle card]\n");
		flag = 1;
	}
	if(!(prevG.playedCardCount+1 == G.playedCardCount)){
		printf("TEST FAILED: Played card count incorrect [middle card]\n");
		flag = 1;
	}

	printf("Removing the last card in Player 1's hand until 1 card remains..\n");
	int cards = G.handCount[0];
	for(int i = 0; i < cards-1; i++){
		discardCard(G.handCount[0]-1, 0, &G, 0);
		if(!(prevG.handCount[0]-(i+2) == G.handCount[0])){
			printf("TEST FAILED: Player 1 hand count incorrect [last card]\n");
			flag = 1;
		}
		if(!(prevG.deckCount[0] == G.deckCount[0])){
			printf("TEST FAILED: Player 1 deck count incorrect [last card]\n");
			flag = 1;
		}
		if(!(prevG.discardCount[0]+(i+2) == G.discardCount[0])){
			printf("TEST FAILED: Player 1 discard count incorrect [last card]\n");
			flag = 1;
		}
		if(!(prevG.handCount[1] == G.handCount[1])){
			printf("TEST FAILED: Player 2 hand count incorrect [last card]\n");
			flag = 1;
		}
		if(!(prevG.deckCount[1] == G.deckCount[1])){
			printf("TEST FAILED: Player 2 deck count incorrect [last card]\n");
			flag = 1;
		}
		if(!(prevG.discardCount[1] == G.discardCount[1])){
			printf("TEST FAILED: Player 2 discard count incorrect [last card]\n");
			flag = 1;
		}
		if(!(prevG.playedCardCount+(2+i) == G.playedCardCount)){
			printf("TEST FAILED: Played card count incorrect [last card]\n");
			flag = 1;
		}
	}


	printf("Removing the final card in Player 1's hand..\n");
	discardCard(0, 0, &G, 0);
	if(!(prevG.handCount[0]-5 == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect [final remaining card]\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0] == G.deckCount[0])){
		printf("TEST FAILED: Player 1 deck count incorrect [final remaining card]\n");
		flag = 1;
	}
	if(!(prevG.discardCount[0]+5 == G.discardCount[0])){
		printf("TEST FAILED: Player 1 discard count incorrect [final remaining card]\n");
		flag = 1;
	}
	if(!(prevG.handCount[1] == G.handCount[1])){
		printf("TEST FAILED: Player 2 hand count incorrect [final remaining card]\n");
		flag = 1;
	}
	if(!(prevG.deckCount[1] == G.deckCount[1])){
		printf("TEST FAILED: Player 2 deck count incorrect [final remaining card]\n");
		flag = 1;
	}
	if(!(prevG.discardCount[1] == G.discardCount[1])){
		printf("TEST FAILED: Player 2 discard count incorrect [final remaining card]\n");
		flag = 1;
	}
	if(!(prevG.playedCardCount+5 == G.playedCardCount)){
		printf("TEST FAILED: Played card count incorrect [final remaining card]\n");
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
