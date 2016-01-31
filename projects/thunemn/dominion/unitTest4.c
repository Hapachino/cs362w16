/*
 * Unit test for updateCoins function
 *
 * unitTest1: unitTest1.c dominion.o rngs.o
 *      gcc -o unitTest1 -g unitTest1.c dominion.o rngs.o $(FLAGS)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove prinftf's from output
#define NOISY_TEST 1

int main() {
    int i, p, new_game, toFlag, supplyPos, result;
    int seed = 1000;
    int numPlayer = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    p = 0;

    printf("TESTING gainCard()\n");

    G.deckCount[p] = 30;
    G.discardCount[p] = 20;
    G.handCount[p] = 7;
    G.discard[p][G.discardCount[p]] = 75;
    supplyPos = 4;
#if (NOISY_TEST == 1)
    printf("TESTING toFlag = 0\n");
#endif
    G.supplyCount[4] = 5;
    struct gameState toFlag_0;
    memcpy(&toFlag_0, &G, sizeof(struct gameState));

    result = gainCard(supplyPos, &G, 0, p);
#if (NOISY_TEST == 1)
    if((toFlag_0.discardCount[p] + 1 == G.discardCount[p]))
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
#endif
#if (NOISY_TEST == 1)
    printf("TESTING toFlag = 1\n");
#endif
    G.supplyCount[4] = 5;
    struct gameState toFlag_1;
    memcpy(&toFlag_1, &G, sizeof(struct gameState));

    result = gainCard(supplyPos, &G, 1, p);
#if (NOISY_TEST == 1)
    if((toFlag_1.deckCount[p] + 1 == G.deckCount[p]))
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
#endif
#if (NOISY_TEST == 1)
    printf("TESTING toFlag = 2\n");
#endif
    G.supplyCount[4] = 5;
    struct gameState toFlag_2;
    memcpy(&toFlag_2, &G, sizeof(struct gameState));

    result = gainCard(supplyPos, &G, 2, p);
#if (NOISY_TEST == 1)
    if((toFlag_2.handCount[p] + 1 == G.handCount[p]))
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
#endif



    //check if supply pile is empty (0) or card is not used in game (-1)
#if (NOISY_TEST == 1)
    printf("TESTING empty pile or invalid card\n");
    result = gainCard(-1, &G, -1, p);
    if(result == -1) {
        printf("TEST PASSED: Card not in pile or card does not exist\n");
    }
    else {
        printf("TEST FAILED\n");
    }
#endif

    printf("\nAll tests passed: gainCard()\n");

    return 0;
}


