/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for function getCost

Business Logic to test:
* Function returns the correct number for each card
* Function does not affect game state

**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

# define TESTFUNCTION "getCost"

int main() {
    printf("---------- Testing Function: %s --------------\n", TESTFUNCTION);
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    int costs[10] = {6,4,2,3,5,5,4,4,5,4};
    int testsRun = 0, testsPassed = 0;
    struct gameState testGame;
    struct gameState cleanGame;

    for (int i = 0; i < 10; i++) {
        initializeGame(2, k, 500, &cleanGame);
        memcpy(&testGame, &cleanGame, sizeof(struct gameState));
        if (costs[i] == getCost(k[i])) {
            printf("Card %d cost is correct. Test Failed.\n", k[i]);
            testsPassed++;
        } else {
            printf("Card %d cost is incorrect. Test Failed.\n", k[i]);
        }
        testsRun++;
        printf("Was game state affected?\n");
        if (memcmp(&testGame, &cleanGame, sizeof(struct gameState)) == 0) {
            printf("No. Test Passed.\n");
            testsPassed++;
        } else {
            printf("Yes. Test Failed.\n");
        }
        testsRun++;
    }

    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Function Complete ------\n", TESTFUNCTION);
    return 0;
}