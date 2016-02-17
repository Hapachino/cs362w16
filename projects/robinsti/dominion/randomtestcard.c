/****************************
 ** Author: Tim Robinson
 ** Date: 2/16/2015
 ** Description: This tests the Smithy card's play using random generation.
 ** This test is designed to run with the random test for the Adventurer card,
 ** which be found in the randomtestadventurer.c file.
 ** Add the following rules to your makefile in order to see the results for 
 ** these tests:
	
		randomtest1.o: randomtestadventurer.c dominion.o rngs.o
			gcc -o randomtest1 -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

		randomtest2.o: randomtestcard.c dominion.o rngs.o
			gcc -o randomtest2 -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

		randomtests: randomtest1.o randomtest2.o
			./randomtest1 > randomtestadventurer.out 2>&1
			gcov dominion.c -b >> randomtestadventurer.out
			gcov dominion.c -f >> randomtestadventurer.out
			./randomtest2 > randomtestcard.out 2>&1
			gcov dominion.c -b >> randomtestcard.out
			gcov dominion.c -f >> randomtestcard.out

 ** These rules will produce two output files, one for each of the tests.
 ** The randomtestadventurer.out file contains any test failure information
 ** for the Adventurer random testing as well as coverage information for both 
 ** tests. The randomtestcard.out file contains any test failure information
 ** for the Smithy random testing as well as coverage information for both 
 ** tests.
 ****************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"
#include "dominion.h"
#include "string.h"

int checkSmithy(int currentPlayer, struct gameState *state) {
	struct gameState * pre = malloc(sizeof(struct gameState));
	memcpy(pre, state, sizeof(struct gameState));

	int hand_pos = floor(Random() * state->handCount[currentPlayer]);

	playSmithy(currentPlayer, state, hand_pos);

	if (state->handCount[currentPlayer] != pre->handCount[currentPlayer] + 3)
	{
		printf("Player has %d cards, expected %d\n", state->handCount[currentPlayer], pre->handCount[currentPlayer] + 3);
		return 1;
	} else
	{
		return 0;
	}

}


int main() {

	int i, j, p;
	struct gameState G;
	struct gameState pre;
	int smithySuccess = 1;
	int adventurerSuccess = 1;

	printf("---------------- Testing %s Card ----------------\n", "Smithy");

	for (i = 0; i < 2000; i++)
	{
		for (j = 0; j < sizeof(struct gameState); j++)
		{
			((char *)&G)[j] = floor(Random() * 256);
		}
		memcpy(&pre, &G, sizeof(struct gameState));
		p = floor(Random() * 2);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.playedCardCount = floor(Random() * MAX_DECK);

		int smithyResult = checkSmithy(p, &G);

		if (smithySuccess)
		{
			if (smithyResult)
			{
				smithySuccess = 0;
			}
		}
	}


	if (!smithySuccess)
	{
		printf("Smithy random test failed.\n");
	} else
	{
		printf("Smithy random test passed.\n");
	}


	return 0;
}