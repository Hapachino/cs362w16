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

	printf("Testing smithy\n");
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	play_smithy(&testG, 0);
	printf("Expected: %d, Result: %d\n", G.handCount[G.whoseTurn] + 3, testG.handCount[testG.whoseTurn]);

	G.discardCount[G.whoseTurn] = 5;	
	memcpy(&testG, &G, sizeof(struct gameState));
	play_smithy(&testG, 0);
	
	discardCard(0, G.whoseTurn, &G, 0);
     
	printf("Expected discard count: %d, Result: %d\n", G.discardCount[G.whoseTurn], testG.discardCount[testG.whoseTurn]);
	
	return 0;
}
