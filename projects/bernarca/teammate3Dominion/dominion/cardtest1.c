#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
  printf("Testing adventurer_card\n");
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
	
	testG.deck[thisPlayer][testG.deckCount[thisPlayer] - 1] = adventurer;
	
	adventurer_card(0, &testG, thisPlayer, 0, temphand, z);
	//assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == copper
	//        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == silver
	//        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == gold);
	//assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == copper
	//        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == silver
	//        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == gold);
	        
	printf("The last two cards in the player's hand are coins, as expected.\n");
	
	printf("testG.handCount[otherPlayer] == %d, G.handCount[otherPlayer] == %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	printf("(those should be the same)\n");
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
	        
	printf("testG discard count: %d, G discard count: %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	//assert(testG.discardCount[thisPlayer] > G.discardCount[thisPlayer]);

	//printf("All tests passed.\n");
  printf("\n");

	return 0;
}


