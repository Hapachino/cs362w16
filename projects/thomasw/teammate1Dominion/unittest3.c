/*******************************************
* Test for isGameOver()
* Add this to your dominion makefile
* unittest1: unittest1.c dominion.o rngs.o
     gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*******************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver()"

int main(int argc, char const *argv[])
{
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	memcpy(&testG, &G, sizeof(struct gameState));

	printf("\nTest 1: No province cards remaining\n");
	testG.supplyCount[province] = 0;

	if (!isGameOver(&testG))
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

	//Test 2: if three supply pile are at 0, the game ends

	printf("\nTest 2: 3 supply piles are at 0\n");
	for (i = 0; i < 3; ++i)
	{
		testG.supplyCount[i] = 0;
	}

	if (!isGameOver(&testG))
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

	//Test 3: game over settings not met
	printf("\nTest 3: province and supply are stocked; not game over\n");

	//reset game state
	memcpy(&testG, &G, sizeof(struct gameState));

	if (isGameOver(&testG))
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

    //Test state unchanged for both players
	for (i = 0; i < 2; ++i)
    {
	    printf("\nTesting unchanged state for player%d:\n", i+1);
		printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
		printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
		printf("discard count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);
		if ((testG.handCount[i]) != (G.handCount[i]) || (testG.deckCount[i]) != (G.deckCount[i]) || (testG.discardCount[i]) != (G.discardCount[i]))
		{
			printf("----------------- TEST FAILED -----------------\n");
		}
		else
			printf("----------------- TEST PASSED -----------------\n");
    }

	return 0;
}