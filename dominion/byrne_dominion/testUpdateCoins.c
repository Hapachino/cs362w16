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
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    //initializeGame(2, k, seed, &G);
    int maxSupply = treasure_map + 1;
    int testSeed = 1000;
    //long   i;
    long   x;
    double u;
    char   ok = 0;
    PlantSeeds(-1);
    SelectStream(0);                  /* select the default stream */

    //PutSeed(1);                       /* and set the state to 1    */
    for(i = 0; i < 10000; i++){
        int supplyDex = floor(Random() * maxSupply);
        printf("%d\n",supplyDex);
    }


    printf("All tests passed!\n");

    return 0;
}
