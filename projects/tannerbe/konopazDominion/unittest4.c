#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output 
#define NOISY_TEST 1
#define TESTFUNCTION "isGameOver"

int main() {
    int seed = 1000;
	int numPlayers = 4;
    int i, j, e, result;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);
	int provinceCounts[5] = { 0, 1, 5, 8, 12 };
	int numEmptyStacks[6] = { 0, 1, 2, 3, 3, 7 };
	int emptyStacks[6][7] = { {}, { 10 }, { 4, 5 }, { 1, 7, 16 }, { 2, 4, 24 }, { 4, 5, 8, 10, 11, 12, 13 } };
	int isGameOverReturnValues[6] = { 0, 0, 0, 1, 0, 1 }; //isGameOver should return 0, 0, 0, 1, 0, 1 respectively, assuming provinceCount > 0 
 

    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	for (i = 0; i < 5; i++)
	{
		G.supplyCount[province] = provinceCounts[i];
		for (j = 0; j < 6; j++)
		{
			memcpy(&testG, &G, sizeof(struct gameState)); //copy the game
			for (e = 0; e < numEmptyStacks[j]; e++)
			{
				if (emptyStacks[j][e] < 17)
				{
					testG.supplyCount[emptyStacks[j][e]] = 0; //set predefined stacks to be empty
				}
			}			
			result = isGameOver(&testG);

			if (testG.supplyCount[province] == 0) // if provinces were empty, game should end regardless
			{
#if (NOISY_TEST == 1)
				printf("isGameOver = %d, expected = %d\n", result, 1);
#endif
				assert(result == 1);
			}
			else
			{
#if (NOISY_TEST == 1)
				printf("isGameOver = %d, expected = %d\n", result, isGameOverReturnValues[j]);
#endif
				assert(result == isGameOverReturnValues[j]);
			}

			//restore values and check that the rest of the game was left intact
			for (e = 0; e < numEmptyStacks[j]; e++)
			{
				if (emptyStacks[j][e] < 17)
				{
					testG.supplyCount[emptyStacks[j][e]] = G.supplyCount[emptyStacks[j][e]]; //restore supply counts
				}
			}
			result = memcmp(&testG, &G, sizeof(struct gameState));
			printf("memcmp result = %d, expected = %d\n", result, 0);
			assert(result == 0);

		}
	}
 
    printf("All tests passed!\n");

    return 0;
}
