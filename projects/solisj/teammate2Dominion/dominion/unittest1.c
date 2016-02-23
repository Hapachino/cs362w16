/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
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
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    int init, curseCount;
    struct gameState G;
    int numPlayerOption[3] = {2, 3, 4};
    
    printf("Initalization of 2 Player Game\n");
    init = initializeGame(numPlayerOption[0], k, 1000, &G);
    curseCount = G.supplyCount[0];
    printf("Current Curse Cards = %d, Correct Curse Cards = %d\n", curseCount, 10);
    supplyCount(curse, &G);
    assert(curseCount == 10);
    
    printf("Initalization of 3 Player Game\n");
    init = initializeGame(numPlayerOption[1], k, 1000, &G);
    curseCount = G.supplyCount[0];
    printf("Current Curse Cards = %d, Correct Curse Cards = %d\n", curseCount, 20);
    assert(curseCount == 20);

    printf("Initalization of 4 Player Game\n");
    init = initializeGame(numPlayerOption[2], k, 1000, &G);
    curseCount = G.supplyCount[0];
    printf("Current Curse Cards = %d, Correct Curse Cards = %d\n", curseCount, 30);
    assert(curseCount == 30);

    return 0;
}
