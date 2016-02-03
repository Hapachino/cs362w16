#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	int x, y, z, rtotal, ftotal;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};
	
	
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing fullDeckCount\n");
	
	x = rand() % 10;
	y = rand() % 20;
	z = rand() % 10;
	
	G.handCount[0] = x;
	G.deckCount[0] = y;
	G.discardCount[0] = z;
	
	rtotal = x + y + z;
	ftotal = fullDeckCount(0, smithy, &G);
	
	if(rtotal != ftotal)
	{
		printf("Test failed. Result: %d, Expected: %d\n", rtotal, ftotal);
	}
	else
	{
		printf("Test passed\n");
	}

	return 0;
}
