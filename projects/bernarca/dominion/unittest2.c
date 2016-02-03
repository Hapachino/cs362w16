#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
  
  printf("testing gainCard\n");
  
  
  
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
		int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
  int supplyPos = 1;
	G.supplyCount[supplyPos] = 10;
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	gainCard(1, &testG, 1, thisPlayer);

/*
	assert(testG.deck[ thisPlayer ][ testG.deckCount[thisPlayer] - 1] == supplyPos);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + 1);
	assert(testG.supplyCount[supplyPos] == G.supplyCount[supplyPos] - 1);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
*/
	memcpy(&testG, &G, sizeof(struct gameState));

  gainCard(1, &testG, 2, thisPlayer);
/*
	assert(testG.hand[ thisPlayer ][ testG.handCount[thisPlayer] - 1] == supplyPos);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1);
	assert(testG.supplyCount[supplyPos] == G.supplyCount[supplyPos] - 1);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
*/

	memcpy(&testG, &G, sizeof(struct gameState));
	
	gainCard(1, &testG, 0, thisPlayer);
/*
	assert(testG.discard[thisPlayer][ testG.discardCount[thisPlayer] - 1] == supplyPos);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);
	assert(testG.supplyCount[supplyPos] == G.supplyCount[supplyPos] - 1);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
*/


	//printf("All tests passed.\n");
  printf("\n");
	return 0;
}


