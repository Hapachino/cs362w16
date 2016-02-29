#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {copper, minion, mine, silver, gold, cutpurse,
		sea_hag, tribute, smithy, council_room};

	printf("Testing village card\n");
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	play_village(0, &testG, 0);
	printf("Expected: %d, Result: %d\n", G.handCount[G.whoseTurn] + 1, testG.handCount[testG.whoseTurn]);

	memcpy(&testG, &G, sizeof(struct gameState));
	play_village(0, &testG, 0);
     
	printf("Expected action count: %d, Result: %d\n", G.numActions + 2, testG.numActions);
	
	return 0;
}
