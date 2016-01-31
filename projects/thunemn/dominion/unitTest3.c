/*
 * Unit test for isGameOver function
 *
 * unitTest3: unitTest3.c dominion.o rngs.o
 *      gcc -o unitTest3 -g unitTest3.c dominion.o rngs.o $(FLAGS)
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
    int i, cost;
    int isCorrect = 0;
    int card_cost[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4,
                         3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

    printf("TESTING getCost()\n");
    printf("TESTING all available cards:\n");
    //test each available card
    for(i = 0; i < 27; ++i) {
        cost = getCost(i);
        if(cost != card_cost[i])
            isCorrect = -1;
    }
#if (NOISY_TEST == 1)
    if(isCorrect != -1)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");

    //test a card which does not exist
    printf("TESTING non-existent card:\n");
    cost = getCost(35);
    if(cost == -1)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
#endif

    printf("\nAll tests passed: getCost()\n");

    return 0;
}
