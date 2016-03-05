#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    printf("Testing smithy_card\n");
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

	
	smithy_card(thisPlayer, &testG, 1);
	printf("G.handCount[thisPlayer]: %d, testG.handCount[thisPlayer]: %d (testG should be 3 more)\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
  printf("G.handCount[otherPlayer]: %d, testG.handCount[otherPlayer]: %d (should be equal)\n", G.handCount[otherPlayer], testG.handCount[otherPlayer]);
  //assert(G.handCount[thisPlayer] == testG.handCount[thisPlayer] - 3);
  //assert(G.handCount[otherPlayer] == testG.handCount[otherPlayer]);


	//printf("All tests passed.\n");
  printf("\n");
	return 0;
}


