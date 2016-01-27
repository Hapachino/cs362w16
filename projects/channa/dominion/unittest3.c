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
    printf("----------------- TESTING isGameOver():\n");
#endif

    // Test without any changes
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 1: No changes\n");
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Test with empty province pile
    G.supplyCount[province] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 2: Empty province pile\n");
    printf("Game is over: %d\n", result);
#endif
    // True
    assert(result == 1);

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // Test with 1 empty supply pile
    G.supplyCount[adventurer] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 3: 1 empty supply pile\n");
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Test with 2 empty supply piles
    G.supplyCount[village] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 4: 2 empty supply piles\n");
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Test with 3 empty supply piles
    G.supplyCount[great_hall] = 0;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 5: 3 empty supply piles\n");
    printf("Game is over: %d\n", result);
#endif
    // True
    assert(result == 1);

    // Re-test with 2 empty supply piles
    G.supplyCount[great_hall] = 10;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 6: Re-test with 2 empty supply piles\n");
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Re-test with 1 empty supply pile
    G.supplyCount[village] = 10;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 7: Re-test with 1 empty supply piles\n");
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    // Re-test with 0 supply piles
    G.supplyCount[adventurer] = 10;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 8: Re-test with 0 empty supply piles\n");
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

   // Test with an almost empty province pile
    G.supplyCount[province] = 1;
    result = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Test 9: Re-test with almost empty province pile\n");
    printf("Game is over: %d\n", result);
#endif
    // False
    assert(result == 0);

    printf("\nAll tests passed!");

    return 0;
}
