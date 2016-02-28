/*******************************************
* Random Test for Adventurer
* Add this to your dominion makefile
* randomtest1: randomtestadventurer.c dominion.o rngs.o
     gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
*******************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"

int main(int argc, char const *argv[])
{
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed;
	int pass = 1;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	printf("\n----------------- Random Testing Card: %s ----------------\n", TESTCARD);

	for (seed = 1; seed < 10000; seed++)
	{
		int expectedDiscard = 0;
		int expectedDraw = 0;
		int foundTreasure = 0;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		// copy the game state to a test case

		memcpy(&testG, &G, sizeof(struct gameState));
		
		int counter = testG.deckCount[thisPlayer] - 1;
		
		while(foundTreasure < 2)
		{
			if (testG.deck[thisPlayer][counter] == copper)
			{
				foundTreasure++;
				expectedDraw++;
			}
			else if (testG.deck[thisPlayer][counter] == estate)
			{
				expectedDiscard++;
			}
			counter=counter-1;
		}

		//DEBUG
		// printf("\nDeck Contents: \n");
	 //    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
	 //        printf("%d, ", testG.deck[thisPlayer][i]);
	 //    }

	 //    // Empty
	 //    printf("\nDiscard contents:\n");
	 //    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
	 //        printf("%d, ", testG.discard[thisPlayer][i]);
	 //    }

	 //    // 4, 4, 1, 4, 4
	 //    printf("\nHand contents:\n");
	 //    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
	 //        printf("%d, ", testG.hand[thisPlayer][i]);
	 //    }

		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - (expectedDraw + expectedDiscard))
	    {
	    	printf("\nTest Failed: Deck contents incorrect on seed iteration: %d\n", seed);
	    	pass = 0;
			printf("Expected Deck count: %d, Expected Discard Count: %d\n", (G.deckCount[thisPlayer] - (expectedDraw + expectedDiscard)), (G.discardCount[thisPlayer] + expectedDiscard));
			printf("Actual Deck count: %d, Actual Discard Count: %d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer]);
	    }

	    if (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + expectedDiscard)
	    {
	    	printf("\nTest Failed: Discard contents incorrect on seed itration: %d\n", seed);
	    	pass = 0;
			printf("Expected Deck count: %d, Expected Discard Count: %d\n", (G.deckCount[thisPlayer] - (expectedDraw + expectedDiscard)), (G.discardCount[thisPlayer] + expectedDiscard));
			printf("Actual Deck count: %d, Actual Discard Count: %d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer]);
	    }

        if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + expectedDraw)
	    {
	    	printf("\nTest Failed: hand contents incorrect on seed iteration: %d\n", seed);
	    	pass = 0;
	    }
		
		//Testing game state for Player 2
		if ((testG.handCount[thisPlayer+1]) != (G.handCount[thisPlayer+1]) || (testG.deckCount[thisPlayer+1]) != (G.deckCount[thisPlayer+1]) || (testG.discardCount[thisPlayer+1]) != (G.discardCount[thisPlayer+1]))
		{
			printf("----------------- TEST FAILED -----------------\n");
			pass = 0;
		}

	}

	if(pass)
	{
		printf("\n----------------- ALL TESTS PASSED ----------------- \n");
	}
	else
	{
		printf("\n--------------- TEST FAILED for 1 or more iterations ----------------- \n");
	}

	return 0;
}