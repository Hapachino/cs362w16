/*
Filename:	unittest2.c
Author:		Chris Loomis
Created:	1/27/2016
Last Mod:	1/27/2016

This is a unit test of updateCoins() from dominion.c, lines 1196-1224.
updateCoins() takes int player, struct gameState *state, and int bonus as arguments.
It calculates the number of coins the player has based on treasure cards in their hand.
bonus is used if any cards played grant them extra coins.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {
	int i;
	time_t t;
	int seed = 50;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, feast, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing updateCoins() ----------------\n\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//no coins
	for(i=0; i < testG.handCount[0]; i++)
		testG.hand[0][i] = estate;
	
	updateCoins(0, &testG, 0);
	
	if(testG.coins != 0){
		printf(" !!! Test 0, no coins in hand, FAILED !!!\n");
		printf(" !!! coins is %d !!!\n", testG.coins);
	}
	else
		printf("Test 0, no coins in hand, PASSED\n");
	
	//this makes the hand 1 copper and 4 estate
	testG.hand[0][0] = copper;
	for(i=1; i<testG.handCount[0]; i++)
		testG.hand[0][i] = estate;
	
	updateCoins(0, &testG, 0);
	
	if(testG.coins != 1){
		printf(" !!! Test 1, copper in hand at index 0, FAILED !!!\n");
		printf(" !!! coins is %d !!!\n", testG.coins);
	}
	else
		printf("Test 1, copper in hand at index 0, PASSED\n");
	
	srand(time(&t));
	
	//float r = rand();
	//printf("\nRandom() test result is %f\n", r);
	int r = rand();
	//printf("\nrand() test result is %d\n", r);
	int rc = r % (testG.handCount[0]);
	//printf("random card selected %d from %d", rc, testG.handCount[0]);
	
	//no coins
	for(i=0; i < testG.handCount[0]; i++)
		testG.hand[0][i] = estate;
	//place silver randomly in hand
	testG.hand[0][rc] = silver;
	
	updateCoins(0, &testG, 0);
	
	if(testG.coins != 2){
		printf(" !!! Test 2, silver in hand at random index %d, FAILED !!!\n", rc);
		printf(" !!! coins is %d !!!\n", testG.coins);
	}
	else
		printf("Test 2, silver in hand at random index %d, PASSED\n", rc);

	
	printf("\n >>>>> Test complete <<<<<\n\n");
	
	return 0;
}