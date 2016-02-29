#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    printf("Testing village_card\n");
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
		int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	int temphand[100];
	int z;
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("testing for player 1...\n");
	village_card(thisPlayer, &testG, 1);
	printf("testG.numActions: %d, G.numActions: %d (testG should have 1 more)\n", testG.numActions, G.numActions);
	
	//assert(testG.numActions == G.numActions + 1);
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("testing for player 2...\n");
	village_card(otherPlayer, &testG, 1);
	printf("testG.numActions: %d, G.numActions: %d (testG should have 1 more)\n", testG.numActions, G.numActions);
	
	//assert(testG.numActions == G.numActions + 1);


	//printf("All tests passed.\n");
  printf("\n");
	return 0;
}


