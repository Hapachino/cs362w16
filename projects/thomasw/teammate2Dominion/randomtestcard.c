/*******************************************
* Random Test for Steward
* Add this to your dominion makefile
* randomtest2: randomtestcard.c dominion.o rngs.o
     gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
*******************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Steward"

int main(int argc, char const *argv[])
{
	int j;
	int handpos = 0, bonus = 0;
	int seed;
	int pass = 1;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	printf("\n----------------- Random Testing Card: %s ----------------\n", TESTCARD);
	printf("Testing 10,000 random game instances\n");

	for (seed = 1; seed < 10000; ++seed)
	{
		initializeGame(numPlayers, k, seed, &G);

		G.handCount[thisPlayer] = rand() % 20 + 5;
		G.deckCount[thisPlayer] = rand() % 20 + 5;

		int choice1 = rand() % 3 + 1;
		int choice2 = rand() % G.handCount[thisPlayer];
		int choice3 = rand() % G.handCount[thisPlayer];
		if (choice2 == choice3)
		{
			choice3++;
		}


		for(j = 0; j < G.deckCount[thisPlayer]; j++)
		{
		    int randCard = rand() % 10;
            G.deck[thisPlayer][j] = k[randCard];
		}

		for(j = 0; j < G.handCount[thisPlayer]; j++)
		{
		    int randCard = rand() % 10;
            G.hand[thisPlayer][j] = k[randCard];
		}

		memcpy(&testG, &G, sizeof(struct gameState));

		//DEBUG
	 //    printf("\nInitial Deck Contents: \n");
	 //    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
	 //        printf("%d, ", testG.deck[thisPlayer][i]);
	 //    }

	 //    printf("\nInitial Hand contents:\n");
	 //    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
	 //        printf("%d, ", testG.hand[thisPlayer][i]);
		// }

	    cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	    //DEBUG
	 //    printf("\n after Deck Contents: \n");
	 //    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
	 //        printf("%d, ", testG.deck[thisPlayer][i]);
	 //    }

	 //    printf("\n after Hand contents:\n");
	 //    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
	 //        printf("%d, ", testG.hand[thisPlayer][i]);
		// }

	    //Draw 2 cards
		if (choice1 == 1)
		{
			if (testG.hand[thisPlayer][ testG.handCount[thisPlayer] - 1] != G.deck[thisPlayer][ G.deckCount[thisPlayer] - 1])
			{
				printf("\n----------------- TEST FAILED: Choice 1 draw 1, seed %d-----------------\n", seed);
				printf("Drew %d, expected %d: \n", testG.hand[thisPlayer][ testG.handCount[thisPlayer] - 1], G.deck[thisPlayer][ G.deckCount[thisPlayer] - 1]);
				pass = 0;

			}

			//Because we "plyaed" a card at handpos 0 and it gets discarded, we have to check handpos 0 for the other drawn card
			//Since discardcard() replaces the card with the last card in the hand.
			if (testG.hand[thisPlayer][0] != G.deck[thisPlayer][ G.deckCount[thisPlayer] - 2])
			{
				printf("----------------- TEST FAILED: Choice 1 draw 2, seed %d-----------------\n", seed);
				printf("Drew %d, expected %d: \n", testG.hand[thisPlayer][0], G.deck[thisPlayer][ G.deckCount[thisPlayer] - 2]);
				pass = 0;
			}
		}

		if (choice1 == 2)
		{
			if (testG.coins != G.coins + 2)
			{
				printf("\n----------------- TEST FAILED: Choice 2, seed %d: coins not added-----------------\n", seed);
				pass = 0;
			}
		}

		//You have to account for the played card being discarded, so the total discarded should be 3
		if (choice1 == 3)
		{
			if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 3)
			{
				printf("\n----------------- TEST FAILED: Choice 3, seed %d: -----------------", seed);
				printf("\nHand count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 3);
				pass = 0;
			}
			
		    if(testG.playedCardCount > 1)
		    {
				printf("\n----------------- TEST FAILED: Choice 3, seed %d: Cards not trashed-----------------", seed);
				pass = 0;
		    }

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
		printf("\n----------------- All TESTS PASSED ----------------- \n");
	}
	else
	{
		printf("\n--------------- TEST FAILED for 1 or more iterations ----------------- \n");
	}

	return 0;
}
