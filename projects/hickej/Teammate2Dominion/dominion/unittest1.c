#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
  
  printf("testing drawCard\n");
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
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	drawCard(thisPlayer, &testG);
	newCards = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);
	//assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	//assert(testG.coins == G.coins + xtraCoins);

  // Now we're going to draw a bunch of cards to trigger drawCard when the deck is empty.
  int x;
  G.discardCount[0] = 50;
  for (x = 0; x < 100; x++){
    drawCard(thisPlayer, &testG);
  }

	//printf("All tests passed.\n");

  printf("\n");

	return 0;
}


