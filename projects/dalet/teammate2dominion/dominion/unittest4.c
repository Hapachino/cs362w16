/*
Rishi Bhandarkar
CS 362

Unit test for gainCard() function
Gamestate
	- The game is initiated for 2 players, and both players are dealt 3 estate cards and 7 copper cards
	- Player 1 draws 5 cards

Requirements to test
	- Player 1 will attempt to add a card from the supply that does not exist (the 'feast' card)
		- Hand, deck, and discard piles for both players should not change after failed add attempt
	- Player 1 will add the 'adventurer' card to their hand
		- Hand size should go up by 1 for Player 1
		- Player 1 discard/deck and all Player 2 piles should be unchanged
		- The Kingdom/Victory cards should remain unchaned except one fewer 'adventurer' card
	- Player 1 will add the 'adventurer' card to their deck
		- Player 1 hand size will remain 1 larger, deck will increase by 1
		- Player 1 discard will remain, and all player 2 piles will remain unchanged
		- The Kingdom/Victory cards should remain unchanged except two fewer 'adventurer' cards
	- Player 1 will add the 'adventurer' card from supply to their discard pile
		- Player 1 hand size and deck will remain 1 larger, discard pile will increase by 1
		- Player 2 piled remain unchanged
		- The Kingdom/Victory cards should remain unchanged except three fewer 'adventurer' cards
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

	printf ("Testing the gainCard() method\n");
	
	printf("Attempting to add a card not in the supply..\n");
	int noCard = gainCard(feast, &G, 2, 0);
	if(noCard != -1){
		printf("TEST FAILED: attempt to add non-existant card failed\n");
		flag = 1;
	}
	
	if(!(prevG.handCount[0] == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0] == G.deckCount[0])){
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

	printf("Adding 'Adventurer' from supply to Player 1's hand..\n");
	gainCard(adventurer, &G, 2, 0);
	if(!(prevG.handCount[0]+1 == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0] == G.deckCount[0])){
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
	
	printf("Test Victory and Kingdom piles [after adding to hand]..\n");
	int arraySize = sizeof(G.supplyCount) / sizeof(int);
	for(int i = 0; i < arraySize; i++){
		if(G.supplyCount[i] != prevG.supplyCount[i]){
			if(i != adventurer){
				printf("TEST FAILED: Kingdom/Victory supplied have been altered\n");
				flag = 1;
			}
		}
	}

	printf("Add 'Adventurer' card from supply to Player 1's deck\n");
	gainCard(adventurer, &G, 1, 0);
	if(!(prevG.handCount[0]+1 == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0]+1 == G.deckCount[0])){
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
	
	printf("Test Victory and Kingdom piles [after adding to deck]..\n");
	arraySize = sizeof(G.supplyCount) / sizeof(int);
	for(int i = 0; i < arraySize; i++){
		if(G.supplyCount[i] != prevG.supplyCount[i]){
			if(i != adventurer){
				printf("TEST FAILED: Kingdom/Victory supplied have been altered\n");
				flag = 1;
			}
		}
	}

	printf("Add 'Adventurer' from supply to Player 1's discard pile\n");
	gainCard(adventurer, &G, 0, 0);
	if(!(prevG.handCount[0]+1 == G.handCount[0])){
		printf("TEST FAILED: Player 1 hand count incorrect\n");
		flag = 1;
	}
	if(!(prevG.deckCount[0]+1 == G.deckCount[0])){
		printf("TEST FAILED: Player 1 deck count incorrect\n");
		flag = 1;
	}
	if(!(prevG.discardCount[0]+1 == G.discardCount[0])){
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
	
	printf("Test Victory and Kingdom piles [after adding to discard pile]..\n");
	arraySize = sizeof(G.supplyCount) / sizeof(int);
	for(int i = 0; i < arraySize; i++){
		if(G.supplyCount[i] != prevG.supplyCount[i]){
			if(i != adventurer){
				printf("TEST FAILED: Kingdom/Victory supplied have been altered\n");
				flag = 1;
			}
		}
	}

	if(flag == 0){
		printf("TEST SUCCEEDED\n");
	}

	return 0;
}
