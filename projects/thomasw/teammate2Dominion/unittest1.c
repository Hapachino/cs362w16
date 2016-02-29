/*******************************************
* Test for handCard()
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

#define TESTFUNCTION "handCard()"

int main(int argc, char const *argv[])
{
	int i;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	memcpy(&testG, &G, sizeof(struct gameState));

	//Set up initial hand
	testG.hand[thisPlayer][0] = copper;
    testG.hand[thisPlayer][1] = silver;
    testG.hand[thisPlayer][2] = gold;
    testG.hand[thisPlayer][3] = village;
    testG.hand[thisPlayer][4] = minion;    

    printf("\nInitial Hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    for (i = 0; i < testG.handCount[thisPlayer]; ++i)
    {
    	int cardVal = handCard(i, &testG);
		printf("\nChecking handCard return values:\n");
		printf("Card = %d, expected = %d\n", cardVal, testG.hand[thisPlayer][i]);
		if (cardVal != testG.hand[thisPlayer][i])
		{
			printf("----------------- TEST FAILED -----------------\n");
		}
		else
			printf("----------------- TEST PASSED -----------------\n");
    }

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