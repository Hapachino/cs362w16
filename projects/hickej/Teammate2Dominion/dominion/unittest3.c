#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    printf("Testing updateCoins\n");
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
	
	G.handCount[thisPlayer]++;
	
	// Test correct adding of copper
	G.hand[thisPlayer][G.handCount[thisPlayer] - 1] = copper;
	
	updateCoins(thisPlayer, &testG, 0);
  updateCoins(thisPlayer, &G, 0);
  
  printf("testG coin count: %d, G coin count: %d (G should have 1 more)\n", testG.coins, G.coins);
  //assert(testG.coins == G.coins - 1);
  
  
  // Test correct adding of silver
  G.hand[thisPlayer][G.handCount[thisPlayer] - 1] = silver;
  
  updateCoins(thisPlayer, &testG, 0);
  updateCoins(thisPlayer, &G, 0);
  
  printf("testG coin count: %d, G coin count: %d (G should have 2 more)\n", testG.coins, G.coins);
  //assert(testG.coins == G.coins - 2);
  
  
  // Test correct adding of gold
  G.hand[thisPlayer][G.handCount[thisPlayer] - 1] = gold;
  
  updateCoins(thisPlayer, &testG, 0);
  updateCoins(thisPlayer, &G, 0);
  
	printf("testG coin count: %d, G coin count: %d (G should have 3 more)\n", testG.coins, G.coins);
	//assert(testG.coins == G.coins - 3);
	
	
	// Test adding in a bonus
	G.handCount[thisPlayer]--;
	updateCoins(thisPlayer, &testG, 0);
  updateCoins(thisPlayer, &G, 1);
  printf("testG coin count: %d, G coin count: %d (G should have 1 more)\n", testG.coins, G.coins);
	//assert(testG.coins == G.coins - 1);


	//printf("All tests passed.\n");
	printf("\n");

	return 0;
}


