#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
  printf("testing council_room_card\n");
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

	council_room_card(thisPlayer, &testG, 1);
	printf("old hand count: %d, new hand count: %d (new should be 4 more)\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
	printf("Old # of buys: %d, new # of buys: %d (new should be 1 more)\n", G.numBuys, testG.numBuys);
	printf("Old enemy hand count: %d, new enemy hand count: %d (new should be 1 more)\n", G.handCount[otherPlayer], testG.handCount[otherPlayer]);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 4);
	//assert(testG.numBuys == G.numBuys + 1);
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer] + 1);


	//printf("All tests passed.\n");
  printf("\n");
	return 0;
}


