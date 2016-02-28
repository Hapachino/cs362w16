/*
Filename:	unittest3.c
Author:		Chris Loomis
Created:	1/30/2016
Last Mod:	1/30/2016

This is a unit test of isGameOver() from dominion.c, lines 390-415.
isGameOver() takes struct gameState *state as an argument.
A game ends when there are either no more province cards, or 3 or more cards have run out.
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
	
	printf("----------------- Testing isGameOver() ----------------\n\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
//no provinces left	
	testG.supplyCount[province] = 0;
	
	if(isGameOver(&testG) != 1)
		printf(" !!! Game testG did not end with 0 province cards remaining, FAILED !!!\n");
	else
		printf("Game testG ended properly with 0 province cards remaining\n");
	
	if(isGameOver(&G) != 0)
		printf(" !!! Game G ended prematurely while testing 0 province cards, FAILED !!!\n");
	
	memcpy(&testG, &G, sizeof(struct gameState));
//-1 provinces left, absurd
	testG.supplyCount[province] = -1;
	
	if(isGameOver(&testG) != 1)
		printf(" !!! Game testG did not end with -1 province cards remaining, FAILED !!!\n");
	else
		printf("Game testG ended properly with -1 province cards remaining\n");
	
	if(isGameOver(&G) != 0)
		printf(" !!! Game G ended prematurely while testing -1 province cards, FAILED !!!\n");
	
	memcpy(&testG, &G, sizeof(struct gameState));
//1 provinces left, should not end, boundary case
	testG.supplyCount[province] = 1;
	
	if(isGameOver(&testG) != 0)
		printf(" !!! Game testG ended prematurely with 1 province card remaining, FAILED !!!\n");
	else
		printf("Game testG did not end prematurely with 1 province card remaining\n");
	
	if(isGameOver(&G) != 0)
		printf(" !!! Game G ended prematurely while testing 1 province cards, FAILED !!!\n");
	
	memcpy(&testG, &G, sizeof(struct gameState));
//three cards are out	
	testG.supplyCount[adventurer] = 0;
	testG.supplyCount[embargo] = 0;
	testG.supplyCount[village] = 0;
	
	if(isGameOver(&testG) != 1)
		printf(" !!! Game testG did not end with 3 supply count at 0, FAILED !!!\n");
	else
		printf("Game testG ended properly with 3 supply count at 0\n");
	
	if(isGameOver(&G) != 0)
		printf(" !!! Game G ended prematurely while testing 0 supply count for 3 cards, FAILED !!!\n");
	
		memcpy(&testG, &G, sizeof(struct gameState));
//two cards are out, should not end, boundary case
	testG.supplyCount[minion] = 0;
	testG.supplyCount[mine] = 0;
	
	if(isGameOver(&testG) != 0)
		printf(" !!! Game testG ended prematurely with 2 supply count at 0, FAILED !!!\n");
	else
		printf("Game testG did not end with 2 supply count at 0\n");
	
	if(isGameOver(&G) != 0)
		printf(" !!! Game G ended prematurely while testing 0 supply count for 2 cards, FAILED !!!\n");
	
			memcpy(&testG, &G, sizeof(struct gameState));
//four cards are out, should end, boundary case
	testG.supplyCount[cutpurse] = 0;
	testG.supplyCount[feast] = 0;
	testG.supplyCount[tribute] = 0;
	testG.supplyCount[smithy] = 0;
	
	if(isGameOver(&testG) != 1)
		printf(" !!! Game testG did not end with 4 supply count at 0, FAILED !!!\n");
	else
		printf("Game testG ended properly with 4 supply count at 0\n");
	
	if(isGameOver(&G) != 0)
		printf(" !!! Game G ended prematurely while testing 0 supply count for 4 cards, FAILED !!!\n");
	
	printf("\n >>>>> Test complete <<<<<\n\n");
	
	return 0;
}