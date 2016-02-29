/* Paul Zotz
 * CS 362 Winter 2015
 * Assignment 3 - unit test 2 - isGameOver()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int returnVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    printf ("TESTING isGameOver:\n");
    initializeGame(numPlayer, k, seed, &G);

    // test 1 - newly initialized game
    memcpy(&testG, &G, sizeof(struct gameState));
    returnVal = isGameOver(&testG);
#if (NOISY_TEST == 1)
    printf("\n");
    printf("Newly initialized game\n");
    printf("Return value: %d, expected: %d\n", returnVal, 0);
#endif
    assert(returnVal == 0);

    // test 2 - four empty piles
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[copper] = 0;
    testG.supplyCount[gold] = 0;
    testG.supplyCount[silver] = 0;
    testG.supplyCount[duchy] = 0;
    returnVal = isGameOver(&testG);

#if (NOISY_TEST == 1)
    printf("\n");
    printf("Four empty supply piles\n");
    printf("Return value: %d, expected: %d\n", returnVal, 1);
#endif
    assert(returnVal == 1);

    // test 3 - empty province supply pile
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[province] = 0;
    returnVal = isGameOver(&testG);

#if (NOISY_TEST == 1)
    printf("\n");
    printf("Empty Province pile (no others empty)\n");
    printf("Return value: %d, expected: %d\n", returnVal, 1);
#endif
    assert(returnVal == 1);

    printf("All tests passed!\n");

    return 0;
}
