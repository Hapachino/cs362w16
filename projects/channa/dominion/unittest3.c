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
    int i;
    int seed = 1000;
    // set seed for random numbers
    srand(3);

    int numPlayer = 2;
    int p, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, tribute, embargo};

    // int k[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room,
    //     feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward,
    //     tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map
    // };

    // const char *cards[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
    //     "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
    //     "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"
    // };

    struct gameState G;
    int result;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("\n========TESTING isGameOver():========\n");

    result = isGameOver(&G);
    printf("Game is over: %d\n", result);
    assert(result == 0);

    G.supplyCount[province] = 0;

    result = isGameOver(&G);
    printf("Game is over: %d\n", result);
    assert(result == 1);

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.supplyCount[adventurer] = 0;

    result = isGameOver(&G);
    printf("Game is over: %d\n", result);
    assert(result == 0);

    G.supplyCount[village] = 0;

    result = isGameOver(&G);
    printf("Game is over: %d\n", result);
    assert(result == 0);

    G.supplyCount[great_hall] = 0;

    result = isGameOver(&G);
    printf("Game is over: %d\n", result);
    assert(result == 1);

    G.supplyCount[great_hall] = 10;

    result = isGameOver(&G);
    printf("Game is over: %d\n", result);
    assert(result == 0);

    printf("\nAll tests passed!");

    return 0;
}
