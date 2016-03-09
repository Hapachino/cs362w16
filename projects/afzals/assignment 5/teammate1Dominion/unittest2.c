#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	int i, j;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int different = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing shuffle function\n");

	for(i = 0; i < 10; i++)
	{
			G.deck[0][i] = i;
	}
	
	G.deckCount[0] = 0;
	j = shuffle(0, &G);
	if(j == -1){
		printf("Passed Test 1\n");
	}
	else{
		printf("Failed Test 1\n");
	}

	G.deckCount[0] = 10;
	shuffle(0, &G);

	for(i = 0; i < 10; i++)
	{
		if(i != G.deck[0][i]){different++;};	
	}
	
	if(different < 8)
	{
		printf("Test Failed\n");
		for(i = 0; i < 10; i++)
		{
			printf("Start: %d, Shuffled: %d\n", i, G.deck[0][i]);	
		}
	}
	else
	{
		printf("Test Succeeded\n");
	}
	printf("Rearranged Cards: %d\n", different);

	return 0;
}
