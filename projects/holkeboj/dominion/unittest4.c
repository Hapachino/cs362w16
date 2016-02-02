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
    int other_cards[18] = {curse, estate, duchy, province, copper, silver, gold, council_room,
                feast, remodel, baron, great_hall, steward, tribute, ambassador,
                outpost, salvager, treasure_map};
    int other_costs[18] = {0,2,5,8,0,3,6,5,4,4,4,3,3,5,3,5,4,4};
    int testsRun = 0, testsPassed = 0;
    struct gameState testGame;
    struct gameState cleanGame;

    for (int i = 0; i < 18; i++) {
        initializeGame(2, k, 500, &cleanGame);
        memcpy(&testGame, &cleanGame, sizeof(struct gameState));
        if (i < 10) {
            if (costs[i] == getCost(k[i])) {
                printf("Kingdom Card %d cost is correct. Test Passed.\n", k[i]);
                testsPassed++;
            } else {
                printf("Kingdom Card %d cost is incorrect. Test Failed.\n", k[i]);
            }
            testsRun++;
        }
        if (other_costs[i] == getCost(other_cards[i])) {
            printf("Other Card %d cost is correct. Test Passed.\n", other_cards[i]);
            testsPassed++;            
        } else {
            printf("Other Card %d cost is incorrect. Test Failed.\n", other_cards[i]);
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