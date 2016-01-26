/* -----------------------------------------------------------------------
 * test isGameOver()
 * 
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;

    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, tribute, embargo};

    struct gameState G;
    int result;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
    printf("TESTING isGameOver():\n");
#endif

    // Test without any changes
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Test with empty province pile
    G.supplyCount[province] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // True
    assert(result == 1);

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // Test with one empty supply pile
    G.supplyCount[adventurer] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Test with two empty supply piles
    G.supplyCount[village] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Test with three empty supply piles
    G.supplyCount[great_hall] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // True
    assert(result == 1);

    // Re-test with two empty supply piles
    G.supplyCount[great_hall] = 10;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Re-test with one empty supply pile
    G.supplyCount[village] = 10;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Re-test with zero supply piles
    G.supplyCount[adventurer] = 10;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

   // Test with an almost empty province pile
    G.supplyCount[province] = 1;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    printf("\nAll tests passed!");

    return 0;
}
