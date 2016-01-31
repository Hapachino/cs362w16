/* -----------------------------------------------------------------------
 * isGameOver() Unit Testing file
 * Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"



// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int main() {
    int i, j, endgame = 0;
    int pass = 0, fail = 0;
    int tests = 100;  // number of times to run test
    int seed = 500;
    srand(seed);
    struct gameState state;

    printf ("TESTING isGameOver():\n");
    for(j=0; j < tests; j++)
    {
     endgame = 0;

    int zeros = 0;


    //load random number of kindom cards
    for(i = curse; i <= treasure_map; i++)
    {
        state.supplyCount[i] = rand() % 12 - 1;  //It is possible to have supplyCount set to -1 (card not used in game)
        if(state.supplyCount[i] == 0)
            zeros++;
    }

    if(state.supplyCount[province] == 0 || zeros >= 3)
        endgame = 1;

    if(endgame != isGameOver(&state))
    {
        printf("***FAILED*** ");
        printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
        for(i = duchy; i <= treasure_map; i++)
        {
            printf("%d, ", state.supplyCount[i]);
        }
        printf("\b\b]\n");
        fail++;
    }

    else
    {
        pass++;
        #if (NOISY_TEST == 1)
        printf("------------ ");
        printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
        for(i = duchy; i <= treasure_map; i++)
        {
            printf("%d, ", state.supplyCount[i]);
        }
        printf("\b\b]\n");
        #endif
    }

    }
    printf("Test results: [%d fails]  [%d/%d passes]\n", fail, pass, tests);
    return 0;
}
